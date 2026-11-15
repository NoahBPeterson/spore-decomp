// src/game/SPEngine/_at_00680000.cpp -- migrated from slice(s) s0068e670, s0068d840, s0068c330, s0068b150, s00687c20, s006870a0, s00683f80, s00681f10, s00680c30 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00680000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"
#include <stdlib.h>   // atol, strtoul, wcstol (msvcr90 imports)
#include <ctype.h>    // tolower
#include <intrin.h>   // _ReadWriteBarrier
#include "EA/Variant.h"
#include "SP/cCommandParameterSet.h"
#include "SP/cCommandServer.h"
#include "SP/cMessageCommandDispatcher.h"
#include "SP/cStringCommandGenerator.h"
#include <intrin.h>
#include <wchar.h>
#include <string.h>
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "SP/cJob.h"
#include "SP/JobCondition.h"
#include "EA/Thread/Mutex.h"
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// unnamed retail callees and globals (address in the comment)
extern "C" void* MemcpyT(void* dst, const void* src, uint32_t n);        // 0x011e0744 (memcpy thunk)
extern "C" void EASTL_dealloc(void* p);                                  // 0x0f47380 EASTL_allocator_deallocate
extern "C" void* EASTL_alloc6(uint32_t n, void* tag, uint32_t a, uint32_t b,
                              const char* file, uint32_t line);          // 0x0f473a0 EASTL_allocator_allocate
extern "C" char g_allocTag[];                                            // 0x013ebc58 "App"
extern "C" char g_fileEASTL[];                                           // 0x013ebb38 allocator.h path
extern "C" void __cdecl WriteUint32(void* s, void* p, int n, int flags); // 0x093aa70
extern "C" void __cdecl ReadInt32(void* s, void* p, int n, int flags);   // 0x093a780
extern "C" void* __cdecl RBTreeIncrement(void* node);                    // 0x0921580
extern "C" void* __cdecl RBTreeDecrement(void* node);                    // 0x09215c0
extern "C" void __cdecl RBTreeInsert(void* nodeNew, void* pos, void* anchor, int canInsert); // 0x09216a0
extern "C" void __cdecl MoveBack_300(void* first, void* last, void* destLast); // 0x00680300
extern "C" void* __cdecl CopyN_270(void* first, void* last, void* dest); // 0x00680270
extern "C" void* __cdecl CopyN_1a0(void* first, void* last, void* dest); // 0x006801a0
extern "C" void  __cdecl CopyN_230(void* first, void* last, void* dest); // 0x00680230
extern "C" void  __cdecl CtorN_420(void** pv, void* first, void* last, void* dest, void* last2); // 0x00680420

// ---- items of slice s00680c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) { return p; }
extern "C" void* MemcpyT(void* dst, const void* src, uint32_t n);        // 0x011e0744 (memcpy thunk)
extern "C" void EASTL_dealloc(void* p);                                  // 0x0f47380 EASTL_allocator_deallocate
extern "C" void* EASTL_alloc6(uint32_t n, void* tag, uint32_t a, uint32_t b,
                              const char* file, uint32_t line);          // 0x0f473a0 EASTL_allocator_allocate
extern "C" char g_allocTag[];                                            // 0x013ebc58 "App"
extern "C" char g_fileEASTL[];                                           // 0x013ebb38 allocator.h path
extern "C" void __cdecl WriteUint32(void* s, void* p, int n, int flags); // 0x093aa70
extern "C" void __cdecl ReadInt32(void* s, void* p, int n, int flags);   // 0x093a780
extern "C" void* __cdecl RBTreeIncrement(void* node);                    // 0x0921580
extern "C" void* __cdecl RBTreeDecrement(void* node);                    // 0x09215c0
extern "C" void __cdecl RBTreeInsert(void* nodeNew, void* pos, void* anchor, int canInsert); // 0x09216a0
extern "C" void __cdecl MoveBack_300(void* first, void* last, void* destLast); // 0x00680300
extern "C" void* __cdecl CopyN_270(void* first, void* last, void* dest); // 0x00680270
extern "C" void* __cdecl CopyN_1a0(void* first, void* last, void* dest); // 0x006801a0
extern "C" void  __cdecl CopyN_230(void* first, void* last, void* dest); // 0x00680230
extern "C" void  __cdecl CtorN_420(void** pv, void* first, void* last, void* dest, void* last2); // 0x00680420
struct S8 {
    char* mpBegin;
    char* mpEnd;
    char* mpEndCap;
    void Init(int n);                       // 0x00475ab0 RangeInitialize
    ~S8() {
        if ((int)(mpEndCap - mpBegin) > 1 && mpBegin)
            EASTL_dealloc(mpBegin);
    }
    __forceinline S8(const S8& x) {
        mpBegin = 0;
        mpEnd = 0;
        mpEndCap = 0;
        char* xEnd = x.mpEnd;
        char* xBegin = x.mpBegin;
        int n = xEnd - xBegin;
        Init(n + 1);
        MemcpyT(mpBegin, xBegin, (uint32_t)n);
        mpEnd = mpBegin - xBegin + xEnd;
        *mpEnd = 0;
    }
};
struct N48 {
    uint32_t v[18];
    N48(const N48&);                        // 0x00680130-ish construct helpers
    ~N48();
};
struct SStrA {
    char* mpBegin;
    char* mpEnd;
    char* mpEndCap;
    ~SStrA() {
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_dealloc(mpBegin);
    }
};
struct SStrB {
    char* mpBegin;
    char* mpEnd;
    char* mpEndCap;
    ~SStrB() {
        if ((int)(mpEndCap - mpBegin) > 1 && mpBegin)
            EASTL_dealloc(mpBegin);
    }
};
struct NC0 { void Fix(NC0* prev); };        // 0x006800c0
struct V48 {
    N48* mpBegin;
    N48* mpEnd;
    N48* mpEndCap;
    N48* ReallocN7a0(int n, N48* first, N48* last);   // 0x006807a0
    void Destroy3f0(N48* first, N48* last);           // 0x006803f0
    void insert(N48* pos, const N48& x);              // 0x00680cc0 (below)
    V48& operator=(const V48* other);                 // 0x00680e70 (below)
};
struct VF {
    char* mpBegin;
    char* mpEnd;
    char* mpEndCap;
    void* mTag[2];
    void Reserve(int n, void* tag);                   // 0x004aa350
    VF& operator=(const VF& x);                       // 0x0050d4e0
    ~VF();
    __forceinline VF(const VF& x) {
        Reserve((int)(x.mpEnd - x.mpBegin) >> 2, (void*)x.mTag);
        int n = (int)(x.mpEnd - x.mpBegin);
        mpEnd = (char*)((uint32_t*)MemcpyT(mpBegin, x.mpBegin, (uint32_t)n) + (n >> 2));
    }
};
struct Pod16 { uint32_t w[4]; };
struct Pod60 { uint32_t w[24]; };
struct M5a0 {
    char c;
    M5a0() {}
    M5a0(const M5a0& x);                    // 0x00680a50
    ~M5a0(); // 0x00680730
};
struct ObjC30 {
    S8 mStr;                                // +0x00
    char pad[4];
    M5a0 mM;                                // +0x10
    ObjC30(const ObjC30& other);            // 0x00680c30 (below)
};
struct RNode {
    RNode* mpRight;                         // +0
    RNode* mpLeft;                          // +4
    uint32_t pad[2];                        // +8
    int mKey;                               // +0x10
    ObjC30 mVal;                            // +0x14
};
struct PairOut { RNode* first; bool second; };
struct AllocArg { };
struct RAnchor {
    uint32_t pad;
    RNode* mpBegin;                         // +8 from map start
    RNode* mpRoot;                          // +0xc
    RNode* mpParent;                        // +0x10
};
struct MapV {
    char pad0[4];
    RAnchor mAnchor;                        // +4
    int mnSize;                             // +0x14
    RNode* CreateNode(const int* key);      // 0x006811d0
    RNode** InsertPair(RNode** pOut, RNode* pos, int* key, bool bAllowEquiv); // 0x00681590 (below)
    void InsertUnique(PairOut* pOut, const int* key, AllocArg alloc);     // 0x006815f0 (below)
};
struct IRd12 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void vA();
virtual void vB();
    virtual void Read(void* p, int n);      // slot 12 (0x30)
};
struct IWrt14 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void vA();
virtual void vB();
virtual void vC();
virtual void vD();
    virtual void Write(const void* p, int n);   // slot 14 (0x38)
};
struct VU32 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpEndCap;
    void DoIns_4558a0(uint32_t* pos, int* val);   // 0x004558a0
};
struct S16 {
    void* f0;
    void* f4;
    void* f8;
    void* fC;
    void* f10;
    S16() { f0 = 0; f4 = 0; f8 = 0; fC = 0; f10 = 0; }
};
struct SPString {
    char pad[0x14];
    int mTableId;                           // +0x14
    int mInstanceId;                        // +0x18
    int mX;                                 // +0x1c
    SPString();                             // 0x006b5060
    void Load(int a, int b, int c);         // 0x006b54b0
    const char* c_str();                    // 0x006b5240
};
struct Thing {
    char pad[0x14];
    Thing() {}
    ~Thing();                               // 0x00680730
};
struct WF80 {
    void __thiscall Make5c0(Thing* t, IWrt14* w);   // 0x006805c0
};
struct T28 { ~T28(); };                     // 0x00680730
struct T1160 { ~T1160(); };                 // 0x00681160
struct Cls1400 {
    SStrB mVec;                             // +0x00 (inline dtor)
    char pad0[0x28 - 12];
    T28 m28;                                // +0x28
    char pad1[0x3c - 0x28 - 1];
    T1160 m3c;                              // +0x3c
    ~Cls1400();
};
struct Node1480 {
    Node1480* mpDown;                       // +0
    void* mpNext;                           // +4
    char pad0[0xC];
    SStrB m14;                              // +0x14
    char padM[4];
    SStrA m24;                              // +0x24
    char pad1[8];
    SStrA m38;                              // +0x38
};
struct MapC2 {
    void FreeNodes(Node1480* p);            // 0x00681480 (below)
};
struct Node15 {
    Node15* mpDown;                         // +0
    void* mpNext;                           // +4
    char pad0[0x14 - 8];
    SStrB m14;                              // +0x14
    char pad1[0x24 - 0x14 - 12];
    T28 m24;                                // +0x24
};
struct MapC0 {
    void FreeChain2(Node15* p);             // 0x00681500 (below)
};
struct ContC {
    void __thiscall AddEntry10e0(void* p);  // 0x006810e0
};
struct Obj1800 {
    Pod60 m0;                               // +0x00
    M5a0 mM;                                // +0x60
    char pad[0x74 - 0x60 - 1];
    VF mF0;                                 // +0x74
    VF mF1;                                 // +0x88
    VF mF2;                                 // +0x9c
    VF mF3;                                 // +0xb0
    Obj1800(const Obj1800& other);          // 0x00681800 (below)
};
struct Obj1700 {
    S8 mStr;                                // +0x00
    char pad[4];                            // +0x0c: vector block starts at +0x10 in the original
    VF mF0;                                 // +0x10
    VF mF1;                                 // +0x24
    Obj1700(const Obj1700& other);          // 0x00681700 (below)
};
struct ObjA {
    Pod16 m0;                               // +0x00
    VF mF0;                                 // +0x10
    VF mF1;                                 // +0x24
    VF mF2;                                 // +0x38
    VF mF3;                                 // +0x4c
    ObjA(const ObjA& other);                // 0x00681a10 (below)
    ObjA& operator=(const ObjA& x);         // 0x00681c40 (below)
};
struct ObjB50 {
    Pod60 m0;                               // +0x00
    V48 mV48;                               // +0x60
    VF mF0;                                 // +0x74
    VF mF1;                                 // +0x88
    VF mF2;                                 // +0x9c
    VF mF3;                                 // +0xb0
    ObjB50& operator=(const ObjB50& x);     // 0x00681b50 (below)
};
struct MapC0b {
    void __thiscall ReadKey(S16* out, IRd12* s);    // 0x00680560
    void __thiscall LoadEntries(ContC* out, IRd12* s);  // 0x006812c0 (below)
};
// ---- items of slice s00680c30 end

// ---- items of slice s00681f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl WriteByte(void* s, void* p, int n);              // 0x093a9a0
extern "C" void  __cdecl StringResize(void* s, int n);                   // 0x047bf30
extern "C" void  __cdecl UninitCopy(void** out, void* first, void* last, void* dst, void* last2); // 0x0681ca0
extern "C" void* __cdecl CreateNode1(const void* pair);                  // 0x06811d0 (value ObjC30)
extern "C" void* __cdecl CreateNode2(const void* pair);                  // 0x06826c0 (value Obj1700)
struct IWrt {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void vA();
virtual void vB();
virtual void vC();
virtual void vD();
    virtual void Write(const void* p, int n);       // slot 14 (0x38)
};
struct IRd {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void vA();
virtual void vB();
    virtual void Read(void* p, int n);              // slot 12 (0x30)
};
extern "C" void  __cdecl SaveVec390(void* self, void* v, IWrt* w);       // 0x0680390
extern "C" void  __cdecl SaveObj500(void* self, void* o, IWrt* w);       // 0x0680500
extern "C" void  __cdecl SaveObj5c0(void* self, void* o, IWrt* w);       // 0x06805c0
extern "C" void  __cdecl LoadEntries(void* self, void* out, IRd* r);     // 0x06812c0
struct PairOut2 { void* first; bool second; };
struct S8_s0068_1f10 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    S8_s0068_1f10() {}
    void Init(int n);                           // 0x0475ab0 RangeInitialize
    __forceinline S8_s0068_1f10(const S8_s0068_1f10& x) {
        mpBegin = 0; mpEnd = 0; mpCap = 0;
        char* xEnd = x.mpEnd;
        char* xBegin = x.mpBegin;
        int n = xEnd - xBegin;
        Init(n + 1);
        MemcpyT(mpBegin, xBegin, (uint32_t)n);
        mpEnd = mpBegin - xBegin + xEnd;
        *mpEnd = 0;
    }
    ~S8_s0068_1f10() { if ((int)(mpCap - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};
struct V20 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void* mAlloc[2];
    ~V20() { if (mpBegin && ((int*)mpBegin)[-1]) EASTL_dealloc(mpBegin); }
};
struct M5a0_s0068_1f10 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void* mAlloc[2];
    M5a0_s0068_1f10() {}
    M5a0_s0068_1f10(const M5a0_s0068_1f10& o);                        // 0x0680a50 (out-of-slice)
    ~M5a0_s0068_1f10();                                    // 0x0680730
};
struct VV12 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    ~VV12();                                    // 0x0681160
    VV12() {}
    VV12(const VV12& o);                        // 0x0682740 (below)
};
struct ObjC30_s0068_1f10 {
    S8_s0068_1f10 mStr;                                    // +0x00
    uint32_t padC;                              // +0x0c
    M5a0_s0068_1f10 mVec;                                  // +0x10
    ObjC30_s0068_1f10(const ObjC30_s0068_1f10& o);                    // 0x0680c30 (out-of-slice)
};
struct Obj1700_s0068_1f10 {
    S8_s0068_1f10 mStr;                                    // +0x00
    uint32_t padC;                              // +0x0c
    V20 mF0;                                    // +0x10
    V20 mF1;                                    // +0x24
    Obj1700_s0068_1f10(const Obj1700_s0068_1f10& o);                  // 0x0681700 (out-of-slice)
};
struct Obj2A10 {
    S8_s0068_1f10 mStr;                                    // +0x00
    uint32_t padC;                              // +0x0c
    uint8_t b10, b11, b12, b13, b14;            // +0x10
    uint8_t pad15[3];                           // +0x15
    uint32_t w18, w1c, w20, w24;                // +0x18
    M5a0_s0068_1f10 mM;                                    // +0x28
    VV12 mVec;                                  // +0x3c
    Obj2A10(const Obj2A10& o);                  // 0x0682a10 (below)
    // implicit ~Obj2A10() is generated inline (calls ~VV12, ~M5a0, ~S8)
};
struct Bits20 { uint32_t w[5]; };
struct ObjA_s0068_1f10 {
    uint32_t mW0;                               // +0x00
    uint32_t mW4;                               // +0x04 (never serialized)
    uint32_t mW8;                               // +0x08
    uint32_t mWc;                               // +0x0c
    V20 mF0;                                    // +0x10
    V20 mF1;                                    // +0x24
    V20 mF2;                                    // +0x38
    V20 mF3;                                    // +0x4c
    ObjA_s0068_1f10(const ObjA_s0068_1f10& o);                        // 0x0681a10 (out-of-slice)
};
struct Obj1800_s0068_1f10 {
    Bits20 mBits[4];                            // +0x00 (0x50; each written by 0x0680500)
    uint32_t mW50;                              // +0x50
    uint32_t mW54;                              // +0x54
    uint32_t mW58;                              // +0x58
    uint32_t mW5c;                              // +0x5c
    M5a0_s0068_1f10 mM;                                    // +0x60 (written by 0x06805c0)
    V20 mF0;                                    // +0x74
    V20 mF1;                                    // +0x88
    V20 mF2;                                    // +0x9c
    V20 mF3;                                    // +0xb0
    Obj1800_s0068_1f10(const Obj1800_s0068_1f10& o);                  // 0x0681800 (out-of-slice)
};
struct Node2 {
    Node2* mpRight;                             // +0x00
    Node2* mpLeft;                              // +0x04
    Node2* mpParent;                            // +0x08
    uint32_t mColor;                            // +0x0c
    int mKey;                                   // +0x10
    Obj1700_s0068_1f10 mVal;                               // +0x14
};
struct Map2 {
    uint32_t pad0;                              // +0x00
    Node2* mpAnchor;                            // +0x04
    Node2* mpBegin;                             // +0x08
    Node2* mpRoot;                              // +0x0c
    uint32_t mColor;                            // +0x10
    uint32_t mnSize;                            // +0x14
    uint32_t mAlloc;                            // +0x18
    Node2* Clone(Node2* src, Node2* parent);                // 0x0682be0 (below)
    void InsertHint(Node2** out, Node2* hint, int* key, char flag); // 0x06828a0 (below)
    void InsertUnique(PairOut2* out, const int* key);       // 0x0682900 (below)
};
struct Node1 {
    Node1* mpRight;
    Node1* mpLeft;
    Node1* mpParent;
    uint32_t mColor;
    int mKey;                                   // +0x10
    ObjC30_s0068_1f10 mVal;                                // +0x14
};
struct Map1 {
    uint32_t pad0;
    Node1* mpAnchor;                            // +0x04
    Node1* mpBegin;                             // +0x08
    Node1* mpRoot;                              // +0x0c
    uint32_t mColor;                            // +0x10
    uint32_t mnSize;                            // +0x14
    uint32_t mAlloc;                            // +0x18
    void InsertHint(Node1** out, Node1* hint, int* key, char flag); // 0x06825d0 (below)
    void InsertUnique(PairOut2* out, const int* key);               // 0x06815f0 (out-of-slice)
    ObjC30_s0068_1f10* operator[](const int& key);                // 0x0682af0 (below)
};
struct Node3 {
    Node3* mpRight;
    Node3* mpLeft;
    Node3* mpParent;
    uint32_t mColor;
    int mKey;                                   // +0x10
    Obj2A10 mVal;                               // +0x14
};
struct Map3 {
    uint32_t pad0;
    Node3* mpAnchor;
    Node3* mpBegin;
    Node3* mpRoot;
    uint32_t mColor;
    uint32_t mnSize;
    uint32_t mAlloc;
    void FreeNodes(Node3* p);                   // 0x0682800 (below)
};
struct Buf {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    uint32_t mAlloc;
    ~Buf() { if ((int)(mpCap - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};
struct MapC2_s0068_1f10 {
    uint32_t pad0;                              // +0x00
    void* mpAnchor;                             // +0x04
    void* mpBegin;                              // +0x08
    void* mpRoot;                               // +0x0c
    ~MapC2_s0068_1f10() { FreeNodes(mpRoot); }
    void FreeNodes(void* p);                    // 0x0681480 (out-of-slice)
};
struct Cls60 {
    Buf mVec;                                   // +0x00
    MapC2_s0068_1f10 mMap;                                 // +0x10
    ~Cls60();
};
struct SerCtx {
    void __thiscall WriteVec1800(VV12* v, IWrt* w);
    void __thiscall WriteVecA(VV12* v, IWrt* w);
    void __thiscall WriteMap1700(Map2* map, IWrt* w);
    void __thiscall WriteMap2A10(Map3* map, IWrt* w);
    void __thiscall LoadMap1(Map1* map, IRd* r);
};
static __forceinline void WriteVecU32(IWrt* w, V20* v) {
    int n = (int)((v->mpEnd - v->mpBegin) / 4);
    w->Write(&n, 4);
    for (int i = 0; i < n; ++i) {
        uint32_t e = ((uint32_t*)v->mpBegin)[i];
        w->Write(&e, 4);
    }
}
extern "C" void  __cdecl RangeInitialize(void* s, int n);                // 0x0475ab0
// ---- items of slice s00681f10 end

// ---- items of slice s00683f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char  g_emptyStr[];                          // 0x1667bac (empty string sentinel)
extern "C" void  FUN_006841a0(void*, void*);
extern "C" void  FUN_00682ca0(void*, void*);
extern "C" void  FUN_00680fc0(void*, void*);
extern "C" void  FUN_006823f0(void*, void*);
extern "C" void  FUN_00682e90(void*, void*);
extern "C" void  FUN_00683ab0(void*, void*);
extern "C" void  FUN_00684740(void*, void*);
extern "C" void  FUN_00684a90(void*, void*);
static inline void** VT(void* p) { return *(void***)p; }
struct S8_s0068_3f80 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    S8_s0068_3f80() { mpBegin = g_emptyStr; mpEnd = g_emptyStr; mpCap = g_emptyStr + 1; }
    void Resize(int n, int ch);                     // 0x047bf30 (thiscall, ret 8)
};
struct V20_s0068_3f80 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void* mAlloc[2];
    V20_s0068_3f80() { mpBegin = 0; mpEnd = 0; mpCap = 0; mAlloc[0] = 0; mAlloc[1] = 0; }
};
struct M5a0_s0068_3f80 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    void* mAlloc[2];
    M5a0_s0068_3f80() { mpBegin = 0; mpEnd = 0; mpCap = 0; mAlloc[0] = 0; mAlloc[1] = 0; }
};
struct VV12_s0068_3f80 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    VV12_s0068_3f80() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
};
struct Buf_s0068_3f80 {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    uint32_t mAlloc;
    Buf_s0068_3f80() { mpBegin = g_emptyStr; mpEnd = g_emptyStr; mpCap = g_emptyStr + 1; mAlloc = 0; }
    ~Buf_s0068_3f80() { if ((int)(mpCap - mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};
struct Obj1700_s0068_3f80 {
    S8_s0068_3f80 mStr;                                        // +0x00
    uint32_t padC;                                  // +0x0c
    V20_s0068_3f80 mF0;                                        // +0x10
    V20_s0068_3f80 mF1;                                        // +0x24
};
struct Obj2A10_s0068_3f80 {
    S8_s0068_3f80 mStr;                                        // +0x00
    uint32_t padC;                                  // +0x0c
    uint8_t b10, b11, b12, b13, b14;                // +0x10
    uint8_t pad15[3];                               // +0x15
    uint32_t w[4];                                  // +0x18
    M5a0_s0068_3f80 mM;                                        // +0x28
    VV12_s0068_3f80 mVec;                                      // +0x3c
    Obj2A10_s0068_3f80() { padC = 0; b10 = b11 = b12 = b13 = b14 = 0;
                w[0] = w[1] = w[2] = w[3] = 0; }
};
struct NodeA { NodeA* mpRight; NodeA* mpLeft; NodeA* mpParent; uint32_t mColor; int mKey; Obj1700_s0068_3f80 mVal; };
struct MapA {
    void* pad0; NodeA* mpAnchor; NodeA* mpBegin; NodeA* mpRoot; uint32_t mColor; uint32_t mnSize; uint32_t mAlloc;
    Obj1700_s0068_3f80* Idx(const int& key);                   // 0x0683d10 (out-of-slice)
};
struct Map2_s0068_3f80 {
    void* pad0; void* mpAnchor; void* mpBegin; void* mpRoot; uint32_t mColor; uint32_t mnSize;
    Map2_s0068_3f80() { pad0 = 0; mpAnchor = &mpAnchor; mpBegin = &mpAnchor; mpRoot = 0; mColor = 0; mnSize = 0; }
    void FreeNodes(void* p);                        // 0x0681480 (out-of-slice)
    ~Map2_s0068_3f80() { FreeNodes(mpRoot); }
};
struct ObjY {
    Buf_s0068_3f80 mVec;                                       // +0x00
    Map2_s0068_3f80 mMap;                                      // +0x10
    ObjY() {}
    ObjY(const ObjY& o);                            // 0x0683670 (out-of-slice)
};
struct NodeC { NodeC* mpRight; NodeC* mpLeft; NodeC* mpParent; uint32_t mColor; int mKey; ObjY mVal; };
struct MapC {
    void* pad0; NodeC* mpAnchor; NodeC* mpBegin; NodeC* mpRoot; uint32_t mColor; uint32_t mnSize; uint32_t mAlloc;
    NodeC* CreateNode(const void* pair);                        // 0x0684420
    void InsertPair(NodeC** out, NodeC* pos, const void* pair, char flag);   // 0x06844a0
    void InsertUnique(void* pairOut, const void* pair, char flag);           // 0x0684500
    void InsertHint(NodeC** out, NodeC* hint, const void* pair, char flag);  // 0x0684890
    ObjY* Idx(const int& key);                                  // 0x0684980
    void FreeChain(NodeC* p);                                   // 0x0683160 (out-of-slice)
    ~MapC() { FreeChain(mpRoot); }
};
struct NodeB { NodeB* mpRight; NodeB* mpLeft; NodeB* mpParent; uint32_t mColor; int mKey; Obj2A10_s0068_3f80 mVal; };
struct MapB {
    void* pad0; NodeB* mpAnchor; NodeB* mpBegin; NodeB* mpRoot; uint32_t mColor; uint32_t mnSize; uint32_t mAlloc;
    NodeB* CreateNode(const void* pair);                        // 0x0683480
    void InsertPair(NodeB** out, NodeB* pos, const void* pair, char flag);   // 0x0683500
    void InsertUnique(void* pairOut, const void* pair, char flag);           // 0x0683560
    void InsertHint(NodeB** out, NodeB* hint, const void* pair, char flag);  // 0x0684330
    Obj2A10_s0068_3f80* Idx(const int& key);                               // 0x0684610
    void FreeNodes(NodeB* p);                                   // 0x0682800 (out-of-slice)
    ~MapB() { FreeNodes(mpRoot); }
};
struct MapC0_s0068_3f80 {
    void* pad0; void* mpAnchor; void* mpBegin; void* mpRoot; uint32_t mColor; uint32_t mnSize; uint32_t mAlloc;
    void FreeChain2(void* p);                       // 0x0681500 (out-of-slice)
    ~MapC0_s0068_3f80() { FreeChain2(mpRoot); }
};
struct BufM {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    uint32_t mAlloc;
    void Erase(void* begin, void* end);             // 0x0680b70 (thiscall, ret 8)
    ~BufM() {
        Erase(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_dealloc(mpBegin);
    }
};
struct GmeEditorResBase {
    void* vtbl;
    ~GmeEditorResBase() { vtbl = (void*)0x13eb938; }   // ??_7GmeEditorResBase@@6B@
};
struct Factory : GmeEditorResBase {
    char pad04[0x14];                               // +0x04 .. +0x18
    MapB m18;                                       // +0x18
    MapC0_s0068_3f80 m34;                                      // +0x34
    MapC m50;                                       // +0x50
    BufM m6c;                                       // +0x6c
    ~Factory();

    char Create(int* mgr, int** out, int a, int b);
    void ReadMapA(MapA* map, IRd* r);
    void ReadMapC(MapC* map, IRd* r);               // 0x0684a90
    void WriteMapC(MapC* map, IWrt* w);
    void ReadMapB(MapB* map, IRd* r);

    // out-of-slice helpers
    void ReadVecU32(V20_s0068_3f80* v, IRd* r);                // 0x0681250
    void LoadEntries(M5a0_s0068_3f80* v, IRd* r);              // 0x06812c0
    void LoadObj1800(VV12_s0068_3f80* v, IRd* r);              // 0x0683700
    void WriteMap1700(Map2_s0068_3f80* map, IWrt* w);          // 0x0681f10
};
struct CPropList { void* ctor(); };                 // 0x0683e90
struct FactSer {
    int __thiscall ser_6842c0(int* a, int* b, int c, int d);
};
struct Map844 {
    char pad0[4];
    void* head;    // +0x04
    void* tail;    // +0x08
    char padc[8];
    int count;     // +0x14
    void* allocNode(int* key);   // FUN_00684420
    void* insert(void** out, void* at, int* key, char flag);
};
// ---- items of slice s00683f80 end

// ---- items of slice s006870a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  g_count;                    // 0x0152b348
extern "C" char* g_array;                   // 0x015fea00
struct VecU32G { uint32_t* b; uint32_t* e; uint32_t* c;
    void InsertRange(uint32_t* first, uint32_t* last, uint32_t* dst); // 0x06ad970
};
struct VecWStr { void* b; void* e; void* c;
    void push_back(const void* p);          // 0x0553f10
};
struct VecU32 { uint32_t* b; uint32_t* e; uint32_t* c;
    void DoIns(uint32_t* pos, const uint32_t* val); // 0x04558a0
};
// ---- items of slice s006870a0 end

// ---- items of slice s00687c20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWString[];                       // 0x1667bac shared empty string
extern "C" void EASTL_allocator_deallocate(void* p);  // 0xf47380
extern "C" void* memcpy(void*, const void*, unsigned);  // E8 call (non-dllimport thunk)
extern const char g_allocFile[];                      // 0x13ebb38 EASTL/allocator.h path
extern "C" int __cdecl FUN_00687bc0(int id);          // clamp id against table size (0x687bc0)
extern "C" void* __cdecl FUN_009309b0(void* dest, const wchar_t* src, int a3, int a4);  // 0x9309b0
extern "C" void __cdecl WStr_Format(void* out, const wchar_t* fmt, ...);
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* pFile, int line);      // 0xf473a0 EA 6-arg operator new
struct WStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  void* mAllocUnused;   // stateless allocator member (never stored)

  WStr() : mpBegin(gEmptyWString), mpEnd(gEmptyWString), mpCapacity(gEmptyWString + 1) {}
  WStr(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  WStr(const WStr& x) : mpBegin(0), mpEnd(0), mpCapacity(0) {
    _ReadWriteBarrier();
    RangeInitialize(x.mpBegin, x.mpEnd);
  }
  WStr(const wchar_t* pBegin, const wchar_t* pEnd)
      : mpBegin(0), mpEnd(0), mpCapacity(0) {
    _ReadWriteBarrier();
    RangeInitialize(pBegin, pEnd);
  }
  struct InlineTag { InlineTag() {} };
  // Same as the range ctor but with the allocation (EA operator new "App") expanded inline.
  __forceinline WStr(const wchar_t* pBegin, const wchar_t* pEnd, const InlineTag&)
      : mpBegin(0), mpEnd(0), mpCapacity(0) {
    const int n = (int)(pEnd - pBegin);
    const int cap = n + 1;
    if (cap > 1) {
      mpBegin = (wchar_t*)operator new(cap * 2, "App", 0, 0, g_allocFile, 0xd1);
      mpCapacity = mpBegin + cap;
    } else {
      mpBegin = gEmptyWString;
      mpCapacity = gEmptyWString + 1;
    }
    memcpy(mpBegin, pBegin, n * 2);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
  ~WStr() {
    if ((((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  WStr& operator=(const WStr& x);                  // 0x5c3d90
  void Assign(const wchar_t* b, const wchar_t* e); // 0x423650
  void push_back(wchar_t c);                       // 0x4f6510
  void AllocateSelf(int n);                        // 0x429760
  void RangeInitialize(const wchar_t* p);          // 0x579a90
  void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd) {
    const int n = (int)(pEnd - pBegin);
    AllocateSelf(n + 1);
    memcpy(mpBegin, pBegin, n * 2);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
};
struct WStrRange { const wchar_t* begin; const wchar_t* end; };
struct Entry40 {
  uint8_t b;
  uint8_t pad1[3];
  int a3;
  WStr name;      // +8
  WStr other;     // +0x18
};
struct EntryVec {                                // 0x15fea00
  Entry40* mpBegin;
  Entry40* mpEnd;
  void* mpCap;
  void Grow(int n);                              // 0x687ab0
};
extern EntryVec g_entryVec;                      // 0x15fea00
namespace EA {
namespace ArgScript {
class cArguments_s0068_7c20 { public:
  int NumArguments();                            // 0x837f30
  char* operator[](int i);                       // 0x837f20
};
}
}
struct cRendererCheat {
  virtual void Execute(EA::ArgScript::cArguments_s0068_7c20* args);
  WStr mStr;                     // +4
  char pad[0x20c - 0x14];
  EntryVec* mpEntries;           // +0x20c
  int mMode;                     // +0x210
};
// ---- items of slice s00687c20 end

// ---- items of slice s0068b150 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint32;
typedef unsigned __int64 uint64;
typedef unsigned long uintptr_t_s0068_b150;
void  EAFree(void* p);                                                       // 0x00F47380 cdecl
struct FreeItem {
    uint32 pad0;
    uint32 pad4;
    uint64 next;
};
struct FreeList {
    uint64 mHead;                        // +0x00

    void Drain();                        // 0x0068C220
    void Push(uint32 a, uint32 b);       // 0x0068C280
};
// ---- items of slice s0068b150 end

// ---- items of slice s0068c330 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* EAAllocate(unsigned size, const char* area, int a, int b, const char* file, int line); // 0x00F473A0
uint64 __fastcall AtomicRead64(volatile uint64* p);                                           // 0x0068C140
struct Atomic64 {
    void Exchange(uint64 v);       // 0x0068C1B0 (thiscall)
};
struct PopOut {
    void* a;
    void* b;
};
struct PendingVec {
    void DoInsertValue(void* pos, void* v);   // 0x007E1340 (thiscall)
};
struct FreeQueue {
    uint64 mPop;      // +0x00
    uint64 mPush;     // +0x08
    void*  mPending;  // +0x10
    void*  mPendingEnd;//+0x14
    void*  mCapacity; // +0x18
    char   pad1c[8];
    uint32 m24;       // +0x24
    uint32 m28;       // +0x28
    uint32 m2c;       // +0x2c
    uint32 m30;       // +0x30

    bool __declspec(noinline) TryPop(void** out);
    void Drain();
    void Shutdown();
    void Flush();
    void DrainList();
};
struct FreeQueueOps {                                   // FreeList::Push(uint32, uint32) thiscall
    void Push(uint32 lo, uint32 hi);                    // 0x0068C280
};
inline void FreeListPush(void* self, uint32 lo, uint32 hi)
{
    ((FreeQueueOps*)self)->Push(lo, hi);
}
// ---- items of slice s0068c330 end

// ---- items of slice s0068d840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void SetNameCallbacks(void* a, void* b);                  // 0x08dd8d0
extern "C" void* GetResourceManager();                               // 0x067dcd0
extern "C" int   ResourceManagerAdd(void* p);                        // 0x06b22f0
extern "C" void  Sub68dc00(void* a, void* b, void* c);               // 0x068dc00
extern "C" char gAllocTag[];         // 0x13ebc58 "App"
extern "C" char gEASTLFile[];        // 0x13ebb38 allocator.h path
extern "C" void  FUN_0068d1a0();
extern "C" void  Nuke_9a9600(void*, void*);
extern "C" void  MemcpyT2(void*, const void*, unsigned);
#define VFN(p, off) ((*(void***)(p))[(off) / 4])
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef wchar_t        wch;
extern "C" void* RBTreeInsert_s0068_d840(void* node, void* pos, void* anchor, int canInsert); // 0x09216a0
extern "C" u32   Sub932da0(void* data, int len, u32 seed, int flag);  // 0x0932da0
extern "C" void* Sub932df0(void* a, u32 b, u32 c, u32 d, u32 e);     // 0x0932df0
extern "C" int   WriteUint32_s0068_d840(void* io, void* p, int n, int f);       // 0x093aa70
extern "C" void  GetUptime(u32* out);                                           // 0x091ff50
extern "C" u8    gSerTag[];                                                    // 0x140369c
typedef bool (__thiscall *StreamFn2)(void* self, const void* p, int n);
extern "C" u32  gMaskTable[];        // 0x1403618
extern "C" u32  gHMNameMagic;        // 0x152ca8c
struct IWriter {
    virtual void v0();
    virtual void v1();
    virtual void WritePair(int a, int b, unsigned v);
    void Emit(int a, int b, u8 c, u32 d, u8 e, u8 f);
};
struct SetNode {
    SetNode* mpNodeRight;   // +0x00
    SetNode* mpNodeLeft;    // +0x04
    SetNode* mpNodeParent;  // +0x08
    u8 mColor;              // +0x0c
    u8 padD[3];
    u32 mKey;               // +0x10
    u32 mVal;               // +0x14
};
struct RBSet {
    u32 mCompare;           // +0x00
    SetNode* aRight;        // +0x04
    SetNode* aLeft;         // +0x08
    SetNode* aParent;       // +0x0c
    u8 aColor;              // +0x10
    u8 pad[3];
    u32 mnSize;             // +0x14
    u32 mAlloc;             // +0x18

    void Insert(SetNode** pOut, SetNode* pos, const int* val, char bAllow);
};
struct Coder {
    u8* mBuf;          // +0x00
    u32 f04;           // +0x04
    u32 f08;           // +0x08
    u32 f0c;           // +0x0c
    u32 f10;           // +0x10
    u32 f14;           // +0x14
    u32 f18;           // +0x18
    u32 f1c;           // +0x1c
    u8  f20; u8 pad21[3];
    u32 f24;           // +0x24
    u32 f28;           // +0x28
    u32 f2c;           // +0x2c
    u32 f30;           // +0x30 hash
    u32 f34;           // +0x34
    u32 f38;           // +0x38
    u32 f3c;           // +0x3c cur
    u32 f40;           // +0x40 limit
    u32 f44;           // +0x44 bit
    u32 f48;           // +0x48 mask
    u32 f4c;           // +0x4c
    u32 f50;           // +0x50 top
    u8  pad54;
    u8  f55;           // +0x55
    u8  f56;           // +0x56
    u8  pad57;
    u32 f58;           // +0x58
    u32 f5c;           // +0x5c
    u32 f60;           // +0x60
    u32 f64;           // +0x64
    u32 f68;           // +0x68
    u32 f6c;           // +0x6c

    Coder();
    ~Coder();
    void Init();        // 0x68e610
    void MaskInit();    // 0x68ddc0
    bool EncodeBit(u8 bit);       // 0x68de20
    void Flush();                 // 0x68df00
    bool DecodeBit(u8* out);      // 0x68dfd0
    bool DecodeFinish();          // 0x68e0c0
    void Init2();                 // 0x68db70
    char Serialize(void* io, int mode);  // 0x68e1a0
    int  Read(void* dst, u32 n);         // 0x68e3b0
    char Verify(char p);                 // 0x68e490
};
struct NameMapTree {                 // 0x1c bytes
    u32 f00;                         // +0x00  (left untouched)
    u32 mpNode;                      // +0x04  -> &mpNode
    u32 mpRoot;                      // +0x08  -> &mpNode
    u32 f0c;                         // +0x0c  = 0
    u32 f10;                         // +0x10  (dword then byte 0)
    u32 f14;                         // +0x14  = 0
    u32 f18;                         // +0x18  (left untouched)
    NameMapTree();
    ~NameMapTree();
};
struct NameMapCtor {
    void* mVt;                       // +0x00
    u32   mUptime;                   // +0x04
    NameMapTree m1;                  // +0x08
    NameMapTree m2;                  // +0x24
    NameMapCtor();
};
NameMapTree::NameMapTree() {
    mpRoot = 0;
    f0c = 0;
    f10 = 0;
    mpNode = (u32)(size_t)this + 4;
    mpRoot = (u32)(size_t)this + 4;
    f0c = 0;
    f10 = 0;
    f14 = 0;
}
struct Citizen {
    u32 f00, f04, f08, f0c, f10;
    u32 f14;      // +0x14 resource count
    void Init(void* out, void* arg3, u32 flags);   // 0x68dd10
};
struct SerCtx_s0068_d840 {
    char pad[0x14];
    void ctor87cf40();                          // 0x87cf40
    void m87cf60(void* v);                      // 0x87cf60
    bool m87d2a0(int a, int b);                 // 0x87d2a0
    bool m87d030(void* dst, void* src, int n);  // 0x87d030
    void m87cff0();                             // 0x87cff0
    void m87d260();                             // 0x87d260
};
// ---- items of slice s0068d840 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
extern "C" bool SPKeyFromName(u32* param_1, wch* param_2, u32 param_3, u32 param_4);  // 0x0068d840 (stays in the slice: not this object's)

// ---- items of slice s0068e670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  AddRef_68F950(void* job);          // 0x068f950  cJob::AddRef
extern "C" int  Release_690120(void* job);         // 0x0690120  cJob::Release
extern "C" void AddWeakDependency_6913C0(void* self, void* other); // 0x06913c0
extern "C" bool Continuation_68F9F0(void* job, void* fn, void* arg);  // 0x068f9f0
extern "C" int  LockDec_68F9B0(void* lock);        // 0x068f9b0
typedef unsigned long long u64;
extern "C" u32 __cdecl CRC32(const void* data, u32 n, u32 seed, int flag);      // 0x0932da0
extern "C" u64 __cdecl CRC64(const void* data, u32 n, u32 lo, u32 hi, u32 x);   // 0x0932df0
extern "C" u8  gMagicA[];      // 0x14036a0
extern "C" u8  gMagicB[];      // 0x14036a8
extern "C" u32 gTailTag;       // 0x14036b4
extern "C" u32 gHNMagic;       // 0x152ca8c  CRC32 name-hash seed
namespace EA {
namespace Thread {
struct Mutex_s0068_e670 {
    uint32_t _[12];
    void Lock(unsigned int nameId);   // ?Lock@Mutex@Thread@EA@@QAEXI@Z   0x09221b0
    void Unlock();                    // ?Unlock@Mutex@Thread@EA@@QAEXXZ 0x0922270
};
}
}
typedef EA::Thread::Mutex_s0068_e670 Mutex_s0068_e670;
struct VecU8 {
    u8* mpBegin;                                                             // +0x00
    u8* mpEnd;                                                               // +0x04
    u8* mpCap;                                                               // +0x08

    u32 size() const { return (u32)(mpEnd - mpBegin); }

    u8* erase(u8* first, u8* last) {
        MemcpyT(first, last, (u32)(mpEnd - last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }

    void DoInsertValues(u8* pos, u32 n, const void* value);                  // 0x004c10e0
    void resize(u32 n);                                                      // 0x004c0410
    void eraseAll();                                                         // 0x00631dc0

    void AssignFill(u32 count, const void* pval);
};
struct Entry {
    u32 type;                                                                // +0x00
    u32 pad04[3];                                                            // +0x04
    u32 width;                                                               // +0x10
    u32 height;                                                              // +0x14
    u32 bits;                                                                // +0x18
    u8  pad1c[0x438 - 0x1c];
    u32 f438;                                                                // +0x438
};
struct Hinter {
    u32 mRaw[5];
    Hinter();                                                                // 0x87cde0
    ~Hinter();                                                               // 0x87d070
    void   Open(const char* path);                                           // 0x87ce00
    char   GetFrame(int kind, u32* out);                                     // 0x87d0b0
    Entry* GetEntry(int idx);                                                // 0x87ced0
    char   Read(Entry* e, void* dst, int n);                                 // 0x87cf00
    void   Free(Entry* e);                                                   // 0x87cef0
};
struct Coder_s0068_e670 {
    VecU8 mData;                                                             // +0x00
    u32 f0c;                                                                 // +0x0c
    u32 f10;                                                                 // +0x10
    u32 mWidth;                                                              // +0x14
    u32 mHeight;                                                             // +0x18
    u32 mStride;                                                             // +0x1c
    u8  mFlag;                                                               // +0x20
    u8  pad20[3];
    u32 mState;                                                              // +0x24
    u32 mHashLo;                                                             // +0x28
    u32 mHashHi;                                                             // +0x2c
    u32 f30;                                                                 // +0x30
    u32 f34;                                                                 // +0x34
    u32 f38;                                                                 // +0x38
    u32 f3c;                                                                 // +0x3c
    u32 f40;                                                                 // +0x40
    u32 f44;                                                                 // +0x44
    u32 f48;                                                                 // +0x48
    u32 f4c;                                                                 // +0x4c
    u32 f50;                                                                 // +0x50
    u8  pad54;                                                               // +0x54
    u8  f55;                                                                 // +0x55
    u8  f56;                                                                 // +0x56
    u8  pad57;
    VecU8 mStream;                                                           // +0x58
    u32 f64;                                                                 // +0x64
    u32 f68;                                                                 // +0x68
    u32 f6c;                                                                 // +0x6c

    void InitMask();                                                         // 0x068ddc0
    char EncodeBit(u8 b);                                                    // 0x068de20
    void Flush();                                                            // 0x068df00
    int  Read(void* dst, u32 n);                                             // 0x068e3b0

    char ReadHeader(int* out);
    int  InitBitmap(int width, int height, int bits, u8 flag);
    char ReadData(void* io);
    char OpenData(const char* path);
    char WriteData(const u8* data, u32 n);
    char Finalize(char flag);
    char Begin(char external);
};
struct ThreadMutex {
    u32 mRaw[12];                                                            // 0x30 bytes
    ThreadMutex(const void* name, bool b);                                   // 0x09222a0
    ~ThreadMutex();                                                          // 0x0922130
};
struct GmeRefCount {
    volatile long mRef;                                                      // +0x04 (vptr at +0x00 is implicit)
    GmeRefCount() { volatile long* pRef = &mRef; _InterlockedExchange(pRef, 0); }
    virtual ~GmeRefCount() {}
};
struct CJob {
    int Release();                                                           // 0x0690120
};
struct RefObj : GmeRefCount {
    ThreadMutex mMutex;                                                      // +0x08
    void* mJob;                                                              // +0x38
    RefObj();
    virtual ~RefObj();
};
typedef int (__thiscall *FnAddRef)(void*);
typedef int (__thiscall *FnRelease)(void*);
typedef void (__thiscall *FnAddWeak)(void*, void*);
struct CJobHolder {
    uint32_t pad0[2];
    Mutex_s0068_e670 mMutex;           // +0x08 (0x30 bytes)
    void* mJob;             // +0x38
    bool SetJob(void* target, void* job);
};
typedef bool (__thiscall *FnContinuation)(void*, void*, void*);
struct CJobHolder2 {
    uint32_t f0, f4, f8;
    CJobHolder* mHolder;    // +0x0c
    void* mArg;             // +0x10
    bool Attach(void* job);
};
typedef int (__thiscall *FnLockDec)(void*);
struct JobLock {
    void* vtbl0;            // +0x00
    void* vtbl1;            // +0x04
    volatile long mRef;     // +0x08 refcount (lock xchg/xadd)
    void* mRefObj;          // +0x0c intrusive refcounted object
    void* mJob;             // +0x10
    JobLock(void* out, void* job, void* refObj);
    ~JobLock();
};
// ---- items of slice s0068e670 end

// @ 0x00680c30
__declspec(noinline) ObjC30::ObjC30(const ObjC30& other)
: mStr(other.mStr), mM(other.mM) {}

// @ 0x00680cc0
void V48::insert(N48* pos, const N48& x)
{
    N48* xAdj = (N48*)&x;
    if (mpEnd != mpEndCap) {
        if (xAdj >= pos && xAdj < mpEnd)
            xAdj = (N48*)&x + 1;
        N48* end = mpEnd;
        if (end)
            ((NC0*)end)->Fix((NC0*)(end - 1));
        end = mpEnd;
        MoveBack_300(pos, end - 1, end);
        new (pos) N48(*xAdj);
        mpEnd = end + 1;
    } else {
        int nElem = (int)(mpEnd - mpBegin) / 72;
        int nNew;
        if (nElem == 0)
            nNew = 1;
        else
            nNew = nElem * 2;
        N48* pNew = 0;
        if (nNew)
            pNew = (N48*)EASTL_alloc6((uint32_t)(nNew * 72), g_allocTag, 0, 0, g_fileEASTL, 0xd1);
        N48* begin = mpBegin;
        N48* pMid = (N48*)CopyN_1a0(begin, pos, pNew);
        CopyN_230(begin, pos, pNew);
        if (pMid)
            ((NC0*)pMid)->Fix((NC0*)&x);
        N48* const end = mpEnd;
        N48* pMid2 = (N48*)CopyN_1a0(pos, end, pNew + 1);
        CopyN_230(pos, end, pNew + 1);
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_dealloc(mpBegin);
        mpEnd = pMid2;
        mpBegin = pNew;
        mpEndCap = pNew + nNew;
    }
}

// @ 0x00680e70
V48& V48::operator=(const V48* other)
{
    if (other != this) {
        uint32_t n = (uint32_t)((other->mpEnd - other->mpBegin) / 72);
        uint32_t cap = (uint32_t)((mpEndCap - mpBegin) / 72);
        if (n > cap) {
            N48* pNew = ReallocN7a0(n, other->mpBegin, other->mpEnd);
            N48* begin = mpBegin;
            Destroy3f0(begin, mpEnd);
            if (begin && ((int*)begin)[-1])
                EASTL_dealloc(begin);
            mpEndCap = pNew + n;
            mpBegin = pNew;
            mpEnd = pNew + n;
        } else {
            int m = (int)(mpEnd - mpBegin) / 72;
            N48* begin = mpBegin;
            if (m < n) {
                CopyN_270(other->mpBegin, other->mpBegin + m, begin);
                N48* pX = other->mpEnd;
                CtorN_420((void**)&pX, other->mpBegin + m, pX, mpEnd, pX);
                mpEnd = mpBegin + n;
            } else {
                N48* pEnd = (N48*)CopyN_270(other->mpBegin, other->mpEnd, begin);
                Destroy3f0(pEnd, mpEnd);
                mpEnd = mpBegin + n;
            }
        }
    }
    return *this;
}

// @ 0x00680fc0
void Save_00680fc0(WF80* wthis, MapV* map, IWrt14* w)
{
    int nSize = map->mnSize;
    w->Write(&nSize, 4);
    for (RNode* n = map->mAnchor.mpBegin; n != (RNode*)&map->mAnchor; n = (RNode*)RBTreeIncrement(n)) {
        int key = n->mKey;
        ObjC30 tmp(n->mVal);
        w->Write(&key, 4);
        int size = tmp.mStr.mpEnd - tmp.mStr.mpBegin;
        WriteUint32(w, &tmp.mStr.mpBegin, size, 0);
        if (size)
            w->Write(tmp.mStr.mpBegin, size);
        Thing t;
        wthis->Make5c0(&t, w);
        if ((int)(tmp.mStr.mpEnd - tmp.mStr.mpBegin) > 1 && tmp.mStr.mpBegin)
            EASTL_dealloc(tmp.mStr.mpBegin);
    }
}

// @ 0x00681250
void __stdcall ReadVecU32(VU32* v, IRd12* s)
{
    int count;
    s->Read(&count, 4);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        int value;
        ReadInt32(s, &value, 1, 0);
        uint32_t* p = v->mpEnd;
        if (p < v->mpEndCap) {
            v->mpEnd = p + 1;
            if (p)
                *p = (uint32_t)value;
        } else {
            v->DoIns_4558a0(v->mpEnd, &value);
        }
    }
}

// @ 0x006812c0
void MapC0b::LoadEntries(ContC* out, IRd12* s)
{
    int count;
    s->Read(&count, 4);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        S16 a;
        S16 b;
        SPString str;
        str.mTableId = 0;
        str.mInstanceId = 0;
        str.mX = 0;
        ReadKey(&a, s);
        ReadKey(&b, s);
        int v1;
        ReadInt32(s, &v1, 1, 0);
        int v2;
        ReadInt32(s, &v2, 1, 0);
        str.Load(v2, v1, 0);
        str.mTableId = v2;
        str.mInstanceId = v1;
        ReadInt32(s, &str.mX, 1, 0);
        out->AddEntry10e0(&a);
        str.c_str();
    }
}

// @ 0x00681400
Cls1400::~Cls1400()
{}

// @ 0x00681480
void MapC2::FreeNodes(Node1480* p)
{
    while (p) {
        FreeNodes(p->mpDown);
        Node1480* next = (Node1480*)p->mpNext;
        p->m38.~SStrA();
        p->m24.~SStrA();
        p->m14.~SStrB();
        EASTL_dealloc(p);
        p = next;
    }
}

// @ 0x00681500
void MapC0::FreeChain2(Node15* p)
{
    while (p) {
        FreeChain2(p->mpDown);
        Node15* next = (Node15*)p->mpNext;
        p->m24.~T28();
        p->m14.~SStrB();
        EASTL_dealloc(p);
        p = next;
    }
}

// @ 0x00681590
RNode** MapV::InsertPair(RNode** pOut, RNode* pos, int* key, bool bAllowEquiv)
{
    int bIns;
    if (!bAllowEquiv && pos != (RNode*)&mAnchor && *key >= pos->mKey)
        bIns = 1;
    else
        bIns = 0;
    RNode* nNew = CreateNode(key);
    RBTreeInsert(nNew, pos, &mAnchor, bIns);
    ++mnSize;
    *pOut = nNew;
    return pOut;
}

// @ 0x006815f0
void MapV::InsertUnique(PairOut* pOut, const int* key, AllocArg alloc)
{
    RNode* pos = (RNode*)&mAnchor;
    bool bLess = true;
    RNode* n = mAnchor.mpRoot;
    if (n) {
        do {
            pos = n;
            bLess = (*key < n->mKey);
            n = bLess ? n->mpLeft : n->mpRight;
        } while (n);
    }
    RNode* found = pos;
    if (bLess) {
        if (pos != mAnchor.mpBegin) {
            pos = (RNode*)RBTreeDecrement(pos);
        } else {
            int bIns = (pos != (RNode*)&mAnchor && *key >= pos->mKey);
            RNode* nNew = CreateNode(key);
            RBTreeInsert(nNew, pos, &mAnchor, bIns);
            ++mnSize;
            pOut->first = nNew;
            pOut->second = true;
            return;
        }
    }
    if (pos->mKey < *key) {
        int bIns = (found != (RNode*)&mAnchor && *key >= found->mKey);
        RNode* nNew = CreateNode(key);
        RBTreeInsert(nNew, found, &mAnchor, bIns);
        ++mnSize;
        pOut->first = nNew;
        pOut->second = true;
    } else {
        pOut->first = pos;
        pOut->second = false;
    }
}

// @ 0x00681700
__declspec(noinline) Obj1700::Obj1700(const Obj1700& other)
: mStr(other.mStr), mF0(other.mF0), mF1(other.mF1) {}

// @ 0x00681800
__declspec(noinline) Obj1800::Obj1800(const Obj1800& other)
: m0(other.m0), mM(other.mM), mF0(other.mF0), mF1(other.mF1),
      mF2(other.mF2), mF3(other.mF3) {}

// @ 0x00681a10
__declspec(noinline) ObjA::ObjA(const ObjA& other)
: m0(other.m0), mF0(other.mF0), mF1(other.mF1), mF2(other.mF2), mF3(other.mF3) {}

// @ 0x00681b50
ObjB50& ObjB50::operator=(const ObjB50& x)
{
    m0 = x.m0;
    mV48 = &x.mV48;
    mF0 = x.mF0;
    mF1 = x.mF1;
    mF2 = x.mF2;
    mF3 = x.mF3;
    return *this;
}

// @ 0x00681c40
ObjA& ObjA::operator=(const ObjA& x)
{
    m0 = x.m0;
    mF0 = x.mF0;
    mF1 = x.mF1;
    mF2 = x.mF2;
    mF3 = x.mF3;
    return *this;
}

// @ 0x00681e80
ObjA* CopyBackwardA(ObjA* srcFirst, ObjA* srcLast, ObjA* dstLast)
{
    if (srcLast != srcFirst) {
        ObjA* d = dstLast;
        do {
            --srcLast;
            --d;
            *d = *srcLast;
        } while (srcLast != srcFirst);
        return d;
    }
    return dstLast;
}

// @ 0x00681f10
void SerCtx::WriteMap1700(Map2* map, IWrt* w)
{
    void* self = this;
    int n = (int)map->mnSize;
    w->Write(&n, 4);
    Node2* anchor = (Node2*)&map->mpAnchor;
    for (Node2* p = map->mpBegin; p != anchor; p = (Node2*)RBTreeIncrement(p)) {
        int key = p->mKey;
        Obj1700_s0068_1f10 tmp(p->mVal);
        w->Write(&key, 4);
        int len = (int)(tmp.mStr.mpEnd - tmp.mStr.mpBegin);
        WriteUint32(w, &len, 1, 0);
        if (len) w->Write(tmp.mStr.mpBegin, len);
        SaveVec390(self, &tmp.mF0, w);
        SaveVec390(self, &tmp.mF1, w);
    }
}

// @ 0x00682060
Cls60::~Cls60()
{}

// @ 0x006820c0
void SerCtx::WriteVec1800(VV12* v, IWrt* w)
{
    void* self = this;
    int n = (int)((v->mpEnd - v->mpBegin) / 0xc4);
    w->Write(&n, 4);
    Obj1800_s0068_1f10* last = (Obj1800_s0068_1f10*)v->mpEnd;
    for (Obj1800_s0068_1f10* p = (Obj1800_s0068_1f10*)v->mpBegin; p != last; p = (Obj1800_s0068_1f10*)((char*)p + 0xc4)) {
        Obj1800_s0068_1f10 tmp(*p);
        SaveObj500(self, &tmp.mBits[0], w);
        SaveObj500(self, &tmp.mBits[1], w);
        SaveObj500(self, &tmp.mBits[2], w);
        SaveObj500(self, &tmp.mBits[3], w);
        w->Write(&tmp.mW50, 4);
        WriteUint32(w, &tmp.mW5c, 1, 0);
        WriteUint32(w, &tmp.mW58, 1, 0);
        WriteUint32(w, &tmp.mW54, 1, 0);
        SaveObj5c0(self, &tmp.mM, w);
        WriteVecU32(w, &tmp.mF0);
        WriteVecU32(w, &tmp.mF1);
        WriteVecU32(w, &tmp.mF2);
        WriteVecU32(w, &tmp.mF3);
    }
}

// @ 0x006823f0
void SerCtx::WriteVecA(VV12* v, IWrt* w)
{
    int n = (int)((v->mpEnd - v->mpBegin) / 0x60);
    w->Write(&n, 4);
    ObjA_s0068_1f10* last = (ObjA_s0068_1f10*)v->mpEnd;
    for (ObjA_s0068_1f10* p = (ObjA_s0068_1f10*)v->mpBegin; p != last; p = (ObjA_s0068_1f10*)((char*)p + 0x60)) {
        ObjA_s0068_1f10 tmp(*p);
        w->Write(&tmp.mW0, 4);
        w->Write(&tmp.mW8, 4);
        w->Write(&tmp.mWc, 4);
        WriteVecU32(w, &tmp.mF0);
        WriteVecU32(w, &tmp.mF2);
    }
}

// @ 0x006825d0
void Map1::InsertHint(Node1** out, Node1* hint, int* key, char flag)
{
    Node1* anchor = (Node1*)&mpAnchor;
    Node1* pos = anchor;
    int side = 0;
    if (hint == mpBegin || hint == anchor) {
        if (mnSize != 0 && *key > mpBegin->mKey) { pos = mpBegin; side = 0; }
        else { pos = 0; side = 0; }
    } else {
        Node1* next = (Node1*)RBTreeIncrement(hint);
        if (*key > hint->mKey && next->mKey > *key) {
            if (hint->mpRight != 0) { pos = next; side = 1; }
            else { pos = hint; side = 0; }
        } else { pos = 0; side = 0; }
    }
    if (pos == 0) {
        PairOut2 pair;
        pair.first = 0;
        InsertUnique(&pair, key);
        *out = (Node1*)pair.first;
        return;
    }
    side = side || pos == anchor || *key < pos->mKey;
    Node1* nNew = (Node1*)CreateNode1(key);
    RBTreeInsert(nNew, pos, anchor, side);
    ++mnSize;
    *out = nNew;
}

// @ 0x00682740
VV12::VV12(const VV12& o)
{
    int n = (int)(o.mpEnd - o.mpBegin) / 0xc4;
    char* p = n ? (char*)EASTL_alloc6((uint32_t)n * 0xc4, g_allocTag, 0, 0, g_fileEASTL, 0xd1) : 0;
    mpBegin = p;
    mpEnd = p;
    mpCap = p + n * 0xc4;
    UninitCopy((void**)&mpEnd, o.mpBegin, o.mpEnd, p, (void*)&o);
}

// @ 0x00682800
void Map3::FreeNodes(Node3* p)
{
    while (p) {
        FreeNodes(p->mpRight);
        Node3* next = p->mpLeft;
        p->mVal.~Obj2A10();
        EASTL_dealloc(p);
        p = next;
    }
}

// @ 0x006828a0
void Map2::InsertHint(Node2** out, Node2* hint, int* key, char flag)
{
    Node2* anchor = (Node2*)&mpAnchor;
    int bIns;
    if (flag == 0 && hint != anchor && hint->mKey <= *key)
        bIns = 1;
    else
        bIns = 0;
    Node2* nNew = (Node2*)CreateNode2(key);
    RBTreeInsert(nNew, hint, anchor, bIns);
    ++mnSize;
    *out = nNew;
}

// @ 0x00682900
void Map2::InsertUnique(PairOut2* pairOut, const int* key)
{
    Node2* anchor = (Node2*)&mpAnchor;
    Node2* pos = anchor;
    int bLess = 1;
    Node2* n = mpRoot;
    if (n) {
        do {
            pos = n;
            bLess = (*key < n->mKey);
            n = bLess ? n->mpRight : n->mpLeft;
        } while (n);
    }
    Node2* found = pos;
    if (bLess) {
        if (pos == mpBegin) {
            int bIns = (pos != anchor && *key >= pos->mKey) ? 1 : 0;
            Node2* nNew = (Node2*)CreateNode2(key);
            RBTreeInsert(nNew, pos, anchor, bIns);
            ++mnSize;
            pairOut->first = nNew;
            pairOut->second = true;
            return;
        }
        pos = (Node2*)RBTreeDecrement(pos);
    }
    if (pos->mKey >= *key) {
        pairOut->first = pos;
        pairOut->second = false;
        return;
    }
    {
        int bIns = (found != anchor && *key >= found->mKey) ? 1 : 0;
        Node2* nNew = (Node2*)CreateNode2(key);
        RBTreeInsert(nNew, found, anchor, bIns);
        ++mnSize;
        pairOut->first = nNew;
        pairOut->second = true;
    }
}

// @ 0x00682a10
Obj2A10::Obj2A10(const Obj2A10& o)
: mStr(o.mStr), b10(o.b10), b11(o.b11), b12(o.b12), b13(o.b13), b14(o.b14),
      w18(o.w18), w1c(o.w1c), w20(o.w20), w24(o.w24), mM(o.mM), mVec(o.mVec) {}

// @ 0x00682af0
ObjC30_s0068_1f10* Map1::operator[](const int& key)
{
    Node1* anchor = (Node1*)&mpAnchor;
    Node1* pos = anchor;
    Node1* cur = mpRoot;
    while (cur) {
        if (cur->mKey < key) {
            pos = cur;
            cur = cur->mpLeft;
        } else {
            cur = cur->mpRight;
        }
    }
    if (pos == anchor || pos->mKey < key) {
        Node1* nNew = 0;
        Node1** out = &nNew;
        InsertHint(out, pos, (int*)&key, 0);
        return &nNew->mVal;
    }
    return &pos->mVal;
}

// @ 0x00682be0
Node2* Map2::Clone(Node2* src, Node2* parent)
{
    Node2* dst = (Node2*)CreateNode2(&src->mKey);
    dst->mpRight = 0;
    dst->mpLeft = 0;
    dst->mpParent = parent;
    dst->mColor = src->mColor;
    if (src->mpRight)
        dst->mpRight = Clone(src->mpRight, dst);
    Node2* cur = dst;
    for (Node2* sib = src->mpLeft; sib != 0; sib = sib->mpLeft) {
        Node2* n = (Node2*)CreateNode2(&sib->mKey);
        n->mpRight = 0;
        n->mpLeft = 0;
        n->mpParent = cur;
        n->mColor = sib->mColor;
        cur->mpLeft = n;
        if (sib->mpRight)
            n->mpRight = Clone(sib->mpRight, n);
        cur = n;
    }
    return dst;
}

// @ 0x00682ca0
void SerCtx::WriteMap2A10(Map3* map, IWrt* w)
{
    void* self = this;
    int n = (int)map->mnSize;
    w->Write(&n, 4);
    Node3* anchor = (Node3*)&map->mpAnchor;
    for (Node3* p = map->mpBegin; p != anchor; p = (Node3*)RBTreeIncrement(p)) {
        int key = p->mKey;
        Obj2A10 tmp(p->mVal);
        w->Write(&key, 4);
        int len = (int)(tmp.mStr.mpEnd - tmp.mStr.mpBegin);
        WriteUint32(w, &len, 1, 0);
        if (len) w->Write(tmp.mStr.mpBegin, len);
        WriteByte(w, &tmp.b10, 1);
        WriteByte(w, &tmp.b11, 1);
        WriteByte(w, &tmp.b12, 1);
        WriteByte(w, &tmp.b13, 1);
        WriteByte(w, &tmp.b14, 1);
        w->Write(&tmp.w18, 4);
        WriteUint32(w, &tmp.w18, 1, 0);
        WriteUint32(w, &tmp.w18, 1, 0);
        WriteUint32(w, &tmp.w18, 1, 0);
        SaveObj5c0(self, &tmp.mM, w);
        WriteVec1800(&tmp.mVec, w);
    }
}

// @ 0x00682e90
void SerCtx::LoadMap1(Map1* map, IRd* r)
{
    void* self = this;
    int count;
    r->Read(&count, 4);
    for (int i = 0; i < count; ++i) {
        int key;
        r->Read(&key, 4);
        ObjC30_s0068_1f10* val = map->operator[](key);
        if (val->mStr.mpBegin != val->mStr.mpEnd) {
            *val->mStr.mpBegin = 0;
            val->mStr.mpEnd = val->mStr.mpBegin;
        }
        int len;
        ReadInt32(r, &len, 1, 0);
        if (len) {
            StringResize(&val->mStr, 0);
            r->Read(val->mStr.mpBegin, len);
        }
        LoadEntries(self, &val->mVec, r);
    }
}

// @ 0x00683f80
Factory::~Factory()
{}

// @ 0x00684040
char Factory::Create(int* mgr, int** out, int a, int b)
{
    int* obj = (int*)EASTL_alloc6(0x80, (void*)"App/cConversationFactory", 0, 0, 0, 0);
    if (obj) obj = (int*)((CPropList*)obj)->ctor();
    int* v = (int*)((void* (__thiscall*)(void*))VT(mgr)[4])(mgr);
    obj[2] = v[0];
    obj[3] = v[1];
    obj[4] = v[2];
    if (((char (__thiscall*)(void*, int*, int*, int, int))VT(this)[9])(this, mgr, obj, a, b)) {
        *out = obj;
        ((void (__thiscall*)(void*))VT(obj)[0])(obj);
        return 1;
    }
    ((void (__thiscall*)(void*, int))VT(obj)[2])(obj, 1);
    return 0;
}

// @ 0x006840d0
void Factory::ReadMapA(MapA* map, IRd* r)
{
    uint32_t count;
    r->Read(&count, 4);
    for (uint32_t i = 0; i < count; ++i) {
        int key;
        r->Read(&key, 4);
        Obj1700_s0068_3f80* val = map->Idx(key);
        if (val->mStr.mpBegin != val->mStr.mpEnd) {
            *val->mStr.mpBegin = 0;
            val->mStr.mpEnd = val->mStr.mpBegin;
        }
        int len;
        ReadInt32(r, &len, 1, 0);
        if (len) {
            val->mStr.Resize(len, 0);
            r->Read(val->mStr.mpBegin, len);
        }
        ReadVecU32(&val->mF0, r);
        ReadVecU32(&val->mF1, r);
    }
}

// @ 0x006841a0
void Factory::WriteMapC(MapC* map, IWrt* w)
{
    int n = (int)map->mnSize;
    w->Write(&n, 4);
    NodeC* anchor = (NodeC*)&map->mpAnchor;
    for (NodeC* p = map->mpBegin; p != anchor; p = (NodeC*)RBTreeIncrement(p)) {
        int key = p->mKey;
        ObjY tmp(p->mVal);
        w->Write(&key, 4);
        int len = (int)(tmp.mVec.mpEnd - tmp.mVec.mpBegin);
        WriteUint32(w, &len, 1, 0);
        if (len) w->Write(tmp.mVec.mpBegin, len);
        WriteMap1700(&tmp.mMap, w);
    }
}

// @ 0x006842c0
int FactSer::ser_6842c0(int* a, int* b, int c, int d)
{
    (void)c; (void)d;
    int i = a ? ((int (__thiscall*)(void*, int))VT(a)[0xc / 4])(a, 0x355d6f5) : 0;
    void* u = ((void* (__thiscall*)(void*))VT(b)[0x18 / 4])(b);
    FUN_006841a0((void*)(i + 0x50), u);
    FUN_00682ca0((void*)(i + 0x18), u);
    FUN_00680fc0((void*)(i + 0x34), u);
    FUN_006823f0((void*)(i + 0x6c), u);
    return 1;
}

// @ 0x00684330
void MapB::InsertHint(NodeB** out, NodeB* hint, const void* pair, char flag)
{
    (void)flag;
    NodeB* anchor = (NodeB*)&mpAnchor;
    int* key = (int*)pair;
    if (hint == mpAnchor || hint == anchor) {
        if (mnSize == 0 || *key <= mpAnchor->mKey)
            goto UNIQUE;
        {
            int bIns = (mpAnchor == anchor || *key < mpAnchor->mKey) ? 0 : 1;
            NodeB* n = CreateNode(pair);
            RBTreeInsert(n, mpAnchor, anchor, bIns);
            ++mnSize;
            *out = n;
            return;
        }
    } else {
        NodeB* next = (NodeB*)RBTreeIncrement(hint);
        if (*key <= hint->mKey || next->mKey <= *key)
            goto UNIQUE;
        if (hint->mpRight == 0) {
            InsertPair(out, hint, pair, 0);
            return;
        }
        {
            NodeB* n = CreateNode(pair);
            RBTreeInsert(n, next, anchor, 0);
            ++mnSize;
            *out = n;
            return;
        }
    }
UNIQUE:
    {
        void* p[2];
        p[0] = 0;
        InsertUnique(p, pair, 0);
        *out = (NodeB*)p[0];
    }
}

// @ 0x006844a0
void* Map844::insert(void** out, void* at, int* key, char flag)
{
    int f = (!flag && at != (char*)this + 4 && *key >= *(int*)((char*)at + 0x10)) ? 1 : 0;
    void* node = allocNode(key);
    RBTreeInsert(node, at, (char*)this + 4, f);
    count += 1;
    *out = node;
    return out;
}

// @ 0x00684500
void MapC::InsertUnique(void* pairOut, const void* pair, char flag)
{
    (void)flag;
    const int* key = (const int*)pair;
    NodeC* anchor = (NodeC*)&mpAnchor;
    NodeC* pos = anchor;
    bool bLess = true;
    NodeC* n = mpRoot;
    if (n) {
        do {
            pos = n;
            bLess = (*key < n->mKey);
            n = bLess ? n->mpLeft : n->mpRight;
        } while (n);
    }
    NodeC* found = pos;
    if (bLess) {
        if (pos == mpBegin) {
            int bIns = (pos != anchor && *key >= pos->mKey) ? 1 : 0;
            NodeC* nn = CreateNode(pair);
            RBTreeInsert(nn, pos, anchor, bIns);
            ++mnSize;
            ((void**)pairOut)[0] = nn;
            *((uint8_t*)pairOut + 4) = 1;
            return;
        }
        pos = (NodeC*)RBTreeDecrement(pos);
    }
    if (pos->mKey >= *key) {
        ((void**)pairOut)[0] = pos;
        *((uint8_t*)pairOut + 4) = 0;
        return;
    }
    {
        int bIns = (found != anchor && *key >= found->mKey) ? 1 : 0;
        NodeC* nn = CreateNode(pair);
        RBTreeInsert(nn, found, anchor, bIns);
        ++mnSize;
        ((void**)pairOut)[0] = nn;
        *((uint8_t*)pairOut + 4) = 1;
    }
}

// @ 0x00684610
Obj2A10_s0068_3f80* MapB::Idx(const int& key)
{
    NodeB* anchor = (NodeB*)&mpAnchor;
    NodeB* pos = anchor;
    NodeB* cur = mpRoot;
    while (cur) {
        if (cur->mKey < key) cur = cur->mpRight;
        else { pos = cur; cur = cur->mpLeft; }
    }
    if (pos == anchor || key < pos->mKey) {
        struct { int k; Obj2A10_s0068_3f80 v; } p;
        p.k = key;
        NodeB* n;
        NodeB** out = &n;
        InsertHint(out, pos, &p.k, 0);
        return &(*out)->mVal;
    }
    return &pos->mVal;
}

// @ 0x00684740
void Factory::ReadMapB(MapB* map, IRd* r)
{
    uint32_t count;
    r->Read(&count, 4);
    for (uint32_t i = 0; i < count; ++i) {
        int key;
        r->Read(&key, 4);
        Obj2A10_s0068_3f80* val = map->Idx(key);
        if (val->mStr.mpBegin != val->mStr.mpEnd) {
            *val->mStr.mpBegin = 0;
            val->mStr.mpEnd = val->mStr.mpBegin;
        }
        int len;
        ReadInt32(r, &len, 1, 0);
        if (len) {
            val->mStr.Resize(len, 0);
            r->Read(val->mStr.mpBegin, len);
        }
        r->Read(&val->b10, 1);
        r->Read(&val->b11, 1);
        r->Read(&val->b12, 1);
        r->Read(&val->b13, 1);
        r->Read(&val->b14, 1);
        r->Read(&val->w[0], 4);
        ReadInt32(r, &val->w[3], 1, 0);
        ReadInt32(r, &val->w[2], 1, 0);
        ReadInt32(r, &val->w[1], 1, 0);
        LoadEntries(&val->mM, r);
        LoadObj1800(&val->mVec, r);
    }
}

// @ 0x00684890
void MapC::InsertHint(NodeC** out, NodeC* hint, const void* pair, char flag)
{
    (void)flag;
    NodeC* anchor = (NodeC*)&mpAnchor;
    int* key = (int*)pair;
    if (hint == mpAnchor || hint == anchor) {
        if (mnSize == 0 || *key <= mpAnchor->mKey)
            goto UNIQUE;
        {
            int bIns = (mpAnchor == anchor || *key < mpAnchor->mKey) ? 0 : 1;
            NodeC* n = CreateNode(pair);
            RBTreeInsert(n, mpAnchor, anchor, bIns);
            ++mnSize;
            *out = n;
            return;
        }
    } else {
        NodeC* next = (NodeC*)RBTreeIncrement(hint);
        if (*key <= hint->mKey || next->mKey <= *key)
            goto UNIQUE;
        if (hint->mpRight == 0) {
            ((Map844*)this)->insert((void**)out, hint, key, 0);
            return;
        }
        {
            NodeC* n = CreateNode(pair);
            RBTreeInsert(n, next, anchor, 0);
            ++mnSize;
            *out = n;
            return;
        }
    }
UNIQUE:
    {
        void* p[2];
        p[0] = 0;
        InsertUnique(p, pair, 0);
        *out = (NodeC*)p[0];
    }
}

// @ 0x00684980
ObjY* MapC::Idx(const int& key)
{
    NodeC* anchor = (NodeC*)&mpAnchor;
    NodeC* pos = anchor;
    NodeC* cur = mpRoot;
    while (cur) {
        if (cur->mKey < key) cur = cur->mpRight;
        else { pos = cur; cur = cur->mpLeft; }
    }
    if (pos == anchor || key < pos->mKey) {
        struct { int k; ObjY v; } p;
        p.k = key;
        NodeC* n;
        NodeC** out = &n;
        InsertHint(out, pos, &p.k, 0);
        return &(*out)->mVal;
    }
    return &pos->mVal;
}

// @ 0x00684a90
void Factory::ReadMapC(MapC* map, IRd* r)
{
    uint32_t count;
    r->Read(&count, 4);
    for (uint32_t i = 0; i < count; ++i) {
        int key;
        r->Read(&key, 4);
        ObjY* val = map->Idx(key);
        if (val->mVec.mpBegin != val->mVec.mpEnd) {
            *val->mVec.mpBegin = 0;
            val->mVec.mpEnd = val->mVec.mpBegin;
        }
        int len;
        ReadInt32(r, &len, 1, 0);
        if (len) {
            ((S8_s0068_3f80*)&val->mVec)->Resize(len, 0);
            r->Read(val->mVec.mpBegin, len);
        }
        ReadMapA((MapA*)&val->mMap, r);
    }
}

// @ 0x00684b40
int ser_684b40(int* a, int* b)
{
    int i = ((int (__thiscall*)(void*))VT(a)[0x1c / 4])(a);
    if (i) {
        i = ((int (__thiscall*)(void*, int))VT(*(void**)(i + 4))[0xc / 4])(*(void**)(i + 4), 0x226a1de);
        if (i) return 0;
    }
    void* u = ((void* (__thiscall*)(void*))VT(a)[0x18 / 4])(a);
    int j = b ? ((int (__thiscall*)(void*, int))VT(b)[0xc / 4])(b, 0x355d6f5) : 0;
    FUN_00684a90((void*)(j + 0x50), u);
    FUN_00684740((void*)(j + 0x18), u);
    FUN_00682e90((void*)(j + 0x34), u);
    FUN_00683ab0((void*)(j + 0x6c), u);
    return 1;
}

// @ 0x00684be0
int __cdecl TruncFloat_684be0(float p)
{
    return (int)p;
}

// @ 0x00687a00
extern "C" void Thunk_687a00(int n, uint32_t* base)
{
    ((VecU32G*)0x0152b5a0)->InsertRange(base, base + n, base);
}

// @ 0x00687a20
extern "C" void Iterate2(VecWStr* v0, VecU32* v1)
{
    if (g_count >= 0) {
        for (int i = 0; i <= g_count; ++i) {
            char* e = g_array + i * 0x28;
            if (e[0] != 0 && *(int*)(e + 4) != 0 &&
                *(int*)(e + 0x18) != *(int*)(e + 0x1c)) {
                v0->push_back(e + 0x18);
                uint32_t val = *(uint32_t*)(e + 4);
                uint32_t* p = v1->e;
                if (p < v1->c) {
                    v1->e = p + 1;
                    if (p) *p = val;
                } else {
                    v1->DoIns(p, &val);
                }
            }
        }
    }
}

// @ 0x006884f0
void EntrySet(int id, unsigned char b, int a3, const WStrRange* p4, const WStrRange* p5)
{
  int res = FUN_00687bc0(id);
  if (res == id)
    g_entryVec.mpBegin[res].b = b;
  g_entryVec.mpBegin[id].a3 = a3;
  if (res == id && p4 != (const WStrRange*)&g_entryVec.mpBegin[res].name)
    g_entryVec.mpBegin[res].name.Assign(p4->begin, p4->end);
  if (p5 != (const WStrRange*)&g_entryVec.mpBegin[id].other)
    g_entryVec.mpBegin[id].other.Assign(p5->begin, p5->end);
}

// @ 0x00688570
void cRendererCheat::Execute(EA::ArgScript::cArguments_s0068_7c20* args)
{
  if (mpEntries) {
    int n = args->NumArguments();
    if ((unsigned)(n - 4) <= 1) {
      int id = atol(args->operator[](1));
      int capped = FUN_00687bc0(id);
      EntryVec* vec = mpEntries;
      Entry40* e = vec->mpBegin + id;
      if (capped == id)
        e->b = 1;
      *(unsigned*)&e->a3 = strtoul(args->operator[](3), 0, 16);
      if (n == 5) {
        WStr tmp;
        WStr_Format(&tmp, L"", args->operator[](4));
        if (capped == id) {
          FUN_009309b0(&mStr, tmp.mpBegin, mMode, 4);
          e->name = mStr;
        }
      }
    }
  }
}

// @ 0x0068c140
uint64 __fastcall AtomicRead64(volatile uint64* p)
{
    volatile uint64 old;
    do {
        old = *p;
    } while (_InterlockedCompareExchange64((volatile __int64*)p, (__int64)old, (__int64)old) != (__int64)old);
    return old;
}

// @ 0x0068c1b0
uint64 __fastcall AtomicExchange64(volatile uint64* p, uint64 v)
{
    volatile uint64 old;
    do {
        old = *p;
    } while (_InterlockedCompareExchange64((volatile __int64*)p, (__int64)v, (__int64)old) != (__int64)old);
    return old;
}

// @ 0x0068c220
void FreeList::Drain()
{
    while (AtomicRead64(&mHead) != 0) {
        FreeItem* n = (FreeItem*)(uintptr_t_s0068_b150)AtomicRead64(&mHead);
        mHead = n->next;
        EAFree((void*)(uintptr_t_s0068_b150)AtomicRead64(&mHead));
    }
}

// @ 0x0068c280
void FreeList::Push(uint32 a, uint32 b)
{
    FreeItem* n = (FreeItem*)(uintptr_t_s0068_b150)AtomicRead64(&mHead);
    n->pad0 = a;
    n->pad4 = b;
    for (;;) {
        uint64 old = AtomicRead64(&mHead);
        n->next = old;
        uint64 want = AtomicRead64(&mHead);
        if (_InterlockedCompareExchange64((volatile __int64*)&mHead, (__int64)(old + 1), (__int64)want) == (__int64)want)
            break;
    }
}

// @ 0x0068c330
bool FreeQueue::TryPop(void** out)
{
    // Tagged-head CAS loop on the push side (+0x08): the popped node stores the next
    // tagged head at node+0x08, and the ABA tag (high dword) is bumped on every pop.
    uint64 raw = mPush;
    uint64 head = AtomicRead64(&raw);
    if ((uint32)head == 0)
        return false;
    for (;;) {
        uint64 headCopyRaw = head;
        uint64 headCopy = AtomicRead64(&headCopyRaw);
        uint64 nextRaw = *(volatile uint64*)((unsigned)headCopy + 8);
        uint64 next = AtomicRead64(&nextRaw);
        uint64 headCopy2Raw = headCopy;
        uint64 headCopy2 = AtomicRead64(&headCopy2Raw);
        uint64 desired = (uint64)(uint32)next | ((uint64)((uint32)(headCopy2 >> 32) + 1) << 32);
        if ((uint64)_InterlockedCompareExchange64((volatile __int64*)&mPush, (__int64)desired,
                                                  (__int64)headCopy2) == headCopy2) {
            uint64 nodeRaw = (uint64)(uint32)headCopy;
            uint64 node = AtomicRead64(&nodeRaw);
            out[0] = (void*)*(uint32*)(unsigned)node;
            out[1] = (void*)*(uint32*)((unsigned)node + 4);
            FreeListPush(this, (uint32)headCopy, (uint32)(headCopy >> 32));
            return true;
        }
        uint64 raw2 = mPush;
        head = AtomicRead64(&raw2);
        if ((uint32)head == 0)
            return false;
    }
}

// @ 0x0068c460
void FreeQueue::Drain()
{
    while (mPending != mPendingEnd) {
        void* item = ((void**)mPendingEnd)[-2];
        void (__cdecl* f)(void*) = ((void(__cdecl**)(void*))mPendingEnd)[-1];
        f(item);
        mPendingEnd = (char*)mPendingEnd - sizeof(uint64);
    }
    PopOut v;
    while (TryPop((void**)&v))
        ((void (__cdecl*)(void*))v.b)(v.a);
}

// @ 0x0068c4e0
void FreeQueue::Shutdown()
{
    void* p = mPending;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        EAFree(p);
    {
        PopOut v;
        while (TryPop((void**)&v)) {
        }
    }
    return DrainList();
}

// @ 0x0068c520
FreeQueue* FreeQueueCreate()
{
    FreeQueue* q = (FreeQueue*)EAAllocate(0x38, "App", 0, 0, 0, 0);
    if (q != 0) {
        ((Atomic64*)q)->Exchange(0);
        ((Atomic64*)((char*)q + 8))->Exchange(0);
        q->mPending = 0;
        q->mPendingEnd = 0;
        q->mCapacity = 0;
        q->m24 = 1;
        q->m28 = 5;
        q->m2c = 2;
        q->m30 = 0x32;
        return q;
    }
    return 0;
}

// @ 0x0068c590
void FreeQueue::Flush()
{
    PopOut v;
    while (TryPop((void**)&v)) {
        void** end = (void**)mPendingEnd;
        if (end < (void**)mCapacity) {
            mPendingEnd = end + 2;
            if (end != 0) {
                end[0] = v.a;
                end[1] = 0;
            }
        } else {
            ((PendingVec*)((char*)this + 0x10))->DoInsertValue(end, &v);
        }
    }
    uint32* propsRoot = *(uint32**)0x015fd918;
    uint32 n = m24;
    uint32 d = m28;
    uint32 a = m2c;
    uint32 b = m30;
    if (propsRoot != 0) {
        uint32* p = *(uint32**)((char*)propsRoot + 0x3c);
        n = *(uint32*)((char*)p + 0x134);
        d = *(uint32*)((char*)p + 0x138);
        a = *(uint32*)((char*)p + 0x13c);
        b = *(uint32*)((char*)p + 0x140);
    }
    uint32 count = (uint32)(((char*)mPendingEnd - (char*)mPending) >> 3);
    uint32 target = count;
    if (d != 0) {
        uint32 t = (count * n) / d + a;
        if (t <= count)
            target = t;
    }
    if (count - target > b)
        target = count - b;
    while (target != 0) {
        void* item = *(void**)((char*)mPendingEnd - 8);
        void (__cdecl* f)(void*) = *(void(__cdecl**)(void*))((char*)mPendingEnd - 4);
        mPendingEnd = (char*)mPendingEnd - 8;
        f(item);
        --target;
    }
}

// @ 0x0068d420
void __stdcall HashClearBuckets(void** buckets, uint32 n)
{
    for (uint32 i = 0; i < n; ++i) {
        void* node = buckets[i];
        while (node != 0) {
            void* b = *(void**)((char*)node + 4);
            void* c = *(void**)((char*)node + 0xc);
            void* next = *(void**)((char*)node + 0x14);
            if ((((char*)c - (char*)b) & ~1) > 2 && b != 0)
                EAFree(b);
            EAFree(node);
            node = next;
        }
        buckets[i] = 0;
    }
}

// @ 0x0068da70
extern "C" void FUN_0068da70(void* p1, void* p2, void* p3, void* p4)
{
    SPKeyFromName((u32*)p1, (wch*)p2, (u32)p3, (u32)p4);
}

// @ 0x0068da90
extern "C" void FUN_0068da90()
{
    SetNameCallbacks((void*)&FUN_0068da70, (void*)FUN_0068d1a0);
}

// @ 0x0068dab0
void IWriter::Emit(int a, int b, u8 c, u32 d, u8 e, u8 f)
{
    unsigned packed = ((((d & 0x1f) | 0x40) << 8 | c) << 8 | e) << 8 | f;
    WritePair(a, b, packed);
}

// @ 0x0068daf0
void RBSet::Insert(SetNode** pOut, SetNode* pos, const int* val, char bAllow)
{
    int canInsert;
    if (bAllow == 0 && pos != (SetNode*)&aRight && *val >= *(int*)((char*)pos + 0x10))
        canInsert = 1;
    else
        canInsert = 0;
    SetNode* n = (SetNode*)EASTL_alloc6(0x18, gAllocTag, 0, 0, gEASTLFile, 0xd1);
    int* pKey = (int*)((char*)n + 0x10);
    if (pKey) {
        pKey[0] = val[0];
        pKey[1] = val[1];
    }
    RBTreeInsert_s0068_d840(n, pos, &aRight, canInsert);
    SetNode** pp = pOut;
    mnSize += 1;
    *pp = n;
}

// @ 0x0068db70
NameMapCtor::NameMapCtor()
: mVt((void*)0x1403594), mUptime(0) {
    GetUptime(&mUptime);
}

// @ 0x0068dc90
Coder::~Coder()
{
    mBuf = (u8*)0x1403594;
    // nuke two embedded rbtrees at +0x24 and +0x08
    ((void(__thiscall*)(void*, void*))Nuke_9a9600)((char*)this + 0x24, *(void**)((char*)this + 0x30));
    ((void(__thiscall*)(void*, void*))Nuke_9a9600)((char*)this + 0x08, *(void**)((char*)this + 0x14));
}

// @ 0x0068dd10
void Citizen::Init(void* param_2, void* param_3, u32 param_4)
{
    u32* out = (u32*)param_2;
    out[1] = (u32)param_3;
    if ((param_4 & 0xc0000000) == 0x40000000)
        out[2] = param_4;
    else
        out[2] = 0x40010000;
    struct RBKeyPair {
        u32 key;
        u32 value;
    } key = { (param_4 >> 0x10) & 0xff, f04 };
    struct RBLookupResult {
        void* p;
        u8 found;
        u8 pad[3];
    } l8;
    ((void(__thiscall*)(void*, void*, void*, void*))Sub68dc00)((char*)this + 8, &l8, &key, out);
    SetNode* node = (SetNode*)l8.p;
    if (!l8.found)
        node->mVal += 1;
    *out = node->mVal;
    void* mgr = GetResourceManager();
    if (mgr != 0) {
        while (ResourceManagerAdd(out) != 0) {
            node->mVal += 1;
            *out = node->mVal;
        }
    }
}

// @ 0x0068ddc0
void Coder::MaskInit()
{
    u32 v = f40;
    u32 i = 0;
    if (v & 0xffff0000) { i = 0x10; v >>= 16; }
    if (v & 0xff00) { i += 8; v >>= 8; }
    if (v & 0xf0) { i += 4; v >>= 4; }
    if (v & 0xc) { i += 2; v >>= 2; }
    if (v & 2) i += 1;
    u32 m = gMaskTable[i];
    f50 = m;
    f3c = m;
    f44 = 1;
    f30 = 0x811c9dc5;
    f48 = ~(f4c - 1);
}

// @ 0x0068de20
bool Coder::EncodeBit(u8 b)
{
    bool res = true;
    int n = 8;
    do {
        if (n == 0)
            return res;
        u32 cur = f3c;
        if (f40 <= cur) {
            do {
                if ((cur & 1) == 0)
                    cur = cur >> 1;
                else
                    cur = (cur >> 1) ^ f50;
                f3c = cur;
                if (cur == f50) {
                    f44 = f44 << 1;
                    f48 = f48 << 1;
                }
            } while (f40 <= cur);
        }
        u32 h = f30 * 0x1000193;
        u8* pb = mBuf + f3c;
        f30 = h;
        f30 = ((~f48 & f3c & 0xff) | (*pb & f48)) ^ h;
        u8 tb;
        if (((h >> 0xf) ^ (u32)b) & 1)
            tb = (u8)f44;
        else
            tb = 0;
        b = b >> 1;
        *pb = (u8)((~(u8)f44 & *pb) | tb);
        u32 c2 = f3c;
        if ((c2 & 1) == 0)
            c2 = c2 >> 1;
        else
            c2 = (c2 >> 1) ^ f50;
        f3c = c2;
        res = true;
        if (c2 == f50) {
            f44 = f44 << 1;
            f48 = f48 << 1;
            res = (f44 != f4c);
        }
        n -= 1;
    } while (res);
    return false;
}

// @ 0x0068df00
void Coder::Flush()
{
    volatile u32 saved = f44;
    volatile u8 dl = 0;
    do {
        u32 cur = f3c;
        if (f40 <= cur) {
            do {
                if ((cur & 1) != 0)
                    cur = (cur >> 1) ^ f50;
                else
                    cur = cur >> 1;
                f3c = cur;
                if (cur == f50) {
                    f44 = f44 << 1;
                    f48 = f48 << 1;
                }
            } while (f40 <= cur);
        }
        if (saved == f44) {
            u32 h = f30 * 0x1000193;
            u8* pb = mBuf + f3c;
            f30 = h;
            f30 = ((((~f48 & f3c) | (*pb & f48))) & 0xff) ^ h;
            u8 b = (u8)f44;
            u32 bit = 0 - (u32)((((h >> 0xf) ^ (u32)dl) & 1) != 0);
            *pb = (u8)(((~b) & *pb) | (u8)(bit & f44));
            dl = (u8)(dl >> 1);
            u32 c2 = f3c;
            if ((c2 & 1) != 0)
                c2 = (c2 >> 1) ^ f50;
            else
                c2 = c2 >> 1;
            f3c = c2;
            if (c2 == f50) {
                f44 = f44 << 1;
                f48 = f48 << 1;
            }
        }
    } while (saved == f44);
}

// @ 0x0068dfd0
bool Coder::DecodeBit(u8* out)
{
    bool res = true;
    int n = 8;
    u8 bval = 0;
    do {
        if (n == 0) {
            *out = bval;
            return res;
        }
        u32 cur = f3c;
        if (f40 <= cur) {
            do {
                if ((cur & 1) == 0)
                    cur = cur >> 1;
                else
                    cur = (cur >> 1) ^ f50;
                f3c = cur;
                if (cur == f50) {
                    f44 = f44 << 1;
                    f48 = f48 << 1;
                }
            } while (f40 <= cur);
        }
        u32 cur2 = f3c;
        u32 mask = f48;
        u32 byte = mBuf[cur2];
        u32 h = ((~mask & cur2 & 0xff) | (byte & mask)) ^ f30 * 0x1000193;
        u32 bitv = f44;
        f30 = h;
        u8 tb;
        if ((h & 0x8000) == 0)
            tb = (u8)(-((byte & bitv) != 0) & 0x80);
        else
            tb = (u8)((-((byte & bitv) != 0) & 0x80u) + 0x80);
        bval = (u8)(bval >> 1) | tb;
        u32 c2 = cur2;
        if ((c2 & 1) == 0)
            c2 = c2 >> 1;
        else
            c2 = (c2 >> 1) ^ f50;
        f3c = c2;
        res = true;
        if (c2 == f50) {
            res = (bitv * 2 != f4c);
            f44 = bitv * 2;
            f48 = mask * 2;
        }
        n -= 1;
    } while (res);
    *out = bval;
    return false;
}

// @ 0x0068e0c0
bool Coder::DecodeFinish()
{
    u32 uVar1 = f44;
    for (;;) {
        if (uVar1 != f44)
            return true;
        u32 cur = f3c;
        if (f40 <= cur) {
            do {
                if ((cur & 1) == 0)
                    cur = cur >> 1;
                else
                    cur = (cur >> 1) ^ f50;
                f3c = cur;
                if (cur == f50) {
                    f44 = f44 << 1;
                    f48 = f48 << 1;
                }
            } while (f40 <= cur);
        }
        if (uVar1 != f44)
            return true;
        u32 cur2 = f3c;
        u32 mask = f48;
        u32 byte = mBuf[cur2];
        u32 h = ((~mask & cur2 & 0xff) | (byte & mask)) ^ f30 * 0x1000193;
        f30 = h;
        u8 tb;
        if ((h & 0x8000) == 0)
            tb = (u8)(-((byte & uVar1) != 0) & 0x80);
        else
            tb = (u8)((-((byte & uVar1) != 0) & 0x80u) + 0x80);
        u32 c2 = cur2;
        if ((c2 & 1) == 0)
            c2 = c2 >> 1;
        else
            c2 = (c2 >> 1) ^ f50;
        f3c = c2;
        if (c2 == f50) {
            f44 = uVar1 * 2;
            f48 = mask * 2;
            if (uVar1 * 2 == f4c)
                return false;
        }
        if (tb != 0)
            return false;
    }
}

// @ 0x0068e1a0
char Coder::Serialize(void* io, int mode)
{
    u32 ver = 4;
    if (mode != 0 && f58 != f5c)
        return 0;
    if (mode == 1)
        ver = 6;
    else if (mode == 2)
        ver = 5;

    u8 buf[0x2a70];
    memset(buf, 0, 0x2a70);
    u32 m14 = f14;
    u32 m18 = f18;
    u32 m1c = f1c * 8;
    *(u32*)(buf + 0x10) = m14;
    *(u32*)(buf + 0x14) = m18;
    *(u32*)(buf + 0x18) = m1c;
    if (f20 != 0)
        *(u32*)(buf + 0x438) = 8;

    SerCtx_s0068_d840 ctx;
    ctx.ctor87cf40();
    ctx.m87cf60(io);
    if (!ctx.m87d2a0((int)ver, 1)) {
        ctx.m87d260();
        return 0;
    }
    int prod = (int)(m1c * m18);
    int n = (prod + (prod >> 31 & 7)) >> 3;
    char bl = (char)(ctx.m87d030(buf, mBuf, n) != 0);
    ctx.m87cff0();

    if (f55 != 0 && f58 != f5c) {
        u32 h = Sub932da0(gSerTag, 4, 0xffffffff, 0);
        h = Sub932da0((void*)f58, f5c - f58, h, 1);
        u32 len = f5c - f58;
        bool r = (bl != 0);
        if (r) {
            r = ((StreamFn2)VFN(io, 0x28))(io, 0, 2);
            if (r) {
                u32 tmp = len;
                r = WriteUint32_s0068_d840(io, &tmp, 1, 0) != 0;
                if (r) {
                    r = ((StreamFn2)VFN(io, 0x38))(io, gSerTag, 4);
                    if (r) {
                        r = ((StreamFn2)VFN(io, 0x38))(io, (void*)f58, (int)len);
                        if (r) {
                            tmp = h;
                            r = WriteUint32_s0068_d840(io, &tmp, 1, 0) != 0;
                        }
                    }
                }
            }
        }
        bl = r ? 1 : 0;
    }
    ctx.m87d260();
    return bl;
}

// @ 0x0068e3b0
int Coder::Read(void* dst, u32 n)
{
    if (f55 != 0) {
        int d = (int)(f5c - f6c) - (int)f58;
        u32 avail = (u32)(d - 8);
        if (f56 != 0)
            avail = (u32)(d - 0xc);
        if (f24 == 3 && (int)avail >= 0) {
            if (avail < n)
                n = avail;
            MemcpyT2(dst, (void*)(f58 + f6c), n);
            f6c += n;
            return (int)n;
        }
        f24 = 1;
        return -1;
    }
    if (f24 == 3) {
        u32 a = f38;
        u32 b = f34;
        if (a <= b) {
            if (b < a + n)
                n = b - a;
            u8 c = 1;
            u8* p = (u8*)dst;
            if (p != p + n) {
                do {
                    if (c == 0)
                        goto fail;
                    c = DecodeBit(p) ? 1 : 0;
                    p += 1;
                } while (p != (u8*)dst + n);
                if (c == 0)
                    goto fail;
            }
            f38 += n;
            void* r = Sub932df0(dst, n, f28, f2c, 0);
            *(void**)((char*)this + 0x28) = r;
            return (int)n;
        }
    }
fail:
    f24 = 1;
    return -1;
}

// @ 0x0068e490
char Coder::Verify(char p)
{
    if (f55 != 0) {
        if (f24 != 3)
            return false;
        if ((u32)(f5c - f6c - f58) < 8)
            return false;
        if (f56 != 0) {
            int n = f5c - f58;
            int ptr = f58;
            u32 h = Sub932da0((void*)mBuf, f04 - (int)mBuf, gHMNameMagic, 0);
            h = Sub932da0((void*)(ptr + 8), n - 0x14, h, 1);
            if (*(u32*)(n + ptr - 0xc) != h)
                return false;
        }
        {
            int e = f5c - 8;
            if (*(int*)e != (f5c - f58) - 0x10)
                return false;
            u32 tag = *(u32*)(e + 4);
            if (tag != 0xe6adc7ce && tag != 0xe6f1a35c)
                return false;
        }
        f24 = 1;
        return true;
    }

    if (f24 != 3)
        return false;
    {
        u32 a;
        char ok = 1;
        while (f38 < f34) {
            ok = (Read(&a, 4) != -1);
            if (!ok)
                break;
        }
        u32 wantA = f28;
        u32 wantB = f2c;
        f34 = 0xffffffff;
        if (!ok)
            goto fail;
        {
            u32 b;
            if (Read(&b, 4) == -1)
                goto fail;
            u32 c[2];
            if (Read(c, 8) == -1)
                goto fail;
            if (b != 0x2450d16)
                goto fail;
            if (c[0] != wantA)
                goto fail;
            if (c[1] != wantB)
                goto fail;
            f24 = 1;
            if (p != 0)
                DecodeFinish();
            return true;
        }
    }
fail:
    f24 = 1;
    return false;
}

// @ 0x0068e610
Coder::Coder()
{
    mBuf = 0;
    f04 = 0; f08 = 0;
    f14 = 0; f18 = 0;
    f20 = 0;
    f24 = 0;
    f28 = 0xffffffff;
    f2c = 0xffffffff;
    f30 = 0;
    f34 = 0;
    f38 = 0;
    f3c = 0;
    f40 = 0;
    f44 = 0;
    f48 = 0;
    f4c = 8;
    f50 = 0;
    f55 = 0;
    f56 = 0;
    f58 = 0;
    f5c = 0;
    f60 = 0;
    f6c = 0;
}

// @ 0x0068e670
char Coder_s0068_e670::ReadHeader(int* out)
{
    u32 hdr[2];
    if (f55 != 0) {
        f56 = 0;
        if (mState != 1) return 0;
        if (mData.mpBegin == mData.mpEnd) return 0;
        const u8* p = mStream.mpBegin;
        bool a = (memcmp(p, gMagicA, 8) == 0);
        bool b = (memcmp(p, gMagicB, 8) == 0);
        u32 n = (u32)(mStream.mpEnd - mStream.mpBegin);
        if (n < 0x10 || (!a && !b)) { mState = 1; return 0; }
        f6c = 8;
        if (out) *out = (int)(n - 0x10);
        if (b) return 1;
        u32 m = n - 0x14;
        if (m == 0) return 0;
        if (out) *out = (int)m;
        f56 = 1;
        return 1;
    }
    if (mState != 1) return 0;
    if (mData.mpBegin == mData.mpEnd) return 0;
    if ((u32)(mData.mpEnd - mData.mpBegin) != f40) return 0;
    InitMask();
    f34 = 0xffffffff;
    mState = 3;
    if (Read(hdr, 8) == 0) { mState = 1; return 0; }
    if (hdr[0] != 0x02450d16) {
        InitMask();
        f48 = ~f44;
        f34 = 0xffffffff;
        mState = 3;
        if (Read(hdr, 8) == 0) { mState = 1; return 0; }
        if (hdr[0] != 0x02450d16) { mState = 1; return 0; }
    }
    f34 = hdr[1];
    f38 = 0;
    mHashLo = 0xffffffff;
    mHashHi = 0xffffffff;
    if (out) *out = (int)hdr[1];
    return 1;
}

// @ 0x0068e8a0
void VecU8::AssignFill(u32 count, const void* pval)
{
    u8* e = mpEnd;
    if (count > (u32)(e - mpBegin)) {
        DoInsertValues(e, (u32)(mpBegin - e) + count, pval);
        return;
    }
    erase(mpBegin + count, mpEnd);
}

// @ 0x0068e8f0
int Coder_s0068_e670::InitBitmap(int width, int height, int bits, u8 flag)
{
    mStride = (u32)(bits / 8);
    u32 total = mStride * (u32)width * (u32)height;
    mHeight = (u32)height;
    mData.clear();
    mWidth = (u32)width;
    mFlag = flag;
    if (total > mData.size()) {
        u8 zero = 0;
        mData.DoInsertValues(mData.mpEnd, (u32)(mData.mpBegin - mData.mpEnd) + total, &zero);
    } else {
        mData.erase(mData.mpBegin + total, mData.mpEnd);
    }
    f40 = total;
    mState = 1;
    return (int)mData.mpBegin;
}

// @ 0x0068eb50
char Coder_s0068_e670::OpenData(const char* path)
{
    f55 = 0;
    if (!path) return 0;
    u32 frame;
    Hinter q;
    q.Open(path);
    char ok = q.GetFrame(0x32, &frame);
    if (ok && frame != 0) {
        Entry* e = q.GetEntry(0);
        if (e) {
            if (e->bits == 0x18 || e->bits == 0x20) {
                mWidth = e->width;
                mHeight = e->height;
                mStride = e->bits / 8;
                mFlag = (e->f438 == 8);
                u32 total = mStride * mHeight * e->width;
                mData.resize(total);
                f40 = 0;
                mState = 0;
                ok = q.Read(e, mData.mpBegin, (int)(mStride * mWidth));
                if (ok) {
                    f40 = total;
                    if (e->type == 0x504e47 && ReadData((void*)path))
                        f55 = 1;
                    mState = 1;
                }
                q.Free(e);
            } else {
                ok = 0;
            }
        }
    }
    return ok;
}

// @ 0x0068eca0
char Coder_s0068_e670::WriteData(const u8* data, u32 n)
{
    if (f55) {
        if (mState != 2) return 0;
        mStream.resize((u32)(mStream.mpEnd - mStream.mpBegin) + n);
        MemcpyT(mStream.mpEnd - n, data, n);
        return 1;
    }
    if (mState != 2) return 0;
    char ok = 1;
    const u8* p = data;
    const u8* end = data + n;
    while (p != end) {
        if (!ok) break;
        ok = EncodeBit(*p++);
    }
    if (ok) {
        f34 += n;
        u64 h = CRC64(data, n, mHashLo, mHashHi, 0);
        mHashLo = (u32)h;
        mHashHi = (u32)(h >> 32);
    }
    mState = ok ? mState : 1;
    return ok;
}

// @ 0x0068ed70
char Coder_s0068_e670::Finalize(char flag)
{
    if (f55) {
        if (mState != 2) return 0;
        if ((u32)(mStream.mpEnd - mStream.mpBegin) < 8) return 0;
        if (f56) {
            u32 crc = CRC32(mData.mpBegin, (u32)(mData.mpEnd - mData.mpBegin), gHNMagic, 0);
            crc = CRC32(mStream.mpBegin + 8, (u32)(mStream.mpEnd - mStream.mpBegin) - 8, crc, 1);
            mStream.resize((u32)(mStream.mpEnd - mStream.mpBegin) + 4);
            *(u32*)(mStream.mpEnd - 4) = crc;
        }
        u32 n = (u32)(mStream.mpEnd - mStream.mpBegin);
        mStream.resize(n + 8);
        *(u32*)(mStream.mpEnd - 8) = n - 8;
        *(u32*)(mStream.mpEnd - 4) = gTailTag;
        mState = 1;
        return 1;
    }
    if (mState != 2) return 0;
    u32 saved = f34;
    u32 buf[3];
    buf[0] = 0x02450d16;
    buf[1] = mHashLo;
    buf[2] = mHashHi;
    char ok = WriteData((u8*)buf, 4);
    if (ok) ok = WriteData((u8*)&buf[1], 8);
    if (ok && flag) Flush();
    InitMask();
    u32 tail[2];
    tail[0] = 0x02450d16;
    tail[1] = saved;
    if (ok && WriteData((u8*)tail, 8)) {
        mState = 1;
        return 1;
    }
    mState = 1;
    return 0;
}

// @ 0x0068eef0
char Coder_s0068_e670::Begin(char external)
{
    f55 = external;
    if (external) {
        f56 = 0;
        if (mState != 1) return 0;
        if (mData.mpBegin == mData.mpEnd) return 0;
        mState = 2;
        mStream.resize(8);
        ((u32*)mStream.mpBegin)[0] = ((u32*)gMagicB)[0];
        ((u32*)mStream.mpBegin)[1] = ((u32*)gMagicB)[1];
        f56 = 1;
        return 1;
    }
    mStream.clear();
    if (mState != 1) return 0;
    if (mData.mpBegin == mData.mpEnd) return 0;
    if ((u32)(mData.mpEnd - mData.mpBegin) != f40) return 0;
    InitMask();
    u32 local[2];
    local[0] = 0x02450d16;
    local[1] = 0xffffffff;
    mState = 2;
    if (WriteData((u8*)local, 8)) {
        mHashLo = 0xffffffff;
        mHashHi = 0xffffffff;
        f34 = 0;
        return 1;
    }
    mState = 1;
    return 0;
}

// @ 0x0068eff0
RefObj::RefObj()
: mMutex(0, true), mJob(0) {
}

// @ 0x0068f050
RefObj::~RefObj()
{
    if (mJob)
        ((CJob*)mJob)->Release();
}

// @ 0x0068f0b0
bool CJobHolder::SetJob(void* target, void* job)
{
    struct JobPtr {
        void* mJob;
        __forceinline JobPtr(void* p) : mJob(p) {
            if (mJob) ((FnAddRef)AddRef_68F950)(mJob);
        }
        __forceinline ~JobPtr() {
            if (mJob) ((FnRelease)Release_690120)(mJob);
        }
    };
    mMutex.Lock((unsigned)0x014036f0);
    void* old = mJob;
    JobPtr held(old);                                   // strong ref to the old job
    if (job != mJob) {
        JobPtr add(job);                                // (acquire, freed below)
        mJob = job;
        if (old) ((FnRelease)Release_690120)(old);
    }
    mMutex.Unlock();
    ((FnAddWeak)AddWeakDependency_6913C0)(target, old);
    return true;
}

// @ 0x0068f180
bool CJobHolder2::Attach(void* job)
{
    CJobHolder* holder = mHolder;
    if (holder->SetJob(mArg, job)) {
        return ((FnContinuation)Continuation_68F9F0)(job, (void*)0x00753fb0, this);
    }
    return false;
}

// @ 0x0068f1d0
JobLock::JobLock(void* out, void* job, void* refObj)
{
    vtbl0 = (void*)0x013f1ab0;
    vtbl1 = (void*)0x013ef094;
    _InterlockedExchange(&mRef, 0);
    vtbl0 = (void*)0x014036fc;
    vtbl1 = (void*)0x014036f8;
    mRefObj = refObj;
    if (refObj)
        _InterlockedIncrement((volatile long*)((char*)refObj + 4));
    mJob = job;
    if (job) ((FnAddRef)AddRef_68F950)(job);
    *(void**)out = (void*)0x0068f1c0;
    *((void**)out + 1) = this;
    ((FnLockDec)LockDec_68F9B0)(this);
}
