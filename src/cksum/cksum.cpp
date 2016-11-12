#include <cksum.h>
#include <stdint.h>
#include <arpa/inet.h>

class checksum
{
public:
    checksum(const uint16_t* words, unsigned nwords)
    {
	m_sum = 0;
	const uint16_t* const end = words + nwords;
	while(words != end)
	{
	    m_sum += *words;
	    ++words;
	}
    }
    void add(const uint16_t* word)
    {
	m_sum += *word;
    }
    void add(const uint32_t* two)
    {
        const uint16_t* words = reinterpret_cast<const uint16_t*>(two);
        m_sum += words[0];
        m_sum += words[1];
    }
    uint16_t get() const
    {
        return m_sum + (m_sum >> 16);
    }
private:
    uint32_t m_sum;
};

uint16_t sum(const uint16_t* words, unsigned nwords)
{
    checksum sum(words, nwords);
    return sum.get();
}

//! make the iphdr have the correct checksum
void cksum_ip4_fix(struct iphdr* ip)
{
    ip->check = 0;
    ip->check = ~sum(reinterpret_cast<uint16_t*>(ip), /*word count*/ ip->ihl * 2);
}

//! Make the tcp header have the correct checksum. The ip header is
//! used for the IP addresses to form the pseudo-header.
void cksum_tcp4_fix(struct tcphdr* tcp, const struct iphdr* ip)
{
    tcp->check = 0;
    checksum sum(reinterpret_cast<uint16_t*>(tcp), /*word count*/(tcp->doff*2));
    sum.add(&ip->saddr);
    sum.add(&ip->daddr);
    uint16_t tcplen_n = htons(ntohs(ip->tot_len) - ip->ihl*4);
    sum.add(&tcplen_n);
    uint8_t proto[2];
    proto[0] = 0;
    proto[1] = ip->protocol;
    sum.add(reinterpret_cast<uint16_t*>(&proto[0]));
    tcp->check = ~sum.get();
}


