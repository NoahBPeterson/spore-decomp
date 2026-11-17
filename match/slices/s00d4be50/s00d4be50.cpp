// Serializer registration (0x00d4be50): add this object to the serializer as a child with the class descriptor at
// 0x15838e4 and the name L"cTribeFoodRaidEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d4be50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d4be50[];   // 0x015838e4 class descriptor

struct Object_d4be50 {
    bool AddTo(Serializer_d4be50* serializer);
};

// @ 0x00d4be50
bool Object_d4be50::AddTo(Serializer_d4be50* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_d4be50, L"cTribeFoodRaidEvent");
}
