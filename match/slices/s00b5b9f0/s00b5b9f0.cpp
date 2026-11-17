// Serializer registration (0x00b5b9f0): add this object to the serializer as a child with the class descriptor at
// 0x15b72ec and the name L"cLivingUniverse" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b5b9f0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b5b9f0[];   // 0x015b72ec class descriptor

struct Object_b5b9f0 {
    bool AddTo(Serializer_b5b9f0* serializer);
};

// @ 0x00b5b9f0
bool Object_b5b9f0::AddTo(Serializer_b5b9f0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b5b9f0, L"cLivingUniverse");
}
