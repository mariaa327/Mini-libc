// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	while (*source != '\0') {
		*destination = *source; // copiaza fiecare caracter
		destination++;
		source++;
	}
	*destination = '\0'; // adauga terminatorul de sir
    return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	size_t i;
	for (i = 0; i < len; i++) {
		if (source[i] != '\0') {
			destination[i] = source[i];
		} else {
			destination[i] = '\0'; // daca source este mai scurt decat len atunci se completeaza cu nule
		}
	}
	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	while (*destination != '\0') {
		destination++; // muta pointerul la finalul lui destination
	}

	while (*source != '\0') {
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	while (*destination != '\0') {
        destination++;
    }

    size_t i;
    for (i = 0; i < len && source[i] != '\0'; i++) {
		destination[i] = source[i]; // adauga len caractere la final
    }

    destination[i] = '\0';
    return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	while (*str1 != '\0' && *str2 != '\0') {
		// compara caracterele pana cand se gaseste unul diferit sau se ajunge la final
		if (*str1 != *str2) {
			if (*str1 < *str2)
				return -1;
			else
				return 1;
		}
		str1++;
		str2++;
	}

	// daca ambele siruri au ajuns la final atunci sunt egale
	if (*str1 == '\0' && *str2 == '\0')
		return 0;

	// daca primul sir ajunge la final atunci returneaza -1, altfel 1
	if (*str1 == '\0')
		return -1;
	else
		return 1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	// la fel ca la strcmp doar ca compar primele len caractere
	size_t i;
	for (i = 0; i < len; i++) {
		if (str1[i] == '\0' && str2[i] == '\0')
			return 0;
		if (str1[i] != str2[i]) {
			if (str1[i] < str2[i])
				return -1;
			else
				return 1;
		}
	}
	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */

	// cauta caracterul 'c' in sir
	while (*str != '\0') {
		if (*str == (char)c)
			return (char *)str;
		str++;
	}

	// in cazul in care caracterul este '\0', il returneaza
	if ((char)c == '\0')
		return (char *)str;

	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	const char *last = NULL;

	// parcurge sirul si retine ultima aparitie a lui 'c'
	while (*str != '\0') {
		if (*str == (char)c)
			last = str;
		str++;
	}

	if ((char)c == '\0')
		return (char *)str;

	return (char *)last;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	// daca needle e gol returneaza inceputul
	if (*needle == '\0')
		return (char *)haystack;

	// parcurg caracterele din haystack
	while (*haystack != '\0') {
		const char *hay = haystack;
		const char *nee = needle;

		// compar caracterele succesive
		while (*hay != '\0' && *nee != '\0' && *hay == *nee) {
			hay++;
			nee++;
		}

		// daca am ajuns la finalul lui needle inseamna ca am gasit subsirul
		if (*nee == '\0')
			return (char *)haystack;

		haystack++;
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */

	if (*needle == '\0')
		return (char *)haystack;

	const char *last = NULL;

	// parcurg intregul sir, de aceea nu am return
	while (*haystack != '\0') {
		const char *hay = haystack;
		const char *nee = needle;

		while (*hay != '\0' && *nee != '\0' && *hay == *nee) {
			hay++;
			nee++;
		}

		// daca s-aau potrivit caracterele cu needle, atunci retin ultima potrivire
		if (*nee == '\0')
			last = haystack;

		haystack++;
	}
	return (char *)last;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	char *dest = (char *)destination;
	char *src = (char *)source;

	size_t i;
	// copiez cate un octet in destinatie
	for (i = 0; i < num; i++)
		dest[i] = src[i];

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	char *dest = (char *)destination;
	const char *src = (const char *)source;

	size_t i;

	// verific suprapunerea zonelor de memorie
	if (dest > src && dest < src + num) {
		for (i = num; i > 0; i--)
			dest[i-1] = src[i-1]; // daca exista suprapuneri atunci	copiez in sens invers
	} else {
		for (i = 0; i < num; i++)
			dest[i] = src[i]; // copiez normal
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */

	const char *p1 = (const char *)ptr1;
	const char *p2 = (const char *)ptr2;

	size_t i;
	// compar octet cu octet
	for (i = 0; i < num; i++) {
		if (p1[i] != p2[i]){
			if (p1[i] < p2[i]) {
				return -1;
			} else {
				return 1;
			}
		}
	}

	return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	char *src = (char *)source;
	size_t i;
	char uc = (char)value;

	// inlocuiesc fiecare octet cu ce e in value
	for (i = 0; i < num; i++)
		src[i] = uc;

	return source;
}
