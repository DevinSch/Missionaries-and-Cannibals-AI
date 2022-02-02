// Author: Devin Schafthuizen
// Class: CPSC-3750
// Date: Feb 1st/2022
// Problem1: Cannibal and Missionary
#include <vector>

/**
// Person Class structure
// Person can be Cannibal or Missionary
**/
class Person {
public:
  Person() {};
  std::string getType() {return type;}
  std::string type;
};

class Cannibal : public Person {
public:
  Cannibal() {type = "Cannibal";}
private:
};

class Missionary : public Person {
public:
  Missionary() {type = "Missionary";}
private:
};

/**
// Location Class structure
// 2 Locations start and end.
*/
class Location {
public:
  Location() {}
  Location(std::string name) {area = name;}

  Location & operator = (Location copy) {
    area = copy.area;
    this->cannibal_population.clear();
    this->Missionary_population.clear();
    while(!copy.cannibal_population.empty()) {
      cannibal_population.push_back(copy.cannibal_population.back());
      copy.cannibal_population.pop_back();
    }
    while(!copy.Missionary_population.empty()) {
      Missionary_population.push_back(copy.Missionary_population.back());
      copy.Missionary_population.pop_back();
    }
    return *this;
  }

  void addPerson(Person traveler) {
    if (traveler.getType() == "Cannibal") {
      cannibal_population.push_back(traveler);
    } else {
      Missionary_population.push_back(traveler);
    }
  }

  void removePerson(Person traveler) {
    if (traveler.getType() == "Cannibal") {
      cannibal_population.pop_back();
    } else {
      Missionary_population.pop_back();
    }
  }


  std::string area;
  std::vector<Person> cannibal_population;
  std::vector<Person> Missionary_population;
};

/**
// GameState class structure
// Each game state has the two location as well as there populations
*/
class GameState {
public:
  GameState() {}
  GameState(Location one, Location two) {
    start = one;
    end = two;
    boat_position = "Start";
  }

  GameState & operator = (GameState copy) {
    start = copy.start;
    end = copy.end;
    //previous = copy.previous;
    actions = copy.actions;
    boat_position = copy.boat_position;
    return *this;
  }

  bool failedState() {
    if (start.cannibal_population.size() > start.Missionary_population.size()
            && start.Missionary_population.size() != 0)
      return true;
    else if (end.cannibal_population.size() > end.Missionary_population.size()
            && end.Missionary_population.size() != 0)
      return true;
    else
      return false;
  }

  bool goalState() {
    if (end.cannibal_population.size() == 3 && end.Missionary_population.size() == 3)
      return true;
    else
      return false;
  }

  void printActions() {
    std::cout << "The moves in order to win were:\n";
    for (std::vector<std::string>::iterator it = actions.begin();
                it != actions.end(); ++it)
      std::cout << "- " << *it;
  }

  void addAction(std::string text) {actions.push_back(text);}

  bool boatAtStart() {
    if (boat_position == "Start") {
      return true;
    } else {
      return false;
    }
  }

  void moveBoat() {
    if (boat_position == "Start") {
      boat_position = "End";
    } else if (boat_position == "End") {
      boat_position = "Start";
    }
  }

  Location start;     // Starting position
  Location end;       // Ending position
private:
  std::string boat_position;
  std::vector<std::string> actions;
};
