// Serializer registration (0x01016040): add this object to the serializer as a child with the class descriptor at
// 0x15b6d4c and the name L"cSimulatorWalkAround" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_1016040 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_1016040[];   // 0x015b6d4c class descriptor

struct Object_1016040 {
    bool AddTo(Serializer_1016040* serializer);
};

// @ 0x01016040
bool Object_1016040::AddTo(Serializer_1016040* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_1016040, L"cSimulatorWalkAround");
}
