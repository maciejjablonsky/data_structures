#!/bin/bash

INIT=$(pwd)
mkdir -p build
rm -r build/*
cd build
cmake ..
mkdir -p bin
make

mv test_* bin

PASSED=0
ALL=0
FAILED_TESTS=""
cd "$INIT"
for FILE in build/bin/* ; do
    ./"$FILE"
    if (( $? == 0 ))  ; then
        PASSED=$((PASSED + 1))
    else
        FAILED_TESTS="${FAILED_TESTS}$(echo ${FILE} | sed 's#.*/##g')\n"
    fi
    ALL=$((ALL + 1))
done

printf "\n$PASSED/$ALL tests passed.\n"
if [[ -n ${FAILED_TESTS} ]]; then
    echo "Failed tests:"
    printf "${FAILED_TESTS}"
fi