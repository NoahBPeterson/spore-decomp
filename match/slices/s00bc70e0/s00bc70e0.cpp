// Serializer registration (0x00bc70e0): add this object to the serializer as a child with the class descriptor at
// 0x156d254 and the name L"cVignetteManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bc70e0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bc70e0[];   // 0x0156d254 class descriptor

struct Object_bc70e0 {
    bool AddTo(Serializer_bc70e0* serializer);
};

// @ 0x00bc70e0
bool Object_bc70e0::AddTo(Serializer_bc70e0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bc70e0, L"cVignetteManager");
}
