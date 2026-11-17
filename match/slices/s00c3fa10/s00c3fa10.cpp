// Serializer registration (0x00c3fa10): add this object to the serializer as a child with the class descriptor at
// 0x1573ee8 and the name L"cInteractableObject" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c3fa10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c3fa10[];   // 0x01573ee8 class descriptor

struct Object_c3fa10 {
    bool AddTo(Serializer_c3fa10* serializer);
};

// @ 0x00c3fa10
bool Object_c3fa10::AddTo(Serializer_c3fa10* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c3fa10, L"cInteractableObject");
}
