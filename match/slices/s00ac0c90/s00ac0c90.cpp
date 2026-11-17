// Serializer registration (0x00ac0c90): add this object to the serializer as a child with the class descriptor at
// 0x1565a9c and the name L"cAnimalSpeciesManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ac0c90 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ac0c90[];   // 0x01565a9c class descriptor

struct Object_ac0c90 {
    bool AddTo(Serializer_ac0c90* serializer);
};

// @ 0x00ac0c90
bool Object_ac0c90::AddTo(Serializer_ac0c90* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_ac0c90, L"cAnimalSpeciesManager");
}
