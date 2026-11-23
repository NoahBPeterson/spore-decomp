// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.

// @ 0x0001002d50
extern char DAT_15b67c0[];

struct LocalSerializer_01002d50 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_01002d50(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_692900(void* stream);                                        // 0x00692900
};

struct GO_01002d50 {
    void Serialize_01002d50(void* stream);
};

void GO_01002d50::Serialize_01002d50(void* stream)
{
    LocalSerializer_01002d50 s(this, DAT_15b67c0, 0x1a80d26);
    s.Ser_692900(stream);
}
