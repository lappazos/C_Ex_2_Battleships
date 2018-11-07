CC=gcc
CFLAGS = -Wextra -Wall -Wvla -std=c99

# Executables

make: battleships.c battleships_game.c
	$(CC) $(CFLAGS) -o ex2 battleships_game.c battleships.c

# Object Files

battleships: battleships.c
	$(CC) $(CFLAGS) -c battleships.c

# Other Targets

clean:
	rm -f *.o ex2.exe