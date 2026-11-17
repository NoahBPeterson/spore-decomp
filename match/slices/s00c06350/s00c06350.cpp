// Serializer registration (0x00c06350): add this object to the serializer as a child with the class descriptor at
// 0x1571370 and the name L"cCreatureAnimal" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c06350 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c06350[];   // 0x01571370 class descriptor

struct Object_c06350 {
    bool AddTo(Serializer_c06350* serializer);
};

// @ 0x00c06350
bool Object_c06350::AddTo(Serializer_c06350* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c06350, L"cCreatureAnimal");
}
