// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct V3i { int a, b, c; };
struct Ev {
    char mPad0[8];
    int m8;
    char mPadC[4];
    int m10;
    char mPad14[4];
    int m18;
};
struct Sub {
    bool Take(V3i v); // 0x00eb14c0
};
struct Track;
struct Viewer {
    char mPad00[0xc];
    Sub mSub;                       // +0x0c
    char mPad0d[0xd4 - 0x0c - 1];
    Track* mpMusic;                 // +0xd4
    void Refresh();                 // 0x00ea4610
    void Follow();                  // 0x00ea4cb0
    bool FUN_00ea4e60(int id, void* arg);
};

// @ 0x00ea4e60
bool Viewer::FUN_00ea4e60(int id, void* arg)
{
    bool ok = false;
    switch (id) {
    case 0x00f62def: {
        Ev* ev = (Ev*)arg;
        V3i v;
        v.a = ev->m18;
        v.b = ev->m8;
        v.c = ev->m10;
        ok = mSub.Take(v);
        if (ok)
            Follow();
        break;
    }
    case 0x0510b72f:
        ok = mpMusic == arg;
        if (ok)
            Refresh();
        break;
    }
    return ok;
}
