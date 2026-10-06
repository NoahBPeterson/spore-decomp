// slice s007fed20 — UTFWin cSPUIBehaviorWinEventBase + win interpolators.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
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
inline void VCallI1(void* o, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}

struct IObj {
    virtual void AddRef();
    virtual void Release();
    virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
};
struct SerItem { void* type; void* base; unsigned count; void* extra; };

void* FUN_007fc880(void* self, int msg, void* arg);
void  FUN_007fcc40(void* out, void* arg);
void  FUN_007fa6d0(int, void*);
void* FUN_007fa690(void* p, int i);
void* FUN_007fa390(void* o, void* p, int b);
bool  FUN_007fa520(void* arr, int n, void* counter);
void* FUN_007fe950(void* p);
void  FUN_007fb480(void* self, int v);
bool  FUN_007fead0(void* self, unsigned v);
void  FUN_00c463d0();
void* EA_Messaging_GetServer();

// ===========================================================================
// Shade colour interpolator.
// ===========================================================================
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

// @ 0x007ff5d0
void ShadeColor::Init(unsigned from, unsigned to) {
    mColorFrom = from;
    mColorTo = to;
    mbUseWin = 0;
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
        if (mbUseWin && !mbFrom) {
            VCallV(this, 0x28);
            mbFrom = 1;
        }
        unsigned c = 0; // EA::UTFWin::Color::Lerp(mColorFrom, mColorTo, t)
        VCallI1(w, 0x5c, (int)c);
    }
}

// ===========================================================================
// Scale interpolator.
// ===========================================================================
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

// @ 0x007ff690
void Scale::Set(float from, float to) {
    mScaleFrom = from;
    mScaleTo = to;
    mbUseWin = 0;
}

// @ 0x007ff6b0
void Scale::Set2(float v) {
    mScaleTo = v;
    mbUseWin = 1;
}

// @ 0x007ff6d0
void Scale::SetDefault() {
    mScaleFrom = 1.0f;
}

// @ 0x007ff7c0
void Scale::Apply(float t, int a) {
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

// ===========================================================================
// SerItem readers.
// ===========================================================================
// @ 0x007ff8c0
bool SerReadC(SerItem* out, void* src) {
    IObj* p = *(IObj**)((char*)src + 4);
    VCallV(p, 0x14);
    out->base = p;
    out->count = 1;
    out->type = 0;
    return true;
}

// ===========================================================================
// cSPUIBehaviorPredicateWinState.
// ===========================================================================
struct PredState {
    char pad0[4];
    void* mpEvent;            // +0x14
    unsigned mWinStateQuery;  // +0x18
    void* mpQueryWindow;      // +0x1c
    unsigned mQueryWindowId;  // +0x20
    unsigned mQueryHexParam;  // +0x24
    unsigned mRelationToWindow; // +0x28
    int Refresh();            // @ 0x007ffa50
};

// @ 0x007ffa50
int PredState::Refresh() {
    void** slot = (void**)((char*)this + 0x1c);
    if (*slot && (VCallI(*slot, 0x10) == 0 ||
        (*(int*)((char*)this + 0x20) != 0x7fffffff && VCallI(*slot, 0x1c) != *(int*)((char*)this + 0x20)))) {
        void* p = *slot;
        if (p) { *slot = 0; VCallV(p, 4); }
    }
    if (*slot == 0) {
        if (*(int*)((char*)this + 0x28) == 3) {
            void* w = *(void**)((char*)this + 0x14);
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
        } else if (*(int*)((char*)this + 0x20) == 0x7fffffff) {
            void* w = *(void**)((char*)this + 0x14);
            if (w) {
                void* np = VCallR(w, 0x1c);
                if (np && VCallI(np, 0x10) != 0 && np != *slot) {
                    if (np) VCallV(np, 0);
                    void* op = *slot;
                    *slot = np;
                    if (op) VCallV(op, 4);
                }
            }
        }
    }
    return (int)(intptr_t)*slot;
}

// @ 0x007ff9f0 (ctor) - approximate
void PredStateCtor(void* self) {
    ((void(*)(void*))0)(self);
    *(unsigned*)((char*)self + 0x18) = 1;
    *(void**)((char*)self + 0x1c) = 0;
    *(unsigned*)((char*)self + 0x20) = 0x7fffffff;
    *(unsigned*)((char*)self + 0x24) = 0x7fffffff;
    *(unsigned*)((char*)self + 0x28) = 0;
}

// @ 0x007ff940
bool CopyThing(void* self) {
    char tmp[12];
    ((void(__fastcall*)(void*))0)(tmp);
    *(int*)((char*)self + 4) = *(int*)(tmp + 4);
    *(int*)((char*)self + 8) = *(int*)(tmp + 8);
    *(int*)((char*)self + 0) = *(int*)(tmp + 0);
    return true;
}

// ===========================================================================
// Win event base / bool-state event.
// ===========================================================================
struct WinEvent {
    char pad0[0x7c];
    bool mbMessageTargetRegistered;  // +0x7c
    unsigned mMessageType;           // +0x80
    unsigned mMessageWinId;          // +0x84
    char mbBroadcastMode;            // +0x88
    char mbOrigialVisibility;        // +0x89
};

// @ 0x007ff400 (ctor)
void WinEventCtor(WinEvent* self, unsigned type, unsigned winId, bool broadcast) {
    *(void**)((char*)self) = 0;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    self->mbMessageTargetRegistered = false;
    self->mMessageType = 0;
    self->mMessageWinId = 0;
    self->mbBroadcastMode = false;
    self->mbOrigialVisibility = true;
    self->mMessageType = type;
    self->mMessageWinId = winId;
    self->mbBroadcastMode = broadcast;
}

// @ 0x007ff470 (ctor)
void WinBoolCtor(WinEvent* self, unsigned type, unsigned winId, bool broadcast) {
    WinEventCtor(self, type, winId, broadcast);
    *(int*)((char*)self + 0x8c) = 3;
}

// ===========================================================================
// Event dispatch (large; reconstruction).
// ===========================================================================
// @ 0x007ff0d0
int WinEventHandleMessage(void* self, unsigned msg, void* arg) {
    int r = (int)(intptr_t)FUN_007fc880(self, msg, arg);
    if (msg == 0x11) {
        void* s = EA_Messaging_GetServer();
        if (s && !*(char*)((char*)self + 0x6c)) {
            void* w = *(void**)((char*)self + 4);
            if (w) {
                unsigned q = (unsigned)(intptr_t)VCallR(w, 0x1c);
                if (!FUN_007fead0(self, q)) {
                    VCallI1(s, 0x20, (int)(intptr_t)self);
                    *(char*)((char*)self + 0x6c) = 1;
                }
            }
        }
    }
    return r;
}

// @ 0x007ff290
int WinBoolHandleMessage(void* self, unsigned msg, void* arg) {
    return WinEventHandleMessage(self, msg, arg);
}

// @ 0x007fed20
int CreateBehaviorMessage(void* self, void** out, void* a, void* b) {
    *out = 0;
    FUN_00c463d0();
    return 0;
}

// @ 0x007ff510 (ctor, approximate: base vtable stores omitted)
void ShadeColorCtor(void* self) {
    *(char*)((char*)self + 0xc) = 0;
    *(char*)((char*)self + 0xd) = 1;
    *(unsigned*)((char*)self + 0x14) = 0xffffffff;
    *(unsigned*)((char*)self + 0x18) = 0xff000000;
}

// @ 0x007ff620 (ctor, approximate: base vtable stores omitted)
void ScaleCtor(void* self) {
    *(char*)((char*)self + 0xc) = 0;
    *(char*)((char*)self + 0x20) = 0;
    *(char*)((char*)self + 0xd) = 1;
    *(float*)((char*)self + 0x18) = 1.0f;
    *(float*)((char*)self + 0x1c) = 1.0f;
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
