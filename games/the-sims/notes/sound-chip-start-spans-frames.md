# The sound chip's start runs on the IOP for longer than a frame, so frame 19 holds only its first writes.

About: Switching on and the logos; logos; 0033A8E8

Proof: #1838; logos

With the Dreamport giving the GS and the sound chip nothing, frames 0 to 18 of logos match. At frame 19 the original's sound list has 78 things where the Dreamport's 17 are only blocks of samples. The start comes from the EE's 0x0033A8E8, which binds the sound driver's server 0x80000701, whose call 0x8000 reaches the start of the module LIBSD.IRX, at 0x456C in it. That writes the chip through its functions at 0x15F8, 0x1E8C, 0x42E4, 0x4014 and 0x1648 in turn, with waits of 120 loops at 0x20D4 between, and the voice loop at 0x4014 alone writes far more than 61 registers. So the start goes on past frame 19 as the IOP's slices of 600 ticks pass, and the kit, which runs a twin's IOP code all at once at the end of a slice, can't end frame 19 where the original does until it lets an IOP twin's time pass.
