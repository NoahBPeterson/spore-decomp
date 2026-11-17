// Serializer registration (0x00c6a340): add this object to the serializer as a child with the class descriptor at
// 0x15778f0 and the name L"cEgg" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c6a340 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c6a340[];   // 0x015778f0 class descriptor

struct Object_c6a340 {
    bool AddTo(Serializer_c6a340* serializer);
};

// @ 0x00c6a340
bool Object_c6a340::AddTo(Serializer_c6a340* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c6a340, L"cEgg");
}
