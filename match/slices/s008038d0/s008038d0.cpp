// Slice s008038d0 (w2g6 #14), 32-bit MSVC 2008.
// Two classes:
//   DragDropCaptureWin (vtable 0x01417694)  : 008038d0..008045a0
//   UTFWin::cSPUIFrameSequencer (0x01417804 / secondary 0x01417790) : 00804620..008048c0

typedef unsigned int u32;
#include <intrin.h>

// --- external helpers (identities are relocations, so names are free) -------
extern "C" void* EA_UTFWin_GetManager();
extern "C" void* EA_Messaging_GetServer();
extern "C" void  SPUIHelpers_RemoveWindowCallback(void*, void*);
extern "C" void  SPUIHelpers_UpdateMouseFocus(int);
extern "C" void* FUN_009512c0();
extern "C" void* FUN_009512d0(int, int, const char*, void*);
extern "C" void* FUN_007f3160(void*);
extern "C" void  FUN_00804ed0(void*, void*);
extern "C" void  FUN_008085d0(void*, void*, int, int, void*);
extern "C" void  AutoRefCount_Assign(void**, void*);
extern "C" void  MultiHeapDelete(void*);
extern "C" void  AtExit013c0510();
extern "C" void  Fn803730();
extern "C" void  Fn803750();
extern "C" void  Fn803710_x();
extern "C" int   atexit(void (*)());

// generic virtual dispatch through the vtable at object+0
static inline void* VSlot(void* p, unsigned byteOff) { return (void*)&((void**)*(void**)p)[byteOff / 4]; }
static inline void AddRefObj(void* p) { (*(void(__thiscall**)(void*))VSlot(p, 0))(p); }
static inline void ReleaseObj(void* p) { (*(void(__thiscall**)(void*))VSlot(p, 4))(p); }

struct Variant {
    char d[0x10];
    void Destruct(int);
};

struct Event;

typedef void (*CbFn)(void*, Event*);

struct Cb {
    void* field0;   // +0x00
    void* ptr;      // +0x04  (refcounted)
    CbFn  fn;       // +0x08
    void* ctx;      // +0x0c
    bool  b10;      // +0x10
    bool  b11;      // +0x11

    bool Setup();                // 0x00803b40
    Cb& operator=(const Cb& o);  // 0x00803b70
};

struct Event {
    u32   type;  // +0x00
    float x;     // +0x04
    float y;     // +0x08
    int   id;    // +0x0c
    Cb*   cb;    // +0x10
    u32   z0;    // +0x14
    u32   z1;    // +0x18
    void* p;     // +0x1c
};

struct DragDropCaptureWin {
    void** vtable;  // +0x00
    Cb a;           // +0x04
    Cb b;           // +0x18
    float x;        // +0x2c
    float y;        // +0x30
    int id;         // +0x34
    void* win;      // +0x38
    void* p;        // +0x3c

    void Transition(int ev, Cb* cb);           // 0x00803790 (other slice)
    void Sub8038d0(int ev);                    // 0x008038d0
    void Dispose(bool b);                      // 0x00803bd0
    void Sub803e60();                          // 0x00803e60
    bool Sub8040e0(Cb* arg1, void* arg2);      // 0x008040e0
    bool OnEvent(int a, void* e);              // 0x008042f0
    void* ScalarDeletingDtor(char flags);      // 0x008044a0
    bool Sub8045a0(void* o, int v);            // 0x008045a0

    void SendEvent(Cb* cb, u32 type) {
        Event e;
        e.type = type; e.x = x; e.y = y; e.id = id;
        e.cb = cb; e.z0 = 0; e.z1 = 0; e.p = p;
        if (cb->b11) { cb->fn(cb->ctx, &e); cb->b11 = false; }
    }
};

// ===========================================================================
// 0x00803b40
bool Cb::Setup() {
    if (fn != 0) return true;
    if (ptr != 0) { ctx = ptr; fn = (CbFn)&Fn803750; return true; }
    if (field0 != 0) { ctx = field0; fn = (CbFn)&Fn803730; return true; }
    return false;
}

// 0x00803b70
Cb& Cb::operator=(const Cb& o) {
    field0 = o.field0;
    _ReadWriteBarrier();
    void* old = ptr;
    void* np = o.ptr;
    if (np != old) {
        if (np != 0) AddRefObj(np);
        ptr = np;
        if (old != 0) ReleaseObj(old);
    }
    fn = o.fn; ctx = o.ctx; b10 = o.b10; b11 = o.b11;
    return *this;
}

// 0x008038d0 : transition dispatcher
void DragDropCaptureWin::Sub8038d0(int ev) {
    Cb* A = &a;
    Cb* B = &b;
    if (a.fn != b.fn || a.ctx != b.ctx) {
        if (ev == 0x7be2447) {
            Transition(ev, B);
            SendEvent(B, 0x7be2446);
            SendEvent(A, 0x7be2446);
            return;
        }
        if (b.b10 == 0) {
            if (ev == 0x7be2445) { Transition(ev, A); return; }
            if (ev == 0x7be2444 || ev == 0x7be2446) { Transition(ev, A); Transition(ev, B); }
            return;
        }
        if (ev == 0x7be2444) { Transition(ev, B); SendEvent(A, 0x7be2446); return; }
        if (ev == 0x7be2445) { Transition(ev, B); SendEvent(A, 0x7be2446); return; }
        if (ev == 0x7be2446) { Transition(ev, B); Transition(0x7be2444, A); return; }
        return;
    }
    Transition(ev, A);
    if (ev != 0x7be2447) return;
    SendEvent(A, 0x7be2446);
}

// 0x00803bd0
void DragDropCaptureWin::Dispose(bool bArg) {
    if (a.fn != 0) {
        if (bArg) Sub8038d0(0x7be2447);
        SendEvent(&a, 0x7be2446);
        SendEvent(&b, 0x7be2446);
    }
    if (win != 0) {
        void* w = win;
        AddRefObj(w);
        if (win != 0) { void* old = win; win = 0; ReleaseObj(old); }
        SPUIHelpers_RemoveWindowCallback(w, (void*)&Fn803710_x);
        void* mgr = EA_UTFWin_GetManager();
        if (mgr != 0) {
            (*(void(__thiscall**)(void*, int, void*))VSlot(mgr, 0x5c))(mgr, 1, w);
            (*(void(__thiscall**)(void*, int, void*))VSlot(mgr, 0x5c))(mgr, 0, w);
            void* o = (*(void*(__thiscall**)(void*))VSlot(w, 0x10))(w);
            if (o != 0) {
                void* o2 = (*(void*(__thiscall**)(void*))VSlot(w, 0x10))(w);
                (*(void(__thiscall**)(void*, void*))VSlot(o2, 0xe0))(o2, w);
            }
            SPUIHelpers_UpdateMouseFocus(1);
            void** vt = (void**)*(void**)mgr;
            void* c = (*(void*(__thiscall**)(void*))&vt[1])(mgr);
            (*(void(__thiscall**)(void*, int, void*))&vt[0x4c / 4])(mgr, 0, c);
        }
        ReleaseObj(w);
    }
    if (a.fn != 0) {
        if (p != 0) AddRefObj(p);
        if (a.ptr != 0) AddRefObj(a.ptr);
        CbFn fn = a.fn;
        void* ctx = a.ctx;
        Event e;
        e.type = 0x7be2441; e.x = 0.0f; e.y = 0.0f; e.id = 0;
        e.cb = &a; e.z0 = 0; e.z1 = 0; e.p = p;
        void* oldp = p;
        if (p != 0) { p = 0; ReleaseObj(oldp); }
        Cb def; def.field0 = 0; def.ptr = 0; def.fn = 0; def.ctx = 0; def.b10 = true; def.b11 = false;
        a = def; b = def;
        fn(ctx, &e);
        void* srv = EA_Messaging_GetServer();
        (*(void(__thiscall**)(void*, int, Event*, int))VSlot(srv, 0x14))(srv, (int)e.type, &e, 0);
        if (a.ptr != 0) ReleaseObj(a.ptr);
        if (oldp != 0) ReleaseObj(oldp);
    }
}

// 0x00803e60
void DragDropCaptureWin::Sub803e60() {
    Cb lcb;
    lcb.field0 = 0; lcb.ptr = 0; lcb.fn = 0; lcb.ctx = 0; lcb.b10 = true; lcb.b11 = false;
    Event e;
    e.type = 0x7be2442; e.x = x; e.y = y; e.id = id;
    e.cb = &a; e.z0 = 0; e.z1 = 0; e.p = p;

    void* mgr = EA_UTFWin_GetManager();
    if (mgr != 0) {
        (*(void(__thiscall**)(void*, int, int))VSlot(win, 0x7c))(win, 0x10, 1);
        void* ctrl = (*(void*(__thiscall**)(void*, float*))VSlot(mgr, 0x44))(mgr, &x);
        (*(void(__thiscall**)(void*, int, int))VSlot(win, 0x7c))(win, 0x10, 0);
        if (ctrl != 0) {
            void* mgr2 = EA_UTFWin_GetManager();
            (*(void(__thiscall**)(void*, int, void*, int))VSlot(mgr2, 0x10))(mgr2, 0, &e, 0);
        }
    }
    if (lcb.fn == 0) {
        if (lcb.ptr == 0) {
            if (lcb.field0 == 0) {
                void* srv = EA_Messaging_GetServer();
                (*(void(__thiscall**)(void*, int, Event*, int))VSlot(srv, 0x14))(srv, 0x7be2442, &e, 0);
            } else { lcb.ctx = lcb.field0; lcb.fn = (CbFn)&Fn803730; }
        } else { lcb.ctx = lcb.ptr; lcb.fn = (CbFn)&Fn803750; }
        if (lcb.fn == 0) {
            if (lcb.ptr == 0) {
                if (lcb.field0 == 0) { a = lcb; }
                else { lcb.ctx = lcb.field0; lcb.fn = (CbFn)&Fn803730; }
            } else { lcb.ctx = lcb.ptr; lcb.fn = (CbFn)&Fn803750; }
        }
    }
    if (a.fn != lcb.fn || a.ctx != lcb.ctx) {
        if (a.fn != b.fn || a.ctx != b.ctx) {
            Event e2;
            e2.type = 0x7be2446; e2.x = x; e2.y = y; e2.id = id;
            e2.cb = &a; e2.z0 = 0; e2.z1 = 0; e2.p = p;
            if (b.b11) { b.fn(b.ctx, &e2); b.b11 = false; }
        }
        a = lcb;
        if (a.fn != b.fn || a.ctx != b.ctx) {
            if (b.b10 != 0) {
                Transition(0x7be2444, &b);
                SendEvent(&a, 0x7be2446);
                if (b.ptr != 0) ReleaseObj(b.ptr);
                return;
            }
            Transition(0x7be2444, &a);
            Transition(0x7be2444, &b);
        } else {
            Transition(0x7be2444, &b);
        }
    }
    if (b.ptr != 0) ReleaseObj(b.ptr);
}

// 0x008040e0
bool DragDropCaptureWin::Sub8040e0(Cb* arg1, void* arg2) {
    if (a.fn != 0) return false;
    void* mgr = EA_UTFWin_GetManager();
    if ((*(int(__thiscall**)(void*, int))VSlot(mgr, 0x54))(mgr, 1) != 0) return false;
    if ((*(int(__thiscall**)(void*, int))VSlot(mgr, 0x54))(mgr, 0) != 0) return false;
    a = *arg1;
    if (!a.Setup()) return false;
    AutoRefCount_Assign(&p, arg2);
    a.b10 = true;
    {
        Event e;
        e.type = 0x7be2440; e.x = 0.0f; e.y = 0.0f; e.id = 0;
        e.cb = &a; e.z0 = 0; e.z1 = 0; e.p = p;
        a.fn(a.ctx, &e);
        void* srv = EA_Messaging_GetServer();
        (*(void(__thiscall**)(void*, int, Event*, int))VSlot(srv, 0x14))(srv, (int)e.type, &e, 0);
    }
    void* x0 = FUN_009512c0();
    void* obj = FUN_009512d0(0x20c, 4, "DragDropCaptureWin", x0);
    if (obj != 0) {
        void* r = FUN_007f3160(obj);
        obj = (r != 0) ? (char*)r + 4 : 0;
    }
    AutoRefCount_Assign(&win, obj);
    void* w = win;
    (*(void(__thiscall**)(void*, void*))VSlot(w, 0x6c))(w, &a);
    (*(void(__thiscall**)(void*, int))VSlot(w, 0x50))(w, 0x7bf9347);
    {
        void* o = (*(void*(__thiscall**)(void*))VSlot(mgr, 4))(mgr);
        (*(void(__thiscall**)(void*, void*))VSlot(o, 0xd8))(o, w);
    }
    FUN_008085d0(w, (void*)&Fn803710_x, 0x41, 0, this);
    (*(void(__thiscall**)(void*, int, int))VSlot(w, 0x7c))(w, 0x40, 1);
    {
        void* o = (*(void*(__thiscall**)(void*))VSlot(w, 0x10))(w);
        (*(void(__thiscall**)(void*, void*))VSlot(o, 0xe8))(o, w);
    }
    {
        void* o = (*(void*(__thiscall**)(void*))VSlot(mgr, 4))(mgr);
        (*(void(__thiscall**)(void*, int, void*))VSlot(mgr, 0x4c))(mgr, 0, o);
    }
    (*(void(__thiscall**)(void*, int, void*))VSlot(mgr, 0x58))(mgr, 1, w);
    (*(void(__thiscall**)(void*, int, void*))VSlot(mgr, 0x58))(mgr, 0, w);
    id = 0;
    FUN_00804ed0(&x, &y);
    b = a;
    Sub8038d0(0x7be2444);
    return false;
}

// 0x008042f0 : event handler
bool DragDropCaptureWin::OnEvent(int arg, void* pe) {
    bool bVar1 = false;   // used as bl
    bool bVar2 = false;   // [esp+0xe]
    unsigned char flag10 = 0; // [esp+0x10]
    int* e = (int*)pe;
    switch (e[2]) {
    case 1:
        if (e[4] != 0x1b) return true;
        FUN_00804ed0(&x, &y);
        id = e[5];
        bVar1 = true; flag10 = 0;
        break;
    case 0x1c:
        bVar1 = true; flag10 = 0;
        break;
    case 2: case 5: case 9: case 10: case 0x1b:
        return true;
    case 3: case 4: case 11: case 12: case 13: case 14: case 15: case 16:
    case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24:
    case 25: case 26:
        return false;
    case 6: case 8:
        bVar2 = true;
        x = *(float*)&e[3];
        y = *(float*)&e[4];
        id = e[5];
        break;
    case 7:
        bVar1 = true;
        x = *(float*)&e[3];
        flag10 = 1;
        y = *(float*)&e[4];
        id = e[5];
        break;
    default:
        return false;
    }
    Sub803e60();
    if (bVar1) {
        Dispose(flag10 != 0);
        return true;
    }
    if (bVar2) {
        if (a.fn == b.fn && a.ctx == b.ctx) {
            Transition(0x7be2445, &a);
        } else if (b.b10 == 0) {
            Transition(0x7be2445, &a);
        } else {
            Transition(0x7be2445, &b);
            SendEvent(&a, 0x7be2446);
        }
    }
    return true;
}

// 0x008044a0 scalar deleting destructor
void* DragDropCaptureWin::ScalarDeletingDtor(char flags) {
    vtable = (void**)0x1417694;
    Dispose(false);
    if (p != 0) ReleaseObj(p);
    if (win != 0) ReleaseObj(win);
    if (b.ptr != 0) ReleaseObj(b.ptr);
    if (a.ptr != 0) ReleaseObj(a.ptr);
    if (flags & 1) MultiHeapDelete(this);
    return this;
}

// 0x008045a0
bool DragDropCaptureWin::Sub8045a0(void* o, int v) {
    Cb tmp;
    tmp.field0 = 0; tmp.ptr = 0; tmp.fn = 0; tmp.ctx = 0; tmp.b10 = true; tmp.b11 = false;
    if (o != 0) { AddRefObj(o); tmp.ptr = o; }
    bool r = Sub8040e0(&tmp, (void*)v);
    if (tmp.ptr != 0) ReleaseObj(tmp.ptr);
    return r;
}

// 0x00804500 dynamic initializer of the singleton (guard + atexit)
static DragDropCaptureWin g_ddcw;
static int g_ddcwGuard;
void* GetDragDropCaptureWin() {
    if ((g_ddcwGuard & 1) == 0) {
        g_ddcwGuard |= 1;
        g_ddcw.vtable = (void**)0x1417694;
        g_ddcw.a.field0 = 0; g_ddcw.a.ptr = 0; g_ddcw.a.fn = 0; g_ddcw.a.ctx = 0;
        g_ddcw.a.b10 = true; g_ddcw.a.b11 = false;
        g_ddcw.b.field0 = 0; g_ddcw.b.ptr = 0; g_ddcw.b.fn = 0; g_ddcw.b.ctx = 0;
        g_ddcw.b.b10 = true; g_ddcw.b.b11 = false;
        g_ddcw.x = 0.0f; g_ddcw.y = 0.0f; g_ddcw.id = 0; g_ddcw.win = 0; g_ddcw.p = 0;
        atexit(&AtExit013c0510);
    }
    return &g_ddcw;
}

// ===========================================================================
// UTFWin::cSPUIFrameSequencer
// ===========================================================================
struct Sec {
    void** vtable;          // +0x00
    float mTime;            // +0x04
    float mFrameTime;       // +0x08
    float mDuration;        // +0x0c
    float mOOFrameCount;    // +0x10
    float mOOFrameCountPP;  // +0x14
    float mFrameDuration;   // +0x18
    float mOOFrameDuration; // +0x1c
    int mDirection;         // +0x20
    int mEndingMode;        // +0x24
    int mFrameCount;        // +0x28
    int mCurrentFrame;      // +0x2c
    int mLoopCount;         // +0x30
    int mCurrentLoop;       // +0x34
    int mStateFlags;        // +0x38
    void* mpFS;             // +0x3c
    void* mpVisitor;        // +0x40
    Variant mContext;       // +0x44
    int mFlags2;            // +0x54

    int  Get0x18();          // 0x00804620
    int  Get0x1c();          // 0x00804640
    bool Set0x20(int);       // 0x00804660
    bool Zero0x28();         // 0x008046a0
    bool V0x2c();            // 0x008046c0
    bool V0x30();            // 0x008046f0
    unsigned Bit1();         // 0x00804710
    unsigned Bit0();         // 0x00804720
    unsigned Bit2();         // 0x00804830
    void SetBit2(int);       // 0x00804840
    unsigned Bit3();         // 0x00804860
};

struct cSPUIFrameSequencer {
    void** vtable;  // +0x00
    int mRefCount;  // +0x04
    Sec sec;        // +0x08
    void SetFrameRange(int, int, char);  // 0x00804730
    void DtorBody();                     // 0x008048c0
};

// 0x00804620
int Sec::Get0x18() {
    if (mpFS != 0) {
        if (((bool(__thiscall*)(void*))((void**)*(void**)mpFS)[9])(mpFS)) return 1;
    }
    return 0;
}

// 0x00804640
int Sec::Get0x1c() { return (int)mDuration; }

// 0x00804660
bool Sec::Set0x20(int n) {
    if (n <= 0) n = 1;
    float f = (float)n;
    float t = mOOFrameCount * f;
    mDuration = f;
    mFrameDuration = t;
    mOOFrameDuration = 1.0f / t;
    return true;
}

// 0x008046a0
bool Sec::Zero0x28() {
    mStateFlags = 0;
    mTime = 0.0f;
    mFrameTime = 0.0f;
    return true;
}

// 0x008046c0
bool Sec::V0x2c() {
    if (((bool(__thiscall*)(void*))((void**)*(void**)this)[0xe])(this)) {
        if (!((bool(__thiscall*)(void*))((void**)*(void**)this)[0xd])(this))
            mStateFlags |= 2;
    }
    return ((bool(__thiscall*)(void*))((void**)*(void**)this)[0xd])(this);
}

// 0x008046f0
bool Sec::V0x30() {
    if (((bool(__thiscall*)(void*))((void**)*(void**)this)[0xd])(this))
        mStateFlags &= ~2;
    return ((bool(__thiscall*)(void*))((void**)*(void**)this)[0xe])(this);
}

// 0x00804710
unsigned Sec::Bit1() { return ((unsigned)mStateFlags >> 1) & 1; }

// 0x00804720
unsigned Sec::Bit0() { return (unsigned)mStateFlags & 1; }

// 0x00804830
unsigned Sec::Bit2() { return ((unsigned)(int)(signed char)mStateFlags & 4) >> 2; }

// 0x00804840
void Sec::SetBit2(int b) {
    if (b != 1) { mStateFlags &= ~4; return; }
    mStateFlags |= 4;
}

// 0x00804860
unsigned Sec::Bit3() { return ((unsigned)mStateFlags >> 3) & 1; }

// 0x00804730
void cSPUIFrameSequencer::SetFrameRange(int p2, int p3, char p4) {
    if (sec.mpVisitor == 0) return;
    void* fs = sec.mpFS;
    int dir = sec.mDirection;
    int cur = sec.mCurrentFrame;
    int cnt = (*(int(__thiscall**)(void*))VSlot(fs, 0x10))(fs);
    int last = cnt - 1;
    if (p4) p2 += (p3 == 0) ? 1 : -1;
    typedef void (__thiscall *VisFn)(void*, void*, void*, int, int);
    VisFn vis = (VisFn)(*(void**)VSlot(fs, 0x20));
    void* buf = &sec.mContext;
    if (dir == p3) {
        if (dir == 0) {
            if (cur >= p2) { vis(fs, sec.mpVisitor, buf, p2, cur); return; }
            vis(fs, sec.mpVisitor, buf, p2, last);
            last = 0;
        } else {
            if (cur <= p2) { vis(fs, sec.mpVisitor, buf, p2, cur); return; }
            vis(fs, sec.mpVisitor, buf, p2, 0);
        }
    } else if (dir == 0) {
        vis(fs, sec.mpVisitor, buf, p2, 0);
        if (cur < 1) return;
        last = 1;
    } else {
        vis(fs, sec.mpVisitor, buf, p2, last);
        if (last <= cur) return;
        last = cnt - 2;
    }
    vis(fs, sec.mpVisitor, buf, last, cur);
}

// 0x008048c0
void cSPUIFrameSequencer::DtorBody() {
    vtable = (void**)0x1417804;
    sec.vtable = (void**)0x1417790;
    _ReadWriteBarrier();
    (*(void(__thiscall**)(void*, int))VSlot(&sec, 0x10))(&sec, 0);
    if ((sec.mFlags2 & 4) != 0) sec.mContext.Destruct(0);
    sec.vtable = (void**)0x13eb938;
    vtable = (void**)0x13ec458;
}
