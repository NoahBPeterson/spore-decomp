// Serializer registration (0x00c5f210): add this object to the serializer as a child with the class descriptor at
// 0x15770b8 and the name L"cMissionStory201" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c5f210 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c5f210[];   // 0x015770b8 class descriptor

struct Object_c5f210 {
    bool AddTo(Serializer_c5f210* serializer);
};

// @ 0x00c5f210
bool Object_c5f210::AddTo(Serializer_c5f210* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c5f210, L"cMissionStory201");
}
