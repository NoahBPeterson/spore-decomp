// Slice s00ca4600 -- move the closest-set element held in the scratch slot one place back and
// re-insert it into the closest set.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// `slot` is the start of the "closest objects" array and `pos` is the array position (the debug
// database types it int; the code dereferences it, so it is the position pointer itself).  The
// element at pos[-1] is kept alive in a local, the element at the scratch position (slot[0]) is
// assigned over it with the usual reference-counted assignment, and the saved element is inserted
// into the set at index (it - slot) - 1.  The helper at 0x00ca44f0 does the sorted insert; it takes
// its element by value and expects the caller to hold the reference for the duration of the call,
// which is what the small holder below does.
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV8 PV PV PV PV PV PV PV PV

// Reference-counted base of the objects in the set: AddRef at +0x60, Release at +0x64.
struct RefCounted {
    PV8 PV8 PV8
    virtual void AddRef();    // +0x60
    virtual void Release();   // +0x64
};

// Copied field by field, like the original's copy constructor (four single-float moves).
struct Vec4 {
    float x, y, z, w;
    Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
};

// Holds a reference for the duration of one call: AddRef when built, Release when destroyed.
// The insert helper takes it by value, so the temporary lives in the outgoing argument slot; the
// reference the local holds is dropped explicitly after the call.
struct RefHolder {
    RefCounted* p;
    RefHolder(RefCounted* q) : p(q) { if (p) p->AddRef(); }
    RefHolder(const RefHolder& o) : p(o.p) {}
    ~RefHolder() { if (p) p->Release(); }
};

void InsertClosest(RefCounted** slot, int a, int count, int b, RefHolder item, Vec4 p); // 0x00ca44f0

// @ 0x00ca4600
void ShiftClosest(RefCounted** slot, int pos, Vec4 p)
{
    RefCounted** it = (RefCounted**)pos;

    RefCounted* item = it[-1];
    if (item)
        item->AddRef();

    RefCounted* current = *slot;
    RefCounted* old = it[-1];
    if (current != old) {
        if (current)
            current->AddRef();
        it[-1] = current;
        if (old)
            old->Release();
    }

    InsertClosest(slot, 0, (int)(it - slot) - 1, 0, RefHolder(item), p);
    if (item)
        item->Release();
}
