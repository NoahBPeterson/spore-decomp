// Serializer registration (0x00bba1e0): add this object to the serializer as a child with the class descriptor at
// 0x156cb70 and the name L"cStarRecord" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bba1e0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bba1e0[];   // 0x0156cb70 class descriptor

struct Object_bba1e0 {
    bool AddTo(Serializer_bba1e0* serializer);
};

// @ 0x00bba1e0
bool Object_bba1e0::AddTo(Serializer_bba1e0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bba1e0, L"cStarRecord");
}
