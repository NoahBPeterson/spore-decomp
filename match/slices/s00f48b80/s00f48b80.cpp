// Slice s00f48b80 -- SP terrain-brush description serializer + ArgScript brush commands.
//
//   0x00f48b80  WriteTerrainBrushDesc(Stream*, cTerrainBrushDescription*)
//   0x00f49040  cTerrainBrushDescription::cTerrainBrushDescription()
//   0x00f49250  cBrushCommandBase::OnRegister(void*, void*)
//   0x00f49260  cBrushCommand::Ribbon(cArguments*)      ("cap"/"numTiles"/...)
//   0x00f49350  cBrushCommand::Life(cArguments*)        (lifetime)
//   0x00f49390  cBrushCommand::Rate(cArguments*)        (imprints/second)
//   0x00f493d0  cBrushCommand::Texture(cArguments*)     (texture/draw/vary/offset/gaussian/cube)
//   0x00f49660  cBrushCommand::Filter(cArguments*)      (filtering/kernel)
//   0x00f49780  cBrushCommand::Cond(cArguments*)        (condition + falloff)
//   0x00f499a0  cBrushCommand::Cond2(cArguments*)       (condition + falloff, 5-arg form)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast
//
// The ArgScript command objects hold the argument parser at this+0x04 and a pointer to the
// parameter block at this+0x0c.  That block is a refcounted object whose cTerrainBrushDescription
// member lives at +0x08 (the serializer / ctor operate directly on the embedded member), with the
// cEffectsParser at +0x110; the command's field accesses therefore land 8 bytes after the
// serializer's description offsets.

#include "types.h"

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned __int64   uint64;

// ---------------------------------------------------------------- math types
struct Vector3 { float x, y, z; };

// ------------------------------------------- eastl::vector<float, sp_vector_allocator> (retail 0x14)
struct FloatVector {
    float* mpBegin;      // +0x00
    float* mpEnd;        // +0x04
    float* mpCapacity;   // +0x08
    uint32 mAlloc[2];    // +0x0c
};

// -------------------------------------------------- SP::cTerrainBrushDescription (0x108)
struct cTerrainBrushDescription {
    uint32 mDescriptionBase[2];       // +0x00  (vtable + refcount/flag word)
    float  mLocation[3];              // +0x08
    uint32 pad14;                     // +0x14
    uint64 mTexture;                  // +0x18
    uint8  mDrawMode;                 // +0x20
    bool   mDoGaussian;               // +0x21
    char   pad22[2];
    float  mGaussianSlope;            // +0x24
    float  mLifetime;                 // +0x28
    FloatVector mSizeCurve;           // +0x2c
    FloatVector mIntensityCurve;      // +0x40
    bool   mWaterLevelIsZero;         // +0x54
    char   pad55[3];
    float  mIntensityVary;            // +0x58
    float  mSizeVary;                 // +0x5c
    float  mRotationVary;             // +0x60
    uint32 mTextureOffset[2];         // +0x64
    float  mLevelValue;               // +0x6c
    float  mLevelVary;                // +0x70
    float  mLevelRangeValue1;         // +0x74
    float  mLevelRangeValue2;         // +0x78
    float  mImprintsPerSecond;        // +0x7c
    bool   mDoFiltering;              // +0x80
    bool   mFilterGlobal;             // +0x81
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
    bool   mDoCubeMap;                // +0xd0
    char   padD1[3];
    Vector3 mRot;                     // +0xd4
    Vector3 mRotVary;                 // +0xe0
    bool   mRibbonBrush;              // +0xec
    char   padEd[3];
    uint32 mRibbonNumTiles;           // +0xf0
    uint32 mRibbonNumSteps;           // +0xf4
    uint32 mRibbonNumTextureStrips;   // +0xf8
    uint32 mRibbonNumSkip;            // +0xfc
    char   mRibbonCap;                // +0x100
    char   pad101[7];                 // pad to 0x108

    cTerrainBrushDescription();                       // 0x00f49040
};

// ------------------------------------------------------- stream / IO helpers
struct Stream {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
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

// ---------------------------------------------------------------- ArgScript
struct cArguments {
    char** MainArguments(int* pCount, int lo, int hi);                // 0x00838020
    char** OptionArguments(const char* name, int n);                  // 0x00838330
    char** OptionArguments(const char* name, int* pCount, int lo, int hi);  // 0x00838130
};

char  ParseEnum(const char* s, const void* table);                    // 0x00840bb0
bool  ParseName(const char* s, const void* table, int* out);          // 0x008407c0
float ParseRangedFloat(void* parser, const char* s, float lo, float hi);  // 0x00840d50

// Argument parser object reached through the command's mParser (+0x04) / desc's mParser (+0x110).
// Only the slots this slice uses are named; the leading dummies place them at their real offsets.
struct cEffectsParser {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();  virtual void v4();
    virtual void v5();  virtual void v6();  virtual void v7();  virtual void v8();  virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36();
    virtual char  ParseBool(const char* s);            // +0x94
    virtual float ParseFloat(const char* s);           // +0x98
    virtual int   ParseInt(const char* s);             // +0x9c
    virtual void  v40();                               // +0xa0
    virtual void* ParseVec2(void* out, const char* s); // +0xa4
    __int64 LookupRes(int a, const char* s);           // 0x00a6ec40
};

// -------------------------------------------------- command parameter block
struct cBrushCommandDesc {
    void*  mHeader0;                  // +0x00
    uint32 mHeader4;                  // +0x04
    cTerrainBrushDescription mDesc;   // +0x08
    cEffectsParser* mParser;          // +0x110  (same object as cBrushCommand::mParser)
    uint32 mPad114;                   // +0x114
};

// SSE clamp helper (the original's inline maxss/minss).
static __forceinline float ClampF(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// ------------------------------------------------------------ command object
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

// ------------------------------------------------------------------- globals
extern const float kOne;                 // 0x01485720  1.0f
extern const float kNegOne;              // 0x013eb1bc -1.0f
extern const float kNegTwo;              // 0x013ef61c -2.0f
extern const float kHalf;                // 0x01471064  0.5f
extern const float kFive;                // 0x01486110  5.0f

extern const char  kEASTLName[];         // 0x013f2150 "EASTL"
extern const char  kAllocatorFile[];     // 0x013ebb38 allocator.h path

extern const char kTable18[];            // 0x0148de18  (global/name table)
extern const char kSmoothTable[];        // 0x0148dd58  (smooth enum table)
extern const char kReplaceTable[];       // 0x0148de30  (replace enum table)
extern const char kDrawModeTable[];      // 0x0148de70
extern const char kCondOpTable[];        // 0x0148de50

// ============================================================ functions =====

// @ 0x00f48b80
void WriteTerrainBrushDesc(Stream* s, cTerrainBrushDescription* d)
{
    s->Write(&d->mLocation, 0x0c);
    WriteUint64(s, &d->mTexture, 1, 0);
    StreamWrite(s, &d->mDrawMode, 1);
    StreamWrite(s, &d->mDoGaussian, 1);
    WriteUint32(s, &d->mGaussianSlope, 1, 0);
    WriteUint32(s, &d->mLifetime, 1, 0);
    WriteFloatVector(s, &d->mSizeCurve);
    WriteFloatVector(s, &d->mIntensityCurve);
    StreamWrite(s, &d->mWaterLevelIsZero, 1);
    WriteUint32(s, &d->mIntensityVary, 1, 0);
    WriteUint32(s, &d->mSizeVary, 1, 0);
    WriteUint32(s, &d->mRotationVary, 1, 0);
    s->Write(&d->mTextureOffset, 8);
    WriteUint32(s, &d->mLevelValue, 1, 0);
    WriteUint32(s, &d->mLevelVary, 1, 0);
    WriteUint32(s, &d->mLevelRangeValue1, 1, 0);
    WriteUint32(s, &d->mLevelRangeValue2, 1, 0);
    WriteUint32(s, &d->mImprintsPerSecond, 1, 0);
    StreamWrite(s, &d->mDoFiltering, 1);
    StreamWrite(s, &d->mFilterGlobal, 1);
    StreamWrite(s, &d->mKernelType, 1);
    StreamWrite(s, &d->mKernelOp, 1);
    WriteUint32(s, &d->mDeltaAmount, 1, 0);
    WriteFloatVector(s, &d->mSpacingCurve);
    WriteUint32(s, &d->mSpacingVary, 1, 0);
    StreamWrite(s, &d->mCondOp, 1);
    WriteUint32(s, &d->mCondN1, 1, 0);
    WriteUint32(s, &d->mCondN2, 1, 0);
    StreamWrite(s, &d->mFallOffOp, 1);
    WriteUint32(s, &d->mFallOffN1, 1, 0);
    WriteUint32(s, &d->mFallOffN2, 1, 0);
    StreamWrite(s, &d->mGradientCondOp, 1);
    WriteUint32(s, &d->mGradientCondN1, 1, 0);
    WriteUint32(s, &d->mGradientCondN2, 1, 0);
    StreamWrite(s, &d->mGradientFallOffOp, 1);
    WriteUint32(s, &d->mGradientFallOffN1, 1, 0);
    WriteUint32(s, &d->mGradientFallOffN2, 1, 0);
    StreamWrite(s, &d->mDoCubeMap, 1);
    s->Write(&d->mRot, 0x0c);
    s->Write(&d->mRotVary, 0x0c);
    StreamWrite(s, &d->mRibbonBrush, 1);
    WriteUint32(s, &d->mRibbonNumTiles, 1, 0);
    WriteUint32(s, &d->mRibbonNumSteps, 1, 0);
    WriteUint32(s, &d->mRibbonNumTextureStrips, 1, 0);
    WriteUint32(s, &d->mRibbonNumSkip, 1, 0);
    StreamWrite(s, &d->mRibbonCap, 1);
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
    mTextureOffset[0] = 0.0f;
    mTextureOffset[1] = 0.0f;
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
                mDesc->mDesc.mLevelValue = ClampF(mParser->ParseFloat(d[1]), -2.0f, 1.0f);
            } else {
                mDesc->mDesc.mLevelRangeValue1 = ClampF(mParser->ParseFloat(d[1]), -1.0f, 1.0f);
                mDesc->mDesc.mLevelRangeValue2 = ClampF(mParser->ParseFloat(d[2]), -1.0f, 1.0f);
            }
        }
    }

    a = args->OptionArguments("vary", 1);
    if (a != 0)
        mDesc->mDesc.mLevelVary = ParseRangedFloat(mParser, a[0], 0.0f, 1.0f);

    a = args->OptionArguments("offset", 1);
    if (a != 0) {
        uint32 v[2];
        uint32* p = (uint32*)mParser->ParseVec2(v, a[0]);
        mDesc->mDesc.mTextureOffset[0] = p[0];
        mDesc->mDesc.mTextureOffset[1] = p[1];
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
