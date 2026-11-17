// Serializer registration (0x00ac78d0): add this object to the serializer as a child with the class descriptor at
// 0x1565c60 and the name L"cBundleManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ac78d0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ac78d0[];   // 0x01565c60 class descriptor

struct Object_ac78d0 {
    bool AddTo(Serializer_ac78d0* serializer);
};

// @ 0x00ac78d0
bool Object_ac78d0::AddTo(Serializer_ac78d0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_ac78d0, L"cBundleManager");
}
