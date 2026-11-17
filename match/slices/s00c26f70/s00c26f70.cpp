// Serializer registration (0x00c26f70): add this object to the serializer as a child with the class descriptor at
// 0x15721f0 and the name L"cCreatureCitizen" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c26f70 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c26f70[];   // 0x015721f0 class descriptor

struct Object_c26f70 {
    bool AddTo(Serializer_c26f70* serializer);
};

// @ 0x00c26f70
bool Object_c26f70::AddTo(Serializer_c26f70* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c26f70, L"cCreatureCitizen");
}
