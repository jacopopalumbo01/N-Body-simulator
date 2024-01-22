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

    // boolean flag to make sure particle is updated in case all others have been absorbed
    bool updated = false;

#if defined(_OPENMP)
#pragma omp parallel for private(updated) schedule(static) /*collapse(2)*/
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
      m_root.InsertParticle(*iter, 0);
    }

    m_root.ComputeMass();

    // boolean flag to make sure particle is updated in case all others have been absorbed
    bool updated = false;

#if defined(_OPENMP)
#pragma omp parallel for private(updated) schedule(static) /*collapse(2)*/
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

} // namespace NBodyEnv
