// Slice s004b33e0: SP::cSPEditorPaintTheme prop/region helpers (unoptimized editor module,
// /Od /Ob1 /arch:SSE, no /EHsc).  Complements slice s004b2320.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct cSPColorRGB { uint32_t x, y, z; };
struct PropObj;
struct PropMgr;

struct PropObj {
    virtual void v0(); virtual void Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual char Has(uint32_t id);
    virtual void v8(); virtual void v9();
    virtual void* Get(uint32_t id);
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual char GetPropertyList(int id, uint32_t type, void** out);
};

extern "C" {
    void* SP_PropertyManager();
    void  FUN_006a0760(void* obj, uint32_t id, void* a, void* b);
    void  FUN_004553b0(void* out, void* key);
    void* FUN_00454420(void* value);
    char  FUN_0041db10(void* a, void* b, void* c);
    void  FUN_004098a0(void* dst, const void* src);
    void  FUN_00566c50(void* tree);
    int   FUN_004b5210(void* out, void* key);
    float* FUN_004b5370(void* key);
    int   FUN_00564f50();
    void  FUN_00422c50();
    void  FUN_004e8a30(void* o);
    int   FUN_004accf0();
    void* FUN_004accb0(int i);
    void  FUN_004769b0(void* a, void* b);
    void  GetPropertyAsIntArray(PropObj* list, uint32_t id, void* a, void* b);
    void  FUN_004b3e10(int a);
    void  FUN_004b5980(void* tag);
    void* FUN_004b5080(void* a, void* b);
    void  FUN_004b4fa0(void* a);
    void  FUN_00441d10(void* a);
    void  FUN_004b5xxx_push(void* value);
    int   FUN_004b3b20(int self, int key, int* outCount, int* outPtr);
}

namespace SP {
struct PaintVector {
    void* mpBegin; void* mpEnd; void* mpCap;
    char  mInline[0x110];
    void* Insert(void* value);
};
struct ModelTree { char _[0x1c]; };
class cSPEditorPaintTheme {
public:
    void* mpVtbl0; void* mpVtbl1; int mRefCount;
    PaintVector mPropTheme;          // +0xc
    ModelTree   mModelTheme;         // +0x128
    uint32_t mPropThemeID;           // +0x144
    uint32_t mSourceRef;             // +0x148
    uint32_t mResourceType;          // +0x14c
    void* mpClosestBegin;            // +0x150
    void* mpClosestEnd;              // +0x154
    void* mpClosestCap;              // +0x158
    char  pad_15c[8];
    uint32_t mSkinEffects[3];
    uint32_t mSkinEffectSeeds[3];
    cSPColorRGB mSkinColors[3];
    void InitClosestRegions(int a, int b);
    void SetRegionColor(int a, int b, int c, int d);
};
}
using namespace SP;

extern uint32_t DAT_015d6cc8;
extern "C" void* g_closestReserve;

// @ 0x004b33e0
int FUN_004b33e0(int* out, int* range, int key)
{
    (void)out; (void)range; (void)key;
    return 0;
}

// @ 0x004b3660
int FUN_004b3660(int self, int* out, int key)
{
    (void)self; (void)out; (void)key;
    return 0;
}

// @ 0x004b3730
void cSPEditorPaintTheme::InitClosestRegions(int a, int b)
{
    FUN_004769b0((void*)mResourceType, (void*)mSourceRef);
    int id = 0;
    bool match = false;
    if ((a == 0x24682294) || (a == 0x476a98c7)) {
        if ((b == 0x24682294) || (b == 0x476a98c7))
            id = 0x1625a584;
        else if (b == 0x2399be55)
            id = (int)0xb5306a4c;
    } else if (a == 0x2399be55) {
        if ((b == 0x24682294) || (b == 0x476a98c7))
            id = (int)0x844c912e;
        else if (b == 0x2399be55)
            id = (int)0xb3ef1246;
    }
    (void)match;
    if (id != 0) {
        PropObj* list = 0;
        PropMgr* mgr = (PropMgr*)SP_PropertyManager();
        if (list)
            list->Release();
        char ok = mgr->GetPropertyList(id, 0x4060e200, (void**)&list);
        if (ok) {
            int count = 0;
            int data = 0;
            GetPropertyAsIntArray(list, 0x52c57aa, &count, &data);
            FUN_00441d10(&mpClosestBegin);
            for (int i = 0; i < count; i++)
                FUN_004b5xxx_push((void*)(data + i * 4));
        }
        if (list)
            list->Release();
    }
}

// @ 0x004b3910
int FUN_004b3910(int self, int* out, int key)
{
    if (out == 0)
        return 0;
    FUN_00566c50((void*)(self + 300));
    int local_c = 0;
    void* found = (void*)FUN_004b5210(&local_c, &key);
    if (found != 0) {
        void* r = FUN_004b5080((void*)&key, 0);
        int iVar2 = FUN_004b33e0(out, (int*)r, key);
        if (iVar2 != 0)
            return 1;
    }
    char cVar1 = (char)FUN_004b3660(self, out, key);
    if (cVar1 != '\0')
        return 1;
    int a = 0, b = 0;
    FUN_004553b0(&a, &key);
    int node = (a == b) ? *(int*)(self + 0x10) : a;
    if (node != *(int*)(self + 0x10)) {
        int* src = (int*)FUN_00454420(&key);
        for (int k = 0; k < 7; k++)
            out[k] = src[k];
        return 1;
    }
    return 0;
}

// @ 0x004b3a50
int FUN_004b3a50(int out, int key, int arg3)
{
    int local_8 = 0;
    int local_10 = 0;
    char c = (char)FUN_004b3b20(0, key, &local_8, &local_10);
    if (c == '\0') {
        if (FUN_004b3910(out, (int*)key, arg3) != 0)
            return 1;
    } else {
        for (int i = 0; i < local_8; i++) {
            if (FUN_004b3910(out, *(int**)(local_10 + i * 4), arg3) != 0)
                return 1;
        }
    }
    int limit = 0x22;
    int i = 0;
    while (i < limit) {
        if (FUN_004b3910(out, (int*)i, arg3) != 0)
            return 1;
        i++;
    }
    return 0;
}

// @ 0x004b3b20
int FUN_004b3b20(int self, int key, int* outCount, int* outPtr)
{
    if (outCount == 0 || outPtr == 0 || key < 0)
        return 0;
    *outCount = 0;
    int found = 0;
    int start = *(int*)(self + 0x150);
    int n = (*(int*)(self + 0x154) - start) >> 2;
    int i = 0;
    while (i < n && found != key) {
        if (*(int*)(start + i * 4) == -1)
            found++;
        i++;
    }
    if (i == n)
        return 0;
    *outPtr = start + i * 4;
    do {
        int off = i * 4;
        i++;
        if (*(int*)(start + off) == -1)
            break;
        *outCount = *outCount + 1;
    } while (i != n);
    return 1;
}

// @ 0x004b3c20
void FUN_004b3c20(int model)
{
    if (model != 0) {
        int local = *(int*)(model + 0x1c);
        int local2 = local;
        int addr = model + 0x4c8;
        (void)addr;
        FUN_004b5080(&local2, &addr);
        FUN_004b4fa0(&local2);
    }
}

// @ 0x004b3c70
void cSPEditorPaintTheme::SetRegionColor(int a, int b, int c, int d)
{
    PropObj* list = 0;
    PropMgr* mgr = (PropMgr*)SP_PropertyManager();
    if (list)
        list->Release();
    mgr->GetPropertyList(d, 0x406a6f00, (void**)&list);
    if (list != 0) {
        int n = 0;
        int data = 0;
        FUN_006a0760(list, 0xf21a7bdc, &data, &n);
        for (int i = 0; i < n; i++) {
            if (*(char*)(data + i) == 1) {
                int a1 = 0, b1 = 0;
                FUN_004553b0(&a1, &i);
                int node = (a1 == b1) ? *(int*)((char*)&mPropTheme + 0xc)
                                      : a1;
                if (node != *(int*)((char*)&mPropTheme + 0xc)) {
                    int e = (int)FUN_00454420(&i);                    *(int*)(e + 0x10) = a;
                    *(int*)(e + 0x14) = b;
                    *(int*)(e + 0x18) = c;
                }
            }
        }
    }
    if (list)
        list->Release();
}
