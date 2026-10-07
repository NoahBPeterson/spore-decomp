// Slice s00fc8450: rw::movie::EventLogger (RenderWare movie event logger).
// Region flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: the AsyncOp local gets no EH frame).
#include "types.h"

namespace rw {
namespace core {
namespace filesys {

// rwcore/filesys/asyncop.h (b5-decomp layout, size 0x48).
struct AsyncOp
{
    uint8_t mData[0x48];

    AsyncOp();                                                          // 0x11e84f0
    ~AsyncOp();                                                         // 0x11e8530
    int32_t Open(const char* lpcPath, uint32_t luFlags, void* lpfnComplete,
                 uint32_t luUserData, int32_t liPriority);            // 0x11e8a40
    int32_t Write(void* lpStream, void* lpBuffer, uint64_t lu64Position, uint64_t lu64Count,
                  void* lpfnComplete, uint32_t luUserData, int32_t liPriority); // 0x11e88a0
    int32_t Close(void* lpStream, void* lpfnComplete, uint32_t luUserData,
                  int32_t liPriority);                                  // 0x11e89e0
    void*    GetResultHandle();                                         // 0x11e8770
    uint64_t GetResultSize();                                           // 0x11e87a0
    int32_t  GetStatus(const int32_t* lpbWantWait);                     // 0x11e8740
};

} // namespace filesys
} // namespace core

namespace movie {

class Event
{
public:
    unsigned int mTag;      // +0x0
    char*        mMessage;  // +0x4
};

struct Entry
{
    float  timeStamp;        // +0x00
    Event* event;            // +0x04
    int    eventContext;     // +0x08
    float  timeStart;        // +0x0c
    float  timeStop;         // +0x10
    bool   isDurationEvent;  // +0x14
};

class EventLogger
{
public:
    void*         mAllocator;   // +0x00 EA::Allocator::ICoreAllocator*
    void*         mStopwatch;   // +0x04 rw::core::timer::Stopwatch*
    void*         mMutex;       // +0x08 EA::Thread::Mutex*
    unsigned int  mMaxEntries;  // +0x0c
    Entry*        mEntriesList; // +0x10
    unsigned int  mEntryPos;    // +0x14
    unsigned int  mMaxEvents;   // +0x18
    unsigned int  mEventTag;    // +0x1c
    Event**       mEventList;   // +0x20

    void Dump();

    bool IsDurationEvent(unsigned int tag)
    {
        for (unsigned int i = 0; i < mEntryPos; ++i)
        {
            if (mEntriesList[i].event->mTag == tag)
                return mEntriesList[i].isDurationEvent;
        }
        return false;
    }
};

} // namespace movie
} // namespace rw

extern "C" void   FUN_00c2e4e0(const char* fmt, ...);                         // debug printf
extern "C" int    FUN_011ea790(char* buf, unsigned int n, const char* fmt, ...); // snprintf
extern "C" size_t FUN_011e8c40(const char* s);                                // strlen

static const int32_t kWaitForCompletion = -1;  // 0x149184c

using rw::core::filesys::AsyncOp;

// Echo to the debug console, then append the text to the log file.
#define LOG_LINE(fmt, text)                                                       \
    do {                                                                          \
        FUN_00c2e4e0(fmt, text);                                                  \
        op.Write(handle, (void*)(text), pos, FUN_011e8c40(text), 0, 0, 0);       \
        pos += op.GetResultSize();                                                \
    } while (0)

static const char kDashesNL[] =
    "-------------------------------------------------------------------------\n";
static const char kDashes[] =
    "-------------------------------------------------------------------------";
static const char kHeader[] = "EVENT LOGGER DUMP ----------------------------------";
static const char kCapacity[] = "**Entries log capacity reached.  Increase number of entries**";

// @ 0x00fc8660  rw::movie::EventLogger::Dump
void rw::movie::EventLogger::Dump()
{
    AsyncOp op;
    char buffer[256];

    op.Open("EventLog.txt", 7, 0, 0, 0);
    void* handle = op.GetResultHandle();

    if (mEntryPos >= mMaxEntries)
        FUN_00c2e4e0(kCapacity);

    uint64_t pos = 0;

    // Per-tag statistics.
    for (unsigned int tag = 0; tag < mEventTag; ++tag)
    {
        if (IsDurationEvent(tag))
        {
            LOG_LINE("\n%s", kDashesNL);

            FUN_011ea790(buffer, 0x100, "EventTag %d is a duration event\n", tag);
            LOG_LINE("%s\n", buffer);

            FUN_011ea790(buffer, 0x100, ",%s \n", mEventList[tag]->mMessage);
            LOG_LINE("%s", buffer);

            float minDur = 1000000.0f;
            float maxDur = -1000000.0f;
            float total = 0.0f;
            int   count = 0;
            for (unsigned int j = 0; j < mEntryPos; ++j)
            {
                if (mEntriesList[j].event->mTag == tag)
                {
                    float d = mEntriesList[j].timeStop - mEntriesList[j].timeStart;
                    total += d;
                    if (d < minDur)
                        minDur = d;
                    if (d > maxDur)
                        maxDur = d;
                    ++count;
                }
            }

            FUN_011ea790(buffer, 0x100,
                         "NumberEvents: %5d, TotalDuration: %12.4f ms\nAve: %12.4f ms = %6.2f Hz\n"
                         "Min: %12.4f ms = %6.2f Hz\nMax: %12.4f ms = %6.2f Hz\n",
                         count, (double)total, (double)(total / count),
                         (double)(1000.0f / (total / count)), (double)minDur,
                         (double)(1000.0f / minDur), (double)maxDur, (double)(1000.0f / maxDur));
            LOG_LINE("%s", buffer);

            LOG_LINE("%s", kDashesNL);
        }
        else
        {
            FUN_011ea790(buffer, 0x100, "EventTag %d is not a duration event \n", tag);
            LOG_LINE("%s", buffer);
        }
    }

    LOG_LINE("%s", kHeader);
    LOG_LINE("%s", "Time (ms): \n");

    // Chronological list.
    for (unsigned int i = 0; i < mEntryPos; ++i)
    {
        if (mEntriesList[i].isDurationEvent)
            FUN_011ea790(buffer, 0x100, "<%12.4f : %12.4f> = %12.4f: %s%d\n",
                         (double)mEntriesList[i].timeStart, (double)mEntriesList[i].timeStop,
                         (double)(mEntriesList[i].timeStop - mEntriesList[i].timeStart),
                         mEventList[mEntriesList[i].event->mTag]->mMessage,
                         mEntriesList[i].eventContext);
        else
            FUN_011ea790(buffer, 0x100, "%12.4f: %s%d\n", (double)mEntriesList[i].timeStamp,
                         mEventList[mEntriesList[i].event->mTag]->mMessage,
                         mEntriesList[i].eventContext);
        LOG_LINE("%s", buffer);
    }

    if (mEntryPos >= mMaxEntries)
        LOG_LINE("%s", kCapacity);

    LOG_LINE("%s\n", kHeader);

    // Per-tag entry lists.
    for (unsigned int tag = 0; tag < mEventTag; ++tag)
    {
        LOG_LINE("\n%s", kDashes);

        FUN_011ea790(buffer, 0x100, ",%s \n", mEventList[tag]->mMessage);
        LOG_LINE("%s", buffer);

        for (unsigned int i = 0; i < mEntryPos; ++i)
        {
            if (mEntriesList[i].event->mTag == tag)
            {
                if (mEntriesList[i].isDurationEvent)
                {
                    FUN_011ea790(buffer, 0x100, "%04d, %12.4f -> %12.4f = %12.4f,\n",
                                 mEntriesList[i].eventContext, (double)mEntriesList[i].timeStart,
                                 (double)mEntriesList[i].timeStop,
                                 (double)(mEntriesList[i].timeStop - mEntriesList[i].timeStart));
                    FUN_00c2e4e0("%s", buffer);
                }
                else
                {
                    FUN_011ea790(buffer, 0x100, "%04d, %12.4f,\n", mEntriesList[i].eventContext,
                                 (double)mEntriesList[i].timeStamp);
                    FUN_00c2e4e0("%s", buffer);
                }
                op.Write(handle, buffer, pos, FUN_011e8c40(buffer), 0, 0, 0);
                pos += op.GetResultSize();
            }
        }

        LOG_LINE("%s", kDashes);
    }

    op.Close(handle, 0, 0, 0);
    op.GetStatus(&kWaitForCompletion);
}
