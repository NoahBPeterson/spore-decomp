// Serializer registration (0x00cb9540): add this object to the serializer as a child with the class descriptor at
// 0x157e888 and the name L"cICBM" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cb9540 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cb9540[];   // 0x0157e888 class descriptor

struct Object_cb9540 {
    bool AddTo(Serializer_cb9540* serializer);
};

// @ 0x00cb9540
bool Object_cb9540::AddTo(Serializer_cb9540* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_cb9540, L"cICBM");
}
