// Serializer registration (0x00eadd10): add this object to the serializer as a child with the class descriptor at
// 0x15a9198 and the name L"cPlayerCityMusic" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_eadd10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_eadd10[];   // 0x015a9198 class descriptor

struct Object_eadd10 {
    bool AddTo(Serializer_eadd10* serializer);
};

// @ 0x00eadd10
bool Object_eadd10::AddTo(Serializer_eadd10* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_eadd10, L"cPlayerCityMusic");
}
