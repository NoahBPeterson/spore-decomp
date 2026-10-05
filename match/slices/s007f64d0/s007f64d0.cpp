// UTFWin window-animation target functors and their factories,
// slice s007f64d0 (0x7F64D0..0x7F7525). /O2 /arch:SSE2 /fp:fast.
// The "target" object layout is: vtable(0), callback(4), vtable(8), animator(c),
// target object(0x10), start values(0x14..), captured values(0x1c..).
#include "types.h"

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

#define VT(p) (*(void***)(p))

typedef void   (__thiscall *FV0)(void*);
typedef void   (__thiscall *FVI)(void*, int);
typedef void   (__thiscall *FVF)(void*, float, float);
typedef void   (__thiscall *FVP)(void*, void*);
typedef void*  (__thiscall *FPR0)(void*);
typedef void*  (__thiscall *FPRI)(void*, int);
typedef char   (__thiscall *FPC0)(void*);
typedef float  (__thiscall *FPF0)(void*);
typedef uint32_t(__thiscall *FPU0)(void*);

void  __cdecl thunk_7fd140(void*);
void  __cdecl thunk_7fcff0(void*);
void  __cdecl FUN_805ef0(void* out, void* obj);
float __cdecl FUN_805290(void*);
float __cdecl FUN_8052c0(void*);
float __cdecl FUN_805200(void*);
float __cdecl FUN_805230(void*);
void* __cdecl FUN_805260(void*);
void  __cdecl FUN_8082f0(void*, float, float);
void  __cdecl FUN_808190(void*, float, float);
void  __cdecl FUN_808230(void*, void*);
uint32_t __cdecl Color_Lerp(uint32_t c1, uint32_t c2, float t);

extern void* g_vt_013f6400;
extern void* g_vt_013f63fc;
extern void* g_vt_014153bc;

struct Vector2 { float x, y; Vector2& operator=(const Vector2& o) { x = o.x; y = o.y; return *this; } };
struct Vector4 { float x, y, z, w;
    Vector4& operator=(const Vector4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; } };

// --------------------------------------------------------------------------
// callbacks
// --------------------------------------------------------------------------

// @ 0x007F64D0
bool F64D0(void* self, int a2, float a3, int phase)
{
    void* obj = *(void**)((char*)self + 0x10);
    if (obj == 0)
        return false;
    if (phase == 0) {
        thunk_7fd140(obj);
        struct { uint64_t pad; float x, y; } v;
        FUN_805ef0(&v.x, *(void**)((char*)self + 0x10));
        *(float*)((char*)self + 0x1c) = v.x;
        *(float*)((char*)self + 0x20) = v.y;
        return *(void**)((char*)self + 0x10) != 0;
    }
    if (phase == 2) {
        void* an = *(void**)((char*)self + 0xc);
        ((void(__thiscall*)(void*, float))VT(an)[0x2c / 4])(an, a3);
        float t = ((FPF0)VT(an)[0x18 / 4])(an);
        float y = (*(float*)((char*)self + 0x18) - *(float*)((char*)self + 0x20)) * t
                  + *(float*)((char*)self + 0x20);
        float x = (*(float*)((char*)self + 0x14) - *(float*)((char*)self + 0x1c)) * t
                  + *(float*)((char*)self + 0x1c);
        obj = *(void**)((char*)self + 0x10);
        ((FVF)VT(obj)[0x70 / 4])(obj, x, y);
        char r = ((FPC0)VT(an)[0x3c / 4])(an);
        return r == 0;
    }
    if (phase == 1) {
        thunk_7fcff0(obj);
        void* p = *(void**)((char*)self + 0x10);
        if (p) {
            *(void**)((char*)self + 0x10) = 0;
            ((FV0)VT(p)[4 / 4])(p);
        }
    }
    return *(void**)((char*)self + 0x10) != 0;
}

// @ 0x007F65F0
bool F65F0(void* self, int a2, float a3, int phase)
{
    void* obj = *(void**)((char*)self + 0x10);
    if (obj == 0)
        return false;
    if (phase == 0) {
        void* o = *(void**)((char*)self + 0x10);
        thunk_7fd140(o);
        o = *(void**)((char*)self + 0x10);
        *(float*)((char*)self + 0x1c) = FUN_805290(o);
        o = *(void**)((char*)self + 0x10);
        *(float*)((char*)self + 0x20) = FUN_8052c0(o);
        return *(void**)((char*)self + 0x10) != 0;
    }
    if (phase == 2) {
        void* an = *(void**)((char*)self + 0xc);
        ((void(__thiscall*)(void*, float))VT(an)[0x2c / 4])(an, a3);
        float t = ((FPF0)VT(an)[0x18 / 4])(an);
        float y = (*(float*)((char*)self + 0x18) - *(float*)((char*)self + 0x20)) * t
                  + *(float*)((char*)self + 0x20);
        float x = (*(float*)((char*)self + 0x14) - *(float*)((char*)self + 0x1c)) * t
                  + *(float*)((char*)self + 0x1c);
        FUN_8082f0(*(void**)((char*)self + 0x10), x, y);
        char r = ((FPC0)VT(an)[0x3c / 4])(an);
        return r == 0;
    }
    if (phase == 1) {
        thunk_7fcff0(obj);
        void* p = *(void**)((char*)self + 0x10);
        if (p) {
            *(void**)((char*)self + 0x10) = 0;
            ((FV0)VT(p)[4 / 4])(p);
        }
    }
    return *(void**)((char*)self + 0x10) != 0;
}

// @ 0x007F66F0
bool F66F0(void* self, int a2, float a3, int phase)
{
    void* obj = *(void**)((char*)self + 0x10);
    if (obj == 0)
        return false;
    if (phase == 0) {
        void* o = *(void**)((char*)self + 0x10);
        thunk_7fd140(o);
        o = *(void**)((char*)self + 0x10);
        *(float*)((char*)self + 0x18) = FUN_805200(o);
        o = *(void**)((char*)self + 0x10);
        *(float*)((char*)self + 0x20) = FUN_805230(o);
        return *(void**)((char*)self + 0x10) != 0;
    }
    if (phase == 2) {
        void* an = *(void**)((char*)self + 0xc);
        ((void(__thiscall*)(void*, float))VT(an)[0x2c / 4])(an, a3);
        float t = ((FPF0)VT(an)[0x18 / 4])(an);
        float y = (*(float*)((char*)self + 0x1c) - *(float*)((char*)self + 0x20)) * t
                  + *(float*)((char*)self + 0x20);
        float x = (*(float*)((char*)self + 0x14) - *(float*)((char*)self + 0x18)) * t
                  + *(float*)((char*)self + 0x18);
        FUN_808190(*(void**)((char*)self + 0x10), x, y);
        char r = ((FPC0)VT(an)[0x3c / 4])(an);
        return r == 0;
    }
    if (phase == 1) {
        thunk_7fcff0(obj);
        void* p = *(void**)((char*)self + 0x10);
        if (p) {
            *(void**)((char*)self + 0x10) = 0;
            ((FV0)VT(p)[4 / 4])(p);
        }
    }
    return *(void**)((char*)self + 0x10) != 0;
}

// @ 0x007F67F0
bool F67F0(void* self, int a2, float a3, int phase)
{
    void* obj = *(void**)((char*)self + 0x10);
    if (obj == 0)
        return false;
    if (phase == 0) {
        thunk_7fd140(obj);
        float* f = (float*)((FPR0)VT(*(void**)((char*)self + 0x10))[0x38 / 4])(
            *(void**)((char*)self + 0x10));
        *(float*)((char*)self + 0x1c) = f[2] - f[0];
        *(float*)((char*)self + 0x20) = f[3] - f[1];
        return *(void**)((char*)self + 0x10) != 0;
    }
    if (phase == 2) {
        void* an = *(void**)((char*)self + 0xc);
        ((void(__thiscall*)(void*, float))VT(an)[0x2c / 4])(an, a3);
        float t = ((FPF0)VT(an)[0x18 / 4])(an);
        float y = (*(float*)((char*)self + 0x18) - *(float*)((char*)self + 0x20)) * t
                  + *(float*)((char*)self + 0x20);
        float x = (*(float*)((char*)self + 0x14) - *(float*)((char*)self + 0x1c)) * t
                  + *(float*)((char*)self + 0x1c);
        obj = *(void**)((char*)self + 0x10);
        ((FVF)VT(obj)[0x74 / 4])(obj, x, y);
        char r = ((FPC0)VT(an)[0x3c / 4])(an);
        return r == 0;
    }
    if (phase == 1) {
        thunk_7fcff0(obj);
        void* p = *(void**)((char*)self + 0x10);
        if (p) {
            *(void**)((char*)self + 0x10) = 0;
            ((FV0)VT(p)[4 / 4])(p);
        }
    }
    return *(void**)((char*)self + 0x10) != 0;
}

// @ 0x007F6910
bool F6910(void* self, int a2, float a3, int phase)
{
    void* obj = *(void**)((char*)self + 0x10);
    if (obj == 0)
        return false;
    if (phase == 0) {
        thunk_7fd140(obj);
        float* f = (float*)((FPR0)VT(*(void**)((char*)self + 0x10))[0x38 / 4])(
            *(void**)((char*)self + 0x10));
        *(float*)((char*)self + 0x24) = f[0];
        *(float*)((char*)self + 0x28) = f[1];
        *(float*)((char*)self + 0x2c) = f[2];
        *(float*)((char*)self + 0x30) = f[3];
        return *(void**)((char*)self + 0x10) != 0;
    }
    if (phase == 2) {
        void* an = *(void**)((char*)self + 0xc);
        ((void(__thiscall*)(void*, float))VT(an)[0x2c / 4])(an, a3);
        float t = ((FPF0)VT(an)[0x18 / 4])(an);
        float v[4];
        v[0] = (*(float*)((char*)self + 0x14) - *(float*)((char*)self + 0x24)) * t
               + *(float*)((char*)self + 0x24);
        v[1] = (*(float*)((char*)self + 0x18) - *(float*)((char*)self + 0x28)) * t
               + *(float*)((char*)self + 0x28);
        v[2] = (*(float*)((char*)self + 0x1c) - *(float*)((char*)self + 0x2c)) * t
               + *(float*)((char*)self + 0x2c);
        v[3] = (*(float*)((char*)self + 0x20) - *(float*)((char*)self + 0x30)) * t
               + *(float*)((char*)self + 0x30);
        obj = *(void**)((char*)self + 0x10);
        ((FVP)VT(obj)[0x6c / 4])(obj, v);
        char r = ((FPC0)VT(an)[0x3c / 4])(an);
        return r == 0;
    }
    if (phase == 1) {
        thunk_7fcff0(obj);
        void* p = *(void**)((char*)self + 0x10);
        if (p) {
            *(void**)((char*)self + 0x10) = 0;
            ((FV0)VT(p)[4 / 4])(p);
        }
    }
    return *(void**)((char*)self + 0x10) != 0;
}

// @ 0x007F6A60
bool F6A60(void* self, int a2, float a3, int phase)
{
    void* obj = *(void**)((char*)self + 0x10);
    if (obj == 0)
        return false;
    if (phase == 0) {
        thunk_7fd140(obj);
        *(uint32_t*)((char*)self + 0x18) =
            ((FPU0)VT(*(void**)((char*)self + 0x10))[0x30 / 4])(*(void**)((char*)self + 0x10)) >> 0x18;
        return *(void**)((char*)self + 0x10) != 0;
    }
    if (phase == 2) {
        void* an = *(void**)((char*)self + 0xc);
        ((void(__thiscall*)(void*, float))VT(an)[0x2c / 4])(an, a3);
        float t = ((FPF0)VT(an)[0x18 / 4])(an);
        uint32_t cur = ((FPU0)VT(*(void**)((char*)self + 0x10))[0x30 / 4])(
            *(void**)((char*)self + 0x10));
        obj = *(void**)((char*)self + 0x10);
        uint32_t lerp = Color_Lerp(*(uint32_t*)((char*)self + 0x18),
                                   *(uint32_t*)((char*)self + 0x14), t);
        ((void(__thiscall*)(void*, uint32_t))VT(obj)[0x5c / 4])(
            obj, (lerp << 0x18) + (cur & 0xffffff));
        char r = ((FPC0)VT(an)[0x3c / 4])(an);
        return r == 0;
    }
    if (phase == 1) {
        thunk_7fcff0(obj);
        void* p = *(void**)((char*)self + 0x10);
        if (p) {
            *(void**)((char*)self + 0x10) = 0;
            ((FV0)VT(p)[4 / 4])(p);
        }
    }
    return *(void**)((char*)self + 0x10) != 0;
}

// @ 0x007F6B50
bool F6B50(void* self, int a2, float a3, int phase)
{
    void* obj = *(void**)((char*)self + 0x10);
    if (obj == 0)
        return false;
    if (phase == 0) {
        thunk_7fd140(obj);
        *(uint32_t*)((char*)self + 0x18) =
            ((FPU0)VT(*(void**)((char*)self + 0x10))[0x30 / 4])(*(void**)((char*)self + 0x10));
        return *(void**)((char*)self + 0x10) != 0;
    }
    if (phase == 2) {
        void* an = *(void**)((char*)self + 0xc);
        ((void(__thiscall*)(void*, float))VT(an)[0x2c / 4])(an, a3);
        float t = ((FPF0)VT(an)[0x18 / 4])(an);
        obj = *(void**)((char*)self + 0x10);
        uint32_t lerp = Color_Lerp(*(uint32_t*)((char*)self + 0x18),
                                   *(uint32_t*)((char*)self + 0x14), t);
        ((void(__thiscall*)(void*, uint32_t))VT(obj)[0x5c / 4])(obj, lerp);
        char r = ((FPC0)VT(an)[0x3c / 4])(an);
        return r == 0;
    }
    if (phase == 1) {
        thunk_7fcff0(obj);
        void* p = *(void**)((char*)self + 0x10);
        if (p) {
            *(void**)((char*)self + 0x10) = 0;
            ((FV0)VT(p)[4 / 4])(p);
        }
    }
    return *(void**)((char*)self + 0x10) != 0;
}

// @ 0x007F6C30
bool F6C30(void* self, int a2, float a3, int phase)
{
    void* obj = *(void**)((char*)self + 0x10);
    if (obj == 0)
        return false;
    if (phase == 0) {
        if (*(void**)((char*)self + 0x58) != 0) {
            char c = ((char(__cdecl*)(void*, void*, int))*(void**)((char*)self + 0x58))(
                obj, (char*)self + 0x14, 0);
            if (c == 0)
                return false;
        }
        if (*(short*)((char*)self + 0x3a) == 0) {
            ((void(__cdecl*)(void*, void*, void*))*(void**)((char*)self + 0x54))(
                *(void**)((char*)self + 0x10), (char*)self + 0x14, (char*)self + 0x28);
            return *(void**)((char*)self + 0x10) != 0;
        }
    } else if (phase == 2) {
        void* an = *(void**)((char*)self + 0xc);
        ((void(__thiscall*)(void*, float))VT(an)[0x2c / 4])(an, a3);
        float t = ((FPF0)VT(an)[0x18 / 4])(an);
        ((void(__cdecl*)(void*, void*, void*, void*, float))*(void**)((char*)self + 0x50))(
            *(void**)((char*)self + 0x10), (char*)self + 0x14, (char*)self + 0x28,
            (char*)self + 0x3c, t);
        char r = ((FPC0)VT(an)[0x3c / 4])(an);
        return r == 0;
    } else if (phase == 1) {
        if (*(void**)((char*)self + 0x58) != 0)
            ((void(__cdecl*)(void*, void*, int))*(void**)((char*)self + 0x58))(
                obj, (char*)self + 0x14, 1);
        void* p = *(void**)((char*)self + 0x10);
        if (p) {
            *(void**)((char*)self + 0x10) = 0;
            ((FV0)VT(p)[4 / 4])(p);
        }
    }
    return *(void**)((char*)self + 0x10) != 0;
}

// @ 0x007F6D20
bool F6D20(void* self, int a2, int a3, int phase)
{
    if (phase == 2)
        return (bool)((int(__cdecl*)(void*, void*, int))*(void**)((char*)self + 0x28))(
            *(void**)((char*)self + 0x10), (char*)self + 0x14, 2);
    return true;
}

// @ 0x007F6D90  (copy constructor for the target element)
void* F6D90(void* dst, void* src)
{
    void* p = *(void**)src;
    *(void**)dst = p;
    if (p)
        ((FV0)VT(p)[0])(p);
    *(void**)((char*)dst + 4) = *(void**)((char*)src + 4);
    *(void**)((char*)dst + 8) = &g_vt_013f6400;
    *(void**)((char*)dst + 0xc) = *(void**)((char*)src + 0xc);
    *(void**)((char*)dst + 0x10) = &g_vt_013f63fc;
    void* q = *(void**)((char*)src + 0x14);
    *(void**)((char*)dst + 0x14) = q;
    if (q)
        ((FV0)VT(q)[0])(q);
    for (int i = 0; i < 0x1c; ++i)
        ((uint32_t*)((char*)dst + 0x18))[i] = ((uint32_t*)((char*)src + 0x18))[i];
    return dst;
}

// @ 0x007F6DF0  (copy constructor for the window-animation target)
void* F6DF0(void* dst, void* src)
{
    *(void**)((char*)dst + 0) = &g_vt_014153bc;
    *(void**)((char*)dst + 4) = &g_vt_013f6400;
    *(void**)((char*)dst + 8) = *(void**)((char*)src + 8);
    *(void**)((char*)dst + 0xc) = &g_vt_013f63fc;
    void* p = *(void**)((char*)src + 0x10);
    *(void**)((char*)dst + 0x10) = p;
    if (p)
        ((FV0)VT(p)[0])(p);
    for (int i = 0; i < 0x1c; ++i)
        ((uint32_t*)((char*)dst + 0x14))[i] = ((uint32_t*)((char*)src + 0x14))[i];
    void* q = *(void**)((char*)src + 0x84);
    *(void**)((char*)dst + 0x84) = q;
    if (q)
        ((FV0)VT(q)[0])(q);
    *(void**)((char*)dst + 0x88) = *(void**)((char*)src + 0x88);
    return dst;
}

// @ 0x007F6EE0  (copy a range of elements forward)
void F6EE0(void* first, void* last, void* dst)
{
    while (first != last) {
        if (dst != 0) {
            void* p = *(void**)first;
            *(void**)dst = p;
            if (p)
                ((FV0)VT(p)[0])(p);
            *(void**)((char*)dst + 4) = *(void**)((char*)first + 4);
            *(void**)((char*)dst + 8) = &g_vt_013f6400;
            *(void**)((char*)dst + 0xc) = *(void**)((char*)first + 0xc);
            *(void**)((char*)dst + 0x10) = &g_vt_013f63fc;
            void* q = *(void**)((char*)first + 0x14);
            *(void**)((char*)dst + 0x14) = q;
            if (q)
                ((FV0)VT(q)[0])(q);
            for (int i = 0; i < 0x1c; ++i)
                ((uint32_t*)((char*)dst + 0x18))[i] = ((uint32_t*)((char*)first + 0x18))[i];
        }
        first = (char*)first + 0x88;
        dst = (char*)dst + 0x88;
    }
}

// @ 0x007F6F80  (destroy a range of elements)
void* F6F80(void* first, void* last, char* dst)
{
    if (first != last) {
        do {
            *(void**)((char*)first + 8) = &g_vt_013f6400;
            *(void**)((char*)first + 0x10) = &g_vt_013f63fc;
            void* q = *(void**)((char*)first + 0x14);
            if (q)
                ((FV0)VT(q)[4 / 4])(q);
            void* p = *(void**)first;
            if (p)
                ((FV0)VT(p)[4 / 4])(p);
            first = (char*)first + 0x88;
            dst += 0x88;
        } while (first != last);
    }
    return dst;
}

// @ 0x007F6FF0  (assignment operator)
void* F6FF0(void* self, void* src)
{
    *(void**)((char*)self + 4) = *(void**)((char*)src + 4);
    void* old = *(void**)((char*)self + 0xc);
    void* q = *(void**)((char*)src + 0xc);
    if (q != old) {
        if (q)
            ((FV0)VT(q)[0])(q);
        *(void**)((char*)self + 0xc) = q;
        if (old)
            ((FV0)VT(old)[4 / 4])(old);
    }
    for (int i = 0; i < 0x70; ++i)
        ((uint8_t*)((char*)self + 0x10))[i] = ((uint8_t*)((char*)src + 0x10))[i];
    return self;
}

// --------------------------------------------------------------------------
// factories
// --------------------------------------------------------------------------

// @ 0x007F7050
void* __cdecl SPUICreateWindowAnimationTargetPosition(void* out, void* target, float x, float y,
                                                      void* anim)
{
    void* a = *(void**)((char*)anim + 4);
    *(void**)((char*)out + 0) = &g_vt_013f6400;
    *(void**)((char*)out + 8) = &g_vt_013f63fc;
    *(void**)((char*)out + 0xc) = 0;
    _ReadWriteBarrier();
    {
        void* old = *(void**)((char*)out + 0xc);
        if (a != old) {
            if (a) ((FV0)VT(a)[0])(a);
            *(void**)((char*)out + 0xc) = a;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    void** slot = (void**)((char*)out + 0x10);
    *(void**)slot = 0;
    _ReadWriteBarrier();
    {
        void* old = *slot;
        if (target != old) {
            if (target) ((FV0)VT(target)[0])(target);
            *slot = target;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    *(float*)((char*)slot + 4) = x;
    *(float*)((char*)slot + 8) = y;
    *(void**)((char*)out + 4) = (void*)&F64D0;
    return out;
}

// @ 0x007F7100
void* __cdecl F7100(void* out, void* target, float x, float y, void* anim)
{
    void* a = *(void**)((char*)anim + 4);
    *(void**)((char*)out + 0) = &g_vt_013f6400;
    *(void**)((char*)out + 8) = &g_vt_013f63fc;
    *(void**)((char*)out + 0xc) = 0;
    _ReadWriteBarrier();
    {
        void* old = *(void**)((char*)out + 0xc);
        if (a != old) {
            if (a) ((FV0)VT(a)[0])(a);
            *(void**)((char*)out + 0xc) = a;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    void** slot = (void**)((char*)out + 0x10);
    *(void**)slot = 0;
    _ReadWriteBarrier();
    {
        void* old = *slot;
        if (target != old) {
            if (target) ((FV0)VT(target)[0])(target);
            *slot = target;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    *(float*)((char*)slot + 4) = x;
    *(float*)((char*)slot + 8) = y;
    *(void**)((char*)out + 4) = (void*)&F65F0;
    return out;
}

// @ 0x007F71B0
bool F71B0(void* self, int a2, float a3, int phase)
{
    void* obj = *(void**)((char*)self + 0x10);
    if (obj == 0)
        return false;
    if (phase == 0) {
        void* p = FUN_805260(obj);
        *(int*)((char*)self + 0x24) = *(int*)((char*)p + 0xc);
        return *(void**)((char*)self + 0x10) != 0;
    }
    if (phase == 2) {
        void* an = *(void**)((char*)self + 0xc);
        ((void(__thiscall*)(void*, float))VT(an)[0x2c / 4])(an, a3);
        float t = ((FPF0)VT(an)[0x18 / 4])(an);
        float v[4];
        v[0] = *(float*)((char*)self + 0x14);
        v[1] = *(float*)((char*)self + 0x18);
        v[2] = *(float*)((char*)self + 0x1c);
        v[3] = *(float*)((char*)self + 0x20) * t + *(float*)((char*)self + 0x24);
        FUN_808230(*(void**)((char*)self + 0x10), v);
        char r = ((FPC0)VT(an)[0x3c / 4])(an);
        return r == 0;
    }
    if (phase == 1) {
        *(void**)((char*)self + 0x10) = 0;
        if (obj)
            ((FV0)VT(obj)[4 / 4])(obj);
    }
    return *(void**)((char*)self + 0x10) != 0;
}

// @ 0x007F7290
void* __cdecl SPUICreateWindowAnimationRotation(void* out, void* target, int a, int b, int c,
                                                int d, void* anim)
{
    void* an = *(void**)((char*)anim + 4);
    *(void**)((char*)out + 0) = &g_vt_013f6400;
    *(void**)((char*)out + 8) = &g_vt_013f63fc;
    *(void**)((char*)out + 0xc) = 0;
    _ReadWriteBarrier();
    {
        void* old = *(void**)((char*)out + 0xc);
        if (an != old) {
            if (an) ((FV0)VT(an)[0])(an);
            *(void**)((char*)out + 0xc) = an;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    void** slot = (void**)((char*)out + 0x10);
    *(void**)slot = 0;
    _ReadWriteBarrier();
    {
        void* old = *slot;
        if (target != old) {
            if (target) ((FV0)VT(target)[0])(target);
            *slot = target;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    *(int*)((char*)slot + 4) = a;
    *(int*)((char*)slot + 8) = b;
    *(int*)((char*)slot + 0xc) = c;
    *(int*)((char*)slot + 0x10) = d;
    *(void**)((char*)out + 4) = (void*)&F71B0;
    return out;
}

// @ 0x007F7340
void* __cdecl SPUICreateWindowAnimationTargetScale(void* out, void* target, float f, void* anim)
{
    void* a = *(void**)((char*)anim + 4);
    *(void**)((char*)out + 0) = &g_vt_013f6400;
    *(void**)((char*)out + 8) = &g_vt_013f63fc;
    *(void**)((char*)out + 0xc) = 0;
    _ReadWriteBarrier();
    {
        void* old = *(void**)((char*)out + 0xc);
        if (a != old) {
            if (a) ((FV0)VT(a)[0])(a);
            *(void**)((char*)out + 0xc) = a;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    void** slot = (void**)((char*)out + 0x10);
    *(void**)slot = 0;
    _ReadWriteBarrier();
    {
        void* old = *slot;
        if (target != old) {
            if (target) ((FV0)VT(target)[0])(target);
            *slot = target;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    *(float*)((char*)slot + 4) = f;
    *(float*)((char*)slot + 0xc) = f;
    *(void**)((char*)out + 4) = (void*)&F66F0;
    return out;
}

// @ 0x007F73E0
void* __cdecl SPUICreateWindowAnimationTargetSize(void* out, void* target, float* size, void* anim)
{
    void* a = *(void**)((char*)anim + 4);
    *(void**)((char*)out + 0) = &g_vt_013f6400;
    *(void**)((char*)out + 8) = &g_vt_013f63fc;
    *(void**)((char*)out + 0xc) = 0;
    _ReadWriteBarrier();
    {
        void* old = *(void**)((char*)out + 0xc);
        if (a != old) {
            if (a) ((FV0)VT(a)[0])(a);
            *(void**)((char*)out + 0xc) = a;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    void** slot = (void**)((char*)out + 0x10);
    *(void**)slot = 0;
    _ReadWriteBarrier();
    {
        void* old = *slot;
        if (target != old) {
            if (target) ((FV0)VT(target)[0])(target);
            *slot = target;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    *(Vector2*)((char*)slot + 4) = *(Vector2*)size;
    *(void**)((char*)out + 4) = (void*)&F67F0;
    return out;
}

// @ 0x007F7480
void* __cdecl F7480(void* out, void* target, float* v, void* anim)
{
    void* a = *(void**)((char*)anim + 4);
    *(void**)((char*)out + 0) = &g_vt_013f6400;
    *(void**)((char*)out + 8) = &g_vt_013f63fc;
    *(void**)((char*)out + 0xc) = 0;
    _ReadWriteBarrier();
    {
        void* old = *(void**)((char*)out + 0xc);
        if (a != old) {
            if (a) ((FV0)VT(a)[0])(a);
            *(void**)((char*)out + 0xc) = a;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    void** slot = (void**)((char*)out + 0x10);
    *(void**)slot = 0;
    _ReadWriteBarrier();
    {
        void* old = *slot;
        if (target != old) {
            if (target) ((FV0)VT(target)[0])(target);
            *slot = target;
            if (old) ((FV0)VT(old)[4 / 4])(old);
        }
    }
    *(Vector4*)((char*)slot + 4) = *(Vector4*)v;
    *(void**)((char*)out + 4) = (void*)&F6910;
    return out;
}

// --------------------------------------------------------------------------
// cross-references
// --------------------------------------------------------------------------
uint32_t Color_Lerp(uint32_t c1, uint32_t c2, float t);
void* F6D90(void* dst, void* src);
void* F6DF0(void* dst, void* src);
void  F6EE0(void* first, void* last, void* dst);
void* F6F80(void* first, void* last, char* dst);
void* F6FF0(void* self, void* src);
