// Serializer registration (0x00b0d6e0): add this object to the serializer as a child with the class descriptor at
// 0x1567d18 and the name L"cGameBehaviorManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b0d6e0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b0d6e0[];   // 0x01567d18 class descriptor

struct Object_b0d6e0 {
    bool AddTo(Serializer_b0d6e0* serializer);
};

// @ 0x00b0d6e0
bool Object_b0d6e0::AddTo(Serializer_b0d6e0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_b0d6e0, L"cGameBehaviorManager");
}
