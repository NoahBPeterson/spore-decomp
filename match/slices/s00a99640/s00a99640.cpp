// Slice s00a99640: constructor of a Swarm-style effect parameter block (retail size ~0x2c0, vtable 0x01458aec)
// @ 0x00a99b20 (Claude-coined name: cEffectParams::cEffectParams).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc), same as the Swarm region 0xa77c80-0xa7c5xx.
//
// Sets ~170 members to their defaults (0, +-1, 2.0, 5.0, +-10000, -1e9, 0.25, ... and the three words of
// two global Vec3 constants), then seeds six one-element curve vectors (SimpleVector<float>, 0x14 bytes in retail)
// and one Vec3 vector.
#include "types.h"
inline void* operator new(size_t, void* p) { return p; }

struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(const Vec3f& o) { x = o.x; y = o.y; z = o.z; }
};
extern Vec3f g_vec3_01678e1c;     // 0x01678e1c (runtime-initialised constant, copied per word)
extern Vec3f g_vec3_01678dd0;     // 0x01678dd0

// eastl::vector<float, sp_vector_allocator> as laid out in retail (5 words)
struct FloatVec {
    float* mpBegin; float* mpEnd; float* mpCapacity; const char* mpName; int mpExtra;
    void Init() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void DoInsertValue(float* pos, const float& v);     // 0x00455660 (ret 8)
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) { float* p = mpEnd; mpEnd = p + 1; if (p) *p = v; }
        else DoInsertValue(mpEnd, v);
    }
};

struct Vec3Vec {
    Vec3f* mpBegin; Vec3f* mpEnd; Vec3f* mpCapacity; const char* mpName; int mpExtra;
    void Init() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void DoInsertValue(Vec3f* pos, const Vec3f& v);     // 0x007ed1b0 (ret 8)
    void push_back(const Vec3f& v)
    {
        if (mpEnd < mpCapacity) { Vec3f* p = mpEnd; mpEnd = p + 1; if (p) new (p) Vec3f(v); }
        else DoInsertValue(mpEnd, v);
    }
};

// A plain 3-word eastl vector whose elements need no destruction on free.
struct SimpleVec {
    void* mpBegin; void* mpEnd; void* mpCap;
    void Init() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
};

// A 3-word vector whose elements DO need destruction (cleared through a helper).
struct ClearVec {
    void* mpBegin; void* mpEnd; void* mpCap;
    void Init() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
    void Clear();                                       // 0x00a87300
};

struct cRefBase {
    int   mRefCount;                    // +0x04
    cRefBase() : mRefCount(0) {}
    void SetVtbl(void* v) { *(void**)this = v; }   // set the implicit vptr
};

struct cEffectParams : cRefBase {
    virtual ~cEffectParams();
    int   i08, i0c;
    float f10, f14, f18, f1c, f20, f24, f28, f2c, f30, f34, f38, f3c, f40;
    float f44, f48, f4c, f50, f54, f58, f5c, f60, f64;
    FloatVec v68;                       // +0x68
    float f7c;
    int   i80;
    FloatVec v84;                       // +0x84
    float f98;
    FloatVec v9c;                       // +0x9c
    FloatVec vb0;                       // +0xb0
    FloatVec vc4;                       // +0xc4
    float fd8, fdc, fe0, fe4, fe8, fec;
    Vec3Vec vf0;                        // +0xf0
    Vec3f v104;                         // +0x104
    FloatVec v110;                      // +0x110
    float f124;
    int   i128, i12c, i130;
    char  b134;
    char  pad135[3];
    Vec3f v138, v144;
    float f150, f154, f158;
    Vec3f v15c;
    float f168, f16c;
    SimpleVec v170;                     // +0x170
    char  pad17c[8];
    char  b184, b185, b186, b187;
    SimpleVec v188;                     // +0x188
    char  pad194[8];
    SimpleVec v19c;                     // +0x19c
    char  pad1a8[8];
    ClearVec  v1b0;                     // +0x1b0
    char  pad1bc[8];    float f1c4, f1c8, f1cc, f1d0, f1d4, f1d8, f1dc, f1e0, f1e4;
    int   i1e8, i1ec, i1f0, i1f4, i1f8, i1fc;
    float f200, f204, f208, f20c, f210, f214, f218;
    SimpleVec v21c;                     // +0x21c
    char  pad228[8];
    char  b230;
    char  pad231[3];
    float f234, f238, f23c, f240, f244, f248, f24c;
    SimpleVec v250;                     // +0x250
    char  pad25c[8];
    char  b264;
    char  pad265[3];
    Vec3f v268;
    float f274, f278, f27c;
    Vec3f v280;
    SimpleVec v28c;                     // +0x28c
    char  pad298[8];
    float f2a0, f2a4;
    SimpleVec v2a8;                     // +0x2a8
    char  pad2b4[8];
    float f2bc;

    cEffectParams();
};

// @ 0x00a99b20
cEffectParams::cEffectParams()
{
    i08 = 0; i0c = 0;
    f10 = 2.0f; f14 = 2.0f; f18 = 0.0f;
    f1c = -1.0f; f20 = -1.0f; f24 = -1.0f; f28 = -1.0f;
    f2c = 0.0f; f30 = 0.0f; f34 = 1.0f; f38 = 0.0f; f3c = 0.0f; f40 = 1.0f;
    f44 = 0.0f; f48 = 0.0f; f4c = 0.0f; f50 = 0.0f; f54 = 0.0f; f58 = 0.0f; f5c = 0.0f; f60 = 0.0f;
    f64 = -1.0f;
    v68.Init();
    f7c = 1.0f;
    i80 = 0;
    v84.Init();
    f98 = 0.0f;
    v9c.Init(); vb0.Init(); vc4.Init();
    fd8 = 0.0f; fdc = 0.0f; fe0 = 0.0f; fe4 = 0.0f; fe8 = 0.0f; fec = 0.0f;
    vf0.Init();
    v104.x = g_vec3_01678e1c.x; v104.y = g_vec3_01678e1c.y; v104.z = g_vec3_01678e1c.z;
    v110.Init();
    f124 = 0.0f;
    i128 = -1; i12c = 0; i130 = -1;
    b134 = 0;
    v138.x = g_vec3_01678e1c.x; v138.y = g_vec3_01678e1c.y; v138.z = g_vec3_01678e1c.z;
    v144.x = g_vec3_01678e1c.x; v144.y = g_vec3_01678e1c.y; v144.z = g_vec3_01678e1c.z;
    f150 = 0.0f; f154 = 0.0f; f158 = 0.0f;
    v15c.x = g_vec3_01678e1c.x; v15c.y = g_vec3_01678e1c.y; v15c.z = g_vec3_01678e1c.z;
    f168 = 0.0f; f16c = 0.0f;
    v170.mpBegin = 0; v170.mpEnd = 0; v170.mpCap = 0;
    b184 = 0; b185 = (char)0xff; b186 = 0; b187 = (char)0xff;
    v188.mpBegin = 0; v188.mpEnd = 0; v188.mpCap = 0;
    v19c.mpBegin = 0; v19c.mpEnd = 0; v19c.mpCap = 0;
    v1b0.mpBegin = 0; v1b0.mpEnd = 0; v1b0.mpCap = 0;
    f1d8 = -1000000000.0f;
    f1c4 = 1.0f; f1c8 = 0.0f; f1cc = 0.0f; f1d0 = 0.0f; f1d4 = 0.0f;
    f1dc = 0.0f; f1e0 = -10000.0f; f1e4 = 10000.0f;
    i1e8 = -1; i1ec = -1; i1f0 = -1; i1f4 = -1; i1f8 = -1; i1fc = -1;
    f200 = 5.0f; f204 = 5.0f; f208 = 0.0f; f20c = 0.0f; f210 = 0.25f; f214 = 0.0f; f218 = 0.0f;
    v21c.mpBegin = 0; v21c.mpEnd = 0; v21c.mpCap = 0;
    f234 = 5.0f; f238 = 5.0f;
    b230 = 2;
    f23c = 0.0f; f240 = 0.0f; f244 = 0.25f; f248 = 0.0f; f24c = 0.0f;
    v250.mpBegin = 0; v250.mpEnd = 0; v250.mpCap = 0;
    b264 = 2;
    v268.x = g_vec3_01678e1c.x; v268.y = g_vec3_01678e1c.y; v268.z = g_vec3_01678e1c.z;
    f274 = 0.0f; f278 = 0.0f; f27c = 0.0f;
    v280.x = g_vec3_01678e1c.x; v280.y = g_vec3_01678e1c.y; v280.z = g_vec3_01678e1c.z;
    v28c.mpBegin = 0; v28c.mpEnd = 0; v28c.mpCap = 0;
    f2a0 = 1.0f; f2a4 = 0.0f;
    v2a8.mpBegin = 0; v2a8.mpEnd = 0; v2a8.mpCap = 0;
    f2bc = 0.0f;

    v68.push_back(30.0f);
    Vec3f d = g_vec3_01678dd0;
    vf0.push_back(d);
    v110.push_back(1.0f);
    v84.push_back(1.0f);
    v9c.push_back(0.0f);
    vb0.push_back(0.0f);
    vc4.push_back(0.0f);
}

// ============================================================================================
// Rec7 vector machinery (elements are 0x1c bytes).  These are the eastl-style
// vector<Rec7> operations at 0x00a99640..0x00a9a500.
// ============================================================================================

struct Rec7 {
    uint32_t w0, w1, w2, w3, w4, w5, w6;    // 0x00..0x18
};

// Helpers implemented elsewhere in the retail image.
extern "C" Rec7* __cdecl CopyRec7(Rec7* first, Rec7* last, Rec7* out);       // 0x00a78e30
extern "C" Rec7* __cdecl MoveRec7(Rec7* first, Rec7* last, Rec7* out);       // 0x00a7a930
extern "C" void  __cdecl Rec7_ShiftBack(Rec7* first, Rec7* last, Rec7* out); // 0x006fd250
extern "C" void  __cdecl DestroyRangeRec7(Rec7* first, Rec7* last);          // 0x00d73090
extern "C" void  __cdecl FillRec7(Rec7* first, Rec7* last, const Rec7* v);   // 0x006fd140
extern "C" Rec7  __cdecl RotateCopy(const Rec7* first, const Rec7* last, Rec7* dst, const Rec7* dstEnd);  // 0x00a99350
extern "C" Rec7  __cdecl RotateCopy2(const Rec7* first, const Rec7* last, Rec7* dst); // 0x00a993b0
extern "C" Rec7* __cdecl AllocCopy(Rec7* dst, uint32_t n, const Rec7* v, Rec7* pos); // 0x00a99240
extern "C" void* __cdecl eastl_alloc_counted(size_t n);                      // 0x00f473a0
extern "C" void  __cdecl operator_delete_arr(void* p);                       // 0x00f47380 operator delete[]
extern "C" void  __cdecl ClearElements(void* begin, void* end);              // 0x00a87300

extern float gSentinel_15653e0;                                              // 0x015653e0

// eastl vector<Rec7> (=SP::cEffectParams-owned record vector).
struct RecVec {
    Rec7* mpBegin;      // 0x00
    Rec7* mpEnd;        // 0x04
    Rec7* mpCap;        // 0x08

    uint32_t size() const { return (uint32_t)((char*)mpEnd - (char*)mpBegin) / 0x1c; }
    uint32_t capacity() const { return (uint32_t)((char*)mpCap - (char*)mpBegin) / 0x1c; }

    void    reserve(uint32_t n, const void* tag);            // 0x00a05830
    void    UninitialisedFill(Rec7* out, uint32_t n, const Rec7* v); // 0x00a99410
    Rec7*   AllocCopyN(uint32_t n, const Rec7* first, const Rec7* last); // 0x00a9a250
    Rec7*   AllocMoveN(uint32_t n, const Rec7* first, const Rec7* last); // 0x00a9a2b0

    void    insert(Rec7* pos, uint32_t n, const Rec7& v);   // @ 0x00a99640
    void    resize(uint32_t n);                             // @ 0x00a99a10
    void    resizeZero(uint32_t n);                         // @ 0x00a99a90
    RecVec* reserveFill(const RecVec* src);                 // @ 0x00a9a310
    RecVec* reserveFill2(const RecVec* src);                // @ 0x00a9a370
    RecVec* assign(const RecVec& src);                      // @ 0x00a9a3d0
    RecVec* assignMove(const RecVec& src);                  // @ 0x00a9a500
};

// raw, counted-allocation free used by every destructor in this slice
static inline void FreeCounted(void* p) {
    if (p) {
        if (((int*)p)[-1] != 0)
            operator_delete_arr(p);
    }
}

// @ 0x00a99640  vector<Rec7>::insert(pos, n, value)
void RecVec::insert(Rec7* pos, uint32_t n, const Rec7& v)
{
    uint32_t freeSlots = capacity() - size();
    if (n > freeSlots) {
        uint32_t old = size();
        uint32_t cap = old * 2;
        if (old == 0)
            cap = 1;
        uint32_t need = old + n;
        if (need > cap)
            cap = need;
        Rec7* nw = cap ? (Rec7*)eastl_alloc_counted(cap * 0x1c) : 0;
        Rec7* mid = CopyRec7(mpBegin, pos, nw);
        AllocCopy(mid, n, &v, pos);
        Rec7* tail = CopyRec7(pos, mpEnd, mid + n);
        FreeCounted(mpBegin);
        mpBegin = nw;
        mpEnd = tail;
        mpCap = nw + cap;
    } else if (n) {
        Rec7 tmp = v;
        uint32_t room = (uint32_t)((char*)mpEnd - (char*)pos) / 0x1c;
        if (n < room) {
            Rec7* split = mpEnd - n;
            RotateCopy2(split, mpEnd, mpEnd);
            Rec7* e = mpEnd;
            mpEnd += n;
            Rec7_ShiftBack(pos, split, e);
            FillRec7(pos, (Rec7*)((char*)pos + n * 0x1c), &tmp);
        } else {
            uint32_t extra = n - room;
            AllocCopy(mpEnd, extra, &tmp, pos);
            Rec7* e = mpEnd;
            mpEnd += extra;
            RotateCopy2(pos, e, mpEnd);
            mpEnd += room;
            FillRec7(pos, e, &tmp);
        }
    }
}

// @ 0x00a99a10  vector<Rec7>::resize(n)
void RecVec::resize(uint32_t n)
{
    if (size() < n) {
        uint32_t extra = n - size();
        Rec7 tmp;
        UninitialisedFill(mpEnd, extra, &tmp);   // member helper bumps mpEnd internally
    } else {
        DestroyRangeRec7(mpBegin + n, mpEnd);
        mpEnd = mpBegin + n;
    }
}

// @ 0x00a99a90  vector<Rec7>::resize(n) with a zero-filled value
void RecVec::resizeZero(uint32_t n)
{
    if (size() < n) {
        Rec7 tmp;
        tmp.w0=0; tmp.w1=0; tmp.w2=0; tmp.w3=0; tmp.w4=0; tmp.w5=0; tmp.w6=0;
        insert(mpEnd, n - size(), tmp);
    } else {
        DestroyRangeRec7(mpBegin + n, mpEnd);
        mpEnd = mpBegin + n;
    }
}

// @ 0x00a9a310  reserve the source's element count then splice its range in
RecVec* RecVec::reserveFill(const RecVec* src)
{
    uint32_t n = src->size();
    reserve(n, &src->mpCap);
    RotateCopy(src->mpBegin, src->mpEnd, mpBegin, 0);
    mpEnd = mpBegin + n;
    return this;
}

// @ 0x00a9a370  same shape, move flavour
RecVec* RecVec::reserveFill2(const RecVec* src)
{
    uint32_t n = src->size();
    reserve(n, &src->mpCap);
    RotateCopy2(src->mpBegin, src->mpEnd, mpBegin);
    mpEnd = mpBegin + n;
    return this;
}

// @ 0x00a9a3d0  vector<Rec7>::operator=
RecVec* RecVec::assign(const RecVec& src)
{
    if (&src != this) {
        uint32_t n = src.size();
        if (capacity() < n) {
            Rec7* nw = AllocCopyN(n, src.mpBegin, src.mpEnd);
            FreeCounted(mpBegin);
            mpBegin = nw;
            mpCap = nw + n;
        } else if (size() < n) {
            uint32_t have = size();
            MoveRec7(src.mpBegin, src.mpBegin + have, mpBegin);
            RotateCopy(src.mpBegin + have, src.mpEnd, mpEnd, 0);
        } else {
            MoveRec7(src.mpBegin, src.mpEnd, mpBegin);
        }
        mpEnd = mpBegin + n;
    }
    return this;
}

// @ 0x00a9a500  vector<Rec7>::operator= (move-flavoured)
RecVec* RecVec::assignMove(const RecVec& src)
{
    if (&src != this) {
        uint32_t n = src.size();
        if (capacity() < n) {
            Rec7* nw = AllocMoveN(n, src.mpBegin, src.mpEnd);
            FreeCounted(mpBegin);
            mpBegin = nw;
            mpCap = nw + n;
        } else if (size() < n) {
            uint32_t have = size();
            MoveRec7(src.mpBegin, src.mpBegin + have, mpBegin);
            RotateCopy2(src.mpBegin + have, src.mpEnd, mpEnd);
        } else {
            MoveRec7(src.mpBegin, src.mpEnd, mpBegin);
        }
        mpEnd = mpBegin + n;
    }
    return this;
}

// @ 0x00a9a1c0  shift a 6-float block unless its head is the sentinel value
struct Float6 {
    float v[6];
    void Shift(float dx, float dy, float dz);        // 0x00a9a1c0
};

void Float6::Shift(float dx, float dy, float dz)
{
    const float s = gSentinel_15653e0;
    if (v[0] == s || v[0] == -s)
        return;
    v[0] -= dx; v[1] -= dy; v[2] -= dz;
    v[3] += dx; v[4] += dy; v[5] += dz;
}

void ClearVec::Clear()
{
    ClearElements(mpBegin, mpEnd);
}

// @ 0x00a99870  ~cEffectParams
cEffectParams::~cEffectParams()
{
    FreeCounted(v2a8.mpBegin);
    FreeCounted(v28c.mpBegin);
    FreeCounted(v250.mpBegin);
    FreeCounted(v21c.mpBegin);
    v1b0.Clear();
    FreeCounted(v1b0.mpBegin);
    FreeCounted(v19c.mpBegin);
    FreeCounted(v188.mpBegin);
    FreeCounted(v170.mpBegin);
    FreeCounted(v110.mpBegin);
    FreeCounted(vf0.mpBegin);
    FreeCounted(vc4.mpBegin);
    FreeCounted(vb0.mpBegin);
    FreeCounted(v9c.mpBegin);
    FreeCounted(v84.mpBegin);
    FreeCounted(v68.mpBegin);
    SetVtbl((void*)0x13ef094);
}

