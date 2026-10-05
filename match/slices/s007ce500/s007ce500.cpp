// Slice s007ce500 (w2g5 slices 7-9).  Region: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
// Contains: anonymous-namespace GroundCoverCirclePhysics, SP::InitAppEffects,
// and a family of eastl::vector<eastl::pair<...>> template instances.
#include "types.h"

// ---------------------------------------------------------------- intrinsics
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---------------------------------------------------------------- EA allocator hooks (addresses only)
extern "C" void* __cdecl EAlloc(uint32_t size, const char* name, int flags, int debugFlags,
                                const char* file, int line);   // 0x00f473a0
extern "C" void  __cdecl EFree(void* p);                       // 0x00f47380
extern "C" double __cdecl sqrt(double);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);

// ===========================================================================
// 0x007ce500  anonymous_namespace::GroundCoverCirclePhysics
// ===========================================================================
struct RandomLinearCongruential {          // thiscall receiver at 0x016778dc
    double RandomDoubleUniform();
};
extern RandomLinearCongruential sRandom;   // 0x016778dc

extern const float g_153d63c;   // 0x0153d63c
extern const float g_153d638;   // 0x0153d638
extern const float g_1485378;   // 0x01485378
extern uint32_t    g_153d634;   // 0x0153d634

extern "C" float* FUN_007cdbe0(float* out, char* p);       // 0x007cdbe0
extern "C" float* FUN_00a816d0();                          // 0x00a816d0
extern "C" float* FUN_00a817c0(float* a, char* p, float f); // 0x00a817c0
extern "C" void   FUN_007cdee0(float* v);                  // 0x007cdee0
extern "C" void   FUN_007cda70(float* v);                  // 0x007cda70
extern "C" double FUN_007cdb90(float* v);                  // 0x007cdb90

struct IFilter {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual bool Test(float* pos, float* a, float* b, int c, int d, int e); // slot 4
};
struct IVec3Provider {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void a4();
    virtual void a5();
    virtual bool Contains(float* v);       // slot 6 (0x18)
    virtual float Get(float* v);           // slot 7 (0x1c)
    virtual void Lambda(float* out, float* v); // slot 8 (0x20)
    virtual void Get2(float* out, float* v);   // slot 9 (0x24)
    virtual void Sub(float* out, float* v);    // slot 10 (0x28)
};

int GroundCoverCirclePhysics(char* self, float dt, char* p3, char* p4)
{
    float acc = dt + *(float*)(self + 8);
    *(float*)(self + 8) = acc;
    if (*(float*)(self + 0xc) <= acc)
        return 0;

    float m0 = *(float*)(p4 + 0xcc);
    float m1 = *(float*)(p4 + 0xd0);
    float m2 = *(float*)(p4 + 0xd4);
    float vx = m0, vy = m1, vz = m2;
    if (*(uint8_t*)(p4 + 0x100) & 2) {
        vx = *(float*)(p4 + 0x12c) * m2 + *(float*)(p4 + 0x120) * m1 + *(float*)(p4 + 0x114) * m0;
        vy = *(float*)(p4 + 0x118) * m0 + *(float*)(p4 + 0x130) * m2 + *(float*)(p4 + 0x124) * m1;
        vz = *(float*)(p4 + 0x11c) * m0 + *(float*)(p4 + 0x134) * m2 + *(float*)(p4 + 0x128) * m1;
    }
    float k = *(float*)(p4 + 0x110);
    float* pos = (float*)(self + 0x10);
    float cx = *(float*)(p4 + 0x104) + k * vx;
    float sx0 = *pos;
    float cy = *(float*)(p4 + 0x108) + k * vy;
    float sy0 = *(float*)(self + 0x14);
    float cz = *(float*)(p4 + 0x10c) + k * vz;
    float sz0 = *(float*)(self + 0x18);
    float rx = sx0, ry = sy0, rz = sz0;
    if (*(uint8_t*)(p4 + 0x100) & 2) {
        rx = *(float*)(p4 + 0x12c) * sz0 + *(float*)(p4 + 0x120) * sy0 + sx0 * *(float*)(p4 + 0x114);
        ry = *(float*)(p4 + 0x118) * sx0 + *(float*)(p4 + 0x130) * sz0 + *(float*)(p4 + 0x124) * sy0;
        rz = *(float*)(p4 + 0x11c) * sx0 + *(float*)(p4 + 0x134) * sz0 + *(float*)(p4 + 0x128) * sy0;
    }
    float k2 = *(float*)(p4 + 0x110);
    float px = *(float*)(p4 + 0x104) + rx * k2;
    float py = *(float*)(p4 + 0x108) + ry * k2;
    float pz = *(float*)(p4 + 0x10c) + rz * k2;

    float A = (cx * cx + cz * cz) + cy * cy;
    float B = (px * cx + pz * cz) + py * cy;
    float C = (px * px + pz * pz) + py * py;

    if (B * B < ((A / (g_153d63c * g_153d63c + A)) * C) * A) {
        double r = sRandom.RandomDoubleUniform();
        if ((float)r >= g_153d638) {
            float t = B / A;
            double r2 = sRandom.RandomDoubleUniform();
            double s = (1.0 - r2) * ((double)t / sqrt((double)C - (double)t * (double)B)) * (double)g_153d63c + r2;
            float f = (float)(s + s);
            px = (cx * t - px) * f + px;
            py = (cy * t - py) * f + py;
            pz = (cz * t - pz) * f + pz;
            *pos = px;
            *(float*)(self + 0x14) = py;
            *(float*)(self + 0x18) = pz;
        } else if (*(float*)(p3 + 100) < 0.0f) {
            float* v;
            if ((*(uint32_t*)(p3 + 8) >> 4 & 1) == 0)
                v = FUN_007cdbe0(&cx, p4 + 0x1c0);
            else
                v = FUN_00a816d0();
            *pos = v[0]; *(float*)(self + 0x14) = v[1]; *(float*)(self + 0x18) = v[2];
            FUN_007cdee0(pos);
        } else {
            float* v = FUN_00a817c0(&cx, p4 + 0x1c0, *(float*)(p3 + 100));
            *pos = v[0]; *(float*)(self + 0x14) = v[1]; *(float*)(self + 0x18) = v[2];
            FUN_007cdee0(pos);
        }
        *(uint32_t*)(self + 0x34) = 0x3f800000;
        if (*(char*)(p4 + 0x210) != 0) {
            uint32_t* it = *(uint32_t**)(p4 + 0x1e4);
            int base = *(int*)(p4 + 0x1fc);
            if (it != *(uint32_t**)(p4 + 0x1e8)) {
                do {
                    if ((float)(*(uint32_t*)it[1] & g_153d634) != 0.0f) {
                        int iv = (it[2] == 0) ? 0 : (int)it[3] + base;
                        IFilter* f = (IFilter*)it[0];
                        if (f->Test(pos, pos, &cx, 0, iv, 0)) {
                            float w = *(float*)((char*)it[1] + 0x20);
                            if (w != 0.0f) {
                                *pos = cx * w + *pos;
                                *(float*)(self + 0x14) += cy * w;
                                *(float*)(self + 0x18) += cz * w;
                            }
                            break;
                        }
                    }
                    it += 6;
                } while (it != *(uint32_t**)(p4 + 0x1e8));
            }
        }
        if (((*(uint32_t*)(p3 + 8) >> 5 & 1) != 0) && *(int*)(p4 + 0x1b4) != 0) {
            float a = *pos, b = *(float*)(self + 0x14), c = *(float*)(self + 0x18);
            if (*(char*)(p4 + 0x1bd) == 0) FUN_007cda70(&a); else FUN_007cdee0(&a);
            IVec3Provider* p = *(IVec3Provider**)(p4 + 0x1b4);
            if (p->Contains(&a)) {
                float d = p->Get(&a);
                c = d;
                float e = *(float*)(p4 + 0x1c8);
                float g = *(float*)(p4 + 0x1d4);
                c = (float)(FUN_007cdb90(&e) + (double)c);
                if (*(char*)(p4 + 0x1bd) == 0) FUN_007cdee0(&a); else FUN_007cda70(&a);
                *pos = a; *(float*)(self + 0x14) = b; *(float*)(self + 0x18) = c;
            }
        }
        if (*(int*)(p4 + 0x1b8) != 0) {
            float a = *pos, b = *(float*)(self + 0x14), c = *(float*)(self + 0x18);
            if (*(char*)(p4 + 0x1be) == 0) FUN_007cda70(&a); else FUN_007cdee0(&a);
            IVec3Provider* p = *(IVec3Provider**)(p4 + 0x1b8);
            if (p->Contains(&a)) {
                p->Sub(&a, &a);
                *(float*)(self + 0x38) = a;
                *(float*)(self + 0x3c) = b;
                *(float*)(self + 0x34) = c * *(float*)(self + 0x34);
                *(float*)(self + 0x40) = *(float*)(self + 0x18);
            }
        }
        if (*(int*)(p4 + 0x1b4) != 0) {
            float a = *pos, b = *(float*)(self + 0x14), c = *(float*)(self + 0x18);
            if (*(char*)(p4 + 0x1bd) == 0) FUN_007cda70(&a); else FUN_007cdee0(&a);
            float d = (*(IVec3Provider**)(p4 + 0x1b4))->Get(&a);
            if (d < 0.5f) *(uint32_t*)(self + 0x34) = 0;
        }
    }
    return 1;
}

// ===========================================================================
// 0x007cec80  SP::InitAppEffects
// ===========================================================================
struct IPropertyManager {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual bool GetProperty(uint32_t key, uint32_t hash, void* out);  // 0x2c
};
extern "C" IPropertyManager* PropertyManager();   // 0x0067de30

struct GroundCoverConfig;
template <typename T> struct AutoRefT {
    T* mpObject;
    AutoRefT& operator=(T* p)
    {
        if (p != mpObject) {
            T* pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
struct GroundCoverConfig {
    virtual int AddRef();           // slot 0
    virtual int Release();          // slot 1 (0x4)
};
extern AutoRefT<GroundCoverConfig> sGroundCoverConfig;   // 0x01636e18

extern "C" void FUN_007d4460();
extern "C" void FUN_007d5ff0();
extern "C" void FUN_007e09a0();
extern "C" void FUN_007e12a0();
extern "C" void FUN_007ef270();
extern "C" void FUN_007efa10();
extern "C" void FUN_007edc10();
extern "C" void FUN_007ee450();
extern "C" void FUN_00a99150();
extern "C" void FUN_007d7f40();
extern "C" void FUN_007cdff0();
extern "C" void FUN_00aa7fa0(int, void (*)());
extern "C" void UpdateFromGroundCoverConfig();

void SP_InitAppEffects()
{
    FUN_007d4460();
    FUN_007d5ff0();
    FUN_007e09a0();
    FUN_007e12a0();
    FUN_007ef270();
    FUN_007efa10();
    FUN_007edc10();
    FUN_007ee450();
    FUN_00a99150();
    FUN_007d7f40();
    FUN_00aa7fa0(3, FUN_007cdff0);
    FUN_00aa7fa0(4, FUN_007cdff0);
    IPropertyManager* pm = PropertyManager();
    sGroundCoverConfig = (GroundCoverConfig*)0;
    if (pm->GetProperty(0xc6db66f9, 0xea5118b1, &sGroundCoverConfig))
        UpdateFromGroundCoverConfig();
}

// ===========================================================================
// 0x007ced20  destructor (class with vtable 0x1411b88 -> base 0x13eb394)
// ===========================================================================
struct IMessagingServer {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void Unregister(void* obj, int id, int code);   // 0x2c
};
extern "C" IMessagingServer* GetServer();  // 0x00883860

struct PaintSystemBase {
    virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3();
    virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7();
    virtual ~PaintSystemBase() {}
};
struct DerivedPaint : PaintSystemBase {
    virtual ~DerivedPaint();
    bool mb4;           // +4
    char pad5[3];
    void* m8;           // +8
    char padC[0x1c - 0xc];
    int m1c;            // +0x1c
};
DerivedPaint::~DerivedPaint()
{
    if (mb4) {
        GetServer()->Unregister(this, m1c, 0xffffd8f1);
        m1c = 0;
        mb4 = false;
    }
    void* p = m8;
    if (p && *(int*)((char*)p - 4) != 0)
        EFree(p);
}
void ForceEmit_DP(DerivedPaint* p) { p->~DerivedPaint(); }

// ===========================================================================
// eastl::pair<uint64_t, AutoRefCount<...>> range helpers
// ===========================================================================
struct PropList {
    virtual void v0();          // +0
    int m4;                     // +4
    volatile long mRefCount;    // +8
    int Release()
    {
        _InterlockedExchangeAdd(&mRefCount, -1);
        if (_InterlockedExchangeAdd(&mRefCount, 0) < 1) {
            _InterlockedExchangeAdd(&mRefCount, 1);
            return 1;
        }
        return _InterlockedExchangeAdd(&mRefCount, 0);
    }
    void AddRef() { _InterlockedExchangeAdd(&mRefCount, 1); }
};
struct PropPair {
    uint64_t first;
    PropList* pObj;
};

inline void ReleaseProp(PropList* p)
{
    p->Release();
}
inline void AddRefProp(PropList* p)
{
    p->AddRef();
}

// @ 0x007cede0  DestructRange(begin,end,out)
void* DestructRange_7cede0(PropPair* begin, PropPair* end, char* out)
{
    for (; begin != end; begin = (PropPair*)((char*)begin + 0x10)) {
        if (begin->pObj)
            ReleaseProp(begin->pObj);
        out += 0x10;
    }
    return out;
}

// @ 0x007cee40  CopyRange(begin,end,dst)
void CopyRange_7cee40(PropPair* begin, PropPair* end, PropPair* dst)
{
    for (; begin != end; begin = (PropPair*)((char*)begin + 0x10), dst = (PropPair*)((char*)dst + 0x10)) {
        dst->first = begin->first;
        PropList* nv = begin->pObj;
        PropList* ov = dst->pObj;
        if (nv != ov) {
            if (nv) AddRefProp(nv);
            dst->pObj = nv;
            if (ov) ReleaseProp(ov);
        }
    }
}

// @ 0x007ceec0  CopyBackward(first,last,dst)
void CopyBackward_7ceec0(PropPair* first, PropPair* last, PropPair* dst)
{
    while (last != first) {
        last = (PropPair*)((char*)last - 0x10);
        dst = (PropPair*)((char*)dst - 0x10);
        dst->first = last->first;
        PropList* nv = last->pObj;
        PropList* ov = dst->pObj;
        if (nv != ov) {
            if (nv) AddRefProp(nv);
            dst->pObj = nv;
            if (ov) ReleaseProp(ov);
        }
    }
}

// @ 0x007cefd0  DestructRange2(begin,end) __stdcall
void __stdcall DestructRange2_7cefd0(PropPair* begin, PropPair* end)
{
    while (begin < end) {
        if (begin->pObj)
            ReleaseProp(begin->pObj);
        begin = (PropPair*)((char*)begin + 0x10);
    }
}

// @ 0x007cef40  ctor for the class holding a vector at +8
struct HasVt {
    virtual void d0();
};
struct VecHolder : HasVt {
    bool mb4;
    char pad5[3];
    void* mBegin;   // +8
    void* mEnd;     // +0xc
    void* mCap;     // +0x10
    VecHolder();
};
VecHolder::VecHolder() : mb4(false), mBegin(0), mEnd(0), mCap(0) {}

// ===========================================================================
// eastl::vector<pair<uint64_t, VirtualObj*>> destructor
// ===========================================================================
struct VirtualObj {
    virtual void v0();
    virtual int Release();   // slot 1 (0x4)
    virtual void v2();
};
template <typename T> struct AutoRef {
    T* mpObject;
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};
struct VPair {
    uint64_t first;
    AutoRef<VirtualObj> pObj;
};
struct VVec {
    VPair* mpBegin;   // +0
    VPair* mpEnd;     // +4
    VPair* mpEndCap;  // +8
    ~VVec();
};
VVec::~VVec()
{
    for (VPair* p = mpBegin; p < mpEnd; p = (VPair*)((char*)p + 0x10))
        p->~VPair();
    if (mpBegin)
        EFree(mpBegin);
}
void ForceEmit_VecDtor(VVec* v) { delete v; }

// ===========================================================================
// 8-byte element vector insert helpers
// ===========================================================================
struct P8 { uint32_t a, b; };
extern "C" void* __cdecl FUN_0099efa0(void* src, void* end, void* dst); // uninitialized_copy
extern "C" void  __cdecl FUN_0076ffd0(void* a, void* b, void* c, void* d, void* e);
extern "C" void  __cdecl FUN_0073fe50(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_00a52da0(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_006ac440(void* a, int n, void* v);

struct Vec8 {
    P8* mpBegin;
    P8* mpEnd;
    P8* mpEndCap;
    void insert(P8* pos, uint32_t n, const P8& value);
    void insert(P8* pos, const P8& value);
};

// @ 0x007cf030  insert(pos, n, value)
void Vec8::insert(P8* pos, uint32_t n, const P8& value)
{
    if ((uint32_t)(mpEndCap - mpEnd) < n) {
        uint32_t len = (uint32_t)(mpEnd - mpBegin);
        uint32_t newCap = len * 2;
        if (len == 0) newCap = 1;
        uint32_t need = len + n;
        if (need > newCap) newCap = need;
        P8* nb = newCap ? (P8*)EAlloc(newCap * 8, "App", 0, 0,
             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        P8* mid = (P8*)FUN_0099efa0(mpBegin, pos, nb);
        P8* fill = mid;
        for (uint32_t i = n; i != 0; --i) {
            if (fill) { fill->a = value.a; fill->b = value.b; }
            fill++;
        }
        P8* ne = (P8*)FUN_0099efa0(pos, mpEnd, fill);
        P8* old = mpBegin;
        if (old && *(int*)((char*)old - 4) != 0)
            EFree(old);
        mpBegin = nb;
        mpEnd = ne;
        mpEndCap = nb + newCap;
    } else if (n != 0) {
        P8 local = value;
        P8* end = mpEnd;
        uint32_t tail = (uint32_t)(end - pos);
        if (n < tail) {
            uint32_t nn = n * 8;
            P8* src = (P8*)((char*)end - nn);
            FUN_0076ffd0(&pos, src, end, end, src);
            mpEnd = (P8*)((char*)mpEnd + nn);
            FUN_0073fe50(pos, src, end);
            FUN_00a52da0(pos, (char*)pos + nn, &local);
        } else {
            uint32_t extra = n - tail;
            FUN_006ac440(end, extra, &local);
            mpEnd = (P8*)((char*)mpEnd + extra * 8);
            FUN_0076ffd0(&pos, pos, end, mpEnd, (void*)tail);
            mpEnd = (P8*)((char*)mpEnd + tail * 8);
            FUN_00a52da0(pos, end, &local);
        }
    }
}

// @ 0x007cf1f0  insert(pos, value)
void Vec8::insert(P8* pos, const P8& value)
{
    if (mpEnd != mpEndCap) {
        if (pos <= &value && &value < mpEnd)
            pos += 1;
        if (mpEnd) {
            mpEnd->a = mpEnd[-1].a;
            mpEnd->b = mpEnd[-1].b;
        }
        char* src = (char*)pos;
        int n = (int)((char*)mpEnd - 8 - src);
        memmove((char*)mpEnd + (n >> 3) * -8, src, n);
        *pos = value;
        mpEnd = (P8*)((char*)mpEnd + 8);
        return;
    }
    uint32_t len = (uint32_t)(mpEnd - mpBegin);
    uint32_t newCap;
    if (len == 0) newCap = 1;
    else { newCap = len * 2; if (newCap == 0) newCap = 1; }
    P8* nb = (P8*)EAlloc(newCap * 8, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    // first half
    int s1 = (int)((char*)pos - (char*)mpBegin);
    char* d1 = (char*)FUN_0099efa0(mpBegin, pos, nb);
    P8* mid = (P8*)(d1 + (s1 >> 3) * 8);
    if (mid) { mid->a = value.a; mid->b = value.b; }
    P8* ne = (P8*)FUN_0099efa0(pos, mpEnd, mid + 1);
    if (mpBegin) EFree(mpBegin);
    mpBegin = nb;
    mpEnd = (P8*)((char*)ne + ((char*)mpEnd - (char*)pos >> 3) * 8);
    mpEndCap = nb + newCap;
}
