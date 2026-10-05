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

struct Container {
    char pad[0x200];
    ~Container();
    void* Ctor(int param);      // 0x00507c70
    void* Copy(void** src);     // 0x00508320
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
// @ 0x00507c70  (PARTIAL skeleton)
// ---------------------------------------------------------------------------
void* Container::Ctor(int param)
{
    (void)param;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00508320  (copy-constructor-ish: header words then sub-objects)
// ---------------------------------------------------------------------------
void SubCopyA(const void* src);   // 0x0050d440
void SubCopyB(const void* src);   // 0x0050da90
void SubCopyC(const void* src);   // 0x00565be0

void* Container::Copy(void** src)
{
    void** dst = (void**)this;
    dst[0] = src[0];
    dst[1] = src[1];
    SubCopyA(src + 2);
    SubCopyA(src + 7);
    SubCopyA(src + 0xc);
    SubCopyB(src + 0x11);
    dst[0x16] = src[0x16];
    dst[0x17] = src[0x17];
    dst[0x18] = src[0x18];
    dst[0x19] = src[0x19];
    dst[0x1a] = src[0x1a];
    SubCopyA(src + 0x1b);
    SubCopyC(src + 0x20);
    return this;
}
