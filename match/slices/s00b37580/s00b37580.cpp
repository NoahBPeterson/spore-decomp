// Serializer registration (0x00b37580): add this object to the serializer as a child with the class descriptor at
// 0x15695a0 and the name L"cGameViewManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b37580 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b37580[];   // 0x015695a0 class descriptor

struct Object_b37580 {
    bool AddTo(Serializer_b37580* serializer);
};

// @ 0x00b37580
bool Object_b37580::AddTo(Serializer_b37580* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_b37580, L"cGameViewManager");
}
