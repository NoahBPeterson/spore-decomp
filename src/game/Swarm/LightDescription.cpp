// src/game/Swarm/LightDescription.cpp -- migrated from slice(s) s00a987c0, s00a978d0 by tools/migrate/rewrite.py
// Object file: Swarm/LightDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern void  operator_delete(void* p);                                    // (0xf47380)
extern void* EA_IO_WriteUint32(void* stream, const void* in, int, int);   // (0x93aa70)
extern int   EA_IO_StreamWrite(void* stream, const void* src, int count); // (0x93a9a0)
extern int   EA_IO_WriteUint16(void* stream, const void* in, int, int);   // (0x93a9d0)
extern void* EA_ArgScript_MainArguments();                                // (0x838320)
extern int   EA_ArgScript_HasFlag();                                       // (0x8380b0)
extern void* EA_ArgScript_OptionArguments();                               // (0x838130)
extern void AppPropsFields_ctor();                                         // (0x83cdd0)
extern void  FUN_007ec580(void* stream, void* v);                         // (0x7ec580)
extern void  FUN_007d0250(void* stream, void* v);                         // (0x7d0250)
extern float   g_realOne;             // (0x1485720)
extern char vtable_IEvent[];          // (0x13ef094) SP::Audio::IEventModifier
extern char vtable_Light0[];          // (0x145884c)
extern char vtable_Light1[];          // (0x1458848)

// ---- items of slice s00a978d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef unsigned char  u8;
typedef unsigned int   u32;
extern void  operator_delete(void* p);                                    // (0xf47380)
extern void* EA_IO_WriteUint32(void* stream, const void* in, int, int);   // (0x93aa70)
extern int   EA_IO_StreamWrite(void* stream, const void* src, int count); // (0x93a9a0)
extern int   EA_IO_WriteUint16(void* stream, const void* in, int, int);   // (0x93a9d0)
extern void* EA_ArgScript_MainArguments();                                // (0x838320)
extern int   EA_ArgScript_HasFlag();                                       // (0x8380b0)
extern void* EA_ArgScript_OptionArguments();                               // (0x838130)
extern void AppPropsFields_ctor();                                         // (0x83cdd0)
extern void  FUN_007ec580(void* stream, void* v);                         // (0x7ec580)
extern void  FUN_007d0250(void* stream, void* v);                         // (0x7d0250)
extern float   g_realOne;             // (0x1485720)
extern u16     gEmptyString16[];      // (0x1667bac) eastl empty 16-bit string sentinel
extern u16     gEmptyString16Cap[];   // (0x1667bad)
extern char vtable_IEvent[];          // (0x13ef094) SP::Audio::IEventModifier
extern char vtable_Light0[];          // (0x145884c)
extern char vtable_Light1[];          // (0x1458848)
struct Str16                          // eastl::string16-ish (0xc bytes)
{
	const void* mpBegin;               // +0x00
	const void* mpEnd;                 // +0x04
	u32         mCapacity;             // +0x08
};
static inline void DestroySpVector(void* mpBegin)
{
	if (mpBegin && ((int*)mpBegin)[-1])
		operator_delete(mpBegin);
}
struct EffectObjB
{
	void* mpVtbl;                      // +0x00
	char  pad04[0x14];                 // +0x04
	void* mpVec18;                     // +0x18
	char  pad1c[0x10];                 // +0x1c
	void* mpVec2c;                     // +0x2c
	char  pad30[0x10];                 // +0x30
	void* mpVec40;                     // +0x40

	void Destroy();
};
struct EffectObjB2
{
	void* mpVtbl;                      // +0x00
	char  pad04[4];                    // +0x04
	u32   mn08;                        // +0x08
	u8    mb0c;                        // +0x0c
	char  pad0d[3];                    // +0x0d
	float mf10;                        // +0x10
	u16   mw14;                        // +0x14
	char  pad16[2];                    // +0x16
	void* mVec18[3];                   // +0x18
	char  pad24[8];                    // +0x24
	void* mVec2c[3];                   // +0x2c
	char  pad38[8];                    // +0x38
	void* mVec40[3];                   // +0x40
	char  pad4c[8];                    // +0x4c
	float mf54;                        // +0x54
};
namespace ArgScript {
struct LightEffect
{
	void*  mpVtbl;                     // +0x00
	char   pad04[0x30];                // +0x04
	u32    mn34;                       // +0x34
	void*  mpVtbl2;                    // +0x38
	u32    mn3c;                       // +0x3c
	u32    mn40;                       // +0x40
	u8     mb44;                       // +0x44
	char   pad45[3];                   // +0x45
	float  mf48;                       // +0x48
	u16    mw4c;                       // +0x4c
	char   pad4e[2];                   // +0x4e
	u32    mV1a;                       // +0x50
	u32    mV1b;                       // +0x54
	u32    mV1c;                       // +0x58
	char   pad5c[8];                   // +0x5c
	u32    mV2a;                       // +0x64
	u32    mV2b;                       // +0x68
	u32    mV2c;                       // +0x6c
	char   pad70[8];                   // +0x70
	u32    mV3a;                       // +0x78
	u32    mV3b;                       // +0x7c
	u32    mV3c;                       // +0x80
	char   pad84[8];                   // +0x84
	float  mf8c;                       // +0x8c
	Str16  mStr90;                     // +0x90

	LightEffect();
};  // namespace ArgScript
}
struct LifeSub                         // *(cmd+0x0c) + 4
{
	char  pad00[8];                    // +0x00
	u32   mFlags;                      // +0x08
	char  pad0c[4];                    // +0x0c
	float mf10;                        // +0x10
	u16   mw14;                        // +0x14
};
struct LifeData
{
	char   pad00[4];                   // +0x00
	LifeSub sub;                       // +0x04  (the object reached through cmd+0x0c, +4)
};
struct LifeHost                        // the object at command+0x04 (+0x98 returns float, +0xa0 returns u16)
{
	void* mpVtbl;                      // +0x00
};
struct cCameraLifeCommand
{
	void*      mpVtbl;                 // +0x00
	LifeHost*  mpHost;                 // +0x04
	char       pad08[4];               // +0x08
	LifeData*  mpData;                 // +0x0c

	void Execute(void* args);
};
// ---- items of slice s00a978d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u16     gEmptyString16[];      // (0x1667bac) eastl empty 16-bit string sentinel
extern u16     gEmptyString16Cap[];   // (0x1667bad)

// ---- items of slice s00a987c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_156522c;                      // 0x0156522c  light parser data slot
extern void* g_1565230;                      // 0x01565230  LightType slot
extern void* g_1565234;                      // 0x01565234  LightLife slot
extern void* g_1565238;                      // 0x01565238  LightColor slot
extern void* g_156523c;                      // 0x0156523c  LightStrength slot
extern void* g_1565240;                      // 0x01565240  LightSize slot
extern void* g_1565244;                      // 0x01565244  LightSpotWidth slot
extern const char g_str_LightType[];         // 0x01458974
extern const char g_str_LightLife[];         // 0x01458960
extern const char g_str_LightColor[];        // 0x01458948
extern const char g_str_LightStrength[];     // 0x01458930
extern const char g_str_LightSize[];         // 0x0145891c
extern const char g_str_LightSpotWidth[];    // 0x01458900
extern const char g_str_LightEffect[];       // 0x014589a0
extern const char g_str_GroupLight[];        // 0x01458988
extern const char g_str_ambient[];           // 0x01565248 (table->name)
extern const char g_str_penumbra[];          // 0x014589b8
extern const char g_str_Swarm[];             // 0x013f1fdc
extern "C" void* EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0xf473a0
extern void* g_vtbl_LightType;      // 0x01458870
extern void* g_vtbl_LightLife;      // 0x01458888
extern void* g_vtbl_LightColor;     // 0x014588a0
extern void* g_vtbl_LightStrength;  // 0x014588b8
extern void* g_vtbl_LightSize;      // 0x014588d0
extern void* g_vtbl_LightSpotWidth; // 0x014588e8
extern void* g_vtbl_LightEffectSub;  // 0x01458848
extern void* g_vtbl_GroupLight;   // 0x01458830
extern void __stdcall Vec0C_erase(void* first, void* last);   // 0x9e0480 (ret 8)
extern void __stdcall VecClear3(void* vec, void* p1, int zero);   // 0x11e0744
void __stdcall ArgScript_Text_SetUserData(void* self, void* p);      // 0xfd9450
void __stdcall ArgScript_cCommandBase_ctor(void* p);                 // 0x83c800
void __stdcall ArgScript_cCommandBase_OnRegister(void* self, void* p1, void* p2); // 0x83c780
void* __stdcall ArgScript_OptionArguments(const void* args, const char* name, int a); // 0x838330
unsigned char __stdcall ArgScript_ParseEnum(const char* s, const void* tbl); // 0x840bb0
inline void* EAAlloc(unsigned int n, const char* name)
{
    return EAAllocate(n, name, 0, 0, 0, 0);
}
struct FVec5 {                       // 5-word eastl::vector<float>
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    const char* mpName;
    int   mpExtra;
    void assign(const FVec5& src);                       // 0x50d4e0
    void reserve(int n, const char* name);               // 0x4aa350
    float* insert_end(float* first, unsigned int n);     // 0x11e0744
};
struct Vec0C5 {                      // 5-word eastl::vector<3-float element>
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* mpName;
    int   mpExtra;
    void assign(const Vec0C5& src);                      // 0x6f5cd0
    void copy_construct(const Vec0C5& src);              // 0x6f50f0
};
struct LightEffectSub {
    void* v00;                       // +0x00
    int   n04;                       // +0x04
    int   n08;                       // +0x08
    unsigned char n0c;               // +0x0c
    float f10;                       // +0x10
    short s14;                       // +0x14
    void* v18a;                      // +0x18 (3-float element storage)
    void* v18b;
    void* v18c;
    float f24;                       // +0x24
    float f28;                       // +0x28
    FVec5 v2c;                       // +0x2c
    FVec5 v40;                       // +0x40
    float f54;                       // +0x54

    LightEffectSub() {}
    LightEffectSub& operator=(const LightEffectSub& src);
    LightEffectSub& copy_construct(const LightEffectSub& src);
    void Read(void* stream, int n);
    void Install(char flag);
};
struct LightEffect_s00a9_87c0 {
    void* v00;
    int   pad[12];
    void* p34;                       // +0x34
    LightEffectSub sub38;            // +0x38  (0x58 bytes)
    void* s90;                       // +0x90  string begin
    void* s94;                       // +0x94
    int   s98;
    void Install(char flag);
};
struct ArgCommand {
    void* v00;                       // +0x00
    void* p04;                       // +0x04  parser / manager
    void* v08;                       // +0x08
    void* p0c;                       // +0x0c  light sub-data
    int   pad1[9];                   // +0x10 .. +0x33
    void* p34;                       // +0x34
    LightEffectSub sub38;            // +0x38
    void* s90;                       // +0x90
    void* s94;                       // +0x94
    int   s98;
    void ExecuteType(void* args);
    void ExecuteLife(void* args);
    void ExecuteColor(void* args);
    void ExecuteSize(void* args);
    void ExecuteSpotWidth(void* args);
    void ExecuteEffect(void* args);
    void OnRegister(void* parser, void* state);
};
struct FloatVec {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    const char* mpName;
    int mpExtra;
    void DoInsertValue(float* pos, const float& v);   // 0x00455660 (ret 8)
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) { float* p = mpEnd; mpEnd = p + 1; if (p) *p = v; }
        else DoInsertValue(mpEnd, v);
    }
};
void AddToScript(void* state, void* parser);
static void* MakeCommand(unsigned int sz, const char* name, void* vtbl);
struct IVtParser {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void AddCommand(void* slot, void* cmd);   // +0x18
};
static void* MakeCommand(unsigned int sz, const char* name, void* vtbl)
{
    unsigned char* p = (unsigned char*)EAAlloc(sz, name);
    if (!p) return 0;
    ArgScript_cCommandBase_ctor(p);
    *(void**)p = vtbl;
    return p;
}
struct EaString {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* mpAlloc;
    void assign(const char* first, const char* last);   // 0x454cb0
};
struct cArguments {
    const char** MainArguments(int n);                      // 0x838320
    const char** MainArguments(int* count, int a, int b);   // 0x838020
};
struct cEffectsParser {
    int GetInheritedDescription(void** argv, int n, int t);  // 0xa6f090
};
struct IVtScript {    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void AddCommand(void* slot, void* cmd, void* state);   // +0x14
    virtual void AddCommand18(void* slot, void* cmd);              // +0x18
};
struct CtorHost { void ctor(); };
struct IVtParser2 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
    virtual void   NotifyChanged(void* self);               // +0x8c
virtual void v90();
virtual void v94();
    virtual float  ParseScalar(const char* s);              // +0x98
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
    virtual void vac();
    virtual float* ParseVec3(float* out, const char* s);    // +0xb0
};
struct Elem0C { float x, y, z; };
struct Elem0CVec {
    Elem0C* mpBegin;
    Elem0C* mpEnd;
    Elem0C* mpCapacity;
    const char* mpName;
    int mpExtra;
};
extern void __stdcall ScaleCurve(Elem0C* pos, const Elem0C* v);   // 0x7ed1b0 (ret 8)
struct DescInstaller {
    void Install(void* str, int t, void* desc);   // 0xa6f9c0 (thiscall: ecx=installer)
};
// ---- items of slice s00a987c0 end

// @ 0x00a98520
void EffectObjB::Destroy()
{
	DestroySpVector(mpVec40);
	DestroySpVector(mpVec2c);
	DestroySpVector(mpVec18);
	mpVtbl = (void*)vtable_IEvent;
}

// @ 0x00a985c0
void FUN_00a985c0(void* stream, EffectObjB2* o)
{
	{
		u32 v = o->mn08;
		EA_IO_WriteUint32(stream, &v, 1, 0);
	}
	{
		u8 b = o->mb0c;
		EA_IO_StreamWrite(stream, &b, 1);
	}
	{
		float f = o->mf10;
		EA_IO_WriteUint32(stream, &f, 1, 0);
	}
	{
		u16 w = o->mw14;
		EA_IO_WriteUint16(stream, &w, 1, 0);
	}

	FUN_007ec580(stream, o->mVec18);
	FUN_007d0250(stream, o->mVec2c);
	FUN_007d0250(stream, o->mVec40);

	{
		float f = o->mf54;
		EA_IO_WriteUint32(stream, &f, 1, 0);
	}
}

// @ 0x00a98670
namespace ArgScript {
LightEffect::LightEffect()
{
	((void(__thiscall*)(void*))AppPropsFields_ctor)(this);
	mpVtbl = (void*)vtable_Light0;
	mn34 = 0xcd338355;
	mpVtbl2 = (void*)vtable_Light1;
	mn3c = 0;
	mn40 = 0;
	mf48 = g_realOne;
	mb44 = 1;
	mw4c = 0;
	mV1a = 0;
	mV1b = 0;
	mV1c = 0;
	mV2a = 0;
	mV2b = 0;
	mV2c = 0;
	mV3a = 0;
	mV3b = 0;
	mV3c = 0;
	mf8c = 0.0f;
	mStr90.mpBegin = gEmptyString16;
	mStr90.mpEnd = gEmptyString16;
	mStr90.mCapacity = (u32)gEmptyString16Cap;
}
}  // namespace ArgScript

// @ 0x00a98700
void cCameraLifeCommand::Execute(void* args)
{
	LifeSub* d = &mpData->sub;
	int* v = (int*)((void*(__thiscall*)(void*, int))EA_ArgScript_MainArguments)(args, 1);

	float f = (*(float(__thiscall**)(void*, int))(*(char**)mpHost + 0x98))(mpHost, *v);
	d->mf10 = f;

	if (((int(__thiscall*)(void*, const char*))EA_ArgScript_HasFlag)(args, "single") != 0) {
		d->mw14 = 1;
		return;
	}

	int count;
	int* p = (int*)((void*(__thiscall*)(void*, const char*, int*, int, int))EA_ArgScript_OptionArguments)(args, "loop", &count, 0, 1);
	if (p != 0) {
		if (count <= 0) {
			d->mw14 = 0;
			return;
		}
	} else {
		p = (int*)((void*(__thiscall*)(void*, const char*, int*, int, int))EA_ArgScript_OptionArguments)(args, "sustain", &count, 0, 1);
		if (p == 0)
			return;
		d->mFlags |= 8;
		if (count <= 0) {
			d->mw14 = 1;
			return;
		}
	}

	d->mw14 = (*(u16(__thiscall**)(void*, int))(*(char**)mpHost + 0xa0))(mpHost, *p);
}

// @ 0x00a987c0
void ArgCommand::OnRegister(void* parser, void* state)
{
    void* sub = (state != 0) ? (void*)((int)state - 0xc) : 0;
    *(void**)((char*)this + 0x30) = sub;
    ArgScript_cCommandBase_OnRegister(this, parser, state);
    ArgScript_Text_SetUserData(this, (char*)this + 0x34);

    IVtParser* vt = (IVtParser*)this;
    vt->AddCommand(g_1565230, MakeCommand(0x10, g_str_LightType,     g_vtbl_LightType));
    vt->AddCommand(g_1565234, MakeCommand(0x10, g_str_LightLife,     g_vtbl_LightLife));
    vt->AddCommand(g_1565238, MakeCommand(0x10, g_str_LightColor,    g_vtbl_LightColor));
    vt->AddCommand(g_156523c, MakeCommand(0x10, g_str_LightStrength, g_vtbl_LightStrength));
    vt->AddCommand(g_1565240, MakeCommand(0x10, g_str_LightSize,     g_vtbl_LightSize));
    vt->AddCommand(g_1565244, MakeCommand(0x10, g_str_LightSpotWidth,g_vtbl_LightSpotWidth));
}

// @ 0x00a98990
void AddToScript(void* state, void* parser)
{
    unsigned char* le = (unsigned char*)EAAllocate(0xa0, g_str_LightEffect, 0, 0, 0, 0);
    if (le) ((CtorHost*)le)->ctor();          // ArgScript::LightEffect::LightEffect (0xa98670)
    else    le = 0;
    ((IVtScript*)parser)->AddCommand(g_156522c, le, state);

    unsigned char* cmd = (unsigned char*)EAAllocate(0x10, g_str_GroupLight, 0, 0, 0, 0);
    if (cmd) {
        ((CtorHost*)cmd)->ctor();             // cCommandBase::cCommandBase (0x83c800)
        *(void**)cmd = g_vtbl_GroupLight;
    } else {
        cmd = 0;
    }
    ((IVtScript*)parser)->AddCommand18(g_156522c, cmd);
}

// @ 0x00a98a80
void ArgCommand::ExecuteType(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    const char** a = args->MainArguments(1);
    unsigned char e = ArgScript_ParseEnum(a[0], g_str_ambient);
    unsigned char* sub = (unsigned char*)p0c;
    sub[0x10] = e;
    if (sub[0x10] == 4) {
        FloatVec* v = (FloatVec*)(sub + 0x44);
        if (v->mpBegin == v->mpCapacity) {
            v->push_back(1.0f);
        }
    }
}

// @ 0x00a98b00
void ArgCommand::ExecuteSize(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int n = 0;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    unsigned char* sub = (unsigned char*)p0c;

    Elem0CVec* v = (Elem0CVec*)(sub + 0x1c);
    Vec0C_erase(v->mpBegin, v->mpEnd);

    for (int i = 0; i < n; ++i) {
        float tmp[3];
        ((IVtParser2*)p04)->ParseVec3(tmp, a[i]);
        Elem0C* p = v->mpEnd;
        if (p < v->mpCapacity) {
            v->mpEnd = p + 1;
            if (p) { p->x = tmp[0]; p->y = tmp[1]; p->z = tmp[2]; }
        } else {
            ScaleCurve(p, (const Elem0C*)tmp);
        }
    }

    unsigned int* flags = (unsigned int*)((unsigned char*)p0c + 0xc);
    if (n > 0) *flags |= 1;
    else       *flags &= ~1u;
}

// @ 0x00a98bc0
void ArgCommand::ExecuteLife(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int n = 0;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    unsigned char* sub = (unsigned char*)p0c;

    FloatVec* v = (FloatVec*)(sub + 0x30);
    float* begin = v->mpBegin;
    float* end   = v->mpEnd;
    VecClear3(begin, end, 0);
    v->mpEnd = v->mpEnd - (end - begin);

    for (int i = 0; i < n; ++i) {
        float f = ((IVtParser2*)p04)->ParseScalar(a[i]);
        v->push_back(f);
    }

    unsigned int* flags = (unsigned int*)((unsigned char*)p0c + 0xc);
    if (n > 0) *flags |= 2;
    else       *flags &= ~2u;
}

// @ 0x00a98c90
void ArgCommand::ExecuteColor(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int n = 0;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    unsigned char* sub = (unsigned char*)p0c;

    FloatVec* v = (FloatVec*)(sub + 0x44);
    float* begin = v->mpBegin;
    float* end   = v->mpEnd;
    VecClear3(begin, end, 0);
    v->mpEnd = v->mpEnd - (end - begin);

    for (int i = 0; i < n; ++i) {
        float f = ((IVtParser2*)p04)->ParseScalar(a[i]);
        v->push_back(f);
    }

    unsigned int* flags = (unsigned int*)((unsigned char*)p0c + 0xc);
    if (n > 0) *flags |= 4;
    else       *flags &= ~4u;
}

// @ 0x00a98d60
void ArgCommand::ExecuteSpotWidth(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int n = 0;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    unsigned char* sub = (unsigned char*)p0c;

    FloatVec* v = (FloatVec*)(sub + 0x44);
    float* begin = v->mpBegin;
    float* end   = v->mpEnd;
    VecClear3(begin, end, 0);
    v->mpEnd = v->mpEnd - (end - begin);

    for (int i = 0; i < n; ++i) {
        float f = ((IVtParser2*)p04)->ParseScalar(a[i]);
        v->push_back(f);
    }

    const char** opt = (const char**)ArgScript_OptionArguments(args, g_str_penumbra, 1);
    if (opt) {
        float f = ((IVtParser2*)p04)->ParseScalar(opt[0]);
        *(float*)((unsigned char*)p0c + 0x58) = f;
    }
}

// @ 0x00a98e40
LightEffectSub& LightEffectSub::operator=(const LightEffectSub& src)
{
    n08 = src.n08;
    n0c = src.n0c;
    f10 = src.f10;
    s14 = src.s14;
    ((Vec0C5*)&v18a)->assign(*(const Vec0C5*)&src.v18a);
    v2c.assign(src.v2c);
    v40.assign(src.v40);
    f54 = src.f54;
    return *this;
}

// @ 0x00a98ea0
LightEffectSub& LightEffectSub::copy_construct(const LightEffectSub& src)
{
    n04 = 0;
    v00 = (void*)&g_vtbl_LightEffectSub;             // 0x01458848 placeholder
    n08 = src.n08;
    n0c = src.n0c;
    f10 = src.f10;
    s14 = src.s14;
    ((Vec0C5*)&v18a)->copy_construct(*(const Vec0C5*)&src.v18a);

    v2c.reserve((int)(src.v2c.mpEnd - src.v2c.mpBegin), src.v2c.mpName);
    {
        float* r = v2c.insert_end(src.v2c.mpBegin, (unsigned int)(src.v2c.mpEnd - src.v2c.mpBegin));
        v2c.mpEnd = r;
    }
    v40.reserve((int)(src.v40.mpEnd - src.v40.mpBegin), src.v40.mpName);
    {
        float* r = v40.insert_end(src.v40.mpBegin, (unsigned int)(src.v40.mpEnd - src.v40.mpBegin));
        v40.mpEnd = r;
    }
    f54 = src.f54;
    return *this;
}

// @ 0x00a98f60
void ArgCommand::ExecuteEffect(void* argsRaw)
{
    cArguments* args = (cArguments*)argsRaw;
    int argc;
    const char** a = args->MainArguments(&argc, 1, 3);

    const char* p = a[0];
    const char* e = p;
    const char* q = p + 1;
    while (*e++) { }
    const char* end = p + (e - q);
    ((EaString*)((char*)this + 0x90))->assign(p, end);

    if (argc > 1) {
        int desc = ((cEffectsParser*)*(void**)((char*)this + 0x30))->GetInheritedDescription((void**)a, argc, 10);
        if (desc) sub38.operator=(*(const LightEffectSub*)desc);
    }

    ((IVtParser2*)p04)->NotifyChanged(this);
}

// @ 0x00a98fd0
void LightEffect_s00a9_87c0::Install(char flag)
{
    unsigned char* s = (unsigned char*)this;
    if (flag == 0) {
        void* p = EAAlloc(0x58, g_str_Swarm);
        void* d = p ? &((LightEffectSub*)p)->copy_construct(*(const LightEffectSub*)(s + 0x38)) : 0;
        ((DescInstaller*)*(void**)(s + 0x30))->Install(*(void**)(s + 0x90), 10, d);
    }
    if (*(unsigned char**)(s + 0x90) != *(unsigned char**)(s + 0x94)) {
        **(unsigned char**)(s + 0x90) = 0;
        *(void**)(s + 0x94) = *(void**)(s + 0x90);
    }
}
