#include "game/types.h"

// 0x00d4b5a0 lazily builds nine singletons. For each one the compiler emits
// (docs/codegen.md 12.3): a bit in the shared static guard, an inlined derived
// constructor (out-of-line base ctor call, then the derived vftable store),
// an atexit registration of the COFF-local destructor thunk, and then a
// non-virtual IsReady()/Initialize() pair inherited from the common base.
// The concrete class identities are not recovered yet, so the names here are
// slice-local; the shape is what the retail bytes show.

// IsReady()/Initialize() are declared only: they live outside this slice, so
// the compiler cannot assume the this-pointer in ecx survives the IsReady()
// call and must reload it for Initialize(). The constructor and destructor
// are visible and non-throwing, which keeps the static-guard code free of an
// exception frame (retail has none).
class cLazyBase_00d4b5a0 {
public:
    __declspec(noinline) cLazyBase_00d4b5a0(int flags);
    __declspec(noinline) virtual ~cLazyBase_00d4b5a0();

    bool IsReady() const;
    void Initialize();

protected:
    int mFlags;
    bool mReady;
};

cLazyBase_00d4b5a0::cLazyBase_00d4b5a0(int flags)
    : mFlags(flags), mReady(false)
{
}

cLazyBase_00d4b5a0::~cLazyBase_00d4b5a0()
{
}

class cLazyThing1_00d4b5a0 : public cLazyBase_00d4b5a0 {
public:
    cLazyThing1_00d4b5a0() : cLazyBase_00d4b5a0(0) {}
    virtual void Reset() {}
};

class cLazyThing2_00d4b5a0 : public cLazyBase_00d4b5a0 {
public:
    cLazyThing2_00d4b5a0() : cLazyBase_00d4b5a0(0) {}
    virtual void Reset() {}
};

class cLazyThing3_00d4b5a0 : public cLazyBase_00d4b5a0 {
public:
    cLazyThing3_00d4b5a0() : cLazyBase_00d4b5a0(0) {}
    virtual void Reset() {}
};

class cLazyThing4_00d4b5a0 : public cLazyBase_00d4b5a0 {
public:
    cLazyThing4_00d4b5a0() : cLazyBase_00d4b5a0(0) {}
    virtual void Reset() {}
};

class cLazyThing5_00d4b5a0 : public cLazyBase_00d4b5a0 {
public:
    cLazyThing5_00d4b5a0() : cLazyBase_00d4b5a0(0) {}
    virtual void Reset() {}
};

class cLazyThing6_00d4b5a0 : public cLazyBase_00d4b5a0 {
public:
    cLazyThing6_00d4b5a0() : cLazyBase_00d4b5a0(0) {}
    virtual void Reset() {}
};

class cLazyThing7_00d4b5a0 : public cLazyBase_00d4b5a0 {
public:
    cLazyThing7_00d4b5a0() : cLazyBase_00d4b5a0(0) {}
    virtual void Reset() {}
};

class cLazyThing8_00d4b5a0 : public cLazyBase_00d4b5a0 {
public:
    cLazyThing8_00d4b5a0() : cLazyBase_00d4b5a0(0) {}
    virtual void Reset() {}
};

class cLazyThing9_00d4b5a0 : public cLazyBase_00d4b5a0 {
public:
    cLazyThing9_00d4b5a0() : cLazyBase_00d4b5a0(0) {}
    virtual void Reset() {}
};

// @ 0x00d4b5a0
void EnsureLazyThings_00d4b5a0()
{
    static cLazyThing1_00d4b5a0 sThing1;
    if (!sThing1.IsReady())
        sThing1.Initialize();

    static cLazyThing2_00d4b5a0 sThing2;
    if (!sThing2.IsReady())
        sThing2.Initialize();

    static cLazyThing3_00d4b5a0 sThing3;
    if (!sThing3.IsReady())
        sThing3.Initialize();

    static cLazyThing4_00d4b5a0 sThing4;
    if (!sThing4.IsReady())
        sThing4.Initialize();

    static cLazyThing5_00d4b5a0 sThing5;
    if (!sThing5.IsReady())
        sThing5.Initialize();

    static cLazyThing6_00d4b5a0 sThing6;
    if (!sThing6.IsReady())
        sThing6.Initialize();

    static cLazyThing7_00d4b5a0 sThing7;
    if (!sThing7.IsReady())
        sThing7.Initialize();

    static cLazyThing8_00d4b5a0 sThing8;
    if (!sThing8.IsReady())
        sThing8.Initialize();

    static cLazyThing9_00d4b5a0 sThing9;
    if (!sThing9.IsReady())
        sThing9.Initialize();
}
