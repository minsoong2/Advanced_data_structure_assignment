# 💡 Advanced Data Structures Assignment - Fall 2022

## SIC, SIC/XE
: A hypothetical computer used to simplify the study of actual computer instructions.

- **8 bits** = 1 byte
- **3 consecutive Bytes** = 1 Word
- The lowest byte of the 3 bytes that make up a Word determines the address.

## 🌟 Architecture of SIC (Simplified Instructional Computer)

### 📘 Architecture of SIC - Registers (A, X, L, PC, SW)

- **A**: Used for basic arithmetic operations (Accumulator register).
- **X**: Stores and calculates addresses (Index register).
- **L**: Used for jumping to specific memory addresses and storing the return address (Linkage register).
  - SIC does not have a stack.
- **PC**: Contains the address of the next instruction to execute (Program Counter).
- **SW**: Contains a variety of information, such as carry or flags (Status Word register).

### 📘 Architecture of SIC - Data formats (Character, Integer)

- SIC does not support floating-point numbers. SIC/XE does support floating-point numbers.
- **Character**: 8 bits (ASCII).
- **Integer**: 24 bits (Managed with binary numbers).
  - Negative numbers are represented using 2's complement.

### 📘 Architecture of SIC - Instruction formats, Addressing mode

- **Instruction formats**: 24 bits.
  - 8 bits for opcode + 1 bit X + 15 bits for address.
- **Opcode**: Determines the command to be executed.
- **X**: A flag for Index-Address mode (1 indicates Index-Address mode, 0 indicates Direct Address mode).
- **Address**:
  - Direct Address = Direct address.
  - Index-Address = Address + X (Address of the index register).

### 🌟Instruction of SIC

#### 📘Load & Store Instructions

- `LDA α`: Loads the value of α into the A register.
- `LDX β`: Loads the value of β into the X register.
- `STA γ`: Stores the value of the A register into γ.
- `STX δ`: Stores the value of the X register into δ.

Note: Registers are 24 bits wide. To store a byte (8 bits), the leftmost 16 bits are truncated.

#### 📘Arithmetic & Logic Operations

- `ADD α`: Adds the value of α to the A register.
- `SUB α`: Subtracts the value of α from the A register.
- `MUL α`: Multiplies the A register by α.
- `DIV α`: Divides the A register by α.
- `AND β`: Performs a bitwise AND with the A register and β.
- `OR γ`: Performs a bitwise OR with the A register and γ.

#### 📘Comparison Instructions

- `COMP α`: Sets the condition code (CC) based on the comparison of the A register with α.
- `TIX`: Increments the X register by 1 and compares it with α, setting the condition code (CC) accordingly.

#### 📘Conditional Jumps

- `J α`: Jumps to the address specified by α.
- `JLT β`: Jumps to the address specified by β if CC is set to less than (<).
- `JGT γ`: Jumps to the address specified by γ if CC is set to greater than (>).
- `JEQ δ`: Jumps to the address specified by δ if CC is set to equal (==).

#### 📘Subroutine Linkage

- `JSUB READ`: Saves the current Program Counter (PC) to the Linkage register (L) for return and jumps to the subroutine at address READ.
- `RSUB`: Returns from the subroutine by restoring the PC from the Linkage register (L).

#### 📘I/O
The following commands are used for interacting with the INDEV (Input Device)

- `TD INDEV`: Tests the INDEV device and sets the condition code (CC).
  - `<`: Indicates that the device is ready.
  - `=`: Indicates that the device isn't ready.

- `RD INDEV`: Reads a 1-byte value from the INDEV and stores it in the rightmost byte of the accumulator (A).

- `WD INDEV`: Writes the value of the rightmost byte of the accumulator (A) as 1 byte to the INDEV.

### 📘Data Definition Instructions

- `BYTE`: Defines a byte of data, either as a character constant or hexadecimal constant.
- `WORD`: Defines a word-sized integer constant.
- `RESB`: Reserves the specified number of bytes.
- `RESW`: Reserves the specified number of words.

#### Examples

- `ALPHA RESW 1`: Reserves space for 1 word.
- `FIVE WORD 5`: Defines a word with the value of 5.
- `CHARZ BYTE C'Z'`: Defines a byte with the character constant 'Z'.
- `C1 RESB 1`: Reserves space for 1 byte.

## 🚀Assembler Implementation Requirements

The assembler program should be able to compile the given assembly language and produce object code. For example:

COPY START 2000  
LDA FIVE  
STA ALPHA  
LDCH CHARZ  
STCH C1  
ALPHA RESW 1  
FIVE WORD 5  
CHARZ BYTE C'EOF'  
C1 RESB 1  
END  


The assembler will generate an object program with the header, text, and end records.

## 🚀Submission Requirements

- The program must be written in C and should compile and run in a Linux environment.
- Makefile must be used for compilation.
- The submission should include a design document, revised design document, and program documentation.

## 🚀Evaluation

- The evaluation will be based on the successful compilation and execution of two input files and a presentation.

## 🚀Deadlines

- Design Document: November 14th
- Revised Design Document: November 18th
- Program Documentation: November 30th

## 🚀References

- For detailed understanding, refer to [Youngkyu's Blog on RESW](http://dev.youngkyu.kr/tag/RESW).
