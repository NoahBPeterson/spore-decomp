#include "game/types.h"

struct Inner_0069dc60 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual bool Eval(void* a, void* b); // +0x38
};

struct Sub4_0069dc60 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual Inner_0069dc60* Get(); // +0x18
};

struct Cond_0069dc60 {
    uint32_t mUnk00;      // +0x00
    Sub4_0069dc60* mpSub; // +0x04
    uint32_t mUnk08;      // +0x08
    uint8_t mFlag0c;      // +0x0c

    // @ 0x0069dc60
    int Check(void* a, void* b);
};

// @ 0x0069dc60
int Cond_0069dc60::Check(void* a, void* b)
{
    int r = mFlag0c && mpSub->Get()->Eval(a, b);
    mFlag0c = r;
    return r;
}
