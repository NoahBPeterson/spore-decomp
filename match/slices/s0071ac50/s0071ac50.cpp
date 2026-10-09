// Slice s0071ac50: SP::cMeshBuilder::CreateMeshData (dev-PDB name; retail is a
// __thiscall void member with no args).  Allocates a fresh SP::cMeshData (0x58),
// stores it in mMeshData (+0x148), then converts the builder's source arrays into
// cMDElementArrays, the builder sections into cMDSections (index arrays + format
// entries) and copies the primitives, finally post-processes the mesh data and
// calls ClearMeshInfo.
// Module flags (same as the s00719e10 cMeshBuilder methods):
//   /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
//
// Retail layouts (verified against the asm; the 2008 PDB differs):
//   sp_vector = 3 pointers + 8-byte allocator = 0x14 bytes
//   cMeshData 0x58: vtbl, refcount, mEltArrays +8, mSections +0x1c,
//                   mPrimitives +0x30, mAttachments +0x44
//   cMDSection 0x8c: mVertIndices +0, mNumVertices +0x10,
//                   fixed_vector<cMDFormatEntry,6> +0x14, fixed_vector<cIndexArrayRef,3> +0x44
//   cMeshBuilder::cSection 0xd0, cBoneWeights 0x28, cMorphTarget 0x50
#include "types.h"
#include <intrin.h>

typedef unsigned int size_t;

void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);             // 0x00f473a0
void operator delete[](void* p);                           // 0x00f47380
inline void* operator new(size_t, void* p) { return p; }

// ---------------------------------------------------------------------------
// Ref counting
// ---------------------------------------------------------------------------
namespace EA { namespace COM {
struct IRefCount {
    virtual int AddRef() = 0;   // slot 0
    virtual int Release() = 0;  // slot 1
};
} }

// EA::RefCountTemplate<EA::Thread::AtomicInt<int>> (vtable 0x013ef094)
struct RefCountTemplate {
    virtual ~RefCountTemplate();   // slot 0: scalar deleting dtor
    long mnRefCount;               // +0x4
    RefCountTemplate() { _InterlockedExchange(&mnRefCount, 0); }
    int AddRef() { return _InterlockedExchangeAdd(&mnRefCount, 1) + 1; }
    int Release()
    {
        int n = _InterlockedExchangeAdd(&mnRefCount, -1) - 1;
        if (n == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            delete this;
        }
        return n;
    }
};

// ---------------------------------------------------------------------------
// Containers (retail layouts)
// ---------------------------------------------------------------------------
template <typename T>
struct sp_vector {
    T* mpBegin;          // +0x0
    T* mpEnd;            // +0x4
    T* mpCapacity;       // +0x8
    uint32_t mAlloc[2];  // +0xc  sp_vector_allocator
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);  // out of line
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            ::new (p) T(value);
        } else
            DoInsertValue(mpEnd, value);
    }
};

// eastl::fixed_vector<T,N,true>: header 0x18 (begin/end/capacity, overflow
// allocator, pool pointer, one more dword), then the inline buffer.
template <typename T, int N>
struct fixed_vector_base {
    T* mpBegin;            // +0x00
    T* mpEnd;              // +0x04
    T* mpCapacity;         // +0x08
    uint32_t mOverflow;    // +0x0c
    void* mpPoolBegin;     // +0x10
    uint32_t mUnused;      // +0x14
    uint32_t mBuffer[(sizeof(T) * N) / 4];  // +0x18
    fixed_vector_base()
    {
        mpBegin = mpEnd = (T*)mBuffer;
        mpPoolBegin = mBuffer;
        mpCapacity = (T*)mBuffer + N;
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    void DoInsertValue(T* position, const T& value);  // out of line
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            ::new (p) T(value);
        } else
            DoInsertValue(mpEnd, value);
    }
};

// eastl::bitset<11>
struct bitset11 {
    uint32_t mWord;
    bool test(uint32_t i) const
    {
        if (i < 11)
            return (mWord & (1u << (i & 31))) != 0;
        return false;
    }
};

// ---------------------------------------------------------------------------
// Mesh data types
// ---------------------------------------------------------------------------
struct cSPVector2 { float x, y; };
struct cSPVector3 { float x, y, z; };
struct tMDUByte4 { unsigned char c[4]; };
struct cMDBoneTransform { float m[12]; };            // 0x30

// SP::cEltArrayRef / SP::cIndexArrayRef (0x10)
struct cEltArrayRef {
    int mNumElts;                     // +0x0
    unsigned char* mData;             // +0x4
    unsigned short mEltSize;          // +0x8
    unsigned short mEltStride;        // +0xa
    EA::COM::IRefCount* mDataRC;      // +0xc  AutoRefCount<IRefCount>

    cEltArrayRef() : mNumElts(0), mData(0), mEltSize(0), mEltStride(0), mDataRC(0) {}
    cEltArrayRef(int n, const void* data, unsigned short size, unsigned short stride)
        : mNumElts(n), mData((unsigned char*)data), mEltSize(size), mEltStride(stride), mDataRC(0) {}
    template <typename T>
    explicit cEltArrayRef(const sp_vector<T>& v)
        : mNumElts(v.size()), mData((unsigned char*)v.mpBegin),
          mEltSize(sizeof(T)), mEltStride(sizeof(T)), mDataRC(0) {}
    __forceinline cEltArrayRef(const cEltArrayRef& o)
        : mNumElts(o.mNumElts), mData(o.mData), mEltSize(o.mEltSize),
          mEltStride(o.mEltStride), mDataRC(o.mDataRC)
    {
        if (mDataRC)
            mDataRC->AddRef();
    }
    ~cEltArrayRef()
    {
        if (mDataRC)
            mDataRC->Release();
    }
    cEltArrayRef& operator=(const cEltArrayRef& o)
    {
        mNumElts = o.mNumElts;
        mData = o.mData;
        mEltSize = o.mEltSize;
        mEltStride = o.mEltStride;
        EA::COM::IRefCount* old = mDataRC;
        if (o.mDataRC != old) {
            if (o.mDataRC)
                o.mDataRC->AddRef();
            mDataRC = o.mDataRC;
            if (old)
                old->Release();
        }
        return *this;
    }
};
typedef cEltArrayRef cIndexArrayRef;

enum tMDSemantic {
    kSemPosition = 1, kSemNormal = 2, kSemTangent = 3, kSemBinormal = 4,
    kSemColor = 5, kSemTexCoord = 8, kSemBoneIndices = 9, kSemBoneWeights = 10,
    kSemMorphPosition = 0xc, kSemMorphNormal = 0xd, kSemBonePose = 0x12,
    kSemSubsetID = 0x14, kSemSubsetMaterial = 0x15
};

// SP::cMDElementArray (0x20)
struct cMDElementArray {
    int mSemantic;       // +0x0  tMDSemantic
    int mNumber;         // +0x4
    int mType;           // +0x8  tMDDataType
    int mClass;          // +0xc  tMDElementClass
    cEltArrayRef mArray; // +0x10
    cMDElementArray(int sem, int number, int type, int cls, const cEltArrayRef& a)
        : mSemantic(sem), mNumber(number), mType(type), mClass(cls), mArray(a) {}
    __forceinline cMDElementArray(const cMDElementArray& o)
        : mSemantic(o.mSemantic), mNumber(o.mNumber), mType(o.mType), mClass(o.mClass),
          mArray(o.mArray) {}
};

// SP::cMDFormatEntry (4)
struct cMDFormatEntry {
    short mElts;
    short mIndices;
    cMDFormatEntry(short elts, short indices) : mElts(elts), mIndices(indices) {}
};

// fixed_vector<cIndexArrayRef,3>: destructor is out of line (0x0041f9b0).
struct IndexArrayFixedVector : fixed_vector_base<cIndexArrayRef, 3> {
    ~IndexArrayFixedVector();
};
// fixed_vector<cMDFormatEntry,6>: trivially destructible elements.
struct FormatFixedVector : fixed_vector_base<cMDFormatEntry, 6> {
    ~FormatFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
};

// SP::cMDSection (retail 0x8c)
struct cMDSection {
    cIndexArrayRef mVertIndices;          // +0x00
    int mNumVertices;                     // +0x10
    FormatFixedVector mFormat;            // +0x14
    IndexArrayFixedVector mEltIndices;    // +0x44
    cMDSection() : mNumVertices(0) {}
    cMDSection(const cMDSection& o);      // out of line (0x0042cba0)
};

// SP::cMDPrimitive (0x14)
struct cMDPrimitive { int mPrimType, mSection, mStart, mEnd, mSubset; };

// SP::cMeshData (retail 0x58, vtable 0x013eb8d0)
struct cMeshData : RefCountTemplate {
    sp_vector<cMDElementArray> mEltArrays;   // +0x08
    sp_vector<cMDSection> mSections;         // +0x1c
    sp_vector<cMDPrimitive> mPrimitives;     // +0x30
    sp_vector<void*> mAttachments;           // +0x44
    cMeshData() {}
    virtual ~cMeshData();
};

// EA::AutoRefCount<cMeshData>
struct MeshDataPtr {
    cMeshData* mp;
    __forceinline MeshDataPtr& operator=(cMeshData* p)
    {
        if (p != mp) {
            cMeshData* old = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    cMeshData* operator->() const { return mp; }
};

void MeshData_ResolveArrays(cMeshData* md);   // 0x007320f0 (walks every elt/index array ref)

// ---------------------------------------------------------------------------
// SP::cMeshBuilder (retail layout, only what is used here)
// ---------------------------------------------------------------------------
struct cSubset { unsigned int mID; unsigned int mMaterialID; };

// SP::cMeshBuilder::cSection (retail 0xd0)
struct cBuilderSection {
    bitset11 mVertexFormat;               // +0x00
    int mNumVertices;                     // +0x04
    sp_vector<int> mPositionIndices;      // +0x08
    sp_vector<int> mNormalIndices;        // +0x1c
    uint32_t pad_30[0x78 / 4];            // +0x30
    sp_vector<int> mAttribIndices;        // +0xa8  (tex coord / colour index stream)
    sp_vector<int> mVertIndices;          // +0xbc
};

// SP::cMeshBuilder::cBoneWeights (retail 0x28)
struct cBoneWeights {
    sp_vector<int> mIndices;              // +0x00
    sp_vector<float> mWeights;            // +0x14
};

// SP::cMeshBuilder::cMorphTarget (retail 0x50)
struct cMorphTarget {
    sp_vector<int> mPositionIndices;          // +0x00
    sp_vector<cSPVector3> mPositionDeltas;    // +0x14
    sp_vector<int> mNormalIndices;            // +0x28
    sp_vector<cSPVector3> mNormalDeltas;      // +0x3c
};

class cMeshBuilder {
public:
    void CreateMeshData();
    void ClearMeshInfo();                              // 0x0071a650

    void* mpVtbl;                                      // +0x000
    int mRefCount;                                     // +0x004
    sp_vector<cSPVector3> mPositions;                  // +0x008
    sp_vector<cSPVector3> mNormals;                    // +0x01c
    sp_vector<cSPVector2> mTexCoords[4];               // +0x030
    sp_vector<tMDUByte4> mColors[2];                   // +0x080
    sp_vector<cSPVector3> mTangents;                   // +0x0a8
    sp_vector<cSPVector3> mBinormals;                  // +0x0bc
    sp_vector<cBuilderSection> mSections;              // +0x0d0
    sp_vector<cMDPrimitive> mPrimitives;               // +0x0e4
    sp_vector<cSubset> mSubsets;                       // +0x0f8
    sp_vector<cMDBoneTransform> mBonePoses;            // +0x10c
    sp_vector<cBoneWeights> mBoneWeightsArray;         // +0x120
    sp_vector<cMorphTarget> mMorphTargetArray;         // +0x134
    MeshDataPtr mMeshData;                             // +0x148
};

enum { kDataFloat2 = 2, kDataFloat3 = 3, kDataUByte4 = 5, kDataInt = 6,
       kDataMatrix = 0xe, kDataFloat1x = 0x81, kDataFloat3x = 0x83 };

// @ 0x0071ac50
void cMeshBuilder::CreateMeshData()
{
    mMeshData = new ("Graphics", 0, 0, 0, 0) cMeshData;

    // Vertex attribute streams.
    mMeshData->mEltArrays.push_back(
        cMDElementArray(kSemPosition, 0, kDataFloat3, 0, cEltArrayRef(mPositions)));
    mMeshData->mEltArrays.push_back(
        cMDElementArray(kSemNormal, 0, kDataFloat3, 1, cEltArrayRef(mNormals)));

    int tangentElt = mMeshData->mEltArrays.size();
    if (!mTangents.empty())
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemTangent, 0, kDataFloat3, 1, cEltArrayRef(mTangents)));

    int binormalElt = mMeshData->mEltArrays.size();
    if (!mBinormals.empty())
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemBinormal, 0, kDataFloat3, 1, cEltArrayRef(mBinormals)));

    int texCoordElt = mMeshData->mEltArrays.size();
    for (int i = 0; i < 4; ++i) {
        if (!mTexCoords[i].empty())
            mMeshData->mEltArrays.push_back(
                cMDElementArray(kSemTexCoord, i, kDataFloat2, 2, cEltArrayRef(mTexCoords[i])));
    }

    int colorElt = mMeshData->mEltArrays.size();
    for (int i = 0; i < 2; ++i) {
        if (!mColors[i].empty())
            mMeshData->mEltArrays.push_back(
                cMDElementArray(kSemColor, i, kDataUByte4, 2, cEltArrayRef(mColors[i])));
    }

    // Bone weights: two streams (weights, indices) per bone.
    int boneElt = mMeshData->mEltArrays.size();
    int numBones = mBoneWeightsArray.size();
    for (int i = 0; i < numBones; ++i) {
        cBoneWeights& bw = mBoneWeightsArray[i];
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemBoneWeights, i, kDataFloat1x, 0, cEltArrayRef(bw.mWeights)));
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemBoneIndices, i, kDataInt, 0, cEltArrayRef(bw.mIndices)));
    }

    // Morph targets: position deltas + indices for every target...
    int morphPosElt = mMeshData->mEltArrays.size();
    int numMorphs = mMorphTargetArray.size();
    for (int i = 0; i < numMorphs; ++i) {
        cMorphTarget& mt = mMorphTargetArray[i];
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemMorphPosition, i, kDataFloat3x, 0, cEltArrayRef(mt.mPositionDeltas)));
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemMorphPosition, i, kDataInt, 0, cEltArrayRef(mt.mPositionIndices)));
    }

    // ...then normal deltas + indices for targets that have them.
    int morphNrmElt = mMeshData->mEltArrays.size();
    numMorphs = mMorphTargetArray.size();
    for (int i = 0; i < numMorphs; ++i) {
        cMorphTarget& mt = mMorphTargetArray[i];
        if (!mt.mNormalDeltas.empty()) {
            mMeshData->mEltArrays.push_back(
                cMDElementArray(kSemMorphNormal, i, kDataFloat3x, 0, cEltArrayRef(mt.mNormalDeltas)));
            mMeshData->mEltArrays.push_back(
                cMDElementArray(kSemMorphNormal, i, kDataInt, 0, cEltArrayRef(mt.mNormalIndices)));
        }
    }

    if (!mBonePoses.empty())
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemBonePose, 0, kDataMatrix, 5, cEltArrayRef(mBonePoses)));

    if (!mSubsets.empty()) {
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemSubsetID, 0, kDataInt, 8,
                            cEltArrayRef(mSubsets.size(), &mSubsets.mpBegin->mID, 4, 8)));
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemSubsetMaterial, 0, kDataInt, 8,
                            cEltArrayRef(mSubsets.size(), &mSubsets.mpBegin->mMaterialID, 4, 8)));
    }

    // Sections.
    int numSections = mSections.size();
    for (int s = 0; s < numSections; ++s) {
        cBuilderSection& src = mSections[s];
        cMDSection section;
        section.mVertIndices = cIndexArrayRef(src.mVertIndices);
        section.mNumVertices = src.mNumVertices;

        int positionIndex = -1;
        int normalIndex = -1;
        int attribIndex = -1;
        if (!src.mPositionIndices.empty()) {
            positionIndex = section.mEltIndices.size();
            section.mEltIndices.push_back(cIndexArrayRef(src.mPositionIndices));
        }
        if (!src.mNormalIndices.empty()) {
            normalIndex = section.mEltIndices.size();
            section.mEltIndices.push_back(cIndexArrayRef(src.mNormalIndices));
        }
        if (!src.mAttribIndices.empty()) {
            attribIndex = section.mEltIndices.size();
            section.mEltIndices.push_back(cIndexArrayRef(src.mAttribIndices));
        }

        bitset11 format = src.mVertexFormat;
        if (format.test(0) && positionIndex >= 0)
            section.mFormat.push_back(cMDFormatEntry(0, (short)positionIndex));
        if (format.test(1) && normalIndex >= 0) {
            section.mFormat.push_back(cMDFormatEntry(1, (short)normalIndex));
            if (!mTangents.empty())
                section.mFormat.push_back(cMDFormatEntry((short)tangentElt, (short)normalIndex));
            if (!mBinormals.empty())
                section.mFormat.push_back(cMDFormatEntry((short)binormalElt, (short)normalIndex));
        }
        if (attribIndex >= 0) {
            for (int i = 0; i < 4; ++i) {
                if (format.test(i + 2))
                    section.mFormat.push_back(cMDFormatEntry((short)(texCoordElt + i), (short)attribIndex));
            }
            for (int i = 0; i < 2; ++i) {
                if (format.test(i + 6))
                    section.mFormat.push_back(cMDFormatEntry((short)(colorElt + i), (short)attribIndex));
            }
        }
        if (format.test(8)) {
            int n = mBoneWeightsArray.size();
            for (int i = 0; i < n; ++i)
                section.mFormat.push_back(cMDFormatEntry((short)(boneElt + i * 2), -1));
        }
        if (positionIndex >= 0) {
            if (format.test(9)) {
                int n = mMorphTargetArray.size();
                for (int i = 0; i < n; ++i)
                    section.mFormat.push_back(cMDFormatEntry((short)(morphPosElt + i * 2), (short)positionIndex));
            }
            if (format.test(10)) {
                int n = mMorphTargetArray.size();
                for (int i = 0; i < n; ++i)
                    section.mFormat.push_back(cMDFormatEntry((short)(morphNrmElt + i * 2), (short)positionIndex));
            }
        }

        mMeshData->mSections.push_back(section);
    }

    // Primitives.
    int numPrims = mPrimitives.size();
    for (int i = 0; i < numPrims; ++i)
        mMeshData->mPrimitives.push_back(mPrimitives[i]);

    MeshData_ResolveArrays(mMeshData.mp);
    ClearMeshInfo();
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
