// src/game/cmn/collection.cpp.cpp -- migrated from slice(s) s01133a80 by tools/migrate/rewrite.py
// Object file: cmn/collection.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/Collection.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_sys;                        // 0x016e61a8  rw::audio::core::System

// ---- items of slice s01133a80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_sys;                        // 0x016e61a8  rw::audio::core::System
class System
{
public:
	void* Alloc(int size, const char* name, int align, int flags);   // 0x0112c820
	void  Free(void* p, int flags);                                  // 0x0112c850
};
struct CollNode
{
	CollNode* pnext;    // +0x0
	CollNode* pprev;    // +0x4
	int       data;     // +0x8
}; // 0xc
struct CollBlock
{
	CollBlock* pnext;   // +0x0
	int        count;   // +0x4
}; // 0x8, followed by `count` CollNodes
struct Collection
{
	CollBlock* mBlockHead;   // +0x0
	CollBlock* mBlockTail;   // +0x4
	int        mBlockCount;  // +0x8
	CollNode*  mFreeHead;    // +0xc
	CollNode*  mUsedHead;    // +0x10
	int        mSize;        // +0x14
	int        mCapacity;    // +0x18

	void      FUN_01133a80(CollNode* n);       // 0x01133a80
	bool      FUN_01133ad0(int add);           // 0x01133ad0
	bool      FUN_01133bd0(void* userdata);    // 0x01133bd0
	void      FUN_01133c30(int* slot);         // 0x01133c30
};
// ---- items of slice s01133a80 end

// @ 0x01133ad0
bool Collection::FUN_01133ad0(int add)
{
	Collection* c = this;
	int count = c->mCapacity + add;
	CollBlock* blk = (CollBlock*)((System*)g_sys)->Alloc(
		count * 0xc + 8, "rw::audio::core::Collection: NodeBlock", 0x10, 0);
	if (blk == 0)
		return true;
	blk->count = count;
	blk->pnext = 0;
	if (c->mBlockHead == 0)
		c->mBlockHead = blk;
	else
		c->mBlockTail->pnext = blk;
	c->mBlockCount++;
	c->mBlockTail = blk;

	CollNode* n = (CollNode*)((char*)blk + 8);
	for (int i = 0; i < count; i++)
	{
		n->data = 0;
		n->pnext = c->mFreeHead;
		n->pprev = 0;
		if (c->mFreeHead != 0)
			c->mFreeHead->pprev = n;
		c->mFreeHead = n;
		n++;
	}
	c->mCapacity += count;
	return false;
}

// @ 0x01133bd0
bool Collection::FUN_01133bd0(void* userdata)
{
	Collection* c = this;
	bool r = false;
	if (c->mFreeHead == 0)
	{
		r = FUN_01133ad0(c->mSize + 1);
		if (r)
			return r;
	}
	CollNode* n = c->mFreeHead;
	if (n != 0)
	{
		c->mFreeHead = n->pnext;
		if (c->mFreeHead != 0)
			c->mFreeHead->pprev = 0;
	}
	*(void**)((char*)n + 8) = userdata;
	*(void**)userdata = n;
	n->pnext = c->mUsedHead;
	n->pprev = 0;
	if (c->mUsedHead != 0)
		c->mUsedHead->pprev = n;
	c->mUsedHead = n;
	c->mSize++;
	return r;
}

// @ 0x01133c90
bool __fastcall FUN_01133c90(Collection* c)
{
	CollBlock* blk = c->mBlockHead;
	bool r = false;
	if (blk != 0 && blk->pnext != 0 && blk->count <= c->mCapacity - c->mSize)
	{
		int i = 0;
		CollNode* n = (CollNode*)((char*)blk + 8);
		CollNode* start = n;
		if (blk->count > 0)
		{
			for (;;)
			{
				if (*(int*)((char*)n + 8) == 0)   // n[1].data == 0 => free?
				{
					if (n == c->mFreeHead)
						c->mFreeHead = n->pnext;
					if (n->pprev != 0)
						n->pprev->pnext = n->pnext;
					if (n->pnext != 0)
						n->pnext->pprev = n->pprev;
				}
				i++;
				n = (CollNode*)((char*)n + 0xc);
				if (i >= blk->count)
					break;
			}
		}
		int local4 = 0;
		if (blk->count > 0)
		{
			do
			{
				CollNode* p = *(CollNode**)((char*)start + 8); // start[1].pnext (userdata slot)
				if (p != 0)
				{
					CollNode* q = p->pnext;
					p->pnext = 0;
					q->data = 0;
					if (q == c->mUsedHead)
						c->mUsedHead = q->pnext;
					if (q->pprev != 0)
						q->pprev->pnext = q->pnext;
					if (q->pnext != 0)
						q->pnext->pprev = q->pprev;
					q->pnext = c->mFreeHead;
					q->pprev = 0;
					if (c->mFreeHead != 0)
						c->mFreeHead->pprev = q;
					c->mFreeHead = q;
					c->mSize--;
					if (start == c->mFreeHead)
						c->mFreeHead = start->pnext;
					if (start->pprev != 0)
						start->pprev->pnext = start->pnext;
					if (start->pnext != 0)
						start->pnext->pprev = start->pprev;
					if (c->mFreeHead == 0)
					{
						if ((char)c->FUN_01133ad0(c->mSize + 1) != 0)
							goto next;
					}
					{
						CollNode* f = c->mFreeHead;
						if (f != 0)
						{
							c->mFreeHead = f->pnext;
							if (c->mFreeHead != 0)
								c->mFreeHead->pprev = 0;
						}
						*(CollNode**)((char*)f + 8) = p;
						p->pnext = f;
						f->pnext = c->mUsedHead;
						f->pprev = 0;
						if (c->mUsedHead != 0)
							c->mUsedHead->pprev = f;
						c->mUsedHead = f;
						c->mSize++;
					}
				}
			next:
				local4++;
				start = (CollNode*)((char*)start + 0xc);
			} while (local4 < blk->count);
		}
		if (c->mBlockHead != 0)
		{
			c->mBlockHead = c->mBlockHead->pnext;
			if (c->mBlockHead == 0)
				c->mBlockTail = 0;
			c->mBlockCount--;
		}
		c->mCapacity -= blk->count;
		((System*)g_sys)->Free(blk, 0);
		r = 1;
	}
	return r;
}
