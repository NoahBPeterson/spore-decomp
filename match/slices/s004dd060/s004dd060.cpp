// w1g1 slice s004dd060 -- SP::cSPEditorSpeciesManager::ReloadTuning.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
//
// 8809-byte /Od function: reloads the species tuning tables, walks every model
// type, builds/updates species profiles and repopulates the manager's two
// ResourceKey -> cSpeciesProfile* hash maps.  Reconstructing it byte-exactly
// requires the exact /Od local-name hash for well over a hundred locals plus
// the inlined EASTL rbtree/hashtable/vector templates, so it is recorded here
// as a compilable skeleton (see partial.txt).

typedef unsigned int uint32_t;

namespace SP {

struct cSPEditorSpeciesManager {
    char pad[0x100];
    void ReloadTuning(); // @ 0x004dd060
};

} // namespace SP

// @ 0x004dd060
void SP::cSPEditorSpeciesManager::ReloadTuning()
{
    // Body not reconstructed in budget.
}
