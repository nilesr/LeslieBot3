#include "random.h"
#include <string.h>
#define DEFINE_TRIVIA 1
#include "trivia/trivia.h"
#include <algorithm>

void loadLogo(franchize_t franchize);

int serial(const char* fmt, ...);

int random();

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
  // Just in case the randomizer we select doesn't set a logo
  loadLogo(SMASH);
  return (*SELECTORS[i].randomizer)();
}

char* random_trivia() {
  static bool shuffled = false;
  static int order[N_TRIVIA];
  if (!shuffled) {
    for (int i = 0; i < N_TRIVIA; i++) {
      order[i] = i;
    }    
    for (int c = 0; c < N_TRIVIA * 10; c++) {
      int i = random() % N_TRIVIA;
      int j = random() % N_TRIVIA;
      std::swap(order[i], order[j]);
    }
    shuffled = true;
  }
  static int idx = 0;
  loadLogo(SMASH);
  String s{trivia(order[idx++ % N_TRIVIA])};
  return strdup(s.c_str());
}

char* random_smasher() {
  const smasher_t* smasher = smashers + random() % N_SMASHERS;
  loadLogo(smasher->franchize);
  char* result = nrprintf("Play %s", smasher->name);
  return result;
}

char* random_letter() {
  char letter;
  int total;
  const smasher_t* randomly_selected_smasher;
  // There are no smashers with a Q in their name
  do {
    letter = 'A' + (random() % 26);
    total = 0;
    for (int i = 0; i < N_SMASHERS; i++) {
      if (strchr(smashers[i].name, letter) || strchr(smashers[i].name, tolower(letter))) {
	total++;
	if (random() % total == 0) {
	  randomly_selected_smasher = smashers + i;
	}
      }
    }
  } while (total == 0);
  loadLogo(randomly_selected_smasher->franchize);
  return nrprintf("Play someone with a %c in their name (%d total)", letter, total);
}

char* random_smasher_diagonal() {
  const smasher_t* smasher = smashers + random() % N_SMASHERS;
  loadLogo(smasher->franchize);
  return nrprintf("Play someone diagonal from %s", smasher->name);
}

char* random_smasher_horizontal() {
  const smasher_t* smasher = smashers + random() % N_SMASHERS;
  loadLogo(smasher->franchize);
  return nrprintf("Play someone left or right from %s", smasher->name);
}

char* random_smasher_vertical() {
  const smasher_t* smasher = smashers + random() % N_SMASHERS;
  loadLogo(smasher->franchize);
  return nrprintf("Play someone up or down from %s", smasher->name);
}

char* random_franchize() {
  franchize_t franchize = (franchize_t) (random() % N_FRANCHIZE);
  int total = 0;
  for (int i = 0; i < N_SMASHERS; i++) {
    if (smashers[i].franchize == franchize) {
      total++;
    }
  }
  loadLogo(franchize);
  return nrprintf("Play someone from this franchize (%d total)", total);
}

char* last_three_matches() {
  return strdup("Play someone you played against in the last 3 matches");
}

char* prom() {
  return strdup("Play someone you would be willing to go to prom with");
}

char* cant_look_sans() {
  return strdup("Play someone who can't look sans in the eyes");
}

char* random_smasher_horizontal_exact() {
  const int offset = (random() % 7) + 1;
  const char* direction = (random() % 2) == 0 ? "left" : "right";
  return nrprintf("Play the character %d to the %s from whoever you last played as", offset, direction);
}

char* therapy() {
  return strdup("Play someone who needs therapy");
}

char* sus() {
  return strdup("Play the most \"sus\" character");
}

char* light_green() {
  return strdup("Play the character who would pick light green in among us");
}

char* infallable() {
  return strdup("Play someone who has never done anything wrong, bless their hearts");
}

char* recent_seen_fanart() {
  return strdup("Play the character that you last saw fanart of");
}

char* recent_drawn_fanart() {
  return strdup("Play the character that you last drew fanart of");
}

char* zelda_arm_wrestling() {
  return strdup("Play someone who zelda could beat in an arm wrestling match");
}

char* midpoint_enemies() {
  return strdup("Play someone in the middle of two characters who would not like each other");
}

char* leslie() {
  return strdup("Play the character that Leslie would make you play");
}

char* want_added_to_botw2() {
  return strdup("Play the character you would most like added to BOTW 2");
}

char* most_chaotic() {
  return strdup("Play the most chaotic character");
}

char* least_chaotic() {
  return strdup("Play the least chaotic character");
}

char* inflated_ego() {
  return strdup("Play someone who thinks they are cooler than they really are");
}

char* not_played_today() {
  return strdup("Play someone you haven't played yet today");
}

char* surprised_if_transported_to_reality() {
  return strdup("Play the fighter who would be most suprised if they were transported to reality");
}

char* never_played_franchize() {
  return strdup("Play someone from a video game you've never played and never want to play");
}

char* same_franchize_as_last_game_played() {
  return strdup("Play a character from the same franchize as the last game you've played");
}

char* would_cry_at_last_character() {
  return strdup("Play someone who would cry if they saw your last character");
}

char* likes_owls() {
  return strdup("Play the character who most likes owls");
}

char* anime() {
  return strdup("Play an anime character");
}

char* buff() {
  return strdup("Play a buff character");
}

char* probably_banned_from_tournaments() {
  return strdup("Play someone you think should be banned from smash competitions");
}

char* best_duck() {
  return strdup("Play the character that would survive the best if they were turned into a duck");
}

char* worst_duck() {
  return strdup("Play the character that would survive the worst if they were turned into a duck");
}

char* cant_tie_shoes() {
  return strdup("Play a character that probably doesn't know how to tie their shoes");
}

char* best_professor() {
  return strdup("Play a character who you would want as a professor, and isn't a teacher");
}

char* afraid_of() {
  return strdup("Play a character who you are afraid of");
}

char* would_beat_up_last_character() {
  return strdup("Play a character that would beat up the character you last played as");
}

char* confused_by_rickroll() {
  return strdup("Play a character that would be confused by a rick roll");
}

char* least_vowels() {
  return strdup("Play the character with the least number of vowels in their name");
}

char* most_vowels() {
  return strdup("Play the character with the most number of vowels in their name");
}

char* dab() {
  return strdup("Play a character who would unironically dab");
}

char* negative_int() {
  return strdup("Play a character who has a negative intelligence stat");
}

char* negative_chr() {
  return strdup("Play a character who has a negative charisma stat");
}

char* hottest_take() {
  return strdup("Play the character you have the hottest of takes on");
}
