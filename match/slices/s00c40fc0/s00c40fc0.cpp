// Serializer registration (0x00c40fc0): add this object to the serializer as a child with the class descriptor at
// 0x15740d8 and the name L"cInterCityRoad" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c40fc0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c40fc0[];   // 0x015740d8 class descriptor

struct Object_c40fc0 {
    bool AddTo(Serializer_c40fc0* serializer);
};

// @ 0x00c40fc0
bool Object_c40fc0::AddTo(Serializer_c40fc0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c40fc0, L"cInterCityRoad");
}
