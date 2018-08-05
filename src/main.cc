#include <iostream>
#include <string>

#include "grid.h"
#include <stdexcept>

using namespace std;

bool TEXTONLY;
int STARTLEVEL = 0;
string SCRIPTFILE = "sequence.txt";
int SEED;

bool matchCommand(string command, string input, int upTo) {

    if (input.length() < (unsigned) upTo || input.length() > command.length()) {
        return false;
    }
    for (int i = 0; i < (signed) input.length(); ++i) {
        if (command[i] != input[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {


    for (int i = 1; i < argc; ++i){
      string flag = argv[i];
      if (flag == "-text"){
        TEXTONLY = true;
      }
      else if (flag == "-startlevel"){
        STARTLEVEL = stoi(argv[i+1]);
      }
      else if (flag == "-scriptfile"){
        SCRIPTFILE = argv[i+1];
      }
      else if (flag == "-seed"){
        SEED = stoi(argv[i+1]);
      }
    }

    Grid g = Grid(); // initialize the board
    cout << g; // print out the empty board
    try {

        // will have to set the level to 0 and start the game => make the first block appear
        // in the top left corner
        int repeat = 1;
        bool valid = true;

        while (true) {
            string cmd;
            cin >> cmd;
            if (isdigit(cmd[0])) {
                repeat = cmd[0] - 48;
                cmd = cmd.substr(1);
            }
            for (int j = 0; j < repeat; ++j) {

                // moving the block commands

                if (matchCommand("left", cmd, 3)) {
                    g.changeBlock("LEFT");
                } else if (matchCommand("right", cmd, 1)) {
                    g.changeBlock("RIGHT");
                } else if (matchCommand("down", cmd, 2)) {
                    g.changeBlock("DOWN");
                } else if (matchCommand("clockwise", cmd, 2)) {
                    g.changeBlock("CLOCKWISE");
                } else if (matchCommand("counterclockwise", cmd, 2)) {
                    g.changeBlock("COUNTERCLOCKWISE");
                } else if (matchCommand("drop", cmd, 2)) {
                    g.changeBlock("DROP");


                    // replace block commands
                } else if (cmd == "I") {
                    g.replaceBlock('I');
                    break;
                } else if (cmd == "J"){
                    g.replaceBlock('J');
                    break;
                } else if (cmd == "L"){
                    g.replaceBlock('L');
                    break;
                } else if (cmd == "S"){
                    g.replaceBlock('S');
                    break;
                } else if (cmd == "T"){
                    g.replaceBlock('T');
                    break;
                } else if (cmd == "Z"){
                    g.replaceBlock('Z');
                    break;
                } else if (cmd == "O"){
                    g.replaceBlock('O');
                    break;

                    // level commands
                } else if (matchCommand("levelup", cmd, 6)) {
                    g.levelUp();
                } else if (matchCommand("leveldown", cmd, 6)) {
                    g.levelDown();
                } else if (matchCommand("hint", cmd, 1)){
                    g.suggestHint();
                    repeat = 1;
                }else if (cmd == "restart"){
                    g.changeBlock("RESTART");
                } else {
                  cout << "INVALID COMMAND" << endl;
                  repeat = 1;
                  valid = false;
                }
                // will have to add the rest of the commands
            }
            if(valid){
             // print out a board each time an action is completed
            cout << g << endl;
          }

            valid = true;
            repeat = 1;
        }
    } catch (out_of_range ex) {
        cout << g;
        cout << ex.what() << endl;

    }
}
