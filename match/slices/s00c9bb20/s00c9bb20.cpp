// Serializer registration (0x00c9bb20): add this object to the serializer as a child with the class descriptor at
// 0x157c320 and the name L"cTribeFoodMat" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c9bb20 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c9bb20[];   // 0x0157c320 class descriptor

struct Object_c9bb20 {
    bool AddTo(Serializer_c9bb20* serializer);
};

// @ 0x00c9bb20
bool Object_c9bb20::AddTo(Serializer_c9bb20* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c9bb20, L"cTribeFoodMat");
}
