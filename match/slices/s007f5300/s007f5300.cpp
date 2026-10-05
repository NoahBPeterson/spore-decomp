// Sims3/UTFWin UI module, slice s007f5300 (0x7F5300..0x7F64C6).
// /O2. IMEComposition / cSPUIAnimatedIconWin / cSPUIAnimator and the SPUI
// animation time-function factories.
#include "types.h"

#define VTOBJ(p) (*(void***)(p))

typedef void   (__thiscall *FV0)(void*);
typedef void   (__thiscall *FVI)(void*, int);
typedef void   (__thiscall *FVP)(void*, void*);
typedef void*  (__thiscall *FPR0)(void*);
typedef void*  (__thiscall *FPRP)(void*, void*);
typedef void*  (__thiscall *FPRI)(void*, int);
typedef char   (__thiscall *FPC0)(void*);
typedef char   (__thiscall *FPCV)(void*, void*);
typedef int    (__thiscall *FPI0)(void*);
typedef int64_t(__thiscall *FPI64)(void*);

// externals (relocations masked)
void* __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(int size, int align, const char* name, void* caller);
void* __cdecl FUN_0095fba0();
void  __cdecl deallocate(void* p);
void  __cdecl IMEComp_CalculateTextSize(void* out, void* a, int b, void* c, void* d);
float __cdecl SPUIHelpers_GetElapsedSeconds();

// stub for declared-only callees; overloads give the right stack cleanup
struct Callee {
    void  f();
    void  f(int);
    void  f(void*);
    void  f(void*, int);
    void  f(int, int);
    void  f(void*, int, int);
    void  f(void*, void*, int, int);
    void  f(float);
    void  f(float, float);
    void  f(float, float, float);
    void  f6(float, float, float, float, float, float);
    void  resize(int);
    void* ctor();
    void* ctor2(int, int);
    void* ctorff(float, float);
    void* ctorf(float);
    bool  b();
    bool  b(void*);
    void* p();
    void* p(int);
    int64_t i64();
};
struct WT { bool Initialize(); bool Dispose(); void Shutdown(); };
struct CastStub { void* Cast(int); };
struct VecCallee { void resize(int); };

extern void* g_vt_014153bc;
extern void* g_vt_013f6400;
extern void* g_vt_013f63fc;
extern void* g_vt_01415298;
extern void* g_vt_01415178;
extern void* g_vt_01415144;
extern void* g_vt_0141513c;
extern void* g_vt_013eb938;
extern void* g_vt_01415350;
extern void* g_vt_01415338;
extern void* g_vt_013fa72c;
extern const float g_c1000;
extern const float g_c001;
extern const float g_c200;
extern const float g_c10;
extern const float g_c100;
extern const float g_c001p;
extern const float g_c01;
extern const float g_c1f;

// --------------------------------------------------------------------------
struct Obj {
    void  M5300(void* p);
    int   M53C0(void* p);
    bool  M53D0();
    void* M5410(int type);
    bool  M5460(int v);
    int   M5490();
    void  M54B0(int v);
    bool  M54E0();
    void  M55B0();
    bool  M55F0(void* ev);
    bool  M5660(void* p);
    void  M5690();
    void  M56C0();
    float M56E0();
    bool  M5710(float v);
    void  M58E0();
    bool  M5990();
    bool  M59E0(void* obj, int a2, int a3, int a4);
    bool  M5A60(void* ctx);
    bool  M5BD0(void* out, int, int);
    Obj*  M5C20();
    void  M5D00();
    void* M5FF0(char flags);
};

// @ 0x007F5300
void Obj::M5300(void* p)
{
    if (p == 0)
        return;
    if (*(int*)p != 0) {
        void* t = FUN_0095fba0();
        int out[2];
        IMEComp_CalculateTextSize(out, *(void**)p, *(int*)((char*)p + 8),
                                  *(void**)((char*)this + 0x6b8), t);
        void* sub = (char*)this + 4;
        ((Callee*)sub)->f(*(void**)p);
    }
    if (*(int*)((char*)p + 4) != 0) {
        void* vec = (char*)this + 0x694;
        ((VecCallee*)vec)->resize(*(int*)((char*)p + 8));
        uint32_t n = (uint32_t)*(int*)((char*)p + 8);
        for (uint32_t i = 0; i < n; ++i) {
            uint8_t* src = (uint8_t*)*(void**)((char*)p + 4);
            uint8_t* dst = (uint8_t*)*(void**)((char*)this + 0x694);
            dst[i] = src[i];
            if (dst[i] >= 4)
                dst[i] = 0;
        }
    }
    ((Callee*)this)->f();
    ((Callee*)this)->f(p);
    void* sub = (char*)this + 4;
    ((Callee*)sub)->f();
}

// @ 0x007F53C0
int Obj::M53C0(void* p)
{
    return *(int*)((char*)p + 0x10) + *(int*)((char*)this + 4);
}

// @ 0x007F53D0
bool Obj::M53D0()
{
    if (*(char*)((char*)this + 0x22c) != 0)
        return true;
    void* f = VTOBJ(this)[0x98 / 4];
    *(char*)((char*)this + 0x22c) = 1;
    ((void(__thiscall*)(void*))f)(this);
    void* sub = (char*)this + 4;
    ((FV0)VTOBJ(sub)[0x90 / 4])(sub);
    return ((WT*)this)->Initialize();
}

// @ 0x007F5410
void* Obj::M5410(int type)
{
    if (type == 0x105a93d) {
        if (this != 0)
            return (char*)this + 0x20c;
        return 0;
    }
    if (type == 0x106f146)
        return this;
    if (type != 0x10edf11)
        return ((CastStub*)this)->Cast(type);
    if (this != 0)
        return (char*)this + 0x210;
    return 0;
}

// @ 0x007F5460
bool Obj::M5460(int v)
{
    if (v < 0)
        return true;
    if (v >= *(int*)((char*)this + 0x24))
        return true;
    if (*(int*)((char*)this + 0x1c) == v)
        return true;
    *(int*)((char*)this + 0x1c) = v;
    void* full = (char*)this - 0x208;
    ((FV0)VTOBJ(full)[0x90 / 4])(full);
    return true;
}

// @ 0x007F5490
int Obj::M5490()
{
    float x = *(float*)((char*)this + 8) * g_c1000;
    return (int)x;
}

// @ 0x007F54B0
void Obj::M54B0(int v)
{
    *(float*)((char*)this + 0x214) = (float)v * g_c001;
}

// @ 0x007F54E0
bool Obj::M54E0()
{
    if (*(char*)((char*)this + 0x244) == 0)
        return false;
    void* sub = (char*)this + 4;
    char r = ((FPC0)VTOBJ(sub)[0x28 / 4])(sub);
    if ((r & 1) == 0)
        return false;
    float f = 0.0f;
    if (*(int*)((char*)this + 0x250) == 0 && *(int*)((char*)this + 0x254) == 0) {
        void* q = (char*)this + 0x270;
        ((FV0)VTOBJ(q)[0x24 / 4])(q);
    } else {
        void* sw = (char*)this + 0x250;
        int64_t t = ((Callee*)sw)->i64();
        f = (float)t * *(float*)((char*)this + 0x264);
    }
    {
        void* sw = (char*)this + 0x250;
        ((Callee*)sw)->f();
    }
    if (f > g_c200)
        f = g_c10;
    void* q = (char*)this + 0x270;
    ((void(__thiscall*)(void*, int, int))VTOBJ(q)[0x3c / 4])(q, (int)f, 0);
    ((FV0)VTOBJ(sub)[0x98 / 4])(sub);
    return true;
}

// @ 0x007F55B0
void Obj::M55B0()
{
    void* sub = (char*)this + 4;
    int r = ((FPI0)VTOBJ(sub)[0x28 / 4])(sub);
    bool flag;
    if ((r & 1) != 0 && *(char*)((char*)this + 0x244) != 0)
        flag = true;
    else
        flag = false;
    ((void(__thiscall*)(void*, int, int))VTOBJ(sub)[0x7c / 4])(sub, 8, flag);
}

// @ 0x007F55F0
bool Obj::M55F0(void* ev)
{
    if (*(int*)((char*)ev + 8) == 0x16) {
        void* v = *(void**)((char*)ev + 0x18);
        ((FV0)VTOBJ(this)[0x98 / 4])(this);
        void* sub = (char*)this + 4;
        void* p = ((FPR0)VTOBJ(sub)[0xa8 / 4])(sub);
        ((void(__thiscall*)(void*, void*, int, int))VTOBJ(p)[0x18 / 4])(p, v, 0, 0);
        return true;
    }
    if (*(int*)((char*)ev + 8) == 0xe && *(int*)((char*)ev + 0xc) == 1 &&
        ((*(uint32_t*)((char*)ev + 0x14) ^ *(uint32_t*)((char*)ev + 0x10)) & 1) != 0) {
        ((FV0)VTOBJ(this)[0x9c / 4])(this);
    }
    return ((Callee*)this)->b(ev);
}

// @ 0x007F5660
bool Obj::M5660(void* p)
{
    bool r = ((Callee*)this)->b(p);
    ((FV0)VTOBJ(this)[0x98 / 4])(this);
    return r;
}

// @ 0x007F5690
void Obj::M5690()
{
    ((Callee*)this)->f();
    ((FV0)VTOBJ(this)[0x98 / 4])(this);
    ((FV0)VTOBJ(this)[0x9c / 4])(this);
}

// @ 0x007F56C0
void Obj::M56C0()
{
    void* q = (char*)this + 0x270;
    ((FV0)VTOBJ(q)[0x24 / 4])(q);
}

// @ 0x007F56E0
float Obj::M56E0()
{
    float f = 0.0f;
    if (*(char*)((char*)this + 0x34) == 0) {
        int n = *(int*)((char*)this + 0x20);
        if (n != 0)
            f = (float)*(int*)((char*)this + 0x18) / (float)n;
    }
    return f;
}

// @ 0x007F5710
bool Obj::M5710(float v)
{
    if (*(char*)((char*)this + 0x34) != 0)
        return false;
    int n = *(int*)((char*)this + 0x20);
    if (n == 0)
        return false;
    if (v < 0.0f)
        return false;
    if (v > g_c100)
        return false;
    int idx = (int)((float)(n - 1) * v * g_c001p);
    void* sub = (char*)this - 4;
    return ((bool(__thiscall*)(void*, int))VTOBJ(sub)[0x14 / 4])(sub, idx);
}

// @ 0x007F58E0
void Obj::M58E0()
{
    void* seq = (char*)this + 0x268;
    *(void**)((char*)this + 0) = &g_vt_01415298;
    *(void**)((char*)this + 4) = &g_vt_01415178;
    *(void**)((char*)this + 0x20c) = &g_vt_01415144;
    *(void**)((char*)this + 0x210) = &g_vt_0141513c;
    ((Callee*)seq)->f();
    void* p = *(void**)((char*)this + 0x248);
    if (p)
        ((FV0)VTOBJ(p)[4 / 4])(p);
    *(void**)((char*)this + 0x20c) = &g_vt_013eb938;
    ((Callee*)this)->f();
}

// @ 0x007F5990
bool Obj::M5990()
{
    void* p = *(void**)((char*)this + 0x248);
    if (p) {
        *(void**)((char*)this + 0x248) = 0;
        ((FV0)VTOBJ(p)[4 / 4])(p);
    }
    if (*(char*)((char*)this + 0x22c) != 0) {
        void* q = (char*)this + 0x270;
        void* f = VTOBJ(q)[0x14 / 4];
        *(char*)((char*)this + 0x22c) = 0;
        ((void(__thiscall*)(void*))f)(q);
        return ((WT*)this)->Dispose();
    }
    return true;
}

// @ 0x007F59E0
bool Obj::M59E0(void* obj, int a2, int a3, int a4)
{
    if (obj == 0)
        return false;
    void* old = *(void**)((char*)this + 0x248);
    if (obj != old) {
        ((FV0)VTOBJ(obj)[0])(obj);
        *(void**)((char*)this + 0x248) = obj;
        if (old)
            ((FV0)VTOBJ(old)[4 / 4])(old);
    }
    *(int*)((char*)this + 0x240) = a3;
    *(int*)((char*)this + 0x23c) = a2;
    *(int*)((char*)this + 0x230) = a4;
    void* f = VTOBJ(this)[0x98 / 4];
    *(int*)((char*)this + 0x234) = 0;
    *(int*)((char*)this + 0x238) = 0;
    ((void(__thiscall*)(void*))f)(this);
    return true;
}

// @ 0x007F5A60  (best-effort complete)
bool Obj::M5A60(void* ctx)
{
    void* rc = ((Callee*)ctx)->p(0);
    void* spr = *(void**)((char*)this + 0x248);
    if (spr != 0 && *(int*)((char*)this + 0x240) != 0 && *(int*)((char*)this + 0x23c) != 0) {
        int cols = *(int*)((char*)this + 0x23c);
        int rows = *(int*)((char*)this + 0x240);
        int idx = *(int*)((char*)this + 0x228);
        float rem = (float)(idx % rows);
        float quot = (float)(idx / rows);
        float invRows = g_c1f / (float)rows;
        float invCols = g_c1f / (float)cols;
        struct UV { float a, b, c, d; } uv;
        uv.a = rem * invRows;
        uv.d = (quot + g_c1f) * invCols;
        uv.b = quot * invCols;
        uv.c = (rem + g_c1f) * invRows;
        struct Rect { float x, y, w, h; } r;
        r.x = 0.0f;
        r.y = 0.0f;
        r.w = *(float*)((char*)this + 0x90) - *(float*)((char*)this + 0x88);
        r.h = *(float*)((char*)this + 0x94) - *(float*)((char*)this + 0x8c);
        ((void(__thiscall*)(void*, void*, void*, void*))VTOBJ(rc)[0x58 / 4])(rc, &r, spr, &uv);
    } else {
        float w = *(float*)((char*)this + 0x90) - *(float*)((char*)this + 0x88);
        float h = *(float*)((char*)this + 0x94) - *(float*)((char*)this + 0x8c);
        ((void(__thiscall*)(void*, float, float, float, float))VTOBJ(rc)[0x38 / 4])(
            rc, 0.0f, 0.0f, w, h);
    }
    ((Callee*)ctx)->f();
    return true;
}

// @ 0x007F5BD0
bool Obj::M5BD0(void* out, int, int)
{
    *(float*)out = *(float*)((char*)this + 0xc);
    *(float*)((char*)out + 4) = *(float*)((char*)this + 0x10);
    return true;
}

// @ 0x007F5C20
Obj* Obj::M5C20()
{
    ((Callee*)this)->f();
    *(void**)((char*)this + 0x20c) = &g_vt_01415144;
    *(void**)((char*)this + 0x210) = &g_vt_0141513c;
    *(int*)((char*)this + 0x220) = 1;
    *(int*)((char*)this + 0x228) = 1;
    *(int*)((char*)this + 0x23c) = 1;
    *(void**)((char*)this + 0) = &g_vt_01415298;
    *(void**)((char*)this + 4) = &g_vt_01415178;
    *(void**)((char*)this + 0x20c) = &g_vt_01415144;
    *(void**)((char*)this + 0x210) = &g_vt_0141513c;
    *(float*)((char*)this + 0x214) = g_c1f;
    *(int*)((char*)this + 0x218) = 0;
    *(int*)((char*)this + 0x21c) = 0;
    *(char*)((char*)this + 0x22c) = 0;
    *(int*)((char*)this + 0x230) = 0;
    *(int*)((char*)this + 0x234) = 0;
    *(int*)((char*)this + 0x238) = 0;
    *(int*)((char*)this + 0x240) = 0;
    *(int*)((char*)this + 0x248) = 0;
    ((Callee*)((char*)this + 0x250))->ctor2(4, 0);
    ((Callee*)((char*)this + 0x268))->ctor();
    return this;
}

// @ 0x007F5D00  (best-effort complete)
void Obj::M5D00()
{
    void* spr = *(void**)((char*)this + 0x248);
    int cols = *(int*)((char*)this + 0x238);
    int frames = *(int*)((char*)this + 0x230);
    int rows = *(int*)((char*)this + 0x240);
    int cw = *(int*)((char*)this + 0x234);
    int r = 1;
    if (spr == 0) {
        rows = 1;
        cw = 0x20;
        cols = 0x20;
        frames = 1;
    } else {
        if (cw < 1) {
            if (rows < 1)
                cw = *(int*)((char*)spr + 0x20);
            else
                cw = (int)((float)*(int*)((char*)spr + 0x1c) / (float)rows);
            if (cw < 1)
                cw = 1;
        }
        r = *(int*)((char*)spr + 0x1c) / cw;
        if (cols < 1) {
            if (*(int*)((char*)this + 0x23c) < 1)
                cols = *(int*)((char*)spr + 0x20);
            else
                cols = (int)((float)*(int*)((char*)spr + 0x20) / (float)*(int*)((char*)this + 0x23c));
            if (cols < 1)
                cols = 1;
        }
        int c = *(int*)((char*)spr + 0x20) / cols;
        if (frames < 1)
            frames = c * r;
    }
    *(int*)((char*)this + 0x234) = cw;
    *(int*)((char*)this + 0x238) = cols;
    *(int*)((char*)this + 0x240) = r;
    *(int*)((char*)this + 0x23c) = (*(int*)((char*)this + 0x23c));
    void* sub = (char*)this + 4;
    void* dp = ((FPR0)VTOBJ(sub)[0xa8 / 4])(sub);
    *(int*)((char*)this + 0x230) = frames;
    void* drawable = 0;
    if (dp != 0)
        drawable = ((FPRI)VTOBJ(dp)[0xc / 4])(dp, (int)0x26e0fbc);
    if (drawable == 0) {
        void* caller = FUN_009512c0();
        drawable = FUN_009512d0(0x14, 4, "UI/AnimatedIconDrawable", caller);
        if (drawable) {
            *(void**)((char*)drawable + 4) = &g_vt_013fa72c;
            *(void**)((char*)drawable + 8) = 0;
            *(void**)drawable = &g_vt_01415350;
            *(void**)((char*)drawable + 4) = &g_vt_01415338;
            *(float*)((char*)drawable + 0xc) = (float)*(int*)((char*)this + 0x234);
            *(float*)((char*)drawable + 0x10) = (float)*(int*)((char*)this + 0x238);
        } else {
            drawable = 0;
        }
        ((FVP)VTOBJ(sub)[0xb0 / 4])(sub, drawable);
    }
    *(float*)((char*)drawable + 0xc) = (float)*(int*)((char*)this + 0x234);
    *(float*)((char*)drawable + 0x10) = (float)*(int*)((char*)this + 0x238);
    void* q = (char*)this + 0x270;
    ((FV0)VTOBJ(q)[0x14 / 4])(q);
    *(int*)((char*)this + 0x228) = 0;
    char r2 = ((FPCV)VTOBJ(q)[0x10 / 4])(q, (char*)this + 0x20c);
    *(char*)((char*)this + 0x22c) = r2;
}

// @ 0x007F5FF0
void* Obj::M5FF0(char flags)
{
    *(void**)((char*)this + 0) = &g_vt_014153bc;
    void* p = *(void**)((char*)this + 0x84);
    if (p)
        ((FV0)VTOBJ(p)[4 / 4])(p);
    *(void**)((char*)this + 4) = &g_vt_013f6400;
    *(void**)((char*)this + 0xc) = &g_vt_013f63fc;
    void* q = *(void**)((char*)this + 0x10);
    if (q)
        ((FV0)VTOBJ(q)[4 / 4])(q);
    if ((flags & 1) != 0)
        deallocate(this);
    return this;
}

// --------------------------------------------------------------------------
// Free helpers
// --------------------------------------------------------------------------

// @ 0x007F5EB0
uint32_t Color_Lerp(uint32_t c1, uint32_t c2, float t)
{
    uint32_t a1 = c1 >> 0x18;
    uint32_t r1 = (c1 >> 0x10) & 0xff;
    uint32_t g1 = (c1 >> 8) & 0xff;
    uint32_t b1 = c1 & 0xff;
    uint32_t res;
    res = (uint32_t)(int)((float)(int)((c2 >> 0x10 & 0xff) - r1) * t + (float)(int)r1) & 0xff;
    res |= ((uint32_t)(int)((float)(int)((c2 >> 0x18) - a1) * t + (float)(int)a1) & 0xff) << 8;
    res = (res << 8) |
          ((uint32_t)(int)((float)(int)((c2 >> 8 & 0xff) - g1) * t + (float)(int)g1) & 0xff);
    res = (res << 8) |
          ((uint32_t)(int)((float)(int)((c2 & 0xff) - b1) * t + (float)(int)b1) & 0xff);
    return res;
}

// @ 0x007F5F70
void __stdcall DestroyRange(void* first, void* last)
{
    while (first < last) {
        ((void(__thiscall*)(void*, int))VTOBJ(first)[0])(first, 0);
        first = (char*)first + 0x8c;
    }
}

// @ 0x007F6040
void* __cdecl CreateTimeRamp(void* out, float a, float b, float c)
{
    *(void**)out = &g_vt_013f63fc;
    *(void**)((char*)out + 4) = 0;
    void* caller = FUN_009512c0();
    void* mem = FUN_009512d0(0x48, 4, "SPUICreateAnimationTimerRamp", caller);
    void* obj = mem ? ((Callee*)mem)->ctor() : 0;
    void* old = *(void**)((char*)out + 4);
    if (obj != old) {
        if (obj)
            ((FV0)VTOBJ(obj)[0])(obj);
        *(void**)((char*)out + 4) = obj;
        if (old)
            ((FV0)VTOBJ(old)[4 / 4])(old);
    }
    ((Callee*)obj)->f(a, b, c);
    return out;
}
// @ 0x007F60D0
void* __cdecl CreateTimeSmooth(void* out, float a2, float a3, float a4, float a5, float a6)
{
    *(void**)out = &g_vt_013f63fc;
    *(void**)((char*)out + 4) = 0;
    void* caller = FUN_009512c0();
    void* mem = FUN_009512d0(0x48, 4, "cSPUIBehaviorTimeFunctionSmoothRamp", caller);
    void* obj = mem ? ((Callee*)mem)->ctorff(a3, a4) : 0;
    void* old = *(void**)((char*)out + 4);
    if (obj != old) {
        if (obj)
            ((FV0)VTOBJ(obj)[0])(obj);
        *(void**)((char*)out + 4) = obj;
        if (old)
            ((FV0)VTOBJ(old)[4 / 4])(old);
    }
    ((Callee*)obj)->f(a2, a5, a6);
    return out;
}

// @ 0x007F6170
void* __cdecl CreateTimeDamped(void* out, float a2, float a3, float a4, float a5, float a6,
                               float a7, float a8)
{
    *(void**)out = &g_vt_013f63fc;
    *(void**)((char*)out + 4) = 0;
    void* caller = FUN_009512c0();
    void* mem = FUN_009512d0(0x50, 4, "cSPUIBehaviorTimeFunctionDampedPeriodic", caller);
    void* obj = mem ? ((Callee*)mem)->ctorf(a5) : 0;
    void* old = *(void**)((char*)out + 4);
    if (obj != old) {
        if (obj)
            ((FV0)VTOBJ(obj)[0])(obj);
        *(void**)((char*)out + 4) = obj;
        if (old)
            ((FV0)VTOBJ(old)[4 / 4])(old);
    }
    ((Callee*)obj)->f6(a2, a7, a8, a3, a4, a6);
    return out;
}

// --------------------------------------------------------------------------
// cSPUIAnimator
// --------------------------------------------------------------------------
struct AnimatorS {
    char pad0[4];
    char* mBegin;   // +4
    char* mEnd;     // +8
    char pad1[0xc];
    float mLast;    // +0x18
    bool  mActive;  // +0x1c
    bool RemoveAnimation(void* obj, int type);
    bool HasAnimation(void* obj, int type);
    bool Empty();
    void Update();
};

typedef void (__cdecl *AnimFn1)(void*, float, float, int, int);
typedef bool (__cdecl *AnimFn2)(void*, float, float, int, int);

// @ 0x007F6210
bool AnimatorS::RemoveAnimation(void* obj, int type)
{
    if (obj == 0)
        return false;
    uint32_t n = (uint32_t)((mEnd - mBegin) / 0x88);
    for (uint32_t i = 0; i < n; ++i) {
        char* e = mBegin + i * 0x88;
        if (*(void**)e == obj && (*(int*)(e + 4) == type || type == -1)) {
            ((AnimFn1)*(void**)(e + 0xc))(e + 8, 0.0f, 0.0f, 1, 0);
            void* r = *(void**)e;
            if (r) {
                *(void**)e = 0;
                ((FV0)VTOBJ(r)[4 / 4])(r);
            }
        }
    }
    return false;
}

// @ 0x007F62C0
bool AnimatorS::HasAnimation(void* obj, int type)
{
    if (obj == 0)
        return false;
    uint32_t n = (uint32_t)((mEnd - mBegin) / 0x88);
    for (uint32_t i = 0; i < n; ++i) {
        char* e = mBegin + i * 0x88;
        if (*(void**)e == obj && (*(int*)(e + 4) == type || type == -1))
            return true;
    }
    return false;
}

// @ 0x007F6340
bool AnimatorS::Empty()
{
    uint32_t n = (uint32_t)((mEnd - mBegin) / 0x88);
    for (uint32_t i = 0; i < n; ++i) {
        char* e = mBegin + i * 0x88;
        if (*(void**)e != 0) {
            void* p = *(void**)(e + 0x14);
            if (p == 0)
                return false;
            if (!((FPC0)VTOBJ(p)[0x3c / 4])(p))
                return false;
        }
    }
    return true;
}

// @ 0x007F63B0
void AnimatorS::Update()
{
    float now = SPUIHelpers_GetElapsedSeconds();
    if (mActive) {
        float dt = now - mLast;
        if (dt > g_c01)
            dt = g_c01;
        uint32_t n = (uint32_t)((mEnd - mBegin) / 0x88);
        bool any = false;
        for (uint32_t i = 0; i < n; ++i) {
            char* e = mBegin + i * 0x88;
            if (*(void**)e) {
                bool r = ((AnimFn2)*(void**)(e + 0xc))(e + 8, now, dt, 2, 0);
                if (!r) {
                    ((AnimFn1)*(void**)(e + 0xc))(e + 8, 0.0f, 0.0f, 1, 0);
                    void* p = *(void**)e;
                    if (p) {
                        *(void**)e = 0;
                        ((FV0)VTOBJ(p)[4 / 4])(p);
                    }
                } else {
                    any = true;
                }
            }
        }
        mActive = any;
    }
    mLast = now;
}
