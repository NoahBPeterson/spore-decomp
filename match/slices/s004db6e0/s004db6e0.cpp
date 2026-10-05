// w1g1 slice s004db6e0 -- SP::cSpeciesCheat::Execute (3967 bytes, /Od /Ob1)
//
// A very large /Od cheat-command handler: it parses the "species_query" arguments
// (min/max constraint list via FunctionalMatch::Constraint), resolves the object
// template DB, then dispatches sub-commands (dumpFull / dump / speciesDump) that
// either print parameter ranges or write a species_dump.csv through an
// EA::IO::FileStream.  The body is dominated by inlined EASTL string/vector
// temporaries whose /Od frame slots are assigned by the compiler's name hash, so
// it is recorded here as a compilable skeleton (see partial.txt).

typedef unsigned int uint32_t;

namespace SP {

struct cSpeciesCheat {
    char pad[0x10];                 // base cCommandStateT<...>, size 0x10
    void Execute(void* pArguments); // __thiscall, virtual override
};

// @ 0x004db6e0
void cSpeciesCheat::Execute(void* pArguments)
{
    (void)pArguments;
    // Body not reconstructed in budget: it is a >3.8 KB /Od function built from
    // inlined EASTL basic_string/vector/rbtree temporaries.  Reconstructing it
    // byte-exactly needs the /Od local-name hash for ~50 locals (od_names.py fit)
    // plus the exact inline templates; recorded as partial.
}

} // namespace SP
