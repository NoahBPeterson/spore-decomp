// Slice s00e0df70 (batch bfs1 #39).  cSPUIMinimapWin helpers.
// 32-bit MSVC 2008 SP1, /O2 /arch:SSE.
#include <math.h>
#include <intrin.h>

struct Vector3 { float x, y, z; };
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

static inline void Release(void* p) {
    if (p) ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
}
static inline void AddRef(void* p) {
    if (p) ((void(__thiscall*)(void*))(*(void***)p)[0 / 4])(p);
}

// ===========================================================================
//  0x00e0e9a0  destructor over an array of 0x14-byte records
// ===========================================================================
// @ 0x00e0e9a0
void __stdcall e0e9a0(u32 begin, u32 end) {
    if (begin < end) {
        u32 n = ((end - begin) - 1) / 0x14 + 1;
        char* e = (char*)begin + 0xc;
        do {
            void* p1 = *(void**)(e + 4);
            if (p1) Release(p1);
            void* p0 = *(void**)(e + 0);
            if (p0) Release(p0);
            e += 0x14;
            --n;
        } while (n != 0);
    }
}

// ===========================================================================
//  0x00e0e9f0  eastl::lower_bound<SP::cDataSerializationInfo>
// ===========================================================================
struct DataInfo {
    u32   mKey;                  // +0x00
    char  pad_04[0x10];
};
// @ 0x00e0e9f0
DataInfo* __cdecl lower_bound_DataInfo(DataInfo* first, DataInfo* last, u32* value) {
    int n = (int)(last - first);
    while (n > 0) {
        int half = n >> 1;
        DataInfo* mid = first + half;
        if (mid->mKey < *value) {
            first = mid + 1;
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// ===========================================================================
//  0x00e0ea40  copy-assign with two refcounted members
// ===========================================================================
struct RefHolder {
    void* mp0;                   // +0x00
    u8    b4;                    // +0x04
    char  pad_05[3];
    void* mp8;                   // +0x08
    void* mpc;                   // +0x0c
    RefHolder* Assign(const RefHolder& o);   // copy-assign (likely operator=; named so the checker can find it)
};
// @ 0x00e0ea40
RefHolder* RefHolder::Assign(const RefHolder& o) {
    mp0 = o.mp0;
    b4 = o.b4;
    if (o.mp8 != mp8) {
        AddRef(o.mp8);
        void* old = mp8;
        mp8 = o.mp8;
        Release(old);
    }
    if (o.mpc != mpc) {
        AddRef(o.mpc);
        void* old = mpc;
        mpc = o.mpc;
        Release(old);
    }
    return this;
}


// ---- vtable stub classes (generated padding around the real slots) ----
struct IRef0 {
    virtual void AddRef();
    virtual void Release();
};
struct IRef1 {
    virtual void v00();
    virtual void AddRef();
    virtual void Release();
};
struct Obj19 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void* f3(int id);
};
struct IWin {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual IWin* GetParent();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual Obj19* f19();
    virtual void f20(int a);
    virtual void v15();
    virtual void v16();
    virtual void f23(int a);
    virtual void SetArea(const float* r);
    virtual void v19();
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void v1e();
    virtual void f31(int a, int b);
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void f36();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v2a();
    virtual void f43(int a);
    virtual void v2c();
    virtual void v2d();
    virtual void v2e();
    virtual void v2f();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void AddChild(IWin* w);
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v3a();
    virtual void v3b();
    virtual IWin* GetChild(unsigned id, int flag);
};
struct ResMgr {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual bool Get(const unsigned* key, IRef0** out, int a, int b, int c, int d);
};
struct TexFactory {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void Register(void* tex);
    virtual void v0e();
    virtual void v0f();
    virtual struct TexObj* Create(int w, int h, int a, int b, int c, int d);
};
struct DistGrid {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual struct GridSub* f3();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void v1e();
    virtual void v1f();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v2a();
    virtual void v2b();
    virtual void v2c();
    virtual void v2d();
    virtual void v2e();
    virtual void v2f();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual const float* f51();
    virtual const float* f52();
};
struct MsgServer {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void Register(void* handler, int id);
};
struct IXfObj {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual const Vector3* GetPos();
    virtual const void* GetRot();
};
struct MinimapVt {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v1a();
    virtual void v1b();
    virtual void v1c();
    virtual void v1d();
    virtual void v1e();
    virtual void v1f();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void Refresh();
};

// ===========================================================================
//  Types
// ===========================================================================

struct Matrix3 {
    Vector3 row0, row1, row2;
    Matrix3& Assign(const Matrix3& m);          // 0x41cb40
};
struct XForm {                      // PartTransform: flags, change counter, position, scale, basis
    unsigned short flags;           // +0
    unsigned short rev;             // +2
    Vector3 pos;                    // +4
    float scale;                    // +0x10
    Matrix3 m;                      // +0x14
    void Invert();                  // 0x40efa0 PartTransform::Invert
    void SetPos(const Vector3& p) {
        const int* src = (const int*)&p;
        int y = src[1];
        int x = src[0];
        int z = src[2];
        flags |= 4;
        rev++;
        ((int*)&pos)[1] = y;
        ((int*)&pos)[0] = x;
        ((int*)&pos)[2] = z;
    }
    void SetBasis(const Matrix3& b) { m = b; flags |= 2; rev++; }
};

struct LockInfo { void* data; int a, b, c, d, e, f; };
struct Tex {
    int Lock(int mode, int zero, LockInfo* out);    // 0x11ef750
    void Unlock(LockInfo* info);                    // 0x11ef880
};
struct TexObj { Tex* tex; unsigned flags; };
struct ResObj;
struct Image {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual ResObj* Find(const char* name);          // +0xc
    int f4;                                          // +4
    char pad8[0xc];
    void* GetAllocator();                            // 0x7f54d0
    Image(TexObj* t);                                // 0x8333b0 UI::Image::Image
};
struct TexImage : IRef0 {
    char pad4[0x28];
    TexImage(Image* img, int w, int h, float a, float b, float c, float d, int e);   // 0x9579f0
};
struct AllocObj { int pad; unsigned flags; int Fn46f260(); };
struct ResObj {
    AllocObj* GetAllocator();                        // 0x7f54d0 Resource::DatabasePackedFile::GetAllocator
};
struct Obj3Ret { void Fn82eb80(int a, void* alloc); };           // 0x82eb80
struct RefSlot {
    IRef0* p;
    void Assign(IRef0* v);                           // 0xb5f950 AutoRefCount::operator=
};
struct Layout : IRef1 {
    char pad4[0x14];
    Layout();                                        // 0x810000
    bool Init(const wchar_t* name, int a, int b, int c);   // 0x812160
    void SetVisibility(int v);                       // 0x810590
};
struct IconTree {
    char hdr[4];
    char sentinel[4];                                // +4 = end()
    void Find(void** out, const unsigned* key);      // 0xe5c780 eastl::rbtree::find
};
struct GridData : IRef0 { char pad4[0x18]; int count; char pad20[8]; int* table; };
struct GridSub { char pad[0x3c]; float f3c; };
struct PlanetModelObj { char pad[0x24]; int f24; };
struct Planet { char pad[0x13c]; struct PlanetSub* sub; };
struct PlanetSub { char pad[0xb4]; float f; };

// ---- globals / free functions -------------------------------------------------------------
extern const Matrix3 g_16a2070;                      // 0x16a2070
extern float g_1485720, g_13ec4b8, g_13f1160, g_141021c, g_13f2100;
extern unsigned char g_16a40b8;
extern int g_16a40bc;
extern unsigned g_16a40c0;
extern unsigned char g_16a40c8[];
extern unsigned g_16a38b8[];
extern const char g_147d84e[];                       // "...itorButtonBounceDuration"
extern const wchar_t g_147fb74[];                    // L"MinimapIcons"
extern const wchar_t g_147fb4c[];                    // L"ui_material_minimap"
extern const unsigned g_147f678[];                   // message id table
extern const unsigned g_key_a, g_key_b;

ResMgr*     __cdecl EA_GetManager();                 // 0x67dcd0
TexFactory* __cdecl GetTexFactory();                 // 0x67dd60
MsgServer*  __cdecl SP_MessageServer();              // 0x67dcc0
void        __cdecl FUN_00b3d460();
int         __cdecl GetUniverseContext();            // 0x1021080
Planet*     __cdecl GetActivePlanet();               // 0x1021260
PlanetModelObj* __cdecl PlanetModel();               // 0xb3d350
DistGrid*   __cdecl DebugDrawGrid();                 // 0xf48aa0
int         __cdecl GetCurrentGameMode();            // 0xb5b800
const void* __cdecl Matrix3FromQuaternion(void* out, const void* q);   // 0x59c190
Vector3*    __cdecl normalized_safe(Vector3* out, const Vector3* in);   // 0x449c20
void        __cdecl FUN_00957c20(Image* img, int a);
void        __cdecl UpdatePallete(unsigned* pal, int a, unsigned c1, unsigned c2, int v, int mode);   // 0xe0ad10
void        __cdecl FUN_00e0cba0(const float* a, const void* b, int c, int d, const float* e);
void        __cdecl FUN_00e0c820(const float* a, const void* b, int c, int d, const float* e, float f, bool g);
const float* __cdecl FUN_00e0b580(void* out, int a, const Vector3* v, const float* b, const float* c, float f, int g);
IRef0*      __cdecl GetImageFromLayout(Layout* l, unsigned id);   // 0x8061c0
void        __cdecl SetWindowSPMaterial(IWin* w, const wchar_t* name, int a);   // 0x808ad0
void*       __cdecl FUN_009512c0();
void*       __cdecl FUN_009512d0(int size, int a, const char* name, void* b);
void        __cdecl AnchorWindowToWindow(IWin* a, IWin* b, int flags, int c);    // 0x807340
void*       __cdecl memset(void* p, int v, unsigned n);
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);
struct PerfCount { unsigned lo, hi; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(PerfCount* c);
extern const char g_147fad0[], g_147fabc[], g_147fb90[], g_147fb38[], g_13f6b3c[];

struct CursorAttachment : IRef0 {
    char pad4[0xac];
    CursorAttachment();                              // 0xe2b8e0
};
struct CamBase1 { virtual void AddRef(); virtual void Release(); };
struct WinBase : CamBase1, IWin {
    WinBase();                                       // 0x962a10 EA::UTFWin::Window::Window
    char pad_win[0x20c - 8];
};
struct MinimapWin;
struct MinimapCamera : WinBase {
    int f20c;                                        // +0x20c
    int f210;                                        // +0x210
    virtual void AddRef();
    virtual void Release();
    virtual IWin* GetParent();
    MinimapCamera() : f20c(0), f210(0) { ((void(__thiscall*)(void*))(*(void***)this)[0])(this); }
    void SetOwner(MinimapWin* w);                    // 0xe0b230
};
void* __cdecl operator new(unsigned int, int, const char*, void*);

typedef void (__thiscall *VSlot)(void*);
static __forceinline void CallSlot(void* p, int i) { ((VSlot)(*(void***)p)[i])(p); }
// ---- cSPUIMinimapWin (retail layout reconstructed from the asm) ---------------------------
struct MinimapWin : MinimapVt, IWin {
    char pad_008[0x214 - 8];
    char handler[0x10];             // +0x214  EA::Messaging::AutoHandler
    void* msgServer;                // +0x224
    void* handlerPtr;               // +0x228
    const unsigned* msgTable;       // +0x22c
    int msgCount;                   // +0x230
    int m234;                       // +0x234
    char pad_238;
    unsigned char squareRaster;     // +0x239
    char pad_23a[2];
    int width;                      // +0x23c
    int height;                     // +0x240
    IRef0* mRoadIcon;               // +0x244
    IRef0* mMapImage;               // +0x248
    RefSlot mTexture;               // +0x24c
    IRef0* mIconImage;              // +0x250
    IRef0* mCamera;                 // +0x254
    Layout* mLayout;                // +0x258
    char pad_25c[4];
    unsigned swLo;                  // +0x260
    unsigned swHi;                  // +0x264
    int m268;                       // +0x268
    int m26c;                       // +0x26c
    int swMode;                     // +0x270
    char pad_274[8];
    Image* mImage;                  // +0x27c
    unsigned char edge[0x81];       // +0x280
    char pad_301[0x31c - 0x301];
    IconTree tree;                  // +0x31c
    char pad_324[0x338 - 0x324];
    float m338[3];                  // +0x338
    float m344[3];                  // +0x344
    float m350;                     // +0x350
    char pad_354[4];
    int m358;                       // +0x358
    unsigned m35c;                  // +0x35c
    int m360;                       // +0x360
    unsigned char b364;             // +0x364
    char pad_365[0x984 - 0x365];
    GridData* mGrid;                // +0x984
    IRef0* mCursor;                 // +0x988

    bool FindIcon(unsigned id, const float* dir, bool flag);          // 0xe0df70
    void Update();                                                    // 0xe1a0
    void build_edge_offsets();                                        // 0xe840
    bool Init();                                                      // 0xeab0
    bool Initialize();                                                // 0xb1fbf0 UTFWin::Window::Initialize
    void FUN_e0bcb0(const float* a, const float* b, float* c);        // 0xe0bcb0
    void ComputeIconPositionFromMinimapCoords(const float* c, IWin* w, bool f);   // 0xe0bf40
    void FUN_e0d100(IWin* w, float f, const float* p, const float* q);            // 0xe0d100
};

// ===========================================================================
//  0x00e0df70  place a feedback icon window for an event id
// ===========================================================================
struct ImgInfo { virtual void v0(); virtual void GetInfo(int* w, int* h, unsigned char** d); };
struct IconNode { char pad[0x18]; float vec[3]; };

// @ 0x00e0df70
bool MinimapWin::FindIcon(unsigned id, const float* dir, bool flag)
{
    IconNode* it;
    tree.Find((void**)&it, &id);
    if ((char*)it != tree.sentinel) {
        IWin* sub = (IWin*)((char*)this + 4);   // IWindow subobject (no null test)
        IWin* win = sub->GetChild(id, 1);
        float x = dir[0];
        float y = dir[1];
        float z = dir[2];
        float inv = 1.0f / (float)sqrt((double)(x * x + y * y + z * z + g_13ec4b8));
        Vector3 n;
        n.x = x * inv;
        n.y = y * inv;
        n.z = z * inv;
        *(Vector3*)it->vec = n;
        float f = 0.0f;
        FUN_e0bcb0(it->vec, &n.x, flag ? &f : 0);
        ComputeIconPositionFromMinimapCoords(&n.x, win, flag);
        if (flag)
            FUN_e0d100(win, f, &n.x, &n.x);
        sub->f36();
        IWin* parent = win->GetParent();
        IWin* next = parent->GetChild(id + 1, 0);
        if (next)
            AnchorWindowToWindow(win, next, 0x300, 0);
        return true;
    }
    return false;
}

// ===========================================================================
//  0x00e0e0e0  position of an object's inverse transform
// ===========================================================================
// @ 0x00e0e0e0
void __cdecl GetInverseOffset(float* out, IXfObj* o)
{
    XForm xf;
    xf.flags = 0;
    xf.rev = 0;
    xf.scale = g_1485720;
    xf.m.Assign(g_16a2070);
    xf.SetPos(*o->GetPos());
    char tmp[0x24];
    const Matrix3* m = (const Matrix3*)Matrix3FromQuaternion(tmp, o->GetRot());
    xf.SetBasis(*m);
    xf.Invert();
    out[0] = xf.pos.x;
    out[1] = xf.pos.y;
    out[2] = xf.pos.z;
}

// ===========================================================================
//  0x00e0e840  per-row transparent-edge widths of the minimap mask
// ===========================================================================
// @ 0x00e0e840
void MinimapWin::build_edge_offsets()
{
    int n = squareRaster ? 0x80 : 0x100;
    memset(edge, 0, 0x81);
    unsigned key[3];
    key[0] = 0x361f52ed;
    key[1] = 0x03e421ed;
    key[2] = 0;
    IRef0* ptr = 0;
    ResMgr* mgr = EA_GetManager();
    {
        IRef0* t = ptr;
        if (t) { ptr = 0; t->Release(); }
    }
    if (mgr->Get(key, &ptr, 0, 0, 0, 0)) {
        int w, h;
        unsigned char* data;
        // ptr's secondary interface (+0x18) reports width, height and the pixel data
        ImgInfo* ii = (ImgInfo*)((char*)ptr + 0x18);
        ii->GetInfo(&w, &h, &data);
        int stride = w * 4;
        if (w * 2 > n)
            w = (unsigned)n >> 1;
        if (h * 2 > 0x80)
            h = 0x40;
        if (h > 0) {
            unsigned char* d0 = edge;
            unsigned char* d1 = &edge[0x7f];
            unsigned char* row = data;
            int rows = h;
            do {
                int j = 0;
                if (w > 0) {
                    const unsigned char* px = row + 3;
                    do {
                        if (*px != 0)
                            break;
                        (*d0)++;
                        (*d1)++;
                        j++;
                        px += 4;
                    } while (j < w);
                }
                row += stride;
                d0++;
                d1--;
                rows--;
            } while (rows != 0);
        }
        edge[0x80] = edge[0x7f];
    }
    {
        IRef0* t = ptr;
        if (t) { ptr = 0; t->Release(); }
        if (ptr) ptr->Release();
    }
}

// ===========================================================================
//  0x00e0eab0  window init: cursor, resources, layout, message handlers, camera child
// ===========================================================================
// @ 0x00e0eab0
bool MinimapWin::Init()
{
    CursorAttachment* ca = new(g_13f6b3c, 0, 0, 0, 0) CursorAttachment();
    {
        IRef0* old = mCursor;
        if ((IRef0*)ca != old) {
            if (ca) ((IRef0*)ca)->AddRef();
            mCursor = (IRef0*)ca;
            if (old) old->Release();
        }
    }
    IRef0* ptr = 0;
    unsigned key[3];
    key[0] = 0x26976266;
    key[1] = 0x03e421ed;
    key[2] = 0;
    ResMgr* mgr = EA_GetManager();
    if (ptr) { IRef0* t = ptr; ptr = 0; t->Release(); }
    mgr->Get(key, &ptr, 0, 0, 0, 0);
    {
        // mGrid is an AutoRefCount<> slot taking the loaded object
        IRef0* nw = ptr;
        GridData* old = mGrid;
        if (nw != (IRef0*)old) {
            if (nw) nw->AddRef();
            mGrid = (GridData*)nw;
            if (old) old->Release();
        }
    }
    if (swMode == 1) {
        unsigned long long t = __rdtsc();
        swLo = (unsigned)t;
        swHi = (unsigned)(t >> 32);
    } else {
        PerfCount t;
        QueryPerformanceCounter(&t);
        swLo = t.lo;
        swHi = t.hi;
    }
    m268 = 0;
    m26c = 0;
    bool ok = Initialize();
    IWin* sub = (IWin*)((char*)this + 4);   // IWindow subobject (no null test)
    {
        float r[4];
        r[0] = 0.0f;
        r[1] = 0.0f;
        r[2] = (float)width;
        r[3] = (float)height;
        sub->SetArea(r);
    }
    build_edge_offsets();
    m35c |= 4;
    sub->f43(0);
    sub->f23(-1);
    m360 = 0xf000;
    {
        Layout* lay = new(g_147fb90, 0, 0, 0, 0) Layout();
        Layout* old = mLayout;
        if (lay != old) {
            if (lay) lay->AddRef();
            mLayout = lay;
            if (old) old->Release();
        }
    }
    if (mLayout->Init(g_147fb74, 0x40464100, 1, 0x5b598fa))
        mLayout->SetVisibility(0);
    {
        IRef0* nw = GetImageFromLayout(mLayout, 0x5e51b82);
        IRef0* old = mIconImage;
        if (nw != old) {
            if (nw) CallSlot(nw, 0);
            mIconImage = nw;
            if (old) CallSlot(old, 1);
        }
    }
    {
        IRef0* nw = GetImageFromLayout(mLayout, 0x67b4af8);
        IRef0* old = mRoadIcon;
        if (nw != old) {
            if (nw) CallSlot(nw, 0);
            mRoadIcon = nw;
            if (old) CallSlot(old, 1);
        }
    }
    {
        IRef0* nw = GetImageFromLayout(mLayout, 0x67b4ad8);
        IRef0* old = mMapImage;
        if (nw != old) {
            if (nw) CallSlot(nw, 0);
            mMapImage = nw;
            if (old) CallSlot(old, 1);
        }
    }
    {
        MsgServer* srv = SP_MessageServer();
        void* h = handler;
        msgServer = srv;
        handlerPtr = h;
        msgTable = g_147f678;
        msgCount = 0x12;
        m234 = 0;
        if (srv && h) {
            for (unsigned i = 0; i < 0x48; i += 4)
                srv->Register(handler, *(const unsigned*)((const char*)g_147f678 + i));
        }
    }
    SetWindowSPMaterial(sub, g_147fb4c, 0);
    sub->f31(0x400, 1);
    MinimapCamera* cam = new(4, g_147fb38, FUN_009512c0()) MinimapCamera();
    cam->SetOwner(this);
    IWin* csub = (IWin*)((char*)cam + 4);
    {
        float r[4];
        r[0] = 0.0f;
        r[1] = 0.0f;
        r[2] = (float)width;
        r[3] = (float)height;
        csub->SetArea(r);
    }
    csub->f20(0x6c53765);
    sub->AddChild(csub);
    {
        IRef0* old = mCamera;
        IRef0* nw = (IRef0*)cam;
        if (nw != old) {
            nw->AddRef();
            mCamera = nw;
            if (old) old->Release();
        }
    }
    ((IRef0*)cam)->Release();
    if (ptr) ptr->Release();
    return ok;
}

// ===========================================================================
//  0x00e0e1a0  per-frame minimap texture / palette refresh
// ===========================================================================
static inline int FtoI(float f) { return (int)f; }

// @ 0x00e0e1a0
void MinimapWin::Update()
{
    FUN_00b3d460();
    if (GetUniverseContext() != 0)
        return;
    if (mGrid == 0)
        return;
    int n = squareRaster ? 0x80 : 0x100;
    if (mTexture.p == 0) {
        TexObj* tex = GetTexFactory()->Create(n, 0x80, 1, 0x18, 0x15, 0);
        Image* img = new("UI/MiniMapCivTexture", 0, 0, 0, 0) Image(tex);
        mImage = img;
        FUN_00957c20(img, 1);
        if (!(tex->flags & 1))
            GetTexFactory()->Register(tex);
        IWin* sub = (IWin*)((char*)this + 4);   // IWindow subobject (no null test)
        Obj19* o = sub->f19();
        Obj3Ret* r3 = 0;
        if (o)
            r3 = (Obj3Ret*)o->f3(0x5234b49);
        r3->Fn82eb80(1, mImage->GetAllocator());
        LockInfo info;
        Tex* t = tex->tex;
        if (t->Lock(2, 0, &info)) {
            memset(info.data, 0, n << 9);
            t->Unlock(&info);
        }
        TexImage* im2 = new("UI/cUIMinimapWin", 0, 0, 0, 0) TexImage(mImage, n, 0x80, 0.0f, 0.0f, 1.0f, 1.0f, 8);
        mTexture.Assign(im2);
    }
    Image* res = mImage;
    int sp10 = 0;
    if (res) {
        sp10 = res->f4;
        if (sp10 == 0) {
            ResObj* r = res->Find(g_147d84e);
            if (r) {
                if (r->GetAllocator()->flags & 1)
                    sp10 = r->GetAllocator()->Fn46f260();
            }
        }
    }
    if (mTexture.p == 0)
        return;
    if (sp10 == 0)
        return;
    if (PlanetModel() == 0)
        return;
    if (PlanetModel()->f24 == 0)
        return;
    GridSub* gs = DebugDrawGrid()->f3();
    unsigned flags = m35c;
    if (flags & 4) {
        if (gs != 0) {
            int mode = GetCurrentGameMode();
            if (mode == 0x1654c01 || GetCurrentGameMode() == 0x1654c02 || GetCurrentGameMode() == 0x1654c10) {
                m358 = 0x10;
                FUN_00e0c820((const float*)gs, g_16a40c8, 0, 0x80, m338, m350, (m35c & 3) != 0);
            } else {
                m358 = 10;
                FUN_00e0cba0((const float*)gs, g_16a40c8, 0, 0x80, m338);
            }
            b364 = 1;
            m35c = 0;
            g_16a40c0 = 0;
            g_16a40bc = 0;
            g_16a40b8 = 1;
            goto L_refresh;
        }
        if (g_16a40b8 != 0)
            goto L_refresh;
        if (g_16a40bc != 0)
            goto L_scroll;
    } else {
        if (g_16a40b8 != 0)
            goto L_refresh;
        if (g_16a40bc != 0)
            goto L_scroll;
        g_16a40c0 = flags;
        m35c = 0;
    }
    if ((g_16a40c0 & 2) == 0)
        goto L_refresh;
L_scroll:
    FUN_00e0cba0((const float*)gs, g_16a40c8 + n * g_16a40bc, g_16a40bc, 8, m338);
    g_16a40c0 &= ~2u;
    g_16a40bc = (g_16a40bc + 8) & 0x7f;
    if (g_16a40bc != 0)
        return;
    g_16a40b8 = 1;
    return;
L_refresh:
    {
        Vector3 v3;
        GetInverseOffset(&v3.x, (IXfObj*)GetActivePlanet());
        Vector3 tmp;
        const Vector3* nv = normalized_safe(&tmp, &v3);
        v3 = *nv;
        char outb[8];
        const float* rr = FUN_00e0b580(outb, 0, &v3, m338, m344, m350, 0);
        int rot = FtoI(rr[0] * g_13f1160) - 0x40;
        if ((rot != m360 && GetCurrentGameMode() != 0x1654c02) || g_16a40b8 != 0 || (g_16a40c0 & 1) != 0) {
            m360 = rot;
            float f12 = gs->f3c;
            int pv = FtoI((f12 + g_1485720) * g_141021c);
            Planet* pl = GetActivePlanet();
            int idx = FtoI((float)(mGrid->count - 1) * pl->sub->f);
            int pcol = mGrid->table[idx];
            const float* fp = DebugDrawGrid()->f51();
            int r = FtoI(fp[0] * g_13f2100);
            int g = FtoI(fp[1] * g_13f2100);
            int b = FtoI(fp[2] * g_13f2100);
            unsigned col1 = (((unsigned)r << 8) | g) << 8 | b;
            unsigned col2;
            if (GetCurrentGameMode() == 0x1654c10) {
                col2 = 0xffffff;
            } else {
                const float* fp2 = DebugDrawGrid()->f52();
                int r2 = FtoI(fp2[0] * g_13f2100);
                int g2 = FtoI(fp2[1] * g_13f2100);
                int b2 = FtoI(fp2[2] * g_13f2100);
                col2 = (((unsigned)r2 << 8) | g2) << 8 | b2;
            }
            UpdatePallete(g_16a38b8, pv, col1, col2, pcol, m358);
            LockInfo info;
            Tex* t = (Tex*)sp10;
            if (t->Lock(10, 0, &info)) {
                unsigned* dst = (unsigned*)info.data;
                const unsigned char* src = g_16a40c8;
                for (unsigned j = 0; j < 0x80; j++) {
                    int e = edge[j];
                    unsigned* p = dst;
                    if (e > 0) {
                        for (int k = 0; k < e; k++) *p++ = 0;
                    }
                    int cnt = n - e * 2;
                    for (int k = 0; k < cnt; k++) {
                        int idx2 = (k << 8) / cnt;
                        *p++ = g_16a38b8[(((idx2 - rot) * 2) & 0x100) + src[idx2]];
                    }
                    if (e > 0) {
                        for (int k = 0; k < e; k++) *p++ = 0;
                    }
                    src += n;
                    dst += n;
                }
                t->Unlock(&info);
            }
            g_16a40c0 &= ~1u;
            g_16a40b8 = 0;
            IWin* sub = (IWin*)((char*)this + 4);   // IWindow subobject (no null test)
            sub->f36();
            Refresh();
        }
    }
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct ResObj {
    void GetAllocator(); // 0x007f54d0
};
struct IconTree {
    void Find(void**, unsigned int*); // 0x00e5c780
};
}
