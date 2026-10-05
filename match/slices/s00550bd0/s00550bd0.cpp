// Slice s00550bd0: Pollinator::cAssetMetadata field setters / tag-list helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

// ---- externals -------------------------------------------------------------
void  FUN_00423820(void* self, const void* a, const void* b);   // WStr construct
void  FUN_004237d0(void* self);                                 // WStr dtor
void  FUN_0047d390(void* self, const void* a, const void* b);   // char string range ctor
void  FUN_00554170();
void  FUN_005541e0();
void  FUN_006b8f40(void* v);
int*  FUN_00607a60();                                           // AuthManager
int   FUN_0067cb30();                                           // returns something
void  FUN_00553cc0(void* v);                                    // vector<string> clear/push
void  FUN_00554b60(void* a, void* b);
void  FUN_004769b0(void* a, void* b);
void  FUN_00554760(void* a, void* b);
void  FUN_00554020(void* a, void* b);
void  operator_delete(void* p);
void  EA_DateTime_Set(int);
void  WStr_Assign(void* self, const void* a, const void* b);
char  GetParentServerID(int a, void* b, void* c);
char  AddPollinatorDebugInfo(int a, void* b, void* c);

extern char DAT_013f027c[];
extern char DAT_013f3da0[];
extern char DAT_013ec468[];

// ---- stub string -----------------------------------------------------------
struct WStr {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    int       mAlloc;
    void Append(const void* a, const void* b);   // 0x429580
};
void WStr_Format(void* out, const void* fmt, int arg);   // 0x41e050 cdecl

// ---- cAssetMetadata --------------------------------------------------------
struct Meta {
    char pad[0x400];
    char FUN_00550b60(int key);
    char FUN_00550bd0(uint16_t* str);
    void FUN_00550cf0(WStr* out);
    char FUN_00550da0(int* param_2, int* param_3, int* param_4);
    char FUN_00551240(int* param_2, uint16_t* param_3, uint16_t* param_4, int param_5,
                      int* param_6, char param_7);
    char SetMetadata(uint32_t* param_2, int param_3, int param_4, int param_5, void* param_6,
                     uint16_t* param_7, void* param_8, uint16_t* param_9, uint16_t* param_10,
                     uint16_t* param_11, int param_12, void* param_13, char param_14);
    void FUN_005519d0(uint16_t* a, uint16_t* b, int c);
    void FUN_00551af0(int a, int b);
};

// @ 0x00550bd0
char Meta::FUN_00550bd0(uint16_t* param_1)
{
    uint16_t* local_10 = param_1;
    uint16_t* local_6c = param_1;
    short sVar1;
    do { sVar1 = *local_6c; local_6c++; } while (sVar1 != 0);
    uint16_t* local_c = param_1 + (((int)local_6c - (int)(param_1 + 1)) >> 1);
    uint16_t* local_8 = 0;
    do {
        uint16_t* local_28;
        for (local_28 = local_10; local_28 != local_c && *local_28 != 0x2c; local_28++) { }
        local_8 = local_28;
        if (local_28 != local_10) {
            int local_20 = 0, local_1c = 0, local_18 = 0;
            FUN_00423820(&local_20, local_10, local_28);
            FUN_00554170();
            FUN_005541e0();
            FUN_006b8f40(&local_20);
            if (local_20 != local_1c) {
                FUN_00553cc0(&local_20);
            }
            FUN_004237d0(&local_20);
        }
        local_10 = local_8 + 1;
    } while (local_8 != local_c && local_10 != local_c);
    return 1;
}

// @ 0x00550cf0
void Meta::FUN_00550cf0(WStr* out)
{
    char* s = (char*)this;
    char* pe = *(char**)(s + 0xb0);
    bool first = true;
    for (char* p = *(char**)(s + 0xac); p != pe; p += 0x10) {
        if (!first) {
            uint16_t* sep = (uint16_t*)DAT_013f027c;
            uint16_t* q = sep;
            while (*q != 0) q++;
            out->Append(sep, sep + (((int)q - (int)sep) >> 1));
        }
        out->Append(*(void**)p, *(void**)(p + 4));
        first = false;
    }
}

// @ 0x00550da0
char Meta::FUN_00550da0(int* param_2, int* param_3, int* param_4)
{
    char* s = (char*)this;
    char result = 0;
    if (param_3 != 0) {
        int local_50 = param_3[0];
        if (FUN_00550b60(local_50) != 0) {
            *(int*)(s + 0x20) = param_2[0];
            *(int*)(s + 0x24) = param_2[1];
            *(int*)(s + 0x28) = param_2[2];
            *(int*)(s + 0x2c) = 0;
            *(int*)(s + 0x30) = 0;
            *(int*)(s + 0x34) = 0;
            *(int*)(s + 0x38) = param_3[0xe];
            *(int*)(s + 0x3c) = param_3[0xf];
            *(int*)(s + 0x40) = param_3[0x16];
            *(int*)(s + 0x44) = param_3[0x17];
            *(int*)(s + 8) = param_2[0];
            *(int*)(s + 0xc) = 0x30bdee3;
            *(int*)(s + 0x10) = param_2[2];
            *(int*)(s + 0x48) = param_3[10];
            *(int*)(s + 0x4c) = param_3[0xb];
            int64_t dt = 0;
            EA_DateTime_Set(1);
            *(int*)(s + 0x50) = (int)dt;
            *(int*)(s + 0x54) = (int)(dt >> 32);
            int local_54 = param_3[0x29];
            WStr* dst = (WStr*)(s + 0x58);
            char* src = (char*)(local_54 + 8);
            if (src != (char*)dst) {
                WStr_Assign(dst, *(void**)(local_54 + 8), *(void**)(local_54 + 0xc));
            }
            int local_60 = param_3[0x29];
            *(int*)(s + 0x68) = *(int*)(local_60 + 0x18);
            *(int*)(s + 0x6c) = *(int*)(local_60 + 0x1c);
            int* am = (int*)FUN_00607a60();
            int64_t u = ((int64_t(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
            *(char*)(s + 0x74) = (*(int*)(s + 0x68) == (int)u && *(int*)(s + 0x6c) == (int)(u >> 32));
            *(int*)(s + 0x70) = 0xffffffff;
            if (param_3 + 6 != (int*)(s + 0x78)) {
                WStr_Assign((WStr*)(s + 0x78), (void*)param_3[6], (void*)param_3[7]);
            }
            if (param_3 + 0x34 != (int*)(s + 0x88)) {
                WStr_Assign((WStr*)(s + 0x88), (void*)param_3[0x34], (void*)param_3[0x35]);
            }
            if (*param_4 != param_4[1]) {
                FUN_00553cc0(param_4);
            }
            if (*(char*)(param_3 + 0x44) != 0) {
                int local_48[3] = {0, 0, 0};
                char* e = (char*)"tag:spore.com,2006:AssembledContent";
                char* q = e;
                while (*q != 0) q++;
                FUN_0047d390(local_48, e, q);
                FUN_00553cc0(local_48);
                if (1 < local_48[2] - local_48[0] && local_48[0] != 0) {
                    operator_delete((void*)local_48[0]);
                }
            }
            FUN_00554b60(*(void**)(s + 0xac), *(void**)(s + 0xb0));
            int local_2c = param_3[0x39];
            for (int it = param_3[0x38]; it != local_2c; it += 0x10) {
                /* push_back string at it (PARTIAL shape) */
                FUN_00553cc0((void*)it);
            }
            FUN_004769b0(*(void**)(s + 0xc0), *(void**)(s + 0xc4));
            int local_a4 = param_3[0x3f];
            int local_cc = param_3[0x3e];
            for (; local_cc != local_a4; local_cc += 4) {
                char local_b0[8];
                FUN_00554020(local_b0, (void*)local_cc);
            }
            result = 1;
        }
    }
    return result;
}

// @ 0x00551240
char Meta::FUN_00551240(int* param_2, uint16_t* param_3, uint16_t* param_4, int param_5,
                        int* param_6, char param_7)
{
    char* s = (char*)this;
    *(int*)(s + 0x20) = param_2[0];
    *(int*)(s + 0x24) = param_2[1];
    *(int*)(s + 0x28) = param_2[2];
    *(int*)(s + 8) = param_2[0];
    *(int*)(s + 0xc) = 0x30bdee3;
    *(int*)(s + 0x10) = param_2[2];
    EA_DateTime_Set(1);
    *(int*)(s + 0x48) = 0;
    *(int*)(s + 0x4c) = 0;
    *(int*)(s + 0x50) = *(int*)(s + 0x48);
    *(int*)(s + 0x54) = *(int*)(s + 0x4c);
    int* am = (int*)FUN_00607a60();
    int* p = (int*)((int(__thiscall*)(void*))((*(void***)am)[0x38 / 4]))(am);
    WStr_Format((void*)(s + 0x58), (void*)&DAT_013f3da0, *p);
    int64_t u = ((int64_t(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
    *(int64_t*)(s + 0x68) = u;
    *(int*)(s + 0x70) = 0xffffffff;
    *(char*)(s + 0x74) = 1;
    {
        uint16_t* q = param_3; while (*q) q++;
        unsigned n = (unsigned)((q - param_3) >> 1);
        if (n > 0xff) n = 0x100;
        WStr_Assign((WStr*)param_3, param_3, param_3 + n);
    }
    {
        uint16_t* q = param_4; while (*q) q++;
        unsigned n = (unsigned)((q - param_4) >> 1);
        if (n > 0xfff) n = 0x1000;
        WStr_Assign((WStr*)param_4, param_4, param_4 + n);
    }
    *(int*)(s + 0x2c) = param_6[0];
    *(int*)(s + 0x30) = param_6[1];
    *(int*)(s + 0x34) = param_6[2];
    *(int*)(s + 0x38) = 0xffffffff;
    *(int*)(s + 0x3c) = 0xffffffff;
    *(int*)(s + 0x40) = 0xffffffff;
    *(int*)(s + 0x44) = 0xffffffff;
    if (*(int*)(s + 0x2c) != 0
        && GetParentServerID((int)s, s + 0x38, s + 0x40) == 0
        && ((*(unsigned*)(s + 0x38) & *(unsigned*)(s + 0x3c)) == 0xffffffff)) {
        FUN_0067cb30();
        if (AddPollinatorDebugInfo((int)(s + 0x2c), s + 0x38, 0) != 0) {
            *(int*)(s + 0x40) = *(int*)(s + 0x38);
            *(int*)(s + 0x44) = *(int*)(s + 0x3c);
        }
    }
    if (param_7 == 0) {
        *(int*)(s + 0x18) = 0xffffffff;
        *(int*)(s + 0x1c) = 0xffffffff;
    } else {
        int t = (int)FUN_0067cb30();
        *(int*)(s + 0x18) = *(int*)(t + 0x60);
        *(int*)(s + 0x1c) = *(int*)(t + 100);
    }
    FUN_00554760(*(void**)(s + 0x98), *(void**)(s + 0x9c));
    FUN_00553cc0(p);
    if (param_5 != 0) {
        FUN_00554b60(*(void**)(s + 0xac), *(void**)(s + 0xb0));
        FUN_00550bd0((uint16_t*)param_5);
    }
    return 1;
}

// @ 0x00551620
char Meta::SetMetadata(uint32_t* param_2, int param_3, int param_4, int param_5, void* param_6,
                       uint16_t* param_7, void* param_8, uint16_t* param_9, uint16_t* param_10,
                       uint16_t* param_11, int param_12, void* param_13, char param_14)
{
    char* s = (char*)this;
    *(unsigned*)(s + 0x20) = param_2[0];
    *(unsigned*)(s + 0x24) = param_2[1];
    *(unsigned*)(s + 0x28) = param_2[2];
    *(unsigned*)(s + 8) = param_2[0];
    *(int*)(s + 0xc) = 0x30bdee3;
    *(unsigned*)(s + 0x10) = param_2[2];
    *(int*)(s + 0x18) = param_3;
    *(int*)(s + 0x1c) = param_4;
    *(int*)(s + 0x58) = param_5;
    *(int*)(s + 0x5c) = (int)param_6;
    if (param_14 == 0) {
        *(int*)(s + 0x18) = *(int*)(s + 0x58);
        *(int*)(s + 0x1c) = *(int*)(s + 0x5c);
    } else {
        EA_DateTime_Set(1);
        *(int*)(s + 0x18) = 0;
        *(int*)(s + 0x1c) = 0;
    }
    {
        uint16_t* q = param_7; while (*q) q++;
        unsigned n = (unsigned)((q - param_7) >> 1);
        if (n > 0xff) n = 0x100;
        WStr_Assign((WStr*)param_7, param_7, param_7 + n);
    }
    *(int*)(s + 0x78) = (int)param_8;
    *(int*)(s + 0x88) = (int)param_9;
    *(int*)(s + 0x8c) = 0xffffffff;
    *(char*)(s + 0x90) = 0;
    int* am = (int*)FUN_00607a60();
    int64_t u = ((int64_t(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
    *(char*)(s + 0x90) = (*(int*)(s + 0x78) == (int)u && *(int*)(s + 0x88) == (int)(u >> 32));
    {
        uint16_t* q = param_10; while (*q) q++;
        unsigned n = (unsigned)((q - param_10) >> 1);
        if (n > 0xff) n = 0x100;
        WStr_Assign((WStr*)param_10, param_10, param_10 + n);
    }
    {
        uint16_t* q = param_11; while (*q) q++;
        unsigned n = (unsigned)((q - param_11) >> 1);
        if (n > 0xfff) n = 0x1000;
        WStr_Assign((WStr*)param_11, param_11, param_11 + n);
    }
    FUN_00550bd0((uint16_t*)param_12);
    if (param_13 != 0) {
        FUN_00554760(*(void**)(s + 0x98), *(void**)(s + 0x9c));
        int local_2c[3] = {0, 0, 0};
        char* e = (char*)param_13;
        char* q = e;
        while (*q != 0) q++;
        FUN_0047d390(local_2c, e, q);
        FUN_00553cc0(local_2c);
        if (1 < local_2c[2] - local_2c[0] && local_2c[0] != 0) {
            operator_delete((void*)local_2c[0]);
        }
    }
    return 1;
}

// @ 0x005519d0
void Meta::FUN_005519d0(uint16_t* param_2, uint16_t* param_3, int param_4)
{
    char* s = (char*)this;
    {
        uint16_t* q = param_2; while (*q) q++;
        unsigned n = (unsigned)((q - param_2) >> 1);
        if (n > 0xff) n = 0x100;
        WStr_Assign((WStr*)(s + 0x78), param_2, param_2 + n);
    }
    {
        uint16_t* q = param_3; while (*q) q++;
        unsigned n = (unsigned)((q - param_3) >> 1);
        if (n > 0xfff) n = 0x1000;
        WStr_Assign((WStr*)(s + 0x88), param_3, param_3 + n);
    }
    if (param_4 != 0) {
        FUN_00554b60(*(void**)(s + 0xac), *(void**)(s + 0xb0));
        FUN_00550bd0((uint16_t*)param_4);
    }
}

// @ 0x00551af0
void Meta::FUN_00551af0(int a, int b)
{
    *(int*)((char*)this + 0x18) = a;
    *(int*)((char*)this + 0x1c) = b;
    int* am = (int*)FUN_00607a60();
    int* p = (int*)((int(__thiscall*)(void*))((*(void***)am)[0x38 / 4]))(am);
    WStr_Format((void*)((char*)this + 0x58), (void*)&DAT_013f3da0, *p);
    *(int64_t*)((char*)this + 0x68) = ((int64_t(__thiscall*)(void*))((*(void***)am)[0x40 / 4]))(am);
}
