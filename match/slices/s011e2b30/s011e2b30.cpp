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
};

struct RwHashMap
{
	RwHashEntry* mTable;
	unsigned int mSize;
	void Find(RwHashIterator& out, const unsigned int& key) const;
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
