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


SCSFExport scsf_LargeBidAskHighlight(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef LargeAskHighlightTopLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef LargeAskHighlightBottomLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef LargeBidHighlightTopLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef LargeBidHighlightBottomLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef ExtendingLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef Buyers_Aggressive_Side_Signal_1 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Buyers_Aggressive_Side_Signal_2 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Buyers_Aggressive_Side_Signal_3 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Sellers_Aggressive_Side_Signal_1 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Sellers_Aggressive_Side_Signal_2 = sc.Subgraph[SGIndex++];
	SCSubgraphRef Sellers_Aggressive_Side_Signal_3 = sc.Subgraph[SGIndex++];


	int InputIndex = 0;
	SCInputRef Input_Standart_Daviations = sc.Input[InputIndex++];	
	SCInputRef Want_Horizontal_Ray = sc.Input[InputIndex++];
	SCInputRef Want_Aggressive_Side_Signal = sc.Input[InputIndex++];
	SCInputRef Distance_Of_Aggressive_Side_Signal_From_Bar = sc.Input[InputIndex++];	
	SCInputRef Want_Hor_Line_Width_Wider = sc.Input[InputIndex++];
	SCInputRef Hor_Line_Width_Factor = sc.Input[InputIndex++];

	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphRegion = 0;
		sc.GraphName = "LargeBidAskHighlight";
		sc.FreeDLL = 0;
		sc.AutoLoop = 1;
		sc.MaintainVolumeAtPriceData = 1;
		sc.TransparencyLevel = 55;

		Input_Standart_Daviations.Name = "Number Of Standatd Deviations";
		Input_Standart_Daviations.SetFloat(2.0);	

		Want_Horizontal_Ray.Name = "Want Hoirizontal Ray?";
		Want_Horizontal_Ray.SetYesNo(1);

		Want_Aggressive_Side_Signal.Name = "Want aggressive side signal?";
		Want_Aggressive_Side_Signal.SetCustomInputStrings("None; Based on Bar's SDV; Relative to Session;");
		Want_Aggressive_Side_Signal.SetCustomInputIndex(0);

		Distance_Of_Aggressive_Side_Signal_From_Bar.Name = "Distance of aggressive side signal from bar";
		Distance_Of_Aggressive_Side_Signal_From_Bar.SetInt(3);		

		Want_Hor_Line_Width_Wider.Name = "Want horizontal line width wider for large volumes?";
		Want_Hor_Line_Width_Wider.SetYesNo(0);
		
		Hor_Line_Width_Factor.Name = "Horizontal line width factor";
		Hor_Line_Width_Factor.SetFloat(1.5);		

		LargeAskHighlightTopLine.Name = "Large Ask Volume Highlight";
		LargeAskHighlightTopLine.DrawStyle = DRAWSTYLE_FILLRECTBOTTOM_TRANSPARENT;
		LargeAskHighlightTopLine.PrimaryColor = RGB(0, 255, 0);

		LargeAskHighlightBottomLine.Name = "Large Ask Volume Highlight";
		LargeAskHighlightBottomLine.DrawStyle = DRAWSTYLE_FILLRECTTOP_TRANSPARENT;
		LargeAskHighlightBottomLine.PrimaryColor = RGB(0, 255, 0);

		LargeBidHighlightTopLine.Name = "Large Bid Volume Highlight";
		LargeBidHighlightTopLine.DrawStyle = DRAWSTYLE_FILLRECTBOTTOM_TRANSPARENT;
		LargeBidHighlightTopLine.PrimaryColor = RGB(255, 0, 0);

		LargeBidHighlightBottomLine.Name = "Large Bid Volume Highlight";
		LargeBidHighlightBottomLine.DrawStyle = DRAWSTYLE_FILLRECTTOP_TRANSPARENT;
		LargeBidHighlightBottomLine.PrimaryColor = RGB(255, 0, 0);

		ExtendingLine.Name = " Extending Line";
		ExtendingLine.LineStyle = LINESTYLE_DASHDOT;
		ExtendingLine.LineWidth = 3;

		Buyers_Aggressive_Side_Signal_1.Name = "Buyers aggression level 1 signal";
		Buyers_Aggressive_Side_Signal_1.DrawStyle = DRAWSTYLE_TRIANGLE_UP;
		Buyers_Aggressive_Side_Signal_1.PrimaryColor = RGB(0, 255, 0);
		Buyers_Aggressive_Side_Signal_1.LineWidth = 3;

		Buyers_Aggressive_Side_Signal_2.Name = "Buyers aggression level 2 signal";
		Buyers_Aggressive_Side_Signal_2.DrawStyle = DRAWSTYLE_TRIANGLE_UP;
		Buyers_Aggressive_Side_Signal_2.PrimaryColor = RGB(0, 255, 0);
		Buyers_Aggressive_Side_Signal_2.LineWidth = 5;

		Buyers_Aggressive_Side_Signal_3.Name = "Buyers aggression level 3 signal";
		Buyers_Aggressive_Side_Signal_3.DrawStyle = DRAWSTYLE_TRIANGLE_UP;
		Buyers_Aggressive_Side_Signal_3.PrimaryColor = RGB(0, 255, 0);
		Buyers_Aggressive_Side_Signal_3.LineWidth = 7;

		Sellers_Aggressive_Side_Signal_1.Name = "Buyers aggression level 1 signal";
		Sellers_Aggressive_Side_Signal_1.DrawStyle = DRAWSTYLE_TRIANGLE_DOWN;
		Sellers_Aggressive_Side_Signal_1.PrimaryColor = RGB(255, 0, 0);
		Sellers_Aggressive_Side_Signal_1.LineWidth = 3;

		Sellers_Aggressive_Side_Signal_2.Name = "Buyers aggression level 2 signal";
		Sellers_Aggressive_Side_Signal_2.DrawStyle = DRAWSTYLE_TRIANGLE_DOWN;
		Sellers_Aggressive_Side_Signal_2.PrimaryColor = RGB(255, 0, 0);
		Sellers_Aggressive_Side_Signal_2.LineWidth = 5;

		Sellers_Aggressive_Side_Signal_3.Name = "Buyers aggression level 3 signal";
		Sellers_Aggressive_Side_Signal_3.DrawStyle = DRAWSTYLE_TRIANGLE_DOWN;
		Sellers_Aggressive_Side_Signal_3.PrimaryColor = RGB(255, 0, 0);
		Sellers_Aggressive_Side_Signal_3.LineWidth = 7;


		return;
	}

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.UpdateStartIndex == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}

	float& PreviousLargestAskVolPrice = sc.GetPersistentFloat(5);
	float& PreviousLargestBidVolPrice = sc.GetPersistentFloat(6);
	float& PreviousAverageAskVolumePerLevel = sc.GetPersistentFloat(7);
	float& PreviousAverageBidVolumePerLevel = sc.GetPersistentFloat(8);
	float& PreviousSDV_Ask = sc.GetPersistentFloat(9);
	float& PreviousSDV_Bid = sc.GetPersistentFloat(10);
	float& PreviousAskNumOfSDV = sc.GetPersistentFloat(11);
	float& PreviousBidNumOfSDV = sc.GetPersistentFloat(12);
	float& SessionAvgLargestAskVol = sc.GetPersistentFloat(13);
	float& SessionAvgLargestBidVol = sc.GetPersistentFloat(14);
	


	__int64& LastProcessedSequence = sc.GetPersistentInt64(1);
	int& PreviousIndex = sc.GetPersistentInt(5);
	int& PreviousLargestAskVol = sc.GetPersistentInt(6);
	int& PreviousLargestBidVol = sc.GetPersistentInt(7);
	int& SessionCumAskLargestVol = sc.GetPersistentInt(8);
	int& SessionCumBidLargestVol = sc.GetPersistentInt(9);
	int& BarCounter_Session = sc.GetPersistentInt(10);
	int& GG = sc.GetPersistentInt(11);
	int& RR = sc.GetPersistentInt(12);
	int& PreviousReplayStatus = sc.GetPersistentInt(13);


	//SCString& Status = sc.GetPersistentSCString(0);

	SCString str;
	int LargestAskVol = 0;
	int LargestBidVol = 0;
	int AskLineWidth = 0, BidLineWidth = 0;
	float LargestAskVolPrice = 0;
	float LargestBidVolPrice = 0;
	float LinePrice;
	float Range, AverageAskVolumePerLevel, AverageBidVolumePerLevel;
	float AskDifSum = 0, BidDifSum = 0, S_Ask = 0, S_Bid, SDV_Ask = 0, SDV_Bid = 0;
	float RelativeLargestAskVol = 0.0, RelativeLargestBidVol = 0.0;

	Range = sc.High[sc.Index] - sc.Low[sc.Index];
	AverageAskVolumePerLevel = sc.AskVolume[sc.Index] / (Range / sc.TickSize + 1);
	AverageBidVolumePerLevel = sc.BidVolume[sc.Index] / (Range / sc.TickSize + 1);

	int VAPSizeAtBarIndex = sc.VolumeAtPriceForBars->GetSizeAtBarIndex(sc.Index);
	s_VolumeAtPriceV2* p_VolumeAtPriceAtIndex;

	if (sc.Index == 0 || sc.ReplayStatus == REPLAY_RUNNING && PreviousReplayStatus == REPLAY_STOPPED) {
		for (int i = 0; i <= sc.Index; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 14000000 + i);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 15000000 + i);
		}

	}

	//iterate through bar levels and get largest ask and bid vols and prices and the AskDifSum BidDifSum
	for (int VAPIndex = 0; VAPIndex < VAPSizeAtBarIndex; VAPIndex++)
	{
		sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.Index, VAPIndex, &p_VolumeAtPriceAtIndex);
		if (p_VolumeAtPriceAtIndex->AskVolume > LargestAskVol)
		{
			LargestAskVol = p_VolumeAtPriceAtIndex->AskVolume;
			LargestAskVolPrice = sc.Low[sc.Index] + VAPIndex * sc.TickSize;
		}

		if (p_VolumeAtPriceAtIndex->BidVolume > LargestBidVol)
		{
			LargestBidVol = p_VolumeAtPriceAtIndex->BidVolume;
			LargestBidVolPrice = sc.Low[sc.Index] + VAPIndex * sc.TickSize;
		}
		AskDifSum += pow((float)p_VolumeAtPriceAtIndex->AskVolume - AverageAskVolumePerLevel, 2);
		BidDifSum += pow((float)p_VolumeAtPriceAtIndex->BidVolume - AverageBidVolumePerLevel, 2);
	}

	if (LargestAskVolPrice != 0 && LargestBidVolPrice != 0)
	{
		LargeAskHighlightTopLine[sc.Index] = LargestAskVolPrice + sc.TickSize / 2;
		LargeAskHighlightBottomLine[sc.Index] = LargestAskVolPrice - sc.TickSize / 2;
		LargeBidHighlightTopLine[sc.Index] = LargestBidVolPrice + sc.TickSize / 2;
		LargeBidHighlightBottomLine[sc.Index] = LargestBidVolPrice - sc.TickSize / 2;
	}

	S_Ask = AskDifSum / (Range / sc.TickSize + 1); //ask variabllity
	S_Bid = BidDifSum / (Range / sc.TickSize + 1); //bid variablility
	SDV_Ask = (float)pow(S_Ask, 0.5);
	SDV_Bid = (float)pow(S_Bid, 0.5);

	float AskNumOfSDV = ((float)LargestAskVol - AverageAskVolumePerLevel) / SDV_Ask;
	float BidNumOfSDV = ((float)LargestBidVol - AverageBidVolumePerLevel) / SDV_Bid;

	float SDV_Diff = (AskNumOfSDV - BidNumOfSDV) / Input_Standart_Daviations.GetFloat();

	c_SCTimeAndSalesArray TimeSales;
	sc.GetTimeAndSales(TimeSales);
	if (TimeSales.Size() == 0)	return;  // No Time and Sales data available for the symbol

	SCDateTime DTV;
	

	if (sc.Index != PreviousIndex)
	{
		DTV = sc.BaseDateTimeIn[sc.Index];
		if (DTV.GetTime() == sc.StartTime1 || (sc.UseSecondStartEndTimes == 1 && DTV.GetTime() == sc.StartTime2))
		{
			SessionCumAskLargestVol = 0;
			SessionCumBidLargestVol = 0;
			BarCounter_Session = 0;
			SessionCumAskLargestVol = 0;
			SessionCumBidLargestVol = 0;			
		}
		else
		{
			SessionCumAskLargestVol += PreviousLargestAskVol;
			SessionCumBidLargestVol += PreviousLargestBidVol;
			BarCounter_Session++;
		}

		if (BarCounter_Session != 0)
		{
			SessionAvgLargestAskVol = (float)SessionCumAskLargestVol / (float)BarCounter_Session;
			SessionAvgLargestBidVol = (float)SessionCumBidLargestVol / (float)BarCounter_Session;
		}

		if (Want_Hor_Line_Width_Wider.GetYesNo() && PreviousLargestAskVol / SessionAvgLargestAskVol >= Hor_Line_Width_Factor.GetFloat()) AskLineWidth = ceilf((float)ExtendingLine.LineWidth * 1.5);
		else AskLineWidth = ExtendingLine.LineWidth;
		if (Want_Hor_Line_Width_Wider.GetYesNo() && PreviousLargestBidVol / SessionAvgLargestBidVol >= Hor_Line_Width_Factor.GetFloat()) BidLineWidth = ceilf((float)ExtendingLine.LineWidth * 1.5);
		else BidLineWidth = ExtendingLine.LineWidth;

		if ((float)PreviousLargestAskVol >= PreviousAverageAskVolumePerLevel + Input_Standart_Daviations.GetFloat() * PreviousSDV_Ask &&
			(float)PreviousLargestBidVol >= PreviousAverageBidVolumePerLevel + Input_Standart_Daviations.GetFloat() * PreviousSDV_Bid &&
			PreviousLargestAskVolPrice == PreviousLargestBidVolPrice
			)
		{
			if (Want_Aggressive_Side_Signal.GetIndex() == 1)
			{
				if (PreviousAskNumOfSDV - PreviousBidNumOfSDV >= 0.1 * Input_Standart_Daviations.GetFloat())
				{
					if (PreviousAskNumOfSDV - PreviousBidNumOfSDV >= 0.3 * Input_Standart_Daviations.GetFloat()) Buyers_Aggressive_Side_Signal_3[sc.Index - 1] = sc.High[sc.Index - 1] + Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
					else if (PreviousAskNumOfSDV - PreviousBidNumOfSDV >= 0.2 * Input_Standart_Daviations.GetFloat()) Buyers_Aggressive_Side_Signal_2[sc.Index - 1] = sc.High[sc.Index - 1] + Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
					else Buyers_Aggressive_Side_Signal_1[sc.Index - 1] = sc.High[sc.Index - 1] + Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
				}
				else if (PreviousBidNumOfSDV - PreviousAskNumOfSDV >= 0.1 * Input_Standart_Daviations.GetFloat())
				{
					if (PreviousBidNumOfSDV - PreviousAskNumOfSDV >= 0.3 * Input_Standart_Daviations.GetFloat()) Sellers_Aggressive_Side_Signal_3[sc.Index - 1] = sc.Low[sc.Index - 1] - Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
					else if (PreviousBidNumOfSDV - PreviousAskNumOfSDV >= 0.2 * Input_Standart_Daviations.GetFloat()) Sellers_Aggressive_Side_Signal_2[sc.Index - 1] = sc.Low[sc.Index - 1] - Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
					else Sellers_Aggressive_Side_Signal_1[sc.Index - 1] = sc.Low[sc.Index - 1] - Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;

				}
			}

			if (Want_Horizontal_Ray.GetYesNo()) {
				sc.AddLineUntilFutureIntersection
				(sc.Index - 1// where to start drawing
					, 3 //ExhaustionType.GetIndex()  // LineIDForBar
					, PreviousLargestAskVolPrice// The price level of the line
					, RGB(128, 64, 64)
					, ExtendingLine.LineWidth
					, ExtendingLine.LineStyle
					, 0 //DisplayValueLabel.GetYesNo()
					, false //DisplayNameLabel // true/false
					, ""// "string" or string variable
				);
			}

		}
		else
		{

			if ((float)PreviousLargestBidVol >= PreviousAverageBidVolumePerLevel + Input_Standart_Daviations.GetFloat() * PreviousSDV_Bid)
			{
				if (Want_Aggressive_Side_Signal.GetIndex() == 1)
				{
					if (PreviousBidNumOfSDV - PreviousAskNumOfSDV >= 0.1 * Input_Standart_Daviations.GetFloat())
					{
						if (PreviousBidNumOfSDV - PreviousAskNumOfSDV >= 0.3 * Input_Standart_Daviations.GetFloat()) Sellers_Aggressive_Side_Signal_3[sc.Index - 1] = sc.Low[sc.Index - 1] - Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
						else if (PreviousBidNumOfSDV - PreviousAskNumOfSDV >= 0.2 * Input_Standart_Daviations.GetFloat()) Sellers_Aggressive_Side_Signal_2[sc.Index - 1] = sc.Low[sc.Index - 1] - Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
						else Sellers_Aggressive_Side_Signal_1[sc.Index - 1] = sc.Low[sc.Index - 1] - Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;

					}
				}

				if (Want_Horizontal_Ray.GetYesNo()) {
					sc.AddLineUntilFutureIntersection
					(sc.Index - 1// where to start drawing
						, 2//ExhaustionType.GetIndex()  // LineIDForBar
						, PreviousLargestBidVolPrice// The price level of the line
						, LargeBidHighlightTopLine.PrimaryColor
						, BidLineWidth
						, ExtendingLine.LineStyle
						, 0 //DisplayValueLabel.GetYesNo()
						, false //DisplayNameLabel // true/false
						, ""// "string" or string variable
					);
				}
			}

			if ((float)PreviousLargestAskVol >= PreviousAverageAskVolumePerLevel + Input_Standart_Daviations.GetFloat() * PreviousSDV_Ask)
			{
				if (Want_Aggressive_Side_Signal.GetIndex() == 1)
				{
					if (PreviousAskNumOfSDV - PreviousBidNumOfSDV >= 0.1 * Input_Standart_Daviations.GetFloat())
					{
						if (PreviousAskNumOfSDV - PreviousBidNumOfSDV >= 0.3 * Input_Standart_Daviations.GetFloat()) Buyers_Aggressive_Side_Signal_3[sc.Index - 1] = sc.High[sc.Index - 1] + Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
						else if (PreviousAskNumOfSDV - PreviousBidNumOfSDV >= 0.2 * Input_Standart_Daviations.GetFloat()) Buyers_Aggressive_Side_Signal_2[sc.Index - 1] = sc.High[sc.Index - 1] + Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
						else Buyers_Aggressive_Side_Signal_1[sc.Index - 1] = sc.High[sc.Index - 1] + Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
					}
				}

				if (Want_Horizontal_Ray.GetYesNo()) {
					sc.AddLineUntilFutureIntersection
					(sc.Index - 1// where to start drawing
						, 1 //ExhaustionType.GetIndex()  // LineIDForBar
						, PreviousLargestAskVolPrice// The price level of the line
						, LargeAskHighlightTopLine.PrimaryColor
						, AskLineWidth
						, ExtendingLine.LineStyle
						, 0 //DisplayValueLabel.GetYesNo()
						, false //DisplayNameLabel // true/false2
						, ""// "string" or string variable
					);
				}

			}
		}

	}

	RelativeLargestAskVol = (float)LargestAskVol / SessionAvgLargestAskVol;
	RelativeLargestBidVol = (float)LargestBidVol / SessionAvgLargestBidVol;	

	if (Want_Aggressive_Side_Signal.GetIndex() == 2)
	{
		if (RelativeLargestBidVol >= 1.5 && RelativeLargestBidVol < 2.0) Sellers_Aggressive_Side_Signal_1[sc.Index] = sc.Low[sc.Index] - (float)Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
		else if (RelativeLargestBidVol >= 2 && RelativeLargestBidVol < 3.0) Sellers_Aggressive_Side_Signal_2[sc.Index] = sc.Low[sc.Index] - (float)Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
		else if (RelativeLargestBidVol >= 3) Sellers_Aggressive_Side_Signal_3[sc.Index] = sc.Low[sc.Index] - (float)Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;

		if (RelativeLargestAskVol >= 1.5 && RelativeLargestAskVol < 2.0) Buyers_Aggressive_Side_Signal_1[sc.Index] = sc.High[sc.Index] + (float)Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
		else if (RelativeLargestAskVol >= 2 && RelativeLargestAskVol < 3.0) Buyers_Aggressive_Side_Signal_2[sc.Index] = sc.High[sc.Index] + (float)Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
		else if (RelativeLargestAskVol >= 3) Buyers_Aggressive_Side_Signal_3[sc.Index] = sc.High[sc.Index] + (float)Distance_Of_Aggressive_Side_Signal_From_Bar.GetInt() * sc.TickSize;
	}

	PreviousLargestAskVol = LargestAskVol;
	PreviousLargestBidVol = LargestBidVol;
	PreviousLargestAskVolPrice = LargestAskVolPrice;
	PreviousLargestBidVolPrice = LargestBidVolPrice;
	PreviousAverageAskVolumePerLevel = AverageAskVolumePerLevel;
	PreviousAverageBidVolumePerLevel = AverageBidVolumePerLevel;
	PreviousSDV_Ask = SDV_Ask;
	PreviousSDV_Bid = SDV_Bid;
	PreviousAskNumOfSDV = AskNumOfSDV;
	PreviousBidNumOfSDV = BidNumOfSDV;
	PreviousIndex = sc.Index;
	PreviousReplayStatus = sc.ReplayStatus;

	if (sc.LastCallToFunction || sc.Index == 0)
	{
		PreviousLargestAskVolPrice = 0.0;
		PreviousLargestBidVolPrice = 0.0;
		PreviousAverageAskVolumePerLevel = 0.0;
		PreviousAverageBidVolumePerLevel = 0.0;
		PreviousSDV_Ask = 0.0;
		PreviousSDV_Bid = 0.0;
		PreviousAskNumOfSDV = 0.0;
		PreviousBidNumOfSDV = 0.0;
		PreviousIndex = 0;
		PreviousLargestAskVol = 0;
		PreviousLargestBidVol = 0;
		SessionAvgLargestAskVol = 0;
		SessionAvgLargestBidVol = 0;
		//Status = "";
		BarCounter_Session = 0;

		for (int i = 0; i <= sc.Index; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 14000000 + i);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 15000000 + i);
		}
	}
}

