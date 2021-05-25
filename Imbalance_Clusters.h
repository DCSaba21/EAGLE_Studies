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


SCSFExport scsf_Imbalance_Clusters(SCStudyInterfaceRef sc)
{
	const int MaxNumberOfClusters = 10;

	int SGIndex = 0;
	SCSubgraphRef BuyImbExtLine = sc.Subgraph[40];
	SCSubgraphRef SellImbExtLine = sc.Subgraph[41];


	int InputIndex = 0;
	SCInputRef MinImbalanceRatio = sc.Input[InputIndex++];
	SCInputRef MaxDist = sc.Input[InputIndex++];
	SCInputRef MinNumOfImb4Cluster = sc.Input[InputIndex++];
	SCInputRef Extend_Line_From_Signal = sc.Input[InputIndex++];
	SCInputRef Sound_Alert = sc.Input[InputIndex++];
	SCInputRef Buy_Cluster_Alert_Number = sc.Input[InputIndex++];
	SCInputRef Sell_Cluster_Alert_Number = sc.Input[InputIndex++];


	if (sc.SetDefaults)
	{
		sc.GraphName = "Imbalance_Clusters";

		sc.FreeDLL = 0;
		sc.AutoLoop = 1;
		sc.GraphRegion = 0;
		sc.DrawZeros = 0;
		sc.MaintainVolumeAtPriceData = 1;
		//sc.IncludeInStudySummary = 1;

		for (int i = 0; i <= 18; i += 2) {
			sc.Subgraph[i].Name = "Buy Imbalance Box Top";
			sc.Subgraph[i].DrawStyle = DRAWSTYLE_RIGHT_OFFSET_BOX_TOP;
			sc.Subgraph[i].PrimaryColor = RGB(0, 255, 0);
			sc.Subgraph[i].LineWidth = 2;
		}

		for (int i = 1; i <= 19; i += 2) {
			sc.Subgraph[i].Name = "Buy Imbalance Box  Bottom";
			sc.Subgraph[i].DrawStyle = DRAWSTYLE_RIGHT_OFFSET_BOX_BOTTOM;
			sc.Subgraph[i].PrimaryColor = RGB(0, 255, 0);
			sc.Subgraph[i].LineWidth = 2;
		}

		for (int i = 20; i <= 38; i += 2) {
			sc.Subgraph[i].Name = "Sell Imbalance Box Top";
			sc.Subgraph[i].DrawStyle = DRAWSTYLE_LEFT_OFFSET_BOX_TOP;
			sc.Subgraph[i].PrimaryColor = RGB(255, 0, 0);
			sc.Subgraph[i].LineWidth = 2;
		}

		for (int i = 21; i <= 39; i += 2) {
			sc.Subgraph[i].Name = "Sell Imbalance Box  Bottom";
			sc.Subgraph[i].DrawStyle = DRAWSTYLE_LEFT_OFFSET_BOX_BOTTOM;
			sc.Subgraph[i].PrimaryColor = RGB(255, 0, 0);
			sc.Subgraph[i].LineWidth = 2;
		}

		BuyImbExtLine.Name = "Buy Imbalace Clusters Extention_Line";
		BuyImbExtLine.DrawStyle = LINESTYLE_DOT;
		BuyImbExtLine.PrimaryColor = RGB(0, 255, 0);
		BuyImbExtLine.LineWidth = 2;

		SellImbExtLine.Name = "Sell Imbalace Clusters Extention_Line";
		SellImbExtLine.DrawStyle = LINESTYLE_DOT;
		SellImbExtLine.PrimaryColor = RGB(255, 0, 0);
		SellImbExtLine.LineWidth = 2;


		MinImbalanceRatio.Name = "Minimum Imbalance Ratio";
		MinImbalanceRatio.SetFloat(3);

		MaxDist.Name = "Maximum Distance between adjacent Imbalances (Ticks)";
		MaxDist.SetInt(2);

		MinNumOfImb4Cluster.Name = "Minimum Imbalaces For Drawing a Cluster";
		MinNumOfImb4Cluster.SetInt(2);

		Extend_Line_From_Signal.Name = "Extend Horizontal Line From Signal?";
		Extend_Line_From_Signal.SetYesNo(0);

		Sound_Alert.Name = "Want Sound Alert ?";
		Sound_Alert.SetYesNo(0);

		Buy_Cluster_Alert_Number.Name = "Buy Cluster Sound Alert Number";
		Buy_Cluster_Alert_Number.SetInt(1);

		Sell_Cluster_Alert_Number.Name = "Sell Cluster Sound Alert Number";
		Sell_Cluster_Alert_Number.SetInt(1);

		return;
	}

	if (sc.IsUserAllowedForSCDLLName == false) {
		if (sc.Index == 0) {
			sc.AddMessageToLog("You are not allowed to use this study", 1);
		}
		return;
	}
	if (sc.DLLNameUserServiceLevel > 0 && sc.DLLNameUserServiceLevel != 10) return;

	SCString str;

	int& PersistBuyClusterCounter = sc.GetPersistentInt(1);
	int& PersistSellClusterCounter = sc.GetPersistentInt(2);
	int& TotalBarBuyClustersCounter = sc.GetPersistentInt(3); // counter of all buy clusters that happened during the bar
	int& TotalBarSellClustersCounter = sc.GetPersistentInt(4); // counter of all sell clusters that happened during the bar
	int& PreviousIndex = sc.GetPersistentInt(5);

	/* PersistentFloat 1-40 are used for remembering all clusters that happened on current bar to avoid repeating sound alerts
	Buycluster - persistentFloat 1-20
	SellClusters - PersistentFloat 21-40*/

	if (sc.Index != PreviousIndex) {
		TotalBarBuyClustersCounter = 1;
		TotalBarSellClustersCounter = 21;
		for (int i = 1; i <= 40; i++) {
			sc.SetPersistentFloat(i, 0.0f);
		}
	}
	int AskVol, BidVol, BuyersImbCounter, SellersImbCounter, BuyClustersCounter, SellClustersCounter;
	int BuyExtLineCounter, SellExtLineCounter;
	float ImbRatio, BottomPriceOfBuyCluster, BottomPriceOfSellCluster;
	float LastBuyImbPrice, LastSellImbPrice, BuyImbPrice, SellImbPrice;
	int ClusterAlreadyHappenedInBar;
	AskVol = 0; BidVol = 0; BuyersImbCounter = 0; SellersImbCounter = 0; BuyClustersCounter = 0; SellClustersCounter = 0;
	BuyExtLineCounter = 0; SellExtLineCounter = 0;;
	ImbRatio = 0; BottomPriceOfBuyCluster = 0; BottomPriceOfSellCluster = 0;
	LastBuyImbPrice = 0; LastSellImbPrice = 0; BuyImbPrice = 0; SellImbPrice = 0;

	int BarLevels = (int)((sc.High[sc.Index] - sc.Low[sc.Index]) / sc.TickSize) + 1;

	//Delete all previous clusters on current bar
	if (sc.Index == sc.ArraySize - 1) {
		for (int i = 1; i <= PersistBuyClusterCounter; i++) {
			sc.Subgraph[(i * 2) - 1][sc.Index] = 0;
			sc.Subgraph[(i - 1) * 2][sc.Index] = 0;
		}

		for (int i = 1; i <= PersistSellClusterCounter; i++) {
			sc.Subgraph[(i * 2) - 1 + 20][sc.Index] = 0;
			sc.Subgraph[(i - 1) * 2 + 20][sc.Index] = 0;
		}
		for (int i = 0; i <= BarLevels; i++) {
			sc.DeleteLineUntilFutureIntersection(sc.Index, i);
		}
	}

	//******* Loop Through all bar's levels every tick ***************************************************
	s_VolumeAtPriceV2* p_VolumeAtPriceAtIndex;
	
	for (int ElementIndex = 0; ElementIndex < BarLevels - 1; ElementIndex++) {
		sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.Index, ElementIndex, &p_VolumeAtPriceAtIndex);
		BidVol = p_VolumeAtPriceAtIndex->BidVolume;
		sc.VolumeAtPriceForBars->GetVAPElementAtIndex(sc.Index, ElementIndex + 1, &p_VolumeAtPriceAtIndex);
		AskVol = p_VolumeAtPriceAtIndex->AskVolume;

		ImbRatio = (float)AskVol / (float)BidVol;

		if (ImbRatio >= MinImbalanceRatio.GetFloat() && BidVol != 0) { //If Imbalance in favor of buyers

			BuyImbPrice = sc.Low[sc.Index] + sc.TickSize * (float)(ElementIndex + 1);
			BuyersImbCounter++;

			if (BuyImbPrice - LastBuyImbPrice > (float)MaxDist.GetInt() * sc.TickSize) { // If distance too large
				BuyersImbCounter = 1;
				BottomPriceOfBuyCluster = BuyImbPrice;
			}

			else { // If distance is good
				if (BuyersImbCounter >= MinNumOfImb4Cluster.GetInt()) { // if we have enough imbalances for drawing cluster
					if (BuyersImbCounter == MinNumOfImb4Cluster.GetInt())  BuyClustersCounter++; // If it's the first imbalance that meets the min num of imbalances for cluster
					PersistBuyClusterCounter = BuyClustersCounter;
					sc.Subgraph[(BuyClustersCounter * 2) - 1][sc.Index] = BottomPriceOfBuyCluster - sc.TickSize / 2;
					sc.Subgraph[(BuyClustersCounter - 1) * 2][sc.Index] = BuyImbPrice + sc.TickSize / 2;
					// Loop through all clusters that happened in this bar and see if we had this one already

					ClusterAlreadyHappenedInBar = 0;
					for (int i = 1; i <= 20; i++) {
						if (sc.GetPersistentFloat(i) == BottomPriceOfBuyCluster) {
							ClusterAlreadyHappenedInBar = 1;
							break;
						}
					}
					if (ClusterAlreadyHappenedInBar == 0) {
						sc.SetPersistentFloat(TotalBarBuyClustersCounter, BottomPriceOfBuyCluster);
						TotalBarBuyClustersCounter++;
						//str.Format("Buy Cluster Bottom = %f", BottomPriceOfBuyCluster);
						//sc.AddMessageToLog(str,0);
						if (Sound_Alert.GetYesNo() == 1) sc.SetAlert(Buy_Cluster_Alert_Number.GetInt());
					}

					if (Extend_Line_From_Signal.GetYesNo() == 1) {
						for (float BuyExtLinePrice = BottomPriceOfBuyCluster; BuyExtLinePrice <= BuyImbPrice; BuyExtLinePrice += sc.TickSize) {
							sc.AddLineUntilFutureIntersection
							(sc.Index // where to start drawing
								, (int)((BuyExtLinePrice - sc.Low[sc.Index]) / sc.TickSize)  // LineIDForBar
								, BuyExtLinePrice // The price level of the line
								, BuyImbExtLine.PrimaryColor
								, BuyImbExtLine.LineWidth
								, BuyImbExtLine.LineStyle
								, 0 //DisplayValueLabel.GetYesNo()
								, false //DisplayNameLabel // true/false
								, ""// "string" or string variable
							);
						}
					}
				}
			}
			LastBuyImbPrice = BuyImbPrice;
		}

		else if (ImbRatio <= 1.0f / MinImbalanceRatio.GetFloat() && AskVol != 0 && BidVol != 0) { //If Imbalance in favor of sellers
			SellImbPrice = sc.Low[sc.Index] + sc.TickSize * (float)(ElementIndex);
			SellersImbCounter++;

			if (SellImbPrice - LastSellImbPrice > (float)MaxDist.GetInt() * sc.TickSize) { // If distance too large
				SellersImbCounter = 1;
				BottomPriceOfSellCluster = SellImbPrice;
			}

			else { // If distance is good
				if (SellersImbCounter >= MinNumOfImb4Cluster.GetInt()) { // if we have enough imbalances for drawing cluster
					if (SellersImbCounter == MinNumOfImb4Cluster.GetInt())  SellClustersCounter++; // If it's the first imbalance that meets the min num of imbalances for cluster
					PersistSellClusterCounter = SellClustersCounter;
					sc.Subgraph[(SellClustersCounter * 2) - 1 + 20][sc.Index] = BottomPriceOfSellCluster - sc.TickSize / 2;
					sc.Subgraph[(SellClustersCounter - 1) * 2 + 20][sc.Index] = SellImbPrice + sc.TickSize / 2;

					ClusterAlreadyHappenedInBar = 0;
					for (int i = 21; i <= 40; i++) {
						if (sc.GetPersistentFloat(i) == BottomPriceOfSellCluster) {
							ClusterAlreadyHappenedInBar = 1;
							break;
						}
					}
					if (ClusterAlreadyHappenedInBar == 0) {
						sc.SetPersistentFloat(TotalBarSellClustersCounter, BottomPriceOfSellCluster);
						TotalBarSellClustersCounter++;
						//str.Format("Sell Cluster Bottom = %f", BottomPriceOfSellCluster);
						//sc.AddMessageToLog(str,0);
						if (Sound_Alert.GetYesNo() == 1) sc.SetAlert(Sell_Cluster_Alert_Number.GetInt());
					}
					if (Extend_Line_From_Signal.GetYesNo() == 1) {
						for (float SellExtLinePrice = BottomPriceOfSellCluster; SellExtLinePrice <= SellImbPrice; SellExtLinePrice += sc.TickSize) {
							sc.AddLineUntilFutureIntersection
							(sc.Index // where to start drawing
								, (int)((SellExtLinePrice - sc.Low[sc.Index]) / sc.TickSize) // LineIDForBar
								, SellExtLinePrice // The price level of the line
								, SellImbExtLine.PrimaryColor
								, SellImbExtLine.LineWidth
								, SellImbExtLine.LineStyle
								, 0 //DisplayValueLabel.GetYesNo()
								, false //DisplayNameLabel // true/false
								, ""// "string" or string variable
							);
						}
					}
				}
			}
			LastSellImbPrice = SellImbPrice;
		}

	}
	PreviousIndex = sc.Index;
}

