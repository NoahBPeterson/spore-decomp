// scratch: loop spellings for TimerManager::Defragment / Release (not compiled by the manifest)
struct Collection { int a[7]; void f(); void g(); };
struct TM { Collection c[2]; };

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMa(TM* t) {
    Collection* p = t->c;
    int n = 2;
    do {
        p->f();
        ++p;
    } while (--n);
}

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMb(TM* t) {
    Collection* p = t->c;
    int n = 2;
    while (n-- > 0) {
        p->f();
        ++p;
    }
}

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMc(TM* t) {
    Collection* p = t->c;
    int n = 2;
    do {
        p->f();
        ++p;
        --n;
    } while (n != 0);
}

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMd(TM* t) {
    Collection* p = t->c;
    int n = 2;
    do {
        p->f();
        ++p;
    } while (n = n - 1);
}

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMe(TM* t) {
    int n = 2;
    Collection* p = t->c;
    while (n != 0) {
        p->f();
        n -= 1;
        ++p;
    }
}

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMf(TM* t) {
    Collection* p = t->c;
    for (int n = 2; n > 0; --n) {
        p->f();
        ++p;
    }
}

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMg(TM* t) {
    int n = 2;
    Collection* p = t->c;
    do {
        p->f();
        p = p + 1;
        --n;
    } while (n);
}

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMh(TM* t) {
    Collection* p = t->c;
    int n = 2;
    do {
        p->f();
        ++p;
        n = n - 1;
    } while (n);
}

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMi(TM* t) {
    Collection* p = t->c;
    for (int n = 2; n; --n) {
        p->f();
        ++p;
    }
}

// 0x0112da30: not byte-exact; the byte-exact version is the lifted one in match/slices/s0112da30/s0112da30.cpp
void TMj(TM* t) {
    Collection* p = t->c;
    for (int n = 2; --n >= 0;) {
        p->f();
        ++p;
    }
}
