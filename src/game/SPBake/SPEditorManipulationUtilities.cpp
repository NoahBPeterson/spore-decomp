// src/game/SPBake/SPEditorManipulationUtilities.cpp -- migrated from slice(s) s004a9920, s004a3dc0, s004a1a70, s0049fbd0, s0049a2a0, s006414e0, s004a89e0, s004a7c30, s004a6f10, s0049b340, s00499410, s00498470, s004974e0, s00496d30, s00496300, s004956b0, s004942b0, s00493640, s004928d0, s00491900, s00490a70, s0048fde0, s00481f00, s00453250, s00435d40 by tools/migrate/rewrite.py
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

// ---- items of slice s0048fde0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
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
Vector3* Vector3_Scale(Vector3* out, const float* s, const Vector3* v); // 0x0041de40
Vector3* Vector3_Sub(Vector3* out, const Vector3* a, const Vector3* b); // 0x0041db10
void ExpandBy(BoundingBox* b, float m);                               // 0x0044ad00
// ---- items of slice s0048fde0 end

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
struct RefBlockVec {
    cSPEditorBlock_s0049_fbd0** b; cSPEditorBlock_s0049_fbd0** e; cSPEditorBlock_s0049_fbd0** c; int allocPair[2];
    RefBlockVec(char& a);                       // 0x540470
    ~RefBlockVec();                             // 0x453eb0
};
void FUN_49efc0(cSPEditorBlock_s0049_fbd0*, cSPVector3_s0049_fbd0, cSPVector3_s0049_fbd0, cSPMatrix3_s0049_fbd0, cSPMatrix3_s0049_fbd0, LimbVec<cSPEditorBlock_s0049_fbd0*>*);
void FUN_49efc0(cSPEditorBlock_s0049_fbd0*, Vector3T_s0049_fbd0, Vector3T_s0049_fbd0, Mat3Id, Matrix33T_s0049_fbd0, LimbVec<cSPEditorBlock_s0049_fbd0*>*);
bool FUN_49dd20(cSPEditorBlock_s0049_fbd0*, LimbVec<cSPEditorBlock_s0049_fbd0*>*, int);
void RepinBlockToTorso(cSPEditorBlock_s0049_fbd0* block, cSPVector3_s0049_fbd0 t, cSPMatrix3_s0049_fbd0 r, bool flag);
// ---- items of slice s0049fbd0 end

// ---- items of slice s004a1a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
extern const cSPVector3_s004a_1a70 kSnapZero;               // 0x015d64d8
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
Vec3_s004a_3dc0* __cdecl Vector3_Scale(Vec3_s004a_3dc0* out, const float* s, const Vec3_s004a_3dc0* v); // @ 0x41de40
Vec3_s004a_3dc0* __cdecl FUN_0041dc10(Vec3_s004a_3dc0* out, const Vec3_s004a_3dc0* a, const Vec3_s004a_3dc0* b); // @ 0x41dc10 (a + b)
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
Vector3T_s004a_9920 operator*(const Vector3T_s004a_9920& v, const Matrix33T_s004a_9920& m);   // @ 0x41daf0
Vector3T_s004a_9920 operator-(const Vector3T_s004a_9920& v);                       // @ 0x422020
Vector3T_s004a_9920 operator+(const Vector3T_s004a_9920& a, const Vector3T_s004a_9920& b);    // @ 0x41dc10
namespace SP {
struct Quaternion { float x, y, z, w; };
}
namespace SP {
inline void Set(Vector3T_s004a_9920& v, float x, float y, float z) { v.x = x; v.y = y; v.z = z; }
}
// ---- items of slice s004a9920 end

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







// @ 0x004a8d70
M3::M3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    m[0].x = a; m[0].y = b; m[0].z = c;
    m[1].x = d; m[1].y = e; m[1].z = f;
    m[2].x = g; m[2].y = h; m[2].z = i;
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
