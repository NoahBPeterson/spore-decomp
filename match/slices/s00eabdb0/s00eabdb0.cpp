// Serializer registration (0x00eabdb0): add this object to the serializer as a child with the class descriptor at
// 0x15a912c and the name L"cPlaceableSound" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_eabdb0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_eabdb0[];   // 0x015a912c class descriptor

struct Object_eabdb0 {
    bool AddTo(Serializer_eabdb0* serializer);
};

// @ 0x00eabdb0
bool Object_eabdb0::AddTo(Serializer_eabdb0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_eabdb0, L"cPlaceableSound");
}
