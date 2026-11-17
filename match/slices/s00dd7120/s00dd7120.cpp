// Serializer registration (0x00dd7120): add this object to the serializer as a child with the class descriptor at
// 0x15a2cb0 and the name L"cUIEventLog" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_dd7120 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_dd7120[];   // 0x015a2cb0 class descriptor

struct Object_dd7120 {
    bool AddTo(Serializer_dd7120* serializer);
};

// @ 0x00dd7120
bool Object_dd7120::AddTo(Serializer_dd7120* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_dd7120, L"cUIEventLog");
}
