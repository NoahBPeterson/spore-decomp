// Serializer registration (0x00b1e4b0): add this object to the serializer as a child with the class descriptor at
// 0x15761d0 and the name L"cGenericPressureEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b1e4b0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b1e4b0[];   // 0x015761d0 class descriptor

struct Object_b1e4b0 {
    bool AddTo(Serializer_b1e4b0* serializer);
};

// @ 0x00b1e4b0
bool Object_b1e4b0::AddTo(Serializer_b1e4b0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b1e4b0, L"cGenericPressureEvent");
}
