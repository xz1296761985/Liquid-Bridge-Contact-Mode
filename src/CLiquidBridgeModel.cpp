#include "CLiquidBridgeModel.h"

#include "Helpers.h"
#include <string>

using namespace NApi;
using namespace NApiCore;
using namespace NApiCm;

// Add the name for the preference file custom properties
const string CLiquidBridgeModel::PREFS_FILE = "Liquid_Bridge_prefs.txt";
const string CLiquidBridgeModel::BRIDGE_STATUS = "BridgeStatus";
const string CLiquidBridgeModel::BRIDGE_FORCE = "BridgeForce";
const string CLiquidBridgeModel::LIQUID_CONTENT = "Liquid Content";




CLiquidBridgeModel::CLiquidBridgeModel()
{
	// Does nothing here
    ;
}

CLiquidBridgeModel::~CLiquidBridgeModel()
{
	// Does nothing here
    ;
}

void CLiquidBridgeModel::getPreferenceFileName(char prefFileName[FILE_PATH_MAX_LENGTH])
{
    // Copy in the name of the preference file	  
	strcpy(prefFileName, PREFS_FILE.c_str());
}

bool CLiquidBridgeModel::isThreadSafe()
{
    // Thread safe
    return true;
}

bool CLiquidBridgeModel::usesCustomProperties()
{
    // Use custom properties
    return true;
}

bool CLiquidBridgeModel::setup(NApiCore::IApiManager_1_0& apiManager, const char  prefFile[])
{
	// Read in the preference file
    ifstream prefsFile(prefFile);

    if(!prefsFile)
	{return false;}
    else
    {
		string str;
		string description;
		double nliqGamma, nliqWettingAngle;
		prefsFile >> description >> t_start_cohesion;
		prefsFile >> description >> m_liqRho;
		prefsFile >> description >> description >> description;
        while (prefsFile)
        {
			// Read value from preference file
            prefsFile >> str >> nliqGamma >> nliqWettingAngle;
			
			string::size_type i (str.find (':')); // find position of symbol ':'
			string surfA = str.substr (0, i); // Extract substring for surfA
			str.erase (0, i + 1); // Erase the first substring
			string surfB = str; // Extract substring for surfB

			// Add bridge parameter to the list
			m_bridgeParameters.addBridgeParameters(surfA,
											   surfB,
											   CBridgeParameters(nliqGamma,
															   nliqWettingAngle));
        }
		return true;
    }	
}

bool CLiquidBridgeModel::starting(NApiCore::IApiManager_1_0& apiManager)
{
    return true;
}

void CLiquidBridgeModel::stopping(NApiCore::IApiManager_1_0& apiManager)
{
    ;
}

NApi::ECalculateResult CLiquidBridgeModel::calculateForce(
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
                                   double&      calculatedChargeMovedToElem1)
{


	// Get values of particle custom properties
	const double* LiquidContentValue1 = elem1PropData->getValue(LIQUID_CONTENT.c_str());
	const double* LiquidContentValue2 = elem2PropData->getValue(LIQUID_CONTENT.c_str());
	
	// Get values of the contact custom properties
	const double* m_BridgeStatus = contactPropData->getValue(BRIDGE_STATUS.c_str());
	double* m_BridgeStatusDelta  = contactPropData->getDelta(BRIDGE_STATUS.c_str()); 
	const double* m_BridgeForce = contactPropData->getValue(BRIDGE_FORCE.c_str());
	double* m_BridgeForceDelta  = contactPropData->getDelta(BRIDGE_FORCE.c_str()); 
	
	/* Create vectors */
	CSimple3DVector relVel = CSimple3DVector(elem1VelX,elem1VelY,elem1VelZ) - CSimple3DVector(elem2VelX,elem2VelY,elem2VelZ);
	CSimple3DVector vel1 = CSimple3DVector(elem1VelX,elem1VelY,elem1VelZ);
	CSimple3DVector vel2= CSimple3DVector(elem2VelX,elem2VelY,elem2VelZ);
	CSimple3DVector angVel1(elem1AngVelX,elem1AngVelY,elem1AngVelZ);
	CSimple3DVector angVel2(elem2AngVelX,elem2AngVelY,elem2AngVelZ);

	/* Create points */
	CSimple3DPoint contactPoint = CSimple3DPoint(contactPointX,contactPointY,contactPointZ);
    
	// The unit vector from element 1 to the contact point
    CSimple3DVector unitCPVect = contactPoint - CSimple3DPoint(elem1PosX, elem1PosY, elem1PosZ) ;
    unitCPVect.normalise();

	// Dimensionless distance between the 2 particles, liquid bridge radius, liquid volume from particle 1, liquid volume from particle 2
	double sPrime, liqRadius, liqVolumeSurf1, liqVolumeSurfSurf1, liqVolumeSurf2;
    
	// Dimensionless liquid bridge volume
	double liqVolumeStar;
	double aValue, bValue, cValue; // Parameters for capillary force model from Mikami et al. 1998.
	double ruptureDistance; // Distance at which rupture of the liquid bridge occurs

	/* Bridge variables - set them to false*/
	bool bridgeExists = false, bridgeBroken = false, newBridge = false; 

    // Clear return values
    calculatedNormalForceX = 0.0;
    calculatedNormalForceY = 0.0;
    calculatedNormalForceZ = 0.0;
    calculatedUnsymNormalForceX = 0.0;
    calculatedUnsymNormalForceY = 0.0;
    calculatedUnsymNormalForceZ = 0.0;
    calculatedTangentialForceX = 0.0;
    calculatedTangentialForceY = 0.0;
    calculatedTangentialForceZ = 0.0;
    calculatedUnsymTangentialForceX = 0.0;
    calculatedUnsymTangentialForceY = 0.0;
    calculatedUnsymTangentialForceZ = 0.0;
    calculatedElem1AdditionalTorqueX = 0.0;
    calculatedElem1AdditionalTorqueY = 0.0;
    calculatedElem1AdditionalTorqueZ = 0.0;
    calculatedElem1UnsymAdditionalTorqueX = 0.0;
    calculatedElem1UnsymAdditionalTorqueY = 0.0;
    calculatedElem1UnsymAdditionalTorqueZ = 0.0;
    calculatedElem2AdditionalTorqueX = 0.0;
    calculatedElem2AdditionalTorqueY = 0.0;
    calculatedElem2AdditionalTorqueZ = 0.0;
    calculatedElem2UnsymAdditionalTorqueX = 0.0;
    calculatedElem2UnsymAdditionalTorqueY = 0.0;
    calculatedElem2UnsymAdditionalTorqueZ = 0.0;
    calculatedChargeMovedToElem1 = 0.0;

	 // Normal and tangential components of the relative velocity at the contact point
    CSimple3DVector relVel_n = unitCPVect * unitCPVect.dot(relVel);
    CSimple3DVector relVel_t = relVel - relVel_n;

    // Equivalent radii & mass
    double nEquivRadius =  elem1PhysicalCurvature * elem2PhysicalCurvature /
        (elem1PhysicalCurvature + elem2PhysicalCurvature);

    double nEquivMass = elem1Mass * elem2Mass /
        (elem1Mass + elem2Mass);

    // Effective Young's Modulus
    double nYoungsMod1 = 2 * (1.0 + elem1Poisson) * elem1ShearMod;
    double nYoungsMod2 = 2 * (1.0 + elem2Poisson) * elem2ShearMod;

    // Equivalent Young's & shear modulus
    double nEquivYoungsMod =  ( 1 - pow(elem1Poisson, 2) ) / nYoungsMod1
        + ( 1 - pow(elem2Poisson, 2) ) / nYoungsMod2;

    nEquivYoungsMod = 1.0 / nEquivYoungsMod;

    double nEquivShearMod =   ( 2.0 - elem1Poisson ) /  elem1ShearMod
        + ( 2.0 - elem2Poisson ) /  elem2ShearMod;

    nEquivShearMod = 1.0 / nEquivShearMod;

	CBridgeParameters bridgeParams = m_bridgeParameters.getBridgeParameters(elem1Type, elem2Type);

	/************************************************************************************/
	/* Calculate characteristic radius, liquid bridge volume and rupture distance       */
	/************************************************************************************/

	if(elem2IsSurf) // Check to see if it is a particle-particle contact
	{
		/* Define characteristic radius from Derjaguin approximation as defined in Willet et al., 2000, Langmuir */
		liqRadius = 2.0*nEquivRadius;

		/* Calculate dimensionless volume from liquid volume in each particle from Shi and McCarthy, Powder Tech  2008*/
		liqVolumeSurf1 = (0.01 * *LiquidContentValue1 * elem1Mass / m_liqRho /2.0) * (1 - sqrt( 1 - ( pow(elem2PhysicalCurvature,2)/pow((elem1PhysicalCurvature + elem2PhysicalCurvature),2))));
		liqVolumeSurf2 = (0.01 * *LiquidContentValue2 * elem2Mass / m_liqRho /2.0) * (1 - sqrt( 1 - ( pow(elem1PhysicalCurvature,2)/pow((elem1PhysicalCurvature + elem2PhysicalCurvature),2))));

		liqVolumeStar = (liqVolumeSurf1 + liqVolumeSurf2) / pow(liqRadius, 3.0);

		/*Rupture distance */

		ruptureDistance = liqRadius * (0.99 + 0.62 * bridgeParams.m_nLiqWettingAngle) * pow( liqVolumeStar , 0.34 ); /*From Mikami et al 1998*/
	}
	 else
	 {
		 liqRadius = elem1PhysicalCurvature;

		 /*Calculate dimensionless volume from liquid volume in each particle from Shi and McCarthy, Powder Tech  2008*/
		 //liqVolumeSurf1 = (*LiquidContentValue1 / m_liqRho /2) * (1 - sqrt( 1 - ( pow( elem1PhysicalCurvature , 2 )/pow( (elem1PhysicalCurvature + elem1PhysicalCurvature), 2))));
		 liqVolumeSurf1 = (0.01 * *LiquidContentValue1 *elem1Mass / m_liqRho /2.0) * (1 - sqrt(3.0/4.0));
		 //liqVolumeSurf2 = 0;

		 liqVolumeStar = liqVolumeSurf1/ pow(liqRadius, 3.0);

		 /*Rupture distance */

		 ruptureDistance = liqRadius * (0.95 + 0.22 * bridgeParams.m_nLiqWettingAngle) * pow( liqVolumeStar , 0.32 ); /*From Mikami et al 1998*/

	 }


    /*****************************/
    /* Normal Calculation        */
    /*****************************/
	CSimple3DVector F_n;
	CSimple3DVector F_nd;
	//B value used for both normal and tangential damping
	double B=0.0;
	if(normalPhysicalOverlap > 0.0)
	{
    // Normal spring constant and normal force
    double K_n   = 4.0 / 3.0 * nEquivYoungsMod * sqrt(nEquivRadius);
    F_n  = - unitCPVect * K_n * pow(normalPhysicalOverlap, 1.5);

    // Damping calculation
	
    if(coeffRest > 0.0)
    {
        double myLog = log(coeffRest);
        B = - myLog/ sqrt(myLog * myLog + PI * PI);
    }

    double S_n = 2.0 * nEquivYoungsMod * sqrt(nEquivRadius * normalPhysicalOverlap);
    F_nd = unitCPVect * 2 * sqrt(5.0 / 6.0) * B * sqrt(S_n * nEquivMass) *  relVel_n.length();

    // Are we in a loading situation?
    if(relVel_n.dot(unitCPVect) > 0.0)
    {
        F_nd = -F_nd;
    }
	/* If particles are in contact and no bridge was formed previously, a new liquid bridge is formed*/
	if( *m_BridgeStatus!=1)
		{
			*m_BridgeStatusDelta = 1 - *m_BridgeStatus;
			newBridge = true;
        }
	}
	//Particle-Particle bond ruptures
	else if( (-normalPhysicalOverlap > ruptureDistance) && *m_BridgeStatus==1) 
	{
	    *m_BridgeStatusDelta = -*m_BridgeStatus;
		bridgeBroken = true;

		/* Reset Liquid Bridge force*/
		*m_BridgeForceDelta = - *m_BridgeForce;
	}

	else
    {
         F_n = unitCPVect * 0.0;
         F_nd = unitCPVect * 0.0;
    }
    /*******************************/
    /* Capillary Force Calculation */
    /*******************************/

    /* Only applied if the two particles have an existing bridge */
	if( *m_BridgeStatus == 1 && !bridgeBroken) 
	{
	   bridgeExists = true;
    }

	else if (newBridge) {bridgeExists = true;}

	else {bridgeExists = false;}

	CSimple3DVector F_n_liq;

	/* Perform capillary force calculation*/
	if( bridgeExists && elem2IsSurf ) //Particle-Particle interaction model acc. Mikami et al. 1998
    {

		if((time >= t_start_cohesion) && (liqVolumeStar != 0.0))
		{
		    /* Calculate separation distance, this is equal to h^c in the paper and the x-axis in Fig. 5 of Mikami et al. 1998 */
			/* Particle-particle h^c=2h/rp */

			//Nondimensionalize separation distance
			if ( normalPhysicalOverlap > 0.0)
            {				            	
            	sPrime = 0.0;  //Set separation distance during contact to zero to avoid super large cohesion force from large overlap
			}
            else
            {
				sPrime = -normalPhysicalOverlap/liqRadius ; //Separation after physical contact
			}

            /* Calculate force - according to Mikami et al. 1998  for sphere - sphere interaction */
		    aValue = -1.1 / pow(liqVolumeStar, 0.53 );
			bValue = ( -0.34 * log(liqVolumeStar) - 0.96 ) * bridgeParams.m_nLiqWettingAngle * bridgeParams.m_nLiqWettingAngle- 0.019 * log(liqVolumeStar) + 0.48;
		    cValue = 0.0042 * log(liqVolumeStar) + 0.078;
			F_n_liq = unitCPVect * PI * liqRadius * bridgeParams.m_nLiqGamma * ( exp( aValue * sPrime + bValue ) + cValue );
		}

		else
		{
		   F_n_liq = unitCPVect * 0.0;
		}
    }

    else if( bridgeExists && (elem2IsSurf==false)) //Particle-Wall interaction model acc. Mikami et al. 1998
    {
        if((time >= t_start_cohesion) && (liqVolumeStar != 0.0))
		{
			/* Calculate separation distance, this is equal to h^c in the paper and the x-axis in Fig. 5 of Mikami et al. 1998 */
			/* Particle-wall h^c=h/rp */
			if (normalPhysicalOverlap > 0.0)
			{
				//Set separation distance during contact to zero to avoid super large cohesion force from large overlap;
				sPrime = 0.0; 
			}
			else
			{
				sPrime = -normalPhysicalOverlap/( liqRadius ) ; //Separation after physical contact
			}

	        /*Calculate force for sphere - wall interaction Mikami et al. 1998*/
			aValue = -1.9 / pow(liqVolumeStar, 0.51 );
			bValue = ( -0.16 * log(liqVolumeStar) - 0.76 ) * bridgeParams.m_nLiqWettingAngle * bridgeParams.m_nLiqWettingAngle - 0.012 * log(liqVolumeStar) + 1.2;
			cValue = 0.013 * log(liqVolumeStar) + 0.18;
			F_n_liq = unitCPVect * PI * liqRadius * bridgeParams.m_nLiqGamma * ( exp( aValue * sPrime + bValue ) + cValue );
    	}
    	
		else
		{
		    //Set to zero if no liquid bridge exists
			F_n_liq =  unitCPVect * 0.0;
		}

	}
	else
	{
	    //Set to zero if no liquid bridge exists
		F_n_liq =  unitCPVect * 0.0;
	}

	

    /*Fill in parameters we were passed in*/

 	CSimple3DVector newF_n = F_n + F_nd + F_n_liq;
    calculatedUnsymNormalForceX = F_nd.dx();
    calculatedUnsymNormalForceY = F_nd.dy();
    calculatedUnsymNormalForceZ = F_nd.dz();

    calculatedNormalForceX = newF_n.dx();
    calculatedNormalForceY = newF_n.dy();
    calculatedNormalForceZ = newF_n.dz();

	/* Update Liquid Bridge force*/
	*m_BridgeForceDelta = F_n_liq.length() - *m_BridgeForce;


    /*****************************/
    /* Tangential Calculation    */
    /*****************************/
	CSimple3DVector F_t;
	CSimple3DVector F_td;
	CSimple3DVector newF_t;

	if(normalPhysicalOverlap>0)
	{
    double S_t =  8.0 * nEquivShearMod * sqrt(nEquivRadius * normalPhysicalOverlap);
    CSimple3DVector nOverlap_t(tangentialOverlapX, tangentialOverlapY, tangentialOverlapZ);
    F_t = -nOverlap_t * S_t;

    // Damping

    if(F_t.length() > F_n.length() * (staticFriction) )
    {
        newF_t = F_t * F_n.length() * (staticFriction) / F_t.length();
        nOverlap_t = -newF_t / S_t; //slippage has occurred so the tangential overlap is reduced a bit

        //at this point we get energy loss from the sliding!
        F_td = newF_t;
    }
    else
    {
        //at this point we get energy loss from the damping!
        F_td = - relVel_t * 2 * sqrt(5.0 / 6.0) * B * sqrt(S_t * nEquivMass);
        newF_t = F_t + F_td;
    }
	
    // Fill in parameters we were passed in
    calculatedTangentialForceX = newF_t.dx();
    calculatedTangentialForceY = newF_t.dy();
    calculatedTangentialForceZ = newF_t.dz();
    calculatedUnsymTangentialForceX = F_td.dx();
    calculatedUnsymTangentialForceY = F_td.dy();
    calculatedUnsymTangentialForceZ = F_td.dz();

    tangentialOverlapX = nOverlap_t.dx();
    tangentialOverlapY = nOverlap_t.dy();
    tangentialOverlapZ = nOverlap_t.dz();
	}

    /*****************************/
    /* Rolling Friction          */
    /*****************************/

    // Only relevant if actually rolling
    if(!isZero(angVel1.lengthSquared()))
    {
        CSimple3DVector torque1 = angVel1;
        torque1.normalise();
        torque1 *= -newF_n.length() * elem1PhysicalCurvature * rollingFriction;
        calculatedElem1AdditionalTorqueX = torque1.dx();
        calculatedElem1AdditionalTorqueY = torque1.dy();
        calculatedElem1AdditionalTorqueZ = torque1.dz();
        calculatedElem1UnsymAdditionalTorqueX = torque1.dx();
        calculatedElem1UnsymAdditionalTorqueY = torque1.dy();
        calculatedElem1UnsymAdditionalTorqueZ = torque1.dz();
    }

    if(!isZero(angVel2.lengthSquared()))
    {
        CSimple3DVector torque2 = angVel2;
        torque2.normalise();
        torque2 *= -newF_n.length() * elem2PhysicalCurvature * rollingFriction;
        calculatedElem2AdditionalTorqueX = torque2.dx();
        calculatedElem2AdditionalTorqueY = torque2.dy();
        calculatedElem2AdditionalTorqueZ = torque2.dz();
        calculatedElem2UnsymAdditionalTorqueX = torque2.dx();
        calculatedElem2UnsymAdditionalTorqueY = torque2.dy();
        calculatedElem2UnsymAdditionalTorqueZ = torque2.dz();
    }

    return eSuccess;
}







unsigned int CLiquidBridgeModel::getNumberOfRequiredProperties(
                 const EPluginPropertyCategory category)
{
	//register 1 particle property
	if (eParticle == category)
	{return 1;}
	//register 2 contact property
	else if (eContact == category)
	{return 2;}
	else
	{return 0;}



}

bool CLiquidBridgeModel::getDetailsForProperty(
					unsigned int				propertyIndex,
					EPluginPropertyCategory     category,
					char                        name[CUSTOM_PROP_MAX_NAME_LENGTH],
					EPluginPropertyDataTypes&   dataType,
					unsigned int&               numberOfElements,
					EPluginPropertyUnitTypes&   unitType)
{
    if (0 == propertyIndex &&  eParticle == category)
    {
        strcpy(name, LIQUID_CONTENT.c_str());
        dataType         = eDouble;
        numberOfElements = 1;
        unitType         = eNone;
        return true;
    }

	if (0 == propertyIndex &&  eContact == category)
    {
        strcpy(name, BRIDGE_STATUS.c_str()); 
        dataType         = eDouble;
        numberOfElements = 1;
        unitType         = eNone;

        return true;
    }
	 if (1  == propertyIndex &&   eContact == category)
    {

		strcpy(name, BRIDGE_FORCE.c_str());
        dataType         = eDouble;
        numberOfElements = 1;
        unitType         = eNone;

        return true;
    }

    else
    {
        return false;
    }
}