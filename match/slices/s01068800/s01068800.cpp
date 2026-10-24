// Decompiled from SporeApp.exe (gold6 batch, worker 33).
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef float          f32;

// ---------------------------------------------------------------------------
// vtable call shapes
// ---------------------------------------------------------------------------
typedef void  (__thiscall* Fn1)(void*, u32);
typedef void  (__thiscall* Fn2)(void*, u32, u32);
typedef void  (__thiscall* FnP)(void*, void*);
typedef void* (__thiscall* FnFind)(void*, u32, u32);

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
extern "C" void  __cdecl op_del_array(void* p);                 // 0x00f47380
extern "C" void  __cdecl SP_SetImageFromKey(void* win, void* key); // 0x00e2f5c0
extern "C" void* __stdcall SP_GetMissionManager(void* obj);     // 0x00feb9f0

// 16-byte eastl string temporary (begin/end/cap, one dword padding).
struct EaString16 {
    u32 mpBegin;   // +0x00
    u32 mpEnd;     // +0x04
    u32 mpCap;     // +0x08
    u32 mPad0C;    // +0x0c
};

struct Obj3 {
    void* FUN_c45ca0(EaString16* out);   // 0x00c45ca0
};

struct MissionMgr {
    u32 FUN_febf80();                    // 0x00febf80
};

// @ 0x01068800
void __stdcall FUN_01068800(void* layout, u32 index, void* obj, u32 unused)
{
    void* w1 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, (index + 0x1c2245) << 4, 1);
    ((Fn2)(*(void***)w1)[0x7c / 4])(w1, 1, 1);

    index <<= 4;
    void* w2 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, index + 0x1c22451, 1);

    EaString16 sEarly;
    EaString16 sLate;
    sLate.mpBegin = 0x1667bac;
    sLate.mpEnd = 0x1667bac;
    FnP fnB8 = (FnP)(*(void***)obj)[0xb8 / 4];
    sLate.mpCap = 0x1667bae;
    fnB8(obj, &sLate);
    ((FnP)(*(void***)w2)[0x80 / 4])(w2, (void*)sLate.mpBegin);

    void* w3 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, index + 0x1c22452, 1);
    if (w3 != 0) {
        sEarly.mpBegin = 0x1667bac;
        sEarly.mpEnd = 0x1667bac;
        FnP fnC8 = (FnP)(*(void***)obj)[0xc8 / 4];
        sEarly.mpCap = 0x1667bae;
        fnC8(obj, &sEarly);
        ((FnP)(*(void***)w3)[0x80 / 4])(w3, (void*)sEarly.mpBegin);
        if ((s32)((sEarly.mpCap - sEarly.mpBegin) & 0xfffffffeu) > 2 && sEarly.mpBegin != 0)
            op_del_array((void*)sEarly.mpBegin);
    }

    void* w4 = ((FnFind)(*(void***)layout)[0xf0 / 4])(layout, index + 0x1c22454, 1);
    if (w4 != 0) {
        void* key = ((Obj3*)obj)->FUN_c45ca0(&sEarly);
        SP_SetImageFromKey(w4, key);
        void* mgr = SP_GetMissionManager(obj);
        u32 v = ((MissionMgr*)mgr)->FUN_febf80();
        ((Fn1)(*(void***)w4)[0x5c / 4])(w4, v);
    }

    if ((s32)((sLate.mpCap - sLate.mpBegin) & 0xfffffffeu) > 2 && sLate.mpBegin != 0)
        op_del_array((void*)sLate.mpBegin);
}

// ---------------------------------------------------------------------------
// 01068f70 -- terraforming numeric properties
// ---------------------------------------------------------------------------
typedef void  (__thiscall* FnV)(void*);
typedef void  (__thiscall* Fn3P)(void*, u32, u32, void**);
typedef char  (__thiscall* FnProp24)(void*, u32, void**);

struct Property {
    u8  mPad00[0x12];   // +0x00
    u16 mn12;           // +0x12
    u32* GetUInt();     // 0x0041ea00
};

struct Space {
    u8  mPad00[0x544];  // +0x000
    u32 mVal544;        // +0x544
    u32 mVal548;        // +0x548
    u32 mVal54C;        // +0x54c
    u32 mVal550;        // +0x550
    u32 mVal554;        // +0x554
    u32 mVal558;        // +0x558
    u32 mVal55C;        // +0x55c
    u32 mVal560;        // +0x560
    u32 mVal564;        // +0x564
    void FUN_01068f70();
};

extern "C" void* __cdecl SP_PropertyManager();   // 0x0067de30

#define TF_LOAD(member, key)                                                   \
    member = 0xffffffffu;                                                      \
    if (prop != 0) {                                                           \
        if (((FnProp24)(*(void***)prop)[0x24 / 4])(prop, (key), &out) &&       \
            ((Property*)out)->mn12 == 10)                                      \
            member = *((Property*)out)->GetUInt();                             \
    }

// @ 0x01068f70
void Space::FUN_01068f70()
{
    void* prop = 0;
    void* out;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        void* old = prop;
        prop = 0;
        ((FnV)(*(void***)old)[4 / 4])(old);
    }
    ((Fn3P)(*(void***)pm)[0x2c / 4])(pm, 0xddb63e53, 0x2ae0c7e, &prop);

    TF_LOAD(mVal544, 0x680fae3);
    TF_LOAD(mVal548, 0x680fae4);
    TF_LOAD(mVal54C, 0x680fae5);
    TF_LOAD(mVal550, 0x680fae6);
    TF_LOAD(mVal554, 0x680fae7);
    TF_LOAD(mVal558, 0x680fb1b);
    TF_LOAD(mVal55C, 0x680fb1c);
    TF_LOAD(mVal560, 0x680fb1d);
    TF_LOAD(mVal564, 0x680fb1e);

    if (prop != 0)
        ((FnV)(*(void***)prop)[4 / 4])(prop);
}

// ---------------------------------------------------------------------------
// 01068d30 -- SetTerraformingSlot
// ---------------------------------------------------------------------------
typedef void* (__thiscall* FnC0)(void*, u32);
typedef void  (__thiscall* FnV1)(void*, u32);
typedef void  (__thiscall* FnV2)(void*, u32, u32);
typedef void  (__thiscall* FnV0)(void*);

struct Vec3 { u32 x, y, z; };

struct TfSlot {
    void* mpObj00;   // +0x00
    u32   mn04;      // +0x04
    u32   mn08;      // +0x08
    u32   mn0C;      // +0x0c
    u8    mPad10[8]; // +0x10
    u32   mn18;      // +0x18
    u8    mb1C;      // +0x1c
};

extern "C" TfSlot* __stdcall FUN_01067ef0(u32 a);                  // 0x01067ef0
extern "C" u8 __cdecl FUN_00807cb0(void* w, void* key, int arg);   // 0x00807cb0

// @ 0x01068d30
void __stdcall FUN_01068d30(volatile u32 a1, Vec3* v, u8 a3, u8 a4, u32 a5, u32 a6)
{
    TfSlot* slot = FUN_01067ef0(a1);
    if (slot == 0) return;
    void* obj = slot->mpObj00;
    if (obj == 0) return;

    void* sub = ((FnC0)(*(void***)obj)[0xc / 4])(obj, 0x8ed27e7a);
    slot->mn04 = v->x;
    slot->mn08 = v->y;
    slot->mn0C = v->z;

    u8 a1flag = (u8)a1;
    if (a4 != 0) {
        if (a1flag == 0) {
            if (slot->mn18 != 2) {
                ((FnV1)(*(void***)sub)[0x1c / 4])(sub, 1);
                FUN_00807cb0(obj, (void*)0x15b936c, 0);
                FUN_00807cb0(obj, (void*)0x15b9378, 2);
                FUN_00807cb0(obj, (void*)0x15b9384, 3);
            }
            slot->mn18 = 2;
            return;
        }
    } else {
        if (a1flag == 0 &&
            (v->x != *(u32*)0x16e224c || v->y != *(u32*)0x16e2250 || v->z != *(u32*)0x16e2254)) {
            if (slot->mn18 != 0 || slot->mb1C != a3) {
                ((FnV1)(*(void***)sub)[0x1c / 4])(sub, 2);
                if (a3 == 0) {
                    FUN_00807cb0(obj, (void*)0x15b9300, 0);
                    FUN_00807cb0(obj, (void*)0x15b930c, 2);
                    FUN_00807cb0(obj, (void*)0x15b9318, 3);
                    FUN_00807cb0(obj, (void*)0x15b9324, 4);
                    FUN_00807cb0(obj, (void*)0x15b9330, 6);
                    FUN_00807cb0(obj, (void*)0x15b933c, 7);
                } else {
                    FUN_00807cb0(obj, (void*)0x15b92b8, 0);
                    FUN_00807cb0(obj, (void*)0x15b92c4, 2);
                    FUN_00807cb0(obj, (void*)0x15b92d0, 3);
                    FUN_00807cb0(obj, (void*)0x15b92dc, 4);
                    FUN_00807cb0(obj, (void*)0x15b92e8, 6);
                    FUN_00807cb0(obj, (void*)0x15b92f4, 7);
                }
            }
            ((FnV2)(*(void***)sub)[0x28 / 4])(sub, 4, a5);
            ((FnV0)(*(void***)obj)[0x90 / 4])(obj);
            slot->mb1C = a3;
            slot->mn18 = 0;
            return;
        }
    }

    if (v->x == *(u32*)0x16e224c && v->y == *(u32*)0x16e2250 && v->z == *(u32*)0x16e2254 && a1flag == 0) {
        if (slot->mn18 != 3) {
            ((FnV1)(*(void***)sub)[0x1c / 4])(sub, 1);
            FUN_00807cb0(obj, (void*)0x15b9348, 0);
            FUN_00807cb0(obj, (void*)0x15b9354, 2);
            FUN_00807cb0(obj, (void*)0x15b9360, 3);
        }
        slot->mn18 = 3;
        slot->mb1C = 0;
    } else {
        slot->mn18 = 1;
        slot->mb1C = 0;
    }
}

// ---------------------------------------------------------------------------
// 01068970 -- DisplayStarPlanet
// ---------------------------------------------------------------------------
typedef void  (__thiscall* FnWin2)(void*, u32, u32);
typedef void  (__thiscall* FnWin1)(void*, u32);

struct Slot {
    u8  mPad00[0x28];   // +0x00
    u32 mn28;           // +0x28
    u8  mPad2C[0x88];   // +0x2c
    f32 mfB4;           // +0xb4
    bool FUN_b8d970();          // 0x00b8d970
    bool FUN_b8dac0();          // 0x00b8dac0
    int  FUN_b8dab0();          // 0x00b8dab0
    u32  FUN_b8e090();          // 0x00b8e090
    void FUN_b8dd60(u32* out);  // 0x00b8dd60
    void* FUN_b8dad0();         // 0x00b8dad0
    void* FUN_ecdba0();         // 0x00ecdba0
};

struct Layout {
    void* FindWindowByID(u32 id, u32 one);   // 0x008105b0
};

struct TfMgr {
    int FUN_bbc670();                        // 0x00bbc670
};

struct SpeciesMgr {
    void* GetProfile();                      // 0x004df550
};

struct AutoRef {
    void* mpObject;                          // +0x00
    void** AsPPVoidParam();                  // 0x00a16f40
};

extern "C" void* __stdcall TerraformingManager(void* slot);   // 0x00b3d430
extern "C" void* __cdecl FUN_01021370();                      // 0x01021370
extern "C" void* __cdecl FUN_01021300(u32 a);                // 0x01021300
extern "C" u8    __cdecl FUN_00c70150(void* a, void* b);     // 0x00c70150
extern "C" void* __cdecl FUN_00e2eba0(void* a);              // 0x00e2eba0
extern "C" void* __stdcall GetSetting9(u32 id);               // 0x00401090
extern "C" void* __cdecl GetDominantSpeciesThumbnailKey(u32* out, u32 planet); // 0x01065f00
extern "C" void* __cdecl SP_PropertyManager2();               // 0x0067de30
extern "C" u8    __cdecl SP_GetPropertyAsUint32(void* prop, u32 id, u32* out); // 0x004af210

// @ 0x01068970
bool __stdcall FUN_01068970(void* layoutRaw, u32 index, void* slotRaw)
{
    Layout* layout = (Layout*)layoutRaw;
    Slot* slot = (Slot*)slotRaw;
    if (index >= 5) return false;
    if (slot->FUN_b8d970()) return false;
    switch (slot->mn28) {
    case 2: case 3: case 4: case 5:
        break;
    default:
        return false;
    }

    u32 color;
    u32 flag18 = 1;
    void* tf = TerraformingManager(slot);
    if (((TfMgr*)tf)->FUN_bbc670() > 0) {
        color = 0xff7dd244;
    } else {
        f32 v = slot->mfB4;
        if (v > *(f32*)0x1485544)
            color = 0xffd42727;
        else if (*(f32*)0x13eb8a0 > v)
            color = 0xff21a5e7;
        else
            color = 0xffffffff;
    }
    if (slot->FUN_b8dac0())
        flag18 = 2;

    void* w1 = layout->FindWindowByID((index + 0x684bc0) << 4, 1);
    if (w1 == 0) return false;
    ((FnWin2)(*(void***)w1)[0x7c / 4])(w1, 1, 1);

    index <<= 4;
    void* w2 = layout->FindWindowByID(index + 0x684bc01, 1);
    void* w3 = layout->FindWindowByID(index + 0x684bc02, 1);
    void* w4 = layout->FindWindowByID(index + 0x684bc03, 1);
    void* w5 = layout->FindWindowByID(index + 0x684bc07, 1);

    ((FnWin2)(*(void***)w2)[0x7c / 4])(w2, 1, 0);
    ((FnWin2)(*(void***)w3)[0x7c / 4])(w3, 1, 0);
    ((FnWin2)(*(void***)w4)[0x7c / 4])(w4, 1, 0);
    ((FnWin2)(*(void***)w5)[0x7c / 4])(w5, 1, 0);

    void* wsel;
    switch (flag18) {
    case 0: wsel = w4; break;
    case 1: wsel = w3; break;
    case 2: wsel = w5; break;
    default: wsel = 0; break;
    }
    ((FnWin2)(*(void***)wsel)[0x7c / 4])(wsel, 1, 1);
    ((FnWin1)(*(void***)wsel)[0x5c / 4])(wsel, color);

    void* w6 = layout->FindWindowByID(index + 0x684bc05, 1);
    u32 countPos = (slot->FUN_b8dab0() > 0);
    ((FnWin2)(*(void***)w6)[0x7c / 4])(w6, 1, countPos);

    if (FUN_01021370() == slot) {
        SP_SetImageFromKey(w6, (void*)0x15b9124);
    } else {
        void* empire = FUN_01021300(0);
        if (FUN_00c70150(slot, empire)) {
            SP_SetImageFromKey(w6, (void*)0x15b9118);
        } else if (countPos != 0) {
            SP_SetImageFromKey(w6, FUN_00e2eba0(slot));
        }
    }

    void* profile;
    if (slot->FUN_b8dab0() < 2) {
        profile = 0;
    } else {
        void* mgr = GetSetting9(slot->FUN_b8e090());
        profile = ((SpeciesMgr*)mgr)->GetProfile();
    }

    void* w7 = layout->FindWindowByID(index + 0x684bc04, 1);
    void* w8 = layout->FindWindowByID(index + 0x684bc06, 1);
    u32 keyBuf[3];
    if (profile != 0) {
        void* key = GetDominantSpeciesThumbnailKey(keyBuf, (u32)slot);
        SP_SetImageFromKey(w7, key);
    }
    ((FnWin2)(*(void***)w7)[0x7c / 4])(w7, 1, (u32)(profile != 0));

    void* effect = slot->FUN_ecdba0();
    ((FnWin1)(*(void***)w8)[0x80 / 4])(w8, *(u32*)effect);
    ((FnWin2)(*(void***)w8)[0x7c / 4])(w8, 1, 1);

    if (slot->FUN_b8dab0() > 0) {
        u32 k;
        slot->FUN_b8dd60(&k);
        if (k != 0x6334d0ad && k != 0x4f3d572f) {
            AutoRef prop;
            prop.mpObject = 0;
            u32 out = 0;
            void* pm = SP_PropertyManager2();
            void* keyObj = slot->FUN_b8dad0();
            void** pp = prop.AsPPVoidParam();
            ((Fn3P)(*(void***)pm)[0x2c / 4])(pm, *(u32*)keyObj, 0x34d97fa, pp);
            if (SP_GetPropertyAsUint32(prop.mpObject, 0x58cbb75, &out)) {
                ((FnWin1)(*(void***)w5)[0x5c / 4])(w5, out | 0xff000000);
                ((FnWin2)(*(void***)w5)[0x7c / 4])(w5, 1, 1);
            }
            if (prop.mpObject != 0)
                ((FnV0)(*(void***)prop.mpObject)[4 / 4])(prop.mpObject);
        }
    }
    return true;
}
