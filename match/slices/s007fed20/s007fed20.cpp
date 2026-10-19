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
inline void VCallPP(void* o, int off, void* a, void* b) {
    ((void(__thiscall*)(void*, void*, void*))(*(void**)((char*)*(void**)o + off)))(o, a, b);
}
inline void* VCallPR(void* o, int off, int a) {
    return ((void*(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}

struct IObj {
    virtual void AddRef();
    virtual void Release();
    virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
};
struct SerItem3 { void* f0; void* f4; void* f8; void* fC; };

// Helper ABIs (thiscall modelled as member functions).
struct Obj7fb250 {
    void f(SerItem3* out);                            // 0x7fb250 ret 4
};
struct EvApi {                                          // thiscall helpers
    void BaseCtor();                                    // 0x7fbf40 ret 0
    void SetWinMessageType(unsigned);                   // 0x7fec00 ret 4
    void SetMessageWinId(unsigned);                     // 0x7fec90 ret 4
    void InterpBaseCtor();                              // 0x7fba00 ret 0
};
struct C_7fa690 {
    void* GetAt(int i);                                 // 0x7fa690 ret 4
    bool  SetAt(int i, void* obj);                      // 0x7fa6d0 ret 8
};
struct MsgServer {
    int Add(void* a, void* b, char c);                  // 0x7fa390 ret 0xc
};
struct ARef {
    void* Reset();                                      // 0xc463d0 ret 0
};
extern "C" unsigned ColorLerp(unsigned from, unsigned to, float t);  // 0x7f5eb0 cdecl
struct InterpTarget {
    void SetXform(float* tmp);                        // 0x95ea30 ret 4
};
extern "C" void* EA_Messaging_GetServer();              // 0x883860
struct Q {
    bool IsWinState(unsigned v);                      // 0x7fead0 ret 4
};
struct C_7fe7d0 {
    bool Pred(bool a, bool b);                        // 0x7fe7d0 ret 8
};
void* FUN_007fe950(void* p);                            // 0x7fe950
void  FUN_007fcc40(void* out, void* arg);               // 0x7fcc40 Factory
struct Edge {
    void* Dispatch(unsigned msg, void* arg);          // 0x7fc880 ret 8
};
extern "C" MsgServer* g_164b1f8;                        // 0x164b1f8
extern void FUN_007fba00(void*);                        // 0x7fba00 ret 0 (thiscall)

extern char vt_we_a[], vt_we_b[], vt_we_c[], vt_we_d[], vt_we_e[];  // 0x14161c4 0x14161ac 0x14162a4 0x141619c 0x1416140
extern char vt_wb_a[], vt_wb_b[], vt_wb_c[], vt_wb_d[], vt_wb_e[];  // 0x14162cc 0x14162b4 0x14162a4 0x1416294 0x1416238
extern char vt_sc_a[], vt_sc_b[];                                  // 0x14163f8 0x14163e8
extern char vt_ss_a[], vt_ss_b[];                                  // 0x141642c 0x14163e8


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
    void Init(unsigned from, unsigned to);
    void CopyFromWindow();
    void Apply(float t, int a);
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
    if (!mpWindow || a != 0)
        return;
    if (mbUseWin && !mbFrom) {
        VCallV(this, 0x28);
        mbFrom = 1;
    }
    void* w = mpWindow;
    void** vt = *(void***)w;
    unsigned to = mColorTo;
    unsigned from = mColorFrom;
    unsigned c = ColorLerp(from, to, t);
    ((void(__thiscall*)(void*, unsigned))vt[0x17])(w, c);
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
    char mbInit;      // +0x20
    void Set(float from, float to);
    void Set2(float v);
    void SetDefault();
    void Apply(float t, InterpTarget* a);
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
void Scale::Apply(float t, InterpTarget* a) {
    if (!mpWindow) return;
    if (a != 0) {
        if (mbInit) {
            float tmp[3];
            tmp[0] = mScale;
            tmp[1] = mScale;
            tmp[2] = 1.0f;
            a->SetXform(tmp);
        }
        return;
    }
    mbInit = 1;
    if (mbUseWin && !mbFrom) {
        VCallV(this, 0x28);
        mbFrom = 1;
    }
    VCallV(mpWindow, 0x98);
    float v = (1.0f - t) * mScaleFrom + mScaleTo * t;
    mScale = v;
    if (fabsf(v) < 0.03f) { mScale = 0.03f; return; }
    if (fabsf(1.0f - v) < 0.03f) mScale = 1.0f;
}

// ===========================================================================
// SerItem writers.
// ===========================================================================
// @ 0x007ff8c0
bool SerReadC(SerItem3* out, void* src) {
    IObj* p = *(IObj**)((char*)src + 4);
    VCallV(p, 0x14);
    out->f4 = p;
    out->f8 = (void*)1;
    out->f0 = 0;
    return true;
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
bool CopyThing(SerItem3* out, void* src) {
    Obj7fb250* o = *(Obj7fb250**)((char*)src + 4);
    SerItem3 tmp;
    o->f(&tmp);
    out->f4 = tmp.f4;
    out->f8 = tmp.f8;
    out->f0 = tmp.f0;
    return true;
}

// ===========================================================================
// cSPUIBehaviorPredicateWinState.
// ===========================================================================
struct PredState {
    char pad0[0x14];
    void* mpEvent;            // +0x14
    unsigned mWinStateQuery;  // +0x18
    void* mpQueryWindow;      // +0x1c
    unsigned mQueryWindowId;  // +0x20
    unsigned mQueryHexParam;  // +0x24
    unsigned mRelationToWindow; // +0x28
    int Refresh();
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

// @ 0x007ff9f0
void PredStateCtor(void* self) {
    *(unsigned*)((char*)self + 0x18) = 1;
    *(void**)((char*)self + 0x1c) = 0;
    *(unsigned*)((char*)self + 0x20) = 0x7fffffff;
    *(unsigned*)((char*)self + 0x24) = 0x7fffffff;
    *(unsigned*)((char*)self + 0x28) = 0;
}

// ===========================================================================
// Win event base.
// ===========================================================================
struct WinEvent {
    char pad0[0x7c];
    char mbMessageTargetRegistered; // +0x7c
    unsigned mMessageType;          // +0x80
    unsigned mMessageWinId;         // +0x84
    char mbBroadcastMode;           // +0x88
    char mbOrigialVisibility;       // +0x89
    WinEvent* Ctor(unsigned type, unsigned winId, bool broadcast);
};

struct WinBoolStateEvent : WinEvent {
    char pad8c[0x4];                // +0x8c
    WinBoolStateEvent* Ctor(unsigned a, unsigned type, unsigned winId, bool broadcast);
};

// @ 0x007ff400
WinEvent* WinEvent::Ctor(unsigned type, unsigned winId, bool broadcast) {
    ((EvApi*)this)->BaseCtor();
    mbMessageTargetRegistered = 0;
    mMessageType = 0;
    mMessageWinId = 0;
    mbBroadcastMode = 0;
    *(void**)((char*)this + 0x00) = (void*)vt_we_a;
    *(void**)((char*)this + 0x04) = (void*)vt_we_b;
    *(void**)((char*)this + 0x08) = (void*)vt_we_c;
    *(void**)((char*)this + 0x10) = (void*)vt_we_d;
    *(void**)((char*)this + 0x18) = (void*)vt_we_e;
    mbOrigialVisibility = 1;
    ((EvApi*)this)->SetWinMessageType(type);
    ((EvApi*)this)->SetMessageWinId(winId);
    mbBroadcastMode = (char)broadcast;
    return this;
}

// @ 0x007ff470
WinBoolStateEvent* WinBoolStateEvent::Ctor(unsigned a, unsigned type, unsigned winId, bool broadcast) {
    (void)a;
    ((WinEvent*)this)->Ctor(type, winId, broadcast);
    *(void**)((char*)this + 0x00) = (void*)vt_wb_a;
    *(void**)((char*)this + 0x04) = (void*)vt_wb_b;
    *(void**)((char*)this + 0x08) = (void*)vt_wb_c;
    *(void**)((char*)this + 0x10) = (void*)vt_wb_d;
    *(void**)((char*)this + 0x18) = (void*)vt_wb_e;
    *(int*)((char*)this + 0x8c) = 3;
    return this;
}

// ===========================================================================
// Win interpolators (ctors).
// ===========================================================================
struct ShadeColorFull {
    char pad0[0xc];
    char mbFrom;          // +0xc
    char mbUseWin;        // +0xd
    char padE[2];
    void* mpWindow;       // +0x10
    unsigned mColorTo;    // +0x14
    unsigned mColorFrom;  // +0x18
    ShadeColorFull* Ctor();
};

struct ScaleFull {
    char pad0[0xc];
    char mbFrom;      // +0xc
    char mbUseWin;    // +0xd
    char padE[2];
    void* mpWindow;   // +0x10
    float mScale;     // +0x14
    float mScaleTo;   // +0x18
    float mScaleFrom; // +0x1c
    char mbInit;      // +0x20
    ScaleFull* Ctor();
};

// @ 0x007ff510
ShadeColorFull* ShadeColorFull::Ctor() {
    ((EvApi*)this)->InterpBaseCtor();
    mbFrom = 0;
    mbUseWin = 1;
    *(void**)((char*)this + 0x00) = (void*)vt_sc_a;
    *(void**)((char*)this + 0x04) = (void*)vt_sc_b;
    mColorTo = 0xffffffff;
    mColorFrom = 0xff000000;
    return this;
}

// @ 0x007ff620
ScaleFull* ScaleFull::Ctor() {
    ((EvApi*)this)->InterpBaseCtor();
    mbFrom = 0;
    mbInit = 0;
    mbUseWin = 1;
    *(void**)((char*)this + 0x00) = (void*)vt_ss_a;
    *(void**)((char*)this + 0x04) = (void*)vt_ss_b;
    mScaleTo = 1.0f;
    mScaleFrom = 1.0f;
    return this;
}

// ===========================================================================
// Event dispatch.
// ===========================================================================
struct WinEventW {                 // = (char*)E + 0x10
    char pad0[4];
    void* mpWindow;                // +0x04
    void* mpTarget;                // +0x08
    char padC[0x5c];
    void* mpBehaviorMsg;           // +0x68
    char mbRegistered;             // +0x6c
    unsigned mMessageType;         // +0x70
    unsigned mMessageWinId;        // +0x74
    char mbBroadcastMode;          // +0x78
    char mbVisibility;             // +0x79
    bool HandleMessage(unsigned msg, void* arg);     // 0x7ff0d0 ret 8
    bool BoolHandleMessage(unsigned msg, void* arg); // 0x7ff290 ret 8
};

struct EvE {
    char pad0[0x14];
    void* mpWindow;                                   // +0x14
    bool CreateBehaviorMessage(void** out, unsigned kind, void* a3); // 0x7fed20 ret 0xc
};

// @ 0x007ff0d0
bool WinEventW::HandleMessage(unsigned msg, void* arg) {
    ((Edge*)this)->Dispatch(msg, arg);
    if (msg >= 0x1d)
        return 0;
    void* saved18 = *(void**)((char*)arg + 0x18);
    if (msg == 0x11) {
        unsigned type = mMessageType;
        void* srv = EA_Messaging_GetServer();
        if (srv && !mbRegistered && mpWindow) {
            unsigned q = (unsigned)(intptr_t)VCallR(mpWindow, 0x1c);
            if (!((Q*)((char*)this - 0x10))->IsWinState(q)) {
                VCallPP(srv, 0x20, this, (void*)(intptr_t)type);
                mbRegistered = 1;
            }
        }
        mbVisibility = (char)(VCallI(mpWindow, 0x28) & 1);
        void* local = 0;
        unsigned q = (unsigned)(intptr_t)VCallR(mpWindow, 0x1c);
        if (((Q*)((char*)this - 0x10))->IsWinState(q) &&
            ((EvE*)((char*)this - 0x10))->CreateBehaviorMessage(&local, mMessageType, 0)) {
            *(int*)((char*)local + 0x20) = 1;
            VCallPP(this, 0x04, *(void**)((char*)local + 0x30), local);
            if (mbBroadcastMode)
                ((MsgServer*)g_164b1f8)->Add(*(void**)((char*)local + 0x30), local, 0);
        } else {
            VCallPP(mpWindow, 0x7c, (void*)1, 0);
        }
        if (local) VCallV(local, 8);
    } else if (msg == 0x12) {
        void* srv = EA_Messaging_GetServer();
        if (srv && mbRegistered) {
            ((void(__thiscall*)(void*, void*, unsigned, int))(*(void**)((char*)*(void**)srv + 0x2c)))
                (srv, this, mMessageType, -0x270f);
            mbRegistered = 0;
        }
    }
    if (mpWindow) {
        void* local = 0;
        unsigned q = (unsigned)(intptr_t)VCallR(mpWindow, 0x1c);
        if (((Q*)((char*)this - 0x10))->IsWinState(q)) {
            if (((EvE*)((char*)this - 0x10))->CreateBehaviorMessage(&local, mMessageType, saved18)) {
                *(int*)((char*)local + 0x20) = 0;
                VCallPP(this, 0x04, *(void**)((char*)local + 0x30), local);
                if (mbBroadcastMode)
                    ((MsgServer*)g_164b1f8)->Add(*(void**)((char*)local + 0x30), local, 1);
            }
            if (local) VCallV(local, 8);
        }
    }
    return 0;
}

// @ 0x007ff290
bool WinEventW::BoolHandleMessage(unsigned msg, void* arg) {
    HandleMessage(msg, arg);
    if (msg != mMessageType)
        return 0;
    switch (msg) {
    case 0x25a5f95: case 0x25a5f84: case 0x249f699: case 0x25a5f5a:
    case 0x25a5f8e: case 0x25a5f9a: case 0x25a61c5: case 0x25c8cb3:
        break;
    default:
        return 0;
    }
    char bFlag = (*(int*)((char*)arg + 0x20) != 0);
    unsigned uVar2 = *(unsigned*)((char*)arg + 0x18);
    unsigned uVar3 = mMessageWinId;
    void* node = 0;
    bool takeNode = false;
    bool doLookup = false;
    if (uVar3 == 0x7fffffff) {
        doLookup = (mpWindow != 0 &&
                    (unsigned)(intptr_t)VCallR(mpWindow, 0x1c) == uVar2);
    } else {
        doLookup = (uVar3 == uVar2);
    }
    if (doLookup) {
        if (bFlag || (node = ((C_7fa690*)arg)->GetAt(0)) == 0)
            takeNode = true;
        else
            node = VCallPR(node, 0x0c, (int)0xeeee8218);
    } else {
        if (!bFlag) return 0;
    }
    if (takeNode) node = 0;
    void* old = mpBehaviorMsg;
    if (node != old) {
        if (node) VCallV(node, 0);
        mpBehaviorMsg = node;
        if (old) VCallV(old, 4);
    }
    if (bFlag) {
        char vis = mbVisibility;
        if (vis != (char)(VCallI(mpWindow, 0x28) & 1))
            VCallPP(mpWindow, 0x7c, (void*)1, (void*)(intptr_t)vis);
    }
    bool pred = ((C_7fe7d0*)((char*)this - 0x10))->Pred((*(int*)((char*)arg + 0x10) != 0), bFlag);
    if (pred) {
        void* target = *(void**)((char*)this + 8);
        VCallI1(target, 0x3c, 1);
    }
    return 0;
}

// ===========================================================================
// Create behavior message.
// ===========================================================================
static int MakeEbfBody(EvE* E, void** out, unsigned kind, void* a3) {
    void* win = *(void**)((char*)E + 0x14);
    if (a3 != 0 && (*(int*)((char*)a3 + 8) != 0xe || *(int*)((char*)a3 + 0xc) != 1))
        return 0;
    unsigned mask = 0;
    if (kind == 0x25a5f84) mask = 1;
    else if (kind == 0x25c8cb3) mask = 2;
    if (a3 != 0 && (mask & (*(unsigned*)((char*)a3 + 0x14) ^ *(unsigned*)((char*)a3 + 0x10))) == 0)
        return 0;
    void* local = 0;
    void* fr = ((ARef*)&local)->Reset();
    FUN_007fcc40(fr, (void*)(intptr_t)kind);
    unsigned r = (unsigned)(intptr_t)VCallR(win, 0x28);
    ((C_7fa690*)local)->SetAt(0, FUN_007fe950((char*)E + 0x14));
    *(unsigned*)((char*)local + 0x10) = r & mask;
    *(void**)((char*)local + 0x18) = VCallR(win, 0x1c);
    *out = local;
    VCallV(local, 4);
    if (local) VCallV(local, 8);
    return 1;
}

static int MakeE47Body(EvE* E, void** out, unsigned kind, void* a3) {
    void* win = *(void**)((char*)E + 0x14);
    void* piVar7 = 0;
    if (win) piVar7 = VCallR(win, 0x0c);
    if (a3 != 0 && (*(int*)((char*)a3 + 8) != 0x13 || piVar7 == 0))
        return 0;
    unsigned mask = 0;
    if (kind == 0x25a5f8e) mask = 8;
    else if (kind == 0x25a5f95) mask = 2;
    else mask = 4;
    if (a3 != 0 && (mask & (*(unsigned*)((char*)a3 + 0x10) ^ *(unsigned*)((char*)a3 + 0x0c))) == 0)
        return 0;
    void* local = 0;
    void* fr = ((ARef*)&local)->Reset();
    FUN_007fcc40(fr, (void*)(intptr_t)kind);
    unsigned r = (unsigned)(intptr_t)VCallR(win, 0x2c);
    void* u = piVar7 ? VCallR(piVar7, 0x0c) : 0;
    ((C_7fa690*)local)->SetAt(0, u);
    *(unsigned*)((char*)local + 0x10) = r & mask;
    *(void**)((char*)local + 0x18) = VCallR(win, 0x1c);
    *out = local;
    VCallV(local, 4);
    if (local) VCallV(local, 8);
    return 1;
}

// @ 0x007fed20
bool EvE::CreateBehaviorMessage(void** out, unsigned kind, void* a3) {
    EvE* E = this;
    *out = 0;
    if (kind < 0x25a5f96) {
        if (kind == 0x249f699 || kind == 0x25a5f5a) {
            void* piVar7 = (kind == 0x249f699) ? (void*)1 : 0;
            if (!(a3 == 0 || (*(int*)((char*)a3 + 8) == 10 &&
                              *(void**)((char*)a3 + 0xc) == piVar7)))
                return 0;
            void* local = 0;
            void* fr = ((ARef*)&local)->Reset();
            FUN_007fcc40(fr, (void*)(intptr_t)kind);
            void* win = *(void**)((char*)E + 0x14);
            void* target;
            if (a3 == 0)
                target = VCallR(VCallR(win, 0x14), 0x48);
            else
                target = *(void**)((char*)a3 + 0x18);
            ((C_7fa690*)local)->SetAt(0, FUN_007fe950((char*)E + 0x14));
            *(unsigned*)((char*)local + 0x10) = (target == win);
            *(void**)((char*)local + 0x18) = VCallR(win, 0x1c);
            *out = local;
            VCallV(local, 4);
            if (local) { VCallV(local, 8); return *out != 0; }
            return 0;
        }
        if (kind == 0x25a5f84)
            return MakeEbfBody(E, out, kind, a3) ? (*out != 0) : 0;
        if (kind == 0x25a5f8e || kind == 0x25a5f95)
            return MakeE47Body(E, out, kind, a3) ? (*out != 0) : 0;
        return 0;
    }
    if (kind == 0x25a5f9a)
        return MakeE47Body(E, out, kind, a3) ? (*out != 0) : 0;
    if (kind == 0x25a61c5) {
        if (a3 != 0 && *(int*)((char*)a3 + 8) == 0x287259f6) {
            void* local = 0;
            void* fr = ((ARef*)&local)->Reset();
            FUN_007fcc40(fr, (void*)(intptr_t)kind);
            void* win = *(void**)((char*)E + 0x14);
            void* u = VCallR(win, 0x0c);
            ((C_7fa690*)local)->SetAt(0, u);
            *(unsigned*)((char*)local + 0x10) = 1;
            *(void**)((char*)local + 0x18) = VCallR(win, 0x1c);
            *out = local;
            VCallV(local, 4);
            if (local) { VCallV(local, 8); return *out != 0; }
        }
        return 0;
    }
    if (kind == 0x25c8cb3)
        return MakeEbfBody(E, out, kind, a3) ? (*out != 0) : 0;
    return 0;
}


