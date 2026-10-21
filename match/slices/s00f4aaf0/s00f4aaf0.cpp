// Slice s00f4aaf0 -- Terrain SWARM brush command / component support code.
// Region is /O2 (no frame pointer) with /arch:SSE float moves; a couple of the
// object-copy helpers use x87.  Class layouts follow the 2008 dev PDB with the
// retail eastl::vector growth (0x10 -> 0x14) applied, matching slice s00f4c300.

#include <math.h>
#include <string.h>
#include <intrin.h>

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned __int64 uint64;

// ------------------------------------------------------------------ math types
struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct Matrix3 { float m[9]; Matrix3* Assign(const Matrix3* src); };   // 0x0041cb40
struct cTransform {                       // EA::Swarm::cTransform, 0x38
    uint16 mFlags;
    uint16 mModificationCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;
    void PreTransformBy(const cTransform* x);            // 0x00537f40
    cTransform& operator=(const cTransform& o);          // 0x00537dc0
};

// ------------------------------------------------------------- eastl containers
struct FloatVector {                       // eastl::vector<float, sp_vector_allocator> 0x14
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32 mAlloc[2];
    uint32 size() const { return (uint32)(mpEnd - mpBegin); }
};

struct cBrushVertex {                      // SP::cBrushVertex, 0x1c
    Vector3 mPosition;
    Vector2 mUV;
    float mIntensity;
    float mSize;
};

struct BrushVertexVector {                 // eastl::vector<cBrushVertex, sp_vector_allocator>
    cBrushVertex* mpBegin;                 // +0x00
    cBrushVertex* mpEnd;                   // +0x04
    cBrushVertex* mpCapacity;              // +0x08
    uint32 mAlloc[2];                      // +0x0c
    uint32 size() const;                   // 0x00f4b160
    cBrushVertex* back();                  // 0x00f4b180
};

// ---------------------------------------------------------------- brush data
struct cTerrainBrushDescription {          // SP::cTerrainBrushDescription (retail layout)
    uint32 mDescriptionBase[2];            // +0x00
    float  mLocation[3];                   // +0x08
    uint32 pad14;                          // +0x14
    uint32 mTexture[2];                    // +0x18
    uint8  mDrawMode;                      // +0x20
    bool   mDoGaussian;                    // +0x21
    char   pad22[2];
    float  mGaussianSlope;                 // +0x24
    float  mLifetime;                      // +0x28
    FloatVector mSizeCurve;                // +0x2c
    FloatVector mIntensityCurve;           // +0x40
    bool   mWaterLevelIsZero;              // +0x54
    char   pad55[3];
    float  mIntensityVary;                 // +0x58
    float  mSizeVary;                      // +0x5c
    float  mRotationVary;                  // +0x60
    float  mTextureOffset[2];              // +0x64
    float  mLevelValue;                    // +0x6c
    float  mLevelVary;                     // +0x70
    float  mLevelRangeValue1;              // +0x74
    float  mLevelRangeValue2;              // +0x78
    float  mImprintsPerSecond;             // +0x7c
    bool   mDoFiltering;                   // +0x80
    bool   mFilterGlobal;                  // +0x81
    uint8  mKernelType;                    // +0x82
    uint8  mKernelOp;                      // +0x83
    float  mDeltaAmount;                   // +0x84
    FloatVector mSpacingCurve;             // +0x88
    float  mSpacingVary;                   // +0x9c
    uint8  mCondOp;                        // +0xa0
    char   padA1[3];
    float  mCondN1;                        // +0xa4
    float  mCondN2;                        // +0xa8
    uint8  mFallOffOp;                     // +0xac
    char   padAd[3];
    float  mFallOffN1;                     // +0xb0
    float  mFallOffN2;                     // +0xb4
    uint8  mGradientCondOp;                // +0xb8
    char   padB9[3];
    float  mGradientCondN1;                // +0xbc
    float  mGradientCondN2;                // +0xc0
    uint8  mGradientFallOffOp;             // +0xc4
    char   padC5[3];
    float  mGradientFallOffN1;             // +0xc8
    float  mGradientFallOffN2;             // +0xcc
    bool   mDoCubeMap;                     // +0xd0
    char   padD1[3];
    Vector3 mRot;                          // +0xd4
    Vector3 mRotVary;                      // +0xe0
    bool   mRibbonBrush;                   // +0xec
    char   padEd[0x108 - 0xed];            // tail (ribbon params)

    cTerrainBrushDescription();                                  // 0x00f49040
    cTerrainBrushDescription& operator=(const cTerrainBrushDescription&);  // 0x00f4a5d0
    ~cTerrainBrushDescription();                                 // 0x00f48b00
    cTerrainBrushDescription* Construct(const cTerrainBrushDescription& src);  // 0x00f4a810
};

// ------------------------------------------------------------- effects parser
struct cEffectsParser;                     // EA::Swarm::cEffectsParser (opaque)
struct cEffectsParser {
    void* GetInheritedDescription(char** args, int argc, int mask);   // 0x00a6f090
    void  Install(void* name, int mask, void* desc);                  // 0x00a6f9c0
};

// ------------------------------------------------------------------ ArgScript
struct cArguments {                        // EA::ArgScript::cArguments, 0x38
    char** MainArguments(int* count, int a, int b);       // 0x00838020
    char** OptionArguments(const char* name, int a);      // 0x00838330
};
struct cCommandBase {                      // EA::ArgScript::cCommandBase, 0x10
    void* vtbl;
    uint32 mPad[3];
    cCommandBase();                        // 0x0083c800
};

struct Registrar {                         // command / group registrar
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void RegisterKey(void* key, void* cmd);     // +0x14
    virtual void RegisterGroup(void* key, void* cmd);   // +0x18
};

extern void* g15b099c;
extern void* g15b09a0;
extern void* g15b09a4;
extern void* g15b09a8;

// ------------------------------------------------------- brush effect command
struct NString {                           // eastl::basic_string (0x10)
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32 mAlloc;
    void assign(const void* first, const void* last);     // 0x00454cb0
};

struct cBrushEffectCommand {               // (anonymous)::cBrushEffectCommand, 0x160
    void* vtbl;                            // +0x00
    void* mComponent;                      // +0x04
    uint32 pad08[10];                      // +0x08..+0x30
    cEffectsParser* mParser;               // +0x30
    uint32 pad34;                          // +0x34
    uint32 mStateID;                       // +0x38
    uint32 pad3c;                          // +0x3c
    cTerrainBrushDescription mDesc;        // +0x40
    void* pad148;                          // +0x148
    uint32 pad14c;                         // +0x14c
    NString mDescName;                     // +0x150

    void Execute(cArguments*);             // 0x00f4aaf0
    void Build(char whenZero);             // 0x00f4abc0
};

// ------------------------------------------------- brush create component
struct SWARM_TerrainBrushCreate {
    void* vtbl;                            // +0x00
    void* vtbl2;                           // +0x04
    int   mRefTarget;                      // +0x08
    void* mParam;                          // +0x0c
    uint8 mFlag10;                         // +0x10
    char  pad11[3];                        // +0x11
    uint16 w14;                            // +0x14
    uint16 w16;                            // +0x16
    Vector3 mPos;                          // +0x18
    float mSize;                           // +0x24
    Matrix3 mRot;                          // +0x28
    float mF4c;                            // +0x4c
    uint16 w50;                            // +0x50
    uint16 w52;                            // +0x52
    Vector3 mPos2;                         // +0x54
    float mSize2;                          // +0x60
    Matrix3 mRot2;                         // +0x64
    float mF88;                            // +0x88
    uint8 mFlag8c;                         // +0x8c
    float mF90;                            // +0x90
    float mF94;                            // +0x94
    float mF98;                            // +0x98
    float mF9c;                            // +0x9c
    float mFa0;                            // +0xa0
    float mFa4;                            // +0xa4
    uint8 mFa8;                            // +0xa8
    uint8 mFa9;                            // +0xa9
    float mFac;                            // +0xac
    float mFb0;                            // +0xb0
    float mFb4;                            // +0xb4
    float mFb8;                            // +0xb8
    float mFbc;                            // +0xbc
    void* mPc0;                            // +0xc0
    void* mPc4;                            // +0xc4
    uint32 mCc8;                           // +0xc8
    uint32 mCcc;                           // +0xcc
    SWARM_TerrainBrushCreate(void* p);     // 0x00f4b220
    ~SWARM_TerrainBrushCreate();           // 0x00f4b3a0
};

// ------------------------------------------------- cTerrainBrushEffect (0xd8)
struct cComponentStats;

// Parameter blocks the terrain decal builder (0x00f6c940) consumes.  The retail
// code builds these on the stack; offsets match the original frame layout.
struct cDecalFront {                       // brush/level descriptor
    uint8  mUseNoise;                      // +0x00  (no texture, or gaussian draw)
    uint8  mFilterGlobal;                  // +0x01
    uint8  mDoCubeMap;                     // +0x02
    uint8  pad03;
    float  mGaussianSlope;                 // +0x04
    uint32 mDrawMode;                      // +0x08
    float  mLevel;                         // +0x0c
    float  mLevelRange1;                   // +0x10
    float  mLevelRange2;                   // +0x14
    float  mRotationVary;                  // +0x18
};
struct cDecalBoxParams {                   // filter / gradient descriptor
    uint8  mDoFiltering;                   // +0x00
    uint8  mRibbonKernel;                  // +0x01  (mKernelType == 0x12)
    char   pad02[2];
    uint32 mKernel[17];                    // +0x04  kernel weights (0x44 bytes)
    uint32 mGradientCondOp;                // +0x48
    float  mGradientCondN1;                // +0x4c
    float  mGradientCondN2;                // +0x50
    uint32 mGradientFallOffOp;             // +0x54
    float  mGradientFallOffN1;             // +0x58
    float  mGradientFallOffN2;             // +0x5c
};

struct cTerrainEditor {
    float GetWaterLevel();                                // 0x00f678d0
    float GetHeightAt(Vector3 p);                         // 0x00f67aa0
    void  BuildDecalBox(int a2, int a3, int a4, void** outRef,
                        const cDecalFront* front, const cDecalBoxParams* params,
                        int zero, float offset, float rotVary, int zero2, int one);
    // 0x00f6c940
};
cTerrainEditor* TerrainEditor();                          // 0x00f48a70

class cTerrainBrushEffect {
public:
    virtual void Initialize(void*, void*, void*);
    virtual void Dispose();
    virtual void Start(int hardStart);
    virtual int  Stop(int hardStop);
    virtual int  IsRunning();
    virtual void ApplyEffect(float dt, float, cComponentStats*);

    void ApplyGlobal(float intensity, const Matrix3& kernel);   // 0x00f4bcb0
    bool SetParam(int id, float* value, int);                   // 0x00f4b110
    void Imprint(const Vector3& pos, int, int, int, const void* kernel);  // 0x00f4b870
    void SetTransform(void* a, const cTransform* t);            // 0x00f4b6e0

    int mRefCount;                           // +0x04
    int mRefCountPad;                        // +0x08
    cTerrainBrushDescription* mDesc;         // +0x0c
    bool mActive;                            // +0x10
    cTransform mTransform;                   // +0x14
    float mSize;                             // +0x4c
    cTransform mPreviousTransform;           // +0x50
    float mPreviousSize;                     // +0x88
    bool mPreviousValuesInitialized;         // +0x8c
    float mAccumulatedTime;                  // +0x90
    float mLODSizeScale;                     // +0x94
    float mIntensityScale;                   // +0x98
    float mOverallTime;                      // +0x9c
    float mInvLifetime;                      // +0xa0
    float mLifeTime;                         // +0xa4
    bool mDoSpacing;                         // +0xa8
    bool mDoSpacingVary;                     // +0xa9
    float mSpacingVaryVal;                   // +0xac
    float mDistTraveled;                     // +0xb0
    float mUserLevelParm;                    // +0xb4
    float mUserSizeParm;                     // +0xb8
    float mLevelValue;                       // +0xbc
    void* mpTexture;                         // +0xc0
    BrushVertexVector mRibbonBrushList;      // +0xc4
};

// ------------------------------------------------------------------- callees
void* EAAllocate(uint32 size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  EAAllocatorDeallocate(void* p);                                       // 0x00f47380
void* operator new(uint32 size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void  operator delete[](void* p);                                           // 0x00f47380
void  ReleaseRefcounted(void* p);
uint32 Aullshr(uint64 v, int n);                                            // 0x011e08d0

// Inline form of the EA cGmeRefCount release the retail code expands at each
// call site: decrement the count word at +8, then restore-or-barrier.
__forceinline void ReleaseNoRef(void* p)
{
    long* c = (long*)((char*)p + 8);
    _InterlockedExchangeAdd(c, -1);
    long old = _InterlockedExchangeAdd(c, 0);
    if (old < 1)
        _InterlockedExchangeAdd(c, 1);
    else
        _InterlockedExchangeAdd(c, 0);
}

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
    virtual void Read(void* dst, int size);    // slot 12 (0x30)
};
void ReadRaw8(Stream* s, void* dst, int a, int b);   // 0x0093a800
void ReadInt32_(Stream* s, void* dst, int a, int b); // 0x0093a780
void ReadByte_(Stream* s, void* dst, int a);         // 0x0093a6c0
void ReadBool_(Stream* s, void* dst);                // 0x0093ac80
void ReadFloat2(Stream* s, void* dst);               // 0x007d27d0

struct TextureRef { void* p; void Assign(void* src); };      // 0x00576650 (this = destination)
void* Singleton67dd60();                             // 0x0067dd60
float RandomRange(float a, float b);                 // 0x007d45d0
void  DecalBoxBuilder(void* a);                      // 0x00f6c940

extern float DAT_016c8ff0;
extern float DAT_016c8ff4;
extern float DAT_016c8ff8;
extern Matrix3 DAT_016c9020;
extern const float kOne;                             // 0x01485720 (1.0f)
extern const float k9999;                            // 0x0148e61c (9999.0f)
extern const float k0_01;                            // 0x013eb960 (0.01f)
extern const float kNegOne;                          // 0x013eb1bc (-1.0f)
struct VtblObj { void* slot[16]; };
extern VtblObj kGmeRefCountVtbl;                     // 0x013ef094
extern VtblObj kGmeIComponentVtbl;                   // 0x013f21d4
extern VtblObj kBrushCreateVtbl;                     // 0x0148e714
extern VtblObj kBrushCreateVtbl2;                    // 0x0148e710
extern VtblObj kBrushEffectCmdVtbl;                  // 0x0148decc
extern VtblObj kGroupBrushCmdVtbl;                   // 0x0148deb0

// ============================================================ functions =====
// @ 0x00f4aaf0
void cBrushEffectCommand::Execute(cArguments* args)
{
    int argc;
    char** main = args->MainArguments(&argc, 1, 3);
    char* s = *main;
    char* e = s + strlen(s);
    mDescName.assign(s, e);
    mDesc = cTerrainBrushDescription();
    if (argc > 1) {
        void* found = mParser->GetInheritedDescription(main, argc, 0x20);
        if (found)
            mDesc = *(cTerrainBrushDescription*)found;
    }
    mDesc.mWaterLevelIsZero = false;
    if (args->OptionArguments("waterLevelIsZero", 0))
        mDesc.mWaterLevelIsZero = true;
    void** vt = *(void***)mComponent;
    ((void (__thiscall*)(void*, void*))vt[0x8c / 4])(mComponent, this);
}

// @ 0x00f4abc0
void cBrushEffectCommand::Build(char whenZero)
{
    if (whenZero == 0) {
        cTerrainBrushDescription* d =
            (cTerrainBrushDescription*)EAAllocate(0x108,
                "Terrain/TerrainBrushDescription/cTerrainBrushDescription", 0, 0, 0, 0);
        void* p = d ? d->Construct(mDesc) : 0;
        mParser->Install(mDescName.mpBegin, 0x20, p);
    }
}

// @ 0x00f4ac10
void SWARM_TerrainBrushAddCommands(Registrar* groups, Registrar* commands)
{
    cBrushEffectCommand* c =
        new ("ArgScript/BrushEffect", 0, 0, 0, 0) cBrushEffectCommand;
    commands->RegisterKey(&g15b09a4, c);

    c = new ("ArgScript/BrushEffect", 0, 0, 0, 0) cBrushEffectCommand;
    commands->RegisterKey(&g15b09a8, c);

    groups->RegisterGroup(&g15b099c, new ("ArgScript/GroupBrush", 0, 0, 0, 0) cCommandBase);
    groups->RegisterGroup(&g15b09a4, new ("ArgScript/GroupBrush", 0, 0, 0, 0) cCommandBase);
    groups->RegisterGroup(&g15b09a0, new ("ArgScript/GroupBrush", 0, 0, 0, 0) cCommandBase);
    groups->RegisterGroup(&g15b09a8, new ("ArgScript/GroupBrush", 0, 0, 0, 0) cCommandBase);
}

// @ 0x00f4adf0
void ReadTerrainBrushDesc(Stream* stream, int, void* obj)
{
    char* p = (char*)obj;
    stream->Read(p + 0x08, 0x0c);
    ReadRaw8(stream, p + 0x18, 1, 0);
    ReadByte_(stream, p + 0x20, 1);
    ReadBool_(stream, p + 0x21);
    ReadInt32_(stream, p + 0x24, 1, 0);
    ReadInt32_(stream, p + 0x28, 1, 0);
    ReadFloat2(stream, p + 0x2c);
    ReadFloat2(stream, p + 0x40);
    ReadBool_(stream, p + 0x54);
    ReadInt32_(stream, p + 0x58, 1, 0);
    ReadInt32_(stream, p + 0x5c, 1, 0);
    ReadInt32_(stream, p + 0x60, 1, 0);
    stream->Read(p + 0x64, 8);
    ReadInt32_(stream, p + 0x6c, 1, 0);
    ReadInt32_(stream, p + 0x70, 1, 0);
    ReadInt32_(stream, p + 0x74, 1, 0);
    ReadInt32_(stream, p + 0x78, 1, 0);
    ReadInt32_(stream, p + 0x7c, 1, 0);
    ReadBool_(stream, p + 0x80);
    ReadBool_(stream, p + 0x81);
    ReadByte_(stream, p + 0x82, 1);
    ReadByte_(stream, p + 0x83, 1);
    ReadInt32_(stream, p + 0x84, 1, 0);
    ReadFloat2(stream, p + 0x88);
    ReadInt32_(stream, p + 0x9c, 1, 0);
    ReadByte_(stream, p + 0xa0, 1);
    ReadInt32_(stream, p + 0xa4, 1, 0);
    ReadInt32_(stream, p + 0xa8, 1, 0);
    ReadByte_(stream, p + 0xac, 1);
    ReadInt32_(stream, p + 0xb0, 1, 0);
    ReadInt32_(stream, p + 0xb4, 1, 0);
    ReadByte_(stream, p + 0xb8, 1);
    ReadInt32_(stream, p + 0xbc, 1, 0);
    ReadInt32_(stream, p + 0xc0, 1, 0);
    ReadByte_(stream, p + 0xc4, 1);
    ReadInt32_(stream, p + 0xc8, 1, 0);
    ReadInt32_(stream, p + 0xcc, 1, 0);
    ReadBool_(stream, p + 0xd0);
    stream->Read(p + 0xd4, 0x0c);
    stream->Read(p + 0xe0, 0x0c);
    ReadBool_(stream, p + 0xec);
    ReadInt32_(stream, p + 0xf0, 1, 0);
    ReadInt32_(stream, p + 0xf4, 1, 0);
    ReadInt32_(stream, p + 0xf8, 1, 0);
    ReadInt32_(stream, p + 0xfc, 1, 0);
    ReadBool_(stream, p + 0x100);
}

// @ 0x00f4b110
bool cTerrainBrushEffect::SetParam(int id, float* value, int)
{
    switch (id) {
    case 4:
        mIntensityScale = *value;
        return true;
    case 0x15:
        mUserLevelParm = *value;
        return true;
    case 0x16:
        mUserSizeParm = *value;
        return true;
    }
    return false;
}

// @ 0x00f4b180
cBrushVertex* BrushVertexVector::back()
{
    return mpEnd - 1;
}

// @ 0x00f4b190
struct BrushBigElem { uint32 v[0x71]; };
BrushBigElem* CopyElemsBackward(BrushBigElem* first, BrushBigElem* last, BrushBigElem* dst)
{
    while (last != first) {
        --last;
        --dst;
        *dst = *last;
    }
    return dst;
}

// @ 0x00f4b1d0
struct F7 { float a, b, c, d, e, f, g; };
F7* CopyF7(F7* first, F7* last, F7* dst)
{
    for (; first != last; ++first) {
        if (dst) {
            dst->a = first->a;
            dst->b = first->b;
            dst->c = first->c;
            dst->d = first->d;
            dst->e = first->e;
            dst->f = first->f;
            dst->g = first->g;
        }
        ++dst;
    }
    return dst;
}

// @ 0x00f4b220
SWARM_TerrainBrushCreate::SWARM_TerrainBrushCreate(void* p)
{
    vtbl2 = (void*)&kGmeRefCountVtbl;
    mRefTarget = 0;
    vtbl = (void*)&kBrushCreateVtbl;
    vtbl2 = (void*)&kBrushCreateVtbl2;
    mParam = p;
    mFlag10 = 0;
    w14 = 0;
    w16 = 0;
    mPos.x = DAT_016c8ff0;
    mPos.y = DAT_016c8ff4;
    mPos.z = DAT_016c8ff8;
    mSize = 1.0f;
    mRot.Assign(&DAT_016c9020);
    mF4c = 1.0f;
    w52 = 0;
    w50 = 0;
    mPos2.x = DAT_016c8ff0;
    mPos2.y = DAT_016c8ff4;
    mPos2.z = DAT_016c8ff8;
    mSize2 = 1.0f;
    mRot2.Assign(&DAT_016c9020);
    mF88 = 1.0f;
    mF94 = 1.0f;
    mF98 = 1.0f;
    mFa0 = 1.0f;
    mFa4 = 1.0f;
    mFac = 1.0f;
    mFlag8c = 0;
    mFa8 = 0;
    mF90 = 0.0f;
    mF9c = 0.0f;
    mFa9 = 1;
    mFb0 = 0.0f;
    mFb4 = k9999;
    mFb8 = k9999;
    mFbc = 0.0f;
    mPc0 = 0;
    mPc4 = 0;
    mCc8 = 0;
    mCcc = 0;
}

// @ 0x00f4b3a0
SWARM_TerrainBrushCreate::~SWARM_TerrainBrushCreate()
{
    vtbl = (void*)&kBrushCreateVtbl;
    vtbl2 = (void*)&kBrushCreateVtbl2;
    if (mPc4 != 0 && *(int*)((char*)mPc4 - 4) != 0)
        EAAllocatorDeallocate(mPc4);
    if (mPc0 != 0)
        ReleaseNoRef(mPc0);
    vtbl = (void*)&kGmeIComponentVtbl;
    vtbl2 = (void*)&kGmeRefCountVtbl;
}

// @ 0x00f4b420
void cTerrainBrushEffect::Initialize(void*, void*, void*)
{
    float epsilon = 0.0001f;                    // xmm0, loaded before the deref
    cTerrainBrushDescription* d = mDesc;
    mLifeTime = d->mLifetime;
    float* denom = &d->mLifetime;
    if (!(d->mLifetime > epsilon))              // movss xmm1,[ecx]; comiss; ja
        denom = &epsilon;
    mInvLifetime = 1.0f / *denom;
    mDoSpacing = (d->mSpacingCurve.mpBegin != d->mSpacingCurve.mpEnd);
    uint32 texLo = d->mTexture[0];              // mov ecx, [eax+0x18]
    if ((texLo & d->mTexture[1]) != 0xffffffff) {
        void* mgr = Singleton67dd60();
        cTerrainBrushDescription* d2 = mDesc;
        uint64 tex = *(uint64*)&d2->mTexture[0];
        uint32 hi = (uint32)(tex >> 32);
        void** vtbl = *(void***)mgr;
        void* res = ((void* (__thiscall*)(void*, uint32, uint32, uint32))vtbl[0x20 / 4])(mgr, d2->mTexture[0], hi, 0);
        ((TextureRef*)&mpTexture)->Assign(res);
    }
}

// @ 0x00f4b4c0
struct BrushHugeElem { uint32 v[0x71]; };
void CopyElemsForward(BrushHugeElem* first, BrushHugeElem* last, BrushHugeElem* dst)
{
    for (; first != last; ++first) {
        if (dst)
            *dst = *first;
        ++dst;
    }
}

// @ 0x00f4b6e0
void cTerrainBrushEffect::SetTransform(void* p, const cTransform* t)
{
    cTransform tmp;
    tmp.mFlags = t->mFlags;
    tmp.mModificationCount = t->mModificationCount;
    tmp.mTranslation.x = t->mTranslation.x;
    tmp.mTranslation.y = t->mTranslation.y;
    tmp.mTranslation.z = t->mTranslation.z;
    tmp.mScale = t->mScale;
    tmp.mRotation.Assign(&t->mRotation);
    tmp.PreTransformBy((const cTransform*)p);
    mPreviousTransform = mTransform;
    mPreviousSize = mSize;
    mSize = tmp.mScale;
    mTransform = tmp;
    if (!mPreviousValuesInitialized) {
        mPreviousTransform = mTransform;
        mPreviousSize = mSize;
        float dx = tmp.mTranslation.x, dy = tmp.mTranslation.y, dz = tmp.mTranslation.z;
        if (sqrtf(dz * dz + dy * dy + dx * dx) > 0.01f) {
            mPreviousValuesInitialized = true;
            if (mDesc->mDrawMode == 3) {
                float v = mUserLevelParm;
                if (v == 9999.0f) {
                    float r = RandomRange(1.0f, mDesc->mLevelVary);
                    float lv = mDesc->mLevelValue;
                    if (lv < -1.0f) {
                        mLevelValue = TerrainEditor()->GetHeightAt(tmp.mTranslation) * r;
                    } else {
                        mLevelValue = lv * r;
                    }
                } else {
                    mLevelValue = v;
                }
            }
        }
    }
}

// @ 0x00f4b870
void cTerrainBrushEffect::Imprint(const Vector3& pos, int a2, int a3, int a4, const void* kernel)
{
    float offset = 0.0f;
    if (mDesc->mWaterLevelIsZero) {
        float w = TerrainEditor()->GetWaterLevel();
        offset = (w + w) - 1.0f;
    }

    void* outRef = 0;
    ((TextureRef*)&outRef)->Assign(mpTexture);

    cTerrainBrushDescription* d = mDesc;

    cDecalFront front;
    front.mUseNoise      = (mpTexture == 0 || d->mDoGaussian) ? 1 : 0;
    front.mFilterGlobal  = d->mFilterGlobal ? 1 : 0;
    front.mDoCubeMap     = d->mDoCubeMap ? 1 : 0;
    front.mGaussianSlope = d->mGaussianSlope;
    front.mDrawMode      = d->mDrawMode;
    front.mLevel         = mLevelValue + offset;
    front.mLevelRange1   = d->mLevelRangeValue1;
    front.mLevelRange2   = d->mLevelRangeValue2;
    front.mRotationVary  = d->mRotVary.x;
    if (d->mDrawMode != 5 && d->mDrawMode != 6) {
        front.mLevelRange1 += offset;
        front.mLevelRange2 += offset;
    }

    cDecalBoxParams params;
    params.mDoFiltering  = d->mDoFiltering ? 1 : 0;
    params.mRibbonKernel = (d->mDoFiltering && d->mKernelType == 0x12) ? 1 : 0;
    for (int i = 0; i < 17; ++i)
        params.mKernel[i] = ((const uint32*)kernel)[i];
    params.mGradientCondOp    = d->mGradientCondOp;
    params.mGradientCondN1    = d->mGradientCondN1;
    params.mGradientCondN2    = d->mGradientCondN2;
    params.mGradientFallOffOp = d->mGradientFallOffOp;
    params.mGradientFallOffN1 = d->mGradientFallOffN1;
    params.mGradientFallOffN2 = d->mGradientFallOffN2;

    (void)pos;
    TerrainEditor()->BuildDecalBox(a2, a3, a4, &outRef, &front, &params, 0, offset,
                                   d->mRotVary.x, 0, 1);

    if (outRef != 0)
        ReleaseNoRef(outRef);
}
