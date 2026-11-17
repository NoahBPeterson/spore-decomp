// Serializer registration (0x00b0bcd0): add this object to the serializer as a child with the class descriptor at
// 0x1567a80 and the name L"cFruitManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b0bcd0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b0bcd0[];   // 0x01567a80 class descriptor

struct Object_b0bcd0 {
    bool AddTo(Serializer_b0bcd0* serializer);
};

// @ 0x00b0bcd0
bool Object_b0bcd0::AddTo(Serializer_b0bcd0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_b0bcd0, L"cFruitManager");
}
