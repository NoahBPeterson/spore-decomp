// Serializer registration (0x00c3e610): add this object to the serializer as a child with the class descriptor at
// 0x1573a60 and the name L"cGamePlant" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c3e610 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c3e610[];   // 0x01573a60 class descriptor

struct Object_c3e610 {
    bool AddTo(Serializer_c3e610* serializer);
};

// @ 0x00c3e610
bool Object_c3e610::AddTo(Serializer_c3e610* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c3e610, L"cGamePlant");
}
