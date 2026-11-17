// Serializer registration (0x01037280): add this object to the serializer as a child with the class descriptor at
// 0x15b7cac and the name L"cSpaceGfx" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_1037280 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_1037280[];   // 0x015b7cac class descriptor

struct Object_1037280 {
    bool AddTo(Serializer_1037280* serializer);
};

// @ 0x01037280
bool Object_1037280::AddTo(Serializer_1037280* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_1037280, L"cSpaceGfx");
}
