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

SCSFExport scsf_Volume_Spike(SCStudyGraphRef sc)
{
	int SGIndex = 0;
	SCSubgraphRef V_Spike = sc.Subgraph[SGIndex++];
	SCSubgraphRef AskVol_Spike = sc.Subgraph[SGIndex++];
	SCSubgraphRef BidVol_Spike = sc.Subgraph[SGIndex++];
	SCSubgraphRef V_Spike_Extention_Line = sc.Subgraph[SGIndex++];

	int InputIndex = 0;
	SCInputRef V_SpikeType = sc.Input[InputIndex++];
	SCInputRef BarsBack = sc.Input[InputIndex++];
	SCInputRef Spike_Threshold_Percent = sc.Input[InputIndex++];
	SCInputRef Sound_Alert = sc.Input[InputIndex++];
	SCInputRef Alert_Number = sc.Input[InputIndex++];
	SCInputRef Extend_Line_From_Signal = sc.Input[InputIndex++];


	// Section 1 - Set the configuration variables and defaults
	if (sc.SetDefaults)
	{
		sc.GraphName = "Volume_Spike";

		// During development set this flag to 1, so the DLL can be rebuilt without restarting Sierra Chart. When deveBarsBacklopment is completed, set it to 0 to improve performance.
		sc.FreeDLL = 0;
		sc.AutoLoop = 1;
		sc.GraphRegion = 0;
		sc.DrawStudyUnderneathMainPriceGraph = 1;
		//sc.IncludeInStudySummary = 1;

		V_Spike.Name = "Volume_Spike";
		V_Spike.DrawStyle = DRAWSTYLE_TEXT;
		V_Spike.PrimaryColor = RGB(0, 0, 255);
		V_Spike.TextDrawStyleText = "X";
		V_Spike.LineWidth = 18;
		V_Spike.DrawZeros = false;

		AskVol_Spike.Name = "Ask Volume Spike";
		AskVol_Spike.DrawStyle = DRAWSTYLE_TEXT;
		AskVol_Spike.PrimaryColor = RGB(0, 255, 0);
		AskVol_Spike.TextDrawStyleText = "X";
		AskVol_Spike.LineWidth = 18;
		AskVol_Spike.DrawZeros = false;


		BidVol_Spike.Name = "Bid Volume Spike";
		BidVol_Spike.DrawStyle = DRAWSTYLE_TEXT;
		BidVol_Spike.PrimaryColor = RGB(255, 0, 0);
		BidVol_Spike.TextDrawStyleText = "X";
		BidVol_Spike.LineWidth = 18;
		BidVol_Spike.DrawZeros = false;


		V_SpikeType.Name = "Choose Volume_Spike Type";
		V_SpikeType.SetCustomInputStrings("Volume; Ask or Bid Volume;");
		V_SpikeType.SetCustomInputIndex(0);

		BarsBack.Name = "Number Of Bars Back for Average";
		BarsBack.SetInt(4);

		Spike_Threshold_Percent.Name = "Volume_Spike Threshold Percent";
		Spike_Threshold_Percent.SetInt(100);

		Sound_Alert.Name = "Want Sound Alert ?";
		Sound_Alert.SetYesNo(0);

		Alert_Number.Name = "Sound Alert Number";
		Alert_Number.SetInt(1);

		V_Spike_Extention_Line.Name = "Extention_Line";
		V_Spike_Extention_Line.DrawStyle = LINESTYLE_SOLID;
		V_Spike_Extention_Line.PrimaryColor = RGB(255, 255, 0);
		V_Spike_Extention_Line.LineWidth = 4;

		Extend_Line_From_Signal.Name = "Extend Horizontal Line From Signal?";
		Extend_Line_From_Signal.SetYesNo(0);

		return;
	}

	// Section 2 - Do data processing here

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}	

	//CreateDirectory(L"\Volume_Spike_Folder", NULL); // create the folder for the on bar signals if the folder doesn't exist
	
	SCString FileName;		

	
	int   VolSum = 0, AskSum = 0, BidSum = 0, DeltaSum = 0;
	int& PreviousIndex = sc.GetPersistentInt(1);
	int& LastSignalIndex = sc.GetPersistentInt(2);
	int& PreviousReplayStatus = sc.GetPersistentInt(3);
	int& RedrawFlag = sc.GetPersistentInt(4);
	float& VolAvg = sc.GetPersistentFloat(1);
	float& AskAvg = sc.GetPersistentFloat(2);
	float& BidAvg = sc.GetPersistentFloat(3);
	float& DeltaAvg = sc.GetPersistentFloat(4);
	float& LastSignalPrice = sc.GetPersistentFloat(5);
	SCString& PreviousChartName = sc.GetPersistentSCString(0);
	SCString& PreviousFileName = sc.GetPersistentSCString(1);

	// extract  BarPeriodType from sc.GetStudyName(0)
	SCString ccCode, barsPeriodType, ChartSymbol, Spike_Type;
	SCString thisName = sc.GetStudyName(0); // like ESM7 [CB] Flex Renko 32-31-1 #5 --but Continuous None gives no []
											//SCString str;
	SCString DateTimeString;
	ChartSymbol = sc.GetChartSymbol(sc.ChartNumber).GetChars();

	if (V_SpikeType.GetIndex() == 0) Spike_Type = "Volume";
	else if (V_SpikeType.GetIndex() == 1) Spike_Type = "Ask_Bid";
	else if (V_SpikeType.GetIndex() == 2) Spike_Type = "Delta";

	FileName.Format("Volume_Spike_Data_%s_%i_%i_%i.csv", Spike_Type.GetChars(), sc.ChartNumber, BarsBack.GetInt(), Spike_Threshold_Percent.GetInt());	

	if (sc.ReplayStatus == REPLAY_RUNNING && PreviousReplayStatus == REPLAY_STOPPED ||
		sc.ReplayStatus == REPLAY_STOPPED && PreviousReplayStatus == REPLAY_STOPPED && sc.GetStudyName(0) != PreviousChartName ||
		FileName != PreviousFileName
		)
	{
		remove(FileName); //remove the data file when replay starts.the replay will create the file from scratch		
	}
 
	if (sc.Index == 0 || sc.IsFullRecalculation) RedrawFlag = 1; 		

	if (LastSignalIndex != sc.Index && sc.Index == sc.ArraySize - 1) {
		if (RedrawFlag == 1) {   // ============  Read Signals from CSV and draw them ==============================================			
			float SignalPrice;
			long float SignalDateTime;
			using namespace std;
		
			ifstream ip2(FileName);			
			
			if (ip2.is_open())
			{			
				string PriceString;
				string DTString;
				string SpikeType;

				while (ip2.good()) {						
					getline(ip2, PriceString, ',');
					getline(ip2, DTString, ',');
					getline(ip2, SpikeType, '\n');

					if (PriceString != "" && DTString != "")
					{
						SignalPrice = stof(PriceString);
						SignalDateTime = stod(DTString);
					}
					if (SpikeType == "Volume") V_Spike_Extention_Line.PrimaryColor = V_Spike.PrimaryColor;
					else if (SpikeType == "AskSpike") V_Spike_Extention_Line.PrimaryColor = AskVol_Spike.PrimaryColor;
					else V_Spike_Extention_Line.PrimaryColor = BidVol_Spike.PrimaryColor;

					SCString str;

					V_Spike[sc.GetNearestMatchForSCDateTime(sc.ChartNumber, SignalDateTime)] = SignalPrice;
					if (Extend_Line_From_Signal.GetYesNo() == 1) {
						sc.AddLineUntilFutureIntersection
						(sc.GetNearestMatchForSCDateTime(sc.ChartNumber, SignalDateTime) // Index where to start drawing
							, 0 //V_SpikeType.GetIndex()  // LineIDForBar
							, SignalPrice // The price level of the line
							, V_Spike_Extention_Line.PrimaryColor
							, V_Spike_Extention_Line.LineWidth
							, V_Spike_Extention_Line.LineStyle
							, 0 //DisplayValueLabel.GetYesNo()
							, false //DisplayNameLabel // true/false
							, ""// "string" or string variable
						);
					}
				}
				ip2.close();
			}			
			RedrawFlag = 0;
		}


		if (V_SpikeType.GetIndex() == 0) { //If Volume V_Spike
			if (PreviousIndex != sc.Index) {
				for (int i = 1; i <= BarsBack.GetInt(); i++) {
					VolSum = VolSum + sc.Volume[sc.Index - i];
				}
				VolAvg = (float)VolSum / (float)BarsBack.GetInt();
			}
			float TrsldPass = 0;
			if ((float)sc.Volume[sc.Index] >= VolAvg * (1 + (float)Spike_Threshold_Percent.GetInt() / 100)) { 

				V_Spike[sc.Index] = sc.Close[sc.Index];
				LastSignalIndex = sc.Index;
				LastSignalPrice = sc.Close[sc.Index];
				if (Sound_Alert.GetYesNo() == 1) sc.SetAlert(Alert_Number.GetInt());
				if (Extend_Line_From_Signal.GetYesNo() == 1) {
					sc.AddLineUntilFutureIntersection
					(sc.Index // where to start drawing
						, 0 //V_SpikeType.GetIndex()  // LineIDForBar
						, sc.Close[sc.Index] // The price level of the line
						, V_Spike.PrimaryColor
						, V_Spike_Extention_Line.LineWidth
						, V_Spike_Extention_Line.LineStyle
						, 0 //DisplayValueLabel.GetYesNo()
						, false //DisplayNameLabel // true/false
						, ""// "string" or string variable
					);
				}
				// Save Signal to CSV

				std::ofstream file(FileName, std::ios::out | std::ios::app);
				if (!file) {
					SCString Buffer;
					Buffer.Format("Unable to open file - %s ", FileName);
					sc.AddMessageToLog(Buffer, 1);
				}

				SCString SignalDataString;
			
				SignalDataString.Format("%f,%lf,Volume\n", LastSignalPrice, sc.BaseDateTimeIn[LastSignalIndex]);

				file << SignalDataString;// << std::endl;

				file.close();
			}

		}
		else if (V_SpikeType.GetIndex() == 1) {//If Ask/BId V_Spike
			if (PreviousIndex != sc.Index) {
				for (int i = 1; i <= BarsBack.GetInt(); i++) {
					AskSum = AskSum + sc.AskVolume[sc.Index - i];
					BidSum = BidSum + sc.BidVolume[sc.Index - i];
				}
				AskAvg = (float)AskSum / (float)BarsBack.GetInt();
				BidAvg = (float)BidSum / (float)BarsBack.GetInt();
			}
			float TrsldPass = 0;
			if ((float)sc.AskVolume[sc.Index] >= AskAvg * (1 + (float)Spike_Threshold_Percent.GetInt() / 100)) {

				AskVol_Spike[sc.Index] = sc.Close[sc.Index];
				LastSignalIndex = sc.Index;
				LastSignalPrice = sc.Close[sc.Index];
				if (Sound_Alert.GetYesNo() == 1) sc.SetAlert(Alert_Number.GetInt());
				if (Extend_Line_From_Signal.GetYesNo() == 1) {
					sc.AddLineUntilFutureIntersection
					(sc.Index // where to start drawing
						, 0 //V_SpikeType.GetIndex()  // LineIDForBar
						, sc.Close[sc.Index] // The price level of the line
						, AskVol_Spike.PrimaryColor
						, V_Spike_Extention_Line.LineWidth
						, V_Spike_Extention_Line.LineStyle
						, 0 //DisplayValueLabel.GetYesNo()
						, false //DisplayNameLabel // true/false
						, ""// "string" or string variable
					);
				}
				// Save Signal to CSV

				std::ofstream file(FileName, std::ios::out | std::ios::app);
				if (!file) {
					SCString Buffer;
					Buffer.Format("Unable to open file - %s", FileName);
					sc.AddMessageToLog(Buffer, 1);
				}

				SCString SignalDataString;

				SignalDataString.Format("%f,%lf,AskSpike\n", LastSignalPrice, sc.BaseDateTimeIn[LastSignalIndex]);

				file << SignalDataString;// << std::endl;

				file.close();
			}

			if ((float)sc.BidVolume[sc.Index] >= BidAvg * (1 + (float)Spike_Threshold_Percent.GetInt() / 100)) {

				BidVol_Spike[sc.Index] = sc.Close[sc.Index];
				LastSignalIndex = sc.Index;
				LastSignalPrice = sc.Close[sc.Index];
				if (Sound_Alert.GetYesNo() == 1) sc.SetAlert(Alert_Number.GetInt());
				if (Extend_Line_From_Signal.GetYesNo() == 1) {
					sc.AddLineUntilFutureIntersection
					(sc.Index // where to start drawing
						, 0 //V_SpikeType.GetIndex()  // LineIDForBar
						, sc.Close[sc.Index] // The price level of the line
						, BidVol_Spike.PrimaryColor
						, V_Spike_Extention_Line.LineWidth
						, V_Spike_Extention_Line.LineStyle
						, 0 //DisplayValueLabel.GetYesNo()
						, false //DisplayNameLabel // true/false
						, ""// "string" or string variable
					);
				}
				// Save Signal to CSV

				std::ofstream file(FileName, std::ios::out | std::ios::app);
				if (!file) {
					SCString Buffer;
					Buffer.Format("Unable to open file - %s", FileName);
					sc.AddMessageToLog(Buffer, 1);
				}

				SCString SignalDataString;

				SignalDataString.Format("%f,%lf,BidSpike\n", LastSignalPrice, sc.BaseDateTimeIn[LastSignalIndex]);

				file << SignalDataString;// << std::endl;

				file.close();
			}
		}	
	}
	PreviousIndex = sc.Index;
	PreviousReplayStatus = sc.ReplayStatus;
	PreviousChartName = sc.GetStudyName(0);
	PreviousFileName = FileName;
	//if(sc.LastCallToFunction) RemoveDirectory(L"\Volume_Spike_Folder");
}

