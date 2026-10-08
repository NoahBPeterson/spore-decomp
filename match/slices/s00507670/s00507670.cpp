// w1g1 slice s00507670 -- destructor/constructor helpers for a large anim/vector
// container class (vector members at +0x08/+0x1c/+0x30/+0x44/+0x6c/+0x80).
//
// Flags: /Od /Ob1 /MD /Gy /TP.

typedef unsigned int uint32_t;

void ea_delete(void* p);              // operator_delete__

struct Container;

void DestroySubA();                   // 0x005156b0
void DestroySubB();                   // 0x00425990
void DestroySubC();                   // 0x0050ea50

// @ 0x00507b30  (destroy the six vector members)
void __fastcall DestroyVectors(Container* self)
{
    char* base = (char*)self;
    for (uint32_t* p = *(uint32_t**)(base + 0x80); p < *(uint32_t**)(base + 0x84); p += 3) {}
    DestroySubA();
    for (uint32_t* p = *(uint32_t**)(base + 0x6c); p < *(uint32_t**)(base + 0x70); p += 1) {}
    DestroySubB();
    for (uint32_t* p = *(uint32_t**)(base + 0x44); p < *(uint32_t**)(base + 0x48); p += 5) {}
    DestroySubC();
    for (uint32_t* p = *(uint32_t**)(base + 0x30); p < *(uint32_t**)(base + 0x34); p += 1) {}
    DestroySubB();
    for (uint32_t* p = *(uint32_t**)(base + 0x1c); p < *(uint32_t**)(base + 0x20); p += 1) {}
    DestroySubB();
    for (uint32_t* p = *(uint32_t**)(base + 0x08); p < *(uint32_t**)(base + 0x0c); p += 1) {}
    DestroySubB();
}

struct CSetA { char pad[0x14]; CSetA& operator=(const CSetA& o); };   // 0x0050d440
struct CSetB { char pad[0x14]; CSetB& operator=(const CSetB& o); };   // 0x0050da90
struct CSetC { char pad[0x14]; CSetC& operator=(const CSetC& o); };   // 0x00565be0

struct Container {                  // 0x94-byte element ("Skinner" allocation)
    int    m00, m04;
    CSetA  m08, m1c, m30;
    CSetB  m44;
    float  m58, m5c, m60, m64;
    int    m68;
    CSetA  m6c;
    CSetC  m80;
    ~Container();
    Container(const Container& src);      // 0x00508320 (copy constructor)
};

// @ 0x00507670  (container destructor)
void __fastcall Container_dtor(Container* self)
{
    char* base = (char*)self;
    uint32_t* begin = *(uint32_t**)(base + 0xe4);
    uint32_t* end   = *(uint32_t**)(base + 0xe8);
    for (uint32_t i = 0; i < (uint32_t)(end - begin); ++i) {
        void* p = (void*)begin[i];
        if (p != 0) {
            DestroyVectors((Container*)p);
            ea_delete(p);
        }
        begin[i] = 0;
    }
    void* p59 = *(void**)(base + 0x164);
    if (p59 != 0) {
        ((Container*)p59)->~Container();
        ea_delete(p59);
    }
    *(void**)(base + 0x164) = 0;
}

Container::~Container() {}   // placeholder for the inlined sub-destructor call

// ---------------------------------------------------------------------------
// @ 0x00507c70  copy constructor of the 0x1d0-byte ref-counted container (vtable 0x013f18cc):
// default-constructs every member, then assigns the vector/set members from the source and
// deep-copies the element pointers of the vector at +0xe4 (each element is a 0x94-byte object).
// ---------------------------------------------------------------------------
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);

struct Alloc { Alloc() {} };
struct SpAlloc { char pad[8]; SpAlloc(const Alloc& a); };                 // 0x00429360
struct VSetImpl {                                            // vector_set<unsigned>, 0x14 bytes
    char pad[0x14];
    VSetImpl(const Alloc& a);                                // 0x00540470
};
template <int K> struct VSetK : VSetImpl {
    VSetK(const Alloc& a) : VSetImpl(a) {}
    VSetK& operator=(const VSetK& o);       // K=0: 0x00473500, K=1: 0x00473b00, K=2: 0x0050d070
};
typedef VSetK<0> VSet;
typedef VSetK<1> VSetB;
typedef VSetK<2> VSetC;
struct VSetD : VSetImpl { VSetD() : VSetImpl(Alloc()) {} };
struct Vec {                                                 // 0x14-byte vector
    void* mpBegin; void* mpEnd; void* mpCap; SpAlloc mAlloc;
    Vec(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    Vec& operator=(const Vec& o);                            // 0x0050d4e0
};
struct VecP {                                                // vector of element pointers
    Container** mpBegin; Container** mpEnd; Container** mpCap; SpAlloc mAlloc;
    VecP(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    VecP& operator=(const VecP& o);                          // 0x0050d4e0
    unsigned int size() const { return mpEnd - mpBegin; }
    Container*& operator[](unsigned int i) { return mpBegin[i]; }
};
struct VecG {
    void* mpBegin; void* mpEnd; void* mpCap; SpAlloc mAlloc;
    VecG(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    VecG& operator=(const VecG& o);                          // 0x0050d750
};
struct VecU {                                                // SP::SimpleVector<unsigned>
    unsigned int* mpBegin; unsigned int* mpEnd; unsigned int* mpCap; SpAlloc mAlloc;
    VecU(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    unsigned int* erase(unsigned int* first, unsigned int* last);   // 0x004769b0
    void clear() { erase(mpBegin, mpEnd); }
};
struct VecT {                                                // member at +0x17c
    void* mpBegin; void* mpEnd; void* mpCap; SpAlloc mAlloc;
    VecT(const Alloc& a) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    void Clear();                                            // 0x004208f0
};
struct BBox { char pad[0x18]; BBox() { Reset(); } void Reset(); };                     // BoundingBox_Reset 0x00409c00

struct GmeRefCount {
    int mnRefCount;
    GmeRefCount() : mnRefCount(0) {}
    virtual ~GmeRefCount();
};

struct Skin : GmeRefCount {
    VSet   m08, m1c;
    VSetB  m30;
    VSetC  m44;
    VSet   m58, m6c;
    Vec    m80, m94;
    VSet   ma8;
    Vec    mbc;
    VSetD  md0;
    VecP   me4;
    Vec    mf8;
    int    m10c;
    Vec    m110;
    VecG   m124;
    Vec    m138;
    BBox   m14c;
    void*  m164;
    VecU   m168;
    VecT   m17c;
    Vec    m190;
    VSet   m1a4;
    VecG   m1b8;
    int    m1cc;

    Skin(const Skin& o);
    virtual ~Skin();
};

Skin::Skin(const Skin& o)
    : m08(Alloc()), m1c(Alloc()), m30(Alloc()), m44(Alloc()), m58(Alloc()), m6c(Alloc()),
      m80(Alloc()), m94(Alloc()), ma8(Alloc()), mbc(Alloc()), md0(), me4(Alloc()),
      mf8(Alloc()), m110(Alloc()), m124(Alloc()), m138(Alloc()), m14c(), m164(0),
      m168(Alloc()), m17c(Alloc()), m190(Alloc()), m1a4(Alloc()), m1b8(Alloc())
{
    m08 = o.m08;
    m1c = o.m1c;
    m30 = o.m30;
    m44 = o.m44;
    m58 = o.m58;
    m6c = o.m6c;
    m80 = o.m80;
    m94 = o.m94;
    ma8 = o.ma8;
    mbc = o.mbc;
    m110 = o.m110;
    m138 = o.m138;
    m124 = o.m124;
    me4 = o.me4;
    for (unsigned int i = 0; i < me4.size(); ++i) {
        me4[i] = new("Skinner", 0, 0, 0, 0) Container(*me4[i]);
    }
    m10c = o.m10c;
    m1b8 = o.m1b8;
    m1cc = o.m1cc;
    m190 = o.m190;
    m168.clear();
    m17c.Clear();
}

// ---------------------------------------------------------------------------
// @ 0x00508320  (copy-constructor-ish: header words then sub-objects)
// ---------------------------------------------------------------------------
template <int N> inline void ScratchSlots() { unsigned int slots[N]; }

Container::Container(const Container& src)
{
    ScratchSlots<21>();
    m00 = src.m00;
    m04 = src.m04;
    m08 = src.m08;
    m1c = src.m1c;
    m30 = src.m30;
    m44 = src.m44;
    m58 = src.m58;
    m5c = src.m5c;
    m60 = src.m60;
    m64 = src.m64;
    m68 = src.m68;
    m6c = src.m6c;
    m80 = src.m80;
}
