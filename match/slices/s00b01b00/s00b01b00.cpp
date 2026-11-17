// Serializer registration (0x00b01b00): add this object to the serializer as a child with the class descriptor at
// 0x167b858 and the name L"cFruitGroup" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b01b00 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b01b00[];   // 0x0167b858 class descriptor

struct Object_b01b00 {
    bool AddTo(Serializer_b01b00* serializer);
};

// @ 0x00b01b00
bool Object_b01b00::AddTo(Serializer_b01b00* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b01b00, L"cFruitGroup");
}
