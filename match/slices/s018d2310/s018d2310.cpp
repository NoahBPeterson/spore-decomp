// Slice s018d2310: EA's SSL library license check (SL_* interface).
//
// SLnext() is the SL_ macro's "call $+5" stub: the call pushes the return
// address, and the body at 0x018d2315 reads it as the call code for
// SLgetlicinfo().  The body hands its result back by writing it over that
// pushed return address, so it returns straight to SLnext's caller and the
// stub itself is just a call.  cl at /O2 would make `return f();` a tail
// jump, hence the /Od scope, which leaves the frame-less `call; ret`.
//
// The body (0x018d2315) is a save-all-registers shim around SLgetlicinfo that
// reads the stack with absolute offsets, which no C++ declaration reproduces:
// it is left out until it can be written without transcription.

int __stdcall SLnext_body(void);

// @ 0x018d2310
#pragma optimize("", off)
int __stdcall SLnext(void)
{
    return SLnext_body();
}
#pragma optimize("", on)
