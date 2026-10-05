// Slice s004fcae0: Simulator::cCreatureAbility ctor/dtor and small vector methods
// (unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast).
#include "types.h"

struct Vector3 { float x, y, z; };

extern int vtbl_Simulator_cCreatureAbility[];
extern int PTR_FUN_013f11b8[];

void FUN_004fd9a0(void* end, const void* val);   // 0x004fd9a0
void FUN_004fd940(void* p);                      // 0x004fd940
void FUN_0050e690(int a, int b);                 // 0x0050e690
void FUN_00548690(int a, int b);                 // 0x00548690
void FUN_00554b10(void* p);                      // 0x00554b10
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Pod16 { void* p0; void* p1; float f; void* p2; };

struct Vec24 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void push_back(const void* val);     // 0x004fd570
    int  size() const { return (int)(mpEnd - mpBegin) / 0x18; }
};

struct Vec16 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void push_back(const void* val);     // 0x004fd5e0
    int  size() const { return (int)(mpEnd - mpBegin) / 0x10; }
};

struct Ability {
    void* vptr;                                   // +0
    int m4;                                       // +4
    Vec24 mVec8;                                  // +8
    int m14, m18;                                 // +0x14,+0x18
    Vec16 mVec1c;                                 // +0x1c

    Ability();
    ~Ability();
    int Add(const Vector3* pos, float a, float b, int c);
    int Add2(void* a, void* b, float c, void* d);
    void Dispose();
};

// @ 0x004fcae0
Ability::Ability()
{
    ScratchSlots<1>();
    *(int**)this = vtbl_Simulator_cCreatureAbility;
    *(int*)((char*)this + 4) = 0;
    *(int**)this = PTR_FUN_013f11b8;
    int* p = (int*)((char*)this + 8);
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    int* q = (int*)((char*)this + 0x1c);
    q[0] = 0;
    q[1] = 0;
    q[2] = 0;
}

// @ 0x004fcb90
Ability::~Ability()
{
    *(int**)this = PTR_FUN_013f11b8;
    for (uint32_t i = *(uint32_t*)((char*)this + 8); i < *(uint32_t*)((char*)this + 0xc); i += 0x18) {
    }
    FUN_004fd940((char*)this + 8);
    for (uint32_t j = *(uint32_t*)((char*)this + 0x1c); j < *(uint32_t*)((char*)this + 0x20); j += 0x10) {
    }
    FUN_00554b10((char*)this + 0x1c);
    *(int**)this = vtbl_Simulator_cCreatureAbility;
}

// @ 0x004fcc20
int Ability::Add(const Vector3* pos, float a, float b, int c)
{
    float val[6];
    val[0] = pos->x;
    val[1] = pos->y;
    val[2] = pos->z;
    val[3] = a;
    val[4] = b;
    *(int*)&val[5] = c;
    ScratchSlots<2>();
    mVec8.push_back(val);
    return mVec8.size() - 1;
}

// @ 0x004fcca0
int Ability::Add2(void* a, void* b, float c, void* d)
{
    Pod16 val;
    val.p0 = a;
    val.p1 = b;
    val.f = c;
    val.p2 = d;
    mVec1c.push_back(&val);
    return mVec1c.size() - 1;
}

// @ 0x004fd520
void Ability::Dispose()
{
    FUN_0050e690(*(int*)((char*)this + 8), *(int*)((char*)this + 0xc));
    FUN_00548690(*(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20));
}

// @ 0x004fd5e0
void Vec16::push_back(const void* val)
{
    if (mpEnd < mpCapacity) {
        char* p = mpEnd;
        mpEnd += 0x10;
        if (p) {
            *(uint32_t*)(p + 0x0) = *(const uint32_t*)((const char*)val + 0x0);
            *(uint32_t*)(p + 0x4) = *(const uint32_t*)((const char*)val + 0x4);
            *(uint32_t*)(p + 0x8) = *(const uint32_t*)((const char*)val + 0x8);
            *(uint32_t*)(p + 0xc) = *(const uint32_t*)((const char*)val + 0xc);
        }
    } else {
        FUN_004fd9a0(mpEnd, val);
    }
}

// @ 0x004fd670
void CopyPod24(void* dst, const void* src)
{
    *(float*)((char*)dst + 0x00) = *(const float*)((char*)src + 0x00);
    *(float*)((char*)dst + 0x04) = *(const float*)((char*)src + 0x04);
    *(float*)((char*)dst + 0x08) = *(const float*)((char*)src + 0x08);
    *(float*)((char*)dst + 0x0c) = *(const float*)((char*)src + 0x0c);
    *(float*)((char*)dst + 0x10) = *(const float*)((char*)src + 0x10);
    *(int*)((char*)dst + 0x14) = *(const int*)((char*)src + 0x14);
}

// ---------------------------------------------------------------------------
// The remaining functions are large /Od bodies whose full reconstruction was out
// of budget; they are listed in partial.txt as skeletons.
// ---------------------------------------------------------------------------
// @ 0x004fcd00
void FUN_004fcd00() {}
// @ 0x004fd380
void FUN_004fd380() {}
// @ 0x004fd6d0
void FUN_004fd6d0() {}

