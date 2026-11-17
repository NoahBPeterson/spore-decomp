// Serializer registration (0x00c60740): add this object to the serializer as a child with the class descriptor at
// 0x1577210 and the name L"cMissionTerraform" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c60740 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c60740[];   // 0x01577210 class descriptor

struct Object_c60740 {
    bool AddTo(Serializer_c60740* serializer);
};

// @ 0x00c60740
bool Object_c60740::AddTo(Serializer_c60740* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c60740, L"cMissionTerraform");
}
