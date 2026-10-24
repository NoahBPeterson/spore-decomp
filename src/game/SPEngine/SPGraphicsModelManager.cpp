// src/game/SPEngine/SPGraphicsModelManager.cpp -- migrated from slice(s) s007523a0, s00753270, s00751560, s007507e0, s00750180, s0074f200, s0074e2b0, s0074d4b0, s0074c260, s0074b170, s0074a290, s00749370, s00748800, s00747920, s007469b0, s00745ac0, s00744ad0, s00743b20, s00742b30 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsModelManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cModelWorld.h"
#include "SP/cMWModelInternal.h"
#include "SP/cModelInstance.h"
#include "cSPVector3.h"
#include "cOccluder.h"
#include "cSPBoundingBox.h"
#include "cSPTransform.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include <string.h>
#include <math.h>
#include <float.h>
#include "SP/cJob.h"
#include "EA/Allocator/FixedAllocatorBase.h"
#include "EA/ArgScript/cIParser.h"
#include "rw/graphics/GlobalState.h"
#include "SP/cMWGroupInternal.h"
#include "SP/cMWGroup.h"
#include "SP/cMWObject.h"
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)
inline void* operator new(unsigned int, void* p) { return p; }   // placement new (moved out of the s00743b20 block by hand: rewrite.py drops it as a <new> duplicate)
struct Vec3 { float x, y, z; };   // hand-placed before all slice blocks: rewrite.py emitted it after the s00745ac0 DrawRecord that uses it (C2146)

// ---- items of slice s00742b30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cModelWorld56 {
    // @ 0x00743940  vtable adjustor helper
    int Adjustor(int unused);

    // @ 0x007439d0
    void SetCurveSegment(int* a, int* b, int index);

    // @ 0x00743a20
    void GetCurveSegment(int* a, int* b, int index);

    // @ 0x00743a60
    void SetCurveRange(int index, int begin, int end);

    // @ 0x00743a80
    void GetCurveRange(int index, int* begin, int* end);

    // @ 0x00743b00  SP::cModelWorld::ResetHighlightCurve
    void ResetHighlightCurve();

    // @ 0x00742ca0  rbtree-ish insert
    void MapInsert(int* pos, int* value);

    // @ 0x00742cf0
    void SetAnimationResource(int* p);

    // @ 0x00742b30
    void Sub2b30(int a2, int a3);
    // @ 0x00742db0  SP::cModelInstance::ConstructFromGameModelResource
    void ConstructFromGameModelResource(void* a2);
    // @ 0x00742f60
    void Sub2f60(int a2);
    // @ 0x00743030  SP::cModelInstance::GetBoneParents
    int GetBoneParents(void* a2);
    // @ 0x00743150
    void Sub3150(int a2);
    // @ 0x00743270
    void Sub3270(int a2, int a3);
    // @ 0x007434b0
    void Sub34b0(int a2);
};
// ---- items of slice s00742b30 end

// ---- items of slice s00743b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct intrusive_node { intrusive_node* mpNext; intrusive_node* mpPrev; };
struct Model {
    void*    mpWorld;                 // +0x00
    uint32_t mFlags;                  // +0x04
    char     pad08[0x38];             // +0x08
    int      mnRefCount;              // +0x40
    char     pad44[0x28];             // +0x44
    float    mDefaultBoundingRadius;  // +0x6c
    char     pad70[0x20];             // +0x70
    void*    mpField90;               // +0x90  (abs 0x98 in cMWModelInternal)
};
struct cModelInstance {
    int  GetAnimationIDs();                              // 0x0073aba0
    int  GetAnimIDs(uint32_t* dst, int g, int h);        // 0x0073abb0
    int  GetAnimMoveToTimes(int a, int b, int c);        // 0x0073abb0
    int  GetNumBones();                                  // 0x0073b7e0
    int  GetPoseTransforms(void* dst, int original);     // 0x0073d6b0
    int  GetBoneTransforms(void* dst);                   // 0x00740550
    int  GetBoneIDs(void* dst);                          // 0x00740740
    int  GetBoneParents(void* dst);                      // 0x00743030
    bool GetAnimationRange(int a, float& d, int b, float& c);  // 0x0073b6d0
    void SetActive(int a, int b, int c, float d, int e);
    void MoveToTime(int a, int b, float c);
    void SetWeight(int a, int b, float c);
};
bool __cdecl LineClip(const void*, const void*, int, int);  // 0x006989d0
struct cSPVector3_s0074_3b20 { float x, y, z; };
struct cSPMatrix3_s0074_3b20 { float m[9]; };
struct cSPTransform_s0074_3b20 {
    uint16_t   mFlags;         // +0x00
    uint16_t   mModCount;      // +0x02
    cSPVector3_s0074_3b20 mTranslation;   // +0x04
    float      mScale;         // +0x10
    cSPMatrix3_s0074_3b20 mRotation;      // +0x14
    float      mMatrix30;      // +0x38
    uint32_t   mData3C;        // +0x3c
};
struct cMWModelInternal : intrusive_node, Model {
    void* mpField9c;                  // abs +0x9c
    void* mpFieldA0;                  // +0xa0
    void* mpFieldA4;                  // +0xa4
    void* mpFieldA8;                  // +0xa8
    void* mpFieldAC;                  // +0xac
    void* mpFieldB0;                  // +0xb0
    cModelInstance* mAnim[6];         // +0xb4
    char    pad_cc[0x138 - 0xcc];
    uint32_t mFlags138;               // +0x138
};
struct cLoadQueue_s0074_3b20 { void StallUntilLoaded(uint32_t); };
struct cModelWorld;
struct IModelWorld {
    virtual int   AddRef();                              // +0x00
    virtual int   Release();                             // +0x04
    virtual void  dtor();                                // +0x08
    virtual void* CreateModel(uint32_t, uint32_t, int);  // +0x0c
    virtual int   GetNumModelsLoading();                 // +0x10
    virtual bool  CallOnLoad(Model*, void*, void*);      // +0x14
    virtual void  PreloadModels(void*, int);             // +0x18
    virtual bool  ModelsHavePreloaded(int);              // +0x1c
    virtual void* CreateGroup(int, void*&);              // +0x20
    virtual void* m24();                                 // +0x24
    virtual void* m28();                                 // +0x28
    virtual bool  m2c(void*);                            // +0x2c
    virtual bool  m30(void*);                            // +0x30
    virtual bool  m34(void*);                            // +0x34
    virtual bool  m38(void*);                            // +0x38
    virtual bool  m3c(void*);                            // +0x3c
    virtual bool  m40(void*);                            // +0x40
    virtual bool  m44(void*);                            // +0x44
    virtual bool  m48(void*);                            // +0x48
    virtual bool  m4c(void*);                            // +0x4c
    virtual void  GetModelResourceIDs(Model*, void*, void*); // +0x50
    virtual void  GetRegionList(Model*, void*);          // +0x54
    virtual void  StallUntilLoaded(Model*);              // +0x58
};
uint32_t Getb20(Model* model);  // 0x00743b20 (defined below; used by a stub's inline body)
struct cModelWorld : IModelWorld {
    // slice methods
    int   Getb20(Model*);
    int   GetNumAnimations(Model*);
    int   GetAnimationIDs(Model*, uint32_t*);
    int   GetAnimationMoveToTimes(Model*, int, int);
    int   GetDeformationAnimationIDs(Model*, int, int);
    float StallGetBoundingBox(Model*);
    void* GetNumAnimationGroups(Model*);
    void  GetModelResourceIDs(Model*, uint32_t*, uint32_t*);
    void  StallUntilLoaded2(Model*, uint32_t);
    void  AnimAction(Model*, int, int, float, int);
    void  MoveToTime(Model*, int, float, int);
    void  SetWeight(Model*, int, float, int);
    bool  GetAnimationRange(Model*, int, int, float&, float&);
    int   GetNumBones(Model*);
    int   GetPoseTransforms(Model*, void*, int);
    int   GetBoneTransforms(Model*, void*);
    int   GetBoneIDs(Model*, void*);
    int   GetBoneParents(Model*, void*);
    bool  IsVecEmpty(int);
    void* VecClear();
    bool  CallOnLoad(Model*, void*, void*);
};
struct RefCounted { virtual void AddRef(); virtual void Release(); };
struct Elem28 {
    uint32_t    m0;
    RefCounted* mRef;
    uint32_t    m8, mC, m10, m14, m18;
    Elem28(const Elem28& o);
};
Elem28::Elem28(const Elem28& o) {
    m0 = o.m0;
    mRef = o.mRef;
    if (mRef)
        mRef->AddRef();
    m8 = o.m8;
    mC = o.mC;
    m10 = o.m10;
    m14 = o.m14;
    m18 = o.m18;
}
struct Pair8 { uint32_t val; float key; };
struct cOccluder6 { uint32_t d[6]; };
struct ResInfo { char pad[8]; uint32_t field8; uint32_t fieldC; uint32_t field10; };
struct ResHolder { ResInfo* Get(); };
// ---- items of slice s00743b20 end

// ---- items of slice s00744ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
bool  __stdcall Check434b0(void*);   // 0x007434b0
struct EffectInner;
struct EffectEntry {
    union {
        struct {
            uint32_t mID;     // +0x00
            uint32_t mPad4;   // +0x04
        };
        uint64_t mKey;        // +0x00 id along with its zero tag word
    };
    EffectInner* mpInner;     // +0x08
    char         pad0C[0x44 - 0x0C];
    uint8_t      mEnabled;    // +0x44
    char         pad45[3];
};  // 0x48
struct EffectInner {
    virtual void v00(); virtual void v04(); virtual void v08(int); virtual void v0C(int);
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual bool v44(int, int, int); virtual bool v48(int, int, int);
    virtual bool v4C(int, int);
};
struct Prop {
    char pad[0x12];
    uint16_t mType;                 // +0x12
    float* GetFloat();
};
struct PropHolder {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20();
    virtual bool Find(int id, void** out);   // slot 9 (0x24)
};
struct SlotVec { int* mp; int next(int idx); };
struct SlotCell { int v[5]; void Assign(int* src); };
struct ChunkObj { virtual int AddRef(); virtual int Release(); };
struct DequeIter { int v[4]; int* Advance(int n); };
struct RefObj { virtual void v0(int); int mRef; };
struct AutoRef { RefObj* mp; AutoRef* Release(); };
struct Model_s0074_4ad0;
struct cModelInstance_s0074_4ad0;
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int);
void  __cdecl EA_Free(void*);       // 0x00f47380
void  __cdecl MemMove(void*, const void*, unsigned); // 0x13cc480 msvcr90!memmove
int   __cdecl VecDoInsertValue();   // 0x011e0744
void  __cdecl PropertyGetFloatArray(void*, const char*, void*, void*); // 0x006a08b0
bool  __cdecl RuntimeModelBuilder_GetRuntimeMeshes(cModelInstance_s0074_4ad0*, int, int, int, int); // 0x007763b0
struct Model_s0074_4ad0 {
    void*    mpWorld;                 // +0x00
    uint32_t mFlags;                  // +0x04
    char     pad08[0x38];             // +0x08
    int      mnRefCount;              // +0x40
    char     pad44[0x94 - 0x44];      // +0x44
};
struct cModelInstance_s0074_4ad0 {
    void SetBoneTable(int a, int b);  // 0x0073b800 (cModelInstance::SetBoneTable)
    void SetBoneCallback(int a, int b, int c, int d);  // 0x0073b840 (cModelInstance::SetBoneCallback)
    void SetAnimationGroupTransform(int a, int b);  // 0x0073f4b0 (cModelInstance::SetAnimationGroupTransform)
    int  GetRegionMaterialInfo(int region);  // 0x00741150 (cModelInstance::GetRegionMaterialInfo)
    void SetDynamicDraw(int a, int b);  // 0x0073b8e0 (cModelInstance::SetDynamicDraw)
    int  GetDeformationHandles(void* a, void* b);  // 0x0073d1e0 (cModelInstance::GetDeformationHandles)
    int  GetArenaResource();  // 0x0073d160 (cModelInstance::GetArenaResource)
    bool SelectMesh(int a, int b);
    cModelInstance_s0074_4ad0* Init();
    void SetFlags(int a, int b);
    void Method742cf0(void* a);
    void ConstructFromGameModelResource(void* a);  // 0x00742db0 (cModelInstance::ConstructFromGameModelResource)
    int  GetAnimationIDs();  // 0x0073aba0 (cModelInstance::GetAnimationIDs)
    void SetActive(int a, int b, int c, float d, int e);  // 0x0073ac20 (cModelInstance::SetActive)
    void MoveToTime(int a, int b, float c);  // 0x0073b190 (cModelInstance::MoveToTime)
    void SetWeight(int a, int b, float c);  // 0x0073b530 (cModelInstance::SetWeight)
};
struct cMWModelInternal_s0074_4ad0 : intrusive_node, Model_s0074_4ad0 {
    void*    mpField9c;               // abs +0x9c
    void*    mpFieldA0;
    void*    mpFieldA4;
    void*    mpFieldA8;
    void*    mpFieldAC;
    void*    mpFieldB0;
    cModelInstance_s0074_4ad0* mAnim[6];         // +0xb4
    char     pad_cc[0xd4 - 0xcc];
    int      mFieldD4;                // +0xd4
    int      mFieldD8;                // +0xd8
    void*    mpFieldDC;               // +0xdc
    char     pad_e0[0x124 - 0xe0];
    float    mField124;               // +0x124
    uint8_t  mField128;               // +0x128
    uint8_t  mField129;               // +0x129
    char     pad_12a[0x138 - 0x12a];
    uint32_t mFlags138;               // +0x138
};
struct IModelWorld_s0074_4ad0 {
    virtual int   AddRef();
    virtual int   Release();
    virtual void  dtor();
    virtual void* CreateModel(uint32_t, uint32_t, int);
    virtual int   GetNumModelsLoading();
    virtual bool  CallOnLoad(Model_s0074_4ad0*, void*, void*);
    virtual void  PreloadModels(void*, int);
    virtual bool  ModelsHavePreloaded(int);
    virtual void* CreateGroup(int, void*&);
    virtual void* m24();
    virtual void* m28();
    virtual bool  m2c(void*);
    virtual bool  m30(void*);
    virtual bool  m34(void*);
    virtual bool  m38(void*);
    virtual bool  m3c(void*);
    virtual bool  m40(void*);
    virtual bool  m44(void*);
    virtual bool  m48(void*);
    virtual bool  m4c(void*);
    virtual void  GetModelResourceIDs(Model_s0074_4ad0*, void*, void*);
    virtual void  GetRegionList(Model_s0074_4ad0*, void*);
    virtual void  StallUntilLoaded(Model_s0074_4ad0*);
};
void DequeInsert(int* self, unsigned count, int flag);  // 0x007457a0 (defined below; used by a stub's inline body)
struct cModelWorld_s0074_4ad0 : IModelWorld_s0074_4ad0 {
    int   Getb20(Model_s0074_4ad0*);
    int   GetNumAnimations(Model_s0074_4ad0*);  // 0x00744790 (cModelWorld::GetNumAnimations)
    int   GetAnimationIDs(Model_s0074_4ad0*, uint32_t*);  // 0x007447c0 (cModelWorld::GetAnimationIDs)
    int   GetAnimationMoveToTimes(Model_s0074_4ad0*, int, int);  // 0x007447f0 (cModelWorld::GetAnimationMoveToTimes)
    int   GetDeformationAnimationIDs(Model_s0074_4ad0*, int, int);  // 0x00744830 (cModelWorld::GetDeformationAnimationIDs)
    float StallGetBoundingBox(Model_s0074_4ad0*);  // 0x007446a0 (cModelWorld::StallGetBoundingBox)
    void* GetNumAnimationGroups(Model_s0074_4ad0*);  // 0x007446c0 (cModelWorld::GetNumAnimationGroups)
    void  GetModelResourceIDs(Model_s0074_4ad0*, uint32_t*, uint32_t*);  // 0x007446e0 (cModelWorld::GetModelResourceIDs)
    void  StallUntilLoaded2(Model_s0074_4ad0*, uint32_t);  // 0x00744760 (cModelWorld::StallUntilLoaded2)
    void  AnimAction(Model_s0074_4ad0*, int, int, float, int);  // 0x00744870 (cModelWorld::AnimAction)
    void  MoveToTime(Model_s0074_4ad0*, int, float, int);  // 0x00744900 (cModelWorld::MoveToTime)
    void  SetWeight(Model_s0074_4ad0*, int, float, int);  // 0x00744950 (cModelWorld::SetWeight)
    bool  GetAnimationRange(Model_s0074_4ad0*, int, int, float&, float&);  // 0x007449a0 (cModelWorld::GetAnimationRange)
    int   GetNumBones(Model_s0074_4ad0*);  // 0x007449e0 (cModelWorld::GetNumBones)
    int   GetPoseTransforms(Model_s0074_4ad0*, void*, int);  // 0x00744a10 (cModelWorld::GetPoseTransforms)
    int   GetBoneTransforms(Model_s0074_4ad0*, void*);  // 0x00744a40 (cModelWorld::GetBoneTransforms)
    int   GetBoneIDs(Model_s0074_4ad0*, void*);  // 0x00744a70 (cModelWorld::GetBoneIDs)
    int   GetBoneParents(Model_s0074_4ad0*, void*);  // 0x00744aa0 (cModelWorld::GetBoneParents)
    bool  IsVecEmpty(int);
    void* VecClear();  // 0x00743b50 (cModelWorld::VecClear)
    bool  CallOnLoad(Model_s0074_4ad0*, void*, void*);  // 0x007445b0 (cModelWorld::CallOnLoad)

    void  SetBoneTable(Model_s0074_4ad0*, int, int);  // 0x00744ad0 (cModelWorld::SetBoneTable)
    void  SetBoneCallback(Model_s0074_4ad0*, int, int, int, int);  // 0x00744b10 (cModelWorld::SetBoneCallback)
    void  SetAnimationGroupTransform(Model_s0074_4ad0*, int, int);  // 0x00744b60 (cModelWorld::SetAnimationGroupTransform)
    int   GetMaterialInfo(Model_s0074_4ad0*, int);  // 0x00744ba0 (cModelWorld::GetMaterialInfo)
    void  SetDynamicDraw(Model_s0074_4ad0*, int, int);  // 0x00744be0 (cModelWorld::SetDynamicDraw)
    int   GetNumLODs(Model_s0074_4ad0*);  // 0x00744c30 (cModelWorld::GetNumLODs)
    void  SetLOD(Model_s0074_4ad0*, int);
    void  SetSomeFloat(Model_s0074_4ad0*, float);  // 0x00744cf0 (cModelWorld::SetSomeFloat)
    void  SetEffectEnabled(Model_s0074_4ad0*, char, char, int);  // 0x00744d80 (cModelWorld::SetEffectEnabled)
    char  ForEachEffectA(Model_s0074_4ad0*, int, int, int, int);  // 0x00744e10 (cModelWorld::ForEachEffectA)
    char  ForEachEffectB(Model_s0074_4ad0*, int, int, int, int);  // 0x00744e90 (cModelWorld::ForEachEffectB)
    char  ForEachEffectC(Model_s0074_4ad0*, int, int, int);  // 0x00744f10 (cModelWorld::ForEachEffectC)
    int   GetDeformationHandles(Model_s0074_4ad0*, void*, void*);
    bool  GetRuntimeMeshes(Model_s0074_4ad0*, int, int, int, int);  // 0x00744fc0 (cModelWorld::GetRuntimeMeshes)
    bool  CheckFlag(Model_s0074_4ad0*, int);  // 0x00745010 (cModelWorld::CheckFlag)
    bool  SelectMesh(Model_s0074_4ad0*, int, int, char);  // 0x00745050 (cModelWorld::SelectMesh)
    uint32_t GetSlot(int);
    int   HACK_GetArenaResource(Model_s0074_4ad0*);  // 0x00745110 (cModelWorld::HACK_GetArenaResource)
    void  FillColor(int*);  // 0x00745140 (cModelWorld::FillColor)
    void* ReleaseRef();
    void  ReleaseRefs();
    void* DequeInsert(int, int);
};
void* cModelWorld_s0074_4ad0::VecClear() { *(uint32_t*)this = 0; return this; }
struct RangeDtor { void Destroy(void**, void**); };
struct RCObj_s0074_4ad0 {
    virtual int AddRef();
    virtual int Release();
};
void* __fastcall GetThing(void*);   // 0x00bddd00
struct Small7 { uint32_t d[7]; uint8_t b; void* Init(); };
// ---- items of slice s00744ad0 end

// ---- hand-kept items of s00745ac0 begin (functions of this slice that mig7 skips stay in the TU and need them; rewrite.py drops items only they use)
    extern float g_f1485720; // 0x01485720
    extern float g_f140d674; // 0x0140d674
    extern float g_f162eb0c; // 0x0162eb0c
    extern float g_f162eb10; // 0x0162eb10
    extern float g_f162eb14; // 0x0162eb14
    extern float g_f162ec38; // 0x0162ec38
struct cSPTransform_s0074_5ac0;
struct cSPBoundingBox_s0074_5ac0 {
    Vec3 mMin;   // +0x00
    Vec3 mMax;   // +0x0c
    void Transform(const cSPTransform_s0074_5ac0& xf);   // 0x00409dd0
};
struct cSPTransform_s0074_5ac0 {
    unsigned short mFlags;             // +0x00
    unsigned short mModificationCount; // +0x02
    Vec3 mTranslation;                 // +0x04
    float mScale;                      // +0x10
    float mRotation[9];                // +0x14
};
struct Vec6 {
    float a, b, c, d, e, f;
    Vec6() {}
    Vec6(const Vec6& o) { a = o.a; b = o.b; c = o.c; d = o.d; e = o.e; f = o.f; }
};
struct P6 { float a, b, c, d, e, f; };
struct cOccluder_s0074_5ac0 {
    float a, b, c, d, e, f;
};
typedef bool (__cdecl *cOccluderCompare)(const cOccluder_s0074_5ac0&, const cOccluder_s0074_5ac0&);
struct FloatKeyPair {
    float x, y;
    FloatKeyPair() {}
    FloatKeyPair(const FloatKeyPair& v) { x = v.x; y = v.y; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct FloatKeyLess { bool operator()(const FloatKeyPair& a, const FloatKeyPair& b) const { return a[1] < b[1]; } };
struct FloatKeyGreater { bool operator()(const FloatKeyPair& a, const FloatKeyPair& b) const { return a[1] > b[1]; } };
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int align,
                                       const char* file, int line);   // 0x00f473a0
extern float g_f162eb0c, g_f162eb10, g_f162eb14, g_f162ec38, g_f1485720; // 0x0162eb0c
extern float g_f1537ab0, g_f1537ab4, g_f1537ab8, g_f13eb1bc, g_f140d674;
void Matrix3_Assign(void* dst, const void* src);                      // 0x0041cb40
void cSPTransform_Assign(cSPTransform_s0074_5ac0* dst, const cSPTransform_s0074_5ac0* src); // 0x00537dc0
void BoundingBox_TransformBy(cSPBoundingBox_s0074_5ac0* box, const cSPTransform_s0074_5ac0* xf); // 0x00409dd0
int  FUN_006ffbd0(const void* v, float r);                            // 0x006ffbd0
int  cFrustumCull_FrustumTestSphere(void* self, const void* p, unsigned flags); // 0x00700120
int  FUN_00511140(void* p);                                          // 0x00511140
typedef bool (__cdecl *Compare24)(const P6&, const P6&);
struct E20 { uint32_t flags; float x, y, z, w; };
struct Node18 {
    void* pLeft;      // +0x00
    void* pRight;     // +0x04
    void* pParent;    // +0x08
    int   mColor;     // +0x0c
    uint32_t mKey;    // +0x10
    void*    mRef;    // +0x14
};
struct DrawRecord {
    void* mOwner;          // +0x00
    int   mFlags;          // +0x04
    unsigned short mA;     // +0x08
    unsigned short mB;     // +0x0a
    Vec3  mPos;            // +0x0c
    float mScale;          // +0x18
    float mRotation[9];    // +0x1c
    int   mR0;             // +0x40
    int   mR1;             // +0x44
    int   mR2;             // +0x48
    Vec3  mDir;            // +0x4c
    float mDirScale;       // +0x58
    bool  mB0;             // +0x5c
    bool  mB1;             // +0x5d
    int   mP0;             // +0x60
    int   mP1;             // +0x64
    float mF0;             // +0x68
    float mF1;             // +0x6c
    float mF2;             // +0x70
    float mF3;             // +0x74
    float mF4;             // +0x78
    float mF5;             // +0x7c
    float mF6;             // +0x80
    float mF7;             // +0x84
    float mF8;             // +0x88
    float mF9;             // +0x8c
    int   mLast;           // +0x90
};
struct FrustumFilterArg {
    uint32_t mA;       // +0x00
    uint32_t mB;       // +0x04
    uint32_t mC;       // +0x08
    uint32_t mD;       // +0x0c
    int (__cdecl* mCallback)(void*); // +0x10
    unsigned char mE;  // +0x14
    unsigned char mF;  // +0x15
};
struct CullModel {
    unsigned char pad0[0x0c];
    uint32_t mFlags;        // +0x0c
    cSPTransform_s0074_5ac0 mTransform; // +0x10
    unsigned char pad48[0x4c - 0x48];
    uint32_t mMaskA;        // +0x4c
    uint32_t mMaskB;        // +0x50
    unsigned char pad54[0x65 - 0x54];
    unsigned char mC0;      // +0x65
    unsigned char pad66[0x74 - 0x66];
    float mRadius;          // +0x74
    cSPBoundingBox_s0074_5ac0 mBox;    // +0x78
    unsigned char pad90[0x94 - 0x90];
};
struct SlotObj { void F(int idx, void* handle); };
struct ObjD8 { void G(void* info); };
struct MWInternal {
    unsigned char pad0[0x9c];
    SlotObj* mSlots[4];      // +0x9c
    unsigned char padAC[0xd8 - 0xac];
    ObjD8* mD8;              // +0xd8
};
struct HullModel {
    unsigned char pad0[0xa8];
    Vec3 mMin;     // +0xa8
    Vec3 mMax;     // +0xb4
};
struct ModelInternal {
    unsigned char pad0[0x78];
    Vec3 mMin;     // +0x78
    Vec3 mMax;     // +0x84
    unsigned char pad90[0xac - 0x90];
    HullModel* mHull;   // +0xac
    unsigned char padB0[0xe4 - 0xb0];
    cSPTransform_s0074_5ac0 mTransform; // +0xe4
};
struct CModelWorldStub {
    void GetHullBoundingBox(void* handle, cSPBoundingBox_s0074_5ac0* out);
};
struct ListNode { ListNode* pNext; ListNode* pPrev; };
struct GroupSlot {
    unsigned char pad0[0x1b4];
    int mCount;              // +0x1b4
    void* mSlotObj;          // +0x1cc
    bool mFlag;              // +0x1d0
};
struct GroupInternal : ListNode {
    unsigned char pad8[0x134 - 0x8];
    void* mObj;              // +0x134
};
struct GroupWorld {
    unsigned char pad0[0x19c];
    ListNode mGroupList;         // +0x19c
    unsigned char pad1a4[0x1cc - 0x1a4];
    void* mSlotObj;              // +0x1cc
    void AssignGroup(void* newObj, int idx, bool flag);
};
namespace __equiv_ann1 {
struct ObjD8 {
    void G();   // 0x0041d8b0 (equiv t3)
};
}
namespace __equiv_ann1 {
struct SlotObj {
    void F();   // 0x00743150 (equiv t3)
};
}
// ---- hand-kept items of s00745ac0 end

// ---- hand-kept items of s007469b0 begin (functions of this slice that mig7 skips stay in the TU and need them; rewrite.py drops items only they use)
#pragma inline_depth(0)
#pragma inline_depth()
void cHierGrid_Remove(void* grid, int id);                                     // 0x00704100
void FUN_00745340(void);                                                       // 0x00745340
void  operator_delete_(void* p);
struct RCObj {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    int mRefCount;   // +4
};
struct OccInfo { int mId; Vec3 mPosition; float mRadius; };   // 0x14
struct CModelWorld {
    unsigned char pad0[0x14];
    int mNumModels;                      // +0x14 (anchor of mModelList dummy)
    unsigned char pad18[0x2bc - 0x18];
    OccInfo* mOccluders;                 // +0x2bc

    void SetWorldBounds(Vec3 bounds[2], float a, float b);
    void UpdateOccluder(int idx, Vec3* pos, float radius);
    void ShutdownModel(int model);
};
struct VViewer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                 virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                 virtual void v8(); };
struct Mat3 { float m[9]; void Assign(const void* src); };   // 0x0041cb40
struct Rec48 {
    int a, b, c;      // +0 +4 +8
    short d;          // +0xc
    short e;          // +0xe
    Vec3 pos;         // +0x10
    float scale;      // +0x1c
    Mat3 rot;         // +0x20
    unsigned char f;  // +0x44
    Rec48();
};
struct Stub007470c0 { void F(); };
struct Stub00747190 { void* F(int* src); };
struct Stub00747270 { void F(); };
// ---- hand-kept items of s007469b0 end

// ---- hand-kept items of s00747920 begin (functions of this slice that mig7 skips stay in the TU and need them; rewrite.py drops items only they use)
void  FUN_00745e00(void* first, int top, int size, int pos, float vx, float vy, uint32_t cmp);
void  FUN_00745e80(void* first, int top, int size, int pos, float vx, float vy, uint32_t cmp);
static inline void RelObj(RCObj* o)
{
    if (o && --o->mRefCount == 0) {
        o->mRefCount = 1;
        (*(void(__thiscall**)(RCObj*, int))(*(void**)o))(o, 1);
    }
}
struct Stub00747920 { void F(); };
struct Mat3_s0074_7920 { float m[9]; Mat3_s0074_7920() {} Mat3_s0074_7920(const Mat3_s0074_7920& o) { for (int i = 0; i < 9; ++i) m[i] = o.m[i]; } };
struct Rec38 {
    int a; short b, c; int d, e, f, g;
    Mat3_s0074_7920 rot;   // +0x18
};
struct Rec38Stub { Rec38* F(Rec38* src); };
struct E3C { int key; RCObj* obj; short a, b; int d, e, f, g, h, i, j, k, l, m; };
struct E3CResult { int cur; };
struct Occluder { float a, b, c, d, e, f; };
typedef bool (__cdecl* OccluderCmp)(const Occluder&, const Occluder&);
void AdjustHeapOccluder(Occluder* first, int top, int size, int pos, Occluder value, OccluderCmp cmp);
struct Occluder4 { float a, b, c, d, e, f; };
struct FKP { float x, y; FKP() {} FKP(const FKP& v) { x = v.x; y = v.y; } };
struct CmpGt { bool operator()(const FKP& a, const FKP& b) const { return a.y > b.y; } };
struct CmpLt { bool operator()(const FKP& a, const FKP& b) const { return a.y < b.y; } };
// 0x3c-byte POD element: dword key, two words, then 13 floats (+8..+0x38)
struct Plain3C74 { uint32_t key; unsigned short a, b; float f[13]; };
// deque iterator passed by value: {current, block begin, block end, map slot}
struct DequeBlockIter74 { char* cur; char* begin; char* end; char** map; };
// 0x1c-byte refcounted element: key, object (+4), five dwords (+8..+0x18)
struct RCElem3C74 { uint32_t key; RCObj* obj; uint32_t f0, f1, f2, f3, f4; };
static inline void AddRefRaw74(RCObj* o)
{
    if (o) (*(void(__thiscall**)(RCObj*))(*(void***)o)[0])(o);
}
static inline void ReleaseRaw74(RCObj* o)
{
    if (o) (*(void(__thiscall**)(RCObj*))(*(void***)o)[1])(o);
}
static inline void CopyElem3C74(RCElem3C74* d, const RCElem3C74* s)
{
    d->key = s->key;
    RCObj* o = s->obj;
    RCObj* old = d->obj;
    if (o != old) {
        AddRefRaw74(o);
        d->obj = o;
        ReleaseRaw74(old);
    }
    d->f0 = s->f0;
    d->f1 = s->f1;
    d->f2 = s->f2;
    d->f3 = s->f3;
    d->f4 = s->f4;
}
// ---- hand-kept items of s00747920 end

// ---- hand-kept items of s00748800 begin (functions of this slice that mig7 skips stay in the TU and need them; rewrite.py drops items only they use)
extern int g_appProps;     // 0x015fd918
extern float g_f162ec4c[9];   // 0x0162ec4c
#pragma pack(push, 4)
#pragma pack(pop)
struct cSPTransform_s0074_8800 {
    unsigned short mFlags; unsigned short mModificationCount;
    Vec3 mTranslation; float mScale; float mRotation[9];
};
struct cSPBoundingBox_s0074_8800 { Vec3 mMin; Vec3 mMax; };
void  translateTransform(void* out, void* a, const void* b);
void  cSPTransform_Assign(void* dst, const void* src);
void  cSPBoundingBox_Transform(cSPBoundingBox_s0074_8800* box, const void* xf);
int   FUN_00490330(float* p);
int   cModelInstance_IntersectsSphere(void* inst, const float* pos, const void* xf, bool b);
struct CullModel_s0074_8800 {
    unsigned char pad0[0x0c];
    uint32_t mFlags;         // +0x0c
    unsigned char pad10[0x4c - 0x10];
    uint32_t mMaskA;         // +0x4c
    uint32_t mMaskB;         // +0x50
    unsigned char pad54[0x65 - 0x54];
    unsigned char mC0;       // +0x65
    unsigned char pad66[0x74 - 0x66];
    float mRadius;           // +0x74
    float mBoxMinX;          // +0x78
    unsigned char pad7c[0x84 - 0x7c];
    float mBoxMaxX;          // +0x84
    unsigned char pad88[0x9c - 0x88];
    void* mInst1;            // +0x9c
    unsigned char pada0[0xac - 0xa0];
    void* mInst2;            // +0xac
    unsigned char padb0[0xe4 - 0xb0];
    unsigned char mTransform[0x38]; // +0xe4
};
struct SphereArg {
    uint32_t a, b, c, d;
    int (__cdecl* cb)(void*);
    unsigned char e, f;
};
struct QueryArg {
    unsigned __int64 incMask;            // 0x00 include mask
    unsigned __int64 excMask;            // 0x08 exclude mask
    bool (__cdecl* filter)(void*);       // 0x10
    unsigned char lodDefault;            // 0x14
    unsigned char qflags;                // 0x15
};
inline unsigned BitOf(uint32_t v, int n) { return (v >> n) & 1; }
struct QModelInst {
    unsigned char pad[0xcc];
    int mHasData;                        // 0xcc
    bool PickLineWithHit(int a, int b, void* xf, float* outDist);   // 0x0073e080
};
struct QXform {
    unsigned short mFlags, mCount;
    Vec3 mTranslation; float mScale; float mRot[9];
    QXform();
    QXform& operator=(const QXform&);     // 0x00537dc0
};
extern const float g_f140d674_s0074_8800;   // 0x0140d674
QXform::QXform()
{
    mFlags = 0; mCount = 0;
    mTranslation.x = g_f162eb0c; mTranslation.y = g_f162eb10; mTranslation.z = g_f162eb14;
    mScale = g_f1485720;
    for (int i = 0; i < 9; ++i) mRot[i] = g_f162ec4c[i];
}
struct QNode {
    QNode* mNext;                        // 0x00
    unsigned char pad4[0x0c - 4];
    uint32_t mFlags;                     // 0x0c
    unsigned char pad10[0x4c - 0x10];
    unsigned __int64 mMask;              // 0x4c
    unsigned char pad54[0x65 - 0x54];
    unsigned char mLod;                  // 0x65
    unsigned char pad66[0x74 - 0x66];
    float mRadius;                       // 0x74
    float mBoxMin;                       // 0x78
    unsigned char pad7c[0x84 - 0x7c];
    float mBoxMax;                       // 0x84
    unsigned char pad88[0x9c - 0x88];
    QModelInst* mInst1;                  // 0x9c
    unsigned char pada0[0xac - 0xa0];
    QModelInst* mInst2;                  // 0xac
    unsigned char padb0[0xe4 - 0xb0];
    unsigned char mXf[0x38];             // 0xe4
};
struct QCollection {
    int Query(int a, int b, float f, int cap, QNode** out);   // 0x00702860
};
bool FUN_00700c80(int a, int b, Vec3* pos, float radius, float* outDist);
bool FUN_00744050(int a, int b, QXform* xf, float* box, float* outDist);
__forceinline void ConsiderModel(QNode* m, int a, int b, QueryArg* q, float& best, QNode*& bestM)
{
    QXform local;
    if (!(m->mFlags & 1)) return;
    if (!(q->incMask == 0 || (m->mMask & q->incMask) != 0)) return;
    if ((m->mMask & q->excMask) != 0) return;
    if (q->filter != 0 && !q->filter((char*)m + 8)) return;
    int lod;
    if ((q->qflags & 1) && BitOf(m->mFlags, 8))
        lod = m->mLod;
    else
        lod = q->lodDefault;
    local = *(QXform*)((char*)m + 0x10);
    if (BitOf(m->mFlags, 7) || (q->qflags & 2)) {
        local.mCount++;
        local.mScale = g_f1485720;
    }
    Vec3 pos;
    pos.x = local.mTranslation.x;
    pos.y = local.mTranslation.y;
    pos.z = local.mTranslation.z;
    float dist;
    if (!FUN_00700c80(a, b, &pos, m->mRadius * local.mScale, &dist)) return;
    bool ok;
    if (lod >= 3 && m->mInst1 != 0 && m->mInst1->mHasData != 0) {
        unsigned char tmp[56];
        translateTransform(tmp, m->mXf, &local);
        ok = m->mInst1->PickLineWithHit(a, b, tmp, &dist);
    } else if (lod >= 2 && m->mInst2 != 0 && m->mInst2->mHasData != 0) {
        unsigned char tmp[56];
        translateTransform(tmp, m->mXf, &local);
        ok = m->mInst2->PickLineWithHit(a, b, tmp, &dist);
    } else if (lod >= 1 && !(m->mBoxMin > m->mBoxMax)) {
        ok = FUN_00744050(a, b, &local, &m->mBoxMin, &dist);
    } else {
        ok = true;
    }
    if (!ok) return;
    if (dist < best) {
        best = dist;
        bestM = m;
    }
}
struct cModelWorld_s0074_8800 {
    unsigned char pad0[0x118];
    QCollection mTree;                   // 0x118
    unsigned char pad119[0x13c - 0x119];
    int mCountA;                         // 0x13c
    int mCountB;                         // 0x140
    unsigned char pad144[0x19c - 0x144];
    QNode mList;                         // 0x19c (list anchor)

    void* FindClosest(int a, int b, float* outDist, QueryArg* q);
};
// ---- hand-kept items of s00748800 end

// ---- items of slice s00749370 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPTransform_s0074_9370 {
    unsigned short mFlags; unsigned short mModificationCount;
    Vec3 mTranslation; float mScale; float mRotation[9];
};
int   FUN_00700c80(const void* a, const void* b, const float* p, float r, void* out);
int   FUN_0073e080(const void* a, const void* b, const void* xf, void* out);
int   FUN_00744050(const void* a, const void* b, const void* xf, const void* box, void* out);
int   FUN_00743fb0(const void* p, float r, const void* box);
int   cModelInstance_PickLine(void* inst, const float* pos, float r, const void* xf, bool b);
struct CMWModel {
    unsigned char pad0[0x04];
    uint32_t mFlags;         // +0x04
    unsigned char pad8[0x44 - 0x08];
    uint32_t mMaskA;         // +0x44
    uint32_t mMaskB;         // +0x48
    unsigned char pad4c[0x5d - 0x4c];
    unsigned char mC0;       // +0x5d
    unsigned char pad5e[0x6c - 0x5e];
    float mRadius;           // +0x6c
    float mBoxMinX;          // +0x70
    unsigned char pad74[0x7c - 0x74];
    float mBoxMaxX;          // +0x7c
    unsigned char pad80[0x94 - 0x80];
    void* mInst1;            // +0x94
    unsigned char pad98[0xa4 - 0x98];
    void* mInst2;            // +0xa4
    unsigned char pada8[0xdc - 0xa8];
    unsigned char mTransform[0x38]; // +0xdc
};
struct FilterArg {
    uint32_t a, b, c, d;
    int (__cdecl* cb)(void*);
    unsigned char e, f;
};
// ---- items of slice s00749370 end

// ---- hand-kept items of s0074a290 begin (functions of this slice that mig7 skips stay in the TU and need them; rewrite.py drops items only they use)
extern "C" void __cdecl eastl_dealloc(void* p);
static inline void** VT(void* p) { return *(void***)p; }
struct cSPTransform_s0074_a290 {
    uint16_t f0;
    uint16_t f2;
    float    f4;
    float    f8;
    float    fc;
    float    f10;
    float    m[9];        // +0x14
    void operator=(const cSPTransform_s0074_a290& o);
};
extern cSPTransform_s0074_a290 translateTransform(const void* xform, const void* src);
struct cModelInstance_s0074_a290 {
    bool BuildBaked(cSPTransform_s0074_a290* t, void* arg);   // FUN_00743270
    bool GetMeshesX(void* arg);       // FUN_0073eb90
};
namespace SP {
struct cModelWorld_s0074_a290 {
    char pad[0x800];

    void ReleaseTransformedHull(void** pp);              // 0074a650 0x0074a650
    void FreeTransformedBuffer();                        // 0074b150
    void RemoveOccluder(int idx);                        // 0074a8c0 0x0074a8c0
    bool GetBakedMeshes(void* model, void* arg2);        // 0074a690
    bool GetBakedMeshesUnscaled(void* model, void* arg2); // 0074a700 0x0074a700
    bool GetBakedMeshes2(void* model, void* arg2, cSPTransform_s0074_a290* out);  // 0074a780
    bool GetMeshes(void* model, void* arg2, cSPTransform_s0074_a290* out);        // 0074a850 0x0074a850
    static void SetExternalEffectsTransform(void* a, void* b, void* c);  // 0074a290
    void SubA490(void* a, void* b);                      // 0074a490
    void SubA920(void* a, void* b);                      // 0074a920
};  // namespace SP
}
struct HullVtbl { virtual void slot0(); virtual void slot1(); };
struct TransformedHull {
    char pad0[0x10];
    void* p10;      // +0x10
    char pad1[4];
    HullVtbl* p18;  // +0x18
};
// ---- hand-kept items of s0074a290 end

// ---- hand-kept items of s0074b170 begin (functions of this slice that mig7 skips stay in the TU and need them; rewrite.py drops items only they use)
extern const float kDefaultFloat;   // 0x015d1168
extern const bool kDefaultBool;     // 0x015d115d
struct IPropList;
struct ListNode_s0074_b170 { ListNode_s0074_b170* prev; ListNode_s0074_b170* next; char pad[4]; uint32_t flags; };
namespace SP {
struct cModelWorld_s0074_b170 {
    char pad0[0x1c];
    char mWorldType;       // +0x1c
    char pad1[0x1a0 - 0x1d];
    ListNode_s0074_b170  mListA;      // +0x19c anchor area
    char pad2[4];
    ListNode_s0074_b170  mListB;      // +0x1a4 anchor area
    void AddAttachments(ListNode_s0074_b170* n);  // 0x0074ac80 (SP::cModelWorld::AddAttachments)
    void ShutdownModel(ListNode_s0074_b170* n);  // 0x00746b90 (SP::cModelWorld::ShutdownModel)
    void SetInWorld(ListNode_s0074_b170* n, bool b);
    void UpdateFromPropList(IPropList* pl, void* mdl, uint32_t flags, int unused);  // 0x0074b760 (SP::cModelWorld::UpdateFromPropList)
};
}
namespace SP {
struct cLoadingModel_s0074_b170 {  // 0x50 bytes
    uint32_t pad[0x14];
    ~cLoadingModel_s0074_b170();
};
}
namespace SP {
struct LoadDeque { ~LoadDeque(); };
}
namespace SP {
struct cLoadQueue {
    char pad[4];
    cLoadingModel_s0074_b170 arr[8];                       // +4, 0x50 each
    LoadDeque dq;                               // +0x284
    ~cLoadQueue();
};
}
struct Vec3f { float x, y, z; };
struct Mat3f { float m[9]; };
struct FloatField {                              // float member assigned through a user operator=
    float v;
    FloatField& operator=(const float& o) { v = o; return *this; }
};
struct BBoxf { Vec3f mMin, mMax; };
struct Matrix33Template {                       // rw::math::fpu::Matrix33Template<float,0>
    float m[9];
    Matrix33Template() {}
    Matrix33Template(const Matrix33Template& x);   // 0x0041cb40 (Matrix3::Assign), out of line
};
struct RwMat33 {
    float m[9];
    RwMat33(const Matrix33Template& x);            // 0x0041cb40 (row-wise copy), out of line
};
struct V3 {                                     // Vector3 with a user copy ctor (movss copies)
    float x, y, z;
    uint32_t pad;
    V3() {}
    V3(float a, float b, float c) : x(a), y(b), z(c) {}
    V3(const V3& o) : x(o.x), y(o.y), z(o.z) {}
};
Matrix33Template Matrix33FromEulerXYZ(const V3& angles);   // 0x00453920
struct XForm {                                  // cSPTransform, 0x38 bytes
    uint16_t mFlags;
    uint16_t mCount;
    Vec3f mOffset;
    float mScale;
    Mat3f mRot;
};
struct Property {
    void* mpData;           // +0
    uint32_t pad4;
    int mnItemCount;        // +8
    uint32_t padC;
    uint16_t mnFlags;       // +0x10
    uint16_t mnType;        // +0x12

    float* GetFloat();      // 0x0041ea70
    BBoxf* GetBBox();       // 0x005f2320
    __forceinline void* Items()
    {
        if (mnFlags & 0x30)
            return mpData;
        return mnType ? (void*)this : 0;
    }
};
const Vec3f* GetDefaultVec3();      // 0x006bb5e0
const BBoxf* GetDefaultBBox();      // 0x006bb630
const float* GetDefaultVec4();      // 0x006bb610
__forceinline const bool* ValBool(Property* p)
{
    if (p->mnType == 1 || p->mnType == 0x10) return (const bool*)p->Items();
    return &kDefaultBool;
}
__forceinline const Vec3f* ValVec3(Property* p)
{
    if (p->mnType == 0x31 || p->mnType == 0x10) return (const Vec3f*)p->Items();
    return GetDefaultVec3();
}
__forceinline const BBoxf* ValBBox(Property* p)
{
    if (p->mnType == 0x39 || p->mnType == 0x10) return (const BBoxf*)p->Items();
    return GetDefaultBBox();
}
__forceinline const float* ValVec4(Property* p)
{
    if (p->mnType == 0x34 || p->mnType == 0x10) return (const float*)p->Items();
    return GetDefaultVec4();
}
struct IPropList {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual bool Get(uint32_t id, Property** out);       // +0x24
};
bool __cdecl GetPropertyAsFloatArray(IPropList* pl, uint32_t id, int* count, float** arr);   // 0x006a08b0
struct BBoxMember : BBoxf {
    void TransformBy(XForm* t);             // 0x00409dd0 (cSPBoundingBox::Transform)
};
struct ModelRec {                               // model record passed to UpdateFromPropList
    char pad0[0xc];
    uint32_t mFlags;                            // +0x0c
    char pad10[0x54 - 0x10];
    float mQuat[4];                             // +0x54
    char pad64[0x70 - 0x64];
    uint16_t mUpdateCount;                      // +0x70
    char pad72[2];
    FloatField mRadius;                         // +0x74
    BBoxMember mBox;                            // +0x78
    char pad90[0x9c - 0x90];
    int f9c;                                    // +0x9c
    char pada0[0xac - 0xa0];
    int fac;                                    // +0xac
    char padb0[0xd4 - 0xb0];
    float* mpArr;                               // +0xd4
    char padd8[0xe4 - 0xd8];
    XForm mXform;                               // +0xe4
    char pad11c[0x129 - 0x11c];
    uint8_t mCount129;                          // +0x129
};
extern const Mat3f gIdentity3;      // 0x0162ec4c
extern const Vec3f gZeroVec3;       // 0x0162eb0c
static __forceinline float Len3(const Vec3f& v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
static __forceinline const float& MaxF(const float& a, const float& b) { return (a < b) ? b : a; }
__forceinline const float* ValFloat(Property* p);  // 0x0074b760 (defined below; used by a stub's inline body)
void SP::cModelWorld_s0074_b170::UpdateFromPropList(IPropList* pl, void* mdl, uint32_t flags, int unused)
{
    ModelRec* m = (ModelRec*)mdl;
    XForm* t = &m->mXform;
    BBoxMember* box = &m->mBox;
    t->mRot = gIdentity3;
    t->mScale = 1.0f;
    t->mOffset = gZeroVec3;
    t->mFlags = 0;
    t->mCount = 0;
    box->mMin.x = -1.0f; box->mMin.y = -1.0f; box->mMin.z = -1.0f;
    box->mMax.x = 1.0f; box->mMax.y = 1.0f; box->mMax.z = 1.0f;
    m->mRadius = 1.0f;

    Property* prop = 0;
    bool hasBBox = false;

    if (pl->Get(0xfba611, &prop)) {
        t->mScale = *ValFloat(prop);
        t->mCount++;
    }
    if (pl->Get(0xfba610, &prop)) {
        V3 v(*(const V3*)ValVec3(prop));
        t->mFlags |= 4;
        t->mCount++;
        t->mOffset = *(Vec3f*)&v;
    }
    if (pl->Get(0xfba613, &prop)) {
        const Vec3f* d = ValVec3(prop);
        float dx = d->x, dy = d->y, dz = d->z;
        V3 e(dx * 0.017453292f, dy * 0.017453292f, dz * 0.017453292f);
        RwMat33 rot(Matrix33FromEulerXYZ(e));
        t->mFlags |= 2;
        t->mCount++;
        *(RwMat33*)&t->mRot = rot;
    }
    if (pl->Get(0x3704e55, &prop) && !*ValBool(prop))
        m->mFlags |= 0x40000;
    else
        m->mFlags &= 0xfffbffff;

    if (m->f9c == 0 && m->fac == 0) {
        if (pl->Get(0x31d2791, &prop)) {
            hasBBox = true;
            BBoxf* b = prop->GetBBox();
            box->mMax = b->mMax;
            box->mMin = b->mMin;
            if (t->mScale != 1.0f || (t->mFlags & 6))
                box->TransformBy(t);
        }
        if (pl->Get(0x31d2792, &prop)) {
            hasBBox = false;
            m->mRadius = *prop->GetFloat();
            if (t->mScale != 1.0f || (t->mFlags & 6)) {
                float r = m->mRadius.v * t->mScale;
                m->mRadius.v = r;
                m->mRadius.v = Len3(t->mOffset) + r;
            }
        }
    }
    m->mFlags &= 0xfffcffff;

    if (pl->Get(0xf9efba, &prop)) {
        hasBBox = true;
        const BBoxf* b = ValBBox(prop);
        box->mMax = b->mMax;
        box->mMin = b->mMin;
        if (t->mScale != 1.0f || (t->mFlags & 6))
            box->TransformBy(t);
        m->mFlags |= 0x10000;
        m->mFlags |= 0x20000;
    }
    if (pl->Get(0xf9efb9, &prop)) {
        m->mRadius = *ValFloat(prop);
        if (t->mScale != 1.0f || (t->mFlags & 6)) {
            float r = t->mScale * m->mRadius.v;
            m->mRadius.v = r;
            m->mRadius.v = Len3(t->mOffset) + r;
        }
        m->mFlags |= 0x20000;
    } else if (hasBBox) {
        Vec3f n;
        n.x = -box->mMin.x;
        n.y = -box->mMin.y;
        n.z = -box->mMin.z;
        const Vec3f& mx = m->mBox.mMax;
        const float& cz = MaxF(n.z, mx.z);
        const float& cy = MaxF(n.y, mx.y);
        const float& cx = MaxF(n.x, mx.x);
        m->mRadius.v = sqrtf(cz * cz + cy * cy + cx * cx);
    }
    if (!(flags & 0x10000000)) {
        int count;
        if (GetPropertyAsFloatArray(pl, 0x2e33a81, &count, &m->mpArr)) {
            if (count > 0)
                m->mCount129 = (uint8_t)count;
            else
                m->mpArr = 0;
        }
    }
    if (pl->Get(0xfba612, &prop)) {
        const float* q = ValVec4(prop);
        float a = q[0], b2 = q[1], c = q[2];
        float d = q[3];
        m->mQuat[0] = a; m->mQuat[1] = b2; m->mQuat[2] = c; m->mQuat[3] = d;
        m->mFlags |= 2;
    }
    AddAttachments((ListNode_s0074_b170*)m);
    m->mUpdateCount++;
}
// ---- hand-kept items of s0074b170 end

// ---- items of slice s0074c260 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memmove_(void* dst, const void* src, unsigned size);
extern "C" void __cdecl OpDeleteArr(void* p);   // 0xf47380
extern char g_fn743910[];
extern char g_fn74d080[];   // 0x74d080
extern "C" void __cdecl operator_delete_arr(void* p);
struct VecInt {
    char pad0[0x4c];
    int* begin;   // +0x4c
    int* end;     // +0x50
    bool remove_first(int v);
};
struct E18 {
    float a, b, c, d, e, f;
    E18& operator=(const E18& o) { a = o.a; b = o.b; c = o.c; d = o.d; e = o.e; f = o.f; return *this; }
};
struct E18Vt {
    void DoInsert(E18* pos, const E18* v);   // 0074c020
};
struct Vec18 {
    E18* begin;   // +0x00
    E18* end;     // +0x04
    E18* cap;     // +0x08
    void push_back(const E18* v);
};
namespace eastl {
template <typename T> struct iterator_traits;
}
namespace eastl {
template <typename T> struct iterator_traits<T*> { typedef T value_type; };
}
namespace eastl {
template <typename It, typename Compare>
void partial_sort(It first, It middle, It last, Compare compare);   // out of line elsewhere
}
namespace eastl {
template <typename It, typename Compare>
inline It median(It a, It b, It c, Compare compare)
{
    if (compare(*a, *b)) {
        if (compare(*b, *c)) return b;
        else if (compare(*a, *c)) return c;
        else return a;
    } else if (compare(*a, *c)) return a;
    else if (compare(*b, *c)) return c;
    return b;
}
}
namespace eastl {
template <typename It, typename T, typename Compare>
It get_partition(It first, It last, T pivotValue, Compare compare)
{
    for (;; ++first) {
        while (compare(*first, pivotValue)) ++first;
        --last;
        while (compare(pivotValue, *last)) --last;
        if (first >= last) return first;
        T temp(*first);
        *first = *last;
        *last = temp;
    }
}
}
namespace eastl {
template <typename It, typename Size, typename Compare>
void quick_sort_impl(It first, It last, Size kRecursionCount, Compare compare)
{
    typedef typename iterator_traits<It>::value_type value_type;
    while ((last - first) > 28 && (kRecursionCount > 0)) {
        const It position_partition(eastl::get_partition(first, last, *eastl::median(first, first + (last - first) / 2, last - 1, compare), compare));
        eastl::quick_sort_impl(position_partition, last, --kRecursionCount, compare);
        last = position_partition;
    }
    if (kRecursionCount == 0)
        eastl::partial_sort(first, last, last, compare);
}
}
struct cDrawModelInfo { void* p; float key; };
struct DrawGreater { int pad; bool operator()(const cDrawModelInfo& a, const cDrawModelInfo& b) const { return a.key > b.key; } };
struct cAlphaSortLessComparator { int pad; bool operator()(const cDrawModelInfo& a, const cDrawModelInfo& b) const { return a.key < b.key; } };
struct cOccluder_s0074_c260 {
    float f[6];
    cOccluder_s0074_c260() {}
    cOccluder_s0074_c260(const cOccluder_s0074_c260& o) { f[0] = o.f[0]; f[1] = o.f[1]; f[2] = o.f[2]; f[3] = o.f[3]; f[4] = o.f[4]; f[5] = o.f[5]; }
};
typedef bool (__cdecl *OccCmp)(const cOccluder_s0074_c260&, const cOccluder_s0074_c260&);
struct ModelKey { uint32_t inst, type, group; };
struct PropListW { bool GetDescription(uint32_t hash); };
extern PropListW* g_appProps_s0074_c260;   // 0x15fd918
bool __cdecl GetPropertyAsKey(void* props, uint32_t id, ModelKey* out);   // 0x6a1250
#define V(n) virtual void v##n();
struct ResMgrW {
    V(0) V(1) V(2)
    virtual bool Lookup0c(ModelKey* key, RefCounted** out, int a, int b, int c, int d);   // 0x0c
    V(4)
    virtual bool Find14(ModelKey* key, RefCounted** out);                                  // 0x14
    V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
    virtual void Notify38(uint32_t a, uint32_t b);                                         // 0x38
    V(15) V(16) V(17) V(18) V(19) V(20) V(21)
    virtual int Error58(ModelKey* key);                                                    // 0x58
};
ResMgrW* __cdecl GetResMgrW();    // 0x67dcd0
ResMgrW* __cdecl GetResMgrW2();   // 0x67dd60
struct TmpVec {
    uint32_t* b; uint32_t* e; void* owner; uint32_t pad[3]; uint32_t prefix; uint32_t buf[32];
    TmpVec() : b(buf), e(buf), owner(0), prefix(0) {}
};
struct RefHolder { RefCounted* p; RefHolder() : p(0) {} ~RefHolder() { if (p) p->Release(); } };
void __cdecl FillResourceList(RefCounted* res, TmpVec* out, void* fn);   // 0x7141e0
void __fastcall DestructRange(TmpVec* v, int, uint32_t* b, uint32_t* e); // 0x70f520
struct LoadReq {
    uint32_t key; RefCounted* model; uint32_t a4, a5, idx, z0, z1;
    ~LoadReq() { if (model) model->Release(); }
};
struct LoadQueue {
    uint32_t d;
    void Push(LoadReq* r);           // 0x74bda0
    void Remove(uint32_t* pkey);     // 0x74be40
};
struct ModelEntry {
    char pad0[8]; uint32_t key; uint32_t flags0; char pad10[0x128]; int idx;   // flags at +0xc, idx at +0x138
};
struct cModelWorld_s0074_c260 {
    char pad0[0x314];
    LoadQueue queue;            // +0x314
    uint32_t active[8][0x14];   // +0x318, stride 0x50 (first dword compared)
    bool ModelIsResidentInMemory(RefCounted* model);  // 0x0074c670 (cModelWorld::ModelIsResidentInMemory)
    void __stdcall UpdateFromPropList(RefCounted* model, ModelEntry* entry, int idx, int z);   // 0x74b760 (free in orig)
    void ScheduleForLoad(ModelEntry* entry, RefCounted* model, uint32_t a4, uint32_t a5);  // 0x0074c910 (cModelWorld::ScheduleForLoad)
    void Load74a920(RefCounted* model, ModelEntry* entry, int idx);   // 0x74a920
};
void __stdcall UpdateFromPropList(RefCounted* model, ModelEntry* entry, int idx, int z);
struct JobW { char pad[0x20]; RefCounted* res; };
struct cJobW {
    void Wait();        // 0x6926b0
    void GetStatus();   // 0x690120
    void Run6913c0(struct JobW* j);              // 0x6913c0
    bool Continuation(void* fn, void* arg);      // 0x68f9f0
};
struct ResListW { void Fill(TmpVec* out, void* fn); };   // 0x73bd60 (thiscall on the resource)
struct PropOwner { char pad[0x10]; uint32_t flags; };
void __cdecl FUN_00756790(JobW** job, uint32_t inst, uint32_t grp, uint32_t flags);
struct LoadJob {
    uint32_t pad0;
    PropOwner* props;      // +0x04
    uint32_t pad8;
    uint32_t grp;          // +0x0c
    uint32_t flags;        // +0x10
    char pad14[0x10];
    uint32_t userArg;      // +0x24
    char pad28[4];
    int state;             // +0x2c
    JobW* job;             // +0x30
    RefCounted* refs[6];   // +0x34
    uint32_t count;        // +0x4c (overlaps refs end; see original)
    bool Step(cJobW* cj);
};
struct E14V { float x, y, z, w; };
struct E14 {
    int a; E14V v;
    E14(const E14& o) {
        a = o.a;
        unsigned sign = (unsigned)o.a >> 31;
        if ((sign & 1) == 0) {
            E14V* d = &v;
            if (d) { d->x = o.v.x; d->y = o.v.y; d->z = o.v.z; d->w = o.v.w; }
        }
    }
    E14& operator=(const E14& o);   // 0x7456a0
};
E14* __cdecl copy_backward14(E14* first, E14* last, E14* dest);          // 0x745f40
E14* __cdecl uninit_copy14(E14* first, E14* last, E14* dest);            // 0x745bb0
void* __cdecl operator_new_dbg(unsigned size, const char* name, int a, int b, const char* file, int line);
struct VecE14 {
    E14* mBegin; E14* mEnd; E14* mCap;
    void DoInsertValue(E14* pos, const E14& value);
};
struct ListNode_s0074_c260 { ListNode_s0074_c260* next; };
struct ModelNode {   // list node for models, 0x134/+0x98 fields used below
    ListNode_s0074_c260 link;
    char pad4[0x94];
    struct ResChain* chain;   // +0x98
    char pad9c[0x98];
    uint32_t handle;          // +0x134
};
struct ResChain { char pad[0x30]; ResChain* next; };
struct ReleaseTarget { V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
    virtual void Free(uint32_t h); };       // slot 8 = 0x20
struct MsgHeader { char pad[8]; uint32_t a; uint32_t pad2; uint32_t b; uint32_t pad3; uint32_t c; };
struct cModelWorldMsg {
    char pad[0x194 - 8];       // this here is the IMessageListener subobject (world+8)
    ListNode_s0074_c260 listA;            // +0x194 sentinel
    ListNode_s0074_c260 listB;            // +0x19c sentinel
    char pad1a4[0x1c4 - 0x1a4];
    ReleaseTarget* target;     // +0x1c4
    bool HandleMessage(uint32_t msgId, MsgHeader* msg);
};
void __stdcall ShutdownModel(cModelWorld_s0074_c260* w, ModelNode* n);                       // 0x746b90 (thiscall)
struct cModelWorldX {
    void ShutdownModel(ModelNode* n);                                              // 0x746b90
    void ScheduleForLoad(ModelNode* n, ResChain* chain, uint32_t a, uint32_t b);   // 0x74c910
};
// ---- items of slice s0074c260 end

// ---- items of slice s0074d4b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefObj { virtual int AddRef(); virtual int Release(); };
struct PropRef {
  IRefObj* p;
  PropRef() : p(0) {}
  ~PropRef() { if (p) p->Release(); }
  void reset() {
    if (p) {
      IRefObj* t = p;
      p = 0;
      t->Release();
    }
  }
};
struct IPropMgr {
  virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3();
  virtual void pv4(); virtual void pv5(); virtual void pv6(); virtual void pv7();
  virtual void pv8(); virtual void pv9(); virtual void pv10();
  virtual bool GetPropertyList(uint32_t id, uint32_t group, IRefObj** out);   // +0x2c
};
IPropMgr* __cdecl PropertyManager();                                          // 0x0067de30
struct cCookie {
  virtual void* DeletingDtor(int flags);
  int mRefCount;
  char pad8[0xa8 - 8];
  float mV0[3];          // +0xa8
  float mV1[3];          // +0xb4
  float mScale;          // +0xc0
  char padc4[0xcc - 0xc4];
  uint8_t mFlagCC;       // +0xcc
  void FUN_0073ab40(uint32_t v);   // 0x0073ab40
};
struct CookieRef {
  cCookie* p;
  CookieRef() : p(0) {}
  ~CookieRef() {
    if (p) {
      int n = p->mRefCount - 1;
      p->mRefCount = n;
      if (n == 0) {
        p->mRefCount = 1;
        p->DeletingDtor(1);
      }
    }
  }
  CookieRef& operator=(const CookieRef& o);   // 0x00609ea0 AutoRefCount<cCookie>::operator=
};
struct cB4Obj {
  uint32_t first;
  char pad[0x18 - 4];
  void* FUN_007454f0();           // 0x007454f0
};
struct cModelWorld_s0074_d4b0;
struct cModelNode {
  cModelNode* mpNext;       // +0x00
  cModelNode* mpPrev;       // +0x04
  uint32_t obj8;            // +0x08 (model object starts here)
  uint32_t mFlags;          // +0x0c
  char mXform[0x38];        // +0x10 cSPTransform
  char pad48[4];
  uint64_t mMask;           // +0x4c (type mask)
  char pad54[0x65 - 0x54];
  uint8_t mLod;             // +0x65
  char pad66[0x74 - 0x66];
  float mRadius;            // +0x74
  float mBoxMin[3];         // +0x78
  float mBoxMax[3];         // +0x84
  char pad90[0x98 - 0x90];
  IRefObj* mProps;          // +0x98
  cCookie* mCookie;         // +0x9c
  char pada0[0xac - 0xa0];
  cCookie* mCookie2;        // +0xac
  char padb0[4];
  cB4Obj mB4;               // +0xb4
  uint8_t mFlagCC;          // +0xcc
  char padcd[0x12c - 0xcd];
  uint32_t mFlags12c;       // +0x12c
  char pad130[0x138 - 0x130];
  uint32_t mCreateFlags;    // +0x138
  cModelNode(cModelWorld_s0074_d4b0* world);   // 0x00746e50
  void* Obj() { return (char*)this + 8; }
};
struct cFixedAlloc {          // EA::Allocator fixed pool at 0x0162ed08
  char pad[0x10];
  void** mpFree;              // +0x10 (0x0162ed18) head of the free list
  bool AddCore(int a, int b); // 0x00926650
  void* Alloc();              // 0x004fde40
};
extern cFixedAlloc gModelNodeAlloc;
struct PtrVec {
  void** mpBegin; void** mpEnd; void** mpCapacity;
  void DoInsertValue(void** pos, void* const& v);       // 0x006c1570
  void push_back(void* const& v) {
    if (mpEnd < mpCapacity) {
      void** e = mpEnd;
      mpEnd = e + 1;
      if (e) *e = v;
    } else {
      DoInsertValue(mpEnd, v);
    }
  }
  void PushObj(void* obj) {     // push_back of a temporary: the value lives in a stack slot
    void** e = mpEnd;
    void* v = obj;
    if (e < mpCapacity) {
      mpEnd = e + 1;
      if (e) *e = v;
    } else {
      DoInsertValue(e, v);
    }
  }
  void clear() {
    void** first = mpBegin;
    void** last = mpEnd;
    memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
    mpEnd -= (last - first);   // element count: (last-first)>>2, then *4
  }
};
struct cModelFilter {
  uint64_t incl;               // +0x00 required type bits (0 = any)
  uint64_t excl;               // +0x08 excluded type bits
  bool (__cdecl* pred)(void* obj);   // +0x10 optional predicate on the model object
  uint8_t lod;                 // +0x14 default detail level
  uint8_t fl;                  // +0x15 bit0: use per-node lod, bit1: force unit scale
  uint16_t pad;
};
struct cAppProps { char pad[0x2c]; int f2c; char pad30[0x94 - 0x30]; int f94; char pad98[0x118 - 0x98]; int f118; };
struct cGlobalA { char pad[0x3c]; cAppProps* sub; };
extern cGlobalA* g_015fd918;    // 0x015fd918 (SP::sAppProperties)
bool __cdecl CreateModelInstance(uint32_t a, uint32_t b, CookieRef* out, uint32_t lod);   // 0x00754ba0 SP::CreateModelInstance
uint32_t __cdecl FUN_007453d0(void* a, cCookie* c, uint32_t flags);                        // 0x007453d0
struct cModelWorldQuery { int FUN_00702860(const float* p0, const float* p1, float radius, int max, cModelNode** out); };  // 0x00702860
struct cModelWorld_s0074_d4b0 {
  char pad0[0x1e];
  uint8_t mbFallback;                  // +0x1e
  char pad1f[0x118 - 0x1f];
  cModelWorldQuery mQuery;             // +0x118 (spatial index)
  char pad11c[0x13c - 0x11c];
  void* mpIndexBegin;                  // +0x13c
  void* mpIndexEnd;                    // +0x140
  char pad144[0x19c - 0x144];
  cModelNode* mListA_next;             // +0x19c sentinel of the active list
  cModelNode* mListA_prev;             // +0x1a0
  cModelNode* mListB_next;             // +0x1a4 sentinel of the secondary list
  cModelNode* mListB_prev;             // +0x1a8
  char pad1ac[0x894 - 0x1ac];
  int mCount894;                       // +0x894
  int mCount898;                       // +0x898

  void* CreateModel(uint32_t a, uint32_t b, uint32_t flags);       // 0x0074d4b0
  bool CollectModels(PtrVec* out, const cModelFilter* f);          // 0x0074d870
  bool CollectSweep(const float* p0, const float* p1, PtrVec* out, const cModelFilter* f, float radius);  // 0x0074d990
  void UpdateFromPropList(IRefObj* props, cModelNode* node, uint32_t flags, int z);   // 0x0074b760
  void ScheduleForLoad(cModelNode* node, IRefObj* props, uint32_t a, uint32_t b);     // 0x0074c910
  cModelNode* ListAEnd() { return (cModelNode*)&mListA_next; }
  cModelNode* ListBEnd() { return (cModelNode*)&mListB_next; }
};
static inline void ListPushBack(cModelNode* s, cModelNode* n) {
  n->mpPrev = s->mpPrev;
  n->mpNext = s;
  s->mpPrev = n;
  n->mpPrev->mpNext = n;
}
// ---- items of slice s0074d4b0 end

// ---- items of slice s0074e2b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IntVec {
    int* mpBegin; int* mpEnd; int* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    int& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(int* pos, const int& v);   // 0x006ec4a0 (eastl::vector<int>::DoInsertValue, grow path)
    void push_back(const int& x)
    {
        if (mpEnd < mpCapacity) {
            int* e = mpEnd++;
            if (e)
                *e = x;
        } else
            DoInsertValue(mpEnd, x);
    }
};
struct VecIntAdd {
    char pad0[0x4c];
    IntVec v;     // +0x4c
    bool add_unique(int x);
};
struct Node { Node* next; Node* prev; };       // eastl::intrusive_list_node
struct ModelVec {                              // eastl::vector<cMWModelInternal*, sp_vector_allocator>
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void DoInsertValue(void** position, void* const& value);   // 0x006c1570
    void erase(void** first, void** last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(void* const& value)
    {
        if (mpEnd < mpCapacity) {
            void** p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
struct PropValues { char pad[0x2c]; int mValue; };
struct AppProperties { char pad[0x3c]; PropValues* mpValues; };
extern AppProperties* gAppProperties;          // 0x015fd918
struct HierGrid {
    char pad0[0x24];
    void** mGridsBegin;                        // +0x24 (retail grid at world+0x118)
    void** mGridsEnd;
    char pad1[0x78 - 0x2c];
    int QuerySphere(const void* center, const void* radius, int max, Node** out);   // 0x007027e0
    int QueryFrustum(const void* frustum, int max, Node** out);                      // 0x007026d0
    int QueryShape(float f, const void* p, int max, Node** out);                     // 0x00702760
    int QueryRay(const void* start, const void* end, float radius, int max, Node** out);  // 0x00702860
};
bool __cdecl FilterModelSphere(Node* item, const void* sphere, void* ctx);    // 0x00748800 (anonymous ns)
bool __cdecl FilterModelFrustum(Node* item, const void* frustum, void* ctx);  // 0x007460b0 (anonymous ns)
bool __cdecl FilterModelShape(Node* item, const void* p, float f, void* ctx); // 0x00748530
struct cModelWorld_s0074_e2b0 {
    char pad0[0x118];
    HierGrid mHierGrid;        // +0x118
    char pad1[0x19c - 0x118 - 0x78];
    Node mGroupList;           // +0x19c
    bool FindModelsInSphere(const void* sphere, ModelVec* out, void* ctx);                    // 0x0074ed00
    bool FindModelsInBox(const void* frustum, ModelVec* out, void* ctx);                      // 0x0074ee80
    bool FindModelsInShape(const void* p, float f, ModelVec* out, void* ctx);                 // 0x0074eb70
    bool RayCastModels(const struct Vec3_s0074_e2b0* start, const struct Vec3_s0074_e2b0* end, struct HitVec* out, const struct ModelFilter* filter, float radius);  // 0x0074e2b0
};
void __cdecl EASTL_allocator_deallocate(void* p);                   // 0x00f47380
struct RBNodeBase { RBNodeBase* mpNodeRight; RBNodeBase* mpNodeLeft; RBNodeBase* mpNodeParent; char mColor; };
RBNodeBase* __cdecl RBTreeIncrement(const RBNodeBase* pNode);       // 0x00921580
void __cdecl RBTreeErase(RBNodeBase* pNode, RBNodeBase* pNodeAnchor); // 0x00921880
struct IListenerV {           // vtable with slot 94
    virtual int AddRef();
    virtual int Release();
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
    virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
    virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
    virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73();
    virtual void s74(); virtual void s75(); virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
    virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83(); virtual void s84(); virtual void s85();
    virtual void s86(); virtual void s87(); virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91();
    virtual void s92(); virtual void s93();
    virtual void Notify();    // slot 94 (+0x178)
};
struct MapNode {              // rbtree_node<pair<unsigned, AutoRefCount<IListenerV>>>
    RBNodeBase base;
    unsigned mKey;            // +0x10
    IListenerV* mpValue;      // +0x14
};
struct ListenerMap {          // eastl::map<unsigned, AutoRefCount<IListenerV>> at resource +0xc
    int mCompare;             // +0x0 (empty compare + allocator)
    RBNodeBase mAnchor;       // +0x4
    unsigned mnSize;          // +0x14
    void DoNukeSubtree(RBNodeBase* pNode);   // 0x00d0c930
    ~ListenerMap() { DoNukeSubtree(mAnchor.mpNodeParent); }
    ListenerMap() {}
    struct iterator { RBNodeBase* mpNode; iterator() {} };
    iterator find(const unsigned& key);      // 0x00e5c780
    void clear()
    {
        DoNukeSubtree(mAnchor.mpNodeParent);
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    iterator end() { iterator e; e.mpNode = &mAnchor; return e; }
    __forceinline void erase(iterator position)
    {
        ((MapNode*)position.mpNode)->mpValue->Notify();
        --mnSize;
        RBTreeIncrement(position.mpNode);
        RBTreeErase(position.mpNode, &mAnchor);
        IListenerV* pValue = *(IListenerV* volatile*)&((MapNode*)position.mpNode)->mpValue;
        if (pValue) pValue->Release();
        EASTL_allocator_deallocate(position.mpNode);
    }
};
struct TableMap {             // second map at resource +0x28 (node nuke at 0x009a9600)
    int mCompare;
    RBNodeBase mAnchor;
    unsigned mnSize;
    void DoNukeSubtree(RBNodeBase* pNode);   // 0x009a9600
    ~TableMap() { DoNukeSubtree(mAnchor.mpNodeParent); }
};
struct IntVecSp {             // eastl::vector<int, sp_vector_allocator>
    int* mpBegin; int* mpEnd; int* mpCapacity;
    ~IntVecSp() throw() {
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
    }
};
template <class T> struct AutoRef_s0074_e2b0 {
    T* mpObject;
    AutoRef_s0074_e2b0() : mpObject(0) {}
    ~AutoRef_s0074_e2b0() { if (mpObject) mpObject->Release(); }
    AutoRef_s0074_e2b0& operator=(T* p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct ResBase0 { virtual ~ResBase0() {} };
struct ResBase1 { virtual ~ResBase1() {} };
struct EditorResource : ResBase0, ResBase1 {
    int mnRefCount;                // +0x8
    ListenerMap mListeners;        // +0xc
    int mPad24;                    // +0x24
    TableMap mTable;               // +0x28
    int mPad40[2];                 // +0x40
    AutoRef_s0074_e2b0<IListenerV> mpOwner;   // +0x48
    IntVecSp mIds;                 // +0x4c
    ~EditorResource();             // 0x0074f010
    bool Shutdown();               // 0x0074f0c0
    void RemoveListener(unsigned key);   // 0x0074f130
};
struct Vec3_s0074_e2b0 {
    float x, y, z;
    Vec3_s0074_e2b0() {}
    Vec3_s0074_e2b0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3_s0074_e2b0(const Vec3_s0074_e2b0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct HitPair { void* mpModel; float mDistance; };
struct HitVec {                       // eastl::vector<pair<cMWModel*, float>, sp_vector_allocator>
    HitPair* mpBegin; HitPair* mpEnd; HitPair* mpCapacity;
    void erase(HitPair* first, HitPair* last);                       // 0x00d018d0
    void insert(HitPair* position, const HitPair& value);            // 0x0074cd70
};
struct ModelFilter {
    unsigned __int64 mInclude;            // +0x0
    unsigned __int64 mExclude;            // +0x8
    bool (__cdecl *mpCallback)(void* model);   // +0x10
    unsigned char mDefaultLOD;            // +0x14
    unsigned char mFlags;                 // +0x15 (1: use model LOD, 2: ignore model scale)
};
// ---- items of slice s0074e2b0 end

// ---- items of slice s0074f200 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_renderStateDirty;                                         // 0x016fa38c
extern uint32_t g_016f9244;
extern uint32_t g_016f921c;
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
struct cFeedbackEvent;
struct RbNodeU {
    RbNodeU* mpNodeRight;     // +0
    RbNodeU* mpNodeLeft;      // +4
    RbNodeU* mpNodeParent;    // +8
    uint32_t mColor;          // +0xc
    uint32_t mKey;            // +0x10
    cFeedbackEvent* mValue;   // +0x14
};
struct cFeedbackEvent {
    virtual void AddRef();
    virtual void Release();    // ref-counted event: vtable slot 1 (the original unwind funclets 0x7455d0/0x7a9610 call [vt+4])
};
struct AutoRefFE {            // AutoRefCount<cFeedbackEvent>
    cFeedbackEvent* mp;
    AutoRefFE() : mp(0) {}
    AutoRefFE(const AutoRefFE& o) : mp(o.mp) { if (mp) mp->AddRef(); }
    ~AutoRefFE() { if (mp) mp->Release(); }
};
struct PairUU {               // eastl::pair<const uint32_t, AutoRefCount<cFeedbackEvent>>
    uint32_t first;
    AutoRefFE second;
    PairUU(const uint32_t& k, const AutoRefFE& v) : first(k), second(v) {}
};
struct RbIterU {
    RbNodeU* mpNode;
    RbIterU(RbNodeU* p) : mpNode(p) {}
    RbIterU(const RbIterU& o) : mpNode(o.mpNode) {}
};
struct CompactMapUU {
    char pad0[4];
    RbNodeU mAnchor;          // +4 (right/left/parent/color)
    uint32_t mKeyDummy;
    uint32_t mnSize;
    struct TrueTag {};        // eastl::true_type (1-byte empty tag passed by value)
    RbIterU Insert(RbIterU pos, const PairUU& value, TrueTag tag);   // 0x0074c170 (DoInsertValue with hint)
    cFeedbackEvent*& Subscript(const uint32_t& key);                                             // 0x0074f200
};
struct cOccluder_s0074_f200 {
    uint32_t v[6];
};
typedef bool(__cdecl* OccluderCompare)(const cOccluder_s0074_f200&, const cOccluder_s0074_f200&);
void quick_sort_impl(cOccluder_s0074_f200* first, cOccluder_s0074_f200* last, int kDepthLimit, OccluderCompare compare);   // 0x0074d190
void insertion_sort(cOccluder_s0074_f200* first, cOccluder_s0074_f200* last, OccluderCompare compare);                       // 0x007459c0
void insertion_sort_unguarded(cOccluder_s0074_f200* first, cOccluder_s0074_f200* last, OccluderCompare compare);             // 0x00745ac0
template <typename Size>
inline Size Log2(Size n)
{
    int i;
    for (i = 0; n; ++i)
        n >>= 1;
    return (Size)(i - 1);
}
struct Elem1C {
    uint32_t v[7];
    Elem1C(const Elem1C& o);                 // 0x00743b60
    Elem1C& operator=(const Elem1C& o);      // 0x00747190
};
Elem1C* ext_copy_range(Elem1C* first, Elem1C* last, Elem1C* dest);        // 0x00743d90 (returns end of dest)
void ext_copy_range_tail(Elem1C* first, Elem1C* last, Elem1C* dest);      // 0x00745f00
Elem1C* ext_copy_backward(Elem1C* first, Elem1C* last, Elem1C* dest);     // 0x00748470
struct VecElem1C {
    Elem1C* mpBegin;
    Elem1C* mpEnd;
    Elem1C* mpCapacity;
    uint32_t mAllocator;
    Elem1C* mpPoolBegin;    // +0x10 (fixed buffer; never freed)
    void DoInsertValue(Elem1C* position, const Elem1C& value);
};
static const char kEastlAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct SPTransform {
    char data[0x38];
    SPTransform& operator=(const SPTransform& o);   // 0x00537dc0
};
struct ModelInfo {
    uint32_t mId;
    SPTransform mTransform;
    ModelInfo(const ModelInfo& o);                  // 0x00747ac0
    ModelInfo& operator=(const ModelInfo& o)
    {
        mId = o.mId;
        mTransform = o.mTransform;
        return *this;
    }
};
ModelInfo* ext_mi_copy(ModelInfo* first, ModelInfo* last, ModelInfo* dest);                                              // 0x00748170
void ext_mi_fill_n(ModelInfo* dest, uint32_t n, const ModelInfo* value, uint32_t nAgain);                                // 0x00747c90
void ext_mi_copy_ex(ModelInfo** pResult, ModelInfo* first, ModelInfo* last, ModelInfo* dest, ModelInfo* firstAgain);     // 0x00747b70
ModelInfo* ext_mi_copy_backward(ModelInfo* first, ModelInfo* last, ModelInfo* dest);                                     // 0x007484f0
struct VecModelInfo {
    ModelInfo* mpBegin;
    ModelInfo* mpEnd;
    ModelInfo* mpCapacity;
    uint32_t mAllocator;
    ModelInfo* mpPoolBegin;
    void DoInsertValues(ModelInfo* position, uint32_t n, const ModelInfo& value);
};
struct ShaderRef {              // intrusive ref (refcount at +4, deleting dtor in slot 0)
    void* vtbl;
    int mnRefCount;
    int DrawBatch(void* arg, uint32_t drawArg);   // 0x0073fd20
};
struct ShaderRefPtr {
    ShaderRef* mp;
    ShaderRefPtr() : mp(0) {}
    ~ShaderRefPtr()
    {
        if (mp && --mp->mnRefCount == 0) {
            mp->mnRefCount = 1;
            ((void(__thiscall*)(ShaderRef*, int))(*(void***)mp)[0])(mp, 1);
        }
    }
};
struct cDrawModelInfo_s0074_f200 {
    char pad0[0xc];
    uint32_t mFlags;                  // +0xc
    char pad10[0x54 - 0x10];
    float mColor[4];                  // +0x54
    char pad64[0x9c - 0x64];
    ShaderRefPtr mShaders[4];         // +0x9c (indexed by mLayerType)
    char padac[0xb0 - 0xac];
    ShaderRef* mpAltShader;           // +0xb0
    char padb4[0xd8 - 0xb4];
    uint32_t mDrawArg;                // +0xd8
    char padDC[0x128 - 0xdc];
    uint8_t mLayerType;               // +0x128
    char pad129[0x134 - 0x129];
    void** mpExtra;                   // +0x134
};
static inline uint8_t VariantByte(const cDrawModelInfo_s0074_f200* i) { return *((const uint8_t*)i + 0x64); }
struct DrawEntry {
    cDrawModelInfo_s0074_f200* pInfo;
    float fDistance;
};
struct DrawList {
    DrawEntry* mpBegin;
    DrawEntry* mpEnd;
};
struct Float4 {
    float x, y, z, w;
    Float4() {}
    Float4& operator=(const Float4& o)
    {
        x = o.x;
        y = o.y;
        z = o.z;
        w = o.w;
        return *this;
    }
};
struct AlphaSortCompare {};
struct Camera {
    void GetFrustumPlanes(Float4* out);                                     // 0x007c44e0
};
void SortDrawList(DrawEntry* first, DrawEntry* last, AlphaSortCompare c);   // 0x0074d000 (eastl::quick_sort)
void SortDrawListOpaque(DrawEntry* first, DrawEntry* last, AlphaSortCompare c);   // 0x0074cf80
void PushShaderDataNull();                                                  // 0x00777bf0
void SetShaderConstant(int id, const void* data, bool bChanged);            // 0x00777ae0
void PopShaderData();                                                       // 0x00777c10
void SetBlendMode(uint32_t mode);                                           // 0x011f1340 (rw::graphics::GlobalState::SetBlendMode)
struct cModelWorld_s0074_f200 {
    char pad0[0x8a4];
    int mnDrawnOpaque;       // +0x8a4
    int mnDrawnAlpha;        // +0x8a8
    int mnDrawnTotal;        // +0x8ac
    void SetViewport(uint8_t* pVariant);       // 0x00745140 (thiscall on the world)
    void DrawLayer(bool bAlpha, DrawList* pList, uint32_t flags, void* pArg, Camera* pCamera);
};
static inline bool Differs(const Float4& a, const Float4& b)
{
    return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
}
static inline uint32_t SignBit(float f) { return (*(uint32_t*)&f) >> 31; }
struct RbAnchorBase {
    RbAnchorBase* mpNodeRight;
    RbAnchorBase* mpNodeLeft;
    RbAnchorBase* mpNodeParent;
    uint32_t mColor;
    RbAnchorBase() : mpNodeLeft(0), mpNodeParent(0), mColor(0) {}
};
struct RbTreeHeader {
    RbAnchorBase mAnchor;
    uint32_t mnSize;
    RbTreeHeader()
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        *(uint8_t*)&mAnchor.mColor = 0;
        mnSize = 0;
    }
};
struct FeedbackBaseA {
    virtual void a0();
};
struct FeedbackBaseB {
    uint32_t mRefCount;
    virtual void b0();
    FeedbackBaseB() : mRefCount(0) {}
};
struct cFeedbackMgr : FeedbackBaseA, FeedbackBaseB {
    uint32_t mpad0c;
    RbTreeHeader mTreeA;          // +0x10 .. +0x20
    uint32_t mpad24, mpad28;
    RbTreeHeader mTreeB;          // +0x2c .. +0x3c
    uint32_t mpad40;
    uint32_t mn44, mn48, mn4c, mn50, mn54;
    cFeedbackMgr();
    int AllocSlot(uint32_t key, uint32_t unused);   // 0x0074fe10
    bool StartJobs(void** pSource);                 // 0x0074fea0
    virtual void a0();
    virtual void b0();
};
struct SlotTree {
    uint32_t mpad;
    void find(RbNodeU** pResult, const uint32_t* key);              // 0x00e5c780 (rbtree<uint, pair<const uint, AutoRef<cFeedbackEvent>>>::find)
};
struct SlotIndexTree {
    uint32_t mpad;
    uint32_t& operator[](const uint32_t& key);                       // 0x00643a40 (map<uint,uint>::operator[])
};
struct SlotAllocator {
    char pad0[0x28];
    SlotTree mTree;                                                 // +0x28 (shared tree object; anchor at +0x2c)
    char mAnchor[0x18];                                             // +0x2c (tree anchor / end node)
    int mnNextSlot;                                                 // +0x44
    int Allocate(uint32_t key, uint32_t unused);
};
struct IJobManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual bool CreateJob(struct cJobRef* pRef);      // slot 4 (0x10)
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Lock();                               // slot 8 (0x20)
    virtual void Unlock();                             // slot 9 (0x24)
};
IJobManager* GetJobManager();                          // 0x0068f4d0
struct cJob {
    void (*mpCallback)(void*);                         // +0x00
    void* mpCallbackData;                              // +0x04
    char pad08[0x10];
    uint32_t mFlags;                                   // +0x18
    void SetDependency(cJob* pOther);                  // 0x00691380 (this = dependent)
    void Start();                                      // 0x006909b0
    void Release();                                    // 0x00690120
    void SetCallback(void (*f)(void*), void* data) { mpCallback = f; mpCallbackData = data; }
};
struct cJobRef {
    cJob* mp;
    void reset() { if (mp) { cJob* pOld = mp; mp = 0; pOld->Release(); } }
};
struct JobLock {
    IJobManager* m;
    JobLock(IJobManager* mgr) : m(mgr) { m->Lock(); }
    ~JobLock() { m->Unlock(); }
};
struct cFeedbackJobs {
    char pad0[0x1c];
    uint8_t mbStarted;                                 // +0x1c
    char pad1d[3];
    cJobRef mJobA;                                     // +0x20
    cJobRef mJobB;                                     // +0x24
    struct Tree28 {
        uint32_t mpad;
        void ResetTree(uint32_t first);                // 0x00478db0 (thiscall on this+0x28)
    } mTree28;                                         // +0x28
    uint32_t mnState;                                  // +0x2c
    cJobRef mJobC;                                     // +0x30
    char pad34[0x4c - 0x34];
    uint32_t mbActive;                                 // +0x4c
    void Assign(void** pSource);                       // 0x00747190
    bool Start(void** pSource);
};
void JobCallback(void*);                               // 0x0074d080
struct cOccluderInfo {
    float v[4];
    cOccluderInfo() {}
    cOccluderInfo(const cOccluderInfo& o)
    {
        v[0] = o.v[0];
        v[1] = o.v[1];
        v[2] = o.v[2];
        v[3] = o.v[3];
    }
};
struct SlotEntry {
    uint32_t mFlags;            // bit31 free, bit30 last, low 30 bits next-free link
    cOccluderInfo mItem;
};
struct SlotVectorOccluder {
    SlotEntry* mpBegin;
    SlotEntry* mpEnd;
    SlotEntry* mpCapacity;
    uint32_t mAllocator;
    uint32_t mUnused10;
    uint32_t mMinFree;          // +0x14
    uint32_t mFreeHead;         // +0x18
    void DoInsertEntry(SlotEntry* position, const SlotEntry& value);   // 0x0074ce20
    uint32_t create(const cOccluderInfo& item);
};
// ---- items of slice s0074f200 end

// ---- hand-kept items of s00750180 begin (functions of this slice that mig7 skips stay in the TU and need them; rewrite.py drops items only they use)
struct cOccluderInfo_s0075_0180 { int f0; int x, y, z; float r; };
struct SlotVector {
    cOccluderInfo_s0075_0180* mBegin;   // +0x00
    char pad0[0x18];
    int create(void* out);   // 00750030
};
struct MW6 {
    char pad[0x2bc];
    SlotVector vec;          // +0x2bc
    void AddOccluder(int* src, float f);
};
// ---- hand-kept items of s00750180 end

// ---- items of slice s007507e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3_s0075_07e0 { float x, y, z; };
}
namespace SP {
struct Matrix3 {
    float m[9];
    void Assign(const Matrix3& src);                    // 0x0041cb40
};
}
namespace SP {
struct cSPTransform {                                   // 0x38 bytes
    uint16_t mFlags;                                    // +0x00
    uint16_t mFlags2;                                   // +0x02
    Vec3_s0075_07e0     mOffset;                                   // +0x04
    float    mScale;                                    // +0x10
    Matrix3  mRotation;                                 // +0x14
    cSPTransform& operator=(const cSPTransform& o);     // 0x00537dc0
    void Accumulate(const cSPTransform* other);         // 0x0040ccb0
};
}
namespace SP {
struct cMWMesh {
    virtual void DeleteThis(int flags);                 // slot 0: scalar deleting destructor
    int mnRefCount;                                     // +0x04
    char pad08[0x70 - 8];
    cSPTransform mTransform;                            // +0x70
    char padA8[0xc8 - 0xa8];
    uint8_t mDrawFlags;                                 // +0xc8 (bit 0: alpha)

    void Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            DeleteThis(1);
        }
    }
};
}
namespace SP {
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
};
}
namespace SP {
struct cMWModelInternal_s0075_07e0 {
    cMWModelInternal_s0075_07e0* mpNext;                           // +0x00 (model list hook)
    char pad04[0xc - 4];
    uint32_t mFlags;                                    // +0x0c
    cSPTransform mTransform;                            // +0x10
    char pad48[0x4c - 0x48];
    uint32_t mGroupMask[2];                             // +0x4c
    char pad54[0x60 - 0x54];
    float mAlpha;                                       // +0x60
    char pad64[0x74 - 0x64];
    float mBoundingRadius;                              // +0x74
    char pad78[0x8c - 0x78];
    float mHorizonRadius;                               // +0x8c
    float mLODDistance;                                 // +0x90
    char pad94[0x9c - 0x94];
    AutoRefCount<cMWMesh> mLODs[4];                     // +0x9c
    char padAC[0xb0 - 0xac];
    cMWMesh* mpLowLODMesh;                              // +0xb0
    char padB4[0xd4 - 0xb4];
    float* mpLODThresholds;                             // +0xd4
    char padD8[0xe4 - 0xd8];
    cSPTransform mExtraTransform;                       // +0xe4
    char pad11c[0x128 - 0x11c];
    uint8_t mLOD;                                       // +0x128
    uint8_t mNumLODs;                                   // +0x129
    char pad12a[0x130 - 0x12a];
    uint32_t mLastVisibleFrame;                         // +0x130
};
}
namespace SP {
struct cDrawModelInfo_s0075_07e0 {
    cMWModelInternal_s0075_07e0* mpModel;
    float mDistance;
};
}
namespace SP {
struct DrawModelVector {                                // eastl::vector<cDrawModelInfo>
    cDrawModelInfo_s0075_07e0* mpBegin;
    cDrawModelInfo_s0075_07e0* mpEnd;
    cDrawModelInfo_s0075_07e0* mpCapacity;
    cDrawModelInfo_s0075_07e0* erase(cDrawModelInfo_s0075_07e0* first, cDrawModelInfo_s0075_07e0* last);       // 0x00d018d0
    void DoInsertValue(cDrawModelInfo_s0075_07e0* position, const cDrawModelInfo_s0075_07e0& v);    // 0x006ec390
    void push_back(const cDrawModelInfo_s0075_07e0& v)
    {
        if (mpEnd < mpCapacity) {
            cDrawModelInfo_s0075_07e0* p = mpEnd++;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};
}
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);       // memcpy thunk
namespace SP {
struct ModelPtrVector {                                 // eastl::vector<cMWModelInternal*>
    cMWModelInternal_s0075_07e0** mpBegin;
    cMWModelInternal_s0075_07e0** mpEnd;
    cMWModelInternal_s0075_07e0** mpCapacity;
    void resize(int n);                                                         // 0x00758ee0
    void DoInsertValue(cMWModelInternal_s0075_07e0** position, cMWModelInternal_s0075_07e0* const& v);  // 0x006ec4a0
    cMWModelInternal_s0075_07e0** erase(cMWModelInternal_s0075_07e0** first, cMWModelInternal_s0075_07e0** last)
    {
        FUN_011e0744(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(cMWModelInternal_s0075_07e0* const& v)
    {
        if (mpEnd < mpCapacity) {
            cMWModelInternal_s0075_07e0** p = mpEnd++;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};
}
namespace SP {
struct cOccluderSlot {                                  // spstl::slot_vector entry (0x14 bytes)
    uint32_t mFlags;                                    // bit 31: free
    Vec3_s0075_07e0 mCenter;
    float mRadius;
};
}
namespace SP {
struct cOccluder {
    Vec3_s0075_07e0 mDir;
    float mDistance;    // distance from the camera times cos(half angle)
    float mSinAngle;
    float mCosAngle;
};
}
namespace SP {
void EA_operator_delete_array(void* p);                 // 0x00f47380 (operator delete[])
}
namespace SP {
struct OccluderFixedVector {                            // eastl::fixed_vector<cOccluder, 16>
    cOccluder* mpBegin;
    cOccluder* mpEnd;
    cOccluder* mpCapacity;
    uint32_t mAllocator;
    cOccluder* mpPoolBegin;
    uint32_t mPad;
    cOccluder mBuffer[16];

    OccluderFixedVector()
    {
        cOccluder* p = mBuffer;
        mpEnd = p;
        mpPoolBegin = p;
        mpBegin = p;
        mpCapacity = (cOccluder*)((char*)mBuffer + sizeof(mBuffer));
    }
    ~OccluderFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            EA_operator_delete_array(mpBegin);
    }
    void push_back(const cOccluder& v);                 // 0x0074cdd0
};
}
namespace SP {
typedef bool(__cdecl* OccluderCompare_s0075_07e0)(const cOccluder&, const cOccluder&);
}
namespace SP {
bool __cdecl OccluderLess(const cOccluder& a, const cOccluder& b);                       // 0x00743920
}
namespace SP {
void __cdecl quick_sort(cOccluder* first, cOccluder* last, OccluderCompare_s0075_07e0 compare);     // 0x0074f3a0
}
namespace SP {
int __cdecl FUN_00745660(cOccluderSlot* first, cOccluderSlot* last, uint32_t frame);     // 0x00745660
}
namespace SP {
struct cFrustumCull_s0075_07e0 {
    void Setup(const void* cameraFrustum);              // 0x006ffe00
    void FUN_006ffa80(float f);                         // 0x006ffa80
    uint8_t TestSphere(const Vec3_s0075_07e0* center, float radius);   // 0x006ffbd0 (bit 0x40: outside)
};
}
namespace SP {
struct cHierGrid_s0075_07e0 {
    int FrustumQuery(cFrustumCull_s0075_07e0* cull, int maxCount, cMWModelInternal_s0075_07e0** out);   // 0x007026d0
};
}
namespace SP {
struct cCamera {
    char pad00[0xc0];
    char mFrustum[1];                                   // +0xc0
    void GetTransform(cSPTransform* out);               // 0x007c40f0
};
}
namespace SP {
struct Property_s0075_07e0 {
    void* mpData;                                       // +0x00 (value in place for small types)
    char pad04[0x10 - 4];
    uint8_t mFlags;                                     // +0x10 (0x30: value behind mpData)
    char pad11;
    uint16_t mType;                                     // +0x12 (0xd: float)
    float GetValueFloat() const { return *(const float*)((mFlags & 0x30) ? mpData : (const void*)this); }
};
}
namespace SP {
struct cModelTuning {
    char pad00[0x2c];
    int mCullLevel;                                     // +0x2c
    char pad30[0x9c - 0x30];
    float mLODScale;                                    // +0x9c
    char padA0[0xe0 - 0xa0];
    float mAlphaThreshold;                              // +0xe0
};
}
namespace SP {
struct cAppProperties {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08();
    virtual bool GetProperty(uint32_t id, Property_s0075_07e0*& out);   // +0x24
    char pad04[0x3c - 4];
    cModelTuning* mpTuning;                             // +0x3c
};
}
namespace SP {
extern cAppProperties* g_AppProperties;                 // 0x015fd918
}
namespace SP {
extern uint32_t g_FrameCounter;                         // 0x016f8cf8
}
namespace SP {
extern uint32_t g_AlphaFadeFlags;                       // 0x01537bf0
}
namespace SP {
extern Vec3_s0075_07e0 g_ZeroVector;                               // 0x0162eb0c
}
namespace SP {
extern Matrix3 g_IdentityMatrix;                        // 0x0162ec4c
}
namespace SP {
struct cDrawSetInfo_s0075_07e0 {                                   // 0x20 bytes
    uint32_t mIncludeMask[2];
    uint32_t mExcludeMask[2];
    char pad10[0x10];
};
}
namespace SP {
class cModelWorld_s0075_07e0 {
public:
    char pad000[0x28];
    cFrustumCull_s0075_07e0 mFrustumCuller;                        // +0x28
    char pad029[0x118 - 0x29];
    cHierGrid_s0075_07e0 mHierGrid;                                // +0x118
    char pad119[0x138 - 0x119];
    int mGridModelCount;                                // +0x138
    void* mGridBegin;                                   // +0x13c
    void* mGridEnd;                                     // +0x140
    char pad144[0x19c - 0x144];
    cMWModelInternal_s0075_07e0* mModelListHead;                   // +0x19c (intrusive list anchor)
    char pad1a0[0x1bc - 0x1a0];
    cDrawSetInfo_s0075_07e0 mDrawSets[(0x2b4 - 0x1bc) / 0x20];     // +0x1bc
    char pad2bc_[0x2b4 - 0x1bc - sizeof(cDrawSetInfo_s0075_07e0) * ((0x2b4 - 0x1bc) / 0x20)];
    float mHorizonCullFactor;                           // +0x2b4
    float mLODScale;                                    // +0x2b8
    cOccluderSlot* mOccludersBegin;                     // +0x2bc (spstl::slot_vector)
    cOccluderSlot* mOccludersEnd;                       // +0x2c0
    char pad2c4[0x2d0 - 0x2c4];
    uint32_t mOccludersFirstUsed;                       // +0x2d0
    char pad2d4[0x2d8 - 0x2d4];
    ModelPtrVector mDrawList;                           // +0x2d8
    char pad2e4[0x2ec - 0x2e4];
    DrawModelVector mOpaqueDrawList;                    // +0x2ec
    char pad2f8[0x300 - 0x2f8];
    DrawModelVector mAlphaDrawList;                     // +0x300
    char pad30c[0x8a0 - 0x30c];
    int mNumDrawModels;                                 // +0x8a0
    char pad8a4[0x8ac - 0x8a4];
    int mNumMeshesDrawn;                                // +0x8ac

    void UpdateVisibility(uint32_t flags, cCamera* camera, int drawSet);
};
}
// ---- items of slice s007507e0 end

// ---- hand-kept items of s00751560 begin (functions of this slice that mig7 skips stay in the TU and need them; rewrite.py drops items only they use)
namespace SP {
struct cSPVector3 {
  float x, y, z;
};
}
namespace SP {
struct cSPMatrix3 {
  float m[9];
};
}
namespace SP {
struct cSPTransform_s0075_1560 {
  uint16_t mFlags;
  uint16_t mModificationCount;
  cSPVector3 mTranslation;
  float mScale;
  cSPMatrix3 mRotation;
};
}
namespace SP {
class cMWObject_s0075_1560 {
 public:
  void* mWorld;
  uint32_t mFlags;
  char pad_8[0x38];
  int mRefCount;  // +0x40
};
}
namespace SP {
struct cModelInfo_s0075_1560 {
  cMWObject_s0075_1560* mObject;
  cSPTransform_s0075_1560 mLocalTransform;
};
}
namespace SP {
class cMWGroup_s0075_1560 {
 public:
  char pad_0[0x44];
  cModelInfo_s0075_1560* mObjectsBegin;
  cModelInfo_s0075_1560* mObjectsEnd;
  cModelInfo_s0075_1560* mObjectsCapacity;
};
}
namespace SP {
class cMWGroupInternal_s0075_1560 {
 public:
  void* mNodeNext;
  void* mNodePrev;
  cMWGroup_s0075_1560 mGroup;  // +0x8
};
}
namespace SP {
struct MWGroupDtorStub { void F(); };
}
// ---- hand-kept items of s00751560 end

// ---- hand-kept items of s00753270 begin (functions of this slice that mig7 skips stay in the TU and need them; rewrite.py drops items only they use)
void* RBTreeIncrement(void*);
struct TreeNode_00753540 {
  char pad_0[0x14];
  void* mObject;  // +0x14
};
struct TreeWalker_00753540 {
  char pad_0[0x10];
  void* mEnd;   // +0x10
  void* mRoot;  // +0x14
  void ForEach(float a, float b);
};
struct NodeRunThunk {
  void Run(float a, float b);
};
// ---- hand-kept items of s00753270 end

// ---- items of slice s00745ac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void FUN_007760a0(int a, int b, int c, int d, int e, void* f);        // 0x007760a0
int  SP_CreateModelInstance(unsigned a, int b, void* c);              // 0x00754ba0
int  FUN_007454f0(int x);                                            // 0x007454f0
int  FUN_007434b0(int x);                                            // 0x007434b0
void FUN_0073b980(void* a, void* b, void* c, void* d, void* e, void* f, void* g); // 0x0073b980
struct SlotObj_s0074_5ac0 { void F(int idx, void* handle); };
struct ObjD8_s0074_5ac0 { void G(void* info); };
struct MWInternal_s0074_5ac0 {
    unsigned char pad0[0x9c];
    SlotObj_s0074_5ac0* mSlots[4];      // +0x9c
    unsigned char padAC[0xd8 - 0xac];
    ObjD8_s0074_5ac0* mD8;              // +0xd8
};
struct VecField {
    void* mBegin;    // +0x00
    void* mEnd;      // +0x04
    unsigned char pad8[0x0c - 0x08];
    void* mCapacity; // +0x0c
    void* mStore;    // +0x10
    unsigned char pad14[0x18 - 0x14];
    void* mExtra;    // +0x18
    unsigned char pad1c[0x24 - 0x1c];
    void* mOther;    // +0x24
};
struct HullQuery {
    uint32_t mKey;    // +0x00
    uint32_t mType;   // +0x04
    void*    m0;      // +0x08
    void*    m1;      // +0x0c
    void*    m2;      // +0x10
    void*    m3;      // +0x14
    void*    mInst;   // +0x18
};
struct VariantKey { uint32_t a, b; int c; };
struct IVirtual { virtual int v0(int); virtual int v1(int); };
namespace __equiv_ann1 {
struct ObjD8_s0074_5ac0 {
    void G();   // 0x0041d8b0 (equiv t3)
};
}
namespace __equiv_ann1 {
struct SlotObj_s0074_5ac0 {
    void F();   // 0x00743150 (equiv t3)
};
}
// ---- items of slice s00745ac0 end

// ---- items of slice s007469b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void cHierGrid_Shutdown(void* grid);                                            // 0x00704060
void cHierGrid_Init(void* grid, void* bounds, float size, int a, int b);        // 0x00704260
void FUN_00745560(void* out, int a, int b, int c, int d, int e, int f, int g, int h, int i); // 0x00745560
int  FUN_007c4510(int a, float b, void* c, void* d);                           // 0x007c4510
void FUN_007453d0(void* p);                                                    // 0x007453d0
int  FUN_007454f0(int a, int b);                                               // 0x007454f0
int  SP_GetPropertyAsIntArray(void* props, uint32_t key, int* count, int* data); // 0x0051e5e0
void DrawRecord_CtorProto(void* owner);
// ---- items of slice s007469b0 end

// ---- items of slice s00747920 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPTransform_s0074_7920 {
    unsigned short mFlags; unsigned short mModificationCount;
    Vec3 mTranslation; float mScale; float mRotation[9];
};
void* operator_new(uint32_t n, const char* name, int a, int b, const char* file, int line);
void  FUN_007457a0(int a, int b);
void* FUN_00743fb0(void* p, float f, void* box);
struct CullModel_s0074_7920 {
    unsigned char pad0[0x0c];
    uint32_t mFlags;         // +0x0c
    unsigned char pad10[0x4c - 0x10];
    uint32_t mMaskA;         // +0x4c
    uint32_t mMaskB;         // +0x50
    unsigned char pad54[0x65 - 0x54];
    unsigned char mC0;       // +0x65
    unsigned char pad66[0x74 - 0x66];
    float mRadius;           // +0x74
    float mBoxMinX;          // +0x78
    unsigned char pad7c[0x84 - 0x7c];
    float mBoxMaxX;          // +0x84
    unsigned char pad88[0x9c - 0x88];
    void* mInst1;            // +0x9c
    unsigned char pada0[0xac - 0xa0];
    void* mInst2;            // +0xac
    unsigned char padb0[0xe4 - 0xb0];
    unsigned char mTransform[0x38]; // +0xe4
};
// ---- items of slice s00747920 end

// ---- items of slice s00748800 begin (TODO(rewrite): local stubs, replace by canonical classes)
int   ComposeTransforms(void* xf);
int   FUN_0073e080(float* a, int b, void* c, int d);
int   FUN_006ba870(int a);
struct PickSrc { unsigned short f0, f1; float a, b, c; int d; float rot[9]; };
// ---- items of slice s00748800 end

// ---- items of slice s0074a290 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_162eb0c, g_162eb10, g_162eb14, g_1485720;
extern char g_162ec4c[];
extern void __cdecl PropGetTransforms(void* list, unsigned key, int* count, void* out);  // 0x6a0c30
extern "C" void* __cdecl GfxAlloc(unsigned size, const char* name, int, int, int, int);  // 0xf473a0
extern bool __cdecl CreateModelInstance(unsigned id, unsigned idx, void** out, unsigned flags); // 0x754ba0
extern void __cdecl Sub7340(void* obj);                              // 0x747340
extern "C" float __cdecl sqrtf(float);
extern "C" void* __cdecl EffectsManager();     // 0x67ddd0
extern bool __cdecl PropReserve(void* list, unsigned key, int* count, void* out);     // 0x6a0ae0
extern bool __cdecl PropGetFloats(void* list, unsigned key, int* count, void* out);   // 0x6a08b0
extern bool __cdecl PropGetInts(void* list, unsigned key, int* count, void* out);     // 0x6a0990
extern "C" void* __cdecl memset(void*, int, unsigned);
static __forceinline void ReleaseSlot(void** slot)
{
    void* q = *slot;
    if (q) {
        *slot = 0;
        uint32_t* rc = (uint32_t*)((char*)q + 4);
        if (--*rc == 0) {
            *rc = 1;
            ((void(__thiscall*)(void*, int))VT(q)[0])(q, 1);
        }
    }
}
struct cSPTransform_s0074_a290_s0074_a290 {
    uint16_t f0;
    uint16_t f2;
    float    f4;
    float    f8;
    float    fc;
    float    f10;
    float    m[9];        // +0x14
    void operator=(const cSPTransform_s0074_a290_s0074_a290& o);   // 0x537dc0
    void Compose(const cSPTransform_s0074_a290_s0074_a290* o);   // ComposeTransforms 0x40ccb0
};
extern cSPTransform_s0074_a290_s0074_a290 translateTransform_s0074_a290(const void* xform, const void* src);   // 0x6271a0
struct Matrix3_s0074_a290 {
    float m[9];
    void Assign(const void* src);   // 0x41cb40
};
struct cModelInstance_s0074_a290_s0074_a290 {
    bool BuildBaked(cSPTransform_s0074_a290_s0074_a290* t, void* arg);   // FUN_00743270
    bool GetMeshesX(void* arg);       // FUN_0073eb90
};
namespace SP {
struct cModelWorld_s0074_a290_s0074_a290 {
    char pad[0x800];

    void ReleaseTransformedHull(void** pp);              // 0074a650
    void FreeTransformedBuffer();                        // 0074b150
    void RemoveOccluder(int idx);                        // 0074a8c0
    bool GetBakedMeshes(void* model, void* arg2);        // 0074a690
    bool GetBakedMeshesUnscaled(void* model, void* arg2); // 0074a700
    bool GetBakedMeshes2(void* model, void* arg2, cSPTransform_s0074_a290_s0074_a290* out);  // 0074a780
    bool GetMeshes(void* model, void* arg2, cSPTransform_s0074_a290_s0074_a290* out);        // 0074a850
    static void __stdcall SetExternalEffectsTransform(void* a, void* b, void* c);  // 0074a290
    void SubA490(void* a, void* b);                      // 0074a490
    void SubA920(void* list, void* obj, uint32_t flags); // 0074a920
    void AddAttachments(char* model);                    // 0074ac80
};  // namespace SP
}
struct EffRec {
    uint32_t id;       // +0x00
    uint32_t id2;      // +0x04
    void*    obj;      // +0x08
    cSPTransform_s0074_a290_s0074_a290 xf;   // +0x0c
    uint32_t pad;      // +0x44
};
typedef void (__cdecl *Sub9510Fn)(void*, unsigned, void*, unsigned);   // 0x6b9510
typedef void (__cdecl *VecCopyFn)(void*, const void*, unsigned);       // 0x11e0744
struct PropKey { uint32_t id; uint32_t id2; int idx; };             // 0xc bytes
extern bool __cdecl GetPropertyAsKey(void* list, unsigned key, PropKey* out);   // 0x6a1250
struct cSPBoundingBox_s0074_a290 {
    float w[6];
    void TransformBy(const void* xf);   // 0x409dd0
};
struct IRel { virtual void v0(); virtual void Release(); };
struct Rec48_s0074_a290 {
    uint32_t id;       // +0
    uint32_t id2;      // +4
    IRel*    obj;      // +8
    cSPTransform_s0074_a290_s0074_a290 xf;   // +0xc
    uint8_t  flag;     // +0x44
    Rec48_s0074_a290();                                    // 0x746de0
    ~Rec48_s0074_a290() { if (obj) obj->Release(); }       // 0xae9670
};
void* operator new[](size_t, const char*, int, int, int, int);   // 0xf473a0
#define VCALL(T, obj, off) ((T)VT(obj)[(off) / 4])
// ---- items of slice s0074a290 end

// @ 0x00743940
int cModelWorld56::Adjustor(int unused)
{
    (void)unused;
    return (int)((char*)this - 0xc);
}

// @ 0x00743950
void __stdcall SetTimeScale(int param_1, float scale)
{
    if (param_1 != 0) {
        *(float*)(param_1 + 0x114) = scale;
        return;
    }
    *(float*)0x11c = scale;
}

// @ 0x007439b0
int __stdcall OffsetOrE4(int param_1)
{
    if (param_1 != 0)
        return param_1 + 0xdc;
    return 0xe4;
}

// @ 0x007439d0
void cModelWorld56::SetCurveSegment(int* a, int* b, int index)
{
    char* p = (char*)this + index * 0x20;
    *(int*)(p + 0x1bc) = a[0];
    *(int*)(p + 0x1c0) = a[1];
    *(int*)(p + 0x1c4) = b[0];
    *(int*)(p + 0x1c8) = b[1];
    if (*(int*)(p + 0x1b4) < 0)
        *(int*)(p + 0x1b4) = 0;
}

// @ 0x00743a20
void cModelWorld56::GetCurveSegment(int* a, int* b, int index)
{
    char* p = (char*)this + index * 0x20;
    a[0] = *(int*)(p + 0x1bc);
    a[1] = *(int*)(p + 0x1c0);
    b[0] = *(int*)(p + 0x1c4);
    b[1] = *(int*)(p + 0x1c8);
}

// @ 0x00743a60
void cModelWorld56::SetCurveRange(int index, int begin, int end)
{
    char* p = (char*)this + index * 0x20;
    *(int*)(p + 0x1b4) = begin;
    *(int*)(p + 0x1b8) = end;
}

// @ 0x00743a80
void cModelWorld56::GetCurveRange(int index, int* begin, int* end)
{
    if (begin)
        *begin = *(int*)((char*)this + index * 0x20 + 0x1b4);
    if (end)
        *end = *(int*)((char*)this + index * 0x20 + 0x1b8);
}

// @ 0x00743b00
void SP::cModelWorld::ResetHighlightCurve()
{
    float v = *(float*)((char*)this + 0x890);
    *(float*)((char*)this + 0x87c) = v;
    *(float*)((char*)this + 0x860) = 0.0f;
}

// @ 0x00743b20
uint32_t Getb20(Model* model)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    return ~(m->mFlags138 >> 4) & 1;
}

// @ 0x00743b50
void* cModelWorld::VecClear()
{
    *(uint32_t*)this = 0;
    return this;
}

// @ 0x00743bb0
void __stdcall DestroyPtrRange(void** first, void** last)
{
    for (; first < last; ++first) {
        if (*first)
            EA_Free(*first);
    }
}

// @ 0x00743be0
void SortDescGuarded(Pair8* first, Pair8* last)
{
    if (first == last)
        return;
    Pair8* iSorted = first + 1;
    if (iSorted == last)
        return;
    do {
        Pair8 temp = *iSorted;
        Pair8* iNext = iSorted;
        if (iSorted != first) {
            do {
                if (!(temp.key > (iNext - 1)->key))
                    break;
                *iNext = *(iNext - 1);
                --iNext;
            } while (iNext != first);
        }
        *iNext = temp;
        ++iSorted;
    } while (iSorted != last);
}

// @ 0x00743c50
void SortDescUnguarded(Pair8* first, Pair8* last)
{
    for (Pair8* current = first; current != last; ++current) {
        Pair8* end = current;
        Pair8* prev = current - 1;
        Pair8 value = *current;
        while (value.key > prev->key) {
            *end = *prev;
            --end;
            --prev;
        }
        *end = value;
    }
}

// @ 0x00743cb0
void SortAscGuarded(Pair8* first, Pair8* last)
{
    if (first == last)
        return;
    Pair8* iSorted = first + 1;
    if (iSorted == last)
        return;
    do {
        Pair8 temp = *iSorted;
        Pair8* iNext = iSorted;
        if (iSorted != first) {
            do {
                if (!(temp.key < (iNext - 1)->key))
                    break;
                *iNext = *(iNext - 1);
                --iNext;
            } while (iNext != first);
        }
        *iNext = temp;
        ++iSorted;
    } while (iSorted != last);
}

// @ 0x00743d20
void SortAscUnguarded(Pair8* first, Pair8* last)
{
    for (Pair8* current = first; current != last; ++current) {
        Pair8* end = current;
        Pair8* prev = current - 1;
        Pair8 value = *current;
        while (value.key < prev->key) {
            *end = *prev;
            --end;
            --prev;
        }
        *end = value;
    }
}

// @ 0x00743d90
Elem28* UninitCopy(const Elem28* first, const Elem28* last, Elem28* dst)
{
    for (; first != last; ++first, ++dst)
        new (dst) Elem28(*first);
    return dst;
}

// @ 0x00743e50
void PromoteCocc(cOccluder6* first, int top, int pos, cOccluder6 value, bool (*compare)(const cOccluder6&, const cOccluder6&))
{
    int parent = (pos - 1) >> 1;
    while (pos > top && compare(first[parent], value)) {
        first[pos] = first[parent];
        pos = parent;
        parent = (pos - 1) >> 1;
    }
    first[pos] = value;
}

// @ 0x00743f00
void PromoteF00(Pair8* first, int top, int pos, Pair8 value)
{
    for (int parent = (pos - 1) >> 1;
         (pos > top) && (first[parent].key > value.key);
         parent = (pos - 1) >> 1) {
        first[pos] = first[parent];
        pos = parent;
    }
    first[pos] = value;
}

// @ 0x00743f60
void PromoteF60(Pair8* first, int top, int pos, Pair8 value)
{
    for (int parent = (pos - 1) >> 1;
         (pos > top) && (value.key > first[parent].key);
         parent = (pos - 1) >> 1) {
        first[pos] = first[parent];
        pos = parent;
    }
    first[pos] = value;
}

// @ 0x00743fb0
uint32_t BoxDistSq(const float* p, float radius, const float* box)
{
    float d2 = 0.0f;
    for (int i = 0; i < 3; ++i) {
        float v = p[i];
        if (v < box[i]) {
            float d = v - box[i];
            d2 += d * d;
        } else if (v > box[i + 3]) {
            float d = v - box[i + 3];
            d2 += d * d;
        }
    }
    return d2 <= radius * radius;
}

// @ 0x00744050
void TransformTwo(const cSPVector3_s0074_3b20* p1, const cSPVector3_s0074_3b20* p2, const cSPTransform_s0074_3b20* t, int a, int b)
{
    cSPVector3_s0074_3b20 r1, r2;
    {
        const cSPVector3_s0074_3b20* p = p1;
        cSPVector3_s0074_3b20 v;
        v.x = p->x - t->mTranslation.x;
        v.y = p->y - t->mTranslation.y;
        v.z = p->z - t->mTranslation.z;
        float s = t->mScale;
        if (s != 1.0f) {
            float inv = 1.0f / s;
            v.x *= inv; v.y *= inv; v.z *= inv;
        }
        if (t->mFlags & 2) {
            r1.x = t->mRotation.m[0]*v.x + t->mRotation.m[1]*v.y + t->mRotation.m[2]*v.z;
            r1.y = t->mRotation.m[3]*v.x + t->mRotation.m[4]*v.y + t->mRotation.m[5]*v.z;
            r1.z = t->mRotation.m[6]*v.x + t->mRotation.m[7]*v.y + t->mRotation.m[8]*v.z;
        } else {
            r1 = v;
        }
    }
    {
        const cSPVector3_s0074_3b20* p = p2;
        cSPVector3_s0074_3b20 v;
        v.x = p->x - t->mTranslation.x;
        v.y = p->y - t->mTranslation.y;
        v.z = p->z - t->mTranslation.z;
        float s = t->mScale;
        if (s != 1.0f) {
            float inv = 1.0f / s;
            v.x *= inv; v.y *= inv; v.z *= inv;
        }
        if (t->mFlags & 2) {
            r2.x = t->mRotation.m[0]*v.x + t->mRotation.m[1]*v.y + t->mRotation.m[2]*v.z;
            r2.y = t->mRotation.m[3]*v.x + t->mRotation.m[4]*v.y + t->mRotation.m[5]*v.z;
            r2.z = t->mRotation.m[6]*v.x + t->mRotation.m[7]*v.y + t->mRotation.m[8]*v.z;
        } else {
            r2 = v;
        }
    }
    LineClip(&r1, &r2, a, b);
}

// @ 0x007442c0
bool TransformTwoOffset(const cSPVector3_s0074_3b20* p1, const cSPVector3_s0074_3b20* p2, const cSPTransform_s0074_3b20* t, cSPVector3_s0074_3b20 a, cSPVector3_s0074_3b20 b, int flag, float pad)
{
    cSPVector3_s0074_3b20 r2, r1;
    {
        const cSPVector3_s0074_3b20* p = p1;
        cSPVector3_s0074_3b20 v;
        v.x = p->x - t->mTranslation.x;
        v.y = p->y - t->mTranslation.y;
        v.z = p->z - t->mTranslation.z;
        if (t->mScale != 1.0f) {
            float inv = 1.0f / t->mScale;
            v.x *= inv; v.y *= inv; v.z *= inv;
        }
        if (t->mFlags & 2) {
            // The original multiplies the z term first, then y, then x.
            r1.x = t->mRotation.m[2]*v.z + t->mRotation.m[1]*v.y + t->mRotation.m[0]*v.x;
            r1.y = t->mRotation.m[5]*v.z + t->mRotation.m[4]*v.y + t->mRotation.m[3]*v.x;
            r1.z = t->mRotation.m[8]*v.z + t->mRotation.m[7]*v.y + t->mRotation.m[6]*v.x;
        } else {
            r1 = v;
        }
    }
    {
        const cSPVector3_s0074_3b20* p = p2;
        cSPVector3_s0074_3b20 v;
        v.x = p->x - t->mTranslation.x;
        v.y = p->y - t->mTranslation.y;
        v.z = p->z - t->mTranslation.z;
        if (t->mScale != 1.0f) {
            float inv = 1.0f / t->mScale;
            v.x *= inv; v.y *= inv; v.z *= inv;
        }
        if (t->mFlags & 2) {
            r2.x = t->mRotation.m[2]*v.z + t->mRotation.m[1]*v.y + t->mRotation.m[0]*v.x;
            r2.y = t->mRotation.m[5]*v.z + t->mRotation.m[4]*v.y + t->mRotation.m[3]*v.x;
            r2.z = t->mRotation.m[8]*v.z + t->mRotation.m[7]*v.y + t->mRotation.m[6]*v.x;
        } else {
            r2 = v;
        }
    }
    if (pad != 0.0f) {
        float off = pad / t->mScale;
        a.x -= off; a.y -= off; a.z -= off;
        b.x += off; b.y += off; b.z += off;
    }
    return LineClip(&r1, &r2, (int)&a, flag);
}

// @ 0x007445b0
bool cModelWorld::CallOnLoad(Model* model, void* cb, void* data)
{
    bool onLoad = (model->mFlags >> 14) & 1;   // bool, like StallGetBoundingBox: the original reads
                                               // mFlags into eax, shr 0xe, then test al,1
    if (onLoad != 0) {
        ((void (__cdecl*)(Model*, void*))cb)(model, data);
        return true;
    }
    for (uint32_t i = 0; i < 8; ++i) {
        char* e = (char*)this + 0x318 + i * 0x50;
        if (*(Model**)e == model) {
            for (uint32_t j = 0; j < 8; ++j) {
                char* f = (char*)this + 0x318 + j * 0x50;
                if (*(Model**)f == model) {
                    *(void**)(f + 0x14) = cb;
                    *(void**)(f + 0x18) = data;
                    return true;
                }
            }
            return false;
        }
    }
    char* begin = *(char**)((char*)this + 0x5a0);
    char* segEnd = *(char**)((char*)this + 0x5a8);
    char** segTable = *(char***)((char*)this + 0x5ac);
    char* end = *(char**)((char*)this + 0x5b0);
    while (begin != end) {
        if (*(Model**)begin == model) {
            *(void**)(begin + 0x14) = cb;
            *(void**)(begin + 0x18) = data;
            return true;
        }
        begin += 0x1c;
        if (begin == segEnd) {
            begin = *++segTable;
            segEnd = begin + 0xe0;
        }
    }
    return false;
}

// @ 0x00744680
bool SP::cModelWorld::ModelsHavePreloaded(int i) const
{
    struct Entry { void* p0; void* p1; void* p2; uint32_t a; uint32_t b; };
    Entry* v = (Entry*)((char*)this + 0x5d0 + i * 0x14);
    return v->p0 == v->p1;
}

// @ 0x007446a0
float cModelWorld::StallGetBoundingBox(Model* model)
{
    bool b = (model->mFlags >> 17) & 1;
    if (!b)
        this->StallUntilLoaded(model);
    return model->mDefaultBoundingRadius;
}

// @ 0x007446c0
void* cModelWorld::GetNumAnimationGroups(Model* model)
{
    if (((model->mFlags >> 16) & 1) == 0)
        this->StallUntilLoaded(model);
    return (char*)model + 0x70;
}

// @ 0x007446e0
void cModelWorld::GetModelResourceIDs(Model* model, uint32_t* pInstance, uint32_t* pGroup)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    uint32_t inst = 0, group = 0;
    ResInfo* p = (ResInfo*)m->mpField90;
    volatile uint32_t tmp;
    if (p) {
        tmp = p->fieldC;
    } else {
        ResHolder* y = (ResHolder*)m->mpField9c;
        if (y) {
            p = y->Get();
            if (p) {
                y = (ResHolder*)m->mpField9c;
                p = y->Get();
                tmp = p->fieldC;
            }
        }
    }
    if (p) {
        group = p->field10;
        inst = p->field8;
    }
    if (pInstance)
        *pInstance = inst;
    if (pGroup)
        *pGroup = group;
}

// @ 0x00744760
void cModelWorld::StallUntilLoaded2(Model* model, uint32_t a)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cLoadQueue_s0074_3b20* q = (cLoadQueue_s0074_3b20*)m->mpField9c;
    if (q)
        q->StallUntilLoaded(a);
}

// @ 0x00744790
int cModelWorld::GetNumAnimations(Model* model)
{
    if (model) {
        cMWModelInternal* m = static_cast<cMWModelInternal*>(model);
        if (m) {
            cModelInstance* inst = m->mAnim[0];
            if (inst)
                return inst->GetAnimationIDs();
        }
    }
    return 0;
}

// @ 0x007447c0
int cModelWorld::GetAnimationIDs(Model* model, uint32_t* dst)
{
    if (model) {
        cMWModelInternal* m = static_cast<cMWModelInternal*>(model);
        if (m) {
            cModelInstance* inst = m->mAnim[0];
            if (inst)
                return inst->GetAnimIDs(dst, 0, 0);
        }
    }
    return 0;
}

// @ 0x007447f0
int cModelWorld::GetAnimationMoveToTimes(Model* model, int a, int b)
{
    if (model) {
        cMWModelInternal* m = static_cast<cMWModelInternal*>(model);
        if (m) {
            cModelInstance* inst = m->mAnim[0];
            if (inst)
                return inst->GetAnimMoveToTimes(b, a, 0);
        }
    }
    return 0;
}

// @ 0x00744830
int cModelWorld::GetDeformationAnimationIDs(Model* model, int a, int b)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetAnimMoveToTimes(b, a, 0) : 0;
}

// @ 0x00744870
void cModelWorld::AnimAction(Model* model, int arga, int argb, float argc, int argd)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance** p = m->mAnim;
    if (*p) {
        bool b = (argb == 2);
        if (argb == 2 || argb == 0)
            argb = 1;
        else
            argb = 0;
        int i = 0;
        do {
            cModelInstance* inst = *p;
            if (!inst)
                break;
            inst->SetActive(arga, argd, argb, argc, b);
            ++i;
            ++p;
        } while (i < 6);
        m->mFlags138 |= 0x40000000u;
    }
}

// @ 0x00744900
void cModelWorld::MoveToTime(Model* model, int a, float b, int c)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    int i = 0;
    cModelInstance** p = m->mAnim;
    do {
        cModelInstance* inst = *p;
        if (!inst)
            return;
        inst->MoveToTime(a, c, b);
        ++i;
        ++p;
    } while (i < 6);
}

// @ 0x00744950
void cModelWorld::SetWeight(Model* model, int a, float b, int c)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    int i = 0;
    cModelInstance** p = m->mAnim;
    do {
        cModelInstance* inst = *p;
        if (!inst)
            return;
        inst->SetWeight(a, c, b);
        ++i;
        ++p;
    } while (i < 4);
}

// @ 0x007449a0
bool cModelWorld::GetAnimationRange(Model* model, int a, int b, float& c, float& d)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    if (inst)
        return inst->GetAnimationRange(a, d, b, c);
    return false;
}

// @ 0x007449e0
int cModelWorld::GetNumBones(Model* model)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetNumBones() : 0;
}

// @ 0x00744a10
int cModelWorld::GetPoseTransforms(Model* model, void* dst, int original)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetPoseTransforms(dst, original) : 0;
}

// @ 0x00744a40
int cModelWorld::GetBoneTransforms(Model* model, void* dst)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetBoneTransforms(dst) : 0;
}

// @ 0x00744a70
int cModelWorld::GetBoneIDs(Model* model, void* dst)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetBoneIDs(dst) : 0;
}

// @ 0x00744aa0
int cModelWorld::GetBoneParents(Model* model, void* dst)
{
    cMWModelInternal* m = model ? static_cast<cMWModelInternal*>(model) : 0;
    cModelInstance* inst = m->mAnim[0];
    return inst ? inst->GetBoneParents(dst) : 0;
}

// @ 0x00744ad0
void cModelWorld_s0074_4ad0::SetBoneTable(Model_s0074_4ad0* model, int a, int b)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    int i = 0;
    cModelInstance_s0074_4ad0** p = m->mAnim;
    do {
        cModelInstance_s0074_4ad0* inst = *p;
        if (!inst)
            return;
        inst->SetBoneTable(a, b);
        ++i;
        ++p;
    } while (i < 4);
}

// @ 0x00744b10
void cModelWorld_s0074_4ad0::SetBoneCallback(Model_s0074_4ad0* model, int a, int b, int c, int d)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    int i = 0;
    cModelInstance_s0074_4ad0** p = m->mAnim;
    do {
        cModelInstance_s0074_4ad0* inst = *p;
        if (!inst)
            return;
        inst->SetBoneCallback(c, d, a, b);
        ++i;
        ++p;
    } while (i < 4);
}

// @ 0x00744b60
void cModelWorld_s0074_4ad0::SetAnimationGroupTransform(Model_s0074_4ad0* model, int a, int b)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    int i = 0;
    cModelInstance_s0074_4ad0** p = m->mAnim;
    do {
        cModelInstance_s0074_4ad0* inst = *p;
        if (!inst)
            return;
        inst->SetAnimationGroupTransform(a, b);
        ++i;
        ++p;
    } while (i < 4);
}

// @ 0x00744ba0
int cModelWorld_s0074_4ad0::GetMaterialInfo(Model_s0074_4ad0* model, int region)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    if (region < 0)
        return *(int*)((char*)m + 0xd8);
    cModelInstance_s0074_4ad0* inst = *(cModelInstance_s0074_4ad0**)((char*)m + 0x9c);
    return inst->GetRegionMaterialInfo(region);
}

// @ 0x00744be0
void cModelWorld_s0074_4ad0::SetDynamicDraw(Model_s0074_4ad0* model, int a, int b)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    cModelInstance_s0074_4ad0** p = (cModelInstance_s0074_4ad0**)((char*)m + 0x9c);
    int n = 4;
    do {
        if (*p)
            (*p)->SetDynamicDraw(a, b);
        ++p;
    } while (--n);
}

// @ 0x00744c30
int cModelWorld_s0074_4ad0::GetNumLODs(Model_s0074_4ad0* model)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    int count = 0, i = 0;
    int* p = (int*)((char*)m + 0x9c);
    do {
        if (*p == 0)
            return count;
        ++i;
        ++count;
        ++p;
    } while (i < 4);
    return count;
}

// @ 0x00744c70
void cModelWorld_s0074_4ad0::SetLOD(Model_s0074_4ad0* model, int lod)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    if (lod < 0) {
        m->mFlags138 &= 0xefffffff;
        if (m->mFieldD4 == 0) {
            uint32_t tmp = 0;
            PropertyGetFloatArray(*(void**)((char*)m + 0x98), (const char*)0x2e33a81,
                                  &tmp, &m->mFieldD4);
            m->mField129 = (uint8_t)tmp;
            return;
        }
    } else {
        m->mFlags138 |= 0x10000000;
        m->mField128 = (uint8_t)lod;
        m->mFieldD4 = 0;
        m->mField129 = 0;
    }
}

// @ 0x00744cf0
void cModelWorld_s0074_4ad0::SetSomeFloat(Model_s0074_4ad0* model, float v)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    if (v < 0.0f) {
        m->mFlags138 &= 0xdfffffff;
        m->mField124 = 0.0f;
        PropHolder* h = *(PropHolder**)((char*)m + 0x98);
        if (h) {
            void* tmp;
            if (h->Find(0x2a907b8, &tmp) && ((Prop*)tmp)->mType == 0xd) {
                float f = *((Prop*)tmp)->GetFloat();
                m->mField124 = f;
            }
        }
    } else {
        m->mFlags138 |= 0x20000000;
        m->mField124 = v;
    }
}

// @ 0x00744d80
void cModelWorld_s0074_4ad0::SetEffectEnabled(Model_s0074_4ad0* model, char a, char b, int id)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    EffectEntry* e = *(EffectEntry**)((char*)m + 0xdc);
    if (!e || !e->mpInner)
        return;
    do {
        if (id == 0 || (id == (int)e->mID && e->mPad4 == 0)) {
            if ((*(uint32_t*)((char*)m + 0xc) >> 0x13) & 1) {
                int arg = (b == 0);
                if (a)
                    e->mpInner->v08(arg);
                else
                    e->mpInner->v0C(arg);
            }
            e->mEnabled = a;
        }
        e = (EffectEntry*)((char*)e + 0x48);
    } while (e->mpInner);
}

// @ 0x00744e10
char cModelWorld_s0074_4ad0::ForEachEffectA(Model_s0074_4ad0* model, int a, int b, int c, int id)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    EffectEntry* e = *(EffectEntry**)((char*)m + 0xdc);
    if (e) {
        EffectInner* inner = e->mpInner;
        char result = 0;
        while (inner) {
            if (id == 0 || (uint64_t)(uint32_t)id == e->mKey) {
                if (inner->v44(a, b, c) != 0 || result != 0)
                    result = 1;
            }
            inner = *(EffectInner**)((char*)e + 0x50);
            e = (EffectEntry*)((char*)e + 0x48);
        }
        return result;
    }
    return 0;
}

// @ 0x00744e90
char cModelWorld_s0074_4ad0::ForEachEffectB(Model_s0074_4ad0* model, int a, int b, int c, int id)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    EffectEntry* e = *(EffectEntry**)((char*)m + 0xdc);
    if (e) {
        EffectInner* inner = e->mpInner;
        char result = 0;
        while (inner) {
            if (id == 0 || (uint64_t)(uint32_t)id == e->mKey) {
                if (inner->v48(a, b, c) != 0 || result != 0)
                    result = 1;
            }
            inner = *(EffectInner**)((char*)e + 0x50);
            e = (EffectEntry*)((char*)e + 0x48);
        }
        return result;
    }
    return 0;
}

// @ 0x00744f10
char cModelWorld_s0074_4ad0::ForEachEffectC(Model_s0074_4ad0* model, int a, int b, int id)
{
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    EffectEntry* e = *(EffectEntry**)((char*)m + 0xdc);
    if (e) {
        EffectInner* inner = e->mpInner;
        char result = 0;
        while (inner) {
            if (id == 0 || (uint64_t)(uint32_t)id == e->mKey) {
                if (inner->v4C(a, b) != 0 || result != 0)
                    result = 1;
            }
            inner = *(EffectInner**)((char*)e + 0x50);
            e = (EffectEntry*)((char*)e + 0x48);
        }
        return result;
    }
    return 0;
}

// @ 0x00744f80
int cModelWorld_s0074_4ad0::GetDeformationHandles(Model_s0074_4ad0* model, void* a, void* b)
{
    this->StallUntilLoaded(model);
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    cModelInstance_s0074_4ad0* inst = *(cModelInstance_s0074_4ad0**)((char*)m + 0x9c);
    if (inst)
        return inst->GetDeformationHandles(a, b);
    return 0;
}

// @ 0x00744fc0
bool cModelWorld_s0074_4ad0::GetRuntimeMeshes(Model_s0074_4ad0* model, int a, int b, int c, int d)
{
    this->StallUntilLoaded(model);
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    cModelInstance_s0074_4ad0* inst = *(cModelInstance_s0074_4ad0**)((char*)m + 0x9c);
    if (inst)
        return RuntimeModelBuilder_GetRuntimeMeshes(inst, a, b, c, d);
    return false;
}

// @ 0x00745010
bool cModelWorld_s0074_4ad0::CheckFlag(Model_s0074_4ad0* model, int a)
{
    this->StallUntilLoaded(model);
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    cModelInstance_s0074_4ad0* p = *(cModelInstance_s0074_4ad0**)((char*)m + 0xac);
    if (p) {
        if (Check434b0((void*)a))
            return true;
    }
    return false;
}

// @ 0x00745050
bool cModelWorld_s0074_4ad0::SelectMesh(Model_s0074_4ad0* model, int a, int b, char c)
{
    this->StallUntilLoaded(model);
    cMWModelInternal_s0074_4ad0* m = model ? static_cast<cMWModelInternal_s0074_4ad0*>(model) : 0;
    cModelInstance_s0074_4ad0* inst = c ? *(cModelInstance_s0074_4ad0**)((char*)m + 0xac)
                             : *(cModelInstance_s0074_4ad0**)((char*)m + 0x9c);
    if (inst)
        return inst->SelectMesh(a, b);
    return false;
}

// @ 0x007450a0
uint32_t cModelWorld_s0074_4ad0::GetSlot(int i)
{
    return *(uint32_t*)((char*)this + 0x1cc + i * 0x20);
}

// @ 0x00745110
SP::cArenaResource * SP::cModelWorld::HACK_GetArenaResource(SP::cMWModel * model)
{
    SP::cMWModelInternal* m = model ? static_cast<SP::cMWModelInternal*>(model) : 0;
    SP::cModelInstance* inst = *(SP::cModelInstance**)((char*)m + 0x9c);
    if (inst)
        return inst->GetArenaResource();
    return 0;
}

// @ 0x00745140
void cModelWorld_s0074_4ad0::FillColor(int* out)
{
    float x, y, z, w;
    switch (*out) {
    case 0:
        out[1] = 0x3f800000; out[2] = 0x3f800000;
        out[3] = 0x3f800000; out[4] = 0x3f800000; return;
    case 1:
    case 0xc:
        x = 1.0f; y = 0.0f; z = 0.0f; w = 1.0f; break;
    case 2:
    case 3:
        out[1] = *(int*)((char*)this + 0x850);
        out[2] = *(int*)((char*)this + 0x854);
        out[3] = *(int*)((char*)this + 0x858);
        out[4] = *(int*)((char*)this + 0x85c); return;
    case 4:
        x = 0.0f; y = 0.5f; z = 1.0f; w = 1.0f; break;
    case 5:
    case 8:
        x = 0.8f; y = 0.8f; z = 1.1f; w = 1.0f; break;
    case 9:
        x = 0.9f; y = 0.9f; z = 1.0f; w = 1.0f; break;
    case 0xb:
        x = 1.0f; y = 0.5f; z = 0.0f; w = 0.75f; break;
    default:
        x = 1.0f; y = 1.0f; z = 1.0f; w = 1.0f; break;
    }
    out[1] = *(int*)&x;
    out[2] = *(int*)&y;
    out[3] = *(int*)&z;
    out[4] = *(int*)&w;
}

// @ 0x00745340
void cModelWorld_s0074_4ad0::ReleaseRefs()
{
    RCObj_s0074_4ad0* a = *(RCObj_s0074_4ad0**)((char*)this + 0x90);
    if (a)
        a->Release();
    RCObj_s0074_4ad0* b = *(RCObj_s0074_4ad0**)((char*)this + 0x64);
    if (b)
        b->Release();
}

// @ 0x007453a0
void* Small7::Init()
{
    d[0] = 0xffffffff;
    d[1] = 0; d[2] = 0; d[3] = 0; d[4] = 0; d[5] = 0; d[6] = 0;
    b = 1;
    return this;
}

// @ 0x007453d0
bool __cdecl FactoryNew(void** out, void* arg2, unsigned flags)
{
    cModelInstance_s0074_4ad0* inst = (cModelInstance_s0074_4ad0*)EA_New(0xa0, "Graphics/ModelManager/Animations", 0, 0, 0, 0);
    if (inst)
        inst = inst->Init();
    if (inst)
        *(int*)((char*)inst + 4) += 1;
    inst->SetFlags(flags & 1, (flags >> 1) & 1);
    void* r1 = 0;
    void* h = GetThing(arg2);
    if (h) r1 = (void*)((int (__thiscall*)(void*, int))((*(void***)h)[3]))(h, 0x2f4e681b);
    void* r2 = 0;
    void* h2 = GetThing(arg2);
    if (h2) r2 = (void*)((int (__thiscall*)(void*, int))((*(void***)h2)[3]))(h2, 0xe6bce5);
    if (r1)
        inst->Method742cf0(r1);
    else if (r2)
        inst->ConstructFromGameModelResource(r2);
    *out = inst;
    return true;
}

// @ 0x007454f0
AutoRef* AutoRef::Release()
{
    RefObj* p = mp;
    if (p) {
        mp = 0;
        int n = (*(volatile int*)&p->mRef += -1);
        if (n == 0) {
            *(volatile int*)&p->mRef = 1;
            p->v0(1);
        }
    }
    return this;
}

// @ 0x00745520
int SlotVec::next(int idx)
{
    uint32_t* p = (uint32_t*)(mp + idx * 5);
    uint32_t v = *p;
    do {
        if ((v >> 0x1e) & 1)
            return 0x3fffffff;
        v = p[5];
        p += 5;
        ++idx;
    } while ((int)v < 0);
    return idx;
}

// @ 0x00745560
void ChunkFind(uint32_t* out, int* cur, int* start, int* end, int** seg, int key)
{
    while (cur != end && *cur != key) {
        cur += 7;
        if (cur == end) {
            seg += 1;
            cur = *seg;
            end = cur + 0x38;
            start = cur;
        }
    }
    out[2] = (uint32_t)end;
    out[3] = (uint32_t)seg;
    out[0] = (uint32_t)cur;
    out[1] = (uint32_t)start;
}

// @ 0x007455e0
void __fastcall DestroyChunk(int param_1)
{
    ChunkObj* p = *(ChunkObj**)(*(int*)(param_1 + 8) + 4);
    if (p)
        p->Release();
    if (*(int*)(param_1 + 0xc))
        EA_Free(*(void**)(param_1 + 0xc));
    int* q = (int*)(*(int*)(param_1 + 0x14) + 4);
    *(int**)(param_1 + 0x14) = q;
    int v = *q;
    *(int*)(param_1 + 0xc) = v;
    *(int*)(param_1 + 0x10) = v + 0xe0;
    *(int*)(param_1 + 8) = *(int*)(param_1 + 0xc);
}

// @ 0x00745630
void __fastcall DequeDoPopFront(int* self)
{
    if (*self) {
        ((RangeDtor*)self)->Destroy((void**)self[5], (void**)(self[9] + 4));
        if (*self)
            EA_Free((void*)*self);
    }
}

// @ 0x00745660
int SlotCount(uint32_t* first, uint32_t* last)
{
    int n = 0;
    do {
        uint32_t* p = first;
        if (last == first)
            return n;
        do {
            first = p + 5;
            bool b = (*p >> 0x1e) & 1;
            if (b)
                break;
            p = first;
            bool b2 = (*first >> 0x1f) & 1;
            if (!b2)
                break;
        } while (true);
        ++n;
    } while (true);
}

// @ 0x007456a0
void SlotCell::Assign(int* src)
{
    int* dst = (int*)this;
    if (((-1 < *src) || (*dst < 0)) && (-1 < *src)) {
        if (*dst < 0) {
            if (dst + 1 != 0) {
                dst[1] = src[1];
                dst[2] = src[2];
                dst[3] = src[3];
                dst[4] = src[4];
                *dst = *src;
                return;
            }
        } else {
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[4] = src[4];
        }
    }
    *dst = *src;
}

// @ 0x00745710
int* DequeIter::Advance(int n)
{
    int* self = (int*)this;
    int d = (self[0] - self[1]) / 0x1c + n;
    if (d < 8) {
        self[0] = self[0] + n * 0x1c;
        return self;
    }
    int i = ((d + 0x1000000 + ((d + 0x1000000) >> 31 & 7)) >> 3) - 0x200000;
    int* p = (int*)(self[3] + i * 4);
    self[3] = (int)p;
    int v = *p;
    self[1] = v;
    self[2] = v + 0xe0;
    self[0] = self[1] + (d - i * 8) * 0x1c;
    return self;
}

// @ 0x007457a0
void DequeInsert(int* self, unsigned count, int flag)
{
    int* begin = (int*)self[5];
    int n = (self[9] - (int)begin) >> 2;
    int i6 = n + 1;
    unsigned total = i6 + count;
    unsigned cap = self[1];
    if (total * 2 < cap) {
        int* dst = (int*)(self[0] + ((cap - total >> 1) + (flag ? count : 0)) * 4);
        if (dst < begin)
            VecDoInsertValue();
        else
            MemMove(dst + (i6 - (((int)(n * 4 + 4)) >> 2)), begin, n * 4 + 4);
    } else {
        int newcap = i6 + 2 + cap;
        int* p = (int*)EA_New(newcap * 4, "Graphics", 0, 0,
                              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        int* dst = (int*)((char*)p + (((int)begin - self[0]) / 4 + (flag ? count : 0)) * 4);
        if (self[0])
            VecDoInsertValue();
        if (self[0])
            EA_Free((void*)self[0]);
        self[0] = (int)p;
        self[1] = newcap;
        self[5] = (int)dst;
        int v = *dst;
        self[3] = v;
        self[4] = v + 0xe0;
        self[9] = (int)(dst + n);
        v = dst[n];
        self[7] = v;
        self[8] = v + 0xe0;
    }
}

// @ 0x007458d0
void DequeInit(int* self, unsigned count)
{
    int i6 = (count >> 3) + 1;
    unsigned a = (count >> 3) + 3;
    unsigned b = 8;
    unsigned cap = (a < 9) ? a : b;
    self[1] = cap;
    int* p = (int*)EA_New(cap * 4, "Graphics", 0, 0, (const char*)0x13ebb38, 0xd1);
    int* first = (int*)((char*)p + ((cap - i6) >> 1) * 4);
    int* last = first + i6;
    self[0] = (int)p;
    for (int* q = first; q < last; ++q)
        *q = (int)EA_New(0xe0, "Graphics", 0, 0, (const char*)0x13ebb38, 0xd1);
    self[5] = (int)first;
    int v = *first;
    self[3] = v;
    self[4] = v + 0xe0;
    self[2] = self[3];
    self[9] = (int)(last - 1);
    v = last[-1];
    self[7] = v;
    self[8] = v + 0xe0;
    self[6] = self[7] + (count & 7) * 0x1c;
}

// @ 0x007459c0
void Sort18(uint32_t* first, uint32_t* last, bool (*compare)(const void*, const void*))
{
    if (first == last)
        return;
    uint32_t* cur = first;
    while ((cur += 6) != last) {
        uint32_t tmp[6];
        tmp[0] = cur[0]; tmp[1] = cur[1]; tmp[2] = cur[2];
        tmp[3] = cur[3]; tmp[4] = cur[4]; tmp[5] = cur[5];
        uint32_t* p = cur;
        while (p != first) {
            uint32_t* prev = p - 6;
            if (!compare(tmp, prev))
                break;
            p[0] = prev[0]; p[1] = prev[1]; p[2] = prev[2];
            p[3] = prev[3]; p[4] = prev[4]; p[5] = prev[5];
            p = prev;
        }
        p[0] = tmp[0]; p[1] = tmp[1]; p[2] = tmp[2];
        p[3] = tmp[3]; p[4] = tmp[4]; p[5] = tmp[5];
    }
}

// @ 0x00745ac0
void Sort24(P6* first, P6* last, Compare24 compare)
{
    for (P6* i = first; i != last; ++i) {
        P6 temp(*i);
        P6* j = i;
        while (compare(temp, *(j - 1))) {
            *j = *(j - 1);
            --j;
        }
        *j = temp;
    }
}

// @ 0x00745bb0
E20* Copy20(E20* first, E20* last, E20* dest)
{
    for (; first != last; first += 1, dest += 1) {
        if (dest) {
            dest->flags = first->flags;
            if (!(first->flags >> 31)) {
                dest->x = first->x;
                dest->y = first->y;
                dest->z = first->z;
                dest->w = first->w;
            }
        }
    }
    return dest;
}

// @ 0x00745c20
Node18* CreateNode18(const uint32_t* value)
{
    Node18* p = (Node18*)EASTL_allocator_allocate(0x18, "Graphics", 0, 0,
                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (p) {
        p->mKey = *value;
        p->mRef = (void*)value[1];
        if (p->mRef)
            (*(void(__thiscall**)(void*))p->mRef)(p->mRef);
    }
    return p;
}

// @ 0x00745ca0
Vec6* UninitCopy24(Vec6* first, Vec6* last, Vec6* dest)
{
    for (; first != last; first += 1, dest += 1) {
        if (dest) new (dest) Vec6(*first);
    }
    return dest;
}

// @ 0x00745cf0
void PromoteOccluder(cOccluder_s0074_5ac0* first, int topPosition, int position, cOccluder_s0074_5ac0 value, cOccluderCompare compare)
{
    int parentPosition = (position - 1) >> 1;
    for (; position > topPosition && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

// @ 0x00745e00
void PromotePairGt(FloatKeyPair* first, int topPosition, int position, FloatKeyPair value, FloatKeyGreater compare)
{
    int parentPosition = (position - 1) >> 1;
    for (; position > topPosition && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

// @ 0x00745e80
void PromotePairLt(FloatKeyPair* first, int topPosition, int position, FloatKeyPair value, FloatKeyLess compare)
{
    int parentPosition = (position - 1) >> 1;
    for (; position > topPosition && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

// @ 0x00745f90
DrawRecord* DrawRecord_Ctor(DrawRecord* self, void* owner)
{
    self->mOwner = owner;
    self->mFlags = 0;
    self->mA = 0;
    self->mB = 0;
    self->mPos.x = g_f162eb0c;
    self->mPos.y = g_f162eb10;
    self->mPos.z = g_f162eb14;
    self->mScale = g_f1485720;
    Matrix3_Assign(self->mRotation, &g_f162ec38);
    self->mR0 = 0;
    self->mR1 = 0;
    self->mR2 = 0;
    self->mDir.x = g_f1537ab0;
    self->mDir.y = g_f1537ab4;
    self->mDir.z = g_f1537ab8;
    self->mDirScale = g_f1485720;
    self->mB0 = false;
    self->mB1 = false;
    self->mP0 = 0;
    self->mP1 = 0;
    self->mF0 = g_f1485720;
    self->mF1 = g_f13eb1bc;
    self->mF2 = g_f13eb1bc;
    self->mF3 = g_f13eb1bc;
    self->mF4 = g_f1485720;
    self->mF5 = g_f1485720;
    self->mF6 = g_f1485720;
    self->mF7 = g_f140d674;
    self->mF8 = g_f140d674;
    self->mLast = 0;
    return self;
}

// @ 0x007460b0
int FilterModelFrustum(CullModel* model, void* culler, FrustumFilterArg* arg)
{
    cSPTransform_s0074_5ac0 local;
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mModificationCount = 0;
    local.mFlags = 0;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);

    if (!(model->mFlags & 1))
        return 1;
    if (!((arg->mA == 0 && arg->mB == 0) ||
          (model->mMaskA & arg->mA) != 0 || (model->mMaskB & arg->mB) != 0))
        return 1;
    if ((model->mMaskA & arg->mC) != 0 || (model->mMaskB & arg->mD) != 0)
        return 1;
    if (arg->mCallback != 0 && !arg->mCallback((char*)model + 8))
        return 1;

    unsigned char b;
    if ((arg->mF & 1) && ((model->mFlags >> 8) & 1))
        b = model->mC0;
    else
        b = arg->mE;

    cSPTransform_Assign(&local, &model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->mF & 2)) {
        local.mModificationCount = local.mModificationCount + 1;
        local.mScale = g_f1485720;
    }

    float pos[3];
    pos[0] = local.mTranslation.x;
    pos[1] = local.mTranslation.y;
    pos[2] = local.mTranslation.z;
    int r = FUN_006ffbd0(pos, model->mRadius * local.mScale);
    if (r & 0x40)
        return 1;

    if (b != 0 && model->mBox.mMin.x <= model->mBox.mMax.x) {
        cSPBoundingBox_s0074_5ac0 box;
        FUN_00511140(&model->mBox);
        BoundingBox_TransformBy(&box, &local);
        if (cFrustumCull_FrustumTestSphere(culler, &box, 0x200) & 0x40)
            return 1;
    }
    return 0;
}

// @ 0x00746250
void cModelWorld_SetMaterialInfo(void* /*this*/, void* handle, void* info, int idx)
{
    MWInternal* p = handle ? (MWInternal*)((char*)handle - 8) : 0;
    if (idx < 0) {
        p->mD8->G(info);
        return;
    }
    for (int i = 0; i < 4; ++i) {
        if (p->mSlots[i] == 0)
            return;
        p->mSlots[i]->F(idx, handle);
    }
}

// @ 0x007462b0
void FUN_007462b0(void* /*this*/, void* handle, VecField* v)
{
    MWInternal_s0074_5ac0* p = handle ? (MWInternal_s0074_5ac0*)((char*)handle - 8) : 0;
    void* src = 0;
    if (p->mSlots[0] == 0 && p->mSlots[1] == 0 && p->mSlots[2] == 0 && p->mSlots[3] == 0) {
        // no slots: still run the commit below
    } else {
        // find a live slot and detach its refcounted object at +0x18
        void* q = (void*)v->mExtra;
        if (q) {
            v->mExtra = 0;
            (*(void(__thiscall**)(void*))(*(void**)q))(q);
        }
        FUN_0073b980(&v->mStore, &v->mBegin, &v->mExtra, &v->mEnd, &v->mOther, &v->mCapacity, &v->mExtra);
    }
    if (v->mEnd != v->mExtra) {
        v->mEnd = v->mExtra;
        EASTL_allocator_deallocate(v->mStore);
        uint32_t n = (uint32_t)v->mEnd;
        v->mStore = EASTL_allocator_allocate(n * 0xc, "Graphics", 0, 0, 0, 0);
    }
}

// @ 0x00746360
void cModelWorld_GetHull(void* self, HullQuery* out)
{
    (*(void(__thiscall**)(void*, HullQuery*))((char*)(*(void**)self) + 0x58))(self, out);
    unsigned char* p = (unsigned char*)out - 8;
    out->mKey = 0;
    out->mType = 0;
    out->m0 = 0;
    out->m1 = 0;
    out->m2 = 0;
    out->m3 = 0;
    if (out->mInst) {
        void* q = out->mInst;
        out->mInst = 0;
        (*(void(__thiscall**)(void*, int))((char*)(*(void**)q) + 4))(q, 1);
    }
    if (*(void**)(p + 0xac) == 0 && *(void**)(p + 0x98) != 0) {
        VariantKey variant;
        memset(&variant, 0, sizeof(variant));
        int ok = (*(int(__thiscall**)(void*, uint32_t, void*))
                  ((char*)(**(void***)(p + 0x98)) + 0x24))(*(void**)(p + 0x98), 0xf9efc0, &variant);
        if (ok) {
            // resolved resource key
            SP_CreateModelInstance(variant.a, variant.c == -1 ? 0 : variant.c, (void*)FUN_007454f0(0));
        }
    }
    if (*(void**)(p + 0xac) != 0 || *(void**)(p + 0x9c) != 0) {
        FUN_007434b0(0);
        if (out->mInst) {
            void* q = out->mInst;
            out->mInst = 0;
            (*(void(__thiscall**)(void*, int))((char*)(*(void**)q) + 4))(q, 1);
        }
        FUN_0073b980(&out->mKey, &out->mType, &out->m0, &out->m1, &out->m2, &out->m3, &out->mInst);
    }
}

// @ 0x00746560
void CModelWorldStub::GetHullBoundingBox(void* handle, cSPBoundingBox_s0074_5ac0* out)
{
    ModelInternal* p = handle ? (ModelInternal*)((char*)handle - 8) : 0;
    HullModel* h = p->mHull;
    if (h) {
        out->mMax = h->mMax;
        out->mMin = h->mMin;
        const cSPTransform_s0074_5ac0& xf = p->mTransform;
        if (xf.mScale != g_f1485720 || (*(unsigned char*)&xf & 6))
            out->Transform(xf);
    } else {
        out->mMax = p->mMax;
        out->mMin = p->mMin;
    }
}

// @ 0x00746610
int cModelWorld_GetRuntimeModel(void* self, void* handle, int* params)
{
    (*(void(__thiscall**)(void*, void*))((char*)(*(void**)self) + 0x58))(self, handle);
    ModelInternal* p = handle ? (ModelInternal*)((char*)handle - 8) : 0;
    unsigned char* q = (unsigned char*)p;
    if (*(void**)(q + 0x9c) != 0) {
        float rot[9];
        Matrix3_Assign(rot, &g_f162ec38);
        FUN_007760a0(*(int*)(q + 0x9c), (int)handle, params[0], params[1], params[2], rot);
        return 0;
    }
    return 3;
}

// @ 0x007466e0
int FUN_007466e0(void* self, void* handle)
{
    (*(void(__thiscall**)(void*, void*))((char*)(*(void**)self) + 0x58))(self, handle);
    ModelInternal* p = handle ? (ModelInternal*)((char*)handle - 8) : 0;
    if (*(void**)((char*)p + 0x9c) == 0)
        return 0;
    if (!FUN_007434b0((int)handle))
        return 0;
    if (!((*(uint32_t*)((char*)p + 0xc) >> 9) & 1)) {
        HullModel* h = (HullModel*)*(void**)((char*)p + 0xac);
        (void)h;
        Vec3 mn = *(Vec3*)((char*)p + 0xa8);
        (void)mn;
        // Copy bounding box out of the model instance (offsets as in retail).
        Vec3 srcMax = *(Vec3*)((char*)p + 0xc0);
        (void)srcMax;
        float scale = p->mTransform.mScale;
        if (scale != g_f1485720 || (*(unsigned char*)&p->mTransform & 6)) {
            // recompute bounding radius
            float a = *(float*)((char*)p + 0xe8);
            float b = *(float*)((char*)p + 0xec);
            float c = *(float*)((char*)p + 0xf0);
            float r = sqrtf(a * a + b * b + c * c);
            (void)r;
        }
    }
    return 1;
}

// @ 0x007467f0
int FUN_007467f0(void* self, void* a, void* b, Vec3* out1, Vec3* out2, Vec3* out3)
{
    char buf[36];
    char* p = buf;
    memset(buf, 0, sizeof(buf));
    void* local = 0;
    if (!(*(int(__thiscall**)(void*, int, void*, void*, void*))((char*)(*(void**)self) + 0x114))(self, 0, &local, a, b))
        return 0;
    {
        IVirtual* lv = (IVirtual*)local;
        if (lv) { lv->v1(0); }
    }
    if (!(*(int(__thiscall**)(void*, char*))((char*)(*(void**)local) + 8))(local, buf)) {
        if (local) (*(void(__thiscall**)(void*))((char*)(*(void**)local) + 4))(local);
        return 0;
    }
    out1->x = *(float*)(buf + 0);  out1->y = *(float*)(buf + 4);  out1->z = *(float*)(buf + 8);
    out2->x = *(float*)(buf + 12); out2->y = *(float*)(buf + 16); out2->z = *(float*)(buf + 20);
    out3->x = *(float*)(buf + 24); out3->y = *(float*)(buf + 28); out3->z = *(float*)(buf + 32);
    if (local) (*(void(__thiscall**)(void*))((char*)(*(void**)local) + 4))(local);
    return 1;
}

// @ 0x00746910
void GroupWorld::AssignGroup(void* newObj, int idx, bool flag)
{
    GroupWorld* w = this;
    void* self = this;
    if (idx == 0) {
        for (ListNode* n = w->mGroupList.pNext; n != (ListNode*)&w->mGroupList; n = n->pNext) {
            GroupInternal* g = (GroupInternal*)n;
            if (g->mObj != 0)
                (*(void(__thiscall**)(void*, void*))((char*)(**(void***)w->mSlotObj) + 0x20))(w->mSlotObj, g->mObj);
            g->mObj = 0;
        }
    }
    GroupSlot* s = (GroupSlot*)((char*)self + idx * 0x20);
    void* old = s->mSlotObj;
    if (newObj != s->mSlotObj) {
        if (newObj) (*(void(__thiscall**)(void*))(*(void**)newObj))(newObj);
        s->mSlotObj = newObj;
        if (old) (*(void(__thiscall**)(void*, int))((char*)old + 4));
    }
    s->mFlag = flag;
    if (s->mCount < 0)
        s->mCount = 0;
}

// @ 0x007469b0
void CModelWorld::SetWorldBounds(Vec3 bounds[2], float param_3, float param_4)
{
    float d0 = bounds[0].x - bounds[0].y;  // placeholder (real shape below)
    (void)d0;
    unsigned char* b = (unsigned char*)this;
    float sx = bounds[1].x - bounds[0].x;
    float sy = bounds[1].y - bounds[0].y;
    float sz = bounds[1].z - bounds[0].z;
    float dim = sx;
    if (sy > dim) dim = sy;
    if (sz > dim) dim = sz;
    if (*(void**)(b + 0x140) != *(void**)(b + 0x13c))
        cHierGrid_Shutdown(b + 0x118);
    for (unsigned char* n = *(unsigned char**)(b + 0x19c); n != b + 0x19c; n = *(unsigned char**)n)
        *(int*)(n + 0x120) = -1;
    if (bounds[0].x <= bounds[1].x) {
        float f0 = dim * 2.0f;
        float q0 = f0 / (param_3 + 1e-08f);
        float q1 = f0 / (param_4 + 1e-08f);
        int i0 = (int)(q0 + 0.5f);
        int i1 = (int)(q1 + 0.5f);
        int lvl = i0 < 0 ? 0 : i0;
        int lv2 = i1 < 7 ? i1 : 7;
        if (lv2 < lvl) lv2 = lvl;
        cHierGrid_Init(b + 0x118, bounds, dim, lvl, lv2);
    }
}

// @ 0x00746b40
void CModelWorld::UpdateOccluder(int idx, Vec3* pos, float radius)
{
    mOccluders[idx].mPosition = *pos;
    mOccluders[idx].mRadius = radius;
}

// @ 0x00746b90
void cModelWorld_ShutdownModel(CModelWorld* self, int model)
{
    unsigned char* b = (unsigned char*)self;
    if (*(int*)(model + 0x120) >= 0) {
        cHierGrid_Remove(b + 0x118, *(int*)(model + 0x120));
        *(int*)(model + 0x120) = -1;
    }
    if (*(int*)(model + 0x134) != 0) {
        VViewer* v = *(VViewer**)(b + 0x224);
        // vtable slot at +0x20
        (*(void(__thiscall**)(VViewer*, int))(((char*)(*(void**)v) + 0x20)))(v, *(int*)(model + 0x134));
        *(int*)(model + 0x134) = 0;
    }
    int p = *(int*)(model + 0xdc);
    if (p) {
        int q = p + 8;
        int* it = *(int**)(p + 8);
        while (it) {
            (*(void(__thiscall**)(int*, int))((char*)(*it) + 0xc))(it, 1);
            int* nx = (int*)(q + 0x48);
            q += 0x48;
            it = (int*)*nx;
        }
        int* raw = (int*)p;
        operator_delete_((char*)raw - 4);
        *(int*)(model + 0xdc) = 0;
    }
    if (*(int**)(model + 0xe0)) {
        int* arr = *(int**)(model + 0xe0);
        int n = *arr;
        for (int i = 0; i < n; ++i) {
            int v = *(int*)(arr + 5 + i);
            if (v != -1) {
                VViewer* vw = *(VViewer**)(b + 0x224);
                (*(void(__thiscall**)(VViewer*, int))(((char*)(*(void**)vw) + 0x14)))(vw, v);
                *(int*)(arr + 5 + i) = -1;
            }
        }
        operator_delete_(arr);
        *(int*)(model + 0xe0) = 0;
    }
    unsigned char* l = *(unsigned char**)(b + 0x4c);
    unsigned char* e = *(unsigned char**)(b + 0x50);
    for (; l != e; l += 4)
        (*(void(__thiscall**)(void*, void*))((char*)(**(void***)l) + 4))(*(void**)l, (void*)(model + 8));
}

// @ 0x00746cc0
int FUN_00746cc0(int self, int key)
{
    int it;
    // find(key) yields node or anchor; return value at +0x14 when found.
    (void)key;
    it = 0;
    if (it != self + 0x10)
        return *(int*)(it + 0x14);
    return 0;
}

// @ 0x00746cf0
int FUN_00746cf0(int self, int a, float b)
{
    int hit = 0;
    float best = 0.0f;
    int vec24[3], vec30[3];
    memset(vec24, 0, 12);
    memset(vec30, 0, 12);
    FUN_007c4510(a, b, vec30, vec24);
    int n = *(int*)(self + 0x14);
    if (n != self + 0x10) {
        do {
            void* obj = *(void**)(n + 0x14);
            if (*((char*)obj + 0x24) != 0) {
                int r = (*(int(__thiscall**)(void*, void*, void*, float*, void*))
                         (((char*)(*(void**)obj) + 0x28)))(obj, vec30, vec24, &b, 0);
                if (r && best < b) { best = b; hit = r; }
            }
            n = 0;
        } while (0);
        if (hit) {
            if (!(*(uint32_t*)(hit + 4) & 0x40)) *(uint32_t*)(hit + 4) |= 0x40;
            else *(uint32_t*)(hit + 4) &= ~0x40;
        }
    }
    return hit != 0;
}

// @ 0x00746de0
Rec48::Rec48()
{
    a = -1;
    b = -1;
    c = 0;
    d = 0;
    e = 0;
    pos.x = g_f162eb0c;
    pos.y = g_f162eb10;
    pos.z = g_f162eb14;
    scale = g_f1485720;
    rot.Assign(&g_f162ec38);
    f = 1;
}

// @ 0x00746e50
void FUN_00746e50(void* self, void* owner)
{
    unsigned char* b = (unsigned char*)self;
    memset(b, 0, 8);
    DrawRecord_CtorProto(owner);
    // vector constructors at +0x9c and +0xb4 (6 RCObj refs each)
    for (int i = 0; i < 6; ++i) { *(int*)(b + 0x9c + i * 4) = 0; *(int*)(b + 0xb4 + i * 4) = 0; }
    *(void**)(b + 0xd4) = 0;
    *(void**)(b + 0xd8) = 0;
    *(void**)(b + 0xdc) = 0;
    *(void**)(b + 0xe0) = 0;
    *(short*)(b + 0xe6) = 0;
    *(short*)(b + 0xe4) = 0;
    *(float*)(b + 0xe8) = g_f162eb0c;
    *(float*)(b + 0xec) = g_f162eb10;
    *(float*)(b + 0xf0) = g_f162eb14;
    *(float*)(b + 0xf4) = g_f1485720;
    Matrix3_Assign(b + 0xf8, &g_f162ec38);
    *(float*)(b + 0x11c) = g_f1485720;
    *(int*)(b + 0x120) = -1;
    *(unsigned char*)(b + 0x128) = 0;
    *(unsigned char*)(b + 0x129) = 0;
    *(short*)(b + 0x12a) = 0;
    *(int*)(b + 0x124) = 0;
    *(int*)(b + 0x12c) = 0;
    *(int*)(b + 0x130) = 0;
    *(int*)(b + 0x134) = 0;
    *(int*)(b + 0x138) = 0;
    *(int*)(b + 0x138) |= 0x80000;
    *(int*)(b + 0xcc) = -1;
    *(short*)(b + 0xd0) = (short)0xffff;
}

// @ 0x00746fc0
void FUN_00746fc0(void* self)
{
    unsigned char* b = (unsigned char*)self;
    void* p = *(void**)(b + 0xdc);
    if (p) {
        operator_delete_((char*)p - 4);
        *(void**)(b + 0xdc) = 0;
    }
    if (*(int*)(b + 0xe0)) {
        operator_delete_(*(void**)(b + 0xe0));
        *(void**)(b + 0xe0) = 0;
    }
    RCObj* r = (RCObj*)*(void**)(b + 0xd8);
    if (r) {
        if (--r->mRefCount == 0) { r->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)r))(r, 1); }
    }
    for (int i = 0; i < 6; ++i) {
        RCObj* q = (RCObj*)*(void**)(b + 0xb4 + i * 4);
        if (q && --q->mRefCount == 0) { q->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)q))(q, 1); }
        RCObj* s = (RCObj*)*(void**)(b + 0x9c + i * 4);
        if (s && --s->mRefCount == 0) { s->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)s))(s, 1); }
    }
    FUN_00745340();
}

// @ 0x007470c0
void Stub007470c0::F()
{
    unsigned char* b = (unsigned char*)this;
    *(int*)(b + 0x138) = 0x8000000;
    RCObj* p = (RCObj*)*(void**)(b + 0x98);
    if (p) { *(void**)(b + 0x98) = 0; (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)p) + 4)))(p, 1); }
    RCObj* q = (RCObj*)*(void**)(b + 0x6c);
    if (q) { *(void**)(b + 0x6c) = 0; (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)q) + 4)))(q, 1); }
    for (int i = 0; i < 6; ++i) {
        RCObj* a = (RCObj*)*(void**)(b + 0x9c + i * 4);
        if (a) { *(void**)(b + 0x9c + i * 4) = 0; if (--a->mRefCount == 0) { a->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)a))(a, 1); } }
        RCObj* c = (RCObj*)*(void**)(b + 0xb4 + i * 4);
        if (c) { *(void**)(b + 0xb4 + i * 4) = 0; if (--c->mRefCount == 0) { c->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)c))(c, 1); } }
    }
    RCObj* r = (RCObj*)*(void**)(b + 0xd8);
    if (r) {
        *(void**)(b + 0xd8) = 0;
        if (--r->mRefCount == 0) { r->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)r))(r, 1); }
    }
}

// @ 0x00747190
void* Stub00747190::F(int* src)
{
    int* dst = (int*)this;
    *dst = *src;
    int* old = (int*)dst[1];
    int* nw = (int*)src[1];
    if (nw != old) {
        if (nw) (*(void(__thiscall**)(int*))(*(void**)nw))(nw);
        dst[1] = (int)nw;
        if (old) (*(void(__thiscall**)(int*, int))(((char*)(*(void**)old) + 4)))(old, 1);
    }
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    return dst;
}

// @ 0x007471f0
void FUN_007471f0(void* self)
{
    unsigned char* b = (unsigned char*)self;
    memset(b, 0, 0x18);
    // mModelInstance array at +0x9c constructed empty (6 refs)
    for (int i = 0; i < 6; ++i)
        *(int*)(b + 0x9c + i * 4) = 0;
    *(int*)(b + 0x38) = 0;
    *(int*)(b + 0x3c) = 0;
    *(int*)(b + 0x40) = 6;
    *(int*)(b + 0x30) = 0;
}

// @ 0x00747270
void Stub00747270::F()
{
    unsigned char* b = (unsigned char*)this;
    for (int i = 0; i < 6; ++i) {
        RCObj* r = (RCObj*)*(void**)(b + 0x9c + i * 4);
        if (r && --r->mRefCount == 0) { r->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)r))(r, 1); }
    }
    RCObj* p = (RCObj*)*(void**)(b + 0x18);
    if (p && --p->mRefCount == 0) { p->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)p))(p, 1); }
    RCObj* q = (RCObj*)*(void**)(b + 0x10);
    if (q && --q->mRefCount == 0) { q->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)q))(q, 1); }
}

// @ 0x00747340
void FUN_00747340(int param_1)
{
    unsigned char* b = (unsigned char*)param_1;
    int count = 0, data = 0;
    if (SP_GetPropertyAsIntArray(*(void**)(b + 0x98), 0x60cbbef, &count, &data)) {
        int local[6] = {0, 0, 0, 0, 0, 0};
        int i = 0;
        while (true) {
            if (*(int*)(b + 0x9c + i * 4) != 0 && i < count) {
                uint32_t idx = *(uint32_t*)(data + i * 4);
                if (idx < 6) {
                    int src = *(int*)(b + 0x9c + idx * 4);
                    if (src == 0) break;
                    if (local[idx] == 0) {
                        int v = FUN_007454f0(src, *(int*)(b + 0x138));
                        FUN_007453d0((void*)v);
                    }
                }
            }
            ++i;
            if (i > 5) {
                char map[8];
                int k = 0;
                for (int j = 0; j < 6; ++j) {
                    if (local[j] == 0) map[j] = -1;
                    else { map[j] = (char)k; ++k; }
                }
                for (int j = 0; j < 6; ++j) {
                    if (*(int*)(b + 0x9c + j * 4) != 0)
                        *(char*)(b + 0xcc + j) = map[j];
                }
                return;
            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        if (*(int*)(b + 0x9c + i * 4) != 0) {
            *(char*)(b + 0xcc + i) = 0;
            int v[6] = {0, 0, 0, 0, 0, 0};
            FUN_007453d0((void*)v);
        }
    }
}

// @ 0x00747640
int FUN_00747640(int self, int* key)
{
    int local[4];
    int b = (int)self;
    FUN_00745560(local, *(int*)(b + 0x28c), *(int*)(b + 0x290), *(int*)(b + 0x294),
                 *(int*)(b + 0x298), *(int*)(b + 0x29c), *(int*)(b + 0x2a0),
                 *(int*)(b + 0x2a4), *(int*)(b + 0x2a8), *key);
    return local[0] != *(int*)(b + 0x29c);
}

// @ 0x00747720
void FUN_00747720(int* d)
{
    int beg = d[2], end = d[4], map = d[5];
    if (beg != d[6]) {
        do {
            RCObj* r = (RCObj*)*(void**)(beg + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            beg += 0x1c;
            if (beg == end) { beg = *(int*)(map + 4); map += 4; end = beg + 0xe0; }
        } while (beg != d[6]);
    }
    if (*d != 0) {
        int last = d[9];
        for (int* p = (int*)d[5]; p < (int*)(last + 4); ++p)
            if (*p) operator_delete_((void*)*p);
        operator_delete_((void*)*d);
    }
}

// @ 0x007477d0
void FUN_007477d0(int self)
{
    unsigned char* b = (unsigned char*)self;
    uint32_t start = *(uint32_t*)(b + 8);
    if (*(int*)(b + 0x14) == *(int*)(b + 0x24)) {
        while (start < *(uint32_t*)(b + 0x18)) {
            RCObj* r = (RCObj*)*(void**)(start + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            start += 0x1c;
        }
    } else {
        while (start < *(uint32_t*)(b + 0x10)) {
            RCObj* r = (RCObj*)*(void**)(start + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            start += 0x1c;
        }
        start = *(uint32_t*)(b + 0x1c);
        while (start < *(uint32_t*)(b + 0x18)) {
            RCObj* r = (RCObj*)*(void**)(start + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            start += 0x1c;
        }
        if (*(int*)(b + 0x1c)) operator_delete_(*(void**)(b + 0x1c));
    }
    uint32_t* p = (uint32_t*)(*(int*)(b + 0x14) + 4);
    while (p < *(uint32_t**)(b + 0x24)) {
        uint32_t base = *p;
        for (uint32_t q = base; q < base + 0xe0; q += 0x1c) {
            RCObj* r = (RCObj*)*(void**)(q + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
        }
        if (*p) operator_delete_((void*)*p);
        ++p;
    }
    *(int*)(b + 0x18) = *(int*)(b + 8);
    *(int*)(b + 0x1c) = *(int*)(b + 0xc);
    *(int*)(b + 0x20) = *(int*)(b + 0x10);
    *(int*)(b + 0x24) = *(int*)(b + 0x14);
}

// @ 0x007478b0
void FUN_007478b0(uint32_t* v)
{
    uint32_t beg = *v, end = v[1];
    for (; beg < end; beg += 0x1c) {
        RCObj* r = (RCObj*)*(void**)(beg + 4);
        if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
    }
    if (*v != 0 && *v != v[4])
        operator_delete_((void*)*v);
}

// @ 0x00747920
void Stub00747920::F()
{
    unsigned char* b = (unsigned char*)this;
    int beg = *(int*)(b + 0x18);
    int end = *(int*)(b + 0x1c);
    if (beg == end) {
        if (end) operator_delete_((void*)end);
        int* mapEnd = (int*)(*(int*)(b + 0x24) - 4);
        *(int**)(b + 0x24) = mapEnd;
        int blk = *mapEnd;
        *(int*)(b + 0x1c) = blk;
        *(int*)(b + 0x20) = blk + 0xe0;
        *(int*)(b + 0x18) = blk + 0xc4;
        if (*(int**)(blk + 200)) {
            RCObj* r = *(RCObj**)(blk + 200);
            (*(void(__thiscall**)(RCObj*, int))((char*)(*(void**)r) + 4))(r, 1);
        }
    } else {
        *(int*)(b + 0x18) = beg - 0x1c;
        RCObj* r = *(RCObj**)(beg - 0x18);
        if (r) (*(void(__thiscall**)(RCObj*, int))((char*)(*(void**)r) + 4))(r, 1);
    }
}

// @ 0x00747980
void FUN_00747980(int* d, int* entry)
{
    RCObj* o = (RCObj*)entry[1];
    if (o) (*(void(__thiscall**)(RCObj*))(*(void**)o))(o);
    if (d[1] <= (int)((unsigned)(d[9] - *d) >> 2) + 1)
        FUN_007457a0(1, 1);
    void* blk = operator_new(0xe0, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    *(void**)(d[9] + 4) = blk;
    int* slot = (int*)d[6];
    if (slot) {
        RCObj* o2 = (RCObj*)entry[1];
        slot[0] = entry[0];
        slot[1] = (int)o2;
        if (o2) (*(void(__thiscall**)(RCObj*))(*(void**)o2))(o2);
        slot[2] = entry[2];
        slot[3] = entry[3];
        slot[4] = entry[4];
        slot[5] = entry[5];
        slot[6] = entry[6];
    }
    int m = d[9];
    d[9] = m + 4;
    int nb = *(int*)(m + 4);
    d[7] = nb;
    d[8] = nb + 0xe0;
    d[6] = d[7];
    RelObj(o);
}

// @ 0x00747ac0
Rec38* Rec38Stub::F(Rec38* src)
{
    Rec38* dst = (Rec38*)this;
    dst->a = src->a;
    dst->b = src->b;
    dst->c = src->c;
    dst->d = src->d;
    dst->e = src->e;
    dst->f = src->f;
    dst->g = src->g;
    new (&dst->rot) Mat3_s0074_7920(src->rot);
    return dst;
}

// @ 0x00747b70
void FUN_00747b70(E3CResult* res, E3C* first, E3C* last, E3C* dst)
{
    res->cur = (int)dst;
    if (first != last) {
        for (; first != last; first += 1, dst += 1) {
            if (dst) {
                dst->key = first->key;
                RCObj* o = first->obj;
                if (o != dst->obj) {
                    if (o) (*(void(__thiscall**)(RCObj*))(*(void**)o))(o);
                    dst->obj = o;
                    if (dst->obj) RelObj(dst->obj);
                }
                dst->a = first->a;
                dst->b = first->b;
                dst->d = first->d;
                dst->e = first->e;
                dst->f = first->f;
                dst->g = first->g;
                dst->h = first->h;
                dst->i = first->i;
                dst->j = first->j;
                dst->k = first->k;
                dst->l = first->l;
                dst->m = first->m;
            }
        }
        res->cur = (int)dst;
    }
}

// @ 0x00747c90
void* FUN_00747c90(E3C* dst, int n, E3C* value)
{
    // the original only computes eax after the n>0 test, so an n==0 call returns
    // the caller's incoming eax unchanged
    uint32_t entryEax;
    __asm { mov entryEax, eax }
    if ((uint32_t)n == 0)
        return (void*)entryEax;
    Plain3C74* d = (Plain3C74*)dst;
    Plain3C74* v = (Plain3C74*)value;
    for (uint32_t i = (uint32_t)n; i != 0; --i, ++d) {
        if (d == 0) break;
        *d = *v;
    }
    // the original keeps the cursor pre-biased by +0x10 and hands it back in eax
    return (char*)d + 0x10;
}

// @ 0x00747eb0
void MakeHeapOccluder(Occluder* first, Occluder* last, OccluderCmp compare)
{
    int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            AdjustHeapOccluder(first, parentPosition, heapSize, parentPosition,
                               *(first + parentPosition), compare);
        } while (parentPosition != 0);
    }
}

// @ 0x00747f30
void PopHeapOccluder(Occluder4* first, Occluder4* last, OccluderCmp compare)
{
    for (; (last - first) > 1; --last) {
        Occluder4 temp(*(last - 1));
        *(last - 1) = *first;
        int n = (int)(last - first) - 1;
        AdjustHeapOccluder((Occluder*)first, 0, n, 0, *(Occluder*)&temp, compare);
    }
}

// @ 0x00748010
void MakeHeapGt(FKP* first, FKP* last, uint32_t compare)
{
    int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            FUN_00745e00(first, parentPosition, heapSize, parentPosition,
                         first[parentPosition].x, first[parentPosition].y, compare);
        } while (parentPosition != 0);
    }
}

// @ 0x00748060
void SortHeapGt(FKP* first, FKP* last, uint32_t compare)
{
    for (; (last - first) > 1; --last) {
        FKP temp(*(last - 1));
        *(last - 1) = *first;
        FUN_00745e00(first, 0, (int)(last - first) - 1, 0, temp.x, temp.y, compare);
    }
}

// @ 0x007480c0
void MakeHeapLt(FKP* first, FKP* last, uint32_t compare)
{
    int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            FUN_00745e80(first, parentPosition, heapSize, parentPosition,
                         first[parentPosition].x, first[parentPosition].y, compare);
        } while (parentPosition != 0);
    }
}

// @ 0x00748110
void SortHeapLt(FKP* first, FKP* last, uint32_t compare)
{
    for (; (last - first) > 1; --last) {
        FKP temp(*(last - 1));
        *(last - 1) = *first;
        FUN_00745e80(first, 0, (int)(last - first) - 1, 0, temp.x, temp.y, compare);
    }
}

// @ 0x00748170
void FUN_00748170(int* first, int* last, int* dst)
{
    for (; first != last; first += 0xf, dst += 0xf) {
        if (dst) {
            dst[0] = first[0];
            *(short*)(dst + 1) = *(short*)(first + 1);
            *(short*)((char*)dst + 6) = *(short*)((char*)first + 6);
            dst[2] = first[2];
            dst[3] = first[3];
            dst[4] = first[4];
            dst[5] = first[5];
            dst[6] = first[6];
            dst[7] = first[7];
            dst[8] = first[8];
            dst[9] = first[9];
            dst[10] = first[10];
            dst[11] = first[11];
            dst[12] = first[12];
            dst[13] = first[13];
            dst[14] = first[14];
        }
    }
}

// @ 0x00748280
// three iterators are passed by value: {current, block begin, block end, map slot}
void* FUN_00748280(void* out,
                   char* fcur, char* fbeg, char* fend, char** fmap,
                   char* lcur, char* lbeg, char* lend, char** lmap,
                   char* rcur, char* rbeg, char* rend, char** rmap)
{
    DequeBlockIter74 first = { fcur, fbeg, fend, fmap };
    DequeBlockIter74 last = { lcur, lbeg, lend, lmap };
    DequeBlockIter74 result = { rcur, rbeg, rend, rmap };
    while (first.cur != last.cur) {
        CopyElem3C74((RCElem3C74*)result.cur, (const RCElem3C74*)first.cur);
        result.cur += 0x1c;
        if (result.cur == result.end) {
            result.map += 1;
            char* nb = *result.map;
            result.cur = nb;
            result.begin = nb;
            result.end = nb + 0xe0;
        }
        first.cur += 0x1c;
        if (first.cur == first.end) {
            first.map += 1;
            char* nb = *first.map;
            first.cur = nb;
            first.begin = nb;
            first.end = nb + 0xe0;
        }
    }
    DequeBlockIter74* o = (DequeBlockIter74*)out;
    o->cur = result.cur;
    o->begin = result.begin;
    o->end = result.end;
    o->map = result.map;
    return out;
}

// @ 0x00748380
void* FUN_00748380(void* out,
                   char* fcur, char* fbeg, char* fend, char** fmap,
                   char* lcur, char* lbeg, char* lend, char** lmap,
                   char* rcur, char* rbeg, char* rend, char** rmap)
{
    DequeBlockIter74 first = { fcur, fbeg, fend, fmap };
    DequeBlockIter74 src = { lcur, lbeg, lend, lmap };
    DequeBlockIter74 dst = { rcur, rbeg, rend, rmap };
    if (src.cur != first.cur) {
        for (;;) {
            if (src.cur == src.begin) {
                src.map -= 1;
                char* nb = *src.map;
                src.begin = nb;
                src.end = nb + 0xe0;
                src.cur = src.end;
            }
            src.cur -= 0x1c;
            if (dst.cur == dst.begin) {
                dst.map -= 1;
                char* nb = *dst.map;
                dst.begin = nb;
                dst.end = nb + 0xe0;
                dst.cur = dst.end;
            }
            dst.cur -= 0x1c;
            CopyElem3C74((RCElem3C74*)dst.cur, (const RCElem3C74*)src.cur);
            if (src.cur == first.cur) break;
        }
    }
    DequeBlockIter74* o = (DequeBlockIter74*)out;
    o->cur = dst.cur;
    o->begin = dst.begin;
    o->end = dst.end;
    o->map = dst.map;
    return out;
}

// @ 0x00748470
int* FUN_00748470(int first, int last, int* dst)
{
    if (last == first) return dst;
    int* result = dst;
    int src = last - 0x1c;
    do {
        int* d = dst - 7;
        d[0] = *(int*)(src);
        RCObj* so = *(RCObj**)(src + 4);
        RCObj* old = (RCObj*)dst[-6];
        if (so != old) {
            if (so) (*(void(__thiscall**)(RCObj*))(*(void**)so))(so);
            dst[-6] = (int)so;
            if (old) RelObj(old);
        }
        d[1] = *(int*)(src + 8);
        d[2] = *(int*)(src + 0xc);
        d[3] = *(int*)(src + 0x10);
        d[4] = *(int*)(src + 0x14);
        d[5] = *(int*)(src + 0x18);
        result = d;
        dst = d;
        last = src;
        src = last - 0x1c;
    } while (last != first);
    return result;
}

// @ 0x00748530
int FilterModelSphere(CullModel_s0074_7920* model, float* pos, SphereArg* arg)
{
    if (!(model->mFlags & 1)) return 1;
    if (!((arg->a == 0 && arg->b == 0) ||
          (model->mMaskB & arg->b) != 0 || (model->mMaskA & arg->a) != 0))
        return 1;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 1;
    if (arg->cb != 0 && !arg->cb((char*)model + 8))
        return 1;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;
    cSPTransform_s0074_7920 local;
    memset(&local, 0, sizeof(local));
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);
    cSPTransform_Assign(&local, model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }
    float dx = pos[0] - local.mTranslation.x;
    float dy = pos[1] - local.mTranslation.y;
    float dz = pos[2] - local.mTranslation.z;
    float reach = model->mRadius * local.mScale;
    if (dx * dx + dy * dy + dz * dz < reach * reach) {
        if (b != 0 && model->mBoxMinX <= model->mBoxMaxX)
            return FUN_00743fb0(pos, 0.0f, &model->mBoxMinX) == 0;
    }
    return 1;
}

// @ 0x00748800
int FilterModelSphere2(CullModel_s0074_8800* model, float* pos, SphereArg* arg)
{
    if (!(model->mFlags & 1)) return 1;
    if (!((arg->a == 0 && arg->b == 0) ||
          (model->mMaskB & arg->b) != 0 || (model->mMaskA & arg->a) != 0))
        return 1;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 1;
    if (arg->cb != 0 && !arg->cb((char*)model + 8))
        return 1;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;

    cSPTransform_s0074_8800 local;
    memset(&local, 0, sizeof(local));
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);
    cSPTransform_Assign(&local, model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }

    float dx0 = local.mTranslation.x - pos[0];
    if (local.mTranslation.x < pos[0] || pos[3] < local.mTranslation.x)
        dx0 = local.mTranslation.x - pos[3];
    else
        dx0 = 0.0f;
    float acc = dx0 * dx0;
    if (local.mTranslation.y < pos[1] || pos[4] < local.mTranslation.y) {
        float d = local.mTranslation.y - pos[4];
        if (!(local.mTranslation.y < pos[1])) d = local.mTranslation.y - pos[4];
        else d = local.mTranslation.y - pos[1];
        acc += d * d;
    }
    {
        float d = 0.0f;
        if (local.mTranslation.z < pos[2] || pos[5] < local.mTranslation.z)
            d = local.mTranslation.z - (pos[5] < local.mTranslation.z ? pos[5] : pos[2]);
        acc += d * d;
    }
    float reach = model->mRadius * local.mScale;
    if (reach * reach < acc) return 1;

    if (b > 2 && model->mInst1 != 0 && *(int*)((char*)model->mInst1 + 0xcc) != 0) {
        char tmp[56];
        translateTransform(tmp, model->mTransform, &local);
        return cModelInstance_IntersectsSphere(model->mInst1, pos, tmp, b == 3) == 0;
    }
    if (b > 1 && model->mInst2 != 0 && *(int*)((char*)model->mInst2 + 0xcc) != 0) {
        char tmp[56];
        translateTransform(tmp, model->mTransform, &local);
        return cModelInstance_IntersectsSphere(model->mInst2, pos, tmp, true) == 0;
    }
    if (b != 0 && model->mBoxMinX <= model->mBoxMaxX) {
        cSPBoundingBox_s0074_8800 box;
        FUN_00511140(&model->mBoxMinX);
        cSPBoundingBox_Transform(&box, model->mTransform);
        return FUN_00490330(pos) == 0;
    }
    return 0;
}

// @ 0x00748ad0
int FUN_00748ad0(float* a, int b, unsigned short* src, int param_4, int param_5, int model, int idx, int param_8, float radius)
{
    PickSrc local;
    local.f0 = src[0];
    local.f1 = src[1];
    local.a = *(float*)(src + 2);
    local.b = *(float*)(src + 4);
    local.c = *(float*)(src + 6);
    local.d = *(int*)(src + 8);
    memcpy(local.rot, src + 10, sizeof(local.rot));
    ComposeTransforms((void*)(model + 0xe4));
    if (radius <= 0.0f) {
        if (FUN_0073e080(a, b, &local, param_8)) return 1;
    } else {
        local.f0 |= 4;
        local.f1++;
        local.a += -a[0];
        local.b += -a[1];
        local.c += -a[2];
        FUN_006ba870(param_5);
        void* inst = *(void**)(model + 0x9c + idx * 4);
        if (cModelInstance_IntersectsSphere(inst, (float*)param_4, &local, false)) return 1;
    }
    return 0;
}

// @ 0x00748c30
void* cModelWorld_s0074_8800::FindClosest(int a, int b, float* outDist, QueryArg* q)
{
    QNode* bestM = 0;
    float best = g_f140d674_s0074_8800;
    if (mCountA == mCountB ||
        *(int*)(*(int*)(g_appProps + 0x3c) + 0x2c) < 2) {
        QNode* anchor = &mList;
        QNode* n = mList.mNext;
        if (n == anchor) return 0;
        do {
            ConsiderModel(n, a, b, q, best, bestM);
            n = n->mNext;
        } while (n != anchor);
    } else {
        QNode* list[0x400];
        int cnt = mTree.Query(a, b, 0.0f, 0x400, list);
        if (cnt < 1) return 0;
        int i = 0;
        do {
            ConsiderModel(list[i], a, b, q, best, bestM);
            ++i;
        } while (i < cnt);
    }
    if (bestM == 0) return 0;
    if (outDist) *outDist = best;
    return (char*)bestM + 8;
}

// @ 0x00749bd0
int FindModelsInFrustum(const void* frustumA, const void* frustumB, CMWModel* model, void* out, FilterArg* arg)
{
    if (model == 0 || (int)model == 8) return 0;
    if (!(model->mFlags & 1)) return 0;
    if ((arg->a != 0 || arg->b != 0) &&
        ((model->mMaskB & arg->b) == 0 && (model->mMaskA & arg->a) == 0))
        return 0;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 0;
    if (arg->cb != 0 && !arg->cb(model))
        return 0;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;

    cSPTransform_s0074_9370 local;
    memset(&local, 0, sizeof(local));
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);
    cSPTransform_Assign(&local, model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }
    float pos[3];
    pos[0] = local.mTranslation.x;
    pos[1] = local.mTranslation.y;
    pos[2] = local.mTranslation.z;
    if (!FUN_00700c80(frustumA, frustumB, pos, model->mRadius * local.mScale, out))
        return 0;

    if ((b < 3 || model->mInst1 == 0) || *(int*)((char*)model->mInst1 + 0xcc) == 0) {
        if ((b < 2 || model->mInst2 == 0) || *(int*)((char*)model->mInst2 + 0xcc) == 0) {
            if (b == 0) return 1;
            if (model->mBoxMaxX <= model->mBoxMinX && model->mBoxMinX != model->mBoxMaxX)
                return 1;
            if (FUN_00744050(frustumA, frustumB, &local, &model->mBoxMinX, out) != 0)
                return 0;
            return 0;
        }
        char tmp[56];
        translateTransform(tmp, model->mTransform, &local);
        if (FUN_0073e080(frustumA, frustumB, tmp, out) != 0) return 0;
        return 0;
    }
    char tmp[56];
    translateTransform(tmp, model->mTransform, &local);
    if (FUN_0073e080(frustumA, frustumB, tmp, out) != 0) return 0;
    return 0;
}

// @ 0x00749e50
int PickAgainstModel(float* pos, float radius, CMWModel* model, FilterArg* arg)
{
    if (model == 0 || (int)model == 8) return 0;
    if (!(model->mFlags & 1)) return 0;
    if (!((arg->a == 0 && arg->b == 0) ||
          (model->mMaskB & arg->b) != 0 || (model->mMaskA & arg->a) != 0))
        return 0;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 0;
    if (arg->cb != 0 && !arg->cb(model))
        return 0;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;

    cSPTransform_s0074_9370 local;
    memset(&local, 0, sizeof(local));
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);
    cSPTransform_Assign(&local, model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }
    float reach = model->mRadius * local.mScale + radius;
    float dx = pos[0] - local.mTranslation.x;
    float dy = pos[1] - local.mTranslation.y;
    float dz = pos[2] - local.mTranslation.z;
    if (dx * dx + dy * dy + dz * dz >= reach * reach)
        return 0;
    if ((b < 3 || model->mInst1 == 0) || *(int*)((char*)model->mInst1 + 0xcc) == 0) {
        if (b != 0 &&
            (model->mBoxMinX < model->mBoxMaxX || model->mBoxMinX == model->mBoxMaxX) &&
            FUN_00743fb0(pos, radius, &model->mBoxMinX) == 0)
            return 0;
    } else {
        char tmp[56];
        translateTransform(tmp, model->mTransform, &local);
        if (cModelInstance_PickLine(model->mInst1, pos, radius, tmp, false) == 0) return 0;
    }
    return 1;
}

// @ 0x0074a070
int FUN_0074a070(float* pos, CMWModel* model, FilterArg* arg)
{
    if (model == 0 || (int)model == 8) return 0;
    if (!(model->mFlags & 1)) return 0;
    if (!((arg->a == 0 && arg->b == 0) ||
          (model->mMaskB & arg->b) != 0 || (model->mMaskA & arg->a) != 0))
        return 0;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 0;
    if (arg->cb != 0 && !arg->cb(model))
        return 0;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;

    cSPTransform_s0074_9370 local;
    memset(&local, 0, sizeof(local));
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);
    cSPTransform_Assign(&local, model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }
    float reach = model->mRadius * local.mScale;
    float dx0 = local.mTranslation.x - pos[0];
    if (!(local.mTranslation.x < pos[0] || pos[3] < local.mTranslation.x)) dx0 = 0.0f;
    else dx0 = local.mTranslation.x - pos[3];
    float acc = dx0 * dx0;
    {
        float d = 0.0f;
        if (local.mTranslation.y < pos[1]) d = local.mTranslation.y - pos[1];
        else if (pos[4] < local.mTranslation.y) d = local.mTranslation.y - pos[4];
        acc += d * d;
    }
    {
        float d = 0.0f;
        if (local.mTranslation.z < pos[2]) d = local.mTranslation.z - pos[2];
        else if (pos[5] < local.mTranslation.z) d = local.mTranslation.z - pos[5];
        acc += d * d;
    }
    if (acc <= reach * reach) {
        if (b > 2 && model->mInst1 != 0 && *(int*)((char*)model->mInst1 + 0xcc) != 0) {
            char tmp[56];
            translateTransform(tmp, model->mTransform, &local);
            if (cModelInstance_IntersectsSphere(model->mInst1, pos, tmp, false) == 0) return 0;
        }
        return 1;
    }
    return 0;
}

// @ 0x0074a290
void SP::cModelWorld_s0074_a290_s0074_a290::SetExternalEffectsTransform(void* a, void* b, void* c)
{
    char* model = a ? (char*)a - 8 : 0;
    EffRec* rec = *(EffRec**)(model + 0xdc);
    if (rec == 0)
        return;

    if (b != 0) {
        if (rec->obj == 0)
            return;
        do {
            if (c == 0 || (c == (void*)rec->id && rec->id2 == 0)) {
                rec->xf = *(cSPTransform_s0074_a290_s0074_a290*)b;
                void* obj = rec->obj;
                cSPTransform_s0074_a290_s0074_a290 t;
                t.f0 = *(uint16_t*)((char*)a + 8);
                t.f2 = *(uint16_t*)((char*)a + 0xa);
                t.f4 = *(float*)((char*)a + 0xc);
                t.f8 = *(float*)((char*)a + 0x10);
                t.fc = *(float*)((char*)a + 0x14);
                t.f10 = *(float*)((char*)a + 0x18);
                ((Matrix3_s0074_a290*)&t.m[0])->Assign((char*)a + 0x1c);
                t.Compose(&rec->xf);
                ((void(__thiscall*)(void*, cSPTransform_s0074_a290_s0074_a290*))VT(obj)[0x18 / 4])(obj, &t);
            }
            rec++;
        } while (rec->obj);
        return;
    }

    int count = 0;
    void* data = 0;
    PropGetTransforms(*(void**)((char*)a + 0x90), 0x2a907b6, &count, &data);
    rec = *(EffRec**)(model + 0xdc);
    if (rec->obj == 0)
        return;
    int i = 0;
    do {
        if (c == 0 || (c == (void*)rec->id && rec->id2 == 0)) {
            void* obj = rec->obj;
            void* arg;
            if (i < count) {
                rec->xf = ((cSPTransform_s0074_a290_s0074_a290*)data)[i];
                cSPTransform_s0074_a290_s0074_a290 t = translateTransform_s0074_a290(&rec->xf, (char*)a + 8);
                arg = &t;
            } else {
                rec->xf.f0 = 0;
                rec->xf.f2 = 0;
                rec->xf.f4 = g_162eb0c;
                rec->xf.f8 = g_162eb10;
                rec->xf.fc = g_162eb14;
                rec->xf.f10 = g_1485720;
                *(Matrix3_s0074_a290*)&rec->xf.m[0] = *(Matrix3_s0074_a290*)g_162ec4c;
                arg = (char*)a + 8;
            }
            ((void(__thiscall*)(void*, void*))VT(obj)[0x18 / 4])(obj, arg);
        }
        i++;
        rec++;
    } while (rec->obj);
}

// @ 0x0074a490
void SP::cModelWorld_s0074_a290_s0074_a290::SubA490(void* model, void* outp)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    uint32_t* p = *(uint32_t**)outp;
    if (p == 0) {
        p = (uint32_t*)GfxAlloc(0x28, "Graphics", 0, 0, 0, 0);
        if (p) {
            p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0;
            p[5] = 0; p[6] = 0; p[7] = 0; p[8] = 0; p[9] = 0;
        }
        void* arg = base ? base + 8 : 0;
        ((void(__thiscall*)(void*, void*, void*))VT(this)[0xd8 / 4])(this, arg, p);
        p[8] = p[0];
        p[9] = p[4];
        p[7] = p[2];
        uint32_t n = p[2];
        p[0] = 0xc;
        p[4] = (uint32_t)GfxAlloc(n * 0xc, "Graphics", 0, 0, 0, 0);
        *(uint32_t**)outp = p;
    } else {
        ((void(__thiscall*)(void*, void*, void*))VT(this)[0x17c / 4])(this, model, p);
    }

    cSPTransform_s0074_a290_s0074_a290 t;
    t.f0 = *(uint16_t*)(base + 0x10);
    t.f2 = *(uint16_t*)(base + 0x12);
    t.f4 = *(float*)(base + 0x14);
    t.f8 = *(float*)(base + 0x18);
    t.fc = *(float*)(base + 0x1c);
    t.f10 = *(float*)(base + 0x20);
    ((Matrix3_s0074_a290*)&t.m[0])->Assign(base + 0x24);
    t.Compose((cSPTransform_s0074_a290_s0074_a290*)(base + 0xe4));

    void* src = (void*)p[9];
    void* dst = (void*)p[4];
    if (p[8] == p[0]) {
        ((VecCopyFn)0x11e0744)(dst, src, p[2] * p[0]);
    } else {
        uint32_t* s = (uint32_t*)src;
        uint32_t* d = (uint32_t*)dst;
        for (uint32_t k = p[2]; k > 0; k--) {
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            s = (uint32_t*)((char*)s + p[8]);
            d += 3;
        }
    }
    ((Sub9510Fn)0x6b9510)(&t, p[2], (void*)p[4], 0xc);
}

// @ 0x0074a650
void SP::cModelWorld_s0074_a290_s0074_a290::ReleaseTransformedHull(void** pp)
{
    TransformedHull* h = (TransformedHull*)*pp;
    if (h) {
        eastl_dealloc(h->p10);
        HullVtbl* p = h->p18;
        if (p)
            p->slot1();
        eastl_dealloc(h);
    }
}

// @ 0x0074a690
bool SP::cModelWorld_s0074_a290_s0074_a290::GetBakedMeshes(void* model, void* arg2)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    if (*(int*)(base + 0x9c) != 0) {
        cSPTransform_s0074_a290_s0074_a290 t = translateTransform_s0074_a290(base + 0xe4, base + 0x10);
        cModelInstance_s0074_a290_s0074_a290* inst = *(cModelInstance_s0074_a290_s0074_a290**)(base + 0x9c);
        return inst->BuildBaked(&t, arg2);
    }
    return false;
}

// @ 0x0074a700
bool SP::cModelWorld_s0074_a290_s0074_a290::GetBakedMeshesUnscaled(void* model, void* arg2)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    if (*(int*)(base + 0x9c) != 0) {
        cSPTransform_s0074_a290_s0074_a290 t = translateTransform_s0074_a290(base + 0xe4, base + 0x10);
        ++t.f2;
        t.f10 = 1.0f;
        cModelInstance_s0074_a290_s0074_a290* inst = *(cModelInstance_s0074_a290_s0074_a290**)(base + 0x9c);
        return inst->BuildBaked(&t, arg2);
    }
    return false;
}

// @ 0x0074a780
bool SP::cModelWorld_s0074_a290_s0074_a290::GetBakedMeshes2(void* model, void* arg2, cSPTransform_s0074_a290_s0074_a290* out)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    if (*(int*)(base + 0x9c) != 0) {
        cSPTransform_s0074_a290_s0074_a290 r = translateTransform_s0074_a290(base + 0xe4, base + 0x10);
        *out = r;
        r.f0 = 0;
        r.f2 = 0;
        r.f4 = g_162eb0c;
        r.f8 = g_162eb10;
        r.fc = g_162eb14;
        r.f10 = g_1485720;
        ((Matrix3_s0074_a290*)&r.m[0])->Assign((const void*)g_162ec4c);
        cModelInstance_s0074_a290_s0074_a290* inst = *(cModelInstance_s0074_a290_s0074_a290**)(base + 0x9c);
        return inst->BuildBaked(&r, arg2);
    }
    return false;
}

// @ 0x0074a850
bool SP::cModelWorld_s0074_a290_s0074_a290::GetMeshes(void* model, void* arg2, cSPTransform_s0074_a290_s0074_a290* out)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    if (*(int*)(base + 0x9c) != 0) {
        *out = translateTransform_s0074_a290(base + 0xe4, base + 0x10);
        cModelInstance_s0074_a290_s0074_a290* inst = *(cModelInstance_s0074_a290_s0074_a290**)(base + 0x9c);
        return inst->GetMeshesX(arg2);
    }
    return false;
}

// @ 0x0074a920
void SP::cModelWorld_s0074_a290_s0074_a290::SubA920(void* list, void* obj, uint32_t flags)
{
    char* o = (char*)obj;
    for (int i = 0; i < 6; i++) {
        ReleaseSlot((void**)(o + 0x9c + i * 4));
        ReleaseSlot((void**)(o + 0xb4 + i * 4));
        *(uint8_t*)(o + 0xcc + i) = 0xff;
    }

    PropKey k;
    k.id = 0; k.id2 = 0; k.idx = 0;
    for (int i = 0; i < 4; i++) {
        if (!GetPropertyAsKey(list, i + 0xf9efbb, &k))
            break;
        void** slot = (void**)(o + 0x9c + i * 4);
        ReleaseSlot(slot);
        int idx = (k.idx == -1) ? *(int*)((char*)list + 0x10) : k.idx;
        CreateModelInstance(k.id, idx, slot, flags);
    }

    if ((flags & 0x20) && GetPropertyAsKey(list, 0xf9efc1, &k)) {
        void** slot = (void**)(o + 0xb0);
        int idx = (k.idx == -1) ? *(int*)((char*)list + 0x10) : k.idx;
        ReleaseSlot(slot);
        CreateModelInstance(k.id, idx, slot, 0);
    }

    if (GetPropertyAsKey(list, 0xf9efc0, &k)) {
        void** slot = (void**)(o + 0xac);
        int idx = (k.idx == -1) ? 0 : k.idx;
        ReleaseSlot(slot);
        CreateModelInstance(k.id, idx, slot, 0);
    }

    Sub7340(obj);

    void** pslot = (void**)(o + 0x9c);
    if (*pslot == 0)
        pslot = (void**)(o + 0xac);
    void* src = *pslot;
    if (src == 0)
        goto tail;

    if (!(*(uint8_t*)(o + 0xe) & 1)) {
        *(uint32_t*)(o + 0x84) = *(uint32_t*)((char*)src + 0xb4);
        *(uint32_t*)(o + 0x88) = *(uint32_t*)((char*)src + 0xb8);
        *(uint32_t*)(o + 0x8c) = *(uint32_t*)((char*)src + 0xbc);
        *(uint32_t*)(o + 0x78) = *(uint32_t*)((char*)src + 0xa8);
        *(uint32_t*)(o + 0x7c) = *(uint32_t*)((char*)src + 0xac);
        *(uint32_t*)(o + 0x80) = *(uint32_t*)((char*)src + 0xb0);
        if (*(float*)(o + 0xf4) != 1.0f || (*(uint8_t*)(o + 0xe4) & 6))
            ((cSPBoundingBox_s0074_a290*)(o + 0x78))->TransformBy(o + 0xe4);
    }

    if (!((*(uint32_t*)(o + 0xc) >> 0x11) & 1)) {
        float v = *(float*)((char*)src + 0xc0);
        *(float*)(o + 0x74) = v;
        if (*(float*)(o + 0xf4) != 1.0f || (*(uint8_t*)(o + 0xe4) & 6)) {
            v = *(float*)(o + 0xf4) * *(float*)(o + 0x74);
            *(float*)(o + 0x74) = v;
            float dx = *(float*)(o + 0xe8);
            float dy = *(float*)(o + 0xec);
            float dz = *(float*)(o + 0xf0);
            *(float*)(o + 0x74) = sqrtf(dx * dx + dy * dy + dz * dz) + v;
        }
    }

tail:
    *(uint32_t*)(o + 0xc) |= 0x4000;
    ++*(uint16_t*)(o + 0x70);
    void* q = *(void**)(o + 0x6c);
    if (q) {
        void* r = ((void*(__thiscall*)(void*, unsigned))VT(q)[0xc / 4])(q, 0x7bbc4ff);
        if (r)
            ((void(__thiscall*)(void*, void*))VT(r)[0])(r, o + 8);
    }
}

// @ 0x0074ac80
void SP::cModelWorld_s0074_a290_s0074_a290::AddAttachments(char* m)
{
    cSPTransform_s0074_a290_s0074_a290 t;
    Rec48_s0074_a290* r;
    char* var;
    int n; int first; int c2;
    int cnt1; void* data1; int cnt2; void* data2; int cnt3; void* data3;
    uint32_t flags = *(uint32_t*)(m + 0x138);
    if (!(flags & 8)) {
        void* list = *(void**)(m + 0x98);
        if (!(flags & 4) && PropReserve(list, 0x2a907b5, &cnt1, &data1)) {
            int good = 0;
            cnt2 = 0;
            PropGetTransforms(list, 0x2a907b6, &cnt2, &data2);
            cnt3 = 0;
            data3 = 0;
            PropReserve(list, 0x2a907b9, &cnt3, &data3);
            void* defModel = *(void**)((char*)this + 0x5c8);
            if (defModel == 0) {
                void* e = EffectsManager();
                defModel = VCALL(void*(__thiscall*)(void*), e, 0x5c)(e);
            }
            for (int i = 0; i < cnt1; i++) {
                void* e = EffectsManager();
                if (VCALL(bool(__thiscall*)(void*, unsigned, int), e, 0x28)(e, *(unsigned*)((char*)data1 + i * 12), 0))
                    good++;
            }
            Rec48_s0074_a290* recs = new ("Graphics", 0, 0, 0, 0) Rec48_s0074_a290[good + 1];
            *(Rec48_s0074_a290**)(m + 0xdc) = recs;
            int j = 0;
            for (int i = 0; i < cnt1; i++) {
                r = (Rec48_s0074_a290*)(*(char**)(m + 0xdc) + j * 0x48);
                void* mdl;
                if (i < cnt3) {
                    void* e = EffectsManager();
                    mdl = VCALL(void*(__thiscall*)(void*, unsigned), e, 0x54)(e, *(unsigned*)((char*)data3 + i * 12));
                    if (mdl == 0) mdl = defModel;
                } else {
                    mdl = defModel;
                }
                if (r->obj) {
                    IRel* o = r->obj;
                    r->obj = 0;
                    o->Release();
                }
                if (VCALL(bool(__thiscall*)(void*, unsigned, int, void*), mdl, 8)(mdl, *(unsigned*)((char*)data1 + i * 12), 0, &r->obj)) {
                    void* o = r->obj;
                    VCALL(void(__thiscall*)(void*, int, void*), o, 0x4c)(o, 6, (char*)this + 0xc);
                    if (i < cnt2) {
                        r->xf = ((cSPTransform_s0074_a290_s0074_a290*)data2)[i];
                        t.f0 = *(uint16_t*)(m + 0x10);
                        t.f2 = *(uint16_t*)(m + 0x12);
                        t.f4 = *(float*)(m + 0x14);
                        t.f8 = *(float*)(m + 0x18);
                        t.fc = *(float*)(m + 0x1c);
                        t.f10 = *(float*)(m + 0x20);
                        ((Matrix3_s0074_a290*)&t.m[0])->Assign(m + 0x24);
                        t.Compose(&r->xf);
                        void* o2 = r->obj;
                        VCALL(void(__thiscall*)(void*, cSPTransform_s0074_a290_s0074_a290*), o2, 0x18)(o2, &t);
                    } else {
                        void* o2 = r->obj;
                        VCALL(void(__thiscall*)(void*, void*), o2, 0x18)(o2, m + 0x10);
                    }
                    if ((*(uint32_t*)(m + 0xc) >> 0x13) & 1) {
                        void* o3 = r->obj;
                        VCALL(void(__thiscall*)(void*, int), o3, 8)(o3, 0);
                    }
                    if (!(*(uint8_t*)(m + 0xc) & 1)) {
                        void* o4 = r->obj;
                        VCALL(void(__thiscall*)(void*, int), o4, 0x30)(o4, 1);
                    }
                    r->id = *(uint32_t*)((char*)data1 + i * 12);
                    r->id2 = 0;
                    j++;
                }
            }
            if (!(*(uint32_t*)(m + 0x138) & 0x20000000)) {
                *(float*)(m + 0x124) = 0.0f;
                if (list) {
                    if (VCALL(bool(__thiscall*)(void*, unsigned, char**), list, 0x24)(list, 0x2a907b8, &var)
                        && *(uint16_t*)(var + 0x12) == 0xd) {
                        char* p = var;
                        if (*(uint8_t*)(var + 0x10) & 0x30) p = *(char**)var;
                        *(float*)(m + 0x124) = *(float*)p;
                    }
                }
            }
        }
        if (*(int*)((char*)this + 0x1cc) != 0) {
            if (PropGetFloats(list, 0x49fc837, &n, &first)) {
                unsigned size = n * 4 + 0x14;
                int* p = (int*)GfxAlloc(size, "Graphics", 0, 0, 0, 0);
                memset(p, 0, size);
                p[0] = n;
                for (int k = 0; k < n; k++) p[5 + k] = -1;
                *(int**)(m + 0xe0) = p;
                p[1] = first;
                if (PropGetInts(list, 0x49fc838, &c2, *(char**)(m + 0xe0) + 8) && c2 != n)
                    (*(int**)(m + 0xe0))[2] = 0;
                if (PropGetInts(list, 0x49fc83a, &c2, *(char**)(m + 0xe0) + 0x10) && c2 != n)
                    (*(int**)(m + 0xe0))[4] = 0;
                if (PropGetFloats(list, 0x49fc839, &c2, *(char**)(m + 0xe0) + 0xc) && c2 != n)
                    (*(int**)(m + 0xe0))[3] = 0;
            }
        }
        char* mgr = *(char**)((char*)this + 0x18);
        void** it = *(void***)(mgr + 0x4c);
        void** end = *(void***)(mgr + 0x50);
        for (; it != end; ++it) {
            void* o = *it;
            VCALL(void(__thiscall*)(void*, void*), o, 0)(o, m + 8);
        }
    }
}

// @ 0x0074b150
void SP::cModelWorld_s0074_a290_s0074_a290::FreeTransformedBuffer()
{
    void* p = *(void**)((char*)this + 0x44);
    if (p && p != *(void**)((char*)this + 0x54))
        eastl_dealloc(p);
}

// @ 0x0074b170
void cloadqueue_b170(void* self)
{
    (void)self;
}

// @ 0x0074b2b0
SP::cLoadQueue::~cLoadQueue()
{}

// @ 0x0074b390
void partial_sort_b390(void* a, void* b, void* c, void* cmp)
{
    (void)a; (void)b; (void)c; (void)cmp;
}

// @ 0x0074b690
void SP::cModelWorld_s0074_b170::SetInWorld(ListNode_s0074_b170* n, bool b)
{
    if (mWorldType == 0)
        return;
    if (((n->flags >> 0xf) & 1) == (uint32_t)b)
        return;
    ListNode_s0074_b170* node = (ListNode_s0074_b170*)((char*)n - 8);
    ListNode_s0074_b170* prev = node->prev;
    ListNode_s0074_b170* next = node->next;
    next->prev = prev;
    prev->next = next;
    node->prev = 0;
    node->next = 0;
    if (b) {
        node->next = mListA.next;
        node->prev = &mListA;
        mListA.next = node;
        node->next->prev = node;
        AddAttachments(node);
    } else {
        node->next = mListB.next;
        node->prev = &mListB;
        mListB.next = node;
        node->next->prev = node;
        ShutdownModel(node);
    }
    if (b)
        node->flags |= 0x8000;
    else
        node->flags &= 0xffff7fff;
}

// @ 0x0074b760
__forceinline const float* ValFloat(Property* p)
{
    if (p->mnType == 0xd || p->mnType == 0x10) return (const float*)p->Items();
    return &kDefaultFloat;
}

// @ 0x0074bda0
void list_find_bda0(void* self, void* key)
{
    (void)self; (void)key;
}

// @ 0x0074be40
void list_erase_be40(void* self, int* key)
{
    (void)self; (void)key;
}

// @ 0x0074bf10
void vec_insert_bf10(void* self, void* pos, void* val)
{
    (void)self; (void)pos; (void)val;
}

// @ 0x0074c020
void vec_insert_c020(void* self, void* pos, void* val)
{
    (void)self; (void)pos; (void)val;
}

// @ 0x0074c260
template void eastl::quick_sort_impl<cDrawModelInfo*, int, DrawGreater>(cDrawModelInfo*, cDrawModelInfo*, int, DrawGreater)
;

// @ 0x0074c370
template void eastl::quick_sort_impl<cDrawModelInfo*, int, cAlphaSortLessComparator>(cDrawModelInfo*, cDrawModelInfo*, int, cAlphaSortLessComparator)
;

// @ 0x0074c580
template cOccluder_s0074_c260* eastl::get_partition<cOccluder_s0074_c260*, cOccluder_s0074_c260, OccCmp>(cOccluder_s0074_c260*, cOccluder_s0074_c260*, cOccluder_s0074_c260, OccCmp)
;

// @ 0x0074c670
bool SP::cModelWorld::ModelIsResidentInMemory(SP::cPropertyList * model)
{
    if (!g_appProps_s0074_c260->GetDescription(0x69089a6))
        return false;
    if (model == 0)
        return false;
    ResMgrW* mgr = GetResMgrW();
    int i = 0;
    do {
        ModelKey k = { 0, 0, 0 };
        if (!GetPropertyAsKey(model, 0xf9efbb + i, &k)) {
            if (i == 0)
                return false;
            break;
        }
        RefHolder res;
        k.type = 0xe6bce5;
        if (!mgr->Find14(&k, &res.p) && mgr->Error58(&k) != 0)
            return false;
        if (res.p == 0) {
            k.type = 0x2f4e681b;
            if (!mgr->Find14(&k, 0) && mgr->Error58(&k) != 0)
                return false;
        } else {
            TmpVec v;
            FillResourceList(res.p, &v, g_fn743910);
            if (v.b != v.e) {
                DestructRange(&v, 0, v.b, v.e);
                if (v.b != 0 && v.b[-1] != 0)
                    OpDeleteArr(v.b);
                return false;
            }
            DestructRange(&v, 0, v.b, v.e);
            if (v.b != 0 && v.b[-1] != 0)
                OpDeleteArr(v.b);
        }
        ++i;
    } while (i < 4);

    ModelKey k2 = { 0, 0, 0 };
    if (GetPropertyAsKey(model, 0xf9efc0, &k2)) {
        k2.type = 0xe6bce5;
        if (!mgr->Find14(&k2, 0) && mgr->Error58(&k2) != 0)
            return false;
        k2.type = 0x2f4e681b;
        if (!mgr->Find14(&k2, 0)) {
            if (mgr->Error58(&k2) != 0)
                return false;
        }
    }
    return true;
}

// @ 0x0074c910
void cModelWorld_s0074_c260::ScheduleForLoad(ModelEntry* entry, RefCounted* model, uint32_t a4, uint32_t a5)
{
    entry->flags0 &= 0xffffbfff;
    if (entry->idx >= 0)
        UpdateFromPropList(model, entry, entry->idx, 0);
    uint32_t* key = &entry->key;
    bool found;
    {
        uint32_t i = 0;
        uint32_t* p = &active[0][0];
        for (;;) {
            if ((uint32_t*)*p == key) { found = true; break; }
            ++i;
            p += 0x14;
            if (i >= 8) { found = false; break; }
        }
    }
    bool propOn = g_appProps_s0074_c260->GetDescription(0x3dd1848d);
    bool resident = ModelIsResidentInMemory(model);
    if (!propOn || (!found && resident)) {
        uint32_t* kk = key;
        queue.Remove(kk ? (uint32_t*)&kk : 0);
        Load74a920(model, entry, entry->idx);
    } else {
        LoadReq r;
        r.key = (uint32_t)key;
        r.model = model;
        if (model) model->AddRef();
        r.a4 = a4;
        r.a5 = a5;
        r.idx = entry->idx;
        r.z0 = 0;
        r.z1 = 0;
        queue.Push(&r);
    }
}

// @ 0x0074ca70
bool VecInt::remove_first(int v)
{
    int n = (int)((char*)end - (char*)begin) >> 2;
    if (n > 0) {
        int i = 0;
        int* p = begin;
        do {
            if (*p == v) {
                int* dst = begin + i;
                int* src = dst + 1;
                if (src < end)
                    memmove_(dst, src, (unsigned)((char*)end - (char*)src));
                end = (int*)((char*)end - 4);
                return true;
            }
            ++i;
            ++p;
        } while (i < n);
    }
    return false;
}

// @ 0x0074cad0
bool LoadJob::Step(cJobW* cj)
{
    if (state == 6) {
        state = 0;
        count = 1;
    } else {
        RefCounted* r;
        if (job == 0) {
            r = 0;
        } else {
            ((cJobW*)job)->Wait();
            r = job->res;
        }
        ResMgrW* mgr = GetResMgrW2();
        RefCounted* old = refs[state];
        if (r != old) {
            if (r) ((uint32_t*)r)[1]++;
            refs[state] = r;
            if (old) {
                int n = ((int*)old)[1] - 1;
                ((int*)old)[1] = n;
                if (n == 0) {
                    ((int*)old)[1] = 1;
                    old->Release();
                }
            }
        }
        if (r) {
            TmpVec v;
            ((ResListW*)r)->Fill(&v, g_fn743910);
            uint32_t* p = v.b;
            if (p != v.e) {
                do {
                    mgr->Notify38(*p, userArg);
                    ++p;
                } while (p != v.e);
            }
            DestructRange(&v, 0, v.b, v.e);
            if (v.b != 0 && v.b[-1] != 0)
                OpDeleteArr(v.b);
        }
        ++state;
    }
    JobW** pj = &job;
    if (*pj != 0) {
        cJobW* oj = (cJobW*)*pj;
        *pj = 0;
        oj->GetStatus();
    }
    if (state == 6)
        return true;
    ModelKey k = { 0, 0, 0 };
    uint32_t sz;
    uint32_t fl;
    if (state == 0) {
        if (GetPropertyAsKey(props, 0xf9efbb, &k)) {
            sz = k.group;
            if (sz == 0xffffffff) sz = grp;
            fl = flags;
            FUN_00756790(pj, k.inst, sz, fl);
        }
    } else if (state == 4) {
        if ((flags & 0x20) && props && GetPropertyAsKey(props, 0xf9efc1, &k)) {
            sz = k.group;
            if (sz == 0xffffffff) sz = props->flags;
            fl = flags;
            FUN_00756790(pj, k.inst, sz, fl);
        }
    } else if (state == 5) {
        if (GetPropertyAsKey(props, 0xf9efc0, &k)) {
            fl = 0;
            sz = -(uint32_t)(k.group != 0xffffffff) & k.group;
            FUN_00756790(pj, k.inst, sz, fl);
        }
    } else {
        if (!GetPropertyAsKey(props, state + 0xf9efbb, &k)) {
            state = 3;
        } else {
            sz = k.group;
            if (sz == 0xffffffff) sz = props->flags;
            FUN_00756790(pj, k.inst, sz, flags);
            ++count;
        }
    }
    cj->Run6913c0(*pj);
    return cj->Continuation(g_fn74d080, this);
}

// @ 0x0074cdd0
void Vec18::push_back(const E18* v)
{
    E18* e = end;
    if (e < cap) {
        end = e + 1;
        if (e)
            *e = *v;
    } else {
        ((E18Vt*)this)->DoInsert(e, v);
    }
}

// @ 0x0074ce20
void VecE14::DoInsertValue(E14* pos, const E14& value)
{
    if (mEnd != mCap) {
        const E14* pv = &value;
        if (pv >= pos && pv < mEnd)
            ++pv;
        ::new (mEnd) E14(*(mEnd - 1));
        copy_backward14(pos, mEnd - 1, mEnd);
        *pos = *pv;
        ++mEnd;
        return;
    }
    int nPrev = (int)(mEnd - mBegin);
    int nNew;
    if (nPrev) nNew = nPrev * 2; else nNew = 1;
    const int* pNew = &nNew; (void)pNew;
    E14* newBegin = nNew ? (E14*)operator_new_dbg(nNew * sizeof(E14), "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    E14* newPos = uninit_copy14(mBegin, pos, newBegin);
    ::new (newPos) E14(value);
    E14* newEnd = uninit_copy14(pos, mEnd, newPos + 1);
    if (mBegin)
        operator_delete_arr(mBegin);
    mBegin = newBegin;
    mEnd = newEnd;
    mCap = newBegin + nNew;
}

// @ 0x0074d190
template void eastl::quick_sort_impl<cOccluder_s0074_c260*, int, OccCmp>(cOccluder_s0074_c260*, cOccluder_s0074_c260*, int, OccCmp)
;

// @ 0x0074d2c0
bool cModelWorldMsg::HandleMessage(uint32_t msgId, MsgHeader* msg)
{
    if (msgId == 0xf62def) {
        ModelKey k;
        uint32_t c = msg->c;
        k.inst = msg->a; k.type = msg->b; k.group = msg->c;   // msg + 8 / +0x10 / +0x18
        RefHolder res;
        ResMgrW* mgr = GetResMgrW();
        if (res.p) { RefCounted* t = res.p; res.p = 0; t->Release(); }
        if (mgr->Lookup0c(&k, &res.p, 0, 0, 0, 0)) {
            ResChain* want = (ResChain*)res.p;
            cModelWorldX* world = (cModelWorldX*)((char*)this - 8);
            for (ListNode_s0074_c260* n = listA.next; n != &listA; n = n->next) {
                ModelNode* m = (ModelNode*)n;
                for (ResChain* r = m->chain; r; r = r->next) {
                    if (r == want) {
                        world->ShutdownModel(m);
                        world->ScheduleForLoad(m, m->chain, k.group, k.type);
                        want = (ResChain*)res.p;
                        break;
                    }
                }
            }
            for (ListNode_s0074_c260* n = listB.next; n != &listB; n = n->next) {
                ModelNode* m = (ModelNode*)n;
                for (ResChain* r = m->chain; r; r = r->next) {
                    if (r == want) {
                        world->ScheduleForLoad(m, m->chain, k.group, k.type);
                        want = (ResChain*)res.p;
                        break;
                    }
                }
            }
        }
        (void)c;
        return true;
    }
    if (msgId != 0x2495f34)
        return false;
    for (ListNode_s0074_c260* n = listA.next; n != &listA; n = n->next) {
        ModelNode* m = (ModelNode*)n;
        if (m->handle != 0)
            target->Free(m->handle);
        m->handle = 0;
    }
    return true;
}

// @ 0x0074d4b0
void* cModelWorld_s0074_d4b0::CreateModel(uint32_t a, uint32_t b, uint32_t flags)
{
  PropRef props;
  IPropMgr* pm = PropertyManager();
  props.reset();
  if (pm->GetPropertyList(a, b, &props.p)) {
    void* mem;
    for (;;) {
      if (gModelNodeAlloc.mpFree) {
        mem = gModelNodeAlloc.mpFree;
        gModelNodeAlloc.mpFree = (void**)*gModelNodeAlloc.mpFree;
        break;
      }
      if (!gModelNodeAlloc.AddCore(0, 0)) {
        mem = 0;
        break;
      }
    }
    cModelNode* n = mem ? new (mem) cModelNode(this) : 0;
    uint32_t secondary = flags & 0x80000000;
    if (!secondary) {
      ListPushBack(ListAEnd(), n);
      n->mFlags |= 0x8000;
    } else {
      ListPushBack(ListBEnd(), n);
      n->mFlags |= 1;
    }
    n->mCreateFlags = flags;
    // AutoRefCount assignment: n->mProps = props
    IRefObj* np = props.p;
    IRefObj* old = n->mProps;
    if (np != old) {
      if (np) np->AddRef();
      n->mProps = np;
      if (old) old->Release();
    }
    mCount894 += 1;
    if (flags & 0x10) {
      n->mFlags |= 0x4000;
      UpdateFromPropList(props.p, n, flags, 0);
    } else {
      if (!secondary) mCount898 += 1;
      ScheduleForLoad(n, props.p, a, b);
    }
    n->mFlags12c = n->mFlags;
    return n->Obj();
  }

  if (!mbFallback) return 0;

  CookieRef res;
  uint32_t lod = flags & 1;
  if (!CreateModelInstance(a, b, &res, lod)) {
    if (g_015fd918->sub->f94 == 0) return 0;
    if (!CreateModelInstance(0x1565205f, 0xd94352ed, &res, lod)) return 0;
  }
  void* mem = gModelNodeAlloc.Alloc();
  cModelNode* n = mem ? new (mem) cModelNode(this) : 0;
  ListPushBack(ListAEnd(), n);
  mCount894 += 1;
  mCount898 += 1;
  n->mFlags |= 1;
  n->mFlags |= 0x8000;
  n->mCreateFlags = flags;
  {
    // n->mCookie = res (AutoRefCount<cCookie>::operator=)
    ((CookieRef*)&n->mCookie)->operator=(res);
  }
  cCookie* ck = res.p;
  n->mRadius = ck->mScale;
  n->mBoxMax[0] = ck->mV1[0];
  n->mBoxMax[1] = ck->mV1[1];
  n->mBoxMax[2] = ck->mV1[2];
  n->mBoxMin[0] = ck->mV0[0];
  n->mBoxMin[1] = ck->mV0[1];
  n->mBoxMin[2] = ck->mV0[2];
  FUN_007453d0(n->mB4.FUN_007454f0(), n->mCookie, flags);
  uint32_t v = n->mB4.first;
  n->mCookie->FUN_0073ab40(v);
  n->mFlagCC = 0;
  n->mFlags |= 0x4000;
  n->mFlags12c = n->mFlags;
  return n->Obj();
}

// @ 0x0074d870
bool cModelWorld_s0074_d4b0::CollectModels(PtrVec* out, const cModelFilter* f)
{
  cModelNode* end = ListAEnd();
  if (f->pred == 0 && f->incl == 0 && f->excl == 0) {
    for (cModelNode* n = mListA_next; n != end; n = n->mpNext) {
      if (n->mFlags & 1) {
        out->PushObj(n->Obj());
      }
    }
    return out->mpBegin != out->mpEnd;
  }
  for (cModelNode* n = mListA_next; n != end; n = n->mpNext) {
    if (n->mFlags & 1) {
      if ((f->incl == 0 || (n->mMask & f->incl) != 0) &&
          (n->mMask & f->excl) == 0 &&
          (f->pred == 0 || f->pred(n->Obj()))) {
        out->PushObj(n->Obj());
      }
    }
  }
  return out->mpBegin != out->mpEnd;
}

// @ 0x0074eb70
bool cModelWorld_s0074_e2b0::FindModelsInShape(const void* p, float f, ModelVec* out, void* ctx)
{
    Node* items[0x400];
    bool bGrid;
    if (mHierGrid.mGridsBegin != mHierGrid.mGridsEnd && gAppProperties->mpValues->mValue > 1)
        bGrid = true;
    else
        bGrid = false;
    out->clear();
    if (bGrid) {
        int n = mHierGrid.QueryShape(f, p, 0x400, items);
        for (int i = 0; i < n; ++i) {
            Node* item = items[i];
            if (!FilterModelShape(item, p, f, ctx)) {
                void* model = item ? (void*)(item + 1) : 0;
                out->push_back(model);
            }
        }
    } else {
        for (Node* it = mGroupList.next; it != &mGroupList; it = it->next) {
            if (!FilterModelShape(it, p, f, ctx)) {
                void* model = it ? (void*)(it + 1) : 0;
                out->push_back(model);
            }
        }
    }
    return out->mpBegin != out->mpEnd;
}

// @ 0x0074ed00
bool cModelWorld_s0074_e2b0::FindModelsInSphere(const void* sphere, ModelVec* out, void* ctx)
{
    Node* items[0x400];
    bool bGrid;
    if (mHierGrid.mGridsBegin != mHierGrid.mGridsEnd && gAppProperties->mpValues->mValue > 1)
        bGrid = true;
    else
        bGrid = false;
    out->clear();
    if (bGrid) {
        int n = mHierGrid.QuerySphere(sphere, (const char*)sphere + 0xc, 0x400, items);
        for (int i = 0; i < n; ++i) {
            Node* item = items[i];
            if (!FilterModelSphere(item, sphere, ctx)) {
                void* model = item ? (void*)(item + 1) : 0;
                out->push_back(model);
            }
        }
    } else {
        for (Node* it = mGroupList.next; it != &mGroupList; it = it->next) {
            if (!FilterModelSphere(it, sphere, ctx)) {
                void* model = it ? (void*)(it + 1) : 0;
                out->push_back(model);
            }
        }
    }
    return out->mpBegin != out->mpEnd;
}

// @ 0x0074ee80
bool cModelWorld_s0074_e2b0::FindModelsInBox(const void* frustum, ModelVec* out, void* ctx)
{
    Node* items[0x400];
    bool bGrid;
    if (mHierGrid.mGridsBegin != mHierGrid.mGridsEnd && gAppProperties->mpValues->mValue > 1)
        bGrid = true;
    else
        bGrid = false;
    out->clear();
    if (bGrid) {
        int n = mHierGrid.QueryFrustum(frustum, 0x400, items);
        for (int i = 0; i < n; ++i) {
            Node* item = items[i];
            if (!FilterModelFrustum(item, frustum, ctx)) {
                void* model = item ? (void*)(item + 1) : 0;
                out->push_back(model);
            }
        }
    } else {
        for (Node* it = mGroupList.next; it != &mGroupList; it = it->next) {
            if (!FilterModelFrustum(it, frustum, ctx)) {
                void* model = it ? (void*)(it + 1) : 0;
                out->push_back(model);
            }
        }
    }
    return out->mpBegin != out->mpEnd;
}

// @ 0x0074f010
EditorResource::~EditorResource()
{}

// @ 0x0074f0c0
bool EditorResource::Shutdown()
{
    mpOwner = 0;
    for (RBNodeBase* n = mListeners.mAnchor.mpNodeLeft; n != &mListeners.mAnchor; n = RBTreeIncrement(n))
        ((MapNode*)n)->mpValue->Notify();
    mListeners.clear();
    return true;
}

// @ 0x0074f1a0
bool VecIntAdd::add_unique(int x)
{
    IntVec& vec = v;
    int n = vec.size();
    for (int i = 0; i < n; ++i)
        if (vec[i] == x)
            return false;
    vec.push_back(x);
    return true;
}

// @ 0x0074f200
cFeedbackEvent*& CompactMapUU::Subscript(const uint32_t& key)
{
    RbNodeU* const pEnd = &mAnchor;
    RbNodeU* pCurrent = mAnchor.mpNodeParent;
    RbNodeU* pRangeEnd = pEnd;
    while (pCurrent) {
        if (!(pCurrent->mKey < key)) {
            pRangeEnd = pCurrent;
            pCurrent = pCurrent->mpNodeLeft;
        } else {
            pCurrent = pCurrent->mpNodeRight;
        }
    }
    RbIterU itLowerBound(pRangeEnd);
    if ((itLowerBound.mpNode == pEnd) || (key < itLowerBound.mpNode->mKey))
        itLowerBound = Insert(itLowerBound, PairUU(key, AutoRefFE()), TrueTag());
    return itLowerBound.mpNode->mValue;
}

// @ 0x0074f3a0
void quick_sort(cOccluder_s0074_f200* first, cOccluder_s0074_f200* last, OccluderCompare compare)
{
    if (first != last) {
        quick_sort_impl(first, last, 2 * Log2(last - first), compare);
        if ((last - first) > 28) {
            insertion_sort(first, first + 28, compare);
            insertion_sort_unguarded(first + 28, last, compare);
        } else {
            insertion_sort(first, last, compare);
        }
    }
}

// @ 0x0074f420
void VecElem1C::DoInsertValue(Elem1C* position, const Elem1C& value)
{
    if (mpEnd != mpCapacity) {
        const Elem1C* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) Elem1C(*(mpEnd - 1));
        ext_copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = nPrevSize ? 2 * nPrevSize : 1;
        Elem1C* const pNewData = nNewSize ? (Elem1C*)operator new(nNewSize * sizeof(Elem1C), "Graphics", 0, 0, kEastlAllocFile, 0xd1) : 0;
        Elem1C* pNewEnd = ext_copy_range(mpBegin, position, pNewData);
        ext_copy_range_tail(mpBegin, position, pNewData);
        ::new (pNewEnd) Elem1C(value);
        ++pNewEnd;
        pNewEnd = ext_copy_range(position, mpEnd, pNewEnd);
        ext_copy_range_tail(position, mpEnd, pNewEnd);
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNewData;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x0074f5d0
void VecModelInfo::DoInsertValues(ModelInfo* position, uint32_t n, const ModelInfo& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const ModelInfo temp = value;
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            if (n < nExtra) {
                ModelInfo* pDummy;
                ext_mi_copy_ex(&pDummy, mpEnd - n, mpEnd, mpEnd, mpEnd - n);
                ModelInfo* const pOldEnd = mpEnd;
                mpEnd += n;
                ext_mi_copy_backward(position, pOldEnd - n, pOldEnd);
                for (ModelInfo* p = position; p != position + n; ++p)
                    *p = temp;
            } else {
                ModelInfo* pDummy;
                ext_mi_fill_n(mpEnd, n - nExtra, &temp, n - nExtra);
                mpEnd += n - nExtra;
                ext_mi_copy_ex(&pDummy, position, mpEnd - (n - nExtra), mpEnd, (ModelInfo*)(n - nExtra));
                mpEnd += nExtra;
                for (ModelInfo* p = position; p != mpEnd - n; ++p)
                    *p = temp;
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = nPrevSize ? 2 * nPrevSize : 1;
        uint32_t nNewSize = nPrevSize + n;
        if (nGrowSize > nNewSize)
            nNewSize = nGrowSize;
        ModelInfo* const pNewData = nNewSize ? (ModelInfo*)operator new(nNewSize * sizeof(ModelInfo), "Graphics", 0, 0, kEastlAllocFile, 0xd1) : 0;
        ModelInfo* pNewEnd = ext_mi_copy(mpBegin, position, pNewData);
        ext_mi_fill_n(pNewEnd, n, &value, nNewSize);
        pNewEnd = ext_mi_copy(position, mpEnd, pNewEnd + n);
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x0074f800
void cModelWorld_s0074_f200::DrawLayer(bool bAlpha, DrawList* pList, uint32_t flags, void* pArg, Camera* pCamera)
{
    uint32_t tempGuard = 0;
    Float4 planes;
    pCamera->GetFrustumPlanes(&planes);

    Float4 color;
    color.x = 0.0f;
    color.y = 0.0f;
    color.z = 0.0f;
    color.w = 0.0f;
    uint32_t lastVariant = 0;
    int8_t lastSignCount = -1;
    Float4 cacheA;           // last value sent as constant 0x20c
    Float4 cacheB;           // last value sent as constant 0x22e
    uint8_t dirtyB = 0;
    uint8_t zeroByte;
    (void)tempGuard;
    (void)zeroByte;

    if (!bAlpha)
        mnDrawnOpaque = 0;
    else
        mnDrawnAlpha = 0;

    if (flags & 0x800) {
        SetBlendMode(bAlpha ? 0x60005 : 0x10002);
        g_renderStateDirty |= 0x40100;
        g_016f9244 = 8;
        g_016f921c = 0;
    }

    if (!(flags & 0x8000)) {
        AlphaSortCompare cmp;
        if (!bAlpha)
            SortDrawList(pList->mpBegin, pList->mpEnd, cmp);
        else
            SortDrawListOpaque(pList->mpBegin, pList->mpEnd, cmp);
    }

    const int nCount = (int)(pList->mpEnd - pList->mpBegin);
    for (int i = 0; i < nCount; ++i) {
        cDrawModelInfo_s0074_f200* pInfo = pList->mpBegin[i].pInfo;
        const float fDistance = pList->mpBegin[i].fDistance;

        ShaderRef* pShader;
        {
            ShaderRefPtr nullRef;
            const ShaderRefPtr& src = (pInfo->mLayerType < 4) ? pInfo->mShaders[pInfo->mLayerType] : nullRef;
            pShader = src.mp;
        }
        if (pInfo->mLayerType == 0 && ((pInfo->mFlags >> 13) & 1) && pInfo->mpAltShader)
            pShader = pInfo->mpAltShader;

        PushShaderDataNull();

        if ((pInfo->mFlags >> 3) & 1) {
            const uint8_t variant = VariantByte(pInfo);
            const bool bChanged = lastVariant != variant;
            lastVariant = variant;
            SetViewport((uint8_t*)&lastVariant);
            SetShaderConstant(0x202, &lastVariant, bChanged);
        }

        const uint32_t f = pInfo->mFlags;
        color.x = pInfo->mColor[0];
        color.y = pInfo->mColor[1];
        color.z = pInfo->mColor[2];
        color.w = pInfo->mColor[3];

        if ((f >> 2) & 1) {
            if ((f >> 11) & 1)
                color.w = 0.5f;
            else if ((f >> 10) & 1)
                color.w = 0.0f;
            else
                color.w = 1.0f;
            dirtyB = Differs(cacheB, color) ? 1 : 0;
            cacheB = color;
            SetShaderConstant(0x218, &zeroByte, false);
            SetShaderConstant(0x22e, &cacheB, dirtyB != 0);
            if (bAlpha) {
                Float4 one;
                one.x = 1.0f;
                one.y = 1.0f;
                one.z = 1.0f;
                one.w = pInfo->mColor[3];
                const bool bChanged = Differs(cacheA, one);
                cacheA = one;
                color = cacheA;
                SetShaderConstant(0x20c, &cacheA, bChanged);
            }
        } else if ((f >> 1) & 1) {
            const bool bChanged = Differs(cacheA, color);
            cacheA = color;
            color = cacheA;
            SetShaderConstant(0x20c, &cacheA, bChanged);
        }

        Float4 d;
        d.x = planes.x - fDistance;
        d.y = planes.y - fDistance;
        d.z = planes.z - fDistance;
        d.w = planes.w - fDistance;
        const int8_t nSigns = (int8_t)(SignBit(d.x) + SignBit(d.y) + SignBit(d.z) + SignBit(d.w));
        const bool bSignChanged = lastSignCount != nSigns;
        lastSignCount = nSigns;
        SetShaderConstant(0x237, &lastSignCount, bSignChanged);

        if (pInfo->mpExtra)
            SetShaderConstant(0x219, *pInfo->mpExtra, false);

        const int nDrawn = pShader->DrawBatch(pArg, pInfo->mDrawArg);
        PopShaderData();
        mnDrawnTotal += nDrawn;
        if (!bAlpha)
            ++mnDrawnOpaque;
        else
            ++mnDrawnAlpha;
    }
}

// @ 0x0074fd90
cFeedbackMgr::cFeedbackMgr()
{
    mn44 = 0;
    mn48 = 0;
    mn4c = 0;
    mn50 = 0;
    mn54 = 0;
}

// @ 0x0074fe10
int SlotAllocator::Allocate(uint32_t key, uint32_t unused)
{
    RbNodeU* pFound;
    mTree.find(&pFound, &key);
    if (pFound != (RbNodeU*)mAnchor)
        return (int)(uint32_t)pFound->mValue;
    const int nSlot = mnNextSlot;
    if (nSlot < 0x40) {
        (*(SlotIndexTree*)&mTree)[key] = nSlot;
        ++mnNextSlot;
        return nSlot;
    }
    return -1;
}

// @ 0x0074fea0
bool cFeedbackJobs::Start(void** pSource)
{
    if (*pSource == 0)
        return false;
    mTree28.ResetTree((uint32_t)*pSource);
    Assign(pSource);
    mbActive = 1;
    mnState = 6;
    mJobC.reset();
    JobLock lock(GetJobManager());
    {
        IJobManager* pMgr = GetJobManager();
        mJobA.reset();
        if (!pMgr->CreateJob(&mJobA))
            return false;
    }
    {
        IJobManager* pMgr = GetJobManager();
        mJobB.reset();
        if (!pMgr->CreateJob(&mJobB))
            return false;
    }
    mJobA.mp->mFlags = 0x80000000;
    mJobA.mp->SetCallback(JobCallback, this);
    mJobB.mp->SetDependency(mJobA.mp);
    mJobB.mp->Start();
    mbStarted = 1;
    mJobA.mp->Start();
    return true;
}

// @ 0x00750030
uint32_t SlotVectorOccluder::create(const cOccluderInfo& item)
{
    uint32_t nIndex = mFreeHead;
    if (nIndex != 0x3fffffff) {
        mFreeHead = mpBegin[nIndex].mFlags & 0x3fffffff;
        mpBegin[nIndex].mFlags &= 0x7fffffff;
        cOccluderInfo* pItem = &mpBegin[nIndex].mItem;
        if (pItem)
            ::new (pItem) cOccluderInfo(item);
    } else {
        const cOccluderInfo temp(item);
        nIndex = (uint32_t)(mpEnd - mpBegin);
        if (mpEnd < mpCapacity) {
            SlotEntry* pEnd = mpEnd;
            mpEnd = pEnd + 1;
            if (pEnd)
                pEnd->mFlags = 0x80000000;
        } else {
            SlotEntry entry;
            entry.mFlags = 0x80000000;
            DoInsertEntry(mpEnd, entry);
        }
        if (nIndex != 0)
            mpBegin[nIndex - 1].mFlags &= 0xbfffffff;
        {
            SlotEntry* e = mpBegin + nIndex;
            e->mFlags |= 0x40000000;
        }
        {
            SlotEntry* e = mpBegin + nIndex;
            e->mFlags &= 0x7fffffff;
        }
        cOccluderInfo* pItem = &mpBegin[nIndex].mItem;
        if (pItem)
            ::new (pItem) cOccluderInfo(temp);
    }
    if (mMinFree > nIndex)
        mMinFree = nIndex;
    return nIndex;
}

// @ 0x00750180
void helper_50180(void* self)
{ (void)self; }

// @ 0x00750310
void dtor_50310(void* self)
{ (void)self; }

// @ 0x007503a0
void dtor_503a0(void* self)
{ (void)self; }

// @ 0x007505a0
void preload_505a0(void* self)
{ (void)self; }

// @ 0x00750780
void MW6::AddOccluder(int* src, float f)
{
    uint32_t tmp[4];
    int idx = vec.create(tmp);
    char* base = (char*)vec.mBegin;
    int off = idx * 0x14;
    *(int*)(base + off + 4) = src[0];
    *(int*)(base + off + 8) = src[1];
    *(int*)(base + off + 0xc) = src[2];
    *(float*)((char*)vec.mBegin + off + 0x10) = f;
}

// @ 0x007507e0
namespace SP {
void cModelWorld_s0075_07e0::UpdateVisibility(uint32_t flags, cCamera* camera, int drawSet)
{
    cAppProperties* props = g_AppProperties;
    mDrawList.clear();
    mOpaqueDrawList.erase(mOpaqueDrawList.mpBegin, mOpaqueDrawList.mpEnd);
    mAlphaDrawList.erase(mAlphaDrawList.mpBegin, mAlphaDrawList.mpEnd);

    cSPTransform camXf;
    camXf.mFlags = 0;
    camXf.mFlags2 = 0;
    camXf.mOffset = g_ZeroVector;
    camXf.mScale = 1.0f;
    camXf.mRotation.Assign(g_IdentityMatrix);
    camera->GetTransform(&camXf);

    bool updateLOD = (flags >> 9) & 1;
    bool useOccluders = (flags >> 10) & 1;
    bool forceOpaque = (flags >> 16) & 1;
    Vec3_s0075_07e0 camPos = camXf.mOffset;
    int cullLevel = props->mpTuning->mCullLevel;
    float lodScale = mLODScale * props->mpTuning->mLODScale;
    uint32_t frame = g_FrameCounter;

    OccluderFixedVector occluders;
    if (cullLevel > 2 && useOccluders) {
        cOccluderSlot* first = mOccludersFirstUsed < 0x3fffffff ? mOccludersBegin + mOccludersFirstUsed
                                                                 : mOccludersEnd;
        int n = FUN_00745660(first, mOccludersEnd, frame);
        for (int i = 0; i < n; i++) {
            if ((uint32_t)i < (uint32_t)(mOccludersEnd - mOccludersBegin) &&
                !((mOccludersBegin[i].mFlags >> 31) & 1)) {
                const cOccluderSlot& e = mOccludersBegin[i];
                float dx = e.mCenter.x - camPos.x;
                float dy = e.mCenter.y - camPos.y;
                float dz = e.mCenter.z - camPos.z;
                float dist = sqrtf((dx * dx + dz * dz) + dy * dy);
                cOccluder occ;
                if (dist > e.mRadius) {
                    float inv = 1.0f / dist;
                    float s = inv * e.mRadius;
                    occ.mSinAngle = s;
                    occ.mCosAngle = sqrtf(1.0f - s * s);
                    occ.mDir.x = inv * dx;
                    occ.mDir.y = inv * dy;
                    occ.mDir.z = inv * dz;
                    if (!(s > 0.1f))
                        continue;
                } else {
                    occ.mSinAngle = 1.0f;
                    float inv = 1.0f / (dist + 1e-06f);
                    occ.mCosAngle = 0.0f;
                    occ.mDir.x = inv * dx;
                    occ.mDir.y = inv * dy;
                    occ.mDir.z = inv * dz;
                }
                float cx = camPos.x - e.mCenter.x;
                float cy = camPos.y - e.mCenter.y;
                float cz = camPos.z - e.mCenter.z;
                occ.mDistance = sqrtf((cx * cx + cz * cz) + cy * cy) * occ.mCosAngle;
                occluders.push_back(occ);
            }
        }
        quick_sort(occluders.mpBegin, occluders.mpEnd, OccluderLess);
    }

    cFrustumCull_s0075_07e0* cull = &mFrustumCuller;
    cull->Setup(camera->mFrustum);
    Property_s0075_07e0* prop;
    if (props->GetProperty(0x13d7382, prop) && prop->mType == 0xd)
        cull->FUN_006ffa80(prop->GetValueFloat());

    mNumDrawModels = 0;
    int count;
    if (mGridBegin != mGridEnd && cullLevel > 1) {
        mDrawList.resize(mGridModelCount);
        count = mHierGrid.FrustumQuery(cull, (int)(mDrawList.mpEnd - mDrawList.mpBegin), mDrawList.mpBegin);
    } else {
        for (cMWModelInternal_s0075_07e0* node = mModelListHead; node != (cMWModelInternal_s0075_07e0*)&mModelListHead;
             node = node->mpNext)
            mDrawList.push_back(node);
        count = (int)(mDrawList.mpEnd - mDrawList.mpBegin);
    }
    mNumDrawModels = count;
    mNumMeshesDrawn = 0;

    for (int i = 0; i < mNumDrawModels; i++) {
        cMWModelInternal_s0075_07e0* model = mDrawList.mpBegin[i];

        bool visible;
        if (!(model->mFlags & 1)) {
            visible = false;
        } else {
            const cDrawSetInfo_s0075_07e0& ds = mDrawSets[drawSet];
            if ((ds.mIncludeMask[1] | ds.mIncludeMask[0]) != 0 &&
                ((model->mGroupMask[0] & ds.mIncludeMask[0]) | (model->mGroupMask[1] & ds.mIncludeMask[1])) == 0)
                visible = false;
            else if ((model->mGroupMask[0] & ds.mExcludeMask[0]) != 0 ||
                     (model->mGroupMask[1] & ds.mExcludeMask[1]) != 0)
                visible = false;
            else
                visible = true;
        }

        Vec3_s0075_07e0 pos = model->mTransform.mOffset;
        float radius = model->mTransform.mScale * model->mBoundingRadius;
        if (cullLevel > 0) {
            if (visible && !(cull->TestSphere(&pos, radius) & 0x40))
                visible = true;
            else
                visible = false;
        }

        float dx = camPos.x - pos.x;
        float dy = camPos.y - pos.y;
        float dz = camPos.z - pos.z;
        float dist = sqrtf((dz * dz + dy * dy) + dx * dx);

        if (visible) {
            float horizon = mHorizonCullFactor;
            if (horizon != 0.0f && !((model->mFlags >> 4) & 1)) {
                // Horizon test: is the model hidden behind the planet?
                float p, q;
                if ((model->mFlags >> 5) & 1) {
                    float r = model->mHorizonRadius * model->mTransform.mScale;
                    const float* axis = &model->mTransform.mRotation.m[6];
                    p = (dz * axis[2] + dy * axis[1]) + dx * axis[0];
                    q = (dist * r) / sqrtf(r * r + horizon * horizon);
                } else {
                    float plen = sqrtf((pos.z * pos.z + pos.y * pos.y) + pos.x * pos.x);
                    float clen = sqrtf((camPos.z * camPos.z + camPos.y * camPos.y) + camPos.x * camPos.x);
                    float r2 = radius + radius;
                    if (clen < plen) {
                        float k = plen / clen;
                        float tz = camPos.z * k - pos.z;
                        float ty = camPos.y * k - pos.y;
                        float tx = camPos.x * k - pos.x;
                        p = (pos.z * tz + pos.y * ty) + pos.x * tx;
                    } else {
                        p = (pos.z * dz + pos.y * dy) + pos.x * dx;
                    }
                    q = ((r2 * plen) * dist) / sqrtf(r2 * r2 + horizon * horizon);
                }
                if (p < -q)
                    visible = false;
                else
                    visible = true;
            }

            if (visible && occluders.mpBegin != occluders.mpEnd) {
                // Occluder cones, sorted by decreasing angular size.
                float ratio = model->mBoundingRadius / dist;
                int n = (int)(occluders.mpEnd - occluders.mpBegin);
                for (int j = 0; j < n; j++) {
                    const cOccluder& o = occluders.mpBegin[j];
                    if (!(o.mSinAngle > ratio))
                        break;
                    if (dist > o.mDistance) {
                        float vy = pos.y - camPos.y;
                        float vx = pos.x - camPos.x;
                        float vz = pos.z - camPos.z;
                        float proj = (o.mDir.z * vz + o.mDir.y * vy) + o.mDir.x * vx;
                        float t = proj * o.mSinAngle - radius;
                        if (!(0.0f > t)) {
                            float perp = (((vx * vx + vz * vz) + vy * vy) - proj * proj) * o.mCosAngle * o.mCosAngle;
                            if (t * t >= perp) {
                                visible = false;
                                break;
                            }
                        }
                    }
                }
            }
        }

        float lodDist = dist * lodScale;
        if (updateLOD)
            model->mLODDistance = lodDist;
        if (!visible)
            continue;

        if (updateLOD) {
            float* thresholds = model->mpLODThresholds;
            model->mLastVisibleFrame = frame;
            if (thresholds) {
                float d = lodDist / model->mTransform.mScale;
                while (model->mLOD > 0 && thresholds[model->mLOD - 1] > d)
                    model->mLOD--;
                while (model->mLOD < model->mNumLODs && d > thresholds[model->mLOD])
                    model->mLOD++;
            }
        }

        cMWMesh* mesh = (model->mLOD < 4 ? model->mLODs[model->mLOD] : AutoRefCount<cMWMesh>()).get();
        if (model->mLOD == 0 && ((model->mFlags >> 13) & 1) && model->mpLowLODMesh)
            mesh = model->mpLowLODMesh;
        if (!mesh)
            continue;

        if (model->mExtraTransform.mScale != 1.0f || (model->mExtraTransform.mFlags & 6)) {
            cSPTransform xf = model->mTransform;
            xf.Accumulate(&model->mExtraTransform);
            mesh->mTransform = xf;
        } else {
            mesh->mTransform = model->mTransform;
        }

        cDrawModelInfo_s0075_07e0 info;
        info.mpModel = model;
        info.mDistance = dist;
        if (forceOpaque) {
            mOpaqueDrawList.push_back(info);
        } else if ((model->mFlags & g_AlphaFadeFlags) && 1.0f > model->mAlpha) {
            if (model->mAlpha > props->mpTuning->mAlphaThreshold)
                mAlphaDrawList.push_back(info);
        } else if (!(mesh->mDrawFlags & 1) && !((model->mFlags >> 12) & 1)) {
            mOpaqueDrawList.push_back(info);
        } else {
            mAlphaDrawList.push_back(info);
        }
    }
}
}  // namespace SP

// @ 0x00751560
namespace SP {
void cModelWorld_FinishBackgroundLoad(void* self)
{
  (void)self;
}
}  // namespace SP

// @ 0x00751b30
namespace SP {
void cModelWorld_UpdateHighlightProps(void* self)
{ (void)self; }
}  // namespace SP

// @ 0x00751d00
namespace SP {
void MWGroupDtorStub::F()
{
  cMWGroupInternal_s0075_1560* self = (cMWGroupInternal_s0075_1560*)this;
  int bytes = (int)((char*)self->mGroup.mObjectsEnd - (char*)self->mGroup.mObjectsBegin);
  int count = bytes / 0x3c;
  for (int i = 0; i < count; ++i) {
    cMWObject_s0075_1560* o = self->mGroup.mObjectsBegin[i].mObject;
    if (o) {
      if (o->mRefCount < 2) {
        typedef void(__thiscall *ReleaseFn)(void*, int);
        void** vtbl = *(void***)o;
        ((ReleaseFn)vtbl[0x170 / 4])(o, (o->mFlags >> 31) & 1);
      } else {
        o->mRefCount = o->mRefCount - 1;
      }
    }
  }
  self->mGroup.mObjectsEnd = self->mGroup.mObjectsBegin;
}
}  // namespace SP

// @ 0x00751de0
namespace SP {
void FUN_00751de0(void* self)
{ (void)self; }
}  // namespace SP

// @ 0x00751ed0
namespace SP {
void FUN_00751ed0(void* self)
{ (void)self; }
}  // namespace SP

// @ 0x00751ff0
namespace SP {
void cModelWorld_Init(void* self)
{ (void)self; }
}  // namespace SP

// @ 0x007520e0
namespace SP {
void cModelWorld_Shutdown(void* self)
{ (void)self; }
}  // namespace SP

// @ 0x007523a0
namespace SP {
void cEffectsRenderer_RenderMainEffectsLayer(void* self)
{ (void)self; }
}  // namespace SP

// @ 0x00753540
void TreeWalker_00753540::ForEach(float a, float b)
{
  void* n = mRoot;
  void* end = (char*)this + 0x10;
  while (n != end) {
    ((NodeRunThunk*)((TreeNode_00753540*)n)->mObject)->Run(a, b);
    n = RBTreeIncrement(n);
  }
}

// @ 0x00753630
void FUN_00753630(void* self, int* p)
{ (void)self; (void)p; }

// @ 0x00753770
void* FUN_00753770(void* self, void* a, void* b)
{ (void)a; (void)b; return self; }

// @ 0x00753810
void* FUN_00753810(void* self, void* a, int n, void* src)
{ (void)a; (void)n; (void)src; return self; }

// @ 0x00753880
void cLoadQueue_ctor_00753880(void* self)
{ (void)self; }

// @ 0x00753bb0
void* FUN_00753bb0(void* self, void* a, void* b)
{ (void)a; (void)b; return 0; }

// @ 0x00753c50
void cModelWorld_FinalRelease_00753c50(void* self)
{ (void)self; }

// @ 0x00753d10
void* FUN_00753d10(void* self, void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; return 0; }
