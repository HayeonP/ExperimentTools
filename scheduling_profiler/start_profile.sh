#!/bin/bash

echo "========================================"
echo "[INFO] Initialize profile scheduling."

echo 0 > /sys/kernel/debug/tracing/tracing_on
sleep 1

echo 0 > /sys/kernel/debug/tracing/events/enable
sleep 1

# Set events
echo 1 > /sys/kernel/debug/tracing/events/sched/sched_switch/enable
echo "<sched_switch: Enable>"
echo 1 > /sys/kernel/debug/tracing/events/sched/sched_wakeup/enable
echo "<sched_wakeup: Enable>"
sleep 1

echo 1 > /sys/kernel/debug/tracing/tracing_on
sleep 1
echo "[INFO] Trun on tracing."
echo "========================================"











