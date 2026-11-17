// Serializer registration (0x00c7fec0): add this object to the serializer as a child with the class descriptor at
// 0x1579cd0 and the name L"cSimPlanetLowLOD" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c7fec0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c7fec0[];   // 0x01579cd0 class descriptor

struct Object_c7fec0 {
    bool AddTo(Serializer_c7fec0* serializer);
};

// @ 0x00c7fec0
bool Object_c7fec0::AddTo(Serializer_c7fec0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c7fec0, L"cSimPlanetLowLOD");
}
