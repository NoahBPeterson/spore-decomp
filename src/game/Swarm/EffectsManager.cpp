// src/game/Swarm/EffectsManager.cpp -- migrated from slice(s) s00a6dfc0, s00a6d020, s00a691c0, s00a6c190 by tools/migrate/rewrite.py
// Object file: Swarm/EffectsManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Swarm/cGlobalParams.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete__(void* p);
extern "C" bool  FUN_00a72f70(int x);
extern float gEC;     // 0x016768ec
extern float gF0;     // 0x016768f0
extern float gF4;     // 0x016768f4
extern float gC4;     // 0x016768c4
extern float gC8;     // 0x016768c8
extern float gCC;     // 0x016768cc
extern const char kFXIdentity4[];   // 0x01676930
extern const char kCameraInstr[];   // 0x01676998
extern const float kMilli;          // 0x013f9428 = 0.001f
#include <string.h>
#include <intrin.h>
#include "EA/Stopwatch.h"
#include "EA/ArgScript/cArguments.h"

// ---- items of slice s00a6c190 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_delete__(void* p);
extern "C" bool  FUN_00a72f70(int x);
extern float gEC;     // 0x016768ec
extern float gF0;     // 0x016768f0
extern float gF4;     // 0x016768f4
extern float gC4;     // 0x016768c4
extern float gC8;     // 0x016768c8
extern float gCC;     // 0x016768cc
extern const char kFXIdentity4[];   // 0x01676930
extern const char kCameraInstr[];   // 0x01676998
extern const float kMilli;          // 0x013f9428 = 0.001f
struct ICollBase {
    virtual void r00();
    virtual void r04();
    virtual ICollBase* r08();
    virtual void r0c();
};
struct IComp {
    virtual void q00();
    virtual void q04();
    virtual void q08(int a, int b, int c);
    virtual void q0c();
    virtual void q10();
    virtual void q14(float f, int i);
    virtual void q18(); virtual void q1c(); virtual void q20(); virtual void q24();
    virtual void q28(); virtual void q2c(); virtual void q30(); virtual void q34();
    virtual void q38(); virtual void q3c();
    virtual void q40();
};
struct IColl7 {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s10(int a, int b, int c, int d);
    virtual void s14(int a, int b, int c);
    virtual void s18();
    virtual long long s1c(int t);
};
struct IDecal {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09();
    virtual void d28(int a, int b);
    virtual void d2c(int a, int b);
    virtual void d30(int a, int b, int c);
    virtual void d34(int a, int b, int c);
};
struct Matrix44 { char m[0x40]; void Ctor(const void* src); };
struct Matrix33 { char m[0x24]; void Assign(const void* src); };
struct FXParams {
    float f0;
    float f4;
    float f8;
    float fc;
    float f10;
    char  b14;
    char  pad15[3];
    float f18;
    int   i1c;
};
struct cEffectsManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(float a, float b);          // 0x40
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual IColl7* v21(int t);                  // 0x54

    char _pad04[0x44 - 0x04];
    ICollBase* m44;                              // 0x44
    ICollBase* m48;                              // 0x48
    int   m4c;                                   // 0x4c
    float m50;                                   // 0x50
    int   m54;                                   // 0x54
    float m58;                                   // 0x58
    float m5c;                                   // 0x5c
    float m60;                                   // 0x60
    float m64;                                   // 0x64
    unsigned m68;                                // 0x68
    char _pad6c[0xd0 - 0x6c];
    float md0;                                   // 0xd0
    float md4;                                   // 0xd4
    char _padD8[0x1f0 - 0xd8];
    void* m1f0;                                  // 0x1f0
    ICollBase* m1f4[20];                         // 0x1f4
    IComp* m244;                                 // 0x244

    void  DoUpdate(unsigned a, unsigned b);      // 0x00a6c8f0
    void  SetFlag(int index, char value);        // 0x00a6c940
    bool  GetFlag(int index);                    // 0x00a6c970
    void  SetParams(const FXParams* p);          // 0x00a6c9b0
    void  SetResources(ICollBase* p);            // 0x00a6ca10
    void  SetComponent(ICollBase* p, int type); // 0x00a6ca90
    void* GetComponent(int type);                // 0x00a6cb10
    void  Comp8(int a, int b, int c);            // 0x00a6cb30
    void  Comp14(float f, int i);                // 0x00a6cb70
    void  ResetState();                          // 0x00a6cba0
    void  SetComponent244(IComp* p);             // 0x00a6cbc0
    void* LookupA(int a, int idx, int type);     // 0x00a6cc20
    void* LookupB(int a, int idx, int type);     // 0x00a6cc50
    void  Decal30(int a, int b, int c);          // 0x00a6cc80
    void  Decal28(int a, int b);                 // 0x00a6cca0
    void  Coll10(int a, int b, int c, int d);    // 0x00a6ccc0
    void  Decal34(int a, int b, int c);          // 0x00a6cd10
    void  Decal2c(int a, int b);                 // 0x00a6cd30
    void  Coll14(int a, int b, int c);           // 0x00a6cd50
    long long GetS1c(int t);                     // 0x00a6cd70
};
struct cGlobalParams {
    float mParticleDensity;          // 0x00
    float mParticleScale;            // 0x04
    int   mParticleMultThreshold;    // 0x08
    float mMaxParticleSize;          // 0x0c
    int   mMaxParticles;             // 0x10
    int   mMaxEffects;               // 0x14
    int   mMaxDistributeSamples;     // 0x18
    Matrix44 mProjectionMatrix;      // 0x1c
    Matrix33 mCameraOrientation;     // 0x5c
    float mCameraTranslation[3];     // 0x80
    float mLODPosition[3];           // 0x8c
    float mCursorRayPoint[3];        // 0x98
    float mCursorRayDirection[3];    // 0xa4
    char  mCursorRayAvailable;       // 0xb0
    char  _padB1[3];
    int   mButtonFlags;              // 0xb4
    int   mButtonChangedFlags;       // 0xb8
    float mWindDirection[3];         // 0xbc
    float mWindPointStrength;        // 0xc8
    float mWindPoint[3];             // 0xcc
    float mGravityDirection[3];      // 0xd8
    float mGravityPointStrength;     // 0xe4
    float mGravityPoint[3];          // 0xe8
    float mSunDirection[3];          // 0xf4
    float mSunPointStrength;         // 0x100
    float mSunPoint[3];              // 0x104
    char  mShowBoundingBoxes;        // 0x110
    char  mShowSurfaces;             // 0x111
    char  mShowEffects;              // 0x112
    char  _pad113;
    float mShowEffectsScale;         // 0x114
    char  mDisableParticleAlpha;     // 0x118
    char  mDrawParticles;            // 0x119
    char  mDrawMeshes;               // 0x11a
    char  mDrawModels;               // 0x11b
    char  mDrawDecals;               // 0x11c

    cGlobalParams();
};
struct GmeRefCount {
    int ScalarDeletingDestructor(unsigned flags);
};
// ---- items of slice s00a6c190 end

// ---- items of slice s00a691c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefObject {
    virtual void Destroy(int flag);   // vtable slot 0
    int mnRefCount;                   // +0x04
};
struct RefVecSlot {
    RefObject** mpBegin;      // +0x00
    RefObject** mpEnd;        // +0x04
    RefObject** mpCapacity;   // +0x08
    uint32_t    mx0c;         // +0x0c
    uint32_t    mx10;         // +0x10
};
struct RegRec24 {
    void*    pf0;        // +0x00
    void*    pf4;        // +0x04
    uint32_t pad8;       // +0x08
    uint16_t w0c;        // +0x0c
    uint16_t padE;       // +0x0e
    uint32_t pad10[5];   // +0x10
};
extern RegRec24 g_RegA[32];        // 0x01675a00
struct Ctx {
    int  DispatchLookup(uint32_t key, uint32_t* out, int count);   // 0x00a691c0
    void ForEachRegA(uint32_t arg);                                // 0x00a69310
    void ForEachRegB(uint32_t arg);                                // 0x00a69380
    bool Serialize(void* stream);                                  // 0x00a69630
};
// ---- items of slice s00a691c0 end

// ---- items of slice s00a6d020 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_011e073e(void* dst, int val, int size);                    // 0x11e073e
extern "C" void* EAAllocate(unsigned size, const char* file, int a, int b, int c, int d); // 0xf473a0
extern "C" void  MakeCaseInsensitive(void* s);                                  // 0x8409b0
extern "C" __declspec(dllimport) int sprintf(char*, const char*, ...);          // 0x13cc4a0
extern "C" __declspec(dllimport) int isdigit(int);                              // 0x13cc4cc
extern "C" __declspec(dllimport) unsigned long strtoul(const char*, char**, int); // 0x13cc4f8
extern "C" __declspec(dllimport) size_t strlen(const char*);
extern int gTblB[];        // 0x1675eb0
extern int gTblBEnd;       // 0x16766b0
extern int gTblA[];        // 0x16759f8
extern int gTblAEnd;       // 0x1675e78
extern const char  kStatsFmt[];     // 0x1455b10
extern const char  kDensityFmt[];   // 0x1455b00
extern const char  kSwarmSurface[]; // 0x1455c48
extern const char  kSwarm[];        // 0x13f1fdc
extern const float kOne;            // 0x1485720
extern const float kZero;           // 0x1485378
extern const float kPoint9;         // 0x13ec4b4
extern const float kPoint4;         // 0x13ec434
extern char kVtA2c[];    // 0x1455a2c
extern char kVtA64[];    // 0x1455a64
extern char kVtA98[];    // 0x1455a98
extern char kVtAcc[];    // 0x1455acc
extern char kVtRel[];    // 0x1455a60
extern char kVtEffMgr[]; // 0x1455b80
extern char kVtRefCnt[]; // 0x1455b7c
extern char kVtGme[];    // 0x13ef094
struct cEffectsWorld {
    cEffectsWorld* ctor(void* mgr, float* density);   // 0xa70780
};
struct IDrawableCall {
    bool UseCollision(unsigned id, unsigned c);       // 0x950ea0
};
struct VectorObj {
    void dtor();                                       // 0xae6970
};
struct HashOps {
    void DoFreeNodes(void** bucket, int count);        // 0x961d60
};
namespace EA {
namespace Swarm {
struct EString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void* mpAlloc;      // +0x0c
    void assign(const char* first, const char* last);
};
}
}
namespace EA {
namespace Swarm {
struct HashNode { int mKey; void* mValue; HashNode* mpNext; };
}
}
namespace EA {
namespace Swarm {
struct HashIter { HashNode* mpNode; HashNode** mpBucket; };
}
}
namespace EA {
namespace Swarm {
struct HashTable {
    void*       mpF0;             // +0x00
    HashNode**  mpBucketArray;    // +0x04
    int         mnBucketCount;    // +0x08
    int         mnElementCount;   // +0x0c
    int         mPad[4];          // +0x10
    HashIter* find(HashIter* out, const unsigned* key);   // 0x645ed0
    void**   f(const void* key);                     // 0x962100
    HashIter erase(const HashIter& it);              // 0xadc970
};
}
}
namespace EA {
namespace Swarm {
struct PairKey { int a; int b; };
}
}
namespace EA {
namespace Swarm {
struct CompNode { int f00; int f04; int mComp; };     // mComp at +0x08
}
}
namespace EA {
namespace Swarm {
struct CompIter { CompNode* mpNode; void* mpBucket; };
}
}
namespace EA {
namespace Swarm {
struct CompMap {
    void*      mpF0;             // +0x00
    CompNode** mpBucketArray;    // +0x04
    int        mnBucketCount;    // +0x08
    CompIter*  find(CompIter* out, const PairKey* key);   // 0xa7bf40
};
}
}
namespace EA {
namespace Swarm {
struct IRefCounted {
    virtual void AddRef();     // 0x00
    virtual void Release();    // 0x04
};
}
}
namespace EA {
namespace Swarm {
struct IComponent : IRefCounted {
    virtual void v08();                       // 0x08
    virtual void Release2();                  // 0x0c
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void v1c();                       // 0x1c
};
}
}
namespace EA {
namespace Swarm {
struct ICollection : IRefCounted {
    virtual char v08();                       // 0x08
    virtual void v0c();                       // 0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual int  v2c(int a, int b, int c);    // 0x2c
virtual void v30();
virtual void v34();
virtual void v38();
    virtual char v3c(int a, const char* b);   // 0x3c

    void FUN_00a69380(void* mgr);             // 0xa69380
};
}
}
namespace EA {
namespace Swarm {
struct IValue : IRefCounted {
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual char v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54(float, float, void*);

    void FUN_00a719c0(int i);                 // 0xa719c0
    void FUN_00a72010(int i);                 // 0xa72010
};
}
}
namespace EA {
namespace Swarm {
struct IWorld : IRefCounted {
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void v1c(void* p);                // 0x1c
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual void v4c();                       // 0x4c
};
}
}
namespace EA {
namespace Swarm {
struct IRenderer : IRefCounted {
    virtual void v08(float* p);               // 0x08
};
}
}
namespace EA {
namespace Swarm {
struct Stopwatch {
    unsigned   mnStartLo;     // +0x00
    unsigned   mnStartHi;     // +0x04
    unsigned   mnElapsedLo;   // +0x08
    unsigned   mnElapsedHi;   // +0x0c
    int        mnUnits;       // +0x10
    float      mfCoeff;       // +0x14
    long long  GetElapsedTimeFloat();   // 0x93a3a0
};
}
}
namespace EA {
namespace Swarm {
struct ResInfo {
    int f00, f04, f08, f0c, f10, f14, f18, f1c;
    int f20, f24, f28, f2c, f30, f34, f38, f3c;
    int f40, f44, f48;
};
}
}
namespace EA {
namespace Swarm {
struct InitParams {
    float a;        // +0x00
    float b;        // +0x04
    float c;        // +0x08
    float d;        // +0x0c
    float e;        // +0x10
    char  f;        // +0x14
    char  pad[3];
    float g;        // +0x18
    int   h;        // +0x1c
};
}
}
namespace EA {
namespace Swarm {
class cEffectsManager_s00a6_d020 { public:
    void*      mpVtbl;                 // +0x00
    void*      mpRefVtbl;              // +0x04
    int        m08;                    // +0x08
    char       mInitialized;           // +0x0c
    char       _pad0d[3];
    Stopwatch  mTimer;                 // +0x10
    float      mDampedSimTimeInMS;     // +0x28
    ICollection** mCollectionsBegin;   // +0x2c
    ICollection** mCollectionsEnd;     // +0x30
    void*      m34;                    // +0x34
    void*      m38;                    // +0x38
    void*      m3c;                    // +0x3c
    IRenderer* mRenderer;              // +0x40
    IRefCounted* m44;                  // +0x44
    IRefCounted* m48;                  // +0x48
    int        m4c;                    // +0x4c
    float      m50;                    // +0x50
    int        m54;                    // +0x54
    float      m58;                    // +0x58
    float      m5c;                    // +0x5c
    float      m60;                    // +0x60
    float      m64;                    // +0x64
    int        m68;                    // +0x68
    int        m6c;                    // +0x6c
    int        m70;                    // +0x70
    ResInfo    mResInfo;               // +0x74
    EString    mStatsStr;              // +0xc0
    float      mDensity;               // +0xd0
    int        md4;                    // +0xd4
    char       _padD8[0xe0 - 0xd8];
    int        mE0;                    // +0xe0
    int        mE4;                    // +0xe4
    int        mE8;                    // +0xe8
    char       _padEC[0x1f0 - 0xec];
    IComponent* m1f0;                  // +0x1f0
    IComponent* m1f4[12];              // +0x1f4
    HashTable  mHash;                  // +0x224
    IWorld*    mWorld;                 // +0x244
    EString    mName;                  // +0x248

    void      DoUpdate(float a, float b);                       // 00a6d020
    bool      FUN_00a6d3b0(ICollection* p);                     // 00a6d3b0
    void      FUN_00a6d480();                                   // 00a6d480
    bool      FUN_00a6d4e0(int a, int b);                       // 00a6d4e0
    int       FUN_00a6d5a0(int a, int b, int c, int d);         // 00a6d5a0
    const char* GetStatsString();                               // 00a6d640 0x00a6d640
    bool      GetEffectInfo(int a, const char* name);           // 00a6d730 0x00a6d730
    unsigned  FUN_00a6d7b0(int a, int b);                       // 00a6d7b0
    unsigned  FUN_00a6d840(const char* s);                      // 00a6d840
    bool      Shutdown();                                       // 00a6d950 0x00a6d950
    bool      FUN_00a6da80(unsigned key);                       // 00a6da80
    bool      FUN_00a6db00(int a, int b, unsigned c);           // 00a6db00
    ~cEffectsManager_s00a6_d020();                                         // 00a6db40
    bool      Init();                                           // 00a6dc60 0x00a6dc60
    void      SetRenderer(IRenderer* p);                        // 00a6ded0 0x00a6ded0
    IWorld*   CreateWorld(unsigned id, unsigned b);             // 00a6df30
};
}
}
namespace EA {
namespace Swarm {
typedef void (__thiscall *VfnA8)(void* self, InitParams* params);
}
}
namespace EA {
namespace Swarm {
typedef void (__thiscall *Vfn78)(void* self, unsigned hash, int zero, void* obj);
}
}
namespace EA {
namespace Swarm {
inline HashNode* HashFirst(HashNode**& b)
{
    HashNode* n = *b;
    if (n == 0) {
        ++b;
        if (*b == 0) {
            do { ++b; } while (*b == 0);
        }
        n = *b;
    }
    return n;
}
}
}
namespace EA {
namespace Swarm {
inline void HashNext(HashNode**& b, HashNode*& node)
{
    node = node->mpNext;
    if (node == 0) {
        do {
            ++b;
            node = *b;
        } while (node == 0);
    }
}
}
}
namespace EA {
namespace Swarm {
struct CopyRec {
    EString a;      // +0x00
    EString b;      // +0x10
    void*   ref;    // +0x20
};
}
}
// ---- items of slice s00a6d020 end

// ---- items of slice s00a6dfc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  v0093a560(void* sw, int units, bool b);                    // 0x93a560 Stopwatch ctor
extern "C" void  v00a6cdb0(void* p);                                        // 0xa6cdb0 cGlobalParams ctor
extern "C" void  v0011e073e(void* block, int val, int size);                // 0x11e073e operator new[]
extern "C" void  v00a0a360(void* vec, void* a, void* b);                    // 0xa0a360 SL71::v0a360
extern "C" void  v00a69310(void* obj);                                      // 0xa69310 collection refresh
extern "C" void  v00a72060(void* core, int filter);                         // 0xa72060
extern const float kTwo;            // 0x1470f1c 2.0f
extern void* gEmptyString16;        // 0x1667bac
namespace EA {
namespace Swarm {
struct UIntVec {
    unsigned* mpBegin;      // +0x00
    unsigned* mpEnd;        // +0x04
    unsigned* mpCapacity;   // +0x08
    void reserve(unsigned n);                          // 0x004e0880
    void DoInsertValue(unsigned* pos, const unsigned* v); // 0x004558a0
};
}
}
namespace EA {
namespace Swarm {
struct VecBase {
    char*  mpBegin;         // +0x00
    char*  mpEnd;           // +0x04
    char*  mpCapacity;      // +0x08
    char*  Append(void* first, void* last);          // 0xa6d8c0
    void   FixTail(char* p);                         // 0x7e2be0
};
}
}
namespace EA {
namespace Swarm {
struct ICollection_s00a6_dfc0 {
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};
}
}
namespace EA {
namespace Swarm {
class cEffectsManager_s00a6_dfc0 { public:
    char      _pad00[0x2c];
    void**    mpCollBegin;          // +0x2c (vector of ICollection*)
    void**    mpCollEnd;            // +0x30
    void**    mpCollCapacity;       // +0x34
    char      _pad38[0x224 - 0x38];
    void*     mpHashF0;             // +0x224
    void**    mpBuckets;            // +0x228 (HashTable.mpBucketArray)
    int       mnBucketCount;        // +0x22c
    int       mnElementCount;       // +0x230
    void      FUN_00a6dfc0(void* vec);      // 00a6dfc0
    bool      FUN_00a6e050(void* p);        // 00a6e050
    void      FUN_00a6e320(VecBase* vec, void* b, void* c);  // 00a6e320
    void      FUN_00a6e3e0(VecBase* vec, void* b);           // 00a6e3e0
    void*     FUN_00a6e4b0();                                // 00a6e4b0
};
}
}
// ---- items of slice s00a6dfc0 end

// @ 0x00a69310
void Ctx::ForEachRegA(uint32_t arg)
{
    char* self = (char*)this;
    int k = 0;
    RegRec24* rec = g_RegA;
    do {
        if (rec->pf0 != 0) {
            RefVecSlot* slot = (RefVecSlot*)(*(char**)(self + 0x20) + k);
            int n = (int)(slot->mpEnd - slot->mpBegin);
            int i = 0;
            if (n > 0) {
                do {
                    ((void(__cdecl*)(RefObject*, uint32_t))rec->pf0)(slot->mpBegin[i], arg);
                    ++i;
                } while (i < n);
            }
        }
        ++rec;
        k += 0x14;
    } while (rec < (RegRec24*)0x01675e80);
}

// @ 0x00a69380
void Ctx::ForEachRegB(uint32_t arg)
{
    char* self = (char*)this;
    int k = 0;
    RegRec24* rec = g_RegA;
    do {
        if (rec->pf4 != 0) {
            RefVecSlot* slot = (RefVecSlot*)(*(char**)(self + 0x20) + k);
            int n = (int)(slot->mpEnd - slot->mpBegin);
            int i = 0;
            if (n > 0) {
                do {
                    ((void(__cdecl*)(RefObject*, uint32_t))rec->pf4)(slot->mpBegin[i], arg);
                    ++i;
                } while (i < n);
            }
        }
        ++rec;
        k += 0x14;
    } while (rec < (RegRec24*)0x01675e84);
}

// @ 0x00a6c8f0
void cEffectsManager::DoUpdate(unsigned a, unsigned b)
{
    v16((float)a * kMilli, (float)b * kMilli);
}

// @ 0x00a6c940
void cEffectsManager::SetFlag(int index, char value)
{
    if (index < 0x20) {
        unsigned mask = 1u << index;
        if (value)
            m68 |= mask;
        else
            m68 &= ~mask;
    }
}

// @ 0x00a6c970
bool cEffectsManager::GetFlag(int index)
{
    if (index < 0x20)
        return (m68 & (1u << index)) != 0;
    return false;
}

// @ 0x00a6c9b0
void cEffectsManager::SetParams(const FXParams* p)
{
    m58 = p->f0;
    m5c = p->f8;
    md4 = p->f4;
    m60 = p->fc;
    m64 = p->f10;
    m4c = (p->b14 == 0);
    m50 = p->f18;
    m54 = p->i1c;
}

// @ 0x00a6ca10
void cEffectsManager::SetResources(ICollBase* p)
{
    ICollBase* c6 = m44;
    if (p != c6) {
        if (p)
            p->r00();
        m44 = p;
        if (c6)
            c6->r04();
    }
    if (p != 0) {
        ICollBase* q = p->r08();
        ICollBase* c7 = m48;
        if (q != c7) {
            if (q)
                q->r00();
            m48 = q;
            if (c7)
                c7->r04();
        }
    }
    else {
        ICollBase* c7 = m48;
        if (c7) {
            m48 = 0;
            c7->r04();
        }
    }
}

// @ 0x00a6ca90
void cEffectsManager::SetComponent(ICollBase* p, int type)
{
    if (type >= 0) {
        ICollBase* old = m1f4[type];
        if (p != old) {
            if (p)
                p->r08();
            m1f4[type] = p;
            if (old)
                old->r0c();
        }
    }
    else {
        ICollBase* old = (ICollBase*)m1f0;
        if (p != old) {
            if (p)
                p->r08();
            m1f0 = p;
            if (old)
                old->r0c();
        }
    }
}

// @ 0x00a6cb10
void* cEffectsManager::GetComponent(int type)
{
    if (type >= 0) {
        void* r = m1f4[type];
        if (r)
            return r;
    }
    return m1f0;
}

// @ 0x00a6cb30
void cEffectsManager::Comp8(int a, int b, int c)
{
    m244->q08(a, b, c);
    _ReadWriteBarrier();
}

// @ 0x00a6cb70
void cEffectsManager::Comp14(float f, int i)
{
    m244->q14(f, i);
}

// @ 0x00a6cba0
void cEffectsManager::ResetState()
{
    md0 = m58;
    m244->q40();
}

// @ 0x00a6cbc0
void cEffectsManager::SetComponent244(IComp* p)
{
    IComp* old;
    if (p != 0) {
        old = m244;
        if (p == old)
            return;
    }
    else {
        p = (IComp*)v21(0);
        old = m244;
        if (p == old)
            return;
        if (p == 0)
            goto done;
    }
    p->q00();
done:
    m244 = p;
    if (old)
        old->q04();
}

// @ 0x00a6cc20
void* cEffectsManager::LookupA(int a, int idx, int type)
{
    int* table = *(int**)((char*)this + 0x2c);
    int  obj = *(int*)((char*)table + type * 4);
    int  arr = *(int*)((char*)obj + 0xc);
    int* e = (int*)(arr + a * 0x14);
    if (e[0] == e[1])
        return 0;
    return *(void**)(e[0] + idx * 4);
}

// @ 0x00a6cc50
void* cEffectsManager::LookupB(int a, int idx, int type)
{
    int* table = *(int**)((char*)this + 0x2c);
    int  obj = *(int*)((char*)table + type * 4);
    int  arr = *(int*)((char*)obj + 0x20);
    int* e = (int*)(arr + a * 0x14);
    if (e[0] == e[1])
        return 0;
    return *(void**)(e[0] + idx * 4);
}

// @ 0x00a6cc80
void cEffectsManager::Decal30(int a, int b, int c)
{
    ((IDecal*)m44)->d30(a, b, c);
    _ReadWriteBarrier();
}

// @ 0x00a6cca0
void cEffectsManager::Decal28(int a, int b)
{
    ((IDecal*)m44)->d28(a, b);
    _ReadWriteBarrier();
}

// @ 0x00a6ccc0
void cEffectsManager::Coll10(int a, int b, int c, int d)
{
    IColl7* p = (IColl7*)m48;
    if (p) {
        p->s10(a, b, c, d);
        _ReadWriteBarrier();
    }
}

// @ 0x00a6cd10
void cEffectsManager::Decal34(int a, int b, int c)
{
    ((IDecal*)m44)->d34(a, b, c);
    _ReadWriteBarrier();
}

// @ 0x00a6cd30
void cEffectsManager::Decal2c(int a, int b)
{
    ((IDecal*)m44)->d2c(a, b);
    _ReadWriteBarrier();
}

// @ 0x00a6cd50
void cEffectsManager::Coll14(int a, int b, int c)
{
    IColl7* p = (IColl7*)m48;
    if (p) {
        p->s14(a, b, c);
        _ReadWriteBarrier();
    }
}

// @ 0x00a6cd70
long long cEffectsManager::GetS1c(int t)
{
    IColl7* p = (IColl7*)m48;
    if (p)
        return p->s1c(t);
    union {
        long long value;
        struct { unsigned low, high; } words;
    } missing;
    missing.words.low = ~0u;
    missing.words.high = ~0u;
    return missing.value;
}

// @ 0x00a6cd90
bool __stdcall RangeNotEmpty(void* p)
{
    int a = *(int*)((char*)p + 0x10);
    if (a != *(int*)((char*)p + 0x14))
        return FUN_00a72f70(a);
    return false;
}

// @ 0x00a6cdb0
cGlobalParams::cGlobalParams()
{
    mParticleDensity = 1.0f;
    mParticleScale = 1.0f;
    mParticleMultThreshold = 0x14;
    mMaxParticleSize = 1000.0f;
    mMaxParticles = 0;
    mMaxEffects = 0;
    mMaxDistributeSamples = 0;
    mProjectionMatrix.Ctor(&kFXIdentity4);
    mCameraOrientation.Assign(&kCameraInstr);
    mCameraTranslation[0] = 0.0f;
    mCameraTranslation[1] = 0.0f;
    mCameraTranslation[2] = 0.0f;
    mLODPosition[0] = 0.0f;
    mLODPosition[1] = 0.0f;
    mLODPosition[2] = 0.0f;
    mCursorRayPoint[0] = 0.0f;
    mCursorRayPoint[1] = 0.0f;
    mCursorRayPoint[2] = 0.0f;
    mCursorRayDirection[0] = 0.0f;
    mCursorRayDirection[1] = 0.0f;
    mCursorRayDirection[2] = 1.0f;
    mCursorRayAvailable = 0;
    mButtonFlags = 0;
    mButtonChangedFlags = 0;
    mWindDirection[0] = gEC;
    mWindDirection[1] = gF0;
    mWindDirection[2] = gF4;
    mWindPointStrength = 0.0f;
    mWindPoint[0] = gEC;
    mWindPoint[1] = gF0;
    mWindPoint[2] = gF4;
    mGravityDirection[0] = 0.0f;
    mGravityDirection[1] = 0.0f;
    mGravityDirection[2] = -1.0f;
    mGravityPointStrength = 0.0f;
    mGravityPoint[0] = gEC;
    mGravityPoint[1] = gF0;
    mGravityPoint[2] = gF4;
    mSunDirection[0] = gC4;
    mSunDirection[1] = gC8;
    mSunDirection[2] = gCC;
    mSunPointStrength = 0.0f;
    mSunPoint[0] = gC4;
    mSunPoint[1] = gC8;
    mSunPoint[2] = gCC;
    mShowBoundingBoxes = 0;
    mShowSurfaces = 0;
    mShowEffects = 0;
    mShowEffectsScale = 0.1f;
    mDisableParticleAlpha = 0;
    mDrawParticles = 1;
    mDrawMeshes = 1;
    mDrawModels = 1;
    mDrawDecals = 1;
}

// @ 0x00a6d000
int GmeRefCount::ScalarDeletingDestructor(unsigned flags)
{
    *(void**)((char*)this + 4) = (void*)0x013ef094;
    if (flags & 1)
        operator_delete__(this);
    return (int)this;
}

// @ 0x00a6d3b0
namespace EA { namespace Swarm {
bool cEffectsManager_s00a6_d020::FUN_00a6d3b0(ICollection* p)
{
    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        if (mCollectionsBegin[i] == p) {
            p->AddRef();
            p->FUN_00a69380(this);
            ICollection* old = mCollectionsBegin[i];
            mCollectionsBegin[i] = 0;
            if (old != 0)
                old->Release();

            HashNode** bucket = mHash.mpBucketArray;
            HashNode* node = HashFirst(bucket);
            HashNode* end = mHash.mpBucketArray[mHash.mnBucketCount];
            while (node != end) {
                ((IValue*)node->mValue)->FUN_00a719c0(i);
                HashNext(bucket, node);
            }
            p->Release();
            return true;
        }
    }
    return false;
}
}}  // namespace EA::Swarm

// @ 0x00a6d480
namespace EA { namespace Swarm {
void cEffectsManager_s00a6_d020::FUN_00a6d480()
{
    HashNode** bucket = mHash.mpBucketArray;
    HashNode* node = HashFirst(bucket);
    HashNode* end = mHash.mpBucketArray[mHash.mnBucketCount];
    while (node != end) {
        ((IValue*)node->mValue)->v38();
        HashNext(bucket, node);
    }
}
}}  // namespace EA::Swarm

// @ 0x00a6d4e0
namespace EA { namespace Swarm {
bool cEffectsManager_s00a6_d020::FUN_00a6d4e0(int a, int b)
{
    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        ICollection* coll = mCollectionsBegin[i];
        if (coll != 0) {
            CompMap* map = (CompMap*)((char*)coll + 0x68);
            PairKey key;
            key.a = a;
            key.b = b;
            CompIter it;
            map->find(&it, &key);
            if (it.mpNode != map->mpBucketArray[map->mnBucketCount])
                return true;
        }
    }
    return false;
}
}}  // namespace EA::Swarm

// @ 0x00a6d5a0
namespace EA { namespace Swarm {
int cEffectsManager_s00a6_d020::FUN_00a6d5a0(int a, int b, int c, int d)
{
    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        ICollection* coll = mCollectionsBegin[i];
        if (coll != 0) {
            CompMap* map = (CompMap*)((char*)coll + 0x68);
            PairKey key;
            key.a = a;
            key.b = b;
            CompIter it;
            map->find(&it, &key);
            if (it.mpNode != map->mpBucketArray[map->mnBucketCount] &&
                it.mpNode->mComp >= 0)
                return coll->v2c(it.mpNode->mComp, c, d);
        }
    }
    return 0;
}
}}  // namespace EA::Swarm

// @ 0x00a6d640
namespace EA { namespace Swarm {
const char* cEffectsManager_s00a6_d020::GetStatsString()
{
    char buf[2048];
    sprintf(buf, kStatsFmt, (double)mDampedSimTimeInMS,
            mResInfo.f00, mResInfo.f04, mResInfo.f08,
            mResInfo.f14, mResInfo.f10, mResInfo.f1c, mResInfo.f18,
            mResInfo.f24, mResInfo.f20, mResInfo.f28, mResInfo.f30, mResInfo.f2c);
    if (mDensity < kOne) {
        char* e = buf + strlen(buf);
        sprintf(e, kDensityFmt, (double)mDensity);
    }
    mStatsStr.assign(buf, buf + strlen(buf));
    return mStatsStr.mpBegin;
}
}}  // namespace EA::Swarm

// @ 0x00a6d730
namespace EA { namespace Swarm {
bool cEffectsManager_s00a6_d020::GetEffectInfo(int a, const char* name)
{
    mName.assign(name, name + strlen(name));
    MakeCaseInsensitive(&mName);

    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        ICollection* c = mCollectionsBegin[i];
        if (c != 0) {
            if (c->v3c(a, mName.mpBegin) != 0)
                return true;
        }
    }
    return false;
}
}}  // namespace EA::Swarm

// @ 0x00a6d7b0
namespace EA { namespace Swarm {
unsigned cEffectsManager_s00a6_d020::FUN_00a6d7b0(int a, int b)
{
    PairKey key;
    CompIter it;
    int n = (int)(mCollectionsEnd - mCollectionsBegin);
    for (int i = 0; i < n; ++i) {
        ICollection* coll = mCollectionsBegin[i];
        if (coll != 0) {
            CompMap* map = (CompMap*)((char*)coll + 0x68);
            key.a = a;
            key.b = b;
            map->find(&it, &key);
            if (it.mpNode != map->mpBucketArray[map->mnBucketCount] &&
                it.mpNode->mComp >= 0)
                return ((unsigned)i << 24) | (unsigned)it.mpNode->mComp;
        }
    }
    return 0xffffffffu;
}
}}  // namespace EA::Swarm

// @ 0x00a6d840
namespace EA { namespace Swarm {
unsigned cEffectsManager_s00a6_d020::FUN_00a6d840(const char* s)
{
    if (s == 0)
        return (unsigned)(size_t)mWorld;
    if (isdigit((unsigned char)*s) != 0) {
        unsigned key = (unsigned)strtoul(s, 0, 0);
        HashTable* h = &mHash;
        HashIter it;
        HashIter* r = h->find(&it, &key);
        if (r->mpNode != h->mpBucketArray[h->mnBucketCount])
            return (unsigned)(size_t)r->mpNode->mValue;
    }
    return 0;
}
}}  // namespace EA::Swarm

// @ 0x00a6d8c0
namespace EA { namespace Swarm {
CopyRec* FUN_00a6d8c0(CopyRec* first, CopyRec* last, CopyRec* dest)
{
    if (first != last) {
        do {
            if (first != dest)
                dest->a.assign(first->a.mpBegin, first->a.mpEnd);
            if (&first->b != &dest->b)
                dest->b.assign(first->b.mpBegin, first->b.mpEnd);
            void* nv = first->ref;
            void* ov = dest->ref;
            if (nv != ov) {
                if (nv != 0)
                    ((IRefCounted*)nv)->AddRef();
                dest->ref = nv;
                if (ov != 0)
                    ((IRefCounted*)ov)->Release();
            }
            ++dest;
            ++first;
        } while (first != last);
    }
    return dest;
}
}}  // namespace EA::Swarm

// @ 0x00a6d950
namespace EA { namespace Swarm {
bool cEffectsManager_s00a6_d020::Shutdown()
{
    if (!mInitialized)
        return true;
    mInitialized = false;

    int* pB = gTblB;
    do {
        void (*fn)(int) = (void (*)(int))*pB;
        if (fn != 0)
            fn(0);
        pB += 8;
    } while (pB < &gTblBEnd);

    int* pA = gTblA;
    do {
        void (*fn)(int) = (void (*)(int))*pA;
        if (fn != 0)
            fn(0);
        pA += 9;
    } while (pA < &gTblAEnd);

    if (mWorld != 0) {
        IWorld* w = mWorld;
        mWorld = 0;
        w->Release();
    }

    {
        HashNode** bucket = mHash.mpBucketArray;
        HashNode* node = HashFirst(bucket);
        HashNode* end = mHash.mpBucketArray[mHash.mnBucketCount];
        while (node != end) {
            ((IValue*)node->mValue)->v50();
            HashNext(bucket, node);
        }
    }
    ((HashOps*)&mHash)->DoFreeNodes((void**)mHash.mpBucketArray, mHash.mnBucketCount);
    mHash.mnElementCount = 0;

    if (m1f0 != 0) {
        IComponent* c = m1f0;
        m1f0 = 0;
        c->Release2();
    }
    for (int i = 0; i < 12; ++i) {
        IComponent* c = m1f4[i];
        if (c != 0) {
            m1f4[i] = 0;
            c->Release2();
        }
    }
    return true;
}
}}  // namespace EA::Swarm

// @ 0x00a6da80
namespace EA { namespace Swarm {
bool cEffectsManager_s00a6_d020::FUN_00a6da80(unsigned key)
{
    HashTable* h = &mHash;
    HashIter it;
    HashIter* r = h->find(&it, &key);
    if (r->mpNode != h->mpBucketArray[h->mnBucketCount]) {
        IValue* v = (IValue*)r->mpNode->mValue;
        v->v50();
        IValue* old = (IValue*)r->mpNode->mValue;
        if (old != 0) {
            r->mpNode->mValue = 0;
            old->Release();
        }
        h->erase(it);
        return true;
    }
    return false;
}
}}  // namespace EA::Swarm

// @ 0x00a6db00
namespace EA { namespace Swarm {
bool cEffectsManager_s00a6_d020::FUN_00a6db00(int a, int b, unsigned c)
{
    unsigned r = FUN_00a6d7b0(a, b);
    if ((int)r < 0)
        return false;
    ICollection* coll = mCollectionsBegin[(int)r >> 24];
    return ((IDrawableCall*)coll)->UseCollision(r & 0xffffff, c);
}
}}  // namespace EA::Swarm

// @ 0x00a6db40
namespace EA { namespace Swarm {
cEffectsManager_s00a6_d020::~cEffectsManager_s00a6_d020()
{
    mpVtbl = (void*)kVtEffMgr;
    mpRefVtbl = (void*)kVtRefCnt;

    if ((mName.mpCapacity - mName.mpBegin) > 1 && mName.mpBegin != 0)
        operator_delete__(mName.mpBegin);

    if (mWorld != 0)
        mWorld->Release();

    ((HashOps*)&mHash)->DoFreeNodes((void**)mHash.mpBucketArray, mHash.mnBucketCount);
    mHash.mnElementCount = 0;
    if (mHash.mnBucketCount > 1)
        operator_delete__(mHash.mpBucketArray);

    for (int i = 11; i >= 0; --i) {
        IComponent* c = m1f4[i];
        if (c != 0)
            c->Release2();
    }
    if (m1f0 != 0)
        m1f0->Release2();

    if ((mStatsStr.mpCapacity - mStatsStr.mpBegin) > 1 && mStatsStr.mpBegin != 0)
        operator_delete__(mStatsStr.mpBegin);

    if (m48 != 0)
        m48->Release();
    if (m44 != 0)
        m44->Release();
    if (mRenderer != 0)
        mRenderer->Release();

    ((VectorObj*)&mCollectionsBegin)->dtor();
    mpRefVtbl = (void*)kVtGme;
}
}}  // namespace EA::Swarm

// @ 0x00a6dc60
namespace EA { namespace Swarm {
bool cEffectsManager_s00a6_d020::Init()
{
    if (mInitialized)
        return true;
    mInitialized = true;
    FUN_011e073e(&mResInfo, 0, 0x4c);

    InitParams params;
    params.a = kOne;
    params.b = kOne;
    params.c = kPoint9;
    params.d = kZero;
    params.e = kOne;
    params.f = 1;
    params.g = kPoint4;
    params.h = 0;
    ((VfnA8)(*(void***)this)[0xa8 / 4])(this, &params);

    mE8 = 1000;

    {
        void* p = EAAllocate(0xc, kSwarmSurface, 0, 0, 0, 0);
        if (p != 0) {
            *(int*)((char*)p + 8) = 0;
            *(const void**)p = (const void*)kVtA2c;
            *(const void**)((char*)p + 4) = (const void*)kVtRel;
        }
        ((Vfn78)(*(void***)this)[0x78 / 4])(this, 0x8e88fab0, 0, p);
    }
    {
        void* p = EAAllocate(0xc, kSwarmSurface, 0, 0, 0, 0);
        if (p != 0) {
            *(int*)((char*)p + 8) = 0;
            *(const void**)p = (const void*)kVtA64;
            *(const void**)((char*)p + 4) = (const void*)kVtRel;
        }
        ((Vfn78)(*(void***)this)[0x78 / 4])(this, 0xce9f4d94, 0, p);
    }
    {
        void* p = EAAllocate(0xc, kSwarmSurface, 0, 0, 0, 0);
        if (p != 0) {
            *(int*)((char*)p + 8) = 0;
            *(const void**)p = (const void*)kVtA98;
            *(const void**)((char*)p + 4) = (const void*)kVtRel;
        }
        ((Vfn78)(*(void***)this)[0x78 / 4])(this, 0xae88fac6, 0, p);
    }
    {
        void* p = EAAllocate(0xc, kSwarmSurface, 0, 0, 0, 0);
        if (p != 0) {
            *(int*)((char*)p + 8) = 0;
            *(const void**)p = (const void*)kVtAcc;
            *(const void**)((char*)p + 4) = (const void*)kVtRel;
        }
        ((Vfn78)(*(void***)this)[0x78 / 4])(this, 0xee8a4494, 0, p);
    }

    {
        int* pA = gTblA;
        do {
            void (*fn)(int) = (void (*)(int))*pA;
            if (fn != 0)
                fn(1);
            pA += 9;
        } while (pA < &gTblAEnd);
    }
    {
        int* pB = gTblB;
        do {
            void (*fn)(int) = (void (*)(int))*pB;
            if (fn != 0)
                fn(1);
            pB += 8;
        } while (pB < &gTblBEnd);
    }

    IWorld* w;
    {
        void* mem = EAAllocate(0xa4, kSwarm, 0, 0, 0, 0);
        if (mem != 0)
            w = (IWorld*)((cEffectsWorld*)mem)->ctor(this, &mDensity);
        else
            w = 0;
    }
    w->v4c();
    w->v1c(mRenderer);

    IWorld* old = mWorld;
    if (w != old) {
        w->AddRef();
        mWorld = w;
        if (old != 0)
            old->Release();
    }

    {
        unsigned key = 0;
        IWorld** slot = (IWorld**)mHash.f(&key);
        IWorld* cur = *slot;
        if (w != cur) {
            w->AddRef();
            *slot = w;
            if (cur != 0)
                cur->Release();
        }
    }
    return true;
}
}}  // namespace EA::Swarm

// @ 0x00a6ded0
namespace EA { namespace Swarm {
void cEffectsManager_s00a6_d020::SetRenderer(IRenderer* p)
{
    IRenderer* old = mRenderer;
    if (p != old) {
        if (p != 0)
            p->AddRef();
        mRenderer = p;
        if (old != 0)
            old->Release();
    }
    if (mHash.mnElementCount != 0) {
        unsigned key = 0;
        IWorld* w = *(IWorld**)mHash.f(&key);
        w->v1c(p);
    }
}
}}  // namespace EA::Swarm

// @ 0x00a6df30
namespace EA { namespace Swarm {
IWorld* cEffectsManager_s00a6_d020::CreateWorld(unsigned id, unsigned b)
{
    (void)b;
    IWorld* w;
    {
        void* mem = EAAllocate(0xa4, kSwarm, 0, 0, 0, 0);
        if (mem != 0)
            w = (IWorld*)((cEffectsWorld*)mem)->ctor(this, &mDensity);
        else
            w = 0;
    }
    w->v4c();
    w->v1c(mRenderer);

    IWorld** slot = (IWorld**)mHash.f(&id);
    IWorld* cur = *slot;
    if (w != cur) {
        w->AddRef();
        *slot = w;
        if (cur != 0)
            cur->Release();
    }
    return w;
}
}}  // namespace EA::Swarm

// @ 0x00a6dfc0
namespace EA { namespace Swarm {
void cEffectsManager_s00a6_dfc0::FUN_00a6dfc0(void* vec)
{
    cEffectsManager_s00a6_dfc0* ebx = this;
    UIntVec* ebp = (UIntVec*)vec;
    ebp->reserve((unsigned)ebx->mnElementCount);

    unsigned** edi = (unsigned**)ebx->mpBuckets;
    unsigned* esi = *edi;
    if (esi == 0) {
        ++edi;
        if (*edi == 0) {
            do { ++edi; } while (*edi == 0);
        }
        esi = *edi;
    }
    unsigned* end = *(unsigned**)((char*)ebx->mpBuckets + ebx->mnBucketCount * 4);
    while (esi != end) {
        unsigned* dst = ebp->mpEnd;
        if (dst < ebp->mpCapacity) {
            ebp->mpEnd = dst + 1;
            if (dst != 0)
                *dst = *esi;
        }
        else {
            ebp->DoInsertValue(dst, esi);
        }
        esi = (unsigned*)esi[2];
        while (esi == 0) {
            esi = (unsigned*)edi[1];
            ++edi;
        }
    }
}
}}  // namespace EA::Swarm

// @ 0x00a6e050
namespace EA { namespace Swarm {
bool cEffectsManager_s00a6_dfc0::FUN_00a6e050(void* p)
{
    cEffectsManager_s00a6_dfc0* ebp = this;
    ICollection_s00a6_dfc0* ebx = (ICollection_s00a6_dfc0*)p;
    ICollection_s00a6_dfc0** piVar5 = (ICollection_s00a6_dfc0**)((char*)ebp + 0x2c);

    int n = (*(int*)((char*)ebp + 0x30) - *(int*)((char*)ebp + 0x2c)) >> 2;
    int i = 0;
    if (0 < n) {
        ICollection_s00a6_dfc0** piVar4 = (ICollection_s00a6_dfc0**)*piVar5;
        do {
            if (*piVar4 == ebx)
                return true;
            ++i;
            ++piVar4;
        } while (i < n);
    }

    n = (*(int*)((char*)ebp + 0x30) - (int)*piVar5) >> 2;
    i = 0;
    if (0 < n) {
        ICollection_s00a6_dfc0** base = (ICollection_s00a6_dfc0**)*piVar5;
        ICollection_s00a6_dfc0** piVar4 = base;
        do {
            if (*piVar4 == 0) {
                ICollection_s00a6_dfc0* old = base[i];
                if (ebx != old) {
                    if (ebx != 0)
                        ebx->AddRef();
                    base[i] = ebx;
                    if (old != 0)
                        old->Release();
                }
                goto tail;
            }
            ++i;
            ++piVar4;
        } while (i < n);
    }

    if (ebx != 0)
        ebx->AddRef();
    {
        ICollection_s00a6_dfc0** puVar1 = (ICollection_s00a6_dfc0**)((char*)ebp + 0x30);
        if (puVar1 < (ICollection_s00a6_dfc0**)((char*)ebp + 0x34)) {
            *(ICollection_s00a6_dfc0***)((char*)ebp + 0x30) = puVar1 + 1;
            if (puVar1 != 0) {
                *puVar1 = ebx;
                if (ebx != 0)
                    ebx->AddRef();
            }
        }
        else {
            v00a0a360(puVar1, &ebx, 0);
        }
    }
    if (ebx != 0)
        ebx->Release();

tail:
    v00a69310(ebp);
    {
        ICollection_s00a6_dfc0** bk = (ICollection_s00a6_dfc0**)(*(int*)((char*)ebp + 0x228));
        ICollection_s00a6_dfc0* node = (ICollection_s00a6_dfc0*)*bk;
        if (node == 0) {
            ++bk;
            node = (ICollection_s00a6_dfc0*)*bk;
            while (node == 0) {
                ++bk;
                node = (ICollection_s00a6_dfc0*)*bk;
            }
        }
        ICollection_s00a6_dfc0* end = *(ICollection_s00a6_dfc0**)(*(int*)((char*)ebp + 0x228) + *(int*)((char*)ebp + 0x22c) * 4);
        while (node != end) {
            v00a72060(*(void**)((char*)node + 4), -1);
            node = *(ICollection_s00a6_dfc0**)((char*)node + 8);
            while (node == 0) {
                node = *(ICollection_s00a6_dfc0**)((char*)bk + 4);
                ++bk;
            }
        }
    }
    return true;
}
}}  // namespace EA::Swarm

// @ 0x00a6e1a0
namespace EA { namespace Swarm {
void* cEffectsManager_ctor(void* self)
{
    char* esi = (char*)self;
    int ebx = 0;
    *(int*)(esi + 4) = 0x13ef094;                 // ??_7GmeRefCount@@6B@
    *(int*)(esi + 8) = ebx;
    v0093a560(esi + 0x10, 4, false);              // Stopwatch
    *(int*)(esi + 0x00) = 0x1455b80;
    *(int*)(esi + 4) = 0x1455b7c;
    *(char*)(esi + 0x0c) = (char)ebx;
    *(int*)(esi + 0x2c) = ebx;
    *(int*)(esi + 0x30) = ebx;
    *(int*)(esi + 0x34) = ebx;
    *(int*)(esi + 0x40) = ebx;
    *(int*)(esi + 0x44) = ebx;
    *(int*)(esi + 0x48) = ebx;
    *(int*)(esi + 0x4c) = ebx;
    *(float*)(esi + 0x50) = 0.0f;
    *(int*)(esi + 0x54) = ebx;
    *(float*)(esi + 0x58) = kOne;
    *(float*)(esi + 0x5c) = kPoint9;
    *(float*)(esi + 0x60) = 0.0f;
    *(float*)(esi + 0x64) = kOne;
    *(int*)(esi + 0x68) = ebx;
    *(int*)(esi + 0x6c) = ebx;
    *(int*)(esi + 0x70) = ebx;
    v0011e073e(esi + 0x74, ebx, 0x4c);
    void* edi = (void*)gEmptyString16;
    *(void**)(esi + 0xc0) = edi;
    *(void**)(esi + 0xc4) = edi;
    *(int*)(esi + 0xc8) = 0x1667bad;
    v00a6cdb0(esi + 0xd0);
    *(int*)(esi + 0x1f0) = ebx;
    *(int*)(esi + 0x1f4) = 0;
    *(int*)(esi + 0x1f8) = 0;
    *(int*)(esi + 0x1fc) = 0;
    *(int*)(esi + 0x200) = 0;
    *(int*)(esi + 0x204) = 0;
    *(int*)(esi + 0x208) = 0;
    *(int*)(esi + 0x20c) = 0;
    *(int*)(esi + 0x210) = 0;
    *(int*)(esi + 0x214) = 0;
    *(int*)(esi + 0x218) = 0;
    *(int*)(esi + 0x21c) = 0;
    *(int*)(esi + 0x220) = 0;
    *(float*)(esi + 0x234) = kOne;
    *(float*)(esi + 0x238) = kTwo;
    *(int*)(esi + 0x230) = ebx;
    *(int*)(esi + 0x23c) = ebx;
    *(int*)(esi + 0x22c) = 1;
    *(int*)(esi + 0x228) = 0x154df28;
    *(int*)(esi + 0x244) = ebx;
    *(void**)(esi + 0x248) = edi;
    *(void**)(esi + 0x24c) = edi;
    *(int*)(esi + 0x250) = 0x1667bad;
    return esi;
}
}}  // namespace EA::Swarm

// @ 0x00a6e320
namespace EA { namespace Swarm {
void cEffectsManager_s00a6_dfc0::FUN_00a6e320(VecBase* vec, void* b, void* c)
{
    char* ebp = (char*)this;
    char* ebx = vec->mpBegin;
    char* esi = vec->mpEnd;
    char* r = vec->Append(esi, ebx);
    vec->FixTail(r);
    int d = (int)(esi - ebx);
    vec->mpEnd += ((d / 12) * 0x24);
    char* bk = *(char**)(ebp + 0x228);
    char* node = *(char**)bk;
    if (node == 0) {
        bk += 4;
        if (*(char**)bk == 0) {
            do { bk += 4; } while (*(char**)bk == 0);
        }
        node = *(char**)bk;
    }
    char* end = *(char**)(*(int*)(ebp + 0x228) + *(int*)(ebp + 0x22c) * 4);
    while (node != end) {
        char* coll = *(char**)(node + 4);
        (*(void(__thiscall**)(void*, void*, void*, void*))(*((char**)*(char**)coll) + 0x44))(coll, (void*)vec, b, c);
        node = *(char**)(node + 8);
        while (node == 0) {
            char* t = *(char**)(bk + 4);
            bk += 4;
            node = t;
        }
    }
}
}}  // namespace EA::Swarm

// @ 0x00a6e3e0
namespace EA { namespace Swarm {
void cEffectsManager_s00a6_dfc0::FUN_00a6e3e0(VecBase* vec, void* b)
{
    char* ebx = (char*)this;
    char* ebp = vec->mpBegin;
    char* esi = vec->mpEnd;
    char* r = vec->Append(esi, ebp);
    vec->FixTail(r);
    int d = (int)(esi - ebp);
    vec->mpEnd += (d / 12) * 0x24;
    int n = (*(int*)(ebx + 0x30) - *(int*)(ebx + 0x2c)) >> 2;
    for (int i = 0; i < n; ++i) {
        char* c = *(char**)(*(int*)(ebx + 0x2c) + i * 4);
        if (c != 0)
            (*(void(__thiscall**)(void*, void*, void*))(*((char**)*(char**)c) + 0x40))(c, (void*)vec, b);
    }
}
}}  // namespace EA::Swarm
