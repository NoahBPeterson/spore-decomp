// Slice s00a6f110 (gold7): cEmitter::Forward (0x00a6fee0).
// Forward temporarily raises bits 1|2 of the emitter state word and hands the
// step over to the virtual hook at vtable +0x54, then restores the state.
#include "types.h"

typedef unsigned int u32;

struct cEmitter {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual void ForwardStep(float a, float b, int c);   // vtable +0x54

    char pad[0x10 - 4];
    u32  mState;                                         // +0x10

    void Forward(float a, float b, int c);
};

// @ 0x00a6fee0
void cEmitter::Forward(float a, float b, int c)
{
    u32 saved = mState;
    mState = saved | 6;
    ForwardStep(a, b, c);
    mState = saved;
}
