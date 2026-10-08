// Slice s01074bb0: SP::cSPUISpace message handler (IHandlerRC::HandleMessage override).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// `this` here is the IHandlerRC subobject (cSPUISpace + 0xc), so member offsets below are
// relative to the subobject and the cSPUISpace methods are called on (this - 0xc).
#include "types.h"

typedef unsigned int uint;

struct Key3 { uint a, b, c; };           // resource key (instance, group, type order as stored)

// --------------------------------------------------------------------------- small stubs
struct IEffect {                         // EA::Swarm::cIVisualEffect (slots used here)
    virtual void v00();
    virtual void Release();              // 0x04
    virtual void Start(int flag);        // 0x08
    virtual void Stop(int flag);         // 0x0c
    virtual bool IsPlaying();            // 0x10
    virtual void v14();
    virtual void SetTransform(void* xf); // 0x18
};

struct EffectRef {                       // EA::AutoRefCount<cIVisualEffect>
    IEffect* p;
    IEffect** AsPPTypeParam();           // 0x00a16f40
    ~EffectRef() { if (p) p->Release(); }
};

struct EffectsMgr {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual bool CreateEffect(uint id, int unused, IEffect** out);   // 0x2c
};
EffectsMgr* __cdecl EffectsManager();                                // 0x0067ddd0

struct XformMsg {                        // 0x38 bytes; ctor 0x00434040
    uint16_t flags;                      // |4 position, |2 matrix
    int16_t count;
    float pos[3];
    float scale;
    float mat[9];
    XformMsg();
    void SetPosition(const float* v);    // 0x00571d40 (ret 4)
};
struct Matrix3 { float m[9]; };

struct IWindow {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
    virtual void s70(); virtual void s74(); virtual void s78();
    virtual void SetVisible(int a, int b);                           // 0x7c
};
struct GlobalUI {
    IWindow* FindWindowByID(uint id);    // 0x00e012b0 (ret 4)
};

struct cString {
    char d[0x14]; const wchar_t* GetText(int flags);    // 0x006b55c0 (ret 4)
};

struct WString {                         // eastl::basic_string<wchar_t> (begin, end, capacity)
    const wchar_t* mpBegin; const wchar_t* mpEnd; const wchar_t* mpCapacity; uint mAllocator;
    void DeallocateSelf();               // 0x00933960
};
extern const wchar_t gEmptyStr[];        // 0x01667bac (2 chars)

struct Obj288 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void va(); virtual void vb();
    virtual void On(uint a); };                                      // 0x30

struct Planet {
    bool SetSpeciesAsScanned(const Key3* k);    // 0x00c73ea0 (ret 4)
};
struct Species {
    void GetUiName(WString* out);    // 0x004da330 (ret 4)
};
struct Creature {
    Species* GetSpeciesProfile();                                    // 0x00c0bbd0
    Key3* GetKey();                                                  // 0x00c0bc00
};
Creature* __cdecl CreatureFromObject(void* o);                       // 0x00f19200
void* __cdecl ObjectFromKey(void* o);                                // 0x00c9f060
void* __cdecl IsCreatureOwned(Creature* c);                           // 0x00c0c380
struct Sel { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void* GetSelection(uint idx); };   // 0x1c
struct Sel2 {
    void* Resolve();    // 0x00bd6a60
};
struct Cfg { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void va(); virtual void vb();
    virtual int Query(uint id); };                                   // 0x30
Cfg* __cdecl ConfigManager();                                        // 0x0067dd30
struct MsgSub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void* GetObj();                      // 0x10
    virtual void v14();
    virtual uint* GetValuePtr(); };              // 0x18
struct Inv34 { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual float* GetPosition();                                    // 0x2c
    virtual Matrix3* GetOrientationQ(); };                           // 0x30 (quaternion ptr)
struct PlayerInv { char pad[0x34]; Inv34 sub; };
struct UFOSim {
    PlayerInv* GetPlayerInventory();    // 0x00a1ad60
};
UFOSim* __cdecl GetUFOSimulator();                                   // 0x00ffbe50
Matrix3* __cdecl Matrix3FromQuaternion(void* out, void* q);          // 0x0059c190

struct Empire {
    Key3* GetUFOKey();    // 0x00c326b0
};
Empire* __cdecl GetPlayerEmpire();                                   // 0x01021300
int __cdecl GetUniverseContext();                                    // 0x01021080
void* __cdecl GetActivePlanet();                                     // 0x01021260
struct GameOwner {
    int GetMode();    // 0x00fe42a0
};
struct SpaceGame {
    GameOwner* GetOwner2();    // 0x00bfc5f0
};
SpaceGame* __cdecl SpaceGameGet();                                   // 0x01002bd0
bool __cdecl world(int n);                                           // 0x00685520
struct Gate {
    bool Check();    // 0x00b5ca60
};
Gate* __cdecl GetGate();                                             // 0x00b3d230
struct NameTable {
    uint Lookup(const char* name);    // 0x00ad7db0
};
NameTable* __cdecl GetNameTable();                                   // 0x00b3d4d0
struct Notifier {
    void Notify(int code, uint value);    // 0x00e19350 (ret 8)
};
Notifier* __cdecl GetNotifier();                                     // 0x00b3d3f0
struct StarMgr {
    void* Lookup(void* planet);    // 0x00ba6dc0 (ret 4)
};
StarMgr* __cdecl StarManager();                                      // 0x00b3d2a0
struct StarMap {
    void RemoveVisualGroup(uint group, int flag);                    // 0x01045b90 (ret 8)
    void CreatePlanetRecordVisual(void* star, uint group, uint fx, int a, int b); // 0x01045910 (ret 0x14)
};
StarMap* __cdecl GetStarMap();                                       // 0x01046fc0
int __cdecl GetRecorderState();                                      // 0x00435e90
void __cdecl KillSetiEffects(uint id, int state);                    // 0x00435ed0

extern uint g15b929c;                                                // 0x015b929c
extern uint g15b9294;                                                // 0x015b9294
struct UIGlobals { char pad[0x14]; uint f14; char pad2[0xc]; void* f24; };
extern UIGlobals* g16e0d08;                                          // 0x016e0d08

struct Obj22c {
    void* GetField();    // 0x00ff3f00 (reads +0x8c)
};
struct DispStrat {
    uint GetDisplayStrategy();    // 0x0104bfe0 (reads +0x240)
};
struct Win59c {
    void Refresh();    // 0x00e36620
};

// cSPUISpace methods (called on this - 0xc)
struct UISpace {
    void F106b220(uint a);                                           // 0x0106b220
    void F1068f70();                                                 // 0x01068f70
    void F1067f60(int a);                                            // 0x01067f60
    void UpdateActivePlanetInfo();                                   // 0x0106a4e0
    void F106f120(void* m);                                          // 0x0106f120
    void F106a280();                                                 // 0x0106a280
    void F106aab0(bool b);                                           // 0x0106aab0
    void F106e5e0();                                                 // 0x0106e5e0
    void F106e630();                                                 // 0x0106e630
    void F106f160(void* m);                                          // 0x0106f160
    void F1071570();                                                 // 0x01071570
    void Init();                                                     // 0x01073700
    bool F1065e20();                                                 // 0x01065e20 (body below)
    void F1065e40();                                                 // 0x01065e40
    char pad[0x618]; uint mState618;
    void SetToolTip(void* subject, const wchar_t* title, const wchar_t* text, const Key3* key); // 0x01067c50
};

// Static helper receiving the key pointer in EAX (UFO key -> window image), 0x01066720.
struct Layout {
    IWindow* FindWindowByID(uint id, int flag);    // 0x008105b0 (ret 8)
};
struct LayoutHolder {
    Layout* GetBuffer();    // 0x0093b6c0
};
struct SpaceGameData { char pad[0x14]; struct UIRoot* ui; };
struct UIRoot { char pad[0x224]; LayoutHolder* holder; };
void __cdecl SetWindowImage(IWindow* w, const Key3* key, int idx);   // 0x00807bb0
__declspec(noinline) static void SetUFOImage(const Key3* key)
{
    Key3 k;
    k.a = key->a; k.b = key->b; k.c = key->c;
    k.b = 0x2f7d0004;
    Layout* l = 0;
    SpaceGameData* sg = (SpaceGameData*)SpaceGameGet();
    if (sg && sg->ui)
        l = sg->ui->holder->GetBuffer();
    IWindow* w = l->FindWindowByID(0xb0b00000, 1);
    SetWindowImage(w, &k, -1);
}

struct UIHandler {
    char p0[0x218];
    GlobalUI* mGlobalUI;            // +0x218
    char p1[0x22c - 0x21c];
    Obj22c* m22c;                   // +0x22c
    char p2[0x288 - 0x230];
    Obj288* m288;                   // +0x288
    char p3[0x2f8 - 0x28c];
    EffectRef mEffect;              // +0x2f8
    char p4[0x310 - 0x2fc];
    char* mOwner;                   // +0x310
    uint mLastKey;                  // +0x314
    char p5[0x458 - 0x318];
    cString mText458;               // +0x458
    cString mText46c;               // +0x46c
    char p7[0x494 - 0x46c - 0x14];
    cString mText494;               // +0x494
    char p8[0x59c - 0x494 - 0x14];
    Win59c* m59c;                   // +0x59c
    char p9[0x60c - 0x5a0];
    uint mBadgeState;               // +0x60c

    UISpace* Outer() { return (UISpace*)((char*)this - 0xc); }
    bool HandleMessage(uint msgID, void* msg);
};

// @ 0x01074bb0  SP::cSPUISpace::HandleMessage
bool UIHandler::HandleMessage(uint msgID, void* msg)
{
    char* m = (char*)msg;
    switch (msgID) {
    case 0x38cf2fc:
        Outer()->F106b220(*(uint*)(m + 8));
        return true;
    case 0xf62def:
        if (*(uint*)(m + 0x18) == 0xddb63e53) {
            Outer()->F1068f70();
            return false;
        }
        break;
    case 0x3ac86ad:
        Outer()->F1067f60(1);
        if (world(2)) {
            IWindow* w = mGlobalUI->FindWindowByID(0x7ce6631);
            if (w) w->SetVisible(1, 0);
        }
        return false;
    case 0x44f1189: {
        uint id = *(uint*)(m + 8);
        if (id == GetNameTable()->Lookup("SPG_MasterBadge")) {
            if (mEffect.p && mEffect.p->IsPlaying())
                mEffect.p->Stop(1);
        }
        return false;
    }
    case 0x3ac86b5:
        Outer()->F1067f60(0);
        if (world(2)) {
            IWindow* w = mGlobalUI->FindWindowByID(0x7ce6631);
            if (w) w->SetVisible(1, 1);
        }
        return false;
    case 0x490d429:
        Outer()->UpdateActivePlanetInfo();
        return true;
    case 0x5da932e:
        SetUFOImage(GetPlayerEmpire()->GetUFOKey());
        return false;
    case 0x534052c: {
        if (GetUniverseContext() != 0) return false;
        if (GetGate()->Check()) return false;
        void* o = ((MsgSub*)msg)->GetObj();
        void* sel = ((Sel*)o)->GetSelection(0);
        Creature* c = CreatureFromObject(ObjectFromKey(((Sel2*)sel)->Resolve()));
        if (c) {
            void* owned = IsCreatureOwned(c);
            Species* sp = c->GetSpeciesProfile();
            Key3 key;
            WString name;
            name.mpBegin = gEmptyStr; name.mpEnd = gEmptyStr; name.mpCapacity = gEmptyStr + 1;
            sp->GetUiName(&name);
            UIGlobals* g = g16e0d08;
            g->f14 = 0;
            g->f24 = sp;
            {
                Key3* k = c->GetKey();
                key.a = k->a; key.b = k->b; key.c = k->c;
            }
            key.b = 0x2f7d0004;
            if (key.a != mLastKey) {
                mLastKey = key.a;
                void* planet = GetActivePlanet();
                char* target;
                if (owned) {
                    target = mOwner ? mOwner + 4 : 0;
                    const wchar_t* title = name.mpBegin;
                    Outer()->SetToolTip(target, title, mText458.GetText(0), &key);
                } else {
                    if (planet && !((Planet*)planet)->SetSpeciesAsScanned(c->GetKey())) {
                        target = mOwner ? mOwner + 4 : 0;
                        Outer()->SetToolTip(target, mText494.GetText(0), 0, 0);
                    } else {
                        target = mOwner ? mOwner + 4 : 0;
                        const wchar_t* title = name.mpBegin;
                        Outer()->SetToolTip(target, title, mText46c.GetText(0), &key);
                    }
                }
            }
            name.DeallocateSelf();
            return false;
        }
        if (m59c) m59c->Refresh();
        return false;
    }
    case 0x5e793a6:
        Outer()->F106f120(msg);
        if (*(int*)(m + 0x14) == 2) {
            uint* r = ((MsgSub*)msg)->GetValuePtr();
            GetNotifier()->Notify(-0xb, *r);
        }
        return false;
    case 0x6174b67:
        Outer()->F106a280();
        return true;
    case 0x5e793b4:
        if (m288) m288->On(*(uint*)m);
        return false;
    case 0x61dae5c:
        if (msg == m22c->GetField()) {
            bool b = ((DispStrat*)msg)->GetDisplayStrategy() == 0xe7c9ede0;
            Outer()->F106aab0(b);
        }
        return false;
    case 0x62b45bb:
        KillSetiEffects(0xefaaa0c7, GetRecorderState());
        Outer()->F106e5e0();
    retTrue:
        return true;
    case 0x61dae65:
        if (msg == m22c->GetField())
            Outer()->F106aab0(false);
        return false;
    case 0x62b45c3:
        KillSetiEffects(0xefaaa0c7, GetRecorderState());
        Outer()->F106e630();
        return true;
    case 0x64e43b9:
        if (*(uint*)(m + 8) == 0x4dc4aacb)
            mBadgeState = 3;
        return false;
    case 0x635ae73:
        Outer()->F106f160(msg);
        return false;
    case 0x65ff54a:
        if (*(uint*)(m + 0x10) == g15b929c && *(uint*)(m + 0x18) == g15b9294) {
            UISpace* o = Outer();
            o->F1071570();
            o->Init();
        }
        return false;
    case 0x665e639: {
        EffectRef ref;
        ref.p = 0;
        EffectsManager()->CreateEffect(0x31a596d6, 0, ref.AsPPTypeParam());
        if (ref.p) {
            PlayerInv* inv = GetUFOSimulator()->GetPlayerInventory();
            XformMsg xf;
            xf.SetPosition(inv->sub.GetPosition());
            Matrix3 tmp;
            Matrix3* mat = Matrix3FromQuaternion(&tmp, inv->sub.GetOrientationQ());
            *(Matrix3*)xf.mat = *mat;
            xf.flags |= 2;
            xf.count += 1;
            ref.p->SetTransform(&xf);
            ref.p->Start(0);
        }
        return false;
    }
    case 0x665e1ab: {
        uint id;
        switch (SpaceGameGet()->GetOwner2()->GetMode()) {
        case 0: id = 0xe14ab551; break;
        case 1: id = 0xe14ab550; break;
        case 2: id = 0xe14ab553; break;
        case 3: id = 0xe14ab552; break;
        case 4: id = 0xe14ab555; break;
        case 5: id = 0xe14ab554; break;
        case 6: id = 0xe14ab557; break;
        case 7: id = 0xe14ab556; break;
        case 8: id = 0xe14ab559; break;
        case 9: id = 0xe14ab558; break;
        case 10: id = 0xf89b6cc0; break;
        default:
            goto retTrue;
        }
        EffectRef& r = mEffect;
        if (r.p && r.p->IsPlaying())
            r.p->Stop(1);
        EffectsManager()->CreateEffect(id, 0, r.AsPPTypeParam());
        if (r.p)
            r.p->Start(0);
        return true;
    }
    case 0x670eccd:
        if (ConfigManager()->Query(0x4ea96cb) == 0) {
            if (Outer()->F1065e20()) {
                Outer()->F1065e40();
                return false;
            }
        }
        return false;
    case 0x68996fb: {
        uint planet = *(uint*)(m + 8);
        if (planet) {
            void* star = StarManager()->Lookup((void*)planet);
            if (star) {
                GetStarMap()->RemoveVisualGroup(0x626fd8e, 1);
                if (*(int*)(m + 0x10) == 1)
                    GetStarMap()->CreatePlanetRecordVisual(star, 0x626fd8e, 0x587f7ac7, 1, 1);
            }
        }
        return true;
    }
    case 0x6779f04: {
        uint v = *(uint*)m;
        GetNotifier()->Notify(-0xd, v);
        return false;
    }
    }
    return false;
}

// @ 0x01065e20  (same-TU callee: lets cl keep ECX across the call)
__declspec(noinline) bool UISpace::F1065e20()
{
    int s = mState618;
    if (s == 1 || s == 2 || s == 5 || s == 7) return true;
    return false;
}
