// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct IFace {
    virtual void v0();
    virtual void Release();
};
struct Base {
    virtual void v0();
    ~Base(); // 0x00e06870
};
extern char gMeterVtableB[]; // 0x0147f4e0
void __cdecl Free(void* p);  // 0x008074a0
struct Meter : Base {
    void* mp4;
    char pad[0x20];
    IFace* mp28;
    IFace* mp2c;
    IFace* mp30;
    ~Meter();
};

// @ 0x00e07750
Meter::~Meter()
{
    mp4 = gMeterVtableB;
    if (mp2c) {
        Free(mp2c);
        IFace* p = mp2c;
        if (p) {
            mp2c = 0;
            p->Release();
        }
    }
    IFace* p30 = mp30;
    if (p30) p30->Release();
    IFace* p2c = mp2c;
    if (p2c) p2c->Release();
    IFace* p28 = mp28;
    if (p28) p28->Release();
}
