// slice s007fd840 — UTFWin behavior action/event region. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <cstddef>
#include <math.h>
#include <intrin.h>
#include "types.h"

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
inline void* VCallR1(void* o, int off, int a) {
    return ((void*(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}

struct IObj {
    virtual void AddRef();
    virtual void Release();
    virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
};

// shared stub classes for the out-of-line thiscall callees
struct AB {                       // cSPUIBehaviorActionBase
    void Ctor();                  // 0x7fbbc0
    bool HandleMessageBase(int, void*); // 0x7f9b80  (really 8-byte thiscall wrapper)
    void SetEnabled(int);         // 0x7fb3b0
    bool SetEnabled2(int);        // 0x7fb3b0 variant used by 7fdd10
    void BaseDtor();              // 0x7fb320
};
struct PredActBase {              // cSPUIBehaviorPredicateBase / ActionBase (smaller)
    void Ctor();                  // 0x7fba00 / 0x7fbb20 / 0x7fbbc0
    void BaseDtor();              // 0x7fb320
};
struct EvBase {
    void Ctor();                  // 0x7fc200
    void SetValue(int);           // 0x7f9ae0
};

// messaging server with the virtual slots used by the event base
struct Svr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(void*, unsigned);  // +0x20  register target
    virtual void v9();
    virtual void v10();
    virtual void v11(void*, unsigned, int); // +0x2c  unregister target
    virtual void v12();
};

extern float g_f164b620;   // 0x0164b620 (equiv t3)
float FUN_007facf0(void* self);
void  FUN_007fa6d0(int, void*);
void* FUN_007fa690(void* self, int i);
void* FUN_007fa390(void* o, void* p, int b);
bool  FUN_007fa520(void* arr, int n, void* counter);
void  FUN_007fcc40(void* out, void* arg);
void  FUN_007fe950(void* p);
void  FUN_007fb250(void* out);
void  FUN_0095ea30(void* p);
void  FUN_007fb480(void* self, int v);
void  FUN_00951330(void* p);        // 0x00951330 (MultiHeapObject::operator delete)
void* EA_Messaging_GetServer();   // 0x00883860 (equiv t2)
void  SList_SetAllocator(void* p, void* a);
void  FUN_007fba00(void*);
void  FUN_007fbb20(void*);
void  FUN_007fbbc0(void*);
struct C_7fb320 { void Dtor(); };   // 0x007fb320 (thiscall)
struct C_7fc200 { void Dtor(); };   // 0x007fc200 (thiscall)

// EA::StdC::Stopwatch (0x0093a560 ctor, 0x0093a3a0 elapsed read).  Layout taken
// from the retail: a start tick, the accumulated elapsed ticks, the units the
// ticks are in and a scaling coefficient.
struct Stopwatch {
    unsigned __int64 mnStartTime;         // +0x00
    unsigned __int64 mnTotalElapsedTime;  // +0x08
    int   mnUnits;                        // +0x10
    float mfCoefficient;                  // +0x14
    void Init(int a, int b);              // 0x93a560 (ctor; args units, start)
    long long GetElapsed();               // 0x93a3a0 (tick count in edx:eax)
};
union Li { int Parts[2]; unsigned __int64 Quad; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(Li*);

// Out-of-line callees declared as methods so they keep the retail ABI
// (ECX = object, remaining arguments on the stack).
struct TC_7fb3b0 { bool FUN_007fb3b0(int v); };              // 0x007fb3b0 base SetEnabled gate
struct TC_7fd200 { void FUN_007fd200(unsigned f, int on); };  // 0x007fd200 flag setter
struct TC_7fb480 { bool FUN_007fb480(int v); };              // 0x007fb480
struct TC_7fa1d0 { void FUN_007fa1d0(); };                   // 0x007fa1d0 cSPUIBehaviorEventBase::SerUpdate
struct TC_b5f950 { void FUN_b5f950(void* p); };              // 0x00b5f950 AutoRefCount<T>::operator=
void* FUN_005ca960(void* o);                                 // 0x005ca960 COM interface_cast<IWinButton_,IWindow>

// ===========================================================================
// DampedPeriodic overrides (slots 24/25 of the time-function vtable).
// ===========================================================================
struct Damped {
    char  pad0[0xc];
    float mParamDuration;        // +0x0c
    float mParamFrequency;       // +0x10
    float mParamDamping;         // +0x14
    char  pad18[8];
    float mParamPreDelayFactor;  // +0x20
    float mParamPostDelayFactor; // +0x24
    char  pad28[0x18];
    float mWorkTimeFrom;         // +0x40
    float mWorkTimeTo;           // +0x44
    char  mbCeilingMode;         // +0x48
    char  pad49[3];
    unsigned mPeriodicType;      // +0x4c
    float v25(float t);          // @ 0x007fd840
    bool  v24();                 // @ 0x007fd890
};
// Out-of-line overrides reached from Damped::v24 (this in ecx).
struct Ev   { bool Eval(); };    // 0x007f9550 base Eval
struct C_TF { bool IsValid(); }; // 0x007facf0 readiness check

// @ 0x007fd840
float Damped::v25(float t) {
    float r = 1.0f;
    if (mPeriodicType == 1)
        r = cosf(mParamFrequency * g_f164b620 * t);
    if (mbCeilingMode)
        r = (r + 1.0f) * 0.5f;
    return r;
}

// @ 0x007fd890
bool Damped::v24() {
    if (mParamFrequency <= 0.0f && mParamFrequency != 0.0f)
        mParamFrequency = 0.0f;
    ((Ev*)this)->Eval();
    float f = mParamDamping;
    float delta = mWorkTimeTo - mWorkTimeFrom;
    if (f == 0.0f) {
        if (0.0f < delta && ((C_TF*)this)->IsValid()) {
            mParamDamping = -(logf(0.001f) / delta);
            ((Ev*)this)->Eval();
        }
    } else if (0.0f < f) {
        mParamDuration = ((-1.0f / f) * logf(0.001f)) /
                         ((1.0f - mParamPreDelayFactor) - mParamPostDelayFactor);
        ((Ev*)this)->Eval();
    }
    return true;
}

// ===========================================================================
// Serialization item readers.
// ===========================================================================
struct SerItem { void* type; void* base; unsigned count; void* extra; };

// @ 0x007fda80
bool SerReadA(SerItem* out, void* src) {
    IObj* p = *(IObj**)((char*)src + 4);
    VCallV(p, 0x14);
    out->base = p;
    out->count = 1;
    out->type = 0;
    return true;
}

// @ 0x007feb40
struct Sec5 {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5(); // +0x14
};
bool SerReadB(SerItem* out, void* src) {
    void* p = *(void**)((char*)src + 4);
    ((Sec5*)((char*)p + 4))->s5();
    out->base = p;
    out->count = 1;
    out->type = 0;
    return true;
}

// @ 0x007ff8c0
bool SerReadC(SerItem* out, void* src) {
    IObj* p = *(IObj**)((char*)src + 4);
    VCallV(p, 0x14);
    out->base = p;
    out->count = 1;
    out->type = 0;
    return true;
}

struct SerBuffer { void* type; void* base; unsigned count; };
struct SerItem14 { char pad[0x14]; unsigned count; };

// @ 0x007fde00
bool SerLoadVector(SerBuffer* p, void* self, SerItem14* item) {
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

// @ 0x007fe690
bool SerLoadVector2(SerBuffer* p, void* self, SerItem14* item) {
    IObj** src = *(IObj***)((char*)self + 4);
    IObj** dst = (IObj**)(*(int*)((char*)p + 4) + *(int*)((char*)item + 0x10));
    for (unsigned i = 0; i < item->count; i++) {
        void* created = 0;
        if (*dst) VCallV(*dst, 4);
        if (*src) {
            created = VCallR1(*src, 0xc, 0x243c076);
            if (created) VCallV(created, 0);
        }
        *dst = (IObj*)created;
        ++dst;
        ++src;
    }
    return true;
}

// ===========================================================================
// cSPUIBehaviorActionWinInterpolator (this = ActionBase subobject + 0?)
// ===========================================================================
// HandleMessage is entered on the sub-object whose vtable the constructor
// installs at primary+0x0c, so the fields it touches sit 0x0c below the primary
// object's.  The ctor / SetEnabled / DeletingDtor run on the primary object
// instead (Interp0 below).
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

// The primary object: starts on the root vtable and is what the constructor,
// SetEnabled and DeletingDtor receive in ECX.
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

// @ 0x007fdb60
void Interp::SetTimeFunction(IObj* np) {
    IObj* old = *(IObj**)((char*)this + 0x3c);
    if (np != old) {
        if (old) old->Release();
        *(IObj**)((char*)this + 0x3c) = np;
        if (np) np->AddRef();
    }
}

// @ 0x007fdb90
void Interp::SetValueInterp(IObj* np) {
    IObj* old = *(IObj**)((char*)this + 0x40);
    if (np != old) {
        if (old) old->Release();
        *(IObj**)((char*)this + 0x40) = np;
        if (np) np->AddRef();
    }
}

// @ 0x007fdbc0
bool Interp::HandleMessage(int msg, void* arg) {
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
char Interp::SetEnabled(int v) {
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

// @ 0x007fdab0
Interp::Interp() {
    Interp0* o = (Interp0*)this;
    ((AB*)this)->Ctor();
    Stopwatch* sw = &o->mStopwatch;
    o->mVtbl0 = (void*)0x1415f18;
    o->mVtbl4 = (void*)0x1415f08;
    o->mVtblC = (void*)0x1415ef8;
    o->mpTimeFunction = 0;
    o->mpValueInterp = 0;
    o->mLastTime = 0.0f;
    sw->Init(5, 0);
    ((TC_7fd200*)this)->FUN_007fd200(0x80, 1);
    ((TC_7fd200*)this)->FUN_007fd200(0x100, 1);
    if (sw->mnUnits == 1) {
        sw->mnStartTime = __rdtsc();
        sw->mnTotalElapsedTime = 0;
    } else {
        Li li;
        QueryPerformanceCounter(&li);
        sw->mnTotalElapsedTime = 0;
        sw->mnStartTime = li.Quad;
    }
}

// ===========================================================================
// cSPUIBehaviorActionWinState (this = ActionBase subobject)
// ===========================================================================
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

// @ 0x007fe070
State::State() {
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
void State::SetWindow(IObj* np) {
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
int State::Refresh() {
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

// @ 0x007fe3f0
bool State::Activate(int v) {
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

// @ 0x007fdfa0
void State::SetAllocatorObj() {
    void* w = *(void**)((char*)this + 0x40);
    if (!w) return;
    void* s = VCallR(w, 0xc);
    if (!s) return;
    void* src = *(void**)((char*)this + 0x38);
    if (!src) return;
    SList_SetAllocator(s, (void*)(intptr_t)VCallR(src, 0x1c));
}

// @ 0x007fdfe0
bool State::InitWith(int v) {
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

// ===========================================================================
// cSPUIBehaviorWinEventBase and friends
// ===========================================================================
struct WinEvent {
    void* mVtbl0;   // +0x00
    void* mVtbl4;   // +0x04
    void* mVtbl8;   // +0x08
    void* mVtblC;   // +0x0c
    void* mVtbl10;  // +0x10
    void* mVtbl14;  // +0x14
    void* mVtbl18;  // +0x18
    char  pad1c[0x60];               // +0x1c .. +0x7b
    bool mbMessageTargetRegistered;  // +0x7c
    unsigned mMessageType;           // +0x80
    unsigned mMessageWinId;          // +0x84
    char mbBroadcastMode;            // +0x88
    char mbOrigialVisibility;        // +0x89
    bool IsWinState(unsigned v);     // 0x007fead0
    void* DeletingDtor(unsigned char flags);
    bool IsThisType();               // @ 0x007fe7a0
    void SerUpdateWin();             // @ 0x007feb70
    void SetWinMessageType(unsigned t);
    void SetMessageWinId(unsigned id);
};

bool FUN_007fead0(WinEvent* self, unsigned v) { return self->IsWinState(v); }

// @ 0x007fead0
bool WinEvent::IsWinState(unsigned v) {
    int i = *(int*)((char*)this + 0x84);
    if (i != 0x7fffffff)
        return i == (int)v;
    void* p = *(void**)((char*)this + 0x14);
    if (p) {
        int q = VCallI(p, 0x1c);
        if (q == (int)v) return true;
    }
    return false;
}

// @ 0x007fec00
void WinEvent::SetWinMessageType(unsigned t) {
    unsigned old = mMessageType;
    if (t == old) return;
    Svr* s = (Svr*)EA_Messaging_GetServer();
    if (s && mbMessageTargetRegistered) {
        s->v11((char*)this + 0x10, old, -9999);
        mbMessageTargetRegistered = false;
    }
    mMessageType = t;
    s = (Svr*)EA_Messaging_GetServer();
    if (s && !mbMessageTargetRegistered) {
        void* w = *(void**)((char*)this + 0x14);
        if (w) {
            unsigned q = (unsigned)(intptr_t)VCallR(w, 0x1c);
            if (!IsWinState(q)) {
                s->v8((char*)this + 0x10, t);
                mbMessageTargetRegistered = true;
            }
        }
    }
}

// @ 0x007fec90
void WinEvent::SetMessageWinId(unsigned id) {
    if (id == mMessageWinId) return;
    unsigned t = mMessageType;
    Svr* s = (Svr*)EA_Messaging_GetServer();
    if (s && mbMessageTargetRegistered) {
        s->v11((char*)this + 0x10, t, -9999);
        mbMessageTargetRegistered = false;
    }
    mMessageWinId = id;
    t = mMessageType;
    s = (Svr*)EA_Messaging_GetServer();
    if (s && !mbMessageTargetRegistered) {
        void* w = *(void**)((char*)this + 0x14);
        if (w) {
            unsigned q = (unsigned)(intptr_t)VCallR(w, 0x1c);
            if (!IsWinState(q)) {
                s->v8((char*)this + 0x10, t);
                mbMessageTargetRegistered = true;
            }
        }
    }
}

// @ 0x007feb70
void WinEvent::SerUpdateWin() {
    ((TC_7fa1d0*)this)->FUN_007fa1d0();
    unsigned u = *(unsigned*)((char*)this + 0x80);
    Svr* s = (Svr*)EA_Messaging_GetServer();
    if (s != 0 && *(char*)((char*)this + 0x7c) != 0) {
        s->v11((char*)this + 0x10, u, -9999);
        *(char*)((char*)this + 0x7c) = 0;
    }
    u = *(unsigned*)((char*)this + 0x80);
    s = (Svr*)EA_Messaging_GetServer();
    if (s != 0 && *(char*)((char*)this + 0x7c) == 0) {
        void* w = *(void**)((char*)this + 0x14);
        if (w != 0) {
            unsigned q = (unsigned)(intptr_t)VCallR(w, 0x1c);
            if (!IsWinState(q)) {
                s->v8((char*)this + 0x10, u);
                *(char*)((char*)this + 0x7c) = 1;
            }
        }
    }
    VCallI1((char*)this + 0x18, 0x3c, 0);
}

// ===========================================================================
// Property interpolators.
// ===========================================================================
struct ShadeColor {
    char pad0[0xc];
    char mbA, mbB;        // +0xc, +0xd
    char padE[2];
    unsigned mColorTo;    // +0x14
    unsigned mColorFrom;  // +0x18
    ShadeColor();
    void Init(unsigned from, unsigned to);
    void Apply(float t, int a);
    void CopyFromWindow();
};

// @ 0x007ff510
ShadeColor::ShadeColor() {
    *(char*)((char*)this + 0xc) = 0;
    *(char*)((char*)this + 0xd) = 1;
    mColorTo = 0xffffffff;
    mColorFrom = 0xff000000;
}

// @ 0x007ff5d0
void ShadeColor::Init(unsigned from, unsigned to) {
    mColorFrom = from;
    mColorTo = to;
    *(char*)((char*)this + 0xd) = 0;
}

// @ 0x007ff600
void ShadeColor::CopyFromWindow() {
    void* w = *(void**)((char*)this + 0x10);
    mColorFrom = (unsigned)(intptr_t)VCallR(w, 0x30);
}

// @ 0x007ff570
void ShadeColor::Apply(float t, int a) {
    void* w = *(void**)((char*)this + 0x10);
    if (w && a == 0) {
        if (*(char*)((char*)this + 0xd) && !*(char*)((char*)this + 0xc)) {
            VCallV(this, 0x28);
            *(char*)((char*)this + 0xc) = 1;
        }
        unsigned c = 0; // Color::Lerp(mColorFrom, mColorTo, t)
        VCallI1(w, 0x5c, (int)c);
    }
}

struct Scale {
    char pad0[0xc];
    char mbA, mbB;    // +0xc, +0xd
    char padE[2];
    float mScale;     // +0x14
    float mScaleTo;   // +0x18
    float mScaleFrom; // +0x1c
    bool mbInit;      // +0x20
    Scale();
    void Set(float from, float to);   // @ 0x007ff690
    void Set2(float v);               // @ 0x007ff6b0
    void SetDefault();                // @ 0x007ff6d0
};

// @ 0x007ff620
Scale::Scale() {
    *(char*)((char*)this + 0xc) = 0;
    *(char*)((char*)this + 0xd) = 1;
    *(char*)((char*)this + 0x20) = 0;
    mScaleTo = 1.0f;
    mScaleFrom = 1.0f;
}

// @ 0x007ff690
void Scale::Set(float from, float to) {
    mScaleFrom = from;
    mScaleTo = to;
    *(char*)((char*)this + 0xd) = 0;
}

// @ 0x007ff6b0
void Scale::Set2(float v) {
    mScaleTo = v;
    *(char*)((char*)this + 0xd) = 1;
}

// @ 0x007ff6d0
void Scale::SetDefault() {
    mScaleFrom = 1.0f;
}

// @ 0x007fe7a0
bool WinEvent::IsThisType() {
    return *(int*)((char*)this + 0x68) == 0x25a5f84;
}

// @ 0x007ff8f0
bool PredCheck(void* self, char* p) {
    if (*p == 0) {
        void* r = VCallR(self, 0x14);
        r = VCallR(r, 0x48);
        if (r != self) { *p = 0; return true; }
    }
    *p = 1;
    return false;
}

// @ 0x007ff940
bool CopyThing(void* self) {
    char tmp[12];
    FUN_007fb250(tmp);
    *(int*)((char*)self + 4) = *(int*)(tmp + 4);
    *(int*)((char*)self + 8) = *(int*)(tmp + 8);
    *(int*)((char*)self + 0) = *(int*)(tmp + 0);
    return true;
}

struct BoolEvent {
    bool Pred(char a, char b);
    void Activate(int v);            // @ 0x007fe8c0
};

// @ 0x007fe7d0
bool BoolEvent::Pred(char a, char b) {
    void* self = this;
    bool result = false;
    int counter = -1;
    if (FUN_007fa520((char*)self + 0x1c, 4, &counter)) {
        void* w = (char*)self + 0x18;
        switch (*(unsigned*)((char*)self + 0x8c)) {
        case 0: if (a == 0 || b != 0) { VCallI1(w, 0x48, a == 0); return a == 0; } break;
        case 1: if (a != 0 || b != 0) { VCallI1(w, 0x48, a != 0); return a != 0; } break;
        case 2: result = true; VCallI1(w, 0x48, a == 0); break;
        case 3: VCallI1(w, 0x48, a != 0); return true;
        }
    }
    return result;
}

// @ 0x007fe8c0
void BoolEvent::Activate(int v) {
    if ((char)v == 0 && *(int*)((char*)this + 0x68) == 0x25a61c5) {
        int counter = -1;
        if (FUN_007fa520((char*)this + 4, 4, &counter)) {
            int arg;
            switch (*(unsigned*)((char*)this + 0x74)) {
            case 0:
            case 2: arg = 1; break;
            case 3: arg = 0; break;
            default: goto done;
            }
            VCallI1(this, 0x48, arg);
        }
    }
done:
    ((TC_7fb480*)this)->FUN_007fb480(v);
}

// @ 0x007fe330
void* Interp::DeletingDtor(unsigned char flags) {
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
void* State::DeletingDtor(unsigned char flags) {
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

// @ 0x007fea90
void* WinEvent::DeletingDtor(unsigned char flags) {
    void* self = this;
    WinEvent* w = this;
    w->mVtbl0 = (void*)0x14161c4;
    w->mVtbl4 = (void*)0x14161ac;
    w->mVtbl8 = (void*)0x14162a4;
    w->mVtbl10 = (void*)0x141619c;
    w->mVtbl18 = (void*)0x1416140;
    ((C_7fc200*)self)->Dtor();
    if (flags & 1) FUN_00951330(self);
    return self;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
