#include "random.h"
#include <string.h>
#define DEFINE_TRIVIA 1
#include "trivia/trivia.h"

void loadLogo(franchize_t franchize);

int serial(const char* fmt, ...);

int random();

char* random_smasher() {
	const smasher_t* smasher = smashers + random() % N_SMASHERS;
	loadLogo(smasher->franchize);
	char* result = nrprintf("Play %s", smasher->name);
	return result;
}

char* random_challenge() {
	int sum_weights = 0;
	for (int i = 0; i < N_SELECTOR; i++) {
		sum_weights += SELECTORS[i].weight;
	}
  int rand = random() % sum_weights;
	int i = 0;
	while (rand >= SELECTORS[i].weight) {
		rand -= SELECTORS[i].weight;
		i += 1;
	}
	serial("Using randomizer at index %d\r\n", i);
	return (*SELECTORS[i].randomizer)();
}

char* random_trivia() {
	loadLogo(SMASH);
	// TODO this wil not be the final implementation
	return strdup(String{trivia(random() % N_TRIVIA)}.c_str());
}
