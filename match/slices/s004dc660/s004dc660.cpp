// w1g1 slice s004dc660 -- cSpeciesCheat::GetFullPath and the cPlantSummarizer /
// cSpeciesSummarizer functional-match glue around 0x4dc660-0x4dd05f.
//
// Region is unoptimized: /Od /Ob1 /MD /Gy /TP /arch:SSE (frame pointer, this spilled
// to [ebp-4], SSE scalar float copies; no C++ EH frame).

typedef unsigned int uint32_t;

namespace SP {

struct cSpeciesCheat {
    char pad[0x10];
    void GetFullPath(void* key, void* out); // @ 0x004dc660
};

struct cPlantSummarizer {
    char pad[0x10];
    int GetStaticType();                    // @ 0x004dc730
    int GetResType(int);                    // @ 0x004dc740
    bool ExtractParameters(int* desc, void* out); // @ 0x004dc760
};

struct cSpeciesSummarizer {
    char pad[0x10];
    int GetStaticType();                    // @ 0x004dc920
    int GetResType(int);                    // @ 0x004dc930
    bool ExtractParameters(int* desc, void* out); // @ 0x004dc950
};

struct cSPEditorSpeciesManager {
    char pad[0x100];
    void Teardown();                        // @ 0x004dcaa0
    bool HandleMessage(int msgId, void* payload); // @ 0x004dcee0
};

} // namespace SP

extern int g_plantStaticType;   // DAT_015d9670
extern int g_speciesStaticType; // DAT_015d9674

// @ 0x004dc730
int SP::cPlantSummarizer::GetStaticType()
{
    return g_plantStaticType;
}

// @ 0x004dc740
int SP::cPlantSummarizer::GetResType(int p)
{
    if (p == 0)
        return 0x438f6347;
    return -1;
}

// @ 0x004dc920
int SP::cSpeciesSummarizer::GetStaticType()
{
    return g_speciesStaticType;
}

// @ 0x004dc930
int SP::cSpeciesSummarizer::GetResType(int p)
{
    if (p == 0)
        return 0x2b978c46;
    return -1;
}

// @ 0x004dc660
// SP::cSpeciesCheat::GetFullPath(void* key, WString* out) -- resolves the resource
// path (manager vcall +0x7c) and display name (vcall +0x58 / +0x28) and formats
// L"%ls%ls" into out.  Skeleton.
void SP::cSpeciesCheat::GetFullPath(void* key, void* out)
{
    (void)key; (void)out;
}

// @ 0x004dc760
// SP::cPlantSummarizer::ExtractParameters(int* desc, void* out).  Skeleton.
bool SP::cPlantSummarizer::ExtractParameters(int* desc, void* out)
{
    (void)desc; (void)out;
    return false;
}

// @ 0x004dc950
// SP::cSpeciesSummarizer::ExtractParameters(int* desc, void* out).  Skeleton.
bool SP::cSpeciesSummarizer::ExtractParameters(int* desc, void* out)
{
    (void)desc; (void)out;
    return false;
}

// @ 0x004dcaa0
// 1082-byte /Od teardown of the species-manager maps (ResourceKey ->
// cSpeciesProfile*).  Skeleton.
void SP::cSPEditorSpeciesManager::Teardown()
{
}

// @ 0x004dcee0
// SP::cSPEditorSpeciesManager::HandleMessage(int msgId, void* payload).  Skeleton.
bool SP::cSPEditorSpeciesManager::HandleMessage(int msgId, void* payload)
{
    (void)msgId; (void)payload;
    return false;
}
