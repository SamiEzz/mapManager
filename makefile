all : ./bin/api


./bin/api : ./src/main.c 
	gcc -o ./bin/api.exe ./src/main.c ./src/jsmn.c ./src/functions.c

