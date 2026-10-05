// Slice s004db1b0: SP::cSpeciesCheat and Skinner::PaintSystem destructor/init helpers.
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#pragma pack(push, 4)

// distinct stub callee classes so each call is a separate masked relocation
struct Sub0 { void f(); };
struct Sub1 { void f(); };
struct Sub2 { void f(); };
struct Sub3 { void f(); };
struct SubDtor { void f(); };

struct IVtbl9 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(int a, int b);
};

extern int g_paintSystemVtblA[];
extern int g_paintSystemVtblB[];

struct PaintSystem {
    void Destroy();
};

// @ 0x004DB3E0  (Skinner::PaintSystem destructor body)
void PaintSystem::Destroy()
{
    *(void**)this = (void*)g_paintSystemVtblA;
    ((Sub0*)this)->f();
    int* p = (int*)((char*)this + 0xd0);
    if (*p != 0)
        ((Sub1*)p)->f();
    ((Sub2*)((char*)this + 0xb0))->f();
    ((Sub3*)((char*)this + 0x84))->f();
    ((Sub3*)((char*)this + 0x64))->f();
    ((Sub3*)((char*)this + 0x44))->f();
    ((Sub3*)((char*)this + 0x24))->f();
    ((Sub3*)((char*)this + 4))->f();
    *(void**)this = (void*)g_paintSystemVtblB;
}

// @ 0x004DB620
struct Connector {
    void* mpObj;    // +0
    int   mnB;      // +4
    int   mnC;      // +8
    int   mnD;      // +0xc
    int   mnE;      // +0x10
    void Init(void* pObj, int b, int c, uint32_t n);
};

void Connector::Init(void* pObj, int b, int c, uint32_t n)
{
    mpObj = pObj;
    mnB = b;
    mnC = c;
    mnD = n;
    mnE = 0;
    if (pObj != 0 && b != 0 && mnC != 0) {
        for (uint32_t i = 0; i < n; i = i + 1) {
            ((IVtbl9*)pObj)->v09(b, *(int*)(c + i * 4));
        }
    }
}

// @ 0x004DB6B0  SP::cSpeciesCheat::Description
struct SpeciesCheat {
    const char* Description(int param);
};

const char* SpeciesCheat::Description(int param)
{
    if (param == 0)
        return "Used to test species queries to the OTDB";
    else
        return "[-<param> <min> <max> [-<param> <min> <max>]...] | [-dump <param>] | [-dumpFull <param>]\n"
           "-cost <min> <max>\n-baseGear <min> <max>\n-height <min> <max>\n-carnivore <min> <max>\n"
           "-herbivore <min> <max>\n-numGraspers <min> <max>\n-totalAttack <min> <max>\n"
           "-attack <min> <max>\n-cuteness <min> <max>\n-totalSocial <min> <max>\n-social <min> <max>\n"
           "-numFeet <min> <max>\n-meanLookingScore <min> <max>\n-biteCapRange <min> <max>\n"
           "-strikeCapRange <min> <max>\n-chargeCapRange <min> <max>\n-spitCapRange <min> <max>\n"
           "-singCapRange <min> <max>\n-danceCapRange <min> <max>\n-charmCapRange <min> <max>\n"
           "-poseCapRange <min> <max>\n-glideCapRange <min> <max>\n-stealthCapRange <min> <max>\n"
           "-sprintCapRange <min> <max>\n-senseCapRange <min> <max>\n-healthCapRange <min> <max>\n";
}

// ---------------------------------------------------------------------------
// Larger neighbours -> partial.txt
// ---------------------------------------------------------------------------
// @ 0x004DB1B0
void SpeciesCheat_Op1(void* self) { (void)self; }
// @ 0x004DB2C0
void SpeciesCheat_Op2(void* self) { (void)self; }
// @ 0x004DB470
void SpeciesCheat_Op3(void* self) { (void)self; }
