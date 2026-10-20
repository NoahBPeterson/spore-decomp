// codegen probe 5: volatile flags
struct DG { void Stop(); };
struct E {
    void* a; void* b; void* c; void* d; void* e; volatile unsigned mFlags; DG* g; int* p; int* desc;
    void Stop1(int);
    void Stop2(int);
    void Start1(int);
    void U1();
    void U2();
};
void E::Stop1(int) {
    if (mFlags & 1) {
        mFlags &= ~1u;
        g->Stop();
    }
}
void E::Stop2(int) {
    if ((mFlags & 1) != 0) {
        mFlags &= ~1u;
        g->Stop();
    }
}
void E::Start1(int) {
    if ((mFlags & 1) == 0 && g) {
        mFlags |= 1;
        if (((*desc >> 1) & 1) != 0) U2(); else U1();
    }
}
