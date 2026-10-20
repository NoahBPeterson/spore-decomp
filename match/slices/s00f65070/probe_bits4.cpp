// codegen probe 4: flags + call
struct DG { void Stop(); };
struct E {
    void* a; void* b; void* c; void* d; void* e; unsigned mFlags; DG* g; int* p; int* desc;
    void Stop1(int);
    void Stop2(int);
    void Stop3(int);
    void U1();
    void U2();
    void Start1(int);
};
void E::Stop1(int) {
    if (mFlags & 1) {
        mFlags &= ~1u;
        g->Stop();
    }
}
void E::Stop2(int) {
    if ((mFlags & 1) != 0) {
        mFlags = mFlags & 0xfffffffe;
        g->Stop();
    }
}
void E::Stop3(int) {
    unsigned f = mFlags;
    if (f & 1) {
        f &= ~1u;
        mFlags = f;
        g->Stop();
    }
}
void E::Start1(int) {
    if ((mFlags & 1) == 0 && g) {
        mFlags |= 1;
        if (((*desc >> 1) & 1) != 0) U2(); else U1();
    }
}
