// src/game/SPEngine/_at_006c0000.cpp -- migrated from slice(s) s006cdca0, s006c4a70, s006c3b90, s006c2cd0, s006c1cd0, s006c0db0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_006c0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_16c8b44;                                    // 0x16c8b44  SP::cSPMemPool singleton
#include <string.h>
#include "rw/core/arena/Arena.h"
#include <math.h>
#include <xmmintrin.h>

// ---- items of slice s006c0db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
struct CtlKey { void* KeyOf(int idx); };                   // 0x11fd860
extern u32   __fastcall sub_928a30_t(void* self, int, u32, u32, int,int,int,int,int,int); // 0x928a30
extern void* g_16c8b44;                                    // 0x16c8b44  SP::cSPMemPool singleton
// ---- items of slice s006c0db0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32   __fastcall sub_928a30_t(void* self, int, u32, u32, int,int,int,int,int,int); // 0x928a30

// ---- items of slice s006c1cd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
struct Key16 { u32 k0, k1, k2, k3; };
#define KEY_LESS(x, y) ((x)[1] < (y)[1] || ((x)[1] == (y)[1] && ((x)[0] < (y)[0] || ((x)[0] == (y)[0] && ((x)[3] < (y)[3] || ((x)[3] == (y)[3] && (x)[2] < (y)[2]))))))
#define LESS6(a0, a1, a2, a3, b) ((a1) < (b)[1] || ((a1) == (b)[1] && ((a0) < (b)[0] || ((a0) == (b)[0] && ((a3) < (b)[3] || ((a3) == (b)[3] && (a2) < (b)[2]))))))
struct KeyPack {
    Key16 v[4];
    void Assign(const u32* a, const u32* b, const u32* c, const u32* d);
};
struct Rec16 {
    u32 a, b;
    u16 c, d;
    void* p;
    Rec16* CopyFrom(const Rec16* src);
};
typedef void* (__thiscall* BakeFrameAtFn)(void* ctl, u32 frame);
typedef void  (__thiscall* EmbeddedSetTransformFn)(void* self, const float* m, int a, int b);
struct BakePair {
    void* state;   // +0x00
    u32   frame;   // +0x04
};
struct BakeContext {
    char       rsv00[8];
    BakePair*  pairs;     // +0x08
    char       rsv0c[4];
    u32**      flagsPtr;  // +0x10
};
struct BakeFrameCtl {
    char rsv00[0x14];
    u32  frameCount;      // +0x14
};
// ---- items of slice s006c1cd0 end

// ---- items of slice s006c2cd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static __forceinline float MulSS(float a, float b) {
  return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static __forceinline float AddSS(float a, float b) {
  return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
struct Mat4 {
  float m[16];
  void SetRows(const float* r0, const float* r1, const float* r2, const float* r3); // 0x006c2740
};
struct Rec24 { uint32_t f0, f1, f2, f3, f4, f5; };
void AdjustHeap(Rec24* base, int hole, int len, int top, Rec24 value);
int FUN_0071ddc0(int res, int a, int b, int c, int d);
struct RefCounted {
  virtual void AddRef();   // vtable[0]
  virtual void Release();  // vtable[1]
};
struct Range {
  char pad0[4];
  int base;        // +4
  char pad1[2];
  uint16_t stride; // +0xa
};
struct Descriptor;
struct Container {
  virtual void slot0(Descriptor* out, int b);  // vtable[0]
  char pad0[8];
  char* begin;  // +0xc
  char* end;    // +0x10
  Descriptor* MakeDescriptor(Descriptor* out);
};
struct Descriptor {
  int count;        // +0
  void* first;      // +4
  uint16_t a;       // +8
  uint16_t b;       // +0xa
  Container* owner; // +0xc
};
struct RBNode {
  char pad0[0x10];
  int key0;  // +0x10
  int key1;  // +0x14
};
void RBTreeInsert(RBNode* node, RBNode* hint, RBNode* header, int side); // 0x009216a0
void* EASTL_alloc(int size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
struct RBTree {
  char pad0[0x14];
  int count;       // +0x14
  RBNode** insert(RBNode** out, RBNode* hint, const int* key, bool flag);
};
static float SignF(float v) {
  if (v > 0.0f) return 1.0f;
  if (v < 0.0f) return -1.0f;
  return 0.0f;
}
struct BaseA {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
};
struct BaseB {
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
};
struct BakedArenaThing : BaseA, BaseB {
  int m_ref;      // +8
  int m_c;        // +0xc
  int m_10;       // +0x10
  int m_14;       // +0x14
  int m_20;       // +0x20
  BakedArenaThing();
};
// ---- items of slice s006c2cd0 end

// ---- items of slice s006c3b90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Rec24_s006c_3b90 {
  uint64_t k0, k1, k2;
};
inline bool operator<(const Rec24_s006c_3b90& a, const Rec24_s006c_3b90& b) {
  return a.k0 < b.k0 || (a.k0 == b.k0 && a.k1 < b.k1);
}
void AdjustHeap(Rec24_s006c_3b90* base, int hole, int len, int top, Rec24_s006c_3b90 value); // 0x006c2bc0
void MakeHeap(Rec24_s006c_3b90* first, Rec24_s006c_3b90* last);                              // 0x006c33b0
void SortHeap(Rec24_s006c_3b90* first, Rec24_s006c_3b90* last);                              // 0x006c3430
struct Mat4_s006c_3b90 {
  float m[16];
  void SetRows(const float* r0, const float* r1, const float* r2, const float* r3);
  void Assign(const float* a, const float* b, const float* c, const float* d); // 0x006c2740
};
float* ScaleMatrixReversed(float* out, const float* m, float s); // 0x006c2cd0
inline void Mat4_s006c_3b90::SetRows(const float* r0, const float* r1, const float* r2, const float* r3) {
  Assign(r0, r1, r2, r3);
}
static void BakeWeighted(float* outA, float* outB, const float* base, const float* dir,
                         const float* s, const int* idx, int layout, int count) {
  uint16_t stride = *(uint16_t*)(layout + 0xa);
  char* seg = (char*)*(int*)(layout + 4);
  char* blk = seg + stride * idx[0];
  float fourth[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  Mat4_s006c_3b90 m;
  m.SetRows((const float*)blk, (const float*)(blk + 0x10), (const float*)(blk + 0x20), fourth);
  float sm[16];
  ScaleMatrixReversed(sm, m.m, s[0]);

  for (int k = 1; k <= count; ++k) {
    const float* q = (const float*)(seg + stride * idx[k]);
    float w = s[k];
    float zw = w * 0.0f;
    sm[0]  += q[0]  * w; sm[1]  += q[1]  * w; sm[2]  += q[2]  * w; sm[3]  += q[3]  * w;
    sm[4]  += q[4]  * w; sm[5]  += q[5]  * w; sm[6]  += q[6]  * w; sm[7]  += q[7]  * w;
    sm[8]  += q[8]  * w; sm[9]  += q[9]  * w; sm[10] += q[10] * w; sm[11] += q[11] * w;
    sm[12] += zw; sm[13] += zw; sm[14] += zw; sm[15] += w;
  }

  float d0 = dir[0], d1 = dir[1], d2 = dir[2];
  float b0 = base[0], b1 = base[1], b2 = base[2];

  outB[0] = ((d2 * sm[8] + d0 * sm[0]) + d1 * sm[4]) + sm[12] * 0.0f;
  outB[1] = ((d1 * sm[5] + d2 * sm[9]) + d0 * sm[1]) + sm[13] * 0.0f;
  outB[2] = ((d1 * sm[6] + d2 * sm[10]) + d0 * sm[2]) + sm[14] * 0.0f;

  outA[0] = ((b2 * sm[8] + b0 * sm[0]) + b1 * sm[4]) + sm[12];
  outA[1] = ((b1 * sm[5] + b2 * sm[9]) + b0 * sm[1]) + sm[13];
  outA[2] = ((b1 * sm[6] + b2 * sm[10]) + b0 * sm[2]) + sm[14];
}
// ---- items of slice s006c3b90 end

// ---- items of slice s006c4a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Rec24_s006c_4a70 {
  uint64_t k0, k1, k2;
};
Rec24_s006c_4a70* GetPartition(Rec24_s006c_4a70* first, Rec24_s006c_4a70* last, Rec24_s006c_4a70 pivot);           // 0x006c4870
void PartialSort(Rec24_s006c_4a70* first, Rec24_s006c_4a70* middle, Rec24_s006c_4a70* last);            // 0x006c4960
Rec24_s006c_4a70* Median(Rec24_s006c_4a70* a, Rec24_s006c_4a70* b, Rec24_s006c_4a70* c);                           // 0x006c2970
void InsertionSortA(Rec24_s006c_4a70* first, Rec24_s006c_4a70* last);                        // 0x006c27b0
void InsertionSortB(Rec24_s006c_4a70* first, Rec24_s006c_4a70* last);                        // 0x006c28a0
static inline int Log2(int n) {
  int i = 0;
  while (n > 0) {
    n >>= 1;
    ++i;
  }
  return i - 1;
}
// ---- items of slice s006c4a70 end

// ---- items of slice s006cdca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline float BakeMulSS(float a, float b)
{
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static inline float BakeAddSS(float a, float b)
{
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static inline float BakeSubSS(float a, float b)
{
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
struct RefObject
{
    virtual void AddRef();
    virtual void Release();
};
struct Handle
{
    uint32_t a;         // +0
    uint32_t b;         // +4  data base
    uint16_t c;         // +8
    uint16_t d;         // +a  stride
    RefObject* mpRef;   // +c

    Handle() : a(0), b(0), c(0), d(0), mpRef(0) {}
    Handle(const Handle& o) : a(o.a), b(o.b), c(o.c), d(o.d), mpRef(o.mpRef)
    {
        if (mpRef)
            mpRef->AddRef();
    }
    ~Handle()
    {
        if (mpRef)
            mpRef->Release();
    }
    Handle* Assign(const Handle* src);   // out of line: 0x00424f70
};
struct Elem32
{
    uint32_t w0, w1, w2, w3;
    Handle handle;
};
struct ElemTable
{
    uint32_t p0;
    uint32_t p4;
    Elem32* mBegin;
};
struct BakeEntry
{
    uint32_t f0;        // +0   index into the param_5 (position) stream
    uint32_t f4;        // +4
    uint32_t f8;        // +8   index into the handle's colour stream
    uint32_t fc;        // +c   index into the handle's uv stream
    uint32_t f10;       // +10
    uint32_t f14;       // +14
};
struct StreamDesc
{
    uint32_t p0;
    uint32_t base;
    uint16_t p8;
    uint16_t stride;
    uint32_t pc;
};
struct ScaleInfo
{
    char pad[0x10];
    float scale;
};
void FUN_006c3780(void* out0, void* out1, const void* pos3, const void* dir3,
                  const void* color, const void* uv, int param);
// ---- items of slice s006cdca0 end

// @ 0x006c1c30
int StateFromGlobal(u32* p)
{
    u32 v = **(u32**)((char*)p + 0x28);
    if (v == 1)
        return 0;
    if (v == 3) {
        u8* q = (u8*)((CtlKey*)p)->KeyOf(0);
        if (q != 0) {
            if (q[8] == 1 && q[9] == 6)
                return 1;
            if (q[8] == 0 && q[9] == 1)
                return 2;
        }
    }
    return 3;
}

// @ 0x006c1c80
u32 MakeStream(u32* out, u32* in)
{
    u32 v = sub_928a30_t(g_16c8b44, 0, in[0], in[1], 0, 0, 0, 0, 0, 0);
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    out[0] = v;
    return (u32)out;
}

// @ 0x006c1cd0
void AnimationBakeDriver(BakeContext* ctx, BakeFrameCtl* ctl, const float* xf)
{
    float inv[256][16];
    float stack[64][16];

    const u32 count = ctl->frameCount;
    BakePair* const pairs = ctx->pairs;
    BakePair* const pairEnd = pairs + count;
    const u32* const flags = *ctx->flagsPtr;
    BakePair* curPair = pairs;

    float cur[16];
    for (int k = 0; k < 16; ++k)
        cur[k] = xf[k];

    bool done = false;

    if (count != 0) {
        // inverse bind-pose matrix for every frame (back to front fills the array)
        for (u32 n = count; n != 0; --n) {
            const u32 fi = n - 1;
            const float* q = (const float*)((BakeFrameAtFn)0x011fda50)(ctl, fi);
            const float x = q[0] * 1.4142135f;
            const float y = q[1] * 1.4142135f;
            const float z = q[2] * 1.4142135f;
            const float w = q[3] * 1.4142135f;
            const float xx = (0.0f - x) * x + 0.5f;
            const float yy = (0.0f - y) * y + 0.5f;
            const float zz = (0.0f - z) * z + 0.5f;
            const float t1 = w * z + y * x;
            const float t2 = y * x - w * z;
            const float s  = yy + xx;
            float* m = inv[fi];
            m[0]  = zz + yy;
            m[1]  = t1;
            m[2]  = x * z - w * y;
            m[3]  = t2;
            m[4]  = t2;
            m[5]  = xx + zz;
            m[6]  = w * x + z * y;
            m[7]  = t1;
            m[8]  = w * y + x * z;
            m[9]  = z * y - w * x;
            m[10] = s;
            m[11] = s;
            m[12] = q[4];
            m[13] = q[5];
            m[14] = q[6];
            m[15] = q[7];
        }
    }

    if (count != 0) {
        float* sp = &stack[0][0];
        for (u32 i = 0; i < count; ++i) {
            if (done)
                return;

            const float* m = inv[i];
            float r[16];
            for (int col = 0; col < 4; ++col) {
                r[0 + col]  = m[1] * cur[4 + col] + m[0] * cur[0 + col] + m[2] * cur[8 + col];
                r[4 + col]  = m[5] * cur[4 + col] + m[4] * cur[0 + col] + m[6] * cur[8 + col];
                r[8 + col]  = m[9] * cur[4 + col] + m[8] * cur[0 + col] + m[10] * cur[8 + col];
                r[12 + col] = (m[13] * cur[4 + col] + m[12] * cur[0 + col] + m[14] * cur[8 + col])
                              + cur[12 + col];
            }

            while (curPair->frame == i) {
                if (curPair->state != 0)
                    ((EmbeddedSetTransformFn)0x011edc10)(curPair->state, r, 3, 1);
                ++curPair;
                if (curPair >= pairEnd) {
                    done = true;
                    break;
                }
            }

            switch (flags[i] & 3) {
            case 0:
                for (int k = 0; k < 16; ++k)
                    cur[k] = r[k];
                break;
            case 1:
                sp -= 16;
                for (int k = 0; k < 16; ++k)
                    cur[k] = sp[k];
                break;
            case 2:
                for (int k = 0; k < 16; ++k)
                    sp[k] = cur[k];
                sp += 16;
                for (int k = 0; k < 16; ++k)
                    cur[k] = r[k];
                break;
            default:
                break;
            }
        }
    }
}

// @ 0x006c2690
void UnpackColor(u32 packed, float* out)
{
    float k = 0.0078740157f;
    out[0] = (float)(packed & 0xff) * k - 1.0f;
    out[1] = (float)((packed >> 8) & 0xff) * k - 1.0f;
    out[2] = (float)((packed >> 16) & 0xff) * k - 1.0f;
}

// @ 0x006c26f0
bool KeyLess(const u32* a, const u32* b)
{
    if (a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]))
        return true;
    if (a[0] == b[0] && a[1] == b[1]) {
        if (a[3] < b[3])
            return true;
        if (a[3] == b[3] && a[2] < b[2])
            return true;
    }
    return false;
}

// @ 0x006c2740
void KeyPack::Assign(const u32* a, const u32* b, const u32* c, const u32* d)
{
    ((u32*)&v[0])[0] = a[0]; ((u32*)&v[0])[1] = a[1];
    ((u32*)&v[0])[2] = a[2]; ((u32*)&v[0])[3] = a[3];
    ((u32*)&v[1])[0] = b[0]; ((u32*)&v[1])[1] = b[1];
    ((u32*)&v[1])[2] = b[2]; ((u32*)&v[1])[3] = b[3];
    ((u32*)&v[2])[0] = c[0]; ((u32*)&v[2])[1] = c[1];
    ((u32*)&v[2])[2] = c[2]; ((u32*)&v[2])[3] = c[3];
    ((u32*)&v[3])[0] = d[0]; ((u32*)&v[3])[1] = d[1];
    ((u32*)&v[3])[2] = d[2]; ((u32*)&v[3])[3] = d[3];
}

// @ 0x006c27b0
u32* InsertionSort6(u32* first, u32* last)
{
    if (first == last)
        return last;
    u32* cur = first + 6;
    if (cur == last)
        return last;
    u32* hole;
    do {
        u32 k0 = cur[0], k1 = cur[1], k2 = cur[2], k3 = cur[3], k4 = cur[4], k5 = cur[5];
        hole = cur;
        while (hole != first) {
            u32* prev = hole - 6;
            if (!LESS6(k0, k1, k2, k3, prev))
                break;
            hole[0] = prev[0]; hole[1] = prev[1]; hole[2] = prev[2];
            hole[3] = prev[3]; hole[4] = prev[4]; hole[5] = prev[5];
            hole = prev;
        }
        hole[0] = k0; hole[1] = k1; hole[2] = k2;
        hole[3] = k3; hole[4] = k4; hole[5] = k5;
        cur += 6;
    } while (cur != last);
    return hole;
}

// @ 0x006c28a0
void InsertionSortOne(u32* first, u32* last)
{
    if (first == last)
        return;
    u32 k0 = first[0], k1 = first[1], k2 = first[2], k3 = first[3], k4 = first[4], k5 = first[5];
    u32* hole = first;
    u32* prev = first - 6;
    while (true) {
        if (!KeyLess(prev, first) && !(first[0] == prev[0] && first[1] == prev[1] &&
            (first[3] > prev[3] || (first[3] == prev[3] && first[2] >= prev[2]))))
            break;
        hole[0] = prev[0]; hole[1] = prev[1]; hole[2] = prev[2];
        hole[3] = prev[3]; hole[4] = prev[4]; hole[5] = prev[5];
        hole = prev;
        prev -= 6;
    }
    hole[0] = k0; hole[1] = k1; hole[2] = k2;
    hole[3] = k3; hole[4] = k4; hole[5] = k5;
}

// @ 0x006c2970
u32* Median3(u32* a, u32* b, u32* c)
{
    bool (*const volatile keyLess)(const u32*, const u32*) = KeyLess;
    if (KEY_LESS(a, b)) {
        if (keyLess(b, c))
            return b;
        if (keyLess(a, c))
            return c;
        return a;
    }
    if (keyLess(a, c))
        return a;
    if (keyLess(b, c))
        return c;
    return b;
}

// @ 0x006c2a00
u32* SiftUp(u32* base, int lower, int pos, u32 k0, u32 k1, u32 k2, u32 k3, u32 k4, u32 k5)
{
    u32 kk[6] = { k0, k1, k2, k3, k4, k5 };
    int i = pos;
    int parent = (i - 1) >> 1;
    while (i > lower) {
        u32* p = base + parent * 6;
        if (!KEY_LESS(p, kk))
            break;
        u32* d = base + i * 6;
        d[0] = p[0]; d[1] = p[1]; d[2] = p[2];
        d[3] = p[3]; d[4] = p[4]; d[5] = p[5];
        i = parent;
        parent = (i - 1) >> 1;
    }
    u32* d = base + i * 6;
    d[0] = kk[0]; d[1] = kk[1]; d[2] = kk[2];
    d[3] = kk[3]; d[4] = kk[4]; d[5] = kk[5];
    return d;
}

// @ 0x006c2ad0
Rec16* Rec16::CopyFrom(const Rec16* src)
{
    a = src->a;
    b = src->b;
    c = src->c;
    d = src->d;
    p = src->p;
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
    return this;
}

// @ 0x006c2b10
Rec16* CopyRange(Rec16* first, Rec16* last, Rec16* out)
{
    if (first == last)
        return out;
    do {
        if (out != 0) {
            out->a = first->a;
            out->b = first->b;
            out->c = first->c;
            out->d = first->d;
            out->p = first->p;
            if (out->p != 0)
                ((void(__thiscall*)(void*))(*(void***)out->p)[0])(out->p);
        }
        ++first;
        ++out;
    } while (first != last);
    return out;
}

// @ 0x006c2bc0
u32* SiftDown(u32* base, int lower, int count, int pos, u32 k0, u32 k1, u32 k2, u32 k3, u32 k4, u32 k5)
{
    int child = pos * 2 + 2;
    while (child < count) {
        u32* c = base + child * 6;
        u32* p = base + (child - 1) * 6;
        if (KEY_LESS(c, p))
            --child;
        u32* s = base + child * 6;
        u32* d = base + pos * 6;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4]; d[5] = s[5];
        pos = child;
        child = pos * 2 + 2;
    }
    if (child == count) {
        u32* s = base + (child - 1) * 6;
        u32* d = base + pos * 6;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4]; d[5] = s[5];
        pos = child - 1;
    }
    return SiftUp(base, lower, pos, k0, k1, k2, k3, k4, k5);
}

// @ 0x006c2cd0
float* ScaleMatrixReversed(float* out, const float* m, float s)
{
  float t[16];
  t[0]  = m[0xc] * s; t[1]  = m[0xd] * s; t[2]  = m[0xe] * s; t[3]  = m[0xf] * s;
  t[4]  = m[0x8] * s; t[5]  = m[0x9] * s; t[6]  = m[0xa] * s; t[7]  = m[0xb] * s;
  t[8]  = m[0x4] * s; t[9]  = m[0x5] * s; t[10] = m[0x6] * s; t[11] = m[0x7] * s;
  t[12] = m[0x0] * s; t[13] = m[0x1] * s; t[14] = m[0x2] * s; t[15] = m[0x3] * s;
  // The temporary is filled bottom-up, so the rows go back to SetRows in reverse:
  // out row 0 is the last-computed block (m[0..3]*s).
  ((Mat4*)out)->SetRows(t + 12, t + 8, t + 4, t);
  return out;
}

// @ 0x006c2e00
void PopHeap(Rec24* first, Rec24* last)
{
  Rec24 value = last[-1];
  last[-1] = first[0];
  AdjustHeap(first, 0, (int)(last - first) - 1, 0, value);
}

// @ 0x006c2ea0
float* FUN_006c2ea0(float* out, const float* axis, const float* n, const float* scale, const void* obj)
{
  float n0 = n[0], n1 = n[1], n2 = n[2];
  float a0 = fabsf(n0), a1 = fabsf(n1), a2 = fabsf(n2);
  float g0 = (a2 < a0) ? 0.0f : 1.0f;
  float g1 = (a1 < a2) ? 0.0f : 1.0f;
  float g2 = (a0 < a1) ? 0.0f : 1.0f;
  float g3 = (a2 < a1) ? 0.0f : 1.0f;
  float g4 = (a1 < a0) ? 0.0f : 1.0f;
  float g5 = (a0 < a2) ? 0.0f : 1.0f;
  float sign2 = SignF(n2);
  float sign1 = SignF(n1);
  float sign0 = SignF(n0);

  float t = -(g4 * g1 * sign1);
  float u = sign0 * (g5 * g2);

  // The original is SSE-scalar: every add/mul rounds to float32. cl15 emits
  // x87, whose 24-bit precision double-rounds denormal results, so the
  // multiplies that can produce a denormal go through MulSS (single rounding).
  volatile float r0 = axis[1] * u;
  r0 = r0 + axis[0] * (g3 * g0);
  r0 = r0 + axis[0] * t;
  volatile float p0 = MulSS(r0, scale[0]);

  volatile float r1 = axis[2] * (sign0 * u);
  r1 = r1 + axis[1] * ((g3 * g0) * sign2);
  r1 = r1 + axis[2] * (-sign1 * t);
  volatile float p1 = -MulSS(r1, scale[1]);

  float k = *(const float*)((const char*)obj + 0x10);
  out[0] = MulSS(p0, k);
  out[1] = MulSS(p1, k);
  return out;
}

// @ 0x006c3080
bool FUN_006c3080(float* out, int count, int res, int* data, const Range* vtx, const float* scale, const void* obj)
{
  int idx = FUN_0071ddc0(res, 2, 0, 3, 0xe);
  if (idx >= 0) {
    char* e = (char*)(*(int*)(res + 8) + idx * 0x20);
    RefCounted* rc = *(RefCounted**)(e + 0x1c);
    char* blockBase = (char*)*(int*)(e + 0x14);
    uint16_t blockStride = *(uint16_t*)(e + 0x1a);
    if (rc) rc->AddRef();
    for (int i = 0; i < count; ++i) {
      const float* col = (const float*)(blockBase + blockStride * data[1]);
      float n[3] = { col[0], col[1], col[2] };
      const float* p = (const float*)(vtx->base + (int)vtx->stride * data[0]);
      float ax[3] = { p[0], p[1], p[2] };
      float tmp[2];
      FUN_006c2ea0(tmp, ax, n, scale, obj);
      out[0] = tmp[0];
      out[1] = tmp[1];
      data += 6;
      out += 2;
    }
    if (rc) rc->Release();
    return true;
  }
  idx = FUN_0071ddc0(res, 2, 0, 7, 0xe);
  if (idx < 0) return false;
  char* e = (char*)(*(int*)(res + 8) + idx * 0x20);
  RefCounted* rc = *(RefCounted**)(e + 0x1c);
  char* blockBase = (char*)*(int*)(e + 0x14);
  uint16_t blockStride = *(uint16_t*)(e + 0x1a);
  if (rc) rc->AddRef();
  for (int i = 0; i < count; ++i) {
    const float* p = (const float*)(vtx->base + (int)vtx->stride * data[0]);
    float ax[3] = { p[0], p[1], p[2] };
    unsigned packed = *(unsigned*)(blockBase + blockStride * data[1]);
    float n[3];
    n[0] = (float)(packed & 0xff) * (1.0f / 127.0f) - 1.0f;
    n[1] = (float)((packed >> 8) & 0xff) * (1.0f / 127.0f) - 1.0f;
    n[2] = (float)((packed >> 16) & 0xff) * (1.0f / 127.0f) - 1.0f;
    float tmp[2];
    FUN_006c2ea0(tmp, ax, n, scale, obj);
    out[0] = tmp[0];
    out[1] = tmp[1];
    data += 6;
    out += 2;
  }
  if (rc) rc->Release();
  return true;
}

// @ 0x006c32f0
Descriptor* Container::MakeDescriptor(Descriptor* out)
{
  char* begin = this->begin;
  char* end = this->end;
  out->count = (int)(end - begin) >> 3;
  out->first = begin;
  out->a = 8;
  out->b = 8;
  out->owner = this;
  slot0(out, 0);
  return out;
}

// @ 0x006c3330
RBNode** RBTree::insert(RBNode** out, RBNode* hint, const int* key, bool flag)
{
  int side = (!flag && (char*)hint != (char*)this + 4 && !(key[0] < hint->key0)) ? 1 : 0;
  RBNode* node = (RBNode*)EASTL_alloc(0x18, "Graphics", 0, 0,
                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                      "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                      "EASTL/allocator.h",
                                      0xd1);
  if ((char*)node + 0x10 != 0) {
    node->key0 = key[0];
    node->key1 = key[1];
  }
  RBTreeInsert(node, hint, (RBNode*)((char*)this + 4), side);
  ++count;
  *out = node;
  return out;
}

// @ 0x006c33b0
void MakeHeap(Rec24* first, Rec24* last)
{
  int len = (int)(last - first);
  if (len >= 2) {
    int i = ((len - 2) >> 1) + 1;
    do {
      --i;
      AdjustHeap(first, i, len, i, first[i]);
    } while (i != 0);
  }
}

// @ 0x006c3430
void SortHeap(Rec24* first, Rec24* last)
{
  while (last - first > 1) {
    PopHeap(first, last);
    --last;
  }
}

// @ 0x006c3510
BakedArenaThing::BakedArenaThing()
: m_ref(0), m_c(0), m_10(0), m_14(0), m_20(0) {}

// @ 0x006c3550
float* FUN_006c3550(float* outA, float* outB, const float* base, const float* dir, const float* s, const int* idx, int layout)
{
  char* p = (char*)(*(int*)(layout + 4) + (uint16_t)*(uint16_t*)(layout + 0xa) * idx[0]);
  float fourth[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  Mat4 m;
  m.SetRows((const float*)p, (const float*)(p + 0x10), (const float*)(p + 0x20), fourth);
  float sm[16];
  ScaleMatrixReversed(sm, m.m, s[0]);

  // The original is SSE-scalar and groups the products as shown (the direction
  // rows start with the z term, the point rows with the y/z terms); the fourth
  // column is multiplied by the literal 0.0f, which only matters for the sign
  // of an exact zero result. Reproduce that order exactly.
  float d0 = dir[0], d1 = dir[1], d2 = dir[2];
  float b0 = base[0], b1 = base[1], b2 = base[2];
  volatile float vzero = 0.0f;
  float z = vzero;

  outB[0] = AddSS(AddSS(AddSS(MulSS(sm[0], d0), MulSS(sm[8], d2)), MulSS(sm[4], d1)),
                  MulSS(sm[12], z));
  outB[1] = AddSS(AddSS(AddSS(MulSS(sm[9], d2), MulSS(sm[5], d1)), MulSS(sm[1], d0)),
                  MulSS(sm[13], z));
  outB[2] = AddSS(AddSS(AddSS(MulSS(sm[10], d2), MulSS(sm[6], d1)), MulSS(sm[2], d0)),
                  MulSS(sm[14], z));

  outA[0] = AddSS(AddSS(AddSS(MulSS(sm[8], b2), MulSS(sm[0], b0)), MulSS(sm[4], b1)), sm[12]);
  outA[1] = AddSS(AddSS(AddSS(MulSS(sm[5], b1), MulSS(sm[9], b2)), MulSS(sm[1], b0)), sm[13]);
  outA[2] = AddSS(AddSS(AddSS(MulSS(sm[6], b1), MulSS(sm[10], b2)), MulSS(sm[2], b0)), sm[14]);
  return outA;
}

// @ 0x006c3780
float* FUN_006c3780(float* outA, float* outB, const float* base, const float* dir, const float* s, const int* idx, int layout)
{
  uint16_t stride = *(uint16_t*)(layout + 0xa);
  char* seg = (char*)*(int*)(layout + 4);
  char* p = seg + stride * idx[0];
  float fourth[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  Mat4 m;
  m.SetRows((const float*)p, (const float*)(p + 0x10), (const float*)(p + 0x20), fourth);
  float sm[16];
  ScaleMatrixReversed(sm, m.m, s[0]);

  const float* off = (const float*)(seg + stride * idx[1]);
  float k = s[1];
  volatile float vzero = 0.0f;
  float z = vzero;
  // A zero-width lane of the offset block is folded into the translation column
  // (s[1] * 0.0f): it can flip an exact -0.0 translation to +0.0.
  float t12 = AddSS(sm[12], MulSS(k, z));
  float t13 = AddSS(sm[13], MulSS(k, z));
  float t14 = AddSS(sm[14], MulSS(k, z));

  float o0 = AddSS(sm[0], MulSS(off[0], k));
  float o1 = AddSS(sm[1], MulSS(off[1], k));
  float o2 = AddSS(sm[2], MulSS(off[2], k));
  float o4 = AddSS(sm[4], MulSS(off[4], k));
  float o5 = AddSS(sm[5], MulSS(off[5], k));
  float o6 = AddSS(sm[6], MulSS(off[6], k));
  float o8 = AddSS(sm[8], MulSS(off[8], k));
  float o9 = AddSS(sm[9], MulSS(off[9], k));
  float o10 = AddSS(sm[10], MulSS(off[10], k));

  float d0 = dir[0], d1 = dir[1], d2 = dir[2];
  float b0 = base[0], b1 = base[1], b2 = base[2];

  outB[0] = AddSS(AddSS(AddSS(MulSS(o0, d0), MulSS(o8, d2)), MulSS(o4, d1)), MulSS(t12, z));
  outB[1] = AddSS(AddSS(AddSS(MulSS(o5, d1), MulSS(o9, d2)), MulSS(o1, d0)), MulSS(t13, z));
  outB[2] = AddSS(AddSS(AddSS(MulSS(o6, d1), MulSS(o10, d2)), MulSS(o2, d0)), MulSS(t14, z));

  outA[0] = AddSS(AddSS(AddSS(MulSS(o8, b2), MulSS(o0, b0)), MulSS(o4, b1)), t12);
  outA[1] = AddSS(AddSS(AddSS(MulSS(o5, b1), MulSS(o9, b2)), MulSS(o1, b0)), t13);
  outA[2] = AddSS(AddSS(AddSS(MulSS(o6, b1), MulSS(o10, b2)), MulSS(o2, b0)), t14);
  return outA;
}

// @ 0x006c3b90
float* FUN_006c3b90(float* outA, float* outB, const float* base, const float* dir, const float* s, const int* idx, int layout)
{
  BakeWeighted(outA, outB, base, dir, s, idx, layout, 2);
  return outA;
}

// @ 0x006c4200
float* FUN_006c4200(float* outA, float* outB, const float* base, const float* dir, const float* s, const int* idx, int layout)
{
  BakeWeighted(outA, outB, base, dir, s, idx, layout, 3);
  return outA;
}

// @ 0x006c4870
Rec24_s006c_3b90* GetPartition(Rec24_s006c_3b90* first, Rec24_s006c_3b90* last, Rec24_s006c_3b90 pivot)
{
  for (;; ++first) {
    while (*first < pivot) ++first;
    --last;
    while (pivot < *last) --last;
    if (first >= last) return first;
    Rec24_s006c_3b90 tmp = *first;
    *first = *last;
    *last = tmp;
  }
}

// @ 0x006c4960
void PartialSort(Rec24_s006c_3b90* first, Rec24_s006c_3b90* middle, Rec24_s006c_3b90* last)
{
  MakeHeap(first, middle);
  for (Rec24_s006c_3b90* i = middle; i < last; ++i) {
    if (*i < *first) {
      Rec24_s006c_3b90 value = *i;
      *i = *first;
      AdjustHeap(first, 0, (int)(middle - first), 0, value);
    }
  }
  SortHeap(first, middle);
}

// @ 0x006c4a70
void QuickSortImpl(Rec24_s006c_4a70* first, Rec24_s006c_4a70* last, int depth)
{
  int n = (int)(last - first);
  while (n > 0x1c && depth > 0) {
    Rec24_s006c_4a70 pivot = *Median(first, first + (last - first) / 2, last - 1);
    Rec24_s006c_4a70* mid = GetPartition(first, last, pivot);
    --depth;
    QuickSortImpl(mid, last, depth);
    n = (int)(mid - first);
    last = mid;
  }
  if (depth == 0)
    PartialSort(first, last, last);
}

// @ 0x006c4c20
void QuickSort(Rec24_s006c_4a70* first, Rec24_s006c_4a70* last)
{
  if (first != last) {
    int n = (int)(last - first);
    QuickSortImpl(first, last, 2 * Log2(n));
    if (n > 0x1c) {
      InsertionSortA(first, first + 0x1c);
      InsertionSortB(first + 0x1c, last);
    } else {
      InsertionSortA(first, last);
    }
  }
}

// @ 0x006ce860
bool Bake_6ce860(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos, float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    Elem32* base = table->mBegin;
    Handle hA = base[index].handle;
    Handle hB;
    if (handleIndex >= 0)
        hB.Assign(&base[handleIndex].handle);
    if (count != 0)
    {
        float axisDir[3] = { 1.0f, 0.0f, 0.0f };
        float* o = out;
        BakeEntry* e = entries;
        int n = count;
        do
        {
            uint32_t u[4];
            uint8_t* s = (uint8_t*)(hA.b + hA.d * e->fc);
            u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = s[2] / 3; u[3] = s[3] / 3;
            float color[4];
            float* c = (float*)(hB.b + hB.d * e->f8);
            color[0] = c[0]; color[1] = c[1]; color[2] = 0.0f; color[3] = 0.0f;
            float* ps = (float*)(pos->base + pos->stride * e->f0);
            float p3[3];
            p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
            float res[3];
            float scratch[3];
            FUN_006c3780(res, scratch, p3, axisDir, color, u, param10);
            float scale = scaleInfo->scale;
            o[0] = BakeMulSS(BakeAddSS(BakeMulSS(axis[0], res[0]), axis[2]), scale);
            o[1] = BakeMulSS(BakeSubSS(1.0f, BakeAddSS(BakeMulSS(res[1], axis[1]), axis[3])), scale);
            o += 2;
            e += 1;
        } while (--n);
    }
    return true;
}
