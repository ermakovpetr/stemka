all:
	cd library && make
	cd convert && make
	cd example && make

clean:
	cd library && make clean
	cd convert && make clean
	cd example && make clean

clean_all:
	cd library && make clean_all
	cd convert && make clean_all
	cd example && make clean_all

