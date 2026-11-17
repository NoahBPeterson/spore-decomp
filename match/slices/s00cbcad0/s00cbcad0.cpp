// Serializer registration (0x00cbcad0): add this object to the serializer as a child with the class descriptor at
// 0x157d890 and the name L"cDefaultToolProjectile" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cbcad0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cbcad0[];   // 0x0157d890 class descriptor

struct Object_cbcad0 {
    bool AddTo(Serializer_cbcad0* serializer);
};

// @ 0x00cbcad0
bool Object_cbcad0::AddTo(Serializer_cbcad0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_cbcad0, L"cDefaultToolProjectile");
}
