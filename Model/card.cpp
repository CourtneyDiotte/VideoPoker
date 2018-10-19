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

#include "card.h"

std::string Card::toString() const
{
    return  faceNames.at(face) +  suitNames.at(suit);
}

CardColor Card::getColor() const
{
    if(suit == Suit::DIAMOND || suit == Suit::HEART)
        return CardColor::Red;
    else
        return CardColor::Black;
}

void Card::flip()
{
    _flipped = _flipped ? false : true;
}

std::ostream& operator<<(std::ostream& os, Card& c)
{
    os << c.toString();
    return os;
}

const std::set<Suit> Card::suits {
    Suit::CLUB,
    Suit::DIAMOND,
    Suit::HEART,
    Suit::SPADE};

const std::set<Face> Card::faces {
    Face::ACE,
    Face::TWO,
    Face::THREE,
    Face::FOUR,
    Face::FIVE,
    Face::SIX,
    Face::SEVEN,
    Face::EIGHT,
    Face::NINE,
    Face::TEN,
    Face::JACK,
    Face::QUEEN,
    Face::KING};

const std::map<Face, std::string> Card::faceNames {
    {Face::ACE, " A"},
    {Face::TWO," 2"},
    {Face::THREE," 3"},
    {Face::FOUR, " 4"},
    {Face::FIVE, " 5"},
    {Face::SIX," 6"},
    {Face::SEVEN," 7"},
    {Face::EIGHT," 8"},
    {Face::NINE," 9"},
    {Face::TEN,"10"},
    {Face::JACK," J"},
    {Face::QUEEN," Q"},
    {Face::KING," K"}
};

const std::map<Suit, std::string> Card::suitNames {
    {Suit::HEART,"♥️"},
    {Suit::DIAMOND,"♦️"},
    {Suit::CLUB,"♣️"},
    {Suit::SPADE,"♠️"}};

