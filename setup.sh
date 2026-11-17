#!/usr/bin/env bash
# Setup for Ubuntu/WSL: C/C++17 toolchain only (no third-party libraries, no Python).
set -euo pipefail
cd "$(dirname "$0")"
sudo apt-get update
sudo apt-get install -y build-essential gdb make
# Sample build and run (README "Build and run")
( cd LinkedList && make && ./Stack_app.exe < /dev/null )
( cd "Assignments Code solutions/C++" && make avl_tree )
echo "Other programs: g++ -std=c++17 -O2 <file>.cpp -o out   (see README 'Build and run')"
