// Serializer registration (0x00b1d920): add this object to the serializer as a child with the class descriptor at
// 0x156840c and the name L"cGameModeManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b1d920 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b1d920[];   // 0x0156840c class descriptor

struct Object_b1d920 {
    bool AddTo(Serializer_b1d920* serializer);
};

// @ 0x00b1d920
bool Object_b1d920::AddTo(Serializer_b1d920* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b1d920, L"cGameModeManager");
}
