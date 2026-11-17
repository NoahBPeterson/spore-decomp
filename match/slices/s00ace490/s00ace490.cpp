// Serializer registration (0x00ace490): add this object to the serializer as a child with the class descriptor at
// 0x1565d68 and the name L"cCastingManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ace490 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ace490[];   // 0x01565d68 class descriptor

struct Object_ace490 {
    bool AddTo(Serializer_ace490* serializer);
};

// @ 0x00ace490
bool Object_ace490::AddTo(Serializer_ace490* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_ace490, L"cCastingManager");
}
