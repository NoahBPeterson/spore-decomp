// Simulator content-validation summarizer (cContentValidationSummarizer) and its Timer helper.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP (no EH).
#include "types.h"

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t*);

// ---------------------------------------------------------------- Timer
struct Timer {
    uint64_t start;
    uint32_t pad[2];
    int mode;   // 1 = rdtsc, otherwise QueryPerformanceCounter
    void StartIfUnset();
};

// @ 0x00435480
void Timer::StartIfUnset() {
    if (start == 0) {
        if (mode == 1) {
            uint64_t t;
            __asm { rdtsc } __asm { mov dword ptr [t+4], edx } __asm { mov dword ptr [t], eax }
            start = t;
        } else {
            int64_t t;
            QueryPerformanceCounter(&t);
            start = t;
        }
    }
}

// ---------------------------------------------------------------- helper types
struct IObj1 { virtual void v0(); virtual void Rel1(); virtual void Rel2(); };
struct IMgr : IObj1 { virtual void m3(); virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15(); virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19(); virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23(); virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27(); virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31(); virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35(); virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39(); virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43(); virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47(); virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51(); virtual void m52(); virtual void Detach(void* a, int b, int c); };
struct RefA { IObj1* p; inline ~RefA() { if (p) p->Rel1(); } };
struct RefM { IMgr* p; inline IMgr* get() const { return p; } inline IMgr* operator->() const { return p; }
              inline ~RefM() { if (p) p->Rel1(); } };
struct RefB { IObj1* p; inline ~RefB() { if (p) p->Rel2(); } };
struct Counted { void Release(); };
struct CountedPtr { Counted* p; inline Counted* get() const { return p; } inline ~CountedPtr() { if (p) p->Release(); } };

struct Summ;
struct SummPtr {
    Summ* p;
    inline Summ* get() const { return p; }
    inline Summ* operator->() const { return p; }
    inline ~SummPtr();
};

struct Rec { uint32_t id, a, b, value, d; };
struct RecVec { Rec* begin; Rec* end; Rec* cap; inline int size() const { return end - begin; } ~RecVec(); };
struct T540520 { uint32_t a[0x78/4]; ~T540520(); };
struct T4e1bf0 { uint32_t a[0x38/4]; ~T4e1bf0(); };
struct T4b5440 { uint32_t a[0x38/4]; ~T4b5440(); };
struct T5333d0 { uint32_t a[0x1c/4]; ~T5333d0(); };
struct T4554a0 { uint32_t a[4]; void Free(uint32_t); inline ~T4554a0() { Free(a[3]); } };
struct T4543c0 { uint32_t a[0x34/4]; ~T4543c0(); };
struct ByteFixedBuf { uint32_t a[0x34/4]; void ReleaseHeap(); inline ~ByteFixedBuf() { ReleaseHeap(); } };
struct T454e90 { uint32_t* b; uint32_t* e; uint32_t pad[0x98/4]; void Clear(uint32_t* b, uint32_t* e); void Free();
                 inline ~T454e90() { Clear(b, e); Free(); } };
struct T453dc0 { uint32_t a[0x108/4]; ~T453dc0(); };
struct Pool;
struct Node { uint32_t a, b; Pool* pool; inline Pool* GetPool() const { return pool; } void Destroy(); };
struct Pool { void Free(char* tag, Node* n); };
struct Owner { bool Check(); };   // FUN_004adc40
void EASTL_allocator_deallocate(void*); // 0x00f47380

// 60-bit flag set stored as two words
struct BitSet60 {
    uint32_t w[2];
    __forceinline void Set(uint32_t n, bool v) {
        if (n < 60) {
            if (v) { uint32_t* p = &w[n / 32]; *p = (1u << (n % 32)) | *p; }
            else   { uint32_t* p = &w[n / 32]; *p = ~(1u << (n % 32)) & *p; }
        }
    }
};

struct Base0 { virtual ~Base0() {} uint32_t x; };
struct Base1 { virtual ~Base1() {} void* CastInterface(uint32_t id); };   // cEditorResource part, at +8

struct Summ : Base0, Base1 {
    RefA f0c; CountedPtr f10; CountedPtr f14; RefM f18;
    uint32_t pad1[(0x28-0x1c)/4];
    Owner* f28;
    uint32_t pad1b;
    float f30;
    uint32_t pad1c[(0x154-0x34)/4];
    RefA f154[3]; RefA f160;
    uint32_t pad2a[(0x18c-0x164)/4];
    Node* f18c;
    uint32_t pad2[(0x234-0x190)/4];
    T453dc0 f234;
    RefB f33c; T454e90 f340;
    SummPtr f3e0; RefB f3e4; uint32_t f3e8; RefA f3ec; CountedPtr f3f0;
    uint32_t pad3[(0x460-0x3f4)/4];
    ByteFixedBuf f460; ByteFixedBuf f494; T4543c0 f4c8;
    uint32_t pad4[(0x614-0x4fc)/4];
    T4554a0 f614; uint32_t pad4b[3]; T5333d0 f630;
    uint32_t pad5[(0x6cc-0x64c)/4];
    T4b5440 f6cc; T4e1bf0 f704; T4e1bf0 f73c;
    T540520 f774, f7ec, f864, f8dc, f954, f9cc, fa44, fabc, fb34;
    uint32_t pad6[(0xc0c-0xbac)/4];
    RecVec recs;
    uint32_t pad7[(0xdb4-0xc18)/4];
    uint32_t resDb4, resDb8, resDbc;
    uint32_t pad8[2];
    BitSet60 bits;
    uint32_t pad9[(0xe00-0xdd0)/4];
    RefA fe00;

    virtual ~Summ();
    Summ* ScalarDelete(uint32_t flags);
    void SetOwner(Owner* o);
    float GetF30();
    uint32_t LookupRecord(uint32_t id);
    uint32_t GetResource(uint32_t id);
    bool HasFlag3B3C();
    inline bool TestBit(uint32_t i);
    void SetFlag(uint32_t n, bool v);
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};

inline SummPtr::~SummPtr() { if (p) ((IObj1*)p)->Rel2(); }

// @ 0x00435510
Summ::~Summ() {
    if (f10.get() && f18.get()) f18->Detach(f10.get(), 0, 0);
    if (f18c) { char tag; f18c->GetPool()->Free(&tag, f18c); f18c->Destroy(); }
    f18c = 0;
}

// @ 0x004354E0  (scalar deleting destructor)
Summ* Summ::ScalarDelete(uint32_t flags) {
    this->Summ::~Summ();
    if (flags & 1) operator delete(this);
    return this;
}

// @ 0x00435A10
void Summ::SetFlag(uint32_t n, bool v) {
    bits.Set(n, v);
    if (f28) {
        if (f28->Check()) {
            if (f3e0.get()) f3e0->bits.Set(n, v);
        }
    }
}

// @ 0x004359B0
void* Base1::CastInterface(uint32_t id) {
    switch (id) {
    case 0xefd66f0b: return (char*)this - 8; break;
    case 0xee3f516e: return static_cast<Base1*>((Summ*)((char*)this - 8));
    }
    return 0;
}

// @ 0x00435B60
uint32_t Summ::LookupRecord(uint32_t id) {
    int i;
    int n;
    for (i = 0, n = recs.size(); i < n; i++)
        if (recs.begin[i].id == id) return recs.begin[i].value;
    return 0;
}

// @ 0x00435BE0
void Summ::SetOwner(Owner* o) { f28 = (Owner*)o; }

// @ 0x00435C00
float Summ::GetF30() { return f30; }

// @ 0x00435C20
uint32_t Summ::GetResource(uint32_t id) {
    switch (id) {
    case 0xdd94fb65: return resDb4; break;
    case 0x2dc2a89d: return resDbc; break;
    case 0x0e40c402: return resDb8; break;
    }
    return 0;
}

inline bool Summ::TestBit(uint32_t i) {
    uint32_t w; bool r;
    if (i < 60) { w = bits.w[i / 32]; r = (w & (1u << (i % 32))) != 0; } else r = false;
    return r;
}

// @ 0x00435C80
bool Summ::HasFlag3B3C() { return TestBit(0x39) || TestBit(0x3a); }
