extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long dwTlsIndex);

struct HkMem_010e19f0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void Dealloc(void* p, int size, int align);
};

struct HkTlsMem_010e19f0 {
    void FreeArray(void* p, int size, int align);
};

struct HkArray_010e19f0 {
    void* m_data;
    int m_size;
    int m_capacityAndFlags;

    ~HkArray_010e19f0() {
        if ((m_capacityAndFlags & 0x80000000) == 0) {
            HkTlsMem_010e19f0* tls = (HkTlsMem_010e19f0*)TlsGetValue(*(unsigned long*)0x016e4174);
            tls->FreeArray(m_data, (m_capacityAndFlags & 0x3fffffff) * 12, 0x14);
        }
    }
};

struct Base_010e19f0 {
    short m4;
    short m6;
    int m8;
    virtual ~Base_010e19f0() {}
};

struct Obj_010e19f0 : public Base_010e19f0 {
    HkArray_010e19f0 m_arr;

    virtual ~Obj_010e19f0() {}

    void operator delete(void* p) {
        Obj_010e19f0* self = (Obj_010e19f0*)p;
        int size = (unsigned short)self->m4;
        HkMem_010e19f0* mem = *(HkMem_010e19f0**)0x016e4178;
        mem->Dealloc(p, size, 0x1c);
    }

    void* ScalarDtor(unsigned int flags);
};

// @ 0x010e19f0
void* Obj_010e19f0::ScalarDtor(unsigned int flags) {
    this->Obj_010e19f0::~Obj_010e19f0();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
