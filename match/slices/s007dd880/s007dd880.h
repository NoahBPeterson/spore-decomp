// Shared declarations for the SP::cSmoothCameraController slices (s007dd880, s007de7d0).
// Retail layout (size 0x3a4). Differs from the 2008 PDB: every eastl vector member is followed by one
// extra dword, so offsets are PDB+4 per preceding vector (+0x18 after mMaxPitches) and +0x20 from
// mCurrentOrientation on.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
#pragma once
#include "types.h"

typedef unsigned int size_type;

// ---- EA allocator / memory (masked relocations) ----
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* __cdecl EA_Alloc(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
void  __cdecl EA_Free(void* p) throw();                                                                                       // 0x00f47380
extern "C" void* __cdecl memset(void*, int, size_t);
#pragma intrinsic(memset)
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
inline void* operator new(size_t, void* p) { return p; }

// ---- eastl::vector<float, sp_vector_allocator>, 5 words (0x14 bytes) ----
struct FloatVec {
    float* mpBegin; float* mpEnd; float* mpCapacity; const char* mpName; int mpAllocExtra;

    FloatVec() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    // vector(n): allocate n floats and zero-fill (variable n compiles to `rep stosd`)
    __forceinline FloatVec(size_type n)
    {
        mpBegin = n ? (float*)EA_Alloc(n * 4, "App", 0, 0, ALLOC_FILE, 0xd1) : 0;
        mpCapacity = mpBegin + n;
        for (size_type i = 0; i < n; ++i) mpBegin[i] = 0.0f;
        mpEnd = mpBegin + n;
    }
    // same, for compile-time sizes (inline memset: integer-register zero stores)
    __forceinline FloatVec(size_type n, int)
    {
        mpBegin = n ? (float*)EA_Alloc(n * 4, "App", 0, 0, ALLOC_FILE, 0xd1) : 0;
        mpCapacity = mpBegin + n;
        memset(mpBegin, 0, n * 4);
        mpEnd = mpBegin + n;
    }
    ~FloatVec() { if (mpBegin) { if (((int*)mpBegin)[-1]) EA_Free(mpBegin); } }
    float& operator[](size_type i) { return mpBegin[i]; }
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    void DoInsertValue(float* pos, const float& v);              // 0x00455660 (push_back slow path)
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) ::new((void*)mpEnd++) float(v);
        else DoInsertValue(mpEnd, v);
    }
    void erase_all()
    {
        float* first = mpBegin; float* last = mpEnd;
        memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
    }
};

// ---- property records (cPropertyList::GetProperty result) ----
extern float    g_defaultFloat;     // 0x015d1168
extern unsigned g_defaultUInt;      // 0x015d1164
struct Property {
    void* data; unsigned count; unsigned short flags; unsigned short type;
    void* GetStorage() { if (flags & 0x30) return data; return type ? (void*)this : (void*)0; }
    unsigned GetArrayCount() { if (flags & 0x30) return count; return type != 0; }
    float* GetFloat() { if (type == 0xd || type == 0x10) return (float*)GetStorage(); return &g_defaultFloat; }
    unsigned* GetUInt() { if (type == 0xa || type == 0x10) return (unsigned*)GetStorage(); return &g_defaultUInt; }
};
struct cPropertyList {
    virtual void AddRef();                  // 0x00
    virtual void Release();                 // 0x04
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual bool HasProperty(unsigned id);  // 0x1c
    virtual void s8(); virtual void s9();
    virtual Property* GetProperty(unsigned id); // 0x28
};

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct tLerpScalar  { float mCurrent; float mTarget; int mSteps; float mMinChange;      // 0x10
    tLerpScalar() { memset(this, 0, 16); } };
struct tLerpVector3 { Vec3 mCurrent; Vec3 mTarget; int mSteps; float mMinChange; };        // 0x20
struct tLerpQuaternion { Quat mCurrent; Quat mTarget; int mSteps; float mMinChange; };    // 0x28

struct tSavedCameraPosition {                                                              // 0x38
    bool mValid; int mCurrentZoomLevel; float mDistance; int mCurrentOrientation;
    float mHeading, mNearClip, mFarClip, mFOV, mPitchParam;
    Vec3 mSubjectPosition; int mFloorLevel; int mWallMode;
};

struct __declspec(novtable) cICameraControllerBase { virtual void slot0(); };
struct cIHandlerBase { cIHandlerBase() {} virtual ~cIHandlerBase() {} virtual void hslot0(); };
struct cRefCountBase { cRefCountBase() : mRefCount(0) {} virtual ~cRefCountBase() {} virtual void rslot0(); int mRefCount; };

struct AutoRefCountPL {
    cPropertyList* mpObject;
    AutoRefCountPL(cPropertyList* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCountPL() { if (mpObject) mpObject->Release(); }
    cPropertyList* operator->() const { return mpObject; }
};

struct cSmoothCameraController : cICameraControllerBase, cIHandlerBase, cRefCountBase {
    // vtable slot N is at byte offset N*4 (slot 0 = cICameraControllerBase::slot0)
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
    virtual void ConfigUpdated();   // 0x50  @ 0x007dd880
    virtual void v21();
    virtual void Reset();                // 0x58  @ 0x007de7d0
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26_Unk(int);           // 0x68
    virtual void v27();
    virtual void SetZoomLevels(const FloatVec& zoom, const FloatVec& fov);             // 0x70 @ 0x007df6a0
    virtual void SetCurrentZoomLevel(int level);                                       // 0x74
    virtual void SetClipPlanes(const FloatVec& nearClip, const FloatVec& farClip);     // 0x78 @ 0x007df6d0
    virtual void SetPitchAngles(const FloatVec& minDeg, const FloatVec& maxDeg);      // 0x7c @ 0x007df230
    virtual void v32();
    virtual void SetOrientations(const FloatVec& v);                                   // 0x84 @ 0x007df700
    virtual void SetCurrentDiscreteOrientation(int i);                                 // 0x88
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void SetEdgeConstraints(float a, float b, float c, float d);              // 0xac @ 0x007df330
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49_Refresh();           // 0xc4
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();

    AutoRefCountPL mConfig;               // +0x10
    FloatVec mEdgeConstraints; // +0x14
    int mCurrentZoomLevel;                // +0x28
    float mContinuousZoomDistance;        // +0x2c
    FloatVec mZoomLevels;      // +0x30
    FloatVec mNearClipPlanes;  // +0x44
    FloatVec mFarClipPlanes;   // +0x58
    FloatVec mMinPitches;      // +0x6c
    FloatVec mMaxPitches;      // +0x80
    float mViewSlope;                     // +0x94
    tLerpScalar mBufferedHeading;         // +0x98
    tLerpScalar mBufferedDistanceAlongCurve; // +0xa8
    tLerpScalar mBufferedNearClip;        // +0xb8
    tLerpScalar mBufferedFarClip;         // +0xc8
    tLerpScalar mBufferedFOV;             // +0xd8
    tLerpScalar mBufferedPitchParam;      // +0xe8
    tLerpVector3 mBufferedSubjectPosition; // +0xf8
    tLerpVector3 mBufferedLookAtPosition;  // +0x118
    FloatVec mFOVLevels;     // +0x138
    FloatVec mOrientations;   // +0x14c
    int mCurrentOrientation;              // +0x160
    Vec3 mDraggedVelocity;                // +0x164
    unsigned mPositionInterpolationSteps; // +0x170
    float mTranslationInputVelocity;      // +0x174
    Vec3 mxyzSubjectOffset;               // +0x178
    tLerpQuaternion mRelativeOrientation; // +0x184
    float mHeadingRelative;               // +0x1ac
    bool mTracking, mReadFromStream, mAdjustablePitch, mbInModalDialogLoop; // +0x1b0
    int mStartMouseWheelLevel;            // +0x1b4
    tLerpScalar mKeyboardRotation;        // +0x1b8
    tLerpScalar mKeyboardZoomDelta;       // +0x1c8
    tLerpVector3 mKeyboardTranslation;    // +0x1d8
    float mKeyboardRotationSpeed;         // +0x1f8
    float mKeyboardZoomSpeed;             // +0x1fc
    float mKeyboardZoomScale;             // +0x200
    float mKeyboardTranslationSpeed;      // +0x204
    tSavedCameraPosition mCameraPositions[7]; // +0x208
    float mSubjectTrackingDeadZoneMagnitude;  // +0x390
    float mRotationPitchRatioMax;         // +0x394
    float mCameraPitchScaling;            // +0x398
    float mContinuousRotationScaling;     // +0x39c
    float mMaxRotationDelta;              // +0x3a0

    cSmoothCameraController(cPropertyList* config);   // @ 0x007df450
};
