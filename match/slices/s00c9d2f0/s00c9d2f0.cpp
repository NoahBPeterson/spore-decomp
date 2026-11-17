// Serializer registration (0x00c9d2f0): add this object to the serializer as a child with the class descriptor at
// 0x157c5d0 and the name L"cTribeTool" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c9d2f0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c9d2f0[];   // 0x0157c5d0 class descriptor

struct Object_c9d2f0 {
    bool AddTo(Serializer_c9d2f0* serializer);
};

// @ 0x00c9d2f0
bool Object_c9d2f0::AddTo(Serializer_c9d2f0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c9d2f0, L"cTribeTool");
}
