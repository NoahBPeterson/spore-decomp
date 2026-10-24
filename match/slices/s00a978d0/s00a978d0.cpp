// Slice s00a978d0 (gold7): an EA::Swarm effect/controller cluster plus two function-pointer
// registration thunks. Members of EA::Swarm::cGameEffect, the "Swarm" descriptor factory/reader,
// a class-B destructor/writer pair, an ArgScript LightEffect ctor and a cCameraLifeCommand::Execute.
//
// Layouts are laid out flat to the retail offsets (the retail layout differs from the dev-PDB
// declarations). cSPTransform is 0x38 bytes: {word flags, word modCount, float x/y/z, float scale,
// Matrix3 rotation} (verified against the sibling slice s00eb5480 and the 0x00a98400 copy below).
//
// Functions in this slice (VAs written parenthesised so they are not mistaken for markers):
//   FUN_00a978d0 (0x00a978d0)  effect-list update (per-frame integration + drawer dispatch)
//   FUN_00a97f10 (0x00a97f10)  effect class A registration thunk
//   FUN_00a97f50 (0x00a97f50)  effect class A destructor (ret 4)
//   FUN_00a97f90 (0x00a97f90)  "Swarm" descriptor stream reader
//   EA::Swarm::cGameEffect::SetUnknownParam (0x00a98030)
//   EA::Swarm::cGameEffect::ApplyEffect     (0x00a98050)
//   EA::Swarm::cGameEffect::Init            (0x00a98090)
//   EA::Swarm::cGameEffect::Start           (0x00a980b0)
//   EA::Swarm::cGameEffect::Stop            (0x00a98200)
//   FUN_00a98340 (0x00a98340)  cGameEffect constructor (ret 4)
//   FUN_00a98400 (0x00a98400)  cSPTransform setter (ret 8)
//   FUN_00a98480 (0x00a98480)  "Swarm" descriptor factory
//   FUN_00a984f0 (0x00a984f0)  effect class B registration thunk
//   FUN_00a98520 (0x00a98520)  effect class B destructor
//   FUN_00a985c0 (0x00a985c0)  effect class B stream writer
//   ArgScript::LightEffect::LightEffect (0x00a98670) ctor
//   `anonymous namespace'::cCameraLifeCommand::Execute (0x00a98700)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s00eb6490 / s00eb5480).
#include "types.h"

typedef unsigned int   uint;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef unsigned char  uintptr_t_dummy;   // (unused; kept for parity with sibling sources)

struct Vector3_t { float x, y, z; };   // 0xc
struct Matrix3   { float m[9]; };      // 0x24

// -------------------------------------------------------------------------------------------------
// External helpers (addresses in parentheses; the callee symbols are masked by the byte-diff).
// -------------------------------------------------------------------------------------------------
extern void  operator_delete(void* p);                                    // (0xf47380)
extern void* operator_new(uint size, const char* name, uint, uint, uint, uint); // (0xf473a0)

extern void* EA_IO_ReadInt32(void* stream, void* out, int, int);          // (0x93a780)
extern void* EA_IO_WriteUint32(void* stream, const void* in, int, int);   // (0x93aa70)
extern int   EA_IO_StreamWrite(void* stream, const void* src, int count); // (0x93a9a0)
extern int   EA_IO_WriteUint16(void* stream, const void* in, int, int);   // (0x93a9d0)
extern void* EA_IO_ReadString16(void* stream, void* out);                 // (0x5302b0)
extern void* EA_Messaging_GetServer();                                    // (0x883860)

// these are __thiscall (callee cleans); called through __thiscall function pointers below
extern void* EA_ArgScript_MainArguments();                                // (0x838320)
extern int   EA_ArgScript_HasFlag();                                       // (0x8380b0)
extern void* EA_ArgScript_OptionArguments();                               // (0x838130)

extern void Matrix3_Assign();                                             // (0x41cb40)
extern void cTransform_PreTransformBy();                                  // (0x537f40)
extern void cSPTransformOps_Assign();                                     // (0x537dc0)
extern void AppPropsFields_ctor();                                         // (0x83cdd0)

extern void FUN_00a97830();                                               // (0xa97830)
extern void FUN_00a78e90();                                               // (0xa78e90)
extern void FUN_006e95a0();                                               // (0x6e95a0)
extern void  FUN_007ec580(void* stream, void* v);                         // (0x7ec580)
extern void  FUN_007d0250(void* stream, void* v);                         // (0x7d0250)
extern void  FUN_00a983d0();                                              // (0xa983d0)
extern void* FUN_00a98480(void* stream, int version);                     // (0xa98480)

// -------------------------------------------------------------------------------------------------
// Globals / runtime constants.
// -------------------------------------------------------------------------------------------------
extern float   g_realZero;            // (0x1485378)
extern float   g_realOne;             // (0x1485720)
extern Vector3_t g_vec1678ad0;        // (0x1678ad0)
extern char    g_mat1678b78[];        // (0x1678b78) identity Matrix3
extern u16     gEmptyString16[];      // (0x1667bac) eastl empty 16-bit string sentinel
extern u16     gEmptyString16Cap[];   // (0x1667bad)
extern float   g_fBoundsInit;         // (0x1565198) bound-initialisation magnitude
extern float   g_fTeleportThreshold;  // (0x15651a8) squared-distance teleport threshold

extern char vtable_SwarmDesc[];       // (0x1458750)
extern char vtable_Eff0[];            // (0x1458788)
extern char vtable_Eff1[];            // (0x14599e8)
extern char vtable_IEvent[];          // (0x13ef094) SP::Audio::IEventModifier
extern char vtable_Light0[];          // (0x145884c)
extern char vtable_Light1[];          // (0x1458848)

// -------------------------------------------------------------------------------------------------
// Local flat layouts.
// -------------------------------------------------------------------------------------------------
struct Str16                          // eastl::string16-ish (0xc bytes)
{
	const void* mpBegin;               // +0x00
	const void* mpEnd;                 // +0x04
	u32         mCapacity;             // +0x08
};

struct cSPTransform                    // 0x38 bytes
{
	u16     mFlags;                    // +0x00
	u16     mModCount;                 // +0x02
	float   mOffsetX;                  // +0x04
	float   mOffsetY;                  // +0x08
	float   mOffsetZ;                  // +0x0c
	float   mScale;                    // +0x10
	Matrix3 mRotation;                 // +0x14
};

struct cGameDescription
{
	char  pad00[8];                    // +0x00
	u32   mFlags;                      // +0x08
	u32   mMessageID;                  // +0x0c
	u32   mData1;                      // +0x10
	u32   mData2;                      // +0x14
	u32   mData3;                      // +0x18
	u32   mData4;                      // +0x1c
	const void* mString;               // +0x20
	char  pad24[0x0c];                 // +0x24
	float mLife;                       // +0x30
};

namespace EA { namespace Swarm {

struct IUnknown32;

struct cGameEffect                     // layout from the (0x00a98340) constructor
{
	void*  mpVtbl0;                    // +0x00  (0x1458788)
	void*  mpVtbl1;                    // +0x04  (0x14599e8)
	u32    mn08;                       // +0x08
	cGameDescription* mpDesc;          // +0x0c
	u8     mActive;                    // +0x10
	char   pad11[3];                   // +0x11
	float  mAge;                       // +0x14
	cSPTransform mTransform;           // +0x18
	IUnknown32*  mOwner;               // +0x50

	char SetUnknownParam(int which, IUnknown32* value);   // (0xa98030)
	void ApplyEffect(float dt, int, int);                 // (0xa98050)
	void Init(int, int, void* owner);                     // (0xa98090)
	void Start(int);                                      // (0xa980b0)
	void Stop(int);                                       // (0xa98200)
	void SetTransform(void* xform, const cSPTransform* src);  // (0xa98400)
	cGameEffect* Construct(cGameDescription* desc);       // (0xa98340)
};

// the object (0x00a98090) pulls its owner pointer from (owner field at +0xb8)
struct InitSource
{
	char pad00[0xb8];                  // +0x00
	IUnknown32* mpOwner;               // +0xb8
};

} } // namespace EA::Swarm

using EA::Swarm::cGameEffect;
using EA::Swarm::IUnknown32;

// payload for the messaging dispatch in Start/Stop: 8-byte-strided value slots
struct EffectMsg
{
	u32 mData1;                        // +0x00
	u32 mPad04;                        // +0x04
	u32 mData2;                        // +0x08
	u32 mPad0c;                        // +0x0c
	u32 mData3;                        // +0x10
	u32 mPad14;                        // +0x14
	u32 mData4;                        // +0x18
	u32 mPad1c;                        // +0x1c
	const void* mString;               // +0x20
	u32 mPad24;                        // +0x24
	void* mTransform;                  // +0x28
	u32 mPad2c;                        // +0x2c
	void* mOwner;                      // +0x30
	u32 mPad34;                        // +0x34
	u32 mType;                         // +0x38
	u32 mPad3c;                        // +0x3c
};

// -------------------------------------------------------------------------------------------------
// free-list idiom wrapper (reads as a member operation, inlines to the (0xf47380) delete)
// -------------------------------------------------------------------------------------------------
static inline void DestroySpVector(void* mpBegin)
{
	if (mpBegin && ((int*)mpBegin)[-1])
		operator_delete(mpBegin);
}

// =================================================================================================
// (0x00a978d0) effect-list update
// =================================================================================================
struct SwarmNode
{
	SwarmNode* mpNext;                 // +0x00
	SwarmNode* mpPrev;                 // +0x04
	float mf08;                        // +0x08
	float mf0c;                        // +0x0c
	float mf10;                        // +0x10
	float mf14;                        // +0x14
	float mf18;                        // +0x18
	float mf1c;                        // +0x1c
	float mf20;                        // +0x20
	float mf24;                        // +0x24
	float mf28;                        // +0x28
};
extern SwarmNode* g_pNodeFreeList;     // (0x167888c)

struct Desc1c                          // *(this+0x1c): the effect description side
{
	char  pad00[8];                    // +0x00
	u32   mFlags;                      // +0x08
	char  pad0c[8];                    // +0x0c
	float mf14;                        // +0x14
	char  pad18[0x48];                 // +0x18
	float* mp60;                       // +0x60
	char  pad64[0x10];                 // +0x64
	float mf74;                        // +0x74
	char  pad78[0x44];                 // +0x78
	float mfBC;                        // +0xbc
	float mfC0;                        // +0xc0
	float mfC4;                        // +0xc4
	char  padC8[0x1c];                 // +0xc8
	float mfE4;                        // +0xe4
	float mfE8;                        // +0xe8
	float mfEC;                        // +0xec
	float mfF0;                        // +0xf0
	float mfF4;                        // +0xf4
	char  padF8[0x10];                 // +0xf8
	float mf108;                       // +0x108
};

struct Desc24                          // *(this+0x24): the "player"/avatar side
{
	float mf00;                        // +0x00
	char  pad04[4];                    // +0x04
	float mf08;                        // +0x08
	char  pad0c[0xb0];                 // +0x0c
	float mfBC;                        // +0xbc
	float mfC0;                        // +0xc0
	float mfC4;                        // +0xc4
	char  padC8[0x10];                 // +0xc8
	float mfD8;                        // +0xd8
	float mfDC;                        // +0xdc
	float mfE0;                        // +0xe0
};

struct Xform38                         // *(this+0xc8): a transform used by the drawer dispatch
{
	char  pad00[0x10];                 // +0x00
	float mf10;                        // +0x10  (read as *(this+0xd8))
	char  pad14[0x24];                 // +0x14
};

struct UpdateCtx                       // the caller's per-frame stats block (third parameter)
{
	char pad00[0x10];                  // +0x00
	int  mn10;                         // +0x10
	int  mn14;                         // +0x14
};

struct SwarmCtrl
{
	char       pad00[0x0c];            // +0x00
	u8         mb0c;                   // +0x0c
	u8         mb0d;                   // +0x0d
	char       pad0e[2];               // +0x0e
	SwarmNode* mpNext;                 // +0x10  (list sentinel embedded here)
	SwarmNode* mpPrev;                 // +0x14
	int        mn18;                   // +0x18
	Desc1c*    mp1c;                   // +0x1c
	void*      mp20;                   // +0x20
	Desc24*    mp24;                   // +0x24
	char       pad28[4];               // +0x28
	double     mTimeD;                 // +0x2c
	u8         mb34;                   // +0x34
	char       pad35[0x23];            // +0x35
	Vector3_t  mPos;                   // +0x58
	Vector3_t  mBoundsMin;             // +0x68
	Vector3_t  mBoundsMax;             // +0x74
	float      mf80;                   // +0x80
	char       pad84[0x10];            // +0x84
	Vector3_t  mWorld;                 // +0x94
	char       padA0[0x28];            // +0xa0
	Xform38    mXform;                 // +0xc8
	Vector3_t  mLastTeleport;          // +0x100
	u16        mw10c;                  // +0x10c
	u16        mw10e;                  // +0x10e
	float      mf110;                  // +0x110
	float      mf114;                  // +0x114
	float      mf118;                  // +0x118
	float      mf11c;                  // +0x11c
	float      mf120;                  // +0x120
	float      mf124;                  // +0x124
	float      mf12c;                  // +0x12c
	char       pad130[4];              // +0x130
	float      mf134;                  // +0x134
	float      mf138;                  // +0x138
	u32        mn13c;                  // +0x13c
	u32        mn140;                  // +0x140
	u32        mn144;                  // +0x144
	float      mf148;                  // +0x148
	float      mf14c;                  // +0x14c
	float      mf150;                  // +0x150
	u32        mn154;                  // +0x154
	u32        mn158;                  // +0x158
	u32        mn15c;                  // +0x15c
	char       pad160[0x24];           // +0x160
	int        mn184;                  // +0x184

	void Update(float dt, float param3, UpdateCtx* ctx);
};

// @ 0x00a978d0
void SwarmCtrl::Update(float dt, float param3, UpdateCtx* ctx)
{
	Desc1c* d;

	if (mb34 == 0) {
		if (mw10e < mw10c) {
			ctx->mn14 += (int)(mw10c - mw10e) * mn18;
			mw10e = mw10c;
		}
	} else {
		dt = mp1c->mf14 + dt;
		mb34 = 0;
	}

	if (dt < 0.0f)
		return;

	d = mp1c;
	if (((d->mFlags >> 10) & 1) != 0 && mb0d == 0) {
		float f = (float)((1.0 - mTimeD) * d->mf74 - 0.01);
		float keep = 0.0f;
		if (f <= 0.0f || (keep = f, f < dt))
			dt = keep;
	}

	float fz = mWorld.z;
	float fy = mWorld.y;
	float fx = mWorld.x;
	float dz = fz - mLastTeleport.z;
	float dy = fy - mLastTeleport.y;
	float dx = fx - mLastTeleport.x;
	if (g_fTeleportThreshold < (dz * dz + dy * dy) + dx * dx) {
		mLastTeleport.x = fx;
		mLastTeleport.y = fy;
		mLastTeleport.z = fz;
	}

	mf148 = ((mf114 - mf110) * param3 + mf110) * mf12c;
	mn154 = mn13c;
	mn158 = mn140;
	mf150 = ((mf124 - mf120) * param3 + mf120) * mf138;
	mn15c = mn144;
	mf14c = ((mf11c - mf118) * param3 + mf118) * mf134;

	Desc24* av;
	if ((d->mFlags & 1) == 0 && ((d->mFlags >> 1) & 1) == 0) {
		av = mp24;
	} else {
		av = mp24;
		if (*d->mp60 <= (float)(int)av->mf08)
			goto LAB_ae9;
	}
	mf148 = mf148 * av->mf00;

LAB_ae9:
	{
		Desc1c* p = mp1c;
		mTimeD = (double)(dt + (float)mTimeD);

		float vF4 = p->mfF4;
		float tD8 = av->mfD8;
		float tDC = av->mfDC;
		float tE0 = av->mfE0;
		mPos.x = tD8 * vF4;
		mPos.y = tDC * vF4;
		mPos.z = tE0 * vF4;

		float vF0 = p->mfF0;
		float tBC = av->mfBC;
		float tC0 = av->mfC0;
		float tC4 = av->mfC4;
		mPos.x = tBC * vF0 + mPos.x;
		mPos.y = tC0 * vF0 + mPos.y;
		mPos.z = tC4 * vF0 + mPos.z;

		((void(__thiscall*)(void*, void*))FUN_00a78e90)(&mXform, &mPos);

		p = mp1c;
		mPos.y = p->mfE8 + mPos.y;
		mPos.x = p->mfE4 + mPos.x;
		mPos.z = p->mfEC + mPos.z;

		mBoundsMin.x = g_fBoundsInit;
		mBoundsMin.y = g_fBoundsInit;
		mBoundsMin.z = g_fBoundsInit;
		float neg = -g_fBoundsInit;
		mBoundsMax.x = neg;
		mBoundsMax.y = neg;
		mBoundsMax.z = neg;

		SwarmNode* end = (SwarmNode*)((char*)this + 0x10);
		SwarmNode* node = mpNext;
		while (node != end) {
			float cur = node->mf08;
			node->mf08 = cur + dt;
			if (node->mf0c <= cur + dt) {
				SwarmNode* prev = node->mpPrev;
				SwarmNode* next = node->mpNext;
				prev->mpNext = next;
				next->mpPrev = prev;
				node->mpNext = 0;
				node->mpPrev = 0;
				--mn18;
				node->mpNext = g_pNodeFreeList;
				g_pNodeFreeList = node;
				node = next;
			} else {
				float m20 = node->mf20;
				float px = mPos.x;
				float pz = mPos.z;
				float m1c = node->mf1c;
				Desc1c* p2 = mp1c;
				float m24 = node->mf24;
				float n20 = mPos.y * dt + node->mf20;
				node->mf20 = n20;
				float n24 = node->mf24 + pz * dt;
				node->mf24 = n24;
				float n1c = m1c + px * dt;
				node->mf1c = n1c;
				float damp = 1.0f - p2->mf108 * dt;
				float d1c = damp * n1c;
				node->mf1c = d1c;
				float d24 = damp * n24;
				node->mf24 = d24;
				float d20 = damp * n20;
				node->mf20 = d20;
				float half = dt * 0.5f;
				float v10 = node->mf10 + (d1c + m1c) * half;
				node->mf18 = (d24 + m24) * half + node->mf18;
				node->mf10 = v10;
				node->mf14 = (d20 + m20) * half + node->mf14;
				if (v10 < mBoundsMin.x)
					mBoundsMin.x = v10;
				float q = node->mf10;
				if (mBoundsMax.x <= q && q != mBoundsMax.x)
					mBoundsMax.x = q;
				if (node->mf14 < mBoundsMin.y)
					mBoundsMin.y = node->mf14;
				q = node->mf14;
				if (mBoundsMax.y <= q && q != mBoundsMax.y)
					mBoundsMax.y = q;
				if (node->mf18 < mBoundsMin.z)
					mBoundsMin.z = node->mf18;
				q = node->mf18;
				if (mBoundsMax.z <= q && q != mBoundsMax.z)
					mBoundsMax.z = q;
				node = node->mpNext;
			}
		}
	}

	if (mb0d == 0)
		((void(__thiscall*)(void*, float))FUN_00a97830)((void*)((char*)this - 4), dt);

	((void(__thiscall*)(void*, void*))FUN_006e95a0)(&mBoundsMin, &mXform);

	if (mn184 >= 0) {
		float fv = mXform.mf10;
		float f80 = mf80;
		float f14c = mf14c;
		void* mgr = mp20;
		void* q = (*(void*(__thiscall**)(void*))(*(char**)mgr + 0x20))(mgr);
		(*(void(__thiscall**)(void*, int, void*, float))(*(char**)q + 0x20))(q, mn184, &mBoundsMin, (fv * f80) * f14c);
	}

	if (mn18 == 0 && mb0d != 0) {
		mb0c = 0;
		if (mn184 >= 0) {
			void* mgr = mp20;
			void* q = (*(void*(__thiscall**)(void*))(*(char**)mgr + 0x20))(mgr);
			(*(void(__thiscall**)(void*, int, int))(*(char**)q + 0x24))(q, mn184, 0);
			return;
		}
	} else {
		mLastTeleport.x = fx;
		mLastTeleport.y = fy;
		mLastTeleport.z = fz;
		ctx->mn10 += mn18;
	}
}

// =================================================================================================
// (0x00a97f10 / 0x00a984f0) effect class registration thunks
// =================================================================================================
extern void* g_1676030;
extern void* g_1676038;
extern void* g_167603c;
extern void* g_1676044;
extern int   g_1676048;
extern int   g_167604c;
extern void FUN_00a96bb0();
extern void FUN_00a96b70();
extern void FUN_00a97ec0();
extern void FUN_00a940e0();

// @ 0x00a97f10
void FUN_00a97f10()
{
	g_1676030 = (void*)FUN_00a96bb0;
	g_1676038 = (void*)FUN_00a96b70;
	g_167603c = (void*)FUN_00a97ec0;
	g_1676044 = (void*)FUN_00a940e0;
	g_1676048 = 1;
	g_167604c = 1;
}

extern void* g_1676018;
extern void* g_167601c;
extern int   g_1676028;
extern int   g_167602c;

// @ 0x00a984f0
void FUN_00a984f0()
{
	g_1676018 = (void*)FUN_00a983d0;
	g_167601c = (void*)FUN_00a98480;
	g_1676028 = 1;
	g_167602c = 1;
}

// =================================================================================================
// (0x00a97f50) effect class A destructor (ret 4)
// =================================================================================================
struct EffectObjA
{
	void* mpVtbl;                      // +0x00
	char  pad04[0x1c];                 // +0x04
	int   mnBegin;                     // +0x20  (managed buffer address)
	char  pad24[4];                    // +0x24
	int   mnEnd;                       // +0x28

	void* Destroy(char freeSelf);
};

// @ 0x00a97f50
void* EffectObjA::Destroy(char freeSelf)
{
	int begin = mnBegin;
	if (mnEnd - begin > 1 && begin != 0)
		operator_delete((void*)begin);

	mpVtbl = (void*)vtable_IEvent;

	if ((freeSelf & 1) != 0)
		operator_delete(this);
	return this;
}

// =================================================================================================
// (0x00a97f90) "Swarm" descriptor stream reader
// =================================================================================================
struct SwarmDesc                       // the 0x34-byte object built by (0x00a98480)
{
	void*  mpVtbl;                     // +0x00
	u32    mn04;                       // +0x04
	u32    mn08;                       // +0x08
	u32    mn0c;                       // +0x0c
	u32    mn10;                       // +0x10
	u32    mn14;                       // +0x14
	u32    mn18;                       // +0x18
	u32    mn1c;                       // +0x1c
	Str16  mStr;                       // +0x20
	u32    mn2c;                       // +0x2c
	float  mf30;                       // +0x30
};

// @ 0x00a97f90
void FUN_00a97f90(void* stream, int unusedVersion, SwarmDesc* desc)
{
	u32 tmp;

	EA_IO_ReadInt32(stream, &tmp, 1, 0);
	desc->mn08 = tmp & 0x3ff;

	EA_IO_ReadInt32(stream, &desc->mn0c, 1, 0);
	EA_IO_ReadInt32(stream, &desc->mn10, 1, 0);
	EA_IO_ReadInt32(stream, &desc->mn14, 1, 0);

	EA_IO_ReadInt32(stream, &desc->mn18, 1, 0);
	EA_IO_ReadInt32(stream, &desc->mn1c, 1, 0);
	EA_IO_ReadString16(stream, &desc->mStr);
	EA_IO_ReadInt32(stream, &desc->mf30, 1, 0);
}

// =================================================================================================
// (0x00a98030) cGameEffect::SetUnknownParam
// =================================================================================================
// @ 0x00a98030
char cGameEffect::SetUnknownParam(int which, IUnknown32* value)
{
	char result = 1;
	if (which == 1)
		mOwner = value;
	else
		result = 0;
	return result;
}

// =================================================================================================
// (0x00a98050) cGameEffect::ApplyEffect
// =================================================================================================
// @ 0x00a98050
void cGameEffect::ApplyEffect(float dt, int, int)
{
	mAge = dt + mAge;
	float life = mpDesc->mLife;
	if (life > g_realZero && mAge > life)
		(*(void(__thiscall**)(void*, int))(*(char**)this + 0x0c))(this, 0);
}

// =================================================================================================
// (0x00a98090) cGameEffect::Init
// =================================================================================================
// @ 0x00a98090
void cGameEffect::Init(int, int, void* owner)
{
	if (owner != 0)
		mOwner = ((InitSource*)owner)->mpOwner;
}

// =================================================================================================
// (0x00a980b0) cGameEffect::Start
// =================================================================================================
// @ 0x00a980b0
void cGameEffect::Start(int)
{
	if (mActive != 0)
		return;

	mActive = 1;
	mAge = 0.0f;

	void* server = EA_Messaging_GetServer();
	if (server == 0)
		return;

	cGameDescription* desc = mpDesc;

	if (((desc->mFlags >> 3) & 1) != 0) {
		EffectMsg msg;
		msg.mType = 0;
		if (((desc->mFlags >> 5) & 1) != 0)
			msg.mData1 = desc->mData1;
		if (((desc->mFlags >> 6) & 1) != 0)
			msg.mData2 = desc->mData2;
		if (((desc->mFlags >> 7) & 1) != 0)
			msg.mData3 = desc->mData3;
		if (((desc->mFlags >> 8) & 1) != 0)
			msg.mData4 = desc->mData4;
		if (((desc->mFlags >> 9) & 1) != 0)
			msg.mString = desc->mString;
		msg.mOwner = mOwner;
		msg.mTransform = &mTransform;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, desc->mMessageID, &msg, 0);
	}

	cGameDescription* desc0 = mpDesc;
	if ((desc0->mFlags & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 0;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8471, &msg, 0);
	}

	cGameDescription* desc1 = mpDesc;
	if (((desc1->mFlags >> 1) & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 1;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8471, &msg, 0);
	}

	cGameDescription* desc2 = mpDesc;
	if (((desc2->mFlags >> 2) & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 2;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8473, &msg, 0);
	}
}

// =================================================================================================
// (0x00a98200) cGameEffect::Stop
// =================================================================================================
// @ 0x00a98200
void cGameEffect::Stop(int)
{
	if (mActive == 0)
		return;

	mActive = 0;

	void* server = EA_Messaging_GetServer();
	if (server == 0)
		return;

	cGameDescription* desc = mpDesc;

	if ((desc->mFlags & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 0;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8472, &msg, 0);
	}

	cGameDescription* desc1 = mpDesc;
	if (((desc1->mFlags >> 1) & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 1;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8472, &msg, 0);
	}

	cGameDescription* desc2 = mpDesc;
	if (((desc2->mFlags >> 2) & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 0;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8474, &msg, 0);
	}

	cGameDescription* desc3 = mpDesc;
	if (((desc3->mFlags >> 4) & 1) != 0) {
		EffectMsg msg;
		msg.mType = 0;
		if (((desc3->mFlags >> 5) & 1) != 0)
			msg.mData1 = desc3->mData1;
		if (((desc3->mFlags >> 6) & 1) != 0)
			msg.mData2 = desc3->mData2;
		if (((desc3->mFlags >> 7) & 1) != 0)
			msg.mData3 = desc3->mData3;
		if (((desc3->mFlags >> 8) & 1) != 0)
			msg.mData4 = desc3->mData4;
		if (((desc3->mFlags >> 9) & 1) != 0)
			msg.mString = desc3->mString;
		msg.mOwner = mOwner;
		msg.mTransform = &mTransform;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, desc3->mMessageID, &msg, 0);
	}
}

// =================================================================================================
// (0x00a98340) cGameEffect constructor (ret 4)
// =================================================================================================
// @ 0x00a98340
cGameEffect* cGameEffect::Construct(cGameDescription* desc)
{
	*(volatile void**)&mpVtbl1 = (void*)vtable_IEvent;
	mn08 = 0;
	mAge = 0.0f;
	mpVtbl0 = (void*)vtable_Eff0;
	mpVtbl1 = (void*)vtable_Eff1;
	mpDesc = desc;
	mActive = 0;
	mTransform.mFlags = 0;
	mTransform.mModCount = 0;
	mTransform.mOffsetX = g_vec1678ad0.x;
	mTransform.mOffsetY = g_vec1678ad0.y;
	mTransform.mOffsetZ = g_vec1678ad0.z;
	mTransform.mScale = g_realOne;
	((void(__thiscall*)(void*, const void*))Matrix3_Assign)(&mTransform.mRotation, g_mat1678b78);
	mOwner = 0;
	return this;
}

// =================================================================================================
// (0x00a98400) cSPTransform setter (ret 8)
// =================================================================================================
// @ 0x00a98400
void cGameEffect::SetTransform(void* xform, const cSPTransform* src)
{
	cSPTransform tmp;
	tmp.mFlags = src->mFlags;
	tmp.mModCount = src->mModCount;
	tmp.mOffsetX = src->mOffsetX;
	tmp.mOffsetY = src->mOffsetY;
	tmp.mOffsetZ = src->mOffsetZ;
	tmp.mScale = src->mScale;
	((void(__thiscall*)(void*, const void*))Matrix3_Assign)(&tmp.mRotation, &src->mRotation);
	((void(__thiscall*)(void*, void*))cTransform_PreTransformBy)(&tmp, xform);
	((void(__thiscall*)(void*, const void*))cSPTransformOps_Assign)(&mTransform, &tmp);
}

// =================================================================================================
// (0x00a98480) "Swarm" descriptor factory
// =================================================================================================
// @ 0x00a98480
void* FUN_00a98480(void* stream, int version)
{
	SwarmDesc* obj = 0;
	SwarmDesc* p = (SwarmDesc*)operator_new(0x34, "Swarm", 0, 0, 0, 0);
	if (p != 0) {
		p->mn04 = 0;
		p->mpVtbl = (void*)vtable_SwarmDesc;
		p->mn08 = 0;
		p->mn0c = 0;
		p->mn10 = 0;
		p->mn14 = 0;
		p->mn18 = 0;
		p->mn1c = 0;
		p->mStr.mpBegin = gEmptyString16;
		p->mStr.mpEnd = gEmptyString16;
		p->mStr.mCapacity = (u32)gEmptyString16Cap;
		p->mf30 = 0.0f;
		obj = p;
	}
	FUN_00a97f90(stream, version, obj);
	return obj;
}

// =================================================================================================
// (0x00a98520) effect class B destructor
// =================================================================================================
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

// @ 0x00a98520
void EffectObjB::Destroy()
{
	DestroySpVector(mpVec40);
	DestroySpVector(mpVec2c);
	DestroySpVector(mpVec18);
	mpVtbl = (void*)vtable_IEvent;
}

// =================================================================================================
// (0x00a985c0) effect class B stream writer
// =================================================================================================
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

// =================================================================================================
// (0x00a98670) ArgScript::LightEffect constructor
// =================================================================================================
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
};

// @ 0x00a98670
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

} // namespace ArgScript

// =================================================================================================
// (0x00a98700) `anonymous namespace'::cCameraLifeCommand::Execute (ret 4)
// =================================================================================================
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