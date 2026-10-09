// Slice s00726c20 — SP::QuantizeVertices (5110 bytes, retail version).
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
//
// Identified from the 2008 dev build (work/devbuild: SPGraphicsMeshJoin.obj, SP::QuantizeVertices
// at dev-build address 00f487c0, 2559 bytes, signature (cMeshData*, float granularity, tQuantizeType)); the local
// names below are the dev PDB's. The retail function grew a fourth parameter (a per-class table of
// {scale, flags}) and classifies points by bone, normal octant and section before welding them.
// Retail layouts (from the disassembly): eastl::vector is 0x14 bytes, fixed_vector keeps its buffer
// at +0x18, cMDSection is 0x8c bytes.
#include <new>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0

struct cSPVector3 {
  float x, y, z;
  cSPVector3() {}
  cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// cvtss2si helper (current rounding mode), as in the other SP math modules.
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

namespace EA {
namespace COM {
class IRefCount {
 public:
  virtual int AddRef();
  virtual int Release();
};
}  // namespace COM

template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) {
    if (mpObject)
      mpObject->AddRef();
  }
  ~AutoRefCount() {
    if (mpObject)
      mpObject->Release();
  }
  AutoRefCount& operator=(T* pObject) {
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
  AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
};

namespace Thread {
typedef unsigned int ThreadTime;
void ThreadSleep(const ThreadTime& timeRelative);  // 0x00921df0
}  // namespace Thread
}  // namespace EA

namespace eastl {
struct sp_vector_allocator {
  uint32_t mName[2];
  sp_vector_allocator() {}
};

template <typename T>
class vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator mAllocator;
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  void DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};

// eastl::fixed_vector<T, N, true> (retail layout: buffer at +0x18)
template <typename T, int N>
class fixed_vector {
 public:
  T* mpBegin;          // +0x00
  T* mpEnd;            // +0x04
  T* mpCapacity;       // +0x08
  uint32_t mOverflow;  // +0x0c
  T* mpPoolBegin;      // +0x10
  uint32_t mPad;       // +0x14
  uint32_t mBuffer[N * sizeof(T) / 4];  // +0x18 (aligned_buffer)

  fixed_vector() {
    mpPoolBegin = (T*)mBuffer;
    mpBegin = mpEnd = (T*)mBuffer;
    mpCapacity = (T*)mBuffer + N;
  }
  explicit fixed_vector(int n);  // fixed_vector<int,256>: 0x00726900
  ~fixed_vector() {
    if (mpBegin && mpBegin != mpPoolBegin)
      operator delete[](mpBegin);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  void DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};

struct true_type {};

template <typename K, typename V>
struct pair {
  K first;
  V second;
  pair(const K& k, const V& v) : first(k), second(v) {}
};

// eastl::hash_map<cDecCellID, int, cDecCellHash>
template <typename K, typename V>
class hash_map {
 public:
  typedef pair<const K, V> value_type;
  struct node_type {
    value_type mValue;
    node_type* mpNext;
  };
  struct iterator {
    node_type* mpNode;
    node_type** mpBucket;
    iterator() {}
    iterator(node_type** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    iterator(const iterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
    bool operator!=(const iterator& x) const { return mpNode != x.mpNode; }
    value_type* operator->() const { return &mpNode->mValue; }
  };
  struct insert_return_type {
    iterator first;
    bool second;
  };

  node_type** mpBucketArray;   // +0x00
  uint32_t mnBucketCount;      // +0x04
  uint32_t mnElementCount;     // +0x08
  float mfMaxLoadFactor;       // +0x0c
  float mfGrowthFactor;        // +0x10
  uint32_t mnNextResize;       // +0x14

  hash_map() {
    mfMaxLoadFactor = 1.0f;
    mfGrowthFactor = 2.0f;
    mnBucketCount = 1;
    mpBucketArray = (node_type**)&gpEmptyBucketArray[0];
    mnElementCount = 0;
    mnNextResize = 0;
  }
  ~hash_map() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
      operator delete[](mpBucketArray);
  }
  iterator end() { return iterator(mpBucketArray + mnBucketCount); }
  iterator find(const K& k);                                                   // 0x00721bb0
  insert_return_type DoInsertValue(const value_type& value, true_type tag);  // 0x00721c30
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);                    // 0x007611f0
  V& operator[](const K& k) {
    iterator it = find(k);
    if (it != end())
      return it->second;
    return DoInsertValue(value_type(k, V()), true_type()).first->second;
  }
  static void* gpEmptyBucketArray[2];  // 0x0154df28
};
}  // namespace eastl

namespace SP {

enum tQuantizeType { kQuantizePositionOnly = 0, kQuantizePositionClasses = 1, kQuantizeAll = 2 };

struct tMDShort4 { short m0, m1, m2, m3; };
struct tMDUByte4 { uint8_t m0, m1, m2, m3; };

struct cEltArrayRef {
  int mNumElts;                                  // +0x0
  uint8_t* mData;                                // +0x4
  uint16_t mEltSize;                             // +0x8
  uint16_t mEltStride;                           // +0xa
  EA::AutoRefCount<EA::COM::IRefCount> mDataRC;  // +0xc
  cEltArrayRef(int eltSize) : mNumElts(0), mData(0), mEltSize((uint16_t)eltSize), mEltStride((uint16_t)eltSize) {}
  int size() const { return mNumElts; }
};

template <typename T>
struct cEltArrayRefT : public cEltArrayRef {
  cEltArrayRefT() : cEltArrayRef(sizeof(T)) {}
  cEltArrayRefT(const cEltArrayRef& r) : cEltArrayRef(r) {}
  cEltArrayRefT& operator=(const cEltArrayRef& r) {
    cEltArrayRef::operator=(r);
    return *this;
  }
  T& operator[](int i) { return *(T*)(mData + i * mEltStride); }
};
// out-of-line instance (0x006c2ad0)
template <>
struct cEltArrayRefT<int> : public cEltArrayRef {
  cEltArrayRefT(const cEltArrayRef& r);
  int& operator[](int i) { return *(int*)(mData + i * mEltStride); }
};

struct cIndexArrayRef : public cEltArrayRef {
  cIndexArrayRef() : cEltArrayRef(0) {}
  int& Int(int i) { return *(int*)(mData + i * mEltStride); }
  uint16_t& UShort(int i) { return *(uint16_t*)(mData + i * mEltStride); }
};

template <typename T>
class cEltArrayT : public EA::COM::IRefCount {
 public:
  void* mpInterfaceVtbl;                 // +0x04
  int mRefCount;                         // +0x08
  eastl::vector<T> mEltData;             // +0x0c
  uint32_t mField20;                     // +0x20
  cEltArrayT();                          // 0x006c3510
  cEltArrayRefT<T> AsRef();              // 0x007217c0
};

struct cMDElementArray {
  int mSemantic;        // +0x00
  int mNumber;          // +0x04
  int mType;            // +0x08
  int mClass;           // +0x0c
  cEltArrayRef mArray;  // +0x10
};

struct cMDFormatEntry {
  short mElts;     // +0x0
  short mIndices;  // +0x2
};

struct cMDSection {
  cIndexArrayRef mVertIndices;                       // +0x00
  int mNumVertices;                                  // +0x10
  eastl::fixed_vector<cMDFormatEntry, 6> mFormat;    // +0x14
  eastl::fixed_vector<cIndexArrayRef, 3> mEltIndices;  // +0x44
};

class cMeshData {
 public:
  void* mpVtbl;                                // +0x00
  int mRefCount;                               // +0x04
  eastl::vector<cMDElementArray> mEltArrays;   // +0x08
  eastl::vector<cMDSection> mSections;         // +0x1c
};

// Per-class quantization settings (8 bytes per entry of the caller's table).
struct cQuantizeClass {
  float mScale;        // +0x0
  bool mUseBoneClass;  // +0x4
  uint8_t mFlagB;      // +0x5
  uint8_t mNormalMask; // +0x6
  uint8_t mPad;
  cQuantizeClass() : mScale(1.0f), mUseBoneClass(true), mFlagB(0), mNormalMask(0) {}
};

struct cDecCellID {
  int m[3];
  cDecCellID(int x, int y, int z) {
    m[0] = x;
    m[1] = y;
    m[2] = z;
  }
};

void PushIndices(cMeshData* meshData);                                                  // 0x007366e0
int FindEltArrayIndex(cMeshData* meshData, int semantic, int number, int type, int classes);  // 0x0071ddc0
int FindSectionEltIndex(cMeshData* meshData, int section, int eltArrayIndex);           // 0x0071e040
void CreateArray(const cIndexArrayRef& src, cIndexArrayRef& dst);                       // 0x007201b0

// @ 0x00726c20
void QuantizeVertices(cMeshData* meshData, float granularity, tQuantizeType quantizeType,
                      const cQuantizeClass* classes)
{
  PushIndices(meshData);
  int pointArrayIndex = FindEltArrayIndex(meshData, 1, 0, 3, 0xe);
  if (pointArrayIndex < 0 || meshData->mEltArrays[pointArrayIndex].mClass != 0)
    return;

  cEltArrayRefT<cSPVector3> points(meshData->mEltArrays[pointArrayIndex].mArray);
  eastl::hash_map<cDecCellID, int> pointMap;
  eastl::fixed_vector<int, 256> indicesRemap(points.mNumElts);
  eastl::fixed_vector<int, 256> anchorIndices;
  eastl::fixed_vector<float, 256> weights;
  cEltArrayT<cSPVector3>* newPoints = new ("Graphics", 0, 0, 0, 0) cEltArrayT<cSPVector3>;
  int newIndex = 0;

  int index = FindEltArrayIndex(meshData, 9, 0, 9, 0xe);
  cEltArrayRefT<tMDShort4> boneIndices;
  cEltArrayRefT<tMDUByte4> boneIndicesB;
  if (index >= 0) {
    boneIndices = meshData->mEltArrays[index].mArray;
    if (boneIndices.mNumElts != points.mNumElts)
      boneIndices = cEltArrayRefT<tMDShort4>();
  } else {
    index = FindEltArrayIndex(meshData, 9, 0, 7, 0xe);
    if (index >= 0) {
      boneIndicesB = meshData->mEltArrays[index].mArray;
      if (boneIndicesB.mNumElts != points.mNumElts)
        boneIndicesB = cEltArrayRefT<tMDUByte4>();
    }
  }

  cEltArrayRefT<long> classIndices;
  cQuantizeClass defaultClass;
  if (classes) {
    defaultClass = classes[0];
    index = FindEltArrayIndex(meshData, 0x18, 0, 6, 0xe);
    if (index >= 0)
      classIndices = meshData->mEltArrays[index].mArray;
  }

  index = FindEltArrayIndex(meshData, 2, 0, 3, 0xe);
  cEltArrayRefT<cSPVector3> normals;
  if (index >= 0) {
    normals = meshData->mEltArrays[index].mArray;
    if (normals.mNumElts != points.mNumElts)
      normals = cEltArrayRefT<cSPVector3>();
  }

  index = FindEltArrayIndex(meshData, 2, 0, 7, 0xe);
  cEltArrayRefT<uint32_t> packedNormals;
  if (index >= 0) {
    packedNormals = meshData->mEltArrays[index].mArray;
    if (packedNormals.mNumElts != points.mNumElts)
      packedNormals = cEltArrayRefT<uint32_t>();
  }

  eastl::fixed_vector<int, 8> sectionStarts;
  index = FindEltArrayIndex(meshData, 0x19, 0, 6, 0xe);
  if (index >= 0) {
    cEltArrayRefT<int> starts(meshData->mEltArrays[index].mArray);
    const uint8_t* p = starts.mData;
    for (int j = 0; j < starts.mNumElts; j++) {
      sectionStarts.push_back(*(const int*)p);
      p += starts.mEltStride;
    }
  } else {
    sectionStarts.push_back(0);
    sectionStarts.push_back(points.size());
  }

  int ns = sectionStarts.size() - 1;
  for (int is = 0; is < ns; is++) {
    for (int i = sectionStarts[is]; i < sectionStarts[is + 1]; i++) {
      int classIdx = 0;
      const cQuantizeClass* info = &defaultClass;
      if (boneIndices.mData) {
        classIdx = boneIndices[i].m0 / 3;
        if (classIndices.mData)
          info = &classes[classIndices[classIdx]];
      } else if (boneIndicesB.mData) {
        classIdx = boneIndicesB[i].m0 / 3;
        if (classIndices.mData)
          info = &classes[classIndices[classIdx]];
      }

      float scale = info->mScale * granularity;
      cSPVector3 v(points[i]);
      cDecCellID cellID(RoundToInt(v.x * scale), RoundToInt(v.y * scale), RoundToInt(v.z * scale));
      cellID.m[0] ^= -(int)info->mUseBoneClass & (classIdx << 24);
      cellID.m[1] ^= info->mFlagB << 24;
      cellID.m[2] ^= is << 27;
      if (normals.mData) {
        cSPVector3 n(normals[i]);
        uint32_t nx = *(uint32_t*)&n.x;
        uint32_t ny = *(uint32_t*)&n.y;
        uint32_t nz = *(uint32_t*)&n.z;
        cellID.m[2] ^= ((((nz >> 29) & 4) + ((ny >> 30) & 2) + (nx >> 31)) & info->mNormalMask) << 24;
      }
      if (packedNormals.mData) {
        uint32_t p = packedNormals[i];
        cellID.m[2] ^= (((((p >> 16) & 0xff) >> 5 & 4) + (((p >> 8) & 0xff) >> 6 & 2) + ((p & 0xff) >> 7)) &
                        info->mNormalMask)
                       << 24;
      }

      eastl::hash_map<cDecCellID, int>::iterator it = pointMap.find(cellID);
      if (it != pointMap.end()) {
        indicesRemap[i] = it->second;
        cSPVector3& p = newPoints->mEltData[it->second];
        p.x = v.x + p.x;
        p.y = p.y + v.y;
        p.z = p.z + v.z;
        weights[it->second] += 1.0f;
      } else {
        indicesRemap[i] = newIndex;
        pointMap[cellID] = newIndex;
        newIndex++;
        newPoints->mEltData.push_back(v);
        weights.push_back(1.0f);
        if (quantizeType)
          anchorIndices.push_back(i);
      }

      if ((i & 0xfff) == 0)
        EA::Thread::ThreadSleep(0);
    }
  }
  EA::Thread::ThreadSleep(0);

  for (int i = 0; i < newIndex; i++) {
    float inv = 1.0f / weights[i];
    cSPVector3& p = newPoints->mEltData[i];
    p.x = inv * p.x;
    p.y = inv * p.y;
    p.z = p.z * inv;
  }

  meshData->mEltArrays[pointArrayIndex].mArray = newPoints->AsRef();

  int numSections = meshData->mSections.size();
  for (int is = 0; is < numSections; is++) {
    int oldEltIndicesIndex = FindSectionEltIndex(meshData, is, pointArrayIndex);
    if (oldEltIndicesIndex < 0)
      continue;
    cIndexArrayRef srcEltIndices(
        meshData->mSections[is].mEltIndices[meshData->mSections[is].mFormat[oldEltIndicesIndex].mIndices]);
    cIndexArrayRef dstEltIndices;
    CreateArray(srcEltIndices, dstEltIndices);
    cIndexArrayRef dstEltIndicesPC;
    if (quantizeType)
      CreateArray(srcEltIndices, dstEltIndicesPC);

    if (srcEltIndices.mEltSize == 4) {
      if (quantizeType) {
        for (int i = 0; i < srcEltIndices.mNumElts; i++) {
          dstEltIndices.Int(i) = indicesRemap[srcEltIndices.Int(i)];
          dstEltIndicesPC.Int(i) = anchorIndices[dstEltIndices.Int(i)];
        }
      } else {
        for (int i = 0; i < srcEltIndices.mNumElts; i++)
          dstEltIndices.Int(i) = indicesRemap[srcEltIndices.Int(i)];
      }
    } else if (srcEltIndices.mEltSize == 2) {
      if (quantizeType) {
        for (int i = 0; i < srcEltIndices.mNumElts; i++) {
          dstEltIndices.UShort(i) = (uint16_t)indicesRemap[srcEltIndices.UShort(i)];
          dstEltIndicesPC.UShort(i) = (uint16_t)anchorIndices[dstEltIndices.UShort(i)];
        }
      } else {
        for (int i = 0; i < srcEltIndices.mNumElts; i++)
          dstEltIndices.UShort(i) = (uint16_t)indicesRemap[srcEltIndices.UShort(i)];
      }
    }

    cMDSection& section = meshData->mSections[is];
    int newEltIndicesIndex = section.mEltIndices.size();
    section.mEltIndices.push_back(dstEltIndices);
    short& formatIndices = section.mFormat[oldEltIndicesIndex].mIndices;
    oldEltIndicesIndex = formatIndices;
    formatIndices = (short)newEltIndicesIndex;
    if (quantizeType) {
      int newEltIndicesPCIndex = section.mEltIndices.size();
      section.mEltIndices.push_back(dstEltIndicesPC);
      for (int f = 0; f < section.mFormat.size(); f++) {
        if (section.mFormat[f].mIndices == oldEltIndicesIndex &&
            (quantizeType == kQuantizeAll ||
             meshData->mEltArrays[section.mFormat[f].mElts].mClass == 0))
          section.mFormat[f].mIndices = (short)newEltIndicesPCIndex;
      }
    }
    EA::Thread::ThreadSleep(0);
  }
}

}  // namespace SP
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
