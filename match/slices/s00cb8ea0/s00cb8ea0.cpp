// Serializer registration (0x00cb8ea0): add this object to the serializer as a child with the class descriptor at
// 0x157e578 and the name L"cCulturalProjectile" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cb8ea0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cb8ea0[];   // 0x0157e578 class descriptor

struct Object_cb8ea0 {
    bool AddTo(Serializer_cb8ea0* serializer);
};

// @ 0x00cb8ea0
bool Object_cb8ea0::AddTo(Serializer_cb8ea0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_cb8ea0, L"cCulturalProjectile");
}
