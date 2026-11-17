// Serializer registration (0x00bd1360): add this object to the serializer as a child with the class descriptor at
// 0x156dba8 and the name L"cBuildingHouse" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bd1360 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bd1360[];   // 0x0156dba8 class descriptor

struct Object_bd1360 {
    bool AddTo(Serializer_bd1360* serializer);
};

// @ 0x00bd1360
bool Object_bd1360::AddTo(Serializer_bd1360* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bd1360, L"cBuildingHouse");
}
