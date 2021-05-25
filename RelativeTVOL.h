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


SCSFExport scsf_Relative_TVOL(SCStudyInterfaceRef sc)
{

	int SGIndex = 0;
	SCSubgraphRef RealativeTVOL_3 = sc.Subgraph[SGIndex++];
	SCSubgraphRef RealativeTVOL_2 = sc.Subgraph[SGIndex++];
	SCSubgraphRef RealativeTVOL_1 = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef Input_ChartNumber = sc.Input[InputIndex++];
	SCInputRef Input_FontSize = sc.Input[InputIndex++];
	SCInputRef Input_TextColor = sc.Input[InputIndex++];
	SCInputRef Start_Time = sc.Input[InputIndex++];
	SCInputRef End_Time = sc.Input[InputIndex++];

	if (sc.SetDefaults)
	{
  // Configuration defaults
	  sc.GraphName = "Relative_TVOL";
		sc.StudyDescription = "Relative_TVOL";

		sc.AutoLoop = 1;
		sc.FreeDLL = 1;

		
		RealativeTVOL_3.Name = "TVOLrel1D";
		RealativeTVOL_3.DrawStyle = DRAWSTYLE_LINE;
		RealativeTVOL_3.LineWidth = 2;
		RealativeTVOL_3.PrimaryColor = RGB(0, 0, 255);

		RealativeTVOL_2.Name = "TVOLrel2Ds";
		RealativeTVOL_2.DrawStyle = DRAWSTYLE_LINE;
		RealativeTVOL_2.LineWidth = 2;
		RealativeTVOL_2.PrimaryColor = RGB(0, 255, 0);

		RealativeTVOL_1.Name = "TVOLrel10Davr";
		RealativeTVOL_1.DrawStyle = DRAWSTYLE_LINE;
		RealativeTVOL_1.LineWidth = 2;
		RealativeTVOL_1.PrimaryColor = RGB(255, 0, 0);
		

		Input_ChartNumber.Name = "The number of the chart on which to draw the text";
		Input_ChartNumber.SetInt(23);

		Input_FontSize.Name = "Font Size";
		Input_FontSize.SetInt(12);
		Input_TextColor.Name = "Text Color";
		Input_TextColor.SetColor(255, 0, 255);

		Start_Time.Name = "Start Time";
		Start_Time.SetTime(HMS_TIME(9, 32, 0));
		End_Time.Name = "End Time";
		End_Time.SetTime(HMS_TIME(16, 04, 0));

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

	float CurrentCumulativeValue = sc.Close[sc.Index];
	float& Y1CumulativeValue = sc.GetPersistentFloat(0); // the cumulative value for this time of day yesterday
	float& Y2CumulativeValue = sc.GetPersistentFloat(1); // and the day before
	float& Y3CumulativeValue = sc.GetPersistentFloat(2); // and the day before
	float& Y4CumulativeValue = sc.GetPersistentFloat(3); // and the day before
	float& Y5CumulativeValue = sc.GetPersistentFloat(4); // and the day before
	float& Y6CumulativeValue = sc.GetPersistentFloat(5); // and the day before
	float& Y7CumulativeValue = sc.GetPersistentFloat(6); // and the day before
	float& Y8CumulativeValue = sc.GetPersistentFloat(7); // and the day before
	float& Y9CumulativeValue = sc.GetPersistentFloat(8); // and the day before
	float& Y10CumulativeValue = sc.GetPersistentFloat(9); // and the day before

	int& Counter = sc.GetPersistentInt(0);
	int& BarIndex = sc.GetPersistentInt(1);

	float RelativeTVOL1 = 0;
	float RelativeTVOL2 = 0;
	float RelativeTVOL3 = 0;

	SCDateTime DTV = sc.BaseDateTimeIn[sc.Index];
	int CurrentBarTime = DTV.GetTime();

	Counter = 0;
	if (BarIndex != sc.Index)
	{
		for (int i = sc.Index - 1; i >= 0; i--)
		{// loop backwards thru the bars until Counter = 10 (including)
			if (sc.BaseDateTimeIn[i].GetTime() == CurrentBarTime)
			{
				Counter++;
				if (Counter == 1) Y1CumulativeValue = sc.Close[i];
				else if (Counter == 2) Y2CumulativeValue = sc.Close[i];
				else if (Counter == 3) Y3CumulativeValue = sc.Close[i];
				else if (Counter == 4) Y4CumulativeValue = sc.Close[i];
				else if (Counter == 5) Y5CumulativeValue = sc.Close[i];
				else if (Counter == 6) Y6CumulativeValue = sc.Close[i];
				else if (Counter == 7) Y7CumulativeValue = sc.Close[i];
				else if (Counter == 8) Y8CumulativeValue = sc.Close[i];
				else if (Counter == 9) Y9CumulativeValue = sc.Close[i];
				else Y10CumulativeValue = sc.Close[i];
				if (Counter == 10) break;
			}
		}
	}

	RelativeTVOL1 = CurrentCumulativeValue / Y1CumulativeValue;
	RelativeTVOL2 = CurrentCumulativeValue / Y2CumulativeValue;
	RelativeTVOL3 = CurrentCumulativeValue / ((Y1CumulativeValue + Y2CumulativeValue + Y3CumulativeValue + Y4CumulativeValue + Y5CumulativeValue + Y6CumulativeValue + Y7CumulativeValue + Y8CumulativeValue + Y9CumulativeValue + Y10CumulativeValue) / 10);

	if ( (End_Time.GetTime() >= sc.LatestDateTimeForLastBar.GetTime()) && (sc.LatestDateTimeForLastBar.GetTime()>= Start_Time.GetTime()) )
	{
		RealativeTVOL_1[sc.Index] = RelativeTVOL1;
		RealativeTVOL_2[sc.Index] = RelativeTVOL2;
		RealativeTVOL_3[sc.Index] = RelativeTVOL3;
	}
	else 
	{
		RealativeTVOL_1[sc.Index] = 1;
		RealativeTVOL_2[sc.Index] = 1;
		RealativeTVOL_3[sc.Index] = 1;
	}

	s_UseTool ValuesAsText;

	ValuesAsText.Clear();
	ValuesAsText.AddAsUserDrawnDrawing = 1;
	ValuesAsText.ChartNumber = Input_ChartNumber.GetInt();
	ValuesAsText.DrawingType = DRAWING_TEXT;
	ValuesAsText.AddMethod = UTAM_ADD_OR_ADJUST;
	ValuesAsText.FontSize = Input_FontSize.GetInt();
	ValuesAsText.FontBold = 1;
	ValuesAsText.Color = Input_TextColor.GetColor();
	ValuesAsText.TextAlignment = DT_VCENTER | DT_LEFT;
	ValuesAsText.UseRelativeVerticalValues = 1;
	ValuesAsText.Text.Format("%.3f  %.3f  %.3f ", RelativeTVOL3, RelativeTVOL2, RelativeTVOL1);
	ValuesAsText.LineNumber = 10203005;
	ValuesAsText.BeginDateTime = 75;
	ValuesAsText.BeginValue = 96;
	sc.UseTool(ValuesAsText);

	BarIndex = sc.Index;
}
