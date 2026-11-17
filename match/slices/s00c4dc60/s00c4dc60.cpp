// Serializer registration (0x00c4dc60): add this object to the serializer as a child with the class descriptor at
// 0x1575468 and the name L"cMissionChangeArchetype" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c4dc60 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c4dc60[];   // 0x01575468 class descriptor

struct Object_c4dc60 {
    bool AddTo(Serializer_c4dc60* serializer);
};

// @ 0x00c4dc60
bool Object_c4dc60::AddTo(Serializer_c4dc60* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c4dc60, L"cMissionChangeArchetype");
}
