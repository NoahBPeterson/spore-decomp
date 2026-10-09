// Slice s004c73f0: SP::cSkinObject::UpdateBlocks (12342 bytes, /Od).
// Rebuilds the runtime creature resource (one 0x8c-byte cRuntimeCreatureBlock per editor
// rigblock, plus the capability / deform / transform side tables) from the editor's rigblocks.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast /Oy (no /EHsc; the original's frame is
// 16-byte aligned).
//
// Name: dev-PDB candidate (caller-scored) SP::cSkinObject::UpdateBlocks; the receiver's layout
// matches cSkinObject (mResource at +0x8, mBlockProps at +0xc, mNodeBlockMap at +0x20), but
// retail is larger than the 2008 PDB (cRuntimeCreatureResource is 0x128 here, its block 0x8c).
// Rigblock offsets follow ModAPI Editors::EditorRigblock (2017 build).
#include "types.h"

#pragma pack(push, 4)

void* operator new(unsigned int size, const char* pName, int flags, int debugFlags, int file, int line); // 0x00F473A0
void* memset(void* p, int c, unsigned int n);

// ---------------------------------------------------------------------------------------------
// Math types
// ---------------------------------------------------------------------------------------------
struct RwVector3 { float x, y, z; };

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    float& operator[](int i) { return (&x)[i]; }
    void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
    Vector3& operator=(const RwVector3& v);            // 0x004098A0 (fld/fstp member copy)
};

struct Matrix3 {
    float m[3][3];
};

namespace rw { namespace math { namespace fpu {
    template <class T, int A> struct Matrix33Template {
        T m[3][3];
        Matrix33Template() {}
        Matrix33Template(const Matrix33Template& x);
    };
    Matrix33Template<float, 0> Matrix33FromEulerXYZ(const Vector3& angles); // 0x00453920
}}}

struct RwMatrix33 {
    float m[3][3];
    RwMatrix33(const rw::math::fpu::Matrix33Template<float, 0>& x); // 0x0041CB40 (row-wise copy)
};

Vector3 operator*(const Vector3& v, const float& s);        // 0x0041DCA0
RwVector3 operator*(const Vector3& v, const RwMatrix33& m); // 0x0041DAF0
Vector3& operator*=(Vector3& v, const float& s);           // 0x0041DBA0
Vector3& operator+=(Vector3& v, const Vector3& w);         // 0x0041DDB0 (Vector3_Add)
float VectorLength(const Vector3& v);                      // 0x0040AE50

extern float gPI;                                          // 0x015D928C

struct Transform {                                         // cSPTransform, 0x38
    uint16_t mFlags;
    uint16_t mVersion;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;
    Transform();                                           // 0x00409930
};

struct RectF {                                             // EA::RectT<float>
    float left, top, right, bottom;
    RectF(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {}
};

struct ResourceKey {
    uint32_t instance;
    uint32_t type;
    uint32_t group;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instance(i), type(t), group(g) {}
};

template <class T> inline T Lerp(T a, T b, T t)
{
    T d = b - a;
    d = d * t;
    return a + d;
}

// Saturate to [0, 1] with maxss/minss (NaN gives 1).
inline float Clamp01(float v)
{
    float hi = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, v
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}

// ---------------------------------------------------------------------------------------------
// Ref counting / properties
// ---------------------------------------------------------------------------------------------
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator bool() const { return mpObject != 0; }
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
    T** AsPointer();                                       // 0x0041D870 (releases, returns &mpObject)
};

struct Property {
    void* mpData;          // +0x00
    uint32_t pad04;
    int mnItemCount;       // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;      // +0x10
    uint16_t mnType;       // +0x12

    int GetItemCount() const
    {
        if (mnFlags & 0x30)
            return mnItemCount;
        else if (mnType)
            return 1;
        else
            return 0;
    }
    template <class T> T* GetValues()
    {
        if (mnFlags & 0x30)
            return (T*)mpData;
        else if (mnType)
            return (T*)this;
        else
            return 0;
    }
};

class cPropertyList {
public:
    virtual int AddRef();                                  // 0x00
    virtual int Release();                                 // 0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual bool HasProperty(uint32_t id);                 // 0x1c
    virtual void v20();
    virtual void v24();
    virtual Property* GetProperty(uint32_t id);            // 0x28
};

class cPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** ppList); // 0x2c
};

namespace SP {
    cPropertyManager* PropertyManager();                                                  // 0x0067DE30
    bool GetPropertyAsVector3(const cPropertyList* p, uint32_t id, Vector3* out);        // 0x006A1110
    bool GetPropertyAsKeyInstance(const cPropertyList* p, uint32_t id, uint32_t* out);   // 0x006A12A0
    bool GetPropertyAsKeyArray(const cPropertyList* p, uint32_t id, int* count, ResourceKey** out);      // 0x006A0AE0
    bool GetPropertyAsTransformArray(const cPropertyList* p, uint32_t id, int* count, Transform** out);  // 0x006A0C30
}
bool GetBoolProperty(const cPropertyList* p, uint32_t id, bool* out);   // 0x00407190
bool GetFloatProperty(const cPropertyList* p, uint32_t id, float* out); // 0x0040CF10

extern const uint32_t kDeformPropertyLists[0x5f];                       // 0x013F03D0

// ---------------------------------------------------------------------------------------------
// Editor rigblock (ModAPI Editors::EditorRigblock, 0xe08)
// ---------------------------------------------------------------------------------------------
template <uint32_t N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const
    {
        if (i < N) {
            const uint32_t w = mWord[i >> 5];
            return (w & (1 << (i % 32))) != 0;
        }
        return false;
    }
};

struct CapabilityLevel {
    bool mIsVariableLevel; // +0x00
    int mMinLevel;         // +0x04
    int mLevel;            // +0x08
    int mHandleIndex;      // +0x0c
};
struct EditorRigblockCapability { // 0x14
    uint32_t mPropertyID;
    CapabilityLevel mLevel;
};

struct CapabilityVector {
    EditorRigblockCapability* mpBegin;
    EditorRigblockCapability* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct EditorRigblock {
    uint32_t pad00[3];
    AutoRefCount<cPropertyList> mpPropList;  // +0x0c
    uint32_t pad10[3];
    uint32_t mInstanceID;                    // +0x1c
    uint32_t mGroupID;                       // +0x20
    uint32_t pad24[9];
    Vector3 mPosition;                       // +0x48
    uint32_t pad54[3];
    Matrix3 mTotalOrientation;               // +0x60
    uint32_t pad84[0x52];
    int mLimbType;                           // +0x1cc
    float mMuscleScale;                      // +0x1d0
    uint32_t pad1d4;
    float mSize;                             // +0x1d8
    uint32_t pad1dc;
    float mModelMinScale;                    // +0x1e0
    float mModelMaxScale;                    // +0x1e4
    uint32_t pad1e8[0x55];
    EditorRigblock* mpParent;                // +0x33c
    uint32_t pad340[0x28];
    EditorRigblock* mpSymmetricRigblock;     // +0x3e0
    EditorRigblock* mpAsymmetricRigblock;    // +0x3e4
    uint32_t pad3e8[0x82];
    int mModelBakeLevel;                     // +0x5f0
    uint32_t pad5f4[0x186];
    CapabilityVector mCapabilities;          // +0xc0c (fixed_vector<EditorRigblockCapability,20>)
    uint32_t padc14[0x6d];
    bitset<60> mBooleanAttributes;           // +0xdc8
    uint32_t paddd0[0xd];
    uint32_t mIndex;                         // +0xe04

    float GetSize() const { return mSize; }
    float GetMuscleScale() const { return mMuscleScale; }
    EditorRigblock* GetParent() const { return mpParent; }
    EditorRigblock* GetSymmetric() const { return mpSymmetricRigblock; }
    EditorRigblock* GetAsymmetric() const { return mpAsymmetricRigblock; }
    uint32_t GetInstanceID() const { return mInstanceID; }
    uint32_t GetGroupID() const { return mGroupID; }

    uint32_t GetModelUInt32(uint32_t propID);    // 0x00435C20
    int GetHandleCount();                        // 0x0043C040
    float GetHandleValue(int index);             // 0x0043C2D0
    uint32_t GetHandleID(int index);             // 0x0043C340
    Vector3 GetBoneVector();                     // 0x0043E080
    float GetBaseJointScale();                   // 0x0043EED0
    float GetEndJointScale();                    // 0x0043F3F0
};

uint32_t GetCapabilityCode(uint32_t propertyID); // 0x004615B0

// Global block-data provider (0x00401010 returns *0x015D0C04).
class IBlockDataProvider {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual bool GetBounds(uint32_t instance, uint32_t group, const float* deforms, int numDeforms,
                           Vector3* pMin, Vector3* pMax);                          // 0x54
    virtual void v58();
    virtual bool GetBakeKey(uint32_t instance, uint32_t group, ResourceKey* pKey);  // 0x5c
};
IBlockDataProvider* GetBlockDataProvider();      // 0x00401010

// ---------------------------------------------------------------------------------------------
// EASTL containers (only the members used here)
// ---------------------------------------------------------------------------------------------
struct sp_vector_allocator { const char* mpName; uint32_t mFlags; };
struct false_type { false_type() {} };

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    T& back() { return *(mpEnd - 1); }
    void clear() { erase(mpBegin, mpEnd); }
    template <class It> void assign(It first, It last) { DoAssignFromIterator(first, last, false_type()); }

    T* erase(T* first, T* last);                                   // per instantiation
    void resize(uint32_t n);                                       // per instantiation
    void resize(uint32_t n, const T& value);                       // 0x004CD710 (RectF)
    void push_back();                                              // 0x004CD4C0 (Rec38)
    template <class It> void DoAssignFromIterator(It first, It last, false_type); // 0x004D04F0 / 0x004D06E0
};

// fixed_vector<T, N>: header + inline buffer.
template <class T, int N> struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    T mBuffer[N];

    fixed_vector();                                  // 0x004CD140 / 0x0041D050
    explicit fixed_vector(uint32_t n);               // 0x004CD0C0
    ~fixed_vector() { for (T* p = mpBegin; p < mpEnd; ++p) {} DoFree(); }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void push_back(const T& value);                  // 0x00422380 / 0x004CD810 / 0x004CD8F0
    void DoFree();                                   // 0x004C0B80 / 0x004C64D0
};

// The topological order buffer (fixed_vector<int, 64>) is built in two steps.
struct AllocTag { AllocTag() {} };
struct IndexVector {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    uint32_t mAllocator[3];
    int mBuffer[64];

    IndexVector() { InitBase(AllocTag()); InitBuffer(); }
    ~IndexVector() { for (int* p = mpBegin; p < mpEnd; ++p) {} DoFree(); }
    int size() const { return (int)(mpEnd - mpBegin); }
    int& operator[](int i) { return mpBegin[i]; }
    IndexVector* InitBase(const AllocTag&);          // 0x00540470
    void InitBuffer();                               // 0x004C5E70
    void DoFree();                                   // 0x00425990
};

struct SkelNode {           // per-input-block node for the topological sort
    short mParent;
    short mType;
};

// fixed_hash_map<uint32_t, MappedPair> (16 nodes)
struct MappedPair { int mIndex; float mWeight; };
struct HashNode { uint32_t mKey; MappedPair mValue; HashNode* mpNext; };
template <class T> struct hash {};                    // no user ctor: the default-arg temp is zeroed
template <class T> struct equal_to { equal_to() {} };

struct hashtable_iterator {
    HashNode* mpNode;
    HashNode** mpBucket;
    hashtable_iterator(HashNode** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
    HashNode& operator*() const { return *mpNode; }
    bool operator!=(const hashtable_iterator& x) const { return mpNode != x.mpNode; }
    hashtable_iterator& operator++()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
        return *this;
    }
};

struct SoundMap {
    uint32_t mFunctors;
    HashNode** mpBucketArray;   // +0x04
    uint32_t mnBucketCount;     // +0x08
    uint32_t mRest[0x74];

    SoundMap(const hash<uint32_t>& h = hash<uint32_t>(), const equal_to<uint32_t>& eq = equal_to<uint32_t>()); // 0x004CD1B0
    ~SoundMap();                                       // 0x004CDA30
    hashtable_iterator begin();                        // 0x00564140
    hashtable_iterator end() { return hashtable_iterator(mpBucketArray + mnBucketCount); }
    MappedPair& operator[](const uint32_t& key);       // 0x004CD240
};

// ---------------------------------------------------------------------------------------------
// Runtime creature resource
// ---------------------------------------------------------------------------------------------
struct cRuntimeCreatureBlock {   // 0x8c (retail; dev PDB is 0x80 without mOffset)
    short mBlockIndex;           // +0x00
    short mNodeIndex;            // +0x02
    short mParentIndex;          // +0x04
    short mSymmetricIndex;       // +0x06
    uint16_t mFlags;             // +0x08
    uint8_t mSubmeshId;          // +0x0a
    uint8_t mBlockType;          // +0x0b
    uint16_t mCapOffset;         // +0x0c
    uint16_t mDeformOffset;      // +0x0e
    uint8_t mNumCaps;            // +0x10
    uint8_t mNumDeforms;         // +0x11
    uint16_t m_RESERVED;         // +0x12
    Vector3 mBoundsMin;          // +0x14
    Vector3 mBoundsMax;          // +0x20
    float mScale;                // +0x2c
    Matrix3 mRotation;           // +0x30
    Vector3 mTranslation;        // +0x54
    Vector3 mOffset;             // +0x60
    float mScaleFactor;          // +0x6c
    float mBoneLength;           // +0x70
    float mMuscleScale;          // +0x74
    float mBaseJointScale;       // +0x78
    float mEndJointScale;        // +0x7c
    uint32_t mSoundId;           // +0x80
    uint32_t mGroupId;           // +0x84
    uint32_t mInstanceId;        // +0x88
};

struct cRuntimeBlockTransform {  // 0x38
    int mBlockIndex;
    uint32_t mModelID;
    Vector3 mTranslation;
    Matrix3 mRotation;
};

class cRuntimeCreatureResource {
public:
    virtual int AddRef();
    virtual int Release();
    cRuntimeCreatureResource();                          // 0x004B9DA0

    uint32_t pad04[5];
    uint32_t mModel[0x20];                               // +0x18 (cSerializedEditorModel, 0x80)
    vector<cRuntimeCreatureBlock> mBlocks;               // +0x98
    vector<uint32_t> mCapCodes;                          // +0xac
    vector<uint8_t> mCapValues;                          // +0xc0
    vector<uint32_t> mDeformIDs;                         // +0xd4
    vector<float> mDeformValues;                         // +0xe8
    vector<float> mDeformWeights;                        // +0xfc
    uint32_t mFlags;                                     // +0x110
    vector<cRuntimeBlockTransform> mTransforms;          // +0x114
};

void SortSkeletonNodes(const SkelNode* nodes, int count, IndexVector* pOrder, void*, void*, void*, int* pNumRoots); // 0x00461680
bool IsSkeletonSymmetric(EditorRigblock** blocks, int count);                                                       // 0x0046D6C0

struct NodeEntry { uint32_t data[13]; };          // 0x34: pair<cSPVector3, fixed_vector<uint32_t,4>>
struct BonePair { int first; float second; };
struct BoneTransform { uint32_t data[0xe]; };
struct VertexWeights { uint32_t data[5]; };

class cSkinObject {
public:
    uint32_t pad00[2];
    AutoRefCount<cRuntimeCreatureResource> mResource;     // +0x08
    vector<AutoRefCount<cPropertyList> > mBlockProps;     // +0x0c
    vector<uint8_t> mNodeBlockMap;                        // +0x20
    uint32_t pad34[3];
    vector<NodeEntry> mNodes;                             // +0x40
    vector<BonePair> mBones;                              // +0x54
    vector<BoneTransform> mBoneTransforms;                // +0x68
    vector<VertexWeights> mVertexWeights;                 // +0x7c
    vector<RectF> mTextureSubRects;                       // +0x90

    bool UpdateBlocks(EditorRigblock** blocks, int count, vector<EditorRigblock*>* pOrderedBlocks);
};

// @ 0x004c73f0
bool cSkinObject::UpdateBlocks(EditorRigblock** blocks, int count, vector<EditorRigblock*>* pOrderedBlocks)
{
    IBlockDataProvider* pProvider = GetBlockDataProvider();
    cSkinObject* const pThis = this;
    IndexVector order;
    int numRoots = count;

    if (!pThis->mResource.get())
        pThis->mResource = new("Editor", 0, 0, 0, 0) cRuntimeCreatureResource();

    cRuntimeCreatureResource* pRes = pThis->mResource.get();

    for (int i = 0; i < count; i++) {
        EditorRigblock* pSym = blocks[i]->GetSymmetric();
        if (pSym)
            pSym->mIndex = 0xffffffff;
    }
    for (int i = 0; i < count; i++)
        blocks[i]->mIndex = i;

    {
        fixed_vector<SkelNode, 64> nodes(count);
        for (int i = 0; i < count; i++) {
            SkelNode& node = nodes[i];
            EditorRigblock* pBlock = blocks[i];
            EditorRigblock* pParent = pBlock->GetParent();
            if (pParent && pParent->mIndex < (uint32_t)count && blocks[pParent->mIndex] == pParent)
                node.mParent = (short)pParent->mIndex;
            else
                node.mParent = -1;

            if (pBlock->mBooleanAttributes.test(7))
                node.mType = 5;
            else if (pBlock->mBooleanAttributes.test(8))
                node.mType = 4;
            else if (pBlock->mBooleanAttributes.test(11))
                node.mType = 3;
            else if (pBlock->mBooleanAttributes.test(20))
                node.mType = 0;
            else
                node.mType = 2;

            int bakeLevel = pBlock->mModelBakeLevel;
            if (node.mType == 2 && bakeLevel >= 2 && node.mParent != -1)
                node.mType = 1;
        }

        // A type-1 node with a type-2 child turns its whole type-1 ancestor chain into type 2.
        for (int i = 0; i < count; i++) {
            if (nodes[i].mType == 1) {
                for (int j = 0; j < count; j++) {
                    if (nodes[j].mParent == i && nodes[j].mType == 2) {
                        for (int k = i; k != -1 && nodes[k].mType == 1; k = nodes[k].mParent)
                            nodes[k].mType = 2;
                        break;
                    }
                }
            }
        }

        SortSkeletonNodes(nodes.mpBegin, count, &order, 0, 0, 0, &numRoots);
    }

    memset(&pRes->mModel, 0, sizeof(pRes->mModel));
    pRes->mBlocks.clear();
    pRes->mCapCodes.clear();
    pRes->mCapValues.clear();
    pRes->mDeformIDs.clear();
    pRes->mDeformValues.clear();
    pRes->mDeformWeights.clear();
    pRes->mTransforms.clear();

    int numBlocks = order.size();
    pThis->mBlockProps.resize(numBlocks);                        // 0x00421BF0
    for (int i = 0; i < numBlocks; i++) {
        int& index = order[i];
        pThis->mBlockProps[i] = blocks[index]->mpPropList.get();
    }
    pRes->mBlocks.resize(numBlocks);                             // 0x004C0350
    cRuntimeCreatureBlock* pRuntimeBlocks = pRes->mBlocks.mpBegin;

    {
        fixed_vector<float, 256> deformValues;
        fixed_vector<float, 256> deformWeights;
        fixed_vector<uint32_t, 256> deformIDs;
        fixed_vector<uint32_t, 256> capCodes;
        fixed_vector<uint8_t, 256> capValues;
        SoundMap soundMap;

        for (int i = 0; i < numBlocks; i++)
            blocks[order[i]]->mIndex = i;

        for (int i = 0; i < numBlocks; i++) {
            EditorRigblock* pBlock = blocks[order[i]];
            cRuntimeCreatureBlock* pRB = &pRuntimeBlocks[i];
            cPropertyList* pProps = pThis->mBlockProps[i].get();

            memset(pRB, 0, sizeof(cRuntimeCreatureBlock));
            pRB->mBlockIndex = (short)i;
            pRB->mNodeIndex = -1;
            pRB->mSubmeshId = 0;
            pRB->mGroupId = pBlock->GetGroupID();
            pRB->mInstanceId = pBlock->GetInstanceID();

            EditorRigblock* pParent = pBlock->GetParent();
            if (pParent)
                pRB->mParentIndex = (short)pParent->mIndex;
            else
                pRB->mParentIndex = -1;

            EditorRigblock* pSym = 0;
            bool bSymmetric = false;
            if (pBlock->mBooleanAttributes.test(57)) {
                pSym = pBlock->GetAsymmetric();
                bSymmetric = (pSym && pSym->GetAsymmetric() == pBlock) ? 1 : 0;
            } else {
                pSym = pBlock->GetSymmetric();
                bSymmetric = (pSym && pSym->GetSymmetric() == pBlock) ? 1 : 0;
            }
            if (pSym && bSymmetric && pSym->mIndex < (uint32_t)numBlocks && blocks[order[pSym->mIndex]] == pSym)
                pRB->mSymmetricIndex = (short)pSym->mIndex;
            else
                pRB->mSymmetricIndex = -1;

            if (pBlock->mBooleanAttributes.test(7))
                pRB->mBlockType = 5;
            else if (pBlock->mBooleanAttributes.test(8))
                pRB->mBlockType = 4;
            else if (pBlock->mBooleanAttributes.test(11))
                pRB->mBlockType = 3;
            else if (pBlock->mBooleanAttributes.test(20))
                pRB->mBlockType = 0;
            else if (pRB->mBlockIndex < numRoots)
                pRB->mBlockType = 2;
            else
                pRB->mBlockType = 1;

            int bakeLevel = pBlock->mModelBakeLevel;
            if (bakeLevel == 0) {
                ResourceKey bakeKey(0, 0, 0);
                if (!pProvider->GetBakeKey(pBlock->GetInstanceID(), pBlock->GetGroupID(), &bakeKey))
                    bakeLevel = 1;
            }
            if (bakeLevel > 0)
                pRB->mFlags |= 8;
            if (pBlock->mBooleanAttributes.test(10))
                pRB->mFlags |= 1;
            if (pBlock->mBooleanAttributes.test(31))
                pRB->mFlags |= 4;
            int limbType = pBlock->mLimbType;
            if (limbType == 1)
                pRB->mFlags |= 0x10;

            bool bValue = true;
            GetBoolProperty(pProps, 0xb6f17b6c, &bValue);
            if (!bValue)
                pRB->mFlags |= 0x200;
            bool bValue2 = false;
            GetBoolProperty(pProps, 0xa64e0669, &bValue2);
            if (bValue2)
                pRB->mFlags |= 0x800;
            if (pBlock->mBooleanAttributes.test(57))
                pRB->mFlags |= 0x1000;

            // Capabilities
            pRB->mCapOffset = (uint16_t)capCodes.size();
            pRB->mNumCaps = 0;
            for (int j = 0, numCaps = pBlock->mCapabilities.size(); j < numCaps; j++) {
                if (pRB->mNumCaps == 32)
                    return false;
                uint32_t propID = pBlock->mCapabilities.mpBegin[j].mPropertyID;
                uint32_t code = GetCapabilityCode(propID);
                capCodes.push_back(code);
                const CapabilityLevel* pLevel = &pBlock->mCapabilities.mpBegin[j].mLevel;
                if (!pLevel->mIsVariableLevel) {
                    uint8_t value = (uint8_t)pLevel->mLevel;
                    capValues.push_back(value);
                } else {
                    float t = pBlock->GetHandleValue(pLevel->mHandleIndex);
                    float f = (float)pLevel->mMinLevel + (float)(pLevel->mLevel - pLevel->mMinLevel) * t;
                    f += 0.5f;
                    uint8_t value = (uint8_t)(int)f;
                    capValues.push_back(value);
                }
                pRB->mNumCaps++;
            }

            // Deforms: handles of the block, then deform lists named by its property file.
            int numHandles = pBlock->mBooleanAttributes.test(10) ? 0 : pBlock->GetHandleCount();
            pRB->mDeformOffset = (uint16_t)deformValues.size();
            ResourceKey key(0, 0, 0);
            key.instance = pBlock->GetInstanceID();
            key.group = pBlock->GetGroupID();
            for (int h = 0; h < numHandles; h++) {
                uint32_t id = pBlock->GetHandleID(h);
                deformIDs.push_back(id);
                float value = pBlock->GetHandleValue(h);
                deformValues.push_back(value);
                float weight = 1.0f;
                deformWeights.push_back(weight);
            }

            AutoRefCount<cPropertyList> pFileProps;
            if (SP::PropertyManager()->GetPropertyList(key.instance, key.group, pFileProps.AsPointer())) {
                const int kNumDeformLists = 0x5f;
                for (int n = 0; n < kNumDeformLists; n++) {
                    if (pFileProps->HasProperty(kDeformPropertyLists[n])) {
                        AutoRefCount<cPropertyList> pDeformList;
                        if (SP::PropertyManager()->GetPropertyList(kDeformPropertyLists[n], 0x47bf35f, pDeformList.AsPointer())) {
                            Property* pIDs = pDeformList->GetProperty(0x47be908);
                            int numIDs = pIDs->GetItemCount();
                            ResourceKey* ids = pIDs->GetValues<ResourceKey>();
                            Property* pValues = pDeformList->GetProperty(0x47be96f);
                            int numValues = pValues->GetItemCount();
                            float* values = pValues->GetValues<float>();
                            Property* pWeights = pDeformList->GetProperty(0x684d16c);
                            int numWeights = pWeights->GetItemCount();
                            float* weights = pWeights->GetValues<float>();
                            (void)numValues; (void)numWeights;
                            for (int j = 0; j < numIDs; j++) {
                                deformIDs.push_back(ids[j].instance);
                                deformValues.push_back(values[j]);
                                deformWeights.push_back(weights[j]);
                            }
                        }
                    }
                }
            }
            pRB->mNumDeforms = (uint8_t)(deformValues.size() - pRB->mDeformOffset);

            // Transform
            pRB->mScale = pBlock->GetSize();
            pRB->mRotation = pBlock->mTotalOrientation;
            pRB->mTranslation = pBlock->mPosition;
            pRB->mBoneLength = VectorLength(pBlock->GetBoneVector()) / pBlock->GetSize();
            pRB->mMuscleScale = pBlock->GetMuscleScale();
            pRB->mBaseJointScale = pBlock->GetBaseJointScale();
            pRB->mEndJointScale = pBlock->GetEndJointScale();

            // Bounds
            if (pRB->mBlockType == 5 && (pRB->mFlags & 1)) {
                pRB->mBoundsMin.Set(-0.19f, -0.07f, -0.35f);
                pRB->mBoundsMax.Set(0.19f, 0.07f, 0.03f);
            } else if (pRB->mBlockType == 3) {
                float r = (pRB->mBaseJointScale + pRB->mEndJointScale) * 0.5f * 0.06f;
                pRB->mBoundsMin.Set(-r, -pRB->mBoneLength, -r);
                pRB->mBoundsMax.Set(r, 0.0f, r);
            } else {
                IBlockDataProvider* pBounds = GetBlockDataProvider();
                float* pDeforms = deformValues.mpBegin;
                if (!pBounds->GetBounds(pRB->mInstanceId, pRB->mGroupId, &pDeforms[pRB->mDeformOffset], numHandles,
                                        &pRB->mBoundsMin, &pRB->mBoundsMax)) {
                    pRB->mBoundsMin.Set(-0.1f, -0.1f, -0.1f);
                    pRB->mBoundsMax.Set(0.1f, 0.1f, 0.1f);
                }
            }

            // Offset
            pRB->mOffset = Vector3(0.0f, 0.0f, 0.0f);
            if (SP::GetPropertyAsVector3(pProps, 0x68de7a9, &pRB->mOffset)) {
                float offsetScale;
                if (GetFloatProperty(pProps, 0xfba611, &offsetScale))
                    pRB->mOffset *= offsetScale;
                __declspec(align(16)) Vector3 eulerDegrees;   // some 16-aligned local gives the original its `and esp,-16` frame; which one is not recovered
                if (SP::GetPropertyAsVector3(pProps, 0xfba613, &eulerDegrees)) {
                    float degToRad = gPI / 180.0f;
                    Vector3 euler = eulerDegrees * degToRad;
                    RwMatrix33 rot(rw::math::fpu::Matrix33FromEulerXYZ(euler));
                    Vector3& offset = pRB->mOffset;
                    offset = offset * rot;
                }
                Vector3 translate;
                if (SP::GetPropertyAsVector3(pProps, 0xfba610, &translate))
                    pRB->mOffset += translate;
            }
            float tY;
            if (GetFloatProperty(pProps, 0x68de7aa, &tY))
                pRB->mOffset[1] = Lerp(pRB->mBoundsMax[1], pRB->mBoundsMin[1], tY);
            float tZ;
            if (GetFloatProperty(pProps, 0x68de7ab, &tZ))
                pRB->mOffset[2] = Lerp(pRB->mBoundsMax[2], pRB->mBoundsMin[2], tZ);

            // Attached models
            const uint32_t kModelKeys = 0x32f4549;
            const uint32_t kModelTransforms = 0x2a907b6;
            int numModels;
            ResourceKey* modelKeys;
            if (SP::GetPropertyAsKeyArray(pProps, kModelKeys, &numModels, &modelKeys)) {
                int numTransforms = 0;
                Transform* transforms = 0;
                SP::GetPropertyAsTransformArray(pProps, kModelTransforms, &numTransforms, &transforms);
                Transform identity;
                for (int m = 0; m < numModels; m++) {
                    const Transform* pTransform = (m < numTransforms) ? &transforms[m] : &identity;
                    const Transform& t = *pTransform;
                    pRes->mTransforms.push_back();
                    cRuntimeBlockTransform& out = pRes->mTransforms.back();
                    const ResourceKey& modelKey = modelKeys[m];
                    out.mBlockIndex = pRB->mBlockIndex;
                    out.mModelID = modelKey.instance;
                    out.mTranslation = t.mTranslation;
                    out.mRotation = t.mRotation;
                }
            }

            float minScale = pBlock->mModelMinScale;
            float maxScale = pBlock->mModelMaxScale;
            float scaleRange = maxScale - minScale;
            float size = pBlock->GetSize();
            float scaleFactor = Clamp01((size - minScale) / scaleRange);
            pRB->mScaleFactor = scaleFactor;

            // Sound
            pRB->mSoundId = pBlock->GetModelUInt32(0xdd94fb65);
            if (pRB->mSoundId)
                pRB->mFlags |= 0x20;
            else {
                pRB->mSoundId = pBlock->GetModelUInt32(0x2dc2a89d);
                if (pRB->mSoundId)
                    pRB->mFlags |= 0x80;
                else {
                    uint32_t soundKey = pBlock->GetModelUInt32(0xe40c402);
                    if (soundKey) {
                        float weight = 0.0f;
                        GetFloatProperty(pProps, 0x6440a76, &weight);
                        weight *= pBlock->GetSize();
                        MappedPair& best = soundMap[soundKey];
                        if (weight > best.mWeight) {
                            best.mIndex = pRB->mBlockIndex;
                            best.mWeight = weight;
                        }
                    }
                }
            }

            uint32_t ownerInstance = 0;
            if (SP::GetPropertyAsKeyInstance(pProps, 0xf48eb09, &ownerInstance) && ownerInstance == pBlock->GetInstanceID())
                pRB->mFlags |= 0x100;
        }

        // One block per looping sound gets the sound; the loudest overall is flagged 0x400.
        MappedPair* pLoudest = 0;
        for (hashtable_iterator it = soundMap.begin(), itEnd = soundMap.end(); it != itEnd; ++it) {
            HashNode& kv = *it;
            MappedPair& v = kv.mValue;
            cRuntimeCreatureBlock& rb = pRuntimeBlocks[v.mIndex];
            rb.mSoundId = kv.mKey;
            rb.mFlags |= 0x40;
            if (!pLoudest || v.mWeight > pLoudest->mWeight)
                pLoudest = &v;
        }
        if (pLoudest)
            pRuntimeBlocks[pLoudest->mIndex].mFlags |= 0x400;

        pRes->mCapCodes.assign(capCodes.mpBegin, capCodes.mpEnd);
        pRes->mCapValues.assign(capValues.mpBegin, capValues.mpEnd);
        pRes->mDeformIDs.assign(deformIDs.mpBegin, deformIDs.mpEnd);
        pRes->mDeformValues.assign(deformValues.mpBegin, deformValues.mpEnd);
        pRes->mDeformWeights.assign(deformWeights.mpBegin, deformWeights.mpEnd);

        pRes->mFlags = 0;
        if (IsSkeletonSymmetric(blocks, numBlocks))
            pRes->mFlags |= 1;
    }

    // Nodes and submeshes
    int numNodes = 0;
    int submesh = 1;
    for (int i = 0; i < numBlocks; i++) {
        cRuntimeCreatureBlock* pRB = &pRuntimeBlocks[i];
        if (pRB->mParentIndex == -1 ||
            (pRB->mBlockType == 3 && pRuntimeBlocks[pRB->mParentIndex].mBlockType != 3)) {
            pRB->mFlags |= 2;
            numNodes++;
        }
        pRB->mNodeIndex = (short)numNodes;
        numNodes++;
        if (!(pRB->mFlags & 1)) {
            pRB->mSubmeshId = (uint8_t)submesh;
            submesh++;
        }
    }

    pThis->mNodeBlockMap.resize(numNodes);                       // 0x004C0410
    int node = 0;
    for (int i = 0; i < numBlocks; i++) {
        if (pRuntimeBlocks[i].mFlags & 2)
            pThis->mNodeBlockMap[node++] = (uint8_t)i;
        pThis->mNodeBlockMap[node++] = (uint8_t)i;
    }

    pThis->mTextureSubRects.clear();
    pThis->mTextureSubRects.resize(numBlocks, RectF(0.0f, 0.0f, 1.0f, 1.0f));
    pThis->mNodes.clear();
    pThis->mBones.clear();
    pThis->mBoneTransforms.clear();
    pThis->mVertexWeights.clear();

    if (pOrderedBlocks) {
        pOrderedBlocks->resize(numBlocks);                        // 0x004CD3C0
        EditorRigblock** pOut = pOrderedBlocks->mpBegin;
        for (int i = 0; i < numBlocks; i++)
            pOut[i] = blocks[order[i]];
    }

    return numBlocks > 0;
}

#pragma pack(pop)
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct E {
    void erase();   // 0x00514750 (equiv t2)
    void resize();   // 0x004c0410 (equiv t2)
};
struct I {
    void erase();   // 0x004769b0 (equiv t2)
};
struct M {
    void erase();   // 0x004769b0 (equiv t2)
};
struct PAUEditorRigblock {
    void resize();   // 0x004cd3c0 (equiv t3)
};
struct UBonePair {
    void erase();   // 0x00530c80 (equiv t2)
};
struct UBoneTransform {
    void erase();   // 0x004238c0 (equiv t3)
};
struct UNodeEntry {
    void erase();   // 0x004ce110 (equiv t3)
};
struct URectF {
    void erase();   // 0x004ce200 (equiv t3)
    void resize();   // 0x004cd710 (equiv t3)
};
struct UVertexWeights {
    void erase();   // 0x00455ae0 (equiv t2)
};
struct UcRuntimeBlockTransform {
    void erase();   // 0x004c0730 (equiv t3)
};
struct UcRuntimeCreatureBlock {
    void erase();   // 0x004c0680 (equiv t3)
    void resize();   // 0x004c0350 (equiv t3)
};
struct VcPropertyList {
    void resize();   // 0x00421bf0 (equiv t2)
};
struct fixed_vector {
    void push_back();   // 0x004cd810 (equiv t3)
};
}
