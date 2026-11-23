// Slice s008f2420: same shape as s00614f20's cSmallB::Init (0x006162d0), with the
// vtable pointer at 0x1439a30 instead of 0x13fc508. Spelled exactly like the donor;
// cl 15 compiles the plain thiscall member to the retail ret 8 form.
// Flags: /O2 /MD /Gy /TP

extern void* kVtbl1439a30[];

// @ 0x008f2420
struct cSmallB_008f2420 {
    void** vtbl; int mnRef; int mA; int mB;
    cSmallB_008f2420* Init(int a, int b);
};

cSmallB_008f2420* cSmallB_008f2420::Init(int a, int b)
{
    mnRef = 0;
    vtbl = kVtbl1439a30;
    mA = a;
    mB = b;
    return this;
}
