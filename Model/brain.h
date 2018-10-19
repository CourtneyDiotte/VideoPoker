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

#ifndef BRAIN_H
#define BRAIN_H
#include <vector>
#include "Model/card.h"
#include "Model/deck.h"
#include "Model/hand.h"
#include <QString>
#include "View/cardqpushbutton.h"
#include <QCoreApplication>
#include <QTime>


class Brain
{
public:
    Brain();

    void setCardN(int f);

    void removeCard(int cardIndex); //removes card at specified index

    int getBet(){return _bet;}   //returns bet amount
    void setBet(int b){_bet = b;}   //set bet amount

    int getBalance() {return _balance;}     //returns current balance
    void setBalance(int bal){_balance = bal;}   //set balance

    void winningHand();     //resolves hand to a winning hand or creates losing message

    void updateBalance() {_balance += _winningAmount;}      //update balance with winning amount from hand

    std::string getWinningHand() {return _winningHandType;}     //returns the winning hand name

    void delay(int millisecondsToWait);     //delay

    std::string getLosingMessage(){return losingMessage;}       //returns losing message if there is no winning hand

    void shuffle();         //Shuffle deck
    void dealNewHand();     //deal new hand (5 cards)
    void replaceCardAtN(int index);     //replace card at specified index

    CardPtr getCardAtN(int n);      //returns card at n

    void reset();       //reset bet and balance to 0

private:
    Hand* _hand;
    Deck* _deck;
    int _bet;
    int _balance;
    int _winningAmount;
    std::string _winningHandType;
    std::string losingMessage;
};

#endif // BRAIN_H
