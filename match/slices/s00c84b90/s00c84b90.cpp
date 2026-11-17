// Serializer registration (0x00c84b90): add this object to the serializer as a child with the class descriptor at
// 0x1579d78 and the name L"cSolarSystem" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c84b90 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c84b90[];   // 0x01579d78 class descriptor

struct Object_c84b90 {
    bool AddTo(Serializer_c84b90* serializer);
};

// @ 0x00c84b90
bool Object_c84b90::AddTo(Serializer_c84b90* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_c84b90, L"cSolarSystem");
}
