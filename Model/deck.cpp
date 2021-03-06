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

#include "deck.h"
#include "card.h"
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <random>

Deck::Deck()
{
    if (_deck.size() != 0)
        _deck.clear();

    for (auto f : Card::faces)
        for (auto s : Card::suits)
            _deck.push_back(std::make_shared<Card>(Card(f,s)));


    _topOfDeck = _deck.size()-1;
}

bool Deck::isEmpty() const
{
    return (_topOfDeck < 0);
}

CardPtr Deck::drawCard()
{
    if(isEmpty()){
        return nullptr;
    }
    else{
        return _deck[_topOfDeck--]; //post decrement happens after expression happens
    }
}

void Deck::shuffle()
{

    std::random_shuffle(_deck.begin(), _deck.end());

    _topOfDeck = _deck.size()-1;
}
