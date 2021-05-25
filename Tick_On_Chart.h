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


SCSFExport scsf_TickOnChart(SCStudyGraphRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef TickPlus1 = sc.Subgraph[SGIndex++];
	SCSubgraphRef TickPlus2 = sc.Subgraph[SGIndex++];
	SCSubgraphRef TickPlus3 = sc.Subgraph[SGIndex++];
	SCSubgraphRef TickMinus1 = sc.Subgraph[SGIndex++];
	SCSubgraphRef TickMinus2 = sc.Subgraph[SGIndex++];
	SCSubgraphRef TickMinus3 = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef Source_TickChart_n_Study = sc.Input[InputIndex++];
	//SCInputRef SourceTick = sc.Input[InputIndex++];
	SCInputRef DistanceFromCandle = sc.Input[InputIndex++];
	SCInputRef Sound_Alert = sc.Input[InputIndex++];
	SCInputRef Sound_Alert_MinTick = sc.Input[InputIndex++];
	SCInputRef Sound_Alert_Number = sc.Input[InputIndex++];
	SCInputRef Threshold_1 = sc.Input[InputIndex++];
	SCInputRef Threshold_2 = sc.Input[InputIndex++];
	SCInputRef Threshold_3 = sc.Input[InputIndex++];


	// Section 1 - Set the configuration variables and defaults


	if (sc.SetDefaults)
	{
		sc.GraphName = "TickOnChart";

		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		sc.CalculationPrecedence = VERY_LOW_PREC_LEVEL;
		sc.GraphRegion = 0;
		sc.DrawZeros = 0;
		//sc.UpdateAlways = 1;
		//sc.IncludeInStudySummary = 1;

		TickPlus1.Name = "First Threshold Positive Tick Alert";
		TickPlus1.DrawStyle = DRAWSTYLE_TEXT;
		TickPlus1.TextDrawStyleText = "T";
		TickPlus1.PrimaryColor = RGB(0, 128, 0);
		TickPlus1.LineWidth = 12;
		TickPlus1.DrawZeros = false;
		//TickPlus1.TransparentLabelBackground = 1;

		TickPlus2.Name = "Second Threshold Positive Tick Alert";
		TickPlus2.DrawStyle = DRAWSTYLE_TEXT;
		TickPlus2.TextDrawStyleText = "T";
		TickPlus2.PrimaryColor = RGB(0, 128, 0);
		TickPlus2.LineWidth = 18;
		TickPlus2.DrawZeros = false;

		TickPlus3.Name = "Third Threshold Positive Tick Alert";
		TickPlus3.DrawStyle = DRAWSTYLE_TEXT;
		TickPlus3.TextDrawStyleText = "T";
		TickPlus3.PrimaryColor = RGB(0, 128, 0);
		TickPlus3.LineWidth = 28;
		TickPlus3.DrawZeros = false;

		TickMinus1.Name = "First Threshold Negative Tick Alert";
		TickMinus1.DrawStyle = DRAWSTYLE_TEXT;
		TickMinus1.TextDrawStyleText = "T";
		TickMinus1.PrimaryColor = RGB(255, 0, 0);
		TickMinus1.LineWidth = 12;
		TickMinus1.DrawZeros = false;

		TickMinus2.Name = "Second Threshold Negative Tick Alert";
		TickMinus2.DrawStyle = DRAWSTYLE_TEXT;
		TickMinus2.TextDrawStyleText = "T";
		TickMinus2.PrimaryColor = RGB(255, 0, 0);
		TickMinus2.LineWidth = 18;
		TickMinus2.DrawZeros = false;

		TickMinus3.Name = "Third Threshold Negative Tick Alert";
		TickMinus3.DrawStyle = DRAWSTYLE_TEXT;
		TickMinus3.TextDrawStyleText = "T";
		TickMinus3.PrimaryColor = RGB(255, 0, 0);
		TickMinus3.LineWidth = 26;
		TickMinus3.DrawZeros = false;

		Source_TickChart_n_Study.Name = "Source_Tick_Chart";
		Source_TickChart_n_Study.SetChartNumber(1);

		//SourceTick.Name = "Source_Tick";
		//SourceTick.SetChartStudyValues(3,0);

		DistanceFromCandle.Name = "Distance of Signal from Bar";
		DistanceFromCandle.SetInt(4);

		Sound_Alert.Name = "Want a Sound Alert ?";
		Sound_Alert.SetYesNo(0);

		Sound_Alert_Number.Name = "Sound Alert Number";
		Sound_Alert_Number.SetInt(1);

		Sound_Alert_MinTick.Name = "Choose the Minimal Tick for Sound Alert";
		Sound_Alert_MinTick.SetCustomInputStrings("First; Second; Third");
		Sound_Alert_MinTick.SetCustomInputIndex(0);

		Threshold_1.Name = "Minimum TICK for First Threshold ";
		Threshold_1.SetInt(600);

		Threshold_2.Name = "Minimum TICK for Second Threshold ";
		Threshold_2.SetInt(800);

		Threshold_3.Name = "Minimum TICK for Third Threshold ";
		Threshold_3.SetInt(1000);




		return;
	}
	// Section 2 - Do data processing here

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}

	SCGraphData Tick;
	sc.GetChartBaseData(Source_TickChart_n_Study.GetChartNumber(), Tick);
	SCFloatArrayRef TickHigh = Tick[SC_HIGH];
	SCFloatArrayRef TickLow = Tick[SC_LOW];
	SCFloatArrayRef TickLast = Tick[SC_LAST];
	int TickArraySize = Tick[SC_HIGH].GetArraySize();

	int Threshold1 = Threshold_1.GetInt();
	int Threshold2 = Threshold_2.GetInt();
	int Threshold3 = Threshold_3.GetInt();

	int& Index = sc.GetPersistentInt(1);
	int& HistoricalBars = sc.GetPersistentInt(2);
	int& PreviousTick = sc.GetPersistentInt(3);

	

	int Dist = DistanceFromCandle.GetInt();
	int SoundAlertNumber = Sound_Alert_Number.GetInt();
	int MinTickForSoundAlert = Threshold1 * (Sound_Alert_MinTick.GetIndex() == 0) + Threshold2 * (Sound_Alert_MinTick.GetIndex() == 1) + Threshold3 * (Sound_Alert_MinTick.GetIndex() == 2);
	
	SCDateTime TickDT;
	SCDateTimeArray TickDTArray;

	sc.GetChartDateTimeArray(Source_TickChart_n_Study.GetChartNumber(), TickDTArray);
	int MatchingIndex;
	if (sc.Index == 0) HistoricalBars = 1;
	if (HistoricalBars == 1 && sc.Index == sc.ArraySize - 1) {
		// Run through Tick Chart historical bars. Only Once.
		for (int i = 0; i < TickArraySize; i++) {
			if (TickHigh[i] >= Threshold1 && TickHigh[i] < Threshold2) {
				TickDT = TickDTArray[i];
				//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
				//TickPlus1[MatchingIndex] = sc.High[MatchingIndex] + Dist*sc.TickSize;
				MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
				TickPlus1[MatchingIndex] = sc.High[MatchingIndex] + Dist * sc.TickSize;
			}
			else if (TickHigh[i] >= Threshold2 && TickHigh[i] < Threshold3) {
				TickDT = TickDTArray[i];
				//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
				//TickPlus2[MatchingIndex] = sc.High[MatchingIndex] + Dist*sc.TickSize;
				MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
				TickPlus2[MatchingIndex] = sc.High[MatchingIndex] + Dist * sc.TickSize;
			}
			else if (TickHigh[i] >= Threshold3) {
				TickDT = TickDTArray[i];
				//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
				//TickPlus3[MatchingIndex] = sc.High[MatchingIndex] + Dist*sc.TickSize;
				MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
				TickPlus3[MatchingIndex] = sc.High[MatchingIndex] + Dist * sc.TickSize;
			}

			if (TickLow[i] <= -Threshold1 && TickLow[i] > -Threshold2) {
				TickDT = TickDTArray[i];
				//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
				//TickMinus1[MatchingIndex] = sc.Low[MatchingIndex] - Dist*sc.TickSize;
				MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
				TickMinus1[MatchingIndex] = sc.Low[MatchingIndex] - Dist * sc.TickSize;
			}
			else if (TickLow[i] <= -Threshold2 && TickLow[i] > -Threshold3) {
				TickDT = TickDTArray[i];
				//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
				//TickMinus2[MatchingIndex] = sc.Low[MatchingIndex] - Dist*sc.TickSize;
				MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
				TickMinus2[MatchingIndex] = sc.Low[MatchingIndex] - Dist * sc.TickSize;
			}
			else if (TickLow[i] <= -Threshold3) {
				TickDT = TickDTArray[i];
				//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
				//TickMinus3[MatchingIndex] = sc.Low[MatchingIndex] - Dist*sc.TickSize;
				MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
				TickMinus3[MatchingIndex] = sc.Low[MatchingIndex] - Dist * sc.TickSize;
			}
		}
		HistoricalBars = 0;
	}

	/*if (Index == sc.Index) {
		if (TickP3 == 1) { TickPlus3[sc.Index] = sc.High[sc.Index] + Dist * sc.TickSize; TickP3 = 0; if (Sound_Alert.GetYesNo() == 1 && MinTickForSoundAlert <= 2) sc.SetAlert(SoundAlertNUmber); }
		else if (TickP2 == 1) { TickPlus2[sc.Index] = sc.High[sc.Index] + Dist * sc.TickSize; TickP2 = 0; if (Sound_Alert.GetYesNo() == 1 && MinTickForSoundAlert <= 1) sc.SetAlert(SoundAlertNUmber); }
		else if (TickP1 == 1) { TickPlus1[sc.Index] = sc.High[sc.Index] + Dist * sc.TickSize; TickP1 = 0; if (Sound_Alert.GetYesNo() == 1 && MinTickForSoundAlert == 0) sc.SetAlert(SoundAlertNUmber); }

		if (TickM3 == 1) { TickMinus3[sc.Index] = sc.Low[sc.Index] - Dist * sc.TickSize; TickM3 = 0; if (Sound_Alert.GetYesNo() == 1 && MinTickForSoundAlert <= 2) sc.SetAlert(SoundAlertNUmber); }
		else if (TickM2 == 1) { TickMinus2[sc.Index] = sc.Low[sc.Index] - Dist * sc.TickSize; TickM2 = 0; if (Sound_Alert.GetYesNo() == 1 && MinTickForSoundAlert <= 1) sc.SetAlert(SoundAlertNUmber); }
		else if (TickM1 == 1) { TickMinus1[sc.Index] = sc.Low[sc.Index] - Dist * sc.TickSize; TickM3 = 0; if (Sound_Alert.GetYesNo() == 1 && MinTickForSoundAlert == 0) sc.SetAlert(SoundAlertNUmber); }
	}*/
		
	if (Sound_Alert.GetYesNo() &&
		(TickLast[TickArraySize - 1] >= MinTickForSoundAlert && PreviousTick < MinTickForSoundAlert ||
		TickLast[TickArraySize - 1] <= -MinTickForSoundAlert && PreviousTick > -MinTickForSoundAlert)
	    ) sc.SetAlert(SoundAlertNumber);
		

	if (TickHigh[TickArraySize - 1] >= Threshold1 && TickHigh[TickArraySize - 1] < Threshold2) {
		TickDT = TickDTArray[TickArraySize - 1];
		//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
		//TickPlus1[MatchingIndex] = sc.High[MatchingIndex] + Dist*sc.TickSize;
		MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
		TickPlus1[MatchingIndex] = sc.High[MatchingIndex] + Dist * sc.TickSize;
	}
	else if (TickHigh[TickArraySize - 1] >= Threshold2 && TickHigh[TickArraySize - 1] < Threshold3) {
		TickDT = TickDTArray[TickArraySize - 1];
		//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
		//TickPlus2[MatchingIndex] = sc.High[MatchingIndex] + Dist*sc.TickSize;
		MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
		TickPlus2[MatchingIndex] = sc.High[MatchingIndex] + Dist * sc.TickSize;
		TickPlus1[MatchingIndex] = 0;
	}
	else if (TickHigh[TickArraySize - 1] >= Threshold3) {
		TickDT = TickDTArray[TickArraySize - 1];
		//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
		//TickPlus3[MatchingIndex] = sc.High[MatchingIndex] + Dist*sc.TickSize;
		MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
		TickPlus3[MatchingIndex] = sc.High[MatchingIndex] + Dist * sc.TickSize;
		TickPlus1[MatchingIndex] = 0;
		TickPlus2[MatchingIndex] = 0;
	}

	if (TickLow[TickArraySize - 1] <= -Threshold1 && TickLow[TickArraySize - 1] > -Threshold2) {
		TickDT = TickDTArray[TickArraySize - 1];
		//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
		//TickMinus1[MatchingIndex] = sc.Low[MatchingIndex] - Dist*sc.TickSize;
		MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
		TickMinus1[MatchingIndex] = sc.Low[MatchingIndex] - Dist * sc.TickSize;
	}
	else if (TickLow[TickArraySize - 1] <= -Threshold2 && TickLow[TickArraySize - 1] > -Threshold3) {
		TickDT = TickDTArray[TickArraySize - 1];
		//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
		//TickMinus2[MatchingIndex] = sc.Low[MatchingIndex] - Dist*sc.TickSize;
		MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
		TickMinus2[MatchingIndex] = sc.Low[MatchingIndex] - Dist * sc.TickSize;
		TickMinus1[MatchingIndex] = 0;
	}
	else if (TickLow[TickArraySize - 1] <= -Threshold3) {
		TickDT = TickDTArray[TickArraySize - 1];
		//MatchingIndex = sc.GetNearestMatchForSCDateTime(sc.ChartNumber, TickDT);
		//TickMinus3[MatchingIndex] = sc.Low[MatchingIndex] - Dist*sc.TickSize;
		MatchingIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, TickDT);
		TickMinus3[MatchingIndex] = sc.Low[MatchingIndex] - Dist * sc.TickSize;
		TickMinus1[MatchingIndex] = 0;
		TickMinus2[MatchingIndex] = 0;
	}

	

	Index = sc.Index;
	PreviousTick = TickLast[TickArraySize - 1];
}

