#if !defined(cbridgeparameters_h)
#define cbridgeparameters_h

class CBridgeParameters
{
    public:
        CBridgeParameters();

        CBridgeParameters(double m_nLiqGamma,
						double m_nLiqWettingAngle);

        double      m_nLiqGamma;
		double      m_nLiqWettingAngle;

};

#endif