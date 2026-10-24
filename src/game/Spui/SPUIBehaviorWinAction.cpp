// src/game/Spui/SPUIBehaviorWinAction.cpp -- migrated from slice(s) s012f64e0, s007fd840 by tools/migrate/rewrite.py
// Object file: Spui/SPUIBehaviorWinAction.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <cstddef>
#include <math.h>

// ---- items of slice s007fd840 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* VCallR(void* o, int off) {
    return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCallV(void* o, int off) {
    ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline bool VCallB(void* o, int off) {
    return ((bool(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline int VCallI(void* o, int off) {
    return ((int(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCall1(void* o, int off, void* a) {
    ((void(__thiscall*)(void*, void*))(*(void**)((char*)*(void**)o + off)))(o, a);
}
inline void VCallI1(void* o, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}
inline float VCallF(void* o, int off) {
    return ((float(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
struct IObj {
    virtual void AddRef();
    virtual void Release();
    virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
};
struct AB {                       // cSPUIBehaviorActionBase
    void Ctor();                  // 0x7fbbc0
    bool HandleMessageBase(int, void*); // 0x7f9b80  (really 8-byte thiscall wrapper)
    void SetEnabled(int);         // 0x7fb3b0
    bool SetEnabled2(int);        // 0x7fb3b0 variant used by 7fdd10
    void BaseDtor();              // 0x7fb320
};
struct EvBase {
    void Ctor();                  // 0x7fc200
    void SetValue(int);           // 0x7f9ae0
};
void  FUN_007fb320(void* self);
void  FUN_00951330(void* p);        // 0x00951330 (MultiHeapObject::operator delete)
void  SList_SetAllocator(void* p, void* a);
struct Stopwatch {
    int lo, hi, a, b, mode;
    void Init(int, int);
    float GetElapsed();
};
struct Interp0 {
    void* mVtbl0;   // +0x00
    void* mVtbl4;   // +0x04
    unsigned m08;   // +0x08
    void* mVtblC;   // +0x0c
    char pad10[0x2c];
    void* mpTimeFunction;   // +0x3c
    void* mpValueInterp;    // +0x40
};
struct C_7fb320 { void Dtor(); };   // 0x007fb320 (thiscall)
struct Interp {
    char  pad0[0xc];
    void* mpEvent;
    char  pad10[0x20];
    void* mpTimeFunction;   // +0x30
    void* mpValueInterp;    // +0x34
    float mLastTime;        // +0x38
    Stopwatch mStopwatch;   // +0x3c
    char  pad4c[0x14];
    Interp();
    void* DeletingDtor(unsigned char flags);
    bool HandleMessage(int msg, void* arg);   // @ 0x007fdbc0
    char SetEnabled(int v);                   // @ 0x007fdd10
    void SetTimeFunction(IObj* p);            // @ 0x007fdb60
    void SetValueInterp(IObj* p);             // @ 0x007fdb90
};
struct State {
    void* mVtbl0;        // +0x00
    void* mVtbl4;        // +0x04
    void* mVtbl8;        // +0x08
    void* mVtblC;        // +0x0c
    char pad10[0x2c];
    void* mpSlot;        // +0x3c
    void* mpValueInterp; // +0x40
    char pad44[0xc];
    State();
    void* DeletingDtor(unsigned char flags);
    int Refresh();                       // @ 0x007fe130
    bool Activate(int v);                // @ 0x007fe3f0
    void SetWindow(IObj* p);             // @ 0x007fe0e0
    void SetAllocatorObj();              // @ 0x007fdfa0
    bool InitWith(int v);                // @ 0x007fdfe0
};
// ---- items of slice s007fd840 end

// @ 0x007fdb60
void Interp::SetTimeFunction(IObj* np)
{
    IObj* old = *(IObj**)((char*)this + 0x3c);
    if (np != old) {
        if (old) old->Release();
        *(IObj**)((char*)this + 0x3c) = np;
        if (np) np->AddRef();
    }
}

// @ 0x007fdb90
void Interp::SetValueInterp(IObj* np)
{
    IObj* old = *(IObj**)((char*)this + 0x40);
    if (np != old) {
        if (old) old->Release();
        *(IObj**)((char*)this + 0x40) = np;
        if (np) np->AddRef();
    }
}

// @ 0x007fdbc0
bool Interp::HandleMessage(int msg, void* arg)
{
    AB* b = (AB*)this;
    b->HandleMessageBase(msg, arg);
    void* tf = *(void**)((char*)this + 0x30);
    void* vi = *(void**)((char*)this + 0x34);
    if (msg == 0xc) {
        if (tf && vi) {
            float el = mStopwatch.GetElapsed() * *(float*)((char*)this + 0x50) - mLastTime;
            VCallI1(tf, 0x2c, *(int*)&el);
            float v = VCallF(tf, 0x18);
            VCall1(vi, 0x18, *(void**)&v);
            mLastTime = el;
            if (!VCallB(tf, 0x3c))
                goto done;
        }
        ((bool(__thiscall*)(void*, int))(*(void**)((char*)*(void**)this - 0xc + 0x1c)))((char*)this - 0xc, 0);
    } else if (msg == 0x15) {
        if (tf && vi) {
            int u = *(int*)(*(int*)((char*)arg + 0x18) + 0x18);
            float v = VCallF(tf, 0x18);
            VCall1(vi, 0x18, *(void**)&v);
        }
    } else if (msg == 0x24f6efa && tf) {
        VCallI1(tf, 0x30, *(int*)((char*)arg + 0x10) == 0);
        if (!((bool(__thiscall*)(void*, int))(*(void**)((char*)*(void**)this - 0xc + 0x18)))((char*)this - 0xc, 0)) {
            float v = VCallF(tf, 0x18);
            VCall1(vi, 0x18, *(void**)&v);
        }
    }
done:
    return false;
}

// @ 0x007fdd10
char Interp::SetEnabled(int v)
{
    char before = VCallB(this, 0x18);
    char ok = ((char(__thiscall*)(void*, int))(*(void**)((char*)*(void**)this + 0x0))) ? 1 : 0;
    ok = ((char(__thiscall*)(void*, int))0, 0);
    // FUN_007fb3b0
    char r = 0;
    if (r) {
        void* tf = *(void**)((char*)this + 0x30);
        void* vi = *(void**)((char*)this + 0x34);
        if (tf && vi) {
            int q = VCallI(vi, 0x44);
            VCallI1(tf, 0x30, q == 0);
        }
        if (before == 0) {
            before = VCallB(this, 0x18);
            if (before) {
                if (tf) VCallV(tf, 0x24);
                float el = mStopwatch.GetElapsed() * *(float*)((char*)this + 0x5c);
                *(float*)((char*)this + 0x44) = el;
            }
        }
    }
    return r;
}

// @ 0x007fdfa0
void State::SetAllocatorObj()
{
    void* w = *(void**)((char*)this + 0x40);
    if (!w) return;
    void* s = VCallR(w, 0xc);
    if (!s) return;
    void* src = *(void**)((char*)this + 0x38);
    if (!src) return;
    SList_SetAllocator(s, (void*)(intptr_t)VCallR(src, 0x1c));
}

// @ 0x007fdfe0
bool State::InitWith(int v)
{
    ((EvBase*)this)->SetValue(v);
    void* w = *(void**)((char*)this + 0x40);
    if (w) {
        void* s = VCallR(w, 0xc);
        if (s) {
            void* src = *(void**)((char*)this + 0x38);
            if (src)
                SList_SetAllocator(s, (void*)(intptr_t)VCallR(src, 0x1c));
            else
                SList_SetAllocator(s, 0);
        }
    }
    return true;
}

// @ 0x007fe330
void* Interp::DeletingDtor(unsigned char flags)
{
    void* self = this;
    Interp0* p0 = (Interp0*)self;
    void* a = p0->mpTimeFunction;        // +0x3c
    p0->mVtbl0 = (void*)0x1415f18;
    p0->mVtbl4 = (void*)0x1415f08;
    p0->mVtblC = (void*)0x1415ef8;
    if (a) {
        VCallV(a, 4);
        p0->mpTimeFunction = 0;
    }
    void* b = p0->mpValueInterp;         // +0x40
    if (b) {
        VCallV(b, 4);
        p0->mpValueInterp = 0;
    }
    ((C_7fb320*)self)->Dtor();
    if (flags & 1) FUN_00951330(self);
    return self;
}

// @ 0x012f7570
void init_1542c44()
{
    *(int*)0x1542c44 = 1;
    *(int*)0x1542c48 = 0;
    *(void**)0x1542c4c = (void*)0x1416034; *(int*)0x1542c50 = 0x254cdfc; *(short*)0x1542c54 = 0x13; *(int*)0x1542c58 = 0x40; *(int*)0x1542c5c = 1;
}
