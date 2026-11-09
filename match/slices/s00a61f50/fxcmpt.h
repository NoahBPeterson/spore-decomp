// Slice s00a61f50 -- EAPd reflected "FX component" (kFXCmpt*) class family.
// Range 0x00a61f50..0x00a62ec0.  Un-named SPAudio object living in the
// work/migrate/modmap.json gap between eapdmenu.obj (ends 0x00a61c20) and
// eapdtable.obj (starts 0x00a62410).
//
// Recovered class model (from the code): a reflected object with
//   +0x28 / +0x2c : two interned property-name handles
//   +0x30         : element count
//   +0x34         : element capacity
//   +0x38         : pointer to an array of 0x0c-byte { int32 state; float value; float pad; }
//   +0x3c         : float accumulator
// plus the EAPd reflection entry points every method uses.
#pragma once

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned __int64   uint64;

struct EapdInterned { uint32 name; uint32 id; };

// --------------------------------------------------------------- EAPd runtime
EapdInterned* __cdecl FUN_00a675f0(const char* s, EapdInterned* out);          // 0x00a675f0
void* __cdecl FUN_00a48ea0(uint32 a, uint32 b, void* ctor, uint32 size,
                                uint32 d, uint32 e, uint32 f, uint32 g);     // 0x00a48ea0
bool  __cdecl FUN_00a47f30(void* cls, void* handler);                      // 0x00a47f30
bool  __cdecl FUN_00a47f70(void* cls, void* handler);                     // 0x00a47f70
bool  __cdecl FUN_00a47f10(void* cls, void* handler);                     // 0x00a47f10
bool  __cdecl FUN_00a48a80(void* cls, void* method, uint32 a, uint32 b,
                            uint32 c, uint32 d, uint32 e, uint32 f);         // 0x00a48a80
bool  __cdecl FUN_00a48b30(void* cls, void* method, uint32 a, uint32 b,
                               uint32 c, uint32 d, uint32 e, uint32 f,
                               uint32 g);                                    // 0x00a48b30
bool  __cdecl FUN_00a48a30(void* cls, void* method, uint32 a, uint32 b,
                             uint32 c, uint32 d);                            // 0x00a48a30
void* __cdecl FUN_00a49390(void* cls);                                   // 0x00a49390
void  __cdecl FUN_00a49d30(uint32 a, uint32 b, uint32 c, void* obj);           // 0x00a49d30
void  __cdecl FUN_00a49e40(uint32 a, uint32 b, uint32 c, int n, void* arr); // 0x00a49e40
void  __cdecl FUN_00a49a00(void* obj, void* b, float* v);                  // 0x00a49a00
void  __cdecl FUN_00a487f0(const char* fmt, ...);                                 // 0x00a487f0
void  __cdecl FUN_00a49570(void* it, float v);                                // 0x00a49570
void* __cdecl FUN_00a671f0(uint32 a, uint32 b, uint32 c);                   // 0x00a671f0
void  __cdecl FUN_011e0744(void* dst, const void* src, uint32 n);            // 0x011e0744
float __cdecl FUN_00a68fe0(void* self, float total);
void  __cdecl FUN_00936090(float* dst, float v);                               // 0x00936090
float __cdecl _fabs_(double x);   // CRT fabs helper (0x00927000)
float __cdecl FUN_00a68fe0(double x);                         // 0x00a68fe0

// Global reflection registry slots.
extern uint32 g_fxCmptSeqA_1675838;      // 0x01675838
extern uint32 g_fxCmptMeta_167583c;      // 0x0167583c
extern uint32 g_fxCmptSoundMeta_1675840; // 0x01675840
extern uint32 g_fxCmptMeta2_1675844;     // 0x01675844
extern uint32 g_fxCmptSeqB_1675848;      // 0x01675848
extern uint32 g_fxCmptSeqC_167584c;      // 0x0167584c
extern uint32 g_fxCmptMeta3_1675850;     // 0x01675850
extern uint32 g_fxCmptSeqD_1675854;      // 0x01675854
extern uint32 g_fxCmptSeqE_1675858;      // 0x01675858
extern uint32 g_eapdA_16758ac;           // 0x016758ac
extern uint32 g_eapdB_16758b0;           // 0x016758b0
extern uint32 g_eapdC_16758c4;           // 0x016758c4
extern uint32 g_eapdD_16758c8;           // 0x016758c8
extern uint32 g_eapdE_1675490;           // 0x01675490
extern uint32 g_refDepth_167545c;        // 0x0167545c  (recursion guard, limit 1000)

// Referenced string constants.
extern const char g_fxEmptyStr_13f2ce4[];  // 0x013f2ce4
extern const char g_fxMetaStr_14546a4[];   // 0x014546a4
extern const char g_fxFmt_1432d80[];       // 0x01432d80
extern const char g_fxFmt2_1432d80[];      // 0x01432d80
extern const char g_fxFmt3_1455518[];      // 0x01455518
extern const char g_fxCoreStr_1455520[];   // 0x01455520
extern const char g_fxCoreStr2_1409198[];  // 0x01409198

// Reflection callbacks referenced from the class registration entry points.
void __cdecl FUN_00a61e50(void* ctx, int i, void* elem);   // 0x00a61e50
void __cdecl FUN_00a61ee0(void* ctx, int i, void* elem);      // 0x00a61ee0
void __cdecl FUN_00a61ec0(void* ctx, int i, void* elem);     // 0x00a61ec0
void __cdecl FUN_00a62050(void* ctx, int i, void* elem);      // 0x00a62050
void* __cdecl FUN_00a61c20(void* mem, uint32 which);       // 0x00a61c20

// --------------------------------------------------------------- class layouts
struct FxAccum {                       // wrapper for the 0x00936090 thiscall setter
    void Set(float v);                  // 0x00936090
};

struct FXElem {                         // 0x0c
    int   state;                        // +0x00
    float value;                        // +0x04
    float pad;                          // +0x08
};

struct FXTableBase {                    // reflected component base
    uint8  pad00[0x28];
    uint32 nameA;                       // +0x28
    uint32 nameB;                       // +0x2c
    int    count;                       // +0x30
    int    capacity;                    // +0x34
    FXElem* elems;                      // +0x38
    float  accum;                       // +0x3c
};
