// Serializer registration (0x00c405a0): add this object to the serializer as a child with the class descriptor at
// 0x1573fe0 and the name L"cInteractiveOrnament" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c405a0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c405a0[];   // 0x01573fe0 class descriptor

struct Object_c405a0 {
    bool AddTo(Serializer_c405a0* serializer);
};

// @ 0x00c405a0
bool Object_c405a0::AddTo(Serializer_c405a0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c405a0, L"cInteractiveOrnament");
}
