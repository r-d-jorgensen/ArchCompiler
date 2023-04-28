#include <stdio.h>
#include <string>
#include <iostream>
//#include <bitset>
#include <fstream>
//#include <vector>
// Include necessary libraries

using namespace std;
using namespace std;

int registers[10] = {0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0}; //registers are assumed to be restricted to integer values; represented in decimal
int instructionLength = 4; //instruction length of 4 bits will be used to decode the instructions
//get pointer register which is the first element of the array
int* pReg = registers; //initialized to memory location of registers[0]
int* ptr =  &registers[1] ; //pointer for executing instructions; initialized to memory location of registers[1]


int executeInstruction(string instruction, int &programCounter, bool &skipToLoopEnd, int &loopStart, int &instCnt) { //the function will return any outputs rather than printing them directly. printInstruction will handle printing the output

	//if ptr is in first location for some reason move pointer by 1
	//ptr = (ptr == pReg) ? ptr + 1 : ptr;

	if(instruction == "0000" && (ptr != &registers[1]) )
	{  // Move the pointer to the next element, if not at the end of the array
		ptr--;
	}
	else if(instruction == "0001" && (ptr != &registers[9]))
	{ // Move the pointer to the previous element, if not at the beginning of the non pointer register
		ptr++;
	}
	else if(instruction == "0010")
	{ //increment location by 1
		(*ptr)++;
	}
	else if(instruction =="0011")
	{ //decrement location by 1
		(*ptr)--;
	}
	else if(instruction =="0100")
	{
		//add pointer value to location value
		*ptr += *pReg;
	}
	else if(instruction=="0101")
	{
		//subtract pointer value to location value
		*ptr -= *pReg;
	}
	else if(instruction=="0110")
	{
		//output (print) value at pointer
		return *ptr;
	}
	else if(instruction=="0111")
	{
		//input and store value to location at pointer
		int input;
		cin >> input;
		*ptr = input;
	}
	else if(instruction=="1000")
	{
		//store location value in pointer
		*pReg = *ptr;
	}
	else if(instruction=="1001")
	{
		//load pointer value to location
		*ptr = *pReg;

	}
	else if(instruction=="1010")
	{
		//OR pointer value and location value store in pointer value
		if(*pReg||*ptr){
			*pReg = 1;
		}else{
			*pReg = 0;
		}
	}
	else if(instruction=="1011")
	{
		//AND pointer value and location value store in pointer value
		if(*pReg&&*ptr){
			*pReg = 1;
		}else{
			*pReg = 0;
		}
	}
	else if(instruction=="1100")
	{
		 //== equality check between pointer and location values
		if(*pReg==*ptr){
			*pReg = 1;
		}else{
			*pReg = 0;
		}
	}
	else if(instruction=="1101")
	{
		//if pointer value is 0 go to end of loop
		if(*pReg==0){
			skipToLoopEnd = 1;
		}else{
			loopStart = programCounter; //remember the start of the loop
		}

	}
	else if(instruction=="1110")
	{
		// end of loop
		if(skipToLoopEnd==1){//if we jumped forward to the end of loop, we don't need to repeat it
			skipToLoopEnd=0;
		}else{//otherwise, we need to return to the start of the loop
			instCnt+=((programCounter-loopStart)/4)+1; //loop end - loop start + 1 (+1 is so we add instructions for loop start AND end)
			programCounter=loopStart-4; //reset the program counter to the beginning of the loop (-4, since the for loop adds +4)
		}
	}
	else if(instruction=="1111")
	{
		//go to end loop (ckossler: is this like a "continue"? does this really mean restart loop? that's how I implementeed it)
		instCnt+=((programCounter-loopStart)/4)+1; //loop end - loop start + 1 (+1 is so we add instructions for loop start AND end)
		programCounter = loopStart-4;
	}
	else
	{
		cout<<"The instruction was not valid"<<endl;
	}

    return -9999; //this means there is no output
}


void compileMachineCode(string program) {

	//create output string
	string machineCode="";

	//set flag to ignore further characters if characters are within comments, !!
	bool ignore = 0;

	//convert assembly code in program to machinecode
	for (char c : program) {
	        switch (c) {
	            case '<':
	                if(ignore!=1){
	                	machineCode.append("0000");
	                }
	                break;
	            case '>':
	            	if(ignore!=1){
	            		machineCode.append("0001");
	            	}
	                break;
	            case '+':
	            	if(ignore!=1){
	            		machineCode.append("0010");
	            	}
	                break;
	            case '-':
	            	if(ignore!=1){
	            		machineCode.append("0011");
	            	}
	                break;
	            case '*':
	            	if(ignore!=1){
	            		machineCode.append("0100");
	            	}
	                break;
	            case '_':
	            	if(ignore!=1){
	            		machineCode.append("0101");
	            	}
	                break;
	            case '%':
	            	if(ignore!=1){
	            		machineCode.append("0110");
	            	}
	                break;
	            case '$':
	            	if(ignore!=1){
	            		machineCode.append("0111");
	            	}
	                break;
	            case '#':
	            	if(ignore!=1){
	            		machineCode.append("1000");
	            	}
	                break;
	            case '@':
	            	if(ignore!=1){
	            		machineCode.append("1001");
	            	}
	                break;
	            case '|':
	            	if(ignore!=1){
	            		machineCode.append("1010");
	            	}
	                break;
	            case '&':
	            	if(ignore!=1){
	            		machineCode.append("1011");
	            	}
	                break;
	            case '=':
	            	if(ignore!=1){
	            		machineCode.append("1100");
	            	}
	                break;
	            case '(':
	            	if(ignore!=1){
	            		machineCode.append("1101");
	            	}
	                break;
	            case ')':
	            	if(ignore!=1){
	            		machineCode.append("1110");
	            	}
	                break;
	            case '?':
	            	if(ignore!=1){
	            		machineCode.append("1111");
	            	}
	                break;
	            case '!':
	                ignore=!ignore; //flip the ignore flag
	                break;
	            default:
	                break; // Ignore other characters
	        }
	    }

    // output machine code to machineCode.txt
    ofstream outFile("machineCode.txt");
    // Write the string to the file
    outFile << machineCode;
    // Close the file
    outFile.close();
    return;
}


void printCurrentState(string instruction,int ct,int output) {
    // print the instruction being executed
    // print the values of each register
	cout<<ct<<"			"<<instruction<<"		"<<registers[0]<<"	"<<registers[1]<<"	"<<registers[2]<<"	"<<registers[3]<<"	"<<registers[4]<<"	"<<registers[5]<<"	"<<registers[6]<<"	"<<registers[7]<<"	"<<registers[8]<<"	"<<registers[9];
	if(output!=-9999){
		cout<<"	"<<output<<endl;
	}else{
		cout<<"	"<<endl;
	}

    return;
}

int instructionCount(std::string machineCode,int instructionCodeLength){
	if(machineCode.length()%instructionCodeLength!=0){
		return -1; //error checking if we receive machine code of invalid length
	} else {
		return machineCode.length()/instructionCodeLength;
	}
}

void runMachineCode(string fromMachine) {
    // read code from machineCode.txt
    string instructions = "00100010001001100010"; // or array of instructions [0000, 0000, ....]
    if (fromMachine !="")
	{
		instructions = fromMachine;
	}

    //get the total instruction count, for looping purposes and error checking
	int instCnt = instructionCount(instructions,instructionLength);
	if(instCnt==-1){
		cout << "The machine code is invalid length, silly!" << endl; //print error and return early
		return;
	}

	//initialize variables
    int programCounter = 0; //keeps track of current instruction to execute
	int output=-9999; //output of -9999 means there is no output; all other values are valid outputs
	bool skipToLoopEnd = 0; //flag indicating if an instruction should be skipped because the latest instruction was to skip to end of loop
	int loopStart = 0; //keeps track of most recent loop start

    // set up output table
	cout<<"Instruction Count	Instruction	R0(ptr)	R1	R2	R3	R4	R5	R6	R7	R8	R9	Program Output" <<endl;
	cout<<"--------------------------------------------------------------------------------------------------------------------------------------" <<endl;
	cout<<"n/a			n/a		"<<registers[0]<<"	"<<registers[1]<<"	"<<registers[2]<<"	"<<registers[3]<<"	"<<registers[4]<<"	"<<registers[5]<<"	"<<registers[6]<<"	"<<registers[7]<<"	"<<registers[8]<<"	"<<registers[9]<<endl;

	// loop over each instruction
	for(int i = 0; i < instCnt; i++){

		//grab current instruction
		string givenInstruction(instructions,programCounter,instructionLength);

		//skip next instruction if we are jumping to loop end and the next instruction does not signify end of current loop
		if(skipToLoopEnd==1&&givenInstruction!="1110"){
			programCounter = programCounter + 4;
			continue;
		}

		//take action based on instruction
		//cout<<"Instruction: "<<givenInstruction<<" Program Counter:" << programCounter << " Skip Flag:"<<skipToLoopEnd<< " Loop Start: " << loopStart << endl;
		output=executeInstruction(givenInstruction,programCounter,skipToLoopEnd,loopStart,instCnt);
		printCurrentState(givenInstruction,i,output);

		//move counter up to grab next instruction
		programCounter = programCounter + 4;
	}

    return;
}


// Define the opcode values for each instruction
/*
enum Opcode {
    MOVE_PTR_UP = 0b0000,          // < - move pointer up
    MOVE_PTR_DOWN = 0b0001,        // > - move pointer down
    INC_LOC = 0b0010,              // + - increment location by 1
    DEC_LOC = 0b0011,              // - - decrement location by 1
    ADD_PTR_TO_LOC = 0b0100,       // * - add pointer value to location value
    SUB_PTR_FROM_LOC = 0b0101,     // _ - subtract pointer value from location value
    PRINT_VAL = 0b0110,            // % - output (print) value at pointer
    READ_VAL = 0b0111,             // $ - input and store value to location at pointer
    STORE_LOC = 0b1000,            // # - store location value in pointer
    LOAD_LOC = 0b1001,             // @ - load pointer value to location
    OR_PTR_LOC = 0b1010,           // | - OR pointer value and location value, store in pointer value
    AND_PTR_LOC = 0b1011,          // & - AND pointer value and location value, store in pointer value
    CMP_PTR_LOC = 0b1100,          // = - check equality between pointer and location values
    LOOP_START = 0b1101,           // ( - if pointer value is 0, go to end of loop
    LOOP_END = 0b1110,             // ) - end of loop
    LOOP_EXIT = 0b1111             // ? - go to end loop
};

// Define the structure for an instruction

struct Instruction {
    Opcode opcode;
    int operand;

    Instruction(Opcode opcode, int operand = 0)
        : opcode(opcode), operand(operand) {}
};
*/
// Function to parse the program and convert it into instructions

/* ckossler: commenting this out because it does not provide output to a file. Rather than modify this directly,
 * I instead copied this to the compileMachineCode program and instead of saving to a vector, saved to a string
 *
vector<Instruction> parse_program(const string& program) {
    vector<Instruction> instructions;
    for (char c : program) {
        switch (c) {
            case '<':
                instructions.push_back(Instruction(MOVE_PTR_UP));
                break;
            case '>':
                instructions.push_back(Instruction(MOVE_PTR_DOWN));
                break;
            case '+':
                instructions.push_back(Instruction(INC_LOC));
                break;
            case '-':
                instructions.push_back(Instruction(DEC_LOC));
                break;
            case '*':
                instructions.push_back(Instruction(ADD_PTR_TO_LOC));
                break;
            case '_':
                instructions.push_back(Instruction(SUB_PTR_FROM_LOC));
                break;
            case '%':
                instructions.push_back(Instruction(PRINT_VAL));
                break;
            case '$':
                instructions.push_back(Instruction(READ_VAL));
                break;
            case '#':
                instructions.push_back(Instruction(STORE_LOC));
                break;
            case '@':
                instructions.push_back(Instruction(LOAD_LOC));
                break;
            case '|':
                instructions.push_back(Instruction(OR_PTR_LOC));
                break;
            case '&':
                instructions.push_back(Instruction(AND_PTR_LOC));
                break;
            case '=':
                instructions.push_back(Instruction(CMP_PTR_LOC));
                break;
            case '(':
                instructions.push_back(Instruction(LOOP_START));
                break;
            case ')':
                instructions.push_back(Instruction(LOOP_END));
                break;
            case '?':
                instructions.push_back(Instruction(LOOP_EXIT));
                break;
            //case '?':
                //instructions.push_back(Instruction(LOOP_EXIT));
                //break;
            default:
                break; // Ignore other characters
        }
    }
    return instructions;
}
*/

// Function to execute the program based on the instructions - Ckossler: I commented this out because there is already a function to do this which debola and I worked on

/*
void execute_program(const vector<Instruction>& program) {
    const int MEMORY_SIZE = 30000;
    vector<int> memory(MEMORY_SIZE, 0);
    int pointer = 0;
    vector<int> loop_stack;

    for (int pc = 0; pc < program.size(); pc++) {
        const Instruction& instruction = program[pc];
        switch (instruction.opcode) {
            case MOVE_PTR_UP:
                pointer--;
                break;
            case MOVE_PTR_DOWN:
                pointer++;
                break;
            case INC_LOC:
                memory[pointer]++;
                break;
            case DEC_LOC:
                memory[pointer]--;
                break;
            case ADD_PTR_TO_LOC:
                memory[pointer] += memory[pointer];
                break;
            case SUB_PTR_FROM_LOC:
                memory[pointer] -= memory[pointer];
                break;
            case PRINT_VAL:
                cout << memory[pointer];
                break;
            case READ_VAL:
                cin >> memory[pointer];
                break;
            case STORE_LOC:
                memory[pointer] = pointer;
                break;
            case LOAD_LOC:
                pointer = memory[pointer];
                break;
            case OR_PTR_LOC:
                memory[pointer] |= memory[pointer];
                break;
            case AND_PTR_LOC:
                memory[pointer] &= memory[pointer];
                break;
            case CMP_PTR_LOC:
                if (memory[pointer] == memory[memory[pointer]]) {
                    pc++;
                }
                break;
            case LOOP_START:
                if (memory[pointer] == 0) {
                    int loopDepth = 1;
                    while (loopDepth > 0) {
                        pc++;
                        if (pc >= program.size()) {
                            cerr << "Error: Unmatched '(' at instruction " << pc << endl;
                            return;
                        }
                        if (program[pc].opcode == LOOP_START) {
                            loopDepth++;
                        } else if (program[pc].opcode == LOOP_END) {
                            loopDepth--;
                        }
                    }
                } else {
                    loop_stack.push_back(pc);
                }
                break;
            case LOOP_END:
                if (memory[pointer] != 0) {
                    pc = loop_stack.back() - 1;
                } else {
                    loop_stack.pop_back();
                }
                break;
            case LOOP_EXIT:
                if (!loop_stack.empty()) {
                    pc = loop_stack.back() - 1;
                    loop_stack.pop_back();
                }
                break;
            default:
                break;
        }
    }
}
*/

string readInstruction(string filename) {
    // Open the file for reading
    std::ifstream inputFile(filename);

    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return "";
    }

    // Read the contents of the file into a string
    std::string contents((std::istreambuf_iterator<char>(inputFile)),
                          (std::istreambuf_iterator<char>()));

    // Close the file
    inputFile.close();
    return contents;
}

int main() {

	string program = readInstruction("program.txt"); //assumes program.txt is in same folder as exe
	if (program == ""){
		return 1;
	}

	//ckossler: commented the below out because execute_program was already handled in the scope of runMachineCode, and parse_program did not output to a file as expected.
		// vector<Instruction> parsed_program = parse_program(program);
		// execute_program(parsed_program);

	// Convert assembly to machine code and output to file
    compileMachineCode(program);

	//Read machine code
	string machineCode = readInstruction("machineCode.txt");
	if (machineCode == ""){
		//use Default
		machineCode = "00100010001001100010";
	}
    runMachineCode(machineCode); //machinecode
    return 0;
}

