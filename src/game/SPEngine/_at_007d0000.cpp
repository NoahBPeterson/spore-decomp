// src/game/SPEngine/_at_007d0000.cpp -- migrated from slice(s) s007df780, s007db1b0, s007da2d0, s007d76d0, s007d67e0, s007d56f0, s007d3930, s007d03f0, s007cf310 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_007d0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/Swarm/cEffectParams.h"
#include "SP/cGameModelDescription.h"
#include "EA/Swarm/cTransform.h"
#include <intrin.h>
#include <math.h>
#include <string.h>
#include "EA/Stopwatch.h"
#include "EA/Random/RandomLinearCongruential.h"
#include <stdio.h>
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- items of slice s007cf310 begin (TODO(rewrite): local stubs, replace by canonical classes)
void WriteUint16(void*, const uint16_t&, int, int);   // 0x0093a9d0
void WriteUint32(void*, const uint32_t&, int, int);   // 0x0093aa70
void WriteFloat32(void*, const float&, int, int);     // 0x0093aa70
void WriteByte(void*, const uint8_t&, int);           // 0x0093a9a0  (operator<<)
struct IStream {
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
virtual void s12();
virtual void s13();
    virtual void Write(void*, int);   // slot 14 (0x38)
};
// ---- items of slice s007cf310 end

// ---- items of slice s007d03f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl RBTreeIncrement(void* node);                                // 0x00921580
extern "C" void  __cdecl FUN_0053bd00(void*, void*);
void* __cdecl EAlloc(uint32_t, const char*, int, int, const char*, int);   // 0x00f473a0
void WU16(void*, const void*, int, int);   // 0x0093a9d0
void WU32(void*, const void*, int, int);   // 0x0093aa70
void WB(void*, const void*, int);          // 0x0093a9a0
void Ser360(void* stream, char* p);   // 0x007d0360
void* Ser2B0(void*, int*);            // 0x007d02b0
struct CloneTreeOwner { void* CloneTree(int* src, void* parent); };
bool RI32(void* stream, void* dst, int count, int flag);   // 0x0093a780
struct RBTreeFind {
    void* DoInsert(void* out, const int* key, int value);  // 0x007d0850 (ret 0xc)
};
// ---- items of slice s007d03f0 end

// ---- items of slice s007d3930 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Random {
class RandomLinearCongruential_s007d_3930 { public: double RandomDoubleUniform(); };
}
}
extern EA::Random::RandomLinearCongruential_s007d_3930 gRandom;   // 0x16778dc
// ---- items of slice s007d3930 end

// ---- items of slice s007d56f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_vecInit[3];                      // 0x16371dc
extern const float g_vecInitB[3];                     // 0x1637118
extern const float g_one;                             // 0x1485720
void* operator new[](size_t size);
void  operator delete[](void* p) throw();                // 0xf47380
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void  operator delete(void* p) throw();                  // 0xf47380 (same EA allocator free)
inline void* operator new(size_t, void* p) throw() { return p; }
#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct Matrix33 {
    float m[9];
    void Assign(const Matrix33* src) throw();         // 0x41cb40 (Matrix3::Assign)
    Matrix33(const Matrix33& o);                      // same routine, used for by-value copies
    Matrix33() {}
};
extern const Matrix33 g_matIdentityA;                 // 0x1637360 (effect-component rotation)
extern const Matrix33 g_matIdentityB;                 // 0x163725c (split-manager rotation)
struct cTransform {                                   // size 0x38
    uint16_t mFlags;                                  // +0
    uint16_t mModificationCount;                      // +2
    float mTranslation[3];                            // +4
    float mScale;                                     // +0x10
    Matrix33 mRotation;                               // +0x14
    cTransform() {}
    cTransform& operator=(const cTransform& o);       // 0x537dc0
    void Concat(const cTransform& o);                 // 0x537f40
};
struct GmeRefCount {                                       // RefCountTemplate<int>: vptr + count
    GmeRefCount() : mnRefCount(0) {}
    virtual ~GmeRefCount() {}                              // slot 0: scalar deleting dtor
    int mnRefCount;                                   // +4
};
inline void ReleaseRef(GmeRefCount* p) {                   // inline RefCountTemplate::Release
    volatile int* r = &p->mnRefCount;
    int n = *r + -1;
    *r = n;
    if (n == 0) { p->mnRefCount = 1; delete p; }
}
template<class T> struct AutoRef {
    T* mpObject;
    ~AutoRef() { if (mpObject) ReleaseRef(mpObject); }
};
struct cIModelWorld {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
    virtual bool QueryModels(const float* pos, float radius, void* outVec, void* filter);   // +0x38
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
virtual void w30();
virtual void w31();
virtual void w32();
virtual void w33();
virtual void w34();
virtual void w35();
virtual void w36();
virtual void w37();
virtual void w38();
virtual void w39();
virtual void w40();
virtual void w41();
virtual void w42();
virtual void w43();
virtual void w44();
virtual void w45();
virtual void w46();
virtual void w47();
virtual void w48();
virtual void w49();
virtual void w50();
virtual void w51();
virtual void w52();
virtual void w53();
virtual void w54();
virtual void w55();
virtual void w56();
virtual void w57();
virtual void w58();
virtual void w59();
virtual void w60();
virtual void w61();
virtual void w62();
virtual void w63();
virtual void w64();
virtual void w65();
virtual void w66();
virtual void w67();
virtual void w68();
virtual void w69();
virtual void w70();
virtual void w71();
virtual void w72();
virtual void w73();
virtual void w74();
virtual void w75();
virtual void w76();
virtual void w77();
virtual void w78();
virtual void w79();
virtual void w80();
virtual void w81();
virtual void w82();
virtual void w83();
virtual void w84();
virtual void w85();
virtual void w86();
virtual void w87();
virtual void w88();
virtual void w89();
virtual void w90();
    virtual void ReleaseModel(struct cMWModel* m, int flag);                                // +0x16c
    virtual void DestroyModel(struct cMWModel* m, unsigned char flag);                                // +0x170
};
struct ResKey { unsigned instanceID, typeID, groupID; };
struct cPropertyList { int f0, f4; ResKey mKey; };                                  // key at +8,+0xc,+0x10
struct cMWModel {                                     // retail layout (see 0x90 property list)
    cIModelWorld* mpWorld;                            // +0
    unsigned mFlags;                                  // +4
    cTransform mXform;                                // +8
    int mnRefCount;                                   // +0x40
    char pad[0x90 - 0x44];
    cPropertyList* mPropertyList;                     // +0x90
};
inline void ReleaseModel(cMWModel* m) {
    int n = m->mnRefCount;
    if (n > 1) { m->mnRefCount = n - 1; }
    else { m->mpWorld->DestroyModel(m, (unsigned char)((m->mFlags >> 31) & 1)); }
}
struct AutoModelRef {
    cMWModel* mpObject;
    ~AutoModelRef() { if (mpObject) ReleaseModel(mpObject); }
    void Assign(cMWModel* m);                         // 0x478db0
};
struct GmeIComponent {                                   // EA::Swarm::cIComponent
    virtual void Initialize(void* world, void* manager, void* params);   // +0x00
    virtual void Dispose();                                              // +0x04
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
    virtual void SetTransforms(const cTransform& source, const cTransform& rigid);  // +0x18
virtual void w7();
virtual void w8();
virtual void w9();
virtual void w10();
virtual void w11();
virtual void w12();
    virtual void AddRef();                                               // +0x34
    virtual void Release();                                              // +0x38
    ~GmeIComponent() {}
};
struct cEffectParams {
    void* vtbl; char pad[0xcc];
    ~cEffectParams();                                 // 0x7d4ae0
};
struct cSplitController {                             // size 0x40
    cTransform mLocalXform;                           // +0
    cEffectParams* mParams;                           // +0x38
    GmeIComponent* mComponent;                           // +0x3c (AutoRefCount<cIComponent>)
    cSplitController(const cSplitController& o);      // 0x7d5300
    cSplitController& operator=(const cSplitController& o) {
        mLocalXform = o.mLocalXform;
        mParams = o.mParams;
        GmeIComponent* nc = o.mComponent;
        GmeIComponent* oc = mComponent;
        if (nc != oc) {
            if (nc) nc->AddRef();
            mComponent = nc;
            if (oc) oc->Release();
        }
        return *this;
    }
    ~cSplitController() { GmeIComponent* c = mComponent; if (c) c->Release(); }
};
struct CtrlVecBase {                                  // eastl::VectorBase<cSplitController, sp_vector_allocator>
    cSplitController* mpBegin;
    cSplitController* mpEnd;
    cSplitController* mpCapacity;
    int mAlloc;
    ~CtrlVecBase() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin); }
};
struct CtrlVec : CtrlVecBase {                        // eastl::vector<cSplitController, sp_vector_allocator>
    ~CtrlVec();
    void DoInsertValue(cSplitController* position, const cSplitController& value);
};
inline void CtrlDestroyValues(cSplitController* first, cSplitController* last) {
    for (; first < last; ++first) first->~cSplitController();
}
struct cAnimationInfo { float mAge, mInvLength, mCurveMultiplier; };   // size 0xc
struct AnimIter {                                     // eastl::generic_iterator<cAnimationInfo*> (non-POD: returned via hidden pointer)
    cAnimationInfo* mpNode;
    AnimIter(cAnimationInfo* p) : mpNode(p) {}
};
struct AnimFalseType {};                              // eastl::integral_constant<bool, false>
AnimIter __cdecl AnimUninitCopyIter(AnimIter first, AnimIter last, AnimIter dest, AnimFalseType);   // 0x898b80
inline AnimIter AnimUninitCopyWrap(cAnimationInfo* first, cAnimationInfo* last, cAnimationInfo* dest) {   // eastl::uninitialized_copy
    const AnimIter f(first), l(last), d(dest);
    return AnimUninitCopyIter(f, l, d, AnimFalseType());
}
cAnimationInfo* __cdecl AnimUninitCopy(cAnimationInfo* first, cAnimationInfo* last, cAnimationInfo* dest);   // 0xa11310
void __cdecl AnimCopyBackward(cAnimationInfo* first, cAnimationInfo* last, cAnimationInfo* destEnd);          // 0xabced0
void __cdecl AnimFill(cAnimationInfo* first, cAnimationInfo* last, const cAnimationInfo* v);                  // 0xa177f0
void __cdecl AnimUninitFillN(cAnimationInfo* dest, unsigned n, const cAnimationInfo* v);                      // 0x6e5760
struct AnimVec {                                      // eastl::vector<cAnimationInfo, sp_vector_allocator>
    cAnimationInfo* mpBegin;
    cAnimationInfo* mpEnd;
    cAnimationInfo* mpCapacity;
    void DoInsertValues(cAnimationInfo* position, unsigned n, const cAnimationInfo* value);
};
struct cSplitInstance {                               // SP::cSplitManager::cSplitInstance, size 0x74
    cSplitInstance(const void* src);                  // 0x799450
};
struct Elem78 {                                       // cSplitInstanceList::cElement, size 0x78
    uint32_t mNextFree;                               // +0
    uint8_t  mFlags;                                  // +4 (cSplitInstance)
    char pad[3];
    cTransform mInstanceTransform;                    // +8
    cTransform mFinalTransform;                       // +0x40
};
struct SplitListVec {                                 // eastl::vector<cSplitInstanceList>
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void DestroyRange(char* first, char* last) throw();  // 0x7d5360
    __forceinline ~SplitListVec() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
    }
};
struct cSplitManager : GmeRefCount {
    cTransform mComponentTransform;                   // +0x8
    SplitListVec mSplitClientList;                    // +0x40
    cSplitManager();
    // 0x7d62d0 = scalar deleting destructor (compiler-generated destructor)
    void SetComponentTransform(const cTransform& t);  // 0x7d4980
};
struct AnimVec5 {                                     // eastl::vector<cAnimationInfo> (+ allocator words)
    cAnimationInfo* mpBegin; cAnimationInfo* mpEnd; cAnimationInfo* mpCapacity; int mAlloc, mAlloc2;
    ~AnimVec5() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin); }
};
struct CtrlVec5 : CtrlVec { int mAlloc2; };
struct cIModelManager;
struct cGameModelEffect : GmeIComponent, GmeRefCount {
    void* mDesc;                                      // +0x0c
    int mPackageID;                                   // +0x10
    bool mActive, mIsVisible, mIsLoaded;              // +0x14..0x16
    unsigned mGameModelInstanceID;                    // +0x18
    unsigned mGameModelGroupID;                       // +0x1c
    float mGameModelColor[3];                         // +0x20
    float mGameModelAlpha;                            // +0x2c
    float mGameModelScale;                            // +0x30
    float mIntersectionRadius;                        // +0x34
    AutoModelRef mGameModel;                          // +0x38
    cTransform mComponentXform;                       // +0x3c
    float mLastLocation[3];                           // +0x74
    float mLODSizeScale[2];                           // +0x80
    float mLODAlphaScale[2];                          // +0x88
    AnimVec5 mAnimationInfo;                          // +0x90
    AutoRef<GmeRefCount> mModelSplitter;                   // +0xa4
    AutoRef<cSplitManager> mSplitManager;             // +0xa8
    CtrlVec5 mSplitControllers;                       // +0xac
    cIModelManager* mModelManager;                    // +0xc0
    cIModelWorld* mGameModelWorld;                    // +0xc4

    cGameModelEffect(void* desc, int packageID);
    ~cGameModelEffect();
    virtual void SetTransforms(const cTransform& source, const cTransform& rigid);
    void Unload();
    void FindGameModel();
};
struct ModelQueryFilter { int a[5]; char b0, b1; };
struct ModelPtrVec {                                  // eastl::fixed_vector<cMWModel*, 17>
    cMWModel** mpBegin; cMWModel** mpEnd; cMWModel** mpCapacity; cMWModel** mpBuffer;
    cMWModel* mBuffer[17];
    ModelPtrVec() { mpBegin = mBuffer; mpEnd = mBuffer; mpBuffer = mBuffer; mpCapacity = mBuffer + 17; }
    ~ModelPtrVec() { if (mpBegin && mpBegin != mBuffer) operator delete[](mpBegin); }
};
char** UninitCopyElem78(char** out, char* first, char* last, char* base, const void* extra);  // 0x7d5aa0
struct RBNodeBase { RBNodeBase* mpNodeRight; RBNodeBase* mpNodeLeft; RBNodeBase* mpNodeParent; int mColor; };
struct RbMap {                                        // eastl::map copy-constructed from another map
    int pad0;
    RBNodeBase mAnchor;                               // +4
    unsigned mnSize;                                  // +0x14
    int mAllocator;                                   // +0x18
    RbMap(const RbMap& x);                            // 0x7d0ac0
    ~RbMap() { DoNuke(mAnchor.mpNodeParent); }
    void DoNuke(RBNodeBase* root);                    // 0x9a9600
};
struct cMapResABase : GmeRefCount {
    int mType;                                        // +8
    cMapResABase() : mType(4) {}
};
struct cMapResA : cMapResABase, RbMap {               // 0x7d6380 ctor / 0x7d63e0 scalar deleting dtor (map at +0xc)
    cMapResA(const RbMap& m) : RbMap(m) {}
};
struct GmeEditorResBase { virtual ~GmeEditorResBase() {} };
struct cMapResB : GmeEditorResBase, GmeRefCount {                  // 0x7d6440 ctor / 0x7d6500 dtor (map at +0x0c)
    RbMap mMap;                                       // +0x0c
    float mVec[3];                                    // +0x28
    AutoRef<GmeRefCount> mpRef;                            // +0x34
    cMapResB(const RbMap& m, const float* v, GmeRefCount* r);
};
// ---- items of slice s007d56f0 end

// ---- items of slice s007d67e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int size_type;
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define ALLOC_NAME "App"
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
void ea_free(void* p);                                   // 0x00f47380
struct cElement;
cElement* AllocElementArray(size_type n, cElement* first, cElement* last);          // 0x007d61f0
cElement* AssignElements(cElement* first, cElement* last, cElement* dest);           // 0x007d6250 (src, srcEnd, dest)
cElement** UninitCopyElements(cElement** out, cElement* first, cElement* last, cElement* dest); // 0x007d5aa0 (*out = dest, *out advances)
void      DestroyElementRange(cElement* first, cElement* last);                     // 0x007d4940
void      ResizeFloatVector(void* vec, int n);                                      // 0x007d65a0
void      Sub_7d5e60(void* self);                                                   // 0x007d5e60
void      Sub_478db0(int value);                                                    // 0x00478db0
int       Sub_79ac10(int a, int b, int c);                                          // 0x0079ac10
void*     RandomLCG_Swarm();                                                        // returns &sRandom
double    RandomDoubleUniform(void* rng);                                           // 0x009360d0
struct cSPVector3_s007d_67e0 { float x, y, z; };
struct cSPMatrix3_s007d_67e0 { float m[9]; };
struct cSPTransform_s007d_67e0 {                    // size 0x38
    unsigned short mFlags;               // +0x00
    unsigned short mModificationCount;   // +0x02
    cSPVector3_s007d_67e0     mTranslation;         // +0x04
    float          mScale;               // +0x10
    cSPMatrix3_s007d_67e0     mRotation;            // +0x14
};
struct cSplitInstance_s007d_67e0 {                  // size 0x74
    unsigned char mFlags;                // +0x00
    char _pad[3];
    cSPTransform_s007d_67e0  mInstanceTransform;    // +0x04
    cSPTransform_s007d_67e0  mFinalTransform;       // +0x3c
    cSplitInstance_s007d_67e0(int a, const cSPTransform_s007d_67e0& x, int b);   // @ 0x007d4a40 (defined in slice s007d4a40)
};
struct cElement {                        // size 0x78
    int           mNextFree;             // +0x00
    cSplitInstance_s007d_67e0 mData;                // +0x04
};
struct CElementVector {
    cElement* mpBegin;    // +0x00
    cElement* mpEnd;      // +0x04
    cElement* mpCapacity; // +0x08
    CElementVector& operator=(const CElementVector& x);   // @ 0x007d7080
};
struct cSplitInstanceList {
    int             mNextFree;      // +0x00
    CElementVector  mDataArray;     // +0x04
    int             mUnk10;         // +0x10
    int             mUnk14;         // +0x14
    int             mExtra;         // +0x18

    cSplitInstanceList()
        : mNextFree(-1), mUnk10(0), mUnk14(0), mExtra(0)
    { mDataArray.mpBegin = 0; mDataArray.mpEnd = 0; mDataArray.mpCapacity = 0; }

    __forceinline cSplitInstanceList(const cSplitInstanceList& x);  // inline deep copy
    int insert(const cSplitInstance_s007d_67e0& value);              // @ 0x0079ff40 (defined in slice s007d4a40)
    ~cSplitInstanceList();                                // inline element teardown
};
__forceinline cSplitInstanceList::cSplitInstanceList(const cSplitInstanceList& x) {
    mNextFree = x.mNextFree;
    const size_type nBytes = (size_type)((char*)x.mDataArray.mpEnd - (char*)x.mDataArray.mpBegin);
    const size_type nCount = nBytes / sizeof(cElement);
    cElement* buf = nCount
        ? (cElement*)operator new[](nCount * sizeof(cElement), ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1)
        : 0;
    mDataArray.mpBegin = buf;
    mDataArray.mpEnd = buf;
    mDataArray.mpCapacity = buf + nCount;
    cElement* cur = buf;
    UninitCopyElements(&cur, x.mDataArray.mpBegin, x.mDataArray.mpEnd, buf);
    mDataArray.mpEnd = cur;
    mExtra = x.mExtra;
}
inline cSplitInstanceList::~cSplitInstanceList() {
    if (mDataArray.mpBegin != 0) {
        DestroyElementRange(mDataArray.mpBegin, mDataArray.mpEnd);
        if (((int*)mDataArray.mpBegin)[-1] != 0)
            ea_free(mDataArray.mpBegin);
    }
}
struct ListVector {
    cSplitInstanceList* mpBegin;
    cSplitInstanceList* mpEnd;
    cSplitInstanceList* mpCapacity;
    void DoInsertValues(cSplitInstanceList* position, size_type n, const cSplitInstanceList& value); // @ 0x007d72e0
    void resize(size_type n);                                                                         // @ 0x007d7560
    void erase(cSplitInstanceList* first, cSplitInstanceList* last);                                  // @ 0x007d7280 (ecx=this)
};
struct cParamRec { unsigned short mOffset; unsigned short mCount; };
struct IUnknown32 { void** vftable; };
struct AutoRefCountIUnknown {
    IUnknown32* mpObject;
    AutoRefCountIUnknown& operator=(const AutoRefCountIUnknown& x) {
        if (mpObject != x.mpObject) {
            if (x.mpObject != 0)
                ((void(__thiscall*)(IUnknown32*))x.mpObject->vftable[0])(x.mpObject);
            IUnknown32* pOld = mpObject;
            mpObject = x.mpObject;
            if (pOld != 0)
                ((void(__thiscall*)(IUnknown32*))pOld->vftable[1])(pOld);
        }
        return *this;
    }
};
struct FloatVec { float* mpBegin; float* mpEnd; float* mpCapacity; int mAlloc; FloatVec& operator=(const FloatVec&); };  // 0x0050d4e0
struct IntVec   { int*   mpBegin; int*   mpEnd; int*   mpCapacity; int mAlloc; IntVec& operator=(const IntVec&); };  // 0x0050d4e0
struct cEffectParams_s007d_67e0 {                    // retail size 0xd8 (dev PDB 0xcc)
    cParamRec mFloatParams[25];           // +0x00
    FloatVec  mFloatParamStorage;         // +0x64
    char      mPad74[4];                  // +0x74
    cParamRec mIntParams[9];              // +0x78
    int       mUnk9c;                     // +0x9c
    IntVec    mIntParamStorage;           // +0xa0
    char      mPadB0[4];                  // +0xb0
    AutoRefCountIUnknown mUnknownParams[9]; // +0xb4
    cEffectParams_s007d_67e0& operator=(const cEffectParams_s007d_67e0& x);
};
struct cSwarmParams {
    char     pad00[0x0c];
    unsigned mFlags;          // +0x0c
    char     pad10[0x20];
    int*     mV30;            // +0x30
    int*     mV34;            // +0x34
    char     pad38[0x34];
    int*     mV6c;            // +0x6c
    int*     mV70;            // +0x70
    char     pad74[0x0c];
    unsigned mFlags80;        // +0x80
    unsigned char mByte84;    // +0x84
};
struct cSwarmThis {
    void**   vftable;         // +0x00
    char     pad04[0x08];
    cSwarmParams* mParams;    // +0x0c
    char     pad10[0x04];
    unsigned char mFlag14;    // +0x14
    unsigned char mFlag15;    // +0x15
    unsigned char mFlag16;    // +0x16
    char     pad17;
    int      mArg18;          // +0x18
    int      mArg1c;          // +0x1c
    char     pad20[0x10];
    float    mFloat30;        // +0x30
    char     pad34[0x04];
    void*    mRec;            // +0x38
    unsigned short mCount3e;  // +0x3e
    float    mF40;            // +0x40
    float    mF44;            // +0x44
    float    mF48;            // +0x48
    float    mF4c;            // +0x4c
    char     pad50[0x40];
    void*    mFloatVec;       // +0x90
    char     pad94[0x10];
    int*     mA4;             // +0xa4
    int*     mA8;             // +0xa8
    char*    mB0;             // +0xac  (begin of 0x40-byte records)
    char*    mB4;             // +0xb0
    char     padB4[0x0c];
    IUnknown32* mC0;          // +0xc0
    IUnknown32* mC4;          // +0xc4

    void Sub_7d6c10(int arg);
};
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s007d67e0 end

// ---- items of slice s007d76d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct TransformHelper {
    void __thiscall Sub_537f40(void* xform);              // 0x00537f40  cTransform::PreTransformBy
};
struct Matrix3Helper {
    void __thiscall Matrix3_Assign(const void* src);      // 0x0041cb40  cSPMatrix3::Assign
};
void* Sub_67de00();                        // 0x0067de00
struct AbilityDesc {
    char           pad00[0x0c];
    unsigned char  mKind;      // +0x0c
    char           pad0d[3];
    char           pad10[8];
    float*         mPosition;  // +0x18
    char           pad1c[0x10];
    float*         mRadius;    // +0x2c
    char           pad30[0x10];
    float*         mScale;     // +0x40
};
struct Vec3f { float x, y, z; };
struct Mat3f { float m[9]; };
struct TransformTemp {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    Vec3f          mTranslation;        // +0x04
    float          mScale;              // +0x10
    Mat3f          mRotation;           // +0x14
};
struct cAbilityCmd {
    void** mBaseVtbl;     // +0x00
    void** mAbilityVtbl;  // +0x04
    int    mUnk08;        // +0x08
    void*  mDesc;         // +0x0c
    void*  mIface;        // +0x10
    unsigned char mActive;// +0x14
    char   pad15[3];
    float  mx, my, mz;    // +0x18,+0x1c,+0x20
    int    mId;           // +0x24

    void Destroy();
    void SetIface(int, int, int);
    void Activate(int);
    void Deactivate(int);
    void SetTransform(void* xformA, const TransformTemp* desc);
};
// ---- items of slice s007d76d0 end

// ---- items of slice s007da2d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __int64 __rdtsc(void);   // 0x00f47582 (crt lib_)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
extern char gEmptyString[];                  // 0x01667bac
extern void* vtbl_MsgBase[];                // 0x013eb90c
extern void* vtbl_MsgDerived[];             // 0x01452a38
#pragma intrinsic(expf, fabsf)
#pragma intrinsic(__rdtsc)
#pragma intrinsic(_InterlockedExchange)
typedef void* HMODULE;
typedef const char* LPCSTR;
typedef int BOOL;
typedef void* FARPROC;
struct RandomLinearCongruential {
    void SetSeed(int);                       // 0x00936090
    uint32_t RandomUint32Uniform();          // 0x009360b0
};
extern RandomLinearCongruential g_sRandom;   // 0x016778dc (EA::Swarm::sRandom)
void* SP_ConfigManager();                    // 0x0067dd30
struct IConfigManager {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual void v11(int, int);
};
struct ManifestSource {
    char pad[8];
    void* (*mNext)();      // +0x8
    void Load();
};
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
extern "C" __declspec(dllimport) BOOL    __stdcall FreeLibrary(HMODULE);
void* __cdecl OpNewPlugin(void*, int, int);      // 0x011e073e
void  __cdecl VecDoInsertPlugin(void*, void*, int);  // 0x011e0744
struct PluginManager {
    char pad[0x2c];
    HMODULE mModule;        // +0x2c
    bool Load(const char* name, int param);
};
bool PluginManager::Load(const char* name, int param)
{
    if (mModule) {
        FreeLibrary(mModule);
        mModule = 0;
        OpNewPlugin(this, 0, 0x2c);
    }
    mModule = LoadLibraryA(name);
    if (mModule) {
        OpNewPlugin(this, 0, 0x2c);
        FARPROC fn = GetProcAddress(mModule, "oaPluginInit");
        if (fn) {
            int result;
            int ret = ((int(__cdecl*)(int, int*, int, int, int, int))fn)
                          (param, &result, 0, 2, 0, 6);
            if (ret && result == 0) {
                int value = *(int*)ret;
                if (value >= 0x2c)
                    value = 0x2c;
                VecDoInsertPlugin(this, (void*)ret, value);
                return true;
            }
        }
    }
    if (mModule) {
        FreeLibrary(mModule);
        mModule = 0;
        OpNewPlugin(this, 0, 0x2c);
    }
    return false;
}
namespace eastl {
class allocator_s007d_a2d0 { public:
    void deallocate(void* p, unsigned int) { delete[] (char*)p; }
};
}
namespace eastl {
struct basic_string_s007d_a2d0 {
    char* mpBegin;                           // +0x00
    char* mpEnd;                             // +0x04
    char* mpCapacity;                        // +0x08
    allocator_s007d_a2d0 mAllocator;                    // +0x0c (empty)
    basic_string_s007d_a2d0() : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(); }
    ~basic_string_s007d_a2d0() { DeallocateSelf(); }
    void AllocateSelf() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(char* p, unsigned int n) { if (p) mAllocator.deallocate(p, n); }
    const char* c_str() const { return mpBegin; }
    basic_string_s007d_a2d0& sprintf(const char* pFormat, ...);   // 0x00472fe0
};
}
struct EA_Stopwatch {
    uint64_t mnStartTime;                          // +0x00
    uint64_t mnTotalElapsedTime;                   // +0x08
    int      mnUnits;                              // +0x10
    float    mfStopwatchCyclesToUnitsCoefficient;  // +0x14

    EA_Stopwatch(int units, bool start);           // 0x0093a560
    int64_t GetElapsedTimeFloat();                 // 0x0093a3a0

    void Start() {
        if (mnStartTime == 0) {
            if (mnUnits == 1) {
                mnStartTime = __rdtsc();
            } else {
                int64_t li;
                QueryPerformanceCounter(&li);
                mnStartTime = (uint64_t)li;
            }
        }
    }
};
void* EA_GetMessagingServer();              // 0x00883860
struct Msg2T {
    void* vptr;                             // +0x00
    long  mField04;                         // +0x04
    void* mpText;                           // +0x08
    void* mField0c;                         // +0x0c
    void* mField10;                         // +0x10
};
typedef void (__thiscall *MsgPostFn)(void*, unsigned, void*, int);
struct SimObject {
virtual void v00();
virtual void v01();
    virtual void v02(int);
    virtual void v03(int);
    virtual char v04();
};
struct WorldObject {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15(float, float, void*);
};
// ---- items of slice s007da2d0 end

// ---- items of slice s007db1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl SporeAutomateAtExit();
extern "C" int  __cdecl atexit(void (__cdecl*)(void));
struct IConfigManager2 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11(int);
    virtual unsigned int v12(unsigned int);   // slot 12 (0x30), returns an id
};
void EDealloc(void* p);      // 0x00f47380
struct Str {                 // EA::string8 (cString8)
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAlloc;
    ~Str() { if ((int)(mpCapacity - mpBegin) > 1 && mpBegin != 0) EDealloc(mpBegin); }
};
void Sprintf8(char*, const char*, ...);      // 0x00938470
int g_1638280;
int g_1638284;
struct ManifestSource2 {
    char pad[8];
    void* (*mNext)();
    void Load();
};
void ManifestSource2::Load()
{
    IConfigManager2* cm = (IConfigManager2*)SP_ConfigManager();
    if (!cm)
        return;
    int* entry = (int*)mNext();
    while (entry) {
        int value;
        sscanf(*(const char**)((char*)entry + 4), "%x", &value);
        cm->v11(value);
        entry = (int*)mNext();
    }
}
struct SimVecU {             // SP::SimpleVector<unsigned int> (0x004cd3c0 = resize)
    unsigned int* mpBegin;
    unsigned int* mpEnd;
    unsigned int* mpCapacity;
    void resize(unsigned int n);          // 0x004cd3c0
    ~SimVecU() { if (mpBegin[-1] != 0) EDealloc(mpBegin); }
};
struct AutomateRunner {
    char pad0[0xc];
    void (__cdecl* mLog2)(void*);                          // +0xc
    void (__cdecl* mLog1)(char*, int, unsigned int*);      // +0x10
    char pad1[0x18];
    HMODULE mModule;        // +0x2c
    void ListCommands();    // 007db1b0
    void ListCommands2();   // 007db2a0
};
void* SP_PluginManagerGlobal;                  // 0x1638254
struct CmdMsg {
    int mType;        // +0x00
    char* mText;      // +0x04
    int a08;          // +0x08
    int a0c;          // +0x0c
    int a10;          // +0x10
    int a14;          // +0x14
    int a18;          // +0x18
    int a1c;          // +0x1c
    int a20;          // +0x20
    char pad[0x14];   // +0x24 .. +0x38
};
void AutomateRunner::ListCommands2()
{
    IConfigManager2* cm = (IConfigManager2*)SP_ConfigManager();
    if (!cm)
        return;
    SimVecU v;
    v.mpBegin = 0; v.mpEnd = 0; v.mpCapacity = 0;
    v.resize(9);
    v.mpBegin[0] = 0x046170a6;
    v.mpBegin[1] = 0x0461709e;
    v.mpBegin[2] = 0x0461709f;
    unsigned int n = (unsigned int)(((int)v.mpEnd - (int)v.mpBegin) >> 2);
    for (unsigned int i = 0; i < n; ++i) {
        char buf[32];
        Sprintf8(buf, "%x", v.mpBegin[i]);
        CmdMsg m = {};
        m.mType = 2;
        m.mText = buf;
        m.a10 = 1;
        m.a18 = 3;
        m.a20 = 3;
        mLog2(&m);
    }
}
int FUN_0092b200(const wchar_t*, int, int, int, int);  // 0x0092b200
int FUN_008d3ac0();                                    // 0x008d3ac0
void* FUN_0092b1b0(int);                               // 0x0092b1b0
void  EA_ConvertToString8(void*, void*);               // 0x0093c570
extern "C" int __stdcall FreeLibrary_s007d_b1b0(void*);           // kernel32
struct WideStr {                 // EA::string16-like object returned by 0x0092b1b0
    const wchar_t* mpBegin;
    const wchar_t* mpEnd;
};
struct PluginLoader {            // 0x007db0c0  (Loads a plugin DLL by name)
    bool Load(const char* name, char* afterSemi);
};
struct CommandRunner {
    char pad0[4];
    int (__cdecl* mReadCmd)(int*);   // +0x4
    char pad2[0x24];
    HMODULE mModule;                 // +0x2c
    bool Run(const char* args, char* flagOut);
};
void __cdecl EDealloc(void*);                 // 0x00f47380
// ---- items of slice s007db1b0 end

// ---- items of slice s007df780 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector3_s007d_f780 { float x, y, z; };
struct cError_s007d_f780 { cError_s007d_f780(const char*); };
namespace EA {
namespace Random {
class RandomLinearCongruential_s007d_f780 { public:
    unsigned mState;
    void   SetSeed(unsigned seed);        // 0x00936090
    double RandomDoubleUniform();         // 0x009360d0
};
}
}
namespace EA {
namespace IO {
bool WriteUint32(void* stream, const void* value, unsigned count, int endian);  // 0x0093aa70
}
}
namespace EA {
namespace ArgScript {
class cArguments_s007d_f780 { public:
    const char** MainArguments(int* count, int lo, int hi);   // 0x00838020
};
}
}
namespace EA {
namespace Swarm {
class cEffectsParser { public:
    void AddDescription(void* args, const char* name, int type, int flag);   // 0x00a6fc30
    void AddAnonDescription(void* args, int type, void* desc, int flag);     // 0x00a6fd40
};
}
}
void* __cdecl EAllocSwarm(int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
struct cSafeDynamicKernelStorage {
    int mKernelType;            // +0x0
    void* mKernelData;          // +0x4
    void* mKernelDataVariation; // +0x8

    void SetKernelType(int type);                              // 007e0340
    void SetNormal(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b);  // 007e0420
    void SetOrigin(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b);  // 007e0480
    void SetRadius(float a, float b);                          // 007e04f0
    void SetDirection(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b);// 007e0570
    cSafeDynamicKernelStorage& operator=(const cSafeDynamicKernelStorage& o);  // 007e05e0

    void* CreateRandomKernel();                                // 007df780
    void  Serialize(void* stream);                             // 007dfac0
    cSafeDynamicKernelStorage* ConstructFrom(const cSafeDynamicKernelStorage& o);  // 007dfc20
};
void cSafeDynamicKernelStorage::SetNormal(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b)
{
    if (mKernelType != 0)
        throw cError_s007d_f780("Either type not specified or type does not support this parameter");
    *(cSPVector3_s007d_f780*)mKernelData = a;
    *(cSPVector3_s007d_f780*)mKernelDataVariation = b;
}
void cSafeDynamicKernelStorage::SetOrigin(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b)
{
    if (mKernelType == 1 || mKernelType == 2) {
        *(cSPVector3_s007d_f780*)mKernelData = a;
        *(cSPVector3_s007d_f780*)mKernelDataVariation = b;
        return;
    }
    throw cError_s007d_f780("Either type not specified or type does not support this parameter");
}
void cSafeDynamicKernelStorage::SetRadius(float a, float b)
{
    if (mKernelType == 1) {
        *(float*)((char*)mKernelData + 0xc) = a;
        *(float*)((char*)mKernelDataVariation + 0xc) = b;
        return;
    }
    if (mKernelType == 2) {
        *(float*)((char*)mKernelData + 0x18) = a;
        *(float*)((char*)mKernelDataVariation + 0x18) = b;
        return;
    }
    throw cError_s007d_f780("Either type not specified or type does not support this parameter");
}
void cSafeDynamicKernelStorage::SetDirection(const cSPVector3_s007d_f780& a, const cSPVector3_s007d_f780& b)
{
    if (mKernelType != 2)
        throw cError_s007d_f780("Either type not specified or type does not support this parameter");
    *(cSPVector3_s007d_f780*)((char*)mKernelData + 0xc) = a;
    *(cSPVector3_s007d_f780*)((char*)mKernelDataVariation + 0xc) = b;
}
struct cDescCtx {
    char  mPad[0xc];
    void* mParser;                       // +0xc

    void FUN_007dfd90(EA::ArgScript::cArguments_s007d_f780* args);
};
// ---- items of slice s007df780 end

// @ 0x007d01f0
void* Ser1F0(IStream* s, char* p)
{
    uint16_t v16 = *(uint16_t*)p;
    float vf;
    WriteUint16(s, v16, 1, 0);
    vf = *(float*)(p + 0x10);
    WriteFloat32(s, vf, 1, 0);
    s->Write(p + 0x14, 0x24);
    s->Write(p + 4, 0xc);
    return s;
}

// @ 0x007d0250
void* Ser250(IStream* s, int* vec)
{
    int n = (vec[1] - vec[0]) >> 2;
    WriteUint32(s, (uint32_t)n, 1, 0);
    for (uint32_t i = 0; i < (uint32_t)n; i++)
        WriteFloat32(s, (float)*(float*)(vec[0] + i * 4), 1, 0);
    return s;
}

// @ 0x007d02b0
void* Ser2B0(IStream* s, int* vec)
{
    int n = (vec[1] - vec[0]) >> 3;
    WriteUint32(s, (uint32_t)n, 1, 0);
    for (uint32_t i = 0; i < (uint32_t)n; i++) {
        int* e = (int*)(vec[0] + i * 8);
        WriteUint32(s, (uint32_t)e[0], 1, 0);
        WriteByte(s, (uint8_t)*((uint8_t*)e + 4), 1);
        WriteByte(s, (uint8_t)*((uint8_t*)e + 5), 1);
    }
    return s;
}

// @ 0x007d0360
void Ser360(IStream* s, char* p)
{
    s->Write(p, 8);
    Ser250(s, (int*)(p + 8));
    WriteFloat32(s, (float)*(float*)(p + 0x1c), 1, 0);
    WriteUint32(s, (uint32_t)*(uint32_t*)(p + 0x24), 1, 0);
    WriteByte(s, (uint8_t)*(uint8_t*)(p + 0x28), 1);
}

// @ 0x007d03f0
void SerTree(void* stream, char* tree)
{
    uint32_t v = *(uint32_t*)(tree + 0x14);
    WU32(stream, &v, 1, 0);
    for (char* n = *(char**)(tree + 8); n != tree + 4; n = (char*)RBTreeIncrement(n)) {
        v = *(uint32_t*)(n + 0x10);
        WU32(stream, &v, 1, 0);
    }
}

// @ 0x007d0450
void* SerResp(void* stream, int* vec)
{
    int n = (vec[1] - vec[0]) / 0x2c;
    WU32(stream, &n, 1, 0);
    if (n != 0) {
        int i = 0;
        do {
            Ser360(stream, (char*)vec[0] + i);
            i += 0x2c;
            n = n - 1;
        } while (n != 0);
    }
    return stream;
}

// @ 0x007d04b0
void* SerDlg(void* stream, int* vec)
{
    uint32_t n = (uint32_t)((vec[1] - vec[0]) / 0x68);
    WU32(stream, &n, 1, 0);
    if (n != 0) {
        int off = 0;
        do {
            char* e = (char*)vec[0] + off;
            uint8_t b = *(uint8_t*)e;
            WB(stream, &b, 1);
            uint32_t v = *(uint32_t*)(e + 4);
            WU32(stream, &v, 1, 0);
            uint16_t h = *(uint16_t*)(e + 8);
            WU16(stream, &h, 1, 0);
            uint32_t v2 = *(uint32_t*)(e + 0x18);
            WU32(stream, &v2, 1, 0);
            ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x38 / 4])(stream, e + 0x1c, 0x24);
            ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x38 / 4])(stream, e + 0xc, 0xc);
            SerTree(stream, e + 0x4c);
            ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x38 / 4])(stream, e + 0x40, 0xc);
            off += 0x68;
            n--;
        } while (n != 0);
    }
    return stream;
}

// @ 0x007d06f0
void Ser6F0(void* stream, char* p)
{
    uint32_t v;
    v = *(uint32_t*)(p + 0xc);   WU32(stream, &v, 1, 0);
    v = *(uint32_t*)(p + 0x10);  WU32(stream, &v, 1, 0);
    ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x38 / 4])(stream, p + 0x14, 0xc);
    v = 0; WU32(stream, &v, 1, 0);
    v = 0; WU32(stream, &v, 1, 0);
    v = 0; WU32(stream, &v, 1, 0);
    v = 0; WU32(stream, &v, 1, 0);
    SerResp(stream, (int*)(p + 0x30));
    Ser2B0(stream, (int*)(p + 0x44));
    SerDlg(stream, (int*)(p + 0x58));
    FUN_0053bd00(stream, p + 0x6c);
    v = 0; WU32(stream, &v, 1, 0);
    uint8_t b = 0; WB(stream, &b, 1);
    b = 0; WB(stream, &b, 1);
    v = 0; WU32(stream, &v, 1, 0);
}

// @ 0x007d0920
void* CloneTreeOwner::CloneTree(int* src, void* parent)
{
    int* n = (int*)EAlloc(0x14, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if ((int*)((char*)n + 0x10) != 0)
        *(int*)((char*)n + 0x10) = src[4];
    n[0] = 0;
    n[1] = 0;
    n[2] = (int)parent;
    *((char*)n + 0xc) = (char)src[3];
    if (*src != 0) {
        void* r = this->CloneTree((int*)*src, n);
        n[0] = (int)r;
    }
    void* cur = n;
    for (int* c = (int*)src[1]; c != 0; c = (int*)c[1]) {
        int* m = (int*)EAlloc(0x14, "App", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        if ((int*)((char*)m + 0x10) != 0)
            *(int*)((char*)m + 0x10) = c[4];
        m[0] = 0;
        m[1] = 0;
        m[2] = (int)cur;
        *((char*)m + 0xc) = (char)c[3];
        *((void**)cur + 1) = m;
        if (*c != 0) {
            void* r = this->CloneTree((int*)*c, m);
            m[0] = (int)r;
        }
        cur = m;
    }
    return n;
}

// @ 0x007d0c10
void ReadC10(void* stream, RBTreeFind* tree)
{
    unsigned int count;
    RI32(stream, &count, 1, 0);
    for (unsigned int i = 0; i < count; i++) {
        union { int v; char c; } value;
        int key;
        struct { void* node; unsigned int valid; } out;
        RI32(stream, &key, 1, 0);
        value.c = 0;
        tree->DoInsert(&out, &key, value.v);
    }
}

// @ 0x007d4540
uint32_t TestKey(void* unused, const uint32_t* p, uint32_t* out, int n)
{
    uint32_t lo = p[0x24 / 4];
    uint32_t hi = p[0x28 / 4];
    if ((lo & hi) != 0xffffffff) {
        if (n > 0) { out[0] = lo; out[1] = hi; out[2] = 0x102; }
        return 1;
    }
    return 0;
}

// @ 0x007d45d0
double __cdecl RandomRange(float a, float b)
{
    double r = gRandom.RandomDoubleUniform();
    double lo = (double)a - (double)b;
    double hi = (double)a + (double)b;
    double v = r * (hi - lo) + lo;
    if (v < hi) {
        if (lo <= v)
            return v;
        return lo;
    }
    return hi;
}

// @ 0x007d5a30
CtrlVec::~CtrlVec()
{
    CtrlDestroyValues(mpBegin, mpEnd);
}

// @ 0x007d5aa0
char** UninitCopyElem78(char** out, char* first, char* last, char* base, const void* extra)
{
    *out = base;
    while (first != last) {
        char* p = *out;
        if (p) { *(uint32_t*)p = *(uint32_t*)first; new (p + 4) cSplitInstance(first + 4); }
        *out = *out + 0x78;
        first += 0x78;
    }
    (void)extra;
    return out;
}

// @ 0x007d5af0
cGameModelEffect::cGameModelEffect(void* desc, int packageID)
{
    mDesc = desc;
    mPackageID = packageID;
    mActive = false;
    mIsVisible = true;
    mIsLoaded = false;
    mGameModelInstanceID = 0xffffffff;
    mGameModelGroupID = 0xffffffff;
    mGameModelColor[0] = 1.0f;
    mGameModelColor[1] = 1.0f;
    mGameModelColor[2] = 1.0f;
    mGameModelAlpha = 1.0f;
    mGameModelScale = 1.0f;
    mIntersectionRadius = 1e-5f;
    mGameModel.mpObject = 0;
    mComponentXform.mFlags = 0;
    mComponentXform.mModificationCount = 0;
    mComponentXform.mTranslation[0] = g_vecInit[0];
    mComponentXform.mTranslation[1] = g_vecInit[1];
    mComponentXform.mTranslation[2] = g_vecInit[2];
    mComponentXform.mScale = 1.0f;
    mComponentXform.mRotation.Assign(&g_matIdentityA);
    mLastLocation[0] = g_vecInit[0];
    mLastLocation[1] = g_vecInit[1];
    mLastLocation[2] = g_vecInit[2];
    mAnimationInfo.mpBegin = 0; mAnimationInfo.mpEnd = 0; mAnimationInfo.mpCapacity = 0;
    mModelSplitter.mpObject = 0;
    mSplitManager.mpObject = 0;
    mLODSizeScale[0] = 1.0f; mLODSizeScale[1] = 1.0f;
    mSplitControllers.mpBegin = 0; mSplitControllers.mpEnd = 0; mSplitControllers.mpCapacity = 0;
    mLODAlphaScale[0] = 1.0f; mLODAlphaScale[1] = 1.0f;
    mModelManager = 0;
    mGameModelWorld = 0;
}

// @ 0x007d5c50
cGameModelEffect::~cGameModelEffect()
{}

// @ 0x007d5d50
cSplitManager::cSplitManager()
{
    mComponentTransform.mFlags = 0;
    mComponentTransform.mModificationCount = 0;
    mComponentTransform.mTranslation[0] = g_vecInitB[0];
    mComponentTransform.mTranslation[1] = g_vecInitB[1];
    mComponentTransform.mTranslation[2] = g_vecInitB[2];
    mComponentTransform.mScale = g_one;
    mComponentTransform.mRotation.Assign(&g_matIdentityB);
    mSplitClientList.mpBegin = 0;
    mSplitClientList.mpEnd = 0;
    mSplitClientList.mpCapacity = 0;
}

// @ 0x007d5e60
void cGameModelEffect::FindGameModel()
{
    ModelPtrVec found;
    float pos[3] = { mComponentXform.mTranslation[0], mComponentXform.mTranslation[1], mComponentXform.mTranslation[2] };
    ModelQueryFilter filter = { { 0, 0, 0, 0, 0 }, 0, 0 };
    if (mGameModelWorld->QueryModels(pos, mIntersectionRadius, &found, &filter)) {
        int n = (int)(found.mpEnd - found.mpBegin);
        for (int i = 0; i < n; ++i) {
            cPropertyList* pl = found.mpBegin[i]->mPropertyList;
            if (pl) {
                ResKey key = pl->mKey;
                if (key.instanceID == mGameModelInstanceID || key.groupID == mGameModelGroupID) {
                    cMWModel* cur = mGameModel.mpObject;
                    cur->mpWorld->ReleaseModel(cur, 0);
                    mGameModel.Assign(found.mpBegin[i]);
                    break;
                }
            }
        }
    }
}

// @ 0x007d6030
void AnimVec::DoInsertValues(cAnimationInfo* position, unsigned n, const cAnimationInfo* value)
{
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const cAnimationInfo temp = *value;
            unsigned nExtra = (unsigned)(mpEnd - position);
            if (n < nExtra) {
                cAnimationInfo* pOldEnd = mpEnd;
                AnimUninitCopyWrap(pOldEnd - n, pOldEnd, pOldEnd);
                mpEnd += n;
                AnimCopyBackward(position, pOldEnd - n, pOldEnd);
                AnimFill(position, position + n, &temp);
            } else {
                cAnimationInfo* pOldEnd = mpEnd;
                AnimUninitFillN(pOldEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                AnimUninitCopyWrap(position, pOldEnd, mpEnd);
                mpEnd += nExtra;
                AnimFill(position, pOldEnd, &temp);
            }
        }
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nGrow = nPrevSize ? nPrevSize * 2 : 1;
        unsigned nNewSize = nGrow > nPrevSize + n ? nGrow : nPrevSize + n;
        cAnimationInfo* pNewData = nNewSize ? (cAnimationInfo*)operator new(nNewSize * sizeof(cAnimationInfo), "App", 0, 0, EASTL_ALLOC_FILE, 0xd1) : 0;
        cAnimationInfo* pNewEnd = AnimUninitCopy(mpBegin, position, pNewData);
        AnimUninitFillN(pNewEnd, n, value);
        pNewEnd = AnimUninitCopy(position, mpEnd, pNewEnd + n);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x007d61f0
void* __stdcall AllocAndCopy78(unsigned n, char* first, char* last)
{
    char* buf = n ? (char*)operator new(n * 0x78, "App", 0, 0, EASTL_ALLOC_FILE, 0xd1) : 0;
    char* out = buf;
    UninitCopyElem78(&out, first, last, buf, 0);
    return buf;
}

// @ 0x007d6250
Elem78* CopyElems78(Elem78* first, Elem78* last, Elem78* dst)
{
    if (first == last) return dst;
    while (first != last) {
        dst->mNextFree = first->mNextFree;
        dst->mFlags = first->mFlags;
        dst->mInstanceTransform = first->mInstanceTransform;
        dst->mFinalTransform = first->mFinalTransform;
        ++first; ++dst;
    }
    return dst;
}

// @ 0x007d6380
cMapResA* MakeMapResA(void* mem, const RbMap& m)
{ return new (mem) cMapResA(m); }

// @ 0x007d6440
cMapResB::cMapResB(const RbMap& m, const float* v, GmeRefCount* r)
: mMap(m) {
    mVec[0] = v[0];
    mVec[1] = v[1];
    mVec[2] = v[2];
    mpRef.mpObject = r;
    if (r) ++r->mnRefCount;
}

// @ 0x007d67e0
cSplitInstanceList** CopyConstructToPtr(cSplitInstanceList** pDest, const cSplitInstanceList* first, const cSplitInstanceList* last, cSplitInstanceList* dest)
{
    *pDest = dest;
    for (; first != last; ++first) {
        ::new (*pDest) cSplitInstanceList(*first);
        *pDest += 1;
    }
    return pDest;
}

// @ 0x007d68f0
void FillConstructN(cSplitInstanceList* dest, size_type n, const cSplitInstanceList* value)
{
    for (; n != 0; --n, ++dest)
        ::new (dest) cSplitInstanceList(*value);
}

// @ 0x007d69f0
cSplitInstanceList* CopyConstructRange(const cSplitInstanceList* first, const cSplitInstanceList* last, cSplitInstanceList* dest)
{
    for (; first != last; ++first, ++dest)
        ::new (dest) cSplitInstanceList(*first);
    return dest;
}

// @ 0x007d6b00
cEffectParams_s007d_67e0& cEffectParams_s007d_67e0::operator=(const cEffectParams_s007d_67e0& x)
{
    for (int i = 0; i < 25; ++i)
        mFloatParams[i] = x.mFloatParams[i];
    mFloatParamStorage = x.mFloatParamStorage;
    for (int i = 0; i < 9; ++i)
        mIntParams[i] = x.mIntParams[i];
    mUnk9c = x.mUnk9c;
    mIntParamStorage = x.mIntParamStorage;
    for (int i = 0; i < 9; ++i)
        mUnknownParams[i] = x.mUnknownParams[i];
    return *this;
}

// @ 0x007d6c10
void cSwarmThis::Sub_7d6c10(int arg)
{
    cSwarmParams* params = mParams;
    if (mC4 != 0 && mRec == 0) {
        unsigned local = 0;
        if (params->mV30 == params->mV34)
            local = 1;
        else if (1 < (unsigned)((int)((char*)params->mV34 - (char*)params->mV30) / 0x2c))
            local = 2;
        if ((params->mFlags >> 5) & 1)
            local |= 8;
        int r = ((int(__thiscall*)(IUnknown32*, int, int, int))mC4->vftable[3])(mC4, mArg18, mArg1c, local);
        Sub_478db0(r);
        void* rec = mRec;
        mFlag16 = 0;
        if (rec != 0) {
            if (mFlag15 == 0)
                *(unsigned*)((char*)rec + 4) &= ~1u;
            else
                *(unsigned*)((char*)rec + 4) |= 1u;
            if ((params->mFlags >> 4) & 1) {
                float dx = *(float*)((char*)rec + 0x7c) - *(float*)((char*)rec + 0x70);
                float dy = *(float*)((char*)rec + 0x80) - *(float*)((char*)rec + 0x74);
                float dz = *(float*)((char*)rec + 0x84) - *(float*)((char*)rec + 0x78);
                float d = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
                d *= *(float*)((char*)rec + 0x18);
                if (0.0f < d) {
                    d = mFloat30 / d;
                    mFloat30 = d;
                    mCount3e = (unsigned short)(mCount3e + 1);
                    mF4c = d;
                }
            }
            if (mA4 != 0) {
                ((void(__thiscall*)(IUnknown32*, void*))mC4->vftable[0x58 / 4])(mC4, rec);
                int v = Sub_79ac10((int)mA4, (int)mA8, 1);
                ((void(__thiscall*)(IUnknown32*, void*, int))mC4->vftable[0xac / 4])(mC4, rec, v);
            }
            unsigned h = ((unsigned(__thiscall*)(IUnknown32*, unsigned, int))mC0->vftable[0x28 / 4])(mC0, 0x73cb32c9, 0);
            if (h < 0x40) {
                unsigned* w = (unsigned*)((char*)rec + 0x44 + (h >> 5) * 4);
                *w |= 1u << (h & 0x1f);
            }
            if (params->mV6c != params->mV70) {
                int cnt = (int)((char*)params->mV70 - (char*)params->mV6c) >> 2;
                for (int i = 0; i < cnt; ++i) {
                    unsigned hh = ((unsigned(__thiscall*)(IUnknown32*, int, int))mC0->vftable[0x28 / 4])(mC0, params->mV6c[i], 0);
                    if (hh < 0x40) {
                        unsigned* w = (unsigned*)((char*)rec + 0x44 + (hh >> 5) * 4);
                        *w |= 1u << (hh & 0x1f);
                    }
                }
            }
            *(unsigned*)((char*)rec + 4) |= params->mFlags80;
            *(unsigned char*)((char*)rec + 0x5d) = (unsigned char)params->mByte84;
            void** rvt = *(void***)rec;
            ((void(__thiscall*)(void*, int))rvt[0x16c / 4])(rec, 0);
        }
    }
    if ((params->mFlags >> 3) & 1)
        Sub_7d5e60(this);
    if (mFlag14 == 0 && mRec != 0) {
        mFlag14 = 1;
        int n = (int)(mB4 - mB0) >> 6;
        for (int i = 0; i < n; ++i) {
            void* o = *(void**)(mB0 + i * 0x40 + 0x3c);
            ((void(__thiscall*)(void*, int))((*(void***)o)[2]))(o, arg);
        }
        int cnt = (int)((char*)params->mV34 - (char*)params->mV30) / 0x2c;
        ResizeFloatVector(&mFloatVec, cnt);
        if (cnt != 0) {
            float* out = (float*)mFloatVec;
            int i = 0;
            int off = 0;
            int remaining = cnt;
            do {
                out[i] = 0.0f;
                float* p = (float*)((char*)params->mV30 + off);
                float lo = p[0];
                float hi = p[1];
                double r = RandomDoubleUniform(RandomLCG_Swarm());
                float v = (float)(r * (double)(hi - lo) + (double)lo);
                if (v >= hi) v = hi;
                else if (v < lo) v = lo;
                if (v <= 0.0f) out[i + 1] = 0.0f;
                else out[i + 1] = 1.0f / v;
                float c = *(float*)((char*)params->mV30 + off + 0x1c);
                double r2 = RandomDoubleUniform(RandomLCG_Swarm());
                float upper = c + 1.0f;
                float lower = 1.0f - c;
                float v2 = (float)(r2 * (double)(upper - lower) + (double)lower);
                if (v2 >= upper) v2 = upper;
                else if (v2 < lower) v2 = lower;
                off += 0x2c;
                out[i + 2] = v2;
                i += 3;
            } while (--remaining);
        }
        *(float*)((char*)this + 0x74) = mF40;
        *(float*)((char*)this + 0x78) = mF44;
        *(float*)((char*)this + 0x7c) = mF48;
    }
}

// @ 0x007d7080
CElementVector& CElementVector::operator=(const CElementVector& x)
{
    if (this != &x) {
        size_type n = (size_type)(x.mpEnd - x.mpBegin);
        if ((size_type)(mpCapacity - mpBegin) < n) {
            cElement* pNew = AllocElementArray(n, x.mpBegin, x.mpEnd);
            if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
                ea_free(mpBegin);
            mpBegin = pNew;
            mpCapacity = pNew + n;
        } else if ((size_type)(mpEnd - mpBegin) < n) {
            size_type nOld = (size_type)(mpEnd - mpBegin);
            AssignElements(x.mpBegin, x.mpBegin + nOld, mpBegin);
            cElement* cur = mpEnd;
            UninitCopyElements(&cur, x.mpBegin + nOld, x.mpEnd, mpEnd);
        } else {
            AssignElements(x.mpBegin, x.mpEnd, mpBegin);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x007d71b0
cSplitInstanceList* CopyAssignForward(const cSplitInstanceList* first, const cSplitInstanceList* last, cSplitInstanceList* dest)
{
    for (; first != last; ++first, ++dest) {
        dest->mNextFree = first->mNextFree;
        dest->mDataArray = first->mDataArray;
        dest->mExtra = first->mExtra;
    }
    return dest;
}

// @ 0x007d71f0
cSplitInstanceList* CopyAssignBackward(const cSplitInstanceList* first, const cSplitInstanceList* last, cSplitInstanceList* dest)
{
    while (last != first) {
        --last;
        --dest;
        dest->mNextFree = last->mNextFree;
        dest->mDataArray = last->mDataArray;
        dest->mExtra = last->mExtra;
    }
    return dest;
}

// @ 0x007d7240
void AssignValueRange(cSplitInstanceList* first, cSplitInstanceList* last, const cSplitInstanceList* value)
{
    for (; first != last; ++first) {
        first->mNextFree = value->mNextFree;
        first->mDataArray = value->mDataArray;
        first->mExtra = value->mExtra;
    }
}

// @ 0x007d7560
void ListVector::resize(size_type n)
{
    const size_type nSize = (size_type)(mpEnd - mpBegin);
    if (n > nSize) {
        cSplitInstanceList value;
        DoInsertValues(mpEnd, n - nSize, value);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x007d7ce0
bool __stdcall FilterAbilityType(int type, int, int)
{
    switch (type) {
        case 4: return true;
        case 5: return true;
        default: return false;
    }
}

// @ 0x007d7d00
void cAbilityCmd::Destroy()
{
    mBaseVtbl = (void**)0x01412458;
    mAbilityVtbl = (void**)0x01412454;
    if (mIface != 0) {
        void** vt = *(void***)mIface;
        ((void(__thiscall*)(void*))vt[1])(mIface);
    }
    mAbilityVtbl = (void**)0x013ef094;
    mBaseVtbl = (void**)0x013f21d4;
}

// @ 0x007d7d70
void cAbilityCmd::SetIface(int, int, int)
{
    void* iface = Sub_67de00();                          // some manager
    void** vt = *(void***)iface;
    void* result = ((void*(__thiscall*)(void*))vt[0x9c / 4])(iface);
    void* old = mIface;
    if (result != old) {
        if (result != 0)
            ((void(__thiscall*)(void*))(*(void***)result)[0])(result);
        mIface = result;
        if (old != 0)
            ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }
}

// @ 0x007d7dc0
void cAbilityCmd::Activate(int arg)
{
    if (mActive == 0 && mIface != 0) {
        AbilityDesc* desc = (AbilityDesc*)mDesc;
        mActive = 1;
        float scale = *(float*)0x01488874;
        if (desc->mKind == 4)
            scale = *desc->mScale;
        float pos[3];
        pos[0] = desc->mPosition[0];
        pos[1] = desc->mPosition[1];
        pos[2] = desc->mPosition[2];
        float p[3];
        p[0] = mx;
        p[1] = my;
        p[2] = mz;
        float radius = *desc->mRadius;
        void** vt = *(void***)mIface;
        int r = ((int(__thiscall*)(void*, float*, float*, float, float))
                 vt[0xc / 4])(mIface, p, pos, radius, scale);
        mId = r;
    }
}

// @ 0x007d7e80
void cAbilityCmd::Deactivate(int)
{
    if (mActive != 0) {
        mActive = 0;
        if (mId != -1) {
            void** vt = *(void***)mIface;
            ((void(__thiscall*)(void*, int))vt[0x14 / 4])(mIface, mId);
            mId = -1;
        }
    }
}

// @ 0x007d7ed0
cAbilityCmd* AbilityCmdNew(void* arg)
{
    cAbilityCmd* p = (cAbilityCmd*)operator new[](0x28, "Swarm", 0, 0, 0, 0);
    if (p != 0) {
        p->mAbilityVtbl = (void**)0x013ef094;
        p->mUnk08 = 0;
        p->mBaseVtbl = (void**)0x01412458;
        p->mAbilityVtbl = (void**)0x01412454;
        p->mDesc = arg;
        p->mIface = 0;
        p->mActive = 0;
        p->mx = 0.0f;
        p->my = 0.0f;
        p->mz = 0.0f;
        p->mId = -1;
        return p;
    }
    return 0;
}

// @ 0x007d7f40
void AbilityRegister()
{
    *(void**)0x01675ff8 = (void*)0x007d7ed0;
    *(void**)0x01675ff0 = 0;
}

// @ 0x007d7f60
void cAbilityCmd::SetTransform(void* xformA, const TransformTemp* desc)
{
    TransformTemp t;
    t.mFlags = desc->mFlags;
    t.mModificationCount = desc->mModificationCount;
    t.mTranslation = desc->mTranslation;
    t.mScale = desc->mScale;
    ((Matrix3Helper*)&t.mRotation)->Matrix3_Assign(&desc->mRotation);
    ((TransformHelper*)&t)->Sub_537f40(xformA);
    float tx = t.mTranslation.x;
    float ty = t.mTranslation.y;
    float tz = t.mTranslation.z;
    if (mx != tx || my != ty || mz != tz) {
        mx = tx;
        my = ty;
        mz = tz;
        if (mId != -1) {
            float p[3];
            p[0] = mx; p[1] = my; p[2] = mz;
            void** vt = *(void***)mIface;
            ((void(__thiscall*)(void*, int, float*))vt[0x10 / 4])(mIface, mId, p);
        }
    }
}

// @ 0x007dae20
int SP_RunOfflineWorld(WorldObject* world, SimObject* sim, int seed, unsigned int dtMs, float maxSeconds, int unused, float* outElapsed, char verbose, void* effectName)
{
    if (seed == 0 || seed == -1)
        seed = 0xdeadbeef;
    g_sRandom.SetSeed(seed);
    g_sRandom.RandomUint32Uniform();
    g_sRandom.RandomUint32Uniform();
    g_sRandom.RandomUint32Uniform();

    int totalMs = 0;
    EA_Stopwatch sw(5, false);
    sw.Start();
    sim->v02(0);

    float dt = (float)dtMs * 0.001f;
    float elapsed;
    char buffer[0x80];
    for (;;) {
        world->v15(dt, dt, buffer);
        totalMs += dtMs;
        elapsed = (float)sw.GetElapsedTimeFloat() *
                  sw.mfStopwatchCyclesToUnitsCoefficient;
        if (!sim->v04())
            break;
        if (!(maxSeconds > elapsed))
            break;
    }
    sim->v03(1);
    if (outElapsed)
        *outElapsed = elapsed;
    world->v13();
    if (verbose) {
        eastl::basic_string_s007d_a2d0 text;
        text.sprintf("Effect: %s, Duration: %d virtual ms in %g s (%g x)\n",
                     (const char*)effectName, totalMs, (double)elapsed,
                     (double)totalMs / ((double)elapsed * 1000.0f));
        Msg2T msg;
        msg.mField10 = 0;
        msg.vptr = vtbl_MsgBase;
        _InterlockedExchange(&msg.mField04, 0);
        msg.vptr = vtbl_MsgDerived;
        msg.mpText = (void*)text.c_str();
        void* server = EA_GetMessagingServer();
        ((MsgPostFn)(*(void***)server)[5])(server, 0x11998ee, &msg, 0);
    }
    return totalMs;
}

// @ 0x007db060
void ManifestSource::Load()
{
    IConfigManager* cm = (IConfigManager*)SP_ConfigManager();
    if (!cm)
        return;
    int* entry = (int*)mNext();
    while (entry) {
        int value;
        sscanf(*(const char**)((char*)entry + 4), "%x", &value);
        cm->v11(value, *(int*)((char*)entry + 8));
        entry = (int*)mNext();
    }
}

// @ 0x007db1b0
void AutomateRunner::ListCommands()
{
    IConfigManager2* cm = (IConfigManager2*)SP_ConfigManager();
    if (!cm)
        return;
    SimVecU v;
    v.mpBegin = 0; v.mpEnd = 0; v.mpCapacity = 0;
    v.resize(9);
    v.mpBegin[0] = 0x046170a6;
    v.mpBegin[1] = 0x0461709e;
    v.mpBegin[2] = 0x0461709f;
    unsigned int n = (unsigned int)(((int)v.mpEnd - (int)v.mpBegin) >> 2);
    for (unsigned int i = 0; i < n; ++i) {
        unsigned int id = cm->v12(v.mpBegin[i]);
        char buf[36];
        Sprintf8(buf, "%x", v.mpBegin[i]);
        mLog1(buf, 2, &id);
    }
}

// @ 0x007db3a0
bool CommandRunner::Run(const char* args, char* flagOut)
{
    (void)args;
    *flagOut = 0;
    int idx = FUN_0092b200(L"-openautomate", 1, 0, 0, 0);
    if (idx == -1)
        return false;
    if (idx + 1 >= FUN_008d3ac0())
        return false;
    *flagOut = 1;
    WideStr* ws = (WideStr*)FUN_0092b1b0(idx + 1);
    const wchar_t* wp = ws->mpBegin;
    unsigned int wcount = (unsigned int)(ws->mpEnd - wp) >> 1;
    int semi = -1;
    for (unsigned int k = 0; k < wcount; ++k) {
        if (wp[k] == L';') { semi = (int)k; break; }
    }
    Str s;
    EA_ConvertToString8(&s, ws);
    char buf[1024];
    strcpy(buf, s.mpBegin);
    char* rest = buf + (int)(s.mpEnd - s.mpBegin);
    if (semi >= 0) {
        buf[semi] = 0;
        rest = buf + semi + 1;
    }
    if (((PluginLoader*)this)->Load(buf, rest)) {
        *flagOut = 0;
        int c = 0;
        for (;;) {
            c = 0;
            c = ((int (__cdecl*)(int*))*(void**)((char*)this + 4))(&c);
            switch (c) {
            case 0: *flagOut = 1; goto flush;
            case 2: ((AutomateRunner*)this)->ListCommands2(); break;
            case 3: ((AutomateRunner*)this)->ListCommands(); break;
            case 4: ((ManifestSource2*)this)->Load(); break;
            }
            if (*flagOut) goto flush;
            if (c == 1) break;
        }
flush:
        if (mModule) {
            FreeLibrary_s007d_b1b0(mModule);
            mModule = 0;
            memset(this, 0, 0x2c);
        }
        return true;
    }
    return false;
}

// @ 0x007db570
void SP_AutomateEntry(int a, int b)
{
    if (!(g_1638284 & 1)) {
        g_1638284 |= 1;
        g_1638280 = 0;
        atexit(SporeAutomateAtExit);
    }
    ((CommandRunner*)&SP_PluginManagerGlobal)->Run((const char*)a, (char*)b);
}

// @ 0x007df780
void* cSafeDynamicKernelStorage::CreateRandomKernel()
{
    EA::Random::RandomLinearCongruential_s007d_f780 rng;
    rng.SetSeed(0xffffffffu);
    int type = mKernelType;
    if (type == 0) {
        const float* a = (const float*)mKernelData;
        const float* b = (const float*)mKernelDataVariation;
        float* out = (float*)EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        double r;
        r = rng.RandomDoubleUniform(); float x = (float)((r + r - 1.0) * b[0] + a[0]);
        r = rng.RandomDoubleUniform(); float y = (float)((r + r - 1.0) * b[1] + a[1]);
        r = rng.RandomDoubleUniform(); float z = (float)((r + r - 1.0) * b[2] + a[2]);
        float inv = 1.0f / sqrtf(x * x + y * y + z * z);
        out[0] = x * inv; out[1] = y * inv; out[2] = z * inv;
        r = rng.RandomDoubleUniform(); double v = (r + r - 1.0) * b[3] + a[3]; out[3] = (float)(v * v);
        return out;
    }
    if (type == 1) {
        const float* a = (const float*)mKernelData;
        const float* b = (const float*)mKernelDataVariation;
        float* out = (float*)EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        double r;
        r = rng.RandomDoubleUniform(); out[0] = (float)((r + r - 1.0) * b[0] + a[0]);
        r = rng.RandomDoubleUniform(); out[1] = (float)((r + r - 1.0) * b[1] + a[1]);
        r = rng.RandomDoubleUniform(); out[2] = (float)((r + r - 1.0) * b[2] + a[2]);
        r = rng.RandomDoubleUniform(); double v = (r + r - 1.0) * b[3] + a[3]; out[3] = (float)(v * v);
        return out;
    }
    if (type == 2) {
        const float* a = (const float*)mKernelData;
        const float* b = (const float*)mKernelDataVariation;
        float* out = (float*)EAllocSwarm(0x1c, "App", 0, 0, 0, 0);
        double r;
        r = rng.RandomDoubleUniform(); out[0] = (float)((r + r - 1.0) * b[0] + a[0]);
        r = rng.RandomDoubleUniform(); out[1] = (float)((r + r - 1.0) * b[1] + a[1]);
        r = rng.RandomDoubleUniform(); out[2] = (float)((r + r - 1.0) * b[2] + a[2]);
        r = rng.RandomDoubleUniform(); float x = (float)((r + r - 1.0) * b[3] + a[3]);
        r = rng.RandomDoubleUniform(); float y = (float)((r + r - 1.0) * b[4] + a[4]);
        r = rng.RandomDoubleUniform(); float z = (float)((r + r - 1.0) * b[5] + a[5]);
        float inv = 1.0f / sqrtf(x * x + y * y + z * z);
        out[3] = x * inv; out[4] = y * inv; out[5] = z * inv;
        r = rng.RandomDoubleUniform(); double v = (r + r - 1.0) * b[6] + a[6]; out[6] = (float)(v * v);
        return out;
    }
    return 0;
}

// @ 0x007dfac0
void cSafeDynamicKernelStorage::Serialize(void* stream)
{
    unsigned type = (unsigned)mKernelType;
    EA::IO::WriteUint32(stream, &type, 1, 0);
    switch (mKernelType) {
    case 0:
    case 1: {
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, mKernelData, 0xc);
        float v = *(float*)((char*)mKernelData + 0xc);
        EA::IO::WriteUint32(stream, &v, 1, 0);
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, mKernelDataVariation, 0xc);
        v = *(float*)((char*)mKernelDataVariation + 0xc);
        EA::IO::WriteUint32(stream, &v, 1, 0);
        break;
    }
    case 2: {
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, mKernelData, 0xc);
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, (char*)mKernelData + 0xc, 0xc);
        float v = *(float*)((char*)mKernelData + 0x18);
        EA::IO::WriteUint32(stream, &v, 1, 0);
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, mKernelDataVariation, 0xc);
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, (char*)mKernelDataVariation + 0xc, 0xc);
        v = *(float*)((char*)mKernelDataVariation + 0x18);
        EA::IO::WriteUint32(stream, &v, 1, 0);
        break;
    }
    }
}

// @ 0x007dfbd0
void __cdecl FUN_007dfbd0(void* description, void* stream)
{
    ((cSafeDynamicKernelStorage*)((char*)description + 8))->Serialize(stream);
}

// @ 0x007dfbf0
void* FUN_007dfbf0()
{
    int* p = (int*)EAllocSwarm(8, "Swarm", 0, 0, 0, 0);
    if (p) {
        p[1] = 0;
        p[0] = 0x1453948;
        return p;
    }
    return 0;
}

// @ 0x007dfd90
void cDescCtx::FUN_007dfd90(EA::ArgScript::cArguments_s007d_f780* args)
{
    int count = 0;
    const char** av = args->MainArguments(&count, 0, 1);
    if (count == 1) {
        ((EA::Swarm::cEffectsParser*)mParser)->AddDescription(args, av[0], 0x29, 0);
        return;
    }
    void** p = (void**)EAllocSwarm(8, "Swarm", 0, 0, 0, 0);
    if (p) { p[1] = 0; p[0] = (void*)0x1453948; }
    if (p) p[1] = (void*)((int)p[1] + 1);
    ((EA::Swarm::cEffectsParser*)mParser)->AddAnonDescription(args, 0x29, p, 0);
    if (p) {
        int rc = (int)p[1] - 1;
        p[1] = (void*)rc;
        if (rc == 0) {
            p[1] = (void*)1;
            (*(void(__thiscall**)(void*, int))(*(void**)p))(p, 1);
        }
    }
}
