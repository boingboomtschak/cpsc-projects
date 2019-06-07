// Devon McKee
// player.cpp
// Implementation of Player class as described in player.h

#include "player.h"

using namespace std;

Player::Player()
{
  name = "Unnamed";
  space = START_SPACE;
  chutes = 0;
  ladders = 0;
}

Player::Player(string str)
{
  name = str;
  space = START_SPACE;
  chutes = 0;
  ladders = 0;
}

string Player::getName() const
{
  return name;
}

int Player::getSpace() const
{
  return space;
}

bool Player::incrementChutes()
{
  chutes++;
  return true;
}

bool Player::incrementLadders()
{
  ladders++;
  return true;
}

void Player::setSpace(int num)
{
  space = num;
}

void Player::setName(string str)
{
  name = str;
}

void Player::reportChutesLadders()
{
  cout << name << " has landed on..\n";
  cout << chutes << " chutes and " << ladders << " ladders.\n";
}

void Player::reset()
{
  space = START_SPACE;
  chutes = 0;
  ladders = 0;
}
