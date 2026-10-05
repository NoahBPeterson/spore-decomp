// Sims3 UI IME module, slice s007f42e0 (0x7F42E0..0x7F5220).
// /O2. Real class layouts from the 2008 dev-build PDB; raw offsets for the
// heavyweight UTFWin sub-object chain (offsets confirmed against the asm).
#include "types.h"

typedef unsigned short wchar16;

#define VTOBJ(p) (*(void***)(p))

typedef void*  (__thiscall *FPR0)(void*);
typedef void   (__thiscall *FV0)(void*);
typedef void   (__thiscall *FVI)(void*, int);
typedef void   (__thiscall *FVP)(void*, void*);
typedef void*  (__thiscall *FPRP)(void*, void*);
typedef void*  (__thiscall *FPRI)(void*, int);
typedef char   (__thiscall *FPC0)(void*);
typedef char   (__thiscall *FPCI)(void*, int);
typedef int    (__thiscall *FPI0)(void*);

// ---- externals (relocations are masked, so only the convention matters) ----
void* __cdecl FUN_009512c0();
void* __cdecl FUN_009512d0(int size, int align, const char* name, void* caller);
void* __cdecl op_new(int size, const char* name, int a, int b, int c, int d);
void* __cdecl FUN_0067de40();
void* __cdecl SP_Canvas();
void* __cdecl FUN_0067dce0();
void* __cdecl EA_Messaging_GetServer();
void* __cdecl EA_UTFWin_GetManager();
void* __cdecl interface_cast(void* window);
bool  __cdecl DoFindNode(void* table, const wchar_t* key);
void  __cdecl deallocate(void* p);

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

extern void* g_vt_1414fd0;
extern void* g_vt_1414eb0;
extern void* g_vt_1414db8;
extern void* g_vt_1414dac;
extern void* g_vt_13eb394;
extern void* g_vt_1414d84;
extern void* g_vt_1414ba4;
extern void* g_vt_13eb90c;
extern const wchar_t g_ja_jp[] = L"ja-jp";
extern const char g_name_IMEServer[] = "UI/IME/IMEServer";
extern const char g_name_IMEProxy[] = "UI/IME/IMEProxy";
extern const char g_name_IMECandidateList[] = "UI/IME/IMECandidateList";
extern const char g_name_mpWinComposition[] = "UI/IME/mpWinComposition";
extern void* g_pIMEProxy;   // 0x01542214
extern void* g_pIMEServer;  // 0x01542210
extern const float g_compDx;
extern const float g_compDy;
extern const float g_updConst1;
extern const float g_updConst2;

// ---- stub classes (declared-only callees stay out of line) ----
struct WinTextEditCtor { void Ctor(); };
struct IMEServerWin32Ctor {
    void* Ctor();
    void SetCanvas(void*);
    void SetSomething(void*);
};
struct IMECandidateListCtor { void* Ctor(); };
struct IMECandidateListInit { void Init(void* msg); };
struct IMECompositionInit { void Init(void* msg); };
struct IMECompositionCtorStub { IMECompositionCtorStub* Construct(); };
struct IMEProxyInit { bool Init(void* server, void* svc); };
struct IMEProxyMisc { void M1(); void M2(); };
struct AutoRefAssign { void* Assign(void* p); };
struct IMEProxyShutdown { void Shutdown(); };

// --------------------------------------------------------------------------
// Wide fixed buffer (layout shared with 0x0042F9D0).
// --------------------------------------------------------------------------
struct WideFixedBuf {
    wchar16* mBegin;      // +0x00
    wchar16* mEnd;        // +0x04
    wchar16* mCapacity;   // +0x08
    int      mPad;        // +0x0c
    wchar16* mFixed;      // +0x10
    wchar16  mFixedBuf[0x100]; // +0x14
    WideFixedBuf(const wchar16* s);
    WideFixedBuf& append(const wchar16* first, const wchar16* last);
};

static inline uint32_t WLen(const wchar16* s)
{
    const wchar16* p = s;
    while (*p)
        ++p;
    return (uint32_t)(p - s);
}

// @ 0x007F48D0
WideFixedBuf::WideFixedBuf(const wchar16* s)
{
    wchar16* pFixed = mFixedBuf;
    mFixed = pFixed;
    mCapacity = pFixed + 0x100;
    mEnd = pFixed;
    mBegin = pFixed;
    *mBegin = 0;
    append(s, s + WLen(s));
}

// --------------------------------------------------------------------------
// IMEProxy (size 0x44)
// --------------------------------------------------------------------------
struct IMEProxyS {
    char     pad0[8];
    bool     mbInitialized;               // +0x08
    uint32_t mnTickCount;                 // +0x0c
    void*    mpMessageServer;             // +0x10
    int32_t  mPtX;                        // +0x14
    int32_t  mPtY;                        // +0x18
    bool     mbNonTextEditCompositionEnabled; // +0x1c
    void*    mpIMEServer;                 // +0x20
    void*    mpWinMgr;                    // +0x24
    void*    mpWinLastFocus;              // +0x28
    bool     mbWinCompositionEnabled;     // +0x2c
    void*    mpWinComposition;            // +0x30
    void*    mpWinCompositionTextStyle;   // +0x34
    bool     mbWinCandidateListEnabled;   // +0x38
    void*    mpWinCandidateList;          // +0x3c
    void*    mpWinCandidateListTextStyle; // +0x40

    bool Update();
    void StartCandidateList();
    void StartComposition();
    bool HandleMessage(uint32_t msgId, void* param);
    void SetupDefaultFonts();             // external 0x7F31E0
};

// @ 0x007F4500
void IMEProxyS::StartCandidateList()
{
    if (!mbWinCandidateListEnabled)
        return;
    void* pCand = (char*)this + 0x3c;
    if (mpWinCandidateList != 0)
        return;
    void* window = ((FPR0)VTOBJ(mpWinMgr)[4 / 4])(mpWinMgr);
    void* caller = FUN_009512c0();
    void* mem = FUN_009512d0(0x244, 4, g_name_IMECandidateList, caller);
    void* obj;
    if (mem) {
        obj = ((IMECandidateListCtor*)mem)->Ctor();
    } else {
        obj = 0;
    }
    ((AutoRefAssign*)pCand)->Assign(obj);
    if (*(void**)pCand == 0)
        return;
    SetupDefaultFonts();
    void* win = (char*)*(void**)pCand + 4;
    ((FVP)VTOBJ(window)[0xd8 / 4])(window, win);
    ((FVP)VTOBJ(window)[0xe8 / 4])(window, win);
    ((void(__thiscall*)(void*, int, int))VTOBJ(win)[0x7c / 4])(win, 4, 0);
    ((IMECandidateListInit*)mpWinCandidateList)->Init(mpMessageServer);
}

// @ 0x007F50F0
void IMEProxyS::StartComposition()
{
    if (!mbWinCompositionEnabled)
        return;
    if (mpWinComposition != 0)
        return;
    void* window = ((FPR0)VTOBJ(mpWinMgr)[4 / 4])(mpWinMgr);
    void* caller = FUN_009512c0();
    void* mem = FUN_009512d0(0x6c0, 8, g_name_mpWinComposition, caller);
    void* obj;
    if (mem) {
        obj = ((IMECompositionCtorStub*)mem)->Construct();
    } else {
        obj = 0;
    }
    ((AutoRefAssign*)((char*)this + 0x30))->Assign(obj);
    void* comp = mpWinComposition;
    ((FVI)VTOBJ((char*)comp + 4)[0x50 / 4])((char*)comp + 4, (int)0x7a7c0bb);
    if (mpWinComposition == 0)
        return;
    SetupDefaultFonts();
    void* win = (char*)mpWinComposition + 4;
    ((FVP)VTOBJ(window)[0xd8 / 4])(window, win);
    ((FVP)VTOBJ(window)[0xe8 / 4])(window, win);
    if (mPtX != 0x7fffffff) {
        struct Rect { float l, t, r, b; } rc;
        rc.l = (float)mPtX;
        rc.t = (float)mPtY;
        rc.r = (float)mPtX + g_compDx;
        rc.b = (float)mPtY + g_compDy;
        ((void(__thiscall*)(void*, void*))VTOBJ((char*)mpWinComposition + 4)[0x6c / 4])(
            (char*)mpWinComposition + 4, &rc);
    }
    ((void(__thiscall*)(void*, int, int))VTOBJ((char*)mpWinComposition + 4)[0x7c / 4])(
        (char*)mpWinComposition + 4, 4, 0);
    ((IMECompositionInit*)mpWinComposition)->Init(mpMessageServer);
}

// @ 0x007F5220
bool IMEProxyS::HandleMessage(uint32_t msgId, void* param)
{
    switch (msgId) {
    case 0x2ac44ed1: {
        void* comp = mpWinComposition;
        if (comp) {
            char c = ((FPCI)VTOBJ((char*)comp + 0x20c)[0x48 / 4])((char*)comp + 0x20c, 0x80);
            if (c)
                return true;
        }
        StartCandidateList();
        return true;
    }
    case 0x2ac44c0e: {
        void* mgr = EA_UTFWin_GetManager();
        void* w = ((FPRI)VTOBJ(mgr)[0x48 / 4])(mgr, 0);
        if (w) {
            void* t = ((FPRI)VTOBJ(w)[0xc / 4])(w, (int)0xcf428691);
            if (t) {
                char c = ((FPCI)VTOBJ(t)[0x48 / 4])(t, 0x80);
                if (c) {
                    int* p = *(int**)((char*)param + 0x10);
                    *p = 2;
                    StartComposition();
                    return true;
                }
                int* p = *(int**)((char*)param + 0x10);
                *p = 1;
            }
        }
        StartComposition();
        return true;
    }
    case 0x2ac44c11:
        ((IMEProxyMisc*)this)->M1();
        return true;
    case 0x2ac44ed4:
        ((IMEProxyMisc*)this)->M2();
        return true;
    }
    return true;
}

// @ 0x007F42E0  (best-effort complete translation; not byte-exact)
bool IMEProxyS::Update()
{
    if ((++mnTickCount & 3) != 0)
        return true;
    if (mpWinMgr == 0)
        return true;
    if (mpIMEServer == 0)
        return true;

    void* focus = ((FPR0)VTOBJ(mpWinMgr)[0x48 / 4])(mpWinMgr);
    bool bVar10 = false;
    if (mpWinLastFocus != focus) {
        char c = ((FPC0)VTOBJ(mpIMEServer)[0x1c / 4])(mpIMEServer);
        if (c != 0) {
            bool show = false;
            void* comp = mpWinComposition;
            if (comp) {
                void* q = (char*)comp + 0x20c;
                void* r = ((FPR0)VTOBJ(q)[0x10 / 4])(q);
                if (r != focus)
                    show = true;
            }
            void* cand = mpWinCandidateList;
            if (cand && (char*)cand + 4 != focus)
                show = true;
            if (show)
                ((FVI)VTOBJ(mpIMEServer)[0x20 / 4])(mpIMEServer, 0);
        }
        uint8_t localFlag = 0;
        void* mgr = FUN_0067de40();
        void* key = ((FPR0)VTOBJ(mgr)[0x14 / 4])(mgr);
        if (DoFindNode(key, g_ja_jp)) {
            interface_cast(focus);
        }
        if (((FPC0)VTOBJ(mpIMEServer)[0x1c / 4])(mpIMEServer) == 0) {
            int r = (int)((FPRI)VTOBJ(focus)[0xc / 4])(focus, (int)0xcf428691);
            if (r != 0) {
                ((FVI)VTOBJ(mpIMEServer)[0x20 / 4])(mpIMEServer, 1);
                bVar10 = true;
            }
        }
        mpWinLastFocus = focus;
        if (bVar10 || mbNonTextEditCompositionEnabled)
            bVar10 = true;
        bool bNonText = mbNonTextEditCompositionEnabled;
        mPtX = 0x7fffffff;
        mPtY = 0x7fffffff;
        if (!bNonText && focus != 0) {
            int r1 = (int)((FPRI)VTOBJ(focus)[0xc / 4])(focus, (int)0xcf428691);
            int r2 = 0, r3 = 0;
            if (r1 == 0) {
                r2 = (int)((FPRI)VTOBJ(mpWinLastFocus)[0xc / 4])(mpWinLastFocus, (int)0x1382be3e);
                if (r2 == 0)
                    r3 = (int)((FPRI)VTOBJ(mpWinLastFocus)[0xc / 4])(mpWinLastFocus, (int)0x9fedbcdb);
            }
            if (r1 != 0 || r2 != 0 || r3 != 0)
                bVar10 = true;
        }
        if (!bVar10) {
            struct Msg {
                uint32_t f0;
                uint32_t f4;
                uint32_t f8;
                uint32_t fc;
                uint32_t f10;
                void*    vt;      // +0x14
                uint32_t rc;      // +0x18
                uint32_t f1c;
                uint32_t f20;
                uint32_t a;       // +0x24
                uint32_t f28;
                uint32_t b;       // +0x2c
                uint32_t f30;
                void*    arg;     // +0x34
            } msg;
            msg.vt = &g_vt_13eb90c;
            msg.rc = 0;
            msg.a = 2;
            msg.b = 2;
            msg.arg = (void*)0xbe10a20;
            ((void(__thiscall*)(void*, int, Msg*, int))VTOBJ(mpMessageServer)[0x14 / 4])(
                mpMessageServer, (int)0xbe10a20, &msg, 0);
            if (*(uint32_t*)((char*)&msg + 0x18) != 0) {
                bool eq = (localFlag == 0);
                mPtX = *(int*)((char*)&msg + 0x24);
                mPtY = *(int*)((char*)&msg + 0x2c);
                if (!eq)
                    goto after;
            }
            if (((FPC0)VTOBJ(mpIMEServer)[0x1c / 4])(mpIMEServer)) {
                ((FVI)VTOBJ(mpIMEServer)[0x20 / 4])(mpIMEServer, 0);
            }
        after:
            ;
        }
    }
    return true;
}

// --------------------------------------------------------------------------
// IMEComposition (size 0x6a0)
// --------------------------------------------------------------------------
struct WinTextEditDtorStub { void Dtor(); };
struct IMECompositionS {
    char pad0[0x700];
    IMECompositionS* Construct();
    void Dtor();
    void SetFlag(int x);   // @ 0x7F4630
};

// @ 0x007F4920
IMECompositionS* IMECompositionS::Construct()
{
    ((WinTextEditCtor*)this)->Ctor();
    *(void**)((char*)this + 0x658) = &g_vt_13eb394;
    *(uint8_t*)((char*)this + 0x660) = 0;
    *(uint32_t*)((char*)this + 0x664) = 0;
    *(void**)((char*)this + 0x0) = &g_vt_1414fd0;
    *(void**)((char*)this + 0x4) = &g_vt_1414eb0;
    *(void**)((char*)this + 0x20c) = &g_vt_1414db8;
    *(void**)((char*)this + 0x658) = &g_vt_1414dac;
    *(uint32_t*)((char*)this + 0x688) = 0;
    *(uint32_t*)((char*)this + 0x68c) = 0;
    *(uint32_t*)((char*)this + 0x694) = 0;
    *(uint32_t*)((char*)this + 0x69c) = 0;
    *(uint32_t*)((char*)this + 0x698) = 0;
    *(uint32_t*)((char*)this + 0x6b8) = 0;
    *(uint32_t*)((char*)this + 0x6a8) = 0xffffffff;
    *(uint32_t*)((char*)this + 0x6ac) = 0xffffffff;
    *(uint32_t*)((char*)this + 0x6b0) = 0xffffffff;
    *(uint32_t*)((char*)this + 0x6b4) = 0xffffffff;
    return this;
}

// @ 0x007F4630
void IMECompositionS::SetFlag(int x)
{
    void* sub = (char*)this + 0x208;
    ((void(__thiscall*)(void*, int, int))VTOBJ(sub)[0x60 / 4])(sub, x, 1);
}

// @ 0x007F45B0
void IMECompositionS::Dtor()
{
    *(void**)((char*)this + 0x0) = &g_vt_1414fd0;
    *(void**)((char*)this + 0x4) = &g_vt_1414eb0;
    *(void**)((char*)this + 0x20c) = &g_vt_1414db8;
    *(void**)((char*)this + 0x658) = &g_vt_1414dac;
    void* p1 = *(void**)((char*)this + 0x694);
    if (p1 && *(int*)((char*)p1 - 4) != 0)
        deallocate(p1);
    void* p2 = *(void**)((char*)this + 0x68c);
    if (p2)
        ((FV0)VTOBJ(p2)[4 / 4])(p2);
    void* p3 = *(void**)((char*)this + 0x688);
    if (p3)
        ((FV0)VTOBJ(p3)[4 / 4])(p3);
    *(void**)((char*)this + 0x658) = &g_vt_13eb394;
    ((WinTextEditDtorStub*)this)->Dtor();
}

// @ 0x007F49B0  (partial: large candidate-list layout routine)
void IMECandidateListS_SetupWindow(void* self)
{
    (void)self;
}

// --------------------------------------------------------------------------
// IMEService (size 0xc)
// --------------------------------------------------------------------------
struct IMEServiceS {
    void* vftable;       // +0x00
    void* mpIMEServer;   // +0x04
    void* mpIMEProxy;    // +0x08
    bool Init();
};

// @ 0x007F4710
bool IMEServiceS::Init()
{
    void* server = EA_Messaging_GetServer();
    void* mem = op_new(0xd8, g_name_IMEServer, 0, 0, 0, 0);
    void* srv;
    if (mem) {
        srv = ((IMEServerWin32Ctor*)mem)->Ctor();
    } else {
        srv = 0;
    }
    mpIMEServer = srv;
    ((IMEServerWin32Ctor*)srv)->SetCanvas(SP_Canvas());
    ((IMEServerWin32Ctor*)srv)->SetSomething(FUN_0067dce0());
    ((void(__thiscall*)(void*, void*))VTOBJ(srv)[0x18 / 4])(srv, server);
    ((FV0)VTOBJ(srv)[4 / 4])(srv);

    void* pmem = op_new(0x44, g_name_IMEProxy, 0, 0, 0, 0);
    void* proxy;
    if (pmem) {
        *(void**)pmem = &g_vt_1414d84;
        _InterlockedExchange((long*)((char*)pmem + 4), 0);
        *(void**)pmem = &g_vt_1414ba4;
        *(uint8_t*)((char*)pmem + 8) = 0;
        *(uint32_t*)((char*)pmem + 0xc) = 0;
        *(uint32_t*)((char*)pmem + 0x10) = 0;
        *(uint32_t*)((char*)pmem + 0x14) = 0x7fffffff;
        *(uint32_t*)((char*)pmem + 0x18) = 0x7fffffff;
        *(uint8_t*)((char*)pmem + 0x1c) = 0;
        *(uint32_t*)((char*)pmem + 0x20) = 0;
        *(uint32_t*)((char*)pmem + 0x24) = 0;
        *(uint32_t*)((char*)pmem + 0x28) = 0;
        *(uint8_t*)((char*)pmem + 0x2c) = 1;
        *(uint32_t*)((char*)pmem + 0x30) = 0;
        *(uint32_t*)((char*)pmem + 0x34) = 0;
        *(uint8_t*)((char*)pmem + 0x38) = 1;
        *(uint32_t*)((char*)pmem + 0x3c) = 0;
        *(uint32_t*)((char*)pmem + 0x40) = 0;
        proxy = pmem;
    } else {
        proxy = 0;
    }
    void* old = mpIMEProxy;
    if (proxy != old) {
        if (proxy)
            ((FV0)VTOBJ(proxy)[8 / 4])(proxy);
        mpIMEProxy = proxy;
        if (old)
            ((FV0)VTOBJ(old)[0xc / 4])(old);
    }
    void* cur = mpIMEProxy;
    if (cur == 0)
        return false;
    return ((IMEProxyInit*)cur)->Init(mpIMEServer, this);
}

// @ 0x007F4860
void IMEServiceShutdown()
{
    if (g_pIMEProxy) {
        ((IMEProxyShutdown*)g_pIMEProxy)->Shutdown();
        void* p = g_pIMEProxy;
        if (p) {
            g_pIMEProxy = 0;
            ((FV0)VTOBJ(p)[0xc / 4])(p);
        }
    }
    if (g_pIMEServer) {
        void* p = g_pIMEServer;
        ((FV0)VTOBJ(p)[8 / 4])(p);
        if (g_pIMEServer) {
            ((void(__thiscall*)(void*, int))VTOBJ(g_pIMEServer)[0 / 4])(g_pIMEServer, 1);
        }
        g_pIMEServer = 0;
    }
}
