// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.

// @ 0x0001002d90
extern char DAT_15b67c0[];

struct LocalSerializer_01002d90 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_01002d90(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_693e10(void* stream);                                        // 0x00693e10
};

struct GO_01002d90 {
    void Serialize_01002d90(void* stream);
};

void GO_01002d90::Serialize_01002d90(void* stream)
{
    LocalSerializer_01002d90 s(this, DAT_15b67c0, 0x1a80d26);
    s.Ser_693e10(stream);
}
