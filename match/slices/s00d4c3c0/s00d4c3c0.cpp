// Serializer registration (0x00d4c3c0): add this object to the serializer as a child with the class descriptor at
// 0x15839d4 and the name L"cBabyGameEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d4c3c0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d4c3c0[];   // 0x015839d4 class descriptor

struct Object_d4c3c0 {
    bool AddTo(Serializer_d4c3c0* serializer);
};

// @ 0x00d4c3c0
bool Object_d4c3c0::AddTo(Serializer_d4c3c0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_d4c3c0, L"cBabyGameEvent");
}
