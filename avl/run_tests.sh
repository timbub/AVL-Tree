#!/bin/bash
PROGRAM="./build/tree"

TESTS_DIR="./tests"

echo "running E2E tests"
for INPUT_FILE in ${TESTS_DIR}/*.in; do

    BASENAME="${INPUT_FILE%.in}"

    EXPECTED_FILE="${BASENAME}.out"
    ACTUAL_FILE="${BASENAME}.act"

${PROGRAM} < ${INPUT_FILE} > ${ACTUAL_FILE}

diff -q -w "${ACTUAL_FILE}" "${EXPECTED_FILE}"

if [ $? -eq 0 ]; then
    echo "TEST ${INPUT_FILE} PASSED"
else
    echo "TEST ${INPUT_FILE} FAILED"
fi

rm ${ACTUAL_FILE}
done
