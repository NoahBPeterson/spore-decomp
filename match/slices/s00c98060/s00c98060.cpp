// Serializer registration (0x00c98060): add this object to the serializer as a child with the class descriptor at
// 0x157ba68 and the name L"cTribe" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c98060 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c98060[];   // 0x0157ba68 class descriptor

struct Object_c98060 {
    bool AddTo(Serializer_c98060* serializer);
};

// @ 0x00c98060
bool Object_c98060::AddTo(Serializer_c98060* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c98060, L"cTribe");
}
