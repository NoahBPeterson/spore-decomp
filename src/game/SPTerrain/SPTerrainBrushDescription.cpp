#include <intrin.h>
// src/game/SPTerrain/SPTerrainBrushDescription.cpp -- migrated from slice(s) s00f49b30, s00f48b80 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainBrushDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"

// unnamed retail callees and globals (address in the comment)
extern float DAT_016c8f18;
extern float DAT_016c8f1c;
extern float DAT_016c8f20;
extern const float kFive;                // 0x01486110  5.0f
extern const char  kEASTLName[];         // 0x013f2150 "EASTL"
extern const char  kAllocatorFile[];     // 0x013ebb38 allocator.h path
extern const char kTable18[];            // 0x0148de18  (global/name table)
extern const char kSmoothTable[];        // 0x0148dd58  (smooth enum table)
extern const char kReplaceTable[];       // 0x0148de30  (replace enum table)
extern const char kDrawModeTable[];      // 0x0148de70
extern const char kCondOpTable[];        // 0x0148de50

// ---- items of slice s00f48b80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      uint8;
typedef unsigned int       uint32;
typedef unsigned __int64   uint64;
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct FloatVector {
    float* mpBegin;      // +0x00
    float* mpEnd;        // +0x04
    float* mpCapacity;   // +0x08
    uint32 mAlloc[2];    // +0x0c
};
struct cTerrainBrushDescription {
    uint32 mDescriptionBase[2];       // +0x00  (vtable + refcount/flag word)
    float  mLocation[3];              // +0x08
    uint32 pad14;                     // +0x14
    uint64 mTexture;                  // +0x18
    uint8  mDrawMode;                 // +0x20
    uint8  mDoGaussian;               // +0x21
    char   pad22[2];
    float  mGaussianSlope;            // +0x24
    float  mLifetime;                 // +0x28
    FloatVector mSizeCurve;           // +0x2c
    FloatVector mIntensityCurve;      // +0x40
    uint8  mWaterLevelIsZero;         // +0x54
    char   pad55[3];
    float  mIntensityVary;            // +0x58
    float  mSizeVary;                 // +0x5c
    float  mRotationVary;             // +0x60
    Vector2 mTextureOffset;           // +0x64
    float  mLevelValue;               // +0x6c
    float  mLevelVary;                // +0x70
    float  mLevelRangeValue1;         // +0x74
    float  mLevelRangeValue2;         // +0x78
    float  mImprintsPerSecond;        // +0x7c
    uint8  mDoFiltering;              // +0x80
    uint8  mFilterGlobal;             // +0x81
    uint8  mKernelType;               // +0x82
    uint8  mKernelOp;                 // +0x83
    float  mDeltaAmount;              // +0x84
    FloatVector mSpacingCurve;        // +0x88
    float  mSpacingVary;              // +0x9c
    uint8  mCondOp;                   // +0xa0
    char   padA1[3];
    float  mCondN1;                   // +0xa4
    float  mCondN2;                   // +0xa8
    uint8  mFallOffOp;                // +0xac
    char   padAd[3];
    float  mFallOffN1;                // +0xb0
    float  mFallOffN2;                // +0xb4
    uint8  mGradientCondOp;           // +0xb8
    char   padB9[3];
    float  mGradientCondN1;           // +0xbc
    float  mGradientCondN2;           // +0xc0
    uint8  mGradientFallOffOp;        // +0xc4
    char   padC5[3];
    float  mGradientFallOffN1;        // +0xc8
    float  mGradientFallOffN2;        // +0xcc
    uint8  mDoCubeMap;                // +0xd0
    char   padD1[3];
    Vector3 mRot;                     // +0xd4
    Vector3 mRotVary;                 // +0xe0
    uint8  mRibbonBrush;              // +0xec
    char   padEd[3];
    uint32 mRibbonNumTiles;           // +0xf0
    uint32 mRibbonNumSteps;           // +0xf4
    uint32 mRibbonNumTextureStrips;   // +0xf8
    uint32 mRibbonNumSkip;            // +0xfc
    char   mRibbonCap;                // +0x100
    char   pad101[7];                 // pad to 0x108

    cTerrainBrushDescription();                       // 0x00f49040
};
struct Stream {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
    virtual void Write(const void* src, int size);    // slot 14 (+0x38)
};
bool WriteUint32(Stream* s, const void* p, int a, int b);   // 0x0093aa70
bool WriteUint64(Stream* s, const void* p, int a, int b);   // 0x0093ab10
bool StreamWrite(Stream* s, const void* p, int n);          // 0x0093a9a0
void WriteFloatVector(Stream* s, const void* p);            // 0x007d0250
void* EAAllocate(uint32 size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
extern float DAT_016c8f18;
extern float DAT_016c8f1c;
extern float DAT_016c8f20;
struct cArguments {
    char** MainArguments(int* pCount, int lo, int hi);                // 0x00838020
    char** OptionArguments(const char* name, int n);                  // 0x00838330
    char** OptionArguments(const char* name, int* pCount, int lo, int hi);  // 0x00838130
};
char  ParseEnum(const char* s, const void* table);                    // 0x00840bb0
bool  ParseName(const char* s, const void* table, int* out);          // 0x008407c0
float ParseRangedFloat(void* parser, const char* s, float lo, float hi);  // 0x00840d50
struct cEffectsParser {
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
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
    virtual char  ParseBool(const char* s);            // +0x94
    virtual float ParseFloat(const char* s);           // +0x98
    virtual int   ParseInt(const char* s);             // +0x9c
    virtual void  v40();                               // +0xa0
    virtual void* ParseVec2(void* out, const char* s); // +0xa4
    __int64 LookupRes(int a, const char* s);           // 0x00a6ec40
};
struct cBrushCommandDesc {
    void*  mHeader0;                  // +0x00
    uint32 mHeader4;                  // +0x04
    cTerrainBrushDescription mDesc;   // +0x08
    cEffectsParser* mParser;          // +0x110  (same object as cBrushCommand::mParser)
    uint32 mPad114;                   // +0x114
};
struct cBrushCommand {
    void*  vtbl;              // +0x00
    cEffectsParser* mParser;  // +0x04
    uint32 m08;               // +0x08
    cBrushCommandDesc* mDesc;   // +0x0c

    void Ribbon(cArguments* args);    // 0x00f49260
    void Life(cArguments* args);      // 0x00f49350
    void Rate(cArguments* args);      // 0x00f49390
    void Texture(cArguments* args);   // 0x00f493d0
    void Filter(cArguments* args);    // 0x00f49660
    void Cond(cArguments* args);      // 0x00f49780
    void Cond2(cArguments* args);     // 0x00f499a0
};
struct cMetaCommandBase {
    void* vtbl;          // +0x00
    void* m04;           // +0x04
    void* m08;           // +0x08
    void* m0c;           // +0x0c
    void OnRegister(void* a, void* b);        // 0x0083c7f0
};
struct cBrushCommandBase : cMetaCommandBase {
    void OnRegister(void* a, void* b);        // 0x00f49250
};
extern const float kFive;                // 0x01486110  5.0f
extern const char  kEASTLName[];         // 0x013f2150 "EASTL"
extern const char  kAllocatorFile[];     // 0x013ebb38 allocator.h path
extern const char kTable18[];            // 0x0148de18  (global/name table)
extern const char kSmoothTable[];        // 0x0148dd58  (smooth enum table)
extern const char kReplaceTable[];       // 0x0148de30  (replace enum table)
extern const char kDrawModeTable[];      // 0x0148de70
extern const char kCondOpTable[];        // 0x0148de50
// ---- items of slice s00f48b80 end

// ---- items of slice s00f49b30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char  T_148de50[];      // 0x0148de50  ParseEnum table
extern "C" char  S_vary[];         // 0x013f2d14  "vary"
extern "C" char  S_global[];       // 0x01458ba8  "global"
extern "C" float KF_13eecd4;       // 0x013eecd4  (1/255)
extern "C" char  VT_148dec8[];     // 0x0148dec8  BrushState vtable
typedef unsigned int  u32;
typedef unsigned char u8;
#define VFN(o, off, T) ((T)(*(void***)(o))[((off) >> 2)])
typedef float (__thiscall *TC_fp)(void*, const char*);
typedef void* (__thiscall *TC_ppp)(void*, void*, const char*);
extern "C" void* __cdecl eastl_vector_insert(void* dst, const void* src, u32 bytes);  // 0x11e0744
struct cArguments_s00f4_9b30 {
    const char** MainArguments(int* out, int lo, int hi);                    // 0x838020
    const char** OptionArguments(const char* name, int n);                   // 0x838330
    const char** OptionArguments(const char* name, int* out, int a, int b);  // 0x838130
    const char*  operator[](int i);                                          // 0x837f20
};
struct Vec {
    float* begin;   // +0x00
    float* end;     // +0x04
    float* cap;     // +0x08
    void*  alloc;   // +0x0c

    Vec(const Vec& o) {
        int n = (int)(o.end - o.begin);
        Init(n, &o.alloc);
        void* r = eastl_vector_insert(begin, o.begin, (u32)((char*)o.end - (char*)o.begin));
        end = (float*)r + n;
    }
    Vec& operator=(const Vec& o);             // 0x50d4e0
    void Init(int n, const void* a);          // 0x4aa350
    void DoInsertValue(float* pos, const float& v);   // 0x455660
    void push_back(const float& v) {
        if (end < cap) { float* p = end; end = p + 1; if (p) *p = v; }
        else DoInsertValue(end, v);
    }
    void erase(float* first, float* last) {
        eastl_vector_insert(first, last, (u32)((char*)end - (char*)last));
        *(int*)&end += (int)(((char*)last - (char*)first) >> 2) * -4;
    }
};
struct BrushState {
    void* vt;        // +0x00
    int   f04;       // +0x04
    float f08;       // +0x08
    float f0c;       // +0x0c
    float f10;       // +0x10
    int   f14;       // +0x14  (never copied)
    int   f18;       // +0x18
    int   f1c;       // +0x1c
    u8    b20;       // +0x20
    u8    b21;       // +0x21
    char  pad22[2];  // +0x22
    float f24;       // +0x24
    float f28;       // +0x28
    Vec   v2c;       // +0x2c
    int   f3c;       // +0x3c
    Vec   v40;       // +0x40
    int   f50;       // +0x50
    u8    b54;       // +0x54
    char  pad55[3];  // +0x55
    float f58;       // +0x58
    float f5c;       // +0x5c
    float f60;       // +0x60
    float f64;       // +0x64
    float f68;       // +0x68
    float f6c;       // +0x6c
    float f70;       // +0x70
    float f74;       // +0x74
    float f78;       // +0x78
    float f7c;       // +0x7c
    u8    b80;       // +0x80
    u8    b81;       // +0x81
    u8    b82;       // +0x82
    u8    b83;       // +0x83
    float f84;       // +0x84
    Vec   v88;       // +0x88
    int   f98;       // +0x98
    float f9c;       // +0x9c
    u8    ba0;       // +0xa0
    char  pada1[3];  // +0xa1
    float fa4;       // +0xa4
    float fa8;       // +0xa8
    u8    bac;       // +0xac
    char  padad[3];  // +0xad
    float fb0;       // +0xb0
    float fb4;       // +0xb4
    u8    bb8;       // +0xb8
    char  padb9[3];  // +0xb9
    float fbc;       // +0xbc
    float fc0;       // +0xc0
    u8    bc4;       // +0xc4
    char  padc5[3];  // +0xc5
    float fc8;       // +0xc8
    float fcc;       // +0xcc
    u8    bd0;       // +0xd0
    char  padd1[3];  // +0xd1
    float fd4;       // +0xd4  (copied as int in operator=)
    float fd8;       // +0xd8
    float fdc;       // +0xdc
    float fe0;       // +0xe0
    float fe4;       // +0xe4
    float fe8;       // +0xe8
    u8    bec;       // +0xec
    char  paded[3];  // +0xed
    int   ff0;       // +0xf0
    int   ff4;       // +0xf4
    int   ff8;       // +0xf8
    int   ffc;       // +0xfc
    u8    b100;      // +0x100

    BrushState(const BrushState& o);            // 0x00f4a810
    BrushState& operator=(const BrushState& o); // 0x00f4a5d0
};
struct BrushSubState {
    char  pad00[0x34];   // +0x00
    Vec   v2c;           // +0x34  (= BrushState::v2c)
    char  pad44[4];      // +0x44
    Vec   v40;           // +0x48  (= BrushState::v40)
    char  pad58[8];      // +0x58
    float f60;           // +0x60  (= BrushState::f58)
    float f64;           // +0x64  (= BrushState::f5c)
    char  pad68[0x21];   // +0x68
    u8    b89;           // +0x89  (= BrushState::b81)
    char  pad8a[6];      // +0x8a
    Vec   v88;           // +0x90  (= BrushState::v88)
    char  padA0[4];      // +0xa0
    float fA4;           // +0xa4  (= BrushState::f9c)
};
struct cCommandBase {
    void* vt;        // +0x00
    void* parser;    // +0x04
    int   f08;       // +0x08
    void* state;     // +0x0c

    cCommandBase();                                        // 0x83c800
    void OnRegister(cArguments_s00f4_9b30* p, void* s);               // 0x83c780
    void SetUserData(void* p);                             // 0xfd9450
    void* operator new(u32, const char*, int, int, int, int);
};
struct cBrushCondRangeCommand : cCommandBase { void Execute(cArguments_s00f4_9b30* args); };   // 0x00f49b30
struct cBrushVecCommand : cCommandBase { void Execute(cArguments_s00f4_9b30* args); };         // 0x00f49c50
struct cBrushFloatsCommand : cCommandBase { void Execute(cArguments_s00f4_9b30* args); };      // 0x00f4a130
struct cBrushSizeCommand : cCommandBase { void Execute(cArguments_s00f4_9b30* args); };        // 0x00f4a3b0
struct cBrushVaryCommand : cCommandBase { void Execute(cArguments_s00f4_9b30* args); };        // 0x00f4a4c0
struct Vec3f { float x, y, z; };
#define SUBST ((BrushSubState*)this->state)
// ---- items of slice s00f49b30 end

// @ 0x00f48b80
void WriteTerrainBrushDesc(Stream* s, cTerrainBrushDescription* d)
{
    uint32 u;
    uint64 u64;

    s->Write(&d->mLocation, 0x0c);
    u64 = d->mTexture;                  WriteUint64(s, &u64, 1, 0);
    *(uint8*)&u = d->mDrawMode;         StreamWrite(s, &u, 1);
    *(uint8*)&u = d->mDoGaussian != 0;  StreamWrite(s, &u, 1);
    *(float*)&u = d->mGaussianSlope;    WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mLifetime;         WriteUint32(s, &u, 1, 0);
    WriteFloatVector(s, &d->mSizeCurve);
    WriteFloatVector(s, &d->mIntensityCurve);
    *(uint8*)&u = d->mWaterLevelIsZero != 0; StreamWrite(s, &u, 1);
    *(float*)&u = d->mIntensityVary;    WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mSizeVary;         WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mRotationVary;     WriteUint32(s, &u, 1, 0);
    s->Write(&d->mTextureOffset, 8);
    *(float*)&u = d->mLevelValue;       WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mLevelVary;        WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mLevelRangeValue1; WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mLevelRangeValue2; WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mImprintsPerSecond; WriteUint32(s, &u, 1, 0);
    *(uint8*)&u = d->mDoFiltering != 0; StreamWrite(s, &u, 1);
    *(uint8*)&u = d->mFilterGlobal != 0; StreamWrite(s, &u, 1);
    *(uint8*)&u = d->mKernelType;       StreamWrite(s, &u, 1);
    *(uint8*)&u = d->mKernelOp;         StreamWrite(s, &u, 1);
    *(float*)&u = d->mDeltaAmount;      WriteUint32(s, &u, 1, 0);
    WriteFloatVector(s, &d->mSpacingCurve);
    *(float*)&u = d->mSpacingVary;      WriteUint32(s, &u, 1, 0);
    *(uint8*)&u = d->mCondOp;           StreamWrite(s, &u, 1);
    *(float*)&u = d->mCondN1;           WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mCondN2;           WriteUint32(s, &u, 1, 0);
    *(uint8*)&u = d->mFallOffOp;        StreamWrite(s, &u, 1);
    *(float*)&u = d->mFallOffN1;        WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mFallOffN2;        WriteUint32(s, &u, 1, 0);
    *(uint8*)&u = d->mGradientCondOp;   StreamWrite(s, &u, 1);
    *(float*)&u = d->mGradientCondN1;   WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mGradientCondN2;   WriteUint32(s, &u, 1, 0);
    *(uint8*)&u = d->mGradientFallOffOp; StreamWrite(s, &u, 1);
    *(float*)&u = d->mGradientFallOffN1; WriteUint32(s, &u, 1, 0);
    *(float*)&u = d->mGradientFallOffN2; WriteUint32(s, &u, 1, 0);
    *(uint8*)&u = d->mDoCubeMap != 0;   StreamWrite(s, &u, 1);
    s->Write(&d->mRot, 0x0c);
    s->Write(&d->mRotVary, 0x0c);
    *(uint8*)&u = d->mRibbonBrush != 0; StreamWrite(s, &u, 1);
    u = d->mRibbonNumTiles;             WriteUint32(s, &u, 1, 0);
    u = d->mRibbonNumSteps;             WriteUint32(s, &u, 1, 0);
    u = d->mRibbonNumTextureStrips;     WriteUint32(s, &u, 1, 0);
    u = d->mRibbonNumSkip;              WriteUint32(s, &u, 1, 0);
    *(uint8*)&u = d->mRibbonCap != 0;   StreamWrite(s, &u, 1);
}

// @ 0x00f49040
cTerrainBrushDescription::cTerrainBrushDescription()
{
    mDescriptionBase[1] = 0;
    mDescriptionBase[0] = 0x0148dec8;
    mLocation[0] = DAT_016c8f18;
    mLocation[1] = DAT_016c8f1c;
    mLocation[2] = DAT_016c8f20;
    mGaussianSlope = 0.0f;
    mTexture = 0xffffffffffffffffull;
    mDrawMode = 0;
    mDoGaussian = false;
    mLifetime = kFive;

    mSizeCurve.mpBegin = (float*)EAAllocate(4, kEASTLName, 0, 0, (int)kAllocatorFile, 0xd1);
    mSizeCurve.mpCapacity = mSizeCurve.mpBegin + 1;
    *mSizeCurve.mpBegin = 1.0f;
    mSizeCurve.mpEnd = mSizeCurve.mpBegin + 1;

    mIntensityCurve.mpBegin = (float*)EAAllocate(4, kEASTLName, 0, 0, (int)kAllocatorFile, 0xd1);
    *mIntensityCurve.mpBegin = 1.0f;
    mIntensityCurve.mpCapacity = mIntensityCurve.mpBegin + 1;
    mIntensityCurve.mpEnd = mIntensityCurve.mpBegin + 1;

    mWaterLevelIsZero = false;
    mIntensityVary = 0.0f;
    mSizeVary = 0.0f;
    mRotationVary = 0.0f;
    mTextureOffset.x = 0.0f;
    mTextureOffset.y = 0.0f;
    mLevelValue = 0.0f;
    mLevelVary = 0.0f;
    mLevelRangeValue1 = 0.0f;
    mLevelRangeValue2 = 0.0f;
    mImprintsPerSecond = 1.0f;
    mDoFiltering = false;
    mFilterGlobal = false;
    mKernelType = 0;
    mKernelOp = 0;
    mDeltaAmount = 0.0f;
    mSpacingCurve.mpBegin = 0;
    mSpacingCurve.mpEnd = 0;
    mSpacingCurve.mpCapacity = 0;
    mSpacingVary = 0.0f;
    mCondOp = 0;
    mCondN1 = 0.0f;
    mCondN2 = 0.0f;
    mFallOffOp = 0;
    mFallOffN1 = 0.0f;
    mFallOffN2 = 0.0f;
    mGradientCondOp = 0;
    mGradientCondN1 = 0.0f;
    mGradientCondN2 = 0.0f;
    mGradientFallOffOp = 0;
    mGradientFallOffN1 = 0.0f;
    mGradientFallOffN2 = 0.0f;
    mDoCubeMap = false;
    mRot.x = 0.0f; mRot.y = 0.0f; mRot.z = 0.0f;
    mRotVary.x = 0.0f; mRotVary.y = 0.0f; mRotVary.z = 0.0f;
    mRibbonNumTiles = 1;
    mRibbonNumTextureStrips = 1;
    mRibbonNumSkip = 1;
    mRibbonCap = true;
    mRibbonBrush = false;
    mRibbonNumSteps = 0x14;
}

// @ 0x00f49250
void cBrushCommandBase::OnRegister(void* a, void* b)
{
    m0c = b;
    cMetaCommandBase::OnRegister(a, b);
}

// @ 0x00f49260
void cBrushCommand::Ribbon(cArguments* args)
{
    mDesc->mDesc.mRibbonBrush = true;
    char** a = args->OptionArguments("cap", 1);
    if (a != 0)
        mDesc->mDesc.mRibbonCap = mParser->ParseBool(a[0]);
    a = args->OptionArguments("numTiles", 1);
    if (a != 0)
        mDesc->mDesc.mRibbonNumTiles = mParser->ParseInt(a[0]);
    a = args->OptionArguments("numSteps", 1);
    if (a != 0)
        mDesc->mDesc.mRibbonNumSteps = mParser->ParseInt(a[0]);
    a = args->OptionArguments("numTextureStrips", 1);
    if (a != 0)
        mDesc->mDesc.mRibbonNumTextureStrips = mParser->ParseInt(a[0]);
    a = args->OptionArguments("numSkip", 1);
    if (a != 0)
        mDesc->mDesc.mRibbonNumSkip = mParser->ParseInt(a[0]);
}

// @ 0x00f49350
void cBrushCommand::Life(cArguments* args)
{
    int count;
    char** a = args->MainArguments(&count, 0, 0x7fffffff);
    if (count > 0)
        mDesc->mDesc.mLifetime = mParser->ParseFloat(a[0]);
}

// @ 0x00f49390
void cBrushCommand::Rate(cArguments* args)
{
    int count;
    char** a = args->MainArguments(&count, 1, 0x7fffffff);
    if (count > 0)
        mDesc->mDesc.mImprintsPerSecond = mParser->ParseFloat(a[0]);
}

// @ 0x00f493d0
#include "sse_helpers.h"
void cBrushCommand::Texture(cArguments* args)
{
    int count;
    char** a = args->MainArguments(&count, 0, 1);
    mDesc->mDesc.mLevelVary = 0.0f;
    if (count > 0)
        mDesc->mDesc.mTexture = (uint64)mDesc->mParser->LookupRes(0, a[0]);

    char** d = args->OptionArguments("draw", &count, 1, 3);
    if (d != 0) {
        mDesc->mDesc.mDrawMode = ParseEnum(d[0], kDrawModeTable);
        mDesc->mDesc.mLevelValue = 0.0f;
        mDesc->mDesc.mLevelRangeValue2 = 0.0f;
        mDesc->mDesc.mLevelRangeValue1 = 0.0f;
        if (count > 1) {
            if (mDesc->mDesc.mDrawMode == 3) {
                mDesc->mDesc.mLevelValue = SseClamp(mParser->ParseFloat(d[1]), -2.0f, 1.0f);
            } else {
                mDesc->mDesc.mLevelRangeValue1 = SseClamp(mParser->ParseFloat(d[1]), -1.0f, 1.0f);
                mDesc->mDesc.mLevelRangeValue2 = SseClamp(mParser->ParseFloat(d[2]), -1.0f, 1.0f);
            }
        }
    }

    a = args->OptionArguments("vary", 1);
    if (a != 0)
        mDesc->mDesc.mLevelVary = ParseRangedFloat(mParser, a[0], 0.0f, 1.0f);

    a = args->OptionArguments("offset", 1);
    if (a != 0) {
        uint32 v[2];
        mDesc->mDesc.mTextureOffset = *(Vector2*)mParser->ParseVec2(v, a[0]);
    }

    a = args->OptionArguments("gaussian", &count, 0, 1);
    if (a != 0) {
        mDesc->mDesc.mDoGaussian = true;
        if (count == 1)
            mDesc->mDesc.mGaussianSlope = mParser->ParseFloat(a[0]);
        else
            mDesc->mDesc.mGaussianSlope = 1.0f;
    }

    a = args->OptionArguments("cube", 0);
    if (a != 0)
        mDesc->mDesc.mDoCubeMap = true;
}

// @ 0x00f49660
void cBrushCommand::Filter(cArguments* args)
{
    int count;
    char** a = args->MainArguments(&count, 0, 0x7fffffff);
    if (count >= 1) {
        int unused;
        mDesc->mDesc.mDoFiltering = true;
        int skip = 1;
        if (ParseName(a[0], kTable18, &unused))
            skip = 0;
        mDesc->mDesc.mKernelType = ParseEnum(a[1 - skip], kSmoothTable);
        if (mDesc->mDesc.mKernelType == 0)
            mDesc->mDesc.mDoFiltering = false;
        if (count == 3 - skip) {
            uint8 kt = mDesc->mDesc.mKernelType;
            if (kt == 0x0f || kt == 0x10 || kt == 0x14)
                mDesc->mDesc.mDeltaAmount = mParser->ParseFloat(a[2 - skip]);
            else
                mDesc->mDesc.mKernelOp = ParseEnum(a[2 - skip], kReplaceTable);
        }
    } else {
        mDesc->mDesc.mDoFiltering = false;
    }
}

// @ 0x00f49780
void cBrushCommand::Cond(cArguments* args)
{
    int count;
    char** a = args->MainArguments(&count, 0, 0x7fffffff);
    mDesc->mDesc.mCondOp = ParseEnum(a[0], kCondOpTable);
    if (mDesc->mDesc.mCondOp == 3 && count == 3) {
        mDesc->mDesc.mCondN1 = mParser->ParseFloat(a[1]);
        mDesc->mDesc.mCondN2 = mParser->ParseFloat(a[2]);
    } else if (count == 2) {
        mDesc->mDesc.mCondN1 = mParser->ParseFloat(a[1]);
    } else {
        mDesc->mDesc.mCondOp = 0;
    }

    mDesc->mDesc.mFallOffOp = 0;
    count = 0;
    char** f = args->OptionArguments("falloff", &count, 1, 2);
    if (f != 0) {
        if (count > 0)
            mDesc->mDesc.mFallOffN1 = mParser->ParseFloat(f[0]);
        if (count > 1)
            mDesc->mDesc.mFallOffN2 = mParser->ParseFloat(f[1]);
        uint8 op = mDesc->mDesc.mCondOp;
        if (op == 3) {
            if (count == 2 && mDesc->mDesc.mCondN1 > mDesc->mDesc.mFallOffN1
                           && mDesc->mDesc.mFallOffN2 > mDesc->mDesc.mCondN2)
                mDesc->mDesc.mFallOffOp = 1;
        } else if (op == 1) {
            if (count == 1 && mDesc->mDesc.mCondN1 > mDesc->mDesc.mFallOffN1)
                mDesc->mDesc.mFallOffOp = 1;
        } else if (op == 2) {
            if (count == 1 && mDesc->mDesc.mFallOffN1 > mDesc->mDesc.mCondN1)
                mDesc->mDesc.mFallOffOp = 1;
        }
    }

    mDesc->mDesc.mFallOffN1 = (mDesc->mDesc.mFallOffN1 + 1.0f) * 0.5f;
    mDesc->mDesc.mCondN1 = (mDesc->mDesc.mCondN1 + 1.0f) * 0.5f;
    mDesc->mDesc.mCondN2 = (mDesc->mDesc.mCondN2 + 1.0f) * 0.5f;
    mDesc->mDesc.mFallOffN2 = (mDesc->mDesc.mFallOffN2 + 1.0f) * 0.5f;
}

// @ 0x00f499a0
void cBrushCommand::Cond2(cArguments* args)
{
    int count;
    char** a = args->MainArguments(&count, 0, 0x7fffffff);
    mDesc->mDesc.mCondOp = ParseEnum(a[0], kCondOpTable);
    mDesc->mDesc.mFallOffOp = 0;
    if (mDesc->mDesc.mCondOp == 3 && count == 5) {
        mDesc->mDesc.mFallOffOp = 1;
        mDesc->mDesc.mFallOffN1 = mParser->ParseFloat(a[1]);
        mDesc->mDesc.mCondN1 = mParser->ParseFloat(a[2]);
        mDesc->mDesc.mCondN2 = mParser->ParseFloat(a[3]);
        mDesc->mDesc.mFallOffN2 = mParser->ParseFloat(a[4]);
    } else if (count == 3) {
        mDesc->mDesc.mFallOffOp = 1;
        mDesc->mDesc.mFallOffN1 = mParser->ParseFloat(a[2]);
        mDesc->mDesc.mCondN1 = mParser->ParseFloat(a[1]);
    } else {
        mDesc->mDesc.mCondOp = 0;
    }

    mDesc->mDesc.mFallOffN1 = (mDesc->mDesc.mFallOffN1 + 1.0f) * 0.5f;
    mDesc->mDesc.mCondN1 = (mDesc->mDesc.mCondN1 + 1.0f) * 0.5f;
    mDesc->mDesc.mCondN2 = (mDesc->mDesc.mCondN2 + 1.0f) * 0.5f;
    mDesc->mDesc.mFallOffN2 = (mDesc->mDesc.mFallOffN2 + 1.0f) * 0.5f;
}

struct BrushRangeState {
    char reserved[0xc0];
    u8 mode;
    char reservedC1[3];
    float lower;
    float upper;
    u8 enabled;
    char reservedCD[3];
    float start;
    float end;
};

// @ 0x00f49b30
void cBrushCondRangeCommand::Execute(cArguments_s00f4_9b30* args)
{
    int n;
    const char** a = args->MainArguments(&n, 0, 0x7fffffff);
    static_cast<BrushRangeState*>(this->state)->mode = (u8)ParseEnum(a[0], T_148de50);
    static_cast<BrushRangeState*>(this->state)->enabled = 0;
    if (static_cast<BrushRangeState*>(this->state)->mode == 3 && n == 5) {
        static_cast<BrushRangeState*>(this->state)->enabled = 1;
        _ReadWriteBarrier();
        static_cast<BrushRangeState*>(this->state)->start =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[1]);
        _ReadWriteBarrier();
        static_cast<BrushRangeState*>(this->state)->lower =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[2]);
        _ReadWriteBarrier();
        static_cast<BrushRangeState*>(this->state)->upper =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[3]);
        _ReadWriteBarrier();
        static_cast<BrushRangeState*>(this->state)->end =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[4]);
        return;
    }
    if (n == 3) {
        static_cast<BrushRangeState*>(this->state)->enabled = 1;
        _ReadWriteBarrier();
        static_cast<BrushRangeState*>(this->state)->start =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[2]);
        _ReadWriteBarrier();
        static_cast<BrushRangeState*>(this->state)->lower =
            VFN(this->parser, 0x98, TC_fp)(this->parser, a[1]);
        return;
    }
    static_cast<BrushRangeState*>(this->state)->mode = 0;
}

// @ 0x00f49c50
void cBrushVecCommand::Execute(cArguments_s00f4_9b30* args)
{
    Vec3f tmp;
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    const Vec3f* r = (const Vec3f*)VFN(this->parser, 0xa8, TC_ppp)(this->parser, &tmp, a[0]);
    char* st = (char*)this->state;
    *(Vec3f*)(st + 0xdc) = *r;
    const char** o = args->OptionArguments(S_vary, 1);
    if (o) {
        const Vec3f* r2 = (const Vec3f*)VFN(this->parser, 0xa8, TC_ppp)(this->parser, &tmp, o[0]);
        char* st2 = (char*)this->state;
        *(Vec3f*)(st2 + 0xe8) = *r2;
    }
}

// @ 0x00f4a130
void cBrushFloatsCommand::Execute(cArguments_s00f4_9b30* args)
{
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);

    Vec* v = &SUBST->v40;
    v->erase(v->begin, v->end);
    for (int i = 0; i < n; i++) {
        float f = VFN(this->parser, 0x98, TC_fp)(this->parser, a[i]);
        SUBST->v40.push_back(f);
    }

    const char** o = args->OptionArguments(S_vary, 1);
    if (o)
        SUBST->f60 = ParseRangedFloat(this->parser, o[0], 0.0f, 1.0f);

    const char* s = args->operator[](0);
    bool is255 = (s[0] == '2' && s[1] == '5' && s[2] == '5' && s[3] == '\0');
    if (is255) {
        Vec* w = &SUBST->v40;
        int cnt = (int)(w->end - w->begin);
        for (int i = 0; i < cnt; i++)
            w->begin[i] = w->begin[i] * KF_13eecd4;
    }
}

// @ 0x00f4a3b0
void cBrushSizeCommand::Execute(cArguments_s00f4_9b30* args)
{
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);

    Vec* v = &SUBST->v2c;
    v->erase(v->begin, v->end);
    for (int i = 0; i < n; i++) {
        float f = VFN(this->parser, 0x98, TC_fp)(this->parser, a[i]);
        SUBST->v2c.push_back(f);
    }

    const char** o = args->OptionArguments(S_vary, 1);
    if (o)
        SUBST->f64 = ParseRangedFloat(this->parser, o[0], 0.0f, 1.0f);

    if (args->OptionArguments(S_global, &n, 0, 1))
        SUBST->b89 = 1;
}

// @ 0x00f4a4c0
void cBrushVaryCommand::Execute(cArguments_s00f4_9b30* args)
{
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);

    SUBST->fA4 = 0.0f;
    Vec* v = &SUBST->v88;
    v->erase(v->begin, v->end);
    for (int i = 0; i < n; i++) {
        float f = VFN(this->parser, 0x98, TC_fp)(this->parser, a[i]);
        SUBST->v88.push_back(f);
    }

    const char** o = args->OptionArguments(S_vary, 1);
    if (o)
        SUBST->fA4 = ParseRangedFloat(this->parser, o[0], 0.0f, 1.0f);
}

// @ 0x00f4a5d0
BrushState& BrushState::operator=(const BrushState& o)
{
    *(int*)((char*)this + 0x08) = *(int*)((char*)&o + 0x08);
    *(int*)((char*)this + 0x0c) = *(int*)((char*)&o + 0x0c);
    *(int*)((char*)this + 0x10) = *(int*)((char*)&o + 0x10);
    f18 = o.f18;
    f1c = o.f1c;
    b20 = o.b20;
    b21 = o.b21;
    f24 = o.f24;
    f28 = o.f28;
    v2c = o.v2c;
    v40 = o.v40;
    b54 = o.b54;
    f58 = o.f58;
    f5c = o.f5c;
    f60 = o.f60;
    *(int*)((char*)this + 0x64) = *(int*)((char*)&o + 0x64);
    *(int*)((char*)this + 0x68) = *(int*)((char*)&o + 0x68);
    f6c = o.f6c;
    f70 = o.f70;
    f74 = o.f74;
    f78 = o.f78;
    f7c = o.f7c;
    b80 = o.b80;
    b81 = o.b81;
    b82 = o.b82;
    b83 = o.b83;
    f84 = o.f84;
    v88 = o.v88;
    f9c = o.f9c;
    ba0 = o.ba0;
    fa4 = o.fa4;
    fa8 = o.fa8;
    bac = o.bac;
    fb0 = o.fb0;
    fb4 = o.fb4;
    bb8 = o.bb8;
    fbc = o.fbc;
    fc0 = o.fc0;
    bc4 = o.bc4;
    fc8 = o.fc8;
    fcc = o.fcc;
    bd0 = o.bd0;
    *(int*)((char*)this + 0xd4) = *(int*)((char*)&o + 0xd4);
    *(int*)((char*)this + 0xd8) = *(int*)((char*)&o + 0xd8);
    *(int*)((char*)this + 0xdc) = *(int*)((char*)&o + 0xdc);
    *(int*)((char*)this + 0xe0) = *(int*)((char*)&o + 0xe0);
    *(int*)((char*)this + 0xe4) = *(int*)((char*)&o + 0xe4);
    *(int*)((char*)this + 0xe8) = *(int*)((char*)&o + 0xe8);
    bec = o.bec;
    ff0 = o.ff0;
    ff4 = o.ff4;
    ff8 = o.ff8;
    ffc = o.ffc;
    b100 = o.b100;
    return *this;
}

// @ 0x00f4a810
BrushState::BrushState(const BrushState& o)
: vt((void*)VT_148dec8), f04(0),
      f08(o.f08), f0c(o.f0c), f10(o.f10),
      f18(o.f18), f1c(o.f1c),
      b20(o.b20), b21(o.b21),
      f24(o.f24), f28(o.f28),
      v2c(o.v2c), v40(o.v40),
      b54(o.b54),
      f58(o.f58), f5c(o.f5c), f60(o.f60), f64(o.f64), f68(o.f68),
      f6c(o.f6c), f70(o.f70), f74(o.f74), f78(o.f78), f7c(o.f7c),
      b80(o.b80), b81(o.b81), b82(o.b82), b83(o.b83),
      f84(o.f84), v88(o.v88),
      f9c(o.f9c), ba0(o.ba0),
      fa4(o.fa4), fa8(o.fa8),
      bac(o.bac), fb0(o.fb0), fb4(o.fb4), bb8(o.bb8),
      fbc(o.fbc), fc0(o.fc0), bc4(o.bc4),
      fc8(o.fc8), fcc(o.fcc), bd0(o.bd0),
      fd4(o.fd4), fd8(o.fd8), fdc(o.fdc), fe0(o.fe0), fe4(o.fe4), fe8(o.fe8),
      bec(o.bec), ff0(o.ff0), ff4(o.ff4), ff8(o.ff8), ffc(o.ffc), b100(o.b100)
{
}
