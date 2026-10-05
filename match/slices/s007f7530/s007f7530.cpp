// slice s007f7530: SPUI window/object animation targets (UI module).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// @ 0x007f7530 .. 0x007f8400
#include "types.h"
#include <new>
#include <string.h>

// ---------------------------------------------------------------------------
// Refcount helpers: AddRef is vtable byte 0, Release is vtable byte 4.
// ---------------------------------------------------------------------------
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

// Stub vtable symbols (addresses are masked in verification).
void* g_vtblAnim[1] = {0};
void* g_vtblTimer[1] = {0};

// ---------------------------------------------------------------------------
// Layouts
// ---------------------------------------------------------------------------
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

// Outer animation object (cSPUIAnimator::cAnimation, size 0x10 for our purposes).
struct AnimRaw {
    void* vf;                     // +0
    void* mActionFunc;            // +4
    void* timerVf;                // +8
    void* mpTimeFunction;         // +0xc
};

// ---------------------------------------------------------------------------
// target-data overlays at outer+0x10
// ---------------------------------------------------------------------------
struct TD_Shade {                 // cSPUIWindowAnimationTargetShade(Alpha), 0xc
    AutoRefCount<void> mpWin;     // +0
    uint32_t mTarget;             // +4
    uint32_t mFrom;               // +8
};

struct TD_Position {              // cSPUIWindowAnimationTargetPosition, 0x14
    AutoRefCount<void> mpWin;     // +0
    Point2DT mTargetPos;          // +4
    Point2DT mFromPos;            // +0xc
};

struct TD_Scale {                 // cSPUIWindowAnimationTargetScale, 0xc
    AutoRefCount<void> mpWin;     // +0
    float mTarget;                // +4
    float mFrom;                  // +8
};

struct TD_Size {                  // cSPUIWindowAnimationTargetSize, 0x14
    AutoRefCount<void> mpWin;     // +0
    Point2DT mTargetSize;         // +4
    Point2DT mFromSize;           // +0xc
};

struct TD_Rotation {              // cSPUIWindowAnimationRotation, 0x18
    AutoRefCount<void> mpWin;     // +0
    float mTarget[4];             // +4
    float mCurrent;               // +0x14
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

// The param passed as the timing function (cSPUIAnimationTimerInterpolation result).
struct InterpResult {             // matches cAnimationTimer
    void* vf;                     // +0
    void* mpTimeFunction;         // +4
};

// ---------------------------------------------------------------------------
// Callees (masked relocations).
// ---------------------------------------------------------------------------
extern "C" float __cdecl SPUIHelpers_GetElapsedSeconds();
extern "C" void* __cdecl FUN_007f6170(Point2DT* out, float a, int b, int c, float d, int e, int f, float g, int h);
extern "C" void* __cdecl FUN_007f60d0(InterpResult* out, float a, int b, int c, int d, int e);
extern "C" void* __cdecl FUN_007f6040(InterpResult* out, float a, int b, int c);

void FUN_007f6c30() {}
void FUN_007f6d20() {}
void FUN_007f6ff0_impl() {}
void TargetShade_Update() {}
void TargetFill_Update() {}

// ===========================================================================
// @ 0x007f7530
// ===========================================================================
AnimRaw* SPUICreateWindowAnimationTargetShadeAlpha(AnimRaw* p, void* win, uint32_t target, cAnimationTimer* t) {
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

// ===========================================================================
// @ 0x007f75d0
// ===========================================================================
AnimRaw* SPUICreateWindowAnimationTargetShade(AnimRaw* p, void* win, uint32_t target, cAnimationTimer* t) {
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

// ===========================================================================
// @ 0x007f7670  SPUICreateWindowAnimationTargetOscillatingFill
// ===========================================================================
AnimRaw* SPUICreateWindowAnimationTargetOscillatingFill(AnimRaw* p, void* win, uint32_t target, float duration, float from, float type) {
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

// ===========================================================================
// @ 0x007f7740  SPUICreateObjectAnimation
// ===========================================================================
AnimRaw* SPUICreateObjectAnimation(AnimRaw* p, void* obj, EA_Variant* ctx, uint32_t a, int b,
                                   cAnimationTimer* t, EA_Variant* vf, EA_Variant* vt, int e) {
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

// ===========================================================================
// @ 0x007f7830
// ===========================================================================
AnimRaw* FUN_007f7830(AnimRaw* p, uint32_t a2, void* obj, EA_Variant* val) {
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

// ===========================================================================
// @ 0x007f78c0  array destructor, stride 0x88 (cSPUIAnimator::cAnimationInfo)
// ===========================================================================
struct AInfo88 {
    void* mpObject;               // +0
    uint32_t mType;               // +4
    void* animVf;                 // +8
    void* animAction;             // +0xc
    void* timerVf;                // +0x10
    void* mpTimeFunction;         // +0x14
    char mData[0x88 - 0x18];      // +0x18
};

void __stdcall FUN_007f78c0(AInfo88* first, AInfo88* last) {
    while (first < last) {
        first->animVf = (void*)g_vtblAnim;
        first->timerVf = (void*)g_vtblTimer;
        if (first->mpTimeFunction) RcRel(first->mpTimeFunction);
        if (first->mpObject) RcRel(first->mpObject);
        first += 1;
    }
}

// ===========================================================================
// @ 0x007f7920  cSPUIAnimator::cAnimationInfo::operator=
// ===========================================================================
struct AnimBody { void CopyFrom(AnimBody* src); };

struct AnimInfo88B {
    void* mpObject;               // +0
    uint32_t mType;               // +4
    AnimBody anim;                // +8
    AnimInfo88B* operator=(AnimInfo88B* src);
};

AnimInfo88B* AnimInfo88B::operator=(AnimInfo88B* src) {
    RefAssign(&mpObject, src->mpObject);
    mType = src->mType;
    anim.CopyFrom(&src->anim);
    return this;
}

// ===========================================================================
// @ 0x007f7970  cSPUIAnimationSequence::cAnimInfo::operator=
// ===========================================================================
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

AInfo8c* AInfo8c::operator=(AInfo8c* src) {
    ((AnimBody*)((char*)this + 4))->CopyFrom((AnimBody*)((char*)src + 4));
    RefAssign(&mpObject, src->mpObject);
    mType = src->mType;
    return this;
}

// ===========================================================================
// @ 0x007f7a60  eastl::copy_impl<...>::do_copy<cAnimInfo*,cAnimInfo*>
// ===========================================================================
AInfo8c* do_copy_animinfo(AInfo8c* first, AInfo8c* last, AInfo8c* dst) {
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

// ===========================================================================
// @ 0x007f7b30  forward copy of cAnimationInfo (stride 0x88)
// ===========================================================================
AInfo88* copy_animinfo88(AInfo88* first, AInfo88* last, AInfo88* dst) {
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

// ===========================================================================
// @ 0x007f7c00  copy_backward of cAnimationInfo (stride 0x88)
// ===========================================================================
AInfo88* copy_backward_animinfo88(AInfo88* first, AInfo88* last, AInfo88* dst) {
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

// ===========================================================================
// @ 0x007f7ce0  fill-style forward copy of cAnimInfo (single source)
// ===========================================================================
AInfo8c* fill_copy_animinfo(AInfo8c* first, AInfo8c* last, AInfo8c* src) {
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

// ===========================================================================
// @ 0x007f7db0  fill-style backward copy of cAnimInfo (single source)
// ===========================================================================
AInfo8c* fill_copy_backward_animinfo(AInfo8c* first, AInfo8c* last, AInfo8c* src) {
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

// ===========================================================================
// @ 0x007f7eb0  SPUICreateAnimationTimerInterpolation
// ===========================================================================
InterpResult* SPUICreateAnimationTimerInterpolation(InterpResult* dest, float duration, float param3, int type) {
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

// ===========================================================================
// @ 0x007f80d0  SPUICreateWindowAnimationTargetPosition
// ===========================================================================
extern "C" AnimRaw* __cdecl Concrete_TargetPosition(AnimRaw* p, void* win, Point2DT pos, cAnimationTimer* t);
__forceinline Point2DT Pt(float x, float y) { Point2DT p; p.x = x; p.y = y; return p; }
AnimRaw* SPUICreateWindowAnimationTargetPosition(AnimRaw* p, void* win, float x, float y, float duration, float from, int type) {
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, from, type);
    Concrete_TargetPosition(p, win, Pt(x, y), &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}

// ===========================================================================
// @ 0x007f8140  SPUICreateWindowAnimationRotation
// ===========================================================================
extern "C" AnimRaw* __cdecl Concrete_Rotation(AnimRaw* p, void* win, float vx, float vy, float vz, float vw, cAnimationTimer* t);
AnimRaw* SPUICreateWindowAnimationRotation(AnimRaw* p, void* win, float vx, float vy, float vz, float vw, float duration, float from, int type) {
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, from, type);
    Concrete_Rotation(p, win, vx, vy, vz, vw, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}

// ===========================================================================
// @ 0x007f81d0  SPUICreateWindowAnimationTargetScale
// ===========================================================================
extern "C" AnimRaw* __cdecl Concrete_TargetScale(AnimRaw* p, void* win, float from, cAnimationTimer* t);
AnimRaw* SPUICreateWindowAnimationTargetScale(AnimRaw* p, void* win, float from, float duration, float base, int type) {
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, base, type);
    Concrete_TargetScale(p, win, from, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}

// ===========================================================================
// @ 0x007f8230  SPUICreateWindowAnimationTargetSize
// ===========================================================================
extern "C" AnimRaw* __cdecl Concrete_TargetSize(AnimRaw* p, void* win, uint32_t value, cAnimationTimer* t);
AnimRaw* SPUICreateWindowAnimationTargetSize(AnimRaw* p, void* win, uint32_t value, float duration, float from, int type) {
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, from, type);
    Concrete_TargetSize(p, win, value, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}

// ===========================================================================
// @ 0x007f8290  SPUICreateWindowAnimationTargetShadeAlpha
// ===========================================================================
AnimRaw* SPUICreateWindowAnimationTargetShadeAlphaW(AnimRaw* p, void* win, uint32_t target, float duration, float from, int type) {
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, from, type);
    SPUICreateWindowAnimationTargetShadeAlpha(p, win, target, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}

// ===========================================================================
// @ 0x007f82f0  SPUICreateWindowAnimationTargetShade
// ===========================================================================
AnimRaw* SPUICreateWindowAnimationTargetShadeW(AnimRaw* p, void* win, uint32_t target, float duration, float from, int type) {
    cAnimationTimer timer;
    SPUICreateAnimationTimerInterpolation((InterpResult*)&timer, duration, from, type);
    SPUICreateWindowAnimationTargetShade(p, win, target, &timer);
    if (timer.mpTimeFunction) RcRel(timer.mpTimeFunction);
    return p;
}

// ===========================================================================
// @ 0x007f8350  eastl::vector<cAnimInfo,sp_vector_allocator>::vector(const vector&)
// ===========================================================================
extern "C" void* __cdecl EASTL_allocator_allocate(int n, void* a, int b, int c, const char* file, int line);
extern "C" void* __cdecl FUN_007f6e60(AInfo8c** srcOut, AInfo8c* first, AInfo8c* last, AInfo8c* dst, AInfo8c** srcIn);

struct Vec8c { AInfo8c* mpBegin; AInfo8c* mpEnd; AInfo8c* mpCapacity; void* mAlloc; };

Vec8c* vector_cAnimInfo_ctor(Vec8c* this_, Vec8c* src) {
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

// ===========================================================================
// @ 0x007f83e0  UI::MissionCardAnimator::MissionCardAnimator
// ===========================================================================
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
MissionCardAnimator::MissionCardAnimator()
    : begin(0), end(0), cap(0), mTime(0.0f), mFlag(false) {}
void MissionCardAnimator::v1() {}

// ===========================================================================
// @ 0x007f8400  eastl::vector<cAnimInfo,sp_vector_allocator>::operator=
// ===========================================================================
extern "C" void __cdecl FUN_007f5f70(AInfo8c* first, AInfo8c* last);
extern "C" void* __cdecl FUN_007f79d0(int n, AInfo8c* first, AInfo8c* last);
extern "C" void __cdecl EASTL_allocator_deallocate(void* p);

Vec8c* vector_cAnimInfo_assign(Vec8c* this_, Vec8c* src) {
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
