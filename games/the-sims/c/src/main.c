// The Sims Dreamport: the game's own code, in C, on the PlayStation 2's kit in C (kit/ps2/c/ps2.h), with the console's screen,
// frame, sound and buttons in console.h, which the build makes from kit/consoles.js. src/main.js runs it on the page,
// built to WebAssembly as src/game.wasm (kit/ps2/c/README.md).

#include "ps2.h"

// once, with the player's copy in kit_copy: the screen, an NTSC one showing the framebuffer at the start of the GS's memory
void game_start(void) {
  gs_screen(GS_PMODE, 0xFF25);
  gs_screen(GS_SMODE2, 1);
  gs_screen(GS_DISPFB1, (SCREEN_W / 64) << 9);
  gs_screen(GS_DISPLAY1, 656 | 36 << 12 | 3 << 23);
  gs_screen(GS_DISPLAY1 + 4, (SCREEN_W * 4 - 1) | (SCREEN_H - 1) << 12);
}

// what the original does each frame, writing the GS's registers as it does, with its sums done the EE's way (ee_add
// and the rest). As the console starts, the original gives the GS nothing
void game_step(uint32_t buttons) {}

// its picture: what the screen shows of what the GS drew
void game_draw(void) { gs_show(); }

// its sound, CONSOLE_SOUND_RATE samples a second, which starts as silence
void game_sound(float *left, float *right, int count) {}
