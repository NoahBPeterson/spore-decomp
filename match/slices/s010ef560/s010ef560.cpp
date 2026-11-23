// Same shape as s010878b0's finishLoadedObject_hkRigidBody (0x01087e20): placement-
// constructs the base part (here 0x10eedd0, donor 0x1087d50), then the derived class's
// own vtable (here 0x149e2ec, donor 0x149e00c) is installed by the inlined ctor.
// Flags: /vc71 /O2 /MD /Gy /TP
#include <new>

struct hkFinishLoadedObjectFlag_010ef560 { int m_finishing; };

struct hkEntity_010ef560 {
    hkEntity_010ef560(hkFinishLoadedObjectFlag_010ef560 flag);   // 0x10eedd0 (__thiscall)
    virtual void v0();
};

struct hkRigidBody_010ef560 : hkEntity_010ef560 {
    hkRigidBody_010ef560(hkFinishLoadedObjectFlag_010ef560 f) : hkEntity_010ef560(f) {}
};

// @ 0x010ef560
void finishLoadedObject_010ef560(void* p)
{
    if (p != 0)
    {
        hkFinishLoadedObjectFlag_010ef560 flag; flag.m_finishing = 1;
        new (p) hkRigidBody_010ef560(flag);
    }
}
