// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.

// @ 0x0000c56220
extern char DAT_15761d0[];

struct LocalSerializer_00c56220 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_00c56220(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_693e10(void* stream);                                        // 0x00693e10
};

struct GO_00c56220 {
    void Serialize_00c56220(void* stream);
};

void GO_00c56220::Serialize_00c56220(void* stream)
{
    LocalSerializer_00c56220 s(this, DAT_15761d0, 0x1a80d26);
    s.Ser_693e10(stream);
}
