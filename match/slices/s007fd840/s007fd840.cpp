// slice s007fd840 — UTFWin behavior action/event region. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <cstddef>
#include <math.h>
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
void  FUN_007fb320(void* self);
void* EA_Messaging_GetServer();   // 0x00883860 (equiv t2)
void  SList_SetAllocator(void* p, void* a);
void  FUN_007fba00(void*);
void  FUN_007fbb20(void*);
void  FUN_007fbbc0(void*);
void  FUN_007fc200(void*);

struct Stopwatch {
    int lo, hi, a, b, mode;
    void Init(int, int);
    float GetElapsed();
};
struct Li { int lo; int hi; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(Li*);
unsigned __int64 __rdtsc();

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
    void  EvalBase();
    bool  IsReady();
    float v25(float t);          // @ 0x007fd840
    bool  v24();                 // @ 0x007fd890
};

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
    EvalBase();
    float f = mParamDamping;
    float delta = mWorkTimeTo - mWorkTimeFrom;
    if (f == 0.0f) {
        if (0.0f < delta && IsReady()) {
            mParamDamping = -(logf(0.001f) / delta);
            EvalBase();
        }
    } else if (0.0f < f) {
        mParamDuration = ((-1.0f / f) * logf(0.001f)) /
                         ((1.0f - mParamPreDelayFactor) - mParamPostDelayFactor);
        EvalBase();
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
    return SerLoadVector(p, self, item);
}

// ===========================================================================
// cSPUIBehaviorActionWinInterpolator (this = ActionBase subobject + 0?)
// ===========================================================================
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
    bool HandleMessage(int msg, void* arg);   // @ 0x007fdbc0
    char SetEnabled(int v);                   // @ 0x007fdd10
    void SetTimeFunction(IObj* p);            // @ 0x007fdb60
    void SetValueInterp(IObj* p);             // @ 0x007fdb90
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
char Interp::SetEnabled(int v) {
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

// @ 0x007fdab0
Interp::Interp() {
    ((AB*)this)->Ctor();
    void* tf = 0, *vi = 0;
    *(void**)((char*)this + 0x3c) = tf;
    *(void**)((char*)this + 0x40) = vi;
    *(float*)((char*)this + 0x44) = 0.0f;
    mStopwatch.Init(5, 0);
    void* vt = *(void**)((char*)this);
    (void)vt;
    // SetFlag(0x80,true) and SetFlag(0x100,true)
    (void)0;
    if (mStopwatch.mode == 1) {
        unsigned __int64 t = __rdtsc();
        mStopwatch.lo = (int)t;
        mStopwatch.hi = (int)(t >> 32);
        mStopwatch.a = 0;
        mStopwatch.b = 0;
    } else {
        Li li;
        QueryPerformanceCounter(&li);
        mStopwatch.lo = li.lo;
        mStopwatch.hi = li.hi;
        mStopwatch.a = 0;
        mStopwatch.b = 0;
    }
}

// ===========================================================================
// cSPUIBehaviorActionWinState (this = ActionBase subobject)
// ===========================================================================
struct State {
    char pad0[0xc];
    char pad10[0x2c];
    void* mpSlot;        // +0x3c
    char pad40[0x10];
    State();
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
    *(void**)((char*)this + 0x40) = 0;
    *(int*)((char*)this + 0x44) = 0x7fffffff;
    *(int*)((char*)this + 0x48) = 0x7fffffff;
    *(void**)((char*)this + 0x4c) = 0;
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
    if (*slot && (VCallI(*slot, 0x10) == 0 ||
        (*(int*)((char*)this + 0x44) != 0x7fffffff && VCallI(*slot, 0x1c) != *(int*)((char*)this + 0x44)))) {
        void* p = *slot;
        if (p) { *slot = 0; VCallV(p, 4); }
    }
    if (*slot == 0) {
        if (*(int*)((char*)this + 0x4c) == 3) {
            void* w = *(void**)((char*)this + 0x38);
            void* np = w ? VCallR(w, 0x58) : 0;
            if (np != *slot) {
                if (np) VCallV(np, 0);
                void* op = *slot;
                *slot = np;
                if (op) VCallV(op, 4);
            }
            if (VCallI(*slot, 0x10) == 0) {
                void* p = *slot;
                if (p) { *slot = 0; VCallV(p, 4); }
            }
        } else if (*(int*)((char*)this + 0x44) == 0x7fffffff) {
            void* w = *(void**)((char*)this + 0x38);
            if (w) {
                void* np = VCallR(w, 0x1c);
                if (np && VCallI(np, 0x10) != 0 && np != *slot) {
                    if (np) VCallV(np, 0);
                    void* op = *slot;
                    *slot = np;
                    if (op) VCallV(op, 4);
                }
            }
        } else {
            void* w = *(void**)((char*)this + 0x38);
            if (w) {
                unsigned id = (unsigned)VCallR(w, 0x1c);
                if (id == *(unsigned*)((char*)this + 0x44) && *slot == 0) {
                    void* np = VCallR(w, 0x58);
                    *slot = np;
                }
            }
        }
    }
    return (int)(intptr_t)*slot;
}

// @ 0x007fe3f0
bool State::Activate(int v) {
    char before = VCallB(this, 0x18);
    char ok = 1;
    (void)ok;
    if (!v) return true;   // reconstruction of the set-enabled gate
    if (before) return true;
    before = VCallB(this, 0x18);
    if (!before) return true;
    int* tgt = (int*)Refresh();
    if (!tgt) return true;
    switch (*(unsigned*)((char*)this + 0x3c)) {
    case 0: VCallI1(tgt, 0x7c, 1); break;
    case 1: VCallI1(tgt, 0x7c, 0); break;
    case 2: VCallI1(tgt, 0x7c, 2); break;
    case 3: VCallI1(tgt, 0x7c, 4); break;
    case 4: VCallI1(tgt, 0x7c, 0x10); break;
    case 5: VCallI1(tgt, 0x7c, 0); break;
    default: break;
    }
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
    char pad0[0x7c];
    bool mbMessageTargetRegistered;  // +0x7c
    unsigned mMessageType;           // +0x80
    unsigned mMessageWinId;          // +0x84
    char mbBroadcastMode;            // +0x88
    char mbOrigialVisibility;        // +0x89
    bool IsWinState(unsigned v);     // @ 0x007fead0
    bool IsThisType();               // @ 0x007fe7a0
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
void SerUpdateWin(void* self) {
    ((EvBase*)self)->SetValue(0); // placeholder: real base SerUpdate
    unsigned u = *(unsigned*)((char*)self + 0x80);
    void* s = EA_Messaging_GetServer();
    if (s && *(char*)((char*)self + 0x7c)) {
        ((void(__thiscall*)(void*, void*, unsigned, int))(*(void**)((char*)*(void**)s + 0x2c)))(s, (char*)self + 0x10, u, -9999);
        *(char*)((char*)self + 0x7c) = 0;
    }
    u = *(unsigned*)((char*)self + 0x80);
    s = EA_Messaging_GetServer();
    if (s && !*(char*)((char*)self + 0x7c)) {
        void* w = *(void**)((char*)self + 0x14);
        if (w) {
            unsigned q = (unsigned)(intptr_t)VCallR(w, 0x1c);
            if (!((WinEvent*)self)->IsWinState(q)) {
                ((void(__thiscall*)(void*, void*, unsigned))(*(void**)((char*)*(void**)s + 0x20)))(s, (char*)self + 0x10, u);
                *(char*)((char*)self + 0x7c) = 1;
            }
        }
    }
    VCallV((char*)self + 0x18, 0x3c);
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

// @ 0x007fe7d0
bool BoolPred(void* self, char a, char b) {
    bool result = false;
    int counter = -1;
    if (FUN_007fa520((char*)self + 0x1c, 4, &counter)) {
        void* w = *(void**)((char*)self + 0x18);
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
void BoolActivate(void* self, int v) {
    if ((char)v == 0 && *(int*)((char*)self + 0x68) == 0x25a61c5) {
        int counter = -1;
        if (FUN_007fa520((char*)self + 0x18, 4, &counter)) {
            int arg;
            switch (*(unsigned*)((char*)self + 0x68)) {
            case 0: case 2: arg = 1; break;
            case 3: arg = 0; break;
            default: goto done;
            }
            VCallI1(*(void**)((char*)self + 0x10), 0x48, arg);
        }
    }
done:
    FUN_007fb480(self, v);
}

// @ 0x007fe330
void* InterpDtor(void* self, unsigned char flags) {
    if (*(void**)((char*)self + 0x3c)) {
        VCallV(*(void**)((char*)self + 0x3c), 4);
        *(void**)((char*)self + 0x3c) = 0;
    }
    if (*(void**)((char*)self + 0x40)) {
        VCallV(*(void**)((char*)self + 0x40), 4);
        *(void**)((char*)self + 0x40) = 0;
    }
    FUN_007fb320(self);
    (void)flags;
    return self;
}

// @ 0x007fe390
void* StateDtor(void* self, unsigned char flags) {
    if (*(void**)((char*)self + 0x40)) {
        void* p = *(void**)((char*)self + 0x40);
        *(void**)((char*)self + 0x40) = 0;
        VCallV(p, 4);
    }
    FUN_007fb320(self);
    (void)flags;
    return self;
}

// @ 0x007fea90
void* WinEventDtor(void* self, unsigned char flags) {
    FUN_007fc200(self);
    (void)flags;
    return self;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
