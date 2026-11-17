// Serializer registration (0x0104c8d0): add this object to the serializer as a child with the class descriptor at
// 0x15b8850 and the name L"cSpaceToolData" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_104c8d0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_104c8d0[];   // 0x015b8850 class descriptor

struct Object_104c8d0 {
    bool AddTo(Serializer_104c8d0* serializer);
};

// @ 0x0104c8d0
bool Object_104c8d0::AddTo(Serializer_104c8d0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0xc), sDescriptor_104c8d0, L"cSpaceToolData");
}
