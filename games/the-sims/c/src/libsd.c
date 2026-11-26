// Twins of the functions of The Sims's sound library for the IOP, LIBSD.IRX, each named by the code map's key, its address
// from the module's start and the module, in the comment above it. The sound chip, the SPU2, is written at the addresses
// the module writes it, from 0xBF900000, where core 0's registers start and core 1's are 0x400 further on. The module's
// own values are named by labels with their addresses from its start.

typedef unsigned short u16;
typedef unsigned int u32;


// where each of the library's parameters is, a register of the sound chip for each kind
extern const u32 D_00004930[];
// each core's interrupt handler, and what it's given, two words apart
extern u32 D_000052C8[2];
extern u32 D_000052DC[4];
// what the library keeps of its transfers, cleared as it starts
extern u32 D_000052B0, D_000052B4, D_000052B8;

// a register of the sound chip, by its address from the chip's start
#define SPU2(offset) (*(volatile u16 *)(0xBF900000u + (offset)))

/** 0x00001E70@LIBSD.IRX: a moment's wait, four stores to a word of the stack */
void sd_pause(void) {
  volatile int word;
  word = 0;
  word = 0;
  word = 0;
  word = 0;
}

/** 0x000020D4@LIBSD.IRX: one step of the wait, 120 products kept on the stack */
void sd_wait_step(void) {
  volatile int product, count;
  product = 13;
  for (count = 0; count < 120; count++) product = product * 13;
}

/** 0x00002130@LIBSD.IRX: waits `steps` steps */
void sd_wait(int steps) {
  for (int i = 0; i < steps; i++) sd_wait_step();
}

/** 0x00001648@LIBSD.IRX: both cores' mixing switches and volumes as the library starts them, and with `keep` 0 their
 *  master and effect volumes off and core 0's and core 1's effect areas ending at 14 and 15 */
void sd_start_volumes(int keep) {
  SPU2(0x7C0) = 0xC032;
  if (keep == 0) {
    SPU2(0x19A) = 0xC000;
    SPU2(0x59A) = 0xC001;
  } else {
    SPU2(0x19A) = 0xC080;
    SPU2(0x59A) = 0xC081;
  }
  SPU2(0x188) = 0xFFFF;
  SPU2(0x18A) = 0xFF;
  SPU2(0x190) = 0xFFFF;
  SPU2(0x192) = 0xFF;
  SPU2(0x18C) = 0xFFFF;
  SPU2(0x18E) = 0xFF;
  SPU2(0x194) = 0xFFFF;
  SPU2(0x196) = 0xFF;
  SPU2(0x588) = 0xFFFF;
  SPU2(0x58A) = 0xFF;
  SPU2(0x590) = 0xFFFF;
  SPU2(0x592) = 0xFF;
  SPU2(0x58C) = 0xFFFF;
  SPU2(0x58E) = 0xFF;
  SPU2(0x594) = 0xFFFF;
  SPU2(0x596) = 0xFF;
  SPU2(0x198) = 0xFF0;
  SPU2(0x598) = 0xFFC;
  if (keep == 0) {
    SPU2(0x760) = 0;
    SPU2(0x762) = 0;
    SPU2(0x788) = 0;
    SPU2(0x78A) = 0;
    SPU2(0x764) = 0;
    SPU2(0x766) = 0;
    SPU2(0x78C) = 0;
    SPU2(0x78E) = 0;
    SPU2(0x33C) = 14;
    SPU2(0x73C) = 15;
  }
  SPU2(0x768) = 0;
  SPU2(0x76A) = 0;
  SPU2(0x790) = 0x7FFF;
  SPU2(0x792) = 0x7FFF;
  SPU2(0x76C) = 0;
  SPU2(0x76E) = 0;
  SPU2(0x794) = 0;
  SPU2(0x796) = 0;
}

/** 0x00004550@LIBSD.IRX: the library's word of transfers in progress, and each core's, cleared */
void sd_clear_transfers(void) {
  D_000052B8 = 0;
  D_000052B0 = 0;
  D_000052B4 = 0;
}

/** 0x00003E3C@LIBSD.IRX: a core's interrupt handler and what it's given set, and the handler it had given back */
u32 sd_set_handler(int core, u32 handler, u32 data) {
  volatile u32 kept;
  u32 was = D_000052C8[core];
  D_000052C8[core] = handler;
  D_000052DC[core * 2] = data;
  kept = data;
  return was;
}

/** 0x0000207C@LIBSD.IRX: a core's delay on the IOP's bus, its four bits from 24 cleared */
void sd_clear_delay(int core) {
  volatile u32 *delay = (volatile u32 *)(0xBF801014u + ((u32)core << 10));
  *delay = *delay & 0xF0FFFFFF;
}

/** 0x00003670@LIBSD.IRX: a parameter of a voice or a core set: which kind from the entry's bits 8 to 15, the core from
 *  bit 0, a voice from bits 1 to 5, and for a register of a voice's own a core 1,024 bytes along, or 40 for one of the
 *  registers bit 7 says are 40 bytes apart */
void sd_set_param(u32 entry, u32 value) {
  u32 core = entry & 1;
  u32 apart = (entry & 0x80) ? 40 : 1024;
  u32 at = D_00004930[(entry >> 8) & 0xFF] + core * apart + ((entry & 0x3E) << 3);
  *(volatile u16 *)at = (u16)value;
}
