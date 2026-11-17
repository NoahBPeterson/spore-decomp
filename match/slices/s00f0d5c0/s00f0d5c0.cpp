// Serializer registration (0x00f0d5c0): add this object to the serializer as a child with the class descriptor at
// 0x15ad5ac and the name L"cPlaceableEffect" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_f0d5c0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_f0d5c0[];   // 0x015ad5ac class descriptor

struct Object_f0d5c0 {
    bool AddTo(Serializer_f0d5c0* serializer);
};

// @ 0x00f0d5c0
bool Object_f0d5c0::AddTo(Serializer_f0d5c0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_f0d5c0, L"cPlaceableEffect");
}
