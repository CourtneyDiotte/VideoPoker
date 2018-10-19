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

#ifndef CARD_H
#define CARD_H

#include <string>
#include <set>
#include <map>
#include <iostream>


enum class Suit {CLUB, DIAMOND, HEART, SPADE};
enum class Face {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
enum class CardColor {Black, Red};
class Card
{
public:
    Card(Face f, Suit s) : suit(s), face(f), _flipped(false) {}
    std::string toString() const;

    CardColor getColor() const;
    bool isFlipped() const {return _flipped;}

    void flip();

    const Face getFace()const{return face;}
    const Suit getSuit() const {return suit;}

    const Suit suit;
    const Face face;

private:
    bool _flipped;

public:

    // class members ///////////////////////////////////
    static const std::set<Suit> suits;
    static const std::set<Face> faces;

private:
    static const std::map<Face, std::string>  faceNames;
    static const std::map<Suit, std::string>  suitNames;
    ////////////////////////////////////////////////////
};

//
// comparison operator overloads
//
inline bool operator==(const Card& lhs, const Card& rhs){
    return ((lhs.face == rhs.face)&&(lhs.suit == rhs.suit));
}
inline bool operator< (const Card& lhs, const Card& rhs){
    if (lhs.face < rhs.face) return true;
    if ((lhs.face == rhs.face) && (lhs.suit < rhs.suit)) return true;
    return false;
}
inline bool operator!=(const Card& lhs, const Card& rhs){return !operator==(lhs,rhs);}
inline bool operator> (const Card& lhs, const Card& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const Card& lhs, const Card& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const Card& lhs, const Card& rhs){return !operator< (lhs,rhs);}

std::ostream& operator<<(std::ostream& os, Card& c);
#endif // CARD_H
