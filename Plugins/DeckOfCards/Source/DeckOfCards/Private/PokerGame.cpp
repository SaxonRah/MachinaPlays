// Robert Chubb - Saxon Rah - Parabolic Labs
#include "DeckOfCardsPrivatePCH.h"
#include "PokerGame.h"
 

void APokerGame::TestAll()
{
	FOutputDeviceNull ar;
	FString DrawnHandTypeFString = "";
	FStandardCardArray HandArray;

	UE_LOG(GenLog, Warning, TEXT("--------------------------Test All--------------------------"));
	Poker->PrintDeckToLog();
	Poker->CallFunctionByNameWithArguments(TEXT("DisplayDeck"), ar, NULL, true);


	//////////////////////////////////////////////////////////////////////////
	// Random Hand
	UE_LOG(GenLog, Warning, TEXT("--------------------------Random Hand--------------------------"));
	DrawPokerHand(HandArray);
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Random Hand--------------------------"));
	DrawPokerHand(HandArray);
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Random Hand--------------------------"));
	DrawPokerHand(HandArray);
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Random Hand--------------------------"));
	DrawPokerHand(HandArray);
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Random Hand--------------------------"));
	DrawPokerHand(HandArray);
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Royal Flush
	UE_LOG(GenLog, Warning, TEXT("--------------------------Royal Flush--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Ace));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_King));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Queen));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Jack));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Ten));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Ace));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_King));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Queen));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Jack));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Ten));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);
	//////////////////////////////////////////////////////////////////////////
	// Straight Flush
	UE_LOG(GenLog, Warning, TEXT("--------------------------Straight Flush--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Jack));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Ten));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Nine));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Eight));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Seven));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	//////////////////////////////////////////////////////////////////////////
	// Four of a Kind
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	UE_LOG(GenLog, Warning, TEXT("--------------------------Four of a Kind--------------------------"));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Five));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Five));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Five));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Five));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Two));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	//////////////////////////////////////////////////////////////////////////
	// Full House
	UE_LOG(GenLog, Warning, TEXT("--------------------------Full House--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Six));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Six));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Six));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_King));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_King));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	//////////////////////////////////////////////////////////////////////////
	// Flush
	UE_LOG(GenLog, Warning, TEXT("--------------------------Flush--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Jack));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Nine));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Eight));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Four));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Two));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	//////////////////////////////////////////////////////////////////////////
	// Straight
	UE_LOG(GenLog, Warning, TEXT("--------------------------Straight--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Ten));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Nine));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Eight));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Seven));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Six));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	//////////////////////////////////////////////////////////////////////////
	// Three of a Kind
	UE_LOG(GenLog, Warning, TEXT("--------------------------Three of a Kind--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Queen));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Queen));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Queen));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Nine));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Two));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	//////////////////////////////////////////////////////////////////////////
	// Two Pair
	UE_LOG(GenLog, Warning, TEXT("--------------------------Two Pair--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Jack));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Jack));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Three));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Three));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Two));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	//////////////////////////////////////////////////////////////////////////
	// One Pair
	UE_LOG(GenLog, Warning, TEXT("--------------------------One Pair--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Ten));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Ten));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Eight));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Two));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Clubs, EStandardCardRank::CR_Four));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	//////////////////////////////////////////////////////////////////////////
	// High Card
	UE_LOG(GenLog, Warning, TEXT("--------------------------High Card--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_King));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Diamonds, EStandardCardRank::CR_Queen));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Seven));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Spades, EStandardCardRank::CR_Four));
	HandArray.AddCard(FStandardCard(EStandardCardSuit::CS_Hearts, EStandardCardRank::CR_Three));
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	//////////////////////////////////////////////////////////////////////////
	// Generate Hand By Type
	UE_LOG(GenLog, Warning, TEXT("--------------------------Generate Hand By Type--------------------------"));

	UE_LOG(GenLog, Warning, TEXT("--------------------------Royal Flush--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_RoyalFlush, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Straight Flush--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_StraightFlush, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Four of a Kind--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_FourOfAKind, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Full House--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_FullHouse, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Flush--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_Flush, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	UE_LOG(GenLog, Warning, TEXT("--------------------------Straight--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_Straight, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Three of a Kind--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_ThreeOfAKind, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------Two Pair--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_TwoPair, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);

	UE_LOG(GenLog, Warning, TEXT("--------------------------One Pair--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_OnePair, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);


	UE_LOG(GenLog, Warning, TEXT("--------------------------High Card--------------------------"));
	HandArray.DiscardAll();
	HandArray.ReserveCardArray(5);
	GeneratePokerHandByType(EStandardPokerHandRank::PR_HighCard, HandArray);
	HandArray.PrintCardsToLog();
	DrawnHandTypeFString = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", AnalyzePokerHand(HandArray));
	UE_LOG(GenLog, Warning, TEXT("Type of Hand : %s"), *DrawnHandTypeFString);
	
}



FString APokerGame::GetHandAsString(FStandardCardArray InHand)
{
	FString HandStringTemp = "", HandString = "";
	for(int32 i = 0; i < InHand.SCArray.Num(); ++i)
	{
		HandStringTemp = InHand.SCArray[i].GetCardAsShorhandString();
		HandString = HandString + HandStringTemp + TEXT(" ");
	}
	return HandString;
}

bool APokerGame::DrawPokerHand(FStandardCardArray &OutHand)
{
	return Poker->DrawCardsFromTop(5, OutHand);
}

void APokerGame::DrawPokerHandFromAnInfiniteDeck(FStandardCardArray &OutHand)
{
	Poker->CreateFactoryDeck();
	Poker->FisherYatesShuffle();
	Poker->DrawCardsFromTop(5, OutHand);
}

bool APokerGame::GeneratePokerHandByType(EStandardPokerHandRank RankToGenerate, FStandardCardArray &OutHand)
{
	if (RankToGenerate == EStandardPokerHandRank::PR_RankCount) return false;

	switch (RankToGenerate)
	{
		case EStandardPokerHandRank::PR_RoyalFlush:
		{
			// containing five cards of sequential rank, all of the same suit, starting from ace
				// pick a random suit
				// select rank that is ace to ten
				// make a hand based on random suit and starting rank to iterate from
			// Verify hand is desired rank and return

			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = RandomCardSuit();
			OutHand.AddCard(FStandardCard(TempSuit, EStandardCardRank::CR_Ace));
			OutHand.AddCard(FStandardCard(TempSuit, EStandardCardRank::CR_King));
			OutHand.AddCard(FStandardCard(TempSuit, EStandardCardRank::CR_Queen));
			OutHand.AddCard(FStandardCard(TempSuit, EStandardCardRank::CR_Jack));
			OutHand.AddCard(FStandardCard(TempSuit, EStandardCardRank::CR_Ten));
			
			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_RoyalFlush)
			{
				OutHand.DiscardAll();
				return false;
			} 
			else
			{
				return true;
			}
		}
		case EStandardPokerHandRank::PR_StraightFlush:
		{
			// containing five cards of sequential rank, all of the same suit
				// pick a random suit
				// select a random starting rank that is 0 to rankcount - (5 or 4 test pls)
				// make a hand based on random suit and starting rank to iterate from
			// Verify hand is desired rank and return

			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = RandomCardSuit();
			EStandardCardRank StartingRank = RandomCardRank(0, static_cast<int32>(EStandardCardRank::CR_Nine));
			if (StartingRank > EStandardCardRank::CR_Ten)
			{
				StartingRank = EStandardCardRank::CR_Nine;
			}
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank++));
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank++));
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank++));
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank++));

			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_StraightFlush)
			{
				OutHand.DiscardAll();
				return false;
			}
			else
			{
				return true;
			}
		}
		case EStandardPokerHandRank::PR_FourOfAKind:
		{
			// containing four cards of the same rank and one card of another rank
				// pick a random rank and get all 4 suits and get a random card that is not related
				// make hand based on that
			// Verify hand is desired rank and return
			
			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = EStandardCardSuit::CS_Spades;
			EStandardCardRank StartingRank = RandomCardRank();
			
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			OutHand.AddCard(FStandardCard(TempSuit++, StartingRank));
			OutHand.AddCard(FStandardCard(TempSuit++, StartingRank));
			OutHand.AddCard(FStandardCard(TempSuit++, StartingRank));
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank++));

			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_FourOfAKind)
			{
				OutHand.DiscardAll();
				return false;
			}
			else
			{
				return true;
			}
		}
		case EStandardPokerHandRank::PR_FullHouse:
		{
			// containing three cards of one rank and two cards of another rank
				// pick a random rank and get 3 random suits and get a random suit of two ranks
				// make hand based on that
			// Verify hand is desired rank and return
			
			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = RandomCardSuit();
			EStandardCardRank StartingRank = RandomCardRank();
			
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			OutHand.AddCard(FStandardCard(TempSuit++, StartingRank));
			OutHand.AddCard(FStandardCard(TempSuit++, StartingRank));
			OutHand.AddCard(FStandardCard(TempSuit++, StartingRank++));
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_FullHouse)
			{
				OutHand.DiscardAll();
				return false;
			}
			else
			{
				return true;
			}
		}
		case EStandardPokerHandRank::PR_Flush:
		{
			// containing five cards all of the same suit, not all of sequential rank
				// pick a random rank and get 3 random suits and get 2 random cards that is not related
				// make hand based on that
			// Verify hand is desired rank and return
			
			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = RandomCardSuit();
			EStandardCardRank StartingRank = RandomCardRank();

			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			StartingRank++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			StartingRank++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			StartingRank++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			StartingRank++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_Flush)
			{
				OutHand.DiscardAll();
				return false;
			}
			else
			{
				return true;
			}
		}
		case EStandardPokerHandRank::PR_Straight:
		{
			// containing five cards of sequential rank, not all of the same suit
				// pick a random rank that is 0 to rankcount - (5 or 4 test pls)
				// pick random suits
				// make hand based on that
			// Verify hand is desired rank and return
			
			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = RandomCardSuit();
			EStandardCardRank StartingRank = RandomCardRank(0, static_cast<int32>(EStandardCardRank::CR_Nine));
			if (StartingRank > EStandardCardRank::CR_Ten)
			{
				StartingRank = EStandardCardRank::CR_Ten;
			}
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_Straight)
			{
				OutHand.DiscardAll();
				return false;
			}
			else
			{
				return true;
			}
		}
		case EStandardPokerHandRank::PR_ThreeOfAKind:
		{
			// containing three cards of the same rank and two cards of two other ranks 
				// pick a random rank and get 3 random suits and get 2 other rank cards
				// make hand based on that
			// Verify hand is desired rank and return
			
			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = RandomCardSuit();
			EStandardCardRank StartingRank = RandomCardRank();
			
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_ThreeOfAKind)
			{
				OutHand.DiscardAll();
				return false;
			}
			else
			{
				return true;
			}
		}
		case EStandardPokerHandRank::PR_TwoPair:
		{
			// containing two cards of the same rank, two cards of another rank and one card of a third rank
				// pick a random rank and get 2 random suits, pick a different rank and get 2 random suits, then one other rank card
				// make hand based on that
			// Verify hand is desired rank and return
			
			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = RandomCardSuit();
			EStandardCardRank StartingRank = RandomCardRank();

			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_TwoPair)
			{
				OutHand.DiscardAll();
				return false;
			}
			else
			{
				return true;
			}
		}
		case EStandardPokerHandRank::PR_OnePair:
		{
			// containing two cards of the same rank and three cards of three other ranks
				// pick a random rank and get 2 random suits, then get three other rank cards
				// make hand based on that
			// Verify hand is desired rank and return
			
			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = RandomCardSuit();
			EStandardCardRank StartingRank = RandomCardRank();

			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			TempSuit++; StartingRank++; TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++; TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++; TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_OnePair)
			{
				OutHand.DiscardAll();
				return false;
			}
			else
			{
				return true;
			}
		}
		case EStandardPokerHandRank::PR_HighCard:
		{
			// containing five cards not all of sequential rank or of the same suit, and none of which are of the same rank
				// pick random ranks and suits
				// make hand based on that
			// Verify hand is desired rank and return
			
			OutHand.DiscardAll();
			EStandardCardSuit TempSuit = RandomCardSuit();
			EStandardCardRank StartingRank = RandomCardRank();

			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			TempSuit++; StartingRank++; TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++; TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++; TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));
			TempSuit++; StartingRank++; TempSuit++; StartingRank++;
			OutHand.AddCard(FStandardCard(TempSuit, StartingRank));

			if (AnalyzePokerHand(OutHand) != EStandardPokerHandRank::PR_HighCard)
			{
				OutHand.DiscardAll();
				return false;
			}
			else
			{
				return true;
			}
		}
		default:
		{
			return false;
		}
	}
}

EStandardPokerHandRank APokerGame::RandomHandRank(int32 Min, int32 Max)
{
	return (EStandardPokerHandRank)FMath::RandRange(Min, Max);
}

EStandardCardRank APokerGame::RandomCardRank(int32 Min, int32 Max)
{
	return (EStandardCardRank)FMath::RandRange(Min, Max);
}

EStandardCardSuit APokerGame::RandomCardSuit(int32 Min, int32 Max)
{
	return (EStandardCardSuit)FMath::RandRange(Min, Max);
}

EStandardPokerHandRank APokerGame::AnalyzePokerHand(FStandardCardArray InHand)
{
	PokerHandAnalyzer pha;
	return pha.AnalyzeHand(InHand);
}

void APokerGame::PrintHandRankToLog(EStandardPokerHandRank InRank)
{
	FString TempRank = TEXT("");
	TempRank = ConvertEnumValueToString<EStandardPokerHandRank>("EStandardPokerHandRank", InRank);
	UE_LOG(GenLog, Warning, TEXT("Poker Hand Rank: %s"), *TempRank);
}
