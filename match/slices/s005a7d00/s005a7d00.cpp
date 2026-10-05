// slice s005a7d00 — badness calculators, cSPEditorHandleSpine ctor/dtor/Init and
// assorted editor handle helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <intrin.h>
#include "types.h"

#define PV(n) virtual void pv##n();

namespace EA {
template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mnRefCount(0) {}
    virtual ~RefCountVTemplate() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() { int n = (*(volatile int*)&mnRefCount += -1); if (n == 0) { mnRefCount = 1; delete this; return 0; } return mnRefCount; }
    T mnRefCount;
};
namespace COM { class IUnknown32 { public: virtual int AddRef() = 0; virtual int Release() = 0; }; }
}

struct Vector3 { float x, y, z; };

struct S36 { int v[9]; };

class cCopy9 {
public:
    void Assign(const S36& s);
};

// @ 0x005a88a0
void cCopy9::Assign(const S36& s) {
    __movsd((unsigned long*)this, (unsigned long*)&s, 9);
}

// ---- EditorTuning accessor --------------------------------------------------
struct TuningData { char pad[0x60]; Vector3 mValue; };
TuningData* EditorTuning();  // 0x00401070

// @ 0x005a8900
Vector3* __stdcall GetEditorTuningValue(Vector3* out) {
    TuningData* t = EditorTuning();
    *(int*)&out->x = *(int*)&t->mValue.x;
    *(int*)&out->y = *(int*)&t->mValue.y;
    *(int*)&out->z = *(int*)&t->mValue.z;
    return out;
}

// ---- simple handle-ish class -----------------------------------------------
class cHandleish {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void v5();                 // +0x14
    PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual void v12(int, int);        // +0x30
    char  pad0[0xc];
    void* m10;    // +0x10
    void* m14;    // +0x14
    void* m18;    // +0x18
    void SetState(int state);   // 0x005a8a60
    void SetEnabled(bool enabled);  // 0x005a8a80
};

// @ 0x005a8a60
void cHandleish::SetState(int state) {
    if (m14 && m18) {
        m10 = (void*)state;
        v5();
    }
}

// @ 0x005a8a80
void cHandleish::SetEnabled(bool enabled) {
    if (m14 && m18 && enabled != (*(unsigned char*)((char*)m14 + 4) & 1)) {
        if (enabled) {
            v5();
            v12(3, 1);
        } else {
            v12(1, 1);
        }
    }
}

// ---- SP::cSPEditorHandle / cSPEditorHandleSpine -----------------------------
namespace SP {
class cSPEditorHandle : public EA::COM::IUnknown32, public EA::RefCountVTemplate<int> {
public:
    cSPEditorHandle();
    virtual ~cSPEditorHandle();
    void Shutdown();  // 0x0047e2c0
    char pad[0x50 - 0xc];
};
struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(const cSPVector3& c) : x(c.x), y(c.y), z(c.z) {} };
struct cSPMatrix3 { float m[9]; void Assign(const cSPMatrix3&); };  // 0x0041cb40
extern cSPVector3 gSpineOffset;   // 0x015e7e34
extern cSPMatrix3 gSpineOrient;   // 0x015e7f64

class cSPEditorHandleSpine : public cSPEditorHandle {
public:
    cSPVector3 mOffset;   // +0x50
    cSPMatrix3 mOrient;   // +0x5c
    cSPEditorHandleSpine();
    virtual ~cSPEditorHandleSpine() { Shutdown(); }
    void Init(void* param);  // 0x005a8970
};
}

// @ 0x005a8ad0
SP::cSPEditorHandleSpine::cSPEditorHandleSpine() : mOffset(SP::gSpineOffset) {
    mOrient.Assign(SP::gSpineOrient);
}

// ---- remaining functions in the slice (abridged) ---------------------------
// @ 0x005a7d00  cSPEditorGeneralBadnessCalculator::CalculateValues
void FUN_005a7d00() {}

// @ 0x005a83d0
void FUN_005a83d0() {}

// @ 0x005a85f0  cSPEditorHandBadnessCalculator::CalculateBadness
void FUN_005a85f0() {}

// @ 0x005a8970
void SP::cSPEditorHandleSpine::Init(void*) {}

// @ 0x005a8b20
void FUN_005a8b20() {}
