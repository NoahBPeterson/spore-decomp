// Slice s00bce1e0 -- Simulator cGameData / cBuilding / cCommunity helpers around
// 0x00bce1e0..0x00bcedff: the owner-removal teardown chains, the spatial /
// property-vector accessors, the cVarListSerializer read path, and the lazily
// built editor placeholder vectors.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (Simulator TU).
#include "types.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define VS(o, off)   (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)  ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1) \
    ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Vec3u   { u32 x, y, z; };

// ---------------------------------------------------------------------------
// Common engine types.
// ---------------------------------------------------------------------------
struct cGameNounManager {
    void* mVtbl;                  // +0
    void RemoveNoun(void* noun);  // 0x00b225d0
    void* CreateNoun(u32 id);     // 0x00b20c60
};

cGameNounManager* SP_NounManager();                          // 0x00b3d300
void* PropertyManager();                                    // 0x0067de30
bool  GetPropertyAsVector3(void* list, u32 id, void* out);  // 0x006a1110

// Sub-objects of cBuilding.
struct Sub34 {                       // +0x34
    void* mVtbl;                     // +0x00
    u8    d[0x64];
    void FUN_00c8b2e0();             // 0x00c8b2e0
    bool Read(void* stream);         // 0x00c88b00
    bool ReadBig(void* stream);      // 0x00c43c10
    void FUN_00c43f90(void);         // 0x00c43f90  (Shutdown)
    void FUN_00c421b0(void* p);      // 0x00c421b0
};
struct SubC4  { u8 d[0x3c]; };                              // +0xc4
struct Sub108 { u8 d[0x18]; void FUN_00ac0450(); };         // +0x108
struct Sub120 {                                             // +0x120
    u8 d[0xcc];
    void FUN_00bfc720();                                     // 0x00bfc720
    void FUN_00bfc470(u8 b);                                 // 0x00bfc470
};
struct Sub504 { u8 d[0x18]; void FUN_00ac0450(); };         // +0x504
struct Sub51C { u8 d[0x6c]; void FUN_00abf710(); };         // +0x51c
struct Sub588 {                                             // +0x588
    u8   d[0xf8];
    bool FUN_00bfc540(void* stream);                         // 0x00bfc540
    void FUN_00bfc720();                                     // 0x00bfc720
};
struct cToolData {
    bool FUN_0104bd50();         // 0x0104bd50
    void UseToolStop();          // 0x0104fa90
};
cToolData* __stdcall FUN_00b3d390(cToolData* p);   // 0x00b3d390

void FUN_00bcd480(void* p, float a, float b); // 0x00bcd480

// ---------------------------------------------------------------------------
// 0x00bce400 -- forward a constant pair of floats to FUN_00bcd480.
// ---------------------------------------------------------------------------
extern float g_f169c1b0;   // 0x0169c1b0
extern float g_f169c1b4;   // 0x0169c1b4

// @ 0x00bce400
void FUN_00bce400(void* param_1)
{
    FUN_00bcd480(param_1, g_f169c1b0, g_f169c1b4);
}

// ---------------------------------------------------------------------------
// The player-visible "building" object; only the fields touched here are named.
// ---------------------------------------------------------------------------
struct cCity;

// Types used by the editor-target helper (0x00bce660).
struct Sub508 {
    void* mVtbl;          // +0x000
    u8    d[0x614];       // +0x004 .. +0x618
    int   FUN_00vt10();   // vtable slot 0x10
};
struct RType660 {
    void*  mVtbl;         // +0x000
    u8     m04[0x504];    // +0x004 .. +0x508
    Sub508 m508;          // +0x508 .. +0xb20
    u32    mB20;          // +0xb20
};
struct cVt8Obj {
    void*    mVtbl;       // +0
    Vector3* FUN_00vt2c();    // vtable slot 0x2c
};
struct cCiv {
    void* mVtbl;
    void FUN_00bf02b0();      // 0x00bf02b0
};
struct cCity {
    void* mVtbl;
    cCiv* GetCivilization(int uVar5, Vector3 v);   // 0x00bd9bf0
    void  FUN_00c00b00(int a, int b);              // 0x00c00b00
};

struct cBuilding {
    u8             m00[0x2c];
    void*          mpRef2c;      // +0x2c
    u8             m30[0x04];
    Sub34          m34;          // +0x34 .. +0x9c
    u8             m9c[0x28];    // +0x9c .. +0xc4
    SubC4          mC4;          // +0xc4 .. +0x100
    cCity*         mp100;        // +0x100  (cCity)
    u8             m104[0x04];
    Sub108         m108;         // +0x108 .. +0x120
    Sub120         m120;         // +0x120 .. +0x1ec
    void*          mp1ec;        // +0x1ec  (space inventory)
    void*          mp1f0;        // +0x1f0  (owner city)
    u8             m1f4[0x30];   // +0x1f4 .. +0x224
    u32            m224;         // +0x224
    u8             m228[0xe4];   // +0x228 .. +0x30c
    u8             m30c;         // +0x30c
    u8             m30d[0x1f7];  // +0x30d .. +0x504
    Sub504         m504;         // +0x504 .. +0x51c
    Sub51C         m51C;         // +0x51c .. +0x588
    Sub588         m588;         // +0x588 .. +0x680
    void*          mp680;        // +0x680
    u8             m684[0x04];
    void*          mp688;        // +0x688
    void*          mp68c;        // +0x68c
    cToolData*     mp690;        // +0x690
    cToolData*     mp694;        // +0x694
    cToolData*     mp698;        // +0x698
    cToolData*     mp69c;        // +0x69c
    void*          mp6a0;        // +0x6a0
    void*          mp6a4;        // +0x6a4

    float GetCost();                       // 0x00bce9a0
    int   FUN_00bce5d0();                  // 0x00bce5d0
    void  FUN_00bce970();                  // 0x00bce970
    void  FUN_00bce9b0();                  // 0x00bce9b0
    void  SetOwnerCity1(void* param_2);    // 0x00bce8e0
    void  FUN_00bcea10(u32 param_2);       // 0x00bcea10
    void  FUN_00bce660(void* param_2);     // 0x00bce660
    void  FUN_00bce1e0();                  // 0x00bce1e0
    void  SetGameDataOwner2(void* p);      // 0x00b18550
    void  FUN_00bcd4e0(u32 param_2);       // 0x00bcd4e0
};

// ---------------------------------------------------------------------------
// 0x00bce5d0 -- delegate to m100->vt[0x4c], or -1 when absent.
// ---------------------------------------------------------------------------
// @ 0x00bce5d0
int cBuilding::FUN_00bce5d0()
{
    void* p = mp100;
    if (p == 0)
        return -1;
    return VC0(int, p, 0x4c);
}

// ---------------------------------------------------------------------------
// 0x00bce5f0 -- load the model, then pull the model-key vector property.
// (this is the cSpatialObject sub-object; its own layout is used here)
// ---------------------------------------------------------------------------
struct cSpatialObject {
    void* mVtbl;        // +0x00
    u8    m04[0x98];    // +0x04 .. +0x9c
    void* mp9c;         // +0x9c
    u8    mA0[0x580];   // +0xa0 .. +0x620
    Vec3u m620;         // +0x620
    bool LoadModel(u32 id);        // 0x00c8a550
    bool FUN_00bce5f0(u32 param_2);
};

// @ 0x00bce5f0
bool cSpatialObject::FUN_00bce5f0(u32 param_2)
{
    if (LoadModel(param_2)) {
        void* p = mp9c;
        void* q = *(void**)((char*)p + 0x90);
        if (q != 0) {
            Vec3u v;
            if (GetPropertyAsVector3(q, 0x475062du, &v))
                m620 = v;
        }
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00bce9a0 -- GetCost: notify and report zero.
// ---------------------------------------------------------------------------
// @ 0x00bce9a0
float cBuilding::GetCost()
{
    VC0(void, this, 0x4c);
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00bce9b0 -- tear down the spatial / property sub-objects and the refs.
// ---------------------------------------------------------------------------
// @ 0x00bce9b0
void cBuilding::FUN_00bce9b0()
{
    m120.FUN_00bfc720();
    m108.FUN_00ac0450();
    m34.FUN_00c8b2e0();

    void* p = mp1f0;
    if (p != 0) {
        mp1f0 = 0;
        VC0(void, p, 4);
    }
    if (mp1ec != 0)
        SP_NounManager()->RemoveNoun(mp1ec);
}

// ---------------------------------------------------------------------------
// 0x00bce1e0 -- RemoveOwner: stop tools, drop the refs, shut the loco down.
// ---------------------------------------------------------------------------
// @ 0x00bce1e0
void cBuilding::FUN_00bce1e0()
{
    if (mp690 != 0 && mp690->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp690);
        r->UseToolStop();
    }
    if (mp694 != 0 && mp694->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp694);
        r->UseToolStop();
    }
    if (mp698 != 0 && mp698->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp698);
        r->UseToolStop();
    }
    if (mp69c != 0 && mp69c->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp69c);
        r->UseToolStop();
    }

    {
        void* p = mp68c;
        if (p != 0) {
            mp68c = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp690;
        if (p != 0) {
            mp690 = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp694;
        if (p != 0) {
            mp694 = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp698;
        if (p != 0) {
            mp698 = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp69c;
        if (p != 0) {
            mp69c = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp6a4;
        if (p != 0) {
            mp6a4 = 0;
            VC0(void, p, 0x64);
        }
    }

    if (mp680 != 0) {
        if (VC0(bool, mp680, 0x10))
            VC1(void, mp680, 0xc, void*, 0);
    }
    {
        void* p = mp680;
        if (p != 0) {
            mp680 = 0;
            VC0(void, p, 4);
        }
    }

    if (mp6a0 != 0) {
        SP_NounManager()->RemoveNoun(mp6a0);
        void* p = mp6a0;
        mp6a0 = 0;
        if (p != 0)
            VC0(void, p, 4);
    }
    {
        void* p = mp688;
        mp688 = 0;
        if (p != 0)
            VC0(void, p, 4);
    }

    m588.FUN_00bfc720();
    m504.FUN_00ac0450();
    m51C.FUN_00abf710();

    {
        void* p = mpRef2c;
        if (p != 0) {
            mpRef2c = 0;
            VC0(void, p, 4);
        }
    }

    m34.FUN_00c43f90();
}

// ---------------------------------------------------------------------------
// 0x00bce8e0 -- SetOwnerCity1: set the owner city and the space inventory.
// ---------------------------------------------------------------------------
// @ 0x00bce8e0
void cBuilding::SetOwnerCity1(void* param_2)
{
    SetGameDataOwner2(param_2);

    void* oldCity = mp1f0;
    if (param_2 != oldCity) {
        if (param_2 != 0)
            VC0(void, param_2, 0);
        mp1f0 = param_2;
        if (oldCity != 0)
            VC0(void, oldCity, 4);
    }

    void* noun = SP_NounManager()->CreateNoun(0x21ffa3fu);

    void* inv;
    if (noun != 0)
        inv = VC1(void*, noun, 0xc, u32, 0xb075dec5u);
    else
        inv = 0;

    void* oldInv = mp1ec;
    if (inv != oldInv) {
        if (inv != 0)
            VC0(void, inv, 0);
        mp1ec = inv;
        if (oldInv != 0)
            VC0(void, oldInv, 4);
    }
}

// ---------------------------------------------------------------------------
// 0x00bcea10 -- install an argument and flag the object as dirty.
// ---------------------------------------------------------------------------
// @ 0x00bcea10
void cBuilding::FUN_00bcea10(u32 param_2)
{
    FUN_00bcd4e0(param_2);
    m30c = 1;
}

// ---------------------------------------------------------------------------
// 0x00bce970 -- propagate the current editor object to the +0x120 sub-object.
// ---------------------------------------------------------------------------
struct RType { u8 m00; u8 m01; };
struct F3F950Target {
    RType* FUN_00f3f950(void* arg);   // 0x00f3f950
};
struct GlobalsTable {
    u8              m00[0x74];
    F3F950Target*   mp74;             // +0x74
};
extern GlobalsTable* g_globals16c7aa4;   // 0x016c7aa4

// @ 0x00bce970
void cBuilding::FUN_00bce970()
{
    RType* r = g_globals16c7aa4->mp74->FUN_00f3f950(this);
    if (r != 0)
        m120.FUN_00bfc470(r->m01);
}

// ---------------------------------------------------------------------------
// 0x00bce8b0 -- cCommunity: forward an argument to the +0x66c time object.
// ---------------------------------------------------------------------------
struct cCommunity {
    u8    m00[0x66c];
    void* mp66c;                     // +0x66c
    void  func54h(void* param_2);    // 0x00c88670
    void  FUN_00bce8b0(u32 param_2);
};

// @ 0x00bce8b0
void cCommunity::FUN_00bce8b0(u32 param_2)
{
    func54h((void*)param_2);
    void* p = mp66c;
    if (p != 0)
        VC1(void, (char*)p + 0x70, 0x38, u32, param_2);
}

// ---------------------------------------------------------------------------
// 0x00bce660 -- pick the best target object and tell the owner city about it.
// ---------------------------------------------------------------------------
// @ 0x00bce660
void cBuilding::FUN_00bce660(void* param_2)
{
    bool bVar1 = false;
    int uVar5 = -1;

    if (param_2 == 0)
        return;

    RType660* r = VC1(RType660*, param_2, 0x5c, u32, 0x137e8e0u);
    if (r != 0 && r->mB20 == 0) {
        bVar1 = true;
        uVar5 = VC0(int, &r->m508, 0x10);
    }

    void* p = VC1(void*, param_2, 0x5c, u32, 0xb033b403u);
    if (p != 0) {
        bVar1 = true;
        uVar5 = VC0(int, p, 0x4c);
    }

    void* q = VC1(void*, param_2, 0x5c, u32, 0xd0036e08u);
    if (q != 0) {
        uVar5 = VC0(int, q, 0x4c);
    } else if (!bVar1) {
        return;
    }

    cVt8Obj* r2 = VC0(cVt8Obj*, param_2, 8);
    Vector3* pv = VC0(Vector3*, r2, 0x2c);

    cCiv* civ = mp100->GetCivilization(uVar5, *pv);
    civ->FUN_00bf02b0();
    mp100->FUN_00c00b00(0, uVar5);
}

// ---------------------------------------------------------------------------
// 0x00bcea30 -- SP::GetPropertyT_DO_NOT_USE<float>: fetch a variant property.
// ---------------------------------------------------------------------------
extern float g_f15d9c6c;   // 0x015d9c6c

struct cVariant {
    void* mPtr;         // +0x000
    u8    m04[0x0c];    // +0x004 .. +0x010
    u8    mFlags;       // +0x010
    u8    m11;          // +0x011
    u16   mType;        // +0x012
};

// @ 0x00bcea30
float FUN_00bcea30(u32 a, u32 b, u32 c, float def)
{
    void* local = 0;
    void* pm = PropertyManager();
    if (local != 0) {
        void* old = local;
        local = 0;
        VC0(void, old, 4);
    }
    if (VC3(bool, pm, 0x2c, u32, a, u32, b, void**, &local)) {
        cVariant* out;
        if (VC2(bool, local, 0x24, u32, c, cVariant**, &out)) {
            u16 t = out->mType;
            float* pf;
            if (t == 0xd || t == 0x10) {
                if ((out->mFlags & 0x30) != 0)
                    pf = (float*)out->mPtr;
                else
                    pf = (t != 0) ? (float*)out : 0;
            } else {
                pf = &g_f15d9c6c;
            }
            float f = *pf;
            if (local != 0)
                VC0(void, local, 4);
            return f;
        }
    }
    if (local != 0)
        VC0(void, local, 4);
    return def;
}

// ---------------------------------------------------------------------------
// 0x00bcebc0 / 0x00bcec50 -- lazily build the two editor placeholder vectors.
// ---------------------------------------------------------------------------
extern Vector3 g_v756d754;   // 0x0156d754
extern Vector3 g_v756d760;   // 0x0156d760

// @ 0x00bcebc0
Vector3* FUN_00bcebc0()
{
    if (g_v756d754.x == -1.0f) {
        void* local = 0;
        void* pm = PropertyManager();
        if (local != 0) {
            void* old = local;
            local = 0;
            VC0(void, old, 4);
        }
        if (VC3(bool, pm, 0x2c, u32, 0x4529f96fu, u32, 0x40636200u,
                void**, &local))
            GetPropertyAsVector3(local, 0x48f5b53u, &g_v756d754);
        if (local != 0)
            VC0(void, local, 4);
    }
    return &g_v756d754;
}

// @ 0x00bcec50
Vector3* FUN_00bcec50()
{
    if (g_v756d760.x == -1.0f) {
        void* local = 0;
        void* pm = PropertyManager();
        if (local != 0) {
            void* old = local;
            local = 0;
            VC0(void, old, 4);
        }
        if (VC3(bool, pm, 0x2c, u32, 0x4529f96fu, u32, 0x40636200u,
                void**, &local))
            GetPropertyAsVector3(local, 0x48f5b54u, &g_v756d760);
        if (local != 0)
            VC0(void, local, 4);
    }
    return &g_v756d760;
}