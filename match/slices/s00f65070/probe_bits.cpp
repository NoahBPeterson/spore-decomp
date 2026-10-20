// codegen probe: how cl spells flag test/or/and
struct B { unsigned mWord; };
struct T {
    void* a; int b; B mFlags; void* p; int* q;
};
void __stdcall f1(T* t) {
    if (!(t->mFlags.mWord & 1) && t->p) {
        t->mFlags.mWord |= 1;
        if (((*(unsigned*)t->q >> 1) & 1) != 0) f1(t); else f1(t);
    }
}
void __stdcall f2(T* t) {
    if (!(t->mFlags.mWord & 1) && t->p) {
        t->mFlags.mWord |= 1;
        if (((*(unsigned*)t->q >> 1) & 1) != 0) f2(t); else f2(t);
    }
}
struct U {
    void* a; int b; unsigned mFlags; void* p; int* q;
};
void __stdcall f3(U* t) {
    if (!(t->mFlags & 1) && t->p) {
        t->mFlags |= 1;
        if (((*(unsigned*)t->q >> 1) & 1) != 0) f3(t); else f3(t);
    }
}
void __stdcall f4(U* t) {
    if ((t->mFlags & 1) != 0) {
        t->mFlags &= ~1u;
        f4(t);
    }
}
void __stdcall f5(T* t) {
    if ((t->mFlags.mWord & 1) != 0) {
        t->mFlags.mWord &= ~1u;
        f5(t);
    }
}
