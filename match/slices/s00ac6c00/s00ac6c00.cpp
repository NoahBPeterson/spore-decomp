// Serializer registration (0x00ac6c00): add this object to the serializer as a child with the class descriptor at
// 0x1565c14 and the name L"cBlobShadowManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ac6c00 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ac6c00[];   // 0x01565c14 class descriptor

struct Object_ac6c00 {
    bool AddTo(Serializer_ac6c00* serializer);
};

// @ 0x00ac6c00
bool Object_ac6c00::AddTo(Serializer_ac6c00* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_ac6c00, L"cBlobShadowManager");
}
