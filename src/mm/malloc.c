// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	static int initialized = 0; // initializez lista de memorie la primul apel
    if (!initialized) {
        mem_list_init();
        initialized = 1;
    }

    if (size == 0)
        size = 1;

    // aloc memorie cu mmap, cu dimensiunea ceruta
    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
        return NULL;

    // adaug blocul in lista de memorie alocata
    if (mem_list_add(ptr, size) < 0) {
        munmap(ptr, size);
        return NULL; // fără errno
    }

    return ptr; // pointerul catre memoria alocata
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
    // daca size > (SIZE_MAX / nmemb) inmultirea ar depasi SIZE_MAX
	if (nmemb != 0 && size > (size_t)-1 / nmemb)
        return NULL;

    size_t total_size = nmemb * size; // dimensiunea totala necesara
    if (total_size == 0)
        total_size = 1;

    void *ptr = malloc(total_size); // aloc memorie
    if (ptr == NULL)
        return NULL;

    memset(ptr, 0, total_size); // initializez toata memoria cu 0

    return ptr;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
	if (ptr == NULL)
        return;

    struct mem_list *item = mem_list_find(ptr); // caut blocul in lista de alocari
    if (item == NULL)
        return; // pointer invalid sau deja eliberat

    munmap(item->start, item->len); // elibereaza memoria reala

    mem_list_del(ptr); // elimina intrarea din lista de alocari
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	struct mem_list *item;
    void *new_ptr;

    // daca ptr este null atunci realloc se comporta ca si malloc
    if (ptr == NULL) {
        return malloc(size);
    }

    // daca size este 0 atunci realloc se comporta ca free
    if (size == 0) {
        item = mem_list_find(ptr);
        if (item != NULL) {
            munmap(ptr, item->len);
            mem_list_del(ptr);
        }
        return NULL;
    }

    // caut blocul de memorie existent in lista
    item = mem_list_find(ptr);
    if (item == NULL)
        return NULL;

    // maresc memoria
    new_ptr = mremap(ptr, item->len, size, MREMAP_MAYMOVE);
    if (new_ptr == MAP_FAILED)
        return NULL;

    // actualizez lista de memorie daca adresa s-a schimbat si sterg intrarea veche si adaug una nous cu adresa noua
    if (new_ptr != ptr) {
        mem_list_del(ptr);
        if (mem_list_add(new_ptr, size) == -1) {
            munmap(new_ptr, size);
            return NULL;
        }
    } else {
        // aceeasi adresa dar cu alt size
        item->len = size;
    }

    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
    // daca size > (SIZE_MAX / nmemb) inmultirea ar depasi SIZE_MAX
	if (nmemb != 0 && size > ((size_t)-1) / nmemb) {
        return NULL;
    }

    return realloc(ptr, nmemb * size);
}
