// Serializer registration (0x00f39e20): add this object to the serializer as a child with the class descriptor at
// 0x15b029c and the name L"cScenarioVehicleTicker" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_f39e20 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_f39e20[];   // 0x015b029c class descriptor

struct Object_f39e20 {
    bool AddTo(Serializer_f39e20* serializer);
};

// @ 0x00f39e20
bool Object_f39e20::AddTo(Serializer_f39e20* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_f39e20, L"cScenarioVehicleTicker");
}
