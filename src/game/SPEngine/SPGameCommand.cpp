// src/game/SPEngine/SPGameCommand.cpp -- migrated from slice(s) s00689ee0, s00688dd0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGameCommand.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCommandParameterSet.h"
#include "SP/cStringCommandGenerator.h"
#include "SP/cCommandServer.h"
#include "EA/Variant.h"
#include <string.h>
#include <new>

// ---- items of slice s00688dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint32;
typedef unsigned short uint16;
void* RBTreeDecrement(void* node);   // 0x009215c0 cdecl
void* RBTreeIncrement(void* node);   // 0x00921580 cdecl
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
struct DispShutdown {
    void* vtbl;
    bool  Shutdown();
};
struct DispTeardown {
    void* vtbl;
    bool  Teardown();
};
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
struct ParamWalker {
    void* vtbl;
    bool  Walk(char* node, uint32 flags, void* sink);
};
struct EditorResBase {
    virtual ~EditorResBase() {}
    virtual void er1();
};
struct EditorResDerived : EditorResBase {
    char  pad[0x1c];
    void* m20;   // +0x20
    void* m24;   // +0x24
    ~EditorResDerived();
};
// ---- items of slice s00688dd0 end

// ---- items of slice s00689ee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* MemcpyT(void* dst, const void* src, unsigned n);            // 0x011e0744 memcpy thunk
extern "C" void  EASTL_dealloc(void* p);                                     // 0x0f47380
extern "C" void* EASTL_alloc6(unsigned sz, const char* name, unsigned a,
                              unsigned b, const char* file, unsigned line);  // 0x0f473a0
extern "C" void  RBTreeErase(void* node, void* anchor);                      // 0x0921880
extern "C" int   MakeLocaleAvailable(void* a, void* b);                      // 0x087d9a0
extern "C" void  VecDestroyValues(void* first, void* last);                  // 0x084aad0
extern "C" void  Sub689dc0(void* a, int b, void* c);                         // 0x0689dc0
extern "C" void  Sub689e80(void* a);                                         // 0x0689e80
extern "C" void  Sub68a140(void* a, void* b, void* c);                       // 0x068a140
extern "C" char gAllocTag[];               // 0x13ebc58 "App"
extern "C" char gEASTLFile[];              // 0x13ebb38 allocator.h path
extern "C" void* vtbl_cCommandParameterSet;   // 0x1403310
extern "C" void* vtbl_cCommandParameterSet2;  // 0x140330c
extern "C" void* vtbl_cStringCommandGenerator; // 0x1403354
extern "C" void* vtbl_cStringCommandGenerator2;// 0x1403350
extern "C" void* vtbl_Base1;               // 0x13ef094
extern "C" void* vtbl_Base0;               // 0x13eb938
#define VFN(p, off) ((*(void***)(p))[(off) / 4])
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef wchar_t        wch;
extern "C" int   WMemCmp(const wch* a, const wch* b, unsigned n);            // 0x0572930
extern "C" wch  gEmptyWStr[];              // 0x1667bac empty string buffer
extern "C" wch  gLiteral1403308[];         // 0x1403308 wide literal
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
struct Variant {
    u32 raw0, raw1, raw2, raw3;   // +0x00
    u16 mFlags;                   // +0x10
    u16 mTypeId;                  // +0x12

    void Assign(const void* src);                       // 0x0542b80 (thiscall)
    void Destruct(int b);                               // 0x093db80 (thiscall)
    void Init(int a, int b, int c, int d, int e);       // 0x093dd80 (thiscall)
};
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
    u8 aColor;               // +0x10
    u8 pad1[3];
    u32 mnSize;              // +0x14
    u32 mAlloc;              // +0x18

    VMapNode* endNode() { return (VMapNode*)&aRight; }
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
struct cCommandParameterSet {
    void* vtbl0;             // +0x00
    void* vtbl1;             // +0x04
    u32 mRefCount;           // +0x08
    VMap mParameterMap;      // +0x0c
    Variant mDefaultVariant; // +0x28

    cCommandParameterSet();
    ~cCommandParameterSet();
    u32 GetNextParameterID(u32 id);
    void RemoveParameter(u32 id);
    void AdjustParameterCount(u32 n);
    bool ExecuteCommand(int cmd, void* a, void* b);
    bool SetParameterCount(void* a, void* b, void* out);
};
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
};
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
    u32  GetCommandIDFromCommandString(WStr* str, int len);
    bool RegisterCommandGenerator(void* gen);
    bool UnregisterCommandGenerator(void* gen);
    int  ExecuteCommandFormatted(const wch* fmt, ...);
};
void* operator new(size_t, const char* name, unsigned a, unsigned b,
                   const char* file, unsigned line);
extern "C" wch  gLiteral1403384[];         // 0x1403384 format literal
// ---- items of slice s00689ee0 end

// @ 0x006895f0
bool SP::cCommandParameterSet::ValidateParameter(unsigned int a, unsigned int b)
{
    if (((int(__thiscall*)(void*, uint32))(*(void***)this)[0x1c / 4])(this, a) != 0 &&
        b == 0xff)
        return true;
    return false;
}


// @ 0x006896a0
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


// @ 0x006896f0
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


// @ 0x00689730
bool SP::cStringCommandGenerator::Shutdown()
{
    void* p = mpEmptyParameterSetOutput.mpObject;
    if (p != 0) {
        mpEmptyParameterSetOutput.mpObject = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    return true;
}


// @ 0x00689810
EditorResDerived::~EditorResDerived()
{
    if (m24 != 0)
        ((void(__thiscall*)(void*))(*(void***)m24)[1])(m24);
    if (m20 != 0)
        ((void(__thiscall*)(void*))(*(void***)m20)[1])(m20);
}


// @ 0x00689920
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


// @ 0x00689980
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


// @ 0x00689b00
bool SP::cCommandServer::SetCommandDispatcher(SP::cICommandDispatcher * p)
{
    if (mpCommandDispatcher.mpObject == p)
        return true;
    void* old = *(void* volatile*)((char*)this + 0x20);
    if (p != old) {
        if (p != 0)
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
        mpCommandDispatcher.mpObject = p;
        if (old != 0)
            ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }
    return true;
}


// @ 0x00689b40
int SP::cCommandServer::ExecuteCommand(unsigned int a, SP::cICommandParameterSet * b, SP::cICommandParameterSet * c)
{
    uint32 c_v = (uint32)c;
    uint32 b_v = (uint32)b;
    void* p = mpCommandDispatcher.mpObject;
    if (p != 0)
        return ((int(__thiscall*)(void*, uint32, uint32, uint32))
            (*(void***)p)[0x1c / 4])(p, a, b_v, c_v);
    return 2;
}


// @ 0x00689b60
int SP::cCommandServer::ExecuteCommand(eastl::basic_string<wchar_t, eastl::allocator> const * a, SP::cICommandParameterSet * b)
{
    uint32 b_v = (uint32)b;
    uint32 a_v = (uint32)a;
    void* p = mpStringCommandGenerator.mpObject;
    if (p != 0)
        return ((int(__thiscall*)(void*, uint32, uint32))
            (*(void***)p)[0x20 / 4])(p, a_v, b_v);
    return 2;
}


// @ 0x00689be0
void* ParamSet::operator[](uint32 key)
{
    void* it;
    mMap.find(&it, key);
    if (it != (void*)((char*)this + 0x10))
        return (char*)it + 0x14;
    return (char*)this + 0x28;
}


// @ 0x00689c20
void* ParamSet::GetParameter(uint32 key)
{
    void* it;
    mMap.find(&it, key);
    if (it != (void*)((char*)this + 0x10))
        return (char*)it + 0x14;
    return 0;
}


// @ 0x00689c50
void ParamSet::AppendParameter(uint32 v)
{
    uint32 id = 0;
    if (mSize != 0)
        id = *(uint32*)((char*)RBTreeDecrement((char*)this + 0x10) + 0x10) + 1;
    ((void(__thiscall*)(void*, uint32, uint32))(*(void***)this)[0x20 / 4])(this, id, v);
}


// @ 0x00689d00
unsigned int SP::cCommandParameterSet::GetFirstParameterID() const
{
    if (mParameterMap.mnSize != 0)
        return *(uint32*)(*(char**)((char*)this + 0x14) + 0x10);
    return 0xffffffff;
}


// @ 0x00689dc0
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

// @ 0x00689ee0
cCommandInfo::cCommandInfo(const cCommandInfo& o)
: mnID(o.mnID), msName(o.msName), msParam(o.msParam) {}

// @ 0x00689fc0
u32 cCommandParameterSet::GetNextParameterID(u32 id)
{
    VMapNode* node = mParameterMap.find(id).mpNode;
    VMapNode* endNode = mParameterMap.endNode();
    if (node != endNode) {
        VMapNode* next = (VMapNode*)RBTreeIncrement(node);
        if (next != endNode)
            return next->mKey;
    }
    return 0xffffffffu;
}

// @ 0x0068a000
cCommandInfo::~cCommandInfo()
{}

// @ 0x0068a040
u32 cCommandServer::FindCommandInfoByName(const wch* name)
{
    CInfoNode* p = cmLeft;
    CInfoNode* endNode = (CInfoNode*)&cmRight;
    while (p != endNode) {
        const wch* nrl = p->mValue.msName.mpBegin;
        unsigned nlen = (unsigned)(p->mValue.msName.mpEnd - nrl);
        const wch* q = name;
        while (*q) q += 1;
        unsigned qlen = (unsigned)(q - name);
        unsigned mn = nlen < qlen ? nlen : qlen;
        int r = WMemCmp(nrl, name, mn);
        if (r == 0 && nlen == qlen)
            return p->mValue.mnID;
        p = (CInfoNode*)RBTreeIncrement(p);
    }
    return 0;
}

// @ 0x0068a250
extern "C" VMapNode* FUN_0068a250(const PairUV* src)
{
    return new (gAllocTag, 0u, 0u, gEASTLFile, 0xd1u) VMapNode(*src);
}

// @ 0x0068a2e0
extern "C" WStr* FUN_0068a2e0()
{
    static WStr s;
    return &s;
}

// @ 0x0068a320
extern "C" void FUN_0068a320(WStr* src, WStr* dst)
{
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

// @ 0x0068a3f0
bool cCommandServer::GetCommandInfo(u32 id, WStr* name, WStr* param)
{
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

// @ 0x0068a720
cCommandParameterSet::~cCommandParameterSet()
{
    vtbl0 = &vtbl_cCommandParameterSet;
    vtbl1 = &vtbl_cCommandParameterSet2;
    if (mDefaultVariant.mFlags & 4)
        mDefaultVariant.Destruct(0);
    mParameterMap.DoNukeSubtree(mParameterMap.aParent);
    vtbl1 = &vtbl_Base1;
    vtbl0 = &vtbl_Base0;
}

// @ 0x0068a870
void cCommandParameterSet::RemoveParameter(u32 id)
{
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

// @ 0x0068a8d0
cStringCommandGenerator::~cStringCommandGenerator()
{
    vtbl0 = &vtbl_cStringCommandGenerator;
    vtbl1 = &vtbl_cStringCommandGenerator2;
    if (mpEmptySet) {
        ((void(__thiscall*)(void*))VFN(mpEmptySet, 4))(mpEmptySet);
    }
    VecDestroyValues(mArrBegin, mArrEnd);
    if (mArrBegin && *(int*)((char*)mArrBegin - 4) != 0)
        EASTL_dealloc(mArrBegin);
    vtbl1 = &vtbl_Base1;
    vtbl0 = &vtbl_Base0;
}

// @ 0x0068a970
bool SP::cCommandServer::RegisterCommandParameterInfo(unsigned int id, wchar_t const * param)
{
    eastl::map<unsigned int,EA::Variant,eastl::less<unsigned int>,eastl::allocator>* map = (eastl::map<unsigned int,EA::Variant,eastl::less<unsigned int>,eastl::allocator>*)((char*)this + 4);
    CInfoNode* node = (CInfoNode*)map->find(id).mpNode;
    if (node == (CInfoNode*)&mCommandInfoMap.mAnchor.mpNodeRight)
        return false;
    if (param && *param) {
        node->mValue.msParam.AssignCStr(param);
        return true;
    }
    if (mbAutoBasicParameterInfoCreation) {
        node->mValue.msParam.Format(gLiteral1403384, node->mValue.msName.mpBegin);
    }
    return true;
}

// @ 0x0068aae0
bool cCommandServer::RegisterCommandGenerator(void* gen)
{
    if (gen)
        ((void(__thiscall*)(void*))VFN(gen, 0))(gen);
    VMap* set = (VMap*)((char*)this + 0x2c);
    CGenNode* endNode = (CGenNode*)&csRight;
    CGenNode* node = (CGenNode*)set->find((u32)(size_t)gen).mpNode;
    if (node == endNode) {
        void* v = 0;
        Sub68a140((char*)this + 0x2c, &gen, v);
        if (csSize != 0) {
            for (CGenNode* p = csLeft; p != endNode; p = (CGenNode*)RBTreeIncrement(p)) {
                Sub689dc0((char*)p + 0x14, 1, gen);
            }
        }
    }
    if (gen)
        ((void(__thiscall*)(void*))VFN(gen, 4))(gen);
    return true;
}

// @ 0x0068abb0
bool cCommandServer::UnregisterCommandGenerator(void* gen)
{
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

// @ 0x0068ac60
int cCommandServer::ExecuteCommandFormatted(const wch* fmt, ...)
{
    WStr s;
    s.Format(fmt, (void*)((char*)&fmt + 4));
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

// @ 0x0068ad30
cCommandParameterSet::cCommandParameterSet()
{
    vtbl1 = &vtbl_Base1;
    mRefCount = 0;
    vtbl0 = &vtbl_cCommandParameterSet;
    vtbl1 = &vtbl_cCommandParameterSet2;
    mParameterMap.aLeft = 0;
    mParameterMap.aParent = 0;
    mParameterMap.aColor = 0;
    mParameterMap.aRight = (VMapNode*)&mParameterMap.aRight;
    mParameterMap.aLeft = (VMapNode*)&mParameterMap.aRight;
    mParameterMap.aParent = 0;
    mParameterMap.aColor = 0;
    mParameterMap.mnSize = 0;
    mDefaultVariant.mFlags = 0;
    mDefaultVariant.mTypeId = 0;
}

// @ 0x0068ad90
bool cCommandParameterSet::ExecuteCommand(int cmd, void* a, void* b)
{
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
    Sub689e80(v);
    Variant var;
    var.mFlags = 0;
    var.mTypeId = 0;
    unsigned short type = ((Variant*)v)->mTypeId;
    void* chosen;
    if (type == 0x13 || type == 0x10) {
        if (((Variant*)v)->mFlags & 0x30)
            chosen = v;
        else
            chosen = (type != 0) ? v : 0;
    } else {
        chosen = FUN_0068a2e0();
    }
    int r;
    if (*(char*)b == 0) {
        WStr tmp;
        ((WStr*)v)->MakeLower();
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

// @ 0x0068af10
cStringCommandGenerator::cStringCommandGenerator()
{
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
