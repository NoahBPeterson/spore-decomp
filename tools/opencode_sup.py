#!/usr/bin/env python3
"""Supervisor helper for brokered opencode matching waves (one group = one batch + a pool of sessions).

usage: opencode_sup.py <group> <command> [args]
  pending [WAIT]          wait up to WAIT s (default 90) for permission requests from this group's sessions; print each
                          as "<sid>:<rid> <title> <action> :: <resources>" (shell commands shown in full as "FULL: <command>", up to 3000 chars)
  reply once|reject [-m MSG] <sid:rid>...   answer requests (logged to work/opencode/decisions.jsonl)
  status                  one line per session: range, state, cost, cache share, slice progress; plus group totals
  launch [N]              start sessions for the next N unlaunched ranges (default 1)
  unhang [SECS]           interrupt + re-prompt sessions whose current model call has run > SECS (default 600)
  nudge <sid>             re-prompt one idle, unfinished session to continue
  switch                  interrupt every launched session and re-prompt it on the group's current provider/model
  ns [N]                  set per-session cache namespaces: range k uses model "<model>-c<k%N:02d>" (0 disables;
                          aliases are created by tools/opencode_cache_ns.py). Re-prompt to apply to live sessions.
Group file: work/opencode/groups/<group>.json = {"batch", "provider", "model", "ranges": [[a, b], ...],
            "sessions": {}, "cache_ns": N (optional, per-session prompt-cache namespace count)}
The broker for the group reads work/opencode/sessions_<group>.txt (kept in sync here).
"""
import base64, json, os, re, subprocess, sys, time, urllib.error, urllib.parse, urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)
for _try in range(10):  # `opencode service status` sometimes prints nothing useful; retry
    _m = re.search(r"http://[0-9.:]+", subprocess.run(["opencode", "service", "status"], capture_output=True,
                                                      text=True).stdout)
    if _m:
        break
    time.sleep(1)
url = _m.group(0)
_pw = json.load(open(os.path.expanduser("~/.config/opencode/service.json")))["password"]
H = {"Authorization": "Basic " + base64.b64encode(("opencode:" + _pw).encode()).decode(), "content-type": "application/json"}
LOC = "location%5Bdirectory%5D=" + urllib.parse.quote(ROOT)


def api(method, path, body=None):
    req = urllib.request.Request(url + path + ("&" if "?" in path else "?") + LOC, method=method, headers=H,
                                 data=json.dumps(body).encode() if body is not None else None)
    try:
        with urllib.request.urlopen(req, timeout=60) as r:
            return json.loads(r.read() or b"{}")
    except urllib.error.HTTPError as e:
        return {"error": e.code, "body": e.read().decode()[:300]}


group = sys.argv[1]
GF = W("work/opencode/groups", group + ".json")
G = json.load(open(GF))
SESS = G.setdefault("sessions", {})  # range index (str) -> session id
BATCH = json.load(open(W("work/batches", G["batch"] + ".json")))


def save():
    json.dump(G, open(GF, "w"), indent=1)
    open(W("work/opencode", "sessions_%s.txt" % group), "w").write("".join(s + "\n" for s in SESS.values()))


def model(k=None):
    """Range k's model. With "cache_ns": N set, range k uses the alias "<model>-c<k%N:02d>", which maps to the
    same real model but a distinct cheaperinference prompt-cache namespace (see tools/opencode_cache_ns.py)."""
    mid = G["model"]
    if k is not None and G.get("cache_ns") and G.get("provider") == "cheaperinference":
        mid = "%s-c%02d" % (mid, int(k) % int(G["cache_ns"]))
    return {"providerID": G["provider"], "id": mid}


PROMPT = open(W("work/opencode", G.get("prompt") or "wave_prompt.txt")).read()


def prompt_for(k):
    a, b = G["ranges"][k]
    n = sum(len(BATCH[i]["vas"]) for i in range(a, b + 1))
    return PROMPT.replace("{BATCH}", G["batch"]).replace("{A}", str(a)).replace("{B}", str(b)).replace("{N}", str(n))


def progress(k):
    a, b = G["ranges"][k]
    tot = done = ok = 0
    for i in range(a, b + 1):
        sid = BATCH[i]["id"]
        tot += len(BATCH[i]["vas"])
        for f, isok in (("manifest.txt", 1), ("nonmatching.txt", 0), ("partial.txt", 0)):
            p = W("match/slices", sid, f)
            if os.path.exists(p):
                if isok:  # manifest: "<source> <symbol> <va> [flags]"
                    n = sum(1 for l in open(p) if l.strip() and not l.lstrip().startswith("#"))
                else:
                    n = sum(1 for l in open(p) if re.match(r"\s*(?:0x)?[0-9a-fA-F]{6,8}\b", l))
                done += n
                ok += n * isok
    return tot, done, ok


def requests_for(sid):
    r = api("GET", "/api/session/%s/permission" % sid)
    if "error" in r:
        r = api("GET", "/api/permission/request")
        return [x for x in r.get("data", []) if x.get("sessionID") == sid]
    return r.get("data", [])


cmd = sys.argv[2]
args = sys.argv[3:]
titles = {sid: "%s-%s" % (group, k) for k, sid in SESS.items()}

if cmd == "pending":
    end = time.time() + (int(args[0]) if args else 90)
    while True:
        out = []
        for sid in SESS.values():
            for r in requests_for(sid):
                res = r.get("resources") or r.get("patterns") or []
                txt = " ; ".join(res) if isinstance(res, list) else str(res)
                lim = 3000 if r.get("action") in ("bash", "shell") else 300
                if r.get("action") in ("bash", "shell"):
                    # `resources` is the command split into pieces (pipes and redirects lost); show the full text
                    src = r.get("source") or {}
                    m = api("GET", "/api/session/%s/message/%s" % (sid, src.get("messageID")))
                    for part in (m.get("data") or {}).get("content", []):
                        inp = (part.get("state") or {}).get("input") or {}
                        if part.get("id") == src.get("id") and "command" in inp:
                            txt = "FULL: " + inp["command"]
                            if inp.get("workdir") not in (None, ROOT):
                                txt += "  [workdir %s]" % inp["workdir"]
                out.append("%s:%s %s %s :: %s" % (sid, r["id"], titles[sid], r.get("action"), txt[:lim]))
        if out or time.time() > end:
            print("\n".join(out) if out else "(none)")
            break
        time.sleep(3)

elif cmd == "reply":
    v = args.pop(0)
    msg = None
    if args and args[0] == "-m":
        msg = args[1]
        args = args[2:]
    assert v in ("once", "reject")
    for a in args:
        sid, rid = a.split(":")
        r = api("POST", "/api/session/%s/permission/%s/reply" % (sid, rid), {"decision": v, "message": msg})
        open(W("work/opencode/decisions.jsonl"), "a").write(json.dumps(
            {"t": time.strftime("%H:%M:%S"), "group": group, "session": sid, "request": rid, "verdict": v,
             "why": msg or "supervisor"}) + "\n")
        print(rid[-6:], v, "ERR %s" % r if "error" in r else "ok")

elif cmd == "status":
    act = api("GET", "/api/session/active").get("data", {})
    allss = {s["id"]: s for s in api("GET", "/api/session?limit=500").get("data", [])}
    T = [0.0, 0, 0, 0, 0]
    for k in range(len(G["ranges"])):
        tot, done, ok = progress(k)
        sid = SESS.get(str(k))
        s = allss.get(sid, {}) if sid else {}
        kids = [x for x in allss.values() if x.get("parentID") == sid] if sid else []
        cost = sum(x.get("cost", 0) for x in [s] + kids if x)
        tk = s.get("tokens", {})
        inp, cr = tk.get("input", 0), tk.get("cache", {}).get("read", 0)
        state = "-" if not sid else ("active" if sid in act else "idle")
        print("r%-3d %s %-6s funcs %3d/%-3d exact %3d  $%.3f  cache %2.0f%%  %s" % (
            k, G["ranges"][k], state, done, tot, ok, cost, 100.0 * cr / max(1, inp + cr), sid or ""))
        T = [T[0] + cost, T[1] + done, T[2] + tot, T[3] + ok, T[4] + (1 if state == "active" else 0)]
    print("TOTAL funcs %d/%d exact %d  $%.2f  active %d  launched %d/%d" % (T[1], T[2], T[3], T[0], T[4], len(SESS),
                                                                             len(G["ranges"])))

elif cmd == "launch":
    n = int(args[0]) if args else 1
    for k in range(len(G["ranges"])):
        if n <= 0:
            break
        if str(k) in SESS:
            continue
        s = api("POST", "/api/session", {"title": "spore-%s-%d" % (group, k), "location": {"directory": ROOT},
                                         "model": model(k)})
        sid = s.get("id") or s.get("data", {}).get("id")
        SESS[str(k)] = sid
        save()  # broker must know the session before its first request
        api("POST", "/api/session/%s/prompt" % sid, {"text": prompt_for(k), "model": model(k)})
        print("launched r%d %s" % (k, sid))
        n -= 1
    save()

elif cmd == "unhang":
    lim = int(args[0]) if args else 600
    for k, sid in SESS.items():
        if requests_for(sid):
            continue
        m = api("GET", "/api/session/%s/message?limit=2" % sid).get("data", [])
        a = [x for x in m if x.get("type") == "assistant" or x.get("role") == "assistant"]
        if a and not a[0].get("time", {}).get("completed") and time.time() - a[0]["time"]["created"] / 1000 > lim:
            api("POST", "/api/session/%s/interrupt" % sid, {})
            api("POST", "/api/session/%s/prompt" % sid, {"text": "Your previous model call hung and was interrupted. "
                "Continue your task from the files already written in your slices.", "model": model(int(k))})
            print("unhung r%s %s" % (k, sid))

elif cmd == "switch":  # move every launched session to the group's current provider/model (and cache namespace)
    for k, sid in SESS.items():
        api("POST", "/api/session/%s/model" % sid, {"model": model(int(k))})  # prompt's "model" field doesn't change it
        api("POST", "/api/session/%s/interrupt" % sid, {})
        r = api("POST", "/api/session/%s/prompt" % sid, {"text": "You were interrupted to switch model provider. "
            "Continue your task exactly where you left off: check the files already written in your slices, then keep "
            "going.", "model": model(int(k))})
        print("switched r%s %s %s" % (k, sid, "ERR %s" % r if "error" in r else "ok"))

elif cmd == "nudge":
    sid = args[0]
    assert sid in SESS.values(), "not a session of this group"
    k = next(kk for kk, s in SESS.items() if s == sid)
    api("POST", "/api/session/%s/model" % sid, {"model": model(int(k))})  # prompt's "model" field doesn't change it
    api("POST", "/api/session/%s/prompt" % sid, {"text": "Continue your task: check the files already written in your "
        "slices and finish the remaining slices, then give the final one-line-per-slice summary.",
        "model": model(int(k))})
    print("nudged", sid)

elif cmd == "ns":  # set (or clear) the per-session cache-namespace count for this group
    G["cache_ns"] = int(args[0]) if args else 32
    save()
    print("cache_ns =", G["cache_ns"], "(re-prompt sessions or launch new ones to apply)")
else:
    sys.exit(__doc__)
