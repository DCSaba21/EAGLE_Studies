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


SCSFExport scsf_TickOnChartSource(SCStudyGraphRef sc)
{
	int InputIndex = 0;
	SCInputRef Threshold_1 = sc.Input[InputIndex++];
	SCInputRef Threshold_2 = sc.Input[InputIndex++];
	SCInputRef Threshold_3 = sc.Input[InputIndex++];
	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)

	{
		sc.GraphName = "TickOnChartSource";

		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When development is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		sc.AutoLoop = 1;  //Auto looping is enabled.
		sc.GraphRegion = 0;
		//sc.IncludeInStudySummary = 1;

		Threshold_1.Name = "Minimum TICK for First Threshold ";
		Threshold_1.SetInt(600);

		Threshold_2.Name = "Minimum TICK for Second Threshold ";
		Threshold_2.SetInt(800);

		Threshold_3.Name = "Minimum TICK for Third Threshold ";
		Threshold_3.SetInt(1000);

		return;
	}

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}
	if (sc.DLLNameUserServiceLevel > 0) return;

	// Section 2 - Do data processing here

	int& TickP1 = sc.GetPersistentInt(1);
	int& TickP2 = sc.GetPersistentInt(2);
	int& TickP3 = sc.GetPersistentInt(3);
	int& TickM1 = sc.GetPersistentInt(4);
	int& TickM2 = sc.GetPersistentInt(5);
	int& TickM3 = sc.GetPersistentInt(6);
	int& TickArraySize = sc.GetPersistentInt(7);
	int& PreviousIndex = sc.GetPersistentInt(8);
	int& Threshold1 = sc.GetPersistentInt(9);
	int& Threshold2 = sc.GetPersistentInt(10);
	int& Threshold3 = sc.GetPersistentInt(11);

	Threshold1 = Threshold_1.GetInt();
	Threshold2 = Threshold_2.GetInt();
	Threshold3 = Threshold_3.GetInt();


	TickArraySize = sc.ArraySize;

	if (PreviousIndex != sc.Index) {
		TickP1 = 0; TickP2 = 0; TickP3 = 0; TickM1 = 0; TickM2 = 0; TickM3 = 0;
	}

	if (sc.Index == sc.ArraySize - 1) {
		if (sc.Close[sc.Index] >= (float)Threshold1 && sc.Close[sc.Index] < (float)Threshold2 && TickP1 == 0) {
			TickP1 = 1;
		}
		else if (sc.Close[sc.Index] < (float)Threshold1)  TickP1 = 0;

		if (sc.Close[sc.Index] >= (float)Threshold2 && sc.Close[sc.Index] < (float)Threshold3 && TickP2 == 0) {
			TickP2 = 1;
		}
		else if (sc.Close[sc.Index] < (float)Threshold2)  TickP2 = 0;

		if (sc.Close[sc.Index] >= (float)Threshold3 && TickP3 == 0) {
			TickP3 = 1;
		}
		else if (sc.Close[sc.Index] < (float)Threshold3)  TickP3 = 0;


		if (sc.Close[sc.Index] <= -(float)Threshold1 && sc.Close[sc.Index] > -(float)Threshold2 && TickM1 == 0) {
			TickM1 = 1;
		}
		else if (sc.Close[sc.Index] > (float)Threshold1)  TickM1 = 0;

		if (sc.Close[sc.Index] <= -(float)Threshold2 && sc.Close[sc.Index] > -(float)Threshold3 && TickM2 == 0) {
			TickM2 = 1;
		}
		else if (sc.Close[sc.Index] > (float)Threshold2)  TickM2 = 0;

		if (sc.Close[sc.Index] <= -(float)Threshold3 && TickM3 == 0) {
			TickM3 = 1;
		}
		else if (sc.Close[sc.Index] > (float)Threshold3)  TickM3 = 0;
	}

	PreviousIndex = sc.Index;
}
