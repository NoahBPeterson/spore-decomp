// src/game/SPEditors/SPEditorManipulationRotationHandle.cpp -- migrated from slice(s) s005a8d20, s005b5a30, s005b5110, s005b4170 by tools/migrate/rewrite.py
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
#include "SP/cSPEditorAnimatedEventInfo.h"
#include <new>
#ifndef SP_EDITOR_MANIP_SCAFFOLD_H
#endif  // SP_EDITOR_MANIP_SCAFFOLD_H

// ---- items of slice s005b4170 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Vector3Template_s005b_4170 {
 public:
  T x, y, z;
  Vector3Template_s005b_4170() {}
  Vector3Template_s005b_4170(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N>
class Matrix33Template_s005b_4170 {
 public:
  Vector3Template_s005b_4170<T, N> xAxis, yAxis, zAxis;
  Matrix33Template_s005b_4170() {}
};
}
}
}
struct cSPVector3_s005b_4170 : public rw::math::fpu::Vector3Template_s005b_4170<float, 0> {
  typedef rw::math::fpu::Vector3Template_s005b_4170<float, 0> base;
  cSPVector3_s005b_4170() {}
  cSPVector3_s005b_4170(float ax, float ay, float az) : base(ax, ay, az) {}
  cSPVector3_s005b_4170(const base& v) { x = v.x; y = v.y; z = v.z; }
  cSPVector3_s005b_4170& operator=(const base& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3_s005b_4170 : public rw::math::fpu::Matrix33Template_s005b_4170<float, 0> {
  cSPMatrix3_s005b_4170() {}
  cSPMatrix3_s005b_4170(const cSPMatrix3_s005b_4170& o);   // 0x0041cb40
};
bool operator!=(const cSPMatrix3_s005b_4170& a, const cSPMatrix3_s005b_4170& b);   // 0x0041dd90
namespace EA {
namespace COM {
class IUnknown32_s005b_4170 {
 public:
  virtual int AddRef();
  virtual int Release();
};  // namespace COM
}
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_4170 {
 public:
  RefCountVTemplate_s005b_4170() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005b_4170() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace {
struct RefA {  // AddRef slot 1, Release slot 2
  virtual ~RefA();
  virtual int AddRef();
  virtual int Release();
};
struct RefB {  // Release slot 1
  virtual int AddRef();
  virtual int Release();
};
struct BaseManip : EA::COM::IUnknown32_s005b_4170 {
  virtual ~BaseManip();
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  char pad_7;
  float mDeadZoneSize;   // +0x8
  float mInitialX;       // +0xc
  float mInitialY;       // +0x10
  BaseManip();
};

// eastl::sp_vector<AutoRefCount<cSPEditorBlock> > layout: three pointers followed by the
// 8-byte retail sp_vector_allocator.  Elements are reference-counted block pointers.
struct PileList_s005b_4170 {
  RefA** mpBegin;
  RefA** mpEnd;
  RefA** mpCapacity;
  uint32_t mAllocator[2];
  PileList_s005b_4170() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  void erase(RefA** first, RefA** last);                        // 0x00454280
  void DoInsertValueEnd(RefA** position, RefA* const& value);   // 0x00454ee0
};

struct IObject {
  virtual void* Cast(uint32_t id);   // +0x00
  virtual int AddRef();              // +0x04
  virtual int Release();             // +0x08
};

// Handle object whose vtable slot 0x30 takes two ints.
struct RefHandle {
  virtual void* Cast(uint32_t id);   // +0x00
  virtual int AddRef();              // +0x04
  virtual int Release();             // +0x08
  virtual void v3();                 // +0x0c
  virtual void v4();                 // +0x10
  virtual void v5();                 // +0x14
  virtual void v6();                 // +0x18
  virtual void v7();                 // +0x1c
  virtual void v8();                 // +0x20
  virtual void v9();                 // +0x24
  virtual void v10();                // +0x28
  virtual void v11();                // +0x2c
  virtual void SetState(int a, int b);   // +0x30
};
}  // namespace
namespace SP {
class cSPEditorAnimatedEventInfo_s005b_4170 : public IObject {
 public:
  uint32_t mData[11];
  cSPEditorAnimatedEventInfo_s005b_4170();   // 0x0059d960
  void MessagePost(uint32_t id, void* block, void* model, uint32_t a, bool b, float c, int d, int e,
                   float f);   // 0x0059d840
};  // namespace SP
}
namespace PM {
struct V3 {
  float x, y, z;
  V3() {}
  V3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  V3(const V3& v) : x(v.x), y(v.y), z(v.z) {}
};
}
namespace PM {
struct M3 {
  V3 a, b, c;
  M3() {}
  M3(const M3& m);  // out of line: Matrix3::Assign (0x0041cb40)
};
}
namespace PM {
struct BBox {
  V3 mn, mx;
};
}
namespace PM {
struct Blk;
}
namespace PM {
struct Model {
  float GetScale();                  // 0x004adaa0
  float GetFloorZ();                 // 0x004adb00
  void SetUsingSymmetry(bool);       // 0x004adc20
  bool UsingSymmetry();              // 0x004adc40
  unsigned GetBlockCount();          // 0x004accf0
  Blk* GetBlock(unsigned index);     // 0x004accb0
};
}
namespace PM {
struct Blk {
  char pad0[0x28];
  Model* model;  // +0x28
  char pad2c[0x48 - 0x2c];
  V3 pos;  // +0x48
  char pad54[0xa8 - 0x54];
  M3 orient;  // +0xa8
  char padcc[0x33c - 0xcc];
  void* socket;       // +0x33c
  Blk** kidsBegin;    // +0x340
  Blk** kidsEnd;      // +0x344
  char pad348[0x3e0 - 0x348];
  Blk* sym;           // +0x3e0
  char pad3e4[0xdc8 - 0x3e4];
  uint32_t flags;     // +0xdc8
  void SetBooleanAttribute(int id, bool v);      // 0x00435a10
  BBox* GetBBox(BBox* out, int a, int b, int c);  // 0x0044ae00
  void SetPosition(const V3& p, bool notify);     // 0x00448e90
  void SetOrientation(const M3& m, bool notify);  // 0x00449420
  void SetSymmetrySign(int sign);                 // 0x0044e980
  void AddToEffectsMask(cSPVector3_s005b_4170 pos, bool flag);   // 0x00448690
  void F3cad0();                                  // 0x0043cad0
};
}
namespace PM {
void DeleteInvalidBlocks(Blk* block, void* pile);        // 0x004a6f10
}
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
class RotationHandle : public BaseManip, public EA::RefCountVTemplate_s005b_4170<int> {
 public:
  RefHandle* m1c;   // +0x1c rotation handle
  PM::Blk* m20;     // +0x20 rotated block
  PileList_s005b_4170 mPile;   // +0x24
  bool OnMouseUp(int button, float x, float y, int mods);
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

// ---- items of slice s005a8d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)
struct Vector3_s005a_8d20 {
    float x, y, z;
    Vector3_s005a_8d20() {}
    Vector3_s005a_8d20(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s005a_8d20 operator-(const Vector3_s005a_8d20& b) const { return Vector3_s005a_8d20(x - b.x, y - b.y, z - b.z); }
    float Dot(const Vector3_s005a_8d20& b) const { return x * b.x + y * b.y + z * b.z; }
};
struct Quaternion { float x, y, z, w; };
struct Matrix3_s005a_8d20 {
    float m[9];
    Matrix3_s005a_8d20& SetRotation(const Quaternion& q);   // 0x0041CB40
};
Matrix3_s005a_8d20 operator*(const Matrix3_s005a_8d20& a, const Matrix3_s005a_8d20& b);   // 0x0041DE20
// ---- items of slice s005a8d20 end

// ---- items of slice s005b5110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float   kOneConst;         // 0x01485720
extern void* vtbl_13f7634[];            // derived, +0x00
extern void* vtbl_13f7624[];            // derived, +0x14
extern void* vtbl_13ec458[];            // base,    +0x14
extern void* vtbl_13eb938[];            // base,    +0x00
struct Vector3_s005b_5110 {
    float x, y, z;
    Vector3_s005b_5110() {}
    Vector3_s005b_5110(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s005b_5110 operator+(const Vector3_s005b_5110& b) const { return Vector3_s005b_5110(x + b.x, y + b.y, z + b.z); }
    Vector3_s005b_5110 operator*(float s) const { return Vector3_s005b_5110(x * s, y * s, z * s); }
};
struct Matrix3_s005b_5110 { Vector3_s005b_5110 row[3]; Matrix3_s005b_5110() {} };
extern const Matrix3_s005b_5110 kIdentityMatrix_s005b_5110;   // 0x015e9f94
void  OpDelete(void* p);                                                       // 0x00f47380
void  BuildPileList(void* block, void* pile, int flag);                        // 0x0048c790
void  PileSetup(char* block, void* pile);                                      // 0x004961d0
Matrix3_s005b_5110* MatMul(Matrix3_s005b_5110* out, const Matrix3_s005b_5110* a, const Matrix3_s005b_5110* b);             // 0x0041de20
void  CopyAddRefPtrs(void** pOutEnd, void** first, void** last, void** dest, void* owner);  // 0x004b2220
Vector3_s005b_5110 MulVecMat_s005b_5110(const Vector3_s005b_5110& v, const Matrix3_s005b_5110& m)
{
    return Vector3_s005b_5110(v.x * m.row[0].x + v.z * m.row[2].x + v.y * m.row[1].x,
                   v.x * m.row[0].y + v.z * m.row[2].y + v.y * m.row[1].y,
                   v.x * m.row[0].z + v.z * m.row[2].z + v.y * m.row[1].z);
}
class Block;
struct PileList_s005b_5110 {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void Dtor();                                        // 0x00453eb0 (thiscall)
    void VectorCtor(int count, void* alloc);            // 0x0066aec0 (thiscall)
};
class Handle {
public:
    virtual int  AddRef();                          // 0x00
    virtual int  Release();                         // 0x04
    virtual void v08();
    virtual void* Cast(uint32_t typeID);            // 0x0c
    virtual uint32_t GetType();                     // 0x10
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual Vector3_s005b_5110 GetPosition();                  // 0x24
    virtual void v28();
    virtual void v2c();
    virtual void SetState(int state, int flag);     // 0x30
    Block* GetEditorBlock();                        // 0x0047e6c0 (non-virtual)
};
class Ring : public Handle {
public:
    Vector3_s005b_5110 GetForwardVector(bool a);               // 0x00484ee0
    Vector3_s005b_5110 GetRotationAxis(bool a);                // 0x00484e40
};
class Block {
public:
    virtual void v00();
    virtual int  AddRef();                          // 0x04
    virtual int  Release();                         // 0x08
    void Refresh();                                 // 0x00448a80
    void F3cfc0(int h, char d);                     // 0x0043cfc0

    char pad00[0x24];                               // vptr is at +0x00
    void* mEditorModel;                             // +0x28
    char pad2c[0x48 - 0x2c];
    Vector3_s005b_5110 mPosition;                              // +0x48
    Vector3_s005b_5110 mHistoryPosition;                       // +0x54
    Matrix3_s005b_5110 mOrientation;                           // +0x60
    Matrix3_s005b_5110 mHistoryOrientation;                    // +0x84
    Matrix3_s005b_5110 mBaseOrientation;                       // +0xa8
    Matrix3_s005b_5110 mHistoryBaseOrientation;                // +0xcc
    Matrix3_s005b_5110 mUserOrientation;                       // +0xf0
    Matrix3_s005b_5110 mHistoryUserOrientation;                // +0x114
    char pad138[0x33c - 0x138];
    Block* mParentBlock;                            // +0x33c
};
template <class T>
struct AutoRefCount_s005b_5110 {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCount_s005b_5110& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
class cViewer {
public:
    bool GetWorldRayFromScreenCoords(float x, float y, Vector3_s005b_5110* origin, Vector3_s005b_5110* dir);   // 0x007c4730
};
class cApp_s005b_5110 {
public:
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
virtual void v54();
    virtual cViewer* GetViewer();                   // 0x58
};
cApp_s005b_5110* App_s005b_5110();                                        // 0x0067dd10
struct RotationHandle_s005b_5110 {
    void*      vtbl0;                    // +0x00
    uint8_t    bFlag04;                  // +0x04
    uint8_t    pad05[7];
    float      f0c;                      // +0x0c
    float      f10;                      // +0x10
    void*      vtbl14;                   // +0x14
    uint32_t   d18;                      // +0x18
    AutoRefCount_s005b_5110<Handle> mRotationHandle;   // +0x1c
    AutoRefCount_s005b_5110<Block>  mBlock;            // +0x20
    PileList_s005b_5110   mPileList;                // +0x24
    uint32_t   pad34;                    // +0x34
    Vector3_s005b_5110    mMouseOffset;             // +0x38
    Vector3_s005b_5110    mInitialClickPosition;    // +0x44
    float      mHistoryAppliedRoll;      // +0x50
    Matrix3_s005b_5110    mRotationModifier;        // +0x54
    Matrix3_s005b_5110    mBaseOrientation;         // +0x78
    Matrix3_s005b_5110    mInitialUserOrientation;  // +0x9c
    Vector3_s005b_5110    mRotationAxis;            // +0xc0
    Vector3_s005b_5110    mBlockHistoryForward;     // +0xcc
    Vector3_s005b_5110    mPlaneNormal;             // +0xd8
    Matrix3_s005b_5110    mParentOrientation;       // +0xe4
    Matrix3_s005b_5110    mGeometryOrientation;     // +0x108
    float      mTimeSpentSnapped;        // +0x12c
    uint8_t    mOutsideInitialSnapRange; // +0x130
    uint8_t    pad131[3];
    float      mTargetRoll;              // +0x134
    float      mActualRoll;              // +0x138
    float      mSymmetryModifier;        // +0x13c
    float      mX;                       // +0x140
    float      mY;                       // +0x144
    Vector3_s005b_5110    mCameraPlanePoint;        // +0x148
    uint32_t   d154;                     // +0x154

    void BaseManipCtor();                                   // 0x005b0f80 (thiscall)
    RotationHandle_s005b_5110* Init();
    RotationHandle_s005b_5110* Destroy(uint32_t flags);
    void SetInput(Handle* h, Vector3_s005b_5110 a, Vector3_s005b_5110 b);
    bool DoOnMouseDown(float unused, float x, float y, uint32_t z);
    PileList_s005b_5110* GetPileCopy(PileList_s005b_5110* out) const;
    void Update(float x, float y);
};
struct cTransform {
    uint16_t flags;      // +0x00
    uint16_t count;      // +0x02
    uint8_t  pad04[0x10];
    Matrix3_s005b_5110  rotation;   // +0x14
    void PreRotate(const Matrix3_s005b_5110& m);
};
// ---- items of slice s005b5110 end

// @ 0x005a9c40
bool IntersectRaySphere(const Vector3_s005a_8d20& origin, const Vector3_s005a_8d20& direction, const Vector3_s005a_8d20& center, float radius, float* pDistance)
{
    Vector3_s005a_8d20 d = origin - center;
    float a = direction.Dot(direction);
    float b = direction.Dot(d);
    float c = d.Dot(d) - radius * radius;
    float discriminant = b * b - c * a;
    if (discriminant < 0.0f)
        return false;
    double s  = sqrt(discriminant);
    float  t0 = (float)(-b - s);
    if (s - b < 0.0)
        return false;
    if (pDistance) {
        if (t0 <= 0.0f)
            *pDistance = 0.0f;
        else
            *pDistance = t0 / a;
    }
    return true;
}

// @ 0x005b4f20
float Stub_005b4f20(float angle)
{
  float r = (float)fmod(angle, *(volatile float*)0x15e9fd8);
  if (r > 3.1415927410125732f)
    return r - *(volatile float*)0x15e9fd8;
  if (r < -3.1415927410125732f)
    return r + *(volatile float*)0x15e9fd8;
  return r;
}

// @ 0x005b4fa0
bool RotationHandle::OnMouseUp(int button, float x, float y, int mods)
{
  (void)button; (void)x; (void)y; (void)mods;
  if (m1c && m20) {
    m20->AddToEffectsMask(cSPVector3_s005b_4170(1.0f, 1.0f, 1.0f), false);
    m1c->SetState(3, 1);
    m20->F3cad0();
    if (mChangedObject) {
      SP::cSPEditorAnimatedEventInfo_s005b_4170* msg = new ("Editor", 0, 0, 0, 0) SP::cSPEditorAnimatedEventInfo_s005b_4170();
      if (msg)
        msg->AddRef();
      PM::Blk* block = m20;
      PM::Model* model = block ? block->model : 0;
      msg->MessagePost(0x211685f7, block, model, 0, false, 0.0f, 0, -1, 1.0f);
      if (msg)
        msg->Release();
    }
    PM::DeleteInvalidBlocks(m20, &mPile);
  }
  return true;
}

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

// @ 0x005b5110
void RotationHandle_s005b_5110::SetInput(Handle* h, Vector3_s005b_5110 a, Vector3_s005b_5110 b)
{
    mMouseOffset = a;
    mCameraPlanePoint = b;
    mTimeSpentSnapped = 0.0f;
    mRotationHandle = h;
    mBlock = mRotationHandle->GetEditorBlock();
}

// @ 0x005b51b0
void cTransform::PreRotate(const Matrix3_s005b_5110& m)
{
    if (flags & 2) {
        Matrix3_s005b_5110 t;
        t.row[0].x = m.row[0].x * rotation.row[0].x + m.row[0].y * rotation.row[1].x + m.row[0].z * rotation.row[2].x;
        t.row[0].y = m.row[0].x * rotation.row[0].y + m.row[0].y * rotation.row[1].y + m.row[0].z * rotation.row[2].y;
        t.row[0].z = m.row[0].x * rotation.row[0].z + m.row[0].y * rotation.row[1].z + m.row[0].z * rotation.row[2].z;
        t.row[1].x = m.row[1].x * rotation.row[0].x + m.row[1].y * rotation.row[1].x + m.row[1].z * rotation.row[2].x;
        t.row[1].y = m.row[1].x * rotation.row[0].y + m.row[1].y * rotation.row[1].y + m.row[1].z * rotation.row[2].y;
        t.row[1].z = m.row[1].x * rotation.row[0].z + m.row[1].y * rotation.row[1].z + m.row[1].z * rotation.row[2].z;
        t.row[2].x = m.row[2].x * rotation.row[0].x + m.row[2].y * rotation.row[1].x + m.row[2].z * rotation.row[2].x;
        t.row[2].y = m.row[2].x * rotation.row[0].y + m.row[2].y * rotation.row[1].y + m.row[2].z * rotation.row[2].y;
        t.row[2].z = m.row[2].x * rotation.row[0].z + m.row[2].y * rotation.row[1].z + m.row[2].z * rotation.row[2].z;
        rotation = t;
    } else {
        rotation = m;
        flags |= 2;
    }
    ++count;
}

// @ 0x005b53c0
RotationHandle_s005b_5110* RotationHandle_s005b_5110::Init()
{
    BaseManipCtor();
    *(void* volatile*)&vtbl14 = vtbl_13ec458;
    d18 = 0;
    *(void* volatile*)&vtbl0 = vtbl_13f7634;
    *(void* volatile*)&vtbl14 = vtbl_13f7624;
    mRotationHandle.mpObject = 0;
    mBlock.mpObject = 0;
    mPileList.mpBegin = 0;
    mPileList.mpEnd = 0;
    mPileList.mpCapacity = 0;
    mMouseOffset.x = 0.0f;
    mMouseOffset.y = 0.0f;
    mMouseOffset.z = 0.0f;
    mOutsideInitialSnapRange = 0;
    d154 = 0;
    bFlag04 = 0;
    mHistoryAppliedRoll = 0.0f;
    mTimeSpentSnapped = 0.0f;
    mTargetRoll = 0.0f;
    mActualRoll = 0.0f;
    mSymmetryModifier = kOneConst;
    mX = 0.0f;
    mY = 0.0f;
    return this;
}

// @ 0x005b5470
void RotationHandle_s005b_5110::Update(float x, float y)
{
    if (mBlock.mpObject == 0 || mRotationHandle.mpObject == 0)
        return;

    mOutsideInitialSnapRange = 0;
    mHistoryAppliedRoll = 0.0f;
    BuildPileList(mBlock.mpObject, &mPileList, 0);
    PileSetup((char*)mBlock.mpObject, &mPileList);

    mGeometryOrientation = kIdentityMatrix_s005b_5110;
    mTargetRoll = 0.0f;
    mActualRoll = 0.0f;

    Block* b = mBlock.mpObject;
    const Matrix3_s005b_5110* pParent;
    if (b->mParentBlock != 0)
        pParent = &b->mParentBlock->mOrientation;
    else
        pParent = &kIdentityMatrix_s005b_5110;
    mParentOrientation = *pParent;

    mInitialUserOrientation = b->mHistoryUserOrientation;
    mBaseOrientation = b->mHistoryBaseOrientation;
    mRotationModifier = kIdentityMatrix_s005b_5110;

    Vector3_s005b_5110 origin, dir;
    App_s005b_5110()->GetViewer()->GetWorldRayFromScreenCoords(x, y, &origin, &dir);

    if (mRotationHandle->GetType() != 0x50a2ed2)
        return;

    Ring* ring = mRotationHandle.mpObject ? (Ring*)mRotationHandle.mpObject->Cast(0x50a2ed2) : 0;

    Vector3_s005b_5110 fwd = ring->GetForwardVector(false);
    mBlockHistoryForward = MulVecMat_s005b_5110(fwd, b->mHistoryOrientation);
    mRotationAxis = MulVecMat_s005b_5110(ring->GetRotationAxis(false), mInitialUserOrientation);

    Matrix3_s005b_5110 local;
    MatMul(&local, &b->mHistoryUserOrientation, &b->mHistoryBaseOrientation);

    Vector3_s005b_5110 v = MulVecMat_s005b_5110(ring->GetRotationAxis(false), local);

    float inv = (float)(1.0 / sqrt((double)v.x * (double)v.x + (double)v.y * (double)v.y + (double)v.z * (double)v.z));
    mPlaneNormal = v * inv;

    float planeD = -(mPlaneNormal.x * b->mHistoryPosition.x + mPlaneNormal.y * b->mHistoryPosition.y + mPlaneNormal.z * b->mHistoryPosition.z);
    float denom = mPlaneNormal.x * dir.x + mPlaneNormal.y * dir.y + mPlaneNormal.z * dir.z;
    if (denom != 0.0f) {
        float t = -((origin.x * mPlaneNormal.x + origin.y * mPlaneNormal.y + origin.z * mPlaneNormal.z) + planeD) / denom;
        if (t >= 0.0f)
            mInitialClickPosition = origin + dir * t;
    }
}

// @ 0x005b5900
bool RotationHandle_s005b_5110::DoOnMouseDown(float unused, float x, float y, uint32_t z)
{
    (void)unused;
    mX = x;
    mY = y;
    f0c = x;
    f10 = y;
    d154 = z;
    Update(x, y);
    mBlock->Refresh();
    mBlock->F3cfc0((int)mRotationHandle.mpObject, 1);
    mRotationHandle->SetState(2, 1);
    return false;
}

// @ 0x005b5980
PileList_s005b_5110* RotationHandle_s005b_5110::GetPileCopy(PileList_s005b_5110* out) const
{
    int count = (int)((char*)mPileList.mpEnd - (char*)mPileList.mpBegin) >> 2;
    PileList_s005b_5110* p = out;
    p->VectorCtor(count, (void*)&mPileList.mAllocator);
    CopyAddRefPtrs((void**)&out, (void**)mPileList.mpBegin, (void**)mPileList.mpEnd, (void**)p->mpBegin, out);
    p->mpEnd = out;
    return p;
}

// @ 0x005b59d0
RotationHandle_s005b_5110* RotationHandle_s005b_5110::Destroy(uint32_t flags)
{
    vtbl0 = vtbl_13f7634;
    vtbl14 = vtbl_13f7624;
    mPileList.Dtor();
    if (mBlock.mpObject) mBlock.mpObject->Release();
    if (mRotationHandle.mpObject) mRotationHandle.mpObject->Release();
    vtbl14 = vtbl_13ec458;
    vtbl0 = vtbl_13eb938;
    if (flags & 1) OpDelete(this);
    return this;
}

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
