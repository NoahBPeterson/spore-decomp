// Slice s00943f60 -- EA::Internet::HTTPClient::Shutdown (0x009440e0).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <intrin.h>

void __cdecl operator_delete__(void*) throw();   // 0x00f47380

typedef void (__thiscall *VF0)(void*);
typedef int  (__thiscall *VFI0)(void*);
#define VSLOT(p, byteoff) ((*(void***)(p))[(byteoff) / 4])
#define VCALL0(p, off)    ((VF0)VSLOT(p, off))(p)
#define VCALLI0(p, off)   ((VFI0)VSLOT(p, off))(p)

namespace EA { namespace Thread {
struct Mutex {
    void Lock(const void* timeout);   // 0x009221b0
    void Unlock();                    // 0x00922270
};
}}

namespace EA { namespace Internet {

extern const int kLockTimeout;        // 0x0143F214

typedef void (__cdecl *NotifyFn)(void* ctx, void* client, unsigned msg, void* data, int zero);

// Refcounted filter object: vtable slot 0 is the deleting destructor, count at +4.
struct RefObj {
    virtual void Destroy(int flags);
    int mnRefCount;
};

// Worker thread info (0x90 of the client): bCreated at +4, socket at +0x20.
struct WorkerThreadInfo {
    int   pad0;
    char  bCreated;                   // +4
    char  pad1[0x20 - 5];
    void* mpSocket;                   // +0x20
};

class HTTPClient {
public:
    char pad0[0xc];
    bool mbInitialized;               // +0xc
    char pad1[0x24 - 0xd];
    NotifyFn mpNotify;                // +0x24
    void* mpNotifyCtx;                // +0x28
    char pad2[0x54 - 0x2c];
    void* mpLogB;                     // +0x54
    void* mpLogA;                     // +0x58
    char pad3[0x60 - 0x5c];
    EA::Thread::Mutex mMutex;         // +0x60
    char pad4[0x90 - 0x61];
    WorkerThreadInfo* mpWorkerThreadInfo;   // +0x90
    char pad5[0x140 - 0x94];
    char* mpReadBuffer;               // +0x140
    char pad7[0x148 - 0x144];
    char* mpWriteBuffer;              // +0x148 (freed when non-null)
    char pad6[0x150 - 0x14c];
    RefObj** mpFiltersBegin;          // +0x150
    RefObj** mpFiltersEnd;            // +0x154

    void SetTimeout(int a, int ms);   // 0x00943a30
    void Pump(void* socket);          // 0x009421b0
    bool Shutdown();
};

bool HTTPClient::Shutdown() {
    if (mbInitialized) {
        mMutex.Lock(&kLockTimeout);
        if (mpNotify) {
            mpNotify(mpNotifyCtx, this, 0x700af201, 0, 0);
            mpNotify = 0;
        }
        mpNotifyCtx = 0;
        if (mpLogB) {
            if (VCALLI0(mpLogB, 0x10)) {
                VCALL0(mpLogB, 0x34);
                VCALL0(mpLogB, 0x18);
            }
            VCALL0(mpLogB, 0x08);
        }
        if (mpLogA) {
            // The original calls the B stream's 0x34/0x18 slots here (retail copy-paste).
            if (VCALLI0(mpLogA, 0x10)) {
                VCALL0(mpLogB, 0x34);
                VCALL0(mpLogB, 0x18);
            }
            VCALL0(mpLogA, 0x08);
        }
        WorkerThreadInfo* info = mpWorkerThreadInfo;
        if (info && info->bCreated) {
            VCALL0(info->mpSocket, 0x00);
            SetTimeout(0, 0);
            Pump(info->mpSocket);
            VCALL0(info->mpSocket, 0x04);
        }
        operator_delete__(mpReadBuffer);
        if (mpWriteBuffer)
            operator_delete__(mpWriteBuffer);
        mbInitialized = false;
        mMutex.Unlock();
    }
    while (mpFiltersBegin != mpFiltersEnd) {
        RefObj* p = *--mpFiltersEnd;
        int old = _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, -1);
        if (old - 1 == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
    return true;
}

}}
