// Slice s00464300 (SPBake/SPEditorExportUtilities.cpp).
//   nSPSkinner::cExportHelper ctor/dtor            (0x00464300 / 0x00464480)
//   (anonymous)::cBlockGeometryExporter ctor/dtor  (0x00464580 / 0x00464680)
//   free export routine                            (0x004647b0)
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// Reserves N dwords of /Od frame, standing in for the frame of an inline callee cl declined.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---------------------------------------------------------------------------------------------
// EASTL bits (retail layout: three pointers + an 8-byte allocator slot = 0x14)
// ---------------------------------------------------------------------------------------------
// The allocator's deallocate tail of each vector instantiation is out of line and takes the
// vector header in ecx. Declared as __fastcall with one pointer so the call site is exactly
// `mov ecx, header; call`; the address comment lets the equivalence harness bind each one.
void __fastcall DeallocU32(void* header);        // 0x00425990
void __fastcall DeallocF64(void* header);        // 0x0045daf0
void __fastcall DeallocVec3(void* header);       // 0x005156b0
void __fastcall DeallocVec4(void* header);       // 0x00554b10
void __fastcall DeallocNode(void* header);       // 0x00474f30
void __fastcall DeallocJoint(void* header);      // 0x00474fb0
void __fastcall DeallocBone(void* header);       // 0x00476ec0
void __fastcall DeallocKey(void* header);        // 0x00476f80

namespace eastl {

// Per-element deallocator (specialized below, once every element type is declared).
template <class T> struct VectorDeallocator;

// Empty tag argument of the tagged vector constructor (the temporary sits in one byte of the frame).
// Retail's empty constructor carried an unused 4-byte local; /Od still gives it a frame slot, which is
// the 4-byte hole below the tag temporary in both constructors of this slice.
struct allocator_tag {
    allocator_tag() {}
};

// The allocator slot is 8 bytes; only its first word is ever written. The tag constructor stayed
// out of line in retail (0x00429360, empty, __thiscall ret 4).
struct sp_vector_allocator {
    uint32_t mData[2];
    sp_vector_allocator() {}
    sp_vector_allocator(const allocator_tag& tag);    // 0x00429360
};

// Only the deallocate tail of these destructors is out of line (one per element size:
// 0x00425990 u32, 0x0045daf0 double, 0x005156b0 0xc, 0x00554b10 0x10, 0x00476ec0 0x54, 0x00476f80 0x30).
// Retail calls them with the vector header in ecx (__thiscall, no arguments).

// Trivially-destructible elements: the whole destructor is inlined, leaving an empty element loop.
template <class T>
class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    vector(const allocator_tag& tag)
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(tag) {}
    ~vector() {
        for (T* p = mpBegin; p < mpEnd; ++p) {
        }
        VectorDeallocator<T>::Free(this);
    }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int i) { return *(mpBegin + i); }
};

// Elements with a real destructor: retail kept the destructor of these vector instantiations out of
// line (0x00474f30 node, 0x00474fb0 export_joint), so the member destructor is a plain call.
// Retail's inline tagged constructor of this template carried an unused 4-byte local; /Od gives it a
// frame slot, which is the 4-byte hole below the tag temporary in both constructors of this slice.
template <class T>
class vector_external_dtor {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    vector_external_dtor() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    vector_external_dtor(const allocator_tag& tag)
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(tag)
    {
        unsigned int unused;
    }
    // Inlined at the call site, which is `mov ecx, header; call <full element dtor>`.
    ~vector_external_dtor() { VectorDeallocator<T>::Free(this); }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
};

}  // namespace eastl

// ---------------------------------------------------------------------------------------------
// geometry element types (same shapes as slice s00464bb0)
// ---------------------------------------------------------------------------------------------
struct cSPVector2 { float x, y; };
struct cSPVector3 { float x, y, z; };
struct cSPVector4 { float x, y, z, w; };
namespace SP { struct tMDUByte4 { uint8_t v[4]; }; }

// Local element stand-ins for the skinner helper's containers (only sizes matter here).
struct cExportHelperNode { uint8_t mData[0x48]; };
struct cExportHelperBone { uint8_t mData[0x54]; };
struct cExportHelperExportJoint { uint8_t mData[0xd8]; };
struct cExportHelperKeyPair { uint8_t mData[0x30]; };

namespace eastl {
template <> struct VectorDeallocator<unsigned int> {
    static void Free(void* header) { DeallocU32(header); }
};
template <> struct VectorDeallocator<double> {
    static void Free(void* header) { DeallocF64(header); }
};
template <> struct VectorDeallocator<cSPVector3> {
    static void Free(void* header) { DeallocVec3(header); }
};
template <> struct VectorDeallocator<cSPVector4> {
    static void Free(void* header) { DeallocVec4(header); }
};
template <> struct VectorDeallocator<cSPVector2> {
    static void Free(void* header) { DeallocF64(header); }
};
template <> struct VectorDeallocator<SP::tMDUByte4> {
    static void Free(void* header) { DeallocU32(header); }
};
template <> struct VectorDeallocator<cExportHelperNode> {
    static void Free(void* header) { DeallocNode(header); }
};
template <> struct VectorDeallocator<cExportHelperExportJoint> {
    static void Free(void* header) { DeallocJoint(header); }
};
template <> struct VectorDeallocator<cExportHelperBone> {
    static void Free(void* header) { DeallocBone(header); }
};
template <> struct VectorDeallocator<cExportHelperKeyPair> {
    static void Free(void* header) { DeallocKey(header); }
};
}

// eastl::basic_string<wchar_t> (string16): three pointers + a 4-byte allocator word.
extern wchar_t gEmptyString16;                        // 0x01667bac

// Empty tag of the formatting constructor; a variadic member uses __cdecl in MSVC, so `this` is
// the first stack argument (as in the original: the path temporary is pushed last).
struct CtorSprintf {};

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int mAllocator;

    string16()
    {
        mpBegin = 0;
        mpEnd = 0;
        mpCapacity = 0;
        mpBegin = &gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    string16(CtorSprintf tag, const wchar_t* fmt, ...);   // 0x00473020 (__cdecl)
    void Deallocate();                                // 0x004237d0 (thiscall, empty except free)
    ~string16() { Deallocate(); }
};

// Hothead scalar constants (shared .rdata floats).
extern const float kZero;                             // 0x01485378
extern const float kOne;                              // 0x01485720

namespace EA {
template <class T>
class RectT {
public:
    T left, top, right, bottom;
    RectT(T l, T t, T r, T b) : left(l), top(t), right(r), bottom(b) {}
};
namespace IO {
void SplitPath(const wchar_t* pPath, wchar_t* pDrive, wchar_t* pDirectory, wchar_t* pFileName,
               wchar_t* pExtension, int nCapacity);    // 0x00930180
}
}

// ---------------------------------------------------------------------------------------------
// nSPSkinner::cExportHelper (0xa4)
// ---------------------------------------------------------------------------------------------
namespace nSPSkinner {

class cExportHelper {
public:
    cExportHelper();                                  // 0x00464300
    ~cExportHelper();                                 // 0x00464480

    void InitStaticMesh(const wchar_t* path);                               // 0x004fe860
    void ExportDummyStaticSkeleton();                                       // 0x005001c0
    void Init(const wchar_t* name, void* nodes, void* links, void* xforms,
              int firstChild, char flag);                                   // 0x004fe8c0
    void ExportMeshBegin(unsigned int numSubmeshes, bool ascii);            // 0x00500880
    void ExportSubmesh(void* mesh, void* weights);                          // 0x00500920
    void ExportMeshEnd();                                                   // 0x00501200
    void ExportSkeleton();                                                  // 0x005002d0

    string16 mBasename;                                                     // +0x00
    eastl::vector_external_dtor<cExportHelperNode> mNodes;                  // +0x10
    eastl::vector<cExportHelperBone> mBones;                                // +0x24
    unsigned int root_nidx;                                                 // +0x38
    bool mMoveRootToOrigin;                                                 // +0x3c
    eastl::vector<unsigned int> parent_nidxs;                               // +0x40
    eastl::vector_external_dtor<cExportHelperExportJoint> mExportJoints;    // +0x54
    unsigned int mExtraJointIDs;                                            // +0x68
    void* export_mesh_FILE;                                                 // +0x6c
    bool export_ascii_mesh;                                                 // +0x70
    unsigned int export_num_meshes;                                         // +0x74
    unsigned int export_submesh_idx;                                        // +0x78
    eastl::vector<double> mKeyTimes;                                        // +0x7c
    eastl::vector<cExportHelperKeyPair> mKeys;                              // +0x90
};

// @ 0x00464300
cExportHelper::cExportHelper()
    : mNodes(eastl::allocator_tag())
    , mBones(eastl::allocator_tag())
    , export_mesh_FILE(0)
    , export_ascii_mesh(false)
    , export_num_meshes(0)
    , export_submesh_idx(0)
{
    bool unused;                                      // retail kept a 1-byte local: the tags start at -2
}

// @ 0x00464480
cExportHelper::~cExportHelper()
{
}

}  // namespace nSPSkinner

// ---------------------------------------------------------------------------------------------
// (anonymous namespace)::cBlockGeometryExporter (0x78)
// ---------------------------------------------------------------------------------------------
namespace {

class cBlockGeometryExporter {
public:
    cBlockGeometryExporter();                         // 0x00464580
    ~cBlockGeometryExporter();                        // 0x00464680

    eastl::vector_external_dtor<unsigned int> mTriangleIndices;    // +0x00
    eastl::vector<cSPVector3> mPositions;                   // +0x14
    eastl::vector<cSPVector3> mNormals;                     // +0x28
    eastl::vector<cSPVector2> mTextureCoordinates;          // +0x3c
    eastl::vector<cSPVector4> mBoneWeights;                 // +0x50
    eastl::vector<SP::tMDUByte4> mBoneIndices;              // +0x64

    void Export(nSPSkinner::cExportHelper& helper, void* block, EA::RectT<float>& uvRect,
                unsigned int id, bool flag);                // 0x00464bb0
};

// @ 0x00464580
cBlockGeometryExporter::cBlockGeometryExporter()
    : mTriangleIndices(eastl::allocator_tag())
{
}

// @ 0x00464680
cBlockGeometryExporter::~cBlockGeometryExporter()
{
}

}  // namespace

// ---------------------------------------------------------------------------------------------
// skin / editor model shapes used by the export routine (same layouts as the migrated headers)
// ---------------------------------------------------------------------------------------------
namespace SP {

class cSPEditorModel {
public:
    const wchar_t* GetFileName();                 // 0x004ae000
    unsigned int GetBlockCount();                 // 0x004accf0
    void* GetBlock(unsigned int index);           // 0x004accb0
};

}  // namespace SP

struct SkinBone {                                 // 0x8c bytes
    int16_t mBlockIndex;                          // +0x00
    int16_t mNodeIndex;                           // +0x02
    int16_t mParent;                              // +0x04
    int16_t mSymmetric;                           // +0x06
    uint16_t mFlags;                              // +0x08
    uint8_t mPartIndex;                           // +0x0a
    uint8_t mType;                                // +0x0b
    uint8_t mPad0c[0x8c - 0x0c];
};

struct SkinBoneVector {
    SkinBone* mpBegin;
    SkinBone* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct SkinData {
    uint8_t mPad0[0x98];
    SkinBoneVector mBones;                        // +0x98
};

struct cSkin {
    SkinData* GetSkinData() { return mpSkinData; }
    uint8_t mPad00[8];
    SkinData* mpSkinData;                         // +0x08
    uint8_t mPad0c[0x34 - 0x0c];
    void* mpSkinMesh;                             // +0x34
    uint8_t mPad38[0x40 - 0x38];
    eastl::vector<unsigned int> mBoneNodes;       // +0x40
    eastl::vector<unsigned int> mBoneLinks;       // +0x54
    eastl::vector<unsigned int> mBoneXforms;      // +0x68
    eastl::vector<unsigned int> mSkinWeights;     // +0x7c
    eastl::vector<EA::RectT<float> > mUVRects;    // +0x90
    uint8_t mPadA4[0xc0 - 0xa4];
    void** mpBlocks;                              // +0xc0
};

// Export model / holder (0x44 bytes): Ctor 0x461400, Dtor 0x4614b0.
struct C461400 {
    uint8_t mData[0x44];
    C461400* Ctor();
    void Dtor();
};

namespace SP { namespace EditorUtils {
void CreateExportCreatureModel(cSkin* pSkin, const wchar_t* modelpath, C461400* pExportModel,
                               nSPSkinner::cExportHelper* helper, bool ignorePartModels);  // 0x0046c900
void ExportCreatureBlocksFile(const wchar_t* baseName, C461400* data);                    // 0x0046e450
}}

// @ 0x004647b0
void F_004647b0(SP::cSPEditorModel* model, cSkin* skin, const wchar_t* dir)
{
    wchar_t name[260];
    EA::IO::SplitPath(model->GetFileName(), 0, 0, name, 0, 4);
    string16 path(CtorSprintf(), L"%ls/%ls", dir, name);

    nSPSkinner::cExportHelper helper;
    cBlockGeometryExporter accum;

    if (skin == 0) {
        helper.InitStaticMesh(path.mpBegin);
        helper.ExportDummyStaticSkeleton();
        int count = model->GetBlockCount();
        helper.ExportMeshBegin(count, false);
        for (int i = 0; i < count; i++) {
            EA::RectT<float> rect(kZero, kZero, kOne, kOne);
            accum.Export(helper, model->GetBlock(i), rect, 0, false);
        }
        helper.ExportMeshEnd();
    } else {
        SkinBone* bones = skin->GetSkinData()->mBones.mpBegin;
        int numBones = skin->GetSkinData()->mBones.size();
        int meshCount = 1;
        for (int i = 0; i < numBones; i++) {
            if (bones[i].mPartIndex > 0)
                meshCount++;
        }
        helper.Init(path.mpBegin, &skin->mBoneNodes, &skin->mBoneLinks, &skin->mBoneXforms,
                    numBones, 0);
        helper.ExportMeshBegin(meshCount, false);
        helper.ExportSubmesh(skin->mpSkinMesh, skin->mSkinWeights.mpBegin);
        for (int i = 0; i < numBones; i++) {
            if (bones[i].mPartIndex > 0) {
                void* block = skin->mpBlocks[i];
                accum.Export(helper, block, skin->mUVRects[i], (short)bones[i].mNodeIndex, false);
            }
        }
        helper.ExportMeshEnd();
        helper.ExportSkeleton();
        C461400 holder;
        holder.Ctor();
        SP::EditorUtils::CreateExportCreatureModel(skin, path.mpBegin, &holder, &helper, true);
        SP::EditorUtils::ExportCreatureBlocksFile(path.mpBegin, &holder);
        holder.Dtor();
    }
}

namespace {

void cBlockGeometryExporter::Export(nSPSkinner::cExportHelper& helper, void* block,
                                    EA::RectT<float>& uvRect, unsigned int id, bool flag)
{
}

}  // namespace
