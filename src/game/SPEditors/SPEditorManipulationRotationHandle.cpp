// src/game/SPEditors/SPEditorManipulationRotationHandle.cpp -- migrated from slice(s) s005b5a30, s005b5110, s005b4170 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorManipulationRotationHandle.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cViewer.h"
#include "SP/cSPEditorManipulationObject.h"
#include "SP/cSPEditorSkinManager.h"
#include <math.h>
#include "EA/ResourceMan/Key.h"
#include "SP/cSPEditorHandle.h"
#include "SP/cSPEditorHandleRotationRing.h"
#include "SP/cSPEditorModel.h"
#include <string.h>
#include <stddef.h>
#ifndef SP_EDITOR_MANIP_SCAFFOLD_H
#endif  // SP_EDITOR_MANIP_SCAFFOLD_H

// ---- items of slice s005b4170 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SPin50 {
  char pad_0[4];
  bool mChanged;   // +0x4
  char pad_5[0x20 - 0x5];
  void* m20;       // +0x20
  char pad_24[0x140 - 0x24];
  float mX;        // +0x140
  float mY;        // +0x144
  char pad_148[0x154 - 0x148];
  int m154;        // +0x154
  bool DoOnMouseMove(float x, float y, int z);
};
// ---- items of slice s005b4170 end

// ---- items of slice s005b5a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kSnapThresholds[6];  // 0x013f7608
extern float kPi;                       // 0x01512d60
extern float kTwoPi;                    // 0x015e9fd8
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
namespace eastl {
extern char gEmptyString[2];   // 0x01667bac
}
namespace eastl {
struct allocator_s005b_5a30 {
    void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
template <typename T, typename Allocator = allocator_s005b_5a30>
class basic_string_s005b_5a30 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    __forceinline basic_string_s005b_5a30(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p, p + strlen(p)); }
    ~basic_string_s005b_5a30() { DeallocateSelf(); }

    const T* c_str() const { return mpBegin; }

    void AllocateSelf(size_t n)
    {
        if (n > 1) {
            mpBegin = (T*)mAllocator.allocate(n * sizeof(T));
            mpEnd = mpBegin;
            mpCapacity = mpBegin + n;
        } else {
            mpBegin = (T*)gEmptyString;
            mpEnd = mpBegin;
            mpCapacity = mpBegin + 1;
        }
    }
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        memcpy(mpBegin, pBegin, n * sizeof(T));
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            mAllocator.deallocate(mpBegin);
    }
};
}
namespace eastl {
typedef basic_string_s005b_5a30<char> string;
}
namespace eastl {
bool operator==(const string& a, const char* p);   // 0x00555020
}
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    float& operator[](int i) { return (&x)[i]; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3& operator+=(const Vector3& b) { x += b.x; y += b.y; z += b.z; return *this; }
};
inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
    return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
inline float Length(const Vector3& v) { return sqrtf(Dot(v, v)); }
__forceinline Vector3 NormalizedInline(const Vector3& v)
{
    float len = Length(v);
    float inv = 1.0f / len;
    return v * inv;
}
struct Matrix3 {
    Vector3 row[3];
    Matrix3() {}
    Matrix3(const Matrix3& m);                       // 0x0041cb40 (out of line)
    // inline row-major product (this * b), as inlined in the ring branch
    Matrix3 Mul(const Matrix3& b) const
    {
        Matrix3 r;
        for (int i = 0; i < 3; ++i) {
            const Vector3& a = row[i];
            r.row[i].x = a.x * b.row[0].x + a.z * b.row[2].x + a.y * b.row[1].x;
            r.row[i].y = a.x * b.row[0].y + a.z * b.row[2].y + a.y * b.row[1].y;
            r.row[i].z = a.x * b.row[0].z + a.z * b.row[2].z + a.y * b.row[1].z;
        }
        return r;
    }
};
inline Vector3 MulVecMat(const Vector3& v, const Matrix3& m)
{
    return Vector3(v.x * m.row[0].x + v.z * m.row[2].x + v.y * m.row[1].x,
                   v.x * m.row[0].y + v.z * m.row[2].y + v.y * m.row[1].y,
                   v.x * m.row[0].z + v.z * m.row[2].z + v.y * m.row[1].z);
}
struct Plane {           // n.p + d = 0
    Vector3 n;
    float d;
    Plane(const Vector3& normal, const Vector3& point) : n(normal), d(-Dot(point, normal)) {}
};
extern const Vector3 kZeroVector;       // 0x015e9e64
extern const Vector3 kUpVector;         // 0x015e9fdc
extern const Matrix3 kIdentityMatrix;   // 0x015e9f94
extern const Vector3 kGroundNormal;     // 0x01512d70
extern const Vector3 kSnapAxes[6];      // 0x01512ee0
struct Transform {
    uint16_t mFlags;
    uint16_t mChangeCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;

    // inline here; the ball branch of the original calls it out of line (0x00409930)
    __forceinline Transform() : mFlags(0), mChangeCount(0), mTranslation(kZeroVector), mScale(1.0f), mRotation(kIdentityMatrix) {}
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; mChangeCount++; }
    void PreRotate(const Matrix3& m);                // 0x005b51b0
    void RotateAxisAngle(const Vector3& axis, float angle);   // 0x006baba0
    void ApplyTo(Matrix3* m);                        // 0x006ba870 (XForm2::Apply)
};
Vector3 Normalize(const Vector3& v);                                     // 0x00436ce0
Matrix3 RotationBetween(const Vector3& from, const Vector3& to);         // 0x0069b1c0
float   SignedAngle(const Vector3* a, const Vector3* b, const Vector3* axis);   // 0x0069b760
Matrix3 OrientationFromDirection(const Vector3& dir, const Vector3& up); // 0x004a89e0
Matrix3 Transpose(const Matrix3& m);                                     // 0x0041ded0
Matrix3 MatMul(const Matrix3& a, const Matrix3& b);                      // 0x0041de20
float   WrapAngleToPi(float a);                                          // 0x0059c030
float   AngleDelta(float target, float current);                         // 0x00699730
float   ApproachAngle(float current, float target, float step);          // 0x0069b840
float   SnapRollAngle(float a);                                          // 0x005b4f20
bool    IntersectRayPlane(const Vector3* origin, const Vector3* dir, const Plane* plane, float* t);  // 0x0044e640
bool    IntersectRaySphere(const Vector3* origin, const Vector3* dir, const Vector3* center,
                           float radius, float* t);                      // 0x005a9c40
void    GetSymmetryAxis(int* axis, float* a, float* b);                  // 0x0044c0e0
inline bool IntersectRayPlaneInline(const Vector3* origin, const Vector3* dir, const Plane* plane, float* t)
{
    float denom = Dot(plane->n, *dir);
    if (denom == 0.0f)
        return false;
    *t = -(Dot(*origin, plane->n) + plane->d) / denom;
    return *t >= 0.0f;
}
inline float WrapAngleInline(float a)
{
    float r = fmodf(a, kTwoPi);
    if (r > kPi)
        r -= kTwoPi;
    else if (r < -kPi)
        r += kTwoPi;
    return r;
}
void SetSoundSymbol(uint32_t a, uint32_t b, const char* name);   // 0x00572070
namespace SP {
namespace EditorUtils {
void PlayEditorSound(uint32_t group, uint32_t id, float param, int flags);   // 0x00435f40
}
}
namespace SP {
enum {
    kHandleRotationRing = 0x50a2ed2,
    kHandleRotationBall = 0x50a510e,
};
}
namespace SP {
class cSPEditorHandle_s005b_5a30 {
public:
    virtual int AddRef();                       // 0x00
    virtual int Release();                      // 0x04 0x0051e380
    virtual void v08();
    virtual void* Cast(uint32_t typeID);        // 0x0c
    virtual uint32_t GetType();                 // 0x10
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual Vector3 GetPosition();              // 0x24
    virtual void v28();
    virtual void v2c();
    virtual void SetState(int state, int flag); // 0x30
};
}
namespace SP {
class cSPEditorHandleRotationRing_s005b_5a30 : public cSPEditorHandle_s005b_5a30 {
public:
    char pad04[0x6c - 4];
    uint32_t mRingAxis;                         // +0x6c
};
}
namespace SP {
template <class T>
inline T* object_cast(cSPEditorHandle_s005b_5a30* p, uint32_t id) { return p ? (T*)p->Cast(id) : 0; }
}
namespace SP {
template <class T>
struct AutoRefCount {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}
namespace SP {
class cSPEditorModel_s005b_5a30 {
public:
    float GetZoomScale();                       // 0x004adaa0
    bool  IsSymmetryEnabled();                  // 0x004adc40
};
}
namespace SP {
class cViewer_s005b_5a30 {
public:
    bool GetWorldRayFromScreenCoords(float x, float y, Vector3* origin, Vector3* dir);   // 0x007c4730
};
}
namespace SP {
class cApp {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cViewer_s005b_5a30* GetViewer();               // 0x58
};
}
namespace SP {
cApp* App();                                    // 0x0067dd10
}
namespace SP {
struct PileList { void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator; };
}
namespace SP {
class cSPEditorBlock_s005b_5a30 {
public:
    char pad00[0x28];
    cSPEditorModel_s005b_5a30* mEditorModel;               // +0x28
    char pad2c[0x48 - 0x2c];
    Vector3 mPosition;                          // +0x48
    Vector3 mHistoryPosition;                   // +0x54
    Matrix3 mOrientation;                       // +0x60
    Matrix3 mHistoryOrientation;                // +0x84 (row 2 at +0x9c)
    Matrix3 mBaseOrientation;                   // +0xa8
    Matrix3 mHistoryBaseOrientation;            // +0xcc
    Matrix3 mUserOrientation;                   // +0xf0
    Matrix3 mHistoryUserOrientation;            // +0x114
    char pad138[0x160 - 0x138];
    cSPEditorHandle_s005b_5a30* mRotationBallHandle;       // +0x160
    char pad164[0x418 - 0x164];
    Vector3 mBallAxis;                          // +0x418 (retail-only field)
    char pad424[0x494 - 0x424];
    char* mRotateSoundString;                   // +0x494 (string mpBegin)
    char pad498[0xdcc - 0x498];
    uint32_t mFlags;                            // +0xdcc

    int  IsPinned();                            // 0x0044f220
    int  CalculateSymmetrySign();               // 0x0044f240
    void SetSymmetrySign(int sign);             // 0x0044e980
    bool HasSymmetricBlock(int a);              // 0x0044c4d0
    void SetModelBasedOnSymmetrySign(int sign, bool a, bool b, bool c, bool d);   // 0x00439110
    cSPEditorHandle_s005b_5a30* GetRotationRingHandle(int axis);   // 0x0044aa10
    void SetOrientation(Matrix3 m);             // 0x0043ffa0
};
}
namespace SP {
namespace EditorUtils {
void RepinBlockToTorso(cSPEditorBlock_s005b_5a30* block, Vector3 pos, Matrix3 orient, int flag);   // 0x0049fbd0
}
}
namespace SP {
namespace EditorUtils {
void SetSymmetricBlocksUIState(cSPEditorBlock_s005b_5a30* block, PileList* pile, int state);       // 0x004a7f30
}
}
namespace SP {
void MoveBlock(cSPEditorBlock_s005b_5a30* block, Vector3* pos, Matrix3* oldOrient, Matrix3* newOrient,
               bool a, float scale, bool b, bool c);                    // 0x00498470
}
namespace SP {
void UpdatePile(cSPEditorBlock_s005b_5a30* block, PileList* pile, int a, int b, int c, int d, int e, int f);   // 0x004a6d20
}
namespace SP {
bool CanPlaceSymmetric(int pinned, int sign, bool hasSymmetric);       // 0x004a7ea0
}
namespace SP {
class cSPEditorManipulationRotationHandle {
public:
    char pad0[0x1c];
    AutoRefCount<cSPEditorHandle_s005b_5a30> mRotationHandle;   // +0x1c
    cSPEditorBlock_s005b_5a30* mBlock;                     // +0x20
    PileList mPileList;                         // +0x24
    char pad34[4];
    Vector3 mMouseOffset;                       // +0x38
    Vector3 mInitialClickPosition;              // +0x44
    float mHistoryAppliedRoll;                  // +0x50
    Matrix3 mRotationModifier;                  // +0x54
    Matrix3 mBaseOrientation;                   // +0x78
    Matrix3 mInitialUserOrientation;            // +0x9c
    Vector3 mRotationAxis;                      // +0xc0
    Vector3 mBlockHistoryForward;               // +0xcc
    Vector3 mPlaneNormal;                       // +0xd8
    Matrix3 mParentOrientation;                 // +0xe4
    Matrix3 mGeometryOrientation;               // +0x108
    float mTimeSpentSnapped;                    // +0x12c
    bool mOutsideInitialSnapRange;              // +0x130
    float mTargetRoll;                          // +0x134
    float mActualRoll;                          // +0x138
    float mSymmetryModifier;                    // +0x13c
    float mX;                                   // +0x140
    float mY;                                   // +0x144
    Vector3 mCameraPlanePoint;                  // +0x148 (retail-only field)

    void UpdateHighlight(float x, float y);     // 0x005b5470

    // @ 0x005b5a30
    void Reset(float deltaMs);
};
}
// ---- items of slice s005b5a30 end

// @ 0x005b4fa0
void Stub_005b4fa0()
{}

// @ 0x005b50a0
bool SPin50::DoOnMouseMove(float x, float y, int z)
{
  if (m20) {
    if ((mX != x || mY != y) && !mChanged)
      mChanged = true;
    m154 = z;
    mX = x;
    mY = y;
    return true;
  }
  return false;
}

// @ 0x005b5900
void Stub_005b5900()
{}

// @ 0x005b59d0
void Stub_005b59d0()
{}

// @ 0x005b5a30
namespace SP {
void cSPEditorManipulationRotationHandle::Reset(float deltaMs)
{
    if (mBlock == 0)
        return;

    float dt = deltaMs * 0.001f;
    Vector3 dir;
    Vector3 origin;
    App()->GetViewer()->GetWorldRayFromScreenCoords(mX, mY, &origin, &dir);
    Matrix3 newOrientation(mBlock->mUserOrientation);

    if (mRotationHandle->GetType() == kHandleRotationRing) {
        // ---------------------------------------------------------------- ring
        cSPEditorHandleRotationRing_s005b_5a30* ring =
            object_cast<cSPEditorHandleRotationRing_s005b_5a30>(mRotationHandle.get(), kHandleRotationRing);

        float t;
        if (fabsf(Dot(mPlaneNormal, dir)) < 0.3f) {
            // ray nearly parallel to the ring plane: use a camera-facing plane
            Plane plane(dir, mCameraPlanePoint);
            if (IntersectRayPlaneInline(&origin, &dir, &plane, &t)) {
                Vector3 hit = origin + dir * t - mCameraPlanePoint;
                Vector3 side = Normalize(Cross(dir, mPlaneNormal));
                float along = Dot(side, hit);
                float invZoom = 1.0f / mBlock->mEditorModel->GetZoomScale();
                mTargetRoll = WrapAngleToPi(mHistoryAppliedRoll + (5.0f * invZoom) * along) * 57.29578f;
            }
        } else {
            cSPEditorBlock_s005b_5a30* block = mBlock;
            Plane plane(mPlaneNormal, block->mPosition);
            if (IntersectRayPlaneInline(&origin, &dir, &plane, &t)) {
                Vector3 from = mInitialClickPosition - block->mHistoryPosition;
                Vector3 to = origin + dir * t - block->mHistoryPosition;
                mTargetRoll = WrapAngleToPi(SignedAngle(&from, &to, &mPlaneNormal) * mSymmetryModifier
                                            + mHistoryAppliedRoll) * 57.29578f;
            }
        }

        bool snapping = false;
        if (mTimeSpentSnapped > 1.35f)
            snapping = false;
        else if (mOutsideInitialSnapRange)
            snapping = true;

        float speed = 14.0f;
        Transform xf;
        xf.SetRotation(mGeometryOrientation.Mul(mInitialUserOrientation));
        xf.RotateAxisAngle(mRotationAxis, mTargetRoll * 0.017453292f);
        xf.ApplyTo(&mBlock->mBaseOrientation);

        Vector3 axis = kZeroVector;
        uint32_t ringAxis = ring->mRingAxis;
        if (ringAxis == 0x1d369ee)
            axis = xf.mRotation.row[1];
        else if (ringAxis == 0x67489dc || ringAxis == 0x3bc16bcd)
            axis = xf.mRotation.row[2];

        if (snapping) {
            Matrix3 parent = mParentOrientation;
            int i;
            for (i = 0; (float)i < 6.0f; ++i) {
                Vector3 snapAxis = MulVecMat(kSnapAxes[i], parent);
                if (1.0f - Dot(snapAxis, axis) < kSnapThresholds[i]) {
                    mTargetRoll = SignedAngle(&mBlockHistoryForward, &snapAxis, &mPlaneNormal) * 57.29578f;
                    speed = 35.0f;
                    mTimeSpentSnapped += dt;
                    break;
                }
            }
            if ((float)i == 6.0f)
                mTimeSpentSnapped = 0.0f;
        }

        if (!mOutsideInitialSnapRange) {
            mOutsideInitialSnapRange = true;
            for (int i = 0; (float)i < 6.0f; ++i) {
                Vector3 snapAxis = MulVecMat(kSnapAxes[i], mParentOrientation);
                if (1.0f - Dot(snapAxis, axis) < kSnapThresholds[i] * 2.0f)
                    mOutsideInitialSnapRange = false;
            }
        }

        float oldRoll = mActualRoll;
        mTargetRoll = mTargetRoll * 0.017453292f;
        float delta = AngleDelta(mTargetRoll, oldRoll);
        float newRoll = ApproachAngle(mActualRoll, mTargetRoll, delta * speed * dt);
        mActualRoll = newRoll;
        if (oldRoll != newRoll) {
            float volume = fabsf(WrapAngleInline(newRoll) / kPi);
            eastl::string sound(mBlock->mRotateSoundString);
            SetSoundSymbol(0xb07c3bbf, 0x1e8bda2a, sound.c_str());
            EditorUtils::PlayEditorSound(0xb07c3bbf, 0xfdedb725, volume, 0);
        }

        xf.SetRotation(mInitialUserOrientation);
        xf.RotateAxisAngle(mRotationAxis, mActualRoll);
        newOrientation = xf.mRotation;
    } else if (mRotationHandle->GetType() == kHandleRotationBall) {
        // ---------------------------------------------------------------- ball
        cSPEditorBlock_s005b_5a30* block = mBlock;
        Vector3 ballAxis = block->mBallAxis;
        Vector3 down = -kUpVector;
        Matrix3 ballOrientation = RotationBetween(down, NormalizedInline(ballAxis));
        origin += mMouseOffset;

        Vector3 delta;
        if (mBlock->IsPinned() == 0 && mBlock->mEditorModel->IsSymmetryEnabled()) {
            Vector3 handlePos = mBlock->mRotationBallHandle->GetPosition();
            Vector3 center(handlePos.x, mBlock->mPosition.y, mBlock->mPosition.z);
            int symAxis;
            float symA, symB;
            GetSymmetryAxis(&symAxis, &symA, &symB);
            ballAxis[symAxis] = 0.0f;
            down = -kUpVector;
            ballOrientation = RotationBetween(down, Normalize(ballAxis));
            Plane plane(kGroundNormal, center);
            float t;
            if (!IntersectRayPlane(&origin, &dir, &plane, &t))
                return;
            delta = origin + dir * t - center;
        } else {
            float t = 0.0f;
            float radius = Length(block->mPosition - mRotationHandle->GetPosition());
            if (IntersectRaySphere(&origin, &dir, &block->mPosition, radius, &t)) {
                delta = origin + dir * t - block->mPosition;
            } else {
                Plane plane(dir, block->mPosition);
                float tPlane;
                if (!IntersectRayPlane(&origin, &dir, &plane, &tPlane))
                    return;
                Vector3 hit = origin + dir * tPlane;
                Vector3 rayOrigin = hit;
                Vector3 toward = Normalize(block->mPosition - hit);
                radius = Length(block->mPosition - mRotationHandle->GetPosition());
                block = mBlock;
                if (!IntersectRaySphere(&rayOrigin, &toward, &block->mPosition, radius, &t))
                    return;
                delta = toward * t + hit - block->mPosition;
            }
        }

        Matrix3 rotation(mBlock->mHistoryUserOrientation);
        Vector3 forward = mBlock->mHistoryOrientation.row[2];
        Vector3 up = Normalize(forward);
        Matrix3 look = OrientationFromDirection(delta, up);
        Transform xf;
        rotation = MatMul(MatMul(Transpose(ballOrientation), look), Transpose(mBlock->mHistoryBaseOrientation));
        xf.PreRotate(rotation);
        newOrientation = xf.mRotation;

        Vector3 side = Cross(delta, up);
        float volume = fabsf(SnapRollAngle(SignedAngle(&delta, &up, &side)) / kPi);
        eastl::string sound(mBlock->mRotateSoundString);
        if (!(sound == "")) {
            SetSoundSymbol(0xb07c3bbf, 0x1e8bda2a, sound.c_str());
            EditorUtils::PlayEditorSound(0xb07c3bbf, 0xfdedb725, volume, 0);
        }
    } else {
        return;
    }

    // -------------------------------------------------------------------- common tail
    cSPEditorBlock_s005b_5a30* block = mBlock;
    float scale = 1.0f;
    if ((block->mFlags >> 2) & 1)
        scale = 1.5f;
    Vector3 position = block->mPosition;
    Matrix3 oldOrientation;
    oldOrientation.row[0] = block->mBaseOrientation.row[0];
    oldOrientation.row[1] = block->mBaseOrientation.row[1];
    oldOrientation.row[2] = block->mBaseOrientation.row[2];
    Matrix3 savedOrientation;
    savedOrientation.row[0] = newOrientation.row[0];
    savedOrientation.row[1] = newOrientation.row[1];
    savedOrientation.row[2] = newOrientation.row[2];
    MoveBlock(block, &position, &oldOrientation, &newOrientation, true, scale, true, true);
    mBlock->SetOrientation(newOrientation);

    EditorUtils::RepinBlockToTorso(mBlock, mBlock->mPosition, mBlock->mBaseOrientation, 0);
    EditorUtils::SetSymmetricBlocksUIState(mBlock, &mPileList, 0);
    UpdatePile(mBlock, &mPileList, 0, 0, 0, 0, 1, 1);

    int pinned = mBlock->IsPinned();
    int sign = mBlock->CalculateSymmetrySign();
    bool symmetryOk;
    if (mBlock->mEditorModel)
        symmetryOk = mBlock->mEditorModel->IsSymmetryEnabled();
    else
        symmetryOk = true;
    mBlock->SetSymmetrySign(sign);
    if (!symmetryOk)
        return;
    if (!CanPlaceSymmetric(pinned, sign, mBlock->HasSymmetricBlock(0)))
        return;

    if (sign == 0)
        MoveBlock(mBlock, &position, &oldOrientation, &savedOrientation, true, scale, true, true);

    uint32_t type = mRotationHandle->GetType();
    mBlock->SetModelBasedOnSymmetrySign(sign, true, true, false, false);
    if (type == kHandleRotationBall) {
        mRotationHandle = mBlock->mRotationBallHandle;
    } else {
        int ringIndex = 0;
        if (type == kHandleRotationRing) {
            cSPEditorHandleRotationRing_s005b_5a30* ring =
                object_cast<cSPEditorHandleRotationRing_s005b_5a30>(mRotationHandle.get(), type);
            uint32_t ringAxis = ring->mRingAxis;
            if (ringAxis == 0x1d369ee)
                ringIndex = 2;
            else if (ringAxis == 0x67489dc)
                ringIndex = 0;
            else if (ringAxis == 0x3bc16bcd)
                ringIndex = 1;
        }
        mRotationHandle = mBlock->GetRotationRingHandle(ringIndex);
        mRotationHandle->SetState(2, 0);
    }
    UpdateHighlight(mX, mY);
}
}  // namespace SP
