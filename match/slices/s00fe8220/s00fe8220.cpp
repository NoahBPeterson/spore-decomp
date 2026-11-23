// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.

// @ 0x0000fe8220
extern char DAT_015b4568[];

struct LocalSerializer_00fe8220 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_00fe8220(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_00692900(void* stream);                                          // 0x0000692900
};

struct GO_00fe8220 {
    void Serialize_00fe8220(void* stream);
};

void GO_00fe8220::Serialize_00fe8220(void* stream)
{
    LocalSerializer_00fe8220 s(this, DAT_015b4568, 0x1a80d26);
    s.Ser_00692900(stream);
}
