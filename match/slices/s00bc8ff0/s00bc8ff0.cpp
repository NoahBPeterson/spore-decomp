// Slice s00bc8ff0: behaviour-tree style cursor walk (0x00bc8ff0).
// A tree of 0x88-byte nodes (type 0 = leaf, 1 = group with a child array at +0x80/count at +0x7c). The walk keeps one
// 0xAC-byte Frame per depth in the caller's Cursor, calls the node's callback table (fnA on first entry, fnB every visit,
// fnC on exit) and either descends into the child chosen by FUN_00bc8a00 or unwinds on failure; it stops at the first leaf
// that succeeds and records it in the cursor. Reconstructed from the binary; type/field names are descriptive.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

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
			bool ok = true;
			if (cb)
			{
				void* mask = ctx.active ? ctx.bufB : 0;
				if (wasFirst && cb->fnA && !cb->fnA(p4, t, p7, idx, rec2, mask))
					ok = false;
				else if (cb->fnB && !cb->fnB(p4, t, p7, idx, rec2, mask, f1))
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
