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

#include "Hand.h"

#include <algorithm>
#include <vector>
#include <set>



Hand::Hand()
{
}

void Hand::addCard(CardPtr card)
{
    _hand.push_back(card);
}

void Hand::removeCard(int cardIndex)
{
    std::vector<CardPtr> tempHand;
    cardIndex -= 1;
    if (cardIndex < _hand.size())
    {
        _hand.erase(_hand.begin() + cardIndex);
    }
}

PokerHand Hand::isJacksOrBetter() const
{
    auto faceCounts = getFaceCounts();

    if (std::any_of(faceCounts.begin(),
        faceCounts.end(),
        [](auto p)
    { return (p.first > Face::TEN || p.first == Face::ACE) && p.second == 2; }))
        return PokerHand::JACKS_OR_BETTER;
    return PokerHand::NONE;
}

PokerHand Hand::isPair() const
{
    auto faceCounts = getFaceCounts();

    if (std::any_of(faceCounts.begin(),
        faceCounts.end(),
        [](auto p)
    { return p.second == 2; }))
        return PokerHand::PAIR;

    return PokerHand::NONE;
}

PokerHand Hand::isThreeOffAKind() const
{
    auto faceCounts = getFaceCounts();

    if (std::any_of(faceCounts.begin(),
        faceCounts.end(),
        [](auto t)
    { return t.second == 3; }))
        return PokerHand::THREE_OF_A_KIND;

    return PokerHand::NONE;
}

PokerHand Hand::isTwoPair() const
{
    auto faceCounts = getFaceCounts();
    int pairCount = 0;

    for (auto it : faceCounts)
    {
        //if pair
        if (it.second == 2)
        {
            //increment pair count
            pairCount++;
        }
    }
    //if pair count is 2
    if (pairCount == 2)
    {	//you have 2 pair
        return PokerHand::TWO_PAIR;
    }
    else
    {
        return PokerHand::NONE;
    }
}

PokerHand Hand::isFourOfAKind() const
{
    auto faceCounts = getFaceCounts();

    //check if 4 of the same face
    if (std::any_of(faceCounts.begin(),
        faceCounts.end(),
        [](auto f)
    { return f.second == 4; }))
        return PokerHand::FOUR_OF_A_KIND;
    else
        return PokerHand::NONE;
}

PokerHand Hand::isFullHouse() const
{
    if ((int)isThreeOffAKind() && (int)isPair())
        return PokerHand::FULL_HOUSE;

    return PokerHand::NONE;
}

PokerHand Hand::isFlush() const
{
    auto suitCounts = getSuitCounts();
    //check if suit count is greater than 4
    if (std::any_of(suitCounts.begin(),
        suitCounts.end(),
        [](auto s) { return s.second > 4; }))
        return PokerHand::FLUSH;

    return PokerHand::NONE;
}

PokerHand Hand::isStraight() const
{
    auto faceCount = getFaceCounts();

    std::vector<Face>faces;
    PokerHand isStraight = PokerHand::NONE;
    bool aceHigh = false;
    int ace = 0;

    for (auto o : faceCount)
    {
        faces.push_back(o.first);
    }
    //sort cards
    std::sort(faces.begin(), faces.end());

    //first card
    Face first = faces.front();

    //last card
    Face last = faces.back();

    //if there is an ace
    if ((int)first == 0)
    {
        //make it a high ace
        aceHigh = true;
        ace = 13;
    }
    //if high ace
    if (aceHigh)
    {
        //check if high ace - the second card = 4
        if (ace - static_cast<int>(faces[1]) == 4)
        {
            if (!(int)isPair() && !(int)isThreeOffAKind() && !(int)isFourOfAKind()) {
                isStraight = PokerHand::STRAIGHT;
            }
            else
            {
                isStraight = PokerHand::NONE;
            }
        }
    }
    //else check if last card - first card = 4
    if (static_cast<int>(last) - static_cast<int>(first) == 4)
    {
        if (!(int)isPair() && !(int)isThreeOffAKind() && !(int)isFourOfAKind())
        {
            isStraight = PokerHand::STRAIGHT;
        }
        else
        {
            isStraight = PokerHand::NONE;
        }
    }
    return isStraight;
}

PokerHand Hand::isStraighFlush() const
{
    if ((int)isStraight() && (int)isFlush())
    {
        return PokerHand::STRAIGHT_FLUSH;
    }
    return PokerHand::NONE;
}

PokerHand Hand::isRoyalFlush() const
{
    auto faceCounts = getFaceCounts();

    if (std::any_of(faceCounts.begin(),
        faceCounts.end(),
        [this](auto p)
    { return (p.first > Face::NINE || p.first == Face::ACE) && (int)isFlush(); }))
        return PokerHand::ROYAL_FLUSH;
    return PokerHand::NONE;
}


std::map<PokerHand, int> Hand::payout =
{
    {PokerHand::JACKS_OR_BETTER, 1},
    {PokerHand::TWO_PAIR, 2},
    {PokerHand::THREE_OF_A_KIND, 3},
    {PokerHand::STRAIGHT, 4},
    {PokerHand::FLUSH, 6},
    {PokerHand::FULL_HOUSE, 9},
    {PokerHand::FOUR_OF_A_KIND, 25},
    {PokerHand::STRAIGHT_FLUSH, 50},
    {PokerHand::ROYAL_FLUSH, 250}
};

std::map<PokerHand, std::string> Hand::handType =
{
    { PokerHand::JACKS_OR_BETTER, "Jacks or better!" },
    { PokerHand::TWO_PAIR, "Two pair" },
    { PokerHand::THREE_OF_A_KIND, "Three of a kind" },
    { PokerHand::STRAIGHT, "Straight" },
    { PokerHand::FLUSH, "Flush" },
    { PokerHand::FULL_HOUSE, "Full house" },
    { PokerHand::FOUR_OF_A_KIND, "Four of a kind" },
    { PokerHand::STRAIGHT_FLUSH, "Straight flush" },
    { PokerHand::ROYAL_FLUSH, "Royal flush" }
};

std::map<Face, int> Hand::getFaceCounts() const
{
    std::map<Face, int>tmp;

    for (auto e : _hand)
    {
        tmp[e->face]++;
    }

    return tmp;
}

std::map<Suit, int> Hand::getSuitCounts() const
{
    std::map<Suit, int>tmp;

    for (auto e : _hand)
    {
        tmp[e->suit]++;
    }
    return tmp;
}

std::set<Face> Hand::getFaces() const
{
    std::set<Face> tmp;
    std::for_each(
        _hand.begin(),
        _hand.end(),
        [&tmp](auto c) {
        tmp.insert(c->face);
    });
    return tmp;
}

void Hand::replaceCard(int cardIndex, CardPtr card)
{
    if(cardIndex < _hand.size())
    {
        _hand[cardIndex] = card;
    }
}

CardPtr Hand::getCardAtN(int n)
{
    return _hand.at(n);
}
