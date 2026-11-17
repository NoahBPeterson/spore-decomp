// Serializer registration (0x00ae7f60): add this object to the serializer as a child with the class descriptor at
// 0x1566c00 and the name L"cCommGraphicsManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ae7f60 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ae7f60[];   // 0x01566c00 class descriptor

struct Object_ae7f60 {
    bool AddTo(Serializer_ae7f60* serializer);
};

// @ 0x00ae7f60
bool Object_ae7f60::AddTo(Serializer_ae7f60* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_ae7f60, L"cCommGraphicsManager");
}
