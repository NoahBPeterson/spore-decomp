// Serializer registration (0x00d004f0): add this object to the serializer as a child with the class descriptor at
// 0x1581ec8 and the name L"cCivMissionManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d004f0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d004f0[];   // 0x01581ec8 class descriptor

struct Object_d004f0 {
    bool AddTo(Serializer_d004f0* serializer);
};

// @ 0x00d004f0
bool Object_d004f0::AddTo(Serializer_d004f0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_d004f0, L"cCivMissionManager");
}
