// Serializer registration (0x00beca20): add this object to the serializer as a child with the class descriptor at
// 0x156f588 and the name L"cCityWalls" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_beca20 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_beca20[];   // 0x0156f588 class descriptor

struct Object_beca20 {
    bool AddTo(Serializer_beca20* serializer);
};

// @ 0x00beca20
bool Object_beca20::AddTo(Serializer_beca20* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_beca20, L"cCityWalls");
}
