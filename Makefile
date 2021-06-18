T1 = Modelos_graficos
T2 = Build
CF = g++
OP = -O2 
LIBC=$(PWD)/Libs
PD=$(PWD)/Main
all: dir bld comp clean

dir: 
	mkdir -p $(T1) $(T2)

bld: dir 
	$(CF) -I $(LIBC) -c $(LIBC)/grafos.cpp
	$(CF) -I $(LIBC) -c $(LIBC)/modelos_graficos.cpp
	mv *.o $(T2)

comp: bld
	$(CF) -I $(LIBC) -o $(T1)/Modelos_graficos_exe $(PD)/grafos1.cpp $(T2)/*.o $(OP)


.PHONY: clean
clean:
	rm -r $(T2)
	clear

clean_all:
	rm -r $(T1)
	rm -r $(T2)
	clear