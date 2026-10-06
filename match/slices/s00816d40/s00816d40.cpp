// Slice s00816d40 (batch w2g7 #5), 32-bit MSVC 2008.
// UI::CalloutMessageBox / cSPUIMessageBox helpers.
// Relocations are masked; externs only need the right convention/arity.

typedef unsigned int  u32;
typedef unsigned char u8;

// ---- external --------------------------------------------------------------
extern "C" u32   FNV1_String16(const wchar_t* s, u32 basis, int);
extern "C" void* SP_MovieSystem();
extern "C" void* FUN_0067de40();
extern "C" void  EA_Messaging_RemoveHandler(int, int, int, int, int);
extern "C" void* Property_GetBool();

// ---- vtable call helpers ---------------------------------------------------
static inline void Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void Vv1(void* p, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void Vv2(void* p, int off, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
static inline void* Vcp0(void* p, int off) {
    return ((void*(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline char Vb0(void* p, int off) {
    return ((char(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline char Vb2(void* p, int off, int a, int b) {
    return ((char(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}

struct EString {
    EString& operator=(const EString&);
    void     Load(u32, u32, const wchar_t*);
};

struct cSPUILayout {
    char  pad_00[0x0c];
    void* FindWindowByID(u32 id, int arg);
    void  Shutdown(int arg);
    void  Init(u32 a, int b, int c, const wchar_t* s);
    ~cSPUILayout();
};

// ===========================================================================
// @ 0x008175a0
void __stdcall FUN_008175a0(EString* self) {
    self->Load(0xacb4e314, 0x6329c6c, L"Movie Name (PLACEHOLDER)");
}

// ===========================================================================
// 008175c0 : teardown of window/layout/handler members
struct MsgBoxB {
    char  pad_00[0x10];
    void* mLayout;     // +0x10
    void* mW1;         // +0x14
    void* mW2;         // +0x18
    void* mW3;         // +0x1c
    void* mHandler;    // +0x20
    u32   hA, hB, hC, hD; // +0x24..0x30
    void  teardown();
};
// @ 0x008175c0
void MsgBoxB::teardown() {
    void* p = this ? (void*)((char*)this + 8) : 0;
    void* o = FUN_0067de40();
    o = Vcp0(o, 0x20);
    Vv1(o, 0x20, (int)p);
    if (mLayout) {
        if (mW1) { mW1 = 0; Vv0(mW1, 0x04); }
        if (mW2) { mW2 = 0; Vv0(mW2, 0x04); }
        if (mW3) { mW3 = 0; Vv0(mW3, 0x04); }
        ((cSPUILayout*)mLayout)->Shutdown(1);
        if (mLayout) { void* q = mLayout; mLayout = 0; Vv0(q, 0x08); }
    }
    if (mHandler) {
        void* h = mHandler;
        mHandler = 0;
        EA_Messaging_RemoveHandler((int)h, hA, hB, hC, hD);
    }
}

// ===========================================================================
// 00817670 : show/hide the three message-box windows
struct MsgBoxC {
    char  pad_00[0x14];
    void* mW1;   // +0x14
    void* mW2;   // +0x18
    void* mW3;   // +0x1c
    char  pad_20[0x35 - 0x20];
    u8    b35;   // +0x35
    void setVisible(int on);
};
// @ 0x00817670
void MsgBoxC::setVisible(int on) {
    if ((char)on) {
        if (*(void**)0x15fd918 == 0) goto show;
        {
            void* props = *(void**)0x15fd918;
            char ok = Vb2(props, 0x24, 0x641021a, (int)&on);
            if (ok && Property_GetBool()) b35 = *(u8*)Property_GetBool();
        }
        goto show;
    }
show:
    Vv2(mW1, 0x7c, 1, on);
    Vv2(mW2, 0x7c, 1, on);
    Vv2(mW3, 0x7c, 1, on);
}

// ===========================================================================
// 00817720 : rebind root/child windows from the layout
struct MsgBoxD {
    char  pad_00[0x10];
    void* mLayout;  // +0x10
    void* mW1;      // +0x14
    void* mW2;      // +0x18
    void* mW3;      // +0x1c
    void rebind();
};
static void BindWin(void** slot, void* neu, int callOffset) {
    void* old = *slot;
    if (neu == old) return;
    if (neu) Vv0(neu, 0);
    *slot = neu;
    if (old) Vv0(old, 0x04);
}
// @ 0x00817720
void MsgBoxD::rebind() {
    void* w = ((cSPUILayout*)mLayout)->FindWindowByID(0xffffffff, 1);
    BindWin(&mW1, w, 0);
    if (mW1) Vv1(mW1, 0x104, (int)this);
    w = ((cSPUILayout*)mLayout)->FindWindowByID(0x62ef978, 1);
    BindWin(&mW2, w, 0);
    w = ((cSPUILayout*)mLayout)->FindWindowByID(0x642d110, 1);
    BindWin(&mW3, w, 0);
}

// ===========================================================================
// 008177e0 : release on shutdown, or tail-call rebind
struct MsgBoxE {
    char  pad_00[0x14];
    void* mW1;   // +0x14
    void* mW2;   // +0x18
    void* mW3;   // +0x1c
    void release();
    void rebind();  // 00817720
};
// @ 0x008177e0
void MsgBoxE::release() {
    void* p;
    p = mW2; if (p) { mW2 = 0; Vv0(p, 0x04); }
    p = mW3; if (p) { mW3 = 0; Vv0(p, 0x04); }
    if (mW1) Vv1(mW1, 0x108, (int)this);
}

// ===========================================================================
// 00817840 : enable/disable movie-related windows
struct MsgBoxF {
    char pad_00[0x30];
    u8   b30;   // +0x30
    bool setMovieState(u32 id);
};
extern "C" void FUN_00817670(void*, int);
struct Helper817670 { void Fn(int arg); };
// @ 0x00817840
bool MsgBoxF::setMovieState(u32 id) {
    if (id > 0x62ff413) {
        if (id >= 0x62ff414 && id <= 0x62ff415) {
            b30 = 0;
            ((Helper817670*)((char*)this - 4))->Fn(0);
        }
    } else {
        if (id == 0x62ff413) {
            ((Helper817670*)((char*)this - 4))->Fn(1);
            return true;
        }
        if (id == 0x604c6e0) {
            void* ms = SP_MovieSystem();
            if (ms && Vb0(ms, 0x30))
                Vv0(ms, 0x38);
        }
    }
    return true;
}

// ===========================================================================
// 00817c40 : named-string getter (hash dispatch)
struct CellNameSrc {
    char     pad_00[0x30];
    EString* f30;  // +0x30
    EString* f34;  // +0x34
    EString* f38;  // +0x38
    EString* f3c;  // +0x3c
    bool getName(const wchar_t* key, EString* out);
};
// @ 0x00817c40
bool CellNameSrc::getName(const wchar_t* key, EString* out) {
    u32 h = FNV1_String16(key, 0x811c9dc5, 1);
    EString* m;
    if (h > 0xb148e703) {
        if (h != 0xce645bea) return false;
        m = f34;
    } else {
        if (h == 0xb148e703) m = f30;
        else if (h == 0x6933bb85) m = f38;
        else if (h != 0xae892933) return false;
        else m = f3c;
    }
    if (!m) return false;
    *out = *m;
    return true;
}

// ===========================================================================
// 00817000 : scalar deleting destructor
struct MsgBoxA {
    char        pad_00[0x0c];
    cSPUILayout layout;   // +0x0c
    void* scalarDtor(u8 flags);
};
extern "C" void Dealloc(void*);
// @ 0x00817000
void* MsgBoxA::scalarDtor(u8 flags) {
    *(void**)((char*)this + 0) = (void*)0x1418dd4;
    *(void**)((char*)this + 4) = (void*)0x1418dc4;
    layout.~cSPUILayout();
    *(void**)((char*)this + 4) = (void*)0x13ec458;
    *(void**)((char*)this + 0) = (void*)0x13eb938;
    if (flags & 1) Dealloc(this);
    return this;
}

// ===========================================================================
// incomplete / approximate implementations (see partial.txt)
// ===========================================================================
struct cSPUIMessageBoxStub {
    char pad_00[0x2000];
    void AutoSizeButtons() { *(volatile int*)pad_00 = 0; }     // 00816d40
    void Init() { *(volatile int*)pad_00 = 0; }                // 00817040
    void reload() { *(volatile int*)pad_00 = 0; }              // 008178b0
    void reloadIcons() { *(volatile int*)pad_00 = 0; }         // 00817b00
};
void stub_816d40(cSPUIMessageBoxStub* p) { p->AutoSizeButtons(); }
void stub_817040(cSPUIMessageBoxStub* p) { p->Init(); }
void stub_8178b0(cSPUIMessageBoxStub* p) { p->reload(); }
void stub_817b00(cSPUIMessageBoxStub* p) { p->reloadIcons(); }

// 00817a40 : ctor
void stub_817a40(void* p) {
    *(void**)((char*)p + 0) = (void*)0x1418e70;
    *(void**)((char*)p + 4) = (void*)0x1418e68;
    *(void**)((char*)p + 8) = (void*)0x1418e50;
    for (int i = 0x10; i < 0x88; i += 4) *(u32*)((char*)p + i) = 0;
}
