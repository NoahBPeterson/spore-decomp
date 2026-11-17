// Serializer registration (0x00ac4d20): add this object to the serializer as a child with the class descriptor at
// 0x1565bac and the name L"cAStar" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ac4d20 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ac4d20[];   // 0x01565bac class descriptor

struct Object_ac4d20 {
    bool AddTo(Serializer_ac4d20* serializer);
};

// @ 0x00ac4d20
bool Object_ac4d20::AddTo(Serializer_ac4d20* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_ac4d20, L"cAStar");
}
