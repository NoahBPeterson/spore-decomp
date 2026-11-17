// Serializer registration (0x00ae5800): add this object to the serializer as a child with the class descriptor at
// 0x15669f0 and the name L"cCitySimulator" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ae5800 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ae5800[];   // 0x015669f0 class descriptor

struct Object_ae5800 {
    bool AddTo(Serializer_ae5800* serializer);
};

// @ 0x00ae5800
bool Object_ae5800::AddTo(Serializer_ae5800* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_ae5800, L"cCitySimulator");
}
