#include "System/System.hpp"
#include "Particle/Particle.hpp"
#include "Functions/EulerDiscretizer.hpp"
#include "Functions/VerletDiscretizer.hpp"
#include "TreeNode/TreeNode.hpp"
#include <omp.h>

namespace NBodyEnv
{

  // TODO FIX TEMPLATE

  template <>
  void System<EulerDiscretizer>::addParticle(Particle particle)
  {
    _systemParticles.push_back(particle);
    _prevState.push_back(particle);
  }

  template <>
  const Particle &System<EulerDiscretizer>::getParticle(int index) const
  {
    return _systemParticles[index];
  }

  template <>
  void System<EulerDiscretizer>::printParticles() const
  {
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end(); iter++)
    {
      std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
    }
  }

  template <>
  void System<EulerDiscretizer>::compute()
  {
    // Save current state in a temp vector
    std::vector<NBodyEnv::Particle> tempState(_systemParticles);

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    // Reset forces
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      iter->setForce({0.0, 0.0, 0.0});
    }

    // boolean flag to make sure particle is updated in case all others have been absorbed
    bool updated = false;

    // OLD IMPLEMENTATION, CAUSED RACE CONDITIONS probably due to the fact that
    // inner loop starts from value i, which depends on the outer loop and is not thread safe
    //
    // #if defined(_OPENMP)
    // #pragma omp parallel for private(updated) schedule(static)
    // #endif
    //     for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    //     {
    //       // if (!_systemParticles[i].getVisible())
    //       //   continue;
    //       // updated = false;

    //       for (long unsigned int j = i + 1; j < _systemParticles.size(); ++j)
    //       {
    //         // if (!_systemParticles[j].getVisible())
    //         //   continue;
    //         _systemParticles[i].computeForce(_systemParticles[j], _func);
    //         // updated = true;
    //       }

    //       // if (!updated)
    //       // {
    //       //   // all particles have been absorbed by p1, therefore they are not visible ==> the computeForce method in the loop
    //       //   // above has not been called, and the force on p1 has not been updated ==> we need to update it here with a ghostParticle
    //       //   NBodyEnv::Particle ghostParticle(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
    //       //                                    {0.0, 0.0, 0.0}, 0, 0);
    //       //   _systemParticles[i].computeForce(ghostParticle, _func);
    //       //   // should use a break here, but it's not possible in openmp
    //       //   continue;
    //       // }
    //     }

#if defined(_OPENMP)
#pragma omp parallel for private(updated) schedule(static) /*collapse(2)*/
#endif
    for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    {
      if (!_systemParticles[i].getVisible())
        continue;
      updated = false;

      for (long unsigned int j = 0; j < _systemParticles.size(); ++j)
      {
        if (!_systemParticles[j].getVisible())
          continue;
        _systemParticles[i].computeForce(_systemParticles[j], _func);
        updated = true;
      }

      if (!updated)
      {
        // all particles have been absorbed by p1, therefore they are not visible ==> the computeForce method in the loop
        // above has not been called, and the force on p1 has not been updated ==> we need to update it here with a ghostParticle
        NBodyEnv::Particle ghostParticle(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                         {0.0, 0.0, 0.0}, 0, 0);
        _systemParticles[i].computeForce(ghostParticle, _func);
        // should use a break here, but it's not possible in openmp
        continue;
      }
    }

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    // need to decouple the update of the position and velocity from the
    // computation of the forces, for unknown reasons
    for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    {
      _discretizer.discretize(_systemParticles[i], _deltaTime);
    }
  }

  template <>
  void System<VerletDiscretizer>::addParticle(Particle particle)
  {
    _systemParticles.push_back(particle);
    _prevState.push_back(particle);
  }

  template <>
  const Particle &System<VerletDiscretizer>::getParticle(int index) const
  {
    return _systemParticles[index];
  }

  template <>
  void System<VerletDiscretizer>::printParticles() const
  {
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end(); iter++)
    {
      std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
    }
  }

  template <>
  void System<VerletDiscretizer>::compute()
  {
    // set number of threads
    // omp_set_num_threads(2);

    // Save current state in a temp vector
    std::vector<NBodyEnv::Particle> tempState(_systemParticles);
#if defined(_OPENMP)
#pragma omp parallel for
#endif
    // Reset forces
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      iter->setForce({0.0, 0.0, 0.0});
      // std::cout << "Number of threads: " << omp_get_num_threads() << "\n";
    }

    // boolean flag to make sure particle is updated in case all others have been absorbed
    bool updated = false;

    // OLD IMPLEMENTATION, CAUSED RACE CONDITIONS probably due to the fact that
    // inner loop starts from value i, which depends on the outer loop and is not thread safe
    //
    // #if defined(_OPENMP)
    // #pragma omp parallel for private(updated) schedule(static)
    // #endif
    //     for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    //     {
    //       if (!_systemParticles[i].getVisible())
    //         continue;
    //       updated = false;
    //       for (long unsigned int j = i + 1; j < _systemParticles.size(); ++j)
    //       {
    //         if (!_systemParticles[j].getVisible())
    //           continue;
    //         _systemParticles[i].computeForce(_systemParticles[j], _func);
    //         updated = true;
    //       }

    //       // if (!updated)
    //       // {
    //       //   // all particles have been absorbed by p1, therefore they are not visible ==> the computeForce method in the loop
    //       //   // above has not been called, and the force on p1 has not been updated ==> we need to update it here with a ghostParticle
    //       //   NBodyEnv::Particle ghostParticle(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
    //       //                                    {0.0, 0.0, 0.0}, 0, 0);
    //       //   _systemParticles[i].computeForce(ghostParticle, _func);
    //       //   // should use a break here, but it's not possible in openmp
    //       //   continue;
    //       // }
    //     }

#if defined(_OPENMP)
#pragma omp parallel for private(updated) schedule(static)
#endif
    for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    {
      if (!_systemParticles[i].getVisible())
        continue;
      updated = false;

      for (long unsigned int j = 0; j < _systemParticles.size(); ++j)
      {
        if (!_systemParticles[j].getVisible())
          continue;
        _systemParticles[i].computeForce(_systemParticles[j], _func);
        updated = true;
      }

      if (!updated)
      {
        // all particles have been absorbed by p1, therefore they are not visible ==> the computeForce method in the loop
        // above has not been called, and the force on p1 has not been updated ==> we need to update it here with a ghostParticle
        NBodyEnv::Particle ghostParticle(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                         {0.0, 0.0, 0.0}, 0, 0);
        _systemParticles[i].computeForce(ghostParticle, _func);
        // should use a break here, but it's not possible in openmp
        continue;
      }
    }

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    // need to decouple the update of the position and velocity from the
    // computation of the forces, for unknown reasons
    for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    {
      if (_prevState[i].getPos().xPos == 0 && _prevState[i].getPos().yPos == 0 && _prevState[i].getPos().zPos == 0)
      {
        _discretizer.updateFirsePos(_systemParticles[i], _deltaTime);
      }
      else
      {
        _discretizer.updatePos(_systemParticles[i], _prevState[i], _deltaTime);
      }
    }

    // Update previous state
    _prevState.clear();
    std::copy(tempState.begin(), tempState.end(), _prevState.begin());
  }
   template <>
  void System<EulerDiscretizer>::computeBH()
  {
    // Reset forces both in the system and in the root and insert particles in the root
    m_root.ResetNode(m_root.GetMax(), m_root.GetMin());

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      iter->setForce({0.0, 0.0, 0.0});
      m_root.InsertParticle(*iter, 0);
    }

    m_root.ComputeMass();

#if defined(_OPENMP)
#pragma omp parallel for schedule(static) /*collapse(2)*/
#endif
    for (int i = 0; i < m_root.GetNParticles(); ++i)
    {
      // std::cout << "Computing force for particle " << i << std::endl;
      std::vector<double> force = m_root.ComputeForce(_systemParticles[i]);
    }

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    // need to decouple the update of the position and velocity from the
    // computation of the forces, for unknown reasons
    for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    {
      _discretizer.discretize(_systemParticles[i], _deltaTime);
    }
  }

  template <>
  void System<VerletDiscretizer>::computeBH()
  {
    // Reset forces both in the system and in the root and insert particles in the root
    m_root.ResetNode(m_root.GetMax(), m_root.GetMin());

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      iter->setForce({0.0, 0.0, 0.0});
    }

    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      m_root.InsertParticle(*iter, 0);
    }


    m_root.ComputeMass();

#if defined(_OPENMP)
#pragma omp parallel for schedule(static) /*collapse(2)*/
#endif
    for (int i = 0; i < m_root.GetNParticles(); ++i)
    {
      // std::cout << "Computing force for particle " << i << std::endl;
      std::vector<double> force = m_root.ComputeForce(_systemParticles[i]);
    }

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    // need to decouple the update of the position and velocity from the
    // computation of the forces, for unknown reasons
    for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    {
      if (_prevState[i].getPos().xPos == 0 && _prevState[i].getPos().yPos == 0 && _prevState[i].getPos().zPos == 0)
      {
        _discretizer.updateFirsePos(_systemParticles[i], _deltaTime);
      }
      else
      {
        _discretizer.updatePos(_systemParticles[i], _prevState[i], _deltaTime);
      }
    }
  }


  template <>
  void System<RKDiscretizer>::addParticle(Particle particle)
  {
    _systemParticles.push_back(particle);
    _prevState.push_back(particle);
  }

  template <>
  const Particle &System<RKDiscretizer>::getParticle(int index) const
  {
    return _systemParticles[index];
  }

  template <>
  void System<RKDiscretizer>::printParticles() const
  {
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end(); iter++)
    {
      std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
    }
  }

  template <>
  void System<RKDiscretizer>::compute()
  {
    // Save current state in a temp vector
    std::vector<NBodyEnv::Particle> tempState(_systemParticles);

#if defined(_OPENMP)
#pragma omp parallel for
#endif
    // Reset forces
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      iter->setForce({0.0, 0.0, 0.0});
    }

    // boolean flag to make sure particle is updated in case all others have been absorbed
    bool updated = false;

#if defined(_OPENMP)
#pragma omp parallel for private(updated) schedule(static) /*collapse(2)*/
#endif
    for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    {
      if (!_systemParticles[i].getVisible())
        continue;
      updated = false;

      for (long unsigned int j = 0; j < _systemParticles.size(); ++j)
      {
        if (!_systemParticles[j].getVisible() || j == i)
          continue;
    
        _discretizer.discretize(_systemParticles[i], _systemParticles[j], Functions::getGravFunction(), _deltaTime);
        
        updated = true;
      }

      if (!updated)
      {
        // all particles have been absorbed by p1, therefore they are not visible ==> the computeForce method in the loop
        // above has not been called, and the force on p1 has not been updated ==> we need to update it here with a ghostParticle
        NBodyEnv::Particle ghostParticle(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                         {0.0, 0.0, 0.0}, 0, 0);
        _discretizer.discretize(_systemParticles[i], ghostParticle, Functions::getGravFunction(), _deltaTime);
        // should use a break here, but it's not possible in openmp
        continue;
      }
    }
  }

  // MPI
  template <>
  void System<RKDiscretizer>::computeMPI()
  {
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Master
    if (world_rank == 0) {
      // Save current state in a temp vector
      std::vector<NBodyEnv::Particle> tempState(_systemParticles);

      // Reset forces in parallel threads if compiled with openMP
      #if defined(_OPENMP)
      #pragma omp parallel for
      #endif
      for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
          iter++)
      {
        iter->setForce({0.0, 0.0, 0.0});
      }

      // Serialize particles
      std::string serialConversion;

      boost::iostreams::back_insert_device<std::string> inserter(serialConversion);
      boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
      boost::archive::binary_oarchive send_ar(s);

      send_ar << _systemParticles;
      s.flush();
      int len = serialConversion.size();

      // Send to others
      for (int i = world_rank + 1; i < world_size; i++) {
        MPI_Send( &len, 1, MPI_INT, i, 0, MPI_COMM_WORLD );
        MPI_Send( (void *)serialConversion.data(), len, MPI_BYTE, i, 0, MPI_COMM_WORLD );
      }
        
      // Receive from others
      for (int i = world_rank + 1; i < world_size; i++) {
        // Receive len
        int serialLen;
        MPI_Recv( &serialLen, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Receive data
        char data[len+1];
        MPI_Recv( data, len, MPI_BYTE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        data[len] = '\0';

        // Unserialize all
        std::vector<NBodyEnv::Particle> temp;
        boost::iostreams::basic_array_source<char> device(data, len);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
        boost::archive::binary_iarchive recv_ar(s);

        recv_ar >> temp;

        // Get positions
        int numParts = _systemParticles.size() / (world_size - 1); // As for workers. Master node doesn't work
        size_t initVec = numParts * (i - 1);
        size_t endVec = numParts * i - 1;

        // Last node has always endVec = end of the vector
        if(i == world_size - 1)
          endVec = _systemParticles.size() - 1;
        
        // Update 
        for(int j = initVec; j <= endVec; j++)
          _systemParticles[j] = temp[j - initVec];
        

        // End work
      }
    } else { // Others

      // Receive len
      int len;
      MPI_Recv( &len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      // Receive data
      char data[len+1];
      MPI_Recv( data, len, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      data[len] = '\0';

      // Unserialize all
      boost::iostreams::basic_array_source<char> device(data, len);
      boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
      boost::archive::binary_iarchive recv_ar(s);

      recv_ar >> _systemParticles;

      // Calculate number of particles
      int numParts = _systemParticles.size() / (world_size - 1); // Master node doesn't work

      // If the first node has numParts = 0 there are too few particles for the number all nodes.
      // All computation will be done by the first one
      if(numParts == 0 && world_rank == 1)
        numParts = _systemParticles.size();

      size_t initVec = numParts * (world_rank - 1);
      size_t endVec = numParts * world_rank - 1;

      // Last node has always endVec = end of the vector
      if(world_rank == world_size - 1)
        endVec = _systemParticles.size() - 1;

      
      // And now compute

      // boolean flag to make sure particle is updated in case all others have been absorbed
      bool updated = false;

      // Here we use also openmp. If the library is compiled with it, we are going to use multiprocessor (or multi-node
      // in a cluster) and multi-threading
      #if defined(_OPENMP)
      #pragma omp parallel for private(updated) schedule(static) /*collapse(2)*/
      #endif
      for (size_t i = initVec; i <= endVec; ++i)
      {
        if (!_systemParticles[i].getVisible())
          continue;
        updated = false;

        for (long unsigned int j = 0; j < _systemParticles.size(); ++j)
        {
          if (!_systemParticles[j].getVisible() || j == i)
            continue;
      
          _discretizer.discretize(_systemParticles[i], _systemParticles[j], Functions::getGravFunction(), _deltaTime);
          
          updated = true;
        }

        if (!updated)
        {
          // all particles have been absorbed by p1, therefore they are not visible ==> the computeForce method in the loop
          // above has not been called, and the force on p1 has not been updated ==> we need to update it here with a ghostParticle
          NBodyEnv::Particle ghostParticle(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                          {0.0, 0.0, 0.0}, 0, 0);
          _discretizer.discretize(_systemParticles[i], ghostParticle, Functions::getGravFunction(), _deltaTime);
          // should use a break here, but it's not possible in openmp
          continue;
        }
      }

      // Now we have to send contribute back to master
      // Extract only computed particles
      auto first = _systemParticles.begin() + initVec;
      auto last  = _systemParticles.begin() + endVec + 1;

      std::vector<Particle> toReturn(first, last);

      // Serialize vector
      std::string serialConversion;

      boost::iostreams::back_insert_device<std::string> inserter(serialConversion);
      boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s2(inserter);
      boost::archive::binary_oarchive send_ar(s2);

      send_ar << toReturn;
      s2.flush();
      len = serialConversion.size();

      // Send to master legnth of serialized string
      MPI_Send(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

      // Send to master serialized vector
      MPI_Send( (void *)serialConversion.data(), len, MPI_BYTE, 0, 0, MPI_COMM_WORLD );

      // Work ended
    }
  }
} // namespace NBodyEnv
