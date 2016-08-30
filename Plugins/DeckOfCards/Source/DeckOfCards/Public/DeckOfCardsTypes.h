// Robert Chubb - Saxon Rah - Parabolic Labs
// Deck of Cards Types
#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Object.h"
#include "Algo/Reverse.h"
#include "UnrealMathUtility.h"

#include <string>

#include "DeckOfCardsTypes.generated.h"

// Example usage
// ConvertEnumValueToString<EVictoryEnum>("EVictoryEnum", VictoryEnum)));
template<typename TEnum>
static FORCEINLINE FString ConvertEnumValueToString(const FString& Name, TEnum Value)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!enumPtr)
	{
		return FString("Invalid");
	}

	return enumPtr->GetEnumName((int32)Value);
}

UENUM(BlueprintType)
enum class EStandardCardSuit : uint8
{
	CS_Spades			UMETA(DisplayName = "Spades"),
	CS_Hearts			UMETA(DisplayName = "Hearts"),
	CS_Clubs			UMETA(DisplayName = "Clubs"),
	CS_Diamonds			UMETA(DisplayName = "Diamonds"),
	CS_SuitCount		UMETA(DisplayName = "SUIT_COUNT")
};

// inline EStandardCardSuit& operator++(EStandardCardSuit& eDOW, int32)  // <--- note -- must be a reference
// {
// 	const int32 i = static_cast<int32>(eDOW);
// 	eDOW = static_cast<EStandardCardSuit>((i + 1) % static_cast<int32>(EStandardCardSuit::CS_SuitCount));
// 	return eDOW;
// }

inline EStandardCardSuit& operator++(EStandardCardSuit& f, int32)
{
	switch (f)
	{
	case EStandardCardSuit::CS_Spades: return f = EStandardCardSuit::CS_Hearts;
	case EStandardCardSuit::CS_Hearts: return f = EStandardCardSuit::CS_Clubs;
	case EStandardCardSuit::CS_Clubs: return f = EStandardCardSuit::CS_Diamonds;
	case EStandardCardSuit::CS_Diamonds: return f = EStandardCardSuit::CS_Spades;
	default: return f = EStandardCardSuit::CS_SuitCount;
	}
}

inline EStandardCardSuit& operator--(EStandardCardSuit& f, int32)
{
	switch (f)
	{
	case EStandardCardSuit::CS_Spades: return f = EStandardCardSuit::CS_Diamonds;
	case EStandardCardSuit::CS_Hearts: return f = EStandardCardSuit::CS_Spades;
	case EStandardCardSuit::CS_Clubs: return f = EStandardCardSuit::CS_Hearts;
	case EStandardCardSuit::CS_Diamonds: return f = EStandardCardSuit::CS_Clubs;
	default: return f = EStandardCardSuit::CS_SuitCount;
	}
}

enum ControlType { BASE, UPPER_ARM, LOWER_ARM, WRIST };

// Overload the ControlType++ operator
inline ControlType& operator++(ControlType& eDOW, int)  // <--- note -- must be a reference
{
	const int i = static_cast<int>(eDOW) + 1;
	eDOW = static_cast<ControlType>((i) % 4);
	return eDOW;
}

// Overload the ControlType-- operator
inline ControlType& operator--(ControlType& type, int)  // <--- note -- must be a reference
{
	const int i = static_cast<int>(type) - 1;

	if (i < 0) // Check whether to cycle to last item if number goes below 0
	{
		type = static_cast<ControlType>(3);
	}
	else // Else set it to current number -1
	{
		type = static_cast<ControlType>((i) % 4);
	}
	return type;
}

UENUM(BlueprintType)
enum class EStandardCardRank : uint8
{
	CR_Ace				UMETA(DisplayName = "Ace"),
	CR_Two				UMETA(DisplayName = "Two"),
	CR_Three			UMETA(DisplayName = "Three"),
	CR_Four				UMETA(DisplayName = "Four"),
	CR_Five				UMETA(DisplayName = "Five"),
	CR_Six				UMETA(DisplayName = "Six"),
	CR_Seven			UMETA(DisplayName = "Seven"),
	CR_Eight			UMETA(DisplayName = "Eight"),
	CR_Nine				UMETA(DisplayName = "Nine"),
	CR_Ten				UMETA(DisplayName = "Ten"),
	CR_Jack				UMETA(DisplayName = "Jack"),
	CR_Queen			UMETA(DisplayName = "Queen"),
	CR_King				UMETA(DisplayName = "King"),
	CR_RankCount		UMETA(DisplayName = "RANK_COUNT")
};

inline EStandardCardRank& operator++(EStandardCardRank& f, int32)
{
	switch (f)
	{
	case EStandardCardRank::CR_Two: return f = EStandardCardRank::CR_Three;
	case EStandardCardRank::CR_Three: return f = EStandardCardRank::CR_Four;
	case EStandardCardRank::CR_Four: return f = EStandardCardRank::CR_Five;
	case EStandardCardRank::CR_Five: return f = EStandardCardRank::CR_Six;
	case EStandardCardRank::CR_Six: return f = EStandardCardRank::CR_Seven;
	case EStandardCardRank::CR_Seven: return f = EStandardCardRank::CR_Eight;
	case EStandardCardRank::CR_Eight: return f = EStandardCardRank::CR_Nine;
	case EStandardCardRank::CR_Nine: return f = EStandardCardRank::CR_Ten;
	case EStandardCardRank::CR_Ten: return f = EStandardCardRank::CR_Jack;
	case EStandardCardRank::CR_Jack: return f = EStandardCardRank::CR_Queen;
	case EStandardCardRank::CR_Queen: return f = EStandardCardRank::CR_King;
	case EStandardCardRank::CR_King: return f = EStandardCardRank::CR_Ace;
	case EStandardCardRank::CR_Ace: return f = EStandardCardRank::CR_Two;
	default: return f = EStandardCardRank::CR_RankCount;
	}
}

inline EStandardCardRank& operator--(EStandardCardRank& f, int32)
{
	switch (f)
	{
	case EStandardCardRank::CR_Two: return f = EStandardCardRank::CR_Ace;
	case EStandardCardRank::CR_Three: return f = EStandardCardRank::CR_Two;
	case EStandardCardRank::CR_Four: return f = EStandardCardRank::CR_Three;
	case EStandardCardRank::CR_Five: return f = EStandardCardRank::CR_Four;
	case EStandardCardRank::CR_Six: return f = EStandardCardRank::CR_Five;
	case EStandardCardRank::CR_Seven: return f = EStandardCardRank::CR_Six;
	case EStandardCardRank::CR_Eight: return f = EStandardCardRank::CR_Seven;
	case EStandardCardRank::CR_Nine: return f = EStandardCardRank::CR_Eight;
	case EStandardCardRank::CR_Ten: return f = EStandardCardRank::CR_Nine;
	case EStandardCardRank::CR_Jack: return f = EStandardCardRank::CR_Ten;
	case EStandardCardRank::CR_Queen: return f = EStandardCardRank::CR_Jack;
	case EStandardCardRank::CR_King: return f = EStandardCardRank::CR_Queen;
	case EStandardCardRank::CR_Ace: return f = EStandardCardRank::CR_King;
	default: return f = EStandardCardRank::CR_RankCount;
	}
}

USTRUCT(BlueprintType)
struct FStandardCard
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playing Cards")
		EStandardCardSuit Suit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playing Cards")
		EStandardCardRank Rank;

	bool operator==(const FStandardCard& Card) const
	{
		return (Suit == Card.Suit && Rank == Card.Rank);
	}
	bool operator!=(const FStandardCard& Card) const
	{
		return (Suit != Card.Suit && Rank != Card.Rank);
	}

	FStandardCard()
	{
		Suit = EStandardCardSuit::CS_Spades;
		Rank = EStandardCardRank::CR_Ace;
	};

	FStandardCard(EStandardCardSuit SuitIndex, EStandardCardRank RankIndex)
	{
		SetCardByEnums(SuitIndex, RankIndex);
	};

	FStandardCard(int32 Index)
	{
		SetCardByIndex(Index);
	};

	FStandardCard(int32 SuitIndex, int32 RankIndex)
	{
		SetCardByIndexes(SuitIndex, RankIndex);
	};

	void SetCardByEnums(EStandardCardSuit SuitIndex, EStandardCardRank RankIndex)
	{
		Suit = SuitIndex;
		Rank = RankIndex;
	}

	void SetCardByIndex(int32 Index) 
	{
		Suit = static_cast<EStandardCardSuit>(Index / static_cast<int32>(EStandardCardRank::CR_RankCount));
		Rank = static_cast<EStandardCardRank>(Index % static_cast<int32>(EStandardCardRank::CR_RankCount));
	}

	void SetCardByIndexes(int32 SuitIndex, int32 RankIndex)
	{
		Suit = static_cast<EStandardCardSuit>(SuitIndex / static_cast<int32>(EStandardCardRank::CR_RankCount));
		Rank = static_cast<EStandardCardRank>(RankIndex % static_cast<int32>(EStandardCardRank::CR_RankCount));
	}

	FString GetSuitAsString()
	{
		return ConvertEnumValueToString<EStandardCardSuit>("EStandardCardSuit", Suit);
	}
	
	FString GetRankAsString()
	{

		return ConvertEnumValueToString<EStandardCardRank>("EStandardCardRank", Rank);
	}

	FString GetSuitAsShorhandString()
	{
		FString SHSuit = "";
		if (Suit == EStandardCardSuit::CS_Clubs)
		{
			SHSuit = "c";
		} 
		else if (Suit == EStandardCardSuit::CS_Diamonds)
		{
			SHSuit = "d";
		}
		else if (Suit == EStandardCardSuit::CS_Hearts)
		{
			SHSuit = "h";
		}
		else if (Suit == EStandardCardSuit::CS_Spades)
		{
			SHSuit = "s";
		}
		else
		{
			SHSuit = "invalid";
		}
		return SHSuit;
	}

	FString GetRankAsShorhandString()
	{

		FString SHRank = "";
		if (Rank == EStandardCardRank::CR_Ace)
		{
			SHRank = "a";
		}
		else if (Rank == EStandardCardRank::CR_Two)
		{
			SHRank = "2";
		}
		else if (Rank == EStandardCardRank::CR_Three)
		{
			SHRank = "3";
		}
		else if (Rank == EStandardCardRank::CR_Four)
		{
			SHRank = "4";
		}
		else if (Rank == EStandardCardRank::CR_Five)
		{
			SHRank = "5";
		}
		else if (Rank == EStandardCardRank::CR_Six)
		{
			SHRank = "6";
		}
		else if (Rank == EStandardCardRank::CR_Seven)
		{
			SHRank = "7";
		}
		else if (Rank == EStandardCardRank::CR_Eight)
		{
			SHRank = "8";
		}
		else if (Rank == EStandardCardRank::CR_Nine)
		{
			SHRank = "9";
		}
		else if (Rank == EStandardCardRank::CR_Ten)
		{
			SHRank = "t";
		}
		else if (Rank == EStandardCardRank::CR_Jack)
		{
			SHRank = "j";
		}
		else if (Rank == EStandardCardRank::CR_Queen)
		{
			SHRank = "q";
		}
		else if (Rank == EStandardCardRank::CR_King)
		{
			SHRank = "k";
		}
		else
		{
			SHRank = "invalid";
		}
		return SHRank;
	}

	// std::string TestString = "Happy";
	// FString HappyString(TestString.c_str());

	// FString UE4Str = "Flowers";
	// std::string MyStdString(TCHAR_TO_UTF8(*UE4Str));

	FString GetCardAsShorhandString()
	{
		return GetRankAsShorhandString() + GetSuitAsShorhandString();
	}

	std::string ConvertCardToShorhandSTDString()
	{
		FString TempSuit = GetSuitAsShorhandString();
		std::string STDTempSuit(TCHAR_TO_UTF8(*TempSuit));

		FString TempRank = GetRankAsShorhandString();
		std::string STDTempRank(TCHAR_TO_UTF8(*TempRank));
		std::string card = STDTempRank + STDTempSuit;
		return card;
	}

	void PrintCardToLog()
	{
		FString TempSuit = TEXT(""), TempRank = TEXT("");
		TempSuit = ConvertEnumValueToString<EStandardCardSuit>("EStandardCardSuit", Suit);
		TempRank = ConvertEnumValueToString<EStandardCardRank>("EStandardCardRank", Rank);
		UE_LOG(GenLog, Warning, TEXT("Suit: %s, Rank: %s"), *TempSuit, *TempRank);
	}
};

USTRUCT(BlueprintType)
struct FStandardCardArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Library")
		TArray<FStandardCard> SCArray;

	void ReserveCardArray(int32 NumberOfCards)
	{
		SCArray.Reserve(NumberOfCards);
	}

	void SetCardArray(FStandardCardArray InArray)
	{
		SCArray = InArray.SCArray;
	}

	void AddCard(FStandardCard InCard)
	{
		SCArray.Push(InCard);
	}

	void AddCards(FStandardCardArray InCards)
	{
		for (int32 i = 0; i < InCards.SCArray.Num(); ++i)
		{
			AddCard(InCards.SCArray[i]);
		}
	}

	bool DiscardCardByIndex(int32 Index)
	{
		/* Check Numbers, clear/erase and discard the card */
		if (SCArray.Num() <= 0 || Index < 0) return false;

		if (Index <= SCArray.Num()-1)
		{
			DiscardCard(SCArray[Index]);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DiscardCard(FStandardCard CardToRemove)
	{
		/* Check Numbers, clear/erase and discard the card */
		if (SCArray.Num() <= 0) return false;

		int32 Index = 0;
		if (SCArray.Find(CardToRemove, Index))
		{
			SCArray.Remove(CardToRemove);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool DiscardCards(FStandardCardArray CardsToRemove)
	{
		/* Check Numbers, clear/erase and discard the cards */
		if (SCArray.Num() <= 0 || CardsToRemove.SCArray.Num() <= 0) return false;

		int32 Index = 0;
		bool bDidFind = false;
		for (int32 i = 0; i < CardsToRemove.SCArray.Num(); ++i)
		{
			bDidFind = false;
			if (SCArray.Find(CardsToRemove.SCArray[i], Index))
			{
				bDidFind = true;
				SCArray.Remove(CardsToRemove.SCArray[i]);
			}
		}
		if (bDidFind == true)
		{

			return true;
		} 
		else
		{
			return false;
		}
	}

	bool DiscardAll()
	{
		/* Check Numbers, clear/erase and discard all cards */
		if (SCArray.Num() <= 0) return false;

		//Empty
		SCArray.Empty();
		return true;
	}

	void FisherYatesShuffle()
	{
		for (int32 ShuffleCount = 1; ShuffleCount < 8; ++ShuffleCount)
		{
			for (int32 i = SCArray.Num() - 1; i > 0; i--)
			{
				int32 j = FMath::FloorToInt(FMath::SRand() * (i + 1)) % SCArray.Num();
				FStandardCard temp = SCArray[i];
				SCArray[i] = SCArray[j];
				SCArray[j] = temp;
			}
			UE_LOG(GenLog, Warning, TEXT("Shuffle #%d"), ShuffleCount);
			//PrintCardsToLog();
		}
	}  

	bool DrawCardFromTop(FStandardCard &OutCard)
	{
		if (SCArray.Num() > 0)
		{
			OutCard = SCArray[SCArray.Num() - 1];
			SCArray.RemoveAt(SCArray.Num() - 1, 1, true);
			return true;
		}
		else
		{
			UE_LOG(GenLog, Warning, TEXT("Tried to draw from an empty CardArray"));
			return false;
		}
	}

	bool DrawCardsFromTop(int32 NumberOfCards, FStandardCardArray &OutCards)
	{
		if (SCArray.Num() > 0 && NumberOfCards < SCArray.Num())
		{
			OutCards.DiscardAll();
			OutCards.ReserveCardArray(NumberOfCards);
			for (int32 i = 0; i < NumberOfCards; ++i)
			{
				OutCards.AddCard(SCArray[SCArray.Num() - 1]);
				SCArray.RemoveAt(SCArray.Num() - 1, 1, true);
			}
			return true;
		}
		else
		{
			UE_LOG(GenLog, Warning, TEXT("Tried to draw from an empty CardArray"));
			return false;
		}
	}

	bool DrawRandomCard(FStandardCard &OutCard)
	{
		if (SCArray.Num() > 0)
		{
			int32 j = FMath::FloorToInt(FMath::RandRange(0, SCArray.Num() - 1));
			OutCard = SCArray[j];
			SCArray.RemoveAt(j, 1, true);
			return true;
		}
		else
		{
			//OutCard = FStandardCard(EStandardCardSuit::CS_Count, EStandardCardRank::CR_Count);
			UE_LOG(GenLog, Warning, TEXT("Tried to draw from an empty CardArray"));
			return false;
		}
	}

	bool DrawRandomCards(int32 NumberOfCards, FStandardCardArray &OutCards)
	{
		if (SCArray.Num() > 0)
		{
			OutCards.DiscardAll();
			OutCards.ReserveCardArray(NumberOfCards);
			for (int32 i = 0; i < NumberOfCards; ++i)
			{
				int32 j = FMath::FloorToInt(FMath::RandRange(0, SCArray.Num() - 1));
				OutCards.AddCard(SCArray[j]);
				SCArray.RemoveAt(j, 1, true);
			}
			return true;
		}
		else
		{
			UE_LOG(GenLog, Warning, TEXT("Tried to draw from an empty CardArray"));
			return false;
		}
	}

	bool CutCardsSloppy(int32 PositionToCutFrom)
	{
		if (SCArray.Num() > 0 && PositionToCutFrom > 0 && PositionToCutFrom < SCArray.Num())
		{
			FStandardCard TempCard;
			FStandardCardArray CutDeck;
			CutDeck.ReserveCardArray(PositionToCutFrom);
			for (int32 i = SCArray.Num() - 1; i >= PositionToCutFrom; --i)
			{
				DrawCardFromTop(TempCard);
				CutDeck.AddCard(TempCard);
				DiscardCard(TempCard);
			}
			AddCards(CutDeck);
			return true;
		}
		else
		{
			UE_LOG(GenLog, Warning, TEXT("Tried to cut an empty CardArray"));
			return false;
		}
	}

	bool CutCards(int32 PositionToCutFrom)
	{
		if (SCArray.Num() > 0 && PositionToCutFrom > 0 && PositionToCutFrom < SCArray.Num())
		{
			FStandardCard TempCard;
			FStandardCardArray CutDeck, NewDeck;
			CutDeck.ReserveCardArray(PositionToCutFrom);
			for (int32 i = PositionToCutFrom; i < SCArray.Num(); ++i)
			{
				//TempCard = SCArray[i];
				DrawCardFromTop(TempCard);
				CutDeck.AddCard(TempCard);
			}
			DiscardCards(CutDeck);
			NewDeck.SCArray = SCArray;
			DiscardAll();
			Algo::Reverse(CutDeck.SCArray);
			AddCards(CutDeck);
			AddCards(NewDeck);
			return true;
		}
		else
		{
			UE_LOG(GenLog, Warning, TEXT("Tried to cut an empty CardArray"));
			return false;
		}
	}

	void PrintCardsToLog()
	{
		for (int32 i = 0; i < SCArray.Num(); ++i)
		{
			SCArray[i].PrintCardToLog();
		}
	}

	void PrintCardsToLog(FStandardCardArray Cards)
	{
		for (int32 i = 0; i < Cards.SCArray.Num(); ++i)
		{
			Cards.SCArray[i].PrintCardToLog();
		}
	}

	FStandardCardArray()
	{};
};
