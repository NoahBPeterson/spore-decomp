// Serializer registration (0x0103d050): add this object to the serializer as a child with the class descriptor at
// 0x15b8140 and the name L"cNPCStore" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_103d050 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_103d050[];   // 0x015b8140 class descriptor

struct Object_103d050 {
    bool AddTo(Serializer_103d050* serializer);
};

// @ 0x0103d050
bool Object_103d050::AddTo(Serializer_103d050* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_103d050, L"cNPCStore");
}
