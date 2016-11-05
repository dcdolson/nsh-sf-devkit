#include <Dpdk/DpdkSetup.h>
#include <string.h>
#include <stdio.h>

extern "C"
{
#include <rte_common.h>
#include <rte_config.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
}

namespace nshdev
{

struct rte_mempool * nshdev_pktmbuf_pool = nullptr;

constexpr uint32_t NB_MBUF = 8192;
constexpr uint32_t MEMPOOL_CACHE_SIZE = 32;

uint32_t DpdkSetup(int argc, char **argv)
{
    int ret = rte_eal_init(argc, argv);

    if(ret < 0)
    {
        return 0;
    }

    struct rte_eth_conf port_conf;
    memset(&port_conf, 0, sizeof(port_conf));
    
    
    port_conf.txmode.mq_mode = ETH_MQ_TX_NONE;

    nshdev_pktmbuf_pool = rte_pktmbuf_pool_create("mbuf_pool",
                                                  NB_MBUF,
                                                  MEMPOOL_CACHE_SIZE,
                                                  0,
                                                  RTE_MBUF_DEFAULT_BUF_SIZE,
                                                  rte_socket_id());


    if(nshdev_pktmbuf_pool == nullptr)
    {
        fprintf(stderr, "Error initializing mbuf pool. Have you allocted enough hugepages?\n");
        return 0;
    }
    
    uint8_t numPorts = rte_eth_dev_count();
    if(numPorts < 1)
    {
        fprintf(stderr, "No interfaces provisioned. Please provision an interface.\n");
        return 0;
    }

    for(uint8_t port = 0; port < numPorts; ++port)
    {
        ret = rte_eth_dev_configure(port, 1, 1, &port_conf);
        if(ret < 0)
        {
            fprintf(stderr, "Failed to configure port %u\n", port);
            return 0;
        }

        ret = rte_eth_rx_queue_setup(port, 0, 128,
                                     rte_eth_dev_socket_id(port),
                                     NULL,
                                     nshdev_pktmbuf_pool);
        if(ret < 0)
        {
            fprintf(stderr, "Failed to setup rx queue for port %u\n", port);
            return 0;
        }

        ret = rte_eth_tx_queue_setup(port, 0, 256,
                                     rte_eth_dev_socket_id(port),
                                     NULL);
        if(ret < 0)
        {
            fprintf(stderr, "Failed to setup tx queue for port %u\n", port);
            return 0;
        }

        if(rte_eth_dev_start(port) < 0)
        {
            fprintf(stderr, "Failed to start port %u\n", port);
            return 0;
        }
    }

    return numPorts;
    
}

}
