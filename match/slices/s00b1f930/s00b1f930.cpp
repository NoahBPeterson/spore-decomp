// Serializer registration (0x00b1f930): add this object to the serializer as a child with the class descriptor at
// 0x1576338 and the name L"cMissionHappinessEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b1f930 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b1f930[];   // 0x01576338 class descriptor

struct Object_b1f930 {
    bool AddTo(Serializer_b1f930* serializer);
};

// @ 0x00b1f930
bool Object_b1f930::AddTo(Serializer_b1f930* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b1f930, L"cMissionHappinessEvent");
}
