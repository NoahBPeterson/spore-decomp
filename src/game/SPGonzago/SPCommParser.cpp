// src/game/SPGonzago/SPCommParser.cpp -- migrated from slice(s) s00432830, s0041e730 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCommParser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern float g_defaultFloat;     // 0x015d1168
#pragma intrinsic(_InterlockedIncrement)

// ---- items of slice s0041e730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_defaultFloat;     // 0x015d1168
struct Property {
    char* data; unsigned pad[3]; unsigned short flags; unsigned short type;   // flags 0x10, type 0x12
    void* GetStorage() { if (flags & 0x30) { return data; } else if (type) return this; return 0; }
    bool* GetBool();
    int* GetInt();
    unsigned* GetUInt();
    float* GetFloat();
};
// ---- items of slice s0041e730 end

// ---- items of slice s00432830 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* target, long value);
extern "C" long __cdecl _InterlockedDecrement(long volatile* target);
#pragma intrinsic(_InterlockedExchange, _InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)
class Object {
public:
    virtual int   v0();
    virtual int   v1();
    virtual ~Object();                       // scalar deleting destructor (+8)
    volatile long mRef;
    int AddRef();       // 0x00432A50
    int Release();      // 0x00432A70
};
// ---- items of slice s00432830 end

// @ 0x0041ea70
float* Property::GetFloat()
{
    if (type == 13 || type == 0x10) { return (float*)GetStorage(); }
    return &g_defaultFloat;
}

// @ 0x00432a50
int Object::AddRef()
{
    return _InterlockedIncrement(&mRef);
}
