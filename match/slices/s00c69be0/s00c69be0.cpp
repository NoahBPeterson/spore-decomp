// @ 0x00c69be0
#include "game/types.h"

namespace SP {
class cNest {
 public:
  int WriteAsText(void* pData);   // 0x00c69be0 (ret 4)
};
}

// 0x00b18420 cGameData::GetFieldValues (ret 4)
struct FnB18420 { int __thiscall f(void* pData); };

// cVarListSerializer stack image (0xa14 bytes); only the two calls this function makes are named.
struct CVarListSer {
    uint32_t mPad00[0x14 / 4];
    void ctor(void* pOwner, void* pFields, int nFlags);   // 0x00692f90
    int  GetFields(void* pOut);                           // 0x00695960
};

int SP::cNest::WriteAsText(void* pData)
{
    uint8_t serA[0xa14];
    uint8_t serB[0xa14];
    int n = ((FnB18420*)this)->f(pData);
    ((CVarListSer*)serA)->ctor((char*)this + 0x34, (void*)0x157a1f8, 0x1a80d26);
    n += ((CVarListSer*)serA)->GetFields(pData);
    ((CVarListSer*)serB)->ctor(this, (void*)0x1577a98, 0x1a80d26);
    n += ((CVarListSer*)serB)->GetFields(pData);
    return n;
}
