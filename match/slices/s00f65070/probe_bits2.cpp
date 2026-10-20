// codegen probe 2: thiscall member shapes
struct G {
    void* a; void* b; void* c; void* d; void* e; unsigned mFlags; int* p;
    void Stop();
    void Update(int);
};
void G::Stop() {
    if ((mFlags & 1) != 0) {
        mFlags &= ~1u;
        a = 0;
    }
}
struct E {
    void* a; void* b; void* c; void* d; void* e; unsigned mFlags; int* p; int* desc;
    void Start(int);
    void U1();
    void U2();
};
void E::Start(int) {
    if (!(mFlags & 1) && p) {
        mFlags |= 1;
        if (((*desc >> 1) & 1) != 0) U2(); else U1();
    }
}
