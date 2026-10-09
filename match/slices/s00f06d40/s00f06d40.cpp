// Heap/sort helpers for a UI list, plus two message dispatchers.
// Elements are pointers to nodes whose +0x24 dword is a priority kind
// (rank: 2 -> 0, 9 -> 1, anything else -> 2).  /O2.
//
// Flags: /O2 /MD /Gy /TP

#include <math.h>

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;

struct Node {
    char pad[0x24];
    int  mKind;   // +0x24
};

__forceinline int Rank(Node* n)
{
    int k = n->mKind;
    int r = 0;
    if (k != 2)
        r = (k != 9) + 1;
    return r;
}

extern char* g_pTable;   // 0x016c7d90

// ---------------------------------------------------------------------------
// 0x00f07770  priority comparison
// ---------------------------------------------------------------------------
// @ 0x00f07770
bool __stdcall FUN_00f07770(Node* a, Node* b)
{
    int ra = Rank(a);
    int rb = b->mKind == 2 ? 0 : ((b->mKind != 9) + 1);
    int c = ra <= rb;
    return c != 0;
}

// ---------------------------------------------------------------------------
// 0x00f077c0  table lookup + kind switch
// ---------------------------------------------------------------------------
struct Entry { int k, pad1, slot, pad2; };   // 0x10

struct Box {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual int  GetKey();     // +0x10
    virtual void v5(); virtual void v6();
    virtual int  GetKind();    // +0x1c
};

// @ 0x00f077c0
void FUN_00f077c0(Box* box)
{
    int key = box->GetKey();
    Entry* p = 0;
    for (int i = 0; i < 5; ++i) {
        if (((Entry*)g_pTable)[i + 1].k == key) {
            p = &((Entry*)g_pTable)[i + 1];
            break;
        }
    }
    switch (box->GetKind()) {
    case 0xcefa1210: p->slot = 0; return;
    case 0xcefa1220: p->slot = 1; return;
    case 0xcefa1230: p->slot = 2; return;
    case 0xcefa1240: p->slot = 3; return;
    }
    p->slot = 0;
}

// ---------------------------------------------------------------------------
// 0x00f078a0  table lookup accessor
// ---------------------------------------------------------------------------
// @ 0x00f078a0
int FUN_00f078a0()
{
    if (g_pTable)
        return *(int*)(g_pTable + 0xc);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00f078b0  float -> bucket index
// ---------------------------------------------------------------------------
// @ 0x00f078b0
int FUN_00f078b0(float* p, float scale)
{
    float v = p[1];
    if ((-scale <= v) && (v <= scale * 4.5f) && (-100.0f <= p[0]) && (p[0] <= 100.0f)) {
        float n = (float)(int)(v / scale);
        if (n < 0.0f)
            n = 0.0f;
        if (n > 4.0f)
            n = 4.0f;
        return (int)n;
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x00f07960  x87 blend helper
// ---------------------------------------------------------------------------
// @ 0x00f07960
float FUN_00f07960(float a, float b)
{
    if (fabsf(a - b) < 4.0f)
        return b;
    float v = (b - a) * 0.2f + a;
    if (4.0f <= fabsf(a - v))
        return v;
    float d = b - a;
    return (fabsf(d) / d) * 4.0f + a;
}

// ---------------------------------------------------------------------------
// 0x00f079e0  insertion sort (backward shift)
// ---------------------------------------------------------------------------
// @ 0x00f079e0
void FUN_00f079e0(Node** first, Node** last)
{
    if (first != last) {
        Node** it = first + 1;
        if (it != last) {
            do {
                Node* v = *it;
                Node** q = it;
                while (q != first) {
                    int rv = Rank(v);
                    int rp = Rank(q[-1]);
                    if (rv > rp)
                        break;
                    *q = q[-1];
                    --q;
                }
                *q = v;
                ++it;
            } while (it != last);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00f07a60  insertion sort (forward shift)
// ---------------------------------------------------------------------------
// @ 0x00f07a60
void FUN_00f07a60(Node** first, Node** last)
{
    for (; first != last; ++first) {
        Node* v = *first;
        Node** p = first;
        Node** q = first;
        for (;;) {
            --q;
            if (Rank(v) > Rank(*q))
                break;
            *p = *q;
            --p;
        }
        *p = v;
    }
}

// ---------------------------------------------------------------------------
// 0x00f07ae0  choose the minimum of three (heap-based)
// ---------------------------------------------------------------------------
// @ 0x00f07ae0
Node** FUN_00f07ae0(Node** a, Node** b, Node** c)
{
    Node* x = *a;
    Node* y = *b;
    if (Rank(y) < Rank(x)) {
        Node* z = *c;
        if (Rank(x) <= Rank(z))
            return a;
        if (FUN_00f07770(y, z))
            return c;
    } else {
        Node* z = *c;
        if (Rank(z) < Rank(y)) {
            if (FUN_00f07770(x, z))
                return a;
            return c;
        }
    }
    return b;
}

// ---------------------------------------------------------------------------
// 0x00f07bd0  destroy a range of 0x44-byte elements
// ---------------------------------------------------------------------------
extern void FUN_00f280f0(void* self);   // element dtor (thiscall)
struct Destructible { void dtor(); };

// @ 0x00f07bd0
char* FUN_00f07bd0(char* first, char* last, char* out)
{
    if (first != last) {
        do {
            ((Destructible*)(first + 4))->dtor();
            first += 0x44;
            out += 0x44;
        } while (first != last);
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00f07c10  sift-up
// ---------------------------------------------------------------------------
// @ 0x00f07c10
void FUN_00f07c10(Node** heap, int idx, int top, Node* v)
{
    if (idx <= top) {
        heap[idx] = v;
        return;
    }
    for (;;) {
        int parent = (idx - 1) >> 1;
        Node* p = heap[parent];
        if (Rank(p) > Rank(v))
            heap[idx] = p;
        if (Rank(p) <= Rank(v))
            break;
        idx = parent;
        if (top >= parent)
            break;
    }
    heap[idx] = v;
}

// ---------------------------------------------------------------------------
// 0x00f06d40  message dispatcher (big)
// ---------------------------------------------------------------------------
extern void FUN_00f065d0();            // 0x00f065d0
extern void FUN_00f06660();            // 0x00f06660
extern void FUN_00f03fc0();            // 0x00f03fc0
extern void FUN_00f044d0();            // 0x00f044d0
extern void FUN_00f03e20();            // 0x00f03e20
extern int  GetRecorderState();        // 0x00435e90
extern void SP_cSPUISpace_KillSetiEffects(int, int); // 0x00435ed0
extern int  ConfigManager();           // 0x0067dd30
extern int  Pollen_AuthManager();      // 0x00607a60
extern void UI_CalloutMessageBox(int, int); // 0x00809db0
extern int  cSPPlayModeSubModeMovie_GetYTPrompt(); // 0x0063b890

// @ 0x00f06d40
bool FUN_00f06d40(int msgId, int* msg)
{
    int sub = *(int*)((char*)msg + 8);
    if (sub == 1) {
        return true;
    }
    if (sub != 0x287259f6)
        return false;
    int id = *(int*)((char*)msg + 0xc);
    switch (id) {
    case 0x5652348: FUN_00f065d0(); return true;
    case 0x5665f58: {
        int cm = ConfigManager();
        void* vt = *(void**)cm;
        (*(void(__thiscall**)(int, int))((char*)vt + 0x30))(cm, 0x5664a8b);
        return true;
    }
    case 0x56be960: FUN_00f06660(); return true;
    case 0x5adbea8: FUN_00f03fc0(); FUN_00f044d0(); return true;
    case 0x5b5bd80: return true;
    case 0x5b5ef51:
        GetRecorderState();
        SP_cSPUISpace_KillSetiEffects(0xe76c9b4f, 0);
        FUN_00f03e20();
        return true;
    case 0x5b5ef52: return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00f072b0  message dispatcher (big)
// ---------------------------------------------------------------------------
extern int  GameTimeManager();         // 0x00b3d380
extern void FUN_00b32250();            // 0x00b32250
extern int  EffectsManager();          // 0x0067ddd0
extern void FUN_00a16f40();            // 0x00a16f40
extern int  WindowManager();           // 0x0067caa0
extern void cSPUIMainWin_OnKeyDown();  // 0x008143a0

// @ 0x00f072b0
bool FUN_00f072b0(int msgId, int* msg)
{
    (void)msg;
    switch (msgId) {
    case 0x7c651b0: return false;
    case 0x7c651b1:
        GameTimeManager();
        FUN_00b32250();
        return false;
    case 0x7d62123:
        return false;
    }
    return false;
}
