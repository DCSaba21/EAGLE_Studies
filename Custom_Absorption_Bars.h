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


SCSFExport scsf_CustomAbsorptionBars(SCStudyInterfaceRef sc)
{
	int SGIndex = 0;
	//SCSubgraphRef 

	int InputIndex = 0;

	SCInputRef Input_Min_Bar_Range = sc.Input[InputIndex++];
	SCInputRef Input_Max_Bar_Range = sc.Input[InputIndex++];
	SCInputRef Input_Standart_Daviations = sc.Input[InputIndex++];
	SCInputRef Input_Rounds = sc.Input[InputIndex++];
	SCInputRef Wait_For_Return = sc.Input[InputIndex++];
	/*SCInputRef ResetTime1 = sc.Input[InputIndex++];
	SCInputRef ResetTime2 = sc.Input[InputIndex++];
	SCInputRef ResetTime3 = sc.Input[InputIndex++];
	SCInputRef ResetTime4 = sc.Input[InputIndex++];
	SCInputRef ResetTime5 = sc.Input[InputIndex++];
	SCInputRef ResetTime6 = sc.Input[InputIndex++];
	SCInputRef ResetTime7 = sc.Input[InputIndex++];*/




	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphRegion = 0;
		sc.GraphName = "CustomAbsorptionBars";
		sc.UsesCustomChartBarFunction = 1;
		sc.FreeDLL = 0;
		sc.AutoLoop = 0;//Always use manual looping.
		sc.MaintainVolumeAtPriceData = 1;

		// This function is called from another thread.
		sc.fp_ACSCustomChartBarFunction = CustomAbsorptionBarsBuildingFunction;

		//sc.MaintainAdditionalChartDataArrays = 1;	


		Input_Min_Bar_Range.Name = "Minimum Bar Range (Points)";
		Input_Min_Bar_Range.SetFloat(5.0);

		Input_Max_Bar_Range.Name = "Maximum Bar Range (Points)";
		Input_Max_Bar_Range.SetFloat(10.0);

		Input_Standart_Daviations.Name = "Number_Of_Standatd_Deviations";
		Input_Standart_Daviations.SetFloat(2.0);

		Input_Rounds.Name = "Calculate every X rounds";
		Input_Rounds.SetInt(10);

		Wait_For_Return.Name = "Wait for return to high volume price?";
		Wait_For_Return.SetYesNo(1);

		/*ResetTime1.Name = "Reset time 1";
		ResetTime1.SetTime(HMS_TIME(0, 0, 0));

		ResetTime2.Name = "Reset time 2";
		ResetTime2.SetTime(HMS_TIME(2, 0, 0));

		ResetTime3.Name = "Reset time 3";
		ResetTime3.SetTime(HMS_TIME(11, 0, 0));

		ResetTime4.Name = "Reset time 4";
		ResetTime4.SetTime(HMS_TIME(11, 30, 0));

		ResetTime5.Name = "Reset time 5";
		ResetTime5.SetTime(HMS_TIME(13, 30, 0));

		ResetTime6.Name = "Reset time 6";
		ResetTime6.SetTime(HMS_TIME(15, 15, 0));

		ResetTime7.Name = "Reset time 7";
		ResetTime7.SetTime(HMS_TIME(16, 15, 0));*/

		return;
	}

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.UpdateStartIndex == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}

	int& r_ChartDataReloadedFlag = sc.GetPersistentInt(CUSTOM_CHART_BAR_RELOAD_FLAG_KEY);

	if (r_ChartDataReloadedFlag == 0)
	{
		sc.FlagToReloadChartData = true;
		r_ChartDataReloadedFlag = 1;
	}

	// It is necessary for the study function which creates custom chart bars to detect changes with its own input settings and flag to reload data.

	float MinBarRange = Input_Min_Bar_Range.GetFloat();
	float& r_PriorMinBarRange = sc.GetPersistentFloat(0);

	float MaxBarRange = Input_Max_Bar_Range.GetFloat();
	float& r_PriorMaxBarRange = sc.GetPersistentFloat(4);

	float StandartDaviations = Input_Standart_Daviations.GetFloat();
	float& r_PriorStandartDaviations = sc.GetPersistentFloat(1);

	int Rounds = Input_Rounds.GetInt();
	int& r_PriorRounds = sc.GetPersistentInt(2);

	int WaitForReturn = Wait_For_Return.GetYesNo();
	int& r_Prior_WaitForReturn = sc.GetPersistentInt(3);


	if (r_PriorMinBarRange != 0 && r_PriorMinBarRange != MinBarRange ||
		r_PriorMaxBarRange != 0 && r_PriorMaxBarRange != MaxBarRange ||
		r_PriorStandartDaviations != 0 && r_PriorStandartDaviations != StandartDaviations ||
		r_PriorRounds != 0 && r_PriorRounds != Rounds||
		r_Prior_WaitForReturn != WaitForReturn
		) sc.FlagToReloadChartData = true;

	r_PriorMinBarRange = MinBarRange;
	r_PriorMaxBarRange = MaxBarRange;
	r_PriorStandartDaviations = StandartDaviations;
	r_PriorRounds = Rounds;
	r_Prior_WaitForReturn = WaitForReturn;


	// Set the graph name for this custom bar type.
	if (sc.IsFullRecalculation)
	{
		sc.GraphName.Format("Custom Absorption Bars %.2f  %.2f", StandartDaviations, MinBarRange);
		
	}
}

