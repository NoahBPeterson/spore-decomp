// Serializer registration (0x00cc56c0): add this object to the serializer as a child with the class descriptor at
// 0x157ea38 and the name L"cNpcTribeController" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cc56c0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cc56c0[];   // 0x0157ea38 class descriptor

struct Object_cc56c0 {
    bool AddTo(Serializer_cc56c0* serializer);
};

// @ 0x00cc56c0
bool Object_cc56c0::AddTo(Serializer_cc56c0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_cc56c0, L"cNpcTribeController");
}
