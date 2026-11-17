// Serializer registration (0x00c3f570): add this object to the serializer as a child with the class descriptor at
// 0x1573d38 and the name L"cHitSphere" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c3f570 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c3f570[];   // 0x01573d38 class descriptor

struct Object_c3f570 {
    bool AddTo(Serializer_c3f570* serializer);
};

// @ 0x00c3f570
bool Object_c3f570::AddTo(Serializer_c3f570* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c3f570, L"cHitSphere");
}
