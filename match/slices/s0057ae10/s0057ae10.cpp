// slice s0057ae10 — SP::cAppModeEditorBase::UpdateAnimatedCreature
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

struct cCreature {
    char pad0[0x74];
    Vector3 mOffset;              // +0x74
    char pad1[0x180 - 0x80];
    void* mpFlagsObj;             // +0x180
};

struct cCreatureFlags {
    char pad0[4];
    uint32_t mFlags;              // +4
};

struct cEditorModel {
    Vector3* GetVector(Vector3* out, int index);   // 0x004adca0 (thiscall, ret 8)
};

struct cAnimatedCreatureManager {
    cCreature* GetCreature(void* viewer);          // 0x0059ca70 (thiscall, ret 4)
};

struct cAppModeEditorBase {
    char pad0[0x98];
    cEditorModel* mEditorSaveModel;                // +0x98
    char pad1[0x31c - 0x9c];
    int32_t mQueuedAnim;                           // +0x31c
    char pad2[0x360 - 0x320];
    cAnimatedCreatureManager* mAnimCreatureManager; // +0x360
    void* mShadowViewer;                           // +0x364
    char pad3[0x384 - 0x368];
    bool mAnimatingCreatureVisible;                // +0x384
    bool mAnimatingCreatureActive;                 // +0x385

    void UpdateRenderSettings();                   // 0x005794b0
    void FUN_00575790();                           // 0x00575790
    void FUN_005757b0();                           // 0x005757b0

    void UpdateAnimatedCreature();
};

extern Vector3 gConst;   // 0x0150cc08

// @ 0x0057ae10
void cAppModeEditorBase::UpdateAnimatedCreature()
{
    if (mAnimCreatureManager != 0) {
        cCreature* creature = mAnimCreatureManager->GetCreature(mShadowViewer);
        if (creature != 0) {
            Vector3 v;
            Vector3* p;
            if (mQueuedAnim == 0) {
                cEditorModel* model = mEditorSaveModel;
                p = model->GetVector(&v, 0);
            } else {
                p = &gConst;
            }
            creature->mOffset = Vector3(*p);
        }
        if (mAnimatingCreatureActive) {
            if (!mAnimatingCreatureVisible && creature != 0) {
                cCreatureFlags* ff = (cCreatureFlags*)creature->mpFlagsObj;
                uint32_t flags = ff->mFlags;
                bool b14 = (flags >> 14) & 1;
                bool b0 = flags & 1;
                bool b15 = (flags >> 15) & 1;
                bool b18 = (flags >> 18) & 1;
                if (b14 && b0 && b15 && !b18) {
                    mAnimatingCreatureVisible = true;
                    UpdateRenderSettings();
                    FUN_00575790();
                }
            }
        }
        if (!mAnimatingCreatureActive) {
            if (mAnimatingCreatureVisible) {
                mAnimatingCreatureVisible = false;
                UpdateRenderSettings();
                FUN_005757b0();
            }
        }
    }
}
