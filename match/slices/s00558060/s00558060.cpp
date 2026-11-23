// Same shape as s00401b80's ResourceKeyAbility::~ResourceKeyAbility (0x00401ed0):
// two stores to [this] (at /Od the redundant first store survives); the vtables here
// are 0x13f4274 then 0x13ec458 (donor: 0x13eb2d8 then 0x13ef094).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE

extern void* kVtbl13f4274[];
extern void* kVtbl13ec458[];

// @ 0x00558060
struct D_00558060 {
    void** vtbl;
    void TakeDown();
};

void D_00558060::TakeDown()
{
    vtbl = kVtbl13f4274;
    vtbl = kVtbl13ec458;
}
