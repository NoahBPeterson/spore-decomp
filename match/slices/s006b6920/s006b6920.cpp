// slice s006b6920: SP::cStringManager and its neighbours.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned short wchar16;

namespace SP {

struct cString;
struct cStringDetokenizer;

// A minimal hash-set stub (retail layout at cStringManager+0x04).
struct InsertTag {};

struct StringSet {
    int erase(cString** key);
    void insert(char* out, cString** key, InsertTag tag);
};

struct IStringManagerBase {
    virtual void b0();
};

struct cStringManager : IStringManagerBase {
    virtual bool AddString(cString* p);      // vtable slot 1
    virtual bool RemoveString(cString* p);   // vtable slot 2 (see 6b5240)

    StringSet mStringList;             // +0x04
    uint32_t  mPad24;                  // +0x24
    uint32_t  mPad28;                  // +0x28
};

} // namespace SP

// @ 0x006b69e0
bool SP::cStringManager::RemoveString(SP::cString* p)
{
    mStringList.erase(&p);
    return true;
}

// @ 0x006b6e50
bool SP::cStringManager::AddString(SP::cString* p)
{
    char result[12];
    mStringList.insert(result, &p, InsertTag());
    return true;
}

// ---------------------------------------------------------------------------
// Partial reconstructions of the remaining functions (see partial.txt).
// ---------------------------------------------------------------------------

// @ 0x006b6920
void FUN_006b6920() {}

// @ 0x006b6a00
void FUN_006b6a00() {}

// @ 0x006b6a70
void FUN_006b6a70() {}

// @ 0x006b6af0
void FUN_006b6af0() {}

// @ 0x006b6b70
void FUN_006b6b70() {}

// @ 0x006b6bf0
void FUN_006b6bf0() {}

// @ 0x006b6d10
void FUN_006b6d10() {}

// @ 0x006b6e80
void FUN_006b6e80() {}

// @ 0x006b6f80
void FUN_006b6f80() {}

// @ 0x006b7180
void FUN_006b7180() {}

// @ 0x006b7320
void FUN_006b7320() {}

// @ 0x006b7380
void FUN_006b7380() {}

// @ 0x006b73e0
void FUN_006b73e0() {}

// @ 0x006b7430
void FUN_006b7430() {}
