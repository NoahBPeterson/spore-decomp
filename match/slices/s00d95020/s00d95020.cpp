// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct IFace {
    virtual void v0();
    virtual void Release(); // slot +0x04
};
void __cdecl operator_delete(void* p); // 0x00f47380
struct Obj {
    char pad0[0xc];
    IFace* mp0c;
    IFace* mp10;
    IFace* mp14;
    IFace* mp18;
    char pad1c[0x28 - 0x1c];
    int* mp28;
    char pad2c[0x3c - 0x2c];
    int* mp3c;
    void FUN_00d95020();
};

// @ 0x00d95020
void Obj::FUN_00d95020()
{
    if (mp3c && mp3c[-1] != 0)
        operator_delete(mp3c);
    if (mp28 && mp28[-1] != 0)
        operator_delete(mp28);
    IFace* a = mp18;
    if (a) a->Release();
    IFace* b = mp14;
    if (b) b->Release();
    IFace* c = mp10;
    if (c) c->Release();
    IFace* d = mp0c;
    if (d) d->Release();
}
