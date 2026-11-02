// src/game/SPGonzago/_at_00c70000.cpp -- migrated from slice(s) s00c7e1c0, s00c7d120, s00c7c0c0, s00c73cb0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00c70000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivData.h"
#include "SP/cCombatant.h"
#include "SP/PlayerPlanetData.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cCollectableItems.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPlanetModel.h"
#include "SP/cPlayer.h"
#include "SP/cPropertyManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <string.h>
#include <new>
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern float g_13f08c0;   // 0x013f08c0

// ---- items of slice s00c73cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* NounManager();                                                       // 0x00b3d300
void* eastl_lower_bound(void* b, void* e, void* k, unsigned char c);       // 0x00ba2e50
void* FUN_00d01260(void* b, void* e, void* k, unsigned char c);            // 0x00d01260
void* FUN_00ba57f0(void* key, int n);                                      // 0x00ba57f0
void* __stdcall FUN_00b3d4f0(void* x);                                     // 0x00b3d4f0
void* FUN_00b21340(void* mgr, void* f1, void* f2, void* f3, void* f4, void* id); // 0x00b21340
extern float g_13f08c0;   // 0x013f08c0
struct Notifier { void Notify(); };
struct EaMap {
    void*         begin;          // +0x00
    void*         end;            // +0x04
    char          mPad08[0x0c];   // +0x08
    unsigned char mCmp14;         // +0x14
    char          mPad15[3];      // +0x15
    void* find(void* key);              // 0x00ba4e60  thiscall, ret 4
    void  find(void* out, void* key);   // 0x00c729b0  thiscall, ret 8
    void* insert(void* key);            // 0x00ba4520  thiscall, ret 4
};
struct EaVec { void* begin; void* end; };  // two-pointer eastl vector
inline bool KeyLess(const void* a, const void* b)
{
    const unsigned* x = (const unsigned*)a;
    const unsigned* y = (const unsigned*)b;
    if (x[0] != y[0]) return x[0] < y[0];
    if (x[2] != y[2]) return x[2] < y[2];
    return x[1] < y[1];
}
struct ComCtxRef {                 // the planet data reached through cPlanet::+0x13c
    char  mPad00[0xbc];            // +0x000
    EaVec mVecBC;                  // +0x0bc  scanned-key vector A (12-byte records)
    char  mPadC4[0xd0 - 0xc4];     // +0x0c4
    EaVec mVecD0;                  // +0x0d0  scanned-key vector B
    char  mPadD8[0x15c - 0xd8];    // +0x0d8
    EaVec mCivVec;                 // +0x15c  vector<cCivData*>
    char  mPad164[0x184 - 0x164];  // +0x164
    void* mCommCtx;                // +0x184
    void* GetCommContext();        // 0x00ce6950  returns mCommCtx
};
struct NounMgr {                   // SP::NounManager() result
    void* GetCurrentTerrainSphere();   // 0x00f67d90  returns this->+0x74
    void* FUN_00b25f40(int id);        // 0x00b25f40
    void  RemoveNoun(void* noun);      // 0x00b225d0
};
struct CivData {
    EaVec* GetCities();                // 0x005c65e0
    void*  GetResourceKey(void* elem); // 0x00ff0cd0
};
struct ScanNode {                  // rbtree node of ComCtxRef's +0x11c0 map
    char mPad00[8];                // +0x000
    EaMap mMaps[5];                // +0x008 species / +0x20 / +0x38 / +0x50 / +0x68
    char mPad80[0xa2 - 0x80];      // +0x080
    unsigned char mFlagA2;         // +0x0a2
};
struct PlanetCls {                 // SP::cPlanet / current terrain sphere
    char       mPad00[0x13c];      // +0x000
    ComCtxRef* mPData;             // +0x13c
    char       mPad140[0x11c0 - 0x140]; // +0x140
    EaMap      mScanned;           // +0x11c0

    void* FUN_00c73cb0(void* key);                 // +0x20 entry of a scanned map
    void* FUN_00c73cd0(void* key);                 // +0x68 entry of a scanned map
    void  FUN_00c73cf0(int flag);                 // scan the two key vectors into maps[0]
    char  SetSpeciesAsScanned(void* key);
    char  IsSpeciesScanned(void* key);
    void  FUN_00c73f80(void* key);
    void  FUN_00c73ff0();
    char  FUN_00c741a0(void* key);
    void  FUN_00c74210(void* key);
    void  FUN_00c74280();
    char  FUN_00c74400(void* key);
    void  FUN_00c74470(void* key);
    char  FUN_00c744e0(unsigned* key);
    char FUN_00c74550(unsigned* key);
    void  FUN_00c745d0(char flag, void* key);
    void  FUN_00c74650();
    void  FUN_00c74690(void* key, char b2, char b3);
    void  FUN_00c74730(void* k1, void* k2);
    int   FUN_00c73350(int* key);                  // defined in slice s00c72c60
    void* FUN_00c735e0(void* key);                 // defined in slice s00c72c60
};
struct SpatialObj { void func7Ch(int a, float* b); };
struct SpatialDerived : SpatialObj { void FUN_00c74880(int a, float* b); };
struct ArtifactResObj { void* GetKey(int mode); };
// ---- items of slice s00c73cb0 end

// ---- items of slice s00c7c0c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_01694b24;                    // 0x01694b24
extern float g_01694b28;                    // 0x01694b28
extern float g_01694b2c;                    // 0x01694b2c
struct Vec3 { float x, y, z; };
class  cRock;
class  cSpatialObject;
class  cSpatialObjectF;
class  cGameNounManager;
bool  __cdecl FUN_0064f350(void* state, int a, int b);                                                  // 0x0064f350
void* __cdecl FUN_00b3d3b0();                                                                            // 0x00b3d3b0
void* __cdecl FUN_00b3d350();                                                                            // 0x00b3d350
class cGameNounManager {
public:
    void* Find(uint32_t objType, uint32_t id);                          // 0x00b21000
    void* GetAvatar();                                                  // 0x00b1fdb0
};
class cKeyObj {
public:
virtual void k00();
virtual void k04();
virtual void k08();
virtual void k0c();
virtual void k10();
virtual void k14();
virtual void k18();
virtual void k1c();
virtual void k20();
virtual void k24();
virtual void k28();
virtual void k2c();
virtual void k30();
virtual void k34();
virtual void k38();
virtual void k3c();
virtual void k40();
virtual void k44();
virtual void k48();
    virtual int  GetKey();                                              // +0x4c
};
class cFeedbackMgr {
public:
    void find(void* out, void* key);                                    // 0x00e5c780  (on +0x190)
    void FUN_00b2a2a0(void* rock, int flag);                            // 0x00b2a2a0
};
class cPlanetModel {
public:
    void FUN_00b83c40(void* model);                                     // 0x00b83c40
};
struct cSpatialObject {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
    virtual Vec3* GetPosition();                                        // +0x2c
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
    virtual void s70();
    virtual float GetDistance(int a, int b);                            // +0x74
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
    virtual int* GetTag();                                              // +0x98
    virtual void s9c();
    void SetLocalExtents(int a, float b);                               // 0x00c7d020
    void FUN_00c89160(int a, float b);                                  // 0x00c89160
};
struct cSpatialRef { void* mpVtbl; };
struct cSpatialObjectF {
virtual void f00();
virtual void f04();
virtual void f08();
virtual void f0c();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
virtual void f20();
virtual void f24();
virtual void f28();
    virtual void* GetModel(float r);                                    // +0x2c
};
class cRock {
public:
    void*    mpVtbl00;                       // +0x0000
    void*    mpVtbl04;                       // +0x0004
    uint8_t  mPad08[0x28 - 0x08];            // +0x0008
    uint32_t mField28;                       // +0x0028  (definition / noun id)
    void*    mpField2C;                      // +0x002c
    uint8_t  mPad30[0x34 - 0x30];            // +0x0030
    cSpatialRef mSpatial;                    // +0x0034  (secondary vtable object)
    uint8_t  mPad38[0x84 - 0x38];            // +0x0038  (base state up to flags)
    uint32_t mFlags84;                       // +0x0084
    int      mField88;                       // +0x0088
    uint8_t  mPad8C[0xa5 - 0x8c];            // +0x008c
    bool     mBoolA5;                        // +0x00a5
    uint8_t  mPadA6[0x130 - 0xa6];           // +0x00a6
    Vec3     mOriginalPosition;              // +0x0130
    void*    mp13C;                          // +0x013c
    uint32_t mField140;                      // +0x0140

    cRock();                                                            // 0x00c7cde0
    bool InitFromDefinition(int a, int b, int c);                       // 0x00c7cce0
    void UpdateModel();                                                 // 0x00c7ce70
    void FUN_00c7cf50(void* arg);                                       // 0x00c7cf50
    bool FUN_00c7cfc0(void* arg);                                       // 0x00c7cfc0
    // base-class routines reached through ecx=this
    void FUN_00c3f9b0();                                                 // 0x00c3f9b0
    void FUN_00c3f9a0(int a);                                            // 0x00c3f9a0
    void FUN_00c3ff10(void* arg);                                        // 0x00c3ff10
    bool FUN_00c3fc80(int a, int b, int c);                              // 0x00c3fc80
    bool FUN_00b183f0(void* arg);                                        // 0x00b183f0
};
// ---- items of slice s00c7c0c0 end

// ---- items of slice s00c7d120 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_13ec4b8;     // 0x013ec4b8  1e-08f
extern float g_13ef61c;     // 0x013ef61c  -2.0f
extern float g_13f7344;     // 0x013f7344  ~0.7f
extern void* g_1694b70;     // 0x01694b70  current selection / query filter
extern char g_castIdSpatial;   // 0x013f94d4  type-id object passed to Cast
typedef unsigned int   u32;
typedef unsigned char  u8;
struct Vec3_s00c7_d120 {
    float x, y, z;
    Vec3_s00c7_d120() {}
    Vec3_s00c7_d120(const Vec3_s00c7_d120& o) : x(o.x), y(o.y), z(o.z) {}
    Vec3_s00c7_d120(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3_s00c7_d120 operator-(const Vec3_s00c7_d120& o) const { return Vec3_s00c7_d120(x - o.x, y - o.y, z - o.z); }
    Vec3_s00c7_d120 operator+(const Vec3_s00c7_d120& o) const { return Vec3_s00c7_d120(x + o.x, y + o.y, z + o.z); }
};
struct RCObj {
#define V(n) virtual void v##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
    V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    V(40) V(41) V(42) V(43) V(44) V(45)
#undef V
    virtual void* Cast(void* id);
    virtual void AddRef();
    virtual void Release();
};
inline void RefAddRef(void* p) { ((RCObj*)p)->AddRef(); }
inline void RefRelease(void* p) { ((RCObj*)p)->Release(); }
inline void* RefCast(void* p, void* id) { return ((RCObj*)p)->Cast(id); }
inline void* RefCast2(void* p, void* id)
{
    return ((void* (__thiscall*)(void*, void*))(*(void***)p)[0x0c / 4])(p, id);
}
struct AutoRef {
    void* mp;
    AutoRef() : mp(0) {}
    explicit AutoRef(void* p) : mp(p) { if (mp) RefAddRef(mp); }
    AutoRef(const AutoRef& o) : mp(o.mp) { if (mp) RefAddRef(mp); }
    ~AutoRef() { if (mp) RefRelease(mp); }
    AutoRef& operator=(const AutoRef& o)
    {
        if (mp != o.mp) {
            void* old = mp;
            if (o.mp) RefAddRef(o.mp);
            mp = o.mp;
            if (old) RefRelease(old);
        }
        return *this;
    }
};
void* __cdecl  LowerBoundU32(u32* first, u32* last, const u32* key, u8 flag); // 0x00555a20
void* __cdecl  MemCpy(void* dst, const void* src, unsigned n);                // 0x011e0744 (msvcr90 memcpy thunk)
void __cdecl  FreeMem(void* p);                                               // 0x00f47380
struct AutoVec {
    void* begin; void* end; void* cap;
    void dtor();                                // 0x00ad92d0
    void erase(void* first, void* last);        // 0x00b48e40
};
bool __cdecl  FilterCand(void* cand, void* ctx);                              // 0x00c7d090
bool __cdecl  PredC0C130(void* c);                                            // 0x00c0c130
bool __cdecl  PredBFC480(void* c);                                            // 0x00bfc480
void* __cdecl PivotSelect(void** a, void** b, void** c, Vec3_s00c7_d120 v);              // 0x00af9e60
void** __cdecl Partition(void** a, void** b, void* pivot, Vec3_s00c7_d120 v);            // 0x00c7d8a0
void __cdecl  FinalSort(void** a, void** b, void** c, Vec3_s00c7_d120 v);                // 0x00b95fe0
void __cdecl  SortVecImpl(void** a, void** b, Vec3_s00c7_d120 v);                        // 0x00c7dac0
void __cdecl  SortRec(void** a, void** b, int depth, Vec3_s00c7_d120 v);                 // 0x00c7d940
void __cdecl  SortRefs(void** a, void** b, Vec3_s00c7_d120 v);                           // 0x00c7d120
struct cTargetList {
    void** vptr;            // +0x000
    void*  mp04;            // +0x004  raw block ([p-4] holds an allocation count)
    char   pad08[0x10];     // +0x008..+0x017
    u32    m18;             // +0x018
    char   pad1c[0x08];     // +0x01c..+0x023
    u32    m24;             // +0x024
    char   pad28[0x10];     // +0x028..+0x037
    u32*   m38;             // +0x038
    u32*   m3c;             // +0x03c
    u32*   m40;             // +0x040
    char   pad44[0x08];     // +0x044..+0x04b
    u8     m4c;             // +0x04c
    char   pad4d[0x03];     // +0x04d..+0x04f
    u32*   m50;             // +0x050
    u32*   m54;             // +0x054
    u32*   m58;             // +0x058
    char   pad5c[0x08];     // +0x05c..+0x063
    u8     m64;             // +0x064
    char   pad65[0x03];     // +0x065..+0x067
    void** m68;             // +0x068
    void** m6c;             // +0x06c
    void** m70;             // +0x070
    char   pad74[0x08];     // +0x074..+0x07b
    u32    m7c;             // +0x07c
    char   m80[0x200];      // +0x080 inline storage for m68
    void** m280;            // +0x280
    void** m284;            // +0x284
    void** m288;            // +0x288
    char   pad28c[0x08];    // +0x28c..+0x293
    u32    m294;            // +0x294
    char   m298[0x200];     // +0x298 inline storage for m280
    float  m498;            // +0x498
    void*  m49c;            // +0x49c

    cTargetList();                          // 0x00c7d700
    ~cTargetList();                         // 0x00c7d650
    bool Has(u32 key);                      // 0x00c7d6d0
    void* FindTarget(void* ctx);            // 0x00c7d7a0
    void* FindTargetThunk();                // 0x00c7d930
    bool HasKey(void* obj);                 // 0x00c7da70
    void ClearAll();                        // 0x00c7dba0
    void ClearOne();                        // 0x00c7dc20
    bool UpdateTarget(void* target);        // 0x00c7d240
    void Update();                          // 0x00c7dcb0
    bool Write(void* stream);               // 0x00c7dfe0
    bool Read(void* stream);                // 0x00c7e0a0
    void* Get(int* idx);                    // 0x00c7e1a0
};
bool IsTargetable(void* self);              // 0x00c7d200 (cdecl)
bool __stdcall AdvanceIndex(void* p);       // 0x00c7e160
struct DistLess {
    bool __thiscall Less(void* a, void* b) const;
};
static inline void EraseU32Vec(u32** v)
{
    u32* b = v[0];
    u32* e = v[1];
    MemCpy(b, e, (unsigned)((char*)e - (char*)e));
    int count = (int)((char*)e - (char*)b) >> 2;
    int delta = -count;
    delta += delta;
    delta += delta;
    *(int*)((char*)v + 4) += delta;
}
// ---- items of slice s00c7d120 end

// ---- items of slice s00c7e1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CS;
void*   MessageServer_0067dcc0();
void*   SpaceGameGet_01002bd0();
void     __fastcall FUN_00bc3170_00(void*);
void     __fastcall cSPTimer_Start_00bc30f0(void*);
void     __fastcall cSPTimer_Restart_00bc3130(void*);
bool     __fastcall FUN_00c70a70_00(void*);
float    __fastcall FUN_00c71d30_00(void*);
struct SimGame     { void* f5180(int); };
struct CubeMapObj  { void FUN_00c70aa0(float); };
struct CubeCell {                       // 0x54 bytes
    uint32_t pad00[8];                  // 0x00
    uint8_t  m1F9C;                     // 0x20  (absolute 0x1f9c in cell #0x5f)
    uint8_t  pad21[0x33];               // 0x21..0x53
    void FUN_00c7dfe0(void* s);         // 0xc7dfe0
    void FUN_00c7e0a0(void* s);         // 0xc7e0a0
};
struct CubeElem {                       // 0x54 bytes (face grid element, ctor)
    uint32_t m00;                       // 0x00
    uint32_t mVec0[0x30 / 4];           // 0x04
    uint32_t mVec1[0x20 / 4];           // 0x34
};
struct CS {
    union {
        struct {
            uint32_t pad00[0x18 / 4];   // 0x00
            void*    mp18;              // 0x18
            uint32_t pad1C[4];          // 0x1c
            void*    mp2C;              // 0x2c
            uint32_t pad30;             // 0x30
            void*    mp34;              // 0x34
            void*    mp38;              // 0x38
            void*    mp3C;              // 0x3c
            void*    mp40;              // 0x40
            void*    mp44;              // 0x44
            void*    mp48;              // 0x48
            void*    mp4C;              // 0x4c
            CubeCell mCells[0x60];      // 0x50
            uint32_t pad1FD0;           // 0x1fd0
            float    m1FD4;             // 0x1fd4
            float    m1FD8;             // 0x1fd8
            uint32_t pad1FDC[5];        // 0x1fdc
            uint8_t  timer1FF0[0x20];   // 0x1ff0
            uint8_t  timer2010[0x20];   // 0x2010
            uint8_t  m2030;             // 0x2030
            uint8_t  m2031;             // 0x2031
            uint8_t  pad2032[6];        // 0x2032
            uint8_t  timer2038[0x28];   // 0x2038
        } h;
        CubeElem mElems[0x60];          // 0x00 (overlaps h)
    };

    void*     ctor_00c7ea70();
    void      FUN_00c7ead0(int* out);
    void      FUN_00c7e280(void* a);
    void      FUN_00c7e2f0(char b);
    void      FUN_00c7e5d0(int a2, int a3, int a4, int a5, void* cb, int a7, int a8);
    void      FUN_00c7e780(int a2, void* cb, int a4, int a5);
    bool      FUN_00c7e8f0(void* s);
    bool      FUN_00c7e950(void* s);
    bool      FUN_00c7e9b0(int msg, int unk);
    CubeElem* FUN_00c7eaf0(float* p);
    void      FUN_00c7ecb0();
    void      FUN_00c7ed00(int* a, int* b);
    bool      FUN_00c7ee50();
};
// ---- items of slice s00c7e1c0 end

// @ 0x00c73ff0
void PlanetCls::FUN_00c73ff0()
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[1];

    ComCtxRef* pd = mPData;
    int nCiv = (int)((char*)pd->mCivVec.end - (char*)pd->mCivVec.begin) / 4;
    for (int i = 0; i < nCiv; ++i) {
        void* civ = ((void**)pd->mCivVec.begin)[i];
        EaVec* cities = ((CivData*)civ)->GetCities();
        int nCity = (int)((char*)cities->end - (char*)cities->begin) / 4;
        for (int j = 0; j < nCity; ++j) {
            char* city = ((char**)cities->begin)[j];
            int nBuild = (*(int*)(city + 0x80) - *(int*)(city + 0x7c)) / 0x38;
            for (int p = 0; p < nBuild; ++p) {
                void* key = ((CivData*)civ)->GetResourceKey(
                                (void*)(*(int*)(city + 0x7c) + p * 0x38));
                void* r = eastl_lower_bound(m->begin, m->end, key, m->mCmp14);
                if (r == m->end || KeyLess(key, r) || r == (void*)((char*)r + 0x10))
                    r = m->end;
                if (r == m->end)
                    ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(key, 2)))->Notify();
                *(char*)m->insert(key) = 1;
            }
        }
    }
}

// @ 0x00c74210
void PlanetCls::FUN_00c74210(void* key)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[2];
    if (!FUN_00c741a0(key))
        ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(key, 2)))->Notify();
    *(char*)m->insert(key) = 1;
}

// @ 0x00c74280
void PlanetCls::FUN_00c74280()
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[2];

    void* vec = FUN_00b21340(NounManager(), (void*)0x00cd7d10, (void*)0x00d3d420,
                             (void*)0x00ae72d0, (void*)0x00b1e500, (void*)0x018c6de8);
    int n = (*(int*)((char*)vec + 8) - *(int*)((char*)vec + 4)) / 4;
    for (int i = 0; i < n; ++i) {
        unsigned char* d = (unsigned char*)(*(int*)((char*)vec + 4) + i * 4);
        ArtifactResObj* obj = (ArtifactResObj*)(d + 0x34);
        void* key = obj->GetKey(0);
        void* r = eastl_lower_bound(m->begin, m->end, key, m->mCmp14);
        if (r == m->end || KeyLess(key, r) || r == (void*)((char*)r + 0x10))
            r = m->end;
        if (r == m->end)
            ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(obj->GetKey(2), 2)))->Notify();
        *(char*)m->insert(obj->GetKey(0)) = 1;
    }
}

// @ 0x00c74470
void PlanetCls::FUN_00c74470(void* key)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[3];
    if (!FUN_00c74400(key))
        ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(key, 2)))->Notify();
    *(char*)m->insert(key) = 1;
}

// @ 0x00c744e0
char PlanetCls::FUN_00c744e0(unsigned* key)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[4];
    char* end = (char*)m->end;
    char* r = (char*)FUN_00d01260(m->begin, end, key, m->mCmp14);
    if (r == end || *key < *(unsigned*)r || r == r + 8)
        r = end;
    return r == end ? (char)0 : *(char*)(r + 4);
}

// @ 0x00c74650
void PlanetCls::FUN_00c74650()
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls* s = (PlanetCls*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    node->mFlagA2 = 1;
}

// @ 0x00c74880
void SpatialDerived::FUN_00c74880(int a, float* b)
{
    func7Ch(a, b);
    b[1] -= g_13f08c0;
}

// @ 0x00c7cce0
bool cRock::InitFromDefinition(int a, int b, int c)
{
    if (FUN_00c3fc80(a, 0, 0)) {
        Vec3* p = ((cSpatialObject*)&mSpatial)->GetPosition();
        mOriginalPosition = *p;
        return true;
    }
    return false;
}

// @ 0x00c7cde0
cRock::cRock()
{
    FUN_00c3f9b0();
    mpVtbl00 = (void*)0x14732a8;
    mpVtbl04 = (void*)0x1473294;
    mSpatial.mpVtbl = (void*)0x14731d0;
    mOriginalPosition.x = g_01694b24;
    mOriginalPosition.y = g_01694b28;
    mOriginalPosition.z = g_01694b2c;
    mp13C = 0;
    mField140 = 0xffffffff;
    FUN_00c3f9a0(5);
    mField88 = 4;
    mBoolA5 = 0;
    mFlags84 |= 0x200;
}

// @ 0x00c7ce70
void cRock::UpdateModel()
{
    if (!mBoolA5)
        return;

    void* noun = ((cGameNounManager*)NounManager())->Find(0x2a8fb3f, mField28);
    if (noun == 0)
        return;
    if (!FUN_0064f350(*(void**)((char*)noun + 0xc), 0x67364ba, 0))
        return;
    if (!FUN_0064f350(*(void**)((char*)noun + 0xc), 0x3d08e15, 0))
        return;

    cSpatialObject* sp = (cSpatialObject*)&mSpatial;
    Vec3* pos = sp->GetPosition();
    float r = sqrtf(pos->x * pos->x + pos->y * pos->y + pos->z * pos->z) * 0.00390625f;
    r += sp->GetDistance(0x10000000, 0);
    void* model = ((cSpatialObjectF*)sp)->GetModel(r);
    ((cPlanetModel*)FUN_00b3d350())->FUN_00b83c40(model);
}

// @ 0x00c7cf50
void cRock::FUN_00c7cf50(void* arg)
{
    FUN_00c3ff10(arg);
    if (mp13C == 0)
        return;

    void* mgr = FUN_00b3d3b0();
    void* node = 0;
    ((cFeedbackMgr*)((char*)mgr + 0x190))->find(&node, &mp13C);
    if (node == (char*)mgr + 0x194)
        return;
    uint8_t* bits = *(uint8_t**)((char*)node + 0x14);
    if (bits == 0)
        return;
    uint32_t idx = mField140;
    ((uint32_t*)(bits + (idx >> 5) * 4))[0] |= 1u << (idx & 0x1f);
}

// @ 0x00c7cfc0
bool cRock::FUN_00c7cfc0(void* arg)
{
    bool bl = FUN_00b183f0(arg);
    int* tag = ((cSpatialObject*)&mSpatial)->GetTag();
    if (*tag == (int)0xc5bba049 && (mFlags84 & 0x100) == 0) {
        ((cFeedbackMgr*)FUN_00b3d3b0())->FUN_00b2a2a0(this, 1);
        return false;
    }
    if (bl)
        UpdateModel();
    return bl;
}

// @ 0x00c7d020
void cSpatialObject::SetLocalExtents(int a, float b)
{
    FUN_00c89160(a, b);
    ((cRock*)((char*)this - 0x34))->UpdateModel();
}

// @ 0x00c7d090
bool __cdecl FUN_00c7d090(void* p1, int32_t* p2)
{
    switch (p2[0]) {
    case 0:
        return true;
    case 1:
        return ((cKeyObj*)p1)->GetKey() == p2[1];
    case 2:
        return ((int32_t*)p1)[7] == p2[1];
    case 8:
        return p1 == ((cGameNounManager*)NounManager())->GetAvatar();
    default:
        return false;
    }
}

// @ 0x00c7d120
void __cdecl SortRefs(void** begin, void** end, Vec3_s00c7_d120 org)
{
    if (begin == end)
        return;
    for (void** it = begin + 1; it != end; ++it) {
        void* value = *it;
        if (value)
            RefAddRef(value);
        void** j = it;
        while (j != begin && ((DistLess*)&org)->Less(value, j[-1])) {
            void* prev = j[-1];
            void* old  = *j;
            if (prev != old) {
                if (prev)
                    RefAddRef(prev);
                *j = prev;
                if (old)
                    RefRelease(old);
            }
            --j;
        }
        void* old = *j;
        if (value != old) {
            if (value)
                RefAddRef(value);
            *j = value;
            if (old)
                RefRelease(old);
        }
        if (value)
            RefRelease(value);
    }
}

// @ 0x00c7d200
bool __cdecl IsTargetable(void* self)
{
    void* o = *(void**)((char*)self + 0x64);
    if (o) {
        void* c = RefCast2(o, (void*)0x17f243b);
        if (c && c != g_1694b70)
            if (((u32 (__thiscall*)(void*))(*(void***)c)[0x20 / 4])(c) == 0x70703b3)
                return true;
    }
    return false;
}

// @ 0x00c7d240
bool cTargetList::UpdateTarget(void* target)
{
    Vec3_s00c7_d120 p1 = ((Vec3_s00c7_d120* (__thiscall*)(void*))
               ((*(void***)this)[0x14 / 4]))(this)[0];
    Vec3_s00c7_d120 q = ((Vec3_s00c7_d120* (__thiscall*)(void*))
              (*(void***)((void**)((*(void***)this)[0x14 / 4]))[1]))(0)[0];
    (void)q;

    Vec3_s00c7_d120 src = *(Vec3_s00c7_d120*)((char*)&p1);
    float k = m498;
    float inv = 1.0f / sqrtf(src.x * src.x + src.y * src.y + src.z * src.z + g_13ec4b8);
    Vec3_s00c7_d120 p1m(src.x + src.x * inv * k, src.y + src.y * inv * k, src.z + src.z * inv * k);

    Vec3_s00c7_d120 p2 = *(Vec3_s00c7_d120*)((char*)&p1);                 // overwritten below
    p2 = ((Vec3_s00c7_d120* (__thiscall*)(void*))((*(void***)target)[0x2c / 4]))(target)[0];
    void* shape = ((void* (__thiscall*)(void*))((*(void***)target)[0x68 / 4]))(target);
    float r = *(float*)((char*)shape + 0x14) * g_13f7344;
    float travel = ((float (__thiscall*)(void*))((*(void***)target)[0x74 / 4]))(target) * g_13f7344;

    Vec3_s00c7_d120 d = p2 - p1m;
    float inv2 = 1.0f / sqrtf(p2.x * p2.x + p2.y * p2.y + p2.z * p2.z + g_13ec4b8);
    Vec3_s00c7_d120 n2(p2.x * inv2, p2.y * inv2, p2.z * inv2);
    float invd = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + g_13ec4b8);
    Vec3_s00c7_d120 nd(d.x * invd, d.y * invd, d.z * invd);
    Vec3_s00c7_d120 cr(n2.y * nd.z - n2.z * nd.y,
            n2.z * nd.x - n2.x * nd.z,
            n2.x * nd.y - n2.y * nd.x);
    float invc = 1.0f / sqrtf(cr.x * cr.x + cr.y * cr.y + cr.z * cr.z + g_13ec4b8);
    cr.x *= invc; cr.y *= invc; cr.z *= invc;

    p2.x += n2.x * r; p2.y += n2.y * r; p2.z += n2.z * r;

    void* spatial = RefCast(target, (void*)0x17f243b);
    if (!spatial)
        return true;

    g_1694b70 = ((void* (__thiscall*)(void*))((*(void***)this)[0x10 / 4]))(this);
    p2.x += cr.x * travel; p2.y += cr.y * travel; p2.z += cr.z * travel;

    void* hit = 0;
    void* mgr = ((void* (__cdecl*)(void))0x00b3d240)();
    ((void (__thiscall*)(void*, void*, void*, void*, void*, void*, int))
     ((*(void***)mgr)[0x50 / 4]))(mgr, &p2, &p1m, (void*)IsTargetable, &hit, &hit, 1);

    if (hit != spatial && hit != 0) {
        p2.x += cr.x * (travel * g_13ef61c);
        p2.y += cr.y * (travel * g_13ef61c);
        p2.z += cr.z * (travel * g_13ef61c);
        ((void (__thiscall*)(void*))((*(void***)hit)[0x04 / 4]))(hit);
        mgr = ((void* (__cdecl*)(void))0x00b3d240)();
        ((void (__thiscall*)(void*, void*, void*, void*, void*, void*, int))
         ((*(void***)mgr)[0x50 / 4]))(mgr, &p2, &p1m, (void*)IsTargetable, &hit, &hit, 1);
        g_1694b70 = 0;
        if (hit)
            ((void (__thiscall*)(void*))((*(void***)hit)[0x04 / 4]))(hit);
        return false;
    }
    g_1694b70 = 0;
    if (hit)
        ((void (__thiscall*)(void*))((*(void***)hit)[0x04 / 4]))(hit);
    return true;
}

// @ 0x00c7d650
cTargetList::~cTargetList()
{
    void* old = m49c;
    *(void**)this = (void*)0x1473324;
    if (old)
        FreeMem(old);
    m49c = 0;
    ((AutoVec*)((char*)this + 0x280))->dtor();
    ((AutoVec*)((char*)this + 0x68))->dtor();
    if (m50) FreeMem(m50);
    if (m38) FreeMem(m38);
    char* p = (char*)mp04;
    if (p && *(int*)(p - 4)) FreeMem(p);
}

// @ 0x00c7d6d0
bool cTargetList::Has(u32 key)
{
    ((void (__thiscall*)(void*, void**, const u32*))0x00e5c780)(this, (void**)&key, &key);
    return *(void**)&key != (char*)this + 4;
}

// @ 0x00c7d700
cTargetList::cTargetList()
{
    float z = 0.0f;
    vptr = (void**)0x1473324;
    mp04 = 0;
    *(u32*)((char*)this + 0x08) = 0;
    *(u32*)((char*)this + 0x0c) = 0;
    m38 = 0; m3c = 0; m40 = 0;
    m50 = 0; m54 = 0; m58 = 0;
    _ReadWriteBarrier();
    m68 = (void**)((char*)this + 0x80);
    m6c = m68;
    _ReadWriteBarrier();
    m7c = 0;
    m70 = (void**)((char*)m68 + 0x200);
    m280 = (void**)((char*)this + 0x298);
    m284 = m280;
    _ReadWriteBarrier();
    m294 = 0;
    m288 = (void**)((char*)m280 + 0x200);
    *(float*)((char*)this + 0x498) = z;
    m49c = 0;
    m18 = 0;
}

// @ 0x00c7d7a0
void* cTargetList::FindTarget(void* ctx)
{
    void* sel = this ? ((void* (__thiscall*)(void*, void*))
                        (*(void***)this)[0x04 / 4])(this, &g_castIdSpatial) : 0;

    void** it  = m68;
    void** end = m6c;
    void* result = 0;
    for (; it != end; ++it) {
        void* o = *it;
        if (!o)
            continue;
        void* c = RefCast(o, (void*)0x17f243b);
        if (!c)
            continue;
        if (((bool (__thiscall*)(void*))(*(void***)c)[0x2c / 4])(c))
            continue;
        if (!FilterCand(c, ctx))
            continue;
        void* cb = RefCast2(c, &g_castIdSpatial);
        if (cb && ((int (__thiscall*)(void*))0x008e7f80)(cb) == 2)
            continue;
        if (!sel || result)
            return c;
        u32 key = *(u32*)((char*)c + 0x24);
        void* out;
        void** node = ((void** (__thiscall*)(void*, void*, const u32*))0x00e5c780)(
            (char*)sel + 0x0c, &out, &key);
        if (*node != (void**)((char*)sel + 0x10))
            return c;
        result = c;
    }
    return result;
}

// @ 0x00c7d930
void* cTargetList::FindTargetThunk()
{
    return FindTarget((char*)this + 0x28);
}

// @ 0x00c7d940
void __cdecl SortRec(void** a, void** b, int depth, Vec3_s00c7_d120 v)
{
    while ((((char*)b - (char*)a) & ~3) > 0x70 && depth > 0) {
        void** p = (void**)PivotSelect(a, a + (b - a) / 2, b - 1, v);
        void* pivot = *p;
        if (pivot)
            RefAddRef(pivot);
        void** mid = Partition(a, b, pivot, v);
        --depth;
        SortRec(mid, b, depth, v);
        b = mid;
    }
    if (depth == 0)
        FinalSort(a, b, b, v);
}

// @ 0x00c7da70
bool cTargetList::HasKey(void* obj)
{
    u32 key = *(u32*)((char*)obj + 0x24);
    u32* it = (u32*)LowerBoundU32(m38, m3c, &key, m4c);
    if (it == m3c || key < *it || it == it + 1)
        it = m3c;
    return it != m3c;
}

// @ 0x00c7dba0
void cTargetList::ClearAll()
{
    AutoVec* v1 = (AutoVec*)((char*)this + 0x68);
    v1->erase(v1->begin, v1->end);
    EraseU32Vec((u32**)&m38);
    AutoVec* v2 = (AutoVec*)((char*)this + 0x280);
    v2->erase(v2->begin, v2->end);
    EraseU32Vec((u32**)&m50);
}

// @ 0x00c7dc20
void cTargetList::ClearOne()
{
    AutoVec* v = (AutoVec*)((char*)this + 0x280);
    v->erase(v->begin, v->end);
    EraseU32Vec((u32**)&m50);
}

// @ 0x00c7dc70
void __cdecl SortVec(void** a, void** b, Vec3_s00c7_d120 v)
{
    SortVecImpl(a, b, v);
}

// @ 0x00c7dcb0
void cTargetList::Update()
{
    EraseU32Vec((u32**)&m38);
    AutoVec* v1 = (AutoVec*)((char*)this + 0x68);
    v1->erase(v1->begin, v1->end);
    AutoVec* v2 = (AutoVec*)((char*)this + 0x280);
    v2->erase(v2->begin, v2->end);

    void* sel = this ? ((void* (__thiscall*)(void*, void*))
                        ((*(void***)this)[0x04 / 4]))(this, (void*)0x116dd1b) : 0;
    void* list = ((void* (__thiscall*)(void*))0x00c420d0)(sel);
    u32* arr = *(u32**)list;
    int n = (int)(*(u32**)((char*)list + 4) - arr) >> 2;
    for (int i = 0; i < n; ++i) {
        void* o = (void*)arr[i];
        if (!o)
            continue;
        void* c = RefCast(o, (void*)0x17f243b);
        if (!c)
            continue;
        u32 type = ((u32 (__thiscall*)(void*))((*(void***)c)[0x20 / 4]))(c);
        bool add;
        if (type == 0x18eb45e) {
            if (PredC0C130(c))
                continue;
            add = true;
        } else if (type == 0x70703b3) {
            void* cb = RefCast2(c, &g_castIdSpatial);
            add = !PredBFC480(cb);
        } else if (type == 0xf2897537 || type == 0x18c6de8) {
            add = true;
        } else {
            add = false;
        }
        if (add && !UpdateTarget(o))
            continue;

        u32 key = *(u32*)((char*)c + 0x24);
        u32* it = (u32*)LowerBoundU32(m38, m3c, &key, m4c);
        if (it == m3c || key < *it) {
            if (m3c == m40) {
                ((void (__thiscall*)(void*,void*,const u32*))0x005481d0)(&m38, it, &key);
            } else {
                *m3c = key;
                m3c = m3c + 1;
            }
            AutoRef tmp(c);
            if (m6c == m70)
                ((void (__thiscall*)(void*,void*,void**))0x00bab900)(&m68, m6c, &tmp.mp);
            else {
                *m6c = c;
                RefAddRef(c);
                m6c = m6c + 1;
            }
        } else {
            AutoRef tmp(c);
            if (m6c == m70)
                ((void (__thiscall*)(void*,void*,void**))0x00bab900)(&m68, m6c, &tmp.mp);
            else {
                *m6c = c;
                RefAddRef(c);
                m6c = m6c + 1;
            }
        }

        u32* it2 = (u32*)LowerBoundU32(m50, m54, &key, m64);
        if (!(it2 == m54 || key < *it2)) {
            if (it2 == m54) {
                void* pair[2];
                ((void (__thiscall*)(void*,void*,const u32*))0x00554020)(&m50, pair, &key);
                AutoRef tmp(c);
                if (m284 == m288)
                    ((void (__thiscall*)(void*,void*,void**))0x00bab900)(&m280, m284, &tmp.mp);
                else {
                    *m284 = c;
                    RefAddRef(c);
                    m284 = m284 + 1;
                }
            }
        }
    }

    Vec3_s00c7_d120 pos = ((Vec3_s00c7_d120* (__thiscall*)(void*))((*(void***)sel)[0x2c / 4]))(sel)[0];
    SortVecImpl((void**)m68, (void**)m6c, pos);
    SortVecImpl((void**)m280, (void**)m284, pos);
}

// @ 0x00c7e160
bool __stdcall AdvanceIndex(void* p)
{
    int* v = (int*)p;
    int one = 1;
    int zero = 0;
    bool ok = true;
    v[3] += 0x54;
    v[0] += one;
    if (v[0] >= 4) {
        v[1] += one;
        v[0] = zero;
        if (v[1] >= 4) {
            v[2] += one;
            v[1] = zero;
            if (v[2] >= 6) {
                v[3] = zero;
                ok = false;
            }
        }
    }
    return ok;
}

// @ 0x00c7e1a0
void* cTargetList::Get(int* idx)
{
    int n = idx[0] + (idx[1] + idx[2] * 4) * 4;
    return (char*)this + n * 0x54;
}

// @ 0x00c7e280
void CS::FUN_00c7e280(void* a)
{
    h.mp4C = a;
    FUN_00bc3170_00(h.timer1FF0);
    FUN_00bc3170_00(h.timer2010);
    cSPTimer_Start_00bc30f0(h.timer2010);
    void* hTarget = (void*)&h.mp34;
    void* ms = MessageServer_0067dcc0();
    h.mp38 = ms;
    h.mp3C = hTarget;
    h.mp40 = (void*)0x1473354;
    h.mp44 = (void*)1;
    h.mp48 = 0;
    if (ms != 0 && hTarget != 0) {
        ((void(__thiscall*)(void*, void*, uint32_t))(*(void***)ms)[0x24 / 4])(ms, hTarget, 0x44448ed);
    }
}

// @ 0x00c7e2f0
void CS::FUN_00c7e2f0(char b)
{
    h.m2030 = (uint8_t)b;
    h.m2031 = 0;
    if (b != 0) cSPTimer_Restart_00bc3130(h.timer2038);
    else { h.m1FD4 = 0.0f; h.m1FD8 = 0.0f; }
    if (h.mp4C != 0) {
        if (!FUN_00c70a70_00(h.mp4C))
            ((CubeMapObj*)h.mp4C)->FUN_00c70aa0(FUN_00c71d30_00(h.mp4C));
    }
    ((SimGame*)SpaceGameGet_01002bd0())->f5180((int)(b == 0));
}

// @ 0x00c7e490
void __stdcall FUN_00c7e490(int a1, int a2, int p, int a4, char* e)
{
    (void)a1; (void)a2; (void)a4;
    int* pi = (int*)p;
    int* ei = (int*)e;
    if (*e != 0) {
        if (pi[1] == ei[1] && pi[2] == ei[2] && pi[3] == ei[3]) pi[4] = 0;
        if (pi[5] == ei[1] && pi[6] == ei[2] && pi[7] == ei[3]) pi[8] = 0;
        if (pi[9] == ei[1] && pi[10] == ei[2] && pi[11] == ei[3]) pi[12] = 0;
    } else {
        if (pi[0xd] == ei[1] && pi[0xe] == ei[2] && pi[0xf] == ei[3]) pi[0x10] = 0;
        if (pi[0x11] == ei[1] && pi[0x12] == ei[2] && pi[0x13] == ei[3]) pi[0x14] = 0;
    }
}

// @ 0x00c7e530
void __stdcall FUN_00c7e530(int a, int b, int p, int d, int* e)
{
    (void)a; (void)b; (void)d;
    if (*(int*)(p + 0x34) == e[0] && *(int*)(p + 0x38) == e[1] && *(int*)(p + 0x3c) == e[2]) {
        *(int*)(p + 0x34) = e[3]; *(int*)(p + 0x38) = e[4]; *(int*)(p + 0x3c) = e[5];
    }
    if (*(int*)(p + 0x44) == e[0] && *(int*)(p + 0x48) == e[1] && *(int*)(p + 0x4c) == e[2]) {
        *(int*)(p + 0x44) = e[3]; *(int*)(p + 0x48) = e[4]; *(int*)(p + 0x4c) = e[5];
    }
}
