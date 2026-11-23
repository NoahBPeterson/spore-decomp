// Same shape as s00437b00's Tracker::HasRelevantPoints2 (0x00438420); the callee
// here is 0x004d8f10.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS-

// @ 0x004d9030
struct Ctx_004d9030;
struct Tracker_004d9030 {
    bool HasRelevantPoints(Ctx_004d9030* ctx);       // 0x004d8f10
    bool HasRelevantPoints2(Ctx_004d9030* ctx);
};

bool Tracker_004d9030::HasRelevantPoints2(Ctx_004d9030* ctx)
{
    return HasRelevantPoints(ctx);
}
