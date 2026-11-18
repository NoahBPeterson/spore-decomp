// Slice s00c697a0: a teardown method that drops a ref-counted pointer, shuts down two
// members and then tail-calls the class's own base teardown.

struct IRefObj_s00c6_97a0 {
    virtual int AddRef();
    virtual int Release();
};

struct Member34_s00c6_97a0 {
    void Shutdown();  // 0x00c8b2e0
};

struct Member108_s00c6_97a0 {
    void Shutdown();  // 0x00bfc720
};

struct Owner_s00c6_97a0 {
    char pad00[0x2c];
    IRefObj_s00c6_97a0* mpRef;  // +0x2c
    char pad30[4];
    Member34_s00c6_97a0 m34;    // +0x34
    char pad35[0x108 - 0x35];
    Member108_s00c6_97a0 m108;  // +0x108

    void Teardown();
    void BaseTeardown();  // 0x00c69540
};

// @ 0x00c697a0
void Owner_s00c6_97a0::Teardown()
{
    if (IRefObj_s00c6_97a0* p = mpRef) {
        mpRef = 0;
        p->Release();
    }
    m34.Shutdown();
    m108.Shutdown();
    BaseTeardown();
}
