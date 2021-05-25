#pragma once
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

SCSFExport CustomAbsorptionBarsBuildingFunction(SCCustomChartBarInterfaceRef ChartBarInterface)
{
	ChartBarInterface.StartNewBarFlag = 0;
	
	SCInputRef Input_Min_Bar_Range = ChartBarInterface.GetInput(0);
	SCInputRef Input_Max_Bar_Range = ChartBarInterface.GetInput(1);
	SCInputRef Input_Standart_Daviations = ChartBarInterface.GetInput(2);
	SCInputRef Input_Rounds = ChartBarInterface.GetInput(3);
	SCInputRef Input_Wait_For_Return = ChartBarInterface.GetInput(4);

	/*SCInputRef ResetTime1 = ChartBarInterface.GetInput(4);
	SCInputRef ResetTime2 = ChartBarInterface.GetInput(5);
	SCInputRef ResetTime3 = ChartBarInterface.GetInput(6);
	SCInputRef ResetTime4 = ChartBarInterface.GetInput(7);
	SCInputRef ResetTime5 = ChartBarInterface.GetInput(8);
	SCInputRef ResetTime6 = ChartBarInterface.GetInput(9);
	SCInputRef ResetTime7 = ChartBarInterface.GetInput(10);*/

	
	float& PreviousRange = ChartBarInterface.GetPersistentFloat(10);
	float& LargestBidVolPrice = ChartBarInterface.GetPersistentFloat(11);
	float& LargestAskVolPrice = ChartBarInterface.GetPersistentFloat(12);
	int& BarAskVol = ChartBarInterface.GetPersistentInt(10);
	int& BarbidVol = ChartBarInterface.GetPersistentInt(11);
	int& LargestAskVol = ChartBarInterface.GetPersistentInt(12);
	int& LargestBidVol = ChartBarInterface.GetPersistentInt(13);
	int& RoundsCounter = ChartBarInterface.GetPersistentInt(14);
	


	if (ChartBarInterface.IsFirstBarOfChart)
	{
		//reset persistents
		PreviousRange = 0;
		BarAskVol = 0;
		BarbidVol = 0;
		LargestBidVolPrice = 0;
		LargestAskVolPrice = 0;
		LargestAskVol = 0;
		LargestBidVol = 0;
		RoundsCounter = 0;
	}

	if (ChartBarInterface.IsDeterminingIfShouldStartNewBar)
	{
		float BarHigh = ChartBarInterface.GetChartBarValue(SC_HIGH, ChartBarInterface.CurrentBarIndex);
		float BarLow = ChartBarInterface.GetChartBarValue(SC_LOW, ChartBarInterface.CurrentBarIndex);
		float Range = BarHigh - BarLow;

		if (Range >= Input_Min_Bar_Range.GetFloat() && RoundsCounter == Input_Rounds.GetInt())
		{
			int  NewBarAskVolume = ChartBarInterface.GetChartBarValue(SC_ASKVOL, ChartBarInterface.CurrentBarIndex);
			int  NewBarBidVolume = ChartBarInterface.GetChartBarValue(SC_BIDVOL, ChartBarInterface.CurrentBarIndex);

			int VAPSizeAtBarIndex = ChartBarInterface.VolumeAtPriceForBars->GetSizeAtBarIndex(ChartBarInterface.CurrentBarIndex);
			float AverageAskVolumePerLevel = (float)NewBarAskVolume / (Range / ChartBarInterface.TickSize + 1);
			float AverageBidVolumePerLevel = (float)NewBarBidVolume / (Range / ChartBarInterface.TickSize + 1);

			float AskDifSum = 0, BidDifSum = 0, S_Ask = 0, S_Bid, SDV_Ask = 0, SDV_Bid = 0;

			s_VolumeAtPriceV2* p_VolumeAtPriceAtIndex;
			for (int VAPIndex = 0; VAPIndex < VAPSizeAtBarIndex; VAPIndex++)
			{
				ChartBarInterface.VolumeAtPriceForBars->GetVAPElementAtIndex(ChartBarInterface.CurrentBarIndex, VAPIndex, &p_VolumeAtPriceAtIndex);
				if (p_VolumeAtPriceAtIndex->AskVolume > LargestAskVol)
				{
					LargestAskVol = p_VolumeAtPriceAtIndex->AskVolume;
					LargestAskVolPrice = BarLow + VAPIndex * ChartBarInterface.TickSize;;
				}
				if (p_VolumeAtPriceAtIndex->BidVolume > LargestBidVol)
				{
					LargestBidVol = p_VolumeAtPriceAtIndex->BidVolume;
					LargestBidVolPrice = BarLow + VAPIndex * ChartBarInterface.TickSize;;
				}
				AskDifSum += pow((float)p_VolumeAtPriceAtIndex->AskVolume - AverageAskVolumePerLevel, 2);
				BidDifSum += pow((float)p_VolumeAtPriceAtIndex->BidVolume - AverageBidVolumePerLevel, 2);
			}

			S_Ask = AskDifSum / (Range / ChartBarInterface.TickSize + 1);
			S_Bid = BidDifSum / (Range / ChartBarInterface.TickSize + 1);
			SDV_Ask = (float)pow(S_Ask, 0.5);
			SDV_Bid = (float)pow(S_Bid, 0.5);
			float NumOfAsk_SDV = (LargestAskVol - AverageAskVolumePerLevel) / SDV_Ask;
			float NumOfBid_SDV = (LargestBidVol - AverageBidVolumePerLevel) / SDV_Bid;

			if (Range >= Input_Max_Bar_Range.GetFloat() ||
				((float)LargestAskVol > AverageAskVolumePerLevel + Input_Standart_Daviations.GetFloat() * SDV_Ask &&
				NumOfAsk_SDV > NumOfBid_SDV &&
				(Input_Wait_For_Return.GetYesNo() == 0 || ChartBarInterface.NewFileRecord.GetHigh() == LargestAskVolPrice)))
			{
				ChartBarInterface.StartNewBarFlag = 1;

				PreviousRange = 0;
				BarAskVol = 0;
				BarbidVol = 0;
				LargestBidVolPrice = 0;
				LargestAskVolPrice = 0;
				LargestAskVol = 0;
				LargestBidVol = 0;
				RoundsCounter = 0;
			}
			else if 
			(
				(float)LargestBidVol > AverageBidVolumePerLevel + Input_Standart_Daviations.GetFloat() * SDV_Bid &&
				(Input_Wait_For_Return.GetYesNo() == 0 || ChartBarInterface.NewFileRecord.GetLow() == LargestBidVolPrice)
			)
			{
				ChartBarInterface.StartNewBarFlag = 1;

				PreviousRange = 0;
				BarAskVol = 0;
				BarbidVol = 0;
				LargestBidVolPrice = 0;
				LargestAskVolPrice = 0;
				LargestAskVol = 0;
				LargestBidVol = 0;
				RoundsCounter = 0;

			}			
		}
		PreviousRange = Range;
		if (RoundsCounter == Input_Rounds.GetInt()) RoundsCounter = 0;
		RoundsCounter++;
		
	}

	if (ChartBarInterface.IsFinalProcessingAfterNewOrCurrentBar)
	{

	}
	//

	else if (ChartBarInterface.IsInsertFileRecordsProcessing)
	{

	}

	
}


