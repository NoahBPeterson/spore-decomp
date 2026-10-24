// s010175b0 -- SP::cSPSpacePlanetCameraController helpers / unnamed functions
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;
typedef float f32;
typedef double f64;

#define VT(p) (*(void***)(p))

struct cSPVector3 {
    union { f32 x; u32 ux; };
    union { f32 y; u32 uy; };
    union { f32 z; u32 uz; };
};

struct TableEntry { f32 key; f32 value; };
struct Table { TableEntry* begin; TableEntry* end; };

extern f32 g16dd3d0;
extern f32 g16dd3b4;
extern f32 g16dd360;
extern f32 g16dd35c;
extern f32 g16dd368;
extern f32 g16dd364;
extern f32 g16dd374;
extern f32 g16dd384;
extern f32 g16dd394;
extern f32 g16dd398;
extern f32 g16dd39c;
extern f32 g16dd3a0;
extern f32 g16dd3a4;
extern f32 g16dd3a8;
extern f32 g16dd3e8;
extern f32 g16dd3ec;
extern f32 g16dd3f8;
extern f32 g16dd414;
extern f32 g16dd418;
extern f32 g16dd434;
extern u8  g16dd3fc;
extern u8  g16dd441;
extern u32 g16dd444;
extern u32 g16dd448;
extern u32 g16dd44c;
extern u32 g16dda78;
extern f32 g16dda74;
extern f32 g16dda70;
extern Table g16dda14;
extern Table g16dda28;
extern f32 g15b6d88;
extern f32 g15b6d8c;
extern f32 g145cfe8;
extern f32 g1471064;
extern f32 g1485720;
extern f32 g13eb95c;
extern u32 g15b6ddc;
extern u32 g15b6de0;
extern u32 g15b6de4;

class COps {
public:
    bool FUN_00c8b800();
    f32 FUN_00b7e4d0();
    f32 FUN_00a0ab60();
    f32 FUN_00c37120();
    void FUN_00b815a0(void* out, void* dir);
    void* FUN_00a1ad60();
    u32 FUN_01021080();
    bool FUN_01044920();
};
#define MOPS(p) ((COps*)(p))

extern void* __cdecl FUN_01021230();
extern void* __cdecl FUN_00ffbe50();
extern void* __cdecl FUN_00b3d350();
extern void* __cdecl FUN_00c37360();
extern void* __cdecl FUN_00b3d380();
extern void* __cdecl FUN_00b3d470();
extern void* __cdecl FUN_0067ddd0();
extern void __cdecl FUN_00f47380(void* p);
extern void __cdecl FUN_00571db0(void* h, u32 a, u32 b, u32 c, u32 d);
extern f32 __cdecl FUN_010433e0(void* a, u32 b, f32 c, u32 d);
extern f32 __cdecl FUN_01043310(void* a, u32 b, f32 c, u32 d);
extern "C" f32 __cdecl sqrtf(f32 x);

struct cGameTimeManager {
    u8 pad00[0x48];
    u8 m48;                          // +0x48
};

class cPlayerInventory {
public:
    u8 pad00[0x34];
    void* m34;                       // +0x34  embedded object (vtable first)
    u8 pad38[0x74c - 0x38];
    u8 m74C;                         // +0x74c
    u8 pad74D[0x750 - 0x74D];
    f32 m750[3];                     // +0x750
};

class cSPSpacePlanetCameraController {
public:
    u8 pad00[0x14];
    void* mPathSource;               // +0x14
    u8 pad18[0x60 - 0x18];
    f32 m60;                         // +0x60
    u8 pad64[0x68 - 0x64];
    union { f32 f; u8 b; } m68;      // +0x68
    f32 kPlanetFarZoomHeight;        // +0x6c
    f32 m70;                         // +0x70
    f32 m74;                         // +0x74  planet radius
    f32 m78;                         // +0x78
    f32 m7C;                         // +0x7c
    f32 m80;                         // +0x80
    f32 m84;                         // +0x84
    u8 pad88[0x8c - 0x88];
    f32 m8C;                         // +0x8c
    f32 m90;                         // +0x90
    u32 m94;                         // +0x94
    u32 m98;                         // +0x98
    u32 m9C;                         // +0x9c
    u32 mA0;                         // +0xa0
    u32 mA4;                         // +0xa4
    u32 mA8;                         // +0xa8
    f32 mAC;                         // +0xac
    f32 mB0;                         // +0xb0
    u32 mB4;                         // +0xb4
    u32 mB8;                         // +0xb8
    u32 mBC;                         // +0xbc
    u32 mC0;                         // +0xc0
    u32 mC4;                         // +0xc4
    u32 mC8;                         // +0xc8
    u8 padCC[0xd0 - 0xcc];
    f32 mD0;                         // +0xd0
    u32 mD4;                         // +0xd4
    u32 mD8;                         // +0xd8
    u32 mDC;                         // +0xdc
    u32 mE0;                         // +0xe0
    u32 mE4;                         // +0xe4
    u32 mE8;                         // +0xe8
    f32 mEC;                         // +0xec
    f32 mF0;                         // +0xf0
    f32 mF4;                         // +0xf4
    u8 padF8[0x138 - 0xf8];
    u32 m138;                        // +0x138
    u8 m13C;                         // +0x13c
    u8 m13D;                         // +0x13d
    u8 m13E;                         // +0x13e
    u8 m13F;                         // +0x13f
    u8 m140;                         // +0x140
    u8 pad141[0x144 - 0x141];
    u32 m144;                        // +0x144
    u32 m148;                        // +0x148
    u32 m14C;                        // +0x14c
    u8 pad150[0x15c - 0x150];
    u32 m15C;                        // +0x15c
    u32 m160;                        // +0x160
    u32 m164;                        // +0x164
    u8 pad168[0x194 - 0x168];
    u8 m194;                         // +0x194
    u8 pad195[0x198 - 0x195];
    u32 m198;                        // +0x198
    u8 pad19C[0x228 - 0x1A0];

    f32 FUN_01017790(bool a, bool b);
    void FUN_01017910();
    void* FUN_01017b70();
    f32 FUN_01017bb0();
    f32 FUN_01017d30();
    f32 FUN_01017e80();
    bool FUN_01017f20();
};

class cEditorTraceObject {
public:
    u32 mVtbl0;                      // +0x00
    u32 mVtbl4;                      // +0x04
    u32 mVtbl8;                      // +0x08
    u8 pad0C[0x10 - 0x0c];
    void* m10;                       // +0x10
    void* m14;                       // +0x14
    u32 m18;                         // +0x18
    u32 m1C;                         // +0x1c
    u32 m20;                         // +0x20
    u32 m24;                         // +0x24
    u32 m28;                         // +0x28
    u8 pad2C[0x48 - 0x2c];
    void* m48;                       // +0x48

    void FUN_01018060();
};

struct ArrayHeader { u32 count; };

// @ 0x010175b0
f32 __stdcall FUN_010175b0(int mode, f32 value)
{
    f32 lo = g16dd3d0;
    f32 hi = g16dd3b4;
    Table* table;
    if (mode == 1) {
        if (!MOPS(FUN_01021230())->FUN_00c8b800()) {
            f32 t = (value - lo) / (hi - lo);
            if (t < 0.0f)
                t = 0.0f;
            if (t > 1.0f)
                t = 1.0f;
            if ((g16dda78 & 1) == 0) {
                g16dda78 = g16dda78 | 1;
                g16dda74 = 0.08726646f;
            }
            if ((g16dda78 & 2) == 0) {
                g16dda78 = g16dda78 | 2;
                g16dda70 = 0.87266463f;
            }
            return (g16dda70 - g16dda74) * t + g16dda74;
        }
        table = &g16dda14;
    } else {
        table = &g16dda28;
    }

    TableEntry* b = table->begin;
    int n = (int)(table->end - b);
    if (n <= 0)
        return 0.0f;

    f32 v = value;
    if (v < b[0].key)
        v = b[0].key;
    if (v > b[n - 1].key)
        v = b[n - 1].key;

    TableEntry* lower = 0;
    TableEntry* upper = 0;
    for (int i = 0; i < n; i++) {
        TableEntry* e = &b[i];
        if (v <= e->key) {
            if (e->key <= v)
                return e->value;
            if (upper == 0 || e->key < upper->key)
                upper = e;
        } else {
            if (lower == 0 || e->key > lower->key)
                lower = e;
        }
    }
    if (lower != 0 && upper != 0)
        return lower->value + (upper->value - lower->value) *
               ((v - lower->key) / (upper->key - lower->key));
    return 0.0f;
}

// @ 0x01017790
f32 cSPSpacePlanetCameraController::FUN_01017790(bool a, bool b)
{
    u32 ctx = MOPS(this)->FUN_01021080();
    f32 high;
    f32 low;
    if (ctx == 1) {
        if (!a) {
            high = g16dd3a8;
            low = g16dd3a4;
        } else if (!b) {
            high = g16dd398;
            low = g16dd394;
        } else {
            high = g16dd3a0;
            low = g16dd39c;
        }
    } else {
        if (!a) {
            high = g16dd368;
            low = g16dd364;
        } else {
            high = g16dd360;
            low = g16dd35c;
        }
    }

    f32 lo = 0.0f;
    if (ctx == 1)
        lo = g16dd3d0;
    else if (ctx == 2)
        lo = g16dd384;
    f32 hi = 0.0f;
    if (ctx == 1)
        hi = g16dd3b4;
    else if (ctx == 2)
        hi = g16dd374;

    f32 t = (this->m68.f - lo) / (hi - lo);
    t = t < lo ? lo : t;
    t = t > hi ? hi : t;
    return high + (low - high) * t;
}

// @ 0x010178e0
cSPVector3* __stdcall FUN_010178e0(cSPVector3* out)
{
    cPlayerInventory* inv = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();
    cSPVector3* pos = (cSPVector3*)((f32* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);
    out->x = pos->x;
    out->y = pos->y;
    out->z = pos->z;
    return out;
}

// @ 0x01017910
void cSPSpacePlanetCameraController::FUN_01017910()
{
    this->mD4 = 0;
    this->mD8 = 0;
    this->mE0 = 0;
    this->mDC = 0;
    this->mE4 = 0;
    this->mF0 = 1.0f;
    this->mF4 = 1.0f;
    this->mE8 = 0;
    this->mEC = 1.0f;

    this->m68.b = 1;
    this->kPlanetFarZoomHeight = 50.0f;
    this->m70 = g16dd434;
    this->m74 = MOPS(FUN_00b3d350())->FUN_00b7e4d0();
    this->m7C = 0.2617994f;
    this->m78 = 0.0f;
    this->m90 = 0.0f;
    this->m94 = g15b6ddc;
    this->m98 = g15b6de0;
    this->m9C = g15b6de4;
    this->mA0 = g16dd444;
    this->mA4 = g16dd448;
    this->mA8 = g16dd44c;
    this->mAC = 0.0f;
    this->mB0 = 0.0f;
    this->m198 = 0;
    this->m138 = 0;
    this->mB4 = g16dd444;
    this->mB8 = g16dd448;
    this->mBC = g16dd44c;
    this->mC0 = g16dd444;
    this->mC4 = g16dd448;
    this->mC8 = g16dd44c;
    this->mD0 = 0.0f;
    this->m13F = 1;
    this->m140 = 0;
    this->m144 = g16dd444;
    this->m148 = g16dd448;
    this->m14C = g16dd44c;
    this->m15C = g16dd444;
    this->m160 = g16dd448;
    this->m164 = g16dd44c;
    this->m13C = 1;
    this->m8C = 0.0f;
    this->m80 = 0.0f;
    this->m84 = 0.2617994f;
    this->m13E = 0;

    void** slot = (void**)((u8*)FUN_00b3d470() + 0xc4);
    if (*slot != 0) {
        void* obj = *(void**)((u8*)FUN_00b3d470() + 0xc4);
        ((void (__thiscall*)(void*, u32))VT(obj)[0xc / 4])(obj, 1);

        void** slot2 = (void**)((u8*)FUN_00b3d470() + 0xc4);
        void* q = *slot2;
        if (q != 0) {
            *slot2 = 0;
            ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
            return;
        }
    }
}

// @ 0x01017b70
void* cSPSpacePlanetCameraController::FUN_01017b70()
{
    cPlayerInventory* inv = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();
    if (inv->m74C != 0) {
        cGameTimeManager* tm = (cGameTimeManager*)FUN_00b3d380();
        if ((tm->m48 & 1) == 0)
            return inv->m750;
    }
    return ((void* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);
}

// @ 0x01017bb0
f32 cSPSpacePlanetCameraController::FUN_01017bb0()
{
    f32 l18 = MOPS(FUN_00c37360())->FUN_00a0ab60();
    f32 l1c = this->m74;

    cPlayerInventory* invA = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();
    cPlayerInventory* invB = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();

    f32* pos;
    if (invB->m74C != 0 && (((cGameTimeManager*)FUN_00b3d380())->m48 & 1) == 0)
        pos = invB->m750;
    else
        pos = (f32*)((f32* (__thiscall*)(void*))VT(&invB->m34)[0x2c / 4])(&invB->m34);

    f32 dist = sqrtf(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]) - l1c;
    f32 gap = MOPS(invA)->FUN_00c37120() - l1c;

    f32* minPtr = &gap;
    if (dist <= gap)
        minPtr = &dist;
    f32* maxPtr = &gap;
    if (gap <= dist)
        maxPtr = &dist;

    f32 base = g15b6d88 * l18;
    f32 v = *minPtr;
    if (v < base)
        v = base;
    if (v > l18)
        v = l18;
    f32 t = (v - base) / (l18 - base);
    return (*maxPtr - dist) * (((2.7f - (t + t)) * t) * t) + dist;
}

// @ 0x01017ce0
void __stdcall FUN_01017ce0(u32 unused, cSPVector3* out)
{
    cPlayerInventory* inv = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();
    cSPVector3* pos;
    if (inv->m74C != 0 && (((cGameTimeManager*)FUN_00b3d380())->m48 & 1) == 0)
        pos = (cSPVector3*)inv->m750;
    else
        pos = (cSPVector3*)((f32* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);

    out->ux = pos->ux;
    out->uy = pos->uy;
    out->uz = pos->uz;
}

// @ 0x01017d30
f32 cSPSpacePlanetCameraController::FUN_01017d30()
{
    f32 res = this->m60;
    if (this->m140 != 0 && g16dd3fc == 0) {
        f32 a = MOPS(FUN_00b3d350())->FUN_00b7e4d0() + g16dd3e8;
        f32 b = MOPS(FUN_00c37360())->FUN_00a0ab60();
        f32 c = MOPS(FUN_00b3d350())->FUN_00b7e4d0();
        f32 d = (a - (c + b)) / (((g16dd414 + g16dd418) * 0.5f) * g16dd3f8);
        if (this->m194 != 0)
            d = -d;
        res = d;
    }
    return res;
}

// @ 0x01017dd0
cSPVector3* __stdcall FUN_01017dd0(cSPVector3* out)
{
    void* planet = FUN_00b3d350();
    cPlayerInventory* inv = (cPlayerInventory*)MOPS(FUN_00ffbe50())->FUN_00a1ad60();

    if (planet != 0) {
        cSPVector3* pos;
        if (inv->m74C != 0 && (((cGameTimeManager*)FUN_00b3d380())->m48 & 1) == 0)
            pos = (cSPVector3*)inv->m750;
        else
            pos = (cSPVector3*)((f32* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);
        MOPS(planet)->FUN_00b815a0(out, pos);
        return out;
    }

    cSPVector3* pos;
    if (inv->m74C != 0 && (((cGameTimeManager*)FUN_00b3d380())->m48 & 1) == 0)
        pos = (cSPVector3*)inv->m750;
    else
        pos = (cSPVector3*)((f32* (__thiscall*)(void*))VT(&inv->m34)[0x2c / 4])(&inv->m34);
    out->x = pos->x;
    out->y = pos->y;
    out->z = pos->z;
    return out;
}

// @ 0x01017e80
f32 cSPSpacePlanetCameraController::FUN_01017e80()
{
    bool flag = MOPS(this)->FUN_01044920();
    f32 a = MOPS(FUN_00b3d350())->FUN_00b7e4d0();
    f32 c = g16dd3ec + a;
    f32 b = a + g16dd3e8;
    if (flag) {
        if (this->m13D != 0)
            return b + 1.0f;
        if (this->m13E != 0) {
            if (this->FUN_01017d30() < 0.0f)
                return b;
        }
    }
    return c;
}

// @ 0x01017f20
bool cSPSpacePlanetCameraController::FUN_01017f20()
{
    if (g16dd441 != 0)
        return true;

    if (this->m13D != 0) {
        f32 h = MOPS(FUN_00b3d350())->FUN_00b7e4d0() + g16dd3e8;
        f32 v = ((f32 (__thiscall*)(void*))VT(this)[0x60 / 4])(this);
        if (h > v)
            return false;
    }

    f32 ref = this->FUN_01017bb0();
    u32 arg;
    switch (this->m138) {
    case 3:
        arg = 0x6046db4;
        break;
    case 4:
        arg = 0x6046db5;
        break;
    default:
        arg = 0x195a060;
        break;
    }

    f32 v1 = FUN_010433e0(this->mPathSource, arg, ref, 0);
    void* src = this->mPathSource;
    f32 v2 = FUN_01043310(src, arg, v1, 1);
    return v2 - this->kPlanetFarZoomHeight < g15b6d8c;
}

// @ 0x01017fe0
void __cdecl FUN_01017fe0()
{
    void** slot = (void**)((u8*)FUN_00b3d470() + 0xc4);
    if (*slot == 0) {
        void* effects = FUN_0067ddd0();
        void** slot2 = (void**)((u8*)FUN_00b3d470() + 0xc4);
        void* old = *slot2;
        if (old != 0) {
            *slot2 = 0;
            ((void (__thiscall*)(void*))VT(old)[4 / 4])(old);
        }
        ((void (__thiscall*)(void*, u32, u32, void**))VT(effects)[0x2c / 4])(effects, 0x44059911, 0, slot2);
    }

    void** slot3 = (void**)((u8*)FUN_00b3d470() + 0xc4);
    if (*slot3 != 0) {
        void** slot4 = (void**)((u8*)FUN_00b3d470() + 0xc4);
        void* obj = *slot4;
        ((void (__thiscall*)(void*, u32))VT(obj)[8 / 4])(obj, 0);
    }
}

// @ 0x01018060
void cEditorTraceObject::FUN_01018060()
{
    void* arr = this->m48;
    if (arr != 0) {
        ArrayHeader* hdr = ((ArrayHeader*)arr) - 1;
        if (hdr->count != 0)
            FUN_00f47380(arr);
    }

    u32 h = this->m18;
    if (h != 0) {
        this->m18 = 0;
        FUN_00571db0((void*)h, this->m1C, this->m20, this->m24, this->m28);
    }

    void* p14 = this->m14;
    if (p14 != 0)
        ((void (__thiscall*)(void*))VT(p14)[4 / 4])(p14);
    void* p10 = this->m10;
    if (p10 != 0)
        ((void (__thiscall*)(void*))VT(p10)[4 / 4])(p10);

    this->mVtbl8 = 0x13ec458;
    this->mVtbl4 = 0x13eb394;
    this->mVtbl0 = 0x13eb938;
}
