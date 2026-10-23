// Slice s00e63ac0 (frozen batch spcg1): object SPGonzago/SPCellGame.obj.
// Cell-game collision update, cell-effect spawn, cCellGfx lifetime (ctor/dtor),
// DNA-effect HUD helper and EASTL vector instances.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- common layouts
struct cSPVector3 { float x, y, z; };
struct cSPMatrix3 { float m[9]; };
struct cSPTransform {                 // size 0x38
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3 mTranslation;          // +0x4
    float mScale;                     // +0x10
    cSPMatrix3 mRotation;             // +0x14
};

// intrusive ref-counted object (vtable: 0=AddRef 4=Release)
struct RefObj {
    virtual int AddRef();
    virtual int Release();
    virtual int v2(); virtual int v3(); virtual int v4(); virtual int v5();
    virtual int v6(); virtual int v7(); virtual int v8(); virtual int v9();
    virtual int v10(); virtual int v11(); virtual int v12(); virtual int v13();
    virtual int v14(); virtual int v15(); virtual int v16(); virtual int v17();
    virtual int v18(); virtual int v19(); virtual int v20(); virtual int v21();
    virtual int v22(); virtual int v23();
};

// 23-slot vtable prober (slots 0x00..0x58).
struct VObj {
    virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
    virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
    virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
    virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
    virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
    virtual int v20(); virtual int v21(); virtual int v22();
};

extern "C" void  __cdecl sPartIntersectTarget(void*, void*, void*);                 // 0xe63480
extern "C" void  __cdecl cSPTransform_assign(cSPTransform*, const cSPTransform*);   // 0x537dc0
extern "C" int   __cdecl WStr_Format(wchar_t*, const wchar_t*, ...);                // 0x41e050
struct IRef;
extern "C" IRef* __cdecl FUN_00e61550();
extern "C" void  __cdecl FUN_00e627a0(int);
extern "C" void  __cdecl FUN_00e5bd30(void*);
extern "C" int   __cdecl EA_Hash_FNV1_String8(const char*, uint32_t, int);          // 0x932e80
extern "C" void* __cdecl SP_CreateEffectSafe(int, int, int, int);                   // 0x628450
extern "C" void  __cdecl FUN_00743b50(void*);
extern "C" void* __cdecl FUN_00b72210(void* p, int id);
extern "C" void* __cdecl FUN_0067de90(int, ...);
extern "C" void* __cdecl FUN_00ba54f0(int, ...);
extern "C" void* __cdecl FUN_007ec160(int, ...);
extern "C" void  __cdecl FUN_007eb820(int, ...);
extern "C" void  __cdecl FUN_00e82dc0(void*);
extern "C" void  __cdecl FUN_00e63400(void*);
extern "C" void  __cdecl EA_SetNumberString(int, int, wchar_t*, int);               // 0x881ae0
extern "C" void  __cdecl FUN_00a80dd0(void*, void*);                                // SimpleVector<CellData*> insert
extern "C" void  __cdecl FUN_004558a0(void*, void*);                                // SimpleVector<uint> insert
extern "C" void* __cdecl FUN_0099efa0(void*, void*, void*);
extern "C" void* __cdecl FUN_00e5c860(void*, void*, void*);
extern "C" void  __cdecl FUN_00e5c7d0(void*);
extern "C" void* __cdecl operator_new(uint32_t, const char*, int, int, const char*, int); // 0xf473a0
extern "C" void  __cdecl operator_delete(void*);                                    // 0xf47380

extern void* g_CellGame;              // cCellGame* stored at 0x16b3c04
extern void* g_CellGfx;               // cCellGfx*  stored at 0x16b3c08

#define CG(off) (*(void**)((char*)g_CellGame + (off)))
#define GFX(off) (*(void**)((char*)g_CellGfx + (off)))

// ================================================================ 00e63ac0
struct Cell;                          // {cSPTransform m0; cSPTransform m1; void* mpPart;} size 0x74
struct CellArray { Cell* begin; Cell* end; Cell* cap; };

// @ 0x00e63ac0
void __cdecl FUN_00e63ac0(CellArray* a) {
    int n = (int)(((char*)a->end - (char*)a->begin) / 0x74);
    for (int i = 0; i < n; ++i) {
        Cell* c = (Cell*)((char*)a->begin + i * 0x74);
        void* part = *(void**)((char*)c + 0x70);
        if (((VObj*)part)->v10() != 0) {
            sPartIntersectTarget(part, c, (char*)c + 0x38);
        } else {
            if (part) {
                *(void**)((char*)c + 0x70) = 0;
                ((RefObj*)part)->v2();
            }
            Cell* last = (Cell*)((char*)a->begin + (n - 1) * 0x74);
            cSPTransform_assign((cSPTransform*)c, (cSPTransform*)last);
            cSPTransform_assign((cSPTransform*)((char*)c + 0x38), (cSPTransform*)((char*)last + 0x38));
            void* lp = *(void**)((char*)last + 0x70);
            void* cp = *(void**)((char*)c + 0x70);
            if (lp != cp) {
                if (lp) ((RefObj*)lp)->v2();
                *(void**)((char*)c + 0x70) = lp;
                if (cp) ((RefObj*)cp)->v3();
            }
            a->end = (Cell*)((char*)a->end - 0x74);
            void* ep = *(void**)((char*)a->end + 0x70);
            if (ep) ((RefObj*)ep)->v3();
            --i; --n;
        }
    }
}

// ================================================================ 00e63bf0
// @ 0x00e63bf0
void __cdecl FUN_00e63bf0(int* pCell, int effKind, int* pEffect, uint16_t* xform, char create) {
    if (create) {
        if (*pEffect == 0) {
            uint32_t nameHash;
            if (*(int*)((char*)g_CellGame + 0x411c) == *pCell)
                nameHash = EA_Hash_FNV1_String8("cell_call_avatar", 0x811c9dc5, 1);
            else
                nameHash = EA_Hash_FNV1_String8("cell_call_mate", 0x811c9dc5, 1);
            SP_CreateEffectSafe(effKind, nameHash, 0, (int)pEffect);
            ((VObj*)*pEffect)->v02();
        }
        cSPTransform local;
        cSPTransform_assign(&local, (cSPTransform*)xform);
        if (*(int*)((char*)g_CellGame + 0x411c) != *pCell)
            FUN_00e5bd30(&local);
        sPartIntersectTarget((void*)*pEffect, (char*)pCell + 0xc0, &local);
    } else if (*pEffect) {
        ((VObj*)*pEffect)->v03();
        ((VObj*)*pEffect)->v01();
        *pEffect = 0;
    }
}

// ================================================================ 00e63d10
struct IRef { virtual int AddRef(); virtual int Release(); };
struct AutoRef {
    IRef* mpObject;
    AutoRef& operator=(IRef* p) {
        if (p != mpObject) {
            IRef* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
extern AutoRef g_16b3de0;

// @ 0x00e63d10
void __cdecl FUN_00e63d10(int arg) {
    g_16b3de0 = FUN_00e61550();
    FUN_00e627a0(arg);
}

// ================================================================ 00e63d60
struct PairIU { int a; uint32_t b; };
struct FixedVec8 {
    PairIU* mpBegin;
    PairIU* mpEnd;
    PairIU* mpCapacity;
    uint32_t mOverflowAllocator;
    PairIU* mpPoolBegin;
    void DoInsertValue(PairIU* position, const PairIU& value);
};

// @ 0x00e63d60
void FixedVec8::DoInsertValue(PairIU* position, const PairIU& value) {
    PairIU* pValue = const_cast<PairIU*>(&value);
    if (mpEnd != mpCapacity) {
        if (pValue >= position && pValue < mpEnd) ++pValue;
        *mpEnd = *(mpEnd - 1);
        PairIU* p = mpEnd;
        while (p != position) { --p; p[0] = p[-1]; }
        *position = *pValue;
        ++mpEnd;
    } else {
        uint32_t n = (uint32_t)(mpEnd - mpBegin);
        uint32_t nNew = n ? n * 2 : 1;
        PairIU* pNew = nNew ? (PairIU*)operator_new(nNew * 8, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        PairIU* pNewEnd = (PairIU*)FUN_0099efa0(mpBegin, position, pNew);
        if (pNewEnd) *pNewEnd = *pValue;
        PairIU* pEnd2 = (PairIU*)FUN_0099efa0(position, mpEnd, pNewEnd + 1);
        if (mpBegin && mpBegin != mpPoolBegin) operator_delete(mpBegin);
        mpBegin = pNew; mpEnd = pEnd2; mpCapacity = pNew + nNew;
    }
}

// ================================================================ 00e63e70
struct SoundElem {
    SoundElem& operator=(const SoundElem& o);   // out-of-line at 0xe5c7d0
    char raw[0x2c];
};
struct FixedVec44 {
    SoundElem* mpBegin;
    SoundElem* mpEnd;
    SoundElem* mpCapacity;
    uint32_t mOverflowAllocator;
    SoundElem* mpPoolBegin;
    void DoInsertValue(SoundElem* position, const SoundElem& value);
};

// @ 0x00e63e70
void FixedVec44::DoInsertValue(SoundElem* position, const SoundElem& value) {
    SoundElem* pValue = const_cast<SoundElem*>(&value);
    if (mpEnd != mpCapacity) {
        if (pValue >= position && pValue < mpEnd) ++pValue;
        if (mpEnd) FUN_00e5c7d0(mpEnd - 1);
        SoundElem* p = mpEnd;
        while (p != position) { --p; *p = p[-1]; }
        *position = *pValue;
        ++mpEnd;
    } else {
        uint32_t n = (uint32_t)(mpEnd - mpBegin);
        uint32_t nNew = n ? n * 2 : 1;
        SoundElem* pNew = nNew ? (SoundElem*)operator_new(nNew * 0x2c, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        SoundElem* pNewEnd = (SoundElem*)FUN_00e5c860(mpBegin, position, pNew);
        if (pNewEnd) FUN_00e5c7d0(pValue);
        SoundElem* pEnd2 = (SoundElem*)FUN_00e5c860(position, mpEnd, pNewEnd + 1);
        if (mpBegin && mpBegin != mpPoolBegin) operator_delete(mpBegin);
        mpCapacity = pNew + nNew; mpEnd = pEnd2; mpBegin = pNew;
    }
}

// ================================================================ 00e63f90
struct BigObj {
    virtual void v0();            // vtable at +0
    void Destroy();
};
// @ 0x00e63f90
void BigObj::Destroy() {
    (*(void(__fastcall**)(void*, int, int))0)(0, 0, 0);
}

// ================================================================ 00e64090
struct GfxObj {
    virtual void v0();
    void Destroy();
};
// @ 0x00e64090
void GfxObj::Destroy() {
    (*(void(__fastcall**)(void*, int))0)(0, 0);
}

// ================================================================ 00e642a0
// @ 0x00e642a0
void __cdecl SP_sUpdateDNAEffect(void* a1, int param2) {
    uint8_t* obj = (uint8_t*)operator_new(0x1c, "Simulator", 0, 0, 0, 0);
    if (obj) {
        *(int*)(obj + 0x4) = 0x013ef094;
        *(int*)(obj + 0x8) = 0;
        *(int*)(obj + 0x0) = 0x013f585c;
        *(int*)(obj + 0x4) = 0x013f5858;
        *(int*)(obj + 0xc) = 0x01667bac;
        *(int*)(obj + 0x10) = 0x01667bac;
        *(int*)(obj + 0x14) = 0x01667bae;
        (*(void(__fastcall**)(void*))(*(int*)obj))((void*)obj);
    } else {
        obj = 0;
    }
    if (param2 == 0) {
        WStr_Format((wchar_t*)(obj + 0xc), L"%lc%lc", 0x2b, 0x268b);
    } else {
        wchar_t buf[64];
        EA_SetNumberString(1, 0, buf, 0x40);
        ((uint16_t*)buf)[0x3e] = 0;
        WStr_Format((wchar_t*)(obj + 0xc), L"%lc%lc%ls", 0x268b, 0x2b, buf);
    }
    (*(void(__thiscall**)(void*, int, uint8_t*))(*(int*)a1 + 0x4c))((void*)a1, 8, obj);
    if (obj) (*(void(__fastcall**)(void*))(*(int*)obj + 4))((void*)obj);
}

// ================================================================ 00e64390
struct FmtObj {
    virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
    virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
    virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
    virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
    virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
    virtual int v20(); virtual int v21(); virtual int v22();
    uint8_t pad[0x8c];
    int mState;   // +0x90
    void Format(wchar_t* buf);
};
// @ 0x00e64390
void FmtObj::Format(wchar_t* buf) {
    if (mState != 0 && mState != 4 && mState != 5) {
        int a = v21();
        int b = v22();
        WStr_Format(buf, L"%d/%d", a, b);
    }
}

// ================================================================ 00e644e0
struct VecInsert44 {
    SoundElem* mpBegin;
    SoundElem* mpEnd;
    SoundElem* mpCapacity;
    uint32_t mOverflowAllocator;
    SoundElem* mpPoolBegin;
    SoundElem* insert(SoundElem* position, const SoundElem& value);
};
// @ 0x00e644e0
SoundElem* VecInsert44::insert(SoundElem* position, const SoundElem& value) {
    int idx = (int)(position - mpBegin);
    SoundElem* pEnd = mpEnd;
    if (position == pEnd && pEnd != mpCapacity) {
        mpEnd = pEnd + 1;
        if (pEnd) pEnd->operator=(value);
    } else {
        ((FixedVec44*)this)->DoInsertValue(position, value);
    }
    return mpBegin + idx;
}

// ================================================================ 00e64980
struct Gfx58 {
    virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
    virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
    virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
    virtual int v12(void*, int, void*, void*, int);
};
struct CellData;
struct SimpleVec { CellData** mpBegin; CellData** mpEnd; CellData** mpCapacity;
                   void DoInsertValue(CellData** position, CellData*& value); };
struct CellGfxObj {
    uint8_t pad0[0x28];
    SimpleVec mVector;        // +0x28
    uint8_t pad2[0x58 - 0x28 - 0xc];
    Gfx58* mpAt58;            // +0x58
};
// @ 0x00e64980
void __cdecl FUN_00e64980(int param1) {
    int local[3];
    local[0] = param1;
    local[1] = 0x3d97a8e4;
    local[2] = *(int*)0x015a7d0c;
    CellGfxObj* gfx = (CellGfxObj*)g_CellGfx;
    CellData* r = (CellData*)gfx->mpAt58->v12(local, 2, (void*)0x016b3c28, (void*)0x015a7c4c, 1);
    if (r) {
        SimpleVec* v = &gfx->mVector;
        if (v->mpEnd < v->mpCapacity) {
            *v->mpEnd = r;
            v->mpEnd = v->mpEnd + 1;
        } else {
            v->DoInsertValue(v->mpEnd, r);
        }
    }
}

// ================================================================ 00e645b0
struct TreeObj {
    char pad0[4];
    void* InsertNode(char isHint, void* hint, int* pParent, int* pValue, char unused);
};
// @ 0x00e645b0
void* TreeObj::InsertNode(char isHint, void* hint, int* pParent, int* pValue, char unused) {
    (void)isHint; (void)hint; (void)pParent; (void)unused;
    return pValue;
}

// ================================================================ 00e646d0
// @ 0x00e646d0
void* __fastcall FUN_00e646d0(void* self) {
    *(int*)self = 0;
    FUN_00743b50((char*)self + 0x1c);
    FUN_00743b50((char*)self + 0x38);
    FUN_00743b50((char*)self + 0x54);
    *(int*)((char*)self + 0x74) = (int)((char*)self + 0x74);
    *(int*)((char*)self + 0x78) = (int)((char*)self + 0x74);
    *(int*)((char*)self + 0x7c) = 0;
    *(uint8_t*)((char*)self + 0x80) = 0;
    *(int*)((char*)self + 0x84) = 0;
    FUN_00743b50((char*)self + 0x8c);
    FUN_00743b50((char*)self + 0xa8);
    FUN_00743b50((char*)self + 0xc4);
    FUN_00743b50((char*)self + 0x168);
    return self;
}

// ================================================================ 00e647d0
// @ 0x00e647d0
void* __fastcall FUN_00e647d0(void* self) {
    for (int i = 0; i < 0x5c; i += 4) *(int*)((char*)self + i) = 0;
    FUN_00743b50((char*)self + 0x168);
    return self;
}

// ================================================================ 00e648d0
// @ 0x00e648d0
void FUN_00e648d0() { }

// ================================================================ 00e643e0
// @ 0x00e643e0
void __cdecl FUN_00e643e0(int id) {
    void* cell = FUN_00b72210((char*)g_CellGame + 0x1c, id);
    void* a = *(void**)((char*)cell + 0xfc);
    void* b = *(void**)((char*)cell + 0x100);
    void* c = *(void**)((char*)cell + 0x104);
    if (a && a != *(void**)((char*)CG(0x5190) + 0x10)) {
        void* r = FUN_0067de90(7, a, b, c);
        (void)r;
    }
}
