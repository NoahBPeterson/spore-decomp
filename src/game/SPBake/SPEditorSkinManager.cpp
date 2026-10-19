// src/game/SPBake/SPEditorSkinManager.cpp -- migrated from slice(s) s005002d0, s004c38e0, s004c3230, s004c2100 by tools/migrate/rewrite.py
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
namespace SP {
class cSPEditorSkinPartView {
public:
    char pad[0xe0];
    void* mSceneObject;                 // +0xe0
    void* GetSceneObject() { return mSceneObject; }
};
}
namespace SP {
class cSPEditorSkinManager_s004c_38e0 {
public:
    char pad0[0x10];
    void* mModel;                        // +0x10 (asm: cmp [this+0x10],0 in Update)
    void* mSceneObjectModelWorld;        // +0x14 (asm: pushed as 2nd arg of 0x4cc7d0)
    cSPEditorSkinPartView* mTorsoSkin;   // +0x18
    cSPEditorSkinPartView* mCompleteSkin; // +0x1c
    char pad20[0x7c - 0x20];

    void* GetSceneObjectById(uint32_t which);
    void Update(uint32_t p2, char p3, uint32_t p4, uint32_t p5);  // 0x004c38e0 (SP::cSPEditorSkinManager::Update)
    void UpdateTorso(uint32_t a, uint32_t b);  // 0x004c3230 (SP::cSPEditorSkinManager::UpdateTorso)
    void UpdatePaintedSkin(uint32_t a, uint32_t b, uint32_t c);  // 0x004c4290 (SP::cSPEditorSkinManager::UpdatePaintedSkin)
    void UpdatePaintedSkin();            // 0x4c4290 is called with no stack args (asm), see Update
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
void cSPEditorSkinManager_s004c_38e0::Update(uint32_t p2, char p3, uint32_t p4, uint32_t p5)
{
    (void)p2; (void)p3;
    UpdateTorso(p4, p5);
    if (mModel != 0) {
        // PARTIAL: see the note above.
    }
    UpdatePaintedSkin();
}
}  // namespace SP

// @ 0x004c4290
namespace SP {
void cSPEditorSkinManager_UpdatePaintedSkin(void* self, uint32_t a, uint32_t b, uint32_t c)
{
    (void)self; (void)a; (void)b; (void)c;
}
}  // namespace SP

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
