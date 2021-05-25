//&&&&&&&&&&&&&&
#pragma once
#ifndef _SIERRACHART_H_
#define _SIERRACHART_H_
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define  _CRT_SECURE_NO_WARNINGS
#endif


SCSFExport scsf_IceBerg_DEV(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	//SCSubgraphRef SgName = sc.Subgraph[SGIndex++];	

	int InputIndex = 0;
	SCInputRef LevelsToAvg = sc.Input[InputIndex++];
	SCInputRef MaxColumnLevels = sc.Input[InputIndex++];
	SCInputRef TicksAway = sc.Input[InputIndex++];
	SCInputRef TicksBeyond = sc.Input[InputIndex++];
	SCInputRef AbsorptionVolThreshold = sc.Input[InputIndex++];
	SCInputRef IceBergThreshold = sc.Input[InputIndex++];
	SCInputRef IceBergWithSRThreshold = sc.Input[InputIndex++];
	SCInputRef AbsAskColumnPosition = sc.Input[InputIndex++];
	SCInputRef AbsBidColumnPosition = sc.Input[InputIndex++];
	SCInputRef IcebergsAskColumnPosition = sc.Input[InputIndex++];
	SCInputRef IcebergsBidColumnPosition = sc.Input[InputIndex++];
	SCInputRef FontSize = sc.Input[InputIndex++];
	SCInputRef CumulatingAskTextColor = sc.Input[InputIndex++];
	SCInputRef CumulatingBidTextColor = sc.Input[InputIndex++];	
	SCInputRef ResetAskTextColor = sc.Input[InputIndex++];
	SCInputRef ResetBidTextColor = sc.Input[InputIndex++];
	SCInputRef AbsorptionTextColor = sc.Input[InputIndex++];
	SCInputRef AbsSuccessTextColor = sc.Input[InputIndex++];
	SCInputRef IceBergTextColor = sc.Input[InputIndex++];
	SCInputRef IceBergWithSRTextColor = sc.Input[InputIndex++];
	SCInputRef WantStackedSoundAlert = sc.Input[InputIndex++];
	SCInputRef BidStackedAlertNumber = sc.Input[InputIndex++];
	SCInputRef AskStackedAlertNumber = sc.Input[InputIndex++];
	

	if (sc.SetDefaults)
	{
		sc.GraphName = "IceBerg_DEV";
		sc.GraphRegion = 0;
		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		sc.UsesMarketDepthData = 1;
		sc.ReceivePointerEvents = ACS_RECEIVE_POINTER_EVENTS_ALWAYS;
		sc.MaintainVolumeAtPriceData = 1;
		//sc.UpdateAlways = 1;		

		MaxColumnLevels.Name = "Maximum Price Range For Columns (Points)";
		MaxColumnLevels.SetFloat(100);

		LevelsToAvg.Name = "How many DOM Levels to Average?";
		LevelsToAvg.SetInt(10);

		TicksAway.Name = "How Many Ticks Allowed to Distance From Iceberg Price - Holding Direction ";
		TicksAway.SetInt(7);

		TicksBeyond.Name = "How Many Ticks Allowed to Distance From Iceberg Price - Breach Direction";
		TicksBeyond.SetInt(5);	

		AbsorptionVolThreshold.Name = "Multiplier Of average depth for Absorption signal";
		AbsorptionVolThreshold.SetFloat(7);

		IceBergThreshold.Name = "Multiplier of average depth for Iceberg signal";
		IceBergThreshold.SetFloat(0.8);

		IceBergWithSRThreshold.Name = "Multiplier of average depth for Iceberg with Stop Run signal";
		IceBergWithSRThreshold.SetFloat(0.2);

		AbsAskColumnPosition.Name = "Ask Absorptions Column Position";
		AbsAskColumnPosition.SetInt(118);

		AbsBidColumnPosition.Name = "Bid Absorptions Column Position";
		AbsBidColumnPosition.SetInt(108);

		IcebergsAskColumnPosition.Name = "Ask Icebergs Column Position";
		IcebergsAskColumnPosition.SetInt(128);

		IcebergsBidColumnPosition.Name = "Bid Icebergs Column Position";
		IcebergsBidColumnPosition.SetInt(98);

		FontSize.Name = "FontSize";
		FontSize.SetInt(8);

		CumulatingAskTextColor.Name = "Color Of Ask Absorptions That Are Still Cumulating";
		CumulatingAskTextColor.SetColor(230, 0, 0);

		CumulatingBidTextColor.Name = "Color Of Bid Absorptions That Are Still Cumulating";
		CumulatingBidTextColor.SetColor(0, 200, 0);

		ResetAskTextColor.Name = "Color of ask volume text that was reset to zero";
		ResetAskTextColor.SetColor(150, 0, 0);

		ResetBidTextColor.Name = "Color of Bid volume text that was reset to zero";
		ResetBidTextColor.SetColor(0, 160, 0);

		AbsorptionTextColor.Name = "Absorption Text Color";
		AbsorptionTextColor.SetColor(205, 205, 0);

		AbsSuccessTextColor.Name = "Succesful Absorption Text Color";
		AbsSuccessTextColor.SetColor(166, 166, 0);

		IceBergTextColor.Name = "Iceberg Text Color";
		IceBergTextColor.SetColor(255, 255, 50);

		IceBergWithSRTextColor.Name = "Iceberg With Stop RunText Color";
		IceBergWithSRTextColor.SetColor(255, 0, 255);	

		WantStackedSoundAlert.Name = "Want IceBerg Sound Alerts?";
		WantStackedSoundAlert.SetYesNo(1);

		AskStackedAlertNumber.Name = "Ask IceBerg Sound Alert";
		AskStackedAlertNumber.SetInt(35);		

		BidStackedAlertNumber.Name = "Bid Iceberg Sound Alert";
		BidStackedAlertNumber.SetInt(36);

		return;
	}
	
	int64_t& LastProcessedSequence = sc.GetPersistentInt64(1);	

	int& OnlyOnce = sc.GetPersistentInt(49000);
	int& FirstLastBarIndex = sc.GetPersistentInt(49001); // this is the first bar that we analyze (the first last bar)	
	int& AskResetAdjustmentPriceToArray = sc.GetPersistentInt(49003);
	int& BidResetAdjustmentPriceToArray = sc.GetPersistentInt(49004);
	int& EndPrvBarAskAbsPriceToArray = sc.GetPersistentInt(49005);
	int& EndPrvBarBidAbsPriceToArray = sc.GetPersistentInt(49006);
	int& AskFlagsPriceToArray = sc.GetPersistentInt(49007);
	int& BidFlagsPriceToArray = sc.GetPersistentInt(49008);
	int& AskTradedLastCyclePriceToArray = sc.GetPersistentInt(49009);
	int& BidTradedLastCyclePriceToArray = sc.GetPersistentInt(49010);	
	int& AskDepthPriceToArray = sc.GetPersistentInt(49011);
	int& BidDepthPriceToArray = sc.GetPersistentInt(49012);
	int& IceBergCounter = sc.GetPersistentInt(49013);
	int& PreviousCycleIndex = sc.GetPersistentInt(49014);
	int& Reset_Abs_MenuID = sc.GetPersistentInt(49015);
	int& Reset_Icb_MenuID = sc.GetPersistentInt(49016);
	int& Reset_All_MenuID = sc.GetPersistentInt(49017);
	int& PreviousReplayStatus = sc.GetPersistentInt(49018);

	float& PreviousCycleHigh = sc.GetPersistentFloat(0);
	float& PreviousCycleLow = sc.GetPersistentFloat(1);
	float& LowestPriceToDelete = sc.GetPersistentFloat(2);
	float& HighestPriceToDelete = sc.GetPersistentFloat(3);
	float& PreviousAverageDepth = sc.GetPersistentFloat(4);
	
	

	int FirstMidOfPersArray = (int)(MaxColumnLevels.GetFloat() / sc.TickSize); // didn't devide by 2 because of directional days
	
	int PriceInTicks;
	int BarLevels;
	float AverageDepth;
	float PreviousBarLow = 0, PreviousBarHigh = 0;
	float CycleLow = 0, CycleHigh = 0;
	int NoNewTrades = 1;
	int CycleBidVolSum = 0, CycleAskVolSum = 0;

	s_VolumeAtPriceV2* p_VolumeAtPriceAtIndex;
	c_SCTimeAndSalesArray TimeSales;
	sc.GetTimeAndSales(TimeSales);

	s_MarketDepthEntry DepthEntry;

	s_UseTool AskAbs, BidAbs, AskIcb, BidIcb;		
	
	
	//====================== RESETS ============================================================

	if (Reset_Abs_MenuID <= 0) Reset_Abs_MenuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "Reset Absorptions Columns");
	if (Reset_Icb_MenuID <= 0) Reset_Icb_MenuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "Reset Iceberg Columns");
	if (Reset_All_MenuID <= 0) Reset_All_MenuID = sc.AddACSChartShortcutMenuItem(sc.ChartNumber, "Reset All Columns");

	if (OnlyOnce == 1) {
		if (sc.UpdateStartIndex == 0 ||
			sc.ReplayStatus == REPLAY_RUNNING && PreviousReplayStatus == REPLAY_STOPPED  ||
			sc.MenuEventID == Reset_All_MenuID ||
			HighestPriceToDelete - LowestPriceToDelete >= MaxColumnLevels.GetFloat()) {		

			// Delete columns
			for (int i = (int)(LowestPriceToDelete / sc.TickSize); i <= (int)(HighestPriceToDelete / sc.TickSize); i++) {
				sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1000000);
				sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1100000);
				sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3000000);
				sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3100000);
			}

			//Delete int persistent array
			for (int i = 0; i <= 48999; i++) {
				sc.GetPersistentInt(i) = 0;
			}
			
			AskResetAdjustmentPriceToArray = 0;
			BidResetAdjustmentPriceToArray = 0;
			EndPrvBarBidAbsPriceToArray = 0;
			AskFlagsPriceToArray = 0;
			BidFlagsPriceToArray = 0;
			AskTradedLastCyclePriceToArray = 0;
			BidTradedLastCyclePriceToArray = 0;
			IceBergCounter = 0;				
			PreviousCycleIndex = 0;			
			PreviousReplayStatus = 0;

			PreviousCycleHigh = 0;
			PreviousCycleLow = 0;
			LowestPriceToDelete = 0;
			HighestPriceToDelete = 0;
			PreviousAverageDepth = 0;			
			PreviousCycleHigh = 0;
			PreviousCycleLow = 0;
			
			OnlyOnce = 0;
		}

		else if (sc.MenuEventID == Reset_Abs_MenuID) {			

			//Delete relevant persistent int array entries
			for (int i = 0; i <= 12 * FirstMidOfPersArray; i++) {
				sc.GetPersistentInt(i) = 0;
			}
			for (int i = (int)(LowestPriceToDelete / sc.TickSize); i <= (int)(HighestPriceToDelete / sc.TickSize); i++) {
				sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1000000);
				sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1100000);

			}

			OnlyOnce = 0;
		}

		else if ((sc.MenuEventID == Reset_Icb_MenuID)) {			
			for (int i = 12 * FirstMidOfPersArray; i <= 20 * FirstMidOfPersArray; i++) {
				sc.GetPersistentInt(i) = 0;
			}
			for (int i = (int)(LowestPriceToDelete / sc.TickSize); i <= (int)(HighestPriceToDelete / sc.TickSize); i++) {
				sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3000000);
				sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3100000);
			}
			IceBergCounter = 0;			
		}
	}
	
	// ============================  ONLY ONCE ===========================================================

	if (OnlyOnce == 0) {		

		LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence;

		AskResetAdjustmentPriceToArray = (int)(sc.RoundToTickSize(sc.Ask) / sc.TickSize) - FirstMidOfPersArray;
		BidResetAdjustmentPriceToArray = (int)(sc.RoundToTickSize(sc.Bid) / sc.TickSize - (3 * FirstMidOfPersArray));
		EndPrvBarAskAbsPriceToArray = (int)(sc.RoundToTickSize(sc.Ask) / sc.TickSize) - (5 * FirstMidOfPersArray);
		EndPrvBarBidAbsPriceToArray = (int)(sc.RoundToTickSize(sc.Bid) / sc.TickSize - (7 * FirstMidOfPersArray));
		AskFlagsPriceToArray = (int)(sc.RoundToTickSize(sc.Ask) / sc.TickSize) - (9 * FirstMidOfPersArray);
		BidFlagsPriceToArray = (int)(sc.RoundToTickSize(sc.Bid) / sc.TickSize) - (11 * FirstMidOfPersArray);		
		AskDepthPriceToArray = (int)(sc.RoundToTickSize(sc.Ask) / sc.TickSize) - (13 * FirstMidOfPersArray);
		BidDepthPriceToArray = (int)(sc.RoundToTickSize(sc.Bid) / sc.TickSize) - (15 * FirstMidOfPersArray);
		AskTradedLastCyclePriceToArray = (int)(sc.RoundToTickSize(sc.Ask) / sc.TickSize) - (17 * FirstMidOfPersArray);
		BidTradedLastCyclePriceToArray = (int)(sc.RoundToTickSize(sc.Bid) / sc.TickSize) - (19 * FirstMidOfPersArray);
		

		FirstLastBarIndex = sc.ArraySize - 1;		
		BarLevels = (int)((sc.RoundToTickSize(sc.High[FirstLastBarIndex]) - sc.RoundToTickSize(sc.Low[FirstLastBarIndex])) / sc.TickSize) + 1;
		
		// Iterate through price levels of the current bar and save its values as negative
		for (int ElementIndex = 0; ElementIndex < BarLevels; ElementIndex++) {
			PriceInTicks = (int)((sc.RoundToTickSize(sc.Low[FirstLastBarIndex]) + (float)ElementIndex * sc.TickSize) / sc.TickSize);

			sc.VolumeAtPriceForBars->GetVAPElementAtIndex(FirstLastBarIndex, ElementIndex, &p_VolumeAtPriceAtIndex);

			sc.GetPersistentInt(PriceInTicks - EndPrvBarBidAbsPriceToArray) = -((int)p_VolumeAtPriceAtIndex->BidVolume );
			sc.GetPersistentInt(PriceInTicks - EndPrvBarAskAbsPriceToArray) = -((int)p_VolumeAtPriceAtIndex->AskVolume );		
		}

		float BidsSum = 0, AsksSum = 0, AsksAverage = 0, BidsAverage = 0;
		for (int Level = 1; Level < LevelsToAvg.GetInt(); Level++) {
			s_MarketDepthEntry DepthEntry;

			sc.GetBidMarketDepthEntryAtLevel(DepthEntry, Level);
			BidsSum += min(DepthEntry.Quantity, 200);			

			sc.GetAskMarketDepthEntryAtLevel(DepthEntry, Level);
			AsksSum += min(DepthEntry.Quantity,200);
			
		}

		AsksAverage = (float)AsksSum / (float)(LevelsToAvg.GetInt() - 1);
		BidsAverage = (float)BidsSum / (float)(LevelsToAvg.GetInt() - 1);

		AverageDepth = (AsksAverage + BidsAverage) / 2;
		PreviousAverageDepth = AverageDepth;
		PreviousAverageDepth = 200;
	
		HighestPriceToDelete = sc.RoundToTickSize(sc.Ask); // sc.High[sc.ArraySize - 1];
		LowestPriceToDelete = sc.RoundToTickSize(sc.Bid); // sc.Low[sc.ArraySize - 1];
		LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence;				

		OnlyOnce = 1;	
	}		
	

	// ================   NEW BAR -  update the EndPrvBar persistent vars
	else if (sc.ArraySize - 1 != PreviousCycleIndex) {	
		
		BarLevels = (int)((sc.RoundToTickSize(sc.High[PreviousCycleIndex]) - sc.RoundToTickSize(sc.Low[PreviousCycleIndex])) / sc.TickSize) + 1;

		// Iterate through price levels of the previous bar and add the volume values to the EndPrvBar array
		for (int ElementIndex = 0; ElementIndex < BarLevels; ElementIndex++) {
			PriceInTicks = (int)((sc.RoundToTickSize(sc.Low[PreviousCycleIndex]) + (float)ElementIndex * sc.TickSize) / sc.TickSize);

			sc.VolumeAtPriceForBars->GetVAPElementAtIndex(PreviousCycleIndex, ElementIndex, &p_VolumeAtPriceAtIndex);

			sc.GetPersistentInt(PriceInTicks - EndPrvBarBidAbsPriceToArray) += (p_VolumeAtPriceAtIndex->BidVolume + sc.GetPersistentInt(PriceInTicks - BidResetAdjustmentPriceToArray));
			sc.GetPersistentInt(PriceInTicks - BidResetAdjustmentPriceToArray) = 0;

			sc.GetPersistentInt(PriceInTicks - EndPrvBarAskAbsPriceToArray) += (p_VolumeAtPriceAtIndex->AskVolume + sc.GetPersistentInt(PriceInTicks - AskResetAdjustmentPriceToArray));
			sc.GetPersistentInt(PriceInTicks - AskResetAdjustmentPriceToArray) = 0;
		}
		CycleHigh = sc.RoundToTickSize(sc.High[sc.ArraySize - 1]);
		CycleLow = sc.RoundToTickSize(sc.Low[sc.ArraySize - 1]);
		if (CycleHigh > HighestPriceToDelete) HighestPriceToDelete = CycleHigh;
		if (CycleLow < LowestPriceToDelete) LowestPriceToDelete = CycleLow;
	}

	// ============== TnS - Get the highest and lowest prices processed this cycle	
	
	else if (LastProcessedSequence != 0) {		
		for (int TSIndex = 0; TSIndex < TimeSales.Size(); ++TSIndex) {
			if (TimeSales[TSIndex].Sequence <= LastProcessedSequence) {				
				continue;
			}
			if (CycleLow == 0) {
				CycleLow = sc.RoundToTickSize(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier);
				CycleHigh = sc.RoundToTickSize(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier);
				NoNewTrades = 0;
			}
			else {
				if (TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier > CycleHigh) CycleHigh = sc.RoundToTickSize(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier);
				else if (TimeSales[TSIndex].Price* sc.RealTimePriceMultiplier < CycleLow) CycleLow = sc.RoundToTickSize(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier);
			}			
			if (TimeSales[TSIndex].Type == SC_TS_ASK) {
				CycleAskVolSum += TimeSales[TSIndex].Volume;
				int AskTradePriceInTicks = (int)((sc.RoundToTickSize(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier) / sc.TickSize));
				sc.GetPersistentInt(AskTradePriceInTicks - AskTradedLastCyclePriceToArray) += TimeSales[TSIndex].Volume;
			}
			else if (TimeSales[TSIndex].Type == SC_TS_BID) {
				CycleBidVolSum += TimeSales[TSIndex].Volume;
				int BidTradePriceInTicks = (int)((sc.RoundToTickSize(TimeSales[TSIndex].Price * sc.RealTimePriceMultiplier) / sc.TickSize));
				sc.GetPersistentInt(BidTradePriceInTicks - BidTradedLastCyclePriceToArray) += TimeSales[TSIndex].Volume;

			}
		}

		
		if (CycleHigh + sc.TickSize > sc.RoundToTickSize(sc.High[sc.ArraySize - 1])) CycleHigh = sc.RoundToTickSize(sc.High[sc.ArraySize - 1]);
		else CycleHigh = sc.RoundToTickSize (CycleHigh + sc.TickSize);

		if (CycleLow - sc.TickSize < sc.RoundToTickSize(sc.Low[sc.ArraySize - 1])) CycleLow = sc.RoundToTickSize(sc.Low[sc.ArraySize - 1]);
		else CycleLow = sc.RoundToTickSize(CycleLow - sc.TickSize);
		
		if (CycleHigh != 0) {
			if (CycleHigh > HighestPriceToDelete) HighestPriceToDelete = CycleHigh;
		}
		if (CycleLow != 0) {
			if (CycleLow < LowestPriceToDelete) LowestPriceToDelete = CycleLow;
		}	

		LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence;
		
	}	
	// ======================================================================================================
	// ======================================================================================================	
	// ====================================================================================================== 	

	// ==============  UPDATE ABS ARRAYS every cycle (just the cyclelow to cyclehigh levels) ===============================

	if (NoNewTrades == 0) {		
		for (float Price = sc.RoundToTickSize(CycleLow); Price <= CycleHigh; Price += sc.TickSize) {
			PriceInTicks = (int)(Price / sc.TickSize);
			int ElementIndex = (int)((Price - sc.RoundToTickSize(sc.Low[sc.ArraySize - 1])) / sc.TickSize);

			sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.ArraySize - 1, ElementIndex, &p_VolumeAtPriceAtIndex);
			
			int BidAbsVolAtPrice = sc.GetPersistentInt(PriceInTicks - EndPrvBarBidAbsPriceToArray) + p_VolumeAtPriceAtIndex->BidVolume + sc.GetPersistentInt(PriceInTicks - BidResetAdjustmentPriceToArray);

			int AskAbsVolAtPrice = sc.GetPersistentInt(PriceInTicks - EndPrvBarAskAbsPriceToArray) + p_VolumeAtPriceAtIndex->AskVolume + sc.GetPersistentInt(PriceInTicks - AskResetAdjustmentPriceToArray);

			if (BidAbsVolAtPrice >= (int)(PreviousAverageDepth * AbsorptionVolThreshold.GetFloat())) {
				sc.GetPersistentInt(PriceInTicks - BidFlagsPriceToArray) = 5;
				
			}
			else sc.GetPersistentInt(PriceInTicks - BidFlagsPriceToArray) = 1;

			if (AskAbsVolAtPrice >= (int)(PreviousAverageDepth * AbsorptionVolThreshold.GetFloat())){
				sc.GetPersistentInt(PriceInTicks - AskFlagsPriceToArray) = 5;				
			}
			else sc.GetPersistentInt(PriceInTicks - AskFlagsPriceToArray) = 1;

		
			BidAbs.Clear();
			BidAbs.AddAsUserDrawnDrawing = 1;
			BidAbs.AllowSaveToChartbook = 0;
			BidAbs.ChartNumber = sc.ChartNumber;
			BidAbs.DrawingType = DRAWING_TEXT;
			BidAbs.LineNumber = PriceInTicks + 1100000;
			BidAbs.AddMethod = UTAM_ADD_OR_ADJUST;
			BidAbs.FontSize = FontSize.GetInt();
			if (sc.GetPersistentInt(PriceInTicks - BidFlagsPriceToArray) == 5)
				BidAbs.Color = AbsorptionTextColor.GetColor();
			else BidAbs.Color = CumulatingBidTextColor.GetColor();
			BidAbs.FontBold = 1;
			BidAbs.TextAlignment = DT_VCENTER | DT_LEFT;
			BidAbs.UseRelativeVerticalValues = 0;
			BidAbs.BeginDateTime = AbsBidColumnPosition.GetInt();
			BidAbs.BeginValue = Price;
			BidAbs.Text.Format("%i", BidAbsVolAtPrice);
			sc.UseTool(BidAbs);

			AskAbs.Clear();
			AskAbs.AddAsUserDrawnDrawing = 1;
			AskAbs.AllowSaveToChartbook = 0;
			AskAbs.ChartNumber = sc.ChartNumber;
			AskAbs.DrawingType = DRAWING_TEXT;
			AskAbs.LineNumber = PriceInTicks + 1000000;
			AskAbs.AddMethod = UTAM_ADD_OR_ADJUST;
			AskAbs.FontSize = FontSize.GetInt();
			if (sc.GetPersistentInt(PriceInTicks - AskFlagsPriceToArray) == 5)
				AskAbs.Color = AbsorptionTextColor.GetColor();
			else AskAbs.Color = CumulatingAskTextColor.GetColor();
			AskAbs.FontBold = 1;
			AskAbs.TextAlignment = DT_VCENTER | DT_LEFT;
			AskAbs.UseRelativeVerticalValues = 0;
			AskAbs.BeginDateTime = AbsAskColumnPosition.GetInt();
			AskAbs.BeginValue = Price;
			AskAbs.Text.Format("%i", AskAbsVolAtPrice);
			sc.UseTool(AskAbs);
			
			// ============    ICEBERGS ==================================
			// ============    ICEBERGS ==================================
			// ============    ICEBERGS ==================================
			
			int IceBergFlag = 0;

			// ================================  BID ICEBERG  =================================================
			if (Price >= sc.RoundToTickSize(sc.Ask)) {
				;			sc.GetBidMarketDepthEntryAtLevel(DepthEntry, ((sc.RoundToTickSize(sc.Bid) - Price) / sc.TickSize));
				int BidStack = DepthEntry.Quantity - sc.GetPersistentInt(PriceInTicks - BidDepthPriceToArray) + sc.GetPersistentInt(PriceInTicks - BidTradedLastCyclePriceToArray);


				if (BidStack >= IceBergThreshold.GetFloat() * PreviousAverageDepth &&
					((float)(BidAbsVolAtPrice) >= (PreviousAverageDepth * AbsorptionVolThreshold.GetFloat() / 2)))
					IceBergFlag = 1;

				if (BidStack >= IceBergWithSRThreshold.GetFloat() * PreviousAverageDepth &&
					(float)CycleBidVolSum >= PreviousAverageDepth * 0.8 &&
					(float)CycleAskVolSum <= PreviousAverageDepth * 0.2)
					IceBergFlag = 2;

				if (IceBergFlag > 0) {

					IceBergCounter++;					

					if (WantStackedSoundAlert.GetYesNo()) sc.SetAlert(BidStackedAlertNumber.GetInt());

					BidIcb.Clear();
					BidIcb.AddAsUserDrawnDrawing = 1;
					BidIcb.AllowSaveToChartbook = 0;
					BidIcb.ChartNumber = sc.ChartNumber;
					BidIcb.DrawingType = DRAWING_TEXT;
					BidIcb.LineNumber = PriceInTicks + 3000000;
					BidIcb.AddMethod = UTAM_ADD_OR_ADJUST;
					BidIcb.FontSize = FontSize.GetInt();
					if (IceBergFlag == 1)BidIcb.Color = IceBergTextColor.GetColor();
					else BidIcb.Color = IceBergWithSRTextColor.GetColor();
					BidIcb.FontBold = 1;
					BidIcb.TextAlignment = DT_VCENTER | DT_LEFT;
					BidIcb.UseRelativeVerticalValues = 0;
					BidIcb.BeginDateTime = IcebergsBidColumnPosition.GetInt();
					BidIcb.BeginValue = sc.RoundToTickSize(Price);
					BidIcb.Text.Format("%i_%i", IceBergCounter, BidStack);
					sc.UseTool(BidIcb);					
					
				}
			}
		

			IceBergFlag = 0; 
			// ================================  ASK ICEBERGS  =================================================
			if (Price <= sc.RoundToTickSize(sc.Bid)) {
				sc.GetAskMarketDepthEntryAtLevel(DepthEntry, (Price - (sc.RoundToTickSize(sc.Ask) / sc.TickSize)));
				int AskStack = DepthEntry.Quantity - sc.GetPersistentInt(PriceInTicks - AskDepthPriceToArray) + sc.GetPersistentInt(PriceInTicks - AskTradedLastCyclePriceToArray);

				if (AskStack >= IceBergThreshold.GetFloat() * PreviousAverageDepth &&
					(float)(AskAbsVolAtPrice) >= (PreviousAverageDepth * AbsorptionVolThreshold.GetFloat() / 2))
					IceBergFlag = 1;
				if (AskStack >= IceBergWithSRThreshold.GetFloat() * PreviousAverageDepth &&
					(float)CycleAskVolSum >= PreviousAverageDepth * 0.8 &&
					(float)CycleBidVolSum <= PreviousAverageDepth * 0.2)
					IceBergFlag = 2;

				if (IceBergFlag > 0) {

					IceBergCounter++;					

					if (WantStackedSoundAlert.GetYesNo()) sc.SetAlert(AskStackedAlertNumber.GetInt());

					AskIcb.Clear();
					AskIcb.AddAsUserDrawnDrawing = 1;
					AskIcb.AllowSaveToChartbook = 0;
					AskIcb.ChartNumber = sc.ChartNumber;
					AskIcb.DrawingType = DRAWING_TEXT;
					AskIcb.LineNumber = PriceInTicks + 3100000;
					AskIcb.AddMethod = UTAM_ADD_OR_ADJUST;
					AskIcb.FontSize = FontSize.GetInt();
					if (IceBergFlag == 1) AskIcb.Color = IceBergTextColor.GetColor();
					else AskIcb.Color = IceBergWithSRTextColor.GetColor();
					AskIcb.FontBold = 1;
					AskIcb.TextAlignment = DT_VCENTER | DT_LEFT;
					AskIcb.UseRelativeVerticalValues = 0;
					AskIcb.BeginDateTime = IcebergsAskColumnPosition.GetInt();
					AskIcb.BeginValue = sc.RoundToTickSize(Price);
					AskIcb.Text.Format("%i_%i", IceBergCounter, AskStack);
					sc.UseTool(AskIcb);
										
				}
			}
					

			//============ Update TicksBeyond/TicksAaway ========================

			int InCurrentBarRange = 0;
			if (Price > PreviousCycleHigh) {
				sc.GetPersistentInt(PriceInTicks - AskFlagsPriceToArray - TicksBeyond.GetInt()) = 2;			
				
				sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.ArraySize - 1, ElementIndex - TicksBeyond.GetInt(), &p_VolumeAtPriceAtIndex);		
				InCurrentBarRange = (Price - (float)TicksBeyond.GetInt() * sc.TickSize >= sc.RoundToTickSize(sc.Low[sc.ArraySize - 1]));
				
				sc.GetPersistentInt(PriceInTicks - AskResetAdjustmentPriceToArray - TicksBeyond.GetInt()) = -((int)p_VolumeAtPriceAtIndex->AskVolume * InCurrentBarRange + sc.GetPersistentInt(PriceInTicks - EndPrvBarAskAbsPriceToArray - TicksBeyond.GetInt()));
								

				if (sc.GetPersistentInt(PriceInTicks - BidFlagsPriceToArray - TicksAway.GetInt()) == 5) {
					sc.GetPersistentInt(PriceInTicks - BidFlagsPriceToArray - TicksAway.GetInt()) = 4;
					
				}
				else if(sc.GetPersistentInt(PriceInTicks - BidFlagsPriceToArray - TicksAway.GetInt()) != 4)sc.GetPersistentInt(PriceInTicks - BidFlagsPriceToArray - TicksAway.GetInt()) = 3;

				sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.ArraySize - 1, ElementIndex - TicksAway.GetInt(), &p_VolumeAtPriceAtIndex);

				InCurrentBarRange = (Price - (float)TicksAway.GetInt() * sc.TickSize >= sc.RoundToTickSize(sc.Low[sc.ArraySize - 1]));

				sc.GetPersistentInt(PriceInTicks - BidResetAdjustmentPriceToArray - TicksAway.GetInt()) = -((int)p_VolumeAtPriceAtIndex->BidVolume * InCurrentBarRange + sc.GetPersistentInt(PriceInTicks - EndPrvBarBidAbsPriceToArray - TicksAway.GetInt()));

				BidAbs.Clear();
				BidAbs.AddAsUserDrawnDrawing = 1;
				BidAbs.AllowSaveToChartbook = 0;
				BidAbs.ChartNumber = sc.ChartNumber;
				BidAbs.DrawingType = DRAWING_TEXT;
				BidAbs.LineNumber = PriceInTicks - TicksAway.GetInt() + 1100000;
				BidAbs.AddMethod = UTAM_ADD_OR_ADJUST;	
				if(sc.GetPersistentInt(PriceInTicks - BidFlagsPriceToArray - TicksAway.GetInt()) == 4)
				BidAbs.Color = AbsSuccessTextColor.GetColor();
				else BidAbs.Color = ResetBidTextColor.GetColor();
				sc.UseTool(BidAbs);

				AskAbs.Clear();
				AskAbs.AddAsUserDrawnDrawing = 1;
				AskAbs.AllowSaveToChartbook = 0;
				AskAbs.ChartNumber = sc.ChartNumber;
				AskAbs.DrawingType = DRAWING_TEXT;
				AskAbs.LineNumber = PriceInTicks - TicksBeyond.GetInt() + 1000000;
				AskAbs.AddMethod = UTAM_ADD_OR_ADJUST;				
				AskAbs.Color = ResetAskTextColor.GetColor();				
				sc.UseTool(AskAbs);
			}

			else if (Price < PreviousCycleLow) {
				sc.GetPersistentInt(PriceInTicks - BidFlagsPriceToArray + TicksBeyond.GetInt()) = 2;
				sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.ArraySize - 1, ElementIndex + TicksBeyond.GetInt(), &p_VolumeAtPriceAtIndex);

				InCurrentBarRange = (Price + (float)TicksBeyond.GetInt() * sc.TickSize <= sc.RoundToTickSize(sc.High[sc.ArraySize - 1]));

				sc.GetPersistentInt(PriceInTicks -BidResetAdjustmentPriceToArray + TicksBeyond.GetInt()) = -((int)p_VolumeAtPriceAtIndex->BidVolume * InCurrentBarRange + sc.GetPersistentInt(PriceInTicks - EndPrvBarBidAbsPriceToArray + TicksBeyond.GetInt()));

				if (sc.GetPersistentInt(PriceInTicks - AskFlagsPriceToArray + TicksAway.GetInt()) == 5) {
					sc.GetPersistentInt(PriceInTicks - AskFlagsPriceToArray + TicksAway.GetInt()) = 4;
				}
				else if(sc.GetPersistentInt(PriceInTicks - AskFlagsPriceToArray + TicksAway.GetInt()) != 4)sc.GetPersistentInt(PriceInTicks - AskFlagsPriceToArray + TicksAway.GetInt()) = 3;

				sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.ArraySize - 1, ElementIndex + TicksAway.GetInt(), &p_VolumeAtPriceAtIndex);

				InCurrentBarRange = (Price + (float)TicksAway.GetInt() * sc.TickSize <= sc.RoundToTickSize(sc.High[sc.ArraySize - 1]));
				
				sc.GetPersistentInt(PriceInTicks - AskResetAdjustmentPriceToArray + TicksAway.GetInt()) = -((int)p_VolumeAtPriceAtIndex->AskVolume * InCurrentBarRange + sc.GetPersistentInt(PriceInTicks - EndPrvBarAskAbsPriceToArray + TicksAway.GetInt()));


				BidAbs.Clear();
				BidAbs.AddAsUserDrawnDrawing = 1;
				BidAbs.AllowSaveToChartbook = 0;
				BidAbs.ChartNumber = sc.ChartNumber;
				BidAbs.DrawingType = DRAWING_TEXT;
				BidAbs.LineNumber = PriceInTicks + TicksBeyond.GetInt() + 1100000;
				BidAbs.AddMethod = UTAM_ADD_OR_ADJUST;				
				BidAbs.Color = ResetBidTextColor.GetColor();				
				sc.UseTool(BidAbs);

				AskAbs.Clear();
				AskAbs.AddAsUserDrawnDrawing = 1;
				AskAbs.AllowSaveToChartbook = 0;
				AskAbs.ChartNumber = sc.ChartNumber;
				AskAbs.DrawingType = DRAWING_TEXT;
				AskAbs.LineNumber = PriceInTicks + TicksAway.GetInt() + 1000000;
				AskAbs.AddMethod = UTAM_ADD_OR_ADJUST;	
				if (sc.GetPersistentInt(PriceInTicks - AskFlagsPriceToArray + TicksAway.GetInt()) == 4)
					AskAbs.Color = AbsSuccessTextColor.GetColor();
				else AskAbs.Color = ResetAskTextColor.GetColor();				
				sc.UseTool(AskAbs);
			}			
		}
	}	


	// ===========================================================================================
	// ===========================================================================================
	// =============== Calculate Average Depth ===================================================

	float BidsSum = 0, AsksSum = 0, AsksAverage = 0, BidsAverage = 0;
	for (int Level = 1; Level < LevelsToAvg.GetInt(); Level++) {	

		sc.GetBidMarketDepthEntryAtLevel(DepthEntry, Level);
		BidsSum += min(DepthEntry.Quantity, PreviousAverageDepth * 2);			

		sc.GetAskMarketDepthEntryAtLevel(DepthEntry, Level);
		AsksSum += min(DepthEntry.Quantity, PreviousAverageDepth * 2);		
	}

	AsksAverage = (float)AsksSum / (float)(LevelsToAvg.GetInt() - 1);
	BidsAverage = (float)BidsSum / (float)(LevelsToAvg.GetInt() - 1);

	AverageDepth = (AsksAverage + BidsAverage) / 2;
	

	// =========== Remember Depth Values for next cycle ===========================================

	for (int Level = 0; Level < LevelsToAvg.GetInt(); Level++) {
		s_MarketDepthEntry DepthEntry;

		sc.GetBidMarketDepthEntryAtLevel(DepthEntry, Level);
		sc.GetPersistentInt((int)(sc.RoundToTickSize(sc.Bid - (float)Level * sc.TickSize) / sc.TickSize) - BidDepthPriceToArray) = (int)DepthEntry.Quantity;		
		

		sc.GetAskMarketDepthEntryAtLevel(DepthEntry, Level);
		sc.GetPersistentInt((int)(sc.RoundToTickSize(sc.Ask + (float)Level * sc.TickSize) / sc.TickSize) - AskDepthPriceToArray ) = (int)DepthEntry.Quantity;
	}

	// iterate through cyclelow to cyclehigh and reset volatprice values them to zero for next cycle+
	for (float Price = CycleLow; Price <= CycleHigh; Price += sc.TickSize) {
		sc.GetPersistentInt((int)((Price / sc.TickSize) - BidTradedLastCyclePriceToArray)) = 0;
		sc.GetPersistentInt((int)((Price / sc.TickSize) - AskTradedLastCyclePriceToArray)) = 0;

	}

	// ============  UPDATE PERS VARS ===========================================

	PreviousCycleIndex = sc.ArraySize - 1;
	if(CycleHigh != 0) PreviousCycleHigh = CycleHigh;
	if (CycleLow!= 0)PreviousCycleLow = CycleLow;
	if(AverageDepth > 0) PreviousAverageDepth = AverageDepth;
	PreviousReplayStatus = sc.ReplayStatus;
	
	// ====================  LAST FUNCTION CALL ====================================

	if (sc.LastCallToFunction) {
		for (int i = (int)(LowestPriceToDelete / sc.TickSize); i <= (int)(HighestPriceToDelete / sc.TickSize); i++) {
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1000000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 1100000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3000000);
			sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, i + 3100000);
		}
		sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, Reset_Abs_MenuID);
		sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, Reset_Icb_MenuID);
		sc.RemoveACSChartShortcutMenuItem(sc.ChartNumber, Reset_All_MenuID);
		
	}
}


