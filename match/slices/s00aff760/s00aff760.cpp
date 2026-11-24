// Same shape as s00c44a20's GameObj::Serialize_c44b40 (0x00c44b40): a 0xa14-byte
// LocalSerializer on the stack, constructed with (this, name table, 0x1a80d26), then
// one serializer call. Name table and serializer call re-pointed.

// @ 0x0000aff760
extern char DAT_1567a80[];

struct LocalSerializer_00aff760 {
    unsigned buf[0xa14 / 4];
    LocalSerializer_00aff760(void* owner, const void* table, unsigned id);   // 0x00692f90
    void Ser_695960(void* stream);                                        // 0x00695960
};

struct GO_00aff760 {
    void Serialize_00aff760(void* stream);
};

void GO_00aff760::Serialize_00aff760(void* stream)
{
    LocalSerializer_00aff760 s(this, DAT_1567a80, 0x1a80d26);
    s.Ser_695960(stream);
}
