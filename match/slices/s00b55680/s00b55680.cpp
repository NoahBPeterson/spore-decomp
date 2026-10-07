// Slice s00b55680 -- PARTIAL. Function 00b55680 (2436 bytes): cdecl void(Obj* self, Obj* other, u8 flag), plain ret.
// Verified so far: the top-level dispatch on [self+0xa7] / [self+0xa8] bits and the b532b0 query; the
// "bit 4 / flag" byte setup and the 1-arg thiscall vt+0xb8(0x116dd1b). NOT yet written: the
// hashtable-find path (self+0xa7==0), the Havok phantom build (cPlanetModel orientation, hkRotation set,
// hkSimpleShapePhantom ctor, addPhantom/removePhantom, setPosition, activate), and the vt+0x58/+0x5c/+0x58 tail.
// Built /O2 /MD /Gy /EHsc /TP.
typedef unsigned char  u8;
typedef unsigned int   u32;

void __cdecl Partial_00b55680(u8* self, u8* other, u8 flag)
{
    if (self[0xa7] == 0) {
        // TODO(partial): hashtable find (0x167ed58 table) / FUN_00aef6b0 / FUN_00b4dd70 path, then b53940 + b3e620 + b54230 + b54000 tails.
        return;
    }
    u32 a8 = *(u32*)(self + 0xa8);
    if (((a8 >> 1) & 1) == 0)
        return;

    void* piVar8 = *(void**)(self + 0xb0);     // [esi+0xb0]
    u8 b24 = (u8)(((a8 >> 4) & 1) != 0 || flag != 0);
    (void)piVar8; (void)b24; (void)other;
    // TODO(partial): b532b0(self) result; if nonzero: b3e620(self, piVar8, ...), vt+0xb8(0x116dd1b), b537f0(...).
    // TODO(partial): else branch (other==0 -> b53940 ...), b52690 for param[0x2b]==1, b54230/b3e620 calls.
    // TODO(partial): if float [self+0xb4] != 0: rebuild orientation (vt+0x2c, b7f1f0, vt+0x3c, b523e0, b7f190), hkRotation set, etc.
    // TODO(partial): tail: if DAT_01569ab8 != 0 && (self[0x50] & 0x2000) then b54000(self, 0).
}
