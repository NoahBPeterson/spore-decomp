// src/game/SPGonzago/_at_00bc0000.cpp -- migrated from slice(s) s00bcc010, s00bcb0b0, s00bca040, s00bc8ff0, s00bc8400, s00bc74d0, s00bc6360, s00bc5730, s00bc4730, s00bc34c0, s00bc2570, s00bc1690, s00bbf630 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00bc0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cPropertyList.h"
#include "SP/cSPGameDataUFO.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete__(void* p);                                                   // 0x00f47380
extern "C" void* FUN_006782c0(void* first, void* last, void* result);                          // 0x006782c0
extern "C" void  FUN_00829110(void* dest, void* first, void* last, void* a, void* b);          // 0x00829110
extern "C" void* FUN_00b93c60(void* self, int n, void* alloc);                                 // 0x00b93c60
extern "C" void* FUN_00bbc700(void* a, void* b, float x, float y, float z);                    // 0x00bbc700
extern "C" void* FUN_00c6fe00(void* p);                                                        // 0x00c6fe00
extern "C" void* FUN_0102f810(void* p);                                                        // 0x0102f810
extern "C" float FUN_0102f8c0(void* p);                                                        // 0x0102f8c0
extern "C" void* FUN_00472b80(void* out, void* m, float a);                                    // 0x00472b80
extern "C" void* FUN_01021260();                                                               // 0x01021260 GetActivePlanet
extern "C" void* FUN_010212a0();                                                               // 0x010212a0 GetActivePlanetRecord
extern "C" void* FUN_01021370();                                                               // 0x01021370 GetPlayerHomePlanet
extern "C" void* FUN_0067de30();                                                               // 0x0067de30 PropertyManager
extern "C" float g_kEpsilon;   // 0x014666c0
extern "C" void* FUN_00b3d300();   // 0x00b3d300 SP::NounManager
extern "C" void* FUN_00b3d350();   // 0x00b3d350 SP::PlanetModel
#include <math.h>
#include <stddef.h>
#include <string.h>
#include "EA/Allocator/FixedAllocatorBase.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cHierGrid.h"
#include <intrin.h>
#include "SP/cGameData.h"
#include "SP/cSpatialObject.h"
#include "EA/Variant.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCity.h"
#include "SP/cCombatant.h"
#include "SP/cSPTimer.h"
#include "SP/cTribeTool.h"
#include "SP/cVehicle.h"
#pragma pack(push, 4)

// ---- items of slice s00bbf630 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  uint;
extern "C" void* EAAllocate(uint size, const char* name, int a, int b, void* site, int line); // 0x00f473a0
extern "C" void  operator_delete__(void* p);                                                   // 0x00f47380
extern "C" void* FUN_006782c0(void* first, void* last, void* result);                          // 0x006782c0
extern "C" void  FUN_00829110(void* dest, void* first, void* last, void* a, void* b);          // 0x00829110
extern "C" void* FUN_00b93c60(void* self, int n, void* alloc);                                 // 0x00b93c60
extern "C" void* FUN_00bbc700(void* a, void* b, float x, float y, float z);                    // 0x00bbc700
extern "C" void* FUN_00c6fe00(void* p);                                                        // 0x00c6fe00
extern "C" void* FUN_0102f810(void* p);                                                        // 0x0102f810
extern "C" float FUN_0102f8c0(void* p);                                                        // 0x0102f8c0
extern "C" void* FUN_00472b80(void* out, void* m, float a);                                    // 0x00472b80
extern "C" void* FUN_01021260();                                                               // 0x01021260 GetActivePlanet
extern "C" void* FUN_010212a0();                                                               // 0x010212a0 GetActivePlanetRecord
extern "C" void* FUN_01021370();                                                               // 0x01021370 GetPlayerHomePlanet
extern "C" void* FUN_0067de30();                                                               // 0x0067de30 PropertyManager
extern "C" float g_kEpsilon;   // 0x014666c0
struct cSPGameDataUFO {
    int AddRef();      // 0x00801920
};
struct Property {
    void*    mpData;      // +0x00
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10
    uint16_t mnType;      // +0x12
};
struct cPropertyList {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, void** out);          // vtable +0x24
};
struct PtrVector {
    void** mpBegin;    // +0x00
    void** mpEnd;      // +0x04
    void** mpCap;      // +0x08

    void   erase(void* first, void* last);   // 0x00e25bd0
    void   push_back(void* src);             // 0x00aea5d0
};
struct SimHash {
    uint32_t pad00;
    uint32_t mpBuckets;    // +0x04
    uint32_t mnBucket;     // +0x08
    uint32_t mUnknown0c;   // +0x0c

    void           find(void* out, const void* key);                    // 0x00a3b2c0
    void           insert(void* iterOut, const void* value, void* key); // 0x00bbf070
    void           deallocate(uint32_t buckets, uint32_t count);        // 0x01068400
    int*           FUN_00bbf630(const int* key);
};
struct RBNodeBase {
    RBNodeBase* mpNodeRight;    // +0x00
    RBNodeBase* mpNodeLeft;     // +0x04
    RBNodeBase* mpNodeParent;   // +0x08
    uint8_t     mColor;         // +0x0c
};
struct RBTree {
    int         mCompare;     // +0x00
    RBNodeBase  mAnchor;      // +0x04
    uint32_t    mnSize;       // +0x14

    void nuke(void* node);    // 0x009a9600
};
struct EntrySub {
virtual void  s00();
virtual void  s04();
virtual void  s08();
virtual void  s0c();
virtual void  s10();
virtual void  s14();
virtual void  s18();
virtual void  s1c();
virtual void  s20();
virtual void  s24();
virtual void  s28();
virtual void* s2c();
virtual void  s30();
virtual void  s34();
virtual void  s38(void* p);
virtual void  s3c(void* p);
    virtual void  s40(float f);
};
struct Entry {
    virtual void  v00();                     // +0x00 AddRef
    virtual void  v04();                     // +0x04 Release
    virtual void  v08();                     // +0x08
    virtual void* v0c(void* a);              // +0x0c
virtual void  v10();
virtual void  v14();
virtual void  v18();
virtual void  v1c();
virtual void  v20();
virtual void  v24();
virtual void  v28();
virtual void  v2c();
virtual void  v30();
virtual void  v34();
virtual void  v38();
virtual void  v3c();
virtual void  v40();
virtual void  v44();
    virtual void  v48(void* a);              // +0x48
    virtual void* v4c();                     // +0x4c
    uint8_t   pad04[0x34 - 0x04];            // data between the vptr and the sub-object
    EntrySub  mSub;                          // +0x34 (own vptr; slots 0x2c/0x38/0x3c/0x40)
    uint8_t   pad38[0x68 - 0x38];
    void**    mpVec;                         // +0x68
    void*     pad6c[2];
    uint8_t   pad74[0x90 - 0x74];
    cPropertyList* mpPropList;               // +0x90
    uint8_t   pad94[0x1ec - 0x94];
    int32_t   m1ec;                          // +0x1ec

    void* FillPair(void* p);                 // 0x00bfe260
    void  FUN_00bfe220(void* p);             // 0x00bfe220
    void  FUN_00bff6e0(void* p);             // 0x00bff6e0
    void  SetState(int s);                   // 0x00bfdfb0
    void  FUN_00bfeaf0(void* p);             // 0x00bfeaf0
};
struct OtherRec {
    void*   mpNoun;     // +0x00
    int32_t mState;     // +0x04
};
struct OtherVec {
    OtherRec** mpBegin;   // +0x00
    OtherRec** mpEnd;     // +0x04
    OtherRec** mpCap;     // +0x08
};
struct GameDataVector {
    uint32_t m00;
    void**   mpBegin;   // +0x04
    void**   mpEnd;     // +0x08
};
extern "C" void* FUN_00b3d300();   // 0x00b3d300 SP::NounManager
struct cGameNounManager {
    void* GetGameDataVector(void* a, void* b, void* c, void* d, uint32_t type);  // 0x00b21340
    void  RemoveNoun(void* noun);                                                // 0x00b225d0
    void* CreateNoun(uint32_t type);                                             // 0x00b20c60
};
inline cGameNounManager* SP_NounManager() { return (cGameNounManager*)FUN_00b3d300(); }
struct WNode {
    uint8_t  pad00[0x3c];
    void**   mpBegin;   // +0x3c
    void**   mpEnd;     // +0x40

    void* FUN_00ff0420();   // 0x00ff0420
};
struct UintArray {
    float* FUN_00572590();   // 0x00572590
};
struct PlanetRecord {
    uint32_t   flags4;      // +0x04
    uint8_t    pad08[0x0c - 0x08];
    float      f0c[4];      // +0x0c
    uint8_t    p1c;         // +0x1c
    uint8_t    pad1d[0x6c - 0x1d];
    float      f_6c;        // +0x6c
    uint8_t    pad70[0x90 - 0x70];
    cPropertyList* mpPropList;  // +0x90
    uint8_t    pad94[0xb0 - 0x94];
    uint32_t   p_b0;        // +0xb0
    uint32_t   p_b4;        // +0xb4
    uint8_t    padb8[0x13c - 0xb8];
    void*      p_13c;       // +0x13c

    OtherVec* FUN_00c71020();    // 0x00c71020
    int    FUN_00c70e00();       // 0x00c70e00
    int    FUN_00c710c0();       // 0x00c710c0
    WNode* FUN_00c71030(int i);  // 0x00c71030
    void   FUN_00c72dd0(void* node);  // 0x00c72dd0
    void*  FUN_00b8de30();       // 0x00b8de30
};
extern "C" void* FUN_00b3d350();   // 0x00b3d350 SP::PlanetModel
struct PropMgr {
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual void d28();
virtual void d29();
virtual void d30();
virtual void d31();
virtual void d32();
virtual void d33();
virtual void d34();
virtual void d35();
virtual void d36();
virtual void d37();
virtual void d38();
virtual void d39();
virtual void d40();
virtual void d41();
virtual void d42();
virtual void d43();
    virtual int  GetPropertyVector(void* out);   // vtable +0xb0
};
struct PlanetModelObj {
    virtual void d00();
    uint8_t pad04[0x24 - 4];
    PropMgr* mpPropMgr;    // +0x24

    float* FUN_00b81630(void* out, void* p);   // 0x00b81630
};
inline PlanetModelObj* SP_PlanetModel() { return (PlanetModelObj*)FUN_00b3d350(); }
struct SimSelf {
    uint8_t  pad00[0x1c];
    SimHash  mHash;          // +0x1c
    uint8_t  pad2c[0x3c - 0x2c];
    uint8_t  mb3c;           // +0x3c
    uint8_t  pad3d[3];
    int32_t  m40;            // +0x40
    uint8_t  mb44;           // +0x44
    uint8_t  pad45[3];
    RBTree   mTree;          // +0x48
    uint8_t  pad60[0x68 - 0x60];
    PtrVector mVec;          // +0x68
    uint8_t  pad74[0x7c - 0x74];
    uint32_t m7c, m80, m84;  // +0x7c
    uint32_t m88, m8c, m90;  // +0x88

    int   FUN_00bbf730(const int* src, float f);
    void  FUN_00bbf860();
    void  FUN_00bbcb90(int tier, void* planet);   // 0x00bbcb90
    void  FUN_00bbfe80();
    void  FUN_00bc0180(uint8_t flag);
};
void FUN_00bbfeb0(void* planet);
void FUN_00bbff40(void* planet);
void FUN_00bc0000(void* planet);
// ---- items of slice s00bbf630 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* EAAllocate(uint size, const char* name, int a, int b, void* site, int line); // 0x00f473a0

// ---- items of slice s00bc1690 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  kFlt156cfb8;                                      // 0x0156CFB8
extern float  kFlt156cfbc;                                      // 0x0156CFBC
extern float  kFlt156cfc0;                                      // 0x0156CFC0
extern float  kFlt156cfc4;                                      // 0x0156CFC4
#define FLT_MAX_ 3.402823466e+38f
// ---- items of slice s00bc1690 end

// ---- items of slice s00bc2570 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_one;          // 0x1485720   (1.0f)
extern float g_dayScale;     // 0x156cfc8
extern float g_thr0;         // 0x156cfb8
extern float g_thr1;         // 0x156cfbc
extern float g_thr2;         // 0x156cfc0
extern float g_thr3;         // 0x156cfc4
extern "C" float  __cdecl FUN_0069b760(float* a, float* b, float* dir);
extern "C" void __cdecl FUN_00bc2670(float len);
#pragma warning(disable: 4100)
#define SP_NOINLINE __declspec(noinline)
struct cTimeOfDay {
    char  pad_0000[0x24];
    float mDayLength;   // +0x24

    void  SetDayLength(float len);
    void  FUN_00bc28c0(float len);
    float FUN_00bc2b30(void* a);
    float FUN_00bc2b60(void* a);
    int   FUN_00bc2b80(void* a);
    void  FUN_00bc2f00(float v, void* a);
    void  FUN_00bc2f70(int mode, void* a);
};
typedef uint64_t (__cdecl* SPTimeFn)();
struct cSPTimer {
    void*   mVtbl;       // +0x00
    uint32_t mUnk4;      // +0x04
    uint64_t mElapsed;   // +0x08
    uint64_t mBase;      // +0x10
    uint8_t mRunning;    // +0x18
    uint8_t pad_19[3];
    SPTimeFn mGetTime;   // +0x1c

    void      Start();
    void      Stop();
    void      Restart();
    void      FUN_00bc3150(uint64_t delta);
    void      FUN_00bc3170();
    uint64_t  GetElapsedTime();
    cSPTimer* FUN_00bc31c0(SPTimeFn fn);
};
// ---- items of slice s00bc2570 end

// ---- items of slice s00bc34c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g156d1fc;                                 // follow-rate scale
extern float g145cfe8;                                 // block of 4 floats (0x3e860a92)
extern void* vt014667f0[];
extern void* vt0145cf78[];
extern void* vt014667ec[];
void* __cdecl operator_new(unsigned size, const char* name, int flags, int a, const char* file, int line);
static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char* const kSimulator = "Simulator";
static inline void freeBuf(void* p) { if (p && ((int*)p)[-1] != 0) operator_delete__(p); }
struct V3 {
    float x, y, z;
    V3() {}
    V3(float a, float b, float c) : x(a), y(b), z(c) {}
    V3(const V3& o) {
        ((uint32_t*)this)[0] = ((const uint32_t*)&o)[0];
        ((uint32_t*)this)[1] = ((const uint32_t*)&o)[1];
        ((uint32_t*)this)[2] = ((const uint32_t*)&o)[2];
    }
    V3& operator=(const V3& o) {
        ((uint32_t*)this)[0] = ((const uint32_t*)&o)[0];
        ((uint32_t*)this)[1] = ((const uint32_t*)&o)[1];
        ((uint32_t*)this)[2] = ((const uint32_t*)&o)[2];
        return *this;
    }
};
struct Q4 { float x, y, z, w; Q4() {} Q4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
extern V3 g168aab4;
struct B0 {
    void __thiscall init(void* a);  // 0x00b12890 (base ctor)
};
struct F3 { float x, y, z; F3(float a, float b, float c) : x(a), y(b), z(c) {} F3(const F3& o) : x(o.x), y(o.y), z(o.z) {} };
struct F4 { float x, y, z, w; F4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} F4(const F4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {} };
extern F3 g156d200v;                                   // 0x0156d200
extern F4 g156d20cv;                                   // 0x0156d20c
struct SubA {
    uint32_t pad[0x15];
    void __thiscall set(F3 v);  // 0x00f4f5a0
};
struct SubB {
    uint32_t pad[0x1b];
    void __thiscall set(F4 q);  // 0x00f4fe50
};
struct FixedVec8 {                                        // fixed_vector<AutoRefCount<cSpatialObject>, 8>
    void** mpBegin; void** mpEnd; void** mpCap;
    uint32_t a, b, overflow;
    void* buf[8];
    void __thiscall dtor();                               // 0x00ad92d0
};
struct Cam {                                              // App()->vf50()->vf1c()
    virtual void v0();
    void __thiscall f7c4d00(void* hdr);  // 0x007c4d00
    void __thiscall f7c4ba0(float a);  // 0x007c4ba0
    void __thiscall f7c4bc0(float a);  // 0x007c4bc0
};
struct Mgr { virtual void v0(); };
struct App1 { virtual void v0(); };
App1* __cdecl App();                                       // 0x0067dd10 SP::App
struct PosHelper : V3 {                                   // 0xb16dc0 / 0xb17790
    PosHelper(Cam* c);  // 0x00b16dc0
    void __thiscall f17790(int a);  // 0x00b17790
};
bool __cdecl f00b17c10(PosHelper* pos, FixedVec8* v);  // 0x00b17c10
bool __cdecl f00b17810(PosHelper* pos, Q4* q);  // 0x00b17810
bool __cdecl f00b182f0(PosHelper* pos, int flags);          // 0x00b182f0 cGameData::PathOrSerializationCheck
void __cdecl f00b16450(PosHelper* pos, FixedVec8* v);  // 0x00b16450
void __cdecl f00b16e50(PosHelper* pos, Q4* q);  // 0x00b16e50
struct Hdr { uint16_t flags; uint16_t count; float v[3]; };
struct C {
    void* vt0; void* vt1; void* vt2;
    uint32_t pad0c[3];
    uint8_t b18, b19; uint16_t pad1a;
    float f1c, f20, f24, f28, f2c, f30, f34, f38;
    SubA s3c;
    SubB s90;
    uint8_t bfc, bfd; uint16_t padfe;
    float f100, f104, f108, f10c, f110, f114, f118, f11c;
    uint8_t b120, b121; uint16_t pad122;
    float f124, f128, f12c, f130, f134, f138, f13c, f140;
    uint32_t pad144[(0x2cc - 0x144) / 4];
    Hdr h2cc;
    uint32_t pad2dc[(0x310 - 0x2dc) / 4];
    float f310, f314;
    uint32_t pad318[(0x394 - 0x318) / 4];
    float f394;
    uint8_t b398; uint8_t pad399[3];
    V3 v39c;
    V3 v3a8;
    uint32_t d3b4;

    C* __thiscall ctor(void* arg);
    void __thiscall update(float dt);
};
struct PM { void __thiscall f00b82970(); };
void* __stdcall PlanetModel(void* a, V3* b, int c);          // SP::PlanetModel (0x00b3d350)
struct LNode {
    LNode* next; uint32_t pad4; int key;
    char pad[0x7d8 - 0xc];
    uint32_t f7d8;
    uint8_t pad7dc; uint8_t b7dd; uint8_t pad7de[6];
    uint32_t f7e4;
};
struct Reg {
    char pad[0x1c];
    LNode* head;          // list sentinel pointer (list anchor at +0x1c)
    LNode* lastPad;
    uint32_t __thiscall findValue(int key);
    uint8_t __thiscall isDisabled(int key);
    void __thiscall setFlag(int key, uint32_t v);
};
#define LIST_END(self) ((LNode*)((char*)(self) + 0x1c))
struct Elem98 {
    void* mpBegin; void* mpEnd; void* mpCap; uint32_t a, b, overflow;
    void* buf[32];
    void __thiscall assign(const Elem98* src);              // FUN_00bc3f50
};
struct A12 { int a, b, c; };
void __cdecl FUN_00512050(A12** out, A12* first, A12* last, A12* dst, int tag);
A12* __cdecl FUN_00a11310(A12* first, A12* last, A12* dst);
A12* __cdecl copy_backward12(A12* first, A12* last, A12* destEnd);   // 0x00abced0
A12* __cdecl copy12(const A12* first, const A12* last, A12* dst);    // 0x00b84c80
struct VecA12 {
    A12* mpBegin; A12* mpEnd; A12* mpCap;
    void __thiscall insert(A12* pos, const A12* first, const A12* last, int tag);
};
void* __cdecl FUN_00bc4_move(void* dst, const void* src, unsigned bytes);   // 0x011e0744 (memmove-like, returns dst)
uint32_t* __cdecl FUN_00c16090(const uint32_t* first, const uint32_t* last, uint32_t* destEnd);
struct VecU32 {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap;
    void __thiscall insert(uint32_t* pos, const uint32_t* first, const uint32_t* last, int tag);
};
template <int N> struct FV {
    void** mpBegin; void** mpEnd; void** mpCap; uint32_t a, b, ovf; void* buf[N];
    FV() { ovf = 0; void** p = buf; mpBegin = p; mpEnd = p; mpCap = p + N; }
};
struct FStr32 {
    char* mpBegin; char* mpEnd; char* mpCap; uint32_t a; char* mpBuf; char buf[32];
    FStr32() { char* p = buf; mpBuf = buf; mpCap = p + 32; mpEnd = p; mpBegin = p; buf[0] = 0; }
};
struct Big {
    uint32_t pad0[2];
    FV<8> v0; FV<64> v1; FV<32> v2; FV<8> v3; FV<6> v4; FV<4> v5; FV<304> v6;
    FStr32 s;
    Big();
};
// ---- items of slice s00bc34c0 end

// ---- items of slice s00bc4730 begin (TODO(rewrite): local stubs, replace by canonical classes)
void** __cdecl VectorErasePtr(void** first, void** last, void** end);          // 0x0042f530
void** __cdecl VectorCopyPtr(void** first, void** last, void** dst);           // 0x006782c0
void* __cdecl GetAudioSystem();                                            // 0x00a206f0
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Quad16 { uint32_t a, b, c, d; };
template <typename T, int N>
struct fixed_vector {
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    T mBuffer[N];

    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    size_type capacity() const { return (size_type)(mpCapacity - mpBegin); }

    void init() {
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
        mAllocator[2] = 0;
    }
};
struct Elem98_s00bc_4730 : fixed_vector<Quad16, 8> {
    void assign(const Elem98_s00bc_4730& other);                        // 0x00bc3f50
};
Elem98_s00bc_4730* __cdecl ElemVecAllocN(unsigned n, const Elem98_s00bc_4730* first, const Elem98_s00bc_4730* last);   // 0x00bc4d90
Elem98_s00bc_4730* __cdecl ElemVecFreeN(Elem98_s00bc_4730* first, Elem98_s00bc_4730* last, Elem98_s00bc_4730* out);               // 0x00bc3ec0
Elem98_s00bc_4730* __cdecl ElemVecCopyBack(Elem98_s00bc_4730* first, Elem98_s00bc_4730* last, Elem98_s00bc_4730* out);            // 0x00bc4060
void    __cdecl ElemVecFillN(Elem98_s00bc_4730* first, unsigned n, const Elem98_s00bc_4730* val);           // 0x00bc4280
Elem98_s00bc_4730* __cdecl ElemVecCopyConstruct(Elem98_s00bc_4730* first, Elem98_s00bc_4730* last, Elem98_s00bc_4730* out);       // 0x00bc4310
Elem98_s00bc_4730* __cdecl ElemVecInsertCopy(void* out, Elem98_s00bc_4730* first, Elem98_s00bc_4730* last, Elem98_s00bc_4730* dst); // 0x00bc4370
Elem98_s00bc_4730* __cdecl ElemVecAssignRange(Elem98_s00bc_4730* first, Elem98_s00bc_4730* last, Elem98_s00bc_4730* out);         // 0x00bc42d0
Elem98_s00bc_4730* __cdecl ElemVecFillRange(Elem98_s00bc_4730* first, Elem98_s00bc_4730* last, const Elem98_s00bc_4730* val);     // 0x00bc4590
struct ElemVecOps : fixed_vector<Elem98_s00bc_4730, 8> {
    void destroyRange(Elem98_s00bc_4730* first, Elem98_s00bc_4730* last);   // 0x00bc3f10
};
struct fixed_string32 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mPad;
    char* mpBuffer;
    char mBuffer[32];
};
struct PropRecord {
    uint32_t mValue0;                                 // +0x000
    int32_t  mCount;                                  // +0x004
    fixed_vector<uint32_t, 8> mIndices;               // +0x008
    fixed_vector<Vector2, 32> mVec2A;                 // +0x040
    fixed_vector<float, 32>   mAngles;                // +0x158
    fixed_vector<uint8_t, 32> mFlags;                 // +0x1f0
    fixed_vector<Vector3, 2>  mVec3;                  // +0x228
    fixed_vector<Vector2, 2>  mVec2B;                 // +0x258
    fixed_vector<Elem98_s00bc_4730, 8>   mLists;                 // +0x280
    fixed_string32            mName;                  // +0x758
    float    mF78C;                                   // +0x78c
    float    mF790;                                   // +0x790
    uint32_t mU794;                                   // +0x794
    uint32_t mU798;                                   // +0x798
    uint8_t  mB79C;                                   // +0x79c
    uint8_t  mB79D;                                   // +0x79d
    uint16_t mPad79E;                                 // +0x79e
    uint32_t mU7A0;                                   // +0x7a0
    uint32_t mU7A4;                                   // +0x7a4
    uint32_t mU7A8;                                   // +0x7a8
    uint32_t mBitMask;                                // +0x7ac
    uint32_t mFourCC;                                 // +0x7b0

    void init();                                      // 0x00bc4630
    void destroy();                                   // 0x00bc4730
    void copyFrom(const PropRecord& src);             // 0x00bc54f0
};
typedef fixed_vector<void*, 32> EntryVec32;
struct EntryVec16 { void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAlloc[3]; void* mBuffer[16];
    void init() { void** p = mBuffer; mpBegin = p; mpEnd = p; p += 16; mpCapacity = p; mAlloc[2] = 0; } };
struct EntryVec16P { void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAlloc[3]; void* mBuffer[16]; uint32_t mPad;
    void init() { void** p = mBuffer; mpBegin = p; mpEnd = p; p += 16; mpCapacity = p; mAlloc[2] = 0; } };
struct EntryVec4  { void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAlloc[3]; void* mBuffer[4];
    void init() { void** p = mBuffer; mpBegin = p; mpEnd = p; p += 4; mpCapacity = p; mAlloc[2] = 0; } };
struct Entry_s00bc_4730 {
    uint32_t mKey;                                    // +0x000
    uint32_t mPad04[7];                               // +0x004
    PropRecord rec;                                   // +0x020
    uint8_t  mB7D4;                                   // +0x7d4
    uint8_t  mDisabled;                               // +0x7d5
    uint16_t mPad7D6;                                 // +0x7d6
    int32_t  mState;                                  // +0x7d8
    int32_t  mBusy;                                   // +0x7dc
    EntryVec32  mCreatures;                           // +0x7e0
    EntryVec16P mA878;                                // +0x878
    EntryVec16  mSounds;                              // +0x8d4
    EntryVec4   mFx;                                  // +0x92c

    Entry_s00bc_4730* init();                                    // 0x00bc4820
};
struct Node {
    Node* mpNext;                                     // +0x00
    Node* mpPrev;                                     // +0x04
    Entry_s00bc_4730 mEntry;                                     // +0x08
};
struct Loco {
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
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
    virtual float GetScale();                         // +0x74
};
struct Creature {
    virtual void v0();
    virtual void Release();                           // +4
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
virtual void v48();
virtual void v49();
virtual void v50();
virtual void v51();
virtual void v52();
virtual void v53();
    virtual void SetFacing(const void* q);            // +0xd8 (0x36*4)
    virtual void SetPos(const void* v);               // +0xdc
    virtual void v56();
    virtual void SetCurrentPose(const void* v);       // +0xe4
virtual void v58();
virtual void v59();
    virtual void SetMotion(const void* v);            // +0xec
    uint32_t mPad04[0x2f];                            // +0x04 .. +0xbf
    Loco loco;                                        // +0xc0
    void MoveToPointAndFacingAtSpeed(int mode, const Vector3* pos, const Vector3* facing,
                                     float speed, float scale);  // 0x00c1c5c0
};
void* __cdecl PlanetSnapB(void* out, Vector3* in, int flag);        // 0x00b82970
void* __cdecl PlanetBuildSurface(void* out, Vector3* pos, Vector3* up); // 0x00b7f250
Vector3* __stdcall BuildOffset(void* out, Entry_s00bc_4730* e, const float* vec2, float scale); // 0x00bc3c20
Vector3* __cdecl normalized_safe(void* scratch, const Vector3* v);   // 0x00449c20
void* __cdecl QuatMulVec3(void* out, const void* q, const Vector3* v); // 0x0059aed0
void __cdecl SetSkinFlag(Entry_s00bc_4730* e, int on);        // 0x00c0d950
void __fastcall E1C7F0(EntryVec32* vec, int unused, Creature** ref);  // 0x00e1c7f0
struct FixedAlloc {
    char     mPad00[0x10];                            // +0x00
    Node*    mpFree;                                  // +0x10
    bool __thiscall AddCore(void* block, unsigned flags);   // 0x00926650
};
struct NodeRoot {
    Node* mpNext;                                     // +0x00
    Node* mpPrev;                                     // +0x04
};
struct Reg_s00bc_4730 {
    NodeRoot  mRoot;                                  // +0x00 (node owner/append root)
    FixedAlloc mAlloc;                                // +0x08 (mpFree at +0x18)
    Node     mSentinel;                               // +0x1c

    void resetEntry(Entry_s00bc_4730* e);                        // 0x00bc4bf0
    void resetAll();                                  // 0x00bc4d60
    void resetByKey(uint32_t key);                    // 0x00bc5040
    void enable(uint32_t key, Creature* c);           // 0x00bc52a0
    bool tryMove(Creature* c, Creature* dest, int flag); // 0x00bc4900
    Node* newNode();                                  // 0x00bc51c0
    void teardown();                                  // 0x00bc53f0
};
struct PropVecA {
    PropRecord* mpBegin;                              // +0
    PropRecord* mpEnd;                                // +4
    PropRecord* mpCapacity;                           // +8
    void destroy();                                   // 0x00bc5210
};
struct PropVecB {
    uint32_t mTag;                                    // +0
    PropRecord* mpBegin;                              // +4
    PropRecord* mpEnd;                                // +8
    PropRecord* mpCapacity;                           // +0xc
    void destroy();                                   // 0x00bc5300

    // vector<Elem98> member ops share this TU's fixed_vector<Elem98,8>
};
struct ElemVec : fixed_vector<Elem98_s00bc_4730, 8> {
    ElemVec* assign(const ElemVec& src);               // 0x00bc5070
    void insert(Elem98_s00bc_4730* pos, unsigned n, const Elem98_s00bc_4730* val); // 0x00bc4df0
    void resize(unsigned n);                           // 0x00bc5340
    Elem98_s00bc_4730* erase(Elem98_s00bc_4730* first, Elem98_s00bc_4730* last);        // 0x00bc5250
};
void PropRecord::init()
{
    uint32_t zero = 0;
    mIndices.init();
    mIndices.mAllocator[2] = zero;
    mVec2A.init();
    mVec2A.mAllocator[2] = zero;
    mAngles.init();
    mAngles.mAllocator[2] = zero;
    mFlags.init();
    mFlags.mAllocator[2] = zero;
    mVec3.init();
    mVec3.mAllocator[2] = zero;
    mVec2B.init();
    mVec2B.mAllocator[2] = zero;
    mLists.init();
    mLists.mAllocator[2] = zero;
    mName.mpBegin = mName.mpBuffer = mName.mBuffer;
    mName.mpEnd = mName.mBuffer;
    mName.mpCapacity = mName.mBuffer + 32;
    mName.mBuffer[0] = 0;
}
void Elem98_s00bc_4730::assign(const Elem98_s00bc_4730& src)
{
    if (&src == this)
        return;
    Quad16* first = src.mpBegin;
    size_t n = (size_t)(src.mpEnd - first);
    size_t cap = (size_t)(mpCapacity - mpBegin);
    if (n > cap) {
        Quad16* buf = (Quad16*)ElemVecAllocN((unsigned)n, 0, 0);
        freeBuf(mpBegin);
        mpBegin = buf;
        mpEnd = buf + n;
        mpCapacity = buf + n;
        memcpy(buf, first, n * sizeof(Quad16));
        return;
    }
    size_t cur = (size_t)(mpEnd - mpBegin);
    if (cur < n) {
        memcpy(mpBegin, first, cur * sizeof(Quad16));
        memcpy(mpEnd, first + cur, (n - cur) * sizeof(Quad16));
        mpEnd = mpBegin + n;
    } else {
        memcpy(mpBegin, first, n * sizeof(Quad16));
        mpEnd = mpBegin + n;
    }
}
void ElemVecOps::destroyRange(Elem98_s00bc_4730* first, Elem98_s00bc_4730* last)
{
    while (first < last) {
        freeBuf(first->mpBegin);
        ++first;
    }
}
// ---- items of slice s00bc4730 end

// ---- items of slice s00bc5730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl operator_delete_arr(void* p);              // 0x00f47380 (operator delete[])
extern const float kAngleScale;                    // 0x0168ab34 (runtime-initialised)
typedef unsigned short char16;
extern const char16 gEmptyString16[1];                              // 0x01667bac
struct string16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    uint32_t mAllocator;
    string16() {
        mpBegin = mpEnd = (char16*)gEmptyString16;
        mpCapacity = mpBegin + 1;
    }
    ~string16() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_arr(mpBegin);
        }
    }
};
struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    ~string8() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_arr(mpBegin);
        }
    }
    const char* c_str() const { return mpBegin; }
};
string8 ConvertToString8(const string16& s);                        // 0x0093c570 EA::ConvertToString8
struct fixed_string32_s00bc_5730 {                                             // fixed_string<char, 32>
    char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAllocator; char* mpBuffer;
    char mBuffer[32];
    void assign(const char* first, const char* last);               // 0x00836910
    fixed_string32_s00bc_5730& operator=(const char* p) {
        assign(p, p + strlen(p));
        return *this;
    }
};
struct Property_s00bc_5730 {
    uint32_t mData;      // +0x00 (or pointer to the data when (mFlags & 0x30))
    uint32_t pad04[3];
    uint16_t mFlags;     // +0x10
    uint16_t mType;      // +0x12 (1 bool, 10 uint32, 13 float)
};
template <typename T>
static inline T& PropData(Property_s00bc_5730* p) {
    T* data = (T*)p;
    if (p->mFlags & 0x30)
        data = *(T**)p;
    return *data;
}
struct cPropertyList_s00bc_5730 {
    virtual void AddRef();
    virtual void Release();
virtual void vf2();
virtual void vf3();
virtual void vf4();
virtual void vf5();
virtual void vf6();
    virtual bool HasProperty(uint32_t id);                          // slot 7 (+0x1c) 0x006a2470
    virtual void vf8();
    virtual bool GetProperty(uint32_t id, Property_s00bc_5730** out);          // slot 9 (+0x24)
};
struct IPropertyManager {
virtual void vf0();
virtual void vf1();
virtual void vf2();
virtual void vf3();
virtual void vf4();
virtual void vf5();
virtual void vf6();
virtual void vf7();
virtual void vf8();
virtual void vf9();
virtual void vf10();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList_s00bc_5730** out);  // slot 11
};
IPropertyManager* PropertyManager();                                // 0x0067de30 SP::PropertyManager
static inline uint32_t PropUInt32(cPropertyList_s00bc_5730* list, uint32_t id, uint32_t def) {
    Property_s00bc_5730* p;
    if (list && list->GetProperty(id, &p) && p->mType == 10)
        return PropData<uint32_t>(p);
    return def;
}
static inline float PropFloat(cPropertyList_s00bc_5730* list, uint32_t id, float def) {
    Property_s00bc_5730* p;
    if (list && list->GetProperty(id, &p) && p->mType == 13)
        return PropData<float>(p);
    return def;
}
static inline bool PropBool(cPropertyList_s00bc_5730* list, uint32_t id, bool def) {
    Property_s00bc_5730* p;
    if (list && list->GetProperty(id, &p) && p->mType == 1)
        return PropData<bool>(p);
    return def;
}
struct Vector2_s00bc_5730 { float x, y; Vector2_s00bc_5730() {} Vector2_s00bc_5730(float a, float b) : x(a), y(b) {} };
struct Vector3_s00bc_5730 { float x, y, z; Vector3_s00bc_5730() {} };
bool GetPropertyAsString16(cPropertyList_s00bc_5730* list, uint32_t id, string16& out);                 // 0x006a1400
bool GetPropertyAsUint32Array(cPropertyList_s00bc_5730* list, uint32_t id, int* count, uint32_t** out); // 0x006a0840
bool GetPropertyAsFloatArray(cPropertyList_s00bc_5730* list, uint32_t id, int* count, float** out);     // 0x006a08b0
bool GetPropertyAsVector2Array(cPropertyList_s00bc_5730* list, uint32_t id, int* count, Vector2_s00bc_5730** out); // 0x006a0920
bool GetPropertyAsVector3Array(cPropertyList_s00bc_5730* list, uint32_t id, int* count, Vector3_s00bc_5730** out); // 0x006a0ae0
bool GetPropertyAsBoolArray(cPropertyList_s00bc_5730* list, uint32_t id, int* count, bool** out);       // 0x006a0760
struct random_access_iterator_tag {};
template <typename T> struct is_pod_copy { enum { value = 0 }; };
template <> struct is_pod_copy<uint32_t> { enum { value = 1 }; };
template <> struct is_pod_copy<float> { enum { value = 1 }; };
template <> struct is_pod_copy<bool> { enum { value = 1 }; };
template <typename T, int N>
struct fixed_vector_s00bc_5730 {
    typedef T value_type;
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    T mBuffer[N];

    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }

    void DoInsertValues(T* position, size_type n, const value_type& value);   // out of line
    void DoInsertFromIterator(T* position, const T* first, const T* last,
                              random_access_iterator_tag);                    // out of line
    void resize(size_type n);                                                 // out of line (Elem98)

    void insert(T* position, const T* first, const T* last) {
        DoInsertFromIterator(position, first, last, random_access_iterator_tag());
    }
    T* erase(T* first, T* last) {
        if (is_pod_copy<T>::value) {
            memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        } else {
            T* dst = first;
            for (T* src = last; src != mpEnd; ++src, ++dst)
                *dst = *src;
        }
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void resize_inline(size_type n) {
        if (n > (size_type)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (size_type)(mpEnd - mpBegin), value_type());
        else
            erase(mpBegin + n, mpEnd);
    }
};
struct Elem16 { uint32_t a, b, c, d; };
typedef fixed_vector_s00bc_5730<Elem16, 8> Elem98_s00bc_5730;            // 0x98 bytes; resize = 0x00bc45c0
struct PropRecord_s00bc_5730 {
    uint32_t mValue0;                              // +0x000
    int mCount;                                    // +0x004
    fixed_vector_s00bc_5730<uint32_t, 8> mIndices;            // +0x008
    fixed_vector_s00bc_5730<Vector2_s00bc_5730, 32> mVec2A;              // +0x040
    fixed_vector_s00bc_5730<float, 32> mAngles;               // +0x158
    fixed_vector_s00bc_5730<bool, 32> mFlags;                 // +0x1f0
    fixed_vector_s00bc_5730<Vector3_s00bc_5730, 2> mVec3;                // +0x228
    fixed_vector_s00bc_5730<Vector2_s00bc_5730, 2> mVec2B;               // +0x258
    fixed_vector_s00bc_5730<Elem98_s00bc_5730, 8> mLists;                // +0x280; resize = 0x00bc5340
    fixed_string32_s00bc_5730 mName;                          // +0x758
    float mF78C;                                   // +0x78c
    float mF790;                                   // +0x790
    uint32_t mU794;                                // +0x794
    uint32_t mU798;                                // +0x798
    bool mB79C;                                    // +0x79c
    bool mB79D;                                    // +0x79d
    uint32_t mU7A0;                                // +0x7a0
    uint32_t mU7A4;                                // +0x7a4
    uint32_t mU7A8;                                // +0x7a8
    uint32_t mBitMask;                             // +0x7ac
    uint32_t mFourCC;                              // +0x7b0
};
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
// ---- items of slice s00bc5730 end

// ---- items of slice s00bc6360 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gOne;                                 // 0x01485720
struct V3_s00bc_6360 {
    float x, y, z;
    V3_s00bc_6360() {}
    V3_s00bc_6360(const V3_s00bc_6360& o) { x = o.x; y = o.y; z = o.z; }
};
struct Mat3 {
    float m[9];
    Mat3() {}
    Mat3(const Mat3& o) { for (int i = 0; i < 9; ++i) m[i] = o.m[i]; }
    Mat3& operator=(const Mat3& o) { memcpy(m, o.m, sizeof(m)); return *this; }
};
struct V2 { float x, y; };
struct A12_s00bc_6360 { uint32_t id, b, c; };                 // 12-byte effect description element (id first)
extern Mat3 gIdentity3;                            // 0x0168ab3c
struct Transform {
    int16_t flags;
    int16_t count;
    V3_s00bc_6360 offset;
    float scale;
    Mat3 rot;
    Transform() { count = 1; flags = 0; scale = gOne; rot = gIdentity3; }
    void SetOffset(const V3_s00bc_6360& v) { offset = v; flags |= 4; }
    void SetRotation(const Mat3& r) { rot = r; flags |= 2; ++count; }
};
struct Effect {
    virtual void v0();
    virtual void Release();                        // +4
    virtual void Start(int a);                     // +8
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void SetTransform(Transform* t);       // +0x18
};
struct EffectsMgr {
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
    virtual void v10();
    virtual bool CreateEffect(uint32_t id, int zero, Effect** out);   // +0x2c
};
EffectsMgr* __cdecl GetEffectsManager();           // 0x0067ddd0 SP::EffectsManager
struct Loco_s00bc_6360 {
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
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
    virtual float GetScale();                      // +0x74
    bool __thiscall IsNearGoal();                  // 0x00c42e20 SP::cLocomotiveObject::IsNearGoal
};
struct Creature_s00bc_6360 {
    virtual void v0();
    virtual void Release();                        // +4
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void v7();
    virtual int GetTypeId();                       // +0x20
    uint32_t pad04[0x2f];
    Loco_s00bc_6360 loco;                                     // +0xc0
    bool __thiscall f00c25480(int a, int b);                    // 0x00c25480
    int __thiscall GetBodyPartIndex(int a, int b);              // 0x00c17580
    void __thiscall SetCurrentToolEffect(int a, int b);         // 0x00c24f40
    void __thiscall InterruptAnimation(int a, int b, int c);    // 0x00c12310
    void __thiscall f00c0e640(int a);                           // 0x00c0e640
    int __thiscall f00c0e370();                                 // 0x00c0e370
    bool __thiscall AnimationFinished(int a);                   // 0x00c123f0
    void __thiscall StartIndependentSound(const char* name, const V3_s00bc_6360* pos, void* ids);  // 0x00c1db40
};
struct Elem98_s00bc_6360 {                                    // fixed_vector<Elem16, 8>
    Elem16* mpBegin; Elem16* mpEnd; uint32_t rest[0x26 - 2];
};
struct FxVec {                                     // vector<AutoRefCount<Effect>>
    Effect** mpBegin; Effect** mpEnd; Effect** mpCap;
    void __thiscall insertFill(Effect** pos, unsigned n, Effect* const* val);   // 0x00a72db0
    void __thiscall erase(Effect** first, Effect** last);                       // 0x00533500
};
struct Planet {
    void* __thiscall BuildSurfaceOrientation2(void* out, V3_s00bc_6360* pos, V3_s00bc_6360* up);      // 0x00b7f250
};
Planet* __cdecl GetPlanetModel();                  // 0x00b3d350 SP::PlanetModel
void __cdecl Matrix3FromQuaternion(Mat3* out, void* q);                         // 0x0059c190
struct Reg_s00bc_6360;
void* __stdcall FUN_00bc3c20(void* out, char* obj, const float* v2, float f);   // slice s00bc34c0
struct Entry_s00bc_6360 {                                     // list node payload (node + 8)
    int key;                                       // +0x00
    V3_s00bc_6360 a;                                          // +0x04
    V3_s00bc_6360 b;                                          // +0x10
    uint32_t pad1c[3];
    int* indices;                                  // +0x28 (rec.mIndices.mpBegin)
    uint32_t pad2c[(0x248 - 0x2c) / 4];
    A12_s00bc_6360* fxBegin; A12_s00bc_6360* fxEnd;                      // +0x248 effect descriptions
    uint32_t pad250[(0x278 - 0x250) / 4];
    V2* fxPos;                                     // +0x278
    uint32_t pad27c[(0x2a0 - 0x27c) / 4];
    Elem98_s00bc_6360* lists;                                 // +0x2a0
    uint32_t pad2a4[(0x778 - 0x2a4) / 4];
    char* nameBegin; char* nameEnd;                // +0x778
    uint8_t pad780[0x7bd - 0x780];
    uint8_t b7bd;
    uint8_t pad7be[0x7d0 - 0x7be];
    uint32_t f7d0;
    uint8_t b7d4;
    uint8_t disabled;                              // +0x7d5
    uint8_t pad7d6[2];
    int state;                                     // +0x7d8
    int busy;                                      // +0x7dc
    Creature_s00bc_6360** crBegin; Creature_s00bc_6360** crEnd;          // +0x7e0
    uint32_t pad7e8[(0x878 - 0x7e8) / 4];
    int* animIdx;                                  // +0x878
    uint32_t pad87c[(0x8d4 - 0x87c) / 4];
    void* soundIds;                                // +0x8d4 (vector, passed by address)
    uint32_t pad8d8[(0x92c - 0x8d8) / 4];
    FxVec fx;                                      // +0x92c
};
struct Node_s00bc_6360 { Node_s00bc_6360* next; Node_s00bc_6360* prev; Entry_s00bc_6360 e; };
struct Reg_s00bc_6360 {
    uint32_t pad00[7];
    Node_s00bc_6360* head;                                    // +0x1c (sentinel anchor)
    uint32_t pad20[5];
    Node_s00bc_6360* freeList;                                // +0x34
    void __thiscall f00bc4bf0(Entry_s00bc_6360* e);           // 0x00bc4bf0
    void __thiscall Update(int a, int b);
};
struct Rec { void __thiscall dtor(); };            // 0x00bc4730
#define LIST_END_s00bc_6360(self) ((Node_s00bc_6360*)((char*)(self) + 0x1c))
struct VecA {
    void* b; void* e; void* c;
    VecA& operator=(const VecA&);                  // 0x0050d4e0
};
struct VecB {
    void* b; void* e; void* c;
    VecB& operator=(const VecB&);                  // 0x00473b00
};
struct ByteV {
    void* b; void* e; void* c;
    void assign(const ByteV&);                     // 0x00420e30
};
struct KeyV {
    uint32_t w[12];
    KeyV& operator=(const KeyV&);                  // 0x006609a0
};
struct VecC {
    uint32_t w[0x136];
    void CopyFrom(const VecC&);                    // 0x00bc5070
};
struct VecD {
    uint8_t* b; uint8_t* e; uint8_t* c;
    uint8_t pad[0x28];
    void assign(uint8_t*, uint8_t*);               // 0x0045f430
};
struct Sub {
    uint32_t f00;                                  // +0x000 (vtable for standalone)
    uint32_t f04;                                  // +0x004 (anim handle when embedded)
    VecA v08;                                      // +0x008
    uint8_t pad14[0x2c];
    VecB v40;                                      // +0x040
    uint8_t pad4c[0x10c];
    VecA v158;                                     // +0x158
    uint8_t pad164[0x8c];
    ByteV v1f0;                                    // +0x1f0
    uint8_t pad1fc[0x2c];
    KeyV v228;                                     // +0x228
    VecB v258;                                     // +0x258
    uint8_t pad264[0x1c];
    VecC v280;                                     // +0x280
    VecD v758;                                     // +0x758
    float f78c;                                    // +0x78c
    float f790;                                    // +0x790
    uint32_t d794;                                 // +0x794
    uint32_t d798;                                 // +0x798
    uint8_t b79c;                                  // +0x79c
    uint8_t b79d;                                  // +0x79d
    uint8_t pad79e[2];
    uint32_t d7a0, d7a4, d7a8, d7ac, d7b0;         // +0x7a0
    Sub(const Sub&);                               // 0x00bc54f0
    Sub& Assign(const Sub&);                       // @ 0x00bc6360
};
struct Anim {
    uint32_t pad0;
    void Build(int anim, int* out);                // 0x004b2030
};
struct EntryB {
    int32_t key;                                   // +0x00
    V3_s00bc_6360 a;                                          // +0x04
    V3_s00bc_6360 b;                                          // +0x10
    float f1c;                                     // +0x1c
    Sub sub;                                       // +0x20 (0x7b4)
    uint8_t b7d4;                                  // +0x7d4
    uint8_t disabled;                              // +0x7d5
    uint8_t pad7d6[2];
    int32_t state;                                 // +0x7d8
    int32_t busy;                                  // +0x7dc
    uint32_t p7e0;                                 // +0x7e0
    uint32_t p7e4;                                 // +0x7e4
    uint8_t pad7e8[0x878-0x7e8];
    Anim anim;                                     // +0x878
};
struct Node2;                                       // { next, prev, EntryB }
struct FixedState {
    uint32_t w[8];
};
struct ListHead {
    Node2* next;                                   // +0x00
    Node2* prev;                                   // +0x04
    FixedState alloc;                              // +0x08..0x28 (object+0x24..0x44)
    void Init();                                   // 0x00bc51c0
};
struct Node2 {
    Node2* next;
    Node2* prev;
    EntryB e;
};
void __cdecl ReadPropRecord(int a, int b, void* out);   // 0x00bc5730
void __fastcall SubDtor(Sub* p);                         // 0x00bc4730
struct SubVec {
    Sub* b; Sub* e; Sub* c;
    SubVec() {}
    SubVec(const SubVec&);                         // @ 0x00bc6e20
    Sub* Erase(Sub*, Sub*);                        // @ 0x00bc7110
    void Insert(Sub*, uint32_t, const Sub&);       // @ 0x00bc7170
};
void* __cdecl SimNew(uint32_t size, const char* name, int a, int b, void* alloc, int line); // 0x00f473a0
void __cdecl MoveRange5(Sub** out, Sub* first, Sub* last, Sub* dst, SubVec* self);          // 0x00bc56b0
Sub* __cdecl CopyRange2(Sub* first, Sub* last, Sub* dst);                                   // 0x00bc56f0
void __cdecl DestroyRange2(Sub* first, Sub* last, Sub* dst);                                // 0x00bc48c0
void __cdecl FillCopy(Sub* dst, uint32_t n, const Sub& value);                              // 0x00bc6540
void __cdecl MoveAssignRange(Sub* dst, Sub* first, Sub* last);                              // 0x00bc65b0
void __cdecl FillValueRange(Sub* pos, Sub* end, const Sub* value);                          // 0x00bc6f40
Sub* __cdecl ShiftTail(Sub* last, Sub* end, Sub* first);                                    // 0x00bc6570
void __fastcall DestroyVecA(SubVec* p);            // 0x00bc5300
void __fastcall DestroyVecB(SubVec* p);            // 0x00bc5210
struct HashNode2 {
    uint32_t pad0;
    Sub* begin;                                    // +0x04
    Sub* end;                                      // +0x08
    uint32_t pad0c[3];
    HashNode2* next;                               // +0x18
};
struct MapIter {
    void* node;                                    // +0x00  bucket chain node (0 when absent)
    void* bucketSlot;                              // +0x04  &buckets[hash] or &buckets[count]
    uint8_t inserted;                              // +0x08  set by Insert only
};
struct MapValue {
    uint32_t key;                                  // +0x00
    SubVec vec;                                    // +0x04
};
struct HashMap {
    uint32_t field00;                              // +0x00
    void** buckets;                                // +0x04
    uint32_t bucketCount;                          // +0x08
    uint32_t size;                                 // +0x0c
    float loadF;                                   // +0x10
    float growF;                                   // +0x14
    uint32_t field18;                              // +0x18
    void ClearBuckets(void** buckets, uint32_t count);   // @ 0x00bc6eb0
    void Find(MapIter* out, uint32_t* key);              // 0x00aea1b0
    void Insert(MapIter* out, const MapValue* value, uint32_t flag); // 0x00bc6f90
    SubVec* FindOrAdd(uint32_t* key);                    // @ 0x00bc7440
};
struct SimClass {
    uint32_t vtbl0;                                // +0x00
    uint32_t vtbl1;                                // +0x04
    uint8_t pad08[0x14];
    ListHead list;                                 // +0x1c
    uint32_t count;                                // +0x44
    HashMap map;                                   // +0x48
    void BaseCtor();                               // 0x00b5b960
    void BaseDtor();                               // 0x00b5b9a0
    int CreateEntry(int, int, const V3_s00bc_6360*, const V3_s00bc_6360*);           // @ 0x00bc64a0
    int CreateEntryCopy(const Sub*, const V3_s00bc_6360*, const V3_s00bc_6360*);     // @ 0x00bc65f0
    SimClass();                                    // @ 0x00bc7380
    void Destroy();                                // @ 0x00bc7080
    void ClearMap();                               // @ 0x00bc6f70
};
struct FixedAlloc_s00bc_6360 {
    FixedState st;
    FixedAlloc_s00bc_6360(uint32_t size, uint32_t align, uint32_t blocks, uint32_t a,
               uint32_t max, void* alloc, void* free, const char* name);  // 0x00926720
    void Commit();                                 // 0x00926640
};
void __fastcall DestroyList(void* p);              // 0x00bc53f0
void __fastcall CommitAlloc(void* p);              // 0x00926640
// ---- items of slice s00bc6360 end

// ---- items of slice s00bc74d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl op_new(int size, const char* name, int, int, const char* file, int line);
extern "C" void  __cdecl op_delete_(void* p);
extern "C" void* __cdecl FUN_00bc4630();
extern "C" void  __cdecl FUN_00bc4730();
extern "C" void  __cdecl FUN_00bc5730(int a, int b, int c);
extern "C" int*  __cdecl FUN_00bc79f0(void* last, void* first, void* dst);
extern "C" int*  __cdecl FUN_00bc7a30(void* first, void* last, void* dst);
extern "C" void    __cdecl FUN_00f47380(void* p);   // 0x00f47380 operator delete
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);   // 0x011e0744
extern float DAT_0168ab70;
extern float DAT_0168ab74;
extern float DAT_0168ab78;
struct RefObj {
    virtual void Add();       // vtbl + 0
    virtual void Release();   // vtbl + 4
};
struct Vec3f { float x, y, z; };
struct cHierGrid {
    char b[0x84];

    void Remove(unsigned index);                                             // 0x00702da0
    int  QuerySphereResult(float radius, float* pos, int maxN, void** out);  // 0x00702760
    bool Init(const Vec3f& box, float v, int a, int b);                     // 0x00704260
};
void __fastcall cHierGrid_ctor(void* p);                                     // 0x00703ce0
void __fastcall cHierGrid_Shutdown(void* p);                                 // 0x00704060
struct Rec_s00bc_74d0 {
    unsigned flags;   // 0x00
    int   f04;        // 0x04
    int   f08;        // 0x08
    int   f0c;        // 0x0c  (float in some paths)
    int   f10;        // 0x10
    int   f14;        // 0x14
    int   f18;        // 0x18
    int   f1c;        // 0x1c
    void* p20;        // 0x20
    void* p24;        // 0x24
    union { int f28; void* p28; };  // 0x28 (int in copy, refcounted ptr in assign)
    int   f2c;        // 0x2c
    int   f30;        // 0x30
    int   f34;        // 0x34
    int   f38;        // 0x38

    Rec_s00bc_74d0* FUN_00bc76d0(Rec_s00bc_74d0* src);   // operator=
    Rec_s00bc_74d0* FUN_00bc7850(Rec_s00bc_74d0* src);   // copy-construct
    Rec_s00bc_74d0* FUN_00bc7920(Rec_s00bc_74d0* src);   // assign / reset
};
struct CivTmp {
    char b[0x7b4];

    CivTmp* __thiscall FUN_00bc4630();   // 0x00bc4630 (returns this)
    void    __thiscall FUN_00bc4730();   // 0x00bc4730
};
struct WE {
    Rec_s00bc_74d0* begin;   // 0x00
    Rec_s00bc_74d0* end;     // 0x04
    Rec_s00bc_74d0* cap;     // 0x08
    int  f0c;     // 0x0c
    int  f10;     // 0x10
    int  freeI;   // 0x14
    int  activeI; // 0x18
    cHierGrid grid; // 0x1c .. 0xa0

    void  FUN_00bc74d0(uint n);
    void  FUN_00bc7170(void* end, uint n, void* hint);   // 0x00bc7170
    void  FUN_00bc7110(void* dst, void* end);            // 0x00bc7110
    int   FUN_00bc7680(int index);
    void  FUN_00bc77e0(int index);
    void** FUN_00bc7a70(void** out, Rec_s00bc_74d0* at);
    void  FUN_00bc7b70(uint n);
    __declspec(noinline) int FUN_00bc7c40(int first, int last);
    void  FUN_00bc7ca0(Rec_s00bc_74d0* at, int* val);
    void  FUN_00bc7e20();
    uint  FUN_00bc7e80(int src);
};
struct Rec7 { char b[0x7b4]; };
struct IntVec { int* begin; int* end; int* cap; };
struct PropMgr_s00bc_74d0 {
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
    virtual void GetVector(int id, IntVec* out);   // vtbl +0x48
};
extern "C" PropMgr_s00bc_74d0* __cdecl FUN_0067de30_s00bc_74d0();        // 0x0067de30 SP::PropertyManager
struct WEHash {
    int   pad00;         // 0x00
    int** mBuckets;      // 0x04
    int   mBucketCount;  // 0x08

    void find(int* out, const unsigned* key);          // 0x00aea1b0
    WE*  FUN_00bc7440(const unsigned* key);            // 0x00bc7440
};
struct WEMap {
    char   pad00[0x48];
    WEHash mHash;        // 0x48
    WE*    FUN_00bc7610(unsigned key, char create);
};
struct WERef {
    WE* mEvents;   // 0x00
    void FUN_00bc7ac0(unsigned delta);
};
struct IntVector {
    int* begin;   // +0x00
    int* end;     // +0x04
    int* cap;     // +0x08
    void __thiscall insert(int* pos, unsigned n, const int* val);   // 0x00b97280
    void __thiscall resize(unsigned n);                             // 0x00b98ea0
    void __thiscall reserve(unsigned n);                            // 0x00d01790
    void __thiscall DoInsertKey4(int* pos, const int* val);         // 0x00b96600
};
struct GridItem {
    char  pad0[8];
    int   mType;     // +0x08
    char  padC[4];
    float mRadius;   // +0x10
    float mX;        // +0x14
    float mY;        // +0x18
    float mZ;        // +0x1c
};
struct WEHolder {
    WE* mEvents;     // +0x00
    void FUN_00bc8080(const float* pos, float radius, IntVector* out, int filter);
};
// ---- items of slice s00bc74d0 end

// ---- items of slice s00bc8400 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCount {
    virtual void AddRef();          // vtbl+0x00
    virtual void Release();         // vtbl+0x04
};
struct cGrid {
    unsigned mLevel;    // +0x00
    unsigned m04;       // +0x04
    unsigned mSlot;     // +0x08
    float    mCellSize; // +0x0c
    float    mHalf;     // +0x10
    unsigned mInUse;    // +0x14  (bit 30 set => occupied)
    unsigned m18;       // +0x18
    unsigned mCells;    // +0x1c
    unsigned m20;       // +0x20
    unsigned mStamp;    // +0x24
    float    mRadius;   // +0x28
    char     m2c[0x5c];

    unsigned CreateEntry(unsigned a, void* b, float c);
};
struct cGridQueue {
    char*    mBeg;      // +0x00
    char*    mEnd;      // +0x04
    char*    mCap;      // +0x08
    unsigned m0c;       // +0x0c
    unsigned m10;       // +0x10
    unsigned m14;       // +0x14
    unsigned m18;       // +0x18
    char*    mTable;    // +0x1c

    unsigned Acquire(void* out);    // 0x00bc7e80 (ret 4)
};
struct cHierGrid_s00bc_8400 {
    cGridQueue* mQueue;     // +0x00
    char        m04[0x39];  // +0x04 .. +0x3c
    char*       mCellTbl;   // +0x3d
    char        m41;        // +0x41 (mask lives here; byte access in source)
    char        m42[3];     // +0x42 .. +0x44
    unsigned*   mKey;       // +0x45
    char        m49[4];     // +0x49 .. +0x4c
    unsigned    m4d;        // +0x4d
    unsigned    m51;        // +0x51
    unsigned    m55;        // +0x55
    char        m59[0x23];  // +0x59 .. +0x7b
    unsigned    m7c;        // +0x7c
    unsigned    m80;        // +0x80

    unsigned NewEntry(unsigned a2, unsigned* src, unsigned a4, float radius,
                      IRefCount* p1, IRefCount* p2);
};
struct GridMask {
    unsigned m00, m04, m08, m0c;
    char     m10;
    char     m11[3];
    unsigned m14;
    unsigned m18;
    unsigned m1c;
    char     m20;
    char     m21[3];
    unsigned m24;
    unsigned m28;
    unsigned m2c;

    bool FitsMask(unsigned m1, unsigned m2);
};
unsigned __cdecl GenerateUInt32(unsigned n);
void* __cdecl Grid_NewArray(void* owner, unsigned tag, unsigned size);
// ---- items of slice s00bc8400 end

// ---- items of slice s00bc8ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_0168B548;                // 0x0168B548 its init guard (bit 0)
extern const float g_0146697C;   // 0x0146697c (FLT_MAX)
#pragma pack(pop)
#pragma pack(push, 1)
struct Node_s00bc_8ff0;
struct Callbacks
{
	int userData;   // +0x00 (copied into the cursor)
	bool (*fnA)(int p4, double t, int p7, int idx, void* rec, void* mask);                  // +0x04 first visit
	bool (*fnB)(int p4, double t, int p7, int idx, void* rec, void* mask, float f1);        // +0x08 every visit
	void (*fnC)(int p4, double t, int p7, void* scratch, Callbacks* self);                  // +0x0c exit
};
struct Node_s00bc_8ff0
{
	uint32_t id;                                                     // +0x00
	int      type;                                                   // +0x04 0 leaf, 1 group
	float    (*condFn)(int p4, double t, int p7, void* bufA, void* flagOut, Node_s00bc_8ff0* node, void* ctx);   // +0x08
	void     (*failFn)(int p4, double t, int p7, void* bufA, Node_s00bc_8ff0* node);                             // +0x0c
	uint32_t flags;                                                  // +0x10
	uint32_t pad14[2];
	float    weight;                                                 // +0x1c
	int      slot;                                                   // +0x20
	int      order;                                                  // +0x24 (-1 until numbered)
	uint32_t pad28[0x12];
	Callbacks* cb;                                                   // +0x70
	int      defaultIdx;                                             // +0x74
	int      kind;                                                   // +0x78
	uint32_t count;                                                  // +0x7c
	Node_s00bc_8ff0*    children;                                               // +0x80 (0x88-byte entries)
	uint32_t pad84;
};
struct Frame   // 0xAC bytes, one per tree depth
{
	uint32_t id;         // +0x00
	int      idx;        // +0x04
	int      childIdx;   // +0x08
	uint32_t counter;    // +0x0c
	double   t;          // +0x10
	uint32_t rec1[5];    // +0x18
	uint32_t rec2[32];   // +0x2c
};
struct Cursor
{
	uint32_t id;         // +0x00 result
	Node_s00bc_8ff0*    node;       // +0x04
	int      childIdx;   // +0x08
	int      depth;      // +0x0c
	Frame    frames[1];  // +0x10 ...
};
struct Ctx   // packed scratch record shared with the helpers (0x59 bytes)
{
	Node_s00bc_8ff0*     node;       // +0x00
	int       a;          // +0x04
	uint8_t   b;          // +0x08
	uint32_t  c9;         // +0x09
	uint32_t  cD;         // +0x0d
	uint32_t  c11;        // +0x11 (child chosen by the selector)
	uint32_t  rec[5];     // +0x15
	uint32_t  prev;       // +0x29
	int       depth;      // +0x2d
	int       p4;         // +0x31
	double    t;          // +0x35
	int       p6;         // +0x3d
	int       p7;         // +0x41
	int       p8;         // +0x45
	void*     rng;        // +0x49
	void*     bufA;       // +0x4d
	void*     bufB;       // +0x51
	Callbacks* active;    // +0x55
};
union FlagWord
{
	uint32_t word;
	uint8_t  flag;
};
struct RandomMersenneTwister
{
	uint32_t mState[0x9c8 / 4];
	RandomMersenneTwister(uint32_t seed);   // 0x00936300 (seeds the generator, ret 4)
};
inline void* operator new(unsigned int, void* p) { return p; }
extern RandomMersenneTwister g_0168AB80;   // 0x0168AB80 shared generator
int   __cdecl AssignOrder(Node_s00bc_8ff0* node, int* counter, uint32_t* maxChildren);                                  // 0x00bc8810
void  __cdecl ResetFrames(int p4, double t, int p7, Node_s00bc_8ff0* node, Frame* frame);                                 // 0x00bc85b0
float __cdecl EvalNode(Node_s00bc_8ff0* node, int a, int idx, int p4, double t, Ctx* ctx, FlagWord* flagOut);            // 0x00bc8970
void  __cdecl ApplyEval(uint32_t flag, Node_s00bc_8ff0* node, Ctx* ctx, int p4, double t);                               // 0x00bc87b0
void  __cdecl SelectChild(Node_s00bc_8ff0* node, Ctx* ctx, int p4, double t);                                            // 0x00bc8a00
struct IRefCounted
{
	virtual void AddRef();       // +0x00
	virtual void Release();      // +0x04
	virtual void V2();           // +0x08
	virtual void V3();           // +0x0c
	virtual void V4();           // +0x10
	virtual void V5();           // +0x14
	virtual void V6();           // +0x18
	virtual void V7();           // +0x1c
	virtual void V8();           // +0x20
	virtual void V9();           // +0x24
	virtual void V10();          // +0x28
	virtual bool V11();          // +0x2c
};
struct Stimulus
{
	uint32_t     id;          // +0x00
	uint32_t     mask;        // +0x04
	float        duration;    // +0x08
	uint32_t     pad0c[8];    // +0x0c
	IRefCounted* volatile object;      // +0x2c
	uint32_t     pad30[2];    // +0x30
};
struct Stimuli
{
	void SetStimulus(Stimulus* s, uint32_t a, uint32_t b, float c, IRefCounted* obj);
	void ClearStimulus(Stimulus* s);
	void ResetStimuli();
	void ClearAll(uint32_t a, uint32_t b);
	uint32_t* UpdateStimuli(float dt);

	Stimulus slot[8];         // +0x000
	uint32_t mMask0;          // +0x1c0
	uint32_t mMask1;          // +0x1c4
};
struct Rec1c
{
	uint32_t     id;         // +0x00
	float        time;       // +0x04
	uint32_t     field8;     // +0x08
	uint32_t     pad0c[3];   // +0x0c
	IRefCounted* object;     // +0x18
};
struct State1c
{
	State1c* Reset();
	void ReleaseObjects();
	void Update(float dt);
	Rec1c* Add(uint32_t id, float duration, IRefCounted* obj, uint32_t field8);
	void ClearMask(uint32_t mask_);
	bool Has(uint32_t mask_);

	uint32_t mask;           // +0x00
	Rec1c    rec[8];         // +0x04
};
typedef void (__cdecl *ActionFn)(void* self);
struct Rec44
{
	uint32_t pad00[8];       // +0x00 .. +0x1f
	uint16_t kind;           // +0x20
	uint16_t pad22;          // +0x22
	int32_t  state;          // +0x24
	int32_t  sub;            // +0x28
	float    f0c;            // +0x2c
	uint32_t a10;            // +0x30
	ActionFn callback;       // +0x34
	uint32_t a18;            // +0x38
	IRefCounted* ptr1c;      // +0x3c
	IRefCounted* ptr20;      // +0x40
};
struct State44
{
	Rec44* SetupAction(float f, uint32_t a, ActionFn cb, uint32_t c, uint32_t unused);
	void ReleaseAction();
	State44* Reset(uint32_t v);
	void ReleaseAll();
	void ClearAll();
	Rec44* Find(uint32_t key);

	Rec44    rec[8];         // +0x00 .. +0x21f
	uint32_t vals[3];        // +0x220
	uint32_t flag;           // +0x22c
};
struct Entry_s00bc_8ff0
{
	uint32_t id;             // +0x00
	uint32_t a;              // +0x04
	uint32_t b;              // +0x08
};
struct EntryState
{
	uint32_t CurrentId();
	bool SetCurrent(uint32_t id);

	uint8_t  pad00[0x14];    // +0x00
	int32_t  current;        // +0x14
	uint32_t count;          // +0x18
	uint8_t  pad1c[8];       // +0x1c
	Entry_s00bc_8ff0    entries[8];     // +0x24
};
union FloatBits
{
	float    f;
	uint32_t u;
};
struct FloatArray
{
	float* At(int i);
	void Set3(int i, const float* v);
	float Get(int i);
	void Set(int i, float v);
	void SetWord(int i, uint32_t v);

	uint8_t pad[0x1a4];      // +0x000
	FloatBits vals[64];      // +0x1a4
};
struct IntArray
{
	void Set(int i, uint32_t v);

	uint8_t  pad[0x220];     // +0x000
	uint32_t vals[64];       // +0x220
};
static void InitRec44(Rec44* r, uint32_t none)
{
	r->kind = 0;
	r->state = none;
	r->sub = none;
	r->ptr1c = 0;
	r->ptr20 = 0;
}
// ---- items of slice s00bc8ff0 end

// ---- items of slice s00bca040 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gFloatMax;      // 0x0146697c  3.4028235e38
extern float gZeroFloat;     // 0x01485378  0.0f
extern short gAgentOrderId;  // 0x0156d290
extern float gOrderDef0;     // 0x0168b580
extern float gOrderDef1;     // 0x0168b584
extern float gOrderDef2;     // 0x0168b588
extern wchar_t gNameAgentOrder[]; // 0x01466980 L"cAgentOrder"
extern char   gDescAgentOrder;    // 0x0156d2a8
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
struct cGonzagoTimer;                 // sizeof 0x20
struct IRefCount_s00bc_a040;
struct cOutStream;
struct cSerializer;
struct cGonzagoTimer {
    void* mVtbl;   // +0x00
    int   m04;     // +0x04
    int   m08;     // +0x08
    int   m0c;     // +0x0c
    int   m10;     // +0x10
    int   m14;     // +0x14
    char  m18;     // +0x18
    int   m1c;     // +0x1c
};
void cGonzagoTimer_ctor(cGonzagoTimer* t);   // @ 0x00b63890
void cGonzagoTimer_dtor(cGonzagoTimer* t);   // @ 0x00b638b0
struct IRefCount_s00bc_a040 {
    virtual void AddRef();                      // vtbl+0x00
    virtual void Release();                     // vtbl+0x04
    virtual void vtbl08();                      // vtbl+0x08
    virtual void* QueryInterface(unsigned id);  // vtbl+0x0c
    virtual void vtbl1c(void* a);               // vtbl+0x1c
    virtual void vtbl20();
    virtual int  vtbl2c();                      // vtbl+0x2c
};
struct IVtbl2c {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c(void*);
};
struct cAgentOrder {
    int           mId;        // +0x00
    char          mPad04[4];  // +0x04
    cGonzagoTimer mTimer;     // +0x08
    IRefCount_s00bc_a040*    mSource;    // +0x28
    float         mTimeLeft;  // +0x2c
    float         mF1;        // +0x30
    float         mF2;        // +0x34
    char          mFlag;      // +0x38
    char          mVariant0[0x14];  // +0x39 .. payload 0x39, tags 0x49/0x4b
    char          mVariant1[0x14];  // +0x4d .. payload 0x4d, tags 0x5d/0x5f
    char          mVariant2[0x14];  // +0x61 .. payload 0x61, tags 0x71/0x73
    char          mVariant3[0x14];  // +0x75 .. payload 0x75, tags 0x85/0x87

    cAgentOrder();
    ~cAgentOrder();
    int  operator_eq(cAgentOrder const& o);
    cAgentOrder* Assign(cAgentOrder const& o);
    cAgentOrder* CopyConstruct(cAgentOrder const& o);
    char Serialize(cOutStream* s);
};
struct cAgentOrderManager {
    // slot record: stride 0x44, 8 slots, base == this
    struct Slot {
        int           mId;        // +0x00   (shifted: slot+0x20 id is at mId+0x20)
    };
    char            mSlots[0x220];       // +0x000  8 slots * 0x44
    void*           mTemplates;          // +0x220
    char            mPad224[8];
    u32             mActiveMask;         // +0x22c
    char            mPad230[0x3b8];
    void*           mArray;              // +0x5e8
    char            mPad5ec[0x14];
    IRefCount_s00bc_a040*      mSource;             // +0x600
    int             mSourceStamp;        // +0x604
    char            mPad608[4];
    // intrusive list 0: head at +0x60c, tail at +0x610, size at +0x614
    char*           mList0Head;          // +0x60c
    char*           mList0Tail;          // +0x610
    u32             mList0Size;          // +0x614
    char            mPad618[0x0c];
    char*           mFree0;              // +0x624
    char            mPad628[0x0c];
    char*           mList1Head;          // +0x634
    char*           mList1Tail;          // +0x638
    u32             mList1Size;          // +0x63c
    char            mPad640[0x0c];
    char*           mFree1;              // +0x64c
    char            mPad650[0x0c];
    char*           mArrayBegin;         // +0x65c
    char*           mArrayEnd;           // +0x664

    void  DeactivateSlot(int id);
    u32   FindSlot(int a, int b, int c, int d);
    int   IsSourceAtEnd();
    int   IsSourceEmpty();
    cAgentOrder* FirstPending();
    void  Tick(float dt);
    cAgentOrder* FindNode(int key, int (*pred)(void*, void*), void* ctx);
    u32   Activate(int tmplIdx, int type, IRefCount_s00bc_a040* p1,
                   float timeLeft, void* header, IRefCount_s00bc_a040* p2);
    void  SaveList2(cOutStream* s, char* list);
    void  FreeAll();
    void ReleaseNode(char** out, char* node);
    void  AllocNode();
    void  ClearList();
    void  AllocLink();
    void  DoInsertValues(char* pos, u32 n, void* val);
    ~cAgentOrderManager();
    void  PopFront();
    cAgentOrder* PushBack(void* a, IRefCount_s00bc_a040* b, char clear);
    void  ReleaseQueueObject(char* obj, u32 idx);
};
struct cSerializer {
    void SaveObject(void* obj, void* desc, void* name);   // @ 0x00695b40
};
void  FUN_00bc8fa0(void*);                             // 0x00bc8fa0
void  FUN_0093db80(void*, int);                        // 0x0093db80 Variant::Destruct
void  FUN_00542b80(void*, void*);                      // 0x00542b80 Variant::operator=
int   FUN_0093aa70(void*, unsigned*, int, int);        // 0x0093aa70 EA::IO::WriteUint32
void  FUN_00926640(void*);                             // 0x00926640 ~FixedAllocatorBase thunk
char  FUN_00926650(void*, void*, unsigned);            // 0x00926650 FixedAllocatorBase::AddCore
void FUN_00bca670(void* p);                            // 0x00bca670
void FUN_00bca6a0(void* p);                            // 0x00bca6a0
void FUN_00bca6f0(void);                               // 0x00bca6f0
bool FUN_00bca7a0(void* ser, char* list);              // 0x00bca7a0
bool FUN_00bca7e0(void* a1, void** slot);              // 0x00bca7e0
bool FUN_00bca960(void* a1, void** slot);              // 0x00bca960
void FUN_00bca990(void* a1, char* list);               // 0x00bca990
int  FUN_00bcacb0(char* list, IRefCount_s00bc_a040* obj);         // 0x00bcacb0
// ---- items of slice s00bca040 end

// ---- items of slice s00bcb0b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete(void* p);                                  // 0x00f47380
extern "C" void* __cdecl operator_new__(void* dst, int count, unsigned size);       // 0x011e073e
extern void* vtbl_cAnimalTrap[1];                                               // 0x01466b40
extern void* vtbl_cAnimalTrapRef[1];                                            // 0x01466b2c
extern void* vtbl_cAnimalTrapSpatial[1];                                        // 0x01466a68
extern int s_serializerGeneric;                                                 // 0x0156d600
extern int s_serializerGenericList;                                             // 0x0156d2a8
extern float g_matrixSeed;                                                      // 0x0168b5fc
extern float g_eps0;                                                            // 0x013ec4b8
extern float g_defaultRadius;                                                   // 0x01473c70
extern float g_bigDistance;                                                     // 0x01466bac
void* wrapper_alloc(unsigned size, void* p);                                        // 0x006abeb0
void  wrapper_free(void* p);                                                        // 0x00f47410
struct string16_s00bc_b0b0 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    string16_s00bc_b0b0() : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(0); }
    string16_s00bc_b0b0(const string16_s00bc_b0b0& o);
    ~string16_s00bc_b0b0() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) operator_delete(mpBegin);
        }
    }
    void RangeInitialize(const char16* p);                                          // 0x00579a90
    const char16* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};
string16_s00bc_b0b0 __cdecl ConvertToString16(const char* in, int n);                          // 0x0093c5a0
struct FixedAllocatorBase {
    uint32_t mFields[8];
    FixedAllocatorBase(unsigned objectSize, unsigned alignment, unsigned objectCount,
                       unsigned a, int b, void* pfnAlloc, void* pfnFree,
                       const char* pszName);                                    // 0x00926720
    ~FixedAllocatorBase();                                                      // 0x00926640
    bool AddCore(void* p, unsigned n);                                          // 0x00926650
};
typedef void (__thiscall* FnThis0)(void*);
struct ListEntry {
    void** vptr;                // +0x000
    uint32_t m04;               // +0x004
    const char* mpName;         // +0x008
    uint32_t m0c;               // +0x00c
    uint32_t m10;               // +0x010
    uint32_t m14;               // +0x014
    uint32_t mValue;            // +0x018
    uint8_t m1c;                // +0x01c
    uint32_t m20[0x180 / 4];    // +0x020
    uint32_t m1a0;              // +0x1a0
    uint32_t m1a4[0x80 / 4];    // +0x1a4
    uint32_t m224;              // +0x224
    uint32_t m228;              // +0x228
    void Construct(void* record);                                               // 0x00bcab80
};
struct ListNode {               // 0x234 bytes
    ListNode* mpNext;           // +0x000
    ListNode* mpPrev;           // +0x004
    ListEntry mEntry;           // +0x008
};
struct RawList {                // 0x28 bytes: sentinel + embedded FixedAllocatorBase
    ListNode* mpNext;           // +0x00
    ListNode* mpPrev;           // +0x04
    FixedAllocatorBase mAlloc;  // +0x08
    void Clear();                                                               // 0x00bcaa00
    ListNode* AllocNode();                                                      // 0x00bcaab0
    void ConstructNode(ListEntry* p);                                           // 0x00bcab80
    RawList* Construct();                                                       // 0x00bcb590
    ListEntry* Insert(const char* name, unsigned typeId, int value, int flags); // 0x00bcb0b0
};
template <class T> const T& MaxRef(const T& a, const T& b) { return a < b ? b : a; }
template <class T> const T& MinRef(const T& a, const T& b) { return a < b ? a : b; }
struct Quad16_s00bc_b0b0 {
    int mIndex;                 // +0x00
    uint32_t mPad;              // +0x04
    double mValue;              // +0x08
};
void* __cdecl copy_705250(void* dst, const void* first, const void* last);      // 0x00705250
struct QuadVec {                // lives at editor +0x5e8
    Quad16_s00bc_b0b0* mpBegin;            // +0x00
    Quad16_s00bc_b0b0* mpEnd;              // +0x04
    Quad16_s00bc_b0b0* mpCap;              // +0x08
    void SetArraySize(unsigned count);                                          // 0x00bcb5f0
    void DoInsertN(Quad16_s00bc_b0b0* pos, unsigned n, const Quad16_s00bc_b0b0* value);               // 0x00bcacf0
};
struct SelEntry {
    uint8_t mUsed;              // +0x00
    uint32_t mA;                // +0x04
    uint32_t mB;                // +0x08
};
struct SelItem {
    void** vptr;                // +0x00
    uint32_t m04;               // +0x04
    uint32_t m08;               // +0x08
    uint32_t m0c;               // +0x0c
    int mUsedCount;             // +0x10
    uint32_t m14;               // +0x14
    uint32_t mCount;            // +0x18
    uint32_t m1c;               // +0x1c
    SelEntry mEntries[1];       // +0x20
};
struct VarSource {              // object assigned to the editor (count at +0x24)
    uint32_t m00[9];            // +0x00..+0x23
    uint32_t mCount;            // +0x24
};
struct cVarListEditor {
    void* mpObject;                 // +0x000
    uint32_t m04;                   // +0x004
    uint32_t mElems[8 * 0x38 / 4];  // +0x008  (8 x 0x38-byte blocks)
    uint32_t mElemTail[2];          // +0x1c8
    uint32_t mSub1[0x418 / 4];      // +0x1d0
    Quad16_s00bc_b0b0* mpVecBegin;             // +0x5e8
    Quad16_s00bc_b0b0* mpVecEnd;               // +0x5ec
    Quad16_s00bc_b0b0* mpVecCap;               // +0x5f0
    uint32_t m5f4;                  // +0x5f4
    uint32_t m5f8;                  // +0x5f8
    void* mp5fc;                    // +0x5fc
    SelItem* mpSelected;            // +0x600
    int mIndex;                     // +0x604
    void* mpItem;                   // +0x608
    RawList mList1;                 // +0x60c
    RawList mList2;                 // +0x634
    string16_s00bc_b0b0 mName;                 // +0x65c

    ListEntry* Insert(const char* name, unsigned typeId, int value, int flags); // 0x00bcb0b0
    cVarListEditor* Construct();                                                // 0x00bcb2a0
    void Reset();                                                               // 0x00bcb3d0
    void ClearSelection();                                                      // 0x00bcb430
    void SetSelection(SelItem* item, int a, int b, void* c);                    // 0x00bcb480
    int  SelectByName(const char* name, int a, const char* c);                  // 0x00bcb510
    void SetListObject(VarSource* item);                                        // 0x00bcb660
    void RemoveItem(SelItem* item, int index);                                  // 0x00bcafe0
    SelItem* FindItem(uint32_t key0, void* key, const char* name);              // 0x00bca620
};
extern cVarListEditor* g_pVarListEditor;                                        // 0x0168b56c
struct ElemOps { void Clear(); void Alloc(); };
bool __cdecl WriteListElement(void* writer, int a, ListEntry* e);               // 0x00ac8050
bool __cdecl WriteListProperty(void* writer, const char* name, RawList* list);  // 0x00bcb160
struct CGameDataOps {
    void Ctor();                                                                // 0x00b18660
    void Dtor();                                                                // 0x00b184c0
    bool Write(void* stream);                                                   // 0x00b18590
};
struct CSpatialOps {
    void Ctor();                                                                // 0x00c89630
    bool Write(void* stream);                                                   // 0x00c88a90
    void Destroy();                                                             // 0x00c8b2e0
    void DtorBody();                                                            // 0x00c8a420
};
uint32_t __cdecl FNV1_String8(const char* s, uint32_t basis, int flags);        // 0x00932e80
struct cSpatialObjectPart {     // 0xd4 bytes, cAnimalTrap +0x34..+0x107
    void** vptr;                // +0x00
    uint32_t m04[0x50 / 4];     // +0x04..+0x53
    uint32_t m54;               // +0x54  (set to 2 by the cAnimalTrap ctor)
    uint32_t m58[0x38 / 4];     // +0x58..+0x8f
    uint32_t m90;               // +0x90  (0x00c4 absolute: tool-type hash)
    uint32_t m94;               // +0x94
    uint32_t m98;               // +0x98  (0x00cc absolute: tribal-tools hash)
    uint32_t m9c[0x38 / 4];     // +0x9c..+0xd3
};
struct cVarListSerializer;                                                      // 0xa14 bytes
bool __cdecl WriteUint32_93aa70(void* stream, const uint32_t* p, unsigned n, int flags); // 0x0093aa70
struct cVarListSerializer {
    uint32_t mData[0xa14 / 4];
    cVarListSerializer* Construct(void* obj, void* generic, unsigned sig); // 0x00692f90
    bool Serialize(void* stream);                                          // 0x00692900
};
struct cAnimalTrap {
    void** vptr;                // +0x000
    void* mRefVtbl;             // +0x004
    uint32_t m08[9];            // +0x008..+0x02b
    void* mp2c;                 // +0x02c
    uint32_t m30;               // +0x030
    cSpatialObjectPart mSpatial;// +0x034
    int mState;                 // +0x108
    uint32_t m10c;              // +0x10c
    uint32_t m110;              // +0x110
    void* mp114;                // +0x114

    cAnimalTrap* __fastcall Construct();                                        // 0x00bcb980
    void SetState(int s);                                                       // 0x00bcb960
    void __fastcall Destroy();                                                  // 0x00bcba80
    bool Write(void* stream);                                                   // 0x00bcbad0
    void Update();                                                              // 0x00bcbc80
    cAnimalTrap* ScalarDeletingDtor(unsigned flags);                            // 0x00bcbc30
};
struct cGonzagoTimer_s00bc_b0b0 {
    uint32_t m[0x20 / 4];                                                       // vptr + 7 words
    cGonzagoTimer_s00bc_b0b0();                                                            // 0x00b63890
    ~cGonzagoTimer_s00bc_b0b0();                                                           // 0x00b638b0
};
struct Variant {                // 0x14 bytes; flags/type words live at +0x10/+0x12
    uint32_t m[4];              // +0x00  (payload, left untouched)
    uint16_t mFlags;            // +0x10
    uint16_t mTypeId;           // +0x12
    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant() { if (mFlags & 4) Destruct(false); }
    void Destruct(bool free);                                                   // 0x0093db80
};
struct Vector3f { float x, y, z; };
struct RefPtr {                 // refcounted payload holder (released by its dtor)
    void* mp;                   // +0x00
    RefPtr() : mp(0) {}
    ~RefPtr() { if (mp) ((FnThis0)(*(void***)mp)[1])(mp); }
};
struct ListRecord {             // 0x90 bytes
    int mIndex;                 // +0x00
    uint32_t m04;               // +0x04  (left untouched)
    cGonzagoTimer_s00bc_b0b0 mTimer;       // +0x08
    RefPtr mRef;                // +0x28
    Vector3f mVec;              // +0x2c
    uint8_t m38;                // +0x38
    Variant mV0;                // +0x39
    Variant mV1;                // +0x4d
    Variant mV2;                // +0x61
    Variant mV3;                // +0x75
    uint8_t mPad89[0x90 - 0x89];// +0x89
    ListRecord() : mIndex(-1), m38(0) {}
};
extern Vector3f g_readVecSeed;                                                  // 0x0168b580
bool __cdecl ReadInt32_93a780(void* stream, void* dst, int count, int flags);   // 0x0093a780
struct Matrix3 { float m[9]; };
struct PtrVec { void** mpBegin; void** mpEnd; void** mpCap; };
struct EffectParams {           // 0x14 bytes
    uint16_t mFlags;            // +0x00
    uint16_t mRefCount;         // +0x02
    Vector3f mPos;              // +0x04
    float mScale;               // +0x10
};
extern Vector3f g_vecZero;                                                      // 0x0168b5f0
void Matrix3Assign(Matrix3* self, const void* src);                             // 0x0041cb40
Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3f* up, const Vector3f* facing); // 0x0069b440
void* EffectsManager();                                                         // 0x0067ddd0
void* NounManager();                                                            // 0x00b3d300
int GetPlayerEmpireOrMinus1();                                                  // 0x00b1f9d0
float GetPropertyFloat(void* list, uint32_t key, float def);                    // 0x004e1c70
void* FUN_00d1e660();                                                           // 0x00d1e660
void* FUN_00b3d240();                                                           // 0x00b3d240
void* GetPlayerTribe(void* mgr);                                                // 0x00bfc5f0
void* GetChieftain(void* tribe);                                                // 0x00c8fd30
// ---- items of slice s00bcb0b0 end

// ---- items of slice s00bcc010 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VF(obj, slot) (*(void**)((char*)*(void**)(obj) + (slot) * 4))
int   __cdecl FUN_004e1c30(void* tool, unsigned id, int def);  // 0x004e1c30 cdecl
void  __cdecl FUN_00b1e500();                                 // 0x00b1e500 callback
void  __cdecl FUN_00cd7d10();                                 // 0x00cd7d10 callback
void  __cdecl FUN_00d3d420();                                 // 0x00d3d420 callback
void  __cdecl FUN_00ace0f0();                                 // 0x00ace0f0 callback
class cGameNounManager_s00bc_c010 {
 public:
    int*  __thiscall GetGameDataVector(void* a, void* b, void* c, void* d, int e); // 0x00b21340 ret 0x14
    void  __thiscall RemoveNoun(void* noun);                   // 0x00b225d0 ret 4
    void* __thiscall GetPlayerCivilization();                  // 0x00b25fb0 ret
    void* __thiscall Unk25f40(void* p);                        // 0x00b25f40 ret 4
};
class cSerializableNoun {
 public:
    char __thiscall WriteBase(void* s);                        // 0x00bcc350
    char __thiscall ReadBase(void* s);                         // 0x00bcc400
};
class cTribeTool : public cSerializableNoun {
 public:
    void __thiscall bcc010();
    void __thiscall bcc230(int elapsed);
    void __thiscall bcc760(int v);
    void __thiscall bcc7e0(int delta);
    int  __thiscall bcc800();
    int  __thiscall bcc820();
    void __thiscall bcc860(int unused);
    void* __thiscall bcc500(int iid);
    void __thiscall ResetTool();                               // 0x00bcbc80 ret
};
// ---- items of slice s00bcc010 end

// @ 0x00bc0000
void FUN_00bc0000(void* planet)
{
    cGameNounManager* nm = SP_NounManager();
    GameDataVector* dv = (GameDataVector*)nm->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);

    int count = (int)(dv->mpEnd - dv->mpBegin);

    void** buf = 0;
    FUN_00b93c60(&buf, count, (char*)dv + 0x10);

    void* dest;
    FUN_00829110(&dest, dv->mpBegin, dv->mpEnd, buf, 0);
    void** end = (void**)dest;

    int n = ((PlanetRecord*)planet)->FUN_00c710c0();
    for (int i = 0; i < n; ++i) {
        WNode* node = ((PlanetRecord*)planet)->FUN_00c71030(i);
        void** vbase = node->mpBegin;
        int k = (int)(node->mpEnd - vbase);
        for (int j = 0; j < k; ++j) {
            float* p = ((UintArray*)vbase[j])->FUN_00572590();
            void** found = (void**)FUN_00bbc700(buf, end, p[0], p[1], p[2]);
            if (found != end) {
                void* access = node->FUN_00ff0420();
                ((Entry*)*found)->FUN_00bff6e0(access);
                if (found + 1 < end)
                    FUN_006782c0(found + 1, end, found);
                end -= 1;
                if (*end != 0)
                    ((Entry*)*end)->v04();
            }
        }
    }

    for (void** p = buf; p < end; ++p) {
        if (*p != 0)
            ((Entry*)*p)->v04();
    }
    if (buf != 0 && buf[-1] != 0)
        operator_delete__(buf);
}

// @ 0x00bc0180
void SimSelf::FUN_00bc0180(uint8_t flag)
{
    Entry** it  = (Entry**)mVec.mpBegin;
    Entry** end = (Entry**)mVec.mpEnd;
    for (; it != end; ++it)
        SP_NounManager()->RemoveNoun(*it);
    mVec.erase(mVec.mpBegin, mVec.mpEnd);

    if (flag == 0) {
        cGameNounManager* nm = SP_NounManager();
        GameDataVector* dv = (GameDataVector*)nm->GetGameDataVector(
            (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);
        void** begin = dv->mpBegin;
        void** dend  = dv->mpEnd;
        int cnt = (int)(dend - begin);

        Entry** buf = 0;
        if (cnt != 0)
            buf = (Entry**)EAAllocate(cnt * 4, "Simulator", 0, 0, (void*)0x13ebb38, 0xd1);

        void* out;
        FUN_00829110(&out, begin, dend, buf, 0);
        Entry** dstEnd = (Entry**)out;

        for (Entry** p = buf; p != dstEnd; ++p) {
            Entry* o = *p;
            mVec.push_back(&o);
        }
        for (Entry** p = buf; p != dstEnd; ++p) {
            if (*p != 0)
                (*p)->v04();
        }
        if (buf != 0 && buf[-1] != 0)
            operator_delete__(buf);
    }

    FUN_0067de30();

    uint32_t arrLocal = 0;
    int32_t  count2   = SP_PlanetModel()->mpPropMgr->GetPropertyVector(&arrLocal);
    uint32_t accepted = 0;
    for (int i = 0; i < count2; ++i) {
        PlanetRecord* planet = ((PlanetRecord**)arrLocal)[i];
        if (planet == 0)
            continue;
        cPropertyList* pl = planet->mpPropList;
        if (pl == 0)
            continue;
        Property* prop = 0;
        if (pl->GetProperty(0x3f6d22a, (void**)&prop) && prop->mnType == 1) {
            char* value = (char*)prop;
            if (prop->mnFlags & 0x30)
                value = (char*)prop->mpData;
            if (*value != 0)
                ++accepted;
        }
    }

    uint32_t budget = accepted;
    void* rec = FUN_010212a0();
    if (rec != FUN_01021370()) {
        void* p1 = ((PlanetRecord*)rec)->FUN_00b8de30();
        int   p2 = ((cSPGameDataUFO*)p1)->AddRef();
        void* p3 = FUN_00c6fe00((void*)(uint32_t)p2);
        void* p4 = FUN_0102f810(p3);
        float f1 = FUN_0102f8c0(p4);
        void* p5 = FUN_0102f810((void*)2);
        float f2 = FUN_0102f8c0(p5);
        budget = (uint32_t)(int32_t)((f1 / f2) * (float)(int)accepted);
    } else {
        budget = 1000;
    }

    for (int k = 0; k < count2; ++k) {
        PlanetRecord* planet = ((PlanetRecord**)arrLocal)[k];
        if (planet == 0)
            continue;
        cPropertyList* pl = planet->mpPropList;
        if (pl == 0)
            continue;
        Property* prop = 0;
        if (!pl->GetProperty(0x3f6d22a, (void**)&prop) || prop->mnType != 1)
            continue;
        char* value = (char*)prop;
        if (prop->mnFlags & 0x30)
            value = (char*)prop->mpData;
        if (*value == 0)
            continue;

        if (flag == 0) {
            Entry** vit = (Entry**)mVec.mpBegin;
            Entry** vend = (Entry**)mVec.mpEnd;
            bool placed = false;
            while (vit != vend) {
                if (placed)
                    break;
                Entry* c = *vit;
                float v1[3];
                float v2[3];
                float* f0 = SP_PlanetModel()->FUN_00b81630(v1, c->mSub.s2c());
                float* f1 = SP_PlanetModel()->FUN_00b81630(v2, planet->f0c);
                if (fabsf(f1[0] - f0[0]) > g_kEpsilon) { ++vit; continue; }
                if (fabsf(f1[1] - f0[1]) > g_kEpsilon) { ++vit; continue; }
                if (fabsf(f1[2] - f0[2]) > g_kEpsilon) { ++vit; continue; }
                c->mSub.s38(planet->f0c);
                float q[4];
                FUN_00472b80(q, &planet->p1c, 0.0f);
                c->mSub.s3c(q);
                c->FUN_00bfeaf0(planet);
                placed = true;
                ++vit;
            }
        } else {
            if ((uint)(mVec.mpEnd - mVec.mpBegin) < (uint)budget) {
                float dist = planet->f_6c;
                cPropertyList* pl2 = planet->mpPropList;
                if (((planet->flags4 >> 0x11) & 1) == 0 && pl2 != 0) {
                    Property* prop2 = 0;
                    if (pl2->GetProperty(0x254cf89, (void**)&prop2) && prop2->mnType == 0xd) {
                        char* v2 = (char*)prop2;
                        if (prop2->mnFlags & 0x30)
                            v2 = (char*)prop2->mpData;
                        dist = *(float*)v2;
                    }
                }
                Entry* node = (Entry*)SP_NounManager()->CreateNoun(0x403df5c);
                if (node != 0)
                    node = (Entry*)node->v0c((void*)0x403df5f);
                Entry* saved = node;
                if (node != 0)
                    node->v00();
                node->mSub.s40(dist);
                node->mSub.s38(planet->f0c);
                float q[4];
                FUN_00472b80(q, &planet->p1c, 0.0f);
                node->mSub.s3c(q);
                node->FUN_00bfeaf0(planet);
                mVec.push_back(&saved);
                if (saved != 0)
                    saved->v04();
            }
        }
    }

    if (flag != 0) {
        void* active = FUN_01021260();
        if (active != 0) {
            OtherVec* v = ((PlanetRecord*)active)->FUN_00c71020();
            if (v->mpBegin == v->mpEnd) {
                FUN_00bbfeb0(active);
                if (((PlanetRecord*)active)->FUN_00c70e00() == 4) {
                    FUN_00bc0000(active);
                    return;
                }
            } else {
                FUN_00bbff40(active);
            }
        }
    }
}
#pragma pack(pop)

// @ 0x00bc22b0
float __fastcall FUN_00bc22b0(void* thisptr, int)
{
    float acc = FLT_MAX_;
    float* base = (float*)((char*)thisptr + 0x1c);
    int outer = 2;
    do {
        float* p = base;
        for (int k = 0; k < 8; ++k) {
            float v = p[k * 2];
            if (v < acc)
                acc = v;
        }
        base += 0x10;
        --outer;
    } while (outer != 0);
    float* r = (float*)((char*)thisptr + 0x94);
    int inner = 9;
    do {
        float v = *r;
        if (v < acc)
            acc = v;
        r += 2;
        --inner;
    } while (inner != 0);
    return (float)sqrt((double)acc);
}

// @ 0x00bc24c0
unsigned __stdcall FUN_00bc24c0(float value)
{
    if (kFlt156cfb8 > value)
        return 0;
    if (kFlt156cfbc > value)
        return 1;
    if (kFlt156cfc0 > value)
        return 2;
    if (kFlt156cfc4 > value)
        return 3;
    return 0;
}

// @ 0x00bc2570
SP_NOINLINE float FUN_00bc2570(float* a, float* b, float* dir)
{
    float d1 = (dir[0] * a[0] + dir[1] * a[1]) + dir[2] * a[2];
    float r1[3];
    r1[0] = a[0] - dir[0] * d1;
    r1[1] = a[1] - dir[1] * d1;
    r1[2] = a[2] - dir[2] * d1;

    float d2 = (b[1] * dir[1] + b[2] * dir[2]) + b[0] * dir[0];
    float r2[3];
    r2[0] = b[0] - dir[0] * d2;
    r2[1] = b[1] - dir[1] * d2;
    r2[2] = b[2] - dir[2] * d2;

    return FUN_0069b760(r1, r2, dir);
}

// @ 0x00bc2830
void cTimeOfDay::SetDayLength(float len)
{
    FUN_00bc2670(len);
    mDayLength = len;
    g_dayScale = g_one;
    g_thr0 = mDayLength * 0.208f;
    g_thr1 = mDayLength * 0.297f;
    g_thr2 = mDayLength * 0.708f;
    g_thr3 = mDayLength * 0.792f;
}

// @ 0x00bc28c0
void cTimeOfDay::FUN_00bc28c0(float len)
{
    if (len != g_dayScale) {
        g_dayScale = len;
        FUN_00bc2670(mDayLength / len);
    }
}

// @ 0x00bc31c0
cSPTimer* cSPTimer::FUN_00bc31c0(SPTimeFn fn)
{
    extern char v_1465d54[];
    mUnk4 = 0;
    mElapsed = 0;
    mBase = 0;
    mRunning = 0;
    mVtbl = v_1465d54;
    mGetTime = fn;
    return this;
}

// @ 0x00bc34c0
C* __thiscall C::ctor(void* arg)
{
    ((B0*)this)->init(arg);
    vt0 = vt014667f0;
    vt1 = vt0145cf78;
    vt2 = vt014667ec;
    d3b4 = 0;
    b18 = 0;
    b19 = 0;
    f20 = 0.0f;
    f1c = 0.0f;
    f30 = 0.0f;
    f2c = 0.0f;
    f28 = 0.0f;
    f24 = 0.0f;
    f34 = 0.0f;
    f38 = 0.0f;
    s3c.set(g156d200v);
    s90.set(g156d20cv);
    f114 = 1.0f;
    f110 = 1.0f;
    f10c = 1.0f;
    f108 = 1.0f;
    bfc = 0;
    bfd = 0;
    f104 = 0.0f;
    f100 = 0.0f;
    f118 = 0.0f;
    f11c = 0.0f;
    b120 = 0;
    b121 = 0;
    f128 = 0.0f;
    f124 = 0.0f;
    f138 = g145cfe8;
    f134 = g145cfe8;
    f130 = g145cfe8;
    f12c = g145cfe8;
    f13c = 0.0f;
    f140 = 0.0f;
    f394 = 0.0f;
    b398 = 0;
    v39c = g168aab4;
    v3a8 = g168aab4;
    return this;
}

// @ 0x00bc3700
void __thiscall C::update(float dt)
{
    App1* app = App();
    Mgr* mgr = (Mgr*)(*(void* (__thiscall**)(App1*))(*(char**)app + 0x50))(app);
    Cam* cam = (Cam*)(*(void* (__thiscall**)(Mgr*))(*(char**)mgr + 0x1c))(mgr);
    cam->f7c4d00(&h2cc);
    cam->f7c4ba0(f310);
    cam->f7c4bc0(f314);
    PosHelper pos(cam);
    bool wasSnapped = b398 != 0;
    Q4 w;
    w.x = pos.x; w.y = pos.y; w.z = pos.z;
    f394 = dt;
    b398 = 0;
    if (f00b17c10(&pos, 0)) b398 = 1;
    if (b398 == 0) {
        if (f00b17810(&pos, 0)) b398 = 1;
        if (b398 == 0 && f00b182f0(&pos, 0x18)) b398 = 1;
    }
    float lenW = sqrtf(w.x * w.x + w.z * w.z + w.y * w.y);
    float lenCur = sqrtf(v39c.x * v39c.x + v39c.y * v39c.y + v39c.z * v39c.z);
    // NOTE: the original epilogue also frees an uninitialised stack slot ([esp+0x78]); omitted (UB).
    if (b398 == 0) {
        v3a8 = V3(w.x, w.y, w.z);
        float d = lenCur - lenW;
        if (d > 1.5258789e-05f) {
            float zero = 0.0f;
            float dd = d;
            const float* p = (d > 0.0f) ? &dd : &zero;
            float tgt = lenCur - ((*p * 0.4f + 1.0f) * g156d1fc) * f394;
            float inv = 1.0f / sqrtf(w.x * w.x + w.y * w.y + w.z * w.z + 1e-8f);
            w.x *= inv; w.y *= inv; w.z *= inv;
            const float* q = (tgt > lenW) ? &tgt : &lenW;
            float s = *q;
            v39c.x = w.x * s; v39c.y = w.y * s; v39c.z = w.z * s;
            if (wasSnapped) b398 = 1;
        }
    } else {
        if (wasSnapped) {
            float inv = 1.0f / sqrtf(w.x * w.x + w.y * w.y + w.z * w.z + 1e-8f);
            w.x *= inv; w.y *= inv; w.z *= inv;
            const float* q = (lenCur > lenW) ? &lenCur : &lenW;
            float s = *q;
            pos.x = w.x * s; pos.y = w.y * s; pos.z = w.z * s;
            pos.f17790(1);
        }
        FixedVec8 vec;
        vec.mpBegin = vec.mpEnd = vec.buf;
        vec.mpCap = vec.buf + 8;
        vec.overflow = 0;
        bool c1 = f00b17c10(&pos, &vec);
        if (c1) {
            f00b16450(&pos, &vec);
            pos.f17790(1);
        }
        w.w = 0.0f;
        bool c2 = f00b17810(&pos, &w);
        if (c2) f00b16e50(&pos, &w);
        bool c3 = f00b182f0(&pos, 0x18);
        if (!c1 && !c2 && !c3) {
            v3a8 = pos;
        } else {
            float d = lenCur - lenW;
            float zero = 0.0f;
            float dd = d;
            const float* p = (d > 0.0f) ? &dd : &zero;
            float f = ((*p * 0.4f + 1.0f) * g156d1fc) * f394;
            float inv = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
            pos.x = pos.x * inv * f + pos.x;
            pos.y = pos.y * inv * f + pos.y;
            pos.z = pos.z * inv * f + pos.z;
        }
        v39c = pos;
        vec.dtor();
    }
    if (b398) {
        h2cc.v[0] = v39c.x;
        h2cc.v[1] = v39c.y;
        h2cc.flags |= 4;
        h2cc.count++;
        h2cc.v[2] = v39c.z;
    }
}

// @ 0x00bc3c20
void* __stdcall FUN_00bc3c20(void* out, char* obj, const float* v2, float f)
{
    float ax = *(float*)(obj + 4), ay = *(float*)(obj + 8), az = *(float*)(obj + 0xc);
    float bx = *(float*)(obj + 0x10), by = *(float*)(obj + 0x14), bz = *(float*)(obj + 0x18);
    float ia = 1.0f / sqrtf(az * az + (ax * ax + ay * ay) + 1e-8f);
    float ib = 1.0f / sqrtf((bx * bx + by * by) + bz * bz + 1e-8f);
    bx *= ib; by *= ib; bz *= ib;
    if (*(char*)(obj + 0x7bd)) f = 1.0f;
    float s = v2[0] * f;
    float t = v2[1] * f;
    V3 r;
    r.x = (by * (ia * az) - bz * (ay * ia)) * s + ax + bx * t;
    r.y = (bz * (ia * ax) - (ia * az) * bx) * s + ay + by * t;
    r.z = (bx * (ay * ia) - by * (ia * ax)) * s + az + bz * t;
    void* pm = PlanetModel(out, &r, 0);
    ((PM*)pm)->f00b82970();
    return out;
}

// @ 0x00bc3db0
uint32_t __thiscall Reg::findValue(int key)
{
    LNode* n = head;
    while (n != LIST_END(this)) {
        if (n->key == key) {
            if (n->b7dd != 0) return 0;
            return n->f7e4;
        }
        n = n->next;
    }
    return 0;
}

// @ 0x00bc3df0
uint8_t __thiscall Reg::isDisabled(int key)
{
    LNode* n = head;
    while (n != LIST_END(this)) {
        if (n->key == key) return n->b7dd;
        n = n->next;
    }
    return 1;
}

// @ 0x00bc3e20
void __thiscall Reg::setFlag(int key, uint32_t v)
{
    LNode* n = head;
    while (n != LIST_END(this)) {
        if (n->key == key) { n->f7d8 = v; return; }
        n = n->next;
    }
    *(uint32_t*)0x7d0 = v;
}

// @ 0x00bc3ec0
Elem98* __cdecl FUN_00bc3ec0(Elem98* first, Elem98* last, Elem98* dst)
{
    while (first != last) {
        freeBuf(first->mpBegin);
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00bc3f10
void __stdcall FUN_00bc3f10(Elem98* first, Elem98* last)
{
    for (; first < last; ++first) freeBuf(first->mpBegin);
}

// @ 0x00bc4030
uint32_t* __cdecl FUN_00bc4030(const uint32_t* first, const uint32_t* last, uint32_t* dst)
{
    for (; first != last; ++first) { *dst = *first; ++dst; }
    return dst;
}

// @ 0x00bc40a0
void __thiscall VecA12::insert(A12* pos, const A12* first, const A12* last, int tag)
{
    if (first == last) return;
    unsigned n = last - first;
    A12* out;
    if (n <= (unsigned)(mpCap - mpEnd)) {
        A12* end = mpEnd;
        unsigned tail = end - pos;
        if (n < tail) {
            A12* mid = end - n;
            FUN_00512050(&out, mid, end, end, tag);
            mpEnd += n;
            copy_backward12(pos, mid, end);
            copy12(first, last, pos);
            return;
        }
        const A12* split = first + tail;
        FUN_00512050(&out, (A12*)split, (A12*)last, end, tag);
        mpEnd += n - tail;
        FUN_00512050(&out, pos, end, mpEnd, tag);
        mpEnd += tail;
        copy_backward12((A12*)first, (A12*)split, pos + tail);
        return;
    }
    unsigned sz = mpEnd - mpBegin;
    unsigned cap = sz * 2;
    if (sz == 0) cap = 1;
    if (cap <= n + sz) cap = n + sz;
    A12* nb = cap ? (A12*)operator_new(cap * 12, kSimulator, 0, 0, kAllocFile, 0xd1) : 0;
    A12* p = FUN_00a11310(mpBegin, pos, nb);
    FUN_00512050(&out, (A12*)first, (A12*)last, p, tag);
    A12* ne = FUN_00a11310(pos, mpEnd, out);
    freeBuf(mpBegin);
    mpBegin = nb;
    mpEnd = ne;
    mpCap = nb + cap;
}

// @ 0x00bc4280
void __cdecl FUN_00bc4280(Elem98* arr, unsigned n, const Elem98* src)
{
    if (n > 0) do {
        if (arr) {
            arr->overflow = 0;
            arr->mpBegin = arr->buf;
            arr->mpEnd = arr->buf;
            arr->mpCap = arr->buf + 32;
            arr->assign(src);
        }
        --n;
        ++arr;
    } while (n > 0);
}

// @ 0x00bc4310
Elem98* __cdecl FUN_00bc4310(const Elem98* first, const Elem98* last, Elem98* dst)
{
    while (first != last) {
        if (dst) {
            dst->overflow = 0;
            dst->mpBegin = dst->buf;
            dst->mpEnd = dst->buf;
            dst->mpCap = dst->buf + 32;
            dst->assign(first);
        }
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00bc4370
Elem98** __cdecl FUN_00bc4370(Elem98** out, const Elem98* first, const Elem98* last, Elem98* dst)
{
    *out = dst;
    for (; first != last; ++first) {
        Elem98* e = *out;
        if (e) {
            e->mpBegin = e->buf;
            e->mpEnd = e->buf;
            e->overflow = 0;
            e->mpCap = e->buf + 32;
            e->assign(first);
        }
        *out = *out + 1;
    }
    return out;
}

// @ 0x00bc43d0
void __thiscall VecU32::insert(uint32_t* pos, const uint32_t* first, const uint32_t* last, int tag)
{
    if (first == last) return;
    unsigned n = last - first;
    if (n <= (unsigned)(mpCap - mpEnd)) {
        uint32_t* end = mpEnd;
        unsigned tail = end - pos;
        if (n < tail) {
            uint32_t* mid = end - n;
            FUN_00bc4_move(end, mid, (char*)end - (char*)mid);
            mpEnd += n;
            memmove(end - (mid - pos), pos, (char*)mid - (char*)pos);
            FUN_00bc4030(first, last, pos);
            return;
        }
        FUN_00bc4030(first + tail, last, end);
        mpEnd += n - tail;
        FUN_00bc4_move(mpEnd, pos, tail * 4);
        mpEnd += tail;
        FUN_00c16090(first, first + tail, pos + tail);
        return;
    }
    unsigned sz = mpEnd - mpBegin;
    unsigned cap = sz * 2;
    if (sz == 0) cap = 1;
    if (cap <= n + sz) cap = n + sz;
    uint32_t* nb = cap ? (uint32_t*)operator_new(cap * 4, kSimulator, 0, 0, kAllocFile, 0xd1) : 0;
    unsigned head = (char*)pos - (char*)mpBegin;
    uint32_t* p = (uint32_t*)FUN_00bc4_move(nb, mpBegin, head);
    uint32_t* d = p + (head >> 2);
    do { *d = *first; ++first; ++d; } while (first != last);
    unsigned rest = (char*)mpEnd - (char*)pos;
    uint32_t* q = (uint32_t*)FUN_00bc4_move(d, pos, rest);
    uint32_t* ne = q + (rest >> 2);
    freeBuf(mpBegin);
    mpEnd = ne;
    mpBegin = nb;
    mpCap = nb + cap;
}

// @ 0x00bc4630
Big::Big()
{}

// @ 0x00bc4730
void PropRecord::destroy()
{
    char* begin = mName.mpBegin;
    if ((mName.mpCapacity - begin) > 1 && begin != 0 && begin != mName.mpBuffer)
        operator_delete__(begin);

    ElemVecOps* lv = (ElemVecOps*)&mLists;
    lv->destroyRange(lv->mpBegin, lv->mpEnd);
    freeBuf(lv->mpBegin);
    freeBuf(mVec2B.mpBegin);
    freeBuf(mVec3.mpBegin);
    freeBuf(mFlags.mpBegin);
    freeBuf(mAngles.mpBegin);
    freeBuf(mVec2A.mpBegin);
    freeBuf(mIndices.mpBegin);
}

// @ 0x00bc4820
Entry_s00bc_4730* Entry_s00bc_4730::init()
{
    rec.init();
    mCreatures.init();
    mA878.init();
    mSounds.init();
    mFx.init();
    return this;
}

// @ 0x00bc4900
bool Reg_s00bc_4730::tryMove(Creature* c, Creature* dest, int flag)
{
    Node* end = &mSentinel;
    Node* node = mSentinel.mpNext;
    while (node != end) {
        if ((Creature*)node->mEntry.mKey == c)
            break;
        node = node->mpNext;
    }
    if (node == end)
        return 0;
    Entry_s00bc_4730* e = &node->mEntry;
    if (e->mDisabled)
        return 0;
    if (e->mBusy == 0)
        return 0;

    int i = (int)(e->mCreatures.mpEnd - e->mCreatures.mpBegin);
    if (dest) {
        (*(void (__thiscall**)(Creature*))**(void***)dest)(dest);
    }
    E1C7F0(&e->mCreatures, 0, &dest);
    if (dest)
        (*(void (__thiscall**)(Creature*))((*(void***)dest)[1]))(dest);

    float* mv = (float*)&e->rec.mVec2A.mpBegin[i];
    Vector2 v2;
    v2.x = mv[0];
    v2.y = mv[1];

    float scale = dest->loco.GetScale();
    Vector3 off;
    Vector3* o = BuildOffset(&off, e, (const float*)&v2, scale);
    Vector3 pos;
    pos.x = o->x; pos.y = o->y; pos.z = o->z;

    float angle = e->rec.mAngles.mpBegin[i];
    Vector3 facing;
    if (e->rec.mValue0 == 1) {
        facing.x = e->rec.mVec3.mpBegin[0].x;
        facing.y = e->rec.mVec3.mpBegin[0].y;
        facing.z = e->rec.mVec3.mpBegin[0].z;
    } else {
        Vector3* sn = (Vector3*)PlanetSnapB(0, &e->rec.mVec3.mpBegin[0], 0);
        Vector3 d;
        d.x = sn->x - pos.x;
        d.y = sn->y - pos.y;
        d.z = sn->z - pos.z;
        facing = *normalized_safe(0, &d);
    }
    if (angle != 0.0f) {
        Vector3* n = normalized_safe(0, &pos);
        float s = sinf(angle * 0.5f);
        float c = cosf(angle * 0.5f);
        float q[4];
        q[0] = n->x * s;
        q[1] = n->y * s;
        q[2] = n->z * s;
        q[3] = c;
        facing = *(Vector3*)QuatMulVec3(0, q, &facing);
    }
    if (e->rec.mFlags.mpBegin[i] == 1) {
        (*(void (__thiscall**)(Creature*, void*))((*(void***)dest)[0x39]))(dest, (char*)this + 0x68);
        SetSkinFlag(e, 1);
    }
    if (flag == 0) {
        dest->MoveToPointAndFacingAtSpeed(2, &pos, &facing, 0.1f, scale);
        --e->mBusy;
        return 1;
    }
    void* op = PlanetBuildSurface(0, &pos, &facing);
    dest->SetFacing(op);
    --e->mBusy;
    return 1;
}

// @ 0x00bc4bf0
void Reg_s00bc_4730::resetEntry(Entry_s00bc_4730* e)
{
    // every pass below is an eastl erase(begin, end): a byte-count guard, the release loop and
    // then `end() -= (last - first)`; the byte form matters because the compiler truncates the
    // difference before it is turned back into elements.
    char* soundBase = (char*)e->mSounds.mpBegin;
    int soundBytes = (int)((char*)e->mSounds.mpEnd - soundBase);
    if ((soundBytes & ~3) > 0) {
        int soundCount = soundBytes >> 2;
        for (int i = 0; i < soundCount; ++i) {
            void* snd = ((void**)soundBase)[i];
            void* sys = GetAudioSystem();
            if (sys) {
                (*(void (__thiscall**)(void*, int))((*(void***)sys)[0x0e]))(sys, 0x347536b);
                (*(void (__thiscall**)(void*, int, void*))((*(void***)sys)[0x10]))(sys, 0x3475385, snd);
                (*(void (__thiscall**)(void*, int, int))((*(void***)sys)[0x10]))(sys, 0x34753a0, 0);
                (*(void (__thiscall**)(void*))((*(void***)sys)[0x16]))(sys);
            }
        }
    }

    void** fxBegin = e->mFx.mpBegin;
    void** fxEnd = e->mFx.mpEnd;
    int fxBytes = (int)((char*)fxEnd - (char*)fxBegin);
    if ((fxBytes & ~3) > 0) {
        int fxCount = fxBytes >> 2;
        for (int i = 0; i < fxCount; ++i) {
            void* fx = fxBegin[i];
            if (fx)
                (*(void (__thiscall**)(void*, int))((*(void***)fx)[3]))(fx, 1);
        }
    }
    void** r = VectorErasePtr(fxEnd, fxEnd, fxBegin);
    for (; r < e->mFx.mpEnd; ++r) {
        if (*r)
            (*(void (__thiscall**)(void*))((*(void***)*r)[1]))(*r);
    }
    e->mFx.mpEnd = (void**)((char*)e->mFx.mpEnd - ((fxBytes >> 2) * 4));

    e->mDisabled = 1;

    void** crBegin = e->mCreatures.mpBegin;
    void** crEnd = e->mCreatures.mpEnd;
    int crBytes = (int)((char*)crEnd - (char*)crBegin);
    void** c = VectorCopyPtr(crEnd, crEnd, crBegin);
    for (; c < e->mCreatures.mpEnd; ++c) {
        if (*c)
            (*(void (__thiscall**)(void*))((*(void***)*c)[1]))(*c);
    }
    e->mCreatures.mpEnd = (void**)((char*)e->mCreatures.mpEnd - ((crBytes >> 2) * 4));
}

// @ 0x00bc4d60
void Reg_s00bc_4730::resetAll()
{
    Node* end = &mSentinel;
    for (Node* n = mSentinel.mpNext; n != end; n = n->mpNext)
        resetEntry(&n->mEntry);
}

// @ 0x00bc4df0
void ElemVec::insert(Elem98_s00bc_4730* pos, unsigned n, const Elem98_s00bc_4730* val)
{
    if (n == 0)
        return;
    if (n > capacity() - size()) {
        unsigned oldSize = size();
        unsigned len = oldSize + n;
        unsigned cap = oldSize * 2;
        if (oldSize == 0)
            cap = 1;
        if (cap < len)
            cap = len;
        Elem98_s00bc_4730* newBuf;
        if (cap != 0)
            newBuf = (Elem98_s00bc_4730*)operator_new(cap * 0x98, kSimulator, 0, 0, kAllocFile, 0xd1);
        else
            newBuf = 0;
        Elem98_s00bc_4730* mid = ElemVecCopyConstruct(mpBegin, pos, newBuf);
        ElemVecFreeN(mpBegin, pos, newBuf);
        ElemVecFillN(mid, n, val);
        Elem98_s00bc_4730* after = mid + n;
        Elem98_s00bc_4730* tail = ElemVecCopyConstruct(pos, mpEnd, after);
        ElemVecFreeN(pos, mpEnd, after);
        freeBuf(mpBegin);
        mpEnd = tail;
        mpBegin = newBuf;
        mpCapacity = newBuf + cap;
        return;
    }

    Elem98_s00bc_4730 tmp;
    tmp.init();
    tmp.assign(*val);
    unsigned tailCount = (unsigned)(mpEnd - pos);
    if (n < tailCount) {
        Elem98_s00bc_4730* first = mpEnd - n;
        void* sret;
        ElemVecInsertCopy(&sret, first, mpEnd, mpEnd);
        mpEnd = mpEnd + n;
        ElemVecCopyBack(pos, first, mpEnd);
        ElemVecFillRange(pos, pos + n, &tmp);
    } else {
        ElemVecFillN(mpEnd, n - tailCount, &tmp);
        mpEnd = mpEnd + (n - tailCount);
        Elem98_s00bc_4730* mid = mpEnd - (n - tailCount);
        void* sret;
        ElemVecInsertCopy(&sret, pos, mid, mpEnd);
        mpEnd = mpEnd + tailCount;
        ElemVecFillRange(pos, mid, &tmp);
    }
    freeBuf(tmp.mpBegin);
}

// @ 0x00bc5040
void Reg_s00bc_4730::resetByKey(uint32_t key)
{
    for (Node* n = mSentinel.mpNext; n != &mSentinel; n = n->mpNext) {
        if (n->mEntry.mKey == key) {
            resetEntry(&n->mEntry);
            return;
        }
    }
}

// @ 0x00bc5070
ElemVec* ElemVec::assign(const ElemVec& src)
{
    if (this == &src)
        return this;
    Elem98_s00bc_4730* sfirst = src.mpBegin;
    unsigned n = (unsigned)(src.mpEnd - sfirst);
    if (n > capacity()) {
        Elem98_s00bc_4730* newBuf = ElemVecAllocN(n, sfirst, src.mpEnd);
        ElemVecOps* self = (ElemVecOps*)this;
        self->destroyRange(mpBegin, mpEnd);
        freeBuf(mpBegin);
        mpBegin = newBuf;
        mpEnd = newBuf + n;
        mpCapacity = newBuf + n;
        return this;
    }
    unsigned cur = size();
    if (cur < n) {
        // assign the overlapping prefix, then copy-construct the tail into the spare slots
        ElemVecAssignRange(sfirst, sfirst + cur, mpBegin);
        void* sret;
        ElemVecInsertCopy(&sret, sfirst + cur, src.mpEnd, mpEnd);
        mpEnd = mpBegin + n;
    } else {
        ElemVec* r = (ElemVec*)ElemVecAssignRange(sfirst, sfirst + n, mpBegin);
        ElemVecOps* self = (ElemVecOps*)this;
        self->destroyRange((Elem98_s00bc_4730*)r, mpEnd);
        mpEnd = mpBegin + n;
    }
    return this;
}

// @ 0x00bc51c0
Node* Reg_s00bc_4730::newNode()
{
    Node* p;
    while (mAlloc.mpFree == 0) {
        if (!mAlloc.AddCore(0, 0)) {
            p = 0;
            goto construct;
        }
    }
    p = mAlloc.mpFree;
    mAlloc.mpFree = p->mpNext;
construct:
    Entry_s00bc_4730* e = 0;
    if (p != 0)
        e = p->mEntry.init();
    p->mpNext = (Node*)(void*)&mRoot;
    p->mpPrev = mRoot.mpPrev;
    mRoot.mpPrev->mpNext = p;
    mRoot.mpPrev = p;
    return (Node*)(void*)e;
}

// @ 0x00bc5210
void PropVecA::destroy()
{
    PropRecord* p = mpBegin;
    PropRecord* last = mpEnd;
    while (p < last) {
        p->destroy();
        p = (PropRecord*)((char*)p + 0x7b4);
    }
    freeBuf(mpBegin);
}

// @ 0x00bc52a0
void Reg_s00bc_4730::enable(uint32_t key, Creature* c)
{
    Node* end = &mSentinel;
    for (Node* n = mSentinel.mpNext; n != end; n = n->mpNext) {
        if (n->mEntry.mKey != key)
            continue;
        void** first = n->mEntry.mCreatures.mpBegin;
        void** last = n->mEntry.mCreatures.mpEnd;
        bool found = false;
        for (void** p = first; p != last; ++p) {
            if (*p == c) {
                found = true;
                break;
            }
        }
        if (found) {
            ++n->mEntry.mBusy;
            resetByKey(key);
        }
        return;
    }
}

// @ 0x00bc5300
void PropVecB::destroy()
{
    PropRecord* p = mpBegin;
    PropRecord* last = mpEnd;
    while (p < last) {
        p->destroy();
        p = (PropRecord*)((char*)p + 0x7b4);
    }
    freeBuf(mpBegin);
}

// @ 0x00bc5340
void ElemVec::resize(unsigned n)
{
    if (n > size()) {
        Elem98_s00bc_4730 tmp;
        tmp.init();
        insert(mpEnd, n - size(), &tmp);
        freeBuf(tmp.mpBegin);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00bc53f0
void Reg_s00bc_4730::teardown()
{
    Node* end = &mSentinel;
    Node* n = mSentinel.mpNext;
    while (n != end) {
        Node* next = n->mpNext;
        Entry_s00bc_4730* e = &n->mEntry;
        for (void** p = e->mFx.mpBegin; p < e->mFx.mpEnd; ++p) {
            if (*p)
                (*(void (__thiscall**)(void*))((*(void***)*p)[1]))(*p);
        }
        freeBuf(e->mFx.mpBegin);
        freeBuf(e->mSounds.mpBegin);
        freeBuf(e->mA878.mpBegin);
        for (void** p = e->mCreatures.mpBegin; p < e->mCreatures.mpEnd; ++p) {
            if (*p)
                (*(void (__thiscall**)(void*))((*(void***)*p)[1]))(*p);
        }
        freeBuf(e->mCreatures.mpBegin);
        e->rec.destroy();
        n->mpNext = mAlloc.mpFree;
        mAlloc.mpFree = n;
        n = next;
    }
}

// @ 0x00bc54f0
void PropRecord::copyFrom(const PropRecord& src)
{
    mValue0 = src.mValue0;
    mCount = src.mCount;

    mIndices.init();
    mIndices = *(const fixed_vector<uint32_t, 8>*)&src.mIndices;

    mVec2A.init();
    mVec2A = *(const fixed_vector<Vector2, 32>*)&src.mVec2A;

    mAngles.init();
    mAngles = *(const fixed_vector<float, 32>*)&src.mAngles;

    mFlags.init();
    mFlags = *(const fixed_vector<uint8_t, 32>*)&src.mFlags;

    mVec3.init();
    mVec3 = *(const fixed_vector<Vector3, 2>*)&src.mVec3;

    mVec2B.init();
    mVec2B = *(const fixed_vector<Vector2, 2>*)&src.mVec2B;

    mLists.init();
    mLists = *(const fixed_vector<Elem98_s00bc_4730, 8>*)&src.mLists;

    mName.mpBegin = mName.mpBuffer = mName.mBuffer;
    mName.mpEnd = mName.mBuffer;
    mName.mpCapacity = mName.mBuffer + 32;
    mName.mBuffer[0] = 0;
    {
        const char* first = src.mName.mpBegin;
        size_t n = (size_t)(src.mName.mpEnd - first);
        if ((size_t)(mName.mpCapacity - mName.mpBegin) < n) {
            char* buf = (char*)operator_new((unsigned)(n + 1), kSimulator, 0, 0, kAllocFile, 0xd1);
            mName.mpBegin = mName.mpEnd = buf;
            mName.mpCapacity = buf + n + 1;
        }
        memcpy(mName.mpBegin, first, n);
        mName.mpBegin[n] = 0;
        mName.mpEnd = mName.mpBegin + n;
    }

    mF78C = src.mF78C;
    mF790 = src.mF790;
    mU794 = src.mU794;
    mU798 = src.mU798;
    mB79C = src.mB79C;
    mB79D = src.mB79D;
    mU7A0 = src.mU7A0;
    mU7A4 = src.mU7A4;
    mU7A8 = src.mU7A8;
    mBitMask = src.mBitMask;
    mFourCC = src.mFourCC;
}

// @ 0x00bc5730
bool ReadPropRecord(uint32_t instance, uint32_t group, PropRecord_s00bc_5730* out)
{
    AutoRefCount<cPropertyList_s00bc_5730> list;
    if (!PropertyManager()->GetPropertyList(instance, group, &list.mpObject))
        return false;

    string16 name;
    int count = 0;
    for (int i = 1; i <= 12; ++i) {
        if (list.mpObject->HasProperty(0x0486668f + i))
            count = i;
    }
    if (count <= 0)
        return false;

    out->mValue0 = PropUInt32(list.mpObject, 0x048665c7, 0);
    if (GetPropertyAsString16(list.mpObject, 0x04ab07c9, name))
        out->mName = ConvertToString8(name).c_str();

    out->mLists.resize(count);
    for (int k = 0; k < count; ++k) {
        Elem98_s00bc_5730& e = out->mLists[k];
        int n = 0;
        uint32_t* values = 0;
        if (GetPropertyAsUint32Array(list.mpObject, 0x04866690 + k, &n, &values)) {
            e.resize(n);
            for (int i = 0; i < n; ++i)
                e[i].a = values[i];

            int m = 0;
            uint32_t* v1;
            if (GetPropertyAsUint32Array(list.mpObject, 0x048666a0 + k, &m, &v1)) {
                if (m > n)
                    m = n;
                for (int i = 0; i < m; ++i)
                    e[i].b = v1[i];
            }
            for (int i = m; i < n; ++i)
                e[i].b = 0;

            m = 0;
            uint32_t* v2;
            if (GetPropertyAsUint32Array(list.mpObject, 0x048666b0 + k, &m, &v2)) {
                if (m > n)
                    m = n;
                for (int i = 0; i < m; ++i)
                    e[i].c = v2[i];
            }
            for (int i = m; i < n; ++i)
                e[i].c = 0xffffffff;

            uint32_t* v3;
            if (GetPropertyAsUint32Array(list.mpObject, 0x048666c0 + k, &m, &v3)) {
                if (m > n)
                    m = n;
                for (int i = 0; i < m; ++i)
                    e[i].d = v3[i];
            }
            for (int i = m; i < n; ++i)
                e[i].d = 0;
        }
    }

    int total;
    uint32_t* indices;
    if (GetPropertyAsUint32Array(list.mpObject, 0x04877bf5, &total, &indices)) {
        out->mCount = total;
        out->mIndices.insert(out->mIndices.begin(), indices, indices + total);
    } else {
        out->mCount = count;
        total = count;
        out->mIndices.resize_inline(count);
        for (int i = 0; i < total; ++i)
            out->mIndices[i] = i;
    }

    int n;
    out->mVec2A.resize_inline(total);
    Vector2_s00bc_5730* vec2;
    if (GetPropertyAsVector2Array(list.mpObject, 0x04879d5a, &n, &vec2)) {
        if (n > total)
            n = total;
        int i;
        for (i = 0; i < n; ++i)
            out->mVec2A[i] = vec2[i];
        for (; i < total; ++i)
            out->mVec2A[i] = Vector2_s00bc_5730(0.0f, 0.0f);
    }

    out->mAngles.resize_inline(total);
    float* angles;
    if (GetPropertyAsFloatArray(list.mpObject, 0x049a2146, &n, &angles)) {
        if (n > total)
            n = total;
        int i;
        for (i = 0; i < n; ++i)
            out->mAngles[i] = angles[i] * kAngleScale * 0.0027777778f;
        for (; i < total; ++i)
            out->mAngles[i] = 0.0f;
    }

    out->mFlags.resize_inline(total);
    bool* flags;
    int i = 0;
    if (GetPropertyAsBoolArray(list.mpObject, 0x0611b46c, &n, &flags)) {
        if (n > total)
            n = total;
        for (; i < n; ++i)
            out->mFlags[i] = flags[i];
    }
    for (; i < total; ++i)
        out->mFlags[i] = false;

    out->mF78C = PropFloat(list.mpObject, 0x048a40a6, 0.0f);
    out->mF790 = PropFloat(list.mpObject, 0x048a40a7, 100.0f);
    out->mU794 = PropUInt32(list.mpObject, 0x049a3514, 0);
    out->mU798 = PropUInt32(list.mpObject, 0x04f38120, 0);
    out->mU7A0 = PropUInt32(list.mpObject, 0x04f38139, 0);
    out->mB79C = PropBool(list.mpObject, 0x05107c07, false);
    out->mU7A4 = PropUInt32(list.mpObject, 0x0564cc3e, 0xffffffff);
    out->mU7A8 = PropUInt32(list.mpObject, 0x0564e207, 0);
    out->mB79D = PropBool(list.mpObject, 0x05b05121, false);

    out->mFourCC = 0;
    string16 code;
    if (GetPropertyAsString16(list.mpObject, 0x057fb0b6, code)) {
        string8 code8 = ConvertToString8(code);
        char buf[256];
        strcpy(buf, code8.c_str());
        out->mFourCC = ((((uint32_t)(uint8_t)buf[3] << 8 | (uint8_t)buf[2]) << 8 |
                         (uint8_t)buf[1]) << 8) | (uint8_t)buf[0];
    }

    out->mBitMask = 0;
    int nBits = 0;
    uint32_t* bits = 0;
    if (GetPropertyAsUint32Array(list.mpObject, 0x056cd5ea, &nBits, &bits)) {
        for (int b = 0; b < nBits; ++b)
            out->mBitMask |= 1 << bits[b];
    }

    int nPos;
    Vector3_s00bc_5730* pos;
    if (GetPropertyAsVector3Array(list.mpObject, 0x0508d625, &nPos, &pos)) {
        out->mVec3.clear();
        out->mVec3.insert(out->mVec3.begin(), pos, pos + nPos);
        out->mVec2B.resize_inline(nPos);
        int nUV;
        Vector2_s00bc_5730* uv;
        if (GetPropertyAsVector2Array(list.mpObject, 0x0508d626, &nUV, &uv)) {
            if (nUV > nPos)
                nUV = nPos;
            int j;
            for (j = 0; j < nUV; ++j)
                out->mVec2B[j] = uv[j];
            // The original's zero-fill writes into mVec2A (+0x40), not mVec2B.
            for (; j < nPos; ++j)
                out->mVec2A[j] = Vector2_s00bc_5730(0.0f, 0.0f);
        }
    }
    return true;
}

// @ 0x00bc6360
Sub& Sub::Assign(const Sub& src)
{
    f00 = src.f00;
    f04 = src.f04;
    v08 = src.v08;
    v40 = src.v40;
    v158 = src.v158;
    v1f0.assign(src.v1f0);
    v228 = src.v228;
    v258 = src.v258;
    v280.CopyFrom(src.v280);
    VecD* s = (VecD*)&src.v758;
    VecD* dst = &v758;
    if (dst != s) {
        if (dst->b != dst->e) {
            *dst->b = 0;
            dst->e = dst->b;
        }
        dst->assign(s->b, s->e);
    }
    f78c = src.f78c;
    f790 = src.f790;
    d794 = src.d794;
    d798 = src.d798;
    b79c = src.b79c;
    b79d = src.b79d;
    d7a0 = src.d7a0;
    d7a4 = src.d7a4;
    d7a8 = src.d7a8;
    d7ac = src.d7ac;
    d7b0 = src.d7b0;
    return *this;
}

// @ 0x00bc64a0
int SimClass::CreateEntry(int a, int b, const V3_s00bc_6360* pa, const V3_s00bc_6360* pb)
{
    list.Init();
    EntryB* e = (EntryB*)((char*)list.prev + 8);
    e->key = (int)count;
    count++;
    ReadPropRecord(a, b, &e->sub);
    e->f1c = 0.0f;
    int anim = (int)e->sub.f04;
    e->busy = anim;
    b = 0;
    e->anim.Build(anim, &b);
    e->a = *pa;
    e->b = *pb;
    e->b7d4 = 0;
    e->disabled = 0;
    e->state = 0;
    return e->key;
}

// @ 0x00bc65f0
int SimClass::CreateEntryCopy(const Sub* src, const V3_s00bc_6360* pa, const V3_s00bc_6360* pb)
{
    list.Init();
    EntryB* e = (EntryB*)((char*)list.prev + 8);
    e->key = (int)count;
    count++;
    const Sub& s = *src;
    e->sub.Assign(s);
    e->f1c = 0.0f;
    int anim = (int)s.f04;
    e->busy = anim;
    src = 0;
    e->anim.Build(anim, (int*)&src);
    e->a = *pa;
    e->b = *pb;
    e->b7d4 = 0;
    e->disabled = 0;
    e->state = 0;
    return e->key;
}

// @ 0x00bc6690
void __thiscall Reg_s00bc_6360::Update(int, int)
{
    for (Node_s00bc_6360* node = head; node != LIST_END_s00bc_6360(this); node = node->next) {
        Entry_s00bc_6360* e = &node->e;
        if (e->busy != 0 || e->disabled != 0) continue;
        int n = e->crEnd - e->crBegin;
        if (e->state != 2) {
            if (!e->b7d4) {
                e->b7d4 = 1;
                for (int i = 0; i < n; ++i) {
                    if (!e->crBegin[i]->loco.IsNearGoal()) { e->b7d4 = 0; break; }
                }
            }
            if (!e->b7d4) continue;
            switch (e->state) {
            case 1: {
                bool pending = false;
                for (int i = 0; i < n; ++i) {
                    Elem98_s00bc_6360* l = &e->lists[e->indices[i]];
                    Creature_s00bc_6360* c = e->crBegin[i];
                    if (c && c->GetTypeId() == 0x18eb4b7) {
                        Elem16* f = l->mpBegin;
                        if (f->c != -1 && f->d == 0xb)
                            pending |= (c->f00c25480(f->c, 0) == 0);
                    }
                }
                if (!pending) e->state = 2;
                break;
            }
            case 0: {
                e->state = 2;
                for (int i = 0; i < n; ++i) {
                    Elem98_s00bc_6360* l = &e->lists[e->indices[i]];
                    Creature_s00bc_6360* c = e->crBegin[i];
                    if (c && c->GetTypeId() == 0x18eb4b7) {
                        Elem16* f = l->mpBegin;
                        if (f->c != -1) {
                            if (f->d == 0xb) {
                                e->state = 1;
                                c->f00c25480(f->c, 0);
                            } else {
                                c->SetCurrentToolEffect(f->c, c->GetBodyPartIndex(f->d, 0));
                            }
                        }
                    }
                }
                break;
            }
            }
            if (e->state != 2) continue;
            // sequence just started: interrupt, play sound, spawn effects
            for (int i = 0; i < n; ++i) {
                Creature_s00bc_6360* c = e->crBegin[i];
                c->InterruptAnimation(e->lists[e->indices[i]].mpBegin->a, -1, 0);
                c->f00c0e640(e->f7d0);
            }
            if (e->nameBegin != e->nameEnd)
                e->crBegin[0]->StartIndependentSound(e->nameBegin, &e->a, &e->soundIds);
            if (e->fxBegin != e->fxEnd) {
                FxVec* v = &e->fx;
                unsigned cnt = e->fxEnd - e->fxBegin;
                if (cnt > (unsigned)(v->mpEnd - v->mpBegin)) {
                    Effect* nul = 0;
                    v->insertFill(v->mpEnd, cnt - (v->mpEnd - v->mpBegin), &nul);
                } else {
                    v->erase(v->mpBegin + cnt, v->mpEnd);
                }
                for (int i = 0; i < (int)cnt; ++i) {
                    EffectsMgr* fm = GetEffectsManager();
                    Effect** slot = &v->mpBegin[i];
                    if (*slot) { Effect* o = *slot; *slot = 0; o->Release(); }
                    if (fm->CreateEffect(e->fxBegin[i].id, 0, slot)) {
                        float s = e->crBegin[0]->loco.GetScale();
                        V3_s00bc_6360 pos3;
                        FUN_00bc3c20(&pos3, (char*)e, (const float*)&e->fxPos[i], s);
                        Transform t;
                        t.SetOffset(pos3);
                        uint32_t quatBuf[4];
                        void* q = GetPlanetModel()->BuildSurfaceOrientation2(quatBuf, &pos3, &e->b);
                        Mat3 m;
                        Matrix3FromQuaternion(&m, q);
                        t.SetRotation(m);
                        v->mpBegin[i]->SetTransform(&t);
                        v->mpBegin[i]->Start(0);
                    }
                }
            }
        } else {
            bool allDone = true;
            for (int i = 0; i < n; ++i) {
                Elem98_s00bc_6360* l = &e->lists[e->indices[i]];
                Creature_s00bc_6360* c = e->crBegin[i];
                int cur = e->animIdx[i];
                if (cur < (l->mpEnd - l->mpBegin)) {
                    int dur = l->mpBegin[cur].b;
                    allDone = false;
                    bool fin;
                    if (dur > 0) fin = c->f00c0e370() >= dur;
                    else fin = c->AnimationFinished(0);
                    if (fin) {
                        e->animIdx[i] = ++cur;
                        if (cur < (l->mpEnd - l->mpBegin)) {
                            c->InterruptAnimation(l->mpBegin[cur].a, -1, 0);
                            if (c && c->GetTypeId() == 0x18eb4b7) {
                                if (l->mpBegin[0].c != -1) {
                                    int bp;
                                    if (l->mpBegin[cur].d == 0xb) bp = -1;
                                    else bp = c->GetBodyPartIndex(l->mpBegin[cur].d, 0);
                                    c->SetCurrentToolEffect(l->mpBegin[cur].c, bp);
                                }
                            }
                        }
                    }
                }
            }
            if (allDone) {
                int key = e->key;
                for (Node_s00bc_6360* m = head; m != LIST_END_s00bc_6360(this); m = m->next) {
                    if (m->e.key == key) { f00bc4bf0(&m->e); break; }
                }
            }
        }
    }
    // reap disabled entries
    for (Node_s00bc_6360* node = head; node != LIST_END_s00bc_6360(this); node = node->next) {
        if (node->e.disabled) {
            Node_s00bc_6360* nxt = node->next;
            Node_s00bc_6360* s = nxt->prev;
            s->prev->next = s->next;
            s->next->prev = s->prev;
            for (Effect** p = s->e.fx.mpBegin; p < s->e.fx.mpEnd; ++p) if (*p) (*p)->Release();
            freeBuf(s->e.fx.mpBegin);
            freeBuf(s->e.soundIds);
            freeBuf(s->e.animIdx);
            for (Creature_s00bc_6360** p = s->e.crBegin; p < s->e.crEnd; ++p) if (*p) (*p)->Release();
            freeBuf(s->e.crBegin);
            ((Rec*)((char*)s + 0x28))->dtor();
            s->next = freeList;
            freeList = s;
            node = nxt;
        }
    }
}

// @ 0x00bc6e20
SubVec::SubVec(const SubVec& src)
{
    int n = (int)(((char*)src.e - (char*)src.b) / 0x7b4);
    Sub* p = n ? (Sub*)SimNew((uint32_t)n * 0x7b4, "Simulator", 0, 0, (void*)0x13ebb38, 0xd1) : 0;
    b = p;
    e = p;
    c = p + n;
    Sub* outEnd = p;
    MoveRange5(&outEnd, src.b, src.e, p, (SubVec*)&src);
    e = outEnd;
}

// @ 0x00bc6eb0
void HashMap::ClearBuckets(void** bucketArray, uint32_t n)
{
    uint32_t i = 0;
    while (i < n) {
        HashNode2* node = (HashNode2*)bucketArray[i];
        while (node) {
            HashNode2* cur = node;
            node = cur->next;
            Sub* end = cur->end;
            Sub* p = cur->begin;
            while (p < end) {
                SubDtor(p);
                ++p;
            }
            freeBuf(cur->begin);
            operator_delete__(cur);
        }
        bucketArray[i] = 0;
        ++i;
    }
}

// @ 0x00bc6f70
void SimClass::ClearMap()
{
    HashMap* m = &map;
    m->ClearBuckets((void**)m->buckets, m->bucketCount);
    m->size = 0;
}

// @ 0x00bc7080
void SimClass::Destroy()
{
    HashMap* m = &map;
    vtbl0 = (uint32_t)0x1466898;
    vtbl1 = (uint32_t)0x1466890;
    m->ClearBuckets((void**)m->buckets, m->bucketCount);
    m->size = 0;
    if (m->bucketCount > 1)
        operator_delete__(m->buckets);
    ListHead* l = &list;
    DestroyList(l);
    CommitAlloc(&l->alloc);
    BaseDtor();
}

// @ 0x00bc7110
Sub* SubVec::Erase(Sub* first, Sub* last)
{
    Sub* newEnd = ShiftTail(last, e, first);
    Sub* oldEnd = e;
    for (Sub* p = newEnd; p < oldEnd; ++p)
        SubDtor(p);
    e -= last - first;
    return first;
}

// @ 0x00bc7170
void SubVec::Insert(Sub* pos, uint32_t n, const Sub& value)
{
    uint32_t freeN = (uint32_t)(c - e);
    if (n > freeN) {
        uint32_t oldN = (uint32_t)(e - b);
        uint32_t newCap = oldN + oldN;
        if (newCap == 0)
            newCap = 1;
        uint32_t need = oldN + n;
        if (newCap < need)
            newCap = need;
        Sub* nb;
        if (newCap == 0)
            nb = 0;
        else
            nb = (Sub*)SimNew(newCap * 0x7b4, "Simulator", 0, 0, (void*)0x13ebb38, 0xd1);
        Sub* mid = CopyRange2(b, pos, nb);
        DestroyRange2(b, pos, nb);
        FillCopy(mid, n, value);
        Sub* mid2 = mid + n;
        Sub* end2 = CopyRange2(pos, e, mid2);
        DestroyRange2(pos, e, mid2);
        if (b && ((int*)b)[-1] != 0)
            operator_delete__((void*)b);
        b = nb;
        e = end2;
        c = nb + newCap;
        return;
    }
    if (n == 0)
        return;
    Sub tmp(value);
    Sub* oldEnd = e;
    uint32_t tailN = (uint32_t)(oldEnd - pos);
    if (n < tailN) {
        Sub* srcFirst = oldEnd - n;
        Sub* outEnd = oldEnd;
        MoveRange5(&outEnd, srcFirst, oldEnd, oldEnd, this);
        e += n;
        MoveAssignRange(pos, srcFirst, oldEnd);
        Sub* fillEnd = pos + n;
        FillValueRange(pos, fillEnd, &tmp);
    } else {
        FillCopy(oldEnd, n - tailN, tmp);
        e += n - tailN;
        Sub* outEnd = e;
        MoveRange5(&outEnd, pos, oldEnd, e, this);
        e += tailN;
        Sub* fillEnd = pos + n;
        FillValueRange(pos, fillEnd, &tmp);
    }
    SubDtor(&tmp);
}

// @ 0x00bc7380
SimClass::SimClass()
{
    BaseCtor();
    vtbl0 = (uint32_t)0x1466898;
    vtbl1 = (uint32_t)0x1466890;
    uint32_t zero = 0;
    FixedAlloc_s00bc_6360 fa(0x95c, 4, 0x20, zero, 0xffffffff, (void*)0x6abeb0, (void*)0xf47410, "Simulator/list");
    ListHead* l = &list;
    l->alloc = fa.st;
    l->next = (Node2*)l;
    l->prev = (Node2*)l;
    fa.Commit();
    count = zero;
    map.loadF = 1.0f;
    map.growF = 2.0f;
    map.size = zero;
    map.field18 = zero;
    map.bucketCount = 1;
    map.buckets = (void**)0x154df28;
}

// @ 0x00bc7440
SubVec* HashMap::FindOrAdd(uint32_t* key)
{
    MapIter it;
    Find(&it, key);
    if (it.node == buckets[bucketCount]) {
        SubVec tmp;
        tmp.b = tmp.e = tmp.c = 0;
        MapValue value = { *key, tmp };
        // The compiler homes the false flag in the incoming key slot, so the
        // stack argument is the key pointer with its low byte cleared.
        uint32_t flag = (uint32_t)key & 0xffffff00u;
        Insert(&it, &value, flag);
        DestroyVecA((SubVec*)&value);
        DestroyVecB(&tmp);
    }
    return (SubVec*)((char*)it.node + 4);
}

// @ 0x00bc74d0
void WE::FUN_00bc74d0(uint param_2)
{
    Rec7* b = (Rec7*)begin;
    Rec7* e = (Rec7*)end;
    if ((uint)(e - b) < param_2) {
        CivTmp tmp;
        void* uVar1 = tmp.FUN_00bc4630();
        this->FUN_00bc7170(end, param_2 - (uint)(((char*)end - (char*)begin) / 0x7b4), uVar1);
        tmp.FUN_00bc4730();
        return;
    }
    this->FUN_00bc7110((char*)begin + param_2 * 0x7b4, end);
}

// @ 0x00bc7570
void __cdecl FUN_00bc7570(int param_1, WE* self)
{
    IntVec list;
    list.begin = 0;
    list.end = 0;
    list.cap = 0;
    PropMgr_s00bc_74d0* pm = FUN_0067de30_s00bc_74d0();
    pm->GetVector(param_1, &list);
    int count = (int)(list.end - list.begin);
    self->FUN_00bc74d0(count);
    if (0 < count) {
        for (int i = 0; i < count; ++i)
            FUN_00bc5730(list.begin[i], param_1, (int)((char*)self->begin + i * 0x7b4));
    }
    if (list.begin != 0 && *(int*)((char*)list.begin - 4) != 0)
        FUN_00f47380(list.begin);
}

// @ 0x00bc7610
WE* WEMap::FUN_00bc7610(unsigned key, char create)
{
    int iter[2];
    iter[0] = 0;
    iter[1] = 0;
    mHash.find(iter, &key);
    if (create == 0 && (int*)iter[0] != mHash.mBuckets[mHash.mBucketCount])
        return (WE*)(iter[0] + 4);
    WE* w = mHash.FUN_00bc7440(&key);
    w->FUN_00bc7110(w->begin, w->end);
    FUN_00bc7570((int)key, w);
    return w;
}

// @ 0x00bc7680
int WE::FUN_00bc7680(int param_2)
{
    unsigned* puVar2 = (unsigned*)((char*)begin + param_2 * 0x3c);
    unsigned uVar1 = *puVar2;
    if ((uVar1 >> 0x1e & 1) == 0) {
        do {
            uVar1 = puVar2[0xf];
            puVar2 = puVar2 + 0xf;
            param_2 = param_2 + 1;
            if ((int)uVar1 >= 0) {
                return param_2;
            }
        } while ((uVar1 >> 0x1e & 1) == 0);
    }
    return 0x3fffffff;
}

// @ 0x00bc76d0
Rec_s00bc_74d0* Rec_s00bc_74d0::FUN_00bc76d0(Rec_s00bc_74d0* param_2)
{
    flags = param_2->flags;
    f04 = param_2->f04;
    f08 = param_2->f08;
    *(float*)&f0c = *(float*)&param_2->f0c;
    *(float*)&f10 = *(float*)&param_2->f10;
    f14 = param_2->f14;
    f18 = param_2->f18;
    f1c = param_2->f1c;
    void* piVar1 = param_2->p20;
    void* piVar2 = p20;
    if (piVar1 != piVar2) {
        if (piVar1 != 0) ((RefObj*)piVar1)->Add();
        p20 = piVar1;
        if (piVar2 != 0) ((RefObj*)piVar2)->Release();
    }
    piVar1 = param_2->p24;
    piVar2 = p24;
    if (piVar1 != piVar2) {
        if (piVar1 != 0) ((RefObj*)piVar1)->Add();
        p24 = piVar1;
        if (piVar2 != 0) ((RefObj*)piVar2)->Release();
    }
    f28 = param_2->f28;
    f2c = param_2->f2c;
    f30 = param_2->f30;
    f34 = param_2->f34;
    return this;
}

// @ 0x00bc7780
int __cdecl FUN_00bc7780(Rec_s00bc_74d0* param_1, Rec_s00bc_74d0* param_2, int param_3)
{
    if (param_1 != param_2) {
        do {
            if ((param_1->flags >> 0x1f & 1) == 0) {
                void* piVar1 = *(void**)((char*)param_1 + 0x28);
                if (piVar1 != 0) ((RefObj*)piVar1)->Release();
                void* piVar2 = *(void**)((char*)param_1 + 0x24);
                if (piVar2 != 0) ((RefObj*)piVar2)->Release();
            }
            param_1 = (Rec_s00bc_74d0*)((char*)param_1 + 0x3c);
            param_3 = param_3 + 0x3c;
        } while (param_1 != param_2);
    }
    return param_3;
}

// @ 0x00bc77e0
void WE::FUN_00bc77e0(int param_2)
{
    int iVar2;
    unsigned* puVar1 = (unsigned*)((char*)begin + param_2 * 0x3c);
    void* p10 = *(void**)(puVar1 + 10);
    if (p10 != 0) ((RefObj*)p10)->Release();
    void* p9 = *(void**)(puVar1 + 9);
    if (p9 != 0) ((RefObj*)p9)->Release();
    *puVar1 = (activeI & 0x3fffffffU) | (*puVar1 & 0xc0000000) | 0x80000000;
    activeI = param_2;
    if (freeI == param_2) {
        iVar2 = FUN_00bc7680(param_2);
        freeI = iVar2;
    }
}

// @ 0x00bc7850
Rec_s00bc_74d0* Rec_s00bc_74d0::FUN_00bc7850(Rec_s00bc_74d0* param_2)
{
    flags = param_2->flags;
    f04 = param_2->f04;
    f08 = param_2->f08;
    *(float*)&f0c = *(float*)&param_2->f0c;
    *(float*)&f10 = *(float*)&param_2->f10;
    *(float*)&f14 = *(float*)&param_2->f14;
    *(float*)&f18 = *(float*)&param_2->f18;
    *(float*)&f1c = *(float*)&param_2->f1c;
    p20 = param_2->p20;
    if (p20 != 0) ((RefObj*)p20)->Add();
    p24 = param_2->p24;
    if (p24 != 0) ((RefObj*)p24)->Add();
    int* s = &param_2->f28;
    f28 = param_2->f28;
    f2c = s[1];
    f30 = s[2];
    f34 = s[3];
    return this;
}

// @ 0x00bc78d0
void __stdcall FUN_00bc78d0(Rec_s00bc_74d0* param_1, Rec_s00bc_74d0* param_2)
{
    if (param_1 < param_2) {
        do {
            if ((param_1->flags >> 0x1f & 1) == 0) {
                void* piVar1 = *(void**)((char*)param_1 + 0x28);
                if (piVar1 != 0) ((RefObj*)piVar1)->Release();
                void* piVar2 = *(void**)((char*)param_1 + 0x24);
                if (piVar2 != 0) ((RefObj*)piVar2)->Release();
            }
            param_1 = (Rec_s00bc_74d0*)((char*)param_1 + 0x3c);
        } while (param_1 < param_2);
    }
}

// @ 0x00bc7920
Rec_s00bc_74d0* Rec_s00bc_74d0::FUN_00bc7920(Rec_s00bc_74d0* param_2)
{
    if ((int)param_2->flags < 0 && (int)flags >= 0) {
        if (p28 != 0) {
            ((RefObj*)p28)->Release();
        }
        if (p24 != 0) {
            ((RefObj*)p24)->Release();
            flags = param_2->flags;
            return this;
        }
    }
    else if ((int)param_2->flags >= 0) {
        if ((int)flags < 0) {
            if (this != (Rec_s00bc_74d0*)0xfffffffc) {
                ((Rec_s00bc_74d0*)((char*)this + 4))->FUN_00bc7850((Rec_s00bc_74d0*)((char*)param_2 + 4));
                flags = param_2->flags;
                return this;
            }
        }
        else {
            ((Rec_s00bc_74d0*)((char*)this + 4))->FUN_00bc76d0((Rec_s00bc_74d0*)((char*)param_2 + 4));
        }
    }
    flags = param_2->flags;
    return this;
}

// @ 0x00bc79a0
Rec_s00bc_74d0* __cdecl FUN_00bc79a0(Rec_s00bc_74d0* param_1, Rec_s00bc_74d0* param_2, Rec_s00bc_74d0* param_3)
{
    if (param_1 == param_2) {
        return param_3;
    }
    do {
        if (param_3 != 0) {
            param_3->flags = param_1->flags;
            if ((int)param_1->flags >= 0 && param_3 != (Rec_s00bc_74d0*)0xfffffffc) {
                (param_3 + 1)->FUN_00bc7850(param_1 + 1);
            }
        }
        param_1 = (Rec_s00bc_74d0*)((char*)param_1 + 0x3c);
        param_3 = (Rec_s00bc_74d0*)((char*)param_3 + 0x3c);
    } while (param_1 != param_2);
    return param_3;
}

// @ 0x00bc7a70
void** WE::FUN_00bc7a70(void** param_2, Rec_s00bc_74d0* param_3)
{
    FUN_00bc77e0(((char*)param_3 - (char*)begin) / 0x3c);
    unsigned* puVar1;
    do {
        puVar1 = (unsigned*)((char*)param_3 + 0x3c);
        if ((*(unsigned*)param_3 >> 0x1e & 1) != 0) break;
        param_3 = (Rec_s00bc_74d0*)puVar1;
    } while ((int)*puVar1 < 0);
    *param_2 = puVar1;
    return param_2;
}

// @ 0x00bc7ac0
void WERef::FUN_00bc7ac0(unsigned delta)
{
    if (delta != 0) {
        float step = (float)delta * 0.001f;
        WE* w = mEvents;
        Rec_s00bc_74d0* at;
        if ((unsigned)w->freeI < 0x3fffffff)
            at = (Rec_s00bc_74d0*)((char*)w->begin + w->freeI * 0x3c);
        else
            at = w->end;
        Rec_s00bc_74d0* end = w->end;
        while (at != end) {
            if (0.0f <= *(float*)((char*)at + 0x10)) {
                *(float*)((char*)at + 0x10) -= step;
                unsigned flags;
                do {
                    flags = *(unsigned*)at;
                    at = (Rec_s00bc_74d0*)((char*)at + 0x3c);
                    if ((flags >> 0x1e) & 1)
                        break;
                } while ((int)*(unsigned*)at < 0);
            }
            else {
                ((cHierGrid*)((char*)w + 0x1c))->Remove(*(unsigned*)((char*)at + 8));
                Rec_s00bc_74d0* next;
                w->FUN_00bc7a70((void**)&next, at);
                at = next;
            }
        }
    }
}

// @ 0x00bc7b70
void WE::FUN_00bc7b70(uint param_2)
{
    int iVar1, iVar2, iVar3;
    if ((uint)(((char*)cap - (char*)begin) / 0x3c) < param_2) {
        if (param_2 == 0) {
            iVar3 = 0;
        } else {
            iVar3 = (int)op_new(param_2 * 0x3c, "Simulator", 0, 0,
                                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        }
        iVar1 = (int)begin;
        iVar2 = (int)end;
        FUN_00bc79a0((Rec_s00bc_74d0*)iVar1, (Rec_s00bc_74d0*)iVar2, (Rec_s00bc_74d0*)iVar3);
        FUN_00bc7780((Rec_s00bc_74d0*)iVar1, (Rec_s00bc_74d0*)iVar2, iVar3);
        if (begin != 0) {
            op_delete_(begin);
        }
        iVar1 = (int)begin;
        begin = (Rec_s00bc_74d0*)iVar3;
        end = (Rec_s00bc_74d0*)(iVar3 + ((int)end - iVar1) / 0x3c * 0x3c);
        cap = (Rec_s00bc_74d0*)(iVar3 + param_2 * 0x3c);
    }
}

// @ 0x00bc7c40
int WE::FUN_00bc7c40(int param_2, int param_3)
{
    int* uVar1 = FUN_00bc79f0((void*)param_3, (void*)end, (void*)param_2);
    FUN_00bc78d0((Rec_s00bc_74d0*)uVar1, end);
    int x = param_3 - param_2;
    end = (Rec_s00bc_74d0*)((char*)end - (x / 0x3c) * 0x3c);
    return param_2;
}

// @ 0x00bc7ca0
void WE::FUN_00bc7ca0(Rec_s00bc_74d0* param_2, int* param_3)
{
    Rec_s00bc_74d0* piVar2 = end;
    if (piVar2 != cap) {
        if (param_2 <= (Rec_s00bc_74d0*)param_3 && (Rec_s00bc_74d0*)param_3 < piVar2) {
            param_3 = (int*)((char*)param_3 + 0x3c);
        }
        if (piVar2 != 0) {
            piVar2->flags = ((Rec_s00bc_74d0*)((char*)piVar2 - 0x3c))->flags;
            if ((int)((Rec_s00bc_74d0*)((char*)piVar2 - 0x3c))->flags >= 0 && piVar2 != (Rec_s00bc_74d0*)0xfffffffc) {
                (piVar2 - 0xe)->FUN_00bc7850((Rec_s00bc_74d0*)((char*)piVar2 - 0x38));
            }
        }
        FUN_00bc7a30((void*)param_2, (void*)((char*)end - 0x3c), end);
        ((Rec_s00bc_74d0*)param_3)->FUN_00bc7920((Rec_s00bc_74d0*)param_3);
        end = (Rec_s00bc_74d0*)((char*)end + 0x3c);
        return;
    }
    int local_4 = ((char*)piVar2 - (char*)begin) / 0x3c;
    int local_8;
    if (local_4 == 0) {
        local_4 = 1;
    } else {
        local_4 = local_4 * 2;
        if (local_4 == 0) {
            local_8 = 0;
            goto LBL;
        }
    }
    local_8 = (int)op_new(local_4 * 0x3c, "Simulator", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
LBL:
    Rec_s00bc_74d0* iVar1 = begin;
    Rec_s00bc_74d0* piVar4 = FUN_00bc79a0(iVar1, param_2, (Rec_s00bc_74d0*)local_8);
    FUN_00bc7780(iVar1, param_2, local_8);
    if (piVar4 != 0) {
        piVar4->flags = *(unsigned*)param_3;
        if ((int)*(unsigned*)param_3 >= 0 && piVar4 != (Rec_s00bc_74d0*)0xfffffffc) {
            (piVar4 + 1)->FUN_00bc7850((Rec_s00bc_74d0*)(param_3 + 1));
        }
    }
    Rec_s00bc_74d0* iVar2 = end;
    Rec_s00bc_74d0* iVar3 = FUN_00bc79a0(param_2, iVar2, piVar4 + 1);
    FUN_00bc7780(param_2, iVar2, (int)(piVar4 + 1));
    if (begin != 0) {
        op_delete_(begin);
    }
    end = iVar3;
    begin = (Rec_s00bc_74d0*)local_8;
    cap = (Rec_s00bc_74d0*)(local_8 + local_4 * 0x3c);
}

// @ 0x00bc7e20
void WE::FUN_00bc7e20()
{
    Rec_s00bc_74d0* puVar1 = end;
    if (puVar1 < cap) {
        end = (Rec_s00bc_74d0*)((char*)puVar1 + 0x3c);
        if (puVar1 != 0) {
            puVar1->flags = 0x80000000;
            return;
        }
    }
    else {
        Rec_s00bc_74d0 tmp;
        tmp.flags = 0x80000000;
        FUN_00bc7ca0(puVar1, (int*)&tmp);
        if ((int)tmp.flags >= 0) {
            void* p28 = *(void**)((char*)&tmp + 0x28);
            if (p28 != 0) ((RefObj*)p28)->Release();
            void* p24 = *(void**)((char*)&tmp + 0x24);
            if (p24 != 0) ((RefObj*)p24)->Release();
        }
    }
}

// @ 0x00bc7e80
uint WE::FUN_00bc7e80(int param_2)
{
    uint uVar3 = activeI;
    if (uVar3 == 0x3fffffff) {
        Rec_s00bc_74d0 tmp;                                    // body temp (record + 4)
        tmp.FUN_00bc7850((Rec_s00bc_74d0*)param_2);
        uVar3 = (uint)(((char*)end - (char*)begin) / 0x3c);
        FUN_00bc7e20();
        if (uVar3 != 0) {
            unsigned* prev = (unsigned*)((char*)begin + (uVar3 - 1) * 0x3c);
            *prev = *prev & 0xbfffffff;
        }
        int iVar1 = uVar3 * 0x3c;
        unsigned* rec = (unsigned*)((char*)begin + iVar1);
        *rec = *rec | 0x40000000;
        *rec = *rec & 0x7fffffff;
        ((Rec_s00bc_74d0*)((char*)begin + iVar1 + 4))->FUN_00bc7850(&tmp);
        if (tmp.p24 != 0) ((RefObj*)tmp.p24)->Release();
        if (tmp.p28 != 0) ((RefObj*)tmp.p28)->Release();
    }
    else {
        int iVar1 = uVar3 * 0x3c;
        unsigned* rec = (unsigned*)((char*)begin + iVar1);
        activeI = *rec & 0x3fffffff;
        *rec = *rec & 0x7fffffff;
        ((Rec_s00bc_74d0*)((char*)begin + iVar1 + 4))->FUN_00bc7850((Rec_s00bc_74d0*)param_2);
    }
    if (uVar3 < (uint)freeI) {
        freeI = uVar3;
    }
    return uVar3;
}

// @ 0x00bc7f80
WE** __fastcall FUN_00bc7f80(WE** param_1)
{
    WE* puVar1 = (WE*)op_new(0xa0, "Simulator/cWorldEventsData", 0, 0, 0, 0);
    if (puVar1 != 0) {
        puVar1->begin = 0;
        puVar1->end = 0;
        puVar1->cap = 0;
        puVar1->freeI = 0x3fffffff;
        puVar1->activeI = 0x3fffffff;
        puVar1->FUN_00bc7b70(0x32);
        cHierGrid_ctor((char*)puVar1 + 0x1c);
        *param_1 = puVar1;
        return param_1;
    }
    WE* p = puVar1;
    *param_1 = p;
    return param_1;
}

// @ 0x00bc8040
void __fastcall FUN_00bc8040(WE** param_1)
{
    WE* puVar1 = *param_1;
    puVar1->FUN_00bc7c40((int)puVar1->begin, (int)puVar1->end);
    puVar1->freeI = 0x3fffffff;
    puVar1->activeI = 0x3fffffff;
    WE* iVar2 = *param_1;
    if (*(int*)((char*)iVar2 + 0x40) != *(int*)((char*)iVar2 + 0x44)) {
        cHierGrid_Shutdown((char*)iVar2 + 0x1c);
        return;
    }
}

// @ 0x00bc8080
void __thiscall WEHolder::FUN_00bc8080(const float* pos, float radius, IntVector* out, int filter)
{
    int zero = 0;
    int buf[0x100];
    IntVector tmp;
    tmp.begin = buf;
    tmp.end = buf;
    tmp.cap = buf + 0x100;
    tmp.insert(buf, 0x100, &zero);

    int n = ((cHierGrid*)((char*)mEvents + 0x1c))->QuerySphereResult(radius, (float*)pos, 0x100, (void**)tmp.begin);
    tmp.resize(n);

    char* blank_end = (char*)out->end;
    memcpy(out->begin, out->end, 0);
    int q = (int)(blank_end - (char*)out->begin) >> 2;
    out->end = (int*)(blank_end - q * 4);
    out->reserve(n);

    for (int i = 0; i < n; ++i) {
        GridItem* item = (GridItem*)buf[i];
        if ((filter == -1 || filter == item->mType)) {
            float dz = pos[2] - item->mZ;
            float dx = pos[0] - item->mX;
            float dy = pos[1] - item->mY;
            float rr = item->mRadius + radius;
            float d2 = dz * dz;
            d2 = d2 + dx * dx;
            d2 = d2 + dy * dy;
            if (rr * rr > d2) {
                if (out->end < out->cap) {
                    *out->end = (int)item;
                    out->end = out->end + 1;
                } else {
                    out->DoInsertKey4(out->end, (const int*)&item);
                }
            }
        }
    }
}

// @ 0x00bc8200
void __fastcall FUN_00bc8200(WE** param_1)
{
    WE* w = *param_1;
    w->FUN_00bc7c40((int)w->begin, (int)w->end);
    w->freeI = 0x3fffffff;
    w->activeI = 0x3fffffff;
    WE* w2 = *param_1;
    if (*(int*)((char*)w2 + 0x40) != *(int*)((char*)w2 + 0x44)) {
        cHierGrid_Shutdown((char*)w2 + 0x1c);
    }

    Vec3f mn;
    Vec3f mx;
    Vec3f size;
    mn.x = DAT_0168ab70 - 650.0f;
    mn.y = DAT_0168ab74 - 650.0f;
    mn.z = DAT_0168ab78 - 650.0f;
    mx.x = DAT_0168ab70 + 650.0f;
    mx.y = DAT_0168ab74 + 650.0f;
    mx.z = DAT_0168ab78 + 650.0f;
    size.x = mx.x - mn.x;
    size.y = mx.y - mn.y;
    size.z = mx.z - mn.z;

    float* pmax = &size.y;
    if (size.y <= size.x) {
        pmax = &size.x;
    }
    if (size.z != *pmax && *pmax <= size.z) {
        pmax = &size.z;
    }
    float broad = *pmax * 2.0f;
    float narrow = broad * 9.999999f;
    broad = broad * 0.01f;

    int n0 = (int)broad;
    if ((float)n0 < broad) n0 = n0 + 1;
    int bits0 = 0;
    for (; n0 != 0; n0 = n0 >> 1) bits0 = bits0 + 1;

    int n1 = (int)narrow;
    if ((float)n1 < narrow) n1 = n1 + 1;
    int bits1 = 0;
    for (; n1 != 0; n1 = n1 >> 1) bits1 = bits1 + 1;

    int level = 0;
    if (0 < bits0 - 1) level = bits0 - 1;
    int maxLevel = 7;
    if (bits1 - 1 < 7) maxLevel = bits1 - 1;
    if (maxLevel < level) maxLevel = level;

    ((cHierGrid*)((char*)*param_1 + 0x1c))->Init(mn, *pmax, level, maxLevel);
}

// @ 0x00bc8400
unsigned __thiscall cHierGrid_s00bc_8400::NewEntry(unsigned a2, unsigned* src, unsigned a4, float radius, IRefCount* p1, IRefCount* p2)
{
    void* tmp1 = 0;
    void* tmp2 = 0;
    unsigned token = mQueue->Acquire(&tmp1);

    if (tmp2 != 0)
        (*(void (***)(void))tmp2)[1]();
    if (tmp1 != 0)
        (*(void (***)(void))tmp1)[1]();

    cGridQueue* q = mQueue;
    unsigned have = (unsigned)((q->mEnd - q->mBeg) / 0x3c);
    if ((token & 0xbfffffff) < have) {
        char* slot = q->mBeg + (token * 0x10 - (token & 0xbfffffff)) * 4;
        if ((int)*(unsigned*)slot >= 0) {
            char* rec = slot + 4;
            if (rec != 0) {
                *(unsigned*)rec = token | 0x40000000;
                *(unsigned*)(rec + 4) =
                    ((cGrid*)q->mTable)->CreateEntry(a4, src, radius);
                *(unsigned*)(rec + 8) = a2;
                *(unsigned*)(rec + 0x14) = *(unsigned*)((char*)src + 4);
                *(unsigned*)(rec + 0x18) = *(unsigned*)((char*)src + 8);
                *(float*)(rec + 0x10) = *(float*)src;
                *(unsigned*)(rec + 0x1c) = *(unsigned*)((char*)src + 0xc);
                *(unsigned*)(rec + 0xc) = *(unsigned*)((char*)src + 0x10);
                IRefCount* old = *(IRefCount**)(rec + 0x20);
                if (p1 != old) {
                    if (p1 != 0)
                        p1->AddRef();
                    *(IRefCount**)(rec + 0x20) = p1;
                    if (old != 0)
                        old->Release();
                }
                IRefCount* old2 = *(IRefCount**)(rec + 0x24);
                if (p2 != old2) {
                    if (p2 != 0)
                        p2->AddRef();
                    *(IRefCount**)(rec + 0x24) = p2;
                    if (old2 != 0)
                        old2->Release();
                }
                *(unsigned*)(rec + 0x28) = 0;
                *(unsigned*)(rec + 0x2c) = 0;
                *(unsigned*)(rec + 0x30) = 0;
                *(unsigned*)(rec + 0x34) = 0;
            }
        }
    }
    return token | 0x40000000;
}

// @ 0x00bc8550
void* __fastcall Grid_AllocThunk(void* self)
{
    return Grid_NewArray(self, 0xff, 0x418);
}

// @ 0x00bc8570
void __cdecl Grid_Notify(char flag, char* obj, char* rec, unsigned p4, double d5)
{
    if (flag == 0)
        return;
    void (*fn)(unsigned, double, unsigned, unsigned, char*) =
        *(void (**)(unsigned, double, unsigned, unsigned, char*))(obj + 0xc);
    if (fn == 0)
        return;
    fn(p4, d5, *(unsigned*)(rec + 0x41), *(unsigned*)(rec + 0x4d), obj);
}

// @ 0x00bc85b0
void __cdecl Grid_WalkInsert(void* a1, double a2, void* a3, char* host, char* obj)
{
    bool done = false;
    do {
        switch (*(unsigned*)(host + 4)) {
        case 1: {
            char* owner = *(char**)(host + 0x70);
            if (owner != 0) {
                void (*fn)(void*, double, void*, unsigned, char*) =
                    *(void (**)(void*, double, void*, unsigned, char*))(owner + 0xc);
                if (fn != 0) {
                    unsigned idx = *(unsigned*)(obj + 4);
                    if (idx == 0xffffffff)
                        idx = *(unsigned*)(host + 0x74);
                    fn(a1, a2, a3, idx, obj + 0x2c);
                }
            }
            if (*(unsigned*)(obj + 8) < *(unsigned*)(host + 0x7c))
                host = *(char**)(host + 0x80) + *(unsigned*)(obj + 8) * 0x88;
            break;
        }
        case 2:
            done = true;
            break;
        case 0: {
            char* owner = *(char**)(host + 0x70);
            if (owner != 0) {
                void (*fn)(void*, double, void*, unsigned, char*) =
                    *(void (**)(void*, double, void*, unsigned, char*))(owner + 0xc);
                if (fn != 0) {
                    unsigned idx = *(unsigned*)(obj + 4);
                    if (idx == 0xffffffff)
                        idx = *(unsigned*)(host + 0x74);
                    fn(a1, a2, a3, idx, obj + 0x2c);
                }
            }
            break;
        }
        default:
            break;
        }
        Grid_NewArray(obj, 0xff, 0x2c);
        obj += 0xac;
    } while (!done);
}

// @ 0x00bc8690
void __fastcall Grid_Shuffle(unsigned n, unsigned char* buf)
{
    unsigned i = 0;
    while (i < n) {
        buf[i] = (unsigned char)i;
        ++i;
    }
    for (i = 0; i + 1 < n; ++i) {
        unsigned j = GenerateUInt32(n - i);
        unsigned char t = buf[i];
        buf[i] = buf[j + i];
        buf[j + i] = t;
    }
}

// @ 0x00bc86e0
void __cdecl Grid_ResetEntry(double when, char* p1, char* p2, char* p3, unsigned* out, char* p4)
{
    if (*(int*)p3 != -1) {
        Grid_WalkInsert(p2, when, p4, p1, p3 + 0x10);
        Grid_NewArray(p3, 0xff, 0x418);
    }
    unsigned n = *(unsigned*)(p1 + 0x24);
    if (n == 0xffffffff) return;
    if (out == 0) return;
    if (n <= 0) return;
    double zero = 0.0;
    do {
        *(double*)(out + 2) = zero;
        *out = 0xffffffff;
        out += 4;
        --n;
    } while (n != 0);
}

// @ 0x00bc8750
bool __thiscall GridMask::FitsMask(unsigned m1, unsigned m2)
{
    char* b = (char*)this;
    unsigned a = *(unsigned*)(b + 8) & m1;
    unsigned d = *(unsigned*)(b + 0xc) & m2;
    if (a != *(unsigned*)(b + 0) || d != *(unsigned*)(b + 4))
        return false;
    if (*(b + 0x10) != 0) {
        if (((*(unsigned*)(b + 0x18) & m1) | (*(unsigned*)(b + 0x1c) & m2)) == 0)
            return false;
    }
    if (*(b + 0x20) != 0) {
        unsigned c = *(unsigned*)(b + 0x28);
        unsigned e = *(unsigned*)(b + 0x2c);
        if ((c & m1) == c && (e & m2) == e)
            return false;
    }
    return true;
}

// @ 0x00bc87b0
void __cdecl Grid_FlushPending(char flag, unsigned a2, char* obj, unsigned a4, double a5)
{
    char* h = *(char**)(obj + 0x55);
    if (h != 0) {
        void (*fn)(void*, double, unsigned, unsigned, char*) =
            *(void (**)(void*, double, unsigned, unsigned, char*))(h + 0xc);
        if (fn != 0)
            fn((void*)a4, a5, *(unsigned*)(obj + 0x41), *(unsigned*)(obj + 0x51), h);
    }
    *(unsigned*)(obj + 0x55) = 0;
    if (flag) {
        unsigned tmp = *(unsigned*)(obj + 0x4d);
        *(unsigned*)(obj + 0x4d) = *(unsigned*)(obj + 0x51);
        *(unsigned*)(obj + 0x51) = tmp;
        *(unsigned*)(obj + 0x55) = a2;
        return;
    }
    *(unsigned*)(obj + 0x55) = 0;
}

// @ 0x00bc8810
int __cdecl Grid_VisitNode(void* arg, int* counter, unsigned* limit)
{
    char* node = (char*)arg;
    if (*(float*)(node + 0x1c) != 0.0f && *(int*)(node + 0x24) == -1) {
        *(int*)(node + 0x20) = *counter;
        ++*counter;
    }
    int best = 1;
    if (*(int*)(node + 4) - 1 == 0 && *(unsigned*)(node + 0x80) != 0) {
        int idx = 0;
        unsigned i = 0;
        unsigned n = *(unsigned*)(node + 0x7c);
        if (n != 0) {
            unsigned off = 0;
            do {
                int r = Grid_VisitNode(*(char**)(node + 0x80) + off, counter, limit);
                if (idx < r)
                    idx = r;
                off += 0x88;
                i += 1;
            } while (i < n);
        }
        best = idx + 1;
        if (*(int*)(node + 0x78) == 3 || *(int*)(node + 0x78) == 4) {
            unsigned v = *(unsigned*)(node + 0x7c);
            if (v < *limit)
                v = *limit;
            *limit = v;
        }
    }
    if (*(int*)(node + 0x24) == -1)
        *(int*)(node + 0x24) = *counter;
    return best;
}

// @ 0x00bc88e0
bool __cdecl Grid_TryNode(char* self, unsigned a2, double a3, cHierGrid_s00bc_8400* ctx)
{
    (void)a2;
    if (*(char*)(self + 0x18) != 0)
        return true;
    if (*(int*)(self + 0x20) != -1) {
        unsigned* base = *(unsigned**)((char*)ctx + 0x3d);
        if (base == 0)
            return false;
        unsigned idx = *(unsigned*)(self + 0x20);
        base[idx * 4] = *(unsigned*)self;
        double* slot = (double*)(base + idx * 4 + 2);
        if (*slot <= a3)
            *slot = a3 + (double)*(float*)(self + 0x1c);
        else
            return false;
    }
    unsigned m = *(unsigned*)((char*)ctx + 0x41);
    if ((*(unsigned*)(self + 0x2c) & m) != *(unsigned*)(self + 0x28))
        return false;
    if (*(char*)(self + 0x30) != 0 && (*(unsigned*)(self + 0x34) & m) == 0)
        return false;
    if (*(char*)(self + 0x38) != 0 &&
        (*(unsigned*)(self + 0x3c) & m) == *(unsigned*)(self + 0x3c))
        return false;
    unsigned* p = *(unsigned**)((char*)ctx + 0x45);
    GridMask* f = (GridMask*)(self + 0x40);
    return f->FitsMask(p[0], p[1]) != 0;
}

// @ 0x00bc8970
double __cdecl Grid_DispatchNode(char* node, unsigned a2, unsigned a3, cHierGrid_s00bc_8400* ctx, double a5)
{
    float r = 0.0f;
    if (Grid_TryNode(node, a2, a5, ctx)) {
        void* fnp = *(void**)(node + 8);
        if (fnp != 0) {
            *(unsigned*)((char*)ctx + 4) = a3;
            *(char**)ctx = node;
            *(char*)((char*)ctx + 8) = 0;
            float (*fn)(unsigned, double, unsigned, unsigned, char*, void*) =
                *(float (**)(unsigned, double, unsigned, unsigned, char*, void*))(node + 8);
            return (double)fn(a2, a5, *(unsigned*)((char*)ctx + 0x41),
                              *(unsigned*)((char*)ctx + 0x4d), node, ctx);
        }
        r = 1.0f;
    }
    return (double)r;
}

// @ 0x00bc8a00
unsigned __cdecl Grid_AdvanceLevel(char* host, char* node, unsigned a3, double a4)
{
    if (host == 0 || node == 0)
        return 0;
    unsigned slotLimit = *(unsigned*)(node + 0xd);
    unsigned count = *(unsigned*)(host + 0x7c);
    float last = *(float*)(node + 0x29);
    unsigned cursor = *(unsigned*)(node + 0x15);
    int mode = *(int*)(host + 4);
    unsigned chosen = 0xffffffff;
    if (mode == 0 || mode == 2)
        return 0;
    if (*(unsigned*)(host + 0x80) == 0 || count == 0)
        return 0;
    switch (*(int*)(host + 0x78)) {
    case 0: {
        unsigned pick = 0xffffffff;
        unsigned lim = count;
        if (slotLimit < count)
            lim = slotLimit;
        unsigned start = 0;
        if (last != 0.0f)
            start = (unsigned)(((int)last - *(int*)(host + 0x80)) / 0x88 + 1);
        unsigned off = start * 0x88;
        while (start < lim) {
            char* chunk = *(char**)(host + 0x80) + off;
            unsigned out = 0;
            double r = Grid_DispatchNode(chunk, 1, start, (cHierGrid_s00bc_8400*)node, a4);
            unsigned prevStart = start;
            if (r <= 0.0) {
                Grid_Notify((char)out, chunk, node, a3, a4);
            } else if (r >= 1.0) {
                Grid_FlushPending((char)out, prevStart, node, a3, a4);
                chosen = prevStart;
                if (prevStart != 0xffffffff)
                    goto done;
                break;
            } else {
                if (pick != 0xffffffff) {
                    Grid_Notify((char)out, chunk, node, a3, a4);
                } else {
                    pick = start;
                    Grid_FlushPending((char)out, prevStart, node, a3, a4);
                }
            }
            off += 0x88;
            ++start;
        }
        if (slotLimit == 0xffffffff || pick == 0xffffffff)
            goto done;
        chosen = pick;
        break;
    }
    case 1:
    case 2: {
        chosen = slotLimit;
        if (slotLimit < count)
            goto done;
        unsigned i = *(unsigned*)(node + 9);
        do {
            ++i;
            if (i >= count) {
                if (*(int*)(host + 0x78) != 2)
                    goto usePrev;
                i = 0;
            }
            char* chunk = *(char**)(host + 0x80) + i * 0x88;
            unsigned out = 0;
            double r = Grid_DispatchNode(chunk, 1, i, (cHierGrid_s00bc_8400*)node, a4);
            if (r > 0.0) {
                Grid_FlushPending((char)out, i, node, a3, a4);
                goto done;
            }
            Grid_Notify((char)out, chunk, node, a3, a4);
            ++cursor;
        } while (cursor < count);
        chosen = 0xffffffff;
        break;
    }
    case 3:
    case 4: {
        chosen = slotLimit;
        if (slotLimit < count)
            goto done;
        unsigned lim = count;
        if (count > 0xf)
            lim = *(unsigned*)0x1466960;
        unsigned keep = lim;
        if (*(int*)(node + 9) == -1)
            Grid_Shuffle(count, (unsigned char*)(node + 0x19));
        do {
            ++cursor;
            if (cursor >= lim) {
                if (*(int*)(host + 0x78) != 4)
                    goto done;
                Grid_Shuffle(count, (unsigned char*)(node + 0x19));
                cursor = 0;
            }
            unsigned idx = *(unsigned char*)(node + 0x19 + cursor);
            char* chunk = *(char**)(host + 0x80) + idx * 0x88;
            unsigned out = 0;
            double r = Grid_DispatchNode(chunk, 1, idx, (cHierGrid_s00bc_8400*)node, a4);
            if (r > 0.0) {
                Grid_FlushPending((char)out, idx, node, a3, a4);
                goto done;
            }
            Grid_Notify((char)out, chunk, node, a3, a4);
            ++keep;
        } while (keep < count);
        chosen = 0xffffffff;
        break;
    }
    case 5:
    case 6: {
        chosen = slotLimit;
        if (slotLimit < count)
            goto done;
        if (count <= *(unsigned*)(node + 9) && *(int*)(host + 0x78) == 5)
            break;
        do {
            unsigned idx = GenerateUInt32(count);
            char* chunk = *(char**)(host + 0x80) + idx * 0x88;
            if ((float)(unsigned)chunk != last) {
                unsigned out = 0;
                double r = Grid_DispatchNode(chunk, 1, idx, (cHierGrid_s00bc_8400*)node, a4);
                if (r > 0.0) {
                    Grid_FlushPending((char)out, idx, node, a3, a4);
                    goto done;
                }
                Grid_Notify((char)out, chunk, node, a3, a4);
            }
            ++cursor;
        } while (cursor < count);
        chosen = 0xffffffff;
        break;
    }
    case 7:
    case 8: {
        float best = 0.0f;
        if ((slotLimit == 0xffffffff || *(int*)(host + 0x78) == 8) && count != 0) {
            unsigned i = 0;
            unsigned off = 0;
            do {
                char* chunk = *(char**)(host + 0x80) + off;
                unsigned out = 0;
                double r = Grid_DispatchNode(chunk, 1, i, (cHierGrid_s00bc_8400*)node, a4);
                if (r <= best) {
                    Grid_Notify((char)out, chunk, node, a3, a4);
                } else {
                    best = (float)r;
                    Grid_FlushPending((char)out, i, node, a3, a4);
                    chosen = i;
                }
                off += 0x88;
                ++i;
            } while (i < count);
        }
        break;
    }
    default:
        break;
    }
    goto store;
usePrev:
    chosen = count;
store:
    *(unsigned*)(node + 0x11) = chosen;
    *(unsigned*)(node + 0x15) = cursor;
    return (unsigned)(chosen < count);
done:
    *(unsigned*)(node + 0x11) = chosen;
    *(unsigned*)(node + 0x15) = cursor;
    return (unsigned)(chosen < count);
}

// @ 0x00bc8fa0
bool __cdecl Grid_HasValidIndex(cGridQueue* q)
{
    int count = 0;
    unsigned limit = 0;
    unsigned n = (unsigned)Grid_VisitNode(q, &count, &limit);
    return n <= 6 && limit <= 0x10;
}

// @ 0x00bc8ff0
bool __cdecl WalkTree(float f1, double t, Node_s00bc_8ff0* node, int p4, Cursor* cur, int p6, int p7, int p8)
{
	if (node->order == -1)
	{
		int counter = 0;
		uint32_t maxChildren = 0;
		AssignOrder(node, &counter, &maxChildren);
	}
	// function-local static RandomMersenneTwister (-1), spelled out with its storage and guard word
	if (!(g_0168B548 & 1))
	{
		g_0168B548 |= 1;
		new (&g_0168AB80) RandomMersenneTwister(0xFFFFFFFF);
	}

	Node_s00bc_8ff0* path[7] = { 0, 0, 0, 0, 0, 0, 0 };
	__declspec(align(64)) uint32_t bufA[32];
	uint32_t bufB[32];
	Ctx ctx;
	FlagWord evalFlag;

	ctx.t = t;
	ctx.p7 = p7;
	ctx.p6 = p6;
	ctx.active = 0;
	ctx.bufA = bufA;
	ctx.p8 = p8;
	ctx.bufB = bufB;
	ctx.p4 = p4;
	ctx.rng = &g_0168AB80;

	Frame* fr = &cur->frames[0];
	bool first = (fr->id != node->id);
	uint32_t* rec1 = fr->rec1;
	uint32_t* rec2 = fr->rec2;
	Frame* nextFr = fr + 1;
	bool wasFirst;
	bool popped = false;
	uint32_t last = 0;
	uint32_t justDone;
	int depth = 0;

	for (;;)
	{
		path[depth + 1] = node;
		justDone = 0;

		switch (node->type)
		{
		case 0:
		{
			wasFirst = first;
			if (first)
			{
				fr->id = node->id;
				fr->t = t;
				first = false;
			}
			int idx = fr->idx;
			if (idx == -1)
				idx = node->defaultIdx;
			Callbacks* cb = node->cb;
			bool (__cdecl *fnA)(int, double, int, int, void*, void*) =
				cb ? cb->fnA : 0;
			bool (__cdecl *fnB)(int, double, int, int, void*, void*, float) =
				cb ? cb->fnB : 0;
			bool ok = true;
			if (cb)
			{
				void* mask = ctx.active ? ctx.bufB : 0;
				if (wasFirst && fnA && !fnA(p4, t, p7, idx, rec2, mask))
					ok = false;
				else if (fnB && !fnB(p4, t, p7, idx, rec2, mask, f1))
					ok = false;
			}
			if (ok)
			{
				if (ctx.active && ctx.active->fnC)
					ctx.active->fnC(p4, t, ctx.p7, ctx.bufB, ctx.active);
				ctx.active = 0;
				cur->id = node->id;
				cur->node = node;
				if (node->cb)
				{
					cur->childIdx = node->cb->userData;
					cur->depth = depth + 1;
					return true;
				}
				cur->childIdx = -1;
				cur->depth = depth + 1;
				return true;
			}
			break;
		}
		case 1:
		{
			if (!node->children)
				return true;
			if (!node->count)
				return true;
			wasFirst = first;
			if (first)
			{
				fr->childIdx = -1;
				fr->id = node->id;
				fr->t = t;
				first = false;
			}
			uint32_t savedChild = fr->childIdx;
			bool pass = true;
			if (popped)
			{
				fr->counter = fr->counter + 1;
				if (savedChild < node->count)
					ResetFrames(p4, t, p7, &node->children[savedChild], nextFr);
				fr->childIdx = -1;
				if (fr->counter > node->count)
				{
					if (ctx.active && ctx.active->fnC)
						ctx.active->fnC(p4, t, ctx.p7, ctx.bufB, ctx.active);
					return false;
				}
				popped = false;
				if (node->flags & 1)
				{
					ctx.c9 = 0xFFFFFFFF;
					ctx.cD = 0xFFFFFFFF;
					ctx.c11 = 0xFFFFFFFF;
					ctx.prev = 0;
					ctx.depth = depth;
					evalFlag.flag = 0;
					float r = EvalNode(node, 0, -1, p4, t, &ctx, &evalFlag);
					if (r > 0.0f)
					{
						ApplyEval(evalFlag.word, node, &ctx, p4, t);
					}
					else
					{
						if (evalFlag.flag && node->failFn)
							node->failFn(p4, t, ctx.p7, ctx.bufA, node);
						pass = false;
					}
				}
			}
			else
			{
				fr->counter = 0;
			}

			if (pass)
			{
				Callbacks* cb = node->cb;
				if (cb)
				{
					int idx = fr->idx;
					if (idx == -1)
						idx = node->defaultIdx;
					void* mask = ctx.active ? ctx.bufB : 0;
					if (wasFirst && cb->fnA && !cb->fnA(p4, t, p7, idx, rec2, mask))
						pass = false;
					else if (cb->fnB && !cb->fnB(p4, t, p7, idx, rec2, mask, f1))
						pass = false;
				}
			}

			if (pass)
			{
				if (ctx.active && ctx.active->fnC)
					ctx.active->fnC(p4, t, ctx.p7, ctx.bufB, ctx.active);
				uint32_t curChild = fr->childIdx;
				ctx.active = 0;
				uint32_t count = node->count;
				ctx.c9 = savedChild;
				ctx.cD = curChild;
				ctx.c11 = 0xFFFFFFFF;
				if (rec1)
				{
					ctx.rec[0] = rec1[0];
					ctx.rec[1] = rec1[1];
					ctx.rec[2] = rec1[2];
					ctx.rec[3] = rec1[3];
					ctx.rec[4] = rec1[4];
				}
				ctx.prev = last;
				ctx.depth = depth;
				SelectChild(node, &ctx, p4, t);
				last = ctx.c11;
				if (last < count && last != curChild)
				{
					if (curChild < count)
						ResetFrames(p4, t, p7, &node->children[curChild], nextFr);
					rec1[0] = ctx.rec[0];
					rec1[1] = ctx.rec[1];
					rec1[2] = ctx.rec[2];
					rec1[3] = ctx.rec[3];
					rec1[4] = ctx.rec[4];
					fr->childIdx = last;
					node = &node->children[last];
					first = true;
					pass = true;
				}
				else if (count <= curChild)
				{
					pass = false;
				}
				else
				{
					node = &node->children[curChild];
				}
				if (pass)
				{
					nextFr = nextFr + 1;
					rec2 = rec2 + sizeof(Frame) / 4;
					rec1 = rec1 + sizeof(Frame) / 4;
					fr = fr + 1;
					depth++;
					last = justDone;
					if (!node)
						return true;
					continue;
				}
			}
			break;
		}
		default:
			return true;
		}

		// failure: leave this node and go back to its parent
		justDone = (uint32_t)node;
		if (ctx.active && ctx.active->fnC)
			ctx.active->fnC(p4, t, ctx.p7, ctx.bufB, ctx.active);
		nextFr = nextFr - 1;
		rec2 = rec2 - sizeof(Frame) / 4;
		rec1 = rec1 - sizeof(Frame) / 4;
		fr = fr - 1;
		node = path[depth];
		depth--;
		ctx.active = 0;
		popped = true;
		last = justDone;
		if (!node)
			return true;
	}
}

// @ 0x00bc9980
uint32_t* Stimuli::UpdateStimuli(float dt)
{
	float zero = 0.0f;
	for (uint32_t i = 0; i < 8; i++)
	{
		Stimulus* s = &slot[i];
		uint32_t id = s->id;
		_ReadWriteBarrier();
		uint32_t m = s->mask;
		if ((id | m) != 0)
		{
			float d = s->duration - dt;
			s->duration = d;
			if (d > zero)
				continue;
			mMask1 &= ~m;
			mMask0 &= ~id;
			s->id = 0;
			s->mask = 0;
			s->duration = zero;
			_ReadWriteBarrier();
			IRefCounted* old = s->object;
			if (old)
			{
				s->object = 0;
				old->Release();
			}
			zero = 0.0f;
		}
	}
	return &mMask0;
}

// @ 0x00bc9a00
bool State1c::Has(uint32_t mask_)
{
	if ((mask & mask_) == 0)
		return false;
	for (uint32_t i = 0; i < 8; i++)
		if (rec[i].id & mask_)
			return true;
	return false;
}

// @ 0x00bc9a30
void IntArray::Set(int i, uint32_t v)
{
	vals[i] = v;
}

// @ 0x00bc9a50
Rec44* State44::Find(uint32_t key)
{
	Rec44* r = &rec[key >> 16];
	if (r->kind != (uint16_t)key || r->state == -1)
		return 0;
	return r;
}

// @ 0x00bc9b10
uint32_t EntryState::CurrentId()
{
	return entries[current].id;
}

// @ 0x00bc9b20
bool EntryState::SetCurrent(uint32_t id)
{
	for (uint32_t i = 0; i < count; i++)
		if (entries[i].id == id)
		{
			current = i;
			return true;
		}
	return false;
}

// @ 0x00bc9b70
float* FloatArray::At(int i)
{
	return &vals[i].f;
}

// @ 0x00bc9b80
void FloatArray::Set3(int i, const float* v)
{
	FloatBits* dst = vals + i;
	const FloatBits* src = (const FloatBits*)v;
	dst[0].u = src[0].u;
	dst[1].u = src[1].u;
	dst[2].u = src[2].u;
}

// @ 0x00bc9bb0
float FloatArray::Get(int i)
{
	return vals[i].f;
}

// @ 0x00bc9bc0
void FloatArray::Set(int i, float v)
{
	vals[i].f = v;
}

// @ 0x00bc9bf0
void FloatArray::SetWord(int i, uint32_t v)
{
	vals[i].u = v;
}

// @ 0x00bc9c10
State1c* State1c::Reset()
{
	mask = 0;
	for (uint32_t i = 0; i < 8; i++)
	{
		rec[i].id = 0;
		rec[i].time = 0.0f;
		rec[i].object = 0;
	}
	return this;
}

// @ 0x00bc9c90
void State1c::ReleaseObjects()
{
	for (int i = 8; i-- > 0; )
	{
		IRefCounted* p = rec[i].object;
		if (p)
			p->Release();
	}
}

// @ 0x00bc9cc0
void State1c::Update(float dt)
{
	if (mask == 0)
		return;
	mask = 0;
	for (uint32_t i = 0; i < 8; i++)
	{
		Rec1c* r = &rec[i];
		if (r->id != 0)
		{
			float t = r->time - dt;
			r->time = t;
			IRefCounted* obj = r->object;
			if (t < 0.0f || (obj && obj->V11()))
			{
				r->id = 0;
				_ReadWriteBarrier();
				IRefCounted* old = r->object;
				if (old)
				{
					r->object = 0;
					old->Release();
				}
			}
			else
				mask |= r->id;
		}
	}
}

// @ 0x00bc9d40
Rec1c* State1c::Add(uint32_t id, float duration, IRefCounted* obj, uint32_t field8)
{
	Rec1c* chosen = 0;
	float best = g_0146697C;
	uint32_t i = 0;
	Rec1c* r = rec;
	do
	{
		if (r->id == 0 || (r->id == id && r->object == obj && r->field8 == field8))
		{
			chosen = r;
			break;
		}
		if (r->time < best)
		{
			chosen = r;
			best = r->time;
		}
		i++;
		r++;
	} while (i < 8);
	mask |= id;
	chosen->id = id;
	chosen->time = duration;
	_ReadWriteBarrier();
	IRefCounted* old = chosen->object;
	if (obj != old)
	{
		if (obj)
			obj->AddRef();
		chosen->object = obj;
		if (old)
			old->Release();
	}
	chosen->field8 = field8;
	return chosen;
}

// @ 0x00bc9de0
void State1c::ClearMask(uint32_t m)
{
	for (uint32_t i = 0; i < 8; i++)
	{
		if (rec[i].id & m)
		{
			rec[i].id = 0;
			_ReadWriteBarrier();
			IRefCounted* old = rec[i].object;
			if (old)
			{
				rec[i].object = 0;
				old->Release();
			}
		}
	}
	mask &= ~m;
}

// @ 0x00bc9e30
Rec44* State44::SetupAction(float f, uint32_t a, ActionFn cb, uint32_t c, uint32_t unused)
{
	Rec44* r = &rec[0];
	r->kind = 0;
	r->state = -1;
	r->sub = -1;
	r->f0c = f;
	r->a10 = a;
	r->callback = cb;
	r->a18 = c;
	r->ptr1c = 0;
	r->ptr20 = 0;
	return r;
}

// @ 0x00bc9e70
void State44::ReleaseAction()
{
	Rec44* r = &rec[0];
	IRefCounted* p = r->ptr20;
	if (p)
		p->Release();
	p = r->ptr1c;
	if (p)
		p->Release();
}

// @ 0x00bc9ea0
State44* State44::Reset(uint32_t v)
{
	uint32_t none = (uint32_t)-1;
	InitRec44(&rec[0], none);
	InitRec44(&rec[1], none);
	InitRec44(&rec[2], none);
	InitRec44(&rec[3], none);
	InitRec44(&rec[4], none);
	InitRec44(&rec[5], none);
	InitRec44(&rec[6], none);
	InitRec44(&rec[7], none);
	flag = 0;
	vals[0] = v;
	return this;
}

// @ 0x00bc9fa0
void State44::ReleaseAll()
{
	for (int i = 8; i-- > 0; )
	{
		IRefCounted* p = rec[i].ptr20;
		if (p)
			p->Release();
		p = rec[i].ptr1c;
		if (p)
			p->Release();
	}
}

// @ 0x00bc9fe0
void State44::ClearAll()
{
	for (uint32_t i = 0; i < 8; i++)
	{
		Rec44* r = &rec[i];
		if (r->state != -1)
		{
			if (r->callback)
				r->callback(r);
			r->state = -1;
			_ReadWriteBarrier();
			IRefCounted* old = r->ptr1c;
			if (old)
			{
				r->ptr1c = 0;
				old->Release();
			}
			old = r->ptr20;
			if (old)
			{
				r->ptr20 = 0;
				old->Release();
			}
		}
	}
	flag = 0;
}

// @ 0x00bca040
void cAgentOrderManager::DeactivateSlot(int id)
{
    unsigned idx = (unsigned)id >> 16;
    char* slot = (char*)this + idx * 0x44;
    if (*(short*)(slot + 0x20) == (short)id && *(int*)(slot + 0x24) != -1) {
        void (*cb)(void*) = *(void(**)(void*))(slot + 0x34);
        if (cb != 0) {
            cb(slot);
        }
        *(int*)(slot + 0x24) = -1;

        IRefCount_s00bc_a040* r1 = *(IRefCount_s00bc_a040**)(slot + 0x3c);
        if (r1 != 0) {
            *(void**)(slot + 0x3c) = 0;
            r1->Release();
        }
        IRefCount_s00bc_a040* r2 = *(IRefCount_s00bc_a040**)(slot + 0x40);
        if (r2 != 0) {
            *(void**)(slot + 0x40) = 0;
            r2->Release();
        }
        *(u32*)((char*)this + 0x22c) &= ~(1u << idx);
    }
}

// @ 0x00bca0c0
u32 cAgentOrderManager::FindSlot(int a, int b, int c, int d)
{
    char* p = (char*)this + 0x28;
    u32 i = 0;
    do {
        if (*(int*)(p - 4) == a && *(int*)(p) == b &&
            (c == 0 || *(int*)(p + 0x14) == c) &&
            (d == 0 || *(int*)(p + 0x18) == d)) {
            return (u32)*(u16*)(p - 8) | (i << 16);
        }
        ++i;
        p += 0x44;
    } while (i < 8);
    return 0xffffffffu;
}

// @ 0x00bca120
cAgentOrder::~cAgentOrder()
{
    char* self = (char*)this;
    if (self[0x85] & 4) {
        FUN_0093db80(self + 0x75, 0);
    }
    if (self[0x71] & 4) {
        FUN_0093db80(self + 0x61, 0);
    }
    if (self[0x5d] & 4) {
        FUN_0093db80(self + 0x4d, 0);
    }
    if (self[0x49] & 4) {
        FUN_0093db80(self + 0x39, 0);
    }
    if (mSource != 0) {
        mSource->Release();
    }
    cGonzagoTimer_dtor(&mTimer);
}

// @ 0x00bca180
int cAgentOrder::operator_eq(cAgentOrder const& o)
{
    char* a = (char*)this;
    char* b = (char*)&o;
    if (*(int*)a != *(int*)b) return 0;
    if (*(int*)(a + 0x28) != *(int*)(b + 0x28)) return 0;
    if (*(short*)(a + 0x4b) != *(short*)(b + 0x4b)) return 0;
    if (*(int*)(a + 0x39) != *(int*)(b + 0x39)) return 0;
    if (*(int*)(a + 0x3d) != *(int*)(b + 0x3d)) return 0;
    if (*(int*)(a + 0x41) != *(int*)(b + 0x41)) return 0;
    if (*(int*)(a + 0x45) != *(int*)(b + 0x45)) return 0;
    if (*(short*)(a + 0x5f) != *(short*)(b + 0x5f)) return 0;
    if (*(int*)(a + 0x4d) != *(int*)(b + 0x4d)) return 0;
    if (*(int*)(a + 0x51) != *(int*)(b + 0x51)) return 0;
    if (*(int*)(a + 0x55) != *(int*)(b + 0x55)) return 0;
    if (*(int*)(a + 0x59) != *(int*)(b + 0x59)) return 0;
    if (*(short*)(a + 0x73) != *(short*)(b + 0x73)) return 0;
    if (*(int*)(a + 0x61) != *(int*)(b + 0x61)) return 0;
    if (*(int*)(a + 0x65) != *(int*)(b + 0x65)) return 0;
    if (*(int*)(a + 0x69) != *(int*)(b + 0x69)) return 0;
    if (*(int*)(a + 0x6d) != *(int*)(b + 0x6d)) return 0;
    if (*(short*)(a + 0x87) != *(short*)(b + 0x87)) return 0;
    if (*(int*)(a + 0x75) != *(int*)(b + 0x75)) return 0;
    if (*(int*)(a + 0x79) != *(int*)(b + 0x79)) return 0;
    if (*(int*)(a + 0x7d) != *(int*)(b + 0x7d)) return 0;
    if (*(int*)(a + 0x81) != *(int*)(b + 0x81)) return 0;
    return 1;
}

// @ 0x00bca280
int cAgentOrderManager::IsSourceAtEnd()
{
    IRefCount_s00bc_a040* s = mSource;
    if (s != 0 && *(int*)((char*)s + 0x14) == mSourceStamp) {
        return 1;
    }
    return 0;
}

// @ 0x00bca2a0
int cAgentOrderManager::IsSourceEmpty()
{
    IRefCount_s00bc_a040* s = mSource;
    if (s != 0 && *(int*)((char*)s + 0x18) == *(int*)((char*)s + 0x10)) {
        return 1;
    }
    return 0;
}

// @ 0x00bca2c0
cAgentOrder* cAgentOrderManager::FirstPending()
{
    char* head = (char*)this + 0x60c;
    if (*(char**)head != head) {
        return (cAgentOrder*)(*(char**)head + 8);
    }
    return 0;
}

// @ 0x00bca350
void cAgentOrderManager::Tick(float dt)
{
    u32 live = mActiveMask;
    if (live == 0) {
        return;
    }
    char* slot = (char*)this + 0x38;
    u32 i = 0;
    do {
        if (i >= 8) {
            return;
        }
        u32 bit = 1u << i;
        if (live & bit) {
            float v = *(float*)(slot - 0x0c) - dt;
            live &= ~bit;
            *(float*)(slot - 0x0c) = v;
            if (!(0.0f <= v)) {
                DeactivateSlot((int)(*(u16*)(slot - 0x18) | (i << 16)));
            } else {
                bool (*cb)(void*, float) = *(bool(**)(void*, float))(slot);
                if (cb != 0 && !cb(slot - 0x38, dt)) {
                    DeactivateSlot((int)(*(u16*)(slot - 0x18) | (i << 16)));
                }
            }
        }
        ++i;
        slot += 0x44;
    } while (live != 0);
}

// @ 0x00bca3d0
cAgentOrder* cAgentOrder::Assign(cAgentOrder const& o)
{
    char* dst = (char*)this;
    char* src = (char*)&o;
    u32* d = (u32*)dst;
    u32* s = (u32*)src;
    for (int i = 0; i < 8; ++i) {
        d[i] = s[i];
    }
    *(u16*)(dst + 0x20) = *(u16*)(src + 0x20);
    *(u32*)(dst + 0x24) = *(u32*)(src + 0x24);
    *(u32*)(dst + 0x28) = *(u32*)(src + 0x28);
    *(u32*)(dst + 0x2c) = *(u32*)(src + 0x2c);
    *(u32*)(dst + 0x30) = *(u32*)(src + 0x30);
    *(u32*)(dst + 0x34) = *(u32*)(src + 0x34);
    *(u32*)(dst + 0x38) = *(u32*)(src + 0x38);

    IRefCount_s00bc_a040* ns = *(IRefCount_s00bc_a040**)(src + 0x3c);
    IRefCount_s00bc_a040* os = *(IRefCount_s00bc_a040**)(dst + 0x3c);
    if (ns != os) {
        if (ns != 0) {
            ns->AddRef();
        }
        *(IRefCount_s00bc_a040**)(dst + 0x3c) = ns;
        if (os != 0) {
            os->Release();
        }
    }
    IRefCount_s00bc_a040* n2 = *(IRefCount_s00bc_a040**)(src + 0x40);
    IRefCount_s00bc_a040* o2 = *(IRefCount_s00bc_a040**)(dst + 0x40);
    if (n2 != o2) {
        if (n2 != 0) {
            n2->AddRef();
        }
        *(IRefCount_s00bc_a040**)(dst + 0x40) = n2;
        if (o2 != 0) {
            o2->Release();
        }
    }
    return this;
}

// @ 0x00bca470
cAgentOrder::cAgentOrder()
{
    mId = -1;
    cGonzagoTimer_ctor(&mTimer);
    mSource = 0;
    mTimeLeft = gOrderDef0;
    mF1 = gOrderDef1;
    mF2 = gOrderDef2;
    mFlag = 0;
    char* self = (char*)this;
    *(u16*)(self + 0x49) = 0;
    *(u16*)(self + 0x4b) = 0;
    *(u16*)(self + 0x5f) = 0;
    *(u16*)(self + 0x5d) = 0;
    *(u16*)(self + 0x71) = 0;
    *(u16*)(self + 0x73) = 0;
    *(u16*)(self + 0x85) = 0;
    *(u16*)(self + 0x87) = 0;
}

// @ 0x00bca620
cAgentOrder* cAgentOrderManager::FindNode(int key, int (*pred)(void*, void*), void* ctx)
{
    char* self = (char*)this;
    char* node = *(char**)self;
    while (node != self) {
        if (*(int*)(node + 0x10) == key && node[0x1c] == 0) {
            if (pred == 0 || pred(node + 8, ctx)) {
                return (cAgentOrder*)(node + 8);
            }
        }
        node = *(char**)node;
    }
    return 0;
}

// @ 0x00bca670
void FUN_00bca670(void* p)
{
    char* self = (char*)p;
    if (*(int*)(self + 0x2c) != 0 && *(char**)(self + 0x2c) != 0) {
        char* o = *(char**)(self + 0x2c);
        char* qi = (char*)((IRefCount_s00bc_a040*)o)->QueryInterface(0xce9f6639);
        if (qi != 0) {
            *(u32*)(self + 0x30) = *(u32*)(qi + 0xe54);
        }
    }
}

// @ 0x00bca6a0
void FUN_00bca6a0(void* p)
{
    char* self = (char*)p;
    if (*(int*)(self + 0x2c) != 0 && *(char**)(self + 0x2c) != 0) {
        char* o = *(char**)(self + 0x2c);
        char* qi = (char*)((IRefCount_s00bc_a040*)o)->QueryInterface(0xce9f6639);
        if (qi != 0) {
            if (*(u32*)(self + 0x30) != *(u32*)(qi + 0xe54)) {
                char* cur = *(char**)(self + 0x2c);
                if (cur != 0) {
                    *(u32*)(self + 0x2c) = 0;
                    ((IRefCount_s00bc_a040*)cur)->Release();
                }
                *(u32*)(self + 0x30) = 0;
            }
        }
    }
}

// @ 0x00bca6f0
void FUN_00bca6f0(void)
{
    *(void**)0x168b54c = (void*)&FUN_00bca670;
    *(void**)0x168b550 = (void*)&FUN_00bca6a0;
    FUN_00bc8fa0((void*)0x1590800);
    FUN_00bc8fa0((void*)0x1590888);
    FUN_00bc8fa0((void*)0x15906f0);
    FUN_00bc8fa0((void*)0x1590778);
    FUN_00bc8fa0((void*)0x1590910);
    FUN_00bc8fa0((void*)0x1590998);
    FUN_00bc8fa0((void*)0x1590a20);
    FUN_00bc8fa0((void*)0x1590aa8);
    FUN_00bc8fa0((void*)0x1590b30);
    FUN_00bc8fa0((void*)0x15aa9e8);
}

// @ 0x00bca7a0
bool FUN_00bca7a0(void* ser, char* list)
{
    char* node = *(char**)list;
    while (node != list) {
        char* order = node + 8;
        if (order != 0) {
            ((cSerializer*)ser)->SaveObject(order, &gDescAgentOrder, gNameAgentOrder);
        }
        node = *(char**)node;
    }
    return true;
}

// @ 0x00bca7e0
bool FUN_00bca7e0(void* a1, void** slot)
{
    void* obj = *slot;
    if (obj != 0) {
        IRefCount_s00bc_a040* qi = (IRefCount_s00bc_a040*)((IRefCount_s00bc_a040*)obj)->QueryInterface(0x179c807);
        if (qi != 0) {
            qi->vtbl1c(a1);
        }
    }
    return true;
}

// @ 0x00bca810
u32 cAgentOrderManager::Activate(int tmplIdx, int type, IRefCount_s00bc_a040* p1, float timeLeft, void* header, IRefCount_s00bc_a040* p2)
{
    float best = gFloatMax;
    u32 idx = 0;
    u32 chosen = 0;
    char* f = (char*)this + 0x2c;
    do {
        if (*(int*)(f - 8) == -1) {
            chosen = idx;
            break;
        }
        if (best >= *(float*)f) {
            best = *(float*)f;
            chosen = idx;
        }
        ++idx;
        f += 0x44;
    } while (idx < 8);

    char* slot = (char*)this + chosen * 0x44;
    DeactivateSlot((int)(*(u16*)((char*)this + 0x20 + chosen * 0x44) | (chosen << 16)));
    ((cAgentOrder*)slot)->Assign(
        *(cAgentOrder*)(*(char**)((char*)this + 0x220 + type * 4) + tmplIdx * 0x44));

    {
        IRefCount_s00bc_a040* old = *(IRefCount_s00bc_a040**)(slot + 0x3c);
        if (p1 != old) {
            if (p1 != 0) {
                p1->AddRef();
            }
            *(IRefCount_s00bc_a040**)(slot + 0x3c) = p1;
            if (old != 0) {
                old->Release();
            }
        }
    }
    *(u16*)(slot + 0x20) = gAgentOrderId;
    ++gAgentOrderId;
    *(int*)(slot + 0x28) = type;
    if (!(timeLeft == gZeroFloat)) {
        *(float*)(slot + 0x2c) = timeLeft;
    }
    if (header != 0) {
        u32* d = (u32*)slot;
        u32* s = (u32*)header;
        for (int i = 0; i < 8; ++i) {
            d[i] = s[i];
        }
    }
    {
        IRefCount_s00bc_a040* old = *(IRefCount_s00bc_a040**)(slot + 0x40);
        if (p2 != old) {
            if (p2 != 0) {
                p2->AddRef();
            }
            *(IRefCount_s00bc_a040**)(slot + 0x40) = p2;
            if (old != 0) {
                old->Release();
            }
        }
    }
    mActiveMask |= 1u << chosen;
    {
        void (*cb)(void*) = *(void(**)(void*))(slot + 0x30);
        if (cb != 0) {
            cb(slot);
        }
    }
    return (u32)*(u16*)(slot + 0x20) | (chosen << 16);
}

// @ 0x00bca960
bool FUN_00bca960(void* a1, void** slot)
{
    void* o = 0;
    if (*slot != 0) {
        o = (void*)((IRefCount_s00bc_a040*)*slot)->QueryInterface(0x179c807);
    }
    ((IVtbl2c*)a1)->v2c(o);
    return true;
}

// @ 0x00bca990
void FUN_00bca990(void* a1, char* list)
{
    int n = 0;
    for (char* n2 = *(char**)list; n2 != list; n2 = *(char**)n2) {
        ++n;
    }
    void* s = (void*)(*(void*(**)(void*))(*(char**)a1 + 0x20))(a1);
    void* ws = (void*)(*(void*(**)(void*))(*(char**)s + 0x18))(s);
    FUN_0093aa70(ws, (unsigned*)&n, 1, 0);
    for (char* n2 = *(char**)list; n2 != list; n2 = *(char**)n2) {
        ((cAgentOrder*)(n2 + 8))->Serialize((cOutStream*)a1);
    }
    void (*fn)(void*) = *(void(**)(void*))(*(char**)a1 + 0x1c);
    fn(a1);
}

// @ 0x00bcaa00
void cAgentOrderManager::FreeAll()
{
    char* self = (char*)this;
    char* node = *(char**)self;
    while (node != self) {
        char* next = *(char**)node;
        *(void**)(node + 8) = (void*)0x1466998;
        IRefCount_s00bc_a040* r = *(IRefCount_s00bc_a040**)(node + 0x1a8);
        if (r != 0) {
            r->Release();
        }
        *(void**)(node + 8) = (void*)0x13ec458;
        *(void**)node = *(void**)(self + 0x18);
        *(void**)(self + 0x18) = node;
        node = next;
    }
}

// @ 0x00bcaa50
void cAgentOrderManager::ReleaseNode(char** out, char* node)
{
    char* self = (char*)this;
    char* next = *(char**)node;
    char* prev = *(char**)(node + 4);
    *(char**)prev = next;
    *(char**)(next + 4) = prev;

    *(void**)(node + 8) = (void*)0x1466998;
    IRefCount_s00bc_a040* r = *(IRefCount_s00bc_a040**)(node + 0x1a8);
    if (r != 0) {
        r->Release();
    }
    *(void**)(node + 8) = (void*)0x13ec458;
    *(void**)node = *(void**)((char*)self + 0x18);
    *(void**)((char*)self + 0x18) = node;
    *out = next;
}

// @ 0x00bcaab0
void cAgentOrderManager::AllocNode()
{
    char* esi = (char*)this + 8;
    char* p;
    for (;;) {
        if (*(char**)(esi + 0x10) != 0) {
            p = *(char**)(esi + 0x10);
            *(char**)(esi + 0x10) = *(char**)p;
            break;
        }
        if (!FUN_00926650(esi, 0, 0)) {
            p = 0;
            break;
        }
    }
    if (p != 0) {
        *(u32*)(p + 4) = 0;
        *(void**)p = (void*)0x1466998;
        *(u8*)(p + 0x1c) = 0;
        *(u32*)(p + 0x1a0) = 0;
        *(u32*)(p + 0x224) = 0;
        *(u32*)(p + 0x228) = 0;
    }
}

// @ 0x00bcab00
void cAgentOrderManager::ClearList()
{
    char* self = (char*)this;
    char* node = *(char**)self;
    while (node != self) {
        char* esi = node;
        char* next = *(char**)node;
        node = next;
        if (esi[0x8d] & 4) {
            FUN_0093db80(esi + 0x7d, 0);
        }
        if (esi[0x79] & 4) {
            FUN_0093db80(esi + 0x69, 0);
        }
        if (esi[0x65] & 4) {
            FUN_0093db80(esi + 0x55, 0);
        }
        if (esi[0x51] & 4) {
            FUN_0093db80(esi + 0x41, 0);
        }
        IRefCount_s00bc_a040* r = *(IRefCount_s00bc_a040**)(esi + 0x30);
        if (r != 0) {
            r->Release();
        }
        cGonzagoTimer_dtor((cGonzagoTimer*)(esi + 0x10));
        *(void**)esi = *(void**)(self + 0x18);
        *(void**)(self + 0x18) = esi;
    }
}

// @ 0x00bcab80
cAgentOrder* cAgentOrder::CopyConstruct(cAgentOrder const& o)
{
    char* self = (char*)this;
    char* src = (char*)&o;
    *(u32*)self = *(u32*)src;
    *(void**)(self + 8) = (void*)0x1465d54;
    *(u32*)(self + 0x0c) = 0;
    *(u32*)(self + 0x10) = *(u32*)(src + 0x10);
    *(u32*)(self + 0x14) = *(u32*)(src + 0x14);
    *(u32*)(self + 0x18) = *(u32*)(src + 0x18);
    *(u32*)(self + 0x1c) = *(u32*)(src + 0x1c);
    *(u8*)(self + 0x20) = *(u8*)(src + 0x20);
    *(u32*)(self + 0x24) = *(u32*)(src + 0x24);
    *(void**)(self + 8) = (void*)0x1464450;

    IRefCount_s00bc_a040* sp = *(IRefCount_s00bc_a040**)(src + 0x28);
    *(IRefCount_s00bc_a040**)(self + 0x28) = sp;
    if (sp != 0) {
        sp->AddRef();
    }
    *(u32*)(self + 0x2c) = *(u32*)(src + 0x2c);
    *(u32*)(self + 0x30) = *(u32*)(src + 0x30);
    *(u32*)(self + 0x34) = *(u32*)(src + 0x34);
    *(u8*)(self + 0x38) = *(u8*)(src + 0x38);

    *(u16*)(self + 0x49) = 0;
    *(u16*)(self + 0x4b) = 0;
    FUN_00542b80(self + 0x39, src + 0x39);
    *(u16*)(self + 0x5d) = 0;
    *(u16*)(self + 0x5f) = 0;
    FUN_00542b80(self + 0x4d, src + 0x4d);
    *(u16*)(self + 0x71) = 0;
    *(u16*)(self + 0x73) = 0;
    FUN_00542b80(self + 0x61, src + 0x61);
    *(u16*)(self + 0x85) = 0;
    *(u16*)(self + 0x87) = 0;
    FUN_00542b80(self + 0x75, src + 0x75);
    return this;
}

// @ 0x00bcac60
void cAgentOrderManager::AllocLink()
{
    char* self = (char*)this;
    char* edi = self + 8;
    char* p;
    for (;;) {
        if (*(char**)(edi + 0x10) != 0) {
            p = *(char**)(edi + 0x10);
            *(char**)(edi + 0x10) = *(char**)p;
            break;
        }
        if (!FUN_00926650(edi, 0, 0)) {
            p = 0;
            break;
        }
    }
    if (p != 0) {
        ((cAgentOrder*)(p + 8))->cAgentOrder::cAgentOrder();
    }
    *(char**)p = self;
    *(char**)(p + 4) = *(char**)(self + 4);
    **(char***)(self + 4) = p;
    *(char**)(self + 4) = p;
}

// @ 0x00bcacb0
int FUN_00bcacb0(char* list, IRefCount_s00bc_a040* obj)
{
    char* node = *(char**)list;
    while (node != list) {
        if ((IRefCount_s00bc_a040*)(node + 8) == obj) {
            char* next;
            ((cAgentOrderManager*)list)->ReleaseNode(&next, node);
            return 1;
        }
        node = *(char**)node;
    }
    return 0;
}

// @ 0x00bcae90
cAgentOrderManager::~cAgentOrderManager()
{
    char* self = (char*)this;
    char* arr = *(char**)(self + 0x65c);
    char* arrEnd = *(char**)(self + 0x664);
    if (arrEnd - arr > 1 && arr != 0) {
        FUN_00f47380(arr);
    }

    {
        char* lst = self + 0x634;
        char* p = *(char**)lst;
        while (p != lst) {
            char* next = *(char**)p;
            *(void**)p = *(void**)(lst + 0x18);
            *(void**)(lst + 0x18) = p;
            p = next;
        }
    }
    FUN_00926640(self + 0x63c);

    ClearList();
    FUN_00926640(self + 0x614);

    if (mSource != 0) {
        mSource->vtbl08();
    }
    char* ap = *(char**)(self + 0x5e8);
    if (ap != 0 && *(int*)(ap - 4) != 0) {
        FUN_00f47380(ap);
    }

    char* p = self + 0x1f4;
    for (int i = 7; i >= 0; --i) {
        p -= 0x38;
        IRefCount_s00bc_a040* r = *(IRefCount_s00bc_a040**)p;
        if (r != 0) {
            r->Release();
        }
    }
}

// @ 0x00bcaf40
void cAgentOrderManager::PopFront()
{
    char* self = (char*)this;
    char* head = self + 0x60c;
    if (*(char**)head == head) {
        return;
    }
    char* node = *(char**)head;
    char* next = *(char**)(node + 4);
    char* prev = *(char**)node;
    *(char**)next = prev;
    *(char**)(prev + 4) = next;
    ((cAgentOrder*)(node + 8))->cAgentOrder::~cAgentOrder();
    *(void**)node = *(void**)(head + 0x18);
    *(void**)(head + 0x18) = node;
}

// @ 0x00bcaf70
cAgentOrder* cAgentOrderManager::PushBack(void* a, IRefCount_s00bc_a040* b, char clear)
{
    char* self = (char*)this;
    if (clear != 0) {
        char* lst = self + 0x60c;
        ClearList();
        *(char**)lst = lst;
        *(char**)(lst + 4) = lst;
    }
    AllocLink();
    char* node = *(char**)(self + 0x610);
    *(void**)(node + 8) = a;
    IRefCount_s00bc_a040* old = *(IRefCount_s00bc_a040**)(node + 0x30);
    if (b != old) {
        if (b != 0) {
            b->AddRef();
        }
        *(IRefCount_s00bc_a040**)(node + 0x30) = b;
        if (old != 0) {
            old->Release();
        }
    }
    return (cAgentOrder*)(node + 8);
}

// @ 0x00bcafe0
void cAgentOrderManager::ReleaseQueueObject(char* obj, u32 idx)
{
    if (obj == 0) {
        return;
    }
    u32 count = *(u32*)(obj + 0x18);
    if (idx >= count) {
        return;
    }
    if (*(u32*)(obj + 0x10) > 1 && idx == *(u32*)(obj + 0x14)) {
        char found = 0;
        u32 i = 0;
        if (count != 0) {
            char* e = obj + 0x20;
            do {
                if (i != idx && *e != 0) {
                    int (*cb)(char*, u32) = *(int(**)(char*, u32))(obj + 0x228);
                    if (cb == 0) {
                        *(u32*)(obj + 0x14) = i;
                        goto cleared;
                    }
                    int r = cb(obj, *(u32*)(e + 4));
                    if (r == 0) {
                        *(u32*)(obj + 0x14) = i;
                        goto cleared;
                    }
                    if (r == 1) {
                        *(u32*)(obj + 0x14) = i;
                        found = 1;
                    }
                }
                ++i;
                e += 0xc;
            } while (i < *(u32*)(obj + 0x18));
            if (found) {
                goto cleared;
            }
        }
        obj[0x1c] = 1;
    }

cleared:
    obj[0x20 + idx * 0xc] = 0;
    if (--*(int*)(obj + 0x10) == 0) {
        obj[0x1c] = 1;
        void (*cb)(char*) = *(void(**)(char*))(obj + 0x224);
        if (cb != 0) {
            cb(obj);
        }
        FUN_00bcacb0((char*)this, (IRefCount_s00bc_a040*)obj);
    }
}

// @ 0x00bcb0b0
ListEntry* RawList::Insert(const char* name, unsigned typeId, int value, int flags)
{
    ListNode* node = AllocNode();
    node->mpNext = (ListNode*)this;
    node->mpPrev = mpPrev;
    mpPrev->mpNext = node;
    mpPrev = node;
    ListEntry* e = &node->mEntry;
    ((FnThis0)(*(void***)e)[1])(e);
    e->mpName = name;
    e->m0c = (uint32_t)value;
    e->m10 = 0;
    e->m14 = 0;
    const uint32_t& clamped = MinRef(MaxRef(typeId, 1u), 0x20u);
    e->mValue = clamped;
    operator_new__((char*)e + 0x20, 0, 0x180);
    operator_new__((char*)e + 0x1a4, 0, 0x80);
    return e;
}

// @ 0x00bcb160
bool __cdecl WriteListProperty(void* writer, const char* name, RawList* list)
{
    bool ok = true;
    if (list->mpNext != (ListNode*)list) {
        string16_s00bc_b0b0 s = name ? ConvertToString16(name, -1) : string16_s00bc_b0b0();
        const char16* label = s.empty() ? (const char16*)L"list" : s.mpBegin;
        ((void (__thiscall*)(void*, const char16*))(*(void***)writer)[0])(writer, label);
        for (ListNode* n = list->mpNext; n != (ListNode*)list; n = n->mpNext)
            ok = ok && WriteListElement(writer, 0, &n->mEntry);
        ((void (__thiscall*)(void*, const char16*))(*(void***)writer)[1])(writer, label);
    }
    return ok;
}

// @ 0x00bcb2a0
cVarListEditor* cVarListEditor::Construct()
{
    mpObject = 0;
    for (int i = 0; i < 8; i++)
        mElems[i * 0x38 / 4 + 0x2c / 4] = 0;
    ((ElemOps*)&mElems[0])->Clear();
    ((ElemOps*)mSub1)->Alloc();

    mpVecBegin = 0;
    mpVecEnd = 0;
    mpVecCap = 0;
    mp5fc = 0;
    mpSelected = 0;
    mIndex = -1;
    mpItem = 0;

    {
        FixedAllocatorBase a(0x98, 8, 1, 0, -1, (void*)&wrapper_alloc, (void*)&wrapper_free, "Simulator/list");
        mList1.mAlloc = a;
        mList1.mpNext = (ListNode*)&mList1;
        mList1.mpPrev = (ListNode*)&mList1;
    }
    {
        FixedAllocatorBase a(0x28, 4, 8, 0, -1, (void*)&wrapper_alloc, (void*)&wrapper_free, "Simulator/list");
        mList2.mAlloc = a;
        mList2.mpNext = (ListNode*)&mList2;
        mList2.mpPrev = (ListNode*)&mList2;
    }
    mName.mpBegin = (char16*)gEmptyString16;
    mName.mpEnd = (char16*)gEmptyString16;
    mName.mpCapacity = (char16*)gEmptyString16 + 1;
    return this;
}

// @ 0x00bcb3d0
void cVarListEditor::Reset()
{
    ((ElemOps*)mSub1)->Alloc();
    ((ElemOps*)&mElems[0])->Clear();
    Quad16_s00bc_b0b0* begin = mpVecBegin;
    Quad16_s00bc_b0b0* end = mpVecEnd;
    copy_705250(end, end, begin);
    mpVecEnd = (Quad16_s00bc_b0b0*)((char*)mpVecEnd + (((char*)end - (char*)begin) >> 4) * -16);
    mpObject = 0;
    RawList* list = &mList1;
    list->Clear();
    list->mpNext = (ListNode*)list;
    list->mpPrev = (ListNode*)list;
}

// @ 0x00bcb430
void cVarListEditor::ClearSelection()
{
    SelItem* p = mpSelected;
    if (p) {
        mpSelected = 0;
        ((FnThis0)(*(void***)p)[2])(p);
    }
    g_pVarListEditor->RemoveItem(p, mIndex);
    mIndex = -1;
}

// @ 0x00bcb510
int cVarListEditor::SelectByName(const char* name, int a, const char* c)
{
    SelItem* sel = mpSelected;
    if (mpItem && sel) {
        const char* key = c ? c : name;
        SelItem* found = g_pVarListEditor->FindItem(sel->m08, mpItem, key);
        if (found) {
            if (found != mpSelected)
                SetSelection(found, (int)name, a, mpItem);
            if (found != sel)
                return true;
        }
    }
    return false;
}

// @ 0x00bcb590
RawList* RawList::Construct()
{
    FixedAllocatorBase a(0x234, 4, 0x20, 0, -1, (void*)&wrapper_alloc, (void*)&wrapper_free, "Simulator/list");
    mAlloc = a;
    mpNext = (ListNode*)this;
    mpPrev = (ListNode*)this;
    return this;
}

// @ 0x00bcb5f0
void QuadVec::SetArraySize(unsigned count)
{
    Quad16_s00bc_b0b0* end = mpEnd;
    Quad16_s00bc_b0b0* begin = mpBegin;
    unsigned n = (unsigned)(end - begin);
    if (count > n) {
        Quad16_s00bc_b0b0 v;
        v.mIndex = -1;
        v.mValue = 0.0;
        DoInsertN(end, count - n, &v);
        return;
    }
    Quad16_s00bc_b0b0* p = begin + count;
    copy_705250(end, end, p);
    int back = (int)((char*)end - (char*)p) >> 4;
    back = -back;
    mpEnd = (Quad16_s00bc_b0b0*)((char*)mpEnd + back * 16);
}

// @ 0x00bcb660
void cVarListEditor::SetListObject(VarSource* item)
{
    if (mpObject)
        Reset();
    mpObject = item;
    if (item) {
        QuadVec* vec = (QuadVec*)&mpVecBegin;
        vec->SetArraySize(item->mCount);
        for (unsigned i = 0; i < item->mCount; i++) {
            Quad16_s00bc_b0b0* e = &mpVecBegin[i];
            e->mValue = 0.0;
            e->mIndex = -1;
        }
    }
}

// @ 0x00bcb700
void __cdecl DestroyVarList()
{
    cVarListEditor* p = g_pVarListEditor;
    if (p) {
        ((RawList*)p)->Clear();
        ((RawList*)p)->mAlloc.~FixedAllocatorBase();
        operator_delete(p);
    }
    g_pVarListEditor = 0;
}

// @ 0x00bcb730
void __cdecl ReadListProperty(void* stream, RawList* list)
{
    list->Clear();
    list->mpNext = (ListNode*)list;
    list->mpPrev = (ListNode*)list;
    uint32_t count = 0;
    void* a = ((void* (__thiscall*)(void*))(*(void***)stream)[8])(stream);
    void* s = ((void* (__thiscall*)(void*))(*(void***)a)[6])(a);
    ReadInt32_93a780(s, &count, 1, 0);
    for (uint32_t i = 0; i < count; i++) {
        ListRecord rec;
        rec.mVec.x = g_readVecSeed.x;
        rec.mVec.y = g_readVecSeed.y;
        rec.mVec.z = g_readVecSeed.z;
        cVarListSerializer ser;
        ser.Construct(&rec, &s_serializerGenericList, 0x1a80d26);
        ser.Serialize(stream);

        ListNode* node;
        FixedAllocatorBase* const alloc = &list->mAlloc;
        do {
            if (alloc->mFields[4]) {
                node = (ListNode*)alloc->mFields[4];
                alloc->mFields[4] = *(uint32_t*)node;
                goto have;
            }
        } while (alloc->AddCore(0, 0));
        node = 0;
    have:
        ListEntry* entry = (ListEntry*)((char*)node + 8);
        if (entry)
            entry->Construct(&rec);
        node->mpNext = (ListNode*)list;
        node->mpPrev = list->mpPrev;
        list->mpPrev->mpNext = node;
        list->mpPrev = node;
    }
    ((void (__thiscall*)(void*))(*(void***)stream)[7])(stream);
}

// @ 0x00bcb960
void cAnimalTrap::SetState(int s)
{
    mState = s;
    if (s == 5)
        m110 = 0;
}

// @ 0x00bcb980
cAnimalTrap* cAnimalTrap::Construct()
{
    ((CGameDataOps*)this)->Ctor();
    ((CSpatialOps*)&mSpatial)->Ctor();
    vptr = vtbl_cAnimalTrap;
    mRefVtbl = vtbl_cAnimalTrapRef;
    mSpatial.vptr = vtbl_cAnimalTrapSpatial;
    mState = 0;
    m10c = 0;
    m110 = 0;
    mp114 = 0;
    mSpatial.m54 = 2;
    mSpatial.m90 = FNV1_String8("trg_sacrifice_altar1", 0x811c9dc5, 1);
    mSpatial.m98 = FNV1_String8("TribalTools", 0x811c9dc5, 1);
    return this;
}

// @ 0x00bcba80
void cAnimalTrap::Destroy()
{
    if (mp114) {
        ((void (__thiscall*)(void*, int))(*(void***)mp114)[3])(mp114, 1);
        if (mp114) {
            void* p = mp114;
            mp114 = 0;
            ((FnThis0)(*(void***)p)[1])(p);
        }
    }
    if (mp2c) {
        void* p = mp2c;
        mp2c = 0;
        ((FnThis0)(*(void***)p)[1])(p);
    }
    ((CSpatialOps*)&mSpatial)->Destroy();
}

// @ 0x00bcbad0
bool cAnimalTrap::Write(void* stream)
{
    void* a = ((void* (__thiscall*)(void*))(*(void***)stream)[8])(stream);
    uint32_t version = 0x61494bd;
    void* b = ((void* (__thiscall*)(void*))(*(void***)a)[6])(a);
    WriteUint32_93aa70(b, &version, 1, 0);
    bool ok = ((CGameDataOps*)this)->Write(stream)
           && ((CSpatialOps*)&mSpatial)->Write(stream);
    cVarListSerializer ser;
    ser.Construct(this, &s_serializerGeneric, 0x1a80d26);
    if (ok && ser.Serialize(stream))
        return true;
    return false;
}

// @ 0x00bcbc30
cAnimalTrap* cAnimalTrap::ScalarDeletingDtor(unsigned flags)
{
    vptr = vtbl_cAnimalTrap;
    mRefVtbl = vtbl_cAnimalTrapRef;
    mSpatial.vptr = vtbl_cAnimalTrapSpatial;
    _ReadWriteBarrier();
    void* p = mp114;
    if (p)
        ((FnThis0)(*(void***)p)[1])(p);
    ((CSpatialOps*)&mSpatial)->DtorBody();
    ((CGameDataOps*)this)->Dtor();
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00bcbc80
void cAnimalTrap::Update()
{
    if (mp114 && ((bool (__thiscall*)(void*))(*(void***)mp114)[4])(mp114))
        return;

    EffectParams ep;
    ep.mFlags = 0;
    ep.mRefCount = 0;
    ep.mPos.x = g_vecZero.x;
    ep.mPos.y = g_vecZero.y;
    ep.mPos.z = g_vecZero.z;

    Matrix3 mtx;
    Matrix3Assign(&mtx, &g_matrixSeed);

    void* spatial = &mSpatial;
    ep.mPos = *(const Vector3f*)((void* (__thiscall*)(void*))(*(void***)spatial)[0x2c / 4])
                  (spatial);
    ep.mFlags |= 4;
    ep.mRefCount++;

    Vector3f up;
    ((void (__thiscall*)(void*, Vector3f*))(*(void***)spatial)[0x5c / 4])(spatial, &up);

    const Vector3f* pos = (const Vector3f*)((void* (__thiscall*)(void*))
                            (*(void***)spatial)[0x2c / 4])(spatial);
    Vector3f facing;
    float inv = 1.0f / sqrtf(pos->x * pos->x + pos->y * pos->y + pos->z * pos->z + g_eps0);
    facing.x = pos->x * inv;
    facing.y = pos->y * inv;
    facing.z = pos->z * inv;

    Matrix3 tmp;
    Matrix3FromFacingAndUp(&tmp, &up, &facing);
    mtx = tmp;

    ep.mFlags |= 2;
    ep.mRefCount++;
    ep.mRefCount++;
    ep.mScale = g_one;

    void* em = EffectsManager();
    if (mp114) {
        void* p = mp114;
        mp114 = 0;
        ((FnThis0)(*(void***)p)[1])(p);
    }
    if (((bool (__thiscall*)(void*, uint32_t, int, void**))(*(void***)em)[0x2c / 4])
            (em, 0x39897926, 0, &mp114)) {
        ((void (__thiscall*)(void*, EffectParams*))(*(void***)mp114)[6])(mp114, &ep);
        ((void (__thiscall*)(void*, int))(*(void***)mp114)[2])(mp114, 0);
    }
    if (mState == 4) {
        void* em2 = EffectsManager();
        if (mp114) {
            void* p = mp114;
            mp114 = 0;
            ((FnThis0)(*(void***)p)[1])(p);
        }
        if (((bool (__thiscall*)(void*, uint32_t, int, void**))(*(void***)em2)[0x2c / 4])
                (em2, 0x2cb92f84, 0, &mp114)) {
            ((void (__thiscall*)(void*, EffectParams*))(*(void***)mp114)[6])(mp114, &ep);
            ((void (__thiscall*)(void*, int))(*(void***)mp114)[2])(mp114, 0);
        }
    }

    void* propOwner = FUN_00d1e660();
    float radius = GetPropertyFloat(*(void**)(*(uint32_t*)((char*)propOwner + 0x1c) + 0x130),
                                    0xb1112498, g_defaultRadius);

    struct BufHolder { uint32_t mOwner; void* mItems[32]; };
    BufHolder holder;
    PtrVec vec;
    holder.mOwner = 0;
    vec.mpBegin = holder.mItems;
    vec.mpEnd = holder.mItems;
    vec.mpCap = holder.mItems + 32;
    void* hits = FUN_00b3d240();
    uint32_t q = ((uint32_t (__thiscall*)(void*, float, PtrVec*, int, int, int))
                  (*(void***)spatial)[0x2c / 4])(spatial, radius, &vec, 0, 0, 0);
    if (((bool (__thiscall*)(void*, uint32_t))(*(void***)hits)[0x48 / 4])(hits, q)) {
        unsigned n = (unsigned)(vec.mpEnd - vec.mpBegin);
        for (unsigned i = 0; i < n; i++) {
            void* obj = vec.mpBegin[i];
            if (!obj)
                continue;
            void* found = ((void* (__thiscall*)(void*, uint32_t))(*(void***)obj)[0xb8 / 4])
                              (obj, 0xd0036e08);
            if (!found)
                continue;
            void* chief = GetChieftain(GetPlayerTribe(NounManager()));
            void* tool = (void*)((char*)found + 0x5a8);
            void* chiefTool = chief ? (void*)((char*)chief + 0x5a8) : 0;
            NounManager();
            int empire = GetPlayerEmpireOrMinus1();
            ((void (__thiscall*)(void*, float, int, int, const Vector3f*, void*))
                (*(void***)tool)[6])(tool, g_bigDistance, empire, 0x11, &up, chiefTool);
        }
    }

    mState++;
    if (mState == 5)
        m110 = 0;
    for (void** it = vec.mpBegin; it < vec.mpEnd; ++it) {
        void* obj = *it;
        if (obj)
            ((void (__thiscall*)(void*))(*(void***)obj)[0xc0 / 4])(obj);
    }
    if (vec.mpBegin && *(uint32_t*)(vec.mpBegin - 1))
        operator_delete(vec.mpBegin);
}

// @ 0x00bcc010
void __thiscall cTribeTool::bcc010()
{
    cTribeTool* self = this;
    void* mgr = FUN_00d1e660();
    char* noun = *(char**)((char*)mgr + 0x1c);
    void* svc = *(void**)(noun + 0x130);
    int selA;
    if (svc == 0 || !((char(__thiscall*)(void*, int, int*))VF(svc, 9))(svc, 0x1070c664, &selA)) {
        selA = 5;
    } else {
        short t = *(short*)(selA + 0x12);
        if (t == 9 || t == 0x10) {
            if ((*(unsigned char*)(selA + 0x10) & 0x30) == 0)
                selA = selA & -(int)(t != 0);
            else
                selA = *(int*)(*(int*)selA);
        } else {
            selA = *(int*)0x15d9c68;
        }
    }

    int   selB;
    float f;
    if (svc == 0 || !((char(__thiscall*)(void*, int, int*))VF(svc, 9))(svc, 0xe17636cf, &selB)) {
        f = *(float*)0x13f1cac;
    } else {
        short t = *(short*)(selB + 0x12);
        if (t == 0xd || t == 0x10) {
            if ((*(unsigned char*)(selB + 0x10) & 0x30) == 0)
                f = *(float*)(selB & -(int)(t != 0));
            else
                f = *(float*)*(int*)selB;
        } else {
            f = *(float*)0x15d9c6c;
        }
    }
    float dist2 = f * f;

    int    count = 0;
    cGameNounManager_s00bc_c010* nm = (cGameNounManager_s00bc_c010*)FUN_00b3d300();
    int*   vec = nm->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                       (void*)FUN_00ace0f0, (void*)FUN_00b1e500, 0x18eb45e);
    int*   p   = (int*)vec[1];
    while (p != (int*)vec[2]) {
        if ((unsigned)count >= (unsigned)selA) break;
        char* obj = (char*)*p;
        if (*(char*)(obj + 0xb5e) == 0 && *(char*)(obj + 0x135) != 0) {
            float* a = (float*)((int(__thiscall*)(void*))VF((char*)self + 0x34, 11))((char*)self + 0x34);
            float* b = (float*)((int(__thiscall*)(void*))VF(obj + 0xc0, 11))(obj + 0xc0);
            float dx = b[0] - a[0];
            float dy = b[1] - a[1];
            float dz = b[2] - a[2];
            float d2 = dx * dx + dy * dy + dz * dz;
            if (d2 < dist2) {
                count++;
                char* r = (char*)((void*(__thiscall*)(void*, int, int, float, void*))
                                  VF(*(char**)(obj + 0xb4c) + 8, 0))(*(char**)(obj + 0xb4c) + 8,
                                                                    0, 0x100, *(float*)0x1466a3c, self);
                if (r != 0) {
                    *(float*)(r + 0xc)  = *(float*)0x1485720;
                    *(float*)(r + 0x10) = *(float*)0x1485720;
                }
            }
        }
        p++;
    }
    *(int*)((char*)self + 0x10c) = 0;
}

// @ 0x00bcc230
void __thiscall cTribeTool::bcc230(int elapsed)
{
    cTribeTool* self = this;
    void* mgr = FUN_00d1e660();
    char* noun = *(char**)((char*)mgr + 0x1c);
    int state = *(int*)((char*)self + 0x108);
    if (state >= 2) {
      if (state <= 4) {
        *(uint32_t*)((char*)self + 0x110) += elapsed;
        *(uint32_t*)((char*)self + 0x10c) += elapsed;
        void* tool = *(void**)(noun + 0x130);
        uint32_t p1 = FUN_004e1c30(tool, 0xbbcb85bc, 0x78) * 1000;
        uint32_t p2 = FUN_004e1c30(*(void**)(noun + 0x130), 0xbe3ce72d, 0x1e) * 1000;
        if (*(uint32_t*)((char*)self + 0x110) > p1) {
            *(int*)((char*)self + 0x108) = 4;
            self->ResetTool();
        } else if (*(uint32_t*)((char*)self + 0x10c) > p2) {
            self->bcc010();
        }
      }
    }
    if (*(int*)((char*)self + 0x108) == 5) {
        *(uint32_t*)((char*)self + 0x110) += elapsed;
        void* tool = *(void**)(noun + 0x130);
        if (*(uint32_t*)((char*)self + 0x110) > (uint32_t)(FUN_004e1c30(tool, 0x42729a8, 5) * 1000))
            ((cGameNounManager_s00bc_c010*)FUN_00b3d300())->RemoveNoun(self);
    }
}
