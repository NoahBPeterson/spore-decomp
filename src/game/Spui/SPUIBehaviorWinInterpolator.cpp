// src/game/Spui/SPUIBehaviorWinInterpolator.cpp -- migrated from slice(s) s007fed20 by tools/migrate/rewrite.py
// Object file: Spui/SPUIBehaviorWinInterpolator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <cstddef>
#include <math.h>

// ---- items of slice s007fed20 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* VCallR(void* o, int off) {
    return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCallV(void* o, int off) {
    ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCallI1(void* o, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}
struct ShadeColor {
    char pad0[0xc];
    char mbFrom;          // +0xc
    char mbUseWin;        // +0xd
    char padE[2];         // +0xe
    void* mpWindow;       // +0x10
    unsigned mColorTo;    // +0x14
    unsigned mColorFrom;  // +0x18
    void Init(unsigned from, unsigned to);      // @ 0x007ff5d0
    void CopyFromWindow();                      // @ 0x007ff600
    void Apply(float t, int a);                 // @ 0x007ff570
};
struct Scale {
    char pad0[0xc];
    char mbFrom;      // +0xc
    char mbUseWin;    // +0xd
    char padE[2];     // +0xe
    void* mpWindow;   // +0x10
    float mScale;     // +0x14
    float mScaleTo;   // +0x18
    float mScaleFrom; // +0x1c
    bool mbInit;      // +0x20
    void Set(float from, float to);   // @ 0x007ff690
    void Set2(float v);               // @ 0x007ff6b0
    void SetDefault();                // @ 0x007ff6d0
    void Apply(float t, int a);       // @ 0x007ff7c0
};
// ---- items of slice s007fed20 end

// @ 0x007ff570
void ShadeColor::Apply(float t, int a)
{
    void* w = *(void**)((char*)this + 0x10);
    if (w && a == 0) {
        if (mbUseWin && !mbFrom) {
            VCallV(this, 0x28);
            mbFrom = 1;
        }
        unsigned c = 0; // EA::UTFWin::Color::Lerp(mColorFrom, mColorTo, t)
        VCallI1(w, 0x5c, (int)c);
    }
}

// @ 0x007ff5d0
void ShadeColor::Init(unsigned from, unsigned to)
{
    mColorFrom = from;
    mColorTo = to;
    mbUseWin = 0;
}

// @ 0x007ff600
void ShadeColor::CopyFromWindow()
{
    void* w = *(void**)((char*)this + 0x10);
    mColorFrom = (unsigned)(intptr_t)VCallR(w, 0x30);
}

// @ 0x007ff620
void ScaleCtor(void* self)
{
    *(char*)((char*)self + 0xc) = 0;
    *(char*)((char*)self + 0x20) = 0;
    *(char*)((char*)self + 0xd) = 1;
    *(float*)((char*)self + 0x18) = 1.0f;
    *(float*)((char*)self + 0x1c) = 1.0f;
}

// @ 0x007ff690
void Scale::Set(float from, float to)
{
    mScaleFrom = from;
    mScaleTo = to;
    mbUseWin = 0;
}

// @ 0x007ff6b0
void Scale::Set2(float v)
{
    mScaleTo = v;
    mbUseWin = 1;
}

// @ 0x007ff6d0
void Scale::SetDefault()
{
    mScaleFrom = 1.0f;
}

// @ 0x007ff7c0
void Scale::Apply(float t, int a)
{
    void* w = *(void**)((char*)this + 0x10);
    if (!w) return;
    if (a == 0) {
        mbInit = true;
        if (mbUseWin && !mbFrom) {
            VCallV(this, 0x28);
            mbFrom = 1;
        }
        VCallV(w, 0x98);
        float v = (1.0f - t) * mScaleFrom + mScaleTo * t;
        mScale = v;
        if (fabsf(v) < 0.03f) { mScale = 0.03f; return; }
        if (fabsf(1.0f - v) < 0.03f) mScale = 1.0f;
    } else if (mbInit) {
        mScale = mScale;
    }
}
