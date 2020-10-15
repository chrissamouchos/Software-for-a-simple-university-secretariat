# paths
INCLUDE_PATH = ./include
SRC_PATH = ./src
OBJS_PATH = ./bin
INPUT = ./input

#Define the compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -I$(INCLUDE_PATH) -pg

#Define text inputs1 and 2
INPUT1 = input1.txt
INPUT2 = input2.txt
CONFIG = configfile.txt

#Define the dependencies
DEP = 	main.c \
		ADTHashtable.c \
		Student.c \
		Utils.c \
		ADTInvertedIndex.c

#Create the .o file with the needed functions
OBJS = $(patsubst %.c,$(OBJS_PATH)/%.o,$(DEP))

#UNLEASH THE FUll POWER OF VALGRIND!!!
FULLVAL = --leak-check=full -v

# The executable programm
EXEC = mngstd

build : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

#Run the programm with args1
run1: $(EXEC)
	./$(EXEC) -i $(INPUT)/$(INPUT1) -c $(CONFIG)

#Run the programm with args2
run2: $(EXEC)
	./$(EXEC) -i $(INPUT)/$(INPUT2) -c $(CONFIG)

#Determine full valgrind
fvalgrind: $(EXEC)
	valgrind $(FULLVAL) ./$(EXEC) -i $(INPUT)/$(INPUT1) -c $(CONFIG)

#Determine simple valgrind
svalgrind: $(EXEC)
	valgrind ./$(EXEC) -i $(INPUT)/$(INPUT1) -c $(CONFIG)

#Profile executed code for input1, then show analysis
profiling:
	{ \
	gprof $(EXEC) gmon.out > analysis.txt;\
	cat analysis.txt;\
	rm gmon.out;\
	echo y | command;\
	}

#Clean workspace
clean:
	{ \
	rm -f $(OBJS) $(EXEC);\
	rm -f gmon.out;  \
	}
