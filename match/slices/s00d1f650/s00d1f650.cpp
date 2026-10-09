// Slice s00d1f650 -- creature ability / camera helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---- globals -----------------------------------------------------------------
extern void* g_gameModeTribe;    // 0x01654c01
extern void* g_gameModeTribe2;   // 0x01654c02
extern const float g_kOne;       // 0x01485720
extern const float g_kZero;      // 0x01485378
extern const float g_kTen;       // 0x01473c70
extern const float g_k1500;      // 0x0147a2fc

// ---- external callees --------------------------------------------------------
void*  FUN_00d51660();                       // 0x00d51660
void*  FUN_00d2e340();                       // 0x00d2e340
void*  GetCurrentGameMode();                 // 0x00b5b800
void*  NounManager();                        // 0x00b3d300
void*  GetPlayerTribe(void* m);              // 0x00bfc5f0 thiscall
void*  GetGameTerrainCursor();               // 0x00b30d70
void*  GetLeader(void* community);           // 0x00c00650 thiscall
unsigned char FUN_00c0e0c0(void* this_, int id);  // 0x00c0e0c0 thiscall ret4
unsigned char FUN_00c0c0e0(void* this_);     // 0x00c0c0e0 thiscall
void*  FUN_00c0ee60(void* this_);            // 0x00c0ee60 thiscall
void*  GetTargetAsCreature(void* this_);     // 0x00c0ee70 thiscall
int    GetToolOfType(void* tribe, int type); // 0x00c8f6e0 thiscall ret4
unsigned char AbilityIsBeingTaughtToBaby(int a); // 0x00d1e6c0 cdecl
unsigned char FUN_00d1f400(void* p);         // 0x00d1f400 cdecl
int    FUN_00d1e530(void* a, void* b, void* c, void* d); // 0x00d1e530 cdecl
unsigned char FUN_00d1e8d0(void* a, void* b); // 0x00d1e8d0 cdecl
void*  CanSocial(void* a, void* b);          // 0x00d1e720 cdecl
void*  PlayIdleAnimation(void* anim, int a, int b); // 0x00bc96a0 thiscall ret 8
void   RemoveHandler(void* a, int b, void* c, void* d, void* e); // 0x00571db0 cdecl
void*  FUN_0067cab0v(int a);                 // 0x0067cab0 cdecl
void   GetFileCount2();
void   FUN_00b5b800_2();

struct InputState {
    void Reset();                              // 0x00697980
    void OnKeyDown(int a, int b);              // 0x00697a50
    void OnKeyUp(int a, int b);                // 0x00697a80
    void OnMouseUp(int a, float b, float c, int d); // 0x00697af0
    void OnMouseWheel(int a, float b, float c, int d); // 0x00697b40
    void GetSpatialObjects(int* v);            // 0x00b30d70? no
};
struct TerrainCursor {
    void GetSpatialObjects(int* v);            // 0x00b30d70 vtable 0x5c
};
void FUN_008d2f30(int a, int b);               // 0x008d2f30 cdecl
void CanvasVisibilitySetter(int* v);           // 0x008013d0
void CursorLayoutIsThing(int* v);              // 0x00801950
void CursorLayoutSetEnabled(int* v);           // 0x00801980
void* FUN_0067cab0(int a);                     // 0x0067cab0 cdecl

struct CanvasObj { void SetVisibility(); };    // 0x008013d0 thiscall
struct CursorLayout { void IsThing(); void SetEnabled(); }; // 0x00801950/80 thiscall

struct Cam {
    unsigned char Init(int a);
    void Deactivate();
    void SetCameraUI(char on);
    unsigned char OnKeyDown(int a, int b);
    unsigned char OnKeyUp(int a, int b);
    unsigned char OnMouseUp(int a, float b, float c, int d);
    unsigned char OnMouseWheel(int a, float b, float c, int d);
};

// @ 0x00d203d0
unsigned char Cam::Init(int a)
{
    (void)a;
    ((InputState*)((char*)this + 0x2bc))->Reset();
    return 1;
}

// @ 0x00d203e0
void Cam::Deactivate()
{
    if (*(unsigned char*)((char*)this + 0x304) != 0) {
        int p0 = *(int*)((char*)this + 0x29c);
        if (p0 != 0) {
            int p1 = *(int*)((char*)this + 0x2a0);
            int p2 = *(int*)((char*)this + 0x2a4);
            int p3 = *(int*)((char*)this + 0x2a8);
            int p4 = *(int*)((char*)this + 0x2ac);
            *(int*)((char*)this + 0x29c) = 0;
            RemoveHandler((void*)p0, p1, (void*)p2, (void*)p3, (void*)p4);
        }
        *(unsigned char*)((char*)this + 0x304) = 0;
    }
}

// @ 0x00d20430
void Cam::SetCameraUI(char on)
{
    if (on != 0) {
        FUN_008d2f30((int)((char*)this + 0x30c), (int)((char*)this + 0x310));
        ((CanvasObj*)FUN_0067cab0(0))->SetVisibility();
        ((CursorLayout*)FUN_0067cab0(0x67f5c34))->IsThing();
        ((CursorLayout*)FUN_0067cab0(1))->SetEnabled();
        *(unsigned char*)((char*)this + 0x314) = 1;
    } else {
        ((CanvasObj*)FUN_0067cab0(1))->SetVisibility();
        ((CursorLayout*)FUN_0067cab0(0))->SetEnabled();
        *(unsigned char*)((char*)this + 0x314) = 0;
    }
}

// @ 0x00d204c0
unsigned char Cam::OnKeyDown(int a, int b)
{
    ((InputState*)((char*)this + 0x2bc))->OnKeyDown(a, b);
    return 0;
}

// @ 0x00d204e0
unsigned char Cam::OnKeyUp(int a, int b)
{
    ((InputState*)((char*)this + 0x2bc))->OnKeyUp(a, b);
    return 0;
}

// @ 0x00d20500
unsigned char Cam::OnMouseUp(int a, float b, float c, int d)
{
    ((InputState*)((char*)this + 0x2bc))->OnMouseUp(a, b, c, d);
    return 0;
}

// @ 0x00d20530
unsigned char Cam::OnMouseWheel(int a, float b, float c, int d)
{
    ((InputState*)((char*)this + 0x2bc))->OnMouseWheel(a, b, c, d);
    float f = 1.0f - (float)a * *(float*)((char*)this + 0x200);
    if (*(int*)((char*)this + 0x1ec) == 2) {
        float v = f * *(float*)((char*)this + 0x188);
        float lo = *(float*)((char*)this + 0x210);
        v = (v < lo) ? lo : v;
        v = (v > 1500.0f) ? 1500.0f : v;
        *(float*)((char*)this + 0x188) = v;
    } else {
        *(float*)((char*)this + 0x17c) = f * *(float*)((char*)this + 0x17c);
    }
    return 0;
}

// @ 0x00d1fa20
unsigned char F_d1fa20(int* p)
{
    if (p[3] == 4)
        return FUN_00d1f400(p);
    if (GetCurrentGameMode() == (void*)0x01654c02) {
        void* tribe = GetPlayerTribe(NounManager());
        switch (p[2]) {
        case 5:  return GetToolOfType(tribe, 4) != 0;
        case 6:  return GetToolOfType(tribe, 5) != 0;
        case 7:  return GetToolOfType(tribe, 6) != 0;
        case 0x2b: return GetToolOfType(tribe, 3) != 0;
        case 0x3a: return GetToolOfType(tribe, 1) != 0;
        case 0x3b: return GetToolOfType(tribe, 2) != 0;
        default: return 0;
        }
    }
    return 1;
}

// @ 0x00d201f0
unsigned char F_d201f0(int* p)
{
    if (GetCurrentGameMode() != (void*)0x01654c02)
        return 1;
    if (p[3] == 4)
        return 1;
    void* tribe = GetPlayerTribe(NounManager());
    int want = 4;
    switch (p[2]) {
    case 5:  if (GetToolOfType(tribe, 4) == 0) return 0; want = 4; break;
    case 6:  if (GetToolOfType(tribe, 5) == 0) return 0; want = 5; break;
    case 7:  if (GetToolOfType(tribe, 6) == 0) return 0; want = 6; break;
    case 0x2b: if (GetToolOfType(tribe, 3) == 0) return 0; want = 3; break;
    case 0x3a: if (GetToolOfType(tribe, 1) == 0) return 0; want = 1; break;
    case 0x3b: if (GetToolOfType(tribe, 2) == 0) return 0; want = 2; break;
    default: return 0;
    }
    (void)want;
    return 0;
}

// ---- big ability-scoring functions (partial) ---------------------------------
// @ 0x00d1f650
unsigned int F_d1f650(void* creature, int a) { (void)creature; (void)a; return 0; }
// @ 0x00d1fb30
int F_d1fb30(unsigned int a) { (void)a; return 1; }
// @ 0x00d1fe00
void F_d1fe00(unsigned int a) { (void)a; }
// @ 0x00d200a0
float F_d200a0(int a) { (void)a; return 0.0f; }
