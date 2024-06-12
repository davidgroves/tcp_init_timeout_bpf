#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: build.sh <timeout>"
  echo "Where timeout is in seconds, including fractions of seconds".
  exit 1
fi

TICKRATE=`getconf CLK_TCK`
TIMEOUT=$1

DELAY=`echo "${TICKRATE} * ${TIMEOUT}" | bc | awk -F '.' ' { print $1 } '`
echo "Setting DELAY to ${DELAY}"

echo "#define DELAY ${DELAY}" > timeout.h

clang -I/usr/include/x86_64-linux-gnu/ -target bpf -O2 -c tcp_init_timeout_bpf.c -o tcp_init_timeout_bpf.o

sudo bpftool prog load tcp_init_timeout_bpf.o /sys/fs/bpf/tcp_init_timeout_bpf
ID=`sudo bpftool prog show | grep sock_ops | awk -F ':' ' { print $1 } '`
sudo bpftool cgroup attach /sys/fs/cgroup/ sock_ops id $ID

