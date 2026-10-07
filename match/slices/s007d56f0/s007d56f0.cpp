// SP::cGameModelEffect / SP::cSplitManager cluster (0x007d56f0..0x007d67xx).
// Retail layout of cGameModelEffect is the 2008 PDB layout shifted by +4/+8 (see members).
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

void* operator new[](size_t size);
void  operator delete[](void* p) throw();
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void  operator delete(void* p) throw();
inline void* operator new(size_t, void* p) throw() { return p; }

#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ------------------------------------------------------------------ math / transform
struct Matrix33 {
    float m[9];
    void Assign(const Matrix33* src) throw();         // 0x41cb40 (Matrix3::Assign)
    Matrix33(const Matrix33& o);                      // same routine, used for by-value copies
    Matrix33() {}
};
extern const Matrix33 g_matIdentityA;                 // 0x1637360 (effect-component rotation)
extern const Matrix33 g_matIdentityB;                 // 0x163725c (split-manager rotation)
extern const float g_vecInit[3];                      // 0x16371dc
extern const float g_vecInitB[3];                     // 0x1637118
extern const float g_one;                             // 0x1485720
extern const float g_radiusInit;                      // 0x14123b0 (1e-5)

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

// ------------------------------------------------------------------ ref-counted helpers
struct RefObj {                                       // RefCountTemplate<int>: vptr + count
    RefObj() : mnRefCount(0) {}
    virtual ~RefObj() {}                              // slot 0: scalar deleting dtor
    int mnRefCount;                                   // +4
};
inline void ReleaseRef(RefObj* p) {                   // inline RefCountTemplate::Release
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
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13();
    virtual bool QueryModels(const float* pos, float radius, void* outVec, void* filter);   // +0x38
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19(); virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31(); virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35(); virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39(); virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44(); virtual void w45(); virtual void w46(); virtual void w47(); virtual void w48(); virtual void w49(); virtual void w50(); virtual void w51(); virtual void w52(); virtual void w53(); virtual void w54(); virtual void w55(); virtual void w56(); virtual void w57(); virtual void w58(); virtual void w59(); virtual void w60(); virtual void w61(); virtual void w62(); virtual void w63(); virtual void w64(); virtual void w65(); virtual void w66(); virtual void w67(); virtual void w68(); virtual void w69(); virtual void w70(); virtual void w71(); virtual void w72(); virtual void w73(); virtual void w74(); virtual void w75(); virtual void w76(); virtual void w77(); virtual void w78(); virtual void w79(); virtual void w80(); virtual void w81(); virtual void w82(); virtual void w83(); virtual void w84(); virtual void w85(); virtual void w86(); virtual void w87(); virtual void w88(); virtual void w89(); virtual void w90();
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

struct IComponent {                                   // EA::Swarm::cIComponent
    virtual void Initialize(void* world, void* manager, void* params);   // +0x00
    virtual void Dispose();                                              // +0x04
    virtual void w2(); virtual void w3(); virtual void w4(); virtual void w5();
    virtual void SetTransforms(const cTransform& source, const cTransform& rigid);  // +0x18
    virtual void w7(); virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11(); virtual void w12();
    virtual void AddRef();                                               // +0x34
    virtual void Release();                                              // +0x38
};
struct AutoComponentRef {
    IComponent* mpObject;
    AutoComponentRef(const AutoComponentRef& o);      // inline in 0x7d5300 (copy ctor of cSplitController)
    ~AutoComponentRef() { if (mpObject) mpObject->Release(); }
};

// ------------------------------------------------------------------ cSplitController vector
struct cEffectParams { void* vtbl; char pad[0xcc]; ~cEffectParams(); };   // 0x7d4ae0
struct cSplitController {                             // size 0x40
    cTransform mLocalXform;                           // +0
    cEffectParams* mParams;                           // +0x38
    IComponent* mComponent;                           // +0x3c (AutoRefCount<cIComponent>)
    cSplitController(const cSplitController& o);      // 0x7d5300
    cSplitController& operator=(const cSplitController& o) {
        mLocalXform = o.mLocalXform;
        mParams = o.mParams;
        IComponent* nc = o.mComponent;
        IComponent* oc = mComponent;
        if (nc != oc) {
            if (nc) nc->AddRef();
            mComponent = nc;
            if (oc) oc->Release();
        }
        return *this;
    }
    ~cSplitController() { IComponent* c = mComponent; if (c) c->Release(); }
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

inline void CtrlDestroyValues(cSplitController* first, cSplitController* last) {
    for (; first < last; ++first) first->~cSplitController();
}

// @ 0x007d5a30  eastl::vector<cSplitController>::~vector
CtrlVec::~CtrlVec() {
    CtrlDestroyValues(mpBegin, mpEnd);
}

// @ 0x007d6620  eastl::vector<cSplitController>::DoInsertValue(position, value)
void CtrlVec::DoInsertValue(cSplitController* position, const cSplitController& value) {
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

// ------------------------------------------------------------------ cAnimationInfo vector
struct cAnimationInfo { float mAge, mInvLength, mCurveMultiplier; };   // size 0xc
cAnimationInfo* __cdecl AnimUninitCopy(cAnimationInfo* first, cAnimationInfo* last, cAnimationInfo* dest);   // 0x898b80 / 0xa11310
void __cdecl AnimCopyBackward(cAnimationInfo* first, cAnimationInfo* last, cAnimationInfo* destEnd);          // 0xabced0
void __cdecl AnimFill(cAnimationInfo* first, cAnimationInfo* last, const cAnimationInfo* v);                  // 0xa177f0
void __cdecl AnimUninitFillN(cAnimationInfo* dest, unsigned n, const cAnimationInfo* v);                      // 0x6e5760
struct AnimVec {                                      // eastl::vector<cAnimationInfo, sp_vector_allocator>
    cAnimationInfo* mpBegin;
    cAnimationInfo* mpEnd;
    cAnimationInfo* mpCapacity;
    void DoInsertValues(cAnimationInfo* position, unsigned n, const cAnimationInfo* value);
};
// @ 0x007d6030  eastl::vector<cAnimationInfo>::DoInsertValues(position, n, value)
void AnimVec::DoInsertValues(cAnimationInfo* position, unsigned n, const cAnimationInfo* value) {
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const cAnimationInfo temp = *value;
            unsigned nExtra = (unsigned)(mpEnd - position);
            if (n < nExtra) {
                cAnimationInfo* pOldEnd = mpEnd;
                AnimUninitCopy(pOldEnd - n, pOldEnd, pOldEnd);
                mpEnd += n;
                AnimCopyBackward(position, pOldEnd - n, pOldEnd);
                AnimFill(position, position + n, &temp);
            } else {
                cAnimationInfo* pOldEnd = mpEnd;
                AnimUninitFillN(pOldEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                AnimUninitCopy(position, pOldEnd, mpEnd);
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

// ------------------------------------------------------------------ cSplitManager
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
struct cSplitManager : RefObj {
    cTransform mComponentTransform;                   // +0x8
    SplitListVec mSplitClientList;                    // +0x40
    cSplitManager();
    // 0x7d62d0 = scalar deleting destructor (compiler-generated destructor)
    void SetComponentTransform(const cTransform& t);  // 0x7d4980
};
// @ 0x007d5d50
cSplitManager::cSplitManager() {
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
// ------------------------------------------------------------------ cGameModelEffect
struct AnimVec5 {                                     // eastl::vector<cAnimationInfo> (+ allocator words)
    cAnimationInfo* mpBegin; cAnimationInfo* mpEnd; cAnimationInfo* mpCapacity; int mAlloc, mAlloc2;
    ~AnimVec5() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin); }
};
struct CtrlVec5 : CtrlVec { int mAlloc2; };
struct cIModelManager;
struct cGameModelEffect : IComponent, RefObj {
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
    AutoRef<RefObj> mModelSplitter;                   // +0xa4
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

// @ 0x007d5af0
cGameModelEffect::cGameModelEffect(void* desc, int packageID) {
    mDesc = desc;
    mPackageID = packageID;
    mActive = false;
    mIsVisible = true;
    mIsLoaded = false;
    mGameModelInstanceID = 0xffffffff;
    mGameModelGroupID = 0xffffffff;
    mGameModelColor[0] = g_one;
    mGameModelColor[1] = g_one;
    mGameModelColor[2] = g_one;
    mGameModelAlpha = g_one;
    mGameModelScale = g_one;
    mIntersectionRadius = g_radiusInit;
    mGameModel.mpObject = 0;
    mComponentXform.mFlags = 0;
    mComponentXform.mModificationCount = 0;
    mComponentXform.mTranslation[0] = g_vecInit[0];
    mComponentXform.mTranslation[1] = g_vecInit[1];
    mComponentXform.mTranslation[2] = g_vecInit[2];
    mComponentXform.mScale = g_one;
    mComponentXform.mRotation.Assign(&g_matIdentityA);
    mLastLocation[0] = g_vecInit[0];
    mLastLocation[1] = g_vecInit[1];
    mLastLocation[2] = g_vecInit[2];
    mAnimationInfo.mpBegin = 0; mAnimationInfo.mpEnd = 0; mAnimationInfo.mpCapacity = 0;
    mModelSplitter.mpObject = 0;
    mSplitManager.mpObject = 0;
    mLODSizeScale[0] = g_one; mLODSizeScale[1] = g_one;
    mSplitControllers.mpBegin = 0; mSplitControllers.mpEnd = 0; mSplitControllers.mpCapacity = 0;
    mLODAlphaScale[0] = g_one; mLODAlphaScale[1] = g_one;
    mModelManager = 0;
    mGameModelWorld = 0;
}

// @ 0x007d5c50  ~cGameModelEffect: members destroyed in reverse order (controllers, split manager,
// model splitter, animation vector, game model)
cGameModelEffect::~cGameModelEffect() {}

// Field-wise cTransform copies: the first rotation goes through Matrix3::Assign, the later ones
// are inlined float copies through a temporary matrix.
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

// @ 0x007d56f0  cGameModelEffect::SetTransforms (IComponent slot 0x18)
void cGameModelEffect::SetTransforms(const cTransform& source, const cTransform& rigid) {
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

// @ 0x007d5dc0  release the controller components and parameter blocks, then the game model
void cGameModelEffect::Unload() {
    unsigned n = (unsigned)(mSplitControllers.mpEnd - mSplitControllers.mpBegin);
    for (unsigned i = 0; i < n; ++i) {
        mSplitControllers.mpBegin[i].mComponent->Dispose();
        cEffectParams* p = mSplitControllers.mpBegin[i].mParams;
        if (p) {
            p->~cEffectParams();
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

// @ 0x007d5e60  find the game model of this effect among the models near its position
struct ModelQueryFilter { int a[5]; char b0, b1; };
struct ModelPtrVec {                                  // eastl::fixed_vector<cMWModel*, 17>
    cMWModel** mpBegin; cMWModel** mpEnd; cMWModel** mpCapacity; cMWModel** mpBuffer;
    cMWModel* mBuffer[17];
    ModelPtrVec() { mpBegin = mBuffer; mpEnd = mBuffer; mpBuffer = mBuffer; mpCapacity = mBuffer + 17; }
    ~ModelPtrVec() { if (mpBegin && mpBegin != mBuffer) operator delete[](mpBegin); }
};
void cGameModelEffect::FindGameModel() {
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

// ------------------------------------------------------------------ existing 0x78-record helpers
char** UninitCopyElem78(char** out, char* first, char* last, char* base, const void* extra);  // 0x7d5aa0
void* VecAlloc0x78(void* vec, unsigned n, const void* alloc);             // 0x7d48e0

// @ 0x007d5aa0  uninitialized_copy of the 0x78-byte records
char** UninitCopyElem78(char** out, char* first, char* last, char* base, const void* extra) {
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

// @ 0x007d61f0
void* __stdcall AllocAndCopy78(unsigned n, char* first, char* last) {
    char* buf = n ? (char*)operator new(n * 0x78, "App", 0, 0, EASTL_ALLOC_FILE, 0xd1) : 0;
    char* out = buf;
    UninitCopyElem78(&out, first, last, buf, 0);
    return buf;
}

// @ 0x007d6250
Elem78* CopyElems78(Elem78* first, Elem78* last, Elem78* dst) {
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

// @ 0x007d6320  eastl::vector<cSplitInstanceList::cElement>::vector(const vector&)
struct Vec78 {
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAlloc;
    Vec78(const Vec78& x);
    void* Allocate(unsigned n, const void* alloc);   // 0x7d48e0
};
Vec78::Vec78(const Vec78& x) {
    Allocate((unsigned)((x.mpEnd - x.mpBegin) / 0x78), &x.mAlloc);
    char* out;
    UninitCopyElem78(&out, x.mpBegin, x.mpEnd, mpBegin, &x);
    mpEnd = out;
}

// ------------------------------------------------------------------ map-holding resources
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
struct cMapResABase : RefObj {
    int mType;                                        // +8
    cMapResABase() : mType(4) {}
};
struct cMapResA : cMapResABase, RbMap {               // 0x7d6380 ctor / 0x7d63e0 scalar deleting dtor (map at +0xc)
    cMapResA(const RbMap& m) : RbMap(m) {}
};
// @ 0x007d6380
cMapResA* MakeMapResA(void* mem, const RbMap& m) { return new (mem) cMapResA(m); }
// @ 0x007d63e0  scalar deleting destructor of cMapResA (vtable emitted by the ctor above)

struct __declspec(novtable) ResBase0 { virtual ~ResBase0() {} };
struct cMapResB : ResBase0, RefObj, RbMap {           // 0x7d6440 ctor / 0x7d6500 dtor (map at +0x0c)
    float mVec[3];                                    // +0x28
    RefObj* mpRef;                                    // +0x34
    cMapResB(const RbMap& m, const float* v, RefObj* r);
    ~cMapResB();
};
// @ 0x007d6440
cMapResB::cMapResB(const RbMap& m, const float* v, RefObj* r) : RbMap(m) {
    mVec[0] = v[0];
    mVec[1] = v[1];
    mVec[2] = v[2];
    mpRef = r;
    if (r) ++r->mnRefCount;
}
// @ 0x007d6500
cMapResB::~cMapResB() {
    if (mpRef) ReleaseRef(mpRef);
}
