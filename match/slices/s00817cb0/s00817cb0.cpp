// Slice s00817cb0 (batch w2g7 #6), 32-bit MSVC 2008.
// cSPUIPieMenuItem / cSPUIPieMenu and helpers.

typedef unsigned int  u32;
typedef unsigned char u8;

struct IWindow;

static inline void Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void Vv1(void* p, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void Vv2(void* p, int off, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
static inline int Vi0(void* p, int off) {
    return ((int(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void* Vcp0(void* p, int off) {
    return ((void*(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline char Vb1(void* p, int off, int a) {
    return ((char(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void* Vcp1(void* p, int off, int a) {
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void* Vcp2(void* p, int off, int a, int b) {
    return ((void*(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
static inline void Vv5(void* p, int off, int a, int b, int c, int d, int e) {
    ((void(__thiscall*)(void*, int, int, int, int, int))(*(void***)p)[off / 4])(p, a, b, c, d, e);
}

extern "C" void SPUIHelpers_UpdateMouseFocus(int);
extern "C" void SPKeyFromName(void* out, void* name, u32, void*);
extern "C" void FUN_00817fa0(void*, int);

// cSPUIPieMenuItem layout (PDB, size 0x30)
struct cSPUIPieMenuItem {
    void**    vftable;          // +0x00
    u32       mID;              // +0x04
    IWindow*  mpCurrentWindow;  // +0x08
    char      pad_0c[0x14 - 0x0c];
    u32       mFlags;           // +0x14
    char      pad_18[0x1c - 0x18];
    void*     mpLHSWindowSet;   // +0x1c
    void*     mpRHSWindowSet;   // +0x20
    void*     mpIconWindow;     // +0x24
    void*     mpParentWin;      // +0x28
    void*     mpWinProc;        // +0x2c

    void SetIcon(int);          // 00818000
    void SetTextColor(int);     // 00817ee0
    void SetId(u32);            // 008188d0
    void MarkUnused();          // 00818950
    bool SetPos(int, int);      // 00817eb0
    void sub817fa0(int);        // 00817fa0
};

// cSPUIPieMenu::cItemInfo (0x4c) embeds the item's fields at the front
struct cItemInfo {
    cSPUIPieMenuItem item;
    char             pad_30[0x4c - 0x30];
};
struct Sub30 {
    char pad_00[0x18];
    int  f18;   // +0x18
    int  f1c;   // +0x1c
};

// @ 0x00817eb0
bool cSPUIPieMenuItem::SetPos(int a, int b) {
    *(int*)((char*)this + 0x64) = a;
    *(int*)((char*)this + 0x68) = b;
    return true;
}

// @ 0x00818370
struct WinProcHolder {
    char      pad_00[0x24];
    IWindow*  mW24;   // +0x24
    bool has(IWindow* w);
};
bool WinProcHolder::has(IWindow* w) {
    bool result = false;
    if (w) {
        if (w != mW24) {
            if (!Vb1(mW24, 0xf8, (int)w)) return false;
        }
        result = true;
    }
    return result;
}

// @ 0x00818330
struct Holder2 {
    char     pad_00[0x24];
    IWindow* mW24;   // +0x24
    char     pad_28[0xb0 - 0x28];
    void*    mWb0;   // +0xb0
    void teardown();
};
void Holder2::teardown() {
    if (mW24) Vv2(mW24, 0x7c, 1, 0);
    if (mWb0) { void* q = mWb0; mWb0 = 0; Vv0(q, 0x04); }
    SPUIHelpers_UpdateMouseFocus(1);
}

// @ 0x00818950
void cSPUIPieMenuItem::MarkUnused() {
    *(u32*)(*(int*)((char*)this + 0x30) + 0x10) = 0xffffffff;
    if (mID != 0xffffffff) {
        SetIcon(0);
        mID = 0xffffffff;
        if (mpCurrentWindow) {
            int r = Vi0(mpCurrentWindow, 0x10);
            if (r) Vv1(mpWinProc, 0xdc, (int)mpCurrentWindow);
        }
        mFlags = 3;
    }
}

// @ 0x00817fa0
void cSPUIPieMenuItem::sub817fa0(int color) {
    IWindow* w = (IWindow*)Vcp2(mpRHSWindowSet, 0xf0, 0x122a5c7, 1);
    if (w) {
        Vv2(w, 0x7c, 2, color);
        w = (IWindow*)Vcp2(mpIconWindow, 0xf0, 0x122a5c7, 1);
        if (w) Vv2(w, 0x7c, 2, color);
    }
}

// @ 0x008182c0
struct PieMenu02 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    bool assign(int a, int b);
};
bool PieMenu02::assign(int a, int b) {
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        Sub30* s = *(Sub30**)((char*)mpBegin + i * 0x4c + 0x30);
        s->f18 = a;
        s->f1c = b;
    }
    return true;
}

// @ 0x008181e0
struct PieMenu03 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    void setColor(u32 id, int color);
};
void PieMenu03::setColor(u32 id, int color) {
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem* it = (cSPUIPieMenuItem*)((char*)mpBegin + i * 0x4c);
        if (it->mID == 0xffffffff || it->mID != id) continue;
        it->sub817fa0(color);
    }
}

// @ 0x00818250
struct PieMenu04 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    char       pad_14[0x5c - 0x14];
    u8         b5c;      // +0x5c
    bool setTextColor(u32 id, int color);
};
bool PieMenu04::setTextColor(u32 id, int color) {
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem* it = (cSPUIPieMenuItem*)((char*)mpBegin + i * 0x4c);
        if (it->mID == id) {
            b5c = 1;
            it->SetTextColor(color);
            return true;
        }
    }
    return false;
}

// @ 0x008188d0
void cSPUIPieMenuItem::SetId(u32 id) {
    IWindow* p = mpCurrentWindow;
    *(u32*)((char*)mpWinProc + 0x10) = id;
    if (id == mID) return;
    SetIcon(0);
    mID = id;
    if (id == 0xffffffff) {
        if (p) {
            if (Vi0(p, 0x10))
                Vv1(mpWinProc, 0xdc, (int)mpCurrentWindow);
        }
    } else {
        if (p) {
            if (Vi0(p, 0x10) == 0) {
                Vv1(mpWinProc, 0xd8, (int)mpCurrentWindow);
                mFlags = 3;
                return;
            }
        }
    }
    mFlags = 3;
}

// @ 0x00817ee0
void cSPUIPieMenuItem::SetTextColor(int color) {
    if (!color) return;
    IWindow* w = (IWindow*)Vcp1(mpRHSWindowSet, 0xf0, 0x122d76c);
    if (!w) return;
    w = (IWindow*)Vcp1(w, 0x0c, 0xf15f4bd);
    if (!w) return;
    Vv1(w, 0x28, color);
    void* q = Vcp0(w, 0x10);
    Vv0(q, 0x90);
    w = (IWindow*)Vcp1(mpIconWindow, 0xf0, 0x122d76c);
    if (!w) return;
    w = (IWindow*)Vcp1(w, 0x0c, 0xf15f4bd);
    if (!w) return;
    Vv1(w, 0x28, color);
    q = Vcp0(w, 0x10);
    Vv0(q, 0x90);
}

// @ 0x00817e20
struct PieMenuInit {
    char pad_00[0x100];
    void Init(void* n1, void* n2, void* p4, void* p5, void* p6, void* p7);
};
void PieMenuInit::Init(void* n1, void* n2, void* p4, void* p5, void* p6, void* p7) {
    u32 key1[3] = {0, 0, 0};
    u32 key2[3] = {0, 0, 0};
    if (n1) SPKeyFromName(key1, n1, 0x510a95b, p4);
    if (n2) SPKeyFromName(key2, n2, 0x510a95b, p4);
    Vv5(this, 0x20, (int)key1, (int)key2, (int)p4, (int)p5, (int)p6);
}

// ===========================================================================
// incomplete / approximate (see partial.txt)
// ===========================================================================
struct PieStub {
    char pad_00[0x4000];
    void a() { *(volatile int*)pad_00 = 0; }
};
void stub_817cb0(PieStub* p) { p->a(); }
void stub_817d70(PieStub* p) { p->a(); }
void stub_818000(PieStub* p) { p->a(); }
void stub_8183a0(PieStub* p) { p->a(); }
void stub_818500(PieStub* p) { p->a(); }
void stub_818650(PieStub* p) { p->a(); }
void stub_8186f0(PieStub* p) { p->a(); }
void stub_818820(PieStub* p) { p->a(); }
