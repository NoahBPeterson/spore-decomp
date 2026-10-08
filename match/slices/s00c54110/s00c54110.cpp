// Slice s00c54110 - SP::cSPMissionFetch::HandleMessage (message handler of the fetch mission).
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// `this` is the IHandler subobject of the mission (mission = this - 0x34); fields are addressed from `this`.
#include "types.h"

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Key  { uint32_t a, b, c; };

extern Vec3 gDefaultPos;   // 0x016907c8
extern Key  gNullKey;      // 0x016907d4
extern wchar_t gEmptyWString[]; // 0x01667bac

// eastl::wstring, 16 bytes with the 4-byte allocator
struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    WStr() { mpBegin = gEmptyWString; mpEnd = gEmptyWString; mpCapacity = gEmptyWString + 1; }
    void DeallocateSelf();            // 0x00933960
    ~WStr() { DeallocateSelf(); }
};

struct Msg { uint32_t f0; uint32_t f4; uint8_t* src; uint32_t fc; void* f10; uint32_t f14; uint32_t f18; };

struct PosProv {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual Vec3* GetPos();           // slot 0x2c
};

struct Mission {
    void  TriggerUIUpdate();                 // 0x00c47d80
    void* GetTargetPlanet();                 // 0x00970b30
    void* GetModel();                        // 0x00c45ce0
    void* GetOwnerEmpire();                  // 0x00c451e0
    void  GetText(uint32_t key, WStr* out);  // 0x00c487d0
    void  PostEvent(void* ev);               // 0x00c48e50
    void  FUN_00c5ed90(int a);               // 0x00c5ed90
    void  FUN_00c47180(void* planet);        // 0x00c47180
    void  Complete();                        // 0x00c52ea0
};
struct Avatar {
    void* SpawnArtifact(void* params);       // 0x00ff5d20
};
struct GameNounMgr {
    Avatar* GetAvatar();                     // 0x00b1fdb0
};
struct SpecimenMgr {
    void* Lookup(Msg* m);                    // 0x00b2b1e0
};
struct ArtItem {
    Key* GetKey(Key* out);                   // 0x00ad2620
};
struct PlantItem {
    Key* GetKey(Key* out);                   // 0x00c3e1e0
};
struct AnimItem {
    Key* GetKey();                           // 0x00c0bc00
};
struct VecP { uint8_t** b; uint8_t** e; };
struct NounMgr {
    VecP* GetAll();                          // 0x00ace2c0
};
struct EventLog {
    void* PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);  // 0x00dd8640
    void  ModifyEventText(void* ev, wchar_t* text);                               // 0x00dd6df0
};
struct CommMgr {
    void AddEntry(int empire, int ctx, int text, uint32_t key, void* obj, int a, int b); // 0x00aeb160
};
struct StarRec {
    int GetCommContext();                    // 0x00ce6950
};
struct Vec3Vec {
    void push_back(const Vec3* v);           // 0x004739d0
};

void*  __cdecl GetActivePlanet();                  // 0x01021260
GameNounMgr* __cdecl SpaceGameGet();               // 0x01002bd0
NounMgr* __cdecl GetNounManager();                 // 0x00b3d300
SpecimenMgr* __cdecl GetSpecimenMgr();             // 0x00b3d3b0
EventLog* __cdecl GetEventLog();                   // 0x00b3d3e0
CommMgr* __cdecl GetCommManager();                 // 0x00b3d4a0
bool   __cdecl KeyEq(const Key* a, const Key* b);  // 0x004eb930
bool   __cdecl KeyNe(const Key* a, const Key* b);  // 0x005f78f0
Vec3*  __cdecl FindVec3(Vec3* first, Vec3* last, const Vec3* v);  // 0x00c52d30
ArtItem*   __cdecl CastArt(void* p);               // 0x00c52220
PlantItem* __cdecl CastPlant(void* p);             // 0x00c52240
AnimItem*  __cdecl CastAnimal(void* p);            // 0x00c52260
AnimItem*  __cdecl CastAnimal2(void* p);           // 0x00c4bbe0
bool   __cdecl IsItemARare(Key* k);                // 0x0103a3c0

struct SpawnParams {
    uint32_t a; Key pos; uint16_t w; uint8_t b12; uint8_t pad; float f; uint32_t g[4]; uint8_t t28;
};

struct FetchHandler {
    void HandleMessage(uint32_t msg, Msg* m);
    void BaseHandleMessage(uint32_t msg, Msg* m);   // 0x00c4a6b0 cSPMission::HandleMessage

    template<class T> T& F(int off) { return *(T*)((char*)this + off); }
    Mission* Mis() { return (Mission*)((char*)this - 0x34); }
};

static inline int SlotId(Mission* mi) {
    return ((int(__thiscall*)(Mission*))(*(void***)mi)[0xa4 / 4])(mi);
}

// @ 0x00c545f0
void FetchHandler::HandleMessage(uint32_t msg, Msg* m)
{
    Key f12plant, f11art2, f11plant, f11art1, f11rare, f12art1, f12art2;
    switch (msg) {
    case 0x2489766: case 0x248976a:
        if (F<int>(0x1bc) != 0) break;
    ui_update:
        if (F<uint32_t>(0x44) == 0x809ab04a)
            Mis()->TriggerUIUpdate();
        break;
    case 0x248975f:
        if (F<uint32_t>(0x1c0) == 0x19ec2c8b) {
            if (F<int>(0x1bc) == 0) {
                Mission* mi = Mis();
                void* target = m->f10;
                if (mi->GetTargetPlanet() == target) {
                    Avatar* av = SpaceGameGet()->GetAvatar();
                    if (av) {
                        SpawnParams sp;
                        sp.a = F<uint32_t>(0x1c4);
                        sp.pos.a = F<uint32_t>(0x1d0);
                        sp.pos.b = F<uint32_t>(0x1d4);
                        sp.pos.c = F<uint32_t>(0x1d8);
                        sp.w = 1;
                        sp.g[1] = 0; sp.g[2] = 0; sp.g[3] = 0;
                        sp.t28 = 0x28;
                        sp.b12 = 5; sp.f = 0.0f;
                        sp.g[0] = 0;
                        void* obj = av->SpawnArtifact(&sp);
                        if (obj) {
                            F<Vec3>(0x1d0) = *((PosProv*)((char*)obj + 0x34))->GetPos();
                        } else {
                            F<Vec3>(0x1d0) = gDefaultPos;
                        }
                    }
                }
            }
            break;
        }
        goto ui_update;
    case 0x2e9977e:
        if (F<uint32_t>(0x1c0) == 0x6d5c48c) {
            uint8_t* src = m->src;
            if (src && m->f18 && m->f18 != 0x2ebcd6a6) {
                void* sp = GetSpecimenMgr()->Lookup(m);
                if (sp && KeyEq((Key*)sp, &F<Key>(0x1dc))) {
                    Vec3 pos = *(Vec3*)(src + 4);
                    Vec3* b = F<Vec3*>(0x21c);
                    Vec3* e = F<Vec3*>(0x220);
                    if (FindVec3(b, e, &pos) == e)
                        ((Vec3Vec*)&F<Vec3*>(0x21c))->push_back(&pos);
                }
            }
        }
        break;
    case 0x3029f12: {
        Mission* mi = Mis();
        void* model = mi->GetModel();
        if (GetActivePlanet() != model) break;
        if (!F<uint8_t>(0x214)) break;
        bool hasTarget = m->f10 != 0;
        uint8_t* src = m->src;
        if (!src) break;
        PosProv* pp;
        switch ((int)F<uint32_t>(0x1c0)) {
        case 0x3e994b2b: case 0x69412983: case (int)0xfb3b1635: {
            AnimItem* a = CastAnimal2(src);
            if (!a) goto done;
            if (!KeyEq(a->GetKey(), &F<Key>(0x1e8))) goto done;
            pp = (PosProv*)((char*)a + 0xc0);
            break;
        }
        case (int)0xbfb44ccc: {
            ArtItem* a = CastArt(src);
            if (!a) goto done;
            if (*(int*)((char*)a + 0x658) != 4) goto done;
            if (!KeyEq(a->GetKey(&f12art1), &F<Key>(0x1f4))) goto done;
            pp = (PosProv*)((char*)a + 0x34);
            break;
        }
        case 0x19ec2c8b: {
            ArtItem* a = CastArt(src);
            if (!a) goto done;
            if (!KeyEq(a->GetKey(&f12art2), &F<Key>(0x1c4))) goto done;
            pp = (PosProv*)((char*)a + 0x34);
            F<Vec3>(0x1d0) = *pp->GetPos();
            break;
        }
        case 0x2dc69129: case 0x6d5c48c: case 0x736c417f: {
            Key* kp = &F<Key>(0x1dc);
            if (KeyNe(kp, &gNullKey)) {
                PlantItem* a = CastPlant(src);
                if (!a) goto done;
                if (!KeyEq(a->GetKey(&f12plant), kp)) goto done;
                pp = (PosProv*)((char*)a + 0x34);
            } else {
                kp = &F<Key>(0x1e8);
                if (!KeyNe(kp, &gNullKey)) goto done;
                AnimItem* a = CastAnimal(src);
                if (!a) goto done;
                if (!KeyEq(a->GetKey(), kp)) goto done;
                pp = (PosProv*)((char*)a + 0xc0);
            }
            break;
        }
        default:
            goto done;
        }
        Vec3 pos = *pp->GetPos();
        if (!hasTarget) break;
        {
            float r = F<float>(0x218);
            float r2 = r * r;
            VecP* list = GetNounManager()->GetAll();
            for (uint8_t** it = list->b; it != list->e; ++it) {
                PosProv* o = (PosProv*)(*it + 0x120);
                Vec3* p = o->GetPos();
                float dz = p->z - pos.z, dy = p->y - pos.y, dx = p->x - pos.x;
                if (r2 > dz * dz + dy * dy + dx * dx) {
                    mi->Complete();
                    goto done;
                }
            }
        }
        {
            WStr text;
            mi->GetText(0x959d4317, &text);
            void* ev = GetEventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
            GetEventLog()->ModifyEventText(ev, text.mpBegin);
            mi->PostEvent(ev);
        }
        break;
    }
    case 0x3029f11: {
        Mission* mi = Mis();
        void* tp = mi->GetTargetPlanet();
        bool ok;
        if (tp == 0) {
            if (F<uint32_t>(0x1c0) != 0x7ecbe6f5) goto done;
            ArtItem* a = CastArt(m->src);
            if (!a) goto done;
            ok = IsItemARare(a->GetKey(&f11rare));
        } else {
            void* tp2 = mi->GetTargetPlanet();
            if (GetActivePlanet() != tp2) goto done;
            uint8_t* src = m->src;
            if (!src) goto done;
            switch ((int)F<uint32_t>(0x1c0)) {
            case 0x3e994b2b: case 0x69412983: case (int)0xfb3b1635: {
                AnimItem* a = CastAnimal2(src);
                if (!a) goto done;
                ok = KeyEq(a->GetKey(), &F<Key>(0x1e8));
                break;
            }
            case (int)0xbfb44ccc: {
                ArtItem* a = CastArt(src);
                if (!a) goto done;
                if (*(int*)((char*)a + 0x658) != 4) goto done;
                ok = KeyEq(a->GetKey(&f11art1), &F<Key>(0x1f4));
                break;
            }
            case 0x19ec2c8b: {
                ArtItem* a = CastArt(src);
                if (!a) goto done;
                if (!KeyEq(a->GetKey(&f11art2), &F<Key>(0x1c4))) goto done;
                F<Vec3>(0x1d0) = gDefaultPos;
                goto finish;
            }
            case 0x2dc69129: case 0x6d5c48c: case 0x736c417f: {
                if (KeyNe(&F<Key>(0x1dc), &gNullKey)) {
                    PlantItem* a = CastPlant(src);
                    if (!a) goto done;
                    ok = KeyEq(a->GetKey(&f11plant), &F<Key>(0x1dc));
                } else {
                    if (!KeyNe(&F<Key>(0x1e8), &gNullKey)) goto done;
                    AnimItem* a = CastAnimal(src);
                    if (!a) goto done;
                    ok = KeyEq(a->GetKey(), &F<Key>(0x1e8));
                }
                break;
            }
            default:
                goto done;
            }
        }
        if (!ok) break;
    finish:
        if (F<uint8_t>(0x214)) {
            if (F<uint32_t>(0x44) != 0xbb448992) break;
            if (F<int>(0x1bc) != 0) break;
            mi->FUN_00c5ed90(1);
            void* obj = F<void*>(0x148);
            if (!obj) obj = mi;
            int owner = *(int*)((char*)mi->GetModel() + 0x13c);
            int empire = *(int*)((char*)mi->GetOwnerEmpire() + 0x84);
            int text = SlotId(mi);
            int ctx = ((StarRec*)owner)->GetCommContext();
            GetCommManager()->AddEntry(empire, ctx, text, 0x932a66fe, obj, 0, 0);
        } else {
            void* pl = GetActivePlanet();
            if (pl) mi->FUN_00c47180(*(void**)((char*)pl + 0x13c));
            mi->Complete();
        }
        break;
    }
    }
done:
    BaseHandleMessage(msg, m);
}
