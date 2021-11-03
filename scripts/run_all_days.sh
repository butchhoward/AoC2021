#!/usr/bin/env bash

if [ ! -x "./solve" ]; then
    echo "Build first, then solve."
    exit 1
fi

./solve
