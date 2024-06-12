## Purpose.

A proof of concept that shows you can set the timeout Linux will use for retransmitting initial SYN's without recompiling the kernel by using BPF tricks.

## DANGER NOTICE.

This is a proof of concept HACK only. It is NOT something I would recommend in production. It was built to answer the question in the Purpose section only.

## Setup.

Only tested on Debian 12 + x64 with kernels 6.8.12 + 6.10-rc3.

You need the following packages installed to use this.

- build-essential
- bpftool
- libc6-dev-i386
- libbpf-dev
- clang
- linux-headers-\`uname -r\`
- (If building with non-Debian packaged kernel, symlink headers to somewhere in the `-I` flags in `build-and-install.sh`)

## Usage

Run ./build-and-install.sh. Read it if you want to know more about what is going on.

## Example.

```
$ ./build-and-install.sh 0.1
Setting DELAY to 10

$ telnet 9.9.99.99

$ tcpdump -i wlp2s0 -n host 9.9.99.99
tcpdump: verbose output suppressed, use -v[v]... for full protocol decode
listening on wlp2s0, link-type EN10MB (Ethernet), snapshot length 262144 bytes
00:45:15.574921 IP 192.168.1.101.35136 > 9.9.99.99.23: Flags [S], seq 2956392957, win 64240, options [mss 1460,sackOK,TS val 4057192041 ecr 0,nop,wscale 7], length 0
00:45:15.677600 IP 192.168.1.101.35136 > 9.9.99.99.23: Flags [S], seq 2956392957, win 64240, options [mss 1460,sackOK,TS val 4057192084 ecr 0,nop,wscale 7], length 0
00:45:15.775596 IP 192.168.1.101.35136 > 9.9.99.99.23: Flags [S], seq 2956392957, win 64240, options [mss 1460,sackOK,TS val 4057192172 ecr 0,nop,wscale 7], length 0
00:45:15.879568 IP 192.168.1.101.35136 > 9.9.99.99.23: Flags [S], seq 2956392957, win 64240, options [mss 1460,sackOK,TS val 4057192216 ecr 0,nop,wscale 7], length 0
00:45:15.981599 IP 192.168.1.101.35136 > 9.9.99.99.23: Flags [S], seq 2956392957, win 64240, options [mss 1460,sackOK,TS val 4057192260 ecr 0,nop,wscale 7], length 0
```

## Bugs and Defects.

- You can't reload it. Get it right or reboot and try again. This sucks. Sorry.

