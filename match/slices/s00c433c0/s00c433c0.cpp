// Serializer registration (0x00c433c0): add this object to the serializer as a child with the class descriptor at
// 0x1574258 and the name L"cLocomotiveObject" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c433c0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c433c0[];   // 0x01574258 class descriptor

struct Object_c433c0 {
    bool AddTo(Serializer_c433c0* serializer);
};

// @ 0x00c433c0
bool Object_c433c0::AddTo(Serializer_c433c0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c433c0, L"cLocomotiveObject");
}
