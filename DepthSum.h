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



SCSFExport scsf_DepthSum(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	
	SCSubgraphRef Bids = sc.Subgraph[SGIndex++];
	SCSubgraphRef Asks = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef Based_On = sc.Input[InputIndex++];
	SCInputRef NumberOfLevel = sc.Input[InputIndex++];
	SCInputRef MinContracts = sc.Input[InputIndex++];
	SCInputRef MaxContracts = sc.Input[InputIndex++];
	SCInputRef MaxUntil = sc.Input[InputIndex++];
	SCInputRef BarPosition = sc.Input[InputIndex++];

	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "DepthSum";
		sc.GraphRegion = 0;
		sc.StudyDescription = "Sum Of Ask&Bid-Depth";

		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		sc.UsesMarketDepthData = 1;

		Based_On.Name = "What should be summed?";
		Based_On.SetCustomInputStrings("DOM; Pulling/Stacking;");
		Based_On.SetCustomInputIndex(0);

		NumberOfLevel.Name = "Number of Bid/Ask Levels to Sum";
		NumberOfLevel.SetInt(24);

		MinContracts.Name = "Only count larger than this (for all levels)";
		MinContracts.SetInt(0);

		MaxContracts.Name = "Maximum counted contracts";
		MaxContracts.SetInt(250);

		MaxUntil.Name = "Use maximum counted contracts until Bid/Ask Levels";
		MaxUntil.SetInt(24);

		BarPosition.Name = "Bar's horizontal position";
		BarPosition.SetInt(85);

		Bids.Name = "Bids";
		Bids.DrawStyle = DRAWSTYLE_LINE;
		Bids.LineWidth = 2;
		Bids.PrimaryColor = RGB(0, 255, 0);

		Asks.Name = "Asks";
		Asks.DrawStyle = DRAWSTYLE_LINE;
		Asks.LineWidth = 2;
		Asks.PrimaryColor = RGB(255, 0, 0);

		return;
	}

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}

	int BidsSum = 0;
	int AsksSum = 0;
	int Quantity = 0;

	for (int Level = 0; Level < NumberOfLevel.GetInt(); Level++) 
	{		// count the latest DOM volumes Sums

		s_MarketDepthEntry DepthEntry;

		if (Based_On.GetIndex() == 0) { // if based on DOM
			sc.GetBidMarketDepthEntryAtLevel(DepthEntry, Level);
			if (MinContracts.GetInt() <= DepthEntry.Quantity) Quantity = DepthEntry.Quantity;
			else Quantity = 0;
			if (Level <= MaxUntil.GetInt()) BidsSum += min(MaxContracts.GetInt(), Quantity);
			else BidsSum += Quantity;

			sc.GetAskMarketDepthEntryAtLevel(DepthEntry, Level);
			if (MinContracts.GetInt() <= DepthEntry.Quantity) Quantity = DepthEntry.Quantity;
			else Quantity = 0;
			if (Level <= MaxUntil.GetInt()) AsksSum += min(MaxContracts.GetInt(), Quantity);
			else AsksSum += Quantity;
		}

		else { // If based on Pulling/Stacking	
			if (Level >= MaxUntil.GetInt()) {
				BidsSum += sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - (float)Level * sc.TickSize);
				AsksSum += sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + (float)Level * sc.TickSize);
			}
		}
	}

	s_UseTool AsksDepthBar, BidsDepthBar, AsksDepthText, BidsDepthText;

	AsksDepthBar.Clear();
	AsksDepthBar.AddAsUserDrawnDrawing = 1;
	AsksDepthBar.ChartNumber = sc.ChartNumber;
	AsksDepthBar.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
	AsksDepthBar.LineNumber = 13000000;
	AsksDepthBar.AddMethod = UTAM_ADD_OR_ADJUST;
	AsksDepthBar.Color = RGB(255, 255, 255);
	AsksDepthBar.SecondaryColor = RGB(255,0,0);
	AsksDepthBar.LineWidth = 3;
	AsksDepthBar.UseRelativeVerticalValues = 1;
	AsksDepthBar.BeginDateTime = BarPosition.GetInt();
	AsksDepthBar.EndDateTime = BarPosition.GetInt() + 3;
	AsksDepthBar.BeginValue = 40 + (int)(ceilf(((float)BidsSum / (float)(AsksSum + BidsSum)) * 20));
	AsksDepthBar.EndValue = 60;
	sc.UseTool(AsksDepthBar);

	BidsDepthBar.Clear();
	BidsDepthBar.AddAsUserDrawnDrawing = 1;
	BidsDepthBar.ChartNumber = sc.ChartNumber;
	BidsDepthBar.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
	BidsDepthBar.LineNumber = 13000001;
	BidsDepthBar.AddMethod = UTAM_ADD_OR_ADJUST;
	BidsDepthBar.Color = RGB(255,255,255);
	BidsDepthBar.SecondaryColor = RGB(0, 255, 0);
	//Sellers_Meter_Bar.TransparencyLevel = Bars_Transparency.GetInt();
	BidsDepthBar.LineWidth = 3;
	BidsDepthBar.UseRelativeVerticalValues = 1;
	BidsDepthBar.BeginDateTime = BarPosition.GetInt();
	BidsDepthBar.EndDateTime = BarPosition.GetInt() + 3;
	BidsDepthBar.BeginValue = 40;
	BidsDepthBar.EndValue = 40 + (int)(ceilf(((float)BidsSum / (float)(AsksSum + BidsSum)) * 20));
	sc.UseTool(BidsDepthBar);


	AsksDepthText.Clear();
	AsksDepthText.AddAsUserDrawnDrawing = 1;
	AsksDepthText.ChartNumber = sc.ChartNumber;
	AsksDepthText.DrawingType = DRAWING_TEXT;
	AsksDepthText.AddMethod = UTAM_ADD_OR_ADJUST;
	AsksDepthText.FontSize = 8;
	AsksDepthText.FontBold = 1;
	AsksDepthText.Color = RGB(255,255,255);
	AsksDepthText.TextAlignment = DT_VCENTER | DT_LEFT;
	AsksDepthText.UseRelativeVerticalValues = 1;
	AsksDepthText.Text.Format("%.1f", (float)AsksSum/1000);
	AsksDepthText.LineNumber = 13000002;
	AsksDepthText.BeginDateTime = BarPosition.GetInt();
	AsksDepthText.BeginValue = 61;
	sc.UseTool(AsksDepthText);

	BidsDepthText.Clear();
	BidsDepthText.AddAsUserDrawnDrawing = 1;
	BidsDepthText.ChartNumber = sc.ChartNumber;
	BidsDepthText.DrawingType = DRAWING_TEXT;
	BidsDepthText.AddMethod = UTAM_ADD_OR_ADJUST;
	BidsDepthText.FontSize = 8;
	BidsDepthText.FontBold = 1;
	BidsDepthText.Color = RGB(255,255,255);
	BidsDepthText.TextAlignment = DT_VCENTER | DT_LEFT;
	BidsDepthText.UseRelativeVerticalValues = 1;
	BidsDepthText.Text.Format("%.1f", (float)BidsSum/1000);
	BidsDepthText.LineNumber = 13000003;
	BidsDepthText.BeginDateTime = BarPosition.GetInt();
	BidsDepthText.BeginValue = 39;
	sc.UseTool(BidsDepthText);

	Bids[sc.ArraySize - 1] = BidsSum;
	Asks[sc.ArraySize - 1] = AsksSum;

	if (sc.LastCallToFunction) {
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 13000000);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 13000001);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 13000002);
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 13000003);
	}

}
