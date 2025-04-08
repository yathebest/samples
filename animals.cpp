#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// Base Class Animal
class Animal {
private:
    const string name; // Animal's name
    int daysLived;     // Tracks how many days the animal has lived
public:
    // Default constructor
    Animal() {}
    // Constructor with name and days lived
    Animal(const string name, int daysLived) : name(name), daysLived(daysLived) {}
    // Copy constructor
    Animal(const Animal& other) : name(other.name), daysLived(other.daysLived) {}
    // Virtual destructor
    virtual ~Animal() {}
    // Returns the number of days lived
    int getDaysLived() {
        return daysLived;
    }
    // Returns the animal's name
    string getName() {
        return name;
    }
    // Prints name and days lived of an animal
    void sayName() {
        cout << "My name is " << name << ", days lived: " << daysLived << endl;
    }
    // Pure virtual method for attack
    virtual void attack(Animal& other) = 0;
    // Sets days lived
    void setDaysLived(int newValue) {
        if (newValue > 10) {
            cout << name << " has died of old days" << endl;
            daysLived = 0; // Marks the animal as dead
        } else {
            daysLived = newValue;
        }
    }
};

// Class Fish
class Fish : virtual public Animal {
public:
    Fish(const string name, int daysLived) : Animal(name, daysLived) {}
    // Fish's attack
    void attack(Animal& other) override {
        cout << "Fish is attacking" << endl;
        other.setDaysLived(0);
    }
};

// Class Bird
class Bird : virtual public Animal {
public:
    Bird(const string name, int daysLived) : Animal(name, daysLived) {}
    // Bird's attack
    void attack(Animal& other) override {
        cout << "Bird is attacking" << endl;
        other.setDaysLived(0);
    }
};

// Class Mouse
class Mouse : virtual public Animal {
public:
    Mouse(const string name, int daysLived) : Animal(name, daysLived) {}
    // Mouse's attack
    void attack(Animal& other) override {
        cout << "Mouse is attacking" << endl;
        other.setDaysLived(0);
    }
};

// Class BetterFish
class BetterFish : public Fish {
public:
    BetterFish(string name, int daysLived) : Animal(name, daysLived), Fish(name, daysLived) {}
    // Constructor from a regular Fish
    BetterFish(Fish& fish) : Animal(fish.getName(), fish.getDaysLived()), Fish(fish.getName(), fish.getDaysLived()) {}
    // BetterFish's attack
    void attack(Animal& other) override {
        cout << "BetterFish is attacking" << endl;
        other.setDaysLived(0);
    }
};

// Class BetterBird
class BetterBird : public Bird {
public:
    BetterBird(string name, int daysLived) : Animal(name, daysLived), Bird(name, daysLived) {}
    // Constructor from a regular Bird
    BetterBird(Bird& bird) : Animal(bird.getName(), bird.getDaysLived()), Bird(bird.getName(), bird.getDaysLived()) {}
    // BetterBird's attack
    void attack(Animal& other) override {
        cout << "BetterBird is attacking" << endl;
        other.setDaysLived(0);
    }
};

// Class BetterMouse
class BetterMouse : public Mouse {
public:
    BetterMouse(string name, int daysLived) : Animal(name, daysLived), Mouse(name, daysLived) {}
    // Constructor from a regular Mouse
    BetterMouse(Mouse& mouse) : Animal(mouse.getName(), mouse.getDaysLived()), Mouse(mouse.getName(), mouse.getDaysLived()) {}
    // BetterMouse's attack
    void attack(Animal& other) override {
        cout << "BetterMouse is attacking" << endl;
        other.setDaysLived(0);
    }
};

// Class Monster
class Monster : public BetterBird, public BetterFish, public BetterMouse {
public:
    // Constructor with name, always sets days lived to 1
    Monster(string name) : Animal(name, 1), BetterBird(name, 1), BetterFish(name, 1), BetterMouse(name, 1) {}
    // Constructor from an existing animal, sets days lived to 1
    Monster(Animal& animal) : Animal(animal.getName(), 1), BetterBird(animal.getName(), 1), BetterFish(animal.getName(), 1), BetterMouse(animal.getName(), 1) {}
    // Monster's attack
    void attack(Animal& other) override {
        cout << "Monster is attacking" << endl;
        other.setDaysLived(0);
    }
};

// Template Class Cage
template <typename T>
class Cage {
public:
    vector<unique_ptr<T>> list; // List of animals 
    // Adds an animal to the cage and sorts by days lived, then by name
    void addAnimal(unique_ptr<T> animal) {
        list.push_back(move(animal));
        sort(list.begin(), list.end(), [](const unique_ptr<T>& a, const unique_ptr<T>& b) {
            if (a->getDaysLived() == b->getDaysLived()) {
                return a->getName() < b->getName();
            } else {
                return a->getDaysLived() < b->getDaysLived();
            }
        });
    }
    // Checks  and removes dead animals
    void scan() {
        for (int i = 0; i < list.size(); i++) {
            if (list[i]->getDaysLived() > 10) {
                cout << list[i]->getName() << " has died of old days" << endl;
                remove(i);
                i--; 
            } else if (list[i]->getDaysLived() == 0) {
                remove(i);
                i--;
            }
        }
    }
    // Returns the name of the animal at position pos
    string getName(int pos) {
        return list[pos]->getName();
    }
    // Returns the days lived of the animal at position pos
    int getDaysLived(int pos) {
        return list[pos]->getDaysLived();
    }
    // Removes the animal at position pos
    void remove(int pos) {
        list.erase(list.begin() + pos);
    }
    // Destroys all animals in the cage
    void kill() {
        list.clear();
    }
    // Makes the animal at pos1 attack the animal at pos2
    void attack(int pos1, int pos2) {
        list[pos1]->attack(*list[pos2]);
        scan(); // Removes any dead animals after the attack
    }
    // Increments days lived for all animals by 1 and checks for deaths
    void add() {
        for (int i = 0; i < list.size(); i++) {
            list[i]->setDaysLived(getDaysLived(i) + 1);
        }
        scan();
    }
    // Checks if an animal exists at position pos
    bool isThere(int pos) {
        return (pos >= 0 && pos < list.size());
    }
    //Prints name and days lived of an animal
    void talk(int pos) {
        if (pos >= 0 && pos < list.size())
            list[pos]->sayName();
        else
            cout << "Animal not found" << endl;
    }
};

// Template Class Aquarium
template <typename T>
class Aquarium {
public:
    vector<unique_ptr<T>> list;
    // Adds an animal to the aquarium and sorts
    void addAnimal(unique_ptr<T> animal) {
        list.push_back(move(animal));
        sort(list.begin(), list.end(), [](const unique_ptr<T>& a, const unique_ptr<T>& b) {
            if (a->getDaysLived() == b->getDaysLived()) {
                return a->getName() < b->getName();
            } else {
                return a->getDaysLived() < b->getDaysLived();
            }
        });
    }
    // Removes the animal at position pos
    void remove(int pos) {
        list.erase(list.begin() + pos);
    }
    // Checks and removes dead animals
    void scan() {
        for (int i = 0; i < list.size(); i++) {
            if (list[i]->getDaysLived() > 10) {
                cout << list[i]->getName() << " has died of old days" << endl;
                remove(i);
                i--;
            } else if (list[i]->getDaysLived() == 0) {
                remove(i);
                i--;
            }
        }
    }
    // Destroys all animals 
    void kill() {
        list.clear();
    }
    // Makes the animal at pos1 attack the animal at pos2
    void attack(int pos1, int pos2) {
        list[pos1]->attack(*list[pos2]);
        scan();
    }
    // Returns the name of the animal at position pos
    string getName(int pos) {
        return list[pos]->getName();
    }
    // Returns the days lived of the animal at position pos
    int getDaysLived(int pos) {
        return list[pos]->getDaysLived();
    }
    // Increments days lived for all animals by 1 and checks for deaths
    void add() {
        for (int i = 0; i < list.size(); i++) {
            list[i]->setDaysLived(getDaysLived(i) + 1);
        }
        scan();
    }
    // Checks if an animal exists at position pos
    bool isThere(int pos) {
        return (pos >= 0 && pos < list.size());
    }
    // Prints name and days lived of an animal
    void talk(int pos) {
        if (pos >= 0 && pos < list.size())
            list[pos]->sayName();
        else
            cout << "Animal not found" << endl;
    }
};

// Prevents creating a Cage for Fish
template <>
class Cage<Fish> {
public:
    Cage() = delete;
};

// Prevents creating an Aquarium for Birds
template <>
class Aquarium<Bird> {
public:
    Aquarium() = delete;
};

// Class Freedom
template <typename T>
class Freedom {
public:
    vector<unique_ptr<T>> list;
    // Adds an animal to Freedom and sorts
    void addAnimal(unique_ptr<T> animal) {
        list.push_back(move(animal));
        sort(list.begin(), list.end(), [](const unique_ptr<T>& a, const unique_ptr<T>& b) {
            if (a->getDaysLived() == b->getDaysLived()) {
                return a->getName() < b->getName();
            } else {
                return a->getDaysLived() < b->getDaysLived();
            }
        });
    }
    // Checks and removes dead animals
    void scan() {
        for (int i = 0; i < list.size(); i++) {
            if (list[i]->getDaysLived() > 10) {
                cout << list[i]->getName() << " has died of old days" << endl;
                remove(i);
                i--;
            } else if (list[i]->getDaysLived() == 0) {
                remove(i);
                i--;
            }
        }
    }
    // Increments days lived
    void add() {
        for (int i = 0; i < list.size(); i++) {
            list[i]->setDaysLived(getDaysLived(i) + 1);
            if (auto monster = dynamic_cast<Monster*>(list[i].get())) {
                if (monster->getDaysLived() > 1) {
                    cout << monster->getName() << " has died of old days" << endl;
                    monster->setDaysLived(0); // Enforces Monster's 1-day lifespan
                }
            }
        }
        scan();
    }
    // Removes the animal at position pos
    void remove(int pos) {
        list.erase(list.begin() + pos);
    }
    // Returns the name of the animal at position pos
    string getName(int pos) {
        return list[pos]->getName();
    }
    // Checks if an animal exists at position pos
    bool isThere(int pos) {
        return (pos >= 0 && pos < list.size());
    }
    // Returns the days lived of the animal at position pos
    int getDaysLived(int pos) {
        return list[pos]->getDaysLived();
    }
    // Prints name and days lived of an animal
    void talk(int pos) {
        if (pos >= 0 && pos < list.size())
            list[pos]->sayName();
        else
            cout << "Animal not found" << endl;
    }
};

// Main Function main 
int main() {
    // Initialize containers for different animal types
    Cage<Mouse> cageMouse;
    Cage<BetterMouse> cageBetterMouse;
    Cage<Bird> cageBird;
    Cage<BetterBird> cageBetterBird;
    Aquarium<Fish> aquariumFish;
    Aquarium<BetterFish> aquariumBetterFish;
    Aquarium<Mouse> aquariumMouse;
    Aquarium<BetterMouse> aquariumBetterMouse;
    Freedom<Animal> freedom;
    int n;
    cin >> n;
    // Loop to process all commands
    for (int i = 0; i < n; i++) {
        string first;
        cin >> first;
        if (first == "CREATE") { //If received command is "CREATE"
            //Take the input values
            string type, name, in, container;
            int days;
            cin >> type >> name >> in >> container >> days;
            // Creates a new animal in the specified container
            if (type == "M") {
                if (container == "Cage") {
                    cageMouse.addAnimal(make_unique<Mouse>(name, days));
                } else if (container == "Aquarium") {
                    aquariumMouse.addAnimal(make_unique<Mouse>(name, days));
                } else {
                    freedom.addAnimal(make_unique<Mouse>(name, days));
                }
                Mouse(name, days).sayName();
            } else if (type == "B") {
                if (container == "Cage") {
                    cageBird.addAnimal(make_unique<Bird>(name, days));
                } else {
                    freedom.addAnimal(make_unique<Bird>(name, days));
                }
                Bird(name, days).sayName();
            } else if (type == "F") {
                if (container == "Aquarium") {
                    aquariumFish.addAnimal(make_unique<Fish>(name, days));
                } else {
                    freedom.addAnimal(make_unique<Fish>(name, days));
                }
                Fish(name, days).sayName();
            } else if (type == "BM") {
                if (container == "Cage") {
                    cageBetterMouse.addAnimal(make_unique<BetterMouse>(name, days));
                } else if (container == "Aquarium") {
                    aquariumBetterMouse.addAnimal(make_unique<BetterMouse>(name, days));
                } else {
                    freedom.addAnimal(make_unique<BetterMouse>(name, days));
                }
                BetterMouse(name, days).sayName();
            } else if (type == "BB") {
                if (container == "Cage") {
                    cageBetterBird.addAnimal(make_unique<BetterBird>(name, days));
                } else {
                    freedom.addAnimal(make_unique<BetterBird>(name, days));
                }
                BetterBird(name, days).sayName();
            } else if (type == "BF") {
                if (container == "Aquarium") {
                    aquariumBetterFish.addAnimal(make_unique<BetterFish>(name, days));
                } else {
                    freedom.addAnimal(make_unique<BetterFish>(name, days));
                }
                BetterFish(name, days).sayName();
            }
        } else if (first == "APPLY_SUBSTANCE") { //If received command is "APPLY_SUBSTANCE"
            //Take the input values
            string type, container;
            int pos;
            cin >> container;
            if (container == "Freedom") { //If received container is "Freedom"
                cin >> pos;
                cout << "Substance cannot be applied in freedom" << endl;
            } else { // Applies a substance
                cin >> type >> pos;
                if (type == "M") {
                    if (container == "Cage" && cageMouse.isThere(pos)) {
                        cageBetterMouse.addAnimal(make_unique<BetterMouse>(cageMouse.getName(pos), (cageMouse.getDaysLived(pos) + 1) / 2));
                        cageMouse.remove(pos);
                    } else if (container == "Aquarium" && aquariumMouse.isThere(pos)) {
                        aquariumBetterMouse.addAnimal(make_unique<BetterMouse>(aquariumMouse.getName(pos), (aquariumMouse.getDaysLived(pos) + 1) / 2));
                        aquariumMouse.remove(pos);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                } else if (type == "B") {
                    if (cageBird.isThere(pos) && container == "Cage") {
                        cageBetterBird.addAnimal(make_unique<BetterBird>(cageBird.getName(pos), (cageBird.getDaysLived(pos) + 1) / 2));
                        cageBird.remove(pos);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                } else if (type == "F") {
                    if (aquariumFish.isThere(pos) && container == "Aquarium") {
                        aquariumBetterFish.addAnimal(make_unique<BetterFish>(aquariumFish.getName(pos), (aquariumFish.getDaysLived(pos) + 1) / 2));
                        aquariumFish.remove(pos);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                } else if (type == "BM") {
                    if (container == "Aquarium" && aquariumBetterMouse.isThere(pos)) {
                        freedom.addAnimal(make_unique<Monster>(aquariumBetterMouse.getName(pos)));
                        aquariumBetterMouse.kill(); // Destroys all animals in the container
                    } else if (container == "Cage" && cageBetterMouse.isThere(pos)) {
                        freedom.addAnimal(make_unique<Monster>(cageBetterMouse.getName(pos)));
                        cageBetterMouse.kill();
                    } else {
                        cout << "Animal not found" << endl;
                    }
                } else if (type == "BF") {
                    if (aquariumBetterFish.isThere(pos) && container == "Aquarium") {
                        freedom.addAnimal(make_unique<Monster>(aquariumBetterFish.getName(pos)));
                        aquariumBetterFish.kill(); // Destroys all animals in the container
                    } else {
                        cout << "Animal not found" << endl;
                    }
                } else if (type == "BB") {
                    if (cageBetterBird.isThere(pos) && container == "Cage") {
                        freedom.addAnimal(make_unique<Monster>(cageBetterBird.getName(pos)));
                        cageBetterBird.kill(); // Destroys all animals in the container
                    } else {
                        cout << "Animal not found" << endl;
                    }
                }
            }
        } else if (first == "REMOVE_SUBSTANCE") { //If received command is "REMOVE_SUBSTANCE"
            //Take the input values
            string type, container;
            int pos;
            cin >> container;
            if (container == "Freedom") { //If received container is "Freedom"
                cin >> pos;
                cout << "Substance cannot be removed in freedom" << endl;
            } else { // Removes the substance
                cin >> type >> pos;
                if (type == "M" || type == "B" || type == "F") {
                    cout << "Invalid substance removal" << endl;
                } else if (type == "BB") {
                    if (cageBetterBird.isThere(pos) && container == "Cage") {
                        cageBird.addAnimal(make_unique<Bird>(cageBetterBird.getName(pos), cageBetterBird.getDaysLived(pos) * 2));
                        cageBetterBird.remove(pos);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                } else if (type == "BF") {
                    if (aquariumBetterFish.isThere(pos) && container == "Aquarium") {
                        aquariumFish.addAnimal(make_unique<Fish>(aquariumBetterFish.getName(pos), aquariumBetterFish.getDaysLived(pos) * 2));
                        aquariumBetterFish.remove(pos);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                } else if (type == "BM") {
                    if (cageBetterMouse.isThere(pos) && container == "Cage") {
                        cageMouse.addAnimal(make_unique<Mouse>(cageBetterMouse.getName(pos), cageBetterMouse.getDaysLived(pos) * 2));
                        cageBetterMouse.remove(pos);
                    } else if (aquariumBetterMouse.isThere(pos) && container == "Aquarium") {
                        aquariumMouse.addAnimal(make_unique<Mouse>(aquariumBetterMouse.getName(pos), aquariumBetterMouse.getDaysLived(pos) * 2));
                        aquariumBetterMouse.remove(pos);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                }
            }
        } else if (first == "ATTACK") { //If received command is "ATTACK"
            //Take the input values
            string type, container;
            int pos1, pos2;
            cin >> container;
            if (container == "Freedom") { //If received container is "Freedom"
                cin >> pos1 >> pos2;
                cout << "Animals cannot attack in Freedom" << endl;
            } else { // Makes one animal attack another
                cin >> type >> pos1 >> pos2;
                if (container == "Cage") {
                    if (type == "B" && cageBird.isThere(pos1) && cageBird.isThere(pos2)) {
                        cageBird.attack(pos1, pos2);
                    } else if (type == "BB" && cageBetterBird.isThere(pos1) && cageBetterBird.isThere(pos2)) {
                        cageBetterBird.attack(pos1, pos2);
                    } else if (type == "M" && cageMouse.isThere(pos1) && cageMouse.isThere(pos2)) {
                        cageMouse.attack(pos1, pos2);
                    } else if (type == "BM" && cageBetterMouse.isThere(pos1) && cageBetterMouse.isThere(pos2)) {
                        cageBetterMouse.attack(pos1, pos2);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                } else if (container == "Aquarium") {
                    if (type == "F" && aquariumFish.isThere(pos1) && aquariumFish.isThere(pos2)) {
                        aquariumFish.attack(pos1, pos2);
                    } else if (type == "BF" && aquariumBetterFish.isThere(pos1) && aquariumBetterFish.isThere(pos2)) {
                        aquariumBetterFish.attack(pos1, pos2);
                    } else if (type == "M" && aquariumMouse.isThere(pos1) && aquariumMouse.isThere(pos2)) {
                        aquariumMouse.attack(pos1, pos2);
                    } else if (type == "BM" && aquariumBetterMouse.isThere(pos1) && aquariumBetterMouse.isThere(pos2)) {
                        aquariumBetterMouse.attack(pos1, pos2);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                }
            }
        } else if (first == "TALK") { //If received command is "TALK"
            //Take the input values
            string type, container;
            int pos;
            cin >> container;
            // Prints name and days lived of an animal
            if (container == "Freedom") {
                cin >> pos;
                if (freedom.isThere(pos)) {
                    freedom.talk(pos);
                } else {
                    cout << "Animal not found" << endl;
                }
            } else { 
                cin >> type >> pos;
                if (container == "Cage") {
                    if (type == "M" && cageMouse.isThere(pos)) {
                        cageMouse.talk(pos);
                    } else if (type == "BM" && cageBetterMouse.isThere(pos)) {
                        cageBetterMouse.talk(pos);
                    } else if (type == "B" && cageBird.isThere(pos)) {
                        cageBird.talk(pos);
                    } else if (type == "BB" && cageBetterBird.isThere(pos)) {
                        cageBetterBird.talk(pos);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                } else if (container == "Aquarium") {
                    if (type == "M" && aquariumMouse.isThere(pos)) {
                        aquariumMouse.talk(pos);
                    } else if (type == "BM" && aquariumBetterMouse.isThere(pos)) {
                        aquariumBetterMouse.talk(pos);
                    } else if (type == "F" && aquariumFish.isThere(pos)) {
                        aquariumFish.talk(pos);
                    } else if (type == "BF" && aquariumBetterFish.isThere(pos)) {
                        aquariumBetterFish.talk(pos);
                    } else {
                        cout << "Animal not found" << endl;
                    }
                }
            }
        } else if (first == "PERIOD") { //If received command is "PERIOD"
            // Advances time by one day for all animals in all containers
            cageBird.add();
            cageBetterBird.add();
            cageMouse.add();
            cageBetterMouse.add();
            aquariumFish.add();
            aquariumBetterFish.add();
            aquariumMouse.add();
            aquariumBetterMouse.add();
            freedom.add();
        }
    }
}