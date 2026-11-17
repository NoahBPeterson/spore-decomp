// Serializer registration (0x00cb8a10): add this object to the serializer as a child with the class descriptor at
// 0x157ddb8 and the name L"cDefaultBeamProjectile" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cb8a10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cb8a10[];   // 0x0157ddb8 class descriptor

struct Object_cb8a10 {
    bool AddTo(Serializer_cb8a10* serializer);
};

// @ 0x00cb8a10
bool Object_cb8a10::AddTo(Serializer_cb8a10* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_cb8a10, L"cDefaultBeamProjectile");
}
