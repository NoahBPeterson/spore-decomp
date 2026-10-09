// Slice s006a9470 -- property-system commands + SP::cPropertyManager init/write.
// Module flags: /O2 /MD /Gy /EHsc /TP
//
// cListPropsCheat::Execute, cPropCheat::Execute, cPropertyManager::Init and
// cPropertyManager (Factory)::WriteResource are written as complete bodies.  Offsets are
// RETAIL offsets (the 2008 PDB layout of cPropertyManager differs).
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------- allocation / EH helpers
void* operator new(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  operator delete[](void* p);   // 0x00f47380

// eastl::string (char, default allocator).  The empty string lives in a shared static buffer.
extern char gEmptyStr[];   // 0x01667bac
namespace eastl {
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    string() : mpBegin(gEmptyStr), mpEnd(gEmptyStr), mpCapacity(gEmptyStr + 1) {}
    ~string()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            delete[] mpBegin;
    }
    const char* c_str() const { return mpBegin; }
    void sprintf(const char* fmt, ...);        // 0x00472fe0
};
}

// eastl::vector<unsigned> with the sp_vector_allocator (count word lives at begin[-1])
struct UIntVec {
    unsigned* mpBegin;
    unsigned* mpEnd;
    unsigned* mpCapacity;
    UIntVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~UIntVec()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            delete[] mpBegin;
    }
};

// ---------------------------------------------------------------- refcounting
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};

template <class T> struct AutoRef {
    T* p;
    AutoRef() : p(0) {}
    AutoRef(T* o) : p(o) { if (p) p->AddRef(); }
    ~AutoRef() { if (p) p->Release(); }
    AutoRef& operator=(T* o)
    {
        T* old = p;
        if (o != old) {
            if (o) o->AddRef();
            p = o;
            if (old) old->Release();
        }
        return *this;
    }
};

// ---------------------------------------------------------------- value types
struct ResourceKey { unsigned a, b, c; };

struct Variant {                       // EA::Variant (0x14 bytes)
    char data[0x10];
    unsigned short flags;              // |2 = initialised, 0x80 = array, 4 = owns data
    unsigned short type;
    Variant() : flags(0), type(0) {}
    ~Variant() { if (flags & 4) Destruct(0); }
    Variant& operator=(const Variant& o);        // 0x00542b80
    void Destruct(int);                          // 0x0093db80
};

struct PropObj {                       // property entry (flags at +0x10)
    char pad[0x10];
    unsigned flags;                    // 0x80 = array
};

// ---------------------------------------------------------------- stubs for external classes
struct cError { eastl::string mMessage; cError(const char* fmt, ...); cError(const cError&); };

namespace EA { namespace ArgScript {
struct cArguments {
    const char** MainArguments(int* pCount, int min, int max);   // 0x00838020
    const char** OptionArguments(const char* name, int n);       // 0x00838330
    bool HasFlag(const char* name);                              // 0x008380b0
};
}}
using EA::ArgScript::cArguments;

void __cdecl Output(void* out, const char* fmt, ...);                         // 0x00841000
void __cdecl SPKeyFromName(ResourceKey* out, const char* name, int a, int b); // 0x0068d5a0
bool __cdecl WildcardMatch(const char* str, const char* pattern, int flags);  // 0x0093d5d0
void __cdecl GetVariantTypeDescription(PropObj* p, eastl::string* out);       // 0x006a5690
void __cdecl GetVariantValueDescription(PropObj* p, eastl::string* out);      // 0x006a8610
bool __cdecl ParseVariantValue(unsigned type, void* out, int argc, const char** argv, Variant* v); // 0x006a6340

// property list (cDirectPropertyList)
struct PropList : IRefObj {
    virtual void p2(); virtual void p3(); virtual void p4();
    virtual void SetProperty(unsigned id, const Variant* v);            // slot 5
    virtual void RemoveProperty(unsigned id);                           // slot 6
    virtual bool HasProperty(unsigned id);                              // slot 7
    virtual void GetVariant(unsigned id, const Variant** out);          // slot 8
    virtual void p9();
    virtual PropObj* GetProperty(unsigned id);                          // slot 10
    virtual void LoadFrom(void* res);                                   // slot 11
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual bool Write(void* stream);                                   // slot 16
    virtual void GetPropertyIDs(UIntVec* out);                          // slot 17
};
extern PropList* sAppProperties;   // 0x015fd918

// hashtable<uint, eastl::string> (id -> name), only what Execute needs
struct IdNameNode { unsigned key; char* name; };
struct IdNameIter { IdNameNode* node; IdNameNode** bucket; };
struct IdNameTable {
    int pad0;
    IdNameNode** mpBuckets;            // +4
    unsigned mnBucketCount;            // +8
    IdNameIter find(const unsigned& key);                           // 0x00a3b2c0
    IdNameNode* end() { return mpBuckets[mnBucketCount]; }
};

struct cPropertyManager;
struct IPropertyManager {                                           // SP::PropertyManager()
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5();
    virtual bool LookupPropertyID(const char* name, unsigned* outId);   // slot 6
    virtual const char* GetPropertyName(unsigned id);                   // slot 7
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual bool GetPropertyList(unsigned a, unsigned c, AutoRef<PropList>* out);   // slot 11
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual const Variant* GetDefaultVariant(unsigned id);              // slot 20
};
IPropertyManager* __cdecl PropertyManager();                        // 0x0067de30

// property-manager message (MessageBasicRC<5>)
struct MsgData { unsigned v, t; };
struct MsgBase {
    virtual void m0();
    long mRefCount;
    MsgData d[5];
    MsgBase() { _InterlockedExchange(&mRefCount, 0); }
    void Destruct();                                                // 0x00421cf0
};
struct PropMsg : MsgBase {
    virtual void m0();
    ~PropMsg() { Destruct(); }
};
struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Post(unsigned id, MsgBase* msg, int arg);          // slot 5
    virtual void s6(); virtual void s7();
    virtual void AddHandler(unsigned id, void* handler);            // slot 8
};
IMessageServer* __cdecl MessageServer();                            // 0x0067dcc0

// ===========================================================================
// `anonymous namespace'::cListPropsCheat::Execute  ("listprops")
// ===========================================================================
struct ListMgr;
struct cCommandBase {                  // base of ArgScript commands / cheats (ctor at 0x0083c800)
    cCommandBase();                    // 0x0083c800
    virtual void Execute(cArguments* args);
    void* mOut;                        // +4
    int f8, fc;
};
struct cListPropsCheat : cCommandBase {
    ListMgr* mMgr;                     // +0x10
    virtual void Execute(cArguments* args);
};

struct ListMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5();
    virtual void m6();
    virtual const char* GetPropertyName(unsigned id);                   // slot 7
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual bool GetPropertyList(unsigned a, unsigned c, AutoRef<PropList>* out);   // slot 11
    char pad[0x148 - 4 - 0];           // (vptr + padding)
    IdNameTable mIdToName;             // +0x148
};

// @ 0x006a9470
void cListPropsCheat::Execute(cArguments* args)
{
    AutoRef<PropList> list(sAppProperties);

    const char** opt = args->OptionArguments("list", 1);
    if (opt) {
        ResourceKey key = {0, 0, 0};
        SPKeyFromName(&key, opt[0], 0, 0);
        list = 0;
        if (!mMgr->GetPropertyList(key.a, key.c, &list))
            throw cError("no such property list!");
    }

    bool ids = args->HasFlag("ids");
    args->HasFlag("desc");

    int cnt;
    const char* wild = 0;
    const char** main = args->MainArguments(&cnt, 0, 1);
    if (cnt > 0)
        wild = main[0];

    UIntVec v;
    list.p->GetPropertyIDs(&v);
    if (v.mpBegin != v.mpEnd) {
        int n = (int)(v.mpEnd - v.mpBegin);
        for (int i = 0; i < n; i++) {
            PropObj* prop = list.p->GetProperty(v.mpBegin[i]);

            eastl::string typeDesc;
            GetVariantTypeDescription(prop, &typeDesc);
            eastl::string valueDesc;
            eastl::string suffix;
            GetVariantValueDescription(prop, &valueDesc);

            unsigned id = v.mpBegin[i];
            const char* name = mMgr->GetPropertyName(id);
            bool named = name != 0;
            if (!name) {
                unsigned key = v.mpBegin[i];
                IdNameIter it = mMgr->mIdToName.find(key);
                if (it.node != mMgr->mIdToName.end()) {
                    name = it.node->name;
                    named = name != 0;
                }
            }

            if (named && (!wild || WildcardMatch(name, wild, 0))) {
                if (!ids)
                    Output(mOut, "%s = %s (%s) %s\n", name, valueDesc.c_str(), typeDesc.c_str(), suffix.c_str());
                else
                    Output(mOut, "%s [0x%08x] = %s (%s) %s\n", name, v.mpBegin[i], valueDesc.c_str(),
                           typeDesc.c_str(), suffix.c_str());
            } else if (!wild) {
                Output(mOut, "0x%08x = %s %s %s\n", v.mpBegin[i], valueDesc.c_str(), typeDesc.c_str(),
                       suffix.c_str());
            }
        }
    }
}

// ===========================================================================
// `anonymous namespace'::cPropCheat::Execute  ("prop")
// ===========================================================================
struct cPropCheat : cCommandBase {
    ListMgr* mMgr;                     // +0x10
    virtual void Execute(cArguments* args);
};

// @ 0x006a9790
void cPropCheat::Execute(cArguments* args)
{
    AutoRef<PropList> list(sAppProperties);

    int argc = 0;
    const char** argv = args->MainArguments(&argc, 1, 0x7fffffff);

    unsigned propId = 0;
    PropertyManager()->LookupPropertyID(argv[0], &propId);
    if (propId == 0)
        throw cError("no such property: %s", argv[0]);

    if (argc > 1) {
        Variant v;
        v = *PropertyManager()->GetDefaultVariant(propId);
        if (v.type == 0) {
            const Variant* p;
            list.p->GetVariant(propId, &p);
            v = *p;
        }
        v.flags |= 2;
        unsigned vt = v.type;
        if (v.flags & 0x80)
            vt |= 0x80000000;
        int n = argc - 1;
        if (!ParseVariantValue(vt, mOut, n, argv + 1, &v))
            throw cError("unknown property type");
        list.p->SetProperty(propId, &v);

        PropMsg msg;
        msg.d[0].v = ((unsigned*)list.p)[3];
        msg.d[1].v = ((unsigned*)list.p)[4];
        msg.d[2].v = ((unsigned*)list.p)[2];
        MessageServer()->Post(0xf62def, &msg, 0);
    } else if (args->HasFlag("remove") || args->HasFlag("clear")) {
        list.p->RemoveProperty(propId);
        PropMsg msg;
        msg.d[0].v = ((unsigned*)list.p)[3];
        msg.d[1].v = ((unsigned*)list.p)[4];
        msg.d[2].v = ((unsigned*)list.p)[2];
        MessageServer()->Post(0xf62def, &msg, 0);
    } else {
        PropObj* prop = list.p->GetProperty(propId);
        eastl::string typeDesc;
        GetVariantTypeDescription(prop, &typeDesc);
        eastl::string valueDesc;
        GetVariantValueDescription(prop, &valueDesc);
        eastl::string suffix;
        Output(mOut, "%s = %s (%s) %s \n", argv[0], valueDesc.c_str(), typeDesc.c_str(), suffix.c_str());
    }
}

// ===========================================================================
// SP::cPropertyManager::Init / Factory::WriteResource
// ===========================================================================
struct IResource : IRefObj {
    virtual void p2();
    virtual unsigned GetType();                                    // slot 3
};
struct IParser : IRefObj {
    virtual void p2();                                             // +8
    virtual void p3();
    virtual void SetOwner(void* a);                                // +0x10 (slot 4)
    virtual void RegisterCommand(const char* name, void* cmd);     // +0x14 (slot 5)
    virtual void q6(); virtual void q7(); virtual void q8(); virtual void q9(); virtual void q10();
    virtual void q11(); virtual void q12(); virtual void q13(); virtual void q14(); virtual void q15();
    virtual void q16(); virtual void q17(); virtual void q18(); virtual void q19(); virtual void q20();
    virtual void q21(); virtual void q22(); virtual void q23(); virtual void q24(); virtual void q25();
    virtual void q26(); virtual void q27(); virtual void q28(); virtual void q29(); virtual void q30();
    virtual void q31(); virtual void q32(); virtual void q33(); virtual void q34(); virtual void q35();
    virtual void q36(); virtual void q37(); virtual void q38(); virtual void q39(); virtual void q40();
    virtual void q41(); virtual void q42(); virtual void q43(); virtual void q44(); virtual void q45();
    virtual struct HashHolder* RegisterHashFunction(const char* name, void* obj);   // +0xb8 (slot 46)
};
struct IFileParser : IRefObj {
    virtual void f2();                                             // +8
    virtual void f3();
    virtual void SetParser(IParser* p);                            // +0x10 (slot 4)
    virtual void f5(); virtual void f6();
    virtual void ParseFile(const char* path, int flags);           // +0x1c (slot 7)
    virtual void f8();                                             // +0x20
    virtual void f9(); virtual void f10();
    virtual void f11(int a);                                       // +0x2c
};
struct IResMgr {
    virtual void r0(); virtual void r1(); virtual void r2();
    virtual bool GetResource(ResourceKey* key, AutoRef<IResource>* out, int a, int b, int c, int d);   // +0xc
    virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7(); virtual void r8();
    virtual void r9(); virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13();
    virtual void r14(); virtual void r15(); virtual void r16();
    virtual void RegisterFactory(int a, void* factory, int b);     // +0x44
    virtual void r18(); virtual void r19(); virtual void r20(); virtual void r21();
    virtual IResource* FindResource(ResourceKey* key);             // +0x58
};
struct ICheatMgr {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5();
    virtual void AddCheat(const char* name, void* cheat, int a);   // +0x18
};

IResMgr* __cdecl GetResourceManager();                   // 0x0067dcd0
ICheatMgr* __cdecl CheatManager();                       // 0x0067de20
IParser* __cdecl CreateParser();                         // 0x008408d0
IFileParser* __cdecl CreateFileParser();                 // 0x00840940
const wchar_t* __cdecl GetDirFromID(unsigned id);        // 0x006886b0
void __cdecl ParseHashDefault(IParser* parser, ResourceKey* key);   // 0x008476b0
unsigned* __cdecl RBTreeIncrement(void* node);           // 0x00921580

namespace eastl {
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    wstring(const wchar_t* pBegin);                                // RangeInitialize, 0x00579a90
    ~wstring()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            delete[] mpBegin;
    }
    void append(const wchar_t* pBegin, const wchar_t* pEnd);      // 0x00429580
};
}
eastl::string* __cdecl ConvertToString8(eastl::string* out, const eastl::wstring* in);   // 0x0093c570

struct HashHolder {
    void Finish();                                       // 0x0083df90
};

// ArgScript command classes registered by Init (vtables at 0x1408d64 ... 0x1408dbc)
struct cCommandBase2 {                                   // ctor at 0x0083c840
    cCommandBase2();                                     // 0x0083c840
    virtual void Execute(cArguments* args);
    void* mOut; int f8, fc;
};
struct cPropertyDefCmd : cCommandBase { virtual void Execute(cArguments* args); };          // size 0x10
struct cPropertyGroupDefCmd : cCommandBase { virtual void Execute(cArguments* args); };     // size 0x10
struct cPropertyListDefCmd : cCommandBase2 {                                                 // size 0x14
    int mField10;
    cPropertyListDefCmd() : mField10(0) {}
    virtual void Execute(cArguments* args);
};
struct cAppPropsCmd {                                                                        // size 0x34
    cAppPropsCmd();                                                                          // 0x0083cdd0
    virtual void Execute(cArguments* args);
    char pad[0x30];
};
struct cHashFunction { virtual void Eval(); int f4; cHashFunction() : f4(0) {} };            // size 8

extern const char* gCmdName_Property;        // 0x0152ee54
extern const char* gCmdName_PropertyGroup;   // 0x0152ef9c
extern const char* gCmdName_PropertyList;    // 0x0152ef98
extern const char* gCmdName_AppProps;        // 0x0152efa0

void* operator new(size_t size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

struct cPropertyManager {
    void* vtbl;                    // +0
    void* factoryVtbl;             // +4  (Factory subobject)
    int f8;
    char mHandler[4];              // +0xc (IHandlerRC subobject)
    char mBlock10[4];              // +0x10 (ArgScript state)
    bool mInitialized;             // +0x14
    bool mUseFileParser;           // +0x15
    char pad16[2];
    IResMgr* mResMgr;              // +0x18
    bool mParsing;                 // +0x1c
    char pad1d[3];
    int mTreeAlloc;                // +0x20
    char* mTreeEndNode() { return (char*)this + 0x24; }
    void* mTreeRight;              // +0x24
    void* mTreeLeft;               // +0x28
    void* mTreeRoot;               // +0x2c
    char mTreeColor;               // +0x30
    char pad31[3];
    unsigned mTreeSize;            // +0x34
    char pad38[4];
    PropList* BaseList() { return (PropList*)((char*)this + 0x3c); }   // embedded list
    char pad3c[0x178 - 0x3c];
    AutoRef<IFileParser> mFileParser;   // +0x178
    AutoRef<IParser> mParser;           // +0x17c

    bool Init();                                       // 0x006a9b60
    void DoNuke(void* root);                           // 0x0068a0f0 (rbtree)
};
struct PropVec { void reserve(unsigned n); };          // 0x006a84f0, at list+0x18
struct RBIter { void* node; };
struct PropTree { RBIter find(const unsigned& key); }; // 0x00e5c780          // 0x006a84f0, at list+0x18

// @ 0x006a9b60
bool cPropertyManager::Init()
{
    if (mInitialized)
        return true;
    mInitialized = true;

    mResMgr = GetResourceManager();
    mResMgr->RegisterFactory(1, &factoryVtbl, 0);

    ResourceKey* appKey = (ResourceKey*)((char*)sAppProperties + 8);
    appKey->a = 0;
    appKey->b = 0xb1b104;
    appKey->c = 0;

    ResourceKey key = {0x8ea246b, 0xb1b104, 0};
    IResource* found = mResMgr->FindResource(&key);
    if (found && found->GetType() != 0x34728492) {
        AutoRef<IResource> res;
        if (mResMgr->GetResource(&key, &res, 0, 0, 0, 0)) {
            BaseList()->LoadFrom(res.p);
            sAppProperties->LoadFrom(res.p);
        }
    }

    mParser = CreateParser();
    if (mUseFileParser) {
        mFileParser = CreateFileParser();
        mFileParser.p->f2();
        mFileParser.p->SetParser(mParser.p);
    } else {
        mParser.p->p2();
    }
    mParser.p->SetOwner(&mBlock10);

    mParser.p->RegisterCommand(gCmdName_Property, new("ArgScript/Property", 0, 0, 0, 0) cPropertyDefCmd);
    mParser.p->RegisterCommand(gCmdName_PropertyGroup, new("ArgScript/PropertyGroup", 0, 0, 0, 0) cPropertyGroupDefCmd);
    mParser.p->RegisterCommand(gCmdName_PropertyList, new("ArgScript/PropertyList", 0, 0, 0, 0) cPropertyListDefCmd);
    mParser.p->RegisterCommand(gCmdName_AppProps, new("ArgScript/AppProps", 0, 0, 0, 0) cAppPropsCmd);
    mParser.p->RegisterHashFunction("hash", new("App", 0, 0, 0, 0) cHashFunction)->Finish();

    mParsing = true;
    if (mFileParser.p) {
        eastl::wstring path(GetDirFromID(0xa0214f));
        const wchar_t* name = L"Properties.txt";
        const wchar_t* nameEnd = name;
        while (*nameEnd)
            ++nameEnd;
        path.append(name, nameEnd);
        {
            eastl::string conv;
            mFileParser.p->ParseFile(ConvertToString8(&conv, &path)->mpBegin, 5);
        }
        mFileParser.p->f8();
        mFileParser.p->f11(1);
    } else {
        ResourceKey hashKey = {0x658b0ab2, 0x24a0e52, 0};
        ParseHashDefault(mParser.p, &hashKey);
    }
    mParsing = false;

    ((PropVec*)((char*)this + 0x54))->reserve(mTreeSize);

    void* end = &mTreeRight;
    for (char* it = (char*)mTreeLeft; it != (char*)end; it = (char*)RBTreeIncrement(it))
        BaseList()->SetProperty(*(unsigned*)(it + 0x10), (const Variant*)(it + 0x14));
    DoNuke(mTreeRoot);
    mTreeRight = end;
    mTreeLeft = end;
    mTreeRoot = 0;
    mTreeColor = 0;
    mTreeSize = 0;

    ICheatMgr* cheats = CheatManager();
    if (cheats) {
        cListPropsCheat* listCheat = new("App", 0, 0, 0, 0) cListPropsCheat;
        listCheat->mMgr = (ListMgr*)this;
        cPropCheat* propCheat = new("App", 0, 0, 0, 0) cPropCheat;
        propCheat->mMgr = (ListMgr*)this;
        cheats->AddCheat("prop", propCheat, 0);
    }

    IMessageServer* ms = MessageServer();
    if (ms)
        ms->AddHandler(0xf62ade, mHandler);
    return true;
}

// ---------------------------------------------------------------- WriteResource
struct IStream32 {
    virtual void s0();
    virtual int AddRef();
    virtual int Release();
    virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13();
    virtual void Write(const void* data, int len);                  // slot 14 (+0x38)
};
struct StreamRef {
    IStream32* p;
    StreamRef(IStream32* s) : p(s) { if (p) p->AddRef(); }
    ~StreamRef() { if (p) p->Release(); }
};
struct IQueryable {
    virtual void a(); virtual void b(); virtual void c();
    virtual void* Query(unsigned id);                               // slot 3 (+0xc)
};
struct IResEntry {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5();
    virtual IStream32* GetStream();                                  // slot 6 (+0x18)
    virtual char* GetOwner();                                        // slot 7 (+0x1c)
};
struct PropWriteList : PropList {
    // slot 16 = Write(stream), reused from PropList
};

struct cPropertyFactory {                                             // the Factory subobject (this = manager + 4)
    bool WriteResource(PropList* list, IResEntry* entry, int a3, int a4);   // @ 0x006aa130
};

// @ 0x006aa130
bool cPropertyFactory::WriteResource(PropList* list, IResEntry* entry, int a3, int a4)
{
    cPropertyManager* mgr = (cPropertyManager*)((char*)this - 4);
    bool ok;
    StreamRef stream(entry->GetStream());
    char* owner = entry->GetOwner();
    if (!owner || !((IQueryable*)(owner + 4))->Query(0x226a1de)) {
        ok = list->Write(stream.p);
    } else {
        eastl::string line;
        UIntVec ids;
        list->GetPropertyIDs(&ids);
        eastl::string desc;
        int n = (int)(ids.mpEnd - ids.mpBegin);
        for (int i = 0; i < n; i++) {
            unsigned id = ids.mpBegin[i];
            bool present;
            if (mgr->mParsing) {
                unsigned key = id;
                present = ((PropTree*)((char*)mgr + 0x20))->find(key).node != mgr->mTreeEndNode();
            } else {
                present = mgr->BaseList()->HasProperty(id);
            }
            if (present) {
                PropObj* prop = list->GetProperty(id);
                GetVariantValueDescription(prop, &desc);
                if (prop->flags & 0x80)
                    stream.p->Write("array ", 6);
                const char* name = ((IPropertyManager*)mgr)->GetPropertyName(ids.mpBegin[i]);
                if (name) {
                    const char* e = name;
                    while (*e++) {}
                    stream.p->Write(name, (int)(e - (name + 1)));
                    stream.p->Write(" ", 1);
                } else {
                    line.sprintf("0x%08x ", ids.mpBegin[i]);
                    stream.p->Write(line.mpBegin, (int)(line.mpEnd - line.mpBegin));
                }
                for (const char* c = desc.mpBegin; *c; ++c) {
                    if (*c == '\r' && c[1] == '\n')
                        continue;
                    if (*c == '\n')
                        stream.p->Write("\r\n", 2);
                    else
                        stream.p->Write(c, 1);
                }
                stream.p->Write("\r\n", 2);
            }
        }
        ok = true;
    }
    return ok;
}

// ===========================================================================
// FUN_006aa0d0 -- bool-vector append helper
// ===========================================================================
struct BoolVec {
    void* mpBegin;   // +0
    void* mpEnd;     // +4
};

struct BoolVecOwner {
    void* vtbl;      // +0

    bool Append(int arg1, BoolVec* v);
};

void FUN_0050f0d0(void*, void*);
void* FUN_0050e4b0(void*, void*);
void BoolVec_DoInsertValue(void* dst, void* src, int count);

// @ 0x006aa0d0
bool BoolVecOwner::Append(int arg1, BoolVec* v)
{
    // this->vfunc_0x48(arg1, v)
    typedef void (__thiscall* Fn48)(void*, int, BoolVec*);
    ((Fn48)((void**)vtbl)[0x48 / 4])(this, arg1, v);

    FUN_0050f0d0(v->mpBegin, v->mpEnd);
    void* dst = FUN_0050e4b0(v->mpBegin, v->mpEnd);
    void* src = v->mpEnd;
    BoolVec_DoInsertValue(dst, src, 0);
    v->mpEnd = (char*)v->mpEnd - (((char*)src - (char*)dst) >> 2) * 4;
    return v->mpBegin != v->mpEnd;
}
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
    void operator delete[](void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct cCommandBase {
    cCommandBase(); // 0x0083c800
};
struct HashHolder {
    void Finish(); // 0x0083df90
};
struct cCommandBase2 {
    cCommandBase2(); // 0x0083c840
};
}
