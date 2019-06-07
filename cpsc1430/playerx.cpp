// Devon McKee
// playerx.cpp
// Implementation of Player class as described in playerx.h

#include "playerx.h"

using namespace std;

Player::Player()
{
  name = "Unnamed";
  space = START_SPACE;
  skipped = false;
  chutes = 0;
  ladders = 0;
  extraTurns = 0;
  skippedTurns = 0;
}

Player::Player(string str)
{
  name = str;
  space = START_SPACE;
  skipped = false;
  chutes = 0;
  ladders = 0;
  extraTurns = 0;
  skippedTurns = 0;
}

string Player::getName() const
{
  return name;
}

int Player::getSpace() const
{
  return space;
}

bool Player::getSkipped() const
{
  return skipped;
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

bool Player::incrementExtraTurns()
{
  extraTurns++;
  return true;
}

bool Player::incrementSkippedTurns()
{
  skippedTurns++;
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

void Player::setSkipped(bool skip)
{
  skipped = skip;
}

void Player::reportInformation()
{
  cout << name << " has landed on " << chutes << " chutes\n";
  cout << name << " has landed on " << ladders << " ladders\n";
  cout << name << " has gained " << extraTurns << " extra turns\n";
  cout << name << " has been skipped for " << skippedTurns << " turns\n";
}

void Player::reset()
{
  space = START_SPACE;
  chutes = 0;
  ladders = 0;
  extraTurns = 0;
  skippedTurns = 0;
}
