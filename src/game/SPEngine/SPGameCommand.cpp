// src/game/SPEngine/SPGameCommand.cpp -- migrated from slice(s) s0068b150, s00689ee0, s00688dd0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGameCommand.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCommandParameterSet.h"
#include "SP/cStringCommandGenerator.h"
#include "SP/cCommandServer.h"
#include "EA/Variant.h"
#include <string.h>
#include <new>
#include "SP/cMessageCommandDispatcher.h"

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
extern "C" unsigned ParseCmd(void* s, int n, int ch, void* out, unsigned f); // 0x093d740
extern "C" int   MakeLocaleAvailable(void* a, void* b);                      // 0x087d9a0
extern "C" void  VecDestroyValues(void* first, void* last);                  // 0x084aad0
extern "C" void  Sub689dc0(void* a, int b, void* c);                         // 0x0689dc0
extern "C" void  Sub689e80(void* a);                                         // 0x0689e80
extern "C" void  Sub68a140(void* a, void* b, void* c);                       // 0x068a140
extern "C" char gAllocTag[];               // 0x13ebc58 "App"
extern "C" char gEASTLFile[];              // 0x13ebb38 allocator.h path
extern "C" void* gCommandServer;           // 0x15ff660
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
void* operator new(size_t sz, const char* name, unsigned a, unsigned b, const char* file, unsigned line);   // 0x0f473a0
extern "C" int   WMemCmp(const wch* a, const wch* b, unsigned n);            // 0x0572930
struct WStr;
struct EmptyAlloc {};
void __cdecl Ins16(void* a, void* b, const WStr& c, const EmptyAlloc& d);                  // 0x0555c40
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
struct VariantL : Variant {
    VariantL() { mFlags = 0; mTypeId = 0; }
    VariantL(int a, int b, int c, int d, int e) { mFlags = 0; mTypeId = 0; Init(a, b, c, d, e); }
    ~VariantL() { if (mFlags & 4) Destruct(0); }
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
struct ICmdSrv {   // cCommandServer interface (vtable slot +0x34)
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual u32 GetCommandIDFromTokens(const wch* first);   // +0x34
};
struct IParamSetV {   // cCommandParameterSet virtual interface
    virtual void AddRef();                                  // +0x00
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
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
void* operator new(size_t, const char* name, unsigned a, unsigned b,
                   const char* file, unsigned line);
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
extern "C" wch  gLiteral1403384[];         // 0x1403384 format literal
// ---- items of slice s00689ee0 end

// ---- items of slice s0068b150 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  __cdecl atexit(void(__cdecl* )());                           // 0x011E07EF (E8)
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
typedef unsigned char  uint8;
void  EAFree(void* p);                                                       // 0x00F47380 cdecl
void* EAAllocate(unsigned n, const char* name, int a, int b, const char* f, int l); // 0x00F473A0 cdecl
void* FUN_0068A2E0();                        // 0x0068A2E0 cdecl
void  FUN_00689EE0(void* out);               // 0x00689EE0 thiscall(out)
void  FUN_0068A000(void* out);               // 0x0068A000 thiscall(out)
void  FUN_00689DC0(void* p, int a, int b);   // 0x00689DC0 thiscall(p,a,b)
void  FUN_00D167E0();                        // 0x00D167E0 cdecl
void* operator new(unsigned int, void*);
struct WStr_s0068_b150 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void*    mAllocator;

    WStr_s0068_b150() { mpBegin = &gEmptyW; mpEnd = &gEmptyW; mpCapacity = &gEmptyWEnd; }
    ~WStr_s0068_b150() { if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin) EAFree(mpBegin); }
    WStr_s0068_b150(const wchar_t* s);                                   // 0x0056E2D0
    WStr_s0068_b150& operator=(const WStr_s0068_b150& x)
    {
        if (this != &x)
            Assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    WStr_s0068_b150& operator=(const wchar_t* s);                        // 0x005C3D90
    WStr_s0068_b150& Assign(const wchar_t* b, const wchar_t* e);         // 0x00423650
    WStr_s0068_b150& Append(const wchar_t* b, const wchar_t* e);         // 0x00429580
    void  Resize(unsigned n);                                 // 0x00429520
    void  push_back(unsigned c);                              // 0x004F6510
};
struct Variant_s0068_b150 {
    char           mGeneric[0x10];
    unsigned short mFlags;    // +0x10
    unsigned short mTypeId;   // +0x12

    Variant_s0068_b150& operator=(unsigned v);                           // 0x00542B80
    void     Destruct(int b);                                 // 0x0093DB80
    void     CtorFromValue(unsigned v);                       // 0x00689E80
};
struct IRefCounted {
    virtual void AddRef() {}        // slot 0
    virtual void Release() {}       // slot 1
    virtual void s2();
    virtual void s3();
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
    ~AutoRefCount() { if (mpObject) ((IRefCounted*)mpObject)->Release(); }
    T* operator=(T* p)
    {
        T* old = mpObject;
        if (p != old) {
            if (p)
                ((IRefCounted*)p)->AddRef();
            mpObject = p;
            if (old)
                ((IRefCounted*)old)->Release();
        }
        return p;
    }
};
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
    void* Insert(void* a, void* b, void* c);          // 0x0068BB50 (extern)
    __forceinline void reset()
    {
        mAnchor.mpRight  = &mAnchor;
        mAnchor.mpLeft   = &mAnchor;
        mAnchor.mpParent = 0;
        mAnchor.mColor   = 0;
        mnSize           = 0;
    }
};
struct CmdInfoNode {
    RbNode  mBase;        // +0x00
    uint32  mKey;         // +0x10
    uint32  mnID;         // +0x14
    WStr_s0068_b150    msName;       // +0x18
    WStr_s0068_b150    msTypeInfo;   // +0x28
};
struct VarMapNode {
    RbNode  mBase;      // +0x00
    uint32  mKey;       // +0x10
    Variant_s0068_b150 mValue;     // +0x14
};
struct VarMap : RbTreeBase {
    Variant_s0068_b150* GetPos(uint32* key);                             // 0x0068BF20 (below)
};
class cCommandParameterSet_s0068_b150 {
public:
    void*   mVt0;         // +0x00
    void*   mVt4;         // +0x04
    void*   m08;
    VarMap  mParams;      // +0x0c (0x18 bytes)
    char    m24[0x14];    // +0x24 .. +0x38
    uint16  m38;
    uint16  m3A;

    void* operator new(unsigned s) { return EAAllocate(s, "App/cCommandParameterSet", 0, 0, 0, 0); }
    cCommandParameterSet_s0068_b150()
    {
        mVt4 = &gVtCpsBase2;
        m08  = 0;
        mVt0 = &gVtCpsPri;
        mVt4 = &gVtCpsSec;
        mParams.reset();
        m38 = 0;
        m3A = 0;
    }
    void SetParameter(uint32 id, uint32 value);   // 0x0068C020
    bool CompareParameterString(WStr_s0068_b150* out);       // 0x0068B370
};
struct ICommandParamSetVt {
    virtual void AddRef();       // slot 0
    virtual void Release();      // slot 1
    virtual void s2();
    virtual void s3();
};
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
class cStringCommandGenerator_s0068_b150 : public IRefCounted {
public:
    uint32_t mBase[8];   // +0x04..+0x24
    cStringCommandGenerator_s0068_b150();                  // 0x0068AF10 (defined elsewhere)
    void* operator new(unsigned s) { return EAAllocate(s, "App/cStringCommandGenerator", 0, 0, 0, 0); }
    void ProcessToken(WStr_s0068_b150* a, WStr_s0068_b150* b);        // 0x0068A320
    bool ConvertCommandToString(int pCmd, IParamSet* pSet, WStr_s0068_b150* out);  // 0x0068B150
};
class cMessageCommandDispatcher : public IRefCounted {
public:
    uint32_t mBase[0x11];  // +0x04..+0x48
    cMessageCommandDispatcher();                // 0x00689D40 (defined elsewhere)
    void* operator new(unsigned s) { return EAAllocate(s, "App/cMessageCommandDispatcher", 0, 0, 0, 0); }
};
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
    virtual void RegisterCmd(unsigned id, const wchar_t* name, void* p); // slot 9 (+0x24)
    virtual void i10();
    virtual void i11();
    virtual bool ProcessCommand(int pCmd, WStr_s0068_b150* out, int b); // slot 12 (+0x30)
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
class cCommandServer_s0068_b150 : public ICommandServerVt {
public:
    struct CmdMap : RbTreeBase {
        void  DestroyNodes(RbNode* node);              // 0x0068B9D0
        void  DestroyNode(RbNode* node, void** itOut); // 0x0068B950
        ~CmdMap() { DestroyNodes(mAnchor.mpParent); }
    };
    struct GenSet : RbTreeBase {
        ~GenSet() { DoNuke(mAnchor.mpParent); }
    };

    CmdMap                 mCommandInfoMap;             // +0x04
    AutoRefCount<IRefCounted>               m1cRef;                     // +0x1c
    AutoRefCount<IRefCounted>               mpCommandDispatcher;        // +0x20
    AutoRefCount<cMessageCommandDispatcher> mpMessageCommandDispatcher; // +0x24
    AutoRefCount<cStringCommandGenerator_s0068_b150>   mpStringCommandGenerator;   // +0x28
    GenSet                 mCommandGeneratorSet;        // +0x2c
    bool                   mb48;                        // +0x48

    bool Shutdown();                                    // 0x0068BCF0
    bool InitDispatchers();                              // 0x0068B760
    cCommandServer_s0068_b150();                                   // 0x0068C040
    ~cCommandServer_s0068_b150();                                  // 0x0068BC50
    bool RegisterCommand(uint32 id, const wchar_t* name, void* p3); // 0x0068BDA0
    bool UnregisterCommand(uint32 id);                  // 0x0068BEC0
    void EnumerateCommands(UintVec& out);               // 0x0068B900
};
cCommandServer_s0068_b150* gpCommandServer;   // 0x015FF660
struct GenOwner {
    char pad0[0x38];
    AutoRefCount<cCommandParameterSet_s0068_b150>    mParams0;    // +0x38
    AutoRefCount<cCommandParameterSet_s0068_b150>    mParams1;    // +0x3c
    AutoRefCount<cStringCommandGenerator_s0068_b150> mGenerator;  // +0x40
    char m44[4];

    bool InitGenerators();               // 0x0068B5B0
};
// ---- items of slice s0068b150 end

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
    SP::cICommandDispatcher* old = *(SP::cICommandDispatcher* volatile*)&mpCommandDispatcher.mpObject;
    if (p != old) {
        if (p != 0)
            p->AddRef();
        mpCommandDispatcher.mpObject = p;
        if (old != 0)
            old->Release();
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

// @ 0x0068a250
extern "C" VMapNode* __stdcall FUN_0068a250(const PairUV* src)
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
extern "C" void __stdcall FUN_0068a320(WStr* src, WStr* dst)
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

// @ 0x0068a460
vector::vector(u32 n, const EmptyAlloc& a)
: VBase16(n, a) {
    const WStr tmp;
    Ins16(mpBegin, (void*)n, tmp, a);
    mpEnd = (WStr*)((char*)mpBegin + n * 0x10);
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

// @ 0x0068a7a0
void cCommandParameterSet::AdjustParameterCount(u32 n)
{
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
    ((void(__thiscall*)(void*, void*, void*))VecDestroyValues)(&mArrBegin, mArrBegin, mArrEnd);
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

// @ 0x0068a9e0
unsigned int SP::cCommandServer::GetCommandIDFromCommandString(eastl::basic_string<wchar_t, eastl::allocator> const * str, unsigned int len) const
{
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

// @ 0x0068aae0
bool cCommandServer::RegisterCommandGenerator(void* gen)
{
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

// @ 0x0068ad30
cCommandParameterSet::cCommandParameterSet()
{
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

// @ 0x0068b000
bool cStringCommandGenerator::SetParameterCount(WStr* str, u32* outId, cCommandParameterSet** outSet)
{
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

// @ 0x0068b150
bool cStringCommandGenerator_s0068_b150::ConvertCommandToString(int pCmd, IParamSet* pSet, WStr_s0068_b150* out)
{
    if (out->mpBegin != out->mpEnd) {
        *(uint16*)out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    if (gpCommandServer == 0)
        return false;

    WStr_s0068_b150 local;
    if (!gpCommandServer->ProcessCommand(pCmd, &local, 0))
        return false;

    ProcessToken(&local, &local);
    out->Append(local.mpBegin, local.mpEnd);

    if (pSet) {
        for (int idx = pSet->First(); idx != -1; idx = pSet->Next(idx)) {
            unsigned v = (unsigned)pSet->GetValue(idx);
            Variant_s0068_b150 temp;
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

            local = WStr_s0068_b150(s);
            ProcessToken(&local, &local);
            out->push_back(' ');
            out->Append(local.mpBegin, local.mpEnd);
            if (temp.mFlags & 4)
                temp.Destruct(0);
        }
    }
    return true;
}

// @ 0x0068b370
bool cCommandParameterSet_s0068_b150::CompareParameterString(WStr_s0068_b150* out)
{
    out->Resize(0);
    WStr_s0068_b150 local;

    RbNode* it  = mParams.mAnchor.mpLeft;
    RbNode* end = &mParams.mAnchor;
    for (; it != end; it = (RbNode*)RbTreeIncrement(it)) {
        unsigned v = ((VarMapNode*)it)->mKey;
        Variant_s0068_b150 temp;
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

        local = WStr_s0068_b150(s);
        out->Append(local.mpBegin, local.mpEnd);
        if (temp.mFlags & 4)
            temp.Destruct(0);
    }
    return true;
}

// @ 0x0068b5b0
bool GenOwner::InitGenerators()
{
    if (mParams0.mpObject == 0) {
        cCommandParameterSet_s0068_b150* p = new cCommandParameterSet_s0068_b150();
        mParams0 = p;
    }
    if (mParams1.mpObject == 0) {
        cCommandParameterSet_s0068_b150* p = new cCommandParameterSet_s0068_b150();
        mParams1 = p;
    }
    if (mGenerator.mpObject == 0) {
        cStringCommandGenerator_s0068_b150* p = new cStringCommandGenerator_s0068_b150();
        mGenerator = p;
        if (mGenerator.mpObject)
            ((IRefCounted*)mGenerator.mpObject)->Init();
    }
    return true;
}

// @ 0x0068b760
bool cCommandServer_s0068_b150::InitDispatchers()
{
    if (!HasSet()) {
        cMessageCommandDispatcher* d = new cMessageCommandDispatcher();
        mpMessageCommandDispatcher = d;
        if (mpMessageCommandDispatcher.mpObject)
            ((IRefCounted*)mpMessageCommandDispatcher.mpObject)->Init();
        SetDispatcher((IRefCounted*)mpMessageCommandDispatcher.mpObject);
    }
    {
        cStringCommandGenerator_s0068_b150* g = new cStringCommandGenerator_s0068_b150();
        mpStringCommandGenerator = g;
        if (mpStringCommandGenerator.mpObject)
            ((IRefCounted*)mpStringCommandGenerator.mpObject)->Init();
        SetGenerator((IRefCounted*)mpStringCommandGenerator.mpObject);
    }
    return true;
}

// @ 0x0068b880
void __stdcall CreateParameterSet(cCommandParameterSet_s0068_b150** out)
{
    cCommandParameterSet_s0068_b150* p = new cCommandParameterSet_s0068_b150();
    *out = p;
    ((ICommandParamSetVt*)p)->AddRef();
}

// @ 0x0068b900
void cCommandServer_s0068_b150::EnumerateCommands(UintVec& out)
{
    RbNode* it  = mCommandInfoMap.mAnchor.mpLeft;
    RbNode* end = &mCommandInfoMap.mAnchor;
    if (it != end) {
        do {
            unsigned v = ((CmdInfoNode*)it)->mKey;
            out.push_back(v);
            it = (RbNode*)RbTreeIncrement(it);
        } while (it != end);
    }
}

// @ 0x0068b950
void cCommandServer_s0068_b150::CmdMap::DestroyNode(RbNode* node, void** itOut)
{
    --mnSize;
    RbNode* next = (RbNode*)RbTreeIncrement(node);
    RbTreeErase(node, &mAnchor);
    ((CmdInfoNode*)node)->msTypeInfo.~WStr_s0068_b150();
    ((CmdInfoNode*)node)->msName.~WStr_s0068_b150();
    EAFree(node);
    *itOut = next;
}

// @ 0x0068b9d0
void cCommandServer_s0068_b150::CmdMap::DestroyNodes(RbNode* node)
{
    while (node) {
        DestroyNodes(node->mpRight);
        RbNode* parent = node->mpLeft;
        ((CmdInfoNode*)node)->msTypeInfo.~WStr_s0068_b150();
        ((CmdInfoNode*)node)->msName.~WStr_s0068_b150();
        EAFree(node);
        node = parent;
    }
}

// @ 0x0068bc50
cCommandServer_s0068_b150::~cCommandServer_s0068_b150()
{
    *(void**)this = &gVtCmdSrv;
    mCommandGeneratorSet.~GenSet();
    if (mpStringCommandGenerator.mpObject)
        ((IRefCounted*)mpStringCommandGenerator.mpObject)->Release();
    if (mpMessageCommandDispatcher.mpObject)
        ((IRefCounted*)mpMessageCommandDispatcher.mpObject)->Release();
    if (mpCommandDispatcher.mpObject)
        ((IRefCounted*)mpCommandDispatcher.mpObject)->Release();
    mCommandInfoMap.~CmdMap();
    *(void**)this = &gVtEditorRes;
}

// @ 0x0068bcf0
bool cCommandServer_s0068_b150::Shutdown()
{
    mCommandInfoMap.DestroyNodes(mCommandInfoMap.mAnchor.mpParent);
    mCommandInfoMap.reset();
    this->SetDispatcher(0);
    if (mpMessageCommandDispatcher.mpObject)
        ((IRefCounted*)mpMessageCommandDispatcher.mpObject)->Deinit();
    if (mpMessageCommandDispatcher.mpObject) {
        IRefCounted* old = (IRefCounted*)mpMessageCommandDispatcher.mpObject;
        mpMessageCommandDispatcher.mpObject = 0;
        old->Release();
    }
    if (mpStringCommandGenerator.mpObject)
        ((IRefCounted*)mpStringCommandGenerator.mpObject)->Deinit();
    if (mpStringCommandGenerator.mpObject) {
        IRefCounted* old = (IRefCounted*)mpStringCommandGenerator.mpObject;
        mpStringCommandGenerator.mpObject = 0;
        old->Release();
    }
    for (RbNode* it = mCommandGeneratorSet.mAnchor.mpLeft;
         it != &mCommandGeneratorSet.mAnchor; it = (RbNode*)RbTreeIncrement(it)) {
    }
    mCommandGeneratorSet.DoNuke(mCommandGeneratorSet.mAnchor.mpParent);
    mCommandGeneratorSet.reset();
    return true;
}

// @ 0x0068bda0
bool cCommandServer_s0068_b150::RegisterCommand(uint32 id, const wchar_t* name, void* p3)
{
    (void)p3;
    if (id == 0 || name == 0)
        return false;
    void* it;
    mCommandInfoMap.Find(&it, &id);
    if (*(RbNode**)it != &mCommandInfoMap.mAnchor)
        return false;

    WStr_s0068_b150 a;
    WStr_s0068_b150 b;
    FUN_00689EE0(&a);
    FUN_0068A000(&b);
    void* nodeOut = 0;
    mCommandInfoMap.Insert(&nodeOut, &b, &a);
    CmdInfoNode* node = (CmdInfoNode*)nodeOut;
    node->mnID = id;
    node->msName = name;
    this->RegisterCmd(id, name, p3);
    FUN_00689DC0(&node->mnID, 1, 0);
    FUN_00D167E0();
    return true;
}

// @ 0x0068bec0
bool cCommandServer_s0068_b150::UnregisterCommand(uint32 id)
{
    RbNode* it;
    mCommandInfoMap.Find(&it, &id);
    if (it == &mCommandInfoMap.mAnchor)
        return false;
    FUN_00689DC0(&((CmdInfoNode*)it)->mnID, 0, 0);
    RbNode* next;
    mCommandInfoMap.DestroyNode(it, (void**)&next);
    return true;
}

// @ 0x0068bf20
__declspec(noinline) Variant_s0068_b150* VarMap::GetPos(uint32* key)
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
        Variant_s0068_b150 v1;
        v1.mFlags  = 0;
        v1.mTypeId = 0;
        *(uint32*)&v1.mGeneric[0] = *key;
        Variant_s0068_b150 v2;
        v2.mFlags  = 0;
        v2.mTypeId = 0;
        v2 = *(uint32*)key;
        y = (RbNode*)Insert(y, key, &v2);
        if (v2.mFlags & 4)
            v2.Destruct(0);
        if (v1.mFlags & 4)
            v1.Destruct(0);
    }
    return (Variant_s0068_b150*)((char*)y + 0x14);
}

// @ 0x0068c020
void cCommandParameterSet_s0068_b150::SetParameter(uint32 id, uint32 value)
{
    Variant_s0068_b150* slot = mParams.GetPos(&id);
    *slot = value;
}

// @ 0x0068c040
cCommandServer_s0068_b150::cCommandServer_s0068_b150()
{
    *(void**)this = &gVtCmdSrv;
    mCommandInfoMap.reset();
    m1cRef.mpObject = 0;
    mpCommandDispatcher.mpObject = 0;
    mpMessageCommandDispatcher.mpObject = 0;
    mpStringCommandGenerator.mpObject = 0;
    {
        RbNode* a = &mCommandGeneratorSet.mAnchor;
        a->mpRight = a;
        a->mpLeft  = a;
        a->mpParent = 0;
        a->mColor  = 0;
        mCommandGeneratorSet.mnSize = 0;
    }
    mb48 = false;
}
