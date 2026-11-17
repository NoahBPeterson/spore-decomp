// Serializer registration (0x00e300b0): add this object to the serializer as a child with the class descriptor at
// 0x15a5754 and the name L"cUIAssetDiscoveryManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_e300b0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_e300b0[];   // 0x015a5754 class descriptor

struct Object_e300b0 {
    bool AddTo(Serializer_e300b0* serializer);
};

// @ 0x00e300b0
bool Object_e300b0::AddTo(Serializer_e300b0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_e300b0, L"cUIAssetDiscoveryManager");
}
