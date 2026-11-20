// Slice s00e897a0 -- cCityTerritoryView::HandleSimulationUpdate (0x00e897a0).
//
// The view forwards the simulation update to the cSpatialObjectView base, tells the
// effect system whether the territory is the active combatant, and then either clears
// the two selection ring effects or refreshes the selection when the territory object
// moved / changed size.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)
#pragma warning(disable : 4244)

typedef unsigned int  u32;
typedef unsigned char u8;

struct Float3 {
    float x, y, z;
};

// Retail global used as the comparison origin.
extern Float3 g_16c45d8;              // 0x016c45d8

bool __cdecl Vector3Equal(const Float3* a, const Float3* b);     // 0x004232c0
bool __cdecl Vector3_NotEqual(const Float3* a, const Float3* b);  // 0x0041dd30
u32  __cdecl GetUniverseContext();                                // 0x01021080

#define PAD_VIRT(n) virtual void pad##n()

// Bounds interface embedded in the territory object (GetPosition +0x2c, GetRadius +0x70).
struct IObjectBounds {
PAD_VIRT(0);
PAD_VIRT(1);
PAD_VIRT(2);
PAD_VIRT(3);
PAD_VIRT(4);
PAD_VIRT(5);
PAD_VIRT(6);
PAD_VIRT(7);
PAD_VIRT(8);
PAD_VIRT(9);
PAD_VIRT(10);
    virtual const Float3* GetPosition();          // +0x2c
PAD_VIRT(12);
PAD_VIRT(13);
PAD_VIRT(14);
PAD_VIRT(15);
PAD_VIRT(16);
PAD_VIRT(17);
PAD_VIRT(18);
PAD_VIRT(19);
PAD_VIRT(20);
PAD_VIRT(21);
PAD_VIRT(22);
PAD_VIRT(23);
PAD_VIRT(24);
PAD_VIRT(25);
PAD_VIRT(26);
PAD_VIRT(27);
    virtual float GetRadius();                    // +0x70
};

// Object returned by Cast(0x2450023) -- the territory whose selection may change.
struct cTerritoryObject {
PAD_VIRT(0);
PAD_VIRT(1);
PAD_VIRT(2);
PAD_VIRT(3);
PAD_VIRT(4);
PAD_VIRT(5);
PAD_VIRT(6);
PAD_VIRT(7);
PAD_VIRT(8);
PAD_VIRT(9);
PAD_VIRT(10);
PAD_VIRT(11);
PAD_VIRT(12);
PAD_VIRT(13);
PAD_VIRT(14);
PAD_VIRT(15);
PAD_VIRT(16);
PAD_VIRT(17);
PAD_VIRT(18);
PAD_VIRT(19);
PAD_VIRT(20);
PAD_VIRT(21);
    virtual bool IsAlternate();                   // +0x58
    virtual void SetSelected(bool b);             // +0x5c
    u8 pad04[0x34 - 4];
    IObjectBounds mBounds;                        // +0x34

    bool IsCombatant();                           // 0x00bebb20
};

// Object returned by Cast(0x1186577) -- the city the territory belongs to.
struct cCityObject {
PAD_VIRT(0);
PAD_VIRT(1);
PAD_VIRT(2);
PAD_VIRT(3);
PAD_VIRT(4);
PAD_VIRT(5);
PAD_VIRT(6);
PAD_VIRT(7);
PAD_VIRT(8);
PAD_VIRT(9);
PAD_VIRT(10);
    virtual const Float3* GetPosition();          // +0x2c
PAD_VIRT(12);
PAD_VIRT(13);
PAD_VIRT(14);
PAD_VIRT(15);
PAD_VIRT(16);
PAD_VIRT(17);
PAD_VIRT(18);
PAD_VIRT(19);
    virtual bool IsActive();                      // +0x50
PAD_VIRT(21);
PAD_VIRT(22);
    virtual void SetSelected(bool b);             // +0x5c
    u8 pad04[0x72 - 4];
    bool mbFlag72;                                // +0x72
};

// The cSpatialObjectView base of the territory view.
struct cSpatialObjectView {
PAD_VIRT(0);
PAD_VIRT(1);
PAD_VIRT(2);
PAD_VIRT(3);
PAD_VIRT(4);
PAD_VIRT(5);
PAD_VIRT(6);
PAD_VIRT(7);
PAD_VIRT(8);
PAD_VIRT(9);
PAD_VIRT(10);
PAD_VIRT(11);
PAD_VIRT(12);
PAD_VIRT(13);
PAD_VIRT(14);
PAD_VIRT(15);
PAD_VIRT(16);
PAD_VIRT(17);
PAD_VIRT(18);
PAD_VIRT(19);
PAD_VIRT(20);
PAD_VIRT(21);
PAD_VIRT(22);
PAD_VIRT(23);
PAD_VIRT(24);
PAD_VIRT(25);
PAD_VIRT(26);
PAD_VIRT(27);
PAD_VIRT(28);
PAD_VIRT(29);
PAD_VIRT(30);
PAD_VIRT(31);
PAD_VIRT(32);
PAD_VIRT(33);
PAD_VIRT(34);
PAD_VIRT(35);
PAD_VIRT(36);
PAD_VIRT(37);
PAD_VIRT(38);
PAD_VIRT(39);
PAD_VIRT(40);
PAD_VIRT(41);
PAD_VIRT(42);
PAD_VIRT(43);
PAD_VIRT(44);
PAD_VIRT(45);
    virtual cTerritoryObject* Cast(u32 typeId);   // +0xb8

    void HandleSimulationUpdate(int a, int b);    // 0x00e92ca0
    void StopEffect(u32 id, bool immediate);      // 0x00c8ad30
    bool HasEffect(u32 id);                       // 0x00c88910
    bool CheckEffectMode(u32 a, u32 b, bool c, int d); // 0x00c8b220
};

struct cCityTerritoryView {
    void** mpVtbl;                                // +0x00
    u32 pad04[2];
    cSpatialObjectView* mpObject;                 // +0x0c
    u32 pad10[(0x34 - 0x10) / 4];
    int mPlacementState;                          // +0x34
    Float3 mCenter;                               // +0x38
    float mRadius;                                // +0x44

    void HandleSimulationUpdate(int a, int b);    // 0x00e897a0
    void UpdateSelection();                       // 0x00e87db0
};

// @ 0x00e897a0
void cCityTerritoryView::HandleSimulationUpdate(int a, int b)
{
    ((cSpatialObjectView*)this)->HandleSimulationUpdate(a, b);

    cSpatialObjectView* view = mpObject;
    cTerritoryObject* territory = view ? view->Cast(0x2450023) : 0;

    const u32 mode = GetUniverseContext();          // 0x00e92ca0 fan-out: space vs. planet view
    bool inSimulation = mode == 0;
    bool activeCombatant = inSimulation && territory != 0 && territory->IsCombatant();
    mpObject->CheckEffectMode(0xb1e858ed, 0x6577c69, activeCombatant, 0);

    if (!inSimulation) {
        mpObject->StopEffect(0x243a1dc, true);
        mpObject->StopEffect(0x243a1dd, true);
        return;
    }

    cSpatialObjectView* obj = mpObject;
    if (obj == 0)
        return;

    cCityObject* city = (cCityObject*)obj->Cast(0x1186577);
    if (city == 0)
        return;

    const Float3* cityPos = city->GetPosition();
    Float3 pos;
    pos.x = cityPos->x;
    pos.y = cityPos->y;
    pos.z = cityPos->z;

    if (territory == 0)
        return;

    if (!city->mbFlag72)
        territory->SetSelected(true);

    if (!city->IsActive() || Vector3Equal(&pos, &g_16c45d8)) {
        mpObject->StopEffect(0x243a1dc, true);
        mpObject->StopEffect(0x243a1dd, true);
        return;
    }

    if (!city->IsActive())
        return;

    if (!mpObject->HasEffect(0x243a1dc)) {
        UpdateSelection();
        return;
    }

    if (Vector3_NotEqual(&pos, &mCenter)) {
        UpdateSelection();
        return;
    }

    if (territory->mBounds.GetRadius() != mRadius)
        UpdateSelection();
}
