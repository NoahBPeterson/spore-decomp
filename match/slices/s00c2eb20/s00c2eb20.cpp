// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.

// @ 0x0000c2eb20
extern char DAT_1572a18[];

struct LocalSerializer_00c2eb20 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_00c2eb20(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_695960(void* stream);                                        // 0x00695960
};

struct GO_00c2eb20 {
    void Serialize_00c2eb20(void* stream);
};

void GO_00c2eb20::Serialize_00c2eb20(void* stream)
{
    LocalSerializer_00c2eb20 s(this, DAT_1572a18, 0x1a80d26);
    s.Ser_695960(stream);
}
