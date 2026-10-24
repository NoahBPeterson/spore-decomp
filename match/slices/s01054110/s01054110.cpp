// @slice s01054110
// SP tool-strategy handlers.  These are the activate/deactivate/creation
// entry points of the place-colony, beam, area and space tools.  Almost all
// of them follow the same shape: fetch an engine noun through the noun
// manager (CreateNoun + the noun's own virtual "get sub-object" slot), poke
// it, and hand it to the terrain cursor.
//
// Every engine object is modelled as a single Obj view whose first dword is
// the vtable pointer.  The vtable itself is a struct of *named* slots; each
// call site casts a slot to its exact __thiscall signature and names the slot
// with a VSlot constant.  No raw byte-offset pointer arithmetic appears
// anywhere.
//
// __thiscall callees are declared as ordinary member functions of small local
// structs (MSVC rejects __thiscall on free functions); the `// 0x<va>` comment
// on the declaration is what lets the equivalence harness hook them.

typedef unsigned int  u32;
typedef unsigned char u8;

struct Obj;

typedef void          (__thiscall *VfnRaw)();
typedef void          (__thiscall *Vfn0)(void*);
typedef void*         (__thiscall *VfnP)(void*);
typedef void          (__thiscall *VfnI)(void*, int);
typedef void*         (__thiscall *VfnPI)(void*, int);
typedef void          (__thiscall *VfnII)(void*, int, int);
typedef void          (__thiscall *VfnVV)(void*, void*, void*);
typedef void          (__thiscall *VfnV)(void*, void*);
typedef unsigned char (__thiscall *VfnB)(void*);
typedef unsigned char (__thiscall *VfnB3)(void*, void*, void*, int);

// Named vtable slots (value = byte offset / 4).
enum VSlot {
    kV00 = 0x00 / 4,
    kV04 = 0x04 / 4,
    kV0C = 0x0c / 4,
    kV10 = 0x10 / 4,
    kV18 = 0x18 / 4,
    kV24 = 0x24 / 4,
    kV2C = 0x2c / 4,
    kV38 = 0x38 / 4,
    kV48 = 0x48 / 4,
    kV54 = 0x54 / 4,
    kV5C = 0x5c / 4,
    kV68 = 0x68 / 4,
    kVB8 = 0xb8 / 4,
    kVD0 = 0xd0 / 4,
    kVD4 = 0xd4 / 4
};

struct Vtbl {
    VfnRaw mSlots[0xd8 / 4];    // +0x00 .. +0xd4
};

struct Vec3 { float x, y, z; };

// Sub-object embedded inside a game object at +0x34; it carries its own
// vtable pointer.
struct Sub34 {
    Vtbl* mpVtbl;               // +0x00
};

struct Obj {
    Vtbl*         mpVtbl;                  // +0x000
    unsigned char mPad004[0x30];           // +0x004
    Sub34         mSub34;                  // +0x034
    unsigned char mPad038[0xa6 - 0x38];    // +0x038
    u8            mByteA6;                 // +0x0a6
    unsigned char mPad0A7[0x110 - 0xa7];   // +0x0a7
    u8            mByte110;                // +0x110
    unsigned char mPad111[0x114 - 0x111];  // +0x111
    Obj*          mpManager114;            // +0x114  owning tool manager
    unsigned char mPad118[0x120 - 0x118];  // +0x118
    Obj*          mpArea120;               // +0x120  current AoE area noun
    Obj*          mpBeam124;               // +0x124  current beam projectile
    Obj*          mpUnk128;                // +0x128
    unsigned char mPad12c[0x140 - 0x12c];  // +0x12c
    Obj*          mpUnk140;                // +0x140
    float         mF144;                   // +0x144
    float         mF148;                   // +0x148
    float         mF14c;                   // +0x14c  range multiplier
    unsigned char mPad150[0x154 - 0x150];  // +0x150
    Vec3          mVec154;                 // +0x154  previous aim/orientation
    Vec3          mVec160;                 // +0x160  new aim/orientation
    Obj*          mpUnk16c;                // +0x16c  transform receiver
};

// ---- __thiscall callees (declared as members; VA in the line comment) ------
struct ToolStrategy {
    char ActivateTool(int a);                     // 0x10537e0
};
struct GameObj {
    void f50d0(int a);                            // 0x10050d0
};
struct NounMgr {
    void* CreateNoun(u32 key);                    // 0xb20c60
    void  RemoveNoun(void* noun);                 // 0xb225d0
};
struct C8017f0 {
    char Set(void* a);                            // 0x8017f0
};
struct ObjVec {
    void* erase(void* a);                         // 0xb3d390
};
struct ToolManager {
    void UseToolStop();                           // 0x104fa90
};
struct SpaceTool {
    float Get01();                                // 0x104bdd0
    float Get02(float x);                         // 0x104bdb0
    float Get03();                                // 0x104be30
    char  Get04();                                // 0x104cd00
    char  Get05();                                // 0x104cd10
    char  Get06();                                // 0x104cd30
    char  Get07();                                // 0x104cd50
    char  Get08();                                // 0x104cd90
    float Get09();                                // 0x104bee0
    float Get0a();                                // 0x104be50
    void  Get0b();                                // 0x104bdc0
};
struct ChargeTool {
    float Spread(float x);                        // 0xce6940
};
struct Projectile {
    void SetA(int a);                             // 0xcb3d00
    void SetB(int a);                             // 0xcb3ce0
};
struct BeamProjectile {
    void Fire(void* a, void* b);                  // 0xcb5770
};
struct AoEArea {
    void InitArea(void* tool);                    // 0xcb5cf0
    void StartArea();                             // 0xcb6090
};
struct Noun2 {
    void Cleanup();                               // 0xcb3c70
};
struct SubObj2 {
    void Notify(int a);                           // 0x1030dd0
};
struct Simulator {
    void ClearDirty();                            // 0xb78860
};
struct XformMsgObj {
    void construct();                             // 0x434040
};

// ---- cdecl callees --------------------------------------------------------
extern void*  SP_SpaceGameGet(void);                  // 0x1002bd0
extern void*  SP_GetUniverseContext(void);            // 0x1021080
extern void*  SP_NounManager(void);                   // 0xb3d300
extern void   FUN_00bebb10(void);                     // 0xbebb10
extern void*  SP_GetGameTerrainCursor(void);          // 0xb30d70
extern void   FUN_00bed920(int a, int b);             // 0xbed920
extern void*  SP_GonzagoModelWorld(void);             // 0xb3d520
extern void*  FUN_0067cab0(int a);                    // 0x67cab0
extern void*  FUN_011e0810(void);                     // 0x11e0810
extern void   FUN_00cb7c20(float* v, int a);          // 0xcb7c20
extern void   FUN_00cc0870(float f, void* a, void* b); // 0xcc0870
extern void*  FUN_00b3d3c0(void);                     // 0xb3d3c0
extern float* FUN_00449c20(float* dst, float* src);   // 0x449c20
extern float* FUN_006985b0(float* out, float* in);    // 0x6985b0

struct XformMsg {
    unsigned short mFlags;      // +0x00
    unsigned short mCount;      // +0x02
    unsigned char  mPad04[0x50];
    Vec3           mVec;        // +0x54
    float          mBasis[9];   // +0x60
};

struct PlaceColonyTool {
    char ActivateTool(int a);              // 0x10537e0
    char DeactivateTool(int param_1);      // @ 0x01054110
};

// ---------------------------------------------------------------------------
// @ 0x01054110
// SP::cSPPlaceColonyToolStrategy::DeactivateTool (PDB candidate).  Turns the
// colony placement object off, clears the terrain cursor's pending object and
// drops a "5" behaviour event.
char PlaceColonyTool::DeactivateTool(int param_1)
{
    if (!ActivateTool(param_1))
        return 0;
    Obj* game = (Obj*)SP_SpaceGameGet();
    if (!game)
        return 0;
    if (SP_GetUniverseContext() != 0)
        return 0;
    ((GameObj*)game)->f50d0(1);

    Obj* nounMgr = (Obj*)SP_NounManager();
    Obj* noun = (Obj*)((NounMgr*)nounMgr)->CreateNoun(0x244fb08u);
    Obj* obj;
    if (!noun) {
        obj = 0;
    } else {
        obj = (Obj*)((VfnPI)noun->mpVtbl->mSlots[kV0C])(noun, 0x2450023);
        if (obj)
            ((Vfn0)obj->mpVtbl->mSlots[kV00])(obj);
    }

    obj->mByteA6 = 1;
    Sub34* sub = &obj->mSub34;
    ((VfnI)sub->mpVtbl->mSlots[kV54])(sub, 1);
    ((Vfn0)obj->mpVtbl->mSlots[kV68])(obj);
    obj->mByte110 = 1;
    FUN_00bebb10();

    Obj* cursor = (Obj*)SP_GetGameTerrainCursor();
    ((VfnV)cursor->mpVtbl->mSlots[kVD0])(cursor, sub);
    FUN_00bed920(0xfd701f6f, 5);
    ((Vfn0)obj->mpVtbl->mSlots[kV04])(obj);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x010541f0
// Cancels whatever object the terrain cursor currently holds; the tool passes
// its own "0" state to the game and to the cursor's setter.
char __stdcall FUN_010541f0(int param_1)
{
    (void)param_1;
    Obj* world = (Obj*)SP_GonzagoModelWorld();
    ((VfnII)world->mpVtbl->mSlots[kV18])(world, 0, 5);

    Obj* game = (Obj*)SP_SpaceGameGet();
    if (!game)
        return 0;
    void* host = FUN_0067cab0(0);
    ((C8017f0*)host)->Set(0);
    ((GameObj*)game)->f50d0(0);

    Obj* cursor = (Obj*)SP_GetGameTerrainCursor();
    Obj* obj = (Obj*)((VfnP)cursor->mpVtbl->mSlots[kVD4])(cursor);
    if (!obj) {
        obj = 0;
    } else {
        obj = (Obj*)((VfnPI)obj->mpVtbl->mSlots[kVB8])(obj, 0x2450023);
        if (obj) {
            ((Vfn0)obj->mpVtbl->mSlots[kV00])(obj);
            Obj* nounMgr = (Obj*)SP_NounManager();
            ((NounMgr*)nounMgr)->RemoveNoun(obj);
        }
    }
    ((VfnV)cursor->mpVtbl->mSlots[kVD0])(cursor, 0);
    if (obj)
        ((Vfn0)obj->mpVtbl->mSlots[kV04])(obj);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x010542a0
// As above but only cancels while a universe is live, and selects "4" on the
// model world.
char __stdcall FUN_010542a0(int param_1)
{
    (void)param_1;
    Obj* world = (Obj*)SP_GonzagoModelWorld();
    ((VfnII)world->mpVtbl->mSlots[kV18])(world, 0, 4);

    Obj* game = (Obj*)SP_SpaceGameGet();
    if (!game)
        return 0;
    if (SP_GetUniverseContext() != 0)
        return 0;
    void* host = FUN_0067cab0(0);
    ((C8017f0*)host)->Set(0);

    Obj* cursor = (Obj*)SP_GetGameTerrainCursor();
    Obj* obj = (Obj*)((VfnP)cursor->mpVtbl->mSlots[kVD4])(cursor);
    if (!obj) {
        obj = 0;
    } else {
        obj = (Obj*)((VfnPI)obj->mpVtbl->mSlots[kVB8])(obj, 0x2450023);
        if (obj) {
            ((Vfn0)obj->mpVtbl->mSlots[kV00])(obj);
            Obj* nounMgr = (Obj*)SP_NounManager();
            ((NounMgr*)nounMgr)->RemoveNoun(obj);
        }
    }
    ((VfnV)cursor->mpVtbl->mSlots[kVD0])(cursor, 0);
    if (obj)
        ((Vfn0)obj->mpVtbl->mSlots[kV04])(obj);
    return 1;
}

struct ToolStrategy2 {
    void StopTool(void* param_2, void* param_3);   // @ 0x01054350
};

// ---------------------------------------------------------------------------
// @ 0x01054350
// Drops an active tool: if the tool's object at +0x140 reports "not busy" it
// is erased from the tool-manager vector and stopped.  Then the cursor's
// current object is told to restart with the width returned by the strategy
// virtual at slot +0x24.
void ToolStrategy2::StopTool(void* param_2, void* param_3)
{
    Obj* self = (Obj*)this;
    Obj* p2 = (Obj*)param_2;
    Obj* sub = p2->mpUnk140;
    if (sub != 0 && !((VfnB)sub->mpVtbl->mSlots[kV10])(sub)) {
        void* r = ((ObjVec*)sub)->erase(param_2);
        ((ToolManager*)r)->UseToolStop();
    }

    Obj* cursor = (Obj*)SP_GetGameTerrainCursor();
    Obj* obj = (Obj*)((VfnP)cursor->mpVtbl->mSlots[kVD4])(cursor);
    if (!obj)
        return;
    obj = (Obj*)((VfnPI)obj->mpVtbl->mSlots[kVB8])(obj, 0x2450023);
    if (!obj)
        return;
    ((Vfn0)obj->mpVtbl->mSlots[kV00])(obj);
    u8 w = ((VfnB3)self->mpVtbl->mSlots[kV24])(self, param_2, param_3, 0);
    ((VfnI)obj->mpVtbl->mSlots[kV5C])(obj, w);
    ((Vfn0)obj->mpVtbl->mSlots[kV04])(obj);
}

// ---------------------------------------------------------------------------
// @ 0x01054ec0
// SP::cSPDefaultBeamTool::CreateBeam.  Fires a beam projectile: pulls the
// tool's beam "deed" object, spawns a cDefaultBeamProjectile noun, seeds it
// with the tool's spread/jitter values and the target's push vector, then
// swaps it into the tool's current-beam slot.
char __stdcall FUN_01054ec0(void* param_1, void* param_2)
{
    Obj* tool = (Obj*)param_1;
    if (!tool->mpManager114)
        return 0;
    Obj* mgr = tool->mpManager114;
    Obj* deed = (Obj*)((VfnPI)mgr->mpVtbl->mSlots[kVB8])(mgr, 0x13f94d4);
    if (!deed)
        return 0;

    Obj* nounMgr = (Obj*)SP_NounManager();
    Obj* noun = (Obj*)((NounMgr*)nounMgr)->CreateNoun(0x24630d7u);
    Obj* proj;
    if (!noun) {
        proj = 0;
    } else {
        proj = (Obj*)((VfnPI)noun->mpVtbl->mSlots[kV0C])(noun, 0x24630ce);
        if (proj)
            ((Vfn0)proj->mpVtbl->mSlots[kV00])(proj);
    }

    float a = ((SpaceTool*)tool)->Get01();
    float b = ((SpaceTool*)tool)->Get02((a - 1.0f) * tool->mF14c + 1.0f);
    float y = ((ChargeTool*)tool)->Spread(b) * tool->mF144;
    (void)y;
    void* vfx = FUN_011e0810();
    ((VfnVV)proj->mpVtbl->mSlots[kV54])(proj, tool, vfx);

    char c1 = ((SpaceTool*)tool)->Get04();
    ((Projectile*)proj)->SetA(c1);
    char c2 = ((SpaceTool*)tool)->Get05();
    ((Projectile*)proj)->SetB(c2);
    proj->mVec154.z = ((SpaceTool*)tool)->Get03();

    Obj* m2 = tool->mpManager114;
    void* up = ((VfnP)m2->mpVtbl->mSlots[kV2C])(m2);
    Sub34* sub = &proj->mSub34;
    ((VfnV)sub->mpVtbl->mSlots[kV38])(sub, up);

    void* push = ((VfnP)deed->mpVtbl->mSlots[kV10])(deed);
    ((VfnV)proj->mpVtbl->mSlots[kV48])(proj, push);

    ((BeamProjectile*)proj)->Fire(deed, param_2);

    Obj* old = tool->mpBeam124;
    if (proj != old) {
        ((Vfn0)proj->mpVtbl->mSlots[kV00])(proj);
        tool->mpBeam124 = proj;
        if (old)
            ((Vfn0)old->mpVtbl->mSlots[kV04])(old);
    }
    ((Vfn0)proj->mpVtbl->mSlots[kV04])(proj);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01055040
// SP::cSPDefaultAoETool::CreateArea (PDB candidate).  Spawns a
// cDefaultAoEArea noun, initialises it from the tool, seeds its push vector
// and swaps it into the tool's current-area slot.
char __stdcall FUN_01055040(void* param_1, void* param_2)
{
    (void)param_2;
    Obj* tool = (Obj*)param_1;
    if (!tool->mpManager114)
        return 0;
    Obj* mgr = tool->mpManager114;
    Obj* deed = (Obj*)((VfnPI)mgr->mpVtbl->mSlots[kVB8])(mgr, 0x13f94d4);
    if (!deed)
        return 0;

    Obj* nounMgr = (Obj*)SP_NounManager();
    Obj* noun = (Obj*)((NounMgr*)nounMgr)->CreateNoun(0x4167186u);
    Obj* area;
    if (!noun) {
        area = 0;
    } else {
        area = (Obj*)((VfnPI)noun->mpVtbl->mSlots[kV0C])(noun, 0x4167194);
        if (area)
            ((Vfn0)area->mpVtbl->mSlots[kV00])(area);
    }

    ((AoEArea*)area)->InitArea(tool);

    Obj* m2 = tool->mpManager114;
    void* up = ((VfnP)m2->mpVtbl->mSlots[kV2C])(m2);
    Sub34* sub = &area->mSub34;
    ((VfnV)sub->mpVtbl->mSlots[kV38])(sub, up);

    void* push = ((VfnP)deed->mpVtbl->mSlots[kV10])(deed);
    ((VfnV)area->mpVtbl->mSlots[kV48])(area, push);

    ((AoEArea*)area)->StartArea();

    Obj* old = tool->mpArea120;
    if (area != old) {
        ((Vfn0)area->mpVtbl->mSlots[kV00])(area);
        tool->mpArea120 = area;
        if (old)
            ((Vfn0)old->mpVtbl->mSlots[kV04])(old);
    }
    ((Vfn0)area->mpVtbl->mSlots[kV04])(area);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x01055130
// Tears the tool down: notifies the +0x128 object's sub-object with "2",
// releases and clears the current beam, and marks the simulator clean.
char __stdcall FUN_01055130(void* param_1)
{
    Obj* tool = (Obj*)param_1;
    if (tool->mpUnk128) {
        Obj* o = tool->mpUnk128;
        Obj* sub = (Obj*)((VfnPI)o->mpVtbl->mSlots[kV0C])(o, 0x114242e6);
        if (sub)
            ((SubObj2*)sub)->Notify(2);
    }
    if (tool->mpBeam124) {
        ((Noun2*)tool->mpBeam124)->Cleanup();
        Obj* o = tool->mpBeam124;
        if (o) {
            tool->mpBeam124 = 0;
            ((Vfn0)o->mpVtbl->mSlots[kV04])(o);
        }
    }
    if (((SpaceTool*)tool)->Get07()) {
        void* sim = FUN_00b3d3c0();
        ((Simulator*)sim)->ClearDirty();
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x010551b0
// Builds an orthonormal orientation frame from the tool's previous (+0x154)
// and new (+0x160) aim vectors and posts it as an XformMsg to the transform
// receiver at +0x16c.  The original is pure SSE; this reconstruction keeps
// the observable behaviour (the comparisons, the basis build and the
// dispatch) but not MSVC's exact instruction schedule (recorded in
// partial.txt).
void __stdcall FUN_010551b0(void* param_1, float* param_2)
{
    Obj* tool = (Obj*)param_1;
    Vec3 old = tool->mVec154;
    Vec3 nw;
    nw.x = param_2[0];
    nw.y = param_2[1];
    nw.z = param_2[2];
    tool->mVec160 = nw;

    if (!tool->mpUnk16c)
        return;

    const float kZero = 0.0f;
    bool oldNonZero = (old.x != kZero || old.y != kZero || old.z != kZero);
    bool newNonZero = (nw.x != kZero || nw.y != kZero || nw.z != kZero);
    bool changed = (old.x != nw.x || old.y != nw.y || old.z != nw.z);
    if (!(oldNonZero && newNonZero && changed))
        return;

    XformMsg msg;
    ((XformMsgObj*)&msg)->construct();
    msg.mFlags |= 4;
    msg.mCount++;
    msg.mVec = old;

    // unit direction of the aim change, falling back to an orthogonal of the
    // old vector when the two are (nearly) coincident.
    Vec3 unitOld;
    FUN_00449c20(&unitOld.x, &old.x);
    Vec3 delta;
    delta.x = nw.x - old.x;
    delta.y = nw.y - old.y;
    delta.z = nw.z - old.z;
    float len2 = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
    Vec3 dir;
    if (len2 <= 1.5258789e-05f) {
        Vec3 ortho;
        FUN_006985b0(&ortho.x, &unitOld.x);
        FUN_00449c20(&dir.x, &ortho.x);
    } else {
        FUN_00449c20(&dir.x, &delta.x);
    }

    // right = dir x unitOld, up = unitOld x right, basis = {right, up, dir}
    Vec3 right;
    right.x = dir.y * unitOld.z - dir.z * unitOld.y;
    right.y = dir.z * unitOld.x - dir.x * unitOld.z;
    right.z = dir.x * unitOld.y - dir.y * unitOld.x;
    Vec3 up;
    up.x = unitOld.y * right.z - unitOld.z * right.y;
    up.y = unitOld.z * right.x - unitOld.x * right.z;
    up.z = unitOld.x * right.y - unitOld.y * right.x;

    msg.mBasis[0] = right.x; msg.mBasis[1] = right.y; msg.mBasis[2] = right.z;
    msg.mBasis[3] = up.x;    msg.mBasis[4] = up.y;    msg.mBasis[5] = up.z;
    msg.mBasis[6] = dir.x;   msg.mBasis[7] = dir.y;   msg.mBasis[8] = dir.z;

    msg.mFlags |= 2;
    msg.mCount++;
    ((VfnV)tool->mpUnk16c->mpVtbl->mSlots[kV18])(tool->mpUnk16c, &msg);
}

// ---------------------------------------------------------------------------
// @ 0x010543e0
// SP::LaunchProjectile(cSPSpaceToolData*, int*).  A 1367-byte routine built
// from long SSE dot/normalise chains plus a quaternion -> matrix conversion.
// The original's register allocation and SSE scheduling are not reproducible
// from C++ source, so this is a structural reconstruction of the control flow
// and the observable calls (recorded in partial.txt).
void __stdcall LaunchProjectile(void* param_1, int* param_2)
{
    Obj* tool = (Obj*)param_1;

    // 1. projectile-motion hash -> discrete kind 0..0x10
    int kind = 0;
    {
        int h = ((SpaceTool*)tool)->Get07();
        switch (h) {
        case 0x1d128dd5:      kind = 4;   break;
        case (int)0xd1ed94c1: kind = 0xb; break;
        case (int)0x87fbadc9: kind = 0xd; break;
        case (int)0xcb738c11: kind = 10;  break;
        case 0x188b10a2:      kind = 0xf; break;
        case 0x229300a9:      kind = 0xe; break;
        case 0x543f8e29:      kind = 0xc; break;
        case 0x732ed233:      kind = 0x10; break;
        default:              kind = 0;   break;
        }
    }

    // 2. spread / jitter scalars fed to the charge object.
    float base = ((SpaceTool*)tool)->Get01();
    float spread = (base - 1.0f) * tool->mF14c + 1.0f;
    float jitter = ((SpaceTool*)tool)->Get02(spread);
    ((SpaceTool*)tool)->Get0b();
    ((ChargeTool*)tool)->Spread(jitter);
    void* vfx = FUN_011e0810();
    (void)vfx;

    // 3. projectile angle (degrees -> radians -> half-angle) feeds the
    //    orientation-frame / quaternion build that the original then reduces
    //    to a modified push vector.
    float angle = ((SpaceTool*)tool)->Get09() * 0.017453292f * 0.5f;
    (void)angle;

    float push[3];
    push[0] = tool->mVec154.x;
    push[1] = tool->mVec154.y;
    push[2] = tool->mVec154.z;
    if (((SpaceTool*)tool)->Get06() && param_2)
        FUN_00cc0870(push[0], param_2, push);
    else
        FUN_00cb7c20(push, 0);
}