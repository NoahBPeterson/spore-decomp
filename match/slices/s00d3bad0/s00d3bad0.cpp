// Serializer registration (0x00d3bad0): add this object to the serializer as a child with the class descriptor at
// 0x15833f0 and the name L"cCreatureModeStrategy" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d3bad0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d3bad0[];   // 0x015833f0 class descriptor

struct Object_d3bad0 {
    bool AddTo(Serializer_d3bad0* serializer);
};

// @ 0x00d3bad0
bool Object_d3bad0::AddTo(Serializer_d3bad0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_d3bad0, L"cCreatureModeStrategy");
}
