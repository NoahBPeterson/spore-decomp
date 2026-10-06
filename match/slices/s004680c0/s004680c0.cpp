// Editor model-mesh upload job, 0x004680c0 (5152 bytes).
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
//
// Builds a render-mesh description from the editor's model mesh: offsets every vertex position,
// pads an empty mesh with one dummy triangle, creates a 0x58-byte mesh group ("Editor" heap) holding
// one batch (index desc + a list of vertex streams: positions, normals, tangents, uvs, bone weights,
// bone indices, extra 0x98 stream, bone palette), adds the per-part index ranges, then asks the game
// mesh builder (SP::GetModelAsGameMeshes, 0x7573a0) for a job and queues it (optionally after a
// property-list load job), either waiting for this->mJob or chaining after pDependency.
// No class/method names are known (no PDB/ModAPI hit); type and method names below are descriptive.
// Byte-exact: see the notes on frame holes (declined inline push_back), the inline-budget cutoff and
// the local-name choice next to the function.
#include "types.h"

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)

inline void* operator new(unsigned int, void* p) { return p; }

// Reserved frame of an inline callee that cl /Ob1 declined (not identified): an N-dword hole.
template <int N>
inline void ScratchSlots()
{
    uint32_t s[N];
}
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

// Holder whose ctor/dtor are out of line (0x0041cc20 / 0x004a9b10) and whose Reset() (0x0041d870)
// drops the object and returns the holder as an out-parameter.
struct ObjectRef {
    IObject* p;
    ObjectRef() : p(0) {}
    ObjectRef(IObject* o);                // 0x0041cc20
    ~ObjectRef();                         // 0x004a9b10
    ObjectRef& Reset();                   // 0x0041d870
    IObject* get() const { return p; }
    operator IObject**() { return &p; }
};

// Owner reference inside a stream desc: same out-of-line ctor, inline release.
struct OwnerRef {
    IObject* p;
    OwnerRef(IObject* o);                 // 0x0041cc20
    ~OwnerRef()
    {
        if (p)
            p->Release();
    }
};

struct Vector3 {
    float x, y, z;
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& o);            // 0x004098a0
};
struct Vector2 {
    float x, y;
    Vector2(float x_, float y_) : x(x_), y(y_) {}
};
Vector3* __cdecl Vector3_Add(Vector3* a, const Vector3* b);   // 0x0041ddb0 (a += b)

struct cJob {
    int Release();                        // 0x00690120
    void Queue();                         // 0x006909b0
    void AddDependency(cJob* other);      // 0x00691380
    void Wait();                          // 0x006926b0
};

struct JobRef {
    cJob* p;
    JobRef() : p(0) {}
    ~JobRef()
    {
        if (p)
            p->Release();
    }
    JobRef& Reset();                      // 0x0041d940 (drop + return the holder as out-param)
    JobRef& operator=(cJob* j);           // 0x0041cd10
    cJob* get() const { return p; }
    cJob* operator->() const { return p; }
    operator cJob**() { return &p; }
};

template <class T, int N>
struct Vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];               // sp_vector_allocator
    int size() const { return (int)(mpEnd - mpBegin); }
    T* data() const { return mpBegin; }
    T* begin() const { return mpBegin; }
    T* end() const { return mpEnd; }

    // EASTL vector::push_back. /Ob1 declines to inline these; each call site keeps the callee's
    // reserved frame as a hole in this function's /Od frame.
    void DoInsertValue(T* position, const T& value);
    void DoInsertValueEnd();
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    // The same push_back instance, called after cl had used up this caller's /Ob1 inline budget:
    // no inline attempt, so no reserved frame (from the 6th stream on).
    void push_back_no_inline(const T& value);
    void push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());
    }
};

struct Pod12 { float v[3]; };
struct PairIF { int i; float f; };
struct Elem16 { uint32_t v[4]; };
struct Elem18 { uint32_t v[6]; };
struct Elem8c { uint32_t v[0x8c / 4]; };

struct Vec12 : Vec<Vector3, 0> {
    int count() const;                    // 0x004737f0; push_back 0x004739d0
};
struct VecPairIF : Vec<PairIF, 0> {
    int count() const;                    // 0x00474050
    void erase(PairIF* first, PairIF* last);   // 0x00530c80
    void clear() { erase(mpBegin, mpEnd); }
};
struct VecPairFF : Vec<Vector2, 0> {
    int count() const;                    // 0x00474050; push_back 0x00473f30
};
struct Vec16 : Vec<Elem16, 0> {
    int count() const;                    // 0x004743b0
    void erase(Elem16* first, Elem16* last);   // 0x00548690
    void clear() { erase(mpBegin, mpEnd); }
};
struct VecU32 : Vec<uint32_t, 0> {
    int count() const;                    // 0x004746a0
    void insert(uint32_t* position, uint32_t n, const uint32_t& value);
    void erase(uint32_t* first, uint32_t* last);
    void resize(uint32_t n, const uint32_t& value)  // 0x004746c0
    {
        if (n > (uint32_t)(mpEnd - mpBegin))
            insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value);
        else
            erase(mpBegin + n, mpEnd);
    }
    uint32_t& operator[](int i) { return mpBegin[i]; }
};
struct Vec18 : Vec<Elem18, 0> {};

struct ModelMesh : IObject {
    uint32_t pad04[2];
    VecU32 mIndices;                      // +0x0c
    Vec12 mPositions;                     // +0x20
    Vec12 mNormals;                       // +0x34
    Vec12 mTangents;                      // +0x48
    VecPairFF mTexCoords;                 // +0x5c
    VecPairIF mBoneWeights;               // +0x70 (resource type checked)
    Vec16 mBoneIndices;                   // +0x84
    Vec18 mExtra;                         // +0x98
    uint8_t mBonePalette[4];              // +0xac
};

struct EmptyCheck {                       // any EASTL vector seen through its empty() (0x00526430)
    bool empty();
};

// Vertex-stream description (0x10 bytes): count, data, two 16-bit strides, owner reference.
struct StreamDesc {
    int mCount;
    void* mpData;
    uint16_t mStride;
    uint16_t mStride2;
    OwnerRef mOwner;

    template <class V>
    StreamDesc(V& v, IObject* owner, int stride)
        : mCount(v.count()), mpData(v.data()), mStride((uint16_t)stride), mStride2((uint16_t)stride),
          mOwner(owner)
    {
    }
    StreamDesc(int count, void* data, IObject* owner, int);      // 0x0046f140
    StreamDesc(Vec18* v, IObject* owner, int);                   // 0x004755a0
    StreamDesc(const StreamDesc& o);                             // 0x00401b80
};

// One vertex stream of a batch (0x20 bytes).
struct StreamElem {
    int mUsage;
    int mIndex;
    int mType;
    int mSlot;
    StreamDesc mDesc;
    StreamElem(int usage, int index, int type, int slot, const StreamDesc& d)
        : mUsage(usage), mIndex(index), mType(type), mSlot(slot), mDesc(d)
    {
    }
};

struct StreamElemC : StreamElem {
    StreamElemC(int usage, int index, int type, int slot, const StreamDesc& d);   // 0x00469500
};

struct StreamVec : Vec<StreamElem, 0> {    // push_back 0x0041f7d0
    void reserve(int n);                  // 0x00475320
    int count() const;                    // 0x00475240
};

struct StreamIndex {
    int16_t mStream;
    int16_t mSub;
    StreamIndex(int s, int sub) : mStream((int16_t)s), mSub((int16_t)sub) {}
};

struct IndexVec : Vec<StreamIndex, 0> {   // push_back 0x00475130
    void reserve(int n);                  // 0x00475040
};

struct IndexRange {                       // 0x14 bytes
    IndexRange(int type, int a, uint32_t first, uint32_t last, int b);   // 0x00469550
    uint32_t v[5];
};
struct IndexRangeVec {
    void push_back(const IndexRange& r);  // 0x004227f0
};

struct Batch {                            // 0x8c bytes
    Batch();
    Batch(const Batch& o);
    void SetIndices(const StreamDesc& d); // 0x004694e0
    uint32_t pad00[4];
    int mVertexCount;                     // +0x10
    IndexVec mStreamIndices;              // +0x14
    uint32_t rest[(0x8c - 0x28) / 4];
};

struct BatchVec : Vec<Batch, 0> {        // push_back() 0x00475430
    Batch& back() { return *(mpEnd - 1); }
};

struct MeshGroup {                        // 0x58 bytes, ThreadedObject refcount at +4
    MeshGroup();                          // 0x0040d160
    uint32_t vt;
    volatile long mnRefCount;             // +0x04
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    StreamVec mStreams;                   // +0x08
    BatchVec mBatches;                    // +0x1c
    IndexRangeVec mRanges;                // +0x30
    uint32_t pad34[(0x58 - 0x34) / 4];
};

struct MeshGroupRef {
    MeshGroup* p;
    MeshGroupRef(MeshGroup* g) : p(g)
    {
        if (p)
            p->AddRef();
    }
    ~MeshGroupRef();                      // 0x00472520
    MeshGroup* operator->() const { return p; }
};

struct MeshGroupList {                    // RefVector, 0x1c bytes
    MeshGroupList(int n, const MeshGroupRef& r);   // 0x00472990
    ~MeshGroupList();                     // 0x0041eb80
    uint32_t v[7];
};

struct BonePalette : IObject {            // 0x24 bytes
    BonePalette();                        // 0x00472860
    int AddRef();
    int Release();
    StreamDesc GetDesc();                 // 0x004728e0
    uint32_t pad04[2];
    struct Vec : ::Vec<uint32_t, 0> {
        void assign(uint32_t* first, uint32_t* last);   // 0x00475620
    } mBones;                             // +0x0c
    uint32_t pad20;
};

struct PaletteRef {
    BonePalette* p;
    PaletteRef(BonePalette* o);           // 0x0041cc20
    ~PaletteRef();                        // 0x004a9b10
    BonePalette* operator->() const { return p; }
};

struct IJobManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void AddJob(cJob** job);      // +0x10
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Lock();                  // +0x20
    virtual void Unlock();                // +0x24
};
IJobManager* GetJobManager();             // 0x0068f4d0

struct JobLock {
    IJobManager* p;
    JobLock(IJobManager* m) : p(m) { p->Lock(); }
    ~JobLock() { p->Unlock(); }
};

struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, IObject** dst);   // +0x2c
};
cPropertyManager* PropertyManager();      // 0x0067de30

struct InstanceID {
    uint32_t value;
};
struct ResourceKey {
    InstanceID instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() : instanceID(), typeID(0), groupID(0) {}
};

// Type IDs carry bit fields: byte 1 selects the variant, the top two bits the kind.
struct TypeIDBits {
    uint32_t lo : 8;
    uint32_t variant : 8;
    uint32_t hi : 14;
    uint32_t kind : 2;
};
inline uint32_t WithVariant(uint32_t typeID, int variant)
{
    ((TypeIDBits*)&typeID)->variant = variant;
    return typeID;
}
inline bool IsKind1(uint32_t typeID) { return ((TypeIDBits*)&typeID)->kind == 1; }
struct TypeID {
    uint32_t value;
    TypeID(uint32_t v) : value(v) {}
    uint32_t Variant() const { return (value >> 8) & 0xff; }
};


void __cdecl LoadPropertyListJob(cJob** job, IObject* propList, MeshGroupList* meshes, uint32_t instanceID,
                                 uint32_t key, uint32_t c8, cJob* after);          // 0x00460d40
bool __cdecl GetModelAsGameMeshes(cJob** job, MeshGroupList* meshes, uint32_t instanceID, uint32_t typeID,
                                  uint32_t c8, int, int, void* out1b4, void* out15c, int,
                                  ResourceKey* altKey, cJob* after);               // 0x007573a0

extern bool g_bUseAltModelKey;            // 0x015d3c30

struct SizedSpan {
    int mCount;
    void* mpData;
    SizedSpan(int count, void* data) : mCount(count), mpData(data) {}
};
struct SpanVec : Vec<SizedSpan, 0> {};     // push_back 0x005402c0

struct Holder10 {
    uint32_t pad[0x98 / 4];
    Vec<Elem8c, 0> mElems;                // +0x98
};

class MeshUploadJob {
public:
    bool Run(cJob* pDependency);

    uint32_t pad00[3];
    ModelMesh* mpMesh;                    // +0x0c
    Holder10* mpHolder;                   // +0x10
    Holder10* GetHolder() { return mpHolder; }
    uint32_t pad14[(0xc8 - 0x14) / 4];
    uint32_t mC8;                         // +0xc8
    uint32_t GetC8() const { return mC8; }
    Vector3 mOffset;                      // +0xcc
    uint32_t mInstanceID;                 // +0xd8
    uint32_t mTypeID;                     // +0xdc
    uint32_t GetTypeID() const { return mTypeID; }
    JobRef mJob;                          // +0xe0
    cJob* GetJob() const { return mJob.get(); }
    uint8_t* mBytesBegin;                 // +0xe4
    uint8_t* mBytesEnd;                   // +0xe8
    VecU32 mPartRanges;                   // +0xec
    uint32_t padfc[(0x124 - 0x100) / 4];
    VecU32 mVertexCounts;                 // +0x124 (only begin/end used)
    uint32_t pad138[(0x15c - 0x138) / 4];
    SpanVec mSpans;                       // +0x15c
    uint32_t pad170[(0x1b4 - 0x170) / 4];
    uint32_t mOut1b4;                     // +0x1b4
};

#define ADD_STREAM(VEC, STRIDE, USAGE, IDX, TYPE, SLOT)                                         \
    mAllocator->push_back(StreamIndex(mPositions->size(), -1));                                     \
    mPositions->push_back(StreamElem(USAGE, IDX, TYPE, SLOT, StreamDesc(VEC, mNormals, STRIDE)));

// /Od slot order of the function-scope locals is fixed by cl's symbol-table buckets, so their names were
// chosen (from identifiers already declared above) to reproduce the original frame. Roles:
//   mNormals = the model mesh, rest/kind = holder element begin/count, mBoneWeights = position offset,
//   mStride = vertex positions, mTexCoords = unused flag, mSlot = new mesh group, mUsage = its batch,
//   mAllocator = batch stream-index list, mPositions = group stream list, owner = triangle index count,
//   mDesc = mesh-group list for the builder, mVertexCount = job-manager lock, hi = property-list key,
//   mnRefCount = property-list load job, mBatches = property list, mType = alternate model key,
//   mpBegin = mesh build job.
// @ 0x004680c0
bool MeshUploadJob::Run(cJob* pDependency)
{
    ModelMesh* mNormals = mpMesh;
    Elem8c* rest = GetHolder()->mElems.mpBegin;
    int kind = GetHolder()->mElems.size();

    mSpans.push_back(SizedSpan(mBytesEnd - mBytesBegin, mBytesBegin));

    Vector3 mBoneWeights(mOffset);
    Vector3* mStride = mNormals->mPositions.mpBegin;
    for (int i = 0, n = mNormals->mPositions.size(); i < n; i++)
        Vector3_Add(&mStride[i], &mBoneWeights);

    ScratchSlots<2>();
    if (((EmptyCheck*)&mNormals->mIndices)->empty()) {
        // empty mesh: one degenerate triangle
        mNormals->mIndices.resize(3, 0);
        mNormals->mPositions.push_back(Vector3(0.0f, 0.0f, 0.0f));
        mNormals->mNormals.push_back(Vector3(0.0f, 0.0f, 1.0f));
        mNormals->mTangents.push_back(Vector3(0.0f, 1.0f, 0.0f));
        mNormals->mTexCoords.push_back(Vector2(0.0f, 0.0f));
        mNormals->mBoneWeights.clear();
        mNormals->mBoneIndices.clear();
    }

    mVertexCounts.push_back(mNormals->mPositions.size());
    mPartRanges.push_back(mNormals->mIndices.size());

    bool mTexCoords = false;
    ScratchSlots<2>();
    MeshGroupRef mSlot(new ("Editor", 0, 0, 0, 0) MeshGroup());
    mSlot->mBatches.push_back();
    Batch* mUsage = &mSlot->mBatches.back();
    IndexVec* mAllocator = &mUsage->mStreamIndices;
    StreamVec* mPositions = &mSlot->mStreams;
    mAllocator->reserve(8);
    mPositions->reserve(8);

    ADD_STREAM(mNormals->mPositions, 0xc, 1, 0, 3, 0)
    ADD_STREAM(mNormals->mNormals, 0xc, 2, 0, 3, 1)
    ADD_STREAM(mNormals->mTexCoords, 8, 8, 0, 2, 2)
    ADD_STREAM(mNormals->mTangents, 0xc, 3, 0, 3, 2)

    if (!((EmptyCheck*)&mNormals->mBoneWeights)->empty()) {
        ADD_STREAM(mNormals->mBoneWeights, 8, 9, 0, 9, 0)
        mAllocator->push_back(StreamIndex(mPositions->size(), -1));
        mPositions->push_back_no_inline(StreamElem(10, 0, 4, 0, StreamDesc(mNormals->mBoneIndices, mNormals, 0x10)));
        if (!((EmptyCheck*)&mNormals->mExtra)->empty()) {
            mAllocator->push_back_no_inline(StreamIndex(mPositions->size(), -1));
            mPositions->push_back_no_inline(StreamElemC(0x18, 0, 6, 5, StreamDesc(&mNormals->mExtra, mNormals, 0)));
        }
        PaletteRef palette(new ("Editor", 0, 0, 0, 0) BonePalette());
        palette->mBones.assign(mVertexCounts.begin(), mVertexCounts.end());
        mAllocator->push_back_no_inline(StreamIndex(mPositions->count(), -1));
        mPositions->push_back_no_inline(StreamElemC(0x19, 0, 6, 0xb, palette->GetDesc()));
    }

    int owner = mNormals->mIndices.count();
    mUsage->mVertexCount = mNormals->mPositions.count();
    mUsage->SetIndices(StreamDesc(owner, mNormals->mIndices.data(), mNormals, 0));
    mPositions->push_back_no_inline(StreamElemC(0x15, 0, 6, 8, StreamDesc(1, mNormals->mBonePalette, mNormals, 0)));

    for (int i = 1, n = mPartRanges.count(); i < n; i++)
        mSlot->mRanges.push_back(IndexRange(4, 0, mPartRanges[i - 1], mPartRanges[i], 0));

    MeshGroupList mDesc(1, mSlot);
    JobLock mVertexCount(GetJobManager());

    if (pDependency == 0) {
        GetJobManager()->AddJob(mJob.Reset());
        GetJob();
    }

    uint32_t hi = WithVariant(mTypeID, 0xe3);
    JobRef mnRefCount;
    ObjectRef mBatches;
    if (PropertyManager()->GetPropertyList(0x4529f96f, hi, mBatches.Reset()))
        LoadPropertyListJob(mnRefCount.Reset(), mBatches.get(), &mDesc, mInstanceID, hi, GetC8(), mJob.get());

    ResourceKey mType;
    if (g_bUseAltModelKey && IsKind1(GetTypeID())) {
        if (TypeID(GetTypeID()).Variant() == 0x62) {
            mType.instanceID.value = mInstanceID;
            mType.groupID = WithVariant(mTypeID, 0x71);
            mType.typeID = 0xffffffff;
        }
    }

    JobRef mpBegin;
    if (!GetModelAsGameMeshes(mpBegin.Reset(), &mDesc, mInstanceID, mTypeID, GetC8(), 0, 0, &mOut1b4, &mSpans,
                              0, mType.instanceID.value ? &mType : 0,
                              (mnRefCount.p ? mnRefCount : mJob).get())) {
        return false;
    }

    if (mnRefCount.p)
        mnRefCount->Queue();
    if (pDependency == 0) {
        mpBegin->Queue();
        mJob->Queue();
        mJob->Wait();
        mJob = 0;
    } else {
        mpBegin->AddDependency(pDependency);
        mpBegin->Queue();
    }
    return true;
}
