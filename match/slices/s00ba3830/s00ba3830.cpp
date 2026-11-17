// Serializer registration (0x00ba3830): add this object to the serializer as a child with the class descriptor at
// 0x156c370 and the name L"cSpeciesRelationshipManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ba3830 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ba3830[];   // 0x0156c370 class descriptor

struct Object_ba3830 {
    bool AddTo(Serializer_ba3830* serializer);
};

// @ 0x00ba3830
bool Object_ba3830::AddTo(Serializer_ba3830* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_ba3830, L"cSpeciesRelationshipManager");
}
