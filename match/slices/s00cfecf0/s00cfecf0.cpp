// Serializer registration (0x00cfecf0): add this object to the serializer as a child with the class descriptor at
// 0x1581cc8 and the name L"cEventLogCommManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cfecf0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cfecf0[];   // 0x01581cc8 class descriptor

struct Object_cfecf0 {
    bool AddTo(Serializer_cfecf0* serializer);
};

// @ 0x00cfecf0
bool Object_cfecf0::AddTo(Serializer_cfecf0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_cfecf0, L"cEventLogCommManager");
}
