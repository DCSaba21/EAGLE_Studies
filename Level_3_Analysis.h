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

SCSFExport scsf_Level_3_Analysis(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef Current_Price_Line = sc.Subgraph[SGIndex++];
	SCSubgraphRef CumAskAbsOnBarSignalTopLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef CumAskAbsOnBarSignalBottomLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef CumBidAbsOnBarSignalTopLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef CumBidAbsOnBarSignalBottomLine = sc.Subgraph[SGIndex++];



	int InputIndex = 0;
	SCInputRef Columns_Width_And_Position = sc.Input[InputIndex++];
	SCInputRef Left_Column_Position = sc.Input[InputIndex++];
	SCInputRef Right_Column_Position = sc.Input[InputIndex++];
	SCInputRef Color_Settings = sc.Input[InputIndex++];
	SCInputRef Top_Text_Color = sc.Input[InputIndex++];
	SCInputRef Positive_Pull_Stack_Text_Color = sc.Input[InputIndex++];
	SCInputRef Positive_Pull_Stack_Bars_Outline_Color = sc.Input[InputIndex++];
	SCInputRef Positive_Pull_Stack_Bars_Fill_Color = sc.Input[InputIndex++];
	SCInputRef Negative_Pull_Stack_Text_Color = sc.Input[InputIndex++];
	SCInputRef Negative_Pull_Stack_Bars_Outline_Color = sc.Input[InputIndex++];
	SCInputRef Negative_Pull_Stack_Bars_Fill_Color = sc.Input[InputIndex++];
	SCInputRef Buyers_Absorption_Text_Color = sc.Input[InputIndex++];
	SCInputRef Buyers_Absorption_Bars_Outline_Color = sc.Input[InputIndex++];
	SCInputRef Buyers_Absorption_Bars_Fill_Color = sc.Input[InputIndex++];
	SCInputRef Sellers_Absorption_Text_Color = sc.Input[InputIndex++];
	SCInputRef Sellers_Absorption_Bars_Outline_Color = sc.Input[InputIndex++];
	SCInputRef Sellers_Absorption_Bars_Fill_Color = sc.Input[InputIndex++];
	SCInputRef Buyers_Absorption_Sellers_Stacking_OutLine_Color = sc.Input[InputIndex++];
	SCInputRef Buyers_Absorption_Sellers_Pulling_OutLine_Color = sc.Input[InputIndex++];
	SCInputRef Sellers_Absorption_Buyers_Stacking_OutLine_Color = sc.Input[InputIndex++];
	SCInputRef Sellers_Absorption_Buyers_Pulling_OutLine_Color = sc.Input[InputIndex++];
	SCInputRef Bar_Positive_Delta_Color = sc.Input[InputIndex++];
	SCInputRef Bar_Negative_Delta_Color = sc.Input[InputIndex++];
	SCInputRef Bar_Positive_Absorptions_Sum_Color = sc.Input[InputIndex++];
	SCInputRef Bar_Negative_Absorptions_Sum_Color = sc.Input[InputIndex++];
	SCInputRef Buyers_Absorption_On_Bar_Signal_Color = sc.Input[InputIndex++];
	SCInputRef Sellers_Absorption_On_Bar_Signal_Color = sc.Input[InputIndex++];
	SCInputRef More_Buying_Imbalance_Color = sc.Input[InputIndex++];
	SCInputRef More_Selling_Imbalance_Color = sc.Input[InputIndex++];
	SCInputRef Other_Parameters = sc.Input[InputIndex++];
	SCInputRef Bars_Outline_Width = sc.Input[InputIndex++];
	SCInputRef AbsWithPullStack_Outline_Width = sc.Input[InputIndex++];
	SCInputRef Font_Size = sc.Input[InputIndex++];
	SCInputRef Cumulative_Absorption_Tolerance = sc.Input[InputIndex++];
	SCInputRef Bars_Transparency = sc.Input[InputIndex++];
	SCInputRef Draw_Values_Under_Bars = sc.Input[InputIndex++];
	SCInputRef Draw_Absorption_On_Bars = sc.Input[InputIndex++];
	SCInputRef Absorption_On_Bars_Signal_Threshold = sc.Input[InputIndex++];
	SCInputRef Pull_Stack__Threshold = sc.Input[InputIndex++];
	SCInputRef Number_Of_Depth_Levels = sc.Input[InputIndex++];
	SCInputRef Show_Current_Price_Line = sc.Input[InputIndex++];
	SCInputRef Reset_Custom_Button_Number = sc.Input[InputIndex++];
	SCInputRef Blank_Line_1 = sc.Input[InputIndex++];
	SCInputRef Blank_Line_2 = sc.Input[InputIndex++];
	SCInputRef Imbalance_Ratio = sc.Input[InputIndex++];
	SCInputRef Aggression_Meter_Reset_Mode = sc.Input[InputIndex++];
	SCInputRef Want_TotalVol_Column = sc.Input[InputIndex++];
	SCInputRef Want_Aggression_Bar_Column = sc.Input[InputIndex++];
	SCInputRef Want_Absorption_Sound_Alert = sc.Input[InputIndex++];
	SCInputRef Buyers_Absorption_Signal_Sound_Alert_Number = sc.Input[InputIndex++];
	SCInputRef Sellers_Absorption_Signal_Sound_Alert_Number = sc.Input[InputIndex++];
	SCInputRef Level_Taken_With_Pulling_Threashold = sc.Input[InputIndex++];
	SCInputRef Ask_Level_Taken_With_Pulling_Sound_Alert_Number = sc.Input[InputIndex++];
	SCInputRef Bid_Level_Taken_With_Pulling_Sound_Alert_Number = sc.Input[InputIndex++];
	SCInputRef Want_Sound_Alert_For_Level_Taken_With_Pulling = sc.Input[InputIndex++];
	SCInputRef Ask_Level_Taken_With_Pulling_Signal_Color = sc.Input[InputIndex++];
	SCInputRef Bid_Level_Taken_With_Pulling_Signal_Color = sc.Input[InputIndex++];
	SCInputRef Level_Taken_With_Pulling_Signal_Size = sc.Input[InputIndex++];
	SCInputRef Want_Cumulative_Absorption_Column = sc.Input[InputIndex++];
	SCInputRef Want_Recent_Absorption_Column = sc.Input[InputIndex++];
	SCInputRef Want_Pull_Stack_Column = sc.Input[InputIndex++];
	SCInputRef Use_Reset_Time = sc.Input[InputIndex++];
	SCInputRef Reset_Time_1 = sc.Input[InputIndex++];
	SCInputRef Reset_Time_2 = sc.Input[InputIndex++];

	//SCInputRef Aggression_Meter_Reset_Custom_Button_Number = sc.Input[InputIndex++];\\

//
	if (sc.SetDefaults)
	{
		sc.GraphName = "Level_3_Analysis";

		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		sc.GraphRegion = 0;
		sc.UpdateAlways = 1;
		sc.CalculationPrecedence = VERY_LOW_PREC_LEVEL;		
		sc.ReceivePointerEvents = ACS_RECEIVE_POINTER_EVENTS_ALWAYS;

		//SubGraphs
		Current_Price_Line.Name = "Current Price Line";
		Current_Price_Line.PrimaryColor = RGB(0, 255, 0);
		Current_Price_Line.SecondaryColorUsed = 1;
		Current_Price_Line.SecondaryColor = RGB(255, 0, 0);
		Current_Price_Line.DrawStyle = DRAWSTYLE_LINE;
		Current_Price_Line.LineStyle = LINESTYLE_DASHDOTDOT;
		Current_Price_Line.LineWidth = 1;

		CumAskAbsOnBarSignalTopLine.Name = "Buyers Absorption On Bar";
		CumAskAbsOnBarSignalTopLine.DrawStyle = DRAWSTYLE_FILLRECTBOTTOM_TRANSPARENT;
		CumAskAbsOnBarSignalTopLine.PrimaryColor = RGB(0, 255, 0); //Buyers_Absorption_Text_Color.GetColor();

		CumAskAbsOnBarSignalBottomLine.Name = "Buyers Absorption On Bar";
		CumAskAbsOnBarSignalBottomLine.DrawStyle = DRAWSTYLE_FILLRECTTOP_TRANSPARENT;
		CumAskAbsOnBarSignalBottomLine.PrimaryColor = RGB(0, 255, 0); //Buyers_Absorption_Text_Color.GetColor();

		CumBidAbsOnBarSignalTopLine.Name = "Sellers Absorption On Bar";
		CumBidAbsOnBarSignalTopLine.DrawStyle = DRAWSTYLE_FILLRECTBOTTOM_TRANSPARENT;
		CumBidAbsOnBarSignalTopLine.PrimaryColor = RGB(255, 0, 0);  //Sellers_Absorption_Text_Color.GetColor();

		CumBidAbsOnBarSignalBottomLine.Name = "Sellers Absorption On Bar";
		CumBidAbsOnBarSignalBottomLine.DrawStyle = DRAWSTYLE_FILLRECTTOP_TRANSPARENT;
		CumBidAbsOnBarSignalBottomLine.PrimaryColor = RGB(255, 0, 0); //Sellers_Absorption_Text_Color.GetColor();/		

		//Inputs

		Columns_Width_And_Position.Name = "========== Columns Width & Position ===========================";
		Columns_Width_And_Position.SetString("");

		Left_Column_Position.Name = "Left Column Position (Distance From Right Edge of Chart 1-150)";
		Left_Column_Position.SetInt(76);

		Right_Column_Position.Name = "Right Column Position (Distance From Right Edge of Chart 1-150)";
		Right_Column_Position.SetInt(36);


		Color_Settings.Name = "========== Color Settings ================================================";
		Color_Settings.SetString("");

		Top_Text_Color.Name = "Top Text Color";
		Top_Text_Color.SetColor(255, 255, 255);

		Positive_Pull_Stack_Text_Color.Name = "Positive Pull Stack Text Color";
		Positive_Pull_Stack_Text_Color.SetColor(0, 255, 255);

		Positive_Pull_Stack_Bars_Outline_Color.Name = "Positive Pull Stack Bars Outline Color";
		Positive_Pull_Stack_Bars_Outline_Color.SetColor(0, 255, 255);

		Positive_Pull_Stack_Bars_Fill_Color.Name = "Positive Pull Stack Bars Fill Color";
		Positive_Pull_Stack_Bars_Fill_Color.SetColor(64, 128, 128);

		Negative_Pull_Stack_Text_Color.Name = "Negative Pull Stack Text Color";
		Negative_Pull_Stack_Text_Color.SetColor(255, 255, 0);

		Negative_Pull_Stack_Bars_Outline_Color.Name = "Negative Pull Stack Bars Outline Color";
		Negative_Pull_Stack_Bars_Outline_Color.SetColor(255, 255, 0);

		Negative_Pull_Stack_Bars_Fill_Color.Name = "Negative Pull Stack Bars Fill Color";
		Negative_Pull_Stack_Bars_Fill_Color.SetColor(64, 128, 128);

		Buyers_Absorption_Text_Color.Name = "Buyers Absorption Text Color";
		Buyers_Absorption_Text_Color.SetColor(0, 255, 0);

		Buyers_Absorption_Bars_Outline_Color.Name = "Buyers Absorption Bars Outline Color";
		Buyers_Absorption_Bars_Outline_Color.SetColor(0, 255, 0);

		Buyers_Absorption_Bars_Fill_Color.Name = "Buyers Absorption Bars Fill Color";
		Buyers_Absorption_Bars_Fill_Color.SetColor(64, 128, 128);

		Sellers_Absorption_Text_Color.Name = "Sellers Absorption Text Color";
		Sellers_Absorption_Text_Color.SetColor(255, 0, 0);

		Sellers_Absorption_Bars_Outline_Color.Name = "Sellers Absorption Bars Outline Color";
		Sellers_Absorption_Bars_Outline_Color.SetColor(255, 0, 0);

		Sellers_Absorption_Bars_Fill_Color.Name = "Sellers Absorption Bars Fill Color";
		Sellers_Absorption_Bars_Fill_Color.SetColor(64, 128, 128);

		Buyers_Absorption_Sellers_Stacking_OutLine_Color.Name = "L3A Signal - Buyers Absorption & Sellers Stacking OutLine Color";
		Buyers_Absorption_Sellers_Stacking_OutLine_Color.SetColor(255, 0, 0);

		Buyers_Absorption_Sellers_Pulling_OutLine_Color.Name = "L3A Signal - Buyers Absorption & Sellers Pulling OutLine Color";
		Buyers_Absorption_Sellers_Pulling_OutLine_Color.SetColor(255, 130, 130);

		Sellers_Absorption_Buyers_Stacking_OutLine_Color.Name = "L3A Signal - Sellers Absorption & Buyers Stacking OutLine Color";
		Sellers_Absorption_Buyers_Stacking_OutLine_Color.SetColor(0, 255, 0);

		Sellers_Absorption_Buyers_Pulling_OutLine_Color.Name = "L3A Signal - Sellers Absorption &_Buyers Pulling OutLine Color";
		Sellers_Absorption_Buyers_Pulling_OutLine_Color.SetColor(187, 255, 187);

		Bar_Positive_Delta_Color.Name = "Bar's Positive Delta Color";
		Bar_Positive_Delta_Color.SetColor(0, 255, 0);

		Bar_Negative_Delta_Color.Name = "Bar's Negative Delta Color";
		Bar_Negative_Delta_Color.SetColor(255, 0, 0);

		Bar_Positive_Absorptions_Sum_Color.Name = "Bar's Positive Recent Absorptions Sum Color";
		Bar_Positive_Absorptions_Sum_Color.SetColor(0, 255, 0);

		Bar_Negative_Absorptions_Sum_Color.Name = "Bar's Negative Recent Absorptions Sum Color";
		Bar_Negative_Absorptions_Sum_Color.SetColor(255, 0, 0);

		More_Buying_Imbalance_Color.Name = "More Buying Imbalance Signal Color";
		More_Buying_Imbalance_Color.SetColor(255, 255, 0);

		More_Selling_Imbalance_Color.Name = "More Selling Imbalance Signal Color";
		More_Selling_Imbalance_Color.SetColor(255, 255, 0);


		Other_Parameters.Name = "========== Other Parameters ==================================================";
		Other_Parameters.SetString("");

		Bars_Outline_Width.Name = "Bars Outline Width";
		Bars_Outline_Width.SetInt(2);

		AbsWithPullStack_Outline_Width.Name = "Absorption With Pull / Stack Rectangle Outline_Width";
		AbsWithPullStack_Outline_Width.SetInt(2);

		Font_Size.Name = "Font_Size";
		Font_Size.SetInt(9);

		Cumulative_Absorption_Tolerance.Name = "Cumulative Absorption Tolerance (Ticks)";
		Cumulative_Absorption_Tolerance.SetInt(4);

		Bars_Transparency.Name = "Bars_Transparency (1-100)";
		Bars_Transparency.SetInt(65);

		Draw_Values_Under_Bars.Name = "Draw Values Under Bars?";
		Draw_Values_Under_Bars.SetYesNo(0);

		Draw_Absorption_On_Bars.Name = "Draw Absorption Signals On Bars?";
		Draw_Absorption_On_Bars.SetYesNo(1);

		Absorption_On_Bars_Signal_Threshold.Name = "Absorption Threshold (%)";
		Absorption_On_Bars_Signal_Threshold.SetInt(300);

		Pull_Stack__Threshold.Name = "Pull/Stack Threshold (%)";
		Pull_Stack__Threshold.SetInt(300);

		Number_Of_Depth_Levels.Name = "Number Of Depth Levels For Pull/Stack Column";
		Number_Of_Depth_Levels.SetInt(10);

		Show_Current_Price_Line.Name = "Draw Current Price Line?";
		Show_Current_Price_Line.SetYesNo(1);

		//Reset_Custom_Button_Number.Name = "Reset Custom Button Number";
		//Reset_Custom_Button_Number.SetInt(2);

		Blank_Line_1.Name = "";
		Blank_Line_1.SetString("");

		Blank_Line_2.Name = "";
		Blank_Line_2.SetString("");

		Imbalance_Ratio.Name = "Minimal Ratio for Imbalance Signal";
		Imbalance_Ratio.SetFloat(3);

		Aggression_Meter_Reset_Mode.Name = "Aggression Meter Reset Mode";
		Aggression_Meter_Reset_Mode.SetCustomInputStrings("Reset When The Best Bid or Best Ask Change; Reset With Right Click Menu");
		Aggression_Meter_Reset_Mode.SetCustomInputIndex(1);

		Want_TotalVol_Column.Name = "Want a TotalVol Column?";
		Want_TotalVol_Column.SetYesNo(1);

		Want_Aggression_Bar_Column.Name = "Want the Aggression Bar Column?";
		Want_Aggression_Bar_Column.SetYesNo(1);

		Want_Absorption_Sound_Alert.Name = "Want Sound Alert For Large Absorption Signals?";
		Want_Absorption_Sound_Alert.SetYesNo(0);

		Buyers_Absorption_Signal_Sound_Alert_Number.Name = "Buyers Absorption Signal Sound Alert Number";
		Buyers_Absorption_Signal_Sound_Alert_Number.SetInt(31);

		Sellers_Absorption_Signal_Sound_Alert_Number.Name = "Sellesr Absorption Signal Sound Alert Number";
		Sellers_Absorption_Signal_Sound_Alert_Number.SetInt(32);

		Level_Taken_With_Pulling_Threashold.Name = "Level Taken With Pulling Threashold";
		Level_Taken_With_Pulling_Threashold.SetInt(50);

		Ask_Level_Taken_With_Pulling_Sound_Alert_Number.Name = "Ask Level Taken With Pulling Sound Alert Number";
		Ask_Level_Taken_With_Pulling_Sound_Alert_Number.SetInt(34);

		Bid_Level_Taken_With_Pulling_Sound_Alert_Number.Name = "Bid Level Taken With Pulling Sound Alert Number";
		Bid_Level_Taken_With_Pulling_Sound_Alert_Number.SetInt(35);

		Want_Sound_Alert_For_Level_Taken_With_Pulling.Name = "Want sound slert for Level Taken With Pulling signals?";
		Want_Sound_Alert_For_Level_Taken_With_Pulling.SetYesNo(0);

		Ask_Level_Taken_With_Pulling_Signal_Color.Name = "Color of Ask level taken with pulling signal";
		Ask_Level_Taken_With_Pulling_Signal_Color.SetColor(255, 255, 0);

		Bid_Level_Taken_With_Pulling_Signal_Color.Name = "Color of Bid level taken with pulling signal";
		Bid_Level_Taken_With_Pulling_Signal_Color.SetColor(255, 255, 0);

		Level_Taken_With_Pulling_Signal_Size.Name = "Size of level taken with pulling signal";
		Level_Taken_With_Pulling_Signal_Size.SetInt(10);

		Want_Cumulative_Absorption_Column.Name = "Want Cumulative Absorption Column?";
		Want_Cumulative_Absorption_Column.SetYesNo(1);

		Want_Recent_Absorption_Column.Name = "Want Recent Absorption Column?";
		Want_Recent_Absorption_Column.SetYesNo(1);

		Want_Pull_Stack_Column.Name = "Want Pull Stack Column?";
		Want_Pull_Stack_Column.SetYesNo(1);

		Use_Reset_Time.Name = "Use Reset Time?";
		Use_Reset_Time.SetYesNo(0);

		Reset_Time_1.Name = "Reset Time 1";
		Reset_Time_1.SetTime(HMS_TIME(9, 30, 0));

		Reset_Time_2.Name = "Reset Time 2";
		Reset_Time_2.SetTime(HMS_TIME(18, 0, 0));



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

	SCString str; // for sending messages to log	

	 // +++  return section (to avoid cpu exceptions) ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	if (sc.ServerConnectionState != SCS_CONNECTED && sc.IsReplayRunning() == 0) return;
	c_SCTimeAndSalesArray TimeSales;
	sc.GetTimeAndSales(TimeSales);
	if (TimeSales.Size() == 0) {
		//str = "Return from 282"; sc.AddMessageToLog(str, 0);
		return;  // No Time and Sales data available for the symbol
	}
	/*if ((sc.SymbolData->BidDOM[0].Volume == NULL || sc.SymbolData->AskDOM[0].Volume == NULL) && sc.IsReplayRunning() == 0){
		return; //return if no depth data
	}*/
	if ((sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask) == NULL || sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid) == NULL) && sc.IsReplayRunning() == 0) {
		return;
	}
	int& PreviousReplayStatus = sc.GetPersistentInt(16);
	if (sc.ReplayStatus == REPLAY_PAUSED) {
		PreviousReplayStatus = REPLAY_PAUSED;
		return;
	}


	//CreateDirectory(L"\L3A_Folder", NULL); // create the folder for the on bar signals if the folder doesn't exist

	// ++++++++++++++++++++++++++++++++ start memory allocation for Persistent arrays ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	int* p_AskRecentAbsorptions = (int*)sc.GetPersistentPointer(1);
	int* p_BidRecentAbsorptions = (int*)sc.GetPersistentPointer(2);
	int* p_AskCumulativeAbsorptions = (int*)sc.GetPersistentPointer(3);
	int* p_BidCumulativeAbsorptions = (int*)sc.GetPersistentPointer(4);
	int* p_RecentAskAbsToBeErased = (int*)sc.GetPersistentPointer(5);
	int* p_RecentBidAbsToBeErased = (int*)sc.GetPersistentPointer(6);
	//int* p_BeforeClearedCumAbsorption = (int*)sc.GetPersistentPointer(7);
	int* p_AskTotalAbsorptions = (int*)sc.GetPersistentPointer(8);
	int* p_BidTotalAbsorptions = (int*)sc.GetPersistentPointer(9);

	if (p_AskRecentAbsorptions == NULL) {
		//Allocate an array of 1024 ints.
		p_AskRecentAbsorptions = (int*)sc.AllocateMemory(1024 * sizeof(int));
		if (p_AskRecentAbsorptions != NULL) sc.SetPersistentPointer(1, p_AskRecentAbsorptions);
	}

	if (p_BidRecentAbsorptions == NULL) {
		//Allocate an array of 1024 ints.
		p_BidRecentAbsorptions = (int*)sc.AllocateMemory(1024 * sizeof(int));
		if (p_BidRecentAbsorptions != NULL) sc.SetPersistentPointer(2, p_BidRecentAbsorptions);
	}

	if (p_AskCumulativeAbsorptions == NULL) {
		//Allocate an array of 1024 ints.
		p_AskCumulativeAbsorptions = (int*)sc.AllocateMemory(1024 * sizeof(int));
		if (p_AskCumulativeAbsorptions != NULL) sc.SetPersistentPointer(3, p_AskCumulativeAbsorptions);
	}

	if (p_BidCumulativeAbsorptions == NULL) {
		//Allocate an array of 1024 ints.
		p_BidCumulativeAbsorptions = (int*)sc.AllocateMemory(1024 * sizeof(int));
		if (p_BidCumulativeAbsorptions != NULL) sc.SetPersistentPointer(4, p_BidCumulativeAbsorptions);
	}

	if (p_RecentAskAbsToBeErased == NULL) {
		//Allocate an array of 1024 ints.
		p_RecentAskAbsToBeErased = (int*)sc.AllocateMemory(1024 * sizeof(int));
		if (p_RecentAskAbsToBeErased != NULL) sc.SetPersistentPointer(5, p_RecentAskAbsToBeErased);
	}

	if (p_RecentBidAbsToBeErased == NULL) {
		//Allocate an array of 1024 ints.
		p_RecentBidAbsToBeErased = (int*)sc.AllocateMemory(1024 * sizeof(int));
		if (p_RecentBidAbsToBeErased != NULL) sc.SetPersistentPointer(6, p_RecentBidAbsToBeErased);
	}

	/*if (p_BeforeClearedCumAbsorption == NULL) {
		//Allocate an array of 1024 ints.
		p_BeforeClearedCumAbsorption = (int*)sc.AllocateMemory(1024 * sizeof(int));
		if (p_BeforeClearedCumAbsorption != NULL) sc.SetPersistentPointer(7, p_BeforeClearedCumAbsorption);
	}*/

	if (p_AskTotalAbsorptions == NULL) {
		//Allocate an array of 1024 ints.
		p_AskTotalAbsorptions = (int*)sc.AllocateMemory(1024 * sizeof(int));
		if (p_AskTotalAbsorptions != NULL) sc.SetPersistentPointer(8, p_AskTotalAbsorptions);
	}

	if (p_BidTotalAbsorptions == NULL) {
		//Allocate an array of 1024 ints.
		p_BidTotalAbsorptions = (int*)sc.AllocateMemory(1024 * sizeof(int));
		if (p_BidTotalAbsorptions != NULL) sc.SetPersistentPointer(9, p_BidTotalAbsorptions);
	}
	// ++++++++++++++++++++++++  End of memory allocation +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// ++++++++++++++++++++++++   Most Variables Declaration +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	s_UseTool RecentAskAbsorptionText, RecentBidAbsorptionText, RecentAskAbsorptionBars, RecentBidAbsorptionBars;
	s_UseTool CumulativeAskAbsorptionText, CumulativeBidAbsorptionText, CumulativeAskAbsorptionBars, CumulativeBidAbsorptionBars;
	s_UseTool TotalAskAbsorptionText, TotalBidAbsorptionText, TotalAskAbsorptionBars, TotalBidAbsorptionBars;
	//s_UseTool CumAbsorptionBeforeClearedText, CumAbsorptionBeforeClearedBars;
	s_UseTool PullStackBidText, PullStackAskText, PullStackBidBars, PullStackAskBars;
	s_UseTool BarDelta, BarSumRecentAbsorptions;
	s_UseTool AskAbsWithPullStack, BidAbsWithPullStack;
	//s_UseTool TopText;
	s_UseTool CurrentPriceLine;
	s_UseTool Buyers_Meter_Bar, Sellers_Meter_Bar, Meter_Bar_Frame, Buyers_Meter_Text, Sellers_Meter_Text;
	s_UseTool Hor_Buyers_Meter_Bar, Hor_Sellers_Meter_Bar, Hor_Meter_Bar_Frame, Hor_Buyers_Meter_Text, Hor_Sellers_Meter_Text;
	s_UseTool Pulling_Alert_Visual;


	int64_t& LastProcessedSequence = sc.GetPersistentInt64(1);
	int& ArrayPriceDifference = sc.GetPersistentInt(2);
	int& LowestLineNumber = sc.GetPersistentInt(3);
	int& HighestLineNumber = sc.GetPersistentInt(4);
	int& OnlyOnce = sc.GetPersistentInt(5);
	int& LargestRecentAbsorption = sc.GetPersistentInt(6);
	int& LargestCumulativeAbsorption = sc.GetPersistentInt(7);
	int& PreviousLargestRecentAbsorption = sc.GetPersistentInt(8);
	int& PreviousLargestCumulativeAbsorption = sc.GetPersistentInt(9);
	int& FirstIndex = sc.GetPersistentInt(10);
	int& PreviousIndex = sc.GetPersistentInt(11);
	int& LargestAskCumAbsBar = sc.GetPersistentInt(12);
	int& LargestBidCumAbsBar = sc.GetPersistentInt(13);
	int& PreviousCumAskAbsOnBarSignalIndex = sc.GetPersistentInt(14);
	int& PreviousCumBidAbsOnBarSignalIndex = sc.GetPersistentInt(15);
	//int& PreviousReplayStatus = sc.GetPersistentInt(16); // moved up to return section
	int& UnderBarsTextCounter = sc.GetPersistentInt(17);
	int& PreviousWindowPixelWidth = sc.GetPersistentInt(18);
	int& LargestTotalAbsorption = sc.GetPersistentInt(19);
	int& PreviousLargestTotalAbsorption = sc.GetPersistentInt(20);
	int& PreviousLastTradeTime = sc.GetPersistentInt(21);
	int& Buyers_Meter = sc.GetPersistentInt(22);
	int& Sellers_Meter = sc.GetPersistentInt(23);
	int& Reset_L3A_MenuID = sc.GetPersistentInt(24);
	int& Reset_Aggression_Meter_MenuID = sc.GetPersistentInt(25);
	int& LargestBeforeClearedAbsorption = sc.GetPersistentInt(26);
	int& PreviousBidPullStackValue = sc.GetPersistentInt(27);
	int& PreviousAskPullStackValue = sc.GetPersistentInt(28);
	int& PullingAlertCounter = sc.GetPersistentInt(29);
	int& p_WantTotalVolColumn = sc.GetPersistentInt(30);
	int& p_WantCumulativeABsorptionColumn = sc.GetPersistentInt(31);
	int& p_WantRecentAbsorptionColmn = sc.GetPersistentInt(32);
	int& p_WantPullStackColumn = sc.GetPersistentInt(33);
	int& p_WantAgrressionBar = sc.GetPersistentInt(34);		
	int& Updated_Font_Size = sc.GetPersistentInt(35);
	int& L3_Text_Toggle_Menu_ID = sc.GetPersistentInt(36);
	int& RightClick_TextToggle_State = sc.GetPersistentInt(37);
	int& Previous_RightClick_TextToggle_State = sc.GetPersistentInt(38);

	float& HighestRecentAskAbsPrice = sc.GetPersistentFloat(1);
	float& LowestRecentAskAbsPrice = sc.GetPersistentFloat(2);
	float& HighestRecentBidAbsPrice = sc.GetPersistentFloat(3);
	float& LowestRecentBidAbsPrice = sc.GetPersistentFloat(4);
	float& LastAskTradePrice = sc.GetPersistentFloat(5);
	float& LastBidTradePrice = sc.GetPersistentFloat(6);
	float& PreviousCumAskAbsOnBarSignalPrice = sc.GetPersistentFloat(7);
	float& PreviousCumBidAbsOnBarSignalPrice = sc.GetPersistentFloat(8);
	float& PreviousAskPrice = sc.GetPersistentFloat(9);
	float& PreviousBidPrice = sc.GetPersistentFloat(10);

	SCString& PreviousChartName = sc.GetPersistentSCString(1);
	SCString ThisString; 


	int VolBarExtToRight, OneColumnWidth, Column1Position, Column2Position, Column3Position, Column4Position, Column5Position;
	int TotalColumnsWidth = Left_Column_Position.GetInt() - Right_Column_Position.GetInt();

	int NumberOfColumns = Want_TotalVol_Column.GetYesNo() * 2 + Want_Aggression_Bar_Column.GetYesNo() + Want_Cumulative_Absorption_Column.GetYesNo() + Want_Recent_Absorption_Column.GetYesNo() + Want_Pull_Stack_Column.GetYesNo();

	OneColumnWidth = (int)((float)TotalColumnsWidth / (float)NumberOfColumns);
	Column1Position = 150 - Left_Column_Position.GetInt();
	Column2Position = 150 - Left_Column_Position.GetInt() +
		1 * OneColumnWidth * Want_TotalVol_Column.GetYesNo() +
		Want_TotalVol_Column.GetYesNo() * 1;
	Column3Position = 150 - Left_Column_Position.GetInt() +
		2 * OneColumnWidth * (Want_TotalVol_Column.GetYesNo() && Want_Cumulative_Absorption_Column.GetYesNo()) +
		1 * OneColumnWidth * (Want_TotalVol_Column.GetYesNo() != Want_Cumulative_Absorption_Column.GetYesNo()) +
		2 * (Want_TotalVol_Column.GetYesNo() && Want_Cumulative_Absorption_Column.GetYesNo()) +
		1 * (Want_TotalVol_Column.GetYesNo() != Want_Cumulative_Absorption_Column.GetYesNo());
	Column4Position = Column3Position + OneColumnWidth * Want_Recent_Absorption_Column.GetYesNo() +
		2 * Want_Recent_Absorption_Column.GetYesNo();
	Column5Position = Column4Position + OneColumnWidth * Want_Aggression_Bar_Column.GetYesNo() +
		4 * Want_Aggression_Bar_Column.GetYesNo();


	int WindowPixelWidth = sc.StudyRegionRightCoordinate - sc.StudyRegionLeftCoordinate;
	float OneCharSCWidthUnits = ((float)Font_Size.GetInt() / (float)WindowPixelWidth) * 150.0f;
	int StringLength, StringSCLength, ChangeLengthFactor;

	int RecentAbsProfileVolUnit = 0; int CumulativeAbsProfileVolUnit = 0; int TotalAbsProfileVolUnit = 0; int BeforeClearedAbsVolUnit = 0;
	int RecentColumnSum = 0; int CumulativeColumnSum = 0; int NumberOfLevels = 0;
	float RecentColumnAvg = 0; float CumulativeColumnAvg = 0;
	int LargestPullStackVol = 0;

	if (ArrayPriceDifference == 0) ArrayPriceDifference = (int)(sc.Ask / sc.TickSize) - 500;
	int CurrentAskArrayIndex = (int)(sc.Ask / sc.TickSize) - ArrayPriceDifference;
	int CurrentBidArrayIndex = (int)(sc.Bid / sc.TickSize) - ArrayPriceDifference;

		
	SCDateTime DTV;
	int Year, Month, Day;
	SCString FileName, ChartName;
	DTV = sc.LatestDateTimeForLastBar;
	DTV.GetDateYMD(Year, Month, Day);
	ChartName.Format("%s", sc.GetChartName(sc.ChartNumber).GetChars());
	//FileName.Format("L3A_Folder\\L3A_Data_%i%i%i_%s.csv", Month, Day, Year, ChartName.GetChars());
	FileName.Format("L3A_Data_%i%i%i_%s.csv", Month, Day, Year, ChartName.GetChars());


	// Add chart short cut menu item
	if (Reset_L3A_MenuID <= 0) Reset_L3A_MenuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "Reset L3A");
	if (Reset_Aggression_Meter_MenuID <= 0) Reset_Aggression_Meter_MenuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "Reset Aggression Meter");
	if (L3_Text_Toggle_Menu_ID <= 0) L3_Text_Toggle_Menu_ID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "L3A Text Toggle");

	if (sc.MenuEventID != 0 && sc.MenuEventID == L3_Text_Toggle_Menu_ID)
	{
		if (RightClick_TextToggle_State == 0) RightClick_TextToggle_State = 1;
		else if (RightClick_TextToggle_State == 1) RightClick_TextToggle_State = 0;

	}	

	if (RightClick_TextToggle_State == 1) Updated_Font_Size = 1;
	else Updated_Font_Size = Font_Size.GetInt();
	// ++++++++++++  Only Once ----> this is to be carried out only on  the first cycle of the study  +++++++++++++++++++++++++++++++++++++++++++++++++++

	if (OnlyOnce == 0) {
		HighestRecentAskAbsPrice = sc.Ask;
		LowestRecentAskAbsPrice = sc.Ask;
		HighestRecentBidAbsPrice = sc.Bid;
		LowestRecentBidAbsPrice = sc.Bid;
		LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence;
		HighestLineNumber = (int)(sc.Ask / sc.TickSize) + 10100000;
		LowestLineNumber = (int)(sc.Bid / sc.TickSize) + 10100000; // otherwise we will never get a line number lower.
	}

	// ++++++++++++++++++++++++     Load Historical On Bars Abs (sc.UpdateStartIndex == 0)  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	if (sc.UpdateStartIndex == 0) {

		SCString TradeType;
		float SignalPrice;
		int SignalIndex;		
	}

	//+++++++++++++++++++++++++++++++++ Reset Absorption Columns To Zero ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (sc.MenuEventID != 0 && sc.MenuEventID == Reset_L3A_MenuID
		|| sc.ReplayStatus == REPLAY_RUNNING && PreviousReplayStatus == REPLAY_STOPPED
		|| (Use_Reset_Time.GetYesNo() == 1 &&
			(PreviousLastTradeTime < Reset_Time_1.GetTime() && sc.LatestDateTimeForLastBar.GetTime() >= Reset_Time_1.GetTime()
				|| PreviousLastTradeTime < Reset_Time_2.GetTime() && sc.LatestDateTimeForLastBar.GetTime() >= Reset_Time_2.GetTime()))
		|| p_WantTotalVolColumn != Want_TotalVol_Column.GetYesNo()
		|| p_WantCumulativeABsorptionColumn != Want_Cumulative_Absorption_Column.GetYesNo()
		|| p_WantRecentAbsorptionColmn != Want_Recent_Absorption_Column.GetYesNo()
		|| p_WantPullStackColumn != Want_Pull_Stack_Column.GetYesNo()
		|| p_WantAgrressionBar != Want_Aggression_Bar_Column.GetInt()) {
		for (float AskLoopPrice = LowestRecentAskAbsPrice; AskLoopPrice <= HighestRecentAskAbsPrice; AskLoopPrice += sc.TickSize) {
			int LoopCurrentAskArrayIndex = (int)(AskLoopPrice / sc.TickSize) - ArrayPriceDifference;
			p_AskRecentAbsorptions[LoopCurrentAskArrayIndex] = 0;
			p_AskCumulativeAbsorptions[LoopCurrentAskArrayIndex] = 0;
			p_RecentAskAbsToBeErased[LoopCurrentAskArrayIndex] = 0;
			//p_BeforeClearedCumAbsorption[LoopCurrentAskArrayIndex] = 0;
			p_AskTotalAbsorptions[LoopCurrentAskArrayIndex] = 0;
		}
		for (float BidLoopPrice = HighestRecentBidAbsPrice; BidLoopPrice >= LowestRecentBidAbsPrice; BidLoopPrice -= sc.TickSize) {
			int LoopCurrentBidArrayIndex = (int)(BidLoopPrice / sc.TickSize) - ArrayPriceDifference;
			p_BidRecentAbsorptions[LoopCurrentBidArrayIndex] = 0;
			p_BidCumulativeAbsorptions[LoopCurrentBidArrayIndex] = 0;
			p_RecentBidAbsToBeErased[LoopCurrentBidArrayIndex] = 0;
			//p_BeforeClearedCumAbsorption[LoopCurrentBidArrayIndex] = 0;
			p_BidTotalAbsorptions[LoopCurrentBidArrayIndex] = 0;
		}

		// Delete all recent and cumulative and Total absorption text and bars
		for (int i = LowestLineNumber - 300; i <= HighestLineNumber + 300; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i); // line numbers of text
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 2000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 4000); // line numbers of text
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 6000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 8000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 10000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 12000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 14000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 16000); //line numbers of bars
		}
		// Delete all Pull/Stack text and bars
		for (int i = 0; i <= Number_Of_Depth_Levels.GetInt(); i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10200001 + i); // line numbers of text
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10200401 + i); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10200000 - i); // line numbers of text
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10200400 - i); //line numbers of bars
		}


		// Delete all Under Bars Text
		for (int i = 10201000; i <= 10202000 + 2 + UnderBarsTextCounter; i += 2) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1);
		}

		// Delete all L3A Rectangles
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203000);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203001);

		//Delete Meter_Bars
		//sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203005);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203006);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203007);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203008);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203009);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203010);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203011);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203012);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203013);

		//Delete Pulling Alert SignalDataString
		for (int i = 0; i <= PullingAlertCounter; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 12000000 + i);
		}



		ArrayPriceDifference = (int)(sc.Ask / sc.TickSize) - 500;
		HighestRecentAskAbsPrice = sc.Ask;
		LowestRecentAskAbsPrice = sc.Ask;
		HighestRecentBidAbsPrice = sc.Bid;
		LowestRecentBidAbsPrice = sc.Bid;
		LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence;
		HighestLineNumber = (int)(sc.Ask / sc.TickSize) + 10100000;
		LowestLineNumber = (int)(sc.Bid / sc.TickSize) + 10100000;
		LargestRecentAbsorption = 0;
		LargestCumulativeAbsorption = 0;
		LargestTotalAbsorption = 0;
		PreviousLargestRecentAbsorption = 0;
		PreviousLargestCumulativeAbsorption = 0;
		PreviousLargestTotalAbsorption = 0;
		FirstIndex = 0;
		PreviousIndex = 0;
		LargestAskCumAbsBar = 0;
		LargestBidCumAbsBar = 0;
		PreviousCumAskAbsOnBarSignalIndex = 0;
		PreviousCumBidAbsOnBarSignalIndex = 0;
		UnderBarsTextCounter = 0;
		Buyers_Meter = 0;
		Sellers_Meter = 0;
		PullingAlertCounter = 0;


		LastAskTradePrice = 0;
		LastBidTradePrice = 0;
		PreviousCumAskAbsOnBarSignalPrice = 0;
		PreviousCumBidAbsOnBarSignalPrice = 0;
		PreviousAskPrice = 0;;
		PreviousBidPrice = 0;

		//sc.SetACSToolEnable(Reset_Custom_Button_Number.GetInt(), FALSE); //Set Button back to OFF mode
	}

	if (sc.GetChartName(sc.ChartNumber).GetChars() != PreviousChartName.GetChars()) {
		for (int i = 10201000; i <= 10202000 + 2 + UnderBarsTextCounter; i += 2) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1);
		}
	}

	// ++++++++++++++++Iterate through the Time and Sales and process unprocessed entries++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ +
	if (Aggression_Meter_Reset_Mode.GetIndex() == 1 && sc.MenuEventID != 0 && sc.MenuEventID == Reset_Aggression_Meter_MenuID) {
		Buyers_Meter = 0;
		Sellers_Meter = 0;
		//sc.SetACSToolEnable(Aggression_Meter_Reset_Custom_Button_Number.GetInt(), FALSE); //Set Button back to OFF mode
	}
	if (LastProcessedSequence != 0) {
		int TnsLoopArrayIndex, CumulativeAskAbsorptionArrayIndexToReset, CumulativeBidAbsorptionArrayIndexToReset;
		for (int TSIndex = 0; TSIndex < TimeSales.Size(); ++TSIndex) {
			if (TimeSales[TSIndex].Sequence <= LastProcessedSequence) continue; //jump to next loop cycle if we have no new T&S entries to process
			if (TimeSales[TSIndex].Type == SC_TS_ASK) {
				TnsLoopArrayIndex = (int)(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier / sc.TickSize) - ArrayPriceDifference;
				CumulativeAskAbsorptionArrayIndexToReset = (int)((TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier - (float)Cumulative_Absorption_Tolerance.GetInt() * sc.TickSize) / sc.TickSize) - ArrayPriceDifference;


				if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier > HighestRecentAskAbsPrice) HighestRecentAskAbsPrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
				else if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier < LowestRecentAskAbsPrice) LowestRecentAskAbsPrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;

				if (p_RecentAskAbsToBeErased[TnsLoopArrayIndex] == 1) {// in order to erase the recent abs only when we get back to them we remember that we have to ersae them as "1" and then erase only when we get back to them
					p_AskRecentAbsorptions[TnsLoopArrayIndex] = 0;
					p_RecentAskAbsToBeErased[TnsLoopArrayIndex] = 0;
				}
				p_AskRecentAbsorptions[TnsLoopArrayIndex] += TimeSales[TSIndex].Volume; // acumulate just after reseting if had to get reset

				if (Aggression_Meter_Reset_Mode.GetIndex() == 0 && TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier != LastAskTradePrice)  Buyers_Meter = 0;
				Buyers_Meter += TimeSales[TSIndex].Volume;


				if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier != LastAskTradePrice) {
					p_RecentAskAbsToBeErased[(int)(LastAskTradePrice / sc.TickSize) - ArrayPriceDifference] = 1;  // mark it as has to be reset for ther next time it becomes the ask
				}

				p_AskCumulativeAbsorptions[TnsLoopArrayIndex] += TimeSales[TSIndex].Volume;
				p_AskTotalAbsorptions[TnsLoopArrayIndex] += TimeSales[TSIndex].Volume;

				if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier > LastAskTradePrice) {
					p_AskCumulativeAbsorptions[CumulativeAskAbsorptionArrayIndexToReset] = 0;
					if (PreviousAskPullStackValue < -Level_Taken_With_Pulling_Threashold.GetInt()) {
						if (Want_Sound_Alert_For_Level_Taken_With_Pulling.GetYesNo())sc.SetAlert(Ask_Level_Taken_With_Pulling_Sound_Alert_Number.GetInt());
						s_UseTool Pulling_Alert_Visual;
						Pulling_Alert_Visual.Clear();
						Pulling_Alert_Visual.AddAsUserDrawnDrawing = 1;
						Pulling_Alert_Visual.ChartNumber = sc.ChartNumber;
						Pulling_Alert_Visual.DrawingType = DRAWING_MARKER;
						Pulling_Alert_Visual.MarkerType = MARKER_STAR;
						Pulling_Alert_Visual.MarkerSize = Level_Taken_With_Pulling_Signal_Size.GetInt();
						Pulling_Alert_Visual.Color = Ask_Level_Taken_With_Pulling_Signal_Color.GetColor();
						Pulling_Alert_Visual.LineNumber = 12000000 + PullingAlertCounter;
						PullingAlertCounter++;
						Pulling_Alert_Visual.AddMethod = UTAM_ADD_OR_ADJUST;
						Pulling_Alert_Visual.UseRelativeVerticalValues = 0;
						Pulling_Alert_Visual.BeginIndex = sc.ArraySize - 1;
						Pulling_Alert_Visual.BeginValue = LastAskTradePrice;
						sc.UseTool(Pulling_Alert_Visual);

						str.Format("Ask_Pulling @%f  %i contracts pulled", LastAskTradePrice, PreviousAskPullStackValue);
						sc.AddMessageToLog(str, 0);
					}


					/*CumAbsorptionBeforeClearedText.Clear();
					CumAbsorptionBeforeClearedText.AddAsUserDrawnDrawing = 1;
					CumAbsorptionBeforeClearedText.ChartNumber = sc.ChartNumber;
					CumAbsorptionBeforeClearedText.DrawingType = DRAWING_TEXT;
					CumAbsorptionBeforeClearedText.LineNumber = (int)((sc.Ask - sc.TickSize) / sc.TickSize) + 10108000;
					CumAbsorptionBeforeClearedText.AddMethod = UTAM_ADD_OR_ADJUST;
					CumAbsorptionBeforeClearedText.FontSize = Font_Size.GetInt();
					CumAbsorptionBeforeClearedText.FontBold = 1;
					CumAbsorptionBeforeClearedText.Color = Buyers_Absorption_Text_Color.GetColor();
					CumAbsorptionBeforeClearedText.Text.Format("%i", p_AskCumulativeAbsorptions[TnsLoopArrayIndex - 1]);
					p_BeforeClearedCumAbsorption[TnsLoopArrayIndex - 1] = p_AskCumulativeAbsorptions[TnsLoopArrayIndex - 1];
					StringLength = CumAbsorptionBeforeClearedText.Text.GetLength();
					switch (StringLength) {
					case 1: ChangeLengthFactor = 2;
						break;
					case 2: ChangeLengthFactor = 1;
						break;
					case 3: ChangeLengthFactor = 0;
						break;
					case 4: ChangeLengthFactor = 0;
						break;
					case 5: ChangeLengthFactor = -1;
						break;
					case 6: ChangeLengthFactor = -1;
						break;
					}
					StringSCLength = (int)(ceilf(OneCharSCWidthUnits * ((float)StringLength + ChangeLengthFactor)));
					CumAbsorptionBeforeClearedText.BeginDateTime =
						Sellers_Meter_Text.BeginDateTime = (double)(Column2Position - StringSCLength); //Column1Position - (int)(ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1))));
					CumAbsorptionBeforeClearedText.TextAlignment = DT_VCENTER | DT_LEFT;
					CumAbsorptionBeforeClearedText.UseRelativeVerticalValues = 0;
					CumAbsorptionBeforeClearedText.BeginValue = sc.Ask - sc.TickSize;
					if (Want_Cumulative_Absorption_Column.GetInt()) sc.UseTool(CumAbsorptionBeforeClearedText);*/
				}

				LastAskTradePrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
			}


			else if (TimeSales[TSIndex].Type == SC_TS_BID) {
				TnsLoopArrayIndex = (int)(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier / sc.TickSize) - ArrayPriceDifference;
				CumulativeBidAbsorptionArrayIndexToReset = (int)((TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier + (float)Cumulative_Absorption_Tolerance.GetInt() * sc.TickSize) / sc.TickSize) - ArrayPriceDifference;


				if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier < LowestRecentBidAbsPrice) LowestRecentBidAbsPrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
				else if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier > HighestRecentBidAbsPrice) HighestRecentBidAbsPrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;

				if (p_RecentBidAbsToBeErased[TnsLoopArrayIndex] == 1) {
					p_BidRecentAbsorptions[TnsLoopArrayIndex] = 0;
					p_RecentBidAbsToBeErased[TnsLoopArrayIndex] = 0;
				}

				p_BidRecentAbsorptions[TnsLoopArrayIndex] += TimeSales[TSIndex].Volume;

				if (Aggression_Meter_Reset_Mode.GetIndex() == 0 && TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier != LastBidTradePrice) Sellers_Meter = 0;
				Sellers_Meter += TimeSales[TSIndex].Volume;

				if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier != LastBidTradePrice) {
					p_RecentBidAbsToBeErased[(int)(LastBidTradePrice / sc.TickSize) - ArrayPriceDifference] = 1;
				}

				p_BidCumulativeAbsorptions[TnsLoopArrayIndex] += TimeSales[TSIndex].Volume;
				p_BidTotalAbsorptions[TnsLoopArrayIndex] += TimeSales[TSIndex].Volume;

				if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier < LastBidTradePrice) {
					p_BidCumulativeAbsorptions[CumulativeBidAbsorptionArrayIndexToReset] = 0;
					if (PreviousBidPullStackValue < -Level_Taken_With_Pulling_Threashold.GetInt()) {
						if (Want_Sound_Alert_For_Level_Taken_With_Pulling.GetYesNo())sc.SetAlert(Bid_Level_Taken_With_Pulling_Sound_Alert_Number.GetInt());
						s_UseTool Pulling_Alert_Visual;
						Pulling_Alert_Visual.Clear();
						Pulling_Alert_Visual.AddAsUserDrawnDrawing = 1;
						Pulling_Alert_Visual.ChartNumber = sc.ChartNumber;
						Pulling_Alert_Visual.DrawingType = DRAWING_MARKER;
						Pulling_Alert_Visual.MarkerType = MARKER_STAR;
						Pulling_Alert_Visual.MarkerSize = Level_Taken_With_Pulling_Signal_Size.GetInt();
						Pulling_Alert_Visual.Color = Bid_Level_Taken_With_Pulling_Signal_Color.GetColor();
						Pulling_Alert_Visual.LineNumber = 12000000 + PullingAlertCounter;
						PullingAlertCounter++;
						Pulling_Alert_Visual.AddMethod = UTAM_ADD_OR_ADJUST;
						Pulling_Alert_Visual.UseRelativeVerticalValues = 0;
						Pulling_Alert_Visual.BeginIndex = sc.ArraySize - 1;
						Pulling_Alert_Visual.BeginValue = LastBidTradePrice;
						sc.UseTool(Pulling_Alert_Visual);

						str.Format("Bid_Pulling @%f  %i contracts pulled", LastBidTradePrice, PreviousBidPullStackValue);
						sc.AddMessageToLog(str, 0);
					}

					/*CumAbsorptionBeforeClearedText.Clear();
					CumAbsorptionBeforeClearedText.AddAsUserDrawnDrawing = 1;
					CumAbsorptionBeforeClearedText.ChartNumber = sc.ChartNumber;
					CumAbsorptionBeforeClearedText.DrawingType = DRAWING_TEXT;
					CumAbsorptionBeforeClearedText.LineNumber = (int)((sc.Bid + sc.TickSize) / sc.TickSize) + 10108000;
					CumAbsorptionBeforeClearedText.AddMethod = UTAM_ADD_OR_ADJUST;
					CumAbsorptionBeforeClearedText.FontSize = Font_Size.GetInt();
					CumAbsorptionBeforeClearedText.FontBold = 1;
					CumAbsorptionBeforeClearedText.Color = Sellers_Absorption_Text_Color.GetColor();
					CumAbsorptionBeforeClearedText.Text.Format("%i", p_BidCumulativeAbsorptions[TnsLoopArrayIndex + 1]);
					p_BeforeClearedCumAbsorption[TnsLoopArrayIndex + 1] = p_BidCumulativeAbsorptions[TnsLoopArrayIndex + 1];
					StringLength = CumAbsorptionBeforeClearedText.Text.GetLength();
					switch (StringLength) {
					case 1: ChangeLengthFactor = 2;
						break;
					case 2: ChangeLengthFactor = 1;
						break;
					case 3: ChangeLengthFactor = 0;
						break;
					case 4: ChangeLengthFactor = 0;
						break;
					case 5: ChangeLengthFactor = -1;
						break;
					case 6: ChangeLengthFactor = -1;
						break;
					}
					StringSCLength = (int)(ceilf(OneCharSCWidthUnits * ((float)StringLength + ChangeLengthFactor)));
					CumAbsorptionBeforeClearedText.BeginDateTime =
						Sellers_Meter_Text.BeginDateTime = (double)(Column2Position - StringSCLength);//Column1Position - (int)(ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1))));
					CumAbsorptionBeforeClearedText.TextAlignment = DT_VCENTER | DT_LEFT;
					CumAbsorptionBeforeClearedText.UseRelativeVerticalValues = 0;
					CumAbsorptionBeforeClearedText.BeginValue = sc.Bid + sc.TickSize;
					if (Want_Cumulative_Absorption_Column.GetInt()) sc.UseTool(CumAbsorptionBeforeClearedText);*/
				}

				LastBidTradePrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
			}
		}
	} // End of TnS Iteration
	LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence; //Update the LastProcessedSequence number at the end of the TnS iteration
	NumberOfLevels = (int)((HighestRecentAskAbsPrice - LowestRecentBidAbsPrice) / sc.TickSize) + 1;

	// ++++++++++++++++Every Tick Redraw the Meter Bars  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	if (Want_Aggression_Bar_Column.GetYesNo() == 1) {
		Buyers_Meter_Bar.Clear();
		Buyers_Meter_Bar.AddAsUserDrawnDrawing = 1;
		Buyers_Meter_Bar.ChartNumber = sc.ChartNumber;
		Buyers_Meter_Bar.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
		Buyers_Meter_Bar.LineNumber = 10203006;
		Buyers_Meter_Bar.AddMethod = UTAM_ADD_OR_ADJUST;
		Buyers_Meter_Bar.Color = RGB(255, 255, 255);
		Buyers_Meter_Bar.SecondaryColor = Buyers_Absorption_Text_Color.GetColor();
		//Buyers_Meter_Bar.TransparencyLevel = Bars_Transparency.GetInt();
		Buyers_Meter_Bar.LineWidth = 3;
		Buyers_Meter_Bar.UseRelativeVerticalValues = 1;
		Buyers_Meter_Bar.BeginDateTime =
		Sellers_Meter_Text.BeginDateTime = (double)(Column4Position + 1);
		Buyers_Meter_Bar.EndDateTime =
		Sellers_Meter_Text.BeginDateTime = (double)(Column4Position + OneColumnWidth - 1);
		Buyers_Meter_Bar.BeginValue = 30 + (ceilf(((float)Sellers_Meter / (float)(Sellers_Meter + Buyers_Meter)) * 40));
		Buyers_Meter_Bar.EndValue = 70;
		sc.UseTool(Buyers_Meter_Bar);

		Sellers_Meter_Bar.Clear();
		Sellers_Meter_Bar.AddAsUserDrawnDrawing = 1;
		Sellers_Meter_Bar.ChartNumber = sc.ChartNumber;
		Sellers_Meter_Bar.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
		Sellers_Meter_Bar.LineNumber = 10203007;
		Sellers_Meter_Bar.AddMethod = UTAM_ADD_OR_ADJUST;
		Sellers_Meter_Bar.Color = RGB(255, 255, 255);
		Sellers_Meter_Bar.SecondaryColor = Sellers_Absorption_Text_Color.GetColor();
		//Sellers_Meter_Bar.TransparencyLevel = Bars_Transparency.GetInt();
		Sellers_Meter_Bar.LineWidth = 3;
		Sellers_Meter_Bar.UseRelativeVerticalValues = 1;
		Sellers_Meter_Bar.BeginDateTime =
			Sellers_Meter_Text.BeginDateTime = (double)Column4Position + 1;
		Sellers_Meter_Bar.EndDateTime =
			Sellers_Meter_Text.BeginDateTime = (double)(Column4Position + OneColumnWidth - 1);
		Sellers_Meter_Bar.BeginValue = 30;
		Sellers_Meter_Bar.EndValue = (double)(30 + (ceilf(((float)Sellers_Meter / (float)(Sellers_Meter + Buyers_Meter)) * 40)));
		sc.UseTool(Sellers_Meter_Bar);


		Buyers_Meter_Text.Clear();
		Buyers_Meter_Text.AddAsUserDrawnDrawing = 1;
		Buyers_Meter_Text.ChartNumber = sc.ChartNumber;
		Buyers_Meter_Text.DrawingType = DRAWING_TEXT;
		Buyers_Meter_Text.AddMethod = UTAM_ADD_OR_ADJUST;
		Buyers_Meter_Text.FontSize = Font_Size.GetInt();
		Buyers_Meter_Text.FontBold = 1;
		Buyers_Meter_Text.Color = Top_Text_Color.GetColor();
		Buyers_Meter_Text.TextAlignment = DT_VCENTER | DT_LEFT;
		Buyers_Meter_Text.UseRelativeVerticalValues = 1;
		Buyers_Meter_Text.Text.Format("%i", Buyers_Meter);
		Buyers_Meter_Text.LineNumber = 10203008;
		Buyers_Meter_Text.BeginDateTime = (double)Column4Position + 1;
		Buyers_Meter_Text.BeginValue = 72;
		sc.UseTool(Buyers_Meter_Text);

		Sellers_Meter_Text.Clear();
		Sellers_Meter_Text.AddAsUserDrawnDrawing = 1;
		Sellers_Meter_Text.ChartNumber = sc.ChartNumber;
		Sellers_Meter_Text.DrawingType = DRAWING_TEXT;
		Sellers_Meter_Text.AddMethod = UTAM_ADD_OR_ADJUST;
		Sellers_Meter_Text.FontSize = Font_Size.GetInt();
		Sellers_Meter_Text.FontBold = 1;
		Sellers_Meter_Text.Color = Top_Text_Color.GetColor();
		Sellers_Meter_Text.TextAlignment = DT_VCENTER | DT_LEFT;
		Sellers_Meter_Text.UseRelativeVerticalValues = 1;
		Sellers_Meter_Text.Text.Format("%i", Sellers_Meter);
		Sellers_Meter_Text.LineNumber = 10203009;
		Sellers_Meter_Text.BeginDateTime = (double)Column4Position + 1;
		Sellers_Meter_Text.BeginValue = 28;
		sc.UseTool(Sellers_Meter_Text);
	}

	// ++++++++++++++++Every Tick Redraw the Horizontal Meter Bars (delta for Session anf Vol breakdown for session)  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	int SessionAskVol = 0; int SessionBidVol = 0; int SessionDelta = 0;
	for (int Index = sc.ArraySize - 1; Index < sc.ArraySize; Index--) {
		SCDateTime PriorStartOfPeriod = sc.GetStartOfPeriodForDateTime(sc.BaseDateTimeIn[Index - 1], TIME_PERIOD_LENGTH_UNIT_DAYS, 1, 0, 1);
		SCDateTime StartOfPeriod = sc.GetStartOfPeriodForDateTime(sc.BaseDateTimeIn[Index], TIME_PERIOD_LENGTH_UNIT_DAYS, 1, 0, 1);

		SessionAskVol += (int)sc.AskVolume[Index];
		SessionBidVol += (int)sc.BidVolume[Index];

		if (StartOfPeriod != PriorStartOfPeriod) {
			SessionDelta = SessionAskVol - SessionBidVol;
			break;
		}
	}


	Hor_Buyers_Meter_Bar.Clear();
	Hor_Buyers_Meter_Bar.AddAsUserDrawnDrawing = 1;
	Hor_Buyers_Meter_Bar.ChartNumber = sc.ChartNumber;
	Hor_Buyers_Meter_Bar.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
	Hor_Buyers_Meter_Bar.LineNumber = 10203010;
	Hor_Buyers_Meter_Bar.AddMethod = UTAM_ADD_OR_ADJUST;
	Hor_Buyers_Meter_Bar.Color = RGB(255, 255, 255);
	Hor_Buyers_Meter_Bar.SecondaryColor = Buyers_Absorption_Text_Color.GetColor();
	//Buyers_Meter_Bar.TransparencyLevel = Bars_Transparency.GetInt();
	Hor_Buyers_Meter_Bar.LineWidth = 3;
	Hor_Buyers_Meter_Bar.UseRelativeVerticalValues = 1;
	Hor_Buyers_Meter_Bar.BeginDateTime = (double)(23 + (ceilf(((float)SessionBidVol / (float)(SessionBidVol + SessionAskVol)) * 50)));
	Hor_Buyers_Meter_Bar.EndDateTime = 73;
	Hor_Buyers_Meter_Bar.BeginValue = 98;
	Hor_Buyers_Meter_Bar.EndValue = 100;
	sc.UseTool(Hor_Buyers_Meter_Bar);

	Hor_Sellers_Meter_Bar.Clear();
	Hor_Sellers_Meter_Bar.AddAsUserDrawnDrawing = 1;
	Hor_Sellers_Meter_Bar.ChartNumber = sc.ChartNumber;
	Hor_Sellers_Meter_Bar.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
	Hor_Sellers_Meter_Bar.LineNumber = 10203011;
	Hor_Sellers_Meter_Bar.AddMethod = UTAM_ADD_OR_ADJUST;
	Hor_Sellers_Meter_Bar.Color = RGB(255, 255, 255);
	Hor_Sellers_Meter_Bar.SecondaryColor = Sellers_Absorption_Text_Color.GetColor();
	//Sellers_Meter_Bar.TransparencyLevel = Bars_Transparency.GetInt();
	Hor_Sellers_Meter_Bar.LineWidth = 3;
	Hor_Sellers_Meter_Bar.UseRelativeVerticalValues = 1;
	Hor_Sellers_Meter_Bar.BeginDateTime = 23;
	Hor_Sellers_Meter_Bar.EndDateTime = (double)(23 + (ceilf(((float)SessionBidVol / (float)(SessionBidVol + SessionAskVol)) * 50)));
	Hor_Sellers_Meter_Bar.BeginValue = 98;
	Hor_Sellers_Meter_Bar.EndValue = 100;
	sc.UseTool(Hor_Sellers_Meter_Bar);


	Hor_Buyers_Meter_Text.Clear();
	Hor_Buyers_Meter_Text.AddAsUserDrawnDrawing = 1;
	Hor_Buyers_Meter_Text.ChartNumber = sc.ChartNumber;
	Hor_Buyers_Meter_Text.DrawingType = DRAWING_TEXT;
	Hor_Buyers_Meter_Text.AddMethod = UTAM_ADD_OR_ADJUST;
	Hor_Buyers_Meter_Text.FontSize = Font_Size.GetInt();
	Hor_Buyers_Meter_Text.FontBold = 1;
	Hor_Buyers_Meter_Text.Color = Top_Text_Color.GetColor();
	Hor_Buyers_Meter_Text.TextAlignment = DT_VCENTER | DT_LEFT;
	Hor_Buyers_Meter_Text.UseRelativeVerticalValues = 1;
	Hor_Buyers_Meter_Text.Text.Format("%i", SessionAskVol);
	Hor_Buyers_Meter_Text.LineNumber = 10203012;
	Hor_Buyers_Meter_Text.BeginDateTime = (double)(23 + 1 + (ceilf(((float)SessionBidVol / (float)(SessionBidVol + SessionAskVol)) * 50)));
	Hor_Buyers_Meter_Text.BeginValue = 99;
	sc.UseTool(Hor_Buyers_Meter_Text);

	Hor_Sellers_Meter_Text.Clear();
	Hor_Sellers_Meter_Text.AddAsUserDrawnDrawing = 1;
	Hor_Sellers_Meter_Text.ChartNumber = sc.ChartNumber;
	Hor_Sellers_Meter_Text.DrawingType = DRAWING_TEXT;
	Hor_Sellers_Meter_Text.AddMethod = UTAM_ADD_OR_ADJUST;
	Hor_Sellers_Meter_Text.FontSize = Font_Size.GetInt();
	Hor_Sellers_Meter_Text.FontBold = 1;
	Hor_Sellers_Meter_Text.Color = Top_Text_Color.GetColor();
	Hor_Sellers_Meter_Text.TextAlignment = DT_VCENTER | DT_LEFT;
	Hor_Sellers_Meter_Text.UseRelativeVerticalValues = 1;
	Hor_Sellers_Meter_Text.Text.Format("%i", SessionBidVol);
	Hor_Sellers_Meter_Text.LineNumber = 10203013;
	Hor_Sellers_Meter_Text.BeginDateTime = 24;
	Hor_Sellers_Meter_Text.BeginValue = 99;
	sc.UseTool(Hor_Sellers_Meter_Text);


	// ++++++++++++++++Every Tick Loop through all levels and calculate LargestAbsorption, Volunit, Sum, Average++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	RecentColumnSum = 0; CumulativeColumnSum = 0;
	//Loop Through Ask Levels
	LargestRecentAbsorption = 0; LargestCumulativeAbsorption = 0;  LargestTotalAbsorption = 0;
	for (float AskLoopPrice = sc.Ask; AskLoopPrice <= HighestRecentAskAbsPrice; AskLoopPrice += sc.TickSize) {
		int LoopCurrentAskArrayIndex = (int)(AskLoopPrice / sc.TickSize) - ArrayPriceDifference;
		if (p_AskRecentAbsorptions[LoopCurrentAskArrayIndex] > LargestRecentAbsorption) LargestRecentAbsorption = p_AskRecentAbsorptions[LoopCurrentAskArrayIndex];
		if (p_AskCumulativeAbsorptions[LoopCurrentAskArrayIndex] > LargestCumulativeAbsorption) LargestCumulativeAbsorption = p_AskCumulativeAbsorptions[LoopCurrentAskArrayIndex];
		if (p_AskTotalAbsorptions[LoopCurrentAskArrayIndex] > LargestTotalAbsorption) LargestTotalAbsorption = p_AskTotalAbsorptions[LoopCurrentAskArrayIndex];
		if (p_BidTotalAbsorptions[LoopCurrentAskArrayIndex] > LargestTotalAbsorption) LargestTotalAbsorption = p_BidTotalAbsorptions[LoopCurrentAskArrayIndex];
		RecentColumnSum += p_AskRecentAbsorptions[LoopCurrentAskArrayIndex];
		CumulativeColumnSum += p_AskCumulativeAbsorptions[LoopCurrentAskArrayIndex];
	}
	//Loop Through Bid Levels
	for (float BidLoopPrice = sc.Bid; BidLoopPrice >= LowestRecentBidAbsPrice; BidLoopPrice -= sc.TickSize) {
		int LoopCurrentBidArrayIndex = (int)(BidLoopPrice / sc.TickSize) - ArrayPriceDifference;
		if (p_BidRecentAbsorptions[LoopCurrentBidArrayIndex] > LargestRecentAbsorption) LargestRecentAbsorption = p_BidRecentAbsorptions[LoopCurrentBidArrayIndex];
		if (p_BidCumulativeAbsorptions[LoopCurrentBidArrayIndex] > LargestCumulativeAbsorption) LargestCumulativeAbsorption = p_BidCumulativeAbsorptions[LoopCurrentBidArrayIndex];
		if (p_BidTotalAbsorptions[LoopCurrentBidArrayIndex] > LargestTotalAbsorption) LargestTotalAbsorption = p_BidTotalAbsorptions[LoopCurrentBidArrayIndex];
		if (p_AskTotalAbsorptions[LoopCurrentBidArrayIndex] > LargestTotalAbsorption) LargestTotalAbsorption = p_AskTotalAbsorptions[LoopCurrentBidArrayIndex];

		RecentColumnSum += p_BidRecentAbsorptions[LoopCurrentBidArrayIndex];
		CumulativeColumnSum += p_BidCumulativeAbsorptions[LoopCurrentBidArrayIndex];
	}

	RecentColumnAvg = (float)RecentColumnSum / (float)NumberOfLevels;
	CumulativeColumnAvg = (float)CumulativeColumnSum / (float)NumberOfLevels;
	RecentAbsProfileVolUnit = (int)((float)LargestRecentAbsorption / (float)OneColumnWidth);
	CumulativeAbsProfileVolUnit = (int)((float)LargestCumulativeAbsorption / (float)OneColumnWidth);
	TotalAbsProfileVolUnit = (int)((float)LargestTotalAbsorption / (float)OneColumnWidth);

	//+++++++++++++++++++++++ Update just the CURRENT Recent Bid/Ask Bars and Text every function call ++++++++++++++++++++++++++++++++++++++++++++++++++

	RecentAskAbsorptionBars.Clear();
	RecentAskAbsorptionBars.AddAsUserDrawnDrawing = 1;
	RecentAskAbsorptionBars.ChartNumber = sc.ChartNumber;
	RecentAskAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
	RecentAskAbsorptionBars.LineNumber = (int)(sc.Ask / sc.TickSize) + 10102000;
	RecentAskAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
	RecentAskAbsorptionBars.Color = Buyers_Absorption_Bars_Outline_Color.GetColor();
	RecentAskAbsorptionBars.SecondaryColor = Buyers_Absorption_Bars_Fill_Color.GetColor();
	RecentAskAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
	RecentAskAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
	RecentAskAbsorptionBars.UseRelativeVerticalValues = 0;
	RecentAskAbsorptionBars.BeginDateTime = Column3Position;
	RecentAskAbsorptionBars.EndDateTime = (double)(Column3Position + (int)((float)p_AskRecentAbsorptions[CurrentAskArrayIndex] / (float)RecentAbsProfileVolUnit));
	RecentAskAbsorptionBars.BeginValue = sc.Ask - sc.TickSize / 2;
	RecentAskAbsorptionBars.EndValue = sc.Ask + sc.TickSize / 2;
	if (RecentAbsProfileVolUnit > 0 && Want_Recent_Absorption_Column.GetYesNo()) sc.UseTool(RecentAskAbsorptionBars);

	RecentBidAbsorptionBars.Clear();
	RecentBidAbsorptionBars.AddAsUserDrawnDrawing = 1;
	RecentBidAbsorptionBars.ChartNumber = sc.ChartNumber;
	RecentBidAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
	RecentBidAbsorptionBars.LineNumber = (int)(sc.Bid / sc.TickSize) + 10102000;
	RecentBidAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
	RecentBidAbsorptionBars.Color = Sellers_Absorption_Bars_Outline_Color.GetColor();
	RecentBidAbsorptionBars.SecondaryColor = Sellers_Absorption_Bars_Fill_Color.GetColor();
	RecentBidAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
	RecentBidAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
	RecentBidAbsorptionBars.UseRelativeVerticalValues = 0;
	RecentBidAbsorptionBars.BeginDateTime = Column3Position;
	RecentBidAbsorptionBars.EndDateTime = (double)(Column3Position + (int)((float)p_BidRecentAbsorptions[CurrentBidArrayIndex] / (float)RecentAbsProfileVolUnit));
	RecentBidAbsorptionBars.BeginValue = sc.Bid - sc.TickSize / 2;
	RecentBidAbsorptionBars.EndValue = sc.Bid + sc.TickSize / 2;
	if (RecentAbsProfileVolUnit > 0 && Want_Recent_Absorption_Column.GetYesNo()) sc.UseTool(RecentBidAbsorptionBars);



	RecentAskAbsorptionText.Clear();
	RecentAskAbsorptionText.AddAsUserDrawnDrawing = 1;
	RecentAskAbsorptionText.ChartNumber = sc.ChartNumber;
	RecentAskAbsorptionText.DrawingType = DRAWING_TEXT;
	RecentAskAbsorptionText.LineNumber = (int)(sc.Ask / sc.TickSize) + 10100000;
	if (RecentAskAbsorptionText.LineNumber > HighestLineNumber)HighestLineNumber = RecentAskAbsorptionText.LineNumber;
	RecentAskAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
	RecentAskAbsorptionText.FontSize = Updated_Font_Size;
	RecentAskAbsorptionText.FontBold = 1;
	if (p_AskRecentAbsorptions[CurrentAskArrayIndex] >= (int)((float)p_BidRecentAbsorptions[CurrentBidArrayIndex] * Imbalance_Ratio.GetFloat())) {
		RecentAskAbsorptionText.Color = More_Buying_Imbalance_Color.GetColor();
		RecentAskAbsorptionText.FontSize = Updated_Font_Size;
	}
	else RecentAskAbsorptionText.Color = Buyers_Absorption_Text_Color.GetColor();
	RecentAskAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
	RecentAskAbsorptionText.UseRelativeVerticalValues = 0;
	RecentAskAbsorptionText.BeginDateTime = Column3Position;
	RecentAskAbsorptionText.BeginValue = sc.Ask;
	RecentAskAbsorptionText.Text.Format("%i", p_AskRecentAbsorptions[CurrentAskArrayIndex]).GetChars();
	if (Want_Recent_Absorption_Column.GetYesNo()) sc.UseTool(RecentAskAbsorptionText);


	RecentBidAbsorptionText.Clear();
	RecentBidAbsorptionText.AddAsUserDrawnDrawing = 1;
	RecentBidAbsorptionText.ChartNumber = sc.ChartNumber;
	RecentBidAbsorptionText.DrawingType = DRAWING_TEXT;
	RecentBidAbsorptionText.LineNumber = (int)(sc.Bid / sc.TickSize) + 10100000;
	if (RecentBidAbsorptionText.LineNumber < LowestLineNumber) LowestLineNumber = RecentBidAbsorptionText.LineNumber;
	RecentBidAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
	RecentBidAbsorptionText.FontSize = Updated_Font_Size;
	RecentBidAbsorptionText.FontBold = 1;
	if (p_BidRecentAbsorptions[CurrentBidArrayIndex] >= (int)((float)p_AskRecentAbsorptions[CurrentAskArrayIndex] * Imbalance_Ratio.GetFloat())) {
		RecentBidAbsorptionText.Color = More_Selling_Imbalance_Color.GetColor();
		RecentBidAbsorptionText.FontSize = Updated_Font_Size;
	}
	else RecentBidAbsorptionText.Color = Sellers_Absorption_Text_Color.GetColor();
	RecentBidAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
	RecentBidAbsorptionText.UseRelativeVerticalValues = 0;
	RecentBidAbsorptionText.BeginDateTime = Column3Position;
	RecentBidAbsorptionText.BeginValue = sc.Bid;
	RecentBidAbsorptionText.Text.Format("%i", p_BidRecentAbsorptions[CurrentBidArrayIndex]).GetChars();
	if (Want_Recent_Absorption_Column.GetYesNo()) sc.UseTool(RecentBidAbsorptionText);



	// ++++++++++++++++++++++++ Update just the CURRENT Cumulative Bid / Ask Bars and Text every function call +++++++++++++++++++++++++++++++++++++++++++++++

	CumulativeAskAbsorptionBars.Clear();
	CumulativeAskAbsorptionBars.AddAsUserDrawnDrawing = 1;
	CumulativeAskAbsorptionBars.ChartNumber = sc.ChartNumber;
	CumulativeAskAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
	CumulativeAskAbsorptionBars.LineNumber = (int)(sc.Ask / sc.TickSize) + 10106000;
	CumulativeAskAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
	CumulativeAskAbsorptionBars.Color = Buyers_Absorption_Bars_Outline_Color.GetColor();
	CumulativeAskAbsorptionBars.SecondaryColor = Buyers_Absorption_Bars_Fill_Color.GetColor();
	CumulativeAskAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
	CumulativeAskAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
	CumulativeAskAbsorptionBars.UseRelativeVerticalValues = 0;
	CumulativeAskAbsorptionBars.BeginDateTime = Column2Position;
	CumulativeAskAbsorptionBars.EndDateTime = (double)(Column2Position + (int)((float)p_AskCumulativeAbsorptions[CurrentAskArrayIndex] / (float)CumulativeAbsProfileVolUnit)); //(int)150 / 100 * Absorption_Column_Max_Column_Width.GetInt();
	CumulativeAskAbsorptionBars.BeginValue = sc.Ask - sc.TickSize / 2;
	CumulativeAskAbsorptionBars.EndValue = sc.Ask + sc.TickSize / 2;
	if (CumulativeAbsProfileVolUnit > 0 && Want_Cumulative_Absorption_Column.GetYesNo()) sc.UseTool(CumulativeAskAbsorptionBars);


	CumulativeBidAbsorptionBars.Clear();
	CumulativeBidAbsorptionBars.AddAsUserDrawnDrawing = 1;
	CumulativeBidAbsorptionBars.ChartNumber = sc.ChartNumber;
	CumulativeBidAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
	CumulativeBidAbsorptionBars.LineNumber = (int)(sc.Bid / sc.TickSize) + 10106000;
	CumulativeBidAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
	CumulativeBidAbsorptionBars.Color = Sellers_Absorption_Bars_Outline_Color.GetColor();
	CumulativeBidAbsorptionBars.SecondaryColor = Sellers_Absorption_Bars_Fill_Color.GetColor();
	CumulativeBidAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
	CumulativeBidAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
	CumulativeBidAbsorptionBars.UseRelativeVerticalValues = 0;
	CumulativeBidAbsorptionBars.BeginDateTime = Column2Position;
	CumulativeBidAbsorptionBars.EndDateTime = (double)(Column2Position + (int)((float)p_BidCumulativeAbsorptions[CurrentBidArrayIndex] / CumulativeAbsProfileVolUnit)); //(int)150 / 100 * Absorption_Column_Max_Column_Width.GetInt();
	CumulativeBidAbsorptionBars.BeginValue = sc.Bid - sc.TickSize / 2;
	CumulativeBidAbsorptionBars.EndValue = sc.Bid + sc.TickSize / 2;
	if (CumulativeAbsProfileVolUnit > 0 && Want_Cumulative_Absorption_Column.GetYesNo())sc.UseTool(CumulativeBidAbsorptionBars);



	CumulativeAskAbsorptionText.Clear();
	CumulativeAskAbsorptionText.AddAsUserDrawnDrawing = 1;
	CumulativeAskAbsorptionText.ChartNumber = sc.ChartNumber;
	CumulativeAskAbsorptionText.DrawingType = DRAWING_TEXT;
	CumulativeAskAbsorptionText.LineNumber = (int)(sc.Ask / sc.TickSize) + 10104000;
	CumulativeAskAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
	CumulativeAskAbsorptionText.FontSize = Updated_Font_Size;
	CumulativeAskAbsorptionText.FontBold = 1;
	CumulativeAskAbsorptionText.Color = Buyers_Absorption_Text_Color.GetColor();
	CumulativeAskAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
	CumulativeAskAbsorptionText.UseRelativeVerticalValues = 0;
	CumulativeAskAbsorptionText.BeginDateTime = Column2Position;
	CumulativeAskAbsorptionText.BeginValue = sc.Ask;
	CumulativeAskAbsorptionText.Text.Format("%i", p_AskCumulativeAbsorptions[CurrentAskArrayIndex]).GetChars();
	if (Want_Cumulative_Absorption_Column.GetYesNo()) sc.UseTool(CumulativeAskAbsorptionText);

	CumulativeBidAbsorptionText.Clear();
	CumulativeBidAbsorptionText.AddAsUserDrawnDrawing = 1;
	CumulativeBidAbsorptionText.ChartNumber = sc.ChartNumber;
	CumulativeBidAbsorptionText.DrawingType = DRAWING_TEXT;
	CumulativeBidAbsorptionText.LineNumber = (int)(sc.Bid / sc.TickSize) + 10104000;
	CumulativeBidAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
	CumulativeBidAbsorptionText.FontSize = Updated_Font_Size;
	CumulativeBidAbsorptionText.FontBold = 1;
	CumulativeBidAbsorptionText.Color = Sellers_Absorption_Text_Color.GetColor();
	CumulativeBidAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
	CumulativeBidAbsorptionText.UseRelativeVerticalValues = 0;
	CumulativeBidAbsorptionText.BeginDateTime = Column2Position;
	CumulativeBidAbsorptionText.BeginValue = sc.Bid;
	CumulativeBidAbsorptionText.Text.Format("%i", p_BidCumulativeAbsorptions[CurrentBidArrayIndex]).GetChars();
	if (Want_Cumulative_Absorption_Column.GetYesNo()) sc.UseTool(CumulativeBidAbsorptionText);

	// ++++++++++++++++++++++++ Update just the CURRENT Total Bid / Ask Bars and Text every function call +++++++++++++++++++++++++++++++++++++++++++++++
	if (Want_TotalVol_Column.GetYesNo() == 1) {
		TotalAskAbsorptionBars.Clear();
		TotalAskAbsorptionBars.AddAsUserDrawnDrawing = 1;
		TotalAskAbsorptionBars.ChartNumber = sc.ChartNumber;
		TotalAskAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
		TotalAskAbsorptionBars.LineNumber = (int)(sc.Ask / sc.TickSize) + 10112000;
		TotalAskAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
		TotalAskAbsorptionBars.Color = Buyers_Absorption_Bars_Outline_Color.GetColor();
		TotalAskAbsorptionBars.SecondaryColor = Buyers_Absorption_Bars_Fill_Color.GetColor();
		TotalAskAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
		TotalAskAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
		TotalAskAbsorptionBars.UseRelativeVerticalValues = 0;
		TotalAskAbsorptionBars.BeginDateTime = Column1Position;
		TotalAskAbsorptionBars.EndDateTime = (double)(Column1Position + (int)((float)p_AskTotalAbsorptions[CurrentAskArrayIndex] / (float)TotalAbsProfileVolUnit)); //(int)150 / 100 * Absorption_Column_Max_Column_Width.GetInt();
		TotalAskAbsorptionBars.BeginValue = sc.Ask - sc.TickSize / 2;
		TotalAskAbsorptionBars.EndValue = sc.Ask + sc.TickSize / 2;
		if (CumulativeAbsProfileVolUnit > 0)sc.UseTool(TotalAskAbsorptionBars);


		TotalBidAbsorptionBars.Clear();
		TotalBidAbsorptionBars.AddAsUserDrawnDrawing = 1;
		TotalBidAbsorptionBars.ChartNumber = sc.ChartNumber;
		TotalBidAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
		TotalBidAbsorptionBars.LineNumber = (int)(sc.Bid / sc.TickSize) + 10110000;
		TotalBidAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
		TotalBidAbsorptionBars.Color = Sellers_Absorption_Bars_Outline_Color.GetColor();
		TotalBidAbsorptionBars.SecondaryColor = Sellers_Absorption_Bars_Fill_Color.GetColor();
		TotalBidAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
		TotalBidAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
		TotalBidAbsorptionBars.UseRelativeVerticalValues = 0;
		TotalBidAbsorptionBars.BeginDateTime = Column1Position;
		TotalBidAbsorptionBars.EndDateTime = (double)(Column1Position - (int)((float)p_BidTotalAbsorptions[CurrentBidArrayIndex] / (float)TotalAbsProfileVolUnit)); //(int)150 / 100 * Absorption_Column_Max_Column_Width.GetInt();
		TotalBidAbsorptionBars.BeginValue = sc.Bid - sc.TickSize / 2;
		TotalBidAbsorptionBars.EndValue = sc.Bid + sc.TickSize / 2;
		if (TotalAbsProfileVolUnit > 0)sc.UseTool(TotalBidAbsorptionBars);



		TotalAskAbsorptionText.Clear();
		TotalAskAbsorptionText.AddAsUserDrawnDrawing = 1;
		TotalAskAbsorptionText.ChartNumber = sc.ChartNumber;
		TotalAskAbsorptionText.DrawingType = DRAWING_TEXT;
		TotalAskAbsorptionText.LineNumber = (int)(sc.Ask / sc.TickSize) + 10116000;
		TotalAskAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
		TotalAskAbsorptionText.FontSize = Updated_Font_Size;
		TotalAskAbsorptionText.FontBold = 1;
		if (p_AskTotalAbsorptions[CurrentAskArrayIndex] >= (int)((float)p_BidTotalAbsorptions[CurrentBidArrayIndex] * Imbalance_Ratio.GetFloat())) {
			TotalAskAbsorptionText.Color = More_Buying_Imbalance_Color.GetColor();
			TotalAskAbsorptionText.FontSize = Updated_Font_Size;
		}
		else TotalAskAbsorptionText.Color = Buyers_Absorption_Text_Color.GetColor();
		TotalAskAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
		TotalAskAbsorptionText.UseRelativeVerticalValues = 0;
		TotalAskAbsorptionText.BeginDateTime = Column1Position;
		TotalAskAbsorptionText.BeginValue = sc.Ask;
		TotalAskAbsorptionText.Text.Format("%i", p_AskTotalAbsorptions[CurrentAskArrayIndex]).GetChars();
		sc.UseTool(TotalAskAbsorptionText);

		TotalBidAbsorptionText.Clear();
		TotalBidAbsorptionText.AddAsUserDrawnDrawing = 1;
		TotalBidAbsorptionText.ChartNumber = sc.ChartNumber;
		TotalBidAbsorptionText.DrawingType = DRAWING_TEXT;
		TotalBidAbsorptionText.LineNumber = (int)(sc.Bid / sc.TickSize) + 10114000;
		TotalBidAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
		TotalBidAbsorptionText.FontSize = Updated_Font_Size;
		TotalBidAbsorptionText.FontBold = 1;
		if (p_BidTotalAbsorptions[CurrentBidArrayIndex] >= (int)((float)p_AskTotalAbsorptions[CurrentAskArrayIndex] * Imbalance_Ratio.GetFloat())) {
			TotalBidAbsorptionText.Color = More_Selling_Imbalance_Color.GetColor();
			TotalBidAbsorptionText.FontSize = Updated_Font_Size;
		}
		else TotalBidAbsorptionText.Color = Sellers_Absorption_Text_Color.GetColor();
		TotalBidAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
		TotalBidAbsorptionText.UseRelativeVerticalValues = 0;
		ThisString.Format("%i", p_BidTotalAbsorptions[CurrentBidArrayIndex]);
		StringLength = ThisString.GetLength();
		switch (StringLength) {
		case 1: ChangeLengthFactor = 2;
			break;
		case 2: ChangeLengthFactor = 1;
			break;
		case 3: ChangeLengthFactor = 0;
			break;
		case 4: ChangeLengthFactor = 0;
			break;
		case 5: ChangeLengthFactor = -1;
			break;
		case 6: ChangeLengthFactor = -1;
			break;
		}
		StringSCLength = (int)(ceilf(OneCharSCWidthUnits * ((float)StringLength + ChangeLengthFactor)));
		TotalBidAbsorptionText.BeginDateTime = (double)(Column1Position - StringSCLength);
		TotalBidAbsorptionText.BeginValue = sc.Bid;
		TotalBidAbsorptionText.Text.Format("%i", p_BidTotalAbsorptions[CurrentBidArrayIndex]).GetChars();
		sc.UseTool(TotalBidAbsorptionText);
	}


	//  +++++++++++++++++++++++  If we have a new LargestRecentAbsorption Or sc.UpdateStartIndex == 0 Draw all Bars of RecentAbsorption column again  ++++++++++++++++++++++++++++++++++

	if (LargestRecentAbsorption > PreviousLargestRecentAbsorption || sc.UpdateStartIndex == 0 || Previous_RightClick_TextToggle_State != RightClick_TextToggle_State) {
		for (float AskLoopPrice = sc.Ask; AskLoopPrice <= HighestRecentAskAbsPrice; AskLoopPrice += sc.TickSize) {
			int LoopCurrentAskArrayIndex = (int)(AskLoopPrice / sc.TickSize) - ArrayPriceDifference;
			RecentAskAbsorptionBars.Clear();
			RecentAskAbsorptionBars.AddAsUserDrawnDrawing = 1;
			RecentAskAbsorptionBars.ChartNumber = sc.ChartNumber;
			RecentAskAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
			RecentAskAbsorptionBars.LineNumber = (int)(AskLoopPrice / sc.TickSize) + 10102000;
			RecentAskAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
			RecentAskAbsorptionBars.Color = Buyers_Absorption_Bars_Outline_Color.GetColor();
			RecentAskAbsorptionBars.SecondaryColor = Buyers_Absorption_Bars_Fill_Color.GetColor();
			RecentAskAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
			RecentAskAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
			RecentAskAbsorptionBars.UseRelativeVerticalValues = 0;
			RecentAskAbsorptionBars.BeginDateTime = Column3Position;
			RecentAskAbsorptionBars.EndDateTime = (double)(Column3Position + (int)((float)p_AskRecentAbsorptions[LoopCurrentAskArrayIndex] / (float)RecentAbsProfileVolUnit));
			RecentAskAbsorptionBars.BeginValue = AskLoopPrice - sc.TickSize / 2;
			RecentAskAbsorptionBars.EndValue = AskLoopPrice + sc.TickSize / 2;
			if (RecentAbsProfileVolUnit > 0 && Want_Recent_Absorption_Column.GetYesNo())
				sc.UseTool(RecentAskAbsorptionBars);

			RecentAskAbsorptionText.Clear();
			RecentAskAbsorptionText.AddAsUserDrawnDrawing = 1;
			RecentAskAbsorptionText.ChartNumber = sc.ChartNumber;
			RecentAskAbsorptionText.DrawingType = DRAWING_TEXT;
			RecentAskAbsorptionText.LineNumber = (int)(AskLoopPrice / sc.TickSize) + 10100000;
			RecentAskAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
			RecentAskAbsorptionText.FontSize = Updated_Font_Size;
			RecentAskAbsorptionText.FontBold = 1;
			if (AskLoopPrice != HighestRecentAskAbsPrice && p_AskRecentAbsorptions[LoopCurrentAskArrayIndex] >= (int)((float)p_BidRecentAbsorptions[LoopCurrentAskArrayIndex - 1] * Imbalance_Ratio.GetFloat())) {
				RecentAskAbsorptionText.Color = More_Buying_Imbalance_Color.GetColor();
				RecentAskAbsorptionText.FontSize = Updated_Font_Size;
			}
			else RecentAskAbsorptionText.Color = Buyers_Absorption_Text_Color.GetColor();
			RecentAskAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
			RecentAskAbsorptionText.UseRelativeVerticalValues = 0;
			RecentAskAbsorptionText.BeginDateTime = Column3Position;
			RecentAskAbsorptionText.BeginValue = AskLoopPrice;
			RecentAskAbsorptionText.Text.Format("%i", p_AskRecentAbsorptions[LoopCurrentAskArrayIndex]).GetChars();
			//if (RecentAbsProfileVolUnit > 0)
			if (Want_Recent_Absorption_Column.GetYesNo()) sc.UseTool(RecentAskAbsorptionText);
		}

		for (float BidLoopPrice = sc.Bid; BidLoopPrice >= LowestRecentBidAbsPrice; BidLoopPrice -= sc.TickSize) {
			int LoopCurrentBidArrayIndex = (int)(BidLoopPrice / sc.TickSize) - ArrayPriceDifference;
			RecentBidAbsorptionBars.Clear();
			RecentBidAbsorptionBars.AddAsUserDrawnDrawing = 1;
			RecentBidAbsorptionBars.ChartNumber = sc.ChartNumber;
			RecentBidAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
			RecentBidAbsorptionBars.LineNumber = (int)(BidLoopPrice / sc.TickSize) + 10102000;
			RecentBidAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
			RecentBidAbsorptionBars.Color = Sellers_Absorption_Bars_Outline_Color.GetColor();
			RecentBidAbsorptionBars.SecondaryColor = Sellers_Absorption_Bars_Fill_Color.GetColor();
			RecentBidAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
			RecentBidAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
			RecentBidAbsorptionBars.UseRelativeVerticalValues = 0;
			RecentBidAbsorptionBars.BeginDateTime = Column3Position;
			RecentBidAbsorptionBars.EndDateTime = (double)(Column3Position + (int)((float)p_BidRecentAbsorptions[LoopCurrentBidArrayIndex] / (float)RecentAbsProfileVolUnit));
			RecentBidAbsorptionBars.BeginValue = BidLoopPrice - sc.TickSize / 2;
			RecentBidAbsorptionBars.EndValue = BidLoopPrice + sc.TickSize / 2;
			if (RecentAbsProfileVolUnit > 0 && Want_Recent_Absorption_Column.GetYesNo())
				sc.UseTool(RecentBidAbsorptionBars);

			RecentBidAbsorptionText.Clear();
			RecentBidAbsorptionText.AddAsUserDrawnDrawing = 1;
			RecentBidAbsorptionText.ChartNumber = sc.ChartNumber;
			RecentBidAbsorptionText.DrawingType = DRAWING_TEXT;
			RecentBidAbsorptionText.LineNumber = (int)(BidLoopPrice / sc.TickSize) + 10100000;
			RecentBidAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
			RecentBidAbsorptionText.FontSize = Updated_Font_Size;
			RecentBidAbsorptionText.FontBold = 1;
			if (BidLoopPrice != LowestRecentBidAbsPrice && p_BidRecentAbsorptions[LoopCurrentBidArrayIndex] >= (int)((float)p_AskRecentAbsorptions[LoopCurrentBidArrayIndex + 1] * Imbalance_Ratio.GetFloat())) {
				RecentBidAbsorptionText.Color = More_Selling_Imbalance_Color.GetColor();
				RecentBidAbsorptionText.FontSize = Updated_Font_Size;
			}
			else RecentBidAbsorptionText.Color = Sellers_Absorption_Text_Color.GetColor();
			RecentBidAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
			RecentBidAbsorptionText.UseRelativeVerticalValues = 0;
			RecentBidAbsorptionText.BeginDateTime = Column3Position;
			RecentBidAbsorptionText.BeginValue = BidLoopPrice;
			RecentBidAbsorptionText.Text.Format("%i", p_BidRecentAbsorptions[LoopCurrentBidArrayIndex]).GetChars();
			//if (RecentAbsProfileVolUnit > 0)
			if (Want_Recent_Absorption_Column.GetYesNo()) sc.UseTool(RecentBidAbsorptionText);
		}
	}

	//  +++++++++++++++++++++++ If we have a new LargestCumulativeAbsorption or sc.UpdateStartIndex == 0 Draw all Bars of RecentAbsorption column again  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	if (LargestCumulativeAbsorption > PreviousLargestCumulativeAbsorption || sc.UpdateStartIndex == 0 || WindowPixelWidth != PreviousWindowPixelWidth || Previous_RightClick_TextToggle_State != RightClick_TextToggle_State) {
		for (float AskLoopPrice = sc.Ask; AskLoopPrice <= HighestRecentAskAbsPrice; AskLoopPrice += sc.TickSize) {
			int LoopCurrentAskArrayIndex = (int)(AskLoopPrice / sc.TickSize) - ArrayPriceDifference;
			CumulativeAskAbsorptionBars.Clear();
			CumulativeAskAbsorptionBars.AddAsUserDrawnDrawing = 1;
			CumulativeAskAbsorptionBars.ChartNumber = sc.ChartNumber;
			CumulativeAskAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
			CumulativeAskAbsorptionBars.LineNumber = (int)(AskLoopPrice / sc.TickSize) + 10106000;
			CumulativeAskAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
			CumulativeAskAbsorptionBars.Color = Buyers_Absorption_Bars_Outline_Color.GetColor();
			CumulativeAskAbsorptionBars.SecondaryColor = Buyers_Absorption_Bars_Fill_Color.GetColor();
			CumulativeAskAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
			CumulativeAskAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
			CumulativeAskAbsorptionBars.UseRelativeVerticalValues = 0;
			CumulativeAskAbsorptionBars.BeginDateTime = Column2Position;
			CumulativeAskAbsorptionBars.EndDateTime = (double)(Column2Position + (int)((float)p_AskCumulativeAbsorptions[LoopCurrentAskArrayIndex] / (float)CumulativeAbsProfileVolUnit)); //(int)150 / 100 * Absorption_Column_Max_Column_Width.GetInt();
			CumulativeAskAbsorptionBars.BeginValue = AskLoopPrice - sc.TickSize / 2;
			CumulativeAskAbsorptionBars.EndValue = AskLoopPrice + sc.TickSize / 2;
			if (CumulativeAbsProfileVolUnit > 0 && Want_Cumulative_Absorption_Column.GetYesNo())
				sc.UseTool(CumulativeAskAbsorptionBars);

			CumulativeAskAbsorptionText.Clear();
			CumulativeAskAbsorptionText.AddAsUserDrawnDrawing = 1;
			CumulativeAskAbsorptionText.ChartNumber = sc.ChartNumber;
			CumulativeAskAbsorptionText.DrawingType = DRAWING_TEXT;
			CumulativeAskAbsorptionText.LineNumber = (int)(AskLoopPrice / sc.TickSize) + 10104000;
			CumulativeAskAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
			CumulativeAskAbsorptionText.FontSize = Updated_Font_Size;
			CumulativeAskAbsorptionText.FontBold = 1;
			CumulativeAskAbsorptionText.Color = Buyers_Absorption_Text_Color.GetColor();
			CumulativeAskAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
			CumulativeAskAbsorptionText.UseRelativeVerticalValues = 0;
			CumulativeAskAbsorptionText.BeginDateTime = Column2Position;
			CumulativeAskAbsorptionText.BeginValue = AskLoopPrice;
			CumulativeAskAbsorptionText.Text.Format("%i", p_AskCumulativeAbsorptions[LoopCurrentAskArrayIndex]).GetChars();
			if (Want_Cumulative_Absorption_Column.GetYesNo()) sc.UseTool(CumulativeAskAbsorptionText);



			/*CumAbsorptionBeforeClearedText.Clear();
			CumAbsorptionBeforeClearedText.AddAsUserDrawnDrawing = 1;
			CumAbsorptionBeforeClearedText.LineNumber = (int)(AskLoopPrice / sc.TickSize) + 10108000;
			CumAbsorptionBeforeClearedText.AddMethod = UTAM_ADD_OR_ADJUST;
			CumAbsorptionBeforeClearedText.FontSize = Font_Size.GetInt();
			CumAbsorptionBeforeClearedText.Color = Sellers_Absorption_Text_Color.GetColor();
			CumAbsorptionBeforeClearedText.Text.Format("%i", p_BeforeClearedCumAbsorption[LoopCurrentAskArrayIndex]);
			ThisString.Format("%i", p_BeforeClearedCumAbsorption[LoopCurrentAskArrayIndex]);
			StringLength = ThisString.GetLength();
			switch (StringLength) {
			case 1: ChangeLengthFactor = 2;
				break;
			case 2: ChangeLengthFactor = 1;
				break;
			case 3: ChangeLengthFactor = 0;
				break;
			case 4: ChangeLengthFactor = 0;
				break;
			case 5: ChangeLengthFactor = -1;
				break;
			case 6: ChangeLengthFactor = -1;
				break;
			}
			StringSCLength = (int)(ceilf(OneCharSCWidthUnits * ((float)StringLength + ChangeLengthFactor)));
			CumAbsorptionBeforeClearedText.BeginDateTime = (double)(Column2Position - StringSCLength); // Column1Position - (int)(ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1))));
																							 //if (RecentAbsProfileVolUnit > 0)
			if (Want_Cumulative_Absorption_Column.GetInt()) sc.UseTool(CumAbsorptionBeforeClearedText);*/
		}

		for (float BidLoopPrice = sc.Bid; BidLoopPrice >= LowestRecentBidAbsPrice; BidLoopPrice -= sc.TickSize) {
			int LoopCurrentBidArrayIndex = (int)(BidLoopPrice / sc.TickSize) - ArrayPriceDifference;
			CumulativeBidAbsorptionBars.Clear();
			CumulativeBidAbsorptionBars.AddAsUserDrawnDrawing = 1;
			CumulativeBidAbsorptionBars.ChartNumber = sc.ChartNumber;
			CumulativeBidAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
			CumulativeBidAbsorptionBars.LineNumber = (int)(BidLoopPrice / sc.TickSize) + 10106000;
			CumulativeBidAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
			CumulativeBidAbsorptionBars.Color = Sellers_Absorption_Bars_Outline_Color.GetColor();
			CumulativeBidAbsorptionBars.SecondaryColor = Sellers_Absorption_Bars_Fill_Color.GetColor();
			CumulativeBidAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
			CumulativeBidAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
			CumulativeBidAbsorptionBars.UseRelativeVerticalValues = 0;
			CumulativeBidAbsorptionBars.BeginDateTime = Column2Position;
			CumulativeBidAbsorptionBars.EndDateTime = (double)(Column2Position + (int)((float)p_BidCumulativeAbsorptions[LoopCurrentBidArrayIndex] / (float)CumulativeAbsProfileVolUnit)); //(int)150 / 100 * Absorption_Column_Max_Column_Width.GetInt();
			CumulativeBidAbsorptionBars.BeginValue = BidLoopPrice - sc.TickSize / 2;
			CumulativeBidAbsorptionBars.EndValue = BidLoopPrice + sc.TickSize / 2;
			if (CumulativeAbsProfileVolUnit > 0 && Want_Cumulative_Absorption_Column.GetYesNo())
				sc.UseTool(CumulativeBidAbsorptionBars);

			CumulativeBidAbsorptionText.Clear();
			CumulativeBidAbsorptionText.AddAsUserDrawnDrawing = 1;
			CumulativeBidAbsorptionText.ChartNumber = sc.ChartNumber;
			CumulativeBidAbsorptionText.DrawingType = DRAWING_TEXT;
			CumulativeBidAbsorptionText.LineNumber = (int)(BidLoopPrice / sc.TickSize) + 10104000;
			CumulativeBidAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
			CumulativeBidAbsorptionText.FontSize = Updated_Font_Size;
			CumulativeBidAbsorptionText.FontBold = 1;
			CumulativeBidAbsorptionText.Color = Sellers_Absorption_Text_Color.GetColor();
			CumulativeBidAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
			CumulativeBidAbsorptionText.UseRelativeVerticalValues = 0;
			CumulativeBidAbsorptionText.BeginDateTime = Column2Position;
			CumulativeBidAbsorptionText.BeginValue = BidLoopPrice;
			CumulativeBidAbsorptionText.Text.Format("%i", p_BidCumulativeAbsorptions[LoopCurrentBidArrayIndex]).GetChars();
			if (Want_Cumulative_Absorption_Column.GetYesNo()) sc.UseTool(CumulativeBidAbsorptionText);

			/*CumAbsorptionBeforeClearedText.Clear();
			CumAbsorptionBeforeClearedText.AddAsUserDrawnDrawing = 1;
			CumAbsorptionBeforeClearedText.LineNumber = (int)(BidLoopPrice / sc.TickSize) + 10108000;
			CumAbsorptionBeforeClearedText.AddMethod = UTAM_ADD_OR_ADJUST;
			CumAbsorptionBeforeClearedText.FontSize = Font_Size.GetInt();
			CumAbsorptionBeforeClearedText.Color = Buyers_Absorption_Text_Color.GetColor();
			CumAbsorptionBeforeClearedText.Text.Format("%i", p_BeforeClearedCumAbsorption[LoopCurrentBidArrayIndex]);
			ThisString.Format("%i", p_BeforeClearedCumAbsorption[LoopCurrentBidArrayIndex]);
			StringLength = ThisString.GetLength();
			switch (StringLength) {
			case 1: ChangeLengthFactor = 2;
				break;
			case 2: ChangeLengthFactor = 1;
				break;
			case 3: ChangeLengthFactor = 0;
				break;
			case 4: ChangeLengthFactor = 0;
				break;
			case 5: ChangeLengthFactor = -1;
				break;
			case 6: ChangeLengthFactor = -1;
				break;
			}
			StringSCLength = (int)(ceilf(OneCharSCWidthUnits * ((float)StringLength + ChangeLengthFactor)));
			CumAbsorptionBeforeClearedText.BeginDateTime = (double)(Column2Position - StringSCLength); //Column1Position - (int)(ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1))));
																							 //if (RecentAbsProfileVolUnit > 0)
			if (Want_Cumulative_Absorption_Column.GetInt()) sc.UseTool(CumAbsorptionBeforeClearedText);*/
		}
	}

	//  +++++++++++++++++++++++  If we have a new LargestTotalAbsorption Or sc.UpdateStartIndex == 0 Draw all Bars of RecentAbsorption column again  ++++++++++++++++++++++++++++++++++
	if (Want_TotalVol_Column.GetYesNo() == 1) {
		if (LargestTotalAbsorption > PreviousLargestTotalAbsorption || sc.UpdateStartIndex == 0 || WindowPixelWidth != PreviousWindowPixelWidth || Previous_RightClick_TextToggle_State != RightClick_TextToggle_State) {
			for (float LoopPrice = LowestRecentBidAbsPrice; LoopPrice <= HighestRecentAskAbsPrice; LoopPrice += sc.TickSize) {
				int LoopCurrentArrayIndex = (int)(LoopPrice / sc.TickSize) - ArrayPriceDifference;
				TotalAskAbsorptionBars.Clear();
				TotalAskAbsorptionBars.AddAsUserDrawnDrawing = 1;
				TotalAskAbsorptionBars.ChartNumber = sc.ChartNumber;
				TotalAskAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
				TotalAskAbsorptionBars.LineNumber = (int)(LoopPrice / sc.TickSize) + 10112000;
				TotalAskAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
				TotalAskAbsorptionBars.Color = Buyers_Absorption_Bars_Outline_Color.GetColor();
				TotalAskAbsorptionBars.SecondaryColor = Buyers_Absorption_Bars_Fill_Color.GetColor();
				TotalAskAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
				TotalAskAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
				TotalAskAbsorptionBars.UseRelativeVerticalValues = 0;
				TotalAskAbsorptionBars.BeginDateTime = Column1Position;
				TotalAskAbsorptionBars.EndDateTime = (double)(Column1Position + (int)((float)p_AskTotalAbsorptions[LoopCurrentArrayIndex] / (float)TotalAbsProfileVolUnit)); //(int)150 / 100 * Absorption_Column_Max_Column_Width.GetInt();
				TotalAskAbsorptionBars.BeginValue = LoopPrice - sc.TickSize / 2;
				TotalAskAbsorptionBars.EndValue = LoopPrice + sc.TickSize / 2;
				if (TotalAbsProfileVolUnit > 0)
					sc.UseTool(TotalAskAbsorptionBars);

				TotalAskAbsorptionText.Clear();
				TotalAskAbsorptionText.AddAsUserDrawnDrawing = 1;
				TotalAskAbsorptionText.ChartNumber = sc.ChartNumber;
				TotalAskAbsorptionText.DrawingType = DRAWING_TEXT;
				TotalAskAbsorptionText.LineNumber = (int)(LoopPrice / sc.TickSize) + 10116000;
				TotalAskAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
				TotalAskAbsorptionText.FontSize = Updated_Font_Size;
				TotalAskAbsorptionText.FontBold = 1;
				if (LoopPrice != LowestRecentBidAbsPrice && p_AskTotalAbsorptions[LoopCurrentArrayIndex] >= (int)((float)p_BidTotalAbsorptions[LoopCurrentArrayIndex - 1] * Imbalance_Ratio.GetFloat())) {
					TotalAskAbsorptionText.Color = More_Buying_Imbalance_Color.GetColor();
					TotalAskAbsorptionText.FontSize = Updated_Font_Size;
				}
				else TotalAskAbsorptionText.Color = Buyers_Absorption_Text_Color.GetColor();
				TotalAskAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
				TotalAskAbsorptionText.UseRelativeVerticalValues = 0;
				TotalAskAbsorptionText.BeginDateTime = Column1Position;
				TotalAskAbsorptionText.BeginValue = LoopPrice;
				TotalAskAbsorptionText.Text.Format("%i", p_AskTotalAbsorptions[LoopCurrentArrayIndex]).GetChars();
				//if (RecentAbsProfileVolUnit > 0)
				sc.UseTool(TotalAskAbsorptionText);

				TotalBidAbsorptionBars.Clear();
				TotalBidAbsorptionBars.AddAsUserDrawnDrawing = 1;
				TotalBidAbsorptionBars.ChartNumber = sc.ChartNumber;
				TotalBidAbsorptionBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
				TotalBidAbsorptionBars.LineNumber = (int)(LoopPrice / sc.TickSize) + 10110000;
				TotalBidAbsorptionBars.AddMethod = UTAM_ADD_OR_ADJUST;
				TotalBidAbsorptionBars.Color = Sellers_Absorption_Bars_Outline_Color.GetColor();
				TotalBidAbsorptionBars.SecondaryColor = Sellers_Absorption_Bars_Fill_Color.GetColor();
				TotalBidAbsorptionBars.TransparencyLevel = Bars_Transparency.GetInt();
				TotalBidAbsorptionBars.LineWidth = Bars_Outline_Width.GetInt();
				TotalBidAbsorptionBars.UseRelativeVerticalValues = 0;
				TotalBidAbsorptionBars.BeginDateTime = Column1Position;
				TotalBidAbsorptionBars.EndDateTime = (double)(Column1Position - (int)((float)p_BidTotalAbsorptions[LoopCurrentArrayIndex] / (float)TotalAbsProfileVolUnit)); //(int)150 / 100 * Absorption_Column_Max_Column_Width.GetInt();
				TotalBidAbsorptionBars.BeginValue = LoopPrice - sc.TickSize / 2;
				TotalBidAbsorptionBars.EndValue = LoopPrice + sc.TickSize / 2;
				if (TotalAbsProfileVolUnit > 0)
					sc.UseTool(TotalBidAbsorptionBars);

				TotalBidAbsorptionText.Clear();
				TotalBidAbsorptionText.AddAsUserDrawnDrawing = 1;
				TotalBidAbsorptionText.ChartNumber = sc.ChartNumber;
				TotalBidAbsorptionText.DrawingType = DRAWING_TEXT;
				TotalBidAbsorptionText.LineNumber = (int)(LoopPrice / sc.TickSize) + 10114000;
				TotalBidAbsorptionText.AddMethod = UTAM_ADD_OR_ADJUST;
				TotalBidAbsorptionText.FontSize = Updated_Font_Size;
				TotalBidAbsorptionText.FontBold = 1;
				if (LoopPrice != HighestRecentAskAbsPrice && p_BidTotalAbsorptions[LoopCurrentArrayIndex] >= (int)((float)p_AskTotalAbsorptions[LoopCurrentArrayIndex + 1] * Imbalance_Ratio.GetFloat())) {
					TotalBidAbsorptionText.Color = More_Selling_Imbalance_Color.GetColor();
					TotalBidAbsorptionText.FontSize = Updated_Font_Size;
				}
				else TotalBidAbsorptionText.Color = Sellers_Absorption_Text_Color.GetColor();
				TotalBidAbsorptionText.TextAlignment = DT_VCENTER | DT_LEFT;
				TotalBidAbsorptionText.UseRelativeVerticalValues = 0;
				ThisString.Format("%i", p_BidTotalAbsorptions[LoopCurrentArrayIndex]);
				StringLength = ThisString.GetLength();
				switch (StringLength) {
				case 1: ChangeLengthFactor = 2;
					break;
				case 2: ChangeLengthFactor = 1;
					break;
				case 3: ChangeLengthFactor = 0;
					break;
				case 4: ChangeLengthFactor = 0;
					break;
				case 5: ChangeLengthFactor = -1;
					break;
				case 6: ChangeLengthFactor = -1;
					break;
				}
				StringSCLength = (int)(ceilf(OneCharSCWidthUnits * ((float)StringLength + ChangeLengthFactor)));
				TotalBidAbsorptionText.BeginDateTime = (double)(Column1Position - StringSCLength);
				TotalBidAbsorptionText.BeginValue = LoopPrice;
				TotalBidAbsorptionText.Text.Format("%i", p_BidTotalAbsorptions[LoopCurrentArrayIndex]).GetChars();
				//if (RecentAbsProfileVolUnit > 0)
				sc.UseTool(TotalBidAbsorptionText);
			}
		}
	}

	// +++++++++++++++++++++++++++++++++   Pulling_Stacking_Section  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	float StackAvg = 0; float PullAvg = 0;
	if (sc.IsReplayRunning() == 0) {
		// Run through all dom levels and find the Largest Pull/Stack vol (LargestPullStackVol).
		int StackSum = 0; int PullSum = 0; int PullLevelsCounter = 0; int  StackLevelsCounter = 0;
		//float StackAvg = 0; float PullAvg = 0;

		for (int DomLevelsCounter = 0; DomLevelsCounter <= Number_Of_Depth_Levels.GetInt() - 1; DomLevelsCounter++) {
			if (abs(sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize)) > LargestPullStackVol)  LargestPullStackVol = abs(sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize));
			if (abs(sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize)) > LargestPullStackVol)  LargestPullStackVol = abs(sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize));
			if (sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize) > 0) {
				StackSum += sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize);
				StackLevelsCounter++;
			}
			else {
				PullSum += sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize);
				PullLevelsCounter++;
			}
			if (sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize) > 0) {
				StackSum += sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize);
				StackLevelsCounter++;
			}
			else {
				PullSum += sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize);
				PullLevelsCounter++;
			}
		}
		PullAvg = (float)PullSum / (float)PullLevelsCounter;
		StackAvg = (float)StackSum / (float)StackLevelsCounter;

		int PullStackProfileVolUnit = (int)(ceilf((float)LargestPullStackVol / (float)OneColumnWidth));
		PreviousBidPullStackValue = sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid);
		PreviousAskPullStackValue = sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask);

		// Populate all dom levels with Stack/Pull bars and text
		for (int DomLevelsCounter = 0; DomLevelsCounter <= Number_Of_Depth_Levels.GetInt() - 1; DomLevelsCounter++) {
			if (sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize) != 0) {
				PullStackAskBars.Clear();
				PullStackAskBars.AddAsUserDrawnDrawing = 1;
				PullStackAskBars.ChartNumber = sc.ChartNumber;
				PullStackAskBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
				PullStackAskBars.LineNumber = 10200001 + DomLevelsCounter;
				PullStackAskBars.AddMethod = UTAM_ADD_OR_ADJUST;
				if (sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize) > 0) {
					PullStackAskBars.Color = Positive_Pull_Stack_Bars_Outline_Color.GetColor();
					PullStackAskBars.SecondaryColor = Positive_Pull_Stack_Bars_Fill_Color.GetColor();

				}
				else {
					PullStackAskBars.Color = Negative_Pull_Stack_Bars_Outline_Color.GetColor();
					PullStackAskBars.SecondaryColor = Negative_Pull_Stack_Bars_Fill_Color.GetColor();
				}
				VolBarExtToRight = (int)(fabs((float)sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize)) / (float)PullStackProfileVolUnit);
				PullStackAskBars.EndDateTime = (double)(Column5Position + VolBarExtToRight);
				PullStackAskBars.TransparencyLevel = Bars_Transparency.GetInt();
				PullStackAskBars.LineWidth = Bars_Outline_Width.GetInt();
				PullStackAskBars.UseRelativeVerticalValues = 0;
				PullStackAskBars.BeginDateTime = Column5Position;
				PullStackAskBars.BeginValue = sc.Ask + DomLevelsCounter * sc.TickSize - sc.TickSize / 2;
				PullStackAskBars.EndValue = sc.Ask + DomLevelsCounter * sc.TickSize + sc.TickSize / 2;
				if (Want_Pull_Stack_Column.GetYesNo())   sc.UseTool(PullStackAskBars);

				PullStackAskText.Clear();
				PullStackAskText.AddAsUserDrawnDrawing = 1;
				PullStackAskText.ChartNumber = sc.ChartNumber;
				PullStackAskText.DrawingType = DRAWING_TEXT;
				PullStackAskText.LineNumber = 10200401 + DomLevelsCounter;
				PullStackAskText.AddMethod = UTAM_ADD_OR_ADJUST;
				PullStackAskText.FontSize = Updated_Font_Size;
				PullStackAskText.FontBold = 1;
				PullStackAskText.Text.Format("%i", sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize));
				if (sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + DomLevelsCounter * sc.TickSize) > 0) {
					PullStackAskText.Color = Positive_Pull_Stack_Text_Color.GetColor();
				}
				else {
					PullStackAskText.Color = Negative_Pull_Stack_Text_Color.GetColor();
				}
				PullStackAskText.BeginDateTime = Column5Position;
				PullStackAskText.TextAlignment = DT_VCENTER | DT_LEFT;
				PullStackAskText.UseRelativeVerticalValues = 0;
				PullStackAskText.BeginValue = sc.Ask + DomLevelsCounter * sc.TickSize;
				if (Want_Pull_Stack_Column.GetYesNo()) sc.UseTool(PullStackAskText);
			}

			if (sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize) != 0) {
				PullStackBidBars.Clear();
				PullStackBidBars.AddAsUserDrawnDrawing = 1;
				PullStackBidBars.ChartNumber = sc.ChartNumber;
				PullStackBidBars.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
				PullStackBidBars.LineNumber = 10200000 - DomLevelsCounter;
				PullStackBidBars.AddMethod = UTAM_ADD_OR_ADJUST;
				if (sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize) > 0) {
					PullStackBidBars.Color = Positive_Pull_Stack_Bars_Outline_Color.GetColor();
					PullStackBidBars.SecondaryColor = Positive_Pull_Stack_Bars_Fill_Color.GetColor();
				}
				else {
					PullStackBidBars.Color = Negative_Pull_Stack_Bars_Outline_Color.GetColor();
					PullStackBidBars.SecondaryColor = Negative_Pull_Stack_Bars_Fill_Color.GetColor();
				}
				VolBarExtToRight = (int)(fabs((float)sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize)) / (float)PullStackProfileVolUnit);
				PullStackBidBars.EndDateTime = (double)(Column5Position + VolBarExtToRight);
				PullStackBidBars.TransparencyLevel = Bars_Transparency.GetInt();
				PullStackBidBars.LineWidth = Bars_Outline_Width.GetInt();
				PullStackBidBars.UseRelativeVerticalValues = 0;
				PullStackBidBars.BeginDateTime = Column5Position;
				PullStackBidBars.BeginValue = sc.Bid - DomLevelsCounter * sc.TickSize - sc.TickSize / 2;
				PullStackBidBars.EndValue = sc.Bid - DomLevelsCounter * sc.TickSize + sc.TickSize / 2;
				if (Want_Pull_Stack_Column.GetYesNo()) sc.UseTool(PullStackBidBars);

				PullStackBidText.Clear();
				PullStackBidText.AddAsUserDrawnDrawing = 1;
				PullStackBidText.ChartNumber = sc.ChartNumber;
				PullStackBidText.DrawingType = DRAWING_TEXT;
				PullStackBidText.LineNumber = 10200400 - DomLevelsCounter;
				PullStackBidText.AddMethod = UTAM_ADD_OR_ADJUST;
				PullStackBidText.FontSize = Updated_Font_Size;
				PullStackBidText.FontBold = 1;
				PullStackBidText.Text.Format("%i", sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize));
				//StringLength = PullStackBidText.Text.GetLength();
				if (sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - DomLevelsCounter * sc.TickSize) > 0) {
					PullStackBidText.Color = Positive_Pull_Stack_Text_Color.GetColor();
				}
				else {
					PullStackBidText.Color = Negative_Pull_Stack_Text_Color.GetColor();
				}
				PullStackBidText.BeginDateTime = Column5Position;
				PullStackBidText.TextAlignment = DT_VCENTER | DT_LEFT;
				PullStackBidText.UseRelativeVerticalValues = 0;
				PullStackBidText.BeginValue = sc.Bid - DomLevelsCounter * sc.TickSize;
				if (Want_Pull_Stack_Column.GetYesNo())	sc.UseTool(PullStackBidText);
			}
		}
	}


	// +++++++++++++++++++++++++++++++++++ Draw Values Under Bars +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	if (Draw_Values_Under_Bars.GetYesNo() == 1) {
		if (PreviousIndex != sc.ArraySize - 1) UnderBarsTextCounter += 2;
		// ================ Draw Deltas Under Bars =======================
		int Delta = (int)(sc.AskVolume[sc.ArraySize - 1] - sc.BidVolume[sc.ArraySize - 1]);
		BarDelta.Clear();
		BarDelta.AddAsUserDrawnDrawing = 1;
		BarDelta.ChartNumber = sc.ChartNumber;
		BarDelta.DrawingType = DRAWING_TEXT;
		BarDelta.LineNumber = 10201000 + UnderBarsTextCounter;
		BarDelta.AddMethod = UTAM_ADD_OR_ADJUST;
		BarDelta.FontSize = Font_Size.GetInt();
		BarDelta.FontBold = 1;
		if (Delta >= 0) BarDelta.Color = Bar_Positive_Delta_Color.GetColor();
		else BarDelta.Color = Bar_Negative_Delta_Color.GetColor();
		BarDelta.TextAlignment = DT_VCENTER | DT_CENTER;
		BarDelta.UseRelativeVerticalValues = 0;
		BarDelta.BeginIndex = sc.ArraySize - 1;
		BarDelta.BeginValue = sc.Low[sc.ArraySize - 1] - 3 * sc.TickSize;
		BarDelta.Text.Format("%i", Delta);
		sc.UseTool(BarDelta);


		// ================ Draw BarSumRecentAbsorptions Under Bars =======================
		int RecentAbsorptionSums = 0;
		for (float i = sc.Ask; i <= sc.High[sc.ArraySize - 1]; i += sc.TickSize) {
			RecentAbsorptionSums += sc.GetRecentAskVolumeAtPrice(i);
		}
		for (float i = sc.Bid; i >= sc.Low[sc.ArraySize - 1]; i -= sc.TickSize) {
			RecentAbsorptionSums -= sc.GetRecentBidVolumeAtPrice(i);
		}

		BarSumRecentAbsorptions.Clear();
		BarSumRecentAbsorptions.AddAsUserDrawnDrawing = 1;
		BarSumRecentAbsorptions.ChartNumber = sc.ChartNumber;
		BarSumRecentAbsorptions.DrawingType = DRAWING_TEXT;
		BarSumRecentAbsorptions.LineNumber = 10202000 + UnderBarsTextCounter + 1;
		BarSumRecentAbsorptions.AddMethod = UTAM_ADD_OR_ADJUST;
		BarSumRecentAbsorptions.FontSize = Font_Size.GetInt();
		BarSumRecentAbsorptions.FontBold = 1;
		if (RecentAbsorptionSums >= 0) BarSumRecentAbsorptions.Color = Bar_Positive_Absorptions_Sum_Color.GetColor();
		else BarSumRecentAbsorptions.Color = Bar_Negative_Absorptions_Sum_Color.GetColor();
		BarSumRecentAbsorptions.TextAlignment = DT_VCENTER | DT_CENTER;
		BarSumRecentAbsorptions.UseRelativeVerticalValues = 0;
		BarSumRecentAbsorptions.BeginIndex = sc.ArraySize - 1;
		BarSumRecentAbsorptions.BeginValue = sc.Low[sc.ArraySize - 1] - 4 * sc.TickSize;
		BarSumRecentAbsorptions.Text.Format("%i", RecentAbsorptionSums);
		sc.UseTool(BarSumRecentAbsorptions);
	}


	// +++++++++++++++ Draw Absorption Signals On Bars +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	if (sc.ArraySize - 1 != PreviousIndex) {
		LargestAskCumAbsBar = 0;
		LargestBidCumAbsBar = 0;
	}
	if (Draw_Absorption_On_Bars.GetYesNo() == 1) {
		if (p_AskCumulativeAbsorptions[(int)(sc.Ask / sc.TickSize) - ArrayPriceDifference] >= (int)(CumulativeColumnAvg * Absorption_On_Bars_Signal_Threshold.GetInt() / 100) && p_AskCumulativeAbsorptions[(int)(sc.Ask / sc.TickSize) - ArrayPriceDifference] > LargestAskCumAbsBar) {
			CumAskAbsOnBarSignalTopLine[sc.ArraySize - 1] = sc.Ask + sc.TickSize / 2;
			CumAskAbsOnBarSignalBottomLine[sc.ArraySize - 1] = sc.Ask - sc.TickSize / 2;
			LargestAskCumAbsBar = p_AskCumulativeAbsorptions[(int)(sc.Ask / sc.TickSize) - ArrayPriceDifference];
			PreviousCumAskAbsOnBarSignalPrice = sc.Ask;
			PreviousCumAskAbsOnBarSignalIndex = sc.ArraySize - 1;
		}
		if (p_BidCumulativeAbsorptions[(int)(sc.Bid / sc.TickSize) - ArrayPriceDifference] >= (int)(CumulativeColumnAvg * Absorption_On_Bars_Signal_Threshold.GetInt() / 100) && p_BidCumulativeAbsorptions[(int)(sc.Bid / sc.TickSize) - ArrayPriceDifference] > LargestBidCumAbsBar) {
			CumBidAbsOnBarSignalTopLine[sc.ArraySize - 1] = sc.Bid + sc.TickSize / 2;
			CumBidAbsOnBarSignalBottomLine[sc.ArraySize - 1] = sc.Bid - sc.TickSize / 2;
			LargestBidCumAbsBar = p_BidCumulativeAbsorptions[(int)(sc.Bid / sc.TickSize) - ArrayPriceDifference];
			PreviousCumBidAbsOnBarSignalPrice = sc.Bid;
			PreviousCumBidAbsOnBarSignalIndex = sc.ArraySize - 1;
		}

		/*if (sc.ArraySize - 1 != PreviousIndex) {
			if (PreviousCumAskAbsOnBarSignalIndex == sc.ArraySize - 1 - 1) {
				std::ofstream file(FileName, std::ios::out | std::ios::app);
				if (!file) {
					SCString Buffer;
					Buffer.Format("Unable to open file - ", FileName);
					sc.AddMessageToLog(Buffer, 1);
				}

				int ValueFormat = sc.BaseGraphValueFormat;
				char *formatString;
				formatString = "%s,%s,%s,%s,%s,%s";

				SCString SignalDataString;
				SignalDataString.Format(formatString,
					"Ask",
					sc.FormatGraphValue(Year, 0).GetChars(),
					sc.FormatGraphValue(Month, 0).GetChars(),
					sc.FormatGraphValue(Day, 0).GetChars(),
					sc.FormatGraphValue(PreviousCumAskAbsOnBarSignalPrice, sc.BaseGraphValueFormat).GetChars(),
					sc.FormatGraphValue(PreviousCumAskAbsOnBarSignalIndex, 0).GetChars()
				);

				file << SignalDataString << std::endl;

				file.close();
				PreviousCumAskAbsOnBarSignalPrice = sc.Ask;
			}
			if (PreviousCumBidAbsOnBarSignalIndex == sc.ArraySize - 1 - 1) {
				std::ofstream file(FileName, std::ios::out | std::ios::app);
				if (!file) {
					SCString Buffer;
					Buffer.Format("Unable to open file - ", FileName);
					sc.AddMessageToLog(Buffer, 1);
					//return;
				}

				int ValueFormat = sc.BaseGraphValueFormat;
				char *formatString;
				formatString = "%s,%s,%s,%s,%s,%s";

				SCString SignalDataString;
				SignalDataString.Format(formatString,
					"Bid",
					sc.FormatGraphValue(Year, 0).GetChars(),
					sc.FormatGraphValue(Month, 0).GetChars(),
					sc.FormatGraphValue(Day, 0).GetChars(),
					sc.FormatGraphValue(PreviousCumBidAbsOnBarSignalPrice, sc.BaseGraphValueFormat).GetChars(),
					sc.FormatGraphValue(PreviousCumBidAbsOnBarSignalIndex, 0).GetChars()
				);

				file << SignalDataString << std::endl;

				file.close();
				PreviousCumBidAbsOnBarSignalPrice = sc.Bid;
			}
		}*/
	}

	// +++++++++++++++++++++++ Absorption With Pull/Stack Signals ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	if (sc.Ask != PreviousAskPrice) sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203000);
	if (sc.Bid != PreviousBidPrice) sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203001);

	if (p_AskCumulativeAbsorptions[(int)(sc.Ask / sc.TickSize) - ArrayPriceDifference] >= (int)(CumulativeColumnAvg * Absorption_On_Bars_Signal_Threshold.GetInt() / 100)) {
		AskAbsWithPullStack.Clear();
		AskAbsWithPullStack.AddAsUserDrawnDrawing = 1;
		AskAbsWithPullStack.ChartNumber = sc.ChartNumber;
		AskAbsWithPullStack.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
		AskAbsWithPullStack.AddMethod = UTAM_ADD_OR_ADJUST;
		AskAbsWithPullStack.TransparencyLevel = Bars_Transparency.GetInt();
		AskAbsWithPullStack.LineWidth = AbsWithPullStack_Outline_Width.GetInt();
		AskAbsWithPullStack.UseRelativeVerticalValues = 0;
		AskAbsWithPullStack.BeginDateTime = (double)(-ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1))) + Column2Position);
		AskAbsWithPullStack.EndDateTime = (double)(OneColumnWidth + Column3Position);
		AskAbsWithPullStack.LineNumber = 10203000;
		AskAbsWithPullStack.Color = Buyers_Absorption_Sellers_Stacking_OutLine_Color.GetColor();
		AskAbsWithPullStack.BeginValue = sc.Ask - sc.TickSize / 2;
		AskAbsWithPullStack.EndValue = sc.Ask + sc.TickSize / 2;
		sc.UseTool(AskAbsWithPullStack);
		if (Want_Absorption_Sound_Alert.GetYesNo()) sc.SetAlert(Buyers_Absorption_Signal_Sound_Alert_Number.GetInt());

		if (sc.IsReplayRunning() == 0) {  //dont try to draw l3a rectangles while replaying because no pull/stack data is avalable
			if (sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask) >= (int)(StackAvg * Pull_Stack__Threshold.GetInt() / 100)) {
				AskAbsWithPullStack.LineNumber = 10203000;
				AskAbsWithPullStack.Color = Buyers_Absorption_Sellers_Stacking_OutLine_Color.GetColor();
				AskAbsWithPullStack.BeginDateTime = (double)(-ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1))) + Column1Position);
				AskAbsWithPullStack.EndDateTime = (double)(OneColumnWidth + Column5Position);
				AskAbsWithPullStack.BeginValue = sc.Ask - sc.TickSize / 2;
				AskAbsWithPullStack.EndValue = sc.Ask + sc.TickSize / 2;
				sc.UseTool(AskAbsWithPullStack);
			}
			else if (sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask) <= (int)(PullAvg * Pull_Stack__Threshold.GetInt() / 100)) {
				AskAbsWithPullStack.LineNumber = 10203000;
				AskAbsWithPullStack.Color = Buyers_Absorption_Sellers_Pulling_OutLine_Color.GetColor();
				AskAbsWithPullStack.BeginDateTime = (double)(-ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1))) + Column1Position);
				AskAbsWithPullStack.EndDateTime = (double)(OneColumnWidth + Column5Position);
				AskAbsWithPullStack.BeginValue = sc.Ask - sc.TickSize / 2;
				AskAbsWithPullStack.EndValue = sc.Ask + sc.TickSize / 2;
				sc.UseTool(AskAbsWithPullStack);
			}
		}
	}
	else if (sc.GetUserDrawnDrawingByLineNumber(0, 10203000, AskAbsWithPullStack)) sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203000);


	if (p_BidCumulativeAbsorptions[(int)(sc.Bid / sc.TickSize) - ArrayPriceDifference] >= (int)(CumulativeColumnAvg * Absorption_On_Bars_Signal_Threshold.GetInt() / 100)) {
		BidAbsWithPullStack.Clear();
		BidAbsWithPullStack.AddAsUserDrawnDrawing = 1;
		BidAbsWithPullStack.ChartNumber = sc.ChartNumber;
		BidAbsWithPullStack.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
		BidAbsWithPullStack.AddMethod = UTAM_ADD_OR_ADJUST;
		BidAbsWithPullStack.TransparencyLevel = Bars_Transparency.GetInt();
		BidAbsWithPullStack.LineWidth = AbsWithPullStack_Outline_Width.GetInt();
		BidAbsWithPullStack.UseRelativeVerticalValues = 0;
		BidAbsWithPullStack.BeginDateTime = (double)(Column2Position - (ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1)))));
		BidAbsWithPullStack.EndDateTime = (double)(Column3Position + OneColumnWidth);
		BidAbsWithPullStack.LineNumber = 10203001;
		BidAbsWithPullStack.Color = Sellers_Absorption_Buyers_Stacking_OutLine_Color.GetColor();
		BidAbsWithPullStack.BeginValue = sc.Bid - sc.TickSize / 2;
		BidAbsWithPullStack.EndValue = sc.Bid + sc.TickSize / 2;
		sc.UseTool(BidAbsWithPullStack);
		if (Want_Absorption_Sound_Alert.GetYesNo()) sc.SetAlert(Sellers_Absorption_Signal_Sound_Alert_Number.GetInt());

		if (sc.IsReplayRunning() == 0) {  //dont try to draw l3a rectangles while replaying because no pull/stack data is avalable
			if (sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid) >= (int)(StackAvg * Pull_Stack__Threshold.GetInt() / 100)) {
				BidAbsWithPullStack.LineNumber = 10203001;
				BidAbsWithPullStack.Color = Sellers_Absorption_Buyers_Stacking_OutLine_Color.GetColor();
				BidAbsWithPullStack.BeginDateTime = (double)(Column1Position - (ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1)))));
				BidAbsWithPullStack.EndDateTime = (double)(Column5Position + OneColumnWidth);
				BidAbsWithPullStack.BeginValue = sc.Bid - sc.TickSize / 2;
				BidAbsWithPullStack.EndValue = sc.Bid + sc.TickSize / 2;
				sc.UseTool(BidAbsWithPullStack);

			}
			else if (sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid) <= (int)(PullAvg * Pull_Stack__Threshold.GetInt() / 100)) {
				BidAbsWithPullStack.LineNumber = 10203001;//(int)(sc.Bid / sc.TickSize) + 210000;
				BidAbsWithPullStack.Color = Sellers_Absorption_Buyers_Pulling_OutLine_Color.GetColor();
				BidAbsWithPullStack.BeginDateTime = (double)(Column1Position - (int)(ceilf((5 + 5 * (((float)Font_Size.GetInt() / 9.0f) - 1)))));
				BidAbsWithPullStack.EndDateTime = (double)(Column5Position + OneColumnWidth);
				BidAbsWithPullStack.BeginValue = sc.Bid - sc.TickSize / 2;
				BidAbsWithPullStack.EndValue = sc.Bid + sc.TickSize / 2;
				sc.UseTool(BidAbsWithPullStack);
			}
		}
	}
	else if (sc.GetUserDrawnDrawingByLineNumber(0, 10203001, BidAbsWithPullStack)) sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203001);



	//+++++++++++++++++++++ Current Price Line +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	if (Show_Current_Price_Line.GetYesNo() == 1) {
		CurrentPriceLine.Clear();
		CurrentPriceLine.AddAsUserDrawnDrawing = 1;
		CurrentPriceLine.ChartNumber = sc.ChartNumber;
		CurrentPriceLine.DrawingType = DRAWING_HORIZONTALLINE;
		CurrentPriceLine.LineNumber = 10203003;
		CurrentPriceLine.AddMethod = UTAM_ADD_OR_ADJUST;
		if (sc.Close[sc.ArraySize - 1] == sc.Ask) CurrentPriceLine.Color = Current_Price_Line.PrimaryColor;
		else CurrentPriceLine.Color = Current_Price_Line.SecondaryColor;
		CurrentPriceLine.LineStyle = Current_Price_Line.LineStyle;
		CurrentPriceLine.LineWidth = Current_Price_Line.LineWidth;
		CurrentPriceLine.UseRelativeVerticalValues = 0;
		CurrentPriceLine.BeginValue = sc.Close[sc.ArraySize - 1];
		sc.UseTool(CurrentPriceLine);
	}

	//++++++++++++++++++  Top Text  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	/*TopText.Clear();
	TopText.AddAsUserDrawnDrawing = 1;
	TopText.ChartNumber = sc.ChartNumber;
	TopText.DrawingType = DRAWING_TEXT;
	TopText.AddMethod = UTAM_ADD_OR_ADJUST;
	TopText.FontSize = Font_Size.GetInt();
	TopText.FontBold = 1;
	TopText.Color = Top_Text_Color.GetColor();
	TopText.TextAlignment = DT_VCENTER | DT_LEFT;
	TopText.UseRelativeVerticalValues = 1;
	TopText.Text.Format("CumAbsAvg: %.0f       PullAvg: %.0f  StackAvg: %.0f     Session Delta: %i", CumulativeColumnAvg, PullAvg, StackAvg, SessionDelta);
	TopText.LineNumber = 10203004;
	TopText.BeginDateTime = 75;
	TopText.BeginValue = 99;
	sc.UseTool(TopText);*/

	// +++++++   Update Persistent Vars Values ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	PreviousReplayStatus = sc.ReplayStatus;
	PreviousLargestRecentAbsorption = LargestRecentAbsorption;
	PreviousLargestCumulativeAbsorption = LargestCumulativeAbsorption;
	PreviousLargestTotalAbsorption = LargestTotalAbsorption;
	PreviousAskPrice = sc.Ask;
	PreviousBidPrice = sc.Bid;
	PreviousIndex = sc.ArraySize - 1;
	OnlyOnce = 1; // this needs to be here otherwise it would reset to1 only after all the autoloop is done
	PreviousChartName = ChartName.GetChars();
	PreviousWindowPixelWidth = WindowPixelWidth;
	PreviousLastTradeTime = sc.LatestDateTimeForLastBar.GetTime();
	p_WantTotalVolColumn = Want_TotalVol_Column.GetYesNo();
	p_WantCumulativeABsorptionColumn = Want_Cumulative_Absorption_Column.GetYesNo();
	p_WantRecentAbsorptionColmn = Want_Recent_Absorption_Column.GetYesNo();
	p_WantPullStackColumn = Want_Pull_Stack_Column.GetYesNo();
	p_WantAgrressionBar = Want_Aggression_Bar_Column.GetYesNo();
	Previous_RightClick_TextToggle_State = RightClick_TextToggle_State;


	// +++++++++++++++++++++++++++++ last call ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	if (sc.LastCallToFunction) {
		// Delete all recent and cumulative and Total absorption text and bars
		for (int i = LowestLineNumber - 300; i <= HighestLineNumber + 300; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i); // line numbers of text
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 2000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 4000); // line numbers of text
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 6000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 8000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 10000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 12000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 14000); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 16000); //line numbers of bars
		}
		// Delete all Pull/Stack text and bars
		for (int i = 0; i <= Number_Of_Depth_Levels.GetInt(); i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10200001 + i); // line numbers of text
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10200401 + i); //line numbers of bars
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10200000 - i); // line numbers of text
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10200400 - i); //line numbers of bars
		}


		// Delete all Under Bars Text
		for (int i = 10201000; i <= 10202000 + 2 + UnderBarsTextCounter; i += 2) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1);
		}

		// Delete all L3A Rectangles
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203000);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203001);


		// Delete Current Price Line
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203003);


		// Delete Top Text
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203004);

		//Delete Meter_Bars
		//sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203005);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203006);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203007);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203008);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203009);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203010);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203011);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203012);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 10203013);

		//Delete Pulling Alert SignalDataString
		for (int i = 0; i <= PullingAlertCounter; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 12000000 + i);
		}

		//Remove Shortcut Menu Items
		sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, Reset_L3A_MenuID);
		sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, Reset_Aggression_Meter_MenuID);
		sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, L3_Text_Toggle_Menu_ID);

		
		//Free Allocated Memory
		if (p_AskRecentAbsorptions != NULL)
		{
			sc.FreeMemory(p_AskRecentAbsorptions);
			sc.SetPersistentPointer(1, NULL);
		}

		if (p_BidRecentAbsorptions != NULL)
		{
			sc.FreeMemory(p_BidRecentAbsorptions);
			sc.SetPersistentPointer(2, NULL);
		}

		if (p_AskCumulativeAbsorptions != NULL)
		{
			sc.FreeMemory(p_AskCumulativeAbsorptions);
			sc.SetPersistentPointer(3, NULL);
		}
		if (p_BidCumulativeAbsorptions != NULL)
		{
			sc.FreeMemory(p_BidCumulativeAbsorptions);
			sc.SetPersistentPointer(4, NULL);
		}
		if (p_RecentAskAbsToBeErased != NULL)
		{
			sc.FreeMemory(p_RecentAskAbsToBeErased);
			sc.SetPersistentPointer(5, NULL);
		}
		if (p_RecentBidAbsToBeErased != NULL)
		{
			sc.FreeMemory(p_RecentBidAbsToBeErased);
			sc.SetPersistentPointer(6, NULL);
		}
		/*if (p_BeforeClearedCumAbsorption != NULL)
		{
			sc.FreeMemory(p_BeforeClearedCumAbsorption);
			sc.SetPersistentPointer(7, NULL);
		}*/
		if (p_AskTotalAbsorptions != NULL)
		{
			sc.FreeMemory(p_AskTotalAbsorptions);
			sc.SetPersistentPointer(8, NULL);
		}
		if (p_BidTotalAbsorptions != NULL)
		{
			sc.FreeMemory(p_BidTotalAbsorptions);
			sc.SetPersistentPointer(9, NULL);
		}

	}
}

