// Slice s00ed1880 -- Simulator scenario "avatar palette" UI glue.
//
// Function pointers and object accesses below are transcribed from the retail disassembly; the
// intrusive reference counting (vtable slot 0 = AddRef, slot 1 = Release, slot 2 = a second
// Release variant, slot 3 = QueryInterface) is preserved exactly because it is visible in the
// instruction stream.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (module built with SSE scalar instructions).
#include "types.h"

typedef void* (__thiscall* FV_v)(void*);
typedef void* (__thiscall* FV_i)(void*, int);
typedef void* (__thiscall* FV_ii)(void*, int, int);
typedef void* (__thiscall* FV_p)(void*, void*);
typedef void* (__thiscall* FV_vi)(void*, int);
typedef void* (__thiscall* FV_vp)(void*, void*);
typedef void* (__thiscall* FV_fff)(void*, void*, void*);

// ---------------------------------------------------------------- imported callees
void* __cdecl EAAllocate(unsigned size, const char* name, int, int, int, int);  // 0xf473a0
void* __cdecl FUN_005c66a0(void);                                  // 0x005c66a0
void* __cdecl FUN_005c64e0(void);                                  // 0x005c64e0
void* __cdecl FUN_005c6710(void*);                                 // 0x005c6710
void* __cdecl FUN_009512c0(void);                                  // 0x009512c0
void* __cdecl FUN_009512d0(int, int, const char*, void*);          // 0x009512d0
void* __cdecl FUN_00ed1250(void*);                                 // 0x00ed1250
void* __cdecl FUN_00ed1120(void*, void*, void*, int, int, int, int); // 0x00ed1120
void* __cdecl FUN_00ed0c30(void*);                                 // 0x00ed0c30
void* __cdecl FUN_00ed1180(void*, void*);                          // 0x00ed1180
void* __cdecl FUN_00ece870(void*, void*);                          // 0x00ece870
void* __cdecl FUN_00572620(void*, void*);                          // 0x00572620
void* __cdecl FUN_005cae30(void*, int);                            // 0x005cae30 GetSubCategory
void* __cdecl FUN_005c2e50(void*, int);                            // 0x005c2e50 GetPageUI
char  FUN_00ecdb80(void*);                                        // 0x00ecdb80 (thiscall)
void* __cdecl FUN_0067dcc0(void*, void*, int);                     // 0x0067dcc0 SP::MessageServer
struct Container;
void* __cdecl FUN_004db620(void*, void*, void*, int);              // 0x004db620 Connector::Init
void* __cdecl FUN_005f2290(int);                                   // 0x005f2290
void* __cdecl FUN_0092a7a0(void*, int);                            // 0x0092a7a0 Schedule
void* __cdecl FUN_00929c60(void*);                                 // 0x00929c60 Cancel
void* __cdecl FUN_00571db0(void*, void*, void*, void*, void*);     // 0x00571db0 RemoveHandler
void* __cdecl FUN_005cb180(void*, char);                           // 0x005cb180 SetVisible
void* __cdecl FUN_00ecf150(void*);                                 // 0x00ecf150
void* __cdecl FUN_00ece990(void*);                                 // 0x00ece990
int   FUN_007f54d0(void*);                                        // 0x007f54d0 (thiscall) GetAllocator
void* __cdecl FUN_005c6810(void*, int*, int, int);                 // 0x005c6810 cSPPaletteItem::Init
void* __cdecl FUN_00805070(int);                                   // 0x00805070 GetLayoutManager
void* __cdecl FUN_00810620(void*);                                 // 0x00810620 GetWorldMainWindow
void* __cdecl FUN_00962a10(void*);                                 // 0x00962a10 Window::Window

struct Container;

// 0x14-byte swatch record.
struct Entry {
    void* a;         // +0x00
    void* b;         // +0x04
    int   cat;       // +0x08
    int   page;      // +0x0c
    int   sub;       // +0x10
};

struct Container {
    char   pad00[8];
    int    f08;                 // +0x08
    int    pad0c;
    void*  hA;                  // +0x10  handle
    void*  hB;                  // +0x14  handle
    void*  hItemUI;             // +0x18  handle
    char   pad1c[4];
    char   conn[0x38 - 0x20];
    void*  hAvatarUI;           // +0x38
    int    pad3c;
    void*  hPaletteCatUI;       // +0x40  QueryInterface 0x52deed23
    int    pad44;
    char   f48;                 // +0x48  visible flag
    char   pad49[3];
    int    notifier;            // +0x4c
    char   pad50[8];
    int    callback;            // +0x58
    Entry* vec0;                // +0x5c
    Entry* vec0End;             // +0x60
    char   pad64[0x0c];
    Entry* vec1;                // +0x70
    Entry* vec1End;             // +0x74
};

// ===========================================================================
// @ 0x00ed1cf0
// ===========================================================================
void __cdecl FUN_00ed1cf0(char* p, int a, int b)
{
    if (p != 0) {
        char* t = *(char**)(p + 0x24);
        if (t != 0) {
            void* f = *(void**)(p + 0x28);
            if (f != 0)
                ((void(__thiscall*)(void*, int, int))f)(*(char**)(p + 0x2c) + (int)t, a, b);
        }
    }
}

// ===========================================================================
// @ 0x00ed1d70
// ===========================================================================
void* __stdcall FUN_00ed1d70(int a, void* spec)
{
    void* p;
    if (spec == 0)
        spec = FUN_009512c0();
    p = FUN_009512d0(0xa0, 8, "UTFWin/cSPScenarioSwatchEditItemUI", spec);
    if (p != 0) {
        p = FUN_00ecf150(p);
        if (p != 0) {
            p = ((FV_i)(*(void***)((char*)p + 8))[0xc / 4])((char*)p + 8, 0x4785a3d);
            if (p != 0)
                return (char*)p + 0xc;
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00ed1dc0
// ===========================================================================
void* __stdcall FUN_00ed1dc0(int a, void* spec)
{
    void* p = EAAllocate(0x6c, "UI/cSPScenarioSwatchItemUI", 0, 0, 0, 0);
    if (p != 0) {
        p = FUN_00ece990(p);
        if (p != 0) {
            p = ((FV_i)(*(void***)((char*)p + 8))[0xc / 4])((char*)p + 8, 0x4785a3d);
            if (p != 0)
                return (char*)p + 0xc;
        }
    }
    (void)a;
    return 0;
}

// ===========================================================================
// @ 0x00ed1e10
// ===========================================================================
int __fastcall FUN_00ed1e10(Container* self, int* unused, int param)
{
    int   i;
    void* p;
    void* cat;

    p = self->hPaletteCatUI;
    if (p == 0)
        cat = 0;
    else
        cat = ((FV_i)(*(void***)p)[0xc / 4])(p, 0x52deed23);

    i = 0;
    if ((*(int*)((char*)cat + 0x38) - *(int*)((char*)cat + 0x34) & -4) > 0) {
        do {
            if (param == (int)((void*(__thiscall*)(void*, int))FUN_005cae30)(cat, i))
                return i;
            ++i;
        } while (i < (*(int*)((char*)cat + 0x38) - *(int*)((char*)cat + 0x34)) >> 2);
    }
    (void)unused;
    return -1;
}

// ===========================================================================
// @ 0x00ed1e70
// ===========================================================================
int __fastcall FUN_00ed1e70(Container* self, int* unused, int key, int arg)
{
    Entry* e = self->vec0;
    Entry* end = self->vec0End;
    int    count = 0;

    if (key == 7) {
        e = self->vec1;
        end = self->vec1End;
    }
    for (; e != end; ++e) {
        if (e->cat == key && e->page == arg && ((char(__thiscall*)(void*))FUN_00ecdb80)(e->a) == 0)
            ++count;
    }
    (void)unused;
    return count;
}

// ===========================================================================
// @ 0x00ed1ec0
// ===========================================================================
void __fastcall FUN_00ed1ec0(Container* self)
{
    Entry** v[2];
    unsigned i;

    v[0] = &self->vec0;
    v[1] = &self->vec1;
    for (i = 0; i < 2; ++i) {
        Entry** tab = (Entry**)v[i];
        Entry* e = tab[0];
        Entry* end = tab[1];
        for (; e < end; ++e)
            ((FV_v)(*(void***)e->a)[0x20 / 4])(e->a);
    }
}

// ===========================================================================
// @ 0x00ed1f00
// ===========================================================================
void* __stdcall FUN_00ed1f00(Entry** tab, int alloc)
{
    Entry* e = tab[0];
    Entry* end = tab[1];
    for (; e < end; ++e) {
        if (((int(__thiscall*)(void*))FUN_007f54d0)(e->a) == alloc)
            return e;
    }
    return 0;
}

// ===========================================================================
// @ 0x00ed1f40
// ===========================================================================
void* __stdcall FUN_00ed1f40(Entry** tab)
{
    Entry* e = tab[0];
    Entry* end = tab[1];
    for (; e < end; ++e) {
        if (((char(__thiscall*)(void*))FUN_00ecdb80)(e->a) != 0)
            return e;
    }
    return 0;
}

// ===========================================================================
// @ 0x00ed1f70
// ===========================================================================
void* __stdcall FUN_00ed1f70(Entry** tab, int key)
{
    Entry* e;
    Entry* end;

    if (key == (int)0xd37c1045)
        key = (int)0x5b3d1d0d;
    else if (key == (int)0xc7fdcb1e)
        key = (int)0x6031c03a;

    e = tab[0];
    end = tab[1];
    for (; e < end; ++e) {
        if ((int)((FV_v)(*(void***)e->a)[0x28 / 4])(e->a) == key && ((char(__thiscall*)(void*))FUN_00ecdb80)(e->a) != 0)
            return e;
    }
    return 0;
}

// ===========================================================================
// @ 0x00ed1fe0
// ===========================================================================
void __fastcall FUN_00ed1fe0(Container* self, int* unused, char show)
{
    int i;

    if (show == self->f48)
        return;

    if (self->hPaletteCatUI != 0)
        FUN_005cb180(
            ((FV_i)(*(void***)self->hPaletteCatUI)[0xc / 4])(self->hPaletteCatUI, 0x52deed23),
            show);
    else
        FUN_005cb180(0, show);

    if (show != 0) {
        char* base = (char*)self + 8;
        self->f08 = (int)FUN_0067dcc0(base, (void*)0x1489bd0, 0x0c);
        self->pad0c; // unused
        for (i = 0; i < 0x30; i += 4) {
            void* h = *(void**)(0x1489bd0 + i);
            if (self->f08 != 0 && base != 0)
                ((FV_fff)(*(void***)self->f08)[0x24 / 4])((void*)self->f08, base, h);
        }
        FUN_0092a7a0((void*)self->callback, 0);
        ((void(__thiscall*)(void*, int))FUN_00ed1180)((void*)self->notifier, (int)show);
        self->f48 = show;
    } else {
        if (self->pad0c == 0)
            ;
        if (self->f08 != 0) {
            int id = self->f08;
            self->f08 = 0;
            FUN_00571db0((void*)id, (void*)0, (void*)0x1489bd0, (void*)0x0c, 0);
        }
        FUN_00929c60((void*)self->callback);
        ((void(__thiscall*)(void*, int))FUN_00ed1180)((void*)self->notifier, (int)show);
        self->f48 = 0;
    }
}

// ===========================================================================
// @ 0x00ed20c0
// ===========================================================================
int __fastcall FUN_00ed20c0(Container* self, int* unused, int key)
{
    Entry* e;
    Entry* end;
    int    count = 0;

    if (key == (int)0xd37c1045)
        key = (int)0x5b3d1d0d;
    else if (key == (int)0xc7fdcb1e)
        key = (int)0x6031c03a;

    e = self->vec0;
    end = self->vec0End;
    for (; e != end; ++e) {
        if ((int)((FV_v)(*(void***)e->a)[0x28 / 4])(e->a) == key && ((char(__thiscall*)(void*))FUN_00ecdb80)(e->a) != 0)
            ++count;
    }
    (void)unused;
    return count;
}

// ===========================================================================
// @ 0x00ed2130
// ===========================================================================
void __stdcall FUN_00ed2130(void** slot, void* value)
{
    void* old;
    void* qi;
    void* made;

    if (value == 0) {
        if (*slot == 0)
            return;
        qi = ((FV_i)(*(void***)((char*)*slot + 8))[0xc / 4])((char*)*slot + 8, 0x722de52);
        if (qi == 0) {
            ((void(__thiscall*)(void**, void*))FUN_00572620)(slot, 0);
            return;
        }
        made = EAAllocate(0x24, "UI/cSPScenarioPaletteItemUIBase", 0, 0, 0, 0);
        if (made == 0) {
            ((void(__thiscall*)(void**, void*))FUN_00572620)(slot, 0);
            return;
        }
        ((void(__thiscall*)(void**, void*))FUN_00572620)(slot, FUN_00ece870(made, qi));
        return;
    }

    ((FV_p)(*(void***)value)[0x10 / 4])(value, *slot);
    old = *slot;
    if (value != old) {
        ((FV_v)(*(void***)value)[4 / 4])(value);
        *slot = value;
        if (old != 0)
            ((FV_v)(*(void***)old)[8 / 4])(old);
    }
}

// ===========================================================================
// @ 0x00ed2210
// ===========================================================================
void* __fastcall FUN_00ed2210(void** dst, void* unused, void* src)
{
    void* a = ((void**)src)[0];
    dst[0] = a;
    if (a != 0)
        ((FV_v)(*(void***)a)[4 / 4])(a);
    a = ((void**)src)[1];
    dst[1] = a;
    if (a != 0)
        ((FV_v)(*(void***)a)[8 / 4])(a);
    dst[2] = ((void**)src)[2];
    dst[3] = ((void**)src)[3];
    ((int*)dst)[4] = ((int*)src)[4];
    (void)unused;
    return dst;
}

// ===========================================================================
// @ 0x00ed2260
// ===========================================================================
void* __fastcall FUN_00ed2260(void** dst, void* unused, void** src)
{
    void* na;
    void* oa;
    void* nb;
    void* ob;

    na = src[0];
    oa = dst[0];
    if (na != oa) {
        if (na != 0)
            ((FV_v)(*(void***)na)[4 / 4])(na);
        dst[0] = na;
        if (oa != 0)
            ((FV_v)(*(void***)oa)[8 / 4])(oa);
    }
    nb = src[1];
    ob = dst[1];
    if (nb != ob) {
        if (nb != 0)
            ((FV_v)(*(void***)nb)[8 / 4])(nb);
        dst[1] = nb;
        if (ob != 0)
            ((FV_v)(*(void***)ob)[0xc / 4])(ob);
    }
    dst[2] = src[2];
    dst[3] = src[3];
    ((int*)dst)[4] = ((int*)src)[4];
    (void)unused;
    return dst;
}

// ===========================================================================
// @ 0x00ed22e0
// ===========================================================================
void* __cdecl FUN_00ed22e0(void* first, void* last, void* dst)
{
    for (; first != last; first = (char*)first + 0x14, dst = (char*)dst + 0x14) {
        if (dst != 0) {
            void* a;
            a = ((void**)first)[0];
            *(void**)dst = a;
            if (a != 0)
                ((FV_v)(*(void***)a)[4 / 4])(a);
            a = ((void**)first)[1];
            ((void**)dst)[1] = a;
            if (a != 0)
                ((FV_v)(*(void***)a)[8 / 4])(a);
            ((int*)dst)[2] = ((int*)first)[2];
            ((int*)dst)[3] = ((int*)first)[3];
            ((int*)dst)[4] = ((int*)first)[4];
        }
    }
    return dst;
}

// ===========================================================================
// @ 0x00ed2340
// ===========================================================================
void* __cdecl FUN_00ed2340(void* first, void* last, void* dst)
{
    for (; first != last; first = (char*)first + 0x14, dst = (char*)dst + 0x14) {
        void* a = ((void**)first)[1];
        if (a != 0)
            ((FV_v)(*(void***)a)[0xc / 4])(a);
        a = ((void**)first)[0];
        if (a != 0)
            ((FV_v)(*(void***)a)[8 / 4])(a);
    }
    return dst;
}

// ===========================================================================
// @ 0x00ed2410
// ===========================================================================
void __fastcall FUN_00ed2410(Container* self, int* unused, int param2, int param3, int param4)
{
    int   i, k, j;
    void* cat;
    int   n;
    int   keys[2];
    Entry** v[2];

    if (self->hPaletteCatUI == 0)
        cat = 0;
    else
        cat = ((FV_i)(*(void***)self->hPaletteCatUI)[0xc / 4])(self->hPaletteCatUI, 0x52deed23);

    n = (*(int*)((char*)cat + 0x38) - *(int*)((char*)cat + 0x34)) >> 2;
    for (i = 0; i < n; ++i)
        if (param2 == (int)FUN_005cae30(cat, i))
            break;
    if (i >= n)
        return;

    keys[0] = param3;
    keys[1] = param4;

    for (k = 0; k < 2; ++k) {
        int page = keys[k];
        void* pageUI;
        if (page < 0)
            continue;
        if (page >= (int)((*(int*)((char*)self + 0x8c) - *(int*)((char*)self + 0x88)) >> 3))
            continue;
        pageUI = FUN_005c2e50(self, page);

        v[0] = &self->vec0;
        v[1] = &self->vec1;
        for (j = 0; j < 2; ++j) {
            Entry** tab = (Entry**)v[j];
            Entry* e = tab[0];
            Entry* end = tab[1];
            for (; e < end; ++e) {
                if (e->cat != i || e->page != page)
                    continue;
                if (page == param4) {
                    if (e->a != 0) {
                        void* qi = ((FV_i)(*(void***)((char*)e->a + 8))[0xc / 4])(
                                        (char*)e->a + 8, 0x722de52);
                        if (qi != 0) {
                            void* made = EAAllocate(0x24, "UI/cSPScenarioPaletteItemUIBase",
                                                    0, 0, 0, 0);
                            if (made != 0)
                                made = FUN_00ece870(made, qi);
                            else
                                made = 0;
                            {
                                void* old = e->a;
                                if (made != old) {
                                    if (made != 0)
                                        ((FV_v)(*(void***)made)[4 / 4])(made);
                                    e->a = made;
                                    if (old != 0)
                                        ((FV_v)(*(void***)old)[8 / 4])(old);
                                }
                            }
                        }
                    }
                } else if (page == param3) {
                    void* sc = FUN_005cae30(pageUI, e->sub);
                    void* val = 0;
                    if (sc != 0)
                        val = ((FV_i)(*(void***)((char*)sc + 0xc))[0xc / 4])(
                                    (char*)sc + 0xc, 0x722de52);
                    FUN_00ed2130(&e->a, val);
                }
            }
        }
    }
}

// ===========================================================================
// @ 0x00ed1880  Container::Init(mainWindow)
// ===========================================================================
bool __fastcall FUN_00ed1880(Container* self, int* unused, void* arg)
{
    void*  mainWin;
    void*  item;
    void*  catDesc;
    void*  itemUI;
    void*  pageWin;
    void*  pageBase;
    float* r;
    float  w, h;

    // store arg into self->hB (slot 0 AddRef / slot 1 Release)
    {
        void* old = self->hB;
        if (arg != old) {
            if (arg != 0 && *(void***)arg != 0)
                ((FV_v)(*(void***)arg)[0])(arg);
            self->hB = arg;
            if (old != 0)
                ((FV_v)(*(void***)old)[4 / 4])(old);
        }
    }

    mainWin = FUN_00810620(FUN_00805070((int)0x8d0f4fb));
    if (self->hB == 0) {
        void* old = self->hB;
        if (mainWin != old) {
            if (mainWin != 0)
                ((FV_v)(*(void***)mainWin)[0])(mainWin);
            self->hB = mainWin;
            if (old != 0)
                ((FV_v)(*(void***)old)[4 / 4])(old);
        }
    }

    {
        void* alloc = EAAllocate(0x54, "Simulator/Scenario/AvatarPaletteItem", 0, 0, 0, 0);
        if (alloc == 0) {
            item = 0;
        } else {
            item = FUN_005c66a0();
            if (item != 0)
                ((FV_v)(*(void***)item)[4 / 4])(item);
        }
    }

    {
        int key[4];
        key[0] = (int)0xd8c67022;
        key[1] = (int)0x00b1b104;
        key[2] = (int)0xd87454e6;
        key[3] = 0;
        if (FUN_005c6810(item, key, 0, 0) == 0 || self->hB == 0) {
            FUN_005c6710(item);
            if (item != 0)
                ((FV_v)(*(void***)item)[8 / 4])(item);
            return false;
        }
    }

    itemUI = FUN_009512d0(0xa0, 8, "Scenario/AvatarPaletteItemUI", FUN_009512c0());
    if (itemUI != 0)
        itemUI = FUN_00ed1250(itemUI);
    else
        itemUI = 0;
    self->hItemUI = itemUI;
    ((FV_v)(*(void***)itemUI)[4 / 4])(itemUI);

    catDesc = EAAllocate(0x34, "Editor", 0, 0, 0, 0);
    if (catDesc == 0) {
        catDesc = 0;
    } else {
        catDesc = FUN_005c64e0();
        if (catDesc != 0)
            ((FV_v)(*(void***)catDesc)[4 / 4])(catDesc);
    }
    {
        void* p = *(void**)((char*)catDesc + 8);
        if (p != 0) {
            *(void**)((char*)catDesc + 8) = 0;
            int rc = *(int*)((char*)p + 4) - 1;
            *(int*)((char*)p + 4) = rc;
            if (rc == 0) {
                *(int*)((char*)p + 4) = 1;
                ((FV_v)(*(void***)p)[0])(p);
            }
        }
        p = *(void**)((char*)catDesc + 0x10);
        if (p != 0) {
            *(void**)((char*)catDesc + 0x10) = 0;
            ((FV_v)(*(void***)p)[4 / 4])(p);
        }
    }
    *(uint16_t*)((char*)catDesc + 0x18) = 0x268a;

    pageWin = FUN_009512d0(0x20c, 4, "Scenario/AvatarPaletteItemUI/page_win", FUN_009512c0());
    pageBase = 0;
    if (pageWin != 0) {
        void* created = FUN_00962a10(pageWin);
        if (created != 0)
            pageBase = (char*)created + 4;
    }

    {
        void** vt = *(void***)pageBase;
        void*  id = ((FV_v)(*(void***)self->hB)[0x38 / 4])(self->hB);
        ((FV_p)(vt[0x6c / 4]))(pageBase, id);
        ((FV_ii)(*(void***)pageBase)[0x7c / 4])(pageBase, 0x10, 1);
        ((FV_p)(*(void***)self->hB)[0xd8 / 4])(self->hB, pageBase);
    }

    {
        float box[4];
        box[0] = 0.0f;
        box[1] = 0.0f;
        box[2] = 100.0f;
        box[3] = 100.0f;
        ((FV_p)(*(void***)pageBase)[0x6c / 4])(pageBase, box);
    }

    r = (float*)((FV_v)(*(void***)pageBase)[0x38 / 4])(pageBase);
    w = r[0];
    h = r[2];
    {
        float* q = (float*)((FV_v)(*(void***)self->hB)[0x38 / 4])(self->hB);
        ((FV_ii)(*(void***)pageBase)[0x64 / 4])(pageBase, 0, 0);
    }

    {
        void* old = self->hB;
        if (pageBase != old) {
            ((FV_v)(*(void***)pageBase)[0])(pageBase);
            self->hB = pageBase;
            if (old != 0)
                ((FV_v)(*(void***)old)[4 / 4])(old);
        }
    }

    {
        void* qi;
        if (self->hItemUI == 0)
            qi = 0;
        else
            qi = ((FV_i)(*(void***)((char*)self->hItemUI + 8))[0xc / 4])(
                     (char*)self->hItemUI + 8, 0x722e9c1);
        ((FV_fff)(*(void***)((char*)qi + 0x24))[4 / 4])((char*)qi + 0x24, pageBase, pageBase);
    }

    FUN_005f2290(0);

    {
        void* qi;
        void* old;
        if (self->hItemUI == 0)
            qi = 0;
        else
            qi = ((FV_i)(*(void***)((char*)self->hItemUI + 8))[0xc / 4])(
                     (char*)self->hItemUI + 8, 0x722e9c1);
        old = *(void**)((char*)qi + 0x40);
        if (old != self->hA) {
            if (old != 0)
                ((FV_v)(*(void***)old)[0])(old);
            void* prev = self->hA;
            self->hA = old;
            if (prev != 0)
                ((FV_v)(*(void***)prev)[4 / 4])(prev);
        }
    }

    if (self->hA != 0) {
        ((FV_v)(*(void***)catDesc)[8 / 4])(catDesc);
        self->hAvatarUI = (void*)FUN_00ed1120(FUN_00ed0c30, 0, self, 0x14, 0, 2, 0);
        {
            void* ms = FUN_0067dcc0((char*)self + 8, (void*)0x15ac038, 2);
            FUN_004db620(ms, (char*)self + 8, (void*)0x15ac038, 2);
        }
        if (unused != 0)
            ((FV_v)(*(void***)unused)[8 / 4])(unused);
        return true;
    }

    {
        void* qi;
        if (self->hItemUI == 0)
            qi = 0;
        else
            qi = ((FV_i)(*(void***)((char*)self->hItemUI + 8))[0xc / 4])(
                     (char*)self->hItemUI + 8, 0x722e9c1);
        ((FV_v)(*(void***)((char*)qi + 0x24))[8 / 4])((char*)qi + 0x24);
    }
    ((FV_v)(*(void***)self->hItemUI)[8 / 4])(self->hItemUI);
    self->hItemUI = 0;
    ((FV_v)(*(void***)catDesc)[8 / 4])(catDesc);
    if (unused != 0)
        ((FV_v)(*(void***)unused)[8 / 4])(unused);
    return false;
}

// placeholder kept for the two big entry points below
