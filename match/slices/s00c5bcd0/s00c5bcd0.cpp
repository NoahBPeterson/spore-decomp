// Serializer registration (0x00c5bcd0): add this object to the serializer as a child with the class descriptor at
// 0x15769a8 and the name L"cRaidPlunderEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c5bcd0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c5bcd0[];   // 0x015769a8 class descriptor

struct Object_c5bcd0 {
    bool AddTo(Serializer_c5bcd0* serializer);
};

// @ 0x00c5bcd0
bool Object_c5bcd0::AddTo(Serializer_c5bcd0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c5bcd0, L"cRaidPlunderEvent");
}
