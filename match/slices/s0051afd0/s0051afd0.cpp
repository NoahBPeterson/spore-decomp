// Slice 3: nSPSkinner paint state machine (cPaintRenderer job), 0x0051afd0.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
//
// PARTIAL: 0051afd0 is a 5268-byte switch state machine over [this+0x33c] (cases 0..13, jump table at
// 0x51c42c) that drives the whole skin-paint pipeline. The skeleton below records the entry shape and
// the state advance; the individual case bodies are not reconstructed.
#include "types.h"

int GetPaintSystem();   // 0x00401080

struct PaintMachine {
    void FUN_0051afd0();
};

// @ 0x0051afd0 FUN_0051afd0
void PaintMachine::FUN_0051afd0()
{
    int ps = GetPaintSystem();
    (void)ps;
    int* tick = (int*)((char*)this + 0x344);
    *tick = *tick + 1;
    int state = *(int*)((char*)this + 0x33c);
    if ((unsigned)state > 0xd)
        return;
    switch (state) {
    default:
        break;
    }
}
