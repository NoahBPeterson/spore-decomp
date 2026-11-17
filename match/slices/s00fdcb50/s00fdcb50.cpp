// Serializer registration (0x00fdcb50): add this object to the serializer as a child with the class descriptor at
// 0x15b4148 and the name L"cAppModeSpace" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_fdcb50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_fdcb50[];   // 0x015b4148 class descriptor

struct Object_fdcb50 {
    bool AddTo(Serializer_fdcb50* serializer);
};

// @ 0x00fdcb50
bool Object_fdcb50::AddTo(Serializer_fdcb50* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_fdcb50, L"cAppModeSpace");
}
