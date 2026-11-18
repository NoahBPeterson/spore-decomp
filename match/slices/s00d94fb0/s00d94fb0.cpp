
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 {
    float x, y, z;
};

namespace SP {

class cCombatant_s00d9_0640;
int IsDamaged(cCombatant_s00d9_0640*);

struct Locomotion {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    PV(6) PV(7) PV(8) PV(9) PV(10)

    virtual const Vec3* GetPosition();
};

struct Combatant {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    PV(18) PV(19) PV(20) PV(21)

    virtual float GetSize_58();

    unsigned char pad04[0x34];
    float mHealth_38;
};

struct City {
    void** GetMembers();
};

struct Citizen {
    unsigned char pad00[0xc0];
    Locomotion mLocomotion;
    unsigned char padC4[0x120 - 0xc4];
    Combatant mCombatant;

    City* GetCity();
};

extern const float kFlHalf;

namespace CitizenTree {

void* FindNearestObjCitizen(
    void** list,
    const Vec3* position,
    bool (*predicate)(void*));

// @ 0x00d94fb0
float FUN_00d94fb0(Citizen* citizen)
{
    Citizen* target = (Citizen*)FindNearestObjCitizen(
        citizen->GetCity()->GetMembers(),
        citizen->mLocomotion.GetPosition(),
        (bool (*)(void*))IsDamaged
    );

    if (target) {
        float& health = reinterpret_cast<float&>(citizen);
        health = target->mCombatant.mHealth_38;

        double ratio =
            (double)health / target->mCombatant.GetSize_58();

        if (ratio < kFlHalf)
            return 1.0f;
    }

    return 0.0f;
}

} // namespace CitizenTree
} // namespace SP
