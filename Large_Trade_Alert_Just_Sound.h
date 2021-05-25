#pragma once
#ifndef _SIERRACHART_H_
#define _SIERRACHART_H_
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define  _CRT_SECURE_NO_WARNINGS
#endif


SCSFExport scsf_Large_Trade_Alert_Just_Sound(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	//SCSubgraphRef SgName = sc.Subgraph[SGIndex++];	

	int InputIndex = 0;
	SCInputRef Threshold_1 = sc.Input[InputIndex++];
	SCInputRef Threshold_2 = sc.Input[InputIndex++];
	SCInputRef Threshold_3 = sc.Input[InputIndex++];
	SCInputRef Threshold_1_Ask_AlertNumber = sc.Input[InputIndex++];
	SCInputRef Threshold_2_Ask_AlertNumber = sc.Input[InputIndex++];
	SCInputRef Threshold_3_Ask_AlertNumber = sc.Input[InputIndex++];
	SCInputRef Threshold_1_Bid_AlertNumber = sc.Input[InputIndex++];
	SCInputRef Threshold_2_Bid_AlertNumber = sc.Input[InputIndex++];
	SCInputRef Threshold_3_Bid_AlertNumber = sc.Input[InputIndex++];
	SCInputRef AlertsFilter = sc.Input[InputIndex++];

	


	if (sc.SetDefaults)
	{

		sc.GraphName = "Large_Trade_Alert_Just_Sound";
		sc.GraphRegion = 0;
		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		
		Threshold_1.Name = "Lowest threshold (contracts)";
		Threshold_1.SetInt(100);

		Threshold_2.Name = "Mid threshold (contracts)";
		Threshold_2.SetInt(200);

		Threshold_3.Name = "Highest threshold (contracts)";
		Threshold_3.SetInt(300);

		Threshold_1_Ask_AlertNumber.Name = "Sound alert number for lowest threshold - Ask trade";
		Threshold_1_Ask_AlertNumber.SetInt(1);

		Threshold_2_Ask_AlertNumber.Name = "Sound alert number for mid threshold  - Ask trade";
		Threshold_2_Ask_AlertNumber.SetInt(2);

		Threshold_3_Ask_AlertNumber.Name = "Sound alert number for highest threshold  - Ask trade";
		Threshold_3_Ask_AlertNumber.SetInt(3);

		Threshold_1_Bid_AlertNumber.Name = "Sound alert number for lowest threshold - Bid trade";
		Threshold_1_Bid_AlertNumber.SetInt(4);

		Threshold_2_Bid_AlertNumber.Name = "Sound alert number for mid threshold  - Bid trade";
		Threshold_2_Bid_AlertNumber.SetInt(5);

		Threshold_3_Bid_AlertNumber.Name = "Sound alert number for highest threshold  - Bid trade";
		Threshold_3_Bid_AlertNumber.SetInt(6);

		AlertsFilter.Name = "Which threshold whould you like sound alert to?";
		AlertsFilter.SetCustomInputStrings("All thresholds; Mid threshold and higher; Just highest threshold");
		AlertsFilter.SetCustomInputIndex(0);



		

		return;
	}

	int64_t& LastProcessedSequence = sc.GetPersistentInt64(1);

	int& OnlyOnce = sc.GetPersistentInt(0);

	c_SCTimeAndSalesArray TimeSales;
	sc.GetTimeAndSales(TimeSales);
	if (OnlyOnce == 0) {
		LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence;
		OnlyOnce = 1;
	}

	if (LastProcessedSequence != 0) {

		for (int TSIndex = 0; TSIndex < TimeSales.Size(); ++TSIndex) {
			if (TimeSales[TSIndex].Sequence <= LastProcessedSequence) continue;

			//  ===============   Process Ask Trades ====================================================================
			if (TimeSales[TSIndex].Type == SC_TS_ASK) {
				if (TimeSales[TSIndex].Volume >= Threshold_3.GetInt()) {
					sc.SetAlert(Threshold_3_Ask_AlertNumber.GetInt());
				}
				else if (TimeSales[TSIndex].Volume >= Threshold_2.GetInt() &&
					AlertsFilter.GetIndex() < 2) {
					sc.SetAlert(Threshold_2_Ask_AlertNumber.GetInt());
				}
				else if (TimeSales[TSIndex].Volume >= Threshold_1.GetInt() &&
					AlertsFilter.GetIndex() == 0) {
					sc.SetAlert(Threshold_1_Ask_AlertNumber.GetInt());
				}
			}

			else if (TimeSales[TSIndex].Type == SC_TS_BID) {
				if (TimeSales[TSIndex].Volume >= Threshold_3.GetInt()) {
					sc.SetAlert(Threshold_3_Bid_AlertNumber.GetInt());
				}
				else if (TimeSales[TSIndex].Volume >= Threshold_2.GetInt() &&
					AlertsFilter.GetIndex() < 2) {
					sc.SetAlert(Threshold_2_Bid_AlertNumber.GetInt());
				}
				else if (TimeSales[TSIndex].Volume >= Threshold_1.GetInt() &&
					AlertsFilter.GetIndex() == 0) {
					sc.SetAlert(Threshold_1_Bid_AlertNumber.GetInt());
				}

			}
		}
		LastProcessedSequence = (int)TimeSales[TimeSales.Size() - 1].Sequence;
	}

}