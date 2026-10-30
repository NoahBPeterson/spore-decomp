"""pytest setup for tools/difftest: run under PYTHONHASHSEED=0, like equiv.py's command line (equiv.pin_hash_seed).
Set-of-strings iteration order follows the hash seed, so without it a row test can pass or fail from run to run."""
import os
import sys


def pytest_configure(config):
    if os.environ.get("PYTHONHASHSEED") == "0":
        return
    # pytest has already redirected fds 1/2 into its capture files: restore them, or the re-exec'd run prints nothing
    capman = config.pluginmanager.getplugin("capturemanager")
    if capman is not None:
        capman.stop_global_capturing()
    os.environ["PYTHONHASHSEED"] = "0"
    os.execv(sys.executable, [sys.executable, "-m", "pytest"] + sys.argv[1:])
