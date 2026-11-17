// Serializer registration (0x00cb5c50): add this object to the serializer as a child with the class descriptor at
// 0x157e358 and the name L"cDefaultAoEArea" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cb5c50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cb5c50[];   // 0x0157e358 class descriptor

struct Object_cb5c50 {
    bool AddTo(Serializer_cb5c50* serializer);
};

// @ 0x00cb5c50
bool Object_cb5c50::AddTo(Serializer_cb5c50* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_cb5c50, L"cDefaultAoEArea");
}
