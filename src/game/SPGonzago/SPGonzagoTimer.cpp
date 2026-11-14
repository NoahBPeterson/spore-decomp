#include "game/types.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cSPTimer.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern void __cdecl FUN_00b63880();
extern void __cdecl FUN_005725a0();
extern void* gGonzagoTimerVtbl;           // 0x01464450
extern char gSig2;   // 0x0156ad88

typedef unsigned char uchar;
struct CSBase {
    void Init(void (*cb)());
    char IsRunning();            // 0x00feba90
    long long GetElapsedTime();  // 0x00bc3190
};
struct cGonzagoTimer : CSBase {
    char  pad04[4];
    long long mElapsed;  // +0x08
    long long mBase;     // +0x10
    int   mPad18;        // +0x18
    void* mGetMs;        // +0x1c
    cGonzagoTimer();
    ~cGonzagoTimer();
    void Write(void* ser);          // 0x00b638d0
    uchar Read(void* ser);          // 0x00b63930
    void AddElapsed(int v);         // 0x00b638c0
};
struct cVarListSerializer {
    char data[0xa14];
    cVarListSerializer(void* obj, void* info, unsigned sig);  // 0x00692f90
    void Serialize(void* ser);                                 // 0x00692900
    uchar SerializeB(void* ser);                               // 0x00693e10
};

// @ 0x00b63890
cGonzagoTimer::cGonzagoTimer()
{
    Init(&FUN_00b63880);
    *(void**)this = &gGonzagoTimerVtbl;
}

// @ 0x00b638b0
cGonzagoTimer::~cGonzagoTimer()
{
    *(void**)this = &gGonzagoTimerVtbl;
    FUN_005725a0();
}

// @ 0x00b638c0
void __thiscall cGonzagoTimer::AddElapsed(int v)
{
    mElapsed += v;
}

// @ 0x00b638d0
void __thiscall cGonzagoTimer::Write(void* ser)
{
    if (IsRunning()) {
        long long t = GetElapsedTime();
        mElapsed = t;
        long long b = ((long long(__thiscall*)(void*))mGetMs)(this);
        mBase = b;
    }
    cVarListSerializer s((char*)this, &gSig2, 0x1a80d26);
    s.Serialize(ser);
}
