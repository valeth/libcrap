#!/usr/bin/env python3

import subprocess
import os
import errno
from glob import glob

def run_test(name: str) -> bool:
    env = {
        **os.environ,
        "LD_LIBRARY_PATH": os.path.join(os.getcwd(), "build")
    }
    ret = subprocess.call(name, env=env, stderr=subprocess.STDOUT)
    if ret == -11:
        print(f"Segmentation fault in {name}!")
    return ret == 0

def run_tests() -> (int, list, list):
    success = []
    failure = []
    test_exes = glob("tests/*_test")
    count = len(test_exes)

    for test_exe in test_exes:
        test = os.path.basename(test_exe)
        print(f"Running {test}...")
        if run_test(test_exe):
            print(f"Test {test} successful")
            success.append(test)
        else:
            print(f"Test {test} failed")
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

if __name__ == "__main__":
    count, success, failure = run_tests()
    summary(count, len(success), len(failure))
