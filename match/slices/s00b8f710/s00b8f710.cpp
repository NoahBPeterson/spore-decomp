// Serializer registration (0x00b8f710): add this object to the serializer as a child with the class descriptor at
// 0x156bd78 and the name L"cPlantCargoInfo" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b8f710 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b8f710[];   // 0x0156bd78 class descriptor

struct Object_b8f710 {
    bool AddTo(Serializer_b8f710* serializer);
};

// @ 0x00b8f710
bool Object_b8f710::AddTo(Serializer_b8f710* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0xc), sDescriptor_b8f710, L"cPlantCargoInfo");
}
