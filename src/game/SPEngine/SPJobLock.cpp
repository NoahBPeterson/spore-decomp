// src/game/SPEngine/SPJobLock.cpp -- migrated from slice(s) s0068e670 by tools/migrate/rewrite.py
// Object file: SPEngine/SPJobLock.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cJob.h"
#include "SP/JobCondition.h"
#include "EA/Thread/Mutex.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  Release_690120(void* job);         // 0x0690120  cJob::Release
#include <intrin.h>
#include <string.h>

// ---- items of slice s0068e670 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** VT(void* p) { return *(void***)p; }
extern "C" int  Release_690120(void* job);         // 0x0690120  cJob::Release
typedef int (__thiscall *FnRelease)(void*);
struct JobLock {
    void* vtbl0;            // +0x00
    void* vtbl1;            // +0x04
    volatile long mRef;     // +0x08 refcount (lock xchg/xadd)
    void* mRefObj;          // +0x0c intrusive refcounted object
    void* mJob;             // +0x10
    JobLock(void* out, void* job, void* refObj);
    ~JobLock();
};
// ---- items of slice s0068e670 end

// @ 0x0068f2b0
JobLock::~JobLock()
{
    if (mJob) ((FnRelease)Release_690120)(mJob);
    void* r = mRefObj;
    if (r) {
        volatile long* rc = (volatile long*)((char*)r + 4);
        long n = _InterlockedDecrement(rc);
        if (n == 0) {
            _InterlockedExchange(rc, 1);
            ((void (__thiscall*)(void*, int))VT(r)[0])(r, 1);
        }
    }
    vtbl0 = (void*)0x013eb938;
    vtbl1 = (void*)0x013ef094;
}
