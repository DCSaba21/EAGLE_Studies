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

SCSFExport scsf_PnV_Overlay(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef Peaks = sc.Subgraph[SGIndex++];
	SCSubgraphRef Valleys = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef Source_Chart_Number = sc.Input[InputIndex++];
	SCInputRef PnF_Study_ID = sc.Input[InputIndex++];
	SCInputRef Interval_Input = sc.Input[InputIndex++];



	if (sc.SetDefaults)
	{
		sc.GraphName = "PnV_Overlay";

		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		sc.GraphRegion = 0;
		sc.DrawZeros = 0;
		//sc.IncludeInStudySummary = 1;

		Peaks.Name = "Peaks Lines";
		Peaks.PrimaryColor = RGB(0, 255, 0);
		Peaks.DrawStyle = DRAWSTYLE_LINE;
		Peaks.LineStyle = LINESTYLE_SOLID;
		Peaks.LineWidth = 4;


		Valleys.Name = "Valleys Lines";
		Valleys.PrimaryColor = RGB(255, 0, 0);
		Valleys.DrawStyle = DRAWSTYLE_LINE;
		Valleys.LineStyle = LINESTYLE_SOLID;
		Valleys.LineWidth = 4;



		Source_Chart_Number.Name = "Source Chart Number";
		Source_Chart_Number.SetInt(41);

		PnF_Study_ID.Name = "ID Of Source Volume profile Study";
		PnF_Study_ID.SetInt(1);

		Interval_Input.Name = "Function Interval in Seconds";
		Interval_Input.SetInt(10);


		return;
	}


	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}
	//if (sc.DLLNameUserServiceLevel > 0) return;

	int& PreviousTime = sc.GetPersistentInt(0);
	int& LastPnVIndex = sc.GetPersistentInt(1);

	SCDateTime DTV;
	DTV = sc.CurrentSystemDateTime;
	int CurrentTime = DTV.GetTime();

	//if (sc.UpdateStartIndex == 0) {
	if (CurrentTime - PreviousTime >= Interval_Input.GetInt() || sc.UpdateStartIndex == 0) {

		s_UseTool PeaksnValleys, PreviousPeaksnValleys;		

		
		float PnVLinePrice = 0;
		int PnVType, PnVStartIndex, PnVEndIndex, PnVProfileIndex, PnVIndex;
		PnVProfileIndex = 0;
		PnVIndex = 0;

		while (sc.GetStudyPeakValleyLine(Source_Chart_Number.GetInt(), PnF_Study_ID.GetInt(), PnVLinePrice, PnVType, PnVStartIndex, PnVEndIndex, PnVProfileIndex, PnVIndex) != 0) {
			if (PnVType == 1) {//peaks
				sc.GetUserDrawnDrawingByLineNumber(sc.ChartNumber, 50000000 + PnVIndex, PreviousPeaksnValleys);
			//	sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 50000000 + PnVIndex);
					{
					PeaksnValleys.Clear();
					PeaksnValleys.AddAsUserDrawnDrawing = 1;
					PeaksnValleys.ChartNumber = sc.ChartNumber;
					PeaksnValleys.DrawingType = DRAWING_HORIZONTALLINE;
					PeaksnValleys.LineNumber = 50000000 + PnVIndex;
					PeaksnValleys.AddMethod = UTAM_ADD_OR_ADJUST;
					PeaksnValleys.Color = Peaks.PrimaryColor;						
					PeaksnValleys.LineWidth = Peaks.LineWidth;
					if (PreviousPeaksnValleys.LineWidth > Peaks.LineWidth) PeaksnValleys.LineWidth = PreviousPeaksnValleys.LineWidth;
					PeaksnValleys.LineStyle = Peaks.LineStyle;
					PeaksnValleys.UseRelativeVerticalValues = 0;
					PeaksnValleys.BeginValue = PnVLinePrice;						
					sc.UseTool(PeaksnValleys);

					sc.GetUserDrawnDrawingByLineNumber(sc.ChartNumber, 50000000 + PnVIndex, PreviousPeaksnValleys);
					if (PreviousPeaksnValleys.LineWidth < Peaks.LineWidth) {
						PeaksnValleys.Clear();
						PeaksnValleys.AddAsUserDrawnDrawing = 1;
						PeaksnValleys.ChartNumber = sc.ChartNumber;
						PeaksnValleys.DrawingType = DRAWING_HORIZONTALLINE;
						PeaksnValleys.LineNumber = 50000000 + PnVIndex;
						PeaksnValleys.AddMethod = UTAM_ADD_OR_ADJUST;
						PeaksnValleys.Color = Peaks.PrimaryColor;
						PeaksnValleys.LineWidth = Peaks.LineWidth;
						PeaksnValleys.LineStyle = Peaks.LineStyle;;
						PeaksnValleys.UseRelativeVerticalValues = 0;
						PeaksnValleys.BeginValue = PnVLinePrice;
						sc.UseTool(PeaksnValleys);
					}
				}
					 
			}
			else if (PnVType == 2) {//valleys
				sc.GetUserDrawnDrawingByLineNumber(sc.ChartNumber, 50000000 + PnVIndex, PreviousPeaksnValleys);
			//	sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 50000000 + PnVIndex);
					PeaksnValleys.Clear();
					PeaksnValleys.AddAsUserDrawnDrawing = 1;
					PeaksnValleys.ChartNumber = sc.ChartNumber;
					PeaksnValleys.DrawingType = DRAWING_HORIZONTALLINE;
					PeaksnValleys.LineNumber = 50000000 + PnVIndex;
					PeaksnValleys.AddMethod = UTAM_ADD_OR_ADJUST;
					PeaksnValleys.Color = Valleys.PrimaryColor;		
					PeaksnValleys.LineWidth = Valleys.LineWidth;
					if (PreviousPeaksnValleys.LineWidth > Valleys.LineWidth) PeaksnValleys.LineWidth = PreviousPeaksnValleys.LineWidth;
					PeaksnValleys.LineStyle = Valleys.LineStyle;;
					PeaksnValleys.UseRelativeVerticalValues = 0;
					PeaksnValleys.BeginValue = PnVLinePrice;						
					sc.UseTool(PeaksnValleys);	
					sc.GetUserDrawnDrawingByLineNumber(sc.ChartNumber, 50000000 + PnVIndex, PreviousPeaksnValleys);
					if (PreviousPeaksnValleys.LineWidth < Valleys.LineWidth) {
						PeaksnValleys.Clear();
						PeaksnValleys.AddAsUserDrawnDrawing = 1;
						PeaksnValleys.ChartNumber = sc.ChartNumber;
						PeaksnValleys.DrawingType = DRAWING_HORIZONTALLINE;
						PeaksnValleys.LineNumber = 50000000 + PnVIndex;
						PeaksnValleys.AddMethod = UTAM_ADD_OR_ADJUST;
						PeaksnValleys.Color = Valleys.PrimaryColor;
						PeaksnValleys.LineWidth = Valleys.LineWidth;							
						PeaksnValleys.LineStyle = Valleys.LineStyle;;
						PeaksnValleys.UseRelativeVerticalValues = 0;
						PeaksnValleys.BeginValue = PnVLinePrice;
						sc.UseTool(PeaksnValleys);
					}
			}
			PnVIndex++;
		}

			

		if (LastPnVIndex > PnVIndex) {				

			for (int i = PnVIndex + 1; i <= LastPnVIndex; i++) {
				sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 50000000 + i);
			}				
		}

		LastPnVIndex = PnVIndex;
		PreviousTime = CurrentTime;			
		
		
	}
	
	
	if (sc.LastCallToFunction) {			
		for (int i = 0; i <= LastPnVIndex; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 50000000 + i);
		}
	}
}

