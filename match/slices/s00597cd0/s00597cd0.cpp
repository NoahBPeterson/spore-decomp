// Serializer registration (0x00597cd0): add this object to the serializer as a child with the class descriptor at
// 0x150d5e8 and the name L"cCollectableItems" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_597cd0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_597cd0[];   // 0x0150d5e8 class descriptor

struct Object_597cd0 {
    bool AddTo(Serializer_597cd0* serializer);
};

// @ 0x00597cd0
bool Object_597cd0::AddTo(Serializer_597cd0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_597cd0, L"cCollectableItems");
}
