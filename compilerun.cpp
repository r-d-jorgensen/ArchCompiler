#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int registers[10] = {0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0}; //registers are assumed to be restricted to integer values; represented in decimal
const int instructionLength = 4; //instruction length of 4 bits will be used to decode the instructions
//get pointer register which is the first element of the array
int* pReg = registers; //initialized to memory location of registers[0]
int* ptr = &registers[1]; //pointer for executing instructions; initialized to memory location of registers[1]

//the function will return any outputs rather than printing them directly. printInstruction will handle printing the output
int executeInstruction(string instruction, int &programCounter, bool &skipToLoopEnd, int &loopStart, int &instCnt) {
	//if ptr is in first location for some reason move pointer by 1
	//ptr = (ptr == pReg) ? ptr + 1 : ptr;

	if (instruction == "0000" && (ptr != &registers[1]) )
	{  // Move the pointer to the next element, if not at the end of the array
		ptr--;
	}
	else if (instruction == "0001" && (ptr != &registers[9]))
	{ // Move the pointer to the previous element, if not at the beginning of the non pointer register
		ptr++;
	}
	else if (instruction == "0010")
	{ //increment location by 1
		(*ptr)++;
	}
	else if (instruction == "0011")
	{ //decrement location by 1
		(*ptr)--;
	}
	else if (instruction == "0100")
	{
		//add pointer value to location value
		*ptr += *pReg;
	}
	else if (instruction == "0101")
	{
		//subtract pointer value to location value
		*ptr -= *pReg;
	}
	else if (instruction == "0110")
	{
		//output (print) value at pointer
		return *ptr;
	}
	else if (instruction == "0111")
	{
		//input and store value to location at pointer
		int input;
		cin >> input;
		*ptr = input;
	}
	else if (instruction == "1000")
	{
		//store location value in pointer
		*pReg = *ptr;
	}
	else if (instruction == "1001")
	{
		//load pointer value to location
		*ptr = *pReg;

	}
	else if (instruction == "1010")
	{
		//OR pointer value and location value store in pointer value
		*pReg = (*pReg || *ptr) ? 1 : 0;
	}
	else if (instruction == "1011")
	{
		//AND pointer value and location value store in pointer value
		*pReg = (*pReg && *ptr) ? 1 : 0;
	}
	else if (instruction == "1100")
	{
		 //== equality check between pointer and location values		
		*pReg = (*pReg == *ptr) ? 1 : 0;
	}
	else if (instruction == "1101")
	{
		//if pointer value is 0 go to end of loop
		if(*pReg == 0)
        {
			skipToLoopEnd = 1;
		}
        else
        {
			loopStart = programCounter; //remember the start of the loop
		}

	}
	else if (instruction == "1110")
	{
		// end of loop
		if (skipToLoopEnd == 1)
        {//if we jumped forward to the end of loop, we don't need to repeat it
			skipToLoopEnd = 0;
		}
        else
        {//otherwise, we need to return to the start of the loop
			instCnt += ((programCounter-loopStart) / 4) + 1; //loop end - loop start + 1 (+1 is so we add instructions for loop start AND end)
			programCounter=loopStart-4; //reset the program counter to the beginning of the loop (-4, since the for loop adds +4)
		}
	}
	else if (instruction=="1111")
	{
		//go to end loop (ckossler: is this like a "continue"? does this really mean restart loop? that's how I implementeed it)
		instCnt+=((programCounter-loopStart)/4)+1; //loop end - loop start + 1 (+1 is so we add instructions for loop start AND end)
		programCounter = loopStart-4;
	}
	else
	{
		cout << "The instruction was not valid" << endl;
	}

    return -9999; //this means there is no output
}


void compileMachineCode(string program) {

	//create output string
	string machineCode="";

	//set flag to ignore further characters if characters are within comments, !!
	bool ignore = false;

	//convert assembly code in program to machinecode
	for (char c : program)
    {
        switch (c) {
            case '<':
                if (!ignore)
                {
                    machineCode.append("0000");
                }
                break;
            case '>':
                if (!ignore)
                {
                    machineCode.append("0001");
                }
                break;
            case '+':
                if (!ignore)
                {
                    machineCode.append("0010");
                }
                break;
            case '-':
                if (!ignore)
                {
                    machineCode.append("0011");
                }
                break;
            case '*':
                if (!ignore)
                {
                    machineCode.append("0100");
                }
                break;
            case '_':
                if (!ignore)
                {
                    machineCode.append("0101");
                }
                break;
            case '%':
                if (!ignore)
                {
                    machineCode.append("0110");
                }
                break;
            case '$':
                if (!ignore)
                {
                    machineCode.append("0111");
                }
                break;
            case '#':
                if (!ignore)
                {
                    machineCode.append("1000");
                }
                break;
            case '@':
                if (!ignore)
                {
                    machineCode.append("1001");
                }
                break;
            case '|':
                if (!ignore)
                {
                    machineCode.append("1010");
                }
                break;
            case '&':
                if (!ignore)
                {
                    machineCode.append("1011");
                }
                break;
            case '=':
                if (!ignore)
                {
                    machineCode.append("1100");
                }
                break;
            case '(':
                if (!ignore)
                {
                    machineCode.append("1101");
                }
                break;
            case ')':
                if (!ignore)
                {
                    machineCode.append("1110");
                }
                break;
            case '?':
                if (!ignore)
                {
                    machineCode.append("1111");
                }
                break;
            case '!':
                ignore = !ignore; //flip the ignore flag
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
	if (output != -9999)
    {
		cout<<"	"<<output<<endl;
	}
    else
    {
		cout<<"	"<<endl;
	}

    return;
}

int instructionCount(string machineCode, int instructionCodeLength)
{
	if(machineCode.length() % instructionCodeLength != 0)
    {
		return -1; //error checking if we receive machine code of invalid length
	}
    else
    {
		return machineCode.length()/instructionCodeLength;
	}
}

void runMachineCode(string fromMachine) {
    // read code from machineCode.txt
    string instructions = "00100010001001100010"; // or array of instructions [0000, 0000, ....]
    if (fromMachine != "")
	{
		instructions = fromMachine;
	}

    //get the total instruction count, for looping purposes and error checking
	int instCnt = instructionCount(instructions,instructionLength);
	if(instCnt == -1)
    {
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
		if(skipToLoopEnd ==1 && givenInstruction != "1110"){
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

string readInstruction(string filename) {
    // Open the file for reading
    ifstream inputFile(filename);

    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return "";
    }

    // Read the contents of the file into a string
    string contents((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));

    // Close the file
    inputFile.close();
    return contents;
}

int main()
{

	string program = readInstruction("program.txt"); //assumes program.txt is in same folder as exe
	if (program == ""){
		return 1;
	}

	// Convert assembly to machine code and output to file
    compileMachineCode(program);

	//Read machine code
	string machineCode = readInstruction("machineCode.txt");
	if (machineCode == "")
    {
		return -1;
	}
    runMachineCode(machineCode); //machinecode
    return 0;
}
