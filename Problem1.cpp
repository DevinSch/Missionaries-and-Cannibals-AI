#include <iostream>
#include <queue>
#include "./People.h"

void BFS(GameState);
void test_Cases();

int main() {

  Location shore1("Start");
  Location shore2("end");

  Cannibal one;
  Cannibal two;
  Cannibal three;
  Missionary four;
  Missionary five;
  Missionary six;

  shore1.addPerson(one);
  shore1.addPerson(two);
  shore1.addPerson(three);
  shore1.addPerson(four);
  shore1.addPerson(five);
  shore1.addPerson(six);

  GameState game1;
  game1.saveGameState(shore1, shore2);
  //GameState start(shore1, shore2, boat);
  //test_Cases();
  BFS(game1);

  std::cout << "End of Program\n";
  return 0;
}

//Test_cases
void test_Cases() {
  Cannibal one;
  Cannibal two;
  Missionary three;
  Missionary four;

  std::cout << "Person one is a: " << one.getType() << "\n";
  std::cout << "Person two is a: " << two.getType() << "\n";
  std::cout << "Person three is a: " << three.getType() << "\n";
  std::cout << "Person four is a: " << four.getType() << "\n\n";

  Location shore1 ("Start");
  Location shore2 ("End");
  Location testshore ("test");

  shore1.addPerson(two);
  shore1.addPerson(one);
  shore1.addPerson(three);
  shore2.addPerson(four);
  //Vehicle boat("boat", 2);

  // Test removing a person
  //shore1.removePerson(two);
  //shore1.removePerson(three);

  GameState test;
  GameState test2;
  //test2.setPreviousGameState(&test);
  test.saveGameState(shore1, shore2);
  test2.saveGameState(testshore, shore2);
  std::cout << "Failed state? " << test.failedState() << "\n";
  std::cout << "Winning State? " << test.goalState() << "\n";
  std::cout << "Failed test state? " << test2.failedState() << "\n\n";

  std::cout << "shore1 current pop: " << shore1.getPopulation() << "\n";
  std::cout << "shore2 current pop: " << shore2.getPopulation() << "\n\n";

  std::cout << "Shore1 = " << shore1.area << "\n";
  std::cout << "Shore2 = " << shore2.area << "\n";
  std::cout << "After \n";
  shore2 = shore1;
  std::cout << "Shore1 = " << shore1.area << "\n";
  std::cout << "Shore2 = " << shore2.area << "\n";
  std::cout << "shore1 current pop: " << shore1.getPopulation() << "\n";
  std::cout << "shore2 current pop: " << shore2.getPopulation() << "\n\n";

}


// Start state 6 people on shore1
// 3 Cannibals and 3 Missionarys
// Goal state 6 people on shore2
// limitation Cannibals can never out number Missionarys
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
    std::cout << "Copy front of queue\n";
    game_state_queue.pop();
    std::cout << "pop the queue\n";
    std::cout << "queue length = " << game_state_queue.size() + 1 << "\n";

    std::cout << "M = " << current.start.Missionary_population.size() << "\n";
    std::cout << "C = " <<current.start.cannibal_population.size() << "\n";

    // check current state for goal or failure
    if (current.goalState() == 1) {
      std::cout << "Winner Winner \n\n";
      current.printActions();
      break; // Breaks while loop immediately
    } else if (current.failedState() == true) {
      // move onto the next gamestate to inspect
      std::cout << "Should have failed \n\n";
      continue; // restart the while loop
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
          move_MC.addAction("One Missionary and one Cannibal move to the other side\n");
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
          move_M.addAction("One Missionary returns to the start on the boat\n");
          game_state_queue.push(move_M);
          if (move_MM.end.Missionary_population.size() > 0) {
            move_MM.start.addPerson(Missionary_move);
            move_MM.end.removePerson(Missionary_move);
            move_MM.addAction("Two Missionaries return to the start on the boat\n");
            game_state_queue.push(move_MM);
          }
        }

        // ******************* One or two Cannibals return in boat *****************
        if(move_C.goalState() == 0 && move_C.end.cannibal_population.size() > 0) {
          move_C.start.addPerson(cannibal_move);
          move_C.end.removePerson(cannibal_move);
          move_CC = move_C;
          move_C.addAction("One Cannibal returns to the start on the boat\n");
          game_state_queue.push(move_C);
          if (move_CC.end.cannibal_population.size() > 0) {
            move_CC.start.addPerson(cannibal_move);
            move_CC.end.removePerson(cannibal_move);
            move_CC.addAction("Two cannibals return to the start on the boat\n");
            game_state_queue.push(move_CC);
          }
        }

        // ****************** One of each return in boat
        if(move_MC.goalState() == 0 && move_MC.end.Missionary_population.size() > 0
            && move_MC.end.cannibal_population.size() > 0) {
          move_MC.start.addPerson(Missionary_move);
          move_MC.end.removePerson(Missionary_move);
          move_MC.start.addPerson(cannibal_move);
          move_MC.end.removePerson(cannibal_move);
          move_MC.addAction("One Missionary and one cannibal returns to the start on the boat\n");
          game_state_queue.push(move_MC);
        }


      } // End of boat not at start
    } // End of if else state check in BFS
    std::cout << "End of while loop\n\n";
  } // End of while loop
} // End of program
