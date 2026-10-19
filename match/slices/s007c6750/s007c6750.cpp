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
    void assign(const char* first, const char* last);   // 0x00454cb0 (thiscall, ret 8)
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
    int*  OperatorIndex(const void* key);   // 0x007c3a90 (thiscall, ret 4) -- hash_map operator[]
};
struct HTKeyMap {                   // same layout, exposed for hashtable::find (0x00645ed0)
    u8    mEmpty[4];
    int   mpBucketArray;            // +0x04
    u32   mnBucketCount;            // +0x08
    u32   mnElementCount;           // +0x0c
    u8    mPolicy[0x10];
    int*  Find(void* out, const void* key);   // 0x00645ed0 (thiscall, ret 8)
    int*  OperatorIndex(const void* key);     // 0x007c3a90 (thiscall, ret 4)
};
struct RefVecS {                    // vector<AutoRefCount<cICameraController>, sp_vector_allocator>
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
    void** mpCapacity;              // +0x08
    u8     mAlloc[8];
    void Destroy();                 // 0x00a23920 (thiscall)
    void AddControllerRef(void** controller);   // 0x007e9350 (thiscall, ret 4)
};
struct NamesVec {                   // vector<basic_string<wchar_t>, sp_vector_allocator>
    int* mpBegin;                   // +0x00 (allocation has a count word at [-1])
    void* mpEnd;                    // +0x04
    void* mpCapacity;               // +0x08
    u32   mAlloc;
    void DoDestroyValues(void* first, void* last);   // 0x0084aad0 (thiscall, ret 8)
    void push_back(const void* item);                // 0x00553f10 (thiscall, ret 4)
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
    void RegisterController(int id, void* controller, const wchar_t* name);   // 0x7c7270
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

// --- helpers used by Init / RegisterController ------------------------------------------------
void* SP_CheatManager();          // 0x0067de20
void* SP_MessageServer();         // 0x0067dcc0
void  cCommandBase_ctor(void*);   // 0x0083c800 (thiscall)
extern "C" unsigned int strlen(const char*);
struct IMessageServer {           // 0x67dcc0 result; slot 8 (offset 0x20) takes (ptr,id)
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(void*, unsigned int);
};
struct cWString {                 // eastl::basic_string<wchar_t>
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void  RangeInitialize(const wchar_t* text);   // 0x00579a90 (thiscall, ret 4)
    void  append(const wchar_t* text);            // 0x005c3d90 (thiscall, ret 4)
    ~cWString() {
        if ((((int)((char*)mpCapacity - (char*)mpBegin)) & 0xfffffffe) > 2 && mpBegin != 0)
            operator_delete(mpBegin);
    }
};
struct ControllerRef {            // AutoRefCount<cICameraController>: releases on scope exit
    void* mpObject;
    ~ControllerRef() {
        if (mpObject != 0)
            (*(void (__thiscall**)(void*))((*(void***)mpObject)[1]))(mpObject);
    }
};

// ===========================================================================
// @ 0x007c6750  `anonymous namespace'::cCameraCheat::Execute
void CameraCheatExecute(int self, void* args) {
    // Console cheat: list/select cameras, set render type.
    // Full argument handling is preserved structurally; see disassembly 0x7c6750.
    (void)self; (void)args;
}

// ===========================================================================
// @ 0x007c6b80
struct PropGroup {                  // the property-group buffer returned by PropertyManager
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    ~PropGroup() { if (mpBegin != 0 && mpBegin[-1] != 0) operator_delete(mpBegin); }
};
struct PropRef {                    // refcounted cPropertyList* local (release on scope exit)
    void* mpObject;
    void reset() {
        if (mpObject != 0) {
            void* p = mpObject;
            mpObject = 0;
            (*(void (__thiscall**)(void*))((*(void***)p)[1]))(p);
        }
    }
    ~PropRef() {
        if (mpObject != 0)
            (*(void (__thiscall**)(void*))((*(void***)mpObject)[1]))(mpObject);
    }
};
typedef void* (__cdecl* TypeFactoryFn)(void*, int);
typedef char (__thiscall* Fn4Bool)(void*, void*, int, void*);
typedef void* (__thiscall* Fn2Ptr)(void*, int);
typedef char (__thiscall* Fn2Bool)(void*, int);
typedef void (__thiscall* Fn3Void)(void*, void*, void*);
typedef void (__thiscall* Fn3VoidInt)(void*, int, void*);
void* PropertyManager();           // 0x0067de30
void* VariantGetTPTR();            // 0x007c65a0
int   g_153cd9c;                   // camera-config property-group type id

void cCameraManager::LoadControllers() {
    PropGroup group;
    group.mpBegin = 0; group.mpEnd = 0; group.mpCapacity = 0;
    void* pm = PropertyManager();
    ((Fn3VoidInt)((*(void***)pm)[0x48 / 4]))(pm, g_153cd9c, &group);
    PropRef cur;
    cur.mpObject = 0;
    int count = (int)((char*)group.mpEnd - (char*)group.mpBegin) >> 2;
    for (int i = 0; i < count; ++i) {
        void* pm2 = PropertyManager();
        cur.reset();
        if (((Fn4Bool)((*(void***)pm2)[0x2c / 4]))(pm2, group.mpBegin[i], g_153cd9c, &cur.mpObject) == 0)
            continue;
        void* v = ((Fn2Ptr)((*(void***)cur.mpObject)[0x28 / 4]))(cur.mpObject, 0xed3928);
        unsigned short type = *(unsigned short*)((char*)v + 0x12);
        void* decoded;
        if (type == 0xa || type == 0x10) {
            if ((*(unsigned char*)((char*)v + 0x10) & 0x30) == 0)
                decoded = (type != 0) ? v : 0;
            else
                decoded = *(void**)v;
        } else {
            decoded = (void*)0x15d1164;
        }
        int key = *(int*)decoded;
        HTKeyMap* map = (HTKeyMap*)&mControllerTypeIDMap;
        int scratch;
        int* node = map->Find(&scratch, &key);
        int* bucketArray = (int*)mControllerTypeIDMap.mpBucketArray;
        if (node == (int*)bucketArray[mControllerTypeIDMap.mnBucketCount])
            continue;
        TypeFactoryFn factory = (TypeFactoryFn)*(void**)((char*)node + 4);
        if (((Fn2Bool)((*(void***)cur.mpObject)[0x1c / 4]))(cur.mpObject, 0xed3929) == 0) {
            void* ctl = factory(cur.mpObject, 0);
            ((Fn3Void)((*(void***)this)[0x24 / 4]))(this, group.mpBegin[i], ctl);
        } else {
            void* v2 = ((Fn2Ptr)((*(void***)cur.mpObject)[0x28 / 4]))(cur.mpObject, 0xed3929);
            unsigned short t2 = *(unsigned short*)((char*)v2 + 0x12);
            void* d2;
            if (t2 == 0x13 || t2 == 0x10) {
                if ((*(unsigned char*)((char*)v2 + 0x10) & 0x30) == 0)
                    d2 = (t2 != 0) ? v2 : 0;
                else
                    d2 = *(void**)v2;
            } else {
                d2 = VariantGetTPTR();
            }
            int arg = *(int*)d2;
            void* ctl = factory(cur.mpObject, arg);
            ((Fn3Void)((*(void***)this)[0x24 / 4]))(this, group.mpBegin[i], ctl);
        }
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
    if (mInitialized)
        return;
    mInitialized = true;
    const char* first = (const char*)cmd;
    mCheatName.assign(first, first + strlen(first));
    if (SP_CheatManager() != 0 && mCheatName.mpBegin != mCheatName.mpEnd) {
        void* cheat = operator_new(0x14, "App", 0, 0, 0, 0);
        if (cheat) {
            cCommandBase_ctor(cheat);
            *(void**)cheat = (void*)0x14104a4;                       // cCameraCheat vftable
            *(void**)((char*)cheat + 0x10) = this;                   // owner manager
        }
    }
    void* obj = operator_new(0x10, "App", 0, 0, 0, 0);
    if (obj) {
        *(void**)((char*)obj + 4) = (void*)0x13eb384;
        *(void**)((char*)obj + 8) = (void*)0x13ef094;
        *(void**)((char*)obj + 0xc) = 0;
        *(void**)obj = (void*)0x14105c0;
        *(void**)((char*)obj + 4) = (void*)0x14105b0;
        *(void**)((char*)obj + 8) = (void*)0x14105ac;
    } else {
        obj = 0;
    }
    if (obj)
        (*(void (__thiscall**)(void*))*(void**)obj)(obj);
    {
        ControllerRef ref;
        ref.mpObject = obj;
        mControllers.AddControllerRef(&ref.mpObject);
    }
    cWString name;
    name.mpBegin = 0; name.mpEnd = 0; name.mpCapacity = 0;
    name.RangeInitialize(L"null");
    mControllerNames.push_back(&name);
    u32 key = 0;
    *(void**)mControllerIDMap.OperatorIndex(&key) = 0;
    mIndexA8 = 0;
    IMessageServer* ms = (IMessageServer*)SP_MessageServer();
    if (ms != 0)
        ms->m8(this, 0xf62def);
}

// ===========================================================================
// @ 0x007c7270  cCameraManager::RegisterController
void cCameraManager::RegisterController(int id, void* controller, const wchar_t* name) {
    HTKeyMap* map = (HTKeyMap*)&mControllerIDMap;
    int scratch;
    int* node = map->Find(&scratch, &id);
    int* bucketArray = (int*)mControllerIDMap.mpBucketArray;
    int* sentinel = (int*)bucketArray[mControllerIDMap.mnBucketCount];
    if (node != sentinel) {
        int idx = *(int*)((char*)node + 4);
        void* old = mControllers.mpBegin[idx];
        if (old != controller) {
            if (old != 0) {
                if (idx == mIndexA8)
                    (*(void (__thiscall**)(void*))((*(void***)old)[7]))(old);
                void* cur = mControllers.mpBegin[*(int*)((char*)node + 4)];
                (*(void (__thiscall**)(void*))((*(void***)cur)[5]))(cur);
            }
            void** slot = &mControllers.mpBegin[*(int*)((char*)node + 4)];
            void* prev = *slot;
            if (controller != prev) {
                if (controller != 0)
                    (*(void (__thiscall**)(void*))((*(void***)controller)[0]))(controller);
                *slot = controller;
                if (prev != 0)
                    (*(void (__thiscall**)(void*))((*(void***)prev)[1]))(prev);
            }
            cWString* slotName = (cWString*)((char*)mControllerNames.mpBegin
                                            + *(int*)((char*)node + 4) * 0x10);
            if (name != 0)
                slotName->append(name);
            else
                slotName->append((const wchar_t*)0x13ec468);
        }
    } else {
        int count = (int)((char*)mControllers.mpEnd - (char*)mControllers.mpBegin) >> 2;
        *map->OperatorIndex(&id) = count;
        void* ctl = controller;
        if (ctl != 0)
            (*(void (__thiscall**)(void*))((*(void***)ctl)[0]))(ctl);
        {
            ControllerRef ref;
            ref.mpObject = ctl;
            mControllers.AddControllerRef(&ref.mpObject);
        }
        cWString ws;
        ws.mpBegin = 0; ws.mpEnd = 0; ws.mpCapacity = 0;
        if (name != 0)
            ws.RangeInitialize(name);
        else
            ws.RangeInitialize((const wchar_t*)0x13ec468);
        mControllerNames.push_back(&ws);
    }
    (*(void (__thiscall**)(void*, void*))((*(void***)controller)[4]))(controller, this);
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
