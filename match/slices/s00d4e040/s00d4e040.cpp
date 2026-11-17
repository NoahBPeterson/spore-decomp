// Serializer registration (0x00d4e040): add this object to the serializer as a child with the class descriptor at
// 0x1583b00 and the name L"cDramaManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d4e040 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d4e040[];   // 0x01583b00 class descriptor

struct Object_d4e040 {
    bool AddTo(Serializer_d4e040* serializer);
};

// @ 0x00d4e040
bool Object_d4e040::AddTo(Serializer_d4e040* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_d4e040, L"cDramaManager");
}
