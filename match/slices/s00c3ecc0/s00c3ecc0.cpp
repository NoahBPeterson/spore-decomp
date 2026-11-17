// Serializer registration (0x00c3ecc0): add this object to the serializer as a child with the class descriptor at
// 0x1573ad8 and the name L"cGameplayMarker" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c3ecc0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c3ecc0[];   // 0x01573ad8 class descriptor

struct Object_c3ecc0 {
    bool AddTo(Serializer_c3ecc0* serializer);
};

// @ 0x00c3ecc0
bool Object_c3ecc0::AddTo(Serializer_c3ecc0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c3ecc0, L"cGameplayMarker");
}
