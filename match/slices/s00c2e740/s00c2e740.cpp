// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.
// Flags: (default)

// @ 0x00c2e740
extern char DAT_01572618[];

struct LocalSerializer_00c2e740 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_00c2e740(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_00695960(void* stream);                                          // 0x00692900
};

struct GO_00c2e740 {
    void Serialize_00c2e740(void* stream);
};

void GO_00c2e740::Serialize_00c2e740(void* stream)
{
    LocalSerializer_00c2e740 s(this, DAT_01572618, 0x1a80d26);
    s.Ser_00695960(stream);
}
