// src/game/SPEngine/SPAppGameModelEffect.cpp -- migrated from slice(s) s007d76d0, s007d67e0, s007d56f0, s007d4a40, s007d3930 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppGameModelEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Swarm/cEffectParams.h"
#include <intrin.h>
#include <math.h>
#include "EA/Swarm/cTransform.h"
#include <string.h>
#include "SP/cGameModelDescription.h"

// ---- items of slice s007d3930 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size);
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
struct cSPTransformOps_s007d_3930 { cSPTransformOps_s007d_3930* Assign(const void* src); };  // 0x537dc0
struct cLabelOps_s007d_3930      { void Propagate(const void* txf); };            // 0x79a0d0
struct IUnknown32 { virtual void AddRef(); virtual void Release(); };
struct EffComp {
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
virtual void e4();
virtual void e5();
virtual void e6();
virtual void e7();
virtual void e8();
virtual void e9();
    virtual void SetFlag(int f);   // +0x28
};
struct EffOwner { void SetVisible(int param); };
struct VecOut {
    void* b; void* e; void* c;
    VecOut* Allocate(unsigned n, void* alloc);
};
struct cEffectParams {
    char pad[0xb4];
    IUnknown32* mUnknown[9];
    void UnknownStore(int idx, IUnknown32* p);
};
struct cEffectNode { void Tick(void* arg); char HandleParam(int kind, float* value, void* extra); };
struct cEffectMessage {
    void* mpSource;         // +0x00
    uint32_t mPad4;         // +0x04
    uint32_t mEventType;    // +0x08
    uint32_t mPadc;         // +0x0c
    uint32_t mKey;          // +0x10
};
struct cEffectMsgContext {
    char pad00[0x0c];
    uint32_t mFlags;        // +0x0c
    char pad10[0x78];
    uint32_t mMessageId;    // +0x88
};
struct cMessageServer;
cMessageServer* __cdecl GetServer();   // 0x00883860
struct XformVec {
    int32_t  field00;      // +0x00
    int32_t  field04;      // +0x04
    void*    p08;          // +0x08  (cSPTransform copy target)
    char     pad0c[0x34];  // +0x0c
    char*    mpBegin;      // +0x40
    char*    mpEnd;        // +0x44
    void DoInsertValue(const void* src);
};
// ---- items of slice s007d3930 end

// ---- items of slice s007d4a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  operator delete[](void* p) throw();
void  operator delete(void* p);
struct Obj {
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
    virtual void AddRef();    // +0x34
    virtual void Release();   // +0x38
};
struct AddRefObj {
    virtual void AddRef();          // vtable[0]
    virtual void Release();         // vtable[1]
};
struct AutoRefCountH {
    AddRefObj* mpObject;
    AutoRefCountH& operator=(AddRefObj* p) {
        if (p != mpObject) {
            AddRefObj* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct RefCounted {
    virtual void v0();          // +0x00 vtable
    uint32_t mFlags;            // +0x04
    uint32_t mPad[0x38 / 4];    // +0x08 ..
    int32_t mRefCount;          // +0x40
    uint32_t mPad2[0x20 / 4];   // +0x44 ..
    AutoRefCountH mHandle;      // +0x64
    void Release();
};
typedef void(__cdecl* VDestroy)(RefCounted*, int);
inline void RefCounted::Release() {
    int32_t c = mRefCount;
    if (c > 1) { mRefCount = c - 1; return; }
    // The destroying destructor is reached through two indirections
    // ([[vtbl]] + 0x170) and takes (this, destroy-flag) on the stack. The flag
    // is formed first so the indirect load keeps the inner table in ecx.
    char flag = (char)(mFlags >> 31);
    void** vtbl = *(void***)this;
    VDestroy dtor = *(VDestroy*)((char*)*(void**)vtbl + 0x170);
    dtor(this, (int)flag);
}
struct AutoRefCount {
    Obj* mpObject;
    AutoRefCount& operator=(Obj* p) {
        if (p != mpObject) {
            Obj* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct cSPTransform_s007d_4a40 {   // size 0x38
    float m[0x38 / 4];
    cSPTransform_s007d_4a40& operator=(const cSPTransform_s007d_4a40& o) {
        for (int i = 0; i < 0x38 / 4; ++i) m[i] = o.m[i];
        return *this;
    }
};
struct Matrix3 { float m[9]; void Assign(const Matrix3& o); };     // 0x41cb40
struct ElemPart { void Init(void* a); };                           // 0x537f40
struct cLabelOps { void Propagate(const void* src); };
typedef void(__thiscall* VCall1)(void*, int);
typedef char(__thiscall* VCall3)(Obj*, int, void*, int);
typedef char(__thiscall* VCall2)(Obj*, int, void*);
typedef int(__thiscall* VCall1i)(void*, int);
struct TransformInit { void* Init(const void* src, void* a, char flag); };
struct IUnk32 { virtual int AddRef(); virtual int Release(); };
struct UnkRef {
    IUnk32* mpObject;
    UnkRef() : mpObject(0) {}
    ~UnkRef() throw() { if (mpObject) mpObject->Release(); }
};
struct cParamRec {
    uint16_t mOffset, mCount;
    cParamRec() : mOffset(0), mCount(0) {}
};
template<class T> struct spvec {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    uint32_t mAlloc[2];
    spvec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~spvec() throw() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin); }
};
struct cEffectParams_s007d_4a40 {
    cParamRec mFloatParams[25];     // +0x00
    spvec<float> mFloatStorage;     // +0x64
    cParamRec mIntParams[10];       // +0x78
    spvec<int> mIntStorage;         // +0xa0
    UnkRef mUnknownParams[9];       // +0xb4
    cEffectParams_s007d_4a40();  // 0x007d55e0 (cEffectParams::cEffectParams_s007d_4a40)
    ~cEffectParams_s007d_4a40();  // 0x007d55e0 (cEffectParams::cEffectParams_s007d_4a40)
    bool Handle(int kind, void* a, int b);
    char Handle2(int kind, void* a);
    void Tick(float param_2, float param_3, int param_4);
    // Swap the (lo,hi) parameter pair while honouring the visibility flag at
    // +0x14 and dropping the previous referenced object at +0x38. The original
    // inlines this block into Handle/Handle2, so keep it inline here too.
    void SetPairVisible(int lo, int hi) {
        char* s = (char*)this;
        char oldVisible = s[0x14];
        if (oldVisible) {
            void** vt = *(void***)s;
            ((VCall1)vt[0xc / 4])(s, 1);
        }
        RefCounted* p = *(RefCounted**)(s + 0x38);
        if (p) {
            *(void**)(s + 0x38) = 0;
            p->Release();
        }
        *(int*)(s + 0x18) = lo;
        *(int*)(s + 0x1c) = hi;
        if (oldVisible) {
            void** vt = *(void***)s;
            ((VCall1)vt[8 / 4])(s, 1);
        }
    }
};
struct EffectCompSet {
    char m_00[0x0c];
    uint32_t mFlags;            // +0x0c
    char m_10[0x20];
    void* mpDescs;              // +0x30
    char m_34[0x54];
    int mId;                    // +0x88
};
struct EffectDesc {             // 0x2c-stride
    char m_00[0x08];
    float* mpValueBegin;        // +0x08
    float* mpValueEnd;          // +0x0c
    char m_10[0x10];
    float mRate;                // +0x20
    int mId;                    // +0x24
    uint8_t mMode;              // +0x28
    char m_29[3];
};
typedef char (__thiscall* EffectHandlerTest)(void*);
typedef void (__thiscall* EffectHandlerApply)(void*, float, float, int);
typedef void (__thiscall* NotifyV70)(void*, void*, int, int, float, int);
typedef void (__thiscall* NotifyV74)(void*, void*, int, float, int);
typedef void (__thiscall* NotifyV80)(void*, void*, int, float*, float*, int);
struct MsgServer {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
    virtual void Send(uint32_t id, void* data, int z);     // +0x14
};
struct MsgPayload {
    void* mpObject;             // +0x00
    int   m_04;                 // +0x04 (unused)
    int   mFlag;                // +0x08
    int   m_0c;                 // +0x0c (unused)
    int   mZero;                // +0x10
};
struct cSPTransformOps { void* Assign(const void* src); };   // 0x537dc0
MsgServer* GetServer_s007d_4a40();                              // 0x883860 EA::Messaging::GetServer
double FUN_007cdb90(float* p);                       // 0x7cdb90
struct TransformBig { void* Init(int a, unsigned pair, float f1, float f2, float f3, float f4,
                       Matrix3 m, Obj* obj); };
struct Elem40 {
    uint16_t a, b;
    float f4, f8, fc, f10;
    Matrix3 mat;        // +0x14
    uint32_t f38;       // +0x38
    AutoRefCount ref;   // +0x3c
    Elem40(const Elem40& o);
};
// ---- items of slice s007d4a40 end

// ---- items of slice s007d56f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  operator delete(void* p) throw();                  // 0xf47380 (same EA allocator free)
inline void* operator new(size_t, void* p) throw() { return p; }
#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct Matrix33 {
    float m[9];
    void Assign(const Matrix33* src) throw();         // 0x41cb40 (Matrix3::Assign)
    Matrix33(const Matrix33& o);                      // same routine, used for by-value copies
    Matrix33() {}
};
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
struct cEffectParams_s007d_56f0 {
    void* vtbl; char pad[0xcc];
    ~cEffectParams_s007d_56f0();                                 // 0x7d4ae0
};
struct cSplitController {                             // size 0x40
    cTransform mLocalXform;                           // +0
    cEffectParams_s007d_56f0* mParams;                           // +0x38
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
cSplitController* __cdecl CtrlCopyBackward(cSplitController* first, cSplitController* last, cSplitController* dest);   // 0x7d5520
cSplitController* __cdecl CtrlMoveRange(cSplitController* first, cSplitController* last, cSplitController* dest);      // 0x7d53a0
void __cdecl CtrlDestroyRange(cSplitController* first, cSplitController* last, cSplitController* dest);                // 0x7d48a0
inline cSplitController* CtrlRelocate(cSplitController* f, cSplitController* l, cSplitController* d) {
    cSplitController* r = CtrlMoveRange(f, l, d);
    CtrlDestroyRange(f, l, d);
    return r;
}
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
struct cAnimationInfo { float mAge, mInvLength, mCurveMultiplier; };   // size 0xc
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
inline void CopyXformHead(cTransform& d, const cTransform& s) {
    d.mFlags = s.mFlags;
    d.mModificationCount = s.mModificationCount;
    d.mTranslation[0] = s.mTranslation[0];
    d.mTranslation[1] = s.mTranslation[1];
    d.mTranslation[2] = s.mTranslation[2];
    d.mScale = s.mScale;
}
__forceinline void CopyXformInline(cTransform& d, const cTransform& s) {
    CopyXformHead(d, s);
    struct Row { float x, y, z; };
    Row r[3];
    for (int k = 0; k < 3; ++k) {
        r[k].x = s.mRotation.m[3 * k];
        r[k].y = s.mRotation.m[3 * k + 1];
        r[k].z = s.mRotation.m[3 * k + 2];
    }
    for (int k = 0; k < 3; ++k) ((Row*)d.mRotation.m)[k] = r[k];
}
char** UninitCopyElem78(char** out, char* first, char* last, char* base, const void* extra);  // 0x7d5aa0
struct Vec78 {
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAlloc;
    Vec78(const Vec78& x);
    void* Allocate(unsigned n, const void* alloc);   // 0x7d48e0
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
cElement** UninitCopyElements(cElement** out, cElement* first, cElement* last, cElement* dest); // 0x007d5aa0 (*out = dest, *out advances)
void      DestroyElementRange(cElement* first, cElement* last);                     // 0x007d4940
struct cSPVector3_s007d_67e0 { float x, y, z; };
struct cSPMatrix3_s007d_67e0 { float m[9]; };
struct cSPTransform_s007d_67e0 {                    // size 0x38
    unsigned short mFlags;               // +0x00
    unsigned short mModificationCount;   // +0x02
    cSPVector3_s007d_67e0     mTranslation;         // +0x04
    float          mScale;               // +0x10
    cSPMatrix3_s007d_67e0     mRotation;            // +0x14
};
struct cSplitInstance {                  // size 0x74
    unsigned char mFlags;                // +0x00
    char _pad[3];
    cSPTransform_s007d_67e0  mInstanceTransform;    // +0x04
    cSPTransform_s007d_67e0  mFinalTransform;       // +0x3c
    cSplitInstance(int a, const cSPTransform_s007d_67e0& x, int b);   // @ 0x007d4a40 (defined in slice s007d4a40)
};
struct cElement {                        // size 0x78
    int           mNextFree;             // +0x00
    cSplitInstance mData;                // +0x04
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
    int insert(const cSplitInstance& value);              // @ 0x0079ff40 (defined in slice s007d4a40)
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
struct cSplitInstanceRef { int mSplitID; int mKey; };
struct cSplitManager_s007d_67e0 {
    char            pad00[4];
    int             mRefCount;              // +0x04
    cSPTransform_s007d_67e0    mComponentTransform;    // +0x08
    ListVector      mSplitClientList;       // +0x40
    cSplitInstanceRef* AddSplitInstance(cSplitInstanceRef* out, int index, int a, int b); // @ 0x007d7640
};
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s007d67e0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
cSplitInstanceList** CopyConstructToPtr(cSplitInstanceList** pDest, const cSplitInstanceList* first, const cSplitInstanceList* last, cSplitInstanceList* dest);  // 0x007d67e0 (stays in the slice: not this object's)
void FillConstructN(cSplitInstanceList* dest, size_type n, const cSplitInstanceList* value);  // 0x007d68f0 (stays in the slice: not this object's)
cSplitInstanceList* CopyConstructRange(const cSplitInstanceList* first, const cSplitInstanceList* last, cSplitInstanceList* dest);  // 0x007d69f0 (stays in the slice: not this object's)
cSplitInstanceList* CopyAssignBackward(const cSplitInstanceList* first, const cSplitInstanceList* last, cSplitInstanceList* dest);  // 0x007d71f0 (stays in the slice: not this object's)
void AssignValueRange(cSplitInstanceList* first, cSplitInstanceList* last, const cSplitInstanceList* value);  // 0x007d7240 (stays in the slice: not this object's)

// ---- items of slice s007d76d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* Sub_7d5d50(void* p);                 // ctor
void  Sub_572680(void* refcountHolder, void* obj);
void* Sub_7d6380(void* p);                 // ctor
void* Sub_7d6440(void* p);                 // ctor
void* Sub_7d55e0(void* p);                 // cEffectParams ctor
void  Sub_7d6b00(void* dst, const void* src); // cEffectParams::operator=
void  Sub_7d4620(void* params, int slot);  // cEffectParams::UnknownStore
void* Sub_7d5240(const void* src);         // build some record
void  Sub_7d7000(void* dst, void* src);
int   Sub_79ab90(int a, void* b, void* c, int d);
void* Sub_7df780(void* p);
void  Sub_4e3260(void* pos, void* value);  // vector<AutoRefCount>::DoInsertValue
void  Sub_4e0e80(void* vec, void* value);  // vector<AutoRefCount>::push_back
void* RBTreeIncrement(void* node);         // eastl::RBTreeIncrement   // 0x00921580 (equiv t2)
struct EffectParamsHelper {
    bool __thiscall GetIntParam(int n, void** outPtr, int* outCount); // 0x00a826c0  cEffectParams::GetIntParam
};
void* ModelManager();
void  AddSplitInstanceRaw(void* mgr, void* xform, int id, int flag); // 0x007d7640 (slice s007d67e0)
struct cGameModelEffect_s007d_76d0 {
    char   pad00[0xc];
    void*  mModelDesc;       // +0x0c
    void*  mUnk10;           // +0x10
    char   pad14[4];
    int    mUnk18;           // +0x18
    int    mUnk1c;           // +0x1c
    int    mUnk20;           // +0x20
    int    mUnk24;           // +0x24
    int    mUnk28;           // +0x28
    float  mUnk2c;           // +0x2c
    float  mUnk30;           // +0x30
    char   pad34[0xa];
    unsigned short mCount3e; // +0x3e
    char   pad40[0xc];
    float  mUnk4c;           // +0x4c
    char   pad50[0x54];
    void*  mParamsObj;       // +0xa4
    void*  mSplitManager;    // +0xa8
    char*  mVecB0;           // +0xac
    char*  mVecB4;           // +0xb0
    char   padB4[0xc];       // +0xb4
    void*  mModelManager;    // +0xc0
    void*  mUnkC4;           // +0xc4

    bool HandleSplitCommand(int a, void* desc, int value, int index, int count);
    void Init(int a, void* desc, int value);
};
// ---- items of slice s007d76d0 end

// @ 0x007d4620
void cEffectParams::UnknownStore(int idx, IUnknown32* p)
{
    IUnknown32* old = mUnknown[idx];
    if (p != old) {
        if (p) p->AddRef();
        mUnknown[idx] = p;
        if (old) old->Release();
    }
}

// @ 0x007d4670
void cEffectNode::Tick(void* arg)
{
    char* s = (char*)this;
    if (s[0x14]) {
        s[0x14] = 0;
        unsigned n = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
        for (unsigned i = 0; i < n; ++i) {
            void* c = *(void**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
            ((void (__thiscall*)(void*, void*))(*(void***)c)[0xc / 4])(c, arg);
        }
        void* p = *(void**)(s + 0x38);
        if (p && *(int*)((char*)p + 0x40) < 2) {
            void* const pOwner = *(void**)p;   // +0x00: the released object
            ((void (__thiscall*)(void*, void*, int))(*(void***)pOwner)[0x16c / 4])(pOwner, p, 0);
        }
        cEffectMsgContext* const ctx = (cEffectMsgContext*)*(void**)(s + 0xc);
        if ((ctx->mFlags >> 2) & 1) {
            cMessageServer* const pServer = GetServer();
            if (pServer) {
                cEffectMessage msg;
                msg.mpSource = p;
                msg.mEventType = 0;
                msg.mKey = 0;
                ((void (__thiscall*)(void*, uint32_t, cEffectMessage*, int))(*(void***)pServer)[0x14 / 4])(
                    pServer, ctx->mMessageId, &msg, 0);
            }
        }
    }
}

// @ 0x007d4730
char cEffectNode::HandleParam(int kind, float* value, void* extra)
{
    char* s = (char*)this;
    char any = 0;
    switch (kind) {
        case 4:
            *(float*)(s + 0x2c) = *(float*)(*(int*)(s + 0xc) + 0x20) * value[0];
            any = 1; break;
        case 5:
            *(float*)(s + 0x20) = *(float*)(*(int*)(s + 0xc) + 0x14) * value[0];
            *(float*)(s + 0x24) = value[1] * *(float*)(*(int*)(s + 0xc) + 0x18);
            *(float*)(s + 0x28) = value[2] * *(float*)(*(int*)(s + 0xc) + 0x1c);
            any = 1; break;
        case 0x101:
            *(float*)(s + 0x80) = value[1];
            *(float*)(s + 0x88) = value[2];
            *(float*)(s + 0x84) = value[4];
            *(float*)(s + 0x8c) = value[5];
            any = 1; break;
        default: break;
    }
    unsigned n = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < n; ++i) {
        void* c = *(void**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = (*(char(__thiscall**)(void*, int, float*, void*))((*(void***)c)[0x1c / 4]))(c, kind, value, extra);
        if (r || any) any = 1;
    }
    return any;
}

// @ 0x007d4820
void EffOwner::SetVisible(int param)
{
    *(uint8_t*)((char*)this + 0x15) = (uint8_t)param;
    _ReadWriteBarrier();
    unsigned count = (unsigned)((*(char**)((char*)this + 0xb0) - *(char**)((char*)this + 0xac)) >> 6);
    if (count != 0) {
        for (unsigned i = 0; i < count; ++i) {
            EffComp* c = *(EffComp**)(*(char**)((char*)this + 0xac) + i * 0x40 + 0x3c);
            c->SetFlag(param);
        }
    }
    void* p = *(void**)((char*)this + 0x38);
    if (p) {
        if ((char)param) *(uint32_t*)((char*)p + 4) |= 1;
        else *(uint32_t*)((char*)p + 4) &= ~1u;
    }
}

// @ 0x007d48e0
VecOut* VecOut::Allocate(unsigned n, void* alloc)
{
    void* buf = n ? operator new(n * 0x78, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    b = buf;
    e = buf;
    c = (char*)buf + n * 0x78;
    return this;
}

// @ 0x007d4980
void XformVec::DoInsertValue(const void* src)
{
    ((cSPTransformOps_s007d_3930*)((char*)this + 8))->Assign(src);
    unsigned count = (unsigned)((mpEnd - mpBegin) / 0x1c);
    unsigned off = 0;
    if (count == 0) return;
    do {
        char* base = *(char**)((char*)this + 0x40);
        int* pm = (int*)*(void**)(base + off + 4);
        int* last = (int*)*(void**)(base + off + 8);
        int* pb = last;
        while (pm != last && *pm != -2) pm = (int*)((char*)pm + 0x78);
        while (pm != pb) {
            ((cLabelOps_s007d_3930*)((char*)pm + 4))->Propagate((char*)this + 8);
            pm = (int*)((char*)pm + 0x78);
            if (pm != last) {
                while (*pm != -2) {
                    pm = (int*)((char*)pm + 0x78);
                    if (pm == last) break;
                }
            }
        }
        off += 0x1c;
    } while (--count);
}

// @ 0x007d4a40
void* TransformInit::Init(const void* src, void* a, char flag)
{
    void* self = this;
    char* s = (char*)self; const char* o = (const char*)src;
    s[0] = flag;
    *(uint16_t*)(s + 4) = *(const uint16_t*)(o);
    *(uint16_t*)(s + 6) = *(const uint16_t*)(o + 2);
    *(float*)(s + 8) = *(const float*)(o + 4);
    *(float*)(s + 0xc) = *(const float*)(o + 8);
    *(float*)(s + 0x10) = *(const float*)(o + 0xc);
    *(float*)(s + 0x14) = *(const float*)(o + 0x10);
    ((Matrix3*)(s + 0x18))->Assign(*(const Matrix3*)(o + 0x14));
    *(uint16_t*)(s + 0x3e) = 0;
    *(uint16_t*)(s + 0x3c) = 0;
    *(float*)(s + 0x40) = *(const float*)0x1637118;
    *(float*)(s + 0x44) = *(const float*)0x163711c;
    *(float*)(s + 0x48) = *(const float*)0x1637120;
    *(float*)(s + 0x4c) = 1.0f;
    ((Matrix3*)(s + 0x50))->Assign(*(const Matrix3*)0x163725c);
    ((cLabelOps*)self)->Propagate(a);
    return self;
}

// @ 0x007d4ae0
cEffectParams_s007d_4a40::~cEffectParams_s007d_4a40()
{
}

// @ 0x007d4b60
bool cEffectParams_s007d_4a40::Handle(int kind, void* pa, int n)
{
    char* s = (char*)this;
    int* a = (int*)pa;
    char changed = 0;
    char oldVisible = 0;
    if (kind == 6) {
        if (*(int*)(s + 0x18) != a[0] || (n == 2 && *(int*)(s + 0x1c) != a[1])) {
            oldVisible = s[0x14];
            if (oldVisible) {
                ((VCall1)(*(void***)s)[0xc / 4])(s, 1);
            }
            RefCounted* p = *(RefCounted**)(s + 0x38);
            if (p) {
                *(void**)(s + 0x38) = 0;
                p->Release();
            }
            *(int*)(s + 0x18) = a[0];
            if (n >= 2) *(int*)(s + 0x1c) = a[1];
            if (oldVisible) {
                ((VCall1)(*(void***)s)[8 / 4])(s, 1);
            }
        }
        changed = 1;
    }
    unsigned cnt = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < cnt; ++i) {
        Obj* c = *(Obj**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = ((VCall3)(*(void***)c)[0x20 / 4])(c, kind, pa, n);
        if (r || changed) changed = 1;
    }
    return changed != 0;
}

// @ 0x007d4c60
char cEffectParams_s007d_4a40::Handle2(int kind, void* pa)
{
    char* s = (char*)this;
    int* a = (int*)pa;
    char changed = 0;
    if (kind == 1) {
        if (*(void**)(s + 0x38)) {
            ((RefCounted*)*(void**)(s + 0x38))->mHandle.operator=((AddRefObj*)a);
            changed = 1;
        }
    } else if (kind == 3) {
        int n = a[3];
        int i;
        for (i = 0; i < n; ++i) {
            if (*(int*)((char*)a + 0x18 + i * 0x10) == (int)*(uint8_t*)(*(int*)(s + 0xc) + 0x85)) break;
        }
        if (i < n) {
            // The matched key sits at record+8, so the (lo,hi) pair lives one
            // stride on from the key slot.
            int lo = *(int*)((char*)a + (i + 1) * 0x10);
            int hi = *(int*)((char*)a + (i + 1) * 0x10 + 4);
            if ((lo & hi) != -1) {
                char oldVisible = s[0x14];
                if (oldVisible) {
                    void** vt = *(void***)s;
                    ((VCall1)vt[0xc / 4])(s, 1);
                }
                RefCounted* p = *(RefCounted**)(s + 0x38);
                if (p) {
                    *(void**)(s + 0x38) = 0;
                    p->Release();
                }
                *(int*)(s + 0x18) = lo;
                *(int*)(s + 0x1c) = hi;
                if (oldVisible) {
                    void** vt = *(void***)s;
                    ((VCall1)vt[8 / 4])(s, 1);
                }
            }
        }
        return 1;
    } else if (kind == 6 && *(int*)(*(int*)(s + 0xc) + 0x2c) == 0) {
        int r = ((VCall1i)(*(void***)a)[0xc / 4])(a, 0);
        if (r) *(int*)(s + 0xc4) = r;
    }
    unsigned cnt = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < cnt; ++i) {
        Obj* c = *(Obj**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = ((VCall2)(*(void***)c)[0x24 / 4])(c, kind, pa);
        if (r || changed) changed = 1;
    }
    return changed;
}

// @ 0x007d4dd0
void cEffectParams_s007d_4a40::Tick(float param_2, float param_3, int param_4)
{
    char* s = (char*)this;

    // Phase 1: drain the 0x40-stride handler array at +0xac/+0xb0.  An empty
    // array goes straight to the target update.  If any handler reports a
    // change (its +0x10 predicate), apply it (+0x14) and fall through to the
    // target update as well; otherwise keep looking.
    {
        char* hbase = (char*)*(int*)(s + 0xac);
        char* hend = (char*)*(int*)(s + 0xb0);
        if (hbase == hend)
            goto update;
        int n = (int)(hend - hbase) >> 6;
        bool none = true;
        if (n > 0) {
            int off = 0;
            int left = n;
            do {
                void* h = *(void**)(hbase + off + 0x3c);
                if (((EffectHandlerTest)(*(void***)h)[0x10 / 4])(h)) {
                    none = false;
                    ((EffectHandlerApply)(*(void***)h)[0x14 / 4])(h, param_2, param_3, param_4);
                }
                off += 0x40;
            } while (--left);
            if (!none)
                goto update;
        }
    }

    // Phase 2: no handler changed anything.  If every 0x1c-stride record in
    // the range set at +0xa8 has a zero at +0x18, the effect is finished:
    // call vtable[3](1) and return.
    {
        int set = *(int*)(s + 0xa8);
        int diff = *(int*)(set + 0x44) - *(int*)(set + 0x40);
        int sign = diff >> 31;
        int n = diff / 0x1c + sign;
        unsigned cnt = (unsigned)(n - sign);
        char* rec = (char*)(*(int*)(set + 0x40) + 0x18);
        for (unsigned i = 0; i < cnt; ++i) {
            if (*(int*)rec != 0)
                goto update;
            rec += 0x1c;
        }
        ((VCall1)(*(void***)s)[0xc / 4])(s, 1);
        return;
    }

update:
    // Phase 3: push the template transform at +0x3c into the target object at
    // +0x38, then interpolate the target's scale/position by param_3.
    {
        char* tgt = *(char**)(s + 0x38);
        cSPTransformOps* xf = (cSPTransformOps*)(tgt + 8);
        xf->Assign(s + 0x3c);
        *(float*)(tgt + 0x4c) = *(float*)(s + 0x20);
        *(float*)(tgt + 0x50) = *(float*)(s + 0x24);
        *(float*)(tgt + 0x54) = *(float*)(s + 0x28);
        *(float*)(tgt + 0x58) = *(float*)(s + 0x2c);
        *(uint32_t*)(tgt + 4) |= 2;

        float f0 = *(float*)(s + 0x80);
        float f1 = *(float*)(s + 0x84);
        if (f0 != 1.0f || f1 != 1.0f) {
            tgt = *(char**)(s + 0x38);
            *(uint16_t*)(tgt + 8) = (uint16_t)(*(uint16_t*)(tgt + 8) | 1);
            *(uint16_t*)(tgt + 0x0a) = (uint16_t)(*(uint16_t*)(tgt + 0x0a) + 1);
            // Each step is rounded to float, matching the original's
            // subss/mulss/addss/mulss chain (not 80-bit x87 intermediates).
            float df = f1 - f0;
            float mf = df * param_3;
            float sf = mf + f0;
            *(float*)(tgt + 0x18) = sf * *(float*)(tgt + 0x18);
        }
        tgt = *(char**)(s + 0x38);
        float g0 = *(float*)(s + 0x88);
        float g1 = *(float*)(s + 0x8c);
        {
            float dg = g1 - g0;
            float mg = dg * param_3;
            float sg = mg + g0;
            *(float*)(tgt + 0x58) = sg * *(float*)(tgt + 0x58);
        }

        // Phase 4: when the 0xc-stride animation array at +0x90/+0x94 is
        // non-empty and the target carries flag bit 14, advance every entry.
        if (*(int*)(s + 0x90) != *(int*)(s + 0x94) &&
            (((*(uint32_t*)(tgt + 4)) >> 14) & 1)) {
            int count = (*(int*)(s + 0x94) - *(int*)(s + 0x90)) / 0xc;
            float dx = *(float*)(s + 0x74) - *(float*)(s + 0x40);
            float dy = *(float*)(s + 0x78) - *(float*)(s + 0x44);
            float dz = *(float*)(s + 0x7c) - *(float*)(s + 0x48);
            float dist = (float)(sqrt((double)dx * dx + (double)dy * dy + (double)dz * dz)
                                 / (double)*(float*)(s + 0x4c));
            if (count != 0) {
                void* notify = *(void**)(s + 0xc4);
                EffectDesc* descBase = (EffectDesc*)(*(EffectCompSet**)(s + 0x0c))->mpDescs;
                int animOff = 0;
                int descOff = 0;
                int left = count;
                do {
                    float* pf = (float*)(*(int*)(s + 0x90) + animOff);
                    EffectDesc* d = (EffectDesc*)((char*)descBase + descOff);
                    float rate = d->mRate;
                    float step = param_2;
                    if (0.0f < rate)
                        step = rate * dist;
                    float v0 = step * pf[1];
                    float v = v0 + pf[0];
                    pf[0] = v;
                    if (1.0f < v) {
                        uint8_t mode = d->mMode;
                        if (mode == 1) {
                            pf[0] = 1.0f;
                        } else if (mode == 2) {
                            pf[0] = 1.0f;
                            ((VCall1)(*(void***)s)[0xc / 4])(s, 0);
                        } else {
                            pf[0] = 0.0f;
                            double fv = FUN_007cdb90((float*)d);
                            pf[1] = (fv <= 0.0) ? 0.0f : 1.0f / (float)fv;
                        }
                    }
                    if (*(char*)(s + 0x16) == 0)
                        ((NotifyV70)(*(void***)notify)[0x70 / 4])
                            (notify, *(void**)(s + 0x38), d->mId, 3, 0.0f, 0);
                    float outA;
                    ((NotifyV80)(*(void***)notify)[0x80 / 4])
                        (notify, *(void**)(s + 0x38), d->mId, &outA, (float*)&param_4, 0);
                    float w = pf[0];
                    float* vals = d->mpValueBegin;
                    int idx = (int)(d->mpValueEnd - d->mpValueBegin) - 1;
                    float out;
                    if (idx == 0) {
                        out = vals[0];
                    } else {
                        float fi = (float)idx;
                        if (idx < 0)
                            fi += 4294967296.0f;
                        w = fi * w;
                        idx = (int)w;
                        float frac = w - (float)idx;
                        if (frac <= 0.0f) {
                            out = vals[idx];
                        } else {
                            float lo = vals[idx];
                            float hi = vals[idx + 1];
                            float dh = hi - lo;
                            float mh = dh * frac;
                            out = mh + lo;
                        }
                    }
                    float dt = *(float*)&param_4 - outA;
                    float pw = pf[2] * out;
                    float arg = pw * dt;
                    ((NotifyV74)(*(void***)notify)[0x74 / 4])
                        (notify, *(void**)(s + 0x38), d->mId, arg, 0);
                    animOff += 0xc;
                    descOff += 0x2c;
                } while (--left);
            }
            *(float*)(s + 0x74) = *(float*)(s + 0x40);
            *(float*)(s + 0x78) = *(float*)(s + 0x44);
            *(float*)(s + 0x7c) = *(float*)(s + 0x48);
        }

        // Phase 5: once the target is live, notify it and broadcast the
        // completion through the messaging server.
        if (*(char*)(s + 0x16) == 0) {
            char* t2 = *(char**)(s + 0x38);
            if (((*(uint32_t*)(t2 + 4)) >> 14) & 1) {
                ((VCall1)(*(void***)t2)[0x16c / 4])(t2, 1);
                EffectCompSet* comps = *(EffectCompSet**)(s + 0x0c);
                if (((comps->mFlags) >> 2) & 1) {
                    MsgServer* srv = GetServer_s007d_4a40();
                    if (srv) {
                        MsgPayload p;
                        p.mpObject = t2;
                        p.mFlag = 1;
                        p.mZero = 0;
                        srv->Send((uint32_t)comps->mId, &p, 0);
                    }
                }
                *(char*)(s + 0x16) = 1;
            }
        }
    }
}

// @ 0x007d5240
void* TransformBig::Init(int a, unsigned pair, float f1, float f2, float f3, float f4, Matrix3 m, Obj* obj)
{
    void* self = this;
    char* s = (char*)self;
    *(uint16_t*)(s) = (uint16_t)pair;
    *(uint16_t*)(s + 2) = (uint16_t)(pair >> 16);
    *(float*)(s + 4) = f1;
    *(float*)(s + 8) = f2;
    *(float*)(s + 0xc) = f3;
    *(float*)(s + 0x10) = f4;
    ((Matrix3*)(s + 0x14))->Assign(m);
    *(int*)(s + 0x38) = a;
    *(void**)(s + 0x3c) = 0;
    ((AutoRefCount*)(s + 0x3c))->operator=(obj);
    return self;
}

// @ 0x007d5300
Elem40::Elem40(const Elem40& o)
{
    a = o.a; b = o.b;
    f4 = o.f4; f8 = o.f8; fc = o.fc; f10 = o.f10;
    mat.Assign(o.mat);
    f38 = o.f38;
    // The copy ctor stores the source pointer first (no release of the
    // not-yet-constructed member) and then takes its own reference.
    Obj* p = o.ref.mpObject;
    ref.mpObject = p;
    if (p) p->AddRef();
}

// @ 0x007d53a0
void* CopyElemRange40(void* first, void* last, void* dst)
{
    char* f = (char*)first; char* l = (char*)last; char* d = (char*)dst;
    while (f != l) {
        *(uint16_t*)(d) = *(const uint16_t*)(f);
        *(uint16_t*)(d + 2) = *(const uint16_t*)(f + 2);
        *(float*)(d + 4) = *(const float*)(f + 4);
        *(float*)(d + 8) = *(const float*)(f + 8);
        *(float*)(d + 0xc) = *(const float*)(f + 0xc);
        *(float*)(d + 0x10) = *(const float*)(f + 0x10);
        *(cSPTransform_s007d_4a40*)(d + 0x14) = *(const cSPTransform_s007d_4a40*)(f + 0x14);
        *(int*)(d + 0x38) = *(const int*)(f + 0x38);
        Obj* p = *(Obj**)(f + 0x3c);
        *(Obj**)(d + 0x3c) = p;
        if (p) p->AddRef();
        f += 0x40; d += 0x40;
    }
    return d;
}

// @ 0x007d5520
void* CopyBackwardsTransforms(void* first, void* last, void* dst)
{
    char* f = (char*)first; char* l = (char*)last; char* d = (char*)dst;
    if (l == f) return d;
    do {
        l -= 0x40; d -= 0x40;
        *(cSPTransform_s007d_4a40*)(d) = *(const cSPTransform_s007d_4a40*)(l);
        *(int*)(d + 0x38) = *(const int*)(l + 0x38);
        AutoRefCount* r = (AutoRefCount*)(d + 0x3c);
        r->operator=(*(Obj**)(l + 0x3c));
    } while (l != f);
    return d;
}

// @ 0x007d5590
void* CopyElem38(void* self, void* a, const void* src)
{
    char* s = (char*)self; const char* o = (const char*)src;
    *(uint16_t*)(s) = *(const uint16_t*)(o);
    *(uint16_t*)(s + 2) = *(const uint16_t*)(o + 2);
    *(float*)(s + 4) = *(const float*)(o + 4);
    *(float*)(s + 8) = *(const float*)(o + 8);
    *(float*)(s + 0xc) = *(const float*)(o + 0xc);
    *(float*)(s + 0x10) = *(const float*)(o + 0x10);
    ((Matrix3*)(s + 0x14))->Assign(*(const Matrix3*)(o + 0x14));
    ((ElemPart*)s)->Init(a);
    return self;
}

// @ 0x007d55e0
cEffectParams_s007d_4a40::cEffectParams_s007d_4a40()
{
}

// @ 0x007d56f0
void cGameModelEffect::SetTransforms(const cTransform& source, const cTransform& rigid)
{
    cTransform xf;
    if (mSplitManager.mpObject) {
        CopyXformHead(xf, source);
        xf.mRotation.Assign(&source.mRotation);
        xf.mScale = mGameModelScale * xf.mScale;
        xf.mFlags |= 1;
        xf.mModificationCount += 1;
        mSplitManager.mpObject->SetComponentTransform(xf);
        unsigned n = (unsigned)(mSplitControllers.mpEnd - mSplitControllers.mpBegin);
        for (unsigned i = 0; i < n; ++i) {
            CopyXformInline(xf, source);
            xf.Concat(mSplitControllers.mpBegin[i].mLocalXform);
            xf.mScale = mGameModelScale * xf.mScale;
            xf.mFlags |= 1;
            xf.mModificationCount += 1;
            mSplitControllers.mpBegin[i].mComponent->SetTransforms(xf, rigid);
        }
    }
    CopyXformInline(xf, rigid);
    xf.Concat(source);
    mComponentXform = xf;
    mComponentXform.mScale = mGameModelScale * mComponentXform.mScale;
    mComponentXform.mFlags |= 1;
    mComponentXform.mModificationCount += 1;
    if (mGameModel.mpObject) mGameModel.mpObject->mXform = mComponentXform;
}

// @ 0x007d5dc0
void cGameModelEffect::Unload()
{
    unsigned n = (unsigned)(mSplitControllers.mpEnd - mSplitControllers.mpBegin);
    for (unsigned i = 0; i < n; ++i) {
        mSplitControllers.mpBegin[i].mComponent->Dispose();
        cEffectParams_s007d_56f0* p = mSplitControllers.mpBegin[i].mParams;
        if (p) {
            p->~cEffectParams_s007d_56f0();
            operator delete(p);
        }
    }
    cMWModel* m = mGameModel.mpObject;
    if (m) {
        mGameModel.mpObject = 0;
        ReleaseModel(m);
    }
    mModelManager = 0;
}

// @ 0x007d6320
Vec78::Vec78(const Vec78& x)
{
    Allocate((unsigned)((x.mpEnd - x.mpBegin) / 0x78), &x.mAlloc);
    char* out;
    UninitCopyElem78(&out, x.mpBegin, x.mpEnd, mpBegin, &x);
    mpEnd = out;
}

// @ 0x007d6620
void CtrlVec::DoInsertValue(cSplitController* position, const cSplitController& value)
{
    if (mpEnd != mpCapacity) {
        const cSplitController* pValue = &value;
        if (position <= pValue && pValue < mpEnd) ++pValue;
        new (mpEnd) cSplitController(*(mpEnd - 1));
        CtrlCopyBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        unsigned nPrev = (unsigned)(mpEnd - mpBegin);
        unsigned nNew = nPrev ? nPrev * 2 : 1;
        cSplitController* pNew = nNew ? (cSplitController*)operator new(nNew * sizeof(cSplitController), "App", 0, 0, EASTL_ALLOC_FILE, 0xd1) : 0;
        cSplitController* pNewPos = CtrlRelocate(mpBegin, position, pNew);
        if (pNewPos) new (pNewPos) cSplitController(value);
        cSplitController* pNewEnd = CtrlRelocate(position, mpEnd, pNewPos + 1);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + nNew;
    }
}

// @ 0x007d72e0
void ListVector::DoInsertValues(cSplitInstanceList* position, size_type n, const cSplitInstanceList& value)
{
    if (n > (size_type)(mpCapacity - mpEnd)) {
        const size_type nPrevSize = (size_type)(mpEnd - mpBegin);
        const size_type nPositionIndex = (size_type)(position - mpBegin);
        size_type nNewCapacity = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const size_type nNewSize = nPrevSize + n;
        if (nNewSize > nNewCapacity)
            nNewCapacity = nNewSize;
        cSplitInstanceList* pNewData = (cSplitInstanceList*)
            operator new[](nNewCapacity * sizeof(cSplitInstanceList), ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1); // 0x00f473a0
        cSplitInstanceList* pNewEnd = CopyConstructRange(mpBegin, position, pNewData);
        FillConstructN(pNewEnd, n, &value);
        cSplitInstanceList* pNewEnd2 = CopyConstructRange(position, mpEnd, pNewEnd + n);
        DestroyElementRange((cElement*)mpBegin, (cElement*)position);
        DestroyElementRange((cElement*)position, (cElement*)mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            ea_free(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd2;
        mpCapacity = pNewData + nNewCapacity;
    } else if (n != 0) {
        cSplitInstanceList tmp(value);
        const size_type nElemsAfter = (size_type)(mpEnd - position);
        if (n < nElemsAfter) {
            cSplitInstanceList* pOldEnd = mpEnd;
            cSplitInstanceList* pSplit = mpEnd - n;
            CopyConstructToPtr(&pOldEnd, pSplit, mpEnd, mpEnd);
            mpEnd = mpEnd + n;
            CopyAssignBackward(position, pSplit, pOldEnd);
            AssignValueRange(position, position + n, &tmp);
        } else {
            FillConstructN(mpEnd, n - nElemsAfter, &tmp);
            cSplitInstanceList* pOldEnd = mpEnd;
            mpEnd = mpEnd + (n - nElemsAfter);
            CopyConstructToPtr(&pOldEnd, position, pOldEnd, mpEnd);
            mpEnd = mpEnd + nElemsAfter;
            AssignValueRange(position, pOldEnd, &tmp);
        }
    }
}

// @ 0x007d7640
cSplitInstanceRef* cSplitManager_s007d_67e0::AddSplitInstance(cSplitInstanceRef* out, int index, int a, int b)
{
    ListVector& list = mSplitClientList;
    if ((int)(list.mpEnd - list.mpBegin) <= index)
        list.resize((size_type)index + 1);
    cSplitInstanceList* pList = list.mpBegin + index;
    int key = pList->insert(cSplitInstance(a, mComponentTransform, b));
    out->mSplitID = index;
    out->mKey = key;
    return out;
}

// @ 0x007d76d0
bool cGameModelEffect_s007d_76d0::HandleSplitCommand(int a, void* desc, int value, int index, int count)
{
    char* rec = (char*)(index * 0x68 + *(int*)(*(int*)((char*)mModelDesc + 0x58)));
    unsigned char kind = (unsigned char)rec[0];
    if (kind == 0) {
        if (count < *(int*)(rec + 4))
            return false;
        void* obj = operator new[](0x28, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        if (obj != 0) {
            if (obj != 0)
                obj = Sub_7d6380(obj);
        }
        if (obj != 0)
            *(int*)((char*)obj + 4) += 1;
        Sub_4e0e80((char*)mParamsObj + 0xc, &obj);
        if (obj != 0) {
            int rc = *(int*)((char*)obj + 4) - 1;
            *(int*)((char*)obj + 4) = rc;
            if (rc == 0) {
                *(int*)((char*)obj + 4) = 1;
                ((void(__thiscall*)(void*))*(void**)*(void**)obj)(obj);
            }
        }
    } else if (kind == 1) {
        if (mSplitManager == 0) {
            void* mgr = operator new[](0x54, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
            if (mgr != 0)
                mgr = Sub_7d5d50(mgr);
            Sub_572680(&mSplitManager, mgr);
        }
        void* elem = operator new[](0x38, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        void* built = 0;
        if (elem != 0)
            built = Sub_7d6440(elem);
        if (built != 0)
            ((void(__thiscall*)(void*))*(void**)*(void**)built)(built);
        void* params = operator new[](0xd8, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        if (params != 0)
            params = Sub_7d55e0(params);
        if (value != 0)
            Sub_7d6b00(params, (void*)value);
        Sub_7d4620(params, 5);
        void** dvt = *(void***)desc;
        ((void(__thiscall*)(void*, int, int, int, int))dvt[0x70 / 4])(desc, 2, *(int*)(rec + 4), (int)mUnk10, (int)mUnk10);
        void* rec2 = Sub_7d5240(params);
        Sub_7d7000((char*)mSplitManager + 0xac, rec2);
        if (built != 0)
            ((void(__thiscall*)(void*))(*(void***)built)[0x38 / 4])(built);
        void* list = *(void**)(mVecB0 - 4);
        ((void(__thiscall*)(void*, void*, void*, void*))(*(void***)list)[0])(list, (void*)a, desc, params);
        void* list2 = *(void**)(mVecB0 - 4);
        ((void(__thiscall*)(void*, int))(*(void***)list2)[0x28 / 4])(list2, (int)(unsigned char)rec[5] /* placeholder */);
        if (built != 0)
            ((void(__thiscall*)(void*))(*(void***)built)[1])(built);
    } else if (kind == 2) {
        if (mSplitManager == 0) {
            void* mgr = operator new[](0x54, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
            if (mgr != 0)
                mgr = Sub_7d5d50(mgr);
            Sub_572680(&mSplitManager, mgr);
        }
        if (*(void**)(rec + 0x54) != rec + 0x50) {
            void* node = *(void**)(rec + 0x54);
            do {
                AddSplitInstanceRaw(mSplitManager, rec + 8, *(int*)((char*)node + 0x10), 2);
                node = RBTreeIncrement(node);
            } while (node != rec + 0x50);
            return true;
        }
    }
    return true;
}

// @ 0x007d7a10
void cGameModelEffect_s007d_76d0::Init(int a, void* desc, int value)
{
    int descObj = *(int*)((char*)mModelDesc + 0x0c);
    (void)descObj;
    void* base = (void*)((char*)mModelDesc);
    int* vecBegin = (int*)((char*)base + 0x44);
    int* vecEnd = (int*)((char*)base + 0x48);
    if (vecBegin[0] != vecEnd[0]) {
        void* holder = operator new[](0x20, ALLOC_NAME, 0, 0, 0, 0);
        if (holder != 0) {
            *(int*)((char*)holder + 4) = 0;
            *(int*)((char*)holder + 8) = 4;
            *(int*)((char*)holder + 0xc) = 0;
            *(int*)((char*)holder + 0x10) = 0;
            *(int*)((char*)holder + 0x14) = 0;
            *(void**)holder = (void*)0x013ebc50;
        }
        void* old = mParamsObj;
        if (holder != old) {
            if (holder != 0)
                *(int*)((char*)holder + 4) += 1;
            mParamsObj = holder;
            if (old != 0) {
                int rc = *(int*)((char*)old + 4) - 1;
                *(int*)((char*)old + 4) = rc;
                if (rc == 0) {
                    *(int*)((char*)old + 4) = 1;
                    ((void(__thiscall*)(void*))*(void**)*(void**)old)(old);
                }
            }
        }
        int nDesc = (*(int*)((char*)base + 0x5c) - *(int*)((char*)base + 0x58)) / 0x68;
        int nCmd = (*(int*)((char*)base + 0x48) - *(int*)((char*)base + 0x44)) >> 3;
        int i = 0;
        for (int cmd = 0; cmd < nCmd; ++cmd) {
            while (i < nDesc && HandleSplitCommand(a, desc, value, i, cmd))
                ++i;
            int entry = *(int*)((char*)base + 0x44) + cmd * 8;
            void* comp = ((void*(__thiscall*)(void*, int, void*, void*))
                          (*(void***)desc)[0x74 / 4])(desc, 0x10, *(void**)(entry), mUnk10);
            void* made = Sub_7df780((char*)comp + 8);
            void* ref = (void*)Sub_79ab90((int)*(char*)(entry + 4), made, comp, (int)*(char*)(entry + 5));
            if (ref != 0)
                *(int*)((char*)ref + 4) += 1;
            void* pobj = mParamsObj;
            void** slot = *(void***)((char*)pobj + 0x10);
            if (slot < *(void***)((char*)pobj + 0x14)) {
                *(void***)((char*)pobj + 0x10) = slot + 1;
                if (slot != 0) *slot = ref;
            } else {
                Sub_4e3260(slot, &ref);
            }
            if (ref != 0) {
                int rc = *(int*)((char*)ref + 4) - 1;
                *(int*)((char*)ref + 4) = rc;
                if (rc == 0) {
                    *(int*)((char*)ref + 4) = 1;
                    ((void(__thiscall*)(void*))*(void**)*(void**)ref)(ref);
                }
            }
            ea_free(made);
        }
        for (; i < nDesc; ++i)
            HandleSplitCommand(a, desc, value, i, 0x7fffffff);
    }
    mUnk18 = *(int*)((char*)base + 0x24);
    mUnk1c = *(int*)((char*)base + 0x28);
    if (value != 0) {
        void* outPtr;
        int outCount;
        if (((EffectParamsHelper*)(void*)value)->GetIntParam(6, &outPtr, &outCount)) {
            mUnk18 = *(int*)outPtr;
            if (outCount > 1)
                mUnk1c = *(int*)((char*)outPtr + 4);
        }
    }
    mUnk20 = *(int*)((char*)base + 0x14);
    mUnk24 = *(int*)((char*)base + 0x18);
    mUnk28 = *(int*)((char*)base + 0x1c);
    mUnk2c = *(float*)((char*)base + 0x20);
    float s = *(float*)((char*)base + 0x10);
    mUnk30 = s;
    mCount3e += 1;
    mUnk4c = s;
    void* mm = ModelManager();
    mModelManager = mm;
    int m = *(int*)((char*)base + 0x2c);
    if (m == 0)
        mUnkC4 = ((void*(__thiscall*)(void*))(*(void***)mm)[0x20 / 4])(mm);
    else
        mUnkC4 = ((void*(__thiscall*)(void*, int))(*(void***)mm)[0x1c / 4])(mm, m);
}
