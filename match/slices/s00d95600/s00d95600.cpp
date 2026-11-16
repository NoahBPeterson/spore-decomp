
#include "types.h"

#define PV(n) virtual void pv##n();

namespace SP {

struct Target {
    PV(0)  PV(1)  PV(2)  PV(3)
    PV(4)  PV(5)  PV(6)  PV(7)
    PV(8)  PV(9)  PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23)

    virtual void AddRef();   // +0x60
    virtual void Release();  // +0x64
};

struct EffectHandle;

struct Owner {
    unsigned char pad00[0xa58];
    Target* mpTarget;        // +0xA58
    unsigned int mCounter;   // +0xA5C
};

struct Creature {
    unsigned char pad00[0xfb8];
    Owner* mpOwner;          // +0xFB8

    void SetSprinting(bool enabled); // 0x00C1AD10

    void InterruptAnimation(
        unsigned int animation,
        int a,
        int b
    ); // 0x00C12310
};

namespace CitizenTree {

struct PolicemanState {
    Target* mpTarget;        // +0x00
    EffectHandle* mpEffect;  // +0x04
};

// @ 0x00d95600
bool __cdecl Policeman_Activate(
    Creature* creature,
    int a2,
    int a3,
    int a4,
    int a5,
    PolicemanState* state,
    int a7,
    int a8
)
{
    if (state) {
        state->mpTarget = 0;
        state->mpEffect = 0;
    }

    Owner* owner = creature->mpOwner;

    Target* target = owner->mpTarget;
    Target* previous = state->mpTarget;

    if (target != previous) {
        if (target) {
            target->AddRef();
        }

        state->mpTarget = target;

        if (previous) {
            previous->Release();
        }
    }

    ++owner->mCounter;

    creature->SetSprinting(true);

    creature->InterruptAnimation(
        0x02481db0,
        -1,
        0
    );

    return true;
}

} // namespace CitizenTree
} // namespace SP
