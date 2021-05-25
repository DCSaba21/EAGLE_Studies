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

SCSFExport scsf_Large_Trade_Alert(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef Large_Buy_1 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Large_Sell_1 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Large_Buy_2 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Large_Sell_2 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Large_Buy_3 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Large_Sell_3 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Large_Buy_Extention = sc.Subgraph[SGIndex++];
	SCSubgraphRef Large_Sell_Extention = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef Threshold_1 = sc.Input[InputIndex++];
	SCInputRef Threshold_2 = sc.Input[InputIndex++];
	SCInputRef Threshold_3 = sc.Input[InputIndex++];
	SCInputRef Sound_Alert = sc.Input[InputIndex++];
	SCInputRef Sound_Alert_MinOrderSize = sc.Input[InputIndex++];
	SCInputRef Large_Buy_Alert_Number = sc.Input[InputIndex++];
	SCInputRef Large_Sell_Alert_Number = sc.Input[InputIndex++];
	SCInputRef Extend_Line_From_Signal = sc.Input[InputIndex++];
	SCInputRef Distance_Away_For_Intersection = sc.Input[InputIndex++];
	SCInputRef Extention_Line_MinOrderSize = sc.Input[InputIndex++];


	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "Large_Trade_Alert";

		sc.StudyDescription = "Large_Trade_Alert";

		sc.AutoLoop = 0;

		sc.FreeDLL = 0;

		sc.GraphRegion = 0;

		sc.CalculationPrecedence = VERY_LOW_PREC_LEVEL;
		//sc.IncludeInStudySummary = 1;

		Large_Buy_1.Name = "Large Trade At the Ask Signal - Group 1";
		Large_Buy_1.PrimaryColor = RGB(155, 255, 155);
		Large_Buy_1.LineWidth = 6;

		Large_Sell_1.Name = "Large Trade At the Bid Signal - Group 1";
		Large_Sell_1.PrimaryColor = RGB(255, 140, 140);
		Large_Sell_1.LineWidth = 6;

		Large_Buy_2.Name = "Large Trade At the Ask Signal - Group 2";
		Large_Buy_2.PrimaryColor = RGB(0, 255, 0);
		Large_Buy_2.LineWidth = 11;

		Large_Sell_2.Name = "Large Trade At the Bid Signal - Group 2";
		Large_Sell_2.PrimaryColor = RGB(255, 0, 0);
		Large_Sell_2.LineWidth = 11;

		Large_Buy_3.Name = "Large Trade At the Ask Signal - Group 3";
		Large_Buy_3.PrimaryColor = RGB(0, 128, 0);
		Large_Buy_3.LineWidth = 16;

		Large_Sell_3.Name = "Large Trade At the Bid Signal - Group 3";
		Large_Sell_3.PrimaryColor = RGB(179, 0, 0);
		Large_Sell_3.LineWidth = 16;

		Large_Buy_Extention.Name = "Large Trade At the Ask Extention Line";
		Large_Buy_Extention.PrimaryColor = RGB(0, 255, 0);
		Large_Buy_Extention.LineWidth = 3;
		Large_Buy_Extention.LineStyle = LINESTYLE_SOLID;

		Large_Sell_Extention.Name = "Large Trade At the Bid Extention Line";
		Large_Sell_Extention.PrimaryColor = RGB(255, 0, 0);
		Large_Sell_Extention.LineWidth = 3;
		Large_Sell_Extention.LineStyle = LINESTYLE_SOLID;



		Threshold_1.Name = "Minimum Trade Size  - Group 1";
		Threshold_1.SetInt(75);

		Threshold_2.Name = "Minimum Trade Size  - Group 2";
		Threshold_2.SetInt(150);

		Threshold_3.Name = "MinimumTrade Size  - Group 3";
		Threshold_3.SetInt(250);

		Sound_Alert.Name = "Want a Sound Alert?";
		Sound_Alert.SetYesNo(0);

		Sound_Alert_MinOrderSize.Name = "Choose the Minimum Group for Sound Alert";
		Sound_Alert_MinOrderSize.SetCustomInputStrings("Group 1; Group 2; Group 3");
		Sound_Alert_MinOrderSize.SetCustomInputIndex(0);

		Large_Buy_Alert_Number.Name = "Large Trade at The Ask Sound Alert Number";
		Large_Buy_Alert_Number.SetInt(13);

		Large_Sell_Alert_Number.Name = "Large Trade at The Bid Sound Alert Number";
		Large_Sell_Alert_Number.SetInt(14);

		Extend_Line_From_Signal.Name = "Extend Horizontal Line From Signal?";
		Extend_Line_From_Signal.SetYesNo(0);

		Extention_Line_MinOrderSize.Name = "Choose the Minimal Group for an Extention Line";
		Extention_Line_MinOrderSize.SetCustomInputStrings("Group 1; Group 2; Group 3");
		Extention_Line_MinOrderSize.SetCustomInputIndex(0);

		Distance_Away_For_Intersection.Name = "Minimal Distance(Ticks) That Price Made From Signal Before Checking Intersection";
		Distance_Away_For_Intersection.SetInt(8);

		

		return;
	}


	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.UpdateStartIndex == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}
	if (sc.DLLNameUserServiceLevel > 0) return;

	if (sc.IsChartDataLoadingInChartbook() == 1) return; // Don't start until all charts finished loading

	s_UseTool SignalExtentionLine, DelExtentionRay, ModExtentionRay;

	__int64& LastProcessedSequence = sc.GetPersistentInt64(1);
	int& SmallestLineNumber = sc.GetPersistentInt(2);
	int& LargestLineNumber = sc.GetPersistentInt(3);
	int& LargeSellCounter = sc.GetPersistentInt(4);
	int& LargeBuyCounter = sc.GetPersistentInt(5);
	int& ExtRayCounter = sc.GetPersistentInt(6);
	int& ModExtCounter = sc.GetPersistentInt(7);
	int& PreviousReplayStatus = sc.GetPersistentInt(8);

	float& LoopBackHigh = sc.GetPersistentFloat(1);
	float& LoopBackLow = sc.GetPersistentFloat(2);

	SCString& PreviousChartName = sc.GetPersistentSCString(1);

	unsigned int Threshold1 = Threshold_1.GetInt();
	unsigned int Threshold2 = Threshold_2.GetInt();
	unsigned int Threshold3 = Threshold_3.GetInt();
	int LargeBuyAlertNumber = Large_Buy_Alert_Number.GetInt();
	int LargeSellAlertNumber = Large_Sell_Alert_Number.GetInt();
	int SoundAlertMinOrderSize = Sound_Alert_MinOrderSize.GetInt();
	int ExtendLineFromSignal = Extend_Line_From_Signal.GetInt();
	int DistanceAwayForIntersection = Distance_Away_For_Intersection.GetInt();
	int ExtentionLineMinOrderSize = Extention_Line_MinOrderSize.GetInt();
	int DrawExtended;

	// Get the Time and Sales
	c_SCTimeAndSalesArray TimeSales;
	sc.GetTimeAndSales(TimeSales);
	if (TimeSales.Size() == 0)	return;  // No Time and Sales data available for the symbol

	if ((sc.ReplayStatus == REPLAY_RUNNING && PreviousReplayStatus == REPLAY_STOPPED) /*|| (sc.ReplayStatus != REPLAY_RUNNING &&  sc.GetChartName(sc.ChartNumber).GetChars() != PreviousChartName.GetChars())*/) {
		for (int i = 20310000; i <= 20360000; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i);
		}
	}

	if (LastProcessedSequence != 0) {
		// Loop through the Time and Sales.
		for (int TSIndex = 0; TSIndex < TimeSales.Size(); ++TSIndex) {
			if (TimeSales[TSIndex].Sequence <= LastProcessedSequence) continue;
			if (TimeSales[TSIndex].Type == SC_TS_BID && TimeSales[TSIndex].Volume >= Threshold1) {
				if (Sound_Alert.GetYesNo() == 1 && SoundAlertMinOrderSize == 0) sc.SetAlert(LargeSellAlertNumber);
				s_UseTool LargeSell;
				LargeSell.Clear();
				LargeSell.AddAsUserDrawnDrawing = 1;
				LargeSell.ChartNumber = sc.ChartNumber;
				LargeSell.DrawingType = DRAWING_MARKER;
				LargeSell.MarkerType = MARKER_POINT;
				if (TimeSales[TSIndex].Volume < Threshold2) {
					LargeSell.MarkerSize = Large_Sell_1.LineWidth;
					LargeSell.Color = Large_Sell_1.PrimaryColor;
				}
				else if (TimeSales[TSIndex].Volume >= Threshold2 && TimeSales[TSIndex].Volume < Threshold3) {
					if (Sound_Alert.GetYesNo() == 1 && SoundAlertMinOrderSize > 0) sc.SetAlert(LargeSellAlertNumber);
					LargeSell.MarkerSize = Large_Sell_2.LineWidth;
					LargeSell.Color = Large_Sell_2.PrimaryColor;
				}
				else {
					if (Sound_Alert.GetYesNo() == 1 && SoundAlertMinOrderSize > 1) sc.SetAlert(LargeSellAlertNumber);
					LargeSell.MarkerSize = Large_Sell_3.LineWidth;
					LargeSell.Color = Large_Sell_3.PrimaryColor;
				}
				LargeSell.LineNumber = 20310000 + LargeSellCounter;
				LargeSellCounter++;
				LargeSell.AddMethod = UTAM_ADD_OR_ADJUST;
				LargeSell.UseRelativeVerticalValues = 0;
				LargeSell.BeginIndex = sc.ArraySize - 1;
				LargeSell.BeginValue = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
				sc.UseTool(LargeSell);

				DrawExtended = 0;
				if (ExtentionLineMinOrderSize == 0 && TimeSales[TSIndex].Volume >= Threshold1) DrawExtended = 1;
				else if (ExtentionLineMinOrderSize == 1 && TimeSales[TSIndex].Volume >= Threshold2) DrawExtended = 1;
				else if (ExtentionLineMinOrderSize == 2 && TimeSales[TSIndex].Volume >= Threshold3) DrawExtended = 1;

				if (ExtendLineFromSignal == 1 && DrawExtended == 1) {
					SignalExtentionLine.Clear();
					SignalExtentionLine.AddAsUserDrawnDrawing = 1;
					SignalExtentionLine.ChartNumber = sc.ChartNumber;
					SignalExtentionLine.DrawingType = DRAWING_HORIZONTAL_RAY;
					SignalExtentionLine.LineNumber = 20320000 + ExtRayCounter;//(int)(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier / sc.TickSize);
					ExtRayCounter++;
					SignalExtentionLine.AddMethod = UTAM_ADD_OR_ADJUST;
					SignalExtentionLine.Color = Large_Sell_Extention.PrimaryColor;
					SignalExtentionLine.LineWidth = Large_Sell_Extention.LineWidth;
					SignalExtentionLine.LineStyle = Large_Sell_Extention.LineStyle;
					SignalExtentionLine.UseRelativeVerticalValues = 0;
					SignalExtentionLine.BeginIndex = sc.ArraySize - 1;
					SignalExtentionLine.BeginValue = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
					sc.UseTool(SignalExtentionLine);
				}
			}


			else if (TimeSales[TSIndex].Type == SC_TS_ASK && TimeSales[TSIndex].Volume >= Threshold1) {
				if (Sound_Alert.GetYesNo() == 1 && SoundAlertMinOrderSize == 0) sc.SetAlert(LargeBuyAlertNumber);
				s_UseTool LargeBuy;
				LargeBuy.Clear();
				LargeBuy.AddAsUserDrawnDrawing = 1;
				LargeBuy.ChartNumber = sc.ChartNumber;
				LargeBuy.DrawingType = DRAWING_MARKER;
				LargeBuy.MarkerType = MARKER_POINT;
				if (TimeSales[TSIndex].Volume < Threshold2) {
					LargeBuy.MarkerSize = Large_Buy_1.LineWidth;
					LargeBuy.Color = Large_Buy_1.PrimaryColor;
				}
				else if (TimeSales[TSIndex].Volume >= Threshold2 && TimeSales[TSIndex].Volume < Threshold3) {
					if (Sound_Alert.GetYesNo() == 1 && SoundAlertMinOrderSize > 0) sc.SetAlert(LargeBuyAlertNumber);
					LargeBuy.MarkerSize = Large_Buy_2.LineWidth;
					LargeBuy.Color = Large_Buy_2.PrimaryColor;
				}
				else {
					if (Sound_Alert.GetYesNo() == 1 && SoundAlertMinOrderSize > 1) sc.SetAlert(LargeBuyAlertNumber);
					LargeBuy.MarkerSize = Large_Buy_3.LineWidth;
					LargeBuy.Color = Large_Buy_3.PrimaryColor;
				}
				LargeBuy.LineNumber = 20330000 + LargeBuyCounter;
				LargeBuyCounter++;
				LargeBuy.AddMethod = UTAM_ADD_ALWAYS;
				LargeBuy.UseRelativeVerticalValues = 0;
				LargeBuy.BeginIndex = sc.ArraySize - 1;
				LargeBuy.BeginValue = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
				sc.UseTool(LargeBuy);

				DrawExtended = 0;
				if (ExtentionLineMinOrderSize == 0 && TimeSales[TSIndex].Volume >= Threshold1) DrawExtended = 1;
				else if (ExtentionLineMinOrderSize == 1 && TimeSales[TSIndex].Volume >= Threshold2) DrawExtended = 1;
				else if (ExtentionLineMinOrderSize == 2 && TimeSales[TSIndex].Volume >= Threshold3) DrawExtended = 1;
				if (ExtendLineFromSignal == 1 && DrawExtended == 1) {
					SignalExtentionLine.Clear();
					SignalExtentionLine.AddAsUserDrawnDrawing = 1;
					SignalExtentionLine.ChartNumber = sc.ChartNumber;
					SignalExtentionLine.DrawingType = DRAWING_HORIZONTAL_RAY;
					SignalExtentionLine.LineNumber = 20340000 + ExtRayCounter;//(int)(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier / sc.TickSize);
					ExtRayCounter++;
					SignalExtentionLine.AddMethod = UTAM_ADD_ALWAYS;
					SignalExtentionLine.Color = Large_Buy_Extention.PrimaryColor;
					SignalExtentionLine.LineWidth = Large_Buy_Extention.LineWidth;
					SignalExtentionLine.LineStyle = Large_Buy_Extention.LineStyle;
					SignalExtentionLine.UseRelativeVerticalValues = 0;
					SignalExtentionLine.BeginIndex = sc.ArraySize - 1;
					SignalExtentionLine.BeginValue = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
					sc.UseTool(SignalExtentionLine);
				}
			}
		}
	}

	LastProcessedSequence = TimeSales[TimeSales.Size() - 1].Sequence;

	// ======================== Start Modifying Rays to Lines on Future  Intersection =========================

	int Flag = 0;
	for (int j = 0; Flag < 1; j++) {       //Loop through all existing Horizontal rays.
		if (sc.GetUserDrawnChartDrawing(sc.ChartNumber, DRAWING_HORIZONTAL_RAY, DelExtentionRay, j)) { //Get the Ray and store it in DelExtentionRay
			if (DelExtentionRay.BeginValue == sc.Close[sc.ArraySize - 1]) {
				int DelExtentionRayLineNumber = DelExtentionRay.LineNumber;
				int DelExtentionRayBeginIndex = DelExtentionRay.BeginIndex;
				float DelExtentionRayBeginValue = DelExtentionRay.BeginValue;
				LoopBackHigh = DelExtentionRayBeginValue; LoopBackLow = DelExtentionRayBeginValue;
				for (int LoopBackIndex = sc.ArraySize - 1; LoopBackIndex > DelExtentionRayBeginIndex; --LoopBackIndex) {
					if (sc.High[LoopBackIndex] > LoopBackHigh) LoopBackHigh = sc.High[LoopBackIndex];
					if (sc.Low[LoopBackIndex] < LoopBackLow) LoopBackLow = sc.Low[LoopBackIndex];
				}
				if (DelExtentionRayBeginIndex != sc.ArraySize - 1 && ((int)((LoopBackHigh - DelExtentionRayBeginValue) / sc.TickSize) >= DistanceAwayForIntersection || (int)((LoopBackLow - DelExtentionRayBeginValue) / sc.TickSize) <= -DistanceAwayForIntersection)) {
					ModExtentionRay.Clear();
					ModExtentionRay.AddAsUserDrawnDrawing = 1;
					ModExtentionRay.ChartNumber = sc.ChartNumber;
					ModExtentionRay.DrawingType = DRAWING_LINE;
					ModExtentionRay.LineNumber = 20350000 + ModExtCounter;
					ModExtCounter++;
					ModExtentionRay.AddMethod = UTAM_ADD_ALWAYS;
					ModExtentionRay.Color = DelExtentionRay.Color;
					ModExtentionRay.LineWidth = DelExtentionRay.LineWidth;
					ModExtentionRay.LineStyle = DelExtentionRay.LineStyle;
					ModExtentionRay.UseRelativeVerticalValues = 0;
					ModExtentionRay.BeginIndex = DelExtentionRay.BeginIndex;
					ModExtentionRay.EndIndex = sc.ArraySize - 1;
					ModExtentionRay.BeginValue = DelExtentionRay.BeginValue;
					ModExtentionRay.EndValue = DelExtentionRay.BeginValue;
					sc.UseTool(ModExtentionRay);
					sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, DelExtentionRayLineNumber);
				}
			}
		}
		else break;
	}

	if (sc.ReplayStatus != REPLAY_RUNNING)   PreviousChartName = sc.GetChartName(sc.ChartNumber).GetChars();
	PreviousReplayStatus = sc.ReplayStatus;

	if (sc.LastCallToFunction) {
		for (int i = 20310000; i <= 20360000; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i);
		}
	}
	
}
