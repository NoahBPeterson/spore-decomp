// Slice s00688dd0 — SP command server / command parameter set + helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

// ---------------------------------------------------------------------------
// rbtree free helpers (call targets are masked relocations)
// ---------------------------------------------------------------------------
void* RBTreeDecrement(void* node);   // 0x009215c0 cdecl
void* RBTreeIncrement(void* node);   // 0x00921580 cdecl

// ===========================================================================
// @ 0x00688ED0  indexed element access
// ===========================================================================
struct E16 { void* v; char rest[12]; };
struct Vec16 {
    uint32 pad0;
    E16*   mpBegin;
    E16*   mpEnd;
    void*  Get(uint32 i);
};

void* Vec16::Get(uint32 i)
{
    if (i < (uint32)((int)((char*)mpEnd - (char*)mpBegin) >> 4))
        return mpBegin[i].v;
    return 0;
}

// ===========================================================================
// @ 0x006895F0  SP::cCommandParameterSet::ValidateParameter
// ===========================================================================
struct CmdParamSetValidate {
    void* vtbl;
    bool  ValidateParameter(uint32 a, uint32 b);
};

bool CmdParamSetValidate::ValidateParameter(uint32 a, uint32 b)
{
    if (((int(__thiscall*)(void*, uint32))(*(void***)this)[0x1c / 4])(this, a) != 0 &&
        b == 0xff)
        return true;
    return false;
}

// ===========================================================================
// @ 0x006896A0  SP::cCommandServer::RegisterCommands
// ===========================================================================
struct CmdEntry {
    uint32  mId;      // +0x00
    uint16* mName;    // +0x04
    uint32  mFlags;   // +0x08
};

struct CommandServer {
    void* vtbl;
    bool  RegisterCommands(CmdEntry* e, int count);
    bool  UnregisterCommands(uint32* e, int count);
};

bool CommandServer::RegisterCommands(CmdEntry* e, int count)
{
    for (; count != 0; e++, count--) {
        uint32  id = e->mId;
        if (id == 0)
            break;
        uint16* name = e->mName;
        if (name == 0)
            break;
        if (*name == 0)
            break;
        ((void(__thiscall*)(void*, uint32, void*, uint32))
            (*(void***)this)[0x1c / 4])(this, id, name, e->mFlags);
    }
    return true;
}

// ===========================================================================
// @ 0x006896F0  SP::cCommandServer::UnregisterCommands
// ===========================================================================
bool CommandServer::UnregisterCommands(uint32* e, int count)
{
    if (count != 0) {
        do {
            uint32 id = *e;
            if (id == 0)
                break;
            ((void(__thiscall*)(void*, uint32))(*(void***)this)[0x28 / 4])(this, id);
            e += 3;
        } while (--count);
    }
    return true;
}

// ===========================================================================
// @ 0x00689730  SP::cStringCommandGenerator::Shutdown
// ===========================================================================
struct StringCommandGenerator {
    char pad[0x20];
    void* mGenerator;   // +0x20
    bool  Shutdown();
};

bool StringCommandGenerator::Shutdown()
{
    void* p = mGenerator;
    if (p != 0) {
        mGenerator = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    return true;
}

// ===========================================================================
// @ 0x00689920  command dispatcher shutdown
// ===========================================================================
struct DispShutdown {
    void* vtbl;
    bool  Shutdown();
};

bool DispShutdown::Shutdown()
{
    ((void(__thiscall*)(void*))(*(void***)this)[0x18 / 4])(this);
    void* p = *(void**)((char*)this + 0x38);
    if (p != 0) {
        *(void**)((char*)this + 0x38) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    p = *(void**)((char*)this + 0x3c);
    if (p != 0) {
        *(void**)((char*)this + 0x3c) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    p = *(void**)((char*)this + 0x40);
    if (p != 0) {
        ((void(__thiscall*)(void*))(*(void***)p)[0x14 / 4])(p);
        p = *(void**)((char*)this + 0x40);
        if (p != 0) {
            *(void**)((char*)this + 0x40) = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        }
    }
    return true;
}

// ===========================================================================
// @ 0x00689980  command dispatcher teardown
// ===========================================================================
struct DispTeardown {
    void* vtbl;
    bool  Teardown();
};

bool DispTeardown::Teardown()
{
    *(void**)((char*)this + 0x18) = 0;
    *(void**)((char*)this + 0x20) = 0;
    void* p = *(void**)((char*)this + 0x30);
    if (p != 0)
        ((void(__thiscall*)(void*, int))(*(void***)p)[0x14 / 4])(p, 0);
    p = *(void**)((char*)this + 0x34);
    if (p != 0)
        ((void(__thiscall*)(void*, int))(*(void***)p)[0x14 / 4])(p, 0);
    p = *(void**)((char*)this + 0x38);
    ((void(__thiscall*)(void*, int))(*(void***)p)[0x14 / 4])(p, 0);
    p = *(void**)((char*)this + 0x3c);
    ((void(__thiscall*)(void*, int))(*(void***)p)[0x14 / 4])(p, 0);
    return true;
}

// ===========================================================================
// @ 0x00689B00  SP::cCommandServer::SetCommandDispatcher
// ===========================================================================
struct CommandServer2 {
    char pad[0x20];
    void* mDispatcher;   // +0x20
    bool  SetCommandDispatcher(void* p);
};

bool CommandServer2::SetCommandDispatcher(void* p)
{
    if (mDispatcher == p)
        return true;
    void* old = *(void* volatile*)((char*)this + 0x20);
    if (p != old) {
        if (p != 0)
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
        mDispatcher = p;
        if (old != 0)
            ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }
    return true;
}

// ===========================================================================
// @ 0x00689B40  SP::cCommandServer::ExecuteCommand (dispatcher)
// ===========================================================================
struct CommandServer3 {
    char pad[0x20];
    void* mDispatcher;   // +0x20
    int ExecuteCommand(uint32 a, uint32 b, uint32 c);
};

int CommandServer3::ExecuteCommand(uint32 a, uint32 b, uint32 c)
{
    void* p = mDispatcher;
    if (p != 0)
        return ((int(__thiscall*)(void*, uint32, uint32, uint32))
            (*(void***)p)[0x1c / 4])(p, a, b, c);
    return 2;
}

// ===========================================================================
// @ 0x00689B60  SP::cCommandServer::ExecuteCommand (string generator)
// ===========================================================================
struct CommandServer4 {
    char pad[0x28];
    void* mGenerator;    // +0x28
    int ExecuteCommand(uint32 a, uint32 b);
};

int CommandServer4::ExecuteCommand(uint32 a, uint32 b)
{
    void* p = mGenerator;
    if (p != 0)
        return ((int(__thiscall*)(void*, uint32, uint32))
            (*(void***)p)[0x20 / 4])(p, a, b);
    return 2;
}

// ===========================================================================
// @ 0x00689BE0  SP::cCommandParameterSet::operator[]
// @ 0x00689C20  SP::cCommandParameterSet::GetParameter
// @ 0x00689C50  SP::cCommandParameterSet::AppendParameter
// @ 0x00689D00  SP::cCommandParameterSet::GetFirstParameterID
// ===========================================================================
struct RBTreeStub {
    char treeData[0x14];
    void find(void** out, const uint32& key);   // decl only (masked reloc)
};

struct ParamSet {
    char       pad0[0xc];
    RBTreeStub mMap;       // +0x0c
    uint32     mSize;      // +0x20
    char       pad1[4];
    uint32     mDefault;   // +0x28

    void* operator[](uint32 key);
    void* GetParameter(uint32 key);
    void  AppendParameter(uint32 v);
    uint32 GetFirstParameterID();
};

void* ParamSet::operator[](uint32 key)
{
    void* it;
    mMap.find(&it, key);
    if (it != (void*)((char*)this + 0x10))
        return (char*)it + 0x14;
    return (char*)this + 0x28;
}

void* ParamSet::GetParameter(uint32 key)
{
    void* it;
    mMap.find(&it, key);
    if (it != (void*)((char*)this + 0x10))
        return (char*)it + 0x14;
    return 0;
}

void ParamSet::AppendParameter(uint32 v)
{
    uint32 id = 0;
    if (mSize != 0)
        id = *(uint32*)((char*)RBTreeDecrement((char*)this + 0x10) + 0x10) + 1;
    ((void(__thiscall*)(void*, uint32, uint32))(*(void***)this)[0x20 / 4])(this, id, v);
}

uint32 ParamSet::GetFirstParameterID()
{
    if (mSize != 0)
        return *(uint32*)(*(char**)((char*)this + 0x14) + 0x10);
    return 0xffffffff;
}

// ===========================================================================
// @ 0x00689DC0  recursive command-parameter walk
// ===========================================================================
struct ParamWalker {
    void* vtbl;
    bool  Walk(char* node, uint32 flags, void* sink);
};

bool ParamWalker::Walk(char* node, uint32 flags, void* sink)
{
    if (node == 0) {
        char* n = *(char**)((char*)this + 0xc);
        char* end = (char*)this + 8;
        for (; n != end; n = (char*)RBTreeIncrement(n))
            Walk(n + 0x14, flags, sink);
    } else {
        if (sink != 0) {
            if ((char)flags != 0) {
                ((void(__thiscall*)(void*, void*, void*, void*))
                    (*(void***)sink)[0x18 / 4])
                    (sink, *(void**)node, node + 4, node + 0x14);
            } else {
                ((void(__thiscall*)(void*, void*, void*, void*))
                    (*(void***)sink)[0x1c / 4])
                    (sink, *(void**)node, node + 4, node + 0x14);
            }
            return true;
        }
        char* n = *(char**)((char*)this + 0x34);
        char* end = (char*)this + 0x30;
        if (n != end) {
            do {
                Walk(node, flags, *(void**)(n + 0x10));
                n = (char*)RBTreeIncrement(n);
            } while (n != end);
        }
    }
    return true;
}

// ===========================================================================
// @ 0x00688DD0 / @ 0x00688E50  post a command-prototype notification
// ===========================================================================
void* operator new(unsigned size, const char* area, int a, int b, int c, int d);
struct NewObj { NewObj(int param); };
struct MsgSrv { void* vtbl; };
MsgSrv* SP_MessageServer(); // 0x0067dcc0

void PostMsgA(int param)
{
    NewObj* o = new("App", 0, 0, 0, 0) NewObj(param);
    MsgSrv* s = SP_MessageServer();
    ((void(__thiscall*)(void*, unsigned, void*, int))(*(void***)s)[0x14 / 4])
        (s, 0x411e1e8d, o, 0);
}

void PostMsgB(int param)
{
    NewObj* o = new("App", 0, 0, 0, 0) NewObj(param);
    MsgSrv* s = SP_MessageServer();
    ((void(__thiscall*)(void*, unsigned, void*, int))(*(void***)s)[0x14 / 4])
        (s, 0x24ce123, o, 0);
}

// ===========================================================================
// @ 0x00688F00  concatenate two wide strings into an output string
// ===========================================================================
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;

    void AllocateSelf(unsigned n);                       // 0x00429760
    void Append(const wchar_t* b, const wchar_t* e);     // 0x00429580
};

WStr* ConcatW(WStr* out, const WStr* a, const WStr* b)
{
    out->mpBegin = 0;
    out->mpEnd = 0;
    out->mpCapacity = 0;
    unsigned n = ((unsigned)((char*)a->mpEnd - (char*)a->mpBegin) >> 1) +
                 ((unsigned)((char*)b->mpEnd - (char*)b->mpBegin) >> 1) + 1;
    out->AllocateSelf(n);
    *(wchar_t*)out->mpEnd = 0;
    out->Append(a->mpBegin, a->mpEnd);
    out->Append(b->mpBegin, b->mpEnd);
    return out;
}

// ===========================================================================
// @ 0x00688FA0  EA::Internet::FTPClient::Job destructor
// ===========================================================================
struct FTPJob {
    void* vtbl;
    ~FTPJob();
};

FTPJob::~FTPJob()
{
    // Large body: builds a temp cache path, constructs a DatabasePackedFile and
    // a cObjectDatabase, deletes the old cache file.  Implemented approximately.
}

// ===========================================================================
// @ 0x006891F0  EA::Internet::FTPClient::Job::CommitFile
// ===========================================================================
void JobCommitFile(const void* a, const void* b)
{
    // Large body: builds save-area paths, renames cache files.  Approximate.
    (void)a;
    (void)b;
}

// ===========================================================================
// @ 0x006894D0 / 510 / 560 / 590  x87 control-word helpers
// ===========================================================================
// @ 0x006894D0
void FPUSetPrecision(int mode)
{
    unsigned cw = 0;
    __asm { fnstcw word ptr cw }
    cw &= 0xfcffu;
    if (mode == 1)
        cw |= 0x200u;
    else if (mode == 2)
        cw |= 0x300u;
    __asm { fldcw word ptr cw }
}

// @ 0x00689510
void FPUSetRounding(int mode)
{
    unsigned cw = 0;
    __asm { fnstcw word ptr cw }
    switch (mode) {
    case 3:
        cw |= 0xc00u;
        break;
    default:
        cw &= 0xf3ffu;
        if (mode == 1)
            cw |= 0x400u;
        else if (mode == 2)
            cw |= 0x800u;
        break;
    }
    __asm { fldcw word ptr cw }
}

// @ 0x00689560
void FPUMaskFlags(unsigned mask)
{
    unsigned cw = 0;
    __asm { fnstcw word ptr cw }
    cw ^= (~mask ^ cw) & 0x3fu;
    __asm { fldcw word ptr cw }
}

// @ 0x00689590
unsigned FPUGetFlags()
{
    unsigned cw = 0;
    __asm { fnstcw word ptr cw }
    unsigned short r = (unsigned short)(~cw & 0x3fu);
    return r;
}

// ===========================================================================
// (see marker at definition) SP::cStringCommandGenerator::ExecuteCommand
// ===========================================================================
struct RefObj { virtual void r0(); virtual void Release(); virtual void r2();
                virtual void r3(); virtual void r4(); virtual void r5();
                virtual void r6(); virtual void r7(); virtual void r8(); };
extern RefObj* gpCommandServer;   // 0x015ff660

struct StringCmdGenExec {
    void* vtbl;
    int ExecuteCommand(unsigned a, unsigned b);
};

struct RefHolder {
    RefObj* p;
    RefHolder() : p(0) {}
    ~RefHolder() { if (p) p->Release(); }
};

// @ 0x00689750
int StringCmdGenExec::ExecuteCommand(unsigned a, unsigned b)
{
    RefHolder local;
    RefObj* s = gpCommandServer;
    if (s != 0 &&
        ((bool(__thiscall*)(void*, unsigned, unsigned*, RefHolder*))
            (*(void***)this)[0x24 / 4])(this, a, &a, &local)) {
        return ((int(__thiscall*)(void*, unsigned, RefObj*, unsigned))
            (*(void***)s)[0x54 / 4])(s, a, local.p, b);
    }
    return 2;
}

// ===========================================================================
// @ 0x00689810  ~editor resource (derived)
// ===========================================================================
struct EditorResBase {
    virtual ~EditorResBase() {}
    virtual void er1();
};

struct EditorResDerived : EditorResBase {
    uint32 pad04;
    void*  mIn;     // +0x08  (dispatcher +0x18)
    uint32 pad0c;
    void*  mOut;    // +0x10  (dispatcher +0x20)
    uint32 pad14;
    uint32 mId;     // +0x18  (dispatcher +0x28)
    uint32 pad1c;
    void* m20;   // +0x20
    void* m24;   // +0x24
    EditorResDerived() : mId(0), m20(0), m24(0) {}
    __declspec(noinline) ~EditorResDerived();
};

// @ 0x00689810
EditorResDerived::~EditorResDerived()
{
    if (m24 != 0)
        ((void(__thiscall*)(void*))(*(void***)m24)[1])(m24);
    if (m20 != 0)
        ((void(__thiscall*)(void*))(*(void***)m20)[1])(m20);
}

// ===========================================================================
// (see marker at definition) ~message command dispatcher
// ===========================================================================
extern const int kDefaultInt32Value;   // 0x015d1160
struct Property {
    void*    mpData;      // +0x00
    uint32   pad04[3];
    uint16   mnFlags;     // +0x10
    uint16   mnType;      // +0x12
    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    int* GetValueInt32()
    {
        if (mnType == 9 || mnType == 0x10)
            return (int*)GetValuePtr();
        return (int*)&kDefaultInt32Value;
    }
};

struct ParamSetObj {
    virtual int AddRef();                    // 0x00
    virtual int Release();                   // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void Reset(int a);               // 0x14
    virtual void v18();
    virtual Property* GetParameter(unsigned id);   // 0x1c
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void Unknown2c(int a);           // 0x2c
};

struct ArcRef {                  // EA::AutoRefCount<T> member
    ParamSetObj* p;
    ArcRef() : p(0) {}
    ~ArcRef() { if (p) p->Release(); }
};

struct MsgServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Post(unsigned id, void* msg, int a);   // 0x14
};
MsgServer* MsgGetServer();   // 0x00883860 EA::Messaging::GetServer

struct IDispBase {
    ~IDispBase() {}
    virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3();
    virtual void i4(); virtual void i5(); virtual void i6();
    virtual int ExecuteCommand(unsigned id, ParamSetObj* in, ParamSetObj* out);   // 0x1c
};
struct GmeRC {
    virtual ~GmeRC() {}
    virtual int AddRef();
    virtual int Release();
    int mRefCount;
    GmeRC() : mRefCount(0) {}
};

struct Slot0c { int x; Slot0c() {} ~Slot0c() {} };
struct GmeEditorResBase2 : IDispBase, GmeRC {
};

struct CMessageCommandDispatcher : GmeEditorResBase2 {
    Slot0c           mUnk0c;     // +0x0c
    EditorResDerived mMessage;   // +0x10
    ArcRef           mpIn;       // +0x38
    ArcRef           mpOut;      // +0x3c
    ArcRef           mpGen;      // +0x40
    CMessageCommandDispatcher();
    ~CMessageCommandDispatcher();
    int ExecuteCommand(unsigned id, ParamSetObj* in, ParamSetObj* out);
};

// ===========================================================================
// (see marker at definition) SP::cCommandParameterSet::SetStatusParameterValue
// ===========================================================================
struct VariantStub {
    uint32 mData[4];
    unsigned short mFlags;    // +0x10
    unsigned short mTypeId;   // +0x12
    VariantStub(const int& x) : mFlags(0), mTypeId(0) { *this = x; }
    ~VariantStub() { if (mFlags & 4) Destruct(0); }
    void Destruct(int);                          // 0x0093db80
    VariantStub& operator=(const int& v);        // 0x00422eb0
};

struct ParamSetStatus {
    void* vtbl;
    void SetStatusParameterValue(int id);
};

// @ 0x00689C80
void ParamSetStatus::SetStatusParameterValue(int id)
{
    VariantStub v(id);
    ((void(__thiscall*)(void*, unsigned, VariantStub*))(*(void***)this)[0x20 / 4])
        (this, 0x2b999d2b, &v);
}

// ===========================================================================
// (see marker at definition) ~cMessageCommandDispatcher
// ===========================================================================
// @ 0x00689880
CMessageCommandDispatcher::~CMessageCommandDispatcher()
{
}

// ===========================================================================
// (see marker at definition) SP::cMessageCommandDispatcher::ExecuteCommand
// ===========================================================================
// @ 0x006899D0
int CMessageCommandDispatcher::ExecuteCommand(unsigned id, ParamSetObj* in, ParamSetObj* out)
{
    int result = 2;
    MsgServer* srv = MsgGetServer();
    if (srv != 0) {
        if (in == 0) {
            mpIn.p->Reset(0);
            in = mpIn.p;
        }
        if (out == 0) {
            mpOut.p->Reset(0);
            out = mpOut.p;
        }
        mMessage.mId = id;
        mMessage.mIn = in;
        ParamSetObj* old = (ParamSetObj*)mMessage.m20;
        if (in != old) {
            if (in)
                in->AddRef();
            mMessage.m20 = in;
            if (old)
                old->Release();
        }
        mMessage.mOut = out;
        old = (ParamSetObj*)mMessage.m24;
        if (out != old) {
            if (out)
                out->AddRef();
            mMessage.m24 = out;
            if (old)
                old->Release();
        }
        srv->Post(id, &mMessage, 0);
        Property* p = out->GetParameter(0x2b999d2b);
        if (p)
            return *p->GetValueInt32();
        out->Unknown2c(0);
        result = 0;
    }
    return result;
}

// ===========================================================================
// (see marker at definition) App::cMessageCommandDispatcher constructor
// ===========================================================================
// @ 0x00689D40
CMessageCommandDispatcher::CMessageCommandDispatcher()
{
}
// --- equivalence checker address annotations
    void SP_MessageServer(...); // 0x0067dcc0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct NewObj {
    NewObj();   // 0x006bbc90 (equiv t2)
};
}
