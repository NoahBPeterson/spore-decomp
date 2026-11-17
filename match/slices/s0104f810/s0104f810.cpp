// Serializer registration (0x0104f810): add this object to the serializer as a child with the class descriptor at
// 0x15b8c4c and the name L"cToolManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_104f810 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_104f810[];   // 0x015b8c4c class descriptor

struct Object_104f810 {
    bool AddTo(Serializer_104f810* serializer);
};

// @ 0x0104f810
bool Object_104f810::AddTo(Serializer_104f810* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_104f810, L"cToolManager");
}
