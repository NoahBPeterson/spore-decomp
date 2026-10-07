// Slice s00f15890: SP UI refresh (thiscall, no args). Two branches on this+0xb8 and a
// shared tail; window lookups by hashed id, vcalls on IWindow (see notes in partial.txt).
// Flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

struct Rect4 { float l, t, r, b; };
struct cString {
    cString(uint32_t table, uint32_t key, int flags);  // 0x006b5770 thiscall, ret 0xc
    ~cString();                                        // 0x006b5240 thiscall
    const wchar_t* GetText();                          // 0x006b55c0 thiscall
};
struct cSPUILayout {
    void* FindWindowByID(uint32_t id, int recurse);    // 0x008105b0 thiscall, ret 8
};
struct Property {
    int* GetInt();                                     // 0x0041e990 thiscall
};

#define VFN(obj, off) (*(void***)(obj))[(off) / 4]
typedef int  (__thiscall* FnRef)(void*);
typedef void (__thiscall* FnSetFlag)(void*, int, int);
typedef void (__thiscall* FnSetCaption)(void*, const wchar_t*);
typedef void (__thiscall* FnSetArea)(void*, const Rect4*);
typedef void* (__thiscall* FnGetArea)(void*);
typedef void* (__thiscall* FnFindVirt)(void*, uint32_t, int);
typedef void (__thiscall* FnVoid)(void*);

extern "C" {
void  __cdecl FUN_00f14120(void* out, const wchar_t* fmt, ...);        // 0x00f14120
int   __cdecl FUN_00eec540(int);                                       // 0x00eec540
int   __cdecl FUN_00eec580(int);                                       // 0x00eec580
int   __cdecl FUN_00eec570(void);                                      // 0x00eec570
float __cdecl FUN_00eec5b0(void);                                      // 0x00eec5b0 (st0)
void* __cdecl FUN_0067cb30(void);                                      // 0x0067cb30
void  __cdecl SetNumberString(int64_t v, wchar_t* buf, int n);         // 0x00881ae0
void* __cdecl SP_WindowManager(void);                                  // 0x0067caa0
void  __cdecl SP_SetImageFromLayout(void* w, void* layout, uint32_t id, int n); // 0x00806a60
bool  __cdecl FUN_00f19640(void);                                      // 0x00f19640
void* __cdecl AchievementsController(uint32_t key, int flag);          // 0x00675250
}

struct Obj10 {
    int   GetA();                 // 0x00f191a0 thiscall
    int   GetElapsed();           // 0x00f19190 thiscall
    float GetScale();             // 0x00f19d10 thiscall
    int   GetKey();               // 0x008dc790 thiscall (hkGenericConstraintData::getScheme)
};
struct Obj20 {
    void Set(int a, int b, int c, int d);  // 0x00f46cf0 thiscall, ret 0x10
};
struct Obj28 {
    void Init(int a);                      // 0x00f14d90 thiscall, ret 4
};
struct GMgr {
    void* Timers();               // 0x00f3bcb0 thiscall (ecx = G+0x74)
};
struct AchCtl {
    void AutoTest();              // 0x00676e90 thiscall
};
struct AssetMgr {
    void* ServerDir();            // 0x0067cb30 is free; 0x0060e600 thiscall follow-up
};

struct PanelStub {
    void Refresh();
};

extern "C" {
// Globals: DAT_016c7aa4 holds a pointer to the global game object (+0x74 sub-object).
extern void* g_pGlobal_016c7aa4;
}

void PanelStub::Refresh() {
    char* s = (char*)this;
    wchar_t buf[26];
    buf[0] = 0;
    wchar_t* pTxt = buf;
    Obj10* m10 = *(Obj10**)(s + 0x10);
    bool isFive = (*(int*)((char*)m10 + 0x90) == 5);

    int a = m10->GetA();   // kept in its frame slot; used below as (float)a and as int64

    if (*(int*)(s + 0xb8) == 0) {
        // Branch A (f15d21): swap window at +0xdc with the id 0x7c79820, then SetFlag on 0x7c796d0.
        cSPUILayout* layout = *(cSPUILayout**)(s + 0x18);
        void* w = layout->FindWindowByID(0x7c79820, 1);
        void* old = *(void**)(s + 0xdc);
        if (w != old) {
            if (w) ((FnRef)VFN(w, 0))(w);
            *(void**)(s + 0xdc) = w;
            if (old) ((FnVoid)VFN(old, 4))(old);
        }
        w = layout->FindWindowByID(0x7c796d0, 1);
        if (w) ((FnSetFlag)VFN(w, 0x7c))(w, 1, 0);
    } else {
        // Branch B (f158f8..f15d1f): swap window at +0xdc with the id 0x7c796d0, then SetFlag on 0x7c79820.
        cSPUILayout* layout = *(cSPUILayout**)(s + 0x18);
        void* w = layout->FindWindowByID(0x7c796d0, 1);
        void* old = *(void**)(s + 0xdc);
        if (w != old) {
            if (w) ((FnRef)VFN(w, 0))(w);
            *(void**)(s + 0xdc) = w;
            if (old) ((FnVoid)VFN(old, 4))(old);
        }
        w = layout->FindWindowByID(0x7c79820, 1);
        if (w) ((FnSetFlag)VFN(w, 0x7c))(w, 1, 0);

        int idx = 0;
        void* p = *(void**)(s + 0xb8);
        if (p) {
            void* prop = 0;
            // f1596a: vcall +0x24(hash 0xcf837237, &prop)
            if (((bool (__thiscall*)(void*, uint32_t, void**))VFN(p, 0x24))(p, 0xcf837237, &prop)
                && *(short*)((char*)prop + 0x12) == 9) {
                idx = *((Property*)prop)->GetInt();
            }
        }
        (void)idx;
        // Remaining body of Branch B is not decoded yet; see partial.txt.
    }

    // Common tail (f15d77).
    if (*(void**)(s + 0xdc))
        ((FnSetFlag)VFN(*(void**)(s + 0xdc), 0x7c))(*(void**)(s + 0xdc), 1, 1);
    (void)pTxt; (void)a; (void)isFive;
}
