// Slice s00cc3220 - SporeApp 0x00cc3220..0x00cc3f40 (projectile view region).
// All functions are __thiscall with `this` in ecx unless noted otherwise.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <wchar.h>
#include <string.h>

typedef unsigned int  uint;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// ---- externals ---------------------------------------------------------------
void __cdecl EAFree(void* p);                        // 0x00f47380  operator delete[]
void* __cdecl EANew(int size, const char* name, int, int, int, int);  // 0x00f473a0
void* __cdecl GetCurrentGameMode();                                   // 0x00b5b800
void  __cdecl FUN_00cf74c0();                                         // 0x00cf74c0
void  __cdecl FUN_00cf74f0();                                         // 0x00cf74f0
u8    __cdecl FUN_00cf1540();                                         // 0x00cf1540
u8    __cdecl FUN_00c8e7c0();                                         // 0x00c8e7c0
void  __cdecl FUN_00c8b130(u32 kind, int a, int b);                   // 0x00c8b130
void  __cdecl FUN_00c88a00(u32 a, float b);                           // 0x00c88a00
void  __cdecl FUN_00c8ad30(int a, int b);                             // 0x00c8ad30
int   __cdecl FUN_00b25f40(u32 a);                                    // 0x00b25f40
void  __cdecl NounManager(u32 a);                                     // 0x00b3d300
u32   __cdecl FUN_00c9c2b0();                                         // 0x00c9c2b0
int   __cdecl FUN_00cb37c0();                                         // 0x00cb37c0
void  __cdecl FUN_00434040();                                         // 0x00434040
void* __cdecl GonzagoModelWorld();                                    // 0x00b3d520
void  __cdecl FUN_00cb5d80(void* a, void* b);                         // 0x00cb5d80
void  __cdecl FUN_00cb5e10(void* a, void* b);                         // 0x00cb5e10
void  __cdecl FUN_00cb5450(void* a, void* b);                         // 0x00cb5450
float __cdecl FUN_0104bdb0();                                         // 0x0104bdb0
void* __cdecl SP_Matrix3FromFacingAndUp(void* out, void* a, void* b); // 0x0041cb40
float* __cdecl SP_Matrix3FromQuaternion(void* out, const void* q);    // 0x0059c190
void* __cdecl FUN_00b894a0(float* v);                                 // 0x00b894a0

// ---- vtable-slot call helpers -----------------------------------------------
static inline void* VT_B8_1(void* p, int a) {
    return ((void* (__thiscall*)(void*, int))*((void***)*(void**)p + 0xb8 / 4))(p, a);
}
static inline void VT_44_3(void* p, int a, float* b, int c) {
    ((void (__thiscall*)(void*, int, float*, int))*((void***)*(void**)p + 0x44 / 4))(p, a, b, c);
}
static inline void VT_30_1(void* p, int a) {
    ((void (__thiscall*)(void*, int))*((void***)*(void**)p + 0x30 / 4))(p, a);
}
static inline void VT_18_1(void* p, void* a) {
    ((void (__thiscall*)(void*, void*))*((void***)*(void**)p + 0x18 / 4))(p, a);
}
static inline void VT_20_1(void* p, void* a) {
    ((void (__thiscall*)(void*, void*))*((void***)*(void**)p + 0x20 / 4))(p, a);
}
static inline void VT_24_1(void* p, void* a) {
    ((void (__thiscall*)(void*, void*))*((void***)*(void**)p + 0x24 / 4))(p, a);
}
static inline int VT_0C_1(void* p, int a) {
    return ((int (__thiscall*)(void*, int))*((void***)*(void**)p + 0x0c / 4))(p, a);
}
static inline void* VT_0C_0(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0x0c / 4))(p);
}
static inline void* VT_0C_3(void* p, int a, int b, int c) {
    return ((void* (__thiscall*)(void*, int, int, int))*((void***)*(void**)p + 0x0c / 4))(p, a, b, c);
}
static inline void* VT_18_0(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0x18 / 4))(p);
}
static inline void* VT_5C_1(void* p, int a) {
    return ((void* (__thiscall*)(void*, int))*((void***)*(void**)p + 0x5c / 4))(p, a);
}
static inline void VT_44_1(void* p, void* a, void* b) {
    ((void (__thiscall*)(void*, void*, void*))*((void***)*(void**)p + 0x44 / 4))(p, a, b);
}
static inline void VT_A8_2(void* p, void* a, void* b) {
    ((void (__thiscall*)(void*, void*, void*))*((void***)*(void**)p + 0xa8 / 4))(p, a, b);
}
static inline int VT_AC_0(void* p) {
    return ((int (__thiscall*)(void*))*((void***)*(void**)p + 0xac / 4))(p);
}
static inline int VT_4C_0(void* p) {
    return ((int (__thiscall*)(void*))*((void***)*(void**)p + 0x4c / 4))(p);
}
static inline float VT_34_F(void* p) {
    return ((float (__thiscall*)(void*))*((void***)*(void**)p + 0x34 / 4))(p);
}
static inline void* VT_E0_0(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0xe0 / 4))(p);
}
static inline void* VT_6C_0(void* p) {
    return ((void* (__thiscall*)(void*))*((void***)*(void**)p + 0x6c / 4))(p);
}
static inline void* PM_DirToSurface(float* out, const float* dir) {
    return ((void* (__thiscall*)(float*, const float*))0x00b815a0)(out, dir);
}
static inline void* PM_BuildSurfaceOrientation(float* a, float* b) {
    return ((void* (__thiscall*)(float*, float*))0x00b7f190)(a, b);
}
static inline void PM_Construct(void* pm, float* out, float* dir) {
    ((void (__thiscall*)(void*, float*, float*))0x00b3d350)(pm, out, dir);
}

// ---- types -------------------------------------------------------------------
struct Vector3 { float x, y, z; };

struct Matrix33 {
    float m[9];
    void Ctor(const void* init);                     // 0x0041cb40
};

// Render/effect update payload handed to effect vtable slot 0x18 / 0x44.
// Layout approximated from the decompile (position / flags / orientation / scale).
struct EffectUpdate {
    Vector3  mPosition;                              // 0x00
    u32      mFlags;                                 // 0x0c  bit0 pos, bit1 orient, bit2 scale
    u8       mCount;                                 // 0x10
    char     pad11[3];
    Matrix33 mOrientation;                           // 0x14
    float    mScale;                                 // 0x38
};

struct cSPSpaceToolData {
    u8 IsInContext();                                // 0x0104cb70
};

struct cSpatialObject {
    void* mpVtbl;                                    // 0x000
    char  pad004[0x134 - 0x004];
    void* mpSpaceToolData;                           // 0x134  space-tool bound to this object
    void  DestroyAllEffects(int a);                  // 0x00c8b0a0
    u8    GetEffect(int key);                        // 0x00c88910
    void* GetEffectObject(int key);                  // 0x00c888e0
    u64   FUN_00cb41b0();                            // 0x00cb41b0
    u64   FUN_00cb4340();                            // 0x00cb4340
    void* FUN_00c888e0(int a);                       // 0x00c888e0
};

// Sub-object reached through vtable slot 0xb8 / 0x0c of the view's object.
struct cSubObject {
    char  pad000[0x034];
    void* mpOwner;                                   // 0x034  receiver used by the owner's slot 0xa8/0xac
    char  pad038[0x504 - 0x038];
    void* mpTool;                                    // 0x504  current tool instance
};

// Tool instance (slot 0x0c of the sub-object).
struct cToolInstance {
    char    pad000[0x544];
    int     mState;                                  // 0x544  1 = on ground, 2 = in air
    char    pad548[0x58c - 0x548];
    Vector3 mPosition;                               // 0x58c  world position
};

// Object returned by FUN_00b894a0 (terrain query result).
struct cTerrainObject {
    char  pad000[0x25c];
    float mHeight;                                   // 0x25c  surface height for the effect
};

// Object returned by FUN_00b25f40.
struct cNounObject {
    char  pad000[0x0cc];
    u32   mEffectParam;                              // 0x0cc
};

// Refcounted model instance returned by the world's slot-0x0c lookup.
struct cModelInstance {
    void* mpVtbl;                                    // 0x000
    u32   mFlags;                                    // 0x004
    char  pad008[0x040 - 0x008];
    int   mRefCount;                                 // 0x040  model reference counter
};

struct cSpatialObjectView {
    void* mpVtbl;                                    // 0x000
    char  pad004[0x0c - 0x04];
    void* mpObject;                                  // 0x00c
    char  pad010[0x34 - 0x10];
    u8    mInGameMode;                               // 0x034  applied game-mode flag
    u8    mModeVariant;                              // 0x035  secondary mode flag

    void  ctor();                                    // 0x00e92af0
    void  BaseDtor();                                // 0x00e92660
    void  HandleSimulationUpdate(u32 fbits, u32 p);  // 0x00e92ca0

    void* FUN_00cc36d0(u8 flag);                     // 0x00cc36d0
    void  FUN_00cc3490(u32 fbits, u32 p);            // 0x00cc3490
    void  FUN_00cc3220(u32 fbits, u32 f2);           // 0x00cc3220
    void  FUN_00cc3950(u32 fbits, u32 f2);           // 0x00cc3950
    void  FUN_00cc3c30(u32 fbits, u32 f2);           // 0x00cc3c30
    void  FUN_00cc3f40(u32 fbits, u32 f2);           // 0x00cc3f40
};

struct cResourceProjectileView : cSpatialObjectView {
    static void* MakeView(cSpatialObject* p);        // 0x00cc3380
};

struct cSpaceDefenseMissileView : cSpatialObjectView {
    static void* MakeView(cSpatialObject* p);        // 0x00cc3570
};

struct cArtilleryProjectileView : cSpatialObjectView {
    static void* MakeView(cSpatialObject* p);        // 0x00cc3730
};

// =============================================================================
// @ 0x00cc36d0
void* cSpatialObjectView::FUN_00cc36d0(u8 flag)
{
    mpVtbl = (void*)0x14767d0;
    if (mpObject) {
        void* r = VT_B8_1(mpObject, 0x24630ce);
        if (r) {
            void* t = ((cSpatialObject*)r)->mpSpaceToolData;
            if (t) {
                if (((cSPSpaceToolData*)t)->IsInContext())
                    ((cSpatialObject*)mpObject)->DestroyAllEffects(0);
            }
        }
    }
    BaseDtor();
    if (flag & 1)
        EAFree(this);
    return this;
}

// @ 0x00cc3490
void cSpatialObjectView::FUN_00cc3490(u32 fbits, u32 p)
{
    HandleSimulationUpdate(fbits, p);
    if (!mpObject)
        return;
    void* r = VT_B8_1(mpObject, 0x5776a28);
    if (!r)
        return;
    u64 v1 = ((cSpatialObject*)r)->FUN_00cb4340();
    if (!(v1 > 0))
        return;
    void* h = ((cSpatialObject*)mpObject)->FUN_00c888e0(0);
    if (!h)
        return;
    u64 v = ((cSpatialObject*)r)->FUN_00cb4340();
    float fr = 1.0f - (float)v * *(float*)0x13f999c;
    VT_44_3(h, 4, &fr, 1);
}

// =============================================================================
// @ 0x00cc3220
// SP::cCulturalProjectileView::HandleSimulationUpdate - mirrors the in-game flag
// into the owned effect and pushes the "settling" scalar to effect slot 0x44.
void cSpatialObjectView::FUN_00cc3220(u32 fbits, u32 f2)
{
    HandleSimulationUpdate(fbits, f2);

    void* r = 0;
    if (mpObject)
        r = VT_B8_1(mpObject, 0x4f76f08);

    u8 inGame = 0;
    if (GetCurrentGameMode() == (void*)0x1654c04) {
        FUN_00cf74c0();
        FUN_00cf74f0();
        if (FUN_00cf1540())
            inGame = 1;
    }
    if (inGame != mInGameMode) {
        mInGameMode = inGame;
        cSpatialObject* o = (cSpatialObject*)mpObject;
        if (o->GetEffect(0))
            VT_30_1(o->GetEffectObject(0), (int)inGame);
    }

    if (r && ((cSpatialObject*)r)->FUN_00cb41b0() != 0) {
        void* e = ((cSpatialObject*)mpObject)->GetEffectObject(0);
        if (e) {
            u64 v = ((cSpatialObject*)r)->FUN_00cb41b0();
            float f = 1.0f - (float)v * *(float*)0x13f999c;
            if (f < 0.0f)
                f = 0.0f;
            if (f > 1.0f)
                f = 1.0f;
            VT_44_3(e, 4, &f, 1);
        }
    }
}

// =============================================================================
// @ 0x00cc3380
// SP::cResourceProjectileView::MakeView - allocates the 0x34-byte view, hooks the
// vtable, forwards the parent handle and configures the impact effect.
void* cResourceProjectileView::MakeView(cSpatialObject* p)
{
    cResourceProjectileView* v = (cResourceProjectileView*)
        EANew(0x34, "Simulator/cResourceProjectileView", 0, 0, 0, 0);
    if (v) {
        v->ctor();
        v->mpVtbl = (void*)0x14607a8;
    }
    VT_24_1(v, p);

    u32 kind = 0x4aad8baf;
    if (p) {
        void* hit = (void*)VT_0C_1(p, 0x5776a28);
        if (hit && FUN_00c8e7c0())
            kind = 0xf95108a3;
    }
    FUN_00c8b130(kind, 0, 0);
    FUN_00c88a00(0, 1024.0f);
    void* e = ((cSpatialObject*)v)->GetEffectObject(0);
    if (e) {
        int id = VT_4C_0(p);
        NounManager(id);
        if (FUN_00b25f40(id)) {
            EffectUpdate blk;
            blk.mFlags = 0;
            blk.mCount = 0;
            VT_44_3(e, 5, (float*)&blk, 3);
        }
    }
    return v;
}

// =============================================================================
// @ 0x00cc3570
// SP::cSpaceDefenseMissileView::MakeView.
// NOTE: the two leading effect-list / allocator-name fields the original clears
// right after the vtable store are not reconstructed (their offsets are unknown).
void* cSpaceDefenseMissileView::MakeView(cSpatialObject* p)
{
    cSpaceDefenseMissileView* v = (cSpaceDefenseMissileView*)
        EANew(0x3c, "Simulator/cSpaceDefenseMissileView", 0, 0, 0, 0);
    if (v) {
        v->ctor();
        v->mpVtbl = (void*)0x1476804;
    }
    VT_24_1(v, p);

    cSubObject* sub = p ? (cSubObject*)VT_0C_1(p, 0x244d3c0) : 0;
    u32 kind = FUN_00c9c2b0();
    FUN_00c8b130(kind, 0, 0x56bb11a);
    FUN_00c88a00(0x56bb11a, 1024.0f);

    if (VT_AC_0(sub->mpOwner) != 0) {
        VT_24_1(v, p);
        return v;
    }
    void* world = GonzagoModelWorld();
    cModelInstance* model = (cModelInstance*)VT_0C_3(world, 0x2e81370, *(int*)0x0169aab0, 0);
    if (model) {
        // the model is refcounted; the counter is bumped while held
        model->mRefCount = model->mRefCount + 1;
    }
    // NOTE: the view's own slot-0x28 call with (world, model + 0x8, scratch + 0x18)
    // is not reconstructed (its argument layout could not be recovered).
    VT_A8_2(sub->mpOwner, model, world);
    if (model->mRefCount > 1) {
        model->mRefCount = model->mRefCount - 1;
        return v;
    }
    ((void (__thiscall*)(void*, u32))((void***)model->mpVtbl)[0x170 / 4])(model, model->mFlags >> 31);
    return v;
}

// =============================================================================
// @ 0x00cc3730
// SP::cArtilleryProjectileView::MakeView - three-way configuration driven by the
// projectile sub-type queried from FUN_00cb37c0.
void* cArtilleryProjectileView::MakeView(cSpatialObject* p)
{
    cArtilleryProjectileView* v = (cArtilleryProjectileView*)
        EANew(0x34, "Simulator/cArtilleryProjectileView", 0, 0, 0, 0);
    if (v) {
        v->ctor();
        v->mpVtbl = (void*)0x1460608;
    }
    VT_24_1(v, p);

    if (!p)
        return v;
    cSubObject* sub = (cSubObject*)VT_0C_1(p, 0x1428a48);
    if (!sub)
        return v;

    int mode = FUN_00cb37c0();
    if (mode == 2) {
        FUN_00c8b130(0x5cd27dc5, 0, 0x46e9287);
        void* e = ((cSpatialObject*)v)->GetEffectObject(0x46e9287);
        if (e) {
            void* q = VT_18_0(sub->mpTool);
            if (q) {
                void* m = VT_5C_1(q, 0xce9f6639);
                if (m) {
                    FUN_00434040();
                    EffectUpdate blk;
                    blk.mFlags = 0;
                    blk.mCount = 0;
                    VT_20_1(e, &blk);
                    blk.mScale = VT_34_F(sub->mpOwner);
                    VT_18_1(e, &blk);
                    VT_44_3(e, 5, (float*)VT_E0_0(m), 3);
                }
            }
        }
        return v;
    }
    if ((u32)(mode - 3) > 1) {
        FUN_00c8b130(0x364ea7b9, 0, 0);
        return v;
    }
    u32 kind = (FUN_00cb37c0() == 3) ? 0x91a80211 : 0x6211b885;
    FUN_00c8b130(kind, 0, 0);
    if (VT_4C_0(sub) != -1) {
        u32 id = VT_4C_0(sub);
        NounManager(id);
        cNounObject* obj = (cNounObject*)FUN_00b25f40(id);
        if (obj) {
            EffectUpdate blk;
            blk.mFlags = obj->mEffectParam;
            blk.mCount = 0;
            void* e = ((cSpatialObject*)v)->GetEffectObject(0);
            if (e)
                VT_44_3(e, 5, (float*)&blk, 3);
        }
    }
    return v;
}

// =============================================================================
// @ 0x00cc3950
// SP::cDefaultToolProjectileView::HandleSimulationUpdate.
void cSpatialObjectView::FUN_00cc3950(u32 fbits, u32 f2)
{
    HandleSimulationUpdate(fbits, f2);

    u8 inGame = 0;
    if (GetCurrentGameMode() == (void*)0x1654c04) {
        FUN_00cf74c0();
        FUN_00cf74f0();
        if (FUN_00cf1540())
            inGame = 1;
    }
    if (inGame != mInGameMode) {
        mInGameMode = inGame;
        cSpatialObject* o = (cSpatialObject*)mpObject;
        if (o->GetEffect(0x500f162))
            VT_30_1(o->GetEffectObject(0x500f162), (int)inGame);
        if (o->GetEffect(0x6565ae1))
            VT_30_1(o->GetEffectObject(0x6565ae1), (int)inGame);
    }

    if (((cSpatialObject*)mpObject)->GetEffect(0x6565ae1)) {
        void* sub = VT_0C_0(this);
        if (sub) {
            cToolInstance* tool = (cToolInstance*)VT_0C_1(sub, 0x24270c4);
            if (tool) {
                float tmp[3];
                tmp[0] = tool->mPosition.x;
                tmp[1] = tool->mPosition.y;
                tmp[2] = tool->mPosition.z;

                EffectUpdate blk;
                blk.mFlags = 0;
                blk.mCount = 0;
                blk.mOrientation.Ctor((void*)0x0169b024);
                float out[4];
                PM_Construct(out, out, tmp);
                float* surf = (float*)PM_DirToSurface(out, tmp);
                blk.mPosition.x = surf[0];
                blk.mPosition.y = surf[1];
                blk.mPosition.z = surf[2];
                blk.mFlags |= 4;
                blk.mCount = (u8)(blk.mCount + 1);
                float* orient = (float*)PM_BuildSurfaceOrientation(tmp, out);
                SP_Matrix3FromQuaternion(out, orient);
                blk.mFlags |= 2;
                blk.mCount = (u8)(blk.mCount + 1);
                blk.mScale = FUN_0104bdb0();
                blk.mCount = (u8)(blk.mCount + 1);
                if (mModeVariant) {
                    float v[3];
                    v[0] = tool->mPosition.x;
                    v[1] = tool->mPosition.y;
                    v[2] = tool->mPosition.z;
                    cTerrainObject* terrain = (cTerrainObject*)FUN_00b894a0(v);
                    if (terrain) {
                        void* m = VT_6C_0(terrain);
                        blk.mScale = ((cTerrainObject*)m)->mHeight;
                        blk.mCount = (u8)(blk.mCount + 1);
                    }
                }
                void* e = ((cSpatialObject*)mpObject)->GetEffectObject(0x6565ae1);
                VT_18_1(e, &blk);
            }
        }
    }

    if (mpObject) {
        cToolInstance* tool = (cToolInstance*)VT_B8_1(mpObject, 0x24270c4);
        if (tool && tool->mState == 1) {
            FUN_00c8ad30(0x500f162, 0);
            FUN_00c8ad30(0x6565ae1, 1);
        }
    }
}

// =============================================================================
// @ 0x00cc3c30
// SP::cDeepSpaceProjectileView::HandleSimulationUpdate.
// NOTE: the projectile transform returned by FUN_00cb5450 is approximated by two
// local vectors (the original passes two scratch buffers on the caller frame).
void cSpatialObjectView::FUN_00cc3c30(u32 fbits, u32 f2)
{
    HandleSimulationUpdate(fbits, f2);

    if (mpObject) {
        cToolInstance* tool = (cToolInstance*)VT_B8_1(mpObject, 0x24270c4);
        if (tool && tool->mState == 2)
            FUN_00c8ad30(0, 0);
    }
    if (mpObject)
        VT_B8_1(mpObject, 0x24270c6);

    float pos[3];
    float dir[3];
    FUN_00cb5450(pos, dir);

    void* e1 = ((cSpatialObject*)mpObject)->GetEffectObject(1);
    if (e1) {
        EffectUpdate blk;
        blk.mFlags = 0;
        blk.mCount = 0;
        blk.mPosition.x = pos[0];
        blk.mPosition.y = pos[1];
        blk.mPosition.z = pos[2];
        blk.mOrientation.m[0] = dir[0];
        blk.mOrientation.m[1] = dir[1];
        blk.mOrientation.m[2] = dir[2];
        VT_44_3(e1, 0xd, (float*)&blk, 6);
    }

    void* e2 = ((cSpatialObject*)mpObject)->GetEffectObject(2);
    if (e2) {
        float off[3];
        off[0] = dir[0] - pos[0];
        off[1] = dir[1] - pos[1];
        off[2] = dir[2] - pos[2];
        EffectUpdate blk;
        blk.mFlags = 0;
        blk.mCount = 0;
        blk.mPosition.x = pos[0];
        blk.mPosition.y = pos[1];
        blk.mPosition.z = pos[2];
        blk.mOrientation.Ctor((void*)0x0169b024);
        SP_Matrix3FromFacingAndUp(blk.mOrientation.m, off, pos);
        blk.mFlags |= 2;
        blk.mCount = (u8)(blk.mCount + 1);
        VT_18_1(e2, &blk);
    }

    void* e3 = ((cSpatialObject*)mpObject)->GetEffectObject(3);
    if (e3) {
        float surf[3];
        surf[0] = *(float*)0x0169b048;
        surf[1] = *(float*)0x0169b04c;
        surf[2] = *(float*)0x0169b050;
        EffectUpdate blk;
        blk.mFlags = 0;
        blk.mCount = 0;
        blk.mOrientation.Ctor((void*)0x0169b024);
        float out[4];
        PM_Construct(out, out, surf);
        float* p = (float*)PM_DirToSurface(out, surf);
        blk.mPosition.x = p[0];
        blk.mPosition.y = p[1];
        blk.mPosition.z = p[2];
        blk.mFlags |= 4;
        blk.mCount = (u8)(blk.mCount + 1);
        float* orient = (float*)PM_BuildSurfaceOrientation(dir, out);
        SP_Matrix3FromQuaternion(out, orient);
        blk.mFlags |= 2;
        blk.mCount = (u8)(blk.mCount + 1);
        VT_18_1(e3, &blk);
    }
}

// =============================================================================
// @ 0x00cc3f40
// SP::cDefaultAoEAreaView::HandleSimulationUpdate - drives the AoE marker effect
// from the area object orientation plus the current scale.
void cSpatialObjectView::FUN_00cc3f40(u32 fbits, u32 f2)
{
    HandleSimulationUpdate(fbits, f2);
    if (!mpObject)
        return;
    void* area = (void*)VT_B8_1(mpObject, 0x4167194);
    if (!area)
        return;
    void* e = ((cSpatialObject*)mpObject)->GetEffectObject(0x4178e6e);
    if (!e)
        return;

    float scratch[4];
    FUN_00cb5d80(scratch, scratch + 2);

    EffectUpdate blk;
    blk.mFlags = 0;
    blk.mCount = 0;
    blk.mPosition.x = scratch[0];
    blk.mPosition.y = scratch[1];
    blk.mPosition.z = scratch[2];
    blk.mOrientation.Ctor((void*)0x0169b024);
    float* q = (float*)SP_Matrix3FromQuaternion(blk.mOrientation.m, scratch + 1);
    for (int i = 0; i < 9; ++i)
        blk.mOrientation.m[i] = q[i];
    // NOTE: the final scale component comes from the AoE area object (offset not
    // reconstructed).
    blk.mFlags |= 4;
    blk.mCount = (u8)(blk.mCount + 1);
    VT_18_1(e, &blk);
}
