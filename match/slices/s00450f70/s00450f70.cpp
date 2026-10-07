// slice s00450f70 -- accessors around a tracker sub-object.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast module.
#include "types.h"

// Reserves N dwords of /Od frame (stands in for the frame of an inline callee cl declined).
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vec3 {
    float x, y, z;
};

struct RCObj {
    virtual void AddRef();
    virtual void Release();
};

struct SubInner {
    char  pad0[0x1c];
    void* field;        // +0x1c
};
struct Sub {
    char     pad0[0x1c];
    SubInner inner;     // +0x1c
};

struct Tracker {
    char   pad0[4];
    RCObj* field4;      // +4
    char   pad8[0x14 - 8];
    Vec3   vec14;       // +0x14
    char   pad20[0x44 - 0x20];
    int    field44;     // +0x44

    void Call(void* tmp, int a, unsigned char b);   // 0x004e9500
};

struct Block2 {
    char     pad0[0x18];
    void*    mp18;        // +0x18
    int      mInstance;   // +0x1c
    int      mGroup;      // +0x20
    char     pad24[0x28 - 0x24];
    int      mField28;    // +0x28
    char     pad2c[0x48 - 0x2c];
    Vec3     mVec48;      // +0x48
    char     pad54[0x188 - 0x54];
    void*    mPtr188;     // +0x188
    Sub*     mSub18c;     // +0x18c
    char     pad190[0x194 - 0x190];
    Vec3     mVec194;     // +0x194
    bool     mFlag1a0;    // +0x1a0
    char     pad1a1[0x1a4 - 0x1a1];
    int      mField1a4;   // +0x1a4
    char     pad1a8[0x1d8 - 0x1a8];
    float    mField1d8;   // +0x1d8
    float    mField1dc;   // +0x1dc
    char     pad1e0[0x33c - 0x1e0];
    void*    mPtr33c;     // +0x33c
    char     pad340[0x378 - 0x340];
    Tracker* mTracker;    // +0x378
    char     pad37c[0xdc8 - 0x37c];
    unsigned int mFlags[2]; // +0xdc8

    bool GetFlag(unsigned int n) const {
        unsigned int tmp;
        bool t14;
        if (n < 60u) {
            tmp = mFlags[n / 32];
            t14 = (tmp & (1u << (n % 32))) != 0;
        } else {
            t14 = false;
        }
        return t14;
    }
    void SetBit(unsigned int n) { unsigned int w = n / 32; mFlags[w] |= (1u << (n % 32)); }
    void ClearBit(unsigned int n) { unsigned int w = n / 32; mFlags[w] &= ~(1u << (n % 32)); }

    int    GetA();                        // 0x004511f0
    int    GetB();                        // 0x00451210
    void   SetF(void* a, unsigned char b);// 0x00451240
    void   SetRef(RCObj* p);              // 0x00451280
    Vec3*  GetVec14(Vec3* out);           // 0x004512e0
    void   SetVec194(int x, int y, int z);// 0x00451330
    void   ResetVec194();                 // 0x00451360
    Vec3*  GetVec194(Vec3* out);          // 0x004513a0
    void   SetPtr188(void* p);            // 0x00451e20
    void   SetSub38(void* p);             // 0x00451e50
    void*  GetSub38();                    // 0x00451e90
    void   Reset188();                    // 0x00451ed0
    unsigned char Rebuild(int a, int b, float c, char d, unsigned char e); // 0x00450f70
    void   FUN_00452040();                // 0x00452040
    void   FUN_00451fe0();                // 0x00451fe0
    void   FUN_00440520(float f, int a, int b);   // 0x00440520
    void   FUN_00449ed0();                // 0x00449ed0
    void   FUN_00448e90(void* p, int a);  // 0x00448e90
    void   FUN_00449420(void* p, int a);  // 0x00449420
    unsigned char BuildBlock(int inst, int grp, int a, int b, float c, char d, unsigned char e, int one); // 0x00441040
};

// @ 0x004511f0
int Block2::GetA() {
    int result = (int)mTracker->field4;
    return result;
}

// @ 0x00451210
int Block2::GetB() {
    if (mTracker != 0) {
        return mTracker->field44;
    } else {
        return -1;
    }
}

// @ 0x00451240
void Block2::SetF(void* a, unsigned char b) {
    void* tmp = mPtr33c;
    mTracker->Call(tmp, (int)a, b);
}

// @ 0x00451280
void Block2::SetRef(RCObj* p) {
    RCObj** slot = &mTracker->field4;
    RCObj* old;
    if (p != *slot) {
        old = *slot;
        if (p != 0) p->AddRef();
        *slot = p;
        if (old != 0) old->Release();
    }
}

// @ 0x004512e0
Vec3* Block2::GetVec14(Vec3* out) {
    Vec3* p = &mTracker->vec14;
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}

// @ 0x00451330
void Block2::SetVec194(int x, int y, int z) {
    *(int*)&mVec194.x = x;
    *(int*)&mVec194.y = y;
    *(int*)&mVec194.z = z;
    mFlag1a0 = true;
}

// @ 0x00451360
void Block2::ResetVec194() {
    mVec194 = mVec48;
    mFlag1a0 = false;
}

// @ 0x004513a0
Vec3* Block2::GetVec194(Vec3* out) {
    Vec3* p = &mVec194;
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}

// @ 0x00451e20
void Block2::SetPtr188(void* p) {
    mPtr188 = p;
    FUN_00452040();
}

// @ 0x00451e50
void Block2::SetSub38(void* p) {
    if (mSub18c != 0) {
        SubInner* q = &mSub18c->inner;
        q->field = p;
    }
}

// @ 0x00451e90
void* Block2::GetSub38() {
    if (mSub18c != 0) {
        SubInner* q = &mSub18c->inner;
        void* result = q->field;
        return result;
    } else {
        return 0;
    }
}

// @ 0x00451ed0
void Block2::Reset188() {
    FUN_00451fe0();
    mPtr188 = 0;
}

// @ 0x00450f70
unsigned char Block2::Rebuild(int a, int b, float c, char d, unsigned char e) {
    bool f12 = GetFlag(0xc);
    bool f39 = GetFlag(0x39);
    mFlags[0] = 0;
    mFlags[1] = 0;
    if (f12) SetBit(0xc); else ClearBit(0xc);
    if (f39) SetBit(0x39); else ClearBit(0x39);
    unsigned char r = BuildBlock(mInstance, mGroup, a, b, c, d, e, 1);
    FUN_00440520(mField1d8, 0, 1);
    mField1dc = mField1d8;
    if (d != 0)
        FUN_00449ed0();
    FUN_00448e90((char*)this + 0x48, 0);
    FUN_00449420((char*)this + 0xa8, 0);
    return r;
}


// ===========================================================================================
// SP::cSPEditorBlock::Shutdown2 (0x00451400): releases everything BuildBlock (0x00441440) set up.
// Retail layout (ModAPI Editors::EditorRigblock offsets, as in slice s00441440).
// ===========================================================================================
namespace SP {

class IUnknown32 {
public:
    virtual int AddRef();
    virtual int Release();
};

template <class T>
struct AutoRefCount {
    T* mpObject;

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
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

template <int N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];

    uint32_t& DoGetWord(uint32_t n) { return mWord[n >> 5]; }
    __forceinline void set(uint32_t n, bool value)
    {
        if (n < N) {
            if (value)
                DoGetWord(n) |= 1u << (n % 32);
            else
                DoGetWord(n) &= ~(1u << (n % 32));
        }
    }
};

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
};

class IModelWorld;

// Graphics::Model
struct cMWModel {
    IModelWorld* mpWorld;                 // +0x00
    uint32_t pad04[(0x40 - 4) / 4];
    int mnRefCount;                       // +0x40
    uint32_t pad44[(0x64 - 0x44) / 4];
    AutoRefCount<IUnknown32> mpOwner;     // +0x64

    int AddRef() { mnRefCount = mnRefCount + 1; return mnRefCount; }
    int Release();                        // 0x0040f360
    inline void RemoveFromWorld();
};

class IModelWorld {
public:
    virtual int AddRef();                                                // 0x00
    virtual int Release();                                               // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void vb8(); virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void SetExternalEffectsTransform(cMWModel* model, const void* transform, uint32_t instanceID);  // 0xd4
    virtual void vd8(); virtual void vdc();
    virtual void ReleaseTransformedHull(int* hull);                      // 0xe0
    virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168();
    virtual bool SetInWorld(cMWModel* model, bool inWorld);              // 0x16c
};

inline void cMWModel::RemoveFromWorld() { mpWorld->SetInWorld(this, false); }

class cSPEditorHandle {
public:
    virtual int AddRef();          // 0x00
    virtual int Release();         // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18();
    virtual void Dispose();        // 0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void Shutdown();       // 0x4c
};

// Object at +0x378 (0x4c bytes); its member at +4 is a refcounted interface.
class cSPEditorBlockHelper378 {
public:
    uint32_t mField0;
    AutoRefCount<IUnknown32> mpObject;
    uint32_t mData[(0x4c - 8) / 4];

    void Shutdown();               // 0x004ae250
};

// FadeController (+0xdd0)
struct cSPEditorBlockOwnerLink {
    uint32_t mData[0x38 / 4];
    bool IsPlaying();              // 0x00434100
    void Stop();                   // 0x004341c0
    void ReleaseHandle();          // 0x00433aa0
};

class cSPEditorBlock;

template <class T>
struct ref_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    uint32_t mBuffer[8];
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;               // 0x00526430 (ICF-shared)
    T& operator[](int i) { return *(mpBegin + i); }
    T* erase(T* first, T* last);      // 0x00533500
    void clear() { erase(mpBegin, mpEnd); }
};

class RefCountVTemplate {
public:
    virtual int AddRef();
    virtual int Release();
    int mnRefCount;
};

class cSPEditorBlock : public RefCountVTemplate, public IUnknown32 {
public:
    AutoRefCount<cPropertyList> mpPropList;          // +0x0c
    AutoRefCount<cMWModel> mpModel;                  // +0x10
    AutoRefCount<cMWModel> mpEffectsMaskModel;       // +0x14
    AutoRefCount<IModelWorld> mpModelWorld;          // +0x18
    uint32_t mInstanceID;                            // +0x1c
    uint32_t mGroupID;                               // +0x20
    int mBlockPack;                                  // +0x24
    void* mpEditorModel;                             // +0x28
    uint32_t pad2c[(0x154 - 0x2c) / 4];
    AutoRefCount<cSPEditorHandle> mAxisHandles[3];   // +0x154
    AutoRefCount<cSPEditorHandle> mpRotationBallHandle;  // +0x160
    uint32_t pad164[(0x1a4 - 0x164) / 4];
    int mTransformedHull;                            // +0x1a4
    uint32_t pad1a8[(0x33c - 0x1a8) / 4];
    AutoRefCount<cSPEditorBlock> mpParent;           // +0x33c
    ref_vector<AutoRefCount<cSPEditorBlock> > mChildren;  // +0x340
    cSPEditorBlockHelper378* mpHelper378;            // +0x378
    uint32_t pad37c[(0x3e4 - 0x37c) / 4];
    AutoRefCount<cSPEditorBlock> mpSymmetricBlock;   // +0x3e4
    bool mIsSymmetric;                               // +0x3e8
    uint8_t pad3e9[3];
    AutoRefCount<cSPEditorHandle> mpBallConnectorHandle;  // +0x3ec
    AutoRefCount<cMWModel> mpSocketConnectorModel;   // +0x3f0
    uint32_t pad3f4[(0x6cc - 0x3f4) / 4];
    ref_vector<AutoRefCount<cSPEditorHandle> > mMorphHandles;  // +0x6cc
    uint32_t pad704[(0xdc8 - 0x704) / 4];
    bitset<60> mBooleanAttributes;                   // +0xdc8
    cSPEditorBlockOwnerLink mOwnerLink;              // +0xdd0

    bool HasParent() const { return mpParent != 0; }
    void Shutdown2();
    void SetBooleanAttribute(int index, bool value); // 0x00435a10
    void RemoveChild(cSPEditorBlock* child);         // 0x00438b10
    void Sub_451ed0();                               // 0x00451ed0 (ReleasePhysics + clear +0x188)
    void Sub_453500(bool b);                         // 0x00453500
    void Sub_438df0(int a);                          // 0x00438df0
    void Sub_438cc0(int a);                          // 0x00438cc0
};

// @ 0x00451400
void cSPEditorBlock::Shutdown2()
{
    if (mTransformedHull) {
        mpModelWorld->ReleaseTransformedHull(&mTransformedHull);
        mTransformedHull = 0;
    }
    Sub_451ed0();
    if (mOwnerLink.IsPlaying())
        mOwnerLink.Stop();
    mOwnerLink.ReleaseHandle();
    mBooleanAttributes.set(1, true);
    void* pEditorModel = mpEditorModel;
    mpEditorModel = 0;

    mpPropList = 0;
    if (mpModel) {
        mpModelWorld->SetExternalEffectsTransform(mpModel, 0, 0);
        mpModel->RemoveFromWorld();
        mpModel = 0;
    }
    if (mpEffectsMaskModel) {
        mpEffectsMaskModel->RemoveFromWorld();
        mpEffectsMaskModel = 0;
    }
    mpModelWorld = 0;

    while (!mChildren.empty()) {
        if (mChildren[0]->mpHelper378) {
            mChildren[0]->mpHelper378->mField0 = 0;
            mChildren[0]->mpHelper378->mpObject = 0;
        }
        mChildren[0]->SetBooleanAttribute(0xc, false);
        RemoveChild(mChildren[0]);
    }
    if (HasParent())
        mpParent->RemoveChild(this);

    if (mpBallConnectorHandle) {
        mpBallConnectorHandle->Dispose();
        mpBallConnectorHandle = 0;
    }
    if (mpSocketConnectorModel) {
        mpSocketConnectorModel->mpOwner = 0;
        mpSocketConnectorModel->RemoveFromWorld();
        ScratchSlots<2>();
        mpSocketConnectorModel = 0;
    }

    int n = mMorphHandles.size();
    for (int i = 0; i < n; i++) {
        if (mMorphHandles[i])
            mMorphHandles[i]->Dispose();
    }
    ScratchSlots<3>();
    mMorphHandles.clear();

    if (mpRotationBallHandle) {
        mpRotationBallHandle->Shutdown();
        mpRotationBallHandle = 0;
    }
    for (int j = 0; j < 3; j++) {
        if (mAxisHandles[j]) {
            mAxisHandles[j]->Dispose();
            mAxisHandles[j] = 0;
        }
    }
    if (mpHelper378) {
        mpHelper378->Shutdown();
        delete mpHelper378;
    }
    if (mpSymmetricBlock && mIsSymmetric) {
        mpSymmetricBlock->Sub_453500(true);
        Sub_453500(false);
    }
    Sub_438df0(0);
    Sub_438cc0(0);
}

}  // namespace SP
