// Slice s00c389f0 -- six unnamed Simulator/SP helpers reached from the tribe /
// UFO machinery.  Layouts recovered from the ctor/dtor pair (00c38c50 /
// 00c38c90) and from the field offsets each body touches.
//
//   00c389f0  float  UFOThing::FUN_00c389f0(float)  clamped accumulator
//   00c38b10  void   UFOThing::FUN_00c38b10()        release + refcount--
//   00c38b90  void   UFOThing::FUN_00c38b90()        release + refcount--
//   00c38c20  void   OffsetHolder::GetPos(Vec3*)     3-float copy
//   00c38c50  ctor   PaintSystemExt::PaintSystemExt()
//   00c38c90  dtor   PaintSystemExt::~PaintSystemExt()
//
// The ctor/dtor pair writes two different vptrs through the same slot: the
// class's own vtable (0x146bb78, 0x10 below cGameDataUFO) at the top and the
// base's (0x13eb394 == vtbl_Skinner::PaintSystem) at the very end, with no
// base-dtor call in between -- the classic MSVC derived-destructor shape for a
// polymorphic class whose base destructor is trivial and inlined.
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// ===========================================================================
// objects returned by the hash lookups (00c38b10 / 00c38b90)
// ===========================================================================
struct RefObj {                            // looked-up object: vtable + counters
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool vf2c();                   // +0x2c (slot 11, vptr at +0)
    uint8_t  pad04[0x224 - 0x04];          // +0x04 .. +0x223
    uint32_t m224;                         // +0x224
    uint32_t m228;                         // +0x228
    uint8_t  pad22c[0x638 - 0x22c];        // +0x22c .. +0x637
    uint32_t m638;                         // +0x638
    uint32_t m63c;                         // +0x63c
};

struct LookupObj {                         // smart pointer at UFOThing+0x7a8/0x7ac
    PV(0)
    virtual void    Release();             // +0x04 (slot 1)
    virtual void    d2();                  // +0x08 (slot 2)
    virtual RefObj* vf0c(uint32_t hash);   // +0x0c (slot 3)
};

// ===========================================================================
// the big receiver shared by 00c389f0 / 00c38b10 / 00c38b90
// ===========================================================================
struct UFOThing {
    void*      vft;                        // +0x000
    uint8_t    pad04[0x710];               // +0x004 .. +0x713
    uint32_t   m714;                       // +0x714
    uint8_t    pad718[0x90];               // +0x718 .. +0x7a7
    LookupObj* mp7a8;                      // +0x7a8
    LookupObj* mp7ac;                      // +0x7ac
    uint8_t    pad7b0[0x44];               // +0x7b0 .. +0x7f3
    float      m7f4;                       // +0x7f4
    float      m7f8;                       // +0x7f8

    float FUN_00c389f0(float d);           // 0x00c389f0
    void  FUN_00c38b10();                  // 0x00c38b10
    void  FUN_00c38b90();                  // 0x00c38b90
};

// ===========================================================================
// helpers used by 00c389f0
// ===========================================================================
struct UFOObj     { void FUN_00ffc020(); };                 // 0x00ffc020
struct MissionMgr { bool IsRunning(); };                    // 0x00feba90
struct TerrainSphere {
    bool FUN_00c772c0(uint32_t hash);      // 0x00c772c0
    void FUN_00c77bf0(uint32_t hash);      // 0x00c77bf0
};
struct cTerrainEditor {
    TerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
struct MsgObj     { void FUN_0106dcd0(); };                 // 0x0106dcd0

UFOObj*         GetUFOSimulator();          // 0x00ffbe50
MissionMgr*     GetMissionManager();        // 0x00feb9f0
cTerrainEditor* NounManager();              // 0x00b3d300
MsgObj*         FUN_010666a0(uint32_t);     // 0x010666a0

// ===========================================================================
// the class whose ctor / dtor pair is 00c38c50 / 00c38c90
// ===========================================================================
struct MsgHandler5 { uint32_t a, b, c, d, e; };

void EA_RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);  // 0x00571db0

namespace Skinner {
struct PaintSystem {                       // base, vtbl 0x13eb394
    virtual ~PaintSystem() {}              // trivial: contributes only a vptr
};
}

struct PaintSystemExt : Skinner::PaintSystem {   // own vtbl 0x146bb78
    LookupObj* mp04;                       // +0x004
    uint8_t    pad08[0x18];                // +0x008 .. +0x01f
    float      m20;                        // +0x020
    uint8_t    pad24[0x184];               // +0x024 .. +0x1a7
    MsgHandler5 msg;                       // +0x1a8 .. +0x1bb

    PaintSystemExt();                      // 0x00c38c50
    virtual ~PaintSystemExt();             // 0x00c38c90
};

// ===========================================================================
// the negative-offset getter 00c38c20: the three floats live 0x4d0 bytes below
// the receiver, so `this` is the high end of the enclosing object
// ===========================================================================
struct OffsetHolder {
    void GetPos(Vec3* out);                // 0x00c38c20
};

// ===========================================================================
// definitions
// ===========================================================================

// @ 0x00c389f0
float UFOThing::FUN_00c389f0(float d)
{
    if (d < 0.0f) {
        if (m714 == 0)
            GetUFOSimulator()->FUN_00ffc020();
    }
    if (m714 == 0 && d < 0.0f) {
        if (!GetMissionManager()->IsRunning())
            return m7f4;
    }

    float hi = m7f8;
    float v  = m7f4 + d;
    float lo = 0.0f;
    v = (v < lo) ? lo : v;
    v = (hi < v) ? hi : v;
    m7f4 = v;

    if (m714 == 0 && v <= m7f8 * 0.2f) {
        TerrainSphere* t = NounManager()->GetCurrentTerrainSphere();
        if (t != 0 && !t->FUN_00c772c0(0x66269e7)) {
            t->FUN_00c77bf0(0x66269e7);
            FUN_010666a0(0x73213921)->FUN_0106dcd0();
        }
    }
    return m7f4;
}

// @ 0x00c38b10
void UFOThing::FUN_00c38b10()
{
    RefObj* x = mp7a8 ? mp7a8->vf0c(0xee9b2232) : 0;
    RefObj* y = mp7a8 ? mp7a8->vf0c(0x4e3faaf) : 0;
    if (x != 0) {
        x->m224--;
    } else {
        if (y != 0)
            y->m63c--;
    }
    if (mp7a8 != 0) {
        LookupObj* t = mp7a8;
        mp7a8 = 0;
        t->Release();
    }
}

// @ 0x00c38b90
void UFOThing::FUN_00c38b90()
{
    RefObj* x = mp7ac ? mp7ac->vf0c(0xee9b2232) : 0;
    RefObj* y = mp7ac ? mp7ac->vf0c(0x4e3faaf) : 0;
    if (x != 0 && !x->vf2c()) {
        x->m228--;
    } else if (y != 0 && !y->vf2c()) {
        y->m638--;
    }
    if (mp7ac != 0) {
        LookupObj* t = mp7ac;
        mp7ac = 0;
        t->Release();
    }
}

// @ 0x00c38c20
void OffsetHolder::GetPos(Vec3* out)
{
    Vec3* p = (Vec3*)((float*)this - 0x134);   // 0x134 floats == 0x4d0 bytes
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
}

// @ 0x00c38c50
PaintSystemExt::PaintSystemExt()
{
    mp04 = 0;
    m20  = 1.0f;
    msg.a = 0;
    msg.b = 0;
    msg.c = 0;
    msg.d = 0;
    msg.e = 0;
}

// @ 0x00c38c90
PaintSystemExt::~PaintSystemExt()
{
    if (mp04 != 0) {
        LookupObj* t = mp04;
        mp04 = 0;
        t->Release();
    }
    if (msg.a != 0) {
        uint32_t a = msg.a;
        uint32_t b = msg.b;
        uint32_t c = msg.c;
        uint32_t d = msg.d;
        uint32_t e = msg.e;
        msg.a = 0;
        EA_RemoveHandler(a, b, c, d, e);
    }
    if (mp04 != 0)
        mp04->Release();
}