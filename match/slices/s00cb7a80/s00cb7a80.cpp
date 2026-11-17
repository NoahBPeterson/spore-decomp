// Serializer registration (0x00cb7a80): add this object to the serializer as a child with the class descriptor at
// 0x157d7d8 and the name L"cFlakProjectile" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cb7a80 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cb7a80[];   // 0x0157d7d8 class descriptor

struct Object_cb7a80 {
    bool AddTo(Serializer_cb7a80* serializer);
};

// @ 0x00cb7a80
bool Object_cb7a80::AddTo(Serializer_cb7a80* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_cb7a80, L"cFlakProjectile");
}
