// Slice s00beb6d0 -- contiguous run 0x00beb6d0..0x00bec860.
// Tools: VS2008 SP1 (cl 15.00).  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
//   Sim::sub_beb6d0        00beb6d0  (big tick: two rbtree clears, 4-slot table rebuild,
//                                     empire check, two pointer-vector sweeps, 3 tail calls)
//   --- Simulator::cCityTerritory -----------------------------------------------
//   00beb950  ctor   00beb9c0 AsInterface   00beb9f0 InitFromDefinition
//   00beba10  ApplyTo 00beba70 UpdateRadius  00beba90 Write   00bebad0 Read
//   00bebbd0  Shutdown 00bebc10 Overlaps     00bebc90 GetClassId  00bebd00 GetIID
//   00bebd40  AsInterface2 00bebd70 SetPoliticalID 00bebd90 SetRadius
//   00bebe50  WriteSerializableObjectCheck    00bebf50 PostDataLoad
//   --- Simulator::cCityWalls ---------------------------------------------------
//   00bec060  base dtor  00bec0f0 PointInsideWall 00bec140 PointInsideInnerWall
//   00bec190  GetCenter  00bec1c0 GetInnerGatePosition 00bec2d0 GetGatePosition
//   00bec460  RequestGatePosition 00bec660 FindNearestPosition
//   00bec790  UpdateGatePosition  00bec860 GetIsWallBuilt
//
// The cCityWalls layout is taken verbatim from match/slices/s00bed920/s00bed920.cpp.
// cCityTerritory is re-laid flat from this slice's disassembly (cSpatialObject at +0x34,
// own fields at 0x108/0x10c/0x110/0x111 and 0x274/0x344).
#include <math.h>
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

// eastl::vector<T>: 0x14 bytes; only the three pointers are touched by this slice.
struct SpVector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint8_t  mAllocator[8];
};

// a release-able / refcounted object: vtable slot 0 = AddRef, slot 1 = Release
struct IObj { virtual void AddRef(); virtual void Release(); };
inline void AddRefOf(void* o) { if (o) ((IObj*)o)->AddRef(); }
inline void ReleaseOf(void* o) { if (o) ((IObj*)o)->Release(); }

// the cSpatialObject sub-object at +0x34 of cCityTerritory / cCityWalls
struct ISub34 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector3* v2c();                       // 0x2c  position
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(void* arg);                  // 0x5c
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual float v70();                          // 0x70
    virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90();
    virtual void v94(void* arg);                  // 0x94
};

// ---------------------------------------------------------------------------
// engine entry points (thiscall ones are modelled as members of small stubs so
// the compiler emits the same "mov ecx,arg" prologue as the original)
// ---------------------------------------------------------------------------
void*    __cdecl NounManager();                                    // 0x00b3d300
int      __cdecl GetPlayerEmpireOrMinus1();                        // 0x00b1f9d0
void*    __cdecl GetCurrentGameMode();                             // 0x00b5b800
void*    __cdecl EventLog(uint32_t id, int a, uint32_t b);         // 0x00b3d3e0
uint32_t __cdecl FNV1_String16(const void* s, uint32_t hash, int len); // 0x00932f30
void*    __cdecl GonzagoModelWorld();                              // 0x00b3d520
void*    __cdecl PlanetModel();                                    // 0x00b3d350
void* __stdcall FUN_00b18460(uint32_t id);                          // 0x00b18460
float    __cdecl FUN_00b685e0(void* obj);                          // 0x00b685e0
void     __cdecl FUN_00b69930(void* obj, float f, int a);          // 0x00b69930
int      __cdecl FUN_00c9e8e0(int kind, const Vector3* p);         // 0x00c9e8e0
void*    __cdecl FUN_01029790();                                   // 0x01029790
void     __cdecl FUN_00c6f770(uint32_t id, int idx, uint32_t val); // 0x00c6f770
bool     __cdecl EAIO_WriteUint32(void* stream, void* v, int a, int b);  // 0x0093aa70
bool     __cdecl EAIO_ReadInt32(void* stream, void* v, int a, int b);    // 0x0093a780
bool     __cdecl StreamWrite(void* stream, void* v, int a);              // 0x0093a9a0
bool     __cdecl ReadBool(void* stream, void* dst);                      // 0x0093ac80

struct GameDataBase {                       // cGameData
    void  Ctor();                           // 0x00b18660
    bool  Write(void* s);                   // 0x00b18590
    bool  Read(void* s);                    // 0x00b18600
};
struct SpatialBase {                        // cSpatialObject
    void  Ctor();                           // 0x00c89630
    bool  Write(void* s);                   // 0x00c88a90
    bool  Read(void* s);                    // 0x00c88b00
    void* AsInterface(uint32_t id);         // 0x00c884f0
    void  Teardown();                       // 0x00c8b2e0
};
struct VarListSerializer {                  // cVarListSerializer
    void* Ctor(void* owner, void* n, uint32_t id);   // 0x00692f90
    bool  SerializeOut(void* s);                     // 0x00692900
    bool  SerializeIn(void* s);                      // 0x00693e10
};
struct NounMgr {                            // cGameNounManager
    void  RemoveNoun(void* noun);           // 0x00b225d0
    void* CreateNoun(void* id);             // 0x00b20c60
};
struct TimerOps {                           // cSPTimer
    uint64_t Elapsed();                     // 0x00bc3190
};
struct TreeOps {                            // eastl rbtree node nuke
    void Nuke(void* node);                  // 0x009a9600
};
struct IdHash {                             // FUN_00bd8660
    void* FindId(uint32_t id);
};
struct ColonyTuning {                       // cSPSpaceColonyTuning
    float GetTerritoryRadius();             // 0x01029820
};
struct PlanetModelT {                       // cPlanetModel
    void Project(Vector3* out, const Vector3* in);   // 0x00b81630
};
struct SimOps {                             // Sim
    void sub_beabb0();                      // 0x00beabb0
    void sub_bea930();                      // 0x00bea930
    void FUN_00bdbe50();                    // 0x00bdbe50
};
struct EventLogOps {                        // cSPUIEventLog
    void RemoveAllEventsOfSameType();       // 0x00dd7620
};
struct IdString {                           // the object at Sim+0x34
    void* GetString();                      // vtable slot 4
};
struct PropReg {                            // 0x00695b40
    void Add(void* ct, void* b, const wchar_t* n);
};

extern float g1485378;      // 0x01485378  0.0f
extern float g13eb1bc;      // 0x013eb1bc  -1.0f
extern char  g13ec4b8;      // 0x013ec4b8  float 1e-8f
extern float g14853e0;      // 0x014853e0  4.0f
extern float g168c420, g168c424, g168c428;   // 0x0168c420 invalid position
extern float g1468fd4;      // 0x01468fd4  FLT_MAX
extern char  g18c88e4;      // 0x018c88e4

// ===========================================================================
struct Sim {
    uint8_t pad_000[0x34];
    uint8_t sub_034[1];                // 0x034
    uint8_t pad_035[0xb0 - 0x35];
    uint8_t timer[1];                  // 0x0b0
    uint8_t pad_0b1[0x340 - 0xb1];
    void**  f340;                      // 0x340
    void**  f344;                      // 0x344
    uint8_t pad_348[0x354 - 0x348];
    void**  f354;                      // 0x354
    void**  f358;                      // 0x358
    uint8_t pad_35c[0x5bc - 0x35c];
    uint8_t tree0[0x1c];               // 0x5bc
    uint8_t tree1[0x1c];               // 0x5d8
    uint8_t* m618;                     // 0x618
    uint8_t pad_61c[0x10];
    void*   m62c;                      // 0x62c

    void sub_beb6d0();
};

static inline void ClearTree(uint8_t* tree)
{
    ((TreeOps*)tree)->Nuke(*(void**)(tree + 0x0c));
    *(void**)(tree + 0x08) = tree + 4;
    *(void**)(tree + 0x0c) = 0;
    tree[0x10] = 0;
    *(uint32_t*)(tree + 0x14) = 0;
    *(void**)(tree + 0x04) = tree + 4;
}

// @ 0x00beb6d0
void Sim::sub_beb6d0()
{
    ClearTree(tree0);
    ClearTree(tree1);

    uint8_t* base = m618;
    void*    ids  = m62c;
    int i = 0;
    int off = 0x10;
    do {
        uint8_t* rec = base + i;
        *(uint32_t*)(rec + off + 8)    = 0;
        *(uint32_t*)(rec + off)        = 0;
        rec[0x20]                      = 0;
        *(uint32_t*)(rec + off + 0x0c) = 0;
        *(uint32_t*)(rec + off + 4)    = 0;
        rec[0x20]                      = 0;

        void* old  = *(void**)(base + i + 0x70);
        void* slot = *(void**)((char*)ids + (i >> 2) * 4);
        void* nu   = 0;
        void* r    = ((IdHash*)slot)->FindId((uint32_t)(uintptr_t)slot);
        if (r) {
            void* fn = *(void**)(*(uint32_t*)r + 0x0c);
            nu = ((void* (__thiscall*)(void*, uint32_t))fn)(r, 0x01186577);
        }
        void** p = (void**)(base + i + 0x70);
        void* cur = *p;
        if (nu != cur) {
            if (nu) ((IObj*)nu)->AddRef();
            *p = nu;
            if (cur) ((IObj*)cur)->Release();
        }
        *(uint8_t*)(base + i + 0x74) = (old != *(void**)(base + i + 0x70));
        i += 0x80;
        off += 0x80;
    } while (off < 0x210);

    NounManager();
    int empire = GetPlayerEmpireOrMinus1();
    int self_emp = ((int (__thiscall*)(void*))*(void**)(*(uint32_t*)this + 0x4c))(this);
    if (self_emp == empire) {
        uint64_t t = ((TimerOps*)timer)->Elapsed() - 0x36b1;
        if ((uint32_t)(t >> 32) == 0 && (uint32_t)t <= 999) {
            void* s = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)sub_034 + 4))(sub_034);
            uint32_t h = FNV1_String16(s, 0x811c9dc5, 1);
            ((EventLogOps*)EventLog(0x38320b95, 0, h))->RemoveAllEventsOfSameType();
        }
    }

    if (GetCurrentGameMode() != (void*)0x01654c05) {
        for (void** p = f340; p != f344; ++p) {
            void* o = *p;
            float f = FUN_00b685e0(o);
            if (f < 1.0f && 0.0f < f)
                FUN_00b69930(o, g13eb1bc, 0);
        }
        for (void** p = f354; p != f358; ++p) {
            void* o = *p;
            float f = FUN_00b685e0(o);
            if (f < 1.0f && 0.0f < f)
                FUN_00b69930(o, g13eb1bc, 0);
        }
    }

    ((SimOps*)this)->sub_beabb0();
    ((SimOps*)this)->FUN_00bdbe50();
    ((SimOps*)this)->sub_bea930();
}

// ===========================================================================
// cCityTerritory -- flat re-lay (retail), cSpatialObject sub-object at +0x34
// ===========================================================================
struct cCityTerritory {
    void*   vfptr0;                    // 0x000
    void*   vfptr1;                    // 0x004
    uint8_t pad_008[0x2c - 8];
    void*   vfptr_rc;                  // 0x02c
    uint8_t pad_030[0x34 - 0x30];
    uint8_t sub34[1];                  // 0x034  cSpatialObject
    uint8_t pad_035[0x108 - 0x35];
    uint8_t m108;                      // 0x108
    uint8_t pad_109[3];
    float   m10c;                      // 0x10c
    uint8_t m110;                      // 0x110
    uint8_t m111;                      // 0x111
    uint8_t pad_112[0x274 - 0x112];
    uint8_t mBuildingLinks[14][14];    // 0x274
    uint8_t pad_338[0x344 - 0x338];
    uint32_t mStyle;                   // 0x344

    ISub34* Sub() { return (ISub34*)sub34; }

    cCityTerritory* ctor();                        // 0x00beb950
    void* AsInterface(uint32_t id);                // 0x00beb9c0
    bool  InitFromDefinition(void* a);             // 0x00beb9f0
    void  ApplyTo(void* obj);                      // 0x00beba10
    void  UpdateRadius();                          // 0x00beba70
    bool  Write(void* stream);                     // 0x00beba90
    bool  Read(void* stream);                      // 0x00bebad0
    void  Shutdown();                              // 0x00bebbd0
    uint32_t Overlaps(cCityTerritory* other);      // 0x00bebc10
    void* AsInterface2(uint32_t id);               // 0x00bebd40
    uint32_t SetPoliticalID(uint32_t id);          // 0x00bebd70
    void  SetRadius();                             // 0x00bebd90
    bool  WriteSerializableObjectCheck(void* stream);  // 0x00bebe50
    bool  PostDataLoad(void* stream);              // 0x00bebf50
};

// @ 0x00beb950
cCityTerritory* cCityTerritory::ctor()
{
    ((GameDataBase*)this)->Ctor();
    ((SpatialBase*)sub34)->Ctor();
    *(void**)sub34      = (void*)0x01468e90;
    m110                = 0;
    m111                = 0;
    vfptr0              = (void*)0x01468e20;
    vfptr1              = (void*)0x01468e0c;
    m108                = 1;
    m10c                = 100.0f;
    return this;
}

// @ 0x00beb9c0
void* cCityTerritory::AsInterface(uint32_t id)
{
    void* r;
    if (id == 0x2450023) {
        r = this;
    } else {
        r = FUN_00b18460(id);
        if (r == 0)
            r = ((SpatialBase*)sub34)->AsInterface(id);
    }
    return r;
}

// @ 0x00beb9f0
bool cCityTerritory::InitFromDefinition(void* a)
{
    ((PropReg*)a)->Add(this, (void*)0x01567e48, L"cGameData");
    return true;
}

// @ 0x00beba10
void cCityTerritory::ApplyTo(void* obj)
{
    uint32_t s = *(uint32_t*)sub34;
    void* v = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)obj + 0x2c))(obj);
    (*(void (__thiscall*)(void*, void*))*(void**)(s + 0x38))(sub34, v);
    void* w = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)obj + 0x30))(obj);
    (*(void (__thiscall*)(void*, void*))*(void**)(*(uint32_t*)sub34 + 0x3c))(sub34, w);
}

// @ 0x00beba70
void cCityTerritory::UpdateRadius()
{
    uint32_t vt = *(uint32_t*)this;
    float r = ((ColonyTuning*)FUN_01029790())->GetTerritoryRadius();
    (*(void (__thiscall*)(void*, float))*(void**)(vt + 0x60))(this, r);
}

// @ 0x00beba90
bool cCityTerritory::Write(void* stream)
{
    bool a = ((GameDataBase*)this)->Write(stream);
    bool b = ((SpatialBase*)sub34)->Write(stream);
    if (b && a)
        return true;
    return false;
}

// @ 0x00bebad0
bool cCityTerritory::Read(void* stream)
{
    bool a = ((GameDataBase*)this)->Read(stream);
    bool b = ((SpatialBase*)sub34)->Read(stream);
    if (b && a)
        return true;
    return false;
}

// @ 0x00bebbd0
void cCityTerritory::Shutdown()
{
    ((SpatialBase*)sub34)->Teardown();
    void* p = vfptr_rc;
    if (p) {
        vfptr_rc = 0;
        ((IObj*)p)->Release();
    }
}

// @ 0x00bebc10
uint32_t cCityTerritory::Overlaps(cCityTerritory* other)
{
    ISub34* os = (ISub34*)((char*)other + 0x34);
    Vector3* a = os->v2c();
    Vector3* b = Sub()->v2c();
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    float dist = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
    float lim  = os->v70() + m10c;
    if (dist < lim)
        return true;
    return false;
}

// @ 0x00bebc90  (cdecl: the original pops no arguments)
uint32_t GetClassId(int a, int b)
{
    switch (a) {
    case 1:
        switch (b) {
        case 1: return 0x1c67c10a;
        case 2: return 0x1c67c10b;
        default: return 0x1844dce8;
        }
    case 2:
        switch (b) {
        case 1: return 0xd18d8db;
        case 2: return 0xd18d8da;
        default: return 0xf2a53913;
        }
    default:
        switch (b) {
        case 1: return 0xff301c01;
        case 2: return 0xff301c00;
        default: return 0x7b29ee1;
        }
    }
}

// @ 0x00bebd00  (cdecl)
uint32_t GetIID(int a)
{
    switch (a) {
    case 0: return 0xc5c4bf13;
    case 1: return 0x7b2047fb;
    case 2: return 0xd513545d;
    case 3: return 0x4dc37ba5;
    default: return 0xc5c4bf13;
    }
}

// @ 0x00bebd40
void* cCityTerritory::AsInterface2(uint32_t id)
{
    if (id == 0xed7fc07)
        return this;
    void* r = FUN_00b18460(id);
    if (r == 0)
        r = ((SpatialBase*)sub34)->AsInterface(id);
    return r;
}

// @ 0x00bebd70
uint32_t cCityTerritory::SetPoliticalID(uint32_t id)
{
    (*(void (__thiscall*)(void*, uint32_t))*(void**)(*(uint32_t*)sub34 + 0x5c))(sub34, id);
    return id;
}

// @ 0x00bebd90
void cCityTerritory::SetRadius()
{
    void* w = GonzagoModelWorld();
    (*(void (__thiscall*)(void*, int, int))*(void**)(*(uint32_t*)w + 0x18))(w, 0, 2);
}

// @ 0x00bebe50
bool cCityTerritory::WriteSerializableObjectCheck(void* stream)
{
    union { char c[0xa20]; double d; } frame;
    uint8_t* ok = (uint8_t*)&frame;
    uint8_t* self = (uint8_t*)this;
    uint8_t* loop = (uint8_t*)this + 0x274;
    int id = 0xed7fc07;
    void* s = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)stream + 0x20))(stream);
    void* out = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)s + 0x18))(s);
    EAIO_WriteUint32(out, &id, 1, 0);
    if (((GameDataBase*)self)->Write(stream)) {
        *ok = 1;
        if (!((SpatialBase*)(self + 0x34))->Write(stream)) *ok = 0;
    } else {
        *ok = 0;
    }
    int rows = 0xe;
    do {
        unsigned i = 0;
        do {
            void* s2 = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)stream + 0x20))(stream);
            void* out2 = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)s2 + 0x18))(s2);
            uint8_t v = loop[i] != 0;
            uint8_t tmp = v;
            StreamWrite(out2, &tmp, 1);
            i++;
        } while (i < 0xe);
        loop += 0xe;
        rows--;
    } while (rows != 0);
    ((VarListSerializer*)(frame.c + 0x14))->Ctor(self, (void*)0x0156f588, 0x1a80d26);
    if (*ok) {
        if (((VarListSerializer*)(frame.c + 0x14))->SerializeOut(stream))
            return true;
    }
    return false;
}

// @ 0x00bebf50
bool cCityTerritory::PostDataLoad(void* stream)
{
    union { char c[0xa20]; double d; } frame;
    uint8_t* ok = (uint8_t*)&frame;
    uint8_t* self = (uint8_t*)this;
    uint8_t* loop = (uint8_t*)this + 0x274;
    int tmp;
    void* s = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)stream + 0x20))(stream);
    void* in = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)s + 0x18))(s);
    EAIO_ReadInt32(in, &tmp, 1, 0);
    if (((GameDataBase*)self)->Read(stream)) {
        *ok = 1;
        if (!((SpatialBase*)(self + 0x34))->Read(stream)) *ok = 0;
    } else {
        *ok = 0;
    }
    int rows = 0xe;
    do {
        unsigned i = 0;
        do {
            void* s2 = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)stream + 0x20))(stream);
            void* in2 = (*(void* (__thiscall*)(void*))*(void**)(*(uint32_t*)s2 + 0x18))(s2);
            ReadBool(in2, loop + i);
            i++;
        } while (i < 0xe);
        loop += 0xe;
        rows--;
    } while (rows != 0);
    ((VarListSerializer*)(frame.c + 0x14))->Ctor(self, (void*)0x0156f588, 0x1a80d26);
    if (*ok) {
        if (!((VarListSerializer*)(frame.c + 0x14))->SerializeIn(stream)) *ok = 0;
    }
    uint32_t old = *(uint32_t*)(self + 0x344);
    *(uint32_t*)(self + 0x344) = 0;
    (*(void (__thiscall*)(void*, uint32_t))*(void**)(*(uint32_t*)self + 0x60))(self, old);
    return *ok != 0;
}

// ===========================================================================
// cCityWalls -- layout from s00bed920 (verified against retail)
// ===========================================================================
struct cCityWalls {
    void*    vtbl_a;             // 0x000
    void*    vtbl_b;             // 0x004
    uint8_t  pad_008[0x2c - 8];
    void*    vfptr_rc;           // 0x02c
    uint8_t  pad_030[0x34 - 0x30];
    uint8_t  sub34[1];           // 0x034  cSpatialObject
    uint8_t  pad_035[0x10c - 0x35];
    uint32_t field_10c;          // 0x10c
    SpVector mDockSlots;         // 0x110
    SpVector field_124;          // 0x124
    uint8_t  pad_138[0x198 - 0x138];
    SpVector field_198;          // 0x198
    uint8_t  pad_1ac[0x254 - 0x1ac];
    uint32_t field_254;          // 0x254
    float    mInnerRadius;       // 0x258
    float    mOuterRadius;       // 0x25c
    float    field_260;          // 0x260
    uint32_t field_264;          // 0x264  cCity*
    uint8_t  pad_268[0x344 - 0x268];
    uint32_t mStyle;             // 0x344
    uint8_t  pad_348[0x354 - 0x348];
    uint32_t field_354;          // 0x354

    ISub34* Sub() const { return (ISub34*)sub34; }
    ISub34* CitySub() const { return (ISub34*)(field_264 + 0x120); }

    void    FUN_00bec060();                       // 0x00bec060
    uint32_t PointInsideWall(const Vector3& p);            // 0x00bec0f0
    uint32_t PointInsideInnerWall(const Vector3& p);       // 0x00bec140
    Vector3 GetCenter();                                  // 0x00bec190
    Vector3 GetInnerGatePosition(int idx);                // 0x00bec1c0
    Vector3 GetGatePosition(int idx);                     // 0x00bec2d0
    Vector3* RequestGatePosition(Vector3* out, int idx, int kind);  // 0x00bec460
    Vector3* FindNearestPosition(Vector3* out, const Vector3* ref, int kind); // 0x00bec660
    void    UpdateGatePosition(int idx);                  // 0x00bec790
    bool GetIsWallBuilt();                                // 0x00bec860
};

// @ 0x00bec060
void cCityWalls::FUN_00bec060()
{
    uint8_t* self = (uint8_t*)this;
    void* p = *(void**)(self + 0x264);
    if (p) {
        *(void**)(self + 0x264) = 0;
        ((IObj*)p)->Release();
    }
    void* n = *(void**)(self + 0x10c);
    if (n) {
        ((NounMgr*)NounManager())->RemoveNoun(n);
        void* q = *(void**)(self + 0x10c);
        if (q) {
            *(void**)(self + 0x10c) = 0;
            ((IObj*)q)->Release();
        }
    }
    void* w = *(void**)(self + 0x354);
    if (w) {
        (*(void (__thiscall*)(void*, int))*(void**)(*(uint32_t*)w + 0x0c))(w, 1);
        void* q = *(void**)(self + 0x354);
        if (q) {
            *(void**)(self + 0x354) = 0;
            ((IObj*)q)->Release();
        }
    }
    void* m = *(void**)(self + 0x2c);
    if (m) {
        *(void**)(self + 0x2c) = 0;
        ((IObj*)m)->Release();
    }
    ((SpatialBase*)(self + 0x34))->Teardown();
}

// @ 0x00bec0f0
uint32_t cCityWalls::PointInsideWall(const Vector3& p)
{
    Vector3* c = Sub()->v2c();
    float dx = p.x - c->x;
    float dy = p.y - c->y;
    float dz = p.z - c->z;
    if ((float)sqrt((double)(dx * dx + dy * dy + dz * dz)) < mOuterRadius)
        return true;
    return false;
}

// @ 0x00bec140
uint32_t cCityWalls::PointInsideInnerWall(const Vector3& p)
{
    Vector3* c = Sub()->v2c();
    float dx = p.x - c->x;
    float dy = p.y - c->y;
    float dz = p.z - c->z;
    if ((float)sqrt((double)(dx * dx + dy * dy + dz * dz)) < mInnerRadius)
        return true;
    return false;
}

// @ 0x00bec190
Vector3 cCityWalls::GetCenter()
{
    Vector3 out;
    Vector3* c = Sub()->v2c();
    out.x = c->x;
    out.y = c->y;
    out.z = c->z;
    return out;
}

// @ 0x00bec1c0
Vector3 cCityWalls::GetInnerGatePosition(int idx)
{
    Vector3* slot = (Vector3*)field_198.mpBegin + idx;
    Vector3* c = CitySub()->v2c();
    float dx = slot->x - c->x;
    float dy = slot->y - c->y;
    float dz = slot->z - c->z;
    float inv = 1.0f / (float)sqrt((double)(dx * dx + (dz * dz + dy * dy)));
    float s = mInnerRadius;
    Vector3* c2 = CitySub()->v2c();
    Vector3 out;
    out.x = c2->x + dx * inv * s;
    out.y = c2->y + dy * inv * s;
    out.z = c2->z + dz * inv * s;
    return out;
}

// @ 0x00bec2d0
Vector3 cCityWalls::GetGatePosition(int idx)
{
    Vector3* slot = (Vector3*)field_198.mpBegin + idx;
    Vector3* c = CitySub()->v2c();
    Vector3 out;
    if (slot->x == c->x && slot->y == c->y && slot->z == c->z) {
        Vector3* c2 = CitySub()->v2c();
        out.x = c2->x;
        out.y = c2->y;
        out.z = c2->z;
        return out;
    }
    Vector3* c3 = CitySub()->v2c();
    float dx = slot->x - c3->x;
    float dy = slot->y - c3->y;
    float dz = slot->z - c3->z;
    float inv = 1.0f / (float)sqrt((double)(dx * dx + (dz * dz + dy * dy)));
    float s = mOuterRadius;
    out.x = c3->x + dx * inv * s;
    out.y = c3->y + dy * inv * s;
    out.z = c3->z + dz * inv * s;
    return out;
}

// @ 0x00bec460
Vector3* cCityWalls::RequestGatePosition(Vector3* out, int idx, int kind)
{
    Vector3* slot = (Vector3*)field_198.mpBegin + idx;
    Vector3* c = CitySub()->v2c();
    float dx = slot->x - c->x;
    float dy = slot->y - c->y;
    float dz = slot->z - c->z;
    float inv = 1.0f / (float)sqrt((double)(dx * dx + dy * dy + dz * dz) + g13ec4b8);
    float ux = dx * inv;
    float uy = dy * inv;
    float uz = dz * inv;
    float s = mOuterRadius;
    Vector3 p;
    p.x = c->x + ux * s;
    p.y = c->y + uy * s;
    p.z = c->z + uz * s;
    if (field_254 == 2 || field_254 == 3) {
        if (kind == 0) {
            if (idx == 3) goto invalid;
        } else if (kind == 1) {
            if (idx != 3) goto invalid;
        }
    }
    {
        int i = 0;
        for (;;) {
            if (FUN_00c9e8e0(kind, &p)) {
                ((PlanetModelT*)PlanetModel())->Project(out, &p);
                return out;
            }
            i++;
            p.x = ux * g14853e0 + p.x;
            p.y = uy * g14853e0 + p.y;
            p.z = uz * g14853e0 + p.z;
            if (i >= 8) break;
        }
    }
invalid:
    out->x = g168c420;
    out->y = g168c424;
    out->z = g168c428;
    return out;
}

// @ 0x00bec660
Vector3* cCityWalls::FindNearestPosition(Vector3* out, const Vector3* ref, int kind)
{
    float best = g1468fd4;
    out->x = g168c420;
    out->y = g168c424;
    out->z = g168c428;
    for (int i = 0; i < 6; ++i) {
        Vector3 p;
        RequestGatePosition(&p, i, kind);
        if (!(p.x == g168c420 && p.y == g168c424 && p.z == g168c428)) {
            float dx = p.x - ref->x;
            float dy = p.y - ref->y;
            float dz = p.z - ref->z;
            float d = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
            if (d < best) {
                out->x = p.x;
                out->y = p.y;
                out->z = p.z;
                best = d;
            }
        }
    }
    return out;
}

// @ 0x00bec790
void cCityWalls::UpdateGatePosition(int idx)
{
    uint8_t* self = (uint8_t*)this;
    if (field_10c == 0) {
        void* n = ((NounMgr*)NounManager())->CreateNoun((void*)0x018c88e4);
        void* old = *(void**)(self + 0x10c);
        if (n != old) {
            if (n) ((IObj*)n)->AddRef();
            *(void**)(self + 0x10c) = n;
            if (old) ((IObj*)old)->Release();
        }
    }
    void* noun = *(void**)(self + 0x10c);
    Vector3* slot = field_124.mpBegin + idx;
    (*(void (__thiscall*)(void*, Vector3*))*(void**)(*(uint32_t*)((uint32_t)noun + 0x70) + 0x94))(
        (void*)((uint32_t)noun + 0x70), slot);
    FUN_00c6f770(0x065658d2, -1, *(uint32_t*)slot);
}

// @ 0x00bec860
bool cCityWalls::GetIsWallBuilt()
{
    void* p = *(void**)((char*)this + 0x354);
    if (p) {
        uint64_t r = (*(uint64_t (__thiscall*)(void*))*(void**)(*(uint32_t*)p + 0x60))((void*)p);
        if (r == 0xf8c9566dULL || r == 0xc809402aULL)
            return true;
    }
    return false;
}
