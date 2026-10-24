// Slice s00d058a0 -- relationship manager event recording: the four-argument overload forwards a
// resolved relationship event into the plain RecordEvent sink.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

// Resolves the two relationship endpoints into a single event value.
int __cdecl FUN_00d01ab0(int a1, int a2, int a3, int a4, int a5, float weight); // 0x00d01ab0

class cRelationshipManager {
public:
    int  RecordEvent(int event);                                       // 0x00d05d90
    void RecordEvent(int a1, int a2, int a3, float weight);            // 0x00d06240
    void RecordFoughtEnemyEvent();
    int  CalculateRelationshipAbsolute();
    void FUN_00d058a0();
    void FUN_00d06030();
    void FUN_00d06400();
    void FUN_00d064b0();
    void FUN_00d065a0();
};

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xd058a0 SP::cRelationshipManager::FUN_00d058a0
void __thiscall cRelationshipManager::FUN_00d058a0()
{
}

// @ 0xd05a20 SP::cRelationshipManager::CalculateRelationshipAbsolute
int __thiscall cRelationshipManager::CalculateRelationshipAbsolute()
{
    return 0;
}

// @ 0xd05d90 SP::cRelationshipManager::RecordEvent
int __thiscall cRelationshipManager::RecordEvent(int event)
{
    (void)event;
    return 0;
}

// @ 0xd06030 SP::cRelationshipManager::FUN_00d06030
void __thiscall cRelationshipManager::FUN_00d06030()
{
}

// @ 0xd06240 SP::cRelationshipManager::RecordEvent(float)
void __thiscall cRelationshipManager::RecordEvent(int a1, int a2, int a3, float weight)
{
    RecordEvent(FUN_00d01ab0(a1, a2, a1, a2, a3, weight));
}

// @ 0xd06270 SP::cRelationshipManager::RecordFoughtEnemyEvent
void __thiscall cRelationshipManager::RecordFoughtEnemyEvent()
{
}

// @ 0xd06400 SP::cRelationshipManager::FUN_00d06400
void __thiscall cRelationshipManager::FUN_00d06400()
{
}

// @ 0xd064b0 SP::cRelationshipManager::FUN_00d064b0
void __thiscall cRelationshipManager::FUN_00d064b0()
{
}

// @ 0xd065a0 SP::cRelationshipManager::FUN_00d065a0
void __thiscall cRelationshipManager::FUN_00d065a0()
{
}

} // namespace SP
