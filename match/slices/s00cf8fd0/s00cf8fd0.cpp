// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>

extern char g_13f09b4[]; // 0x013f09b4
void* operator_new_dbg(unsigned n, const char* tag, int a, int b, int c, int d); // 0x00f473a0

struct Obj {
    virtual void v0();
    virtual void AddRef();
    virtual void Destroy();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void Start(); // slot +0x1c
    Obj();                // 0x00d004c0
};

struct Owner {
    char mPad[0x108];
    Obj* mp; // +0x108
    void FUN_00cf8fd0();
};

// @ 0x00cf8fd0
void Owner::FUN_00cf8fd0()
{
    void* raw = operator_new_dbg(0x74, g_13f09b4, 0, 0, 0, 0);
    Obj* p = raw ? new (raw) Obj() : 0;
    Obj* old = mp;
    if (p != old) {
        if (p)
            p->AddRef();
        mp = p;
        if (old)
            old->Destroy();
    }
    mp->Start();
}
