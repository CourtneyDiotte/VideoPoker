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

#include "mainview.h"
#include "ui_mainview.h"
#include "Model/brain.h"
#include "View/cardqpushbutton.h"
#include <QDebug>
#include <memory>
#include <QVBoxLayout>
#include <QFont>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QString>

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{

    const int NUM_CARDS_IN_HAND = 5;
    srand(time(0));
    ui->setupUi(this);

    ui->centralWidget->setStyleSheet(QStringLiteral("background-color:rgb(39, 163, 101);"));
    this->setWindowTitle("Jacks or Better");
    game = new Brain();

    auto* verticalMain = new QVBoxLayout(ui->centralWidget);   //main Vertical layout
    auto* gridLayout = new QGridLayout();
    auto* horizontalMain = new QHBoxLayout();
    verticalMain->addLayout(gridLayout);
    verticalMain->addLayout(horizontalMain);

    logo = new QLabel();
    logo->setStyleSheet("border-image:url(:/images/Media/banner.png);");
    logo->setMinimumSize(700,100);
    logo->setMaximumSize(700,100);

    gridLayout->addWidget(logo,0,0,1,1);

    paySheet = new QLabel();
    paySheet->setStyleSheet("border-image:url(:/images/Media/paysheet1.png);");
    paySheet->setMinimumSize(700,300);
    paySheet->setMaximumSize(700,300);

    gridLayout->addWidget(paySheet, 1, 0,1,1);

    QFont font; //font for Buttons and cards
    font.setPixelSize(35);

    QFont font2;
    font2.setPixelSize(25);
    font2.setFamily("Times new Roman");

    QFont font3;
    font3.setPixelSize(19);
    font3.setBold(2);
    font3.setFamily("Times new Roman");

    QFont font4;
    font4.setPixelSize(13);



    gridLayout->setVerticalSpacing(10);
    gridLayout->addLayout(horizontalMain, 2, 0);

    game->shuffle();
    game->dealNewHand();
    for(int i = 0; i < NUM_CARDS_IN_HAND; ++i){
        CardQPushButton* cardDisplayBtn = new CardQPushButton(i);
        cardDisplayBtn->setHeld(false);
        cardDisplayBtn->setEnabled(false);
        cardDisplayBtn->setFont(font);
        cardDisplayBtn->setMaximumSize(QSize(128,192));
        cardDisplayBtn->setMinimumSize(QSize(128,192));
        cardDisplayBtn->setText("");
        cardDisplayBtn->setStyleSheet("border-image:url(:/images/Media/cardbackred.png)");
        horizontalMain->addWidget(cardDisplayBtn);
        connect(cardDisplayBtn, &CardQPushButton::clicked, this, &MainView::onCardClick);
        cardDisplayBtns.push_back(cardDisplayBtn);
    }



    auto* horizontalSecondary = new QHBoxLayout();
    gridLayout->addLayout(horizontalSecondary, 4, 0);

    betBtn = new QPushButton();
    betBtn->setText("Bet \nOne");
    betBtn->setEnabled(true);
    betBtn->setStyleSheet(QStringLiteral("background-color:rgb(249, 252, 251);color:black;"));
    betBtn->setMinimumSize(100,100);
    betBtn->setMaximumSize(100,100);
    horizontalSecondary->addWidget(betBtn);
    connect(betBtn, &CardQPushButton::clicked, this, &MainView::onBetClick);
    betBtn->setFont(font);


    maxBetBtn = new QPushButton();
    maxBetBtn->setText("Max \nBet");
    maxBetBtn->setEnabled(true);
    maxBetBtn->setStyleSheet(QStringLiteral("background-color:rgb(249, 252, 251);color:black;"));
    maxBetBtn->setMinimumSize(100,100);
    maxBetBtn->setMaximumSize(100,100);
    horizontalSecondary->addWidget(maxBetBtn);
    connect(maxBetBtn, &CardQPushButton::clicked, this, &MainView::onMaxBetClick);
    maxBetBtn->setFont(font);

    dealBtn = new QPushButton();
    dealBtn->setText("Deal");
    dealBtn->setEnabled(false);
    dealBtn->setStyleSheet(QStringLiteral("background-color:grey; color:black;"));
    dealBtn->setMinimumSize(100,100);
    dealBtn->setMaximumSize(100,100);
    horizontalSecondary->addWidget(dealBtn);
    connect(dealBtn, &CardQPushButton::clicked, this, &MainView::onDealClick);
    dealBtn->setFont(font);

    drawBtn = new QPushButton();
    drawBtn->setText("Draw");
    drawBtn->setEnabled(false);
    drawBtn->setStyleSheet(QStringLiteral("background-color:grey;color:black;"));
    drawBtn->setMinimumSize(100,100);
    drawBtn->setMaximumSize(100,100);
    horizontalSecondary->addWidget(drawBtn);
    connect(drawBtn, &CardQPushButton::clicked, this, &MainView::onDrawClick);
    drawBtn->setFont(font);

    winningHand = new QLabel();
    winningHand->setText(QString("Click on a card to hold "));
    winningHand->setMinimumSize(500,50);
    winningHand->setMaximumSize(500,50);
    winningHand->setFont(font4);
    gridLayout->addWidget(winningHand, 5, 0);

    betLabel = new QLabel();
    betLabel->setText("Bet: 0");
    betLabel->setMinimumSize(80,50);
    betLabel->setMaximumSize(80,50);
    betLabel->setFont(font3);
    horizontalSecondary->addWidget(betLabel);

    balanceLabel = new QLabel();
    balanceLabel->setText(QString("Balance: ") + QString::number(game->getBalance()));
    balanceLabel->setMinimumSize(150,50);
    balanceLabel->setMaximumSize(150,50);
    balanceLabel->setFont(font3);
    horizontalSecondary->addWidget(balanceLabel);

}

MainView::~MainView()
{
    delete ui;
}

void MainView::onCardClick()
{
    maxBetBtn->setEnabled(false);
    betBtn->setStyleSheet(QStringLiteral("background-color:grey;color:black;"));
    maxBetBtn->setStyleSheet(QStringLiteral("background-color:grey;color:black;"));
    betBtn->setEnabled(false);
    auto* cardDisplayBtn = dynamic_cast<CardQPushButton*>(sender());
    CardPtr card = game->getCardAtN(cardDisplayBtn->getIndex());

    if(!cardDisplayBtn->isHeld())
    {
        cardDisplayBtn->setStyleSheet("border-image:url(:/images/Media/cardfrontHold.png);");
        cardDisplayBtn->setHeld(true);

        if(card->getColor() == CardColor::Red){
            cardDisplayBtn->setStyleSheet("border-image:url(:/images/Media/cardfrontHold.png); color: red;");
        }
        else{
            cardDisplayBtn->setStyleSheet("border-image:url(:/images/Media/cardfrontHold.png); color: black;");
        }
            cardDisplayBtn->setText(QString::fromStdString(card->toString()));

    }
    else
    {
        cardDisplayBtn->setStyleSheet("border-image:url(:/images/Media/cardfront.png);");
        cardDisplayBtn->setHeld(false);

        if(card->getColor() == CardColor::Red){
            cardDisplayBtn->setStyleSheet("border-image:url(:/images/Media/cardfront.png); color: red;");
        }
        else{
            cardDisplayBtn->setStyleSheet("border-image:url(:/images/Media/cardfront.png); color: black;");
        }
            cardDisplayBtn->setText(QString::fromStdString(card->toString()));
    }

}

void MainView::onBetClick()
{
    const int BET_INCREMENT = 5;

    dealBtn->setEnabled(true);
    dealBtn->setStyleSheet(QStringLiteral("background-color:rgb(249, 252, 251);color:black;"));

    int tempBet = game->getBet();
    tempBet+= BET_INCREMENT;
    game->setBet(tempBet);

    int tempBalance = game->getBalance();
    tempBalance -= BET_INCREMENT;
    game->setBalance(tempBalance);
    drawView();
}

void MainView::onMaxBetClick()
{
    dealBtn->setEnabled(true);
    dealBtn->setStyleSheet(QStringLiteral("background-color:rgb(249, 252, 251);color:black;"));

    game->setBet(game->getBalance() + game->getBet());

    game->setBalance(0);

    drawView();
}

void MainView::onDealClick()
{
    displayCardButtons();
    drawBtn->setEnabled(true);
    drawBtn->setStyleSheet(QStringLiteral("background-color:rgb(249, 252, 251);color:black;"));
    dealBtn->setEnabled(false);
    dealBtn->setStyleSheet(QStringLiteral("background-color:grey;color:black;"));

    for(auto c : cardDisplayBtns)
    {
        c->setEnabled(true);
    }
    betBtn->setEnabled(false);
    betBtn->setStyleSheet(QStringLiteral("background-color:grey;color:black;"));
    maxBetBtn->setStyleSheet(QStringLiteral("background-color:grey;color:black;"));
    maxBetBtn->setEnabled(false);


    game->shuffle();
    game->dealNewHand();

    displayCardButtons();

    drawView();
}

void MainView::onDrawClick()
{
    drawBtn->setEnabled(false);
    drawBtn->setStyleSheet(QStringLiteral("background-color:grey;color:black;"));
    for(auto card : cardDisplayBtns)
    {
        card->setEnabled(false);
    }

    dealBtn->setEnabled(true);
    dealBtn->setStyleSheet(QStringLiteral("background-color:rgb(249, 252, 251);color:black;"));

    for(auto c : cardDisplayBtns)
    {
        if(!c->isHeld())
        {
            game->replaceCardAtN(c->getIndex());
        }
        c->setHeld(false);
    }

    game->winningHand();
    game->updateBalance();
    displayCardButtons();
    drawView();
    if(game->getLosingMessage() != "")
    {
        winningHand->setText(QString::fromStdString(game->getLosingMessage()));
    }
    else
    {
        winningHand->setText(QString::fromStdString(game->getWinningHand()));
    }
    game->delay(3500);
    resetTurn();
    drawView();

}

void MainView::drawView()
{
    betLabel->setText(QString("Bet: ") + QString::number(game->getBet()));
    balanceLabel->setText(QString("Balance: ") + QString::number(game->getBalance()));

    int tempBalance = game->getBalance();

    if(tempBalance == 0)
    {
        if(game->getBet() > game->getBalance())
        {
            maxBetBtn->setEnabled(false);
            betBtn->setEnabled(false);
        }

    }


    if(game->getBalance() < 0)
    {
        for(auto c : cardDisplayBtns)
        {

            CardPtr card = game->getCardAtN(c->getIndex());
            c->setEnabled(false);

            if(card->getColor() == CardColor::Red){
                c->setStyleSheet("border-image:url(:/images/Media/cardfrontGray.png); color: red;");
            }
            else{
                c->setStyleSheet("border-image:url(:/images/Media/cardfrontGray.png); color: black;");
            }
                c->setText(QString::fromStdString(card->toString()));
        }
    }


}

void MainView::displayCardButtons()
{

    for(auto c : cardDisplayBtns){
        c->setStyleSheet("border-image:url(:/images/Media/cardfront.png)");
        CardPtr card = game->getCardAtN(c->getIndex());
        if(card->getColor() == CardColor::Red){
            c->setStyleSheet("border-image:url(:/images/Media/cardfront.png); color: red;");
        }
        else{
            c->setStyleSheet("border-image:url(:/images/Media/cardfront.png); color: black;");
        }
            c->setText(QString::fromStdString(card->toString()));
    }
}

void MainView::resetTurn()
{

    if(game->getBalance() == 0)
    {
        game->setBalance(250);
    }

    for(auto c : cardDisplayBtns)
    {
        c->setStyleSheet("border-image:url(:/images/Media/cardbackred.png)");
        c->setText("");
    }

    maxBetBtn->setEnabled(true);
    betBtn->setEnabled(true);
    maxBetBtn->setStyleSheet(QStringLiteral("background-color:rgb(249, 252, 251);color:black;"));
    betBtn->setStyleSheet(QStringLiteral("background-color:rgb(249, 252, 251);color:black;"));
    dealBtn->setEnabled(false);
    dealBtn->setStyleSheet(QStringLiteral("background-color:grey;color:black;"));
    game->setBet(0);
    winningHand->setText("");
}
