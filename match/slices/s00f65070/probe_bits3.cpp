// codegen probe 3: bitfield flags
struct BF { unsigned b0:1; unsigned rest:31; };
struct G {
    void* a; void* b; void* c; void* d; void* e; BF mFlags; int* p;
    void Stop();
    void Start(int);
    void U1();
    void U2();
};
void G::Stop() {
    if (mFlags.b0 != 0) {
        mFlags.b0 = 0;
        a = 0;
    }
}
void G::Start(int) {
    if (mFlags.b0 == 0 && p) {
        mFlags.b0 = 1;
        if (((*p >> 1) & 1) != 0) U2(); else U1();
    }
}
