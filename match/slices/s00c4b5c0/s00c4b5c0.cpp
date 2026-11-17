// Serializer registration (0x00c4b5c0): add this object to the serializer as a child with the class descriptor at
// 0x1574fc8 and the name L"cMissionBalance" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c4b5c0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c4b5c0[];   // 0x01574fc8 class descriptor

struct Object_c4b5c0 {
    bool AddTo(Serializer_c4b5c0* serializer);
};

// @ 0x00c4b5c0
bool Object_c4b5c0::AddTo(Serializer_c4b5c0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c4b5c0, L"cMissionBalance");
}
