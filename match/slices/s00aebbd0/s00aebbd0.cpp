// Serializer registration (0x00aebbd0): add this object to the serializer as a child with the class descriptor at
// 0x1566cf8 and the name L"cCommManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_aebbd0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_aebbd0[];   // 0x01566cf8 class descriptor

struct Object_aebbd0 {
    bool AddTo(Serializer_aebbd0* serializer);
};

// @ 0x00aebbd0
bool Object_aebbd0::AddTo(Serializer_aebbd0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_aebbd0, L"cCommManager");
}
