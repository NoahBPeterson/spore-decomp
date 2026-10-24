// Slice s00bc8ff0: behaviour-tree style cursor walk (0x00bc8ff0).
// A tree of 0x88-byte nodes (type 0 = leaf, 1 = group with a child array at +0x80/count at +0x7c). The walk keeps one
// 0xAC-byte Frame per depth in the caller's Cursor, calls the node's callback table (fnA on first entry, fnB every visit,
// fnC on exit) and either descends into the child chosen by FUN_00bc8a00 or unwinds on failure; it stops at the first leaf
// that succeeds and records it in the cursor. Reconstructed from the binary; type/field names are descriptive.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"
#include <intrin.h>

struct Node;

// Per-node callback table (node+0x70). All entries are cdecl.
struct Callbacks
{
	int userData;   // +0x00 (copied into the cursor)
	bool (*fnA)(int p4, double t, int p7, int idx, void* rec, void* mask);                  // +0x04 first visit
	bool (*fnB)(int p4, double t, int p7, int idx, void* rec, void* mask, float f1);        // +0x08 every visit
	void (*fnC)(int p4, double t, int p7, void* scratch, Callbacks* self);                  // +0x0c exit
};

struct Node
{
	uint32_t id;                                                     // +0x00
	int      type;                                                   // +0x04 0 leaf, 1 group
	float    (*condFn)(int p4, double t, int p7, void* bufA, void* flagOut, Node* node, void* ctx);   // +0x08
	void     (*failFn)(int p4, double t, int p7, void* bufA, Node* node);                             // +0x0c
	uint32_t flags;                                                  // +0x10
	uint32_t pad14[2];
	float    weight;                                                 // +0x1c
	int      slot;                                                   // +0x20
	int      order;                                                  // +0x24 (-1 until numbered)
	uint32_t pad28[0x12];
	Callbacks* cb;                                                   // +0x70
	int      defaultIdx;                                             // +0x74
	int      kind;                                                   // +0x78
	uint32_t count;                                                  // +0x7c
	Node*    children;                                               // +0x80 (0x88-byte entries)
	uint32_t pad84;
};

#pragma pack(push, 4)
struct Frame   // 0xAC bytes, one per tree depth
{
	uint32_t id;         // +0x00
	int      idx;        // +0x04
	int      childIdx;   // +0x08
	uint32_t counter;    // +0x0c
	double   t;          // +0x10
	uint32_t rec1[5];    // +0x18
	uint32_t rec2[32];   // +0x2c
};

struct Cursor
{
	uint32_t id;         // +0x00 result
	Node*    node;       // +0x04
	int      childIdx;   // +0x08
	int      depth;      // +0x0c
	Frame    frames[1];  // +0x10 ...
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Ctx   // packed scratch record shared with the helpers (0x59 bytes)
{
	Node*     node;       // +0x00
	int       a;          // +0x04
	uint8_t   b;          // +0x08
	uint32_t  c9;         // +0x09
	uint32_t  cD;         // +0x0d
	uint32_t  c11;        // +0x11 (child chosen by the selector)
	uint32_t  rec[5];     // +0x15
	uint32_t  prev;       // +0x29
	int       depth;      // +0x2d
	int       p4;         // +0x31
	double    t;          // +0x35
	int       p6;         // +0x3d
	int       p7;         // +0x41
	int       p8;         // +0x45
	void*     rng;        // +0x49
	void*     bufA;       // +0x4d
	void*     bufB;       // +0x51
	Callbacks* active;    // +0x55
};
#pragma pack(pop)

union FlagWord
{
	uint32_t word;
	uint8_t  flag;
};

struct RandomMersenneTwister
{
	uint32_t mState[0x9c8 / 4];
	RandomMersenneTwister(uint32_t seed);   // 0x00936300 (seeds the generator, ret 4)
};

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
extern RandomMersenneTwister g_0168AB80;   // 0x0168AB80 shared generator
extern uint32_t g_0168B548;                // 0x0168B548 its init guard (bit 0)

int   __cdecl AssignOrder(Node* node, int* counter, uint32_t* maxChildren);                                  // 0x00bc8810
void  __cdecl ResetFrames(int p4, double t, int p7, Node* node, Frame* frame);                                 // 0x00bc85b0
float __cdecl EvalNode(Node* node, int a, int idx, int p4, double t, Ctx* ctx, FlagWord* flagOut);            // 0x00bc8970
void  __cdecl ApplyEval(uint32_t flag, Node* node, Ctx* ctx, int p4, double t);                               // 0x00bc87b0
void  __cdecl SelectChild(Node* node, Ctx* ctx, int p4, double t);                                            // 0x00bc8a00

// @ 0x00bc8ff0
bool __cdecl WalkTree(float f1, double t, Node* node, int p4, Cursor* cur, int p6, int p7, int p8)
{
	if (node->order == -1)
	{
		int counter = 0;
		uint32_t maxChildren = 0;
		AssignOrder(node, &counter, &maxChildren);
	}
	// function-local static RandomMersenneTwister (-1), spelled out with its storage and guard word
	if (!(g_0168B548 & 1))
	{
		g_0168B548 |= 1;
		new (&g_0168AB80) RandomMersenneTwister(0xFFFFFFFF);
	}

	Node* path[7] = { 0, 0, 0, 0, 0, 0, 0 };
	__declspec(align(64)) uint32_t bufA[32];
	uint32_t bufB[32];
	Ctx ctx;
	FlagWord evalFlag;

	ctx.t = t;
	ctx.p7 = p7;
	ctx.p6 = p6;
	ctx.active = 0;
	ctx.bufA = bufA;
	ctx.p8 = p8;
	ctx.bufB = bufB;
	ctx.p4 = p4;
	ctx.rng = &g_0168AB80;

	Frame* fr = &cur->frames[0];
	bool first = (fr->id != node->id);
	uint32_t* rec1 = fr->rec1;
	uint32_t* rec2 = fr->rec2;
	Frame* nextFr = fr + 1;
	bool wasFirst;
	bool popped = false;
	uint32_t last = 0;
	uint32_t justDone;
	int depth = 0;

	for (;;)
	{
		path[depth + 1] = node;
		justDone = 0;

		switch (node->type)
		{
		case 0:
		{
			wasFirst = first;
			if (first)
			{
				fr->id = node->id;
				fr->t = t;
				first = false;
			}
			int idx = fr->idx;
			if (idx == -1)
				idx = node->defaultIdx;
			Callbacks* cb = node->cb;
			bool (__cdecl *fnA)(int, double, int, int, void*, void*) =
				cb ? cb->fnA : 0;
			bool (__cdecl *fnB)(int, double, int, int, void*, void*, float) =
				cb ? cb->fnB : 0;
			bool ok = true;
			if (cb)
			{
				void* mask = ctx.active ? ctx.bufB : 0;
				if (wasFirst && fnA && !fnA(p4, t, p7, idx, rec2, mask))
					ok = false;
				else if (fnB && !fnB(p4, t, p7, idx, rec2, mask, f1))
					ok = false;
			}
			if (ok)
			{
				if (ctx.active && ctx.active->fnC)
					ctx.active->fnC(p4, t, ctx.p7, ctx.bufB, ctx.active);
				ctx.active = 0;
				cur->id = node->id;
				cur->node = node;
				if (node->cb)
				{
					cur->childIdx = node->cb->userData;
					cur->depth = depth + 1;
					return true;
				}
				cur->childIdx = -1;
				cur->depth = depth + 1;
				return true;
			}
			break;
		}
		case 1:
		{
			if (!node->children)
				return true;
			if (!node->count)
				return true;
			wasFirst = first;
			if (first)
			{
				fr->childIdx = -1;
				fr->id = node->id;
				fr->t = t;
				first = false;
			}
			uint32_t savedChild = fr->childIdx;
			bool pass = true;
			if (popped)
			{
				fr->counter = fr->counter + 1;
				if (savedChild < node->count)
					ResetFrames(p4, t, p7, &node->children[savedChild], nextFr);
				fr->childIdx = -1;
				if (fr->counter > node->count)
				{
					if (ctx.active && ctx.active->fnC)
						ctx.active->fnC(p4, t, ctx.p7, ctx.bufB, ctx.active);
					return false;
				}
				popped = false;
				if (node->flags & 1)
				{
					ctx.c9 = 0xFFFFFFFF;
					ctx.cD = 0xFFFFFFFF;
					ctx.c11 = 0xFFFFFFFF;
					ctx.prev = 0;
					ctx.depth = depth;
					evalFlag.flag = 0;
					float r = EvalNode(node, 0, -1, p4, t, &ctx, &evalFlag);
					if (r > 0.0f)
					{
						ApplyEval(evalFlag.word, node, &ctx, p4, t);
					}
					else
					{
						if (evalFlag.flag && node->failFn)
							node->failFn(p4, t, ctx.p7, ctx.bufA, node);
						pass = false;
					}
				}
			}
			else
			{
				fr->counter = 0;
			}

			if (pass)
			{
				Callbacks* cb = node->cb;
				if (cb)
				{
					int idx = fr->idx;
					if (idx == -1)
						idx = node->defaultIdx;
					void* mask = ctx.active ? ctx.bufB : 0;
					if (wasFirst && cb->fnA && !cb->fnA(p4, t, p7, idx, rec2, mask))
						pass = false;
					else if (cb->fnB && !cb->fnB(p4, t, p7, idx, rec2, mask, f1))
						pass = false;
				}
			}

			if (pass)
			{
				if (ctx.active && ctx.active->fnC)
					ctx.active->fnC(p4, t, ctx.p7, ctx.bufB, ctx.active);
				uint32_t curChild = fr->childIdx;
				ctx.active = 0;
				uint32_t count = node->count;
				ctx.c9 = savedChild;
				ctx.cD = curChild;
				ctx.c11 = 0xFFFFFFFF;
				if (rec1)
				{
					ctx.rec[0] = rec1[0];
					ctx.rec[1] = rec1[1];
					ctx.rec[2] = rec1[2];
					ctx.rec[3] = rec1[3];
					ctx.rec[4] = rec1[4];
				}
				ctx.prev = last;
				ctx.depth = depth;
				SelectChild(node, &ctx, p4, t);
				last = ctx.c11;
				if (last < count && last != curChild)
				{
					if (curChild < count)
						ResetFrames(p4, t, p7, &node->children[curChild], nextFr);
					rec1[0] = ctx.rec[0];
					rec1[1] = ctx.rec[1];
					rec1[2] = ctx.rec[2];
					rec1[3] = ctx.rec[3];
					rec1[4] = ctx.rec[4];
					fr->childIdx = last;
					node = &node->children[last];
					first = true;
					pass = true;
				}
				else if (count <= curChild)
				{
					pass = false;
				}
				else
				{
					node = &node->children[curChild];
				}
				if (pass)
				{
					nextFr = nextFr + 1;
					rec2 = rec2 + sizeof(Frame) / 4;
					rec1 = rec1 + sizeof(Frame) / 4;
					fr = fr + 1;
					depth++;
					last = justDone;
					if (!node)
						return true;
					continue;
				}
			}
			break;
		}
		default:
			return true;
		}

		// failure: leave this node and go back to its parent
		justDone = (uint32_t)node;
		if (ctx.active && ctx.active->fnC)
			ctx.active->fnC(p4, t, ctx.p7, ctx.bufB, ctx.active);
		nextFr = nextFr - 1;
		rec2 = rec2 - sizeof(Frame) / 4;
		rec1 = rec1 - sizeof(Frame) / 4;
		fr = fr - 1;
		node = path[depth];
		depth--;
		ctx.active = 0;
		popped = true;
		last = justDone;
		if (!node)
			return true;
	}
}

// ---------------------------------------------------------------------------
// Behaviour-state helpers (0x00bc9700 .. 0x00bc9fe0).  These are methods of a
// few related state containers; every struct below mirrors the retail field
// offsets and names the fields the code touches.
// ---------------------------------------------------------------------------

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

// 8 stimulus slots of 0x38 bytes; active-bit masks follow the array.
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

// @ 0x00bc9980
uint32_t* Stimuli::UpdateStimuli(float dt)
{
	float zero = 0.0f;
	for (uint32_t i = 0; i < 8; i++)
	{
		Stimulus* s = &slot[i];
		uint32_t id = s->id;
		_ReadWriteBarrier();
		uint32_t m = s->mask;
		if ((id | m) != 0)
		{
			float d = s->duration - dt;
			s->duration = d;
			if (d > zero)
				continue;
			mMask1 &= ~m;
			mMask0 &= ~id;
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
			zero = 0.0f;
		}
	}
	return &mMask0;
}

// 8 records of 0x1c bytes: id/time/object are the live fields, field8 is the
// caller's owner tag.
struct Rec1c
{
	uint32_t     id;         // +0x00
	float        time;       // +0x04
	uint32_t     field8;     // +0x08
	uint32_t     pad0c[3];   // +0x0c
	IRefCounted* object;     // +0x18
};

struct State1c
{
	State1c* Reset();
	void ReleaseObjects();
	void Update(float dt);
	Rec1c* Add(uint32_t id, float duration, IRefCounted* obj, uint32_t field8);
	void ClearMask(uint32_t mask_);
	bool Has(uint32_t mask_);

	uint32_t mask;           // +0x00
	Rec1c    rec[8];         // +0x04
};

typedef void (__cdecl *ActionFn)(void* self);

// 8 records of 0x44 bytes followed by a small tail.
struct Rec44
{
	uint32_t pad00[8];       // +0x00 .. +0x1f
	uint16_t kind;           // +0x20
	uint16_t pad22;          // +0x22
	int32_t  state;          // +0x24
	int32_t  sub;            // +0x28
	float    f0c;            // +0x2c
	uint32_t a10;            // +0x30
	ActionFn callback;       // +0x34
	uint32_t a18;            // +0x38
	IRefCounted* ptr1c;      // +0x3c
	IRefCounted* ptr20;      // +0x40
};

struct State44
{
	Rec44* SetupAction(float f, uint32_t a, ActionFn cb, uint32_t c, uint32_t unused);
	void ReleaseAction();
	State44* Reset(uint32_t v);
	void ReleaseAll();
	void ClearAll();
	Rec44* Find(uint32_t key);

	Rec44    rec[8];         // +0x00 .. +0x21f
	uint32_t vals[3];        // +0x220
	uint32_t flag;           // +0x22c
};

struct Entry
{
	uint32_t id;             // +0x00
	uint32_t a;              // +0x04
	uint32_t b;              // +0x08
};

struct EntryState
{
	uint32_t CurrentId();
	bool SetCurrent(uint32_t id);

	uint8_t  pad00[0x14];    // +0x00
	int32_t  current;        // +0x14
	uint32_t count;          // +0x18
	uint8_t  pad1c[8];       // +0x1c
	Entry    entries[8];     // +0x24
};

union FloatBits
{
	float    f;
	uint32_t u;
};

struct FloatArray
{
	float* At(int i);
	void Set3(int i, const float* v);
	float Get(int i);
	void Set(int i, float v);
	void SetWord(int i, uint32_t v);

	uint8_t pad[0x1a4];      // +0x000
	FloatBits vals[64];      // +0x1a4
};

struct IntArray
{
	void Set(int i, uint32_t v);

	uint8_t  pad[0x220];     // +0x000
	uint32_t vals[64];       // +0x220
};

extern const float g_0146697C;   // 0x0146697c (FLT_MAX)

// @ 0x00bc9a00
bool State1c::Has(uint32_t mask_)
{
	if ((mask & mask_) == 0)
		return false;
	for (uint32_t i = 0; i < 8; i++)
		if (rec[i].id & mask_)
			return true;
	return false;
}

// @ 0x00bc9a30
void IntArray::Set(int i, uint32_t v)
{
	vals[i] = v;
}

// @ 0x00bc9a50
Rec44* State44::Find(uint32_t key)
{
	Rec44* r = &rec[key >> 16];
	if (r->kind != (uint16_t)key || r->state == -1)
		return 0;
	return r;
}

// @ 0x00bc9b10
uint32_t EntryState::CurrentId()
{
	return entries[current].id;
}

// @ 0x00bc9b20
bool EntryState::SetCurrent(uint32_t id)
{
	for (uint32_t i = 0; i < count; i++)
		if (entries[i].id == id)
		{
			current = i;
			return true;
		}
	return false;
}

// @ 0x00bc9b70
float* FloatArray::At(int i)
{
	return &vals[i].f;
}

// @ 0x00bc9b80
void FloatArray::Set3(int i, const float* v)
{
	FloatBits* dst = vals + i;
	const FloatBits* src = (const FloatBits*)v;
	dst[0].u = src[0].u;
	dst[1].u = src[1].u;
	dst[2].u = src[2].u;
}

// @ 0x00bc9bb0
float FloatArray::Get(int i)
{
	return vals[i].f;
}

// @ 0x00bc9bc0
void FloatArray::Set(int i, float v)
{
	vals[i].f = v;
}

// @ 0x00bc9bf0
void FloatArray::SetWord(int i, uint32_t v)
{
	vals[i].u = v;
}

// @ 0x00bc9c10
State1c* State1c::Reset()
{
	mask = 0;
	for (uint32_t i = 0; i < 8; i++)
	{
		rec[i].id = 0;
		rec[i].time = 0.0f;
		rec[i].object = 0;
	}
	return this;
}

// @ 0x00bc9c90
void State1c::ReleaseObjects()
{
	for (int i = 8; i-- > 0; )
	{
		IRefCounted* p = rec[i].object;
		if (p)
			p->Release();
	}
}

// @ 0x00bc9cc0
void State1c::Update(float dt)
{
	if (mask == 0)
		return;
	mask = 0;
	for (uint32_t i = 0; i < 8; i++)
	{
		Rec1c* r = &rec[i];
		if (r->id != 0)
		{
			float t = r->time - dt;
			r->time = t;
			IRefCounted* obj = r->object;
			if (t < 0.0f || (obj && obj->V11()))
			{
				r->id = 0;
				_ReadWriteBarrier();
				IRefCounted* old = r->object;
				if (old)
				{
					r->object = 0;
					old->Release();
				}
			}
			else
				mask |= r->id;
		}
	}
}

// @ 0x00bc9d40
Rec1c* State1c::Add(uint32_t id, float duration, IRefCounted* obj, uint32_t field8)
{
	Rec1c* chosen = 0;
	float best = g_0146697C;
	uint32_t i = 0;
	Rec1c* r = rec;
	do
	{
		if (r->id == 0 || (r->id == id && r->object == obj && r->field8 == field8))
		{
			chosen = r;
			break;
		}
		if (r->time < best)
		{
			chosen = r;
			best = r->time;
		}
		i++;
		r++;
	} while (i < 8);
	mask |= id;
	chosen->id = id;
	chosen->time = duration;
	_ReadWriteBarrier();
	IRefCounted* old = chosen->object;
	if (obj != old)
	{
		if (obj)
			obj->AddRef();
		chosen->object = obj;
		if (old)
			old->Release();
	}
	chosen->field8 = field8;
	return chosen;
}

// @ 0x00bc9de0
void State1c::ClearMask(uint32_t m)
{
	for (uint32_t i = 0; i < 8; i++)
	{
		if (rec[i].id & m)
		{
			rec[i].id = 0;
			_ReadWriteBarrier();
			IRefCounted* old = rec[i].object;
			if (old)
			{
				rec[i].object = 0;
				old->Release();
			}
		}
	}
	mask &= ~m;
}

// @ 0x00bc9e30
Rec44* State44::SetupAction(float f, uint32_t a, ActionFn cb, uint32_t c, uint32_t unused)
{
	Rec44* r = &rec[0];
	r->kind = 0;
	r->state = -1;
	r->sub = -1;
	r->f0c = f;
	r->a10 = a;
	r->callback = cb;
	r->a18 = c;
	r->ptr1c = 0;
	r->ptr20 = 0;
	return r;
}

// @ 0x00bc9e70
void State44::ReleaseAction()
{
	Rec44* r = &rec[0];
	IRefCounted* p = r->ptr20;
	if (p)
		p->Release();
	p = r->ptr1c;
	if (p)
		p->Release();
}

static void InitRec44(Rec44* r, uint32_t none)
{
	r->kind = 0;
	r->state = none;
	r->sub = none;
	r->ptr1c = 0;
	r->ptr20 = 0;
}

// @ 0x00bc9ea0
State44* State44::Reset(uint32_t v)
{
	uint32_t none = (uint32_t)-1;
	InitRec44(&rec[0], none);
	InitRec44(&rec[1], none);
	InitRec44(&rec[2], none);
	InitRec44(&rec[3], none);
	InitRec44(&rec[4], none);
	InitRec44(&rec[5], none);
	InitRec44(&rec[6], none);
	InitRec44(&rec[7], none);
	flag = 0;
	vals[0] = v;
	return this;
}

// @ 0x00bc9fa0
void State44::ReleaseAll()
{
	for (int i = 8; i-- > 0; )
	{
		IRefCounted* p = rec[i].ptr20;
		if (p)
			p->Release();
		p = rec[i].ptr1c;
		if (p)
			p->Release();
	}
}

// @ 0x00bc9fe0
void State44::ClearAll()
{
	for (uint32_t i = 0; i < 8; i++)
	{
		Rec44* r = &rec[i];
		if (r->state != -1)
		{
			if (r->callback)
				r->callback(r);
			r->state = -1;
			_ReadWriteBarrier();
			IRefCounted* old = r->ptr1c;
			if (old)
			{
				r->ptr1c = 0;
				old->Release();
			}
			old = r->ptr20;
			if (old)
			{
				r->ptr20 = 0;
				old->Release();
			}
		}
	}
	flag = 0;
}
