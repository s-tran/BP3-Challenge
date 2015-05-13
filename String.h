#ifndef _String_h
#define _String_h 1

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef
struct String {
	char* ptr;
	uint32_t length;
} String;

/* initialize and return a string
* use the input (mundane C string) as a reference for the
* contents of the created string */
String StringCreate(char input[]) { // makes a string based on input and makes it null-terminated (so it can be printed normally)
	String result;

	uint32_t k = 0;
	while (input[k]) {
		k += 1;
	}

	result.length = k;
	result.ptr = (char*)malloc(k + 1);

	for (k = 0; k < result.length; k += 1) {
		result.ptr[k] = input[k];
	}

	result.ptr[result.length] = 0;

	return result;
}

String StringDup(String in) {
	String result;
	result.length = in.length;
	result.ptr = (char*)malloc(result.length + 1);
	for (uint32_t k = 0; k < result.length + 1; k += 1) {
		result.ptr[k] = in.ptr[k];
	}
	return result;
}

void StringPrint(String s) { // unnecessary here
	for (uint32_t k = 0; k < s.length; k += 1) {
		putchar(s.ptr[k]);
	}
}

uint32_t StringSize(String s) { return s.length; }

void StringDestroy(String s) { free(s.ptr); }

int StringCompare(String s1, String s2) { // 0 = equal, 1 = first greater, 2 = second greater; must be equal lengths
	if (s1.length != s2.length) {
		abort();
	}
	int k = 0;
	while (s1.ptr[k]) {
		if (s1.ptr[k] > s2.ptr[k]) { return 1; }
		if (s1.ptr[k] < s2.ptr[k]) { return 2; }
		k = k + 1;
	}
	return 0;
}

void StringClear(String s1) { // clears a string to all 0s
	for (int i = 0; i < s1.length; i++) {
		s1.ptr[i] = 0;
	}
	s1.length = 0;
}

/* int main(void) {
	String s = StringCreate("Craig");
	String t = StringDup(s);

	t = s;

	printf("Hello ");
	StringPrint(s);
	printf(" I see you're %d characters long\n",
		StringSize(s));


	StringDestroy(s);
	StringDestroy(t);
} */

#endif /* _String_h */


