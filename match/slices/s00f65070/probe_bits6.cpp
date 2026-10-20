// codegen probe 6: combos
struct DG { void Stop(); };
struct BF { unsigned b0:1; unsigned rest:31; };
struct E {
    void* a; void* b; void* c; void* d; void* e; BF mFlags; DG* g; int* p; int* desc;
    void StopV(int); void StopVC(int); void StartV(int); void StartC(int); void U1(); void U2();
};
struct EV {
    void* a; void* b; void* c; void* d; void* e; volatile BF mFlags; DG* g; int* p; int* desc;
    void StopV(int); void StartV(int); void U1(); void U2();
};
struct EC {
    void* a; void* b; void* c; void* d; void* e; BF mFlags; DG* g; int* p; int* desc;
    void StopC(int) const; void StartC(int) const; void U1() const; void U2() const;
};
void E::StopV(int) {
    if (mFlags.b0) { mFlags.b0 = 0; g->Stop(); }
}
void E::StopVC(int) {
    if (mFlags.rest) { mFlags.rest = 0; g->Stop(); }
}
void E::StartV(int) {
    if (!mFlags.b0 && g) { mFlags.b0 = 1; if (((*desc >> 1) & 1) != 0) U2(); else U1(); }
}
void EV::StopV(int) {
    if (mFlags.b0) { mFlags.b0 = 0; g->Stop(); }
}
void EV::StartV(int) {
    if (!mFlags.b0 && g) { mFlags.b0 = 1; if (((*desc >> 1) & 1) != 0) U2(); else U1(); }
}
void EC::StopC(int) const {
    if (mFlags.b0) { const_cast<EC*>(this)->mFlags.b0 = 0; g->Stop(); }
}
void EC::StartC(int) const {
    if (!mFlags.b0 && g) { const_cast<EC*>(this)->mFlags.b0 = 1; if (((*desc >> 1) & 1) != 0) U2(); else U1(); }
}
