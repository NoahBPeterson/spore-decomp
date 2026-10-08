// Simulator::cGameData::IsDestroyed (0x00bfd0d0, 203 bytes): thiscall, one char argument, ret 4.
//
// Shape from the card: the first vslot at +0x58 returns a float that is compared with the float
// at +0x38; when it is larger and the argument is zero, vslot +0x0c gives an object that is
// tested by FUN_00b18740, and if that is false, vslot +0x0c and +0x4c give a second object and
// FUN_00bfca80 is called. Then the pointer at +0x34 is cleared, +0x38 is refreshed from vslot
// +0x58, and if the pointer was non-null a message with vtable 0x013eb844 is sent to
// SP::MessageServer (message id 0x01622184) and destroyed.
//
// Flags: default (x87 float returns from the vslots, fcompi compares).
//
// Names are Claude-coined from the behaviour; the message fields are only what the stores show.
#include "types.h"

#include <intrin.h>

class cGameData;

// Object returned by cGameData vslot +0x0c. Only its slot +0x4c (index 19) is used here.
class Object {
public:
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void _v3();
    virtual void _v4();
    virtual void _v5();
    virtual void _v6();
    virtual void _v7();
    virtual void _v8();
    virtual void _v9();
    virtual void _v10();
    virtual void _v11();
    virtual void _v12();
    virtual void _v13();
    virtual void _v14();
    virtual void _v15();
    virtual void _v16();
    virtual void _v17();
    virtual void _v18();
    virtual Object* _v19();  // +0x4c
};

// Message server: vslot +0x14 (index 5) sends a message.
class MessageServer {
public:
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void _v3();
    virtual void _v4();
    virtual void Send(unsigned int messageID, void* pMessage, unsigned int flags);  // +0x14
};

MessageServer* MessageServerGet();  // 0x0067dcc0, cdecl, no arguments

// Message object built on the stack (SP::MessageBasicRC<5>): stores at +0x0, +0x4, +0x8, +0x10,
// +0x30 and +0x38 are the only ones this function writes.
class IsDestroyedMessage {
public:
    void* mpVtable;   // +0x00 (0x013eb844 once built)
    int mRefCount;    // +0x04 AtomicInt, cleared with an exchange
    cGameData* mpSender;  // +0x08
    int mField10;     // +0x10
    char mRest14[0x1c];   // +0x14
    int mField30;     // +0x30
    char mRest34[4];  // +0x34
    int mField38;     // +0x38
    void Destruct();  // 0x00421cf0 (SlotMessage::Destruct), thiscall, no arguments
};

// Free functions called with the object pointers from the vslots.
char FUN_00b18740(void* p);                              // 0x00b18740, cdecl, one argument, returns char
void FUN_00bfca80(void* pA, void* pB, unsigned int flag);  // 0x00bfca80, cdecl, three arguments

class cGameData {
public:
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual Object* _v3();  // +0x0c
    virtual void _v4();
    virtual void _v5();
    virtual void _v6();
    virtual void _v7();
    virtual void _v8();
    virtual void _v9();
    virtual void _v10();
    virtual void _v11();
    virtual void _v12();
    virtual void _v13();
    virtual void _v14();
    virtual void _v15();
    virtual void _v16();
    virtual void _v17();
    virtual void _v18();
    virtual void _v19();
    virtual void _v20();
    virtual void _v21();
    virtual float _v22();  // +0x58

    void IsDestroyed(char bForce);  // 0x00bfd0d0

private:
    char mUnknown04[0x30];  // +0x04 .. +0x33
    void* mpPending;        // +0x34
    float mProgress;        // +0x38
};

void cGameData::IsDestroyed(char bForce) {
    float current = _v22();
    if (current > mProgress && bForce == 0) {
        Object* pFirst = _v3();
        if (!FUN_00b18740(pFirst)) {
            FUN_00bfca80(_v3(), _v3()->_v19(), 0);
        }
    }

    void* pOld = mpPending;
    mpPending = 0;
    mProgress = _v22();
    if (pOld != mpPending) {
        IsDestroyedMessage msg;
        msg.mpVtable = (void*)0x013eb90c;
        _InterlockedExchange((long*)&msg.mRefCount, 0);
        msg.mpVtable = (void*)0x013eb844;
        msg.mpSender = this;
        msg.mField10 = 0;
        msg.mField30 = 0;
        msg.mField38 = 0;
        MessageServerGet()->Send(0x01622184, &msg, 0);
        msg.Destruct();
    }
}
