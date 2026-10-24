// Slice s00be6f90: cCity message-listener subobject (this = city + 0x20c).
// Built /O2 /MD /Gy /TP /arch:SSE2 (no EH frame, no cookie).
#include <math.h>
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

struct Vec3f { float x, y, z; };

// Shared sub-object interface (at +0x34 of Thing320/Thing324; also the candidate agents).
struct Ctx {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual Vec3f* GetPosition();                    // +0x2c
    virtual void s12(); virtual void s13();
    virtual void Fn38(void* v);                      // +0x38
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual Vec3f* Fn5C(Vec3f* out);                 // +0x5c
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual void s44(); virtual void s45();
    virtual Ctx* FnB8(u32 key);                      // +0xb8
    virtual void s47();
    virtual void FnC0();                             // +0xc0
    void FnBD0000();                                 // 0x00bd0000
    bool __thiscall CanOccupy(const Vec3f* pos);     // 0x00c9e940 (ret 4)
};

struct Thing2F0 {
    void Fn(void* owner, u32 v);                     // 0x00ff2810 (ret 8)
};

struct Thing320 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34();
    virtual u32 Fn8C();                              // +0x8c
    char pad04[0x34 - 4];
    Ctx ctx;                                         // +0x34
};

struct Thing324 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void Fn60(u32 v);                        // +0x60
    char pad04[0x34 - 4];
    Ctx ctx;                                         // +0x34
    char pad38[0x108 - 0x38];
    u8  f108;                                        // +0x108
    char pad109[0x25c - 0x109];
    float f25c;                                      // +0x25c
    char pad260[0x34c - 0x260];
    u32 f34c;                                        // +0x34c
};

struct PlanetRec { char pad[0x13c]; u32 f13c; };

struct Thing590 {
    void Fn(void* owner);                            // 0x00bf2660 (ret 4)
};
PlanetRec* __cdecl Fn1021260();                      // 0x01021260
u32 __cdecl FnBebc90(u32 a, u32 b);                  // 0x00bebc90

struct City {
    char pad[0x29c];
    u32  f29c;
    char pad2[0x2f0 - 0x2a0];
    Thing2F0* f2f0;                          // +0x2f0
    char pad2f4[0x320 - 0x2f4];
    Thing320* f320;                          // +0x320
    Thing324* f324;                          // +0x324
    char pad328[0x354 - 0x328];
    Ctx** f354;                              // +0x354 (vector begin)
    Ctx** f358;                              // +0x358 (vector end)
    char pad35c[0x44c - 0x35c];
    Q*   dummy;
    char pad450[0x540 - 0x450];
    u32  f540;                               // +0x540
    char pad544[0x590 - 0x544];
    Thing590* f590;                          // +0x590
    char pad594[0x761 - 0x594];
    u8   f761;                               // +0x761
    Q* __thiscall AddThing(u32 a, u32 type, Key k, int z);   // 0xbddda0
    void __thiscall F73d0(u32 a, u8 b);             // 0xbe73d0
    u32  __thiscall OverwriteNounsFromNounManager(u32 id);   // 0xbe7370
    u32  __thiscall Fn53b0(const char* name, u32 id);        // 0xbe53b0
    void __thiscall FnBDaf50();                     // 0x00bdaf50
    void __thiscall FnBD9710();                     // 0x00bd9710
    void __thiscall FnBDbaa0();                     // 0x00bdbaa0
    void __thiscall FnBDaea0();                     // 0x00bdaea0
    void __thiscall FnBD88c0();                     // 0x00bd88c0
    void __thiscall Fn6f90();                       // 0x00be6f90
    void __thiscall FnBe5180();                     // 0xbe5180
    void __thiscall FnBe5dd0();                     // 0xbe5dd0
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

// @ 0x00be7370
extern const char NounNameA[];
extern const char NounNameB[];
extern const char NounNameC[];

u32 __thiscall City::OverwriteNounsFromNounManager(u32 id)
{
    const char* name;
    switch (id) {
    case 0x1a55e4d: name = NounNameA; break;
    case 0xecade42: name = NounNameB; break;
    default:        name = NounNameC; break;
    }
    u32 r = Fn53b0(name, id);
    if (f2f0 != 0) {
        PlanetRec* p = Fn1021260();
        f2f0->Fn(this, p->f13c);
    }
    return r;
}

// @ 0x00be73d0
void __thiscall City::F73d0(u32 planet, u8 flag)
{
    if (planet != f540) {
        f540 = planet;
        if (f324) {
            f324->f108 = flag;
            Thing324* p = f324;
            p->Fn60(FnBebc90(planet, p->f34c));
        }
        FnBe5180();
        FnBe5dd0();
    }
    int n = (int)(f358 - f354);
    for (int i = 0; i < n; ++i) {
        Ctx* c = f354[i];
        if (c)
            c->FnBD0000();
    }
    if (f590)
        f590->Fn(this);
}

// --- InfoRec vector (this = a {begin,end,capacity} vector at +0/+4/+8) -----
inline void* operator new(unsigned int, void* p) { return p; }

struct FloatVec {                                    // 0x14 bytes
    float* mpBegin; float* mpEnd; float* mpCap;
    int mAllocState[2];
    FloatVec& operator=(const FloatVec& o);          // 0x0050d4e0
};
struct InfoRec {                                     // 0x20 bytes
    Vec3 pos;
    FloatVec v;
    InfoRec(const InfoRec& o);                       // 0x00be0d70
};
InfoRec* __cdecl CopyInfoRecs(InfoRec* first, InfoRec* last, InfoRec* dst);     // 0x00be0dd0
InfoRec* __cdecl CopyInfoRecsBwd(InfoRec* first, InfoRec* last, InfoRec* dst);  // 0x00be0ed0
void* __cdecl MoveInfoRecs(InfoRec* first, InfoRec* last, InfoRec* dst);        // 0x00bda890
void* __cdecl EAAllocate(u32 n, const char* tag, int a, int b, int file, int line);  // 0x00f473a0
void  __cdecl EFree(void* p);                                                    // 0x00f47380
extern char kEastlFile[];                            // 0x013ebb38 "...EASTL/allocator.h"
extern char kSimulatorTag[];                         // 0x013f09b4 "Simulator"

struct InfoRecVec {
    InfoRec* mpBegin;                                // +0
    InfoRec* mpEnd;                                  // +4
    InfoRec* mpCap;                                  // +8
    void __thiscall Insert(InfoRec* pos, InfoRec* value);   // 0x00be7aa0
};

// @ 0x00be7aa0
void __thiscall InfoRecVec::Insert(InfoRec* pos, InfoRec* value)
{
    InfoRec* end = mpEnd;
    if (end != mpCap) {
        InfoRec* v = value;
        if (v >= pos && v < end)
            v += 1;
        if (end)
            new (end) InfoRec(*(end - 1));
        CopyInfoRecsBwd(pos, mpEnd - 1, mpEnd);
        pos->pos = v->pos;
        pos->v = v->v;
        mpEnd = mpEnd + 1;
        return;
    }
    u32 count = (u32)(mpEnd - mpBegin);
    u32 n;
    if (count > 0)
        n = count * 2;
    else
        n = 1;
    InfoRec* nd = 0;
    if (n != 0)
        nd = (InfoRec*)EAAllocate(n << 5, kSimulatorTag, 0, 0, (int)kEastlFile, 0xd1);
    else
        nd = 0;
    InfoRec* first = mpBegin;
    InfoRec* dst = CopyInfoRecs(first, pos, nd);
    MoveInfoRecs(first, pos, nd);
    if (dst)
        new (dst) InfoRec(*value);
    InfoRec* last = mpEnd;
    dst += 1;
    InfoRec* ni = CopyInfoRecs(pos, last, dst);
    MoveInfoRecs(pos, last, dst);
    InfoRec* old = mpBegin;
    if (old != 0 && ((int*)old)[-1] != 0)
        EFree(old);
    mpBegin = nd;
    mpEnd = ni;
    mpCap = (InfoRec*)((char*)nd + (n << 5));
}

// ---------------------------------------------------------------------------
// City::Fn6f90 -- rebuild the city's action circle from the nearby agents.
// ---------------------------------------------------------------------------
struct CtxVec { Ctx** mpBegin; Ctx** mpEnd; Ctx** mpCap; };       // {begin,end,cap}
struct SlotVec { u32* mpBegin; u32* mpEnd; u32* mpCap; };

class cActionCircle {
 public:
    class tSlot {
     public:
        bool mOccupied;                              // +0x0
        char _pad0[3];
        void* mpReserving;                           // +0x4
        u32   mReservingId;                          // +0x8
        Vec3f mPos;                                  // +0xc
        void __thiscall Reserve(Ctx* noun);          // 0x00afa030
    };
    struct RawVec { void* b; void* e; void* c; int a[2]; };
    Vec3f mFacing;                                   // +0x0
    float mRadius;                                   // +0xc
    float mSlotRadius;                               // +0x10
    Vec3f mCenter;                                   // +0x14
    float mAltitude;                                 // +0x20
    int   mPacking;                                  // +0x24
    bool  mbRelative;                                // +0x28
    char  _pad28[3];
    float mOrientation[4];                           // +0x2c
    RawVec mAgents;                                  // +0x3c
    RawVec mSlots;                                   // +0x50

    cActionCircle();                                 // 0x00afba10
    ~cActionCircle();                                // 0x00afbad0
    void __thiscall SetAtCenter(const Vec3f* center, float radius,
                                const Vec3f* facing, float altitude);   // 0x00af9cf0
    tSlot* __thiscall SlotAt(u32 index);             // 0x00af9ff0
    void __thiscall FnAfef10(int mode, float v);     // 0x00afef10
    void __thiscall FnAfeff0(const Vec3f* p, SlotVec* out);  // 0x00afeff0
};

struct AgentMgr {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17();
    virtual void __thiscall FindAgents(const Vec3f* center, float radius,
                                       CtxVec* out, int a, int b, int c);   // +0x48
};
AgentMgr* __cdecl FnB3d240();                        // 0x00b3d240

struct Callback { void __thiscall FnAc8d40(); };     // 0x00ac8d40
Callback* __stdcall FnB3d480(City* c);               // 0x00b3d480 (ret 4)

struct SimSingleton {                                // 0xc8 bytes
    char pad0[0xa8];
    u8   f0a8;                                       // +0xa8
    SimSingleton();                                  // 0x00ae5c30
    static SimSingleton* Create(void* mem) { return new (mem) SimSingleton(); }
};

extern char gAppNameTag[];                           // 0x01654c05
extern SimSingleton* gSimSingleton;                  // 0x0167a60c
void* __cdecl GetCurrentGameMode();                  // 0x00b5b800
void  __cdecl FUN_00cac360(float x, float y, float z, float r);  // 0x00cac360

// @ 0x00be6f90
void __thiscall City::Fn6f90()
{
    FnBDaf50();
    FnBD9710();
    FnBDbaa0();
    FnB3d480(this)->FnAc8d40();
    FnBDaea0();
    FnBD88c0();

    if (GetCurrentGameMode() == (void*)gAppNameTag) {
        if (gSimSingleton == 0) {
            void* mem = EAAllocate(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
            gSimSingleton = mem ? SimSingleton::Create(mem) : 0;
        }
        gSimSingleton->f0a8 = 1;
    }

    if (f320 != 0) {
        Thing320* t = f320;
        u32 r = t->Fn8C();
        t->ctx.Fn38((void*)r);
    }

    CtxVec candidates = { 0, 0, 0 };
    float radius = f324->f25c + 16.0f;
    Ctx* ctx = &f324->ctx;
    Vec3f center = *ctx->GetPosition();
    {
        cActionCircle circle;
        Vec3f facingOut;
        circle.SetAtCenter(&center, radius, ctx->Fn5C(&facingOut), 0.0f);
        circle.FnAfef10(1, 8.0f);

        AgentMgr* mgr = FnB3d240();
        mgr->FindAgents(&center, radius, &candidates, 0, 0, 0);

        int n = (int)(candidates.mpEnd - candidates.mpBegin);
        for (int i = 0; i < n; ++i) {
            Ctx* noun = candidates.mpBegin[i];
            Ctx* id;
            if (noun != 0 && (id = noun->FnB8(0x137e8e0)) != 0) {
                Vec3f target;
                SlotVec slots = { 0, 0, 0 };
                Vec3f* pos = noun->GetPosition();
                float dx = pos->x - center.x;
                float dy = pos->y - center.y;
                float dz = pos->z - center.z;
                float len2 = dx * dx + dy * dy + dz * dz + 1e-8f;
                float len = sqrtf(len2);
                float inv = 1.0f / len;
                target.x = (inv * dx) * radius + center.x;
                target.y = (inv * dy) * radius + center.y;
                target.z = (inv * dz) * radius + center.z;
                circle.FnAfeff0(&target, &slots);

                int m = (int)(slots.mpEnd - slots.mpBegin);
                int j = 0;
                if (m > 0) {
                    do {
                        cActionCircle::tSlot* slot = circle.SlotAt(slots.mpBegin[j]);
                        if (slot != 0 && !slot->mOccupied && id->CanOccupy(&slot->mPos)) {
                            slot->Reserve(id);
                            noun->Fn38(&slot->mPos);
                            break;
                        }
                        ++j;
                    } while (j < m);
                }
                if (j == m)
                    noun->Fn38(&target);
                if (slots.mpBegin != 0 && ((int*)slots.mpBegin)[-1] != 0)
                    EFree(slots.mpBegin);
            }
        }

        FUN_00cac360(center.x, center.y, center.z, radius);
        if (f761 != 0) {
            FnBe5dd0();
            f761 = 0;
        }
    }

    Ctx** end = candidates.mpEnd;
    for (Ctx** p = candidates.mpBegin; p < end; ++p) {
        if (*p != 0)
            (*p)->FnC0();
    }
    if (candidates.mpBegin != 0 && ((int*)candidates.mpBegin)[-1] != 0)
        EFree(candidates.mpBegin);
}
