// Slice s0076afb0: the scalar deleting destructor of a class with two polymorphic bases
// that owns one heap block at +0x11c.

struct BaseA_s0076_afb0 {
    virtual ~BaseA_s0076_afb0() {}
};

struct BaseB_s0076_afb0 {
    virtual ~BaseB_s0076_afb0() {}
};

struct Owner_s0076_afb0 : BaseA_s0076_afb0, BaseB_s0076_afb0 {
    char pad08[0x11c - 8];
    void* mpBuffer;  // +0x11c

    virtual ~Owner_s0076_afb0()
    {
        if (mpBuffer)
            operator delete(mpBuffer);
    }
};

// Constructing one here makes this file emit the vtable, and with it the scalar deleting destructor.
Owner_s0076_afb0* NewOwner_s0076_afb0() { return new Owner_s0076_afb0; }

// 0x0076afb0 is the compiler-generated scalar deleting destructor: ??_GOwner_s0076_afb0@@UAEPAXI@Z
