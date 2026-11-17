// Serializer registration (0x00b85b90): add this object to the serializer as a child with the class descriptor at
// 0x156b6f0 and the name L"cPlanetModel" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b85b90 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b85b90[];   // 0x0156b6f0 class descriptor

struct Object_b85b90 {
    bool AddTo(Serializer_b85b90* serializer);
};

// @ 0x00b85b90
bool Object_b85b90::AddTo(Serializer_b85b90* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_b85b90, L"cPlanetModel");
}
