// Serializer registration (0x00e3e2e0): add this object to the serializer as a child with the class descriptor at
// 0x15a5a18 and the name L"cUITimeline" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_e3e2e0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_e3e2e0[];   // 0x015a5a18 class descriptor

struct Object_e3e2e0 {
    bool AddTo(Serializer_e3e2e0* serializer);
};

// @ 0x00e3e2e0
bool Object_e3e2e0::AddTo(Serializer_e3e2e0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_e3e2e0, L"cUITimeline");
}
