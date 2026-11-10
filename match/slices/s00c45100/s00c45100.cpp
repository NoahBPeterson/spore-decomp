// Slice s00c45100: property/field registration helpers used by mission serializers.
// 0x00695b40 is Register(pValue, pData, pName) on a serializer-like object.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

struct Serializer {
    void Register(void* pValue, void* pData, void* pName);  // 0x00695b40
};

// @ 0x00c45100
bool FUN_00c45100(Serializer* self, void* pValue)
{
    if (pValue)
        self->Register(pValue, (void*)0x01574c48, (void*)0x0146d138);
    return true;
}

// @ 0x00c45120
bool FUN_00c45120(Serializer* self, void* pValue)
{
    if (pValue)
        self->Register(pValue, (void*)0x01574d38, (void*)0x0146d14c);
    return true;
}
