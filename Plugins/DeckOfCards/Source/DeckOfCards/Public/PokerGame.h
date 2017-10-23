// Robert Chubb - Saxon Rah - Parabolic Labs
// Poker Game Actor
#pragma once
// Engine Stuff
#include "EngineMinimal.h"
#include "Object.h"
#include "GameFramework/Actor.h"
// DeckOfCards Stuff
#include "DeckOfCardsTypes.h"
#include "StandardCardDeck.h"
// Hand Evaluation Stuff
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
// Reflection
#include "PokerGame.generated.h"

UENUM(BlueprintType)
enum class EStandardPokerHandRank : uint8
{
	PR_HighCard			UMETA(DisplayName = "High Card"),
	PR_OnePair			UMETA(DisplayName = "One Pair"),
	PR_TwoPair			UMETA(DisplayName = "Two Pair"),
	PR_ThreeOfAKind		UMETA(DisplayName = "Three of a Kind"),
	PR_Straight			UMETA(DisplayName = "Straight"),
	PR_Flush			UMETA(DisplayName = "Flush"),
	PR_FullHouse		UMETA(DisplayName = "Full House"),
	PR_FourOfAKind		UMETA(DisplayName = "Four of a Kind"),
	PR_StraightFlush	UMETA(DisplayName = "Straight Flush"),
	PR_RoyalFlush		UMETA(DisplayName = "Royal Flush"),
	PR_RankCount		UMETA(DisplayName = "RANK_COUNT")
};

class PokerHandAnalyzer
{
public:
	PokerHandAnalyzer()
	{
		RankCount.AddZeroed(13);
		SuitCount.AddZeroed(4);
	}

	EStandardPokerHandRank AnalyzeHand(FStandardCardArray InHand)
	{
		// This is bucket counting
		// We created TArrays or buckets to throw ideas of cards into, to count suits and ranks to determine hand rank.
		if (InHand.SCArray.Num() != 5)
		{
			return EStandardPokerHandRank::PR_RankCount;
			UE_LOG(GenLog, Warning, TEXT("Hand is too small or too large. 5 Cards please."));
		}
		// Should we sort the hand before iteration? by Suit? by Rank?
		// hand.SCArray.Sort();

		// Loop through the hand and count Suits and Ranks
		for (int32 i = 0; i < InHand.SCArray.Num(); ++i)
		{
			int32 r = static_cast<int32>(InHand.SCArray[i].Rank);
			int32 s = static_cast<int32>(InHand.SCArray[i].Suit);
			RankCount[r]++;
			SuitCount[s]++;
		}
		// UE_LOG(GenLog, Warning, TEXT("Analyze Hand = "));
		// InHand.PrintCardsToLog();

		return AnalyzeHandPrivate();
	}

private:
	TArray<int32> RankCount;
	TArray<int32> SuitCount;

	EStandardPokerHandRank AnalyzeHandPrivate()
	{
		bool bPairOne = false, bPairTwo = false, bThreeOfAKind = false, bFourOfAKind = false, bFlush = false, bStraight = false;
		for (int32 x = 0; x < 13; x++)
			switch (RankCount[x])
			{
				case 2: if (bPairOne) bPairTwo = true; else bPairOne = true; break;
				case 3: bThreeOfAKind = true; break;
				case 4: bFourOfAKind = true;
			}
		for (int32 x = 0; x < 4; x++)
			if (SuitCount[x] == 5)
			{
				bFlush = true; break;
			}

		if (!bPairOne && !bPairTwo && !bThreeOfAKind && !bFourOfAKind)
		{
			int32 s = 0;
			for (int32 x = 0; x < 13; x++)
			{
				if (RankCount[x]) s++; else s = 0;
				if (s == 5) break;
			}
			bStraight = (s == 5) || (s == 4 && RankCount[0] && !RankCount[1]);
		}

		if (bStraight && bFlush)
		{
			if (RankCount[0] > 0)
			{ return EStandardPokerHandRank::PR_RoyalFlush; } 
			else
			{ return EStandardPokerHandRank::PR_StraightFlush; }
		}
		else if (bFourOfAKind) return EStandardPokerHandRank::PR_FourOfAKind;
		else if (bPairOne && bThreeOfAKind) return EStandardPokerHandRank::PR_FullHouse;
		else if (bFlush) return EStandardPokerHandRank::PR_Flush;
		else if (bStraight) return EStandardPokerHandRank::PR_Straight;
		else if (bThreeOfAKind) return EStandardPokerHandRank::PR_ThreeOfAKind;
		else if (bPairOne && bPairTwo) return EStandardPokerHandRank::PR_TwoPair;
		else if (bPairOne) return EStandardPokerHandRank::PR_OnePair;
		return EStandardPokerHandRank::PR_HighCard;
	}
};

UCLASS(Blueprintable)
class APokerGame : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
		AStandardCardDeck* Poker;

	APokerGame()
	{};

	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|PokerGame|UnitTest")
		void TestAll();

	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|PokerGame")
		FString GetHandAsString(FStandardCardArray InHand);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|PokerGame")
		bool DrawPokerHand(FStandardCardArray &OutHand);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|PokerGame")
		void DrawPokerHandFromAnInfiniteDeck(FStandardCardArray &OutHand);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|PokerGame")
		EStandardPokerHandRank RandomHandRank(int32 Min = 0, int32 Max = 9);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|PokerGame")
		EStandardCardRank RandomCardRank(int32 Min = 0, int32 Max = 12);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|PokerGame")
		EStandardCardSuit RandomCardSuit(int32 Min = 0, int32 Max = 3);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|PokerGame")
		bool GeneratePokerHandByType(EStandardPokerHandRank RankToGenerate, FStandardCardArray &OutHand);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|PokerGame")
		EStandardPokerHandRank AnalyzePokerHand(FStandardCardArray InHand);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Cards")
		void PrintHandRankToLog(EStandardPokerHandRank InRank);

};
