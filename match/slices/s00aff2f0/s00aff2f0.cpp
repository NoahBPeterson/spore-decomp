// Serializer registration (0x00aff2f0): add this object to the serializer as a child with the class descriptor at
// 0x1567860 and the name L"cFruit" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_aff2f0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_aff2f0[];   // 0x01567860 class descriptor

struct Object_aff2f0 {
    bool AddTo(Serializer_aff2f0* serializer);
};

// @ 0x00aff2f0
bool Object_aff2f0::AddTo(Serializer_aff2f0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_aff2f0, L"cFruit");
}
