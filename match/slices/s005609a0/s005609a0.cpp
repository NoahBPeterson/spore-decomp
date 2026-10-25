// Slice s005609a0: SP::cSPObjectTemplateDB asset registration, OTDB jobs and the
// cEditorResource-backed resource wrapper emitted in this module.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s0055ce80/s0055ce80.h"

namespace SP {

struct EcxStub9a {
    int FUN_00560c30(void* pKey);
    bool FUN_00560d20(void* other);
    void* FUN_00561090_();
    void FUN_005611b0();
    bool FUN_005609a0(void* pKey, char flag);
    bool FUN_00560d60(void* job);
    void FUN_00561220(void* pData);
    bool FUN_00561340(void* pKey);
};


void __fastcall FUN_0048c720(void* vec, int reserved, void* item);
void __fastcall FUN_00564820(void* vec, int reserved);
void __fastcall FUN_00571680(void* self, int reserved);
void FUN_00571640(void* p);
void FUN_00429360(void* p);
void FUN_005688f0(void* a, void* b, void* c, void* d);
void FUN_005643e0(void* it);
bool FUN_0055c6f0(void* a, void* b, void* c);
bool FUN_0055cd90(void* key, void* vec, void* feat);
void FUN_0068f9b0(void* p);
void FUN_00564470(void* p);
void __fastcall FUN_005156b0(void* self, int reserved, void* owner);
void FUN_00564960(void* out, void* val);
void FUN_0041d940();
void* FUN_0068f4d0();
void FUN_006909b0();
void FUN_005641a0(void* p);
void FUN_005631e0(void* self, void* out);
void FUN_00562280(void* self, void* c);
void FUN_004769b0(void* a, void* b);
void FUN_00555980(void* out, void* key);
void FUN_00561970(int index);
void FUN_00565040(void* out, void* val);
void* OPERATOR_NEW_OTDB(int size, const char* name, int a, int b, int c, int d);
void* FUN_005688f0_();

// ---- stub types for the OTDB job / editor-resource / map helpers --------------
typedef bool (__thiscall *GetRes0cFn)(void* self, const void* key, void** out,
                                      int a, int b, int c, int d);
typedef void (__thiscall *SendFn)(void* self, uint32_t id, void* data, int flags);

struct JobRef54 { void* p; JobRef54* Reset(); };                        // 0x0041d940
struct Job54 {
    void* mVtbl;        // +0x00
    void* mField4;      // +0x04
    char  pad08[0x10];
    int   mField18;     // +0x18
    int  Release();                        // 0x00690120
    void SetData(void* p);                 // 0x0068f9b0
    int  GetStatus();                      // 0x006909b0
};
struct JobMgr54 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual bool Accept(JobRef54* ref);    // vtable +0x10
};
struct Pollinator54 { void PostAddPending(void* p); };                  // 0x00610d40
struct EditorRes54 { virtual int v0(); virtual int v1(); };
struct Sub1c54 { int mPad; void init(void* p); };                      // 0x005641a0
struct FeatVec54 { void ctor(); void clear(); void dtor(); };          // 0x00571640/0x00571680/0x00564470
struct Guard54 { int mPad; void ctor(void* p); };                      // 0x00429360
struct VecBase54 { int mPad; void destroy(); };                        // 0x005156b0
struct VecCopy54 { int mPad; void copyFrom(const void* src); };        // 0x0050d440
struct VecDestroy54 { int mPad; void destroy(); };                     // 0x00553fb0
struct VecRange54 { int mPad; void insert_range(void* pos, void* first, void* last, char flag); };
struct VecErase54 { int mPad; void* erase(void* pos); };               // 0x005643e0
struct Map54 { int mPad; void equal_range(void* out, const void* key); };
struct MapIter54 { int mPad; void* get(); void increment(); };         // 0x00564f50 / 0x00422c50
struct VecSet54 { int mPad; void* insert(void* out, const void* value); };  // 0x00554020
struct TraitData54 { int mPad; void Blend(bool use, void* asset, uint32_t value); };  // 0x005708d0
struct DeclareParam54 { uint32_t mParameter, mType, mValue; void ctor(uint32_t id, uint32_t value); };
struct SpVec54 { int mPad; void push_back(const void* value); };       // 0x004e19a0
struct Vec12_54 { void* mpBegin; void* mpEnd; void* mpCap; };
struct ItPair54 { void* first; void* second; };
struct PairUU54 { uint32_t first; uint32_t second; };
struct IterBool54 { void* first; uint32_t second; };
struct ResourceKey54 { uint32_t mInstanceID, mTypeID, mGroupID; };
struct AssetMsg54 { uint32_t mCount; ResourceKey54 mKey; void* mpBegin; void* mpEnd; };
struct FloatVec54 { float mX, mY, mZ; int mPad; void destroy(); };     // 0x004e1bf0
struct Entry12_54 { uint32_t mA, mB, mC; };
struct DBLookup54 {
    int  FindAssetIndex(const void* key);      // 0x005631e0
    void DecreasePopulation(int index);        // 0x00561970
    char FUN_0055d790(int index, void* list);  // 0x0055d790
    char FUN_0055d230(int index, void* list);  // 0x0055d230
};

void* SP_GetPollinator();                               // 0x0067cb30
void* SP_MessageServer();                               // 0x0067dcc0
void* OTDB_InterfaceCast(void* ref);                    // 0x00421eb0
void  OTDB_GetPartVolumePercentages(void* res, void* out);  // 0x0056a5f0
char  OTDB_IntersectWeights(void* asset, void* weights);    // 0x00571530


// @ 0x005609a0  (large OTDB driver)
bool EcxStub9a::FUN_005609a0(void* pKey, char flag)
{
    void* this_ = this;
    if (flag != 0) {
        ((Pollinator54*)SP_GetPollinator())->PostAddPending(pKey);
    }
    int index = ((DBLookup54*)this_)->FindAssetIndex(pKey);
    if (index == -1)
        return false;

    char* asset = (char*)(index * 0x50 + *(int*)((char*)this_ + 0x14));
    ((DBLookup54*)this_)->DecreasePopulation(index);

    uint32_t value = 0;
    ItPair54 mapIt;
    ((Map54*)((char*)this_ + 0xdc))->equal_range(&mapIt, (char*)pKey + 4);
    void* it = (mapIt.first != mapIt.second) ? mapIt.first
                                             : *(void**)((char*)this_ + 0xe0);
    if (it != *(void**)((char*)this_ + 0xe0)) {
        value = *(uint32_t*)((char*)it + 4);
    }
    ((TraitData54*)((char*)this_ + 0x174))->Blend(false, asset + 0x10, value);

    IterBool54 ins;
    void* insPair = ((VecSet54*)((char*)this_ + 0x28))->insert(&ins, &index);
    if (!*(char*)((char*)insPair + 4))
        return false;

    ResourceKey54 key = *(ResourceKey54*)pKey;
    key.mTypeID = 0x2d5c9af;
    Vec12_54 params;
    params.mpBegin = 0;
    params.mpEnd = 0;
    params.mpCap = 0;
    if (!FUN_0055cd90(&key, &params, 0))
        goto cleanup;

    ((DBLookup54*)this_)->FUN_0055d790(index, &params);
    {
        void* mgr = *(void**)0x015e3f00;
        const void* res = ((const void* (__thiscall*)(void*, const void*))
                           (*(void***)mgr)[0x58 / 4])(mgr, &key);
        if (res != 0) {
            int resFlags = ((int (__thiscall*)(void*))(*(void***)res)[0x20 / 4])((void*)res);
            if ((resFlags & 2) != 0) {
                ((void (__thiscall*)(void*, const void*))
                 (*(void***)res)[0x40 / 4])((void*)res, &key);
            }
        }
    }
    {
        ResourceKey54 key2 = *(ResourceKey54*)pKey;
        key2.mTypeID = 0x2d5c9af;
        void* ref = 0;
        if (ref != 0) {
            void* old = ref;
            ref = 0;
            ((void (__thiscall*)(void*))(*(void***)old)[1])(old);
        }
        void* mgr = *(void**)0x015e3f00;
        bool got = ((GetRes0cFn)(*(void***)mgr)[0x14 / 4])(mgr, &key2, &ref, 0, 0, 0, 0);
        if (got && ref != 0) {
            ((void (__thiscall*)(void*, void*, int))(*(void***)mgr)[0x6c / 4])(mgr, ref, 0);
        }
        ((FeatVec54*)(asset + 0x10))->clear();
        if (ref != 0) {
            void* old = ref;
            ref = 0;
            ((void (__thiscall*)(void*))(*(void***)old)[1])(old);
        }
    }

cleanup:
    char result = 1;
    for (char* p = (char*)params.mpBegin; p < (char*)params.mpEnd; p += 0xc) {
    }
    ((VecBase54*)&params)->destroy();
    return result != 0;
}

// @ 0x00560c30
int EcxStub9a::FUN_00560c30(void* pKey) {
    void* this_ = this;
    int index = -1;
    if (!((DBSub*)((char*)this_ + 0x28))->GetResType()) {
        index = **(int**)((char*)this_ + 0x28);
        FUN_0048c720((char*)this_ + 0x28, 0, *(void**)((char*)this_ + 0x28));
    } else {
        index = (int)((*(int*)((char*)this_ + 0x18) - *(int*)((char*)this_ + 0x14)) / 0x50);
        FUN_00564820((char*)this_ + 0x14, 0);
    }
    char* asset = (char*)(index * 0x50 + *(int*)((char*)this_ + 0x14));
    *(uint32_t*)(asset + 0) = ((uint32_t*)pKey)[0];
    *(uint32_t*)(asset + 4) = ((uint32_t*)pKey)[1];
    *(uint32_t*)(asset + 8) = ((uint32_t*)pKey)[2];
    *(uint32_t*)(asset + 0xc) = 0xffffffff;
    FUN_00571680(asset + 0x10, 0);
    *(uint32_t*)(asset + 0x48) = 0xffffffff;
    *(uint32_t*)(asset + 0x4c) = 0xffffffff;
    return index;
}

// @ 0x00560d20
bool EcxStub9a::FUN_00560d20(void* other) {
    void* this_ = this;
    if (*(uint32_t*)this_ != *(uint32_t*)other)
        return false;
    if (*(uint32_t*)((char*)this_ + 8) != *(uint32_t*)((char*)other + 8))
        return false;
    return true;
}

// @ 0x00560d60
bool EcxStub9a::FUN_00560d60(void* job)
{
    void* this_ = this;
    Vec12_54 vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCap = 0;
    Guard54 guard;
    char guardArg;
    guard.ctor(&guardArg);
    FeatVec54 features;
    features.ctor();
    char result = 0;

    ResourceKey54 key = *(ResourceKey54*)((char*)this_ + 0xc);
    key.mTypeID = 0x2d5c9af;
    if (FUN_0055cd90(&key, &vec, &features)) {
        if (*(char*)((char*)this_ + 0x2c) != 0) {
            char rangeFlag;
            ((VecRange54*)&vec)->insert_range(vec.mpEnd,
                                             *(void**)((char*)this_ + 0x18),
                                             *(void**)((char*)this_ + 0x1c),
                                             rangeFlag);
        } else {
            for (char* it = (char*)vec.mpBegin; it != (char*)vec.mpEnd; ) {
                void* endList = *(void**)((char*)this_ + 0x1c);
                char* found = *(char**)((char*)this_ + 0x18);
                while (found != (char*)endList &&
                       !((EcxStub9a*)found)->FUN_00560d20(it)) {
                    found += 0xc;
                }
                if (found == (char*)endList)
                    it += 0xc;
                else
                    it = (char*)((VecErase54*)&vec)->erase(it);
            }
        }
        result = FUN_0055c6f0((char*)this_ + 0xc, &vec, &features);
    }
    ((Job54*)job)->SetData(0);
    char res = result;
    features.dtor();
    for (char* p = (char*)vec.mpBegin; p < (char*)vec.mpEnd; p += 0xc) {
    }
    ((VecBase54*)&vec)->destroy();
    return res != 0;
}

// @ 0x00560f20
void FUN_00560f20(void* pKey, void* pList, char flag)
{
    JobRef54 ref;
    ref.p = 0;
    JobMgr54* mgr = (JobMgr54*)FUN_0068f4d0();
    if (!mgr->Accept(ref.Reset())) {
        if (ref.p != 0) {
            ((Job54*)ref.p)->Release();
        }
        return;
    }

    void* res = 0;
    void* mem = OPERATOR_NEW_OTDB(0x34, "OTDB", 0, 0, 0, 0);
    if (mem != 0) {
        res = ((EcxStub9a*)mem)->FUN_00561090_();
    }
    if (res != 0) {
        ((EditorRes54*)res)->v0();
    }
    *(int*)((char*)ref.p + 0x18) = 4;
    void* sub = (res != 0) ? (char*)res + 4 : 0;
    *(void**)ref.p = (void*)0x68f5a0;
    *(void**)((char*)ref.p + 4) = sub;
    ((Job54*)ref.p)->SetData(res);
    *(ResourceKey54*)((char*)res + 0x10) = *(ResourceKey54*)pKey;
    ((Sub1c54*)((char*)res + 0x1c))->init(pList);
    *(char*)((char*)res + 0x30) = flag;
    ((Job54*)ref.p)->GetStatus();
    if (res != 0) {
        ((EditorRes54*)res)->v1();
    }
    if (ref.p != 0) {
        ((Job54*)ref.p)->Release();
    }
}

namespace Editor { struct cEditorResource { }; }

// @ 0x00561090
void* EcxStub9a::FUN_00561090_() {
    void* this_ = this;
    *(void**)this_ = (void*)0x13eb938;
    *(void**)this_ = (void*)0x13f1ab0;
    *(void**)((char*)this_ + 4) = (void*)0x140b5a0;
    *(void**)((char*)this_ + 8) = (void*)0x13ef094;
    *(void**)((char*)this_ + 0xc) = 0;
    *(void**)this_ = (void*)0x13f4b00;
    *(void**)((char*)this_ + 4) = (void*)0x13f4afc;
    *(void**)((char*)this_ + 8) = (void*)0x13f4af8;
    *(void**)((char*)this_ + 0x10) = 0;
    *(void**)((char*)this_ + 0x14) = 0;
    *(void**)((char*)this_ + 0x18) = 0;
    *(void**)((char*)this_ + 0x1c) = 0;
    *(void**)((char*)this_ + 0x20) = 0;
    *(void**)((char*)this_ + 0x24) = 0;
    return this_;
}

// @ 0x00561150  (small virtual returning false)
struct CEditorResourceThunk {
    virtual int f(void* p);
};
int CEditorResourceThunk::f(void* p) {
    (void)p;
    return 0;
}

// @ 0x005611b0
void EcxStub9a::FUN_005611b0() {
    void* this_ = this;
    *(void**)this_ = (void*)0x13f4b00;
    *(void**)((char*)this_ + 4) = (void*)0x13f4afc;
    *(void**)((char*)this_ + 8) = (void*)0x13f4af8;
    char* v = (char*)this_ + 0x1c;
    for (char* it = *(char**)v; it < *(char**)(v + 4); it += 0xc) {
    }
    FUN_005156b0(v, 0, this_);
    *(void**)((char*)this_ + 8) = (void*)0x13ef094;
    *(void**)this_ = (void*)0x13eb938;
}

// @ 0x00561220
void EcxStub9a::FUN_00561220(void* pData)
{
    void* this_ = this;
    int index = ((DBLookup54*)this_)->FindAssetIndex((char*)pData + 8);
    if (index == -1)
        return;

    Vec12_54 params;
    params.mpBegin = 0;
    params.mpEnd = 0;
    params.mpCap = 0;
    DeclareParam54 param;
    param.ctor(0x3cc89b1, *(uint32_t*)pData);
    ((SpVec54*)&params)->push_back(&param);

    if (*(int*)((char*)pData + 4) <= 0) {
        ((DBLookup54*)this_)->FUN_0055d790(index, &params);
        FUN_00560f20((char*)pData + 8, &params, 0);
    } else {
        ((DBLookup54*)this_)->FUN_0055d230(index, &params);
        FUN_00560f20((char*)pData + 8, &params, 1);
    }
    void* srv = SP_MessageServer();
    ((SendFn)(*(void***)srv)[0x14 / 4])(srv, 0x64e5bda, pData, 0);

    for (char* p = (char*)params.mpBegin; p < (char*)params.mpEnd; p += 0xc) {
    }
    ((VecBase54*)&params)->destroy();
}

// @ 0x00561340  (large)
bool EcxStub9a::FUN_00561340(void* pKey)
{
    void* this_ = this;
    ItPair54 iters;
    ((Map54*)((char*)this_ + 0x1ec))->equal_range(&iters, (char*)pKey + 4);
    if (iters.first == iters.second)
        return false;

    Vec12_54 params;
    params.mpBegin = 0;
    params.mpEnd = 0;
    params.mpCap = 0;
    Guard54 guard;
    char guardArg;
    guard.ctor(&guardArg);

    char cont = 1;
    while (cont && iters.first != iters.second) {
        void* obj = *(void**)((char*)((MapIter54*)&iters.first)->get() + 4);
        cont = cont ? (((bool (__thiscall*)(void*, void*, void*))
                        (*(void***)obj)[0x20 / 4])(obj, pKey, &params) ? 1 : 0) : 0;
        ((MapIter54*)&iters.first)->increment();
    }

    if (cont) {
        int index = ((EcxStub9a*)this_)->FUN_00560c30(pKey);
        char* asset = (char*)(*(int*)((char*)this_ + 0x14) + index * 0x50 + 0x10);

        ItPair54 it2;
        ((Map54*)((char*)this_ + 0x208))->equal_range(&it2, (char*)pKey + 4);
        if (it2.first != it2.second) {
            void* mgr = EA::ResourceMan::GetManager();
            void* ref = 0;
            if (mgr != 0) {
                if (ref != 0) {
                    void* old = ref;
                    ref = 0;
                    ((void (__thiscall*)(void*))(*(void***)old)[1])(old);
                }
                bool got = ((GetRes0cFn)(*(void***)mgr)[0xc / 4])(mgr, pKey, &ref,
                                                                0, 0, 0, 0);
                if (got) {
                    void* res = OTDB_InterfaceCast(&ref);
                    if (res != 0) {
                        FloatVec54 fv;
                        fv.mX = 0.0f;
                        fv.mY = 0.0f;
                        fv.mZ = 0.0f;
                        Guard54 guard2;
                        char guardArg2;
                        guard2.ctor(&guardArg2);
                        OTDB_GetPartVolumePercentages(res, &fv);
                        while (cont && it2.first != it2.second) {
                            void* obj2 = *(void**)((char*)((MapIter54*)&it2.first)->get() + 4);
                            cont = cont ? (((bool (__thiscall*)(void*, void*, void*, void*))
                                            (*(void***)obj2)[0x1c / 4])(obj2, res, &fv, asset) ? 1 : 0) : 0;
                            ((MapIter54*)&it2.first)->increment();
                        }
                        char inter = OTDB_IntersectWeights(asset, (char*)this_ + 0x240);
                        (void)inter;
                        fv.destroy();
                    }
                }
                if (ref != 0) {
                    void* old = ref;
                    ref = 0;
                    ((void (__thiscall*)(void*))(*(void***)old)[1])(old);
                }
            }
        }

        if (cont && FUN_0055c6f0(pKey, &params, asset) &&
            ((DBLookup54*)this_)->FUN_0055d230(index, &params)) {
            ((cSPObjectTemplateDB*)this_)->FUN_00561850(index);

            uint32_t value = 0;
            void* mapEnd = *(void**)((char*)this_ + 0xe0);
            ItPair54 it3;
            ((Map54*)((char*)this_ + 0xdc))->equal_range(&it3, (char*)pKey + 4);
            void* it = (it3.first != it3.second) ? it3.first : mapEnd;
            if (it != mapEnd) {
                value = *(uint32_t*)((char*)it + 4);
            }
            ((TraitData54*)((char*)this_ + 0x174))->Blend(true, asset, value);

            void* srv = SP_MessageServer();
            AssetMsg54 msg;
            msg.mKey.mInstanceID = 0;
            msg.mKey.mTypeID = 0;
            msg.mKey.mGroupID = 0;
            msg.mCount = 1;
            msg.mKey = *(ResourceKey54*)pKey;
            msg.mpBegin = params.mpBegin;
            msg.mpEnd = params.mpEnd;
            for (Entry12_54* e = (Entry12_54*)params.mpBegin;
                 e != (Entry12_54*)params.mpEnd; ++e) {
                if (e->mA == 0x3cc89b1) {
                    uint32_t paramValue = e->mC;
                    ((SendFn)(*(void***)srv)[0x14 / 4])(srv, 0x64e5bda, &paramValue, 0);
                }
            }
            char ok = 1;
            for (char* p = (char*)params.mpBegin; p < (char*)params.mpEnd; p += 0xc) {
            }
            ((VecBase54*)&params)->destroy();
            return ok != 0;
        }

        IterBool54 ins;
        ((VecSet54*)((char*)this_ + 0x28))->insert(&ins, &index);
    }

    for (char* p = (char*)params.mpBegin; p < (char*)params.mpEnd; p += 0xc) {
    }
    ((VecBase54*)&params)->destroy();
    return false;
}

// @ 0x00561850
void cSPObjectTemplateDB::FUN_00561850(int index)
{
    char* asset = (char*)(index * 0x50 + *(int*)((char*)this + 0x14));
    Vec12_54 list;
    ((VecCopy54*)&list)->copyFrom(asset + 0x2c);
    for (uint32_t* it = (uint32_t*)list.mpBegin; it != (uint32_t*)list.mpEnd; ++it) {
        PairUU54 val;
        val.first = *it;
        val.second = 1;
        IterBool54 res;
        ((DBSub*)((char*)this + 0xac))->Insert(&res, &val);
        if (res.second == 0) {
            ++*(int*)((char*)res.first + 4);
        }
    }
    PairUU54 val2;
    val2.first = *(uint32_t*)(asset + 4);
    val2.second = 1;
    IterBool54 res2;
    ((DBSub*)((char*)this + 0xdc))->Insert(&res2, &val2);
    if (res2.second == 0) {
        ++*(int*)((char*)res2.first + 4);
    }
    ((VecDestroy54*)&list)->destroy();
}

}
