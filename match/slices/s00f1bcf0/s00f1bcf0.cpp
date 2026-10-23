// slice s00f1bcf0 -- SP::cSPEditorVerbTray (coin name; the verb-icon tray owned by the editor),
// five members: the per-index label lookup, the selection/refresh pass, the ability-pair search,
// the show/hide of the creature's verb icons, and the scroll/refresh step.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE
#include "types.h"

// The original source scans for the terminator with an explicit loop (the compiler's
// wcslen intrinsic emits a different word-load form), so reproduce it that way.
static __inline const wchar_t* wend(const wchar_t* s)
{
    const wchar_t* p = s;
    while (*p)
        ++p;
    return p;
}

// ---------------------------------------------------------------------------
// calling-convention helpers
// ---------------------------------------------------------------------------
typedef void  (__thiscall *FnV)(void*);
typedef void* (__thiscall *FnP)(void*);
typedef void* (__thiscall *FnPI)(void*, int);
typedef void  (__thiscall *FnVI)(void*, int);
typedef void  (__thiscall *FnVII)(void*, int, int);
typedef void  (__thiscall *FnVIII)(void*, int, int, int);
typedef int   (__thiscall *FnI)(void*);
typedef char  (__thiscall *FnC)(void*);

// ---------------------------------------------------------------------------
// externals (conventions set here; only the marker functions are matched)
// ---------------------------------------------------------------------------
extern "C" void* FUN_00f264d0(int a, int b, int c);        // cdecl, 3 args
extern "C" void  operator_delete(void* p);                  // 0x00f47380 cdecl
extern "C" bool  FUN_00f3c870(void* a, void* b, float f, int c);  // 0x00f3c870 stdcall, 4 args
extern "C" void* EA_GetSystemAT();                          // 0x00a206f0 cdecl, 0 args
extern "C" void* SP_NounManager();                          // 0x00b3d300 cdecl, 0 args

extern int g_16c7aa4;                                       // the global at 0x016c7aa4

// ---------------------------------------------------------------------------
// eastl string / cString
// ---------------------------------------------------------------------------
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; void* mAlloc;  // 0x10
    WString* assign(const wchar_t* first, const wchar_t* last);            // 0x00423650
};

struct cString {
    uint32_t mData[5];
    cString();                                                             // 0x006b5060
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* source); // 0x006b5770
    ~cString();                                                            // 0x006b5240
    const wchar_t* GetText() const;                                        // 0x006b55c0
    bool Load(uint32_t tableID, uint32_t instanceID, int flag);            // 0x006b54b0
};

// ---------------------------------------------------------------------------
// 0x1ac-byte verb record held by the +0x64 vector
// ---------------------------------------------------------------------------
struct Rec1ac {
    uint8_t mFlag;      // +0x00
    uint8_t mPad01[0x24 - 1];
    int     mType;      // +0x24
    int     mId28;      // +0x28
    int     mId2c;      // +0x2c
    uint8_t mPad30[0x1ac - 0x30];
};

struct Rec44Name {                                  // the +4 sub-object of a 0x44 record
    const wchar_t* Get();                           // 0x00f26360
};

// ---------------------------------------------------------------------------
// helper object reached through g74
// ---------------------------------------------------------------------------
struct Vec {
    void** mpBegin; void** mpEnd; void** mpCapacity;   // 0xc
    Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec();                                            // 0x00ae6970
};

struct G74 {
    void  Fill(int arg, Vec* out);            // 0x00f40d00 thiscall 2
    void* Lookup(int arg);                    // 0x00f3e8a0 thiscall 1
    bool  Test(void* p);                      // 0x00f25670 thiscall 0
    bool  Query3(void* a, int b, void* c);    // 0x00f41dc0 thiscall 3
    bool  Cmp2(void* a, void* b);             // 0x00f3b3b0 thiscall 2
    bool  Find(int a, int b, int c, void* d, void* e);  // 0x00f420d0 thiscall 5
};

struct Combatant {
    int GetDamageState();                     // 0x008e7f80 thiscall 0
};

struct QueryObj {                             // object with a virtual query at vtable[3]
    void* Query(int id);                      // vtable offset 0xc
};

struct RefObj {                               // object released through vtable[1]
    void Release();                           // vtable offset 0x4
};

struct Creature {
    int   Count();                            // 0x00c0f780 thiscall 0
    void* At(int i);                          // 0x00c0f8a0 thiscall 1
    int   Next(int i);                        // 0x00c0f810 thiscall 1
};

struct AudioSystem {
    void Set1(int id);                        // vtable offset 0x38
    void Set2();                              // vtable offset 0x58
};

struct CreatureBase {
    void Show();                              // 0x00c0f2b0
    int  Count2();                            // 0x00c0f4f0
    void* At(int i);                          // 0x00c0f8a0
    void* GetTargetAsCreature();              // 0x00c0ee70
};

struct NounManager {
    void* GetAvatar();                        // 0x00b1fdb0 thiscall 0
};

// ---------------------------------------------------------------------------
// SP::cSPEditorVerbTray
// ---------------------------------------------------------------------------
struct cSPEditorVerbTray {
    uint8_t mPad00[0x54];
    WString mText54;        // +0x54
    Rec1ac* mBegin64;       // +0x64
    Rec1ac* mEnd68;         // +0x68
    uint8_t mPad6c[0x90 - 0x6c];
    int     mField90;       // +0x90
    uint8_t mPad94[0xb0 - 0x94];
    int     mFieldB0;       // +0xb0
    uint8_t mPadB4[0xb8 - 0xb4];
    int     mFieldB8;       // +0xb8
    uint8_t mPadBc[0xc8 - 0xbc];
    int     mFieldC8;       // +0xc8
    void*   mFieldCc;       // +0xcc
    uint8_t mPadD0[0xd4 - 0xd0];
    int     mFieldD4;       // +0xd4

    void GetName(int index, WString* out);                                  // 0x00f1bcf0
    void Refresh(void* pSel, void* target);                                 // 0x00f1be10
    int  FindPair(int a, int b, char c, int* out1, int* out2);              // 0x00f1c030
    void Toggle();                                                          // 0x00f1c2f0
    bool Step();                                                            // 0x00f1c4b0

    void Sub1ae10(int a, int b, int c);                                     // 0x00f1ae10
    void Sub1aae0(int a);                                                   // 0x00f1aae0
    void Sub1b730(int a, void* b, int c);                                   // 0x00f1b730
};

// ===========================================================================
// 0x00f1bcf0 -- label for verb icon #index: format the record's name (or the
// default), then assign it into *out.
// ===========================================================================
// @ 0x00f1bcf0
void cSPEditorVerbTray::GetName(int index, WString* out)
{
    void* g = *(void**)&g_16c7aa4;
    int v = (int)FUN_00f264d0(*(int*)(*(int*)((char*)g + 0x74) + 0x10),
                         mFieldB8,
                         *(int*)((char*)mFieldCc + 0x1c));
    cString cs(0x21851ebe, 0x75f8fc0, 0);

    if (index < (*(int*)(v + 0x1c) - *(int*)(v + 0x18)) / 0x44) {
        char* rec = (char*)*(void**)(v + 0x18) + index * 0x44;
        const wchar_t* name = ((Rec44Name*)(rec + 4))->Get();
        out->assign(name, wend(name));
        if (out->mpEnd != out->mpBegin)
            return;
        const wchar_t* t = cs.GetText();
        out->assign(t, wend(t));
    } else {
        const wchar_t* t = cs.GetText();
        out->assign(t, wend(t));
    }
}

// ===========================================================================
// 0x00f1be10 -- after the selection changes, walk the records and refresh the
// matching ones (and the label text when a pair matches).
// ===========================================================================
// @ 0x00f1be10
void cSPEditorVerbTray::Refresh(void* pSel, void* target)
{
    if (mField90 != 3)
        return;
    int sel = *(int*)((char*)pSel + 0x1c);
    if (sel == -1)
        return;
    Rec1ac* e = mEnd68;
    Rec1ac* p = mBegin64;
    if (p == e)
        return;

    do {
        if (p->mFlag == 0) {
            switch (p->mType) {
            case 1:
            case 7:
                if (p->mId28 == sel && target != 0 && ((*(uint32_t*)((char*)target + 0xb58) >> 9) & 1))
                    Sub1ae10((int)p, 0, 0);
                break;
            case 6:
            case 10: {
                int other;
                if (p->mId28 == sel)
                    other = p->mId2c;
                else if (p->mId2c == sel)
                    other = p->mId28;
                else
                    break;

                bool bl = (*(int*)((char*)target + 0x1c) == other);
                Creature* cr = (Creature*)target;
                for (int i = cr->Count(); i != -1; i = cr->Next(i)) {
                    if (bl)
                        break;
                    bl = false;
                    void* obj = cr->At(i);
                    if (obj) {
                        void* res = ((FnPI)(*(void***)obj)[0xc / 4])(obj, 0x17f243b);
                        if (res && *(int*)((char*)res + 0x1c) == other)
                            bl = true;
                    }
                }
                if (!bl)
                    break;

                if (p->mType == 6) {
                    Sub1ae10((int)p, 0, 0);
                } else {
                    void* g = *(void**)&g_16c7aa4;
                    void* reg = *(void**)((char*)g + 0x7c);
                    if (reg)
                        *(int*)((char*)reg + 0xc) = (int)(((char*)p - (char*)mBegin64) / 0x1ac);
                    cString cs;
                    uint32_t nameId = (p->mType == 10) ? 0x796cfe1
                                    : (p->mType == 0xb)  ? 0x796cfe5 : 0x796d59a;
                    cs.Load(0x21851ebe, nameId, 0);
                    const wchar_t* t = cs.GetText();
                    mText54.assign(t, wend(t));
                    mFieldB0 = 2;
                    Sub1aae0(6);
                }
                break;
            }
            default:
                break;
            }
        }
        p = (Rec1ac*)((char*)p + 0x1ac);
    } while (p != e);
}

// ===========================================================================
// 0x00f1c030 -- find a pair (a in list A, b in list B) whose verb icons are
// compatible; on success write the pair to *out1/*out2.
// ===========================================================================
// @ 0x00f1c030
int cSPEditorVerbTray::FindPair(int a, int b, char c, int* out1, int* out2)
{
    void* g = *(void**)&g_16c7aa4;
    G74* g74 = (G74*)*(void**)((char*)g + 0x74);

    Vec v1; Vec v2;
    g74->Fill(a, &v1);
    g74->Fill(b, &v2);

    int n1 = (int)((char*)v1.mpEnd - (char*)v1.mpBegin) >> 2;
    int n2 = (int)((char*)v2.mpEnd - (char*)v2.mpBegin) >> 2;

    if (n1 > 0 && n2 > 0) {
        bool f1 = false;
        {
            void* p = g74->Lookup(a);
            bool bl = false;
            if (p) {
                if (g74->Test(p) && *(char*)(mFieldB8 * 0x4e0 + 2 + *(int*)((char*)p + 0x70)) != 0)
                    bl = true;
            }
            f1 = (c != 0) && bl;
        }
        bool f2 = false;
        {
            void* p = g74->Lookup(b);
            bool bl = false;
            if (p) {
                if (g74->Test(p) && *(char*)(mFieldB8 * 0x4e0 + 2 + *(int*)((char*)p + 0x70)) != 0)
                    bl = true;
            }
            f2 = (c != 0) && bl;
        }

        for (int i = 0; i < n1; ++i) {
            void* o1 = v1.mpBegin[i];
            if (!o1)
                continue;
            void* q1 = ((FnPI)(*(void***)o1)[0xc / 4])(o1, 0x13f94d4);
            if (q1 && ((Combatant*)q1)->GetDamageState() == 2 && f1)
                continue;
            void* r1 = ((FnPI)(*(void***)o1)[0xc / 4])(o1, 0x1186577);
            if (!r1)
                continue;
            for (int j = 0; j < n2; ++j) {
                void* o2 = v2.mpBegin[j];
                if (o1 == o2 || !o2)
                    continue;
                void* q2 = ((FnPI)(*(void***)o2)[0xc / 4])(o2, 0x13f94d4);
                if (q2 && ((Combatant*)q2)->GetDamageState() == 2 && f2)
                    continue;
                void* r2 = ((FnPI)(*(void***)o2)[0xc / 4])(o2, 0x1186577);
                if (!r2)
                    continue;
                if (FUN_00f3c870(r1, r2, *(float*)0x15ad944, 0)) {
                    if (out1)
                        *out1 = (int)r1;
                    if (out2)
                        *out2 = (int)r2;
                    v2.~Vec();
                    v1.~Vec();
                    return 1;
                }
            }
        }
    }

    for (void** p = v2.mpBegin; p < v2.mpEnd; ++p)
        if (*p)
            ((FnV)(*(void***)*p)[0x4 / 4])(*p);
    if (v2.mpBegin && ((int*)v2.mpBegin)[-1] != 0)
        operator_delete(v2.mpBegin);
    for (void** p = v1.mpBegin; p < v1.mpEnd; ++p)
        if (*p)
            ((FnV)(*(void***)*p)[0x4 / 4])(*p);
    if (v1.mpBegin && ((int*)v1.mpBegin)[-1] != 0)
        operator_delete(v1.mpBegin);
    return 0;
}

// ===========================================================================
// 0x00f1c2f0 -- show the avatar's verb icons and clear the creature's target.
// ===========================================================================
// @ 0x00f1c2f0
void cSPEditorVerbTray::Toggle()
{
    void* audio = EA_GetSystemAT();
    if (audio) {
        ((FnVI)(*(void***)audio)[0x38 / 4])(audio, 0x7f43dd0);
        ((FnV)(*(void***)audio)[0x58 / 4])(audio);
    }

    void* pcc = mFieldCc;
    int arg;
    if (pcc != 0)
        arg = (int)((FnPI)(*(void***)pcc)[0xc / 4])(pcc, 0x1186577);
    else
        arg = 0;
    Sub1ae10(mFieldC8, arg, 0);

    void* avatar = ((NounManager*)SP_NounManager())->GetAvatar();
    void* cr;
    if (avatar != 0)
        cr = ((FnPI)(*(void***)avatar)[0xc / 4])(avatar, 0xce9f6639);
    else
        cr = 0;

    ((CreatureBase*)cr)->Show();

    int i = 0;
    int n = ((CreatureBase*)cr)->Count2();
    for (; i < n; ++i) {
        void* obj = ((CreatureBase*)cr)->At(i);
        if (!obj)
            continue;
        void* a = ((FnPI)(*(void***)obj)[0xb8 / 4])(obj, 0x3a25119);
        if (a) {
            ((FnVI)(*(void***)a)[0x60 / 4])(a, 1);
        } else {
            void* b = ((FnPI)(*(void***)obj)[0xb8 / 4])(obj, 0x17f243b);
            if (!b || *(int*)((char*)b + 0x14) == 0)
                continue;
            ((FnVI)(*(void***)*(void**)((char*)b + 0x14))[0x10 / 4])(*(void**)((char*)b + 0x14), 1);
        }
    }

    int cont = *(int*)((char*)cr + 0xb54);
    int tree = *(int*)((char*)cont + 0x17c);
    void** root = *(void***)((char*)tree + 0x17a4);
    void* node = *root;
    if (node == 0) {
        ++root;
        while (*root == 0)
            ++root;
        node = *root;
    }
    void* endNode = (*(void***)((char*)tree + 0x17a4))[*(int*)((char*)tree + 0x17a8)];
    while (node != endNode) {
        void* r = *(void**)(*(int*)((char*)node + 4) + 0x8c);
        if (r && ((FnC)(*(void***)r)[0x10 / 4])(r)) {
            ((FnVI)(*(void***)r)[0x2c / 4])(r, 0);
            ((FnVI)(*(void***)r)[0x30 / 4])(r, 0);
        }
        node = *(void**)((char*)node + 8);
        while (node == 0) { ++root; node = *root; }
    }

    void* tgt = ((CreatureBase*)cr)->GetTargetAsCreature();
    if (tgt)
        ((FnVIII)(*(void***)tgt)[0x84 / 4])(tgt, 0, 0, 0);
    ((FnVIII)(*(void***)cr)[0x84 / 4])(cr, 0, 0, 0);
}

// ===========================================================================
// 0x00f1c4b0 -- advance the scroll/selection and refresh the visible label.
// ===========================================================================
// @ 0x00f1c4b0
bool cSPEditorVerbTray::Step()
{
    void* g = *(void**)&g_16c7aa4;
    G74* g74 = (G74*)*(void**)((char*)g + 0x74);

    uint32_t n = (uint32_t)(((char*)mEnd68 - (char*)mBegin64) / 0x1ac);
    char found = 1;
    uint32_t count = 0;
    if (n != 0) {
        uint32_t off = 0;
        do {
            if (!found)
                return 0;
            Rec1ac* p = (Rec1ac*)((char*)mBegin64 + off);
            if (p->mFlag == 0) {
                if (!g74->Query3((char*)p + 0x24, mFieldB8, p)) {
                    int type = p->mType;
                    int t = 3;
                    if (type == 10 || type == 0xb)
                        t = 2;
                    Sub1b730((int)count, p, t);
                    found = 0;
                    goto next;
                }
            }
            /* LAB: */
            {
                if (count != 0) {
                    for (uint32_t j = 0; j < count; ++j) {
                        if (g74->Cmp2((char*)p + 0x24, (char*)((char*)mBegin64 + j * 0x1ac) + 0x24)) {
                            mFieldB0 = 4;
                            cString cs;
                            cs.Load(0x21851ebe, 0x7c50b5f, 0);
                            const wchar_t* t = cs.GetText();
                            mText54.assign(t, wend(t));
                            Sub1aae0(6);
                            found = 0;
                            goto next;
                        }
                    }
                }
            }
        next:
            off += 0x1ac;
            ++count;
        } while (count < n);
        if (!found)
            return 0;
    }

    if (g74->Find(mFieldB8, 0, -1, &n, &mBegin64)) {
        int idx = (int)n;
        Rec1ac* p = (Rec1ac*)((char*)mBegin64 + idx * 0x1ac);
        int type = p->mType;
        int t = 3;
        if (type == 10 || type == 0xb)
            t = 2;
        Sub1b730(idx, p, t);
        return 0;
    }
    return found;
}
