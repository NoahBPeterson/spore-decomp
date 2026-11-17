// Serializer registration (0x00675e50): add this object to the serializer as a child with the class descriptor at
// 0x1529330 and the name L"cSPAchievementSerializer" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_675e50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_675e50[];   // 0x01529330 class descriptor

struct Object_675e50 {
    bool AddTo(Serializer_675e50* serializer);
};

// @ 0x00675e50
bool Object_675e50::AddTo(Serializer_675e50* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_675e50, L"cSPAchievementSerializer");
}
