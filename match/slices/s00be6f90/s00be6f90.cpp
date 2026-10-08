// Slice s00be6f90: cCity message-listener subobject (this = city + 0x20c).
// Built /O2 /MD /Gy /TP /arch:SSE2 (no EH frame, no cookie).
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;

struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };
struct Mat3 { float m[9]; };
struct Key  { u32 a, b, c; Key() {} Key(const Key& o) : a(o.a), b(o.b), c(o.c) {} };

struct RefObj { virtual void AddRef(); virtual void Release(); };

// EA::AutoRefCount<T> as used by the original: AsPPTypeParam is an out-of-line shared helper.
template <class T> struct AutoRef {
    T* p;
    AutoRef() : p(0) {}
    ~AutoRef() { if (p) p->Release(); }
    T** __thiscall AsPPTypeParam();      // 0xa16f40 (declared only: stays an out-of-line call)
};

struct PropList : RefObj {};
struct Fx : RefObj {
    virtual void Start(int);                         // 0x08
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual void SetTransform(const struct XformMsg* m);   // 0x18
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void SetParam(int which, const void* v, int n);   // 0x44
};

struct XformMsg {                                    // 0x38 bytes
    u16  flags, count;
    Vec3 pos;
    u32  pad10;
    Mat3 mat;
    XformMsg();                                      // 0x434040
    void __thiscall SetPosition(const Vec3* p);      // 0x571d40
};

struct PropMgr {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual bool Get(u32 owner, u32 id, PropList** out);         // 0x2c
};
struct EffMgr {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual bool Create(u32 id, int flags, Fx** out);            // 0x2c
};
PropMgr* __cdecl PropertyManager();                  // 0x67de30
EffMgr*  __cdecl EffectsManager();                   // 0x67ddd0
bool     __cdecl GetPropertyAsUint32(PropList* l, u32 key, u32* out);   // 0x4af210
Mat3*    __cdecl Matrix3A(Mat3* out, const void* q); // 0x4a9b40
Mat3*    __cdecl Matrix3FromQuaternion(Mat3* out, const void* q);       // 0x59c190

struct Obj120 {                                      // this - 0xec
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual Vec3* GetPosition();                     // 0x2c
    virtual void* GetOrientation();                  // 0x30
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual bool IsReady();                          // 0x58
};

struct Sub { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42();
    virtual u32* Flags();                            // 0xac
};
struct Obj118 {                                      // this[0x118]
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual u32 GetB();                              // 0x64
    virtual void s26();
    virtual u32 GetA();                              // 0x6c
    char pad[0x34 - 4];
};
struct Obj118S : Obj118 { Sub sub; };

struct Node {
    u32   __thiscall Type();                         // 0xfc7e50
    void* __thiscall GetAllocator();                 // 0x7f54d0
};
u32 __cdecl AllocKey(void* alloc, u32 type);         // 0xc9e6d0

struct ModelHolder { char pad[0xc4]; Vec3 pos; Key* __thiscall GetModelTypeKey(u32 x); };  // 0xbf9770

struct Q {
    void __thiscall A(Node* n);                      // 0xa110b0
    void __thiscall B(u32 v);                        // 0xc9eae0
};
struct City {
    char pad[0x29c];
    u32  f29c;
    char pad2[0x44c - 0x2a0];
    Q*   dummy;
    Q* __thiscall AddThing(u32 a, u32 type, Key k, int z);   // 0xbddda0
    void __thiscall F73d0(u32 a, int b);             // 0xbe73d0
};
struct Civ { char pad[0x44c]; City* city; };
struct NounMgr { Civ* __thiscall GetPlayerCivilization(); };    // 0xb25fb0
NounMgr* __cdecl NounManager();                      // 0xb3d300
struct TimeMgr { void __thiscall DecPauseGate(u32 g); };        // 0xb32250
TimeMgr* __cdecl GameTimeManager();                  // 0xb3d380
struct CivStrategy {
    void __thiscall A();                             // 0xcfa120
    bool __thiscall CanBuildSeaVehicles();           // 0xcf75d0
    void __thiscall B();                             // 0xcf8e00
    void __thiscall C();                             // 0xcf7520
};
CivStrategy* __cdecl CivModeStrategyGet();           // 0xcf74c0
void* __cdecl GetActivePlanetRecord();               // 0x10212a0
void  __cdecl PlanetHook(City* c, u32 a, void* rec); // 0xbe2440

struct Msg {
    u32 pad0, pad4;
    u32 data;        // +8
    u32 padc;
    Node* f10;
    u32 pad14;
    u32 f18;
};

static __forceinline void StartFx(Obj120* o, Fx* fx, const Vec3* pos)
{
    XformMsg m;
    m.SetPosition(o->GetPosition());
    Mat3 tmp;
    m.mat = *Matrix3A(&tmp, o->GetOrientation());
    m.flags |= 2;
    m.count++;
    fx->SetTransform(&m);
    fx->SetParam(5, pos, 3);
    fx->Start(0);
}

struct CityListener {
    char pad0[0xe4];
    u32  fE4;
    char pad1[0x118 - 0xe8];
    Obj118S* f118;
    char pad2[0x334 - 0x11c];
    u32  f334;
    char pad3[0x384 - 0x338];
    ModelHolder* f384;

    bool __thiscall HandleMessage(u32 id, Msg* msg);        // 0xbe7470
};

// @ 0x00be7470
bool __thiscall CityListener::HandleMessage(u32 id, Msg* msg)
{
#define CITY ((City*)((char*)this - 0x20c))
#define OBJ ((Obj120*)((char*)this - 0xec))
    switch (id) {
    case 0x5416d55: {
        if (msg->data != (u32)CITY) return 0;
        Node* n = msg->f10;
        u32 mem = msg->f18;
        u32 t = AllocKey(n->GetAllocator(), n->Type());
        u32 w = f334;
        Key* k = f384->GetModelTypeKey(t);
        Q* q = CITY->AddThing(w, n->Type(), *k, 0);
        q->A(n);
        q->B(mem);
        return 0;
    }
    case 0x40fafdf: {
        NounMgr* nm = NounManager();
        if (!nm) return 0;
        City* pc = nm->GetPlayerCivilization()->city;
        if (pc != CITY) return 0;
        if (msg->data == 0x5107b1a) {
            u32 kind = f118->GetA();
            u32 la = f118->GetB();
            CITY->F73d0(((City*)pc)->f29c, 1);
            u32 lb = f118->GetB();
            u32 k0 = 0, k1 = 0;
            switch (kind) {
            case 0: k0 = 0x5f77883; k1 = 0x5f779c3; break;
            case 1: k0 = 0x5f779b2; k1 = 0x5f779c8; break;
            case 2: k0 = 0x5f779b8; k1 = 0x5f779cd; break;
            case 3: k0 = 0x5f779bd; k1 = 0x5f779d2; break;
            }
            Vec3 pos = f384->pos;
            AutoRef<PropList> list;
            if (PropertyManager()->Get(la, 0x2e4b4cc, list.AsPPTypeParam())) {
                u32 id = 0;
                if (GetPropertyAsUint32(list.p, k0, &id)) {
                    AutoRef<Fx> fx;
                    if (EffectsManager()->Create(id, 0, fx.AsPPTypeParam())) {
                        StartFx(OBJ, fx.p, &pos);
                        AutoRef<PropList> list2;
                        if (PropertyManager()->Get(lb, 0x2e4b4cc, list2.AsPPTypeParam())) {
                            u32 id2 = 0;
                            if (GetPropertyAsUint32(list2.p, k1, &id2)) {
                                AutoRef<Fx> fx2;
                                if (EffectsManager()->Create(id2, 0, fx2.AsPPTypeParam()))
                                    StartFx(OBJ, fx2.p, &pos);
                            }
                        }
                    }
                }
            }
        }
        GameTimeManager()->DecPauseGate(0x4bf38a7);
        CivModeStrategyGet()->A();
        if (!CivModeStrategyGet()->CanBuildSeaVehicles()) return 0;
        CivModeStrategyGet()->B();
        CivModeStrategyGet()->C();
        return 1;
    }
    case 0x56e50f1:
        if (msg->data != (u32)CITY || fE4 == 0) return 0;
        PlanetHook(CITY, fE4, GetActivePlanetRecord());
        return 0;
    case 0x6787056: {
        AutoRef<Fx> fx;
        EffMgr* em = EffectsManager();
        if (fx.p) { Fx* old = fx.p; fx.p = 0; old->Release(); }
        if (em->Create(0xea04f48c, 0, &fx.p)) {
            XformMsg m;
            const Vec3* p = OBJ->GetPosition();
            m.pos.x = p->x; m.pos.y = p->y; m.pos.z = p->z;
            m.flags |= 4;
            m.count++;
            Mat3 tmp;
            m.mat = *Matrix3FromQuaternion(&tmp, OBJ->GetOrientation());
            m.flags |= 2;
            m.count++;
            fx.p->SetTransform(&m);
            fx.p->Start(0);
        }
        return 0;
    }
    case 0x5f74817:
        if (OBJ->IsReady() && msg->data == 1) {
            Obj118S* p = f118;
            u32* fl = p->sub.Flags();
            if (fl) fl[1] |= 1;
        }
        return 0;
    }
    return 0;
#undef CITY
#undef OBJ
}
