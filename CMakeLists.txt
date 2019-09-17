cmake_minimum_required(VERSION 3.14)
project(FiveCrowns)

set(CMAKE_CXX_STANDARD 14)

add_executable(FiveCrowns main.cpp CardInterface.h Card.cpp Card.h Joker.cpp Joker.h CardCollection.h Deck.cpp Deck.h Round.cpp Round.h Hand.cpp Hand.h DrawPile.cpp DrawPile.h DiscardPile.cpp DiscardPile.h Game.cpp Game.h Player.cpp Player.h Human.cpp Human.h Computer.cpp Computer.h CardPile.cpp CardPile.h UI.cpp UI.h)