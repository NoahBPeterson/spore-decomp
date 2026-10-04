// Slice s004ad550: SP::cSPEditorModel bounding boxes, skin settings, name/description, block placement/loading.
// Module flags: /Od /Ob1 /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- rw::math / cSP math types ----
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
struct cSPMatrix3 : Matrix33T {};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
};
Vector3T& operator*=(Vector3T& v, const float& s);           // 0x41dba0

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3 mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    cSPTransform();                                          // 0x409930
    void SetTranslation(const cSPVector3& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
};

struct cSPBoundingBox {
    cSPVector3 mMin, mMax;
    cSPBoundingBox& operator=(const cSPBoundingBox& b) { mMax = b.mMax; mMin = b.mMin; return *this; }
    cSPBoundingBox();                                        // 0x409c00 (folded with Reset)
    cSPBoundingBox(const cSPBoundingBox& b);                 // 0x511140
    void Reset();                                            // 0x409c00
    void Add(const cSPBoundingBox& b);                       // 0x43f050
    void Transform(const cSPTransform& t);                   // 0x409dd0
};

struct cSPColorRGB {
    float r, g, b;
    cSPColorRGB(const cSPColorRGB& c) : r(c.r), g(c.g), b(c.b) {}
};

// ---- EASTL-style containers ----
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

template<class I, class T> inline void replace(I first, I last, const T& old_value, const T& new_value)
{
    for (; first != last; ++first) {
        if (*first == old_value) *first = new_value;
    }
}

namespace EA { namespace IO {
int MakeFileNameValid(const wchar_t* src, wchar_t* dst, int platform);   // 0x931250
} }

namespace SP {

struct cMessageData {
    struct Arg { const void* mpValue; uint32_t mType; };
    Arg mArgs[2];
    uint32_t mFlags;
    uint32_t mReserved;
    cMessageData() { mFlags = 0; }
    void SetArg(int i, const void* p) { mArgs[i].mpValue = p; }
};
struct cMessageServer {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void PostMessage(uint32_t id, cMessageData* data, int flags);   // 0x14
};
cMessageServer* MessageServer();                             // 0x67dcc0
inline cMessageServer* GetMessageServer() { return MessageServer(); }

struct cSPEditorModel;

struct cSPEditorBlock {
    virtual void _v0();
    virtual int Release();
    char pad0[0x48 - 4];
    cSPVector3 mPosition;                       // +0x48
    char pad1[0x60 - 0x54];
    cSPMatrix3 mOrientation;                    // +0x60
    char pad2[0x1d8 - 0x84];
    float mUniformScale;                        // +0x1d8
    char pad3[0x33c - 0x1dc];
    AutoRefCount<cSPEditorBlock> mParentBlock;  // +0x33c
    char pad4[0xdc8 - 0x340];
    bitset<60> mFlags;                          // +0xdc8

    float GetUniformScale() const { return mUniformScale; }
    cSPBoundingBox GetBBox(int a, int b, int c);             // 0x44ae00
    bool IsSelectable();                                     // 0x435d40
    void ClearHighlight();                                   // 0x437890
    void SetHighlight(int state, int flags);                 // 0x437a60
    Vector3T GetSnapNormal(bool world);                      // 0x4381e0
    Vector3T GetSnapPosition(bool world);                    // 0x438120
    bool Snap(Vector3T position, Vector3T normal);           // 0x437b00
    bool Load(void* source, int group, float bounds, bool a, bool b);   // 0x450f70
};

struct cSPEditorPhysicsWorld {
    virtual void _v0();
    int mRefCount;                              // +0x04
    int AddRef() { return mRefCount++ + 1; }
    int Release();                                           // 0x453540
    int GetGroup();                                          // 0x4b91c0
    void AttachModel(cSPEditorModel* model);                 // 0x4b94a0
};

struct cSPEditorModel {
    virtual void SetName(const wchar_t* name);               // 0x00
    virtual void _v1();
    virtual void SetDescription(const wchar_t* desc);        // 0x08
    char pad0[0x18 - 4];
    vector<AutoRefCount<cSPEditorBlock> > mBlockList;        // +0x18
    bool mbAllBlocksLoaded;                     // +0x2c
    AutoRefCountP<cSPEditorPhysicsWorld> mPhysicsWorld;      // +0x30
    char pad1[0x38 - 0x34];
    float mBounds;                              // +0x38
    char pad2[0x5c - 0x3c];
    wstring mName;                              // +0x5c
    wstring mDescription;                       // +0x6c
    wstring mCleanName;                         // +0x7c
    uint32_t mSkinEffects[3];                   // +0x8c
    uint32_t mSkinEffectSeeds[3];               // +0x98
    cSPColorRGB mSkinColors[3];                 // +0xa4
    vector<cSPBoundingBox> mBBoxesOverride;     // +0xc8

    cSPBoundingBox GetBoundingBox(bool selectableOnly);
    void GetBlockBoundingBoxes(vector<cSPBoundingBox>& boxes);
    void SetBBoxesOverride(const vector<cSPBoundingBox>& boxes);
    uint32_t GetSkinEffect(int i);
    uint32_t GetSkinEffectSeed(int i);
    cSPColorRGB GetSkinColor(int i);
    void SetSkinEffect(int i, uint32_t effect);
    void SetSkinEffectSeed(int i, uint32_t seed);
    void SetSkinColor(int i, cSPColorRGB color);
    cSPEditorBlock* GetBlock(uint32_t index);                // 0x4accb0
    int GetBlockCount();                                     // 0x4accf0
    void ClearHighlights();
    void SetHighlights(int state);
    bool SnapBlocks();
    void Update();
    bool LoadBlocks(void* source, cSPEditorPhysicsWorld* world, bool a, bool b);
};

// @ 0x4ad550
cSPBoundingBox cSPEditorModel::GetBoundingBox(bool selectableOnly)
{
    cSPBoundingBox bbox;
    bbox.Reset();
    ScratchSlots<12>();
    uint32_t count = mBlockList.size();
    if (count > 0) {
        bbox = mBlockList[0]->GetBBox(0, 0, 0);
        for (int i = 1, n = mBlockList.size(); i < n; i++) {
            if (selectableOnly && !mBlockList[i]->IsSelectable()) continue;
            bbox.Add(mBlockList[i]->GetBBox(0, 0, 0));
        }
    }
    ScratchSlots<1>();
    return bbox;
}

// @ 0x4ad6f0
void cSPEditorModel::GetBlockBoundingBoxes(vector<cSPBoundingBox>& boxes)
{
    if (!mBBoxesOverride.empty()) {
        boxes.assign(mBBoxesOverride.begin(), mBBoxesOverride.end());
    } else {
    boxes.resize(mBlockList.size());
    ScratchSlots<9>();
    for (int i = 0, n = mBlockList.size(); i < n; i++) {
        boxes[i] = mBlockList[i]->GetBBox(2, 1, 0);
        if (mBlockList[i]->mFlags.test(10)) {
            boxes[i].mMin *= 1.1f;
            boxes[i].mMax *= 1.1f;
        }
        cSPTransform t;
        ScratchSlots<1>();
        t.SetTranslation(mBlockList[i]->mPosition);
        t.SetRotation(mBlockList[i]->mOrientation);
        t.SetScale(mBlockList[i]->GetUniformScale());
        boxes[i].Transform(t);
        ScratchSlots<41>();
    }
    }
}

// @ 0x4ada40
void cSPEditorModel::SetBBoxesOverride(const vector<cSPBoundingBox>& boxes)
{
    mBBoxesOverride.assign(boxes.begin(), boxes.end());
}

// @ 0x4adc60
uint32_t cSPEditorModel::GetSkinEffect(int i)
{
    return mSkinEffects[i];
}

// @ 0x4adc80
uint32_t cSPEditorModel::GetSkinEffectSeed(int i)
{
    return mSkinEffectSeeds[i];
}

// @ 0x4adca0
cSPColorRGB cSPEditorModel::GetSkinColor(int i)
{
    return mSkinColors[i];
}

// @ 0x4adcf0
void cSPEditorModel::SetSkinEffect(int i, uint32_t effect)
{
    mSkinEffects[i] = effect;
}

// @ 0x4add10
void cSPEditorModel::SetSkinEffectSeed(int i, uint32_t seed)
{
    mSkinEffectSeeds[i] = seed;
}

// @ 0x4add30
void cSPEditorModel::SetSkinColor(int i, cSPColorRGB color)
{
    mSkinColors[i] = color;
}

// @ 0x4add60
void cSPEditorModel::SetName(const wchar_t* name)
{
    mName.assign(name);
    wchar_t block[256];
    EA::IO::MakeFileNameValid(name, block, 4);
    mCleanName.assign(block);
    replace(mCleanName.begin(), mCleanName.end(), L'!', L'_');
    cMessageData data;
    data.SetArg(0, this);
    data.SetArg(1, mName.c_str());
    GetMessageServer()->PostMessage(0x7aa519dc, &data, 0);
}

// @ 0x4adf20
void cSPEditorModel::SetDescription(const wchar_t* desc)
{
    mDescription.assign(desc);
    cMessageData data;
    data.SetArg(0, this);
    data.SetArg(1, mDescription.c_str());
    GetMessageServer()->PostMessage(0x14418c3f, &data, 0);
}

// @ 0x4ae040
void cSPEditorModel::ClearHighlights()
{
    for (int tmp = 0, t14 = GetBlockCount(); tmp < t14; tmp++) {
        cSPEditorBlock* block = GetBlock(tmp);
        block->ClearHighlight();
    }
}

// @ 0x4ae090
void cSPEditorModel::SetHighlights(int state)
{
    for (int tmp = 0, t14 = GetBlockCount(); tmp < t14; tmp++) {
        cSPEditorBlock* block = GetBlock(tmp);
        block->SetHighlight(state, 0);
    }
}

// @ 0x4ae0f0
bool cSPEditorModel::SnapBlocks()
{
    bool result = true;
    for (int tmp = 0, t14 = GetBlockCount(); tmp < t14; tmp++) {
        cSPEditorBlock* block = GetBlock(tmp);
        if (block->mParentBlock && !block->mFlags.test(7) && !block->mFlags.test(0x1f)) {
            bool snapped = block->Snap(block->GetSnapPosition(true), block->GetSnapNormal(true));
            result = result && snapped;
        }
    }
    return result;
}

// @ 0x4ae250
void cSPEditorModel::Update()
{
}

// @ 0x4ae260
bool cSPEditorModel::LoadBlocks(void* source, cSPEditorPhysicsWorld* world, bool a, bool b)
{
    mbAllBlocksLoaded = true;
    mPhysicsWorld = world;
    int group = 0;
    if (world) group = world->GetGroup();
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mbAllBlocksLoaded = mBlockList[i]->Load(source, group, mBounds, a, b) && mbAllBlocksLoaded;
    if (mPhysicsWorld) mPhysicsWorld->AttachModel(this);
    return true;
}

}  // namespace SP
