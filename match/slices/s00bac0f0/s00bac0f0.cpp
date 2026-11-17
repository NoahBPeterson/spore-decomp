// Serializer registration (0x00bac0f0): add this object to the serializer as a child with the class descriptor at
// 0x156cb18 and the name L"cStarManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bac0f0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bac0f0[];   // 0x0156cb18 class descriptor

struct Object_bac0f0 {
    bool AddTo(Serializer_bac0f0* serializer);
};

// @ 0x00bac0f0
bool Object_bac0f0::AddTo(Serializer_bac0f0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bac0f0, L"cStarManager");
}
