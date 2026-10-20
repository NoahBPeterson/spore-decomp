// Slice s00a28120 - audio system singleton: StartSoundFromCommand/TryStartSound,
// texture/LRU table maintenance, per-key counters, playing-key tracking.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

void operator delete(void*);                                                  // 0x00f47380

// ---------------------------------------------------------------------------
// Refcounted payload objects: primary vtable slot 0 = AddRef, slot 1 = Release.
struct Key8 { unsigned a, b; };
struct Key4 { unsigned a, b, c, d; };
struct Vec3 { float x, y, z; };

struct SndA {
    virtual void AddRef();                                    // slot 0
    virtual void Release();                                   // slot 1
    virtual void s02(); virtual void s03(); virtual void s04();
    virtual void SetGain(double v);                           // slot 5  (+0x14)
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20();
    virtual unsigned GetKey();                                // slot 21 (+0x54)
    virtual bool IsPlaying();                                 // slot 22 (+0x58)
    virtual bool GetLayers(void** out);                       // slot 23 (+0x5c)
    virtual void s24();
    virtual void Prop3(int type, unsigned value, unsigned extra); // slot 25 (+0x64)
};

struct SndB {                                                 // secondary base at +4
    virtual void b0(); virtual void b1(); virtual void b2();
    virtual void PropF(int type, float value, int extra);     // slot 3 (+0xc)
};

struct Snd : SndA, SndB {
    char pad_[0x10 - 8];
    Snd* listNext;                                            // +0x10
    Snd* listPrev;                                            // +0x14
};

// ---- command (EA::Audio::Command) ------------------------------------------
struct Command {
    bool   GetUint32(unsigned hash, unsigned* out);           // 0x00a0fab0
    char*  GetString8(unsigned hash);                         // 0x00a0fb60
    bool   GetBool(unsigned hash, bool* out);                 // 0x00a0fa70
    bool   GetVoidPtr(unsigned hash, void** out);             // 0x00a0fb90
    void*  EnumParameter(void** value, unsigned* id2, unsigned* type, void** extra); // 0x00a0f880
};

// ---- configuration (EA::Audio::IConfiguration) -----------------------------
struct IConfig {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08();
    virtual bool GetBool(unsigned hash, bool* out);           // slot 9  (+0x24)
    virtual void c10();
    virtual bool GetUint32(unsigned hash, unsigned* out);     // slot 11 (+0x2c)
    virtual bool GetFloat(unsigned hash, float* out);         // slot 12 (+0x30)
    virtual void c13();
    virtual bool GetId(unsigned hash, unsigned* out);         // slot 14 (+0x38)
};

// ---- hashtable over keys (buckets at +4, count at +8) ----------------------
struct HIter { void* node; void** bucket; };

struct U32Table {
    char     pad0[4];
    void**   mpBuckets;      // +4
    unsigned mnBuckets;      // +8
    void  find(HIter* out, const void* key);                  // 0x00645ed0
    void  erase(HIter it, HIter* out);                        // 0x00d2c9f0
};

// template instances on the same table shape
void  T4Find(U32Table* t, HIter* out, const void* key);                // 0x00a23ef0
void  T4Op(U32Table* t, HIter* it, const void* key, int tag);          // 0x00a26be0
void  T4Insert2(U32Table* t, HIter* it, const void* pair, int tag);    // 0x00a26b00
void  T4Insert3(U32Table* t, HIter* it, const void* pair, int tag);    // 0x00a26ce0
void  PairInsert(U32Table* t, HIter* it, const void* pair, int tag);   // 0x00a136f0
HIter* PairErase(U32Table* t, void* node, void** bucket);              // 0x00a27660
struct InsertRes { void* node; void** bucket; };
InsertRes* KInsert(InsertRes* out, const void* pair, int tag);         // 0x00a26e10

// LRU nodes are {next+0x10, prev+0x14, owner+0xc}; the ETable iterator uses them.
struct ENode { unsigned pad[3]; void* owner; ENode* next; void* prev; };
struct KeyNode { unsigned pad[1]; void* value; };

// ---- voice object created by GetOrRegisterVoice ----------------------------
void* EAAllocate(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
extern void* g_voiceVT;                                                 // 0x01452bac

struct Voice {
    virtual void AddRef();                                   // slot 0
    virtual void Release2();                                 // slot 1 (+0x4) r=1
    virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual bool IsPlaying();                                // slot 22 (+0x58)
    virtual bool GetLayers(void** out);                      // slot 23 (+0x5c)
    virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32();
    virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v40(); virtual void v41();
    virtual void v42(); virtual void v43(); virtual void v44();
    virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50();
    virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); virtual void v55(); virtual void v56();
    virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62();
    virtual void DestroyV(int flag);                         // (operator delete, +0x8c)
    int     rc;        // +0x04
    void*   f08;
    void*   f0c;
    void*   f10;
    void*   f14;
    void*   f18;       // +0x18
    void*   f1c;       // +0x1c (points at +0x20)
    char    pad[0x98 - 0x20];
    void*   f98;       // +0x98
    void*   f9c;       // +0x9c
    bool    Init();                                          // 0x00a147b0
    void    AddLayer(void* layer);                           // 0x00a14780
    void*   Reset();                                         // 0x00a14730
};

Voice** RefMapFindOrInsert(U32Table* t, const void* key);                // 0x00a27530
void*   PoolAlloc(void* pool, int cb);                                   // 0x00a10ef0

// ---------------------------------------------------------------------------
// System singleton; only the fields touched by this slice are typed.
struct Sys {
    virtual void vs0(); void vs1(); void vs2(); void vs3();
    virtual void vs4(); void vs5(); void vs6(); void vs7();
    virtual void vs8(); void vs9(); void vs10(); void vs11();
    virtual void vs12(); void vs13(); void vs14(); void vs15();
    virtual void vs16(); void vs17(); void vs18(); void vs19();
    virtual void vs20(); void vs21(); void vs22(); void vs23();
    virtual void vs24(); void vs25(); void vs26(); void vs27();
    virtual void vs28(); void vs29(); void vs30(); void vs31();
    virtual void vs32(); void vs33(); void vs34(); void vs35();
    virtual bool     StartSound(unsigned key, unsigned a2, void* data, Vec3* pos, Snd** out); // slot 36 (+0x94)
    virtual bool     StopSound2(unsigned id, int a2);                           // slot 37 (+0x98)
    virtual void vs38(); void vs39(); void vs40(); void vs41();
    virtual void vs42(); void vs43(); void vs44(); void vs45();
    virtual void vs46(); void vs47(); void vs48(); void vs49();
    virtual void vs50(); void vs51(); void vs52(); void vs53();
    virtual void vs54(); void vs55(); void vs56(); void vs57();
    virtual void vs58(); void vs59();
    virtual unsigned SymbolToId(char const* name);                              // slot 60 (+0xf4)
    virtual void vs61(); void vs62(); void vs63(); void vs64();
    virtual void vs65(); void vs66(); void vs67(); void vs68();
    virtual void vs69(); void vs70(); void vs71(); void vs72();
    virtual void vs73(); void vs74(); void vs75(); void vs76();
    virtual void vs77(); void vs78(); void vs79(); void vs80();
    virtual void vs81(); void vs82(); void vs83(); void vs84();
    virtual void vs85();
    virtual int      AddPlaylistRef(unsigned id, int a2);                       // slot 86 (+0x15c)
    virtual void vs87(); void vs88(); void vs89();
    virtual bool     RegisterKey(void* key);                                    // slot 90 (+0x16c)
    virtual bool     UnregisterKey(void* key);                                  // slot 91 (+0x170)
    virtual void vs92(); void vs93(); void vs94(); void vs95();
    virtual void vs96();
    virtual bool     FindPlaylistTable(Key4* key, void* out);                   // slot 97 (+0x188)
    virtual bool     GetPlaylistOwner(Key4* key, void* out);                    // slot 98 (+0x18c)
    virtual bool     GetPlaylistOwner2(Key4* key, void* out);                   // slot 99 (+0x190)
    virtual void vs100(); void vs101(); void vs102();
    virtual void vs103();
    virtual int      ReleasePlaylistRef(unsigned id);                           // slot 104 (+0x1a4)
    virtual void vs105(); void vs106(); void vs107(); void vs108();
    virtual void vs109(); void vs110(); void vs111(); void vs112();
    virtual void vs113(); void vs114(); void vs115();
    virtual Snd*     FindSound(unsigned id);                                    // slot 116 (+0x1d4)
    virtual void vs117(); void vs118(); void vs119(); void vs120();

    char pad_[0x118a1c - 0x4];
    U32Table mActiveTable;        // +0x118a1c (buckets +0x118a20, count +0x118a24)
    char pad2[0x118a3c - 0x118a2c];
    U32Table mLRUTable;           // +0x118a3c (buckets +0x118a40, count +0x118a44)
    char pad3[0x118b90 - 0x118a4c];
    U32Table mVoiceMap;           // +0x118b90 (buckets +0x118b94, count +0x118b98)
    char pad3b[0x118bb0 - 0x118ba0];
    U32Table mCounterA;           // +0x118bb0 (buckets +0x118bb4, count +0x118bb8)
    char pad4[0x13795c - 0x118bc0];
    U32Table mSoundMap;           // +0x13795c
    char pad5[0x137fe8 - 0x137964];
    U32Table mCounterMap;         // +0x137fe8 (buckets +0x137fec, count +0x137ff0)
    char pad6[0x157440 - 0x137ff8];
    U32Table mKeyMap;             // +0x157440
    char pad7[0x158f50 - 0x157450];
    U32Table mObjMap;             // +0x158f50
    char pad8[0x15b750 - 0x158f60];
    void* mLRUIterNode;           // +0x15b750
    void* mLRUIterBucket;         // +0x15b754
    int   mLRUBytes;              // +0x15b758
    int   mLRUEnabled;            // +0x15b75c
    char pad9[0x15b770 - 0x15b760];
    int   mTexEnabled;            // +0x15b770
    char pad10[0x15bbf4 - 0x15b774];
    U32Table mTexTable;           // +0x15bbf4

    bool StartSoundFromCommand(Command& cmd, unsigned id);          // 00a28120
    bool TryStartSound(char* out, unsigned id, IConfig* cfg,
                       Vec3* pos, unsigned a5);                     // 00a28450
    void MaintainLRU();                                             // 00a28810
    void AddTextureRef(Key4* key);                                  // 00a28a20
    bool GetOrRegisterVoice(unsigned key, Voice** out, int nLayers, void* layers); // 00a28aa0
    void RegisterObj(Snd* p);                                       // 00a28c60
    bool UnregisterObj(unsigned key);                               // 00a28d10
    int  GetCounterPlaylist(unsigned key);                          // 00a28d70
    int  AddCounter(unsigned key, int delta);                       // 00a28e90
    bool TrackPlayingKey(Snd* obj);                                 // 00a28f10
    bool UntrackPlayingKey(Snd* obj);                               // 00a29000
};

// The listener transform lives on the audio system singleton at 0x0166d9f4,
// reached through vtable slot 30 (+0x7c).
struct ListenerObj {
    virtual void ls00(); virtual void ls01(); virtual void ls02(); virtual void ls03();
    virtual void ls04(); virtual void ls05(); virtual void ls06(); virtual void ls07();
    virtual void ls08(); virtual void ls09(); virtual void ls10(); virtual void ls11();
    virtual void ls12(); virtual void ls13(); virtual void ls14(); virtual void ls15();
    virtual void ls16(); virtual void ls17(); virtual void ls18(); virtual void ls19();
    virtual void ls20(); virtual void ls21(); virtual void ls22(); virtual void ls23();
    virtual void ls24(); virtual void ls25(); virtual void ls26(); virtual void ls27();
    virtual void ls28(); virtual void ls29();
    virtual void* GetListenerTransform(unsigned surf);         // slot 30 (+0x7c)
};
extern ListenerObj* g_audioSys;                                          // 0x0166d9f4

struct ResponseCurve {
    char raw[0x30];
    ResponseCurve();                                                     // 0x00a1aa50
    bool InitFromConfiguration(unsigned hash, IConfig* cfg);             // 0x00a1a9d0
    float GetOutputValue(float x);                                       // 0x00a1a110
};

// ===========================================================================
// 00a28120: start (or re-target) the sound named by a command.
// ===========================================================================
// @ 0x00a28120
bool Sys::StartSoundFromCommand(Command& cmd, unsigned id)
{
    Snd* snd = 0;
    Snd* found = 0;
    {
        Snd* cur = FindSound(id);
        found = cur;
        Snd* hold = FindSound(id);
        while (found) {
            found = hold;
            Snd* nxt = found;
            if (nxt)
                nxt->AddRef();
            if (cur)
                cur->Release();
            found = nxt;
            break;
        }
    }
    if (snd != found)
        snd = found;
    if (!snd) {
        unsigned key = 0;
        cmd.GetUint32(0x3475381, &key);
        if (key == 0) {
            char* name = cmd.GetString8(0x347537e);
            if (!name)
                return false;
            key = SymbolToId(name);
        }
        void* last = 0;
        HIter it2;
        {
            void** buckets = mSoundMap.mpBuckets;
            unsigned n = mSoundMap.mnBuckets;
            last = buckets[n];
            T4Find(&mSoundMap, &it2, &key);
            if (it2.node != last)
                return false;
        }
        int flag = 0;
        {
            unsigned a = 0, b = 0;
            if (cmd.GetBool(0x3475391, (bool*)&a)) {
                if (cmd.GetBool(0x3475395, (bool*)&b)) {
                    flag = 1;
                    if (!cmd.GetBool(0x3475398, (bool*)&a))
                        flag = 0;
                } else {
                    flag = 0;
                }
            } else {
                flag = 0;
            }
        }
        void* data = 0;
        cmd.GetVoidPtr(0x347539c, &data);
        if (snd)
            snd->Release();
        snd = 0;
        Vec3 pos;
        if (!StartSound(key, id, data, flag ? &pos : 0, &snd)) {
            T4Op(&mSoundMap, &it2, &key, 0);
            StopSound2(id, 1);
            if (data)
                ((SndA*)data)->Release();
            if (snd)
                snd->Release();
            return false;
        }
        if (data)
            ((SndA*)data)->Release();
    }
    {
        void* value = 0;
        unsigned type = 0;
        void* extra = 0;
        unsigned id2 = 0;
        void* node = cmd.EnumParameter(&value, &id2, &type, &extra);
        while (node) {
            if (type == 0) {
                ((SndB*)((char*)snd + 4))->PropF(0, *(float*)&node, 1);
            } else if (type == 5) {
                snd->Prop3(5, (unsigned)node, id2);
            }
            node = cmd.EnumParameter(&value, &id2, &type, &extra);
        }
    }
    float gain = 0.0f;
    cmd.GetBool(0x12c65397, (bool*)&gain);
    snd->SetGain((double)gain);
    if (snd)
        snd->Release();
    return true;
}

// ===========================================================================
// 00a28450: fill a sound template from a configuration.
// ===========================================================================
// @ 0x00a28450
bool Sys::TryStartSound(char* out, unsigned id, IConfig* cfg, Vec3* pos, unsigned a5)
{
    char* p = out;
    *(unsigned*)(p + 0x14) = id;
    *(unsigned*)(p + 0x18) = (unsigned)cfg;
    cfg->GetBool(0x12d2a4d4, (bool*)(p + 0));
    cfg->GetBool(0x6dd08218, (bool*)(p + 1));
    cfg->GetBool(0xba134192, (bool*)(p + 2));
    if (*(bool*)(p + 0)) {
        float window = 0.0f;
        if (!cfg->GetFloat(0xf616b72, (float*)(p + 8)))
            return false;
        if (!cfg->GetFloat(0x3593710, (float*)(p + 4)))
            return false;
        if (!pos)
            return false;
        unsigned surf = 0;
        cfg->GetUint32(0xed1f36d5, &surf);
        Vec3* listener = (Vec3*)g_audioSys->GetListenerTransform(surf);
        float dx = pos->x - listener->x;
        float dy = pos->y - listener->y;
        float dz = pos->z - listener->z;
        float dist = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
        dist = (float)fabs((double)dist);
        if (!*(bool*)(p + 1) && dist > *(float*)(p + 4))
            return false;
        float gain = *(float*)0x01485720;
        cfg->GetFloat(0x2406a047, &gain);
        float fmax = *(float*)0x01485720;
        cfg->GetFloat(0x25df0108, &fmax);
        if (*(float*)(p + 8) > dist)
            window = gain * *(float*)0x01485720;
        else if (gain == 0.0f)
            window = *(float*)0x01485720;
        else if (dist > *(float*)(p + 4))
            window = *(float*)0x01485720;
        else {
            ResponseCurve curve;
            if (curve.InitFromConfiguration(0x1e4db1eb, cfg))
                window = gain * curve.GetOutputValue((dist - *(float*)(p + 8)) /
                                                     (*(float*)(p + 4) - *(float*)(p + 8)));
            else
                window = *(float*)0x01485720;
        }
        *(float*)(p + 0xc) = window;
    }
    *(float*)(p + 0x10) = *(float*)0x01485720;
    cfg->GetFloat(0x393f7f7d, (float*)(p + 0x10));
    *(unsigned*)(p + 0x1c) = 1;
    cfg->GetUint32(0xd9ec19d6, (unsigned*)(p + 0x1c));
    *(unsigned*)(p + 0x24) = 0xee8347b0;
    cfg->GetId(0x7f28acc, (unsigned*)(p + 0x24));
    *(unsigned*)(p + 0x28) = (unsigned)AddPlaylistRef(a5, 0);
    *(unsigned*)(p + 0x2c) = 2;
    cfg->GetUint32(0xbaf7f4f9, (unsigned*)(p + 0x2c));
    cfg->GetUint32(0x51997db2, (unsigned*)(p + 0x3c));
    unsigned* owner = (unsigned*)(p + 0x20);
    cfg->GetId(0x701ed91e, owner);
    if (*owner == 0)
        *owner = a5;
    unsigned slot = *owner;
    Key4 key;
    key.a = 0;
    key.b = slot;
    key.c = 0x3055f61;
    key.d = 0x21407ee;
    *(unsigned*)(p + 0x30) = 0xffffffff;
    if (FindPlaylistTable(&key, p + 0x38)) {
        void* o = 0;
        if (GetPlaylistOwner(&key, &o) && o)
            *(unsigned*)(p + 0x30) = *(unsigned*)((char*)o + 0x14);
        if (o)
            ((SndA*)o)->Release();
    } else {
        *(unsigned*)(p + 0x30) = (unsigned)ReleasePlaylistRef(slot);
    }
    return true;
}

// ===========================================================================
// 00a28810: walk the LRU table, re-registering live entries in the active map.
// ===========================================================================
// @ 0x00a28810
void Sys::MaintainLRU()
{
    HIter res;
    void** bucket = mLRUTable.mpBuckets;
    void* node = *bucket;
    if (!node) {
        ++bucket;
        while (!*bucket)
            ++bucket;
        node = *bucket;
    }
    void* last = mLRUTable.mpBuckets[mLRUTable.mnBuckets];
    while (node != last) {
        Snd* snd = (Snd*)((ENode*)node)->owner;
        bool linked = false;
        if (snd->IsPlaying()) {
            void* layers = 0;
            if (snd->GetLayers(&layers)) {
                if (mTexEnabled) {
                    void** act = mActiveTable.mpBuckets;
                    HIter it;
                    T4Find(&mActiveTable, &it, (char*)layers + 8);
                    void* expected = act[mActiveTable.mnBuckets];
                    if (*(void**)it.node == expected) {
                        mLRUBytes += *(int*)((char*)layers + 0x18);
                        Key4 pair;
                        pair.a = *(unsigned*)((char*)layers + 8);
                        pair.b = *(unsigned*)((char*)layers + 0xc);
                        pair.c = *(unsigned*)((char*)layers + 0x10);
                        pair.d = (unsigned)layers;
                        ((SndA*)layers)->AddRef();
                        HIter it2;
                        T4Insert2(&mActiveTable, &it2, &pair, 0);
                        if (layers)
                            ((SndA*)layers)->Release();
                        mLRUIterNode = mActiveTable.mpBuckets[mActiveTable.mnBuckets];
                        mLRUIterBucket = &mActiveTable.mpBuckets[mActiveTable.mnBuckets];
                    }
                }
                linked = true;
            }
        }
        if (linked) {
            res = *PairErase(&mLRUTable, node, bucket);
            node = res.node;
            bucket = res.bucket;
        } else {
            node = ((ENode*)node)->next;
            if (!node) {
                ++bucket;
                while (!*bucket)
                    ++bucket;
                node = *bucket;
            }
        }
    }
}

// ===========================================================================
// 00a28a20: reference a texture-table entry (insert with count 0 if missing).
// ===========================================================================
// @ 0x00a28a20
void Sys::AddTextureRef(Key4* key)
{
    U32Table* map = &mTexTable;
    HIter it;
    map->find(&it, key);
    if (it.node != map->mpBuckets[map->mnBuckets]) {
        ++((unsigned*)map->mpBuckets[map->mnBuckets])[3];
        return;
    }
    InsertRes res;
    Key4 pair;
    pair.a = key->a;
    pair.b = key->b;
    pair.c = key->c;
    pair.d = 0;
    map->mpBuckets[map->mnBuckets] = 0;
    KInsert(&res, &pair, 1);
}

// ===========================================================================
// 00a28aa0: get (or create) the voice object registered for a resource key.
// ===========================================================================
// @ 0x00a28aa0
bool Sys::GetOrRegisterVoice(unsigned key, Voice** out, int nLayers, void* layers)
{
    Voice* v = 0;
    HIter it;
    mVoiceMap.find(&it, &key);
    if (it.node != mVoiceMap.mpBuckets[mVoiceMap.mnBuckets]) {
        v = (Voice*)((KeyNode*)it.node)->value;
        if (v)
            ++v->rc;
    } else {
        Voice* nv = (Voice*)EAAllocate(0xa0, (char*)0x140a5a0, 0, 0, 0, 0);
        if (nv) {
            nv->rc = 0;
            nv->f0c = (char*)nv + 0x20;
            nv->f08 = (char*)nv + 0x20;
            nv->f18 = (char*)nv + 0x20;
            nv->f9c = nv->f0c;
            nv->f98 = 0;
            nv->f10 = (char*)nv->f98 + 0x78;
            *(void**)nv = g_voiceVT;            ++nv->rc;
            v = nv;
        }
        if (!v->Init()) {
            if (v) {
                if (--v->rc == 0) {
                    v->rc = 1;
                    v->DestroyV(1);
                }
            }
            return false;
        }
        int n = nLayers;
        if (n > 0) {
            char* p = (char*)layers;
            do {
                v->AddLayer(*(void**)p);
                p += 0xc;
            } while (--n);
        }
        v->Reset();
        Voice** slot = RefMapFindOrInsert(&mVoiceMap, &key);
        Voice* old = *slot;
        if (v != old) {
            if (v)
                ++v->rc;
            *slot = v;
            if (old) {
                if (--old->rc == 0) {
                    old->rc = 1;
                    old->DestroyV(1);
                }
            }
        }
    }
    if (out) {
        if (v)
            ++v->rc;
        *out = v;
    }
    if (v) {
        if (--v->rc == 0) {
            v->rc = 1;
            v->DestroyV(1);
        }
    }
    return true;
}

// ===========================================================================
// 00a28c60: register an object (holding two references until the insert ends).
// ===========================================================================
// @ 0x00a28c60
void Sys::RegisterObj(Snd* p)
{
    if (p)
        p->AddRef();
    Key4 pair;
    pair.a = (unsigned)p;
    pair.b = 0;
    pair.c = 0;
    pair.d = (unsigned)p;
    if (p)
        p->AddRef();
    HIter it;
    PairInsert(&mObjMap, &it, &pair, 0);
    if (p)
        p->Release();
}

// ===========================================================================
// 00a28d10: drop a key from the object table.
// ===========================================================================
// @ 0x00a28d10
bool Sys::UnregisterObj(unsigned key)
{
    U32Table* map = &mObjMap;
    HIter it;
    map->find(&it, &key);
    if (it.node == map->mpBuckets[map->mnBuckets])
        return false;
    map->erase(it, &it);
    return true;
}

// ===========================================================================
// 00a28d70: playlist id for a counter key (registering it on first use).
// ===========================================================================
// @ 0x00a28d70
int Sys::GetCounterPlaylist(unsigned key)
{
    U32Table* map = &mCounterMap;
    HIter it;
    map->find(&it, &key);
    if (it.node != map->mpBuckets[map->mnBuckets])
        return *(int*)((char*)it.node + 4);
    Key4 k;
    k.c = 0x1a527db;
    k.d = 0x21407ee;
    k.a = 0;
    k.b = key;
    void* owner = 0;
    int result = -1;
    if (GetPlaylistOwner2(&k, &owner)) {
        short* p = (short*)((char*)owner + 0x14);
        void* p1 = &p[1];
        p1 = PoolAlloc(&p1, 4);
        void* p2 = 0;
        p2 = PoolAlloc(&p1, 4);
        result = (int)p2;
        Key4 pair;
        pair.a = (unsigned)p1;
        pair.b = (unsigned)p2;
        HIter it2;
        T4Insert3(&mCounterMap, &it2, &pair, 0);
    }
    if (owner)
        ((SndA*)owner)->Release();
    return result;
}

// ===========================================================================
// 00a28e90: add a delta to a per-key counter (creating it at delta otherwise).
// ===========================================================================
// @ 0x00a28e90
int Sys::AddCounter(unsigned key, int delta)
{
    U32Table* map = &mCounterA;
    HIter it;
    map->find(&it, &key);
    if (it.node != map->mpBuckets[map->mnBuckets]) {
        int* p = (int*)((char*)it.node + 4);
        *p += delta;
        return *p;
    }
    Key4 pair;
    pair.a = key;
    pair.b = 0;
    pair.c = 0;
    pair.d = delta;
    HIter it2;
    T4Insert3(map, &it2, &pair, 0);
    return delta;
}

// ===========================================================================
// 00a28f10: remember a playing sound's key in the key table.
// ===========================================================================
// @ 0x00a28f10
bool Sys::TrackPlayingKey(Snd* obj)
{
    if (!obj)
        return false;
    if (!obj->IsPlaying())
        return false;
    if (!RegisterKey((char*)obj + 4))
        return false;
    obj->AddRef();                          // local AutoRefCount
    obj->AddRef();                          // pair's smart-pointer copy
    unsigned key = obj->GetKey();
    obj->AddRef();                          // map value's reference
    Key4 pair;
    pair.a = key;
    pair.b = (unsigned)obj;
    pair.c = 0;
    pair.d = 0;
    HIter it;
    PairInsert(&mKeyMap, &it, &pair, 0);
    if (obj)
        obj->Release();
    if (obj)
        obj->Release();
    return true;
}
// ===========================================================================
// 00a29000: forget a playing sound's key.
// ===========================================================================
// @ 0x00a29000
bool Sys::UntrackPlayingKey(Snd* obj)
{
    if (!obj)
        return false;
    unsigned k = obj->GetKey();
    U32Table* map = &mKeyMap;
    HIter it;
    map->find(&it, &k);
    if (it.node == map->mpBuckets[map->mnBuckets])
        return false;
    UnregisterKey((char*)obj + 4);
    map->erase(it, &it);
    if (obj->listNext) {
        if (obj->listPrev) {
            obj->listPrev->listNext = obj->listNext;
            obj->listNext->listPrev = obj->listPrev;
            obj->listNext = 0;
            obj->listPrev = 0;
        }
    }
    obj->listNext = 0;
    obj->listPrev = 0;
    obj->Release();
    return true;
}
