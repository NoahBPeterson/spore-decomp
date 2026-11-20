// @ 0x00d94f40
#include "game/types.h"

// Minimal retail layouts for the interfaces used by this decision.
namespace SP {
struct Vector3 { float x, y, z; };
class cSpatial {
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual const Vector3* GetPosition();
};
class cBuildingData;
class cActionCircle {
public:
    int CountOccupiedSlots(); // 0x00af9fa0
    char storage[0x64];
};
class cCityVisualizer {
public:
    int FindBuildingIndex(cBuildingData*); // 0x00d58130
    char padding[0x220];
    cActionCircle* mSlotCircles;
};
class cCity {
public:
    void** GetMembers(); // 0x00c8e810
};
class cSPCreatureCitizen {
public:
    cCity* GetCity() const; // 0x00c23e40
    char padding[0xc0];
    cSpatial mSpatial;
    char paddingAfterSpatial[0xfb8 - 0xc4];
    cCityVisualizer* mpCityVisualizer;
};
namespace CitizenTree {
bool IsDamaged(void*); // 0x00d91320
cBuildingData* FindNearestObjCitizen(void**, const Vector3*, bool (*)(void*)); // 0x00d94d10

// @ 0x00d94f40
float DamagedBuilding_Decide(cSPCreatureCitizen* citizen)
{
    cBuildingData* building = FindNearestObjCitizen(
        citizen->GetCity()->GetMembers(), citizen->mSpatial.GetPosition(), IsDamaged);
    if (building) {
        int index = citizen->mpCityVisualizer->FindBuildingIndex(building);
        if (index != -1) {
            cActionCircle* circle = &citizen->mpCityVisualizer->mSlotCircles[index];
            if (circle->CountOccupiedSlots() < 2)
                return 1.0f;
        }
    }
    return 0.0f;
}
}
}
