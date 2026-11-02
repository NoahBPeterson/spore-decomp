// src/game/Spui/SPUIBehaviorWinAction.cpp -- migrated from slice(s) s012f64e0, s007fd840 by tools/migrate/rewrite.py
// Object file: Spui/SPUIBehaviorWinAction.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <cstddef>
#include <math.h>
#include "EA/Stopwatch.h"
#include <intrin.h>

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
inline void VCallI1(void* o, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}
inline float VCallF(void* o, int off) {
    return ((float(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline float VCallFI(void* o, int off, int a) {
    return ((float(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}
inline void VCallF1(void* o, int off, float a) {
    ((void(__thiscall*)(void*, float))(*(void**)((char*)*(void**)o + off)))(o, a);
}
inline void VCallF2(void* o, int off, float a, int b) {
    ((void(__thiscall*)(void*, float, int))(*(void**)((char*)*(void**)o + off)))(o, a, b);
}
inline void VCallI2(void* o, int off, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)o + off)))(o, a, b);
}
struct IObj {
    virtual void AddRef();
    virtual void Release();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
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
void  FUN_00951330(void* p);        // 0x00951330 (MultiHeapObject::operator delete)
void  SList_SetAllocator(void* p, void* a);
struct C_7fb320 { void Dtor(); };   // 0x007fb320 (thiscall)
struct Stopwatch {
    unsigned __int64 mnStartTime;         // +0x00
    unsigned __int64 mnTotalElapsedTime;  // +0x08
    int   mnUnits;                        // +0x10
    float mfCoefficient;                  // +0x14
    void Init(int a, int b);              // 0x93a560 (ctor; args units, start)
    long long GetElapsed();               // 0x93a3a0 (tick count in edx:eax)
};
struct TC_7fb3b0 { bool FUN_007fb3b0(int v); };              // 0x007fb3b0 base SetEnabled gate
struct TC_b5f950 { void FUN_b5f950(void* p); };              // 0x00b5f950 AutoRefCount<T>::operator=
void* FUN_005ca960(void* o);                                 // 0x005ca960 COM interface_cast<IWinButton_,IWindow>
struct SerBuffer { void* type; void* base; unsigned count; };
struct SerItem14 { char pad[0x14]; unsigned count; };
struct Interp {
    char  pad0[0xc];
    void* mpEvent;           // +0x0c
    char  pad10[0x20];
    void* mpTimeFunction;    // +0x30  (primary + 0x3c)
    void* mpValueInterp;     // +0x34  (primary + 0x40)
    float mLastTime;         // +0x38  (primary + 0x44)
    Stopwatch mStopwatch;    // +0x3c  (primary + 0x48)
    int   pad54[4];          // +0x54..0x63
    Interp();
    void* DeletingDtor(unsigned char flags);
    bool HandleMessage(int msg, void* arg);   // @ 0x007fdbc0
    char SetEnabled(int v);                   // @ 0x007fdd10
    void SetTimeFunction(IObj* p);            // @ 0x007fdb60
    void SetValueInterp(IObj* p);             // @ 0x007fdb90
};
struct Interp0 {
    void*    mVtbl0;         // 0x00
    void*    mVtbl4;         // 0x04
    unsigned m08;            // 0x08
    void*    mVtblC;         // 0x0c
    unsigned m10, m14, m18, m1c, m20, m24, m28, m2c, m30, m34;  // 0x10..0x37
    void*    mpOwnerWin;     // 0x38  borrowed owner/window (queried through vt[0x44])
    void*    mpTimeFunction; // 0x3c
    void*    mpValueInterp;  // 0x40
    float    mLastTime;      // 0x44
    Stopwatch mStopwatch;    // 0x48  (0x18 bytes, coefficient at 0x5c)
};
struct State {
    void* mVtbl0;        // +0x00
    void* mVtbl4;        // +0x04
    void* mVtbl8;        // +0x08
    void* mVtblC;        // +0x0c
    char pad10[0x2c];    // +0x10
    void* mpSlot;        // +0x3c
    void* mpValueInterp; // +0x40
    char pad44[0xc];     // +0x44
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
    // ECX is the sub-object the constructor put its vtable on at primary+0x0c;
    // the primary object (owner of the root vtable) sits 0x0c bytes below.
    void* primary = (char*)this - 0x0c;
    ((AB*)this)->HandleMessageBase(msg, arg);
    if (msg == 0xc) {
        if (mpTimeFunction == 0 || mpValueInterp == 0)
            goto invalidate;
        {
            long long el = mStopwatch.GetElapsed();
            float t = (float)el * mStopwatch.mfCoefficient;
            VCallF1(mpTimeFunction, 0x2c, t - mLastTime);
            float v = VCallF(mpTimeFunction, 0x18);
            VCallF2(mpValueInterp, 0x18, v, 0);
            mLastTime = t;
            if (VCallB(mpTimeFunction, 0x3c) != 0)
                goto invalidate;
        }
        goto done;
    invalidate:
        VCallI1(primary, 0x1c, 0);
    } else if (msg == 0x15) {
        if (mpTimeFunction == 0 || mpValueInterp == 0)
            goto done;
        {
            int u = *(int*)(*(int*)((char*)arg + 0x18) + 0x18);
            float v = VCallFI(mpTimeFunction, 0x18, u);
            VCallF1(mpValueInterp, 0x18, v);
        }
    } else if (msg == 0x24f6efa) {
        if (mpTimeFunction == 0)
            goto done;
        VCallI1(mpTimeFunction, 0x30, *(int*)((char*)arg + 0x10) == 0);
        if (VCallB(primary, 0x18) != 0)
            goto done;
        float v = VCallFI(mpTimeFunction, 0x18, 0);
        VCallF1(mpValueInterp, 0x18, v);
    }
done:
    return false;
}

// @ 0x007fdd10
char Interp::SetEnabled(int v)
{
    Interp0* o = (Interp0*)this;
    char before = VCallB(this, 0x18);
    char ok = ((TC_7fb3b0*)this)->FUN_007fb3b0(v);
    if (ok == 0)
        return 0;
    if (o->mpTimeFunction != 0 && o->mpOwnerWin != 0) {
        int q = VCallI(o->mpOwnerWin, 0x44);
        VCallI1(o->mpTimeFunction, 0x30, q == 0);
    }
    if (before == 0) {
        if (VCallB(this, 0x18) != 0) {
            if (o->mpTimeFunction != 0)
                VCallV(o->mpTimeFunction, 0x24);
            long long el = o->mStopwatch.GetElapsed();
            o->mLastTime = (float)el * o->mStopwatch.mfCoefficient;
        }
    }
    return ok;
}

// @ 0x007fde00
bool SerLoadVector(SerBuffer* p, void* self, SerItem14* item)
{
    IObj** src = *(IObj***)((char*)self + 4);
    IObj** dst = (IObj**)(*(int*)((char*)p + 4) + *(int*)((char*)item + 0x10));
    unsigned i = 0;
    if (item->count == 0)
        return true;
    do {
        void* created = 0;
        if (*dst) VCallV(*dst, 4);
        if (*src) {
            created = VCallR(*src, 0xc);
            if (created) VCallV(created, 0);
        }
        *dst = (IObj*)created;
        ++i; ++dst; ++src;
    } while (i < item->count);
    return true;
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

// @ 0x007fe070
State::State()
{
    ((AB*)this)->Ctor();
    *(void**)((char*)this + 0x3c) = 0;
    *(void**)((char*)this + 0x00) = (void*)0x1415fe8;
    *(void**)((char*)this + 0x04) = (void*)0x1415fd4;
    *(void**)((char*)this + 0x0c) = (void*)0x1415fc4;
    *(void**)((char*)this + 0x40) = 0;
    *(void**)((char*)this + 0x4c) = 0;
    *(int*)((char*)this + 0x44) = 0x7fffffff;
    *(int*)((char*)this + 0x48) = 0x7fffffff;
}

// @ 0x007fe0e0
void State::SetWindow(IObj* np)
{
    if (np == 0) {
        IObj* old = *(IObj**)((char*)this + 0x40);
        if (old) {
            *(IObj**)((char*)this + 0x40) = 0;
            old->Release();
        }
    }
    ((EvBase*)this)->SetValue((int)np);
}

// @ 0x007fe130
int State::Refresh()
{
    void** slot = (void**)((char*)this + 0x40);
    if (*slot != 0) {
        if (VCallI(*slot, 0x10) == 0 ||
            (*(int*)((char*)this + 0x44) != 0x7fffffff &&
             VCallI(*slot, 0x1c) != *(int*)((char*)this + 0x44))) {
            void* p = *slot;
            if (p != 0) {
                *slot = 0;
                VCallV(p, 4);
            }
        }
    }
    if (*slot != 0)
        goto done;
    {
        unsigned kind = *(unsigned*)((char*)this + 0x4c);
        if (kind == 3) {
            void* w = *(void**)((char*)this + 0x38);
            void* np = w ? VCallR(w, 0x58) : 0;
            void* old = *slot;
            if (np != old) {
                if (np) VCallV(np, 0);
                *slot = np;
                if (old) VCallV(old, 4);
            }
            if (VCallI(*slot, 0x10) != 0)
                goto done;
            if (*slot != 0) {
                void* p = *slot;
                *slot = 0;
                VCallV(p, 4);
            }
        } else if (*(int*)((char*)this + 0x44) == 0x7fffffff) {
            void* w = *(void**)((char*)this + 0x38);
            if (w != 0) {
                void* np = VCallR(w, 0x1c);
                if (np != 0 && VCallI(np, 0x10) != 0)
                    ((TC_b5f950*)((char*)this + 0x40))->FUN_b5f950(np);
            }
        } else if (kind == 0) {
            void* w = *(void**)((char*)this + 0x38);
            if (VCallR(w, 0x1c) != 0) {
                void* e = VCallR(VCallR(w, 0x1c), 0x14);
                if (e != 0 && VCallI(e, 4) != 0) {
                    void* r = VCallR(e, 4);
                    void* v = ((void*(__thiscall*)(void*, int, int))
                               (*(void**)((char*)*(void**)r + 0xf0)))(r, *(int*)((char*)this + 0x44), 1);
                    ((TC_b5f950*)((char*)this + 0x40))->FUN_b5f950(v);
                }
            }
        } else if (kind == 1) {
            void* w = *(void**)((char*)this + 0x38);
            if (w != 0) {
                void* np = VCallR(w, 0x1c);
                if (np != 0) {
                    void* it = VCallR(np, 0x10);
                    while (it != 0) {
                        if (*slot != 0)
                            goto done;
                        if (VCallI(it, 0x1c) == *(int*)((char*)this + 0x44))
                            ((TC_b5f950*)((char*)this + 0x40))->FUN_b5f950(it);
                        it = VCallR(it, 0x10);
                    }
                }
            }
        } else if (kind == 2) {
            void* w = *(void**)((char*)this + 0x38);
            if (w != 0) {
                void* r = VCallR(w, 0x1c);
                if (r != 0) {
                    void* v = ((void*(__thiscall*)(void*, int, int))
                               (*(void**)((char*)*(void**)r + 0xf0)))(r, *(int*)((char*)this + 0x44), 1);
                    ((TC_b5f950*)((char*)this + 0x40))->FUN_b5f950(v);
                }
            }
        }
    }
done:
    return (int)(intptr_t)*slot;
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

// @ 0x007fe390
void* State::DeletingDtor(unsigned char flags)
{
    State* s = this;
    s->mVtbl0 = (void*)0x1415fe8;
    s->mVtbl4 = (void*)0x1415fd4;
    s->mVtblC = (void*)0x1415fc4;
    void* p = s->mpValueInterp;
    if (p) {
        s->mpValueInterp = 0;
        VCallV(p, 4);
    }
    p = s->mpValueInterp;
    if (p) {
        VCallV(p, 4);
    }
    ((C_7fb320*)s)->Dtor();
    if (flags & 1) FUN_00951330(s);
    return s;
}

// @ 0x007fe3f0
bool State::Activate(int v)
{
    char before = VCallB(this, 0x18);
    char ok = ((TC_7fb3b0*)this)->FUN_007fb3b0(v);
    if (ok == 0)
        return true;
    if (before != 0)
        return true;
    if (VCallB(this, 0x18) == 0)
        return true;
    void* tgt = (void*)(intptr_t)Refresh();
    if (tgt == 0)
        goto def;
    switch (*(unsigned*)((char*)this + 0x3c)) {
    case 0:  VCallI2(tgt, 0x7c, 1, 1);      break;
    case 1:  VCallI2(tgt, 0x7c, 1, 0);      break;
    case 2:  VCallI2(tgt, 0x7c, 2, 1);      break;
    case 3:  VCallI2(tgt, 0x7c, 2, 0);      break;
    case 4:  VCallI2(tgt, 0x7c, 0x10, 1);   break;
    case 5:  VCallI2(tgt, 0x7c, 0x10, 0);   break;
    case 6:  VCallI2(tgt, 0x7c, 0x1000, 1); break;
    case 7:  VCallI2(tgt, 0x7c, 0x1000, 0); break;
    case 8:
    case 9: {
        void* btn = FUN_005ca960(tgt);
        if (btn == 0 || VCallI(btn, 0x18) == 1)
            goto def;
        VCallI2(btn, 0x28, 4, *(unsigned*)((char*)this + 0x3c) == 8);
        VCallV(tgt, 0x90);
        break;
    }
    case 10:
    case 11: {
        void* btn = FUN_005ca960(tgt);
        if (btn == 0)
            goto def;
        VCallI2(btn, 0x28, 8, *(unsigned*)((char*)this + 0x3c) == 10);
        VCallV(tgt, 0x90);
        break;
    }
    case 12:
    case 13: {
        void* btn = FUN_005ca960(tgt);
        if (btn == 0)
            goto def;
        VCallI2(btn, 0x28, 2, *(unsigned*)((char*)this + 0x3c) == 0xc);
        VCallV(tgt, 0x90);
        break;
    }
    case 0xe:
        VCallI1(tgt, 0x5c, *(int*)((char*)this + 0x48));
        VCallV(tgt, 0x90);
        break;
    case 0xf:
        VCallI1(tgt, 0xac, *(int*)((char*)this + 0x48));
        VCallV(tgt, 0x90);
        break;
    case 0x10:
        VCallV(tgt, 0x90);
        break;
    case 0x11:
        VCallV(tgt, 0x98);
        break;
    case 0x12:
    case 0x13: {
        void* r = VCallR(tgt, 0x14);
        int arg = (*(unsigned*)((char*)this + 0x3c) != 0x12) - 1;
        arg &= (int)(intptr_t)tgt;
        VCallI2(r, 0x58, 1, arg);
        break;
    }
    default:
        goto def;
    }
    ((TC_7fb3b0*)this)->FUN_007fb3b0(0);
    return true;
def:
    ((TC_7fb3b0*)this)->FUN_007fb3b0(0);
    return true;
}

// @ 0x012f7570
void init_1542c44()
{
    *(int*)0x1542c44 = 1;
    *(int*)0x1542c48 = 0;
    *(void**)0x1542c4c = (void*)0x1416034; *(int*)0x1542c50 = 0x254cdfc; *(short*)0x1542c54 = 0x13; *(int*)0x1542c58 = 0x40; *(int*)0x1542c5c = 1;
}
