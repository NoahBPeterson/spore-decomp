// Serializer registration (0x00fe4a70): add this object to the serializer as a child with the class descriptor at
// 0x15b42f8 and the name L"cBadgeManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_fe4a70 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_fe4a70[];   // 0x015b42f8 class descriptor

struct Object_fe4a70 {
    bool AddTo(Serializer_fe4a70* serializer);
};

// @ 0x00fe4a70
bool Object_fe4a70::AddTo(Serializer_fe4a70* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_fe4a70, L"cBadgeManager");
}
