// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct IFace {
    virtual void AddRef();
    virtual void Release();
};
struct Player {
    void Set(IFace* p); // 0x00ea2d50
};
struct Viewer {
    char mPad[0xd4];
    IFace* mpMusic;     // +0xd4
    char mPadD8[0xdc - 0xd8];
    Player* mpPlayer;   // +0xdc
    void Refresh();     // 0x00ea4610
    void SetMusic(IFace* p);
};

// @ 0x00ea4af0
void Viewer::SetMusic(IFace* p)
{
    IFace* old = mpMusic;
    if (p != old) {
        if (p)
            p->AddRef();
        mpMusic = p;
        if (old)
            old->Release();
    }
    mpPlayer->Set(p);
    Refresh();
}
