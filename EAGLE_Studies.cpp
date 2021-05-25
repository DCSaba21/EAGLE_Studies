#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
//#include "wtypes.h"
#include "sierrachart.h"
//

// Tools Line Numbers:
// 320,000-320,001 ATR_Projection
// 10,099,700 + Price/TickSize - 10,116, 000 + Price/TickSize  --> 12,000,000 + PullingAlertCounter Level_3_  Level_3_Analysis
//14,000,000 + sc.Index,  15,000,000 + sc.Index LargeBidAskHighlight
//20,310,000 - 20,360,000 Large_Order_Alert signals
//PnV_Overlay 30,000,000 + PnVIndex
// Trading_Halt is using 31,000,000 (this is a separate study)//


SCDLLName("EAGLE_studies")


#include "Level_3_Analysis.h"

#include "Delta_Divergence.h"

#include "Large_Trade_Alert.h"

#include "Large_Trade_Alert_Just_Sound.h"

#include "Volume_Spike.h"

#include "Tick_On_Chart.h"

#include "Imbalance_Clusters.h"

#include "CustomAbsorptionBarsBuildingFunction.h"

#include "Custom_Absorption_Bars.h"

#include "Large_Bid_Ask_Highlight.h"

#include "DepthSum.h"

#include "VolumeSegments.h"

#include "SpreadDefence.h"

#include "PeriodicVWAP.h"

#include "RelativeTVOL.h"

#include "IceBerg.h"

#include "Smart_PnV_Overlay.h"

#include "IceBerg_DEV.h"

#include "SpreadDefenseNew.h"




