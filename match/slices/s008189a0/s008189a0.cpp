// Slice s008189a0 (batch w2g7 #7), 32-bit MSVC 2008.
// cSPUIPieMenuItem / cSPUIPieMenu.

typedef unsigned int  u32;
typedef unsigned char u8;

struct IWindow;

static inline void Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void Vv1(void* p, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline int Vi0(void* p, int off) {
    return ((int(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void* Vcp1(void* p, int off, int a) {
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}

extern "C" void SPUIHelpers_UpdateMouseFocus(int);
extern "C" void FUN_008186f0(void*);
extern "C" void FUN_00819880_p();

struct cSPUIPieMenuItem {
    void**   vftable;          // +0x00
    u32      mID;              // +0x04
    IWindow* mpCurrentWindow;  // +0x08
    char     pad_0c[0x14 - 0x0c];
    u32      mFlags;           // +0x14
    char     pad_18[0x1c - 0x18];
    void*    mpLHSWindowSet;   // +0x1c
    void*    mpRHSWindowSet;   // +0x20
    void*    mpIconWindow;     // +0x24
    void*    mpParentWin;      // +0x28
    void*    mpWinProc;        // +0x2c

    void SetIcon(int);          // 00818000
    void Update();              // 008189a0
    void MarkUnused();          // 00818950 (slice 6)
    bool sub8191b0();           // 008191b0
    void dtor819880();          // 00819880
    void SetOrientation(bool, bool); // 008192e0
};

// @ 0x008191b0
bool cSPUIPieMenuItem::sub8191b0() {
    MarkUnused();
    mpCurrentWindow = 0;
    { void* q = mpRHSWindowSet;  if (q) { mpRHSWindowSet = 0;  Vv0(q, 0x04); } }
    { void* q = mpIconWindow;    if (q) { mpIconWindow = 0;    Vv0(q, 0x04); } }
    { void* q = mpParentWin;     if (q) { mpParentWin = 0;     Vv0(q, 0x04); } }
    { void* q = mpWinProc;       if (q) { mpWinProc = 0;       Vv0(q, 0x04); } }
    { void* q = *(void**)((char*)this + 0x30);
      if (q) { *(void**)((char*)this + 0x30) = 0; Vv0(q, 0x04); } }
    return true;
}

// @ 0x00819880
void cSPUIPieMenuItem::dtor819880() {
    vftable = (void**)0x1418ef8;
    sub8191b0();
    void* q;
    q = *(void**)((char*)this + 0x30); if (q) Vv0(q, 0x04);
    q = mpWinProc;    if (q) Vv0(q, 0x04);
    q = mpParentWin;  if (q) Vv0(q, 0x04);
    q = mpIconWindow; if (q) Vv0(q, 0x04);
    q = mpRHSWindowSet; if (q) Vv0(q, 0x04);
    q = mpLHSWindowSet; if (q) Vv0(q, 0x04);
}

// @ 0x008192e0
void cSPUIPieMenuItem::SetOrientation(bool vert, bool update) {
    void** slot = vert ? &mpRHSWindowSet : &mpIconWindow;
    IWindow* w = (IWindow*)*slot;
    if (mpCurrentWindow != w) {
        if (mpCurrentWindow) {
            if (Vi0(mpCurrentWindow, 0x10))
                Vv1(mpWinProc, 0xdc, (int)mpCurrentWindow);
        }
        mpCurrentWindow = w;
        if (mID != 0xffffffff)
            Vv1(mpWinProc, 0xd8, (int)w);
        mFlags |= 2;
        if (update) Update();
        IWindow* parent = (IWindow*)mpParentWin;
        SetIcon(0);
        SetIcon((int)parent);
    }
}

// ---- cSPUIPieMenu (partial layout) ----------------------------------------
struct cSPUIPieMenu {
    char     pad_00[0xc];
    char*    mpBegin;   // +0xc
    char*    mpEnd;     // +0x10
    char     pad_14[0x20 - 0x14];
    int      mItemCount;// +0x20 (used as a count in this build)
    char     pad_24[0x5c - 0x24];
    u8       b5c;       // +0x5c

    void RemoveItem();  // 00818c80
};

// @ 0x00818c80
void cSPUIPieMenu::RemoveItem() {
    for (u32 i = 0; i < (u32)((mpEnd - mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem* it = (cSPUIPieMenuItem*)(mpBegin + i * 0x4c);
        if (it->mID != 0xffffffff) {
            // MarkUnused() inlined by the original
            *(u32*)(*(int*)((char*)it + 0x30) + 0x10) = 0xffffffff;
            if (it->mID != 0xffffffff) {
                it->SetIcon(0);
                it->mID = 0xffffffff;
                if (it->mpCurrentWindow && Vi0(it->mpCurrentWindow, 0x10))
                    Vv1(it->mpWinProc, 0xdc, (int)it->mpCurrentWindow);
                it->mFlags = 3;
            }
            mItemCount += -1;
        }
    }
}

// ===========================================================================
// incomplete / approximate (see partial.txt)
// ===========================================================================
struct PieStub {
    char pad_00[0x8000];
    void a() { *(volatile int*)pad_00 = 0; }
};
void stub_8189a0(PieStub* p) { p->a(); }
void stub_818d20(PieStub* p) { p->a(); }
void stub_819360(PieStub* p) { p->a(); }
void stub_8190f0(PieStub* p) { p->a(); }
void stub_819150(PieStub* p) { p->a(); }
void stub_819220(PieStub* p) { p->a(); }
