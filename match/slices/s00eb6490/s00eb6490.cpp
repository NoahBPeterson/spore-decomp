// Slice s00eb6490 (gold7 index 36): methods of SP::cGameCinematicsCameraController.
//   destructor -- derived vtable reset, tree nuke, 15 spline SpVector releases, owner release,
//                 base vtable reset (0x00eb6490)
//   per-frame housekeeping: walk the trigger rbtree, toggle each trigger's flag, nuke the tree,
//                 renormalize the subject position, hand the active triggers to the trigger manager (0x00eb6760)
//   constructor __thiscall(this, void* pOwner), returns this (ret 4) (0x00eb6a10)
//   Update(uint32_t deltaTicks, cViewer* viewer), ret 8 (0x00eb6c90)
//   BuildTrack(Vector3* points, int n, float ex, float ey, float ez), ret 0x14 (0x00eb7040)
// Layout from the sibling slice s00eb5480 (retail shifts the splines to 0x3c bytes each, so the spline
// block runs +0x1b0 .. +0x2dc, and a fifth track spline sits at +0x2a0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s00eb4420 / s00eb73f0).
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };
struct cSPQuaternion { float x, y, z, w; };
struct Matrix3 { float m[9]; void Assign(const Matrix3& other); };   // 0x0041cb40

extern Vector3 g_zeroVec;          // 0x016c7284: (0,0,0)
extern Matrix3 g_identityMatrix;   // 0x016c7304
extern float   g_one;              // 0x01485720: 1.0f
extern float   g_f700;             // 0x0142eae0: 700.0f
extern float   g_f120;             // 0x013f1f04: 120.0f

void EASTL_allocator_deallocate(void* p);                          // 0x00f47380
struct RBNode;
RBNode* RBTreeIncrement(RBNode* node);                             // 0x00921580
namespace SP { void* App(); void* GetCurrentGameMode(); }

// ---------------------------------------------------------------------------------------------
// SpVector<T>: eastl-style vector<T, sp_vector_allocator>; 0x14 bytes.  The buffer carries an
// allocator ref-count in the word before the data, so release only runs when that word is non-zero.
// ---------------------------------------------------------------------------------------------
struct SpAllocator { uint32_t mData[2]; };

template <class T> struct SpVector {
	T* mpBegin;             // +0x00
	T* mpEnd;               // +0x04
	T* mpCapacity;          // +0x08
	SpAllocator mAllocator; // +0x0c
	void resize(int n);
};

static inline void FreeSpVectorBase(void* mpBegin)
{
	if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
		EASTL_allocator_deallocate(mpBegin);
}

// Hermite track: times, values, slopes (each an SpVector).  0x3c bytes.
template <class T> struct cHermiteSplineInterpolation {
	SpVector<float> mTimes;   // +0x00
	SpVector<T>     mValues;  // +0x14
	SpVector<T>     mSlopes;  // +0x28
	void ComputeSlopes();               // 0x0069a750 (T=Vector3), 0x0069a4c0 (T=float)
	T*   Interpolate(T* out, float t);  // 0x0069a9a0 (T=Vector3), 0x0069a5f0 (T=float)
};

// ---------------------------------------------------------------------------------------------
// Lerp/Slerp state (layout shared with s00eb5480).
// ---------------------------------------------------------------------------------------------
struct tELerpScalar { float mOrig, mCurrent, mTarget, mCurrentTime, mVelocity; };   // 0x14
typedef tELerpScalar tELerpAngle;
struct tSLerpVector3 {
	Vector3 mCurrent, mTarget, mOrig;   // +0x00..0x24
	bool    mOnSphere;                  // +0x24
	float   mCurrentTime;               // +0x28
	Vector3 mVelocity;                  // +0x2c
};                                                                                  // 0x38
struct tELerpQuaternion {
	cSPQuaternion mOrig, mCurrent, mTarget;   // +0x00..0x30
	float mCurrentTime;                       // +0x30
	cSPQuaternion mVelocity;                  // +0x34
};                                                                                  // 0x44

struct cSPTransform {
	uint16_t mFlags;      // +0x00
	uint16_t mModCount;   // +0x02
	Vector3  mOffset;     // +0x04
	float    mScale;      // +0x10
	Matrix3  mRotation;   // +0x14
	float    mExtra;      // +0x38
};                        // 0x3c

// Per-field update helpers (each __thiscall on the lerp state, taking deltaTicks, t, and a flag).
//   FUN_00eb3250 -> scalar state (+0xec mCamOffset, +0xd8 mFieldOfView)
//   FUN_00eb3340 -> angle state  (+0x18 theta, +0x2c phi, +0x40 roll)
//   FUN_00eb3490 -> vector state (+0x54 mSubjectPosition)
//   FUN_00eb6350 -> quaternion state (+0x130 mOrientation)
struct ScalarState : tELerpScalar { void FUN_00eb3250(uint32_t t, float p, uint8_t flag); };
struct AngleState  : tELerpAngle  { void FUN_00eb3340(uint32_t t, float p, uint8_t flag); };
struct VecState    : tSLerpVector3 { void FUN_00eb3490(uint32_t t, float p, uint8_t flag); };
struct QuatState   : tELerpQuaternion { void FUN_00eb6350(uint32_t t, float p, uint8_t flag); };

// rbtree node / header (eastl rbtree: anchor's right/left/parent/color then value slot).
struct RBNode {
	RBNode*  mpNodeRight;   // +0x00
	RBNode*  mpNodeLeft;    // +0x04
	RBNode*  mpNodeParent;  // +0x08
	uint32_t mColor;        // +0x0c
	void*    mpValue;       // +0x10
};                          // 0x14
struct RBTree {
	uint32_t mUnk00;        // +0x00
	RBNode   mAnchor;       // +0x04
	void Nuke(void* root);  // 0x00eb6280
};                          // 0x18

struct cViewer;
struct cTrigger;

// ---------------------------------------------------------------------------------------------
// The camera controller.  Modelled flat (no C++ virtual bases) so the vtable-pointer stores and the
// member teardown order in the ctor/dtor are written explicitly, matching the retail layout.
// ---------------------------------------------------------------------------------------------
struct cGameCinematicsCameraController {
	void*    mpVtbl0;                 // +0x000
	void*    mpVtbl1;                 // +0x004
	void*    mpVtbl2;                 // +0x008
	uint32_t mnField0C;               // +0x00c
	void*    mpOwner;                 // +0x010
	uint32_t mnMode;                  // +0x014
	AngleState  mCameraTheta;         // +0x018
	AngleState  mCameraPhi;           // +0x02c
	AngleState  mCameraRoll;          // +0x040
	VecState    mSubjectPosition;     // +0x054
	VecState    mSubjectDirection;    // +0x08c
	ScalarState mSubjectRadius;       // +0x0c4
	ScalarState mFieldOfView;         // +0x0d8
	ScalarState mCamOffset;           // +0x0ec
	float    mf100;                   // +0x100
	float    mf104;                   // +0x104
	uint8_t  mb108;                   // +0x108
	uint8_t  mb109;                   // +0x109
	uint8_t  mb10A;                   // +0x10a
	uint8_t  mb10B;                   // +0x10b
	float    mf10C;                   // +0x10c
	uint32_t mn110;                   // +0x110
	uint32_t mn114;                   // +0x114
	uint8_t  mPad118[0x130 - 0x118];  // +0x118
	QuatState mOrientation;           // +0x130
	cSPTransform mCurrentTransform;   // +0x174
	cHermiteSplineInterpolation<float>      mDistanceSpline;     // +0x1b0
	cHermiteSplineInterpolation<float>      mPitchSpline;        // +0x1ec
	cHermiteSplineInterpolation<Vector3>    mDirectionSpline;    // +0x228
	cHermiteSplineInterpolation<cSPQuaternion> mOrientationSpline;  // +0x264
	cHermiteSplineInterpolation<Vector3>    mTrackSpline;        // +0x2a0
	Vector3  mTrackPoint;             // +0x2dc
	float    mf2E8;                   // +0x2e8
	float    mf2EC;                   // +0x2ec
	RBTree   mTree;                   // +0x2f0

	cGameCinematicsCameraController* Construct(void* pOwner);   // 0x00eb6a10
	~cGameCinematicsCameraController();                        // 0x00eb6490
	void Update();                                             // 0x00eb6760
	void UpdateView(uint32_t deltaTicks, cViewer* pViewer);    // 0x00eb6c90
	void BuildTrack(Vector3* points, int n, float ex, float ey, float ez);   // 0x00eb7040
	void UpdateInterpolation(float deltaTime);                 // 0x00eb5480
	void UpdateTransform(cSPTransform* pOut);                  // 0x00eb4420
};

struct cViewer {
	void SetViewAngle(float angle);                        // 0x007c5350
	void SetField100(float v);                             // 0x007c4ba0
	void SetField104(float v);                             // 0x007c4bc0
	void SetBasis(void* pTransform);                       // 0x007c4d00
	void GetCameraLocationInfo(Vector3* a, Vector3* b, Vector3* c, Vector3* d) const;   // 0x007c3d30
};

// Trigger / simulation objects touched by Update().
struct cCreatureData { uint8_t mPad00[0x64]; uint8_t mb64; };                    // +0x64 flag
struct cTriggerLinked {
	void* mpVtbl;                    // +0x00
	uint8_t mPad04[0xb54 - 0x04];    // +0x04
	void* mpCreatureData;            // +0xb54
	uint8_t mPadB58[0xf90 - 0xb58];  // +0xb58
	uint8_t mbF90;                   // +0xf90
};
struct cTrigger {
	void* mpVtbl;                   // +0x00
	uint8_t mPad04[0x14 - 0x04];    // +0x04
	void* mpAttachment;             // +0x14
	uint8_t mPad18[0x50 - 0x18];    // +0x18
	uint32_t mFlags50;              // +0x50
};
struct cAttachment {
	void* mpVtbl;                    // +0x00
	uint8_t mPad04[0x10 - 0x04];     // +0x04
};
struct cTriggerMgrJob {
	uint32_t mPad00[0x4c / 4];
};

void* FUN_00b3d4d0();                    // 0x00b3d4d0 GetTriggerMgr
void* FUN_00b3d240();                    // 0x00b3d240 trigger job source
bool  FUN_00adb360(void* mgr, cTrigger* trig);   // 0x00adb360
void  FUN_00eb62c0(void* tree, void* node, uint32_t flags);   // 0x00eb62c0

// ---------------------------------------------------------------------------------------------
// @ 0x00eb6a10  constructor
// ---------------------------------------------------------------------------------------------
cGameCinematicsCameraController* cGameCinematicsCameraController::Construct(void* pOwner)
{
	*(volatile void**)&mpVtbl1 = (void*)0x013eb384;   // cListenerBase subobject vtable
	*(volatile void**)&mpVtbl2 = (void*)0x013ef094;   // SP::Audio::IEventModifier subobject vtable
	mnField0C = 0;
	mpVtbl0 = (void*)0x014886b0;
	mpVtbl1 = (void*)0x014886a0;
	mpVtbl2 = (void*)0x0148869c;
	mpOwner = pOwner;
	if (pOwner != 0)
		(*(void(__thiscall**)(void*))(*(char**)pOwner))(pOwner);

	mf100 = -1.0f;
	mf104 = -1.0f;
	mf10C = 0.0f;
	mnMode = 4;
	mb108 = 0;
	mb109 = 0;
	mb10A = 0;
	mb10B = 1;
	mn110 = 1000;
	mn114 = 0;
	mCurrentTransform.mModCount = 0;
	mCurrentTransform.mFlags = 0;
	mCurrentTransform.mOffset.x = g_zeroVec.x;
	mCurrentTransform.mOffset.y = g_zeroVec.y;
	mCurrentTransform.mOffset.z = g_zeroVec.z;
	mCurrentTransform.mScale = g_one;
	mCurrentTransform.mRotation.Assign(g_identityMatrix);
	mCurrentTransform.mExtra = 0.0f;

	// mDistanceSpline / mPitchSpline / mDirectionSpline / mOrientationSpline / mTrackSpline: clear each vector.
	mDistanceSpline.mTimes.mpBegin = 0;    mDistanceSpline.mTimes.mpEnd = 0;    mDistanceSpline.mTimes.mpCapacity = 0;
	mDistanceSpline.mValues.mpBegin = 0;   mDistanceSpline.mValues.mpEnd = 0;   mDistanceSpline.mValues.mpCapacity = 0;
	mDistanceSpline.mSlopes.mpBegin = 0;   mDistanceSpline.mSlopes.mpEnd = 0;   mDistanceSpline.mSlopes.mpCapacity = 0;
	mPitchSpline.mTimes.mpBegin = 0;       mPitchSpline.mTimes.mpEnd = 0;       mPitchSpline.mTimes.mpCapacity = 0;
	mPitchSpline.mValues.mpBegin = 0;      mPitchSpline.mValues.mpEnd = 0;      mPitchSpline.mValues.mpCapacity = 0;
	mPitchSpline.mSlopes.mpBegin = 0;      mPitchSpline.mSlopes.mpEnd = 0;      mPitchSpline.mSlopes.mpCapacity = 0;
	mDirectionSpline.mTimes.mpBegin = 0;   mDirectionSpline.mTimes.mpEnd = 0;   mDirectionSpline.mTimes.mpCapacity = 0;
	mDirectionSpline.mValues.mpBegin = 0;  mDirectionSpline.mValues.mpEnd = 0;  mDirectionSpline.mValues.mpCapacity = 0;
	mDirectionSpline.mSlopes.mpBegin = 0;  mDirectionSpline.mSlopes.mpEnd = 0;  mDirectionSpline.mSlopes.mpCapacity = 0;
	mOrientationSpline.mTimes.mpBegin = 0; mOrientationSpline.mTimes.mpEnd = 0; mOrientationSpline.mTimes.mpCapacity = 0;
	mOrientationSpline.mValues.mpBegin = 0; mOrientationSpline.mValues.mpEnd = 0; mOrientationSpline.mValues.mpCapacity = 0;
	mOrientationSpline.mSlopes.mpBegin = 0; mOrientationSpline.mSlopes.mpEnd = 0; mOrientationSpline.mSlopes.mpCapacity = 0;
	mTrackSpline.mTimes.mpBegin = 0;       mTrackSpline.mTimes.mpEnd = 0;       mTrackSpline.mTimes.mpCapacity = 0;
	mTrackSpline.mValues.mpBegin = 0;      mTrackSpline.mValues.mpEnd = 0;      mTrackSpline.mValues.mpCapacity = 0;
	mTrackSpline.mSlopes.mpBegin = 0;      mTrackSpline.mSlopes.mpEnd = 0;      mTrackSpline.mSlopes.mpCapacity = 0;

	mf2E8 = g_f700;
	mf2EC = g_f120;

	mTree.mAnchor.mpNodeLeft = 0;
	mTree.mAnchor.mpNodeParent = 0;
	mTree.mAnchor.mColor = 0;
	mTree.mAnchor.mpNodeLeft = &mTree.mAnchor;
	mTree.mAnchor.mpNodeRight = &mTree.mAnchor;
	mTree.mAnchor.mpNodeParent = 0;
	mTree.mAnchor.mColor = 0;
	mTree.mAnchor.mpValue = 0;
	return this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00eb6490  destructor
// ---------------------------------------------------------------------------------------------
cGameCinematicsCameraController::~cGameCinematicsCameraController()
{
	mpVtbl0 = (void*)0x014886b0;
	mpVtbl1 = (void*)0x014886a0;
	mpVtbl2 = (void*)0x0148869c;
	{
		RBTree* pTree = &mTree;
		pTree->Nuke(pTree->mAnchor.mpNodeParent);
	}

	FreeSpVectorBase(mTrackSpline.mSlopes.mpBegin);
	FreeSpVectorBase(mTrackSpline.mValues.mpBegin);
	FreeSpVectorBase(mTrackSpline.mTimes.mpBegin);
	FreeSpVectorBase(mOrientationSpline.mSlopes.mpBegin);
	FreeSpVectorBase(mOrientationSpline.mValues.mpBegin);
	FreeSpVectorBase(mOrientationSpline.mTimes.mpBegin);
	FreeSpVectorBase(mDirectionSpline.mSlopes.mpBegin);
	FreeSpVectorBase(mDirectionSpline.mValues.mpBegin);
	FreeSpVectorBase(mDirectionSpline.mTimes.mpBegin);
	FreeSpVectorBase(mPitchSpline.mSlopes.mpBegin);
	FreeSpVectorBase(mPitchSpline.mValues.mpBegin);
	FreeSpVectorBase(mPitchSpline.mTimes.mpBegin);
	FreeSpVectorBase(mDistanceSpline.mSlopes.mpBegin);
	FreeSpVectorBase(mDistanceSpline.mValues.mpBegin);
	FreeSpVectorBase(mDistanceSpline.mTimes.mpBegin);

	if (mpOwner != 0)
		(*(void(__thiscall**)(void*))(*(char**)mpOwner + 4))(mpOwner);

	mpVtbl2 = (void*)0x013ef094;   // IEventModifier
	mpVtbl1 = (void*)0x013eb394;   // PaintSystem
	mpVtbl0 = (void*)0x013eb938;   // ITracerBase
}

// ---------------------------------------------------------------------------------------------
// @ 0x00eb6760
// ---------------------------------------------------------------------------------------------
void cGameCinematicsCameraController::Update()
{
	void* app = SP::App();
	void* viewProvider = (*(void*(__thiscall**)(void*))(*(char**)app + 0x50))(app);
	cViewer* viewer = (cViewer*)(*(void*(__thiscall**)(void*))(*(char**)viewProvider + 0x1c))(viewProvider);

	Vector3 locA, locB, locC, locD;
	viewer->GetCameraLocationInfo(&locA, &locB, &locC, &locD);

	for (RBNode* node = mTree.mAnchor.mpNodeLeft; node != &mTree.mAnchor; node = RBTreeIncrement(node))
	{
		cTrigger* trig = (cTrigger*)node->mpValue;
		if (trig != 0)
		{
			cTriggerLinked* linked =
				(cTriggerLinked*)(*(void*(__thiscall**)(void*, uint32_t))(*(char**)trig + 0xc))(trig, 0xce9f6639);
			if (linked != 0)
			{
				((cCreatureData*)linked->mpCreatureData)->mb64 = 1;
				linked->mbF90 = 1;
			}
		}
		if (trig->mpAttachment != 0)
		{
			(*(void(__thiscall**)(void*, int))(*(char**)trig->mpAttachment + 0x10))(trig->mpAttachment, 1);
		}
	}

	mTree.Nuke(mTree.mAnchor.mpNodeParent);
	mTree.mAnchor.mpNodeParent = 0;
	mTree.mAnchor.mColor = 0;
	mTree.mAnchor.mpValue = 0;
	mTree.mAnchor.mpNodeRight = &mTree.mAnchor;
	mTree.mAnchor.mpNodeLeft = &mTree.mAnchor;

	float inv = 1.0f / (float)sqrt((double)mSubjectPosition.mCurrent.x * mSubjectPosition.mCurrent.x
	                             + (double)mSubjectPosition.mCurrent.y * mSubjectPosition.mCurrent.y
	                             + (double)mSubjectPosition.mCurrent.z * mSubjectPosition.mCurrent.z + 1e-08);
	Vector3 offset;
	offset.x = (mSubjectPosition.mCurrent.x * inv + mSubjectPosition.mCurrent.x) - locA.x;
	offset.y = (mSubjectPosition.mCurrent.y + mSubjectPosition.mCurrent.y * inv) - locB.x;
	offset.z = (mSubjectPosition.mCurrent.z + mSubjectPosition.mCurrent.z * inv) - locC.x;

	void* triggerMgr = FUN_00b3d4d0();
	Vector3 jobA, jobB, jobC;
	jobA.x = 0; jobA.y = 0; jobA.z = 0;
	(void)jobB; (void)jobC;
	void* jobSrc = FUN_00b3d240();
	(*(void(__thiscall**)(void*, Vector3*, Vector3*, int))(*(char**)jobSrc + 0x4c))(jobSrc, &offset, &jobA, 4);

	cTrigger** begin = (cTrigger**)&jobA;
	cTrigger** endv = (cTrigger**)&offset;
	cTrigger** p = begin;
	if (p != endv)
	{
		do {
			cTrigger* t = *p;
			bool keep = false;
			if (t != 0)
			{
				keep = (*(void*(__thiscall**)(void*, uint32_t))(*(char**)t + 0xb8))(t, 0xce9f6639) == 0
				    && (*(void*(__thiscall**)(void*, uint32_t))(*(char**)t + 0xb8))(t, 0xaeb336b4) == 0
				    && (t->mFlags50 & 0x200) == 0
				    && !FUN_00adb360(triggerMgr, t);
				if (keep)
				{
					cTrigger* sub = (cTrigger*)(*(void*(__thiscall**)(void*, uint32_t))(*(char**)t + 0xb8))(t, 0x17f243b);
					t = sub;
					keep = (sub != 0);
				}
			}
			if (keep)
			{
				cTriggerLinked* linked =
					(cTriggerLinked*)(*(void*(__thiscall**)(void*, uint32_t))(*(char**)t + 0xc))(t, 0xce9f6639);
				if (linked != 0)
				{
					((cCreatureData*)linked->mpCreatureData)->mb64 = 0;
					linked->mbF90 = 0;
				}
				if (t->mpAttachment != 0)
					(*(void(__thiscall**)(void*, int))(*(char**)t->mpAttachment + 0x10))(t->mpAttachment, 0);
				(*(void(__thiscall**)(void*))(*(char**)t))(t);
				FUN_00eb62c0(&mTree, t, 0);
				(*(void(__thiscall**)(void*))(*(char**)t + 4))(t);
			}
			p++;
		} while (p != endv);
	}

	for (cTrigger** q = begin; q < endv; q++)
	{
		if (*q != 0)
			(*(void(__thiscall**)(void*))(*(char**)*q + 0xc0))(*q);
	}
	FreeSpVectorBase(begin);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00eb6c90
// ---------------------------------------------------------------------------------------------
void cGameCinematicsCameraController::UpdateView(uint32_t deltaTicks, cViewer* pViewer)
{
	if (deltaTicks == 0)
		return;

	if (mFieldOfView.mCurrent > 0.0f)
		pViewer->SetViewAngle(mFieldOfView.mCurrent * 57.29578f);
	if (mf100 > 0.0f)
		pViewer->SetField100(mf100);
	if (mf104 > 0.0f)
		pViewer->SetField104(mf104);

	cSPTransform xform;
	xform.mFlags = 0;
	xform.mModCount = 0;
	xform.mOffset = g_zeroVec;
	xform.mScale = g_one;
	xform.mRotation.Assign(g_identityMatrix);
	UpdateTransform(&xform);
	pViewer->SetBasis(&xform);

	mn114 += deltaTicks;
	float ratio = (float)mn114 / (float)mn110;
	if (ratio > 1.0f)
		ratio = 1.0f;
	if (ratio < 0.0f)
		ratio = 0.0f;
	float step = (float)deltaTicks / (float)mn110;

	switch (mnMode)
	{
	case 2:
		mCamOffset.FUN_00eb3250(deltaTicks, ratio, mb108);
		mOrientation.FUN_00eb6350(deltaTicks, ratio, mb108);
		break;
	case 3:
	{
		Vector3 track;
		Vector3* pRes = mTrackSpline.Interpolate(&track, ratio);
		mTrackPoint.x = pRes->x;
		mTrackPoint.y = pRes->y;
		mTrackPoint.z = pRes->z;
		mSubjectPosition.FUN_00eb3490(deltaTicks, ratio, mb108);
		break;
	}
	case 1:
		UpdateInterpolation(step);
		break;
	default:
		if (mnMode != 0)
		{
			mCameraTheta.FUN_00eb3340(deltaTicks, ratio, mb108);
			mCameraPhi.FUN_00eb3340(deltaTicks, ratio, mb108);
			mCameraRoll.FUN_00eb3340(deltaTicks, ratio, mb108);
		}
		mCamOffset.FUN_00eb3250(deltaTicks, ratio, mb108);
		mOrientation.FUN_00eb6350(deltaTicks, ratio, mb108);
		mSubjectPosition.FUN_00eb3490(deltaTicks, ratio, mb108);
		break;
	}

	if (mFieldOfView.mCurrent == -1.0f && mFieldOfView.mTarget > 0.0f)
	{
		mFieldOfView.mCurrent = mFieldOfView.mTarget;
		mFieldOfView.mOrig = mFieldOfView.mTarget;
	}
	else if (mFieldOfView.mTarget == -1.0f && mFieldOfView.mCurrent > 0.0f)
	{
		mFieldOfView.mTarget = mFieldOfView.mCurrent;
		mFieldOfView.mOrig = mFieldOfView.mCurrent;
	}
	else
	{
		mFieldOfView.FUN_00eb3250(deltaTicks, ratio, mb108);
	}

	void* gamemode = SP::GetCurrentGameMode();
	if (gamemode == (void*)0x01654c10 && *(int*)(*(char**)0x016c7aa4 + 0xcc) == 2)
		Update();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00eb7040
// ---------------------------------------------------------------------------------------------
void cGameCinematicsCameraController::BuildTrack(Vector3* points, int n, float ex, float ey, float ez)
{
	int count = n;
	if (!(ex == g_zeroVec.x && ey == g_zeroVec.y && ez == g_zeroVec.z))
		count = n + 1;

	mTrackSpline.mValues.resize(count);
	mTrackSpline.mTimes.resize(count);
	mTrackSpline.mSlopes.resize(count);

	Vector3* values = mTrackSpline.mValues.mpBegin;
	float*   times  = mTrackSpline.mTimes.mpBegin;
	Vector3* slopes = mTrackSpline.mSlopes.mpBegin;

	float denom = (float)(n - 1);
	for (int i = 0; i < n; i++)
	{
		values[i] = points[i];
		times[i] = (float)i / denom;
		slopes[i] = g_zeroVec;
	}
	if (count > n)
	{
		values[n].x = ex;
		values[n].y = ey;
		values[n].z = ez;
		times[n] = g_one;
		slopes[n] = g_zeroVec;
	}

	mTrackSpline.ComputeSlopes();

	mTrackPoint.x = points[0].x;
	mTrackPoint.y = points[0].y;
	mTrackPoint.z = points[0].z;
}
// ---------------------------------------------------------------------------
// Restored by the gold7 check-in: the exact Owner::ClearItems (00eb66c0) from commit 8dd062dbc,
// dropped when this slice was rewritten for its cGameCinematicsCameraController functions.

struct RbNodeBase {            // EASTL rbtree_node_base (16 bytes)
    RbNodeBase* mpNodeRight;   // +0
    RbNodeBase* mpNodeLeft;    // +4
    RbNodeBase* mpNodeParent;  // +8
    char        mColor;        // +0xc
};

struct RbNode : RbNodeBase {   // tree node: value at +0x10
    struct ObjA* mValue;
};

// Tree object (owner+0x2f0).  Declared only; defined in the original.
struct RbTree {
    char      pad0[4];
    RbNodeBase mAnchor;        // +4 (= owner+0x2f4)
    unsigned int mnNodeCount;  // +0x14
    void DoNukeSubtree(RbNodeBase* p);
};

RbNodeBase* RBTreeIncrement(RbNodeBase* p);   // eastl::RBTreeIncrement, __cdecl

struct Sub {                   // object at Inner+0xb54
    char pad0[0x64];
    unsigned char mFlag64;     // +0x64
};

struct Inner {                 // returned by ObjA slot 3
    char  pad0[0xb54];
    Sub*  mpSub;               // +0xb54
    char  pad1[0xf90 - 0xb58];
    unsigned char mFlagF90;    // +0xf90
};

struct Ctrl {                  // object at ObjA+0x14
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    virtual void c4(int flag); // slot +0x10
};

struct ObjA {                  // tree value
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual Inner* v3(unsigned int id);  // slot +0xc
    virtual void v4();
    char  pad0[0x14 - 4];
    Ctrl* mpCtrl;              // +0x14
};

struct Owner {
    char   pad0[0x2f0];
    RbTree mTree;              // +0x2f0
    void ClearItems();
};

// 00eb66c0
void Owner::ClearItems() {
    RbNodeBase* node = mTree.mAnchor.mpNodeLeft;
    if (node != &mTree.mAnchor) {
        do {
            ObjA* value = static_cast<RbNode*>(node)->mValue;
            if (value) {
                Inner* in = value->v3(0xce9f6639u);
                if (in) {
                    in->mpSub->mFlag64 = 1;
                    in->mFlagF90 = 1;
                }
            }
            if (value->mpCtrl)
                value->mpCtrl->c4(1);
            node = RBTreeIncrement(node);
        } while (node != &mTree.mAnchor);
    }
    RbNodeBase* root = mTree.mAnchor.mpNodeParent;
    RbTree* t = &mTree;
    t->DoNukeSubtree(root);
    t->mAnchor.mpNodeLeft = &t->mAnchor;
    t->mAnchor.mpNodeParent = 0;
    t->mAnchor.mColor = 0;
    t->mnNodeCount = 0;
    t->mAnchor.mpNodeRight = &t->mAnchor;
}
