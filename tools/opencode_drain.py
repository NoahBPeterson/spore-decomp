#!/usr/bin/env python3
"""Watch a brokered opencode wave to completion: re-prompt idle-but-unfinished sessions and
interrupt sessions whose current model call has hung.

usage: opencode_drain.py <group> [--interval S=60] [--cooldown S=300] [--hang S=900] [--max-nudges N=3]
                         [--stall S=7200] [--revive K,K,...] [--once]

Each pass:
  * a range is DONE when its manifest+nonmatching+partial count >= its function count (fix batches, whose
    entries carry "causes": when every target VA is logged in work/match/scratch_<id>_fixlog.txt);
  * a range that is idle, unfinished, has no pending permission request, and whose last assistant
    message is older than --cooldown is re-prompted (nudge) on its per-session alias model;
  * a range that is active but whose open model call has run longer than --hang is interrupted and
    re-prompted;
  * a range that would get a nudge after --max-nudges nudges is logged "ABANDONED r<k> <unsettled VAs>"
    and counted as done (round 3: the Manager session sat idle with 0x8de8e0/0x8de940 neither landed
    nor in leave_in_slice and was nudged for four hours; those VAs go to the fix pass instead).
  * a range whose settled-function count and chk.py byte difference (work/match/chk_scores/) have not moved for --stall
    seconds while unfinished is interrupted and
    logged "STALLED r<k> ..." + ABANDONED (round 5, 2026-10-16: the ealog_imp session kept making model calls on
    one 40-function slice for 7.5 h, so neither the nudge cap nor the per-call hang check fired, the drain never
    completed, and the verify/commit steps queued behind it never ran). 0 disables. The clock starts when the
    drain first sees the range, so a restart grants a fresh window.
  * queue groups ("queue": true, "workers": N; tools/matching/claim.py): range k is worker k, its progress counts the
    slices it has claimed, and it is done only once the queue is empty and its claimed slices are settled. A worker
    that settles more functions after a nudge starts a fresh nudge count (it stops after every few slices; that is
    not a stuck session).
Exits 0 ("DRAIN_COMPLETE") once every range is done or abandoned. Safe to kill and restart: its only
state is work/opencode/drain_<group>.log, from which a restart re-reads the nudge counts and the
abandoned ranges. --revive K,... logs "REVIVED r<k>" for those ranges: a restart then treats them as never
abandoned and with no nudges sent (gold6 on the Runpod pod, 2026-10-24: the stall check abandoned 18 workers at
once, two hours after the drain started, because a supervisor bug had interrupted them every 20 minutes until
then; their claimed slices would otherwise stay held for the rest of the wave).
"""
import argparse, base64, glob, json, os, re, subprocess, sys, time, urllib.error, urllib.parse, urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)


def svc():
    for _ in range(10):
        m = re.search(r"http://[0-9.:]+", subprocess.run(["opencode", "service", "status"], capture_output=True,
                                                         text=True).stdout)
        if m:
            return m.group(0)
        time.sleep(1)
    sys.exit("opencode service not reachable")


url = svc()
_pw = json.load(open(os.path.expanduser("~/.config/opencode/service.json")))["password"]
H = {"Authorization": "Basic " + base64.b64encode(("opencode:" + _pw).encode()).decode(),
     "content-type": "application/json"}
LOC = "location%5Bdirectory%5D=" + urllib.parse.quote(ROOT)


def api(method, path, body=None):
    req = urllib.request.Request(url + path + ("&" if "?" in path else "?") + LOC, method=method, headers=H,
                                 data=json.dumps(body).encode() if body is not None else None)
    try:
        with urllib.request.urlopen(req, timeout=60) as r:
            return json.loads(r.read() or b"{}")
    except urllib.error.HTTPError as e:
        return {"error": e.code, "body": e.read().decode()[:200]}


ap = argparse.ArgumentParser()
ap.add_argument("group")
ap.add_argument("--interval", type=int, default=60)
ap.add_argument("--cooldown", type=int, default=300, help="min seconds idle before re-nudging a range")
ap.add_argument("--hang", type=int, default=900, help="seconds an open model call may run before interrupt")
ap.add_argument("--max-nudges", type=int, default=3, help="nudges per range before it is ABANDONED and counted as done")
ap.add_argument("--stall", type=int, default=7200,
                help="seconds an unfinished range may go without settling another function before it is ABANDONED (0 = off)")
ap.add_argument("--revive", default="", help="comma-separated ranges to un-abandon (nudge count reset), logged REVIVED")
ap.add_argument("--once", action="store_true")
a = ap.parse_args()

GF = W("work/opencode/groups", a.group + ".json")
G = json.load(open(GF))
SESS = G.get("sessions", {})
BATCH = json.load(open(W("work/batches", G["batch"] + ".json")))
QUEUE = bool(G.get("queue"))
NK = int(G["workers"]) if QUEUE else len(G["ranges"])
sys.path.insert(0, W("tools/matching"))
import claim  # noqa: E402
NUDGE = ("Continue your task. Act through tool calls: call the edit/write tool to change files and the shell tool to "
         "compile; do not end your turn with a plan in text. Run .venv/bin/python tools/matching/claim.py %s %%s (it "
         "prints the slice you hold if it is unfinished, else your next slice), finish that slice (source, chk.py, "
         "bookkeeping, run_all), and keep claiming until it prints NO SLICE; then give the final one-line-per-slice "
         "summary. Name every field you touch (docs/matching.md): no raw-offset casts like *(u32*)((char*)p + 0x5fc). "
         "If the slice already has committed functions, keep every one of them and its rows: add yours to the same "
         "file, never rewrite it from scratch (a gold7 rewrite dropped an exact function, 2026-10-24)."
         % G["batch"]) if QUEUE else (
         "Continue your task: check the files already written in your slices and finish the remaining slices, then "
         "give the final one-line-per-slice summary.")
LOG = W("work/opencode", "drain_%s.log" % a.group)


def log(msg):
    line = "%s %s" % (time.strftime("%H:%M:%S"), msg)
    print(line, flush=True)
    open(LOG, "a").write(line + "\n")


def model_of(k):
    wm = G.get("worker_model", {}).get(str(k)) if k is not None else None
    if wm:  # per-worker override, e.g. {"providerID": "openrouter", "id": "dsv41-cheapest"} (gold6, 2026-10-24)
        return wm
    mid = G["model"]
    if G.get("cache_ns") and G.get("provider") == "cheaperinference":
        mid = "%s-c%02d" % (mid, int(k) % int(G["cache_ns"]))
    return {"providerID": G["provider"], "id": mid}


def chk_scores(k):
    """Last chk.py score line (work/match/chk_scores/<slice>.log: time, matched, total differing bytes, functions)
    of each slice range k works on, minus the time: a change means the session is still closing the byte
    difference, so the stall check does not fire although nothing has been recorded yet."""
    if QUEUE:
        ids = [BATCH[i]["id"] for i in claim.held(claim.load_claims(G["batch"]), k)]
    else:
        lo, hi = G["ranges"][k]
        ids = [BATCH[i]["id"] for i in range(lo, hi + 1)]
    out = []
    for sid in ids:
        try:
            with open(W("work/match/chk_scores", sid + ".log"), "rb") as f:
                f.seek(0, 2)
                f.seek(max(0, f.tell() - 200))
                last = f.read().decode(errors="replace").strip().splitlines()[-1].split()[1:]
        except (OSError, IndexError):
            last = None
        out.append((sid, tuple(last) if last else None))
    return tuple(out)


def progress(k, unsettled=None):
    """(functions, settled) of range k; `unsettled` (a list) gets the migration VAs not yet settled, or
    '<slice>:<n> unrecorded' for a slice entry. Queue groups: over worker k's claimed slices, and while the queue still
    has slices the total is raised by one so the worker never counts as done."""
    if QUEUE:
        tot, done, left = claim.worker_progress(G["batch"], BATCH, k, unsettled)
        return tot + (1 if left else 0), done
    lo, hi = G["ranges"][k]
    tot = done = 0
    for i in range(lo, hi + 1):
        sid = BATCH[i]["id"]
        tot += len(BATCH[i]["vas"])
        if BATCH[i].get("module"):
            # migration entry (docs/migration-runbook.md s8a): this entry's VAs in the module's bookkeeping
            want = {v.lower() for v in BATCH[i]["vas"]}
            # a function the session deliberately left in the slice (renames manual leave_in_slice / exclude, with a why) is
            # settled too: rewrite.py keeps the module bookkeeping to the functions its TU defines, so it has no row there
            rp = W("work/migrate", "renames_%s.json" % sid)
            if os.path.exists(rp):
                try:
                    man = json.load(open(rp)).get("manual", {})
                except ValueError:
                    man = {}
                left = {v.lower() for k in ("leave_in_slice", "exclude") for v in man.get(k, {})} & want
                done += len(left)
                want -= left
            seen = set()
            for f in ("manifest.txt", "nonmatching.txt", "partial.txt"):
                p = W("src/game", BATCH[i]["module"], f)
                if not os.path.exists(p):
                    continue
                for l in open(p):
                    parts = l.split("#", 1)[0].split()
                    va = (parts[2] if f == "manifest.txt" and len(parts) > 2 else parts[0] if parts else "").lower()
                    va = va[2:] if va.startswith("0x") else va
                    if va in want:
                        seen.add(va)
            done += len(seen)
            if unsettled is not None:
                unsettled += ["%s:%s" % (sid, v) for v in sorted(want - seen)]
            continue
        if BATCH[i].get("causes"):
            # fix entry (batch rck1 on): its target VAs are already in the slice's bookkeeping, so a target
            # counts as settled once a session logs "<va> <verdict> <note>" in a work/match fix log
            want = {v.lower() for v in BATCH[i]["vas"]}
            seen = want & set(fixlog_vas())
            done += len(seen)
            if unsettled is not None:
                unsettled += ["%s:%s" % (sid, v) for v in sorted(want - seen)]
            continue
        n0 = done
        for f in ("manifest.txt", "nonmatching.txt", "partial.txt"):
            p = W("match/slices", sid, f)
            if not os.path.exists(p):
                continue
            done += sum(1 for l in open(p) if re.match(r"\s*(?:0x)?[0-9a-fA-F]{6,8}\b", l)) if f != "manifest.txt" \
                else sum(1 for l in open(p) if l.strip() and not l.lstrip().startswith("#"))
        if unsettled is not None and done - n0 < len(BATCH[i]["vas"]):
            unsettled.append("%s:%d unrecorded" % (sid, len(BATCH[i]["vas"]) - (done - n0)))
    return tot, done


def fixlog_vas():
    """VA -> verdict over every work/match/scratch_*fixlog*.txt: sessions do not always name the log after the slice
    (rck1 2026-10-18: scratch_65_fixlog.txt, scratch_rck1_40_fixlog.txt), and a fix batch's VAs are unique."""
    out = {}
    for fp in glob.glob(W("work/match", "scratch_*fixlog*.txt")):
        for l in open(fp, errors="replace"):
            parts = l.split()
            if parts:
                va = parts[0].lower()
                va = va[2:] if va.startswith("0x") else va
                out[va] = parts[1].upper() if len(parts) > 1 else ""
    return out


def pending(sid):
    r = api("GET", "/api/session/%s/permission" % sid)
    if "error" in r:
        return False
    return bool(r.get("data"))


_DB = os.path.expanduser("~/.local/share/opencode/opencode.db")


def last_activity(sid):
    """Seconds-since-epoch of the session's newest write (any message row's time_updated), from opencode's
    database; None when it cannot be read. opencode 2.1's message API gives only a turn's start time ("assistant"
    = the turn, which spans every model call and tool run until the session goes idle) and no completion time, so
    "created more than --hang ago" fired on every session that had worked for 15 minutes in one turn: on the Runpod
    wave (2026-10-23) the drain interrupted 18 healthy sessions at 22:29:39 and again at 22:44:40, aborting their
    current calls and burning their nudges."""
    if not os.path.exists(_DB):
        return None
    try:
        import sqlite3
        db = sqlite3.connect("file:%s?mode=ro" % _DB, uri=True, timeout=5)
        r = db.execute("select max(time_updated) from session_message where session_id = ?", (sid,)).fetchone()
        db.close()
        return r[0] / 1000 if r and r[0] else None
    except Exception:
        return None


def last_assistant(sid):
    m = api("GET", "/api/session/%s/message?limit=3" % sid).get("data", [])
    for x in m:
        if x.get("type") == "assistant" or x.get("role") == "assistant":
            return x
    return None


nudged_at = {}   # sid -> (monotonic time, done-count when nudged)
nudge_done = {}  # range -> done-count at its last nudge (queue groups reset the nudge count when it grows)
moved = {}       # range -> (time the settled count last changed, that count)
nudges = {}      # range -> nudges sent (re-read from the log on restart)
toolfixed = set()  # message ids already re-prompted for a tool call written as text
toolfix_n = {}     # range -> text tool calls seen
TOOL_TEXT = re.compile(r"DSML|<parameter name=|<invoke name=|<tool_call>")
abandoned = set()
if os.path.exists(LOG):
    for l in open(LOG):
        m = re.search(r" (nudge|ABANDONED|REVIVED) r(\d+)\b", l)
        if m and m.group(1) == "nudge":
            nudges[int(m.group(2))] = nudges.get(int(m.group(2)), 0) + 1
        elif m and m.group(1) == "REVIVED":
            abandoned.discard(int(m.group(2)))
            nudges.pop(int(m.group(2)), None)
        elif m:
            abandoned.add(int(m.group(2)))
for k in (int(x.strip().lstrip("r")) for x in a.revive.split(",") if x.strip()):
    abandoned.discard(k)
    nudges.pop(k, None)
    log("REVIVED r%d" % k)
loops = 0
while True:
    loops += 1
    if QUEUE:  # a supervisor may add workers (replacing an abandoned one) while the drain runs
        G = json.load(open(GF))
        SESS = G.get("sessions", {})
        NK = int(G["workers"])
        # entries may be appended to a running queue batch (part1's 3 late FAILs, 2026-10-24: a claim of index 902
        # against the 901 entries read at start crashed the drain)
        BATCH = json.load(open(W("work/batches", G["batch"] + ".json")))
    now = time.time()
    active = api("GET", "/api/session/active").get("data", {})
    if isinstance(active, list):
        active = {s.get("id", s) if isinstance(s, dict) else s: 1 for s in active}
    finished = busy = 0
    for k in range(NK):
        sid = SESS.get(str(k))
        if not sid:
            continue
        if k in abandoned:
            finished += 1
            continue
        tot, done = progress(k)
        if done >= tot:
            finished += 1
            continue
        sig = (done, chk_scores(k))
        if moved.get(k, (0, None))[1] != sig:
            moved[k] = (now, sig)
        if a.stall and now - moved[k][0] > a.stall:
            uns = []
            progress(k, uns)
            api("POST", "/api/session/%s/interrupt" % sid, {})
            log("STALLED r%d %s (done %d/%d unchanged for %.0fs), interrupted" % (k, sid, done, tot, now - moved[k][0]))
            log("ABANDONED r%d %s (done %d/%d after stall) unsettled: %s" % (k, sid, done, tot, " ".join(uns)))
            abandoned.add(k)
            finished += 1
            continue
        if pending(sid):
            busy += 1
            continue
        last = last_assistant(sid)
        t = (last or {}).get("time", {})
        created = (t.get("created") or 0) / 1000
        completed = (t.get("completed") or 0) / 1000
        act = last_activity(sid)
        is_active = sid in active
        if is_active:
            quiet = (now - act) if act else ((now - created) if created and not completed else 0)
            if quiet > a.hang:
                log("unhang r%d %s (no activity for %.0fs)" % (k, sid, quiet))
                api("POST", "/api/session/%s/interrupt" % sid, {})
                api("POST", "/api/session/%s/prompt" % sid, {"text": "Your previous model call hung and was "
                    "interrupted. Continue your task from the files already written in your slices.",
                    "model": model_of(k)})
                nudged_at[sid] = (now, done)
            else:
                busy += 1
            continue
        # idle and unfinished
        # A turn that ended on tool-call markup written as text (the provider's parser did not turn it into a call):
        # re-prompt at once, without waiting the cooldown or spending a nudge (CheaperInference, 2026-10-24: 0.47% of
        # responses, e.g. '<parameter name="shell"> <｜DSML｜ parameter name="command" ...', abandoned 6 gold7 workers)
        txt = " ".join(c.get("text", "") for c in ((last or {}).get("content") or []) if isinstance(c, dict))
        if last and last.get("id") not in toolfixed and TOOL_TEXT.search(txt):
            toolfixed.add(last.get("id"))
            toolfix_n[k] = toolfix_n.get(k, 0) + 1
            if toolfix_n[k] > 2 and model_of(k).get("providerID") == "cheaperinference" and G.get("fallback", True):
                # the session keeps copying the leaked markup from its own history: move it to OpenRouter (0 leaks
                # in 2,079 responses of the same model), via the group's worker_model override
                Gm = json.load(open(GF))
                Gm.setdefault("worker_model", {})[str(k)] = {"providerID": "openrouter", "id": "dsv41-cheapest"}
                json.dump(Gm, open(GF + ".tmp", "w"), indent=1)
                os.replace(GF + ".tmp", GF)
                G = Gm
                api("POST", "/api/session/%s/model" % sid, {"model": model_of(k)})
                log("toolfix r%d %s: third text tool call, moved to openrouter" % (k, sid))
            log("toolfix r%d %s (tool call came back as text)" % (k, sid))
            api("POST", "/api/session/%s/prompt" % sid, {"text": "Your last tool call came back as plain text, so it "
                "was not executed. Call the tool again through the tool interface (no markup in your reply text), "
                "then continue your task.", "model": model_of(k)})
            nudged_at[sid] = (now, done)
            busy += 1
            continue
        since = now - (act or completed or created or 0)
        prev = nudged_at.get(sid)
        if prev and prev[1] == done and now - prev[0] < a.cooldown:
            continue
        if since < a.cooldown:
            continue
        if QUEUE and done > nudge_done.get(k, done):
            nudges[k] = 0
        if nudges.get(k, 0) >= a.max_nudges:
            uns = []
            progress(k, uns)
            log("ABANDONED r%d %s (done %d/%d after %d nudges) unsettled: %s" % (k, sid, done, tot, nudges[k], " ".join(uns)))
            abandoned.add(k)
            finished += 1
            continue
        nudges[k] = nudges.get(k, 0) + 1
        nudge_done[k] = done
        log("nudge r%d %s (done %d/%d, idle %.0fs, nudge %d of %d)" % (k, sid, done, tot, since, nudges[k], a.max_nudges))
        api("POST", "/api/session/%s/model" % sid, {"model": model_of(k)})
        r = api("POST", "/api/session/%s/prompt" % sid, {"text": NUDGE % k if QUEUE else NUDGE, "model": model_of(k)})
        if "error" in r:
            log("  nudge failed r%d: %s" % (k, r))
        nudged_at[sid] = (now, done)
    log("pass %d: %d/%d ranges done (%d abandoned), %d busy/working" % (loops, finished, NK, len(abandoned), busy))
    if finished == NK:
        log("DRAIN_COMPLETE")
        sys.exit(0)
    if a.once:
        sys.exit(0)
    time.sleep(a.interval)
