// Slice s004ba150: Editor resource constructors / AsInterface thunks plus two large editor
// paint/validity bodies. Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"

extern void* g_vtbl;

extern "C" {
    void  FUN_004f3de0(void* a, void* b, int c, int d, int e, int f, char g);
    void* SP_cResourceBase_AsInterface(void* self, int type);
    void  FUN_0046a7c0(void* a);
    void  FUN_004b00a0(void* a);
    void  FUN_0041eb80(void);
    void  FUN_0041e640(void);
    void  FUN_004e8a30(void* a);
    void* ResourceMgr();
}
extern int DAT_015da860, DAT_015da864, DAT_015da868, DAT_015da86c;

struct cResourceBase {
    cResourceBase* AsInterface(int type);
};

class cEditorResource {
public:
    void* mpVtbl0;   // +0
    int   mRefCount; // +4
    char  pad[0x100];
    cEditorResource(int* src);
    void* AsInterface(int type) { return SP_cResourceBase_AsInterface(this, type); }
};

class cRuntimeCreatureResource {
public:
    cResourceBase* AsInterface(int type);   // 0x4bac80
    void zero();                             // 0x4bacc0
};

// @ 0x4ba150  (EditorValidity::AddCellUpgradeForBlockPropList — large)
int FUN_004ba150(void* self, void* prop)
{
    (void)self; (void)prop;
    return 0;
}

// @ 0x4bab30
cEditorResource::cEditorResource(int* src)
{
    mpVtbl0 = &g_vtbl;
    mpVtbl0 = &g_vtbl;
    mpVtbl0 = &g_vtbl;
    mRefCount = 0;
    *(int*)((char*)this + 8) = *(int*)((char*)src + 8);
    *(int*)((char*)this + 0xc) = *(int*)((char*)src + 0xc);
    *(int*)((char*)this + 0x10) = *(int*)((char*)src + 0x10);
    mpVtbl0 = &g_vtbl;
    *(int*)((char*)this + 0x14) = *(int*)((char*)src + 0x14);
    mpVtbl0 = &g_vtbl;
    FUN_0046a7c0((char*)src + 0x18);
    FUN_004b00a0((char*)src + 0x98);
}

extern void* g_vtbl;

extern void* g_vtbl;

// @ 0x4babe0
void* __fastcall FUN_004babe0(void* self, void* b, char c)
{
    FUN_004f3de0(b, self, DAT_015da860, DAT_015da864, DAT_015da868, DAT_015da86c, c);
    return b;
}

// @ 0x4bac30
void* __fastcall FUN_004bac30(void* self, void* b, void* c, void* d, void* e, void* f, char g)
{
    FUN_004f3de0(b, self, (int)c, (int)d, (int)e, (int)f, g);
    return b;
}

// @ 0x4bac80
cResourceBase* cRuntimeCreatureResource::AsInterface(int type)
{
    return type == 0x3e1c247
               ? (cResourceBase*)this
               : ((cResourceBase*)this)->AsInterface(type);
}

// @ 0x4bacc0
void cRuntimeCreatureResource::zero()
{
    int* p = (int*)this;
    p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
    p[8] = 0; p[9] = 0; p[10] = 0;
}

// @ 0x4bad50
void __fastcall FUN_004bad50(int* p)
{
    FUN_0041eb80();
    FUN_0041e640();
    if (p[2] != 0) {
        extern void ThreadedObject_Release(void*);
        ThreadedObject_Release((void*)p[2]);
    }
    if (p[1] != 0) {
        extern void AutoRefCount_assign(void);
    }
    if (*p != 0)
        (*(void(__thiscall**)(int))(*p + 4))(*p);
}

// @ 0x4badd0  SP::cSPEditorPaintTheme::Apply (large)
int FUN_004badd0(void* self, int* a, void* b)
{
    (void)self; (void)a; (void)b;
    return 0;
}
