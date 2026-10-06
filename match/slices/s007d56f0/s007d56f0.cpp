// SWARM cSplitManager / editor-resource cluster (0x007d56f0..0x007d67xx).
// No function is byte-exact; see nonmatching.txt / partial.txt.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"

void* operator new[](size_t size);
void  operator delete[](void* p);
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void  operator delete(void* p);
inline void* operator new(size_t, void* p) { return p; }

struct cSPTransform {                      // size 0x38
    float m[0x38 / 4];
    cSPTransform& operator=(const cSPTransform& o);   // 0x537dc0
};
struct Obj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual void AddRef();    // +0x34
    virtual void Release();   // +0x38
};
struct cSplitInstance {                     // element body of the 0x78 record
    void* f0;
    cSplitInstance(const void* src);        // 0x799450
};
struct Elem78 {
    uint32_t f0;      // +0
    uint8_t  f4;      // +4
    char pad[3];
    cSPTransform a;   // +8
    cSPTransform b;   // +0x40
};
struct Elem40 {
    uint16_t a, b; float f4, f8, fc, f10;
    float mat[9]; uint32_t f38; Obj* ref;
};

void* VecAlloc0x78(unsigned n);             // 0x7d48e0
char** UninitCopyElem78(char**, char*, char*, char*, unsigned);  // 0x7d5aa0

// --------------------------------------------------------- vector helpers
// @ 0x007d56f0  eastl::vector<Elem78>::DoInsertValue (825 bytes): skeleton
void Elem78DoInsertValue(void* self, void* pos, unsigned n, void* value) {
    (void)self; (void)pos; (void)n; (void)value;
}

// @ 0x007d5a30  eastl::vector<Elem40-ish,0x40>::~vector
struct Vec40 { char* mpBegin; char* mpEnd; char* mpCap; void* a1; void* a2; ~Vec40(); };
Vec40::~Vec40() {
    for (char* p = mpBegin; p < mpEnd; p += 0x40) {
        Obj* r = *(Obj**)(p + 0x3c);
        if (r) r->Release();
    }
    if (mpBegin && *(int*)(mpBegin - 4) != 0) operator delete[](mpBegin);
}

// @ 0x007d5aa0
char** UninitCopyElem78(char** out, char* first, char* last, char* base, unsigned n) {
    *out = base;
    while (first != last) {
        char* p = *out;
        if (p) { *(uint32_t*)p = *(uint32_t*)first; new (p + 4) cSplitInstance(first + 4); }
        *out = *out + 0x78;
        first += 0x78;
    }
    (void)n;
    return out;
}

// @ 0x007d5af0  big effect-component ctor (skeleton)
void* InitComp(void* self, int a, int b) {
    char* s = (char*)self;
    *(void**)(s + 0xc) = (void*)a;
    *(void**)(s + 0x10) = (void*)b;
    *(uint8_t*)(s + 0x14) = 0;
    *(uint8_t*)(s + 0x15) = 1;
    *(uint8_t*)(s + 0x16) = 0;
    *(uint32_t*)(s + 0x18) = 0xffffffff;
    *(uint32_t*)(s + 0x1c) = 0xffffffff;
    for (int i = 0; i < 5; ++i) *(float*)(s + 0x20 + i * 4) = 1.0f;
    *(float*)(s + 0x34) = 0.0000099999997f;
    return self;
}

// @ 0x007d5c50
void EffectAddParam(void* self, int kind, void* value) { (void)self; (void)kind; (void)value; }
// @ 0x007d5d50
void EffectSetParam(void* self, void* value) { (void)self; (void)value; }
// @ 0x007d5dc0
void EffectNotify(void* self, int kind, void* value) { (void)self; (void)kind; (void)value; }
// @ 0x007d5e60
int EffectApply(void* self, void* value, float f) { (void)self; (void)value; (void)f; return 0; }
// @ 0x007d6030
int EffectApply2(void* self, void* value, float f) { (void)self; (void)value; (void)f; return 0; }

// @ 0x007d61f0
void* AllocAndCopy78(unsigned n, char* first, char* last) {
    char* buf = n ? (char*)operator new(n * 0x78, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    char* out = buf;
    UninitCopyElem78(&out, first, last, buf, n);
    return buf;
}

// @ 0x007d6250
Elem78* CopyElems78(Elem78* first, Elem78* last, Elem78* dst) {
    if (first == last) return dst;
    while (first != last) {
        dst->f0 = first->f0;
        dst->f4 = first->f4;
        dst->a = first->a;
        dst->b = first->b;
        ++first; ++dst;
    }
    return dst;
}

// @ 0x007d62d0
void* DeleteComp(void* self, unsigned flags) {
    char* s = (char*)self;
    // destroy mCurve vector at +0x40.. then base vtable, then optional delete
    (void)s;
    if (flags & 1) operator delete(self);
    return self;
}

// @ 0x007d6320
void* CopyVec78(void* self, void* src) {
    (void)self; (void)src;
    return self;
}

// @ 0x007d6380
void* InitEditorComp(void* self, void* a) { (void)self; (void)a; return self; }
// @ 0x007d63e0
void* DeleteEditorComp(void* self, unsigned flags) { (void)self; (void)flags; return self; }
// @ 0x007d6440
void* InitResource(void* self, void* a, float* v, void* ref) { (void)self; (void)a; (void)v; (void)ref; return self; }
// @ 0x007d6500
void DestroyResource(void* self) { (void)self; }
// @ 0x007d6620
void ResourceComplex(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
