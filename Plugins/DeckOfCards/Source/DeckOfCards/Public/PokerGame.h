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

/*
class poker
{
public:
poker() { face = "A23456789TJQK"; suit = "SHCD"; }
std::string analyze(std::string h)
{
std::memset(faceCnt, 0, 13); std::memset(suitCnt, 0, 4); std::vector<std::string> hand;
std::transform(h.begin(), h.end(), h.begin(), toupper); std::istringstream i(h);
std::copy(std::istream_iterator<std::string>(i), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string> >(hand));
if (hand.size() != 5) return "invalid hand."; std::vector<std::string>::iterator it = hand.begin();
std::sort(it, hand.end()); if (hand.end() != std::adjacent_find(it, hand.end())) return "invalid hand.";
while (it != hand.end())
{
if ((*it).length() != 2) return "invalid hand.";
int n = face.find((*it).at(0)), l = suit.find((*it).at(1));
if (n < 0 || l < 0) return "invalid hand.";
faceCnt[n]++; suitCnt[l]++; it++;
}
std::cout << h << ": "; return analyzeHand();
}

private:

std::string face, suit;
unsigned char faceCnt[13], suitCnt[4];

std::string analyzeHand()
{
bool p1 = false, p2 = false, t = false, f = false, fl = false, st = false;
for (int x = 0; x < 13; x++)
switch (faceCnt[x])
{
case 2: if (p1) p2 = true; else p1 = true; break;
case 3: t = true; break;
case 4: f = true;
}
for (int x = 0; x < 4; x++)if (suitCnt[x] == 5) { fl = true; break; }

if (!p1 && !p2 && !t && !f)
{
int s = 0;
for (int x = 0; x < 13; x++)
{
if (faceCnt[x]) s++; else s = 0;
if (s == 5) break;
}
st = (s == 5) || (s == 4 && faceCnt[0] && !faceCnt[1]);
}

if (st && fl) return "straight-flush";
else if (f) return "four-of-a-kind";
else if (p1 && t) return "full-house";
else if (fl) return "flush";
else if (st) return "straight";
else if (t) return "three-of-a-kind";
else if (p1 && p2) return "two-pair";
else if (p1) return "one-pair";
return "high-card";
}
};
*/


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
