// slice s009c4a30 -- nSPCreatureAnim creature-instance finalize/clear/destroy and
// InitCreatureInstance.
//
//   @ 0x009c4a30  FinalizeCreature              (ComputeHierarchy + bounds + rebuild)
//   @ 0x009c4b90  nSPCreatureAnim::dynamics_walking::~dynamics_walking
//   @ 0x009c4bf0  nSPCreatureAnim::creature_instance_data::~creature_instance_data
//   @ 0x009c4cc0  nSPCreatureAnim::creature_instance_data::Release
//   @ 0x009c4d10  creature_instance_data::UnlinkStaticData
//   @ 0x009c4d40  nSPCreatureAnim::creature_instance_data::Clear
//   @ 0x009c52a0  nSPCreatureAnim::InitCreatureInstance
//
// Retail offsets are used throughout (the dev PDB predates this build).  The instance
// object extends past 0x17b0; the static object past 0x410.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char uint8;
typedef unsigned int  uint32;

namespace checkerlib {
struct vector_3 { float x, y, z; };
struct vector_4 { float x, y, z, w; };
struct matrix_3x3 { float m[3][3]; };
}
using checkerlib::vector_3;
using checkerlib::vector_4;
using checkerlib::matrix_3x3;

void operator delete[](void* p);          // 0x00f47380
float sqrtf(float);

namespace nSPCreatureAnim {

// ------------------------------------------------------------------ types

struct creature_static_data;
struct creature_instance_data;

struct creature_static_data {
    uint8 blob[0x410];

    int   Release();                       // 0x009c26a0
    void  InitWiggles();                   // 0x009c26f0
    void  FUN_009c1d30();                  // 0x009c1d30
    void  FUN_009b54a0();                  // 0x009b54a0
    void  FUN_009b5580();                  // 0x009b5580
    void  FUN_009b5930();                  // 0x009b5930
    void  FUN_009bfa20();                  // 0x009bfa20
    float FUN_009b5360();                  // 0x009b5360
};

bool ComputeHierarchy(creature_static_data* c, int flag);   // 0x009c32c0
void FUN_009b6b10(float* mn, float* mx, creature_static_data* c);   // 0x009b6b10
void FUN_009b5ce0(creature_static_data* c);                 // 0x009b5ce0
void FUN_009bf5c0(void* first, void* last, void* out);      // 0x009bf5c0
void FUN_009b4a20(void* first, void* last, void* out);      // 0x009b4a20
struct M3 { float f[9]; void FUN_0099ce40(); };             // 0x0099ce40
void FUN_009e3f70(void* self, int a, int b);                // 0x009e3f70
void FUN_009bd340(creature_instance_data* c);               // 0x009bd340
void* FUN_011e073e(void* p, int a, int b);                  // 0x011e073e
void  FUN_009db1d0(void* self);                             // 0x009db1d0
void  FUN_009db270(void* self);                             // 0x009db270
void  FUN_009db4d0(void* self, float v);                    // 0x009db4d0
void  FUN_009db6d0(void* self, float v, creature_instance_data* c);  // 0x009db6d0
void  FUN_009d34a0(void* self);                             // 0x009d34a0
void  FUN_009da640(void* self, creature_instance_data* c);  // 0x009da640
void  FUN_009d3170(void* self);                             // 0x009d3170

struct phasegroup_vec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32 mAllocator;
    void DoDestroyValues(void* first, void* last);          // 0x009c3240
};

struct dynamics_walking {
    uint8           pad00[0x10];
    phasegroup_vec  groups;                                 // 0x10
    uint8           pad20[0x24 - 0x20];
    void*           feet;                                   // 0x24
    uint8           pad28[0x38 - 0x28];
    void*           vert;                                   // 0x38
    ~dynamics_walking();
};

struct body_vec {                                           // object at instance+0x2e4
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32 mAllocator;
    void FUN_009c3040(int n);                               // 0x009c3040
};

struct sub_2f8 {                                            // object at instance+0x2f8
    uint8 pad[0x10];
    void FUN_009e3f70(int a, int b);                        // 0x009e3f70
    void FUN_009b59c0();                                    // 0x009b59c0
};

struct ik_vec {                                             // object at instance+0x24c
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32 mAllocator;
    void resize(int n);                                     // 0x009c2ef0
};

struct instance_hashtable {                                 // object at instance+0x17a0
    uint32 mAllocator0;                                     // +0x00
    void*  mpBucketArray;                                   // +0x04
    uint32 mnBucketCount;                                   // +0x08
    uint32 mnElementCount;                                  // +0x0c
    uint32 pad10[3];                                        // +0x10
    void*  mpFreeList;                                      // +0x1c  (fixed allocator free list)
    uint32 pad20;                                           // +0x20
    void*  mpPoolBegin;                                     // +0x24
    void*  mpPoolEnd;                                       // +0x28
    uint32 pad2c;
    void*  mpFixedBuffer;                                   // +0x30
    void DoFreeNodes(void* a, void* b);                     // 0x00a1b6c0
};

struct creature_instance_data {
    uint8 blob[0x17b0];

    void Clear(bool flag);                                  // 0x009c4d40
    __declspec(noinline) int Release();                     // 0x009c4cc0
    ~creature_instance_data();                              // 0x009c4bf0
    void InitWiggles();                                     // 0x009c2c20
    void BuildBodyList();                                   // 0x009c20e0
    void FUN_009c4d10();                                    // 0x009c4d10
    void FUN_009cb4f0();                                    // 0x009cb4f0
    void FUN_009b6360();                                    // 0x009b6360
};

// ------------------------------------------------------------------ @ 0x009c4a30

// @ 0x009c4a30
uint32 FinalizeCreature(creature_static_data* c)
{
    if (!ComputeHierarchy(c, 0))
        return 0;

    float l18 = 0.0f, l14 = 0.0f, l10 = 0.0f;
    float lc = 0.0f, l8 = 0.0f, l4 = 0.0f;
    FUN_009b6b10(&l18, &lc, c);

    *(float*)((char*)c + 0x358) = l18;
    lc = lc - l18;
    *(float*)((char*)c + 0x35c) = l14;
    float f3 = l8 - l14;
    float f4 = l4 - l10;
    *(float*)((char*)c + 0x360) = l10;
    *(float*)((char*)c + 0x364) = lc;
    *(float*)((char*)c + 0x368) = f3;
    *(float*)((char*)c + 0x36c) = f4;
    *(float*)((char*)c + 0x370) = sqrtf(lc * lc + (f4 * f4 + f3 * f3));

    c->FUN_009c1d30();
    c->FUN_009b54a0();
    if (*(int*)((char*)c + 0x3c8) == 0) {
        c->FUN_009b5580();
        c->FUN_009b5930();
    }
    c->FUN_009bfa20();
    c->InitWiggles();
    *(float*)((char*)c + 0x374) = c->FUN_009b5360();
    FUN_009b5ce0(c);

    int n = (int)((*(char**)((char*)c + 0x388) - *(char**)((char*)c + 0x384)) / 0x468);
    return (uint32)(n < 0x100);
}

// ------------------------------------------------------------------ @ 0x009c4b90

// @ 0x009c4b90
dynamics_walking::~dynamics_walking()
{
    if (vert && ((int*)vert)[-1] != 0)
        operator delete[](vert);
    if (feet && ((int*)feet)[-1] != 0)
        operator delete[](feet);
    groups.DoDestroyValues(groups.mpBegin, groups.mpEnd);
    if (groups.mpBegin && ((int*)groups.mpBegin)[-1] != 0)
        operator delete[](groups.mpBegin);
}

// ------------------------------------------------------------------ @ 0x009c4bf0

// @ 0x009c4bf0
creature_instance_data::~creature_instance_data()
{
    char* b = (char*)this;
    instance_hashtable* ht = (instance_hashtable*)(b + 0x17a0);
    ht->DoFreeNodes(ht->mpBucketArray, (void*)ht->mnBucketCount);
    {
        void* e = ht->mpBucketArray;
        ht->mnElementCount = 0;
        if (ht->mnBucketCount > 1 && e != ht->mpFixedBuffer) {
            if (e < ht->mpPoolBegin || e >= ht->mpPoolEnd)
                operator delete[](e);
            else {
                *(void**)e = ht->mpFreeList;
                ht->mpFreeList = e;
            }
        }
    }
    if (*(void**)(b + 0x1694) && ((int*)*(void**)(b + 0x1694))[-1] != 0)
        operator delete[](*(void**)(b + 0x1694));
    ((dynamics_walking*)(b + 0x15b8))->~dynamics_walking();
    ((sub_2f8*)(b + 0x2f8))->FUN_009b59c0();
    if (*(void**)(b + 0x2e4) && ((int*)*(void**)(b + 0x2e4))[-1] != 0)
        operator delete[](*(void**)(b + 0x2e4));
    if (*(void**)(b + 0x294))
        ((creature_instance_data*)*(void**)(b + 0x294))->Release();
    if (*(void**)(b + 0x24c) && ((int*)*(void**)(b + 0x24c))[-1] != 0)
        operator delete[](*(void**)(b + 0x24c));
    creature_static_data* sd = *(creature_static_data**)b;
    if (sd)
        sd->Release();
}

// ------------------------------------------------------------------ @ 0x009c4cc0

// @ 0x009c4cc0
int creature_instance_data::Release()
{
    char* b = (char*)this;
    int n = *(int*)(b + 0x14) - 1;
    if (n < 1)
        n = 0;
    *(int*)(b + 0x14) = n;
    if (n < 1) {
        *(int*)(b + 0x14) = 1;
        this->~creature_instance_data();
        operator delete[](this);
        return 0;
    }
    return n;
}

// ------------------------------------------------------------------ @ 0x009c4d10

// @ 0x009c4d10
void creature_instance_data::FUN_009c4d10()
{
    char* b = (char*)this;
    if (*(int*)(b + 0x294) != 0) {
        void* p = *(void**)(b + 0x294);
        *(uint32*)(b + 0x294) = 0;
        ((creature_instance_data*)p)->Release();
    }
    FUN_009cb4f0();
    *(uint8*)(b + 0xc) = 0;
}

// ------------------------------------------------------------------ @ 0x009c4d40

#define F(o) (*(float*)(b + (o)))
struct V2 { float x, y; V2& operator=(const V2& o) { x = o.x; y = o.y; return *this; } };
struct V3 { float x, y, z; V3& operator=(const V3& o) { x = o.x; y = o.y; z = o.z; return *this; } };
#define V2AT(o) (*(V2*)(b + (o)))
#define V3AT(o) (*(V3*)(b + (o)))
struct Elem2bc { uint8 d[0x2bc]; };
struct Elem2c  { uint8 d[0x2c]; };
struct vec2bc { Elem2bc* mpBegin; Elem2bc* mpEnd; };
struct vec2c  { Elem2c*  mpBegin; Elem2c*  mpEnd; };

// @ 0x009c4d40
void creature_instance_data::Clear(bool flag)
{
    char* b = (char*)this;
    creature_static_data* sd;

    if (flag) {
        sd = *(creature_static_data**)b;
        *(uint32*)(b + 0x2c0) = 0;
        if (sd) { *(void**)b = 0; sd->Release(); }
        *(uint8*)(b + 0xc) = 0;
    }

    sd = *(creature_static_data**)b;
    *(uint32*)(b + 0x2c0) = 0;
    if (sd) { *(void**)b = 0; sd->Release(); }
    *(uint32*)(b + 4) = 0;
    *(uint32*)(b + 8) = 0;

    // Bodies.clear()
    {
        vec2bc* v = (vec2bc*)(b + 0x2e4);
        Elem2bc* be = v->mpBegin;
        Elem2bc* en = v->mpEnd;
        FUN_009bf5c0(en, en, be);
        v->mpEnd += (en - be);
    }
    *(uint32*)(b + 0x10) = (uint32)this >> 4;
    *(uint8*)(b + 0xc) = 0;
    FUN_009cb4f0();

    F(0x34) = 0.0f;  F(0x38) = 0.0f;  F(0x30) = 0.0f;  F(0x18) = 0.0f;
    V2AT(0x1c) = V2AT(0x34);
    F(0x24) = 0.0f;
    V2AT(0x28) = V2AT(0x1c);
    F(0x60) = 0.0f;  F(0x64) = 0.0f;  F(0x68) = 1.0f;  F(0x5c) = 0.0f;  F(0x3c) = 0.0f;
    V3AT(0x40) = V3AT(0x60);
    F(0x4c) = 0.0f;
    V3AT(0x50) = V3AT(0x40);
    F(0x6c) = 1.0f;  F(0x70) = 1.0f;
    F(0xb4) = 0.0f;  F(0xb8) = 0.0f;  F(0xb0) = 0.0f;  F(0x98) = 0.0f;
    V2AT(0x9c) = V2AT(0xb4);
    F(0x8c) = 0.0f;
    V2AT(0x90) = V2AT(0x9c);
    F(0x80) = 0.0f;
    V2AT(0x84) = V2AT(0x90);
    F(0x74) = 0.0f;
    V2AT(0x78) = V2AT(0x84);
    F(0xc8) = 0.0f;  F(0xcc) = 0.0f;  F(0xd0) = 0.0f;  F(0xd4) = 1.0f;
    F(0xa4) = 0.0f;  F(0xa8) = 0.0f;  F(0xac) = 0.0f;
    F(0xbc) = 0.0f;  F(0xc0) = 0.0f;  F(0xc4) = 0.0f;
    F(0xd8) = 0.0f;  F(0xdc) = 0.0f;  F(0xe0) = 0.0f;  F(0xe4) = 0.0f;
    F(0x110) = 0.0f; F(0x114) = 0.0f;
    {
        M3* mm = (M3*)(b + 0x118);
        float* m = mm->f;
        m[0] = 0.0f;
        m[1] = 0.0f;
        m[2] = 0.0f;
        m[3] = 0.0f;
        m[4] = 0.0f;
        m[5] = 0.0f;
        m[6] = 0.0f;
        m[7] = 0.0f;
        m[8] = 0.0f;
        mm->FUN_0099ce40();
    }

    F(0x13c) = 0.0f;
    F(0x140) = 0.0f;
    F(0x144) = 0.0f;
    F(0x148) = 0.0f;
    F(0x14c) = 0.0f;
    F(0x150) = 0.0f;
    F(0x154) = 0.0f;
    F(0x158) = 0.0f;
    F(0x15c) = 0.0f;
    F(0x160) = 0.0f;
    F(0x164) = 0.0f;
    F(0x168) = 0.0f;
    F(0x16c) = 0.0f;
    F(0x170) = 0.0f;
    F(0x174) = 0.0f;
    F(0x178) = 0.0f;
    F(0x17c) = 0.0f;
    F(0x180) = 0.0f;
    F(0x184) = 0.0f;
    F(0x188) = 0.0f;
    F(0x18c) = 0.0f;
    F(0x190) = 0.0f;
    F(0x194) = 0.0f;
    F(0x198) = 0.0f;
    F(0x19c) = 0.0f;
    F(0x1a0) = 0.0f;
    F(0x1a4) = 0.0f;

    *(uint32*)(b + 0x274) = 0;
    F(0x27c) = -10.0f;
    F(0x280) = 2.0f;
    F(0x278) = 0.0f;
    F(0x284) = 0.0f;  F(0x288) = 0.0f;  F(0x28c) = 0.0f;  F(0x290) = 1.0f;

    if (*(void**)(b + 0x294)) {
        void* p = *(void**)(b + 0x294);
        *(uint32*)(b + 0x294) = 0;
        ((creature_instance_data*)p)->Release();
    }

    *(uint32*)(b + 0x2b0) = 0;
    *(uint32*)(b + 0x2b8) = 0;
    *(uint32*)(b + 0x2bc) = 0;
    *(uint32*)(b + 0x2b4) = 0xc;
    *(uint32*)(b + 0x2a8) = 0;
    *(uint32*)(b + 0x2ac) = 0xffffffffu;
    *(uint8*)(b + 0x260) = 1;  *(uint8*)(b + 0x261) = 0;
    *(uint8*)(b + 0x262) = 1;  *(uint8*)(b + 0x263) = 0;
    F(0x26c) = 0.0f;  F(0x264) = 0.0f;  F(0x268) = 0.0f;
    ((sub_2f8*)(b + 0x2f8))->FUN_009e3f70(6, 4);

    *(uint32*)(b + 0x1640) = 0;
    F(0x1650) = 0.0f; F(0x1654) = 0.0f; F(0x1658) = 0.0f; F(0x165c) = 1.0f;
    *(uint8*)(b + 0x168c) = 1;  *(uint8*)(b + 0x168d) = 1;
    *(uint8*)(b + 0x168e) = 1;  F(0x1690) = 0.0f;

    // mWiggles.clear()
    {
        vec2c* v = (vec2c*)(b + 0x1694);
        Elem2c* be = v->mpBegin;
        Elem2c* en = v->mpEnd;
        FUN_009b4a20(en, en, be);
        v->mpEnd += (en - be);
    }
    *(uint8*)(b + 0x1704) = 0;  *(uint8*)(b + 0x176c) = 0;
    *(uint8*)(b + 0x1794) = 1;  F(0x1798) = 0.0f;
    *(uint8*)(b + 0x179c) = 0;  *(uint8*)(b + 0x1680) = 1;
    *(uint32*)(b + 0x1684) = 0;
    *(uint32*)(b + 0x2d0) = 0xffffffffu;
    *(uint8*)(b + 0x2d4) = 1;  *(uint8*)(b + 0x2d5) = 0;
    *(uint32*)(b + 0x2dc) = 0;  *(uint32*)(b + 0x2d8) = 0;
    *(uint8*)(b + 0x2e0) = 1;
    *(uint32*)(b + 0x1ac) = 0;
    ((ik_vec*)(b + 0x24c))->resize(0);

    F(0x238) = 0.0f; F(0x23c) = 0.0f;
    F(0x240) = 0.0f; F(0x244) = 1.0f;
    F(0x248) = 1.0f;
    FUN_011e073e(b + 0x1f8, 0xaa, 0x40);
    FUN_011e073e(b + 0x1b8, 0, 0x40);
}
#undef F

// ------------------------------------------------------------------ @ 0x009c52a0

// @ 0x009c52a0
bool InitCreatureInstance(creature_static_data* c, creature_instance_data* inst,
                          float a, float fb, float p5, float p6, float p7,
                          float p8, float p9, int arg10)
{
    char* b = (char*)inst;
    unsigned count = (unsigned)((*(char**)((char*)c + 0x388) - *(char**)((char*)c + 0x384)) / 0x468);
    if (count == 0)
        return false;

    inst->Clear(false);

    creature_static_data* old = *(creature_static_data**)b;
    if (c != old) {
        if (c)
            ++*(int*)((char*)c + 0x348);
        *(creature_static_data**)b = c;
        if (old)
            old->Release();
    }
    *(uint8*)(b + 0xc) = 1;
    *(uint8*)((char*)c + 0x34c) = 0;

    *(float*)(b + 0x30) = a;
    *(float*)(b + 0x34) = fb;
    *(float*)(b + 0x38) = p5;
    *(float*)(b + 0x18) = a;
    *(float*)(b + 0x1c) = fb;
    *(float*)(b + 0x20) = p5;
    *(float*)(b + 0x24) = a;
    *(float*)(b + 0x28) = fb;
    *(float*)(b + 0x2c) = p5;
    *(float*)(b + 0x60) = p7;
    *(float*)(b + 0x64) = p8;
    *(float*)(b + 0x68) = p9;
    *(float*)(b + 0x5c) = p6;
    *(float*)(b + 0x3c) = p6;
    *(float*)(b + 0x40) = p7;
    *(float*)(b + 0x44) = p8;
    *(float*)(b + 0x48) = p9;
    *(float*)(b + 0x4c) = p6;
    *(float*)(b + 0x50) = p7;
    *(float*)(b + 0x54) = p8;
    *(float*)(b + 0x58) = p9;
    *(float*)(b + 0x1644) = a;
    *(float*)(b + 0x1648) = fb;
    *(float*)(b + 0x164c) = p5;
    *(float*)(b + 0x1650) = p6;
    *(float*)(b + 0x1654) = p7;
    *(float*)(b + 0x1658) = p8;
    *(float*)(b + 0x165c) = p9;
    *(float*)(b + 0x6c) = 1.0f;
    *(float*)(b + 0x70) = 1.0f;

    ((body_vec*)(b + 0x2e4))->FUN_009c3040((int)count);
    *(uint32*)(b + 8) = *(uint32*)(b + 0x2e4);
    *(float*)(b + 0x1660) = 0.0f; *(float*)(b + 0x1664) = 0.0f;
    *(float*)(b + 0x1668) = 0.0f; *(float*)(b + 0x166c) = 0.0f;
    *(float*)(b + 0x1670) = 0.0f; *(float*)(b + 0x1674) = 0.0f;
    *(float*)(b + 0x1678) = 0.0f; *(float*)(b + 0x167c) = 0.0f;
    FUN_009db1d0(b + 0x15b8);
    *(uint8*)(b + 0x270) = 1;

    // Per-body instance initialisation.
    for (unsigned i = 0; i < count; ++i) {
        char* e = *(char**)(b + 0x2e4) + i * 0x2bc;      // body instance record
        char* bs = *(char**)((char*)c + 0x384) + i * 0x468;
        *(uint32*)(e + 8) = 0;
        *(uint32*)(e + 0xc) = 0;
        for (int k = 0; k < 20; ++k)
            *(float*)(e + 0x58 + k * 4) = 0.0f;
        *(uint32*)(e + 0xa0) = 0;
        *(uint32*)(e + 0x48) = 0; *(uint32*)(e + 0x4c) = 0;
        *(uint32*)(e + 0x50) = 0;
        *(uint8*)(e + 0x54) = 0; *(uint8*)(e + 0x55) = 0;
        *(uint8*)(e + 0x2a0) = 0; *(uint8*)(e + 0x38) = 0;
        *(uint32*)(e + 0x144) = 0;
        *(void**)(e + 0) = bs;
        *(void**)(e + 4) = inst;
        *(uint32*)(e + 8) = 0;
        *(uint32*)(e + 0xc) = 0;
        *(float*)(e + 0x1c) = *(float*)(bs + 0x118);
        *(float*)(e + 0x20) = *(float*)(bs + 0x11c);
        *(float*)(e + 0x24) = *(float*)(bs + 0x120);
        *(float*)(e + 0x28) = *(float*)(bs + 0x124);
        float sc = *(float*)(b + 0x70);
        *(float*)(e + 0x10) = *(float*)(bs + 0x10c) * sc;
        *(float*)(e + 0x14) = *(float*)(bs + 0x110) * sc;
        *(float*)(e + 0x18) = *(float*)(bs + 0x114) * sc;
        *(uint8*)(e + 0x38) = 0;
        *(float*)(e + 0x3c) = *(float*)(e + 0x10);
        *(float*)(e + 0x40) = *(float*)(e + 0x14);
        *(float*)(e + 0x44) = *(float*)(e + 0x18);
        *(uint32*)(e + 0x144) = 0;
        *(float*)(e + 0x148) = 0.0f; *(float*)(e + 0x14c) = 0.0f;
        *(float*)(e + 0x150) = 0.0f; *(float*)(e + 0x154) = 1.0f;
        *(float*)(e + 0x158) = 0.0f; *(float*)(e + 0x15c) = 0.0f;
        *(float*)(e + 0x160) = 0.0f;
    }

    FUN_009bd340(inst);
    *(uint32*)(b + 0x1688) = arg10;
    *(uint8*)(b + 0x263) = 0;
    *(uint32*)(b + 0x1640) = 0;
    FUN_009db270(b + 0x15b8);

    if (*(int*)(*(char**)((char*)c + 0x3c8)) == 0)
        inst->BuildBodyList();
    else
        inst->FUN_009b6360();

    if (*(uint32*)(b + 0x1640) > 0) {
        void* gt = (void*)(b + 0x15b8);
        if (*(int*)(*(char**)((char*)c + 0x3c8)) == 0)
            FUN_009db6d0(gt, 2.0f, inst);
        else
            FUN_009db4d0(gt, 2.0f);
        FUN_009d34a0(gt);
        FUN_009da640(gt, inst);
        FUN_009d3170(gt);
    }

    inst->InitWiggles();
    return true;
}

}  // namespace nSPCreatureAnim
