// Linear (bump) allocator helper and the "baker" cheat command (Baker system
// management). This module was built WITHOUT optimization:
// compile with /Od /Ob1 /MD /Gy /EHsc /TP.

// ---------------------------------------------------------------------------
// Linear arena: hands out 8-byte aligned chunks from [mpCurrent, mpEnd).
// ---------------------------------------------------------------------------
struct LinearAllocator {
    void* mpVTable;
    void* mpBegin;
    char* mpEnd;      // +0x08
    char* mpCurrent;  // +0x0c
    char* mpLast;     // +0x10

    bool Grow(unsigned int size);  // 0x00928ba0
    void* Allocate(unsigned int size, bool allowGrow);
};

// @ 0x00404480
void* LinearAllocator::Allocate(unsigned int size, bool allowGrow)
{
    size = (size + 7) & ~7u;
    if (allowGrow && (int)(mpEnd - (mpCurrent + size)) < 0) {
        if (!Grow(size))
            return 0;
    }
    void* result = mpCurrent;
    mpCurrent = mpCurrent + size;
    mpLast = mpCurrent;
    return result;
}

// ---------------------------------------------------------------------------
// Baker cheat command
// ---------------------------------------------------------------------------
namespace ArgScript {
    // Generic cheat/command base (ctor at 0x0083c800).
    class ICommand {
    public:
        ICommand();
        virtual void ParseLine(void* line);
        unsigned int mField4;
        unsigned int mField8;
        unsigned int mFieldC;
    };

    class CommandBase : public ICommand {
    public:
        virtual void ParseLine(void* line);
    };

    // Option/flag parser embedded in commands (0xc8 bytes).
    class OptionParser {
    public:
        OptionParser(int mode);                                  // 0x0083a9f0
        void AddOptions(const char* description, ...);           // 0x0083bcd0
        void PrintUsage(const char* name, void* stream);         // 0x0083a2f0
        unsigned int mData[50];
    };
}

class BakerCommand : public ArgScript::CommandBase {
public:
    BakerCommand(void* pBaker);
    virtual void ParseLine(void* line);
    void Description(void* stream);

    void* mpBaker;                      // +0x10
    ArgScript::OptionParser mOptions;   // +0x14
    const char* mKeyFilter;             // +0xdc
    int mLimit;                         // +0xe0
    bool mProcessQueue;                 // +0xe4
    int mFilterGroup;                   // +0xe8
    int mFilterInstance;                // +0xec
};

// @ 0x00404500
BakerCommand::BakerCommand(void* pBaker)
    : mpBaker(pBaker), mOptions(1)
{
    mOptions.AddOptions("Baker system management.",
        "-bake^ [<keyFilter:cstring>]", 0, &mKeyFilter,
            "bake given buildings/vehicles/creatures/etc., switch to model viewer unless noSwitch is specified",
        "-toData^", 6,
            "after baking, promote baked resources to Data, ready for checking in as shipped content",
        "-show^", 0xb, "show result of baking in the model viewer",
        "-force^", 8, "force the baker to perform a full bake, ignoring existing resources on disk",
        "-hires^", 0xe, "bake with high lod model present",
        "-flush^", 1, "flush resman after each bake",
        "-rtts^", 2, "show rtt list after each bake",
        "-limit <n:int>", &mLimit, "bake at most n models",
        "-describeBlocks^", 3,
            "dump text descriptions for all rigblocks to basePath or UserData/Debug/BlockDescriptions.",
        "-filter^ <group:int> <instance:int>", 4, &mFilterGroup, &mFilterInstance,
            "filter by manifest list for describeBlocks cheat",
        "-processQueue^ <bool>", 5, &mProcessQueue, "enable or disable processing of queued items",
        "-dumpProfs^", 7, "dump timing information for bakes completed",
        "-fastDevMode^", 0xc, "enable 'fast' mode until game restart (extremely low quality)",
        0);
}

// @ 0x00404630
void BakerCommand::Description(void* stream)
{
    mOptions.PrintUsage("baker", stream);
}
