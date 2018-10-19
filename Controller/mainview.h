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

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "Model/brain.h"
#include <QPushButton>
#include "Model/deck.h"
#include <QLabel>
#include <memory>
#include "View/cardqpushbutton.h"

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private slots:
    void onCardClick();
    void onBetClick();
    void onMaxBetClick();
    void onDealClick();
    void onDrawClick();

private:
    void drawView();
    void displayCardButtons();
    void resetTurn();

private:
    Brain* game;
    Ui::MainView *ui;
    std::vector<CardQPushButton*> cardDisplayBtns;
    std::unique_ptr<Deck> deck;
    QLabel* balanceLabel;
    QLabel* betLabel;

    QPushButton* betBtn;
    QPushButton* drawBtn;
    QPushButton* dealBtn;
    QPushButton* maxBetBtn;
    QLabel* logo;
    QLabel* paySheet;
    QLabel* hold;
    QLabel* clickToHold;
    QLabel* winningHand;

};

#endif // MAINVIEW_H
