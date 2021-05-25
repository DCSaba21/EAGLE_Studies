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


SCSFExport scsf_Spread_Defence(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef BidDefenceSignalExtLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef AskDefenceSignalExtLine = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef LargeTradeThreashold = sc.Input[InputIndex++];
	SCInputRef WantSoundAlert = sc.Input[InputIndex++];
	SCInputRef BidDefenceAlertSound = sc.Input[InputIndex++];
	SCInputRef AskDefenceAlertSound = sc.Input[InputIndex++];
	SCInputRef BidDefenceSignalColor = sc.Input[InputIndex++];
	SCInputRef BidDefenceSignalSize = sc.Input[InputIndex++];	
	SCInputRef AskDefenceSignalColor = sc.Input[InputIndex++];
	SCInputRef AskDefenceSignalSize = sc.Input[InputIndex++];
	SCInputRef WantExtentionLine = sc.Input[InputIndex++];
	


	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "Spread_Defence";

		sc.FreeDLL = 1;
		sc.AutoLoop = 0;  //Automatic looping is enabled.
		sc.GraphRegion = 0;

		LargeTradeThreashold.Name = "LargeTradeThreashold (contracts)";
		LargeTradeThreashold.SetInt(35);

		WantSoundAlert.Name = "Want sound alert?";
		WantSoundAlert.SetYesNo(1);

		BidDefenceAlertSound.Name = "Bid Defence Sound Alert Number";
		BidDefenceAlertSound.SetInt(24);

		AskDefenceAlertSound.Name = "Ask Defence Sound Alert Number";
		AskDefenceAlertSound.SetInt(25);

		BidDefenceSignalColor.Name = "Bid Defence Signal Color";
		BidDefenceSignalColor.SetColor(0, 255, 255);

		BidDefenceSignalSize.Name = "Bid Defence Signal Size";
		BidDefenceSignalSize.SetInt(6);

		AskDefenceSignalColor.Name = "Ask Defence Signal Color";
		AskDefenceSignalColor.SetColor(128, 0, 255);

		AskDefenceSignalSize.Name = "Ask Defence Signal Size";
		AskDefenceSignalSize.SetInt(6);

		BidDefenceSignalExtLine.Name = "Bid Defence Extending Line";
		BidDefenceSignalExtLine.LineStyle = LINESTYLE_DOT;
		BidDefenceSignalExtLine.LineWidth = 1;
		BidDefenceSignalExtLine.PrimaryColor = RGB(0, 255, 255);

		AskDefenceSignalExtLine.Name = "Ask Defence Extending Line";
		AskDefenceSignalExtLine.LineStyle = LINESTYLE_DOT;
		AskDefenceSignalExtLine.LineWidth = 1;
		AskDefenceSignalExtLine.PrimaryColor = RGB(128, 0, 255);

		WantExtentionLine.Name = "Want extention line?";
		WantExtentionLine.SetYesNo(0);

		return;
	}

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}

	__int64& LastProcessedSequence = sc.GetPersistentInt64(1);
	c_SCTimeAndSalesArray TimeSales;

	int& AskSpreadState = sc.GetPersistentInt(2); // 0 - waitin for a move up  1 - moved up and now monitoring
	int& BidSpreadState = sc.GetPersistentInt(3);//// 0 - waitin for a move down  1 - moved down and now monitoring
	int& LineCounter = sc.GetPersistentInt(4);
	int& LargeAskTradeVol = sc.GetPersistentInt(5);
	int& LargeBidTradeVol = sc.GetPersistentInt(6);

	float& LastBidTradePrice = sc.GetPersistentFloat(0);
	float& LastAskTradePrice = sc.GetPersistentFloat(1);
	float& NewBidTradePrice = sc.GetPersistentFloat(2);
	float& NewAskTradePrice = sc.GetPersistentFloat(3);

	SCString str;
	//SCDateTime DTV;
	//int Year, Month, Day, Hour, Minute, Second, MilliSecond;

	sc.GetTimeAndSales(TimeSales);
	if (TimeSales.Size() == 0)	return;

	if (LastProcessedSequence != 0) {
		// Loop through the Time and Sales.
		for (int TSIndex = 0; TSIndex < TimeSales.Size(); ++TSIndex) {
			if (TimeSales[TSIndex].Sequence <= LastProcessedSequence) continue;

			if (TimeSales[TSIndex].Type == SC_TS_BID) {//checking if the trade happened at the bid
				if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier < LastBidTradePrice) {
					BidSpreadState = 1;
					//AskSpreadState = 0;
				}

				if (BidSpreadState > 0 && TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier > LastBidTradePrice) {
					//we returned
					if (BidSpreadState == 2) { // checking if we just had a large trade at the ask
						//Bid Defence alert Alert

						if (WantExtentionLine.GetYesNo()) {
							sc.AddLineUntilFutureIntersection
							(sc.ArraySize - 1 // where to start drawing
								, 4000000 + LineCounter  // LineIDForBar
								, TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier// The price level of the line
								, BidDefenceSignalExtLine.PrimaryColor
								, BidDefenceSignalExtLine.LineWidth
								, BidDefenceSignalExtLine.LineStyle
								, 0 //DisplayValueLabel.GetYesNo()
								, false //DisplayNameLabel // true/false
								, ""// "string" or string variable
							);
						}

						s_UseTool Bid_Defence_Alert_Signal;
						Bid_Defence_Alert_Signal.Clear();
						Bid_Defence_Alert_Signal.AddAsUserDrawnDrawing = 1;
						Bid_Defence_Alert_Signal.ChartNumber = sc.ChartNumber;
						Bid_Defence_Alert_Signal.DrawingType = DRAWING_MARKER;
						Bid_Defence_Alert_Signal.MarkerType = MARKER_TRIANGLEUP;
						Bid_Defence_Alert_Signal.MarkerSize = BidDefenceSignalSize.GetInt();
						Bid_Defence_Alert_Signal.Color = BidDefenceSignalColor.GetColor();
						Bid_Defence_Alert_Signal.LineNumber = 5000000 + LineCounter;
						Bid_Defence_Alert_Signal.AddMethod = UTAM_ADD_OR_ADJUST;
						Bid_Defence_Alert_Signal.UseRelativeVerticalValues = 0;
						Bid_Defence_Alert_Signal.BeginIndex = sc.ArraySize - 1;
						Bid_Defence_Alert_Signal.BeginValue = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
						sc.UseTool(Bid_Defence_Alert_Signal);


						LineCounter++;						
						if(WantSoundAlert.GetYesNo())sc.SetAlert(BidDefenceAlertSound.GetInt());
						//str.Format("Bid Defence Alert @%f Vol: %i", TimeSales[TSIndex].Price, LargeAskTradeVol);
						//sc.AddMessageToLog(str, 0);
					};

					BidSpreadState = 0;
				}

				if (TimeSales[TSIndex].Volume >= (unsigned int)LargeTradeThreashold.GetInt()) {
					if (AskSpreadState == 1) {
						AskSpreadState = 2;
						LargeBidTradeVol = TimeSales[TSIndex].Volume;
					}
				}

				LastBidTradePrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
			}


			if (TimeSales[TSIndex].Type == SC_TS_ASK) { //checking if the trade happened at the ask
				if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier > LastAskTradePrice) {
					AskSpreadState = 1;
					//BidSpreadState = 0;
				}

				if (AskSpreadState > 0 && TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier < LastAskTradePrice) {
					//we returned
					if (AskSpreadState == 2) {
						//Ask Defence Alert

						if (WantExtentionLine.GetYesNo()) {
							sc.AddLineUntilFutureIntersection
							(sc.ArraySize - 1 // where to start drawing
								, 4000000 + LineCounter  // LineIDForBar
								, TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier// The price level of the line+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								, AskDefenceSignalExtLine.PrimaryColor
								, AskDefenceSignalExtLine.LineWidth
								, AskDefenceSignalExtLine.LineStyle
								, 0 //DisplayValueLabel.GetYesNo()
								, false //DisplayNameLabel // true/false
								, ""// "string" or string variable
							);
						}

						s_UseTool Ask_Defence_Alert_Signal;
						Ask_Defence_Alert_Signal.Clear();
						Ask_Defence_Alert_Signal.AddAsUserDrawnDrawing = 1;
						Ask_Defence_Alert_Signal.ChartNumber = sc.ChartNumber;
						Ask_Defence_Alert_Signal.DrawingType = DRAWING_MARKER;
						Ask_Defence_Alert_Signal.MarkerType = MARKER_TRIANGLEDOWN;
						Ask_Defence_Alert_Signal.MarkerSize = AskDefenceSignalSize.GetInt();
						Ask_Defence_Alert_Signal.Color = AskDefenceSignalColor.GetColor();
						Ask_Defence_Alert_Signal.LineNumber = 5000000 + LineCounter;
						Ask_Defence_Alert_Signal.AddMethod = UTAM_ADD_OR_ADJUST;
						Ask_Defence_Alert_Signal.UseRelativeVerticalValues = 0;
						Ask_Defence_Alert_Signal.BeginIndex = sc.ArraySize - 1;
						Ask_Defence_Alert_Signal.BeginValue = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
						sc.UseTool(Ask_Defence_Alert_Signal);

						LineCounter++;
						if (WantSoundAlert.GetYesNo()) sc.SetAlert(AskDefenceAlertSound.GetInt());
						//str.Format("Ask Defence Alert @%f Vol: %i", TimeSales[TSIndex].Price, LargeBidTradeVol);
						//sc.AddMessageToLog(str, 0);
					}
					AskSpreadState = 0;
				}
				if (TimeSales[TSIndex].Volume >= (unsigned int)LargeTradeThreashold.GetInt()) {
					if (BidSpreadState == 1) {
						BidSpreadState = 2;
						LargeAskTradeVol = TimeSales[TSIndex].Volume;
					}
				}

				LastAskTradePrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
			}
		}
		LastProcessedSequence = TimeSales[TimeSales.Size() - 1].Sequence;
	}
	
	if (sc.LastCallToFunction) {
		for (int i = 0; i <= LineCounter; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 5000000 + i);
		}
	}
}
