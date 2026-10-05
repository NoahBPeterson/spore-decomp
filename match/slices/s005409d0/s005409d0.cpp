// Slice s005409d0: paint-variable evaluator containers + local-light helpers
// + SP::cConfigManager::Init / integer-prefix parser.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <ctype.h>
#include <stdio.h>
#include <wchar.h>

typedef unsigned int size_t;

// ---------------------------------------------------------------- externals
void* operator new[](size_t, const char*, int, unsigned, const char*, int);
void  operator_delete__(void*);
void* FUN_0042dee0(void* alloc, int size, int align, int flags); // @ 0x42dee0
void  FUN_004098a0(void* dst, void* src);            // @ 0x4098a0
int   FUN_0050f8b0(int a, int b, int c);             // @ 0x50f8b0
void  FUN_00457450(int a, int b, void* c, char d);   // @ 0x457450
void  FUN_00512050(int a, int b, int c, int d, char e); // @ 0x512050
void  FUN_0050eb40(int a, int b, int c);             // @ 0x50eb40
void  FUN_00540e80(int a, int b, int c);             // @ 0x540e80
void  FUN_005414d0(void* a, int b, int c, int d, char e); // @ 0x5414d0
void  FUN_00541550(int a, int b, void* c, char d);   // @ 0x541550
int   FUN_005415b0(int a, int b, int c);             // @ 0x5415b0
int   FUN_00540f90(int a, int b, int c);             // @ 0x540f90
void* DoInsertBool(void* vec, void* pos, int n);     // @ 0x11e0744
int   FUN_0092d6f0(const unsigned char* s, int end, int base); // strtol-like
int   FUN_00454d50(const void* table, int start, int end);     // @ 0x454d50
void  FUN_0092e200(int a, int b, int c, unsigned d, unsigned e, int f); // @ 0x92e200
void  FUN_0092e470(int a, int b);                    // @ 0x92e470
void  EADateTime_Set(int a);                         // EA::DateTime::Set
void  FUN_009289f0(void* self, int a, int b, int c, int d, int e, int f); // @ 0x9289f0
void  FUN_00928a80(void* self, int a, int b, int c); // @ 0x928a80
void  FUN_09276c0(void* self, int a);                // @ 0x9276c0

// local-light manager pointer used by the thunks
struct LocalLightMgr {
    void FUN_009289f0(int a, int b, int c, int d, int e, int f);
    void FUN_00928a80(int a, int b, int c);
    void FUN_09276c0(int a);
};
extern LocalLightMgr* g_pLocalLight;    // @ 0x16c8b44

extern unsigned short gCfgDateTable[];  // @ 0x13f3a00
extern unsigned short gCfgTime12[];     // @ 0x13f39e4
extern unsigned short gCfgTime24[];     // @ 0x13f39dc
extern unsigned short gCfgColonTable[]; // @ 0x13f39dc (second)
extern unsigned char  gParsePrefixA[];  // @ 0x13f34dc
extern unsigned char  gParsePrefixB[];  // @ 0x13f34b8

// ---------------------------------------------------------------- entry
struct Entry18 { int m0, m1, m2; float f0, f1, f2; };

struct Obj {
    char mPad[0x200];

    // container helpers: `this` is the container (begin/end/cap at +0/+4/+8)
    void  FUN_005409d0(int* pos, unsigned int n, int* value);
    Entry18* FUN_00540f20(Entry18* src);
    void  FUN_00541030(int* pos, unsigned int n, int* value);
};

// @ 0x005409d0  (vector of 0x18-byte entries: insert/grow)
void Obj::FUN_005409d0(int* pos, unsigned int n, int* value)
{
    int* v = (int*)this;
    if ((unsigned int)((v[2] - v[1]) / 0x18) < n) {
        int old = (v[1] - *v) / 0x18;
        unsigned int cap = old == 0 ? 1 : (unsigned int)(old << 1);
        unsigned int need = (unsigned int)old + n;
        unsigned int newCap = cap < need ? need : cap;
        int* newBuf = newCap == 0 ? 0 : (int*)FUN_0042dee0((char*)v + 0xc, newCap * 0x18, 4, 0);
        int dst = newBuf ? (int)newBuf : 0;
        int mid = FUN_00540f90(*v, (int)pos, dst);
        FUN_00541550(mid, n, value, 0);
        mid = FUN_005415b0((int)pos, v[1], (int)(n * 0x18 + mid));
        if (*v != 0 && *(int*)(*v - 4) != 0)
            operator_delete__((void*)*v);
        *v = dst;
        v[1] = mid;
        v[2] = (int)(newCap * 0x18 + dst);
    } else if (n != 0) {
        int local_20 = value[0];
        int local_1c = value[1];
        int local_18 = value[2];
        int local_14 = value[3];
        int local_10 = value[4];
        int local_c = value[5];
        unsigned int rest = (v[1] - (int)pos) / 0x18;
        int* end = (int*)v[1];
        if (n < rest) {
            FUN_005414d0(0, v[1] + n * -0x18, v[1], v[1], 0);
            v[1] = (int)(n * 0x18 + v[1]);
            int* w = end;
            int* r = end + n * -6;
            while (r != pos) {
                w[-6] = r[-6]; w[-5] = r[-5]; w[-4] = r[-4];
                w[-3] = r[-3]; w[-2] = r[-2]; w[-1] = r[-1];
                w = w - 6; r = r - 6;
            }
            for (int* p = pos; p != pos + n * 6; p = p + 6) {
                p[0] = local_20; p[1] = local_1c; p[2] = local_18;
                p[3] = local_14; p[4] = local_10; p[5] = local_c;
            }
        } else {
            FUN_00541550(v[1], n - rest, &local_20, 0);
            v[1] = (int)((n - rest) * 0x18 + v[1]);
            FUN_00540e80((int)pos, (int)end, v[1]);
            v[1] = (int)(rest * 0x18 + v[1]);
            for (int* p = pos; p != end; p = p + 6) {
                p[0] = local_20; p[1] = local_1c; p[2] = local_18;
                p[3] = local_14; p[4] = local_10; p[5] = local_c;
            }
        }
    }
}

// @ 0x00540f20
Entry18* Obj::FUN_00540f20(Entry18* p)
{
    *(int*)this = *(int*)p;
    ((int*)this)[1] = ((int*)p)[1];
    ((int*)this)[2] = ((int*)p)[2];
    float* src = (float*)((char*)p + 0xc);
    float* first = (float*)((char*)this + 0xc);
    first[0] = src[0];
    first[1] = src[1];
    first[2] = src[2];
    return (Entry18*)this;
}

// @ 0x00541030  (vector of 0xc-byte entries: insert/grow)
void Obj::FUN_00541030(int* pos, unsigned int n, int* value)
{
    int* v = (int*)this;
    if ((unsigned int)((v[2] - v[1]) / 0xc) < n) {
        int old = (v[1] - *v) / 0xc;
        unsigned int cap = old == 0 ? 1 : (unsigned int)(old << 1);
        unsigned int need = (unsigned int)old + n;
        unsigned int newCap = cap < need ? need : cap;
        int* newBuf = newCap == 0 ? 0 : (int*)FUN_0042dee0((char*)v + 0xc, newCap * 0xc, 4, 0);
        int dst = newBuf ? (int)newBuf : 0;
        int mid = FUN_0050f8b0(*v, (int)pos, dst);
        FUN_00457450(mid, n, value, 0);
        mid = FUN_0050f8b0((int)pos, v[1], (int)(n * 0xc + mid));
        if (*v != 0 && *(int*)(*v - 4) != 0)
            operator_delete__((void*)*v);
        *v = dst;
        v[1] = mid;
        v[2] = (int)(newCap * 0xc + dst);
    } else if (n != 0) {
        int local_14 = value[0];
        int local_10 = value[1];
        int local_c = value[2];
        unsigned int rest = (v[1] - (int)pos) / 0xc;
        int* end = (int*)v[1];
        if (n < rest) {
            FUN_00512050(0, v[1] + n * -0xc, v[1], v[1], 0);
            v[1] = (int)(n * 0xc + v[1]);
            int* w = end;
            int* r = end + n * -3;
            while (r != pos) {
                w[-3] = r[-3]; w[-2] = r[-2]; w[-1] = r[-1];
                w = w - 3; r = r - 3;
            }
            for (int* p = pos; p != pos + n * 3; p = p + 3) {
                p[0] = local_14; p[1] = local_10; p[2] = local_c;
            }
        } else {
            FUN_00457450(v[1], n - rest, &local_14, 0);
            v[1] = (int)((n - rest) * 0xc + v[1]);
            FUN_0050eb40((int)pos, (int)end, v[1]);
            v[1] = (int)(rest * 0xc + v[1]);
            for (int* p = pos; p != end; p = p + 3) {
                p[0] = local_14; p[1] = local_10; p[2] = local_c;
            }
        }
    }
}

// @ 0x00541420
void* FUN_00541420(void* a, int b, void* c)
{
    return (void*)((int)DoInsertBool(c, a, b - (int)a)
                   + ((b - (int)a) >> 2) * 4);
}

// @ 0x00541450
int* FUN_00541450(int* out, int* a, int* b, int* dst)
{
    int* p = dst;
    for (; a != b; a = a + 2) {
        if (p != 0) {
            p[0] = a[0];
            p[1] = a[1];
        }
        p = p + 2;
    }
    *out = (int)p;
    return out;
}

// @ 0x00541600
void FUN_00541600(int a)
{
    int local;
    (void)local;
    g_pLocalLight->FUN_009289f0(a, 0, 0, 0, 0, 0);
}

// @ 0x00541630
void FUN_00541630(int a, int b)
{
    bool local = 0;
    (void)local;
    g_pLocalLight->FUN_00928a80(a, b, 0);
}

// @ 0x00541660
void FUN_00541660(int a)
{
    g_pLocalLight->FUN_09276c0(a);
}

// @ 0x00541680
char SP_ConfigManager_Init(void* param_1, int* param_2)
{
    char local_11 = 0;
    EADateTime_Set(1);
    wchar_t* s = (wchar_t*)*(int*)param_1;
    int y = 0, mo = 0, d = 0;
    int iVar1 = swscanf(s, L"%d-%d-%d", &y, &mo, &d);
    if (iVar1 == 3) {
        unsigned short* p = gCfgDateTable;
        while (*p != 0) p = p + 1;
        iVar1 = FUN_00454d50(gCfgDateTable, 0, (int)(p - gCfgDateTable));
        if (iVar1 != -1) {
            unsigned int h = 0, mi = 0;
            int se = 0;
            int iVar2 = swscanf(s + iVar1 + 1, L"%d:%d:%d", &h, &mi, &se);
            if (iVar2 == 3) {
                FUN_0092e200(y, mo, d, h, mi, se);
                unsigned short* q = gCfgTime12;
                while (*q != 0) q = q + 1;
                iVar2 = FUN_00454d50(gCfgTime12, iVar1, (int)(q - gCfgTime12));
                if (iVar2 == -1) {
                    unsigned short* r = gCfgTime24;
                    while (*r != 0) r = r + 1;
                    iVar1 = FUN_00454d50(gCfgTime24, iVar1, (int)(r - gCfgTime24));
                    iVar2 = swscanf(s + iVar1 + 1, L"%d:%d", &h, &mi);
                    if (iVar2 == 2) {
                        local_11 = 1;
                    } else {
                        iVar2 = swscanf(s + iVar1 + 1, L"%d", &h);
                        if (iVar2 == 1) {
                            mi = h % 100;
                            h = h / 100;
                            local_11 = 1;
                        }
                    }
                    if (local_11 != 0) {
                        if (s[iVar1] == L'-') {
                            FUN_0092e470(8, h);
                            FUN_0092e470(9, mi);
                        } else {
                            FUN_0092e470(8, -(int)h);
                            FUN_0092e470(9, -(int)mi);
                        }
                    }
                } else {
                    local_11 = 1;
                }
            }
        }
    }
    param_2[0] = 0;
    param_2[1] = 0;
    return local_11;
}

// @ 0x005418c0
unsigned int FUN_005418c0(unsigned char* s)
{
    unsigned char* local_8 = s;
    if (s != 0) {
        unsigned char* c = gParsePrefixA;
        for (; *c != 0 && *local_8 == *c; local_8 = local_8 + 1)
            c = c + 1;
        if (*c == 0) {
            if (isdigit(*local_8)) {
                unsigned int v = FUN_0092d6f0(local_8, 0, 10);
                return v;
            }
            unsigned char* c2 = gParsePrefixB;
            for (; *c2 != 0 && *local_8 == *c2; local_8 = local_8 + 1)
                c2 = c2 + 1;
            if (*c2 == 0) {
                unsigned int v = FUN_0092d6f0(local_8, 0, 10);
                return v;
            }
        }
    }
    return 0xffffffff;
}
