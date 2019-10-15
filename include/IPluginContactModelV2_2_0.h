#ifndef IPLUGINCONTACTMODELV2_2_0
#define IPLUGINCONTACTMODELV2_2_0

/***************************************************************************/
/* This header file contains the V2.2.0 plugin contact model API           */
/* definition.  Include this header and PluginContactModelCore.h into      */
/* your plugin project then implement the methods from                     */
/* PluginContactModelCore.h and create a new class derived from            */
/* IPluginContactModelV2_2_0 that implements your desired functionality    */
/***************************************************************************/

// Include ALL required headers.  Do not use forward declarations, this
// makes things easier on the end user
#include "PluginConstants.h"
#include "IPluginContactModel.h"
#include "IApiManager_1_0.h"
#include "ICustomPropertyDataApi_1_0.h"

namespace NApiCm
{
    /**
     * This interface contains all of the methods required to create a
     * contact model plugin.  A new class should be created that derives
     * from this interface and implements its methods. Additionally the
     * methods from the PluginContactModelCore.h file need to be implemented.
     *
     * NAME:              Contact Model Plugin API
     * VERSION:           2.2.0
     * CUSTOM PROPERTIES: Contact, Geometry, Particle, Simulation
     *
     * The methods required by the interface are:
     *
     * calculateForce(...)
     *     does the actual force calculation for a contact.
     *
     * The following additional methods can be over-ridden to change
     * the default implementations:
     *
     * getPreferenceFileName(...)
     *     Returns the name of the config file used by this model (if any).
     *     Default: Indicates that no preference file is used
     *
     * isThreadSafe(...)
     *     Indicates that the plugin's calculateForce(...) method is thread
     *     safe (returns true) or not (returns false).  A thread safe
     *     calculateForce(...) can be called in parallel by threads running
     *     on multiple processors. This can speed up the simulation
     *     processing.
     *     Default: Indicates the plugin is not threadsafe
     *
     * usesCustomProperties(...)
     *     Indicates that the plugin wishes to register and/or receive custom
     *     property data.
     *     Default: Indicates the plugin does not use custom properties
     *
     * setup(...)
     *     Performs any one-off setup and initialization just after the
     *     plugin is loaded.
     *     Default: Performs no work but returns true to indicate plugin
     *              loaded cleanly.
     *
     * starting(...)
     *     Called just before simulation starts to allow API handles to
     *     be acquired, temporary storage allocated, files opened etc.
     *     Default: Performs no work but returns true to indicate plugin
     *              is ready to start processing
     *
     * stopping()
     *     Called just after simulation stops to allow API handles to
     *     be released, temporary storage freed, files closed etc.
     *     Default: Does nothing
     *
     * getNumberOfRequiredProperties(...)
     *     Called by EDEM to query the number of custom properties required
     *     by this plugin to run.
     *     Default: Returns 0 to indicate no properties are required for
     *              any category
     *
     * getDetailsForProperty(...)
     *     Returns the details for the custom properties required for this plugin
     *     to run.
     *     Default: Returns false.
     *
     * If you need per plugin instance data simply add entries to your
     * plugin's class definition as you would with any other C++ class
     * definition.
     */
    class IPluginContactModelV2_2_0 : public IPluginContactModel
    {
        public:
            /**
             * Constructor, does nothing
             */
            IPluginContactModelV2_2_0() {}

            /**
             * Destructor, does nothing
             */
            virtual ~IPluginContactModelV2_2_0() {}

            /**
             * Retrieves the name of the config file used by the plugin.
             *
             * If the plugin does not need a config file then prefFileName
             * should be set to an empty string.
             *
             * @param prefFileName (RETURN VALUE)
             *                     A character array to be populated with the
             *                     config file name. This path is relative to
             *                     the directory the plugin is stored in.
             *                     EDEM will prepend the full directory the plugin
             *                     is stored in and pass it back to the setup method.
             */
            virtual void getPreferenceFileName(char prefFileName[NApi::FILE_PATH_MAX_LENGTH]) {prefFileName[0] = '\0';}

            /**
             * If the plugin implementations calculateForce() method is thread
             * safe then this method should return true.
             *
             * When a plug-in is thread safe, EDEM allows multiple threads
             * to call the plug-in at the same time.  This can speed-up
             * calculations substantially on multi-processor machines.
             *
             * Thread safe programming requires a number of conventions and
             * restrictions to be followed.  If in doubt set this method to return
             * false.
             *
             * @return Bool to indicate if the calculateForce() method is thread
             *         safe
             */
            virtual bool isThreadSafe() {return false;}

            /**
             * Indicates whether the plugin wishes to register or receive custom
             * property data.
             *
             * @return Bool to indicate if custom properties are to be registered
             *         or should be supplied to the calculateForce(...) method.
             */
            virtual bool usesCustomProperties() {return false;}

            /**
             * Initializes the plugin by giving it a chance to read any config
             * files, open temporary files, generate data structures or any other
             * one-off setup work.
             *
             * This method is called once, shortly after the plugin is first loaded.
             * If this method returns false EDEM will immediately delete the plugin
             * and an error message will be reported.
             *
             * IMPORTANT: Plugins should not cache API handles in this
             * method.  See the starting(...) and stopping(...) methods.
             *
             * @param apiManager The api manager for use by plugin models
             * @param prefFile Full path to optional preferences file or empty
             *                 string if none
             * @return Bool to say if setup was a success
             */
            virtual bool setup(NApiCore::IApiManager_1_0& apiManager,
                               const char                 prefFile[]) {return true;}

            /**
             * Called to indicate processing is about to begin and the
             * model should allocate any temporary storage and retrieve any
             * file/api/socket handles it may need.
             *
             * If the method returns false then processing will not start.
             *
             * IMPORTANT: Plugins should only retrieve API handles in this
             * method. API handles may change between one processing
             * run and another. Attempting to keep and re-use handles
             * will cause system instability.
             *
             * @param apiManager The api manager for use by plugin models
             * @return true if model is ready to start, else false
             */
            virtual bool starting(NApiCore::IApiManager_1_0& apiManager) {return true;}

            /**
             * Called to indicate processing is finished and that
             * the model should free any temporary storage and close/release
             * file/api/socket handles.
             *
             * The implementation must be able to handle this method being
             * called multiple times in a row without intervening calls
             * to starting.  This can occur when one or more loaded models
             * abort processing.
             *
             * IMPORTANT: Plugins must release all API handles in this
             * method.  API handles may change between one processing
             * run and another.  Attempting to keep and re-use handles
             * will cause system instability.
             */
            virtual void stopping(NApiCore::IApiManager_1_0& apiManager) {};

            /**
             * This function is called when two elements are in contact with
             * each other.
             *
             * These elements can be two surfaces or a surface and a geometry
             * element.  For two surfaces, the function is called when their
             * contact radii cross.  For a surface and a geometry, the
             * function is called when the contact radius of the surface
             * touches the geometry.
             *
             * Element 1 is always a surface, element 2 can be either another
             * surface or a geometry element.
             *
             * @param time
             *            Current time
             * @param timestep
             *            Length of timestep used in simulation
             * @param elem1Id
             *            The id of the element
             * @param elem1Type
             *            Name of the particle template this surface was created
             *            from if elem1IsSurf is true or the name of the geometry
             *            section if elem1IsSurf is true
             * @param elem1Mass
             *            The mass of the parent particle if elem1IsSurf is true,
             *            otherwise a large number (usually 1e8) if elem1IsSurf
             *            is false.
             * @param elem1ShearMod
             *            The shear modulus of the element
             * @param elem1Poisson
             *            Poisson's ratio of the element
             * @param elem1ContactCurvature
             *            The local contact curvature of the element at the
             *            contact point
             * @param elem1PhysicalCurvature
             *            The local physical curvature of the element at the
             *            contact point
             * @param elem1PosX
             *            X coordinate of the centroid of the element (NOT
             *            necessarily the particle)
             * @param elem1PosY
             *            Y coordinate of the centroid of the element (NOT
             *            necessarily the particle)
             * @param elem1PosZ
             *            Z coordinate of the centroid of the element (NOT
             *            necessarily the particle)
             * @param elem1ComX
             *            X coordinate of the centre of mass of the particle
             * @param elem1ComY
             *            Y coordinate of the centre of mass of the particle
             * @param elem1ComZ
             *            Z coordinate of the centre of mass of the particle
             * @param elem1VelX
             *            X component of velocity the element at the contact point
             * @param elem1VelY
             *            Y component of velocity the element at the contact point
             * @param elem1VelZ
             *            Z component of velocity the element at the contact point
             * @param elem1AngVelX
             *            X component of angular velocity of the element
             * @param elem1AngVelY
             *            Y component of angular velocity of the element
             * @param elem1AngVelZ
             *            Z component of angular velocity of the element
             * @param elem1Charge
             *            Charge of the element
             * @param elem1WorkFunction
             *            Work function of the element
             * @param elem1Orientation
             *            Nine-element array containing the orientation matrix for
             *            this element.
             *            The elements of the array are in the following order:
             *                XX, XY, XZ, YX, YY, YZ, ZX, ZY, ZZ
             * @param elem1PropData
             *            Versioned interface providing access to element one's
             *            custom property data and corresponding changeset
             * @param elem2IsSurf
             *            True if the element is a surface, false if not
             * @param elem2Id
             *            As elem1Id but for element 2
             * @param elem2Type
             *            As elem1Type but for element 2
             * @param elem2Mass
             *            As elem1Mass but for element 2
             * @param elem2Area
             *            If elem2IsSurf is false then elem 2 is a geometry element.
             *            This value gives the surface area of that element.
             * @param elem2ShearMod
             *            As elem1ShearMod but for element 2
             * @param elem2Poisson
             *            As elem1Poisson but for element 2
             * @param elem2ContactCurvature
             *            As elem1ContactCurvature but for element 2
             * @param elem2PhysicalCurvature
             *            As elem1PhysicalCurvature but for element 2
             * @param elem2PosX
             *            As elem1PosX but for element 2
             * @param elem2PosY
             *            As elem1PosY but for element 2
             * @param elem2PosZ
             *            As elem1PosZ but for element 2
             * @param elem2ComX
             *            X coordinate of the centre of mass of the particle
             *            or if element is geometry the same as elem2PosX
             * @param elem2ComY
             *            Y coordinate of the centre of mass of the particle
             *            or if element is geometry the same as elem2PosY
             * @param elem2ComZ
             *            Z coordinate of the centre of mass of the particle
             *            or if element is geometry the same as elem2PosZ
             * @param elem2VelX
             *            As elem1VelX but for element 2
             * @param elem2VelY
             *            As elem1VelY but for element 2
             * @param elem2VelZ
             *            As elem1VelZ but for element 2
             * @param elem2AngVelX
             *            As elem1AngVelX but for element 2
             * @param elem2AngVelY
             *            As elem1AngVelY but for element 2
             * @param elem2AngVelZ
             *            As elem1AngVelZ but for element 2
             * @param elem2Charge
             *            As elem1Charge but for element 2
             * @param elem2WorkFunction
             *            As elem1WorkFunction but for element 2
             * @param elem2Orientation
             *            As elem1Orientation but for element 2
             * @param elem2PropData
             *            As elem1PropData but for element 2
             * @param contactPropData
             *            Versioned interface providing access to custom
             *            property data and a corresponding changeset for the
             *            contact
             * @param simulationPropData
             *            Versioned interface providing access to custom
             *            property data and corresponding changeset for the
             *            simulation
             * @param coeffRest
             *            Coefficient of restitution
             * @param staticFriction
             *            Coefficient of static friction
             * @param rollingFriction
             *            Coefficient of rolling friction
             * @param contactPointX
             *            X coordinate of the location of the centroid of the contact
             * @param contactPointY
             *            Y coordinate of the location of the centroid of the contact
             * @param contactPointZ
             *            Z coordinate of the location of the centroid of the contact
             * @param normalPhysicalOverlap
             *            Magnitude of the normal physical overlap
             * @param tangentialPhysicalOverlapX
             *            (INPUT AND RETURN VALUE)
             *            X component of the tangential physical overlap.
             *            The contact model is allowed to change the value of the tangential physical overlap
             * @param tangentialPhysicalOverlapY
             *            (INPUT AND RETURN VALUE)
             *            Y component of the tangential physical overlap.
             *            The contact model is allowed to change the value of the tangential physical overlap
             * @param tangentialPhysicalOverlapZ
             *            (INPUT AND RETURN VALUE)
             *            Z component of the tangential physical overlap.
             *            The contact model is allowed to change the value of the tangential physical overlap
             * @param calculatedNormalForceX
             *            (RETURN VALUE)
             *            X component of normal force on element 1
             *            From Newton III the normal force on element 2 is equal and opposite.
             * @param calculatedNormalForceY
             *            (RETURN VALUE)
             *            Y component of normal force on element 1
             *            From Newton III the normal force on element 2 is equal and opposite.
             * @param calculatedNormalForceZ
             *            (RETURN VALUE)
             *            Z component of normal force on element 1
             *            From Newton III the normal force on element 2 is equal and opposite.
             * @param calculatedUnsymNormalForceX
             *            (RETURN VALUE)
             *            X component of the unsymmetrical normal forces on
             *            element 1. This represent the portion of the calculated
             *            normal force that causes energy loss / gain (eg damping).
             * @param calculatedUnsymNormalForceY
             *            (RETURN VALUE)
             *            Y component of the unsymmetrical normal forces on
             *            element 1. This represent the portion of the calculated
             *            normal force that causes energy loss / gain (eg damping).
             * @param calculatedUnsymNormalForceZ
             *            (RETURN VALUE)
             *            Z component of the unsymmetrical normal forces on
             *            element 1. This represent the portion of the calculated
             *            normal force that causes energy loss / gain (eg damping).
             * @param calculatedTangentialForceX
             *            (RETURN VALUE)
             *            X component of tangential force on element 1
             *            From Newton III the normal force on element 2 is equal and opposite.
             * @param calculatedTangentialForceY
             *            (RETURN VALUE)
             *            Y component of tangential force on element 1
             *            From Newton III the normal force on element 2 is equal and opposite.
             * @param calculatedTangentialForceZ
             *            (RETURN VALUE)
             *            Z component of tangential force on element 1
             *            From Newton III the normal force on element 2 is equal and opposite.
             * @param calculatedUnsymTangentialForceX
             *            (RETURN VALUE)
             *            X component of the unsymmetrical tangential forces on
             *            element 1. This represent the portion of
             *            calculatedTangentialForceX that causes energy
             *            loss / gain (eg damping).
             * @param calculatedUnsymTangentialForceY
             *            (RETURN VALUE)
             *            Y component of the unsymmetrical tangential forces on
             *            element 1. This represent the portion of
             *            calculatedTangentialForceY that causes energy
             *            loss / gain (eg damping).
             * @param calculatedUnsymTangentialForceZ
             *            (RETURN VALUE)
             *            Z component of the unsymmetrical tangential forces on
             *            element 1. This represent the portion of
             *            calculatedTangentialForceZ that causes energy
             *            loss / gain (eg damping).
             * @param calculatedElem1AdditionalTorqueX
             *            (RETURN VALUE)
             *            X coordinate of any additional torque on element 1 not
             *            accounted  for by the above forces (which are deemed to
             *            act at the contact point). These can be useful, for of
             *            example, in a consideration rolling friction.
             * @param calculatedElem1AdditionalTorqueY
             *            (RETURN VALUE)
             *            Y coordinate of any additional torque on element 1 not
             *            accounted  for by the above forces (which are deemed to
             *            act at the contact point). These can be useful, for of
             *            example, in a consideration rolling friction.
             * @param calculatedElem1AdditionalTorqueZ
             *            (RETURN VALUE)
             *            Z coordinate of any additional torque on element 1 not
             *            accounted  for by the above forces (which are deemed to
             *            act at the contact point). These can be useful, for of
             *            example, in a consideration rolling friction.
             * @param calculatedElem1UnsymAdditionalTorqueX
             *            (RETURN VALUE)
             *            X coordinate of any unsymmetrical, additional torque
             *            on element 1 not accounted for by the above forces.
             *            These represent the component of the additional torque
             *            that causes energy loss / gain (eg damping).
             * @param calculatedElem1UnsymAdditionalTorqueY
             *            (RETURN VALUE)
             *            Y coordinate of any unsymmetrical, additional torque
             *            on element 1 not accounted for by the above forces.
             *            These represent the component of the additional torque
             *            that causes energy loss / gain (eg damping).
             * @param calculatedElem1UnsymAdditionalTorqueZ
             *            (RETURN VALUE)
             *            Z coordinate of any unsymmetrical, additional torque
             *            on element 1 not accounted for by the above forces.
             *            These represent the component of the additional torque
             *            that causes energy loss / gain (eg damping).
             * @param calculatedElem2AdditionalTorqueX
             *            (RETURN VALUE)
             *            X coordinate of any additional torque on element 2 not
             *            accounted  for by the above forces (which are deemed to
             *            act at the contact point). These can be useful, for of
             *            example, in a consideration rolling friction.
             * @param calculatedElem2AdditionalTorqueY
             *            (RETURN VALUE)
             *            Y coordinate of any additional torque on element 2 not
             *            accounted  for by the above forces (which are deemed to
             *            act at the contact point). These can be useful, for of
             *            example, in a consideration rolling friction.
             * @param calculatedElem2AdditionalTorqueZ
             *            (RETURN VALUE)
             *            Z coordinate of any additional torque on element 2 not
             *            accounted  for by the above forces (which are deemed to
             *            act at the contact point). These can be useful, for of
             *            example, in a consideration rolling friction.
             * @param calculatedElem2UnsymAdditionalTorqueX
             *            (RETURN VALUE)
             *            X coordinate of any unsymmetrical, additional torque
             *            on element 2 not accounted for by the above forces.
             *            These represent the component of the additional torque
             *            that causes energy loss / gain (eg damping).
             * @param calculatedElem2UnsymAdditionalTorqueY
             *            (RETURN VALUE)
             *            Y coordinate of any unsymmetrical, additional torque
             *            on element 2 not accounted for by the above forces.
             *            These represent the component of the additional torque
             *            that causes energy loss / gain (eg damping).
             * @param calculatedElem2UnsymAdditionalTorqueZ
             *            (RETURN VALUE)
             *            Z coordinate of any unsymmetrical, additional torque
             *            on element 2 not accounted for by the above forces.
             *            These represent the component of the additional torque
             *            that causes energy loss / gain (eg damping).
             * @param calculatedChargeMovedToElem1
             *            (RETURN VALUE)
             *            The amount of charge moved from element 2 to element 1
             *            (if negative charge moves from element 1 to 2
             * @return enum value to indicate function result
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
                                               double       normalPhysicalOverlap,
                                               double&      tangentialPhysicalOverlapX,
                                               double&      tangentialPhysicalOverlapY,
                                               double&      tangentialPhysicalOverlapZ,
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
                                               double&      calculatedChargeMovedToElem1) = 0;

            /**
             * Returns the number of custom properties this plugin wants to
             * register with the system for the supplied category.
             *
             * This version of the API supports the following property
             * categories:
             *     Contact Properties
             *     Geometry Properties
             *     Particle Properties
             *     Simulation Properties
             *
             * The method will be called once for each category at load time.
             * The implementation should return how many properties of that
             * category it wishes to register.
             *
             * If the plugin does not use custom properties this method should
             * return 0 for all categories.
             *
             * @param category The category of the custom property.
             * @return The number of custom properties the plugin wishes to
             *         register.
             */
            virtual unsigned int getNumberOfRequiredProperties(
                                     const NApi::EPluginPropertyCategory category) {return 0;}

            /**
             * Retrieves details for a given property.  This method will be
             * called for each category for propertyIndex values
             * 0...(getNumberOfRequiredProperties(category) - 1) to retrieve
             * the details for that property from the plugin.  These properties
             * will then be registered with the system if they do not clash
             * with any existing properties.
             *
             * This version of the API supports the following property
             * categories:
             *     Contact Properties
             *     Geometry Properties
             *     Particle Properties
             *     Simulation Properties
             *
             * If the plugin does not use custom properties this method should
             * always return false.
             *
             * @param propertyIndex    The index of the property to retrieve data
             *                         for
             * @param category         The category of the custom property to return
             *                         details for.
             * @param name             (RETURN VALUE)
             *                         A CUSTOM_PROP_MAX_NAME_LENGTH char array
             *                         is supplied to be populated with the name
             *                         of the property
             * @param dataType         (RETURN VALUE)
             *                         The data type of the property should allways
             *                         be set to eDouble
             * @param numberOfElements (RETURN VALUE)
             *                         The number of elements (min 1)
             * @param unitType         (RETURN VALUE)
             *                         The unit type of the property
             * @return bool to say if data exists for the property
             */
            virtual bool getDetailsForProperty(
                             unsigned int                    propertyIndex,
                             NApi::EPluginPropertyCategory   category,
                             char                            name[NApi::CUSTOM_PROP_MAX_NAME_LENGTH],
                             NApi::EPluginPropertyDataTypes& dataType,
                             unsigned int&                   numberOfElements,
                             NApi::EPluginPropertyUnitTypes& unitType) {return false;}
    };
};

#endif // IPLUGINCONTACTMODELV2_2_0

