// Serializer registration (0x00bcba20): add this object to the serializer as a child with the class descriptor at
// 0x156d600 and the name L"cAnimalTrap" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bcba20 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bcba20[];   // 0x0156d600 class descriptor

struct Object_bcba20 {
    bool AddTo(Serializer_bcba20* serializer);
};

// @ 0x00bcba20
bool Object_bcba20::AddTo(Serializer_bcba20* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bcba20, L"cAnimalTrap");
}
