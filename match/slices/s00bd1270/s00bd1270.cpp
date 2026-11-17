// Serializer registration (0x00bd1270): add this object to the serializer as a child with the class descriptor at
// 0x156db6c and the name L"cBuildingIndustry" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bd1270 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bd1270[];   // 0x0156db6c class descriptor

struct Object_bd1270 {
    bool AddTo(Serializer_bd1270* serializer);
};

// @ 0x00bd1270
bool Object_bd1270::AddTo(Serializer_bd1270* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bd1270, L"cBuildingIndustry");
}
