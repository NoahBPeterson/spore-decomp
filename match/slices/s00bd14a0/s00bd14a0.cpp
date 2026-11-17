// Serializer registration (0x00bd14a0): add this object to the serializer as a child with the class descriptor at
// 0x156dbe4 and the name L"cBuildingEntertainment" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bd14a0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bd14a0[];   // 0x0156dbe4 class descriptor

struct Object_bd14a0 {
    bool AddTo(Serializer_bd14a0* serializer);
};

// @ 0x00bd14a0
bool Object_bd14a0::AddTo(Serializer_bd14a0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bd14a0, L"cBuildingEntertainment");
}
