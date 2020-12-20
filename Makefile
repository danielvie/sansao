# CONFIGURANDO FLAGS COMPILADOR
CXX           = g++
CC            = gcc

INCLUDE       = -Isrc/lib
DECLARE       = 

CFLAGS	      = -O0 -g -Wall ${INCLUDE} ${DECLARE}
CXXFLAGS	  = -O0 -g -Wall ${INCLUDE} ${DECLARE}
LDFLAGS 	  = 

# DEFININDO NOME LIB 'python' E 'exe'
app           = main.exe

# LENDO ARQUIVOS
src           = $(wildcard src/*.c*)

# AJUSTANDO 'src' E 'obj'
obj           = $(addsuffix .o,$(basename $(src:src/%=obj/%)))

# LEIS DE COMPILACAO
all: r

r: run

i: init

p: 
	@echo -----------------------------
	@echo ${src}
	@echo -----------------------------
	@echo ${obj}
	@echo -----------------------------

# AJUSTANDO FLAGS 'python'
lib: ${pyd}

# COMPILACAO 'app {exe}'
${app}: ${obj}
	$(CXX) -o ${app} ${obj}

# ESCREVENDO '*.o' EM 'obj'
obj/%.o : src/%.cpp
	$(CXX) ${CXXFLAGS} -o $@ -c $<

# MONITORANDO ALTERACOES '.h' IMPORTANTES
# obj/teste.o : src/teste.h

# INICIALIZANDO PASTAS
init: 
	mkdir obj src
	printf "#include <iostream>\n\n" > src/main.cpp
	printf "int main(int argc, char const *argv[]) {\n\n" >> src/main.cpp
	printf "	std::cout << \"-----------------------------------------\\n\";\n" >> src/main.cpp
	printf "	std::cout << \"hello\\n\";\n" >> src/main.cpp
	printf "	return 0;\n" >> src/main.cpp
	printf "}" >> src/main.cpp

# EXECURANDO 'exe'
run: ${app}
	${app}

# LIMPANDO OBJETOS
clean: 
	rm obj/*