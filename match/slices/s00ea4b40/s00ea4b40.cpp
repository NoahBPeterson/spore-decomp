// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct V3 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct Player {
    void Clear(); // 0x00ea3ed0
};
struct Pair {
    void* mpA; // +0x00
    void* mpB; // +0x04
    void Both(void* a, void* b); // 0x00e25bd0
};
struct Obj {
    char mPad[0xd8];
    V3* mpD8;          // +0xd8
    Player* mpPlayer;  // +0xdc
    Pair mPair;        // +0xe0
    char mPadE8[0xf8 - 0xe8];
    void* mpF8;
    void* mpFc;
    void* mp100;
    void* mp104;
    void* mp108;
    void Helper(int n); // 0x00ea4330
    void FUN_00ea4b40();
};
void Free5(void* a, void* b, void* c, void* d, void* e); // 0x00571db0

// @ 0x00ea4b40
void Obj::FUN_00ea4b40()
{
    Helper(0);
    if (mpF8) {
        void* a = mpF8;
        void* b = mpFc;
        void* c = mp100;
        void* d = mp104;
        void* e = mp108;
        mpF8 = 0;
        Free5(a, b, c, d, e);
    }
    mPair.Both(mPair.mpA, mPair.mpB);
    mpPlayer->Clear();
    V3* v = mpD8;
    if (v) {
        mpD8 = 0;
        v->v2();
    }
}
