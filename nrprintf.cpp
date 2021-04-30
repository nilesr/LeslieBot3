#include "nrprintf.h"

char* nrprintf(const char* something, ...) {
	char buf;
	va_list args;
	va_start(args, something);
	const int needed = vsnprintf(&buf, 1, something, args);
	char* result = (char*) malloc(needed+1);
	vsnprintf(result, needed+1, something, args);
	va_end(args);
	return result;
}

