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
  Missionarie four;
  Missionarie five;
  Missionarie six;

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
  Missionarie three;
  Missionarie four;

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
  test2.setPreviousGameState(&test);
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
// 3 Cannibals and 3 Missionaries
// Goal state 6 people on shore2
// limitation Cannibals can never out number Missionaries
void BFS(GameState world) {
  // Set up a queue
  Missionarie missionarie_move;
  Cannibal cannibal_move;
  std::queue<GameState> game_state_queue;
  game_state_queue.push(world);
  //game_state_queue.push(world);
  GameState current;

  while(!game_state_queue.empty()) {
    // pop the front of the queue to inspect
    current = game_state_queue.front();
    std::cout << "Copy front of queue\n";
    game_state_queue.pop();
    std::cout << "pop the queue\n";
    std::cout << "queue length = " << game_state_queue.size() << "\n";

    std::cout << "M = " << current.start.missionarie_population.size() << "\n";
    std::cout << "C = " <<current.start.cannibal_population.size() << "\n";

    // check current state for goal or failure
    if (current.goalState() == true) {
      std::cout << "Winner Winner \n\n";
      current.printActions();
      break; // Breaks while loop immediately
    } else if (current.failedState() == true) {
      // move onto the next gamestate to inspect
      std::cout << "Should have failed \n\n";
      continue; // restart the while loop
    } else {
      std::cout << "Do the other things here? Maybe\n";

      //************** Two Missionarie move******************
      if (current.start.missionarie_population.size() >= 2) {
        GameState move_MM;
        move_MM = current;
        move_MM.start.removePerson(missionarie_move);
        move_MM.start.removePerson(missionarie_move);
        move_MM.end.addPerson(missionarie_move);
        move_MM.end.addPerson(missionarie_move);
        move_MM.setPreviousGameState(&current);
        move_MM.addAction("Two Missionaries move to the other side\n");
        game_state_queue.push(move_MM);
      }

      //************** Two Cannibals move******************
      if (current.start.cannibal_population.size() >= 2) {
        GameState move_CC;
        move_CC = current;
        move_CC.start.removePerson(cannibal_move);
        move_CC.start.removePerson(cannibal_move);
        move_CC.end.addPerson(cannibal_move);
        move_CC.end.addPerson(cannibal_move);
        move_CC.setPreviousGameState(&current);
        move_CC.addAction("Two Cannibals move to the other side\n");
        game_state_queue.push(move_CC);
      }

      //************** one of each move******************
      if (current.start.cannibal_population.size() >= 1 &&
            current.start.missionarie_population.size() >= 1) {
        GameState move_MC;
        move_MC = current;
        move_MC.start.removePerson(missionarie_move);
        move_MC.start.removePerson(cannibal_move);
        move_MC.end.addPerson(missionarie_move);
        move_MC.end.addPerson(cannibal_move);
        move_MC.setPreviousGameState(&current);
        move_MC.addAction("One Missionarie and one Cannibal move to the other side\n");
        game_state_queue.push(move_MC);
      }


          // need to sort out how the boat will be returning
          // Also Maybe I should Implement the boat
          // Then maybe double check spelling
          // refactor and remove some unused code
    }
    // If the boat needs to return to start, do it here

    std::cout << "End of while loop\n\n";
  }

// Game should be over here
}
