// slice s005a9d40 — manipulation cell pinning / manipulation object helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#define PV(n) virtual void pv##n();

class cObj {
public:
    virtual void v0();
    virtual void v1();   // +0x04
    virtual void v2();   // +0x08
};

class cSetter {
public:
    char  pad0[0x1c];
    cObj* m1c;   // +0x1c
    int   m20;   // +0x20
    int   m24;   // +0x24
    int   m28;   // +0x28
    void Set(cObj** pp, int a, int b, int c);
};

// @ 0x005aa3d0
void cSetter::Set(cObj** pp, int a, int b, int c) {
    cObj* p = *pp;
    cObj* old = m1c;
    if (p != old) {
        if (p)
            p->v1();
        m1c = p;
        if (old)
            old->v2();
    }
    m20 = a;
    m24 = b;
    m28 = c;
}

// ---- large object with a Vector3 at +0x138 ---------------------------------
class cBigThing {
public:
    char pad0[0x138];
    uint32_t mX;   // +0x138
    uint32_t mY;   // +0x13c
    uint32_t mZ;   // +0x140
    void SetVec(uint32_t x, uint32_t y, uint32_t z);
};

// @ 0x005aa580
void cBigThing::SetVec(uint32_t x, uint32_t y, uint32_t z) {
    mX = x;
    mY = y;
    mZ = z;
}
void (cBigThing::*g_setVecPtr)(uint32_t, uint32_t, uint32_t) = &cBigThing::SetVec;

// ---- skin manager tail-call -------------------------------------------------
class cSkinManager {
public:
    void GetSkin(int index);
};
class cPinning {
public:
    char pad0[0xe0];
    cSkinManager* mSkinManager;   // +0xe0
    void Update(int deltaTime);
};

// @ 0x005aa5b0
void cPinning::Update(int) {
    mSkinManager->GetSkin(0);
}

// ---- remaining functions in the slice (abridged) ---------------------------
// @ 0x005a9d40
void FUN_005a9d40() {}

// @ 0x005aa420
void FUN_005aa420() {}

// @ 0x005aa490
void FUN_005aa490() {}

// @ 0x005aa530
void FUN_005aa530() {}

// @ 0x005aa5d0
void FUN_005aa5d0() {}

// @ 0x005aa740
void FUN_005aa740() {}

// @ 0x005aa7a0
void FUN_005aa7a0() {}

// @ 0x005aa9c0
void FUN_005aa9c0() {}

// @ 0x005aab00
void FUN_005aab00() {}

// @ 0x005aac30
void FUN_005aac30() {}
