// Serializer registration (0x00c61f80): add this object to the serializer as a child with the class descriptor at
// 0x15773b8 and the name L"cMissionTrade" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c61f80 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c61f80[];   // 0x015773b8 class descriptor

struct Object_c61f80 {
    bool AddTo(Serializer_c61f80* serializer);
};

// @ 0x00c61f80
bool Object_c61f80::AddTo(Serializer_c61f80* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c61f80, L"cMissionTrade");
}
