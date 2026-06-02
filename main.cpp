#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Character {
protected:
    string name;
    int maxHealth;
    int currentHealth;
    int attackPower;

public:
    Character() : name("Default"), maxHealth(100), currentHealth(100), attackPower(10) {}

    Character(string n, int maxH, int attP) : name(n), maxHealth(maxH), currentHealth(maxH), attackPower(attP) {}

    virtual ~Character() {}

    bool isAlive() const {
        return currentHealth > 0;
    }

    void restoreHealth() {
        currentHealth = maxHealth;
    }

    virtual string getTeam() const = 0;

    virtual void attack(Character* target) {
        if (!isAlive() || !target->isAlive()) return;

        cout << name << " attacks " << target->getName() << " for " << attackPower << " standard damage." << endl;
        target->receiveAttack(attackPower);
    }

    virtual void receiveAttack(int damage) {
        currentHealth -= damage;
        if (currentHealth < 0) currentHealth = 0;
        cout << name << " takes " << damage << " damage. (Remaining HP: " << currentHealth << "/" << maxHealth << ")" << endl;
    }

    virtual void display() const {
        cout << name << " (" << getTeam() << ") - HP: " << currentHealth << "/" << maxHealth << ", ATK: " << attackPower;
    }

    string getName() const {
        return name;
    }
};

class Knight : public Character {
public:
    Knight(string n, int maxH, int attP) : Character(n, maxH, attP) {}

    string getTeam() const override {
        return "Hero";
    }

    void receiveAttack(int damage) override {
        if ((rand() % 100) < 60) {
            damage = static_cast<int>(damage * 0.8);
            cout << name << " triggered Holy Shield! Damage reduced by 20%." << endl;
        }
        Character::receiveAttack(damage);
    }
};

class Archer : public Character {
private:
    int arrows;

public:
    Archer(string n, int maxH, int attP) : Character(n, maxH, attP) {
        arrows = (rand() % 6) + 1;
    }

    string getTeam() const override {
        return "Hero";
    }

    void attack(Character* target) override {
        if (!isAlive() || !target->isAlive()) return;

        if (arrows > 0) {
            arrows--;
            int enhancedDamage = static_cast<int>(attackPower * 1.5);
            cout << name << " shoots a precise arrow! (1.5x Damage). Arrows remaining: " << arrows << endl;
            target->receiveAttack(enhancedDamage);
        }
        else {
            Character::attack(target);
        }
    }

    void display() const override {
        Character::display();
        cout << ", Arrows: " << arrows;
    }
};

class Orc : public Character {
public:
    Orc(string n, int maxH, int attP) : Character(n, maxH, attP) {}

    string getTeam() const override {
        return "Monster";
    }

    void receiveAttack(int damage) override {
        if ((rand() % 100) < 15) {
            cout << name << " swiftly dodged the incoming attack entirely!" << endl;
            return;
        }
        Character::receiveAttack(damage);
    }
};

class Goblin : public Character {
public:
    Goblin(string n, int maxH, int attP) : Character(n, maxH, attP) {}

    string getTeam() const override {
        return "Monster";
    }

    void attack(Character* target) override {
        if (!isAlive() || !target->isAlive()) return;

        if ((rand() % 4) == 0) {
            int doubleDamage = attackPower * 2;
            cout << name << " executes a vicious Sneak Attack! (Double Damage)" << endl;
            target->receiveAttack(doubleDamage);
        }
        else {
            Character::attack(target);
        }
    }
};

void battle(Character& a, Character& b) {
    if (a.getTeam() == b.getTeam()) {
        cout << "Battle skipped: Both characters belong to the " << a.getTeam() << " team." << endl;
        return;
    }

    cout << "=========================================" << endl;
    cout << "BATTLE STARTED: " << a.getName() << " VS " << b.getName() << endl;
    cout << "=========================================" << endl;

    Character* first = &a;
    Character* second = &b;

    if ((rand() % 2) == 0) {
        first = &b;
        second = &a;
    }

    cout << first->getName() << " won the initiative and attacks first!" << endl << endl;

    while (first->isAlive() && second->isAlive()) {
        cout << "[Turn: " << first->getName() << "]" << endl;
        first->attack(second);
        if (!second->isAlive()) break;
        cout << endl;

        cout << "[Turn: " << second->getName() << "]" << endl;
        second->attack(first);
        cout << endl;
    }

    Character* winner = first->isAlive() ? first : second;
    cout << "WINNER: " << winner->getName() << " wins the battle!" << endl;
    cout << "=========================================" << endl << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<Character*> characters;
    characters.push_back(new Knight("Arthur", 120, 15));
    characters.push_back(new Archer("Legolas", 90, 18));
    characters.push_back(new Orc("Thrall", 140, 12));
    characters.push_back(new Goblin("Styx", 75, 10));

    bool playAgain = true;

    while (playAgain) {
        for (auto* c : characters) {
            c->restoreHealth();
        }

        cout << "--- Available Characters in Dungeon ---" << endl;
        for (size_t i = 0; i < characters.size(); ++i) {
            cout << i + 1 << ". ";
            characters[i]->display();
            cout << endl;
        }
        cout << "---------------------------------------" << endl;

        int choice = 0;
        while (true) {
            cout << "Select your character by number (1-" << characters.size() << "): ";
            if (cin >> choice && choice >= 1 && choice <= static_cast<int>(characters.size())) {
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid index number." << endl;
        }

        Character* player = characters[choice - 1];
        cout << endl << "▶ You have selected to play as: " << player->getName() << endl << endl;

        bool survivedAll = true;

        for (auto* opponent : characters) {
            if (player == opponent) continue;
            if (player->getTeam() == opponent->getTeam()) continue;

            battle(*player, *opponent);

            if (!player->isAlive()) {
                survivedAll = false;
                break;
            }
            player->restoreHealth();
        }

        if (survivedAll) {
            cout << "VICTORY! You survived all opposing monsters in the dungeon!" << endl;
        }
        else {
            cout << "DEFEAT! You lost and perished in the depths of the dungeon." << endl;
        }

        char response;
        while (true) {
            cout << endl << "Do you want to play again? (y/n): ";
            cin >> response;

            if (response == 'y' || response == 'Y') {
                playAgain = true;
                break;
            }
            else if (response == 'n' || response == 'N') {
                playAgain = false;
                break;
            }
            else {
                cout << "Invalid response. Please enter 'y' for Yes or 'n' for No." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cout << endl;
    }

    for (auto* c : characters) {
        delete c;
    }

    return 0;
}
