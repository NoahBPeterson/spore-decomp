// src/game/SPGonzago/_at_00e90000.cpp -- migrated from slice(s) s00e972b0, s00e8ffa0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00e90000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCommodityNode.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSpatialObject.h"
#include <float.h>
#include <new>

// ---- items of slice s00e8ffa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned int       u32;
struct Vec3 { float x, y, z; };
struct cGameNounManager_s00e8_ffa0 {
    char* GetObject(int id);                          // 0x00b25f40 (thiscall, ret 4)
    void* GetObjectByKey(const void* key);            // 0x00b262c0 (thiscall, ret 4)
};
int                GetCurrentGameMode();               // 0x00b5b800
cGameNounManager_s00e8_ffa0*  NounManager();                      // 0x00b3d300
void*              GonzagoModelWorld();                // 0x00b3d520
namespace SP {
class cSpatialObjectView {
public:
    void** mVTable;                    // +0x00
    void*  mpPrev;                     // +0x04
    void*  mpNext;                     // +0x08
    void*  mpObject;                   // +0x0c
    void*  mpObjectCombatant;          // +0x10
    u8     mField14;                   // +0x14
    u8     mPad15[3];
    Vec3   mColor;                     // +0x18
    u32    mKeyType;                   // +0x24
    u32    mKeyGroup;                  // +0x28
    u32    mKeyInstance;               // +0x2c
    u8     mField30;                   // +0x30
    u8     mField31;                   // +0x31
    u8     mField32;                   // +0x32
    u8     mPad33;                     // +0x33

    void BaseCtor();                   // 0x00e92af0
    void HandleSimulationUpdate(int a, int b);   // 0x00e92ca0
};
}
namespace SP {
class cPlaceholderColonyEditorCursorAttachment : public cSpatialObjectView {
public:
    __declspec(noinline) void* Construct();
    cPlaceholderColonyEditorCursorAttachment* MakeView(void* gameData);
    void HandleSimulationUpdate_c40(int a, int b);
};
}
namespace SP {
class cToolObject : public cSpatialObjectView {
public:
    cToolObject();
};
}
using SP::cSpatialObjectView;
using SP::cPlaceholderColonyEditorCursorAttachment;
using SP::cToolObject;
struct cPlaceholderModel {
    char mPad00[0xc];
    int  mKey;                         // +0x0c: noun key looked up by the manager
};
extern "C" void* __cdecl SPNewObject(u32 size, const char* name, int a, int b, int c, int d);
static inline void* VCall0(void* obj, unsigned off)
{
    return ((void* (__thiscall*)(void*))((void**)(*(void***)obj))[off / 4])(obj);
}
// ---- items of slice s00e8ffa0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* __cdecl SPNewObject(u32 size, const char* name, int a, int b, int c, int d);

// ---- items of slice s00e972b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cIVisualEffect;
struct EffectList
{
    cIVisualEffect** mpBegin;      // +0x00
    cIVisualEffect** mpEnd;        // +0x04
    cIVisualEffect** mpCapacity;   // +0x08
    uint32_t         mAllocator;   // +0x0c
    uint32_t         mPad10;       // +0x10
    EffectList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void EraseRange(cIVisualEffect** first, cIVisualEffect** last);   // 0x00533500
};
struct RefPtr
{
    cIVisualEffect* mp;            // +0x00
    RefPtr() : mp(0) {}
};
struct cIVisualEffect
{
    virtual int  AddRef();         // +0x00
    virtual int  Release();        // +0x04
    virtual void Start(int);       // +0x08
    virtual void Stop(int);        // +0x0c
};
struct cCreature;
struct cEffectsViewBase
{
    cEffectsViewBase();            // 0x00e92af0
    virtual void bv0();
    virtual void bv1();
    virtual void bv2();
    virtual void bv3();
    virtual void bv4();
    virtual void bv5();
    virtual void bv6();
    virtual void bv7();
    virtual void bv8();
    virtual void bv9();
    virtual void bv10();
    char mPad04[0x34 - 4];
};
class cCreatureCameraEffects : public cEffectsViewBase
{
public:
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
    virtual void* GetModel();                   // +0x2c
    virtual void  OnImpostorAdded(void*, void*);  // +0x30

    cCreature*    mpCreature;      // +0x34
    EffectList    mEffectsA;       // +0x38
    EffectList    mEffectsB;       // +0x4c
    RefPtr        mSelectedEffect; // +0x60
    RefPtr        mHiddenEffect;   // +0x64

    cCreatureCameraEffects();
    void ClearEffects(EffectList* list);
    void AddModelGroupImpostors();      // 0x00e97350
    void UpdateSelectionEffect();       // 0x00e978e0
};
struct cCreatureInfo
{
    char  mPad00[0xb0];
    float m_fb0;                 // +0xb0
    float m_fb4;                 // +0xb4
};
struct cCreature
{
    char           mPad00[0x13c];
    cCreatureInfo* mpInfo;             // +0x13c
    char           mPad140[0x170 - 0x140];
    void**         mpVec170Begin;      // +0x170
    void**         mpVec170End;        // +0x174
    void**         mpVec170Cap;        // +0x178
    char           mPad17c[0x184 - 0x17c];
    float          m_f184;             // +0x184
    char           mPad188[0x1bc - 0x188];
    unsigned       m_u1bc;             // +0x1bc
};
// ---- items of slice s00e972b0 end

// @ 0x00e90b50
__declspec(noinline) void* SP::cPlaceholderColonyEditorCursorAttachment::Construct()
{
    BaseCtor();
    Vec3 c = { 0.0f, 1.0f, 0.0f };
    mColor = c;
    mKeyType = 0xd749c1;
    mKeyGroup = 0;
    mVTable = (void**)0x1486934;
    mKeyInstance = 0x5c4fce4c;
    return this;
}

// @ 0x00e90be0
SP::cPlaceholderColonyEditorCursorAttachment* SP::cPlaceholderColonyEditorCursorAttachment::MakeView(void* gameData)
{
    cPlaceholderColonyEditorCursorAttachment* obj =
        (cPlaceholderColonyEditorCursorAttachment*)SPNewObject(
            0x34, "Simulator/cPlaceholderColonyEditorCursorAttachmentView", 0, 0, 0, 0);
    if (obj)
        obj = (cPlaceholderColonyEditorCursorAttachment*)obj->Construct();
    else
        obj = 0;

    cPlaceholderColonyEditorCursorAttachment* self = this;
    void** vtbl = (void**)obj->mVTable;
    ((void (__thiscall*)(void*, void*, void*, void*, void*))
        vtbl[0x28 / 4])(obj, gameData, GonzagoModelWorld(),
                        &self->mKeyType, &self->mColor);
    ((void* (__thiscall*)(void*))
        ((void**)obj->mVTable)[0x2c / 4])(obj);
    return obj;
}

// @ 0x00e90c40
void SP::cPlaceholderColonyEditorCursorAttachment::HandleSimulationUpdate_c40(int a, int b)
{
    cSpatialObjectView::HandleSimulationUpdate(a, b);

    if (GetCurrentGameMode() != 0x1654c05)
        return;

    (void)VCall0(this, 0x2c);
    cGameNounManager_s00e8_ffa0* mgr = NounManager();
    cPlaceholderModel* model = (cPlaceholderModel*)VCall0(this, 0x2c);
    void* noun = mgr->GetObjectByKey(&model->mKey);
    Vec3 c;
    if (noun) {
        c.x = 0.0f;
        c.y = 0.1f;
        c.z = 1.0f;
    } else {
        c.x = 1.0f;
        c.y = 0.0f;
        c.z = 0.1f;
    }
    mColor = c;
}

// @ 0x00e90d00
SP::cToolObject::cToolObject()
{
    BaseCtor();
    Vec3 c = { 1.0f, 1.0f, 1.0f };
    mColor = c;
    mVTable = (void**)0x14869bc;
}

// @ 0x00e972b0
bool IsIdInRange(uint64_t v)
{
    return v - 0x5b02bb3ULL <= 5;
}

// @ 0x00e972e0
cCreatureCameraEffects::cCreatureCameraEffects()
: mpCreature(0)
{
}
