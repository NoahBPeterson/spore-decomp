// src/game/SPBake/SPEditorSkinManager.cpp -- migrated from slice(s) s004c6190, s004c5200, s004c4650, s005002d0, s004c38e0, s004c3230, s004c2100 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorSkinManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cSPEditorSkinPart.h"
#include "cSPTransform.h"
#include <new>
#include "SP/cMeshData.h"
#include <stdio.h>
#include "SP/cRuntimeCreatureResource.h"
#include "SP/cSkinObject.h"
#include <intrin.h>
#pragma pack(push, 4)

// ---- items of slice s004c3230 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(pop)
template <int N> inline void ScratchSlots() { uint32_t s[N]; }
namespace SP {
struct Vector3 {
    float x, y, z;
    Vector3() {}
};
}
namespace SP {
struct Matrix3 {
    float m[9];
};
}
namespace SP {
bool Vector3_NotEqual(const Vector3& a, const Vector3& b);   // 0x0041dd30 (cdecl)
}
namespace SP {
bool Matrix3_NotEqual(const Matrix3& a, const Matrix3& b);   // 0x0041dd90 (cdecl, operator!=<>)
}
namespace SP {
template <uint32_t N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    uint32_t DoGetWord(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const
    {
        if (i < N)
            return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
};
}
namespace SP {
class cSPEditorBlock_s004c_3230 {
public:
    char pad0[0x48];
    Vector3 mPosition;       // +0x48
    char pad54[0x60 - 0x54];
    Matrix3 mOrientation;    // +0x60
    char pad84[0x1d8 - 0x84];
    float mScale;            // +0x1d8
    char pad1dc[0xdc8 - 0x1dc];
    bitset<60> mFlags;      // +0xdc8

    bool IsValid();          // 0x0044c030
    const Vector3& GetPosition() { return mPosition; }
    const Matrix3& GetOrientation() { return mOrientation; }
    float GetScale() { return mScale; }
};
}
namespace SP {
template <class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}
namespace SP {
struct BlockList {
    cSPEditorBlock_s004c_3230** mpBegin;
    cSPEditorBlock_s004c_3230** begin() { return mpBegin; }
};
}
namespace SP {
class cSPEditorModel_s004c_3230 {
public:
    char pad0[0x18];
    BlockList mBlockList;    // +0x18
    int GetBlockCount();     // 0x004accf0
    cSPEditorBlock_s004c_3230** begin() { return mBlockList.begin(); }
};
}
namespace SP {
class cIModelWorld_s004c_3230;
}
namespace SP {
class cSPEditorSkinPart_s004c_3230 {
public:
    struct BlockVec;
    void Update(BlockVec& blocks, bool forceHighQuality);   // 0x004cc540
    void UpdateSceneObject(cIModelWorld_s004c_3230* world);            // 0x004cc7d0
    void SetVisible(bool visible);                          // 0x004cca40
    void SetDrawMaterial(uint32_t id);                      // 0x004cd020
};
}
namespace SP {
struct Alloc {
    Alloc() {}
};
}
namespace SP {
struct TagFalse {
    TagFalse() {}
};
}
namespace SP {
struct __declspec(align(4)) cSPEditorSkinPart_s004c_3230::BlockVec {
    cSPEditorBlock_s004c_3230** mpBegin;
    cSPEditorBlock_s004c_3230** mpEnd;
    cSPEditorBlock_s004c_3230** mpCapacity;
    uint32_t mFixedPad[2];
    uint32_t mOverflow;
    cSPEditorBlock_s004c_3230* mBuffer[40];
    void Init(const Alloc& tag);                       // 0x00540470
    BlockVec()
    {
        Init(Alloc());
        InitFixed();
    }
    void InitFixed();                                  // 0x004c5df0
    void FreeOverflow();                               // 0x00425990 (VectorBase dtor)
    ~BlockVec()
    {
        for (cSPEditorBlock_s004c_3230** p = mpBegin; p < mpEnd; ++p) {
        }
        FreeOverflow();
        ScratchSlots<3>();
    }
    void PushBackOutOfLine(cSPEditorBlock_s004c_3230* const& v);  // 0x00454860
    void push_back(cSPEditorBlock_s004c_3230* const& v)
    {
        PushBackOutOfLine(v);
        ScratchSlots<2>();
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    cSPEditorBlock_s004c_3230** begin() { return mpBegin; }
    cSPEditorBlock_s004c_3230** end() { return mpEnd; }
    cSPEditorBlock_s004c_3230*& operator[](int n)
    {
        cSPEditorBlock_s004c_3230** p = mpBegin + n;
        return *p;
    }
};
}
namespace SP {
typedef cSPEditorSkinPart_s004c_3230::BlockVec BlockVec;
}
namespace SP {
struct cSPTransform {  // size 0x38
    unsigned short mFlags;              // +0x0
    unsigned short mModificationCount;  // +0x2
    Vector3 mTranslation;               // +0x4
    float mScale;                       // +0x10
    Matrix3 mRotation;                  // +0x14

    float GetScale() { return mScale; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void SetTranslation(const Vector3& v)
    {
        mTranslation = v;
        mFlags |= 4;
        mModificationCount++;
    }
    void SetRotation(const Matrix3& m)
    {
        mRotation = m;
        mFlags |= 2;
        mModificationCount++;
    }
};
}
namespace SP {
struct TransformVec {
    cSPTransform* mpBegin;
    cSPTransform* mpEnd;
    cSPTransform* mpCapacity;
    uint32_t mAlloc;
    void erase(cSPTransform* first, cSPTransform* last);   // 0x004238c0
    void clear() { erase(mpBegin, mpEnd); }
    void EmplaceBack();                                    // 0x004c5eb0 (out of line)
    void push_back_default()
    {
        EmplaceBack();
        ScratchSlots<16>();
    }
    cSPTransform& operator[](int i) { return mpBegin[i]; }
    cSPTransform& back() { return mpEnd[-1]; }
};
}
namespace SP {
struct PtrVec {
    cSPEditorBlock_s004c_3230** mpBegin;
    cSPEditorBlock_s004c_3230** mpEnd;
    cSPEditorBlock_s004c_3230** mpCapacity;
    uint32_t mAlloc;
    void DoAssignFromIterator(cSPEditorBlock_s004c_3230** first, cSPEditorBlock_s004c_3230** last, TagFalse tag);   // 0x004d04f0
    // eastl::vector::assign(first, last) -> DoAssign(..., is_integral) -> DoAssignFromIterator(...):
    // the two declined inline levels leave two dead empty-tag temporaries in the caller's frame.
    void assign(cSPEditorBlock_s004c_3230** first, cSPEditorBlock_s004c_3230** last)
    {
        TagFalse unusedIntegralTag;
        TagFalse unusedCategoryTag;
        DoAssignFromIterator(first, last, TagFalse());
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    cSPEditorBlock_s004c_3230*& operator[](int n)
    {
        cSPEditorBlock_s004c_3230** p = mpBegin + n;
        return *p;
    }
};
}
namespace SP {
struct TorsoFlags {
    bool a;
    bool b;
};
}
namespace SP {
class cSPEditorSkinManager_s004c_3230 {
public:
    char pad0[0xc];
    void* mApp;                       // +0xc
    cSPEditorModel_s004c_3230* mModel;           // +0x10
    cIModelWorld_s004c_3230* mSceneObjectModelWorld;  // +0x14
    AutoRefCount<cSPEditorSkinPart_s004c_3230> mTorsoSkin;   // +0x18
    void* mCompleteSkin;              // +0x1c
    TransformVec mPreviousTorsoBlockTransforms;   // +0x20
    uint32_t pad30;                   // +0x30
    PtrVec mPreviousTorsoBlockPointers;           // +0x34 (retail layout)

    void UpdateTorso(TorsoFlags flags, int x);  // 0x004c3230 (SP::cSPEditorSkinManager::UpdateTorso)
};
}
// ---- items of slice s004c3230 end

// ---- items of slice s004c38e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const char kEditorAllocName[];   // 0x013eb430 ?kEditorAllocName@@3QBDB
void* __cdecl operator new(unsigned int size, const char* name, int, int, int, int);
namespace eastl {
template <int N> class bitset_s004c_38e0 {
public:
    uint32_t mWord[(N + 31) / 32];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWordValue(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWordValue(i) & (1 << (i % 32))) != 0;
        return false;
    }
};  // namespace eastl
}
namespace SP {
struct AllocTag { AllocTag() {} };
}
namespace SP {
class cSPEditorBlock_s004c_38e0;
}
namespace SP {
class cSPEditorModel_s004c_38e0;
}
namespace SP {
class cSPEditorSkinPart_s004c_38e0;
}
namespace SP {
class cIModelWorld_s004c_38e0;
}
namespace SP {
class cPaintRequest_s004c_38e0;
}
namespace SP {
struct SkinElem;
}
namespace SP {
struct SkinModel;
}
namespace SP {
struct MatInfo;
}
namespace SP {
bool CollectPartsRec(cSPEditorBlock_s004c_38e0* block, void* parts);        // 0x0048ccf0
}
namespace SP {
uint32_t HashModelType(uint32_t modelType);                      // 0x004bb860
}
namespace SP {
void FUN_00425990();                                             // free (vector teardown)
}
namespace SP {
void FUN_004c64d0();                                             // fixed-vector teardown
}
namespace SP {
class FixedVec16 {
public:
    FixedVec16();                                                // 0x004ce9d0
    void Init(int count, uint8_t* value);                        // 0x004c60e0
    ~FixedVec16() { for (uint8_t* p = mpBegin; p < mpEnd; ++p) {} FUN_004c64d0(); }
    void FUN_004c64d0();                                         // 0x004c64d0
    uint8_t* mpBegin;                                            // +0x00
    uint8_t* mpEnd;                                              // +0x04
    uint8_t* mpCapacity;                                         // +0x08
    uint32_t mAlloc0;                                            // +0x0c
    uint32_t mAlloc4;                                            // +0x10
    uint32_t mAlloc8;                                            // +0x14
    uint8_t  mBuffer[16];                                        // +0x18
};
}
namespace SP {
class VSet128 {
public:
    VSet128(const AllocTag& a);                                  // 0x00540470
    void Init();                                                 // 0x004c5e30
    void push_back(const uint32_t& v);                           // 0x00454860
    ~VSet128() { for (uint32_t* p = mpBegin; p < mpEnd; ++p) {} FUN_00425990(); }
    void FUN_00425990();                                         // 0x00425990
    uint32_t* mpBegin;                                           // +0x00
    uint32_t* mpEnd;                                             // +0x04
    uint32_t* mpCapacity;                                        // +0x08
    uint32_t mAlloc0;                                            // +0x0c
    uint32_t mAlloc4;                                            // +0x10
    uint32_t mAlloc8;                                            // +0x14
    uint32_t mBuffer[128];                                       // +0x18
};
}
namespace SP {
class VSet64 {
public:
    VSet64(const AllocTag& a);                                   // 0x00540470
    void Init();                                                 // 0x004c5e70
    void push_back(const uint32_t& v);                           // 0x00454860
    ~VSet64();                                                   // 0x004e1bf0
    uint32_t* mpBegin;                                           // +0x00
    uint32_t* mpEnd;                                             // +0x04
    uint32_t* mpCapacity;                                        // +0x08
    uint32_t mAlloc0;                                            // +0x0c
    uint32_t mAlloc4;                                            // +0x10
    uint32_t mAlloc8;                                            // +0x14
    uint32_t mBuffer[64];                                        // +0x18
};
}
namespace SP {
struct SkinElem {
    uint32_t mPad0;                                              // +0x00
    uint16_t mType;                                              // +0x04 (0x210 = texture slot)
    uint16_t mPad6;                                              // +0x06
    void*    mData;                                              // +0x08
};
}
namespace SP {
struct SkinElemVector {
    SkinElem** mpBegin;                                          // +0x00
    SkinElem** mpEnd;                                            // +0x04
    SkinElem** mpCapacity;                                       // +0x08
    bool empty();                                                // 0x00526430
};
}
namespace SP {
struct SkinModel {
    uint32_t mPad0;                                              // +0x00
    uint32_t mPad4;                                              // +0x04
    SkinElemVector mElems;                                       // +0x08
};
}
namespace SP {
struct MatInfo {
    uint32_t mPad0;                                              // +0x00
    uint32_t mPad4;                                              // +0x04
    SkinElemVector mElems;                                       // +0x08
};
}
namespace SP {
struct SkinResource {
    uint32_t mPad0[6];                                           // +0x00
    uint32_t mModelType;                                         // +0x18
};
}
namespace SP {
struct PaintData {
    uint8_t mTag;                                                // +0x00
    uint8_t mPad[3];
    float   mA;                                                  // +0x04
    float   mB;                                                  // +0x08
    uint32_t mPadC;                                              // +0x0c
    float   mC;                                                  // +0x10
};
}
namespace SP {
class cPaintRequest_s004c_38e0 {
public:
    uint8_t mPad0[0x70];
    float   mA;                                                  // +0x70
    float   mB;                                                  // +0x74
    float   mC;                                                  // +0x78
};
}
namespace SP {
class cSPEditorSkinPart_s004c_38e0 {
public:
    cSPEditorSkinPart_s004c_38e0();                                         // 0x004cc190
    // The second (dynamic-draw) vtable lives at +0xbc; ref-counting goes through it.
    struct DrawBase {
        virtual int AddRef();
        virtual int Release();
    };

    void SetDrawMaterial(uint32_t id);                           // 0x004cd020
    void SetModel(uint32_t instance, uint32_t group, bool allowHighQuality); // 0x004cc470
    void SetSkinResolution(float realtime, float highQuality);   // 0x004cd060
    void Update(uint32_t* blocks, bool forceHighQuality);        // 0x004cc540
    void UpdateSceneObject(cIModelWorld_s004c_38e0* world);                 // 0x004cc7d0
    bool IsHighQualityPending();                                 // 0x004cc760
    void RestartQualityTimer();                                  // 0x004cc6f0
    void SetVisible(bool visible);                               // 0x004cca40
    void* GetSceneObject() { return mModel; }
    void AddDrawRef() { mDraw.AddRef(); }
    void DrawRelease() { mDraw.Release(); }

    uint8_t mPad0[8];
    SkinResource* mResource;                                     // +0x08
    uint8_t mPad1[0xb8 - 0x0c];
    SkinModel* mSkinModel;                                       // +0xb8
    DrawBase mDraw;                                              // +0xbc (vptr)
    uint8_t mPadDraw[0xe0 - 0xc0];
    void* mModel;                                                // +0xe0
    void* mMatBegin;                                             // +0xe4
    void* mMatEnd;                                               // +0xe8
    void* mMatCapacity;                                          // +0xec
    uint8_t mPadEnd[0x130 - 0xf0];
};
}
namespace SP {
template <class T> class AutoRefCount_s004c_38e0 {
public:
    AutoRefCount_s004c_38e0() : mpObject(0) {}
    AutoRefCount_s004c_38e0(T* const& p) : mpObject(p) { if (mpObject) mpObject->AddDrawRef(); }
    AutoRefCount_s004c_38e0(const AutoRefCount_s004c_38e0& o) : mpObject(o.mpObject) {
        if (mpObject) mpObject->AddDrawRef();
    }
    ~AutoRefCount_s004c_38e0() { if (mpObject) mpObject->DrawRelease(); }
    AutoRefCount_s004c_38e0& operator=(T* const& p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddDrawRef();
            mpObject = p;
            if (old) old->DrawRelease();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    T* mpObject;
};
}
namespace SP {
struct PaintRequestSlot {
    cPaintRequest_s004c_38e0* mpObject;
    cPaintRequest_s004c_38e0* operator->() const { return mpObject; }
};
}
namespace SP {
struct LimbPair {
    cSPEditorBlock_s004c_38e0* first;                                       // +0x00
    AutoRefCount_s004c_38e0<cSPEditorSkinPart_s004c_38e0> second;                      // +0x04
};
}
namespace SP {
struct LimbVector {
    LimbPair* mpBegin;                                           // +0x00
    LimbPair* mpEnd;                                             // +0x04
    LimbPair* mpCapacity;                                        // +0x08
    uint32_t  mAllocName;                                        // +0x0c
    uint32_t  mAllocFlags;                                       // +0x10
    void push_back(const LimbPair& v);                           // 0x004c5fc0
    int size() const { return (int)(mpEnd - mpBegin); }
    LimbPair& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
class cSPEditorBlock_s004c_38e0 {
public:
    bool Paint();                                                // 0x0044c030
    bool HasAnyBlockFlag();                                      // 0x00435d40
    void SetFlag(int flag, bool value);                          // 0x00435a10
    uint8_t mPad0[0x33c];
    void*   mField33c;                                           // +0x33c
    uint8_t mPad1[0xdc8 - 0x340];
    eastl::bitset_s004c_38e0<60> mFlags;                                    // +0xdc8
};
}
namespace SP {
class cSPEditorModel_s004c_38e0 {
public:
    uint32_t GetBlockCount() const;                              // 0x004accf0
    uint8_t mPad0[0x18];
    cSPEditorBlock_s004c_38e0** mpBlockList;                                // +0x18
    uint8_t mPad1[0x50 - 0x1c];
    bool mFlag50;                                                // +0x50
    uint8_t mPad2[0x58 - 0x51];
    uint32_t mName58;                                            // +0x58
};
}
namespace SP {
class cSPEditorSkinManager_s004c_38e0 {
public:
    void UpdateTorso(uint32_t flags, int value);                 // 0x004c3230
    void Update(uint32_t unused, bool paintAll, uint32_t p4, uint32_t p5); // 0x004c38e0
    void UpdatePaintedSkin();                                    // 0x004c4290
    cSPEditorSkinPart_s004c_38e0* CreateSkinObject(cSPEditorBlock_s004c_38e0* block, uint32_t instance); // 0x004c44c0
    void* GetSceneObject(uint32_t which);                        // 0x004c45d0

    uint8_t mPad0[0x10];
    cSPEditorModel_s004c_38e0* mModel;                                      // +0x10
    cIModelWorld_s004c_38e0*   mSceneObjectModelWorld;                      // +0x14
    AutoRefCount_s004c_38e0<cSPEditorSkinPart_s004c_38e0> mTorsoSkin;                  // +0x18
    AutoRefCount_s004c_38e0<cSPEditorSkinPart_s004c_38e0> mCompleteSkin;               // +0x1c
    uint8_t mPad20[0x48 - 0x20];                                 // +0x20 transforms/pointers
    LimbVector mLimbSkins;                                       // +0x48
    PaintRequestSlot mPaintRequest;                              // +0x5c
    uint32_t mDefaultMaterial;                                   // +0x60
    uint8_t  mTextureKey[0x70 - 0x64];                           // +0x64
    void*    mDiffuseTex;                                        // +0x70
    void*    mNormalTex;                                         // +0x74
    float    mPaintResolution;                                   // +0x78
    float    mRealtimeResolution;                                // +0x7c
    float    mHighQualityResolution;                             // +0x80
    bool     mPaintEnabled;                                      // +0x84
    bool     mHairEnabled;                                       // +0x85
};
}
// ---- items of slice s004c38e0 end

// ---- items of slice s005002d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
template <int N> inline void ScratchSlots_s0050_02d0() { uint s[N]; }
namespace eastl {
struct allocator_s0050_02d0 {};
}
namespace eastl {
template <typename T, typename A = allocator_s0050_02d0>
struct basic_string_s0050_02d0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    struct CtorSprintf {};
    basic_string_s0050_02d0(CtorSprintf, const T* pFormat, ...);   // 0x00472f50 (char)
    ~basic_string_s0050_02d0();                                    // 0x00530670
    const T* c_str() const { return mpBegin; }
};
}
typedef eastl::basic_string_s0050_02d0<char> string8;
template <typename T>
struct SPVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int mAllocator;
    uint size() const { return (uint)(mpEnd - mpBegin); }
    T& operator[](uint i) { return mpBegin[i]; }
    bool empty() const;                                  // 0x00526430 (out of line)
};
struct rwVector3 { float v[3]; rwVector3() {} };
struct rwMatrix33 { float m[9]; rwMatrix33() {} };
struct cSPVector3_s0050_02d0 {
    float v[3];
    cSPVector3_s0050_02d0() { v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; }
    cSPVector3_s0050_02d0(const rwVector3& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; }
    cSPVector3_s0050_02d0(const cSPVector3_s0050_02d0& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; }
    const float& operator[](int i) const { return v[i]; }
};
struct cSPMatrix3_s0050_02d0 {
    rwMatrix33 rw;
    cSPMatrix3_s0050_02d0(const rwMatrix33& o) { rw = o; }
};
struct node {                                            // 0x48 bytes
    cSPVector3_s0050_02d0 p;                                        // +0
    char pad[0x44 - 0xc];
    uint jidx;                                           // +0x44
};
struct bone {                                            // 0x54 bytes
    char pad[0x44];
    bool mIsConnectorBone;                               // +0x44
    char pad2[0x50 - 0x45];
    uint jidx;                                           // +0x50
};
struct export_joint {                                    // 0xd8 bytes
    uint parent_jidx;                                    // +0
    uint nidx;                                           // +4
    uint bidx;                                           // +8
    uint type;                                           // +0xc
    SPVector<uint> child_jidxs;                          // +0x10 (fixed_vector header)
    char pad[0x48 - 0x20];
    cSPVector3_s0050_02d0 abs_p;                                    // +0x48
    cSPMatrix3_s0050_02d0 abs_R;                                    // +0x54
    cSPVector3_s0050_02d0 rel_p;                                    // +0x78
    cSPMatrix3_s0050_02d0 rel_R;                                    // +0x84
    char pad2[0xd8 - 0xa8];
};
struct cMeshVertexRef { uint vertex; uint pad; uint uv; };            // 12 bytes
struct cSubMesh {
    char pad[0x6c];
    SPVector<uint> indices;                              // +0x6c
    char pad2[0x80 - 0x7c];
    SPVector<cMeshVertexRef> verts;                      // +0x80
};
struct cVec2 {
    float x, y;
    cVec2() { x = 0.0f; y = 0.0f; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cMeshData {
    char pad[8];
    cSPVector3_s0050_02d0* mpPositions;                             // +8
    char pad1[0x1c - 0xc];
    cSPVector3_s0050_02d0* mpNormals;                               // +0x1c
    char pad2[0x30 - 0x20];
    SPVector<cVec2> uvs;                                 // +0x30
    char pad3[0x58 - 0x40];
    SPVector<uint> indices;                              // +0x58
    char pad4[0xe4 - 0x68];
    SPVector<cSubMesh*> submeshes;                       // +0xe4
    char pad5[0x10c - 0xf4];
    uint material;                                       // +0x10c
};
struct cSkinWeights { unsigned char bone[4]; float weight[4]; uint pad; };   // 0x14 bytes per vertex
class cExportHelper {
public:
    void ExportSkeleton();                               // 0x005002d0
    void ExportMeshBegin(uint numSubmeshes, bool ascii); // 0x00500880
    void ExportSubmesh(cMeshData* mesh, cSkinWeights* weights);   // 0x00500920
    void ExportMeshAdd(int nidx, int bidx, float* pos, float* normals, float* uvs, uint* indices,
                       uint numVerts, uint numFaces, int posStride, int normStride, int uvStride);   // 0x00500ef0
    void ExportMeshEnd();                                // 0x00501200

    const wchar_t* mpName;                               // +0x00
    const wchar_t* GetName() const { return mpName; }
    char pad04[0x0c];
    SPVector<node> mNodes;                               // +0x10
    char pad20[4];
    SPVector<bone> mBones;                               // +0x24 (retail)
    char pad34[0x38 - 0x34];
    uint root_nidx;                                      // +0x38
    bool mMoveRootToOrigin;                              // +0x3c
    char pad3d[0x54 - 0x3d];
    SPVector<export_joint> mExportJoints;                // +0x54
    char pad64[0x6c - 0x64];
    FILE* export_mesh_FILE;                              // +0x6c
    bool export_ascii_mesh;                              // +0x70
    uint export_num_meshes;                              // +0x74
    uint export_submesh_idx;                             // +0x78
};
// ---- items of slice s005002d0 end

// ---- items of slice s004c4650 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    cSPVector3& operator=(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
}
namespace SP {
class cSPEditorBlock_s004c_4650;
}
namespace SP {
template <class T> class AutoRefCount_s004c_4650 {
public:
    AutoRefCount_s004c_4650() : mpObject(0) {}
    AutoRefCount_s004c_4650(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s004c_4650(const AutoRefCount_s004c_4650& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004c_4650() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s004c_4650& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount_s004c_4650& operator=(const AutoRefCount_s004c_4650& o) { return operator=(o.mpObject); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* get() const { return mpObject; }
    T* mpObject;
};
}
namespace SP {
struct RefVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void ctorRef(void* p);                              // 0x429360
    void eraseRange(void* first, void* last);           // 0x426280
    void resize(int n);                                 // 0x41ee90
    void dtorRef();                                     // 0x41eb80
    bool emptyRef() const;                              // 0x526430
};
}
namespace SP {
class TickState {
public:
    static TickState* Get();                            // 0x401080
    void ClearPtr(void* p);                             // 0x522a40
    void ClearPtr100();                                 // 0x5227a0
};
}
namespace SP {
class ThreadedObject {
public:
    void Release();                                     // 0x404f90
};
}
namespace SP {
struct DeformRecord {
    char pad[0x8c];
};
}
namespace SP {
class cRuntimeCreatureResource_s004c_4650 {
public:
    char pad0[0x98];
    DeformRecord* mDeformBegin;     // +0x98
    DeformRecord* mDeformEnd;       // +0x9c
};
}
namespace SP {
class cSkinObject_s004c_4650 {
public:
    char pad0[8];
    AutoRefCount_s004c_4650<cRuntimeCreatureResource_s004c_4650> mResource;   // +0x8
};
}
namespace SP {
class cSPEditorSkinPart_s004c_4650 : public cSkinObject_s004c_4650 {
public:
    char pad9c[0xa4 - 0xc];
    RefVec mOrderedBlocks;        // +0xa4 (erase/resize through RefVec)
    char padac[0xc0 - 0xb0];
    void** mBlockMatInfosBegin;   // +0xc0
    void** mBlockMatInfosEnd;     // +0xc4
    char padc8[0xd0 - 0xc8];
    uint32_t mDrawMaterial;       // +0xd0
    uint32_t mInstance;           // +0xd4
    char padd8[0xfc - 0xd8];
    void* mDiffuseTex;            // +0xfc
    void* mNormalTex;             // +0x100
    char pad104[0x120 - 0x104];
    float mSkinResolutionRealtime;    // +0x120
    float mSkinResolutionHighQuality; // +0x124
    float mSkinResolution;            // +0x128

    void AddRef() { _InterlockedIncrement((long*)((char*)this + 4)); }
    void Release() { if (_InterlockedDecrement((long*)((char*)this + 4)) == 0) Destroy(); }
    void Destroy();

    bool BuildSkeleton();                              // 0x4ca6e0
    void RebuildSkinA();                               // 0x4cb340
    void RebuildSkinB();                               // 0x4cb820
    void Shutdown();                                   // 0x4cced0
    cSPEditorBlock_s004c_4650* GetBlockOnSkin(cSPVector3 pos);    // 0x4ccb70
    void SetDefaultMaterial(uint32_t id);              // 0x4cd020
    void SetSkinResolutions(float realtime, float highQuality);  // 0x4cd060
    bool PickSkinPart(cSPVector3 lod, cSPVector3 dir, cSPVector3* outPos,
                      cSPVector3* outNormal, float* outDist, char flag);  // 0x4ccae0
};
}
namespace SP {
class cSPEditorSkinManager_s004c_4650 {
public:
    char pad0[0x10];
    void* mModel;                        // +0x10
    void* mSceneObjectModelWorld;        // +0x14
    AutoRefCount_s004c_4650<cSPEditorSkinPart_s004c_4650> mTorsoSkin;    // +0x18
    AutoRefCount_s004c_4650<cSPEditorSkinPart_s004c_4650> mCompleteSkin; // +0x1c
    char pad20[0x48 - 0x20];
    struct BlockPart { void* block; AutoRefCount_s004c_4650<cSPEditorSkinPart_s004c_4650> part; };
    struct BlockVec {
        BlockPart* mpBegin;              // +0x48
        BlockPart* mpEnd;                // +0x4c
        int Size() { return (int)(mpEnd - mpBegin); }
        bool Empty() { return mpEnd == mpBegin; }
        BlockPart& Back() { return mpEnd[-1]; }
        void PopBack();                  // 0x4c6070
    };
    BlockVec mBlockTransforms;           // +0x48
    char pad50[0x5c - 0x50];
    AutoRefCount_s004c_4650<struct cPaintRequest> mPaintRequest;   // +0x5c
    uint32_t mDefaultMaterial;           // +0x60
    char pad64[0x78 - 0x64];
    float mPaintResolution;              // +0x78
    float mRealtimeResolution;           // +0x7c
    float mHighQualityResolution;        // +0x80
    uint8_t mPaintEnabled;               // +0x84

    bool CheckPaint() const;             // 0x4c58b0
    void* GetSkin(uint32_t which);
    void Update(uint32_t p2, char p3, uint32_t p4, uint32_t p5);   // 0x4c38e0
    void EnablePaint(char enable);                                 // 0x4c4650
    bool PickSkin(uint32_t which, cSPVector3 lod, cSPVector3 dir,
                  cSPVector3* outPos, cSPVector3* outNormal, float* outDist, char flag);
    cSPEditorBlock_s004c_4650* GetBlockOnSkin(uint32_t which, cSPVector3 pos);
    void DetachSkinParts();                                        // 0x4c4eb0
    void SetDefaultMaterial(uint32_t id);
    void SetDefaultMaterialToDetachedLimb(uint32_t id, const void* block);
    void SetSkinResolutions(float realtime, float highQuality);
};
}
namespace SP {
class cPaintRequest {
public:
    void AddRef() {}
    void Release();                      // 0x453540
};
}
namespace SP {
cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b); // 0x41db10
}
// ---- items of slice s004c4650 end

// ---- items of slice s004c5200 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement)
template<int N> inline void ScratchSlots_s004c_5200() { uint32_t s[N]; }
struct IRef { virtual void AddRef(); virtual void Release(); };
struct EObj { char pad[0xbc]; IRef ref; };
struct EPtr {
    EObj* p;
    EPtr() {}
    EPtr(const EPtr& o) : p(o.p) { if (p) p->ref.AddRef(); }
    EPtr& operator=(EObj* np) {
        if (np != p) { EObj* old = p; if (np) np->ref.AddRef(); p = np; if (old) old->ref.Release(); }
        return *this;
    }
    ~EPtr() { if (p) p->ref.Release(); }
    void Dtor5d50();
    EPtr& Assign5d80(EObj* np);
    EPtr* Copy6150(EPtr* o);
};
struct Pair { int key; EPtr ptr; };
struct PairVec {
    Pair* mpBegin; Pair* mpEnd; Pair* mpCapacity;
    void Dtor5f40();
    void PushBack5fc0(const Pair& v);
    void PopBack6070();
    void DoInsertValue(Pair* pos, const Pair& v);
    void Base45daf0();
};
struct TexData { int format; int pad4; int pad8; uint16_t w; uint16_t h; };
struct Tex {
    TexData* mpData; uint8_t mFlags; uint8_t mPad[3]; long mnRefCount;
    void Release();                             // AtomicRefCounted::Release @ 0x402420
};
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags, int a, int b) throw();
struct ThrObj {                                 // Resource::ThreadedObject: atomic count at +4
    void* vt; long mnRefCount;
    void Release();                             // @ 0x404f90
};
struct ThrRef {
    ThrObj* mp;
    ThrRef& operator=(ThrObj* p) {
        if (p != mp) { ThrObj* old = mp; if (p) _InterlockedIncrement(&p->mnRefCount); mp = p; if (old) old->Release(); }
        return *this;
    }
};
struct SkinKey { uint32_t a, b, c; };
struct SkinObj;
struct SkinRef {
    SkinObj* mp;
    SkinRef& operator=(SkinObj* p);
    SkinRef& AssignA(SkinObj* p);               // operator= with the extra frame hole of the failure-path expansion
};
struct Vec3 { float x, y, z; };
struct SkinObj {
    void* vt; int mnRefCount; ThrRef mpThr; SkinKey mKey;
    uint32_t mAbil[3]; uint32_t m24; uint32_t m28[3]; uint32_t pad34; Vec3 mPos[3];
    int m5c; int m60; uint8_t pad64; bool f65, f66, f67, f68, f69, f6a, f6b, f6c; uint8_t pad6d[3]; uint32_t pad70[5];
    SkinObj();                                  // @ 0x51df40
    int AddRef() { return mnRefCount++ + 1; }
    void Release();                             // EA::RefCountTemplate<int>::Release @ 0x453540
};
inline SkinRef& SkinRef::operator=(SkinObj* p) {
    if (p != mp) { SkinObj* old = mp; if (p) p->AddRef(); mp = p; if (old) old->Release(); }
    return *this;
}
inline SkinRef& SkinRef::AssignA(SkinObj* p) {
    if (p != mp) { SkinObj* old = mp; ScratchSlots_s004c_5200<3>(); if (p) p->AddRef(); mp = p; if (old) old->Release(); }
    return *this;
}
struct SkinDesc {                               // the descriptor passed to the update
    char pad[0x10]; uint32_t mId; char pad2[0x44]; uint32_t mModelType;
    char pad3[0x30]; uint32_t mAbilA[3]; uint32_t mAbilB[3]; Vec3 mPos[3];
    Vec3 GetPos(int i);                         // @ 0x4adca0 (sret)
    uint32_t GetAbilA(int i);                   // @ 0x4adc60
    uint32_t GetAbilB(int i);                   // @ 0x4adc80
    uint32_t ModelType() { return mModelType; }
};
struct Ed {
    char pad[0x1c]; ThrObj* m1c; char pad1c[0x3c]; SkinRef mpSkin; char pad60[4]; SkinKey mKey; Tex* m70; Tex* m74; char pad3[0x0c]; uint8_t mActive;
    SkinObj* Skin() { return mpSkin.mp; }
    ThrObj* Thr() { return m1c; }
    Tex* Diffuse() { return m70; }
    Tex* Normal() { return m74; }
    bool Check58b0();
    bool Update5200(SkinDesc* desc);
    void Get5910(Tex** a, Tex** b);
    void Diag5980(const wchar_t* dir, const wchar_t* name);
};
__forceinline void DestructRange(Pair* first, Pair* last) { for (; first < last; ++first) first->~Pair(); }
struct Transform { uint32_t d[14]; Transform(); };
struct TVec {
    Transform* mpBegin; Transform* mpEnd; Transform* mpCapacity;
    void EmplaceBack5eb0();
    void DoInsertValue(Transform* pos, const Transform& v);
};
// ---- items of slice s004c5200 end

// ---- items of slice s004c6190 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl operator delete(void*);                       // 0x00F47380
struct Elem { int val; void* obj; };
struct Vec8 { Elem* mpBegin; Elem* mpEnd; Elem* mpCap; char alloc[4]; void* mpBuffer; };
// ---- items of slice s004c6190 end

// @ 0x004c2eb0
void cSPEditorSkinManager_dtor(void* self)
{
    (void)self;
}

// @ 0x004c3030
namespace SP
{
void* cSPEditorSkinManager::AsInterface(EA::COM::InterfaceId id)
{
    switch (id) {
    case 0xcfeb4c03:
        return this;
    case 0xee3f516e:
        return this;
    }
    return 0;
}
}

// @ 0x004c3070
void create_ui_raster(void* self, void* a, void* b, void* c)
{
    (void)self; (void)a; (void)b; (void)c;
}
#pragma pack(pop)

// @ 0x004c3230
namespace SP {
void cSPEditorSkinManager_s004c_3230::UpdateTorso(TorsoFlags flags, int x)
{
    if (mModel == 0 || mTorsoSkin == 0 || mSceneObjectModelWorld == 0)
        return;
    {
        BlockVec torsoList;
        int modelBlockCount = mModel->GetBlockCount();
        cSPEditorBlock_s004c_3230** modelBlockList = mModel->begin();
        for (int iBlock = 0; iBlock < modelBlockCount; iBlock++) {
            cSPEditorBlock_s004c_3230* pBlock = modelBlockList[iBlock];
            if (pBlock->IsValid() && pBlock->mFlags.test(7))
                torsoList.push_back(pBlock);
        }

        bool dirty = false;
        if (torsoList.size() == mPreviousTorsoBlockPointers.size()) {
            for (int index = 0, cnt = torsoList.size(); index < cnt; index++) {
                if (mPreviousTorsoBlockPointers[index] != torsoList.mpBegin[index]) {
                    dirty = true;
                    break;
                }
                cSPTransform* transform = mPreviousTorsoBlockTransforms.mpBegin + index;
                if (transform->GetScale() != torsoList[index]->GetScale() ||
                    Vector3_NotEqual(transform->mTranslation, torsoList[index]->GetPosition()) ||
                    Matrix3_NotEqual(transform->mRotation, torsoList[index]->GetOrientation())) {
                    dirty = true;
                    break;
                }
            }
        } else {
            dirty = true;
        }

        if (dirty) {
            mPreviousTorsoBlockPointers.assign(torsoList.begin(), torsoList.end());
            mPreviousTorsoBlockTransforms.clear();
            for (int q = 0, num = torsoList.size(); q < num; q++) {
                mPreviousTorsoBlockTransforms.push_back_default();
                mPreviousTorsoBlockTransforms.back().SetScale(torsoList[q]->GetScale());
                mPreviousTorsoBlockTransforms.back().SetTranslation(torsoList[q]->GetPosition());
                mPreviousTorsoBlockTransforms.back().SetRotation(torsoList[q]->GetOrientation());
            }
            mTorsoSkin->Update(torsoList, false);
            mTorsoSkin->UpdateSceneObject(mSceneObjectModelWorld);
        }

        uint32_t materialId = 0xca9bb36f;
        mTorsoSkin->SetVisible(flags.b || flags.a);
        if (flags.b && flags.a)
            materialId = 0xc276b918;
        else if (flags.b)
            materialId = 0x5097cfd3;
        else if (flags.a)
            materialId = 0x154a1133;
        mTorsoSkin->SetDrawMaterial(materialId);
    }
}
}  // namespace SP

// @ 0x004c38e0
namespace SP {
void cSPEditorSkinManager_s004c_38e0::Update(uint32_t unused, bool paintAll, uint32_t p4, uint32_t p5)
{
    (void)unused;
    UpdateTorso(p4, p5);
    if (mModel != 0) {
        uint32_t nBlocks = mModel->GetBlockCount();
        cSPEditorBlock_s004c_38e0** blockList = mModel->mpBlockList;
        uint8_t anyFlag = 0;
        AllocTag alloc;
        VSet128 blocks(alloc);
        blocks.Init();
        FixedVec16 counts;
        uint8_t countInit = 0;
        counts.Init(mLimbSkins.size(), &countInit);

        for (uint32_t i = 0; i < nBlocks; i++) {
            cSPEditorBlock_s004c_38e0* block = blockList[i];
            if (!block->Paint())
                continue;

            if (block->HasAnyBlockFlag()) {
                uint8_t flag = 0;
                if (block->mFlags.test(10))
                    flag = block->mFlags.test(9) ? 1 : 0;
                anyFlag |= flag;
                blocks.push_back((uint32_t&)block);
                continue;
            }

            if (block->mField33c != 0)
                continue;
            if (!block->mFlags.test(11))
                continue;
            if (!block->mFlags.test(10))
                continue;

            int found = -1;
            int freeSlot = -1;
            int nSkins = mLimbSkins.size();
            for (int j = 0; found == -1 && j < nSkins; j++) {
                if (mLimbSkins[j].first == block)
                    found = j;
                else if (mLimbSkins[j].first == 0)
                    freeSlot = j;
            }

            if (found == -1) {
                if (freeSlot == -1) {
                    freeSlot = mLimbSkins.size();
                    mLimbSkins.push_back(LimbPair());
                    mLimbSkins[freeSlot].second = new (kEditorAllocName, 0, 0, 0, 0) cSPEditorSkinPart_s004c_38e0;
                    mLimbSkins[freeSlot].second->SetDrawMaterial(mDefaultMaterial);
                    mLimbSkins[freeSlot].second->SetModel(
                        (uint32_t)freeSlot - 0x70020768, 0xefeb80ec, true);
                    mLimbSkins[freeSlot].second->UpdateSceneObject(mSceneObjectModelWorld);
                    mLimbSkins[freeSlot].second->SetVisible(false);
                }
                mLimbSkins[freeSlot].first = block;
                mLimbSkins[freeSlot].second->SetVisible(true);
                found = freeSlot;
            }

            counts.mpBegin[found] = 1;

            AllocTag alloc2;
            VSet64 parts(alloc2);
            parts.Init();
            parts.push_back((uint32_t&)block);
            if (CollectPartsRec(block, &parts) ||
                mLimbSkins[found].second->IsHighQualityPending())
                mLimbSkins[found].second->Update((uint32_t*)&parts, false);
        }

        if (anyFlag)
            mCompleteSkin->RestartQualityTimer();
        if (mCompleteSkin->IsHighQualityPending() || mModel->mFlag50 || paintAll)
            anyFlag = 1;
        if (anyFlag) {
            mCompleteSkin->Update((uint32_t*)&blocks, paintAll);
            mCompleteSkin->UpdateSceneObject(mSceneObjectModelWorld);
            mCompleteSkin->mResource->mModelType = mModel->mName58;
        }

        int nSkins = mLimbSkins.size();
        for (int i = 0; i < nSkins; i++) {
            if (mLimbSkins[i].first != 0 && counts.mpBegin[i] == 0) {
                mLimbSkins[i].first = 0;
                mLimbSkins[i].second->SetVisible(false);
            }
        }
        for (uint32_t i = 0; i < nBlocks; i++)
            blockList[i]->SetFlag(9, false);
        mModel->mFlag50 = 0;
    }
    UpdatePaintedSkin();
}
}  // namespace SP

// @ 0x004c4290
namespace SP {
void cSPEditorSkinManager_s004c_38e0::UpdatePaintedSkin()
{
    if (!mPaintEnabled)
        return;
    if (mPaintRequest.mpObject == 0)
        return;
    if (mCompleteSkin.mpObject == 0)
        return;

    uint32_t type = HashModelType(mCompleteSkin->mResource->mModelType);
    uint8_t tag;
    if (type == 0x438f6347)
        tag = 5;
    else if (type == 0x3d97a8e4)
        tag = 4;
    else
        tag = 7;

    SkinModel* model = mCompleteSkin->mSkinModel;
    if (model != 0) {
        if (!model->mElems.empty()) {
            SkinElem* elem = model->mElems.mpBegin[0];
            if (elem->mType == 0x210) {
                PaintData* data = (PaintData*)elem->mData;
                data->mTag = tag;
                data->mA = mPaintRequest->mA;
                data->mB = mPaintRequest->mB;
                data->mC = mPaintRequest->mC;
            }
        }
    }

    int count = (int)((char*)mCompleteSkin->mMatEnd - (char*)mCompleteSkin->mMatBegin) >> 2;
    for (int i = 0; i < count; i++) {
        MatInfo* info = ((MatInfo**)mCompleteSkin->mMatBegin)[i];
        if (info == 0)
            continue;
        if (info->mElems.empty())
            continue;
        SkinElem* elem = info->mElems.mpBegin[0];
        if (elem->mType != 0x210)
            continue;
        PaintData* data = (PaintData*)elem->mData;
        data->mTag = tag;
        data->mA = mPaintRequest->mA;
        data->mB = mPaintRequest->mB;
        data->mC = mPaintRequest->mC;
    }
}
}  // namespace SP

// @ 0x004c4650
namespace SP {
void cSPEditorSkinManager_s004c_4650::EnablePaint(char enable)
{
    if (enable == 0 || mPaintEnabled != 0) {
        if (enable == 0 && mPaintEnabled != 0) {
            if (CheckPaint()) {
                void* req = mPaintRequest;
                TickState::Get()->ClearPtr(req);
            }
            TickState::Get()->ClearPtr100();
            mPaintRequest = 0;
            mPaintEnabled = 0;
        }
    } else {
        Update(0, 1, 0, 0);

        cSPEditorSkinPart_s004c_4650* part = mCompleteSkin;
        part->BuildSkeleton();
        part->RebuildSkinA();
        part->RebuildSkinB();

        cRuntimeCreatureResource_s004c_4650* res = part->mResource;
        DeformRecord* deformBegin = res->mDeformBegin;
        void** blockMatInfos = part->mBlockMatInfosBegin;
        int count = (int)((char*)res->mDeformEnd - (char*)res->mDeformBegin) / 0x8c;

        RefVec vec;
        vec.mpBegin = 0;
        vec.mpEnd = 0;
        vec.mpCapacity = 0;
        unsigned char pad = 0;
        vec.ctorRef(&pad);

        part->mOrderedBlocks.eraseRange(part->mOrderedBlocks.mpBegin, part->mOrderedBlocks.mpEnd);
        part->mOrderedBlocks.resize(count);

        for (int i = 0; i < count; ++i) {
            if ((*(uint16_t*)((char*)deformBegin + i * 0x8c + 8) & 1) == 0) {
                void* matInfo = blockMatInfos[i];
                char* sub = *(char**)((char*)matInfo + 0x10);
                vec.eraseRange(vec.mpBegin, vec.mpEnd);
                (*(void(__thiscall**)(void*, void*))(*(char**)sub + 0xf4))(sub, &vec);
                if (!vec.emptyRef()) {
                    void* newVal = *(void**)vec.mpBegin;
                    void** slot = (void**)((char*)part->mOrderedBlocks.mpBegin + i * 4);
                    if (newVal != *slot) {
                        void* oldVal = *slot;
                        if (newVal != 0) {
                            long* rc = (long*)((char*)newVal + 4);
                            _InterlockedIncrement(rc);
                        }
                        *slot = newVal;
                        if (oldVal != 0) {
                            ((ThreadedObject*)oldVal)->Release();
                        }
                    }
                }
            }
        }
        TickState::Get()->ClearPtr100();
        mPaintEnabled = 1;
        vec.dtorRef();
    }
}
}  // namespace SP

// @ 0x004c58b0
bool Ed::Check58b0()
{
    return Skin() && !Skin()->f6b && !Skin()->f6c;
}

// @ 0x004c5d50
void EPtr::Dtor5d50()
{ if (p) p->ref.Release(); }

// @ 0x004c5d80
EPtr& EPtr::Assign5d80(EObj* np)
{
    if (np != p) { EObj* old = p; if (np) np->ref.AddRef(); p = np; if (old) old->ref.Release(); }
    return *this;
}

// @ 0x004c5eb0
void TVec::EmplaceBack5eb0()
{
    if (mpEnd < mpCapacity) { new (mpEnd++) Transform(); }
    else DoInsertValue(mpEnd, Transform());
    ScratchSlots_s004c_5200<26>();
}

// @ 0x004c5f40
void PairVec::Dtor5f40()
{
    DestructRange(mpBegin, mpEnd);
    ScratchSlots_s004c_5200<3>();
    Base45daf0();
}

// @ 0x004c5fc0
void PairVec::PushBack5fc0(const Pair& v)
{
    if (mpEnd < mpCapacity) { new (mpEnd++) Pair(v); }
    else DoInsertValue(mpEnd, v);
}

// @ 0x004c60e0
void Editor_Erase60e0(void* self)
{ (void)self; }

// @ 0x004c6150
EPtr* EPtr::Copy6150(EPtr* o)
{ p = o->p; if (p) p->ref.AddRef(); return this; }

// @ 0x004c64d0
void __fastcall FUN_004c64d0(Vec8* self)
{
    if (self->mpBegin != 0) {
        int nBytes = (char*)self->mpCap - (char*)self->mpBegin;
        Elem* p = self->mpBegin;
        if (p != self->mpBuffer) {
            Elem* q = p;
            operator delete(q);
            (void)nBytes;
        }
    }
}

// @ 0x00500880
void cExportHelper::ExportMeshBegin(uint numSubmeshes, bool ascii)
{
    string8 filename(string8::CtorSprintf(), "%ls.xmf", GetName());
    export_mesh_FILE = fopen(filename.c_str(), "w");
    ScratchSlots_s0050_02d0<3>();
    export_num_meshes = numSubmeshes;
    export_submesh_idx = 0;
    export_ascii_mesh = ascii;
    FILE* f = export_mesh_FILE;
    fprintf(f, "<MESH VERSION=\"1000\" NUMSUBMESH=\"%d\">\n", export_num_meshes);
}
