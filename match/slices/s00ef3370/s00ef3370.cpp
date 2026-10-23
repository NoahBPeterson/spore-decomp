/* Quest: SP::Thumbnail::cImportExport / SP::cSPUIAssetView IMsgHandler (at +0x108)
 * message handlers, constructor/destructor and UI refresh helpers.
 *
 * Compiled as C++ (/TP): MSVC allocates vtable-call registers the way the
 * original does (vtable in eax, callee in edx) and __thiscall function-pointer
 * types are available, so virtual calls need no dummy second argument.
 */

typedef unsigned char uchar;
typedef unsigned int  uint;

#include <intrin.h>

/* ---- callees (__fastcall with a dummy 2nd param == __thiscall with N stack args) ---- */
extern void  EA_Messaging_RemoveHandler(int h, int a, int b, int c, int d); /* 0x00571db0 cdecl */
extern void __fastcall FUN_00659e30(void *self);  /* 0x00659e30 Cleanup (this in ecx) */
extern void __fastcall FUN_006593c0(void *self);  /* 0x006593c0 (this in ecx) */
extern void __fastcall FUN_006580b0(void *self);  /* 0x006580b0 (this in ecx) */
extern void  FUN_00657f70(void);            /* 0x00657f70 base ctor (this in ecx, no stack args) */
extern int   DAT_015acd3c;                  /* 0x015acd3c */
extern int   DAT_015acc30;                  /* 0x015acc30 */
extern int   DAT_015ee298;                  /* 0x015ee298 */
extern int   VTABLE_0148b1b0;               /* 0x0148b1b0 */
extern int   VTABLE_0148b19c;               /* 0x0148b19c */
extern int   VTABLE_0148b194;               /* 0x0148b194 */
extern int   VTABLE_013eb394;               /* 0x013eb394 */
extern int   VTABLE_0148b208;               /* 0x0148b208 */

extern int   FUN_00985e40(void);            /* 0x00985e40 */
extern uint  FUN_00ebbf60(void);            /* 0x00ebbf60 */
extern void *SP_AssetBrowser(void);         /* 0x00f0e260 SP::AssetBrowser */
extern char  FUN_00ed8130(int a, int b, int c); /* 0x00ed8130 */
extern char  SP_cSPAssetDataList_SetAssetData(int a, int b); /* SetAssetData */
extern uint  AutoRefCount_AsPPTypeParam(void);
extern char  FUN_00552450(int *a, uint b);  /* 0x00552450 */
extern char  FUN_00550970(void);            /* 0x00550970 */
extern void *SP_MessageServer(void);        /* 0x0067dcc0 */
extern int   FUN_00ed4e30(void);            /* 0x00ed4e30 */
extern void *SP_NounManager(void);          /* 0x00b3d300 */
extern int   SP_cGameNounManager_GetAvatar(void *mgr); /* 0x00b1fdb0 */
extern void *SP_ObjectTemplateDB(void);     /* 0x0067cb40 */
extern void *ResourceMan_GetManager(void);  /* 0x0067dcd0 */
extern void  operator_delete(void *p);      /* 0x00f47380 */
extern void __fastcall FUN_00ed6b00(void *self);  /* 0x00ed6b00 Panel::Deactivate2 */
extern void __fastcall FUN_00ed6a10(void *self);  /* 0x00ed6a10 Panel::Activate2 */
extern void  FUN_00f039a0(int a);           /* 0x00f039a0 cdecl */
extern void  FUN_00eff790(int a);           /* 0x00eff790 cdecl */
extern void __fastcall FUN_00ef1ca0(void *self);  /* 0x00ef1ca0 */
extern void  FUN_00f31c20(int a);           /* 0x00f31c20 */
extern uint  FUN_00f37b20(void);            /* 0x00f37b20 */
extern uint  FUN_00f37a40(int *p, int b);   /* 0x00f37a40 */
extern void __fastcall FUN_004e39a0(void *self, void *dummy, void *a, void *b); /* 0x004e39a0 */
extern void __fastcall FUN_004e39d0(void *self, void *dummy, void *end, void *val); /* 0x004e39d0 */
extern void __fastcall FUN_00606880(void *dst, void *dummy, void *src); /* 0x00606880 */
extern void __fastcall FUN_006066f0(void *self);   /* 0x006066f0 Constraint dtor */

/* Constraint ctor: thiscall(this, key, eq, value) */
extern void *Constraint_ctor_eq(void *self, void *dummy, int key, int eq, int val); /* 0x00558960 */
extern void *Constraint_ctor_ne(void *self, void *dummy, int key, int eq, int val); /* 0x00558a20 */

/* 0x00ef3a60 helpers */
extern uchar FUN_008068d0(void *txt, int img, int last); /* 0x008068d0 cdecl */
extern void *SPUIHelpers_GetImageFromLayout(void *layout, int hash); /* 0x008061c0 */

/* 0x00ef3d20 helpers */
extern void __fastcall FUN_006582f0(void *self, void *dummy, int a, int b, int c, int d); /* 0x006582f0 */

/* 0x00ef3e40 helpers */
extern void *FUN_00eed8c0(void *a);         /* 0x00eed8c0 */
extern void __fastcall eastl_wstring_ctor(void *dst, void *dummy, int a, void *name, void *val); /* 0x00473020 */
extern void __fastcall eastl_wstring_free(void *self); /* 0x00933960 */
extern void __fastcall cString_ctor(void *self);       /* 0x006b5060 */
extern uchar __fastcall cString_Load(void *self, void *dummy, int a, int b, void *name); /* 0x006b54b0 */
extern void *__fastcall cString_GetText(void *self);   /* 0x006b55c0 */
extern void __fastcall cString_dtor(void *self);       /* 0x006b5240 */
extern void *FUN_00ec3ca0(float f);                    /* 0x00ec3ca0 cdecl */
extern void *FUN_00ef38a0(void *p);                    /* 0x00ef38a0 cdecl */
extern uchar __fastcall cPropertyBag_GetFloat(void *self, void *dummy, int key, float *out); /* 0x006135d0 */
extern uchar __fastcall cPropertyBag_GetInt32(void *self, void *dummy, int key, int *out);   /* 0x00613660 */

/* 0x00ef4050 helpers */
extern void *FUN_0067cb30(void);            /* 0x0067cb30 cdecl */
extern uchar __fastcall cAssetDirectory_GetServerId(void *self, void *dummy, void *key,
                                                    int *out, int b); /* 0x0054e530 */

struct Constraint { int pad[9]; };           /* 0x24 bytes */
struct ConstraintVec { struct Constraint *begin, *end, *cap; };

/* 0x00ef3a60: direct thiscall to AutoRefCount<...>::operator= */
struct AutoRefCountAssign { void *op(void *src); };

#define RELEASE_CLEAR(off)                                                     \
    do {                                                                       \
        p = *(int **)(self + (off));                                           \
        if (p != 0) {                                                          \
            *(int **)(self + (off)) = 0;                                       \
            ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);               \
        }                                                                      \
    } while (0)

#define RELEASE_ONLY(off)                                                      \
    do {                                                                       \
        p = *(int **)(self + (off));                                           \
        if (p != 0) {                                                          \
            ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);               \
        }                                                                      \
    } while (0)

#define VIS_TOGGLE(off, a, b)                                                  \
    ((void (__thiscall *)(void *, int, int))                                   \
        (*(void ***)*(void **)(self + (off)))[0x1f])(*(void **)(self + (off)), (a), (b))

// @ 0x00ef3370
uint __fastcall FUN_00ef3370(char *self, void *dummy, int msg, int *param_3)
{
    int *vec;
    int *it;
    int *end;
    void *par;
    int *obj;
    uint uVar4;
    struct ConstraintVec list;
    struct Constraint tmp;
    void *db;
    void *mgr;
    int n;
    int i;
    int local;

    switch (msg) {
    case 0x074baf67:
        if ((FUN_00985e40() == 1) && ((param_3[2] == 0) || (param_3[2] == 2))) {
            return FUN_00ebbf60() & 0xffffff00;
        }
        break;
    case 0x05132389:
        if (*(int *)(self + 200) == 1) {
            par = SP_AssetBrowser();
            if ((par == 0) || (*(char *)((char *)par + 0x1c) == 0)) {
                vec = (int *)*param_3;
                it = (int *)*vec;
                end = (int *)vec[1];
                if (it != end) {
                    while ((*(int *)(self + 0x10) == 0) ||
                           (FUN_00ed8130(it[0], it[1], it[2]) == 0)) {
                        it += 3;
                        if (it == end) {
                            return 0;
                        }
                    }
                }
            }
        }
        break;
    case 0x04249453:
        if (SP_cSPAssetDataList_SetAssetData(param_3[2], 0) != 0) {
            n = param_3[8] != 0;
            if (n == 0) {
                uVar4 = AutoRefCount_AsPPTypeParam();
                if ((FUN_00552450(param_3 + 6, uVar4) != 0) && (FUN_00550970() != 0)) {
                    n = 1;
                }
                if (n == 0) {
                    break;
                }
            }
            if (*(char *)(self + 0xa4) == 0) {
                obj = (int *)SP_MessageServer();
                uVar4 = ((uint (__fastcall *)(void *, void *, int, int, int, int))
                             (*(void ***)obj)[6])(obj, 0, 0x07fb11b4, 0, 0, 0);
                *(char *)(self + 0xa4) = 1;
                return uVar4 & 0xffffff00;
            }
        }
        break;
    case 0x0462c656:
        if (FUN_00ed4e30() == 0x07eaf739) {
            DAT_015acc30 = 1;
            return 0x07eaf700;
        }
        break;
    case 0x073e8559:
        uVar4 = SP_cGameNounManager_GetAvatar(SP_NounManager());
        if (uVar4 != 0) {
            *(char *)(uVar4 + 0x131) = 0;
            return uVar4 & 0xffffff00;
        }
        break;
    case 0x07fb11b4:
        db = SP_ObjectTemplateDB();
        list.begin = 0;
        list.end = 0;
        list.cap = 0;

        Constraint_ctor_eq(&tmp, 0, 0x02dd90af, 0, 0x366a930d);
        if (list.end < list.cap) {
            struct Constraint *e = list.end;
            list.end = e + 1;
            if (e != 0) {
                FUN_00606880(e, 0, &tmp);
            }
        } else {
            FUN_004e39d0(&list, 0, list.end, &tmp);
        }
        FUN_006066f0(&tmp);

        Constraint_ctor_eq(&tmp, 0, 0x54a32960, 0, 1);
        if (list.end < list.cap) {
            struct Constraint *e = list.end;
            list.end = e + 1;
            if (e != 0) {
                FUN_00606880(e, 0, &tmp);
            }
        } else {
            FUN_004e39d0(&list, 0, list.end, &tmp);
        }
        FUN_006066f0(&tmp);

        Constraint_ctor_ne(&tmp, 0, 0x03cc89b1, 0, 0x913b23be);
        if (list.end < list.cap) {
            struct Constraint *e = list.end;
            list.end = e + 1;
            if (e != 0) {
                FUN_00606880(e, 0, &tmp);
            }
        } else {
            FUN_004e39d0(&list, 0, list.end, &tmp);
        }
        FUN_006066f0(&tmp);

        {
            struct ConstraintVec out;
            out.begin = 0;
            out.end = 0;
            out.cap = 0;
            ((void (__fastcall *)(void *, void *, void *, void *))
                 (*(void ***)db)[0xe])(db, 0, &out, &list);

            n = (int)((char *)out.end - (char *)out.begin) / 0x24;
            for (i = 0; i < n; i++) {
                mgr = ResourceMan_GetManager();
                local = 0;
                ((uchar (__fastcall *)(void *, void *, void *, void *, int, int, int, int))
                     (*(void ***)mgr)[3])(mgr, 0, (char *)out.begin + i * 0x24,
                                          &local, 0, 0, 0, 0);
            }
        }
        *(char *)(self + 0xa4) = 0;
        break;
    case 0x86a4609d:
        if (*(int *)(self + 200) == 1) {
            FUN_00ed6b00(*(void **)(self + 0x10));
            FUN_00f039a0(1);
            FUN_00eff790(0);
            FUN_00ed6a10(*(void **)(self + 0x10));
            if (param_3 != (int *)1) {
                FUN_00ef1ca0(&DAT_015acc30);
                return 0;
            }
        }
        break;
    case 0xc054b3c0:
        FUN_00f31c20(0);
        if (param_3[2] == 0) {
            return FUN_00f37b20() & 0xffffff00;
        }
        return FUN_00f37a40(param_3, 0) & 0xffffff00;
    default:
        break;
    }
    return 0;
}

// @ 0x00ef38c0
void __fastcall FUN_00ef38c0(char *self)
{
    int iVar1;
    void *q;

    iVar1 = *(int *)(self + 0x10c);
    if (iVar1 != 0) {
        *(int *)(self + 0x10c) = 0;
        EA_Messaging_RemoveHandler(iVar1, *(int *)(self + 0x110), *(int *)(self + 0x114),
                                   *(int *)(self + 0x118), *(int *)(self + 0x11c));
    }
    iVar1 = *(int *)(self + 0x120);
    if (iVar1 != 0) {
        q = (void *)(iVar1 + 0x10);
        *(int *)(self + 0x120) = 0;
        ((void (__thiscall *)(void *))(*(void ***)q)[1])(q);
    }
    FUN_00659e30(self);
}

// @ 0x00ef3930
void __stdcall FUN_00ef3930(int *param_1)
{
    int uVar1;

    uVar1 = DAT_015acd3c;
    param_1[0] = 0x68715e28;
    param_1[1] = 0x0510a95b;
    param_1[2] = uVar1;
}

// @ 0x00ef3950
void __fastcall FUN_00ef3950(char *self)
{
    int *p;

    RELEASE_CLEAR(0x124);
    RELEASE_CLEAR(0x128);
    p = *(int **)(self + 0x12c);
    if (p != 0) {
        ((void (__thiscall *)(void *, int, int))(*(void ***)p)[0x1f])(p, 1, 0);
    }
    RELEASE_CLEAR(0x12c);
    RELEASE_CLEAR(0x130);
    RELEASE_CLEAR(0x134);
    RELEASE_CLEAR(0x138);
    RELEASE_CLEAR(0x13c);
    RELEASE_CLEAR(0x140);
    RELEASE_CLEAR(0x144);
    RELEASE_CLEAR(0x148);
    FUN_006593c0(self);
}

// @ 0x00ef3a60
void __fastcall FUN_00ef3a60(char *self)
{
    void *buf;
    void *img;
    void *layout;
    void **p;

    if (*(int *)(self + 0x124) == 0) {
        return;
    }
    p = *(void ***)(self + 0x120);
    if (p == 0) {
        return;
    }
    if (((int (__fastcall *)(void *))(*(void ***)p)[9])(p) == 0x24720859) {
        FUN_008068d0(*(void **)(self + 0x124), 0, -1);
        VIS_TOGGLE(0x124, 1, 0);
        return;
    }
    layout = *(void **)(self + 0x20);
    buf = 0;
    img = SPUIHelpers_GetImageFromLayout(
              layout,
              ((int (__fastcall *)(void *))(*(void ***)*(void **)(self + 0x120))[9])
                  (*(void **)(self + 0x120)));
    ((AutoRefCountAssign *)&buf)->op(img);
    if (img != 0) {
        FUN_008068d0(*(void **)(self + 0x124), (int)img, -1);
        VIS_TOGGLE(0x124, 1, 1);
        ((void (__fastcall *)(void *))(*(void ***)img)[1])(img);
    } else {
        FUN_008068d0(*(void **)(self + 0x124), 0, -1);
        VIS_TOGGLE(0x124, 1, 0);
    }
}

// @ 0x00ef3b40
void *__fastcall FUN_00ef3b40(char *self)
{
    FUN_00657f70();
    *(void **)(self + 0x108) = (void *)&VTABLE_013eb394;
    _ReadWriteBarrier();
    *(void **)self = (void *)&VTABLE_0148b1b0;
    *(void **)(self + 4) = (void *)&VTABLE_0148b19c;
    *(void **)(self + 0x108) = (void *)&VTABLE_0148b194;
    *(int *)(self + 0x10c) = 0;
    _ReadWriteBarrier();
    *(int *)(self + 0x110) = 0;
    *(int *)(self + 0x114) = 0;
    *(int *)(self + 0x118) = 0;
    *(int *)(self + 0x11c) = 0;
    *(int *)(self + 0x120) = 0;
    *(int *)(self + 0x124) = 0;
    *(int *)(self + 0x128) = 0;
    *(int *)(self + 0x12c) = 0;
    *(int *)(self + 0x130) = 0;
    *(int *)(self + 0x134) = 0;
    *(int *)(self + 0x138) = 0;
    *(int *)(self + 0x13c) = 0;
    *(int *)(self + 0x140) = 0;
    *(int *)(self + 0x144) = 0;
    *(int *)(self + 0x148) = 0;
    return self;
}

// @ 0x00ef3bf0
void __fastcall FUN_00ef3bf0(char *self)
{
    int *p;
    void *q;
    int iVar1;

    *(void **)self = (void *)&VTABLE_0148b1b0;
    *(void **)(self + 4) = (void *)&VTABLE_0148b19c;
    *(void **)(self + 0x108) = (void *)&VTABLE_0148b194;
    _ReadWriteBarrier();
    RELEASE_ONLY(0x148);
    RELEASE_ONLY(0x144);
    RELEASE_ONLY(0x140);
    RELEASE_ONLY(0x13c);
    RELEASE_ONLY(0x138);
    RELEASE_ONLY(0x134);
    RELEASE_ONLY(0x130);
    RELEASE_ONLY(0x12c);
    RELEASE_ONLY(0x128);
    RELEASE_ONLY(0x124);
    p = *(int **)(self + 0x120);
    if (p != 0) {
        q = (void *)((char *)p + 0x10);
        ((void (__thiscall *)(void *))(*(void ***)q)[1])(q);
    }
    iVar1 = *(int *)(self + 0x10c);
    if (iVar1 != 0) {
        *(int *)(self + 0x10c) = 0;
        EA_Messaging_RemoveHandler(iVar1, *(int *)(self + 0x110), *(int *)(self + 0x114),
                                   *(int *)(self + 0x118), *(int *)(self + 0x11c));
    }
    *(void **)(self + 0x108) = (void *)&VTABLE_013eb394;
    FUN_006580b0(self);
}

// @ 0x00ef3d20
void __fastcall FUN_00ef3d20(char *self, void *dummy, int a, int b, int c, int d)
{
    int *p90;
    int *obj;
    int *old;
    void *handler;
    void *srv;

    FUN_006582f0(self, 0, a, b, c, d);

    p90 = *(int **)(self + 0x90);
    if (p90 == 0) {
        obj = 0;
    } else {
        obj = (int *)((int (__fastcall *)(void *, void *, int))
                          (*(void ***)((char *)p90 + 0x10))[3])((char *)p90 + 0x10, 0, 0x8d021ce9);
    }

    old = *(int **)(self + 0x120);
    if (obj != old) {
        if (obj != 0) {
            ((void (__thiscall *)(void *))(*(void ***)((char *)obj + 0x10))[0])((char *)obj + 0x10);
        }
        *(int **)(self + 0x120) = obj;
        if (old != 0) {
            ((void (__thiscall *)(void *))(*(void ***)((char *)old + 0x10))[1])((char *)old + 0x10);
        }
    }

    if (self == 0) {
        handler = 0;
    } else {
        handler = self + 0x108;
    }
    srv = SP_MessageServer();
    *(void **)(self + 0x10c) = srv;
    *(void **)(self + 0x110) = handler;
    *(void **)(self + 0x114) = (void *)&VTABLE_0148b208;
    *(int *)(self + 0x118) = 1;
    *(int *)(self + 0x11c) = 0;
    if ((srv != 0) && (handler != 0)) {
        ((void (__fastcall *)(void *, void *, void *, int))(*(void ***)srv)[9])(srv, 0, handler,
                                                                               0x9818ab6c);
    }
}

// @ 0x00ef3e40
void __fastcall FUN_00ef3e40(char *self)
{
    int *p;
    int *ph;
    void *img;
    int  hash;
    int  n;
    int  cnt;
    float f;
    char wbuf[0x18];

    p = *(int **)(self + 0x12c);
    if (p == 0) {
        return;
    }
    ((void (__thiscall *)(void *, int, int))(*(void ***)p)[0x1f])(p, 1, 0);

    ph = *(int **)(self + 0x120);
    if (ph == 0) {
        return;
    }
    hash = ((int (__fastcall *)(void *))(*(void ***)ph)[9])(ph);
    if (hash == 0x24720859) {
        return;
    }

    if (*(int *)(self + 0x128) != 0) {
        void *s;
        s = (void *)((int (__fastcall *)(void *))(*(void ***)ph)[0x10])(ph);
        s = FUN_00eed8c0(s);
        wbuf[0] = 0;
        eastl_wstring_ctor(wbuf, 0, 0, (void *)0x013f01bc, s);
        p = *(int **)(self + 0x128);
        ((void (__fastcall *)(void *, void *))(*(void ***)p)[0x20])(p, (void *)wbuf);
        p = *(int **)(self + 0x128);
        ((void (__thiscall *)(void *, int, int))(*(void ***)p)[0x1f])(p, 1, 1);
        eastl_wstring_free(wbuf);
    }

    img = (void *)((int (__fastcall *)(void *))(*(void ***)ph)[0x27])(ph);
    f = 0.0f;
    n = 0;
    cnt = 3;
    if (img == 0) {
        return;
    }
    if (cPropertyBag_GetFloat(img, 0, 0x190e18aa, &f) == 0) {
        return;
    }
    if (cPropertyBag_GetInt32(img, 0, 0x35c95bc4, &n) == 0) {
        return;
    }
    if (cPropertyBag_GetInt32(img, 0, 0x11576eea, &cnt) == 0) {
        return;
    }
    {
        void *res = FUN_00ec3ca0(f);
        void *tray = FUN_00ef38a0(self + 0x130);
        if (tray != 0) {
            ((void (__fastcall *)(void *, void *))(*(void ***)((char *)tray + 0x20c))[5])
                ((char *)tray + 0x20c, res);
        }
        *(int *)(DAT_015ee298 + 0x60) = n;

        cString_ctor(wbuf);
        cString_Load(wbuf, 0, 0x6f5943eb, 0x2100001, (void *)0x0148b244);
        p = *(int **)(self + 0x134);
        if (p != 0) {
            ((void (__fastcall *)(void *, void *))(*(void ***)p)[0x20])(p, cString_GetText(wbuf));
        }
        {
            void *slider = FUN_00ef38a0(self + 0x138);
            if ((slider != 0) && (cnt >= 1)) {
                void *sub = (char *)slider + 0x20c;
                int maxv = ((int (__fastcall *)(void *))(*(void ***)sub)[4])(sub);
                if (cnt <= maxv) {
                    ((void (__fastcall *)(void *, int))(*(void ***)sub)[5])(sub, cnt - 1);
                }
            }
        }
        p = *(int **)(self + 0x12c);
        ((void (__thiscall *)(void *, int, int))(*(void ***)p)[0x1f])(p, 1, 1);
        cString_dtor(wbuf);
    }
}

// @ 0x00ef4050
uchar __fastcall FUN_00ef4050(void *self, void *dummy, int magic, char *param_3)
{
    int *h;
    void *dir;
    void *key;
    int local_8;
    int local_4;
    uchar ok;

    if ((magic != 0x9818ab6c) || (param_3 == 0)) {
        return 0;
    }
    h = *(int **)((char *)self + 0x18);
    if (h == 0) {
        return 0;
    }
    dir = *(void **)((char *)FUN_0067cb30() + 0x58);
    local_8 = 0;
    local_4 = 0;
    key = ((void *(__fastcall *)(void *))(*(void ***)h)[0x10])(h);
    ok = cAssetDirectory_GetServerId(dir, 0, key, &local_8, 0);
    if (ok == 0) {
        return 0;
    }
    if (local_8 != *(int *)(param_3 + 8)) {
        return 0;
    }
    if (local_4 != *(int *)(param_3 + 0xc)) {
        return 0;
    }
    if (*param_3 == 0) {
        return 0;
    }
    FUN_00ef3e40((char *)self - 0x108);
    return 0;
}
