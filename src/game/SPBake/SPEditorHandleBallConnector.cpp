// src/game/SPBake/SPEditorHandleBallConnector.cpp -- migrated from slice(s) s0047f520 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorHandleBallConnector.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s0047f520 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint32_t u32;
struct Vec3 { float x, y, z; };
struct cMWModel { char pad[0x44]; u32 mGroups[2]; };
struct ModelManagerIface {
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
    virtual u32 GetGroupID(u32 name, int flag);   // slot 0x28
};
struct cSPEditorHandle;
extern ModelManagerIface* ModelManager();   // 0x0067dd80 (equiv t2)
extern void  cSPEditorHandle_BaseInit(cSPEditorHandle*, void* a, int b, int c, int d); // FUN_0047db30
struct cSPEditorBlock;
struct cSPEditorHandle {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual void GetPosition(Vec3* out);   // slot 0x24
    void* mRefCountVft;                    // +4
    char pad8[8];
    cSPEditorBlock* mBlock;                // +0x10
    cMWModel* mModel;                      // +0x14
    cMWModel* mOverdrawModel;              // +0x18
    char pad1c[0x34];
};
static void SetGroupBit(cMWModel* m, u32 bit)
{
    if (bit < 0x40)
        m->mGroups[bit >> 5] |= 1u << (bit % 32);
}
// ---- items of slice s0047f520 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern ModelManagerIface* ModelManager();   // 0x0067dd80 (equiv t2)
extern void  cSPEditorHandle_BaseInit(cSPEditorHandle*, void* a, int b, int c, int d); // FUN_0047db30

// @ 0x0047f720
void __fastcall BallConnector_Init(cSPEditorHandle* self, int /*edx*/, void* param)
{
    cSPEditorHandle_BaseInit(self, param, 1, 0, 0);
    if (self->mBlock) {
        if (self->mModel)
            SetGroupBit(self->mModel, ModelManager()->GetGroupID(0x900c6cdd, 0));
        if (self->mOverdrawModel) {
            SetGroupBit(self->mOverdrawModel, ModelManager()->GetGroupID(0x22fff11, 0));
            SetGroupBit(self->mOverdrawModel, ModelManager()->GetGroupID(0x900c6cdd, 0));
        }
    }
}
