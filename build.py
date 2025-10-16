#!/usr/bin/env python3
import os
import sys
import subprocess

BUILD_TYPE = os.environ.get("BUILD_TYPE", "release")
BUILD_DIR = "build/debug" if BUILD_TYPE.lower().startswith("d") else "build/release"

CC = "cl" if os.name == "nt" else "cc"
CXX = "cl" if os.name == "nt" else "c++"
CFLAGS = ["/Iinclude"] if os.name == "nt" else ["-Iinclude", "-O2", "-Wall"]
OBJ_FILES = []

os.makedirs(BUILD_DIR, exist_ok=True)

def compile_file(src):
    base = os.path.basename(src)
    name, ext = os.path.splitext(base)
    obj = os.path.join(BUILD_DIR, f"{name}.obj" if os.name == "nt" else f"{name}.o")
    if ext == ".c":
        cmd = [CC] + CFLAGS + (["/c", src, f"/Fo{obj}"] if os.name == "nt" else ["-c", src, "-o", obj])
    else:  # .cpp
        cmd = [CXX] + CFLAGS + (["/c", src, f"/Fo{obj}"] if os.name == "nt" else ["-c", src, "-o", obj])
    print(" ".join(cmd))
    subprocess.check_call(cmd)
    OBJ_FILES.append(obj)

def walk_and_compile(directory):
    for root, dirs, files in os.walk(directory):
        for f in files:
            if f.endswith(".c") or f.endswith(".cpp"):
                compile_file(os.path.join(root, f))

walk_and_compile("src")

if os.name == "nt":
    exe = os.path.join(BUILD_DIR, "wordler.exe")
    cmd = ["cl", "/Fe:" + exe] + OBJ_FILES
else:
    exe = os.path.join(BUILD_DIR, "wordler")
    cmd = ["c++", "-lSDL2", "-lGL", "-lGLU", "-lSDL2_image"] + OBJ_FILES + ["-o", exe]

print("Linking:", " ".join(cmd))
subprocess.check_call(cmd)
print(f"Build complete: {BUILD_DIR}")