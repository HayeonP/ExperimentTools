# !/bin/sh
watch -n 0.5 'echo "[G3D00(mp3)]";cat /sys/devices/platform/19300000.G3D00/utilization;echo "[G3D01(mp3)]";cat /sys/devices/platform/19500000.G3D01/utilization;'
