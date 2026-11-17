// Serializer registration (0x00d4bfa0): add this object to the serializer as a child with the class descriptor at
// 0x1583920 and the name L"cNightPredatorEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d4bfa0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d4bfa0[];   // 0x01583920 class descriptor

struct Object_d4bfa0 {
    bool AddTo(Serializer_d4bfa0* serializer);
};

// @ 0x00d4bfa0
bool Object_d4bfa0::AddTo(Serializer_d4bfa0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_d4bfa0, L"cNightPredatorEvent");
}
