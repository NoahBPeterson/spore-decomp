// Serializer registration (0x00b26e80): add this object to the serializer as a child with the class descriptor at
// 0x1568ac8 and the name L"cGamePersistenceManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b26e80 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b26e80[];   // 0x01568ac8 class descriptor

struct Object_b26e80 {
    bool AddTo(Serializer_b26e80* serializer);
};

// @ 0x00b26e80
bool Object_b26e80::AddTo(Serializer_b26e80* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_b26e80, L"cGamePersistenceManager");
}
