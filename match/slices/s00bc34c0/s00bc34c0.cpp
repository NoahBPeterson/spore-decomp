// Slice s00bc34c0: a camera-follow / collision-snap object (ctor + per-frame update),
// a perpendicular-offset helper, an intrusive-list lookup trio and EASTL range helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <string.h>

extern "C" void __cdecl operator_delete__(void*);
void* __cdecl operator_new(unsigned size, const char* name, int flags, int a, const char* file, int line);

static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char* const kSimulator = "Simulator";

static inline void freeBuf(void* p) { if (p && ((int*)p)[-1] != 0) operator_delete__(p); }

struct V3 {
    float x, y, z;
    V3() {}
    V3(float a, float b, float c) : x(a), y(b), z(c) {}
    V3(const V3& o) {
        ((uint32_t*)this)[0] = ((const uint32_t*)&o)[0];
        ((uint32_t*)this)[1] = ((const uint32_t*)&o)[1];
        ((uint32_t*)this)[2] = ((const uint32_t*)&o)[2];
    }
    V3& operator=(const V3& o) {
        ((uint32_t*)this)[0] = ((const uint32_t*)&o)[0];
        ((uint32_t*)this)[1] = ((const uint32_t*)&o)[1];
        ((uint32_t*)this)[2] = ((const uint32_t*)&o)[2];
        return *this;
    }
};
struct Q4 { float x, y, z, w; Q4() {} Q4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };

// ---- external globals / callees -------------------------------------------------
extern float g156d200, g156d204, g156d208;             // initial value of sub-object at +0x3c
extern float g156d20c, g156d210, g156d214, g156d218;   // initial value of sub-object at +0x90
extern float g156d1fc;                                 // follow-rate scale
extern float g145cfe8;                                 // block of 4 floats (0x3e860a92)
extern V3 g168aab4;
extern void* vt014667f0[];
extern void* vt1145cf78[];
extern void* vt2014667ec[];

struct B0 { void __thiscall init(void* a); };           // FUN_00b12890 (base ctor)
struct F3 { float x, y, z; F3(float a, float b, float c) : x(a), y(b), z(c) {} F3(const F3& o) : x(o.x), y(o.y), z(o.z) {} };
struct F4 { float x, y, z, w; F4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} F4(const F4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {} };
extern F3 g156d200v;                                   // 0x0156d200
extern F4 g156d20cv;                                   // 0x0156d20c
struct SubA { uint32_t pad[0x15]; void __thiscall set(F3 v); };          // FUN_00f4f5a0
struct SubB { uint32_t pad[0x1b]; void __thiscall set(F4 q); };          // FUN_00f4fe50

struct FixedVec8 {                                        // fixed_vector<AutoRefCount<cSpatialObject>, 8>
    void** mpBegin; void** mpEnd; void** mpCap;
    uint32_t a, b, overflow;
    void* buf[8];
    void __thiscall dtor();                               // 0x00ad92d0
};

struct Cam {                                              // App()->vf50()->vf1c()
    virtual void v0();
    void __thiscall f7c4d00(void* hdr);
    void __thiscall f7c4ba0(float a);
    void __thiscall f7c4bc0(float a);
};
struct Mgr { virtual void v0(); };
struct App1 { virtual void v0(); };
App1* __cdecl App();                                       // SP::App

struct PosHelper : V3 {                                   // 0xb16dc0 / 0xb17790
    PosHelper(Cam* c);
    void __thiscall f17790(int a);
};

bool __cdecl f00b17c10(PosHelper* pos, FixedVec8* v);
bool __cdecl f00b17810(PosHelper* pos, Q4* q);
bool __cdecl f00b182f0(PosHelper* pos, int flags);          // cGameData::PathOrSerializationCheck
void __cdecl f00b16450(PosHelper* pos, FixedVec8* v);
void __cdecl f00b16e50(PosHelper* pos, Q4* q);

struct Hdr { uint16_t flags; uint16_t count; float v[3]; };

struct C {
    void* vt0; void* vt1; void* vt2;
    uint32_t pad0c[3];
    uint8_t b18, b19; uint16_t pad1a;
    float f1c, f20, f24, f28, f2c, f30, f34, f38;
    SubA s3c;
    SubB s90;
    uint8_t bfc, bfd; uint16_t padfe;
    float f100, f104, f108, f10c, f110, f114, f118, f11c;
    uint8_t b120, b121; uint16_t pad122;
    float f124, f128, f12c, f130, f134, f138, f13c, f140;
    uint32_t pad144[(0x2cc - 0x144) / 4];
    Hdr h2cc;
    uint32_t pad2dc[(0x310 - 0x2dc) / 4];
    float f310, f314;
    uint32_t pad318[(0x394 - 0x318) / 4];
    float f394;
    uint8_t b398; uint8_t pad399[3];
    V3 v39c;
    V3 v3a8;
    uint32_t d3b4;

    C* __thiscall ctor(void* arg);
    void __thiscall update(float dt);
};

// @ 0x00bc34c0
C* __thiscall C::ctor(void* arg)
{
    ((B0*)this)->init(arg);
    vt0 = vt014667f0;
    vt1 = vt1145cf78;
    vt2 = vt2014667ec;
    d3b4 = 0;
    b18 = 0;
    b19 = 0;
    f20 = 0.0f;
    f1c = 0.0f;
    f30 = 0.0f;
    f2c = 0.0f;
    f28 = 0.0f;
    f24 = 0.0f;
    f34 = 0.0f;
    f38 = 0.0f;
    s3c.set(g156d200v);
    s90.set(g156d20cv);
    f114 = 1.0f;
    f110 = 1.0f;
    f10c = 1.0f;
    f108 = 1.0f;
    bfc = 0;
    bfd = 0;
    f104 = 0.0f;
    f100 = 0.0f;
    f118 = 0.0f;
    f11c = 0.0f;
    b120 = 0;
    b121 = 0;
    f128 = 0.0f;
    f124 = 0.0f;
    f138 = g145cfe8;
    f134 = g145cfe8;
    f130 = g145cfe8;
    f12c = g145cfe8;
    f13c = 0.0f;
    f140 = 0.0f;
    f394 = 0.0f;
    b398 = 0;
    v39c = g168aab4;
    v3a8 = g168aab4;
    return this;
}

// @ 0x00bc3700
void __thiscall C::update(float dt)
{
    App1* app = App();
    Mgr* mgr = (Mgr*)(*(void* (__thiscall**)(App1*))(*(char**)app + 0x50))(app);
    Cam* cam = (Cam*)(*(void* (__thiscall**)(Mgr*))(*(char**)mgr + 0x1c))(mgr);
    cam->f7c4d00(&h2cc);
    cam->f7c4ba0(f310);
    cam->f7c4bc0(f314);
    PosHelper pos(cam);
    bool wasSnapped = b398 != 0;
    Q4 w;
    w.x = pos.x; w.y = pos.y; w.z = pos.z;
    f394 = dt;
    b398 = 0;
    if (f00b17c10(&pos, 0)) b398 = 1;
    if (b398 == 0) {
        if (f00b17810(&pos, 0)) b398 = 1;
        if (b398 == 0 && f00b182f0(&pos, 0x18)) b398 = 1;
    }
    float lenW = sqrtf(w.x * w.x + w.z * w.z + w.y * w.y);
    float lenCur = sqrtf(v39c.x * v39c.x + v39c.y * v39c.y + v39c.z * v39c.z);
    // NOTE: the original epilogue also frees an uninitialised stack slot ([esp+0x78]); omitted (UB).
    if (b398 == 0) {
        v3a8 = V3(w.x, w.y, w.z);
        float d = lenCur - lenW;
        if (d > 1.5258789e-05f) {
            float zero = 0.0f;
            float dd = d;
            const float* p = (d > 0.0f) ? &dd : &zero;
            float tgt = lenCur - ((*p * 0.4f + 1.0f) * g156d1fc) * f394;
            float inv = 1.0f / sqrtf(w.x * w.x + w.y * w.y + w.z * w.z + 1e-8f);
            w.x *= inv; w.y *= inv; w.z *= inv;
            const float* q = (tgt > lenW) ? &tgt : &lenW;
            float s = *q;
            v39c.x = w.x * s; v39c.y = w.y * s; v39c.z = w.z * s;
            if (wasSnapped) b398 = 1;
        }
    } else {
        if (wasSnapped) {
            float inv = 1.0f / sqrtf(w.x * w.x + w.y * w.y + w.z * w.z + 1e-8f);
            w.x *= inv; w.y *= inv; w.z *= inv;
            const float* q = (lenCur > lenW) ? &lenCur : &lenW;
            float s = *q;
            pos.x = w.x * s; pos.y = w.y * s; pos.z = w.z * s;
            pos.f17790(1);
        }
        FixedVec8 vec;
        vec.mpBegin = vec.mpEnd = vec.buf;
        vec.mpCap = vec.buf + 8;
        vec.overflow = 0;
        bool c1 = f00b17c10(&pos, &vec);
        if (c1) {
            f00b16450(&pos, &vec);
            pos.f17790(1);
        }
        w.w = 0.0f;
        bool c2 = f00b17810(&pos, &w);
        if (c2) f00b16e50(&pos, &w);
        bool c3 = f00b182f0(&pos, 0x18);
        if (!c1 && !c2 && !c3) {
            v3a8 = pos;
        } else {
            float d = lenCur - lenW;
            float zero = 0.0f;
            float dd = d;
            const float* p = (d > 0.0f) ? &dd : &zero;
            float f = ((*p * 0.4f + 1.0f) * g156d1fc) * f394;
            float inv = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
            pos.x = pos.x * inv * f + pos.x;
            pos.y = pos.y * inv * f + pos.y;
            pos.z = pos.z * inv * f + pos.z;
        }
        v39c = pos;
        vec.dtor();
    }
    if (b398) {
        h2cc.v[0] = v39c.x;
        h2cc.v[1] = v39c.y;
        h2cc.flags |= 4;
        h2cc.count++;
        h2cc.v[2] = v39c.z;
    }
}

// ---------------------------------------------------------------------------------
struct PM { void __thiscall f00b82970(); };
void* __stdcall PlanetModel(void* a, V3* b, int c);          // SP::PlanetModel (0x00b3d350)

struct Frame {
    uint32_t pad0[1];
    V3 a;                 // +4
    V3 b;                 // +0x10
    uint32_t pad1c[(0x7bd - 0x1c) / 4 + 1];
};

// @ 0x00bc3c20  (stdcall; returns param_1)
void* __stdcall FUN_00bc3c20(void* out, char* obj, const float* v2, float f)
{
    float ax = *(float*)(obj + 4), ay = *(float*)(obj + 8), az = *(float*)(obj + 0xc);
    float bx = *(float*)(obj + 0x10), by = *(float*)(obj + 0x14), bz = *(float*)(obj + 0x18);
    float ia = 1.0f / sqrtf(az * az + (ax * ax + ay * ay) + 1e-8f);
    float ib = 1.0f / sqrtf((bx * bx + by * by) + bz * bz + 1e-8f);
    bx *= ib; by *= ib; bz *= ib;
    if (*(char*)(obj + 0x7bd)) f = 1.0f;
    float s = v2[0] * f;
    float t = v2[1] * f;
    V3 r;
    r.x = (by * (ia * az) - bz * (ay * ia)) * s + ax + bx * t;
    r.y = (bz * (ia * ax) - (ia * az) * bx) * s + ay + by * t;
    r.z = (bx * (ay * ia) - by * (ia * ax)) * s + az + bz * t;
    void* pm = PlanetModel(out, &r, 0);
    ((PM*)pm)->f00b82970();
    return out;
}

// ---- intrusive list at this+0x1c: node.next @0, node.key @8, node fields @0x7dd/0x7e4 ----
struct LNode {
    LNode* next; uint32_t pad4; int key;
    char pad[0x7d8 - 0xc];
    uint32_t f7d8;
    uint8_t pad7dc; uint8_t b7dd; uint8_t pad7de[6];
    uint32_t f7e4;
};
struct Reg {
    char pad[0x1c];
    LNode* head;          // list sentinel pointer (list anchor at +0x1c)
    LNode* lastPad;
    uint32_t __thiscall findValue(int key);
    uint8_t __thiscall isDisabled(int key);
    void __thiscall setFlag(int key, uint32_t v);
};
#define LIST_END(self) ((LNode*)((char*)(self) + 0x1c))

// @ 0x00bc3db0
uint32_t __thiscall Reg::findValue(int key)
{
    LNode* n = head;
    while (n != LIST_END(this)) {
        if (n->key == key) {
            if (n->b7dd != 0) return 0;
            return n->f7e4;
        }
        n = n->next;
    }
    return 0;
}

// @ 0x00bc3df0
uint8_t __thiscall Reg::isDisabled(int key)
{
    LNode* n = head;
    while (n != LIST_END(this)) {
        if (n->key == key) return n->b7dd;
        n = n->next;
    }
    return 1;
}

// @ 0x00bc3e20
// The original dereferences a null "end" object when the key is missing (writes to 0x7d0).
void __thiscall Reg::setFlag(int key, uint32_t v)
{
    LNode* n = head;
    while (n != LIST_END(this)) {
        if (n->key == key) { n->f7d8 = v; return; }
        n = n->next;
    }
    *(uint32_t*)0x7d0 = v;
}

// ---- 0x98-byte fixed_vector elements -------------------------------------------------
struct Elem98 {
    void* mpBegin; void* mpEnd; void* mpCap; uint32_t a, b, overflow;
    void* buf[32];
    void __thiscall assign(const Elem98* src);              // FUN_00bc3f50
};

// @ 0x00bc3ec0
Elem98* __cdecl FUN_00bc3ec0(Elem98* first, Elem98* last, Elem98* dst)
{
    while (first != last) {
        freeBuf(first->mpBegin);
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00bc3f10
void __stdcall FUN_00bc3f10(Elem98* first, Elem98* last)
{
    for (; first < last; ++first) freeBuf(first->mpBegin);
}

// @ 0x00bc4030
uint32_t* __cdecl FUN_00bc4030(const uint32_t* first, const uint32_t* last, uint32_t* dst)
{
    for (; first != last; ++first) { *dst = *first; ++dst; }
    return dst;
}

// ---- vector<12-byte> range insert ---------------------------------------------------
struct A12 { int a, b, c; };
void __cdecl FUN_00512050(A12** out, A12* first, A12* last, A12* dst, int tag);
A12* __cdecl FUN_00a11310(A12* first, A12* last, A12* dst);
A12* __cdecl copy_backward12(A12* first, A12* last, A12* destEnd);   // 0x00abced0
A12* __cdecl copy12(const A12* first, const A12* last, A12* dst);    // 0x00b84c80

struct VecA12 {
    A12* mpBegin; A12* mpEnd; A12* mpCap;
    void __thiscall insert(A12* pos, const A12* first, const A12* last, int tag);
};

// @ 0x00bc40a0
void __thiscall VecA12::insert(A12* pos, const A12* first, const A12* last, int tag)
{
    if (first == last) return;
    unsigned n = last - first;
    A12* out;
    if (n <= (unsigned)(mpCap - mpEnd)) {
        A12* end = mpEnd;
        unsigned tail = end - pos;
        if (n < tail) {
            A12* mid = end - n;
            FUN_00512050(&out, mid, end, end, tag);
            mpEnd += n;
            copy_backward12(pos, mid, end);
            copy12(first, last, pos);
            return;
        }
        const A12* split = first + tail;
        FUN_00512050(&out, (A12*)split, (A12*)last, end, tag);
        mpEnd += n - tail;
        FUN_00512050(&out, pos, end, mpEnd, tag);
        mpEnd += tail;
        copy_backward12((A12*)first, (A12*)split, pos + tail);
        return;
    }
    unsigned sz = mpEnd - mpBegin;
    unsigned cap = sz * 2;
    if (sz == 0) cap = 1;
    if (cap <= n + sz) cap = n + sz;
    A12* nb = cap ? (A12*)operator_new(cap * 12, kSimulator, 0, 0, kAllocFile, 0xd1) : 0;
    A12* p = FUN_00a11310(mpBegin, pos, nb);
    FUN_00512050(&out, (A12*)first, (A12*)last, p, tag);
    A12* ne = FUN_00a11310(pos, mpEnd, out);
    freeBuf(mpBegin);
    mpBegin = nb;
    mpEnd = ne;
    mpCap = nb + cap;
}

// @ 0x00bc4280  (placement-constructs n fixed_vectors as copies of *src)
void __cdecl FUN_00bc4280(Elem98* arr, unsigned n, const Elem98* src)
{
    if (n > 0) do {
        if (arr) {
            arr->overflow = 0;
            arr->mpBegin = arr->buf;
            arr->mpEnd = arr->buf;
            arr->mpCap = arr->buf + 32;
            arr->assign(src);
        }
        --n;
        ++arr;
    } while (n > 0);
}

// @ 0x00bc4310
Elem98* __cdecl FUN_00bc4310(const Elem98* first, const Elem98* last, Elem98* dst)
{
    while (first != last) {
        if (dst) {
            dst->overflow = 0;
            dst->mpBegin = dst->buf;
            dst->mpEnd = dst->buf;
            dst->mpCap = dst->buf + 32;
            dst->assign(first);
        }
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00bc4370
Elem98** __cdecl FUN_00bc4370(Elem98** out, const Elem98* first, const Elem98* last, Elem98* dst)
{
    *out = dst;
    for (; first != last; ++first) {
        Elem98* e = *out;
        if (e) {
            e->mpBegin = e->buf;
            e->mpEnd = e->buf;
            e->overflow = 0;
            e->mpCap = e->buf + 32;
            e->assign(first);
        }
        *out = *out + 1;
    }
    return out;
}

// ---- vector<4-byte> range insert -----------------------------------------------------
void* __cdecl FUN_00bc4_move(void* dst, const void* src, unsigned bytes);   // 0x011e0744 (memmove-like, returns dst)
uint32_t* __cdecl FUN_00c16090(const uint32_t* first, const uint32_t* last, uint32_t* destEnd);

struct VecU32 {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap;
    void __thiscall insert(uint32_t* pos, const uint32_t* first, const uint32_t* last, int tag);
};

// @ 0x00bc43d0
void __thiscall VecU32::insert(uint32_t* pos, const uint32_t* first, const uint32_t* last, int tag)
{
    if (first == last) return;
    unsigned n = last - first;
    if (n <= (unsigned)(mpCap - mpEnd)) {
        uint32_t* end = mpEnd;
        unsigned tail = end - pos;
        if (n < tail) {
            uint32_t* mid = end - n;
            FUN_00bc4_move(end, mid, (char*)end - (char*)mid);
            mpEnd += n;
            memmove(end - (mid - pos), pos, (char*)mid - (char*)pos);
            FUN_00bc4030(first, last, pos);
            return;
        }
        FUN_00bc4030(first + tail, last, end);
        mpEnd += n - tail;
        FUN_00bc4_move(mpEnd, pos, tail * 4);
        mpEnd += tail;
        FUN_00c16090(first, first + tail, pos + tail);
        return;
    }
    unsigned sz = mpEnd - mpBegin;
    unsigned cap = sz * 2;
    if (sz == 0) cap = 1;
    if (cap <= n + sz) cap = n + sz;
    uint32_t* nb = cap ? (uint32_t*)operator_new(cap * 4, kSimulator, 0, 0, kAllocFile, 0xd1) : 0;
    unsigned head = (char*)pos - (char*)mpBegin;
    uint32_t* p = (uint32_t*)FUN_00bc4_move(nb, mpBegin, head);
    uint32_t* d = p + (head >> 2);
    do { *d = *first; ++first; ++d; } while (first != last);
    unsigned rest = (char*)mpEnd - (char*)pos;
    uint32_t* q = (uint32_t*)FUN_00bc4_move(d, pos, rest);
    uint32_t* ne = q + (rest >> 2);
    freeBuf(mpBegin);
    mpEnd = ne;
    mpBegin = nb;
    mpCap = nb + cap;
}

// ---- container-header initialiser ----------------------------------------------------
template <int N> struct FV {
    void** mpBegin; void** mpEnd; void** mpCap; uint32_t a, b, ovf; void* buf[N];
    FV() { ovf = 0; void** p = buf; mpBegin = p; mpEnd = p; mpCap = p + N; }
};
struct FStr32 {
    char* mpBegin; char* mpEnd; char* mpCap; uint32_t a; char* mpBuf; char buf[32];
    FStr32() { char* p = buf; mpBuf = buf; mpCap = p + 32; mpEnd = p; mpBegin = p; buf[0] = 0; }
};
struct Big {
    uint32_t pad0[2];
    FV<8> v0; FV<64> v1; FV<32> v2; FV<8> v3; FV<6> v4; FV<4> v5; FV<304> v6;
    FStr32 s;
    Big();
};

// @ 0x00bc4630
Big::Big() {}
typedef char chk_s_off[(sizeof(Big) >= 0x78c) ? 1 : -1];
