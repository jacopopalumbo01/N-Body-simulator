buildMPI:
	mpic++ example_mpi.cpp -I../../inc -L../../build -ln-body-sim -I${mkBoostInc} -L${mkBoostLib} -lboost_iostreams -lboost_serialization -o example_mpi.o
	mpicc example_speedup_MPI.cpp -fopenmp -I../../inc -L../../build -ln-body-sim -I${mkBoostInc} -L${mkBoostLib} -lboost_iostreams -lboost_serialization -o example_speedup_mpi.o

runMPI:
	mpirun -n 4 example_mpi.o

runSpeedupMPI:
	mpirun -n 8 example_speedup_mpi.o