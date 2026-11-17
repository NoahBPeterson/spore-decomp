// Serializer registration (0x00c012c0): add this object to the serializer as a child with the class descriptor at
// 0x15710b8 and the name L"cCommunity" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c012c0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c012c0[];   // 0x015710b8 class descriptor

struct Object_c012c0 {
    bool AddTo(Serializer_c012c0* serializer);
};

// @ 0x00c012c0
bool Object_c012c0::AddTo(Serializer_c012c0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c012c0, L"cCommunity");
}
