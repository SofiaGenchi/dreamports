// Twins of the functions of The Sims's boot program, SLUS_205.73, each named by its address in the comment above it,
// with every value it uses where the console keeps it, as games/the-sims/proof/addresses.json names them.

#include "ps2.h"

typedef unsigned int u32;

// a word the start-up keeps, which says which of two functions the game hands on
extern u32 boot_choice;

/** 0x00100B30: nothing to do, and 0 for it */
int boot_nothing(void) {
  return 0;
}

/** 0x00100820: the function the game takes, at 0x001009F0 when boot_choice is set and at 0x00100BB8 when it isn't */
u32 boot_pick(void) {
  if (boot_choice != 0) return 0x001009F0;
  return 0x00100BB8;
}

/** 0x00119118: nothing to do for the start-up's step it's given */
void boot_step_nothing(int step, int which) {}

/** 0x00119120: the start-up's first step for everything, which 0x00119118 has nothing to do for */
void boot_first_step(void) {
  boot_step_nothing(1, 0xFFFF);
}

/** 0x0011D230: nothing to do */
void boot_nothing_too(void) {}

/** 0x0011D9D8: an object made ready, its word at 76 cleared and its word at 80 set, and given back */
u32 *boot_ready(u32 *object) {
  object[19] = 0;
  object[20] = 1;
  return object;
}
