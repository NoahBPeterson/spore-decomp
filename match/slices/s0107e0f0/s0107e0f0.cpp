struct HkMem_0107e0f0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void* Alloc(int size, int align);
};

extern "C" void __cdecl Fn_0107f470(void* dst, int val, int size);

struct Obj_0107e0f0 {
    void* m0;
    int m4;
    int m8;

    Obj_0107e0f0* Match_0107e0f0();
};

// @ 0x0107e0f0
Obj_0107e0f0* Obj_0107e0f0::Match_0107e0f0() {
    HkMem_0107e0f0* mem = *(HkMem_0107e0f0**)0x016e4178;
    m0 = mem->Alloc(0x100, 0x14);
    Fn_0107f470(m0, 0, 0x100);
    m4 = 0;
    m8 = 0xf;
    Fn_0107f470(m0, 0, 0x100);
    m4 = 0;
    return this;
}
