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

void FUN_007e5a30(void* p);
void* FUN_007e30f0(void* p);
void* FUN_007e3e20(void* first, void* end, void* last);
void StringAssign(void* self, const void* s);
void MakeCaseInsensitive(void* p);

// @ 0x007E5220  (cAppStateManager constructor: member/subobject initialisation)
struct cAppStateManagerC { void ctor(); };
void cAppStateManagerC::ctor() {
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
        *(float*)(p + off + 0x10) = 0.0f;
        *(uint32_t*)(p + off + 0x14) = 0;
    }
    *(uint32_t*)(p + 0x118) = 0; *(uint32_t*)(p + 0x11c) = 0; *(uint32_t*)(p + 0x120) = 0;
    *(uint32_t*)(p + 0x12c) = 0; *(uint32_t*)(p + 0x130) = 0; *(uint32_t*)(p + 0x134) = 0;
    for (int off = 0x140; off <= 0x160; off += 4)
        *(uint32_t*)(p + off) = 0;
    *(void**)(p + 0x164) = gEmptyStringData;
    *(void**)(p + 0x168) = gEmptyStringData;
    *(void**)(p + 0x16c) = gEmptyStringData + 1;
}

// @ 0x007E5430  (cAppStateManager::Init; incomplete reconstruction)
void* SP_CheatManager();
void cAppStateManagerInit(void* self) {
    (void)self;
    // Parser/command registration is not reconstructed (see partial.txt).
    (void)SP_CheatManager();
}

// @ 0x007E5830  (vector<cActions>::erase helper; incomplete)
void* cActionsEraseHelper(void* vec, void* first, void* last) {
    char* v = (char*)vec;
    char* dst = (char*)FUN_007e3e20(last, *(void**)(v + 4), first);
    char* end = *(char**)(v + 4);
    while (dst < end) {
        FUN_007e5a30(dst);        // ~cActions
        dst += 0x50;
    }
    *(int*)(v + 4) += (int)(((char*)last - (char*)first) / 0x50) * 0x50;
    return first;
}

// @ 0x007E5890  (vector<cActions>::erase with reallocation; incomplete)
void cActionsEraseRange(void* vec, void* first, void* last) {
    (void)vec; (void)first; (void)last;
    // EASTL reallocating erase not reconstructed (see partial.txt).
}

// @ 0x007E5AB0  (cStateCommand::OnEndBlock; incomplete)
struct cStateCommandC { void OnEndBlock(char arg); };
void cStateCommandC::OnEndBlock(char arg) {
    char* self = (char*)this;
    if (arg == 0) {
        char* mgr = *(char**)(self + 0x30);
        int count = (*(int*)(mgr + 0xa8) - *(int*)(mgr + 0xa4)) / 0x50;
        FUN_007e5a30(mgr + 0x2c);
        MakeCaseInsensitive(mgr + 0x18);
        // hash_map operator[] / hashtable find not reconstructed (see partial.txt)
        *(int*)(mgr + 0x7c) = *(int*)(mgr + 0x28);
        (void)count;
    }
    *(uint8_t*)(*(char**)(self + 0x30) + 0x80) = 0;
    StringAssign(gEmptyStringObj, gEmptyStringObj);
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
    StringAssign(gEmptyStringObj, gEmptyStringObj);
}

// @ 0x007E5C40  (cAppStateManager::Update; incomplete)
void cAppStateManagerUpdate(void* self) {
    (void)self;
    // EASTL hash-map state replay not reconstructed (see partial.txt).
}


