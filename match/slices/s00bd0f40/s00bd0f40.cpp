// Serializer registration (0x00bd0f40): add this object to the serializer as a child with the class descriptor at
// 0x156d770 and the name L"cBuilding" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bd0f40 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bd0f40[];   // 0x0156d770 class descriptor

struct Object_bd0f40 {
    bool AddTo(Serializer_bd0f40* serializer);
};

// @ 0x00bd0f40
bool Object_bd0f40::AddTo(Serializer_bd0f40* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bd0f40, L"cBuilding");
}
