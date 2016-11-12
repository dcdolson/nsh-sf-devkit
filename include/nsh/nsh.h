#ifndef NSH_HEADER_H
#define NSH_HEADER_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <arpa/inet.h>

/*
   From https://tools.ietf.org/html/draft-ietf-sfc-nsh-10
   Note version, currently based on rfc version 03.
 
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                Base Header                                    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                Service Path Header                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   ~                Context Headers                                ~
   |                                                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   NSH Base Header

      0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |Ver|O|C|R|R|R|R|R|R|   Length  |    MD Type    | Next Protocol |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Base Header Field Descriptions:

   Version: The version field is used to ensure backward compatibility
   going forward with future NSH updates.  It MUST be set to 0x0 by the
   sender, in this first revision of NSH.

   O bit: when set to 0x1 indicates that this packet is an operations
   and management (OAM) packet.  The receiving SFF and SFs nodes MUST
   examine the payload and take appropriate action (e.g. return status
   information).

   C bit: Indicates that a critical metadata TLV is present (see Section
   3.4.2).  This bit acts as an indication for hardware implementers to
   decide how to handle the presence of a critical TLV without
   necessarily needing to parse all TLVs present.  The C bit MUST be set
   to 0x0 when MD Type= 0x01.

   All other flag fields are reserved.

   Length: total length, in 4-byte words, of NSH including the Base
   Header, the Service Path Header and the optional variable TLVs.  The
   Length MUST be of value 0x6 for MD Type = 0x1 and MUST be of value
   0x2 or higher for MD Type = 0x2.  The NSH header length MUST be an
   integer number of 4 bytes.

*/

struct nsh_base_hdr
{
   union
   {
       // byte 0
       uint32_t b0;

       struct
       {
           struct
           {
# if __BYTE_ORDER == __LITTLE_ENDIAN
               uint8_t flags_reserved_1:4;
               uint8_t flags_C:1;
               uint8_t flags_O:1;
               uint8_t version:2;

               uint8_t length:6;
               uint8_t flags_reserved_2:2;
# elif __BYTE_ORDER == __BIG_ENDIAN
               uint8_t version:2;
               uint8_t flags_O:1;
               uint8_t flags_C:1;
               uint8_t flags_reserved_1:4;

               uint8_t flags_reserved_2:2;
               uint8_t length:6;
# else
#  error "Could not determine byte order"
# endif
           } __attribute__((__packed__));

           uint8_t md_type;
           uint8_t next_protocol;
       } __attribute__((__packed__));
   }__attribute__((__packed__));
} __attribute__((__packed__));

/* Ethertype for NSH */
#define ETHERTYPE_NSH      0x894F   

#define NSH_MD_TYPE_01 1
#define NSH_MD_TYPE_02 2

#define NSH_NEXT_PROTOCOL_IPV4 1
#define NSH_NEXT_PROTOCOL_IPV6 2
#define NSH_NEXT_PROTOCOL_ETHERNET 3
#define NSH_NEXT_PROTOCOL_NSH  4
#define NSH_NEXT_PROTOCOL_MPLS 5

#define NSH_NEXT_PROTOCOL_EXPERIMENTAL_1 0xFE
#define NSH_NEXT_PROTOCOL_EXPERIMENTAL_2 0xFF

#define NSH_VERSION_MASK 0x3
#define NSH_VERSION_ZERO 0

/* When the Base Header specifies MD Type = 0x1, four Context Headers */
/* 4-byte each, MUST be added immediately following the Service Path  */
/* Header                                                             */
#define NSH_MINIMUM_HEADER_SIZE_WITH_MD_TYPE_01 24

/* When the base header specifies MD Type= 0x2, zero or more Variable */
/* Length Context Headers MAY be added, immediately following the     */
/* Service Path Header                                                */
#define NSH_MINIMUM_HEADER_SIZE_WITH_MD_TYPE_02 8

/*
    Service Path Header

      0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |          Service Path ID                      | Service Index |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

struct nsh_service_hdr
{
    union
    { 
        struct
        {
            uint8_t path_id[3];
            uint8_t service_index;
        };
        uint32_t path_and_service;
    };
}  __attribute__((__packed__));

//! @param nsh_service_hdr service header
//! @return service_index
inline static uint8_t nsh_get_service_index(const struct nsh_service_hdr* service_hdr)
{
    return service_hdr->service_index;
}


//! @param nsh_service_hdr service header
//! @return path_id
inline static uint32_t nsh_get_path_id(const struct nsh_service_hdr* service_hdr)
{
    return (ntohl(service_hdr->path_and_service) >> 8);
}

//! Write SPI and SI to a service header.
//! @param nsh_service_Hdr service header
//! @param path_id path_id to set
//! @param service_index to set
inline static void nsh_set_path_and_service(struct nsh_service_hdr* service_hdr, uint32_t path_id, uint8_t service_index)
{
    service_hdr->path_and_service = htonl((path_id<<8)|service_index);
}

//! Compare two service headers
//! @return bool True if the headers are equal
inline static bool nsh_service_hdrs_equal(struct nsh_service_hdr x, struct nsh_service_hdr y)
{
    return x.path_and_service == y.path_and_service;
}


//! @param nsh_service_Hdr service header
inline static void nsh_service_decrease_service_index(struct nsh_service_hdr* service_hdr)
{
    // service index is uint8, so if service index is already 0, reducing by 1 will set its value to be 255.
    --service_hdr->service_index;
}

/* NSH header with base and service headers, naked context headers
 */
struct nsh_hdr
{
    struct nsh_base_hdr     base_hdr;
    struct nsh_service_hdr  service_hdr;
} __attribute__((__packed__)) ;

//! Initialize a nsh header to default values
//! @param nsh_hdr
//! @param length the length in octetes (in multiple of 4) to set in the header.  This length would include the
//!               the nsh_base, service_hdr as well as context headers
static inline void nsh_initialize( struct nsh_hdr* hdr, uint8_t length, uint8_t md_type, uint8_t next_protocol )
{
    hdr->base_hdr.b0 = 0;

    // length must be multiple of 4 byte words
    assert((length%4) == 0 );

    hdr->base_hdr.length = length/4;
    hdr->base_hdr.md_type = md_type;
    hdr->base_hdr.next_protocol = next_protocol;
    hdr->service_hdr.path_and_service = 0;
}

static inline void nsh_set_next_header(struct nsh_hdr* hdr, uint8_t next_header)
{
    hdr->base_hdr.next_protocol = next_header;
}

static inline uint8_t nsh_get_next_header(const struct nsh_hdr* hdr)
{
    return hdr->base_hdr.next_protocol;
}

static inline unsigned nsh_get_size(const struct nsh_hdr* hdr)
{
    return hdr->base_hdr.length * 4;
}

static inline unsigned nsh_get_version(const struct nsh_hdr* hdr)
{
    return hdr->base_hdr.version;
}

static inline void nsh_set_version(struct nsh_hdr* hdr, uint8_t version)
{
    // version field is 2 bits
    assert(version < 4);
    hdr->base_hdr.version = version;
}

static inline unsigned nsh_get_md_type(const struct nsh_hdr* hdr)
{
    return hdr->base_hdr.md_type;
}

static inline bool nsh_is_oam_packet(const struct nsh_hdr* hdr)
{
    return hdr->base_hdr.flags_O;
}

static inline bool nsh_has_critical_metadata(const struct nsh_hdr* hdr)
{
    return hdr->base_hdr.flags_C;
}

static inline void nsh_decrement_service_index(struct nsh_hdr* hdr)
{
    --hdr->service_hdr.service_index;
}

// See https://tools.ietf.org/html/draft-penno-sfc-packet-03#section-5.4.1
static inline void nsh_algorithmic_reversal(struct nsh_hdr* hdr)
{
    hdr->service_hdr.service_index = 255 - hdr->service_hdr.service_index;
}

inline static uint8_t nsh_get_service_index_from_nsh_header(const struct nsh_hdr * hdr)
{
    return hdr->service_hdr.service_index;
}
inline static struct nsh_service_hdr nsh_get_service_hdr(const struct nsh_hdr * hdr)
{
    return (hdr->service_hdr);
}

inline static void nsh_set_service_hdr(struct nsh_hdr * hdr, struct nsh_service_hdr service_hdr)
{
    hdr->service_hdr = service_hdr;
}

#endif

