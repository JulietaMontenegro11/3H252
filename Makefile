run : bin/ajedrez
	./bin/ajedrez

bin/ajedrez : src/Animacion.cpp include/*.hpp
	@mkdir -p bin
	g++ -Iinclude -o bin/ajedrez src/Animacion.cpp -lftxui-component -lftxui-dom -lftxui-screen -lpthread
