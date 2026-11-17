// Serializer registration (0x00c4df50): add this object to the serializer as a child with the class descriptor at
// 0x15755d8 and the name L"cMissionColonize" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c4df50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c4df50[];   // 0x015755d8 class descriptor

struct Object_c4df50 {
    bool AddTo(Serializer_c4df50* serializer);
};

// @ 0x00c4df50
bool Object_c4df50::AddTo(Serializer_c4df50* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c4df50, L"cMissionColonize");
}
