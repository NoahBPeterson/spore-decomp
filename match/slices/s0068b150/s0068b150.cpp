// Slice s0068b150 — SP::cCommandServer and friends (App/cCommandServer.cpp).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;
typedef unsigned __int64 uint64;

// ---------------------------------------------------------------------------
// externals (call targets are masked relocations)
// ---------------------------------------------------------------------------
void  EAFree(void* p);                                                       // 0x00F47380 cdecl
void* EAAllocate(unsigned n, const char* name, int a, int b, const char* f, int l); // 0x00F473A0 cdecl
extern "C" int  __cdecl atexit(void(__cdecl* )());                           // 0x011E07EF (E8)
extern "C" __int64 _InterlockedCompareExchange64(volatile __int64* d, __int64 e, __int64 c);

void* FUN_0068A2E0();                        // 0x0068A2E0 cdecl
void  FUN_00689EE0(void* out);               // 0x00689EE0 thiscall(out)
void  FUN_0068A000(void* out);               // 0x0068A000 thiscall(out)
void  FUN_00689DC0(void* p, int a, int b);   // 0x00689DC0 thiscall(p,a,b)
void  FUN_00D167E0();                        // 0x00D167E0 cdecl
void* operator new(unsigned int, void*);

extern wchar_t gEmptyW;                      // 0x01667BAC
extern wchar_t gEmptyWEnd;                   // 0x01667BAE
extern void*   gVtCpsBase2[1];               // 0x013EF094
extern void*   gVtCpsPri[1];                 // 0x01403310
extern void*   gVtCpsSec[1];                 // 0x0140330C
extern void*   gVtCmdSrv[1];                 // 0x01403410
extern void*   gVtEditorRes[1];              // 0x013EB938
extern char    gDefaultWStrInited;           // 0x015FF8DC
extern void*   gDefaultWStr[3];              // 0x015FF8CC
extern "C" void __cdecl gFun13BEB80();       // 0x013BEB80 atexit dtor

// ---------------------------------------------------------------------------
// WStr — eastl::basic_string<wchar_t>
// ---------------------------------------------------------------------------
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;

    WStr() { mpBegin = &gEmptyW; mpEnd = &gEmptyW; mpCapacity = &gEmptyWEnd; }
    ~WStr() { if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin) EAFree(mpBegin); }
    WStr(const wchar_t* s);                                   // 0x0056E2D0
    WStr& operator=(const WStr& x)
    {
        if (this != &x)
            Assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    WStr& operator=(const wchar_t* s);                        // 0x005C3D90
    WStr& Assign(const wchar_t* b, const wchar_t* e);         // 0x00423650
    WStr& Append(const wchar_t* b, const wchar_t* e);         // 0x00429580
    void  Resize(unsigned n);                                 // 0x00429520
    void  push_back(unsigned c);                              // 0x004F6510
};

// ---------------------------------------------------------------------------
// EA::Variant
// ---------------------------------------------------------------------------
struct Variant {
    char           mGeneric[0x10];
    unsigned short mFlags;    // +0x10
    unsigned short mTypeId;   // +0x12

    Variant& operator=(unsigned v);                           // 0x00542B80
    void     Destruct(int b);                                 // 0x0093DB80
    void     CtorFromValue(unsigned v);                       // 0x00689E80
};

// ---------------------------------------------------------------------------
// refcounted bases and AutoRefCount
// ---------------------------------------------------------------------------
struct IRefCounted {
    virtual void AddRef() = 0;      // slot 0
    virtual void Release() = 0;     // slot 1
    virtual void s2();
    virtual void Init();            // slot 4 (+0x10)
    virtual void Deinit();          // slot 5 (+0x14)
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator=(T* p)
    {
        if (p != mpObject) {
            if (p)
                ((IRefCounted*)p)->AddRef();
            T* old = mpObject;
            mpObject = p;
            if (old)
                ((IRefCounted*)old)->Release();
        }
        return p;
    }
};

// ---------------------------------------------------------------------------
// rbtree shapes (anchor at +4, size at +0x14 of the tree object)
// ---------------------------------------------------------------------------
struct RbNode {
    RbNode* mpRight;
    RbNode* mpLeft;
    RbNode* mpParent;
    uint8   mColor;
};

void* RbTreeIncrement(RbNode* n);                             // 0x00921580 cdecl
void  RbTreeErase(RbNode* n, RbNode* anchor);                 // 0x00921880 cdecl

struct RbTreeBase {
    char    pad0[4];
    RbNode  mAnchor;      // +0x04
    uint32  mnSize;       // +0x14
    void  DoNuke(RbNode* node);                       // 0x00EB6280 (extern)
    void  Find(void* out, void* key);                 // 0x00E5C780 (extern)
    void* Insert(void* a, void* b, void* c);          // 0x0068BA40/0x0068BB50 (extern)
    __forceinline void reset()
    {
        RbNode* a = &mAnchor;
        a->mpRight   = a;
        a->mpLeft    = a;
        a->mpParent  = 0;
        a->mColor    = 0;
        mnSize       = 0;
    }
};

// node of the command-info map: value at +0x14 (id + two WStr)
struct CmdInfoNode {
    RbNode  mBase;        // +0x00
    char    pad10[4];     // +0x10
    uint32  mnID;         // +0x14
    WStr    msName;       // +0x18
    WStr    msTypeInfo;   // +0x28
};

// map<uint32, Variant> node and tree
struct VarMapNode {
    RbNode  mBase;      // +0x00
    uint32  mKey;       // +0x10
    Variant mValue;     // +0x14
};

struct VarMap : RbTreeBase {
    Variant* GetPos(uint32* key);                             // 0x0068BF20 (below)
};

// ---------------------------------------------------------------------------
// cCommandParameterSet (0x3c)
// ---------------------------------------------------------------------------
struct cCommandParameterSet {
    void*   mVt0;         // +0x00
    void*   mVt4;         // +0x04
    void*   m08;
    VarMap  mParams;      // +0x0c (0x18 bytes)
    char    m24[0x14];    // +0x24 .. +0x38
    uint16  m38;
    uint16  m3A;

    void* operator new(unsigned s) { return EAAllocate(s, "App/cCommandParameterSet", 0, 0, 0, 0); }
    cCommandParameterSet();
    void SetParameter(uint32 id, uint32 value);   // 0x0068C020
    void AddRef() { ((IRefCounted*)this)->AddRef(); }
};

cCommandParameterSet::cCommandParameterSet()
{
    mVt4 = &gVtCpsBase2;
    m08  = 0;
    mVt0 = &gVtCpsPri;
    mVt4 = &gVtCpsSec;
    mParams.mAnchor.mpLeft   = 0;
    mParams.mAnchor.mpParent = 0;
    *(uint32*)&mParams.mAnchor.mColor = 0;
    mParams.mAnchor.mpRight  = &mParams.mAnchor;
    mParams.mAnchor.mpLeft   = &mParams.mAnchor;
    mParams.mAnchor.mpParent = 0;
    mParams.mAnchor.mColor   = 0;
    mParams.mnSize = 0;
    m38 = 0;
    m3A = 0;
}

// parameter-set interface used through its vtable
struct IParamSet {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void* GetValue(int i);      // slot 6  (+0x18)
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual int  First();               // slot 14 (+0x38)
    virtual int  Next(int i);           // slot 15 (+0x3c)
};

// ---------------------------------------------------------------------------
// generators / dispatchers
// ---------------------------------------------------------------------------
struct cStringCommandGenerator {
    char mBase[0x08];
    void* operator new(unsigned s) { return EAAllocate(s, "App/cStringCommandGenerator", 0, 0, 0, 0); }
};

struct cMessageCommandDispatcher {
    char mBase[0x44];
    void* operator new(unsigned s) { return EAAllocate(s, "App/cMessageCommandDispatcher", 0, 0, 0, 0); }
};

// server vtable slots
struct ICommandServerVt {
    virtual void i0();
    virtual void Release();             // slot 1  (+0x04)
    virtual void i2();
    virtual void i3();
    virtual void i4();                  // slot 4  (+0x10)
    virtual void i5();                  // slot 5  (+0x14)
    virtual void i6();
    virtual void i7();
    virtual void i8();
    virtual void RegisterCmd(unsigned id, const wchar_t* name); // slot 9 (+0x24)
    virtual void i10();
    virtual void i11();
    virtual bool ProcessCommand(int pCmd, WStr* out, int b); // slot 12 (+0x30)
    virtual void i13();
    virtual void i14();
    virtual void i15();                 // slot 15 (+0x3c)
    virtual void SetGenerator(IRefCounted* g);   // slot 16 (+0x40)
    virtual void i17();
    virtual bool HasSet();              // slot 18 (+0x48)
    virtual void SetDispatcher(IRefCounted* d);  // slot 19 (+0x4c)
};

struct UintVec {
    unsigned* mpBegin;
    unsigned* mpEnd;
    unsigned* mpCapacity;
    void*     mAllocator;

    void DoInsertValue(unsigned* pos, const unsigned& v);     // 0x004558A0
    __forceinline void push_back(const unsigned& v)
    {
        unsigned* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e)
                *e = v;
        } else {
            DoInsertValue(e, v);
        }
    }
};

// map<uint32, Variant>
struct cCommandServer : ICommandServerVt {
    struct CmdMap : RbTreeBase {
        void  DestroyNodes(RbNode* node);              // 0x0068B9D0
        void  DestroyNode(RbNode* node, void** itOut); // 0x0068B950
        ~CmdMap() { DestroyNodes(mAnchor.mpParent); }
    };
    struct GenSet : RbTreeBase {
        ~GenSet() { DoNuke(mAnchor.mpParent); }
    };

    CmdMap                 mCommandInfoMap;             // +0x04
    AutoRefCount<IRefCounted>               mpCommandDispatcher;        // +0x20
    AutoRefCount<cMessageCommandDispatcher> mpMessageCommandDispatcher; // +0x24
    AutoRefCount<cStringCommandGenerator>   mpStringCommandGenerator;   // +0x28
    GenSet                 mCommandGeneratorSet;        // +0x2c
    bool                   mb48;                        // +0x48

    bool Shutdown();                                    // 0x0068BCF0
    bool RegisterCommand(uint32 id, const wchar_t* name, void* p3); // 0x0068BDA0
    bool UnregisterCommand(uint32 id);                  // 0x0068BEC0
    void EnumerateCommands(UintVec& out);               // 0x0068B900
};

cCommandServer* gpCommandServer;   // 0x015FF660

// ===========================================================================
// @ 0x0068b150  SP::cStringCommandGenerator::ConvertCommandToString
// ===========================================================================
struct ConvCmdThis {
    void ProcessToken(WStr* a, WStr* b);   // 0x0068A320
};

bool ConvertCommandToString(ConvCmdThis* self, int pCmd, IParamSet* pSet, WStr* out)
{
    if (out->mpBegin != out->mpEnd) {
        *(uint16*)out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    if (gpCommandServer == 0)
        return false;

    WStr local;
    if (!gpCommandServer->ProcessCommand(pCmd, &local, 0))
        return false;

    self->ProcessToken(&local, &local);
    out->Append(local.mpBegin, local.mpEnd);

    if (pSet) {
        for (int idx = pSet->First(); idx != -1; idx = pSet->Next(idx)) {
            unsigned v = (unsigned)pSet->GetValue(idx);
            Variant temp;
            temp.CtorFromValue(v);

            wchar_t* s;
            if (temp.mTypeId == 0x13 || temp.mTypeId == 0x10) {
                if (temp.mFlags & 0x30)
                    s = *(wchar_t**)temp.mGeneric;
                else
                    s = temp.mTypeId ? (wchar_t*)&temp : 0;
            } else {
                s = (wchar_t*)FUN_0068A2E0();
            }

            local = WStr(s);
            self->ProcessToken(&local, &local);
            out->push_back(' ');
            out->Append(local.mpEnd, local.mpCapacity);
            if (temp.mFlags & 4)
                temp.Destruct(0);
        }
    }
    return true;
}

// ===========================================================================
// @ 0x0068b370  SP::cCommandParameterSet::CompareParameterString
// ===========================================================================
bool CompareParameterString(WStr* out, IParamSet* pSet)
{
    out->Resize(0);
    WStr local;

    for (int idx = pSet->First(); idx != -1; idx = pSet->Next(idx)) {
        unsigned v = (unsigned)pSet->GetValue(idx);
        Variant temp;
        temp.mFlags  = 0x13;
        temp.mTypeId = 0x0b;
        temp = v;

        wchar_t* s;
        if (temp.mTypeId == 0x13 || temp.mTypeId == 0x10) {
            if (temp.mFlags & 0x30)
                s = *(wchar_t**)temp.mGeneric;
            else
                s = temp.mTypeId ? (wchar_t*)&temp : 0;
        } else {
            if (!gDefaultWStrInited) {
                gDefaultWStrInited = 1;
                gDefaultWStr[0] = &gEmptyW;
                gDefaultWStr[1] = &gEmptyW;
                gDefaultWStr[2] = &gEmptyWEnd;
                atexit(&gFun13BEB80);
            }
            s = (wchar_t*)gDefaultWStr;
        }

        local = WStr(s);
        out->Append(local.mpEnd, local.mpCapacity);
        if (temp.mFlags & 4)
            temp.Destruct(0);
    }
    return true;
}

// ===========================================================================
// @ 0x0068b5b0  generator-set init (members at +0x38/+0x3c/+0x40)
// ===========================================================================
struct GenOwner {
    char pad0[0x38];
    AutoRefCount<cCommandParameterSet>    mParams0;    // +0x38
    AutoRefCount<cCommandParameterSet>    mParams1;    // +0x3c
    AutoRefCount<cStringCommandGenerator> mGenerator;  // +0x40
    char m44[4];
};

bool InitGenerators(GenOwner* self)
{
    if (self->mParams0.mpObject == 0) {
        cCommandParameterSet* p = new cCommandParameterSet();
        self->mParams0 = p;
    }
    if (self->mParams1.mpObject == 0) {
        cCommandParameterSet* p = new cCommandParameterSet();
        self->mParams1 = p;
    }
    if (self->mGenerator.mpObject == 0) {
        cStringCommandGenerator* p = new cStringCommandGenerator();
        self->mGenerator = p;
        if (self->mGenerator.mpObject)
            ((IRefCounted*)self->mGenerator.mpObject)->Init();
    }
    return true;
}

// ===========================================================================
// @ 0x0068b760  dispatcher init
// ===========================================================================
bool InitDispatchers(cCommandServer* self)
{
    if (!self->HasSet()) {
        cMessageCommandDispatcher* d = new cMessageCommandDispatcher();
        self->mpMessageCommandDispatcher = d;
        if (self->mpMessageCommandDispatcher.mpObject)
            ((IRefCounted*)self->mpMessageCommandDispatcher.mpObject)->Init();
        self->SetDispatcher((IRefCounted*)self->mpMessageCommandDispatcher.mpObject);
    }
    {
        cStringCommandGenerator* g = new cStringCommandGenerator();
        self->mpStringCommandGenerator = g;
        if (self->mpStringCommandGenerator.mpObject)
            ((IRefCounted*)self->mpStringCommandGenerator.mpObject)->Init();
        self->SetGenerator((IRefCounted*)self->mpStringCommandGenerator.mpObject);
    }
    return true;
}

// ===========================================================================
// @ 0x0068b880  CreateParameterSet
// ===========================================================================
void CreateParameterSet(cCommandParameterSet** out)
{
    *out = new cCommandParameterSet();
    ((IRefCounted*)*out)->AddRef();
}

// ===========================================================================
// @ 0x0068b900  SP::cCommandServer::EnumerateCommands
// ===========================================================================
void cCommandServer::EnumerateCommands(UintVec& out)
{
    RbNode* it  = mCommandInfoMap.mAnchor.mpLeft;
    RbNode* end = &mCommandInfoMap.mAnchor;
    if (it != end) {
        do {
            unsigned v = *(unsigned*)((char*)it + 0x10);
            out.push_back(v);
            it = (RbNode*)RbTreeIncrement(it);
        } while (it != end);
    }
}

// ===========================================================================
// @ 0x0068b950  map node destroy helper (this = &map)
// ===========================================================================
void cCommandServer::CmdMap::DestroyNode(RbNode* node, void** itOut)
{
    --mnSize;
    void* next = RbTreeIncrement(node);
    RbTreeErase(node, &mAnchor);
    {
        WStr* s = (WStr*)((char*)node + 0x28);
        if ((((char*)s->mpCapacity - (char*)s->mpBegin) & ~1) > 2 && s->mpBegin)
            EAFree(s->mpBegin);
    }
    {
        WStr* s = (WStr*)((char*)node + 0x18);
        if ((((char*)s->mpCapacity - (char*)s->mpBegin) & ~1) > 2 && s->mpBegin)
            EAFree(s->mpBegin);
    }
    EAFree(node);
    *itOut = next;
}

// ===========================================================================
// @ 0x0068b9d0  SP::cCommandServer::DestroyMapNodes (recursive, this = &map)
// ===========================================================================
void cCommandServer::CmdMap::DestroyNodes(RbNode* node)
{
    while (node) {
        DestroyNodes(node->mpRight);
        RbNode* parent = node->mpLeft;
        {
            WStr* s = (WStr*)((char*)node + 0x28);
            if ((((char*)s->mpCapacity - (char*)s->mpBegin) & ~1) > 2 && s->mpBegin)
                EAFree(s->mpBegin);
        }
        {
            WStr* s = (WStr*)((char*)node + 0x18);
            if ((((char*)s->mpCapacity - (char*)s->mpBegin) & ~1) > 2 && s->mpBegin)
                EAFree(s->mpBegin);
        }
        EAFree(node);
        node = parent;
    }
}

// ===========================================================================
// @ 0x0068bc50  SP::cCommandServer::~cCommandServer
// ===========================================================================
void cCommandServerDtor(cCommandServer* self)
{
    *(void**)self = &gVtCmdSrv;
    // member destruction in reverse declaration order:
    self->mCommandGeneratorSet.~GenSet();
    if (self->mpStringCommandGenerator.mpObject)
        ((IRefCounted*)self->mpStringCommandGenerator.mpObject)->Release();
    if (self->mpMessageCommandDispatcher.mpObject)
        ((IRefCounted*)self->mpMessageCommandDispatcher.mpObject)->Release();
    if (self->mpCommandDispatcher.mpObject)
        ((IRefCounted*)self->mpCommandDispatcher.mpObject)->Release();
    self->mCommandInfoMap.~CmdMap();
    *(void**)self = &gVtEditorRes;
}

// ===========================================================================
// @ 0x0068bcf0  SP::cCommandServer::Shutdown
// ===========================================================================
bool cCommandServer::Shutdown()
{
    mCommandInfoMap.DestroyNodes(mCommandInfoMap.mAnchor.mpParent);
    mCommandInfoMap.reset();
    this->SetDispatcher(0);
    if (mpMessageCommandDispatcher.mpObject) {
        ((IRefCounted*)mpMessageCommandDispatcher.mpObject)->Deinit();
        if (mpMessageCommandDispatcher.mpObject) {
            mpMessageCommandDispatcher.mpObject = 0;
            ((IRefCounted*)mpMessageCommandDispatcher.mpObject)->Release();
        }
    }
    if (mpStringCommandGenerator.mpObject) {
        ((IRefCounted*)mpStringCommandGenerator.mpObject)->Deinit();
        if (mpStringCommandGenerator.mpObject) {
            mpStringCommandGenerator.mpObject = 0;
            ((IRefCounted*)mpStringCommandGenerator.mpObject)->Release();
        }
    }
    for (RbNode* it = mCommandGeneratorSet.mAnchor.mpLeft;
         it != &mCommandGeneratorSet.mAnchor; it = (RbNode*)RbTreeIncrement(it)) {
    }
    mCommandGeneratorSet.DoNuke(mCommandGeneratorSet.mAnchor.mpParent);
    mCommandGeneratorSet.reset();
    return true;
}

// ===========================================================================
// @ 0x0068bda0  SP::cCommandServer::RegisterCommand
// ===========================================================================
bool cCommandServer::RegisterCommand(uint32 id, const wchar_t* name, void* p3)
{
    (void)p3;
    if (id == 0 || name == 0)
        return false;
    void* it;
    mCommandInfoMap.Find(&it, &id);
    if (*(RbNode**)it != &mCommandInfoMap.mAnchor)
        return false;

    WStr a;
    WStr b;
    FUN_00689EE0(&a);
    FUN_0068A000(&b);
    void* nodeOut = 0;
    mCommandInfoMap.Insert(&nodeOut, &b, &a);
    void* node = nodeOut;
    *(uint32*)((char*)node + 0x14) = id;
    (*(WStr*)((char*)node + 0x18)).operator=(name);
    this->RegisterCmd(id, name);
    FUN_00689DC0((char*)node + 0x14, 1, 0);
    FUN_00D167E0();
    return true;
}

// ===========================================================================
// @ 0x0068bec0  SP::cCommandServer::UnregisterCommand
// ===========================================================================
bool cCommandServer::UnregisterCommand(uint32 id)
{
    void* it;
    mCommandInfoMap.Find(&it, &id);
    if ((RbNode*)it == &mCommandInfoMap.mAnchor)
        return false;
    FUN_00689DC0((char*)it + 0x14, 0, 0);
    void* out;
    mCommandInfoMap.DestroyNode((RbNode*)it, &out);
    return true;
}

// ===========================================================================
// @ 0x0068bf20  eastl::map<unsigned,EA::Variant>::operator[]
// ===========================================================================
__declspec(noinline) Variant* VarMap::GetPos(uint32* key)
{
    RbNode* y = &mAnchor;
    RbNode* x = mAnchor.mpParent;
    while (x) {
        if (!(*key < *(uint32*)((char*)x + 0x10))) {
            y = x;
            x = x->mpLeft;
        } else {
            x = x->mpRight;
        }
    }
    if (y == &mAnchor || *key < *(uint32*)((char*)y + 0x10)) {
        Variant v1;
        v1.mFlags  = 0;
        v1.mTypeId = 0;
        *(uint32*)&v1.mGeneric[0] = *key;
        Variant v2;
        v2.mFlags  = 0;
        v2.mTypeId = 0;
        v2 = *(uint32*)key;
        y = (RbNode*)Insert(y, key, &v2);
        if (v2.mFlags & 4)
            v2.Destruct(0);
        if (v1.mFlags & 4)
            v1.Destruct(0);
    }
    return (Variant*)((char*)y + 0x14);
}

// ===========================================================================
// @ 0x0068c020  SP::cCommandParameterSet::SetParameter
// ===========================================================================
void cCommandParameterSet::SetParameter(uint32 id, uint32 value)
{
    Variant* slot = mParams.GetPos(&id);
    *slot = value;
}

// ===========================================================================
// @ 0x0068c040  SP::cCommandServer::cCommandServer (ctor)
// ===========================================================================
void cCommandServerCtor(cCommandServer* self)
{
    *(void**)self = &gVtCmdSrv;
    self->mCommandInfoMap.reset();
    self->mpCommandDispatcher.mpObject = 0;
    self->mpMessageCommandDispatcher.mpObject = 0;
    self->mpStringCommandGenerator.mpObject = 0;
    self->mCommandGeneratorSet.reset();
    self->mb48 = false;
}

// ===========================================================================
// @ 0x0068c140  atomic 64-bit read (lock cmpxchg8b loop)
// ===========================================================================
uint64 __fastcall AtomicRead64(volatile uint64* p)
{
    volatile uint64 old;
    volatile uint64 next;
    do {
        old  = *(volatile uint64*)p;
        next = old;
    } while (_InterlockedCompareExchange64((volatile __int64*)p, next, old) != old);
    return old;
}

// ===========================================================================
// @ 0x0068c1b0  atomic 64-bit exchange
// ===========================================================================
uint64 __fastcall AtomicExchange64(volatile uint64* p, uint64 v)
{
    volatile uint64 old;
    do {
        old = *(volatile uint64*)p;
    } while (_InterlockedCompareExchange64((volatile __int64*)p, v, old) != old);
    return old;
}

// ===========================================================================
// @ 0x0068c220  free-list drain
// ===========================================================================
struct FreeItem {
    uint64 pad;
    uint64 next;
};

struct FreeList {
    uint64 mHead;                        // +0x00

    void Drain();                        // 0x0068C220
    void Push(uint32 a, uint32 b);       // 0x0068C280
};

void FreeList::Drain()
{
    if ((uint32)AtomicRead64(&mHead) != 0) {
        do {
            uint64 v = mHead;
            FreeItem* item = (FreeItem*)(uint32)AtomicRead64(&v);
            mHead = item->next;
            EAFree((void*)(uint32)AtomicRead64(&v));
        } while ((uint32)AtomicRead64(&mHead) != 0);
    }
}

void FreeList::Push(uint32 a, uint32 b)
{
    uint64 t = ((uint64)b << 32) | a;
    FreeItem* item = (FreeItem*)(uint32)AtomicRead64(&t);
    item->pad  = t;
    item->next = mHead;
    for (;;) {
        uint64 old = *(volatile uint64*)&mHead;
        uint64 c   = AtomicRead64(&old);
        if (_InterlockedCompareExchange64((volatile __int64*)&mHead, (__int64)(c + 1), (__int64)c) == c)
            break;
    }
}
