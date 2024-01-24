buildMPI:
	mpic++ example_mpi.cpp -I../../inc -L../../build -ln-body-sim -I${mkBoostInc} -L${mkBoostLib} -lboost_iostreams -lboost_serialization -o example_mpi.o

runMPI:
	mpirun -n 4 test.o