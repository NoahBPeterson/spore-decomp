// src/game/Spui/SPUIBehaviorWinEvent.cpp -- migrated from slice(s) s007fed20, s007fd840 by tools/migrate/rewrite.py
// Object file: Spui/SPUIBehaviorWinEvent.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/SerTypeInfo.h"
#include <cstddef>
#include <math.h>

// ---- items of slice s007fd840 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* VCallR(void* o, int off) {
    return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCallV(void* o, int off) {
    ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline int VCallI(void* o, int off) {
    return ((int(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCallI1(void* o, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}
struct EvBase {
    void Ctor();                  // 0x7fc200
    void SetValue(int);           // 0x7f9ae0
};
struct Svr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(void*, unsigned);  // +0x20  register target
    virtual void v9();
    virtual void v10();
    virtual void v11(void*, unsigned, int); // +0x2c  unregister target
    virtual void v12();
};
bool  FUN_007fa520(void* arr, int n, void* counter);
void  FUN_007fb480(void* self, int v);
void* EA_Messaging_GetServer();   // 0x00883860 (equiv t2)
void  FUN_00951330(void* p);      // 0x00951330 (MultiHeapObject::operator delete)
struct C_7fc200 { void Dtor(); };// 0x007fc200 (thiscall, no args)
struct SerItem { void* type; void* base; unsigned count; void* extra; };
extern EA::UTFWin::SerTypeInfo gBoolStateEventSerTypeInfo; // 0x014161f4: bool state event type record
struct Sec5 {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5(); // +0x14
};
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
    void SetWinMessageType(unsigned t);
    void SetMessageWinId(unsigned id);
};
struct BoolEvent {
    char Pred(char a, char b);
};
// ---- items of slice s007fd840 end

// ---- items of slice s007fed20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vt_we_a[], vt_we_b[], vt_we_c[], vt_we_d[], vt_we_e[];  // 0x14161c4 0x14161ac 0x14162a4 0x141619c 0x1416140
extern char vt_wb_a[], vt_wb_b[], vt_wb_c[], vt_wb_d[], vt_wb_e[];  // 0x14162cc 0x14162b4 0x14162a4 0x1416294 0x1416238
inline void VCallPP(void* o, int off, void* a, void* b) {
    ((void(__thiscall*)(void*, void*, void*))(*(void**)((char*)*(void**)o + off)))(o, a, b);
}
inline void* VCallPR(void* o, int off, int a) {
    return ((void*(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}
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
struct WinEvent_s007f_ed20 {
    char pad0[0x7c];
    char mbMessageTargetRegistered; // +0x7c
    unsigned mMessageType;          // +0x80
    unsigned mMessageWinId;         // +0x84
    char mbBroadcastMode;           // +0x88
    char mbOrigialVisibility;       // +0x89
    WinEvent_s007f_ed20* Ctor(unsigned type, unsigned winId, bool broadcast);
};
struct WinBoolStateEvent : WinEvent_s007f_ed20 {
    char pad8c[0x4];                // +0x8c
    WinBoolStateEvent* Ctor(unsigned a, unsigned type, unsigned winId, bool broadcast);
};
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
// ---- items of slice s007fed20 end

// @ 0x007fe7a0
bool WinEvent::IsThisType()
{
    return *(int*)((char*)this + 0x68) == 0x25a5f84;
}

// @ 0x007fe7d0
char BoolEvent::Pred(char a, char b)
{
    void* self = this;
    int counter = -1;
    if (FUN_007fa520((char*)self + 0x1c, 4, &counter)) {
        void* w = (char*)self + 0x18;
        switch (*(unsigned*)((char*)self + 0x8c)) {
        case 0: if (a == 0 || b != 0) { VCallI1(w, 0x48, a == 0); return (char)(a == 0); } return 0;
        case 1: if (a != 0 || b != 0) { VCallI1(w, 0x48, a != 0); return a; } return 0;
        case 2: VCallI1(w, 0x48, a == 0); return 1;
        case 3: VCallI1(w, 0x48, a != 0); return 1;
        }
    }
    return 0;
}

// @ 0x007fe8c0
void BoolActivate(void* self, int v)
{
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

// @ 0x007fea90
void* WinEvent::DeletingDtor(unsigned char flags)
{
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

// @ 0x007fead0
bool WinEvent::IsWinState(unsigned v)
{
    if (mMessageWinId == 0x7fffffff) {
        void* p = mVtbl14;
        return p && ((unsigned(__thiscall*)(void*))(*(void***)p)[7])(p) == v;
    }
    return mMessageWinId == v ? 1 : 0;
}

// @ 0x007feb40
bool SerReadB(SerItem* out, void* src)
{
    void* p = *(void**)((char*)src + 4);
    ((Sec5*)((char*)p + 4))->s5();
    out->base = p;
    out->count = 1;
    out->type = &gBoolStateEventSerTypeInfo;
    return true;
}

// @ 0x007feb70
void SerUpdateWin(void* self)
{
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

// @ 0x007fec00
void WinEvent::SetWinMessageType(unsigned t)
{
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
void WinEvent::SetMessageWinId(unsigned id)
{
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

// @ 0x007fed20
bool EvE::CreateBehaviorMessage(void** out, unsigned kind, void* a3)
{
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

// @ 0x007ff0d0
bool WinEventW::HandleMessage(unsigned msg, void* arg)
{
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
bool WinEventW::BoolHandleMessage(unsigned msg, void* arg)
{
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

// @ 0x007ff400
WinEvent_s007f_ed20* WinEvent_s007f_ed20::Ctor(unsigned type, unsigned winId, bool broadcast)
{
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
WinBoolStateEvent* WinBoolStateEvent::Ctor(unsigned a, unsigned type, unsigned winId, bool broadcast)
{
    (void)a;
    ((WinEvent_s007f_ed20*)this)->Ctor(type, winId, broadcast);
    *(void**)((char*)this + 0x00) = (void*)vt_wb_a;
    *(void**)((char*)this + 0x04) = (void*)vt_wb_b;
    *(void**)((char*)this + 0x08) = (void*)vt_wb_c;
    *(void**)((char*)this + 0x10) = (void*)vt_wb_d;
    *(void**)((char*)this + 0x18) = (void*)vt_wb_e;
    *(int*)((char*)this + 0x8c) = 3;
    return this;
}
