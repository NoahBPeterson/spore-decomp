// Slice s00f46560: Spore UI/editor module (SporeApp, /O2 /MD /Gy /EHsc /TP).
//
// Leading entries are UTFWin/editor UI message handlers (cSPUIAssetComments,
// cOnlineTab, cXHTMLFrameSet-derived screens); the tail
// (0x00F47380..0x00F475B0) is the shared-allocator / OS-global plumbing and
// matches byte-for-byte.  Bodies follow the annotated disassembly
// (work/match/scratch_s00f46560_cards.txt).
#include "types.h"
#include <intrin.h>

extern "C" __declspec(dllimport) void* __stdcall GetProcessHeap();
extern "C" __declspec(dllimport) void* __stdcall HeapAlloc(void*, unsigned long, unsigned int);
extern "C" __declspec(dllimport) int __stdcall HeapFree(void*, unsigned long, void*);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long*);

struct Method { void M(); };
struct Method1 { void FUN_009276c0(void*); };
struct Method6 { void M(int, int, int, int, int, int); };
struct Method8 { void M(int, int, int, int, int, int, int, int); };
struct V2 { virtual void a(); virtual void b(); };
struct VBig0 {
    virtual char v0();  virtual char v1();  virtual char v2();  virtual char v3();
    virtual char v4();  virtual char v5();  virtual char v6();  virtual char v7();
    virtual char v8();  virtual char v9();  virtual char v10(); virtual char v11();
    virtual char v12(); virtual char v13(); virtual char v14(); virtual char v15();
    virtual char v16(); virtual char v17(); virtual char v18(); virtual char v19();
    virtual char v20(); virtual char v21(); virtual char v22(); virtual char v23();
    virtual char v24(); virtual char v25(); virtual char v26(); virtual char v27();
    virtual char v28(); virtual char v29(); virtual char v30(); virtual char v31();
    virtual char v32(); virtual char v33(); virtual char v34();
};

extern void __cdecl cdecl_free(void*);
extern char __cdecl cdecl_f935ad0(void*);
extern void* __cdecl cdecl_f935c80(int, void*);
extern void* __cdecl cdecl_f67dd10();
extern void __cdecl cdecl_fddde80(void*);
extern void __cdecl cdecl_f57f3e0(void*);
extern void __cdecl cdecl_feb2e70(void*);
extern void __cdecl cdecl_fef1950(void*);
extern void* __cdecl cdecl_Canvas();

extern char* g_16c8b40;
extern char* g_16c8b44;

void* f_47480();
void f_47430();

// =====================================================================
// Calling-convention helper types for indirect (virtual) calls.
// =====================================================================
typedef void  (__thiscall* FnP)(void*);
typedef void  (__thiscall* FnPi)(void*, int);
typedef void  (__thiscall* FnP2i)(void*, int, int);
typedef void  (__thiscall* FnP3i)(void*, int, int, int);
typedef void  (__thiscall* FnP4i)(void*, int, int, int, int);
typedef void  (__thiscall* FnPv)(void*, void*);
typedef void  (__thiscall* FnP2v)(void*, void*, int);
typedef char  (__thiscall* FnB)(void*);
typedef char  (__thiscall* FnBi)(void*, int);
typedef char  (__thiscall* FnB2i)(void*, int, int);
typedef void* (__thiscall* FnRetP)(void*);
typedef void* (__thiscall* FnRetPi)(void*, int);
typedef void* (__thiscall* FnRetP2)(void*, int, int);
typedef void* (__thiscall* FnRetP4)(void*, int, int, int, int);

static inline void* Vslot(void* o, int off) {
    return ((void**)(*(void**)o))[off / 4];
}

// =====================================================================
// Globals (retail addresses).
// =====================================================================
struct cSessionState {
    unsigned char mPad00[0xac];
    int mSelectedKey[3];         // +0xac  last-edited asset key (12-byte GUID)
    unsigned char mPadB8[0xcc - 0xb8];
    int mEditorId;               // +0xcc
};

struct SpVector {                // eastl::vector under the global allocator
    void* mpBegin;               // +0x00
    void* mpEnd;                 // +0x04
    void FUN_00e25bd0(void* first, void* last);   // 0x00e25bd0  erase
};

extern cSessionState* g_16c7aa4;      // 0x016c7aa4
extern void* g_15ad298;               // 0x015ad298  app singleton
extern void* g_15fd918;               // 0x015fd918  app property list
extern void* g_15b0544;               // 0x015b0544  frame id A
extern void* g_15b0548;               // 0x015b0548  url "blank.html"
extern void* g_15b0560;               // 0x015b0560  frame id B
extern void* g_15b0564;               // 0x015b0564  frame id C
extern void* g_15b0568;               // 0x015b0568  frame id D
extern void* g_15b056c;               // 0x015b056c  url "blank.ep1.ht.."
extern void* g_15b0570;               // 0x015b0570  callout message text
extern SpVector  g_16065d8;           // 0x016065d8  vector<AutoRefCount<ILogReporter>>
extern void*     g_16065ec;           // 0x016065ec
extern int       g_16065f0;           // 0x016065f0
extern unsigned char g_16065f8;       // 0x016065f8
extern void*     g_16065fc;           // 0x016065fc

extern wchar_t g_1667bac;             // 0x01667bac  eastl::gEmptyString16 (begin/end)
extern wchar_t g_1667bae;             // 0x01667bae  (begin + 1 -> capacity)

// =====================================================================
// Callees.
// =====================================================================
// free functions (cdecl)
extern "C" int   FUN_00efc520();                                    // 0x00efc520
extern "C" void  FUN_00efc850();                                    // 0x00efc850
extern "C" void* FUN_00b3d300();                                    // 0x00b3d300  SP::NounManager
extern "C" void* FUN_00883860();                                    // 0x00883860  EA::Messaging::GetServer
extern "C" void* FUN_00607a60();                                    // 0x00607a60  SP::Pollen::AuthManager
extern "C" void* FUN_00d539d0();                                    // 0x00d539d0  SP::cPosseSimulator::Instance
extern "C" void* FUN_0067dd60();                                    // 0x0067dd60  MessageServer
extern "C" void* FUN_0067dcc0();                                    // 0x0067dcc0  MessageServer
extern "C" void  FUN_00571db0(void*, void*, void*, void*, void*);  // 0x00571db0  EA::Messaging::RemoveHandler
extern "C" void  FUN_00ef29c0();                                    // 0x00ef29c0
extern "C" void  GetURL(unsigned int, void*);                       // 0x006214c0  ?GetURL@@YA_NIPAUString8@@@Z
extern "C" void  FUN_004e0850(void*, const wchar_t*, ...);          // 0x004e0850  append formatted text
extern "C" void  FUN_00809db0(void*, void*);                        // 0x00809db0  UI::CalloutMessageBox

// retained-format strings referenced by the URL builders
#define STR_FMT_I64U   ((const wchar_t*)0x0148d600)   // L"%I64u/"
#define STR_148d5f8    ((const wchar_t*)0x0148d5f8)
#define STR_13f01bc    ((const wchar_t*)0x013f01bc)

__declspec(noinline) void f_47380(int p);   // defined at 0x00F47380 below

// EA::UTFWinExtras::cXHTMLFrameSet member functions (frame-set sub-object).
// The layout is opaque here; callers obtain the sub-object address.
struct cXHTMLFrameSet {
    void  FUN_00996cc0(void*);                         // 0x00996cc0  cXHTMLFrameSet::cXHTMLFrameSet
    void  FUN_00996280(int, int, int, int);            // 0x00996280  configure
    void  FUN_00997140();                              // 0x00997140  ClearJobs
    void  FUN_009968a0();                              // 0x009968a0  ~cXHTMLFrameSet
    void* FUN_00996d40(unsigned int);                  // 0x00996d40  GetFrame
    bool  FUN_00997730(void*, const void*, void*, int); // 0x00997730  HandleLocationChange
    bool  FUN_009978b0(void*, void*);                  // 0x009978b0  HandleFormSubmit
    bool  FUN_009979f0(void*, unsigned int);           // 0x009979f0  Attach
};

static cXHTMLFrameSet* FrameAt(void* base, int off) {
    return (cXHTMLFrameSet*)((char*)base + off);
}

// Secondary-base adjustment helper (multiple-inheritance callback view).
static inline void* SecondaryBase(void* o) {
    return o ? (char*)o + 4 : 0;
}

// Reference-counted pointer helpers (EA AutoRefCount semantics).
static inline void RefAdd(void* p) {
    _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1);
}
static inline void RefReleaseKeepAlive(void* p) {
    volatile long* rc = (volatile long*)((char*)p + 8);
    _InterlockedExchangeAdd(rc, -1);
    if (_InterlockedExchangeAdd(rc, 0) < 1)
        _InterlockedExchangeAdd(rc, 1);
}

struct Key12 { int a; int b; int c; };
struct cProperty { char* FUN_0041e920(); };   // 0x0041e920  cProperty::GetBool
struct cGNM2 { void FUN_00b22960(); };        // 0x00b22960  ProcessPending

// =====================================================================
// SP::cSPUIAssetComments  (leading UI message handlers)
// =====================================================================
struct cEditorInner {                          // sub-object held by cEditor
    void FUN_00dffa30(int);                    // 0x00dffa30
    void FUN_00f2b3d0();                       // 0x00f2b3d0
    void FUN_00f26330();                       // 0x00f26330
    unsigned char mPad00[0x238];
    int mId238;                                // +0x238
};

struct cImageResHolder {                       // receiver of GetImageResource
    unsigned char mSlot[4];
    void FUN_00576650(void* key);              // 0x00576650  GetImageResource
};

struct cEditor {
    unsigned char mPad00[0x10];
    cEditorInner* mpInner;                     // +0x10
    unsigned char mFlag14;                     // +0x14
    unsigned char mPad15[0x38 - 0x15];
    cImageResHolder mRes38;                    // +0x38
    void* mImages[4];                          // +0x3c  cached image resources
    unsigned char mPad4c[0x80 - 0x4c];
    int  mf80;                                 // +0x80
    unsigned char mFlag84;                     // +0x84
    unsigned char mFlag85;                     // +0x85
    unsigned char mPad86[0x124 - 0x86];
    unsigned char mFlag124;                    // +0x124

    unsigned char FUN_00f44bf0(void*);         // 0x00f44bf0
    void  FUN_00f41300();                      // 0x00f41300
    void  FUN_00f40370();                      // 0x00f40370
    unsigned char FUN_00f43f20();              // 0x00f43f20
    void  FUN_00f45c30(int, int, int, int);    // 0x00f45c30
    unsigned char FUN_00f46630(void* win);     // cEditor::FUN_00f46630
};

struct UIComments {
    unsigned char mPad00[0xc];
    cEditor* mpEditor;                         // +0x0c
    unsigned char mFrameSet[0x64];             // +0x10  embedded cXHTMLFrameSet

    void FUN_00f46560(int a1);                 // UIComments message handler
    bool FUN_00f468c0(int a1, int* msg);       // UIComments::DoMessage
};

// @ 0x00F46560
void UIComments::FUN_00f46560(int a1) {
    void* app = g_15ad298;
    (*(FnPi)Vslot(app, 0x20))(app, 0);
    mpEditor->FUN_00f41300();
    mpEditor->mpInner->FUN_00dffa30(a1);
    unsigned char flag = mpEditor->FUN_00f43f20();
    int id = g_16c7aa4->mEditorId;
    int t = FUN_00efc520();
    mpEditor->FUN_00f45c30(id, t, 1, 1);
    ((cGNM2*)FUN_00b3d300())->FUN_00b22960();
    mpEditor->FUN_00f45c30(id, t, 0, 0);
    if (flag) mpEditor->FUN_00f40370();
    FUN_00efc850();
    void* srv = FUN_00883860();
    (*(FnP3i)Vslot(srv, 0x14))(srv, 0x72bdb11, 0, 0);
}

// @ 0x00F46630
unsigned char cEditor::FUN_00f46630(void* win) {
    unsigned char ok = 0;
    if (FUN_00f44bf0(win)) {
        mpInner->FUN_00f2b3d0();
        mFlag14 = FUN_00f43f20();
        mpInner->FUN_00f26330();
        void* inst = FUN_00d539d0();
        *(int*)((char*)inst + 0x18) = mpInner->mId238;

        int id = g_16c7aa4->mEditorId;
        if (!id) id = 1;

        char propFlag = 0;
        if (g_15fd918) {
            int out = 0;
            char got = (*(FnB2i)Vslot(g_15fd918, 0x24))(g_15fd918, 0x50caab1, (int)&out);
            if (got && *(short*)(out + 0x12) == 1) {
                char* pv = ((cProperty*)out)->FUN_0041e920();
                propFlag = *pv;
            }
        }
        int sel = propFlag ? -1 : 0;

        FUN_00f41300();
        FUN_00f45c30(id, sel, 1, 1);
        ((cGNM2*)FUN_00b3d300())->FUN_00b22960();
        FUN_00f45c30(id, sel, 0, 0);

        Key12 k;
        k.a = ((int*)win)[0];
        k.b = ((int*)win)[1];
        k.c = ((int*)win)[2];
        void* srv = FUN_0067dd60();
        void* r0 = (*(FnRetP4)Vslot(srv, 0x1c))(srv, k.a, k.b, k.c, 0);
        mRes38.FUN_00576650(r0);

        void** dst = mImages;
        int i = 0;
        do {
            ++i;
            Key12 kk;
            kk.a = ((int*)win)[0];
            kk.b = ((int*)win)[1];
            kk.c = ((int*)win)[2] ^ ((i ^ ((int*)win)[2]) & 0xff);
            void* s2 = FUN_0067dd60();
            void* res = (*(FnRetP4)Vslot(s2, 0x1c))(s2, kk.a, kk.b, kk.c, 0);
            void* old = *dst;
            if (res != old) {
                if (res) RefAdd(res);
                *dst = res;
                if (old) RefReleaseKeepAlive(old);
            }
            ++dst;
        } while (i < 4);

        ok = 1;
        mFlag124 = 1;

        void* gs = FUN_00883860();
        (*(FnP3i)Vslot(gs, 0x14))(gs, 0x72bdb11, 0, 0);
        void* ms = FUN_0067dcc0();
        (*(FnP3i)Vslot(ms, 0x14))(ms, 0x7e1e46d, 0, 0);

        g_16c7aa4->mSelectedKey[0] = ((int*)win)[0];
        g_16c7aa4->mSelectedKey[1] = ((int*)win)[1];
        g_16c7aa4->mSelectedKey[2] = ((int*)win)[2];

        g_16065ec = 0;
        g_16065d8.FUN_00e25bd0(g_16065d8.mpBegin, g_16065d8.mpEnd);
        g_16065f0 = g_16065f0 + 1;
        g_16065f8 = 1;
        void* reporter = g_16065fc;
        if (reporter) {
            g_16065fc = 0;
            (*(FnP)Vslot(reporter, 4))(reporter);
        }
        FUN_00ef29c0();

        mf80 = g_16065f0;
        mFlag84 = 0;
        mFlag85 = 0;
    }
    return ok;
}

// @ 0x00F468C0
bool UIComments::FUN_00f468c0(int a1, int* msg) {
    if (msg[2] == (int)0x287259f6) {
        void* p = (void*)msg[0];
        void* r = (*(FnRetP)Vslot(p, 0x1c))(p);
        if (r == (void*)0x519e168) {
            void* am = FUN_00607a60();
            (*(FnP)Vslot(am, 0x44))(am);
        }
    } else if (msg[2] == 0x3326e8a) {
        int v = *(int*)msg[6];
        if (v) {
            return FrameAt(this, 0x10)->FUN_00997730((void*)msg[0], (void*)v,
                                                     (void*)((int*)msg[6])[1], 0);
        }
    }
    return false;
}

// =====================================================================
// cOnlineTab (frame-set at +0x10)
// =====================================================================
struct WString16 {
    unsigned int* mpBegin;      // +0x00
    unsigned int* mpEnd;        // +0x04
    unsigned int* mpCapacity;   // +0x08
};

struct cOnlineTab {
    unsigned char mPad00[0x10];
    unsigned char mFrameSet[0x64];  // +0x10  embedded cXHTMLFrameSet
    void* mpFrame74;                // +0x74
    void* mpFrame78;                // +0x78
    WString16 mUrl;                 // +0x7c
    unsigned int mf88;              // +0x88  (uninitialised here)
    void* mpHandler;                // +0x8c
    void* mHandlerArg0;             // +0x90
    void* mHandlerArg1;             // +0x94
    int   mHandlerArg2;             // +0x98
    int   mHandlerArg3;             // +0x9c

    bool  FUN_00f46920(void* p);                        // Shutdown
    bool  FUN_00f46a40();                               // teardown
    void  FUN_00f46ab0(int a2);                         // set frame
    void* FUN_00f46b50();                               // ctor
    void  FUN_00f46c00();                               // dtor
    void  FUN_00f46cf0(int a1, int a2, int a3, int a4); // url builder
};

// @ 0x00F46920
bool cOnlineTab::FUN_00f46920(void* p) {
    void* cb = SecondaryBase(this);
    void* srv = FUN_0067dcc0();
    mpHandler = srv;
    mHandlerArg0 = cb;
    mHandlerArg1 = (void*)0x148d5c0;
    mHandlerArg2 = 1;
    mHandlerArg3 = 0;
    if (srv && cb)
        (*(FnP2i)Vslot(srv, 0x24))(srv, (int)cb, 0x44db12e);

    void* prev = mpFrame74;
    if (p != prev) {
        if (p) (*(FnP)Vslot(p, 0))(p);
        mpFrame74 = p;
        if (prev) (*(FnP)Vslot(prev, 4))(prev);
    }
    if (!mpFrame74) return false;

    FrameAt(this, 0x10)->FUN_00996280(0x1002, 0x1006, 0x1003, 0x1024);
    (*(FnPv)Vslot(p, 0x104))(p, this);
    if (FrameAt(this, 0x10)->FUN_009979f0(p, 0x451a4c0)) {
        void* fr = FrameAt(this, 0x10)->FUN_00996d40((unsigned int)g_15b0544);
        void* q = fr ? (char*)fr + 4 : 0;
        void* prev2 = mpFrame78;
        if (q != prev2) {
            if (q) (*(FnP)Vslot(q, 0))(q);
            mpFrame78 = q;
            if (prev2) (*(FnP)Vslot(prev2, 4))(prev2);
        }
    }
    return mpFrame78 != 0;
}

// @ 0x00F46A40
bool cOnlineTab::FUN_00f46a40() {
    if (mpHandler) {
        void* h = mpHandler;
        mpHandler = 0;
        FUN_00571db0(h, mHandlerArg0, mHandlerArg1, (void*)mHandlerArg2, (void*)mHandlerArg3);
    }
    FrameAt(this, 0x10)->FUN_00997140();
    void* p = mpFrame74;
    if (p) {
        (*(FnPv)Vslot(p, 0x108))(p, this);
        p = mpFrame74;
        if (p) {
            mpFrame74 = 0;
            (*(FnP)Vslot(p, 4))(p);
        }
    }
    return true;
}

// @ 0x00F46AB0
void cOnlineTab::FUN_00f46ab0(int a2) {
    cXHTMLFrameSet* fs = FrameAt(this, 0x10);
    void* fr = fs->FUN_00996d40((unsigned int)g_15b0544);
    if (fr) {
        (*(FnP2i)Vslot((char*)fr + 4, 0x7c))((char*)fr + 4, 1, a2);
        fs->FUN_00997730(mpFrame78, (void*)g_15b0548, 0, 0);
        fs->FUN_00997730((*(FnRetP)Vslot(fr, 0x8c))(fr), mUrl.mpBegin, 0, 0);
    }
    void* p = mpFrame74;
    void* r = (*(FnRetP2)Vslot(p, 0xf0))(p, (int)0x7737810, 1);
    if (r)
        (*(FnP2i)Vslot(r, 0x7c))(r, 1, ((unsigned char)a2 == 0) ? 1 : 0);
}

// @ 0x00F46B50
void* cOnlineTab::FUN_00f46b50() {
    *(void**)((char*)this + 4) = (void*)0x13eb394;
    *(void**)((char*)this + 8) = (void*)0x13ec458;
    *(void**)((char*)this + 0xc) = 0;
    *(void**)((char*)this + 0) = (void*)0x148d5dc;
    *(void**)((char*)this + 4) = (void*)0x148d5d4;
    *(void**)((char*)this + 8) = (void*)0x148d5c4;

    FrameAt(this, 0x10)->FUN_00996cc0((void*)0x623f40);

    mpFrame74 = 0;
    mpFrame78 = 0;
    mUrl.mpCapacity = (unsigned int*)&g_1667bae;
    mUrl.mpBegin = (unsigned int*)&g_1667bac;
    mUrl.mpEnd = (unsigned int*)&g_1667bac;
    mpHandler = 0;
    mHandlerArg0 = 0;
    mHandlerArg1 = 0;
    mHandlerArg2 = 0;
    mHandlerArg3 = 0;

    (*(FnP)Vslot(FrameAt(this, 0x10), 0))(FrameAt(this, 0x10));
    return this;
}

// @ 0x00F46C00
void cOnlineTab::FUN_00f46c00() {
    *(void**)((char*)this + 0) = (void*)0x148d5dc;
    *(void**)((char*)this + 4) = (void*)0x148d5d4;
    *(void**)((char*)this + 8) = (void*)0x148d5c4;
    _ReadWriteBarrier();

    if (mpHandler) {
        void* h = mpHandler;
        mpHandler = 0;
        FUN_00571db0(h, mHandlerArg0, mHandlerArg1, (void*)mHandlerArg2, (void*)mHandlerArg3);
    }

    unsigned int* begin = mUrl.mpBegin;
    if (((int)((char*)mUrl.mpCapacity - (char*)begin) & (int)0xfffffffe) > 2 && begin)
        f_47380((int)begin);

    void* p = mpFrame78;
    if (p) (*(FnP)Vslot(p, 4))(p);
    p = mpFrame74;
    if (p) (*(FnP)Vslot(p, 4))(p);

    FrameAt(this, 0x10)->FUN_009968a0();
    *(void**)((char*)this + 8) = (void*)0x13ec458;
    *(void**)((char*)this + 4) = (void*)0x13eb394;
    *(void**)((char*)this + 0) = (void*)0x13eb938;
}

// @ 0x00F46CF0
void cOnlineTab::FUN_00f46cf0(int a1, int a2, int a3, int a4) {
    GetURL(0x811c9dc5, &mUrl);
    FUN_004e0850(&mUrl, STR_FMT_I64U, a1, a2);
    FUN_004e0850(&mUrl, STR_148d5f8, a3);
    FUN_004e0850(&mUrl, STR_13f01bc, a4);
    void* am = FUN_00607a60();
    bool c = (*(FnB)Vslot(am, 0x24))(am);
    FUN_00f46ab0(c == 0 ? 1 : 0);
}

// Secondary (message-proc) base of cOnlineTab, which sits at +4.
struct MsgProc { char Handler(int a1, int a2); };

// @ 0x00F46CD0
char MsgProc::Handler(int a1, int a2) {
    if (a1 == 0x44db12e && a2 != 0)
        ((cOnlineTab*)((char*)this - 4))->FUN_00f46ab0(1);
    return 0;
}

// =====================================================================
// cXHTMLFrameSet-derived screen (frame-set at +0xc, window at +0x70)
// =====================================================================
struct cScreen {
    unsigned char mPad00[0xc];
    unsigned char mFrameSet[0x64];  // +0x0c  embedded cXHTMLFrameSet
    void* mpWindow70;               // +0x70
    void* mpFrame74;                // +0x74
    void* mpFrame78;                // +0x78
    void* mpFrame7c;                // +0x7c

    bool FUN_00f46d60(int a1, int* msg);   // DoMessage
    void* FUN_00f46dd0();                  // ctor
    void  FUN_00f46e30();                  // dtor
    bool FUN_00f46eb0(void* p);            // set window
    bool FUN_00f47040();                   // teardown
    void FUN_00f47080(int a2);             // set visible
    void FUN_00f47120();                   // reset frames
    bool FUN_00f47170(int a1, int a2);     // refresh
};

// @ 0x00F46D60
bool cScreen::FUN_00f46d60(int a1, int* msg) {
    if (msg[2] == 0x3326e8a) {
        int v = *(int*)msg[6];
        if (v)
            return FrameAt(this, 0xc)->FUN_00997730((void*)msg[0], (void*)v,
                                                    (void*)((int*)msg[6])[1], 0);
    } else if (msg[2] == 0x3326e8b) {
        return FrameAt(this, 0xc)->FUN_009978b0((void*)msg[0], (void*)msg[6]);
    } else if (msg[2] == 0x43b0aee) {
        FUN_00809db0(0, &g_15b0570);
        return true;
    }
    return false;
}

// @ 0x00F46DD0
void* cScreen::FUN_00f46dd0() {
    *(void**)((char*)this + 4) = (void*)0x13ec458;
    *(void**)((char*)this + 8) = 0;
    *(void**)((char*)this + 0) = (void*)0x148d6ac;
    *(void**)((char*)this + 4) = (void*)0x148d69c;

    FrameAt(this, 0xc)->FUN_00996cc0((void*)0x623f40);

    mpWindow70 = 0;
    mpFrame74 = 0;
    mpFrame78 = 0;
    mpFrame7c = 0;

    (*(FnP)Vslot(FrameAt(this, 0xc), 0))(FrameAt(this, 0xc));
    return this;
}

// @ 0x00F46E30
void cScreen::FUN_00f46e30() {
    *(void**)((char*)this + 0) = (void*)0x148d6ac;
    *(void**)((char*)this + 4) = (void*)0x148d69c;
    if (mpFrame7c) (*(FnP)Vslot(mpFrame7c, 4))(mpFrame7c);
    if (mpFrame78) (*(FnP)Vslot(mpFrame78, 4))(mpFrame78);
    if (mpFrame74) (*(FnP)Vslot(mpFrame74, 4))(mpFrame74);
    if (mpWindow70) (*(FnP)Vslot(mpWindow70, 4))(mpWindow70);
    FrameAt(this, 0xc)->FUN_009968a0();
    *(void**)((char*)this + 4) = (void*)0x13ec458;
    *(void**)((char*)this + 0) = (void*)0x13eb938;
}

// @ 0x00F46EB0
bool cScreen::FUN_00f46eb0(void* p) {
    void* prev = mpWindow70;
    if (p != prev) {
        if (p) (*(FnP)Vslot(p, 0))(p);
        mpWindow70 = p;
        if (prev) (*(FnP)Vslot(prev, 4))(prev);
    }
    if (!mpWindow70) return false;

    FrameAt(this, 0xc)->FUN_00996280(0x1002, 0x1006, 0x1003, 0x1024);
    (*(FnPv)Vslot(mpWindow70, 0x104))(mpWindow70, this);

    struct { int off; unsigned int id; void** slot; void* frameId; } steps[3] = {
        { 0x74, 0xa910fee9, &mpFrame74, g_15b0560 },
        { 0x78, 0x1d4058a6, &mpFrame78, g_15b0564 },
        { 0x7c, 0xac07aaa8, &mpFrame7c, g_15b0568 },
    };
    for (int i = 0; i < 3; ++i) {
        if (FrameAt(this, 0xc)->FUN_009979f0(mpWindow70, steps[i].id)) {
            void* fr = FrameAt(this, 0xc)->FUN_00996d40((unsigned int)steps[i].frameId);
            void* q = fr ? (char*)fr + 4 : 0;
            void** slot = steps[i].slot;
            void* old = *slot;
            if (q != old) {
                if (q) (*(FnP)Vslot(q, 0))(q);
                *slot = q;
                if (old) (*(FnP)Vslot(old, 4))(old);
            }
        }
    }
    return mpFrame74 != 0 || mpFrame78 != 0 || mpFrame7c != 0;
}

// @ 0x00F47040
bool cScreen::FUN_00f47040() {
    FrameAt(this, 0xc)->FUN_00997140();
    void* p = mpWindow70;
    if (p) {
        (*(FnPv)Vslot(p, 0x108))(p, this);
        p = mpWindow70;
        if (p) {
            mpWindow70 = 0;
            (*(FnP)Vslot(p, 4))(p);
        }
    }
    return true;
}

// @ 0x00F47080
void cScreen::FUN_00f47080(int a2) {
    void* r;
    r = (*(FnRetP2)Vslot(mpWindow70, 0xf0))(mpWindow70, (int)0x7ccce38, 1);
    if (r) (*(FnP2i)Vslot(r, 0x7c))(r, 1, a2);
    r = (*(FnRetP2)Vslot(mpWindow70, 0xf0))(mpWindow70, (int)0x7ccce30, 1);
    if (r) (*(FnP2i)Vslot(r, 0x7c))(r, 1, a2);
    r = (*(FnRetP2)Vslot(mpWindow70, 0xf0))(mpWindow70, (int)0x7da34f8, 1);
    if (r) (*(FnP2i)Vslot(r, 0x7c))(r, 1, a2);
    r = (*(FnRetP2)Vslot(mpWindow70, 0xf0))(mpWindow70, (int)0x561dd60, 1);
    if (r) (*(FnP2i)Vslot(r, 0x7c))(r, 1, a2);
}

// @ 0x00F47120
void cScreen::FUN_00f47120() {
    FrameAt(this, 0xc)->FUN_00997730(mpFrame74, (void*)g_15b056c, 0, 0);
    FrameAt(this, 0xc)->FUN_00997730(mpFrame78, (void*)g_15b056c, 0, 0);
    FrameAt(this, 0xc)->FUN_00997730(mpFrame7c, (void*)g_15b056c, 0, 0);
}

// @ 0x00F47170
bool cScreen::FUN_00f47170(int a1, int a2) {
    void* am = FUN_00607a60();
    unsigned char bl = (*(FnB)Vslot(am, 0x24))(am);

    FUN_00f47080(bl == 0 ? 1 : 0);

    {
        void* w = mpWindow70;
        void* r = (*(FnRetP2)Vslot(w, 0xf0))(w, (int)0x561dd60, 1);
        if (r)
            (*(FnP2i)Vslot(r, 0x7c))(r, 1, bl == 0 ? 1 : 0);
    }
    if (bl) return true;

    FUN_00f47120();

    bool f1 = true;
    if (mpFrame74) {
        WString16 u;
        u.mpBegin = (unsigned int*)&g_1667bac;
        u.mpEnd = (unsigned int*)&g_1667bac;
        u.mpCapacity = (unsigned int*)&g_1667bae;
        GetURL(0x811c9dc9, &u);
        FUN_004e0850(&u, STR_FMT_I64U, a1, a2);
        f1 = FrameAt(this, 0xc)->FUN_00997730(mpFrame74, u.mpBegin, 0, 0);
        if ((((char*)u.mpCapacity - (char*)u.mpBegin) & 0xfffffffeU) > 2 && u.mpBegin)
            f_47380((int)u.mpBegin);
    }

    bool f2 = true;
    if (mpFrame78) {
        WString16 u;
        u.mpBegin = (unsigned int*)&g_1667bac;
        u.mpEnd = (unsigned int*)&g_1667bac;
        u.mpCapacity = (unsigned int*)&g_1667bae;
        GetURL(0x811c9dc8, &u);
        FUN_004e0850(&u, STR_FMT_I64U, a1, a2);
        f2 = FrameAt(this, 0xc)->FUN_00997730(mpFrame78, u.mpBegin, 0, 0);
        if ((((char*)u.mpCapacity - (char*)u.mpBegin) & 0xfffffffeU) > 2 && u.mpBegin)
            f_47380((int)u.mpBegin);
    }

    bool f3 = true;
    if (mpFrame7c) {
        WString16 u;
        u.mpBegin = (unsigned int*)&g_1667bac;
        u.mpEnd = (unsigned int*)&g_1667bac;
        u.mpCapacity = (unsigned int*)&g_1667bae;
        GetURL(0x811c9dc7, &u);
        FUN_004e0850(&u, STR_FMT_I64U, a1, a2);
        f3 = FrameAt(this, 0xc)->FUN_00997730(mpFrame7c, u.mpBegin, 0, 0);
        if ((((char*)u.mpCapacity - (char*)u.mpBegin) & 0xfffffffeu) > 2 && u.mpBegin)
            f_47380((int)u.mpBegin);
    }

    return f1 && f2 && f3;
}

// =====================================================================
// Tail: shared allocator / OS global plumbing (byte-exact subset).
// @ 0x00F47380
__declspec(noinline) void f_47380(int p) {
    if (p) ((Method1*)g_16c8b44)->FUN_009276c0((void*)p);
}

// @ 0x00F473A0
void f_473a0(int a1, int a2, int a3, int a4, int a5, int a6) {
    ((Method6*)g_16c8b44)->M(a1, a3, a4, a2, a5, a6);
}

// @ 0x00F473D0
void f_473d0(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    ((Method8*)g_16c8b44)->M(a1, a2, a3, a5, a6, a4, a7, a8);
}

// @ 0x00F47410
void f_47410(int p) { ((Method1*)g_16c8b44)->FUN_009276c0((void*)p); }

// @ 0x00F47430
void f_47430() {
    char* p = g_16c8b40;
    if (p) {
        char ok = cdecl_f935ad0(p);
        p = g_16c8b40;
        if (ok && p) {
            ((Method*)(p + 0x18))->M();
            HeapFree(GetProcessHeap(), 0, p);
        }
        g_16c8b40 = 0;
    }
}

// @ 0x00F47480
void* f_47480() {
    char* p = (char*)HeapAlloc(GetProcessHeap(), 0, 0x530);
    if (p) {
        *(int*)(p + 4) = 0;
        *(int*)p = 0;
        *(int*)(p + 0x10) = 0x2b5c;
        *(p + 0x14) = 0;
        ((Method6*)(p + 0x18))->M(0, 0, 1, 0, 0, 0);
    }
    return p;
}

// @ 0x00F474D0
char f_474d0() {
    if (!g_16c8b40) {
        g_16c8b40 = (char*)cdecl_f935c80(0xee9b7413, (void*)f_47480);
        if (!g_16c8b40) return 0;
    }
    if (*(int*)(g_16c8b40 + 0x10) == 0x2b5c && *(g_16c8b40 + 0x14) == 0) {
        g_16c8b44 = g_16c8b40 + 0x18;
        return 1;
    }
    f_47430();
    return 0;
}

// @ 0x00F47550
void f_47550() {
    void* a = cdecl_f67dd10();
    cdecl_fddde80(a);
    cdecl_f57f3e0(a);
    cdecl_feb2e70(a);
    cdecl_fef1950(a);
}

// @ 0x00F47580
struct CanvasProc { char pad[0xd]; char flag; void Run(); };
void CanvasProc::Run() {
    char c = flag;
    while (true) {
        if (!c) return;
        void* cv = cdecl_Canvas();
        if (!((VBig0*)cv)->v33()) break;
        c = flag;
    }
}

// @ 0x00F475B0
struct Timer { char pad[0x10]; long long last; float freq; int Elapsed(); };
int Timer::Elapsed() {
    long long t;
    QueryPerformanceCounter(&t);
    long long d = t - last;
    return (int)((float)d * freq);
}