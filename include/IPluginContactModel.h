#ifndef IPLUGINCONTACTMODEL
#define IPLUGINCONTACTMODEL

#include "ApiTypes.h"

/**
 * The NApiCm namespace contains all interfaces related
 * to creating Contact Model plugins.
 *
 * Pick one of the versioned interfaces (e.g. IPluginContactModelV2_0_0)
 * and implement all of its methods as required.  Also implement the
 * methods declared in PluginContactModelCore.h to enable EDEM to load
 * and access the plugin instance.
 */
namespace NApiCm
{
    /**
     * Base class for all plugin contact models.  This class
     * lets us abstractly group all plugin contact models together
     * and determine their type by dynamic_cast operators.
     */
    class IPluginContactModel
    {
    public:
        /**
         * Constructor, does nothing
         */
        IPluginContactModel() {}

        /**
         * Destructor, does nothing
         */
        virtual ~IPluginContactModel() {}
    };
};

#endif // IPLUGINCONTACTMODEL

