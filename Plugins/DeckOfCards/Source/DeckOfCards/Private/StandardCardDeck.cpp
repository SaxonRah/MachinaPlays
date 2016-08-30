// Robert Chubb - Saxon Rah - Parabolic Labs
#include "DeckOfCardsPrivatePCH.h"
#include "StandardCardDeck.h"

void AStandardCardDeck::UnitTest()
{

	UE_LOG(GenLog, Warning, TEXT("-----------Orginal Deck-----------"));
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));

	FStandardCardArray Player1Hand, Player2Hand;
	FStandardCardArray CardsForPlayer2;
	FStandardCard TempCard, TempCard2, TempCard22, TempCard222;

	UE_LOG(GenLog, Warning, TEXT("-----------Set Card By Enum-----------"));
	SetCardByEnums(TempCard2, EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Ace);
	PrintCardToLog(TempCard2);
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));

	UE_LOG(GenLog, Warning, TEXT("-----------Set Card By Index-----------"));
	SetCardByIndex(TempCard22, 2);
	PrintCardToLog(TempCard22);
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));

	UE_LOG(GenLog, Warning, TEXT("-----------Set Card By Indexes-----------"));
	SetCardByIndexes(TempCard222, 3, 2);
	PrintCardToLog(TempCard222);
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));

	//////////////////////////////////////////////////////////////////////////

	UE_LOG(GenLog, Warning, TEXT("-----------Discard By Card-----------"));
	TempCard = FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Ace);
	PrintCardToLog(TempCard);
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));
	DiscardCard(TempCard);
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("-----------Deck After Discard Card-----------"));
	UE_LOG(GenLog, Warning, TEXT("-----------Discard Card By Index #5-----------"));
	PrintCardToLog(Deck.SCArray[5]);
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));
	DiscardCard(6);
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("-----------Deck After Discard Card-----------"));

	//////////////////////////////////////////////////////////////////////////

	UE_LOG(GenLog, Warning, TEXT("-----------Discard All-----------"));
	DiscardAll();
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));
	UE_LOG(GenLog, Warning, TEXT("-----------Create Factory Deck-----------"));
	CreateFactoryDeck();
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("-----------Deck After Factory Deck-----------"));

	//////////////////////////////////////////////////////////////////////////

	UE_LOG(GenLog, Warning, TEXT("-----------Cut Cards Sloppy-----------"));
	CutCardsSloppy(26);
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));

	UE_LOG(GenLog, Warning, TEXT("-----------Discard All-----------"));
	UE_LOG(GenLog, Warning, TEXT("-----------Create Factory Deck-----------"));
	DiscardAll();
	CreateFactoryDeck();

	//////////////////////////////////////////////////////////////////////////

	UE_LOG(GenLog, Warning, TEXT("-----------Cut Cards-----------"));
	CutCards(26);
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));

	UE_LOG(GenLog, Warning, TEXT("-----------Discard All-----------"));
	UE_LOG(GenLog, Warning, TEXT("-----------Create Factory Deck-----------"));
	DiscardAll();
	CreateFactoryDeck();

	//////////////////////////////////////////////////////////////////////////

	UE_LOG(GenLog, Warning, TEXT("-----------Fisher Yates Shuffle-----------"));
	FisherYatesShuffle();
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("-----------Deck After Fisher Yates Shuffle-----------"));

	//////////////////////////////////////////////////////////////////////////

	UE_LOG(GenLog, Warning, TEXT("-----------Draw Card-----------"));
	DrawCardFromTop(TempCard);
	PrintCardToLog(TempCard);
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));
	Player1Hand.AddCard(TempCard);
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("-----------Deck After Draw-----------"));

	//////////////////////////////////////////////////////////////////////////

	UE_LOG(GenLog, Warning, TEXT("-----------Draw Cards-----------"));
	DrawCardsFromTop(5, CardsForPlayer2);
	PrintCardsToLog(CardsForPlayer2);
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));
	Player1Hand.AddCard(TempCard);
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("-----------Deck After Draw Cards-----------"));

	//////////////////////////////////////////////////////////////////////////

	UE_LOG(GenLog, Warning, TEXT("-----------Draw Random Card-----------"));
	DrawRandomCard(TempCard);
	PrintCardToLog(TempCard);
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));
	Player1Hand.AddCard(TempCard);
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("-----------Deck After Random Draw Card-----------"));

	//////////////////////////////////////////////////////////////////////////

	UE_LOG(GenLog, Warning, TEXT("-----------Draw Random Cards-----------"));
	CardsForPlayer2.DiscardAll();
	DrawRandomCards(5, CardsForPlayer2);
	PrintCardsToLog(CardsForPlayer2);
	UE_LOG(GenLog, Warning, TEXT("--------------------------------------------"));
	PrintDeckToLog();
	UE_LOG(GenLog, Warning, TEXT("-----------Deck After Random Draw Cards-----------"));

	//////////////////////////////////////////////////////////////////////////
}

void AStandardCardDeck::SetCardByEnums(FStandardCard &CardToSet, EStandardCardSuit SuitIndex, EStandardCardRank RankIndex)
{
	CardToSet.SetCardByEnums(SuitIndex, RankIndex);
}

void AStandardCardDeck::SetCardByIndex(FStandardCard &CardToSet, int32 Index)
{
	CardToSet.SetCardByIndex(Index);
}

void AStandardCardDeck::SetCardByIndexes(FStandardCard &CardToSet, int32 SuitIndex, int32 RankIndex)
{
	CardToSet.SetCardByIndexes(SuitIndex, RankIndex);
}

void AStandardCardDeck::PrintCardToLog(FStandardCard InCard)
{
	InCard.PrintCardToLog();
}

void AStandardCardDeck::CreateFactoryDeckPrivate()
{
	Deck.ReserveCardArray(StandardNumberOfCards);
	for (int32 cardValue = 0; cardValue < StandardNumberOfCards; ++cardValue)
	{
		Deck.SCArray.Push(FStandardCard(cardValue));
	}
}

void AStandardCardDeck::CreateFactoryDeck()
{
	if (Deck.SCArray.Num() > 0)
	{
		DiscardAll();
		CreateFactoryDeckPrivate();
	} 
	else
	{
		CreateFactoryDeckPrivate();
	}
}

void AStandardCardDeck::ReserveCardArray(int32 NumberOfCards)
{
	Deck.ReserveCardArray(NumberOfCards);
}

void AStandardCardDeck::SetCardArray(FStandardCardArray InArray)
{
	Deck.SetCardArray(InArray);
}

void AStandardCardDeck::AddCard(FStandardCard InCard)
{
	Deck.AddCard(InCard);
}

void AStandardCardDeck::AddCards(FStandardCardArray InCards)
{
	Deck.AddCards(InCards);
}

bool AStandardCardDeck::DiscardCard(FStandardCard InCard)
{
	return Deck.DiscardCard(InCard);
}

bool AStandardCardDeck::DiscardCards(FStandardCardArray InCards)
{
	return Deck.DiscardCards(InCards);
}

bool AStandardCardDeck::DiscardAll()
{
	return Deck.DiscardAll();
}

void AStandardCardDeck::FisherYatesShuffle()
{
	Deck.FisherYatesShuffle();
}

bool AStandardCardDeck::DrawCardFromTop(FStandardCard &OutCard)
{
	return Deck.DrawCardFromTop(OutCard);
}

bool AStandardCardDeck::DrawCardsFromTop(int32 NumberOfCards, FStandardCardArray &OutCards)
{
	return Deck.DrawCardsFromTop(NumberOfCards, OutCards);
}

bool AStandardCardDeck::DrawRandomCard(FStandardCard &OutCard)
{
	return Deck.DrawRandomCard(OutCard);
}

bool AStandardCardDeck::DrawRandomCards(int32 NumberOfCards, FStandardCardArray &OutCards)
{
	return Deck.DrawRandomCards(NumberOfCards, OutCards);
}

bool AStandardCardDeck::CutCardsSloppy(int32 PositionToCutFrom)
{
	return Deck.CutCardsSloppy(PositionToCutFrom);
}

bool AStandardCardDeck::CutCards(int32 PositionToCutFrom)
{
	return Deck.CutCards(PositionToCutFrom);
}

void AStandardCardDeck::PrintDeckToLog()
{
	Deck.PrintCardsToLog();
}

void AStandardCardDeck::PrintCardsToLog(FStandardCardArray InCards)
{
	Deck.PrintCardsToLog(InCards);
}