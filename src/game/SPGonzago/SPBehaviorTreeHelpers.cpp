// src/game/SPGonzago/SPBehaviorTreeHelpers.cpp -- migrated from slice(s) s00ec0a40, s00bc8ff0, s00d990a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPBehaviorTreeHelpers.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPVector3.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cActionCircle.h"
#include "SP/cAnimState.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpatialObject.h"
#include <math.h>
#include <intrin.h>

// ---- items of slice s00d990a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
};
extern Vector3 gStimulusDefaultVec;
struct behavior_stimuli {
    int32_t mStimulusID;                                              // +0x00
    int32_t mField04;                                                 // +0x04
    int32_t mDuration;                                                // +0x08
    Vector3 mOffset;                                                  // +0x0c
    int32_t mField18;                                                 // +0x18
    int32_t mField1c;                                                 // +0x1c
    int32_t mField20;                                                 // +0x20
    float mf24;                                                       // +0x24

    behavior_stimuli& GetAny();                                       // 0x00d997e0
};
// ---- items of slice s00d990a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Vector3 gStimulusDefaultVec;

// ---- items of slice s00bc8ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
#pragma pack(pop)
#pragma pack(push, 1)
struct IRefCounted
{
	virtual void AddRef();       // +0x00
	virtual void Release();      // +0x04
	virtual void V2();           // +0x08
	virtual void V3();           // +0x0c
	virtual void V4();           // +0x10
	virtual void V5();           // +0x14
	virtual void V6();           // +0x18
	virtual void V7();           // +0x1c
	virtual void V8();           // +0x20
	virtual void V9();           // +0x24
	virtual void V10();          // +0x28
	virtual bool V11();          // +0x2c
};
struct Stimulus
{
	uint32_t     id;          // +0x00
	uint32_t     mask;        // +0x04
	float        duration;    // +0x08
	uint32_t     pad0c[8];    // +0x0c
	IRefCounted* volatile object;      // +0x2c
	uint32_t     pad30[2];    // +0x30
};
struct Stimuli
{
	void SetStimulus(Stimulus* s, uint32_t a, uint32_t b, float c, IRefCounted* obj);
	void ClearStimulus(Stimulus* s);
	void ResetStimuli();
	void ClearAll(uint32_t a, uint32_t b);
	uint32_t* UpdateStimuli(float dt);

	Stimulus slot[8];         // +0x000
	uint32_t mMask0;          // +0x1c0
	uint32_t mMask1;          // +0x1c4
};
extern void (*g_0168B54C)(void*);   // 0x0168b54c
// ---- items of slice s00bc8ff0 end

// ---- items of slice s00ec0a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  uint;
struct IRefCounted_s00ec_0a40 {
    virtual void AddRef();    // +0x00
    virtual void Release();   // +0x04
};
struct Stimulus_s00ec_0a40 {
    uint         id;          // +0x00
    uint         mask;        // +0x04
    float        duration;    // +0x08
    uint         pad0c[8];    // +0x0c
    IRefCounted_s00ec_0a40* object;      // +0x2c
    uint         pad30[2];    // +0x30
};
struct Stimuli_s00ec_0a40 {
    void SetStimulus(Stimulus_s00ec_0a40* s, uint a, uint b, float c, IRefCounted_s00ec_0a40* obj); // 0x00bc9700
    void* Find(uint a, uint b);
    Stimulus_s00ec_0a40* Add(uint a, uint b, float c, IRefCounted_s00ec_0a40* obj);

    Stimulus_s00ec_0a40 slot[8];         // +0x000
    uint     mMask0;          // +0x1c0
    uint     mMask1;          // +0x1c4
};
extern void (*g_0168b54c)(void*);   // 0x0168b54c  stimulus-set callback
// ---- items of slice s00ec0a40 end

// @ 0x00bc9700
void Stimuli::SetStimulus(Stimulus* s, uint32_t a, uint32_t b, float c, IRefCounted* obj)
{
	IRefCounted* newObj = obj;
	mMask0 |= a;
	mMask1 |= b;
	s->id = a;
	s->mask = b;
	s->duration = c;
	IRefCounted* old = s->object;
	if (newObj != old)
	{
		if (newObj)
			newObj->AddRef();
		s->object = newObj;
		if (old)
			old->Release();
	}
	if (g_0168B54C)
		g_0168B54C(s);
}

// @ 0x00bc9770
void Stimuli::ClearStimulus(Stimulus* s)
{
	uint32_t id = s->id;
	float zero = 0.0f;
	_ReadWriteBarrier();
	uint32_t mask = s->mask;
	mMask0 &= ~id;
	mMask1 &= ~mask;
	s->id = 0;
	s->mask = 0;
	s->duration = zero;
	_ReadWriteBarrier();
	IRefCounted* old = s->object;
	if (old)
	{
		s->object = 0;
		old->Release();
	}
}

// @ 0x00bc97b0
void Stimuli::ResetStimuli()
{
	mMask0 = 0;
	mMask1 = 0;
	for (uint32_t i = 0; i < 8; i++)
	{
		slot[i].id = 0;
		slot[i].mask = 0;
		slot[i].duration = 0.0f;
		_ReadWriteBarrier();
		IRefCounted* old = slot[i].object;
		if (old)
		{
			slot[i].object = 0;
			old->Release();
		}
	}
}

// @ 0x00bc97f0
Stimulus_s00ec_0a40* Stimuli_s00ec_0a40::Add(uint a, uint b, float c, IRefCounted_s00ec_0a40* obj)
{
    float best = 3.402823466e+38f;
    uint bestIndex = 0xffffffff;
    Stimulus_s00ec_0a40* s = slot;
    for (uint i = 0; i < 8; ++i, ++s)
    {
        if ((s->id | s->mask) == 0)
        {
            best = 0.0f;
            bestIndex = i;
        }
        else if (s->id == a && s->mask == b)
        {
            SetStimulus(s, a, b, c, obj);
            return s;
        }
        else if (s->duration < best)
        {
            best = s->duration;
            bestIndex = i;
        }
    }
    s = &slot[bestIndex];
    mMask0 &= ~s->id;
    mMask0 |= a;
    mMask1 &= ~s->mask;
    mMask1 |= b;
    s->id = a;
    s->mask = b;
    s->duration = c;
    IRefCounted_s00ec_0a40* old = s->object;
    if (obj != old)
    {
        if (obj)
            obj->AddRef();
        s->object = obj;
        if (old)
            old->Release();
    }
    if (g_0168b54c)
        g_0168b54c(s);
    return s;
}

// @ 0x00bc98f0
void Stimuli::ClearAll(uint32_t a, uint32_t b)
{
	if (((a & mMask0) | (b & mMask1)) == 0)
		return;
	for (uint32_t i = 0; i < 8; i++)
	{
		uint32_t id = slot[i].id;
		uint32_t m = slot[i].mask;
		if (((id & a) | (m & b)) != 0)
		{
			mMask0 &= ~id;
			mMask1 &= ~m;
			slot[i].id = 0;
			slot[i].mask = 0;
			slot[i].duration = 0.0f;
			_ReadWriteBarrier();
			IRefCounted* old = slot[i].object;
			if (old)
			{
				slot[i].object = 0;
				old->Release();
			}
		}
	}
}

// @ 0x00d997e0
behavior_stimuli& behavior_stimuli::GetAny()
{
    mStimulusID = 0;
    mField04 = 0;
    mDuration = 0;
    mOffset.x = gStimulusDefaultVec.x;
    mOffset.y = gStimulusDefaultVec.y;
    mOffset.z = gStimulusDefaultVec.z;
    mField18 = 0;
    mField1c = 0;
    mField20 = 0;
    mf24 = 0.0f;
    return *this;
}
