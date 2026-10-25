// Slice s007e5220 (part 1: tractable functions).
#include "s007e5220.h"

HHOOK gSuppressAppSwitchHook;   // 0x16393a4
IPropertyList* gAppProperties;  // 0x15fd918
uint32_t gSleepMs;              // 0x153fb30

// @ 0x007E5E80
int cAppSystem::FUN_007e5e80() {
    return --mURLCount;
}

// @ 0x007E5ED0
void cAppSystem::DeactivateApp() {
    mMinimize = true;
    if (mLockCount)
        SP_MessageServer()->SendMessage(0x462dde3, 0, 0, 0);
}

// @ 0x007E5F00
void cAppSystem::ToggleFullscreen() {
    bool locked = mLockCount != 0;
    mToggleFullscreen = true;
    if (locked)
        SP_MessageServer()->SendMessage(0x462dde3, 0, 0, 0);
}

// @ 0x007E5F30
void cAppSystem::ToggleDisplay() {
    bool locked = mLockCount != 0;
    mToggleDisplay = true;
    if (locked)
        SP_MessageServer()->SendMessage(0x462dde3, 0, 0, 0);
}

// @ 0x007E6020
void cAppSystem::UnlockFromDevice() {
    if (--mLockCount == 0 && gSuppressAppSwitchHook) {
        UnhookWindowsHookEx(gSuppressAppSwitchHook);
        gSuppressAppSwitchHook = 0;
    }
}

// @ 0x007E6050
void cAppSystem::SetEffectCollectionIDs(uint32_t* ids, void* collections) {
    mEffectCollectionIDs = ids;
    if (collections)
        mEffectCollections = collections;
}

// @ 0x007E5D90
void LockToSingleCore() {
    DWORD pid = GetCurrentProcessId();
    HANDLE h = OpenProcess(0x1f0fff, 0, pid);
    ULONG_PTR local_8[2];
    local_8[1] = 0;
    local_8[0] = 0;
    GetProcessAffinityMask(h, local_8 + 1, local_8);
    SetProcessAffinityMask(h, 1);
    CloseHandle(h);
}

// @ 0x007E5E10
void FUN_007e5e10() {
    HWND hwnd = GetForegroundWindow();
    if (hwnd != 0) {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        if (GetCurrentProcessId() == pid)
            return;
    }
    if (gAppProperties->HasProperty(0x4b))
        gSleepMs = gAppProperties->GetIntProperty(0x4b);
    if (gSleepMs > 0)
        ThreadSleep(&gSleepMs);
}

// @ 0x007E5F60
LRESULT __stdcall SuppressAppSwitchProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == 0) {
        KBDLLHOOKSTRUCT_* kb = (KBDLLHOOKSTRUCT_*)lParam;
        SHORT ctrl = GetAsyncKeyState(0x11);
        if ((kb->vkCode == 0x1b && ctrl < 0) ||
            (kb->vkCode == 9 && (kb->flags & 0x20)) ||
            (kb->vkCode == 0x1b && (kb->flags & 0x20))) {
            SP_AppSystem()->v60();
            return 1;
        }
    }
    return CallNextHookEx(gSuppressAppSwitchHook, code, wParam, lParam);
}

// @ 0x007E5FD0
void cAppSystem::LockToDevice() {
    if (mLockCount++ == 0) {
        if (SP_Canvas()->v54())
            gSuppressAppSwitchHook = SetWindowsHookExA(0xd, (void*)&SuppressAppSwitchProc,
                                                       GetModuleHandleA(0), 0);
    }
}

// @ 0x007E6090
void cAppSystem::LoaderCommandHandler() {
    mFieldC0 = (mURLCount > 0) ? 1.0f : 0.0f;
    mFieldC4 = mCanvas->v44() ? 1.0f : 0.0f;
    FUN_00777ae0(0x248, &mGameInfoPaused, 0);
    LoaderVtbl* p = (LoaderVtbl*)FUN_0067dd50();
    if (p)
        p->vf15(0);
}

// ===========================================================================
// Harder slice functions (EASTL / EH heavy).
// ===========================================================================
extern void* gVtbl_13eb384; extern void* gVtbl_13ef094; extern void* gVtbl_1413628;
extern void* gVtbl_1413614; extern void* gVtbl_1413610; extern void* gVtbl_154df28;
extern char  gEmptyStringData[];      // 0x01667bac (empty string byte)
extern char  gEmptyStringObj[];       // 0x013ec47c (empty eastl::string)

void StringAssign(void* self, const void* s);
struct EaStringOps {
    void assign(const char* first, const char* last);  // 0x454cb0
};
void MakeCaseInsensitive(void* p);                      // 0x008409b0
void FUN_007e5a30(void* p);            // cActionsVec::push_back (thiscall, modelled as free for sibling use)
void FUN_00693230(void* self, void* a, void* b);        // hashtable clear/deallocate (this + begin/end)
void FUN_0093dc70(void* self, void* a, void* b);        // hashtable clear/deallocate (this + begin/end)

// ---- eastl::vector<SP::cAppStateManager::cActions, sp_vector_allocator> ----
struct cActions;                       // sizeof == 0x50
struct cActionsVec {                   // eastl::vector<cActions,sp_vector_allocator>
    cActions* mpBegin;                 // +0x00
    cActions* mpEnd;                   // +0x04
    cActions* mpCapacity;              // +0x08
    cActions* erase(cActions* first, cActions* last);          // 0x007e5830
    void      push_back(const cActions* value);                // 0x007e5a30
    void      insert(cActions* pos, const cActions* value);    // 0x007e5890
};
struct cActions {                      // sizeof == 0x50
    void* mEntry[5];                   // +0x00  eastl::vector<cActionMessage>
    void* mExit[5];                    // +0x14
    void* mHandler[5];                 // +0x28
    void* mNameBegin;                  // +0x3c  eastl::basic_string<char>
    void* mNameEnd;                    // +0x40
    void* mNameCapacity;               // +0x44
    void* mNameAllocator;              // +0x48
    int   field4c;                     // +0x4c
    cActions() {                       // default ctor: 3 sub-vectors + eastl empty string
        mEntry[0] = mEntry[1] = mEntry[2] = 0;
        mExit[0] = mExit[1] = mExit[2] = 0;
        mHandler[0] = mHandler[1] = mHandler[2] = 0;
        mNameBegin = gEmptyStringData;
        mNameEnd = gEmptyStringData;
        mNameCapacity = gEmptyStringData + 1;
        field4c = -1;
    }
    cActions& operator=(const cActions& o);    // 0x007e34a0
    void      copy_ctor(const cActions& o);    // 0x007e2ae0
    ~cActions();                               // 0x007e2680 (thiscall)
};
cActions* FUN_007e3e20(cActions* first, cActions* last, cActions* dst);  // copy-assign range
cActions* FUN_007e3e90(cActions* first, cActions* last, cActions* dstEnd);
cActions* FUN_007e2c10(cActions* first, cActions* last, cActions* dst);  // copy-construct range
cActions* FUN_007e2ca0(cActions* first, cActions* last, cActions* dst);  // move-construct range
int*      FUN_006a8340(void* self, void* arg);                           // hashtable lookup
int*      FUN_007c3a90(void* self, void* arg);                           // hash_map::operator[]
void      FUN_00645ed0(void* self, void* out, void* key);                // hashtable::find
void*     FUN_007e30f0(void* p);
void*     FUN_00f473a0(int size, const char* name, int a, int b, const char* file, int line);
void      FUN_00f47380(void* p);
extern char gAllocName_13ebc58[];      // 0x013ebc58
extern char gAllocFile_13ebb38[];      // 0x013ebb38

// @ 0x007E5220  (cAppStateManager constructor: member/subobject initialisation)
struct cAppStateManagerC { void* ctor(); void Update(); };
void* cAppStateManagerC::ctor() {
    char* p = (char*)this;
    *(void**)(p + 4)    = &gVtbl_13eb384;
    *(uint32_t*)(p + 0x10) = 0xceee7649;
    *(void**)(p + 8)    = &gVtbl_13ef094;
    *(uint32_t*)(p + 0xc)  = 0;
    *(void**)(p + 0)    = &gVtbl_1413628;
    *(void**)(p + 4)    = &gVtbl_1413614;
    *(void**)(p + 8)    = &gVtbl_1413610;
    *(uint32_t*)(p + 0x14) = 0;
    *(void**)(p + 0x18) = gEmptyStringData;
    *(void**)(p + 0x1c) = gEmptyStringData;
    *(void**)(p + 0x20) = gEmptyStringData + 1;
    *(uint32_t*)(p + 0x28) = 0xffffffff;
    *(uint32_t*)(p + 0x2c) = 0; *(uint32_t*)(p + 0x30) = 0; *(uint32_t*)(p + 0x34) = 0;
    *(uint32_t*)(p + 0x40) = 0; *(uint32_t*)(p + 0x44) = 0; *(uint32_t*)(p + 0x48) = 0;
    *(uint32_t*)(p + 0x54) = 0; *(uint32_t*)(p + 0x58) = 0; *(uint32_t*)(p + 0x5c) = 0;
    *(void**)(p + 0x68) = gEmptyStringData;
    *(void**)(p + 0x6c) = gEmptyStringData;
    *(void**)(p + 0x70) = gEmptyStringData + 1;
    *(uint32_t*)(p + 0x78) = 0xffffffff;
    *(uint32_t*)(p + 0x7c) = 0xffffffff;
    *(uint8_t*)(p + 0x80) = 0;
    *(uint8_t*)(p + 0x81) = 0;
    *(uint32_t*)(p + 0x84) = 0;
    *(uint32_t*)(p + 0x88) = 0xffffffff;
    *(uint32_t*)(p + 0x8c) = 0xffffffff;
    *(uint32_t*)(p + 0x90) = 0; *(uint32_t*)(p + 0x94) = 0; *(uint32_t*)(p + 0x98) = 0;
    *(uint32_t*)(p + 0xa4) = 0; *(uint32_t*)(p + 0xa8) = 0; *(uint32_t*)(p + 0xac) = 0;
    for (int off = 0xbc; off <= 0xfc; off += 0x20) {
        *(void**)(p + off)        = &gVtbl_154df28;
        *(uint32_t*)(p + off + 4) = 1;
        *(uint32_t*)(p + off + 8) = 0;
        *(float*)(p + off + 0xc)  = 1.0f;
        *(float*)(p + off + 0x10) = 2.0f;
        *(uint32_t*)(p + off + 0x14) = 0;
    }
    *(uint32_t*)(p + 0x118) = 0; *(uint32_t*)(p + 0x11c) = 0; *(uint32_t*)(p + 0x120) = 0;
    *(uint32_t*)(p + 0x12c) = 0; *(uint32_t*)(p + 0x130) = 0; *(uint32_t*)(p + 0x134) = 0;
    for (int off = 0x140; off <= 0x160; off += 4)
        *(uint32_t*)(p + off) = 0;
    *(void**)(p + 0x164) = gEmptyStringData;
    *(void**)(p + 0x168) = gEmptyStringData;
    *(void**)(p + 0x16c) = gEmptyStringData + 1;
    return p;
}

// ---- cAppStateManager::Init helpers (ArgScript parser / cheat manager) ----
struct ParserIface {                   // EA::ArgScript::IParser
    virtual void  v00();                                   //  0
    virtual void  v04();                                   //  1
    virtual void  v08();                                   //  2
    virtual void  v0c();                                   //  3
    virtual void  v10(void*);                              //  4
    virtual void  v14(const char* name, void* cmd);        //  5
    virtual void  f18(); virtual void  f1c(); virtual void  f20(); virtual void  f24();
    virtual void  f28(); virtual void  f2c(); virtual void  f30(); virtual void  f34();
    virtual void  f38(); virtual void  f3c(); virtual void  f40(); virtual void  f44();
    virtual void  f48(); virtual void  f4c(); virtual void  f50(); virtual void  f54();
    virtual void  f58(); virtual void  f5c(); virtual void  f60(); virtual void  f64();
    virtual void  f68(); virtual void  f6c(); virtual void  f70(); virtual void  f74();
    virtual void  f78(); virtual void  f7c(); virtual void  f80(); virtual void  f84();
    virtual void  f88(); virtual void  f8c(); virtual void  f90(); virtual void  f94();
    virtual void  f98(); virtual void  f9c(); virtual void  fa0(); virtual void  fa4();
    virtual void  fa8(); virtual void  fac(); virtual void  fb0(); virtual void  fb4();
    virtual void* vB8(void* a, void* b);                   // 46
};
struct StateObjIface {                 // *(this+0x154): cAppState / cStateMachine
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual bool v20();                                    // +0x20
    virtual void s24();                                    // +0x24
    virtual bool v28();                                    // +0x28
};
struct StateCmdIface {                 // anonymous-namespace cStateCommand / cTransitionCommand
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3();                 // +0x0c  (release)
    virtual void s4();                 // +0x10  (release)
};
struct CheatManagerIface {             // SP::cCheatManager
    virtual void c00(); virtual void c04(); virtual void c08(); virtual void c0c();
    virtual void c10(); virtual void c14(); virtual void c18(); virtual void c1c();
    virtual void c20(); virtual void c24();
    virtual int  c28(const char* name);                    // +0x28
};
struct MServerX {                      // EA::Messaging::Server
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20();
    virtual void m24(void* obj, uint32_t msg);             // +0x24
};

ParserIface*       ArgScriptCreateParser();                // 0x008408d0
void*              CommandBaseCtor(void* p);               // 0x0083cdd0
void*              CmdBaseCtor(void* p);                   // 0x0083c800
void               IfCmdCtor(void* p, void* arg);          // 0x0083df90
void               AppStateCheatCtor(void* p, void* mgr);  // 0x007e4e90
CheatManagerIface* SP_CheatManager();                      // 0x0067de20

extern void*       gVtbl_cStateCommand;       // 0x014131f0
extern void*       gVtbl_cTransitionCommand;  // 0x0141337c
extern void*       gVtbl_chainCmd;            // 0x014134e0
extern void*       gVtbl_endChainCmd;         // 0x014134f8
extern void*       gVtbl_loadResourceCmd;     // 0x014131d8
extern void*       gVtbl_evalReal;            // 0x014131c8
extern char        gIfCommand[];              // 0x014090ec
extern uint32_t    gMsgTable[];               // 0x01413180 (0x12 entries)
extern const char* gName_state;               // 0x0153f5f0
extern const char* gName_transition;          // 0x0153f5f4
extern const char* gName_chain;               // 0x0153f644
extern const char* gName_endChain;            // 0x0153f648
extern const char* gName_loadResource;        // 0x0153f620
extern const char  gStateText_1413124[];      // 0x01413124 ("state")

struct cAppStateManagerI { int Init(const char* name); };

// @ 0x007E5430  cAppStateManagerI::Init
int cAppStateManagerI::Init(const char* name) {
    char* self = (char*)this;
    ParserIface* np = ArgScriptCreateParser();
    ParserIface* op = *(ParserIface**)(self + 0x158);
    if (np != op) {
        if (np) np->v00();
        *(void**)(self + 0x158) = np;
        if (op) op->v04();
    }
    np = *(ParserIface**)(self + 0x158);
    np->v08();
    np->v10(self + 0x10);

    StateCmdIface* sc = (StateCmdIface*)FUN_00f473a0(0x34, gAllocName_13ebc58, 0, 0, 0, 0);
    if (sc) { CommandBaseCtor(sc); *(void**)sc = &gVtbl_cStateCommand; }
    else sc = 0;
    StateCmdIface* osc = *(StateCmdIface**)(self + 0x15c);
    if (sc != osc) {
        if (sc) sc->s3();
        *(void**)(self + 0x15c) = sc;
        if (osc) osc->s4();
    }

    sc = (StateCmdIface*)FUN_00f473a0(0x3c, gAllocName_13ebc58, 0, 0, 0, 0);
    if (sc) { CommandBaseCtor(sc); *(void**)sc = &gVtbl_cTransitionCommand; }
    else sc = 0;
    osc = *(StateCmdIface**)(self + 0x160);
    if (sc != osc) {
        if (sc) sc->s3();
        *(void**)(self + 0x160) = sc;
        if (osc) osc->s4();
    }

    np = *(ParserIface**)(self + 0x158);
    np->v14(gName_state, *(void**)(self + 0x15c));
    np->v14(gName_transition, *(void**)(self + 0x160));

    void* ci = FUN_00f473a0(0x10, gAllocName_13ebc58, 0, 0, 0, 0);
    if (ci) { CmdBaseCtor(ci); *(void**)ci = &gVtbl_chainCmd; }
    else ci = 0;
    np = *(ParserIface**)(self + 0x158);
    np->v14(gName_chain, ci);

    ci = FUN_00f473a0(0x10, gAllocName_13ebc58, 0, 0, 0, 0);
    if (ci) { CmdBaseCtor(ci); *(void**)ci = &gVtbl_endChainCmd; }
    else ci = 0;
    np = *(ParserIface**)(self + 0x158);
    np->v14(gName_endChain, ci);

    ci = FUN_00f473a0(0x10, gAllocName_13ebc58, 0, 0, 0, 0);
    if (ci) { CmdBaseCtor(ci); *(void**)ci = &gVtbl_loadResourceCmd; }
    else ci = 0;
    np = *(ParserIface**)(self + 0x158);
    np->v14(gName_loadResource, ci);

    void* ev = FUN_00f473a0(8, gAllocName_13ebc58, 0, 0, 0, 0);
    if (ev) { *(void**)((char*)ev + 4) = 0; *(void**)ev = &gVtbl_evalReal; }
    else ev = 0;
    np = *(ParserIface**)(self + 0x158);
    IfCmdCtor((char*)np->vB8(gIfCommand, ev), ev);

    const char* stateName = name;
    if (stateName == 0)
        stateName = gStateText_1413124;
    if (SP_CheatManager()->c28(stateName) == 0) {
        void* cheat = FUN_00f473a0(0xe0, gAllocName_13ebc58, 0, 0, 0, 0);
        if (cheat) AppStateCheatCtor(cheat, self);
        SP_CheatManager();
        *(const char**)(self + 0x84) = stateName;
    }

    void* arg4 = self + 4;
    MServerX* ms = (MServerX*)SP_MessageServer();
    *(void**)(self + 0x140) = ms;
    *(void**)(self + 0x144) = arg4;
    *(void**)(self + 0x148) = gMsgTable;
    *(uint32_t*)(self + 0x14c) = 0x12;
    *(uint32_t*)(self + 0x150) = 0;
    if (ms && arg4) {
        for (unsigned i = 0; i < 0x48; i += 4)
            ms->m24(arg4, *(uint32_t*)((char*)gMsgTable + i));
    }
    return 1;
}

inline void EraseDestroyRange(cActions* first, cActions* last) {
    for (cActions* i = first; i < last; ++i)
        i->~cActions();
}
// @ 0x007E5830  cActionsVec::erase
cActions* cActionsVec::erase(cActions* first, cActions* last) {
    cActions* dst = FUN_007e3e20(last, mpEnd, first);
    EraseDestroyRange(dst, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x007E5890  cActionsVec::insert
void cActionsVec::insert(cActions* pos, const cActions* value) {
    if (mpEnd != mpCapacity) {
        const cActions* v = value;
        if (pos <= v && v < mpEnd)
            ++v;
        mpEnd->copy_ctor(*(mpEnd - 1));
        FUN_007e3e90(pos, mpEnd - 1, mpEnd);
        *pos = *v;
        mpEnd = mpEnd + 1;
    } else {
        int n = (int)((mpEnd - mpBegin) / 0x50);
        n = (n == 0) ? 1 : n * 2;
        cActions* buf = 0;
        if (n != 0)
            buf = (cActions*)FUN_00f473a0(n * 0x50, gAllocName_13ebc58, 0, 0, gAllocFile_13ebb38, 0xd1);
        cActions* dst = FUN_007e2c10(mpBegin, pos, buf);
        FUN_007e2ca0(mpBegin, pos, buf);
        dst->copy_ctor(*value);
        ++dst;
        cActions* newEnd = FUN_007e2c10(pos, mpEnd, dst);
        FUN_007e2ca0(pos, mpEnd, dst);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            FUN_00f47380(mpBegin);
        mpCapacity = buf + n;
        mpBegin = buf;
        mpEnd = newEnd;
    }
}

// @ 0x007E5AB0  cStateCommand::OnEndBlock
struct cStateCommandC { void OnEndBlock(char arg); };
void cStateCommandC::OnEndBlock(char arg) {
    char* self = (char*)this;
    if (arg == 0) {
        char* mgr = *(char**)(self + 0x30);
        int count = (*(int*)(mgr + 0xa8) - *(int*)(mgr + 0xa4)) / 0x50;
        ((cActionsVec*)(mgr + 0xa4))->push_back((cActions*)(mgr + 0x2c));
        MakeCaseInsensitive(mgr + 0x18);
        *FUN_006a8340(mgr + 0xf8, mgr + 0x18) = *(int*)(mgr + 0x28);
        *FUN_007c3a90(mgr + 0xb8, mgr + 0x28) = count;
        if (*(int*)(mgr + 0x7c) != -1) {
            int out = 0;
            FUN_00645ed0(mgr + 0xb8, &out, mgr + 0x7c);
            if (out != *(int*)(*(int*)(mgr + 0xbc) + *(int*)(mgr + 0xc0) * 4)) {
                int idx = *(int*)(out + 4);
                *(int*)(*(int*)(mgr + 0xa4) + idx * 0x50 + 0x4c) = *(int*)(mgr + 0x28);
            }
        }
        *(int*)(mgr + 0x7c) = *(int*)(*(char**)(self + 0x30) + 0x28);
    }
    *(uint8_t*)(*(char**)(self + 0x30) + 0x80) = 0;
    ((EaStringOps*)(*(char**)(self + 0x30) + 0x18))->assign(gEmptyStringObj, gEmptyStringObj);
    *(int*)(*(char**)(self + 0x30) + 0x28) = 0xffffffff;
}

// @ 0x007E5BC0  (cTransitionCommand::OnEndBlock)
struct cTransitionCommandC { void OnEndBlock(char arg); };
void cTransitionCommandC::OnEndBlock(char arg) {
    char* self = (char*)this;
    if (arg == 0) {
        char* mgr = *(char**)(self + 0x30);
        int iVar2 = *(int*)(mgr + 0xa8);
        int iVar3 = *(int*)(mgr + 0xa4);
        int count = (iVar2 - iVar3) / 0x50;
        FUN_007e5a30(mgr + 0x2c);
        int local_4 = *(int*)(self + 0x38);
        int local_8 = *(int*)(self + 0x34);
        int* r = (int*)FUN_007e30f0(&local_8);
        (void)local_4;
        *r = count;
    }
    ((EaStringOps*)(*(char**)(self + 0x30) + 0x18))->assign(gEmptyStringObj, gEmptyStringObj);
}

// @ 0x007E5C40  cAppStateManager::Update
void cAppStateManagerC::Update() {
    char* self = (char*)this;
    StateObjIface* sm = *(StateObjIface**)(self + 0x154);
    if (sm != 0 && sm->v28()) {
        ((cActionsVec*)(self + 0xa4))->erase(*(cActions**)(self + 0xa4), *(cActions**)(self + 0xa8));
        FUN_00693230(self + 0xb8, *(void**)(self + 0xbc), *(void**)(self + 0xc0));
        *(int*)(self + 0xc4) = 0;
        FUN_0093dc70(self + 0xd8, *(void**)(self + 0xdc), *(void**)(self + 0xe0));
        *(int*)(self + 0xe4) = 0;
        *(int*)(self + 0x7c) = -1;
        {
            cActions local;
            *(cActions*)(self + 0x2c) = local;
        }
        StateObjIface* sm2 = *(StateObjIface**)(self + 0x154);
        if (sm2->v20()) {
            int out = 0;
            FUN_00645ed0(self + 0xb8, &out, self + 0x88);
            if (out != *(int*)(*(int*)(self + 0xbc) + *(int*)(self + 0xc0) * 4)) {
                int idx = *(int*)(out + 4);
                *(int*)(self + 0x8c) = *(int*)(*(int*)(self + 0xa4) + idx * 0x50 + 0x4c);
            }
        }
    }
}


