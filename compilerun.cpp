#include <stdio.h>
#include <string>
#include <iostream>
#include <bitset>
#include <fstream>
using namespace std;

int registers[10] = {0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0}; //registers are assumed to be restricted to integer values; represented in decimal
int instructionLength = 4; //instruction length of 4 bits will be used to decode the instructions
int* ptr=registers; //pointer for executing instructions; initialized to memory location of registers[0]

int executeInstruction(string instruction) { //the function will return any outputs rather than printing them directly. printInstruction will handle printing the output
    if(instruction=="0000" && (ptr != registers + 9)  )
	{  // Move the pointer to the next element, if not at the end of the array
		ptr++;
		return *ptr;

	}
	else if(instruction=="0001" && (ptr != registers))
	{ // Move the pointer to the previous element, if not at the beginning of the array
		ptr--;	
		return *ptr;
	}
	else if(instruction=="0010")
	{ //increment location by 1
		(*ptr)++;
		return *ptr;		 
	}
	else if(instruction=="0011")
	{ //decrement location by 1
		(*ptr)--;
		return *ptr;
	}
	else if(instruction=="0100")
	{ 		
		 /** Get the value of the previous location of the pointer
		  *  and add pointer value to previous location value
		  **/   
		 if (ptr != registers)  
		 { 	
			*ptr += *(ptr - 1);
		 }
		return *ptr;

		//cout<<"Replace me!"<<endl;
	}
	else if(instruction=="0101")
	{ 
		 /** Get the value of the previous location of the pointer
		  *  and subtract pointer value to previous location value
		  **/
		if (ptr != registers)  
		{ 
			if(*ptr > *(ptr - 1)) 	
			{
				*ptr -= *(ptr - 1);
			}
		}
		return *ptr;

		//cout<<"Replace me!"<<endl;
	}
	else if(instruction=="0110")
	{ 
		//output (print) value at pointer
		return *ptr;
	}
	else if(instruction=="0111")
	{ //input and store previous value to location at pointer
		if (ptr != registers)   
		{  	
			*ptr = *(ptr - 1);
		}
		return *ptr;
		//cout<<"Replace me!"<<endl;
	}
	else if(instruction=="1000")
	{ 
		//store location value in pointer				
		return *ptr;
		cout<<"This just returns the value of pointer in current location!"<<endl;
	}
	else if(instruction=="1001")
	{ 
		//load pointer value to location 	
		return *ptr;
		cout<<"This is same as 0111!"<<endl;
	}
	else if(instruction=="1010")
	{ //OR pointer value and location value store in pointer value
		return *ptr;
		cout<<"this needs more clarification!"<<endl;
	}
	else if(instruction=="1011")
	{ //AND pointer value and location value store in pointer value

		return *ptr;
		cout<<"this needs more clarification! Can do the comparew with previous if we must"<<endl;
	}
	else if(instruction=="1100")
	{ //== equality check between pointer and location values
		return *ptr;
		cout<<"Same issue as above!"<<endl;
	}
	else if(instruction=="1101")
	{ 
		//if pointer value is 0 go to end of loop
		if( *ptr == 0){
			int* endPtr = registers + 10;
			// Move the pointer to the end of the array
    		ptr = endPtr;
		}
		return *ptr;
		//cout<<"Replace me!"<<endl;
	}
	else if(instruction=="1110")
	{ //end of loop
		int* endPtr = registers + 10;
		// Move the pointer to the end of the array
		ptr = endPtr;		
		return *ptr;
		//cout<<"Replace me!"<<endl;
	}
	else if(instruction=="1111")
	{ //go to end loop
		
		int* endPtr = registers + 10;
		// Move the pointer to the end of the array
		ptr = endPtr;		
		return *ptr;
		//cout<<"Replace me!"<<endl;
	}
	else
	{
		cout<<"The instruction was not valid binary"<<endl;
	}

    return -9999; //this means there is no output
}


void compileMachineCode() {
    // read code from program.txt
    string programCode = "+++%+";

    // traslate syntax into machine code
    string runMachineCode = "00100010001001100010";
	//instructionDecode(runMachineCode); //test output

    // output machine code to machineCode.txt
    std::ofstream outFile("machineCode.txt");
    // Write the string to the file
    outFile << runMachineCode;
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
	}else cout<<"	"<<endl;

    return;
}

int instructionCount(std::string machineCode,int instructionCodeLength){
	if(machineCode.length()%instructionCodeLength!=0){
		return -1; //error checking if we receive machine code of invalid length
	} else {
		return machineCode.length()/instructionCodeLength;
	}
}

void runMachineCode() {
    // read code from machineCode.txt
    string instructions = "00100010001001100010"; // or array of instructions [0000, 0000, ....]
    
    //get the total instruction count, for looping purposes and error checking
	int instCnt = instructionCount(instructions,instructionLength);
	if(instCnt==-1){
		cout << "The machine code is invalid length, silly!" << endl; //print error and return early
		return;
	}
    
    int programCounter = 0;
	int output=-9999;
    
    // set up output table
	cout<<"Instruction Count	Instruction	R0	R1	R2	R3	R4	R5	R6	R7	R8	R9	Program Output" <<endl;
	cout<<"---------------------------------------------------------------------------------------------------------------------------------------" <<endl;
	cout<<"n/a			n/a		"<<registers[0]<<"	"<<registers[1]<<"	"<<registers[2]<<"	"<<registers[3]<<"	"<<registers[4]<<"	"<<registers[5]<<"	"<<registers[6]<<"	"<<registers[7]<<"	"<<registers[8]<<"	"<<registers[9]<<endl;
    
	// loop over each instruction
	for(int i = 0; i < instCnt; i++){
		//grab current instruction
		string givenInstruction(instructions,programCounter,instructionLength);

		//take action based on instruction
		output=executeInstruction(givenInstruction);
		printCurrentState(givenInstruction,i,output);

		//move counter up to grab next instruction
		programCounter = programCounter + 4;
	}		

    return;
}

int main() {
    compileMachineCode();
    runMachineCode();
    return 0;
}

