// codegen probe 7
struct DG { void Stop(); };
struct E {
    void* a; void* b; void* c; void* d; void* e; unsigned mFlags; DG* g; int* p; int* desc;
    unsigned& F() { return mFlags; }
    void StopA(int); void StopB(int); void StopC(int); void StopD(int);
    void StartA(int); void StartB(int);
    void U1(); void U2();
};
void E::StopA(int) { if (F() & 1) { F() &= ~1u; g->Stop(); } }
void E::StopB(int) { if (((unsigned char*)&mFlags)[0] & 1) { mFlags &= ~1u; g->Stop(); } }
void E::StopC(int) { if (mFlags & 1) { F() &= ~1u; g->Stop(); } }
void E::StopD(int) { if (F() & 1) { mFlags &= ~1u; g->Stop(); } }
void E::StartA(int) { if (!(F() & 1) && g) { F() |= 1; if (((*desc >> 1) & 1) != 0) U2(); else U1(); } }
void E::StartB(int) { if (!(((unsigned char*)&mFlags)[0] & 1) && g) { mFlags |= 1; if (((*desc >> 1) & 1) != 0) U2(); else U1(); } }
