#pragma once
#ifndef _SIERRACHART_H_
#define _SIERRACHART_H_
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define  _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <fstream>
#include <string>


SCSFExport scsf_PeriodicVWAP(SCStudyInterfaceRef sc)
{

	int SGIndex = 0;
	SCSubgraphRef VwapSG = sc.Subgraph[SGIndex++];

	int InputIndex = 0;

	SCInputRef ResetTime1 = sc.Input[InputIndex++];
	SCInputRef ResetTime2 = sc.Input[InputIndex++];
	SCInputRef ResetTime3 = sc.Input[InputIndex++];
	SCInputRef ResetTime4 = sc.Input[InputIndex++];
	SCInputRef ResetTime5 = sc.Input[InputIndex++];
	SCInputRef ResetTime6 = sc.Input[InputIndex++];
	SCInputRef ResetTime7 = sc.Input[InputIndex++];


	if (sc.SetDefaults)
	{
  // Configuration defaults
	   sc.GraphName = "PeriodicVWAP";
		sc.StudyDescription = "ResettingVWAP";
		sc.GraphRegion = 0;

		sc.AutoLoop = 1;
		sc.FreeDLL = 1;

		ResetTime1.Name="Reset time 1";
		ResetTime1.SetTime(HMS_TIME(0,0,0));
		ResetTime2.Name="Reset time 2";
		ResetTime2.SetTime(HMS_TIME(2,0,0));
		ResetTime3.Name="Reset time 3";
		ResetTime3.SetTime(HMS_TIME(11,0,0));
		ResetTime4.Name="Reset time 4";
		ResetTime4.SetTime(HMS_TIME(11,30,0));
		ResetTime5.Name="Reset time 5";
		ResetTime5.SetTime(HMS_TIME(13,30,0));
		ResetTime6.Name="Reset time 6";
		ResetTime6.SetTime(HMS_TIME(15,15,0));
		ResetTime7.Name="Reset time 7";
		ResetTime7.SetTime(HMS_TIME(16,15,0));

		VwapSG.Name="WVAP";
		VwapSG.DrawStyle = DRAWSTYLE_LINE;
		VwapSG.LineWidth=1;
		VwapSG.PrimaryColor=RGB(237,13,255);

		return;
	}

// Data processing

	if (sc.IsUserAllowedForSCDLLName == false) 
	{
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}

	int&BarIndex = sc.GetPersistentInt(0);
    float& Vwap = sc.GetPersistentFloat(0);
    float& PriceVolProduct = sc.GetPersistentFloat(1);
	float& VolSum = sc.GetPersistentFloat(2);

	if (sc.Index != BarIndex)
	{ //On the first call of a new bar
		if(sc.BaseDateTimeIn[sc.Index].GetTime() == ResetTime1.GetTime()
		  || sc.BaseDateTimeIn[sc.Index].GetTime() == ResetTime2.GetTime()
		  || sc.BaseDateTimeIn[sc.Index].GetTime() == ResetTime3.GetTime()
		  || sc.BaseDateTimeIn[sc.Index].GetTime() == ResetTime4.GetTime()
		  || sc.BaseDateTimeIn[sc.Index].GetTime() == ResetTime5.GetTime()
		  || sc.BaseDateTimeIn[sc.Index].GetTime() == ResetTime6.GetTime()
		  || sc.BaseDateTimeIn[sc.Index].GetTime() == ResetTime7.GetTime()
		)
		{
			//reset to zero what has to be reet
			VwapSG[sc.Index - 1] = sc.Close[sc.Index];
			Vwap = 0;
			PriceVolProduct = 0;
			VolSum = 0;
		}
		else 
		{
	 		PriceVolProduct = PriceVolProduct + sc.Close[sc.Index -1] * sc.Volume[sc.Index -1];
	 		VolSum = VolSum + sc.Volume[sc.Index-1];
	 		Vwap = PriceVolProduct / VolSum;
	 		VwapSG[sc.Index-1] = Vwap;
		}
	}

	 BarIndex = sc.Index;
}
