// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.

// @ 0x0000bfe290
extern char DAT_1570e20[];

struct LocalSerializer_00bfe290 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_00bfe290(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_692900(void* stream);                                        // 0x00692900
};

struct GO_00bfe290 {
    void Serialize_00bfe290(void* stream);
};

void GO_00bfe290::Serialize_00bfe290(void* stream)
{
    LocalSerializer_00bfe290 s(this, DAT_1570e20, 0x1a80d26);
    s.Ser_692900(stream);
}
