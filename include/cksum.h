#ifndef CKSUM_H
#define CKSUM_H
#include <linux/ip.h>
#include <linux/tcp.h>

//! make the iphdr have the correct checksum
void cksum_ip4_fix(struct iphdr* ip);

//! Make the tcp header have the correct checksum. The ip header is
//! used for the IP addresses to form the pseudo-header.
void cksum_tcp4_fix(struct tcphdr* tcp, const struct iphdr* ip);

#endif

