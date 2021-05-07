#pragma once

#include "nrprintf.h"
#include "smashers.h"

typedef char* (randomizer_t)();

randomizer_t random_smasher;
randomizer_t random_smasher;
randomizer_t random_letter;
randomizer_t random_smasher_diagonal;
randomizer_t random_smasher_horizontal;
randomizer_t random_smasher_vertical;
randomizer_t random_franchize;
randomizer_t last_three_matches;
randomizer_t prom;
randomizer_t cant_look_sans;
randomizer_t random_smasher_horizontal_exact;
randomizer_t therapy;
randomizer_t sus;
randomizer_t light_green;
randomizer_t infallable;
randomizer_t recent_seen_fanart;
randomizer_t recent_drawn_fanart;
randomizer_t zelda_arm_wrestling;
randomizer_t midpoint_enemies;
randomizer_t leslie;
randomizer_t want_added_to_botw2;
randomizer_t most_chaotic;
randomizer_t least_chaotic;
randomizer_t inflated_ego;
randomizer_t not_played_today;
randomizer_t surprised_if_transported_to_reality;
randomizer_t never_played_franchize;
randomizer_t same_franchize_as_last_game_played;
randomizer_t would_cry_at_last_character;
randomizer_t likes_owls;
randomizer_t anime;
randomizer_t buff;
randomizer_t probably_banned_from_tournaments;
randomizer_t best_duck;
randomizer_t worst_duck;
randomizer_t cant_tie_shoes;
randomizer_t best_professor;
randomizer_t afraid_of;
randomizer_t would_beat_up_last_character;
randomizer_t confused_by_rickroll;
randomizer_t least_vowels;
randomizer_t most_vowels;
randomizer_t dab;
randomizer_t negative_int;
randomizer_t negative_chr;
randomizer_t hottest_take;

typedef struct selector_t {
	int weight;
	randomizer_t* randomizer;
} selector_t;

#define N_SELECTOR 46
#ifdef DEFINE_SELECTORS
selector_t SELECTORS[N_SELECTOR] {
	{15, &random_smasher},
	{20, &random_letter},
	{20, &random_smasher_diagonal},
	{20, &random_smasher_horizontal},
	{20, &random_smasher_vertical},
	{20, &random_franchize},
	{10, &last_three_matches},
	{1, &prom},
	{1, &cant_look_sans},
	{10, &random_smasher_horizontal_exact},
	{2, &therapy},
	{1, &sus},
	{1, &light_green},
	{2, &infallable},
	{5, &recent_seen_fanart},
	{1, &recent_drawn_fanart},
	{2, &zelda_arm_wrestling},
	{5, &midpoint_enemies},
	{10, &leslie},
	{1, &want_added_to_botw2},
	{1, &most_chaotic},
	{1, &least_chaotic},
	{5, &inflated_ego},
	{10, &not_played_today},
	{1, &surprised_if_transported_to_reality},
	{5, &never_played_franchize},
	{5, &same_franchize_as_last_game_played},
	{5, &would_cry_at_last_character},
	{1, &likes_owls},
	{5, &anime},
	{5, &buff},
	{10, &probably_banned_from_tournaments},
	{1, &best_duck},
	{1, &worst_duck},
	{2, &cant_tie_shoes},
	{2, &best_professor},
	{2, &afraid_of},
	{5, &would_beat_up_last_character},
	{2, &confused_by_rickroll},
	{1, &least_vowels},
	{1, &most_vowels},
	{5, &dab},
	{5, &negative_int},
	{5, &negative_chr},
	{1, &hottest_take},
};
#else
extern selector_t SELECTORS[N_SELECTOR];
#endif

char* random_challenge();
char* random_trivia();
