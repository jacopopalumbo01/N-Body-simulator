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
            NEI = 0,
            NEE,
            NWI,
            NWE,
            SWI,
            SWE,
            SEI,
            SEE,
            NONE
        };

        TreeNode(const std::vector<double> &max, const std::vector<double> &min, TreeNode *parent = nullptr);

        ~TreeNode();

        // getters
        double GetMass() const;
        const std::vector<double> &GetCenterOfMass() const;
        // const double &GetRadius() const;
        const std::vector<double> &GetCenter() const;
        TreeNode *GetParent() const;
        int GetNParticles() const;
        bool GetTheta() const;

        // setters
        void SetMass(double mass);
        void SetCenterOfMass(const std::vector<double> &cm);
        // void SetRadius(double radius);
        void SetCenter(const std::vector<double> &center);
        void SetParent(TreeNode *parent);
        void SetNParticles(int nParticles);
        void SetTheta(bool theta);

        bool IsRoot() const;
        bool IsExternal() const;

        void ResetNode(const std::vector<double> &center, double radius);

        // method to get octants
        Octant GetOctant(double x, double y, double z) const;

        void PrintOctant(Octant octant) const;

        // method to create a new node
        TreeNode *CreateNode(Octant octant);

        void InsertParticle(Particle particle, int level);

        TreeNode *m_octant[8];

    private:
        double m_totMass;
        // center of mass of the node
        std::vector<double> m_cm;
        // radius of the node
        // double m_radius;
        // center of the node
        std::vector<double> m_center;
        // upper right edge of the node
        std::vector<double> m_max;
        // lower left edge of the node ==> used to compute the center of the node
        std::vector<double> m_min;
        // parent of the node
        TreeNode *m_parent;
        // number of particles in the node
        // bear in mind that if the node is external, nParticles == 1 || nParticles == 0
        int m_nParticles;

        // multipole acceptance criterion theta = d / r
        // where d is the node size and r is the distance between the node and the particle
        // that is being considered for force computation
        bool m_theta;

        // Particle that belongs to the node
        Particle *m_particle;
    };
}

#endif // TREE_NODE_HPP