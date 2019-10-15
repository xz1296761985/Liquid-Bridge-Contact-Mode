#include "CBridgeParameters.h"


CBridgeParameters::CBridgeParameters() :
                 m_nLiqGamma(),
				 m_nLiqWettingAngle()

{
    ;
}

CBridgeParameters::CBridgeParameters(double nLiqGamma,
								 double nLiqWettingAngle) :
							     m_nLiqGamma(nLiqGamma),
								m_nLiqWettingAngle(nLiqWettingAngle)


{
    ;
}
