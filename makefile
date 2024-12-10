hepsi : derle calistir

derle:
	g++ -I "./include" -c ./src/Kromozom.cpp -o ./lib/Kromozom.o
	g++ -I "./include" -c ./src/DNA.cpp -o ./lib/DNA.o
	g++ -I "./include" -c ./src/Gen.cpp -o ./lib/Gen.o
	g++ -I "./include" -o ./bin/main  ./lib/Kromozom.o ./lib/DNA.o ./lib/Gen.o ./src/main.cpp

calistir:
	./bin/main













	