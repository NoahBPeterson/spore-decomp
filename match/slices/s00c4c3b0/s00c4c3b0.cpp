// Serializer registration (0x00c4c3b0): add this object to the serializer as a child with the class descriptor at
// 0x1575128 and the name L"cMissionBiosphere" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c4c3b0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c4c3b0[];   // 0x01575128 class descriptor

struct Object_c4c3b0 {
    bool AddTo(Serializer_c4c3b0* serializer);
};

// @ 0x00c4c3b0
bool Object_c4c3b0::AddTo(Serializer_c4c3b0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c4c3b0, L"cMissionBiosphere");
}
