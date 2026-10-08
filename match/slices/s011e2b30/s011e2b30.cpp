// Slice s011e2b30 -- RenderWare 4 core (rw::core::arena): the open-addressing hash map the arena's
// fixup/unfix context uses to look up pointers. Built with VC .NET 2003 like the rest of the RW4 core.
// Module flags: /vc71 /O2 /MD /Gy /TP

unsigned int rw_HashUInt(unsigned int value, unsigned int seed);   // 0x011e4540
extern unsigned int g_rwHashSeed;                                   // 0x014f64ac (FNV offset basis 0x811c9dc5)

// Table entry: key (0xffffffff = empty slot) and its value.
struct RwHashEntry
{
	unsigned int key;
	unsigned int value;
};

// Position in the table, filled through an explicit out parameter (a by-value return gives a
// different prologue).
struct RwHashIterator
{
	unsigned int index;
	unsigned int size;
	RwHashIterator& operator++() { if (++index == size) index = 0; return *this; }
};

// What find() hands back: the entry (or end when the key is absent) and the end of the table.
struct RwHashEntryRange
{
	RwHashEntry* entry;
	RwHashEntry* end;
};

struct RwHashMap
{
	RwHashEntry* mTable;
	unsigned int mSize;    // slots
	unsigned int mCount;   // occupied slots
	void Find(RwHashIterator& out, const unsigned int& key) const;
	void FindEntry(RwHashEntryRange& out, const unsigned int& key) const;
	void EraseAt(RwHashIterator it);
};

// @ 0x011e2b30
void RwHashMap::Find(RwHashIterator& out, const unsigned int& key) const
{
	unsigned int n = mSize;
	unsigned int i = rw_HashUInt(key, g_rwHashSeed) % n;
	unsigned int k = mTable[i].key;
	while (key != k && k != 0xffffffffu)
	{
		if (++i == n)
			i = 0;
		k = mTable[i].key;
	}
	out.size = n;
	out.index = i;
}

// @ 0x011e3a60
// Find() stops at the key's slot or at the first empty slot; only the former is a hit.
void RwHashMap::FindEntry(RwHashEntryRange& out, const unsigned int& key) const
{
	RwHashIterator it;
	Find(it, key);
	RwHashEntry* e = &mTable[it.index];
	if (key == e->key)
	{
		out.end = &mTable[mSize];
		out.entry = e;
		return;
	}
	RwHashEntry* end = &mTable[mSize];
	out.end = end;
	out.entry = end;
}

// @ 0x011e2b90
// Backward-shift deletion: `it` is the hole. Walk the probe run after it and pull back every entry
// whose home slot does not lie cyclically in (hole, cur], so lookups never stop early at the hole.
void RwHashMap::EraseAt(RwHashIterator it)
{
	RwHashIterator start = it;
	RwHashIterator cur = it;
	for (;;)
	{
		++cur;
		if (cur.index == start.index)
			break;
		RwHashEntry* e = mTable + cur.index;
		if (e->key == 0xffffffffu)
			break;
		unsigned int n = mSize;
		unsigned int home = rw_HashUInt(e->key, g_rwHashSeed) % n;
		RwHashIterator next = it;
		++next;
		if (next.index <= cur.index)
		{
			if (next.index <= home && home <= cur.index)
				continue;
		}
		else if (next.index <= home || home <= cur.index)
			continue;
		mTable[it.index] = mTable[cur.index];
		it = cur;
	}
	mTable[it.index].key = 0xffffffffu;
	mTable[it.index].value = 0;
	--mCount;
}
