struct HkMem_0107f000 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void Dealloc(void* p, int size, int align);
};

struct HkRef_0107f000 {
    virtual ~HkRef_0107f000();
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

struct Base_0107f000 {
    short m4;
    short m6;
    virtual ~Base_0107f000() {}
};

struct Obj_0107f000 : public Base_0107f000 {
    HkRef_0107f000* m8;

    virtual ~Obj_0107f000() {
        if (m8) {
            m8->removeReference();
        }
    }

    void operator delete(void* p) {
        Obj_0107f000* self = (Obj_0107f000*)p;
        int size = (unsigned short)self->m4;
        HkMem_0107f000* mem = *(HkMem_0107f000**)0x016e4178;
        mem->Dealloc(p, size, 0x17);
    }

    void* ScalarDtor(unsigned int flags);
};

// @ 0x0107f000
void* Obj_0107f000::ScalarDtor(unsigned int flags) {
    this->Obj_0107f000::~Obj_0107f000();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
