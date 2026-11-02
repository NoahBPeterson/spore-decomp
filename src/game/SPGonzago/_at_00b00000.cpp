// src/game/SPGonzago/_at_00b00000.cpp -- migrated from slice(s) s00b01690 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00b00000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00b01690 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef signed int         i32;
bool  EA_IO_WriteUint32(void* stream, const void* p, int n, int m);      // 0x0093aa70
void* SP_cVarListSerializer_ctor(void* self, const void* p, const void* q, const void* r); // 0x00692f90
bool  SP_cVarListSerializer_Serialize(void* self, void* stream);         // 0x00692900
static inline void** vtbl(const void* p) { return *(void***)p; }
// ---- items of slice s00b01690 end

// @ 0x00b02630
void FUN_00b02630(void* stream, u8* range)
{
    u8* s = (u8*)stream;
    u8* first = *(u8**)range;
    u8* last = *(u8**)(range + 4);
    void* sub = (*(void*(__thiscall**)(u8*))((char*)vtbl(s) + 0x20))(s);
    i32 count = (i32)((u32)(last - first) / 0x19a8);
    int tmp = count;
    void* wr = (*(void*(__thiscall**)(void*))((char*)vtbl(sub) + 0x18))(sub);
    EA_IO_WriteUint32(wr, &tmp, 1, 0);
    u8* f = *(u8**)range;
    u8* l = *(u8**)(range + 4);
    if (f != l) {
        do {
            void* sub2 = (*(void*(__thiscall**)(u8*))((char*)vtbl(s) + 0x20))(s);
            tmp = *(i32*)f;
            void* wr2 = (*(void*(__thiscall**)(void*))((char*)vtbl(sub2) + 0x18))(sub2);
            EA_IO_WriteUint32(wr2, &tmp, 1, 0);
            (*(void(__thiscall**)(u8*))((char*)vtbl(s) + 0x1c))(s);
            u8 ser[0x2c];
            SP_cVarListSerializer_ctor(ser, f + 8, (const void*)0x01567428, (const void*)0x01a80d26);
            SP_cVarListSerializer_Serialize(ser, s);
            (*(void(__thiscall**)(u8*))((char*)vtbl(s) + 0x1c))(s);
            f += 0x19a8;
        } while (f != l);
    }
    (*(void(__thiscall**)(u8*))((char*)vtbl(s) + 0x1c))(s);
}
