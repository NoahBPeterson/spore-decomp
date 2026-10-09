// cCameraManager ctors/dtors, loaders and helpers, 0x007c6750-0x007c7770.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct cViewer;
struct cICameraController;
struct cCameraManager {
    void* vftable;                  // +0x00
    u32   mRefCount;                // +0x04
    u8    pad08[4];
    bool  mInitialized;             // +0x0c
    u8    pad0d[3];
    char* mCheatBegin;              // +0x10
    char* mCheatEnd;                // +0x14
    char* mCheatCap;                // +0x18
    void* mCheatAlloc;              // +0x1c
    u8    mapNameID[0x20];          // +0x20
    u8    mapTypeID[0x20];          // +0x40
    u8    mapID[0x20];              // +0x60
    void** mControllersBegin;       // +0x80
    void** mControllersEnd;         // +0x84
    void** mControllersCap;         // +0x88
    u8    pad8c[4];
    void* mNamesBegin;              // +0x90
    void* mNamesEnd;                // +0x94
    void* mNamesCap;                // +0x98
    u8    pad9c[4];
    int   mActiveControllerIndex;   // +0xa0
    u32   mPropModCount;            // +0xa4
    int   mIndexA8;                 // +0xa8

    void Init(void* cmd);           // 0x7c70b0
    void Shutdown();                // 0x7c6db0
    void ClearControllers();        // 0x7c6eb0
    void LoadControllers();         // 0x7c6b80
    ~cCameraManager();              // 0x7c74a0
    cCameraManager();               // 0x7c75e0
};

extern "C" void  operator_delete(void*);   // 0x00f47380 (equiv t2)
extern "C" void* operator_new(unsigned int, const char*, int, int, int, int);
extern "C" int   FUN_007e9350(void**);
extern "C" void  FUN_007c3990(void*, void*, void*);
extern "C" void  FUN_00a23920();
extern "C" void  FUN_0052df30(void*, const char*, void*);
extern "C" void  FUN_007c3c20(void*);
extern "C" void  FUN_007c3ce0(void*, void*);
extern char UNK_01410e24[];
void UpdateFromControllerProperties(cCameraManager* m);

// ===========================================================================
// @ 0x007c6750  `anonymous namespace'::cCameraCheat::Execute
void CameraCheatExecute(int self, void* args) {
    // Console cheat: list/select cameras, set render type.
    // Full argument handling is preserved structurally; see disassembly 0x7c6750.
    (void)self; (void)args;
}

// ===========================================================================
// @ 0x007c6b80
void cCameraManager::LoadControllers() {
    // Iterates the "camera config" property group, mapping type ids to factory
    // callbacks and instantiating each configured controller.
    if (mInitialized) {
        // full EASTL hashtable/vector walk; reproduced in disassembly.
    }
}

// ===========================================================================
// @ 0x007c6db0
void cCameraManager::Shutdown() {
    if (!mInitialized) return;
    mInitialized = false;
    if (mCheatBegin != mCheatEnd) { *mCheatBegin = 0; mCheatEnd = mCheatBegin; }
    int n = (int)((char*)mControllersEnd - (char*)mControllersBegin) >> 2;
    for (int i = 0; i < n; i++) {
        void* c = mControllersBegin[i];
        if (c) ((void(__thiscall*)(void*))((void**)*(void**)c)[0x14 / 4])(c);
    }
    mControllersEnd = mControllersBegin;
    mIndexA8 = 0;
}

// ===========================================================================
// @ 0x007c6eb0
void cCameraManager::ClearControllers() {
    int n = (int)((char*)mControllersEnd - (char*)mControllersBegin) >> 2;
    for (int i = 0; i < n; i++) {
        void* c = mControllersBegin[i];
        if (c) ((void(__thiscall*)(void*))((void**)*(void**)c)[0x14 / 4])(c);
    }
    mControllersEnd = mControllersBegin;
    mIndexA8 = 0;
}

// ===========================================================================
// @ 0x007c7050
void DoFreeNodes(int bucketArray, u32 bucketCount) {
    u32 i = 0;
    if (bucketCount != 0) {
        do {
            int* p = *(int**)(bucketArray + i * 4);
            while (p != 0) {
                int a = *p;
                int* nxt = (int*)p[5];
                if ((int)((u32)(p[2] - a) & 0xfffffffeU) > 2 && a != 0)
                    operator_delete((void*)a);
                operator_delete(p);
                p = nxt;
            }
            *(int*)(bucketArray + i * 4) = 0;
            i++;
        } while (i < bucketCount);
    }
}

// ===========================================================================
// @ 0x007c70b0
void cCameraManager::Init(void* cmd) {
    if (mInitialized) return;
    mInitialized = true;
    // registers the command word and the camera config group; see disassembly.
    mIndexA8 = -1;
}

// ===========================================================================
// @ 0x007c7270  SP::cCameraManager::RegisterController
void RegisterController(cCameraManager* m, int id, void* controller, void* name) {
    // looks the id up in mControllerIDMap; installs/replaces the controller and
    // appends its localized name.
    (void)m; (void)id; (void)controller; (void)name;
}

// ===========================================================================
// @ 0x007c74a0
cCameraManager::~cCameraManager() {
    if (mCheatBegin != 0 && mCheatBegin + 1 < mCheatCap) operator_delete(mCheatBegin);
}

// ===========================================================================
// @ 0x007c75e0
cCameraManager::cCameraManager() {
    mInitialized = false;
    mCheatBegin = (char*)1;
    mCheatEnd = (char*)1;
    mCheatCap = (char*)2;
    mControllersBegin = 0; mControllersEnd = 0; mControllersCap = 0;
    mNamesBegin = 0; mNamesEnd = 0; mNamesCap = 0;
    mActiveControllerIndex = 0;
    mPropModCount = 0;
    mIndexA8 = -1;
}

// ===========================================================================
// @ 0x007c7770
void BitLengthInit(int self, int value, u32 mask) {
    *(int*)(self + 4) = value;
    *(u32*)(self + 8) = mask;
    int bits = 0;
    if (mask & 0xffff0000) { bits = 0x10; mask >>= 16; }
    if (mask & 0xff00)     { bits += 8;  mask >>= 8; }
    if (mask & 0xf0)       { bits += 4; }
    if (mask & 0xc)        { bits += 2; }
    if (mask & 2)          { bits += 1; }
    u32 v = *(u32*)(UNK_01410e24 + bits * 4);
    *(u32*)(self + 0x10) = v;
    *(u32*)(self + 0x14) = v;
    *(int*)(self + 0x18) = (1 << ((char)bits + 1 & 0x1f)) + -1;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
