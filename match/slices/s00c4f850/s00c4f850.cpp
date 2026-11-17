// Serializer registration (0x00c4f850): add this object to the serializer as a child with the class descriptor at
// 0x15756d8 and the name L"cMissionEradicate" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c4f850 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c4f850[];   // 0x015756d8 class descriptor

struct Object_c4f850 {
    bool AddTo(Serializer_c4f850* serializer);
};

// @ 0x00c4f850
bool Object_c4f850::AddTo(Serializer_c4f850* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c4f850, L"cMissionEradicate");
}
