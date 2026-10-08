// s0046e450 -- /Od /Ob1 region (no /arch: x87 float code).
// Flags: /Od /Ob1 /MD /Gy /TP.
//  * ExportCreatureBlocksFile (0x0046e450): writes "<name>.blocks", a text dump of an editor creature's
//    rig blocks (joint position, cal3D origin, bounds, sound ids, caps, deform channels).
//  * DumpEditorModelZPR (0x0046eae0): builds the editor model's render mesh through the paint system,
//    wraps it in a MeshGroup and hands it to DumpZPR (0x0046f2a0). (The name is a guess.)
// Local names in both are chosen for their /Od slot order (cl lays locals out by name hash).
#include <stdio.h>
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t s[N]; }


struct Mgr {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13(void*);
};

extern "C" Mgr* FUN_0067dd60();

struct Sf260 {
    int field0;
    unsigned char flags;
};

// @ 0x0046f260
int __fastcall FUN_0046f260(Sf260* p)
{
    if (!(p->flags & 1))
        FUN_0067dd60()->v13(p);
    return p->field0;
}

struct BaseDesc {
    virtual void v0();
};

struct Desc {
    int a, b;
    unsigned short c, d;
    BaseDesc* ref;
    Desc* init(int, int, BaseDesc*, int);
    Desc* init0();
};

// @ 0x0046f140
Desc* Desc::init(int a_, int b_, BaseDesc* r_, int)
{
    a = a_;
    b = b_;
    c = 4;
    d = 4;
    BaseDesc** local = &ref;
    *local = r_;
    if (*local)
        (*local)->v0();
    return this;
}

// @ 0x0046f1f0
Desc* Desc::init0()
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    BaseDesc** local = &ref;
    *local = 0;
    if (*local)
        (*local)->v0();
    return this;
}

// ---- not yet reproduced -----------------------------------------------------

// @ 0x0046f1b0
void F_0046f1b0() {}

// ===================================================================================
// ExportCreatureBlocksFile
// ===================================================================================

struct EAString8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    unsigned int alloc;
    struct Tag {};
    EAString8(Tag, const char* fmt, ...);
    ~EAString8();
    const char* c_str() const { return mpBegin; }
};

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
};
struct IPropertyManager {
    virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3(); virtual void pv4();
    virtual void pv5(); virtual void pv6(); virtual void pv7(); virtual void pv8(); virtual void pv9();
    virtual void pv10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList*& result);
};
IPropertyManager* PropertyManager();
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, void* result);

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T*& AsOutParam() {
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return mpObject;
    }
};

struct Vec3 {
    float v[3];
    float& operator[](int i) { return v[i]; }
};

struct CapEntry { const char* name; int value; };
struct DeformEntry { uint32_t id; float value; };

struct Block {
    int version;           // +0x00
    wchar_t name[80];      // +0x04
    char boneName[40];     // +0xa4
    uint32_t keyGroup;     // +0xcc
    uint32_t instanceId;   // +0xd0
    int blockIndex;        // +0xd4
    int parentIndex;       // +0xd8
    int symmetricIndex;    // +0xdc
    Vec3 jointPosition;    // +0xe0
    int submeshIndex;      // +0xec
    Vec3 cal3DOrigin;      // +0xf0
    Vec3 effectsOrigin;    // +0xfc
    Vec3 position;         // +0x108
    float orientX, orientY, orientZ, orientW;  // +0x114
    Vec3 bBoxMin;          // +0x124
    Vec3 bBoxMax;          // +0x130
    float scale;           // +0x13c
    uint32_t pad140;
    uint32_t soundIDFoot;  // +0x144
    uint32_t soundIDMouth; // +0x148
    uint32_t soundIDWeapon;// +0x14c
    int numCaps;           // +0x150
    int numDeform;         // +0x154
    CapEntry caps[32];     // +0x158
    DeformEntry deform[8]; // +0x258
    uint32_t pad298;
};

struct BlockVec {
    Block* mpBegin;
    Block* mpEnd;
    Block* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    Block& operator[](int i) { return mpBegin[i]; }
};

struct CreatureBlocks {
    int version;               // +0
    const wchar_t* mpName;     // +4
    uint32_t pad[6];
    unsigned char isPlant;     // +0x20
    int cal3DRootBlockIndex;   // +0x24
    BlockVec blocks;           // +0x28
    const wchar_t* GetName() const { return mpName; }
};

// Local names: it = file, value = path, x/n = block index/count, base = block, ptr = leftHanded,
// tmp = property list, other = key, len = property id, g/buf = cap index/count, z/hi = deform count/index.
// @ 0x0046e450
namespace SP { namespace EditorUtils {
void ExportCreatureBlocksFile(const wchar_t* baseName, CreatureBlocks* data)
{
    EAString8 value(EAString8::Tag(), "%ls.blocks", baseName);
    FILE* it = fopen(value.c_str(), "w");
    fprintf(it, "version %d\n", data->version);
    fprintf(it, "name \"%S\"\n", data->GetName());
    fprintf(it, "isPlant %d\n", data->isPlant != 0);
    fprintf(it, "cal3DRootBlockIndex %d\n", data->cal3DRootBlockIndex);
    fprintf(it, "numBlocks %d\n\n", data->blocks.size());
    for (int x = 0, n = data->blocks.size(); x < n; ++x) {
        Block* base = &data->blocks[x];
        fprintf(it, "block %d\n", base->blockIndex);
        fprintf(it, "\tversion %d\n", base->version);
        fprintf(it, "\tname %S\n", base->name);
        fprintf(it, "\tinstanceId %d\n", base->instanceId);
        fprintf(it, "\tparentIndex %d\n", base->parentIndex);
        fprintf(it, "\tsymmetricIndex %d\n", base->symmetricIndex);
        fprintf(it, "\tjointPosition %f %f %f\n", base->jointPosition[0], base->jointPosition[1], base->jointPosition[2]);
        fprintf(it, "\tsubmeshIndex %d\n", base->submeshIndex);
        bool ptr = false;
        {
        AutoRefCount<cPropertyList> tmp;
        if (PropertyManager()->GetPropertyList(base->instanceId, base->keyGroup, tmp.AsOutParam())) {
            uint32_t other = 0;
            const uint32_t len = 0xf48eb09;
            if (GetPropertyAsKeyInstance(tmp, len, &other)) {
                if (other == base->instanceId)
                    ptr = true;
            }
        }
        }
        ScratchSlots<3>();
        fprintf(it, "\tleftHanded %d\n", ptr);
        fprintf(it, "\tcal3DBoneName %s\n", base->boneName);
        fprintf(it, "\tcal3DOrigin %f %f %f\n", base->cal3DOrigin[0], base->cal3DOrigin[1], base->cal3DOrigin[2]);
        fprintf(it, "\teffectsOrigin %f %f %f\n", base->effectsOrigin[0], base->effectsOrigin[1], base->effectsOrigin[2]);
        fprintf(it, "\tposition %f %f %f\n", base->position[0], base->position[1], base->position[2]);
        fprintf(it, "\torientation %f %f %f %f\n", base->orientX, base->orientY, base->orientZ, base->orientW);
        fprintf(it, "\tbBoxMin %f %f %f\n", base->bBoxMin[0], base->bBoxMin[1], base->bBoxMin[2]);
        fprintf(it, "\tbBoxMax %f %f %f\n", base->bBoxMax[0], base->bBoxMax[1], base->bBoxMax[2]);
        fprintf(it, "\tscale %f\n", base->scale);
        fprintf(it, "\tsoundIDFoot 0x%8.8x\n", base->soundIDFoot);
        fprintf(it, "\tsoundIDMouth 0x%8.8x\n", base->soundIDMouth);
        fprintf(it, "\tsoundIDWeapon 0x%8.8x\n", base->soundIDWeapon);
        for (int g = 0, buf = base->numCaps; g < buf; ++g)
            fprintf(it, "\tcap %s %d\n", base->caps[g].name, base->caps[g].value);
        for (int hi = 0, z = base->numDeform; hi < z; ++hi)
            fprintf(it, "\tdeformChannel 0x%8.8x %f\n", base->deform[hi].id, base->deform[hi].value);
        fprintf(it, "end\n\n");
    }
    fclose(it);
}
} }  // namespace SP::EditorUtils

// ===================================================================================
// DumpEditorModelZPR
// ===================================================================================

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)

inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

struct OwnerRef {
    IObject* p;
    OwnerRef(IObject* o);                 // 0x0041cc20
    ~OwnerRef()
    {
        if (p)
            p->Release();
    }
};

struct StreamDesc {                       // 0x10 bytes
    int mCount;
    void* mpData;
    uint16_t mStride;
    uint16_t mStride2;
    OwnerRef mOwner;
    StreamDesc(int count, void* data, int stride, IObject* owner)
        : mCount(count), mpData(data), mStride((uint16_t)stride), mStride2((uint16_t)stride), mOwner(owner)
    {
    }
    StreamDesc(int count, void* data, IObject* owner, int);   // 0x0046f140
    StreamDesc(const StreamDesc& o);                          // 0x00401b80
    StreamDesc& operator=(const StreamDesc& o);               // 0x004694e0 (via 0x00424f70)
};

struct StreamElem {                       // 0x20 bytes
    int mUsage;
    int mIndex;
    int mType;
    int mSlot;
    StreamDesc mDesc;
    StreamElem(int usage, int index, int type, int slot, const StreamDesc& d)
        : mUsage(usage), mIndex(index), mType(type), mSlot(slot), mDesc(d)
    {
    }
    StreamElem& operator=(const StreamElem& o);               // 0x00424f10
};

struct StreamIndex {
    int16_t mStream;
    int16_t mSub;
    StreamIndex(int s, int sub) : mStream((int16_t)s), mSub((int16_t)sub) {}
};

struct StreamVec {
    StreamElem* mpBegin;
    StreamElem* mpEnd;
    StreamElem* mpCapacity;
    uint32_t mAllocator[2];
    void resize(unsigned n);                                  // 0x00475260
    StreamElem& operator[](int i) { return mpBegin[i]; }
};
struct DescVec {
    StreamDesc* mpBegin;
    StreamDesc* mpEnd;
    StreamDesc* mpCapacity;
    uint32_t mAllocator[2];
    void resize(unsigned n);                                  // 0x004751a0
    StreamDesc& operator[](int i) { return mpBegin[i]; }
};
struct IndexVec {
    StreamIndex* mpBegin;
    StreamIndex* mpEnd;
    StreamIndex* mpCapacity;
    uint32_t mAllocator[2];
    void push_back(const StreamIndex& v);                     // 0x00475130
};

struct __declspec(align(4)) Batch {                            // 0x8c bytes
    Batch();                              // 0x0046f1b0
    ~Batch();                             // 0x0041f940
    uint32_t mIndices[4];                 // +0x00 (StreamDesc)
    int mVertexCount;                     // +0x10
    IndexVec mStreamIndices;              // +0x14
    uint32_t pad28[(0x44 - 0x28) / 4];
    DescVec mIndexDescs;                  // +0x44
    uint32_t pad58[(0x8c - 0x58) / 4];
};
struct BatchVec {
    Batch* mpBegin;
    Batch* mpEnd;
    Batch* mpCapacity;
    uint32_t mAllocator[2];
    void push_back(const Batch& b);                           // 0x004754e0
    Batch& back() { return *(mpEnd - 1); }
};

struct IndexRange {                       // 0x14 bytes
    IndexRange(int type, int a, uint32_t first, uint32_t last, int b);   // 0x00469550
    uint32_t v[5];
};
struct IndexRangeVec {
    void push_back(const IndexRange& r);                      // 0x004227f0
};

struct MeshGroup {                        // 0x58 bytes
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

struct DefaultRefCounted {
    void* vtbl;
    int mnRefCount;
    void Release();                       // 0x00453540
};
struct V3Vec {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    uint32_t mAllocator[2];
};
template <typename T>
struct Vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    T* begin() const { return mpBegin; }
};
struct Vec3f { float x, y, z; };
struct Vec2f { float x, y; };
struct cMesh : DefaultRefCounted {
    Vec<Vec3f> mVertices;                 // +0x08
    uint32_t pad1c[(0x30 - 0x1c) / 4];
    Vec<Vec2f> mTextureCoordinates;       // +0x30
    uint32_t pad44[5];
    Vec<uint32_t> mVertexIndices_TV;      // +0x58
    uint32_t pad6c[5];
    Vec<uint32_t> mTextureIndices_TV;     // +0x80
};
struct MeshRef {
    cMesh* p;
    MeshRef() : p(0) {}
    ~MeshRef();                           // 0x00472540
    MeshRef& Reset();                     // 0x0041d900
    operator cMesh**() { return &p; }
    cMesh* operator->() const { return p; }
};

struct EditorModelSource {
    uint32_t pad00[0xfc / 4];
    Sf260* mpTexture;                     // +0xfc
    Sf260* GetTexture() { return mpTexture; }
};
struct cPaintSystem {
    void BuildMeshes(EditorModelSource* src, cMesh** ppMesh);   // 0x00525360
};
cPaintSystem* GetPaintSystem();           // 0x00401080

struct AllocTag { AllocTag() {} };
struct RefVector {                        // 0x14 bytes
    MeshGroup** mpBegin;
    MeshGroup** mpEnd;
    MeshGroup** mpCapacity;
    uint32_t mAllocator[2];
    RefVector(const AllocTag&);           // 0x00540470
    RefVector(const RefVector& o);        // 0x0041eae0
    ~RefVector();                         // 0x0041eb80
    void push_back(const MeshGroupRef& r);  // 0x0041ef20
};
bool DumpZPR(RefVector models, int tex, const wchar_t* name);   // 0x0046f2a0

// Frame holes: the original's declined inline callees leave reserved frames (ScratchSlots below:
// before the MeshGroup, after the batch push_back, around the two resize calls). Batch is declared
// align(4) so its temporary sits at the top of the frame like the original's.
// Names: offset = mesh, g = group list, val = batch, owner = index count, hi = mesh group.
// @ 0x0046eae0
namespace SP { namespace EditorUtils {
void DumpEditorModelZPR(EditorModelSource* src, const wchar_t* name)
{
    MeshRef offset;
    GetPaintSystem()->BuildMeshes(src, offset.Reset());
    ScratchSlots<2>();
    MeshGroupRef hi(new ("App", 0, 0, 0, 0) MeshGroup());
    hi->mBatches.push_back(Batch());
    ScratchSlots<3>();
    Batch* val = &hi->mBatches.back();
    ScratchSlots<12>();
    hi.p->mStreams.resize(2);
    hi->mStreams[0] = StreamElem(1, 0, 3, 0, StreamDesc(offset->mVertices.size(), offset->mVertices.begin(), 12, 0));
    hi->mStreams[1] = StreamElem(8, 0, 2, 2, StreamDesc(offset->mTextureCoordinates.size(), offset->mTextureCoordinates.begin(), 8, 0));
    int owner = offset->mVertexIndices_TV.size();
    val->mVertexCount = offset->mVertices.size();
    ScratchSlots<8>();
    val->mIndexDescs.resize(2);
    val->mIndexDescs[0] = StreamDesc(owner, offset->mVertexIndices_TV.begin(), (IObject*)0, 0);
    val->mIndexDescs[1] = StreamDesc(owner, offset->mTextureIndices_TV.begin(), (IObject*)0, 0);
    val->mStreamIndices.push_back(StreamIndex(0, 0));
    val->mStreamIndices.push_back(StreamIndex(1, 1));
    hi->mRanges.push_back(IndexRange(4, 0, 0, owner, 0));
    RefVector g((AllocTag()));
    g.push_back(hi);
    DumpZPR(g, FUN_0046f260(src->GetTexture()), name);
}
} }  // namespace SP::EditorUtils
