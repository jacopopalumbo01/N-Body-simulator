#include "TreeNode/TreeNode.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

namespace NBodyEnv
{
    TreeNode::TreeNode(const std::vector<double> &max, const std::vector<double> &min, TreeNode *parent)
        : m_totMass(0.0),
          m_cm({0.0, 0.0, 0.0}),
          m_center({min[0] + (max[0] - min[0]) / 2.0, min[1] + (max[1] - min[1]) / 2.0, min[2] + (max[2] - min[2]) / 2.0}),
          m_max(max),
          m_min(min),
          m_parent(parent),
          m_nParticles(0),
          m_theta(false),
          m_particle(nullptr)
    {
        for (int i = 0; i < 8; i++)
        {
            m_octant[i] = nullptr;
        }
    }

    // getters
    double TreeNode::GetMass() const
    {
        return m_totMass;
    }

    const std::vector<double> &TreeNode::GetCenterOfMass() const
    {
        return m_cm;
    }

    // const double &TreeNode::GetRadius() const
    // {
    //     return m_radius;
    // }

    const std::vector<double> &TreeNode::GetCenter() const
    {
        return m_center;
    }

    TreeNode *TreeNode::GetParent() const
    {
        return m_parent;
    }

    int TreeNode::GetNParticles() const
    {
        return m_nParticles;
    }

    bool TreeNode::GetTheta() const
    {
        return m_theta;
    }

    // setters
    void TreeNode::SetMass(double mass)
    {
        m_totMass = mass;
    }

    void TreeNode::SetCenterOfMass(const std::vector<double> &cm)
    {
        m_cm = cm;
    }

    // void TreeNode::SetRadius(double radius)
    // {
    //     m_radius = radius;
    // }

    void TreeNode::SetCenter(const std::vector<double> &center)
    {
        m_center = center;
    }

    void TreeNode::SetParent(TreeNode *parent)
    {
        m_parent = parent;
    }

    void TreeNode::SetNParticles(int nParticles)
    {
        m_nParticles = nParticles;
    }

    void TreeNode::SetTheta(bool theta)
    {
        m_theta = theta;
    }

    bool TreeNode::IsRoot() const
    {
        return m_parent == nullptr;
    }

    bool TreeNode::IsExternal() const
    {
        return m_nParticles < 2;
    }

    void TreeNode::ResetNode(const std::vector<double> &center, double radius)
    {
        m_totMass = 0.0;
        m_cm = {0.0, 0.0, 0.0};
        // m_radius = radius;
        m_center = center;
        m_parent = nullptr;
        m_nParticles = 0;
        m_theta = false;
    }

    // method to get octants
    TreeNode::Octant TreeNode::GetOctant(double x, double y, double z) const
    {
        if (x > m_center[0])
        {
            if (y > m_center[1])
            {
                if (z > m_center[2])
                {
                    return NEE;
                }
                else
                {
                    return SEE;
                }
            }
            else
            {
                if (z > m_center[2])
                {
                    return NWE;
                }
                else
                {
                    return SWE;
                }
            }
        }
        else
        {
            if (y > m_center[1])
            {
                if (z > m_center[2])
                {
                    return NEI;
                }
                else
                {
                    return SEI;
                }
            }
            else
            {
                if (z > m_center[2])
                {
                    return NWI;
                }
                else
                {
                    return SWI;
                }
            }
        }
    }

    void TreeNode::PrintOctant(Octant octant) const
    {
        switch (octant)
        {
        case SWI:
            std::cout << "SWI\n";
            break;
        case SWE:
            std::cout << "SWE\n";
            break;
        case SEE:
            std::cout << "SEE\n";
            break;
        case SEI:
            std::cout << "SEI\n";
            break;
        case NWI:
            std::cout << "NWI\n";
            break;
        case NWE:
            std::cout << "NWE\n";
            break;
        case NEE:
            std::cout << "NEE\n";
            break;
        case NEI:
            std::cout << "NEI\n";
            break;

        default:
            std::cout << "Error: Octant not found\n";
        }
    }

    // method to create a new node
    TreeNode *TreeNode::CreateNode(Octant octant)
    {
        switch (octant)
        {
        case SWI:
            return new TreeNode(m_center, m_min, this);
            break;
        case SWE:
            return new TreeNode({m_max[0], m_center[1], m_center[2]}, {m_center[0], m_min[1], m_min[2]}, this);
            break;
        case SEE:
            return new TreeNode({m_max[0], m_max[1], m_center[2]}, {m_center[0], m_min[1], m_center[2]}, this);
            break;
        case SEI:
            return new TreeNode({m_center[0], m_max[1], m_center[2]}, {m_min[0], m_min[1], m_center[2]}, this);
            break;
        case NWI:
            return new TreeNode({m_center[0], m_center[1], m_max[2]}, {m_min[0], m_min[1], m_center[2]}, this);
            break;
        case NWE:
            return new TreeNode({m_max[0], m_center[1], m_max[2]}, {m_center[0], m_min[1], m_center[2]}, this);
            break;
        case NEE:
            return new TreeNode(m_max, m_center, this);
            break;
        case NEI:
            return new TreeNode({m_center[0], m_max[1], m_max[2]}, {m_min[0], m_center[1], m_center[2]}, this);
            break;

        default:
            std::cout << "Error: Octant not found\n";
            // TODO: throw exception
            // std::stringstream ss;
            // ss << "Can't determine quadrant!\n";
            // throw std::runtime_error(ss.str().c_str());
            break;
        }
    }

    void TreeNode::InsertParticle(Particle part, int level)
    {
        // print particle position
        // std::cout << "Particle position: " << part.getPos().xPos << " " << part.getPos().yPos << " " << part.getPos().zPos << "\n";
        // // print min and max
        // std::cout << "Min: " << m_min[0] << " " << m_min[1] << " " << m_min[2] << "\n";
        // std::cout << "Max: " << m_max[0] << " " << m_max[1] << " " << m_max[2] << "\n";
        if ((part.getPos().xPos < m_min[0] || part.getPos().xPos > m_max[0]) || (part.getPos().yPos < m_min[1] || part.getPos().yPos > m_max[1]) || (part.getPos().zPos < m_min[2] || part.getPos().zPos > m_max[2]))
        {
            std::stringstream ss;
            ss << "Particle is out of boundaries!\n";
            throw std::runtime_error(ss.str());
        }

        if (m_nParticles > 1)
        {
            Octant octant = GetOctant(part.getPos().xPos, part.getPos().yPos, part.getPos().zPos);
            if (!m_octant[octant])
                m_octant[octant] = CreateNode(octant);

            std::cout << "Debug 1\n";
            m_octant[octant]->InsertParticle(part, level + 1);
        }
        else if (m_nParticles == 1)
        {
            assert(IsExternal() || IsRoot());

            // There is already a particle
            // subdivide the node and relocate that particle
            // print m_particle position
            std::cout << "Particle position: " << m_particle->getPos().xPos << " " << m_particle->getPos().yPos << " " << m_particle->getPos().zPos << "\n";
            Octant octant = GetOctant(m_particle->getPos().xPos, m_particle->getPos().yPos, m_particle->getPos().zPos);
            std::cout << "Octant p1 \n";
            PrintOctant(octant);
            if (m_octant[octant] == nullptr)
            {
                m_octant[octant] = CreateNode(octant);
            }
            std::cout << "Reinsert p1 \n";
            m_octant[octant]->InsertParticle(*m_particle, level + 1);
            // // TODO: implement if needed
            // m_particle.Reset();

            octant = GetOctant(part.getPos().xPos, part.getPos().yPos, part.getPos().zPos);
            std::cout << "Octant p2 \n";
            PrintOctant(octant);
            if (!m_octant[octant])
                m_octant[octant] = CreateNode(octant);
            std::cout << "Reinsert p2 \n";
            m_octant[octant]->InsertParticle(part, level + 1);
        }
        else if (m_nParticles == 0)
        {
            // assing new particle as the new particle in the node
            std::cout << "Inserted particle in node\n";
            m_particle = &part;
        }

        m_nParticles++;
    }
}
