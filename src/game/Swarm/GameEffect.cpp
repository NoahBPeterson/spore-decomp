// src/game/Swarm/GameEffect.cpp -- migrated from slice(s) s004ad550 by tools/migrate/rewrite.py
// Object file: Swarm/GameEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPBoundingBox.h"
#include "cSPColorRGB.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include "cSPMatrix3.h"
#include "cSPTransform.h"
#include "cSPVector3.h"

// ---- items of slice s004ad550 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
};
struct cSPMatrix3_s004a_d550 : Matrix33T {};
struct cSPVector3_s004a_d550 : Vector3T {
    cSPVector3_s004a_d550() {}
    cSPVector3_s004a_d550(const Vector3T& v) : Vector3T(v) {}
};
Vector3T& operator*=(Vector3T& v, const float& s);           // 0x41dba0
struct cSPTransform_s004a_d550 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3_s004a_d550 mTranslation;
    float mScale;
    cSPMatrix3_s004a_d550 mRotation;
    cSPTransform_s004a_d550();                                          // 0x409930
    void SetTranslation(const cSPVector3_s004a_d550& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    void SetRotation(const cSPMatrix3_s004a_d550& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
};
struct cSPBoundingBox_s004a_d550 {
    cSPVector3_s004a_d550 mMin, mMax;
    cSPBoundingBox_s004a_d550& operator=(const cSPBoundingBox_s004a_d550& b) { mMax = b.mMax; mMin = b.mMin; return *this; }
    cSPBoundingBox_s004a_d550();                                        // 0x409c00 (folded with Reset)
    cSPBoundingBox_s004a_d550(const cSPBoundingBox_s004a_d550& b);                 // 0x511140
    void Reset();                                            // 0x409c00
    void Add(const cSPBoundingBox_s004a_d550& b);                       // 0x43f050
    void Transform(const cSPTransform_s004a_d550& t);                   // 0x409dd0
};
struct cSPColorRGB_s004a_d550 {
    float r, g, b;
    cSPColorRGB_s004a_d550(const cSPColorRGB_s004a_d550& c) : r(c.r), g(c.g), b(c.b) {}
};
template<class T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> struct AutoRefCountP {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCountP& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        ScratchSlots<3>();
        return *this;
    }
};
struct false_type { false_type() {} };
struct input_iterator_tag { input_iterator_tag() {} };
struct forward_iterator_tag : input_iterator_tag { forward_iterator_tag() {} };
struct bidirectional_iterator_tag : forward_iterator_tag { bidirectional_iterator_tag() {} };
struct random_access_iterator_tag : bidirectional_iterator_tag { random_access_iterator_tag() {} };
template<class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    T* begin() const { return mpBegin; }
    T* end() const { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    bool empty() const;                                      // 0x526430
    void DoAssignFromIterator(T* first, T* last, input_iterator_tag);  // 0x4b1cc0
    // __forceinline: plain inline is declined by /Ob1 inside GetBlockBoundingBoxes
    __forceinline void DoAssign(T* first, T* last, const false_type&) { DoAssignFromIterator(first, last, random_access_iterator_tag()); }
    void assign(T* first, T* last) { DoAssign(first, last, false_type()); }
    void resize(uint32_t n);                                 // 0x4aff80
};
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wchar_t* begin() { return mpBegin; }
    wchar_t* end() { return mpEnd; }
    const wchar_t* c_str() const { return mpBegin; }
    static uint32_t CharStrlen(const wchar_t* p) { const wchar_t* pCurrent = p; while (*pCurrent) ++pCurrent; return (uint32_t)(pCurrent - p); }
    wstring& assign(const wchar_t* first, const wchar_t* last);   // 0x423650
    wstring& assign(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
};
namespace SP {
struct cSPEditorModel_s004a_d550;
}
namespace SP {
struct cSPEditorBlock_s004a_d550 {
    virtual void _v0();
    virtual int Release();
    char pad0[0x48 - 4];
    cSPVector3_s004a_d550 mPosition;                       // +0x48
    char pad1[0x60 - 0x54];
    cSPMatrix3_s004a_d550 mOrientation;                    // +0x60
    char pad2[0x1d8 - 0x84];
    float mUniformScale;                        // +0x1d8
    char pad3[0x33c - 0x1dc];
    AutoRefCount<cSPEditorBlock_s004a_d550> mParentBlock;  // +0x33c
    char pad4[0xdc8 - 0x340];
    bitset<60> mFlags;                          // +0xdc8

    float GetUniformScale() const { return mUniformScale; }
    cSPBoundingBox_s004a_d550 GetBBox(int a, int b, int c);             // 0x44ae00
    bool IsSelectable();                                     // 0x435d40
    void ClearHighlight();                                   // 0x437890
    void SetHighlight(int state, int flags);                 // 0x437a60
    Vector3T GetSnapNormal(bool world);                      // 0x4381e0
    Vector3T GetSnapPosition(bool world);                    // 0x438120
    bool Snap(Vector3T position, Vector3T normal);           // 0x437b00
    bool Load(void* source, int group, float bounds, bool a, bool b);   // 0x450f70
};
}
namespace SP {
struct cSPEditorPhysicsWorld_s004a_d550 {
    virtual void _v0();
    int mRefCount;                              // +0x04
    int AddRef() { return mRefCount++ + 1; }
    int Release();                                           // 0x453540
    int GetGroup();                                          // 0x4b91c0
    void AttachModel(cSPEditorModel_s004a_d550* model);                 // 0x4b94a0
};
}
namespace SP {
struct cSPEditorModel_s004a_d550 {
    virtual void SetName(const wchar_t* name);               // 0x00
    virtual void _v1();
    virtual void SetDescription(const wchar_t* desc);        // 0x08
    char pad0[0x18 - 4];
    vector<AutoRefCount<cSPEditorBlock_s004a_d550> > mBlockList;        // +0x18
    bool mbAllBlocksLoaded;                     // +0x2c
    AutoRefCountP<cSPEditorPhysicsWorld_s004a_d550> mPhysicsWorld;      // +0x30
    char pad1[0x38 - 0x34];
    float mBounds;                              // +0x38
    char pad2[0x5c - 0x3c];
    wstring mName;                              // +0x5c
    wstring mDescription;                       // +0x6c
    wstring mCleanName;                         // +0x7c
    uint32_t mSkinEffects[3];                   // +0x8c
    uint32_t mSkinEffectSeeds[3];               // +0x98
    cSPColorRGB_s004a_d550 mSkinColors[3];                 // +0xa4
    vector<cSPBoundingBox_s004a_d550> mBBoxesOverride;     // +0xc8

    cSPBoundingBox_s004a_d550 GetBoundingBox(bool selectableOnly);
    void GetBlockBoundingBoxes(vector<cSPBoundingBox_s004a_d550>& boxes);
    void SetBBoxesOverride(const vector<cSPBoundingBox_s004a_d550>& boxes);
    uint32_t GetSkinEffect(int i);
    uint32_t GetSkinEffectSeed(int i);
    cSPColorRGB_s004a_d550 GetSkinColor(int i);
    void SetSkinEffect(int i, uint32_t effect);
    void SetSkinEffectSeed(int i, uint32_t seed);
    void SetSkinColor(int i, cSPColorRGB_s004a_d550 color);
    cSPEditorBlock_s004a_d550* GetBlock(uint32_t index);                // 0x4accb0
    int GetBlockCount();                                     // 0x4accf0
    void ClearHighlights();
    void SetHighlights(int state);
    bool SnapBlocks();
    void Update();
    bool LoadBlocks(void* source, cSPEditorPhysicsWorld_s004a_d550* world, bool a, bool b);
};
}
// ---- items of slice s004ad550 end

// @ 0x004ae250
namespace SP {
void cSPEditorModel_s004a_d550::Update()
{
}
}  // namespace SP
