// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.

// @ 0x0000ba1d40
extern char DAT_156c0b8[];

struct LocalSerializer_00ba1d40 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_00ba1d40(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_692900(void* stream);                                        // 0x00692900
};

struct GO_00ba1d40 {
    void Serialize_00ba1d40(void* stream);
};

void GO_00ba1d40::Serialize_00ba1d40(void* stream)
{
    LocalSerializer_00ba1d40 s(this, DAT_156c0b8, 0x1a80d26);
    s.Ser_692900(stream);
}
