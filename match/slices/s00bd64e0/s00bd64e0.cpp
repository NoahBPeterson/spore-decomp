// Serializer registration (0x00bd64e0): add this object to the serializer as a child with the class descriptor at
// 0x156df10 and the name L"cCelestialBody" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bd64e0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bd64e0[];   // 0x0156df10 class descriptor

struct Object_bd64e0 {
    bool AddTo(Serializer_bd64e0* serializer);
};

// @ 0x00bd64e0
bool Object_bd64e0::AddTo(Serializer_bd64e0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bd64e0, L"cCelestialBody");
}
