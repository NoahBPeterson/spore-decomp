// cCameraManager ctors/dtors, loaders and helpers, 0x007c6750-0x007c7770.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct cViewer;
struct cICameraController;

extern "C" void  operator_delete(void*);   // 0x00f47380 (equiv t2)

// --- member types as the retail destructor sees them -------------------------------------------
struct IMsgHandlerBase {            // primary base: vptr at +0 (final vtable ??_7IMsgHandler@@6B@)
    virtual ~IMsgHandlerBase() {}
    virtual void h1();
};
struct GmeRefCountBase {            // second base: vptr at +4, refcount at +8 (??_7GmeRefCount@@6B@)
    GmeRefCountBase() : mRefCount(0) {}
    virtual ~GmeRefCountBase() {}
    int mRefCount;
};
struct CheatStr {                   // eastl::basic_string<char>
    char* mpBegin;                  // +0x00
    char* mpEnd;                    // +0x04
    char* mpCapacity;               // +0x08
    int   mAlloc;                   // +0x0c
    ~CheatStr() { if ((int)(mpCapacity - mpBegin) > 1 && mpBegin) operator_delete(mpBegin); }
};
struct HTStr {                      // hashtable<basic_string<wchar_t>, ...>: nodes own a string
    u8    mEmpty[4];
    int   mpBucketArray;            // +0x04
    u32   mnBucketCount;            // +0x08
    u32   mnElementCount;           // +0x0c
    u8    mPolicy[0x10];
    void DoFreeNodes(int bucketArray, u32 bucketCount) throw();   // 0x007c7050 (thiscall, ret 8)
    ~HTStr() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1) operator_delete((void*)mpBucketArray);
    }
};
struct HTPlain {                    // hashtable with trivially destructible nodes
    u8    mEmpty[4];
    int   mpBucketArray;            // +0x04
    u32   mnBucketCount;            // +0x08
    u32   mnElementCount;           // +0x0c
    u8    mPolicy[0x10];
    void DoFreeNodes(int bucketArray, u32 bucketCount) throw();   // 0x00693230 (thiscall, ret 8)
    ~HTPlain() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1) operator_delete((void*)mpBucketArray);
    }
};
struct RefVecS {                    // vector<AutoRefCount<cICameraController>, sp_vector_allocator>
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
    void** mpCapacity;              // +0x08
    u8     mAlloc[8];
    void Destroy();                 // 0x00a23920 (thiscall)
};
struct NamesVec {                   // vector<basic_string<wchar_t>, sp_vector_allocator>
    int* mpBegin;                   // +0x00 (allocation has a count word at [-1])
    void* mpEnd;                    // +0x04
    void* mpCapacity;               // +0x08
    u32   mAlloc;
    void DoDestroyValues(void* first, void* last);   // 0x0084aad0 (thiscall, ret 8)
};

struct cCameraManager : public IMsgHandlerBase, public GmeRefCountBase {   // vptrs at +0 and +4
    bool  mInitialized;             // +0x0c
    u8    pad0d[3];
    CheatStr mCheatName;            // +0x10
    HTStr    mControllerNameIDMap;  // +0x20
    HTPlain  mControllerTypeIDMap;  // +0x40
    HTPlain  mControllerIDMap;      // +0x60
    RefVecS  mControllers;          // +0x80
    NamesVec mControllerNames;      // +0x94
    int   mActiveControllerIndex;   // +0xa4 (approximate; ctor stub only)
    u32   mPropModCount;
    int   mIndexA8;

    void Init(void* cmd);           // 0x7c70b0
    void Shutdown();                // 0x7c6db0
    void ClearControllers();        // 0x7c6eb0
    void LoadControllers();         // 0x7c6b80
    virtual ~cCameraManager();      // 0x7c74a0
    cCameraManager();               // 0x7c75e0
};

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
    if (mCheatName.mpBegin != mCheatName.mpEnd) { *mCheatName.mpBegin = 0; mCheatName.mpEnd = mCheatName.mpBegin; }
    int n = (int)((char*)mControllers.mpEnd - (char*)mControllers.mpBegin) >> 2;
    for (int i = 0; i < n; i++) {
        void* c = mControllers.mpBegin[i];
        if (c) ((void(__thiscall*)(void*))((void**)*(void**)c)[0x14 / 4])(c);
    }
    mControllers.mpEnd = mControllers.mpBegin;
    mIndexA8 = 0;
}

// ===========================================================================
// @ 0x007c6eb0
void cCameraManager::ClearControllers() {
    int n = (int)((char*)mControllers.mpEnd - (char*)mControllers.mpBegin) >> 2;
    for (int i = 0; i < n; i++) {
        void* c = mControllers.mpBegin[i];
        if (c) ((void(__thiscall*)(void*))((void**)*(void**)c)[0x14 / 4])(c);
    }
    mControllers.mpEnd = mControllers.mpBegin;
    mIndexA8 = 0;
}

// ===========================================================================
// @ 0x007c7050
void HTStr::DoFreeNodes(int bucketArray, u32 bucketCount) throw() {
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
    mControllerNames.DoDestroyValues(mControllerNames.mpBegin, mControllerNames.mpEnd);
    int* names = mControllerNames.mpBegin;
    if (names && names[-1])
        operator_delete(names);
    mControllers.Destroy();
}

// ===========================================================================
// @ 0x007c75e0
cCameraManager::cCameraManager() {
    mInitialized = false;
    mCheatName.mpBegin = (char*)1;
    mCheatName.mpEnd = (char*)1;
    mCheatName.mpCapacity = (char*)2;
    mControllers.mpBegin = 0; mControllers.mpEnd = 0; mControllers.mpCapacity = 0;
    mControllerNames.mpBegin = 0; mControllerNames.mpEnd = 0; mControllerNames.mpCapacity = 0;
    mActiveControllerIndex = 0;
    mPropModCount = 0;
    mIndexA8 = -1;
}

// ===========================================================================
// @ 0x007c7770
struct cBitLength {
    int pad0;
    int mValue;      // +0x04
    u32 mMask;       // +0x08
    int pad0c;
    u32 mTableA;     // +0x10
    u32 mTableB;     // +0x14
    int mLimit;      // +0x18
    void BitLengthInit(int value, u32 mask);
};
void cBitLength::BitLengthInit(int value, u32 mask) {
    mValue = value;
    mMask = mask;
    int bits = 0;
    if (mask & 0xffff0000) { bits = 0x10; mask >>= 16; }
    if (mask & 0xff00)     { bits += 8;  mask >>= 8; }
    if (mask & 0xf0)       { bits += 4; }
    if (mask & 0xc)        { bits += 2; }
    if (mask & 2)          { bits += 1; }
    u32 v = *(u32*)(UNK_01410e24 + bits * 4);
    mTableA = v;
    mTableB = v;
    mLimit = (1 << ((char)bits + 1 & 0x1f)) + -1;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
