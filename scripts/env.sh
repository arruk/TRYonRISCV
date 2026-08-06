#!/usr/bin/env bash

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

export RISCV="$REPO_ROOT/.tools/riscv"
export PATH="$RISCV/bin:$PATH"
