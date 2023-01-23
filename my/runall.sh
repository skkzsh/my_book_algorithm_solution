#!/bin/bash

# set -e

exit_code=0  # initialize

for t in $@; do
  echo "[$t]"
  ./$t
  exit_code=$(( $exit_code | $?)) # 1つでも1があれば1を返す
done

exit $exit_code
