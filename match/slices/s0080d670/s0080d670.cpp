// Slice s0080d670 (batch w2g6).
// cSPUILayeredObject / cSPUIModelsAndEffectsRenderer rendering helpers.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE2 (most functions). d810 uses an 8-byte aligned frame.
#include <intrin.h>
#include <math.h>
#include <xmmintrin.h>
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;

void* __cdecl  GameFree(void*);
int  __fastcall Fun104(void*);                    // 0x104c100
u8   __cdecl  VisitSeq(void*, u8*);               // 0x80d620 (slice 23)
void  __cdecl  VisitTree(void*, void*, void*);    // 0x807d30 SPUIHelpers::VisitWindowTreeDepthFirst
void* __cdecl  BBoxAdd();                          // 0x67cad0 cSPBoundingBox::AddBoundingBox
void* __cdecl  ModelMgr();                         // 0x67dd80
void* __cdecl  EffectsMgr();                       // 0x67ddd0
void* __cdecl  GetRaster();                        // 0x67dd50
void* __cdecl  Fun82e4a0();                        // 0x82e4a0
void  __fastcall Fun7c4a60(void*, void*, void*);        // 0x7c4a60 cViewer::FUN_007c4a60
void  __fastcall Fun7c4b50(void*, void*, float);        // 0x7c4b50 cViewer::FUN_007c4b50
void  __fastcall Fun7c3c50(void*, void*, int);          // 0x7c3c50 cViewer::Clear
void  __fastcall BoundingBox_TransformBy(void*, void*, void*); // 0x409dd0 cSPBoundingBox::Transform
int   __cdecl  Fun95ea30(void*);                   // 0x95ea30

typedef void* (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF0v)(void*);
typedef void* (__thiscall *VF1)(void*, void*);
typedef void  (__thiscall *VF1v)(void*, void*);
typedef void* (__thiscall *VF1a)(void*, void*, void*);
typedef void  (__thiscall *VF2v)(void*, void*, void*, int);
typedef void  (__thiscall *VF3v)(void*, void*, void*, void*, void*);

struct Vec2 {
    f32 x, y;
    Vec2() {}
    Vec2(f32 a, f32 b) : x(a), y(b) {}
    Vec2(const Vec2& o) : x(o.x), y(o.y) {}
};
struct Rect4 { f32 x0, y0, x1, y1; };

typedef void  (__thiscall *VFtf)(void*, void*, Vec2);
static inline void** VT(void* o) { return *(void***)o; }

// Retail carries every float temporary in an SSE register (single precision, no x87 excess).
static inline f32 SseSub(f32 a, f32 b) { return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b))); }
static inline f32 SseMul(f32 a, f32 b) { return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b))); }
static inline f32 SseDiv(f32 a, f32 b) { return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b))); }

// generic layered object
struct Layered {
    u8  pad0[8];
    void* renderer;  // +0x8
    void** vBegin;   // +0xc
    void** vEnd;     // +0x10
    void** v2Begin;  // +0x14
    void** v2End;    // +0x18
    u8  pad1c[0x10];          // +0x1c..+0x2b
    u8  modelTransform[0x10]; // +0x2c..+0x3b
    void* obj3c;     // +0x3c
    u8  pad40[4];
    u8  bits44[0x1c]; // +0x44..+0x5f
    u8  pad60[4];     // +0x60..+0x63
    f32 rectMinX;     // +0x64
    f32 rectMinY;     // +0x68
    f32 rectMaxX;     // +0x6c
    f32 rectMaxY;     // +0x70
    u8  flag74;       // +0x74
    u8  flag75;       // +0x75
    u8  flag76;       // +0x76
    u8  pad77;        // +0x77
    u8  flag78;       // +0x78
    u8  pad79[0x1cc - 0x79];
    u8  flag1cc;     // +0x1cc
    u8  pad1d4[0x1d4 - 0x1cd];
    i32 r1d4;        // +0x1d4
    i32 r1d8;        // +0x1d8
    i32 r1dc;        // +0x1dc
    i32 r1e0;        // +0x1e0
    u8  entries1e4[0x24c - 0x1e4];  // 6 * 0x14
    u8  flag24c;     // +0x24c
    u8  pad250[0x250 - 0x24d];
    void* p250;      // +0x250
    void* p254;      // +0x254
    void* p258;      // +0x258
    void* p25c;      // +0x25c
    void* p260;      // +0x260

    u8*  Method810(void* win);            // 0x80d810
    void MethodDA50(void* param, void*, void*, void*, void*); // 0x80da50
    void ReleaseAll();                    // 0x80dbb0
    void MethodDC50(int);                 // 0x80dc50
    void* MethodDC90();                   // 0x80dc90
    int  MethodDD50();                    // 0x80dd50
    void SetObj(void* p, u8 b);           // 0x80dda0
    void RenderEnd();                     // 0x80de20
    void* CameraLocZoom(void* outVec3, float* outZoom); // 0x80dfe0
    bool RenderBegin(int id);             // 0x80e270
};

// renderer device passed a CamState snapshot (0x7c40f0/0x7c4d00 family)
struct Renderer {
    void __thiscall SetViewport(int x, int y, int w, int h); // 0x7c5310
    void __thiscall SetAspect(float aspect);                 // 0x7c4b50
    void __thiscall SetFov(float fov);                       // 0x7c53d0
    void __thiscall SetNearFar(float d);                     // 0x7c4ba0
    void __thiscall Snapshot(void* state);                   // 0x7c40f0
    void __thiscall Submit(void* state);                     // 0x7c4d00
};

struct CamState {
    u16 flags;      // +0x00
    u16 count;      // +0x02
    f32 x;          // +0x04
    f32 y;          // +0x08
    f32 z;          // +0x0c
    f32 w;          // +0x10
    f32 basis[9];   // +0x14..+0x37
};

u8   __cdecl  FUN_8050b0(void*);              // 0x8050b0
void __cdecl  FUN_805ea0(void* outRect);      // 0x805ea0
void __cdecl  CamStateInit(CamState* s);      // 0x409930

// cSPUIModelsAndEffectsRenderer: renders/refcounted
struct ModelsRenderer {
    int __thiscall Release();   // 0x80df80
};

// @ 0x0080d670
u8 __cdecl FUN_0080d670(void* p, u8* p2)
{
    int v = 0;
    if (p) {
        void* x = ((VF0)VT(p)[0x4c / 4])(p);
        if (x) v = Fun104(x);
    }
    VisitSeq(p, (u8*)(*(i32*)(p2 + 4) + v));
    return *p2;
}

// @ 0x0080d6b0
u8 __cdecl FUN_0080d6b0(void* p, u8* p2)
{
    VisitSeq(p, (u8*)*(i32*)(p2 + 4));
    return *p2;
}

// @ 0x0080d6d0
u16 __cdecl FUN_0080d6d0(void* p, u8* p2)
{
    int v = 0;
    if (p) {
        void* x = ((VF0)VT(p)[0x4c / 4])(p);
        if (x) v = Fun104(x);
    }
    if (*(i32*)(p2 + 4) > v) *(i32*)(p2 + 4) = v;
    if (*(i32*)(p2 + 8) < v) *(i32*)(p2 + 8) = v;
    return (u16)((v & 0xff00) | *p2);
}

// @ 0x0080d710  SP::Renderer
void __stdcall FUN_0080d710(void* a, void* b, u8 c)
{
    u8 local[8];
    local[0] = c;
    *(void**)(local + 4) = b;
    VisitTree(a, (void*)FUN_0080d6b0, local);
}

// @ 0x0080d770
void __cdecl FUN_0080d770(void* a, void* b, void* p3)
{
    ((VF2v)VT(p3)[0xc / 4])(p3, a, b, 4);
}

struct FlagSetter { int __thiscall Set790(char p2, char p3); };
// @ 0x0080d790
int FlagSetter::Set790(char p2, char p3)
{
    char* self = (char*)this;
    self[0x75] = p2;
    int v = (p2 && !p3);
    self[0x76] = v;
    return v;
}

// @ 0x0080d7e0
i32 __cdecl FUN_0080d7e0(float* a, float* b)
{
    if (a[0] == b[0] && a[1] == b[1]) return 0;
    return 1;
}

// @ 0x0080db70
void* __fastcall FUN_0080db70(char* p)
{
    if (p) return *(void**)(p + 8);
    return *(void* volatile*)(p + 0x258);
}

// @ 0x0080db90
void* __fastcall FUN_0080db90(char* p)
{
    if (p) return *(void**)(p + 4);
    return *(void* volatile*)(p + 0x254);
}

// @ 0x0080d810
u8* Layered::Method810(void* win)
{
    u32 i = 0;
    u8* e = entries1e4;
    for (; i < 6; ++i, e += 0x14)
        if (*e == 0) break;
    if (i == 6) return 0;
    *e = 1;

    f32* r = (f32*)((VF0)VT(win)[0x38 / 4])(win);
    f32 w = SseSub(r[2], r[0]);
    f32 h = SseSub(r[3], r[1]);

    Vec2 p0, p1, p2, p3;
    VFtf tf = (VFtf)VT(win)[0xc0 / 4];
    tf(win, &p0, Vec2(0.0f, 0.0f));
    tf(win, &p1, Vec2(w, h));
    tf(win, &p2, Vec2(w, 0.0f));
    tf(win, &p3, Vec2(0.0f, h));

    const f32& maxY1 = p3.y > p2.y ? p3.y : p2.y;
    const f32& maxY2 = maxY1 > p1.y ? maxY1 : p1.y;
    const f32& maxY = maxY2 > p0.y ? maxY2 : p0.y;
    const f32& maxX1 = p3.x > p2.x ? p3.x : p2.x;
    const f32& maxX2 = maxX1 > p1.x ? maxX1 : p1.x;
    const f32& maxX = maxX2 > p0.x ? maxX2 : p0.x;
    const f32& minY1 = p2.y > p3.y ? p3.y : p2.y;
    const f32& minY2 = p1.y > minY1 ? minY1 : p1.y;
    const f32& minY = p0.y > minY2 ? minY2 : p0.y;
    const f32& minX1 = p2.x > p3.x ? p3.x : p2.x;
    const f32& minX2 = p1.x > minX1 ? minX1 : p1.x;
    const f32& minX = p0.x > minX2 ? minX2 : p0.x;

    u8* rect = (u8*)((char*)this + i * 0x14 + 0x1d4);
    ((i32*)rect)[0] = (i32)minX;
    ((i32*)rect)[1] = (i32)minY;
    ((i32*)rect)[2] = (i32)maxX;
    ((i32*)rect)[3] = (i32)maxY;
    return rect;
}

// @ 0x0080da50
struct DARecord {
    void* obj;   // +0
    void* a;     // +4
    void* b;     // +8
};

void Layered::MethodDA50(void* param, void* a2, void* a3, void* a4, void* a5)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    void* bb = BBoxAdd();
    if (*(i32*)((char*)bb + 0x38) != 0) return;
    if (flag24c && param) {
        Fun7c4a60((char*)this + 0x60, 0, param);
        flag1cc = 0;
        u32 w = (u32)(*(i32*)((char*)param + 8) - *(i32*)param);
        u32 h = (u32)(*(i32*)((char*)param + 0xc) - *(i32*)((char*)param + 4));
        if (w != 0 && h != 0) {
            void* r = GetRaster();
            void* info = ((VF0)VT(r)[0x1c / 4])(r);
            f32 f = (f32)w * *(f32*)((char*)info + 0x1c) / (f32)h;
            Fun7c4b50((char*)this + 0x60, 0, f);
        }
    }
    Fun7c3c50((char*)this + 0x60, 0, 6);
    DARecord* begin = (DARecord*)vBegin;
    i32 n = (i32)((u8*)vEnd - (u8*)vBegin) / 0xc;
    if (n > 0) {
        struct Local { i32 a, b, c, pad0, pad1; } local;
        local.a = local.b = local.c = local.pad0 = local.pad1 = 0;
        DARecord* it = begin;
        for (i32 i = 0; i < n; ++i, ++it) {
            void* o = it->obj;
            void* result = Fun82e4a0();
            ((VF3v)VT(o)[0xc / 4])(o, it->b, it->a, &local, result);
        }
    }
}

// @ 0x0080dbb0
void Layered::ReleaseAll()
{
    if (!p258) return;
    if (p258) {
        void* o = p258;
        p258 = 0;
        ((VF0v)VT(o)[1])(o);
    }
    {
        void* m = ModelMgr();
        ((VF1v)VT(m)[0x18 / 4])(m, p25c);
    }
    p25c = 0;
    if (p254) {
        void* o = p254;
        p254 = 0;
        ((VF0v)VT(o)[1])(o);
    }
    {
        void* m = EffectsMgr();
        ((VF1v)VT(m)[0x50 / 4])(m, p260);
    }
    p260 = 0;
    ((VF0v)VT(p250)[0x7c / 4])(p250);
    if (p250) {
        void* o = p250;
        p250 = 0;
        ((VF0v)VT(o)[1])(o);
    }
}

// @ 0x0080dc50
void Layered::MethodDC50(int)
{
    if (!obj3c) return;
    void* r = ((VF1)VT(obj3c)[0x144 / 4])(obj3c, 0);
    if (!r) return;
    void* r2 = ((VF1)VT(obj3c)[0x144 / 4])(obj3c, 0);
    ((VF0v)VT(r2)[0x30 / 4])(r2);
}

// @ 0x0080dc90
void* Layered::MethodDC90()
{
    if (!obj3c) return 0;
    void* r = ((VF1)VT(obj3c)[0x144 / 4])(obj3c, 0);
    if (!r) return 0;
    void* r2 = ((VF1)VT(obj3c)[0x144 / 4])(obj3c, 0);
    return ((VF0)VT(r2)[0x34 / 4])(r2);
}

// @ 0x0080dcd0
void __stdcall FUN_0080dcd0(void* a, i32 b, u8 c)
{
    u8 local_c[8];
    *(i32*)(local_c + 4) = 10000;
    *(i32*)(local_c + 8) = 0xffffd8f0;
    local_c[0] = 1;
    VisitTree(a, (void*)FUN_0080d6d0, local_c);
    i32 d = b - *(i32*)(local_c + 4);
    u8 local14[8];
    local14[0] = c;
    *(i32*)(local14 + 4) = d;
    if (d != 0) VisitTree(a, (void*)FUN_0080d670, local14);
}

// @ 0x0080dd50
struct DDBounds {
    i32 flag;    // +0 (only the low byte is used)
    i32 lo;      // +4
    i32 hi;      // +8
};

int Layered::MethodDD50()
{
    void* p = vBegin;
    if (!p) return 0;
    BBoxAdd();
    DDBounds local;
    local.flag = 0;
    local.lo = 10000;
    local.hi = -10000;
    VisitTree(p, (void*)FUN_0080d6d0, &local);
    return local.lo;
}

// @ 0x0080dda0
void Layered::SetObj(void* param, u8 b)
{
    void* old = vBegin;
    if (old == param) return;
    if (*(u8*)((char*)this + 0x74)) {
        ((VF1v)VT(old)[0x108 / 4])(old, *(void**)((char*)this + 0x10));
    }
    if (param != old) {
        if (param) ((VF0v)VT(param)[0])(param);
        vBegin = (void**)param;
        if (old) ((VF0v)VT(old)[1])(old);
    }
    u8 nv;
    if (vBegin == 0 || b == 0) nv = 0; else nv = 1;
    *(u8*)((char*)this + 0x74) = nv;
    if (nv) {
        void* cur = vBegin;
        ((VF1v)VT(cur)[0x104 / 4])(cur, *(void**)((char*)this + 0x10));
    }
}

// @ 0x0080de20
void Layered::RenderEnd()
{
    void** it = v2Begin;
    void** end = v2End;
    while (it != end) {
        void* o = *it++;
        void* m = ModelMgr();
        u32 idx = (u32)(size_t)((VF1)VT(m)[0x28 / 4])(m, (void*)0x32fab27);
        if (idx < 0x40) {
            u32* p = (u32*)((char*)o + 0x44 + (idx >> 5) * 4);
            *p &= ~(1u << (idx & 0x1f));
        }
    }
}

// @ 0x0080de80
void* __cdecl FUN_0080de80(void** first, void** last, void** dest)
{
    while (first != last) {
        if (dest) {
            void* o = *first;
            *dest = o;
            if (o) ((VF0v)VT(o)[0])(o);
        }
        ++first; ++dest;
    }
    return dest;
}

// @ 0x0080df00
void* __cdecl FUN_0080df00(void** first, void** last, void** dest)
{
    while (first != last) {
        if (dest) {
            void* o = *first;
            *dest = o;
            if (o) ((VF0v)VT(o)[0])(o);
            dest[1] = first[1];
            dest[2] = first[2];
        }
        first += 3; dest += 3;
    }
    return dest;
}

// @ 0x0080df50
int __fastcall FUN_0080df50(char* p)
{
    char* b = (p && p != (char*)0x250) ? p - 0x24c : 0;
    return _InterlockedIncrement((long*)(b + 4));
}

// @ 0x0080df80
int __thiscall ModelsRenderer::Release()
{
    char* p = (char*)this;
    char* b = 0;
    if (p) { char* t = p - 0x250; if (t) b = t + 4; }
    long* rc = (long*)(b + 4);
    int n = _InterlockedExchangeAdd(rc, -1) - 1;
    if (n == 0) {
        _InterlockedExchange(rc, 1);
        if (b) ((VF1v)VT(b)[0])(b, (void*)1);
        return 0;
    }
    return n;
}

// @ 0x0080dfc0
void __fastcall FUN_0080dfc0(char* p)
{
    if (p) ((Layered*)(p - 0x250))->ReleaseAll();
    else   ((Layered*)0)->ReleaseAll();
}

// @ 0x0080dfe0
struct Box6 {
    f32 minx, miny, minz;   // +0x00
    f32 maxx, maxy, maxz;   // +0x0c
};

struct ModelObj {
    u8  pad0[4];
    u32 flags;   // +0x04
    u8  pad8[4];
    f32 tx;      // +0x0c
    f32 ty;      // +0x10
    f32 tz;      // +0x14
};

void* Layered::CameraLocZoom(void* outVec3, float* outZoom)
{
    Box6 box;
    box.minx = box.miny = box.minz = 3.402823466e+38F;
    box.maxx = box.maxy = box.maxz = -3.402823466e+38F;

    void* bbox = BBoxAdd();
    void* mgr = *(void**)((char*)bbox + 0x3c);
    ModelObj** begin = (ModelObj**)v2Begin;
    u32 n = (u32)((u8*)v2End - (u8*)v2Begin) >> 2;
    void* lastObj = bbox;

    for (u32 i = 0; i < n; ++i) {
        ModelObj* obj = begin[i];
        lastObj = obj;
        u32 flags = obj->flags;
        if (((flags >> 0xf) & 1) && (flags & 1)) {
            float* pf = (float*)((VF1)VT(mgr)[0x60 / 4])(mgr, obj);
            obj = begin[i];
            f32 tx = obj->tx, ty = obj->ty, tz = obj->tz;
            f32 cmnx = tx + pf[0];
            f32 cmny = ty + pf[1];
            f32 cmnz = tz + pf[2];
            f32 cmxx = tx + pf[3];
            f32 cmxy = ty + pf[4];
            f32 cmxz = tz + pf[5];
            if (box.minx <= box.maxx) {
                if (cmnx < box.minx) box.minx = cmnx;
                if (box.maxx < cmxx) box.maxx = cmxx;
                if (cmny < box.miny) box.miny = cmny;
                if (box.maxy < cmxy) box.maxy = cmxy;
                if (cmnz < box.minz) box.minz = cmnz;
                if (box.maxz < cmxz) box.maxz = cmxz;
            } else {
                box.minx = cmnx; box.miny = cmny; box.minz = cmnz;
                box.maxx = cmxx; box.maxy = cmxy; box.maxz = cmxz;
            }
        }
    }

    if (box.minx <= box.maxx) {
        BoundingBox_TransformBy(&box, 0, modelTransform);
        ((float*)outVec3)[0] = (box.maxx + box.minx) * 0.5f;
        ((float*)outVec3)[1] = (box.maxy + box.miny) * 0.5f;
        ((float*)outVec3)[2] = (box.maxz + box.minz) * 0.5f;
        double dx = (double)box.maxx - (double)box.minx;
        double dy = (double)box.maxy - (double)box.miny;
        double dz = (double)box.maxz - (double)box.minz;
        double sum = (dx * dx + dz * dz) + dy * dy;
        *outZoom = (f32)(sqrt(sum) * 1.8f);
        return outVec3;
    }
    return lastObj;
}

// @ 0x0080e270
bool Layered::RenderBegin(int id)
{
    if (!vBegin) return false;
    if (MethodDD50() != id) return false;
    void** it = v2Begin;
    void** end = v2End;
    if (it == end) return false;
    if (!FUN_8050b0(vBegin)) return false;

    f32 cb = 0.0f, cg = 0.0f, cr = 0.0f, ca = 0.0f;
    if (flag78) {
        u32 c = (u32)(size_t)((VF0)VT(vBegin)[0x30 / 4])(vBegin);
        const f32 k = 0.0039215689f;
        cb = (f32)((c >> 16) & 0xff) * k;
        cg = (f32)((c >> 8) & 0xff) * k;
        cr = (f32)(c & 0xff) * k;
        ca = (f32)(c >> 24) * k;
    }

    for (; it != end; ++it) {
        void* obj = *it;
        void* mgr = ModelMgr();
        u32 idx = (u32)(size_t)((VF1a)VT(mgr)[0x28 / 4])(mgr, (void*)0x32fab27, (void*)0);
        if (idx < 0x40) {
            u32* bits = (u32*)((char*)obj + 0x44 + (idx >> 5) * 4);
            *bits |= 1u << (idx & 0x1f);
        }
        if (flag78) {
            u32 flags = *(u32*)((char*)obj + 4);
            if (flags & 2) {
                *(f32*)((char*)obj + 0x4c) = cb;
                *(f32*)((char*)obj + 0x50) = cg;
                *(f32*)((char*)obj + 0x54) = cr;
                *(f32*)((char*)obj + 0x58) = ca;
            }
        }
    }

    if (!flag75 && !flag76) return true;

    f32* wr = (f32*)((VF0)VT(vBegin)[0x38 / 4])(vBegin);
    f32 rx0 = wr[0], ry0 = wr[1], rx1 = wr[2], ry1 = wr[3];

    Vec2 p0, p1;
    VFtf tf = (VFtf)VT(vBegin)[0xc0 / 4];
    tf(vBegin, &p0, Vec2(0.0f, 0.0f));
    tf(vBegin, &p1, Vec2(rx1 - rx0, ry1 - ry0));

    bool changed = FUN_0080d7e0((float*)&p0, &rectMinX) != 0
                || FUN_0080d7e0((float*)&p1, &rectMaxX) != 0;

    rectMinX = p0.x;
    rectMinY = p0.y;
    rectMaxX = p1.x;
    rectMaxY = p1.y;
    if (rectMinX >= rectMaxX) return false;
    if (rectMinY >= rectMaxY) return false;

    Rect4 vp;
    FUN_805ea0(&vp);
    if (0.0f > rectMaxX) return false;
    if (0.0f > rectMaxY) return false;
    if (rectMinX > vp.x1 - vp.x0) return false;
    if (rectMinY > vp.y1 - vp.y0) return false;

    if (!changed) return true;

    f32 w = rectMaxX - rectMinX;
    f32 h = rectMaxY - rectMinY;
    int iw = (int)w;
    int ih = (int)h;
    int ix = (int)rectMinX;
    int iy = (int)rectMinY;

    Renderer* dev = (Renderer*)renderer;
    dev->SetViewport(ix, iy, iw, ih);
    dev->SetAspect((f32)iw / (f32)ih);
    if (flag76) return true;

    dev->SetFov(50.0f);
    dev->SetNearFar(0.01f);

    f32 camPos[3];
    f32 zoom;
    CameraLocZoom(camPos, &zoom);

    CamState cs;
    CamStateInit(&cs);
    dev->Snapshot(&cs);
    cs.flags |= 4;
    ++cs.count;
    cs.x = camPos[0] - zoom * cs.basis[3];
    cs.y = camPos[1] - zoom * cs.basis[4];
    cs.z = camPos[2] - zoom * cs.basis[5];
    dev->Submit(&cs);
    return true;
}
