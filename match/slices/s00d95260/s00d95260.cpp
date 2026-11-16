
#include "types.h"
#include <intrin.h>

#pragma intrinsic(_ReadWriteBarrier)

namespace SP {

class Citizen;

struct ActionCircle {
    void RemoveAgent(Citizen* citizen); // 0x00afae50
    unsigned char pad[0x64];
};

struct Owner {
    unsigned char pad00[0x220];
    ActionCircle* mpBegin; // +0x220
    ActionCircle* mpEnd;   // +0x224
};

class Citizen {
public:
    virtual void v0();
    virtual void Release();

    unsigned char pad04[0xfb8 - 4];
    Owner* mpOwner; // +0xfb8

    void InterruptAnimation(
        unsigned int animation,
        int a,
        int b
    ); // 0x00c12310

    void SetCurrentToolEffect(
        int effect,
        unsigned int id
    ); // 0x00c24f40
};

struct RepairState {
    unsigned char flag;
    unsigned char pad01[3];
    int slotIndex;        // +0x04
    int slotB;            // +0x08
    Citizen* target;      // +0x0c
};

namespace CitizenTree {

// @ 0x00d95260
void __cdecl RepairBuilding_Deactivate(
    Citizen* citizen,
    int a2,
    int a3,
    int a4,
    int a5,
    RepairState* state,
    int a7,
    int a8
)
{
    int index = state->slotIndex;

    if (index != -1) {
        Owner* owner = citizen->mpOwner;

        if (index < owner->mpEnd - owner->mpBegin) {
            _ReadWriteBarrier();

            owner->mpBegin[index].RemoveAgent(citizen);
        }
    }

    citizen->InterruptAnimation(0x02481db0, -1, 0);
    citizen->SetCurrentToolEffect(0, -1);

    Citizen* target = state->target;

    if (target) {
        target->Release();
    }
}

} // namespace CitizenTree
} // namespace SP
