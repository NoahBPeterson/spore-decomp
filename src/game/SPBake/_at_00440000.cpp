// src/game/SPBake/_at_00440000.cpp -- migrated from slice(s) s00448380 by tools/migrate/rewrite.py
// Object file: SPBake/_at_00440000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPTransform.h"
#include "cSPVector3.h"

// ---- items of slice s00448380 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWord(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
};
}
namespace EA {
template <class T>
struct AutoRefCount_s0044_8380 {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount_s0044_8380& operator=(T* p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
}
namespace SP {
struct cSPEditorBlock_s0044_8380;
}
namespace SP {
struct cMWModel_s0044_8380;
}
namespace SP {
struct cIModelWorld_s0044_8380;
}
namespace SP {
struct cPropertyList_s0044_8380;
}
namespace SP {
struct cSPEditorHandleDeform_s0044_8380;
}
namespace SP {
struct cSPEditorModel_s0044_8380;
}
namespace SP {
struct cSPTransformOps;
}
namespace SP {
using EA::AutoRefCount_s0044_8380;
}
namespace SP {
using eastl::bitset;
}
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
}
namespace SP {
struct Key3 { int a, b, c; };
}
namespace SP {
struct cSPTransformOps {
    virtual void AddRef();                      // vtable +0x00 (slot 0)
    virtual void Release();                     // vtable +0x04 (slot 1)
    cSPTransformOps* Assign(const void* p);     // 0x00537dc0
};
}
namespace SP {
struct cMWModel_s0044_8380 {
    cIModelWorld_s0044_8380* mpWorld;                      // +0x00
    char pad04[4];
    cSPTransformOps mXformOps;                  // +0x08
    char pad0c[0x40 - 0x0c];
    int mRefCount;                              // +0x40
    uint32_t mGroups[2];                        // +0x44
    cSPVector3 mOffset;                         // +0x4c
    char pad58[0x64 - 0x58];
    AutoRefCount_s0044_8380<cSPTransformOps> mOwner;       // +0x64
    void AddRef() { mRefCount++; }
    void Release();                             // 0x0040f360
};
}
namespace SP {
struct cSPEditorModel_s0044_8380 {
    float GetScale();                           // 0x004adaa0
    bool UsingSymmetry() const;                 // 0x004adc40
};
}
namespace SP {
struct cSPEditorHandleDeform_s0044_8380 {
    char pad0[0x8c];
    void* mHandleID;                            // +0x8c
    char pad90[0x180 - 0x90];
    float mDelta;                               // +0x180
    bool RecordHandlePosition(char flag);       // 0x00480e90
    void Update();                              // 0x00482670
};
}
namespace SP {
struct BlockList {
    AutoRefCount_s0044_8380<cSPEditorBlock_s0044_8380>* mpBegin;
    AutoRefCount_s0044_8380<cSPEditorBlock_s0044_8380>* mpEnd;
    AutoRefCount_s0044_8380<cSPEditorBlock_s0044_8380>* mpCapacity;
    int mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    AutoRefCount_s0044_8380<cSPEditorBlock_s0044_8380>& operator[](int i) { return mpBegin[i]; }
    bool empty();                               // 0x00526430
};
}
namespace SP {
struct HandleList {
    AutoRefCount_s0044_8380<cSPEditorHandleDeform_s0044_8380>* mpBegin;
    AutoRefCount_s0044_8380<cSPEditorHandleDeform_s0044_8380>* mpEnd;
    AutoRefCount_s0044_8380<cSPEditorHandleDeform_s0044_8380>* mpCapacity;
    int mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    AutoRefCount_s0044_8380<cSPEditorHandleDeform_s0044_8380>& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
void sub_458f60(void* a, void* b, Key3 key, int c);   // 0x00458f60
}
namespace SP {
struct cIModelWorld_s0044_8380 {
virtual void w0();
virtual void w1();
virtual void w2();
    virtual cMWModel_s0044_8380* CreateEffectsMask(unsigned instance, unsigned group, int kind);   // +0x0c (slot 3)
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
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
    virtual void SetEffectsModel(cMWModel_s0044_8380* model);                                      // +0x58 (slot 22)
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
    virtual void SetModelHandleValue(cMWModel_s0044_8380* model, void* id, float value, int flag); // +0x74 (slot 29)
virtual void w30();
virtual void w31();
    virtual void GetModelHandleRange(cMWModel_s0044_8380* model, void* id, float* lo, float* hi, int flag);   // +0x80 (slot 32)
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
    virtual void SetInWorld(cMWModel_s0044_8380* model, int flag);                                  // +0x16c (slot 91)
};
}
namespace SP {
struct cSPEditorBlock_s0044_8380 {
    virtual void v0();                          // vtable +0x00 (slot 0)
    virtual void AddRef();                      // vtable +0x04 (slot 1)
    virtual void Release();                     // vtable +0x08 (slot 2)
    char pad04[4];
    cSPTransformOps mXformOps;                  // +0x08
    AutoRefCount_s0044_8380<cPropertyList_s0044_8380> mPropList;      // +0x0c
    AutoRefCount_s0044_8380<cMWModel_s0044_8380> mModel;              // +0x10
    AutoRefCount_s0044_8380<cMWModel_s0044_8380> mEffectsMaskObject;  // +0x14
    AutoRefCount_s0044_8380<cIModelWorld_s0044_8380> mModelWorld;     // +0x18
    unsigned mInstance;                         // +0x1c
    unsigned mGroup;                            // +0x20
    char pad24[0x28 - 0x24];
    cSPEditorModel_s0044_8380* mEditorModel;               // +0x28
    char pad2c[0x48 - 0x2c];
    cSPVector3 mPosition;                       // +0x48
    char pad54[0x33c - 0x54];
    void* mField33c;                            // +0x33c
    BlockList mChildBlockList;                  // +0x340
    char pad350[0x3e0 - 0x350];
    AutoRefCount_s0044_8380<cSPEditorBlock_s0044_8380> mSymmetricBlock;   // +0x3e0
    char pad3e4[0x438 - 0x3e4];
    bool mField438;                             // +0x438
    char pad439[0x6cc - 0x439];
    HandleList mItems;                          // +0x6cc
    char pad6dc[0xdc8 - 0x6dc];
    bitset<60> mFlags;                          // +0xdc8
    char paddd0[0xde0 - 0xdd0];
    bool mFieldde0;                             // +0xde0

    enum eBlockFlags { kBlockFlagMax = 60 };

    // this slice
    float GetEffectsMaskScale();                        // 0x00448380
    bool RecordHandlePositionAt(int index, char flag);  // 0x00448480
    bool RecordAllHandlePositions();                    // 0x004484f0
    void UpdateAllHandles();                            // 0x004485d0
    void AddToEffectsMask(cSPVector3 pos, bool flag);   // 0x00448690
    void UpdateEffectsMask();                           // 0x004488c0
    void RemoveFromEffectsMask();                       // 0x00448a80
    void InitDeformAnimationsA();                       // 0x00448b10
    void InitDeformAnimationsB(bool flag);              // 0x00448b80
    bool HasChildWithFlag();                            // 0x00448c10
    void ResetSymmetryBlocks();                         // 0x00448d60
    void ClearSymmetryRecursive();                      // 0x00448dd0
    void SetPosition(const cSPVector3& pos, bool flag); // 0x00448e90

    // neighbours (defined in other slices)
    void SetFlag(eBlockFlags flag, bool value);         // 0x00435a10
    void A48fa0(cSPVector3 pos, bool updatePhysics);    // 0x00448fa0
};
}
// ---- items of slice s00448380 end

// @ 0x004488c0
namespace SP {
void cSPEditorBlock_s0044_8380::UpdateEffectsMask()
{
    if (!mEffectsMaskObject)
        return;
    mEffectsMaskObject->mXformOps.Assign(&mModel->mXformOps);
    mModelWorld->SetEffectsModel(mEffectsMaskObject);
    InitDeformAnimationsB(1);
    int i = 0;
    int count = mItems.size();
    for (; i < count; i++) {
        float lo = 0.0f;
        float hi = 0.0f;
        mModelWorld->GetModelHandleRange(mEffectsMaskObject, mItems[i]->mHandleID, &lo, &hi, 0);
        float value = (hi - lo) * mItems[i]->mDelta + lo;
        mModelWorld->SetModelHandleValue(mEffectsMaskObject, mItems[i]->mHandleID, value, 0);
    }
}
}  // namespace SP

// @ 0x00448b10
namespace SP {
void cSPEditorBlock_s0044_8380::InitDeformAnimationsA()
{
    void* pModel = mModel;
    Key3 key = { 0, 0, 0 };
    key.a = (int)mInstance;
    key.c = (int)mGroup;
    sub_458f60(pModel, mModelWorld, key, 1);
}
}  // namespace SP

// @ 0x00448c10
namespace SP {
bool cSPEditorBlock_s0044_8380::HasChildWithFlag()
{
    if (mChildBlockList.empty() == false) {
        int i = 0;
        int count = mChildBlockList.size();
        for (; i < count; i++) {
            cSPEditorBlock_s0044_8380* child = mChildBlockList[i];
            if (child->mFlags.test(0xc) && !mChildBlockList[i]->mFlags.test(0x14))
                return true;
        }
    }
    return false;
}
}  // namespace SP

// @ 0x00448d60
namespace SP {
void cSPEditorBlock_s0044_8380::ResetSymmetryBlocks()
{
    cSPEditorBlock_s0044_8380* p = mSymmetricBlock;
    if (p)
        p->AddRef();
    ClearSymmetryRecursive();
    if (mEditorModel && mEditorModel->UsingSymmetry() && p)
        p->ClearSymmetryRecursive();
    if (p)
        p->Release();
}
}  // namespace SP

// @ 0x00448dd0
namespace SP {
void cSPEditorBlock_s0044_8380::ClearSymmetryRecursive()
{
    SetFlag((eBlockFlags)0x39, true);
    mSymmetricBlock = 0;
    int i = 0;
    int count = mChildBlockList.size();
    for (; i < count; i++)
        mChildBlockList[i]->ClearSymmetryRecursive();
}
}  // namespace SP
