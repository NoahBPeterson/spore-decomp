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
    float mfLoadFactor;             // +0x10 (1.0f)
    float mfGrowthFactor;           // +0x14 (2.0f)
    int   mnUnk18;                  // +0x18 (0)
    int   mnUnk1c;                  // +0x1c (ctor leaves it alone)
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
    float mfLoadFactor;             // +0x10 (1.0f)
    float mfGrowthFactor;           // +0x14 (2.0f)
    int   mnUnk18;                  // +0x18 (0)
    int   mnUnk1c;                  // +0x1c (ctor leaves it alone)
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
    float mfLoadFactor;             // +0x10 (1.0f)
    float mfGrowthFactor;           // +0x14 (2.0f)
    int   mnUnk18;                  // +0x18 (0)
    int   mnUnk1c;                  // +0x1c (ctor leaves it alone)
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
    void Erase(void** first, void** last);      // 0x00e25bd0 (thiscall, ret 8)
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
    int   mUnkA4;                   // +0xa4 (ctor leaves it alone)
    int   mIndexA8;                 // +0xa8 (ctor -1, Shutdown/ClearControllers 0)
    int   mUnkAC;                   // +0xac (ctor 0)
    u32   mPropModCount;            // +0xb0 (ctor 0)

    void Init(void* cmd);           // 0x7c70b0
    bool Shutdown();                // 0x7c6db0
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
    virtual void m9(); virtual void m10();
    virtual void m11(void* owner, unsigned int id, unsigned int arg);   // offset 0x2c
};
struct ICheatManager {            // 0x67de20 result; slot 7 (offset 0x1c) takes the cheat name
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
    virtual void c4(); virtual void c5(); virtual void c6();
    virtual void Unregister(char* name);
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
// `anonymous namespace'::cCameraCheat::Execute
// Console cheat: no argument prints the current camera, a number or a name
// selects one, and the argument flags drive the manager's list/apply slots.
struct cCameraCheat {
    void* mpVtbl;                   // +0x00
    void* mpUnk4;                   // +0x04 (output object)
    u8    mPad08[8];                // +0x08
    cCameraManager* mpManager;      // +0x10
    void Execute(void* args);       // 0x007c6750 (thiscall, ret 4)
};

typedef int   (__thiscall* FnInt0)(void*);
typedef void  (__thiscall* FnVoidInt)(void*, int);
typedef char  (__thiscall* FnBoolInt)(void*, int);
typedef void* (__thiscall* FnPtrInt)(void*, int);
typedef void* (__thiscall* FnPtrStr)(void*, const char*);
typedef void* (__thiscall* FnPtrV)(void*, void*);
typedef void* (__thiscall* FnPtrVV)(void*, void*, void*);
typedef void  (__cdecl* FnFmt)(void*, const char*, int, const char*, const char*, int);

int    ArgCount(void* ctx);                                     // 0x00837F30
char*  ArgString(void* ctx, void* out, int a, int b);           // 0x00838020
char*  ArgNamed(void* ctx, const char* name, int a);            // 0x00838330
char   ArgFlag(void* ctx, const char* name);                    // 0x008380B0
void   StrCtor(void* str, const char* text, int len);           // 0x0093C5A0 (thiscall)
int    StrCmp(const char* a, const char* b);                    // 0x013CC50C
int    CharClass(int c);                                        // 0x013CC4CC
void*  SP_Object();                                             // 0x0067DD10
void   LogFree(void* text, const void* sink);                   // 0x011E0912
void*  CameraCheatVariantPtr();                                 // 0x007c65a0

// Name of the i-th controller (empty strings read as null).
static const char* NameAt(cCameraManager* mgr, int i) {
    const char* begin = (const char*)mgr->mControllerNames.mpBegin;
    const char* end = (const char*)mgr->mControllerNames.mpEnd;
    if (i < 0 || i >= (int)((end - begin) >> 4))
        return 0;
    const char** elem = (const char**)(begin + (i << 4));
    if (*elem == elem[1] || *elem == 0)
        return 0;
    return *elem;
}

// @ 0x007c6750
void cCameraCheat::Execute(void* args) {
    void* ctx = args;
    cCameraManager* mgr = mpManager;
    if (ArgCount(ctx) == 1) {
        // No argument: print the current camera.
        int idx = ((FnInt0)((*(void***)mgr)[0x58 / 4]))(mgr);
        ((FnFmt)(void*)0x00841000)(mpUnk4, (const char*)0x0141067C, 0, NameAt(mgr, idx), 0, 0);
        return;
    }

    char* arg;
    int   kind[2] = { 0, 0 };
    arg = ArgString(ctx, kind, 0, 1);
    if (kind[0] != 1) {
        arg = ArgNamed(ctx, (const char*)0x013F2CE4, 1);
        if (arg == 0)
            goto common;
    }

    if (CharClass((u8)*arg) != 0) {
        // A leading letter: hand the whole string to the manager's command slot.
        void* res = ((FnPtrStr)((*(void***)mpUnk4)[0xa0 / 4]))(mpUnk4, arg);
        ((FnVoidInt)((*(void***)mgr)[0x34 / 4]))(mgr, (int)res);
    } else {
        CheatStr name;
        StrCtor(&name, arg, -1);
        int count = ((FnInt0)((*(void***)mgr)[0x48 / 4]))(mgr);
        int i;
        for (i = 0; i < count; ++i) {
            const char* nm = NameAt(mgr, i);
            if (nm != 0 && StrCmp(nm, name.mpBegin) == 0)
                break;
        }
        if (i == count) {
            char msg[0x10];
            FUN_0052df30(msg, (const char*)0x01410664, name.mpBegin);
            LogFree(msg, (const void*)0x014F9174);
        }
        ((FnVoidInt)((*(void***)mgr)[0x54 / 4]))(mgr, i);
    }

common:
    if (ArgFlag(ctx, (const char*)0x01409070)) {
        int count = ((FnInt0)((*(void***)mgr)[0x48 / 4]))(mgr);
        for (int i = 0; i < count; ++i) {
            const char* nm = NameAt(mgr, i);
            const char* marker = (i == ((FnInt0)((*(void***)mgr)[0x58 / 4]))(mgr))
                                     ? (const char*)0x01401B58
                                     : (const char*)0x013ED024;
            void* ctrl = ((FnPtrInt)((*(void***)mgr)[0x4c / 4]))(mgr, i);
            int value = 0;
            if (ctrl != 0) {
                void* sub = ((FnPtrInt)((*(void***)ctrl)[0x4c / 4]))(ctrl, 0);
                if (sub != 0 && ((FnBoolInt)((*(void***)sub)[0x1c / 4]))(sub, 0x00B2CCCA)) {
                    void* var = ((FnPtrInt)((*(void***)sub)[0x28 / 4]))(sub, 0x00B2CCCA);
                    unsigned short type = *(unsigned short*)((char*)var + 0x12);
                    void* decoded;
                    if (type == 0x13 || type == 0x10) {
                        if ((*(u8*)((char*)var + 0x10) & 0x30) != 0)
                            decoded = *(void**)var;
                        else
                            decoded = (type != 0) ? var : 0;
                    } else {
                        decoded = CameraCheatVariantPtr();
                    }
                    value = *(int*)decoded;
                }
            }
            if (nm != 0)
                ((FnFmt)(void*)0x00841000)(mpUnk4, (const char*)0x01410648, i << 4, nm, marker, value);
            else
                ((FnFmt)(void*)0x00841000)(
                    mpUnk4, (const char*)0x01410628, 0,
                    (const char*)((FnPtrInt)((*(void***)mgr)[0x50 / 4]))(mgr, i), marker, value);
        }
    }

    char* apply = ArgNamed(ctx, (const char*)0x01410624, 1);
    if (apply != 0) {
        float* src = (float*)((FnPtrStr)((*(void***)mpUnk4)[0xb4 / 4]))(mpUnk4, *(char**)apply);
        float v[4];
        v[0] = src[0]; v[1] = src[1]; v[2] = src[2]; v[3] = src[3];
        void* obj = SP_Object();
        void* out = ((FnPtrV)((*(void***)obj)[0x58 / 4]))(obj, v);
        FUN_007c3c20(out);
    }
    char* reset = ArgNamed(ctx, (const char*)0x01410618, 1);
    if (reset != 0) {
        void* res = ((FnPtrStr)((*(void***)mpUnk4)[0x9c / 4]))(mpUnk4, *(char**)reset);
        void* obj = SP_Object();
        void* out = ((FnPtrVV)((*(void***)obj)[0x58 / 4]))(obj, 0, res);
        FUN_007c3ce0(out, res);
    }
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
bool cCameraManager::Shutdown() {
    if (!mInitialized)
        return true;
    mInitialized = false;
    IMessageServer* ms = (IMessageServer*)SP_MessageServer();
    if (ms != 0)
        ms->m11(this, 0xf62def, 0xffffd8f1u);
    ICheatManager* cheat = (ICheatManager*)SP_CheatManager();
    if (cheat != 0 && mCheatName.mpBegin != mCheatName.mpEnd)
        cheat->Unregister(mCheatName.mpBegin);
    if (mCheatName.mpBegin != mCheatName.mpEnd) {
        *mCheatName.mpBegin = 0;
        mCheatName.mpEnd = mCheatName.mpBegin;
    }
    mControllerIDMap.DoFreeNodes(mControllerIDMap.mpBucketArray, mControllerIDMap.mnBucketCount);
    mControllerIDMap.mnElementCount = 0;
    int n = (int)((char*)mControllers.mpEnd - (char*)mControllers.mpBegin) >> 2;
    for (int i = 0; i < n; i++) {
        void* c = mControllers.mpBegin[i];
        if (c) ((void(__thiscall*)(void*))((void**)*(void**)c)[0x14 / 4])(c);
    }
    mControllers.Erase(mControllers.mpBegin, mControllers.mpEnd);
    mIndexA8 = 0;
    mControllers.Erase(mControllers.mpBegin, mControllers.mpEnd);
    return true;
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
    *(void**)((char*)this + 4) = (void*)0x13ef094;      // GmeRefCountBase vftable during construction
    mRefCount = 0;
    *(void**)this = (void*)0x14106a8;                   // final vftables
    *(void**)((char*)this + 4) = (void*)0x14106a4;
    mInitialized = false;
    mCheatName.mpBegin = (char*)0x1667bac;              // empty string sentinel
    mCheatName.mpEnd = (char*)0x1667bac;
    mCheatName.mpCapacity = (char*)0x1667bad;

    mControllerNameIDMap.mfLoadFactor = 1.0f;
    mControllerNameIDMap.mfGrowthFactor = 2.0f;
    mControllerNameIDMap.mpBucketArray = (int)0x154df28;   // empty bucket array
    mControllerNameIDMap.mnBucketCount = 1;
    mControllerNameIDMap.mnElementCount = 0;
    mControllerNameIDMap.mnUnk18 = 0;

    mControllerTypeIDMap.mfLoadFactor = 1.0f;
    mControllerTypeIDMap.mfGrowthFactor = 2.0f;
    mControllerTypeIDMap.mpBucketArray = (int)0x154df28;
    mControllerTypeIDMap.mnBucketCount = 1;
    mControllerTypeIDMap.mnElementCount = 0;
    mControllerTypeIDMap.mnUnk18 = 0;

    mControllerIDMap.mfLoadFactor = 1.0f;
    mControllerIDMap.mfGrowthFactor = 2.0f;
    mControllerIDMap.mpBucketArray = (int)0x154df28;
    mControllerIDMap.mnBucketCount = 1;
    mControllerIDMap.mnElementCount = 0;
    mControllerIDMap.mnUnk18 = 0;

    mControllers.mpBegin = 0; mControllers.mpEnd = 0; mControllers.mpCapacity = 0;
    mControllerNames.mpBegin = 0; mControllerNames.mpEnd = 0; mControllerNames.mpCapacity = 0;
    mUnkAC = 0;
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
    if (mask & 0xf0)       { bits += 4;  mask >>= 4; }
    if (mask & 0xc)        { bits += 2;  mask >>= 2; }
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
