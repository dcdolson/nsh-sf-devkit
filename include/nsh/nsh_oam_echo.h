#ifndef SVNET_NSH_OAM_ECHO_H
#define SVNET_NSH_OAM_ECHO_H

#include <stdint.h>
#include <stdbool.h>

#include <nsh/nsh.h>

// OAM Echo message
// OAM Echo is used as keepalive message
 
/*
      0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |              Subcode          |            Total length       |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

     Subcode (0x0 - echo request, 0x1 - echo reply)
     Total Length (in bytes) of the OAM echo
*/

struct nsh_oam_echo
{
    uint16_t subcode;
    uint16_t length;              /*!< Length is in bytes and includes oam header and payload */
    uint32_t dst_id;              /*!< Identifier (destination id) */
    uint32_t trn_id;              /*!< Sequence number (keepalive transaction id) */
    uint32_t rqst_timestamp_sec;  /*!< Request timestamp seconds */
    uint32_t rqst_timestamp_usec; /*!< Request timestamp microseconds */
    uint8_t  data[];              /*!< variable length data (any number of octets, calculated using length) */
}__attribute__((__packed__));

//! NSH OAM packet (nsh haeder + nsh oam echo message)
struct nsh_oam_echo_packet
{
    struct nsh_hdr      hdr;
    struct nsh_oam_echo oam_echo;
} __attribute__((__packed__));

#define NSH_NEXT_PROTOCOL_OAM_ECHO  0xFE
#define NSH_ECHO_REQUEST    0x0
#define NSH_ECHO_RESPOND    0x1
#define NSH_HEADER_SIZE_WITH_OAM_ECHO 8

inline static uint16_t nsh_oam_get_subcode(const struct nsh_oam_echo* oam)
{
    return ntohs(oam->subcode);
}

inline static void nsh_oam_set_subcode(struct nsh_oam_echo* oam, uint16_t code)
{
    oam->subcode = htons(code);
}

// Length is in bytes and includes oam header and payload
inline static uint16_t nsh_oam_get_length(const struct nsh_oam_echo* oam)
{
    return ntohs(oam->length);
}

// Length is in bytes and includes oam header and payload
inline static void nsh_oam_set_length(struct nsh_oam_echo* oam, uint16_t length)
{
    oam->length = htons(length);
}

// Identifier (destination id)
inline static uint32_t nsh_oam_get_dst_id(const struct nsh_oam_echo* oam)
{
    return ntohl(oam->dst_id);
}

// Identifier (destination id)
inline static void nsh_oam_set_dst_id(struct nsh_oam_echo* oam, uint32_t dst_id)
{
    oam->dst_id = htonl(dst_id);
}

// Sequence number (keepalive transaction id)
inline static uint32_t nsh_oam_get_trn_id(const struct nsh_oam_echo* oam)
{
    return ntohl(oam->trn_id);
}

// Sequence number (keepalive transaction id)
inline static void nsh_oam_set_trn_id(struct nsh_oam_echo* oam, uint32_t trn_id)
{
    oam->trn_id = htonl(trn_id);
}

// Request timestamp microseconds
inline static uint64_t nsh_oam_get_initiator_timestamp_usec(const struct nsh_oam_echo* oam)
{
    return ntohl(oam->rqst_timestamp_sec) * 1000000UL + ntohl(oam->rqst_timestamp_usec);
}

// Request timestamp microseconds
inline static void nsh_oam_set_initiator_timestamp_usec(struct nsh_oam_echo* oam, uint64_t rqst_timestamp_usec)
{
    uint32_t sec = rqst_timestamp_usec / 1000000UL;
    uint32_t usec = rqst_timestamp_usec - sec * 1000000UL;
    
    oam->rqst_timestamp_sec = htonl(sec);
    oam->rqst_timestamp_usec = htonl(usec);
}

#endif /*SVNET_NSH_OAM_ECHO_H*/
