// Devon McKee
// player.h
// Header file for player class for Chutes & Ladders Redux (p1)
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
  bool incrementChutes();
  bool incrementLadders();
  void setSpace(int num);
  void setName(std::string str);
  void reportChutesLadders();
  // post: reports number of chutes and ladders player has landed on
  void reset();
 private:
  static const int START_SPACE = 0;
  std::string name;
  int space;
  int chutes;
  int ladders;
};

#endif // player_h
