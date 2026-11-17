// Serializer registration (0x00c4afb0): add this object to the serializer as a child with the class descriptor at
// 0x1574ee8 and the name L"cMissionAdventure" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c4afb0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c4afb0[];   // 0x01574ee8 class descriptor

struct Object_c4afb0 {
    bool AddTo(Serializer_c4afb0* serializer);
};

// @ 0x00c4afb0
bool Object_c4afb0::AddTo(Serializer_c4afb0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c4afb0, L"cMissionAdventure");
}
