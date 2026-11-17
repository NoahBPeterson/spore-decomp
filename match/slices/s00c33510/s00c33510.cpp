// Serializer registration (0x00c33510): add this object to the serializer as a child with the class descriptor at
// 0x1572b60 and the name L"cEmpire" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c33510 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c33510[];   // 0x01572b60 class descriptor

struct Object_c33510 {
    bool AddTo(Serializer_c33510* serializer);
};

// @ 0x00c33510
bool Object_c33510::AddTo(Serializer_c33510* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c33510, L"cEmpire");
}
