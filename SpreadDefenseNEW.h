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


SCSFExport scsf_Spread_DefenSeNEW(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef BidDefenceSignalExtLine = sc.Subgraph[SGIndex++];
	SCSubgraphRef AskDefenceSignalExtLine = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef StableSpread = sc.Input[InputIndex++];
	SCInputRef LargeTradeThreashold = sc.Input[InputIndex++];
	SCInputRef WantSoundAlert = sc.Input[InputIndex++];
	SCInputRef BidDefenceAlertSound = sc.Input[InputIndex++];
	SCInputRef AskDefenceAlertSound = sc.Input[InputIndex++];
	SCInputRef BidDefenceSignalColor = sc.Input[InputIndex++];
	SCInputRef BidDefenceSignalSize = sc.Input[InputIndex++];
	SCInputRef AskDefenceSignalColor = sc.Input[InputIndex++];
	SCInputRef AskDefenceSignalSize = sc.Input[InputIndex++];
	SCInputRef WantExtentionLine = sc.Input[InputIndex++];

	//BidSpreadState = 0;
	//AskSpreadState = 0;
	//SpreadStability = 0;


	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "Spread_DefenceNEW";

		sc.FreeDLL = 1;
		sc.AutoLoop = 0;  //Automatic looping is enabled.
		sc.GraphRegion = 0;

		StableSpread.Name = "Stable Spread Lasting (trades)";
		StableSpread.SetInt(10);

		LargeTradeThreashold.Name = "Large Trade Threashold (contracts)";
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


	__int64& LastProcessedSequence = sc.GetPersistentInt64(1);
	c_SCTimeAndSalesArray TimeSales;

	int& AskSpreadState = sc.GetPersistentInt(2); // 0 - waiting for a Stable Spread  1 - waiting for a move up  2 - moved up and now monitoring  3 - opposing force  4 - succesful return
	int& BidSpreadState = sc.GetPersistentInt(3); // 0 - waiting for a Stable Spread  1- waiting for a move down  2 - moved down and now monitoring  3 - opposing force  4 - succesful return
	int& SpreadStability = sc.GetPersistentInt(4);
	int& LineCounter = sc.GetPersistentInt(5);

	float& StableBid = sc.GetPersistentFloat(0);
	float& StableAsk = sc.GetPersistentFloat(1);
	float& LastBidTradePrice = sc.GetPersistentFloat(2);
	float& LastAskTradePrice = sc.GetPersistentFloat(3);


	sc.GetTimeAndSales(TimeSales);
	if (TimeSales.Size() == 0)	return;

	if (LastProcessedSequence != 0) {

		for (int TSIndex = 0; TSIndex < TimeSales.Size(); ++TSIndex) {//  Loop through the Time and Sales
			if (TimeSales[TSIndex].Sequence <= LastProcessedSequence) continue; //...if there is still a Trade to process

			// first establish if we are looking for a Stable Spread STILL (State 0) OR looking for a NEW one (State 2)
			if ( (BidSpreadState == 0) && (AskSpreadState == 0) || (BidSpreadState == 2) || (AskSpreadState == 2) ) {
				
				if ( (TimeSales[TSIndex].Type == SC_TS_BID) && (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier == LastBidTradePrice) || //either @Bid,
			     (TimeSales[TSIndex].Type == SC_TS_ASK) && (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier == LastAskTradePrice) )	{ //or @Ask: price has to be the same as before (Bid or Ask)
						 SpreadStability += 1; //...and if yes, then add to the count
						 

						 if (SpreadStability == (unsigned int)StableSpread.GetInt()) { //and check if now we've reached it
		 					 BidSpreadState = 1; // 1=stable Bid, wait for move
		 					 AskSpreadState = 1; // 1=stable Ask, wait for move
		 					 SpreadStability = 0; // restart counter
		 					 StableBid = LastBidTradePrice; // store Current Bid (gap in Spread permitted!)
							 StableAsk = LastAskTradePrice; // store Current Ask (gap in Spread permitted!)
		 				 }
				}
			}

			// if the Spread is stable...
			if (BidSpreadState == 1) {//...on the Bid side
				if ( (TimeSales[TSIndex].Type == SC_TS_BID) && (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier < LastBidTradePrice) ) {
					//...AND the Trade was @Bid AND got lower
					BidSpreadState = 2; // 2=move happened, wait for come-back
					LastBidTradePrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier; // we have a new Current Bid
				}
			}

			if (AskSpreadState == 1) {//...or on the Ask side
				if ( (TimeSales[TSIndex].Type == SC_TS_ASK) && (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier > LastBidTradePrice) ) {
					//...AND the Trade was @Ask AND got higher
					AskSpreadState = 2; // 2=move happened, wait for come-back
					LastBidTradePrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier; // we have a new Current Ask
				}
			}


			// if the Stable Spread was knocked out on the Bid side...
			if (BidSpreadState == 2) {
				//...are we now trying to return to that Bid...
				if ( (TimeSales[TSIndex].Type == SC_TS_ASK) && (TimeSales[TSIndex].Volume >= (unsigned int)LargeTradeThreashold.GetInt()) ) {
					// ...by a large trade to the opposing Ask side
					BidSpreadState = 3; // 3=counter force tried (multiple times don't matter, one is enough)
					}
			}

			// if the Stable Spread was knocked out on the Ask side...
			if (AskSpreadState == 2) {
				//...are we now trying to return to that Ask...
				if ( (TimeSales[TSIndex].Type == SC_TS_BID) && (TimeSales[TSIndex].Volume >= (unsigned int)LargeTradeThreashold.GetInt()) ) {
					// ...by a large trade to the opposing Bid side
					AskSpreadState = 3; // 3=counter force tried (multiple times don't matter, one is enough)
					}
			}


			// did the force succeed yet...
			if (BidSpreadState == 3) {
					if ( (TimeSales[TSIndex].Type == SC_TS_BID) && (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier == StableBid) || //...on the Bid side...
						 (TimeSales[TSIndex].Type == SC_TS_ASK) && (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier == StableAsk)	) { //...or the Ask side
						 //if price is the same as before (Bid or Ask): Bid State 4: give alert!
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

						BidSpreadState = 0;//Let's start the count for Stable Spread again from scratch
					}
			}


			if (AskSpreadState == 3) {
				if ( (TimeSales[TSIndex].Type == SC_TS_BID) && (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier == StableBid) || //...on the Bid side...
					 (TimeSales[TSIndex].Type == SC_TS_ASK) && (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier == StableAsk)	) { //...or the Ask side
					 //if price is the same as before (Bid or Ask): Ask State 4: give alert!
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

						AskSpreadState = 0;//Let's start the count for Stable Spread again from scratch
				}
	 		}

			if (TimeSales[TSIndex].Type == SC_TS_BID) LastBidTradePrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
			else if (TimeSales[TSIndex].Type == SC_TS_ASK) LastAskTradePrice = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;	    	
	   
		}		
	}
	LastProcessedSequence = TimeSales[TimeSales.Size() - 1].Sequence;

	if (sc.LastCallToFunction) {
		for (int i = 0; i <= LineCounter; i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 5000000 + i);
		}
	}
}
