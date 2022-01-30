#include <vector>

/**
// Person Class structure
// Person can be Cannibal or Missionarie
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

class Missionarie : public Person {
public:
  Missionarie() {type = "Missionarie";}
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
    this->missionarie_population.clear();
    while(!copy.cannibal_population.empty()) {
      cannibal_population.push_back(copy.cannibal_population.back());
      copy.cannibal_population.pop_back();
    }
    while(!copy.missionarie_population.empty()) {
      missionarie_population.push_back(copy.missionarie_population.back());
      copy.missionarie_population.pop_back();
    }
    return *this;
  }

  int getPopulation() {
    return cannibal_population.size()
            + missionarie_population.size();}

  void addPerson(Person traveler) {
    if (traveler.getType() == "Cannibal") {
      cannibal_population.push_back(traveler);
    } else {
      missionarie_population.push_back(traveler);
    }
  }

  void removePerson(Person traveler) {
    if (traveler.getType() == "Cannibal") {
      cannibal_population.pop_back();
    } else {
      missionarie_population.pop_back();
    }
  }


  std::string area;
  std::vector<Person> cannibal_population;
  std::vector<Person> missionarie_population;
};
/*
class Vehicle : public Location {
public:
  Vehicle(std::string name, int max) {name = area; num_seats = max;}
private:
  std::vector<Person> seats;
  int num_seats;
};*/


/**
// GameState class structure
// Each game state has the two location as well as there populations
*/
class GameState {
public:
  GameState() {}

  GameState & operator = (GameState copy) {
    start = copy.start;
    end = copy.end;
    previous = copy.previous;
    actions = copy.actions;
    return *this;
  }

  void saveGameState(Location one, Location two) {
    start = one;
    end = two;
    //transport = three;
    previous = NULL;
  }

  bool failedState() {
    if (start.cannibal_population.size() > start.missionarie_population.size()
            && start.missionarie_population.size() != 0)
      return true;
    else if (end.cannibal_population.size() > end.missionarie_population.size()
            && end.missionarie_population.size() != 0)
      return true;
    else
      return false;
  }

  bool goalState() {
    if (end.cannibal_population.size() == 3 && end.missionarie_population.size() == 3)
      return true;
    else
      return false;
  }

  void setPreviousGameState(GameState* parent) {
    previous = parent;
  }

  void printActions() {
    std::cout << "The moves in order to win were:\n";
    for (std::vector<std::string>::iterator it = actions.begin();
                it != actions.end(); ++it)
      std::cout << "- " << *it;
  }

  void addAction(std::string text) {actions.push_back(text);}

  Location start;     // Starting position
  Location end;       // Ending position

private:
  //Location start;     // Starting position
  //Location end;       // Ending position
  //Location transport; // Do I need a location for a boat?
  std::vector<std::string> actions;
  GameState *previous;// Link to the gamestate that steamed this one
                      // If Null it is the root node
};
