// Slice s004fcae0: Simulator::cCreatureAbility ctor/dtor and small vector methods
// (unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast).
#include "types.h"
#include <cmath>

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
// Samples a relativistic-style acceleration profile between two points and emits one
// FUN_004f8a40 record per step (log-spaced when |d| > 1e-6, linear otherwise).
struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(const Vec3f& o) : x(o.x), y(o.y), z(o.z) {}
    Vec3f& operator=(const Vec3f& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
extern float g_013f11b4;   // 0x013f11b4 (0.25f at runtime, read from memory)
struct Owner {
    char pad[0xc];
    float mScale;                                                // +0xc
    void Emit(const Vec3f* pos, float a, float b, int c);        // 0x004f8a40 (ret 0x10)
};
Vec3f Vec3Sub(const Vec3f* a, const Vec3f* b);               // 0x0041db10 (sret, cdecl)
Vec3f Vec3Add(const Vec3f* a, const Vec3f& b);               // 0x0041dc10
Vec3f Vec3Scale(const float* s, const Vec3f* v);             // 0x0041de40
Vec3f Vec3Div(const Vec3f* v, const float* s);               // 0x00453880
float VectorLength(const Vec3f* v);                          // 0x0040ae50

struct Stepper {
    void Run(Owner* owner, float k0, Vec3f* pA, float pSpeed, float p5, Vec3f* pB, float p7,
             float p8, int p9);
};

// Local names below are chosen only to reproduce the /Od frame slot order.
// @ 0x004fcd00
void Stepper::Run(Owner* owner, float k0, Vec3f* pA, float pSpeed, float p5, Vec3f* pB, float p7,
                  float p8, int p9)
{
    float begin;
    Vec3f where;
    float mid;
    float p30;
    float p4;
    Vec3f p18;
    float n31;
    where = Vec3Sub(pB, pA);
    n31 = VectorLength(&where);
    p18 = Vec3Div(&where, &n31);
    begin = (float)sqrt((double)(1.0f - pow(owner->mScale / pSpeed, g_013f11b4))) * p5 + 1e-6f;
    mid = (float)sqrt((double)(1.0f - pow(owner->mScale / p7, g_013f11b4))) * p8 + 1e-6f;
    p4 = (begin - mid) / n31;
    p30 = k0;
    if ((float)fabs((double)p4) > 1e-6) {
    float t25;
    int v1;
    float p20;
    float i;
    float n16;
        n16 = (1.0f - p30 * p4) / (p30 * p4 + 1.0f);
        p20 = log(1.0f - n31 * p4 / begin) / (float)log((double)n16);
        t25 = ceil(p20);
        i = pow(1.0f - n31 * p4 / begin, 1.0f / t25);
        p30 = (1.0f - i) / ((1.0f + i) * p4);
        n16 = (1.0f - p30 * p4) / (p30 * p4 + 1.0f);
        v1 = (int)t25;
        for (int v37 = 1; v37 < v1; v37++) {
    float chunk;
    float v13;
    float n30;
    float t35;
    float p14;
    Vec3f pos;
            n30 = pSpeed;
            p14 = pow(n16, (float)v37);
            t35 = p14 * begin;
            v13 = t35 / (float)sqrt((double)(1.0f - pow(owner->mScale / n30, g_013f11b4)));
            chunk = (1.0f - p14) * begin / p4;
            pos = Vec3Add(pA, Vec3Scale(&chunk, &p18));
            owner->Emit(&pos, n30, v13, p9);
        }
    } else {
    float buf;
    int p6;
    float p10;
        buf = (p30 * p4 + 1.0f) * n31 / (2.0f * p30 * begin);
        p10 = ceil(buf);
        p30 = n31 / (2.0f * begin * p10 - p4 * n31);
        p6 = (int)p10;
        for (int p22 = 1; p22 < p6; p22++) {
    float p21;
    float v34;
    float n6;
    float hash;
    Vec3f pos;
            n6 = pSpeed;
            p21 = begin;
            hash = p21 / (float)sqrt((double)(1.0f - pow(owner->mScale / n6, g_013f11b4)));
            v34 = 2.0f * p30 * begin * (float)p22 / (p30 * p4 + 1.0f);
            pos = Vec3Add(pA, Vec3Scale(&v34, &p18));
            owner->Emit(&pos, n6, hash, p9);
        }
    }
}

// @ 0x004fd380
void FUN_004fd380() {}
// @ 0x004fd6d0
void FUN_004fd6d0() {}

