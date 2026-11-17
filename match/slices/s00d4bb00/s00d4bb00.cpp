// Serializer registration (0x00d4bb00): add this object to the serializer as a child with the class descriptor at
// 0x1583a10 and the name L"cRainStormEvent" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d4bb00 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d4bb00[];   // 0x01583a10 class descriptor

struct Object_d4bb00 {
    bool AddTo(Serializer_d4bb00* serializer);
};

// @ 0x00d4bb00
bool Object_d4bb00::AddTo(Serializer_d4bb00* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_d4bb00, L"cRainStormEvent");
}
