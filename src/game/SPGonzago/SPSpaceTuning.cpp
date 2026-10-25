// src/game/SPGonzago/SPSpaceTuning.cpp -- migrated from slice(s) s0103fe90 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceTuning.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void _ReadWriteBarrier(void);
extern "C" void* __stdcall FUN_00b3d2a0(void* a);                  // 0x00b3d2a0 SP::StarManager
extern "C" float __cdecl FUN_010307a0(void* p, int a, int b);      // 0x010307a0
extern "C" void  __cdecl FUN_00571db0(void* server, void* handler, void* ids, int count, int prio); // 0x00571db0 EA::Messaging::RemoveHandler
extern float     DAT_013ec5b4;               // 0x013ec5b4 1000.0f
extern float     DAT_013eb960;               // 0x013eb960 0.01f
#pragma intrinsic(_ReadWriteBarrier)

// ---- items of slice s0103fe90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))
extern "C" void _ReadWriteBarrier(void);
extern "C" void* __stdcall FUN_00b3d2a0(void* a);                  // 0x00b3d2a0 SP::StarManager
extern "C" float __cdecl FUN_010307a0(void* p, int a, int b);      // 0x010307a0
extern "C" void  __cdecl FUN_00571db0(void* server, void* handler, void* ids, int count, int prio); // 0x00571db0 EA::Messaging::RemoveHandler
extern float     DAT_013ec5b4;               // 0x013ec5b4 1000.0f
extern float     DAT_013eb960;               // 0x013eb960 0.01f
class tHost {
public:
    void  __thiscall FUN_00692f60(int a);                    // 0x00692f60 cRegNode::Construct
    char  __thiscall FUN_00ab30c0();                         // 0x00ab30c0
    void  __thiscall FUN_00692850();                         // 0x00692850
    void* __thiscall FUN_00baf700();                         // 0x00baf700
    void  __thiscall FUN_00733030(void* a, void* b);         // 0x00733030
    void* __thiscall FUN_00c71e30();                         // 0x00c71e30
    void* __thiscall FUN_00f67d90();                         // 0x00f67d90 GetCurrentTerrainSphere
    char  __thiscall FUN_00c75650();                         // 0x00c75650 cTerrainSphere::Check
    void  __thiscall FUN_00bdbf10();                         // 0x00bdbf10
    void  __thiscall FUN_00ff0350(float f);                  // 0x00ff0350 cCityData::AddValue
    void  __thiscall FUN_00fffdd0(int a, int b);             // 0x00fffdd0
    void* __thiscall FUN_00d06240(void* a);                  // 0x00d06240 cRelationshipManager::RecordEvent
    void  __thiscall FUN_00dd8640(int a, int b, int c, int d, int e, int f); // 0x00dd8640 PostFeedbackEvent
    void  __thiscall FUN_00676e90(int a, int b);             // 0x00676e90 Achievements::AutoTest
    void* __thiscall FUN_00b21340(void* a, void* b, void* c, void* d, void* e); // 0x00b21340 GetGameDataVector
};
class cSpaceTuning {
public:
    uint8_t m00[0x50];           // +0x50 float parameter lives in another view; pad 0x00..0x50
    float   m50;                 // +0x50
    uint8_t m54[0x40];           // +0x54 -> +0x94
    int     m94;                 // +0x94
    uint8_t m98[4];              // +0x98
    float   m9c;                 // +0x9c

    int   __thiscall FUN_010407d0(void* param);
    float __thiscall FUN_01040820(float param);
    uint32_t __thiscall FUN_01040870();
};
class PaintSystem {
public:
    virtual ~PaintSystem() {}
    virtual void _v01();
};
class cSpaceRelationshipTuning : public PaintSystem {
public:
    void* mpServer;              // +0x04
    void* mpHandler;             // +0x08
    void* mpIdArray;             // +0x0c
    int   mnIdArrayCount;        // +0x10
    int   mnPriority;            // +0x14
    void* mPropList;             // +0x18
    void* mUIPropList;           // +0x1c

    void __thiscall FUN_010408f0();
    virtual ~cSpaceRelationshipTuning();
};
// ---- items of slice s0103fe90 end

// @ 0x010407d0
int __thiscall cSpaceTuning::FUN_010407d0(void* param)
{
    void* p = FUN_00b3d2a0(param);
    void* q = ((tHost*)p)->FUN_00baf700();
    float r = FUN_010307a0(q, 0x68d6965, 0x68d696b);
    float f = (float)m94 * r;
    return (int)(f * DAT_013eb960) * 100;
}

// @ 0x01040820
float __thiscall cSpaceTuning::FUN_01040820(float param)
{
    if (m50 > param) {
        return 0.0f;
    }
    return 1.0f;
}

// @ 0x01040870
uint32_t __thiscall cSpaceTuning::FUN_01040870()
{
    return (uint32_t)(m9c * DAT_013ec5b4);
}

// @ 0x010408f0
void __thiscall cSpaceRelationshipTuning::FUN_010408f0()
{
    if (mPropList != 0) {
        void* p = mPropList;
        mPropList = 0;
        ((void(__thiscall*)(void*))VFN(p, 4))(p);
    }
    if (mUIPropList != 0) {
        void* p = mUIPropList;
        mUIPropList = 0;
        ((void(__thiscall*)(void*))VFN(p, 4))(p);
    }
    if (mpServer != 0) {
        void* s = mpServer;
        mpServer = 0;
        FUN_00571db0(s, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
}

// @ 0x01040950
cSpaceRelationshipTuning::~cSpaceRelationshipTuning()
{
    _ReadWriteBarrier();
    void* ui = *(void* volatile*)&mUIPropList;
    if (ui != 0) {
        ((void(__thiscall*)(void*))VFN(ui, 4))(ui);
    }
    void* pl = *(void* volatile*)&mPropList;
    if (pl != 0) {
        ((void(__thiscall*)(void*))VFN(pl, 4))(pl);
    }
    if (mpServer != 0) {
        void* s = mpServer;
        mpServer = 0;
        FUN_00571db0(s, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
}
