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

SCSFExport scsf_Delta_Divergence_Bar(SCStudyGraphRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef Simple_TopDivergence = sc.Subgraph[SGIndex++];
	SCSubgraphRef Simple_BottomDivergence = sc.Subgraph[SGIndex++];
	SCSubgraphRef Disagree_TopDivergence = sc.Subgraph[SGIndex++];
	SCSubgraphRef Disagree_BottomDivergence = sc.Subgraph[SGIndex++];
	SCSubgraphRef Agree_TopDivergence = sc.Subgraph[SGIndex++];
	SCSubgraphRef Agree_BottomDivergence = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef Divergence_Type = sc.Input[InputIndex++];	
	SCInputRef Reference_Period = sc.Input[InputIndex++];
	SCInputRef BarsBack = sc.Input[InputIndex++];
	SCInputRef Delta_Threshold = sc.Input[InputIndex++];
	SCInputRef DistanceFromCandle = sc.Input[InputIndex++];
	SCInputRef SoundAlert = sc.Input[InputIndex++];
	SCInputRef TopSoundAlertNumber = sc.Input[InputIndex++];
	SCInputRef BottomSoundAlertNumber = sc.Input[InputIndex++];

	// Section 1 - Set the configuration variables and defaults

	// This section only runs once upon adding an instance of the study to a chart, and when a chartbook is opened and an instance of this study is on a chart in a chartbook.  It is run once for each instance in this case.
	if (sc.SetDefaults)
	{
		sc.GraphName = "Delta_Divergence";

		sc.StudyDescription = "Delta_Divergence";

		sc.AutoLoop = 1;  // true
		sc.FreeDLL = 0;
		sc.DrawZeros = 0;
		//sc.IncludeInStudySummary = 1;

		sc.GraphRegion = 0;

		Simple_TopDivergence.Name = "Simple Top Divergence";
		Simple_TopDivergence.DrawStyle = DRAWSTYLE_DIAMOND;
		Simple_TopDivergence.LineWidth = 4;
		Simple_TopDivergence.PrimaryColor = RGB(255, 0, 0);

		Simple_BottomDivergence.Name = "Simple Bottom Divergence";
		Simple_BottomDivergence.DrawStyle = DRAWSTYLE_DIAMOND;
		Simple_BottomDivergence.LineWidth = 4;
		Simple_BottomDivergence.PrimaryColor = RGB(0, 255, 0);

		Agree_TopDivergence.Name = "Bar's Price & Delta Agree Top Divergence";
		Agree_TopDivergence.DrawStyle = DRAWSTYLE_DIAMOND;
		Agree_TopDivergence.LineWidth = 4;
		Agree_TopDivergence.PrimaryColor = RGB(255, 0, 0);

		Agree_BottomDivergence.Name = "Bar's Price & Delta Agree Bottom Divergence";
		Agree_BottomDivergence.DrawStyle = DRAWSTYLE_DIAMOND;
		Agree_BottomDivergence.LineWidth = 4;
		Agree_BottomDivergence.PrimaryColor = RGB(0, 255, 0);

		Disagree_TopDivergence.Name = "Bar's Price & Delta Disagree Top Divergence";
		Disagree_TopDivergence.DrawStyle = DRAWSTYLE_DIAMOND;
		Disagree_TopDivergence.LineWidth = 4;
		Disagree_TopDivergence.PrimaryColor = RGB(255, 0, 0);

		Disagree_BottomDivergence.Name = "Bar's Price & Delta Disagree Bottom Divergence";
		Disagree_BottomDivergence.DrawStyle = DRAWSTYLE_DIAMOND;
		Disagree_BottomDivergence.LineWidth = 4;
		Disagree_BottomDivergence.PrimaryColor = RGB(0, 255, 0);

		Divergence_Type.Name = "Divergence Type";
		Divergence_Type.SetCustomInputStrings("Simple; Range;");
		Divergence_Type.SetCustomInputIndex(0);

		Reference_Period.Name = "Reference Period";
		Reference_Period.SetCustomInputStrings("Number of Bars Back; From Session Start;");
		Reference_Period.SetCustomInputIndex(0);

		BarsBack.Name = "Bars_Back_Filter";
		BarsBack.SetInt(0);

		Delta_Threshold.Name = "Delta_Threshold";
		Delta_Threshold.SetInt(0);

		DistanceFromCandle.Name = "Distance From Candle";
		DistanceFromCandle.SetInt(2);

		SoundAlert.Name = "Sound Alert";
		SoundAlert.SetYesNo(0);

		TopSoundAlertNumber.Name = "Top Sound Alert Number";
		TopSoundAlertNumber.SetInt(7);

		BottomSoundAlertNumber.Name = "Bottom Sound Alert Number";
		BottomSoundAlertNumber.SetInt(8);

		// Must return before doing any data processing if sc.SetDefaults is set
		return;
	}


	// Section 2 - Do data processing

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}
	

	int BottomAlert = BottomSoundAlertNumber.GetInt();
	int TopAlert = TopSoundAlertNumber.GetInt();

	int& PreviousIndex = sc.GetPersistentInt(1);
	int& PreviousTopSignal = sc.GetPersistentInt(2);
	int& PreviousBottomSignal = sc.GetPersistentInt(3);

	float& PreviousBarsBackHigh = sc.GetPersistentFloat(1);
	float& PreviousBarsBackLow = sc.GetPersistentFloat(2);
	float& BarsBackHigh = sc.GetPersistentFloat(3);
	float& BarsBackLow = sc.GetPersistentFloat(4);	

	
	SCDateTime DTV, PreviousDTV, SessionStartDT;
	DTV = sc.BaseDateTimeIn[sc.Index];
	PreviousDTV = sc.BaseDateTimeIn[sc.Index - 1];
	int Date = sc.GetTradingDayDate(DTV);
	SessionStartDT = sc.GetStartDateTimeForTradingDate(Date);
	int SessionFirstIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, SessionStartDT);
	float SessionOpen, SessionHigh, SessionLow, SessionClose, NextSessionOpen;
	sc.GetOHLCOfTimePeriod(SessionStartDT, PreviousDTV, SessionOpen, SessionHigh, SessionLow, SessionClose, NextSessionOpen);
	
	if (PreviousIndex != sc.Index || sc.Index == 0)
	{
		PreviousBarsBackHigh = BarsBackHigh;
		PreviousBarsBackLow = BarsBackLow;
		PreviousTopSignal = 0;
		PreviousBottomSignal = 0;
		BarsBackHigh = sc.GetHighest(sc.BaseDataIn[SC_HIGH], BarsBack.GetInt());
		BarsBackLow = sc.GetLowest(sc.BaseDataIn[SC_LOW], BarsBack.GetInt());
	}

	

	int Ask = sc.AskVolume[sc.Index];
	int Bid = sc.BidVolume[sc.Index];
	int Delta = Ask - Bid;
	float BarOC = sc.Close[sc.Index] - sc.Open[sc.Index];

	if (Divergence_Type.GetIndex() == 0) 
	{
		if (BarOC > 0.0  && Delta <= - Delta_Threshold.GetInt())
		{			
			Simple_TopDivergence[sc.Index] = sc.High[sc.Index] + sc.TickSize * DistanceFromCandle.GetInt();
			Disagree_TopDivergence[sc.Index] = 0;
			Disagree_BottomDivergence[sc.Index] = 0;
			
			if (SoundAlert.GetYesNo() == 1 && PreviousTopSignal == 0)sc.SetAlert(TopAlert);
			PreviousTopSignal = 1; PreviousBottomSignal = 0;
		}
		else if (BarOC < 0.0 && Delta >= Delta_Threshold.GetInt())
		{
			Simple_BottomDivergence[sc.Index] = sc.Low[sc.Index] - sc.TickSize * DistanceFromCandle.GetInt();
			Disagree_TopDivergence[sc.Index] = 0;
			Disagree_BottomDivergence[sc.Index] = 0;
			if (SoundAlert.GetYesNo() == 1 && PreviousBottomSignal == 0)sc.SetAlert(BottomAlert);
			PreviousBottomSignal = 1; PreviousTopSignal = 0;
		}
		else
		{ 
			Simple_TopDivergence[sc.Index] = 0; Simple_BottomDivergence[sc.Index] = 0;  PreviousTopSignal = 0; PreviousBottomSignal = 0; 
			Agree_TopDivergence[sc.Index] = 0; Agree_BottomDivergence[sc.Index] = 0;
			Disagree_TopDivergence[sc.Index] = 0; Disagree_BottomDivergence[sc.Index] = 0;
		}
	}

	else {
		if (Divergence_Type.GetIndex() == 1)// if Range mode
		{ 
			if (Reference_Period.GetIndex() == 0)// BarsBack HL
			{
				if (sc.High[sc.Index] > PreviousBarsBackHigh && Delta <= -Delta_Threshold.GetInt()) {
					if (BarOC > 0.0) 
					{
						Disagree_TopDivergence[sc.Index] = sc.High[sc.Index] + sc.TickSize * DistanceFromCandle.GetInt();
						Agree_TopDivergence[sc.Index] = 0;
						Simple_TopDivergence[sc.Index] = 0;
						Simple_BottomDivergence[sc.Index] = 0;
						if (SoundAlert.GetYesNo() == 1 && PreviousTopSignal == 0)sc.SetAlert(TopAlert);
						PreviousTopSignal = 1; PreviousBottomSignal = 0;
					}
					else if (BarOC < 0.0)
					{
						Agree_TopDivergence[sc.Index] = sc.High[sc.Index] + sc.TickSize * DistanceFromCandle.GetInt();
						Disagree_TopDivergence[sc.Index] = 0;
						if (SoundAlert.GetYesNo() == 1 && PreviousTopSignal == 0)sc.SetAlert(TopAlert);
						PreviousTopSignal = 1; PreviousBottomSignal = 0;
					}				
				}
				else if (sc.Low[sc.Index] < PreviousBarsBackLow && Delta >= Delta_Threshold.GetInt()) {
					if (BarOC > 0.0)
					{
						Agree_BottomDivergence[sc.Index] = sc.Low[sc.Index] - sc.TickSize * DistanceFromCandle.GetInt();
						Disagree_BottomDivergence[sc.Index] = 0;
						if (SoundAlert.GetYesNo() == 1 && PreviousTopSignal == 0)sc.SetAlert(BottomAlert);
						PreviousTopSignal = 1; PreviousBottomSignal = 0;
					}
					else if (BarOC < 0.0)
					{
						Disagree_BottomDivergence[sc.Index] = sc.Low[sc.Index] - sc.TickSize * DistanceFromCandle.GetInt();
						Agree_BottomDivergence[sc.Index] = 0;
						Simple_TopDivergence[sc.Index] = 0;
						Simple_BottomDivergence[sc.Index] = 0;
						if (SoundAlert.GetYesNo() == 1 && PreviousTopSignal == 0)sc.SetAlert(BottomAlert);
						PreviousTopSignal = 1; PreviousBottomSignal = 0;
					}
				}
				else 
				{
					Agree_TopDivergence[sc.Index] = 0; Agree_BottomDivergence[sc.Index] = 0;
				    Disagree_TopDivergence[sc.Index] = 0; Disagree_BottomDivergence[sc.Index] = 0;
					Simple_TopDivergence[sc.Index] = 0;	Simple_BottomDivergence[sc.Index] = 0;
				    PreviousTopSignal = 0; PreviousBottomSignal = 0; 
				}
			}


			else if (Reference_Period.GetIndex() == 1)// Session  HL
			{			
				if (sc.High[sc.Index] > SessionHigh && Delta <= -Delta_Threshold.GetInt()) {
					if (BarOC > 0.0)
					{
						Disagree_TopDivergence[sc.Index] = sc.High[sc.Index] + sc.TickSize * DistanceFromCandle.GetInt();
						Agree_TopDivergence[sc.Index] = 0;
						if (SoundAlert.GetYesNo() == 1 && PreviousTopSignal == 0)sc.SetAlert(TopAlert);
						PreviousTopSignal = 1; PreviousBottomSignal = 0;
					}
					else if (BarOC < 0.0)
					{
						Agree_TopDivergence[sc.Index] = sc.High[sc.Index] + sc.TickSize * DistanceFromCandle.GetInt();
						Disagree_TopDivergence[sc.Index] = 0;
						if (SoundAlert.GetYesNo() == 1 && PreviousTopSignal == 0)sc.SetAlert(TopAlert);
						PreviousTopSignal = 1; PreviousBottomSignal = 0;
					}
				}
				else if (sc.Low[sc.Index] < SessionLow && Delta >= Delta_Threshold.GetInt()) {
					if (BarOC > 0.0)
					{
						Agree_BottomDivergence[sc.Index] = sc.Low[sc.Index] - sc.TickSize * DistanceFromCandle.GetInt();
						Disagree_BottomDivergence[sc.Index] = 0;
						if (SoundAlert.GetYesNo() == 1 && PreviousTopSignal == 0)sc.SetAlert(BottomAlert);
						PreviousTopSignal = 1; PreviousBottomSignal = 0;
					}
					else if (BarOC < 0.0)
					{
						Disagree_BottomDivergence[sc.Index] = sc.Low[sc.Index] - sc.TickSize * DistanceFromCandle.GetInt();
						Agree_BottomDivergence[sc.Index] = 0;
						if (SoundAlert.GetYesNo() == 1 && PreviousTopSignal == 0)sc.SetAlert(BottomAlert);
						PreviousTopSignal = 1; PreviousBottomSignal = 0;
					}
				}
				else
				{
					Agree_TopDivergence[sc.Index] = 0; Agree_BottomDivergence[sc.Index] = 0;
					Disagree_TopDivergence[sc.Index] = 0; Disagree_BottomDivergence[sc.Index] = 0;
					PreviousTopSignal = 0; PreviousBottomSignal = 0;
				}
			}
		}
		
	}
	PreviousIndex = sc.Index;
}


