// Serializer registration (0x00c3bc60): add this object to the serializer as a child with the class descriptor at
// 0x1573290 and the name L"cGameDataUFO" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c3bc60 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c3bc60[];   // 0x01573290 class descriptor

struct Object_c3bc60 {
    bool AddTo(Serializer_c3bc60* serializer);
};

// @ 0x00c3bc60
bool Object_c3bc60::AddTo(Serializer_c3bc60* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c3bc60, L"cGameDataUFO");
}
