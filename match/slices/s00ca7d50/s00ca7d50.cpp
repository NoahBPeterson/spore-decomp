// Serializer registration (0x00ca7d50): add this object to the serializer as a child with the class descriptor at
// 0x157cac8 and the name L"cVehicle" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ca7d50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ca7d50[];   // 0x0157cac8 class descriptor

struct Object_ca7d50 {
    bool AddTo(Serializer_ca7d50* serializer);
};

// @ 0x00ca7d50
bool Object_ca7d50::AddTo(Serializer_ca7d50* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_ca7d50, L"cVehicle");
}
