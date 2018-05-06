#!/usr/bin/env python3

import subprocess
import os
import sys
from glob import glob

def run_test(name: str, valgrind=False) -> bool:
    cwd = os.getcwd()
    env = os.environ.update({
        "LD_LIBRARY_PATH": os.path.join(cwd, "build")
    })

    if valgrind:
        cmd = [
            "valgrind",
            "--leak-check=full",
            "--vgdb=no",
            "--time-stamp=yes",
            "--log-file=tests/valgrind-{}.log".format(os.path.basename(name)),
            name
        ]
    else:
        cmd = name
    ret = subprocess.call(cmd, env=env, stderr=subprocess.STDOUT)
    if ret == -11:
        print("Segmentation fault in {}!".format(name))
    return ret == 0

def run_tests(valgrind=False) -> (int, list, list):
    success = []
    failure = []
    test_exes = sorted(glob("tests/*_test"))
    count = len(test_exes)

    for test_exe in test_exes:
        test = os.path.basename(test_exe)
        print("Running {}...".format(test))
        if run_test(test_exe, valgrind):
            print("Test {} successful".format(test))
            success.append(test)
        else:
            print("Test {} failed".format(test))
            failure.append(test)

    return (count, success, failure)

def summary(count: int, successful: int, failed: int):
    print(
        "\n{:-^30}\n".format("[Summary]") +
        "Success: {:d} ({:>7.2%})\n".format(successful, successful / count) +
        "Failed:  {:d} ({:>7.2%})\n".format(failed, failed / count) +
        "Total:   {:d}\n".format(count) +
        "-" * 30
    )

def main(args):
    valgrind = False
    if len(args) > 1:
        valgrind = (args[1] == "--valgrind") or False
    count, success, failure = run_tests(valgrind)
    summary(count, len(success), len(failure))


if __name__ == "__main__":
    main(sys.argv)
