// src/game/SPBake/SPSkinnerPaintSystem.cpp -- migrated from slice(s) s00525360, s00524a50, s005241e0, s00523690, s00522800, s005218e0, s0051fb90 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinnerPaintSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cJobManager.h"
#include "nSPSkinner/cMeshAORender.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "nSPSkinner/cPaintSystem.h"
#include "nSPSkinner/cMesh.h"
#include "SP/cPropertyList.h"
#include "SP/cSkinObject.h"
#include "SP/cJob.h"

// unnamed retail callees and globals (address in the comment)
extern float g_1485720;   // 1.0f
extern float g_1485378;   // 0.0f

// ---- items of slice s0051fb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* FUN_0050a880(void* out, int p);          // 0x0050a880
int   FUN_004fddb0(void* v);                   // 0x004fddb0
void* FUN_0044e460(void* out, ...);             // 0x0044e460
void* FUN_00436ce0(void* out, void* a);        // 0x00436ce0
void  FUN_004a9d20(void* a, void* b);          // 0x004a9d20
float FUN_011e0738(float x);                   // 0x011e0738 lib_cblock sqrt
void  FUN_00520220(int p, float* outA, float* outB);
extern float g_1485720;   // 1.0f
extern float g_1485378;   // 0.0f
// ---- items of slice s0051fb90 end

// ---- items of slice s005218e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gAppProperties;                                          // 0x015fd918
extern void* gUnknown15de57c;                                         // 0x015de57c
extern "C" long __cdecl _InterlockedIncrement(long volatile*);
#pragma intrinsic(_InterlockedIncrement)
struct RcObj { virtual void AddRef(); virtual void Release(); };
struct JobMgr {
    int ContinueJob();                                        // 0x0068f970
};
struct Job { virtual void v0(); virtual void Release(); virtual bool Start(int, void*); virtual void v3(); virtual bool IsRunning(); };
struct AOCache { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                 virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
                 virtual void SetBlendColor(void* tmp, float a, float b); };   // vtable +0x3c
struct MeshAORender {
    void Rebuild();                                           // 0x00516eb0
};
struct Pipeline { void ExecutePipeline(); void F_0051aaa0(); void F_0051a9a0(unsigned plr, int, int, int, int, int, int, int, int, int); int pad[0x33c / 4]; int mFramesWaited; }; // 0x0051afd0 / 0051aaa0 / 0051a9a0
struct PaintListRender { void F_005123b0(); };                 // 0x005123b0
struct MatObj { void F_00526070(unsigned); void F_00526230(unsigned); void F_006909b0(); };
struct MsgServer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void Post(int, int, int); };
struct JobFactory { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
                    virtual unsigned char Create(int, void*, void*, int, int, int); }; // vtable +0x40
class RandomLC {
public:
    unsigned mSeed;
    void SetSeed(unsigned);                                   // 0x00936090
};
extern RandomLC gRandom;                                              // 0x016778dc
bool GetFloatProperty(void* list, unsigned id, float* out);           // 0x0040cf10
int InitVerbCollection(int);                                          // 0x004bb860
int GetIntProperty(void* list, unsigned id);                          // 0x006a2660 (thiscall in orig)
JobFactory* GetJobFactory();                                          // 0x0067ddb0
MsgServer* GetMessageServer();                                        // 0x0067dcc0
void RefCounted_Release(void*);                                       // 0x00453540 (thiscall)
void F_00506590(void* mat, unsigned size);                            // 0x00506590 (thiscall)
struct TickState {
    bool ShouldTick();
    void ClearPtr100();
    TickState& Assign(const TickState& o);                        // 0x005218e0
    bool HandleMessage(int id, void* msg);                        // 0x005219d0
    void Tick(int dt);                                            // 0x00521ba0
    void HandleUpdateMessage(int dt);                             // 0x00521d70
    void F_00523690();
    bool F_00525a40();
    void F_00525d90(unsigned);
    void F_006909b0();
    static void F_0051a6a0(void*);                                // 0x0051a6a0 (cdecl)
    void SetCreatureSkin(int, int);                               // 0x00522b40
};
struct PairF { int first; float second; };
struct IterTag {};
struct PairVector {
    PairF* mpBegin; PairF* mpEnd; PairF* mpCapacity; int mAllocator;
    PairF* erase(PairF* first, PairF* last);                     // 0x00530c80
    void DoAssign(PairF* first, PairF* last, IterTag);            // 0x005283d0
    void assign(PairF* first, PairF* last) { IterTag tag; DoAssign(first, last, tag); }
};
struct PairFixedVector {
    PairF* mpBegin; PairF* mpEnd; PairF* mpCapacity; int mAllocator[2]; int mPool[17];
    PairFixedVector(const PairVector& src);                       // 0x00525cf0
    void DoFree();                                                // 0x00526a40
};
bool GetResourceTypeFromModelType(int modelType);                 // 0x00526430 (thiscall)
struct PairVec { struct E { int a, b; }; E* mpBegin; E* mpEnd; unsigned size() const { return (unsigned)(mpEnd - mpBegin); } };
struct PtrHolder { void* p; void* get() const { return p; } };
struct AtomicRefCounted {
    void* vt; int pad; volatile long mRefCount;
    void AddRef() { _InterlockedIncrement(&mRefCount); }
    void Release();                                               // 0x00402420
};
template<class T> struct RefPtr {
    T* mp;
    RefPtr& operator=(T* p) { T* old = mp; if (p) p->AddRef(); mp = p; if (old) old->Release(); return *this; }
    __forceinline void Clear() { if (mp) *this = 0; }
};
#define F(T, off) (*(T*)((char*)this + (off)))
template<class T> struct VRefPtr {
    T* mp;
    VRefPtr& operator=(T* p) { if (p != mp) { T* old = mp; if (p) p->AddRef(); mp = p; if (old) old->Release(); } return *this; }
    VRefPtr& operator=(const VRefPtr& o) { return operator=(o.mp); }
};
struct CountedObj;
struct CountedPtr { CountedObj* mp; CountedPtr& operator=(CountedObj* p);   // 0x00525d90 (thiscall, out of line)
                    CountedPtr& operator=(const CountedPtr& o) { return operator=(o.mp); } };
struct Vec3Copy { float x, y, z; };
struct TickStateParams {
    Vec3Copy a; Vec3Copy b; float f18; int i1c, i20, i24, i28;
    VRefPtr<RcObj> r2c; int i30; CountedPtr p34;
};
static inline bool JobDone(JobMgr* m) { return (1 << m->ContinueJob() & 0x3c) != 0; }
// ---- items of slice s005218e0 end

// ---- items of slice s00522800 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_userColors[3];             // 0x015df0f0
extern float g_userColors2[3];            // 0x015df204
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void* FUN_00507c70(void* p);              // 0x00507c70
void* FUN_00529d30(void* p);              // 0x00529d30
struct PaintReq {
    void Set(int a2, int a3, int a4, int a5, char a6, char a7, char a8);
};
struct Factory {
    void* Make();
};
namespace nSPSkinner {
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& Set(const Vector3& o);                       // 0x004098a0
};
}
namespace nSPSkinner {
struct Matrix3 { float m[9]; };
}
namespace nSPSkinner {
Vector3 operator+(const Vector3& a, const Vector3& b);   // 0x0041dc10
}
namespace nSPSkinner {
Vector3 operator*(const Vector3& v, const float& s);     // 0x0041dca0
}
namespace nSPSkinner {
Vector3& operator*=(Vector3& v, const float& s);         // 0x0041dba0
}
namespace nSPSkinner {
Vector3 operator*(const Vector3& v, const Matrix3& m);   // 0x0041daf0
}
namespace nSPSkinner {
Vector3& operator+=(Vector3& v, const Vector3& o);       // 0x0041ddb0
}
namespace nSPSkinner {
inline float Fabsf(float f) { return (float)fabs(f); }
}
namespace nSPSkinner {
inline float Abs(float f) { return Fabsf(f); }
}
namespace nSPSkinner {
template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
}
namespace nSPSkinner {
class RefCounted {
public:
    virtual ~RefCounted();
    int AddRef() { return mnRefCount++ + 1; }
    int Release();                                        // 0x00453540
    int mnRefCount;
};
}
namespace nSPSkinner {
template<class T> class AutoRefCount {
public:
    T* mpObject;
    T* operator->() const { return mpObject; }
    AutoRefCount& Assign(T* pObject);                     // 0x0041cc60
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}
namespace nSPSkinner {
struct cMesh_s0052_2800 : RefCounted {
    cMesh_s0052_2800* Clone();                                       // 0x00523570
};
}
namespace nSPSkinner {
struct cMeshAORender_s0052_2800 {
    void Rebuild();                                       // 0x00516eb0
};
}
namespace nSPSkinner {
struct cBone {                                            // size 0x8c
    uint32_t pad0;
    short mParent;                                        // +0x04
    uint8_t pad6[5];
    uint8_t mType;                                        // +0x0b
    uint32_t padc[2];
    Vector3 mStart;                                       // +0x14
    Vector3 mEnd;                                         // +0x20
    float mfScale;                                        // +0x2c
    Matrix3 mRotation;                                    // +0x30
    Vector3 mPosition;                                    // +0x54
    uint32_t pad60[4];
    float mfLength;                                       // +0x70
    uint32_t pad74[6];
};
}
namespace nSPSkinner {
template<class T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    void* mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int n) { return mpBegin[n]; }
    void resize(int n);
};
}
namespace nSPSkinner {
struct cCreatureResource {
    uint32_t pad[0x26];
    sp_vector<cBone> mBones;                              // +0x98
};
}
namespace nSPSkinner {
struct cPropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                // 0x1c
    bool GetBool(uint32_t id);                            // 0x006a25a0
};
}
namespace nSPSkinner {
struct cSkinObject {
    uint32_t pad[2];
    AutoRefCount<cCreatureResource> mpResource;          // +0x08
    sp_vector<cPropertyList*> mBlockProps;                // +0x0c
    uint32_t pad1c[6];
    AutoRefCount<cMesh_s0052_2800> mpMesh;                           // +0x34
};
}
namespace nSPSkinner {
struct cBoneInfo {                                        // size 0x40
    char mParent;                                         // +0x00
    char mChain;                                          // +0x01
    char mNumChildren;                                    // +0x02
    char mFlags;                                          // +0x03
    Vector3 mPosition;                                    // +0x04
    Matrix3 mRotation;                                    // +0x10
    float mfWeight;                                       // +0x34
    float mfStart;                                        // +0x38
    float mfEnd;                                          // +0x3c
};
}
namespace nSPSkinner {
extern sp_vector<cBoneInfo> g_boneInfos;                 // 0x015de470
}
namespace nSPSkinner {
struct ChainWeight { float operator()(int bone); };       // 0x005235c0
}
namespace nSPSkinner {
struct cPaintOutput {
    uint32_t pad[5];
    int mnPending;                                        // +0x14
    uint32_t pad18;
    int mnDone;                                           // +0x1c
    void Reset();                                         // 0x006909b0
};
}
namespace nSPSkinner {
extern AutoRefCount<cPropertyList> g_appProperties;      // 0x015fd918
}
namespace nSPSkinner {
class cPaintSystem_s0052_2800 {
public:
    void SetCreatureSkin(cSkinObject* skin, bool keepMesh);  // 0x00522b40 (nSPSkinner::cPaintSystem::SetCreatureSkin)
    bool ShouldTick();                                    // 0x00522720
    void FinishTick();                                    // 0x00523690
    void RebuildBones();                                  // 0x005241e0

    uint32_t pad0[4];
    AutoRefCount<cMesh_s0052_2800> mpBakedMesh;                      // +0x10
    AutoRefCount<cMeshAORender_s0052_2800> mpMeshAORender;           // +0x14
    uint32_t pad18[2];
    cSkinObject* mpEditorSkinPart;                        // +0x20
    uint32_t pad24[0x11];
    int mOutputDiffuseGroup;                              // +0x68
    int mOutputNormSpecGroup;                             // +0x6c
    int mDXTQuality;                                      // +0x70
    int mOutputIndex;                                     // +0x74
    bool mb78;                                            // +0x78
    bool mb79;                                            // +0x79
    bool mb7a;                                            // +0x7a
    bool mb7b;                                            // +0x7b
    bool mb7c;                                            // +0x7c
    bool mb7d;                                            // +0x7d
    bool mbHighQuality;                                   // +0x7e
    uint8_t pad7f;
    uint32_t pad80[0x1f];
    AutoRefCount<cPaintOutput> mpOutput;                  // +0xfc
};
}
// ---- items of slice s00522800 end

// ---- items of slice s00523690 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kHalf9;                                                     // 0x01471064 (0.5f)
extern float kZero9;                                                     // 0x01485378 (0.0f)
extern float kScale9;                                                    // 0x013f1cac
struct cSPVector3R9 {
    float x, y, z;
    cSPVector3R9() {}
};
struct cSPVector39 {
    float x, y, z;
    cSPVector39() {}
    cSPVector39(const cSPVector3R9& o) : x(o.x), y(o.y), z(o.z) {}
    cSPVector39(const cSPVector39& o) : x(o.x), y(o.y), z(o.z) {}
    void operator=(const cSPVector3R9& o) { x = o.x; y = o.y; z = o.z; }
    void Assign(const cSPVector3R9& o);                      // 0x004098a0
};
struct cSPVector3C9 {
    float x, y, z;
    cSPVector3C9(const cSPVector3R9& o) : x(o.x), y(o.y), z(o.z) {}
    void Assign(const cSPVector3R9& o);                      // 0x004098a0
};
struct Mat39 { float m[9]; };
struct Vec3Pod { float x, y, z; };
cSPVector3R9 MulMat9(const cSPVector39& v, const Mat39& m);             // 0x0041daf0
cSPVector3R9 MulScalar9(const cSPVector39& v, const float& s);             // 0x0041dca0
cSPVector3R9 AddVec9(const cSPVector39& a, const cSPVector39& b);      // 0x0041dc10
cSPVector3R9 SubVec9(const cSPVector39& a, const cSPVector39& b);      // 0x0041db10
void MulAssign9(cSPVector39* a, const cSPVector39* b);                   // 0x0041dba0
void AddAssign9(cSPVector39* a, const cSPVector39* b);                   // 0x0041ddb0
cSPVector3R9 Cross9(const cSPVector39& a, const cSPVector39& b);         // 0x0044e460
cSPVector3R9 Normalize9(const cSPVector3R9& v);                          // 0x00436ce0
cSPVector3R9 Negate9(const cSPVector39& v);                              // 0x00422020
struct Vector2 {
    float x, y;
    Vector2& operator=(const Vector2& o);                    // 0x0051fb60
};
struct cMeshPos9 {
    uint32_t tri;
    Vector2 uv;
    cMeshPos9(const cMeshPos9& o) : tri(o.tri) { uv = o.uv; }
};
struct Prim9 {                                   // 0x8c bytes
    uint32_t pad0[0x14 / 4];
    cSPVector39 vA;                              // +0x14
    cSPVector39 vB;                              // +0x20
    uint32_t pad2c;                              // +0x2c
    Mat39 rot;                                   // +0x30 (also holds the +0x3c axis vector)
};
struct Mesh9 {
    uint32_t pad0[0x190 / 4];
    uint32_t* mPacked;                           // +0x190
    cSPVector3R9 GetTriNormal(uint32_t tri);                  // 0x005121c0
    cSPVector3R9 GetPosition(cMeshPos9 p);                    // 0x0050c490
};
struct Tables9 {
    uint32_t pad0[0x98 / 4];
    char* mPrims;                                // +0x98
};
struct Pal9 {
    uint32_t pad0[8 / 4];
    Tables9* mTables;                            // +0x8
    uint32_t pad1[0x14 / 4];
    uint8_t* mByteMap;                           // +0x20
};
struct Param9 {
    uint32_t pad0[0x1c / 4];
    uint32_t mFlags;                             // +0x1c
    uint32_t pad20[(0x2c - 0x20) / 4];
    uint16_t pad2c;
    uint8_t mMode;                               // +0x2e
    uint8_t mSub;                                // +0x2f
    uint32_t pad30[(0x3c - 0x30) / 4];
    cSPVector39 mDir;                            // +0x3c
    uint32_t pad48[(0x58 - 0x48) / 4];           // +0x48 blob
    float mRngA0;                                // +0x58
    float mRngA1;                                // +0x5c
    float mRngB0;                                // +0x60
    float mRngB1;                                // +0x64
};
struct Sink9 {
    void Set(void* p);                           // 0x004535d0 AutoRefCount::operator=
};
struct HitRec9 {
    uint32_t posRaw[3];                          // +0x0
    Vec3Pod dir;                                 // +0xc
    float f18;                                   // +0x18
    uint32_t i1c;                                // +0x1c
    int i20;                                     // +0x20
    int i24;                                     // +0x24
    uint32_t i28;                                // +0x28
    Sink9 ref;                                   // +0x2c
    uint32_t i30;                                // +0x30
};
struct Ctx9 {
    uint32_t pad0[0x10 / 4];
    Mesh9* mMesh;                                // +0x10
    uint32_t pad14[(0x20 - 0x14) / 4];
    Pal9* mPal;                                  // +0x20
    uint32_t pad24[(0x54 - 0x24) / 4];
    uint32_t mSeed;                              // +0x54

    float NextRandom();                          // 0x005169d0
    void BuildHit(HitRec9* out, Param9* p, cMeshPos9 pos, uint32_t seed);
};
unsigned FUN_00520110(Pal9* p, unsigned v);                          // 0x00520110
void FUN_0051fb90(uint8_t mode, void* blob, cMeshPos9 pos, Param9* p, Pal9* pal, Mesh9* mesh, cSPVector39* out);
void FUN_00520140(cSPVector39* n, cSPVector39* d, Vec3Pod* outA, Vec3Pod* outB);   // 0x00520140
static inline unsigned UnpackIdx9(Pal9* p, unsigned v)
{
    if (v & 0x80000000u)
        return (unsigned)p->mByteMap[v & 0x7fffffffu];
    return v;
}
static inline const int& Max9(const int& a, const int& b) { return (a < b) ? b : a; }
// ---- items of slice s00523690 end

// ---- items of slice s005241e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct MT {
    int base;                                  // +0x00
    unsigned char GetResourceTypeFromModelType();  // 0x00526340
};
extern MT g_mt;                                // 0x015de470
struct Vec2Pair { int a; int b; };
struct PairVec_s0052_41e0 { void push_back(const Vec2Pair& v); };   // 0x00525ff0
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}
struct Model {
    int Get(int i);
    int GetChecked(int i);
};
struct Y {
    void AddPair(int a1, int a2);
};
// ---- items of slice s005241e0 end

// ---- items of slice s00524a50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct sp_vector_allocator {
    uint32_t mFlags[2];
};
template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};
struct VectorU32 : VectorBase<uint32_t> {
    typedef uint32_t size_type;
    void resize(size_type n, const uint32_t& value);   // 0x004746c0
    void resize(size_type n);                          // 0x004cd3c0
    uint32_t* erase(uint32_t* first, uint32_t* last);  // 0x004769b0
    void clear() { erase(mpBegin, mpEnd); }
    uint32_t& operator[](size_type i) { return mpBegin[i]; }
};
struct cSPVector2_s0052_4a50 {
    float x, y;
    float& operator[](int i) { return (&x)[i]; }
};
struct VectorVec2 : VectorBase<cSPVector2_s0052_4a50> {
    typedef uint32_t size_type;
    cSPVector2_s0052_4a50& operator[](size_type i) { return mpBegin[i]; }
};
struct ElemC {
    uint32_t data[3];
};
struct VectorElemC : VectorBase<ElemC> {
    typedef uint32_t size_type;
};
struct DefaultRefCounted {
    void* vtbl;
    int mnRefCount;
    void AddRef();
    void Release();
};
struct cRigBlock {              // 0x8c bytes
    int16_t mParent;            // +0x00
    int16_t pad02;
    int16_t mNext;              // +0x04
    uint16_t pad06;
    uint16_t mFlags;            // +0x08
    uint8_t pad0a;
    uint8_t mType;              // +0x0b
    uint32_t pad0c[0x20];
};
struct cRigModel : DefaultRefCounted {
    uint32_t pad08[0x24];
    VectorBase<cRigBlock> mBlocks;      // +0x98
};
struct cMeshData : DefaultRefCounted {};
struct cSkinnerFactory;
struct cSkinnerSource {
    uint32_t pad00[2];
    cRigModel* mpModel;                 // +0x08
    VectorBase<void*> mCoords;          // +0x0c  (indexed by block slot)
    uint32_t pad1c[6];
    cSkinnerFactory* mpFactory;         // +0x34
    uint32_t pad38[0x16];
    VectorBase<cSPVector2_s0052_4a50> mTexRects;   // +0x90  (0x10-byte rects)
    uint32_t padA0[1];
    VectorBase<cMeshData*> mMeshData;   // +0xa4
};
struct cMeshAORenderObj {
    uint32_t pad00[2];
    VectorU32 mVerts;                   // +0x08
};
struct cMesh : DefaultRefCounted {      // retail size 0x1d0
    VectorElemC m08;                    // +0x08
    uint32_t pad18[6];
    VectorVec2 mTexCoords;              // +0x30
    uint32_t pad40[6];
    VectorU32 mVertexIndices;           // +0x58
    uint32_t pad6c[5];
    VectorU32 mTexIndices;              // +0x80
    uint32_t pad94[0x3f];
    VectorU32 m190;                     // +0x190
    uint32_t pad1a0[1];
    VectorU32 m1a4;                     // +0x1a4
    void Prepare();                     // 0x00509450
    void Reset();                       // 0x00508400
};
struct cSkinnerResult : DefaultRefCounted {
    VectorElemC m08;                                    // +0x08
    uint32_t pad18[0x10];
    VectorU32 m58;                                      // +0x58
    uint32_t pad6c[0x1e];
    VectorBase<cMeshAORenderObj*> mE4;                  // +0xe4
    uint32_t padf4[7];
    VectorU32 m110;                                     // +0x110
    uint32_t pad120[0x1c];
    VectorU32 m190;                                     // +0x190
    void AddMesh(cMesh* src);                           // 0x0050c6c0
    void Finish();                                      // 0x0050c3b0
};
struct SPcJob {
    uint32_t pad00[7];
    int mSlot;                          // +0x1c
    uint32_t pad20[2];
    bool Continuation(void* cb, void* data);   // 0x0068f9f0
};
struct SkinMsg {
    uint32_t pad00[4];
    int16_t mType;                      // +0x12
    char* GetBool();                    // 0x0041e920
};
struct MsgHandler {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual bool HandleMessage(uint32_t id, void** pMsg);   // +0x24
};
struct BuildMeshContext {
    uint32_t pad00[4];
    cSkinnerResult* mpResult;           // +0x10
    uint32_t pad14[3];
    cSkinnerSource* mpSource;           // +0x20
    uint32_t pad24[0x17];
    VectorU32 m80;                      // +0x80
    uint32_t pad90[0x1d];
    cMesh* mpMesh;                      // +0x104
};
bool LoadSkinnerMesh(cMeshData* data, cMesh* mesh);            // 0x0052a700
void ReportBlockError(cRigBlock* block, const char* msg);      // 0x00563de0
// ---- items of slice s00524a50 end

// ---- items of slice s00525360 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PoolNode {
    PoolNode* mpNext;
};
struct PooledObj {
    PoolNode* mpNext;
    uint32_t pad04[0x12];
    int mRefCount;                  // +0x4c
    static PoolNode* sFreeList;     // 0x015de2b0
    static void Free(void* p)
    {
        PoolNode* const node = (PoolNode*)p;
        node->mpNext = sFreeList;
        sFreeList = node;
    }
    void AddRef() { mRefCount++; }
    void Release()
    {
        if (--mRefCount > 0)
            return;
        Free(this);
    }
};
struct PoolPtr {
    PooledObj* mp;
    PoolPtr() : mp(0) {}
    ~PoolPtr();
    PoolPtr& operator=(PooledObj* p);
};
// ---- items of slice s00525360 end

// @ 0x0051fb90
void FUN_0051fb90(void* self)
{ (void)self; }







// @ 0x00520110
unsigned FUN_00520110(int p, unsigned v)
{
    if (v & 0x80000000u)
        return (unsigned)*(unsigned char*)(*(int*)(p + 0x20) + (v & 0x7fffffffu));
    return v;
}







// @ 0x00520140
void FUN_00520140(int p, int flags, float* outDir, float* outVal)
{
    float local_10, local_c, local_8;
    FUN_0044e460(&local_10, &g_1485720, p);
    (void)flags;
    float len2 = (local_10 * local_10 + local_c * local_c) + local_8 * local_8;
    if (len2 <= g_1485378) {
        FUN_00520220(p, outDir, outVal);
    } else {
        float inv = FUN_011e0738(len2);
        FUN_004a9d20(&local_10, &inv);
        outVal[0] = local_10;
        outVal[1] = local_c;
        outVal[2] = local_8;
        void* t = FUN_0044e460(&local_10, &local_10, p);
        float* n = (float*)FUN_00436ce0(&local_10, t);
        outDir[0] = n[0];
        outDir[1] = n[1];
        outDir[2] = n[2];
    }
}







// @ 0x00520220
void FUN_00520220(int p, float* outA, float* outB)
{
    float v[3]; v[0] = g_1485720; v[1] = g_1485720; v[2] = g_1485720;
    float tmp[3];
    int idx = FUN_004fddb0(FUN_0050a880(tmp, p));
    v[idx] = 0.0f;
    float t2[3], t3[3];
    float* n1 = (float*)FUN_00436ce0(t3, FUN_0044e460(t2, v, p));
    outA[0] = n1[0]; outA[1] = n1[1]; outA[2] = n1[2];
    float t4[3], t5[3];
    float* n2 = (float*)FUN_00436ce0(t5, FUN_0044e460(t4, p, outA));
    outB[0] = n2[0]; outB[1] = n2[1]; outB[2] = n2[2];
}






// @ 0x005218e0
TickState& TickState::Assign(const TickState& o)
{
#define D (*(TickStateParams*)this)
#define S (*(const TickStateParams*)&o)
    D.a = S.a;
    D.b = S.b;
    D.f18 = S.f18;
    D.i1c = S.i1c;
    D.i20 = S.i20;
    D.i24 = S.i24;
    D.i28 = S.i28;
    D.r2c = S.r2c;
    D.i30 = S.i30;
    D.p34 = S.p34;
#undef D
#undef S
    return *this;
}






// @ 0x005219d0
bool TickState::HandleMessage(int id, void* msg)
{
    switch (id) {
    case 0x247ca7b:
        if (F(unsigned char, 0x7e) && F(unsigned char, 0x7d)) {
            F(unsigned char, 0x7c) = 1;
            F(unsigned char, 0x7d) = 0;
            char* req = F(char*, 0x1c);
            if (req) {
                char* req2 = F(char*, 0x1c);
                if (*(unsigned char*)(req2 + 0x6a)) {
                    AtomicRefCounted** p = (AtomicRefCounted**)((char*)this + 0x100);
                    if (*p) {
                        AtomicRefCounted* old = *p;
                        *p = 0;
                        old->Release();
                    }
                    F_0051a6a0(p);
                }
            }
        }
        break;
    case 0x44edd9c:
        if (ShouldTick()) {
            // snapshot the pending list at +0x94, rebuild it, then restore the snapshot
            PairFixedVector local(*(PairVector*)((char*)this + 0x94));
            F_00523690();
            PairVector* mine = (PairVector*)((char*)this + 0x94);
            if ((void*)mine != (void*)&local) {
                mine->erase(mine->mpBegin, mine->mpEnd);
                mine->assign(local.mpBegin, local.mpEnd);
            }
            for (PairF* it = local.mpBegin; it < local.mpEnd; ++it) { }
            local.DoFree();
        }
        F(unsigned char, 0x7c) = 0;
        F(unsigned char, 0x7d) = 0;
        break;
    }
    return true;
}






// @ 0x00521ba0
void TickState::Tick(int dt)
{
    if (F(char*, 0x1c) != 0) {
        RandomLC* rng = &gRandom;
        unsigned saved = rng->mSeed;
        rng->SetSeed(F(unsigned, 0x58));
        char* mat = F(char*, 0xc);
        if (*(int*)(mat + 0x10) == 0)
            F_00506590(F(char*, 0xc), *(unsigned*)(F(char*, 0x1c) + 0x5c));
        HandleUpdateMessage(dt);
        float propA = 1.0f;
        float propB = 1.0f;
        GetFloatProperty(gAppProperties, 0x75cd84e9, &propA);
        GetFloatProperty(gAppProperties, 0xeaf2bc95, &propB);
        *(float*)(F(char*, 0x1c) + 0x70) = *(float*)(F(char*, 0xc) + 0x28);
        *(float*)(F(char*, 0x1c) + 0x74) = *(float*)(F(char*, 0xc) + 0x24) * propA;
        *(float*)(F(char*, 0x1c) + 0x78) = *(float*)(F(char*, 0xc) + 0x20) * propB;
        if (!ShouldTick()) {
            *(unsigned char*)(F(char*, 0x1c) + 0x6c) = 1;
            SetCreatureSkin(0, 0);
            void** p = (void**)((char*)this + 0x1c);
            if (*p) {
                void* old = *p;
                *p = 0;
                if (old) RefCounted_Release(old);
            }
        }
        F(unsigned, 0x58) = rng->mSeed;
        rng->SetSeed(saved);
    }
}






// @ 0x00521d70
void TickState::HandleUpdateMessage(int dt)
{
    bool wasTicking = ShouldTick();
    bool a = JobDone(F(JobMgr*, 0xfc));
    bool b = JobDone(F(JobMgr*, 0xf8));
    bool c = false;
    F(int, 0x64) += dt;
    char tmp[0x4c];
    F(AOCache*, 0xf4)->SetBlendColor(tmp, 0.25f, 0.25f);

    if (F(unsigned char, 0x7e) && !F(unsigned char, 0x7c) && !F(unsigned char, 0x7d) && !a) {
        char* req = F(char*, 0x1c);
        if (req && *(unsigned char*)(req + 0x6a) && F(int, 0x100) != 0) {
            F(unsigned char, 0x7c) = 1;
        } else {
            F(MeshAORender*, 0x14)->Rebuild();
            unsigned v58 = 0xf1cf8a9d;
            if (InitVerbCollection(*(int*)(*(char**)(F(char*, 0x20) + 8) + 0x18)) == 0x438f6347)
                v58 = 0xf01f7f52;
            int lo = 0x40;
            int prop = GetIntProperty(gAppProperties, 0xb8864eac);
            int v5c = (prop < lo) ? lo : prop;
            JobFactory* jf = GetJobFactory();
            F(unsigned char, 0x7d) = jf->Create(0x46e92e0, gUnknown15de57c, F(char*, 0x10) + 0x14c, 0x247ca7b, v58, v5c);
        }
    }
    Job* job = F(Job*, 0xf0);
    if (job && !job->IsRunning()) {
        Job** p = (Job**)((char*)this + 0xf0);
        if (*p) {
            Job* old = *p;
            *p = 0;
            old->Release();
        }
    }
    if (F(unsigned char, 0x60)) {
        F(Pipeline*, 0x18)->ExecutePipeline();
        if (F(Pipeline*, 0x18)->mFramesWaited == -1) {
            F(Pipeline*, 0x18)->F_0051aaa0();
            (*(PaintListRender**)(F(char*, 0xc) + 0xc))->F_005123b0();
            F(unsigned char, 0x60) = 0;
        }
    }
    if (!GetResourceTypeFromModelType(*(int*)(F(char*, 0xc) + 8)))
        F(unsigned char, 0x61) = 1;
    if (F(unsigned char, 0x62) && !b && !F_00525a40() && F(int, 0xf0) == 0) {
        int* v = (int*)((char*)this + 0x94);
        if ((unsigned)F(int, 0xec) == (unsigned)((v[1] - v[0]) >> 3)) {
            c = true;
            F(unsigned char, 0x61) = 1;
        }
    }
    if (F(unsigned char, 0x61) && !F(unsigned char, 0x60)) {
        char* mat = F(char*, 0xc);
        ((MatObj*)*(char**)(mat + 8))->F_00526070(*(unsigned*)(mat + 0xc));
        ((MatObj*)(*(char**)(F(char*, 0xc) + 8) + 0x14))->F_00526230(*(unsigned*)(F(char*, 0xc) + 0xc) + 0x14);
        if (c) {
            unsigned char xfer = F(char*, 0x1c) ? *(unsigned char*)(F(char*, 0x1c) + 0x68) : 0;
            F(Pipeline*, 0x18)->F_0051a9a0(*(unsigned*)(F(char*, 0xc) + 0xc), 1, F(unsigned char, 0x63), F(int, 0x68),
                                           F(int, 0x6c), F(int, 0x70), F(int, 0x74), F(unsigned char, 0x78),
                                           F(unsigned char, 0x79), xfer);
            F(unsigned char, 0x62) = 0;
        } else if (F(unsigned char, 0x7a) && F(unsigned, 0x64) > 0x1f4) {
            F(Pipeline*, 0x18)->F_0051a9a0(*(unsigned*)(F(char*, 0xc) + 0xc), 0, 0, F(int, 0x68), F(int, 0x6c), 0, -1, 0, 0, 0);
            F(int, 0x64) = 0;
        } else {
            F(Pipeline*, 0x18)->F_0051a9a0(*(unsigned*)(F(char*, 0xc) + 0xc), 0, 1, 0, 0, 0, -1, 0, 0, 0);
        }
        F(Pipeline*, 0x18)->ExecutePipeline();
        F(unsigned char, 0x60) = 1;
        F(unsigned char, 0x61) = 0;
    }
    if (!F(unsigned char, 0x61) && !b && F_00525a40()) {
        *(int*)(F(char*, 0xf8) + 0x14) = 1;
        *(int*)(F(char*, 0xf8) + 0x1c) = 0;
        F(MatObj*, 0xf8)->F_006909b0();
        b = true;
    }
    if (!b && !F_00525a40() && F(int, 0xf0) == 0 && !JobDone(F(JobMgr*, 0xfc))) {
        for (;;) {
            int* v = (int*)((char*)this + 0x94);
            unsigned idx = F(unsigned, 0xec);
            if (idx >= (unsigned)((v[1] - v[0]) >> 3)) break;
            F(unsigned, 0xec) = idx + 1;
            unsigned* ent = (unsigned*)(F(int, 0x94) + idx * 8);
            F(unsigned char, 0x62) = 1;
            gRandom.SetSeed(ent[1]);
            AOCache* aoc = F(AOCache*, 0xf4);
            Job** p = (Job**)((char*)this + 0xf0);
            if (*p) {
                Job* old = *p;
                *p = 0;
                old->Release();
            }
            if ((*(unsigned char (**)(AOCache*, unsigned, int, void*))(*(char**)aoc + 8))(aoc, ent[0], 0, p)) {
                F(Job*, 0xf0)->Start(0, 0);
                break;
            }
        }
    }
    if (wasTicking && !ShouldTick()) {
        F_00523690();
        GetMessageServer()->Post(0x46d485d, 0, 0);
    }
}






// @ 0x00522720
bool TickState::ShouldTick()
{
    return !(*(unsigned char*)((char*)this + 0x62) == 0 &&
             *(unsigned*)((char*)this + 0xec) >= ((PairVec*)((char*)this + 0x94))->size() &&
             ((PtrHolder*)((char*)this + 0xf0))->get() == 0 &&
             *(unsigned char*)((char*)this + 0x61) == 0 &&
             *(unsigned char*)((char*)this + 0x60) == 0);
}






// @ 0x005227a0
void TickState::ClearPtr100()
{
    ((RefPtr<AtomicRefCounted>*)((char*)this + 0x100))->Clear();
}





// @ 0x00522800
void FUN_00522800(void* self)
{ (void)self; }





// @ 0x005229c0
void FUN_005229c0(int idx, float* v)
{
    int* g1 = (int*)((char*)g_userColors + idx * 0xc);
    g1[0] = *(int*)&v[0];
    g1[1] = *(int*)&v[1];
    g1[2] = *(int*)&v[2];
    float tmp[3];
    tmp[0] = v[0];
    tmp[1] = v[1];
    tmp[2] = v[2];
    int* r = (int*)FUN_00529d30(tmp);
    int* g2 = (int*)((char*)g_userColors2 + idx * 0xc);
    g2[0] = r[0];
    g2[1] = r[1];
    g2[2] = r[2];
}





// @ 0x00522a40
void FUN_00522a40(void* self)
{ (void)self; }





// @ 0x00522ad0
void PaintReq::Set(int a2, int a3, int a4, int a5, char a6, char a7, char a8)
{
    *(int*)((char*)this + 0x68) = a2;
    *(int*)((char*)this + 0x6c) = a3;
    *(int*)((char*)this + 0x70) = a4;
    *(int*)((char*)this + 0x74) = a5;
    *(char*)((char*)this + 0x78) = a6;
    *(char*)((char*)this + 0x79) = a7;
    *(char*)((char*)this + 0x7a) = a8;
}





// @ 0x00522b40
namespace nSPSkinner {
void cPaintSystem_s0052_2800::SetCreatureSkin(cSkinObject* skin, bool keepMesh)
{
    if (ShouldTick())
        FinishTick();
    mOutputDiffuseGroup = 0;
    mOutputNormSpecGroup = 0;
    mDXTQuality = 0;
    mOutputIndex = -1;
    mb78 = false;
    mb7a = false;
    mb7b = false;
    mpEditorSkinPart = skin;

    if (skin) {
        if (keepMesh) {
            mpBakedMesh.Assign(skin->mpMesh.mpObject);
            skin->mpMesh = 0;
        } else {
            cMesh_s0052_2800* pMesh = skin->mpMesh.mpObject;
            mpBakedMesh = pMesh->Clone();
        }

        int lastChain = -1;
        int lastLeaf = -1;
        cBone* bones = skin->mpResource->mBones.mpBegin;
        int count = skin->mpResource->mBones.size();
        g_boneInfos.resize(count);

        for (int i = 0; i < count; ++i) {
            cBone* b = &bones[i];
            if (b->mType != 5 && b->mType != 3)
                break;
            g_boneInfos.mpBegin[i].mFlags = 0;
            g_boneInfos.mpBegin[i].mfStart = 0.0f;
            g_boneInfos.mpBegin[i].mfEnd = 0.0f;
            if (b->mType == 5) {
                Vector3 v = (b->mStart + b->mEnd) * 0.5f;
                v *= b->mfScale;
                v.Set(v * b->mRotation);
                v += b->mPosition;
                g_boneInfos.mpBegin[i].mParent = (char)(i - 1);
                g_boneInfos.mpBegin[i].mChain = (char)i;
                g_boneInfos.mpBegin[i].mNumChildren = -1;
                g_boneInfos.mpBegin[i].mfWeight = 1.0f;
                g_boneInfos.mpBegin[i].mPosition = v;
                g_boneInfos.mpBegin[i].mRotation = b->mRotation;
                lastChain = i;
            } else {
                int parent = b->mParent;
                if (parent != -1 && parent < i && bones[parent].mType == 3) {
                    g_boneInfos[parent].mNumChildren++;
                    g_boneInfos.mpBegin[i].mParent = (char)parent;
                } else {
                    g_boneInfos.mpBegin[i].mParent = -1;
                }
                g_boneInfos.mpBegin[i].mChain =
                    (lastChain != -1 && parent != -1) ? g_boneInfos.mpBegin[parent].mChain : -1;
                g_boneInfos.mpBegin[i].mNumChildren = 0;
                g_boneInfos.mpBegin[i].mfWeight = Abs(b->mfLength) + 1e-08f;
                g_boneInfos.mpBegin[i].mPosition = b->mPosition;
                g_boneInfos.mpBegin[i].mRotation = b->mRotation;
                lastLeaf = i;
            }
        }

        const int& last = Max(lastChain, lastLeaf);
        g_boneInfos.resize(last + 1);

        for (int j = g_boneInfos.size(); j < count; ++j) {
            cPropertyList* props = skin->mBlockProps[j];
            if (props->HasProperty(0xb00f0fef)) {
                for (int k = bones[j].mParent; k != -1; k = bones[k].mParent) {
                    if (bones[k].mType == 3)
                        g_boneInfos[k].mFlags |= 1;
                }
            } else if (props->HasProperty(0xb00f0fe2) || props->HasProperty(0xb00f0ff4)
                       || props->HasProperty(0xb00f0ff7) || props->HasProperty(0xb00f0ff2)) {
                for (int k = bones[j].mParent; k != -1; k = bones[k].mParent) {
                    if (bones[k].mType == 3)
                        g_boneInfos[k].mFlags |= 2;
                }
            }
        }

        RebuildBones();

        if (lastChain < g_boneInfos.size()) {
            float inv = 1.0f / (float)(lastChain + 1);
            for (int k = 0; k <= lastChain; ++k) {
                g_boneInfos.mpBegin[k].mfStart = (float)k * inv;
                g_boneInfos.mpBegin[k].mfEnd = (float)(k + 1) * inv;
            }
        }

        for (int k = 0, n = g_boneInfos.size(); k < n; ++k) {
            if (g_boneInfos.mpBegin[k].mNumChildren == -1)
                continue;
            ChainWeight weight;
            int parent = g_boneInfos.mpBegin[k].mParent;
            float start = (parent < 0) ? 0.0f : g_boneInfos.mpBegin[parent].mfEnd;
            g_boneInfos.mpBegin[k].mfStart = start;
            g_boneInfos[k].mfEnd = start + (1.0f - start) * (g_boneInfos[k].mfWeight / weight(k));
        }

        mpOutput->mnPending = 1;
        mpOutput->mnDone = 0;
        mpOutput->Reset();
        mb7c = false;
        mb7d = false;
        mbHighQuality = g_appProperties->GetBool(0x2853e342);
    } else {
        mpBakedMesh = 0;
        mpMeshAORender->Rebuild();
        mb7c = false;
        mb7d = false;
        mbHighQuality = false;
    }
}
}  // namespace nSPSkinner





// @ 0x00523570
void* Factory::Make()
{
    void* mem = EA_alloc(0x1d0, "Skinner", 0, 0, 0, 0);
    void* result;
    if (mem != 0)
        result = FUN_00507c70(this);
    else
        result = 0;
    return result;
}





// @ 0x005235c0
void FUN_005235c0(void* self)
{ (void)self; }




// @ 0x00523690
void FUN_00523690(void* self)
{ (void)self; }




// @ 0x00523900
void Ctx9::BuildHit(HitRec9* out, Param9* p, cMeshPos9 pos, uint32_t seed)
{
    mSeed = seed ^ 0x129c8901;
    Mesh9* mesh = mMesh;
    cSPVector3R9 nrm = mesh->GetTriNormal(pos.tri);
    cSPVector39 dir;
    switch (p->mMode) {
    case 0: case 1: case 2:
    default:
        FUN_0051fb90(p->mSub, (char*)p + 0x48, pos, p, mPal, mMesh, &dir);
        break;
    case 3:
        dir = p->mDir;
        break;
    case 4: {
        uint32_t v = (mesh->mPacked + pos.tri)[0] >> 16;
        Pal9* pal = mPal;
        Tables9* t = pal->mTables;
        Mat39* m = (Mat39*)(t->mPrims + FUN_00520110(pal, v) * 0x8c + 0x30);
        dir = MulMat9(p->mDir, *m);
        break;
    }
    case 5: {
        uint32_t v = (mesh->mPacked + pos.tri)[0] >> 16;
        Pal9* pal = mPal;
        Tables9* t = pal->mTables;
        char* e = t->mPrims + FUN_00520110(pal, v) * 0x8c + 0x30;
        cSPVector39 axis; axis.x = ((float*)(e + 0xc))[0]; axis.y = ((float*)(e + 0xc))[1]; axis.z = ((float*)(e + 0xc))[2];
        dir = Normalize9(Cross9(*(cSPVector39*)&nrm, axis));
        break;
    }
    case 6: {
        uint32_t v = ((mesh->mPacked + pos.tri)[0] >> 8) & 0xff;
        Pal9* pal = mPal;
        Tables9* t = pal->mTables;
        Mat39* m = (Mat39*)(t->mPrims + FUN_00520110(pal, v) * 0x8c + 0x30);
        dir = MulMat9(p->mDir, *m);
        break;
    }
    case 7: {
        uint32_t v = ((mesh->mPacked + pos.tri)[0] >> 8) & 0xff;
        unsigned idx = UnpackIdx9(mPal, v);
        Prim9* prim = (Prim9*)(mPal->mTables->mPrims + idx * 0x8c);
        float half = kHalf9;
        cSPVector3C9 c(MulScalar9(cSPVector39(AddVec9(prim->vA, prim->vB)), half));
        MulAssign9((cSPVector39*)&c, (cSPVector39*)((char*)prim + 0x2c));
        c.Assign(MulMat9(*(cSPVector39*)&c, prim->rot));
        AddAssign9((cSPVector39*)&c, (cSPVector39*)((char*)prim + 0x54));
        cSPVector39 d = SubVec9(mMesh->GetPosition(pos), *(cSPVector39*)&c);
        cSPVector39 axis(*(cSPVector39*)((char*)prim + 0x3c));
        dir = Normalize9(Cross9(d, axis));
        break;
    }
    }
    if (p->mFlags & 0x20)
        dir.Assign(Negate9(dir));
    Vec3Pod outA, outB;
    FUN_00520140((cSPVector39*)&nrm, &dir, &outA, &outB);
    out->posRaw[0] = *(uint32_t*)&pos.tri;
    out->posRaw[1] = ((uint32_t*)&pos)[1];
    out->posRaw[2] = ((uint32_t*)&pos)[2];
    out->dir = outA;
    out->f18 = kZero9;
    out->i1c = 0;
    out->i20 = -(int)(((p->mRngA1 - p->mRngA0) * NextRandom() + p->mRngA0) * kScale9);
    int b = (int)(((p->mRngB1 - p->mRngB0) * NextRandom() + p->mRngB0) * kScale9);
    out->i24 = Max9(1, b);
    out->i28 = seed;
    out->ref.Set(p);
    out->i30 = 0;
}




// @ 0x005240e0
void FUN_005240e0(void* self)
{ (void)self; }




// @ 0x00524150
void FUN_00524150(void* self)
{ (void)self; }



// @ 0x005241e0
void FUN_005241e0(void* self)
{ (void)self; }



// @ 0x005247b0
int Model::Get(int i)
{
    return i * 0x40 + g_mt.base;
}



// @ 0x005247d0
int Model::GetChecked(int i)
{
    int result;
    if (g_mt.GetResourceTypeFromModelType() != 0) {
        result = 0;
    } else {
        int thing = *(int*)((char*)this + 0x10);
        int* arr = *(int**)(thing + 0x1a4);
        int* slot = &arr[i];
        uint32_t raw = (uint32_t)*slot >> 0x10;
        uint32_t val;
        if (raw & 0x80000000u)
            val = (uint32_t)*(unsigned char*)(*(int*)(*(int*)((char*)this + 0x20) + 0x20) + (raw & 0x7fffffffu));
        else
            val = raw;
        if (val == 0xffffffffu)
            result = 0;
        else
            result = (int)val * 0x40 + g_mt.base;
    }
    return result;
}



// @ 0x00524870
void Y::AddPair(int a1, int a2)
{
    Vec2Pair local;
    local.a = a1;
    local.b = a2;
    ScratchSlots<2>();
    ((PairVec_s0052_41e0*)((char*)this + 0x94))->push_back(local);
}



// @ 0x005248a0
void FUN_005248a0(void* self)
{ (void)self; }


// @ 0x00524a50
bool __cdecl BuildMeshJobCallback(SPcJob* job, BuildMeshContext* ctx)
{
    cSkinnerSource* src = ctx->mpSource;
    cMesh* mesh = ctx->mpMesh;
    cSkinnerResult* result = ctx->mpResult;
    cRigBlock* blocks = src->mpModel->mBlocks.mpBegin;
    int nBlocks = (int)src->mpModel->mBlocks.size();
    int slot = job->mSlot;
    while (slot < nBlocks && (blocks[slot].mFlags & 1))
        slot++;
    uint32_t nFirst = 0;
    for (int k = 0; k < slot; k++) {
        if (!(blocks[k].mFlags & 1))
            nFirst++;
    }
    if (slot >= nBlocks) {
        result->Finish();
        ctx->m80.clear();
        ctx->m80.resize((uint32_t)(result->m08.size()), (uint32_t)-1);
        for (uint32_t i = 0; i < result->m58.size(); i++)
            ctx->m80.mpBegin[result->m58.mpBegin[i]] = i;
        return true;
    }
    cRigBlock* pBlock = &blocks[slot];
    cMeshData* meshData = src->mMeshData.mpBegin[slot];
    if (meshData == 0 || !LoadSkinnerMesh(meshData, mesh))
        ReportBlockError(pBlock, "contains an invalid mesh");
    mesh->Prepare();
    bool bBad = false;
    bool bShift = false;
    for (uint32_t i = 0; i < mesh->mTexCoords.size(); i++) {
        cSPVector2_s0052_4a50& uv = mesh->mTexCoords[i];
        if (uv[0] < 0.0f || uv[0] > 1.0f || uv[1] < -1.0f || uv[1] > 1.0f)
            bBad = true;
        else if (uv[1] < 0.0f)
            bShift = true;
    }
    if (bShift && !bBad) {
        for (uint32_t i = 0; i < mesh->mTexCoords.size(); i++) {
            cSPVector2_s0052_4a50& uv = mesh->mTexCoords[i];
            uv[1] += 1.0f;
            if (uv[1] < 0.0f || uv[1] > 1.0f)
                bBad = true;
        }
    }
    if (bBad) {
        ReportBlockError(pBlock, "contains out-of-bounds texture coordinates");
        mesh->mTexIndices.clear();
    } else {
        cSPVector2_s0052_4a50* rect = &src->mTexRects.mpBegin[slot * 2];
        for (uint32_t i = 0; i < mesh->mTexCoords.size(); i++) {
            cSPVector2_s0052_4a50& uv = mesh->mTexCoords[i];
            float x0 = rect[0].x;
            float dx = rect[1].x - x0;
            uv[0] = x0 + dx * uv[0];
            float y0 = rect[0].y;
            float dy = rect[1].y - y0;
            uv[1] = y0 + dy * uv[1];
        }
    }
    if (mesh->mVertexIndices.empty())
        ReportBlockError(pBlock, "is not in a recognized format -- please make sure the maya material exports tangents");
    else if (mesh->mTexIndices.empty())
        ReportBlockError(pBlock, "does not have any texture coordinates");
    else if (mesh->mTexIndices.size() != mesh->mVertexIndices.size())
        ReportBlockError(pBlock, "does not have a texture coordinate at every vertex");
    else {
        uint32_t key = 0;
        int16_t cur = pBlock->mParent;
        while (cur != -1) {
            if (blocks[cur].mType == 5) {
                key |= (uint32_t)cur << 8;
                break;
            }
            cur = blocks[cur].mNext;
        }
        if (pBlock->mType == 3) {
            key |= 2;
            key |= (uint32_t)pBlock->mParent << 16;
        } else {
            key |= 4;
            cur = pBlock->mParent;
            while (cur != -1) {
                if (blocks[cur].mType == 5 || blocks[cur].mType == 3) {
                    key |= (uint32_t)cur << 16;
                    break;
                }
                cur = blocks[cur].mNext;
            }
        }
        char bKey = 0;
        MsgHandler* handler = (MsgHandler*)src->mCoords.mpBegin[slot];
        if (handler != 0) {
            SkinMsg* pMsg = 0;
            if (handler->HandleMessage(0x317a429d, (void**)&pMsg) && pMsg->mType == 1)
                bKey = *pMsg->GetBool();
        }
        if (bKey != 0)
            key |= 0x40;
        mesh->m1a4.resize((uint32_t)(mesh->m08.size()), key);
        uint32_t nTri = mesh->mVertexIndices.size() / 3;
        uint32_t nBase = result->m110.size();
        result->AddMesh(mesh);
        cMeshAORenderObj* pObj = result->mE4.mpBegin[nFirst];
        pObj->mVerts.resize(nTri);
        for (uint32_t i = 0; i < nTri; i++)
            pObj->mVerts.mpBegin[i] = i + nBase;
        uint32_t notFirst = ~nFirst;
        result->m110.resize(nBase + nTri, notFirst);
        result->m190.resize(nBase + nTri, key);
    }
    mesh->Reset();
    job->mSlot = slot + 1;
    return job->Continuation((void*)&BuildMeshJobCallback, ctx);
}

// @ 0x00525d90
PoolPtr& PoolPtr::operator=(PooledObj* p)
{
    if (p != mp) {
        PooledObj* const pTemp = mp;
        if (p)
            p->AddRef();
        mp = p;
        if (pTemp)
            pTemp->Release();
    }
    return *this;
}
