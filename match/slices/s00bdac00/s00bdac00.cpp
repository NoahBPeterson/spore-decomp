// Serializer registration (0x00bdac00): add this object to the serializer as a child with the class descriptor at
// 0x156e2a0 and the name L"cCulturalTarget" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bdac00 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bdac00[];   // 0x0156e2a0 class descriptor

struct Object_bdac00 {
    bool AddTo(Serializer_bdac00* serializer);
};

// @ 0x00bdac00
bool Object_bdac00::AddTo(Serializer_bdac00* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bdac00, L"cCulturalTarget");
}
