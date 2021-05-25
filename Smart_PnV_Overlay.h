#pragma once
#pragma once
#ifndef _WINDOWS_H_
#define _WINDOWS_H_
#endif

#ifndef _SIERRACHART_H_
#define _SIERRACHART_H_
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define  _CRT_SECURE_NO_WARNINGS
#endif


SCSFExport scsf_Smart_PnV_Overlay(SCStudyInterfaceRef sc)
{
	//int SGIndex = 0;
	SCSubgraphRef Peaks_1 = sc.Subgraph[0];
	SCSubgraphRef Valleys_1 = sc.Subgraph[1];
	SCSubgraphRef Peaks_2 = sc.Subgraph[2];
	SCSubgraphRef Valleys_2 = sc.Subgraph[3];
	SCSubgraphRef Peaks_3 = sc.Subgraph[4];
	SCSubgraphRef Valleys_3 = sc.Subgraph[5];
	SCSubgraphRef Peaks_4 = sc.Subgraph[6];
	SCSubgraphRef Valleys_4 = sc.Subgraph[7];

	//int InputIndex = 0;	
	SCInputRef PnF_Study_ID = sc.Input[0];
	SCInputRef Interval_Input = sc.Input[1];
	SCInputRef PeakGroup1Factor = sc.Input[2];
	SCInputRef PeakGroup2Factor = sc.Input[3];
	SCInputRef PeakGroup3Factor = sc.Input[4];
	SCInputRef PeakGroup4Factor = sc.Input[5];
	SCInputRef ValleyGroup1Factor = sc.Input[6];
	SCInputRef ValleyGroup2Factor = sc.Input[7];
	SCInputRef ValleyGroup3Factor = sc.Input[8];
	SCInputRef ValleyGroup4Factor = sc.Input[9];
	SCInputRef RangeToConsider = sc.Input[10];


	if (sc.SetDefaults)
	{
		sc.GraphName = "Smart_PnV_Overlay";

		sc.FreeDLL = 0;
		sc.AutoLoop = 0;
		sc.GraphRegion = 0;
		sc.DrawZeros = 0;
		//sc.IncludeInStudySummary = 1;

		Peaks_1.Name = "Peak Lines Group 1 (Largest Peaks)";
		Peaks_1.PrimaryColor = RGB(0, 255, 0);
		Peaks_1.DrawStyle = DRAWSTYLE_LINE;
		Peaks_1.LineStyle = LINESTYLE_SOLID;
		Peaks_1.LineWidth = 7;

		Valleys_1.Name = "Valley Lines Group 1 (Deapest Valleys)";
		Valleys_1.PrimaryColor = RGB(255, 0, 0);
		Valleys_1.DrawStyle = DRAWSTYLE_LINE;
		Valleys_1.LineStyle = LINESTYLE_SOLID;
		Valleys_1.LineWidth = 7;

		Peaks_2.Name = "Peak Lines Group 2";
		Peaks_2.PrimaryColor = RGB(0, 255, 0);
		Peaks_2.DrawStyle = DRAWSTYLE_LINE;
		Peaks_2.LineStyle = LINESTYLE_SOLID;
		Peaks_2.LineWidth = 5;

		Valleys_2.Name = "Valley Lines Group2";
		Valleys_2.PrimaryColor = RGB(255, 0, 0);
		Valleys_2.DrawStyle = DRAWSTYLE_LINE;
		Valleys_2.LineStyle = LINESTYLE_SOLID;
		Valleys_2.LineWidth = 5;

		Peaks_3.Name = "Peak Lines Group 3";
		Peaks_3.PrimaryColor = RGB(0, 255, 0);
		Peaks_3.DrawStyle = DRAWSTYLE_LINE;
		Peaks_3.LineStyle = LINESTYLE_SOLID;
		Peaks_3.LineWidth = 3;

		Valleys_3.Name = "Valley Lines Group 3";
		Valleys_3.PrimaryColor = RGB(255, 0, 0);
		Valleys_3.DrawStyle = DRAWSTYLE_LINE;
		Valleys_3.LineStyle = LINESTYLE_SOLID;
		Valleys_3.LineWidth = 3;

		Peaks_4.Name = "Peak Lines Group 4 (Smallest Peaks";
		Peaks_4.PrimaryColor = RGB(0, 255, 0);
		Peaks_4.DrawStyle = DRAWSTYLE_LINE;
		Peaks_4.LineStyle = LINESTYLE_SOLID;
		Peaks_4.LineWidth = 1;

		Valleys_4.Name = "Valley Lines Group 4 (Shallowest Valleys)";
		Valleys_4.PrimaryColor = RGB(255, 0, 0);
		Valleys_4.DrawStyle = DRAWSTYLE_LINE;
		Valleys_4.LineStyle = LINESTYLE_SOLID;
		Valleys_4.LineWidth = 1;
		
	

		PnF_Study_ID.Name = "Source Volume profile Study";//
		PnF_Study_ID.SetStudyID(1);

		Interval_Input.Name = "Function Interval in Seconds";
		Interval_Input.SetInt(10);

		PeakGroup1Factor.Name = "% of Peaks in Group 1 ( Peak with most volume)";
		PeakGroup1Factor.SetFloat(15);

		PeakGroup2Factor.Name = "% of Peaks in Group 2";
		PeakGroup2Factor.SetFloat(35);

		PeakGroup3Factor.Name = "% of Peaks in Group 3";
		PeakGroup3Factor.SetFloat(35);

		PeakGroup4Factor.Name = "% of Peaks in Group 4";
		PeakGroup4Factor.SetFloat(15);

		ValleyGroup1Factor.Name = "% of Valleys in Group 1 (Valleys with least volume)";
		ValleyGroup1Factor.SetFloat(15);

		ValleyGroup2Factor.Name = "% of Valleys in Group 2";
		ValleyGroup2Factor.SetFloat(35);

		ValleyGroup3Factor.Name = "% of Valleys in Group 3";
		ValleyGroup3Factor.SetFloat(35);

		ValleyGroup4Factor.Name = "% of Valleys in Group 4";
		ValleyGroup4Factor.SetFloat(15);

		RangeToConsider.Name = "Apply the Study to This Range ABove and Below Current Price (Points)";
		RangeToConsider.SetFloat(300);


		sc.Input[20].Name = "Target Chart Number";
		sc.Input[20].SetInt(0);

		sc.Input[21].Name = "Target Chart Number";
		sc.Input[21].SetInt(0);

		sc.Input[22].Name = "Target Chart Number";
		sc.Input[22].SetInt(0);

		sc.Input[23].Name = "Target Chart Number";
		sc.Input[23].SetInt(0);

		sc.Input[24].Name = "Target Chart Number";
		sc.Input[24].SetInt(0);

		sc.Input[25].Name = "Target Chart Number";
		sc.Input[25].SetInt(0);

		sc.Input[26].Name = "Target Chart Number";
		sc.Input[26].SetInt(0);

		sc.Input[27].Name = "Target Chart Number";
		sc.Input[27].SetInt(0);

		sc.Input[28].Name = "Target Chart Number";
		sc.Input[28].SetInt(1);

		sc.Input[29].Name = "Target Chart Number";
		sc.Input[29].SetInt(0);

		
		return;
	}


	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}

	if (sc.IsChartDataLoadingInChartbook()) {	
	//	sc.AddMessageToLog("Smart_PnV_Overlay: Charts Are Still LOading in Thos Chartbook", 0);
		return;
	}

	int& PreviousTime = sc.GetPersistentInt(0);
	int& LastPnVIndex = sc.GetPersistentInt(1);
	int& FirstCurrentTime = sc.GetPersistentInt(2);

	SCDateTime DTV;
	DTV = sc.CurrentSystemDateTime;
	int CurrentTime = DTV.GetTime();
	
	if (sc.UpdateStartIndex == 0) {
		SCDateTime FirstDTV;
		FirstDTV = sc.CurrentSystemDateTime;
		FirstCurrentTime = FirstDTV.GetTime();

		/*if (PeakGroup1Factor.GetFloat() + PeakGroup2Factor.GetFloat() + PeakGroup3Factor.GetFloat() + PeakGroup4Factor.GetFloat()  != 100) {
			MessageBox(NULL, L"Smart_PnV_Overlay: Sum of Peaks Groups % Should Be 100. Please Check!", L"Smart_PnV_Overlay Inputs Warning", MB_OK | MB_ICONINFORMATION);
		}

		if (ValleyGroup1Factor.GetFloat() + ValleyGroup2Factor.GetFloat() + ValleyGroup3Factor.GetFloat() + ValleyGroup4Factor.GetFloat() != 100) {
			MessageBox(NULL, L"Smart_PnV_Overlay: Sum of Valleys Groups % Should Be 100. Please Check!", L"Smart_PnV_Overlay Inputs Warning", MB_OK | MB_ICONINFORMATION);
		}*/

		if (PeakGroup1Factor.GetFloat() > 100) {
			PeakGroup1Factor.SetFloat(100); 
			PeakGroup2Factor.SetFloat(0);
			PeakGroup3Factor.SetFloat(0);
			PeakGroup4Factor.SetFloat(0);
		}
		else if (PeakGroup1Factor.GetFloat() + PeakGroup2Factor.GetFloat() > 100) {		
			PeakGroup2Factor.SetFloat(100 - PeakGroup1Factor.GetFloat());
			PeakGroup3Factor.SetFloat(0);
			PeakGroup4Factor.SetFloat(0);
		}
		else if (PeakGroup1Factor.GetFloat() + PeakGroup2Factor.GetFloat() + PeakGroup3Factor.GetFloat() > 100) {
			PeakGroup3Factor.SetFloat(100 - PeakGroup1Factor.GetFloat() - PeakGroup2Factor.GetFloat());
			PeakGroup4Factor.SetFloat(0);			
		}
		else if (PeakGroup1Factor.GetFloat() + PeakGroup2Factor.GetFloat() + PeakGroup3Factor.GetFloat() + PeakGroup4Factor.GetFloat() > 100) {
			PeakGroup4Factor.SetFloat(100 - PeakGroup1Factor.GetFloat() - PeakGroup2Factor.GetFloat() - PeakGroup3Factor.GetFloat());			
		}
		else if (PeakGroup1Factor.GetFloat() + PeakGroup2Factor.GetFloat() + PeakGroup3Factor.GetFloat() + PeakGroup4Factor.GetFloat() < 100) {
			PeakGroup4Factor.SetFloat(100 - PeakGroup1Factor.GetFloat() - PeakGroup2Factor.GetFloat() - PeakGroup3Factor.GetFloat());
		}


		if (ValleyGroup1Factor.GetFloat() > 100) {
			ValleyGroup1Factor.SetFloat(100);
			ValleyGroup2Factor.SetFloat(0);
			ValleyGroup3Factor.SetFloat(0);
			ValleyGroup4Factor.SetFloat(0);
		}
		else if (ValleyGroup1Factor.GetFloat() + ValleyGroup2Factor.GetFloat() > 100) {
			ValleyGroup2Factor.SetFloat(100 - ValleyGroup1Factor.GetFloat());
			ValleyGroup3Factor.SetFloat(0);
			ValleyGroup4Factor.SetFloat(0);
		}
		else if (ValleyGroup1Factor.GetFloat() + ValleyGroup2Factor.GetFloat() + ValleyGroup3Factor.GetFloat() > 100) {
			ValleyGroup3Factor.SetFloat(100 - ValleyGroup1Factor.GetFloat() - ValleyGroup2Factor.GetFloat());
			ValleyGroup4Factor.SetFloat(0);
		}
		else if (ValleyGroup1Factor.GetFloat() + ValleyGroup2Factor.GetFloat() + ValleyGroup3Factor.GetFloat() + ValleyGroup4Factor.GetFloat() > 100) {
			ValleyGroup4Factor.SetFloat(100 - ValleyGroup1Factor.GetFloat() - ValleyGroup2Factor.GetFloat() - ValleyGroup3Factor.GetFloat());
		}
		else if (ValleyGroup1Factor.GetFloat() + ValleyGroup2Factor.GetFloat() + ValleyGroup3Factor.GetFloat() + ValleyGroup4Factor.GetFloat() < 100) {
			ValleyGroup4Factor.SetFloat(100 - ValleyGroup1Factor.GetFloat() - ValleyGroup2Factor.GetFloat() - ValleyGroup3Factor.GetFloat());
		}

	}
	//if (CurrentTime - FirstCurrentTime < 600) return;
	

	// persistent ints 1000-1999 for Peaks   2000-2999 for valleys
	

	s_UseTool PeaksnValleys, PreviousPeaksnValleys;
	
	
	if (CurrentTime - PreviousTime >= Interval_Input.GetInt() || sc.UpdateStartIndex == 0) {
		
		// delete all previous lines
		for (int TargetChartCounter = 0; TargetChartCounter <= 9; TargetChartCounter++) {			
			for (int i = 0; i <= LastPnVIndex; i++) {				
				if (sc.GetPersistentInt(100 + TargetChartCounter) > 0) {					
					sc.DeleteUserDrawnACSDrawing(sc.GetPersistentInt(100 + TargetChartCounter), 50000000 + i);
				}
			}
		}	
		

		float PnVLinePrice = 0;
		int PnVType, PnVStartIndex, PnVEndIndex, PnVProfileIndex, PnVIndex;
		PnVProfileIndex = 0;
		PnVIndex = 0;
		int PeaksCounter = 0, ValleysCounter = 0;
		SCString str;
		s_VolumeAtPriceV2 VolumeAtPrice;

		//get lowest and highest prices of profile
		sc.GetVolumeAtPriceDataForStudyProfile
		(PnF_Study_ID.GetStudyID()
			, 0
			, 0
			, VolumeAtPrice
		);
		float LowestPriceOfProfile = (float)VolumeAtPrice.PriceInTicks * sc.TickSize;	

		/*sc.GetVolumeAtPriceDataForStudyProfile
		(PnF_Study_ID.GetStudyID()
			, sc.GetNumPriceLevelsForStudyProfile(PnF_Study_ID.GetInt(), PnVProfileIndex)
			, 0
			, VolumeAtPrice
		);
		float HighestPriceOfProfile = (float)VolumeAtPrice.PriceInTicks * sc.TickSize;*/

		// ============= Pass the PnVIndex of the lines that are in the range into the persistent arrays ======

		float LowestPriceOfRange = sc.Close[sc.ArraySize - 1] - RangeToConsider.GetFloat();
		float HighestPriceOfRange = sc.Close[sc.ArraySize - 1] + RangeToConsider.GetFloat();
		while (sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType,
			PnVStartIndex, PnVEndIndex, PnVProfileIndex, PnVIndex) != 0) {			
			if (PnVLinePrice >= LowestPriceOfRange && PnVLinePrice <= HighestPriceOfRange) {
				if (PnVType == 1) {//peaks
					sc.GetPersistentInt(1000 + PeaksCounter) = PnVIndex;
					PeaksCounter++;
				}
				else if (PnVType == 2) {//Valleys
					sc.GetPersistentInt(2000 + ValleysCounter) = PnVIndex;
					ValleysCounter++;
				}
			}

			PnVIndex++;
		}
		LastPnVIndex = PnVIndex;

		// ===============  Sort Peaks from most volume to least  ==============================
		
		for (int Counter1 = 0; Counter1 < PeaksCounter; Counter1++) {	
		

			for (int Counter2 = Counter1 + 1; Counter2 < PeaksCounter; Counter2++) {

				sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType,
					PnVStartIndex, PnVEndIndex, PnVProfileIndex, sc.GetPersistentInt(1000 + Counter1));

				sc.GetVolumeAtPriceDataForStudyProfile
				(PnF_Study_ID.GetStudyID()
					, 0
					, (int)((PnVLinePrice - LowestPriceOfProfile) / sc.TickSize)
					, VolumeAtPrice
				);

				int Volume1 = VolumeAtPrice.Volume;


				sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType,
					PnVStartIndex, PnVEndIndex, PnVProfileIndex, sc.GetPersistentInt(1000 + Counter2));


				sc.GetVolumeAtPriceDataForStudyProfile
				(PnF_Study_ID.GetStudyID()
					, 0
					, (int)((PnVLinePrice - LowestPriceOfProfile) / sc.TickSize)
					, VolumeAtPrice
				);

				int Volume2 = VolumeAtPrice.Volume;

				if (Volume2 > Volume1) {
					int Holder = sc.GetPersistentInt(1000 + Counter1);
					sc.GetPersistentInt(1000 + Counter1) = sc.GetPersistentInt(1000 + Counter2);
					sc.GetPersistentInt(1000 + Counter2) = Holder;
				}
			}
		}

		//============    Sort Valleys from least Ratio to largest ==================================== 
		// Ratio = Volume of valley / Volume of larger adjacent peak

		for (int Counter1 = 0; Counter1 < ValleysCounter; Counter1++) {

			for (int Counter2 = Counter1 + 1; Counter2 < ValleysCounter; Counter2++) {

				// ==== Get the price and volume counter1 valley ===============

				sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType,
					PnVStartIndex, PnVEndIndex, PnVProfileIndex, sc.GetPersistentInt(2000 + Counter1));

				sc.GetVolumeAtPriceDataForStudyProfile
				(PnF_Study_ID.GetStudyID()
					, 0
					, (int)((PnVLinePrice - LowestPriceOfProfile) / sc.TickSize)
					, VolumeAtPrice
				);
				float ValleyPrice = PnVLinePrice;
				int Volume1 = VolumeAtPrice.Volume;

				// ===== Find the volume of first peak above (iterate PnV lines from bottom to top) =====

				int AbovePeakVol = 0; int BelowPeakVol = 0;

				PnVIndex = 0;
				while (sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType, PnVStartIndex, PnVEndIndex, PnVProfileIndex, PnVIndex) != 0) {
					if (PnVType == 1 && PnVLinePrice > ValleyPrice) {
						sc.GetVolumeAtPriceDataForStudyProfile
						(PnF_Study_ID.GetStudyID()
							, 0
							, (int)((PnVLinePrice - LowestPriceOfProfile) / sc.TickSize)
							, VolumeAtPrice
						);
						AbovePeakVol = VolumeAtPrice.Volume;
						break;
					}
					PnVIndex++;
				}

				// Find the volume of first peak below (iterate PnV lines from to top bottom)

				for (int PnVIndex = ValleysCounter + PeaksCounter - 1; PnVIndex >= 0; PnVIndex--) {
					sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType,
						PnVStartIndex, PnVEndIndex, PnVProfileIndex, PnVIndex);
					if (PnVType == 1 && PnVLinePrice < ValleyPrice) {
						sc.GetVolumeAtPriceDataForStudyProfile
						(PnF_Study_ID.GetStudyID()
							, 0
							, (int)((PnVLinePrice - LowestPriceOfProfile) / sc.TickSize)
							, VolumeAtPrice
						);
						BelowPeakVol = VolumeAtPrice.Volume;
						break;
					}
				}

				int AdjacentPeakVol = 0;
				if (AbovePeakVol >= BelowPeakVol) AdjacentPeakVol = AbovePeakVol;
				else AdjacentPeakVol = BelowPeakVol;
				float Valley1Ratio = (float)Volume1 / (float)AdjacentPeakVol;

				// ==== Get the price and volume counter2 valley ===============

				sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType,
					PnVStartIndex, PnVEndIndex, PnVProfileIndex, sc.GetPersistentInt(2000 + Counter2));


				sc.GetVolumeAtPriceDataForStudyProfile
				(PnF_Study_ID.GetStudyID()
					, 0
					, (int)((PnVLinePrice - LowestPriceOfProfile) / sc.TickSize)
					, VolumeAtPrice
				);

				ValleyPrice = PnVLinePrice;
				int Volume2 = VolumeAtPrice.Volume;

				 AbovePeakVol = 0;  BelowPeakVol = 0;
				 // Find the volume of first peak above (iterate PnV lines from bottom to top)

				 AbovePeakVol = 0;  BelowPeakVol = 0;

				 PnVIndex = 0;
				 while (sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType, PnVStartIndex, PnVEndIndex, PnVProfileIndex, PnVIndex) != 0) {
					 if (PnVType == 1 && PnVLinePrice > ValleyPrice) {
						 sc.GetVolumeAtPriceDataForStudyProfile
						 (PnF_Study_ID.GetStudyID()
							 , 0
							 , (int)((PnVLinePrice - LowestPriceOfProfile) / sc.TickSize)
							 , VolumeAtPrice
						 );
						 AbovePeakVol = VolumeAtPrice.Volume;
						 break;
					 }
					 PnVIndex++;
				 }

				 // Find the volume of first peak below (iterate PnV lines from to top bottom)

				 for (int PnVIndex = ValleysCounter + PeaksCounter - 1; PnVIndex >= 0; PnVIndex--) {
					 sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType,
						 PnVStartIndex, PnVEndIndex, PnVProfileIndex, PnVIndex);
					 if (PnVType == 1 && PnVLinePrice < ValleyPrice) {
						 sc.GetVolumeAtPriceDataForStudyProfile
						 (PnF_Study_ID.GetStudyID()
							 , 0
							 , (int)((PnVLinePrice - LowestPriceOfProfile) / sc.TickSize)
							 , VolumeAtPrice
						 );
						 BelowPeakVol = VolumeAtPrice.Volume;
						 break;
					 }
				 }
				 AdjacentPeakVol = 0;
				if (AbovePeakVol >= BelowPeakVol) AdjacentPeakVol = AbovePeakVol;
				else AdjacentPeakVol = BelowPeakVol;
				float Valley2Ratio = (float)Volume2 / (float)AdjacentPeakVol;

				if (Valley2Ratio < Valley1Ratio) {
					int Holder = sc.GetPersistentInt(2000 + Counter1);
					sc.GetPersistentInt(2000 + Counter1) = sc.GetPersistentInt(2000 + Counter2);
					sc.GetPersistentInt(2000 + Counter2) = Holder;
				}
			}
		}

		// ==================== Draw Lines ============================================

		// ===================== Draw Peaks ============

		for (int i = 0; i < PeaksCounter; i++) {
			sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType,
				PnVStartIndex, PnVEndIndex, PnVProfileIndex, sc.GetPersistentInt(1000 + i));
			
			for (int TargetChartCounter = 0; TargetChartCounter <= 9; TargetChartCounter++) {
				if (sc.Input[20 + TargetChartCounter].GetInt() > 0) {

					PeaksnValleys.Clear();
					PeaksnValleys.AddAsUserDrawnDrawing = 1;
					PeaksnValleys.ChartNumber = sc.Input[20 + TargetChartCounter].GetInt();
					PeaksnValleys.LockDrawing = 1;
					PeaksnValleys.DrawingType = DRAWING_HORIZONTALLINE;
					PeaksnValleys.LineNumber = 50000000 + sc.GetPersistentInt(1000 + i);
					PeaksnValleys.AddMethod = UTAM_ADD_OR_ADJUST;
					if (((float)i / (PeaksCounter - 1)) * 100 <= PeakGroup1Factor.GetFloat()) {
						PeaksnValleys.Color = Peaks_1.PrimaryColor;
						PeaksnValleys.LineWidth = Peaks_1.LineWidth;
						PeaksnValleys.LineStyle = Peaks_1.LineStyle;
					}
					else if (((float)i / (PeaksCounter - 1)) * 100 <= PeakGroup1Factor.GetFloat() + PeakGroup2Factor.GetFloat()) {
						PeaksnValleys.Color = Peaks_2.PrimaryColor;
						PeaksnValleys.LineWidth = Peaks_2.LineWidth;
						PeaksnValleys.LineStyle = Peaks_2.LineStyle;

					}

					else if (((float)i / (PeaksCounter - 1)) * 100 <= PeakGroup1Factor.GetFloat() + PeakGroup2Factor.GetFloat() + PeakGroup3Factor.GetFloat()) {
						PeaksnValleys.Color = Peaks_3.PrimaryColor;
						PeaksnValleys.LineWidth = Peaks_3.LineWidth;
						PeaksnValleys.LineStyle = Peaks_3.LineStyle;

					}

					else  {
						PeaksnValleys.Color = Peaks_4.PrimaryColor;
						PeaksnValleys.LineWidth = Peaks_4.LineWidth;
						PeaksnValleys.LineStyle = Peaks_4.LineStyle;

					}
					PeaksnValleys.UseRelativeVerticalValues = 0;
					PeaksnValleys.BeginValue = PnVLinePrice;
					sc.UseTool(PeaksnValleys);
				}
			}
		}

		// ============= Draw Valleys ============================

		for (int i = 0; i < ValleysCounter; i++) {
			sc.GetStudyPeakValleyLine(sc.ChartNumber, PnF_Study_ID.GetInt(), PnVLinePrice, PnVType,
				PnVStartIndex, PnVEndIndex, PnVProfileIndex, sc.GetPersistentInt(2000 + i));

			for (int TargetChartCounter = 0; TargetChartCounter <= 9; TargetChartCounter++) {
				if (sc.Input[20 + TargetChartCounter].GetInt() > 0) {

					PeaksnValleys.Clear();
					PeaksnValleys.AddAsUserDrawnDrawing = 1;
					PeaksnValleys.ChartNumber = sc.Input[20 + TargetChartCounter].GetInt();
					PeaksnValleys.LockDrawing = 1;
					PeaksnValleys.DrawingType = DRAWING_HORIZONTALLINE;
					PeaksnValleys.LineNumber = 50000000 + sc.GetPersistentInt(2000 + i);
					PeaksnValleys.AddMethod = UTAM_ADD_OR_ADJUST;
					if (((float)i / (ValleysCounter - 1)) * 100 <= ValleyGroup1Factor.GetFloat()) {
						PeaksnValleys.Color = Valleys_1.PrimaryColor;
						PeaksnValleys.LineWidth = Valleys_1.LineWidth;
						PeaksnValleys.LineStyle = Valleys_1.LineStyle;
					}
					else if (((float)i / (ValleysCounter - 1)) * 100 <= ValleyGroup1Factor.GetFloat() + ValleyGroup2Factor.GetFloat()) {
						PeaksnValleys.Color = Valleys_2.PrimaryColor;
						PeaksnValleys.LineWidth = Valleys_2.LineWidth;
						PeaksnValleys.LineStyle = Valleys_2.LineStyle;

					}

					else if (((float)i / (ValleysCounter - 1)) * 100 <= ValleyGroup1Factor.GetFloat() + ValleyGroup2Factor.GetFloat() + ValleyGroup3Factor.GetFloat()) {
						PeaksnValleys.Color = Valleys_3.PrimaryColor;
						PeaksnValleys.LineWidth = Valleys_3.LineWidth;
						PeaksnValleys.LineStyle = Valleys_3.LineStyle;

					}

					else {
						PeaksnValleys.Color = Valleys_4.PrimaryColor;
						PeaksnValleys.LineWidth = Valleys_4.LineWidth;
						PeaksnValleys.LineStyle = Valleys_4.LineStyle;

					}
					PeaksnValleys.UseRelativeVerticalValues = 0;
					PeaksnValleys.BeginValue = PnVLinePrice;
					sc.UseTool(PeaksnValleys);
				}
			}
		}

		PreviousTime = CurrentTime;		
	}	
	

	for (int i = 0; i <= 9; i++) {
		sc.SetPersistentInt(100 + i, sc.Input[20 + i].GetInt());
	}
	
	

	if (sc.LastCallToFunction) {		
		for (int TargetChartCounter = 0; TargetChartCounter <= 9; TargetChartCounter++) {
			for (int i = 0; i <= LastPnVIndex; i++) {
				sc.DeleteUserDrawnACSDrawing(sc.Input[20 + TargetChartCounter].GetInt(), 50000000 + i);
			}
		}
	}	
}

