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

#include "brain.h"
#include <QDebug>

Brain::Brain() : _bet(0), _balance(250)
{
    _deck = new Deck();
    _hand = new Hand();
}

void Brain::removeCard(int cardIndex)
{
    _hand->removeCard(cardIndex);
}

void Brain::reset()
{
     _bet = (0);
     _balance = (250);
}

void Brain::winningHand()
{
    PokerHand winningHand = PokerHand::NONE;
    PokerHand handIs = PokerHand::NONE;

    if ((int)_hand->isRoyalFlush())					//check from best to worst what hand has
    {
        winningHand = _hand->isRoyalFlush();		//if hand has royal flush, winning hand is royal flush
        handIs = _hand->isRoyalFlush();
        losingMessage = "";
    }
    else if ((int)_hand->isStraighFlush())
    {
        winningHand = _hand->isStraighFlush();		//else if hand has straight, winning hand is straight
        handIs = _hand->isStraighFlush();
        losingMessage = "";
    }
    else if ((int)_hand->isFourOfAKind())
    {
        winningHand = _hand->isFourOfAKind();		//else if hand has four of a kind, winning hand is four of a kind
        handIs = _hand->isFourOfAKind();
        losingMessage = "";
    }
    else if ((int)_hand->isFullHouse())
    {
        winningHand = _hand->isFullHouse();			//else if hand has full-house, winning hand is full-house
        handIs = _hand->isFullHouse();
        losingMessage = "";
    }
    else if ((int)_hand->isFlush())
    {
        winningHand = _hand->isFlush();				//else if hand has flush, winning hand is flush
        handIs = _hand->isFlush();
        losingMessage = "";
    }
    else if ((int)_hand->isStraight())
    {
        winningHand = _hand->isStraight();			//else if hand has a straight, winning hand is a straight
        handIs = _hand->isStraight();
        losingMessage = "";
    }
    else if ((int)_hand->isThreeOffAKind())
    {
        winningHand = _hand->isThreeOffAKind();		//else if hand has three of a king, winning hand is three of a kind
        handIs = _hand->isThreeOffAKind();
        losingMessage = "";
    }
    else if ((int)_hand->isTwoPair())
    {
        winningHand = _hand->isTwoPair();			//else if hand has two pair, winning hand is two pair
        handIs = _hand->isTwoPair();
        losingMessage = "";
    }
    else if ((int)_hand->isJacksOrBetter())
    {
        winningHand = _hand->isJacksOrBetter();		//else if hand has jacks or better, winning hand is jacks or better
        handIs = _hand->isJacksOrBetter();
        losingMessage = "";
    }
    else
    {
        losingMessage = "Better luck next time!";
    }

    _winningAmount = Hand::payout[winningHand] * getBet();
    _winningHandType = Hand::handType[handIs];
}

void Brain::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void Brain::shuffle()
{
    _deck->shuffle();
}

void Brain::dealNewHand()
{
    _hand->clear();
    for(int i = 0; i < 5; i++)
    {
        _hand->addCard(_deck->drawCard());
    }
}

void Brain::replaceCardAtN(int index)
{
    _hand->replaceCard(index, _deck->drawCard());
}

CardPtr Brain::getCardAtN(int n)
{
    return _hand->getCardAtN(n);
}
