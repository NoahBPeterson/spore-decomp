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
// two bases (vtables 0x13eb938 / 0x13ef094 restored on exit); the job (cJob::Release, 0x690120) and the intrusive
// reference object, deleted through its virtual destructor when its count drops to zero
struct JobLockBase0 { virtual void Slot0(); ~JobLockBase0() {} };
struct JobLockBase1 { virtual void Slot0(); ~JobLockBase1() {} };
struct JobLockRefObj {
    virtual ~JobLockRefObj();
    volatile long mRef;     // +0x04
};
inline void JobLockReleaseRef(JobLockRefObj* r)
{
    volatile long* rc = &r->mRef;
    long n = _InterlockedDecrement(rc);
    if (n == 0) {
        _InterlockedExchange(rc, 1);
        delete r;
    }
}
struct JobLockRefHolder {
    JobLockRefObj* mp;
    ~JobLockRefHolder() { if (mp) JobLockReleaseRef(mp); }
};
struct JobLockJob { int Release(); };   // 0x0690120 cJob::Release
struct JobLockJobHolder {
    JobLockJob* mp;
    ~JobLockJobHolder() { if (mp) mp->Release(); }
};
struct __declspec(novtable) JobLock : JobLockBase0, JobLockBase1 {
    volatile long mRef;         // +0x08 refcount (lock xchg/xadd)
    JobLockRefHolder mRefObj;   // +0x0c intrusive refcounted object
    JobLockJobHolder mJob;      // +0x10
    JobLock(void* out, void* job, void* refObj);
    ~JobLock();
};
// ---- items of slice s0068e670 end

// @ 0x0068f2b0
JobLock::~JobLock()
{
}
