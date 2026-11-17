// Serializer registration (0x00bddc70): add this object to the serializer as a child with the class descriptor at
// 0x156ea28 and the name L"cCity" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bddc70 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bddc70[];   // 0x0156ea28 class descriptor

struct Object_bddc70 {
    bool AddTo(Serializer_bddc70* serializer);
};

// @ 0x00bddc70
bool Object_bddc70::AddTo(Serializer_bddc70* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bddc70, L"cCity");
}
