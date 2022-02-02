// Author: Devin Schafthuizen
// Class: CPSC-3750
// Date: Feb 1st/2022
// Problem1: Cannibal and Missionary
#include <iostream>
#include <queue>
#include "./People.h"

void BFS(GameState);

int main() {
  Location shore1("Start");
  Location shore2("end");
  Cannibal cannibal_Ken;
  Missionary Missionary_Marry;

  for(int i = 0; i < 3; i++) {
      shore1.addPerson(cannibal_Ken);
      shore1.addPerson(Missionary_Marry);
  }
  GameState game1(shore1, shore2);
  std::cout << "Searching for solution using BFS\n";
  BFS(game1);

  return 0;
}

void BFS(GameState world) {
  // Set up a queue
  Missionary Missionary_move;
  Cannibal cannibal_move;
  std::queue<GameState> game_state_queue;
  game_state_queue.push(world);
  GameState current;

  while(!game_state_queue.empty()) {
    // pop the front of the queue to inspect
    current = game_state_queue.front();
    game_state_queue.pop();

    // check current state for goal or failure
    if (current.goalState() == 1) {
      std::cout << "Solution found! \n\n";
      current.printActions();
      std::cout << "******* All people are accross the river!! ******* \n";
      break; // Breaks while loop immediately
    } else if (current.failedState() == true) {
      // move onto the next gamestate to inspect
      continue; // restart the while loop and discard current gamestate
    } else {
      if(current.boatAtStart() == 1) {
        GameState current2;
        current2 = current;
        current2.moveBoat();
        //************** Two Missionary move******************
        if (current2.start.Missionary_population.size() >= 2) {
          GameState move_MM;
          move_MM = current2;
          move_MM.start.removePerson(Missionary_move);
          move_MM.start.removePerson(Missionary_move);
          move_MM.end.addPerson(Missionary_move);
          move_MM.end.addPerson(Missionary_move);
          move_MM.addAction("Two Missionaries move to the other side\n");
          game_state_queue.push(move_MM);
        }

        //************** Two Cannibals move******************
        if(current2.start.cannibal_population.size() >= 2) {
          GameState move_CC;
          move_CC = current2;
          move_CC.start.removePerson(cannibal_move);
          move_CC.start.removePerson(cannibal_move);
          move_CC.end.addPerson(cannibal_move);
          move_CC.end.addPerson(cannibal_move);
          move_CC.addAction("Two Cannibals move to the other side\n");
          game_state_queue.push(move_CC);
        }

        //************** one of each move******************
        if(current2.start.cannibal_population.size() >= 1 &&
              current2.start.Missionary_population.size() >= 1) {
          GameState move_MC;
          move_MC = current2;
          move_MC.start.removePerson(Missionary_move);
          move_MC.start.removePerson(cannibal_move);
          move_MC.end.addPerson(Missionary_move);
          move_MC.end.addPerson(cannibal_move);
          move_MC.addAction("One missionary and one cannibal move to the other side\n");
          game_state_queue.push(move_MC);
        }
      } else { // Boat is not at start
        GameState move_M, move_MM, move_C, move_CC, move_MC;
        current.moveBoat();
        move_M = current;
        move_C = current;
        move_MC = current;

        // **************** One or two Missionaries return in boat*****************
        if(move_M.goalState() == 0 && move_M.end.Missionary_population.size() > 0) {
          move_M.start.addPerson(Missionary_move);
          move_M.end.removePerson(Missionary_move);
          move_MM = move_M;
          move_M.addAction("One Missionary returns to the start on the boat\n\n");
          game_state_queue.push(move_M);
          if (move_MM.end.Missionary_population.size() > 0) {
            move_MM.start.addPerson(Missionary_move);
            move_MM.end.removePerson(Missionary_move);
            move_MM.addAction("Two Missionaries return to the start on the boat\n\n");
            game_state_queue.push(move_MM);
          }
        }

        // ******************* One or two Cannibals return in boat *****************
        if(move_C.goalState() == 0 && move_C.end.cannibal_population.size() > 0) {
          move_C.start.addPerson(cannibal_move);
          move_C.end.removePerson(cannibal_move);
          move_CC = move_C;
          move_C.addAction("One Cannibal returns to the start on the boat\n\n");
          game_state_queue.push(move_C);
          if (move_CC.end.cannibal_population.size() > 0) {
            move_CC.start.addPerson(cannibal_move);
            move_CC.end.removePerson(cannibal_move);
            move_CC.addAction("Two cannibals return to the start on the boat\n\n");
            game_state_queue.push(move_CC);
          }
        }

        // ****************** One of each return in boat****************************
        if(move_MC.goalState() == 0 && move_MC.end.Missionary_population.size() > 0
            && move_MC.end.cannibal_population.size() > 0) {
          move_MC.start.addPerson(Missionary_move);
          move_MC.end.removePerson(Missionary_move);
          move_MC.start.addPerson(cannibal_move);
          move_MC.end.removePerson(cannibal_move);
          move_MC.addAction("One Missionary and one cannibal returns to the start on the boat\n\n");
          game_state_queue.push(move_MC);
        }
      } // End of boat not at start
    } // End of if else state check in BFS
  } // End of while loop
} // End of program
