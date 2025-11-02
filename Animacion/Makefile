run : bin/animacion
	./bin/animacion

bin/animacion : src/SolPlaneta.cpp include/*.hpp
	@mkdir -p bin
	g++ -Iinclude -o bin/animacion src/SolPlaneta.cpp -lftxui-component -lftxui-dom -lftxui-screen