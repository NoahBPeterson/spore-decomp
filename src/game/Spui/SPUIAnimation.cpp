// src/game/Spui/SPUIAnimation.cpp -- migrated from slice(s) s007f8540, s007f7530, s007f64d0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIAnimation.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIAnimator.h"
#include <new>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void _ReadWriteBarrier();
extern void* g_vt_013f6400;
extern void* g_vt_013f63fc;
extern void* g_vt_014153bc;
#pragma intrinsic(_ReadWriteBarrier)

// ---- items of slice s007f64d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _ReadWriteBarrier();
#define VT(p) (*(void***)(p))
typedef void   (__thiscall *FV0)(void*);
typedef void   (__thiscall *FVF)(void*, float, float);
typedef void   (__thiscall *FVP)(void*, void*);
typedef void*  (__thiscall *FPR0)(void*);
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
struct TargetElem {
    void* CopyFrom(void* src);
};
struct WindowAnimTarget {
    void* CopyFrom(void* src);
};
struct TargetAssign {
    void* Assign(void* src);
};
uint32_t Color_Lerp(uint32_t c1, uint32_t c2, float t);
void  F6EE0(void* first, void* last, void* dst);
void* F6F80(void* first, void* last, char* dst);
    void Color_Lerp(...); // 0x007f5eb0
// ---- items of slice s007f64d0 end

// ---- items of slice s007f7530 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl SPUIHelpers_GetElapsedSeconds();
extern "C" void* __cdecl EASTL_allocator_allocate(int n, void* a, int b, int c, const char* file, int line);
extern "C" void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
inline void RcAdd(void* p) { ((void(__thiscall*)(void*))(*(void**)(*(void**)p)))(p); }
inline void RcRel(void* p) { ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)p + 4)))(p); }
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    T* operator=(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) RcAdd(p);
            mpObject = p;
            if (old) RcRel(old);
        }
        return p;
    }
};
inline void RefAssign(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) RcAdd(p);
        *slot = p;
        if (old) RcRel(old);
    }
}
void* g_vtblAnim[1] = {0};
void* g_vtblTimer[1] = {0};
struct cAnimationTimer {          // cSPUIAnimator::cAnimationTimer, size 8
    void* vf;                     // +0
    void* mpTimeFunction;         // +4
};
struct EA_Variant {               // EA::Variant, size 0x14
    unsigned char mValue[0x10];   // +0
    unsigned short mFlags;        // +0x10
    unsigned short mTypeId;       // +0x12
    EA_Variant() { mFlags = 0; mTypeId = 0; }
    EA_Variant& operator=(const EA_Variant&);
};
struct Point2DT { float x; float y; };
struct AnimRaw {
    void* vf;                     // +0
    void* mActionFunc;            // +4
    void* timerVf;                // +8
    void* mpTimeFunction;         // +0xc
};
struct TD_Shade {                 // cSPUIWindowAnimationTargetShade(Alpha), 0xc
    AutoRefCount<void> mpWin;     // +0
    uint32_t mTarget;             // +4
    uint32_t mFrom;               // +8
};
struct TD_Object {                // cSPUIObjectAnimation, 0x4c
    AutoRefCount<void> mpObject;  // +0
    EA_Variant mContext;          // +4
    EA_Variant mValueFrom;        // +0x18
    EA_Variant mValueTo;          // +0x2c
    void* mpSetterFunc;           // +0x40
    void* mpGetterFunc;           // +0x44
    void* mpEventFunc;            // +0x48
};
struct InterpResult {             // matches cAnimationTimer
    void* vf;                     // +0
    void* mpTimeFunction;         // +4
};
extern "C" void* __cdecl FUN_007f6170(Point2DT* out, float a, int b, int c, float d, int e, int f, float g, int h);
extern "C" void* __cdecl FUN_007f60d0(InterpResult* out, float a, int b, int c, int d, int e);
extern "C" void* __cdecl FUN_007f6040(InterpResult* out, float a, int b, int c);
void FUN_007f6c30() {}
void FUN_007f6d20() {}
void TargetShade_Update() {}
void TargetFill_Update() {}
struct AInfo88 {
    void* mpObject;               // +0
    uint32_t mType;               // +4
    void* animVf;                 // +8
    void* animAction;             // +0xc
    void* timerVf;                // +0x10
    void* mpTimeFunction;         // +0x14
    char mData[0x88 - 0x18];      // +0x18
};
struct AnimBody { void CopyFrom(AnimBody* src); };
struct AnimInfo88B {
    void* mpObject;               // +0
    uint32_t mType;               // +4
    AnimBody anim;                // +8
    AnimInfo88B* operator=(AnimInfo88B* src);
};
struct AInfo8c {
    void* vf;                     // +0
    void* animVf;                 // +4
    void* animAction;             // +8
    void* timerVf;                // +0xc
    void* mpTimeFunction;         // +0x10
    char mData[0x70];             // +0x14
    void* mpObject;               // +0x84
    uint32_t mType;               // +0x88
    AInfo8c* operator=(AInfo8c* src);
};
extern "C" AnimRaw* __cdecl Concrete_Rotation(AnimRaw* p, void* win, float vx, float vy, float vz, float vw, cAnimationTimer* t);
extern "C" AnimRaw* __cdecl Concrete_TargetScale(AnimRaw* p, void* win, float from, cAnimationTimer* t);
extern "C" AnimRaw* __cdecl Concrete_TargetSize(AnimRaw* p, void* win, uint32_t value, cAnimationTimer* t);
extern "C" void* __cdecl FUN_007f6e60(AInfo8c** srcOut, AInfo8c* first, AInfo8c* last, AInfo8c* dst, AInfo8c** srcIn);
struct Vec8c { AInfo8c* mpBegin; AInfo8c* mpEnd; AInfo8c* mpCapacity; void* mAlloc;
    Vec8c* ctor_copy(Vec8c* src); Vec8c* assign(Vec8c* src); };
struct MissionCardAnimator {
    void*   begin;     // +4
    void*   end;       // +8
    void*   cap;       // +0xc
    int     pad10;     // +0x10
    int     pad14;     // +0x14
    float   mTime;     // +0x18
    bool    mFlag;     // +0x1c
    MissionCardAnimator();
    virtual void v1();
};
void MissionCardAnimator::v1() {}
extern "C" void __cdecl FUN_007f5f70(AInfo8c* first, AInfo8c* last);
extern "C" void* __cdecl FUN_007f79d0(int n, AInfo8c* first, AInfo8c* last);
// ---- items of slice s007f7530 end

// ---- items of slice s007f8540 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl eastl_alloc(int n, void* a, int b, int c, const char* file, int line);
extern "C" void  __cdecl eastl_free(void* p);
extern "C" void  __cdecl anim_copy_body(void* dst, void* src);     // FUN_007f6ff0
struct AInfo8c_s007f_8540 {                 // cSPUIAnimationSequence::cAnimInfo, size 0x8c
    void* vf;                    // +0
    void* animVf;                // +4
    void* animAction;            // +8
    void* timerVf;               // +0xc
    void* mpTimeFunction;        // +0x10
    char mData[0x70];            // +0x14
    void* mpObject;              // +0x84
    uint32_t mType;              // +0x88
};
extern "C" void* __cdecl vec_uninit_copy(void** srcOut, AInfo8c_s007f_8540* first, AInfo8c_s007f_8540* last, AInfo8c_s007f_8540* dst, void** srcIn);
extern "C" void  __cdecl vec_clear_range(AInfo8c_s007f_8540* first, AInfo8c_s007f_8540* last);
extern "C" AInfo8c_s007f_8540* __cdecl vec_move_backward(AInfo8c_s007f_8540* first, AInfo8c_s007f_8540* last, AInfo8c_s007f_8540* dst);
extern "C" void  __cdecl vec_fill(AInfo8c_s007f_8540* first, AInfo8c_s007f_8540* last, AInfo8c_s007f_8540* src);
extern "C" AInfo8c_s007f_8540* __cdecl cAnimInfo_ctor(AInfo8c_s007f_8540* p);             // FUN_007f8970
struct Vec8c_s007f_8540 {
    AInfo8c_s007f_8540* mpBegin;            // +0
    AInfo8c_s007f_8540* mpEnd;              // +4
    AInfo8c_s007f_8540* mpCapacity;         // +8
    void*    mAlloc;             // +0xc

    int size() const { return (int)((char*)mpEnd - (char*)mpBegin) / 0x8c; }
    int capacity() const { return (int)((char*)mpCapacity - (char*)mpBegin) / 0x8c; }

    AInfo8c_s007f_8540* erase(AInfo8c_s007f_8540* first, AInfo8c_s007f_8540* last);
    AInfo8c_s007f_8540* erase(AInfo8c_s007f_8540* pos);
};
// ---- items of slice s007f8540 end

// @ 0x007f64d0
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






// @ 0x007f65f0
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






// @ 0x007f66f0
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






// @ 0x007f67f0
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






// @ 0x007f6910
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






// @ 0x007f6a60
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






// @ 0x007f6b50
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






// @ 0x007f6c30
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






// @ 0x007f6d20
bool F6D20(void* self, int a2, int a3, int phase)
{
    if (phase == 2)
        return (bool)((int(__cdecl*)(void*, void*, int))*(void**)((char*)self + 0x28))(
            *(void**)((char*)self + 0x10), (char*)self + 0x14, 2);
    return true;
}






// @ 0x007f6d90
void* TargetElem::CopyFrom(void* src)
{
    void* dst = this;
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






// @ 0x007f6df0
void* WindowAnimTarget::CopyFrom(void* src)
{
    void* dst = this;
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






// @ 0x007f6ee0
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






// @ 0x007f6f80
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






// @ 0x007f6ff0
void* TargetAssign::Assign(void* src)
{
    void* self = this;
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






// @ 0x007f7050
void* __cdecl SPUICreateWindowAnimationTargetPosition(void* out, void* target, float x, float y, void* anim)
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






// @ 0x007f7100
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






// @ 0x007f71b0
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






// @ 0x007f7290
void* __cdecl SPUICreateWindowAnimationRotation(void* out, void* target, int a, int b, int c, int d, void* anim)
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






// @ 0x007f7340
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






// @ 0x007f73e0
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






// @ 0x007f7480
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





// @ 0x007f7530
AnimRaw* SPUICreateWindowAnimationTargetShadeAlpha(AnimRaw* p, void* win, uint32_t target, cAnimationTimer* t)
{
    p->vf = (void*)g_vtblAnim;
    p->timerVf = (void*)g_vtblTimer;
    p->mpTimeFunction = 0;
    RefAssign(&p->mpTimeFunction, t->mpTimeFunction);
    TD_Shade* d = new ((void*)((char*)p + 0x10)) TD_Shade();
    d->mpWin = win;
    d->mTarget = target;
    p->mActionFunc = (void*)&TargetShade_Update;
    return p;
}





// @ 0x007f75d0
AnimRaw* SPUICreateWindowAnimationTargetShade(AnimRaw* p, void* win, uint32_t target, cAnimationTimer* t)
{
    p->vf = (void*)g_vtblAnim;
    p->timerVf = (void*)g_vtblTimer;
    p->mpTimeFunction = 0;
    RefAssign(&p->mpTimeFunction, t->mpTimeFunction);
    TD_Shade* d = new ((void*)((char*)p + 0x10)) TD_Shade();
    d->mpWin = win;
    d->mTarget = target;
    p->mActionFunc = (void*)&TargetFill_Update;
    return p;
}





// @ 0x007f7670
AnimRaw* SPUICreateWindowAnimationTargetOscillatingFill(AnimRaw* p, void* win, uint32_t target, float duration, float from, float type)
{
    float elapsed = SPUIHelpers_GetElapsedSeconds();
    float remain = duration - elapsed;
    float ratio = 0.0f;
    float total = from;
    if (0.001f < duration && 0.001f < remain && 0.001f < from) {
        total = remain + from;
        ratio = remain / total;
    }
    InterpResult interp;
    FUN_007f6170((Point2DT*)&interp, total, 0xbf800000, 1, 1, ratio, 0, 0.0f, 0);
    SPUICreateWindowAnimationTargetShade(p, win, target, (cAnimationTimer*)&interp);
    if (interp.mpTimeFunction) RcRel(interp.mpTimeFunction);
    return p;
}





// @ 0x007f7740
AnimRaw* SPUICreateObjectAnimation(AnimRaw* p, void* obj, EA_Variant* ctx, uint32_t a, int b, cAnimationTimer* t, EA_Variant* vf, EA_Variant* vt, int e)
{
    p->vf = (void*)g_vtblAnim;
    p->timerVf = (void*)g_vtblTimer;
    p->mpTimeFunction = 0;
    RefAssign(&p->mpTimeFunction, t->mpTimeFunction);
    TD_Object* d = new ((void*)((char*)p + 0x10)) TD_Object();
    d->mpObject = obj;
    d->mValueTo = *ctx;
    d->mValueFrom = *vt;
    d->mContext = *vf;
    d->mpSetterFunc = (void*)a;
    d->mpGetterFunc = (void*)b;
    d->mpEventFunc = (void*)e;
    p->mActionFunc = (void*)&FUN_007f6c30;
    return p;
}





// @ 0x007f7830
AnimRaw* FUN_007f7830(AnimRaw* p, uint32_t a2, void* obj, EA_Variant* val)
{
    p->vf = (void*)g_vtblAnim;
    p->timerVf = (void*)g_vtblTimer;
    p->mpTimeFunction = 0;
    struct TD7830 {
        AutoRefCount<void> mpObject;  // +0
        EA_Variant mValue;            // +4
        uint32_t field18;             // +0x18
    };
    TD7830* d = new ((void*)((char*)p + 0x10)) TD7830();
    d->field18 = a2;
    d->mpObject = obj;
    d->mValue = *val;
    p->mActionFunc = (void*)&FUN_007f6d20;
    return p;
}





// @ 0x007f78c0
void __stdcall FUN_007f78c0(AInfo88* first, AInfo88* last)
{
    while (first < last) {
        first->animVf = (void*)g_vtblAnim;
        first->timerVf = (void*)g_vtblTimer;
        if (first->mpTimeFunction) RcRel(first->mpTimeFunction);
        if (first->mpObject) RcRel(first->mpObject);
        first += 1;
    }
}





// @ 0x007f7920
AnimInfo88B* AnimInfo88B::operator=(AnimInfo88B* src)
{
    RefAssign(&mpObject, src->mpObject);
    mType = src->mType;
    anim.CopyFrom(&src->anim);
    return this;
}





// @ 0x007f7970
AInfo8c* AInfo8c::operator=(AInfo8c* src)
{
    ((AnimBody*)((char*)this + 4))->CopyFrom((AnimBody*)((char*)src + 4));
    RefAssign(&mpObject, src->mpObject);
    mType = src->mType;
    return this;
}





// @ 0x007f7a60
AInfo8c* do_copy_animinfo(AInfo8c* first, AInfo8c* last, AInfo8c* dst)
{
    while (first != last) {
        dst->animAction = first->animAction;
        RefAssign(&dst->mpTimeFunction, first->mpTimeFunction);
        memcpy(dst->mData, first->mData, 0x70);
        RefAssign(&dst->mpObject, first->mpObject);
        dst->mType = first->mType;
        first += 1;
        dst += 1;
    }
    return dst;
}





// @ 0x007f7b30
AInfo88* copy_animinfo88(AInfo88* first, AInfo88* last, AInfo88* dst)
{
    while (first != last) {
        RefAssign(&dst->mpObject, first->mpObject);
        dst->mType = first->mType;
        dst->animAction = first->animAction;
        RefAssign(&dst->mpTimeFunction, first->mpTimeFunction);
        memcpy(dst->mData, first->mData, 0x88 - 0x18);
        first += 1;
        dst += 1;
    }
    return dst;
}





// @ 0x007f7c00
AInfo88* copy_backward_animinfo88(AInfo88* first, AInfo88* last, AInfo88* dst)
{
    while (first != last) {
        --last;
        --dst;
        RefAssign(&dst->mpObject, last->mpObject);
        dst->mType = last->mType;
        dst->animAction = last->animAction;
        RefAssign(&dst->mpTimeFunction, last->mpTimeFunction);
        memcpy(dst->mData, last->mData, 0x88 - 0x18);
    }
    return dst;
}





// @ 0x007f7ce0
AInfo8c* fill_copy_animinfo(AInfo8c* first, AInfo8c* last, AInfo8c* src)
{
    while (first != last) {
        first->animAction = src->animAction;
        RefAssign(&first->mpTimeFunction, src->mpTimeFunction);
        memcpy(first->mData, src->mData, 0x70);
        RefAssign(&first->mpObject, src->mpObject);
        first->mType = src->mType;
        first += 1;
    }
    return first;
}





// @ 0x007f7db0
AInfo8c* fill_copy_backward_animinfo(AInfo8c* first, AInfo8c* last, AInfo8c* src)
{
    while (last != first) {
        --last;
        last->animAction = src->animAction;
        RefAssign(&last->mpTimeFunction, src->mpTimeFunction);
        memcpy(last->mData, src->mData, 0x70);
        RefAssign(&last->mpObject, src->mpObject);
        last->mType = src->mType;
    }
    return last;
}





// @ 0x007f7eb0
InterpResult* SPUICreateAnimationTimerInterpolation(InterpResult* dest, float duration, float param3, int type)
{
    float elapsed = SPUIHelpers_GetElapsedSeconds();
    float remain = duration - elapsed;
    float ratio = 0.0f;
    float total = param3;
    if (0.001f < duration && 0.001f < remain && 0.001f < param3) {
        total = remain + param3;
        ratio = remain / total;
    }
    dest->vf = (void*)g_vtblTimer;
    dest->mpTimeFunction = 0;
    if (type == 1) {
        InterpResult tmp;
        FUN_007f60d0(&tmp, total, 0x3f000000, 0, (int)ratio, 0);
        RefAssign(&dest->mpTimeFunction, tmp.mpTimeFunction);
    } else if (type == 2) {
        InterpResult tmp;
        FUN_007f60d0(&tmp, total, 0, 0x3f000000, (int)ratio, 0);
        RefAssign(&dest->mpTimeFunction, tmp.mpTimeFunction);
    } else if (type == 3) {
        InterpResult tmp;
        FUN_007f60d0(&tmp, total, 0x3f000000, 0x3f000000, (int)ratio, 0);
        RefAssign(&dest->mpTimeFunction, tmp.mpTimeFunction);
    } else {
        InterpResult tmp;
        FUN_007f6040(&tmp, total, (int)ratio, 0);
        RefAssign(&dest->mpTimeFunction, tmp.mpTimeFunction);
    }
    if (dest->mpTimeFunction) RcRel(dest->mpTimeFunction);
    return dest;
}





// @ 0x007f80d0
__forceinline Point2DT Pt(float x, float y)
{ Point2DT p; p.x = x; p.y = y; return p; }





// @ 0x007f8140
AnimRaw* SPUICreateWindowAnimationRotation(AnimRaw* p, void* win, float vx, float vy, float vz, float vw, float duration, float from, int type)
{
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, from, type);
    Concrete_Rotation(p, win, vx, vy, vz, vw, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}





// @ 0x007f81d0
AnimRaw* SPUICreateWindowAnimationTargetScale(AnimRaw* p, void* win, float from, float duration, float base, int type)
{
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, base, type);
    Concrete_TargetScale(p, win, from, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}





// @ 0x007f8230
AnimRaw* SPUICreateWindowAnimationTargetSize(AnimRaw* p, void* win, uint32_t value, float duration, float from, int type)
{
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, from, type);
    Concrete_TargetSize(p, win, value, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}





// @ 0x007f8290
AnimRaw* SPUICreateWindowAnimationTargetShadeAlphaW(AnimRaw* p, void* win, uint32_t target, float duration, float from, int type)
{
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, from, type);
    SPUICreateWindowAnimationTargetShadeAlpha(p, win, target, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}





// @ 0x007f82f0
AnimRaw* SPUICreateWindowAnimationTargetShadeW(AnimRaw* p, void* win, uint32_t target, float duration, float from, int type)
{
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, from, type);
    SPUICreateWindowAnimationTargetShade(p, win, target, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}





// @ 0x007f8350
Vec8c* Vec8c::ctor_copy(Vec8c* src)
{
    Vec8c* this_ = this;
    int n = (int)((char*)src->mpEnd - (char*)src->mpBegin) / 0x8c;
    AInfo8c* mem = 0;
    if (n != 0) {
        mem = (AInfo8c*)EASTL_allocator_allocate(n * 0x8c, (void*)g_vtblAnim, 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    this_->mpBegin = mem;
    this_->mpEnd = mem;
    this_->mpCapacity = (AInfo8c*)((char*)mem + n * 0x8c);
    FUN_007f6e60(&src->mpBegin, src->mpBegin, src->mpEnd, mem, &src->mpBegin);
    this_->mpEnd = src->mpBegin;
    return this_;
}





// @ 0x007f83e0
MissionCardAnimator::MissionCardAnimator()
: begin(0), end(0), cap(0), mTime(0.0f), mFlag(false) {}





// @ 0x007f8400
Vec8c* Vec8c::assign(Vec8c* src)
{
    Vec8c* this_ = this;
    if (src != this_) {
        int n = (int)((char*)src->mpEnd - (char*)src->mpBegin) / 0x8c;
        int cap = (int)((char*)this_->mpCapacity - (char*)this_->mpBegin) / 0x8c;
        if (cap < n) {
            AInfo8c* mem = (AInfo8c*)FUN_007f79d0(n, src->mpBegin, src->mpEnd);
            FUN_007f5f70(this_->mpBegin, this_->mpEnd);
            if (this_->mpBegin != 0 && *(int*)((char*)this_->mpBegin - 4) != 0) {
                EASTL_allocator_deallocate(this_->mpBegin);
            }
            this_->mpBegin = mem;
            this_->mpCapacity = (AInfo8c*)((char*)mem + n * 0x8c);
        } else {
            int have = (int)((char*)this_->mpEnd - (char*)this_->mpBegin) / 0x8c;
            if (have < n) {
                do_copy_animinfo(src->mpBegin, src->mpBegin + have, this_->mpBegin);
                FUN_007f6e60(&src->mpBegin, this_->mpBegin + have, src->mpEnd, this_->mpEnd, &src->mpBegin);
            } else {
                AInfo8c* r = do_copy_animinfo(src->mpBegin, src->mpEnd, this_->mpBegin);
                FUN_007f5f70(r, this_->mpEnd);
            }
        }
        this_->mpEnd = (AInfo8c*)((char*)this_->mpBegin + n * 0x8c);
    }
    return this_;
}




// @ 0x007f85b0
static void vec_insert_n(Vec8c_s007f_8540* v, AInfo8c_s007f_8540* pos, uint32_t n, const AInfo8c_s007f_8540* value)
{
    if ((uint32_t)v->capacity() < n) {
        int oldSize = v->size();
        uint32_t newCap = (oldSize == 0) ? 1u : (uint32_t)oldSize * 2u;
        if (oldSize + n > (int)newCap) newCap = (uint32_t)oldSize + n;
        AInfo8c_s007f_8540* mem = 0;
        if (newCap != 0)
            mem = (AInfo8c_s007f_8540*)eastl_alloc((int)(newCap * 0x8c), v->mAlloc, 0, 0, "alloc", 0xd1);
        AInfo8c_s007f_8540* oldBegin = v->mpBegin;
        void* mid = vec_uninit_copy((void**)&oldBegin, oldBegin, pos, mem, &v->mAlloc);
        vec_clear_range(oldBegin, pos);
        AInfo8c_s007f_8540* p = (AInfo8c_s007f_8540*)mid;
        vec_fill(p, p + n, (AInfo8c_s007f_8540*)value);
        AInfo8c_s007f_8540* tail = (AInfo8c_s007f_8540*)((char*)p + n * 0x8c);
        void* endp = vec_uninit_copy((void**)&pos, pos, (AInfo8c_s007f_8540*)((char*)oldBegin + (oldSize) * 0), tail, &v->mAlloc);
        if (oldBegin != 0 && *(int*)((char*)oldBegin - 4) != 0) eastl_free(oldBegin);
        v->mpBegin = mem;
        v->mpEnd = (AInfo8c_s007f_8540*)endp;
        v->mpCapacity = (AInfo8c_s007f_8540*)((char*)mem + newCap * 0x8c);
    } else if (n != 0) {
        AInfo8c_s007f_8540* oldEnd = v->mpEnd;
        uint32_t tail = (uint32_t)((char*)v->mpEnd - (char*)pos) / 0x8c;
        if (n < tail) {
            AInfo8c_s007f_8540* mid = (AInfo8c_s007f_8540*)((char*)v->mpEnd - n * 0x8c);
            vec_uninit_copy((void**)&v->mpEnd, mid, v->mpEnd, v->mpEnd, &v->mAlloc);
            v->mpEnd = (AInfo8c_s007f_8540*)((char*)v->mpEnd + n * 0x8c);
            vec_move_backward(pos, mid, oldEnd);
            vec_fill(pos, (AInfo8c_s007f_8540*)((char*)pos + n * 0x8c), (AInfo8c_s007f_8540*)value);
        } else {
            AInfo8c_s007f_8540* extra = (AInfo8c_s007f_8540*)((char*)v->mpEnd + (n - tail) * 0x8c);
            vec_fill(v->mpEnd, extra, (AInfo8c_s007f_8540*)value);
            v->mpEnd = extra;
            vec_uninit_copy((void**)&v->mpEnd, pos, oldEnd, v->mpEnd, &v->mAlloc);
            v->mpEnd = (AInfo8c_s007f_8540*)((char*)v->mpEnd + tail * 0x8c);
        }
        vec_fill(pos, oldEnd, (AInfo8c_s007f_8540*)value);
    }
}

// @ 0x007f89f0
static AInfo8c_s007f_8540* vec_insert_one(Vec8c_s007f_8540* v, AInfo8c_s007f_8540* pos, const AInfo8c_s007f_8540* value)
{
    if (v->mpEnd != v->mpCapacity) {
        AInfo8c_s007f_8540* oldEnd = v->mpEnd;
        vec_move_backward(pos, oldEnd - 1, oldEnd);
        if (oldEnd - 1 >= pos) {
            AInfo8c_s007f_8540* t = pos;
            t->animAction = value->animAction;
            /* timer/refcount/data copy through the element assignment */
            anim_copy_body(t, (void*)value);
        }
        v->mpEnd = oldEnd + 1;
        return pos;
    }
    int oldSize = v->size();
    uint32_t newCap = (oldSize == 0) ? 1u : (uint32_t)oldSize * 2u;
    AInfo8c_s007f_8540* mem = 0;
    if (newCap != 0) mem = (AInfo8c_s007f_8540*)eastl_alloc((int)(newCap * 0x8c), v->mAlloc, 0, 0, "alloc", 0xd1);
    AInfo8c_s007f_8540* oldBegin = v->mpBegin;
    void* mid = vec_uninit_copy((void**)&oldBegin, oldBegin, pos, mem, &v->mAlloc);
    AInfo8c_s007f_8540* p = (AInfo8c_s007f_8540*)mid;
    if (p != 0) anim_copy_body(p, (void*)value);
    void* endp = vec_uninit_copy((void**)&v->mpEnd, pos, v->mpEnd, p + 1, &v->mAlloc);
    if (oldBegin != 0 && *(int*)((char*)oldBegin - 4) != 0) eastl_free(oldBegin);
    v->mpBegin = mem;
    v->mpEnd = (AInfo8c_s007f_8540*)endp + 1;
    v->mpCapacity = (AInfo8c_s007f_8540*)((char*)mem + newCap * 0x8c);
    return p;
}

// @ 0x007f8b50
static void vec_resize(Vec8c_s007f_8540* v, uint32_t n)
{
    AInfo8c_s007f_8540* first = v->mpBegin;
    AInfo8c_s007f_8540* end = v->mpEnd;
    if ((uint32_t)((char*)end - (char*)first) / 0x8c < n) {
        AInfo8c_s007f_8540 tmp;
        memset(&tmp, 0, sizeof(tmp));
        cAnimInfo_ctor(&tmp);
        vec_insert_n(v, end, n - (uint32_t)((char*)end - (char*)first) / 0x8c, &tmp);
    } else {
        v->erase((AInfo8c_s007f_8540*)((char*)first + n * 0x8c), end);
    }
}
