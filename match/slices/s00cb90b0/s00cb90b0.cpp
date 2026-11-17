// Serializer registration (0x00cb90b0): add this object to the serializer as a child with the class descriptor at
// 0x157e758 and the name L"cResourceProjectile" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cb90b0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cb90b0[];   // 0x0157e758 class descriptor

struct Object_cb90b0 {
    bool AddTo(Serializer_cb90b0* serializer);
};

// @ 0x00cb90b0
bool Object_cb90b0::AddTo(Serializer_cb90b0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_cb90b0, L"cResourceProjectile");
}
