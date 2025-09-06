#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// ===== Player Class =====
class Player {
public:
    string name;
    vector<string> clues;

    void addClue(const string &clue) {
        for (auto &c : clues) if (c == clue) return; // avoid duplicates
        clues.push_back(clue);
        cout << "\n[Clue Added]: " << clue << "\n";
    }

    void showInventory() {
        cout << "\n--- Your Inventory ---\n";
        if (clues.empty()) cout << "You have no clues yet.\n";
        else for (auto &c : clues) cout << "- " << c << "\n";
        cout << "----------------------\n";
    }

    bool hasClue(const string &clue) {
        for (auto &c : clues) if (c == clue) return true;
        return false;
    }

    int clueCount() { return clues.size(); }
};

// ===== Base Location Class =====
class Location {
public:
    virtual void visit(Player &player) = 0;
    virtual string name() = 0;
    virtual ~Location() {}
};

// ===== Crime Scene =====
class CrimeScene : public Location {
public:
    void visit(Player &player) override {
        cout << "\n==================== CRIME SCENE ====================\n";
        cout << "You arrive at the mayor's mansion. The room is chaotic with overturned furniture.\n";
        cout << "The fireplace is still warm and a shattered vase lies on the floor.\n";
        if (!player.hasClue("Mysterious Key")) {
            cout << "Searching carefully, you find a Mysterious Key and a clue pointing to a location:\n";
            player.addClue("Mysterious Key");
            int r = rand() % 2;
            if (r == 0) player.addClue("Torn Note: Library");
            else player.addClue("Footprints to River");
        } else {
            cout << "You have already collected all clues here.\n";
        }
        player.showInventory();
    }
    string name() override { return "Crime Scene"; }
};

// ===== Library =====
class Library : public Location {
public:
    void visit(Player &player) override {
        cout << "\n==================== LIBRARY ====================\n";
        cout << "You enter a grand library. The smell of old books fills the air.\n";
        if (!player.hasClue("Torn Note: Library")) {
            cout << "You don't have any clue leading you here yet. Explore elsewhere first.\n"; 
            return;
        }
        if (player.hasClue("Diary Hint Letter")) {
            cout << "You have already solved the diary puzzle.\n"; 
            return;
        }

        cout << "A dusty diary on a podium catches your eye. A number puzzle is scribbled inside: 4 3 1 2\n";
        int code;
        cout << "Enter the 4-digit code to unlock the diary: ";
        cin >> code;

        if (code == 3142) {
            cout << "Correct! Inside the diary, you find a letter hinting at the culprit's obsession with puzzles.\n";
            player.addClue("Diary Hint Letter");
        } else {
            cout << "Wrong code! The diary remains locked.\n";
        }
        player.showInventory();
    }
    string name() override { return "Library"; }
};

// ===== River =====
class River : public Location {
public:
    void visit(Player &player) override {
        cout << "\n==================== RIVER ====================\n";
        cout << "A misty river winds through the town. The water glimmers in the fading light.\n";
        if (!player.hasClue("Footprints to River")) {
            cout << "No clues lead you here yet. Explore other locations first.\n"; 
            return;
        }
        if (player.hasClue("River Hint Note")) {
            cout << "You have already solved the river riddle.\n"; 
            return;
        }

        cout << "You notice a floating note with a riddle:\n";
        cout << "\"I speak without a mouth and hear without ears. I have no body, but I come alive with wind. What am I?\"\n";
        cout << "Answer: ";
        string answer; cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

        if (answer == "echo") {
            cout << "Correct! The note reveals: 'The culprit loves puzzles.'\n";
            player.addClue("River Hint Note");
        } else {
            cout << "Incorrect. Try again later.\n";
        }
        player.showInventory();
    }
    string name() override { return "River"; }
};

// ===== NPC Class =====
class NPC {
public:
    string name;
    string hint;
    NPC(string n, string h) : name(n), hint(h) {}
    void talk() { cout << name << ": \"" << hint << "\"\n"; }
};

// ===== Suspect House =====
class SuspectHouse : public Location {
public:
    SuspectHouse(string c) : culprit(c) {}
    void visit(Player &player) override {
        cout << "\n==================== SUSPECT HOUSE ====================\n";
        cout << "You arrive at the suspect's house. It seems quiet, almost too quiet...\n";
        if (!player.hasClue("Mysterious Key")) {
            cout << "You need a key from the Crime Scene to enter.\n"; return;
        }
        if (player.hasClue("Confession Letter")) {
            cout << "You have already obtained the confession letter.\n"; return;
        }
        if (player.clueCount() < 3) {
            cout << "You need more clues before confronting the suspect.\n"; return;
        }

        cout << "Using the key, you unlock the door. Inside, a locked drawer waits for a code.\n";
        cout << "Enter the 4-digit code to open it (hint: same as diary: 3-1-4-2): ";
        int code; cin >> code;
        if (code == 3142) {
            cout << "Success! You find a Confession Letter revealing " << culprit << " as the culprit.\n";
            player.addClue("Confession Letter");
        } else {
            cout << "Wrong code! The drawer stays locked.\n";
        }
        player.showInventory();
    }
    string name() override { return "Suspect House"; }
private:
    string culprit;
};

// ===== Police Station =====
class PoliceStation : public Location {
public:
    PoliceStation(string c) : culprit(c) {}
    void visit(Player &player) override {
        cout << "\n==================== POLICE STATION ====================\n";
        cout << "Time to make your accusation!\n";
        cout << "1. Mr. Black\n2. Mrs. White\n3. Mr. Green\nChoice: ";
        int choice; cin >> choice;
        string accused = (choice==1?"Mr. Black": choice==2?"Mrs. White":"Mr. Green");

        if (accused == culprit && player.hasClue("Confession Letter")) {
            cout << "\nCongratulations Detective " << player.name << "! You solved the case!\n";
            cout << culprit << " is the culprit.\n";
        } else {
            cout << "\nWrong accusation or missing evidence! The case remains unsolved.\n";
        }
    }
    string name() override { return "Police Station"; }
private:
    string culprit;
};

// ===== Game Class =====
class Game {
public:
    void start() {
        srand(time(0));
        vector<string> suspects = {"Mr. Black", "Mrs. White", "Mr. Green"};
        culprit = suspects[rand() % 3];

        cout << "==============================\n";
        cout << "   WELCOME TO MYSTERY DETECTIVE\n";
        cout << "==============================\n";
        cout << "A valuable artifact has been stolen! Solve the case by exploring locations, talking to people, and collecting clues.\n";

        cout << "\nEnter your detective name: ";
        getline(cin, player.name);
        cout << "\nWelcome Detective " << player.name << "! Choose your path wisely.\n";

        // Initialize locations
        locations.push_back(new CrimeScene());
        locations.push_back(new Library());
        locations.push_back(new River());
        locations.push_back(new SuspectHouse(culprit));
        locations.push_back(new PoliceStation(culprit));

        // Initialize NPCs
        npcs.push_back(NPC("Old Butler", "I saw someone near the library last night."));
        npcs.push_back(NPC("Town Guard", "There were footprints leading to the river."));
        
        // Game loop
        int choice;
        while (true) {
            cout << "\n==================== LOCATIONS ====================\n";
            for (size_t i = 0; i < locations.size(); ++i)
                cout << i+1 << ". " << locations[i]->name() << "\n";
            cout << "6. Talk to NPC\n7. Show Inventory\n0. Exit\n";
            cout << "Where do you want to go? Choice: ";
            cin >> choice;

            if (choice == 0) { cout << "Exiting game. Goodbye!\n"; break; }
            else if (choice == 6) { talkToNPC(); }
            else if (choice == 7) { player.showInventory(); }
            else if (choice >=1 && choice <=5) { locations[choice-1]->visit(player); }
            else cout << "Invalid choice.\n";
        }

        // Cleanup
        for (auto loc : locations) delete loc;
    }
private:
    Player player;
    string culprit;
    vector<Location*> locations;
    vector<NPC> npcs;

    void talkToNPC() {
        cout << "\n--- People you can talk to ---\n";
        for (size_t i = 0; i < npcs.size(); ++i)
            cout << i+1 << ". " << npcs[i].name << "\n";
        cout << "Choice: ";
        int c; cin >> c;
        if (c >=1 && c <= (int)npcs.size()) npcs[c-1].talk();
        else cout << "Invalid choice.\n";
    }
};

// ===== Main =====
int main() {
    Game game;
    game.start();
    return 0;
}









