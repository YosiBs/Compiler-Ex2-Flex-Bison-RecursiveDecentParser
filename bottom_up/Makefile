#TO RUN THE PROGRAM (in Linux) PLEASE FOLLOW THESE STEPS:
# 1. open Terminal (in the current folder).
# 2. type the command->		make
# 3. type the command->		make run

#Compiler
CC = gcc
#Flex command
FLEX = flex
#Input and output files
LEX_FILE = olympics.lex
LEX_OUTPUT = lex.yy.c
EXECUTABLE = olympics
#Test file
TEST_FILE = input_olympics.txt
#Object files
OBJECTS = lex.yy.o olympics.tab.o

#default target
all: $(EXECUTABLE)

#Flex target
$(LEX_OUTPUT): $(LEX_FILE)
	$(FLEX) $(LEX_FILE)

#Bison target
olympics.tab.c olympics.tab.h: olympics.y
	bison -d olympics.y

lex.yy.o: $(LEX_OUTPUT) olympics.tab.h
	$(CC) -c $(LEX_OUTPUT)

#Compile target
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

olympics.tab.o: olympics.tab.c olympics.tab.h
	$(CC) -c olympics.tab.c

#Clean target
clean:
	rm -f $(EXECUTABLE) olympics.tab.c olympics.tab.h $(LEX_OUTPUT) $(OBJECTS)

#Run target
run: $(EXECUTABLE)
	./olympics $(TEST_FILE)

.PHONY: all clean run