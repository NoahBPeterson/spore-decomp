// Slice s004d2200: SP::cSPEditorSpeciesManager::GetMatchingCreatureKeys.
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
// The function builds a FunctionalMatch::Constraint and queries the ObjectTemplateDB.
// Complete reconstruction needs the Constraint/Database layouts, which were not
// recovered in this pass; skeleton only (partial.txt).
#include "types.h"
#pragma pack(push, 4)

// @ 0x004D2200  SP::cSPEditorSpeciesManager::GetMatchingCreatureKeys
int GetMatchingCreatureKeys(uint32_t* self, uint32_t manager, int maxCount, uint32_t filter,
                            char useAll, uint32_t* outParams)
{
    (void)self; (void)manager; (void)maxCount; (void)filter; (void)useAll; (void)outParams;
    return 0;
}
