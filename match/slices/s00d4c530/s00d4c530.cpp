// Serializer registration (0x00d4c530): add this object to the serializer as a child with the class descriptor at
// 0x1583a4c and the name L"cSeaMonsterEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d4c530 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d4c530[];   // 0x01583a4c class descriptor

struct Object_d4c530 {
    bool AddTo(Serializer_d4c530* serializer);
};

// @ 0x00d4c530
bool Object_d4c530::AddTo(Serializer_d4c530* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_d4c530, L"cSeaMonsterEvent");
}
