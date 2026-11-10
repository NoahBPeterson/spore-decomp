// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct IFace {
    virtual void AddRef();
    virtual void Release();
};
struct Sub {
    char mPad[0xc];
    int mCount;          // +0x0c, object +0xa8
    void DoNuke(int n);  // 0x009a9600
};
struct Obj {
    char mPad00[0x80];
    IFace* mp80;         // +0x80
    IFace* mp84;         // +0x84
    IFace* mp88;         // +0x88
    IFace* mp8c;         // +0x8c
    char mPad90[0x9c - 0x90];
    Sub mSub;            // +0x9c
    void FUN_00ce6a90();
};

// @ 0x00ce6a90
void Obj::FUN_00ce6a90()
{
    Sub* sub = &mSub;
    int count = sub->mCount;
    sub->DoNuke(count);
    IFace* p8c = mp8c;
    if (p8c)
        p8c->Release();
    IFace* p88 = mp88;
    if (p88)
        p88->Release();
    IFace* p84 = mp84;
    if (p84)
        p84->Release();
    IFace* p80 = mp80;
    if (p80)
        p80->Release();
}
