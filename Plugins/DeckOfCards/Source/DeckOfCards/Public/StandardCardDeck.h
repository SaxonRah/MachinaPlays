// Robert Chubb - Saxon Rah - Parabolic Labs
// CardDeck Actor
#pragma once
#include "EngineMinimal.h"
#include "Object.h"
#include "GameFramework/Actor.h"
#include "DeckOfCardsTypes.h"
#include "StandardCardDeck.generated.h"

UCLASS(Blueprintable)
class AStandardCardDeck : public AActor
{
	GENERATED_BODY()
private:
		void CreateFactoryDeckPrivate();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
		int32 StandardNumberOfCards = static_cast<int32>(EStandardCardSuit::CS_SuitCount) * static_cast<int32>(EStandardCardRank::CR_RankCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards")
		FStandardCardArray Deck;

	AStandardCardDeck()
	{
		CreateFactoryDeck();
	};

	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|UnitTest")
		void UnitTest();

	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Cards")
		void SetCardByEnums(FStandardCard &CardToSet, EStandardCardSuit SuitIndex, EStandardCardRank RankIndex);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Cards")
		void SetCardByIndex(FStandardCard &CardToSet, int32 Index);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Cards")
		void SetCardByIndexes(FStandardCard &CardToSet, int32 SuitIndex, int32 RankIndex);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Cards")
		void PrintCardToLog(FStandardCard InCard);

	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		void CreateFactoryDeck();

	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		void ReserveCardArray(int32 NumberOfCards);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		void SetCardArray(FStandardCardArray InArray);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		void AddCard(FStandardCard InCard);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		void AddCards(FStandardCardArray InCards);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		bool DiscardCard(FStandardCard InCard);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		bool DiscardCards(FStandardCardArray InCards);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		bool DiscardAll();
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		void FisherYatesShuffle();
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		bool DrawCardFromTop(FStandardCard &OutCard);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		bool DrawCardsFromTop(int32 NumberOfCards, FStandardCardArray &OutCards);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		bool DrawRandomCard(FStandardCard &OutCard);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		bool DrawRandomCards(int32 NumberOfCards, FStandardCardArray &OutCards);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		bool CutCardsSloppy(int32 PositionToCutFrom);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		bool CutCards(int32 PositionToCutFrom);
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		void PrintDeckToLog();
	UFUNCTION(BlueprintCallable, Category = "DeckOfCards|Deck")
		void PrintCardsToLog(FStandardCardArray InCards);
	
};
