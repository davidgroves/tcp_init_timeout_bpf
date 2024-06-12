/*
    tcp_init_timeout_bpf.c: Modifies the initial timeout window for 
    TCP SYN's in Linux kernels 6.8 or later using BPF hacks.

    Copyright (C) 2024, David Groves

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <linux/bpf.h>
#include <unistd.h>
#include "timeout.h"

#ifndef __section
#define __section(NAME)                  \
    __attribute__((section(NAME), used))
#endif

__section("sockops")
int set_initial_rto(struct bpf_sock_ops *skops)
{
    int op = (int)skops->op;
    if (op == BPF_SOCK_OPS_TIMEOUT_INIT) {
        skops->reply = DELAY;
    }

    return 1;
}

char _license[] __section("license") = "GPL";

