#!/bin/sh
set -e
SCRIPT_DIR=$(dirname "$0")

ORIG_WD=$(pwd)
cd ${SCRIPT_DIR}

cd autolibrary
cargo run ../config.json

cd ${ORIG_WD}
