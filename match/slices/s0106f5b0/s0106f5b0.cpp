// Slice s0106f5b0 -- SP::cSPUISpace::~cSPUISpace (0x0106f5b0)
// Retail layout (cString is 0x14 bytes here; the 2008 PDB's 0x1c is not retail). Only members that have
// a destructor are modelled; plain data between them is padding. Members are declared in ascending
// offset order, so cl destroys them in the original reverse order by itself.
#include "types.h"

void operator_delete__(void* p);                         // 0x00f47380

// ---- intrusive pointer flavours (differ only in the vtable slot of Release) ----
struct IRel1 { virtual void v0(); virtual void Release(); };                // Release at +4
struct IRel2 { virtual void v0(); virtual void v1(); virtual void Release(); };  // Release at +8
struct IRelC0 {                                                              // Release at +0xc0
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void Release();
};
struct RefCounted {                                  // EA RefCountTemplate: vptr, count at +4, deleting dtor in slot 0
    virtual ~RefCounted();
    int mnRefCount;
    void Release()
    {
        int n = mnRefCount;
        mnRefCount = n - 1;
        n--;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
    }
};

struct Arc1 { IRel1* p; ~Arc1() { if (p) p->Release(); } };
struct Arc2 { IRel2* p; ~Arc2() { if (p) p->Release(); } };
struct ArcC0 { IRelC0* p; ~ArcC0() { if (p) p->Release(); } };
struct ArcRC { RefCounted* p; ~ArcRC() { if (p) p->Release(); } };

// sp_vector_allocator block: a header dword sits in front of the data
struct SpBlock { void* p; ~SpBlock() { if (p && ((int*)p)[-1] != 0) operator_delete__(p); } };
struct RawPtr  { void* p; ~RawPtr() { if (p) operator_delete__(p); } };

struct cString { uint32_t d[5]; ~cString(); };                        // 0x006b5240 (out of line)

struct StrVec {                                                        // eastl::vector<cString, sp_vector_allocator> (+ 1 dword)
    cString* mpBegin; cString* mpEnd; cString* mpCap; uint32_t alloc; uint32_t extra;
    ~StrVec()
    {
        cString* e = mpEnd;
        for (cString* it = mpBegin; it < e; ++it)
            it->~cString();
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};

// eastl::hashtable instances: bucket array (+4), bucket count (+8), element count (+0xc)
struct HashWStr {                                   // hashtable<wchar_t const*, ...>   DoFreeNodes at 0x00693230
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements;
    void DoFreeNodes(void** b, uint32_t n);
    ~HashWStr() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; if (mnBuckets > 1) operator_delete__(mpBuckets); }
};
struct HashB {                                      // hashtable at +0x2a0, free routine at 0x01068400
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements;
    void DoFreeNodes(void** b, uint32_t n);
    ~HashB() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; if (mnBuckets > 1) operator_delete__(mpBuckets); }
};
struct HashTool {                                   // hashtable<uint, pair<uint, AutoRefCount<cSPToolStrategy>>>   0x00961d60
    uint32_t pad0; void** mpBuckets; uint32_t mnBuckets; uint32_t mnElements;
    void DoFreeNodes(void** b, uint32_t n);
    ~HashTool() { DoFreeNodes(mpBuckets, mnBuckets); mnElements = 0; if (mnBuckets > 1) operator_delete__(mpBuckets); }
};

// out-of-line member destructors (callee addresses in the comments)
struct ObjE0A400 { uint32_t d[29]; ~ObjE0A400(); };   // 0x00e0a400
struct Obj4AA120 { uint32_t d[12]; ~Obj4AA120(); };   // 0x004aa120
struct Obj6CB90  { uint32_t d[14]; ~Obj6CB90(); }; // 0x0106cb90 (0x530..0x568)
struct Obj4B5440 { uint32_t d[5]; ~Obj4B5440(); }; // 0x004b5440
struct SharedLibVec { void* a; void* b; void* c; uint32_t alloc; ~SharedLibVec(); };  // 0x005c7f10

void EA_Messaging_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00571db0, cdecl
struct AutoHandler {
    void* mpHandler; uint32_t a, b, c, d;
    ~AutoHandler()
    {
        if (mpHandler) {
            void* h = mpHandler;
            mpHandler = 0;
            EA_Messaging_RemoveHandler(h, a, b, c, d);
        }
    }
};

// ---- base classes (vtable restore order in the epilogue: +0xc, +4, +0) ----
struct BaseRes   { virtual ~BaseRes() {} };                        // GmeEditorResBase-side vptr at +0
struct BaseCount { virtual ~BaseCount() {} int mnRefCount; };      // RefCountVTemplate<int> at +4
struct BaseMsg   { virtual ~BaseMsg() {} };                        // IMsgHandler at +0xc

struct UIMgrA; struct UIMgrB;
UIMgrA* FUN_0067de40();                                            // cdecl, no args
struct UIMgrB { virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
                virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
                virtual void Set(void* v); };                       // +0x20
struct UIMgrA { virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
                virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
                virtual UIMgrB* Get(); };                           // +0x20
struct DeletableObj { virtual ~DeletableObj(); };
extern void* g_16e0d08;                                             // 0x016e0d08

namespace SP {
struct cSPUISpace : BaseRes, BaseCount, BaseMsg {
    uint32_t     pad10[2];            // 0x10
    ArcC0        m018;                // 0x18
    cString      s01c,
                 s030,
                 s044,
                 s058,
                 s06c,
                 s080,
                 s094,
                 s0a8,
                 s0bc,
                 s0d0,
                 s0e4,
                 s0f8,
                 s10c,
                 s120,
                 s134,
                 s148,
                 s15c,
                 s170,
                 s184,
                 s198,
                 s1ac,
                 s1c0,
                 s1d4,
                 s1e8,
                 s1fc,
                 s210;   // 0x1c .. 0x210 (step 0x14)
    uint32_t     pad224;              // 0x224
    ArcRC        m228;                // 0x228
    Arc2         m22c, m230, m234;    // 0x22c
    Arc1         m238;                // 0x238
    uint32_t     pad23c;              // 0x23c
    SpBlock      m240;                // 0x240
    uint32_t     pad244[4];           // 0x244
    Arc2         m254, m258;          // 0x254
    HashTool     m25c;                // 0x25c
    uint32_t     pad26c[4];           // 0x26c
    RawPtr       m27c;                // 0x27c
    uint32_t     pad280[5];           // 0x280
    Arc1         m294, m298, m29c;    // 0x294
    HashB        m2a0;                // 0x2a0
    uint32_t     pad2b0[4];           // 0x2b0
    SpBlock      m2c0;                // 0x2c0
    uint32_t     pad2c4[4];           // 0x2c4
    HashWStr     m2d4;                // 0x2d4
    uint32_t     pad2e4[6];           // 0x2e4
    Arc1         m2fc, m300, m304;    // 0x2fc
    Obj4B5440    m308;                // 0x308
    Arc1         m31c;                // 0x31c
    uint32_t     pad320;              // 0x320
    cString      s324,
                 s338,
                 s34c,
                 s360,
                 s374,
                 s388,
                 s39c,
                 s3b0,
                 s3c4,
                 s3d8,
                 s3ec,
                 s400,
                 s414,
                 s428,
                 s43c,
                 s450,
                 s464,
                 s478,
                 s48c,
                 s4a0,
                 s4b4,
                 s4c8,
                 s4dc,
                 s4f0;   // 0x324 .. 0x4f0 (step 0x14)
    StrVec       v504;                // 0x504
    StrVec       v518;                // 0x518
    uint32_t     pad52c;              // 0x52c
    Obj6CB90     m530;                // 0x530
    DeletableObj* mp568;              // 0x568
    AutoHandler  m56c;                // 0x56c
    Arc1         m580;                // 0x580
    ArcC0        m584;                // 0x584
    Arc1         m588, m58c, m590, m594, m598, m59c, m5a0, m5a4;   // 0x588
    ArcRC        m5a8;                // 0x5a8
    Arc1         m5ac, m5b0, m5b4;    // 0x5ac
    uint32_t     pad5b8[2];           // 0x5b8
    Arc1         m5c0, m5c4;          // 0x5c0
    uint32_t     pad5c8[4];           // 0x5c8
    SpBlock      m5d8;                // 0x5d8
    uint32_t     pad5dc[4];           // 0x5dc
    Obj4AA120    m5ec;                // 0x5ec
    Arc2         m61c;                // 0x61c
    ObjE0A400    m620;                // 0x620
    Arc1         m694;                // 0x694
    SharedLibVec m698;                // 0x698

    virtual ~cSPUISpace();
};

// @ 0x0106f5b0
cSPUISpace::~cSPUISpace()
{
    delete mp568;
    mp568 = 0;
    FUN_0067de40()->Get()->Set(g_16e0d08);
    g_16e0d08 = 0;
}
}   // namespace SP
