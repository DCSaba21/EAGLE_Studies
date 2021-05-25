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


SCSFExport scsf_VolumeSegment_Source(SCStudyGraphRef sc)
{
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "VolumeSegment_Source";

		sc.FreeDLL = 1;
		sc.AutoLoop = 0;

		return;
	}

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}

	float& CurrentValue = sc.GetPersistentFloat(0);
	float& PreviousValue = sc.GetPersistentFloat(1);
	float& PreviousValueStorage = sc.GetPersistentFloat(2);

	PreviousValue = PreviousValueStorage;
	CurrentValue = sc.Close[sc.ArraySize - 1];

	PreviousValueStorage = sc.Close[sc.ArraySize - 1];
}

SCSFExport scsf_VolumeSegment_Destination(SCStudyGraphRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef ValuePerBar = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef Source_Study = sc.Input[InputIndex++];
	SCInputRef Source_Instrument_Start_Time = sc.Input[InputIndex++];
	SCInputRef Source_Instrument_End_Time = sc.Input[InputIndex++];

	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "VolumeSegment_Destination";

		sc.FreeDLL = 1;
		sc.AutoLoop = 0;  //Automatic looping is enabled.
		sc.MaintainReferenceToOtherChartsForPersistentVariables = 1;

		ValuePerBar.Name = "Value Per Bar";
		ValuePerBar.DrawStyle = DRAWSTYLE_BAR;
		ValuePerBar.PrimaryColor  = RGB(0, 255, 0);
		ValuePerBar.LineWidth = 3;


		Source_Study.Name = "Source_Chart_&_Study_Numbers";
		Source_Study.SetChartStudyValues(1, 1);

		Source_Instrument_Start_Time.Name = "Source Instrument Start Time";
		Source_Instrument_Start_Time.SetTime(HMS_TIME(9, 30, 0));

		Source_Instrument_End_Time.Name = "Source Instrument End Time";
		Source_Instrument_End_Time.SetTime(HMS_TIME(16, 9, 59));

		return;
	}

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}

	if (sc.IsChartDataLoadingInChartbook() == 1) return; // Don't start until all charts finished loading
	int& PreviousTime= sc.GetPersistentInt(1);
	int& PreviousIndex = sc.GetPersistentInt(2);
	float& FirstPreviousValuePerBar = sc.GetPersistentFloat(3);

	float& CurrentValue = sc.GetPersistentFloatFromChartStudy(Source_Study.GetChartNumber(), Source_Study.GetStudyID(), 0);
	float& PreviousValue = sc.GetPersistentFloatFromChartStudy(Source_Study.GetChartNumber(), Source_Study.GetStudyID(), 1);

	/*SCDateTime DTV, SessionStartDT;
	DTV = sc.BaseDateTimeIn[sc.Index];
	int Date = sc.GetTradingDayDate(DTV);
	SessionStartDT = sc.GetStartDateTimeForTradingDate(Date);
	int SessionFirstIndex = sc.GetContainingIndexForSCDateTime(sc.ChartNumber, SessionStartDT);
	*/

	/*SCString str;
	str.Format(" %i   %i   %f   %f", sc.LatestDateTimeForLastBar.GetTime(), Source_Instrument_Start_Time.GetTime(), CurrentValue, FirstPreviousValuePerBar);
	sc.AddMessageToLog(str, 0);
	str.Format("Time = %i  StartTime = %i, EndTime = %i CurrentValue = %f  FirstPreviousValuePerBar = %f ",sc.LatestDateTimeForLastBar.GetTime(), Source_Instrument_Start_Time.GetTime(), Source_Instrument_End_Time.GetTime(), CurrentValue, FirstPreviousValuePerBar);
  sc.AddMessageToLog(str, 0);
	*/

	if ( sc.LatestDateTimeForLastBar.GetTime() >= Source_Instrument_Start_Time.GetTime() && PreviousTime < Source_Instrument_Start_Time.GetTime()) FirstPreviousValuePerBar = 0;
	else if (PreviousIndex != sc.ArraySize -1) FirstPreviousValuePerBar = PreviousValue;

	if ( (sc.LatestDateTimeForLastBar.GetTime() >= Source_Instrument_End_Time.GetTime()) || (sc.LatestDateTimeForLastBar.GetTime() <= Source_Instrument_Start_Time.GetTime()) ) {
		FirstPreviousValuePerBar = 0;
		PreviousValue = 0;
		CurrentValue = 0;
	}

	if(sc.LatestDateTimeForLastBar.GetTime() >= Source_Instrument_Start_Time.GetTime() ) ValuePerBar[sc.ArraySize -1] = CurrentValue - FirstPreviousValuePerBar;
//&& sc.LatestDateTimeForLastBar.GetTime() <= Source_Instrument_End_Time.GetTime()
	//if(CurrentValue > FirstPreviousValuePerBar && sc.LatestDateTimeForLastBar.GetTime() >= Source_Instrument_Start_Time.GetTime()) ValuePerBar[sc.ArraySize -1] = CurrentValue - FirstPreviousValuePerBar;

 	PreviousIndex = sc.ArraySize -1;
  PreviousTime = sc.LatestDateTimeForLastBar.GetTime();
}
