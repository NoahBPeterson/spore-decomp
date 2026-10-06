// EA::Swarm::cEffectParams and its transform/parameter helpers
// (0x007d4a40..0x007d56e8).  No function in this slice is byte-exact; see
// nonmatching.txt / partial.txt.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

void* operator new[](size_t size);
void  operator delete[](void* p);
void  operator delete(void* p);

struct Obj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual void AddRef();    // +0x34
    virtual void Release();   // +0x38
};
struct AutoRefCount {
    Obj* mpObject;
    AutoRefCount& operator=(Obj* p) {
        if (p != mpObject) {
            Obj* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};

struct cSPTransform {   // size 0x38
    float m[0x38 / 4];
    cSPTransform& operator=(const cSPTransform& o) {
        for (int i = 0; i < 0x38 / 4; ++i) m[i] = o.m[i];
        return *this;
    }
};
struct Matrix3 { float m[9]; void Assign(const Matrix3& o); };     // 0x41cb40
struct ElemPart { void Init(void* a); };                           // 0x537f40
void ElemCtor(void* self, const void* src);                       // 0x79a0d0

// @ 0x007d4a40
void* InitTransform(void* self, const void* src, void* a, char flag) {
    char* s = (char*)self; const char* o = (const char*)src;
    s[0] = flag;
    *(uint16_t*)(s + 4) = *(const uint16_t*)(o);
    *(uint16_t*)(s + 6) = *(const uint16_t*)(o + 2);
    *(float*)(s + 8) = *(const float*)(o + 4);
    *(float*)(s + 0xc) = *(const float*)(o + 0xc + 8);   // (o+0x14)-0xc
    *(float*)(s + 0x10) = *(const float*)(o + 0x14 - 8);
    *(float*)(s + 0x14) = *(const float*)(o + 0x14 - 4);
    ((Matrix3*)(s + 0x18))->Assign(*(const Matrix3*)(o + 0x14));
    *(uint16_t*)(s + 0x3e) = 0;
    *(uint16_t*)(s + 0x3c) = 0;
    *(float*)(s + 0x40) = *(const float*)0x1637118;
    *(float*)(s + 0x44) = *(const float*)0x163711c;
    *(float*)(s + 0x48) = *(const float*)0x1637120;
    *(float*)(s + 0x4c) = 1.0f;
    ((Matrix3*)(s + 0x50))->Assign(*(const Matrix3*)0x163725c);
    ElemCtor(s, a);
    return self;
}

// @ 0x007d4ae0
struct cEffectParams {
    char data[0xd8];
    cEffectParams();
    ~cEffectParams();
    bool Handle(int kind, void* a, int b);
    char Handle2(int kind, void* a);
    void Tick(void* arg);
};
cEffectParams::~cEffectParams() {
    // destroy mUnknownParams[9] then free the two parameter-storage vectors
}

// @ 0x007d4b60
bool cEffectParams::Handle(int kind, void* pa, int n) {
    char* s = (char*)this;
    int* a = (int*)pa;
    char changed = 0;
    char oldVisible = 0;
    if (kind == 6) {
        if (*(int*)(s + 0x18) != a[0] || (n == 2 && *(int*)(s + 0x1c) != a[1])) {
            oldVisible = s[0x14];
            if (oldVisible) { /* vcall slot 0xc(1) */ }
            Obj* p = *(Obj**)(s + 0x38);
            if (p) { *(void**)(s + 0x38) = 0; /* release or dec */ }
            *(int*)(s + 0x18) = a[0];
            if (n >= 2) *(int*)(s + 0x1c) = a[1];
            if (oldVisible) { /* vcall slot 8(1) */ }
        }
        changed = 1;
    }
    unsigned cnt = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < cnt; ++i) {
        Obj* c = *(Obj**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = (*(char(__thiscall**)(Obj*, int, void*, int))((*(void***)c)[0x20 / 4]))(c, kind, pa, n);
        if (r || changed) changed = 1;
    }
    return changed != 0;
}

// @ 0x007d4c60
char cEffectParams::Handle2(int kind, void* pa) {
    char* s = (char*)this;
    int* a = (int*)pa;
    char changed = 0;
    if (kind == 1) {
        if (*(void**)(s + 0x38)) { AutoRefCount* r = (AutoRefCount*)(s + 0x38); r->operator=((Obj*)a); changed = 1; }
    } else if (kind == 3) {
        unsigned n = (unsigned)a[3];
        unsigned i;
        for (i = 0; i < n; ++i) {
            if (*(int*)((char*)a + 0x18 + i * 0x10) == (int)*(uint8_t*)(*(int*)(s + 0xc) + 0x85)) break;
        }
        if (i < n) {
            int lo = *(int*)((char*)a + i * 0x10);
            int hi = *(int*)((char*)a + i * 0x10 + 4);
            if ((lo & hi) != -1) {
                *(int*)(s + 0x18) = lo;
                *(int*)(s + 0x1c) = hi;
            }
        }
        return 1;
    } else if (kind == 6 && *(int*)(*(int*)(s + 0xc) + 0x2c) == 0) {
        int r = (*(int(__thiscall**)(void*, int))((*(void***)a)[0xc / 4]))(a, 0);
        if (r) *(int*)(s + 0xc4) = r;
    }
    unsigned cnt = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < cnt; ++i) {
        Obj* c = *(Obj**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = (*(char(__thiscall**)(Obj*, int, void*))((*(void***)c)[0x24 / 4]))(c, kind, pa);
        if (r || changed) changed = 1;
    }
    return changed;
}

// @ 0x007d4dd0  (1123-byte effect update; approximate)
void cEffectParams::Tick(void* arg) {
    char* s = (char*)this;
    (void)s; (void)arg;
}

// @ 0x007d5240
void* InitTransformBig(void* self, int a, unsigned pair, float f1, float f2, float f3, float f4,
                       const Matrix3* m, Obj* obj) {
    char* s = (char*)self;
    *(uint16_t*)(s) = (uint16_t)pair;
    *(uint16_t*)(s + 2) = (uint16_t)(pair >> 16);
    *(float*)(s + 4) = f1;
    *(float*)(s + 8) = f2;
    *(float*)(s + 0xc) = f3;
    *(float*)(s + 0x10) = f4;
    ((Matrix3*)(s + 0x14))->Assign(*m);
    *(int*)(s + 0x38) = a;
    ((AutoRefCount*)(s + 0x3c))->operator=(obj);
    return self;
}

struct Elem40 {
    uint16_t a, b;
    float f4, f8, fc, f10;
    Matrix3 mat;        // +0x14
    uint32_t f38;       // +0x38
    AutoRefCount ref;   // +0x3c
    Elem40(const Elem40& o);
};
// @ 0x007d5300
Elem40::Elem40(const Elem40& o) {
    a = o.a; b = o.b;
    f4 = o.f4; f8 = o.f8; fc = o.fc; f10 = o.f10;
    mat.Assign(o.mat);
    f38 = o.f38;
    ref = o.ref.mpObject;
}

// @ 0x007d53a0
void* CopyElemRange40(void* first, void* last, void* dst) {
    char* f = (char*)first; char* l = (char*)last; char* d = (char*)dst;
    while (f != l) {
        *(uint16_t*)(d) = *(const uint16_t*)(f);
        *(uint16_t*)(d + 2) = *(const uint16_t*)(f + 2);
        *(float*)(d + 4) = *(const float*)(f + 4);
        *(float*)(d + 8) = *(const float*)(f + 8);
        *(float*)(d + 0xc) = *(const float*)(f + 0xc);
        *(float*)(d + 0x10) = *(const float*)(f + 0x10);
        *(cSPTransform*)(d + 0x14) = *(const cSPTransform*)(f + 0x14);
        *(int*)(d + 0x38) = *(const int*)(f + 0x38);
        Obj* p = *(Obj**)(f + 0x3c);
        *(Obj**)(d + 0x3c) = p;
        if (p) p->AddRef();
        f += 0x40; d += 0x40;
    }
    return d;
}

// @ 0x007d5520
void* CopyBackwardsTransforms(void* first, void* last, void* dst) {
    char* f = (char*)first; char* l = (char*)last; char* d = (char*)dst;
    if (l == f) return d;
    do {
        l -= 0x40; d -= 0x40;
        *(cSPTransform*)(d) = *(const cSPTransform*)(l);
        *(int*)(d + 0x38) = *(const int*)(l + 0x38);
        AutoRefCount* r = (AutoRefCount*)(d + 0x3c);
        r->operator=(*(Obj**)(l + 0x3c));
    } while (l != f);
    return d;
}

// @ 0x007d5590
void* CopyElem38(void* self, void* a, const void* src) {
    char* s = (char*)self; const char* o = (const char*)src;
    *(uint16_t*)(s) = *(const uint16_t*)(o);
    *(uint16_t*)(s + 2) = *(const uint16_t*)(o + 2);
    *(float*)(s + 4) = *(const float*)(o + 4);
    *(float*)(s + 8) = *(const float*)(o + 8);
    *(float*)(s + 0xc) = *(const float*)(o + 0xc);
    *(float*)(s + 0x10) = *(const float*)(o + 0x10);
    ((Matrix3*)(s + 0x14))->Assign(*(const Matrix3*)(o + 0x14));
    ((ElemPart*)s)->Init(a);
    return self;
}

// @ 0x007d55e0
cEffectParams::cEffectParams() {
    char* s = (char*)this;
    for (int i = 0; i < 0xd8; ++i) s[i] = 0;
}
