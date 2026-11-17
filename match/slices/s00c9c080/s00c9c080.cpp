// Serializer registration (0x00c9c080): add this object to the serializer as a child with the class descriptor at
// 0x157c3d0 and the name L"cTribeHut" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c9c080 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c9c080[];   // 0x0157c3d0 class descriptor

struct Object_c9c080 {
    bool AddTo(Serializer_c9c080* serializer);
};

// @ 0x00c9c080
bool Object_c9c080::AddTo(Serializer_c9c080* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c9c080, L"cTribeHut");
}
