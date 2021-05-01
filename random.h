#pragma once

#include "nrprintf.h"
#include "smashers.h"

typedef char* (randomizer_t)();

randomizer_t random_smasher;

typedef struct selector_t {
	int weight;
	randomizer_t* randomizer;
} selector_t;

#define N_SELECTOR 1
#ifdef DEFINE_SELECTORS
selector_t SELECTORS[N_SELECTOR] {
	{1, &random_smasher}
	// TODO more
};
#else
extern selector_t SELECTORS[N_SELECTOR];
#endif

char* random_challenge();
char* random_trivia();
