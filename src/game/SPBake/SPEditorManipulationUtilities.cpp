// src/game/SPBake/SPEditorManipulationUtilities.cpp -- migrated from slice(s) s004a6690, s004a5970, s004a3760, s004a29a0, s004a0b70, s0049efc0, s0049ecf0, s0049cfd0, s0049c210, s0048ef30, s0048e590, s0048dcd0, s0048d010, s004a9920, s004a3dc0, s004a1a70, s0049fbd0, s0049a2a0, s006414e0, s004a89e0, s004a7c30, s004a6f10, s0049b340, s00499410, s00498470, s004974e0, s00496d30, s00496300, s004956b0, s004942b0, s00493640, s004928d0, s00491900, s00490a70, s0048fde0, s00481f00, s00453250, s00435d40 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorManipulationUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "cSPMatrix3.h"
#include "hkRotation.h"
#include "hkVector4.h"
#include <math.h>
#include <string.h>
#include <new>
#include <xmmintrin.h>
#include "SP/cSPEditorBlock.h"
#include "cSPBoundingBox.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorSnapVector.h"
#include "cSPVector3.h"
#include "SP/cViewer.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cSPEditorLimbStructure.h"
#include "hkAabb.h"
#include "hkBool.h"
#include "hkCdBody.h"
#include "hkCdPointCollector.h"
#include "hkClosestCdPointCollector.h"
#include "hkCollidable.h"
#include "hkContactPoint.h"
#include "hkLinearCastInput.h"
#include "hkMatrix3.h"
#include "hkMotion.h"
#include "hkQuaternion.h"
#include "hkRigidBody.h"
#include "hkRootCdPoint.h"
#include "hkShape.h"
#include "hkTransform.h"
#include <float.h>
#include "SP/cSPEditorHandle.h"
#include "cSPTransform.h"
#include "SP/cSPEditorPhysicsWorld.h"

// ---- items of slice s00435d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Recorder {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual int GetState();                               // +0x20
    virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13();
    virtual void Begin(uint32_t tag);                     // +0x38
    virtual void WriteFloat(uint32_t tag, float v);       // +0x3C
    virtual void WriteInt(uint32_t tag, uint32_t v);      // +0x40
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21();
    virtual void End();                                   // +0x58
};
Recorder* GetRecorder();                                  // 0x00A206F0
// ---- items of slice s00435d40 end

// ---- items of slice s00453250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kZero;    // 0x1485378
struct hkVector4_s0045_3250 {
    union { __m128 m_quad; struct { float x, y, z, w; }; };
    void setZero4() { w = 0.0f; z = 0.0f; y = 0.0f; x = 0.0f; }
    hkVector4_s0045_3250& operator=(const hkVector4_s0045_3250& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
};
struct hkRotation_s0045_3250 {
    hkVector4_s0045_3250 m_col[3];
    hkVector4_s0045_3250& getColumn(int i) { return *(hkVector4_s0045_3250*)((char*)m_col + (i << 4)); }
    void setAll(float x, float y, float z, float w) {
        hkVector4_s0045_3250 v; v.x = x; v.y = y; v.z = z; v.w = w;
    }
};
struct HavokTransform { float a, b; uint32_t pad[2]; hkVector4_s0045_3250 m_translation; hkRotation_s0045_3250 m_rotation; };
// ---- items of slice s00453250 end

// ---- items of slice s00481f00 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline bool IsNaNF(float f)
{
    return (*(uint32_t*)&f & 0x7fffffff) > 0x7f800000u;
}
// ---- items of slice s00481f00 end


// ---- items of slice s00490a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
    float operator[](int i) const { return (&x)[i]; }
};
struct RwVec3 : Vec3 {
    RwVec3() {}
    RwVec3(const RwVec3& v);        // @ 0x4098a0
};
struct Matrix3 {
    Vec3 xAxis, yAxis, zAxis;
    Matrix3() {}
    Matrix3(const Matrix3& m) { Assign(m); }
    Matrix3& Assign(const Matrix3& m);   // @ 0x41cb40
};
struct AllocTag { AllocTag() {} };
struct cSPEditorBlock_s0049_0a70;
struct RefObj {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
template<class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    AutoRefCount(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};
struct cSPEditorBlock_s0049_0a70 : RefObj {
    char pad0[0x48 - 4];
    Vec3 mPosition;                    // +0x48
    char pad1[0x3e0 - 0x54];
    cSPEditorBlock_s0049_0a70* mLink3e0;          // +0x3e0
    cSPEditorBlock_s0049_0a70* mLink3e4;          // +0x3e4
    char pad2[0x5e4 - 0x3e8];
    int mWeight;                       // +0x5e4
    char pad3[0xdc8 - 0x5e8];
    uint32_t mFlags[2];                // +0xdc8
    cSPEditorBlock_s0049_0a70* GetLink3e0() const { return mLink3e0; }
    cSPEditorBlock_s0049_0a70* GetLink3e4() const { return mLink3e4; }
    int GetWeight() const { return mWeight; }
    void FUN_0044e7c0(int x);          // @ 0x44e7c0
    uint32_t Word(uint32_t i) const { return mFlags[i >> 5]; }
    bool TestFlag(uint32_t i) const {
        if (i < 0x3c) return (Word(i) & (1u << (i % 32))) != 0;
        return false;
    }
};
struct Mgr;
struct SPAlloc { uint32_t a, b; SPAlloc(const AllocTag&); };      // @ 0x429360
struct EdList {
    AutoRefCount<cSPEditorBlock_s0049_0a70>* mpBegin;
    AutoRefCount<cSPEditorBlock_s0049_0a70>* mpEnd;
    AutoRefCount<cSPEditorBlock_s0049_0a70>* mpCap;
    SPAlloc mAlloc;
    EdList(const AllocTag& t = AllocTag()) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(t) {}
    ~EdList();                                      // @ 0x453eb0
};
float FUN_00491b40(cSPEditorBlock_s0049_0a70* self, Mgr* mgr, Vec3 v, Matrix3 m, Vec3* out, bool* flag, int n, float k);   // @ 0x491b40
void FUN_004904a0(cSPEditorBlock_s0049_0a70* self, Mgr* mgr, EdList* list, int type);                                       // @ 0x4904a0
float FUN_0048fee0(cSPEditorBlock_s0049_0a70* self, EdList* list, Vec3* out, float k);                                      // @ 0x48fee0
float GetLateralAlignmentPosition(cSPEditorBlock_s0049_0a70* self, EdList* list, Vec3* pos, Matrix3* m, float k);          // @ 0x48ef30
float GetLowAngleOffset(cSPEditorBlock_s0049_0a70* self, EdList* list, Vec3* out, float k);                                 // @ 0x48e590
float FUN_00492e70(cSPEditorBlock_s0049_0a70* self, Vec3* pos, Matrix3* m, int* neg, float k, int flag);                    // @ 0x492e70
struct BlockVec {
    AutoRefCount<cSPEditorBlock_s0049_0a70>* mpBegin;
    AutoRefCount<cSPEditorBlock_s0049_0a70>* mpEnd;
    AutoRefCount<cSPEditorBlock_s0049_0a70>* mpCap;
    uint32_t mAlloc[2];
    BlockVec(const AllocTag&);                              // @ 0x540470
    ~BlockVec();                                            // @ 0x453eb0
    void push_back(const AutoRefCount<cSPEditorBlock_s0049_0a70>& v);  // @ 0x4541f0
    AutoRefCount<cSPEditorBlock_s0049_0a70>& operator[](uint32_t i) { return mpBegin[i]; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    AutoRefCount<cSPEditorBlock_s0049_0a70>* begin() { return mpBegin; }
    AutoRefCount<cSPEditorBlock_s0049_0a70>* end() { return mpEnd; }
};
struct VisitedVec {
    AutoRefCount<cSPEditorBlock_s0049_0a70>* mpBegin;
    AutoRefCount<cSPEditorBlock_s0049_0a70>* mpEnd;
    AutoRefCount<cSPEditorBlock_s0049_0a70>* mpCap;
    uint32_t mAlloc[2];
    VisitedVec(const AllocTag&);                            // @ 0x540470
    ~VisitedVec() { DestroyRange(mpBegin, mpEnd); Free(); }
    void DestroyRange(AutoRefCount<cSPEditorBlock_s0049_0a70>* b, AutoRefCount<cSPEditorBlock_s0049_0a70>* e);   // @ 0x454e90
    void Free();                                            // @ 0x425990
    void push_back(const AutoRefCount<cSPEditorBlock_s0049_0a70>& v);  // @ 0x4541f0
    AutoRefCount<cSPEditorBlock_s0049_0a70>* begin() { return mpBegin; }
    AutoRefCount<cSPEditorBlock_s0049_0a70>* end() { return mpEnd; }
};
void BuildPileList(cSPEditorBlock_s0049_0a70* block, BlockVec* list, bool b);   // @ 0x48c790
template<class I, class T> inline I find(I first, I last, const T& value)
{
    while (first != last && !(*first == value))
        ++first;
    return first;
}
// ---- items of slice s00490a70 end

// ---- items of slice s00491900 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPEditorBlock_s0049_1900 {
    char pad[0x3e0];
    void* tracker;                        // 0x3e0
    void* field3e4;                       // 0x3e4
};
struct Vec {
    void** begin;                         // 0
    void** end;                           // 4
    void Clear(void** a, void** b);
    void Insert(void** p);
};
// ---- items of slice s00491900 end

// ---- items of slice s004928d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_492de0_limit;
struct Vector3_s0049_28d0 {
    float x, y, z;
    float operator[](int i) const { return (&x)[i]; }
    Vector3_s0049_28d0() {}
    Vector3_s0049_28d0(const Vector3_s0049_28d0& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s0049_28d0& operator=(const Vector3_s0049_28d0& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct BoundingBox_s0049_28d0 {
    Vector3_s0049_28d0 mn;
    Vector3_s0049_28d0 mx;
};
struct cSPEditorBlock_s0049_28d0 {
    char pad0[0x48];
    Vector3_s0049_28d0 position;                     // 0x48
    char pad1[0x33c - 0x54];
    void* tracker;                        // 0x33c
    BoundingBox_s0049_28d0* GetBBox(BoundingBox_s0049_28d0* out, int a, int b, int c);  // 0x0044ae00 (cSPEditorBlock::GetBBox)
};
Vector3_s0049_28d0* Vector3_Sub_s0049_28d0(Vector3_s0049_28d0* out, const Vector3_s0049_28d0* a, const Vector3_s0049_28d0* b);
struct S935 {
    Vector3_s0049_28d0 a;
    Vector3_s0049_28d0 b;
    Vector3_s0049_28d0 Sub() const;
};
struct Vec3O {                                   // rw::math::fpu::Vector3Template<float,0>: out-of-line copy ctor
    float v[3];
    Vec3O(const Vec3O& o);                       // 0x004098a0
    float& operator[](int i) { return v[i]; }
    float operator[](int i) const { return v[i]; }
};
struct Matrix3_s0049_28d0 {
    float m[9];
    Matrix3_s0049_28d0() {}
    Matrix3_s0049_28d0(const Matrix3_s0049_28d0& src) { Assign(&src); }
    void Assign(const Matrix3_s0049_28d0* src);             // 0x0041cb40
};
struct Vec3W {                                  // Vector3 with inline movss copy + writable operator[]
    float x, y, z;
    Vec3W() {}
    Vec3W(const Vec3W& o) : x(o.x), y(o.y), z(o.z) {}
    float& operator[](int i) { return (&x)[i]; }
    float operator[](int i) const { return (&x)[i]; }
};
struct Vec3P { float x, y, z; };                 // plain POD triple (integer-register copies)
Vec3W* Vec_Sub(Vec3W* out, const Vec3W* a, const Vec3W* b);     // 0x0041db10
Vec3W* Vec_Sub(Vec3W* out, const Vec3O* a, const Vec3W* b);
Vec3W* Vec_Add(Vec3W* out, const Vec3W* a, const Vec3W* b);     // 0x0041dc10
Vec3W* Vec_MulMat(Vec3W* out, const Vec3W* v, const Matrix3_s0049_28d0* m);   // 0x0041daf0
Matrix3_s0049_28d0* Mat_Inverse(Matrix3_s0049_28d0* out, const Matrix3_s0049_28d0* m);                    // 0x0041ded0
float VectorLength(Vec3W* v);                                          // 0x0040ae50
struct cSPEditorBlock2;
struct BBox2 { Vec3P mn, mx; };                  // 24 bytes
struct cSPEditorBlock2 {
    char pad0[0x48];
    Vec3W position;                            // +0x48
    char pad54[0x60 - 0x54];
    Matrix3_s0049_28d0 rotation;                            // +0x60 (36 bytes)
    char pad1[0x33c - 0x84];
    cSPEditorBlock2* parent;                     // +0x33c
    char pad2[0xdc8 - 0x340];
    uint32_t bits[2];                            // +0xdc8 bitset<60>
    bool TestBit(unsigned i) const {
        if (i < 0x3c) {
            uint32_t w = bits[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
    BBox2* GetBBox(BBox2* out, int a, int b, int c);                     // 0x0044ae00
    void FUN_0043d240(Vec3W* out, int a);                              // 0x0043d240 (ret 8)
    int  FUN_0044e800();                                                 // 0x0044e800
    int  FUN_0044d9e0(Vec3W pos, float radius);                        // 0x0044d9e0 (ret 0x10)
    bool FUN_00438440(cSPEditorBlock2* other, int flag);                 // 0x00438440 (ret 8)
};
void Snap_004928d0(cSPEditorBlock2* blk, Vec3W pos, Matrix3_s0049_28d0 rot, Vec3W* outPos, Matrix3_s0049_28d0* outRot, int idx);
// ---- items of slice s004928d0 end


// ---- items of slice s00493640 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix3_s0049_3640 {
    float m[9];
    Matrix3_s0049_3640(const Matrix3_s0049_3640& src) { Assign(&src); }
    void Assign(const Matrix3_s0049_3640* src);      // 0x0041cb40
};
struct X3 {
    float x, y, z;
    X3() {}
    X3(const X3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct V3 {
    float x, y, z;
    V3() {}
    V3(float a, float b, float c) : x(a), y(b), z(c) {}
    V3& operator=(const X3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
    void SetX(float v) { x = v; }
    void SetY(float v) { y = v; }
};
struct Basis {
    V3 rows[3];
    V3& operator[](int i) { return rows[i]; }
};
template<int N> __forceinline void Scratch() { unsigned pad[N]; (void)pad; }
X3 operator-(const V3& v);                         // 0x00422020
V3 Normalize(const V3& v);                         // 0x00436ce0
V3 Cross(const V3& a, const V3& b);                // 0x0044e460
X3 operator*(const V3& v, const float& s);         // 0x0041dca0
float VectorLength(const V3* v);                   // 0x0040ae50
extern V3 kVecA;                                   // 0x015d6324
extern V3 kVecB;                                   // 0x015d63f4
void FUN_00493ce0(void* a, void* b, Matrix3_s0049_3640 m);
int ClassifyAgainstSymmetryPlane(V3* p, float width, float zmin, float zmax, Basis* out);
// ---- items of slice s00493640 end



// ---- items of slice s004942b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
struct cSPMatrix3_s0049_42b0;
struct cSPVector3_s0049_42b0 {
    float x, y, z;
    cSPVector3_s0049_42b0() {}
    cSPVector3_s0049_42b0(const cSPVector3_s0049_42b0& o);                                     // 0x004098a0
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPMatrix3_s0049_42b0 {
    cSPVector3_s0049_42b0 mRow[3];
    cSPMatrix3_s0049_42b0(const cSPMatrix3_s0049_42b0& o);                                     // 0x0041cb40
    cSPVector3_s0049_42b0& operator[](int i) { return mRow[i]; }
};
struct cSPBoundingBox_s0049_42b0 {
    cSPVector3_s0049_42b0 mMin;
    cSPVector3_s0049_42b0 mMax;
    void GetCorners(cSPVector3_s0049_42b0* corners);                                // 0x00466320
};
cSPVector3_s0049_42b0 operator+(const cSPVector3_s0049_42b0& a, const cSPVector3_s0049_42b0& b);          // 0x0041dc10
cSPVector3_s0049_42b0 operator-(const cSPVector3_s0049_42b0& a, const cSPVector3_s0049_42b0& b);          // 0x0041db10
cSPVector3_s0049_42b0 operator*(const cSPVector3_s0049_42b0& a, const float& s);               // 0x0041dca0
cSPVector3_s0049_42b0& operator*=(cSPVector3_s0049_42b0& a, const float& s);                   // 0x0041dba0
cSPVector3_s0049_42b0& operator+=(cSPVector3_s0049_42b0& a, const cSPVector3_s0049_42b0& b);              // 0x0041ddb0
cSPVector3_s0049_42b0 operator*(const cSPVector3_s0049_42b0& v, const cSPMatrix3_s0049_42b0& m);          // 0x0041daf0
cSPVector3_s0049_42b0 Cross(const cSPVector3_s0049_42b0& a, const cSPVector3_s0049_42b0& b);              // 0x00454c00
float Dot(const cSPVector3_s0049_42b0& a, const cSPVector3_s0049_42b0& b);                      // 0x00455cc0
float Length(const cSPVector3_s0049_42b0& v);                                        // 0x0040ae50
cSPVector3_s0049_42b0 Normalize(const cSPVector3_s0049_42b0& v);                                // 0x00436ce0
extern cSPVector3_s0049_42b0 g_ZAxis;         // 0x015d6324
extern cSPVector3_s0049_42b0 g_SymmetryAxis;  // 0x015d63f4
namespace EA {
template <class T> struct AutoRefCount_s0049_42b0 {
    T* mpObject;
    AutoRefCount_s0049_42b0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0049_42b0() { if (mpObject) mpObject->Release(); }
};
}
namespace eastl {
struct sp_vector_allocator_s0049_42b0 {};
}
namespace eastl {
struct bitset60 {
    uint32_t mWord[2];
    bool test(uint32_t i) const {
        if (i < 60)
            return (mWord[i / 32] & (1 << (i % 32))) != 0;
        return false;
    }
};
}
namespace SP {
class cSPEditorBlock_s0049_42b0;
}
namespace SP {
struct cSPEditorModel_s0049_42b0 {
    bool IsSymmetryEnabled();                                            // 0x004adc40 (byte +0x4f)
};
}
namespace SP {
struct cSPEditorSnapVector_s0049_42b0 {
    cSPVector3_s0049_42b0 mNormal;
    cSPVector3_s0049_42b0 mOrigin;
    void* mTriangleInfo;
    bool mLockToAxis;
    ~cSPEditorSnapVector_s0049_42b0();                                              // 0x004ae250
};
}
namespace SP {
struct BlockVector {   // eastl::vector<EA::AutoRefCount<cSPEditorBlock>, sp_vector_allocator>
    EA::AutoRefCount_s0049_42b0<cSPEditorBlock_s0049_42b0>* mpBegin;
    EA::AutoRefCount_s0049_42b0<cSPEditorBlock_s0049_42b0>* mpEnd;
    EA::AutoRefCount_s0049_42b0<cSPEditorBlock_s0049_42b0>* mpCapacity;
    BlockVector(const eastl::sp_vector_allocator_s0049_42b0& a = eastl::sp_vector_allocator_s0049_42b0());  // 0x00540470
    ~BlockVector();                                                      // 0x00453eb0
    void push_back(const EA::AutoRefCount_s0049_42b0<cSPEditorBlock_s0049_42b0>& v);           // 0x004541f0
};
}
namespace SP {
class cSPEditorBlock_s0049_42b0 {
public:
    virtual void v00();
    virtual int AddRef();                                                // +0x04
    virtual int Release();                                               // +0x08

    uint32_t pad04[9];
    cSPEditorModel_s0049_42b0* mEditorModel;            // +0x28
    uint32_t pad2c[13];
    cSPMatrix3_s0049_42b0 mOrientation;                 // +0x60
    uint32_t pad84[9];
    cSPMatrix3_s0049_42b0 mBaseOrientation;             // +0xa8
    uint32_t padcc[33];
    int mSnapType;                           // +0x150
    uint32_t pad154[122];
    cSPEditorBlock_s0049_42b0* mSymmetricBlock;         // +0x33c (AutoRefCount)
    uint32_t pad340[68];
    float mSnapHeightOffset;                 // +0x450
    uint32_t pad454[605];
    eastl::bitset60 mFlags;                  // +0xdc8

    cSPEditorModel_s0049_42b0* GetEditorModel() { return mEditorModel; }
    cSPEditorBlock_s0049_42b0* GetSymmetricBlock() { return mSymmetricBlock; }

    int GetSnapType();                                                   // 0x0044e7e0
    int GetSymmetryIndex();                                              // 0x0044f220
    cSPEditorSnapVector_s0049_42b0 GetSnapAxis(int index);                          // 0x0044d8f0
    cSPBoundingBox_s0049_42b0 GetBBox(int type, bool a, bool b);                    // 0x0044ae00
    bool IsPinnedOrLocked(bool b);                                       // 0x0043bbc0
    bool IsSymmetryLocked();                                             // 0x00435c80
};
}
namespace SP {
cSPVector3_s0049_42b0 normalized_safe(const cSPVector3_s0049_42b0& v);                          // 0x00449c20
}
namespace SP {
bool IsNAN(const cSPVector3_s0049_42b0& v);                                          // 0x00481f00
}
namespace SP {
namespace EditorUtils {
cSPMatrix3_s0049_42b0 GetSnapOrientation(cSPEditorBlock_s0049_42b0* symmetricBlock, cSPVector3_s0049_42b0 dir);           // 0x0049b460
}
}
namespace SP {
namespace EditorUtils {
cSPMatrix3_s0049_42b0 RotateOrientation(cSPMatrix3_s0049_42b0 m, cSPVector3_s0049_42b0 from, cSPVector3_s0049_42b0 to);              // 0x004906e0
}
}
namespace SP {
namespace EditorUtils {
cSPMatrix3_s0049_42b0 GetSymmetricOrientation(cSPEditorBlock_s0049_42b0* block, cSPMatrix3_s0049_42b0 m);                // 0x00493ce0
}
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s0049_42b0* PickBlocks(BlockVector& ignore, cSPVector3_s0049_42b0 start, cSPVector3_s0049_42b0 dir,
                           cSPVector3_s0049_42b0& hitPos, cSPVector3_s0049_42b0& hitNormal, int* pIndex,
                           bool& bHit, int* pLevel);                                     // 0x004a4840
}
}
// ---- items of slice s004942b0 end

// ---- items of slice s004956b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_tls_slot;                      // 0x016e4174
extern void* __stdcall TlsGetValue(uint32_t index);
extern void* g_vtbl_13ef554;
extern void* g_vtbl_13ef534;
extern void* g_vtbl_13ef55c;
struct Vector3_s0049_56b0 {
    float x, y, z;
};
struct MemMgr {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void Deallocate(void* p, int a, int b);
};
extern MemMgr* g_mem;                         // 0x016e4178
struct HkThreadMemory {
    void DeallocateChunk(void* p, int size, int cls);
};
struct D95 {
    void* vptr;
    void* Del(unsigned flags);
};
struct D960 {
    void* vptr;
    char pad[0xc];
    void* data;                               // 0x10
    char pad2[4];
    int cap;                                  // 0x18
    void Dtor();
    void* Del(unsigned flags);
};
struct D95fe0 {
    void* vptr;
    char pad[0x200];
    void* Ctor();
};
struct D961 {
    char pad[0x4c];
    void** data;                              // 0x4c
    int count;                                // 0x50
    int* Find(int* out, int key);
};
struct Vec_s0049_56b0 {
    void** begin;
    void** end;
};
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(float a, float b, float c) { x = a; y = b; z = c; }
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3_s0049_56b0 : Vector3T {
    cSPVector3_s0049_56b0() {}
    cSPVector3_s0049_56b0(float a, float b, float c) : Vector3T(a, b, c) {}
    __forceinline cSPVector3_s0049_56b0(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3_s0049_56b0& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T operator+(const Vector3T& a, const Vector3T& b);           // @ 0x41dc10
typedef float hkReal;
struct hkBool_s0049_56b0 {
    char m_bool;
    hkBool_s0049_56b0(bool b) { m_bool = (char)b; }
    hkBool_s0049_56b0& operator=(bool b) { m_bool = (char)b; return *this; }
    operator bool() const { return m_bool != 0; }
};
struct __declspec(align(16)) hkVector4_s0049_56b0 {
    hkReal x, y, z, w;
    __forceinline hkVector4_s0049_56b0() {}
    __forceinline hkVector4_s0049_56b0(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
    __forceinline hkVector4_s0049_56b0(const hkVector4_s0049_56b0& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    __forceinline void operator=(const hkVector4_s0049_56b0& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
};
struct hkPropertyValue_s0049_56b0 { uint32_t lo, hi; hkPropertyValue_s0049_56b0() {} hkPropertyValue_s0049_56b0(int v) : lo((uint32_t)v), hi(0) {} void* getPtr() const { return (void*)lo; } };
struct hkProperty_s0049_56b0 { uint32_t m_key; uint32_t pad; hkPropertyValue_s0049_56b0 m_value; };
struct hkCollidable_s0049_56b0 {
    char pad[0x10];
    int m_ownerOffset;                          // +0x10
    char pad2[0x24 - 0x14];
    void* getOwner() const { return (char*)this + m_ownerOffset; }
};
struct hkRigidBody_s0049_56b0 {
    char pad00[0x1c];
    hkCollidable_s0049_56b0 m_collidable;                  // +0x1c
    char pad40[0x4c - 0x1c - sizeof(hkCollidable_s0049_56b0)];
    hkProperty_s0049_56b0* m_properties;                   // +0x4c
    int m_numProperties;                        // +0x50
    char pad54[0x58 - 0x54];
    const hkCollidable_s0049_56b0* getCollidable() const { return &m_collidable; }
    void setPosition(const hkVector4_s0049_56b0& p);       // @ 0x1087820
    hkPropertyValue_s0049_56b0 getProperty(uint32_t key) const;   // @ 0x496140
    int getNumProperties() const { return m_numProperties; }
    hkBool_s0049_56b0 hasProperty(uint32_t key) const
    {
        for (int i = 0; i < getNumProperties(); i++) {
            if (m_properties[i].m_key == key)
                return hkBool_s0049_56b0(true);
        }
        return hkBool_s0049_56b0(false);
    }
};
inline hkRigidBody_s0049_56b0* hkGetRigidBody(const hkCollidable_s0049_56b0* c) { return (hkRigidBody_s0049_56b0*)c->getOwner(); }
struct hkRootCdPoint_s0049_56b0 {
    char pad[0x28];
    const hkCollidable_s0049_56b0* m_rootCollidableB;      // +0x28
    unsigned int m_shapeKeyB;
};
struct hkCollisionInput_s0049_56b0;
extern hkReal HK_REAL_EPSILON;                  // @ 0x13ef4f4
struct hkCdPointCollector_s0049_56b0 {
    hkReal m_earlyOutDistance;
    virtual ~hkCdPointCollector_s0049_56b0() {}            // vtable 0x13ef534
    virtual void addCdPoint(const void* event) = 0;
    virtual void reset();
};
struct AllCdPointCollector : hkCdPointCollector_s0049_56b0 {   // vtable 0x13ef55c
    char pad08[8];
    hkRootCdPoint_s0049_56b0* m_data;                      // +0x10
    int m_size;                                 // +0x14
    int m_capAndFlags;                          // +0x18
    char pad1c[4];
    char storage[8 * 0x30];
    AllCdPointCollector();                      // @ 0x495fe0
    ~AllCdPointCollector();                     // @ 0x4960d0
    virtual void addCdPoint(const void* event);
};
struct hkLinearCastInput_s0049_56b0 {
    hkVector4_s0049_56b0 m_to;
    hkReal m_maxExtraPenetration;
    hkReal m_startPointTolerance;
    hkLinearCastInput_s0049_56b0() { m_maxExtraPenetration = HK_REAL_EPSILON; m_startPointTolerance = HK_REAL_EPSILON; }
};
struct hkCdBodyPairCollector_s0049_56b0 {
    hkBool_s0049_56b0 m_earlyOut;
    hkCdBodyPairCollector_s0049_56b0() : m_earlyOut(false) {}
    virtual ~hkCdBodyPairCollector_s0049_56b0() {}         // vtable 0x13ef534 ?
    virtual void addCdBodyPair(const void* a, const void* b) = 0;
};
struct PenetrationCollector : hkCdBodyPairCollector_s0049_56b0 {   // vtable 0x13ef554
    uint32_t m_extra[4];
    PenetrationCollector() : hkCdBodyPairCollector_s0049_56b0() { m_earlyOut = false; }
    virtual ~PenetrationCollector() {}
    virtual void addCdBodyPair(const void* a, const void* b);
};
struct hkWorld_s0049_56b0 {
    char pad[0x78];
    hkCollisionInput_s0049_56b0* m_collisionInput;         // +0x78
    void linearCast(const hkCollidable_s0049_56b0* collA, const hkLinearCastInput_s0049_56b0& input,
                    hkCdPointCollector_s0049_56b0& castCollector, hkCdPointCollector_s0049_56b0* startCollector);   // @ 0x1082b90
    void getPenetrations(const hkCollidable_s0049_56b0* collA, const hkCollisionInput_s0049_56b0& input, hkCdBodyPairCollector_s0049_56b0& collector);   // @ 0x10867a0
    void updateCollisionFilterOnWorld(int mode, int fullCheck);                // @ 0x10869e0
    void updateCollisionFilterOnEntity(hkRigidBody_s0049_56b0* e, int mode, int fullCheck);   // @ 0x1084fa0
};
struct cSPEditorPhysicsWorld { hkWorld_s0049_56b0* World(); };                // @ 0x4b91c0
struct RefCountTemplate {
    virtual ~RefCountTemplate() {}
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release()                                                        // 0x00453540
    {
        int r = mnRefCount-- - 1;
        if (r)
            return r;
        mnRefCount = 1;
        delete this;
        return 0;
    }
};
struct cSPEditorModel {
    int vt;
    RefCountTemplate rc;                 // +4
    cSPEditorPhysicsWorld* GetPhysicsWorld();   // @ 0x4ad450
    void SetCollisionFilter(int info);          // @ 0x4ad470
    void NumberBlocks();                        // @ 0x4ad4e0
    bool IsSymmetryEnabled();                   // @ 0x4adc40
};
struct ModelRef {
    cSPEditorModel* mp;
    ModelRef(cSPEditorModel* p) : mp(p) { if (mp) mp->rc.AddRef(); }
    ~ModelRef() { if (mp) mp->rc.Release(); }
    cSPEditorModel* operator->() const { return mp; }
};
struct cSPEditorBlock_s0049_56b0;
struct cSPEditorBlock_s0049_56b0 {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    char pad04[0x28 - 4];
    cSPEditorModel* mEditorModel;                // +0x28
    char pad2c[0x34 - 0x2c];
    bool mFlag34;                                // +0x34
    char pad35[0x48 - 0x35];
    cSPVector3_s0049_56b0 mPosition;                        // +0x48
    char pad54[0x18c - 0x54];
    hkRigidBody_s0049_56b0* mpRigidBody;                    // +0x18c
    char pad190[0x33c - 0x190];
    cSPEditorBlock_s0049_56b0* mSymmetricBlock;             // +0x33c
    char pad340[0x3e0 - 0x340];
    cSPEditorBlock_s0049_56b0* mLinkedBlock;                // +0x3e0

    cSPEditorModel* GetEditorModel() { return mEditorModel; }
    cSPEditorBlock_s0049_56b0* GetLinkedBlock() { return mLinkedBlock; }
    cSPEditorBlock_s0049_56b0* GetSymmetricBlock() { return mSymmetricBlock; }
    bool FUN_44c030();                           // @ 0x44c030
    int GetCollisionFilterInfo();                // @ 0x451e90
    void SetCollisionFilterInfo(int info);       // @ 0x451e50
    void SetPosition(const Vector3T& p, bool b); // @ 0x448e90
};
struct BlockVec_s0049_56b0 {
    AutoRefCount<cSPEditorBlock_s0049_56b0>* mpBegin;
    AutoRefCount<cSPEditorBlock_s0049_56b0>* mpEnd;
    AutoRefCount<cSPEditorBlock_s0049_56b0>* mpCap;
    uint32_t mAlloc[2];
    BlockVec_s0049_56b0(const AllocTag&);                              // @ 0x540470
    ~BlockVec_s0049_56b0();                                            // @ 0x453eb0
    void push_back(const AutoRefCount<cSPEditorBlock_s0049_56b0>& v);  // @ 0x4541f0
    bool empty() const;                                     // @ 0x526430
    AutoRefCount<cSPEditorBlock_s0049_56b0>& operator[](uint32_t i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
    AutoRefCount<cSPEditorBlock_s0049_56b0>* begin() { return mpBegin; }
    AutoRefCount<cSPEditorBlock_s0049_56b0>* end() { return mpEnd; }
};
void BuildPileList(cSPEditorBlock_s0049_56b0* block, BlockVec_s0049_56b0* list, bool b);   // @ 0x48c790
template<class I, class T> inline I find_s0049_56b0(I first, I last, T value)
{
    while (first != last && !(*first == value))
        ++first;
    return first;
}
__forceinline hkVector4_s0049_56b0 ToHkVector4(const cSPVector3_s0049_56b0& v)
{
    float x = v[0];
    float y = v[1];
    float z = v[2];
    return hkVector4_s0049_56b0(x, y, z, 0.0f);
}
// ---- items of slice s004956b0 end


// ---- items of slice s00496300 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0049_6300 {
    float x, y, z;
};
Vector3_s0049_6300* Vector3_Sub_s0049_6300(Vector3_s0049_6300* out, const Vector3_s0049_6300* a, const Vector3_s0049_6300* b);   // 0x0041db10
float VectorLength(const Vector3_s0049_6300* v);                                     // 0x0040ae50
void* GetBoneForHandle(void* h);                                          // 0x004aa030
struct Bone {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual int v4();
    void* Get();                          // 0x0047e6c0
    int GetSomething();                   // 0x0047e680
    int Check();                          // 0x0044f220
};
struct LimbStructure {
    char pad[0x5c];
    void Ctor();                          // 0x00488850
    void Init(void* limb, int a, int b);  // 0x004891a0
    void UpdateScaleRange(void* limb, float f); // 0x0048b370
    void F();                             // 0x00488980
    ~LimbStructure();                     // 0x00488900
};
struct HolderA {
    void* Get();                          // 0x0047e6c0
};
// ---- items of slice s00496300 end


// ---- items of slice s00496d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix3_s0049_6d30 {
    float m[9];
    void Assign(const void* src);
};
char FUN_004a7e60(void* p);
char FUN_0043bd80(void* self, float f, Matrix3_s0049_6d30 m);
struct X973 {
    char pad[0xdc8];
    uint32_t flags;                       // 0xdc8
};
struct W {                                         // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    W() {}
    W(const W& v);                                 // 0x004098a0 (out of line)
};
struct V3_s0049_6d30 : W {
    V3_s0049_6d30() {}
    V3_s0049_6d30(const V3_s0049_6d30& v) { x = v.x; y = v.y; z = v.z; }
    V3_s0049_6d30(const W& v) { x = v.x; y = v.y; z = v.z; }
};
W operator-(const W& a, const W& b);               // 0x0041db10
W operator+(const W& a, const W& b);               // 0x0041dc10
W operator*(const W& a, const float& s);           // 0x0041dca0
W operator-(const W& v);                           // 0x00422020
float Dot3(const W* a, const W* b);                // 0x00455cc0
float VectorLength(const V3_s0049_6d30& v);                   // 0x0040ae50
inline float Abs(float v) { return (float)fabs(v); }
struct RayQuery {                                  // 0x2c bytes
    V3_s0049_6d30 mOrigin;                                    // +0x00
    V3_s0049_6d30 mDir;                                       // +0x0c
    bool mHit;                                     // +0x18
    char pad19[3];
    W mPoint;                                      // +0x1c
    float mT;                                      // +0x28
    RayQuery(V3_s0049_6d30 origin, V3_s0049_6d30 dir);                   // 0x005b1080 (ret 0x18)
    ~RayQuery();                                   // 0x00c2e4e0 (empty)
    void Cast(void* a, void* b, W origin, W dir);  // 0x005b1870 (ret 0x20)
    bool IsHit() const { return mHit; }
    W GetPoint() const { return mPoint; }
};
struct EditorBlockRay {
    char pad00[0x28];
    void* mEditorModel;                            // +0x28
    char pad2c[0x48 - 0x2c];
    V3_s0049_6d30 mPosition;                                  // +0x48
    float GetRadius();                             // 0x0043f250
};
// ---- items of slice s00496d30 end

// ---- items of slice s004974e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Matrix3_s0049_74e0 {
    float m[9];
    Matrix3_s0049_74e0(const Matrix3_s0049_74e0& src) { Assign(&src); }
    void Assign(const Matrix3_s0049_74e0* src);      // 0x0041cb40
};
struct Vector3_s0049_74e0 {
    float x, y, z;
    Vector3_s0049_74e0() {}
    Vector3_s0049_74e0(const Vector3_s0049_74e0& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s0049_74e0(float a, float b, float c) : x(a), y(b), z(c) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct Vec3O_s0049_74e0 {
    float v[3];
    Vec3O_s0049_74e0(const Vec3O_s0049_74e0& o); // 0x004098a0
    float& operator[](int i) { return v[i]; }
};
struct FlagOwner {
    void SetFlag(int flag, char v);       // 0x00435a10
};
void FUN_00498230(int p, char flag);
void* __stdcall FUN_00401050(int key, int a, int p, int b);
struct X5ae40 {
    void F();                             // 0x0045ae40
};
struct cSPEditorBlock_s0049_74e0 {
    virtual void pv0();
    virtual int AddRef();                  // +0x4
    virtual int Release();                 // +0x8
};
struct BlockRef {
    cSPEditorBlock_s0049_74e0* mp;
    BlockRef(cSPEditorBlock_s0049_74e0* p) : mp(p) { if (mp) mp->AddRef(); }
    ~BlockRef() { if (mp) mp->Release(); }
};
struct BlockVector_s0049_74e0 {
    BlockRef** mpBegin;
    BlockRef** mpEnd;
    BlockRef** mpCapacity;
    char mAllocator[4];
    BlockVector_s0049_74e0() : mpBegin(0), mpEnd(0), mpCapacity(0) { Init(); }
    ~BlockVector_s0049_74e0();                        // 0x00453eb0
    void Init();                           // 0x00429360 (allocator)
    void reserve(unsigned n);              // 0x004e0880
    void push_back(const BlockRef& r);     // 0x004541f0
};
struct DirVector {                         // vector<Vector3>: 12-byte elements
    Vector3_s0049_74e0* mpBegin;
    Vector3_s0049_74e0* mpEnd;
    Vector3_s0049_74e0* mpCapacity;
    char mAllocator[4];
    DirVector() : mpBegin(0), mpEnd(0), mpCapacity(0) { Init(); }
    ~DirVector();                          // 0x00540520
    void Init();                           // 0x00429360
    void push_back(const Vector3_s0049_74e0& v);      // 0x004739d0
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct EString {                           // eastl::basic_string<char>, empty
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    EString() : mpBegin(0), mpEnd(0), mpCapacity(0) {
        mpBegin = gEmpty;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    ~EString();                            // 0x00530670
    static char gEmpty[2];                 // 0x01667bac
};
struct X982;
struct Vec3P_s0049_74e0 { float a, b, c; };
Vec3O_s0049_74e0 normalized_safe(const Vec3O_s0049_74e0& in);                              // 0x00449c20
Vector3_s0049_74e0* Vec_Mul(Vector3_s0049_74e0* out, Vec3O_s0049_74e0* in, const float* scale);      // 0x0041dca0
Vector3_s0049_74e0* Vec_Sub(Vector3_s0049_74e0* out, Vector3_s0049_74e0* a, Vector3_s0049_74e0* b);             // 0x0041db10
void Vec_AddAssign(Vector3_s0049_74e0* a, Vector3_s0049_74e0* b);                          // 0x0041ddb0
Vector3_s0049_74e0* Vec_Negate(Vector3_s0049_74e0* out, Vector3_s0049_74e0* in);                      // 0x00422020
Vector3_s0049_74e0* Vec_NegateO(Vector3_s0049_74e0* out, Vec3O_s0049_74e0* in);                       // 0x00422020
Vector3_s0049_74e0 Vec_Normalize(const Vector3_s0049_74e0& in);                            // 0x00436ce0
float VectorLength(Vector3_s0049_74e0* v);                                      // 0x0040ae50
Vec3O_s0049_74e0 Vec_Normalize2(const Vec3O_s0049_74e0& in);                               // 0x00436ce0
bool FUN_004a7e60(X982* p);
int PickBlocks(BlockVector_s0049_74e0* blocks, Vector3_s0049_74e0 a, Vector3_s0049_74e0 b, Vector3_s0049_74e0* hitPos, Vector3_s0049_74e0* hitNormal,
               int* hitBlock, bool* flag, int c);                    // 0x004a4840
struct X982 : cSPEditorBlock_s0049_74e0 {
    char pad0[0x138 - 4];
    float dir[3];                          // 0x138
    char pad144[0x33c - 0x144];
    X982* parent;                          // 0x33c
    X982* Parent() const { return parent; }
    void** begin;                          // 0x340
    void** end;                            // 0x344
    char pad2[0xdc8 - 0x348];
    uint32_t bits[1];                      // 0xdc8
    bool GetFlag(unsigned i) const {
        if (i < 0x3c) {
            uint32_t w = bits[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
    bool FUN_00435c80();                   // 0x00435c80
    bool FUN_0043bd50(Vec3O_s0049_74e0 v, float f);   // 0x0043bd50
    bool FUN_0043bd50(Vector3_s0049_74e0 v, float f); // 0x0043bd50 (inline-copied argument)
    bool FUN_0043bc70(float a, float b);   // 0x0043bc70
    void FUN_0043ffa0(Matrix3_s0049_74e0 m);          // 0x0043ffa0
    void MoveTo(int a, Vector3_s0049_74e0 b, Vector3_s0049_74e0 c, char d);  // 0x00436fa0
};
void RepinBlockToTorso(X982* p, Vector3_s0049_74e0 v, Matrix3_s0049_74e0 m, int a);        // 0x0049fbd0
bool FUN_004982b0(X982* p, char a, float b, char c);
bool FUN_00498470(X982* p, Vector3_s0049_74e0* v, Matrix3_s0049_74e0* m1, Matrix3_s0049_74e0* m2, char a, float b, char c, int d);
// ---- items of slice s004974e0 end

// ---- items of slice s00498470 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
struct P3 { float x, y, z; };                   // plain POD triple (dword copies)
struct Vec3_s0049_8470 {
    float x, y, z;
    Vec3_s0049_8470() {}
    Vec3_s0049_8470(const Vec3_s0049_8470& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Vec3C : Vec3_s0049_8470 {
    Vec3C(const Vec3C& o);                      // 0x004098a0
};
struct Matrix3_s0049_8470 {
    float m[9];
    Matrix3_s0049_8470() {}
    Matrix3_s0049_8470(const Matrix3_s0049_8470& o);                  // 0x0041cb40 (Matrix3::Assign)
};
template <unsigned N> struct Bitset {
    u32 mWord[(N + 31) / 32];
    bool test(unsigned pos) const {
        bool r;
        if (pos < N) {
            u32 w = mWord[pos >> 5];
            r = (w & (1u << (pos % 32))) != 0;
        } else {
            r = false;
        }
        return r;
    }
};
struct RefCountV {
    virtual void rc0();
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();                              // 0x00453540
};
struct Model {                                  // SP::cSPEditorModel (retail layout: vptr, then refcount base at +4)
    virtual void m0();
    RefCountV rc;
    bool FUN_004adc40();                        // 0x004adc40
};
template <class T> struct AutoRefModel {
    T* mp;
    AutoRefModel(T* p) : mp(p) { if (mp) mp->rc.AddRef(); }
    ~AutoRefModel() { if (mp) mp->rc.Release(); }
};
struct IPicker {                                // ray-cast / pick service (intrusive refcounted, Release = vtable slot 1)
    virtual void s0();
    virtual void Release();
    bool RayCast(int type, Vec3C origin, Vec3_s0049_8470 dir, P3* hit, P3* normal, float* dist, bool flag);  // 0x004c4a30
    bool RayCast(int type, Vec3_s0049_8470 origin, Vec3_s0049_8470 dir, P3* hit, P3* normal, float* dist, bool flag);   // 0x004c4a30
    struct Block* PickResult(int type, Vec3_s0049_8470 hit);                                                       // 0x004c4d30
};
template <class T> struct AutoRef {
    T* mp;
    ~AutoRef() { if (mp) mp->Release(); }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};
template <class T> struct Ref {
    T* mp;
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};
struct Block {
    char pad0[0x28];
    Ref<Model> mEditorModel;                    // +0x28
    char pad1[0x33c - 0x2c];
    Ref<Block> mSocketBlock;                    // +0x33c
    Block** mSocketBegin;                       // +0x340 (vector of Block*)
    Block** mSocketEnd;                         // +0x344
    char pad2[0xdc8 - 0x348];
    Bitset<60> mFlags;                          // +0xdc8
    int GetSkinIdentifierForPicking();          // 0x0043a870
    void SetBooleanAttribute(int id, bool v);   // 0x00435a10
    float FUN_0043f3a0();                       // 0x0043f3a0
};
bool  __cdecl FUN_004974e0(Block* b, Vec3_s0049_8470 pos, P3* out, bool* ok, float f, uint8_t g);
Matrix3_s0049_8470* __cdecl MoveBlockAndTranslateSnappedBlocks(Matrix3_s0049_8470* ret, Block* b, Matrix3_s0049_8470 m);   // 0x00493ce0
bool  __cdecl FUN_004973f0(Block* b, Matrix3_s0049_8470* m, float f, uint8_t g);
void  __cdecl FUN_0049ec40(Block* b, P3* pos, Matrix3_s0049_8470* m1, Matrix3_s0049_8470* m2, bool e);
void  __cdecl FUN_004983d0(Block* b, bool v);
void  __cdecl FUN_00498230(Block* b, int v);
Block* __cdecl PickBlockForPinning(Block* b, int a30, Vec3_s0049_8470 origin, Vec3_s0049_8470 dir, P3* out1, P3* out2, int a38, int a34); // 0x004a4d60
P3* __cdecl FUN_0041db10(P3* out, const P3* a, const P3* b);        // vector difference a - b
P3* __cdecl Vector3_Normalize(P3* out, const P3* in);                   // 0x00436ce0
float __cdecl VectorLength(const P3* v);                                    // 0x0040ae50
struct Viewer {
    void GetCameraLocationInfo(P3* pos, void* info, int a, int b);          // 0x007c3d30
};
struct App {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual Viewer* GetViewer();                // slot 22 (+0x58)
};
App* __cdecl App_Get();                         // 0x0067dd10 (SP::App)
struct HandleData {
    char pad[8];
    struct { int a; P3 pos; } sub;            // Vec3 at +0xc
};
struct Handle {                                 // gizmo / handle object with a vtable
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual int GetTypeId();                    // slot 4 (+0x10)
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual P3* GetPosition(P3* out);       // slot 9 (+0x24)
    HandleData* FUN_0047e680();                 // 0x0047e680
    Block* FUN_0047e6c0();                      // 0x0047e6c0 (owning block)
};
// ---- items of slice s00498470 end

// ---- items of slice s00499410 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0049_9410 {
    float x, y, z;
    Vector3_s0049_9410() {}
    Vector3_s0049_9410(float ax, float ay, float az);          // 0x00436CA0
    Vector3_s0049_9410(const Vector3_s0049_9410& o) : x(o.x), y(o.y), z(o.z) {}
};
struct V3Agg { float x, y, z; };
struct Vec3I {
    float x, y, z;
    Vec3I() {}
    Vec3I(const Vec3I& o) { x = o.x; y = o.y; z = o.z; }
};
struct Vec3C_s0049_9410 {
    float x, y, z;
    Vec3C_s0049_9410() {}
    Vec3C_s0049_9410(const Vec3C_s0049_9410& o);                          // 0x004098A0
};
struct Plane {
    float a, b, c, d;
    Plane() {}
    Plane(float ax, float bx, float cx, float dx);   // 0x0044E410
};
extern Vector3_s0049_9410 g_15d64d8;
extern Vector3_s0049_9410 g_15d6324;
extern Vec3C_s0049_9410   g_15d64d8_v3c;                    // 0x015d64d8 (g_15d64d8 seen as Vec3C)
Vector3_s0049_9410* VectorSub(Vector3_s0049_9410* out, const Vector3_s0049_9410* a, const Vector3_s0049_9410* b);            // 0x41db10
Vector3_s0049_9410* VectorAdd(Vector3_s0049_9410* out, const Vector3_s0049_9410* a, const Vector3_s0049_9410* b);            // 0x41dc10
Vector3_s0049_9410* Vector3_Scale_s0049_9410(Vector3_s0049_9410* out, const float* s, const Vector3_s0049_9410* v);          // 0x41de40
Vector3_s0049_9410* Vector3_Negate(Vector3_s0049_9410* out, const Vector3_s0049_9410* v);                         // 0x422020
bool     Vector3Equal(const Vector3_s0049_9410* a, const Vector3_s0049_9410* b);                       // 0x4232c0
Vector3_s0049_9410* Vector3_Normalize(Vector3_s0049_9410* out, const Vector3_s0049_9410* v);                      // 0x436ce0
Vector3_s0049_9410* Cross(Vector3_s0049_9410* out, const Vector3_s0049_9410* a, const Vector3_s0049_9410* b);                // 0x44e460
float    VectorLength(const Vector3_s0049_9410* v);                                         // 0x40ae50
float    Dot3(const float* a, const float* b);                                   // 0x455cc0
void PlaneFromPointNormal(Plane* out, const Vector3_s0049_9410* p, const Vector3_s0049_9410* n);       // 0x44e510
bool IntersectRayPlane(const Vector3_s0049_9410* o, const Vector3_s0049_9410* d, const Plane* p, float* t); // 0x44e640
struct IBase0 { virtual void b0(); };
struct IRefCount {
    virtual void r0();
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
};
struct RefObj_s0049_9410 : IBase0, IRefCount { };
struct RefObj_s0049_9410;
struct SkinMgr;
struct AutoRefCountRefObj {
    RefObj_s0049_9410* mpObject;
    AutoRefCountRefObj(RefObj_s0049_9410* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCountRefObj();                                 // 0x004A9AE0
};
struct AutoRefCountSkinMgr {
    SkinMgr* mpObject;
    ~AutoRefCountSkinMgr();                                // 0x004A9B10
    SkinMgr* operator->() const { return mpObject; }
    operator SkinMgr*() const { return mpObject; }
};
struct Block;
struct Entity;
struct SkinMgr {
    bool   PickSkin(int pickId, Vector3_s0049_9410 org, Vector3_s0049_9410 dir, Vector3_s0049_9410* a, Vector3_s0049_9410* b, float* t, int c);  // 0x004C4A30
    // same function, origin given as a Vec3C (copied with the out-of-line copy ctor)
    bool   PickSkin(int pickId, Vec3C_s0049_9410 org, Vector3_s0049_9410 dir, Vector3_s0049_9410* a, Vector3_s0049_9410* b, float* t, int c);    // 0x004C4A30
    Block* GetBlockAtSkinPoint(Vec3C_s0049_9410 pt, int id);  // 0x004C4D30
};
struct Entity {
    char     pad0[0x28];
    RefObj_s0049_9410*  mp28;
    char     pad2c[0xdc8 - 0x2c];
    unsigned mFlagBits[2];
    RefObj_s0049_9410*  GetRefObj() { return mp28; }
    int      GetSkinIdentifierForPicking();                // 0x0043A870
    bool     HasAnyBlockFlag();                            // 0x00435D40
    unsigned GetWord(unsigned i) const { return mFlagBits[i]; }
    bool     TestFlag(unsigned pos) const {
        if (pos < 60)
            return (GetWord(pos >> 5) & (1u << (pos % 32))) != 0;
        return false;
    }
};
Block* PickBlockForPinning(Entity* e, unsigned arg, Vector3_s0049_9410 org, Vector3_s0049_9410 dir,
                           Vector3_s0049_9410* outPt, Vector3_s0049_9410* outN, bool* flag, int z);   // 0x004A4D60
void   FUN_0049c630(Vector3_s0049_9410* out, Vec3C_s0049_9410 pt, SkinMgr* skin);                   // 0x0049C630 cdecl
Vector3_s0049_9410* FUN_004a89e0(Vector3_s0049_9410* out, const Vector3_s0049_9410* a, const Vector3_s0049_9410* b);          // 0x004A89E0 cdecl
template <int N> inline void ScratchSlots_s0049_9410() { unsigned s[N]; }
struct DirSrc;
struct DirOwner {
    char pad0[0x28];
    DirSrc* mp28;
    char pad2c[0x48 - 0x2c];
    Vec3I mDir;                                          // +0x48
    DirSrc* GetSrc() { return mp28; }
    const Vec3I& GetDir() { return mDir; }
};
struct DirSrc {
    Vector3_s0049_9410 GetDir(Vec3I a, DirOwner* o, int z0, int z1, Vector3_s0049_9410 b);  // 0x004ABBC0 (hidden return slot first)
};
// ---- items of slice s00499410 end

// ---- items of slice s0049b340 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct BitOwner {
    char pad0[0xdc8];
    uint32_t bits[2];                     // 0xdc8, 0xdcc
    bool GetFlag(unsigned i) const {
        if (i < 0x3c) {
            uint32_t w = bits[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
struct Y9c0 {
    char pad0[0x3c9];
    char flag;                            // 0x3c9
    char pad1[0x3e0 - 0x3ca];
    void* tracker;                        // 0x3e0
    void Set(char v);
};
// ---- items of slice s0049b340 end


// ---- items of slice s004a6f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s004a_6f10 {
    float x, y, z;
    Vector3T_s004a_6f10() {}
    Vector3T_s004a_6f10(const Vector3T_s004a_6f10& v);                                    // 0x004098a0
    float operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3_s004a_6f10 : Vector3T_s004a_6f10 {
    cSPVector3_s004a_6f10() {}
    cSPVector3_s004a_6f10(const Vector3T_s004a_6f10& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
};
Vector3T_s004a_6f10 operator-(const Vector3T_s004a_6f10& a, const Vector3T_s004a_6f10& b);           // 0x0041db10
Vector3T_s004a_6f10 operator*(const float& s, const Vector3T_s004a_6f10& v);              // 0x0041de40
Vector3T_s004a_6f10& operator+=(Vector3T_s004a_6f10& a, const Vector3T_s004a_6f10& b);               // 0x0041ddb0
Vector3T_s004a_6f10 operator/(const Vector3T_s004a_6f10& v, const float& s);              // 0x00453880
float VectorLength(const cSPVector3_s004a_6f10& v);                            // 0x0040ae50
struct BoundingBox_s004a_6f10 {
    Vector3T_s004a_6f10 mMin, mMax;
    Vector3T_s004a_6f10 GetCenter() const;                                     // 0x00409b90
};
extern const Vector3T_s004a_6f10 kZeroVector;                                  // 0x015d64d8
template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(unsigned i) const
    {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
struct RefCountTemplate_s004a_6f10 {
    virtual ~RefCountTemplate_s004a_6f10();
    int mRefCount;
    int AddRef() { return mRefCount++ + 1; }
    int Release();                                                  // 0x00453540
};
template <class T> struct AutoRefCount_s004a_6f10 {
    T* mpObject;
    AutoRefCount_s004a_6f10(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004a_6f10() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cSPEditorBlock_s004a_6f10;
typedef AutoRefCount_s004a_6f10<cSPEditorBlock_s004a_6f10> BlockRef_s004a_6f10;
struct BlockVector_s004a_6f10 {
    BlockRef_s004a_6f10* mpBegin;
    BlockRef_s004a_6f10* mpEnd;
    BlockRef_s004a_6f10* mpCapacity;
    uint32_t  mAllocator[2];
    BlockVector_s004a_6f10(const AllocTag& a = AllocTag());                    // 0x00540470
    ~BlockVector_s004a_6f10();                                                 // 0x00453eb0
    void push_back(const BlockRef_s004a_6f10& v);                              // 0x004541f0
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef_s004a_6f10& operator[](int i) { return mpBegin[i]; }
    BlockRef_s004a_6f10* begin() { return mpBegin; }
    BlockRef_s004a_6f10* end() { return mpEnd; }
};
struct FixedBlockVector : BlockVector_s004a_6f10 {
    uint32_t mOverflow;
    void*    mBuffer[8];
    FixedBlockVector() { FixedInit(); }
    void FixedInit();                                               // 0x00453770
    FixedBlockVector& operator=(const BlockVector_s004a_6f10& x);              // 0x00453f20
};
template <class It, class T>
inline It find_s004a_6f10(It first, It last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}
struct cSPEditorModel_s004a_6f10;
struct cSPEditorBlock_s004a_6f10 {
    virtual void _v0();
    virtual int AddRef();                                           // +0x04
    virtual int Release();                                          // +0x08
    uint32_t pad04[(0x28 - 0x04) / 4];
    cSPEditorModel_s004a_6f10* mpModel;                                        // +0x028
    uint32_t pad2c[(0x340 - 0x2c) / 4];
    BlockVector_s004a_6f10 mChildren;                                          // +0x340
    uint32_t pad354[(0x3e0 - 0x354) / 4];
    BlockRef_s004a_6f10 mSymmetricBlock;                                       // +0x3e0
    BlockRef_s004a_6f10 mPairedBlock;                                          // +0x3e4
    uint32_t pad3e8[(0x3f0 - 0x3e8) / 4];
    void*    mpSymmetryHandle;                                      // +0x3f0
    uint32_t pad3f4[(0x5e4 - 0x3f4) / 4];
    int      mCost;                                                 // +0x5e4
    uint32_t pad5e8[(0xdc8 - 0x5e8) / 4];
    bitset<60> mFlags;                                              // +0xdc8

    cSPEditorModel_s004a_6f10* GetEditorModel() { return mpModel; }
    cSPEditorBlock_s004a_6f10* GetSymmetricBlock() { return mSymmetricBlock; }
    cSPEditorBlock_s004a_6f10* GetPairedBlock() { return mPairedBlock; }
    void* GetSymmetryHandle() { return mpSymmetryHandle; }
    int GetCost() { return mCost; }
    bool IsValid();                                                 // 0x0044c030
    void SetBooleanAttribute(int id, bool value);                   // 0x00435a10
    int GetSymmetryIndex();                                         // 0x0044f220
    bool IsSymmetryLocked();                                        // 0x00435c80
    void AttachChild(cSPEditorBlock_s004a_6f10* child);                        // 0x00438700
    Vector3T_s004a_6f10 GetOffsetA(bool b);                                    // 0x00438120
    Vector3T_s004a_6f10 GetOffsetB(bool b);                                    // 0x004381e0
    void Place(Vector3T_s004a_6f10 a, Vector3T_s004a_6f10 b);                             // 0x00437b00
    BoundingBox_s004a_6f10 GetBBox(int a, int b, int c);                       // 0x0044ae00
};
struct cSPEditorModelBase {
    virtual ~cSPEditorModelBase();
};
struct cSPEditorModel_s004a_6f10 : cSPEditorModelBase, RefCountTemplate_s004a_6f10 {     // RefCountTemplate at +4
    int GetBlockCount();                                            // 0x004accf0
    cSPEditorBlock_s004a_6f10* GetBlock(int index);                            // 0x004accb0
    void SetUsingSymmetry(bool b);                                  // 0x004adc20
    bool IsUsingSymmetry();                                         // 0x004adc40
    void RemoveBlock(cSPEditorBlock_s004a_6f10* block, bool b);                // 0x004acab0
};
union MessageParam {
    int   i;
    float f;
    void* p;
    uint32_t pad[2];
};
struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SendMessage(uint32_t id, void* data, int flags);  // +0x14
};
struct cMessageManager {
    void RemoveListener(cSPEditorBlock_s004a_6f10* block);                     // 0x0045b150
};
IMessageServer* MessageServer();                                    // 0x0067dcc0
cMessageManager* MessageManager();                                  // 0x00401050
// ---- items of slice s004a6f10 end

// ---- items of slice s004a7c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int GetRecorderState();
extern void KillSetiEffects(int a, int b);
extern void GetBoolProperty(void* props, unsigned int id, bool* out);   // 0x407190 cdecl
struct Key {
    uint32_t mInstance;   // +0x0
    uint32_t mType;       // +0x4
    uint32_t mGroup;      // +0x8
};
struct ResKeySource {
    char pad0[0xc];
    Key GetKey(int mode, int arg);
};
struct cSPEditorBlock_s004a_7c30;
struct cSPEditorModel_s004a_7c30;
struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    void**     mpCapacity;
    void push_back(const uint32_t& value);
};
struct cSPEditorModel_s004a_7c30 {
    char pad0[0x18];
    bool FUN_004adc40();             // +0x0
    int  GetBlockCount();            // 0x4accf0
    cSPEditorBlock_s004a_7c30* GetBlock(int i); // 0x4accb0
};
struct BlockRef_s004a_7c30 {
    cSPEditorBlock_s004a_7c30* mpObject;
    cSPEditorBlock_s004a_7c30* get() { return mpObject; }
    cSPEditorBlock_s004a_7c30* operator->() { return mpObject; }
};
struct Alloc { Alloc() {} };                       // empty tag (temporary)
struct SpAlloc { uint32_t mName; void Init(const Alloc&); };   // 0x429360 (ret 4)
struct BlockVec_s004a_7c30 {
    BlockRef_s004a_7c30* mpBegin;
    BlockRef_s004a_7c30* mpEnd;
    BlockRef_s004a_7c30* mpCapacity;
    SpAlloc mAlloc;
    uint32_t mPad;
    BlockVec_s004a_7c30(const Alloc&);          // 0x540470
    BlockVec_s004a_7c30(const Alloc& a, int) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mAlloc.Init(a); }
    ~BlockVec_s004a_7c30();                     // 0x453eb0
    BlockRef_s004a_7c30& operator[](int i) { return mpBegin[i]; }
    int size() { return mpEnd - mpBegin; }
    void* erase(BlockRef_s004a_7c30* first, BlockRef_s004a_7c30* last);   // 0x454280
};
struct cSPEditorBlock_s004a_7c30 {
    char pad0[0xc];
    void* mPropList;                 // +0xc
    char pad0b[0x28 - 0x10];
    cSPEditorModel_s004a_7c30* mEditorModel;    // +0x28
    char pad1[0x33c - 0x2c];
    cSPEditorBlock_s004a_7c30* mSocketConnector; // +0x33c
    cSPEditorBlock_s004a_7c30* GetParent2() { cSPEditorBlock_s004a_7c30* r = mSocketConnector; return r; }
    BlockVec_s004a_7c30 mChildren;              // +0x340
    char pad2[0x3e0 - 0x354];
    cSPEditorBlock_s004a_7c30* mLinked;         // +0x3e0
    char pad3[0xdc8 - 0x3e4];
    uint32_t mFlags[4];              // +0xdc8

    bool HasAnyBlockFlag();          // 0x435d40
    int  CalculateSymmetrySign();    // 0x44f240
    int  F44c050();
    bool F44c030();
    void F44ba20(int, int);
    void F44bcf0(int, int);
    cSPEditorBlock_s004a_7c30* GetLinked() { return mLinked; }
    cSPEditorModel_s004a_7c30* GetModel() { return mEditorModel; }
    void* GetPropList() { void* r = mPropList; return r; }
    bool IsFlagSet(unsigned int index)
    {
        bool result;
        uint32_t flag;
        if (index < 0x3c) { flag = mFlags[index / 32]; result = (flag & (1u << (index % 32))) != 0; }
        else { result = false; }
        return result;
    }
    cSPEditorBlock_s004a_7c30* GetParent() { return mSocketConnector; }
};
extern bool FUN_004986d0(cSPEditorBlock_s004a_7c30* b);
struct RefObj_s004a_7c30 {
    char pad0[0x3e0];
    void SetRef(int v);              // 0x438cc0
};
struct Vec3_s004a_7c30 { float x, y, z; };
struct Mat3 { float m[9]; };
struct XformMsg {
    uint16_t mFlags;     // +0x0
    uint16_t mCount;     // +0x2
    Vec3_s004a_7c30     mPos;       // +0x4
    uint32_t mUnk10;     // +0x10
    Mat3     mMat;       // +0x14
    char pad[0x38 - 0x38];
    XformMsg();                                                          // 0x00434040
};
struct EffectsManager {
    void* vtable;
};
extern EffectsManager* GetEffectsManager();                              // 0x0067ddd0
static void* VSlot(void* obj, int off) { return *(void**)(*(char**)obj + off); }
extern void FUN_0049dd20(cSPEditorBlock_s004a_7c30* b, BlockVec_s004a_7c30* out, int one);   // cdecl
// ---- items of slice s004a7c30 end

// ---- items of slice s004a89e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* UncheckedIdl0(void* out, void* tag, void* arg);
extern void Matrix3FromFacingAndUp(void* out, void* facing, void* up);
extern void* FUN_004a9b40(void* out, const void* in);
extern void Matrix3Assign(void* out, void* in);
extern void* FUN_00422020(void* out, void* in);
extern void FUN_004098a0(void* in);
extern void* FUN_0044e460(void* out, void* a, void* b);
extern double FUN_0040ae50(void* in);
extern void FUN_00449cc0(void* out);
struct V3_s004a_89e0 {
    float x, y, z;
    float& operator[](int i) { return ((float*)this)[i]; }
};
struct cSPEditorBlock_s004a_89e0;
struct BlockVec_s004a_89e0 {
    cSPEditorBlock_s004a_89e0** mpBegin;
    cSPEditorBlock_s004a_89e0** mpEnd;
    void** mpCapacity;
};
struct cSPEditorBlock_s004a_89e0 {
    char pad0[0x340];
    BlockVec_s004a_89e0 mChildren;              // +0x340
    char pad1[0xdc8 - 0x34c];
    uint32_t mFlags[4];              // +0xdc8

    bool IsFlagSet(unsigned int index)
    {
        bool result;
        uint32_t flag;
        if (index < 0x3c) { flag = mFlags[index / 32]; result = (flag & (1u << (index % 32))) != 0; }
        else { result = false; }
        return result;
    }
};
struct M3 {
    V3_s004a_89e0 m[3];
    M3(float a, float b, float c, float d, float e, float f,
       float g, float h, float i);
};
// ---- items of slice s004a89e0 end


// ---- items of slice s006414e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct IRefCounted_s0064_14e0 {
    virtual int AddRef();
    virtual int Release();
};
struct cAssetMetadata : IRefCounted_s0064_14e0 {
    uint64_t* FUN_005507a0();     // 0x005507A0
    uint64_t* FUN_00550840();     // 0x00550840
    uint64_t* FUN_00550860();     // 0x00550860
    uint64_t  FUN_005508a0();     // 0x005508A0
    bool      FUN_00550970();     // 0x00550970
};
template <class T>
struct AutoRef_s0064_14e0 {
    T* mpObject;
    AutoRef_s0064_14e0() : mpObject(0) {}
    ~AutoRef_s0064_14e0() { if (mpObject) mpObject->Release(); }
    AutoRef_s0064_14e0& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
struct IResource : IRefCounted_s0064_14e0 {
    virtual void s2();
    virtual IRefCounted_s0064_14e0* Cast(uint32_t id);   // +0xC
};
struct IResourceManager {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual bool GetResource(const ResourceKey* k, AutoRef_s0064_14e0<IResource>* out, int a, int b, int c, int d);   // +0xC
    virtual bool GetResourceEx(const ResourceKey* k, void* slot, AutoRef_s0064_14e0<IResource>* out, int a, int b, int c, int d, int e);   // +0x10
};
IResourceManager* GetManager();   // 0x0067DCD0
// ---- items of slice s006414e0 end

// ---- items of slice s0049a2a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
struct Vector3T_s0049_a2a0 {
    float x, y, z;
    Vector3T_s0049_a2a0() {}
    Vector3T_s0049_a2a0(const Vector3T_s0049_a2a0& v);                                    // 0x004098A0
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3_s0049_a2a0 : Vector3T_s0049_a2a0 {
    cSPVector3_s0049_a2a0() {}
    cSPVector3_s0049_a2a0(const cSPVector3_s0049_a2a0& v) : Vector3T_s0049_a2a0(v) {}
    cSPVector3_s0049_a2a0(const Vector3T_s0049_a2a0& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    cSPVector3_s0049_a2a0& operator=(const Vector3T_s0049_a2a0& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
};
struct Vector3_s0049_a2a0 {
    float x, y, z;
    Vector3_s0049_a2a0(const Vector3T_s0049_a2a0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix33T {
    Vector3T_s0049_a2a0 xAxis;
    Vector3T_s0049_a2a0 yAxis;
    Vector3T_s0049_a2a0 zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m);                                  // 0x0041CB40
};
struct cSPMatrix3_s0049_a2a0 : Matrix33T {
    cSPMatrix3_s0049_a2a0() {}
    cSPMatrix3_s0049_a2a0(const cSPMatrix3_s0049_a2a0& m) : Matrix33T(m) {}
};
struct Plane_s0049_a2a0 {
    float a, b, c, d;
    Plane_s0049_a2a0() {}
    Plane_s0049_a2a0(float a, float b, float c, float d);                      // 0x0044E410
};
Vector3T_s0049_a2a0 operator-(const Vector3T_s0049_a2a0& v);                              // 0x00422020
Vector3T_s0049_a2a0 operator*(const Vector3T_s0049_a2a0& v, const float& s);              // 0x0041DCA0
Vector3T_s0049_a2a0 operator*(const float& s, const Vector3T_s0049_a2a0& v);              // 0x0041DE40
Vector3T_s0049_a2a0 operator+(const Vector3T_s0049_a2a0& a, const Vector3T_s0049_a2a0& b);           // 0x0041DC10
Vector3T_s0049_a2a0 operator-(const Vector3T_s0049_a2a0& a, const Vector3T_s0049_a2a0& b);           // 0x0041DB10
float Dot3(const Vector3T_s0049_a2a0& a, const Vector3T_s0049_a2a0& b);                   // 0x00455CC0
cSPVector3_s0049_a2a0 Normalize(const Vector3T_s0049_a2a0& v);                            // 0x00436CE0
float VectorLength(const cSPVector3_s0049_a2a0& v);                            // 0x0040AE50
bool IntersectRayPlane(const Vector3T_s0049_a2a0& origin, const Vector3T_s0049_a2a0& dir,
                       const Plane_s0049_a2a0& plane, float& t);               // 0x0044E640
struct cSPPlane : Plane_s0049_a2a0 {
    cSPPlane(const cSPVector3_s0049_a2a0& normal, const cSPVector3_s0049_a2a0& point)
        : Plane_s0049_a2a0(normal[0], normal[1], normal[2], -Dot3(point, normal)) {}
};
extern cSPVector3_s0049_a2a0 gSymmetryPlaneNormal;                             // 0x015D6370
extern cSPVector3_s0049_a2a0 gSymmetryPlanePoint;                              // 0x015D64D8
struct allocator {
    allocator() {}
};
template<int N>
struct bitset_s0049_a2a0 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const
    {
        if (i < N) {
            uint32_t w = mWord[i >> 5];
            return (w & (1 << (i % 32))) != 0;
        }
        return false;
    }
};
struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
};
struct cSPVector3Vector {
    cSPVector3_s0049_a2a0* mpBegin;
    cSPVector3_s0049_a2a0* mpEnd;
    cSPVector3_s0049_a2a0* mpCapacity;
    sp_vector_allocator mAllocator;
    cSPVector3Vector(const allocator& a = allocator());             // 0x00540470
    ~cSPVector3Vector()
    {
        for (cSPVector3_s0049_a2a0* p = mpBegin; p < mpEnd; ++p) {}
        DeallocateSelf();
        ScratchSlots<3>();      // VectorBase::DeallocateSelf frame
    }
    void DeallocateSelf();                                          // 0x005156B0
    void push_back(const cSPVector3_s0049_a2a0& v);                            // 0x004739D0
};
struct cSPMatrix3Vector {
    cSPMatrix3_s0049_a2a0* mpBegin;
    cSPMatrix3_s0049_a2a0* mpEnd;
    cSPMatrix3_s0049_a2a0* mpCapacity;
    sp_vector_allocator mAllocator;
    cSPMatrix3Vector(const allocator& a = allocator());             // 0x00540470
    ~cSPMatrix3Vector()
    {
        for (cSPMatrix3_s0049_a2a0* p = mpBegin; p < mpEnd; ++p) {}
        DeallocateSelf();
        ScratchSlots<3>();      // VectorBase::DeallocateSelf frame
    }
    void DeallocateSelf();                                          // 0x004AB0D0
    void push_back(const cSPMatrix3_s0049_a2a0& m);                            // 0x004AA080
};
struct RefCountTemplate_s0049_a2a0 {
    virtual ~RefCountTemplate_s0049_a2a0();
    int mRefCount;
    int AddRef() { return mRefCount++ + 1; }
    int Release()                                                   // 0x00453540
    {
        int n = mRefCount - 1;
        mRefCount = mRefCount - 1;
        if (n == 0) {
            mRefCount = 1;
            delete this;
            return 0;
        }
        return n;
    }
};
namespace SP {
struct cSPEditorModelBase_s0049_a2a0 {
    virtual ~cSPEditorModelBase_s0049_a2a0();
};
}
namespace SP {
struct cSPEditorModel_s0049_a2a0 : cSPEditorModelBase_s0049_a2a0, RefCountTemplate_s0049_a2a0 {     // RefCountTemplate at +4
    float GetGridSize();                                            // 0x004ADAA0
    float GetSize1();                                               // 0x004ADB00
    float GetSize2();                                               // 0x004ADB40
    bool IsUsingSymmetry();                                         // 0x004ADC40
};
}
namespace SP {
struct cSPEditorSkinManager_s0049_a2a0 {
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
template<class T> struct AutoRefCount_s0049_a2a0 {
    T* mpObject;
    AutoRefCount_s0049_a2a0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s0049_a2a0(const AutoRefCount_s0049_a2a0& x) { mpObject = x.mpObject; if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0049_a2a0() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}
namespace SP {
enum eSkinIdentifier {};
}
namespace SP {
struct cSPEditorBlock_s0049_a2a0 {
    uint32_t pad00[0x28 / 4];
    cSPEditorModel_s0049_a2a0* mEditorModel;                                   // +0x028
    uint32_t pad2c[(0x48 - 0x2c) / 4];
    cSPVector3_s0049_a2a0 mPosition;                                           // +0x048
    uint32_t pad54[(0xa8 - 0x54) / 4];
    cSPMatrix3_s0049_a2a0 mBaseOrientation;                                    // +0x0a8
    uint32_t padcc[(0x138 - 0xcc) / 4];
    Vector3_s0049_a2a0 mSurfaceNormal;                                         // +0x138
    uint32_t pad144[(0x33c - 0x144) / 4];
    AutoRefCount_s0049_a2a0<cSPEditorBlock_s0049_a2a0> mParentBlock;                      // +0x33c
    uint32_t pad340[(0x3c8 - 0x340) / 4];
    bool mIsPinningAntiAliased;                                     // +0x3c8
    bool mIsOnGround;                                               // +0x3c9
    cSPVector3_s0049_a2a0 mBlockPickDirection;                                 // +0x3cc
    uint32_t pad3d8[(0x3e0 - 0x3d8) / 4];
    AutoRefCount_s0049_a2a0<cSPEditorBlock_s0049_a2a0> mSymmetricBlock;                   // +0x3e0
    uint32_t pad3e4[(0xdc8 - 0x3e4) / 4];
    bitset_s0049_a2a0<60> mFlags;                                              // +0xdc8

    int AddRef();
    int Release();
    cSPEditorModel_s0049_a2a0* GetEditorModel() { return mEditorModel; }
    cSPEditorBlock_s0049_a2a0* GetParent() { return mParentBlock.get(); }
    void SetSurfaceNormal(Vector3_s0049_a2a0 normal) { mSurfaceNormal = normal; }
    eSkinIdentifier GetSkinIdentifierForPicking();                  // 0x0043A870
    float GetStackingDistance();                                    // 0x00448380
    void AttachChild(cSPEditorBlock_s0049_a2a0* child);                        // 0x00438700
    void DetachChild(cSPEditorBlock_s0049_a2a0* child);                        // 0x00438A40
    void MoveTo(int snapIndex, Vector3_s0049_a2a0 position, Vector3_s0049_a2a0 direction, bool snapped);  // 0x00436FA0
};
}
namespace SP {
struct BlockVector_s0049_a2a0 {
    AutoRefCount_s0049_a2a0<cSPEditorBlock_s0049_a2a0>* mpBegin;
    AutoRefCount_s0049_a2a0<cSPEditorBlock_s0049_a2a0>* mpEnd;
    AutoRefCount_s0049_a2a0<cSPEditorBlock_s0049_a2a0>* mpCapacity;
    uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    AutoRefCount_s0049_a2a0<cSPEditorBlock_s0049_a2a0>& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
struct cMessageManager_s0049_a2a0 {
    void PostBlockMessage(uint32_t id, int a, cSPEditorBlock_s0049_a2a0* block, int b);          // 0x0045AE40
    void PostTransformMessage(uint32_t id, int a, cSPVector3_s0049_a2a0* pos, cSPMatrix3_s0049_a2a0* orient); // 0x0045AED0
};
}
namespace SP {
cMessageManager_s0049_a2a0* MessageManager_s0049_a2a0();                                  // 0x00401050
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s0049_a2a0* FindPinningBlock(cSPEditorBlock_s0049_a2a0* block, cSPVector3_s0049_a2a0 origin, cSPVector3_s0049_a2a0 dir,
                                 AutoRefCount_s0049_a2a0<cSPEditorSkinManager_s0049_a2a0> skinManager,
                                 cSPVector3_s0049_a2a0* pPosition, cSPVector3_s0049_a2a0* pNormal, BlockVector_s0049_a2a0& blocks,
                                 int* pSnapIndex, bool* pSnapped);  // 0x00498F10
}
}
namespace SP {
namespace EditorUtils {
bool GetMissStackingPosition(cSPEditorBlock_s0049_a2a0* block, BlockVector_s0049_a2a0& blocks, cSPVector3_s0049_a2a0 origin,
                             cSPVector3_s0049_a2a0 dir, cSPMatrix3_s0049_a2a0 orientation, cSPVector3_s0049_a2a0& position);  // 0x0048DCD0
}
}
namespace SP {
namespace EditorUtils {
int ClassifyAgainstSymmetryPlane(cSPVector3_s0049_a2a0& position, float gridSize, float size1,
                                 float size2, int* pOut);           // 0x00493640
}
}
namespace SP {
namespace EditorUtils {
cSPMatrix3_s0049_a2a0 GetOrientationForNormal(cSPEditorBlock_s0049_a2a0* block, Vector3_s0049_a2a0 normal);  // 0x0049C210
}
}
namespace SP {
namespace EditorUtils {
void RepinBlockToTorso(cSPEditorBlock_s0049_a2a0* block, Vector3_s0049_a2a0 position, cSPMatrix3_s0049_a2a0 orientation,
                       bool b);                                     // 0x0049FBD0
}
}
// ---- items of slice s0049a2a0 end

// ---- items of slice s0049fbd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_zero;                 // 0x1485378
struct Vector3T_s0049_fbd0 {
    float x, y, z;
    Vector3T_s0049_fbd0() {}
    Vector3T_s0049_fbd0(const Vector3T_s0049_fbd0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix33T_s0049_fbd0 {
    Vector3T_s0049_fbd0 xAxis, yAxis, zAxis;
    Matrix33T_s0049_fbd0() {}
    Matrix33T_s0049_fbd0(const Matrix33T_s0049_fbd0& m) : xAxis(m.xAxis), yAxis(m.yAxis), zAxis(m.zAxis) {}
};
struct cSPVector3_s0049_fbd0 : Vector3T_s0049_fbd0 {               // out-of-line copy ctor (Vector3Template copy)
    cSPVector3_s0049_fbd0() {}
    cSPVector3_s0049_fbd0(const Vector3T_s0049_fbd0& v);              // 0x4098a0
    cSPVector3_s0049_fbd0(const cSPVector3_s0049_fbd0& v);            // 0x4098a0
};
struct Mat3B;
struct cSPMatrix3_s0049_fbd0 : Matrix33T_s0049_fbd0 {              // out-of-line copy ctor (Matrix3::Assign)
    cSPMatrix3_s0049_fbd0() {}
    explicit cSPMatrix3_s0049_fbd0(const Mat3B& m);        // 0x449cc0 (wrapper that calls Matrix3::Assign)
    cSPMatrix3_s0049_fbd0(const Matrix33T_s0049_fbd0& m);             // 0x41cb40
    cSPMatrix3_s0049_fbd0(const cSPMatrix3_s0049_fbd0& m);            // 0x41cb40
};
struct PodVec { float x, y, z; };
struct Mat3Id : Matrix33T_s0049_fbd0 {                  // default ctor
    Mat3Id();                                   // 0x402ab0
};
struct Mat3B : Matrix33T_s0049_fbd0 {};                 // tag: selects the 0x449cc0 constructor
template<int N> struct bitset_s0049_fbd0 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
template<typename T> struct LimbVec {
    T* b; T* e; T* c; int allocPair[2];
    LimbVec() { b = 0; e = 0; c = 0; }
    LimbVec(char& a);                            // @ 0x540470
    void push_back(const T& v);                  // @ 0x454860
    ~LimbVec() { for (T* p = b; p < e; ++p) {} Free(); }
    void Free();                                 // @ 0x425990
    T* at(int i) { return b + i; }
    T& operator[](int i) { return *(b + i); }
};
struct cSPEditorModel_s0049_fbd0;
struct cSPEditorBlock_s0049_fbd0 {
    virtual void _v0();
    char pad0[0x28 - 4];
    cSPEditorModel_s0049_fbd0* mEditorModel;                // +0x28
    char pad1[0x48 - 0x2c];
    Vector3T_s0049_fbd0 mPosition;                          // +0x48
    char pad2[0x60 - 0x54];
    Matrix33T_s0049_fbd0 mOrientation;                      // +0x60
    char pad3[0xa8 - 0x84];
    Matrix33T_s0049_fbd0 mTorsoMat;                         // +0xa8
    char pad4[0x33c - 0xcc];
    void* mSocketConnector;                      // +0x33c
    LimbVec<cSPEditorBlock_s0049_fbd0*> mChildren;          // +0x340 (begin,end)
    char pad5[0x3e0 - 0x354];
    cSPEditorBlock_s0049_fbd0* mParent;                     // +0x3e0
    char pad6[0xdc8 - 0x3e4];
    bitset_s0049_fbd0<60> mFlags;                           // +0xdc8
    cSPEditorModel_s0049_fbd0* GetEditorModel() { return mEditorModel; }
    void FUN_448e90(cSPVector3_s0049_fbd0* v, int a);       // @ 0x448e90
    void FUN_449420(Matrix33T_s0049_fbd0* m, int a);        // @ 0x449420
    void FUN_43ffa0(cSPMatrix3_s0049_fbd0 m);               // @ 0x43ffa0
    float* GetBBox(float* out, int, int, int);   // @ 0x44ae00
};
struct cSPEditorModel_s0049_fbd0 {
    cSPEditorBlock_s0049_fbd0* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
    bool FUN_4adc40();                           // @ 0x4adc40
    float FUN_4adaa0();                          // @ 0x4adaa0
};
struct cSPEditorLimbStructure {
    char d[0x58];
    cSPEditorLimbStructure();                   // 0x488850
    ~cSPEditorLimbStructure();                  // 0x488900
    void FUN_4891a0(cSPEditorBlock_s0049_fbd0*, int, int); // 0x4891a0
    void FixAllJoints();                        // 0x489ae0
    void FUN_488980();                          // 0x488980
};
struct RefBlockVec {
    cSPEditorBlock_s0049_fbd0** b; cSPEditorBlock_s0049_fbd0** e; cSPEditorBlock_s0049_fbd0** c; int allocPair[2];
    RefBlockVec(char& a);                       // 0x540470
    ~RefBlockVec();                             // 0x453eb0
};
cSPEditorBlock_s0049_fbd0* FUN_4a5a70(cSPEditorModel_s0049_fbd0* m);
cSPEditorBlock_s0049_fbd0* FUN_4a5970(cSPEditorBlock_s0049_fbd0* b);
Vector3T_s0049_fbd0* FUN_41db10(Vector3T_s0049_fbd0* out, const Vector3T_s0049_fbd0* a, const Vector3T_s0049_fbd0* b);   // a - b
Vector3T_s0049_fbd0* FUN_41dc10(Vector3T_s0049_fbd0* out, const Vector3T_s0049_fbd0* a, const Vector3T_s0049_fbd0* b);   // a - b
Vector3T_s0049_fbd0* FUN_41dca0(Vector3T_s0049_fbd0* out, const Vector3T_s0049_fbd0* a, const float* s);      // a * s
float VectorLength(const Vector3T_s0049_fbd0* v);                       // 0x40ae50
void Vector3_Normalize(Vector3T_s0049_fbd0* out, const Vector3T_s0049_fbd0* in);   // 0x436ce0
void FUN_49efc0(cSPEditorBlock_s0049_fbd0*, cSPVector3_s0049_fbd0, cSPVector3_s0049_fbd0, cSPMatrix3_s0049_fbd0, cSPMatrix3_s0049_fbd0, LimbVec<cSPEditorBlock_s0049_fbd0*>*);
void FUN_49efc0(cSPEditorBlock_s0049_fbd0*, Vector3T_s0049_fbd0, Vector3T_s0049_fbd0, Mat3Id, Matrix33T_s0049_fbd0, LimbVec<cSPEditorBlock_s0049_fbd0*>*);
bool FUN_49dd20(cSPEditorBlock_s0049_fbd0*, LimbVec<cSPEditorBlock_s0049_fbd0*>*, int);
void RepinBlockToTorso(cSPEditorBlock_s0049_fbd0* block, cSPVector3_s0049_fbd0 t, cSPMatrix3_s0049_fbd0 r, bool flag);
void* FUN_4a3dc0(cSPEditorBlock_s0049_fbd0*, void*, cSPVector3_s0049_fbd0, cSPVector3_s0049_fbd0, Vector3T_s0049_fbd0*);
void FUN_4a1070(cSPEditorBlock_s0049_fbd0*);
void FUN_4a29a0(cSPEditorBlock_s0049_fbd0*, void*, void*);
extern PodVec g_vec015d64d8;         // 0x15d64d8
void GetAllLimbs(cSPEditorBlock_s0049_fbd0* block, LimbVec<cSPEditorBlock_s0049_fbd0*>* out, bool unique);
    void Vector3_Normalize(...); // 0x00436ce0
// ---- items of slice s0049fbd0 end

// ---- items of slice s004a1a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kSnapScale;                   // 0x013ef578 (1.3f)
extern const float kDegenerateEps;            // 0x013ef4c4 (1/65536)
struct Vector3T_s004a_1a70 {
    float x, y, z;
    Vector3T_s004a_1a70() {}
    Vector3T_s004a_1a70(const Vector3T_s004a_1a70& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3_s004a_1a70 : Vector3T_s004a_1a70 {
    cSPVector3_s004a_1a70() {}
    cSPVector3_s004a_1a70(const Vector3T_s004a_1a70& v) : Vector3T_s004a_1a70(v) {}
};
template<class T> struct AutoRefCount_s004a_1a70 {
    T* mpObject;
    AutoRefCount_s004a_1a70(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004a_1a70() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct rwVec3 {
    float x, y, z;
    rwVec3() {}
    rwVec3(const rwVec3& v);                      // 0x004098a0
    rwVec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct rwMat3 {                                   // 3 rows of rwVec3
    rwVec3 r[3];
    rwMat3();                                     // 0x00402ab0
    rwMat3(const rwMat3& m);                      // 0x00449cc0
    rwVec3& operator[](int i) { return r[i]; }
};
struct BBox { rwVec3 mn, mx; };
struct Mat9 { float f[9]; };
struct Bitset60 {
    uint32_t w[2];
    bool test(uint32_t i) const
    {
        if (i < 60) {
            uint32_t word = w[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
class cSPEditorBlock_s004a_1a70;
typedef AutoRefCount_s004a_1a70<cSPEditorBlock_s004a_1a70> BlockRef_s004a_1a70;
struct Alloc_s004a_1a70 {
    Alloc_s004a_1a70() {}
    Alloc_s004a_1a70(const Alloc_s004a_1a70& o);                              // 0x00429360
};
struct BlockVec_s004a_1a70 {
    BlockRef_s004a_1a70* mpBegin;
    BlockRef_s004a_1a70* mpEnd;
    BlockRef_s004a_1a70* mpCapEnd;
    Alloc_s004a_1a70 mAlloc;
    BlockVec_s004a_1a70(const Alloc_s004a_1a70& a);                          // 0x00540470 (out-of-line ctor)
    BlockVec_s004a_1a70() : mpBegin(0), mpEnd(0), mpCapEnd(0), mAlloc(Alloc_s004a_1a70()) {}
    ~BlockVec_s004a_1a70();                                       // 0x00453eb0
    void push_back(const BlockRef_s004a_1a70& r);                 // 0x004541f0
    void DoDestroy(BlockRef_s004a_1a70* first, BlockRef_s004a_1a70* last);   // 0x00454280
    BlockRef_s004a_1a70& operator[](int i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cSPEditorModel_s004a_1a70;
struct cSPEditorBlock_s004a_1a70 {
    virtual void _v0();
    virtual void AddRef();                       // +4
    virtual void Release();                      // +8
    char pad0[0x28 - 4];
    cSPEditorModel_s004a_1a70* mpModel;                     // +0x28
    char pad1[0x48 - 0x2c];
    cSPVector3_s004a_1a70 mPosition;                        // +0x48
    char pad2[0x60 - 0x54];
    rwMat3 mOrientation;                         // +0x60
    char pad3[0xa8 - 0x84];
    float mBaseOrientation[9];                   // +0xa8
    char pad4[0x144 - 0xcc];
    cSPVector3_s004a_1a70 mField144;                        // +0x144
    char pad5[0x33c - 0x150];
    AutoRefCount_s004a_1a70<cSPEditorBlock_s004a_1a70> mParent;        // +0x33c
    char pad6[0x3e0 - 0x340];
    AutoRefCount_s004a_1a70<cSPEditorBlock_s004a_1a70> mPinTarget;     // +0x3e0
    char pad7[0xdc8 - 0x3e4];
    Bitset60 mFlags;                             // +0xdc8
    cSPEditorBlock_s004a_1a70* GetParent() const { return mParent; }
    cSPEditorModel_s004a_1a70* GetModel() const { return mpModel; }
    bool GetBooleanAttribute(uint32_t id) const { return mFlags.test(id); }
    void SetBooleanAttribute(int id, bool v);    // 0x435a10
    void FUN_4a1d60(const cSPVector3_s004a_1a70* p);        // @ 0x4a1d60
    void FUN_44ba20(int a, int b);               // 0x44ba20
    void FUN_44bcf0(int a, int b);               // 0x44bcf0
    bool FUN_44c030();                           // 0x44c030
    void FUN_44c0e0(int* a, int* b, int* c);     // 0x44c0e0 (picks an axis)
    BBox* GetBBox(BBox* out, int a, int b, int c);   // 0x44ae00
    void FUN_438a40(cSPEditorBlock_s004a_1a70* o);          // 0x438a40
    void FUN_438700(cSPEditorBlock_s004a_1a70* o);          // 0x438700
    void* GetA();                                // 0x4511f0
    void SetRef(void* r);                        // 0x451280
};
struct cSPEditorModel_s004a_1a70 {
    cSPEditorBlock_s004a_1a70* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
};
struct IMessageManager { void Post(uint32_t id, int a, void* data, int b); };   // 0x45ae40
struct IMessageServer_s004a_1a70 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                        virtual void Send(uint32_t id, int a, int b); };      // +0x14
void* FUN_00401060();                                               // editor context
IMessageManager* MessageManager_s004a_1a70();                                  // 0x401050
IMessageServer_s004a_1a70* MessageServer_s004a_1a70();                                    // 0x67dcc0
void BuildPileList(cSPEditorBlock_s004a_1a70* b, BlockVec_s004a_1a70* v, int flag);       // 0x48c790
void SetSymmetricBlocksUIState(cSPEditorBlock_s004a_1a70* b, int a, int c);    // 0x4a7f30
void FUN_4a6d20(cSPEditorBlock_s004a_1a70* b, int a, int c, int d, int e, int f, int g, int h);  // 0x4a6d20
bool FUN_4a1e10(cSPEditorBlock_s004a_1a70* block);          // defined below
void FUN_43f050(BBox* acc, BBox* other);        // 0x43f050 (merge)
rwVec3* Mat3MulVec(rwVec3* out, rwVec3* v, rwMat3* m);   // 0x41daf0 (_Unchecked_idl0)
extern const cSPVector3_s004a_1a70 kSnapZero;               // 0x015d64d8
extern rwVec3 kUpAxis;                        // 0x015d6370
extern rwVec3 kBlendAxis;                     // 0x015d6324
rwVec3* Vec3Normalize(rwVec3* out, const rwVec3* in);              // 0x436ce0
rwVec3 Vec3Normalized(const rwVec3& in);                           // 0x436ce0 (by-value form)
rwVec3* Vec3Negate(rwVec3* out, const rwVec3* in);                 // 0x422020
rwVec3* Vec3Cross(rwVec3* out, const rwVec3* a, const rwVec3* b);  // 0x454c00
rwVec3* Vec3Lerp(rwVec3* out, const rwVec3* a, const rwVec3* b, float t);   // 0x413cc0
float Vec3Length(const rwVec3* v);                                 // 0x4885d0
// ---- items of slice s004a1a70 end



// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool FUN_4a2560(cSPEditorModel_s004a_1a70* model);  // 0x004a2560 (stays in the slice: not this object's)
void FUN_4a1a70(void* unused, cSPEditorBlock_s004a_1a70* block);  // 0x004a1a70 (stays in the slice: not this object's)
rwVec3* FUN_4a2180(rwVec3* ret, cSPEditorBlock_s004a_1a70* a, cSPEditorBlock_s004a_1a70* b);  // 0x004a2180 (stays in the slice: not this object's)

// ---- items of slice s004a3dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s004a_3dc0 {
    float x, y, z;
    Vec3_s004a_3dc0() {}
    Vec3_s004a_3dc0(const Vec3_s004a_3dc0& o) : x(o.x), y(o.y), z(o.z) {}
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Plane_s004a_3dc0 { float a, b, c, d; Plane_s004a_3dc0() {} Plane_s004a_3dc0(float x, float y, float z, float w); };
struct Bits64 {
    uint32_t w[2];
    Bits64() { w[0] = 0; w[1] = 0; if (0) w[1] &= 0; }
    __forceinline void set(uint32_t pos, bool v)
    {
        if (pos < 0x40) {
            if (v) { uint32_t* p = &w[pos >> 5]; *p = (1u << (pos % 32)) | *p; }
            else   { uint32_t* p = &w[pos >> 5]; *p = ~(1u << (pos % 32)) & *p; }
        }
    }
};
struct Bits60 {
    uint32_t w[2];
    __forceinline bool test(uint32_t pos) const
    {
        if (pos < 0x3c) { uint32_t word = w[pos >> 5]; return (word & (1u << (pos % 32))) != 0; }
        return false;
    }
};
Vec3_s004a_3dc0* __cdecl Vector3_Normalize(Vec3_s004a_3dc0* out, const Vec3_s004a_3dc0* in);          // @ 0x436ce0
float __cdecl Dot3(const Vec3_s004a_3dc0* a, const Vec3_s004a_3dc0* b);                    // @ 0x455cc0
bool  __cdecl IntersectRayPlane(const Vec3_s004a_3dc0* o, const Vec3_s004a_3dc0* d, const Plane_s004a_3dc0* p, float* t); // @ 0x44e640
Vec3_s004a_3dc0* __cdecl Vector3_Scale(Vec3_s004a_3dc0* out, const float* s, const Vec3_s004a_3dc0* v); // @ 0x41de40
Vec3_s004a_3dc0* __cdecl FUN_0041dc10(Vec3_s004a_3dc0* out, const Vec3_s004a_3dc0* a, const Vec3_s004a_3dc0* b); // @ 0x41dc10 (a + b)
Vec3_s004a_3dc0* __cdecl FUN_0041db10(Vec3_s004a_3dc0* out, const Vec3_s004a_3dc0* a, const Vec3_s004a_3dc0* b); // @ 0x41db10 (a - b)
float __cdecl VectorLength(const Vec3_s004a_3dc0* v);                           // @ 0x40ae50
bool __fastcall FUN_0044c030(void* block);                           // @ 0x44c030
struct cMWModel_s004a_3dc0 {
    char pad0[0xc];
    Vec3_s004a_3dc0 mPos;                      // +0xc
    char pad18[0x40 - 0x18];
    int mRefCount;                  // +0x40
    void AddRef() { mRefCount = mRefCount + 1; }
    Vec3_s004a_3dc0* GetPos() { return &mPos; }
};
void __fastcall CountedRelease(void* p);                             // @ 0x40f360
struct RefPtr {
    cMWModel_s004a_3dc0* p;
    RefPtr(cMWModel_s004a_3dc0* q) : p(q) { if (p) p->AddRef(); }
    ~RefPtr() { if (p) CountedRelease(p); }
    cMWModel_s004a_3dc0* get() const { return p; }
};
struct cSPEditorBlock_s004a_3dc0;
struct BlockVec_s004a_3dc0 { cSPEditorBlock_s004a_3dc0** mpBegin; cSPEditorBlock_s004a_3dc0** mpEnd; cSPEditorBlock_s004a_3dc0*& operator[](int i) { cSPEditorBlock_s004a_3dc0** p = mpBegin + i; return *p; } };
struct cSPEditorModel_s004a_3dc0 {
    cSPEditorBlock_s004a_3dc0* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
    float GetScale();                            // @ 0x4adaa0
    bool  FUN_4adc40();                          // @ 0x4adc40
};
struct cSPEditorBlock_s004a_3dc0 {
    virtual void _v0();
    char pad04[0x28 - 4];
    cSPEditorModel_s004a_3dc0* mEditorModel;                // +0x28
    char pad2c[0x48 - 0x2c];
    Vec3_s004a_3dc0 mPos48;                                 // +0x48
    char pad54[0x33c - 0x54];
    cSPEditorBlock_s004a_3dc0* mField33c;                   // +0x33c
    BlockVec_s004a_3dc0 mChildren;                          // +0x340
    char pad348[0x3e0 - 0x348];
    cSPEditorBlock_s004a_3dc0* mParent;                     // +0x3e0
    char pad3e4[0x3f0 - 0x3e4];
    cMWModel_s004a_3dc0* mModel;                            // +0x3f0
    cMWModel_s004a_3dc0* GetModel() { return mModel; }
    char pad3f4[0xdc8 - 0x3f4];
    Bits60 mFlags;                               // +0xdc8
    cSPEditorBlock_s004a_3dc0* GetField33c() { return mField33c; }
    void SetNodeStateChecked(int state, bool b); // @ 0x437a60
    void ClearNodeState();                       // @ 0x437890
};
struct cSPEditorPickInfo {
    Bits64 m0;
    Bits64 m8;
    int m10;
    bool m14;
    bool m15;
    cSPEditorPickInfo();                         // @ 0x4a4c70
};
struct BitsBase;
struct PickModel { char pad[0x44]; uint32_t mBits[2]; };
struct PickBlock {
    char pad[0x10];
    PickModel* mModel;
    PickModel* GetModel() { return mModel; }
    char pad14[4];
    struct IModelWorld* mWorld;   // +0x18
    struct IModelWorld* GetWorld() { return mWorld; }
    void SetNodeStateChecked(int state, bool checked);   // @ 0x437a60
    void ClearNodeState();                                // @ 0x437890
};
struct PickVec { PickBlock** mpBegin; PickBlock** mpEnd; PickBlock*& operator[](int i) { PickBlock** p = mpBegin + i; return *p; } };
struct IModelManager { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual uint32_t GetTypeBit(uint32_t key, int zero); };   // slot 0x28
struct IModelWorld { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual struct PickHit* Raycast(const Vec3_s004a_3dc0* o, const Vec3_s004a_3dc0* e, int zero, int a, int b, cSPEditorPickInfo* filter, char* extra, int c); }; // slot 0x24
struct PickHit { char pad[0x5d]; unsigned char mKind; char pad2[6]; void* mPtr64; };   // +0x5d kind, +0x64 ptr
struct BitsBase { uint32_t w[2]; __forceinline void set(uint32_t pos, bool v) {
    if (pos < 0x40) { if (v) { uint32_t* p = &w[pos >> 5]; *p = (1u << (pos % 32)) | *p; }
                      else   { uint32_t* p = &w[pos >> 5]; *p = ~(1u << (pos % 32)) & *p; } } } };
IModelManager* __cdecl ModelManager();                                   // @ 0x67dd80
void* __cdecl InterfaceCast(void* p);                                    // @ 0x4aa2a0
bool __fastcall GetResourceTypeFromModelType_(PickVec* v);               // @ 0x526430
// ---- items of slice s004a3dc0 end

// ---- items of slice s004a9920 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s004a_9920 {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T_s004a_9920() {}
    Vector3T_s004a_9920(const Vector3T_s004a_9920& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T_s004a_9920 {                              // rw::math::fpu::Matrix33Template<float,0>
    Matrix33T_s004a_9920() {}
    Matrix33T_s004a_9920(const Matrix33T_s004a_9920& m) { xAxis = Vector3T_s004a_9920(m.xAxis); yAxis = Vector3T_s004a_9920(m.yAxis); zAxis = Vector3T_s004a_9920(m.zAxis); }   // emitted out of line @ 0x41cb40
    Vector3T_s004a_9920 xAxis, yAxis, zAxis;
};
struct cSPMatrix3_s004a_9920 : Matrix33T_s004a_9920 {
    static const cSPMatrix3_s004a_9920 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3_s004a_9920 : Vector3T_s004a_9920 {
    cSPVector3_s004a_9920() {}
    cSPVector3_s004a_9920(const Vector3T_s004a_9920& v) : Vector3T_s004a_9920(v) {}
    cSPVector3_s004a_9920& operator=(const Vector3T_s004a_9920& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T_s004a_9920 operator*(const Vector3T_s004a_9920& v, const Matrix33T_s004a_9920& m);   // @ 0x41daf0
Vector3T_s004a_9920 operator-(const Vector3T_s004a_9920& v);                       // @ 0x422020
Vector3T_s004a_9920 operator+(const Vector3T_s004a_9920& a, const Vector3T_s004a_9920& b);    // @ 0x41dc10
struct cSPTransform_s004a_9920 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3_s004a_9920 mTranslation;
    float mScale;
    cSPMatrix3_s004a_9920 mRotation;
    cSPTransform_s004a_9920();                                          // @ 0x409930
    const cSPMatrix3_s004a_9920& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3_s004a_9920& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void PreRotate(const Vector3T_s004a_9920& axis, float angle);       // @ 0x6baba0
};
template<class T> struct AutoRefCount_s004a_9920 {
    T* mpObject;
    ~AutoRefCount_s004a_9920() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> struct CtorSlots_s004a_9920 { static void Reserve() {} static void ReserveClear() {} };
template<class T> struct AutoRefCount_s004a_9920;
template<class T> struct CtorSlots_s004a_9920<AutoRefCount_s004a_9920<T> > { static void Reserve() { ScratchSlots<1>(); } static void ReserveClear() { ScratchSlots<3>(); } };
template<class T> struct VectorBase_s004a_9920 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    VectorBase_s004a_9920() : mpBegin(0), mpEnd(0), mpCapacity(0) { CtorSlots_s004a_9920<T>::Reserve(); }
    ~VectorBase_s004a_9920();                                           // @ 0x425990 (shared)
};
template<class T> struct vector_s004a_9920 : VectorBase_s004a_9920<T> {
    vector_s004a_9920() {}
    ~vector_s004a_9920() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* erase(T* first, T* last);                             // @ 0x4769b0 / 0x454280
    void clear() { erase(mpBegin, mpEnd); ScratchSlots<4>(); CtorSlots_s004a_9920<T>::ReserveClear(); }
    bool empty() const;                                      // @ 0x526430
    void DoDestroyValues(T* first, T* last) { for (; first < last; ++first) first->~T(); }
};
template<int N> struct bitset_s004a_9920 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
namespace SP {
struct cSPEditorBlock_s004a_9920 {
    virtual void _v0();
    virtual int Release();
    char pad0[0x340 - 4];
    vector_s004a_9920<AutoRefCount_s004a_9920<cSPEditorBlock_s004a_9920> > mSymmetricBlocks;   // +0x340
    char pad1[0xdc8 - 0x354];
    bitset_s004a_9920<60> mFlags;                          // +0xdc8
};
}
namespace SP {
namespace EditorUtils {
bool IsSkinnedPart(cSPEditorBlock_s004a_9920* block);                   // @ 0x4a96d0
}
}
namespace SP {
struct ResourceKey_s004a_9920 { uint32_t mGroupID, mTypeID, mInstanceID; };
}
namespace SP {
struct DefaultRefCounted { int Release(); };                  // @ 0x453540
}
namespace SP {
struct cRefCountedResource { void* vftable; DefaultRefCounted mRef; };
}
namespace SP {
struct cVirtualRefCounted { virtual int AddRef(); virtual int Release(); };
}
namespace SP {
template<class T> struct AutoRefCountR {        // AutoRefCount over DefaultRefCounted (+4)
    T* mpObject;
    ~AutoRefCountR();
};
}
namespace SP {
template<class T> struct AutoRefCountV {
    T* mpObject;
    ~AutoRefCountV();
};
}
namespace SP {
struct Quaternion { float x, y, z, w; };
}
namespace SP {
inline void Set(Vector3T_s004a_9920& v, float x, float y, float z) { v.x = x; v.y = y; v.z = z; }
}
namespace SP {
void* EASTLAlloc(void* allocator, unsigned int n, unsigned int align, unsigned int flags);   // @ 0x42dee0
}
namespace SP {
struct WeightedPoint { float mWeight; cSPVector3_s004a_9920 mPoint; };                 // 0x10
}
namespace SP {
struct OrientedPoint {                                                        // 0x34
    cSPMatrix3_s004a_9920 mOrientation; cSPVector3_s004a_9920 mPosition; float mScale;
    OrientedPoint(const OrientedPoint& x);
};
}
namespace SP {
struct cSPTransform_s004a_9920 {                           // 0x38; implicit copy ctor emitted out of line @ 0x40ce80
    uint16_t mFlags; uint16_t mModificationCount; cSPVector3_s004a_9920 mTranslation; float mScale; cSPMatrix3_s004a_9920 mRotation;
};
}
namespace SP {
struct KeyedPair { uint32_t first; cSPTransform_s004a_9920 second; };                    // 0x3c
}
namespace SP {
template<class T> struct evector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    evector(uint32_t n, const uint32_t& allocator);
    T* DoAllocate(uint32_t n) { return n ? (T*)EASTLAlloc(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity) ::new(mpEnd++) T(value);
        else DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(T* position, const T& value);
};
}
namespace SP {
template<class T> struct DequeIterator {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;
    DequeIterator(const DequeIterator& x);                   // @ 0x420050
    DequeIterator& operator++();                             // @ 0x4ab210
    bool operator!=(const DequeIterator& x) const { return mpCurrent != x.mpCurrent; }
    int operator-(const DequeIterator& x) const {
        return (64 * ((mpCurrentArrayPtr - x.mpCurrentArrayPtr) - 1)) + (mpCurrent - mpBegin) + (x.mpEnd - x.mpCurrent);
    }
};
}
namespace SP {
template<class T> struct deque {
    T** mpPtrArray;
    uint32_t mnPtrArraySize;
    DequeIterator<T> mItBegin;
    DequeIterator<T> mItEnd;
    ~deque();
    void FreeBase();                                         // @ 0x501ef0
    uint32_t size() const { return (uint32_t)(mItEnd - mItBegin); }
    uint32_t GetSize() const;
    T& operator[](uint32_t n);
    void push_front(const T& value);
    void DoPushFront(const T& value);                        // @ 0x4ab130
};
}
namespace SP {
struct cSPEditorPart;
}
// ---- items of slice s004a9920 end



// ---- items of slice s0048d010 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(fabs_s0048_d010)
struct Vector3T_s0048_d010 {
    float x, y, z;
    Vector3T_s0048_d010() {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3_s0048_d010 : Vector3T_s0048_d010 {
    cSPVector3_s0048_d010() {}
    __forceinline cSPVector3_s0048_d010(const Vector3T_s0048_d010& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3_s0048_d010& operator=(const Vector3T_s0048_d010& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct hkMemory {
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void _v3();
    virtual void _v4();
    virtual void* Free(void* p, int align, int size);
};
extern hkMemory* g_hkMemory;                    // @ 0x16e4178
struct HkObj {
    char data0[4];
    float mField4;                              // +0x04
    char data1[0x20 - 8];
    float mArray[4];                            // +0x20
    int mField30;                               // +0x30
    char rest[0x40 - 0x34];
    void* F_48db10(unsigned flags);             // @ 0x48db10
    void  F_48db60();                           // @ 0x48db60
    void* F_48dbb0(unsigned flags);             // @ 0x48dbb0
    void* F_48dc50(HkObj* src);                 // @ 0x48dc50
};
extern "C" double __cdecl fabs_s0048_d010(double);
struct hkBool_s0048_d010 {
    char m_bool;
    hkBool_s0048_d010(bool b) { m_bool = (char)b; }
    operator bool() const { return m_bool != 0; }
};
struct __declspec(align(16)) hkVector4_s0048_d010 {
    hkReal x, y, z, w;
    __forceinline hkVector4_s0048_d010() {}
    __forceinline hkVector4_s0048_d010(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
    __forceinline hkVector4_s0048_d010(const hkVector4_s0048_d010& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    __forceinline void operator=(const hkVector4_s0048_d010& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    __forceinline hkReal& operator()(int i) { return (&x)[i]; }
    __forceinline const hkReal& operator()(int i) const { return (&x)[i]; }
    __forceinline void setInterpolate4(const hkVector4_s0048_d010& v0, const hkVector4_s0048_d010& v1, hkReal t)
    {
        const hkReal s = 1.0f - t;
        (*this)(0) = s * v0(0) + t * v1(0);
        (*this)(1) = s * v0(1) + t * v1(1);
        (*this)(2) = s * v0(2) + t * v1(2);
        (*this)(3) = s * v0(3) + t * v1(3);
    }
};
struct hkMatrix3_s0048_d010 {
    hkVector4_s0048_d010 m_col0, m_col1, m_col2;
    __forceinline hkMatrix3_s0048_d010() {}
    hkMatrix3_s0048_d010(const hkMatrix3_s0048_d010& m);              // @ 0x48daf0
    void operator=(const hkMatrix3_s0048_d010& m);         // @ 0x44a8c0
};
struct hkRotation_s0048_d010 : hkMatrix3_s0048_d010 {
    __forceinline hkRotation_s0048_d010() {}
    __forceinline hkRotation_s0048_d010(const hkRotation_s0048_d010& r) : hkMatrix3_s0048_d010(r) {}
};
struct hkTransform_s0048_d010 {
    hkRotation_s0048_d010 m_rotation;
    hkVector4_s0048_d010 m_translation;
    __forceinline hkTransform_s0048_d010() {}
    __forceinline hkTransform_s0048_d010(const hkTransform_s0048_d010& t) : m_rotation(t.m_rotation), m_translation(t.m_translation) {}
    __forceinline void operator=(const hkTransform_s0048_d010& t) { m_rotation = t.m_rotation; m_translation = t.m_translation; }
    void setRotation(const hkRotation_s0048_d010& r) { m_rotation = r; }
    static hkTransform_s0048_d010 s_identity;              // @ 0x15b9b20
    static const hkTransform_s0048_d010& getIdentity() { return s_identity; }
};
struct hkAabb_s0048_d010 {
    hkVector4_s0048_d010 m_min;
    hkVector4_s0048_d010 m_max;
};
struct hkShape_s0048_d010 {
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void getAabb(const hkTransform_s0048_d010& localToWorld, hkReal tolerance, hkAabb_s0048_d010& out) const;   // +0xc
};
struct hkCdBody_s0048_d010 {
    const hkShape_s0048_d010* m_shape;                     // +0x00
    unsigned int m_shapeKey;
    const void* m_motion;
    const hkCdBody_s0048_d010* m_parent;
    const hkShape_s0048_d010* getShape() const { return m_shape; }
};
struct hkCollidable_s0048_d010 : hkCdBody_s0048_d010 {
    int m_ownerOffset;                          // +0x10
    unsigned int m_bpId;
    char m_bpType, m_bpOwnerOffset;
    unsigned short m_objectQualityType;
    unsigned int m_collisionFilterInfo;         // +0x1c
    hkReal m_allowedPenetrationDepth;
    void* getOwner() const { return (char*)this + m_ownerOffset; }
};
struct hkMotion_s0048_d010 {
    char pad[0x10];
    hkTransform_s0048_d010 m_transform;                    // +0x10 (motion state)
    const hkTransform_s0048_d010& getTransform() const { return m_transform; }
    const hkVector4_s0048_d010& getPosition() const { return m_transform.m_translation; }
};
struct hkRigidBody_s0048_d010 {
    char pad00[0x1c];
    hkCollidable_s0048_d010 m_collidable;                  // +0x1c
    char pad40[0x58 - 0x1c - sizeof(hkCollidable_s0048_d010)];
    hkMotion_s0048_d010* m_motion;                         // +0x58
    const hkCollidable_s0048_d010* getCollidable() const { return &m_collidable; }
    hkMotion_s0048_d010* getRigidMotion() const { return m_motion; }
    void setPosition(const hkVector4_s0048_d010& p);       // @ 0x1087820
    void setTransform(const hkTransform_s0048_d010& t);    // @ 0x1087890
};
inline hkRigidBody_s0048_d010* hkGetRigidBody_s0048_d010(const hkCollidable_s0048_d010* c)
{
    hkRigidBody_s0048_d010* body = (hkRigidBody_s0048_d010*)c->getOwner();
    return body;
}
struct hkContactPoint_s0048_d010 {
    hkVector4_s0048_d010 m_position;
    hkVector4_s0048_d010 m_separatingNormal;
    const hkVector4_s0048_d010& getPosition() const { return m_position; }
    hkReal getDistance() const { return m_separatingNormal(3); }
};
struct hkRootCdPoint_s0048_d010 {
    hkContactPoint_s0048_d010 m_contact;
    const hkCollidable_s0048_d010* m_rootCollidableA;
    unsigned int m_shapeKeyA;
    const hkCollidable_s0048_d010* m_rootCollidableB;
    unsigned int m_shapeKeyB;
};
extern hkReal HK_REAL_MAX;                      // @ 0x13ef4f8
struct hkCdPointCollector_s0048_d010 {
    hkReal m_earlyOutDistance;
    hkCdPointCollector_s0048_d010() { m_earlyOutDistance = HK_REAL_MAX; }
    virtual ~hkCdPointCollector_s0048_d010() {}            // vtable 0x13ef534
    virtual void addCdPoint(const void* event) = 0;
    virtual void reset();
};
struct hkClosestCdPointCollector_s0048_d010 : hkCdPointCollector_s0048_d010 {
    hkRootCdPoint_s0048_d010 m_hitPoint;                   // +0x10
    hkClosestCdPointCollector_s0048_d010() { reset(); }
    virtual ~hkClosestCdPointCollector_s0048_d010() {}     // vtable 0x13ef52c
    virtual void addCdPoint(const void* event);
    virtual void reset();                       // @ 0x48db60
    hkBool_s0048_d010 hasHit() const { return m_hitPoint.m_rootCollidableA != 0; }
    const hkRootCdPoint_s0048_d010& getHit() const { return m_hitPoint; }
};
struct hkLinearCastInput_s0048_d010 {
    hkVector4_s0048_d010 m_to;
    hkReal m_maxExtraPenetration;
    hkReal m_startPointTolerance;
    hkLinearCastInput_s0048_d010() { m_maxExtraPenetration = HK_REAL_EPSILON; m_startPointTolerance = HK_REAL_EPSILON; }
};
struct hkWorld_s0048_d010 {
    void linearCast(const hkCollidable_s0048_d010* collA, const hkLinearCastInput_s0048_d010& input,
                    hkCdPointCollector_s0048_d010& castCollector, hkCdPointCollector_s0048_d010* startCollector);   // @ 0x1082b90
};
namespace hkMath {
 inline hkReal fabs_s0048_d010(hkReal r) { return ::fabsf(r); } 
}
struct Matrix3_s0048_d010 { float m[9]; };
struct cSPEditorPhysicsWorld_s0048_d010 { hkWorld_s0048_d010* World(); };                // World @ 0x4b91c0
struct cSPEditorModel_s0048_d010 {
    cSPEditorPhysicsWorld_s0048_d010* GetPhysicsWorld();   // @ 0x4ad450
    void NumberBlocks();                        // @ 0x4ad4e0
};
struct cSPEditorBlock_s0048_d010;
template<class T> struct AutoRefCount_s0048_d010 {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cSPEditorBlock_s0048_d010 {
    char pad00[0x28];
    cSPEditorModel_s0048_d010* mEditorModel;               // +0x28
    char pad2c[0x18c - 0x2c];
    hkRigidBody_s0048_d010* mpRigidBody;                   // +0x18c
    char pad190[0x33c - 0x190];
    AutoRefCount_s0048_d010<cSPEditorBlock_s0048_d010> mSymmetricBlock;   // +0x33c
    void SetCollisionFilterInfo(int info);      // @ 0x451e50
};
struct BlockList;
Vector3T_s0048_d010 operator*(const float& s, const Vector3T_s0048_d010& v);              // @ 0x41de40
Vector3T_s0048_d010 operator+(const Vector3T_s0048_d010& a, const Vector3T_s0048_d010& b);           // @ 0x41dc10
void PrepareBlockForStacking(cSPEditorBlock_s0048_d010* block, BlockList& piles, int a, int b, int c);   // @ 0x4a6690
void ToHkRotation(const Matrix3_s0048_d010& m, hkRotation_s0048_d010& out);               // @ 0x4a8fc0
__forceinline hkVector4_s0048_d010 ToHkVector4_s0048_d010(const cSPVector3_s0048_d010& v)
{
    float x = v[0];
    float y = v[1];
    float z = v[2];
    return hkVector4_s0048_d010(x, y, z, 0.0f);
}
__forceinline cSPVector3_s0048_d010 ToSPVector3(const hkVector4_s0048_d010& v)
{
    float x = v(0);
    float y = v(1);
    float z = v(2);
    cSPVector3_s0048_d010 r;
    r.x = x; r.y = y; r.z = z;
    return r;
}
// ---- items of slice s0048d010 end

// ---- items of slice s0048dcd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec4T {
    float x, y, z, w;
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Vector3T_s0048_dcd0 {
    float x, y, z;
    Vector3T_s0048_dcd0() {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Vector3Val : Vector3T_s0048_dcd0 {
    Vector3Val() {}
    Vector3Val(const Vector3Val& v);                                    // @ 0x4098a0
};
struct cSPVector3_s0048_dcd0 : Vector3T_s0048_dcd0 {
    cSPVector3_s0048_dcd0() {}
    __forceinline cSPVector3_s0048_dcd0(const Vector3T_s0048_dcd0& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3_s0048_dcd0& operator=(const Vector3T_s0048_dcd0& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct hkBool_s0048_dcd0 {
    char m_bool;
    hkBool_s0048_dcd0(bool b) { m_bool = (char)b; }
    operator bool() const { return m_bool != 0; }
};
struct __declspec(align(16)) hkVector4_s0048_dcd0 {
    hkReal x, y, z, w;
    __forceinline hkVector4_s0048_dcd0() {}
    __forceinline hkVector4_s0048_dcd0(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
    __forceinline hkVector4_s0048_dcd0(const hkVector4_s0048_dcd0& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    __forceinline void operator=(const hkVector4_s0048_dcd0& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    __forceinline hkReal& operator()(int i) { return (&x)[i]; }
    __forceinline const hkReal& operator()(int i) const { return (&x)[i]; }
    __forceinline void setInterpolate4(const hkVector4_s0048_dcd0& v0, const hkVector4_s0048_dcd0& v1, hkReal t)
    {
        const hkReal s = 1.0f - t;
        (*this)(0) = s * v0(0) + t * v1(0);
        (*this)(1) = s * v0(1) + t * v1(1);
        (*this)(2) = s * v0(2) + t * v1(2);
        (*this)(3) = s * v0(3) + t * v1(3);
    }
};
struct hkMatrix3_s0048_dcd0 {
    hkVector4_s0048_dcd0 m_col0, m_col1, m_col2;
    __forceinline hkMatrix3_s0048_dcd0() {}
    hkMatrix3_s0048_dcd0(const hkMatrix3_s0048_dcd0& m);              // @ 0x48daf0
    void operator=(const hkMatrix3_s0048_dcd0& m);         // @ 0x44a8c0
};
struct hkRotation_s0048_dcd0 : hkMatrix3_s0048_dcd0 {
    __forceinline hkRotation_s0048_dcd0() {}
    __forceinline hkRotation_s0048_dcd0(const hkRotation_s0048_dcd0& r) : hkMatrix3_s0048_dcd0(r) {}
    hkRotation_s0048_dcd0& operator=(const hkRotation_s0048_dcd0& r);     // @ 0x48daf0
};
struct hkTransform_s0048_dcd0 {
    hkRotation_s0048_dcd0 m_rotation;
    hkVector4_s0048_dcd0 m_translation;
    __forceinline hkTransform_s0048_dcd0() {}
    __forceinline hkTransform_s0048_dcd0(const hkTransform_s0048_dcd0& t) : m_rotation(t.m_rotation), m_translation(t.m_translation) {}
    __forceinline void operator=(const hkTransform_s0048_dcd0& t) { m_rotation = t.m_rotation; m_translation = t.m_translation; }
    void setRotation(const hkRotation_s0048_dcd0& r) { m_rotation = r; }
    static hkTransform_s0048_dcd0 s_identity;              // @ 0x15b9b20
    static const hkTransform_s0048_dcd0& getIdentity() { return s_identity; }
};
struct hkAabb_s0048_dcd0 {
    hkVector4_s0048_dcd0 m_min;
    hkVector4_s0048_dcd0 m_max;
};
struct hkShape_s0048_dcd0 {
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void getAabb(const hkTransform_s0048_dcd0& localToWorld, hkReal tolerance, hkAabb_s0048_dcd0& out) const;   // +0xc
};
struct hkCdBody_s0048_dcd0 {
    const hkShape_s0048_dcd0* m_shape;                     // +0x00
    unsigned int m_shapeKey;
    const void* m_motion;
    const hkCdBody_s0048_dcd0* m_parent;
    const hkShape_s0048_dcd0* getShape() const { return m_shape; }
};
struct hkCollidable_s0048_dcd0 : hkCdBody_s0048_dcd0 {
    int m_ownerOffset;                          // +0x10
    unsigned int m_bpId;
    char m_bpType, m_bpOwnerOffset;
    unsigned short m_objectQualityType;
    unsigned int m_collisionFilterInfo;         // +0x1c
    hkReal m_allowedPenetrationDepth;
    void* getOwner() const { return (char*)this + m_ownerOffset; }
};
struct hkQuaternion_s0048_dcd0 {
    hkReal x, y, z, w;
    __forceinline hkQuaternion_s0048_dcd0() {}
    __forceinline hkQuaternion_s0048_dcd0(const hkQuaternion_s0048_dcd0& q) { x = q.x; y = q.y; z = q.z; w = q.w; }
};
struct hkMotion_s0048_dcd0 {
    char pad[0x10];
    hkTransform_s0048_dcd0 m_transform;                    // +0x10 (motion state)
    const hkTransform_s0048_dcd0& getTransform() const { return m_transform; }
    const hkVector4_s0048_dcd0& getPosition() const { return m_transform.m_translation; }
    char pad50[0x80 - 0x50];
    hkQuaternion_s0048_dcd0 m_rotation;                    // +0x80
    const hkQuaternion_s0048_dcd0& getRotation() const { return m_rotation; }
};
struct hkRigidBody_s0048_dcd0 {
    char pad00[0x1c];
    hkCollidable_s0048_dcd0 m_collidable;                  // +0x1c
    char pad40[0x58 - 0x1c - sizeof(hkCollidable_s0048_dcd0)];
    hkMotion_s0048_dcd0* m_motion;                         // +0x58
    const hkCollidable_s0048_dcd0* getCollidable() const { return &m_collidable; }
    hkMotion_s0048_dcd0* getRigidMotion() const { return m_motion; }
    void setPosition(const hkVector4_s0048_dcd0& p);       // @ 0x1087820
    void setRotation(const hkQuaternion_s0048_dcd0& q);    // @ 0x1087840
    void setTransform(const hkTransform_s0048_dcd0& t);    // @ 0x1087890
};
inline hkRigidBody_s0048_dcd0* hkGetRigidBody_s0048_dcd0(const hkCollidable_s0048_dcd0* c)
{
    hkRigidBody_s0048_dcd0* body = (hkRigidBody_s0048_dcd0*)c->getOwner();
    return body;
}
struct hkContactPoint_s0048_dcd0 {
    hkVector4_s0048_dcd0 m_position;
    hkVector4_s0048_dcd0 m_separatingNormal;
    const hkVector4_s0048_dcd0& getPosition() const { return m_position; }
    hkReal getDistance() const { return m_separatingNormal(3); }
    void setDistance(hkReal d) { m_separatingNormal(3) = d; }
};
struct hkRootCdPoint_s0048_dcd0 {
    hkContactPoint_s0048_dcd0 m_contact;
    const hkCollidable_s0048_dcd0* m_rootCollidableA;
    unsigned int m_shapeKeyA;
    const hkCollidable_s0048_dcd0* m_rootCollidableB;
    unsigned int m_shapeKeyB;
};
struct hkCdPointCollector_s0048_dcd0 {
    hkReal m_earlyOutDistance;
    hkCdPointCollector_s0048_dcd0() { m_earlyOutDistance = HK_REAL_MAX; }
    virtual ~hkCdPointCollector_s0048_dcd0() {}            // vtable 0x13ef534
    virtual void addCdPoint(const void* event) = 0;
    virtual void reset();
};
struct hkClosestCdPointCollector_s0048_dcd0 : hkCdPointCollector_s0048_dcd0 {
    hkRootCdPoint_s0048_dcd0 m_hitPoint;                   // +0x10
    hkClosestCdPointCollector_s0048_dcd0() { reset(); }
    virtual ~hkClosestCdPointCollector_s0048_dcd0() {}     // vtable 0x13ef52c
    virtual void addCdPoint(const void* event);
    virtual void reset();                       // @ 0x48db60
    __forceinline void resetInline() {
        m_hitPoint.m_rootCollidableA = 0;
        m_hitPoint.m_contact.setDistance(HK_REAL_MAX);
        m_earlyOutDistance = HK_REAL_MAX;
    }
    hkBool_s0048_dcd0 hasHit() const { return m_hitPoint.m_rootCollidableA != 0; }
    const hkRootCdPoint_s0048_dcd0& getHit() const { return m_hitPoint; }
};
struct hkLinearCastInput_s0048_dcd0 {
    hkVector4_s0048_dcd0 m_to;
    hkReal m_maxExtraPenetration;
    hkReal m_startPointTolerance;
    hkLinearCastInput_s0048_dcd0() { m_maxExtraPenetration = HK_REAL_EPSILON; m_startPointTolerance = HK_REAL_EPSILON; }
};
struct hkWorld_s0048_dcd0 {
    void linearCast(const hkCollidable_s0048_dcd0* collA, const hkLinearCastInput_s0048_dcd0& input,
                    hkCdPointCollector_s0048_dcd0& castCollector, hkCdPointCollector_s0048_dcd0* startCollector);   // @ 0x1082b90
};
namespace hkMath {
 inline hkReal fabs(hkReal r) { return ::fabsf(r); } 
}
struct Matrix3_s0048_dcd0 { float m[9]; };
struct cSPEditorPhysicsWorld_s0048_dcd0 {
    hkWorld_s0048_dcd0* World();                           // @ 0x4b91c0
    void SetFloorFilter(int info);              // @ 0x4b9440
    void SetDefaultFloorFilter();               // @ 0x4b9470
    void UpdateCollisionFilters();              // @ 0x4b9420
    char pad0[0xc];
    hkRigidBody_s0048_dcd0* mGroundBody;                   // +0x0c
    hkRigidBody_s0048_dcd0* GetGroundBody() { return mGroundBody; }
};
struct cSPEditorModel_s0048_dcd0 {
    char pad0[0x30];
    cSPEditorPhysicsWorld_s0048_dcd0* GetPhysicsWorld();   // @ 0x4ad450
    void NumberBlocks();                        // @ 0x4ad4e0
    float GetMaxHeight();                       // @ 0x4adb40 (+0x44)
    float GetMinHeight();                       // @ 0x4adb00 (+0x40)
    float GetGridSize();                        // @ 0x4adaa0 (+0x38)
};
struct cSPEditorBlock_s0048_dcd0 {
    char pad00[0x28];
    cSPEditorModel_s0048_dcd0* mEditorModel;               // +0x28
    char pad2c[0x18c - 0x2c];
    hkRigidBody_s0048_dcd0* mpRigidBody;                   // +0x18c
    Matrix3_s0048_dcd0 GetNeutralOrientation(Vector3Val direction);    // @ 0x4494b0 (ret 0x10)
};
Vector3T_s0048_dcd0 operator*(const float& s, const Vector3T_s0048_dcd0& v);              // @ 0x41de40
Vector3T_s0048_dcd0 operator+(const Vector3T_s0048_dcd0& a, const Vector3T_s0048_dcd0& b);           // @ 0x41dc10
float VectorLength(const Vector3T_s0048_dcd0& v);                              // @ 0x40ae50
void PrepareBlockForStacking(cSPEditorBlock_s0048_dcd0* block, BlockList& piles, int a, int b, int c);   // @ 0x4a6690
void ToHkRotation(const Matrix3_s0048_dcd0& m, hkRotation_s0048_dcd0& out);               // @ 0x4a8fc0
__forceinline cSPVector3_s0048_dcd0 ToSPVector3_s0048_dcd0(const hkVector4_s0048_dcd0& v)
{
    float x = v(0);
    float y = v(1);
    float z = v(2);
    cSPVector3_s0048_dcd0 r;
    r.x = x; r.y = y; r.z = z;
    return r;
}
template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
// ---- items of slice s0048dcd0 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
float* F_48e510(float* out, Vec4T& src);   // defined at 0x0048e510, called earlier in the TU

// ---- items of slice s0048e590 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0048_e590 {
    float x, y, z;
    Vector3_s0048_e590() {}
    Vector3_s0048_e590(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3_s0048_e590(const Vector3_s0048_e590& o) : x(o.x), y(o.y), z(o.z) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct Vector3R : Vector3_s0048_e590 {};
struct RwVector3 {
    float x, y, z;
    RwVector3(const RwVector3& o);  // 0x004098a0
};
struct Matrix33 {
    float m[9];
};
struct Matrix3_s0048_e590 {
    Vector3_s0048_e590 m[3];
    Matrix3_s0048_e590() {}
    Matrix3_s0048_e590(const Matrix33& other);  // 0x0041cb40
};
Vector3R operator-(const Vector3_s0048_e590& a, const RwVector3& b);  // 0x0041db10
Vector3R operator-(const Vector3_s0048_e590& a, const Vector3_s0048_e590& b);    // 0x0041db10
Vector3R operator+(const Vector3_s0048_e590& a, const RwVector3& b); // 0x0041dc10
Vector3R operator*(const Vector3_s0048_e590& v, const Matrix3_s0048_e590& m);    // 0x0041daf0
Matrix3_s0048_e590 Transposed(const Matrix3_s0048_e590& m);                     // 0x0041ded0
float VectorLength(const Vector3_s0048_e590& v);                     // 0x0040ae50
extern const Matrix33 kIdentity33;  // 0x015d63a8
extern const RwVector3 kZero3;      // 0x015d64d8
inline float Abs_s0048_e590(float x)
{
    float r = (float)fabs((double)x);
    return r;
}
template <int N>
struct bitset_s0048_e590 {
    uint32_t mWord[(N + 31) / 32];
    __forceinline bool test(uint32_t n) const
    {
        if (n < N) {
            uint32_t word = mWord[n >> 5];
            return (word & (1u << (n % 32))) != 0;
        }
        return false;
    }
};
struct Candidate {
    float score;
    Vector3_s0048_e590 pos;
};
struct CandVec {
    Candidate* mpBegin;
    Candidate* mpEnd;
    Candidate* mpCapacity;

    CandVec(const AllocTag&);            // 0x00540470
    ~CandVec()
    {
        for (Candidate* p = mpBegin; p < mpEnd; ++p)
            p->~Candidate();
        DoFree();
    }
    void DoFree();                       // 0x00554b10
    bool empty() const;                  // 0x00526430
    void push_back(const Candidate& c);  // 0x004a9e40
};
struct EditorBlock;
struct BlockList_s0048_e590 {
    EditorBlock** mpBegin;
    EditorBlock** mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;  // 0x00526430
    EditorBlock** at(int i) { return mpBegin + i; }
};
struct Parent {
    uint32_t pad00[0x12];
    Vector3_s0048_e590 mOffset;  // +0x48
    uint32_t pad54[3];
    Matrix3_s0048_e590 mRotation;  // +0x60
};
struct Block_s0048_e590 {
    char pad00[0x28];
    struct SrcObj { float Get(); } *mpSource;  // +0x28 (thiscall getter, 0x004adaa0)
    char pad2c[0x48 - 0x2c];
    Vector3_s0048_e590 mPosition;                         // +0x48
    char pad54[0x33c - 0x54];
    Parent* mpParent;                          // +0x33c
    Parent* GetParent() { return mpParent; }
    char pad340[0xdc8 - 0x340];
    bitset_s0048_e590<60> mFlags;                         // +0xdc8
};
// ---- items of slice s0048e590 end

// ---- items of slice s0048ef30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl acos(double);
extern const float kFloatMax;                            // 0x13ef4c0
#pragma intrinsic(fabs, acos)
inline float Abs_s0048_ef30(float x) { return (float)fabs(x); }
struct Vector3_s0048_ef30 {
    float x, y, z;
    Vector3_s0048_ef30() {}
    Vector3_s0048_ef30(const Vector3_s0048_ef30& v);                           // 0x4098a0 (out of line)
    float& operator[](int i) { return (&x)[i]; }
};
struct Matrix3_s0048_ef30 {
    Vector3_s0048_ef30 xAxis, yAxis, zAxis;
    Matrix3_s0048_ef30() {}
    Matrix3_s0048_ef30(const Matrix3_s0048_ef30& m) { Assign(m); }
    Matrix3_s0048_ef30& Assign(const Matrix3_s0048_ef30& m);                   // 0x41cb40 (out of line)
    Vector3_s0048_ef30& operator[](int i) { return (&xAxis)[i]; }
};
struct Mat3Id_s0048_ef30 : Matrix3_s0048_ef30 {
    Mat3Id_s0048_ef30();                                            // 0x402ab0 (identity)
    Mat3Id_s0048_ef30& operator=(const Matrix3_s0048_ef30& m) { Matrix3_s0048_ef30::operator=(m); return *this; }
};
Vector3_s0048_ef30 operator-(const Vector3_s0048_ef30& a, const Vector3_s0048_ef30& b);   // 0x41db10
Vector3_s0048_ef30 operator*(const Vector3_s0048_ef30& v, const Matrix3_s0048_ef30& m);   // 0x41daf0
Vector3_s0048_ef30& operator+=(Vector3_s0048_ef30& a, const Vector3_s0048_ef30& b);       // 0x41ddb0
Matrix3_s0048_ef30 Inverse(const Matrix3_s0048_ef30& m);                       // 0x41ded0
Vector3_s0048_ef30 Normalize(const Vector3_s0048_ef30& v);                     // 0x436ce0
float VectorLength(const Vector3_s0048_ef30& v);                    // 0x40ae50
extern Vector3_s0048_ef30 g_UpAxis;                                 // 0x15d6324
struct BoundingBox_s0048_ef30 {
    Vector3_s0048_ef30 mMin, mMax;
    Vector3_s0048_ef30& GetCenter(Vector3_s0048_ef30& out) const;              // 0x409b90
};
struct Transform {                                       // cSPTransform, 0x38 bytes
    unsigned short mFlags, mVersion;
    Vector3_s0048_ef30 mPos;
    float mScale;
    Mat3Id_s0048_ef30 mRot;
    Transform();                                         // 0x409930
    void SetRotation(const Matrix3_s0048_ef30& m) { mRot = m; mFlags |= 2; mVersion++; }
    void PreRotate(const Vector3_s0048_ef30& axis, float angle);    // 0x6baba0
};
Matrix3_s0048_ef30 AlignBasis(Matrix3_s0048_ef30 m, Vector3_s0048_ef30 a, Vector3_s0048_ef30 b);     // 0x4906e0 (cdecl, hidden out ptr)
struct PosRot { Mat3Id_s0048_ef30 mRot; Vector3_s0048_ef30 mPos; };            // 0x30
struct Candidate_s0048_ef30 { PosRot pr; float score; };            // 0x34 (OrientedPoint)
template <class T> struct AutoRefCount_s0048_ef30 {
    T* mp;
    AutoRefCount_s0048_ef30() : mp(0) {}
    AutoRefCount_s0048_ef30(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount_s0048_ef30() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};
struct cSPEditorBlock_s0048_ef30;
struct cSPEditorModel_s0048_ef30;
struct BlockRefVec {
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>* mpBegin;
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>* mpEnd;
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>* mpCapacity;
    char mAllocator[0xc];
    void* mBuffer[8];
    BlockRefVec(const AllocTag& a = AllocTag()) { BaseInit(a); FixedInit(); }
    ~BlockRefVec();                                              // 0x00453eb0
    void BaseInit(const AllocTag& a);                            // 0x00540470
    void FixedInit();                                            // 0x00453770
    void push_back(const AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>& v);       // 0x004541f0
    int size() const { return mpEnd - mpBegin; }
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>& operator[](int i) { return mpBegin[i]; }
};
template <class T> void uninitialized_fill_n_ptr(T* p, uint32_t n, const T& value);   // 0x004fc960
struct PtrVecBase {
    cSPEditorBlock_s0048_ef30** mpBegin;
    cSPEditorBlock_s0048_ef30** mpEnd;
    cSPEditorBlock_s0048_ef30** mpCapacity;
    uint32_t mAlloc[2];
    PtrVecBase(uint32_t n, const AllocTag& a);                   // 0x004aa350
    ~PtrVecBase();                                               // 0x00425990
};
struct PtrVec : PtrVecBase {
    explicit PtrVec(uint32_t n, const AllocTag& a = AllocTag()) : PtrVecBase(n, a)
    {
        uninitialized_fill_n_ptr<cSPEditorBlock_s0048_ef30*>(mpBegin, n, (cSPEditorBlock_s0048_ef30*)0);
        mpEnd = mpBegin + n;
    }
    ~PtrVec()
    {
        for (cSPEditorBlock_s0048_ef30** p = mpBegin; p < mpEnd; ++p) {
        }
    }
    cSPEditorBlock_s0048_ef30*& operator[](uint32_t i) { return mpBegin[i]; }
};
struct ChildList {
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>* mpBegin;
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>* mpEnd;
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>* mpCapacity;
    int size() const { return mpEnd - mpBegin; }
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>& operator[](int i) { return mpBegin[i]; }
};
struct BlockList_s0048_ef30 {
    cSPEditorBlock_s0048_ef30** mpBegin; cSPEditorBlock_s0048_ef30** mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;                                          // 0x526430
    cSPEditorBlock_s0048_ef30*& operator[](int i) { return mpBegin[i]; }
};
struct CandVec_s0048_ef30 {
    Candidate_s0048_ef30* mpBegin; Candidate_s0048_ef30* mpEnd; Candidate_s0048_ef30* mpCap; uint32_t mAlloc[2];
    CandVec_s0048_ef30(const AllocTag&);                                    // 0x540470
    void push_back(const Candidate_s0048_ef30& c);                          // 0x4a9f30
    ~CandVec_s0048_ef30() { for (Candidate_s0048_ef30* p = mpBegin; p < mpEnd; ++p) {} Free(); }
    void Free();                                                 // 0x547c90
    int size() const { return (int)(mpEnd - mpBegin); }
    Candidate_s0048_ef30& operator[](int i) { return mpBegin[i]; }
    bool empty() const;                                          // 0x526430
};
struct cSPEditorModel_s0048_ef30 : RefObj {
    bool IsActive();                                    // 0x004adc40
    void SetColliding(int v);                           // 0x004adc20
    void AddBlock(cSPEditorBlock_s0048_ef30* block, int notify);   // 0x004abaf0
};
struct cSPEditorBlock_s0048_ef30 : RefObj {
    char pad0[0x28 - 4];
    AutoRefCount_s0048_ef30<cSPEditorModel_s0048_ef30> mpEditorModel;         // +0x28
    char pad2c[0x48 - 0x2c];
    Vector3_s0048_ef30 mPosition;                                  // +0x48
    char pad54[0xa8 - 0x54];
    Matrix3_s0048_ef30 mOrientation;                               // +0xa8
    char padcc[0xf0 - 0xcc];
    Matrix3_s0048_ef30 mUserOrientation;                           // +0xf0
    char pad114[0x33c - 0x114];
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30> mParentBlock;          // +0x33c
    ChildList mChildren;                                // +0x340
    char pad34c[0x3e0 - 0x34c];
    AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30> mSymmetricBlock;       // +0x3e0
    char pad3e4[0xdc8 - 0x3e4];
    bitset<60> mFlags;                                  // +0xdc8

    cSPEditorBlock_s0048_ef30* Split(int type);                    // 0x0044f420
    bool Func453520();                                  // 0x00453520
    void Func453500(bool v);                            // 0x00453500
    void SetSymmetricBlock(cSPEditorBlock_s0048_ef30* b);          // 0x00438cc0
    void SetAsymmetricBlock(cSPEditorBlock_s0048_ef30* b);         // 0x00438df0
    void SetPosition(const Vector3_s0048_ef30& pos, bool flag);    // 0x00448e90
    void SetUserOrientation(Matrix3_s0048_ef30 m);                 // 0x0043ffa0
    void SetOrientation(const Matrix3_s0048_ef30& m, bool flag);   // 0x00449420
    void SetBaseJointScale(int v);                      // 0x0044e980
    int  CalculateSymmetrySign();                       // 0x0044f240
    void LinkChild(cSPEditorBlock_s0048_ef30* b);                  // 0x00438700
    BoundingBox_s0048_ef30 GetBBox(int a, int b, int c);           // 0x0044ae00
};
inline bool IsNaN(float f) { uint32_t bits = *(uint32_t*)&f; return 0x7f800000 < (bits & 0x7fffffff); }
// ---- items of slice s0048ef30 end


// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)

// ---- items of slice s0048fde0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
};
struct Matrix3_s0048_fde0 {
    float m[9];
    void Assign(const void* src);
};
struct BoundingBox {
    Vector3 mn;
    Vector3 mx;
    BoundingBox() {}
    bool Intersects(const BoundingBox& b) const;
};
struct Tracker {
    char pad0[0x33c];
    int field33c;                         // 0x33c
    void GetOffsetA(Vector3* out, int flag);
    void GetOffsetB(Vector3* out, int flag);
    void Place();
};
struct SubMgr {
    int Count();
    void* Get(int i);
};
struct ModelType {
    void** begin;                         // 0x00
    void** end;                           // 0x04
    bool GetResourceTypeX();              // 0x00526430, thiscall
};
struct cSPEditorBlock {
    char pad0[0x28];
    SubMgr* mgr;                          // 0x28
    char pad1[0x48 - 0x2c];
    Vector3 position;                     // 0x48
    char pad2[0x33c - 0x54];
    int field33c;                         // 0x33c
    void** vecBegin;                      // 0x340
    void** vecEnd;                        // 0x344
    char pad3[0x3e0 - 0x348];
    Tracker* tracker;                     // 0x3e0
    void* field3e4;                       // 0x3e4
    char pad4[0xdc8 - 0x3e8];
    uint32_t bits;                        // 0xdc8

    bool Test();                          // 0x0044f220
    BoundingBox* GetBBox(BoundingBox* out, int a, int b, int c);
    BoundingBox* GetBBox(BoundingBox* out, int a, int b, int c, Vector3* extra);
    void F(Tracker* t);                   // 0x00438700
    bool F1(cSPEditorBlock* c, int type); // 0x00438440
    bool F2(cSPEditorBlock* c);           // 0x00438420
};
struct PtrBag {
    void Insert(void** pp);               // 0x004541f0, thiscall
};
struct IRefCounted {
    virtual void Slot0();
    virtual void AddRef();
    virtual void Release();
};
void Vector3_Normalize(Vector3* out, const Vector3* in);              // 0x00436ce0
Vector3* Cross(Vector3* out, const Vector3* a, const Vector3* b);     // 0x0044e460
Vector3* Vector3_Scale(Vector3* out, const float* s, const Vector3* v); // 0x0041de40
Vector3* Vector3_Sub(Vector3* out, const Vector3* a, const Vector3* b); // 0x0041db10
float VectorLength(const Vector3* v);                                 // 0x0040ae50
void ExpandBy(BoundingBox* b, float m);                               // 0x0044ad00
void SomeCtor(void* self, void* src);                                 // 0x00540470
void SomePush(void* self, void* v);                                   // 0x004a9e40
bool SomeMethod(void* self);                                          // 0x00526430
void SomeDtor(void* self);                                            // 0x004748c0
Vector3 BoundingBox_GetCenter(BoundingBox* b);                        // 0x00409b90 (approx.)
float Acos(float x);                                                  // 0x011e08c8
void TransformCtor(void* self);                                       // 0x00409930
void TransformSetAngleAxis(void* self, float angle, Vector3* axis);   // 0x006baba0
// ---- items of slice s0048fde0 end

Vector3* FUN_004909d0(Vector3* out, const Vector3* a, const Vector3* b);   // defined at 0x004909d0, called earlier in the TU

// ---- items of slice s0049c210 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s0049_c210 {
    float x, y, z;
    Vector3T_s0049_c210() {}
    Vector3T_s0049_c210(const Vector3T_s0049_c210& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T_s0049_c210 {
    Vector3T_s0049_c210 xAxis, yAxis, zAxis;
    Matrix33T_s0049_c210() {}
    Matrix33T_s0049_c210(const Matrix33T_s0049_c210& m) : xAxis(m.xAxis), yAxis(m.yAxis), zAxis(m.zAxis) {}
};
struct cSPVector3_s0049_c210 : Vector3T_s0049_c210 {
    cSPVector3_s0049_c210() {}
    cSPVector3_s0049_c210(const Vector3T_s0049_c210& v) : Vector3T_s0049_c210(v) {}
    cSPVector3_s0049_c210& operator=(const Vector3T_s0049_c210& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3_s0049_c210 : Matrix33T_s0049_c210 {
    cSPMatrix3_s0049_c210() {}
    cSPMatrix3_s0049_c210(const Matrix33T_s0049_c210& m) : Matrix33T_s0049_c210(m) {}
};
template<class T> struct AutoRefCount_s0049_c210 {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    T& operator*() const { return *mpObject; }
    T* get() const { return mpObject; }
};
struct cSPEditorBlock_s0049_c210;
struct cSPTransform_s0049_c210 {
    unsigned short mFlags;
    unsigned short mModificationCount;
    cSPVector3_s0049_c210 mTranslation;
    float mScale;
    cSPMatrix3_s0049_c210 mRotation;
    cSPTransform_s0049_c210();                                              // @ 0x409930
    cSPTransform_s0049_c210(const cSPTransform_s0049_c210& t);                         // @ 0x40ce80
};
struct TrackerRecord {
    cSPEditorBlock_s0049_c210* block;
    cSPTransform_s0049_c210 transform;
};
template<class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void push_back(const T& v);                                  // @ 0x4a9fa0
};
template<int N> struct bitset_s0049_c210 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
struct cSPEditorBlock_s0049_c210 {
    virtual void _v0();
    char pad0[0x48 - 4];
    cSPVector3_s0049_c210 mPosition;                        // +0x48
    char pad1[0x60 - 0x54];
    cSPMatrix3_s0049_c210 mOrientation;                     // +0x60
    char pad1b[0xa8 - 0x84];
    cSPVector3_s0049_c210 mRestPose;                        // +0xa8
    char pad2[0x1d8 - 0xb4];
    float mScale;                                // +0x1d8
    char pad3[0x33c - 0x1dc];
    AutoRefCount_s0049_c210<cSPEditorBlock_s0049_c210> mParentBlock;   // +0x33c
    vector<AutoRefCount_s0049_c210<cSPEditorBlock_s0049_c210> > mSymmetricBlocks;  // +0x340
    char pad4[0x3e0 - 0x34c];
    AutoRefCount_s0049_c210<cSPEditorBlock_s0049_c210> mPinTarget;     // +0x3e0
    char pad5[0x3ec - 0x3e4];
    void* mSkin;                                 // +0x3ec
    char pad6[0xdc8 - 0x3f0];
    bitset_s0049_c210<60> mFlags;                           // +0xdc8
    void FUN_438700(cSPEditorBlock_s0049_c210* block);      // @ 0x438700
    void GetOffsetA(cSPVector3_s0049_c210* out, bool f);    // @ 0x438120
    void GetOffsetB(cSPVector3_s0049_c210* out, bool f);    // @ 0x4381e0
    void Place(cSPVector3_s0049_c210 a, cSPVector3_s0049_c210 b);      // @ 0x437b00
};
Vector3T_s0049_c210 operator-(const Vector3T_s0049_c210& a, const Vector3T_s0049_c210& b);      // @ 0x41db10
float VectorLength(const Vector3T_s0049_c210& v);                         // @ 0x40ae50
cSPVector3_s0049_c210 operator*(const cSPVector3_s0049_c210& v, const cSPMatrix3_s0049_c210& m);  // @ 0x41daf0
cSPVector3_s0049_c210 operator+(const cSPVector3_s0049_c210& a, const cSPVector3_s0049_c210& b);  // @ 0x41dc10
cSPMatrix3_s0049_c210 operator*(const cSPMatrix3_s0049_c210& a, const cSPMatrix3_s0049_c210& b);  // @ 0x41de20
cSPVector3_s0049_c210 operator*(const cSPMatrix3_s0049_c210& m, const cSPVector3_s0049_c210& v);  // @ 0x41ded0
void RepinBlockToTorso(cSPEditorBlock_s0049_c210* block, cSPVector3_s0049_c210 t, cSPMatrix3_s0049_c210 r, int flags);  // @ 0x49fbd0
namespace SP {
namespace EditorUtils {
cSPVector3_s0049_c210 GetSkinTip(cSPEditorBlock_s0049_c210* block);                  // @ 0x4a5d10
}
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s0049_c210* FindSymmetricSpine(cSPEditorBlock_s0049_c210* block);     // @ 0x4a5970
}
}
namespace SP {
namespace EditorUtils {
bool FUN_435c80(cSPEditorBlock_s0049_c210* block);   // @ 0x435c80
}
}
namespace SP {
namespace EditorUtils {
bool FUN_43c510(cSPEditorBlock_s0049_c210* block);   // @ 0x43c510
}
}
namespace SP {
namespace EditorUtils {
struct cSPEditorModel;
}
}
// ---- items of slice s0049c210 end

// ---- items of slice s0049cfd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s0049_cfd0 {
    float x, y, z;
    Vector3T_s0049_cfd0() {}
    Vector3T_s0049_cfd0(const Vector3T_s0049_cfd0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix33T_s0049_cfd0 {
    Vector3T_s0049_cfd0 xAxis, yAxis, zAxis;
    Matrix33T_s0049_cfd0() {}
    Matrix33T_s0049_cfd0(const Matrix33T_s0049_cfd0& m) : xAxis(m.xAxis), yAxis(m.yAxis), zAxis(m.zAxis) {}
};
struct cSPVector3_s0049_cfd0 : Vector3T_s0049_cfd0 {
    cSPVector3_s0049_cfd0() {}
    cSPVector3_s0049_cfd0(const Vector3T_s0049_cfd0& v) : Vector3T_s0049_cfd0(v) {}
    cSPVector3_s0049_cfd0& operator=(const cSPVector3_s0049_cfd0& v) { x = v.x; y = v.y; z = v.z; return *this; }
    cSPVector3_s0049_cfd0& operator=(const Vector3T_s0049_cfd0& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3_s0049_cfd0 : Matrix33T_s0049_cfd0 {
    cSPMatrix3_s0049_cfd0() {}
    cSPMatrix3_s0049_cfd0(const Matrix33T_s0049_cfd0& m) : Matrix33T_s0049_cfd0(m) {}
};
struct cSPTransform_s0049_cfd0 {
    unsigned short mFlags;
    unsigned short mModificationCount;
    cSPVector3_s0049_cfd0 mTranslation;
    float mScale;
    cSPMatrix3_s0049_cfd0 mRotation;
    void TransformVector(cSPVector3_s0049_cfd0* out);   // @ 0x49d640
};
struct cSPEditorBlock_s0049_cfd0 {
    virtual void _v0();
    char pad0[0x1e0 - 4];
    float mMinUniformScale;                  // +0x1e0
    float mMaxUniformScale;                  // +0x1e4
    void SetUniformScale(float v, int flag); // @ 0x440090
};
cSPVector3_s0049_cfd0 operator*(const cSPVector3_s0049_cfd0& v, const cSPMatrix3_s0049_cfd0& m);   // @ 0x41daf0
void ScaleVector(cSPVector3_s0049_cfd0* v, const float& s);                  // @ 0x41dba0
// ---- items of slice s0049cfd0 end

// ---- items of slice s0049ecf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s0049_ecf0 {
    float x, y, z;
    Vector3T_s0049_ecf0() {}
    Vector3T_s0049_ecf0(const Vector3T_s0049_ecf0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct cSPVector3_s0049_ecf0 : Vector3T_s0049_ecf0 {
    cSPVector3_s0049_ecf0() {}
    cSPVector3_s0049_ecf0(const Vector3T_s0049_ecf0& v) : Vector3T_s0049_ecf0(v) {}
};
struct cSPEditorBlock_s0049_ecf0 {
    virtual void _v0();
};
struct cSomeTracker {
    void AddVector(const cSPVector3_s0049_ecf0& v);       // @ 0x44d4f0
};
// ---- items of slice s0049ecf0 end

// ---- items of slice s0049efc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s0049_efc0 {
    float x, y, z;
    Vector3T_s0049_efc0() {}
    Vector3T_s0049_efc0(const Vector3T_s0049_efc0& v);                         // 0x004098a0
};
struct cSPVector3_s0049_efc0 : Vector3T_s0049_efc0 {
    cSPVector3_s0049_efc0() {}
    cSPVector3_s0049_efc0(const cSPVector3_s0049_efc0& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3_s0049_efc0(const Vector3T_s0049_efc0& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix33T_s0049_efc0 {
    float m[3][3];
    Matrix33T_s0049_efc0();                                         // 0x00402ab0
};
struct Matrix3L : Matrix33T_s0049_efc0 {
    Matrix3L(const Matrix33T_s0049_efc0& o) { Matrix33T_s0049_efc0::operator=(o); }
};
struct cSPMatrix3_s0049_efc0 : Matrix33T_s0049_efc0 {
    cSPMatrix3_s0049_efc0(const Matrix33T_s0049_efc0& o) : Matrix33T_s0049_efc0(o) {}
};
Vector3T_s0049_efc0 operator-(const Vector3T_s0049_efc0& a, const Vector3T_s0049_efc0& b);     // 0x0041db10
Vector3T_s0049_efc0 operator+(const Vector3T_s0049_efc0& a, const Vector3T_s0049_efc0& b);     // 0x0041dc10
Vector3T_s0049_efc0 operator*(const Vector3T_s0049_efc0& v, const Matrix33T_s0049_efc0& m);    // 0x0041daf0
Matrix33T_s0049_efc0 operator*(const Matrix33T_s0049_efc0& a, const Matrix33T_s0049_efc0& b);  // 0x0041de20
Matrix33T_s0049_efc0 Inverse(const Matrix33T_s0049_efc0& m);                        // 0x0041ded0
Vector3T_s0049_efc0 Mirror(const Vector3T_s0049_efc0& v);                           // 0x004a8f40 (x -> -x)
Matrix33T_s0049_efc0 MirrorMatrix(const Matrix33T_s0049_efc0& m, int axis);         // 0x004a8e10
extern const Vector3T_s0049_efc0 kZeroVector_s0049_efc0;                            // 0x015d64d8
template<class T> struct AutoRefCount_s0049_efc0 {
    T* mp;
    AutoRefCount_s0049_efc0(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount_s0049_efc0() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};
template<unsigned N> struct bitset_s0049_efc0 {
    uint32_t mWord[(N + 31) / 32];
    bool test(unsigned i) const {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
namespace eastl {
template<class InputIterator, class T>
inline InputIterator find_s0049_efc0(InputIterator first, InputIterator last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}
}
struct cSPEditorBlock_s0049_efc0;
typedef AutoRefCount_s0049_efc0<cSPEditorBlock_s0049_efc0> BlockRef_s0049_efc0;
struct SPAlloc_s0049_efc0 {
    uint32_t a, b;
    SPAlloc_s0049_efc0(const AllocTag& t);                          // 0x00429360
};
struct BlockVec_s0049_efc0 {
    BlockRef_s0049_efc0* mpBegin;
    BlockRef_s0049_efc0* mpEnd;
    BlockRef_s0049_efc0* mpCapacity;
    SPAlloc_s0049_efc0 mAllocator;
    BlockVec_s0049_efc0(const AllocTag& t = AllocTag()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(t) {}
    ~BlockVec_s0049_efc0();                                         // 0x00453eb0
    void push_back(const BlockRef_s0049_efc0& v);                   // 0x004541f0
    BlockRef_s0049_efc0* begin() { return mpBegin; }
    BlockRef_s0049_efc0* end() { return mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef_s0049_efc0& operator[](int i) { return mpBegin[i]; }
};
struct BlockVecX : BlockVec_s0049_efc0 {
    BlockVecX(const AllocTag& t);                        // 0x00540470
};
struct cSPEditorModel_s0049_efc0 : RefObj {
    bool IsSymmetryEnabled();                            // 0x004adc40
};
struct cMWModel : RefObj {
    char pad4[0xc - 4];
    Vector3T_s0049_efc0 mOffset;                                    // +0x0c
};
struct cSPEditorBlock_s0049_efc0 : RefObj {
    char pad0[0x28 - 4];
    AutoRefCount_s0049_efc0<cSPEditorModel_s0049_efc0> mpEditorModel;          // +0x28
    char pad2c[0x48 - 0x2c];
    cSPVector3_s0049_efc0 mPosition;                                // +0x48
    char pad54[0xa8 - 0x54];
    Matrix33T_s0049_efc0 mOrientation;                              // +0xa8
    char padcc[0x3e0 - 0xcc];
    AutoRefCount_s0049_efc0<cSPEditorBlock_s0049_efc0> mpSymmetricBlock;       // +0x3e0
    char pad3e4[0x3f0 - 0x3e4];
    AutoRefCount_s0049_efc0<cMWModel> mpSocketConnectorModel;       // +0x3f0
    char pad3f4[0xdc8 - 0x3f4];
    bitset_s0049_efc0<60> mFlags;                                   // +0xdc8

    int GetSymmetryIndex();                              // 0x0044f220
    void SetPosition(const Vector3T_s0049_efc0& pos, bool notify);  // 0x00448e90
    void SetOrientation(const Matrix33T_s0049_efc0& m, bool notify);   // 0x00449420
};
void BuildPileList(cSPEditorBlock_s0049_efc0* block, BlockVec_s0049_efc0* list, bool b);            // 0x0048c790
bool GetSymmetricPile(cSPEditorBlock_s0049_efc0* block, BlockVec_s0049_efc0* list, bool b);         // 0x0049dd20
// ---- items of slice s0049efc0 end

// ---- items of slice s004a0b70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_ModelWorld;                                     // @ 0x15d60f4
struct Vector3T_s004a_0b70 {
    float x, y, z;
    Vector3T_s004a_0b70() {}
    Vector3T_s004a_0b70(const Vector3T_s004a_0b70& v) : x(v.x), y(v.y), z(v.z) {}
    float Dot2(const Vector3T_s004a_0b70& o) const { return o.x * x + o.y * y + o.z * z; }
    float Dot_s004a_0b70(const Vector3T_s004a_0b70& o) const { return x * o.x + y * o.y + z * o.z; }
};
inline float Dot_s004a_0b70(const Vector3T_s004a_0b70& u, const Vector3T_s004a_0b70& v) { return u.x * v.x + u.y * v.y + u.z * v.z; }
struct cSPVector3_s004a_0b70 : Vector3T_s004a_0b70 {
    cSPVector3_s004a_0b70() {}
    cSPVector3_s004a_0b70(const Vector3T_s004a_0b70& v) : Vector3T_s004a_0b70(v) {}
};
Vector3T_s004a_0b70 operator-(const Vector3T_s004a_0b70& a, const Vector3T_s004a_0b70& b);   // @ 0x41db10
float VectorLength(const Vector3T_s004a_0b70& v);                       // @ 0x40ae50
template<int N> struct bitset_s004a_0b70 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
struct SPAllocTmp { char c; SPAllocTmp() {} };
template<class T> struct AutoRefCount_s004a_0b70 {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> struct vector_s004a_0b70 {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    T& operator[](uint32_t n) { return mpBegin[n]; }
    void AllocatorInit(struct SPAllocTmp* tmp);                           // @ 0x429360 (sp_vector_allocator ctor on mAllocator)
    void push_back(const T& v);                              // @ 0x454860
    ~vector_s004a_0b70();                                               // @ 0x425990
};
struct UIntVector_s004a_0b70 {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t mAllocator[2];
    void AllocatorInit(struct SPAllocTmp* tmp);              // 0x429360
    void push_back(const uint32_t& v);                       // 0x454860
    ~UIntVector_s004a_0b70();                                           // 0x425990
};
struct cSPEditorBlock_s004a_0b70;
struct cSPEditorModel_s004a_0b70 {
    bool FUN_4adc40();                                       // 0x4adc40 (returns byte +0x4f)
    cSPEditorBlock_s004a_0b70* GetBlock(int i);                         // @ 0x4accb0
    int GetBlockCount();                                     // @ 0x4accf0
    float GetScale();                                        // @ 0x4adaa0
    void AddBlock(cSPEditorBlock_s004a_0b70* b, bool notify);           // @ 0x4abaf0
};
struct cSPEditorHandle {
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void _v3();
    virtual void _v4();
    virtual void _v5();
    virtual void _v6();
    virtual void _v7();
    virtual void _v8();
    virtual void _v9();
    virtual void _v10();
    virtual void _v11();
    virtual void SetActive(bool a, bool b);                  // +0x30
};
struct cSPEditorMessageManager {
    void Post(uint32_t id, int a, cSPEditorBlock_s004a_0b70* block, int b);   // @ 0x45ae40
};
cSPEditorMessageManager* GetEditorMessageManager();         // @ 0x401050
struct IMessageServer_s004a_0b70 {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void Post(uint32_t id, int a, int b);            // +0x14
};
IMessageServer_s004a_0b70* MessageServer_s004a_0b70();                             // @ 0x67dcc0
struct cSPEditorLimbStructure_s004a_0b70 {
    char data[0x58];
    cSPEditorLimbStructure_s004a_0b70();                                // @ 0x488850
    ~cSPEditorLimbStructure_s004a_0b70();                               // @ 0x488900
    void Build(cSPEditorBlock_s004a_0b70* b, int a, int c);             // @ 0x4891a0
    void Apply();                                            // @ 0x48bfa0
    void FixAll();                                           // @ 0x489ae0
    void FixB();                                             // @ 0x48a4c0
    void FixC();                                             // @ 0x488980
};
struct cSPEditorBlock_s004a_0b70 {
    virtual void _v0();
    virtual void AddRef();
    virtual void Release();
    char pad0[0x18 - 4];
    int mModelWorld;                             // +0x18
    char pad1[0x28 - 0x1c];
    cSPEditorModel_s004a_0b70* mEditorModel;                // +0x28
    char pad2[0x48 - 0x2c];
    Vector3T_s004a_0b70 mPosition;                          // +0x48
    char pad3[0x60 - 0x54];
    Vector3T_s004a_0b70 mAxes[3];                           // +0x60
    char pad4[0x33c - 0x84];
    cSPEditorBlock_s004a_0b70* mSocketConnector;            // +0x33c
    vector_s004a_0b70<AutoRefCount_s004a_0b70<cSPEditorBlock_s004a_0b70> > mChildren;           // +0x340
    char pad5[0x3e0 - 0x354];
    cSPEditorBlock_s004a_0b70* mSymmetricBlock;             // +0x3e0
    char pad6[0x3ec - 0x3e4];
    cSPEditorHandle* mHandle;                    // +0x3ec
    cSPEditorBlock_s004a_0b70* mAttachPoint;                // +0x3f0 (has a position at +0xc)
    char pad7[0xdc8 - 0x3f4];
    bitset_s004a_0b70<60> mFlags;                           // +0xdc8
    cSPEditorBlock_s004a_0b70* GetAttach() { return mAttachPoint; }

    cSPEditorBlock_s004a_0b70();                                        // @ 0x4346b0
    char pad8[0xe08 - 0xdd0];
    void FUN_451360();                                       // @ 0x451360
    void BuildBlock(uint32_t type, int world, int a, int b, float c, int d, int e, int f);   // @ 0x441440
    void SetBooleanAttribute(int attr, bool value);          // @ 0x435a10
    void Split(int n);                                       // @ 0x44f420
    bool IsPaintable();                                      // @ 0x44c030
    void OnRemoved(bool a, bool b);                          // @ 0x44ba20
    void SetUIState(bool a, bool b);                         // @ 0x44bcf0
    void FUN_438a40(cSPEditorBlock_s004a_0b70* b);                      // @ 0x438a40
    void RecursiveFlag();                                    // @ 0x44ede0
    float GetScaleF();                                       // @ 0x435c00
    int GetSomeId();                                         // @ 0x4511d0
    void Attach(cSPEditorBlock_s004a_0b70* b);                          // @ 0x438700
    void SetOrientation(Vector3T_s004a_0b70* p, int a);                 // @ 0x449420
    void SetPosition(Vector3T_s004a_0b70* p, int a);                    // @ 0x448e90
    float GetAnim();                                         // @ 0x43eed0
    void SetAnim(float f);                                   // @ 0x43eb50
    bool Near(float a, float b);                             // @ 0x43bcf0
    bool CanConnect(cSPEditorBlock_s004a_0b70* o, int n);               // @ 0x438440
    void GetAxisIndices(int* a, int* b, int* c);             // @ 0x44c0e0
};
void* __cdecl operator new(unsigned sz, const char* name, int a, int b, int c, int d);  // @ 0xf473a0
void __cdecl SetSymmetricBlocksUIState(cSPEditorBlock_s004a_0b70* b, int a, int c);   // @ 0x4a7f30
void __cdecl DeleteInvalidBlocks(cSPEditorBlock_s004a_0b70* b, int a);                // @ 0x4a6f10
bool __cdecl FUN_4a7e60(cSPEditorBlock_s004a_0b70* b);
bool __cdecl FUN_4a7dd0(cSPEditorBlock_s004a_0b70* b);
// ---- items of slice s004a0b70 end

// ---- items of slice s004a29a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kNegHalfPi;                    // 0x013ef57c (-pi/2)
struct rwVec3_s004a_29a0 {
    float x, y, z;
    rwVec3_s004a_29a0() {}
    rwVec3_s004a_29a0(const rwVec3_s004a_29a0& v);                      // 0x004098a0
};
struct cSPVector3_s004a_29a0 : rwVec3_s004a_29a0 {
    cSPVector3_s004a_29a0() {}
    cSPVector3_s004a_29a0(const cSPVector3_s004a_29a0& v) : rwVec3_s004a_29a0(v) {}
};
rwVec3_s004a_29a0 operator-(const rwVec3_s004a_29a0& a, const rwVec3_s004a_29a0& b);   // 0x0041db10
struct Vec3_s004a_29a0 {
    float x, y, z;
    Vec3_s004a_29a0() {}
    Vec3_s004a_29a0(const Vec3_s004a_29a0& v) : x(v.x), y(v.y), z(v.z) {}
    Vec3_s004a_29a0(const rwVec3_s004a_29a0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct cSPMatrix3_s004a_29a0 {
    rwVec3_s004a_29a0 r[3];
    cSPMatrix3_s004a_29a0(const cSPMatrix3_s004a_29a0& m);              // 0x0041cb40
    rwVec3_s004a_29a0& operator[](int i) { return r[i]; }
};
struct cSPTransform_s004a_29a0 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vec3_s004a_29a0 mTranslation;
    float mScale;
    cSPMatrix3_s004a_29a0 mRotation;
    cSPTransform_s004a_29a0();                                          // 0x00409930
    const cSPMatrix3_s004a_29a0& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3_s004a_29a0& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void PreRotate(const Vec3_s004a_29a0& axis, float angle);     // 0x006baba0
};
template<class T> struct AutoRefCount_s004a_29a0 {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cCounted {
    uint32_t pad0[3];
    rwVec3_s004a_29a0 mPosition;                             // +0x0c
    uint32_t pad18[(0x40 - 0x18) / 4];
    int mRefCount;                                // +0x40
    void AddRef() { mRefCount = mRefCount + 1; }
    void Release();                               // 0x0040f360
};
template<class T> struct CountedRef {
    T* mpObject;
    CountedRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~CountedRef() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    const rwVec3_s004a_29a0& GetPosition() const { return mpObject->mPosition; }
};
struct cSPEditorBlockModel {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual void _v8();
    virtual rwVec3_s004a_29a0 GetPosition();             // +0x24
    virtual void _v10(); virtual void _v11();
    virtual void SetState(int a, int b);          // +0x30
};
void UpdateModelPaint(cSPEditorBlockModel* m, float delta);   // 0x00496b60
struct cSPEditorModel_s004a_29a0 {
    bool IsUsingSymmetry();                       // 0x004adc40
};
struct cSPEditorBlock_s004a_29a0;
struct BlockVec_s004a_29a0 {
    AutoRefCount_s004a_29a0<cSPEditorBlock_s004a_29a0>* mpBegin;
    AutoRefCount_s004a_29a0<cSPEditorBlock_s004a_29a0>* mpEnd;
    AutoRefCount_s004a_29a0<cSPEditorBlock_s004a_29a0>& operator[](int i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cSPEditorBlock_s004a_29a0 {
    virtual void _v0();
    uint32_t pad04[(0x28 - 4) / 4];
    cSPEditorModel_s004a_29a0* mpEditorModel;                // +0x28
    uint32_t pad2c[(0x48 - 0x2c) / 4];
    cSPVector3_s004a_29a0 mPosition;                         // +0x48
    uint32_t pad54[(0x60 - 0x54) / 4];
    cSPMatrix3_s004a_29a0 mOrientation;                      // +0x60
    uint32_t pad84[(0xa8 - 0x84) / 4];
    cSPMatrix3_s004a_29a0 mBaseOrientation;                  // +0xa8
    uint32_t padcc[(0x33c - 0xcc) / 4];
    AutoRefCount_s004a_29a0<cSPEditorBlock_s004a_29a0> mParent;         // +0x33c
    BlockVec_s004a_29a0 mChildren;                           // +0x340
    uint32_t pad348[(0x3e0 - 0x348) / 4];
    AutoRefCount_s004a_29a0<cSPEditorBlock_s004a_29a0> mPinTarget;      // +0x3e0
    uint32_t pad3e4[2];
    AutoRefCount_s004a_29a0<cSPEditorBlockModel> mModel;     // +0x3ec
    AutoRefCount_s004a_29a0<cCounted> mSocket;               // +0x3f0
    uint32_t pad3f4[(0xdc8 - 0x3f4) / 4];
    Bitset60 mFlags;                              // +0xdc8
    cSPEditorBlockModel* GetModel() const { return mModel; }
    bool GetBooleanAttribute(uint32_t id) const { return mFlags.test(id); }
    void SetBooleanAttribute(int id, bool v);     // 0x00435a10
    float GetSnapScale();                         // 0x0043eed0
    void SetVec194(cSPVector3_s004a_29a0 v);                     // 0x00451330
    void FUN_44ba20(int a, int b);                // 0x0044ba20
    void PinBlock(cSPEditorBlock_s004a_29a0* b);             // 0x00438700
    void RecursiveFlagA();                        // 0x0044ede0
    bool FUN_448c10();                            // 0x00448c10
    int GetSymmetryIndex();                       // 0x0044f220
    int CalculateSymmetrySign();                  // 0x0044f240
    void SetModelBasedOnSymmetrySign(int sign, bool mirror, bool recurse, int a, int b);  // 0x00439110
    bool FUN_435c80();                            // 0x00435c80
};
struct cSPEditorLimbStructure_s004a_29a0 {
    uint32_t pad[0x58 / 4];
    cSPEditorLimbStructure_s004a_29a0();                     // 0x00488850
    ~cSPEditorLimbStructure_s004a_29a0();                    // 0x00488900
    void Init(cSPEditorBlock_s004a_29a0* root, int a, int b);   // 0x004891a0
    void FUN_48c030();                            // 0x0048c030
    void FixAllJoints();                          // 0x00489ae0
    void Rebuild();                               // 0x0048a4c0
    void FUN_488980();                            // 0x00488980
};
struct MsgArg { union { void* p; float f; }; uint32_t pad; };
struct BlockSnapMessage {
    MsgArg mArgs[3];
    int mFlags;
    MsgArg& operator[](int i) { return mArgs[i]; }
};
struct IMessageServer_s004a_29a0 {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void Send(uint32_t id, void* data, int b);   // +0x14
};
IMessageServer_s004a_29a0* MessageServer_s004a_29a0();                  // 0x0067dcc0
IMessageManager* MessageManager_s004a_29a0();                // 0x00401050
int CountSnapBlocks(cSPEditorBlock_s004a_29a0* b, int flag); // 0x00491350
cSPMatrix3_s004a_29a0 BuildSymmetricOrientation(cSPMatrix3_s004a_29a0 m, int mode);   // 0x004a25f0
void RepinBlockToTorso(cSPEditorBlock_s004a_29a0* b, Vec3_s004a_29a0 pos, cSPMatrix3_s004a_29a0 m, int flag);   // 0x0049fbd0
void SetSymmetricBlocksUIState(cSPEditorBlock_s004a_29a0* b, int a, int c);   // 0x004a7f30
bool FUN_4a7e60(cSPEditorBlock_s004a_29a0* b);               // 0x004a7e60
bool FUN_4a7dd0(cSPEditorBlock_s004a_29a0* b);               // 0x004a7dd0
// ---- items of slice s004a29a0 end

// ---- items of slice s004a3760 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPEditorBlock_s004a_3760 { virtual void _v0(); };
// ---- items of slice s004a3760 end

// ---- items of slice s004a5970 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3T_s004a_5970 {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T_s004a_5970() {}
    Vector3T_s004a_5970(const Vector3T_s004a_5970& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T_s004a_5970 {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T_s004a_5970 xAxis, yAxis, zAxis;
};
struct cSPVector3_s004a_5970 : Vector3T_s004a_5970 {
    cSPVector3_s004a_5970() {}
    cSPVector3_s004a_5970(const Vector3T_s004a_5970& v) : Vector3T_s004a_5970(v) {}
    cSPVector3_s004a_5970& operator=(const Vector3T_s004a_5970& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3T_s004a_5970 operator*(const Vector3T_s004a_5970& v, const Matrix33T_s004a_5970& m);   // @ 0x41daf0
Vector3T_s004a_5970 operator-(const Vector3T_s004a_5970& v);                       // @ 0x422020
Vector3T_s004a_5970 operator+(const Vector3T_s004a_5970& a, const Vector3T_s004a_5970& b);    // @ 0x41dc10
template<class T> struct AutoRefCount_s004a_5970 {
    T* mpObject;
    ~AutoRefCount_s004a_5970() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T& operator*() const { return *mpObject; }
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> struct CtorSlots { static void Reserve() {} static void ReserveClear() {} };
template<class T> struct AutoRefCount_s004a_5970;
template<class T> struct CtorSlots<AutoRefCount_s004a_5970<T> > { static void Reserve() { ScratchSlots<1>(); } static void ReserveClear() { ScratchSlots<3>(); } };
template<class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) { CtorSlots<T>::Reserve(); }
    ~VectorBase();                                           // @ 0x425990 (shared)
};
template<class T> struct vector_s004a_5970 : VectorBase<T> {
    vector_s004a_5970() {}
    ~vector_s004a_5970() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* erase(T* first, T* last);                             // @ 0x4769b0 / 0x454280
    void clear() { erase(mpBegin, mpEnd); ScratchSlots<4>(); CtorSlots<T>::ReserveClear(); }
    bool empty() const;                                      // @ 0x526430
    void DoDestroyValues(T* first, T* last) { for (; first < last; ++first) first->~T(); }
};
template<int N> struct bitset_s004a_5970 {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
namespace SP {
#define PV(n) virtual void _v##n();
}
namespace SP {
struct cSkinMesh {
    virtual int AddRef();
    PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual void Rebuild(int mode, int flags);               // 0x30
};
}
namespace SP {
struct cSkinOwner {
    virtual int AddRef();
};
}
namespace SP {
template<class T> struct ArgRef {           // AutoRefCount passed by value (callee releases)
    T* mpObject;
    ArgRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
};
}
namespace SP {
struct cSPEditorModel_s004a_5970;
}
namespace SP {
struct cSPEditorBlock_s004a_5970 {
    virtual void _v0();
    virtual int Release();
    char pad0[0x48 - 4];
    cSPVector3_s004a_5970 mPosition;                       // +0x48
    char pad1[0x60 - 0x54];
    struct { Vector3T_s004a_5970 mRow[3]; const Vector3T_s004a_5970& GetRow(int i) const { return mRow[i]; } } mOrientation;  // +0x60 (cSPMatrix3)
    char pad2[0x1d8 - 0x84];
    float mScale;                               // +0x1d8
    char pad3[0x33c - 0x1dc];
    AutoRefCount_s004a_5970<cSPEditorBlock_s004a_5970> mParentBlock;  // +0x33c
    vector_s004a_5970<AutoRefCount_s004a_5970<cSPEditorBlock_s004a_5970> > mSymmetricBlocks;   // +0x340
    char pad4[0x3e0 - 0x354];
    int mUIState;                               // +0x3e0
    char pad5[0x3ec - 0x3e4];
    AutoRefCount_s004a_5970<cSkinMesh> mSkin;              // +0x3ec
    char pad6[0xdc8 - 0x3f0];
    bitset_s004a_5970<60> mFlags;                          // +0xdc8

    float GetScale() const { return mScale; }
    int GetUIState() const { return mUIState; }
    cSPEditorBlock_s004a_5970* GetParent() const { return mParentBlock; }
    int GetSymmetryCount();                                  // @ 0x44f220
};
}
namespace SP {
struct cSPEditorModel_s004a_5970 {
    cSPEditorBlock_s004a_5970* GetBlock(int i);                         // @ 0x4accb0
    int GetBlockCount();                                     // @ 0x4accf0
};
}
namespace SP {
Vector3T_s004a_5970 operator*(const Vector3T_s004a_5970& v, const float& s);                    // @ 0x41dca0
}
namespace SP {
bool SkinUsesModel(cSkinMesh* skin, ArgRef<cSkinOwner> owner);            // @ 0x498850
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s004a_5970* GetLimbRoot(cSPEditorBlock_s004a_5970* block);
}
}
namespace SP {
namespace EditorUtils {
bool IsLimbConnected(cSPEditorBlock_s004a_5970* block);
}
}
namespace SP {
namespace EditorUtils {
void RebuildSkins(cSPEditorBlock_s004a_5970* block, cSkinOwner* owner);
}
}
namespace SP {
namespace EditorUtils {
void RefreshSkins(cSPEditorBlock_s004a_5970* block, cSPEditorBlock_s004a_5970* except);
}
}
namespace SP {
namespace EditorUtils {
float GetSkinRadiusFromVertebra(float scale);
}
}
namespace SP {
namespace EditorUtils {
cSPVector3_s004a_5970 GetSkinPoint(const cSPVector3_s004a_5970& pos, const cSPVector3_s004a_5970& dir, float scale);
}
}
// ---- items of slice s004a5970 end

// ---- items of slice s004a6690 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefCountTemplate_s004a_6690 {
    virtual ~RefCountTemplate_s004a_6690();
    int mRefCount;
    int AddRef() { return mRefCount++ + 1; }
    int Release();                                                  // 0x00453540
};
template <class T> struct AutoRefCount_s004a_6690 {
    T* mpObject;
    AutoRefCount_s004a_6690(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004a_6690() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cSPEditorBlock_s004a_6690;
typedef AutoRefCount_s004a_6690<cSPEditorBlock_s004a_6690> BlockRef_s004a_6690;
struct BlockVector_s004a_6690 {
    BlockRef_s004a_6690* mpBegin;
    BlockRef_s004a_6690* mpEnd;
    BlockRef_s004a_6690* mpCapacity;
    uint32_t  mAllocator[2];
    BlockVector_s004a_6690(const AllocTag& a = AllocTag());                    // 0x00540470
    ~BlockVector_s004a_6690();                                                 // 0x00453eb0
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef_s004a_6690& operator[](int i) { return mpBegin[i]; }
};
struct FixedBlockVector_s004a_6690 : BlockVector_s004a_6690 {
    uint32_t mOverflow;
    void*    mBuffer[8];
    FixedBlockVector_s004a_6690() { FixedInit(); }
    void FixedInit();                                               // 0x00453770
};
struct FixedBlockVectorInl {
    BlockRef_s004a_6690* mpBegin;
    BlockRef_s004a_6690* mpEnd;
    BlockRef_s004a_6690* mpCapacity;
    uint32_t  mAllocator[2];
    uint32_t  mOverflow;
    void*     mBuffer[8];
    void Construct(const AllocTag& a);                              // 0x00540470
    void FixedInit();                                               // 0x00453770
    void DestructRange(BlockRef_s004a_6690* first, BlockRef_s004a_6690* last);            // 0x00454e90
    void Free();                                                    // 0x00425990
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef_s004a_6690& operator[](int i) { return mpBegin[i]; }
    FixedBlockVectorInl() { Construct(AllocTag()); FixedInit(); }
    ~FixedBlockVectorInl() { DestructRange(mpBegin, mpEnd); Free(); }
};
struct cSPEditorPhysicsWorld_s004a_6690 {
    void SetFloorFilter(int group);                                 // 0x004b9440
    void UpdateCollisionFilters();                                  // 0x004b9420
};
struct cSPEditorBlock_s004a_6690 {
    virtual void _v0();
    uint32_t pad04[(0x28 - 0x04) / 4];
    struct cSPEditorModel_s004a_6690* mpModel;                                 // +0x028
    uint32_t pad2c[(0x3e0 - 0x2c) / 4];
    BlockRef_s004a_6690 mSymmetricBlock;                                       // +0x3e0
    uint32_t pad3e4[(0xdc8 - 0x3e4) / 4];
    bitset<60> mFlags;                                              // +0xdc8

    cSPEditorModel_s004a_6690* GetEditorModel() { return mpModel; }
    cSPEditorBlock_s004a_6690* GetSymmetricBlock() { return mSymmetricBlock; }
    bool FUN_43fc20(int a, int b);               // @ 0x43fc20
    void SetValid(bool v);                       // @ 0x43f6b0
    void SetCollisionGroup(int group);                              // 0x00451e50
    bool IsFlagSet(unsigned i) { return mFlags.test(i); }
    bool HasRelevantPoints2(cSPEditorBlock_s004a_6690* other);                 // 0x00438420
    int GetSkinIdentifierForPicking();                              // 0x0043a870
};
struct cSPEditorModel_s004a_6690 : cSPEditorModelBase, RefCountTemplate_s004a_6690 {      // RefCountTemplate at +4
    cSPEditorBlock_s004a_6690* GetBlock(int i);                                // @ 0x4accb0
    int GetBlockCount();                                            // @ 0x4accf0
    bool FUN_4adc40();                                              // @ 0x4adc40
    void FUN_4adc20(int v);                                         // @ 0x4adc20
    cSPEditorPhysicsWorld_s004a_6690* GetPhysicsWorld();                       // 0x004ad450
};
bool GetSymmetricPile(cSPEditorBlock_s004a_6690* block, BlockVector_s004a_6690* list, bool b);   // 0x0049dd20
// ---- items of slice s004a6690 end

// @ 0x00435f40
void RecordEvent4(uint32_t a, uint32_t b, float c, uint32_t d)
{
    Recorder* r = GetRecorder();
    if (r) {
        r->Begin(0x3475376);
        r->WriteInt(0x3475385, a);
        r->WriteInt(0x34753A7, b);
        r->WriteFloat(0x34753AA, c);
        r->WriteInt(0x34753AD, d);
        r->End();
    }
}




















































// @ 0x00453250
namespace SP { namespace EditorUtils {
HavokTransform* __fastcall GetHavokTransformFromMatrix(HavokTransform* t)
{
    t->a = kZero;
    t->b = kZero;
    hkVector4_s0045_3250& tr = t->m_translation;
    tr.w = kZero; tr.z = kZero; tr.y = kZero; tr.x = kZero;
    hkRotation_s0045_3250& r = t->m_rotation;
    hkVector4_s0045_3250 zero;
    zero.w = kZero; zero.z = kZero; zero.y = kZero; zero.x = kZero;
    r.getColumn(0) = zero;
    r.getColumn(1) = zero;
    r.getColumn(2) = zero;
    return t;
}
}}  // namespace SP::EditorUtils



















































// @ 0x00481f00
bool IsNAN(const float* v)
{
    int n35;
    if (IsNaNF(v[0]) || IsNaNF(v[1]) || IsNaNF(v[2]))
        n35 = 1;
    else
        n35 = 0;
    return n35;
}


















































// @ 0x0048d010
hkRigidBody_s0048_d010* MoveBlockLowAngleStacking(cSPEditorBlock_s0048_d010* block, BlockList& piles, cSPVector3_s0048_d010 position, cSPVector3_s0048_d010 direction, cSPVector3_s0048_d010& outPosition, Matrix3_s0048_d010 orientation, bool unused)
{
    cSPEditorModel_s0048_d010* model = block->mEditorModel;
    int noParent = 0;
    int filterInfo = 1;
    model->NumberBlocks();

    hkRigidBody_s0048_d010* rb = block->mpRigidBody;
    if (rb == 0)
        return 0;

    hkTransform_s0048_d010 originalTransform(rb->getRigidMotion()->getTransform());

    const hkShape_s0048_d010* unusedShape;
    const hkShape_s0048_d010* blockShape = unusedShape;
    blockShape = rb->getCollidable()->getShape();
    hkAabb_s0048_d010 blockAabb;
    blockShape->getAabb(hkTransform_s0048_d010::getIdentity(), 0.0f, blockAabb);
    float originalZ = rb->getRigidMotion()->getPosition()(2);

    PrepareBlockForStacking(block, piles, noParent, filterInfo, 1);
    if (block->mSymmetricBlock)
        block->mSymmetricBlock->SetCollisionFilterInfo(filterInfo);

    hkLinearCastInput_s0048_d010 input;
    cSPVector3_s0048_d010 target = position + 100.0f * direction;
    input.m_to = ToHkVector4_s0048_d010(target);
    input.m_startPointTolerance = 0.0f;
    input.m_maxExtraPenetration = 0.0f;
    rb->setPosition(ToHkVector4_s0048_d010(position));

    hkRotation_s0048_d010 rotation;
    ToHkRotation(orientation, rotation);
    hkTransform_s0048_d010 castTransform;
    castTransform = rb->getRigidMotion()->getTransform();
    castTransform.setRotation(rotation);
    rb->setTransform(castTransform);

    hkClosestCdPointCollector_s0048_d010 collector;
    hkRigidBody_s0048_d010* body = block->mpRigidBody;
    model->GetPhysicsWorld()->World()->linearCast(body->getCollidable(), input, collector, 0);

    bool found = false;
    hkRigidBody_s0048_d010* result = 0;
    if (collector.hasHit()) {
        hkRigidBody_s0048_d010* stackOn = 0;
        hkTransform_s0048_d010 blockTransform;
        blockTransform = rb->getRigidMotion()->getTransform();
        hkRootCdPoint_s0048_d010 hit(collector.getHit());
        hkContactPoint_s0048_d010 contact(hit.m_contact);
        hkRigidBody_s0048_d010* hitBody = hkGetRigidBody_s0048_d010(hit.m_rootCollidableB);
        hkVector4_s0048_d010 hitPosition(contact.getPosition());
        hkReal fraction = contact.getDistance();
        hkVector4_s0048_d010 from = ToHkVector4_s0048_d010(position);
        hkVector4_s0048_d010 newPosition;
        newPosition.setInterpolate4(from, input.m_to, fraction);

        const hkShape_s0048_d010* unusedHitShape;
        const hkShape_s0048_d010* hitShape = unusedHitShape;
        hitShape = hitBody->getCollidable()->getShape();
        hkAabb_s0048_d010 hitAabb;
        hitShape->getAabb(hkTransform_s0048_d010::getIdentity(), 0.0f, hitAabb);
        float hitTop = hitAabb.m_max(2) + hitBody->getRigidMotion()->getPosition()(2);
        float newBottom = blockAabb.m_min(2) + newPosition(2);
        float rise = hitTop - originalZ;
        float gap = hkMath::fabs_s0048_d010(newBottom - hitTop);
        if (gap < 0.05f && rise < 0.05f) {
            stackOn = hitBody;
            result = stackOn;
            found = true;
            outPosition = ToSPVector3(newPosition);
        }
    }
    if (!found)
        result = 0;

    model->NumberBlocks();
    rb->setTransform(originalTransform);
    return result;
}




























// @ 0x0048db10
void* HkObj::F_48db10(unsigned flags)
{
    *(void**)this = (void*)0x13ef534;
    if (flags & 1) {
        hkMemory* node = g_hkMemory;
        node->Free(this, 8, 0x1c);
    }
    return this;
}




























// @ 0x0048db60
void HkObj::F_48db60()
{
    mField30 = 0;
    float k = *(float*)0x13ef4f8;
    mArray[3] = k;
    mField4 = *(float*)0x13ef4f8;
}




























// @ 0x0048dbb0
void* HkObj::F_48dbb0(unsigned flags)
{
    *(void**)this = (void*)0x13ef52c;
    *(void**)this = (void*)0x13ef534;
    if (flags & 1) {
        hkMemory* node = g_hkMemory;
        node->Free(this, 8, 0x1c);
    }
    return this;
}




























// @ 0x0048dc50
void* HkObj::F_48dc50(HkObj* src)
{
    *(float*)((char*)this + 0x0) = *(float*)((char*)src + 0x0);
    *(float*)((char*)this + 0x4) = *(float*)((char*)src + 0x4);
    *(float*)((char*)this + 0x8) = *(float*)((char*)src + 0x8);
    *(float*)((char*)this + 0xc) = *(float*)((char*)src + 0xc);
    float* d = (float*)((char*)src + 0x10);
    float* s = (float*)((char*)this + 0x10);
    s[0] = d[0]; s[1] = d[1]; s[2] = d[2]; s[3] = d[3];
    return this;
}




























// @ 0x0048dcd0
namespace SP { namespace EditorUtils {
bool GetMissStackingPosition(cSPEditorBlock_s0048_dcd0* block, BlockList& piles, Vector3Val position, Vector3Val direction, Matrix3_s0048_dcd0 orientation, cSPVector3_s0048_dcd0* outPosition)
{
    (void)orientation;
    cSPEditorModel_s0048_dcd0* model = block->mEditorModel;
    int noParent = 0;
    int filterInfo = 1;
    model->NumberBlocks();
    PrepareBlockForStacking(block, piles, noParent, filterInfo, 1);
    model->GetPhysicsWorld()->SetFloorFilter(filterInfo);

    hkClosestCdPointCollector_s0048_dcd0 collector;
    collector.resetInline();
    hkLinearCastInput_s0048_dcd0 input;

    float top = model->GetMaxHeight();
    float span = top - model->GetMinHeight();
    float grid = model->GetGridSize();
    const float& extra = Max(grid, span);
    float distance = VectorLength(position) + extra;
    cSPVector3_s0048_dcd0 target = position + distance * direction;
    float tmp[4];
    input.m_to = *(hkVector4_s0048_dcd0*)F_48e510(tmp, (Vec4T&)target);

    bool found = false;
    if (block != 0) {
        hkRigidBody_s0048_dcd0* rb = block->mpRigidBody;
        if (rb != 0) {
            hkRigidBody_s0048_dcd0* rb2 = block->mpRigidBody;
            hkMotion_s0048_dcd0* motion = rb2->getRigidMotion();
            hkQuaternion_s0048_dcd0 savedRotation(motion->getRotation());

            Matrix3_s0048_dcd0 neutral = block->GetNeutralOrientation(direction);
            hkRotation_s0048_dcd0 rotation;
            ToHkRotation(neutral, rotation);
            hkTransform_s0048_dcd0 castTransform;
            castTransform = rb->getRigidMotion()->getTransform();
            castTransform.setRotation(rotation);
            rb->setTransform(castTransform);

            hkVector4_s0048_dcd0 start(position[0], position[1], position[2], 0.0f);
            rb->setPosition(start);

            hkRigidBody_s0048_dcd0* body = block->mpRigidBody;
            model->GetPhysicsWorld()->World()->linearCast(body->getCollidable(), input, collector, 0);

            bool hit = collector.hasHit();
            if (hit) {
                hkRigidBody_s0048_dcd0* hitBody = hkGetRigidBody_s0048_dcd0(collector.getHit().m_rootCollidableB);
                if (hitBody != model->GetPhysicsWorld()->GetGroundBody()) {
                    float fraction = collector.getHit().m_contact.getDistance();
                    hkMotion_s0048_dcd0* m = block->mpRigidBody->getRigidMotion();
                    const hkVector4_s0048_dcd0& cur = m->getPosition();
                    hkVector4_s0048_dcd0 blended;
                    blended.setInterpolate4(cur, input.m_to, fraction);
                    *outPosition = ToSPVector3_s0048_dcd0(blended);
                    found = true;
                }
            }
            rb->setRotation(savedRotation);
        }
    }
    model->NumberBlocks();
    model->GetPhysicsWorld()->SetDefaultFloorFilter();
    model->GetPhysicsWorld()->UpdateCollisionFilters();
    return found;
}
}}  // namespace SP::EditorUtils



























// @ 0x0048e510
float* F_48e510(float* out, Vec4T& src)
{
    float z = src[0];
    float x = src[1];
    float y = src[2];
    out[0] = z;
    out[1] = x;
    out[2] = y;
    out[3] = 0.0f;
    return out;
}



























// @ 0x0048e590
float F_48e590(Block_s0048_e590* self, BlockList_s0048_e590* blocks, Vector3_s0048_e590* out, float scale)
{
    Matrix3_s0048_e590 xform(kIdentity33);
    RwVector3 origin(kZero3);
    if (self->GetParent()) {
        Parent* parent = self->GetParent();
        xform = parent->mRotation;
        parent = self->GetParent();
        origin = *(RwVector3*)&parent->mOffset;
    }
    Vector3_s0048_e590 rel = (self->mPosition - origin) * Transposed(xform);
    *out = self->mPosition;

    bool lowAngle = false;
    if (self->mFlags.test(30) && self->GetParent() == 0)
        lowAngle = true;
    bool haveBlocks = self->mFlags.test(53) && !blocks->empty();
    if (!haveBlocks && !lowAngle)
        return -1.0f;

    float bestScore = -1.0f;
    float lenZ = -1.0f;
    Vector3_s0048_e590 resultPos;
    Vector3_s0048_e590 zOnly;

    CandVec cands((AllocTag()));
    for (int i = 0, n = blocks->size(); i < n; ++i) {
        Block_s0048_e590* blk = (Block_s0048_e590*)*blocks->at(i);
        Vector3_s0048_e590 candRel = (blk->mPosition - origin) * Transposed(xform);
        float dx = candRel[0] - rel[0];
        float dy = candRel[1] - rel[1];
        bool hit = false;
        Vector3_s0048_e590 tgt = rel;
        float adx = Abs_s0048_e590(dx);
        if (adx < 0.2f * scale) {
            tgt[0] += dx;
            hit = true;
        }
        float ady = Abs_s0048_e590(dy);
        if (ady < 0.2f * scale) {
            tgt[1] += dy;
            hit = true;
        }
        if (hit) {
            Candidate c;
            c.score = 0.0f;
            Vector3_s0048_e590 a = tgt - rel;
            Vector3_s0048_e590 b = candRel - rel;
            c.score = VectorLength(a) * VectorLength(b);
            c.pos = tgt;
            cands.push_back(c);
        }
    }

    if (!cands.empty()) {
        float best = FLT_MAX;
        Vector3_s0048_e590 bestPos = rel;
        for (int j = 0, m = (int)(cands.mpEnd - cands.mpBegin); j < m; ++j) {
            if (best > cands.mpBegin[j].score) {
                best = cands.mpBegin[j].score;
                bestPos = cands.mpBegin[j].pos;
            }
        }
        resultPos = (bestPos * xform) + origin;
        bestScore = best;
    }

    if (lowAngle) {
        Vector3_s0048_e590 w = self->mPosition;
        w[2] = 0.0f;
        float thr = self->mpSource->Get() * 0.04f * scale;
        if (VectorLength(w) < thr) {
            w = self->mPosition;
            w[0] = 0.0f;
            w[1] = 0.0f;
            zOnly = w;
            lenZ = VectorLength(w);
        }
    }

    if (lenZ == -1.0f && bestScore == -1.0f)
        return -1.0f;
    if (lenZ != -1.0f) {
        *out = zOnly;
        return lenZ;
    }
    *out = resultPos;
    return bestScore;
}


























// @ 0x0048ef30
float GetLateralAlignmentPosition(cSPEditorBlock_s0048_ef30* self, BlockList_s0048_ef30* list, Vector3_s0048_ef30* outPos, Matrix3_s0048_ef30* outBasis, float k)
{
    Vector3_s0048_ef30 pos(self->mPosition);
    *outPos = pos;
    *outBasis = self->mOrientation;
    if (list->empty())
        return -1.0f;

    Vector3_s0048_ef30 center;
    self->GetBBox(0, 0, 0).GetCenter(center);
    center[1] = self->mPosition[1];
    Vector3_s0048_ef30 lat(self->mOrientation[1]);
    lat[2] = 0.0f;
    lat = Normalize(lat);
    CandVec_s0048_ef30 cands((AllocTag()));
    for (int i = 0, n = list->size(); i < n; ++i) {
        cSPEditorBlock_s0048_ef30* other = (*list)[i];
        Vector3_s0048_ef30 center2;
        other->GetBBox(0, 0, 0).GetCenter(center2);
        center2[1] = (*list)[i]->mPosition[1];
        Matrix3_s0048_ef30 m((*list)[i]->mOrientation);
        Vector3_s0048_ef30 rel = (center - center2) * Inverse(m);
        float off = rel[0];
        Vector3_s0048_ef30 axis2(m[1]);
        axis2[2] = 0.0f;
        axis2 = Normalize(axis2);
        float dot = lat.x * axis2.x + lat.y * axis2.y + lat.z * axis2.z;
        Vector3_s0048_ef30 d2(center2);
        d2[0] = d2[0] - off;
        if (0.95 < dot) {
            if (0.2f * k > Abs_s0048_ef30(off)) {
                Candidate_s0048_ef30 cand;
                cand.score = 0.0f;
                PosRot b;
                Vector3_s0048_ef30 v3 = center2 - center;
                cand.score = VectorLength(v3) * Abs_s0048_ef30(off) * dot;
                Vector3_s0048_ef30 v4(rel);
                v4[0] = v4[0] - off;
                v4 = v4 * m;
                v4 += center2;
                Transform xf;
                xf.SetRotation(self->mOrientation);
                b.mPos = v4;
                if (dot != 1.0f) {
                    float ang = (float)acos(dot);
                    if (!IsNaN(ang))
                        xf.PreRotate(g_UpAxis, ang);
                }
                b.mRot = xf.mRot;
                cand.pr = b;
                cands.push_back(cand);
            }
        }
    }
    if (cands.empty()) {
        return -1.0f;
    } else {
        float best = kFloatMax;
        PosRot bestPr;
        bestPr.mPos = pos;
        bestPr.mRot = self->mOrientation;
        for (int i = 0, n = cands.size(); i < n; ++i) {
            if (best > cands[i].score) {
                best = cands[i].score;
                bestPr = cands[i].pr;
            }
        }
        *outBasis = AlignBasis(Matrix3_s0048_ef30(self->mOrientation), bestPr.mRot[1], bestPr.mRot[2]);
        *outPos = bestPr.mPos;
        return best;
    }
}

























// @ 0x0048f790
void UpdateSymmetryRec(cSPEditorBlock_s0048_ef30* block, int sign)
{
    if (block->mpEditorModel != 0) {
        if (block->mpEditorModel->IsActive() && block != 0 && block->mSymmetricBlock == 0) {
            if (!block->mFlags.test(0x39)) {
                cSPEditorBlock_s0048_ef30* t14 = block->Split(1);                     // sym
                t14->Func453500(!block->Func453520());
                block->SetSymmetricBlock(t14);
                t14->SetSymmetricBlock(block);
                block->SetAsymmetricBlock(t14);
                t14->SetAsymmetricBlock(block);
                block->SetPosition(block->mPosition, 0);
                block->SetUserOrientation(block->mUserOrientation);
                block->SetOrientation(block->mOrientation, 0);
                t14->SetBaseJointScale(-2);
                block->mpEditorModel->AddBlock(t14, 1);
                block->SetBaseJointScale(sign);
                t14->SetBaseJointScale(-sign);
                if (block->mParentBlock != 0) {
                    block->mpEditorModel->SetColliding(0);
                    block->mParentBlock->LinkChild(t14);
                    block->mpEditorModel->SetColliding(1);
                }
                if (block->mSymmetricBlock != 0) {
                    ChildList* len = &block->mChildren;
                    PtrVec v33(len->size());                               // copy of the child pointers
                    for (int p38 = 0, p17 = len->size(); p38 < p17; ++p38)
                        v33[p38] = (*len)[p38];
                    BlockRefVec n40;                         // blocks whose symmetric partner must be linked
                    for (int p38 = 0, p17 = (int)(v33.mpEnd - v33.mpBegin); p38 < p17; ++p38) {
                        int t40 = v33[p38]->CalculateSymmetrySign();       // cs
                        bool t32 = (t40 == sign) || (t40 == 0 && sign == -1);   // match
                        if (v33[p38]->mSymmetricBlock == 0) {
                            UpdateSymmetryRec(v33[p38], sign);
                            if (v33[p38]->mSymmetricBlock != 0 && t32)
                                n40.push_back(AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>(v33[p38]->mSymmetricBlock));
                        }
                        if (!t32)
                            n40.push_back(AutoRefCount_s0048_ef30<cSPEditorBlock_s0048_ef30>(v33[p38]));
                    }
                    block->mpEditorModel->SetColliding(0);
                    if (block->mSymmetricBlock != 0) {
                        for (int p38 = 0, p17 = n40.size(); p38 < p17; ++p38)
                            block->mSymmetricBlock->LinkChild(n40[p38]);
                    }
                    block->mpEditorModel->SetColliding(1);
                }
                ChildList* tmp = &block->mChildren;
                for (int p38 = 0, p17 = tmp->size(); p38 < p17; ++p38)
                    UpdateSymmetryRec((*tmp)[p38], sign);
            }
        }
    }
}

























// @ 0x0048fde0
void FUN_0048fde0(cSPEditorBlock* block)
{
    if (block == 0)
        return;
    if (block->Test() != 0)
        return;
    void** begin = block->vecBegin;
    void** end = block->vecEnd;
    for (int i = 0; i < (int)(end - begin); ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)begin[i];
        Tracker* t = child->tracker;
        if (t != 0 && t->field33c == 0) {
            block->F(t);
            Vector3 a, b;
            t->GetOffsetA(&a, 1);
            t->GetOffsetB(&b, 1);
            t->Place();
        } else {
            FUN_0048fde0(child);
        }
    }
}
















// @ 0x0048fee0
float FUN_0048fee0(cSPEditorBlock* p, ModelType* model, Vector3* out, float scale)
{
    Vector3 tmp(p->position);
    *out = tmp;
    if (model->GetResourceTypeX())
        return -1.0f;
    if (((p->bits >> 0x1b) & 1) == 0)
        return -1.0f;

    BoundingBox bb1;
    Vector3 extra;
    BoundingBox* r = p->GetBBox(&bb1, 0, 0, 0, &extra);
    Vector3 ctr = BoundingBox_GetCenter(r);
    char arr[0x20];
    SomeCtor(arr, &ctr);

    void** mbegin = model->begin;
    void** mend = model->end;
    for (int i = 0; i < (int)(mend - mbegin); ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)mbegin[i];
        BoundingBox bb2;
        Vector3 extra2;
        BoundingBox* r2 = child->GetBBox(&bb2, 0, 0, 0, &extra2);
        Vector3 c2 = BoundingBox_GetCenter(r2);
        float dy = c2.z - extra.z;
        Vector3 v(c2);
        v.z = v.z - dy;
        float ady = dy < 0 ? -dy : dy;
        if (0.2f * scale > ady) {
            Vector3 d;
            Vector3_Sub(&d, &c2, &ctr);
            float len = VectorLength(&d);
            float f = len * ady;
            Vector3 q(tmp);
            q.z = q.z + dy;
            SomePush(arr, &f);
            (void)q;
        }
    }
    SomeMethod(arr);
    if (SomeMethod(arr))
        SomeDtor(arr);
    return -1.0f;
}
















// @ 0x004902c0
bool FUN_004902c0(cSPEditorBlock* a, cSPEditorBlock* b)
{
    if (b == 0)
        return false;
    BoundingBox bbB, bbA;
    b->GetBBox(&bbB, 0, 0, 0);
    a->GetBBox(&bbA, 0, 0, 0);
    ExpandBy(&bbB, 1.1f);
    return bbB.Intersects(bbA);
}
















// @ 0x00490330
bool BoundingBox::Intersects(const BoundingBox& b) const
{
    int r;
    if (mx.x < b.mn.x || b.mx.x < mn.x ||
        mx.y < b.mn.y || b.mx.y < mn.y ||
        mx.z < b.mn.z || b.mx.z < mn.z)
        r = 0;
    else
        r = 1;
    return r;
}
















// @ 0x00490420
bool FUN_00490420(cSPEditorBlock* a, cSPEditorBlock* b, int type)
{
    if (type == 0x1b || type == 0x1a || type == 0x35) {
        int p30 = b->field33c;
        int t29 = a->field33c;
        if (p30 == t29) {
            return true;
        } else {
            return false;
        }
    } else if (type == 0x1c || type == 0x1d) {
        int x = a->field33c;
        if (b == (cSPEditorBlock*)x) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}
















// @ 0x004904a0
void FUN_004904a0(cSPEditorBlock* self, void** vec, PtrBag* bag, int type)
{
    if (self->mgr == 0)
        return;
    SubMgr* mgr = self->mgr;
    for (int i = 0, n = mgr->Count(); i < n; ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)mgr->Get(i);
        if (child == self)
            continue;
        void** it = (void**)*vec;
        void** end = (void**)vec[1];
        while (it != end && *it != child)
            ++it;
        if (it == end) {
            if (self->F1(child, type) && FUN_00490420(self, child, type)) {
                cSPEditorBlock* tmp = child;
                if (tmp)
                    ((IRefCounted*)tmp)->AddRef();
                bag->Insert((void**)&tmp);
                if (tmp)
                    ((IRefCounted*)tmp)->Release();
            }
        }
    }
}
















// @ 0x004905d0
void FUN_004905d0(cSPEditorBlock* self, void** vec, PtrBag* bag)
{
    if (self->mgr == 0)
        return;
    SubMgr* mgr = self->mgr;
    for (int i = 0, n = mgr->Count(); i < n; ++i) {
        cSPEditorBlock* child = (cSPEditorBlock*)mgr->Get(i);
        if (child == self)
            continue;
        void** it = (void**)*vec;
        void** end = (void**)vec[1];
        while (it != end && *it != child)
            ++it;
        if (it == end) {
            if (self->F2(child)) {
                cSPEditorBlock* tmp = child;
                if (tmp)
                    ((IRefCounted*)tmp)->AddRef();
                bag->Insert((void**)&tmp);
                if (tmp)
                    ((IRefCounted*)tmp)->Release();
            }
        }
    }
}
















// @ 0x004906e0
Matrix3_s0048_fde0* FUN_004906e0(Matrix3_s0048_fde0* out, Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4)
{
    Vector3 n;
    Cross(&n, &v3, &v4);
    Vector3_Normalize(&n, &n);
    float d = v0.x * n.x + v0.y * n.y + v0.z * n.z;
    float ad = d < 0 ? -d : d;
    if (ad > 1.5258789e-05f) {
        Vector3 u, w, x;
        FUN_004909d0(&u, &n, &v1);
        Vector3_Normalize(&u, &u);
        FUN_004909d0(&w, &n, &v2);
        Vector3_Normalize(&w, &w);
        Cross(&x, &u, &w);
        Vector3_Normalize(&x, &x);
        v0 = x;
        v1 = u;
        v2 = w;
        out->Assign(&v0);
    } else {
        Vector3 p;
        FUN_004909d0(&p, &n, &v1);
        Vector3_Normalize(&p, &p);
        float c = p.x * v0.x + p.y * v0.y + p.z * v0.z;
        if (c < 0.0f)
            c = 0.0f;
        if (c > 1.0f)
            c = 1.0f;
        float ang = Acos(c);
        char tf[0x28];
        TransformCtor(tf);
        Vector3 arr[3];
        arr[0] = v0;
        arr[1] = v1;
        arr[2] = v2;
        *(uint16_t*)(tf + 0) = *(uint16_t*)(tf + 0) | 2;
        *(uint16_t*)(tf + 2) = *(uint16_t*)(tf + 2) + 1;
        TransformSetAngleAxis(tf, ang, &v1);
        out->Assign(&arr[0]);
    }
    return out;
}
















// @ 0x004909d0
Vector3* FUN_004909d0(Vector3* out, const Vector3* a, const Vector3* b)
{
    float p30 = a->Dot(*b);
    Vector3 t29;
    Vector3 n12;
    Vector3* z = Vector3_Sub(&n12, a, Vector3_Scale(&t29, &p30, b));
    *out = *z;
    return out;
}
















// @ 0x00490a70
float GetAlignmentPosition(cSPEditorBlock_s0049_0a70* self, Mgr* mgr, Vec3 v, Matrix3 m, RwVec3* outPos, Matrix3* outBasis, bool* outFlag, uint8_t flag, Matrix3 m2)
{
    if (self != 0) {
    float t4 = 1.2f;
    RwVec3 size((RwVec3&)self->mPosition);
    float value = -1.0f;
    bool v35 = false;
    Vec3 pNode;
    value = FUN_00491b40(self, mgr, v, m2, &pNode, &v35, 1, t4);
    RwVec3 dst(size);
    Matrix3 hi(m);
    float t38 = -1.0f;
    float t23 = -1.0f;
    EdList p18;
    FUN_004904a0(self, mgr, &p18, 0x1b);
    float p40 = -1.0f;
    Vec3 p35;
    p40 = FUN_0048fee0(self, &p18, &p35, t4);
    Vec3 t13(size);
    Matrix3 n39(m);
    float idx = -1.0f;
    EdList n16;
    FUN_004904a0(self, mgr, &n16, 0x1a);
    idx = GetLateralAlignmentPosition(self, &n16, &t13, &n39, t4);
    float t34 = -1.0f;
    EdList u;
    FUN_004904a0(self, mgr, &u, 0x35);
    float bucket = self->TestFlag(8) ? 10.0f : 1.2f;
    Vec3 p37;
    t34 = GetLowAngleOffset(self, &u, &p37, t4 * bucket);
    Vec3 t29(size);
    Matrix3 t16(m);
    float v25 = -1.0f;
    int n23 = -2;
    self->FUN_0044e7c0(n23);
    v25 = FUN_00492e70(self, &t29, &t16, &n23, t4, flag);

    if (p40 != -1.0f || value != -1.0f) {
        if (p40 == -1.0f) {
            dst.z = pNode[2];
            t38 = value;
            *outFlag = v35;
        } else if (value == -1.0f) {
            dst.z = p35[2];
            t38 = p40;
        } else if (value > p40) {
            dst.z = p35[2];
            t38 = p40;
        } else {
            dst.z = pNode[2];
            t38 = value;
            *outFlag = v35;
        }
    }
    if (idx != -1.0f || v25 != -1.0f || t34 != -1.0f) {
        if (t34 != -1.0f) {
            dst.y = p37[1];
            dst.x = p37[0];
            t23 = t34;
        }
        if (idx == -1.0f && v25 != -1.0f) {
            dst.y = t29[1];
            dst.x = t29[0];
            self->FUN_0044e7c0(n23);
            hi = t16;
            t23 = v25;
        } else if (v25 == -1.0f && idx != -1.0f) {
            dst.y = t13[1];
            dst.x = t13[0];
            hi = n39;
            t23 = idx;
        } else if (idx != -1.0f && v25 != -1.0f) {
            if (v25 > idx) {
                dst.y = t13[1];
                dst.x = t13[0];
                hi = n39;
                t23 = idx;
            } else {
                dst.y = t29[1];
                dst.x = t29[0];
                hi = t16;
                t23 = v25;
            }
        }
    }
    float p21 = -1.0f;
    if (t23 != -1.0f || t38 != -1.0f) {
        if (t23 == -1.0f)
            p21 = t38;
        else if (t38 == -1.0f)
            p21 = t23;
        else
            p21 = t23 + t38;
    }
    *outPos = dst;
    *outBasis = hi;
    ScratchSlots<15>();
    return p21;
    }
    return -1.0f;
}

















































// @ 0x00491350
int CountPileWeight(cSPEditorBlock_s0049_0a70* self, int mode)
{
    int n8 = 0;
    BlockVec list((AllocTag()));
    VisitedVec v20((AllocTag()));
    ScratchSlots<2>();
    BuildPileList(self, &list, 0);
    list.push_back(AutoRefCount<cSPEditorBlock_s0049_0a70>(self));
    if (self->GetLink3e0() != 0) {
        BuildPileList(self->GetLink3e0(), &list, 0);
        list.push_back(AutoRefCount<cSPEditorBlock_s0049_0a70>(self->GetLink3e0()));
    }
    ScratchSlots<2>();
    for (uint32_t i = 0; i < list.size(); ++i) {
        if (find(v20.begin(), v20.end(), list[i]) != v20.end())
            continue;
        if (list[i]->TestFlag(0x39)) {
            if (list[i]->GetLink3e4() != 0) {
                if (mode == 2) {
                    n8 += list[i]->GetWeight();
                    v20.push_back(AutoRefCount<cSPEditorBlock_s0049_0a70>(list[i]->GetLink3e4()));
                    ScratchSlots<2>();
                } else if (mode == 1) {
                    if (find(list.begin(), list.end(), list[i]->GetLink3e4()) != list.end()) {
                        n8 += list[i]->GetWeight();
                        v20.push_back(AutoRefCount<cSPEditorBlock_s0049_0a70>(list[i]->GetLink3e4()));
                        ScratchSlots<2>();
                    }
                }
            } else if (mode == 1) {
                n8 += list[i]->GetWeight();
            } else if (mode == 2) {
                n8 = n8;
            }
        } else {
            n8 += list[i]->GetWeight();
            if (list[i]->GetLink3e0() != 0)
                v20.push_back(AutoRefCount<cSPEditorBlock_s0049_0a70>(list[i]->GetLink3e0()));
        }
    }
    ScratchSlots<2>();
    return n8;
}
















































// @ 0x00491900
int FUN_00491900(Vec* p1, Vec* p2)
{
    p2->Clear(p2->begin, p2->end);
    int n = (int)(p1->end - p1->begin);
    for (int i = 0; i < n; ++i) {
        cSPEditorBlock_s0049_1900* e = (cSPEditorBlock_s0049_1900*)p1->begin[i];
        if (e != 0) {
            if (e->tracker == 0 && e->field3e4 == 0) {
                cSPEditorBlock_s0049_1900* tmp = e;
                if (tmp)
                    ((IRefCounted*)tmp)->AddRef();
                p2->Insert((void**)&tmp);
                if (tmp)
                    ((IRefCounted*)tmp)->Release();
            } else if (e->tracker == 0) {
                if (e->field3e4 != 0) {
                    void* target = e->field3e4;
                    void** it = p2->begin;
                    void** end = p2->end;
                    while (it != end && *it != target)
                        ++it;
                    if (it == end) {
                        cSPEditorBlock_s0049_1900* tmp = e;
                        if (tmp)
                            ((IRefCounted*)tmp)->AddRef();
                        p2->Insert((void**)&tmp);
                        if (tmp)
                            ((IRefCounted*)tmp)->Release();
                    }
                }
            } else {
                void* target = e->tracker;
                void** it = p2->begin;
                void** end = p2->end;
                while (it != end && *it != target)
                    ++it;
                if (it == end) {
                    cSPEditorBlock_s0049_1900* tmp = e;
                    if (tmp)
                        ((IRefCounted*)tmp)->AddRef();
                    p2->Insert((void**)&tmp);
                    if (tmp)
                        ((IRefCounted*)tmp)->Release();
                }
            }
        }
    }
    return (int)(p2->end - p2->begin);
}















































// @ 0x004928d0
void FUN_004928d0(cSPEditorBlock_s0049_28d0* p, int a, int b, int c)
{
    if (p == 0)
        return;
    BoundingBox_s0049_28d0 bb;
    p->GetBBox(&bb, 0, 0, 0);
    (void)a;
    (void)b;
    (void)c;
}



















// @ 0x00492de0
bool FUN_00492de0(cSPEditorBlock_s0049_28d0* p)
{
    cSPEditorBlock_s0049_28d0* t1 = (cSPEditorBlock_s0049_28d0*)p->tracker;
    if (t1 == 0)
        return false;
    cSPEditorBlock_s0049_28d0* t2 = (cSPEditorBlock_s0049_28d0*)p->tracker;
    BoundingBox_s0049_28d0 bb;
    t2->GetBBox(&bb, 0, 0, 0);
    float dz = bb.mx[2] - p->position[2];
    float ad = (float)fabs(dz);
    if (g_492de0_limit > ad)
        return true;
    return false;
}



















// @ 0x00492e70
float FUN_00492e70(cSPEditorBlock2* p, Vec3W* outPos, Matrix3_s0049_28d0* outRot, int* outIdx, float scale, char flag)
{
    cSPEditorBlock2* t1 = p->parent;
    if (t1 != 0) {
    cSPEditorBlock2* t2 = p->parent;
    cSPEditorBlock2* blk = t2;
    Vec3O pos(*(const Vec3O*)&p->position);
    Matrix3_s0049_28d0 rot(p->rotation);
    BBox2 bb;
    blk->GetBBox(&bb, 0, 0, 0);
    Vec3W center;
    blk->FUN_0043d240(&center, 0);
    Vec3O a(*(const Vec3O*)&bb.mn);
    Vec3O b(*(const Vec3O*)&bb.mx);
    float dx = b[0] - a[0];
    float dy = b[1] - a[1];
    float len = (float)sqrt(dy * dy + dx * dx);
    float scaled = len * 0.08f * scale;

    Matrix3_s0049_28d0 invRot;
    Vec3W tSub, tMul;
    Vec3W vl(*Vec_MulMat(&tMul, Vec_Sub(&tSub, &pos, &blk->position), Mat_Inverse(&invRot, &blk->rotation)));
    float ex = vl[0] - center[0];
    float ey = vl[1] - center[1];
    float dist = (float)sqrt(ey * ey + ex * ex);

    Vec3W best(*(Vec3W*)&pos);
    float bestD = -1.0f;
    if (flag && scaled > dist) {
        vl[0] = center[0];
        vl[1] = center[1];
        Vec3W tMul2, tAdd;
        best = *Vec_Add(&tAdd, Vec_MulMat(&tMul2, &vl, &blk->rotation), &blk->position);
        bestD = dist;
    }

    float second = -1.0f;
    Vec3W cand(*(Vec3W*)&pos);
    Matrix3_s0049_28d0 candRot(rot);
    int n = blk->FUN_0044e800();
    if (n > 0) {
        int idx = blk->FUN_0044d9e0(*(Vec3W*)&pos, scaled * 0.25f);
        if (idx != -1) {
            Snap_004928d0(blk, *(Vec3W*)&pos, rot, &cand, &candRot, idx);
            Vec3W tDiff;
            Vec3W diff(*Vec_Sub(&tDiff, (Vec3W*)&pos, &cand));
            second = VectorLength(&diff);
            *outIdx = idx;
        }
    }

    if (p->TestBit(0x1c) && bestD != -1.0f && p->FUN_00438440(p->parent, 0x1c)) {
        *(Vec3P*)outPos = *(Vec3P*)&best;
        *outIdx = -1;
        return bestD;
    }
    if (p->FUN_00438440(p->parent, 0x1d) && p->TestBit(0x1d) && second != -1.0f) {
        *(Vec3P*)outPos = *(Vec3P*)&cand;
        *outRot = candRot;
        return second;
    }
    return -1.0f;
    }
    return -1.0f;
}



















// @ 0x004934d0
void FUN_004934d0(int p)
{
    (void)p;
}



















// @ 0x004935f0
Vector3_s0049_28d0 S935::Sub() const
{
    Vector3_s0049_28d0 p30;
    Vector3_s0049_28d0* t29 = Vector3_Sub_s0049_28d0(&p30, &b, &a);
    return *t29;
}



















// @ 0x00493640
int ClassifyAgainstSymmetryPlane(V3* p, float width, float zmin, float zmax, Basis* out)
{
    bool p30 = false;
    int p18 = 3;
    if (zmin > (*p)[2]) {
        (*p)[2] = zmin;
        p30 = true;
        p18 = 2;
        if (out) {
            V3 t25;
            if ((*p)[0] != 0.0f || (*p)[1] != 0.0f) {
                t25 = -*p;
                t25[2] = 0.0f;
                Scratch<5>();
                t25 = Normalize(t25);
            } else {
                t25 = -kVecB;
            }
            V3 v16;
            v16 = kVecA;
            V3 chunk;
            chunk = Cross(v16, t25);
            (*out)[0] = chunk;
            (*out)[1] = v16;
            (*out)[2] = t25;
        }
    }
    if ((*p)[2] > zmax) {
        (*p)[2] = zmax;
        p30 = true;
        p18 = 0;
        if (out) {
            V3 v13;
            if ((*p)[0] != 0.0f || (*p)[1] != 0.0f) {
                v13 = -*p;
                v13[2] = 0.0f;
                Scratch<5>();
                v13 = Normalize(v13);
            } else {
                v13 = kVecB;
            }
            V3 v37;
            v37 = -kVecA;
            V3 buf;
            buf = Cross(v37, v13);
            (*out)[0] = buf;
            (*out)[1] = v37;
            (*out)[2] = v13;
        }
    }
    V3 n31(p->x, p->y, 0.0f);
    float p4 = VectorLength(&n31);
    float v1 = width / 2.0f;
    if (p4 > v1) {
        V3 v26;
        Scratch<6>();
        v26 = Normalize(n31) * v1;
        p->SetX(v26.x);
        p->SetY(v26.y);
        p30 = true;
        p18 = 1;
        if (out) {
            V3 hash;
            if ((*p)[0] != 0.0f || (*p)[1] != 0.0f) {
                hash = -*p;
                hash[2] = 0.0f;
                Scratch<5>();
                hash = Normalize(hash);
            } else {
                hash = kVecB;
            }
            V3 v34;
            v34 = kVecA;
            V3 mem;
            mem = Cross(hash, v34);
            (*out)[0] = mem;
            (*out)[1] = hash;
            (*out)[2] = v34;
        }
    }
    (void)p30;
    return p18;
}




















// @ 0x00494270
void* FUN_00494270(void* a, void* b)
{
    unsigned hole[11];
    (void)hole;
    FUN_00493ce0(a, b, *(Matrix3_s0049_3640*)((char*)b + 0xa8));
    return a;
}




















// @ 0x004942b0
namespace SP { namespace EditorUtils {
bool GetRotationAndPositionBasedOnBehavior(cSPEditorBlock_s0049_42b0* block, cSPVector3_s0049_42b0& pos, cSPMatrix3_s0049_42b0& orient, cSPVector3_s0049_42b0 dir, bool bAlignToParent, bool bSnapToSymmetry)
{
    bool result = false;
    cSPMatrix3_s0049_42b0 startOrient(orient);
    bool bSymmetry = block->GetEditorModel()->IsSymmetryEnabled();
    if (!bSymmetry)
        bAlignToParent = false;
    bool bSymmetricSnaps = block->GetSymmetricBlock() && block->GetSymmetricBlock()->mFlags.test(0x37);
    bSnapToSymmetry = bSnapToSymmetry && bSymmetricSnaps;
    bool bAlignUp = (block->mFlags.test(0x11) && !bSnapToSymmetry) ||
                    (block->mFlags.test(0x32) && bSnapToSymmetry);

    // Snap onto the symmetric block's snap axis.
    if (block->GetSymmetricBlock() && bSnapToSymmetry && block->GetSnapType() != -1) {
        orient = GetSnapOrientation(block->GetSymmetricBlock(), dir);
        if (block->GetSnapType() != -2) {
            cSPEditorBlock_s0049_42b0* sym = block->GetSymmetricBlock();
            cSPEditorSnapVector_s0049_42b0 axis = sym->GetSnapAxis(block->GetSnapType());
            cSPVector3_s0049_42b0 normal;
            normal = axis.mNormal * block->GetSymmetricBlock()->mOrientation;
            cSPEditorBlock_s0049_42b0* sym2 = block->GetSymmetricBlock();
            orient = RotateOrientation(orient, normal, sym2->mOrientation[2]);
        }
        result = true;
    }

    // Keep the block upright (Z up) with its forward axis horizontal.
    if (block->GetSymmetricBlock() && bAlignUp) {
        if ((bSymmetry && block->GetSymmetryIndex() == 0) || bAlignToParent) {
            orient = GetSymmetricOrientation(block, orient);
            result = true;
        } else {
            cSPVector3_s0049_42b0 forward;
            forward = orient[1];
            cSPVector3_s0049_42b0 right;
            right = orient[0];
            forward[2] = 0.0f;
            forward = normalized_safe(forward);
            cSPVector3_s0049_42b0 up = normalized_safe(Cross(right, forward));
            if (up.x * up.x + up.y * up.y + up.z * up.z < 0.9f || IsNAN(up)) {
                cSPMatrix3_s0049_42b0 base(block->mBaseOrientation);
                up = g_ZAxis;
                forward = normalized_safe(Cross(up, right));
            }
            orient[0] = right;
            orient[1] = forward;
            orient[2] = up;
        }
        result = true;
    }

    // Keep the block's right axis on the symmetry axis.
    if (block->mFlags.test(0x13) && block->GetSymmetricBlock()) {
        if ((bSymmetry && block->GetSymmetryIndex() == 0) || bAlignToParent) {
            orient = GetSymmetricOrientation(block, orient);
        } else {
            cSPVector3_s0049_42b0 forward;
            forward = orient[1];
            cSPVector3_s0049_42b0 right(g_SymmetryAxis);
            if (block->GetSymmetryIndex() == -1) {
                float flip = -1.0f;
                right *= flip;
            }
            forward[1] = 0.0f;
            forward = Normalize(forward);
            if (bAlignToParent && (float)fabs(forward[2]) > 0.0f) {
                forward[0] = 0.0f;
                forward = Normalize(forward);
            }
            cSPVector3_s0049_42b0 up = normalized_safe(Cross(right, forward));
            if (up.x * up.x + up.y * up.y + up.z * up.z < 0.9f || IsNAN(up)) {
                up = g_ZAxis;
                forward = normalized_safe(Cross(up, right));
            }
            orient[0] = right;
            orient[1] = forward;
            orient[2] = up;
        }
        result = true;
    }

    // Drop the block down onto whatever lies below it along its forward axis.
    if (block->mFlags.test(0x12) && block->GetSymmetricBlock() &&
        !block->IsPinnedOrLocked(false) && !bSnapToSymmetry) {
        cSPMatrix3_s0049_42b0 m(startOrient);
        cSPVector3_s0049_42b0 forward;
        forward = m[1];
        forward[2] = 0.0f;
        forward = normalized_safe(forward);
        if (forward.x * forward.x + forward.y * forward.y + forward.z * forward.z < 0.9f || IsNAN(forward)) {
            m = block->mBaseOrientation;
            forward = m[1];
            forward[2] = 0.0f;
            forward = normalized_safe(forward);
        }
        if (forward.x * forward.x + forward.y * forward.y + forward.z * forward.z > 0.9f) {
            cSPBoundingBox_s0049_42b0 bbox = block->GetBBox(1, false, false);
            cSPVector3_s0049_42b0 corners[8];
            bbox.GetCorners(corners);
            cSPVector3_s0049_42b0 center;
            center = (corners[0] * 0.5f + corners[1] * 0.5f) * orient + pos;
            if (0.1f > center[2])
                center[2] = 0.1f;
            if (block->GetSymmetricBlock()) {
                cSPBoundingBox_s0049_42b0 symBox = block->GetSymmetricBlock()->GetBBox(0, false, false);
                if (symBox.mMax[2] + 0.1f > center[2])
                    center[2] = symBox.mMax[2] + 0.1f;
            }

            BlockVector ignore;
            {
                EA::AutoRefCount_s0049_42b0<cSPEditorBlock_s0049_42b0> sym(block->GetSymmetricBlock());
                ignore.push_back(sym);
            }
            int level = 4;
            cSPVector3_s0049_42b0 hitPos;
            cSPVector3_s0049_42b0 hitNormal;
            int hitIndex;
            bool bHit;
            cSPEditorBlock_s0049_42b0* hitBlock = PickBlocks(ignore, center - forward * 20.0f, forward,
                                                  hitPos, hitNormal, &hitIndex, bHit, &level);
            if (hitBlock) {
                cSPVector3_s0049_42b0 up;
                up = orient[1];
                float offset = block->mSnapHeightOffset;
                cSPVector3_s0049_42b0 target;
                target = hitPos - up * offset;
                cSPVector3_s0049_42b0 diff = target - center;
                cSPVector3_s0049_42b0 toTarget(diff);
                float along = Dot(toTarget, up);
                if (along < 0.0f) {
                    cSPVector3_s0049_42b0 diff2 = target - center;
                    cSPVector3_s0049_42b0 delta(diff2);
                    float dist = -Length(delta);
                    pos += up * dist;
                    result = true;
                }
            }
        }
    }

    if (bSymmetry && !block->IsSymmetryLocked() &&
        (block->GetSymmetryIndex() == 0 || bAlignToParent) && !result &&
        block->mFlags.test(0) && block->GetSymmetricBlock()) {
        orient = GetSymmetricOrientation(block, orient);
        result = true;
    }

    if (!block->mFlags.test(0) && block->GetSymmetricBlock()) {
        orient = block->mBaseOrientation;
        result = true;
    }
    return result;
}
}}  // namespace SP::EditorUtils












































// @ 0x004956b0
void SettleBlock(cSPEditorBlock_s0049_56b0* block, BlockVec_s0049_56b0* ignore)
{
    ModelRef model(block->GetEditorModel());
    hkWorld_s0049_56b0* world = model->GetPhysicsWorld()->World();
    model->SetCollisionFilter(0);
    world->updateCollisionFilterOnWorld(0, 1);
    cSPVector3_s0049_56b0 start = block->mPosition + Vector3T(0.0f, 0.0f, 0.2f);
    AllCdPointCollector collector;
    hkLinearCastInput_s0049_56b0 input;
    input.m_to = ToHkVector4(start);
    hkRigidBody_s0049_56b0* rb = block->mpRigidBody;
    world->linearCast(rb->getCollidable(), input, collector, 0);
    BlockVec_s0049_56b0 visited((AllocTag()));
    int n = collector.m_size;
    for (int i = 0; i < n; ++i) {
        hkRootCdPoint_s0049_56b0* hit = &collector.m_data[i];
        const hkCollidable_s0049_56b0* hc = hit->m_rootCollidableB;
        hkRigidBody_s0049_56b0* body = hkGetRigidBody(hc);
        if (body->hasProperty(0)) {
            cSPEditorBlock_s0049_56b0* hitBlock = (cSPEditorBlock_s0049_56b0*)body->getProperty(0).getPtr();
            if (hitBlock->FUN_44c030()) {
                if (find_s0049_56b0(visited.begin(), visited.end(), hitBlock) == visited.end()) {
                    bool skip = false;
                    if (model->IsSymmetryEnabled()) {
                        if (block->GetLinkedBlock() == hitBlock) {
                            skip = true;
                        } else if (!ignore->empty()) {
                            for (int j = 0, cnt = ignore->size(); j < cnt; ++j) {
                                if ((*ignore)[j]->GetLinkedBlock() == hitBlock)
                                    skip = true;
                            }
                        }
                    }
                    if (!skip) {
                        cSPEditorBlock_s0049_56b0* blockA = hitBlock;
                        visited.push_back(blockA);
                        if (hitBlock->GetSymmetricBlock() != block) {
                            if (find_s0049_56b0(ignore->begin(), ignore->end(), hitBlock) == ignore->end()) {
                                model->NumberBlocks();
                                int prevFilter = block->GetCollisionFilterInfo();
                                int hitFilter = hitBlock->GetCollisionFilterInfo();
                                block->SetCollisionFilterInfo(hitFilter);
                                hkRigidBody_s0049_56b0* rb2 = block->mpRigidBody;
                                world->updateCollisionFilterOnEntity(rb2, 0, 1);
                                float px = block->mPosition[0];
                                float py = block->mPosition[1];
                                float pz = block->mPosition[2] - 0.2f;
                                hkVector4_s0049_56b0 lowPos(px, py, pz, 0.0f);
                                hkRigidBody_s0049_56b0* rb3 = block->mpRigidBody;
                                rb3->setPosition(lowPos);
                                PenetrationCollector pc;
                                hkCollisionInput_s0049_56b0* ci = world->m_collisionInput;
                                hkRigidBody_s0049_56b0* rb4 = block->mpRigidBody;
                                world->getPenetrations(rb4->getCollidable(), *ci, pc);
                                block->SetPosition(block->mPosition, true);
                                hkBool_s0049_56b0 hitSomething = pc.m_earlyOut;
                                if (!hitSomething) {
                                    cSPEditorBlock_s0049_56b0* blockB = hitBlock;
                                    ignore->push_back(blockB);
                                    BuildPileList(hitBlock, ignore, false);
                                    SettleBlock(hitBlock, ignore);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}






















// @ 0x00495f90
void* D95::Del(unsigned flags)
{
    this->vptr = &g_vtbl_13ef554;
    this->vptr = &g_vtbl_13ef534;
    if (flags & 1) {
        MemMgr* z = g_mem;
        z->Deallocate(this, 8, 0x1c);
    }
    return this;
}






















// @ 0x00495fe0
void* D95fe0::Ctor()
{
    // reconstructed skeleton: vtable stores + inplace-buffer init
    this->vptr = &g_vtbl_13ef55c;
    *(int*)((char*)this + 4) = 0x7f7fffee;
    void** buf = (void**)((char*)this + 0x10);
    buf[0] = (void*)((char*)this + 0x30);
    buf[1] = 0;
    buf[2] = (void*)0x80000008;
    for (int i = 8; i > 0; --i) {
    }
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 4) = 0x7f7fffee;
    return this;
}






















// @ 0x00496090
void* D960::Del(unsigned flags)
{
    this->Dtor();
    if (flags & 1) {
        MemMgr* z = g_mem;
        z->Deallocate(this, 8, 0x1c);
    }
    return this;
}






















// @ 0x004960d0
void D960::Dtor()
{
    this->vptr = &g_vtbl_13ef55c;
    int c = *(int*)((char*)this + 0x18);
    if ((c & 0x80000000) == 0) {
        void* mem = TlsGetValue(*(uint32_t*)&g_tls_slot);
        ((HkThreadMemory*)mem)->DeallocateChunk(*(void**)((char*)this + 0x10),
                                                 (c & 0x3fffffff) * 0x30, 0x14);
    }
    this->vptr = &g_vtbl_13ef534;
}






















// @ 0x00496140
int* D961::Find(int* out, int key)
{
    int i = 0;
    while (true) {
        if (this->count <= i) {
            out[0] = 0;
            out[1] = 0;
            return out;
        }
        if (*(int*)((char*)this->data + i * 0x10) == key)
            break;
        ++i;
    }
    out[0] = *(int*)((char*)this->data + i * 0x10 + 8);
    out[1] = *(int*)((char*)this->data + i * 0x10 + 0xc);
    return out;
}






















// @ 0x004961d0
void FUN_004961d0(char* save, Vec_s0049_56b0* vec)
{
    if (save != 0) {
        *(Vector3_s0049_56b0*)(save + 0x54) = *(Vector3_s0049_56b0*)(save + 0x48);
        for (int k = 0; k < 9; ++k)
            ((float*)(save + 0x84))[k] = ((float*)(save + 0x60))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(save + 0xcc))[k] = ((float*)(save + 0xa8))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(save + 0x114))[k] = ((float*)(save + 0xf0))[k];
    }
    int n = (int)(vec->end - vec->begin);
    for (int i = 0; i < n; ++i) {
        char* b = (char*)vec->begin[i];
        *(Vector3_s0049_56b0*)(b + 0x54) = *(Vector3_s0049_56b0*)(b + 0x48);
        for (int k = 0; k < 9; ++k)
            ((float*)(b + 0x84))[k] = ((float*)(b + 0x60))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(b + 0xcc))[k] = ((float*)(b + 0xa8))[k];
        for (int k = 0; k < 9; ++k)
            ((float*)(b + 0x114))[k] = ((float*)(b + 0xf0))[k];
    }
}






















// @ 0x00496300
void FUN_00496300(void* p, void* a, void* b)
{
    (void)p;
    (void)a;
    (void)b;
}























// @ 0x00496760
void FUN_00496760(void* p, void* a)
{
    (void)p;
    (void)a;
}























// @ 0x00496b60
void FUN_00496b60(HolderA* a, float f)
{
    void* limb = a->Get();
    LimbStructure ls;
    ls.Ctor();
    ls.Init(limb, 0, 0);
    ls.UpdateScaleRange(limb, f);
    ls.F();
    ls.~LimbStructure();
}























// @ 0x00496bb0
int FUN_00496bb0(char* p, float f)
{
    Bone* bone = (Bone*)GetBoneForHandle(p + 100);
    int c = 0;
    if (bone != 0)
        c = (int)bone->Get();
    if (bone != 0 && bone->v4() == 0x50e8e23 && c != 0 &&
        *(int*)(c + 0x3e0) != 0) {
        int t = bone->GetSomething();
        if (t != 0 && p != 0) {
            Vector3_s0049_6300 d;
            Vector3_Sub_s0049_6300(&d, (Vector3_s0049_6300*)(t + 0xc), (Vector3_s0049_6300*)(p + 0xc));
            float len = VectorLength(&d);
            if (len < 0.01f) {
                float s = f >= 0.0f ? 1.0f : -1.0f;
                int n = ((Bone*)c)->Check();
                if (s != (float)n)
                    c = *(int*)(c + 0x3e0);
            }
        }
    }
    return c;
}























// @ 0x00496d30
void FUN_00496d30(EditorBlockRay* self, V3_s0049_6d30 A, V3_s0049_6d30 B, V3_s0049_6d30* out1, V3_s0049_6d30* out2)
{
    float unused = self->mPosition.x;
    float s = Abs((A.z * 0.99f) / B.z);
    V3_s0049_6d30 P = A + B * s;
    V3_s0049_6d30 N = -B;
    V3_s0049_6d30 Q = self->mPosition - A;
    V3_s0049_6d30 R = B * Dot3(&Q, &B) + A;
    RayQuery r1(R, B);
    RayQuery r2(R, N);
    r1.Cast(self, self, R, B);
    r2.Cast(self, self, R, N);
    *out1 = A;
    *out2 = P;
    if (r1.IsHit() && r2.IsHit()) {
        V3_s0049_6d30 Hn = r1.GetPoint() - B * self->GetRadius();
        V3_s0049_6d30 H2 = r2.GetPoint() - N * self->GetRadius();
        float len1 = VectorLength(P - H2);
        float len2 = VectorLength(P - self->mPosition);
        float len3 = VectorLength(A - Hn);
        float len4 = VectorLength(A - self->mPosition);
        *out1 = Hn;
        *out2 = H2;
    }
}










































// @ 0x004973f0
char FUN_004973f0(X973* p, void* mat, float f, char flag)
{
    char result = 0;
    if (p != 0) {
        Matrix3_s0049_6d30 m;
        if (mat == 0) {
            const float* src = (const float*)((char*)p + 0xf0);
            for (int i = 0; i < 9; ++i)
                m.m[i] = src[i];
        } else {
            const float* src = (const float*)mat;
            for (int i = 0; i < 9; ++i)
                m.m[i] = src[i];
        }
        result = 0;
        char r = FUN_0043bd80(p, f, m);
        if (r) {
            if ((p->flags & 1) == 0) {
                result = 1;
            } else {
                if (FUN_004a7e60(p) || flag)
                    result = 1;
            }
        }
    }
    return result;
}









































// @ 0x004974e0
bool FUN_004974e0(X982* p, Vec3O_s0049_74e0 v, Vec3O_s0049_74e0* outHit, bool* outFlag, float tol, char force)
{
    bool r = false;
    *outFlag = true;
    *outHit = v;
    if (p) {
        if (p->FUN_00435c80()) {
            if (!p->GetFlag(0x1f) || !p->Parent()) return false;
            if (!p->Parent()->GetFlag(0x1f)) return false;
            if (p->Parent()->FUN_00435c80()) return false;
        }
        Vec3O_s0049_74e0 cur(v);
        r = false;
        if (p->FUN_0043bd50(cur, tol)) {
            bool ok = true;
            if (p->Parent()) {
                if (!p->Parent()->GetFlag(0xf)) ok = false;
            }
            if (ok) {
                r = true;
                Vec3O_s0049_74e0 d(*(Vec3O_s0049_74e0*)p->dir);
                if (d[0] != 0.0f || d[1] != 0.0f || d[2] != 0.0f) {
                    d[0] = 0.0f;
                    d = normalized_safe(d);
                    if (d.v[0] * d.v[0] + d.v[1] * d.v[1] + d.v[2] * d.v[2] > 0.9f) {
                        bool f2 = p->Parent() != 0;
                        if (p->GetFlag(0x1f) && f2) {
                            if (p->GetFlag(0x20)) f2 = false;
                        }
                        if (f2) {
                            if (p->Parent()->GetFlag(0xa)) {
                                Vec3O_s0049_74e0 t(*(Vec3O_s0049_74e0*)p->dir);
                                Vec3O_s0049_74e0 nrm = Vec_Normalize2(t);
                                float a0 = nrm[0];
                                if (tol * 0.5f > (float)fabs(a0)) {
                                    r = true;
                                    Vector3_s0049_74e0 copy(*(Vector3_s0049_74e0*)&d);
                                    *(Vec3P_s0049_74e0*)p->dir = *(Vec3P_s0049_74e0*)&copy;
                                } else {
                                    r = false;
                                }
                            } else {
                                BlockVector_s0049_74e0 blocks;
                                blocks.reserve(1);
                                {
                                    BlockRef blk(p->Parent());
                                    blocks.push_back(blk);
                                }
                                Vector3_s0049_74e0 start(*(Vector3_s0049_74e0*)&cur);
                                start[0] = 0.0f;
                                Vector3_s0049_74e0 end(start);
                                const float scale = 4.0f;
                                Vector3_s0049_74e0 mulTmp;
                                Vec_AddAssign(&end, Vec_Mul(&mulTmp, &d, &scale));
                                Vector3_s0049_74e0 negTmp;
                                Vector3_s0049_74e0 negd = *Vec_NegateO(&negTmp, &d);
                                bool flag = false;
                                int hitBlock;
                                Vector3_s0049_74e0 hitPos;
                                Vector3_s0049_74e0 hitNormal;
                                int pick = PickBlocks(&blocks, end, negd, &hitPos, &hitNormal, &hitBlock, &flag, 0);
                                if (pick) {
                                    Vector3_s0049_74e0 subTmp;
                                    Vector3_s0049_74e0 dv = *Vec_Sub(&subTmp, &hitPos, &start);
                                    float len = VectorLength(&dv);
                                    if (p->FUN_0043bc70(len, tol)) {
                                        Vector3_s0049_74e0 nn(hitNormal);
                                        *(Vec3P_s0049_74e0*)p->dir = *(Vec3P_s0049_74e0*)&nn;
                                        *(Vec3P_s0049_74e0*)outHit = *(Vec3P_s0049_74e0*)&hitPos;
                                        Vector3_s0049_74e0 negTmp2;
                                        p->MoveTo(hitBlock, hitPos, *Vec_Negate(&negTmp2, &hitNormal), flag);
                                        r = true;
                                    } else {
                                        r = false;
                                    }
                                }
                            }
                        }
                    }
                }
                if (r) {
                    if (p->GetFlag(0)) {
                        if (FUN_004a7e60(p) || force)
                            r = true;
                        else
                            r = false;
                    }
                }
            }
            if (!r) {
                Vector3_s0049_74e0 again(*(Vector3_s0049_74e0*)&cur);
                if (p->FUN_0043bd50(again, 0.2f)) {
                    r = true;
                    *outFlag = false;
                }
            } else {
                *outFlag = true;
            }
        }
    }
    if (r) (*outHit)[0] = 0.0f;
    return r;
}









































// @ 0x00497f20
bool FUN_00497f20(Vector3_s0049_74e0 v, Vec3O_s0049_74e0* out, float step)
{
    DirVector dirs;
    EString name;
    for (float x = -1.0f; x <= 1.0f; x = x + step) {
        for (float y = -1.0f; y <= 1.0f; y = y + step) {
            for (float z = -1.0f; z <= 1.0f; z = z + step) {
                if ((x != 0.0f || y != 0.0f || z != 0.0f) && (x != 1.0f || y != 1.0f || z != 1.0f)) {
                    Vector3_s0049_74e0 t(x, y, z);
                    dirs.push_back(Vec_Normalize(t));
                }
            }
        }
    }
    const float threshold = 0.1f;
    const float vlen = VectorLength(&v);
    Vector3_s0049_74e0 nv = Vec_Normalize(v);
    float best = 10.0f;
    const int n = dirs.size();
    for (int i = 0; i < n; ++i) {
        Vector3_s0049_74e0 subTmp;
        Vector3_s0049_74e0 dv = *Vec_Sub(&subTmp, &nv, &dirs.mpBegin[i]);
        float dlen = VectorLength(&dv);
        if (dlen < threshold) {
            Vector3_s0049_74e0 mulTmp;
            const float vl = vlen;
            new (out) Vec3O_s0049_74e0(*(Vec3O_s0049_74e0*)Vec_Mul(&mulTmp, (Vec3O_s0049_74e0*)&dirs.mpBegin[i], &vl));
            return true;
        }
        if (dlen < best) best = dlen;
    }
    return false;
}









































// @ 0x00498230
void FUN_00498230(int p, char flag)
{
    ((FlagOwner*)p)->SetFlag(0xf, flag);
    int* pv = (int*)(p + 0x340);
    int n = (pv[1] - pv[0]) >> 2;
    for (int i = 0; i < n; ++i) {
        int child;
        int* slot = (int*)(pv[0] + i * 4);
        child = *slot;
        FUN_00498230(child, flag);
    }
}









































// @ 0x004982b0
bool FUN_004982b0(X982* p, char a, float b, char c)
{
    Vector3_s0049_74e0 v(*(Vector3_s0049_74e0*)((char*)p + 0x48));
    Matrix3_s0049_74e0 m1(*(Matrix3_s0049_74e0*)((char*)p + 0xa8));
    Matrix3_s0049_74e0 m2(*(Matrix3_s0049_74e0*)((char*)p + 0xf0));
    bool r = FUN_00498470(p, &v, &m1, &m2, a, b, c, 1);
    if (r) {
        p->FUN_0043ffa0(m2);
        RepinBlockToTorso(p, v, m1, 0);
    }
    return r;
}









































// @ 0x004983d0
void FUN_004983d0(X982* p, uint8_t flag)
{
    if (p->GetFlag(0xf)) {
        if (flag == 0)
            ((X5ae40*)FUN_00401050(0x3f1bf55, 0, (int)p, 0))->F();
    } else {
        if (flag != 0)
            ((X5ae40*)FUN_00401050(0x3f1bf56, 0, (int)p, 0))->F();
    }
}








































// @ 0x00498470
bool FUN_00498470(Block* blk, P3* pos, Matrix3_s0049_8470* m1, Matrix3_s0049_8470* m2, bool e, float f, uint8_t g, char h)
{
    if (blk != 0 && (blk->mSocketBlock || g != 0) && blk->mEditorModel && blk->mEditorModel->FUN_004adc40()) {
        bool is15 = blk->mFlags.test(0xf);
        bool b1 = true;
        P3 outPos;
        if (FUN_004974e0(blk, *(Vec3_s0049_8470*)pos, &outPos, &b1, f, g)) {
            Matrix3_s0049_8470 tmpRet;
            *m1 = *MoveBlockAndTranslateSnappedBlocks(&tmpRet, blk, *m1);
            Matrix3_s0049_8470 saved(*m2);
            if (FUN_004973f0(blk, m2, f, g)) {
                e = true;
            } else if (is15) {
                e = false;
                *m2 = saved;
            }
            if (!b1) {
                e = false;
                *m2 = saved;
            }
            *pos = outPos;
            FUN_0049ec40(blk, pos, m1, m2, e);
            if (!is15) {
                blk->SetBooleanAttribute(0xf, true);
                if (h)
                    FUN_004983d0(blk, is15);
            }
            return true;
        } else if (is15) {
            FUN_00498230(blk, 0);
            if (h)
                FUN_004983d0(blk, is15);
        }
    }
    return false;
}








































// @ 0x004986d0
bool FUN_004986d0(Block* blk)
{
    if (blk != 0) {
        bool ok = blk->mEditorModel ? blk->mEditorModel->FUN_004adc40() : false;
        if (!ok)
            return false;
        if (blk->mFlags.test(0xf) && !blk->mSocketBlock) {
            if (blk->mFlags.test(0) || blk->mFlags.test(0x1f))
                return false;
            else
                return true;
        } else {
            return FUN_004986d0(blk->mSocketBlock);
        }
    }
    return false;
}








































// @ 0x00498850
bool FUN_00498850(Handle* h, AutoRef<IPicker> picker)
{
    App* app = App_Get();
    P3 camPos;
    char camInfo[14];
    app->GetViewer()->GetCameraLocationInfo(&camPos, camInfo, 0, 0);
    P3 origin;
    origin = camPos;

    P3 tmpA, tmpB, tmpN;
    P3* hpos = h->GetPosition(&tmpA);
    P3* diff = FUN_0041db10(&tmpB, hpos, &camPos);
    Vec3_s0049_8470 diffCopy = *(Vec3_s0049_8470*)diff;
    P3* nrm = Vector3_Normalize(&tmpN, (P3*)&diffCopy);
    P3 dir;
    dir = *nrm;

    Block* pick = 0;
    if (picker.mp != 0) {
        int type = 1;
        bool swapped = false;
        P3 hit1, n1;
        float d1;
        bool found = picker->RayCast(type, *(Vec3C*)&origin, *(Vec3_s0049_8470*)&dir, &hit1, &n1, &d1, true);
        P3 hit2, n2;
        float d2;
        if (picker->RayCast(2, *(Vec3_s0049_8470*)&origin, *(Vec3_s0049_8470*)&dir, &hit2, &n2, &d2, true)) {
            if (!found || d1 > d2) {
                hit1 = hit2;
                n1 = n2;
                swapped = true;
            }
            found = true;
        }
        if (found) {
            if (swapped)
                pick = picker->PickResult(2, *(Vec3_s0049_8470*)&hit1);
            else
                pick = picker->PickResult(type, *(Vec3_s0049_8470*)&hit1);
            if (h->GetTypeId() == 0x50e8e23) {
                HandleData* hd = h->FUN_0047e680();
                P3* p = &hd->sub.pos;
                Vec3_s0049_8470 d3 = *(Vec3_s0049_8470*)FUN_0041db10(&tmpA, &camPos, p);
                float len1 = VectorLength((P3*)&d3);
                float radius = h->FUN_0047e6c0()->FUN_0043f3a0();
                float a = len1 - radius;
                Vec3_s0049_8470 d4 = *(Vec3_s0049_8470*)FUN_0041db10(&tmpB, &hit1, &camPos);
                float len2 = VectorLength((P3*)&d4);
                if (a < len2)
                    pick = 0;
            }
        }
    }

    bool b1 = false;
    bool b2 = false;
    bool same = (pick == h->FUN_0047e6c0());
    if (!same) {
        Block* sock = h->FUN_0047e6c0()->mSocketBlock;
        if (sock != 0) {
            Block* sock2 = h->FUN_0047e6c0()->mSocketBlock;
            if (!sock2->mFlags.test(7)) {
                Block* sock3 = h->FUN_0047e6c0()->mSocketBlock;
                if (sock3 == pick) {
                    b1 = true;
                } else {
                    Block* sock4 = h->FUN_0047e6c0()->mSocketBlock;
                    Block*** vec = (Block***)&sock4->mSocketBegin;
                    int i = 0;
                    int n = (int)((Block**)vec[1] - (Block**)vec[0]);
                    for (; i < n; i++) {
                        Block** pe = &vec[0][i];
                        Block* q = *pe;
                        if (q == pick) {
                            b2 = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (pick == 0) {
        return false;
    } else if (!same && !b1 && !b2) {
        return true;
    }
    return false;
}








































// @ 0x00498f10
Block* FUN_00498f10(Block* blk, Vec3_s0049_8470 origin, Vec3_s0049_8470 dir, AutoRef<IPicker> picker, P3* outHit, P3* outNormal, int a30, int a34, int a38)
{
    AutoRefModel<Model> model(blk->mEditorModel.mp);
    Block* result = 0;
    int skinId = blk->GetSkinIdentifierForPicking();
    Block* pinned = 0;
    P3 hit, normal;
    if (!blk->mFlags.test(0xb))
        pinned = PickBlockForPinning(blk, a30, origin, dir, &hit, &normal, a38, a34);
    result = pinned;
    *outHit = hit;
    *outNormal = normal;
    if (picker.mp != 0 && skinId != 3) {
        bool swapped = false;
        P3 hit1, n1;
        float d1;
        bool found = picker->RayCast(skinId, origin, dir, &hit1, &n1, &d1, true);
        if (skinId == 1) {
            P3 hit2, n2;
            float d2;
            if (picker->RayCast(2, origin, dir, &hit2, &n2, &d2, true)) {
                if (!found || d1 > d2) {
                    hit1 = hit2;
                    n1 = n2;
                    swapped = true;
                }
                found = true;
            }
        }
        if (found) {
            bool take = true;
            if (pinned != 0) {
                P3 tmp;
                Vec3_s0049_8470 d = *(Vec3_s0049_8470*)FUN_0041db10(&tmp, (P3*)&origin, &hit);
                float len = VectorLength((P3*)&d);
                take = len > d1;
            }
            if (take) {
                *outHit = hit1;
                *outNormal = n1;
                if (swapped)
                    result = picker->PickResult(2, *(Vec3_s0049_8470*)&hit1);
                else
                    result = picker->PickResult(skinId, *(Vec3_s0049_8470*)&hit1);
            }
        }
    }
    return result;
}







































// @ 0x00499410
Block* FUN_00499410(Entity* e, Vector3_s0049_9410 org, Vector3_s0049_9410 dir, AutoRefCountSkinMgr skin, Vector3_s0049_9410* outPt, Vector3_s0049_9410* outN, unsigned arg30)
{
    AutoRefCountRefObj u(e->GetRefObj());
    Block* p30 = 0;
    int n37 = e->GetSkinIdentifierForPicking();
    Block* obj = 0;
    bool v28 = false;
    Vector3_s0049_9410 t24;
    Vector3_s0049_9410 v33;
    if (!e->TestFlag(11))
        obj = PickBlockForPinning(e, arg30, org, dir, &t24, &v33, &v28, 0);
    p30 = obj;
    *outPt = t24;
    *outN = v33;
    if (skin) {
        bool v14 = false;
        Vector3_s0049_9410 t25, m;
        float n1;
        bool t14 = skin->PickSkin(n37, org, dir, &t25, &m, &n1, 1);
        if (n37 == 1) {
            Vector3_s0049_9410 pos2, nrm2;
            float t2;
            if (skin->PickSkin(2, org, dir, &pos2, &nrm2, &t2, 1)) {
                if (!t14 || n1 > t2) {
                    t25 = pos2;
                    m = nrm2;
                    v14 = true;
                }
                t14 = true;
            }
        }
        if (!t14) {
            float nrm[3] = { 1.0f, 0.0f, 0.0f };
            float pt[3] = { 0.0f, 0.0f, 0.0f };
            Plane pl(nrm[0], nrm[1], nrm[2], -Dot3(pt, nrm));
            Vec3C_s0049_9410 hit;
            hit = g_15d64d8_v3c;
            float t;
            if (IntersectRayPlane(&org, &dir, &pl, &t)) {
                Vector3_s0049_9410 sv, sum;
                Vector3_Scale_s0049_9410(&sv, &t, &dir);
                Vector3_s0049_9410 r = *VectorAdd(&sum, &org, &sv);
                hit.x = r.x; hit.y = r.y; hit.z = r.z;
            }
            Vector3_s0049_9410 onPlane;
            FUN_0049c630(&onPlane, hit, skin.mpObject);
            Vector3_s0049_9410 tmp;
            Vector3_s0049_9410 d = *VectorSub(&tmp, &onPlane, (Vector3_s0049_9410*)&hit);
            Vector3_s0049_9410 nd;
            Vector3_Normalize(&nd, &d);
            if (skin->PickSkin(n37, hit, nd, &t25, &m, &n1, 1)) {
                if (n1 < 1.0f && e->HasAnyBlockFlag())
                    t14 = true;
            }
        }
        if (t14) {
            bool take = true;
            if (obj) {
                Vector3_s0049_9410 tmp;
                Vector3_s0049_9410 diff = *VectorSub(&tmp, &org, &t24);
                if (!(VectorLength(&diff) > n1))
                    take = false;
            }
            if (take) {
                *outPt = t25;
                *outN = m;
                if (v14)
                    p30 = skin->GetBlockAtSkinPoint(*(Vec3C_s0049_9410*)&t24, 2);
                else
                    p30 = skin->GetBlockAtSkinPoint(*(Vec3C_s0049_9410*)&t24, n37);
            }
        }
    }
    return p30;
}







































// @ 0x00499b40
Vector3_s0049_9410 FUN_00499b40(Vector3_s0049_9410 a, Vector3_s0049_9410 b, Vector3_s0049_9410 c, Vector3_s0049_9410 p)
{
    Vector3_s0049_9410 n5, t15, t24;
    Vector3_s0049_9410 u = *VectorSub(&n5, &b, &c);
    float w = VectorLength(&u);
    Vector3_s0049_9410 p39 = *VectorSub(&t15, &a, &c);
    float p30 = VectorLength(&p39);
    Vector3_s0049_9410 key = *VectorSub(&t24, &b, &a);
    float bucket = VectorLength(&key);
    if (w > 0.0f && p30 > 0.0f && bucket > 0.0f) {
        Vector3_s0049_9410 p11, size, n37;
        Vector3_s0049_9410 chunk = *VectorSub(&p11, &c, &p);
        Vector3_s0049_9410 t6 = *VectorSub(&size, &b, &c);
        float v23 = VectorLength(Cross(&n37, &t6, &chunk)) / w;
        Vector3_s0049_9410 n18, p10, v28, t12, t26, obj;
        Vec3C_s0049_9410 v9(*(Vec3C_s0049_9410*)VectorSub(&n18, &c, &p));
        Vec3C_s0049_9410 ret(*(Vec3C_s0049_9410*)VectorSub(&p10, &a, &c));
        float t18 = VectorLength(Cross(&v28, (Vector3_s0049_9410*)&ret, (Vector3_s0049_9410*)&v9)) / p30;
        Vec3C_s0049_9410 k(*(Vec3C_s0049_9410*)VectorSub(&t12, &a, &p));
        Vec3C_s0049_9410 hi(*(Vec3C_s0049_9410*)VectorSub(&t26, &b, &a));
        float last = VectorLength(Cross(&obj, (Vector3_s0049_9410*)&hi, (Vector3_s0049_9410*)&k)) / bucket;
        float count = p30 * t18 * 0.5f;
        float i = w * v23 * 0.5f;
        float n28 = bucket * last * 0.5f;
        float v33 = count + i + n28;
        if (v33 > 0.0f)
            return Vector3_s0049_9410(i / v33, count / v33, n28 / v33);
    }
    return Vector3_s0049_9410(0.33f, 0.33f, 0.33f);
}







































// @ 0x00499f10
Vector3_s0049_9410* FUN_00499f10(Vector3_s0049_9410* ret, Vector3_s0049_9410 a, Vector3_s0049_9410 b, Vector3_s0049_9410 c)
{
    Vector3_s0049_9410 t13, n29, v11, alloc, cur, cap;
    Vector3_s0049_9410 n38 = *VectorSub(&t13, &b, &a);
    Vector3_s0049_9410 offset = *VectorSub(&v11, &c, &a);
    Vector3_Normalize(&cur, Cross(&n29, &offset, &n38));
    ScratchSlots_s0049_9410<9>();
    Vector3_s0049_9410 n6 = *VectorSub(&alloc, &b, &a);
    Vector3_Normalize(&cap, &n6);
    FUN_004a89e0(ret, &cur, &cap);
    ScratchSlots_s0049_9410<6>();
    return ret;
}







































// @ 0x0049a030
bool FUN_0049a030(Vector3_s0049_9410 origin, Vector3_s0049_9410 dir, Vector3_s0049_9410* out)
{
    Plane p;
    PlaneFromPointNormal((Plane*)&p, &g_15d64d8, &g_15d6324);
    float t;
    if (!IntersectRayPlane(&origin, &dir, &p, &t))
        return false;
    Vector3_s0049_9410 sv;
    Vector3_Scale_s0049_9410(&sv, &t, &dir);
    Vector3_s0049_9410 r;
    VectorAdd(&r, &origin, &sv);
    *out = r;
    return true;
}







































// @ 0x0049a0c0
Vector3_s0049_9410* FUN_0049a0c0(Vector3_s0049_9410* ret, DirOwner* o)
{
    DirSrc* m;
    if (o && (m = o->mp28) != 0) {
        Vector3_s0049_9410 d = o->GetSrc()->GetDir(o->GetDir(), o, 0, 0, g_15d6324);
        V3Agg neg1 = { -1.0f, -1.0f, -1.0f };
        if (Vector3Equal(&d, (Vector3_s0049_9410*)&neg1)) {
            Vector3_s0049_9410 t;
            Vector3_s0049_9410 n = *Vector3_Negate(&t, (Vector3_s0049_9410*)&o->mDir);
            Vector3_Normalize(ret, &n);
            return ret;
        }
        Vector3_s0049_9410 t;
        Vector3_s0049_9410 s = *VectorSub(&t, &d, (Vector3_s0049_9410*)&o->mDir);
        Vector3_Normalize(ret, &s);
        return ret;
    }
    ret->x = g_15d64d8.x;
    ret->y = g_15d64d8.y;
    ret->z = g_15d64d8.z;
    return ret;
}






































// @ 0x0049a2a0
namespace SP { namespace EditorUtils {
bool MoveBlockOrientToSurfaces(cSPEditorBlock_s0049_a2a0* block, BlockVector_s0049_a2a0& blocks, cSPVector3_s0049_a2a0 rayOrigin, cSPVector3_s0049_a2a0 rayDir, AutoRefCount_s0049_a2a0<cSPEditorSkinManager_s0049_a2a0> skinManager, cSPVector3_s0049_a2a0& outPosition, cSPVector3_s0049_a2a0* outNormal, bool b1, bool b2)
{
    bool localBMissed = false;
    AutoRefCount_s0049_a2a0<cSPEditorModel_s0049_a2a0> pModel(block->GetEditorModel());
    cSPVector3_s0049_a2a0 origPos(block->mPosition);
    cSPMatrix3_s0049_a2a0 origOrient(block->mBaseOrientation);
    cSPVector3Vector posArray;
    cSPMatrix3Vector vOrients;
    eSkinIdentifier mySkinIdentifier = block->GetSkinIdentifierForPicking();

    int theNumParts = blocks.size();
    for (int i = 0; i < theNumParts; i++) {
        posArray.push_back(blocks[i]->mPosition);
        ScratchSlots<2>();      // push_back frame
        vOrients.push_back(blocks[i]->mBaseOrientation);
        ScratchSlots<2>();
    }

    cSPEditorBlock_s0049_a2a0* prevParent = block->GetParent();
    cSPVector3_s0049_a2a0 finalDir_(rayDir);
    cSPVector3_s0049_a2a0 bNewPos;
    cSPVector3_s0049_a2a0 up;
    bool snappedResult;
    cSPEditorBlock_s0049_a2a0* newTarget = 0;
    int myIndex = -1;
    snappedResult = false;
    newTarget = FindPinningBlock(block, rayOrigin, rayDir, skinManager, &bNewPos, &up, blocks,
                               &myIndex, &snappedResult);

    bool bSkipMove = false;
    bool pinned = false;
    cSPVector3_s0049_a2a0 theProjected(origPos);
    cSPVector3_s0049_a2a0 refPosTmp(origPos);
    cSPVector3_s0049_a2a0 toSurface(block->mBlockPickDirection);

    cSPPlane curPlane(-rayDir, origPos);
    if (pModel->IsUsingSymmetry() && block->mFlags.test(15)) {
        curPlane = cSPPlane(gSymmetryPlaneNormal, gSymmetryPlanePoint);
        theProjected[0] = 0.0f;
        toSurface[0] = 0.0f;
        toSurface = Normalize(toSurface);
        ScratchSlots<5>();      // Normalize frame
        refPosTmp[0] = 0.0f;
    }

    float curT;
    ScratchSlots<2>();          // IntersectRayPlane frame
    if (IntersectRayPlane(rayOrigin, rayDir, curPlane, curT))
        theProjected = rayOrigin + curT * rayDir;

    float minZ = 0.03f;
    bool myHitGround = false;
    if (theProjected[2] < minZ) {
        theProjected[2] = minZ;
        myHitGround = true;
    }

    if (block->mParentBlock.get()) {
        float offset = pModel->GetGridSize() * 0.01f;
        cSPVector3_s0049_a2a0 toBlock = origPos + origOrient.yAxis * offset - theProjected;
        if (myHitGround)
            toBlock[2] = 0.0f;
        toSurface = Normalize(toBlock);
        ScratchSlots<5>();
    }

    bool found = false;
    if (!newTarget) {
        bool stacked = GetMissStackingPosition(block, blocks, rayOrigin, rayDir,
                                               block->mBaseOrientation, outPosition);
        if (stacked) {
            float backoff = pModel->GetGridSize() / 20.0f;
            cSPVector3_s0049_a2a0 posOutVal;
            cSPVector3_s0049_a2a0 normalOutVal;
            cSPEditorBlock_s0049_a2a0* thePCandidate = FindPinningBlock(block, theProjected - toSurface * backoff, toSurface,
                                                    skinManager, &posOutVal, &normalOutVal, blocks,
                                                    &myIndex, &snappedResult);
            float bMaxRange = block->GetStackingDistance();
            if (thePCandidate) {
                if (bMaxRange < 0.0f || VectorLength(posOutVal - theProjected) < bMaxRange) {
                    ScratchSlots<1>();  // VectorLength frame
                    bNewPos = posOutVal;
                    up = normalOutVal;
                    newTarget = thePCandidate;
                    finalDir_ = toSurface;
                    found = true;
                }
            } else if (block->mParentBlock.get()) {
                myIndex = -1;
                newTarget = block->GetParent();
                up = -origOrient.yAxis;
                bNewPos = origPos;
            }
        } else {
            localBMissed = true;
        }
    }

    up = Normalize(up);
    ScratchSlots<5>();
    if (outNormal)
        *outNormal = up;

    if (newTarget && !block->mFlags.test(51)) {
        cSPVector3_s0049_a2a0 posCopy(bNewPos);
        int r1 = ClassifyAgainstSymmetryPlane(posCopy, pModel->GetGridSize(), pModel->GetSize1(),
                                                pModel->GetSize2(), 0);
        if (r1 != 3) {
            newTarget = 0;
            bool newBOk = GetMissStackingPosition(block, blocks, rayOrigin, rayDir,
                                                   block->mBaseOrientation, outPosition);
            posCopy = outPosition;
            if (ClassifyAgainstSymmetryPlane(posCopy, pModel->GetGridSize(), pModel->GetSize1(),
                                             pModel->GetSize2(), 0) == 3) {
                if (r1 == 0 || r1 == 0) {
                    outPosition[2] = bNewPos[2];
                } else {
                    outPosition[0] = bNewPos[0];
                    outPosition[1] = bNewPos[1];
                }
            }
            localBMissed = !newBOk;
        }
    }

    if (newTarget || pinned) {
        block->SetSurfaceNormal(up);
        cSPMatrix3_s0049_a2a0 orientation = GetOrientationForNormal(block, up);
        RepinBlockToTorso(block, bNewPos, orientation, false);
    }

    if (!pinned) {
        if (newTarget) {
            block->mIsOnGround = false;
            if (block->mSymmetricBlock.get())
                block->mSymmetricBlock->mIsOnGround = false;
        }
        if (block->mParentBlock.get() != newTarget) {
            if (newTarget) {
                if (!block->mParentBlock.get())
                    MessageManager_s0049_a2a0()->PostBlockMessage(0x3f1bf58, 0, block, 0);
                newTarget->AttachChild(block);
            } else if (block->mParentBlock.get()) {
                block->mParentBlock->DetachChild(block);
                MessageManager_s0049_a2a0()->PostTransformMessage(0x3f1bf59, 0, &origPos, &origOrient);
            }
        }
    }

    if (!bSkipMove && block->mParentBlock.get() && block->mParentBlock.get() == newTarget)
        block->MoveTo(myIndex, bNewPos, finalDir_, snappedResult);

    if (!b2 && !newTarget && !pinned)
        return localBMissed;
    return localBMissed;
}
}}  // namespace SP::EditorUtils

































// @ 0x0049b340
bool FUN_0049b340(BitOwner* p)
{
    if (p != 0) {
        if (p->GetFlag(7))
            return true;
        if (p->GetFlag(8))
            return true;
        if (p->GetFlag(0x23))
            return true;
    }
    return false;
}















// @ 0x0049b460
void FUN_0049b460(void* p, void* a, void* b)
{
    (void)p; (void)a; (void)b;
}















// @ 0x0049b8b0
void FUN_0049b8b0(void* p, void* a, void* b)
{
    (void)p; (void)a; (void)b;
}















// @ 0x0049bcc0
void FUN_0049bcc0(void* p, void* a, void* b)
{
    (void)p; (void)a; (void)b;
}















// @ 0x0049c0f0
void Y9c0::Set(char v)
{
    this->flag = v;
    Y9c0* t = (Y9c0*)this->tracker;
    if (t != 0) {
        Y9c0* t2 = (Y9c0*)this->tracker;
        t2->flag = v;
    }
}















// @ 0x0049c140
void FUN_0049c140(void* out, void* p, float x, float y, float z)
{
    (void)out; (void)p; (void)x; (void)y; (void)z;
}















// @ 0x0049c210
namespace SP { namespace EditorUtils {
cSPMatrix3_s0049_c210* FUN_49c210(cSPMatrix3_s0049_c210* out, cSPEditorBlock_s0049_c210* block, float x, float y, float z)
{
    if (!block) {
        *out = cSPMatrix3_s0049_c210();
        return out;
    }
    if (!FUN_43c510(block)) {
        *out = block->mOrientation;
        return out;
    }
    *out = block->mOrientation;
    return out;
}
}}  // namespace SP::EditorUtils














// @ 0x0049c570
namespace SP { namespace EditorUtils {
cSPEditorBlock_s0049_c210* FindClosestSymmetry(cSPVector3_s0049_c210 point, cSPEditorBlock_s0049_c210* block)
{
    float p15 = FLT_MAX;
    cSPEditorBlock_s0049_c210* nCount = block;
    cSPEditorBlock_s0049_c210* t22 = 0;
    while (nCount) {
        cSPVector3_s0049_c210 hi = GetSkinTip(nCount);
        cSPVector3_s0049_c210 item = point - hi;
        float t26 = VectorLength(item);
        if (t26 < p15) {
            p15 = t26;
            t22 = nCount;
        }
        nCount = FindSymmetricSpine(nCount);
    }
    ScratchSlots<1>();
    return t22;
}
}}  // namespace SP::EditorUtils














// @ 0x0049c630
namespace SP { namespace EditorUtils {
cSPVector3_s0049_c210* FUN_49c630(cSPVector3_s0049_c210* out, float x, float y, float z, cSPEditorModel* model)
{
    out->x = x;
    out->y = y;
    out->z = z;
    return out;
}
}}  // namespace SP::EditorUtils














// @ 0x0049c8f0
namespace SP { namespace EditorUtils {
void BuildBlockTransforms(cSPEditorBlock_s0049_c210* block, vector<TrackerRecord>* out, bool recurse)
{
    if (!block) return;
    if (FUN_435c80(block)) return;
    vector<AutoRefCount_s0049_c210<cSPEditorBlock_s0049_c210> >* syms = &block->mSymmetricBlocks;
    int count = syms->size();
    for (int i = 0; i < count; i++) {
        cSPEditorBlock_s0049_c210* sym = syms->mpBegin[i];
        if (!FUN_435c80(sym) && sym->mSkin == 0) {
            cSPMatrix3_s0049_c210 orient = block->mOrientation;
            cSPVector3_s0049_c210 rel = sym->mPosition - block->mPosition;
            cSPVector3_s0049_c210 a = orient * rel;
            cSPVector3_s0049_c210 b = orient * sym->mRestPose;
            TrackerRecord rec;
            rec.block = block;
            rec.transform = cSPTransform_s0049_c210();
            rec.transform.mTranslation = a + b;
            rec.transform.mRotation = orient;
            out->push_back(rec);
        }
        if (recurse) BuildBlockTransforms(sym, out, recurse);
    }
}
}}  // namespace SP::EditorUtils














// @ 0x0049cb90
namespace SP { namespace EditorUtils {
void FUN_49cb90(vector<TrackerRecord>* list)
{
    int i = 0;
    int n = list->size();
    for (; i < n; i++) {
        TrackerRecord& rec = list->mpBegin[i];
        cSPEditorBlock_s0049_c210* block = rec.block;
        cSPTransform_s0049_c210 local(rec.transform);
        cSPEditorBlock_s0049_c210* target = block->mParentBlock->mPinTarget;
        if (target) {
            cSPVector3_s0049_c210 pos = local.mTranslation * target->mOrientation + target->mPosition;
            cSPMatrix3_s0049_c210 rot = local.mRotation * target->mOrientation;
            RepinBlockToTorso(block, pos, rot, 0);
            target->FUN_438700(block);
            if (!block->mFlags.test(10)) {
                cSPVector3_s0049_c210 a;
                cSPVector3_s0049_c210 b;
                block->GetOffsetA(&b, true);
                block->GetOffsetB(&a, true);
                block->Place(a, b);
            }
        }
    }
}
}}  // namespace SP::EditorUtils














// @ 0x0049ce40
namespace SP { namespace EditorUtils {
void RepinBlocks(vector<TrackerRecord>* list)
{
    int i = 0;
    int n = list->size();
    for (; i < n; i++) {
        TrackerRecord& rec = list->mpBegin[i];
        cSPEditorBlock_s0049_c210* block = rec.block;
        cSPTransform_s0049_c210 local(rec.transform);
        cSPEditorBlock_s0049_c210* parent = block->mParentBlock;
        if (parent) {
            cSPVector3_s0049_c210 pos = local.mTranslation * parent->mOrientation + parent->mPosition;
            cSPMatrix3_s0049_c210 rot = local.mRotation * parent->mOrientation;
            RepinBlockToTorso(block, pos, rot, 0);
        }
    }
}
}}  // namespace SP::EditorUtils














// @ 0x0049cfd0
void FUN_49cfd0(cSPEditorBlock_s0049_cfd0* block)
{ (void)block; }













// @ 0x0049d1f0
void FUN_49d1f0(cSPEditorBlock_s0049_cfd0* block, float scale, bool a, bool b)
{ (void)block; (void)scale; (void)a; (void)b; }













// @ 0x0049d390
void FUN_49d390(cSPEditorBlock_s0049_cfd0* block)
{ (void)block; }













// @ 0x0049d550
void FUN_49d550(cSPEditorBlock_s0049_cfd0* block)
{ (void)block; }













// @ 0x0049d640
void cSPTransform_s0049_cfd0::TransformVector(cSPVector3_s0049_cfd0* out)
{
    if (mFlags & 2) {
        *out = *out * mRotation;
    }
    ScaleVector(out, mScale);
}













// @ 0x0049d6b0
void FUN_49d6b0(cSPEditorBlock_s0049_cfd0* block)
{ (void)block; }













// @ 0x0049dca0
float ClampAndSetScale(cSPEditorBlock_s0049_cfd0* block, float value, bool clamp)
{
    if (clamp) {
        float tmp = block->mMinUniformScale;
        if (tmp > value) value = block->mMinUniformScale;
        float t14 = block->mMaxUniformScale;
        if (value > t14) value = block->mMaxUniformScale;
    }
    block->SetUniformScale(value, 0);
    return value;
}













// @ 0x0049dd20
bool FUN_49dd20(cSPEditorBlock_s0049_cfd0* block, void* param, bool b)
{ (void)block; (void)param; (void)b; return false; }













// @ 0x0049ecf0
void FUN_49ecf0(cSPEditorBlock_s0049_ecf0* block)
{ (void)block; }












// @ 0x0049ef80
void FUN_49ef80(cSomeTracker* self, cSPVector3_s0049_ecf0* vecs)
{
    for (int i = 0; i < 3; i++) {
        self->AddVector(vecs[i]);
    }
    ScratchSlots<4>();
}












// @ 0x0049efc0
void MoveBlocks(cSPEditorBlock_s0049_efc0* root, Vector3T_s0049_efc0 oldPos, Vector3T_s0049_efc0 newPos, Matrix33T_s0049_efc0 oldRot, Matrix33T_s0049_efc0 newRot, BlockVec_s0049_efc0* blocks)
{
    Matrix3L invOld = Inverse(oldRot);
    Matrix3L deltaRot = invOld * newRot;
    bool haveSocket = false;
    Vector3T_s0049_efc0 socketPos(kZeroVector_s0049_efc0);
    if (root->mpSocketConnectorModel) {
        socketPos = root->mpSocketConnectorModel->mOffset;
        haveSocket = true;
    }
    BlockVecX processed((AllocTag()));
    int nBlocks = blocks->size();
    for (int i = 0; i < nBlocks; i++) {
        cSPEditorBlock_s0049_efc0* block = (*blocks)[i];
        if (eastl::find_s0049_efc0(processed.begin(), processed.end(), (*blocks)[i]) != processed.end())
            continue;
        if (root->GetSymmetryIndex() == 0 && block->mpSymmetricBlock) {
            if (eastl::find_s0049_efc0(blocks->begin(), blocks->end(), (cSPEditorBlock_s0049_efc0*)block->mpSymmetricBlock) != blocks->end()) {
                processed.push_back(BlockRef_s0049_efc0((cSPEditorBlock_s0049_efc0*)block->mpSymmetricBlock));
                ScratchSlots<2>();
            }
        }
        cSPVector3_s0049_efc0 curPos(block->mPosition);
        if (haveSocket && block->mFlags.test(12)) {
            block->SetPosition(socketPos, true);
        } else {
            cSPVector3_s0049_efc0 local = (curPos - oldPos) * deltaRot;
            block->SetPosition(cSPVector3_s0049_efc0(newPos + local), true);
            cSPVector3_s0049_efc0 unused = local * Inverse(newRot);
            block->SetOrientation(cSPMatrix3_s0049_efc0(block->mOrientation * deltaRot), true);
        }
        cSPVector3_s0049_efc0 shift = block->mPosition - curPos;
        BlockVec_s0049_efc0 pile;
        BuildPileList(block, &pile, 0);
        for (int j = 0, cnt = pile.size(); j < cnt; j++) {
            cSPEditorBlock_s0049_efc0* child = pile[j];
            curPos = child->mPosition;
            if (block->mFlags.test(12)) {
                child->SetPosition(cSPVector3_s0049_efc0(curPos + shift), false);
            } else {
                cSPVector3_s0049_efc0 local = (curPos - oldPos) * deltaRot;
                child->SetOrientation(cSPMatrix3_s0049_efc0(child->mOrientation * deltaRot), false);
                child->SetPosition(cSPVector3_s0049_efc0(newPos + local), true);
            }
        }
        BlockVec_s0049_efc0 mirrorPile;
        if (block->mpSymmetricBlock && block->mpEditorModel->IsSymmetryEnabled()
            && GetSymmetricPile(block->mpSymmetricBlock, &mirrorPile, true)) {
            for (int k = 0, cnt = mirrorPile.size(); k < cnt; k++) {
                cSPEditorBlock_s0049_efc0* child = mirrorPile[k];
                curPos = child->mPosition;
                if (block->mFlags.test(12)) {
                    child->SetPosition(cSPVector3_s0049_efc0(curPos + Mirror(shift)), false);
                } else {
                    cSPVector3_s0049_efc0 local = (curPos - Mirror(oldPos)) * MirrorMatrix(deltaRot, 0);
                    child->SetOrientation(cSPMatrix3_s0049_efc0(child->mOrientation * MirrorMatrix(deltaRot, 0)), false);
                    child->SetPosition(cSPVector3_s0049_efc0(Mirror(newPos) + local), true);
                }
            }
        }
    }
    ScratchSlots<12>();
}











// @ 0x0049fbd0
void RepinBlockToTorso(cSPEditorBlock_s0049_fbd0* block, cSPVector3_s0049_fbd0 t, cSPMatrix3_s0049_fbd0 r, bool flag)
{
    cSPVector3_s0049_fbd0 oldPos(block->mPosition);
    cSPMatrix3_s0049_fbd0 oldMat(block->mOrientation);
    Mat3Id parentMat;
    Vector3T_s0049_fbd0 parentPos;
    if (block->mParent) {
        cSPEditorBlock_s0049_fbd0* p = block->mParent;
        parentPos = p->mPosition;
        parentMat = *(Mat3Id*)&block->mParent->mOrientation;
    }
    block->FUN_448e90(&t, 1);
    if (flag) {
        block->FUN_43ffa0(r);
        block->FUN_449420(&block->mTorsoMat, 1);
    } else {
        block->FUN_449420(&r, 1);
    }
    FUN_49efc0(block, oldPos, block->mPosition, oldMat, block->mOrientation, &block->mChildren);
    Vector3T_s0049_fbd0 zero;
    zero.x = 0; zero.y = 0; zero.z = 0;
    char alloc;
    RefBlockVec touched(alloc);
    if (block->mParent) {
        if (block->mEditorModel->FUN_4adc40()) {
            if (FUN_49dd20(block->mParent, (LimbVec<cSPEditorBlock_s0049_fbd0*>*)&touched, 0)) {
                FUN_49efc0(block->mParent, parentPos, block->mParent->mPosition,
                           parentMat, block->mParent->mOrientation, (LimbVec<cSPEditorBlock_s0049_fbd0*>*)&touched);
            }
        }
    }
}










// @ 0x0049fee0
void FUN_49fee0(cSPEditorBlock_s0049_fbd0* block, bool unique)
{
    LimbVec<cSPEditorBlock_s0049_fbd0*> limbs;
    GetAllLimbs(block, &limbs, unique);
    int i = 0;
    int n = limbs.e - limbs.b;
    for (; i < n; i++) {
        if (limbs.b[i]->mFlags.test(0xb)) {
            cSPEditorLimbStructure ls;
            ls.FUN_4891a0(limbs[i], 0, 0);
            ls.FixAllJoints();
            ls.FUN_488980();
        }
    }
}










// @ 0x004a0020
void GetAllLimbs(cSPEditorBlock_s0049_fbd0* block, LimbVec<cSPEditorBlock_s0049_fbd0*>* out, bool unique)
{
    char a1;
    LimbVec<cSPEditorBlock_s0049_fbd0*> all(a1);
    cSPEditorBlock_s0049_fbd0* cur = FUN_4a5a70(block->GetEditorModel());
    while (cur) {
        all.push_back(cur);
        cur = FUN_4a5970(cur);
    }
    char a2;
    LimbVec<cSPEditorBlock_s0049_fbd0*> seen(a2);
    int i = 0;
    int n = all.e - all.b;
    for (; i < n; i++) {
        LimbVec<cSPEditorBlock_s0049_fbd0*>* kids = &all[i]->mChildren;
        int j = 0;
        int m = kids->e - kids->b;
        for (; j < m; j++) {
            cSPEditorBlock_s0049_fbd0* child = (*kids)[j];
            if (child->mFlags.test(0xb)) {
                if (unique) {
                    cSPEditorBlock_s0049_fbd0** it = seen.b;
                    cSPEditorBlock_s0049_fbd0** end = seen.e;
                    cSPEditorBlock_s0049_fbd0* want = (*kids)[j];
                    while (it != end && *it != want) ++it;
                    if (it != seen.e) continue;
                }
                cSPEditorBlock_s0049_fbd0* v = (*kids)[j];
                out->push_back(v);
                if (unique) {
                    cSPEditorBlock_s0049_fbd0* pv = (*kids)[j]->mParent;
                    seen.push_back(pv);
                }
            }
        }
    }
}










// @ 0x004a02b0
void FUN_4a02b0(cSPEditorBlock_s0049_fbd0* block, cSPVector3_s0049_fbd0 p, cSPVector3_s0049_fbd0 q)
{
    cSPVector3_s0049_fbd0 c(block->mPosition);
    Vector3T_s0049_fbd0 tmp1, tmp2, tmp3;
    PodVec v1 = *(PodVec*)FUN_41db10(&tmp1, &p, &c);
    float len1 = VectorLength((Vector3T_s0049_fbd0*)&v1);
    PodVec v2 = *(PodVec*)FUN_41db10(&tmp2, &q, &c);
    float len2 = VectorLength((Vector3T_s0049_fbd0*)&v2);
    PodVec v3 = *(PodVec*)FUN_41db10(&tmp3, &p, &c);
    Vector3T_s0049_fbd0 n;
    Vector3_Normalize(&n, (Vector3T_s0049_fbd0*)&v3); // 0x00436ce0
    LimbVec<cSPEditorBlock_s0049_fbd0*>* kids = &block->mChildren;
    int i = 0;
    int cnt = kids->e - kids->b;
    for (; i < cnt; i++) {
        cSPEditorBlock_s0049_fbd0* blk = (*kids)[i];
        if (blk->mFlags.test(0xc)) {
            PodVec q2;
            q2.x = q.x; q2.y = q.y; q2.z = q.z;
            RepinBlockToTorso(blk, *(cSPVector3_s0049_fbd0*)&q2, cSPMatrix3_s0049_fbd0(blk->mTorsoMat), false);
        } else if (block->mFlags.test(0xa)) {
            cSPVector3_s0049_fbd0 bp(blk->mPosition);
            Vector3T_s0049_fbd0 tmp4, tmp5, tmp6;
            PodVec d = *(PodVec*)FUN_41db10(&tmp4, &bp, &c);
            float dot = d.x * n.x + d.y * n.y + d.z * n.z;
            float ratio = dot / len1;
            float scaled = ratio * len2;
            float diff = scaled - dot;
            cSPVector3_s0049_fbd0 w(*FUN_41dca0(&tmp5, &n, &diff));
            PodVec r = *(PodVec*)FUN_41dc10(&tmp6, &bp, &w);
            RepinBlockToTorso(blk, *(cSPVector3_s0049_fbd0*)&r, cSPMatrix3_s0049_fbd0(*(const Mat3B*)&blk->mTorsoMat), false);
        }
    }
}










// @ 0x004a06c0
Vector3T_s0049_fbd0* FUN_4a06c0(Vector3T_s0049_fbd0* ret, cSPEditorBlock_s0049_fbd0* block)
{
    if (block == 0) {
        ret->x = g_zero;
        ret->y = g_zero;
        ret->z = g_zero;
        return ret;
    } else if (block->mFlags.test(0x14)) {
        float z = 0.05f;
        if (block->GetEditorModel()) {
            z = block->GetEditorModel()->FUN_4adaa0() / 20.0f;
        }
        ret->x = g_zero;
        ret->y = g_zero;
        ret->z = z;
        return ret;
    } else if (block->mFlags.test(0x1f)) {
        Vector3T_s0049_fbd0 pos;
        pos.x = block->mPosition.x; pos.y = block->mPosition.y; pos.z = block->mPosition.z;
        Vector3T_s0049_fbd0 bb;
        float* pb = block->GetBBox((float*)&bb, 0, 0, 0);
        bb.x = pb[0]; bb.y = pb[1]; bb.z = pb[2];
        Vector3T_s0049_fbd0 tmp;
        Vector3T_s0049_fbd0* r = FUN_41db10(&tmp, &pos, &bb);
        *ret = *r;
        return ret;
    } else {
        ret->x = g_zero;
        ret->y = g_zero;
        ret->z = g_zero;
    }
    return ret;
}










// @ 0x004a0900
bool FUN_4a0900(cSPEditorBlock_s0049_fbd0* block, void* p2, cSPVector3_s0049_fbd0 a, cSPVector3_s0049_fbd0 b, Vector3T_s0049_fbd0* out)
{
    cSPEditorModel_s0049_fbd0* model = block->mEditorModel;
    bool result = false;
    Vector3T_s0049_fbd0 pos;
    pos.x = block->mPosition.x; pos.y = block->mPosition.y; pos.z = block->mPosition.z;
    Vector3T_s0049_fbd0 off;
    void* hit = FUN_4a3dc0(block, p2, a, b, &off);
    if (hit == 0) {
        if (block->mFlags.test(0xc)) {
            FUN_4a1070(block);
            return result;
        }
    }
    if (hit != 0) {
        result = true;
        void* sock = block->mSocketConnector;
        if (hit != sock) {
            FUN_4a29a0(block, p2, hit);
            Vector3T_s0049_fbd0 tmp;
            Vector3T_s0049_fbd0* r = FUN_41db10(&tmp, &block->mPosition, &off);
            *out = *r;
        } else {
            *(PodVec*)out = g_vec015d64d8;
        }
    }
    return result;
}










// @ 0x004a0ac0
bool FUN_4a0ac0(cSPEditorModel_s0049_fbd0* model)
{
    bool h = 0;
    int v1 = 0;
    int idx = model->GetBlockCount();
    for (; v1 < idx; v1++) {
        cSPEditorBlock_s0049_fbd0* p1 = model->GetBlock(v1);
        if (p1 && p1->mFlags.test(0x2d)) {
            h = 1;
        }
    }
    return h;
}










// @ 0x004a0b70
cSPEditorBlock_s004a_0b70* FUN_4a0b70(int world, int idx, float scale)
{
    cSPEditorBlock_s004a_0b70* block = new("Editor", 0, 0, 0, 0) cSPEditorBlock_s004a_0b70();
    block->BuildBlock(0xa077208c, g_ModelWorld, world, idx, scale, 1, 1, 1);
    block->SetBooleanAttribute(0x14, true);
    return block;
}









// @ 0x004a0bf0
void FUN_4a0bf0(cSPEditorBlock_s004a_0b70* block)
{
    cSPEditorModel_s004a_0b70* model = block->mEditorModel;
    if (block && model && block->GetAttach()) {
        cSPEditorBlock_s004a_0b70* nb;
        int j;
        int m;
        int i;
        int n;
        vector_s004a_0b70<AutoRefCount_s004a_0b70<cSPEditorBlock_s004a_0b70> >* children;
        cSPEditorBlock_s004a_0b70* self;
        bool unplaceable;
        unplaceable = false;
        children = &block->mChildren;
        i = 0;
        n = (int)(children->mpEnd - children->mpBegin);
        for (; i < n; i++) {
            FUN_4a0bf0((*children)[i]);
        }
        j = 0;
        m = (int)(children->mpEnd - children->mpBegin);
        for (; j < m; j++) {
            if ((*children)[j]->mFlags.test(0x14) && (*children)[j]->mFlags.test(0x2d)) {
                (*children)[j]->OnRemoved(false, false);
                continue;
            }
            if ((*children)[j]->mFlags.test(0xc)) {
                unplaceable = true;
                break;
            }
            cSPVector3_s004a_0b70 v = (*children)[j]->mPosition - block->mAttachPoint->mPosition;
            if (model->GetScale() * 0.067f < VectorLength(v)) {
                unplaceable = true;
                break;
            }
        }
        self = block;
        if (self) self->AddRef();
        DeleteInvalidBlocks(self, 0);
        if (!unplaceable) {
            int world = block->mModelWorld;
            float scale = block->GetScaleF();
            int id = block->GetSomeId();
            nb = FUN_4a0b70(world, id, scale);
            model->AddBlock(nb, true);
            nb->SetBooleanAttribute(0xc, true);
            if (block->mSymmetricBlock) nb->Split(3);
            block->Attach(nb);
            nb->SetOrientation(&block->mAxes[0], 0);
            nb->SetPosition(&block->mAttachPoint->mPosition, 0);
            nb->SetAnim(nb->GetAnim());
            if (block->IsPaintable()) nb->SetUIState(false, false);
            SetSymmetricBlocksUIState(nb, 0, 0);
        }
        if (self) self->Release();
    }
}









// @ 0x004a1020
void FUN_4a1020(cSPEditorModel_s004a_0b70* model)
{
    int tmp = 0;
    int t14 = model->GetBlockCount();
    for (; tmp < t14; tmp++) {
        model->GetBlock(tmp)->FUN_451360();
    }
}









// @ 0x004a1070
void FUN_4a1070(cSPEditorBlock_s004a_0b70* block)
{
    cSPEditorModel_s004a_0b70* model = block->mEditorModel;
    cSPEditorHandle* handle = block->mHandle;
    block->SetBooleanAttribute(0xc, false);
    handle->SetActive(true, false);
    if (model->FUN_4adc40()) {
        cSPEditorBlock_s004a_0b70* sym = block->mSymmetricBlock;
        if (sym && sym->mHandle) {
            sym->mHandle->SetActive(true, false);
        }
    }
    cSPEditorBlock_s004a_0b70* socket = block->mSocketConnector;
    if (socket) {
        socket->FUN_438a40(block);
        GetEditorMessageManager()->Post(0x3f1bf59, 0, block, 0);
    }
    block->RecursiveFlag();
    bool anyUnsnapped = false;
    cSPEditorBlock_s004a_0b70* liveBlock = 0;
    cSPEditorHandle* firstHandle = 0;
    UIntVector_s004a_0b70 selected;
    selected.mpBegin = 0; selected.mpEnd = 0; selected.mpCapacity = 0;
    SPAllocTmp allocTmp;
    selected.AllocatorInit(&allocTmp);
    vector_s004a_0b70<AutoRefCount_s004a_0b70<cSPEditorBlock_s004a_0b70> >* children = &socket->mChildren;
    int i = 0;
    int n = (int)(children->mpEnd - children->mpBegin);
    for (; i < n; i++) {
        if ((*children)[i]->mFlags.test(0xc)) {
            (*children)[i]->SetUIState(true, true);
            SetSymmetricBlocksUIState((*children)[i], 0, 0);
            uint32_t b = (uint32_t)(cSPEditorBlock_s004a_0b70*)(*children)[i];
            selected.push_back(b);
            if ((*children)[i]->mHandle) {
                firstHandle = (*children)[i]->mHandle;
            }
            anyUnsnapped = true;
            if ((*children)[i]->mFlags.test(0x14) && (*children)[i]->mFlags.test(0x2d)) {
                liveBlock = (*children)[i];
            }
        }
    }
    if (firstHandle) {
        firstHandle->SetActive(true, false);
    }
    if (!anyUnsnapped && socket && socket->mFlags.test(5)) {
        int world = block->mModelWorld;
        float scale = block->GetScaleF();
        int id = block->GetSomeId();
        cSPEditorBlock_s004a_0b70* nb = FUN_4a0b70(world, id, scale);
        if (nb) {
            model->AddBlock(nb, true);
            nb->SetBooleanAttribute(0xc, true);
            if (socket->mSymmetricBlock) nb->Split(3);
            block->Attach(nb);
            nb->SetOrientation(&block->mAxes[0], 0);
            nb->SetPosition(&block->mPosition, 0);
            nb->SetAnim(nb->GetAnim());
            nb->SetBooleanAttribute(0x39, socket->mFlags.test(0x39));
            nb->SetBooleanAttribute(0x3a, socket->mFlags.test(0x3a));
            SetSymmetricBlocksUIState(nb, 0, 0);
        }
    }
    if (socket && socket->mFlags.test(0xb) && FUN_4a7e60(socket) && !FUN_4a7dd0(socket)) {
        cSPEditorLimbStructure_s004a_0b70 limbA;
        cSPEditorLimbStructure_s004a_0b70 limbB;
        limbA.Build(socket, 0, 1);
        limbA.Apply();
        if (socket->mSymmetricBlock) {
            limbB.Build(socket->mSymmetricBlock, 0, 1);
            limbB.Apply();
        }
        limbA.FixAll();
        if (socket->mSymmetricBlock) {
            limbB.FixAll();
            limbB.FixB();
            limbB.FixC();
        }
        limbA.FixB();
        limbA.FixC();
    }
    MessageServer_s004a_0b70()->Post(0x48e5912, 0, 0);
    (void)liveBlock;
}









// @ 0x004a18b0
bool FUN_4a18b0(cSPEditorBlock_s004a_0b70* a, cSPEditorBlock_s004a_0b70* b, float f)
{
    int obj; float v28; int n37; int t24; int u; int v33; int p30;
    if (a->CanConnect(b, 0x2b)) {
        if (!b->IsPaintable()) {
            if (!b->mFlags.test(0x2a)) {
                return false;
            }
        }
        if (a->Near(f, 1.0f) || b->Near(f, 1.0f)) {
            if (a->Near(f / 2.0f, 1.0f) || b->Near(f / 2.0f, 1.0f)) {
                return true;
            } else {
                a->GetAxisIndices(&v33, &n37, &p30);
                b->GetAxisIndices(&obj, &u, &t24);
                v28 = b->mAxes[u].Dot2(a->mAxes[n37]);
                if (v28 > 0.5f) {
                    return true;
                }
            }
        }
    }
    return false;
}









// @ 0x004a1a70
void FUN_4a1a70(void* unused, cSPEditorBlock_s004a_1a70* block)
{
    if (block) {
        if (!block->GetBooleanAttribute(0x2a)) {
            void* ctx = FUN_00401060();
            if (ctx) {
                rwVec3 v(*(rwVec3*)&block->mField144);
                Alloc_s004a_1a70 al;
                BlockVec_s004a_1a70 vec(al);
                {
                    BlockRef_s004a_1a70 r(block);
                    vec.push_back(r);
                }
                BuildPileList(block, &vec, 0);
                for (int i = 0, n = vec.size(); i < n; i++) {
                    cSPEditorBlock_s004a_1a70* b = vec[i];
                    b->FUN_4a1d60((const cSPVector3_s004a_1a70*)&v);
                    b->SetBooleanAttribute(0x2a, true);
                    b->FUN_44ba20(0, 0);
                    if (b->mPinTarget) {
                        cSPEditorBlock_s004a_1a70* pin = b->mPinTarget;
                        pin->SetBooleanAttribute(0x2a, true);
                    }
                }
                if (block->mPinTarget) {
                    cSPEditorBlock_s004a_1a70* pin0 = block->mPinTarget;
                    v = *(rwVec3*)&pin0->mField144;
                    vec.DoDestroy(vec.mpBegin, vec.mpEnd);
                    {
                        BlockRef_s004a_1a70 r(pin0);
                        vec.push_back(r);
                    }
                    BuildPileList(pin0, &vec, 0);
                    for (int i = 0, n = vec.size(); i < n; i++) {
                        cSPEditorBlock_s004a_1a70* b = vec[i];
                        b->FUN_4a1d60((const cSPVector3_s004a_1a70*)&v);
                        b->SetBooleanAttribute(0x2a, true);
                        b->FUN_44ba20(0, 0);
                        if (b->mPinTarget) {
                            cSPEditorBlock_s004a_1a70* pin = b->mPinTarget;
                            pin->SetBooleanAttribute(0x2a, true);
                        }
                    }
                }
            }
            SetSymmetricBlocksUIState(block, 0, 0);
            FUN_4a6d20(block, 0, 0, 0, 0, 0, 1, 1);
        }
    }
}








// @ 0x004a1d60
void cSPEditorBlock_s004a_1a70::FUN_4a1d60(const cSPVector3_s004a_1a70* p)
{
    mField144 = *p;
    if (mPinTarget) {
        cSPVector3_s004a_1a70 v = *p;
        v[0] *= -1.0f;
        mPinTarget->mField144 = v;
    }
}








// @ 0x004a1e10
bool FUN_4a1e10(cSPEditorBlock_s004a_1a70* block)
{
    bool result = false;
    if (block->GetBooleanAttribute(0x2a)) {
        void* ctx = FUN_00401060();
        if (ctx) {
            BlockVec_s004a_1a70 vec;
            {
                BlockRef_s004a_1a70 r(block);
                vec.push_back(r);
            }
            BuildPileList(block, &vec, 0);
            if (block->mPinTarget) {
                cSPEditorBlock_s004a_1a70* pin0 = block->mPinTarget;
                {
                    BlockRef_s004a_1a70 r(pin0);
                    vec.push_back(r);
                }
                BuildPileList(pin0, &vec, 0);
            }
            for (int i = 0, n = vec.size(); i < n; i++) {
                cSPEditorBlock_s004a_1a70* b = vec[i];
                b->FUN_4a1d60(&kSnapZero);
                b->SetBooleanAttribute(0x2a, false);
                b->FUN_44bcf0(0, 0);
                if (b->mPinTarget) {
                    cSPEditorBlock_s004a_1a70* pin = b->mPinTarget;
                    pin->SetBooleanAttribute(0x2a, false);
                }
            }
        }
        if (!block->FUN_44c030())
            block->FUN_44bcf0(1, 1);
        SetSymmetricBlocksUIState(block, 0, 0);
        FUN_4a6d20(block, 0, 0, 0, 0, 0, 1, 1);
        MessageManager_s004a_1a70()->Post(0x3f1bf59, 0, block, 0);
        result = true;
    }
    return result;
}








// @ 0x004a2060
bool FUN_4a2060(cSPEditorBlock_s004a_1a70* block)
{
    if (block) {
        if (block->GetBooleanAttribute(7) || block->GetBooleanAttribute(0x14) || block->GetBooleanAttribute(1))
            return false;
        return true;
    } else {
        return false;
    }
}








// @ 0x004a2180
rwVec3* FUN_4a2180(rwVec3* ret, cSPEditorBlock_s004a_1a70* a, cSPEditorBlock_s004a_1a70* b)
{
    int i0, axis, i2;                             // axis is the 2nd out value
    b->FUN_44c0e0(&i0, &axis, &i2);
    BBox bbA;
    a->GetBBox(&bbA, 1, 0, 0);
    BlockVec_s004a_1a70 vec;
    BuildPileList(a, &vec, 0);
    for (int i = 0, n = vec.size(); i < n; i++) {
        BBox bbi;
        BBox* r = vec[i]->GetBBox(&bbi, 1, 0, 0);
        FUN_43f050(&bbA, r);
    }
    rwVec3 mn(bbA.mn);
    BBox bbB;
    b->GetBBox(&bbB, 1, 0, 0);
    rwVec3 mx(bbB.mx);
    rwVec3 d;
    d.x = 0.0f;
    d.y = 0.0f;
    d.z = 0.0f;
    d[axis] = (mn[axis] - mx[axis]) * kSnapScale;
    rwVec3 tmp;
    rwVec3* t = Mat3MulVec(&tmp, &d, &b->mOrientation);
    d.x = t->x;
    d.y = t->y;
    d.z = t->z;
    new (ret) rwVec3(d);
    return ret;
}








// @ 0x004a2350
bool FUN_4a2350(cSPEditorBlock_s004a_1a70* editor, cSPEditorBlock_s004a_1a70* src, rwVec3* outPos, float* outMat)
{
    bool result = false;
    if (src != 0) {
        *(Vector3T_s004a_1a70*)outPos = src->mPosition;
        *(Mat9*)outMat = *(Mat9*)src->mBaseOrientation;
        cSPEditorBlock_s004a_1a70* parent = src->GetParent();
        if (editor->mParent != parent) {
            if (editor->mParent) {
                editor->mParent->FUN_438a40(editor);
            }
            if (parent) {
                parent->FUN_438700(editor);
                editor->SetRef(src->GetA());
            }
        }
        editor->SetBooleanAttribute(0xf, src->GetBooleanAttribute(0xf));
        if (!src->GetBooleanAttribute(0x2a)) {
            MessageManager_s004a_1a70()->Post(0x3f1bf58, 0, editor, 0);
            rwVec3 d;
            src->FUN_4a1d60((const cSPVector3_s004a_1a70*)FUN_4a2180(&d, editor, src));
            FUN_4a1a70(editor, src);
        }
        result = true;
    } else {
        ScratchSlots<5>();
        bool changed = FUN_4a2560(editor->GetModel());
        if (changed)
            MessageManager_s004a_1a70()->Post(0x3f1bf59, 0, editor, 0);
        MessageServer_s004a_1a70()->Send(0x48e5912, 0, 0);
    }
    return result;
}








// @ 0x004a2560
bool FUN_4a2560(cSPEditorModel_s004a_1a70* model)
{
    bool result = 0;
    if (model) {
        int i = 0;
        int n = model->GetBlockCount();
        for (; i < n; i++) {
            cSPEditorBlock_s004a_1a70* b = model->GetBlock(i);
            bool block = FUN_4a1e10(b);
            result = block || result;
        }
    }
    return result;
}








// @ 0x004a25f0
rwMat3 FUN_4a25f0(rwMat3 m, int mode)
{
    rwMat3 result;
    rwVec3 up(m[1]);
    float a = (float)fabs((up.x * kUpAxis.x + up.y * kUpAxis.y) + up.z * kUpAxis.z);
    rwVec3 dir;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 0.0f;
    if (mode == 0) {
        static rwVec3 sNegX = Vec3Normalized(rwVec3(-1.0f, 0.0f, 0.0f));     // 0x015d60d8
        dir = sNegX;
    } else {
        static rwVec3 sPosX = Vec3Normalized(rwVec3(1.0f, 0.0f, 0.2f));      // 0x015d60cc
        static rwVec3 sNegX2 = Vec3Normalized(rwVec3(-1.0f, 0.0f, 0.2f));    // 0x015d60c0 (guard 0x015d60e4)
        rwVec3* p = (mode == 1) ? &sPosX : &sNegX2;
        rwVec3 base(*p);
        rwVec3 tmp;
        rwVec3* l = Vec3Lerp(&tmp, &base, &kBlendAxis, a);
        dir = *l;
    }
    rwVec3 tmp2;
    rwVec3 x(*Vec3Cross(&tmp2, &up, &dir));
    rwVec3 z;
    if (Vec3Length(&x) < kDegenerateEps) {
        rwVec3 t3;
        new (&x) rwVec3(*Vec3Negate(&t3, &kUpAxis));
        rwVec3 t4;
        new (&z) rwVec3(*Vec3Cross(&t4, &x, &up));
        rwVec3 t5;
        z = *Vec3Normalize(&t5, &z);
        rwVec3 t6;
        new (&up) rwVec3(*Vec3Cross(&t6, &z, &x));
    } else {
        rwVec3 t7;
        new (&z) rwVec3(*Vec3Cross(&t7, &x, &up));
        rwVec3 t8;
        z = *Vec3Normalize(&t8, &z);
    }
    rwVec3 t9;
    x = *Vec3Normalize(&t9, &x);
    result[0] = x;
    result[1] = up;
    result[2] = z;
    return result;
}








// @ 0x004a29a0
void SnapBlockToSocket(cSPEditorBlock_s004a_29a0* block, int unused, cSPEditorBlock_s004a_29a0* target)
{
    cSPEditorModel_s004a_29a0* model = block->mpEditorModel;
    cSPEditorBlockModel* blockModel = block->GetModel();
    bool unusedFlag = false;
    bool anyPaintable = false;
    float scale = 1.0f;
    if (target && target->mSocket) {
        BlockVec_s004a_29a0& children = target->mChildren;
        int count = 0;
        bool notify = false;
        for (int i = 0, n = children.size(); i < n; i++) {
            if (children[i]->mModel) {
                scale = children[i]->GetSnapScale();
                children[i]->SetVec194(children[i]->mPosition);
            }
            if (children[i]->GetBooleanAttribute(0xc)) {
                children[i]->mModel->SetState(1, 0);
                if (!children[i]->GetBooleanAttribute(0xb)) {
                    children[i]->FUN_44ba20(1, 1);
                    if (children[i]->GetBooleanAttribute(0x2d))
                        anyPaintable = true;
                    if (!children[i]->GetBooleanAttribute(0x14))
                        notify = true;
                    count += CountSnapBlocks(children[i], 1);
                }
            }
        }
        if (notify) {
            BlockSnapMessage msg;
            msg.mFlags = 0;
            msg[0].p = block;
            msg[1].p = target;
            msg[2].f = (float)count;
            MessageServer_s004a_29a0()->Send(0x48e5911, &msg, 0);
        }
        CountedRef<cCounted> socket(target->mSocket);
        target->PinBlock(block);
        block->RecursiveFlagA();
        block->SetBooleanAttribute(0xc, true);
        float delta = scale - block->GetSnapScale();
        if (block->mModel)
            UpdateModelPaint(block->mModel, delta);
        Vec3_s004a_29a0 offset = socket->mPosition - blockModel->GetPosition();
        Vec3_s004a_29a0 pos = socket.GetPosition();
        cSPMatrix3_s004a_29a0 orient(block->mBaseOrientation);
        bool mirror = false;
        if (block->GetBooleanAttribute(4)) {
            if (block->GetBooleanAttribute(0xb)) {
                if (!block->FUN_448c10()) {
                    cSPMatrix3_s004a_29a0 m(target->mOrientation);
                    if (target->GetBooleanAttribute(8)) {
                        cSPTransform_s004a_29a0 xf;
                        xf.SetRotation(m);
                        Vec3_s004a_29a0 axis;
                        axis.x = m.r[0].x;
                        axis.y = m.r[0].y;
                        axis.z = m.r[0].z;
                        xf.PreRotate(axis, kNegHalfPi);
                        m = xf.GetRotation();
                    }
                    orient = m;
                } else {
                    orient = block->mBaseOrientation;
                    mirror = true;
                }
            } else if (block->GetBooleanAttribute(0x2c)) {
                orient = BuildSymmetricOrientation(target->mOrientation, target->GetSymmetryIndex());
            } else {
                orient = target->mOrientation;
            }
        } else if (!block->GetBooleanAttribute(0xb)) {
            mirror = true;
            orient = block->mBaseOrientation;
        } else {
            mirror = true;
            orient = block->mBaseOrientation;
        }
        RepinBlockToTorso(block, pos, orient, 0);
        if (model->IsUsingSymmetry()) {
            int sign = block->CalculateSymmetrySign();
            if (sign != block->GetSymmetryIndex()) {
                bool mirrorOrientation = mirror;
                block->SetModelBasedOnSymmetrySign(sign, mirrorOrientation, true, 0, 0);
                blockModel = block->GetModel();
            }
        }
        MessageManager_s004a_29a0()->Post(0x3f1bf58, 0, block, 0);
        blockModel->SetState(1, 0);
        if (model->IsUsingSymmetry()) {
            cSPEditorBlock_s004a_29a0* pin = block->mPinTarget;
            if (pin && pin->mModel)
                pin->mModel->SetState(1, 0);
        }
        SetSymmetricBlocksUIState(block, 0, 0);
        if (target->GetBooleanAttribute(0xb) && FUN_4a7e60(target) && !FUN_4a7dd0(target)) {
            cSPEditorLimbStructure_s004a_29a0 limb;
            cSPEditorLimbStructure_s004a_29a0 pinLimb;
            limb.Init(block, 0, 0);
            limb.FUN_48c030();
            if (!block->FUN_435c80()) {
                pinLimb.Init(block->mPinTarget, 0, 0);
                pinLimb.FUN_48c030();
            }
            limb.FixAllJoints();
            limb.Rebuild();
            if (!block->FUN_435c80()) {
                pinLimb.FixAllJoints();
                pinLimb.Rebuild();
                pinLimb.FUN_488980();
            }
            limb.FUN_488980();
        }
        if (block->GetBooleanAttribute(10))
            block->SetBooleanAttribute(9, true);
        if (block->mParent && block->mParent->GetBooleanAttribute(10))
            block->mParent->SetBooleanAttribute(10, true);
    }
}







// @ 0x004a3760
void FUN_4a3760(int param, float* a, float* b)
{ (void)param; (void)a; (void)b; }






// @ 0x004a37f0
void FUN_4a37f0(cSPEditorBlock_s004a_3760* block)
{ (void)block; }






// @ 0x004a3920
void FUN_4a3920(cSPEditorBlock_s004a_3760* block)
{ (void)block; }






// @ 0x004a3c70
cSPEditorBlock_s004a_3760* FUN_4a3c70(cSPEditorBlock_s004a_3760* block)
{ (void)block; return 0; }






// @ 0x004a3dc0
cSPEditorBlock_s004a_3dc0* FUN_4a3dc0(cSPEditorBlock_s004a_3dc0* block, BlockVec_s004a_3dc0* exclude, Vec3_s004a_3dc0 origin, Vec3_s004a_3dc0 dir, Vec3_s004a_3dc0* outPos)
{
    cSPEditorModel_s004a_3dc0* model = block->mEditorModel;
    bool unusedFlag = false;
    if (block->mFlags.test(0x1f)) {
        if (block->mFlags.test(0xc)) {
            *outPos = block->mPos48;
            Vec3_s004a_3dc0 nrm;
            Vec3_s004a_3dc0* n = Vector3_Normalize(&nrm, &dir);
            Plane_s004a_3dc0 plane;
            Plane_s004a_3dc0 ptmp(n->operator[](0), n->operator[](1), n->operator[](2), -Dot3(&block->mPos48, n));
            plane = ptmp;
            float t;
            if (!IntersectRayPlane(&origin, &dir, &plane, &t))
                return block->GetField33c();
            Vec3_s004a_3dc0 s1, s2, s3;
            Vec3_s004a_3dc0 hit = *FUN_0041dc10(&s2, &origin, Vector3_Scale(&s1, &t, &dir));
            Vec3_s004a_3dc0 diff = *FUN_0041db10(&s3, &hit, &block->mPos48);
            if (VectorLength(&diff) > model->GetScale() * 0.067f)
                return 0;
            else
                return block->GetField33c();
        } else {
        cSPEditorBlock_s004a_3dc0* best = 0;
        float bestDist = 0.0f;
        int count = model->GetBlockCount();
        for (int i = 0; i < count; i++) {
            cSPEditorBlock_s004a_3dc0* other = model->GetBlock(i);
            RefPtr mdl(other->GetModel());
            bool ok = true;
            BlockVec_s004a_3dc0* kids = &other->mChildren;
            int nKids = (int)(kids->mpEnd - kids->mpBegin);
            for (int j = 0; j < nKids; j++) {
                if ((*kids)[j]->mFlags.test(0xb)) {
                    if (block->mFlags.test(0x2c) || block->mFlags.test(0x2d))
                        ok = false;
                }
            }
            bool ok2 = true;
            if (block->mFlags.test(0xa)) {
                if (!other->mFlags.test(0xa) && !other->mFlags.test(8))
                    ok2 = false;
            }
            if (ok2 && other != block && mdl.p && FUN_0044c030(other) && ok) {
                cSPEditorBlock_s004a_3dc0** it = exclude->mpBegin;
                while (it != exclude->mpEnd && *it != other) it++;
                if (it == exclude->mpEnd) {
                    cSPEditorBlock_s004a_3dc0* parent = other->mParent;
                    bool proceed = false;
                    if (!model->FUN_4adc40() || !parent) {
                        proceed = true;
                    } else {
                        cSPEditorBlock_s004a_3dc0** it2 = exclude->mpBegin;
                        while (it2 != exclude->mpEnd && *it2 != parent) it2++;
                        if (it2 == exclude->mpEnd && parent != block) proceed = true;
                    }
                    if (proceed) {
                        Vec3_s004a_3dc0 nrm;
                        Vec3_s004a_3dc0* n = Vector3_Normalize(&nrm, &dir);
                        Plane_s004a_3dc0 plane;
                        Plane_s004a_3dc0 ptmp(n->operator[](0), n->operator[](1), n->operator[](2), -Dot3(mdl.p->GetPos(), n));
                        plane = ptmp;
                        float t;
                        if (IntersectRayPlane(&origin, &dir, &plane, &t)) {
                            Vec3_s004a_3dc0 s1, s2, s3, s4;
                            Vec3_s004a_3dc0 hit = *FUN_0041dc10(&s2, &origin, Vector3_Scale(&s1, &t, &dir));
                            Vec3_s004a_3dc0 diff = *FUN_0041db10(&s3, &hit, mdl.p->GetPos());
                            if (VectorLength(&diff) < model->GetScale() * 0.043f) {
                                Vec3_s004a_3dc0 diff2 = *FUN_0041db10(&s4, &hit, &origin);
                                float dist = VectorLength(&diff2);
                                if (!best || dist < bestDist) {
                                    best = other;
                                    bestDist = dist;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (best) {
            RefPtr m(best->GetModel());
            *outPos = *m.p->GetPos();
            return best;
        }
        }
    }
    return 0;
}





// @ 0x004a4840
void* PickBlocks(PickVec* blocks, Vec3_s004a_3dc0 origin, Vec3_s004a_3dc0 dir, int a24, int a28, int a2c, bool* outFlag, int* pState)
{
    if (!GetResourceTypeFromModelType_(blocks)) {
        *outFlag = false;
        PickBlock* first = (*blocks)[0];
        IModelWorld* world = first->GetWorld();
        IModelManager* mm = ModelManager();
        if (mm && world) {
            bool hasState = false;
            int state = 4;
            if (pState) { hasState = true; state = *pState; }
            uint32_t id = mm->GetTypeBit(0x2cdfcbd, 0);
            int count = (int)(blocks->mpEnd - blocks->mpBegin);
            for (int i = 0; i < count; i++) {
                PickBlock* b = (*blocks)[i];
                if (b->GetModel()) {
                    ((BitsBase*)(b->GetModel()->mBits))->set(id, true);
                }
                b->SetNodeStateChecked(state, hasState);
            }
            cSPEditorPickInfo filter;
            filter.m0.set(id, true);
            filter.m15 |= 1;
            float scale = 1000.0f;
            Vec3_s004a_3dc0 end = *FUN_0041dc10(&end, &origin, Vector3_Scale(&end, &scale, &dir));
            uint32_t extra[1];
            PickHit* hit = world->Raycast(&origin, &end, 0, a24, a28, &filter, (char*)extra, a2c);
            void* result = 0;
            if (hit && hit->mPtr64) {
                result = InterfaceCast(&hit->mPtr64);
                if (result && hit->mKind == 2) *outFlag = true;
            }
            for (int i = 0; i < count; i++) {
                PickBlock* b = (*blocks)[i];
                if (b->GetModel()) {
                    ((BitsBase*)(b->GetModel()->mBits))->set(id, false);
                }
                b->ClearNodeState();
            }
            return result;
        }
    }
    return 0;
}





// @ 0x004a4c70
cSPEditorPickInfo::cSPEditorPickInfo()
{
    m10 = 0;
    m14 = 0;
    m15 = 0;
}





// @ 0x004a4cf0
cSPEditorBlock_s004a_3dc0* FUN_4a4cf0(cSPEditorModel_s004a_3dc0* model, int id)
{
    if (model && (unsigned)model->GetBlockCount() > 0) {
        int tmp = 0;
        int t14 = model->GetBlockCount();
        cSPEditorBlock_s004a_3dc0* block;
        for (; tmp < t14; tmp++) {
            block = model->GetBlock(tmp);
            int field = *(int*)((char*)block + 0x18c);
            if (field == id) return block;
        }
    }
    return 0;
}





// @ 0x004a5a70
namespace SP { namespace EditorUtils {
cSPEditorBlock_s004a_5970* FindRootSpine(cSPEditorModel_s004a_5970* model)
{
    for (int i = 0, n = model->GetBlockCount(); i < n; i++) {
        cSPEditorBlock_s004a_5970* block = model->GetBlock(i);
        if (block && block->mFlags.test(7) && !block->GetParent())
            return block;
    }
    return 0;
}
}}  // namespace SP::EditorUtils




// @ 0x004a5b70
namespace SP {
namespace EditorUtils {
float GetExactSkinRadiusFromVertebra(float scale)
{
    float t14 = 0.70710677f;
    float tmp = scale * 0.37802768f * 0.7f * 1.2f * t14;
    if (0.04f > tmp) tmp = 0.04f;
    return tmp;
}
}
}  // namespace SP::EditorUtils




// @ 0x004a5bd0
namespace SP { namespace EditorUtils {
float GetExactSkinRadius(cSPEditorBlock_s004a_5970* block)
{
    return GetExactSkinRadiusFromVertebra(block->GetScale());
}
}}  // namespace SP::EditorUtils




// @ 0x004a5c00
namespace SP { namespace EditorUtils {
float GetSkinRadiusFromVertebra(float scale)
{
    float r = scale * 0.37802768f * 0.7f;
    if (0.04f > r) r = 0.04f;
    return r;
}
}}  // namespace SP::EditorUtils




// @ 0x004a5c40
namespace SP { namespace EditorUtils {
float GetSkinRadius(cSPEditorBlock_s004a_5970* block)
{
    return GetSkinRadiusFromVertebra(block->GetScale());
}
}}  // namespace SP::EditorUtils




// @ 0x004a5c70
namespace SP { namespace EditorUtils {
cSPVector3_s004a_5970 GetSkinPoint(const cSPVector3_s004a_5970& pos, const cSPVector3_s004a_5970& dir, float scale)
{
    float t = -0.15993178f * scale;
    cSPVector3_s004a_5970 r = pos + dir * t;
    return r;
}
}}  // namespace SP::EditorUtils




// @ 0x004a5d10
namespace SP { namespace EditorUtils {
cSPVector3_s004a_5970 GetSkinTip(cSPEditorBlock_s004a_5970* block)
{
    cSPVector3_s004a_5970 pos = block->mPosition;
    cSPVector3_s004a_5970 dir = block->mOrientation.GetRow(2);
    return GetSkinPoint(pos, dir, block->GetScale());
}
}}  // namespace SP::EditorUtils




// @ 0x004a5db0
namespace SP { namespace EditorUtils {
cSPEditorBlock_s004a_5970* GetRootBlock(cSPEditorBlock_s004a_5970* block)
{
    if (!block) return 0;
    else {
        cSPEditorBlock_s004a_5970* p = block->GetParent();
        if (!p) p = block;
        else {
            while (p->GetParent()) p = p->GetParent();
        }
        return p;
    }
}
}}  // namespace SP::EditorUtils




// @ 0x004a5e10
namespace SP { namespace EditorUtils {
cSPEditorBlock_s004a_5970* GetLimbRoot(cSPEditorBlock_s004a_5970* block)
{
    if (!block) return 0;
    else {
        cSPEditorBlock_s004a_5970* p = block->GetParent();
        if (!p || (!p->mFlags.test(0xb) && !p->mFlags.test(8))) p = block;
        else {
            while (p->GetParent() && (p->GetParent()->mFlags.test(0xb) || p->GetParent()->mFlags.test(8)))
                p = p->GetParent();
        }
        return p;
    }
}
}}  // namespace SP::EditorUtils




// @ 0x004a5fe0
namespace SP { namespace EditorUtils {
bool HasSymmetricLimb(cSPEditorBlock_s004a_5970* block)
{
    if (block) {
        vector_s004a_5970<AutoRefCount_s004a_5970<cSPEditorBlock_s004a_5970> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            if (syms[i]->mFlags.test(0xb))
                return true;
        }
    }
    return false;
}
}}  // namespace SP::EditorUtils




// @ 0x004a60a0
namespace SP { namespace EditorUtils {
bool AreInSameLimb(cSPEditorBlock_s004a_5970* a, cSPEditorBlock_s004a_5970* b)
{
    if (!a || !b) return false;
    if (IsLimbConnected(a) && IsLimbConnected(b)) {
        cSPEditorBlock_s004a_5970* ra = GetLimbRoot(a);
        cSPEditorBlock_s004a_5970* rb = GetLimbRoot(b);
        return ra == rb;
    } else {
        return false;
    }
}
}}  // namespace SP::EditorUtils




// @ 0x004a6120
namespace SP { namespace EditorUtils {
bool IsLimbConnected(cSPEditorBlock_s004a_5970* block)
{
    if (block && block->mFlags.test(8)) return true;
    if (!block || !block->mFlags.test(0x1f)) return false;
    if (block->mFlags.test(0xb)) return true;
    else if (block->GetParent() != block) return IsLimbConnected(block->GetParent());
    else return false;
}
}}  // namespace SP::EditorUtils




// @ 0x004a6270
namespace SP { namespace EditorUtils {
bool IsLimbPart(cSPEditorBlock_s004a_5970* block)
{
    if (!block) return false;
    if (block->mFlags.test(0xb)) return true;
    else if (block->GetParent() != block) return IsLimbPart(block->GetParent());
    else return false;
}
}}  // namespace SP::EditorUtils




// @ 0x004a6310
namespace SP { namespace EditorUtils {
cSPEditorBlock_s004a_5970* GetSymmetryRoot(cSPEditorBlock_s004a_5970* block)
{
    if (!block || !block->GetParent()) return block;
    if (block->GetUIState() || !block->GetSymmetryCount()) return block;
    else if (block->GetParent()->GetUIState() || !block->GetParent()->GetSymmetryCount()) return block;
    else return GetSymmetryRoot(block->GetParent());
}
}}  // namespace SP::EditorUtils




// @ 0x004a63c0
namespace SP { namespace EditorUtils {
void RebuildSkins(cSPEditorBlock_s004a_5970* block, cSkinOwner* owner)
{
    if (block && (block->mSkin || block->mFlags.test(8))) {
        if (block->mSkin) {
            if (!SkinUsesModel(block->mSkin, owner))
                (*block->mSkin).Rebuild(3, 1);
        }
        vector_s004a_5970<AutoRefCount_s004a_5970<cSPEditorBlock_s004a_5970> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            cSPEditorBlock_s004a_5970* sym = syms[i];
            if (sym) RebuildSkins(sym, owner);
        }
    }
}
}}  // namespace SP::EditorUtils




// @ 0x004a6520
namespace SP { namespace EditorUtils {
void RefreshSkins(cSPEditorBlock_s004a_5970* block, cSPEditorBlock_s004a_5970* except)
{
    if (block && (block->mSkin || block->mFlags.test(8))) {
        if (except != block && block->mSkin)
            block->mSkin.get()->Rebuild(1, 1);
        vector_s004a_5970<AutoRefCount_s004a_5970<cSPEditorBlock_s004a_5970> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            cSPEditorBlock_s004a_5970* sym = syms[i];
            if (sym) RefreshSkins(sym, except);
        }
    }
}
}}  // namespace SP::EditorUtils




// @ 0x004a6640
namespace SP { namespace EditorUtils {
void RebuildLimbSkins(cSPEditorBlock_s004a_5970* block, cSkinOwner* owner)
{
    RebuildSkins(GetLimbRoot(block), owner);
}
}}  // namespace SP::EditorUtils




// @ 0x004a6660
namespace SP { namespace EditorUtils {
void RefreshLimbSkins(cSPEditorBlock_s004a_5970* block, bool includeSelf)
{
    cSPEditorBlock_s004a_5970* except = includeSelf ? block : 0;
    RefreshSkins(GetLimbRoot(block), except);
}
}}  // namespace SP::EditorUtils




// @ 0x004a6690
void AssignCollisionGroups(cSPEditorBlock_s004a_6690* block, BlockVector_s004a_6690* list, int grpAll, int grpSel, bool floorAll)
{
    AutoRefCount_s004a_6690<cSPEditorModel_s004a_6690> model(block->GetEditorModel());
    if (model) {
        bool symmetry = model->FUN_4adc40();
        for (int i = 0, size = model->GetBlockCount(); i < size; i++) {
            cSPEditorBlock_s004a_6690* b = model->GetBlock(i);
            b->SetCollisionGroup(grpAll);
        }
        int nBlocks = list->size();
        for (int j = 0; j < nBlocks; j++) {
            (*list)[j]->SetCollisionGroup(grpSel);
            if (symmetry && (*list)[j]->GetSymmetricBlock())
                (*list)[j]->GetSymmetricBlock()->SetCollisionGroup(grpSel);
        }
        block->SetCollisionGroup(grpAll);
        if (symmetry && block->GetSymmetricBlock()) {
            block->GetSymmetricBlock()->SetCollisionGroup(grpSel);
            FixedBlockVectorInl mirror;
            GetSymmetricPile(block->GetSymmetricBlock(), (BlockVector_s004a_6690*)&mirror, true);
            for (int k = 0, n = mirror.size(); k < n; k++) {
                cSPEditorBlock_s004a_6690* item = mirror[k];
                item->SetCollisionGroup(grpSel);
            }
        }
        FixedBlockVector_s004a_6690 ownPile;
        GetSymmetricPile(block, &ownPile, true);
        for (int k = 0, n = ownPile.size(); k < n; k++)
            ownPile[k]->SetCollisionGroup(grpSel);
        for (int i = 0, size = model->GetBlockCount(); i < size; i++) {
            cSPEditorBlock_s004a_6690* other = model->GetBlock(i);
            if (block != other && !block->HasRelevantPoints2(other)) {
                bool isFlag7;
                isFlag7 = other->IsFlagSet(7);
                bool onlyPin = !isFlag7 && other->mFlags.test(11);
                int skinId = block->GetSkinIdentifierForPicking();
                bool skin01 = (skinId == 1 || skinId == 0);
                bool isSkin = skinId == 1;
                if (skin01 && isFlag7) {
                } else if (onlyPin && isSkin) {
                } else {
                    other->SetCollisionGroup(grpSel);
                }
            }
        }
        if (floorAll)
            model->GetPhysicsWorld()->SetFloorFilter(grpAll);
        else
            model->GetPhysicsWorld()->SetFloorFilter(grpSel);
        model->GetPhysicsWorld()->UpdateCollisionFilters();
        ScratchSlots<8>();
    }
}



// @ 0x004a6ca0
void FUN_4a6ca0(cSPEditorModel_s004a_6690* model, int value)
{
    bool saved = model->FUN_4adc40();
    model->FUN_4adc20(0);
    int t14 = 0;
    int tmp = model->GetBlockCount();
    for (; t14 < tmp; t14++) {
        cSPEditorBlock_s004a_6690* block = model->GetBlock(t14);
        block->SetValid(block->FUN_43fc20(0, value));
    }
    model->FUN_4adc20(saved);
}



// @ 0x004a6d20
void FUN_4a6d20(cSPEditorBlock_s004a_6690* block)
{ (void)block; }



// @ 0x004a6f10
namespace SP { namespace EditorUtils {
void DeleteInvalidBlocks(cSPEditorBlock_s004a_6f10* block)
{
    AutoRefCount_s004a_6f10<cSPEditorModel_s004a_6f10> model(block->GetEditorModel());
    if (model) {
        bool usingSymmetry = model->IsUsingSymmetry();
        model.mpObject->SetUsingSymmetry(false);

        // 1. Mark invalid blocks, and the partners of symmetric blocks, for deletion.
        int numBlocks = model->GetBlockCount();
        bool partnerOfBlock = false;
        for (int i = 0; i < numBlocks; i++) {
            cSPEditorBlock_s004a_6f10* b = model->GetBlock(i);
            if (!b->IsValid())
                b->SetBooleanAttribute(1, true);
            if (b->mFlags.test(11) && !b->mFlags.test(1) && b->GetSymmetryHandle() &&
                b->GetSymmetryIndex() == 0.0 && b->GetSymmetricBlock()) {
                b->GetSymmetricBlock()->SetBooleanAttribute(1, true);
                if (b->GetSymmetricBlock() == block)
                    partnerOfBlock = true;
            }
        }

        // 2. Collect the marked blocks; move the children of a deleted block to its partner.
        bool deletedAny = false;
        int totalCost = 0;
        BlockVector_s004a_6f10 kept;
        BlockVector_s004a_6f10 doomed;
        numBlocks = model->GetBlockCount();
        for (int i = 0; i < numBlocks; i++) {
            cSPEditorBlock_s004a_6f10* b = model->GetBlock(i);
            if (b->mFlags.test(1)) {
                doomed.push_back(BlockRef_s004a_6f10(b));
                if (b->GetSymmetryIndex() == 0.0f && b->GetSymmetricBlock() &&
                    !b->GetSymmetricBlock()->mFlags.test(1)) {
                    FixedBlockVector children;
                    children = b->mChildren;
                    for (int j = 0, numChildren = children.size(); j < numChildren; j++) {
                        b->GetSymmetricBlock()->AttachChild(children[j]);
                        if (!b->GetSymmetricBlock()->mFlags.test(10)) {
                            Vector3T_s004a_6f10 offsetA = children[j]->GetOffsetA(true);
                            Vector3T_s004a_6f10 offsetB = children[j]->GetOffsetB(true);
                            children[j]->Place(offsetA, offsetB);
                        }
                    }
                }
            }
        }

        // 3. Delete them.
        numBlocks = doomed.size();
        model.mpObject->SetUsingSymmetry(false);
        Vector3T_s004a_6f10 centerSum(kZeroVector);
        float sizeSum = 0.0f;
        for (int k = 0; k < numBlocks; k++) {
            cSPEditorBlock_s004a_6f10* b = doomed[k];
            bool counted = true;
            if (b->mFlags.test(20) || find_s004a_6f10(kept.begin(), kept.end(), b) != kept.end() ||
                (b->GetSymmetricBlock() && !b->GetSymmetricBlock()->mFlags.test(1)))
                counted = false;
            if (counted) {
                int cost = 0;
                if (b->IsSymmetryLocked()) {
                    if (b->GetPairedBlock()) {
                        if (find_s004a_6f10(doomed.begin(), doomed.end(), b->GetPairedBlock()) != doomed.end()) {
                            kept.push_back(BlockRef_s004a_6f10(b->GetPairedBlock()));
                            cost = b->GetCost();
                        }
                    } else {
                        cost = b->GetCost();
                    }
                } else {
                    cost = b->GetCost();
                }
                totalCost += cost;
                deletedAny = true;
                if (b->GetSymmetricBlock())
                    kept.push_back(BlockRef_s004a_6f10(b->GetSymmetricBlock()));

                BoundingBox_s004a_6f10 bbox = b->GetBBox(0, 0, 0);
                cSPVector3_s004a_6f10 diagonal = bbox.mMax - bbox.mMin;
                float size = VectorLength(diagonal);
                centerSum += size * bbox.GetCenter();
                sizeSum += size;
            }
            uint32_t messageId = 0x7f18f481;
            MessageParam params[1];
            params[0].p = b;
            MessageServer()->SendMessage(messageId, params, 0);
            MessageManager()->RemoveListener(b);
            model.mpObject->RemoveBlock(b, false);
        }

        if (deletedAny) {
            cSPVector3_s004a_6f10 center = centerSum / sizeSum;
            MessageParam params[4];
            int unused = 0;
            params[0].i = totalCost;
            params[1].f = center[0];
            params[2].f = center[1];
            params[3].f = center[2];
            MessageServer()->SendMessage(0xf058b0f2, params, 0);
        }
        model.mpObject->SetUsingSymmetry(usingSymmetry);
    }
}
}}  // namespace SP::EditorUtils




































// @ 0x004a7c30
bool SameKey(ResKeySource* a, ResKeySource* b)
{
    Key first = a->GetKey(-1, 0);
    Key src = b->GetKey(-1, 0);
    return first.mInstance == src.mInstance
        && first.mType == src.mType
        && first.mGroup == src.mGroup;
}




































// @ 0x004a7c90
void GatherBlocks(cSPEditorBlock_s004a_7c30* param_1, UIntVector* param_2)
{
    if (param_1 == 0) return;
    cSPEditorModel_s004a_7c30* model = param_1->mEditorModel;
    if (model == 0) return;
    int i = 0;
    int count = model->GetBlockCount();
    for (; i < count; ++i) {
        cSPEditorBlock_s004a_7c30* blk = model->GetBlock(i);
        if (blk == 0 || blk == param_1) continue;
        if (!SameKey((ResKeySource*)blk, (ResKeySource*)param_1)) continue;
        param_2->push_back((uint32_t)blk);
        if (!model->FUN_004adc40()) continue;
        uint32_t v = (uint32_t)blk->mLinked;
        if (v == 0) continue;
        uint32_t* it = param_2->mpBegin;
        uint32_t* end = param_2->mpEnd;
        while (it != end && *it != v) ++it;
        if (it == end) {
            param_2->push_back(v);
        }
    }
}




































// @ 0x004a7dd0
bool EntHasFlag(cSPEditorBlock_s004a_7c30* e)
{
    if (e != 0) { if (e->IsFlagSet(8)) { return true; } else { return EntHasFlag(e->GetParent()); } }
    else { return false; }
}




































// @ 0x004a7e60
bool BlockBlocked(cSPEditorBlock_s004a_7c30* b)
{
    if (b != 0) {
        bool r = b->HasAnyBlockFlag();
        if (r == false) r = FUN_004986d0(b);
        return r;
    }
    else {
        return false;
    }
}




































// @ 0x004a7ea0
bool AdjacentDir(int a, int b, unsigned char flipped)
{
    if (flipped != 0) return a != b;
    bool result = false;
    if ((a == -1) && (b == 0)) { }
    else if ((a == -1) && (b == 1)) result = true;
    else if ((a == 0) && (b == 1)) result = true;
    else if ((a == 0) && (b == -1)) { }
    else if ((a == 1) && (b == 0)) result = true;
    else if ((a == 1) && (b == -1)) result = true;
    return result;
}




































// @ 0x004a7f30
void SetSymmetricBlocksUIState(cSPEditorBlock_s004a_7c30* b, unsigned int param_2, unsigned char p3)
{
    if (b->GetModel() != 0 && b->GetModel()->FUN_004adc40() && !b->IsFlagSet(0x39)) {
        int item = b->CalculateSymmetrySign();
        cSPEditorBlock_s004a_7c30* p13 = b->GetParent2();
        if (b->IsFlagSet(0x23)) {
            int tmp = b->F44c050();
            bool t14 = false;
            if (tmp == 0) { if (item == 0) t14 = true; }
            else t14 = true;
            if (t14) {
                if (b->GetLinked() != 0 && b->GetLinked()->F44c030())
                    b->GetLinked()->F44ba20(0, 0);
            } else {
                if (b->GetLinked() != 0 && !b->GetLinked()->F44c030() && !b->IsFlagSet(0x3a))
                    b->GetLinked()->F44bcf0(0, 0);
            }
        } else if (!BlockBlocked(b)) {
            if (b->GetLinked() != 0 && b->GetLinked()->F44c030())
                b->GetLinked()->F44ba20(0, 0);
            BlockVec_s004a_7c30 v((Alloc()));
            FUN_0049dd20(b, &v, 1);
            for (int block = 0, mem = v.size(); block < mem; ++block) {
                if (b->F44c030()) v[block]->F44bcf0(0, 0);
                else v[block]->F44ba20(0, 0);
            }
            v.erase(v.mpBegin, v.mpEnd);
            FUN_0049dd20(b->GetLinked(), &v, 1);
            for (int block = 0, mem = v.size(); block < mem; ++block) {
                if (b->GetLinked()->F44c030()) v[block]->F44bcf0(0, 0);
                else v[block]->F44ba20(0, 0);
            }
            ScratchSlots<2>();
        } else if (item == 0) {
            if (b->GetLinked() != 0) {
                bool h = b->IsFlagSet(0xb);
                bool p33 = false;
                void* elem = b->GetPropList();
                GetBoolProperty(elem, 0x7bd0ca3e, &p33);
                ScratchSlots<3>();
                if (!p33 && (!h || !p3)) {
                    if (b->F44c030()) {
                        b->GetLinked()->F44ba20(0, 0);
                        BlockVec_s004a_7c30 w((Alloc()), 0);
                        FUN_0049dd20(b->GetLinked(), &w, 1);
                        for (int block = 0, mem = w.size(); block < mem; ++block) {
                            if (w[block].get() != 0 && !w[block]->F44c030())
                                w[block]->F44bcf0(0, 0);
                        }
                        ScratchSlots<2>();
                    }
                } else {
                    if (b->F44c030() && !b->GetLinked()->F44c030() && !b->IsFlagSet(0x3a))
                        b->GetLinked()->F44bcf0(0, 0);
                }
            }
        } else {
            if (b->GetLinked() != 0) {
                if (b->F44c030()) {
                    if (!b->GetLinked()->F44c030() && !b->IsFlagSet(0x3a)) {
                        b->GetLinked()->F44bcf0(0, 0);
                    } else {
                        if (b->IsFlagSet(0x3a) && b->GetLinked()->F44c030())
                            b->GetLinked()->F44ba20(0, 0);
                    }
                } else if (b->GetLinked()->F44c030()) {
                    b->F44bcf0(0, 0);
                }
            }
        }
        BlockVec_s004a_7c30* t7 = &b->mChildren;
        for (int block = 0, mem = t7->size(); block < mem; ++block)
            SetSymmetricBlocksUIState((*t7)[block].get(), 0, p3);
    }
}




































// @ 0x004a8860
void ReleaseRefs(RefObj_s004a_7c30* b, UIntVector* list)
{
    if (b != 0) {
        b->SetRef(0);
        if (list != 0) {
            int n = list->mpEnd - list->mpBegin;
            for (int i = 0; i < n; ++i) {
                uint32_t& elem = list->mpBegin[i];
                RefObj_s004a_7c30* ptr = (RefObj_s004a_7c30*)elem;
                ptr->SetRef(0);
            }
        }
    }
}




































// @ 0x004a88d0
void KillSeti(int arg)
{
    int a;
    int b;
    KillSetiEffects(arg, GetRecorderState());
}




































// @ 0x004a88f0
bool PostXformEffect(unsigned int id, char* src, void** out)
{
    void* handle = 0;
    EffectsManager* mgr = GetEffectsManager();
    bool ok = ((bool(__thiscall*)(void*, unsigned int, int, void**))VSlot(mgr, 0x2c))(mgr, id, 0, &handle);
    if (!ok) return false;
    XformMsg msg;
    if (src != 0) {
        msg.mPos = *(Vec3_s004a_7c30*)(src + 0x48);
        for (int i = 0; i < 9; ++i)
            msg.mMat.m[i] = ((float*)(src + 0x60))[i];
        msg.mFlags |= 4;
        msg.mCount = (uint16_t)(msg.mCount + 1);
        msg.mFlags |= 2;
        msg.mCount = (uint16_t)(msg.mCount + 1);
        ((void(__thiscall*)(void*, void*))VSlot(handle, 0x18))(handle, &msg);
    }
    ((void(__thiscall*)(void*, int))VSlot(handle, 8))(handle, 0);
    if (out != 0) *out = handle;
    else ((void(__thiscall*)(void*))VSlot(handle, 4))(handle);
    return true;
}



































// @ 0x004a89e0
void* BuildSomeMatrix(void* param_1, void* param_2, void* param_3)
{
    float v0[3], v1[3], v2[3], v3[3], v4[3], v5[3], v6[3], v7[3];
    char b1[12], b2[12];
    void* q = FUN_00422020(b1, param_2);
    v0[0] = ((float*)q)[0]; v0[1] = ((float*)q)[1]; v0[2] = ((float*)q)[2];
    FUN_004098a0(param_3);
    q = FUN_0044e460(b2, v0, v1);
    v2[0] = ((float*)q)[0]; v2[1] = ((float*)q)[1]; v2[2] = ((float*)q)[2];
    if ((double)0.005 <= FUN_0040ae50(v2)) {
        // best effort placeholder
    }
    FUN_00449cc0(v7);
    (void)v3; (void)v4; (void)v5; (void)v6;
    return param_1;
}


// @ 0x004a8d70
M3::M3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    m[0].x = a; m[0].y = b; m[0].z = c;
    m[1].x = d; m[1].y = e; m[1].z = f;
    m[2].x = g; m[2].y = h; m[2].z = i;
}


// @ 0x004a8e10
void* BuildFacingMatrix(void* param_1, void* param_2, unsigned char param_3)
{
    float f1[3];
    float u1[3];
    char buf1[12];
    char buf2[12];
    float* a = (float*)UncheckedIdl0(buf1, (void*)0x015d63f4, param_2);
    f1[0] = a[0]; f1[1] = a[1]; f1[2] = a[2];
    float* b = (float*)UncheckedIdl0(buf2, (void*)0x015d6324, param_2);
    u1[0] = b[0]; u1[1] = b[1]; u1[2] = b[2];
    if (param_3 == 0) {
        *(uint32_t*)&f1[0] ^= 0x80000000u;
        *(uint32_t*)&u1[0] ^= 0x80000000u;
    }
    else {
        *(uint32_t*)&f1[2] ^= 0x80000000u;
        *(uint32_t*)&u1[2] ^= 0x80000000u;
    }
    Matrix3FromFacingAndUp(param_1, f1, u1);
    return param_1;
}


// @ 0x004a8f40
V3_s004a_89e0* NegateX(V3_s004a_89e0* param_1, V3_s004a_89e0* param_2)
{
    V3_s004a_89e0 v;
    v.x = param_2->x;
    v.y = param_2->y;
    v.z = param_2->z;
    v[0] *= -1.0f;
    param_1->x = v.x;
    param_1->y = v.y;
    param_1->z = v.z;
    return param_1;
}


// @ 0x004a8fc0
void TransposeInto(float* param_1, float* param_2)
{
    float v1 = param_1[1];
    float v2 = param_1[2];
    float v3 = param_1[3];
    float v4 = param_1[4];
    float v5 = param_1[5];
    float v6 = param_1[6];
    float v7 = param_1[7];
    float v8 = param_1[8];
    param_2[0] = param_1[0];
    param_2[1] = v1;
    param_2[2] = v2;
    param_2[3] = 0.0f;
    param_2[4] = v3;
    param_2[5] = v4;
    param_2[6] = v5;
    param_2[7] = 0.0f;
    param_2[8] = v6;
    param_2[9] = v7;
    param_2[10] = v8;
    param_2[11] = 0.0f;
}


// @ 0x004a92c0
void HavokAlignedRoutine(void* param_1, void* param_2)
{
    (void)param_1;
    (void)param_2;
}


// @ 0x004a9610
void ConvertToMatrix(void* param_1, void* param_2)
{
    float f[4];
    float* p = (float*)param_1;
    f[0] = p[0]; f[1] = p[1]; f[2] = p[2]; f[3] = p[3];
    char tmp[36];
    void* m = FUN_004a9b40(tmp, f);
    char out[36];
    Matrix3Assign(out, m);
    float* src = (float*)out;
    float* dst = (float*)param_2;
    for (int i = 0; i < 9; ++i) dst[i] = src[i];
}


// @ 0x004a96d0
bool AllChildrenNoFlag(cSPEditorBlock_s004a_89e0* param_1)
{
    if (param_1 == 0) return false;
    if (!param_1->IsFlagSet(0xb)) return false;
    BlockVec_s004a_89e0& v = param_1->mChildren;
    int i = 0;
    int n = v.mpEnd - v.mpBegin;
    for (; i < n; ++i) {
        cSPEditorBlock_s004a_89e0* elem = v.mpBegin[i];
        if (elem->IsFlagSet(0xb) || elem->IsFlagSet(0xc)) return false;
    }
    return true;
}


// @ 0x004a9840
cSPEditorBlock_s004a_89e0* GetFirstFootBlock(cSPEditorBlock_s004a_89e0* param_1)
{
    if (param_1 == 0) return 0;
    if (param_1->IsFlagSet(0x2d)) return param_1;
    BlockVec_s004a_89e0& v = param_1->mChildren;
    int i = 0;
    int n = v.mpEnd - v.mpBegin;
    for (; i < n; ++i) {
        cSPEditorBlock_s004a_89e0* elem = v.mpBegin[i];
        cSPEditorBlock_s004a_89e0* r = GetFirstFootBlock(elem);
        if (r != 0) return r;
    }
    return 0;
}


// @ 0x004a9920
namespace SP { namespace EditorUtils {
cSPEditorBlock_s004a_9920* FindSymmetricFoot(cSPEditorBlock_s004a_9920* block)
{
    if (!block) return 0;
    if (block->mFlags.test(0x2c)) return block;
    else {
        vector_s004a_9920<AutoRefCount_s004a_9920<cSPEditorBlock_s004a_9920> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            cSPEditorBlock_s004a_9920* found = FindSymmetricFoot(syms[i]);
            if (found) return found;
        }
        return 0;
    }
}
}}  // namespace SP::EditorUtils

// @ 0x004a9a00
namespace SP { namespace EditorUtils {
cSPEditorBlock_s004a_9920* FindSymmetricSkinnedPart(cSPEditorBlock_s004a_9920* block)
{
    if (IsSkinnedPart(block)) return block;
    else {
        vector_s004a_9920<AutoRefCount_s004a_9920<cSPEditorBlock_s004a_9920> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            cSPEditorBlock_s004a_9920* found = FindSymmetricSkinnedPart(syms[i]);
            if (found) return found;
        }
        return 0;
    }
}
}}  // namespace SP::EditorUtils

// @ 0x004a9a90
namespace SP {
bool KeyMatches(const ResourceKey_s004a_9920& key, const ResourceKey_s004a_9920& pattern)
{
    if (key.mInstanceID != pattern.mInstanceID) return false;
    if (pattern.mGroupID && key.mGroupID != pattern.mGroupID) return false;
    if (pattern.mTypeID && key.mTypeID != pattern.mTypeID) return false;
    return true;
}
}  // namespace SP

// @ 0x004a9ae0
namespace SP {
template<> AutoRefCountR<cRefCountedResource>::~AutoRefCountR()
{
    if (mpObject) mpObject->mRef.Release();
    ScratchSlots<3>();
}
}  // namespace SP

// @ 0x004a9b10
namespace SP {
template<> AutoRefCountV<cVirtualRefCounted>::~AutoRefCountV()
{
    if (mpObject) mpObject->Release();
}
}  // namespace SP

// @ 0x004a9b40
namespace SP {
Matrix33T_s004a_9920& QuaternionToMatrix(Matrix33T_s004a_9920& mat, const Quaternion& q)
{
    // locals named to reproduce the /Od stack-slot order (see tools/matching/od_names.py fit 11)
    float v22 = q.x * q.x;      // xx
    float n32 = q.y * q.y;      // yy
    float t28 = q.z * q.z;      // zz
    float m = q.x * q.y;       // xy
    float v1 = q.x * q.z;       // xz
    float v3 = q.y * q.z;       // yz
    float t33 = q.w * q.x;      // wx
    float idx = q.w * q.y;      // wy
    float v14 = q.w * q.z;      // wz
    float n36 = 1.0f;
    float p20 = 2.0f;
    Set(mat.xAxis, n36 - (n32 + t28) * p20, (m + v14) * p20, (v1 - idx) * p20);
    Set(mat.yAxis, (m - v14) * p20, n36 - (v22 + t28) * p20, (v3 + t33) * p20);
    Set(mat.zAxis, (v1 + idx) * p20, (v3 - t33) * p20, n36 - (v22 + n32) * p20);
    return mat;
}
}  // namespace SP

// @ 0x004a9d20
namespace SP {
Vector3T_s004a_9920& operator/=(Vector3T_s004a_9920& v, const float& s)
{
    float inv = 1.0f / s;
    Vector3T_s004a_9920 r;
    r.x = v.x * inv; r.y = v.y * inv; r.z = v.z * inv;
    v.x = r.x; v.y = r.y; v.z = r.z;
    return v;
}
}  // namespace SP

// @ 0x004a9e40
namespace SP {
template void evector<WeightedPoint>::push_back(const WeightedPoint& value)
;
}  // namespace SP

// @ 0x004a9f30
namespace SP {
template void evector<OrientedPoint>::push_back(const OrientedPoint& value)
;
}  // namespace SP

// @ 0x004a9fa0
namespace SP {
template void evector<KeyedPair>::push_back(const KeyedPair& value)
;
}  // namespace SP

// @ 0x004aa080
namespace SP {
template void evector<cSPMatrix3_s004a_9920>::push_back(const cSPMatrix3_s004a_9920& value)
;
}  // namespace SP

// @ 0x004aa120
namespace SP {
template<> deque<cSPEditorPart*>::~deque()
{
    for (DequeIterator<cSPEditorPart*> it(mItBegin); it != mItEnd; ++it) {}
    FreeBase();
}
}  // namespace SP

// @ 0x004aa170
namespace SP {
template<> uint32_t deque<cSPEditorPart*>::GetSize() const
{
    return (uint32_t)(mItEnd - mItBegin);
}
}  // namespace SP

// @ 0x004aa1d0
namespace SP {
template<> cSPEditorPart*& deque<cSPEditorPart*>::operator[](uint32_t n)
{
    DequeIterator<cSPEditorPart*> it(mItBegin);
    const int subarrayPosition = (it.mpCurrent - it.mpBegin) + (int)n;
    const int subarrayIndex = ((16777216 + subarrayPosition) / 64) - (16777216 / 64);
    return *(*(it.mpCurrentArrayPtr + subarrayIndex) + (subarrayPosition - (subarrayIndex * 64)));
}
}  // namespace SP

// @ 0x004aa230
namespace SP {
template<> void deque<cSPEditorPart*>::push_front(cSPEditorPart* const& value)
{
    if (mItBegin.mpCurrent != mItBegin.mpBegin) ::new(--mItBegin.mpCurrent) cSPEditorPart*(value);
    else DoPushFront(value);
}
}  // namespace SP

// @ 0x004aa2f0
namespace SP {
inline OrientedPoint::OrientedPoint(const OrientedPoint& x)
: mOrientation(x.mOrientation), mPosition(x.mPosition), mScale(x.mScale)
{
}
}  // namespace SP

// @ 0x00641900
bool GetCreatorType(const ResourceKey* key)
{
    AutoRef_s0064_14e0<IResource> spRes;
    IResourceManager* mgr = GetManager();
    spRes = 0;
    ResourceKey k(key->instanceID, 0x30bdee3, key->groupID);
    if (mgr->GetResource(&k, &spRes, 0, 0, 0, 0)) {
        AutoRef_s0064_14e0<cAssetMetadata> md;
        md.mpObject = spRes.mpObject ? (cAssetMetadata*)spRes.mpObject->Cast(0x30bdee3) : 0;
        if (md.mpObject)
            md.mpObject->AddRef();
        md.mpObject->FUN_005507a0();
        uint64_t* p = md.mpObject->FUN_005507a0();
        if (*p != (uint64_t)-1)
            return true;
    }
    return false;
}
