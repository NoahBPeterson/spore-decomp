// Slice s00c9d230 -- Simulator/SP::cTribeTool: the tribe "tool" placement object.
//
// Layout recovered from the constructor / destructor:
//   +0x000 cGameData base      (two vtable pointers at +0x00 and +0x04, +0x2c owned ptr)
//   +0x034 cSpatialObject base (m90/m94/m98 = abs 0xc4/0xc8/0xcc, m0a4/m0a8 = abs 0xd8/0xdc,
//                               timer = abs 0x100)
//   +0x108 cInteractionTarget base
//   +0x120 cCombatant base, which reaches out to abs 0xc6c: it holds
//             +0x0a4 def object (abs 0x1c4), +0x0a8 def id (abs 0x1c8),
//             +0x0c0 nested vtable (abs 0x1e0), +0x0c8 nested vtable (abs 0x1e8),
//             +0x0cc float (abs 0x1ec), +0x0d0/+0x0d4 (abs 0x1f0/0x1f4),
//             +0x0d8 owned object (abs 0x1f8), +0x0dc int (abs 0x1fc),
//             +0x0e0/+0x100 timers (abs 0x200/0x220),
//             +0x120/+0x124/+0x128 (abs 0x240/0x244/0x248),
//             +0x0b4c anim owner (abs 0xc6c)
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// ===========================================================================
// dispatch views -- each begins with its own vtable pointer at offset 0
// ===========================================================================

struct DefObj {                        // object stored at combatant +0xa4 / +0xd8
    virtual void vf0();                // +0x00 (AddRef)
    virtual void Release();            // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual void* vf4c();              // +0x4c  (no-argument form, used by Init)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    virtual void* vf90();              // +0x90
    void FUN_00c987b0(uint32_t v);     // 0x00c987b0
};
struct DefObj3 {                       // same slot layout, three-argument vf4c
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual void* vf4c(int a, uint32_t b, float c);
};

struct StimObj {                       // object with slots +0x08 / +0x0c (FUN_00c9d670 param 5)
    PV(0) PV(1)
    virtual void* vf08();              // +0x08
    virtual void* vf0c(void* a);       // +0x0c
};

struct AnimCtl {
    void FUN_00bc97f0(int a, int b, float c, int d);   // 0x00bc97f0, ret 0x10
};
struct AnimOwner {
    uint8_t  pad[8];
    AnimCtl  mCtl;                     // +0x08
};

struct SubStream {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void* vf18();              // +0x18
};
struct Stream {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual SubStream* vf20();                          // +0x20
    PV(9)
    virtual bool vf28(uint32_t hash, void* p, int n);   // +0x28
    virtual bool vf2c(void* p);                         // +0x2c
};
void EA_WriteUint32(void* stream, const uint32_t* p, int a, int b);   // 0x0093aa70
void EA_ReadInt32(void* stream, uint32_t* p, int a, int b);           // 0x0093a780

struct cVarListSerializer {
    cVarListSerializer(void* owner, void* vtbl, uint32_t hash);       // 0x00692f90
    bool Serialize(Stream* s);                                        // 0x00692900 (writer variant)
    bool SerializeRead(Stream* s);                                    // 0x00693e10 (reader variant)
    uint8_t pad[0xa14];
};

uint32_t GetCurrentGameMode();                     // 0x00b5b800
uint32_t RelationshipManager();                    // 0x00b3d2c0

// ===========================================================================
// planet-side objects reached from the tool
// ===========================================================================
struct Worm {                                      // object at cPlanetModel +0x24
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    virtual void* vf54(void* a, void* b);          // +0x54
    virtual void  vf58(void* a, int b);            // +0x58
};
struct cPlanetModel {
    uint8_t pad04[0x24];                           // +0x00 .. +0x23
    Worm*   mp24;                                  // +0x24
    void* BuildSurfaceOrientation2(void* a, void* b);   // 0x00b7f250
};
struct PmBuf {                                     // the 16-byte scratch handed to PlanetModel
    cPlanetModel* Init(void* v);                   // 0x00b3d350
};
cPlanetModel* PlanetModel();                       // 0x00b3d350 (singleton accessor)

struct LocExt {                                    // box returned by the spatial +0xac slot
    uint8_t pad00[0x90];
    void*   mp90;                                  // +0x90
};

// ===========================================================================
// the polymorphic components embedded inside cTribeTool
// ===========================================================================

struct cSPTimer {                                  // 8 bytes (lives at spatial +0xcc / abs 0x100)
    uint8_t pad[8];
    void Stop();                                   // 0x00bc3110
    void Restart();                                // 0x00bc3130
};
struct cGonzagoTimer {                             // 0x20 bytes
    uint8_t pad[0x20];
    void Ctor();                                   // 0x00b63890
    void Dtor();                                   // 0x00b638b0
    void Restart();                                // 0x00bc3130
};

struct cGameData {
    void*    vft0;                                 // +0x00
    void*    vft1;                                 // +0x04
    uint8_t  pad08[0x24];
    void*    mp2c;                                 // +0x2c
    uint8_t  pad30[0x04];
    void Ctor();                                   // 0x00b18660
    void Dtor();                                   // 0x00b184c0
    bool Write(Stream* s);                         // 0x00b18590
    bool Read(Stream* s);                          // 0x00b18600
    void IsDestroyed(uint32_t p);                  // 0x00bfd0d0
};

struct cSpatialObject {
    void*    vft;                                  // +0x00
    uint8_t  pad04[0x8c];
    uint32_t m90;                                  // +0x90 (abs 0xc4)
    uint32_t m94;                                  // +0x94 (abs 0xc8)
    uint32_t m98;                                  // +0x98 (abs 0xcc)
    uint8_t  pad9c[0x08];
    uint32_t m0a4;                                 // +0xa4 (abs 0xd8)
    uint32_t m0a8;                                 // +0xa8 (abs 0xdc)
    uint8_t  pad0ac[0x20];
    cSPTimer timer;                                // +0xcc (abs 0x100)
    void Ctor();                                   // 0x00c89630
    void SetLocalExtents(uint32_t a, float b);     // 0x00c89160, ret 8
    bool Write(Stream* s);                         // 0x00c88a90
    bool Read(Stream* s);                          // 0x00c88b00
    void FUN_00c8a420();                           // 0x00c8a420
    void FUN_00c8b2e0();                           // 0x00c8b2e0
};
struct cSpatialObjectV {                           // no-argument +0x2c form
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void* vf2c();                          // +0x2c
    virtual void* vf30();                          // +0x30
    PV(13) PV(14)
    virtual void  vf3c(void* v);                   // +0x3c
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    virtual LocExt* vfac();                        // +0xac
};
struct cSpatialObjectV2 {                          // one-argument +0x2c / +0x3c form
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void* vf2c(void* p);                   // +0x2c
    PV(12) PV(13) PV(14)
    virtual void  vf3c(void* v);                   // +0x3c
};

struct cInteractionTarget {
    void*    vft;                                  // +0x00
    uint8_t  pad04[0x14];
    void Ctor();                                   // 0x00ac03d0
    void FUN_00ac0450();                           // 0x00ac0450
    void FUN_00ac0520();                           // 0x00ac0520
};

struct cCombatant {
    void*    vft;                                  // +0x000
    uint8_t  pad04[0x34];
    float    m38;                                  // +0x038
    uint8_t  pad3c[0x68];
    DefObj*  mDefObj;                              // +0x0a4 (abs 0x1c4)
    uint32_t mDefID;                               // +0x0a8 (abs 0x1c8)
    uint8_t  padac[0x14];
    void*    vftC0;                                // +0x0c0 (abs 0x1e0)
    uint8_t  padc4[0x04];
    void*    vftC8;                                // +0x0c8 (abs 0x1e8)
    float    mCc;                                  // +0x0cc (abs 0x1ec)
    uint32_t mD0;                                  // +0x0d0 (abs 0x1f0)
    uint32_t mD4;                                  // +0x0d4 (abs 0x1f4)
    DefObj*  mpOwner;                              // +0x0d8 (abs 0x1f8)
    uint32_t mDc;                                  // +0x0dc (abs 0x1fc)
    cGonzagoTimer timer1;                          // +0x0e0 (abs 0x200)
    cGonzagoTimer timer2;                          // +0x100 (abs 0x220)
    uint32_t m120;                                 // +0x120 (abs 0x240)
    uint32_t m124;                                 // +0x124 (abs 0x244)
    uint32_t m128;                                 // +0x128 (abs 0x248)
    uint8_t  pad12c[0xa20];
    AnimOwner* mpAnim;                             // +0xb4c (abs 0xc6c)
    void Ctor();                                   // 0x00bfd4e0
    bool Write(Stream* s);                         // 0x00bfc4a0
    bool Read(Stream* s);                          // 0x00bfc540
    void FUN_00bfc720();                           // 0x00bfc720
    void FUN_00bfcd00();                           // 0x00bfcd00
    void TakeHit(float dmg, int a, uint32_t b, uint32_t c, void* d);   // 0x00bfcdd0, ret 0x14
};

struct cTribeToolV {                               // the tool's own virtual slots
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void* vf2c();                          // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void  vf48(void* a);                   // +0x48
    PV(19) PV(20) PV(21) PV(22)
    virtual void* vf5c(void* a);                   // +0x5c
};

struct Found {                                     // object returned by FUN_00b3d240
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23)
    virtual void* vf60(uint32_t a, void* b, void* c);   // +0x60
};
Found* FUN_00b3d240();                             // 0x00b3d240

// ===========================================================================
// the tool
// ===========================================================================
struct cTribeTool {
    cGameData          gameData;                   // +0x000
    cSpatialObject     spatial;                    // +0x034
    cInteractionTarget interact;                   // +0x108
    cCombatant         combatant;                  // +0x120

    cTribeTool();
    ~cTribeTool();

    void Init(DefObj* p);
    void FUN_00c9d4d0();
    void SetLocalExtents(uint32_t a, float b);
    void FUN_00c9d5b0(uint32_t p);
    void FUN_00c9d670(float dmg, int a, uint32_t b, uint32_t c, void* d);
    bool GetIsPlayerOwned();
    void GetCastID(int p);
    bool Write(Stream* s);
    bool Read(Stream* s);
    void FUN_00c9dd50();

    void FUN_43c0(int p);                          // 0x00c88670
    void SetLocalExtentsRaw(uint32_t a, float b);  // same body as cSpatialObject::SetLocalExtents
};

struct GameNounManager { uint32_t GetPlayerTribe(); };   // 0x00bfc5f0
GameNounManager* NounManager();                          // 0x00b3d300

// ---------------------------------------------------------------------------
// @ 0x00c9d230
cTribeTool::cTribeTool()
{
    gameData.Ctor();
    spatial.Ctor();
    interact.Ctor();
    combatant.Ctor();

    combatant.vftC8 = (void*)0x1466c14;
    spatial.vft     = (void*)0x14747c0;
    gameData.vft0   = (void*)0x1474758;
    gameData.vft1   = (void*)0x1474744;
    interact.vft    = (void*)0x1474728;
    combatant.vft   = (void*)0x14746c0;
    combatant.vftC8 = (void*)0x1474698;

    combatant.mCc   = 0.0f;
    combatant.mD0   = 0;
    combatant.mD4   = 0;
    combatant.mpOwner = 0;
    combatant.mDc   = 0;

    combatant.timer1.Ctor();
    combatant.timer2.Ctor();

    combatant.m120  = 0;
    combatant.m124  = 0;
    combatant.m128  = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00c9d3b0
cTribeTool::~cTribeTool()
{
    gameData.vft0   = (void*)0x1474758;
    gameData.vft1   = (void*)0x1474744;
    spatial.vft     = (void*)0x14747c0;
    interact.vft    = (void*)0x1474728;
    combatant.vft   = (void*)0x14746c0;
    combatant.vftC8 = (void*)0x1474698;

    combatant.timer2.Dtor();
    combatant.timer1.Dtor();

    if (combatant.mpOwner)
        combatant.mpOwner->Release();

    combatant.vftC8 = (void*)0x1466c14;
    combatant.FUN_00bfcd00();
    interact.FUN_00ac0520();
    spatial.FUN_00c8a420();
    gameData.Dtor();
}

// ---------------------------------------------------------------------------
// @ 0x00c9d440
void cTribeTool::Init(DefObj* p)
{
    DefObj* old = combatant.mpOwner;
    if (p != old) {
        if (p)
            p->vf0();
        combatant.mpOwner = p;
        if (old)
            old->Release();
    }

    uint8_t      buf[16];
    void*        v  = ((cSpatialObjectV2*)&spatial)->vf2c((void*)0x1699a84);
    cPlanetModel* pm = ((PmBuf*)&buf)->Init(v);
    void*        r  = pm->BuildSurfaceOrientation2((void*)&buf, v);
    ((cSpatialObjectV2*)&spatial)->vf3c(r);

    if (combatant.mpOwner) {
        void* x = combatant.mpOwner->vf4c();
        ((cTribeToolV*)this)->vf48(x);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00c9d4d0
void cTribeTool::FUN_00c9d4d0()
{
    if (combatant.mpOwner) {
        DefObj* t = combatant.mpOwner;
        combatant.mpOwner = 0;
        t->Release();
    }

    if (combatant.m128) {
        Worm* w = 0;
        if (PlanetModel())
            w = PlanetModel()->mp24;
        if (w && combatant.m128) {
            w->vf58((void*)combatant.m128, 1);
            combatant.m128 = 0;
        }
    }

    combatant.FUN_00bfc720();
    interact.FUN_00ac0450();

    if (gameData.mp2c) {
        void* t = gameData.mp2c;
        gameData.mp2c = 0;
        ((DefObj*)t)->Release();
    }

    spatial.FUN_00c8b2e0();
}

// ---------------------------------------------------------------------------
// @ 0x00c9d570
void cTribeTool::SetLocalExtents(uint32_t a, float b)
{
    SetLocalExtentsRaw(a, b);
    if (combatant.mDefObj)
        combatant.mDefObj->FUN_00c987b0(combatant.mDefID);
}

// ---------------------------------------------------------------------------
// @ 0x00c9d5b0
void cTribeTool::FUN_00c9d5b0(uint32_t p)
{
    gameData.IsDestroyed(p);
    ((cSPTimer*)&combatant.mCc)->Stop();

    int st = (int)combatant.mDefID;
    uint32_t tag;
    if (st >= 4 && (st <= 6 || st == 9))
        tag = 0x498ef2b;
    else
        tag = 0x498ef2a;

    uint8_t here[12];
    Found*  ebx = FUN_00b3d240();
    void*   r   = ((cTribeToolV*)this)->vf5c(here);
    void*   pos = ((cTribeToolV*)this)->vf2c();
    ebx->vf60(tag, pos, r);
}

// ---------------------------------------------------------------------------
// @ 0x00c9d670
void cTribeTool::FUN_00c9d670(float dmg, int a, uint32_t b, uint32_t c, void* d)
{
    if (combatant.mDc == 0xa)
        return;

    bool bl = combatant.m38 > *(float*)0x14745dc;

    combatant.TakeHit(dmg, a, b, c, d);

    if (GetCurrentGameMode() != 0x1654c02)
        return;
    if (!combatant.mpOwner)
        return;

    if (combatant.m38 > 0.0f) {
        if (a != -1) {
            ((DefObj3*)combatant.mpOwner)->vf4c(a, 0x530cf04, 1.0f);
        }
        if (!d)
            return;

        StimObj* so = (StimObj*)d;
        void*    ebx = so->vf08();
        void*    ea  = so->vf0c((void*)&combatant);
        (void)ea;
        (void)ebx;
    } else {
        if (!bl)
            return;
        if (a != -1) {
            ((DefObj3*)combatant.mpOwner)->vf4c(a, 0x530cf05, 1.0f);
        }

        combatant.timer2.Restart();

        long* vec = (long*)combatant.mpOwner->vf90();
        long* beg = (long*)*vec;
        long* end = (long*)*(vec + 1);
        for (long* it = beg; it != end; it += 1) {
            void* cit = (void*)*it;
            (void)cit;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00c9d9c0
bool cTribeTool::GetIsPlayerOwned()
{
    uint32_t owner = (uint32_t)combatant.mDefObj;
    return NounManager()->GetPlayerTribe() == owner;
}

// ---------------------------------------------------------------------------
// @ 0x00c9d9f0
void cTribeTool::GetCastID(int p)
{
    FUN_43c0(p);
    if (combatant.mDefObj)
        combatant.mDefObj->FUN_00c987b0(combatant.mDefID);
}

// ---------------------------------------------------------------------------
// @ 0x00c9da20
bool cTribeTool::Write(Stream* s)
{
    uint32_t tmp = 0x116d858;
    EA_WriteUint32(s->vf20()->vf18(), &tmp, 1, 0);

    bool ok;
    if (gameData.Write(s) && spatial.Write(s) && combatant.Write(s)) {
        if (s->vf2c(combatant.mpOwner))
            ok = true;
        else
            ok = false;
    }
    else
        ok = false;

    tmp = spatial.m98;
    EA_WriteUint32(s->vf20()->vf18(), &tmp, 1, 0);
    tmp = spatial.m90;
    EA_WriteUint32(s->vf20()->vf18(), &tmp, 1, 0);
    tmp = spatial.m94;
    EA_WriteUint32(s->vf20()->vf18(), &tmp, 1, 0);

    cVarListSerializer ser(this, (void*)0x157c5d0, 0x1a80d26);
    if (ok) {
        if (ser.Serialize(s))
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00c9db70
bool cTribeTool::Read(Stream* s)
{
    uint32_t tmp;
    EA_ReadInt32(s->vf20()->vf18(), &tmp, 1, 0);

    bool ok;
    if (gameData.Read(s) && spatial.Read(s) && combatant.Read(s)) {
        if (combatant.mpOwner) {
            DefObj* t = combatant.mpOwner;
            combatant.mpOwner = 0;
            t->Release();
        }
        if (s->vf28(0x4f396a66, &combatant.mpOwner, 0))
            ok = true;
        else
            ok = false;
    }
    else
        ok = false;

    EA_ReadInt32(s->vf20()->vf18(), &spatial.m98, 1, 0);
    EA_ReadInt32(s->vf20()->vf18(), &spatial.m90, 1, 0);
    EA_ReadInt32(s->vf20()->vf18(), &spatial.m94, 1, 0);

    cVarListSerializer ser(this, (void*)0x157c5d0, 0x1a80d26);
    if (ok) {
        if (ser.SerializeRead(s))
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00c9dd50
void cTribeTool::FUN_00c9dd50()
{
    Worm* w = PlanetModel()->mp24;
    if (!w)
        return;
    if (combatant.m128)
        return;

    LocExt* a = ((cSpatialObjectV*)&spatial)->vfac();
    if (!a)
        return;

    LocExt* bb = ((cSpatialObjectV*)&spatial)->vfac();
    if (!bb->mp90)
        return;

    uint8_t t[0x40];
    ((void**)t)[0] = 0;

    const Vec3* p = (const Vec3*)((cSpatialObjectV*)&spatial)->vf2c();
    (void)p;

    LocExt* cc = ((cSpatialObjectV*)&spatial)->vfac();
    w->vf54(t, cc->mp90);
    combatant.m128 = 1;
}