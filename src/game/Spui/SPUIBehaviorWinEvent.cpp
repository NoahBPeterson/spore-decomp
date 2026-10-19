// src/game/Spui/SPUIBehaviorWinEvent.cpp -- migrated from slice(s) s007fed20, s007fd840 by tools/migrate/rewrite.py
// Object file: Spui/SPUIBehaviorWinEvent.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
void  FUN_007fc200(void*);
struct SerItem { void* type; void* base; unsigned count; void* extra; };
struct Sec5 {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5(); // +0x14
};
struct WinEvent {
    char pad0[0x7c];
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
    bool Pred(char a, char b);
};
// ---- items of slice s007fd840 end

// ---- items of slice s007fed20 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* FUN_007fc880(void* self, int msg, void* arg);
bool  FUN_007fead0(void* self, unsigned v);
void  FUN_00c463d0();
struct WinEvent_s007f_ed20 {
    char pad0[0x7c];
    bool mbMessageTargetRegistered;  // +0x7c
    unsigned mMessageType;           // +0x80
    unsigned mMessageWinId;          // +0x84
    char mbBroadcastMode;            // +0x88
    char mbOrigialVisibility;        // +0x89
};
// ---- items of slice s007fed20 end

// @ 0x007fe7a0
bool WinEvent::IsThisType()
{
    return *(int*)((char*)this + 0x68) == 0x25a5f84;
}

// @ 0x007fe7d0
bool BoolEvent::Pred(char a, char b)
{
    void* self = this;
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
    FUN_007fc200(self);
    (void)flags;
    return self;
}

// @ 0x007fead0
bool WinEvent::IsWinState(unsigned v)
{
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

// @ 0x007feb40
bool SerReadB(SerItem* out, void* src)
{
    void* p = *(void**)((char*)src + 4);
    ((Sec5*)((char*)p + 4))->s5();
    out->base = p;
    out->count = 1;
    out->type = 0;
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
int CreateBehaviorMessage(void* self, void** out, void* a, void* b)
{
    *out = 0;
    FUN_00c463d0();
    return 0;
}

// @ 0x007ff0d0
int WinEventHandleMessage(void* self, unsigned msg, void* arg)
{
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
int WinBoolHandleMessage(void* self, unsigned msg, void* arg)
{
    return WinEventHandleMessage(self, msg, arg);
}

// @ 0x007ff400
void WinEventCtor(WinEvent_s007f_ed20* self, unsigned type, unsigned winId, bool broadcast)
{
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
