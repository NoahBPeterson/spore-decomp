// Serializer registration (0x00cd7fe0): add this object to the serializer as a child with the class descriptor at
// 0x157f290 and the name L"cTribeModeStrategy" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cd7fe0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cd7fe0[];   // 0x0157f290 class descriptor

struct Object_cd7fe0 {
    bool AddTo(Serializer_cd7fe0* serializer);
};

// @ 0x00cd7fe0
bool Object_cd7fe0::AddTo(Serializer_cd7fe0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0xc), sDescriptor_cd7fe0, L"cTribeModeStrategy");
}
