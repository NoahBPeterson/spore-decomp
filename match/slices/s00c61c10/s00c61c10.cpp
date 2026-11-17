// Serializer registration (0x00c61c10): add this object to the serializer as a child with the class descriptor at
// 0x15772c8 and the name L"cMissionTrackBadge" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c61c10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c61c10[];   // 0x015772c8 class descriptor

struct Object_c61c10 {
    bool AddTo(Serializer_c61c10* serializer);
};

// @ 0x00c61c10
bool Object_c61c10::AddTo(Serializer_c61c10* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c61c10, L"cMissionTrackBadge");
}
