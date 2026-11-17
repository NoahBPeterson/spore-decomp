// Serializer registration (0x00ac0b70): add this object to the serializer as a child with the class descriptor at
// 0x1565ad8 and the name L"cAnimalCargoInfo" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ac0b70 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ac0b70[];   // 0x01565ad8 class descriptor

struct Object_ac0b70 {
    bool AddTo(Serializer_ac0b70* serializer);
};

// @ 0x00ac0b70
bool Object_ac0b70::AddTo(Serializer_ac0b70* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0xc), sDescriptor_ac0b70, L"cAnimalCargoInfo");
}
