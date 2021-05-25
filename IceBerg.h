#pragma once
#ifndef _SIERRACHART_H_
#define _SIERRACHART_H_
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define  _CRT_SECURE_NO_WARNINGS
#endif


SCSFExport scsf_IceBerg(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	//SCSubgraphRef SgName = sc.Subgraph[SGIndex++];	

	int InputIndex = 0;
	SCInputRef LevelsToAvg = sc.Input[InputIndex++];
	SCInputRef Threshold = sc.Input[InputIndex++];	
	SCInputRef Threshold1 = sc.Input[InputIndex++];
	SCInputRef Threshold2 = sc.Input[InputIndex++];
	SCInputRef TicksAway = sc.Input[InputIndex++];
	SCInputRef TicksBeyond = sc.Input[InputIndex++];
	SCInputRef StillCumulatingAskTextColor = sc.Input[InputIndex++];
	SCInputRef StillCumulatingBidTextColor = sc.Input[InputIndex++];
	SCInputRef ResetAskTextColor = sc.Input[InputIndex++];
	SCInputRef ResetBidTextColor = sc.Input[InputIndex++];
	SCInputRef InitialIceBergTextColor = sc.Input[InputIndex++];
	SCInputRef SuccesfulIceBergTextColor = sc.Input[InputIndex++];
	SCInputRef IceBergWithStackingTextColor = sc.Input[InputIndex++];
	SCInputRef IceBergWithStopRunTextColor = sc.Input[InputIndex++];
	SCInputRef AskColumnPosition = sc.Input[InputIndex++];
	SCInputRef BidColumnPosition = sc.Input[InputIndex++];
	SCInputRef AskMemoryColumnPosition = sc.Input[InputIndex++];
	SCInputRef BidMemoryColumnPosition = sc.Input[InputIndex++];
	SCInputRef FontSize = sc.Input[InputIndex++];
	SCInputRef Want_PS_Sound_Alert = sc.Input[InputIndex++];
	SCInputRef AskPulledAlertNumber = sc.Input[InputIndex++];
	SCInputRef AskStackedAlertNumber = sc.Input[InputIndex++];
	SCInputRef BidPulledAlertNumber = sc.Input[InputIndex++];
	SCInputRef BidStackedAlertNumber = sc.Input[InputIndex++];
	SCInputRef L3MaxRange = sc.Input[InputIndex++];


	if (sc.SetDefaults)
	{

		sc.GraphName = "IceBerg";
		sc.GraphRegion = 0;
		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		sc.UsesMarketDepthData = 1;
		//sc.UpdateAlways = 1;

		LevelsToAvg.Name = "How many DOM levels to average?";
		LevelsToAvg.SetInt(10);

		Threshold.Name = "Multiplier Of average depth for Absorption signal";
		Threshold.SetFloat(8);		

		Threshold1.Name = "% of average depth for Iceberg signal";
		Threshold1.SetFloat(100);

		Threshold2.Name = "% of average depth for Iceberg with Stop Run signal";
		Threshold2.SetFloat(60);

		TicksAway.Name = "How many ticks allowed to distance from iceberg price - holding direction ";
		TicksAway.SetInt(7);

		TicksBeyond.Name = "How many ticks price allowed to breach the iceberg price";
		TicksBeyond.SetInt(5);

		StillCumulatingAskTextColor.Name = "Color of ask volume text that is still cumulating";
		StillCumulatingAskTextColor.SetColor(230, 0, 0);

		StillCumulatingBidTextColor.Name = "Color of bid volume text that is still cumulating";
		StillCumulatingBidTextColor.SetColor(0, 200, 0);

		ResetAskTextColor.Name = "Color of ask volume text that was reset to zero";
		ResetAskTextColor.SetColor(150, 0, 0);

		ResetBidTextColor.Name = "Color of Bid volume text that was reset to zero";
		ResetBidTextColor.SetColor(0, 160, 0);

		InitialIceBergTextColor.Name =  "Absorption Text Color";
		InitialIceBergTextColor.SetColor(205, 205, 0);

		SuccesfulIceBergTextColor.Name = "Succesful Absorption Text Color";
		SuccesfulIceBergTextColor.SetColor(166, 166, 0);

		IceBergWithStackingTextColor.Name = "IceBerg With Stacking Text Color ";
		IceBergWithStackingTextColor.SetColor(255, 255, 50);

		IceBergWithStopRunTextColor.Name = "IceBerg With Stop Run Text Color ";
		IceBergWithStopRunTextColor.SetColor(255, 0, 255);

		AskColumnPosition.Name = "Ask volumes column position";
		AskColumnPosition.SetInt(129);

		BidColumnPosition.Name = "Bid volumes column position";
		BidColumnPosition.SetInt(125);

		AskMemoryColumnPosition.Name = "Ask Iceberg Memory column position";
		AskMemoryColumnPosition.SetInt(138);

		BidMemoryColumnPosition.Name = "Bid Iceberg Memory column position";
		BidMemoryColumnPosition.SetInt(123);

		FontSize.Name = "Size of Fonts";
		FontSize.SetInt(8);

		Want_PS_Sound_Alert.Name = "Want Pull/Stack Sound Alerts?";
		Want_PS_Sound_Alert.SetYesNo(1);

		AskPulledAlertNumber.Name = "Not in use";
		AskPulledAlertNumber.SetInt(33);

		AskStackedAlertNumber.Name = "Ask IceBerg Sound Alert";
		AskStackedAlertNumber.SetInt(35);

		BidPulledAlertNumber.Name = "Not In Use";
		BidPulledAlertNumber.SetInt(34);

		BidStackedAlertNumber.Name = "Bid Iceberg Sound Alert";
		BidStackedAlertNumber.SetInt(36);

		L3MaxRange.Name = " Maximum range of L3 columns (Points)";
		L3MaxRange.SetFloat(100);


		return;
	}
	//FLAGS: 0 = nothing special, 1 = absorption, 2 = regular iceberg, 3 = succesful, 4 = iceberg + StopRun	

	int& OnlyOnce = sc.GetPersistentInt(40000);
	int& AskPriceToArray = sc.GetPersistentInt(40001);
	int& BidPriceToArray = sc.GetPersistentInt(40002);
	int& PreviousAskTradePersistentArrayIndex = sc.GetPersistentInt(40003);
	int& PreviousBidTradePersistentArrayIndex = sc.GetPersistentInt(40004);
	int& PreviousReplayStatus = sc.GetPersistentInt(40005);
	int& PreviousAskVolSum = sc.GetPersistentInt(40006);
	int& PreviousBidVolSum = sc.GetPersistentInt(40007);
	int& AskPullStackdPriceToArray = sc.GetPersistentInt(40008);
	int& BidPullStackdPriceToArray = sc.GetPersistentInt(40009);
	int& InitialAskIcbergPriceToArray = sc.GetPersistentInt(40010);
	int& InitialBidIcbergPriceToArray = sc.GetPersistentInt(40011);
	int& Reset_L3_MenuID = sc.GetPersistentInt(40012);
	int& IceBergMemoryAskPriceToArray = sc.GetPersistentInt(40013);
	int& IceBergMemoryBidPriceToArray = sc.GetPersistentInt(40014);
	int& Reset_L3_Mem_MenuID = sc.GetPersistentInt(40015);
	int& Reset_All_L3_MenuID = sc.GetPersistentInt(40016);
	int& PreviousAskPersistentArrayIndex = sc.GetPersistentInt(40017);
	int& PreviousBidPersistentArrayIndex = sc.GetPersistentInt(40018);
	int& AskIceBergCounterPriceToArray = sc.GetPersistentInt(40019);
	int& BidIceBergCounterPriceToArray = sc.GetPersistentInt(40020);



	float& HighestPriceForDelete = sc.GetPersistentFloat(0);
	float& LowestPriceForDelete = sc.GetPersistentFloat(1);
	float& HighestMemPriceForDelete = sc.GetPersistentFloat(2);
	float& LowestMemPriceForDelete = sc.GetPersistentFloat(3);
	float& PreviousAskPrice = sc.GetPersistentFloat(4);
	float& PreviousBidPrice = sc.GetPersistentFloat(5);
	float& PreviousAverageDepth = sc.GetPersistentFloat(6);

	int64_t& LastProcessedSequence = sc.GetPersistentInt64(1);

	s_UseTool AskVols, BidVols, BidVolsBeforeChange, AskVolsBeforeChange, MemoryAskVols, MemoryBidVols;

	c_SCTimeAndSalesArray TimeSales;
	sc.GetTimeAndSales(TimeSales);
	s_MarketDepthEntry DepthEntry;

	int Diff, PriceInTicks;
	float Price;

	if (Reset_L3_MenuID <= 0) Reset_L3_MenuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "Reset L3 + Absorption Columns");
	if (Reset_L3_Mem_MenuID <= 0) Reset_L3_Mem_MenuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "Reset Iceberg Columns");
	if (Reset_All_L3_MenuID <= 0) Reset_All_L3_MenuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "Reset All Columns");

	//Reset All Array entries to 0 and delete all text when replay starts or on manual reset
	int FirstMidOfPersArray = (int)(L3MaxRange.GetFloat() / sc.TickSize) / 2;

	if (sc.ReplayStatus == REPLAY_RUNNING && PreviousReplayStatus == REPLAY_STOPPED ||
		sc.MenuEventID == Reset_All_L3_MenuID ||
		HighestPriceForDelete - LowestPriceForDelete >= L3MaxRange.GetFloat()) {

		for (int i = 0; i <= 20 * FirstMidOfPersArray; i++) {
			sc.GetPersistentInt(i) = 0;
		}
		for (int i = (int)(LowestPriceForDelete / sc.TickSize); i <= (int)(HighestPriceForDelete / sc.TickSize); i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1000000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1100000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3000000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3100000);
		}

		PreviousAskVolSum = 0;
		PreviousBidVolSum = 0;
		OnlyOnce = 0;
		PreviousAskTradePersistentArrayIndex = 0;
		PreviousBidTradePersistentArrayIndex = 0;

	}

	else if (sc.MenuEventID != 0 && sc.MenuEventID == Reset_L3_MenuID) {
		for (int i = 0; i <= 12 * FirstMidOfPersArray; i++) {
			sc.GetPersistentInt(i) = 0;
		}
		for (int i = (int)(LowestPriceForDelete / sc.TickSize); i <= (int)(HighestPriceForDelete / sc.TickSize); i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1000000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1100000);

		}
		PreviousAskVolSum = 0;
		PreviousBidVolSum = 0;
		//OnlyOnce = 0;
		PreviousAskTradePersistentArrayIndex = 0;
		PreviousBidTradePersistentArrayIndex = 0;
		//AskPriceToArray = (int)(sc.Ask / sc.TickSize) - FirstMidOfPersArray;
		//BidPriceToArray = (int)(sc.Bid / sc.TickSize - (3 * FirstMidOfPersArray));
		//PullStackdPriceToArray = (int)(sc.Ask / sc.TickSize - (5 * FirstMidOfPersArray));
		//InitialAskIcbergPriceToArray = (int)(sc.Ask / sc.TickSize - (7 * FirstMidOfPersArray));
		//InitialBidIcbergPriceToArray = (int)(sc.Bid / sc.TickSize - (9 * FirstMidOfPersArray));
	}

	else if ((sc.MenuEventID != 0 && sc.MenuEventID == Reset_L3_Mem_MenuID)) {
		for (int i = 13 * FirstMidOfPersArray; i <= 20 * FirstMidOfPersArray; i++) {
			sc.GetPersistentInt(i) = 0;
		}
		for (int i = (int)(LowestMemPriceForDelete / sc.TickSize); i <= (int)(HighestMemPriceForDelete / sc.TickSize); i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3000000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3100000);
		}
		HighestMemPriceForDelete = sc.Ask;
		LowestMemPriceForDelete = sc.Bid;
	}


	if (OnlyOnce == 0) {
		LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence;
		AskPriceToArray = (int)(sc.Ask / sc.TickSize) - FirstMidOfPersArray;
		BidPriceToArray = (int)(sc.Bid / sc.TickSize - (3 * FirstMidOfPersArray));
		AskPullStackdPriceToArray = (int)(sc.Ask / sc.TickSize - (5 * FirstMidOfPersArray));
		BidPullStackdPriceToArray = (int)(sc.Ask / sc.TickSize - (7 * FirstMidOfPersArray));
		InitialAskIcbergPriceToArray = (int)(sc.Ask / sc.TickSize - (9 * FirstMidOfPersArray));
		InitialBidIcbergPriceToArray = (int)(sc.Bid / sc.TickSize - (11 * FirstMidOfPersArray));
		IceBergMemoryAskPriceToArray = (int)(sc.Ask / sc.TickSize - (13 * FirstMidOfPersArray));
		IceBergMemoryBidPriceToArray = (int)(sc.Bid / sc.TickSize - (15 * FirstMidOfPersArray));
		AskIceBergCounterPriceToArray = (int)(sc.Ask / sc.TickSize - (17 * FirstMidOfPersArray));
		BidIceBergCounterPriceToArray = (int)(sc.Bid / sc.TickSize - (19 * FirstMidOfPersArray));
		HighestPriceForDelete = sc.Ask;
		LowestPriceForDelete = sc.Bid;
		HighestMemPriceForDelete = sc.Ask;
		LowestMemPriceForDelete = sc.Bid;

		int BidsSum = 0, AsksSum = 0;
		for (int Level = 1; Level < LevelsToAvg.GetInt(); Level++)
		{		// count the latest DOM volumes Sums
			s_MarketDepthEntry DepthEntry;


			sc.GetBidMarketDepthEntryAtLevel(DepthEntry, Level);
			BidsSum += min(DepthEntry.Quantity, 200);

			sc.GetAskMarketDepthEntryAtLevel(DepthEntry, Level);
			AsksSum += min(DepthEntry.Quantity, 200);
		}

		float AsksAverage = (float)AsksSum / (float)(LevelsToAvg.GetInt() - 1);
		float BidsAverage = (float)BidsSum / (float)(LevelsToAvg.GetInt() - 1);

		BidsAverage = (AsksAverage + BidsAverage) / 2; //decided to use the average of both sides but left it open to reverse
		AsksAverage = BidsAverage;
		PreviousAverageDepth = AsksAverage;

		OnlyOnce = 1;
	}

	int BidsSum = 0, AsksSum = 0;
	for (int Level = 1; Level < LevelsToAvg.GetInt(); Level++)
	{		// count the latest DOM volumes Sums
		s_MarketDepthEntry DepthEntry;

		sc.GetBidMarketDepthEntryAtLevel(DepthEntry, Level);
		BidsSum += min(DepthEntry.Quantity, PreviousAverageDepth * 2);

		sc.GetAskMarketDepthEntryAtLevel(DepthEntry, Level);
		AsksSum += min(DepthEntry.Quantity, PreviousAverageDepth * 2);
	}

	float AsksAverage = (float)AsksSum / (float)(LevelsToAvg.GetInt() - 1);
	float BidsAverage = (float)BidsSum / (float)(LevelsToAvg.GetInt() - 1);

	BidsAverage = (AsksAverage + BidsAverage) / 2; //decided to use the average of both sides but left it open to reverse
	AsksAverage = BidsAverage;	

	

	// ===================================================================================================

	int ThisAskTradePersistentArrayIndex = 0, ThisBidTradePersistentArrayIndex = 0;
	int ThisAskIceBergFlagPersistentArrayIndex = 0;  int ThisBidIceBergFlagPersistentArrayIndex = 0;
	int ThisAskIceBergMemPersistentArrayIndex = 0;  int ThisBidIceBergMemPersistentArrayIndex = 0;
	int ThisAskIceBergCounterPriceToArrayIndex = 0, ThisBidIceBergCounterPriceToArrayIndex = 0;
	int AskVolsSum = 0, BidVolsSum = 0;
	int AskTradesCounter = 0, BidTradesCounter = 0;
	int CurrentPSAskPersistentArrayIndex = 0, CurrentPSBidPersistentArrayIndex = 0;

	float ThisCycleHighestAskPrice = 0, ThisCycleLowestAskPrice = 0, ThisCycleHighestBidPrice = 0, ThisCycleLowestBidPrice = 0;
	if (LastProcessedSequence != 0) {

		for (int TSIndex = 0; TSIndex < TimeSales.Size(); ++TSIndex) {
			if (TimeSales[TSIndex].Sequence <= LastProcessedSequence) continue;

			//  ===============   Process Ask Trades ====================================================================
			if (TimeSales[TSIndex].Type == SC_TS_ASK) {
				AskTradesCounter++;
				AskVolsSum += TimeSales[TSIndex].Volume;
				Price = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
				if (ThisCycleHighestAskPrice == 0) {
					ThisCycleHighestAskPrice = Price;
					ThisCycleLowestAskPrice = Price;
				}
				PriceInTicks = (int)(Price / sc.TickSize);
				ThisAskTradePersistentArrayIndex = PriceInTicks - AskPriceToArray;
				ThisAskIceBergFlagPersistentArrayIndex = PriceInTicks - InitialAskIcbergPriceToArray;
				ThisAskIceBergMemPersistentArrayIndex = PriceInTicks - IceBergMemoryAskPriceToArray;
				ThisAskIceBergCounterPriceToArrayIndex = PriceInTicks - AskIceBergCounterPriceToArray;
				CurrentPSAskPersistentArrayIndex = PriceInTicks - AskPullStackdPriceToArray;
				if (Price > ThisCycleHighestAskPrice) ThisCycleHighestAskPrice = Price;
				else if (Price < ThisCycleLowestAskPrice) ThisCycleLowestAskPrice = Price;
				if (Price > HighestPriceForDelete) HighestPriceForDelete = Price;

				sc.GetPersistentInt(ThisAskTradePersistentArrayIndex) += TimeSales[TSIndex].Volume;

				// Current Ask
				if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) == 3) sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) = 0;

				if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) != 1 &&
					(float)sc.GetAskMarketDepthStackPullValueAtPrice(Price) != 0 &&
					(float)sc.GetAskMarketDepthStackPullValueAtPrice(Price) >= sc.GetPersistentInt
					(CurrentPSAskPersistentArrayIndex) + (Threshold1.GetFloat() / 100) * PreviousAverageDepth )
				{
					if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) != 2 &&
						(float)sc.GetPersistentInt(ThisAskTradePersistentArrayIndex) >= PreviousAverageDepth * Threshold.GetFloat() / 2) {
						sc.GetPersistentInt(ThisAskIceBergMemPersistentArrayIndex) = sc.GetAskMarketDepthStackPullValueAtPrice(Price) - sc.GetPersistentInt(CurrentPSAskPersistentArrayIndex);
						sc.GetPersistentInt(ThisAskIceBergCounterPriceToArrayIndex)++;
						sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) = 2;
						if(Want_PS_Sound_Alert.GetYesNo()) sc.SetAlert(AskStackedAlertNumber.GetInt());
					}					
				}

				else if ((float)sc.GetPersistentInt(ThisAskTradePersistentArrayIndex) >= PreviousAverageDepth * Threshold.GetFloat()) {
					sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) = 1;
				}
				else if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) != 1) sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) = 0;

				// reached here with Csaba (15/11/2020)
				//TicksBeyond
				if (ThisAskTradePersistentArrayIndex > PreviousAskTradePersistentArrayIndex) {
					Diff = ThisAskTradePersistentArrayIndex - PreviousAskTradePersistentArrayIndex;
					for (int i = 1; i <= Diff; i++) {
						sc.GetPersistentInt(ThisAskTradePersistentArrayIndex - TicksBeyond.GetInt() - i) = 0;
						sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex - TicksBeyond.GetInt() - i) = 0;
					}
				}

				//TicksaWay
				else if (ThisAskTradePersistentArrayIndex < PreviousAskTradePersistentArrayIndex) {
					Diff = PreviousAskTradePersistentArrayIndex - ThisAskTradePersistentArrayIndex;
					for (int i = 1; i <= Diff; i++) {
						if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex + TicksAway.GetInt() + i) > 0) {
							if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex + TicksAway.GetInt() + i) != 3)
							{
								sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex + TicksAway.GetInt() + i) = 3;
							}
						}
						sc.GetPersistentInt(ThisAskTradePersistentArrayIndex + TicksAway.GetInt() + i) = 0;
					}
				}

				PreviousAskTradePersistentArrayIndex = ThisAskTradePersistentArrayIndex;
			}

			//  ===============   Process Bid Trades ====================================================================

			else if (TimeSales[TSIndex].Type == SC_TS_BID) {
				BidTradesCounter++;
				BidVolsSum += TimeSales[TSIndex].Volume;
				Price = TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier;
				if (ThisCycleHighestBidPrice == 0) {
					ThisCycleHighestBidPrice = Price;
					ThisCycleLowestBidPrice = Price;
				}
				PriceInTicks = (int)(Price / sc.TickSize);
				ThisBidTradePersistentArrayIndex = PriceInTicks - BidPriceToArray;
				ThisBidIceBergFlagPersistentArrayIndex = PriceInTicks - InitialBidIcbergPriceToArray;
				ThisBidIceBergMemPersistentArrayIndex = PriceInTicks - IceBergMemoryBidPriceToArray;
				ThisBidIceBergCounterPriceToArrayIndex = PriceInTicks - BidIceBergCounterPriceToArray;
				CurrentPSBidPersistentArrayIndex = PriceInTicks - BidPullStackdPriceToArray;
				if (Price > ThisCycleHighestBidPrice) ThisCycleHighestBidPrice = Price;
				else if (Price < ThisCycleLowestBidPrice) ThisCycleLowestBidPrice = Price;
				if (Price < LowestPriceForDelete) LowestPriceForDelete = Price;

				sc.GetPersistentInt(ThisBidTradePersistentArrayIndex) += TimeSales[TSIndex].Volume;

				// Current Bid
				if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) == 3) sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) = 0;

				if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) != 1 &&
					(float)sc.GetBidMarketDepthStackPullValueAtPrice(Price) != 0 &&
					(float)sc.GetBidMarketDepthStackPullValueAtPrice(Price) >= sc.GetPersistentInt
					(CurrentPSBidPersistentArrayIndex) + (Threshold1.GetFloat() / 100) * PreviousAverageDepth ) 
				{
					if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) != 2 &&
						(float)sc.GetPersistentInt(ThisBidTradePersistentArrayIndex) >= PreviousAverageDepth * Threshold.GetFloat() / 2) {
						sc.GetPersistentInt(ThisBidIceBergMemPersistentArrayIndex) = sc.GetBidMarketDepthStackPullValueAtPrice(Price) - sc.GetPersistentInt(CurrentPSBidPersistentArrayIndex);
						sc.GetPersistentInt(ThisBidIceBergCounterPriceToArrayIndex)++;
						sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) = 2;
						if (Want_PS_Sound_Alert.GetYesNo())sc.SetAlert(BidStackedAlertNumber.GetInt());
					}
					
				}

				else if ((float)sc.GetPersistentInt(ThisBidTradePersistentArrayIndex) >= PreviousAverageDepth * Threshold.GetFloat()) {
					sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) = 1;
				}
				else if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) != 1) sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) = 0;



				// TicksAway
				if (ThisBidTradePersistentArrayIndex > PreviousBidTradePersistentArrayIndex) {
					Diff = ThisBidTradePersistentArrayIndex - PreviousBidTradePersistentArrayIndex;
					for (int i = 1; i <= Diff; i++) {
						if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex - TicksAway.GetInt() - i) > 0) {
							if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex - TicksAway.GetInt() - i) != 3)
							{
								sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex - TicksAway.GetInt() - i) = 3;
							}
						}
						sc.GetPersistentInt(ThisBidTradePersistentArrayIndex - TicksAway.GetInt() - i) = 0;
					}
				}

				//TicksBeyond
				else if (ThisBidTradePersistentArrayIndex < PreviousBidTradePersistentArrayIndex) {
					Diff = PreviousBidTradePersistentArrayIndex - ThisBidTradePersistentArrayIndex;
					for (int i = 1; i <= Diff; i++) {
						sc.GetPersistentInt(ThisBidTradePersistentArrayIndex + TicksBeyond.GetInt() + i) = 0;
						sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex + TicksBeyond.GetInt() + i) = 0;
					}
				}

				PreviousBidTradePersistentArrayIndex = ThisBidTradePersistentArrayIndex;
			}
		}
		LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence;  		
	}

	if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) != 4 && 
		(float)sc.GetAskMarketDepthStackPullValueAtPrice(Price) != 0 &&
		(float)sc.GetAskMarketDepthStackPullValueAtPrice(Price) >= sc.GetPersistentInt
		(CurrentPSAskPersistentArrayIndex) +(Threshold2.GetFloat() / 100) * PreviousAverageDepth &&
		(float)AskVolsSum >= PreviousAverageDepth * 0.8 &&
		(float)BidVolsSum <= PreviousAverageDepth * 0.2) {
		sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) = 4;	
		if (Want_PS_Sound_Alert.GetYesNo())sc.SetAlert(AskStackedAlertNumber.GetInt());
	}

	if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) != 4 &&
		(float)sc.GetBidMarketDepthStackPullValueAtPrice(Price) != 0 &&
		(float)sc.GetBidMarketDepthStackPullValueAtPrice(Price) >= sc.GetPersistentInt
		(CurrentPSBidPersistentArrayIndex) + (Threshold2.GetFloat() / 100) * PreviousAverageDepth &&
		(float)BidVolsSum >= PreviousAverageDepth * 0.8 &&
		(float)AskVolsSum <= PreviousAverageDepth * 0.2) {
		sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) = 4;
		if (Want_PS_Sound_Alert.GetYesNo())sc.SetAlert(BidStackedAlertNumber.GetInt());
	
	}


	// =================  Drawings (Tools) 

	//Drawings ask side
	if (ThisCycleHighestAskPrice != 0) {
		int ThisAskPersistentArrayIndex;
		for (float AskPrice = ThisCycleLowestAskPrice; AskPrice <= ThisCycleHighestAskPrice; AskPrice += sc.TickSize) {
			PriceInTicks = (int)(AskPrice / sc.TickSize);
			ThisAskPersistentArrayIndex = PriceInTicks - AskPriceToArray;
			ThisAskIceBergFlagPersistentArrayIndex = PriceInTicks - InitialAskIcbergPriceToArray;
			ThisAskIceBergMemPersistentArrayIndex = PriceInTicks - IceBergMemoryAskPriceToArray;
			ThisAskIceBergCounterPriceToArrayIndex = PriceInTicks - AskIceBergCounterPriceToArray;		
		

			// ===============   Draw Ask Vols at current Ask

			AskVols.Clear();
			AskVols.AddAsUserDrawnDrawing = 1;
			AskVols.ChartNumber = sc.ChartNumber;
			AskVols.DrawingType = DRAWING_TEXT;
			AskVols.LineNumber = PriceInTicks + 1000000;
			AskVols.AddMethod = UTAM_ADD_OR_ADJUST;
			AskVols.FontSize = FontSize.GetInt();
			AskVols.FontBold = 1;

			if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) == 1) AskVols.Color = InitialIceBergTextColor.GetColor();
			else if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) == 2 ||
				sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) == 4) {

				if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) == 2) {
					AskVols.Color = IceBergWithStackingTextColor.GetColor();
				}
				else {
					AskVols.Color = IceBergWithStopRunTextColor.GetColor();
				}

				if (sc.GetPersistentInt(ThisAskIceBergMemPersistentArrayIndex) != 0) {
					MemoryAskVols.Clear();
					MemoryAskVols.AddAsUserDrawnDrawing = 1;
					MemoryAskVols.ChartNumber = sc.ChartNumber;
					MemoryAskVols.DrawingType = DRAWING_TEXT;
					MemoryAskVols.LineNumber = PriceInTicks + 3000000;
					MemoryAskVols.AddMethod = UTAM_ADD_OR_ADJUST;
					MemoryAskVols.FontSize = FontSize.GetInt();
					MemoryAskVols.FontBold = 1;
					if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) == 2) MemoryAskVols.Color = IceBergWithStackingTextColor.GetColor();
					else MemoryAskVols.Color = IceBergWithStopRunTextColor.GetColor();
					MemoryAskVols.TextAlignment = DT_VCENTER | DT_LEFT;
					MemoryAskVols.UseRelativeVerticalValues = 0;
					MemoryAskVols.BeginDateTime = AskMemoryColumnPosition.GetInt();
					MemoryAskVols.BeginValue = AskPrice;
					MemoryAskVols.Text.Format("%i_%i", sc.GetPersistentInt(ThisAskIceBergCounterPriceToArrayIndex), sc.GetPersistentInt(ThisAskIceBergMemPersistentArrayIndex));
					sc.UseTool(MemoryAskVols);
				}
			}
			else {
				AskVols.Color = StillCumulatingAskTextColor.GetColor();
				sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex) = 0;
			}

			AskVols.TextAlignment = DT_VCENTER | DT_LEFT;
			AskVols.UseRelativeVerticalValues = 0;
			AskVols.BeginDateTime = AskColumnPosition.GetInt();
			AskVols.BeginValue = AskPrice;
			AskVols.Text.Format("%i", sc.GetPersistentInt(ThisAskPersistentArrayIndex));
			sc.UseTool(AskVols);

			// =========== Change colors for succesful and succesful + P/S and Breached

			if (ThisAskPersistentArrayIndex > PreviousAskPersistentArrayIndex) {
				AskVols.Clear();
				AskVols.AddAsUserDrawnDrawing = 1;
				AskVols.ChartNumber = sc.ChartNumber;
				AskVols.DrawingType = DRAWING_TEXT;
				AskVols.LineNumber = PriceInTicks - TicksBeyond.GetInt() - 1 + 1000000;
				AskVols.AddMethod = UTAM_ADD_OR_ADJUST;
				AskVols.Color = ResetAskTextColor.GetColor();
				sc.UseTool(AskVols);
			}

			else if (ThisAskPersistentArrayIndex < PreviousAskPersistentArrayIndex) {
				AskVols.Clear();
				AskVols.AddAsUserDrawnDrawing = 1;
				AskVols.ChartNumber = sc.ChartNumber;
				AskVols.DrawingType = DRAWING_TEXT;
				AskVols.LineNumber = PriceInTicks + TicksAway.GetInt() + 1 + 1000000;
				AskVols.AddMethod = UTAM_ADD_OR_ADJUST;

				if (sc.GetPersistentInt(ThisAskIceBergFlagPersistentArrayIndex + TicksAway.GetInt() + 1) == 3) {
					AskVols.Color = SuccesfulIceBergTextColor.GetColor();
					sc.UseTool(AskVols);

					if (AskPrice + (TicksAway.GetInt() + 1) * sc.TickSize > HighestMemPriceForDelete) HighestMemPriceForDelete = AskPrice + (TicksAway.GetInt() + 1) * sc.TickSize;
					else if (AskPrice + (TicksAway.GetInt() + 1) * sc.TickSize < LowestMemPriceForDelete) LowestMemPriceForDelete = AskPrice + (TicksAway.GetInt() + 1) * sc.TickSize;
				}
				else {
					AskVols.Color = ResetAskTextColor.GetColor();
					sc.UseTool(AskVols);
				}
				//if (AskVols.BeginValue > HighestPriceForDelete) HighestPriceForDelete = AskVols.BeginValue;
			}

			PreviousAskPersistentArrayIndex = ThisAskPersistentArrayIndex;
		}
	}

	//Drawings Bid side

	if (ThisCycleHighestBidPrice != 0) {
		int ThisBidPersistentArrayIndex;
		for (float BidPrice = ThisCycleLowestBidPrice; BidPrice <= ThisCycleHighestBidPrice; BidPrice += sc.TickSize) {
			PriceInTicks = (int)(BidPrice / sc.TickSize);
			ThisBidPersistentArrayIndex = PriceInTicks - BidPriceToArray;
			ThisBidIceBergFlagPersistentArrayIndex = PriceInTicks - InitialBidIcbergPriceToArray;
			ThisBidIceBergMemPersistentArrayIndex = PriceInTicks - IceBergMemoryBidPriceToArray;
			ThisBidIceBergCounterPriceToArrayIndex = PriceInTicks - BidIceBergCounterPriceToArray;			

			// ===============   Draw Bid Vols at current Bid

			BidVols.Clear();
			BidVols.AddAsUserDrawnDrawing = 1;
			BidVols.ChartNumber = sc.ChartNumber;
			BidVols.DrawingType = DRAWING_TEXT;
			BidVols.LineNumber = PriceInTicks + 1100000;
			BidVols.AddMethod = UTAM_ADD_OR_ADJUST;
			BidVols.FontSize = FontSize.GetInt();
			BidVols.FontBold = 1;

			if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) == 1) BidVols.Color = InitialIceBergTextColor.GetColor();
			else if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) == 2 ||
				sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) == 4) {
				if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) == 2) {
					BidVols.Color = IceBergWithStackingTextColor.GetColor();
				}
				else {
					BidVols.Color = IceBergWithStopRunTextColor.GetColor();
				}

				if (sc.GetPersistentInt(ThisBidIceBergMemPersistentArrayIndex) != 0) {
					MemoryBidVols.Clear();
					MemoryBidVols.AddAsUserDrawnDrawing = 1;
					MemoryBidVols.ChartNumber = sc.ChartNumber;
					MemoryBidVols.DrawingType = DRAWING_TEXT;
					MemoryBidVols.LineNumber = PriceInTicks + 3100000;
					MemoryBidVols.AddMethod = UTAM_ADD_OR_ADJUST;
					MemoryBidVols.FontSize = FontSize.GetInt();
					MemoryBidVols.FontBold = 1;
					if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) == 2) MemoryBidVols.Color = IceBergWithStackingTextColor.GetColor();
					else MemoryBidVols.Color = IceBergWithStopRunTextColor.GetColor();
					MemoryBidVols.TextAlignment = DT_VCENTER | DT_LEFT;
					MemoryBidVols.UseRelativeVerticalValues = 0;
					MemoryBidVols.BeginDateTime = BidMemoryColumnPosition.GetInt();
					MemoryBidVols.BeginValue = BidPrice;
					MemoryBidVols.Text.Format("%i_%i", sc.GetPersistentInt(ThisBidIceBergCounterPriceToArrayIndex), sc.GetPersistentInt(ThisBidIceBergMemPersistentArrayIndex));
					sc.UseTool(MemoryBidVols);
				}
			}

			else {
				BidVols.Color = StillCumulatingBidTextColor.GetColor();
				sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex) = 0;
			}

			BidVols.TextAlignment = DT_VCENTER | DT_LEFT;
			BidVols.UseRelativeVerticalValues = 0;
			BidVols.BeginDateTime = BidColumnPosition.GetInt();
			BidVols.BeginValue = BidPrice;
			BidVols.Text.Format("%i", sc.GetPersistentInt(ThisBidPersistentArrayIndex));
			sc.UseTool(BidVols);

			// ============== Change colors for succesful and succesful + p/s and breached

			if (ThisBidPersistentArrayIndex > PreviousBidPersistentArrayIndex) {

				BidVols.Clear();
				BidVols.AddAsUserDrawnDrawing = 1;
				BidVols.ChartNumber = sc.ChartNumber;
				BidVols.DrawingType = DRAWING_TEXT;
				BidVols.LineNumber = PriceInTicks - TicksAway.GetInt() - 1 + 1100000;
				BidVols.AddMethod = UTAM_ADD_OR_ADJUST;

				if (sc.GetPersistentInt(ThisBidIceBergFlagPersistentArrayIndex - TicksAway.GetInt() - 1) == 3) {
					BidVols.Color = SuccesfulIceBergTextColor.GetColor();
					sc.UseTool(BidVols);

					if (BidPrice - (TicksAway.GetInt() + 1) * sc.TickSize > HighestMemPriceForDelete) HighestMemPriceForDelete = BidPrice - (TicksAway.GetInt() + 1) * sc.TickSize;
					else if (BidPrice - (TicksAway.GetInt() + 1) * sc.TickSize < LowestMemPriceForDelete) LowestMemPriceForDelete = BidPrice - (TicksAway.GetInt() + 1) * sc.TickSize;
				}
				else {
					BidVols.Color = ResetBidTextColor.GetColor();
					sc.UseTool(BidVols);
				}

				//if (BidVols.BeginValue < LowestPriceForDelete) LowestPriceForDelete = BidVols.BeginValue;
			}
			else if (ThisBidPersistentArrayIndex < PreviousBidPersistentArrayIndex) {
				BidVols.Clear();
				BidVols.AddAsUserDrawnDrawing = 1;
				BidVols.ChartNumber = sc.ChartNumber;
				BidVols.DrawingType = DRAWING_TEXT;
				BidVols.LineNumber = PriceInTicks + TicksBeyond.GetInt() + 1 + 1100000;
				BidVols.AddMethod = UTAM_ADD_OR_ADJUST;
				BidVols.Color = ResetBidTextColor.GetColor();
				sc.UseTool(BidVols);
			}
			PreviousBidPersistentArrayIndex = ThisBidPersistentArrayIndex;
		}
	}

	//  ==================    Pull/Stack Sound Alerts ==========================
	/*if (Want_PS_Sound_Alert.GetYesNo()) {
		for (int i = 0; i < LevelsToAvg.GetInt(); i++) {
			CurrentPSAskPersistentArrayIndex = (int)(sc.Ask / sc.TickSize) - AskPullStackdPriceToArray;
			CurrentPSBidPersistentArrayIndex = (int)(sc.Bid / sc.TickSize) - BidPullStackdPriceToArray;

			if ((float)sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + sc.TickSize * (float)i) != 0) {
				if ((float)sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + sc.TickSize * (float)i) >= sc.GetPersistentInt(CurrentPSAskPersistentArrayIndex + i) + (Threshold1.GetFloat() / 100) * PreviousAverageDepth)
					sc.SetAlert(AskStackedAlertNumber.GetInt());
				else if ((float)sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + sc.TickSize * (float)i) <= sc.GetPersistentInt(CurrentPSAskPersistentArrayIndex + i) - (Threshold1.GetFloat() / 100) * PreviousAverageDepth)
					sc.SetAlert(AskPulledAlertNumber.GetInt());
			}

			if ((float)sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - sc.TickSize * (float)i) != 0) {
				if ((float)sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - sc.TickSize * (float)i) >= sc.GetPersistentInt(CurrentPSBidPersistentArrayIndex - i) + (Threshold1.GetFloat() / 100) * PreviousAverageDepth)
					sc.SetAlert(BidStackedAlertNumber.GetInt());
				else if ((float)sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - sc.TickSize * (float)i) <= sc.GetPersistentInt(CurrentPSBidPersistentArrayIndex - i) - (Threshold1.GetFloat() / 100) * PreviousAverageDepth)
					sc.SetAlert(BidPulledAlertNumber.GetInt());
			}
		}
	}*/

	// ============   Remember PulStack  values for next function call ==================	
	CurrentPSAskPersistentArrayIndex = (int)(sc.Ask / sc.TickSize) - AskPullStackdPriceToArray;
	CurrentPSBidPersistentArrayIndex = (int)(sc.Bid / sc.TickSize) - BidPullStackdPriceToArray;
	for (int i = 0; i < 20; i++) {
		sc.GetPersistentInt(CurrentPSAskPersistentArrayIndex + i) = sc.GetAskMarketDepthStackPullValueAtPrice(sc.Ask + sc.TickSize * (float)i);
		sc.GetPersistentInt(CurrentPSBidPersistentArrayIndex - i) = sc.GetBidMarketDepthStackPullValueAtPrice(sc.Bid - sc.TickSize * (float)i);
	}


	PreviousReplayStatus = sc.ReplayStatus;
	PreviousAverageDepth = AsksAverage;


	if (sc.LastCallToFunction) {
		for (int i = (int)(LowestPriceForDelete / sc.TickSize); i <= (int)(HighestPriceForDelete / sc.TickSize); i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1000000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1100000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3000000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3100000);
		}
		sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, 4000000);
		sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, Reset_L3_MenuID);
	}
}

