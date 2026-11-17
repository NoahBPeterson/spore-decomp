// Serializer registration (0x00eab460): add this object to the serializer as a child with the class descriptor at
// 0x15a9018 and the name L"cNPCCityMusic" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_eab460 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_eab460[];   // 0x015a9018 class descriptor

struct Object_eab460 {
    bool AddTo(Serializer_eab460* serializer);
};

// @ 0x00eab460
bool Object_eab460::AddTo(Serializer_eab460* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_eab460, L"cNPCCityMusic");
}
