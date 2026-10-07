// Slice s0046c900: SP::EditorUtils::CreateExportCreatureModel (PDB candidate, caller-scored;
// parameter names from the dev PDB: pSkin, modelpath, pExportModel, helper, ignorePartModels).
// Builds the export description of a creature: one ExportJoint (0x29c bytes) per skin block, with
// file name, joint name ("joint_b%d_n%d", or the helper's node/bone names), positions, rotation,
// bone frames, part attachments, the block's model and three hashed properties.
// Editor /Od region: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the string locals have no
// EH frame). Byte-exact. The frame layout depends on: the local names (slot order is a hash bucket
// of the name, ties broken by reverse declaration; the dev-PDB names fit), the inline callees cl
// declines (resize, GetBlockRotation, DeallocateSelf, cMWModel::Release reserve their frames as
// holes), and the result types of the math helpers (a converting/derived result type forces the
// temporary + copy the original has).
#include "types.h"

// ---------------------------------------------------------------------------------------------
// Math
// Value type returned by the out-of-line math helpers; Vector3 converts from it (so the
// results land in a temporary and are copied, as in the original).
struct Vec3f {
    float x, y, z;
    Vec3f(const Vec3f& o) : x(o.x), y(o.y), z(o.z) {}
};

struct Vector3 {
    float x, y, z;
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3(const Vec3f& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vec3f& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Quaternion { float x, y, z, w; };
// Non-POD result type of GetBlockRotation (returned in a temporary, then sliced into a Quaternion).
struct QuatResult : Quaternion {
    QuatResult(const Quaternion& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};
struct Matrix33 { float m[9]; };
namespace rw { namespace math { namespace fpu {
    Quaternion& QuaternionFromMatrix33(Quaternion& out, const Matrix33& m, float tolerance);   // 0x00472b80
}}}

Vec3f operator+(const Vector3& a, const Vector3& b);           // 0x0041dc10
Vec3f operator*(const float& s, const Vec3f& v);               // 0x0041de40
Vec3f RotateVector(const Vector3& v, const Vector3& frame);     // 0x0041dca0

extern const Vector3 kZeroVector;                              // 0x015d4034

// ---------------------------------------------------------------------------------------------
// EASTL string16 (16 bytes) with the inline parts this function expands.
extern wchar_t gEmptyString16;                                 // 0x01667bac

void operator delete[](void* p);

struct allocator {
    void deallocate(void* p, uint32_t) { delete[] (char*)p; }
};

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator mAllocator;

    string16() : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(); }
    ~string16() { DeallocateSelf(); }
    void AllocateSelf() { mpBegin = &gEmptyString16; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    // 0x004237d0 (cl declines to inline it here)
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(wchar_t* p, uint32_t n)
    {
        if (p)
            mAllocator.deallocate(p, n * sizeof(wchar_t));
    }
    void reserve(uint32_t n);                                  // 0x0042e610
    string16& assign(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x00423650
    string16& assign(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
    const wchar_t* c_str() const { return mpBegin; }
    static uint32_t CharStrlen(const wchar_t* pString)
    {
        const wchar_t* pCurrent = pString;
        while (*pCurrent)
            ++pCurrent;
        return (uint32_t)(pCurrent - pString);
    }
};

namespace EA { namespace StdC {
    wchar_t* Strncpy(wchar_t* pDest, const wchar_t* pSource, uint32_t n);   // 0x0092cb90
}}
int Snprintf8(char* pBuffer, uint32_t n, const char* pFormat, ...);       // 0x009384e0

// ---------------------------------------------------------------------------------------------
// Skin data
template <int N> struct Bitset {
    uint32_t mWord[(N + 31) / 32];
    uint32_t GetWord(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const
    {
        if (i < N)
            return (GetWord(i) & (1 << (i % 32))) != 0;
        return false;
    }
};

struct SkinBone {                       // 0x8c bytes
    int16_t mBlockIndex;                // +0x00
    int16_t mNodeIndex;                 // +0x02
    int16_t mParent;                    // +0x04
    int16_t mSymmetric;                 // +0x06
    uint16_t mFlags;                    // +0x08
    uint8_t mPartIndex;                 // +0x0a
    uint8_t mType;                      // +0x0b
    uint32_t pad0c[2];
    Vector3 mStart;                     // +0x14
    Vector3 mEnd;                       // +0x20
    Vector3 mFrame;                     // +0x2c (its x is also exported as a float)
    uint32_t pad38[(0x60 - 0x38) / 4];
    Vector3 mOffset;                    // +0x60
    float mRadius;                      // +0x6c
    uint32_t pad70[(0x8c - 0x70) / 4];
};

struct SkinBoneVector {
    SkinBone* mpBegin;
    SkinBone* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct SkinData {
    uint32_t pad0[0x98 / 4];
    SkinBoneVector mBones;              // +0x98
};

struct ResourceKey { uint32_t instance, type, group; };
struct BlockResource { uint32_t pad0[2]; ResourceKey mKey; };   // key at +0x08

class cMWModel;
class cModelWorld {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc();
    virtual void v0c0(); virtual void v0c4(); virtual void v0c8(); virtual void v0cc();
    virtual void v0d0(); virtual void v0d4(); virtual void v0d8(); virtual void v0dc();
    virtual void v0e0(); virtual void v0e4(); virtual void v0e8(); virtual void v0ec();
    virtual void v0f0(); virtual void v0f4(); virtual void v0f8(); virtual void v0fc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168(); virtual void v16c();
    virtual void ReleaseModel(cMWModel* pModel, bool flag);     // +0x170
};

// 0x0040f360 Counted::Release (cl declines to inline it here)
class cMWModel {
public:
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        if (mnRefCount > 1)
            return --mnRefCount;
        mpWorld->ReleaseModel(this, mFlags.test(31));
        return 0;
    }
    cModelWorld* mpWorld;               // +0x00
    Bitset<32> mFlags;                  // +0x04
    uint32_t pad08[(0x40 - 0x08) / 4];
    int mnRefCount;                     // +0x40
};

namespace EA {
template <class T> class AutoRefCount {
public:
    T* mpObject;
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
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
};
}

struct BlockAttachment {                // 0x14 bytes
    uint32_t mPart;
    uint32_t pad04[2];
    uint32_t mSlot;                     // +0x0c
    uint32_t pad10;
    uint32_t GetPart() const { return mPart; }
    uint32_t GetSlot() const { return mSlot; }
};

struct BlockAttachmentVector {
    BlockAttachment* mpBegin;
    BlockAttachment* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct PartModel {
    uint32_t pad0[0x8c / 4];
    uint32_t mModelID;                  // +0x8c
    uint32_t pad90[(0x180 - 0x90) / 4];
    float mScale;                       // +0x180
};

class cBlock {
public:
    int GetPartModelCount();                    // 0x0043c040
    PartModel* GetPartModel(int index);         // 0x0043c270
    uint32_t GetPropertyValue(uint32_t id);     // 0x00435c20

    BlockResource* GetResource() { return mpResource; }
    cMWModel* GetModel() { return mpModel.mpObject; }
    uint32_t GetModelIDA() { return mIDA; }
    uint32_t GetModelIDB() { return mIDB; }
    cBlock* GetParent() { return mpParent; }

    uint32_t pad0[3];
    BlockResource* mpResource;          // +0x0c
    EA::AutoRefCount<cMWModel> mpModel; // +0x10
    uint32_t pad14[2];
    uint32_t mIDA;                      // +0x1c
    uint32_t mIDB;                      // +0x20
    uint32_t pad24[(0x48 - 0x24) / 4];
    Vector3 mPosition;                  // +0x48
    uint32_t pad54[(0x60 - 0x54) / 4];
    Matrix33 mOrientation;              // +0x60
    uint32_t pad84[(0x33c - 0x84) / 4];
    cBlock* mpParent;                   // +0x33c
    uint32_t pad340[(0xc0c - 0x340) / 4];
    BlockAttachmentVector mAttachments; // +0xc0c
    uint32_t padc14[(0xdb4 - 0xc14) / 4];
    uint32_t mPropertyA;                // +0xdb4
    uint32_t mPropertyB;                // +0xdb8
    uint32_t mPropertyC;                // +0xdbc
    uint32_t paddc0[2];
    Bitset<60> mFlags;                  // +0xdc8
};

// 0x0046d660 (emitted out of line in this module; cl declines to inline it here)
inline QuatResult GetBlockRotation(const Matrix33& m)
{
    Quaternion q;
    return QuatResult(rw::math::fpu::QuaternionFromMatrix33(q, m, 0.0f));
}
uint32_t GetPartID(uint32_t part);                  // 0x00461520

struct cSkin {
    SkinData* GetSkinData() { return mpSkinData; }
    uint32_t pad0[2];
    SkinData* mpSkinData;               // +0x08
    uint32_t pad0c[(0xc0 - 0x0c) / 4];
    cBlock** mpBlocks;                  // +0xc0
};

// ---------------------------------------------------------------------------------------------
// Skeleton helper
struct IntVector {
    int* mpBegin;
    int* mpEnd;
    int& operator[](int i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct HelperNodeGroup {                // 0x48 bytes
    uint32_t pad0[3];
    IntVector mBlocks;                  // +0x0c
    uint32_t pad14[(0x44 - 0x14) / 4];
    int mNode;                          // +0x44
};

struct HelperBone {                     // 0x54 bytes
    uint32_t pad0[0x38 / 4];
    Vector3 mPosition;                  // +0x38
    bool mbConnected;                   // +0x44
    uint8_t pad45[3];
    uint32_t pad48[3];
};

struct HelperNode {                     // 0xd8 bytes
    uint32_t pad0[2];
    int mBone;                          // +0x08
    int mType;                          // +0x0c
    uint32_t pad10[(0xd8 - 0x10) / 4];
};

struct SkeletonHelper {
    HelperNodeGroup& GetGroup(int i) { return mpGroups[i]; }
    uint32_t pad0[4];
    HelperNodeGroup* mpGroups;          // +0x10
    uint32_t pad14[4];
    HelperBone* mpBones;                // +0x24
    uint32_t pad28[4];
    int mRootGroup;                     // +0x38
    uint32_t pad3c[6];
    HelperNode* mpNodes;                // +0x54
};

Vec3f TransformToGroup(const HelperNodeGroup& group, const Vector3& pos);   // 0x0041db10

// ---------------------------------------------------------------------------------------------
// Export model
struct ExportPart { uint32_t mPart; uint32_t mSlot; };
struct ExportPartModel { uint32_t mModelID; float mScale; };

class IExportMesh {
public:
    virtual void AddRef();
    virtual void Release();
};

class IExportFactory {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual IExportMesh* CreateMesh();          // +0x60
};
IExportFactory* GetExportFactory();             // 0x00401010

template <class T> struct MeshPtr {
    T* mpObject;
    T* get() const { return mpObject; }
    MeshPtr& operator=(T* pObject)
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
};

struct ExportJoint {                    // 0x29c bytes
    ExportJoint();                      // 0x00475880
    int mVersion;                       // +0x000
    wchar_t mFileName[0x50];            // +0x004
    char mJointName[0x28];              // +0x0a4
    uint32_t mModelIDB;                 // +0x0cc
    uint32_t mModelIDA;                 // +0x0d0
    int mBlockIndex;                    // +0x0d4
    int mParent;                        // +0x0d8
    int mSymmetric;                     // +0x0dc
    Vector3 mCenter;                    // +0x0e0
    int mPartIndex;                     // +0x0ec
    Vector3 mBonePosition;              // +0x0f0
    Vector3 mOffset;                    // +0x0fc
    Vector3 mPosition;                  // +0x108
    Quaternion mOrientation;            // +0x114
    Vector3 mStart;                     // +0x124
    Vector3 mEnd;                       // +0x130
    float mFrameX;                      // +0x13c
    float mRadius;                      // +0x140
    uint32_t mProperties[3];            // +0x144
    int mNumParts;                      // +0x150
    int mNumPartModels;                 // +0x154
    ExportPart mParts[32];              // +0x158
    ExportPartModel mPartModels[8];     // +0x258
    EA::AutoRefCount<cMWModel> mpModel; // +0x298
};

struct ExportJointVector {
    ExportJoint* mpBegin;
    ExportJoint* mpEnd;
    ExportJoint* mpCapacity;
    uint32_t mAllocator;
    ExportJoint& operator[](int i) { return mpBegin[i]; }
    void erase(ExportJoint* first, ExportJoint* last);     // 0x00475da0
    void clear() { erase(mpBegin, mpEnd); }
    // 0x00473370 (cl declines to inline it here)
    void resize(uint32_t n)
    {
        if (n > (uint32_t)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), ExportJoint());
        else
            erase(mpBegin + n, mpEnd);
    }
    void insert(ExportJoint* position, uint32_t n, const ExportJoint& value) { DoInsertValues(position, n, value); }
    void DoInsertValues(ExportJoint* position, uint32_t n, const ExportJoint& value);   // 0x00478e00
};

struct ExportModel {
    int mVersion;                       // +0x00
    string16 mModelPath;                // +0x04
    uint32_t pad14[3];
    bool mbRootFirst;                   // +0x20
    uint8_t pad21[3];
    int mRootIndex;                     // +0x24
    ExportJointVector mJoints;          // +0x28
    uint32_t pad38[2];
    MeshPtr<IExportMesh> mpMesh;        // +0x40
};

namespace EA { namespace ResourceMan {
    class IResourceManager {
    public:
        virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
        virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
        virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
        virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
        virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
        virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
        virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
        virtual void v70(); virtual void v74(); virtual void v78();
        virtual bool GetFileName(const ResourceKey& key, string16& name);   // +0x7c
    };
    IResourceManager* GetManager();     // 0x0067dcd0
}}

namespace SP { namespace EditorUtils {

// @ 0x0046c900
void CreateExportCreatureModel(cSkin* pSkin, const wchar_t* modelpath, ExportModel* pExportModel,
                               SkeletonHelper* helper, bool ignorePartModels)
{
    string16 tempString;
    tempString.reserve(0x100);

    SkinBone* blocks = pSkin->GetSkinData()->mBones.mpBegin;
    int numBlocks = pSkin->GetSkinData()->mBones.size();
    cBlock** pBlocks = pSkin->mpBlocks;
    ExportModel* pModel = pExportModel;

    pModel->mVersion = 5;
    pModel->mModelPath.assign(modelpath);
    pModel->mJoints.clear();
    if (!pModel->mpMesh.get())
        pModel->mpMesh = GetExportFactory()->CreateMesh();
    pModel->mbRootFirst = false;
    pModel->mRootIndex = 0;

    int idxPlantRoot = -1;
    if (numBlocks > 0 && blocks[0].mParent != -1) {
        idxPlantRoot = blocks[0].mParent;
        if ((uint32_t)idxPlantRoot >= (uint32_t)numBlocks || blocks[idxPlantRoot].mType != 4)
            idxPlantRoot = -1;
        else
            pModel->mRootIndex = idxPlantRoot;
    }

    if (helper) {
        int rootGroup = helper->mRootGroup;
        pModel->mRootIndex = helper->GetGroup(rootGroup).mBlocks[0];
        for (int ii = 0, numInGroup = helper->GetGroup(rootGroup).mBlocks.size(); ii < numInGroup; ++ii) {
            int index = helper->GetGroup(rootGroup).mBlocks[ii];
            if (index < numBlocks && pBlocks[index]->mFlags.test(7)) {
                pModel->mRootIndex = index;
                break;
            }
        }
    }

    pModel->mJoints.resize(numBlocks);
    for (int i = 0; i < numBlocks; ++i) {
        ExportJoint* joint = &pModel->mJoints.mpBegin[i];
        joint->mVersion = 5;

        int blockindex = i;
        if (idxPlantRoot != -1) {
            if (i == 0) {
                blockindex = idxPlantRoot;
                pModel->mbRootFirst = true;
            } else if (i <= idxPlantRoot) {
                blockindex = i - 1;
            }
        }

        cBlock* pBlock = pBlocks[blockindex];
        SkinBone* pBlockData = &pSkin->GetSkinData()->mBones.mpBegin[blockindex];

        string16 resName;
        EA::ResourceMan::GetManager()->GetFileName(pBlock->GetResource()->mKey, resName);
        EA::StdC::Strncpy(joint->mFileName, resName.mpBegin, 0x50);

        joint->mModelIDA = pBlock->GetModelIDA();
        joint->mModelIDB = pBlock->GetModelIDB();
        joint->mBlockIndex = pBlockData->mBlockIndex;
        joint->mParent = pBlockData->mParent;
        if (pBlockData->mFlags & 0x1000)
            joint->mSymmetric = -1;
        else
            joint->mSymmetric = pBlockData->mSymmetric;
        joint->mPartIndex = pBlockData->mPartIndex == 0 ? -1 : pBlockData->mPartIndex;

        if (pBlock->mFlags.test(7) && pBlock->GetParent() != 0)
            joint->mCenter = 0.5f * (pBlock->mPosition + pBlock->GetParent()->mPosition);
        else
            joint->mCenter = pBlock->mPosition;

        Snprintf8(joint->mJointName, 0x28, "joint_b%d_n%d", pBlockData->mBlockIndex, pBlockData->mNodeIndex);
        joint->mBonePosition = kZeroVector;
        joint->mOffset = pBlockData->mOffset;

        if (helper) {
            if (joint->mPartIndex == -1) {
                Snprintf8(joint->mJointName, 0x28, "joint_bone_%d", blockindex);
                joint->mBonePosition = helper->mpBones[blockindex].mPosition;
            } else {
                int nodeIndex = pBlockData->mNodeIndex;
                int nodeIdx = helper->mpGroups[nodeIndex].mNode;
                HelperNode* pN = &helper->mpNodes[nodeIdx];
                switch (pN->mType) {
                case 3:
                    Snprintf8(joint->mJointName, 0x28, "joint_eenode_%d", nodeIndex);
                    break;
                case 2:
                    Snprintf8(joint->mJointName, 0x28, "joint_fakenode_%d", nodeIndex);
                    break;
                case 0:
                    Snprintf8(joint->mJointName, 0x28, "joint_rootnode_%d", nodeIndex);
                    break;
                case 1:
                    if (!helper->mpBones[pN->mBone].mbConnected)
                        Snprintf8(joint->mJointName, 0x28, "joint_bone_%d", pN->mBone);
                    else
                        Snprintf8(joint->mJointName, 0x28, "joint_connbone_%d", pN->mBone);
                    break;
                }
                Vector3 np = TransformToGroup(helper->GetGroup(nodeIndex), pBlock->mPosition);
                joint->mBonePosition = np;
            }
        }

        Vector3 p = pBlock->mPosition;
        joint->mPosition = p;
        Quaternion ori = GetBlockRotation(pBlock->mOrientation);
        joint->mOrientation = ori;
        Vector3 mn = RotateVector(pBlockData->mStart, pBlockData->mFrame);
        Vector3 mx = RotateVector(pBlockData->mEnd, pBlockData->mFrame);
        joint->mStart = mn;
        joint->mEnd = mx;
        joint->mFrameX = pBlockData->mFrame.x;
        joint->mRadius = pBlockData->mRadius;

        joint->mNumParts = pBlock->mAttachments.size();
        for (int k = 0; k < joint->mNumParts; ++k) {
            joint->mParts[k].mPart = GetPartID(pBlock->mAttachments.mpBegin[k].GetPart());
            joint->mParts[k].mSlot = pBlock->mAttachments.mpBegin[k].GetSlot();
        }

        joint->mNumPartModels = 0;
        if (!ignorePartModels && joint->mPartIndex != -1) {
            joint->mNumPartModels = pBlock->GetPartModelCount();
            for (int m = 0; m < joint->mNumPartModels; ++m) {
                PartModel* pPart = pBlock->GetPartModel(m);
                if (pPart) {
                    joint->mPartModels[m].mModelID = pPart->mModelID;
                    joint->mPartModels[m].mScale = pPart->mScale;
                }
            }
            joint->mpModel = pBlock->GetModel();
        }
        {
            int unused;   // an unused local of the original: it only reserves a stack slot at /Od
        }

        joint->mProperties[0] = pBlock->GetPropertyValue(0xdd94fb65);
        joint->mProperties[1] = pBlock->GetPropertyValue(0x0e40c402);
        joint->mProperties[2] = pBlock->GetPropertyValue(0x2dc2a89d);
    }
}

}}  // namespace SP::EditorUtils
