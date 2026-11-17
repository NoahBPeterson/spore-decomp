// Serializer registration (0x00b26f80): add this object to the serializer as a child with the class descriptor at
// 0x1568b08 and the name L"cSavedGameHeader" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b26f80 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b26f80[];   // 0x01568b08 class descriptor

struct Object_b26f80 {
    bool AddTo(Serializer_b26f80* serializer);
};

// @ 0x00b26f80
bool Object_b26f80::AddTo(Serializer_b26f80* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b26f80, L"cSavedGameHeader");
}
