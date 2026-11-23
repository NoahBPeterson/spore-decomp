// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.
// Flags: (default)

// @ 0x00ae9260
extern char DAT_01566db0[];

struct LocalSerializer_00ae9260 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_00ae9260(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_00692900(void* stream);                                          // 0x00692900
};

struct GO_00ae9260 {
    void Serialize_00ae9260(void* stream);
};

void GO_00ae9260::Serialize_00ae9260(void* stream)
{
    LocalSerializer_00ae9260 s(this, DAT_01566db0, 0x1a80d26);
    s.Ser_00692900(stream);
}
