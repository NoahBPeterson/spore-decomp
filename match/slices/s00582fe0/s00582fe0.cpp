// slice s00582fe0 -- SP::cAppModeEditorBase::RunSkinPaintOnEditorModel (0x00582fe0, 2323 bytes)
// plus a skeleton stub for 0x00583900.
// Spawns (or adopts) an animated creature that shows the paint-skin of the editor model and
// puts it into its start pose. kind 0 = torso creature, 1 = one of the "limb" records in the
// vector at +0x36c (an entourage that walks around the torso), 2 = the painter's creature.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (same module as s0057f6c0).
// Names for the helper methods are coined here (no PDB names for them).
#include "types.h"

void* operator new(unsigned int size, void* p) throw() { return p; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// Matrix3 (rows), out-of-line copy constructor at 0x0041cb40
struct Matrix3 {
    Vector3 row[3];
    Matrix3(const Matrix3& m);                                   // 0x0041cb40
};

extern const Vector3 kVecDefault;                                // 0x015e4f18
extern const Vector3 kAxisUp;                                    // 0x015e5024
extern const float kAngleScale;                                  // 0x015e50a0
extern const Vector3 kApproachDir;                               // 0x015e50a4
extern const float kCreatureSpeed;                               // 0x015e4f9c

extern const Matrix3 kIdentityBasis;                             // 0x015e505c (cSPTransform rotation default)
extern const float kOne;                                         // 0x01485720 (_HK_REAL_ONE)
extern const float kHalf;                                        // 0x01471064
extern const float kThreeTenths;                                 // 0x013eb8c8
extern float g_defaultFloat;                                     // 0x015d1168 (Property default)

// cdecl helpers
float RandomFloatRange(float lo, float hi);                      // 0x00572a10
float RandomFloat(float range);                                  // 0x00572a60
Matrix3 MakeRotation(const Vector3& axis, float angle);          // 0x00453b20
float SignedAngle(const Vector3& a, const Vector3& b, const Vector3& axis, bool c);  // 0x0069b760
Vector3 GetModelCenter(struct cSPEditorModel* pModel);           // 0x0046bfd0
bool FUN_004a0ac0(struct cSPEditorModel* pModel);                // 0x004a0ac0

struct cSPEditorModel {
    uint32_t pad00[0x10 / 4];
    uint32_t mTypeID;                                            // +0x10
    uint32_t pad14[(0x58 - 0x14) / 4];
    uint32_t mModelType;                                         // +0x58
};

struct cSkinUpdateFlags {
    bool mbA;
    bool mbB;
    cSkinUpdateFlags() : mbA(false), mbB(false) {}
};

struct cSkinMesh {
    uint32_t pad0[2];
    char* mpBegin;                                               // +0x08 (12-byte entries)
    char* mpEnd;                                                 // +0x0c
};

struct cSkinObject {
    uint32_t pad0[0x34 / 4];
    cSkinMesh* mpMesh;                                           // +0x34
    uint32_t pad38[(0x7c - 0x38) / 4];
    char* mpVertsBegin;                                          // +0x7c (20-byte entries)
    char* mpVertsEnd;                                            // +0x80
    void BuildSkeleton();                                        // 0x004ca6e0
    void FUN_004cb340();                                         // 0x004cb340
    void FUN_004cb820();                                         // 0x004cb820
    __forceinline bool IsMeshValid()
    {
        return mpMesh && (mpMesh->mpEnd - mpMesh->mpBegin) / 12 == (mpVertsEnd - mpVertsBegin) / 20;
    }
};

// Shared base of the skin manager (+0x150) and the painter (+0x154).
struct cSkinHolder {
    cSkinObject* GetSkin(int index);                             // 0x004c49e0
    bool IsSkinUpToDate();                                       // 0x004c4630
    void Update(int a, int b, cSkinUpdateFlags flags, int c);    // 0x004c38e0
};

struct cCreatureStructure {
    void FUN_0059b390();                                         // 0x0059b390
};

// ---- GIF capture support -------------------------------------------------
// 0x0067ddb0 returns the thumbnail/capture service; the grid of creature boxes goes to its
// virtual slot +0x50 together with the viewer, the box centre and the box shrink factor.
struct cViewer;                                                  // 0x7c3f70 (xform accessors only)

void EASTL_allocator_deallocate(void* p);                        // 0x00f47380

struct Box24 {                                                   // 24-byte box: two Vector3
    Vector3 mMin;
    Vector3 mMax;
};

struct cSPTransform {                                            // the viewer's basis
    uint16_t mFlags;                                             // +0x00
    uint16_t mModificationCount;                                 // +0x02
    Vector3 mTranslation;                                        // +0x04
    float mScale;                                                // +0x10
    Matrix3 mRotation;                                           // +0x14
    cSPTransform()
        : mFlags(0), mModificationCount(0), mTranslation(kVecDefault), mScale(kOne),
          mRotation(kIdentityBasis) {}
};

struct BoxVector {                                               // EASTL vector<Box24>
    Box24* mpBegin;                                              // +0x00
    Box24* mpEnd;                                                // +0x04
    Box24* mpCapacity;                                           // +0x08
    uint32_t mAllocator;                                         // +0x0c
    BoxVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~BoxVector()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
    void DoInsertValue(Box24* position, const Box24& value);     // 0x00424010
    void push_back(const Box24& value)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) Box24(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct IThumbnailService {                                       // 0x0067ddb0
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void CaptureBoxes(BoxVector* boxes, cViewer* viewer, int flag,
                              const Vector3* center, float inset, float height);   // +0x50
};
IThumbnailService* ThumbnailService();                           // 0x0067ddb0

struct cViewer {
    void GetXform(cSPTransform* out);                            // 0x007c40f0
    void SetXform(const cSPTransform* in);                       // 0x007c4d00
};

struct Property {                                                // variant property record
    char* mpData;                                                // +0x00
    uint32_t pad04[3];
    uint16_t mFlags;                                             // +0x10
    uint16_t mType;                                              // +0x12
    __forceinline void* GetStorage()
    {
        if (mFlags & 0x30) return mpData;
        if (mType) return this;
        return 0;
    }
    __forceinline float* GetFloat()
    {
        if (mType == 13 || mType == 0x10) return (float*)GetStorage();
        return &g_defaultFloat;
    }
};

struct cDirectPropertyList {                                     // sAppProperties (0x015fd918)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual Property* GetProperty(uint32_t key);                 // +0x28
};
extern cDirectPropertyList* sAppProperties;                      // 0x015fd918

struct cCreatureExtra {                                          // creature +0x180
    uint32_t pad00[0x6c / 4];
    float mSize;                                                 // +0x6c
    Box24 mBoundingBox;                                          // +0x70
};

struct cCreatureEffects {
    void FUN_009cb4f0();                                         // 0x009cb4f0
};

struct cEditorCreature {
    virtual void SetModelResource(void* pResource);              // +0x00
    uint32_t pad04[(0x3c - 0x04) / 4];
    float m3c;                                                   // +0x3c
    uint32_t pad40[(0x154 - 0x40) / 4];
    int m154;                                                    // +0x154
    uint32_t pad158[(0x17c - 0x158) / 4];
    cCreatureEffects* mp17c;                                                 // +0x17c
    cCreatureExtra* mpExtra;                                     // +0x180
    void FUN_00a04a90(int a);                                    // 0x00a04a90
    void FUN_00a04ab0(int a);                                    // 0x00a04ab0
    void FUN_00a04d00(int a);                                    // 0x00a04d00
    void FUN_00a04ce0(uint32_t a);                               // 0x00a04ce0
};

struct cSPEditorAnimatedCreatureManager {
    uint32_t AddCreature(void* pCreature);                                    // 0x0059c9c0
    uint32_t CreateCreature(cSPEditorModel* pModel, cSkinObject* pSkin, bool a, bool b);   // 0x0059c830
    cEditorCreature* GetCreature(uint32_t id);                                // 0x0059ca70
    void SetCreatureVisible(uint32_t id, bool b);                             // 0x0059ce30
    void ResetCreature(uint32_t id);                                          // 0x0059d240
    void FUN_0059d180(uint32_t id, int v);                                    // 0x0059d180
    cCreatureStructure* GetCreatureStructure(uint32_t id);                    // 0x0059cac0
    void FUN_0059d1e0(uint32_t id, bool b);                                   // 0x0059d1e0
    bool GetCreaturePosition(uint32_t id, Vector3* pOut);                     // 0x0059d110
    void FUN_0059d060(uint32_t id, bool b);                                   // 0x0059d060
    void SetCreatureTargetPosition(uint32_t id, Vector3 pos, bool a, bool b); // 0x0059cf00
    void SetCreatureTargetAngle(uint32_t id, float angle, bool a);            // 0x0059cea0
    void SetCreatureSpeeds(uint32_t id, float a, float b);                    // 0x0059d0b0
    void PlayAnimation(uint32_t id, uint32_t anim);                           // 0x0059cb10
    void SetCreaturePreserveHeight(uint32_t id, bool b);                      // 0x0059cf60
};

struct IModelManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void* GetModelResource(uint32_t id, int a, int b);                // +0x28
};
IModelManager* ModelManager();                                                // 0x0067dd80

struct IMessageManager {
    void Post(uint32_t messageID, int a, void* pPayload);                     // 0x0045af60
};
IMessageManager* MessageManager();                                            // 0x00401050

// Placement helper at editor +0x7c.
struct cCreatureLayout {
    void FUN_0062ad70(const Vector3* pTarget, uint32_t id, int index, float size, Vector3 offset);  // 0x0062ad70
};

// Record of one entourage creature (0x30 bytes).
struct cPaintCreatureRec {
    uint32_t mCreatureId;                                        // +0x00
    float m04;                                                   // +0x04
    float mApproachDistance;                                     // +0x08
    Vector3 mOffset;                                             // +0x0c
    bool mb18, mb19, mb1a, mb1b, mb1c;                           // +0x18
    float m20, m24, m28;                                         // +0x20
    int m2c;                                                     // +0x2c
    cPaintCreatureRec()
        : mCreatureId(0), m04(0.0f), mApproachDistance(0.0f), mOffset(kVecDefault),
          mb18(false), mb19(false), mb1a(false), m20(0.0f) {}
    cPaintCreatureRec(const cPaintCreatureRec& r);               // 0x00576900
};

struct cRecVector {
    cPaintCreatureRec* mpBegin;                                  // +0x00
    cPaintCreatureRec* mpEnd;                                    // +0x04
    cPaintCreatureRec* mpCapacity;                               // +0x08
    uint32_t mAllocator[2];
    void DoInsertValue(cPaintCreatureRec* position, const cPaintCreatureRec& value);   // 0x0057f0f0
    void push_back(const cPaintCreatureRec& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) cPaintCreatureRec(value);
        else
            DoInsertValue(mpEnd, value);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
};

namespace SP {

class cAppModeEditorBase {
public:
    uint32_t pad00[0x7c / 4];
    cCreatureLayout* mpLayout;                                   // +0x7c
    uint32_t pad80[(0x98 - 0x80) / 4];
    cSPEditorModel* mpEditorSaveModel;                           // +0x98
    uint32_t pad9c[(0x150 - 0x9c) / 4];
    cSkinHolder* mpSkinManager;                                  // +0x150
    cSkinHolder* mpPainter;                                      // +0x154
    uint32_t pad158[(0x2b5 - 0x158) / 4];
    uint8_t pad2b4[1];
    bool mb2b5;                                                  // +0x2b5
    uint8_t pad2b6[2];
    float mGIFBoxInset;                                          // +0x2b8 (GIF box shrink factor)
    uint8_t pad2bc[(0x31c - 0x2bc)];
    int mEditorMode;                                             // +0x31c
    uint32_t pad320[(0x34c - 0x320) / 4];
    int m34c;                                                    // +0x34c
    uint32_t pad350[(0x360 - 0x350) / 4];
    cSPEditorAnimatedCreatureManager* mpCreatureMgr;             // +0x360
    uint32_t mTorsoCreatureId;                                   // +0x364
    uint32_t mPainterCreatureId;                                 // +0x368
    cRecVector mRecs;                                            // +0x36c
    uint8_t pad380[(0x3d8 - 0x380)];
    cViewer* mpCaptureViewer;                                    // +0x3d8
    uint8_t pad3dc[4];
    bool mIsRecordingGIF;                                        // +0x3e0
    bool mbCountGIFFrames;                                       // +0x3e1
    uint8_t pad3e2[2];
    int mGIFFrameCount;                                          // +0x3e4

    bool RunSkinPaintOnEditorModel(int kind, void* pExisting);
    void FUN_00583900();

    __forceinline void RebuildSkin(cSkinHolder* pHolder, cSkinObject* pSkin)
    {
        pHolder->Update(0, 1, cSkinUpdateFlags(), 0);
        pSkin->BuildSkeleton();
        pSkin->FUN_004cb340();
        pSkin->FUN_004cb820();
    }
};

// @ 0x00582fe0  SP::cAppModeEditorBase::RunSkinPaintOnEditorModel
bool cAppModeEditorBase::RunSkinPaintOnEditorModel(int kind, void* pExisting)
{
    cSkinHolder* pHolder = 0;
    uint32_t* pId = 0;
    int count = 0;
    int idx = 0;

    if (kind == 0) {
        pHolder = mpSkinManager;
        pId = &mTorsoCreatureId;
    } else if (kind == 1) {
        cPaintCreatureRec rec;
        mRecs.push_back(rec);
        pHolder = mpSkinManager;
        count = mRecs.size();
        idx = count - 1;
        pId = &mRecs.mpBegin[idx].mCreatureId;
    } else if (kind == 2) {
        pHolder = mpPainter;
        pId = &mPainterCreatureId;
    }

    if (mpCreatureMgr) {
        if (!pId)
            return false;
        if (pHolder) {
            cSkinObject* pSkin = pHolder->GetSkin(1);
            if (!*pId && pSkin) {
                bool bMeshValid = pSkin->IsMeshValid();
                pHolder->IsSkinUpToDate();
                if (!pHolder->IsSkinUpToDate() || !bMeshValid)
                    RebuildSkin(pHolder, pSkin);

                bool bFlag = true;
                if (kind == 0 && mEditorMode == 0)
                    bFlag = false;

                uint32_t id;
                if (pExisting)
                    id = mpCreatureMgr->AddCreature(pExisting);
                else
                    id = mpCreatureMgr->CreateCreature(mpEditorSaveModel, pSkin, bFlag, kind == 1);
                *pId = id;

                if (id) {
                    cEditorCreature* pCreature = mpCreatureMgr->GetCreature(id);
                    if (pCreature) {
                        IModelManager* pModels = ModelManager();
                        pCreature->SetModelResource(
                            pModels->GetModelResource(kind == 2 ? 0x509991e7 : 0x509991e6, 0, 1));
                        if (pCreature->mp17c)
                            pCreature->mp17c->FUN_009cb4f0();
                        if (!FUN_004a0ac0(mpEditorSaveModel) && mb2b5) {
                            pCreature->FUN_00a04a90(0);
                            if (mpEditorSaveModel->mModelType == 0xdfad9f51)
                                pCreature->FUN_00a04ab0(0);
                        }
                        mpCreatureMgr->SetCreatureVisible(*pId, true);
                        mpCreatureMgr->ResetCreature(*pId);
                        mpCreatureMgr->FUN_0059d180(*pId, m34c);
                        mpCreatureMgr->GetCreature(*pId)->m154 = 1;
                        mpCreatureMgr->GetCreatureStructure(*pId)->FUN_0059b390();
                        mpCreatureMgr->FUN_0059d1e0(*pId, kind != 1);

                        if (kind == 1) {
                            if (!pExisting)
                                pCreature->m3c = 0.45f;
                            Vector3 target = kVecDefault;
                            Vector3 pos;
                            if (mpCreatureMgr->GetCreaturePosition(mTorsoCreatureId, &pos)) {
                                cEditorCreature* pTorso = mpCreatureMgr->GetCreature(mTorsoCreatureId);
                                float size = pTorso->mpExtra->mSize * 1.5f;
                                if (size < 2.0f)
                                    size = 2.0f;
                                else if (size > 3.75f)
                                    size = 3.75f;

                                mRecs.mpBegin[idx].mApproachDistance = RandomFloatRange(3.7f, 5.5f);
                                mRecs.mpBegin[idx].mOffset.x = RandomFloat(0.3f);
                                mRecs.mpBegin[idx].mOffset.y = RandomFloat(0.3f);

                                pos.z = 0.0f;
                                Matrix3 rot = Matrix3(MakeRotation(kAxisUp, (float)(count - 1) / count * kAngleScale));
                                float dx = kApproachDir.x * size;
                                float dy = kApproachDir.y * size;
                                float dz = kApproachDir.z * size;
                                target.x = ((rot.row[1].x * dy + rot.row[2].x * dz) + rot.row[0].x * dx) + pos.x;
                                target.y = pos.y + ((rot.row[0].y * dx + rot.row[1].y * dy) + rot.row[2].y * dz);
                                target.z = pos.z + ((rot.row[0].z * dx + rot.row[1].z * dy) + rot.row[2].z * dz);
                                const cPaintCreatureRec& r = mRecs.mpBegin[idx];
                                target.x = target.x + r.mOffset.x;
                                target.y = r.mOffset.y + target.y;
                                target.z = r.mOffset.z + target.z;

                                mpCreatureMgr->FUN_0059d060(*pId, true);
                                mpLayout->FUN_0062ad70(&target, *pId, count - 1, size,
                                                       mRecs.mpBegin[idx].mOffset);
                                mpCreatureMgr->SetCreatureTargetPosition(*pId, target, true, true);

                                Vector3 negDir(-kApproachDir.x, -kApproachDir.y, -kApproachDir.z);
                                Vector3 diff(pos.x - target.x, pos.y - target.y, pos.z - target.z);
                                mpCreatureMgr->SetCreatureTargetAngle(
                                    *pId, -SignedAngle(diff, negDir, kAxisUp, true), true);
                                mpCreatureMgr->SetCreatureSpeeds(*pId, 0.75f, kCreatureSpeed * 0.75f);
                            }
                            MessageManager()->Post(0x3f1bf57, 0, &target);
                            mpCreatureMgr->PlayAnimation(*pId, 0x43736bf);
                            mRecs.mpBegin[idx].mb18 = false;
                            mRecs.mpBegin[idx].mb19 = true;
                            mRecs.mpBegin[idx].mb1a = false;
                            mRecs.mpBegin[idx].mb1b = false;
                            mRecs.mpBegin[idx].mb1c = false;
                            mRecs.mpBegin[idx].m20 = 0.0f;
                            mRecs.mpBegin[idx].m24 = 0.0f;
                            mRecs.mpBegin[idx].m28 = 0.0f;
                            mRecs.mpBegin[idx].m2c = -1;
                        }

                        if (mpEditorSaveModel && mpEditorSaveModel->mTypeID == 0x3d97a8e4) {
                            pCreature->FUN_00a04d00(1);
                            pCreature->FUN_00a04ce0(0xcbcd1287);
                        }

                        if (kind == 0) {
                            Vector3 c = GetModelCenter(mpEditorSaveModel);
                            mpCreatureMgr->SetCreatureTargetPosition(*pId, Vector3(-c.x, -c.y, -c.z), true, false);
                            if (mEditorMode == 0 || mEditorMode == 1)
                                mpCreatureMgr->SetCreaturePreserveHeight(*pId, true);
                        } else if (kind == 2) {
                            Vector3 c = GetModelCenter(mpEditorSaveModel);
                            mpCreatureMgr->SetCreatureTargetPosition(*pId, Vector3(-c.x, -c.y, -c.z), true, false);
                            mpCreatureMgr->SetCreaturePreserveHeight(*pId, true);
                        }
                    }
                }
            }
        }
    }
    return pId && *pId != 0;
}

// @ 0x00583900
// cAppModeEditorBase::FUN_00583900 -- start a GIF recording of the animated torso creature: mark
// the capture live, take the creature's render box, shrink it toward its own centre by the property
// factor, hand the box to the thumbnail service with the capture viewer, then park the viewer on
// the creature's position.
void cAppModeEditorBase::FUN_00583900()
{
    mIsRecordingGIF = true;
    mGIFFrameCount = 0;

    cEditorCreature* pCreature = mpCreatureMgr->GetCreature(mTorsoCreatureId);
    cCreatureExtra* pExtra = pCreature->mpExtra;
    Box24 box = pExtra->mBoundingBox;

    float inset = *sAppProperties->GetProperty(0x5d2cbfb)->GetFloat();

    Vector3 pos;
    mpCreatureMgr->GetCreaturePosition(mTorsoCreatureId, &pos);

    int count = (int)(mRecs.mpEnd - mRecs.mpBegin);
    float scale = inset;
    if (count != 0)
        scale = inset + kThreeTenths;

    float midX = (box.mMin.x + box.mMax.x) * kHalf;
    float midY = (box.mMin.y + box.mMax.y) * kHalf;
    float midZ = (box.mMin.z + box.mMax.z) * kHalf;
    box.mMin.x = (box.mMin.x - midX) * scale + midX;
    box.mMin.y = (box.mMin.y - midY) * scale + midY;
    box.mMin.z = (box.mMin.z - midZ) * scale + midZ;
    box.mMax.x = (box.mMax.x - midX) * scale + midX;
    box.mMax.y = (box.mMax.y - midY) * scale + midY;
    box.mMax.z = (box.mMax.z - midZ) * scale + midZ;

    BoxVector boxes;
    boxes.push_back(box);

    Vector3 center;
    center.x = (box.mMin.x + box.mMax.x) * kHalf;
    center.y = (box.mMin.y + box.mMax.y) * kHalf;
    center.z = (box.mMin.z + box.mMax.z) * kHalf;
    ThumbnailService()->CaptureBoxes(&boxes, mpCaptureViewer, 0, &center, mGIFBoxInset, 0.0f);

    cSPTransform xf;
    mpCaptureViewer->GetXform(&xf);
    xf.mTranslation.x += pos.x;
    xf.mTranslation.y += pos.y;
    xf.mTranslation.z += pos.z;
    xf.mFlags |= 4;
    xf.mModificationCount++;
    mpCaptureViewer->SetXform(&xf);
}

}  // namespace SP
