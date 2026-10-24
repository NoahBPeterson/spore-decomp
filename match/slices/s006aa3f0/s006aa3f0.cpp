// Slice s006aa3f0 — SP::cPropertyManager property-name registration and related helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <string.h>

// ===========================================================================
// EASTL support types
// ===========================================================================

// eastl::basic_string<char> (16 bytes)
struct StrKey {
    void* mpBegin;      // +0
    void* mpEnd;        // +4
    void* mpCapacity;   // +8
    void* mAllocator;   // +0xc

    void assign(const char* first, const char* last);                 // 0x00454cb0
    void assign(const char* s) { assign(s, s + strlen(s)); }
};

// keyed hashtables (declared only: calls stay out-of-line like the original instantiations)
struct MapNameToID {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    int& operator[](const StrKey& key);       // 0x006a8340
};

struct MapIDToName {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    StrKey* operator[](const uint32_t& key);  // 0x006a8410
};

struct Vec32 {
    uint32_t* mpBegin;     // +0
    uint32_t* mpEnd;       // +4
    uint32_t* mpCapacity;  // +8

    void DoInsertValue(uint32_t* pos, const uint32_t* value);  // 0x004558a0
};

void EA_MakeCaseInsensitive(const char* src, StrKey* dst);   // 0x00840cc0

// ===========================================================================
// Shared support types for the remaining (previously stubbed) functions
// ===========================================================================
#undef VFN
#define VFN(p, off) ((*(void***)(p))[(off) / 4])

// ---- EA::Variant (EASTL variant, 0x14 bytes) ----
struct Variant {
    uint32_t raw0, raw1, raw2, raw3;   // +0x00
    uint16_t mFlags;                   // +0x10  bit2 = "owns", bit7 = "unsigned"
    uint16_t mTypeId;                  // +0x12

    void Assign(const Variant* src);       // 0x0542b80 (thiscall)
    void AssignInt(const int* v);          // 0x0422eb0 (thiscall)
    void Destruct(int b);                  // 0x093db80 (thiscall)
};

struct PairUV { uint32_t key; Variant val; };

struct VMapNode {
    VMapNode* mpNodeRight;   // +0x00
    VMapNode* mpNodeLeft;    // +0x04
    VMapNode* mpNodeParent;  // +0x08
    uint8_t   mColor;        // +0x0c
    uint8_t   padD[3];
    uint32_t  mKey;          // +0x10
    Variant   mValue;        // +0x14
};

struct VIter { VMapNode* mpNode; };
struct RBInsertResult { void* mpNode; uint8_t mInserted; char pad[3]; };

// eastl::rbtree<unsigned, eastl::pair<const unsigned, EA::Variant>>
struct VMap {
    uint32_t  pad0;          // +0x00
    VMapNode* aRight;        // +0x04  (anchor node, also end())
    VMapNode* aLeft;         // +0x08
    VMapNode* aParent;       // +0x0c
    uint8_t   aColor;        // +0x10
    uint8_t   pad1[3];
    uint32_t  mnSize;        // +0x14
    uint32_t  mAlloc;        // +0x18

    VMapNode* endNode() { return (VMapNode*)&aRight; }
    VIter find(const uint32_t& k);                             // 0x0e5c780 (thiscall)
    RBInsertResult DoInsertValue(const PairUV& value, uint32_t b); // 0x068a600 (thiscall)
    void DoNukeSubtree(VMapNode* p);                           // 0x068a0f0 (thiscall)
};

// eastl hashtable base (bucket array + sizes), as used by the property maps
struct HMap {
    uint32_t pad0;            // +0x00
    void**   mpBuckets;       // +0x04
    uint32_t mnBucketCount;   // +0x08
    uint32_t mnElementCount;  // +0x0c
    uint32_t mAlloc;          // +0x10

    void DoFreeNodesH(void** b, uint32_t n);       // 0x06a85b0 (thiscall)
    void DoFreeNodesSound(void** b, uint32_t n);   // 0x0a39c20 (thiscall)
    void ClearBuckets(void** b, uint32_t n);       // 0x042a7b0 (thiscall)
};

// eastl::basic_string<char>
struct EStr {
    char*  mpBegin;      // +0x00
    char*  mpEnd;        // +0x04
    char*  mpCapacity;   // +0x08
    void*  mAllocator;   // +0x0c

    void push_back(char c);                       // 0x05306c0 (thiscall)
    void append(const char* b, const char* e);    // 0x0455d60 (thiscall)
    void assign(const char* s);                   // 0x06a4380 (thiscall)
    void Dtor();                                  // 0x0530670 (thiscall)
    bool Fun_0047d570(void* b);                   // 0x0047d570 (thiscall)
};

// eastl::basic_string<wchar_t>
struct WStr {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    void*    mAllocator;   // +0x0c

    void RangeInitialize(const wchar_t* s);            // 0x0579a90 (thiscall)
    void Append(const wchar_t* b, const wchar_t* e);   // 0x0429580 (thiscall)
};

// eastl::vector<bool, ...> / vector<u32> base (begin / end / capacity)
struct VecU32 {
    uint32_t* mpBegin;     // +0x00
    uint32_t* mpEnd;       // +0x04
    uint32_t* mpCapacity;  // +0x08

    void Resize(uint32_t n);          // 0x004cd3c0 (thiscall)
};

// EA::ArgScript::cArguments
struct cArguments {
    char data[0x44];
    void Dtor();                                                  // 0x0837fa0 (thiscall)
    void SplitIntoArguments(const char* s);                       // 0x08383c0 (thiscall)
    const char** MainArguments(size_t* pCount, int mn, int mx);   // 0x0838020 (thiscall)
};

// EA::ArgScript::cParser (SubstituteVariables thunk)
struct cParser8 {
    void SubstituteVariables(void* s, int b);   // 0x0843650 (thiscall)
};

// SP::cPropertyList
struct cPropertyList {
    char data[0x38];
    void Dtor();                       // 0x0686320 (thiscall)
};

// SP::cError (thrown as a C++ exception)
struct SPcError {
    SPcError(const char* fmt, ...);    // 0x052df30 (thiscall)
};

// EA::IO::StreamBuffer (cFileStream style)
struct StreamBuffer {
    char data[0x30];
    void Ctor(uint32_t size, uint32_t b, void* file);   // 0x093b530 (thiscall)
    void Dtor();                                        // 0x093b5a0 (thiscall)
};

extern "C" void  Fun_011e0912(void* obj, const void* throwInfo);    // 0x11e0912  _CxxThrowException
extern "C" void* Fun_011e0744(void* d, const void* s, unsigned n);  // 0x11e0744  memcpy thunk
extern "C" void  Fun_00f47380(void* p);                             // 0x0f47380  operator delete

// ArgScript / cPropertyManager helpers
int  ParseEnum(const char* s, int* table);                                             // 0x0840bb0
bool ParseVariantValue(unsigned type, void* obj, int n, const char** argv, Variant* v); // 0x06a6340
bool SetDefaultVariantValue(unsigned type, Variant* v);                                // 0x06a4990
bool StripCommentsAndWhiteSpace(char* src, void* a, void* b);                          // 0x0840ec0
int  Fun_008409f0(void* out, void* s, char* fmt);                                      // 0x08409f0
bool Fun_006a6240(const char* name, int* out);                                         // 0x06a6240
bool Fun_006a3f00(int* p);                                                             // 0x06a3f00
int  Fun_006a32c0(const char* s);                                                      // 0x06a32c0
void* ConvertToString8(void* out, const void* wstr);                                   // 0x093c570
uint32_t ReadLine(void* stream, char* buf, size_t n);                                  // 0x093a8b0
bool StrEq(const void* s, const char* lit);                                            // 0x0555020
void* MessageServer();                                                                 // 0x067dcc0
void* GetManager();                                                                    // 0x067dcd0
void* CheatManager();                                                                  // 0x067de20

static void FreeEABuffer(void* p, void* end)
{
    if ((char*)end - (char*)p > 1 && p)
        Fun_00f47380(p);
}

// ===========================================================================
// SP::cPropertyManager (retail member offsets; dev PDB shifted by +4 in places)
// ===========================================================================
struct cPropertyManager {
    void*    mvf00;                        // +0x00
    void*    mBaseFactory;                 // +0x04
    void*    mu08;                         // +0x08
    void*    mBaseIface;                   // +0x0c
    uint32_t mu10;                         // +0x10
    uint8_t  mInitialized;                 // +0x14
    char     pad15[3];                     // +0x15
    void*    mResourceManager;             // +0x18
    uint8_t  mFlag1c;                      // +0x1c
    char     pad1d[3];                     // +0x1d
    VMap     mPropertyMap;                 // +0x20  rbtree<u32, Variant>
    cPropertyList mPropertyList;           // +0x3c
    HMap     mPropertyLists;               // +0x74
    char     pad88[0xc];                   // +0x88
    MapNameToID mPropertyNameToIDMap;      // +0x94
    char pad01[0x14];
    MapIDToName mPropertyIDToNameMap;      // +0xb4
    char pad02[0x14];
    MapNameToID mGroupNameToIDMap;         // +0xd4
    char pad03[0x14];
    MapIDToName mGroupIDToNameMap;         // +0xf4
    char pad04[0x14];
    Vec32 mGroupIDs;                       // +0x114
    char pad05[8];
    MapNameToID mLocalPropertyNameToIDMap; // +0x128
    char pad06[0x14];
    MapIDToName mLocalPropertyIDToNameMap; // +0x148
    char pad07[0x14];
    StrKey mLCName;                        // +0x168
    void*    mp178;                        // +0x178
    void*    mp17c;                        // +0x17c
    EStr     mLine;                        // +0x180
    cArguments mArguments;                 // +0x190
    uint32_t mu1d4;                        // +0x1d4
    EStr     mArgsB;                       // +0x1d8
    uint8_t  mFlag1e8;                     // +0x1e8

    void RegisterPropertyName(const char* name, uint32_t id);
    void RegisterPropertyNameLocal(const char* name, uint32_t id);
    void Fun_006aa450(const char* name, uint32_t id);
    bool Shutdown();
    void ParseAndAddProperty(uint32_t id, uint32_t arg2, uint32_t arg3);
    void InsertPropertyEntry(uint32_t key, Variant* value);
    uint8_t AppendBoolVector(uint32_t arg, int* vec);
    char ReadResource(void* obj, int* res);
    void DestroySelf();
};

// @ 0x006aa3f0
void cPropertyManager::RegisterPropertyName(const char* name, uint32_t id)
{
    EA_MakeCaseInsensitive(name, &mLCName);
    mPropertyNameToIDMap[mLCName] = id;
    StrKey* s = mPropertyIDToNameMap[id];
    s->assign(name);
}

// @ 0x006aa5e0
void cPropertyManager::RegisterPropertyNameLocal(const char* name, uint32_t id)
{
    EA_MakeCaseInsensitive(name, &mLCName);
    mLocalPropertyNameToIDMap[mLCName] = id;
    StrKey* s = mLocalPropertyIDToNameMap[id];
    s->assign(name);
}

// @ 0x006aa450
void cPropertyManager::Fun_006aa450(const char* name, uint32_t id)
{
    StrKey* s = mGroupIDToNameMap[id];
    s->assign(name);

    uint32_t* end = mGroupIDs.mpEnd;
    if (end < mGroupIDs.mpCapacity) {
        mGroupIDs.mpEnd = end + 1;
        if (end)
            *end = id;
    } else {
        mGroupIDs.DoInsertValue(end, &id);
    }
}

// @ 0x006aa7c0
bool cPropertyManager::Shutdown()
{
    if (!mInitialized)
        return true;
    mInitialized = false;
    mResourceManager = 0;

    void* ms = MessageServer();
    if (ms)
        ((void(__thiscall*)(void*, void*, uint32_t, int))VFN(ms, 0x2c))(
            ms, (void*)((char*)this + 0xc), 0xf62ade, -0x270f);

    void* mgr = GetManager();
    if (mgr) {
        void* mgr2 = GetManager();
        ((void(__thiscall*)(void*, uint32_t, void*, uint32_t))VFN(mgr2, 0x44))(
            mgr2, 0, (void*)((char*)this + 4), 0);
    }

    void* ch = CheatManager();
    if (ch) {
        ((void(__thiscall*)(void*, const char*))VFN(ch, 0x1c))(ch, "listProps");
        ((void(__thiscall*)(void*, const char*))VFN(ch, 0x1c))(ch, "prop");
    }

    if (mp178 != 0) {
        void* p = mp178;
        ((void(__thiscall*)(void*))VFN(p, 0xc))(p);
        if (mp178 != 0) {
            void* q = mp178;
            mp178 = 0;
            ((void(__thiscall*)(void*))VFN(q, 4))(q);
        }
    } else {
        void* p = mp17c;
        ((void(__thiscall*)(void*))VFN(p, 0xc))(p);
    }
    if (mp17c != 0) {
        void* q = mp17c;
        mp17c = 0;
        ((void(__thiscall*)(void*))VFN(q, 4))(q);
    }

    HMap* h;
    h = (HMap*)&mPropertyLists;
    h->ClearBuckets(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;

    h = (HMap*)&mGroupNameToIDMap;
    h->DoFreeNodesH(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;

    h = (HMap*)&mGroupIDToNameMap;
    h->DoFreeNodesSound(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;

    Fun_011e0744(mGroupIDs.mpBegin, mGroupIDs.mpEnd, 0);
    mGroupIDs.mpEnd = mGroupIDs.mpBegin;
    return true;
}

// @ 0x006aaa10
void cPropertyManager::ParseAndAddProperty(uint32_t a1, uint32_t a2, uint32_t a3)
{
    char*   line   = (char*)a1;
    void*   parser = (void*)a2;
    void*   out    = (void*)a3;

    if (!StripCommentsAndWhiteSpace(line, &mLine, (void*)((char*)this + 0x1d4)))
        return;

    if (mArgsB.mpBegin != mArgsB.mpEnd) {
        if (mLine.mpBegin != 0 && *mLine.mpBegin == 'e' && StrEq(&mLine, "end")) {
            mLine.Fun_0047d570(&mArgsB);
            if (mArgsB.mpBegin != mArgsB.mpEnd) {
                *mArgsB.mpBegin = 0;
                mArgsB.mpEnd = mArgsB.mpBegin;
            }
        } else {
            mArgsB.push_back(' ');
            mArgsB.append(mLine.mpBegin, mLine.mpEnd);
            return;
        }
    }

    EStr tmp;
    tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCapacity = 0; tmp.mAllocator = 0;
    Fun_008409f0(&tmp, &mLine, (char*)0x1401864);
    ((cParser8*)parser)->SubstituteVariables(&mLine, 1);
    mArguments.SplitIntoArguments(mLine.mpBegin);

    size_t n = 0;
    const char** av = mArguments.MainArguments(&n, 0, 0x7fffffff);

    if (StrEq(&tmp, "array") && mArgsB.mpBegin == mArgsB.mpEnd && (int)n > 0) {
        mArgsB.assign(av[0]);
        tmp.Dtor();
        return;
    }

    Variant v;
    v.raw0 = 0; v.raw1 = 0; v.raw2 = 0; v.raw3 = 0;
    v.mFlags = 0; v.mTypeId = 0;

    uint32_t id = 0;
    int count = (int)n;
    const char** args = av;
    unsigned typeBits = 0;

    if (StrEq(&tmp, "property") && count > 2) {
        id = ((uint32_t(__thiscall*)(void*, const char*))VFN(parser, 0xa0))(parser, args[1]);
        this->RegisterPropertyNameLocal(args[0], id);
        typeBits = (unsigned)ParseEnum(args[2], (int*)0x152ee58);
        v.mTypeId = (uint16_t)typeBits;
        if ((int)typeBits < 0)
            v.mFlags = (uint16_t)(v.mFlags | 0x80);
        args += 3;
        count -= 3;
    } else if (StrEq(&tmp, "prop") && count > 1) {
        typeBits = (unsigned)ParseEnum(args[0], (int*)0x152ee58);
        v.mTypeId = (uint16_t)typeBits;
        if ((int)typeBits < 0)
            v.mFlags = (uint16_t)(v.mFlags | 0x80);
        id = (uint32_t)Fun_006a32c0(args[1]);
        this->RegisterPropertyNameLocal(args[1], id);
        args += 2;
        count -= 2;
    } else {
        int propId = 0;
        if (!Fun_006a6240(args[0], &propId)) {
            SPcError err("unknown property: '%s'", args[0]);
            Fun_011e0912(&err, (const void*)0x14f9174);
            return;
        }
        if (Fun_006a3f00(&propId)) {
            Variant* src = (Variant*)((void*(__thiscall*)(void*))VFN(this, 0x50))(this);
            v.Assign(src);
        } else {
            if (!((char(__thiscall*)(void*, int))VFN(out, 0x1c))(out, propId)) {
                if (v.mFlags & 4) v.Destruct(0);
                if (((char*)tmp.mpCapacity - (char*)tmp.mpBegin) > 1 && tmp.mpBegin)
                    Fun_00f47380(tmp.mpBegin);
                return;
            }
            Variant* src = (Variant*)((void*(__thiscall*)(void*, int))VFN(out, 0x28))(out, propId);
            v.Assign(src);
        }
        id = (uint32_t)propId;
        typeBits = v.mTypeId;
        if (v.mFlags & 0x80)
            typeBits |= 0x80000000u;
    }

    v.mFlags = (uint16_t)(v.mFlags | 2);
    if (count > 0 || (v.mFlags & 0x80)) {
        if (!ParseVariantValue(typeBits, parser, count, args, &v)) {
            SPcError err("couldn't handle type");
            Fun_011e0912(&err, (const void*)0x14f9174);
        }
    }
    ((void(__thiscall*)(void*, uint32_t, Variant*))VFN(out, 0x14))(out, id, &v);
    if (v.mFlags & 4)
        v.Destruct(0);
    if (((char*)tmp.mpCapacity - (char*)tmp.mpBegin) > 1 && tmp.mpBegin)
        Fun_00f47380(tmp.mpBegin);
}

// ===========================================================================
// `anonymous namespace'::cPropertyCommand::Parse
// ===========================================================================
struct cPropertyCommand {
    char pad0[4];
    uint32_t mArg3;                 // +4
    char pad8[4];
    cPropertyManager* mManager;     // +0xc
    uint32_t mArg4;                 // +0x10

    bool Parse(void** param_2);
};

// @ 0x006aadb0
bool cPropertyCommand::Parse(void** param_2)
{
    mManager->ParseAndAddProperty(*(uint32_t*)param_2, mArg3, mArg4);
    return true;
}

// ===========================================================================
// Remaining slice functions
// ===========================================================================

// @ 0x006aa4c0
void cPropertyManager::InsertPropertyEntry(uint32_t key, Variant* value)
{
    Variant v;
    v.raw0 = 0; v.raw1 = 0; v.raw2 = 0; v.raw3 = 0;
    v.mTypeId = 0;
    v.mFlags = 0;
    v.Assign(value);
    v.mFlags = (uint16_t)(v.mFlags | 2);

    if (mFlag1c == 0) {
        cPropertyList* pl = &mPropertyList;
        ((void(__thiscall*)(cPropertyList*, uint32_t, Variant*))VFN(pl, 0x14))(pl, key, &v);
    } else {
        VIter it = mPropertyMap.find(key);
        if (it.mpNode == mPropertyMap.endNode()) {
            PairUV p;
            p.key = key;
            p.val.raw0 = 0; p.val.raw1 = 0; p.val.raw2 = 0; p.val.raw3 = 0;
            p.val.mFlags = 0; p.val.mTypeId = 0;
            p.val.Assign(&v);
            mPropertyMap.DoInsertValue(p, key & 0xffffff00u);
            if (p.val.mFlags & 4)
                p.val.Destruct(0);
        } else {
            it.mpNode->mValue.Assign(&v);
        }
    }
    if (v.mFlags & 4)
        v.Destruct(0);
}

// `anonymous namespace'::cPropertyCommand::Execute
struct cPropertyCommandExec {
    char pad0[4];
    void* mIface;                 // +0x04
    char pad8[4];
    cPropertyManager* mManager;   // +0x0c

    void Execute(void* args);
    void ExecuteGroupName(void* args);
};

// @ 0x006aa640
void cPropertyCommandExec::Execute(void* args)
{
    size_t n = 0;
    const char** av = ((cArguments*)args)->MainArguments(&n, 3, 0x7fffffff);

    void* iface = mIface;
    uint32_t id = ((uint32_t(__thiscall*)(void*, const char*))VFN(iface, 0xa0))(iface, av[1]);
    mManager->RegisterPropertyName(av[0], id);

    Variant v;
    v.raw0 = 0; v.raw1 = 0; v.raw2 = 0; v.raw3 = 0;
    v.mFlags = 0; v.mTypeId = 0;
    int zero = 0;
    v.AssignInt(&zero);

    int type = ParseEnum(av[2], (int*)0x152ee58);
    bool ok;
    if ((int)(n - 3) < 1)
        ok = SetDefaultVariantValue((unsigned)type, &v);
    else
        ok = ParseVariantValue((unsigned)type, iface, (int)(n - 3), av + 3, &v);
    if (!ok) {
        SPcError err("couldn't handle type");
        Fun_011e0912(&err, (const void*)0x14f9174);
    }

    mManager->InsertPropertyEntry(id, &v);
    if (mManager->mFlag1e8) {
        void* app = *(void**)0x15fd918;
        ((void(__thiscall*)(void*, uint32_t, Variant*))VFN(app, 0x14))(app, id, &v);
    }
    if (v.mFlags & 4)
        v.Destruct(0);
}

// @ 0x006aa780
void cPropertyCommandExec::ExecuteGroupName(void* args)
{
    size_t n = 0;
    const char** av = ((cArguments*)args)->MainArguments(&n, 2, 0x7fffffff);

    void* iface = mIface;
    uint32_t id = ((uint32_t(__thiscall*)(void*, const char*))VFN(iface, 0xa0))(iface, av[1]);
    mManager->Fun_006aa450(av[0], id);
}

// @ 0x006aa910
uint8_t cPropertyManager::AppendBoolVector(uint32_t arg, int* vec)
{
    VecU32* v = (VecU32*)vec;
    // Inlined SimpleVector::erase(begin(), end()): a zero-length memcpy, then the end pointer
    // is shrunk by (int32_t)(end - begin) >> 2 elements, exactly as the original computes it
    // (arithmetic shift, so a bogus end pointer wraps rather than collapsing onto begin).
    Fun_011e0744(v->mpBegin, v->mpEnd, 0);
    {
        uint32_t ep = (uint32_t)(size_t)v->mpEnd;
        uint32_t bp = (uint32_t)(size_t)v->mpBegin;
        int32_t  dropped = (int32_t)(ep - bp) >> 2;
        v->mpEnd = (uint32_t*)(size_t)(ep - (uint32_t)dropped * 4u);
    }

    struct FillRequest {
        void*    vtbl;    // +0x00  0x13f662c
        uint32_t f4;      // +0x04  0xb1b104
        uint32_t arg;     // +0x08
    };
    FillRequest req;
    req.vtbl = (void*)0x13f662c;
    req.f4 = 0xb1b104;
    req.arg = arg;

    VecU32 local;
    local.mpBegin = 0; local.mpEnd = 0; local.mpCapacity = 0;

    void* obj = mResourceManager;
    uint32_t count = ((uint32_t(__thiscall*)(void*, void*, void*, uint32_t))VFN(obj, 0x38))(
        obj, &local, &req, 0);

    v->Resize(count);
    for (uint32_t i = 0; i < count; i++)
        ((uint32_t*)v->mpBegin)[i] = *(uint32_t*)((char*)local.mpBegin + i * 0xc);

    req.vtbl = (void*)0x13eb394;

    if (local.mpBegin != 0 && ((uint32_t*)local.mpBegin)[-1] != 0)
        Fun_00f47380(local.mpBegin);

    return (uint8_t)(v->mpBegin != v->mpEnd);
}

// @ 0x006aae30
void cPropertyManager::DestroySelf()
{
    mvf00 = (void*)0x14091e8;
    mBaseFactory = (void*)0x14091b0;
    mBaseIface = (void*)0x14091a0;

    if (mArgsB.mpBegin != 0 && ((char*)mArgsB.mpCapacity - (char*)mArgsB.mpBegin) > 1)
        Fun_00f47380(mArgsB.mpBegin);
    mArguments.Dtor();
    if (mLine.mpBegin != 0 && ((char*)mLine.mpCapacity - (char*)mLine.mpBegin) > 1)
        Fun_00f47380(mLine.mpBegin);
    if (mp17c != 0) {
        void* p = mp17c;
        ((void(__thiscall*)(void*))VFN(p, 4))(p);
    }
    if (mp178 != 0) {
        void* p = mp178;
        ((void(__thiscall*)(void*))VFN(p, 4))(p);
    }
    if (mLCName.mpBegin != 0 && ((char*)mLCName.mpCapacity - (char*)mLCName.mpBegin) > 1)
        Fun_00f47380(mLCName.mpBegin);

    HMap* h;
    h = (HMap*)&mLocalPropertyIDToNameMap;
    h->DoFreeNodesSound(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;
    h = (HMap*)&mLocalPropertyNameToIDMap;
    h->DoFreeNodesH(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;

    if (mGroupIDs.mpBegin != 0 && ((char*)mGroupIDs.mpCapacity - (char*)mGroupIDs.mpBegin) > 1)
        Fun_00f47380(mGroupIDs.mpBegin);

    h = (HMap*)&mGroupIDToNameMap;
    h->DoFreeNodesSound(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;
    h = (HMap*)&mGroupNameToIDMap;
    h->DoFreeNodesH(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;
    h = (HMap*)&mPropertyIDToNameMap;
    h->DoFreeNodesSound(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;
    h = (HMap*)&mPropertyNameToIDMap;
    h->DoFreeNodesH(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;
    h = (HMap*)&mPropertyLists;
    h->ClearBuckets(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;

    mPropertyList.Dtor();
    mPropertyMap.DoNukeSubtree(mPropertyMap.aParent);

    mBaseIface = (void*)0x13eb394;
    mBaseFactory = (void*)0x13effb8;
}

// @ 0x006ab120
char cPropertyManager::ReadResource(void* obj, int* res)
{
    void* v = ((void*(__thiscall*)(void*))VFN(obj, 0x1c))(obj);
    if (v == 0) {
        void* a = *(void**)res;
        void* r = ((void*(__thiscall*)(void*))VFN(obj, 0x18))(obj);
        return ((char(__thiscall*)(void*, void*))VFN(a, 0x3c))(a, r);
    }

    void* sub = *(void**)((char*)v + 4);
    void* node = ((void*(__thiscall*)(void*, uint32_t))VFN(sub, 0xc))(sub, 0x226a1de);
    if (node == 0) {
        void* a = *(void**)res;
        void* r = ((void*(__thiscall*)(void*))VFN(obj, 0x18))(obj);
        return ((char(__thiscall*)(void*, void*))VFN(a, 0x3c))(a, r);
    }

    void* local18 = *(void**)node;
    wchar_t wbuf[256];
    void* w0 = ((void*(__thiscall*)(void*, void*))VFN(obj, 0x10))(obj, wbuf);
    if (!((char(__thiscall*)(void*, void*))VFN(local18, 0x64))(local18, w0))
        return 0;

    void* sw = ((void*(__thiscall*)(void*))VFN(node, 0x28))(node);
    WStr w;
    w.mpBegin = 0; w.mpEnd = 0; w.mpCapacity = 0; w.mAllocator = 0;
    w.RangeInitialize((const wchar_t*)sw);
    wchar_t* we = wbuf;
    while (*we)
        we++;
    w.Append(wbuf, we);

    EStr c;
    c.mpBegin = 0; c.mpEnd = 0; c.mpCapacity = 0; c.mAllocator = 0;
    ConvertToString8(&c, &w);

    void* file = ((void*(__thiscall*)(void*))VFN(obj, 0x18))(obj);
    local18 = file;
    if (file != 0)
        ((void(__thiscall*)(void*))VFN(file, 4))(file);

    uint32_t u4 = (uint32_t)mp178;
    if (mArgsB.mpBegin != mArgsB.mpEnd) {
        *mArgsB.mpBegin = 0;
        mArgsB.mpEnd = mArgsB.mpBegin;
    }

    if (file != 0) {
        ((void(__thiscall*)(int*, uint32_t, void*))VFN(res, 0x48))(res, u4, file);
        mu1d4 = 0;

        StreamBuffer sb;
        sb.Ctor(0x2000, 0, file);
        char buf[0x2000];
        for (;;) {
            uint32_t got = ReadLine(&sb, buf, 0x2000);
            if (got >= 0xfffffffe)
                break;
            ((cPropertyManager*)((char*)this - 4))->ParseAndAddProperty((uint32_t)buf, u4, (uint32_t)res);
        }
        sb.Dtor();
    }

    HMap* h = (HMap*)&mLocalPropertyNameToIDMap;
    h->DoFreeNodesH(h->mpBuckets, h->mnBucketCount);
    h->mnElementCount = 0;

    if (file != 0) {
        ((void(__thiscall*)(void*, uint32_t))VFN(file, 8))(file, 0);
        ((void(__thiscall*)(void*))VFN(file, 4))(file);
    }

    if (c.mpBegin != 0 && ((char*)c.mpCapacity - (char*)c.mpBegin) > 1)
        Fun_00f47380(c.mpBegin);

    if (w.mpBegin != 0) {
        if ((((char*)w.mpCapacity - (char*)w.mpBegin) & 0xfffffffe) > 2)
            Fun_00f47380(w.mpBegin);
        res[0xd] = res[0xd] + 1;
    }
    return 0;
}
