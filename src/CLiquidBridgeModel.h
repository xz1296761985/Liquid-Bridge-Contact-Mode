#if !defined(CLiquidBridgeModel_h)
#define CLiquidBridgeModel_h

#include <string>
#include <fstream>

#include "IPluginContactModelV2_2_0.h"
#include "CBridgeParametersList.h"

using namespace std;

/**
 * This class provides an implementation of IPluginContactModelV2_2_0
 */

/******
 * NOTE: In this empty example, CLiquidBridgeModel is derived from 
 * IPluginContactModelV2_0_0. If you want to change the name
 * of this class, search and replace "CLiquidBridgeModel" for all 
 * files in the project
 ******/


class CLiquidBridgeModel : public NApiCm::IPluginContactModelV2_2_0
{
    public:

        /**
         * Constructor, does nothing
         */
        CLiquidBridgeModel();

        /**
         * Destructor, does nothing
         */
        virtual ~CLiquidBridgeModel();

        /**
         * Sets prefFileName to the empty string as this plugin has no
         * configuration
         *
         * Implementation of method from IPluginContactModelV2_2_0
         */
        virtual void getPreferenceFileName(char prefFileName[NApi::FILE_PATH_MAX_LENGTH]);

        /**
         * Returns true to indicate plugin is thread safe
         *
         * Implementation of method from IPluginContactModelV2_2_0
         */
        virtual bool isThreadSafe();

        /**
         * Returns true to indicate the plugin uses custom properties
         *
         * Implementation of method from IPluginContactModelV2_2_0
         */
        virtual bool usesCustomProperties();

        /**
         * Does nothing
         *
         * Implementation of method from IPluginContactModelV2_2_0
         */
        virtual bool setup(NApiCore::IApiManager_1_0& apiManager, const char prefFile[]);

        /**
         * Does nothing
         *
         * Implementation of method from IPluginContactModelV2_2_0
         */
        virtual bool starting(NApiCore::IApiManager_1_0& apiManager);


        /**
         * Does nothing
         *
         * Implementation of method from IPluginContactModelV2_2_0
         */
        virtual void stopping(NApiCore::IApiManager_1_0& apiManager);

        /**
         *
         *
         * Implementation of method from IPluginContactModelV2_2_0
         */
        virtual NApi::ECalculateResult calculateForce(
                                           double       time,
                                           double       timestep,
                                           int          elem1Id,
                                           const char   elem1Type[],
                                           double       elem1Mass,
                                           double       elem1ShearMod,
                                           double       elem1Poisson,
                                           double       elem1ContactCurvature,
                                           double       elem1PhysicalCurvature,
                                           double       elem1PosX,
                                           double       elem1PosY,
                                           double       elem1PosZ,
                                           double       elem1ComX,
                                           double       elem1ComY,
                                           double       elem1ComZ,
                                           double       elem1VelX,
                                           double       elem1VelY,
                                           double       elem1VelZ,
                                           double       elem1AngVelX,
                                           double       elem1AngVelY,
                                           double       elem1AngVelZ,
                                           double       elem1Charge,
                                           double       elem1WorkFunction,
                                           const double elem1Orientation[9],
                                           NApiCore::ICustomPropertyDataApi_1_0* elem1PropData,
                                           bool         elem2IsSurf,
                                           int          elem2Id,
                                           const char   elem2Type[],
                                           double       elem2Mass,
                                           double       elem2Area,
                                           double       elem2ShearMod,
                                           double       elem2Poisson,
                                           double       elem2ContactCurvature,
                                           double       elem2PhysicalCurvature,
                                           double       elem2PosX,
                                           double       elem2PosY,
                                           double       elem2PosZ,
                                           double       elem2ComX,
                                           double       elem2ComY,
                                           double       elem2ComZ,
                                           double       elem2VelX,
                                           double       elem2VelY,
                                           double       elem2VelZ,
                                           double       elem2AngVelX,
                                           double       elem2AngVelY,
                                           double       elem2AngVelZ,
                                           double       elem2Charge,
                                           double       elem2WorkFunction,
                                           const double elem2Orientation[9],
                                           NApiCore::ICustomPropertyDataApi_1_0* elem2PropData,
                                           NApiCore::ICustomPropertyDataApi_1_0* contactPropData,
                                           NApiCore::ICustomPropertyDataApi_1_0* simulationPropData,
                                           double       coeffRest,
                                           double       staticFriction,
                                           double       rollingFriction,
                                           double       contactPointX,
                                           double       contactPointY,
                                           double       contactPointZ,
                                           double       normalOverlap,
                                           double&      tangentialOverlapX,
                                           double&      tangentialOverlapY,
                                           double&      tangentialOverlapZ,
                                           double&      calculatedNormalForceX,
                                           double&      calculatedNormalForceY,
                                           double&      calculatedNormalForceZ,
                                           double&      calculatedUnsymNormalForceX,
                                           double&      calculatedUnsymNormalForceY,
                                           double&      calculatedUnsymNormalForceZ,
                                           double&      calculatedTangentialForceX,
                                           double&      calculatedTangentialForceY,
                                           double&      calculatedTangentialForceZ,
                                           double&      calculatedUnsymTangentialForceX,
                                           double&      calculatedUnsymTangentialForceY,
                                           double&      calculatedUnsymTangentialForceZ,
                                           double&      calculatedElem1AdditionalTorqueX,
                                           double&      calculatedElem1AdditionalTorqueY,
                                           double&      calculatedElem1AdditionalTorqueZ,
                                           double&      calculatedElem1UnsymAdditionalTorqueX,
                                           double&      calculatedElem1UnsymAdditionalTorqueY,
                                           double&      calculatedElem1UnsymAdditionalTorqueZ,
                                           double&      calculatedElem2AdditionalTorqueX,
                                           double&      calculatedElem2AdditionalTorqueY,
                                           double&      calculatedElem2AdditionalTorqueZ,
                                           double&      calculatedElem2UnsymAdditionalTorqueX,
                                           double&      calculatedElem2UnsymAdditionalTorqueY,
                                           double&      calculatedElem2UnsymAdditionalTorqueZ,
                                           double&      calculatedChargeMovedToElem1);

   /**
         * Returns 0
         *
         * Implementation of method from IPluginContactModelV2_2_0
         */
        virtual unsigned int getNumberOfRequiredProperties(
                                     const NApi::EPluginPropertyCategory category);
        /**
         * Does nothing
         *
         * Implementation of method from IPluginContactModelV2_2_0
         */
        virtual bool getDetailsForProperty(
                         unsigned int                    propertyIndex,
  					     NApi::EPluginPropertyCategory   category,
                         char                            name[NApi::CUSTOM_PROP_MAX_NAME_LENGTH],
                         NApi::EPluginPropertyDataTypes& dataType,
                         unsigned int&                   numberOfElements,
                         NApi::EPluginPropertyUnitTypes& unitType);

         
		/**
		 * Declare a string for the the preferences file name
		 */
        static const string PREFS_FILE;

		static const std::string LIQUID_CONTENT;
        static const std::string BRIDGE_STATUS;
		static const std::string BRIDGE_FORCE; 


		private:
			double              t_start_cohesion;
			double				m_liqRho;
			CBridgeParametersList m_bridgeParameters;

};

#endif
