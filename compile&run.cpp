#include <stdio.h>
#include <string>
using namespace std;

void compileMachineCode() {
    // read code from program.txt
    string programCode = "+++%+";

    // traslate syntax into machine code
    string runMachineCode = "00100010001001100010";

    // output machine code to machineCode.txt

    return;
}

int registars[10] = {0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0};

void executeInstruction(string instruction) {
    // excecute the instruction
    return;
}

void printCurrentState(string instruction) {
    // print the instruction being executed
    // print the values of each registar
    return;
}

void runMachineCode() {
    // read code from machineCode.txt
    string instructions = "00100010001001100010"; // or array of instructions [0000, 0000, ....]

    // loop over each instruction
        executeInstruction("0010");
        printCurrentState("0010");

    return;
}

int main() {
    compileMachineCode();
    runMachineCode();
    return 0;
}

