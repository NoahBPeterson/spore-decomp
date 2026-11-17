// Serializer registration (0x00c8b680): add this object to the serializer as a child with the class descriptor at
// 0x157a828 and the name L"cStar" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c8b680 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c8b680[];   // 0x0157a828 class descriptor

struct Object_c8b680 {
    bool AddTo(Serializer_c8b680* serializer);
};

// @ 0x00c8b680
bool Object_c8b680::AddTo(Serializer_c8b680* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c8b680, L"cStar");
}
