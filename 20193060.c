#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

extern char *optarg;

struct Address_Label_Opcode_Operand_Table { // This table helps output intermediate file.
	int address;
	char* label;
	char* opcode;
	char* operand;
}Table[100] = { {0, NULL, NULL, NULL}, };

struct Symbol_Table { // This table stores symbols and addresses corresponding to symbols.
	int address;
	char* symbol;
}Symbol_Table[] = { {0, NULL}, }; 

struct Store_Opcode_Table { // This table to store 2 bits of opcode corresponding to each instruction.
	char code_[3];
	char mnemonic_[6];
}Opcode_Table[6] = { {"00","START"}, {"33","LDA"}, {"44","STA"}, {"53","LDCH"}, {"57","STCH"}, {"00","END"} };

void Print_SymbolTable(int SymbolTable_Size) { // Print SymbolTable

	int cnt;

	for (cnt = 0; cnt < SymbolTable_Size; cnt++) { // Use Symbol_Table
		printf("%d %s\n", Symbol_Table[cnt].address, Symbol_Table[cnt].symbol);
	}

}

void Print_Intermediate_File(int Table_Size) { // Print Intermediatefile

	int cnt;

	for (cnt = 0; cnt < Table_Size; cnt++) { 
		if (0 == cnt) 
			printf("%s %s %s\n", Table[cnt].label, Table[cnt].opcode, Table[cnt].operand); // Print programname + opcode + operand(start address)
		else 
			printf("%d %s %s %s\n", Table[cnt].address, Table[cnt].label, Table[cnt].opcode, Table[cnt].operand);
			// Print address + label + opcode + operand
	}

}

void Print_H(int Object_Program_Length) { // Print Header Record

	printf("H^%s^%s%d^%s%d\n", Table[0].label, Opcode_Table[0].code_, Table[1].address, Opcode_Table[5].code_, Object_Program_Length);
	/*	
		Table[0].label -> programname, 
		Opcode_Table[0].code_ -> 2 bits of opcode corresponding to START / Table[1].address -> start address
		Opcode_Table[5].code_ -> 2 bits of opcode corresponding to END   / Object_Program_Length
	*/
}

void Print_T(int Text_Record_Length, int Intermediate_File_Length, int SymbolTable_Size) { // Print Text Record

	int cnt, cnt_, cnt__;
	printf("T^%s%d^%d", Opcode_Table[0].code_, Table[1].address, Text_Record_Length); 
	// Opcode_Table[0].code_ -> 2 bits of opcode corresponding to START / Table[1].address -> start address / Text_Record_Length

	for (cnt = 0; cnt < Intermediate_File_Length; cnt++) { // Print 2 bits of opcode corresponding to each instruction and address corresponding to the operand

		if (0 == strcmp(Table[cnt].opcode, Opcode_Table[1].mnemonic_)) {
			// EX) ** LDA FIVE -> Table.opcode = LDA, Opcode_Table.mnemonic_ = LDA
			printf("^");
			for (cnt_ = 0; cnt_ < SymbolTable_Size; cnt_++) {
				if (0 == strcmp(Table[cnt].operand, Symbol_Table[cnt_].symbol)) {
					// Table.operand = FIVE, Symbol_Table.symbol = FIVE
					printf("%s%d", Opcode_Table[1].code_, Symbol_Table[cnt_].address);
					// Opcode_Table.code_ (code of LDA) (2 bits of opcode corresponding to each instruction) -> 33
					// Symbol_Table.address (FIVE) (address corresponding to the operand) -> 2015
				}
			}
		}

		if (0 == strcmp(Table[cnt].opcode, Opcode_Table[2].mnemonic_)) {
			// EX) ** STA ALPHA -> Table.opcode = STA, Opcode_Table.mnemonic_ = STA
			printf("^");
			for (cnt_ = 0; cnt_ < SymbolTable_Size; cnt_++) {
				if (0 == strcmp(Table[cnt].operand, Symbol_Table[cnt_].symbol)) {
					// Table.operand = ALPHA, Symbol_Table.symbol = ALPHA
					printf("%s%d", Opcode_Table[2].code_, Symbol_Table[cnt_].address);
					// Opcode_Table.code_ (code of STA) (2 bits of opcode corresponding to each instruction) -> 44
					// Symbol_Table.address (ALPHA) (address corresponding to the operand) -> 2012
				}
			}
		}

		if (0 == strcmp(Table[cnt].opcode, Opcode_Table[3].mnemonic_)) {
			// EX) ** LDCH CHARZ -> Table.opcode = LDCH, Opcode_Table.mnemonic_ = LDCH
			printf("^");
			for (cnt__ = 0; cnt__ < Intermediate_File_Length; cnt__++) {
				if (0 == strcmp(Table[cnt].operand, Table[cnt__].label)) {
				// Table.operand = CHARZ, Table.label = CHARZ
					for (cnt_ = 0; cnt_ < SymbolTable_Size; cnt_++) {
						if (Table[cnt__].address == Symbol_Table[cnt_].address) {
							//Table.address = 2018, Symbol_Table.address = 2018
							printf("%s%d", Opcode_Table[3].code_, Symbol_Table[cnt_].address);
							// Opcode_Table.code_ (code of LDCH) (2 bits of opcode corresponding to each instruction) -> 53
							// Symbol_Table.address (CHARZ) (address corresponding to the operand) -> 2018
						}
					}
					break; // CHARZ CHARZ...
				}
			}
		}

		if (0 == strcmp(Table[cnt].opcode, Opcode_Table[4].mnemonic_)) {
			// EX) ** STCH C1 -> Table.opcode = STCH, Opcode_Table.mnemonic_ = STCH
			printf("^");
			for (cnt__ = 0; cnt__ < Intermediate_File_Length; cnt__++) {
				if (0 == strcmp(Table[cnt].operand, Table[cnt__].label)) {
				// Table.operand = C1, Table.label = C1
					for (cnt_ = 0; cnt_ < SymbolTable_Size; cnt_++) {
						if (Table[cnt__].address == Symbol_Table[cnt_].address) {
							//Table.address = 2019, Symbol_Table.address = 2019
							printf("%s%d", Opcode_Table[4].code_, Symbol_Table[cnt_].address);
							// Opcode_Table.code_ (code of STCH) (2 bits of opcode corresponding to each instruction) -> 57
							// Symbol_Table.address (C1) (address corresponding to the operand) -> 2019
						}
					}
					break; // C1 C1...
				}
			}
		}

	}

	for (cnt = 0; cnt < Intermediate_File_Length; cnt++) { // Print the values stored in memory in order (hexadicimal)

		if (0 == strcmp(Table[cnt].opcode, "WORD")) {
			printf("^%.6x", atoi(Table[cnt].operand)); // EX) FIVE WORD 5 -> 000005
		}

		if (0 == strcmp(Table[cnt].opcode, "BYTE")) {

			if ('C' == Table[cnt].operand[0]) { // EX) CHARZ BYTE C'EOF' -> 454f46
				// cnt_ = 2, cnt_ < (strlen(Table[cnt].operand) - 1) -> exclude C''

				if (2 == (strlen(Table[cnt].operand) - 1) % 3) { 
					for (cnt_ = 2; cnt_ < strlen(Table[cnt].operand) - 1; cnt_++) { // exclude C'', EX) C'EOF'
						if (2 == cnt_ % 3) {
							printf("^%x", Table[cnt].operand[cnt_]);
						}
						else {
							printf("%x", Table[cnt].operand[cnt_]);
						}
					}
				}
				else if (0 == (strlen(Table[cnt].operand) - 1) % 3) { 
					for (cnt_ = 2; cnt_ < strlen(Table[cnt].operand) - 1; cnt_++) { // exclude C'', EX) C'E'
						if (2 == cnt_ % 3) {
							printf("^%x", Table[cnt].operand[cnt_]);
						}
						else {
							printf("%x", Table[cnt].operand[cnt_]);
						}
					}
				}
				else {
					for (cnt_ = 2; cnt_ < strlen(Table[cnt].operand) - 1; cnt_++) { // exclude C'' EX) C'EO'
						if (2 == cnt_ % 3) {
							printf("^%x", Table[cnt].operand[cnt_]);
						}
						else {
							printf("%x", Table[cnt].operand[cnt_]);
						}
					}
				}

			}
			else if ('X' == Table[cnt].operand[0]) {

			}
			else {}

		}

	}

	printf("\n");
}

void Print_E() {

	printf("E^%s%d\n", Opcode_Table[0].code_, Table[1].address);
	// Opcode_Table[0].code_ -> 2 bits of opcode corresponding to START / Table[1].address -> start address
}

int main(int argc, char** argv)
{
	char code1[4][3] = { "33","44","53","57" };
	char mnemonic[6][6] = { "START","LDA","STA","LDCH","STCH","END" };
	char mnemonic1[4][5] = { "LDA","STA","LDCH","STCH" };
	int locctr, start, length, i = 0, j = 0, k = 0, l = 0, m = 0, n = 0;
	// locctr -> save address, start -> starting address, length -> Length of the input program
	// i -> Distinguishing labels, opcodes, and operands
	// j -> Table[j].label
	// k -> Table[k].opcode
	// l -> Table[l].operand
	// m helps store symbols and address in Symbol_Table, m -> SymbolTable_Size
	// n helps intermediate file output
	// n helps store the address in the address variable of Table, n -> Intermediate_File_Length
	int st, len, actual_len = 0, finaddr = 0;
	// st is a variable that determines whether it is an integer or a string
	// len is the size of memory
	// actual_len -> Text Recode Length
	// finaddr is the address of the last instruction
	
	FILE* p_file = NULL;
	
	int option = 0;
	while( (option = getopt(argc, argv, "i:")) != -1){
		
		switch(option)
		{
			case 'i': 
			p_file = fopen(optarg,"r+");
			break;
			
			default : 
			printf("Command is not valid.\n");
			printf("You must use the -i command\n");
			printf("Ex) ./20193060_exe -i inputfile\n");
			return 0;			
		}
		
	}
	
	char buffer[2000] = { 0, };
	char* p;
	start = 0, locctr = 0;

	if (NULL != p_file) { // Print file content

		fread(buffer, sizeof(buffer), 1, p_file);
		printf("The content of Input file:\n\n");
		printf("%s", buffer);
		printf("\n\n\n");

	}

	p = strtok(buffer, " \n\r"); // Tokenizing Strings with " ", "\n" and "\r"(carriage return)
	while (NULL != p) { // i -> Distinguishing labels, opcodes, and operands
	
	len = strlen(p) + 1; // len is the size of memory

		if (0 == i % 3) { // j is a variable that helps store the label in the label of Table

			Table[j].label = (char*)malloc(sizeof(len));
			Table[j].label = p;
			j++;

		}
		else if (1 == i % 3) { // k is a variable that helps store the opcode in the opcode of Table

			Table[k].opcode = (char*)malloc(sizeof(len));
			Table[k].opcode = p;
			// n helps store the address in the address variable of Table
			// n helps intermediate file output
			if (0 == strcmp(mnemonic[0], p)) { // START
				Table[n].address = 0; // No address at start
				n++;
				locctr = start;
			}
			else if (0 == strcmp(mnemonic[1], p)) { // LDA
				Table[n].address = locctr;
				n++;
				locctr += 3;
			}
			else if (0 == strcmp(mnemonic[2], p)) { // STA
				Table[n].address = locctr;
				n++;
				locctr += 3;
			}
			else if (0 == strcmp(mnemonic[3], p)) { // LDCH
				Table[n].address = locctr;
				n++;
				locctr += 3;
			}
			else if (0 == strcmp(mnemonic[4], p)) { // STCH
				Table[n].address = locctr;
				n++;
				locctr += 3;
			}
			else if (0 == strcmp(mnemonic[5], p)) {// END
				Table[n].address = locctr;
				n++;
				finaddr = locctr - 1; // finaddr is the address of the last instruction
			}
			else {}
			k++;
		}
		else {// l is a variable that helps store the operand in the operand of Table
			Table[l].operand = (char*)malloc(sizeof(len));
			Table[l].operand = p;

			st = atoi(p); // 1, 2000(constant, address) vs C1(variable), **
			if (st) { // if 'st' is an integer

				if (0 == start) {
					start = st; // start = 2000
					locctr = start; 
				}
				else {
					// n helps store the address in the address variable of Table
					// n helps intermediate file output
					// m helps store symbols and address in Symbol_Table
					if (0 == strcmp("WORD", Table[l].opcode)) {
						Table[n].address = locctr;
						n++;
						Symbol_Table[m].address = locctr;
						Symbol_Table[m].symbol = (char*)malloc(sizeof(len));
						Symbol_Table[m].symbol = Table[l].label;
						locctr += 3; // WORD -> 3byte
						m++;
					}
					else if (0 == strcmp("RESB", Table[l].opcode)) {
						Table[n].address = locctr;
						n++;
						Symbol_Table[m].address = locctr;
						Symbol_Table[m].symbol = (char*)malloc(sizeof(len));
						Symbol_Table[m].symbol = Table[l].label;
						locctr += atoi(Table[l].operand); // BYTE -> 1byte, 1 * atoi(Table[l].operand)
						m++;
					}
					else if (0 == strcmp("RESW", Table[l].opcode)) {
						Table[n].address = locctr;
						n++;
						Symbol_Table[m].address = locctr;
						Symbol_Table[m].symbol = (char*)malloc(sizeof(len));
						Symbol_Table[m].symbol = Table[l].label;
						locctr += atoi(Table[l].operand) * 3; // WORD -> 3byte, 3 * atoi(Table[l].operand)
						m++;
					}
					else {}

				}
			}
			else {// if 'st' is a string

				if (0 == strcmp("BYTE", Table[l].opcode)) {
					// n helps store the address in the address variable of Table
					// n helps intermediate file output
					// m helps store symbols and address in Symbol_Table
					if ('C' == Table[l].operand[0]) {
						Table[n].address = locctr;
						n++;
						Symbol_Table[m].address = locctr;
						Symbol_Table[m].symbol = (char*)malloc(sizeof(len));
						Symbol_Table[m].symbol = Table[l].label;
						m++;
						locctr += 1; // BYTE -> 1byte
					}
					else if ('X' == Table[l].operand[0]) {

					}
					else {}

				}

			}
			l++;
		}

		p = strtok(NULL, " \n\r");
		i++;
	}

	length = locctr - start; // length -> Length of the input program
	printf("Length of the input program is %d\n\n", length);

	printf("The contents of Symbol Table:\n\n");
	Print_SymbolTable(m); // m helps store symbols and address in Symbol_Table, m -> SymbolTableSize

	printf("\n\n\n");
	printf("The contents of Intermed File:\n\n");
	Print_Intermediate_File(n);
	// n helps store the address in the address variable of Table
	// n helps intermediate file output
	// n -> Intermediate_File_Length

	printf("\n\n\nObject Program has been generated.");
	printf("\n\n\nObject Program:");
	printf("\n\n\n");
	Print_H(locctr); // locctr is the Object_Program_Length at this point
	
	actual_len = finaddr - start; // actual_len -> Text Recode Length, finaddr is the address of the last instruction
	Print_T(actual_len, n, m);
	// n helps store the address in the address variable of Table
	// n helps intermediate file output
	// n -> Intermediate_File_Length
	// m helps store symbols and address in Symbol_Table, m -> SymbolTableSize

	Print_E();

	fclose(p_file);

	return 0;
}
