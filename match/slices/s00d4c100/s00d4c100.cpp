// Serializer registration (0x00d4c100): add this object to the serializer as a child with the class descriptor at
// 0x158395c and the name L"cUFOAbductionEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d4c100 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d4c100[];   // 0x0158395c class descriptor

struct Object_d4c100 {
    bool AddTo(Serializer_d4c100* serializer);
};

// @ 0x00d4c100
bool Object_d4c100::AddTo(Serializer_d4c100* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_d4c100, L"cUFOAbductionEvent");
}
