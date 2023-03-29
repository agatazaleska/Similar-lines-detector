#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Incorrect number of arguments"
    echo "Usage: "
    echo "test.sh prog dir"
    exit 1
fi


PROGRAM=$1
DIR=$2
VALGRIND="valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all"
COMMAND_VAL="$VALGRIND $PROGRAM"
COMMAND="$PROGRAM"

for FILE in $DIR/*.in
do
    OUTPUT="${FILE%.in}_test.out"
    ERROR="${FILE%.in}_test.err"
    OUTPUT_DIFF="${FILE%.in}_test.diff"
    ERROR_DIFF="${FILE%.in}_error.diff"

    $COMMAND <"$FILE" >"$OUTPUT" 2>"$ERROR"

    diff "${FILE%in}out" "$OUTPUT" >"$OUTPUT_DIFF"
    OUTPUT_DIFF_VAL=$?
    diff "${FILE%in}err" "$ERROR" >"$ERROR_DIFF"
    ERROR_DIFF_VAL=$?

    $COMMAND_VAL <"$FILE" >/dev/null 2>/dev/null
    VALGRIND_RETURN=$?

    
    if [ $OUTPUT_DIFF_VAL -eq 0 ]
    then
        echo "$FILE - TEST - OUTPUT OK"
    else
        echo "$FILE - OUTPUT - TEST FAILED. Brief diff info:"
        head -5 $OUTPUT_DIFF
    fi

    if [ $ERROR_DIFF_VAL -eq 0 ]
    then
        echo "$FILE - TEST - ERRORS OK"
    else
        echo "$FILE - ERRORS - TEST FAILED. Brief diff info:"
        head -5 $ERROR_DIFF
    fi

    if [ $VALGRIND_RETURN -eq 123 ]
    then
        echo "$FILE - !memory error(s) detected."
    fi

    rm "$OUTPUT"
    rm "$ERROR"
    rm "$OUTPUT_DIFF"
    rm "$ERROR_DIFF"

done





