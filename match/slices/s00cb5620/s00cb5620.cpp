// match/slices/s00cb5620/s00cb5620.cpp
// SP::cDefaultBeamProjectile / SP::cDefaultAoEArea and related Simulator helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;
typedef long long      s64;
typedef float          f32;
typedef double         f64;

#define VT(p)   (*(void***)(p))
#define MOPS(p) ((COps*)(p))

extern "C" float __cdecl sqrtf(float);

// ---------------------------------------------------------------------------
// Placeholder struct: every ecx-passed callee is declared here as a member so
// the call site emits `mov ecx, <this>` + `call rel32`.
// ---------------------------------------------------------------------------
struct COps {
    void  FUN_00c88670(u32);                          // 0x00c88670 Simulator::cCommunity::func54h
    void  FUN_00c3f160(s32, f32);                     // 0x00c3f160 cInteractableObject::SetEffectId
    void  FUN_00c8b2e0();                             // 0x00c8b2e0
    void  FUN_00ac0450();                             // 0x00ac0450
    void  FUN_00bc3130();                             // 0x00bc3130 SP::cSPTimer::Restart
    void  FUN_00b638b0();                             // 0x00b638b0 SP::cGonzagoTimer::~cGonzagoTimer
    void  FUN_00c8a420();                             // 0x00c8a420
    f32   FUN_0104be40();                             // 0x0104be40 SP::cSPSpaceToolData::GetDamageRadius
    u32   FUN_00ce6950();                             // 0x00ce6950 cStarRecordRef::GetCommContext
    void  FUN_00be0fc0(u32);                          // 0x00be0fc0
    void  FUN_00bdad60(u32);                          // 0x00bdad60
    void  FUN_00bcc7e0(u32);                          // 0x00bcc7e0
    void  FUN_00bcd130(u32);                          // 0x00bcd130
    u32   FUN_008e7f80();                             // 0x008e7f80 SP::cCombatant::GetDamageState
    u8    FUN_00b35d30(u32, f32, void*, u32);         // 0x00b35d30
    void* FUN_00b7f250();                             // 0x00b7f250 SP::BuildSurfaceOrientation2
    void  FUN_00b184c0();                             // 0x00b184c0 SP::cGameData::~cGameData
    u32   FUN_00a68fb0(u32);                          // 0x00a68fb0 RandomUint32Uniform
};

void* __cdecl FUN_00b7e560(void*);                    // 0x00b7e560 SP::RandomDirection3
void* __stdcall FUN_00b3d350(void*, void*, void*);    // 0x00b3d350 SP::PlanetModel
void* __cdecl FUN_00b3d240(u32, f32, void*, u32);    // 0x00b3d240
void* __cdecl FUN_00ae3370(void*);                    // 0x00ae3370
void* __cdecl FUN_00bcd430(void*);                    // 0x00bcd430
void* __cdecl FUN_00c032a0(void*);                    // 0x00c032a0 SP::GetCreatureFromStimulus
void* __cdecl FUN_00ae3350(void*);                    // 0x00ae3350

__declspec(noinline) u8 __cdecl FUN_00cb6310(void*, u8);   // 0x00cb6310
__declspec(noinline) u8 __cdecl FUN_00cb6400(void*, u8);   // 0x00cb6400

extern f32 gF_0157d350;   // 0x0157d350  ( 1.0)
extern f32 gF_01471064;   // 0x01471064  ( 0.5)
extern f32 gF_013ec4b8;   // 0x013ec4b8  ( 1e-8)
extern u32 gU_0169a40c;   // 0x0169a40c
extern u8  gB_0169a408;   // 0x0169a408

// ---------------------------------------------------------------------------
// Small external views of engine objects touched by this slice.
// ---------------------------------------------------------------------------
struct cAimOwner {
    u8    mPad000[0x118];
    void* mpAim;          // 0x118
};

struct cToolData {
    u8    mPad000[0x114];
    void* mpItem114;      // 0x114
    void* mpItem118;      // 0x118
};

struct cCombatantObj {
    u8    mPad000[0x08];
    u8    mB_08;          // 0x008 mIgnoreCombatLineTest
    u8    mPad009[0x7f];
    u32   mU_88;          // 0x088
    u8    mPad08c[0x19c];
    u32   mU_228;         // 0x228
    u8    mPad22c[0x4e8];
    s32   mS_714;         // 0x714
};

// ---------------------------------------------------------------------------
// Simulator::cCommunity
// ---------------------------------------------------------------------------
class cCommunity {
public:
    u8    mPad000[0x5d4];
    void* mpInteractable;     // 0x5d4
public:
    void FUN_00cb5620(u32);   // 0x00cb5620
};

// ---------------------------------------------------------------------------
// Simulator::cGameData
// ---------------------------------------------------------------------------
class cGameData {
public:
    u8    mPad000[0x2c];      // 0x000
    void* mpSub2c;            // 0x02c
    u8    mPad030[0x04];      // 0x030
    u8    mSub34[0xa6];       // 0x034
    u8    mB_da;              // 0x0da
    u8    mPad0db[0x41];      // 0x0db
    u8    mSub11c[0x18];      // 0x11c
    void* mp134;              // 0x134
    void* mp138;              // 0x138
    u8    mPad13c[0x20];      // 0x13c
    f32   mF15c;              // 0x15c
    u8    mPad160[0x10];      // 0x160
    f32   mF170;              // 0x170
    u8    mPad174[0x04];      // 0x174
    s64   mQ64;               // 0x178 (quotient + sign)
    u8    mPad180[0x60];      // 0x180
    void* mp1e0;              // 0x1e0
public:
    void FUN_00cb5670();                          // 0x00cb5670 RemoveOwner
    void FUN_00cb56f0(void*, s32, f32, f32);      // 0x00cb56f0
};

// ---------------------------------------------------------------------------
// SP::cDefaultBeamProjectile
// ---------------------------------------------------------------------------
class cDefaultBeamProjectile {
public:
    u8    mPad000[0x2c];      // 0x000
    void* mpSub2c;            // 0x02c
    u8    mPad030[0x104];     // 0x030
    void* mpOwner;            // 0x134
    void* mpTarget;           // 0x138
    f32   mCurX;              // 0x13c
    f32   mCurY;              // 0x140
    f32   mCurZ;              // 0x144
    u8    mPad148[0x14];      // 0x148
    f32   mF15c;              // 0x15c
    f32   mDirX;              // 0x160
    f32   mDirY;              // 0x164
    f32   mDirZ;              // 0x168
    u8    mPad16c[0x04];      // 0x16c
    f32   mF170;              // 0x170
    u8    mPad174[0x04];      // 0x174
    s32   mQ178;              // 0x178
    s32   mR17c;              // 0x17c
    f32   mF180;              // 0x180
    f32   mF184;              // 0x184
    f32   mF188;              // 0x188
    f32   mF18c;              // 0x18c
    u32   mU190;              // 0x190
    u32   mU194;              // 0x194
    f32   mF198;              // 0x198
    f32   mF19c;              // 0x19c
    f32   mF1a0;              // 0x1a0
    f32   mF1a4;              // 0x1a4
    f32   mF1a8;              // 0x1a8
    f32   mF1ac;              // 0x1ac
    u8    mPad1b0[0x10];      // 0x1b0
    u8    mTimer1c0[0x20];    // 0x1c0
    void* mpHit;              // 0x1e0
public:
    void FUN_00cb5770(void*, f32*);   // 0x00cb5770 Fire
    void FUN_00cb5930(f32*);          // 0x00cb5930 UpdateTargetPosition
    u32  FUN_00cb5980();              // 0x00cb5980
    u32  FUN_00cb5b70();              // 0x00cb5b70 IsHittingPlayer
};

// ---------------------------------------------------------------------------
// SP::cDefaultAoEArea
// ---------------------------------------------------------------------------
class cDefaultAoEArea {
public:
    void* mpVtbl;             // 0x000
    void* mpVtbl2;            // 0x004
    u8    mPad008[0x2c];      // 0x008
    void* mpSubVtbl;          // 0x034
    u8    mPad038[0xd0];      // 0x038
    void* mpVtbl108;          // 0x108
    u8    mPad10c[0x10];      // 0x10c
    void* mpToolData;         // 0x11c
    f32   mOffX;              // 0x120
    f32   mOffY;              // 0x124
    f32   mOffZ;              // 0x128
    f32   mRadius;            // 0x12c
    u8    mActive;            // 0x130
    u8    mPad131[0x07];      // 0x131
    u8    mTimer138[0x20];    // 0x138
    u32   mU158;              // 0x158
    u32   mU15c;              // 0x15c
    u32   mU160;              // 0x160
    u32   mU164;              // 0x164
    u32   mU168;              // 0x168
    u32   mU16c;              // 0x16c
public:
    void FUN_00cb5bd0();                 // 0x00cb5bd0
    void FUN_00cb5cf0(void*);            // 0x00cb5cf0 InitArea
    u8   FUN_00cb5d80(f32*, f32*);       // 0x00cb5d80
    u8   FUN_00cb5e10(f32*, f32*);       // 0x00cb5e10 GetNoteEffectPositionAndOrientation
    u8   FUN_00cb5fe0();                 // 0x00cb5fe0
    u32  FUN_00cb6020();                 // 0x00cb6020
    u32  FUN_00cb6060();                 // 0x00cb6060 GetNoteEffectID
    void FUN_00cb6090();                 // 0x00cb6090 StartArea
    void FUN_00cb61d0();                 // 0x00cb61d0 StopArea
};

// ===========================================================================
// 0x00cb5620: notify the community's interactable object with the scaled id.
// ===========================================================================
// @ 0x00cb5620
void cCommunity::FUN_00cb5620(u32 a1)
{
    MOPS(this)->FUN_00c88670(a1);
    void* obj = mpInteractable;
    if (obj != 0) {
        f32 k = gF_0157d350;
        f32 s = ((f32 (__thiscall*)(void*))VT(this)[0x34 / 4])(this);
        f32 r = k * s;
        MOPS(obj)->FUN_00c3f160((s32)a1, r);
    }
}

// ===========================================================================
// 0x00cb5670: drop every owner/target reference held by the game data.
// ===========================================================================
// @ 0x00cb5670
void cGameData::FUN_00cb5670()
{
    void* p = mp134;
    if (p != 0) {
        mp134 = 0;
        ((void (__thiscall*)(void*))VT(p)[8 / 4])(p);
    }
    p = mp1e0;
    if (p != 0) {
        mp1e0 = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    p = mp138;
    if (p != 0) {
        mp138 = 0;
        ((void (__thiscall*)(void*))VT(p)[0x64 / 4])(p);
    }
    p = mpSub2c;
    if (p != 0) {
        mpSub2c = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    MOPS((u8*)this + 0x34)->FUN_00c8b2e0();
    MOPS((u8*)this + 0x11c)->FUN_00ac0450();
}

// ===========================================================================
// 0x00cb56f0: adopt the owner and record the timing parameters.
// ===========================================================================
// @ 0x00cb56f0
void cGameData::FUN_00cb56f0(void* a1, s32 a2, f32 a3, f32 a4)
{
    void* old = mp134;
    if (a1 != old) {
        if (a1 != 0)
            ((void (__thiscall*)(void*))VT(a1)[4 / 4])(a1);
        mp134 = a1;
        if (old != 0)
            ((void (__thiscall*)(void*))VT(old)[8 / 4])(old);
    }
    if (a2 != 0)
        mQ64 = 1000 / a2;
    mF170 = a3;
    mF15c = a4;
    mB_da = 0;
}

// ===========================================================================
// 0x00cb5770: launch the beam at a target from a position.
// ===========================================================================
// @ 0x00cb5770
void cDefaultBeamProjectile::FUN_00cb5770(void* target, f32* pos)
{
    MOPS(mTimer1c0)->FUN_00bc3130();

    void* aim = ((cAimOwner*)mpOwner)->mpAim;
    if (aim != 0) {
        f32* p = (f32*)((void* (__thiscall*)(void*))VT(aim)[0x2c / 4])(aim);
        mCurX = p[0];
        mCurY = p[1];
        mCurZ = p[2];
    } else {
        mCurX = pos[0];
        mCurY = pos[1];
        mCurZ = pos[2];
    }

    void* old = mpTarget;
    if (target != old) {
        if (target != 0)
            ((void (__thiscall*)(void*))VT(target)[0x60 / 4])(target);
        mpTarget = target;
        if (old != 0)
            ((void (__thiscall*)(void*))VT(old)[0x64 / 4])(old);
    }

    mF180 = 0.0f;
    mF184 = 0.0f;
    mF188 = 0.0f;
    mF18c = 0.0f;

    void* gd = (void*)((void* (__thiscall*)(void*))VT(target)[8 / 4])(target);
    f32* tpos = (f32*)((void* (__thiscall*)(void*))VT(gd)[0x2c / 4])(gd);
    f32 dx = pos[0] - tpos[0];
    f32 dy = pos[1] - tpos[1];
    f32 dz = pos[2] - tpos[2];
    f32 inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);

    f32 dir[3];
    dir[0] = dx * inv;
    dir[1] = dy * inv;
    dir[2] = dz * inv;
    mDirX = dir[0];
    mDirY = dir[1];
    mDirZ = dir[2];

    f32* rd = (f32*)FUN_00b7e560(dir);
    mF1a4 = rd[0];
    mF1a8 = rd[1];
    mF1ac = rd[2];
    mF198 = 0.0f;
    mF19c = 0.0f;
    mF1a0 = 0.0f;
    mU190 = 0;
    mU194 = 0;
}

// ===========================================================================
// 0x00cb5930: refresh the stored current offset from the aim object.
// ===========================================================================
// @ 0x00cb5930
void cDefaultBeamProjectile::FUN_00cb5930(f32* pos)
{
    f32* src;
    void* owner = mpOwner;
    if (owner != 0) {
        void* aim = ((cAimOwner*)owner)->mpAim;
        if (aim != 0)
            src = (f32*)((void* (__thiscall*)(void*))VT(aim)[0x2c / 4])(aim);
        else
            src = pos;
    } else {
        src = pos;
    }
    *(u32*)&mCurX = ((u32*)src)[0];
    *(u32*)&mCurY = ((u32*)src)[1];
    *(u32*)&mCurZ = ((u32*)src)[2];
}

// ===========================================================================
// 0x00cb5980: return the sub-object's property, or 0.
// ===========================================================================
// @ 0x00cb5980
u32 cDefaultBeamProjectile::FUN_00cb5980()
{
    void** slot = (void**)((u8*)mpSub2c + 0x114);
    void* p = *slot;
    if (p == 0)
        return 0;
    return ((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x13f94d4);
}

// ===========================================================================
// 0x00cb59b0: fire callback shared by the area/projectile effects.
// ===========================================================================
// @ 0x00cb59b0
void __cdecl FUN_00cb59b0(void* self, f32* pos, f32 f1, f32 f2,
                          s32 mode, s32 id, u32 a5, u32 a6)
{
    if (a6 == 0 && id != -1) {
        u32 myId = ((u32 (__thiscall*)(void*))VT(self)[0x10 / 4])(self);
        if (myId == (u32)id)
            return;
    }

    void* propA = 0;
    void* propB = 0;
    if (self != 0) {
        propA = (void*)((u32 (__thiscall*)(void*, u32))VT(self)[0x5c / 4])(self, 0xe9cb8ba);
        propB = (void*)((u32 (__thiscall*)(void*, u32))VT(self)[0x5c / 4])(self, 0x436f315);
    }

    if (mode == 3) {
        if (propA != 0) {
            u32 a = ((u32 (__thiscall*)(void*))VT(propA)[0x10 / 4])(propA);
            u32 b = ((u32 (__thiscall*)(void*))VT(self)[0x10 / 4])(self);
            if (b != a)
                return;
        }
        if (propA != 0)
            return;
        if (propB != 0)
            return;
    }

    void* gd = (void*)((void* (__thiscall*)(void*))VT(self)[8 / 4])(self);
    f32* gp = (f32*)((void* (__thiscall*)(void*))VT(gd)[0x2c / 4])(gd);
    f32 dx = gp[0] - pos[0];
    f32 dy = gp[1] - pos[1];
    f32 dz = gp[2] - pos[2];

    f32 v = f1;
    if (mode != 3) {
        s32 n = (s32)f2;
        u32 r = MOPS((void*)0x01601760)->FUN_00a68fb0((u32)n);
        v = (f32)((s32)r + (s32)f1);
    }

    f32 inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + gF_013ec4b8);
    f32 dir[3];
    dir[0] = dx * inv;
    dir[1] = dy * inv;
    dir[2] = dz * inv;
    ((void (__thiscall*)(void*, f32, s32, s32, f32*, u32))VT(self)[0x18 / 4])
        (self, v, id, mode, dir, a5);
}

// ===========================================================================
// 0x00cb5b70: true when the current hit object is a player.
// ===========================================================================
// @ 0x00cb5b70
u32 cDefaultBeamProjectile::FUN_00cb5b70()
{
    void* p = mpHit;
    if (p != 0) {
        void* q = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xc / 4])(p, 0xb033b403);
        if (q != 0 && ((cCombatantObj*)q)->mS_714 == 0)
            return 1;
    }
    return 0;
}

// ===========================================================================
// 0x00cb5bd0: cDefaultAoEArea destructor.
// ===========================================================================
// @ 0x00cb5bd0
void cDefaultAoEArea::FUN_00cb5bd0()
{
    mpVtbl = (void*)0x14752b8;
    mpVtbl2 = (void*)0x14752a4;
    mpSubVtbl = (void*)0x14751e0;
    mpVtbl108 = (void*)0x14751b4;

    MOPS((u8*)this + 0x138)->FUN_00b638b0();

    void* p = mpToolData;
    if (p != 0)
        ((void (__thiscall*)(void*))VT(p)[8 / 4])(p);

    mpVtbl108 = (void*)0x145dca8;
    MOPS((u8*)this + 0x34)->FUN_00c8a420();
    MOPS(this)->FUN_00b184c0();
}

// ===========================================================================
// 0x00cb5cf0: adopt the tool data and cache its damage radius.
// ===========================================================================
// @ 0x00cb5cf0
void cDefaultAoEArea::FUN_00cb5cf0(void* tool)
{
    void* old = mpToolData;
    if (tool != old) {
        if (tool != 0)
            ((void (__thiscall*)(void*))VT(tool)[4 / 4])(tool);
        mpToolData = tool;
        if (old != 0)
            ((void (__thiscall*)(void*))VT(old)[8 / 4])(old);
    }
    mRadius = MOPS(tool)->FUN_0104be40();
}

// ===========================================================================
// 0x00cb5d80: compute the area position and orientation.
// ===========================================================================
// @ 0x00cb5d80
u8 cDefaultAoEArea::FUN_00cb5d80(f32* pos, f32* orient)
{
    cToolData* tool = (cToolData*)mpToolData;
    if (tool == 0)
        return 0;
    if (tool->mpItem114 == 0)
        return 0;

    f32* p = (f32*)((void* (__thiscall*)(void*))VT((u8*)this + 0x34)[0x2c / 4])((u8*)this + 0x34);
    pos[0] = p[0] + mOffX;
    pos[1] = p[1] + mOffY;
    pos[2] = p[2] + mOffZ;

    f32* q = (f32*)((void* (__thiscall*)(void*))VT((u8*)this + 0x34)[0x30 / 4])((u8*)this + 0x34);
    orient[0] = q[0];
    orient[1] = q[1];
    orient[2] = q[2];
    orient[3] = q[3];
    return 1;
}

// ===========================================================================
// 0x00cb5e10: note-effect position and orientation from the two items.
// ===========================================================================
// @ 0x00cb5e10
u8 cDefaultAoEArea::FUN_00cb5e10(f32* pos, f32* orient)
{
    cToolData* tool = (cToolData*)mpToolData;
    if (tool == 0)
        return 0;
    if (tool->mpItem114 == 0)
        return 0;

    void* i1 = tool->mpItem114;
    void* o1 = (void*)((u32 (__thiscall*)(void*, u32))VT(i1)[0xb8 / 4])(i1, 0x1186577);
    void* i2 = tool->mpItem118;
    void* o2 = 0;
    if (i2 != 0)
        o2 = (void*)((u32 (__thiscall*)(void*, u32))VT(i2)[0xb8 / 4])(i2, 0x1186577);

    u32 f1 = *(u32*)((u8*)o1 + 0x50);
    if ((f1 & 0x10) != 0 && (f1 & 0x20) == 0) {
        f32* p = (f32*)((void* (__thiscall*)(void*))VT(o1)[0x2c / 4])(o1);
        pos[0] = p[0];
        pos[1] = p[1];
        pos[2] = p[2];
    } else {
        f32 tmp[6];
        f32* p = (f32*)((void* (__thiscall*)(void*, void*))VT(o1)[0x6c / 4])(o1, tmp);
        pos[0] = (p[0] + p[3]) * gF_01471064;
        pos[1] = (p[4] + p[1]) * gF_01471064;
        pos[2] = (p[5] + p[2]) * gF_01471064;
    }

    f32 cx, cy, cz;
    u32 f2 = *(u32*)((u8*)o2 + 0x50);
    if ((f2 & 0x10) != 0 && (f2 & 0x20) == 0) {
        f32* p = (f32*)((void* (__thiscall*)(void*))VT(o2)[0x2c / 4])(o2);
        cx = p[0];
        cy = p[1];
        cz = p[2];
    } else {
        f32 tmp[6];
        f32* p = (f32*)((void* (__thiscall*)(void*, void*))VT(o2)[0x6c / 4])(o2, tmp);
        cx = (p[0] + p[3]) * gF_01471064;
        cy = (p[4] + p[1]) * gF_01471064;
        cz = (p[5] + p[2]) * gF_01471064;
    }

    f32 diff[3];
    diff[0] = cx - pos[0];
    diff[1] = cy - pos[1];
    diff[2] = cz - pos[2];

    f32 tmpa[6];
    void* pm = (void*)FUN_00b3d350(tmpa, pos, diff);
    f32* r = (f32*)MOPS(pm)->FUN_00b7f250();
    orient[0] = r[0];
    orient[1] = r[1];
    orient[2] = r[2];
    orient[3] = r[3];
    return 1;
}

// ===========================================================================
// 0x00cb5fe0: true when the item exposes the note-effect property.
// ===========================================================================
// @ 0x00cb5fe0
u8 cDefaultAoEArea::FUN_00cb5fe0()
{
    cToolData* tool = (cToolData*)mpToolData;
    void* p = tool->mpItem118;
    u32 v = 0;
    if (p != 0)
        v = ((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x137e8e0);
    return (v != 0) ? 1 : 0;
}

// ===========================================================================
// 0x00cb6020: note-effect selector derived from the item's state.
// ===========================================================================
// @ 0x00cb6020
u32 cDefaultAoEArea::FUN_00cb6020()
{
    cToolData* tool = (cToolData*)mpToolData;
    void* p = tool->mpItem114;
    u32 v = 0;
    if (p != 0)
        v = ((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x137e8e0);
    u32 x = *(u32*)((u8*)v + 0xb1c);
    return 0x99736761 + ((x != 2) ? 0x749c5cb3 : 0);
}

// ===========================================================================
// 0x00cb6060: always returns the note-effect id hash.
// ===========================================================================
// @ 0x00cb6060
u32 cDefaultAoEArea::FUN_00cb6060()
{
    cToolData* tool = (cToolData*)mpToolData;
    void* p = tool->mpItem114;
    if (p != 0)
        ((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x137e8e0);
    return 0xfb2bdb16;
}

// ===========================================================================
// 0x00cb6090: start the area effect and notify the relevant item.
// ===========================================================================
// @ 0x00cb6090
void cDefaultAoEArea::FUN_00cb6090()
{
    mActive = 0;
    MOPS((u8*)this + 0x138)->FUN_00bc3130();
    cToolData* tool = (cToolData*)mpToolData;
    mU158 = 0;
    mU15c = 0;
    mU160 = 0;
    mU164 = 0;
    mU168 = 0;
    mU16c = 0;

    if (MOPS(tool)->FUN_00ce6950() != 0x94e412ed)
        return;

    void* p = tool->mpItem118;
    void* a = 0;
    void* b = 0;
    void* c = 0;
    if (p != 0)
        a = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x3d5c477);
    p = tool->mpItem118;
    if (p != 0)
        b = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0xe9cb8ba);
    p = tool->mpItem118;
    if (p != 0)
        c = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x436f315);

    if (a != 0) {
        void* q = tool->mpItem114;
        u32 r = 0;
        if (q != 0)
            r = ((u32 (__thiscall*)(void*, u32))VT(q)[0xb8 / 4])(q, 0x17f243b);
        MOPS(a)->FUN_00be0fc0(r);
        return;
    }
    if (b != 0) {
        MOPS(b)->FUN_00bcc7e0(1);
        return;
    }
    if (c != 0)
        MOPS(c)->FUN_00bcd130(1);
}

// ===========================================================================
// 0x00cb61d0: stop the area effect and notify the relevant item.
// ===========================================================================
// @ 0x00cb61d0
void cDefaultAoEArea::FUN_00cb61d0()
{
    mActive = 1;
    cToolData* tool = (cToolData*)mpToolData;
    if (MOPS(tool)->FUN_00ce6950() != 0x94e412ed)
        return;

    void* p = tool->mpItem118;
    if (p != 0) {
        void* q = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x17f243b);
        if (q != 0) {
            if (((u8 (__thiscall*)(void*))VT(q)[0x2c / 4])(q) != 0)
                return;
        }
    }

    void* a = 0;
    void* b = 0;
    void* c = 0;
    p = tool->mpItem118;
    if (p != 0)
        a = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x3d5c477);
    p = tool->mpItem118;
    if (p != 0)
        b = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0xe9cb8ba);
    p = tool->mpItem118;
    if (p != 0)
        c = (void*)((u32 (__thiscall*)(void*, u32))VT(p)[0xb8 / 4])(p, 0x436f315);

    if (a != 0) {
        void* q = tool->mpItem114;
        u32 r = 0;
        if (q != 0)
            r = ((u32 (__thiscall*)(void*, u32))VT(q)[0xb8 / 4])(q, 0x17f243b);
        MOPS(a)->FUN_00bdad60(r);
        return;
    }
    if (b != 0) {
        MOPS(b)->FUN_00bcc7e0(0xffffffff);
        return;
    }
    if (c != 0)
        MOPS(c)->FUN_00bcd130(0xffffffff);
}

// ===========================================================================
// 0x00cb6310: combat-line eligibility check.
// ===========================================================================
// @ 0x00cb6310
u8 __cdecl FUN_00cb6310(void* a1, u8 a2)
{
    if (a1 == 0)
        return 0;

    void* c = (void*)((u32 (__thiscall*)(void*, u32))VT(a1)[0xc / 4])(a1, 0x13f94d4);
    if (c != 0) {
        u32 ds = MOPS(c)->FUN_008e7f80();
        if (ds == 2)
            return 0;
        if (((cCombatantObj*)c)->mB_08 != 0)
            return 0;
        if (a2 != 0)
            return 1;
        u32 id = ((u32 (__thiscall*)(void*))VT(c)[0x10 / 4])(c);
        if (id == gU_0169a40c)
            return 0;
        return 1;
    }

    void* p = (void*)((u32 (__thiscall*)(void*, u32))VT(a1)[0xc / 4])(a1, 0x3ed590d);
    if (p != 0) {
        u32 v = ((cCombatantObj*)p)->mU_88;
        if (v == 0 || v == 1 || v == 2)
            return 1;
        return 0;
    }

    void* q = (void*)((u32 (__thiscall*)(void*, u32))VT(a1)[0xc / 4])(a1, 0x175cdc9);
    if (q != 0) {
        u32 v = ((cCombatantObj*)q)->mU_228;
        if (v == 0x611a05e)
            return 1;
        if (v == 0x611a05f)
            return 1;
    }
    return 0;
}

// ===========================================================================
// 0x00cb63c0 / 0x00cb63e0: single-argument wrappers around FUN_00cb6310.
// ===========================================================================
// @ 0x00cb63c0
void __cdecl FUN_00cb63c0(void* a1)
{
    void* p = *(void**)((u8*)a1 + 0x64);
    FUN_00cb6310(p, 1);
}

// @ 0x00cb63e0
void __cdecl FUN_00cb63e0(void* a1)
{
    void* p = *(void**)((u8*)a1 + 0x64);
    FUN_00cb6310(p, 0);
}

// ===========================================================================
// 0x00cb6400: extended combat-line eligibility check.
// ===========================================================================
// @ 0x00cb6400
u8 __cdecl FUN_00cb6400(void* a1, u8 a2)
{
    if (a1 == 0)
        return 0;

    void* c = (void*)((u32 (__thiscall*)(void*, u32))VT(a1)[0xc / 4])(a1, 0x13f94d4);
    if (c == 0)
        return 0;

    void* prop = (void*)((u32 (__thiscall*)(void*, u32))VT(c)[0x5c / 4])(c, 0xb033b403);
    u32 ds = MOPS(c)->FUN_008e7f80();
    if (ds == 2)
        return 0;
    if (((cCombatantObj*)c)->mB_08 != 0)
        return 0;
    if (a2 == 0) {
        u32 id = ((u32 (__thiscall*)(void*))VT(c)[0x10 / 4])(c);
        if (id == gU_0169a40c)
            return 0;
    }
    if (gB_0169a408 != 0 && prop != 0 && ((cCombatantObj*)prop)->mS_714 == 3)
        return 0;

    if (FUN_00ae3370(c) != 0)
        return 1;
    if (FUN_00bcd430(c) != 0)
        return 1;
    if (FUN_00c032a0(c) != 0)
        return 1;
    if (FUN_00ae3350(c) != 0)
        return 1;
    return 0;
}

// ===========================================================================
// 0x00cb64c0 / 0x00cb64e0: single-argument wrappers around FUN_00cb6400.
// ===========================================================================
// @ 0x00cb64c0
void __cdecl FUN_00cb64c0(void* a1)
{
    void* p = *(void**)((u8*)a1 + 0x64);
    FUN_00cb6400(p, 1);
}

// @ 0x00cb64e0
void __cdecl FUN_00cb64e0(void* a1)
{
    void* p = *(void**)((u8*)a1 + 0x64);
    FUN_00cb6400(p, 0);
}

// ===========================================================================
// 0x00cb6500: run a combat-line test with a temporary "ignore" flag.
// ===========================================================================
// @ 0x00cb6500
u32 __cdecl FUN_00cb6500(u32 a1, f32 a2, u32 a3, void* a4)
{
    u8 old = 0;
    void* cb = (void*)0x00cb63c0;

    if (a4 != 0) {
        old = *((u8*)a4 + 8);
        *((u8*)a4 + 8) = 1;
        if (*((u8*)a4 + 9) != 0) {
            cb = (void*)0x00cb63e0;
            gU_0169a40c = ((u32 (__thiscall*)(void*))VT(a4)[0x10 / 4])(a4);
        }
    }

    void* r = (void*)FUN_00b3d240(a1, a2, cb, a3);
    u32 result = 3;
    if (MOPS(r)->FUN_00b35d30(a1, a2, cb, a3) != 0)
        result = 0;

    if (a4 != 0)
        *((u8*)a4 + 8) = old;
    return result;
}
