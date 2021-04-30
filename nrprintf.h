#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// Totally optional, can be excluded if the compiler doesn't support __attribute__
char* nrprintf(const char* something, ...) __attribute__ ((format (printf,1,2)));
