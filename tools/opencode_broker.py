#!/usr/bin/env python3
"""Permission broker for opencode decomp sessions (no --auto): answers each request once, by policy.

usage: opencode_broker.py <batch name> [--once] [--manual] [--sessions <file>]
--sessions: only handle requests from session IDs listed (one per line) in <file>, re-read every poll, so
two brokers with different policies can serve different sessions at once.
--manual: never auto-approve anything. Clearly forbidden requests are still auto-rejected; every other request
          (including reads/globs/greps) is printed as HOLD for a supervising agent to decide one by one.
Polls the opencode background service for pending permission requests in this project and replies:
  allow  - read-only/project tools (card.py, chk.py, cmpdis.py, run_all.py, pdb_type.py, rg, ls, ...) and
           edits/writes inside match/slices/<id>/, symbols/slices/<id>.txt, work/match/scratch_<id>_* for
           slices of the given batch
  reject - git, deletion outside allowed paths, network, package managers, Ghidra, process control,
           writes anywhere else
  hold   - anything else: left pending and logged as HOLD for the orchestrator (a human-in-the-loop decision)
Every decision is appended to work/opencode/decisions.jsonl. Requires .opencode/opencode.json with
"permission": {"edit": "ask", "bash": "ask", ...} so requests reach the service.
"""
import json, os, re, sys, time, urllib.parse, urllib.request, base64, subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LOG = os.path.join(ROOT, "work/opencode/decisions.jsonl")

batch = sys.argv[1]
ids = [s["id"] for s in json.load(open(os.path.join(ROOT, "work/batches", batch + ".json")))]
IDS = "(?:" + "|".join(map(re.escape, ids)) + ")"
ALLOWED_PATH = re.compile(r"^(?:%s/)?(?:match/slices/%s/[^/]+|symbols/slices/%s\.txt|work/match/.*)$"
                          % (re.escape(ROOT), IDS, IDS))
PY_TOOLS = re.compile(r"^(?:\.venv/bin/python3?\s+)?(?:tools/matching/(?:slice_info|card|chk|cmpdis|try_variants|run_all|od_names|"
                      r"disasm|pattern_info|cmpobj|patterns|libmatch|asm_audit)\.py|tools/pdb_type\.py|"
                      r"tools/difftest/(?:equiv|batch|slice)\.py)(?:\s|$)")
SAFE_CMD = re.compile(r"^(?:rg|ls|cat|head|tail|wc|sort|uniq|cut|tr|echo|printf|true|false|test|\[|pwd|file|xxd|od|"
                      r"c\+\+filt|diff|cmp|basename|dirname|seq|grep|sed|nl|column|date|which|ps|pgrep|pidof|awk|stat|du|find|strings|hexdump|md5|shasum|realpath|readlink|(?:llvm-)?nm|(?:[A-Za-z0-9_]+-w64-mingw32-)?objdump|lsof|sleep|set|export|read|shift|cd|:|local|break|continue)(?:\s|$)")
DENY_CMD = re.compile(r"^(?:sudo|git|curl|wget|pip3?|uv|brew|npm|npx|ssh|scp|rsync|ghidra|pyghidra|analyzeHeadless|"
                      r"kill|pkill|killall|open|osascript|chmod|chown|ln|dd|truncate|shutdown|launchctl|crontab)(?:\s|$)")


def svc():
    u = re.search(r"http://[0-9.:]+", subprocess.run(["opencode", "service", "status"], capture_output=True,
                                                    text=True).stdout + "").group(0)
    pw = json.load(open(os.path.expanduser("~/.config/opencode/service.json")))["password"]
    return u, "Basic " + base64.b64encode(("opencode:" + pw).encode()).decode()


URL, AUTH = svc()
LOC = "location%5Bdirectory%5D=" + urllib.parse.quote(ROOT)


def call(method, path, body=None):
    req = urllib.request.Request(URL + path + ("&" if "?" in path else "?") + LOC, method=method,
                                 data=json.dumps(body).encode() if body is not None else None,
                                 headers={"Authorization": AUTH, "content-type": "application/json"})
    with urllib.request.urlopen(req, timeout=30) as r:
        return json.loads(r.read() or b"{}")


def paths_in(seg):
    """Write targets in a shell segment: output redirects (not 2>&1 / >/dev/null) and tee/mkdir/rm/cp/mv/touch args."""
    if "<<" in seg:  # heredoc: only the command line can redirect; the body is data (C++ `->` etc.)
        seg = seg.split("\n", 1)[0]
    bare = re.sub(r"'[^']*'|\"(?:[^\"\\]|\\.)*\"", "''", seg)  # quoted text can't redirect (template args etc.)
    out = [m.group(1) for m in re.finditer(r"(?<![0-9&-])>>?\s*([^\s;|&]+)", bare) if m.group(1) not in ("/dev/null",)]
    m = re.match(r"^(?:tee(?: -a)?|mkdir(?: -p)?|rm(?: -[rf]+)?|touch|cp|mv)\s+(.*)$", seg)
    if m:
        args = [a for a in m.group(1).split() if not a.startswith("-")]
        out += args[-1:] if seg.startswith(("cp", "mv")) else args
    return out


def ok_path(p):
    p = p.strip("'\"")
    return (bool(ALLOWED_PATH.match(p)) or bool(re.match(r"^(?:%s/)?match/slices/%s/?$" % (re.escape(ROOT), IDS), p))
            or bool(re.match(r"^(?:%s/)?(?:match/slices|symbols/slices|work/match)/?$" % re.escape(ROOT), p)))  # existing parent dirs (mkdir -p)


import ast
SAFE_MODULES = {"json", "re", "struct", "collections", "math", "itertools", "bisect", "glob", "csv", "pefile", "capstone",
                "functools", "string", "textwrap", "pprint", "binascii", "hashlib", "operator", "sys", "os", "cmpobj", "card", "difflib",
                "unicorn", "equiv", "shlex", "pickle", "slice", "coff", "machine", "resolve", "sig", "emu", "smoke", "batch", "smoke"}
BAD_NAMES = {"exec", "eval", "compile", "__import__", "input", "breakpoint", "globals", "locals", "setattr", "delattr"}
BAD_ATTRS = {"write", "writelines", "remove", "unlink", "rename", "replace", "rmdir", "rmtree", "mkdir", "makedirs",
             "system", "popen", "run", "call", "check_call", "check_output", "Popen", "spawn", "kill", "chmod", "chown",
             "truncate", "touch", "write_text", "write_bytes", "symlink", "link", "exit", "_exit", "fork", "execv", "execve"}


def safe_python(code):
    """True if the inline Python only reads: whitelisted imports, open() in read mode, no write/exec/process calls.
    pickle is a code-execution sink: when it is imported, pickle.loads is rejected and every open() must name a
    literal path under work/difftest/ (the checker's own trusted test data, which workers cannot write).
    """
    try:
        tree = ast.parse(code)
    except SyntaxError:
        return False
    pickle_imp = False
    for n in ast.walk(tree):
        if isinstance(n, (ast.Import, ast.ImportFrom)):
            mods = [a.name for a in n.names] if isinstance(n, ast.Import) else [n.module or ""]
            if any(m.split(".")[0] not in SAFE_MODULES for m in mods):
                return False
            if any(m.split(".")[0] == "pickle" for m in mods):
                pickle_imp = True
        elif isinstance(n, ast.Name) and n.id in BAD_NAMES:
            return False
        elif isinstance(n, ast.Attribute) and n.attr in BAD_ATTRS:
            return False
        elif (isinstance(n, ast.Call) and isinstance(n.func, ast.Attribute) and n.func.attr == "loads"
              and isinstance(n.func.value, ast.Name) and n.func.value.id == "pickle"):
            return False  # unpickling bytes that are not a repo-local file
        elif isinstance(n, ast.Call) and isinstance(n.func, ast.Name) and n.func.id == "open":
            mode = n.args[1] if len(n.args) > 1 else next((k.value for k in n.keywords if k.arg == "mode"), None)
            if mode is not None and not (isinstance(mode, ast.Constant) and isinstance(mode.value, str)
                                         and set(mode.value) <= set("rbt")):
                return False
            if pickle_imp:
                a0 = n.args[0] if n.args else None
                if not (isinstance(a0, ast.Constant) and isinstance(a0.value, str) and "work/difftest/" in a0.value):
                    return False  # only unpickle files the checker wrote
    return True


def inline_python(seg):
    """Return the code of `python -c "..."` or `python - <<'EOF' ... EOF`, else None."""
    m = re.match(r"^\.venv/bin/python3? -c (['\"])(.*)\1\s*$", seg, re.S)
    if m:
        return m.group(2)
    m = re.match(r"^\.venv/bin/python3? - <<'?(\w+)'?\n(.*)\n\1\s*$", seg, re.S)
    if m:
        return m.group(2)
    return None


OUTSIDE = re.compile(r"(?:^|[\s=:'\"(<>|;&])(?:~|\$HOME|\$\{HOME\}|/(?!%s(?:/|\b))(?:Users|Volumes|etc|usr|bin|sbin|tmp|var|private|"
                     r"System|Library|opt|Applications|proc|home|root|cores|Network|dev/(?!null\b)))" % re.escape(ROOT.lstrip("/")))
SECRETY = re.compile(r"(?:^|[\s;|&(])(?:env|printenv|set\s*$|export\s+-p|declare\s+-x)(?:\s|$)|\$[A-Z_]*(?:KEY|TOKEN|SECRET|PASSWORD)|"
                     r"\.(?:ssh|aws|config|local)/|Secrets|auth\.json|service\.json|\.opencode/|\.\./\.\.", re.I)


def outside_repo(text):
    """True if the text references a path outside the repo, the home dir, env vars or credential files."""
    return bool(OUTSIDE.search(text) or SECRETY.search(text))


def decide_manual(r):
    act, res = r.get("action"), r.get("resources") or []
    blob = "\n".join(res)
    if act in ("webfetch", "websearch"):
        return "reject", "no network"
    if act in ("read", "glob", "grep", "list", "edit", "write", "patch", "apply_patch", "external_directory"):
        for p in res:
            ap = p if os.path.isabs(p) else os.path.normpath(os.path.join(ROOT, p))
            if not ap.startswith(ROOT + "/") and ap != ROOT or SECRETY.search(p):
                return "reject", "path outside the repo or a credential file: %s" % p[:100]
    if act in ("edit", "write", "patch", "apply_patch"):
        bad = [p for p in res if not ok_path(os.path.relpath(p, ROOT) if os.path.isabs(p) else p)]
        if bad:
            return "reject", "edit outside allowed paths: %s" % bad[:3]
    if act in ("shell", "bash"):
        if outside_repo(blob):
            return "reject", "references a path outside the repo, env vars or credentials"
        v, why = decide(r)
        if v == "reject":
            return v, why
    return "hold", "manual mode: every request needs supervisor approval (policy verdict: %s)" % (decide(r)[1] if act in ("shell","bash") else act)


def decide(r):
    act, res = r.get("action"), r.get("resources") or []
    if act in ("task", "subagent"):
        return "reject", "subagent spawning is forbidden; do the work yourself in this session"
    if act in ("read", "glob", "grep", "list", "lsp", "todowrite", "todoread", "skill"):
        return "once", "read-only/agent tool"
    if act in ("edit", "write", "patch", "apply_patch"):
        bad = [p for p in res if not ok_path(os.path.relpath(p, ROOT) if os.path.isabs(p) else p)]
        return ("once", "edit inside batch slice paths") if not bad else ("reject", "edit outside allowed paths: %s" % bad[:3])
    if act in ("shell", "bash"):
        for seg in res:
            s = re.sub(r"\s*2>&1\s*", " ", seg).strip()
            s = re.sub(r"^(?:[A-Za-z_][A-Za-z0-9_]*=\S*\s+)+", "", s)  # leading VAR=value
            s = re.sub(r"^(?:timeout|gtimeout)\s+(?:-\S+\s+)*\d+[smh]?\s+", "", s)  # `timeout N cmd` wrapper
            s = re.sub(r"^(?:time|/usr/bin/time)\s+", "", s)  # `time cmd` wrapper
            s = re.sub(r"^(?:nohup|setsid)\s+", "", s)       # `nohup cmd` wrapper
            if DENY_CMD.match(s):
                return "reject", "denied command: %s" % s[:80]
            for p in paths_in(s):
                if not ok_path(p):
                    if s.startswith("rm") or ">" in s or s.startswith(("cp", "mv", "tee", "touch")):
                        return "reject", "write outside allowed paths: %s" % p
                    return "hold", "unrecognized path argument: %s" % p
            if s.startswith(("rm", "mkdir", "touch", "cp", "mv", "tee")):
                continue  # all targets checked above
            m = re.match(r"^\.venv/bin/python3? (work/match/scratch_%s\S*\.py)(?:\s|$)" % IDS, s)
            if m and os.path.exists(os.path.join(ROOT, m.group(1))):
                if safe_python(open(os.path.join(ROOT, m.group(1))).read()):
                    continue
                return "hold", "scratch script with side effects or unknown imports: %s" % m.group(1)
            code = inline_python(s)
            if code is not None:
                if safe_python(code):
                    continue
                return "reject", "inline python with side effects or unknown imports; use .venv/bin/python <script> or a repo tool"
            if re.match(r"^(?:python3?|python)(?:\s|$)", s):
                return "reject", "bare python; use .venv/bin/python <script>"
            if s == "perl" or s.startswith("perl "):
                return "reject", "no perl; use the edit/write tools or .venv/bin/python"
            if re.search(r"(?:^|[/\s])tools/matching/cl(?:71)?\.sh\s", s):  # compiler; object output must stay in work/match
                if "/Fo" in s and not re.search(r"/Fo[^\s]*?work[\\/]+match", s):
                    return "reject", "compiler output outside work/match: %s" % s[:120]
                continue
            if "/tmp/" in s or re.search(r"(?:^|\s)/(?:private/)?tmp(?:/|\s|$)", s):
                return "reject", "no /tmp; keep scratch under work/match/: %s" % s[:120]
            if re.match(r"^(?:\S*/)?(?:llvm-|[\w]+-w64-mingw32-)?objdump(?:\s|$)", s):
                continue  # read-only disassembly
            if not (PY_TOOLS.match(s) or SAFE_CMD.match(s)):
                return "hold", "unrecognized command: %s" % s[:120]
            if "system(" in s or (s.startswith("awk") and re.search(r"print[^;}]*>|getline", s)) or (s.startswith("find") and re.search(r"-(?:exec|execdir|delete|ok|fprint)", s)):
                return "reject", "possible in-place edit / shell escape: %s" % s[:120]
            if re.search(r"(?:^|\s)sed\b[^|;&]*\s-i", s) and "work/match/" not in s and "work\\match" not in s:
                return "reject", "in-place sed outside work/match scratch; use the edit tool: %s" % s[:120]
        return "once", "allowed shell"
    if act in ("webfetch", "websearch"):
        return "reject", "no network"
    return "hold", "unknown action %s" % act


held = set()
while True:
    try:
        reqs = call("GET", "/api/permission/request").get("data", [])
    except Exception as e:  # service restart etc.
        print("ERROR polling: %s" % e, flush=True); time.sleep(5); continue
    if "--sessions" in sys.argv:
        try:
            mine = set(open(sys.argv[sys.argv.index("--sessions") + 1]).read().split())
        except OSError:
            mine = set()
        reqs = [r for r in reqs if r["sessionID"] in mine]
    for r in reqs:
        if r["id"] in held:
            continue
        verdict, why = decide_manual(r) if "--manual" in sys.argv else decide(r)
        rec = {"t": time.strftime("%H:%M:%S"), "session": r["sessionID"], "action": r.get("action"),
               "resources": r.get("resources"), "verdict": verdict, "why": why}
        open(LOG, "a").write(json.dumps(rec) + "\n")
        if verdict == "hold":
            held.add(r["id"])
            print("HOLD %s %s %s :: %s" % (r["id"], r["sessionID"], why, json.dumps(r.get("resources"))[:300]), flush=True)
            continue
        msg = None if verdict == "once" else "Rejected by orchestrator policy: %s. Stay inside your slice paths and use the repo tools." % why
        try:
            call("POST", "/api/session/%s/permission/%s/reply" % (r["sessionID"], r["id"]), {"decision": verdict, "message": msg})
            if verdict == "reject":
                print("REJECT %s %s" % (r["sessionID"], why), flush=True)
        except Exception as e:
            print("ERROR replying %s: %s" % (r["id"], e), flush=True)
    if "--once" in sys.argv:
        break
    time.sleep(1.5)
