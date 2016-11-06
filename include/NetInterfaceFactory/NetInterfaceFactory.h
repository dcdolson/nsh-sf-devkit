#ifndef NET_INTERFACE_FACTORY_H
#define NET_INTERFACE_FACTORY_H

#include <memory>

namespace nshdev
{
class NetInterface;

class NetInterfaceFactory
{
public:
    //! Creates a net interface from the program args. Modifies the arguments 
    //! to skip passed the consumed arguments.
    //! Note, the format should be along the lines of: 
    //!     <if_creation_args> ... -- <application_args> ...
    static std::unique_ptr<NetInterface> CreateInterfaceFromArgs(int& argc,
                                                                 char**& argv);
};

}
#endif
