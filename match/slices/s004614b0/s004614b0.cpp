// Slice s004614b0: editor util lookup / creature-model registration helpers.
// /Od /Ob1 /MD /Gy /TP.
#include "types.h"

extern unsigned char g_byte_15d3c30;

extern "C" void* FUN_00461520(const void* key);       // 0x461520 (defined below)
extern "C" void  FUN_009fc0f0(void* p);               // 0x9fc0f0
extern "C" void  FUN_0052a400(int a, unsigned int b, unsigned int c, int d, int e, int f); // 0x52a400
extern "C" void  FUN_00473300(void* p);               // 0x473300
extern "C" void  WString_FreeBuffer(void* p);         // 0x4237d0
extern "C" void  Counted_Release(void* p);            // 0x40f360
extern "C" void* LowerBound12(void* start, void* end, const void* key, int flag); // 0x422430

extern char g_table_150c050;
extern int  g_count_13ec430;
extern char g_unknown[];

// =====================================================================
// @ 0x461510  return a global flag byte
// =====================================================================
unsigned char GetGlobalFlag()
{
    return g_byte_15d3c30;
}

// =====================================================================
// @ 0x461520  table lower_bound lookup returning a name (or "unknown")
// =====================================================================
struct TableEntry {
    int         key;
    const char* name;
    char        pad[4];
};

const char* LookupName(int key)
{
    TableEntry* start = (TableEntry*)&g_table_150c050;
    TableEntry* end = (TableEntry*)((char*)&g_table_150c050 + g_count_13ec430 * 0xc);
    TableEntry* it = (TableEntry*)LowerBound12(start, end, &key, 0);
    TableEntry* found = end;
    if (it != end && !(key < it->key)) {
        found = it;
    }
    if (found == end) {
        return "unknown";
    }
    return found->name;
}

// =====================================================================
// @ 0x4615b0  lookup + consume
// =====================================================================
void UseName(int key)
{
    void* p = (void*)LookupName(key);
    FUN_009fc0f0(p);
    return;
}

// =====================================================================
// @ 0x4614b0  destructor for the string-holder object
// =====================================================================
struct IRefObj {
    virtual void v0();
    virtual void Release();   // +0x04
};

struct Holder {
    char  pad0[4];
    char  str[0x24];     // +0x04  (string buffer)
    char  sub[0x14];     // +0x28
    void* p3c;           // +0x3c
    char  pad40[4];
    IRefObj* p44;        // +0x40
    void Dtor();
};

void Holder::Dtor()
{
    if (p44 != 0) {
        p44->Release();
    }
    if (p3c != 0) {
        Counted_Release(p3c);
    }
    FUN_00473300(sub);
    WString_FreeBuffer(str);
    return;
}

// =====================================================================
// @ 0x4615e0  SP::EditorUtils::RegisterCreatureModels  (bitfield packing)
// =====================================================================
union Bits {
    unsigned int raw;
    struct {
        unsigned int lo : 8;
        unsigned int mid : 8;
        unsigned int hi : 16;
    } f;
};

void RegisterCreatureModels(int a, unsigned int flags, int c, int d, int e)
{
    Bits x;
    x.raw = flags;
    x.f.mid = 0x29;
    x.f.lo = 1;
    Bits y;
    y.raw = flags;
    y.f.mid = 0x29;
    y.f.lo = 0;
    FUN_0052a400(a, y.raw, x.raw, c, d, e);
    return;
}
