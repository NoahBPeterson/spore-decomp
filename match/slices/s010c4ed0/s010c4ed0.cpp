struct HkMem_010c4ed0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void Dealloc(void* p, int size, int align);
};

struct HkRef_010c4ed0 {
    virtual ~HkRef_010c4ed0();
    short m4;
    short m6;

    void removeReference() {
        if (m4 != 0) {
            if (--m6 == 0) {
                delete this;
            }
        }
    }
};

struct Base_010c4ed0 {
    short m4;
    short m6;
    int m8;
    virtual ~Base_010c4ed0() {}
};

struct Obj_010c4ed0 : public Base_010c4ed0 {
    HkRef_010c4ed0* mC;

    virtual ~Obj_010c4ed0() {
        mC->removeReference();
    }

    void operator delete(void* p) {
        Obj_010c4ed0* self = (Obj_010c4ed0*)p;
        int size = (unsigned short)self->m4;
        HkMem_010c4ed0* mem = *(HkMem_010c4ed0**)0x016e4178;
        mem->Dealloc(p, size, 0x24);
    }

    void* ScalarDtor(unsigned int flags);
};

// @ 0x010c4ed0
void* Obj_010c4ed0::ScalarDtor(unsigned int flags) {
    this->Obj_010c4ed0::~Obj_010c4ed0();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
