// Serializer registration (0x00b26b90): add this object to the serializer as a child with the class descriptor at
// 0x1568a8c and the name L"cHerdEffects__DEPRECATED" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b26b90 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b26b90[];   // 0x01568a8c class descriptor

struct Object_b26b90 {
    bool AddTo(Serializer_b26b90* serializer);
};

// @ 0x00b26b90
bool Object_b26b90::AddTo(Serializer_b26b90* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_b26b90, L"cHerdEffects__DEPRECATED");
}
