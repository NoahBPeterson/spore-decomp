// SP::cTerrainBrushEffect::ApplyEffect  @ 0x00f4c300  (vtable 0x0148e714 slot 5, +0x14)  -- byte-exact
//
// Unoptimized (/Od /Ob1 /arch:SSE /fp:fast) Swarm component update for terrain brushes.
// Layouts: cTerrainBrushEffect from the 2008 PDB (matches retail offsets);
// cTerrainBrushDescription is the PDB layout shifted by the retail 0x14-byte
// sp_vector (mSizeCurve 0x2c, mIntensityCurve 0x40, mSpacingCurve 0x88, ...).
// cMapKernel (0x44 bytes) from the PDB; the kernel presets are static tables.
//
// Local names: /Od orders a scope's locals by a 16-bucket hash of the NAME (type does not matter),
// later-declared first inside a bucket.  The odd names (oldUp5, heightOffset7, ...) were chosen with a
// bucket ruler (work/match/scratch_s00f4c300_bucket.py) so the frame matches; ScratchSlots<N> stands
// for the frames of inline callees the original compiler declined.

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

// ---------------------------------------------------------------- math types
struct Vec3Tmp;  // value returned by the out-of-line Vector3 operators

struct Vector3 {
    float x, y, z;
    Vector3();                       // 0x00572590 (empty ctor, returns this)
    Vector3(const Vector3& o);       // 0x004098a0
    Vector3(const Vec3Tmp& o);       // 0x004098a0 (same body)
    float& operator[](int i);        // 0x00572580
};
struct Vec3Tmp { float x, y, z; Vec3Tmp(); };

struct Vector2 {
    float x, y;
    Vector2(float x_, float y_);     // 0x00508780
};

struct Quaternion {
    float x, y, z, w;
    Quaternion();                                    // 0x00572590
    Quaternion(float x_, float y_, float z_, float w_);  // 0x00628970
};

struct Matrix3 {
    float m[9];
    Matrix3();                                   // 0x00572590
    Matrix3& operator=(const Matrix3& o);        // 0x005a88a0
};

struct cTransform {                  // EA::Swarm::cTransform, 0x38
    uint16 mFlags;
    uint16 mModificationCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;
    const Vector3& GetOffset() const;            // 0x006e64f0
    const Matrix3& GetRotation() const;          // 0x009892e0
    cTransform& operator=(const cTransform& o);  // 0x00537dc0
};

// free math helpers (cdecl)
float VectorLength(const Vector3& v);                                   // 0x0040ae50
float Dot3(const Vector3& v);                                           // 0x004885d0
Vector3 normalized_safe(const Vector3& v);                              // 0x00449c20
Vector3 Normalize(const Vector3& v);                                    // 0x00436ce0
Vec3Tmp operator-(const Vector3& a, const Vector3& b);                  // 0x0041db10
Vec3Tmp RotateVector(const Vector3& v, const Quaternion& q);            // 0x0059aed0
Quaternion MatrixToQuaternion(const Matrix3& m);                        // 0x0046d660
Quaternion QuaternionFromDirections(const Vector3& from, const Vector3& to);  // 0x00698180
Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);    // 0x005b26f0
extern const Quaternion kQuaternionIdentity;                            // 0x015b0a48

const float& Min(const float& a, const float& b);   // 0x0059c010
float Clamp01(float v);                             // 0x005a6e00
float Clamp(float v, float lo, float hi);           // 0x0059ab50
float Abs(float v);                                 // 0x00571ce0
int   FloatToInt(float v);                          // 0x00684be0 (truncate)
int   RoundToInt(float v);                          // 0x005e4d30 (cvtss2si)
float RandomRange(float a, float b);                // 0x007d45d0

struct RandomLinearCongruential {
    double RandomDoubleUniform();                   // 0x009360d0
};
RandomLinearCongruential* GetRandom();              // 0x007dad70

struct cTerrainEditor {
    float GetWaterLevel();                          // 0x00f678d0
};
cTerrainEditor* TerrainEditor();                    // 0x00f48a70

// ---------------------------------------------------------------- containers
struct FloatVector {                 // eastl::vector<float, sp_vector_allocator> (retail 0x14)
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    uint32 mAllocator[2];
    uint32 size() const;                            // 0x00572c90
    const float& front() const;                     // 0x00fc8380
    const float& operator[](uint32 n) const { return mpBegin[n]; }
};

struct cBrushVertex {                // SP::cBrushVertex, 0x1c
    Vector3 mPosition;
    Vector2 mUV;
    float mIntensity;
    float mSize;
};

struct BrushVertexVector {           // eastl::vector<cBrushVertex, sp_vector_allocator>
    cBrushVertex* mpBegin;
    cBrushVertex* mpEnd;
    cBrushVertex* mpCapacity;
    uint32 mAllocator[2];
    uint32 size() const;                            // 0x00f4b160
    cBrushVertex& back();                           // 0x00f4b180
    void push_back();                               // 0x00f4c150
};

// ---------------------------------------------------------------- brush data
struct cMapKernel {                  // SP::cMapKernel, 0x44
    float mArray[9];
    float mNormalizer;
    uint32 mOp;
    uint32 mCondOp;
    float mCondN1;
    float mCondN2;
    uint32 mFallOffOp;
    float mFallOffN1;
    float mFallOffN2;
};

extern const cMapKernel kKernelSmooth;      // 0x0148e2f8
extern const cMapKernel kKernelMedian;      // 0x0148e340
extern const cMapKernel kKernelLowPass1;    // 0x0148e388
extern const cMapKernel kKernelLowPass2;    // 0x0148e3d0
extern const cMapKernel kKernelLowPass3;    // 0x0148e418
extern const cMapKernel kKernelLowPass4;    // 0x0148e460
extern const cMapKernel kKernelLowPass5;    // 0x0148e4a8
extern const cMapKernel kKernelHighPass1;   // 0x0148e4f0
extern const cMapKernel kKernelHighPass2;   // 0x0148e538
extern const cMapKernel kKernelHighPass3;   // 0x0148e588
extern const cMapKernel kKernelHighPass4;   // 0x0148e5d8
extern const cMapKernel kKernelEdge1;       // 0x0148e620
extern const cMapKernel kKernelEdge2;       // 0x0148e668
extern const cMapKernel kKernelEdge3;       // 0x0148e6b0
extern const cMapKernel kKernelAdd;         // 0x0148e268
extern const cMapKernel kKernelLevel;       // 0x0148e2b0

struct cTerrainBrushDescription {    // SP::cTerrainBrushDescription (retail layout)
    uint32 mDescriptionBase[2];      // +0x00 EA::Swarm::cDescription
    float mLocation[3];              // +0x08
    uint32 pad14;                    // +0x14
    uint32 mTexture[2];              // +0x18
    uint8 mDrawMode;                 // +0x20
    bool mDoGaussian;                // +0x21
    float mGaussianSlope;            // +0x24
    float mLifetime;                 // +0x28
    FloatVector mSizeCurve;          // +0x2c
    FloatVector mIntensityCurve;     // +0x40
    bool mWaterLevelIsZero;          // +0x54
    float mIntensityVary;            // +0x58
    float mSizeVary;                 // +0x5c
    float mRotationVary;             // +0x60
    float mTextureOffset[2];         // +0x64
    float mLevelValue;               // +0x6c
    float mLevelVary;                // +0x70
    float mLevelRangeValue1;         // +0x74
    float mLevelRangeValue2;         // +0x78
    float mImprintsPerSecond;        // +0x7c
    bool mDoFiltering;               // +0x80
    bool mFilterGlobal;              // +0x81
    uint8 mKernelType;               // +0x82
    uint8 mKernelOp;                 // +0x83
    float mDeltaAmount;              // +0x84
    FloatVector mSpacingCurve;       // +0x88
    float mSpacingVary;              // +0x9c
    uint8 mCondOp;                   // +0xa0
    float mCondN1;                   // +0xa4
    float mCondN2;                   // +0xa8
    uint8 mFallOffOp;                // +0xac
    float mFallOffN1;                // +0xb0
    float mFallOffN2;                // +0xb4
    uint8 mGradientCondOp;           // +0xb8
    float mGradientCondN1;           // +0xbc
    float mGradientCondN2;           // +0xc0
    uint8 mGradientFallOffOp;        // +0xc4
    float mGradientFallOffN1;        // +0xc8
    float mGradientFallOffN2;        // +0xcc
    bool mDoCubeMap;                 // +0xd0
    Vector3 mRot;                    // +0xd4
    Vector3 mRotVary;                // +0xe0
    bool mRibbonBrush;               // +0xec
};

struct cComponentStats;

class cTerrainBrushEffect {          // SP::cTerrainBrushEffect : EA::Swarm::cComponentBase
public:
    virtual void Initialize(void*, void*, void*);
    virtual void Dispose();
    virtual void Start(int hardStart);
    virtual int  Stop(int hardStop);                // +0x0c
    virtual int  IsRunning();
    virtual void ApplyEffect(float dt, float, cComponentStats*);  // +0x14

    void ApplyGlobal(float intensity, const cMapKernel& kernel);  // 0x00f4bcb0
    void Imprint(const Vector3& pos, const Quaternion& rot, float size, float intensity,
                 const cMapKernel& kernel);                       // 0x00f4b870

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

template <int N> inline void ScratchSlots() { uint32 s[N]; }   // frame of a declined inline callee

// Piecewise-linear sample of a curve at t in [0,1].
__forceinline float CurveValue(const FloatVector& curve, float t)
{
    uint32 n = curve.size() - 1;
    if (n == 0)
        return curve[0];
    t *= n;
    int index = FloatToInt(t);
    t -= index;
    if (t > 0.0f) {
        const float& lo2 = curve[index];
        const float& hi = curve[index + 1];
        return (hi - curve[index]) * t + lo2;
    } else
        return curve[index];
}

__forceinline bool IsClose(const Vector3& a, const Vector3& b)
{
    return Abs(a.x - b.x) < 0.001 && Abs(a.y - b.y) < 0.001 && Abs(a.z - b.z) < 0.001;
}

// @ 0x00f4c300
void cTerrainBrushEffect::ApplyEffect(float dt, float, cComponentStats*)
{
    Quaternion spare;
    cMapKernel mapKernel;

    if (mDesc->mDoFiltering) {
        switch (mDesc->mKernelType) {
        case 1:  mapKernel = kKernelSmooth;    break;
        case 2:  mapKernel = kKernelMedian;    break;
        case 3:  mapKernel = kKernelLowPass1;  break;
        case 4:  mapKernel = kKernelLowPass2;  break;
        case 5:  mapKernel = kKernelLowPass3;  break;
        case 6:  mapKernel = kKernelLowPass4;  break;
        case 7:  mapKernel = kKernelLowPass5;  break;
        case 8:  mapKernel = kKernelHighPass1; mapKernel.mOp = 6; break;
        case 9:  mapKernel = kKernelHighPass2; mapKernel.mOp = 6; break;
        case 10: mapKernel = kKernelHighPass3; mapKernel.mOp = 6; break;
        case 11: mapKernel = kKernelHighPass4; break;
        case 12: mapKernel = kKernelEdge1;     mapKernel.mOp = 1; break;
        case 13: mapKernel = kKernelEdge2;     mapKernel.mOp = 1; break;
        case 14: mapKernel = kKernelEdge3;     mapKernel.mOp = 1; break;
        case 15:
            mapKernel = kKernelAdd;
            mapKernel.mArray[4] = mDesc->mDeltaAmount;
            break;
        case 20:
            mapKernel = kKernelLevel;
            mapKernel.mArray[4] = mDesc->mDeltaAmount;
            break;
        case 16:
            mapKernel = kKernelAdd;
            mapKernel.mArray[4] = -mDesc->mDeltaAmount;
            break;
        case 18: break;
        case 19: break;
        case 17: break;
        default:
            return;
        }
        switch (mDesc->mKernelOp) {
        case 1: mapKernel.mOp = 0; break;
        case 2: mapKernel.mOp = 1; break;
        case 3: mapKernel.mOp = 6; break;
        }
    }

    float heightOffset7 = 0.0f;
    float seaLevelQ = 0.0f;
    if (mDesc->mWaterLevelIsZero) {
        cTerrainEditor* terrainEditor = TerrainEditor();
        seaLevelQ = terrainEditor->GetWaterLevel() * 2.0f - 1.0f;
        heightOffset7 = terrainEditor->GetWaterLevel() - 0.5f;
    }
    mapKernel.mCondOp = mDesc->mCondOp;
    mapKernel.mCondN1 = mDesc->mCondN1 + heightOffset7;
    mapKernel.mCondN2 = mDesc->mCondN2 + heightOffset7;
    mapKernel.mFallOffOp = mDesc->mFallOffOp;
    mapKernel.mFallOffN1 = mDesc->mFallOffN1 + heightOffset7;
    mapKernel.mFallOffN2 = mDesc->mFallOffN2 + heightOffset7;

    if (mDesc->mFilterGlobal || mDesc->mDoCubeMap) {
        float intensityRand = RandomRange(1.0f, mDesc->mIntensityVary);
        float intensity = intensityRand * mDesc->mIntensityCurve.front() * mIntensityScale;
        GetRandom()->RandomDoubleUniform();
        ApplyGlobal(intensity, mapKernel);
        Stop(0);
        return;
    }

    float elapsed = Min(dt, 1.0f);
    float accumTime2 = mAccumulatedTime + elapsed;
    float stepTime = 1.0f / mDesc->mImprintsPerSecond;
    int dummy = 0;
    uint32 nImprints = RoundToInt(accumTime2 * mDesc->mImprintsPerSecond);

    Vector3 oldUp5(mPreviousTransform.GetOffset());
    Vector3 curNormal7 = normalized_safe(mTransform.GetOffset());
    if (VectorLength(oldUp5) > 0.0001f)
        oldUp5 = Normalize(oldUp5);
    else
        oldUp5 = curNormal7;

    Matrix3 mat2;
    Quaternion rotPrev;
    Quaternion newRotation;
    Quaternion dirRotation;
    mat2 = mPreviousTransform.GetRotation();
    rotPrev = MatrixToQuaternion(mat2);
    mat2 = mTransform.GetRotation();
    newRotation = MatrixToQuaternion(mat2);
    if (Dot3(oldUp5) < 1.5258789e-05f || Dot3(curNormal7) < 1.5258789e-05f)
        dirRotation = kQuaternionIdentity;
    else
        dirRotation = QuaternionFromDirections(oldUp5, curNormal7);

    float invDt1 = 1.0f / elapsed;
    float travel = VectorLength(curNormal7 - oldUp5) * 500.0f;
    float spacingParam0 = 0.0f;
    float spacingStep3 = 0.0f;

    if (mDoSpacing) {
        mPreviousTransform = mTransform;
        if (mDoSpacingVary) {
            mDoSpacingVary = false;
            mSpacingVaryVal = RandomRange(1.0f, mDesc->mSpacingVary);
        }
        ScratchSlots<19>();
        float size = CurveValue(mDesc->mSizeCurve, 0.0f);
        ScratchSlots<1>();
        if (mUserSizeParm != 9999.0f)
            size = mUserSizeParm;
        float spacingVal = mSpacingVaryVal *
                        CurveValue(mDesc->mSpacingCurve, Clamp01(accumTime2 * mInvLifetime));
        float spacingDistance = size * spacingVal * mSize;
        if (mDistTraveled + travel >= spacingDistance) {
            nImprints = RoundToInt((mDistTraveled + travel) / spacingDistance);
            mDoSpacingVary = true;
            if (travel > 0.0f) {
                spacingParam0 = (spacingDistance - mDistTraveled) / travel;
                spacingStep3 = spacingDistance / travel;
            }
            mDistTraveled = mDistTraveled + travel;
            mDistTraveled = mDistTraveled - nImprints * spacingDistance;
            if (nImprints > 0)
                stepTime = elapsed / nImprints;
        } else {
            mDistTraveled = mDistTraveled + travel;
            nImprints = 0;
        }
    }

    for (uint32 i = 0; i < nImprints; i++) {
        mOverallTime = mOverallTime + stepTime;
        float age = mOverallTime * mInvLifetime;
        if (age > 1.0f) {
            Stop(0);
            return;
        }
        float stepStart = i * stepTime;
        float blend = (stepStart - mAccumulatedTime) * invDt1;
        if (mDoSpacing) {
            blend = spacingParam0;
            spacingParam0 = spacingParam0 + spacingStep3;
        }
        blend = Clamp(blend, 0.0f, 1.0f);

        float intensityVary = RandomRange(1.0f, mDesc->mIntensityVary);
        float intensity = intensityVary * CurveValue(mDesc->mIntensityCurve, age) * mIntensityScale;
        float sizeVary = RandomRange(1.0f, mDesc->mSizeVary);
        float size = sizeVary * CurveValue(mDesc->mSizeCurve, age) * mSize * mLODSizeScale;
        ScratchSlots<8>();
        if (mUserSizeParm != 9999.0f)
            size = mUserSizeParm;
        if (mUserLevelParm != 9999.0f)
            mLevelValue = mUserLevelParm;

        Quaternion imprintRot;
        Quaternion upBlend;
        Quaternion qIdentity(0.0f, 0.0f, 0.0f, 1.0f);
        if (mDesc->mRot[0] != 0.0f || mDesc->mRot[1] != 0.0f || mDesc->mRot[2] != 0.0f) {
            Vector3 randomRot;
            randomRot[0] = RandomRange(mDesc->mRot[0], mDesc->mRotVary[0]);
            randomRot[1] = RandomRange(mDesc->mRot[0], mDesc->mRotVary[1]);
            randomRot[2] = RandomRange(mDesc->mRot[0], mDesc->mRotVary[2]);
        }

        if (blend < 0.0001f) {
            imprintRot = rotPrev;
            upBlend = qIdentity;
        } else if (blend > 0.9999f) {
            imprintRot = newRotation;
            upBlend = dirRotation;
        } else {
            imprintRot = Slerp(rotPrev, newRotation, blend);
            upBlend = Slerp(qIdentity, dirRotation, blend);
        }

        Vector3 position(RotateVector(mPreviousTransform.GetOffset(), upBlend));
        if (!mDesc->mRibbonBrush) {
            Imprint(position, imprintRot, size, intensity, mapKernel);
        } else if (!mRibbonBrushList.size() || !IsClose(position, mRibbonBrushList.back().mPosition)) {
            ScratchSlots<8>();
            mRibbonBrushList.push_back();
            cBrushVertex* vertex = &mRibbonBrushList.back();
            vertex->mPosition = position;
            vertex->mUV = Vector2(0.0f, 0.0f);
            vertex->mIntensity = intensity;
            vertex->mSize = size;
        }
    }

    mAccumulatedTime = mAccumulatedTime + elapsed - nImprints * stepTime;
}
