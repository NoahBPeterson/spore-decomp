// Serializer registration (0x00c62d20): add this object to the serializer as a child with the class descriptor at
// 0x1577678 and the name L"cMissionWar" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c62d20 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c62d20[];   // 0x01577678 class descriptor

struct Object_c62d20 {
    bool AddTo(Serializer_c62d20* serializer);
};

// @ 0x00c62d20
bool Object_c62d20::AddTo(Serializer_c62d20* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c62d20, L"cMissionWar");
}
