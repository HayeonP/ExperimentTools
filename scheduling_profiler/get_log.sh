#!/bin/bash

echo "========================================"
echo "[INFO] Turn off tracing."

echo 0 > /sys/kernel/debug/tracing/tracing_on
sleep(3)

cp /sys/kernel/debug/tracing/trace .
mv trace ftrace_log.c

echo "[INFO] Log file is created as ftrace_log.c to the current directory."
echo "========================================"
