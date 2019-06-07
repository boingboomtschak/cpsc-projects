// Devon McKee
// playerx.h
// Header file for player class for Chutes & Ladders Redux EC (p1x)
// 2019-1-17

#include <iostream>
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
 public:
  Player();
  Player(std::string str);
  std::string getName() const;
  int getSpace() const;
  bool getSkipped() const;
  bool incrementChutes();
  bool incrementLadders();
  bool incrementExtraTurns();
  bool incrementSkippedTurns();
  void setSpace(int num);
  void setName(std::string str);
  void setSkipped(bool skip);
  void reportInformation();
  // post: reports number of chutes and ladders player has landed on, as
  //       well as extra/skipped turns
  void reset();
 private:
  static const int START_SPACE = 0;
  std::string name;
  bool skipped;
  int space;
  int chutes;
  int ladders;
  int extraTurns;
  int skippedTurns;
};

#endif // player_h
