// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.

// @ 0x0000cd3ee0
extern char DAT_157f190[];

struct LocalSerializer_00cd3ee0 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_00cd3ee0(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_693e10(void* stream);                                        // 0x00693e10
};

struct GO_00cd3ee0 {
    void Serialize_00cd3ee0(void* stream);
};

void GO_00cd3ee0::Serialize_00cd3ee0(void* stream)
{
    LocalSerializer_00cd3ee0 s(this, DAT_157f190, 0x1a80d26);
    s.Ser_693e10(stream);
}
