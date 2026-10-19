// src/game/UTFSpore_Win32/ListItem.cpp -- migrated from slice(s) s00614f20 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ListItem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "SP/Pollen/cAssetDirectory.h"
#include "SP/Pollen/cAssetMetadata.h"
#include "SP/Pollen/cModelUploadTransaction.h"
#include "SP/Pollen/cServerResponse.h"
#include "SP/Pollen/cTransactionQueue.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#include <intrin.h>
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(wcscmp)

// ---- items of slice s00614f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0 (EASTL allocate)
struct IFactory { virtual void slot0(); virtual int AddRef(); virtual int Release(); };
template <typename T> struct RefPtr {
    T* p;
    RefPtr() : p(0) {}
    void AssignOutOfLine(T* o);   // 0x00572620 (out-of-line AutoRefCount::operator=)
    __forceinline RefPtr& operator=(T* o) {
        if (o != p) {
            T* t = p;
            if (o) o->AddRef();
            p = o;
            if (t) t->Release();
        }
        return *this;
    }
};
struct cThrottleObj : IFactory { int mnRef; cThrottleObj(); };    // 0x0093c430
struct cThrottleOwner { char pad[0x43c]; int mnCount; char pad2[0xf3c - 0x440]; RefPtr<IFactory> mpThrottle; };
// ---- items of slice s00614f20 end

// @ 0x00615c70
bool __stdcall UpdateThrottle(cThrottleOwner* o)
{
    if (o) {
        int n = o->mnCount;
        if (n >= 400) {
            cThrottleObj* t = new ("Pollinator", 0, 0, 0, 0) cThrottleObj();
            o->mpThrottle = t;
        } else if (n >= 300) {
            cThrottleObj* t = new ("Pollinator", 0, 0, 0, 0) cThrottleObj();
            o->mpThrottle.AssignOutOfLine(t);
        }
        return true;
    }
    return false;
}
