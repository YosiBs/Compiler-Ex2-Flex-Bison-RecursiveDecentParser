#TO RUN THE PROGRAM (in Linux) PLEASE FOLLOW THESE STEPS:
# 1. open Terminal (in the current folder).
# 2. type the command->		make
# 3. type the command->		make run

#Recursive descent parser

#Compiler
CC = gcc
#Flex command
FLEX = flex

#Input and output files
LEX_FILE = olympics.lex
LEX_OUTPUT = lex.yy.c
EXECUTABLE = olympics
#Object files
OBJECTS = olympics.o lex.yy.o  
#Test file
TEST_FILE = input_olympics.txt

#default target
all: $(EXECUTABLE)

#Flex target
$(LEX_OUTPUT): $(LEX_FILE)
	$(FLEX) $(LEX_FILE)

#Object targets
lex.yy.o : $(LEX_OUTPUT) olympics.h
	gcc -c $(LEX_OUTPUT)

olympics.o : olympics.c olympics.h
	gcc -c olympics.c

#Compile target
$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

#Clean target
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(LEX_OUTPUT)

#Run target
run: $(EXECUTABLE)
	./$(EXECUTABLE) $(TEST_FILE)

.PHONY: all clean run

