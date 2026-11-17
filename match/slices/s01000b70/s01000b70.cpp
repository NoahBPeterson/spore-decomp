// Serializer registration (0x01000b70): add this object to the serializer as a child with the class descriptor at
// 0x15b6378 and the name L"cSimulatorPlayerUFO" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_1000b70 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_1000b70[];   // 0x015b6378 class descriptor

struct Object_1000b70 {
    bool AddTo(Serializer_1000b70* serializer);
};

// @ 0x01000b70
bool Object_1000b70::AddTo(Serializer_1000b70* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_1000b70, L"cSimulatorPlayerUFO");
}
