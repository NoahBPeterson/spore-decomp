// Serializer registration (0x00cfeb10): add this object to the serializer as a child with the class descriptor at
// 0x1581d40 and the name L"cEventLogCommItem" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cfeb10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cfeb10[];   // 0x01581d40 class descriptor

struct Object_cfeb10 {
    bool AddTo(Serializer_cfeb10* serializer);
};

// @ 0x00cfeb10
bool Object_cfeb10::AddTo(Serializer_cfeb10* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_cfeb10, L"cEventLogCommItem");
}
