__start__: obj __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -g -pedantic -std=c++17 -iquote inc
LDFLAGS=-Wall




interp: obj/main.o obj/LibInterface.o obj/Set4LibInterfaces.o obj/Scena.o obj/xmlinterp.o obj/klient.o obj/Configuration.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/LibInterface.o obj/Set4LibInterfaces.o obj/Scena.o  obj/xmlinterp.o obj/klient.o obj/Configuration.o -ldl -lxerces-c -pthread

obj/main.o: src/main.cpp inc/Interp4Command.hh inc/xmlinterp.hh  inc/AccessControl.hh inc/Configuration.hh inc/Port.hh inc/klient.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/Set4LibInterfaces.o: src/Set4LibInterfaces.cpp inc/Set4LibInterfaces.hh
	g++ -c ${CPPFLAGS} -o obj/Set4LibInterfaces.o src/Set4LibInterfaces.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh
	g++ -c ${CPPFLAGS} -o obj/Scena.o src/Scena.cpp

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh 
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/klient.o: src/klient.cpp inc/klient.hh  inc/AccessControl.hh
	g++ -c ${CPPFLAGS} -o obj/klient.o src/klient.cpp

obj/Configuration.o: src/Configuration.cpp inc/Configuration.hh 
	g++ -c ${CPPFLAGS} -o obj/Configuration.o src/Configuration.cpp

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
