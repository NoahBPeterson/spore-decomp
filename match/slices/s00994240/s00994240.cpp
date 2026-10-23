// Slice s00994240 -- EA::UTFWinExtras::WinXHTML mouse / focus / DOM-event / document
// methods, plus the layout-refresh helper FUN_00994240 and FUN_00994c30.
// Object file: UTFSpore_Win32/XHTMLFrameSet.obj (closure).
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// ---- globals (address in the comment) ----
extern void* DAT_01550104;                                      // 0x1550104  (DOM attribute name)

// ---- callees: XHTML layout page, ecx = WinXHTML + 0x218 ----
struct XHTMLPage {
    void Layout();                                              // 0x8ec360
    unsigned char Pick(void* pt, void* out);                    // 0x8ec4f0
    void SetImageRequester(void* node, int kind);               // 0x8eb7e0
    void Resize(float w, float h);                              // 0x8ec8c0
    unsigned FUN_008ecc90(void* node);                          // 0x8ecc90
    void FUN_008edc30();                                        // 0x8edc30
    void FUN_008edc90(void* doc);                               // 0x8edc90
};

// ---- callees: DOM ----
struct DOMNode    { void* AsElement(); };                       // 0x8e52f0
struct DOMElement { void* GetAttrValue(void* key); };           // 0x8e45b0
struct DOMDocument {
    void DestroyFormControls();                                 // 0x8e2890
    void FUN_008e2870();                                        // 0x8e2870
};
struct DocX { unsigned char CheckFlag(unsigned char v); };      // 0x8e29e0

// 7-dword IWindow notification message (the first two dwords are unused).
struct WinMsg {
    void* r0;
    void* r1;
    int   code;
    int   f3;
    int   f4;
    int   f5;
    int   f6;
};

#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])

// ---- WinXHTML as seen from these methods ----
struct WinXHTML {
    void CalculateVisibleArea();        // 0x9940f0
    void FUN_00994240();                // 0x994240
    void FUN_00994c30(int);             // 0x994c30
    void FUN_00992ee0(void* a);         // 0x992ee0
    void FUN_00992e00(int lo, int hi);  // 0x992e00
    bool FUN_009948a0(float x, float y, int a);   // 0x9948a0
    bool OnFocusChange(int a, void* b);           // 0x9947f0
    bool OnMouseDown(float x, float y, int a, int b);  // 0x994a40
    void SetDocument(void* doc);                  // 0x994b00
};

// The IWindow-event handler is a member of the sub-object at WinXHTML + 0x210.
struct WinXHTMLCmd {
    void OnDOMEvent(void* param_2);     // 0x9946b0
};

// @ 0x00994240
void WinXHTML::FUN_00994240()
{
    char* self = (char*)this;
    bool flag1;
    bool flag2;
    float saved[4];

    saved[0] = *(float*)(self + 0xa878);
    saved[1] = *(float*)(self + 0xa87c);
    saved[2] = *(float*)(self + 0xa880);
    saved[3] = *(float*)(self + 0xa884);
    CalculateVisibleArea();
    if (*(float*)(self + 0xa878) != saved[0] || *(float*)(self + 0xa87c) != saved[1]
        || *(float*)(self + 0xa880) != saved[2] || *(float*)(self + 0xa884) != saved[3])
        ((XHTMLPage*)(self + 0x218))->Resize(*(float*)(self + 0xa880) - *(float*)(self + 0xa878),
                                             *(float*)(self + 0xa884) - *(float*)(self + 0xa87c));

    saved[0] = *(float*)(self + 0xa878);
    saved[1] = *(float*)(self + 0xa87c);
    saved[2] = *(float*)(self + 0xa880);
    saved[3] = *(float*)(self + 0xa884);
    if (*(int*)(self + 0xa8a8) == 2)
        flag1 = 1;
    else if (*(int*)(self + 0xa8a8) == 1
             && (float)*(int*)(self + 0x250) > *(float*)(self + 0xa884) - *(float*)(self + 0xa87c))
        flag1 = 1;
    else
        flag1 = 0;
    if (*(void**)(self + 0xa8a0) != 0) {
        void* sb = *(void**)(self + 0xa8a0);
        void* w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(w, 0x7c, void(__thiscall*)(void*, int, int))(w, 1, flag1);
    }

    CalculateVisibleArea();
    if (*(float*)(self + 0xa878) != saved[0] || *(float*)(self + 0xa87c) != saved[1]
        || *(float*)(self + 0xa880) != saved[2] || *(float*)(self + 0xa884) != saved[3])
        ((XHTMLPage*)(self + 0x218))->Resize(*(float*)(self + 0xa880) - *(float*)(self + 0xa878),
                                             *(float*)(self + 0xa884) - *(float*)(self + 0xa87c));

    if (*(int*)(self + 0xa894) == 2)
        flag2 = 1;
    else if (*(int*)(self + 0xa894) == 1
             && (float)*(int*)(self + 0x24c) > *(float*)(self + 0xa880) - *(float*)(self + 0xa878))
        flag2 = 1;
    else
        flag2 = 0;
    if (*(void**)(self + 0xa88c) != 0) {
        void* sb = *(void**)(self + 0xa88c);
        void* w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(w, 0x7c, void(__thiscall*)(void*, int, int))(w, 1, flag2);
    }

    CalculateVisibleArea();
    if (*(void**)(self + 0xa8a0) != 0) {
        saved[0] = (*(float*)(self + 0x90) - *(float*)(self + 0x88)) - *(float*)(self + 0xa8ac);
        saved[1] = 0.0f;
        saved[2] = *(float*)(self + 0x90) - *(float*)(self + 0x88);
        saved[3] = *(float*)(self + 0x94) - *(float*)(self + 0x8c);
        if (flag2 != 0)
            saved[3] = saved[3] - *(float*)(self + 0xa89c);
        void* sb = *(void**)(self + 0xa8a0);
        void* w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(w, 0x60, void(__thiscall*)(void*, void*))(w, saved);
        sb = *(void**)(self + 0xa8a0);
        VF(sb, 0x34, void(__thiscall*)(void*, int, int))(sb, (int)(float)*(int*)(self + 0x250), 1);
        sb = *(void**)(self + 0xa8a0);
        VF(sb, 0x3c, void(__thiscall*)(void*, int, int))(
            sb, (int)(*(float*)(self + 0xa884) - *(float*)(self + 0xa87c)), 1);
        sb = *(void**)(self + 0xa8a0);
        VF(sb, 0x4c, void(__thiscall*)(void*, int))(sb, 0x10);
        sb = *(void**)(self + 0xa8a0);
        w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        if (VF(w, 0x100, unsigned char(__thiscall*)(void*, int))(w, 1) == 0) {
            sb = *(void**)(self + 0xa8a0);
            VF(sb, 0x24, void(__thiscall*)(void*, int, int))(sb, (int)*(float*)(self + 0xa8b8), 0);
        }
    }

    if (*(void**)(self + 0xa88c) != 0) {
        saved[0] = 0.0f;
        saved[1] = (*(float*)(self + 0x94) - *(float*)(self + 0x8c)) - *(float*)(self + 0xa89c);
        saved[2] = *(float*)(self + 0x90) - *(float*)(self + 0x88);
        saved[3] = *(float*)(self + 0x94) - *(float*)(self + 0x8c);
        if (flag1 != 0)
            saved[2] = saved[2] - *(float*)(self + 0xa8ac);
        void* sb = *(void**)(self + 0xa88c);
        void* w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        VF(w, 0x60, void(__thiscall*)(void*, void*))(w, saved);
        sb = *(void**)(self + 0xa88c);
        VF(sb, 0x34, void(__thiscall*)(void*, int, int))(sb, (int)(float)*(int*)(self + 0x24c), 1);
        sb = *(void**)(self + 0xa88c);
        VF(sb, 0x3c, void(__thiscall*)(void*, int, int))(
            sb, (int)(*(float*)(self + 0xa880) - *(float*)(self + 0xa878)), 1);
        sb = *(void**)(self + 0xa88c);
        VF(sb, 0x4c, void(__thiscall*)(void*, int))(sb, 0x10);
        sb = *(void**)(self + 0xa88c);
        w = VF(sb, 0x10, void*(__thiscall*)(void*))(sb);
        if (VF(w, 0x100, unsigned char(__thiscall*)(void*, int))(w, 1) == 0) {
            sb = *(void**)(self + 0xa88c);
            VF(sb, 0x24, void(__thiscall*)(void*, int, int))(sb, (int)*(float*)(self + 0xa8b4), 0);
        }
    }
}

// @ 0x009946b0
void WinXHTMLCmd::OnDOMEvent(void* param_2)
{
    char* self = (char*)this;      // WinXHTML base + 0x210
    int*  p = (int*)param_2;

    if (p[1] == 4) {
        char* win = self - 0x20c;
        void* (__thiscall* fn1)(void*) =
            *(void*(__thiscall**)(void*))((char*)*(void**)win + 0x20);
        WinMsg m;
        m.code = 0x3326e8b;
        m.f3 = (int)fn1(win);
        m.f6 = p[0];
        void (__thiscall* fn2)(void*, void*) =
            *(void(__thiscall**)(void*, void*))((char*)*(void**)win + 0x114);
        m.f4 = 0;
        m.f5 = 0;
        fn2(win, &m);
        return;
    }
    if (p[1] == 6) {
        void* doc = *(void**)(self + 0x2c);
        if (doc != 0) {
            if (((DocX*)doc)->CheckFlag(1) == 0) {
                if (*(int*)(self + 0x44) == 0)
                    ((XHTMLPage*)(self + 8))->FUN_008edc30();
                ((XHTMLPage*)(self + 8))->Layout();
                ((WinXHTML*)(self - 0x210))->FUN_00994240();
                char* win = self - 0x20c;
                void (__thiscall* fn)(void*) =
                    *(void(__thiscall**)(void*))((char*)*(void**)win + 0x90);
                fn(win);
            }
            if (((DocX*)doc)->CheckFlag(0) == 0) {
                char* win = self - 0x20c;
                void (__thiscall* fn)(void*, void*) =
                    *(void(__thiscall**)(void*, void*))((char*)*(void**)win + 0x114);
                WinMsg m;
                m.code = 0x51a1a2d;
                m.f3 = 0;
                m.f4 = 0;
                m.f5 = 0;
                m.f6 = (int)doc;
                fn(win, &m);
            }
        }
    }
}

// @ 0x009947f0
bool WinXHTML::OnFocusChange(int param_2, void* param_3)
{
    char* self = (char*)this;

    if (param_2 != 1)
        return true;
    if (param_3 == (self != 0 ? (void*)(self + 4) : 0))
        return true;
    if (*(char*)(self + 0xa8e4) != 0) {
        void* w = (void*)(self + 4);
        void (__thiscall* fn)(void*, void*) =
            *(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x114);
        WinMsg m;
        m.code = 0x51a1a2e;
        m.f3 = 0;
        m.f4 = 0;
        m.f5 = 0;
        m.f6 = 0;
        fn(w, &m);
        *(char*)(self + 0xa8e4) = 0;
    }
    if (*(void**)(self + 0x478) != 0) {
        ((XHTMLPage*)(self + 0x218))->SetImageRequester(0, 0);
        ((XHTMLPage*)(self + 0x218))->FUN_008ecc90(0);
        ((XHTMLPage*)(self + 0x218))->Layout();
        FUN_00994240();
    }
    VF(self + 4, 0x90, void(__thiscall*)(void*))(self + 4);
    return true;
}

// @ 0x009948a0
bool WinXHTML::FUN_009948a0(float param_2, float param_3, int)
{
    char* self = (char*)this;
    float pt[2];
    int   hit[7];

    pt[0] = *(float*)(self + 0xa8b4) + param_2;
    int target = *(int*)(self + 0xa8dc);
    pt[1] = *(float*)(self + 0xa8b8) + param_3;
    unsigned char ok = ((XHTMLPage*)(self + 0x218))->Pick(pt, hit);
    if (ok != 0) {
        if (hit[4] != 0)
            target = hit[4];
        else if (hit[1] != 0)
            target = *(int*)(self + 0xa8e0);
    }
    VF(self + 4, 0x78, void(__thiscall*)(void*, int))(self + 4, target);
    unsigned& rng = *(unsigned*)(self + 0xa850);
    rng = (unsigned)hit[6];
    if (hit[0] != 0 && *(void**)(self + 0x47c) != (void*)hit[0]) {
        void* elem = ((DOMNode*)(void*)hit[0])->AsElement();
        if (elem != 0) {
            void* title = ((DOMElement*)elem)->GetAttrValue(DAT_01550104);
            FUN_00992ee0(title);
        } else if (*(char*)(self + 0xa8e4) != 0) {
            void* w = (void*)(self + 4);
            void (__thiscall* fn)(void*, void*) =
                *(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x114);
            WinMsg m;
            m.code = 0x51a1a2e;
            m.f3 = 0;
            m.f4 = 0;
            m.f5 = 0;
            m.f6 = 0;
            fn(w, &m);
            *(char*)(self + 0xa8e4) = 0;
        }
    }
    unsigned char changed = ((XHTMLPage*)(self + 0x218))->FUN_008ecc90((void*)hit[0]);
    if (*(int*)(self + 0xa860) == 2) {
        if (hit[1] != *(int*)(self + 0x478)) {
            ((XHTMLPage*)(self + 0x218))->SetImageRequester((void*)hit[1], 2);
            goto laidout;
        }
    } else if (*(int*)(self + 0xa860) == 0) {
        if (hit[1] != *(int*)(self + 0x478)) {
            ((XHTMLPage*)(self + 0x218))->SetImageRequester((void*)hit[1], 4);
            goto laidout;
        }
    } else {
        unsigned& a = *(unsigned*)(self + 0xa854);
        FUN_00992e00((a < rng) ? a : rng, (rng < a) ? rng : a);
    }
    if (changed == 0)
        return true;
laidout:
    ((XHTMLPage*)(self + 0x218))->Layout();
    FUN_00994240();
    VF(self + 4, 0x90, void(__thiscall*)(void*))(self + 4);
    return true;
}

// @ 0x00994a40
bool WinXHTML::OnMouseDown(float param_2, float param_3, int, int param_5)
{
    char* self = (char*)this;

    if (param_5 == 8) {
        VF(self, 0x44, void(__thiscall*)(void*, float, float, int))(self, param_2, param_3, 8);
        void* o = *(void**)(self + 0x34);
        VF(o, 0x58, void(__thiscall*)(void*, int, void*))(o, 1, self + 4);
        if (*(void**)(self + 0x478) != 0) {
            *(int*)(self + 0xa860) = 2;
            ((XHTMLPage*)(self + 0x218))->SetImageRequester(*(void**)(self + 0x478), 2);
            ((XHTMLPage*)(self + 0x218))->Layout();
            FUN_00994240();
            VF(self + 4, 0x90, void(__thiscall*)(void*))(self + 4);
            return true;
        }
        if ((*(unsigned char*)(self + 0xa84c) & 1) != 0) {
            FUN_00992e00(0, 0);
            *(int*)(self + 0xa854) = *(int*)(self + 0xa850);
            *(int*)(self + 0xa860) = 1;
        }
        return true;
    }
    return false;
}

// @ 0x00994b00
void WinXHTML::SetDocument(void* param_2)
{
    char* self = (char*)this;
    void* doc = *(void**)(self + 0x23c);

    if (doc != 0) {
        ((DOMDocument*)doc)->DestroyFormControls();
        *(int*)((char*)doc + 0x38) = 0;
        *(int*)((char*)doc + 0x3c) = 0;
    }
    if (*(char*)(self + 0xa8e4) != 0) {
        void* w = (void*)(self + 4);
        void (__thiscall* fn)(void*, void*) =
            *(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x114);
        WinMsg m;
        m.code = 0x51a1a2e;
        m.f3 = 0;
        m.f4 = 0;
        m.f5 = 0;
        m.f6 = 0;
        fn(w, &m);
        *(char*)(self + 0xa8e4) = 0;
    }
    ((XHTMLPage*)(self + 0x218))->FUN_008edc90(param_2);
    if (param_2 != 0) {
        *(int*)((char*)param_2 + 0x38) = (int)(self + 0x20c);
        *(int*)((char*)param_2 + 0x3c) = (int)(self + 0x210);
        ((DOMDocument*)param_2)->FUN_008e2870();
    }
    ((XHTMLPage*)(self + 0x218))->Resize(*(float*)(self + 0xa880) - *(float*)(self + 0xa878),
                                         *(float*)(self + 0xa884) - *(float*)(self + 0xa87c));
    if (((DocX*)param_2)->CheckFlag(1) == 0) {
        ((XHTMLPage*)(self + 0x218))->Layout();
        FUN_00994240();
        VF(self + 4, 0x90, void(__thiscall*)(void*))(self + 4);
    }
    if (((DocX*)param_2)->CheckFlag(0) == 0) {
        void* w = (void*)(self + 4);
        void (__thiscall* fn)(void*, void*) =
            *(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x114);
        WinMsg m;
        m.code = 0x51a1a2d;
        m.f3 = 0;
        m.f4 = 0;
        m.f5 = 0;
        m.f6 = (int)param_2;
        fn(w, &m);
    }
}

// @ 0x00994c30
void WinXHTML::FUN_00994c30(int)
{
    char* self = (char*)this;

    FUN_00994240();
    ((XHTMLPage*)(self + 0x218))->Resize(*(float*)(self + 0xa880) - *(float*)(self + 0xa878),
                                         *(float*)(self + 0xa884) - *(float*)(self + 0xa87c));
}
