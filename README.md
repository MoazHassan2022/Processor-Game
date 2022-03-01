# Processor-Game
It is a multiplayer game with serial communication between 2 PCs made with assembly language.

it has two modes:

Chat mode: the 2 players can chat with nice user friendly window with ability of backspacing and scrolling chat.

Game mode: it is a simulation of processor for each player with registers and memory.

The 2 players can type commands to be executed on opponent's processor and data is sent through serial port in the 2 PCs.

Goal is to put a certain value in opponent's any register with 2 levels of hardness, a forbidden character that each player chooses for the other and  power ups,

Four types of power ups are available:
a. Executing a command on your own processor (consumes 5 points)
b. Executing a command on your processor and your opponent processor at the same 
time (consumes 3 points)
c. Changing the forbidden character only once (consumes 8 points)
d. Clearing all registers at once. (Consumes 30 points and could be used only once).

The game also supports four types of errors:
a. Size mismatch
b. Memory to memory operation
c. Invalid register name
d. Incorrect addressing mode like “mov ax, [CX]”

The game supports inline chat within the game and a pop up game that shows up suddenlu during the game and it is a moving a ball and an arrow to shot the ball and if it is shot the player gets extra score.

Five addressing modes are supported.

Supported Commands are: 
[ADD-ADC-SUB-SBB-XOR-AND-OR-NOP-SHR-SHL-SAR-ROR-RCL-RCR-ROL]

It was a project for the college.


