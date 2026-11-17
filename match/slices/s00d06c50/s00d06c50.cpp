// Serializer registration (0x00d06c50): add this object to the serializer as a child with the class descriptor at
// 0x15820f8 and the name L"cSoundLoopObject" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d06c50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d06c50[];   // 0x015820f8 class descriptor

struct Object_d06c50 {
    bool AddTo(Serializer_d06c50* serializer);
};

// @ 0x00d06c50
bool Object_d06c50::AddTo(Serializer_d06c50* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_d06c50, L"cSoundLoopObject");
}
