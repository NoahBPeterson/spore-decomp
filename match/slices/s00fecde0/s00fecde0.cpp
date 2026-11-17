// Serializer registration (0x00fecde0): add this object to the serializer as a child with the class descriptor at
// 0x15b4b90 and the name L"cMissionManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_fecde0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_fecde0[];   // 0x015b4b90 class descriptor

struct Object_fecde0 {
    bool AddTo(Serializer_fecde0* serializer);
};

// @ 0x00fecde0
bool Object_fecde0::AddTo(Serializer_fecde0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_fecde0, L"cMissionManager");
}
