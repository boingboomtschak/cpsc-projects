// Devon McKee
// p5.cpp
// Card Game (p5)

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "stack.h"
#include "queue.h"

using namespace std;

const int MAX_PLAYERS = 2;
const int SHUFFLE_FACTOR = 4; // Described in shuffle()
const int CARD_MIN = 2; // Min card # (usually 2)
const int CARD_MAX = 13; // Max card # (usually 13)
const int START_HAND = 7; // # of cards in starting hand
const char YES = 'y';

void shuffle(Stack* &s);
// PRE: Stack of cards enters function
// POST: Function returns shuffled stack
int draw(Stack* &deck, Stack* &discard);
// PRE: Checks if deck is empty
// POST: Returns card after moving cards from discard-draw as necessary

int main()
{
  int num_players;
  int active_player;
  int winner;
  int active_card;
  int top_card;
  int draw_card;
  Queue* hands;
  Queue players;
  char cont = YES;
  bool running;
  Stack* deck;
  Stack* discard;
  srand(time(0));
  cout << "\033c";
  cout << "-=-=-=-=-=-=-=-=-\n";
  cout << "  Card Game (p5) \n";
  cout << "  By Devon McKee \n";
  cout << "-=-=-=-=-=-=-=-=-\n";
  cout << "\n";
  cout << "Welcome to Card Game!\n";
  while(cont == YES){
    deck = new Stack;
    discard = new Stack;
    num_players = -1; // Resets input validation test
    active_player = 0;
    running = true;
    for(int i=CARD_MIN; i<=CARD_MAX; i++){
      deck->push(i);
      deck->push(i);
      deck->push(i);
      deck->push(i);
    }
    shuffle(deck);
    cout << "How many players? (1-" << MAX_PLAYERS << ") ";
    while(num_players < 1 || num_players > MAX_PLAYERS){
      cin >> num_players;
      cin.ignore();
    }
    hands = new Queue[num_players];
    for(int i=0; i<num_players; i++){
      for(int j=0; j<START_HAND; j++){
        hands[i].enqueue(deck->pop());
      }
      players.enqueue(i);
    }
    cout << "\n";
    cout << "The game is ready to begin!\n";
    cout << "Press ENTER to begin..";
    cin.ignore();
    cout << "\n";
    while(running){
      cout << "It is player " << active_player+1 << "'s turn.\n";
      active_card = hands[active_player].dequeue();
      top_card = draw(deck, discard);
      cout << " PLAYER | DECK \n";
      cout << " " <<setw(6) << active_card << " | "
           << setw(4) << top_card << " \n"; 
      if(active_card > top_card){
        cout << "The player won!\n";
        discard->push(top_card);
      }else if(active_card == top_card){
        cout << "The player tied!\n";
        discard->push(top_card);
        cout << "The player draws 1 card.\n";
        draw_card = draw(deck, discard);
        hands[active_player].enqueue(draw_card);
      }else{
        cout << "The player lost!\n";
        discard->push(top_card);
        cout << "The player draws 2 cards.\n";
        draw_card = draw(deck, discard);
        hands[active_player].enqueue(draw_card);
        draw_card = draw(deck, discard);
        hands[active_player].enqueue(draw_card);
      }
      cout << "\n";
      discard->push(active_card);
      // check winner
      for(int i=0; i<num_players; i++){
        if(hands[i].isEmpty()){
          winner = i;
          running = false;
        }
      }
      if(active_player == (MAX_PLAYERS-1)){
        active_player = 0;
      }else{
        active_player++;
      }
      cout << "Press ENTER to end the turn..";
      cin.ignore();
      cout << "\n";
    }
    cout << "The winner is player " << winner+1 << "!\n";
    cout << "Congratulations!\n";
    delete[] hands;
    delete deck;
    delete discard;
    cout << "Would you like to play again? (y/n)";
    cin >> cont;
    cin.ignore();
  }
  cout << "\n";
  cout << "Thanks for playing Card Game!\n";
  cout << "Press ENTER to exit the game..";
  cin.ignore();
  return 0;
}

void shuffle(Stack* &s)
{
  // Determines # of stacks to push/pop in and out of when shuffling
  int shuffle = SHUFFLE_FACTOR;
  Stack* stacks = new Stack[shuffle];
  int random;
  bool run = true;
  while(!s->isEmpty()){
    random = (rand() % shuffle);
    stacks[random].push(s->pop());
  }
  while(run){
    random = (rand() % shuffle);
    if(!stacks[random].isEmpty()){
      s->push(stacks[random].pop());
    }
    run = false;
    for(int i=0; i<shuffle; i++){
      if(!stacks[i].isEmpty()){
        run = true;
      }
    }
  }
  delete[] stacks;
}

int draw(Stack* &deck, Stack* &discard)
{
  int card;
  if(deck->isEmpty()){
    while(!discard->isEmpty()){
      deck->push(discard->pop());
      shuffle(deck);
    }
    card = deck->pop();
  }else{
    card = deck->pop();
  }
  return card;
}
