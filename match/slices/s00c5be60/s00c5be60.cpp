// Serializer registration (0x00c5be60): add this object to the serializer as a child with the class descriptor at
// 0x1576bc8 and the name L"cRaidEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c5be60 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c5be60[];   // 0x01576bc8 class descriptor

struct Object_c5be60 {
    bool AddTo(Serializer_c5be60* serializer);
};

// @ 0x00c5be60
bool Object_c5be60::AddTo(Serializer_c5be60* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c5be60, L"cRaidEvent");
}
