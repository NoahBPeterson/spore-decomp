// Slice s00674640 - XHTML detokenizer, Spore guide page loader, achievement-test cheat
// helpers, and a cVar-list serializer.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"

struct VObj { void** vt; };
typedef void   (__thiscall *FnV0)(void*);
typedef void   (__thiscall *FnV1)(void*);
typedef void   (__thiscall *FnV1i)(void*, int);
typedef void   (__thiscall *FnV2ip)(void*, int, void*);
typedef void   (__thiscall *FnV3pii)(void*, void*, int, int);
typedef void   (__thiscall *FnV3ipi)(void*, void*, int, void*);
typedef void*  (__thiscall *FnVp0)(void*);
typedef int    (__thiscall *FnVi0)(void*);
typedef bool   (__thiscall *FnVb2ip)(void*, void*, int);
typedef void   (__thiscall *FnV2pp)(void*, void*, void*);
typedef void   (__thiscall *FnV1p)(void*, void*);

void DeleteObj(void* p);   // 0x00f47380

// ---- external callees -------------------------------------------------
void* __cdecl PropertyManager();          // 0x0067de30
void* __cdecl GetMessagingServer();       // 0x00883860
void* __cdecl GetCheatManager();          // 0x0067de20
void  __cdecl FUN_0067cbe0(int a);
void  __cdecl FUN_005fe1d0();
void* __cdecl GetSaveArea(int a);         // 0x006b1f90
void* __cdecl ZoneObjNew(unsigned n, const char* name, int a, int b, int c, int d); // 0x00926020
void* __cdecl ObjectDbCtor(void* db, void* save);  // 0x0069fa60
void  __cdecl FUN_0069e210(void* p);
char  __cdecl FUN_0069e260(void* p, void* key, int a);
void  __cdecl FUN_0069d860(void* p);
void  __cdecl FUN_0069d8e0(void* p);
extern void* g_achievement_test_str;      // [0x0152906c]

// ---- 0x00674640 : TranslateToken (partial skeleton) ------------------
struct Detokenizer {
    void TranslateToken(int a, int b, int* c);
};
// @ 0x00674640
void Detokenizer::TranslateToken(int a, int b, int* c) { (void)a; (void)b; (void)c; }

// ---- 0x00674d30 : Detokenize ----------------------------------------
struct EString16 {
    void* mpBegin;    // +0
    void* mpEnd;      // +4
    void* mpCapacity; // +8
    void* mAlloc;     // +0xc
    void  Resize(int n);                               // 0x00429520
    void  Assign(unsigned short* b, unsigned short* e); // 0x00423650
};
struct CVarVec {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    void  erase(void* first, void* last);              // 0x00673a90
};
struct Detok2 {
    char pad0[0x60];
    int  m60;             // +0x60
    char pad64[0x10];     // +0x64..0x74
    EString16 str74;      // +0x74
    EString16 str84;      // +0x84
    void* mp94;           // +0x94
    char pad98[8];        // +0x98..0xa0
    CVarVec vecA0;        // +0xa0
    void detokenize();    // 0x006729d0

    void Detokenize(const unsigned short* s, void* a2);
};
// @ 0x00674d30
void Detok2::Detokenize(const unsigned short* s, void* a2) {
    mp94 = 0;
    str84.Resize(0);
    str74.Resize(0);
    vecA0.erase(vecA0.mpBegin, vecA0.mpEnd);
    m60 = 0;
    const unsigned short* p = s;
    while (*p) ++p;
    str84.Assign((unsigned short*)s, (unsigned short*)(s + (p - s)));
    mp94 = a2;
    detokenize();
}

// ---- 0x00674dc0 : sBuildXHTMLDocument (partial skeleton) -------------
// @ 0x00674dc0
void sBuildXHTMLDocument(void* a, void* b) { (void)a; (void)b; }

// ---- 0x00675080 : LoadSporeGuidePage (partial skeleton) --------------
struct GuidePage {
    char pad[0x6c];
    void* mpFrame;   // +0x6c
    void LoadSporeGuidePage(void* a);
};
// @ 0x00675080
void GuidePage::LoadSporeGuidePage(void* a) { (void)a; }

// ---- 0x006751a0 ------------------------------------------------------
// @ 0x006751a0
void __stdcall FUN_006751a0(void* a, void* b) {
    void* pm = PropertyManager();
    ((FnV3ipi)((VObj*)pm)->vt[0x2c / 4])(pm, a, 0x5befd27, b);
}

// ---- 0x006751c0 ------------------------------------------------------
// @ 0x006751c0
bool __stdcall FUN_006751c0(unsigned* p) {
    switch ((*p >> 8) & 7) {
    case 0: return p[1] >= p[2];
    case 1: return p[1] > p[2];
    case 2: return p[1] == p[2];
    case 3: return p[1] < p[2];
    case 4: return p[1] <= p[2];
    case 5: return p[1] != p[2];
    default: return false;
    }
}

// ---- 0x00675260 : cVar-list serialization (complete, non-matching) ---
extern void EA_IO_WriteUint32(void* w, void* p, int n, int a); // 0x0093aa70

void WriteIntVal(int* io, int v) {
    int* o = (int*)((FnVp0)((VObj*)io)->vt[0x20 / 4])(io);
    void* w = (void*)((FnVp0)((VObj*)o)->vt[0x18 / 4])(o);
    EA_IO_WriteUint32(w, &v, 1, 0);
}
struct cVarListSerializer {
    char data[0x18];
    cVarListSerializer(void* owner, void* key, int id);  // 0x00692f90
    void Serialize(int* io);                             // 0x00692900
};
struct CVarList {
    char pad[0xc];
    int* mpBegin;  // +0xc
    int* mpEnd;    // +0x10
    void Serialize(int* io);
};
extern char g_1529330;   // [0x01529330]
// @ 0x00675260
void CVarList::Serialize(int* io) {
    WriteIntVal(io, 1);
    WriteIntVal(io, (mpEnd - mpBegin) >> 4);
    for (int* p = mpBegin; p != mpEnd; p += 4) {
        WriteIntVal(io, p[0]);
        WriteIntVal(io, p[2]);
    }
    cVarListSerializer s((void*)this, &g_1529330, 0x1a80d26);
    s.Serialize(io);
}

// ---- 0x00675370 ------------------------------------------------------
// @ 0x00675370
int __fastcall FUN_00675370(char* p) {
    if (p[0x24] == 0) return *(int*)(p + 8) + 0x3c;
    return (int)(p + 0x28);
}

// ---- 0x006753a0 ------------------------------------------------------
// @ 0x006753a0
void __fastcall FUN_006753a0(char* p) {
    void* srv = GetMessagingServer();
    ((FnV3pii)((VObj*)srv)->vt[0x2c / 4])(srv, p, 0x212d3e7, -0x270f);
    ((FnV3pii)((VObj*)srv)->vt[0x2c / 4])(srv, p, 0x238de9c, -0x270f);
    ((FnV3pii)((VObj*)srv)->vt[0x2c / 4])(srv, p, 0x4bef1e3, -0x270f);
    void* cm = GetCheatManager();
    ((FnV1i)((VObj*)cm)->vt[0x1c / 4])(cm, (int)g_achievement_test_str);
    void* a = *(void**)(p + 8);
    if (a) {
        *(void**)(p + 8) = 0;
        ((FnV1)((VObj*)a)->vt[1])(a);
    }
    if (*(void**)(p + 4)) {
        FUN_0067cbe0(0);
        FUN_005fe1d0();
        void* b = *(void**)(p + 4);
        if (b) {
            *(void**)(p + 4) = 0;
            ((FnV1)((VObj*)b)->vt[2])(b);
        }
    }
}

// ---- 0x00675440 : deserialize cVar list (complete, non-matching) -----
struct SerObj {
    char pad[0xc];
    char* mpBegin;  // +0xc
    char* mpEnd;    // +0x10
    unsigned Read(int* io);
};
// @ 0x00675440
unsigned SerObj::Read(int* io) {
    char ok = ((FnVb2ip)((VObj*)io)->vt[0x38 / 4])(io, (void*)0x14010d4, 4);
    char* i = mpBegin;
    char* e = mpEnd;
    while (ok && i != e) {
        ok = ((FnVb2ip)((VObj*)io)->vt[0x38 / 4])(io, i, 4);
        if (ok) {
            ok = ((FnVb2ip)((VObj*)io)->vt[0x38 / 4])(io, i + 8, 4);
            if (ok) ok = 1; else ok = 0;
        } else ok = 0;
        i += 0x10;
    }
    int local = -1;
    if (ok) {
        ok = ((FnVb2ip)((VObj*)io)->vt[0x38 / 4])(io, &local, 4);
        if (ok) return 1;
    }
    return 0;
}

// ---- 0x006754d0 : load object database (complete, non-matching) ------
struct SaveLoader { char pad[8]; void* mp8; };
// @ 0x006754d0
char __fastcall FUN_006754d0(char* p) {
    char stack[0x18];
    void* save = GetSaveArea(0x11ac19c);
    void* db = ZoneObjNew(0x24, "Simulator", 0, 0, 0, 0);
    if (db) db = ObjectDbCtor(db, save);
    else db = 0;
    if (db) ((FnV1)((VObj*)db)->vt[0])(db);
    FUN_0069e210(stack + 8);
    if (!FUN_0069e260(db, (void*)0x1529498, 1)) {
        FUN_0069d860(stack + 8);
        if (db) ((FnV1)((VObj*)db)->vt[1])(db);
        return 0;
    }
    void* src = *(void**)(p + 8);
    ((FnV1p)((VObj*)src)->vt[0x10 / 4])(src, stack + 0x10);
    FUN_0069d8e0(stack + 0x10);
    FUN_0069d860(stack + 8);
    if (db) ((FnV1)((VObj*)db)->vt[1])(db);
    return 1;
}

// ---- 0x00675590 ------------------------------------------------------
// @ 0x00675590
void __fastcall FUN_00675590(char* p) {
    char* i = *(char**)(p + 0xc);
    char* e = *(char**)(p + 0x10);
    while (i != e) {
        if (i[4] & 2) *(int*)(i + 8) = 0;
        i += 0x10;
    }
    p[0x24] = 0;
}
