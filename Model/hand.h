/*
*
* @author
* Courtney Diotte April 2018
*
* @version 1.0
* *
* @section DESCRIPTION
* Jacks Or Better
*
* @section LICENSE
* *
* Copyright 2018
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/

#ifndef HAND_H
#define HAND_H
#include "Model/card.h"
#include <vector>
#include <set>
#include <string>

using CardPtr = std::shared_ptr<Card>;

enum class PokerHand
{
    NONE,
    PAIR,
    JACKS_OR_BETTER,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

class Hand
{
public:
    Hand();

    void addCard(CardPtr card);     //add card to hand
    void removeCard(int cardIndex);     //remove card from hand
    void replaceCard(int cardIndex, CardPtr card);      //replace card
    const int sizeOfHand() const{return _hand.size();}      //returns size of hand
    CardPtr getCardAtN(int n);      //returns card specified card

    void clear() {_hand.clear();}       //clear hand


    PokerHand isJacksOrBetter() const;		//checks if hand has pair of jacks or better
    PokerHand isPair() const;				//checks if hand has a pair
    PokerHand isTwoPair() const;				//checks if hand has two pair
    PokerHand isThreeOffAKind() const;		//checks if hand has three of a kind
    PokerHand isStraight() const;			//checks if hand is a straight
    PokerHand isFlush() const;				//checks if hand is a flush
    PokerHand isFullHouse() const;			//checks if hand is a full house
    PokerHand isFourOfAKind() const;			//checks if hand is four of a kind
    PokerHand isStraighFlush() const;		//checks if hand is a straight flush
    PokerHand isRoyalFlush() const;
    static std::map<PokerHand, int> payout;		//maps poker hands to payouts
    static std::map<PokerHand, std::string> handType;

private:
    std::vector<CardPtr> _hand;
    std::map<Face, int> getFaceCounts() const;
    std::map<Suit, int> getSuitCounts() const;
    std::set<Face> getFaces() const;
    std::vector<bool> _drawCard;

};


#endif // HAND_H
