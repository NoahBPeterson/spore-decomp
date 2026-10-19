// slice s007f9550: /Od cSPUIBehaviorEventBase region.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct Ev {
    void* AsA(int id);      // @ 0x007f97a0
    void* AsB(int id);      // @ 0x007f9800
    void* Sub10();          // @ 0x007f9860
    void* AsC(int id);      // @ 0x007f9890
    bool  Set14(int value); // @ 0x007f99c0
    void* AsD(int id);      // @ 0x007f99e0
    void* Sub0C();          // @ 0x007f9b50
    bool  Test1();          // @ 0x007f9b90
    void* AsE(int id);      // @ 0x007f9bb0
    bool  False();          // @ 0x007fa120
    void  Call93a0();       // @ 0x007fa130
    uint32_t Flags();       // @ 0x007fa150
    void* AsInterface(int id); // @ 0x007fa180
    Ev*   SetGlobal();      // @ 0x007fa350
    void  ClearGlobal();    // @ 0x007fa370
    bool  Eval();           // @ 0x007f9550
    int** SlotB(int i);     // FUN_007f93b0
    int** SlotC(int i);     // FUN_007f93c0
    int** SlotD(int i);     // FUN_007f93d0
};

struct EvSub { void M(); uint32_t ExtFlags(); };

struct Cont;
struct Iface {                 // cISPUIBehaviorEvent subobject at container+0x18
    bool RemovePredicate(void* pred); // @ 0x007f9ee0
    bool RemoveAction(void* act);     // @ 0x007f9f60
    bool RemoveAllPredicates();       // @ 0x007f9fe0
    bool RemoveAllActions();          // @ 0x007fa060
};

struct Cont {                  // cSPUIBehaviorEventBase
    int** SlotB(int i);        // FUN_007f93b0
    int** SlotC(int i);        // FUN_007f93c0
    int** SlotD(int i);        // FUN_007f93d0
    void  Refresh();           // @ 0x007f9a40
    bool  SetValue(int v);     // @ 0x007f9ae0
    bool  AddB(void* obj);     // @ 0x007f9c10
    bool  RemoveB(void* obj);  // @ 0x007f9c90
    bool  RemoveAllB();        // @ 0x007f9d00
};

inline void* VCallR(void* o, int off) {
    return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCall1(void* o, int off, void* a) {
    ((void(__thiscall*)(void*, void*))(*(void**)((char*)*(void**)o + off)))(o, a);
}

// @ 0x007f9a40
void Cont::Refresh() {
    for (int i = 0; i < 4; ++i) {
        int** slot = SlotB(i);
        if (*slot != 0) {
            int r = (int)VCallR(*slot, 0x2c);
            if (r != *(int*)((char*)this + 0x38)) {
                VCall1(*slot, 0x30, (void*)(*(int*)((char*)this + 0x38)));
            }
        }
    }
    *(int*)((char*)this + 0x34) = -1;
}

// @ 0x007f9ae0
bool Cont::SetValue(int v) {
    *(int*)((char*)this + 0x38) = v;
    for (int i = 0; i < 4; ++i) {
        int** slot = SlotB(i);
        if (*slot != 0) {
            VCall1(*slot, 0x30, (void*)v);
        }
    }
    return true;
}

// @ 0x007f9c10
bool Cont::AddB(void* obj) {
    for (int i = 0; i < 4; ++i) {
        int** slot = SlotB(i);
        if (*slot == 0) {
            *slot = (int*)obj;
            VCallR(obj, 0);
            VCall1(obj, 0x30, (void*)(*(int*)((char*)this + 0x38)));
            return true;
        }
    }
    return false;
}

// @ 0x007f9c90
bool Cont::RemoveB(void* obj) {
    for (int i = 0; i < 4; ++i) {
        int** slot = SlotB(i);
        if (*slot == (int*)obj) {
            VCall1(obj, 0x30, 0);
            VCallR(obj, 4);
            *slot = 0;
            return true;
        }
    }
    return false;
}

// @ 0x007f9d00
bool Cont::RemoveAllB() {
    for (int i = 0; i < 4; ++i) {
        if (*SlotB(i) != 0) {
            VCall1((void*)*SlotB(i), 0x30, 0);
            VCallR((void*)*SlotB(i), 4);
            *SlotB(i) = 0;
        }
    }
    return true;
}


// @ 0x007f9ee0
bool Iface::RemovePredicate(void* pred) {
    for (int i = 0; pred != 0 && i < 4; ++i) {
        int** slot = ((Cont*)((char*)this - 0x18))->SlotC(i);
        if (*slot == (int*)pred) {
            VCall1(pred, 0x30, 0);
            VCallR(pred, 4);
            *slot = 0;
            return true;
        }
    }
    return false;
}

// @ 0x007f9f60
bool Iface::RemoveAction(void* act) {
    for (int i = 0; act != 0 && i < 4; ++i) {
        int** slot = ((Cont*)((char*)this - 0x18))->SlotD(i);
        if (*slot == (int*)act) {
            VCall1(act, 0x28, 0);
            VCallR(act, 4);
            *slot = 0;
            return true;
        }
    }
    return false;
}

// @ 0x007f9fe0
bool Iface::RemoveAllPredicates() {
    for (int i = 0; i < 4; ++i) {
        int** slot = ((Cont*)((char*)this - 0x18))->SlotC(i);
        if (*slot != 0) {
            VCall1((void*)*slot, 0x30, 0);
            VCallR((void*)*slot, 4);
            *slot = 0;
        }
    }
    return true;
}

// @ 0x007fa060
bool Iface::RemoveAllActions() {
    for (int i = 0; i < 4; ++i) {
        int** slot = ((Cont*)((char*)this - 0x18))->SlotD(i);
        if (*slot != 0) {
            VCall1((void*)*slot, 0x28, 0);
            VCallR((void*)*slot, 4);
            *slot = 0;
        }
    }
    return true;
}

extern "C" int* __cdecl FUN_007fa4c0(int* p, int v);
extern "C" void __cdecl FUN_007fa4f0(int p, int a2, int p3);
void* g_evGlobal = 0;


// @ 0x007f97a0
void* Ev::AsA(int id) {
    int v = id;
    if (v == (int)0xeec58382) return this;
    if (v == (int)0xae9cb0fa) return this;
    if (v == (int)0xee3f516e) return this;
    if (v == (int)0x0243a853) return this;
    return 0;
}

// @ 0x007f9800
void* Ev::AsB(int id) {
    if (id == (int)0xeec58382) return this;
    if (id == (int)0xae9cb0fa) return this;
    if (id == (int)0xee3f516e) return this;
    if (id == (int)0x0243c076) return this;
    return 0;
}

// @ 0x007f9860
void* Ev::Sub10() {
    return this ? (void*)((char*)this + 0x10) : 0;
}

// @ 0x007f9890
void* Ev::AsC(int id) {
    if (id == (int)0xeec58382) return this ? (void*)((char*)this + 4) : 0;
    if (id == (int)0xae9cb0fa) return this ? (void*)((char*)this + 4) : 0;
    if (id == (int)0xee3f516e) return this ? (void*)((char*)this + 4) : 0;
    if (id == (int)0x2f009dd0) return this;
    return 0;
}

// @ 0x007f99c0
bool Ev::Set14(int value) {
    *(int*)((char*)this + 0x14) = value;
    return true;
}

// @ 0x007f99e0
void* Ev::AsD(int id) {
    if (id == (int)0xeec58382) return this;
    if (id == (int)0xae9cb0fa) return this;
    if (id == (int)0xee3f516e) return this;
    if (id == (int)0x024b5c98) return this;
    return 0;
}

// @ 0x007f9b50
void* Ev::Sub0C() {
    return this ? (void*)((char*)this + 0x0c) : 0;
}

// @ 0x007f9b90
bool Ev::Test1() {
    return (*(uint32_t*)((char*)this + 0x10) & 1) != 0;
}

// @ 0x007f9bb0
void* Ev::AsE(int id) {
    if (id == (int)0xeec58382) return this;
    if (id == (int)0xae9cb0fa) return this;
    if (id == (int)0xee3f516e) return this;
    if (id == (int)0x02439c2f) return this;
    return 0;
}

// @ 0x007fa120
bool Ev::False() {
    return false;
}

// @ 0x007fa130
void Ev::Call93a0() {
    ((EvSub*)this)->M();
}

// @ 0x007fa150
uint32_t Ev::Flags() {
    bool c = *(bool*)((char*)this + 0x5c);
    uint32_t part = -(uint32_t)(c != 0) & 2u;
    return (((EvSub*)this)->ExtFlags() & 0xfffffffd) | part;
}

// @ 0x007fa180
void* Ev::AsInterface(int id) {
    void* r;
    if (id == (int)0x2f009dd0) {
        r = this ? (void*)((char*)this + 0x18) : 0;
    } else {
        r = AsC(id);
    }
    return r;
}

// @ 0x007fa350
Ev* Ev::SetGlobal() {
    g_evGlobal = this;
    return this;
}

// @ 0x007fa370
void Ev::ClearGlobal() {
    g_evGlobal = 0;
}

// @ 0x007fa4c0
int* FUN_007fa4c0(int* p, int v) {
    p[0xc] = v;
    p[2] = 0;
    ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)p + 4)))(p);
    return p;
}

// @ 0x007fa4f0
void FUN_007fa4f0(int p, int a2, int p3) {
    *(int*)((char*)p + 0x10) = a2;
    *(int*)((char*)p + 0x18) = p3;
    FUN_007fa4c0((int*)p, *(int*)((char*)p3 + 8));
}

// @ 0x007f9550
bool Ev::Eval() {
    *(char*)((char*)this + 0x3a) = 0;
    VCallR(this, 0x24);
    float* p8 = (float*)((char*)this + 0x20);
    float* p9 = (float*)((char*)this + 0x24);
    if (*p8 <= 0.0f && *p8 != 0.0f) *p8 = 0.0f;
    if (*p9 <= 0.0f && *p9 != 0.0f) *p9 = 0.0f;
    if (0.0f <= *p8 || 0.0f <= *p9) {
        if (1.0f < *p8) *p8 = 1.0f;
        if (1.0f < *p8 + *p8) *p9 = 1.0f - *p8;
    } else {
        *p9 = 0.0f;
        *p8 = 0.0f;
    }
    float* p6 = (float*)((char*)this + 0x18);
    float* p7 = (float*)((char*)this + 0x1c);
    if (*p6 <= 0.0f && *p6 != 0.0f) *p6 = 0.0f;
    if (*p7 <= 0.0f && *p7 != 0.0f) *p7 = 0.0f;
    if (0.0f <= *p6 || 0.0f <= *p7) {
        if (1.0f < *p6) *p6 = 1.0f;
        if (1.0f < *p6 + *p6) *p7 = 1.0f - *p6;
    } else {
        *p7 = 0.0f;
        *p6 = 0.0f;
    }
    float* p3 = (float*)((char*)this + 0x0c);
    if (*p3 <= 0.0f && *p3 != 0.0f) *p3 = 1.0e9f;
    *(float*)((char*)this + 0x40) = *p3 * *p8;
    *(float*)((char*)this + 0x44) = (1.0f - *p9) * *p3;
    float* p4 = (float*)((char*)this + 0x10);
    if (*p4 <= 0.0f && *p4 != 0.0f) *p4 = 0.0f;
    return true;
}

// @ 0x007fa390
extern "C" void* __cdecl EA_Messaging_GetServer();
extern "C" void __cdecl FUN_00e4a9c0(void*);
int __cdecl FUN_007fa390(uint32_t msg, void* data, char flag) {
    if (msg < 0x1d) {
        void* srv = EA_Messaging_GetServer();
        if (flag == '\0') VCall1(srv, 0x18, 0);
        else VCall1(srv, 0x14, 0);
    }
    bool special = (msg == 0x25a5f95);
    if (msg >= 0x25a5f96) {
        special = (msg == 0x25a5f9a || msg == 0x25a61c5 || msg == 0x25c8cb3);
    } else if (msg < 0x25a5f85) {
        special = (msg == 0x25a5f84 || msg == 0x249f699 || msg == 0x25a5f5a);
    } else {
        special = (msg == 0x25a5f8e);
    }
    if (!special) return 1;
    FUN_00e4a9c0(data);
    void* srv = EA_Messaging_GetServer();
    if (flag == '\0') VCall1(srv, 0x18, 0);
    else VCall1(srv, 0x14, 0);
    return 1;
}

// Complete cSPUIBehaviorEventBase model (MI: primary base 0x18 bytes, cISPUIBehaviorEvent at +0x18).
struct B0 { virtual void b0(); uint32_t pad[5]; };
struct IfB;
struct PredO { virtual void AddRef(); virtual void Release();
  virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void* GetOwner(); virtual void SetOwner(IfB*); };
struct ActO { virtual void AddRef(); virtual void Release();
  virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual bool IsStarted(); virtual void SetStarted(bool);
  virtual void v8(); virtual void* GetOwner(); virtual void SetOwner(IfB*); };
struct IfB { virtual bool AddPredicate(PredO*) = 0; virtual bool AddAction(ActO*) = 0; };
struct CB : B0, IfB {
    PredO** SlotC(int i);
    ActO** SlotD(int i);
    bool AddPredicate(PredO* pred);
    bool AddAction(ActO* act);
    void SerUpdate();
    char fill[0x5c - 0x1c];
    bool mActive;
    int mLast;
};

// @ 0x007f9d90
bool CB::AddPredicate(PredO* pred) {
    for (int i = 0; i < 4; ++i) {
        PredO** slot = SlotC(i);
        if (*slot == 0) {
            *slot = pred;
            (*slot)->AddRef();
            (*slot)->SetOwner(this);
            return true;
        }
    }
    return false;
}

// @ 0x007f9e20
bool CB::AddAction(ActO* act) {
    for (int i = 0; i < 4; ++i) {
        ActO** slot = SlotD(i);
        if (*slot == 0) {
            *slot = act;
            act->AddRef();
            act->SetOwner(this);
            if (mActive) {
                if (!act->IsStarted()) act->SetStarted(true);
            }
            return true;
        }
    }
    return false;
}

// @ 0x007fa1d0
void CB::SerUpdate() {
    for (int i = 0; i < 4; ++i) {
        PredO** slot = SlotC(i);
        if (*slot != 0) {
            if ((*slot)->GetOwner() != (IfB*)this) {
                (*slot)->SetOwner(this);
            }
        }
    }
    for (int j = 0; j < 4; ++j) {
        ActO** slot = SlotD(j);
        if (*slot != 0) {
            if ((*slot)->GetOwner() != (IfB*)this) {
                (*slot)->SetOwner(this);
                if (mActive) {
                    if (!(*slot)->IsStarted()) (*slot)->SetStarted(true);
                }
            }
        }
    }
    mLast = -1;
}
