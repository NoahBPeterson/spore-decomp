// Serializer registration (0x00c726e0): add this object to the serializer as a child with the class descriptor at
// 0x1578890 and the name L"cPlanet" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c726e0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c726e0[];   // 0x01578890 class descriptor

struct Object_c726e0 {
    bool AddTo(Serializer_c726e0* serializer);
};

// @ 0x00c726e0
bool Object_c726e0::AddTo(Serializer_c726e0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c726e0, L"cPlanet");
}
