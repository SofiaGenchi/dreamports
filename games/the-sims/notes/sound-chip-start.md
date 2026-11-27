# The sound chip's first writes, at frame 19, come from the start of LIBSD.IRX, called through the sound driver.

About: Switching on and the logos; 0033A8E8

Proof: #1838; #1825

Frames 0 to 18 of a recording that switches on and presses nothing give the sound chip nothing, and frame 19 of the original's sound list has 78 things, 17 of them blocks of samples. The EE's 0x0033A8E8 binds the sound driver's server 0x80000701, and its call 0x8000 reaches the start of the module LIBSD.IRX, at 0x456C in it, which writes the chip through its functions at 0x15F8, 0x1E8C, 0x42E4, 0x4014 and 0x1648 in turn, with waits of 120 loops at 0x20D4 between. The voice loop at 0x4014 alone writes far more than 61 registers, so the start goes on past frame 19 as the IOP's time passes. The functions at 0x1E8C and 0x4014 each wait while the chip's status at 0x344 says it's busy, so the function check, whose memory stays as each call starts, can't reach those waits' other ways.
