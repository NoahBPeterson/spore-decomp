// Serializer registration (0x00ba2040): add this object to the serializer as a child with the class descriptor at
// 0x156c0b8 and the name L"cSimTicker" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ba2040 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ba2040[];   // 0x0156c0b8 class descriptor

struct Object_ba2040 {
    bool AddTo(Serializer_ba2040* serializer);
};

// @ 0x00ba2040
bool Object_ba2040::AddTo(Serializer_ba2040* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_ba2040, L"cSimTicker");
}
