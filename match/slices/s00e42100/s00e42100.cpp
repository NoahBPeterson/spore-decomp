// Slice s00e42100 -- editor range panel update.
//
// The object is a UI panel that owns several range/position providers (all of them the same
// abstract interface: v38 returns four floats, v60 writes a four-float buffer, v6C consumes a
// four-float buffer and v7C takes (mode, flag)).  The panel recomputes its displayed range from
// the current selection bounds, the current target span and an optional extra span looked up in
// the panel's key map, pushes the result into its target provider, notifies its slider and then
// stores the delta between the target span and the selection span.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)
#pragma warning(disable : 4244)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned __int64 u64;

// ---------------------------------------------------------------------------------------------
// the four-float provider interface shared by every child of the panel
// ---------------------------------------------------------------------------------------------
class IRangeObj {
public:
    virtual void   r00(); virtual void r04(); virtual void r08(); virtual void r0C();
    virtual void   r10(); virtual void r14(); virtual void r18(); virtual void r1C();
    virtual void   r20(); virtual void r24(); virtual void r28(); virtual void r2C();
    virtual void   r30(); virtual void r34(); virtual float* r38();
    virtual void   r3C(); virtual void r40(); virtual void r44(); virtual void r48(); virtual void r4C();
    virtual void   r50(); virtual void r54(); virtual void r58(); virtual void r5C();
    virtual void   r60(void* buf);
    virtual void   r64(); virtual void r68();
    virtual void   r6C(void* buf);
    virtual void   r70(); virtual void r74(); virtual void r78();
    virtual void   r7C(u32 mode, bool flag);
};

// key-map member of the panel (FUN_00e3ec20 is its thiscall finder)
class CKeyMap {
public:
    IRangeObj** Find(u32* key);     // 0x00e3ec20
    u32         m00;                // +0x0
};

// small holder reached through panel +0x184: {ptr} -> {..., +0x1c provider}
struct Sub184 {
    u8          pad00[0x1c];
    IRangeObj*  m1c;                // +0x1c
    u8          pad20[0xe4 - 0x20];
    u32         mE4;                // +0xe4
    u8          padE8[0xf0 - 0xe8];
    u32         mF0;                // +0xf0
};

struct Holder184 {
    Sub184* m00;                    // +0x0
};

// ---------------------------------------------------------------------------------------------
// the panel
// ---------------------------------------------------------------------------------------------
class cRangePanel {
public:
    void Update();                                  // 0x00e42100

    void Refresh();                                 // 0x00e3f970
    u64  Step(void* p);                             // 0x00e36ff0
    void Apply(u32 lo, u32 hi);                     // 0x00e372b0

    u8          pad000[0x3c];
    IRangeObj*  mpSource3c;                         // +0x3c
    IRangeObj*  mpTarget40;                         // +0x40
    u8          pad044[0x58 - 0x44];
    IRangeObj*  mpSlider58;                         // +0x58
    u8          pad05c[0x60 - 0x5c];
    IRangeObj*  mpRange60;                          // +0x60
    u8          pad064[0xa8 - 0x64];
    void*       mpStepArg;                          // +0xa8
    u8          pad0ac[0xc8 - 0xac];
    CKeyMap     mKeyMap;                            // +0xc8
    u8          pad0cc[0x184 - 0xcc];
    Holder184*  mpHolder184;                        // +0x184
    Sub184**    mppOwner188;                        // +0x188
    u8          pad18c[0x270 - 0x18c];
    float       m270;                               // +0x270
    float       m274;                               // +0x274
    float       m278;                               // +0x278
};

// ---------------------------------------------------------------------------------------------
// retail globals
// ---------------------------------------------------------------------------------------------
extern u8*  GetCurrentGameMode();       // 0x00b5b800
extern u8   g_1654c05;                  // 0x01654c05  "no game mode" sentinel

// @ 0x00e42100 cRangePanel::Update
void cRangePanel::Update() {
    if (mpTarget40 == 0 || mpSource3c == 0)
        return;

    u32   key;
    float fMin;
    float fSpan;
    float fExtra;
    float fSlot;
    float fRange[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float msg[4];

    mpTarget40->r60(fRange);

    Refresh();

    Sub184* owner = mpHolder184->m00;
    fMin = 0.0f;
    if (owner != 0) {
        IRangeObj* p = owner->m1c;
        if (p != 0) {
            fRange[0] = p->r38()[0];
            fRange[0] = (fRange[0] < fMin) ? fRange[0] : fMin;
            fMin = fRange[0];
        }
    }

    float* t = mpTarget40->r38();
    fSpan = t[2] - t[0];

    Sub184* owner2 = mppOwner188[-1];
    if (owner2 != 0) {
        IRangeObj* p = owner2->m1c;
        if (p != 0) {
            fRange[0] = p->r38()[2];
            fRange[0] = (fRange[0] > fSpan) ? fRange[0] : fSpan;
            fSpan = fRange[0];
        }
    }

    fExtra = 0.0f;
    if (owner2 != 0 && owner2->mF0 == 0 && owner2->mE4 != 0x2db6dad3 && mpRange60 != 0) {
        key = owner2->mE4;
        fSlot = 0.0f;
        IRangeObj** slot = mKeyMap.Find(&key);
        if (*slot != 0)
            fSlot = (*slot)->r38()[2];
        float* q = mpRange60->r38();
        if (fSlot < q[2]) {
            if (fSlot > q[0])
                fExtra = fSlot - q[0];
        } else {
            fExtra = q[2] - q[0];
        }
    }

    float* t2 = mpTarget40->r38();
    msg[0] = t2[0];
    msg[1] = t2[1];
    msg[2] = t2[2];
    msg[3] = t2[3];
    msg[0] = fMin;
    msg[2] = (fSpan - fMin) + fExtra;
    mpTarget40->r6C(msg);

    float* sel = mpSource3c->r38();
    if (mpSlider58 != 0) {
        bool flag = (msg[2] - msg[0]) > (sel[2] - sel[0]) && GetCurrentGameMode() != &g_1654c05;
        mpSlider58->r7C(1, flag);
        if (mpStepArg != 0) {
            u64 r = Step(mpStepArg);
            Apply((u32)r, (u32)(r >> 32));
        }
    }

    float* t3 = mpTarget40->r38();
    float d = (t3[2] - t3[0]) - (sel[2] - sel[0]);
    m270 = d;
    m278 = d;
}
