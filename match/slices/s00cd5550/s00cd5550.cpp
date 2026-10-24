// Slice s00cd5550 -- SP::cTribeModeStrategy serialisation / tutorial / effect helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---- stream / IO -------------------------------------------------------------
struct Stream;                      // EA::IO::IStream-like, slots 0x18/0x1c/0x20
struct StreamInner {                // result of slot 0x20, slot 0x18 gives the write target
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual void a3(); virtual void a4(); virtual void a5();
    virtual void* Write_18();       // 0x18
};
struct Stream {
    virtual void k0(); virtual void k1(); virtual void k2(); virtual void k3();
    virtual void k4(); virtual void k5(); virtual void k6();
    virtual void End_1c();          // 0x1c
    virtual StreamInner* Get_20();  // 0x20
};
struct RefObj {                     // simple refcounted: AddRef slot 0, Release slot 1
    virtual void AddRef(); virtual void Release();
};
struct RefMgr {                     // AddRef slot 1, Release slot 2, Update slot 7(0x1c); size 0x98
    RefMgr();
    void* operator new(size_t n, const char* tag, int a, int b, int c, int d);
    virtual void v0(); virtual void AddRef(); virtual void Release();
    virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void Update_1c();       // 0x1c
    virtual void SendMsg_20();      // 0x20
    uint32_t pad[0x25];             // +0x24..+0x97  (vptr 4 + 0x94 = 0x98)
};
struct RefC20 {                     // Release slot 1
    virtual void v0(); virtual void Release();
};

struct cSPVector3 { float x, y, z; };

// ---- globals -----------------------------------------------------------------
extern unsigned char g_vt14774c4;      // 0x014774c4 element vtable
extern const float   g_fltmax;         // 0x01477430
extern const float   g_flt_158133c;    // 0x0158133c
extern const float   g_flt_1473c70;    // 0x01473c70
extern const float   g_flt_1486110;    // 0x01486110
extern const float   g_flt_15812dc;    // 0x015812dc
extern float         g_1559bdc[];      // 0x01559bdc float table (stride 2 floats)
extern const cSPVector3 g_v3_169b360;  // 0x0169b360
extern const cSPVector3 g_v3_169b36c;  // 0x0169b36c
extern void*         g_169b054;        // 0x0169b054 SimSingleton
extern unsigned char g_rand_1601760[];  // 0x01601760 random LCG
extern void*         g_157f290;        // 0x0157f290
extern const char    g_StrSimulator[];     // 0x013f09b4 "Simulator"
extern const char    g_StrSimSingleton[];  // 0x0145f924 "Simulator/SimSingleton"

// ---- callees -----------------------------------------------------------------
bool  EA_IO_WriteUint32(void* inner, const uint32_t* p, int count, int flags); // 0x0093aa70
void* EA_operator_new(uint32_t size, const char* tag, int a, int b, int c, int d); // 0x00f473a0
void  EA_Messaging_RemoveHandler(void* h, void* a, void* b, void* c, void* d);  // 0x00571db0
void* NounManager();                                 // 0x00b3d300
void* PropertyManager();                             // 0x0067de30
void* GonzagoModelWorld();                           // 0x00b3d520
void* EffectsManagerPtr();                           // 0x0067ddd0
void* GetSetting9();                                 // 0x00401090
void* FUN_004df420(void* p);                         // 0x004df420
void* FUN_01021260();                                // 0x01021260
void* FUN_01021230();                                // 0x01021230
void* FUN_00c8b370(void* self, uint32_t hash, void* out); // 0x00c8b370
void* FUN_00c713e0(void* self, int a, int b);        // 0x00c713e0
void* PlanetModel();                                 // 0x00b3d350
void  FUN_00b8d8a0(void* self, void* a, int b, int c);        // 0x00b8d8a0
void* Property_GetUInt(void* prop);                  // 0x0041ea00
void* interface_cast_0xd1c610(void* p, int a);       // 0x00d1c610
void* FUN_00d1e660();                                // 0x00d1e660
float SP_GetPropertyT_float(void* props, uint32_t hash, float def); // 0x004e1c70
void* FUN_0059aed0(float* out, const void* a, const void* b); // 0x0059aed0
void* FUN_00b3d2b0(int a);                           // 0x00b3d2b0
void* cGroundEditorRes_getContainer(void* p);        // 0x00ac79d0
void* FUN_00ac7ab0(void* self, float f, void* container, int mode); // 0x00ac7ab0
uint32_t RandomUint32Uniform(void* self, uint32_t n); // 0x00a68fb0
void  FUN_00cd3b60(void* self);                      // ctor
struct SimSingleton { void* Init(); };                  // 0x00cc5a70 ctor helper (returns this)
struct C20Obj { void clear(); };                       // 0x007b1950 ?clear@C20
struct cTribeDisplayStrategy { void Deactivate(); };   // 0x00ccd050
struct Obj1c8 { void Method(); };                       // 0x00bc21c0
void* FUN_0067cac0(void);                            // 0x0067cac0  returns g_15fcc54
void  FUN_0067c830(void* self, uint32_t hash);       // 0x0067c830  thiscall, ret 4
void* SP_GetCamRotateTrigger();                      // 0x00cd3e60
void  FUN_00b706a0(void* self, uint32_t hash);       // 0x00b706a0 (thiscall ret 4)
void* FUN_0067de90(int a);                           // 0x0067de90
void* FUN_007eb100(void* self);                      // 0x007eb100
unsigned char FUN_00c8e850(void* self);              // 0x00c8e850
unsigned char FUN_00c8e870(void* self);              // 0x00c8e870
void* SP_normalized_safe(cSPVector3* out, const cSPVector3* in); // 0x00449c20
void  XformMsg_ctor(void* self);                     // 0x00434040
void* SP_QuaternionToMatrix(float* out, const void* q); // 0x004a9b40
uint32_t SP_cTribe_GetAdultPopulation(void* tribe);  // 0x00c8f3a0
uint32_t SP_cTribe_GetMaxPopulation(void* tribe);    // 0x00c8eae0
void  DoFreeNodes_removed();                         // unused placeholder

class cVarListSerializer {
public:
    uint32_t mData[0x26e];
    cVarListSerializer(void* varList, void* a, int b);  // 0x00692f90
    bool Serialize(Stream* s);                          // 0x00692900
};

// big tribe-mode object: only the fields this slice touches are named.
void* SP_cGameNounManager_GetPlayerTribe(void* self); // 0x00bfc5f0
void* SP_cCommunity_GetLeader(void* self);           // 0x00c00650
unsigned char FUN_00cd44a0(void* self);             // 0x00cd44a0  TerrainNotHasKey, thiscall -> char
void* FUN_00ac79d0(void* self);                      // 0x00ac79d0
uint32_t SP_RandomUint32Uniform(void* self, uint32_t n); // 0x00a68fb0
void  SP_NormalizedSafe(cSPVector3* out, const cSPVector3* in); // 0x00449c20
void* SP_QuaternionToMatrix(void* out, const void* q); // 0x004a9b40
void* SP_EffectsManager();                           // 0x0067ddd0

struct cTribe {
    uint32_t GetAdultPopulation();   // 0x00c8f3a0  thiscall
    uint32_t GetMaxPopulation();     // 0x00c8eae0  thiscall
};
struct cGameNounManager {
    void* GetPlayerTribe();          // 0x00bfc5f0  thiscall, no args
};

class cTribeModeStrategy {
public:
    uint32_t pad00[8];             // +0x00..+0x1f
    unsigned char* mTribePathsBegin; // +0x20  (vector<path> begin)
    unsigned char* mTribePathsEnd;   // +0x24
    uint32_t pad28[6];             // +0x28..+0x3f
    unsigned char* mPtr_40;        // +0x40
    unsigned char* mPtr_44;        // +0x44
    uint32_t pad48[0x60];          // +0x48..+0x1c7
    void* mp_1c8;                  // +0x1c8
    void* mp_1cc;                  // +0x1cc  (first RemoveHandler arg)
    void* mp_1d0;                  // +0x1d0
    void* mp_1d4;                  // +0x1d4
    void* mp_1d8;                  // +0x1d8
    void* mp_1dc;                  // +0x1dc
    uint32_t pad1e0[0x12];         // +0x1e0..+0x227
    unsigned char mb_228;          // +0x228
    unsigned char pad229[0x13];    // +0x229..+0x23b
    void* mp_23c;                  // +0x23c
    void* mp_240;                  // +0x240
    uint32_t pad244[4];            // +0x244..+0x253
    void* mp_254;                  // +0x254
    uint32_t pad258[0x4f];         // +0x258..+0x393
    void* mp_394;                  // +0x394  mission manager / next strategy
    void* mp_398;                  // +0x398  effect object
    uint32_t pad39c[1];            // +0x39c..+0x39f
    unsigned char pad3a0[3];       // +0x3a0..+0x3a2
    unsigned char mb_3a3;          // +0x3a3

    unsigned char F_cd5550();
    bool          Write(Stream* s);
    void          F_cd56e0();
    int           F_cd5750();
    unsigned char TerrainNotHasKey();   // 0x00cd44a0  thiscall (external, other slice)
    bool          F_cd5e40();
    void          F_cd6390(unsigned char enable);
    void          F_cd6130(uint32_t id);
};

// @ 0x00cd5550
unsigned char cTribeModeStrategy::F_cd5550()
{
    if (mPtr_40 != mPtr_44)
        return *(mPtr_44 - 4) + 0 * (int)(size_t)mPtr_44;
    return 0;
}

// path element (0x14 bytes) holding a vector of points
struct TribePath {
    unsigned char* mpBegin;  // +0x00
    unsigned char* mpEnd;    // +0x04
    unsigned char* mpCap;    // +0x08
    uint32_t mExtra[2];      // +0x0c
};

// @ 0x00cd5570
bool cTribeModeStrategy::Write(Stream* s)
{
    unsigned char* w = (unsigned char*)this - 0xc;   // cVarList base subobject (object-0x0c)
    uint32_t tag = 0x116dd1b;
    StreamInner* inner = s->Get_20();
    EA_IO_WriteUint32(inner->Write_18(), &tag, 1, 0);
    cVarListSerializer ser(w, &g_157f290, 0x1a80d26);
    bool ok = ser.Serialize(s);
    if (ok) {
        uint32_t nPaths = (uint32_t)((mTribePathsEnd - mTribePathsBegin) / 0x14);
        inner = s->Get_20();
        EA_IO_WriteUint32(inner->Write_18(), &nPaths, 1, 0);
        if (nPaths != 0) {
            uint32_t off = 0;
            uint32_t cnt = nPaths;
            for (;;) {
                TribePath* path = (TribePath*)(mTribePathsBegin + off);
                uint32_t nPts = (uint32_t)((path->mpEnd - path->mpBegin) / 0xc);
                inner = s->Get_20();
                EA_IO_WriteUint32(inner->Write_18(), &nPts, 1, 0);
                if (nPts != 0) {
                    uint32_t j = 0;
                    uint32_t c = nPts;
                    for (;;) {
                        inner = s->Get_20();
                        EA_IO_WriteUint32(inner->Write_18(),
                                          (const uint32_t*)(path->mpBegin + j), 3, 0);
                        j += 0xc;
                        if (--c == 0) break;
                    }
                }
                off += 0x14;
                if (--cnt == 0) break;
            }
        }
    }
    return ok;
}

// @ 0x00cd56e0
void cTribeModeStrategy::F_cd56e0()
{
    RefMgr* p = new (g_StrSimulator, 0, 0, 0, 0) RefMgr;
    RefMgr* old = (RefMgr*)mp_394;
    if (p != old) {
        if (p) p->AddRef();
        mp_394 = p;
        if (old) old->Release();
    }
    ((RefMgr*)mp_394)->Update_1c();
}

// @ 0x00cd5750
int cTribeModeStrategy::F_cd5750()
{
    void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
    if (!tribe)
        return 0;
    float f = g_flt_158133c;
    if (mb_3a3) {
        unsigned char noKey = TerrainNotHasKey();
        if (!noKey) {
            if ((int)f <= ((int(__thiscall*)(void*))(*(void***)tribe)[0xa4 / 4])(tribe)) {
                uint32_t pop = ((cTribe*)tribe)->GetAdultPopulation();
                uint32_t max = ((cTribe*)tribe)->GetMaxPopulation();
                if (pop < max)
                    return 1;
            }
        }
    }
    return 0;
}

// @ 0x00cd5810
struct TribeVec {
    unsigned char* mpBegin;  // +0
    unsigned char* mpEnd;    // +4
    unsigned char* mpCap;    // +8
};
typedef bool (__cdecl *TribePred)(void* elem);

void* SP_FindClosest(const TribeVec* v, const cSPVector3* pos, TribePred pred)
{
    unsigned char* it = v->mpBegin;
    unsigned char* end = v->mpEnd;
    void* best = 0;
    float bestDist = g_fltmax;
    if (it == end)
        return best;
    do {
        void* elem = *(void**)it;
        if (pred(elem)) {
            void* sub = (unsigned char*)elem + 0x120;
            cSPVector3* p = ((cSPVector3* (__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
            float dx = p->x - pos->x;
            float dy = p->y - pos->y;
            float dz = p->z - pos->z;
            float d = dx * dx + dy * dy + dz * dz;
            if (bestDist > d) {
                best = elem;
                bestDist = d;
            }
        }
        it += 4;
    } while (it != end);
    return best;
}

// @ 0x00cd58d0
struct Elem16 { virtual void AddRef_0(); virtual void Write_4(Stream* s); virtual void Release_8(); };

void WriteSTLSequenceT(Stream* s, unsigned char* vec)
{
    unsigned char* begin = *(unsigned char**)vec;
    unsigned char* end = *(unsigned char**)(vec + 4);
    uint32_t n = (uint32_t)((end - begin) >> 4);
    StreamInner* inner = s->Get_20();
    EA_IO_WriteUint32(inner->Write_18(), &n, 1, 0);
    unsigned char* p = begin;
    while (p != end) {
        (*(Elem16**)p)->Write_4(s);
        p += 0x10;
    }
    s->End_1c();
}

// @ 0x00cd5980
void WritePairsT(Stream* s, unsigned char* vec)
{
    unsigned char* begin = *(unsigned char**)vec;
    unsigned char* end = *(unsigned char**)(vec + 4);
    uint32_t n = (uint32_t)((end - begin) >> 3);
    StreamInner* inner = s->Get_20();
    EA_IO_WriteUint32(inner->Write_18(), &n, 1, 0);
    unsigned char* p = begin;
    while (p != end) {
        inner = s->Get_20();
        EA_IO_WriteUint32(inner->Write_18(), (const uint32_t*)p, 1, 0);
        s->End_1c();
        inner = s->Get_20();
        EA_IO_WriteUint32(inner->Write_18(), (const uint32_t*)(p + 4), 1, 0);
        s->End_1c();
        p += 8;
    }
    s->End_1c();
}

// element (0x10 bytes) with refcounted pointer at +8 and byte at +0xc
struct ElemRef {
    void* mpVtbl;             // +0
    uint32_t m4;              // +4
    RefObj* volatile mp8;     // +8  (volatile reproduces cl's load ordering)
    unsigned char m0c;        // +0xc
};

// @ 0x00cd5a40
ElemRef* CopyCtorRange(ElemRef* first, ElemRef* last, ElemRef* dst)
{
    while (first != last) {
        if (dst) {
            dst->mpVtbl = &g_vt14774c4;
            dst->m4 = first->m4;
            RefObj* p = first->mp8;
            dst->mp8 = p;
            if (p)
                p->AddRef();
            dst->m0c = first->m0c;
        }
        first++;
        dst++;
    }
    return dst;
}

// @ 0x00cd5a90
ElemRef* AssignRange(ElemRef* first, ElemRef* last, ElemRef* dst)
{
    while (first != last) {
        dst->m4 = first->m4;
        RefObj* p = first->mp8;
        RefObj* d = dst->mp8;
        if (p != d) {
            if (p)
                p->AddRef();
            dst->mp8 = p;
            if (d)
                d->Release();
        }
        dst->m0c = first->m0c;
        first++;
        dst++;
    }
    return dst;
}

// @ 0x00cd5af0
ElemRef* CopyBackwardRange(ElemRef* first, ElemRef* last, ElemRef* dst)
{
    while (last != first) {
        last--;
        dst--;
        dst->m4 = last->m4;
        RefObj* p = last->mp8;
        RefObj* d = dst->mp8;
        if (p != d) {
            if (p)
                p->AddRef();
            dst->mp8 = p;
            if (d)
                d->Release();
        }
        dst->m0c = last->m0c;
    }
    return dst;
}

// @ 0x00cd5b80
struct cCommunity {
    void* GetLeader();                       // 0x00c00650  thiscall, returns [this+0x11c]
};
struct LeaderSub {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual cSPVector3* GetPos();            // +0x2c
    virtual float*      GetQuat();           // +0x30
};
struct LeaderObj { unsigned char mPad00[0xc0]; LeaderSub mSub; };   // sub-object at +0xc0
struct RandLCG  { uint32_t Uniform(uint32_t range); };              // 0x00a68fb0  thiscall
struct SysObj   { unsigned char mPad00[0x24]; void* mp24; };
struct Holder   { unsigned char mPad00[0x130]; void* mp130; };
struct FxSub {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void Apply(cSPVector3* v);       // +0x38
};
struct FxObj {
    unsigned char mPad00[0x34];
    FxSub         mSub34;                    // +0x34
    unsigned char mPad38[0x124 - 0x38];      // +0x38..+0x123
    unsigned char mb124;                     // +0x124
    unsigned char mPad125[3];                // +0x125..+0x127
    void*         mp128;                     // +0x128
    uint32_t      mPad12c;                   // +0x12c
    uint32_t      m130;                      // +0x130
};

void FUN_00cd5b80()
{
    void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
    void* leader = ((cCommunity*)tribe)->GetLeader();
    if (!leader)
        return;
    LeaderSub* leaderSub = &((LeaderObj*)leader)->mSub;
    cSPVector3 pos = *leaderSub->GetPos();
    float* qp = leaderSub->GetQuat();
    float q[4];
    q[0] = qp[0]; q[1] = qp[1]; q[2] = qp[2]; q[3] = qp[3];
    unsigned char* sys = (unsigned char*)FUN_00d1e660();
    void* holder = ((SysObj*)sys)->mp24;
    void* props = ((Holder*)holder)->mp130;
    float cnt = SP_GetPropertyT_float(props, 0xb2aa8e19, g_flt_1473c70);
    float scale = SP_GetPropertyT_float(props, 0xed219018, g_flt_1486110);
    int icnt = (int)cnt;
    uint32_t r = ((RandLCG*)g_rand_1601760)->Uniform((uint32_t)(0x400 - icnt));
    float v1[3], v2[3];
    FUN_0059aed0(v1, &g_v3_169b360, q);
    FUN_0059aed0(v2, &g_v3_169b36c, q);
    if (cnt > 0.0f) {
        float* tbl = &g_1559bdc[r * 2];      // g_1559bdc + r*8 bytes (stride 2 floats)
        int i = 0;                           // loop index (doubles each pass: i = 2i+1)
        do {
            void* container = FUN_00ac79d0(FUN_00b3d2b0(3));
            FxObj* obj = (FxObj*)FUN_00ac7ab0(FUN_00b3d2b0(3), g_flt_15812dc, container, 3);
            if (obj) {
                float ox = tbl[-1];
                float oy = tbl[0];
                cSPVector3 v;
                v.x = oy * (v2[0] * scale) + (ox * (v1[0] * scale) + pos.x);
                v.y = oy * (v2[1] * scale) + (ox * (v1[1] * scale) + pos.y);
                v.z = oy * (v2[2] * scale) + (ox * (v1[2] * scale) + pos.z);
                obj->mSub34.Apply(&v);
                ((void(__thiscall*)(void*, FxObj*)) (*(void***)obj->mp128)[0x30 / 4])(obj->mp128, obj);
                obj->m130 = (uint32_t)(i + 1);
                obj->mb124 = (unsigned char)(i + 1);
            }
            i += i + 1;
            tbl += 2;
        } while ((float)i < cnt);
    }
}

// @ 0x00cd5e40
bool cTribeModeStrategy::F_cd5e40()
{
    if (mp_1cc != 0) {
        void* h = mp_1cc;
        void* a0 = mp_1d0;
        void* a1 = mp_1d4;
        void* a2 = mp_1d8;
        void* a3 = mp_1dc;
        mp_1cc = 0;
        EA_Messaging_RemoveHandler(h, a0, a1, a2, a3);
    }
    if (mp_254 != 0) {
        ((C20Obj*)mp_254)->clear();
        if (mp_254 != 0) {
            RefObj* p = (RefObj*)mp_254;
            mp_254 = 0;
            p->Release();
        }
    }
    if (mb_228 != 0) {
        mb_228 = 0;
        if (g_169b054 == 0) {
            void* p = EA_operator_new(0x100, g_StrSimSingleton, 0, 0, 0, 0);
            g_169b054 = p ? ((SimSingleton*)p)->Init() : 0;
        }
        ((void(__thiscall*)(void*)) (*(void***)g_169b054)[0x20 / 4])(g_169b054);
        if (mp_23c != 0) {
            ((void(__thiscall*)(void*)) (*(void***)mp_23c)[8 / 4])(mp_23c);
            if (mp_23c != 0) {
                ((void(__thiscall*)(void*, int)) (*(void***)mp_23c)[0])(mp_23c, 1);
            }
            mp_23c = 0;
        }
        if (mp_240 != 0) {
            ((cTribeDisplayStrategy*)mp_240)->Deactivate();
            if (mp_240 != 0) {
                unsigned char* q = (unsigned char*)mp_240;
                mp_240 = 0;
                ((void(__thiscall*)(void*)) (*(void***)(q + 0x3c))[4 / 4])(q + 0x3c);
            }
        }
        if (mp_1c8 != 0) {
            ((Obj1c8*)mp_1c8)->Method();
            if (mp_1c8 != 0) {
                RefMgr* p = (RefMgr*)mp_1c8;
                mp_1c8 = 0;
                p->Release();
            }
        }
    }
    return true;
}

// @ 0x00cd5f70
struct SettingObj { void Method(); };                              // 0x004df420
struct MgrA       { void* Get(uint32_t hash, RefObj** out); };     // 0x00c8b370
struct MgrB       { void* Get_713e0(); };                          // 0x00c713e0
struct PropObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual unsigned char GetProp(uint32_t hash, RefObj** out);    // +0x24
};
struct PropValue { unsigned char mPad00[0x12]; uint16_t mType; };
struct PMObj     { void Method_8d8a0(void* e, int a, int b); };     // 0x00b8d8a0

void SP_cTribeModeStrategy_ContinueLoading()
{
    ((SettingObj*)GetSetting9())->Method();
    void* b = FUN_01021260();
    void* p = FUN_01021230();
    RefObj* local = 0;
    void* mgr = PropertyManager();
    if (local != 0) {
        RefObj* t = local;
        local = 0;
        t->Release();
    }
    void* id = ((MgrA*)p)->Get(0xe38475d9, &local);
    ((void(__thiscall*)(void*, void*)) (*(void***)mgr)[0x2c / 4])(mgr, id);
    void* e = ((MgrB*)b)->Get_713e0();
    ((PMObj*)PlanetModel())->Method_8d8a0(e, 1, 1);
    void* out = 0;
    if (local != 0) {
        RefObj* prop;
        unsigned char ok = ((PropObj*)local)->GetProp(0x96bf2d79, &prop);
        if (ok && ((PropValue*)prop)->mType == 10) {
            void* v = Property_GetUInt(prop);
            out = *(void**)v;
        }
    }
    interface_cast_0xd1c610(out, 0);
    if (local != 0)
        local->Release();
}

// @ 0x00cd6040
struct cTribeSensors {
    unsigned char Test1();                       // 0x00c8e870  thiscall
    unsigned char Test2();                       // 0x00c8e850  thiscall
};
struct WorldObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void Notify(RefObj* p, int v);       // +0x18
};

void FUN_00cd6040()
{
    void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
    RefObj* local = 0;
    cTribeSensors* ts = (cTribeSensors*)tribe;
    if (ts->Test1()) {
        if (ts->Test2()) {
            void* pm = PropertyManager();
            if (local != 0) {
                RefObj* t = local;
                local = 0;
                t->Release();
            }
            ((void(__thiscall*)(void*, uint32_t, uint32_t, RefObj**)) (*(void***)pm)[0x2c / 4])(pm, 0x96986124, 0xf71fa311, &local);
        } else {
            void* pm = PropertyManager();
            if (local != 0) {
                RefObj* t = local;
                local = 0;
                t->Release();
            }
            ((void(__thiscall*)(void*, uint32_t, uint32_t, RefObj**)) (*(void***)pm)[0x2c / 4])(pm, 0xed8aab2c, 0xf71fa311, &local);
        }
    } else {
        void* pm = PropertyManager();
        if (local != 0) {
            RefObj* t = local;
            local = 0;
            t->Release();
        }
        ((void(__thiscall*)(void*, uint32_t, uint32_t, RefObj**)) (*(void***)pm)[0x2c / 4])(pm, 0xcb0b8413, 0xf71fa311, &local);
    }
    if (local != 0) {
        void* world = GonzagoModelWorld();
        if (world != 0) {
            WorldObj* w = (WorldObj*)GonzagoModelWorld();
            w->Notify(local, 3);
        }
        if (local != 0)
            local->Release();
    }
}

// @ 0x00cd6130
void cTribeModeStrategy::F_cd6130(uint32_t id)
{
    if (mp_394 == 0)
        return;
    unsigned char* mgr = (unsigned char*)FUN_0067cac0();
    unsigned char* esi = *(unsigned char**)(mgr + 0x4c);

    if (id == 0x64e70b3) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0x2e573ccf)
            return;
        FUN_0067c830(FUN_0067cac0(), 0xb2a3fe9e);
        return;
    }
    if (id == 0x64d44f9) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0xb3009745)
            return;
        FUN_0067c830(FUN_0067cac0(), 0x2e573ccf);
        return;
    }
    if (id == 0x64c010f) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0x508fccb5)
            return;
        FUN_0067c830(FUN_0067cac0(), (uint32_t)SP_GetCamRotateTrigger());
        return;
    }
    if (id == 0x14363974) {
        void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
        if (tribe == 0)
            return;
        uint32_t pop = ((cTribe*)tribe)->GetAdultPopulation();
        uint32_t max = ((cTribe*)tribe)->GetMaxPopulation();
        if (pop >= max)
            return;
        void* ht = FUN_007eb100(FUN_0067de90(0xc));
        if (ht != 0) {
            unsigned char* n = *(unsigned char**)ht;
            while (n != ht) {
                if (*(uint32_t*)(n + 0x10) == 0 &&
                    **(uint32_t**)(n + 0x14) == 0x782e0768)
                    return;
                n = *(unsigned char**)n;
            }
        }
        FUN_00b706a0(mp_394, 0x11ade9ce);
        return;
    }
    if (id == 0x83861976) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0x255c3c16)
            return;
        FUN_0067c830(FUN_0067cac0(), 0xb3009745);
        return;
    }
    if (id == 0x5ac72d7c) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0xb2a3fe9e)
            return;
        void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
        if (tribe == 0)
            return;
        unsigned char bl = FUN_00c8e850(tribe);
        unsigned char al = FUN_00c8e870(tribe);
        if (bl) {
            if (al) {
                FUN_00b706a0(mp_394, 0x2d99d0b);
                FUN_0067c830(FUN_0067cac0(), 0xf4ff7b8a);
                return;
            } else {
                FUN_00b706a0(mp_394, 0x391c432);
                FUN_0067c830(FUN_0067cac0(), 0xa15bb8dd);
                return;
            }
        } else {
            if (!al)
                return;
            FUN_00b706a0(mp_394, 0x69ba7f0d);
            FUN_0067c830(FUN_0067cac0(), 0xccb2843a);
            return;
        }
    }
    if (id == 0x53203528) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != (uint32_t)SP_GetCamRotateTrigger())
            return;
        FUN_0067c830(FUN_0067cac0(), 0x255c3c16);
    }
}

// @ 0x00cd6390
struct XformMsg {
    uint16_t mFlags;    // +0x00
    uint16_t mCount;    // +0x02
    float    mX, mY, mZ; // +0x04
    uint32_t mPad10;    // +0x10
    float    mMatrix[9]; // +0x14
    void ctor();
};

void cTribeModeStrategy::F_cd6390(unsigned char enable)
{
    if (enable == 0) {
        if (mp_398 != 0) {
            ((void(__thiscall*)(void*)) (*(void***)mp_398)[0xc / 4])(mp_398);
            if (mp_398 != 0) {
                RefObj* p = (RefObj*)mp_398;
                mp_398 = 0;
                p->AddRef();
                return;
            }
        }
        return;
    }
    if (mp_398 != 0)
        F_cd6390(0);
    void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
    if (tribe == 0)
        return;
    unsigned char* squad = (unsigned char*)((void*(__thiscall*)(void*)) (*(void***)tribe)[0xac / 4])(tribe);
    if (squad == 0)
        return;
    void* fx = SP_EffectsManager();
    if (mp_398 != 0) {
        RefObj* p = (RefObj*)mp_398;
        mp_398 = 0;
        p->AddRef();
    }
    unsigned char ok = ((unsigned char(__thiscall*)(void*, uint32_t, int, void**)) (*(void***)fx)[0x2c / 4])(fx, 0x1a2cc3f0, 0, &mp_398);
    if (!ok)
        return;
    unsigned char* base = squad + 0x34;
    float* pos = (float*)((void*(__thiscall*)(void*)) (*(void***)base)[0x2c / 4])(base);
    float px = pos[0], py = pos[1], pz = pos[2];
    float* q = (float*)((void*(__thiscall*)(void*)) (*(void***)base)[0x68 / 4])(base);
    float qw = q[0x14 / 4];
    unsigned char* tmp = (unsigned char*)base;   // keep base live
    (void)tmp;
    cSPVector3 in, out;
    in.x = px; in.y = py; in.z = pz;
    in.z = qw;
    SP_NormalizedSafe(&out, &in);
    (void)qw;
    XformMsg msg;
    msg.ctor();
    msg.mFlags |= 4;
    msg.mCount++;
    msg.mX = px;
    msg.mY = py;
    msg.mZ = pz;
    void* qq = ((void*(__thiscall*)(void*)) (*(void***)base)[0x30 / 4])(base);
    SP_QuaternionToMatrix(msg.mMatrix, qq);
    msg.mFlags |= 2;
    msg.mCount++;
    ((void(__thiscall*)(void*, void*)) (*(void***)mp_398)[0x18 / 4])(mp_398, &msg);
    ((void(__thiscall*)(void*, int)) (*(void***)mp_398)[8 / 4])(mp_398, 0);
}

// @ 0x00cd6610
struct HashElem {
    uint32_t pad0;          // +0x00
    unsigned char* mp4;     // +0x04
    unsigned char* mp8;     // +0x08
    uint32_t m0c;           // +0x0c
    void DoFreeNodes(unsigned char* a, unsigned char* b);  // 0x00a1b6c0 (thiscall)
    void Clear();
};
void HashElem::Clear()
{
    DoFreeNodes(mp4, mp8);
    m0c = 0;
}
