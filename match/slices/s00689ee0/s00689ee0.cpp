// Slice s00689ee0: SP::cCommandServer / cCommandParameterSet / cStringCommandGenerator
// command system, small EASTL rbtree map<unsigned, Variant> / map<unsigned, cCommandInfo>
// helpers and command execution. Compiled /O2 /MD /Gy /EHsc /TP /GS-.
#include <string.h>
#include <new>
#include "types.h"

#define VFN(p, off) ((*(void***)(p))[(off) / 4])

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef wchar_t        wch;

// ---- out-of-slice callees (relocation-masked) ----
extern "C" void* MemcpyT(void* dst, const void* src, unsigned n);            // 0x011e0744 memcpy thunk
extern "C" void  EASTL_dealloc(void* p);                                     // 0x0f47380
void* operator new(size_t sz, const char* name, unsigned a, unsigned b, const char* file, unsigned line);   // 0x0f473a0
extern "C" void* EASTL_alloc6(unsigned sz, const char* name, unsigned a,
                              unsigned b, const char* file, unsigned line);  // 0x0f473a0
extern "C" void* RBTreeIncrement(void* node);                                // 0x0921580
extern "C" void* RBTreeDecrement(void* node);                                // 0x09215c0
extern "C" void  RBTreeErase(void* node, void* anchor);                      // 0x0921880
extern "C" int   WMemCmp(const wch* a, const wch* b, unsigned n);            // 0x0572930
extern "C" unsigned ParseCmd(void* s, int n, int ch, void* out, unsigned f); // 0x093d740
extern "C" int   MakeLocaleAvailable(void* a, void* b);                      // 0x087d9a0
extern "C" void  VecDestroyValues(void* first, void* last);                  // 0x084aad0
struct WStr;
struct EmptyAlloc {};
void __cdecl Ins16(void* a, void* b, const WStr& c, const EmptyAlloc& d);                  // 0x0555c40
extern "C" void  Sub689dc0(void* a, int b, void* c);                         // 0x0689dc0
extern "C" void  Sub689e80(void* a);                                         // 0x0689e80
extern "C" void  Sub68a140(void* a, void* b, void* c);                       // 0x068a140

// ---- globals ----
extern "C" wch  gEmptyWStr[];              // 0x1667bac empty string buffer
extern "C" char gAllocTag[];               // 0x13ebc58 "App"
extern "C" char gEASTLFile[];              // 0x13ebb38 allocator.h path
extern "C" wch  gLiteral1403308[];         // 0x1403308 wide literal
extern "C" wch  gLiteral1403384[];         // 0x1403384 format literal
extern "C" void* gCommandServer;           // 0x15ff660
extern "C" void* vtbl_cCommandParameterSet;   // 0x1403310
extern "C" void* vtbl_cCommandParameterSet2;  // 0x140330c
extern "C" void* vtbl_cStringCommandGenerator; // 0x1403354
extern "C" void* vtbl_cStringCommandGenerator2;// 0x1403350
extern "C" void* vtbl_Base1;               // 0x13ef094
extern "C" void* vtbl_Base0;               // 0x13eb938

// =====================================================================
// EASTL basic_string<wchar_t>
// =====================================================================
struct WStr {
    wch* mpBegin;
    wch* mpEnd;
    wch* mpEndCap;
    u32  mAllocator;      // +0x0c (+0x10 with allocator, matches retail 16-byte string)

    void AllocateSelf(unsigned n);                       // 0x0429760
    void Assign(const wch* b, const wch* e);             // 0x0423650
    void Append(const wch* b, const wch* e);             // 0x0429580
    void Insert(wch* pos, const wch* b, const wch* e);   // 0x05f7da0
    void MakeLower();                                    // 0x05e8e80
    void AssignCStr(const wch* s);                       // 0x05c3d90
    void Format(const wch* fmt, ...);                    // 0x041e050

    WStr() {
        mpBegin = gEmptyWStr;
        mpEnd = gEmptyWStr;
        mpEndCap = (wch*)((char*)gEmptyWStr + 2);
    }
    WStr(const WStr& x) {
        mpBegin = 0; mpEnd = 0; mpEndCap = 0;
        RangeInit(x.mpBegin, x.mpEnd);
    }
    void RangeInit(const wch* b, const wch* e) {
        unsigned n = (unsigned)(e - b);
        AllocateSelf(n + 1);
        mpEnd = (wch*)((char*)MemcpyT(mpBegin, b, n * 2) + n * 2);
        *mpEnd = 0;
    }
    ~WStr() {
        if (((int)((char*)mpEndCap - (char*)mpBegin) & ~1) > 2 && mpBegin)
            EASTL_dealloc(mpBegin);
    }
};

// =====================================================================
// EA::Variant
// =====================================================================
struct Variant {
    u32 raw0, raw1, raw2, raw3;   // +0x00
    u16 mFlags;                   // +0x10
    u16 mTypeId;                  // +0x12

    void Assign(const void* src);                       // 0x0542b80 (thiscall)
    void Destruct(int b);                               // 0x093db80 (thiscall)
    void Init(int a, int b, int c, int d, int e);       // 0x093dd80 (thiscall)
};

// A Variant local with the inline destructor (EH state around the scope).
struct VariantL : Variant {
    VariantL() { mFlags = 0; mTypeId = 0; }
    VariantL(int a, int b, int c, int d, int e) { mFlags = 0; mTypeId = 0; Init(a, b, c, d, e); }
    ~VariantL() { if (mFlags & 4) Destruct(0); }
};

// =====================================================================
// map<unsigned, Variant>
// =====================================================================
struct PairUV { u32 key; Variant val; };

struct VMapNode {
    VMapNode* mpNodeRight;   // +0x00
    VMapNode* mpNodeLeft;    // +0x04
    VMapNode* mpNodeParent;  // +0x08
    u8 mColor;               // +0x0c
    u8 padD[3];
    u32 mKey;                // +0x10
    Variant mValue;          // +0x14

    VMapNode(const PairUV& s) {
        mKey = s.key;
        mValue.mFlags = 0;
        mValue.mTypeId = 0;
        mValue.Assign(&s.val);
    }
};

struct VIter {
    VMapNode* mpNode;
    VIter() {}
    VIter(const VIter& x) : mpNode(x.mpNode) {}
    VIter(VMapNode* p) : mpNode(p) {}
};

struct VMap {
    u32 pad0;                // +0x00
    VMapNode* aRight;        // +0x04 (anchor, also end())
    VMapNode* aLeft;         // +0x08 (anchor begin)
    VMapNode* aParent;       // +0x0c (root)
    union {
        u32 aColorWord;      // +0x10 (whole dword zeroed by the anchor init)
        struct { u8 aColor; u8 pad1[3]; };
    };
    u32 mnSize;              // +0x14
    u32 mAlloc;              // +0x18

    VMapNode* endNode() { return (VMapNode*)&aRight; }
    u32 size() const { return mnSize; }
    VIter find(const u32& k);                       // out-of-slice
    void DoNukeSubtree(VMapNode* p) {
        while (p) {
            DoNukeSubtree(p->mpNodeRight);
            VMapNode* next = p->mpNodeLeft;
            Variant* pv = &p->mValue;
            if (pv->mFlags & 4)
                pv->Destruct(0);
            EASTL_dealloc(p);
            p = next;
        }
    }
};

// =====================================================================
// cCommandInfo + its map (cCommandServer)
// =====================================================================
struct cCommandInfo {
    u32 mnID;        // +0x00
    WStr msName;     // +0x04
    WStr msParam;    // +0x14

    cCommandInfo(const cCommandInfo& o);
    ~cCommandInfo();
};

struct CInfoNode {
    CInfoNode* mpNodeRight;  // +0x00
    CInfoNode* mpNodeLeft;   // +0x04
    CInfoNode* mpNodeParent; // +0x08
    u8 mColor;               // +0x0c
    u8 padD[3];
    u32 mKey;                // +0x10
    cCommandInfo mValue;     // +0x14
};

// =====================================================================
// cCommandParameterSet (flat layout, size 0x3c)
// =====================================================================
struct ICmdSrv {   // cCommandServer interface (vtable slot +0x34)
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual u32 GetCommandIDFromTokens(const wch* first);   // +0x34
};
struct IParamSetV {   // cCommandParameterSet virtual interface
    virtual void AddRef();                                  // +0x00
    virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07();
    virtual void SetParameter(u32 index, Variant* v);       // +0x20
};
struct cCommandParameterSet {
    void* vtbl0;             // +0x00
    void* vtbl1;             // +0x04
    u32 mRefCount;           // +0x08
    VMap mParameterMap;      // +0x0c
    Variant mDefaultVariant; // +0x28

    __declspec(noinline) cCommandParameterSet();
    ~cCommandParameterSet();
    u32 GetNextParameterID(u32 id);
    void RemoveParameter(u32 id);
    void AdjustParameterCount(u32 n);
    bool ExecuteCommand(int cmd, void* a, void* b);
};

// =====================================================================
// cStringCommandGenerator (flat layout)
// =====================================================================
struct cStringCommandGenerator {
    void* vtbl0;             // +0x00
    void* vtbl1;             // +0x04
    u32 mRefCount;           // +0x08
    WStr* mArrBegin;         // +0x0c
    WStr* mArrEnd;           // +0x10
    WStr* mArrCap;           // +0x14
    u32 mAlloc0;             // +0x18
    u32 mAlloc1;             // +0x1c
    void* mpEmptySet;        // +0x20

    ~cStringCommandGenerator();
    cStringCommandGenerator();
    bool SetParameterCount(WStr* str, u32* outId, cCommandParameterSet** outSet);   // 0x0068B000
};

// =====================================================================
// cCommandServer (flat layout, map at +4, set at +0x2c)
// =====================================================================
struct CGenNode {
    CGenNode* mpNodeRight;   // +0x00
    CGenNode* mpNodeLeft;    // +0x04
    CGenNode* mpNodeParent;  // +0x08
    u8 mColor;               // +0x0c
    u8 padD[3];
    u32 mKey;                // +0x10
    void* mValue;            // +0x14 (AutoRefCount)
};

struct cCommandServer {
    u32 pad0;                // +0x00
    // map<unsigned, cCommandInfo> at +0x04
    u32 cmp0;                // +0x04
    CInfoNode* cmRight;      // +0x08 (end)
    CInfoNode* cmLeft;       // +0x0c (begin)
    CInfoNode* cmParent;     // +0x10 (root)
    u8 cmColor;              // +0x14
    u8 cmPad[3];
    u32 cmSize;              // +0x18
    u32 cmAlloc;             // +0x1c
    void* mpDispatcher;      // +0x20
    void* mpMsgDispatcher;   // +0x24
    void* mpStrGen;          // +0x28
    // set<AutoRefCount<ICommandGenerator>> at +0x2c
    u32 cs0;                 // +0x2c
    CGenNode* csRight;       // +0x30 (end)
    CGenNode* csLeft;        // +0x34
    CGenNode* csParent;      // +0x38
    u8 csColor;              // +0x3c
    u8 csPad[3];
    u32 csSize;              // +0x40
    u32 csAlloc;             // +0x44
    bool mbAutoBasic;        // +0x48

    u32 FindCommandInfoByName(const wch* name);
    bool GetCommandInfo(u32 id, WStr* name, WStr* param);
    bool RegisterCommandParameterInfo(u32 id, const wch* param);
    u32  GetCommandIDFromCommandString(WStr* const str, int len);
    bool RegisterCommandGenerator(void* gen);
    bool UnregisterCommandGenerator(void* gen);
    int  ExecuteCommandFormatted(const wch* fmt, ...);
};

// =====================================================================
// 0x00689ee0  cCommandInfo::cCommandInfo(const cCommandInfo&)
// =====================================================================
// @ 0x00689ee0
cCommandInfo::cCommandInfo(const cCommandInfo& o)
    : mnID(o.mnID), msName(o.msName), msParam(o.msParam) {}

// =====================================================================
// 0x0068a000  cCommandInfo::~cCommandInfo
// =====================================================================
// @ 0x0068a000
cCommandInfo::~cCommandInfo() {}

// =====================================================================
// 0x0068a040  find command-info node by parameter-name string
// =====================================================================
// @ 0x0068a040
u32 cCommandServer::FindCommandInfoByName(const wch* name) {
    CInfoNode* p = cmLeft;
    CInfoNode* endNode = (CInfoNode*)&cmRight;
    while (p != endNode) {
        const wch* nrl = p->mValue.msName.mpBegin;
        int nlen = (int)(p->mValue.msName.mpEnd - nrl);
        const wch* q = name;
        while (*q) q += 1;
        int qlen = (int)(q - name);
        int mn = qlen < nlen ? qlen : nlen;
        int r = WMemCmp(nrl, name, (unsigned)mn);
        if (r == 0 && nlen == qlen)
            return p->mValue.mnID;
        p = (CInfoNode*)RBTreeIncrement(p);
    }
    return 0;
}

// =====================================================================
// 0x0068a250  map<unsigned,Variant> node allocator
// =====================================================================
void* operator new(size_t, const char* name, unsigned a, unsigned b,
                   const char* file, unsigned line);
void operator delete(void*, const char* name, unsigned a, unsigned b,
                     const char* file, unsigned line);

// @ 0x0068a250
extern "C" VMapNode* __stdcall FUN_0068a250(const PairUV* src) {
    return new (gAllocTag, 0u, 0u, gEASTLFile, 0xd1u) VMapNode(*src);
}

// =====================================================================
// 0x0068a2e0  static empty string accessor
// =====================================================================
// @ 0x0068a2e0
extern "C" WStr* FUN_0068a2e0() {
    static WStr s;
    return &s;
}

// =====================================================================
// 0x0068a320  command-string fixup helper
// =====================================================================
// @ 0x0068a320
extern "C" void __stdcall FUN_0068a320(WStr* src, WStr* dst) {
    if (dst != src)
        dst->Assign(src->mpBegin, src->mpEnd);

    const wch* ecxEnd = src->mpEnd;
    const wch* esiBeg = src->mpBegin;

    if (((int)ecxEnd - (int)esiBeg) >> 1 == 0)
        goto block;

    {
        const wch* p = esiBeg;
        if (p == ecxEnd)
            goto block;
        do {
            if (*p == 1)
                break;
            p += 1;
        } while (p != ecxEnd);
        if (p == ecxEnd)
            goto block;
        if (((int)p - (int)esiBeg) >> 1 != 0)
            goto block;

        p = esiBeg;
        if (p == ecxEnd)
            goto end;
        do {
            if (*p == 9)
                break;
            p += 1;
        } while (p != ecxEnd);
        if (p == ecxEnd)
            goto end;
        if (((int)p - (int)esiBeg) >> 1 == -1)
            goto end;
    }

block:
    {
        const wch* lit = gLiteral1403308;
        const wch* le = lit;
        do { le += 1; } while (*le != 0);
        dst->Insert(dst->mpBegin, lit, le);
        dst->Append(lit, le);
    }
end:
    ;
}

// =====================================================================
// 0x0068a3f0  cCommandServer::GetCommandInfo
// =====================================================================
// @ 0x0068a3f0
bool cCommandServer::GetCommandInfo(u32 id, WStr* name, WStr* param) {
    CInfoNode* endNode = (CInfoNode*)&cmRight;
    VMap* map = (VMap*)((char*)this + 4);
    CInfoNode* node = (CInfoNode*)map->find(id).mpNode;
    if (node != (CInfoNode*)endNode) {
        WStr* srcName = &node->mValue.msName;
        if (srcName != name)
            name->Assign(srcName->mpBegin, srcName->mpEnd);
        if (param) {
            WStr* srcParam = &node->mValue.msParam;
            if (srcParam != param)
                param->Assign(srcParam->mpBegin, srcParam->mpEnd);
        }
        return true;
    }
    return false;
}

// =====================================================================
// 0x0068a460  vector<WStr>::vector(n, a)  (ctor: base sub-object 0x7c7a40, dtor 0x554b10)
// =====================================================================
struct WStrOOL {   // WStr whose destructor calls the out-of-line DeallocateSelf
    wch* mpBegin;
    wch* mpEnd;
    wch* mpEndCap;
    u32  mAllocator;
    WStrOOL() {
        mpBegin = gEmptyWStr;
        mpEnd = gEmptyWStr;
        mpEndCap = (wch*)((char*)gEmptyWStr + 2);
    }
    ~WStrOOL() { DeallocateSelf(); }
    void DeallocateSelf();                               // 0x0933960
};

struct VBase16 {
    WStr* mpBegin;
    WStr* mpEnd;
    WStr* mpEndCap;
    VBase16(u32 n, const EmptyAlloc& a);                       // 0x007c7a40 (thiscall, ret 8)
    ~VBase16();                                          // 0x00554b10
};

struct vector : VBase16 {
    __declspec(noinline) vector(u32 n, const EmptyAlloc& a);   // 0x0068a460
};

// @ 0x0068a460
vector::vector(u32 n, const EmptyAlloc& a) : VBase16(n, a) {
    const WStr tmp;
    Ins16(mpBegin, (void*)n, tmp, a);
    mpEnd = (WStr*)((char*)mpBegin + n * 0x10);
}

// =====================================================================
// 0x00689fc0  cCommandParameterSet::GetNextParameterID
// =====================================================================
// @ 0x00689fc0
u32 cCommandParameterSet::GetNextParameterID(u32 id) {
    VMapNode* node = mParameterMap.find(id).mpNode;
    VMapNode* endNode = mParameterMap.endNode();
    if (node != endNode) {
        VMapNode* next = (VMapNode*)RBTreeIncrement(node);
        if (next != endNode)
            return next->mKey;
    }
    return 0xffffffffu;
}

// =====================================================================
// 0x0068a720  cCommandParameterSet::~cCommandParameterSet
// =====================================================================
// @ 0x0068a720
cCommandParameterSet::~cCommandParameterSet() {
    vtbl0 = &vtbl_cCommandParameterSet;
    vtbl1 = &vtbl_cCommandParameterSet2;
    if (mDefaultVariant.mFlags & 4)
        mDefaultVariant.Destruct(0);
    mParameterMap.DoNukeSubtree(mParameterMap.aParent);
    vtbl1 = &vtbl_Base1;
    vtbl0 = &vtbl_Base0;
}

// =====================================================================
// 0x0068a7a0  adjust parameter count
// =====================================================================
// @ 0x0068a7a0
void cCommandParameterSet::AdjustParameterCount(u32 n) {
    while (mParameterMap.size() < n) {
        VariantL v;
        ((void(__thiscall*)(cCommandParameterSet*, Variant*))VFN(this, 0x24))(this, &v);
    }
    while (mParameterMap.size() > n) {
        VMapNode* node = (VMapNode*)RBTreeDecrement((char*)this + 0x10);
        mParameterMap.mnSize -= 1;
        RBTreeIncrement(node);
        RBTreeErase(node, &mParameterMap.aRight);
        Variant* pv = &node->mValue;
        if (pv->mFlags & 4)
            pv->Destruct(0);
        EASTL_dealloc(node);
    }
}

// =====================================================================
// 0x0068a870  cCommandParameterSet::RemoveParameter
// =====================================================================
// @ 0x0068a870
void cCommandParameterSet::RemoveParameter(u32 id) {
    VIter it = mParameterMap.find(id);
    VMapNode* node = it.mpNode;
    if (node != mParameterMap.endNode()) {
        mParameterMap.mnSize -= 1;
        RBTreeIncrement(node);
        RBTreeErase(node, &mParameterMap.aRight);
        if (node->mValue.mFlags & 4)
            node->mValue.Destruct(0);
        EASTL_dealloc(node);
    }
}

// =====================================================================
// 0x0068a8d0  cStringCommandGenerator::~cStringCommandGenerator
// =====================================================================
// @ 0x0068a8d0
cStringCommandGenerator::~cStringCommandGenerator() {
    vtbl0 = &vtbl_cStringCommandGenerator;
    vtbl1 = &vtbl_cStringCommandGenerator2;
    if (mpEmptySet) {
        ((void(__thiscall*)(void*))VFN(mpEmptySet, 4))(mpEmptySet);
    }
    ((void(__thiscall*)(void*, void*, void*))VecDestroyValues)(&mArrBegin, mArrBegin, mArrEnd);
    if (mArrBegin && *(int*)((char*)mArrBegin - 4) != 0)
        EASTL_dealloc(mArrBegin);
    vtbl1 = &vtbl_Base1;
    vtbl0 = &vtbl_Base0;
}

// =====================================================================
// 0x0068a970  cCommandServer::RegisterCommandParameterInfo
// =====================================================================
// @ 0x0068a970
bool cCommandServer::RegisterCommandParameterInfo(u32 id, const wch* param) {
    VMap* map = (VMap*)((char*)this + 4);
    CInfoNode* node = (CInfoNode*)map->find(id).mpNode;
    if (node == (CInfoNode*)&cmRight)
        return false;
    if (param && *param) {
        node->mValue.msParam.AssignCStr(param);
        return true;
    }
    if (mbAutoBasic) {
        node->mValue.msParam.Format(gLiteral1403384, node->mValue.msName.mpBegin);
    }
    return true;
}

// =====================================================================
// 0x0068a9e0  cCommandServer::GetCommandIDFromCommandString
// =====================================================================
struct WVec16L {   // vector<WStr>: 3 pointers, inline destructor
    WStr* mpBegin;
    WStr* mpEnd;
    WStr* mpEndCap;
    WVec16L(u32 n, const EmptyAlloc& a);                 // 0x0068A460 (thiscall, ret 8)
    void DoDestroyValues(WStr* first, WStr* last);       // 0x0084AAD0 (thiscall, ret 8)
    ~WVec16L() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EASTL_dealloc(mpBegin);
    }
};

// @ 0x0068a9e0
u32 cCommandServer::GetCommandIDFromCommandString(WStr* const str, int len) {
    if (str) {
        if (len == -1)
            len = (int)(str->mpEnd - str->mpBegin);
        const wch* b = str->mpBegin;
        WVec16L vec(1, *(const EmptyAlloc*)&str);
        if (ParseCmd((void*)b, len, 0x20, &vec, 0xffffffffu)) {
            const wch* first = vec.mpBegin->mpBegin;
            return ((ICmdSrv*)this)->GetCommandIDFromTokens(first);
        }
    }
    return 0;
}

// =====================================================================
// 0x0068aae0  cCommandServer::RegisterCommandGenerator
// =====================================================================
// @ 0x0068aae0
bool cCommandServer::RegisterCommandGenerator(void* gen) {
    if (gen)
        ((void(__thiscall*)(void*))VFN(gen, 0))(gen);
    VMap* set = (VMap*)((char*)this + 0x2c);
    CGenNode* genEnd = (CGenNode*)&csRight;
    CGenNode* node = (CGenNode*)set->find((u32)(size_t)gen).mpNode;
    if (node == genEnd) {
        struct GenIter { CGenNode* p; u32 flag; } out;
        ((void(__thiscall*)(VMap*, GenIter*, void*, unsigned))Sub68a140)(
            set, &out, &gen, (unsigned)(size_t)this);
        if (cmSize != 0) {
            CInfoNode* infoEnd = (CInfoNode*)&cmRight;
            for (CInfoNode* p = cmLeft; p != infoEnd; p = (CInfoNode*)RBTreeIncrement(p)) {
                ((void(__thiscall*)(cCommandServer*, void*, unsigned, void*))Sub689dc0)(
                    this, &p->mValue, 1, gen);
            }
        }
    }
    if (gen)
        ((void(__thiscall*)(void*))VFN(gen, 4))(gen);
    return true;
}

// =====================================================================
// 0x0068abb0  cCommandServer::UnregisterCommandGenerator
// =====================================================================
// @ 0x0068abb0
bool cCommandServer::UnregisterCommandGenerator(void* gen) {
    if (gen)
        ((void(__thiscall*)(void*))VFN(gen, 0))(gen);
    VMap* set = (VMap*)((char*)this + 0x2c);
    CGenNode* endNode = (CGenNode*)&csRight;
    CGenNode* node = (CGenNode*)set->find((u32)(size_t)gen).mpNode;
    if (node != endNode) {
        set->mnSize -= 1;
        RBTreeIncrement(node);
        RBTreeErase(node, &set->aRight);
        if (node->mValue)
            ((void(__thiscall*)(void*))VFN(node->mValue, 4))(node->mValue);
        EASTL_dealloc(node);
    }
    if (gen)
        ((void(__thiscall*)(void*))VFN(gen, 4))(gen);
    return true;
}

// =====================================================================
// 0x0068ac60  cCommandServer::ExecuteCommandFormatted
// =====================================================================
// @ 0x0068ac60
int cCommandServer::ExecuteCommandFormatted(const wch* fmt, ...) {
    WStr s;
    s.Format(*(const wch**)fmt, (void*)((char*)&fmt + 4));
    if (s.mpBegin != s.mpEnd) {
        int r = ((int(__thiscall*)(cCommandServer*, WStr*))VFN(this, 0x50))(this, &s);
        if (s.mpBegin && (((unsigned)((char*)s.mpEndCap - (char*)s.mpBegin)) & 0xfffffffeu) > 2u)
            EASTL_dealloc(s.mpBegin);
        return r;
    }
    if (s.mpBegin && (((unsigned)((char*)s.mpEndCap - (char*)s.mpBegin)) & 0xfffffffeu) > 2u)
        EASTL_dealloc(s.mpBegin);
    return 2;
}

// =====================================================================
// 0x0068ad30  App::cCommandParameterSet::cCommandParameterSet
// =====================================================================
// @ 0x0068ad30
cCommandParameterSet::cCommandParameterSet() {
    vtbl1 = &vtbl_Base1;
    mRefCount = 0;
    vtbl0 = &vtbl_cCommandParameterSet;
    vtbl1 = &vtbl_cCommandParameterSet2;
    mParameterMap.aLeft = 0;
    mParameterMap.aParent = 0;
    mParameterMap.aColorWord = 0;
    mParameterMap.aRight = (VMapNode*)&mParameterMap.aRight;
    mParameterMap.aLeft = (VMapNode*)&mParameterMap.aRight;
    mParameterMap.aParent = 0;
    mParameterMap.aColor = 0;
    mParameterMap.mnSize = 0;
    mDefaultVariant.mFlags = 0;
    mDefaultVariant.mTypeId = 0;
}

// =====================================================================
// 0x0068ad90  cCommandParameterSet::ExecuteCommand
// =====================================================================
// @ 0x0068ad90
bool cCommandParameterSet::ExecuteCommand(int cmd, void* a, void* b) {
    if (cmd == -2) {
        for (VMapNode* p = mParameterMap.aLeft; p != mParameterMap.endNode();
             p = (VMapNode*)RBTreeIncrement(p)) {
            if (((bool(__thiscall*)(cCommandParameterSet*, u32, void*, void*))VFN(this, 0x30))(
                    this, p->mKey, a, b))
                return true;
        }
        return false;
    }
    void* v = ((void*(__thiscall*)(cCommandParameterSet*, int))VFN(this, 0x1c))(this, cmd);
    if (!v)
        return false;
    Variant var;
    ((Variant*(__thiscall*)(Variant*, void*))Sub689e80)(&var, v);
    void* chosen;
    if (var.mTypeId == 0x13 || var.mTypeId == 0x10) {
        if (var.mFlags & 0x30)
            chosen = (void*)(size_t)var.raw0;
        else
            chosen = (var.mTypeId != 0) ? (void*)&var : 0;
    } else {
        chosen = FUN_0068a2e0();
    }
    int r;
    if (((char)(size_t)b) == 0) {
        WStr tmp;
        ((WStr*)chosen)->MakeLower();
        tmp.RangeInit(((WStr*)a)->mpBegin, ((WStr*)a)->mpEnd);
        tmp.MakeLower();
        r = MakeLocaleAvailable(chosen, &tmp);
        tmp.~WStr();
    } else {
        r = MakeLocaleAvailable(chosen, a);
    }
    if (var.mFlags & 4)
        var.Destruct(0);
    return r != 0;
}

// =====================================================================
// 0x0068af10  App::cStringCommandGenerator::cStringCommandGenerator
// =====================================================================
// @ 0x0068af10
cStringCommandGenerator::cStringCommandGenerator() {
    vtbl1 = &vtbl_Base1;
    mRefCount = 0;
    vtbl0 = &vtbl_cStringCommandGenerator;
    vtbl1 = &vtbl_cStringCommandGenerator2;
    mArrBegin = 0;
    mArrEnd = 0;
    mArrCap = 0;
    cCommandParameterSet* p = (cCommandParameterSet*)EASTL_alloc6(
        0x3c, "App/cCommandParameterSet", 0, 0, 0, 0);
    if (p) {
        new (p) cCommandParameterSet();
    }
    mpEmptySet = p;
    if (p)
        ((void(__thiscall*)(cCommandParameterSet*))VFN(p, 0))(p);
}

// =====================================================================
// 0x0068b000  cStringCommandGenerator::SetParameterCount (this+0xc is the token vector)
// =====================================================================
// @ 0x0068b000
bool cStringCommandGenerator::SetParameterCount(WStr* str, u32* outId, cCommandParameterSet** outSet) {
    ICmdSrv* srv = (ICmdSrv*)gCommandServer;
    if (srv) {
        const wch* b = str->mpBegin;
        int len = (int)(str->mpEnd - b);
        u32 n = ParseCmd((void*)b, len, 0x20, &mArrBegin, 0xffffffffu);
        if (n >= 1) {
            const wch* first = mArrBegin->mpBegin;
            u32 id = srv->GetCommandIDFromTokens(first);
            *outId = id;
            if (id) {
                cCommandParameterSet* p = new ("App/cCommandParameterSet", 0, 0, 0, 0) cCommandParameterSet();
                *outSet = p;
                ((IParamSetV*)p)->AddRef();
                for (u32 i = 1; i < n; i++) {
                    VariantL var(0x13, 9, (int)((char*)mArrBegin + i * 0x10), 0x10, 1);
                    ((IParamSetV*)*outSet)->SetParameter(i - 1, &var);
                }
                return true;
            }
        }
    }
    return false;
}
