// Slice s004ca6e0: SP::cSkinObject::BuildSkeleton (retail, 3153 bytes; dev PDB 2016 bytes).
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (editor /Od region, no /EHsc).
//
// Rebuilds the skin object's skeleton from the creature resource's block array
// (cRuntimeCreatureBlock, retail stride 0x8c):
//   - counts the leading spine blocks (type 5) and the limb blocks (type 3) that follow,
//     and the number of extra bones needed for limb blocks flagged 2;
//   - resizes mNodes (+0x40, pair<cSPVector3, fixed_vector<uint,4>>), mBones (+0x54,
//     pair<uint,uint>) and mBoneTransforms (+0x68, cSPTransform);
//   - maps node index -> block index, places every node (spine nodes between two spine
//     blocks at the midpoint, the root of a limb block offset by its joint length along
//     the block rotation);
//   - fills bone (parent node, child node) pairs and bone transforms (rotation +
//     translation of the block) for spine, limb and remaining blocks, plus the extra
//     bones of flagged limb blocks;
//   - records each bone index in the bone lists of both of its nodes.
#include "types.h"

#pragma pack(push, 4)

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};

struct cSPMatrix3 {
    float m[3][3];
};

cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b);              // 0x0041DC10
cSPVector3 operator*(const cSPVector3& v, const float& s);                   // 0x0041DCA0
cSPVector3 RotateVector(const cSPVector3& v, const cSPMatrix3& m);           // 0x0041DAF0
cSPVector3& operator+=(cSPVector3& a, const cSPVector3& b);                  // 0x0041DDB0

static inline void AssignVector(cSPVector3* pDst, const cSPVector3& src)
{
    pDst->x = src.x;
    pDst->y = src.y;
    pDst->z = src.z;
}

struct cSPTransform {  // size 0x38
    unsigned short mFlags;              // +0x0
    unsigned short mModificationCount;  // +0x2
    cSPVector3 mTranslation;            // +0x4
    float mScale;                       // +0x10
    cSPMatrix3 mRotation;               // +0x14

    void SetRotation(const cSPMatrix3& m)
    {
        mRotation = m;
        mFlags |= 2;
        mModificationCount++;
    }
    void SetTranslation(const cSPVector3& v)
    {
        mTranslation = v;
        mFlags |= 4;
        mModificationCount++;
    }
};

// eastl::fixed_vector<int, 64> (buffer at +0x18), out-of-line ctor / base dtor.
struct IndexMap {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    uint32_t mAllocator[3];
    int mBuffer[64];

    IndexMap(int n, int value);         // 0x00422740
    void DestroyBase();                 // 0x004C0B80 (VectorBase dtor)
    ~IndexMap()
    {
        for (int* p = mpBegin; p < mpEnd; ++p) {
        }
        DestroyBase();
    }
};

struct BoneIndexList {  // eastl::fixed_vector<unsigned int, 4>
    void push_back(const int& value);   // 0x00422380
    uint32_t mData[10];
};

struct SkinNode {  // pair<cSPVector3, fixed_vector<uint,4>>, 0x34 bytes
    cSPVector3 mPosition;               // +0x0
    BoneIndexList mBoneIndices;         // +0xc
};

struct SkinBone {  // pair<uint,uint>
    int mParentNode;
    int mChildNode;
};

struct NodeVector {
    SkinNode* mpBegin; SkinNode* mpEnd; SkinNode* mpCapacity; uint32_t mAlloc;
    void erase(SkinNode* first, SkinNode* last);        // 0x004CE110
    void resize(int n);                                 // 0x004CD5B0
    void clear() { erase(mpBegin, mpEnd); }
    SkinNode* begin() { return mpBegin; }
};
struct BoneVector {
    SkinBone* mpBegin; SkinBone* mpEnd; SkinBone* mpCapacity; uint32_t mAlloc;
    void erase(SkinBone* first, SkinBone* last);        // 0x00530C80
    void resize(int n);                                 // 0x004CD440
    void clear() { erase(mpBegin, mpEnd); }
    SkinBone* begin() { return mpBegin; }
};
struct TransformVector {
    cSPTransform* mpBegin; cSPTransform* mpEnd; cSPTransform* mpCapacity; uint32_t mAlloc;
    void erase(cSPTransform* first, cSPTransform* last); // 0x004238C0
    void resize(int n);                                  // 0x0041E3B0
    void clear() { erase(mpBegin, mpEnd); }
    cSPTransform* begin() { return mpBegin; }
};
struct RectVector {
    void* mpBegin; void* mpEnd; void* mpCapacity; uint32_t mAlloc;
    void erase(void* first, void* last);                 // 0x00455AE0
    void clear() { erase(mpBegin, mpEnd); }
};

struct cRuntimeCreatureBlock {  // retail size 0x8c
    short mBlockIndex;          // +0x0
    short mNodeIndex;           // +0x2
    short mParentIndex;         // +0x4
    short mSymmetricIndex;      // +0x6
    unsigned short mFlags;      // +0x8
    unsigned char mSubmeshId;   // +0xa
    unsigned char mBlockType;   // +0xb
    uint32_t pad0c[(0x30 - 0x0c) / 4];
    cSPMatrix3 mRotation;       // +0x30
    cSPVector3 mTranslation;    // +0x54
    uint32_t pad60[(0x70 - 0x60) / 4];
    float mJointLength;         // +0x70
    uint32_t pad74[(0x8c - 0x74) / 4];
};

struct BlockVector {
    cRuntimeCreatureBlock* mpBegin; cRuntimeCreatureBlock* mpEnd; cRuntimeCreatureBlock* mpCapacity; uint32_t mAlloc;
    int size() { return (int)(mpEnd - mpBegin); }
};

struct cRuntimeCreatureResource {
    uint32_t pad00[0x98 / 4];
    BlockVector mBlocks;        // +0x98 (retail)
};

namespace SP {

class cSkinObject {
public:
    uint32_t pad00[2];
    cRuntimeCreatureResource* mResource;    // +0x08
    uint32_t pad0c[(0x40 - 0x0c) / 4];
    NodeVector mNodes;                      // +0x40
    uint32_t pad50;
    BoneVector mBones;                      // +0x54
    uint32_t pad64;
    TransformVector mBoneTransforms;        // +0x68
    uint32_t pad78;
    RectVector mTextureSubRects;            // +0x7c

    cRuntimeCreatureResource* GetResource() { return mResource; }
    bool BuildSkeleton();
};

}  // namespace SP

#pragma pack(pop)

using namespace SP;

// @ 0x004CA6E0
bool cSkinObject::BuildSkeleton()
{
    cSkinObject* self = this;
    cRuntimeCreatureBlock* blocks = self->GetResource()->mBlocks.mpBegin;
    int nBlocks = self->GetResource()->mBlocks.size();
    self->mTextureSubRects.clear();
    if (nBlocks == 0)
        return false;

    int i;
    for (i = 0; i < nBlocks && blocks[i].mBlockType == 5; i++) {
    }
    int nSpine = i;
    int nExtraBones = 0;
    if (nSpine > 0) {
        for (; i < nBlocks && blocks[i].mBlockType == 3; i++) {
            if (blocks[i].mFlags & 2)
                nExtraBones++;
        }
    } else {
        for (; i < nBlocks && blocks[i].mBlockType == 3; i++) {
        }
    }
    int limbEnd = i;
    int nRemaining = nBlocks - i;
    int firstType4 = -1;
    if (i < nBlocks && blocks[i].mBlockType == 4)
        firstType4 = i;

    int nNodes = blocks[nBlocks - 1].mNodeIndex + 1;
    int nBones = nBlocks + nExtraBones;
    self->mNodes.clear();
    self->mBones.clear();
    self->mBoneTransforms.clear();
    self->mNodes.resize(nNodes);
    self->mBones.resize(nBones);
    self->mBoneTransforms.resize(nBones);
    SkinNode* nodes = self->mNodes.begin();
    SkinBone* bones = self->mBones.begin();
    cSPTransform* transforms = self->mBoneTransforms.begin();

    IndexMap nodeBlocks(nNodes, -1);
    for (i = 0; i < nBlocks; i++) {
        if (blocks[i].mFlags & 2)
            nodeBlocks.mpBegin[blocks[i].mNodeIndex - 1] = i;
        nodeBlocks.mpBegin[blocks[i].mNodeIndex] = i;
    }

    for (i = 0; i < nNodes; i++) {
        cRuntimeCreatureBlock* pBlock = &blocks[nodeBlocks.mpBegin[i]];
        if (pBlock->mBlockType == 5) {
            if (i == 0 || i == nSpine) {
                nodes[i].mPosition = pBlock->mTranslation;
            } else {
                cRuntimeCreatureBlock* pNext = &blocks[nodeBlocks.mpBegin[i] + 1];
                AssignVector(&nodes[i].mPosition, (pBlock->mTranslation + pNext->mTranslation) * 0.5f);
            }
        } else if (pBlock->mBlockType == 3) {
            if (i == pBlock->mNodeIndex) {
                cSPVector3 pos(0.0f, -pBlock->mJointLength, 0.0f);
                pos = RotateVector(pos, pBlock->mRotation);
                pos += pBlock->mTranslation;
                nodes[i].mPosition = pos;
            } else {
                nodes[i].mPosition = pBlock->mTranslation;
            }
        } else {
            nodes[i].mPosition = pBlock->mTranslation;
        }
    }

    i = 0;
    if (nSpine != 0) {
        for (i = 0; i < nSpine; i++) {
            bones[i].mParentNode = i;
            bones[i].mChildNode = i + 1;
            transforms[i].SetRotation(blocks[i].mRotation);
            transforms[i].SetTranslation(blocks[i].mTranslation);
        }
    }
    for (; i < nBlocks && blocks[i].mBlockType == 3; i++) {
        if (blocks[i].mFlags & 2)
            bones[i].mParentNode = blocks[i].mNodeIndex - 1;
        else
            bones[i].mParentNode = blocks[blocks[i].mParentIndex].mNodeIndex;
        bones[i].mChildNode = blocks[i].mNodeIndex;
        transforms[i].SetRotation(blocks[i].mRotation);
        transforms[i].SetTranslation(blocks[i].mTranslation);
    }
    for (; i < nBlocks; i++) {
        if (nSpine != 0) {
            if (blocks[i].mParentIndex < nSpine / 2)
                bones[i].mParentNode = bones[blocks[i].mParentIndex].mParentNode;
            else
                bones[i].mParentNode = bones[blocks[i].mParentIndex].mChildNode;
        } else if (blocks[i].mFlags & 2) {
            bones[i].mParentNode = blocks[i].mNodeIndex - 1;
        } else {
            bones[i].mParentNode = blocks[blocks[i].mParentIndex].mNodeIndex;
        }
        bones[i].mChildNode = blocks[i].mNodeIndex;
        transforms[i].SetRotation(blocks[i].mRotation);
        transforms[i].SetTranslation(blocks[i].mTranslation);
    }

    int nExtra = 0;
    if (nSpine > 0) {
        for (i = nSpine; i < limbEnd; i++) {
            if (blocks[i].mFlags & 2) {
                int bone = nBlocks + nExtra;
                bones[bone].mParentNode = bones[blocks[i].mParentIndex].mChildNode;
                bones[bone].mChildNode = blocks[i].mNodeIndex - 1;
                transforms[bone].SetRotation(blocks[blocks[i].mParentIndex].mRotation);
                transforms[bone].SetTranslation(blocks[blocks[i].mParentIndex].mTranslation);
                nExtra++;
            }
        }
    }

    for (i = 0; i < nBones; i++) {
        int boneIndex = i;
        nodes[bones[i].mParentNode].mBoneIndices.push_back(boneIndex);
        int boneIndex2 = i;
        nodes[bones[i].mChildNode].mBoneIndices.push_back(boneIndex2);
    }
    (void)nRemaining;
    (void)firstType4;
    return true;
}
