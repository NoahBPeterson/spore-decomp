// Serializer registration (0x00c5a850): add this object to the serializer as a child with the class descriptor at
// 0x1576638 and the name L"cMissionMultiStep" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c5a850 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c5a850[];   // 0x01576638 class descriptor

struct Object_c5a850 {
    bool AddTo(Serializer_c5a850* serializer);
};

// @ 0x00c5a850
bool Object_c5a850::AddTo(Serializer_c5a850* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c5a850, L"cMissionMultiStep");
}
