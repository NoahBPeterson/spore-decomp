// SP::cDefaultCameraController::ReadProperties (0x0101FB40), slice s0101fb40.
// Reads the camera tuning constants from the camera property list into file-scope statics.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

struct Property {
    char pad0[0x10];
    unsigned char flags;   // +0x10: bits 0x30 = value stored indirectly
    char pad1;
    short type;            // +0x12: 1 = bool, 0xd = float
    float* __thiscall GetFloat();   // 0x41ea70
    bool*  __thiscall GetBool();    // 0x41e920
};

struct IPropertyList {
    virtual void v0();
    virtual void Release();                                  // +0x04
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);   // +0x24
};

struct IPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetPropertyList(uint32_t a, uint32_t b, IPropertyList** out);  // +0x2c
};

struct PairIF { float key; float value; };

// eastl::vector<eastl::pair<int,float>, sp_vector_allocator> (begin/end/cap), callees at 0x479830 / 0x530c80
struct VecPairIF {
    PairIF* begin; PairIF* end; PairIF* cap;
    void __thiscall insertN(PairIF* pos, unsigned n, const PairIF& v);   // 0x479830
    void __thiscall erase(PairIF* first, PairIF* last);                  // 0x530c80
    void eraseInline(PairIF* first, PairIF* last) { end += -(last - first); }
};

namespace SP {
IPropertyManager* __cdecl PropertyManager();                                       // 0x67de30
void __cdecl GetPropertyAsFloatArray(IPropertyList*, uint32_t, float**, int*);     // 0x6a08b0
void __cdecl GetPropertyAsPairArray(IPropertyList*, uint32_t, int*, PairIF**);     // 0x6a0920
}
using namespace SP;

extern float g_016dd34c;
extern float g_016dd350;
extern float g_016dd354;
extern float g_016dd358;
extern float g_016dd35c;
extern float g_016dd360;
extern float g_016dd364;
extern float g_016dd368;
extern float* g_016dd36c;
extern int g_016dd370;
extern float g_016dd374;
extern float g_016dd378;
extern float g_016dd37c;
extern float g_016dd380;
extern float g_016dd384;
extern bool g_016dd388;
extern bool g_016dd389;
extern bool g_016dd38a;
extern bool g_016dd38b;
extern float g_016dd38c;
extern float g_016dd390;
extern float g_016dd394;
extern float g_016dd398;
extern float g_016dd39c;
extern float g_016dd3a0;
extern float g_016dd3a4;
extern float g_016dd3a8;
extern float* g_016dd3ac;
extern int g_016dd3b0;
extern float g_016dd3b4;
extern float g_016dd3b8;
extern float g_016dd3bc;
extern float g_016dd3c0;
extern float g_016dd3c4;
extern float g_016dd3c8;
extern float g_016dd3cc;
extern float g_016dd3d0;
extern float g_016dd3d4;
extern float g_016dd3d8;
extern float g_016dd3dc;
extern float g_016dd3e0;
extern float g_016dd3e4;
extern float g_016dd3e8;
extern float g_016dd3ec;
extern float g_016dd3f0;
extern float g_016dd3f4;
extern float g_016dd3f8;
extern bool g_016dd3fc;
extern bool g_016dd3fe;
extern bool g_016dd3ff;
extern float g_016dd400;
extern float g_016dd404;
extern float g_016dd408;
extern float g_016dd40c;
extern float g_016dd410;
extern float g_016dd414;
extern float g_016dd418;
extern float g_016dd41c;
extern float g_016dd420;
extern float g_016dd424;
extern float g_016dd428;
extern float g_016dd42c;
extern float g_016dd430;
extern float g_016dd434;
extern float g_016dd438;
extern float g_016dd43c;
extern bool g_016dd440;
extern bool g_016dd441;

extern VecPairIF g_016dda14, g_016dda28;

#define READ_BOOL(g, def, id) \
    { Property* prop; g = def; \
    if (mConfig && mConfig->GetProperty(id, &prop) && prop->type == 1) g = *prop->GetBool(); }
#define READ_F(g, def, id) \
    { Property* prop; g = def; \
    if (mConfig && mConfig->GetProperty(id, &prop) && prop->type == 0xd) g = *prop->GetFloat(); }
#define READ_FI(g, def, id) \
    { Property* prop; g = def; \
    if (mConfig && mConfig->GetProperty(id, &prop) && prop->type == 0xd) { \
        float* pf = (float*)prop; \
        if (prop->flags & 0x30) pf = *(float**)prop; \
        g = *pf; } }
#define READ_DEG(g, def, id) \
    { Property* prop; g = def; \
    if (mConfig && mConfig->GetProperty(id, &prop) && prop->type == 0xd) g = *prop->GetFloat(); \
    g = g * 0.017453292f; }

namespace SP {
class cDefaultCameraController {
public:
    uint32_t pad[5];
    IPropertyList* mConfig;   // +0x14
    // @ 0x0101FB40
    void ReadProperties();
};
}

// @ 0x0101FB40
void SP::cDefaultCameraController::ReadProperties()
{
    int count1, count2; PairIF* pData1; PairIF* pData2;
    if (!mConfig) {
        IPropertyManager* pm = PropertyManager();
        if (mConfig) { IPropertyList* old = mConfig; mConfig = 0; old->Release(); }
        pm->GetPropertyList(0x521d0174, 0x2ae0c7e, &mConfig);
    }
    READ_BOOL(g_016dd3fe, 0, 0x469153d);
    READ_F(g_016dd43c, 0.0f, 0x195a051);
    READ_F(g_016dd438, 0.0f, 0x195a052);
    READ_F(g_016dd434, 50.0f, 0x195a050);
    READ_F(g_016dd430, 1.0f, 0xe0e60974);
    READ_F(g_016dd42c, 0.699999988f, 0xe0e60975);
    READ_F(g_016dd428, 0.400000006f, 0xe0e60976);
    READ_F(g_016dd424, 0.25f, 0x4e53ffab);
    READ_F(g_016dd420, 0.0299999993f, 0x4e53ffaa);
    READ_F(g_016dd41c, 0.0299999993f, 0x4e53ffa9);
    READ_F(g_016dd418, 50.0f, 0x4658312);
    READ_F(g_016dd414, 2000.0f, 0x46c082b);
    READ_F(g_016dd410, 200.0f, 0x46d60ad);
    READ_DEG(g_016dd40c, 60.0f, 0x195a064);
    READ_F(g_016dd408, 1.0f, 0x48775d9);
    READ_F(g_016dd404, 1.0f, 0x48775e6);
    READ_F(g_016dd400, 1.0f, 0x48775e8);
    READ_F(g_016dd3d8, 0.0500000007f, 0x5baf74f);
    READ_F(g_016dd3d4, 0.00100000005f, 0x5baf750);
    READ_BOOL(g_016dd441, 1, 0x4a0b118);
    READ_BOOL(g_016dd440, 0, 0x4a4bb05);
    READ_BOOL(g_016dd3ff, 0, 0x4a4bb09);
    READ_BOOL(g_016dd3fc, 0, 0x4a4bb1c);
    READ_BOOL(g_016dd38b, 0, 0x4a4bb23);
    READ_BOOL(g_016dd38a, 0, 0x4a4bb27);
    READ_F(g_016dd3f8, 5.0f, 0x49a1d5e);
    READ_DEG(g_016dd3dc, 15.0f, 0x195a061);
    READ_F(g_016dd3f4, 900.0f, 0x63c0263);
    READ_F(g_016dd3f0, 1500.0f, 0x63c0261);
    READ_F(g_016dd3ec, 1000.0f, 0x6295b9e);
    READ_F(g_016dd3e8, 1500.0f, 0x37e593a);
    READ_F(g_016dd3e4, 500.0f, 0x6491aed);
    READ_F(g_016dd3e0, 800.0f, 0x6491aef);
    READ_BOOL(g_016dd389, 0, 0x6046db3);
    READ_F(g_016dd3d0, 20.0f, 0x195a021);
    READ_F(g_016dd3cc, 21.0f, 0x62fd07e);
    READ_F(g_016dd3c8, 25.0f, 0x62eb1ab);
    READ_F(g_016dd3c4, 50.0f, 0x62eb1ad);
    READ_F(g_016dd3c0, 500.0f, 0x62eb1b7);
    READ_F(g_016dd3bc, 800.0f, 0x5e3dcee);
    READ_F(g_016dd3b8, 2300.0f, 0x62ff0ce);
    READ_F(g_016dd3b4, 2400.0f, 0x195a020);
    g_016dd3b0 = 0; g_016dd3ac = 0;
    GetPropertyAsFloatArray(mConfig, 0x632c41b, &g_016dd3ac, &g_016dd3b0);
    READ_F(g_016dd3a8, 2000.0f, 0x4657fb9);
    READ_F(g_016dd3a4, 200000.0f, 0x46ab5aa);
    READ_F(g_016dd3a0, 2000.0f, 0x632a46e);
    READ_F(g_016dd39c, 200000.0f, 0x632a472);
    READ_F(g_016dd398, 2000.0f, 0x665ed99);
    READ_F(g_016dd394, 200000.0f, 0x665ed9c);
    READ_F(g_016dd390, 0.0f, 0x3277323);
    READ_F(g_016dd38c, 0.0f, 0x3277324);
    READ_BOOL(g_016dd388, 0, 0x4691389);
    READ_F(g_016dd350, g_016dd434, 0x61ca5a3);
    READ_F(g_016dd34c, g_016dd434, 0x61ca5b2);
    {
        PairIF fill; pData1 = 0;
        count1 = 0;
        GetPropertyAsPairArray(mConfig, 0x632a03b, &count1, &pData1);
        unsigned n = (unsigned)(g_016dda14.end - g_016dda14.begin);
        if ((unsigned)count1 > n) g_016dda14.insertN(g_016dda14.end, count1 - n, fill);
        else g_016dda14.erase(g_016dda14.begin + count1, g_016dda14.end);
        for (int i = 0; i < count1; ++i) {
            g_016dda14.begin[i].key = pData1[i].key;
            g_016dda14.begin[i].value = pData1[i].value * 0.017453292f;
        }
    }
    READ_FI(g_016dd384, 0.100000001f, 0x195a001);
    READ_FI(g_016dd380, 0.200000003f, 0x62ff100);
    READ_FI(g_016dd37c, 1.0f, 0x5e3e315);
    READ_FI(g_016dd378, 10.0f, 0x62eb105);
    READ_FI(g_016dd374, 1500.0f, 0x195a000);
    g_016dd370 = 0; g_016dd36c = 0;
    GetPropertyAsFloatArray(mConfig, 0x632a816, &g_016dd36c, &g_016dd370);
    READ_FI(g_016dd368, 20000.0f, 0x46bb221);
    READ_FI(g_016dd364, 2000000.0f, 0x46bb224);
    READ_FI(g_016dd360, 20000.0f, 0x632a54d);
    READ_FI(g_016dd35c, 2000000.0f, 0x632a54f);
    {
        PairIF fill; pData2 = 0;
        count2 = 0;
        GetPropertyAsPairArray(mConfig, 0x3a8dee8, &count2, &pData2);
        unsigned n = (unsigned)(g_016dda28.end - g_016dda28.begin);
        if ((unsigned)count2 > n) g_016dda28.insertN(g_016dda28.end, count2 - n, fill);
        else g_016dda28.eraseInline(g_016dda28.begin + count2, g_016dda28.end);
        for (int i = 0; i < count2; ++i) {
            g_016dda28.begin[i].key = pData2[i].key;
            g_016dda28.begin[i].value = pData2[i].value * 0.017453292f;
        }
    }
    READ_FI(g_016dd358, g_016dd434, 0x61ca5b9);
    READ_FI(g_016dd354, g_016dd434, 0x61ca5d4);
}
