#ifndef INTERFACE_COUNT_OPTIONS_H
#define INTERFACE_COUNT_OPTIONS_H

#include <string>
#include <stdint.h>

class InterfaceOptions
{
public:
    InterfaceOptions(int argc, char** argv);

    int GetIfIndex() const;
    const std::string& GetDpdkPciAddress() const;

    //! @ return the number of arguments consumed when processing cmdline
    uint32_t GetNumArgsConsumed() const;

private:
    int m_ifIndex;
    std::string m_dpdkPciAddress;
    uint32_t m_numArgsConsumed;
};

#endif

