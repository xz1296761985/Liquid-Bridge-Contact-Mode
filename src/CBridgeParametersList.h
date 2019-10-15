#if !defined(cbridgeparameterslist_h)
#define cbridgeparameterslist_h

#include <map>
#include <string>

#include "CBridgeParameters.h"

class CBridgeParametersList: public std::map<std::string, CBridgeParameters>
{
    public:
        static const std::string JOIN_STRING;

        void addBridgeParameters(const std::string & key1,
                               const std::string &key2,
                               CBridgeParameters bridgeParameters);

        CBridgeParameters getBridgeParameters(const std::string &key1,
                                          const std::string &key2);

};

#endif