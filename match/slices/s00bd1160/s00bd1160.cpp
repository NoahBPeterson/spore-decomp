// Serializer registration (0x00bd1160): add this object to the serializer as a child with the class descriptor at
// 0x156dab8 and the name L"cBuildingCityHall" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bd1160 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bd1160[];   // 0x0156dab8 class descriptor

struct Object_bd1160 {
    bool AddTo(Serializer_bd1160* serializer);
};

// @ 0x00bd1160
bool Object_bd1160::AddTo(Serializer_bd1160* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bd1160, L"cBuildingCityHall");
}
