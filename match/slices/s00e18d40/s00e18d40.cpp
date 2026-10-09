// Slice s00e18d40 (gold0 slice 25).  Functions 0xe18d40 .. 0xe19d30.
// A UI panel manager derived from SP::cGonzagoSubsystem (mission-log / feedback /
// badges panel), plus a tiny skin-paint command method, a mission-log helper and a
// mission sort comparator.  Optimised module: /O2 /MD /Gy /EHsc /TP.
//
// Class layouts are reconstructed from the original disassembly; offsets not known
// from the 2008 PDB are modelled with a descriptor struct (fields + pad).  Real names
// for the panel class are not present in the dev PDB, so a descriptive stub name is
// used and the mangled symbol is matched by VA.
#include "types.h"

// ---------------------------------------------------------------- externs
void* operator new(unsigned size, const char* name, int flags, int line, const char* file, int line2); // EA 0xf473a0
inline void* operator new(unsigned, void* p) { return p; }
void  operator_delete__(void* p);                       // 0x00f47380

extern char vtbl_1480160[], vtbl_1480110[], vtbl_148010c[], vtbl_1480104[],
            vtbl_14800f4[], vtbl_1480080[], vtbl_14426a0[];

static inline void** Vt(void* p) { return *(void***)p; }
static inline void* pl(void* p) { return p; }

// ---------------------------------------------------------------- types
struct cSPUILayout {
    void* FindWindowByID(int id, int flag);             // 0x008105b0  (ret 8)
    void  SetVisibility(int v);                         // 0x00810590  (ret 4)
    bool  IsVisible();                                  // 0x00810070
    void  Shutdown(int v);                              // 0x00811ad0  (ret 4)
};

struct cGameTimeManager {
    bool IncPauseGate(void* k);                         // 0x00b32220
    bool DecPauseGate(void* k);                         // 0x00b32250
};
struct cWinMgr {                                        // cUIWindowManager
    bool FUN_00e2f3c0(int id);                          // 0x00e2f3c0
    void FUN_00e2f370();                                // 0x00e2f370
    void FUN_00e30dc0();                                // 0x00e30dc0
    void FUN_00e30e20(int a, int b, int c, int d, int e); // 0x00e30e20
    void FUN_00e31030(int a, int b, int c, int d);      // 0x00e31030
};
struct cTribeStrategy { bool FUN_00cd44a0(); };         // 0x00cd44a0
struct cSporepediaObj { bool FUN_01065e20(); };         // 0x01065e20
struct cVerbWin { void FUN_00663350(int x); };          // 0x00663350
struct cMissionManager { void* GetMissionList(); };      // 0x00fedd50
struct cSortMissions { bool operator()(int* a, int* b); }; // 0x00e19d30

namespace SP {
struct cGonzagoSubsystem {
    cGonzagoSubsystem();                                // 0x00b5b960
    ~cGonzagoSubsystem();                               // 0x00b5b9a0
    void PreGameModeTransition(int a, int b);           // 0x00b5b930
    void PostGameModeTransition(int a, int b);          // 0x00b5b900
};
struct cIGonzagoSubsystem { virtual void v0(); };
}

struct cMissionLog;   // fwd

// eastl-style map<unsigned, AutoRefCount<cFeedbackEvent>> embedded at cPanel+0x3c
struct cFeedbackTree {
    void* m00;          // +0x00  (panel 0x3c)
    void* mAnchor;      // +0x04  (panel 0x40) end node (self)
    void* mRoot;        // +0x08  (panel 0x44) root / begin
    int   mSize;        // +0x0c  (panel 0x48)
    char  mFlag;        // +0x10  (panel 0x4c)
    char  pad11[3];
    int   mSize2;       // +0x14  (panel 0x50)

    void  FUN_00e19160(void* node);                                  // 0x00e19160
    void* FUN_00e191a0(void* out, void* key, void* flag);            // 0x00e191a0
    void  FUN_00e18d40(void** out, void* pos, int* value, char flag); // 0x00e18d40
    void* FUN_00e5c780(void* out, void* key);                        // 0x00e5c780
};

struct cPanel {
    char          pad00[0x2c];
    int           mMode;         // +0x2c
    cSPUILayout*  mLayout;       // +0x30
    void*         mHolder;       // +0x34
    void*         mScrollRoot;   // +0x38
    cFeedbackTree mTree;         // +0x3c (0x18 bytes)
    char          pad54[4];      // +0x54
    void*         mBlurEffect;   // +0x58
    void*         mWinMgr;       // +0x5c
    void*         mMsgServer;    // +0x60
    void*         mHandlerPtr;   // +0x64
    void*         mHandlerId;    // +0x68
    int           mHandlerA;     // +0x6c
    int           mHandlerB;     // +0x70
    void*         mListNext;     // +0x74
    void*         mListPrev;     // +0x78

    cPanel();                                                       // 0x00e19680
    ~cPanel();                                                      // 0x00e193f0
    void FUN_00e188b0(int hash);                                    // 0x00e188b0
    void* FUN_00e18b10(void* p);                                    // 0x00e18b10
    void FUN_00e18b50();                                            // 0x00e18b50
    void FUN_00e18cb0(int id);                                      // 0x00e18cb0
    void FUN_00e18dd0(void* p, int a);                              // 0x00e18dd0
    void FUN_00e19010();                                            // 0x00e19010
    void FUN_00e190c0(void* p);                                     // 0x00e190c0
    bool FUN_00e192a0(int, void* msg);                              // 0x00e192a0
    void FUN_00e19350(unsigned key, int arg);                       // 0x00e19350
    void FUN_00e19590(int id, void* obj);                           // 0x00e19590
    void FUN_00e19630();                                            // 0x00e19630
    void FUN_00e19780();                                            // 0x00e19780
    void FUN_00e19820();                                            // 0x00e19820
    void FUN_00e19830(int a, int b);                                // 0x00e19830
    bool FUN_00e19850(int mode);                                    // 0x00e19850
    void FUN_00e19c40(int a, int b);                                // 0x00e19c40
};

// small mission-log UI object (list of ints at +0x34)
struct cMissionLog {
    char  pad00[0x18];
    void* mLayout;       // +0x18
    char  pad1c[0x34 - 0x1c];
    void* mListNext;     // +0x34 sentinel.next
    void* mListPrev;     // +0x38 sentinel.prev
    char  pad3c[0x6c - 0x3c];
    void* mField6c;      // +0x6c

    void FUN_00e19250(int value);                                   // 0x00e19250
    unsigned FUN_00e19c70(int mode);                                // 0x00e19c70
    void FUN_00e19d10(int x);                                       // 0x00e19d10
};

// tiny command object constructed at 0xe198f4 (vtable 0x1480080)
struct cSkinPaintClear {
    void* mpVtbl;        // +0x00
    int   mField4;       // +0x04
    int   mField8;       // +0x08
    void FUN_00e19230(int);                                         // 0x00e19230
};

// ---------------------------------------------------------------- callees
void* FUN_00b3d3f0();                                   // 0x00b3d3f0 sPanel getter
void* FUN_00b3d4d0();                                   // 0x00b3d4d0 trigger mgr getter
void* SP_GameTimeManager();                             // 0x00b3d380
void* SP_WindowManager();                               // 0x0067caa0
void* SP_EffectsManager();                              // 0x0067ddd0
void* SP_CheatManager();                                // 0x0067de20
void* SP_MessageServer();                               // 0x0067dcc0
void* EA_Audio_GetSystemAT();                           // 0x00a206f0
void* SP_GetMissionManager();                           // 0x00feb9f0
int   SP_GetCurrentGameMode();                          // 0x00b5b800
void* GET_CivModeStrategy();                            // 0x00cf74c0
void* SP_TribeModeStrategy_Instance();                  // 0x00cd40b0
void* FUN_010666a0();                                   // 0x010666a0

void  SPUIHelpers_BeginModal(void* win, int a, int b);  // 0x008099a0 (cdecl)
void  SPUIHelpers_EndModal(void* win, int a, int b);    // 0x00809c50 (cdecl)
void  SP_cSPUISpace_KillSetiEffects(int hash, void* a);  // 0x00435ed0 (cdecl)
void  EA_Messaging_RemoveHandler(void* s, void* a, void* b, void* c, void* d); // 0x00571db0
void* eastl_RBTreeInsert(void* node, void* pos, void* header, int flag); // 0x009216a0
void* eastl_RBTreeIncrement(void* node);                // 0x00921580
void* eastl_RBTreeDecrement(void* node);                // 0x009215c0
void  FUN_00c58360(void* key);                          // 0x00c58360

void* FUN_00e1f390();   // ctor of badges layout (0xe1f390)
void* FUN_00e1b2d0();   // ctor (0xe1b2d0)
void* FUN_01064a30();   // ctor (0x1064a30)
void* FUN_0107ae70();   // ctor (0x107ae70)
void* FUN_01063360();   // ctor (0x1063360)
void* FUN_00e31050();   // cUIFlashWindowManager ctor (0xe31050)

// =====================================================================
// @ 0x00e18d40
// =====================================================================
void cFeedbackTree::FUN_00e18d40(void** out, void* pos, int* value, char flag)
{
    char b = 0;
    if (flag == 0 && pos != &mAnchor && (unsigned)*value >= *(unsigned*)((char*)pos + 0x10))
        b = 1;
    char* node = (char*)operator new(0x18, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    char* v = node + 0x10;
    if (v) {
        *(int*)v = value[0];
        int* rc = (int*)value[1];
        *(int**)(v + 4) = rc;
        if (rc)
            (*(void(__thiscall**)(int*))((char*)(*(int**)rc) + 4))(rc);
    }
    eastl_RBTreeInsert(node, pos, &mAnchor, b);
    ++mSize2;
    *out = node;
}

// =====================================================================
// @ 0x00e19590
// =====================================================================
void cPanel::FUN_00e19590(int id, void* obj)
{
    if (obj) (*(void(__thiscall**)(void*))((char*)Vt(obj) + 4))(obj);
    int local10 = id;
    void* localc = obj;
    if (obj) (*(void(__thiscall**)(void*))((char*)Vt(obj) + 4))(obj);
    unsigned flag = (unsigned)obj & 0xffffff00u;
    mTree.FUN_00e191a0(&local10, &localc, &flag);
    if (obj) {
        (*(void(__thiscall**)(void*))((char*)Vt(obj) + 8))(obj);
        (*(void(__thiscall**)(void*))((char*)Vt(obj) + 8))(obj);
    }
    cSPUILayout* layout = mLayout;
    void* w1 = layout->FindWindowByID(-0xa, 1);
    void* w2 = layout->FindWindowByID(-4, 1);
    int mode = mMode;
    (*(void(__thiscall**)(void*, int, unsigned, void*, void*))((char*)Vt(obj) + 0x10))(obj, mode, flag, w2, w1);
}

// =====================================================================
// @ 0x00e192a0
// =====================================================================
bool cPanel::FUN_00e192a0(int, void* msg)
{
    int* m = (int*)msg;
    char bl = 0;
    int tag = m[2];
    if (tag == 1) {
        if (m[5] == 0 && (m[4] == 0x1b || m[4] == 0x4c)) {
            FUN_00e19010();
            return true;
        }
    } else if (tag == (int)0x287259f6) {
        int v = (*(int(__thiscall**)(int))((char*)Vt((void*)m[0]) + 0x1c))(m[0]);
        if (v == -0x10) {
            FUN_00e19010();
            return true;
        }
        if (FUN_00e18b10((void*)v) == 0)
            return false;
        void* at = EA_Audio_GetSystemAT();
        if (at)
            (*(void(__thiscall**)(void*))((char*)Vt(at) + 0x20))(at);
        SP_cSPUISpace_KillSetiEffects(0xc1f95c5a, at);
        FUN_00e18dd0((void*)v, 0);
        return true;
    }
    return bl != 0;
}

// =====================================================================
// @ 0x00e19250
// =====================================================================
void cMissionLog::FUN_00e19250(int value)
{
    char* sentinel = (char*)this + 0x34;
    char* node = (char*)operator new(0xc, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int* v = (int*)(node + 8);
    if (v) *v = value;
    *(void**)node = sentinel;
    *(void**)(node + 4) = *(void**)(sentinel + 4);
    **(void***)(sentinel + 4) = node;
    *(void**)(sentinel + 4) = node;
}

// =====================================================================
// @ 0x00e193f0  (destructor)
// =====================================================================
cPanel::~cPanel()
{
    *(void**)this = vtbl_1480160;
    *(void**)((char*)this + 4) = vtbl_1480110;
    *(void**)((char*)this + 8) = vtbl_148010c;
    *(void**)((char*)this + 0x20) = vtbl_1480104;
    *(void**)((char*)this + 0x24) = vtbl_14800f4;

    void* node = mListNext;
    void* sent = (char*)this + 0x74;
    while (node != sent) {
        void* nxt = *(void**)node;
        operator_delete__(node);
        node = nxt;
    }
    if (mMsgServer) {
        mMsgServer = 0;
        EA_Messaging_RemoveHandler(mMsgServer, mHandlerPtr, mHandlerId, (void*)mHandlerA, (void*)mHandlerB);
    }
    if (mWinMgr)  (*(void(__thiscall**)(void*))((char*)Vt(mWinMgr) + 8))(mWinMgr);
    if (mBlurEffect) (*(void(__thiscall**)(void*))((char*)Vt(mBlurEffect) + 4))(mBlurEffect);
    mTree.FUN_00e19160(*(void**)((char*)this + 0x48));
    if (mScrollRoot) (*(void(__thiscall**)(void*))((char*)Vt(mScrollRoot) + 8))(mScrollRoot);
    if (mLayout)     (*(void(__thiscall**)(void*))((char*)Vt(mLayout) + 8))(mLayout);
    *(void**)((char*)this + 0x24) = vtbl_14426a0;
    *(void**)((char*)this + 0x20) = vtbl_1480160;
    SP::cGonzagoSubsystem* g = (SP::cGonzagoSubsystem*)((char*)this + 4);
    g->~cGonzagoSubsystem();
    *(void**)this = vtbl_14426a0;
}

// =====================================================================
// @ 0x00e19680  (constructor)
// =====================================================================
cPanel::cPanel()
{
    *(void**)this = vtbl_14426a0;
    SP::cGonzagoSubsystem* g = (SP::cGonzagoSubsystem*)((char*)this + 4);
    new (g) SP::cGonzagoSubsystem();
    *(void**)((char*)this + 0x20) = vtbl_1480104;
    *(void**)((char*)this + 0x24) = vtbl_14800f4;
    *(void**)this = vtbl_1480160;
    *(void**)((char*)this + 4) = vtbl_1480110;
    *(void**)((char*)this + 8) = vtbl_148010c;
    *(void**)((char*)this + 0x20) = vtbl_1480104;
    *(void**)((char*)this + 0x24) = vtbl_14800f4;
    mMode = -1;
    mHolder = 0;
    mScrollRoot = 0;
    mTree.m00 = 0;
    mTree.mAnchor = (char*)this + 0x40;
    mTree.mRoot = (char*)this + 0x40;
    mTree.mSize = 0;
    mTree.mFlag = 0;
    mTree.mSize2 = 0;
    *(void**)((char*)this + 0x54) = 0;
    mBlurEffect = 0;
    mWinMgr = 0;
    mMsgServer = 0;
    mHandlerPtr = 0;
    mHandlerId = 0;
    mHandlerA = 0;
    mHandlerB = 0;
    void* list = (char*)this + 0x74;
    *(void**)list = list;
    *(void**)((char*)list + 4) = list;
    int tag = 0x65ff54a;
    void* srv = SP_MessageServer();
    mMsgServer = srv;
    mHandlerPtr = (char*)this + 0x20;
    mHandlerId = &tag;
    mHandlerA = 1;
    mHandlerB = 0;
    if (srv && mHandlerPtr)
        (*(void(__thiscall**)(void*, void*, int))((char*)Vt(srv) + 0x24))(srv, mHandlerPtr, tag);
}

// =====================================================================
// @ 0x00e19630
// =====================================================================
void cPanel::FUN_00e19630()
{
    char* self = (char*)this;
    void* it = *(void**)(self + 0x44);
    char* end = self + 0x40;
    while (it != end) {
        void* ev = *(void**)((char*)it + 0x14);
        (*(void(__thiscall**)(void*))((char*)Vt(ev) + 0x14))(ev);
        it = eastl_RBTreeIncrement(it);
    }
    mTree.FUN_00e19160(*(void**)(self + 0x48));
    void* a = self + 0x40;
    *(void**)(self + 0x44) = a;
    *(void**)a = a;
    *(int*)(self + 0x48) = 0;
    *(char*)(self + 0x4c) = 0;
    *(int*)(self + 0x50) = 0;
}

// =====================================================================
// @ 0x00e19010
// =====================================================================
void cPanel::FUN_00e19010()
{
    if (!mLayout || !mLayout->IsVisible()) return;
    FUN_00e18b50();
    SPUIHelpers_EndModal(mLayout->FindWindowByID(-1, 1), 0, 0);
    if (mBlurEffect) {
        (*(void(__thiscall**)(void*, int))((char*)Vt(mBlurEffect) + 0xc))(mBlurEffect, 1);
        if (mBlurEffect) {
            void* old = mBlurEffect;
            mBlurEffect = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 4))(old);
        }
    }
    void* at = EA_Audio_GetSystemAT();
    void* a = at ? (void*)(*(int(__thiscall**)(void*))((char*)Vt(at) + 0x20))(at) : 0;
    SP_cSPUISpace_KillSetiEffects(0x5dc7f7a6, a);
    mLayout->SetVisibility(0);
    if (mScrollRoot) (*(void(__thiscall**)(void*))((char*)Vt(mScrollRoot) + 0x20))(mScrollRoot);
    cGameTimeManager* gt = (cGameTimeManager*)SP_GameTimeManager();
    gt->DecPauseGate((void*)0x4bf38a4);
}

// =====================================================================
// @ 0x00e190c0
// =====================================================================
void cPanel::FUN_00e190c0(void* p)
{
    if (mLayout && mLayout->IsVisible() && (p == 0 || FUN_00e18b10(p) == mScrollRoot)) {
        FUN_00e19010();
        return;
    }
    if (SP_GetCurrentGameMode() == (int)0x1654c04) {
        if (*(char*)((char*)GET_CivModeStrategy() + 0x148)) return;
    }
    if (SP_GetCurrentGameMode() == (int)0x1654c02) {
        cTribeStrategy* t = (cTribeStrategy*)SP_TribeModeStrategy_Instance();
        if (t->FUN_00cd44a0()) return;
    }
    if (SP_GetCurrentGameMode() == (int)0x1654c05) {
        if (((cSporepediaObj*)FUN_010666a0())->FUN_01065e20()) return;
    }
    FUN_00e18dd0(p, 0);
}

// =====================================================================
// @ 0x00e18dd0
// =====================================================================
void cPanel::FUN_00e18dd0(void* p, int)
{
    int state = *(int*)((char*)FUN_00b3d4d0() + 0x2c);
    if (state == 1 || state == 2) return;

    void* wm = SP_WindowManager();
    int r = (*(int(__thiscall**)(void*))((char*)Vt(wm) + 0x84))(wm);
    if (r != 0) {
        void* wm2 = SP_WindowManager();
        void* a = mLayout->FindWindowByID(-1, 1);
        int r2 = (*(int(__thiscall**)(void*))((char*)Vt(wm2) + 0x84))(wm2);
        if (a != (void*)r2) return;
    }
    if (mLayout && mLayout->IsVisible() && p) {
        if (mScrollRoot) (*(void(__thiscall**)(void*))((char*)Vt(mScrollRoot) + 0x20))(mScrollRoot);
        FUN_00e190c0(p);
        if (mScrollRoot) {
            (*(void(__thiscall**)(void*, void*))((char*)Vt(mScrollRoot) + 0x1c))(mScrollRoot, p);
        }
        return;
    }
    if (!mLayout) return;
    if (mWinMgr) {
        if (!((cWinMgr*)mWinMgr)->FUN_00e2f3c0(0x6244208))
            FUN_00e18b50();
    }
    mLayout->SetVisibility(1);
    void* at = EA_Audio_GetSystemAT();
    void* a = at ? (void*)(*(int(__thiscall**)(void*))((char*)Vt(at) + 0x20))(at) : 0;
    SP_cSPUISpace_KillSetiEffects(0xea8555f2, a);
    if (p) FUN_00e190c0(p);
    if (mScrollRoot) {
        (*(void(__thiscall**)(void*, void*))((char*)Vt(mScrollRoot) + 0x1c))(mScrollRoot, p);
    }
    {
        void* node = *(void**)((char*)this + 0x44);
        char* end = (char*)this + 0x40;
        while (node != end) {
            int* ev = *(int**)((char*)node + 0x14);
            void* win = mLayout->FindWindowByID(*(int*)((char*)node + 0x10), 1);
            if (win) {
                unsigned char c = (*(unsigned char(__thiscall**)(int*))((char*)(*(int**)ev) + 0x24))(ev);
                (*(void(__thiscall**)(void*, int, unsigned char))((char*)Vt(win) + 0x7c))(win, 2, c);
            }
            node = eastl_RBTreeIncrement(node);
        }
    }
    {
        void* em = SP_EffectsManager();
        void* slot = (char*)this + 0x58;
        void* old = *(void**)slot;
        if (old) {
            *(void**)slot = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 4))(old);
        }
        char ok = (*(char(__thiscall**)(void*, int, int, void*))((char*)Vt(em) + 0x2c))(em, 0x4c4ba0a9, 0, slot);
        if (ok) {
            void* cur = *(void**)slot;
            (*(void(__thiscall**)(void*, int))((char*)Vt(cur) + 8))(cur, 0);
        }
    }
    if (mMode != (int)0x1654c05) {
        void* win = mLayout->FindWindowByID(-1, 1);
        SPUIHelpers_BeginModal(win, 0, 1);
    }
    {
        void* wm = SP_WindowManager();
        void* win = mLayout->FindWindowByID(-1, 1);
        (*(void(__thiscall**)(void*, int, void*))((char*)Vt(wm) + 0x4c))(wm, 0, win);
    }
    cGameTimeManager* gt = (cGameTimeManager*)SP_GameTimeManager();
    gt->IncPauseGate((void*)0x4bf38a4);
    for (void* n = *(void**)((char*)this + 0x74); n != (void*)((char*)this + 0x74); n = *(void**)n) {
        ((cWinMgr*)mWinMgr)->FUN_00e30e20(*(int*)((char*)n + 8), 0x6244208, (int)0xce0a0762, 1, 0x68b5a48);
    }
}

// =====================================================================
// @ 0x00e19230
// =====================================================================
void cSkinPaintClear::FUN_00e19230(int)
{
    cPanel* p = (cPanel*)FUN_00b3d3f0();
    p->FUN_00e190c0(0);
}

// =====================================================================
// @ 0x00e19350
// =====================================================================
void cPanel::FUN_00e19350(unsigned key, int arg)
{
    unsigned k = key;
    unsigned local4;
    local4 = 0;
    void* it = 0;
    unsigned* out = &local4;
    mTree.FUN_00e5c780(out, &k);
    it = (void*)local4;
    char* end = (char*)this + 0x40;
    if (it == end) return;

    if (mWinMgr) {
        if (!((cWinMgr*)mWinMgr)->FUN_00e2f3c0(0x6244208))
            FUN_00e18b50();
        ((cWinMgr*)mWinMgr)->FUN_00e31030(0x6244208, 0x77e5a05, 0, 0);
    }
    void* ev = *(void**)((char*)it + 0x14);
    (*(void(__thiscall**)(void*, int))((char*)Vt(ev) + 0x28))(ev, arg);
    {
        void* n = *(void**)((char*)this + 0x74);
        char* sent = (char*)this + 0x74;
        while (n != sent && *(unsigned*)((char*)n + 8) != key)
            n = *(void**)n;
        if (n != sent) return;
    }
    unsigned kk = key;
    FUN_00c58360(&kk);
}

// =====================================================================
// @ 0x00e19780
// =====================================================================
void cPanel::FUN_00e19780()
{
    void* cm = SP_CheatManager();
    if (cm)
        (*(void(__thiscall**)(void*, const char*))((char*)Vt(cm) + 0x1c))(cm, "missionlog");
    if (mWinMgr) {
        ((cWinMgr*)mWinMgr)->FUN_00e30dc0();
        if (mWinMgr) {
            void* old = mWinMgr;
            mWinMgr = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 8))(old);
        }
    }
    if (mBlurEffect) {
        (*(void(__thiscall**)(void*, int))((char*)Vt(mBlurEffect) + 0xc))(mBlurEffect, 1);
        if (mBlurEffect) {
            void* old = mBlurEffect;
            mBlurEffect = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 4))(old);
        }
    }
    if (mScrollRoot) {
        void* old = mScrollRoot;
        mScrollRoot = 0;
        (*(void(__thiscall**)(void*))((char*)Vt(old) + 8))(old);
    }
    FUN_00e19630();
    if (mLayout) {
        mLayout->Shutdown(1);
        if (mLayout) {
            void* old = mLayout;
            mLayout = 0;
            (*(void(__thiscall**)(void*))((char*)Vt(old) + 8))(old);
        }
    }
}

// =====================================================================
// @ 0x00e19820
// =====================================================================
void cPanel::FUN_00e19820()
{
    ((cPanel*)((char*)this - 4))->FUN_00e19780();
}

// =====================================================================
// @ 0x00e19830
// =====================================================================
void cPanel::FUN_00e19830(int a, int b)
{
    SP::cGonzagoSubsystem* g = (SP::cGonzagoSubsystem*)this;
    g->PreGameModeTransition(a, b);
    ((cPanel*)((char*)this - 4))->FUN_00e19780();
}

// =====================================================================
// @ 0x00e19850
// =====================================================================
bool cPanel::FUN_00e19850(int mode)
{
    FUN_00e19780();
    mMode = mode;
    int id;
    switch (mode) {
    case (int)0x1654c00:
        FUN_00e188b0(0x375e8335);
        {
            void* o = operator new(0xe8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1f390() : 0;
            FUN_00e19590(-0xf, o);
        }
        id = -0xf;
        break;
    case (int)0x1654c01:
        FUN_00e188b0(0x2a843c80);
        {
            void* o = operator new(0xe8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1f390() : 0;
            FUN_00e19590(-0xf, o);
            void* o2 = operator new(0x98, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o2 = o2 ? FUN_00e1b2d0() : 0;
            FUN_00e19590(-0xe, o2);
        }
        id = -0xe;
        break;
    case (int)0x1654c02:
        FUN_00e188b0(0x71b4193f);
        {
            void* o = operator new(0xe8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1f390() : 0;
            FUN_00e19590(-0xf, o);
            void* o2 = operator new(0xe8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o2 = o2 ? FUN_00e1f390() : 0;
            FUN_00e19590(0x6722bd6, o2);
            void* o3 = operator new(0x98, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o3 = o3 ? FUN_00e1b2d0() : 0;
            FUN_00e19590(-0xe, o3);
        }
        id = -0xe;
        break;
    case (int)0x1654c04:
        FUN_00e188b0(0x5f7781f5);
        {
            void* o = operator new(0x98, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1b2d0() : 0;
            FUN_00e19590(-0xe, o);
        }
        id = -0xe;
        break;
    case (int)0x1654c05:
        FUN_00e188b0(0xd9b09d9d);
        {
            void* o = operator new(0x98, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o = o ? FUN_00e1b2d0() : 0;
            FUN_00e19590(-0xe, o);
            void* o2 = operator new(0xd8, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o2 = o2 ? FUN_01064a30() : 0;
            FUN_00e19590(-0xd, o2);
            void* o3 = operator new(0x150, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o3 = o3 ? FUN_0107ae70() : 0;
            FUN_00e19590(-0xb, o3);
            void* o4 = operator new(0x1b0, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            o4 = o4 ? FUN_01063360() : 0;
            FUN_00e19590(-0xc, o4);
        }
        id = -0xe;
        break;
    default:
        return false;
    }
    FUN_00e18cb0(id);
    if (SP_CheatManager()) {
        void* cmd = operator new(0x10, "Simulator", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        if (cmd) {
            (*(void(__thiscall**)(void*))0x0083c800)(cmd);
            *(void**)cmd = vtbl_1480080;
        }
    }
    {
        void* wm = operator new(0x58, "UI/cUIFlashWindowManager", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        wm = wm ? FUN_00e31050() : 0;
        void* old = mWinMgr;
        if (wm != old) {
            if (wm) (*(void(__thiscall**)(void*))((char*)Vt(wm) + 4))(wm);
            mWinMgr = wm;
            if (old) (*(void(__thiscall**)(void*))((char*)Vt(old) + 8))(old);
        }
    }
    ((cWinMgr*)mWinMgr)->FUN_00e2f370();
    return true;
}

// =====================================================================
// @ 0x00e19c40
// =====================================================================
void cPanel::FUN_00e19c40(int a, int b)
{
    SP::cGonzagoSubsystem* g = (SP::cGonzagoSubsystem*)this;
    g->PostGameModeTransition(a, b);
    ((cPanel*)((char*)this - 4))->FUN_00e19850(b);
}

// =====================================================================
// @ 0x00e19c70
// =====================================================================
unsigned cMissionLog::FUN_00e19c70(int mode)
{
    unsigned r = 0;
    switch (mode) {
    case (int)0x1654c01: r = 0xdb4fc333; break;
    case (int)0x1654c02: r = 0xe9c06b4e; break;
    case (int)0x1654c04: r = 0x355fd400; break;
    case (int)0x1654c05: r = 0x1cfaca92; break;
    }
    return r;
}

// =====================================================================
// @ 0x00e19d10
// =====================================================================
void cMissionLog::FUN_00e19d10(int x)
{
    if (((cSPUILayout*)mLayout)->IsVisible() && mField6c) {
        ((cVerbWin*)mField6c)->FUN_00663350(x);
    }
}

// ---------------------------------------------------------------- helper callees
// @ 0x00e19160
void cFeedbackTree::FUN_00e19160(void* node)
{
    while (node) {
        FUN_00e19160(*(void**)node);
        void* next = *(void**)((char*)node + 4);
        void* ev = *(void**)((char*)node + 0x14);
        if (ev) (*(void(__thiscall**)(void*))((char*)Vt(ev) + 8))(ev);
        operator_delete__(node);
        node = next;
    }
}

// @ 0x00e191a0
void* cFeedbackTree::FUN_00e191a0(void* out, void* key, void* flag)
{
    (void)flag;
    void* y = &mAnchor;
    char less = 1;
    if (m00) {
        void* x = m00;
        do {
            y = x;
            less = *(unsigned*)key < *(unsigned*)((char*)y + 0x10);
            x = less ? *(void**)((char*)y + 4) : *(void**)y;
        } while (x);
    }
    void* j = y;
    if (less) {
        if (y == mRoot) goto insert;
        j = eastl_RBTreeDecrement(y);
    }
    if (*(unsigned*)key <= *(unsigned*)((char*)j + 0x10)) {
        *(void**)out = j;
        *((char*)out + 4) = 0;
        return out;
    }
insert:
    FUN_00e18d40((void**)out, y, (int*)key, 0);
    *((char*)out + 4) = 1;
    return out;
}

// =====================================================================
// @ 0x00e19d30
// =====================================================================
bool cSortMissions::operator()(int* a, int* b)
{
    int* pa = a ? (int*)(*(int(__thiscall**)(int*, int))((char*)(*(int**)a) + 0xc))(a, 0x2aa5ada) : 0;
    int* pb = b ? (int*)(*(int(__thiscall**)(int*, int))((char*)(*(int**)b) + 0xc))(b, 0x2aa5ada) : 0;
    void* list = ((cMissionManager*)SP_GetMissionManager())->GetMissionList();
    int* cur = (int*)*(int*)list;
    int n = (*((int*)list + 1) - (int)cur) >> 2;
    int k1 = -1;
    int k2 = -1;
    for (int i = 0; i < n; ++i) {
        int v = *cur;
        if (v == (int)pa) k1 = i;
        else if (v == (int)pb) k2 = i;
        if (k1 != -1 && k2 != -1) break;
        ++cur;
    }
    return k1 < k2;
}
