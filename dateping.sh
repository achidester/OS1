#!/bin/sh

echo "Date/ Ping"
set -x  # turn tracing on
date
ping -c 3 example.com
set +x  # turn tracing on
echo "math test"
x=2
: $((++x))
echo $x