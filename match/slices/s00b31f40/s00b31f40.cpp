// Serializer registration (0x00b31f40): add this object to the serializer as a child with the class descriptor at
// 0x1569130 and the name L"cGameTimeManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b31f40 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b31f40[];   // 0x01569130 class descriptor

struct Object_b31f40 {
    bool AddTo(Serializer_b31f40* serializer);
};

// @ 0x00b31f40
bool Object_b31f40::AddTo(Serializer_b31f40* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b31f40, L"cGameTimeManager");
}
