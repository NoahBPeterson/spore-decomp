// Serializer registration (0x00d04e10): add this object to the serializer as a child with the class descriptor at
// 0x1581f50 and the name L"cRelationshipManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d04e10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d04e10[];   // 0x01581f50 class descriptor

struct Object_d04e10 {
    bool AddTo(Serializer_d04e10* serializer);
};

// @ 0x00d04e10
bool Object_d04e10::AddTo(Serializer_d04e10* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0xc), sDescriptor_d04e10, L"cRelationshipManager");
}
