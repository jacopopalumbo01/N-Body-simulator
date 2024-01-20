#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include "Particle/Particle.hpp"
#include <vector>

namespace NBodyEnv
{

    class TreeNode
    {
    public:
        enum Octant
        {
            // structure that describes the octants of the tree
            // NEI = NorthEastInternal
            // NEE = NorthEastExternal and so on
            // the chosen coordinate system is such that
            // {x = 0, y = 0, z = 0} is the center of the box 
            // the minimum is the lower left edge of the box, corresponding to SWI octant
            // the maximum is the upper right edge of the box, corresponding to NEE octant
            NEI = 0,
            NEE,
            NWI,
            NWE,
            SEI,
            SEE,
            SWI,
            SWE,
            NONE
        };

        TreeNode(const std::vector<double> &max, const std::vector<double> &min, TreeNode *parent = nullptr);

        ~TreeNode();

        // getters
        double GetMass() const;
        const std::vector<double> &GetCenterOfMass() const;
        const std::vector<double> &GetCenter() const;
        TreeNode *GetParent() const;
        int GetNParticles() const;
        bool GetTheta() const;

        // setters
        void SetMass(double mass);
        void SetCenterOfMass(const std::vector<double> &cm);
        void SetCenter(const std::vector<double> &center);
        void SetParent(TreeNode *parent);
        void SetNParticles(int nParticles);
        void SetTheta(bool theta);

        bool IsRoot() const;
        bool IsExternal() const;

        // method to reset all the nodes after computing all the forces between particles
        // we need to do this at the start of each time step
        void ResetNode(const std::vector<double> &max, const std::vector<double> &min);

        // method to get an octant of a node, aka one of its 8 children
        Octant GetOctant(double x, double y, double z) const;

        // method for debugging
        void PrintOctant(Octant octant) const;

        // method to create a new node. given an octant
        TreeNode *CreateNode(Octant octant);

        // method to insert a particle in the tree and sink it down to the correct
        // external node, aka leaf. Calls itself recursively until it reaches the correct leaf
        void InsertParticle(const Particle &particle, int level);

        // method to compute mass of all particles contained in the node (and all its children)
        // calls itself recursively until it reaches the leafs
        void ComputeMass();

        // method for debugging
        void PrintNodesWithParticles(const TreeNode *node);

        // compute force on a particle, exloits the multipole acceptance criterion
        // that has been previously set
        std::vector<double> ComputeForce(const Particle &part) const;
        
        std::vector<double> ComputeAcc(const Particle &p1, const Particle &p2) const;

        // octants of each node
        TreeNode *m_octant[8];

    private:
        // total mass of the node, comprised of the mass of all particles contained in its children
        double m_totMass;
        // center of mass of the node
        std::vector<double> m_cm;
        // center of the node
        std::vector<double> m_center;
        // upper right edge of the node, which is the maximum in the chosen coordinate system
        std::vector<double> m_max;
        // lower left edge of the node, which is the minimum in the chosen coordinate system
        // ==> both are used to compute the center of the node when a new one is created
        std::vector<double> m_min;
        // parent of the node
        TreeNode *m_parent;
        // number of particles in the node
        // bear in mind that if the node is external (aka leaf), nParticles == 1 || nParticles == 0
        int m_nParticles;

        // Multipole Acceptance Criterion theta = d / r
        // d =  node size
        // r =  distance between the node and the particle
        // that is being considered for force computation
        static double m_theta;
        // gravitaional constant
        static double m_G;

        // flag to check if the node is too close to the particle that is being considered
        // for force computation, based on the MAC criterion ==> need to further subdivide the
        // node in order to get a better approximation of the force
        // this amounts to considering all its children, the non null octants
        mutable bool m_tooClose;

        // Particle that belongs to the node, bear in mind that each external node
        // (aka leaf) can contain at most one particle
        Particle m_particle;
    };
}

#endif // TREE_NODE_HPP