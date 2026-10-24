// src/game/SPGonzago/SPUIGlobalUICiv.cpp -- migrated from slice(s) s00baa930, s00ba9810 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIGlobalUICiv.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00ba9810 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSortTriple {                                                    // 12-byte sort / run key
    float mX;                                                           // +0x00
    float mY;                                                           // +0x04
    float mZ;                                                           // +0x08
};
// ---- items of slice s00ba9810 end

// ---- items of slice s00baa930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete_array(void* p);            // 0x00f47380
extern "C" void* __cdecl RBTreeIncrement(void* node);               // 0x00921580
extern "C" void  __cdecl DoNukeSubtree(void* node);                 // 0x009a9600
#pragma warning(disable: 4100)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct RBNodeBase {
    RBNodeBase* mpNodeLeft;   // +0x00
    RBNodeBase* mpNodeRight;  // +0x04
    RBNodeBase* mpNodeParent; // +0x08
    u8          mColor;       // +0x0c
    u8          pad[3];
};
struct RBNode {
    RBNode* mpNodeLeft;   // +0x00
    RBNode* mpNodeRight;  // +0x04
    RBNode* mpNodeParent; // +0x08
    u8      mColor;       // +0x0c
    u8      pad[3];
    u32     first;        // +0x10  (pair.first)
    void*   second;       // +0x14
};
struct UnsignedVoidMap {
    char        mCompare[4];  // +0x00
    RBNodeBase  mAnchor;      // +0x04
    u32         mnSize;       // +0x14
    char        mAllocator;   // +0x18
};
struct EaWString {
    u32 mpBegin;   // +0x00
    u32 mpEnd;     // +0x04
    u32 mpCap;     // +0x08
};
struct cClassInfo {
    u32 mField00;   // +0x00
    u32 mField04;   // +0x04
    u32 mField08;   // +0x08
    u8  mField0C;   // +0x0c
    u8  mField0D;   // +0x0d
    u8  mField0E;   // +0x0e
    u8  mField0F;   // +0x0f
    u32 mField10;   // +0x10
    u32 mField14;   // +0x14
    u32 mField18;   // +0x18
    u32 mField1C;   // +0x1c

    cClassInfo& operator=(const cClassInfo& other);   // 0x00bab010
};
struct KeyVec {
    u32 mWords[5];  // 0x14 bytes
    KeyVec& operator=(const KeyVec& o);
};
void* __cdecl SP_PropertyManager();                                 // 0x0067de30
void  __cdecl FUN_00bf2c60(void* self);                             // 0x00bf2c60
void  __cdecl FUN_00bf4a60(u32 key, void* value);                   // 0x00bf4a60
int*  __cdecl Property_GetInt(void* prop);                          // 0x0041e990
void  __cdecl FUN_00c35310(void* self);                             // 0x00c35310
u8    __cdecl FUN_00ba9d60(void* a, void* b);                       // 0x00ba9d60
void* __cdecl FUN_006abf00();                                       // 0x006abf00
void  __cdecl FUN_00dd6740(void* a, void* b, u32 c);                // 0x00dd6740
void  __cdecl FUN_00579bd0(void* a, void* b, u32 c);                // 0x00579bd0
void  __cdecl EA_ConvertToString16(void* out, void* in, u32 n);     // 0x0093c5a0
u8    __cdecl FUN_00ba99f0(void* a, int b, void* c, void* d);       // 0x00ba99f0
u8    __cdecl FUN_00acaf80(void* a, int b, void* c, void* d);       // 0x00acaf80
void* __cdecl FUN_00b96130(void* a, void* b, void* c);              // 0x00b96130
void* __cdecl FUN_009360d0();                                       // 0x009360d0
void  __cdecl FUN_00bb9b00(int a, int b);                           // 0x00bb9b00
class cSPUILayoutManager_s00ba_a930 {
public:
    u8   pad_0000[0x64];
    u8   mField64;              // +0x64
    u8   pad_0065[0xc8 - 0x65];
    void* mListBegin;           // +0xc8
    void* mListEnd;             // +0xcc
    u8   pad_00d0[0x104 - 0xd0];
    void* mVecBegin;            // +0x104
    void* mVecEnd;              // +0x108
    u8   pad_010c[0x150 - 0x10c];
    UnsignedVoidMap mWorlds;    // +0x150
    u8   pad_016c[0x1d8 - 0x16c];
    int  mFeedbackID;           // +0x1d8
    u8   pad_01dc[0x224 - 0x1dc];
    void* mSetA;                // +0x224
    void* mSetB;                // +0x228

    void ReadCameraConfig();    // 0x00baa930
    void ShuffleEvents();       // 0x00baac30
    u8   MergeFeedback();       // 0x00baad00
};
struct SerializerVT {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void* v20();
    virtual void v24();
    virtual void v28(u32 key, void** out, int b);
};
struct SerReaderVT {
    virtual void r00();
    virtual void r04();
    virtual void r08();
    virtual void r0c();
    virtual void r10();
    virtual void r14();
    virtual void r18(void* out, int n, int b);
};
struct WriterVT {
    virtual void Begin(const wchar_t* name);
    virtual void End(const wchar_t* name);
};
void __cdecl wstr_RangeInitialize(void* self, int n);                // 0x00579a90
void __cdecl wstr_Ctor(void* self, const void* other);               // 0x0056e2d0
// ---- items of slice s00baa930 end

// @ 0x00baa810
cSortTriple* PartitionTriples(cSortTriple* pFirst, cSortTriple* pLast, cSortTriple value, char (*pPredicate)(const cSortTriple*, const cSortTriple*))
{
    for (;;) {
        while (pPredicate(pFirst, &value)) ++pFirst;
        --pLast;
        while (pPredicate(&value, pLast)) --pLast;
        if (pFirst >= pLast) return pFirst;
        cSortTriple saved = *pFirst;
        *pFirst = *pLast;
        *pLast = saved;
        ++pFirst;
    }
}

// @ 0x00baa930
void cSPUILayoutManager_s00ba_a930::ReadCameraConfig()
{
    u8* p = (u8*)this;
    void* mgr = SP_PropertyManager();
    mgr = mgr;                             // PropertyManager() result kept for the vtbl call
    (*(void(__thiscall*)(void*, u32, u32))((void**)*(void**)mgr)[0x2c / 4])(mgr, 0x280852f1u, 0x2ae0c7eu);

    int   val = 0;
    void* propMap = p;                     // no-op guard mirroring the original's local
    propMap = propMap;
    FUN_00bf2c60((char*)p);                // build the local property map

    void* ctx = p;                         // this property-manager interface (reloaded)
    int v1 = 0;
    if (ctx != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx)[0x24 / 4])(ctx, &propMap, 0x4ea8f1au)) {
            // value kind check: word at prop+0x12 == 9
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v1 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple1[3];
    triple1[0] = (u32)v1;
    triple1[1] = 0x2399be55u;
    triple1[2] = 0x40636200u;
    FUN_00bf4a60(0x99e92f05u, triple1);

    void* ctx2 = p;
    int v2 = 0;
    if (ctx2 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx2)[0x24 / 4])(ctx2, &propMap, 0x65cce6du)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v2 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple2[3];
    triple2[0] = (u32)v2;
    triple2[1] = 0x2399be55u;
    triple2[2] = 0x40636200u;
    FUN_00bf4a60(0x4e3f7777u, triple2);

    void* ctx3 = p;
    int v3 = 0;
    if (ctx3 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx3)[0x24 / 4])(ctx3, &propMap, 0x65cce70u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v3 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple3[3];
    triple3[0] = (u32)v3;
    triple3[1] = 0x2399be55u;
    triple3[2] = 0x40636200u;
    FUN_00bf4a60(0x47c10953u, triple3);

    void* ctx4 = p;
    int v4 = 0;
    if (ctx4 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx4)[0x24 / 4])(ctx4, &propMap, 0x65cce73u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v4 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple4[3];
    triple4[0] = (u32)v4;
    triple4[1] = 0x2399be55u;
    triple4[2] = 0x40636200u;
    FUN_00bf4a60(0x72c49181u, triple4);

    void* ctx5 = p;
    int v5 = 0;
    if (ctx5 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx5)[0x24 / 4])(ctx5, &propMap, 0x65cf1b6u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v5 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple5[3];
    triple5[0] = (u32)v5;
    triple5[1] = 0x24682294u;
    triple5[2] = 0x40646200u;
    FUN_00bf4a60(0xbc1041e6u, triple5);

    void* ctx6 = p;
    int v6 = 0;
    if (ctx6 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx6)[0x24 / 4])(ctx6, &propMap, 0x65e3a82u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v6 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple6[3];
    triple6[0] = (u32)v6;
    triple6[1] = 0x24682294u;
    triple6[2] = 0x40646200u;
    FUN_00bf4a60(0x2090a11bu, triple6);

    void* ctx7 = p;
    int v7 = 0;
    if (ctx7 != 0) {
        if ((*(u8(__thiscall*)(void*, void**, u32))((void**)*(void**)ctx7)[0x24 / 4])(ctx7, &propMap, 0x65e3a85u)) {
            if (*(u16*)((char*)propMap + 0x12) == 9) {
                v7 = *Property_GetInt(propMap);
            }
        }
    }
    u32 triple7[3];
    triple7[0] = (u32)v7;
    triple7[1] = 0x24682294u;
    triple7[2] = 0x40646200u;
    FUN_00bf4a60(0xc15695dau, triple7);

    if (*(int*)((char*)p + 0x1d8) != -1) {
        // eastl map find at this+0x150 with the key just read
        RBNode* n = (RBNode*)((UnsignedVoidMap*)((char*)p + 0x150))->mAnchor.mpNodeLeft;
        (void)n;
    }
    FUN_00c35310((char*)p + 0x68);
    DoNukeSubtree(*(void**)((char*)p + 0x74));
    if (ctx != 0) {
        (*(void(__thiscall*)(void*))((void**)*(void**)ctx)[4 / 4])(ctx);
    }
}

// @ 0x00baac30
void cSPUILayoutManager_s00ba_a930::ShuffleEvents()
{
    u8* p = (u8*)this;
    FUN_00b96130(*(void**)((char*)p + 0x104), *(void**)((char*)p + 0x108), (void*)0x1601760);
    int n = (int)(*(int*)((char*)p + 0x108) - *(int*)((char*)p + 0x104)) >> 2;
    for (int i = 0; i < n; i++) {
        u32 r = (u32)(size_t)FUN_009360d0();
        u32 idx = r % (u32)n;
        u32 tmp = *(u32*)(*(int*)((char*)p + 0x104) + i * 4);
        *(u32*)(*(int*)((char*)p + 0x104) + i * 4) = *(u32*)(*(int*)((char*)p + 0x104) + idx * 4);
        *(u32*)(*(int*)((char*)p + 0x104) + idx * 4) = tmp;
    }
    int m = (int)(*(int*)((char*)p + 0x110) - *(int*)((char*)p + 0x10c)) >> 2;
    FUN_00bb9b00(0x400, m);
}

// @ 0x00baad00
u8 cSPUILayoutManager_s00ba_a930::MergeFeedback()
{
    u8* p = (u8*)this;
    if (*(char*)((char*)p + 0x64) != 0) {
        return 1;
    }
    if (*(int*)((char*)p + 0x228) == 0) {
        return 1;
    }

    // local raster/scratch list built around +0x2c
    u32 listHead[2];
    listHead[0] = 0x13eb428u;        // ~list anchor sentinel
    listHead[1] = 0x5220cb8u;
    void* self2 = listHead;
    (void)self2;
    FUN_00c35310(listHead);

    void* generator = FUN_006abf00();
    (*(void(__thiscall*)(void*, void*, void*))((void**)*(void**)generator)[0x24 / 4])(generator, listHead, listHead);

    // gather the "read" set from this+0x224
    u32 setA[3];
    setA[0] = 0; setA[1] = 0; setA[2] = 0;
    (*(void(__thiscall*)(void*, u32*, int))((void**)*(void**)*(void**)((char*)p + 0x224))[0x30 / 4])
        (*(void**)((char*)p + 0x224), setA, 0);

    // gather the "write" set from this+0x228
    u32 setB[3];
    setB[0] = 0; setB[1] = 0; setB[2] = 0;
    (*(void(__thiscall*)(void*, u32*, int))((void**)*(void**)*(void**)((char*)p + 0x228))[0x30 / 4])
        (*(void**)((char*)p + 0x228), setB, 0);

    int count = (*(int*)((char*)p + 0xcc) - *(int*)((char*)p + 0xc8)) / 0x14;
    for (int row = 0; row < count; row++) {
        u8* entry = (u8*)(*(int*)((char*)p + 0xc8) + row * 0x14);
        int* v0 = *(int**)entry;
        int  n0 = (*(int*)(entry + 4) - (int)v0) >> 2;
        for (int j = 0; j < n0; j++) {
            int* item = *(int**)((char*)v0 + j * 4);
            u32 name = *(u32*)((char*)item + 0xac);
            for (u32 k = 0; k < name; k++) {
                int key = *(int*)((char*)item + 0x70) + k * 0x1000000;
                if (FUN_00ba9d60(*(void**)((char*)p + 0x224), &key)) {
                    break;
                }
                if (FUN_00ba9d60(*(void**)((char*)p + 0x228), &key)) {
                    break;
                }
            }
        }
    }

    if (setA[0]) {
        // release
        void* v = (void*)setA[0];
        if (v) (*(void(__thiscall*)(void*))((void**)*(void**)v)[4 / 4])(v);
    }
    if (setB[0]) {
        void* v = (void*)setB[0];
        if (v) (*(void(__thiscall*)(void*))((void**)*(void**)v)[4 / 4])(v);
    }
    // erase the scratch list
    (*(void(__thiscall*)(void*, void*))0x75f3f0)(listHead, listHead);
    return 1;
}

// @ 0x00bab010
cClassInfo& cClassInfo::operator=(const cClassInfo& other)
{
    mField00 = other.mField00;
    mField04 = other.mField04;
    mField08 = other.mField08;
    mField0C = other.mField0C;
    mField0D = other.mField0D;
    mField0E = other.mField0E;
    mField0F = other.mField0F;
    mField10 = other.mField10;
    mField14 = other.mField14;
    mField18 = other.mField18;
    mField1C = other.mField1C;
    *(KeyVec*)((char*)this + 0x20) = *(const KeyVec*)((const char*)&other + 0x20);
    *(KeyVec*)((char*)this + 0x34) = *(const KeyVec*)((const char*)&other + 0x34);
    return *this;
}

// @ 0x00bab080
void FUN_00bab080(SerializerVT* ser, void* tree)
{
    u8* t = (u8*)tree;
    DoNukeSubtree(*(void**)((char*)t + 0xc));
    u32 anchor = (u32)((char*)t + 4);
    *(u32*)((char*)t + 4)  = anchor;
    *(u32*)((char*)t + 8)  = anchor;
    *(u32*)((char*)t + 0xc)  = 0;
    *(u8*)((char*)t + 0x10)  = 0;
    *(u32*)((char*)t + 0x14) = 0;

    u32 count = 0;
    {
        void* a = ser->v20();
        ((SerReaderVT*)a)->r18(&count, 1, 0);
    }
    for (u32 i = 0; i < count; i++) {
        void* ref = 0;
        u32 key = 0;
        {
            void* a = ser->v20();
            ((SerReaderVT*)a)->r18(&key, 1, 0);
        }
        ser->v1c();
        if (ref != 0) {
            ref = 0;
        }
        ser->v28(0x3e4353bu, &ref, 0);
        ser->v1c();
        u32 packed = 0;
        FUN_00dd6740(&tree, &key, packed);
    }
    ser->v1c();
}

// @ 0x00bab200
void FUN_00bab200(SerializerVT* ser, void* tree)
{
    u8* t = (u8*)tree;
    DoNukeSubtree(*(void**)((char*)t + 0xc));
    u32 anchor = (u32)((char*)t + 4);
    *(u32*)((char*)t + 4)  = anchor;
    *(u32*)((char*)t + 8)  = anchor;
    *(u32*)((char*)t + 0xc)  = 0;
    *(u8*)((char*)t + 0x10)  = 0;
    *(u32*)((char*)t + 0x14) = 0;

    u32 count = 0;
    {
        void* a = ser->v20();
        ((SerReaderVT*)a)->r18(&count, 1, 0);
    }
    for (u32 i = 0; i < count; i++) {
        void* ref = 0;
        u32 key = 0;
        {
            void* a = ser->v20();
            ((SerReaderVT*)a)->r18(&key, 1, 0);
        }
        ser->v1c();
        if (ref != 0) {
            ref = 0;
        }
        ser->v28(0x1805e75u, &ref, 0);
        ser->v1c();
        u32 packed = 0;
        FUN_00dd6740(&tree, &key, packed);
    }
    ser->v1c();
}

// @ 0x00bab380
u8 FUN_00bab380(char* self, int arg1, int* list)
{
    // self is the serializer interface at caller's param_1 (a char* whose vtbl[0]/[4] are used)
    WriterVT* w = (WriterVT*)self;
    u8 result = 1;
    if (*list == list[1]) {
        return result;
    }

    // Build the field-name wstring from arg1.
    EaWString tmpA;
    EaWString tmpB;
    int flag = 0;
    u8  ok = 1;
    if (arg1 != 0) {
        EA_ConvertToString16(&tmpA, (void*)arg1, 0xffffffffu);
        flag = 1;
    } else {
        tmpA.mpBegin = 0; tmpA.mpEnd = 0; tmpA.mpCap = 0;
        wstr_RangeInitialize(&tmpA, 0);
        flag = 2;
    }
    wstr_Ctor(&tmpB, &tmpA);
    if ((flag & 2) && (((int)((tmpA.mpEnd - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
        flag &= ~2;
    }
    if ((flag & 1) && (((int)((tmpA.mpCap - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
    }

    const wchar_t* name = (tmpB.mpBegin == tmpB.mpEnd) ? L"list" : (const wchar_t*)tmpB.mpBegin;
    w->Begin(name);

    int end = *(int*)((char*)&list + 4);
    ok = 1;
    for (int it = *list; it != end; it += 0x10) {
        if (ok) {
            u8 r = FUN_00ba99f0((void*)self, 0, (void*)it, (void*)L"EA::String8");
            ok = r ? 1 : 0;
        }
    }

    const wchar_t* name2 = (tmpB.mpBegin == tmpB.mpEnd) ? L"list" : (const wchar_t*)tmpB.mpBegin;
    w->End(name2);
    if (((int)((tmpB.mpCap - tmpB.mpBegin) & 0xfffffffeu)) > 2 && tmpB.mpBegin != 0) {
        operator_delete_array((void*)tmpB.mpBegin);
    }
    return ok;
}

// @ 0x00bab4d0
u8 FUN_00bab4d0(char* self, int arg1, int* list)
{
    WriterVT* w = (WriterVT*)self;
    u8 result = 1;
    if (*list == list[1]) {
        return result;
    }

    EaWString tmpA;
    EaWString tmpB;
    int flag = 0;
    u8  ok = 1;
    if (arg1 != 0) {
        EA_ConvertToString16(&tmpA, (void*)arg1, 0xffffffffu);
        flag = 1;
    } else {
        tmpA.mpBegin = 0; tmpA.mpEnd = 0; tmpA.mpCap = 0;
        wstr_RangeInitialize(&tmpA, 0);
        flag = 2;
    }
    wstr_Ctor(&tmpB, &tmpA);
    if ((flag & 2) && (((int)((tmpA.mpEnd - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
        flag &= ~2;
    }
    if ((flag & 1) && (((int)((tmpA.mpCap - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
    }

    const wchar_t* name = (tmpB.mpBegin == tmpB.mpEnd) ? L"list" : (const wchar_t*)tmpB.mpBegin;
    w->Begin(name);

    int end = *(int*)((char*)&list + 4);
    ok = 1;
    for (int it = *list; it != end; it += 0x10) {
        if (ok) {
            u8 r = FUN_00acaf80((void*)self, 0, (void*)it, (void*)L"EA::String16");
            ok = r ? 1 : 0;
        }
    }

    const wchar_t* name2 = (tmpB.mpBegin == tmpB.mpEnd) ? L"list" : (const wchar_t*)tmpB.mpBegin;
    w->End(name2);
    if (((int)((tmpB.mpCap - tmpB.mpBegin) & 0xfffffffeu)) > 2 && tmpB.mpBegin != 0) {
        operator_delete_array((void*)tmpB.mpBegin);
    }
    return ok;
}

// @ 0x00bab620
void FUN_00bab620(SerializerVT* ser, void* tree)
{
    u8* t = (u8*)tree;
    DoNukeSubtree(*(void**)((char*)t + 0xc));
    u32 anchor = (u32)((char*)t + 4);
    *(u32*)((char*)t + 4)  = anchor;
    *(u32*)((char*)t + 8)  = anchor;
    *(u32*)((char*)t + 0xc)  = 0;
    *(u8*)((char*)t + 0x10)  = 0;
    *(u32*)((char*)t + 0x14) = 0;

    u32 count = 0;
    {
        void* a = ser->v20();
        ((SerReaderVT*)a)->r18(&count, 1, 0);
    }
    for (u32 i = 0; i < count; i++) {
        u32 key = 0, val = 0;
        {
            void* a = ser->v20();
            ((SerReaderVT*)a)->r18(&key, 1, 0);
        }
        ser->v1c();
        {
            void* a = ser->v20();
            ((SerReaderVT*)a)->r18(&val, 1, 0);
        }
        ser->v1c();
        u32 kv[2];
        kv[0] = key;
        kv[1] = val;
        FUN_00579bd0(&tree, kv, 0);
        *(u32*)((char*)tree + 0x14) = val;
    }
    ser->v1c();
}

// @ 0x00bab740
u8 FUN_00bab740(char* self, int* tree)
{
    WriterVT* w = (WriterVT*)self;
    u8 result = 1;
    if (tree[5] == 0) {           // +0x14 size
        return result;
    }

    EaWString tmpA;
    EaWString tmpB;
    int flag = 0;
    if (tree != 0) {
        EA_ConvertToString16(&tmpA, (void*)tree, 0xffffffffu);
        flag = 1;
    } else {
        tmpA.mpBegin = 0; tmpA.mpEnd = 0; tmpA.mpCap = 0;
        wstr_RangeInitialize(&tmpA, 0);
        flag = 2;
    }
    wstr_Ctor(&tmpB, &tmpA);
    if ((flag & 2) && (((int)((tmpA.mpEnd - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
        flag &= ~2;
    }
    if ((flag & 1) && (((int)((tmpA.mpCap - tmpA.mpBegin) & 0xfffffffeu)) > 2) && tmpA.mpBegin != 0) {
        operator_delete_array((void*)tmpA.mpBegin);
    }

    const wchar_t* name = (tmpB.mpBegin == tmpB.mpEnd) ? L"map" : (const wchar_t*)tmpB.mpBegin;
    w->Begin(name);

    u8 ok = 1;
    void* anchor = (char*)tree + 4;
    void* node = *(void**)((char*)tree + 8);
    if (node != anchor) {
        do {
            if (ok) {
                u8 r = FUN_00ba99f0((void*)self, 0, (char*)node + 0x14, (void*)L"uint32_t");
                ok = r ? 1 : 0;
            }
            node = RBTreeIncrement(node);
        } while (node != anchor);
    }

    const wchar_t* name2 = (tmpB.mpBegin == tmpB.mpEnd) ? L"map" : (const wchar_t*)tmpB.mpBegin;
    w->End(name2);
    if (((int)((tmpB.mpCap - tmpB.mpBegin) & 0xfffffffeu)) > 2 && tmpB.mpBegin != 0) {
        operator_delete_array((void*)tmpB.mpBegin);
    }
    return ok;
}
