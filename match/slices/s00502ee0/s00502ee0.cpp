// w1g1 slice s00502ee0 -- /Od EASTL vector machinery for two element types:
//   A   (0x54) = cSPTransform base + cSPVector3 + bool + int[2] + int
//   E48 (0x48) = cSPVector3 + fixed_vector<unsigned int,8> + uint
//   Ed8 (0xd8) = 4 dwords + fixed_vector + 3 x (cSPVector3 + cSPMatrix3)
// plus copy-ctors, operator=, copy_backward/relocate/destroy helpers.
//
// Flags: /Od /Ob1 /MD /Gy /TP  (frame pointer, all locals in memory, no C++ EH).
//
// Byte-exact functions: 00502ee0 (A copy-ctor), 005039c0 (A operator=),
// 00503250 (E48 copy-ctor), 00503630 (zero-4 init). The remaining helpers are
// complete behavioral ports whose only difference is the /Od frame hole layout.

typedef unsigned int uint32_t;
template<int N> inline void ScratchSlots() { unsigned int s[N]; }
inline void* operator new(unsigned int, void* p) { return p; }

// ---------------------------------------------------------------------------
// 12-byte float vectors.  Two flavours are needed: the copy-ctor of cSPVector3
// (used inside cSPTransform-derived objects) leaves a large scratch frame, the
// plain one only a small one.
// ---------------------------------------------------------------------------
struct VecA {                                   // cSPVector3 inside the 0x54 class
    float x, y, z;
    VecA() {}
    VecA(const VecA& o) { ScratchSlots<14>(); x = o.x; y = o.y; z = o.z; }
};

struct VecE {                                   // cSPVector3 used by the 0x48 element
    float x, y, z;
    VecE() {}
    VecE(const VecE& o) { ScratchSlots<6>(); x = o.x; y = o.y; z = o.z; }
};

// ---------------------------------------------------------------------------
// eastl::fixed_vector<unsigned int,8>; its copy-ctor is 0x5030e0, erase 0x4769b0,
// assign 0x42c750, deallocate 0x4c0b80.
// ---------------------------------------------------------------------------
struct FixedVec {
    uint32_t* mpBegin;          // 0x00
    uint32_t* mpEnd;            // 0x04
    uint32_t* mpCapacity;       // 0x08
    uint32_t mAllocator[3];     // 0x0c
    uint32_t mFixedBuffer[8];   // 0x18  (0x38 total)
    FixedVec(const FixedVec&);                          // 0x5030e0
    void erase(uint32_t* first, uint32_t* last);        // 0x4769b0
    void assign(uint32_t* first, uint32_t* last, bool); // 0x42c750
    void Destroy();                                     // 0x4c0b80
    FixedVec& operator=(const FixedVec& o) {
        if (this != &o) {
            erase(mpBegin, mpEnd);
            assign(o.mpBegin, o.mpEnd, false);
        }
        return *this;
    }
};

// ---------------------------------------------------------------------------
// cSPTransform (0x38): copy-ctor 0x40ce80, operator= 0x537dc0.
// ---------------------------------------------------------------------------
struct Base {
    unsigned short mFlags, mModificationCount;   // 0x00
    float tx, ty, tz;                            // 0x04
    float mScale;                                // 0x10
    char mRotation[0x24];                        // 0x14
    Base() {}
    Base(const Base&);              // 0x40ce80
    Base& operator=(const Base&);   // 0x537dc0
};

// ---------------------------------------------------------------------------
// A (0x54)
// ---------------------------------------------------------------------------
struct A : Base {
    VecA v;             // 0x38
    bool b;             // 0x44
    int arr[2];         // 0x48
    int c;              // 0x50
};

// @ 0x00502ee0 (A copy-ctor) and @ 0x005039c0 (A operator=)
A* forceA(const A& s, A* p) { A* q = new A(s); *p = s; return q; }

// ---------------------------------------------------------------------------
// E48 (0x48)
// ---------------------------------------------------------------------------
struct E48 {
    VecE v;             // 0x00
    FixedVec vec;       // 0x0c
    uint32_t f44;       // 0x44
    E48(const E48&);    // 0x503250
};

E48::E48(const E48& o) : v(o.v), vec(o.vec), f44(o.f44) {}

// @ 0x00503250 / 0x00503930
E48* forceE48(const E48& s, E48* p) { E48* q = new E48(s); *p = s; return q; }

// @ 0x00503630 -- four-dword initialiser returning this
struct S4 { int a, b, c, d; S4* Init(); };
S4* S4::Init() { a = 0; b = 0; c = 0; d = 0; return this; }

// ---------------------------------------------------------------------------
// Range helpers for E48.
// ---------------------------------------------------------------------------

void EASTL_allocator_deallocate(void* p);       // 0x00f47380
inline void DeleteElemConditional(void* p, int flags)
{
    if (flags & 1) EASTL_allocator_deallocate(p);
}

// @ 0x00503be0
E48* destroy_E48(E48* first, E48* last, E48* result)
{
    ScratchSlots<3>();
    for (; first != last; ++first, ++result) {
        FixedVec& v = first->vec;
        for (uint32_t* p = v.mpBegin; p < v.mpEnd; ++p) {}
        v.Destroy();
        DeleteElemConditional(first, 0);
    }
    return result;
}

// @ 0x005031d0
E48* relocate_E48(E48* first, E48* last, E48* result)
{
    const bool bHasTrivialCopy = false;
    E48* dst = result;
    E48* src = first;
    while (src != last) {
        new (dst) E48(*src);
        ++src;
        ++dst;
    }
    destroy_E48(first, last, result);
    return dst;
}

inline E48* copy_backward_impl(E48* first, E48* last, E48* resultEnd)
{
    while (last != first) {
        --last;
        --resultEnd;
        *resultEnd = *last;
    }
    return resultEnd;
}

// @ 0x00503180
E48* copy_backward_E48(E48* first, E48* last, E48* resultEnd)
{
    ScratchSlots<7>();
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl(first, last, resultEnd);
}

E48* forceAlgos(E48* a, E48* b, E48* c, E48* d)
{
    destroy_E48(a, b, c);
    copy_backward_E48(a, b, d);
    return relocate_E48(a, b, c);
}

// ---------------------------------------------------------------------------
// Ed8 (0xd8)
// ---------------------------------------------------------------------------
struct Mat3 { VecA x, y, z; Mat3(const Mat3&); };   // 0x24, copy-ctor 0x41cb40

struct Ed8 {
    int m0, m1, m2, m3;     // 0x00
    FixedVec vec;           // 0x10
    VecA t0;                // 0x48
    Mat3 r0;                // 0x54
    VecA t1;                // 0x78
    Mat3 r1;                // 0x84
    VecA t2;                // 0xa8
    Mat3 r2;                // 0xb4
};

// @ 0x00502f60 / 0x00503a50
Ed8* forceEd8(const Ed8& s, Ed8* p) { Ed8* q = new Ed8(s); *p = s; return q; }

// @ 0x005033f0
Ed8* destroy_Ed8(Ed8* first, Ed8* last, Ed8* result)
{
    ScratchSlots<3>();
    for (; first != last; ++first, ++result) {
        FixedVec& v = first->vec;
        for (uint32_t* p = v.mpBegin; p < v.mpEnd; ++p) {}
        v.Destroy();
        DeleteElemConditional(first, 0);
    }
    return result;
}
