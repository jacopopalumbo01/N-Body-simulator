#ifndef PART_PARSER
#define PART_PARSER

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

struct Vec
{
    double x;
    double y;
    double z;
};

class Parser
{
public:
    Parser(std::string path, double deltaTime)
    {
        m_partFile.open(path);
        m_deltaTime = deltaTime;
        parse();
    }

    std::vector<std::vector<Vec>> getParticles() { return m_parsed; }
    std::vector<double> getTime() { return m_timePassed; }

private:
    std::ifstream m_partFile;
    std::vector<std::vector<Vec>> m_parsed;
    std::vector<double> m_timePassed;
    int m_numStep;
    int m_particleIndex;
    double m_deltaTime;

    void parse()
    {
        std::string line;
        std::vector<Vec> tempVec;
        m_numStep = -1;

        if (m_partFile.is_open())
        {
            while (m_partFile)
            {
                std::getline(m_partFile, line);

                if (line.length() != 0)
                {
                    // Detect particle
                    if (line.at(0) == 'P')
                    {
                        // std::cout << "New particle detected" << std::endl;

                        // Split string by space
                        char delimiter = ' ';
                        size_t pos = 0;
                        std::string token;

                        // Remove Particle name from the string
                        pos = line.find(delimiter);
                        line.erase(0, pos + 1);

                        // Here we store the particle position
                        Vec partPos = {0.0, 0.0, 0.0};
                        int axis = 0;

                        while ((pos = line.find(delimiter)) != std::string::npos)
                        {
                            token = line.substr(0, pos);
                            line.erase(0, pos + 1);

                            switch (axis)
                            {
                            case 0:
                                partPos.x = stod(token);
                                axis++;
                                break;
                            case 1:
                                partPos.y = stod(token);
                                axis++;
                                break;
                            case 2:
                                partPos.z = stod(token);
                                axis = 0;
                                break;
                            default:
                                break;
                            }
                        }

                        // Save particle in current step
                        tempVec.push_back(partPos);
                    }

                    else if (line.at(0) == '-')
                    {
                        // std::cout << "New time step detected" << std::endl;
                        m_numStep++;
                        m_particleIndex = 0;

                        if (m_numStep != 0)
                        {
                            std::cout << "temp vec size: " << tempVec.size() << std::endl;
                            m_parsed.push_back(tempVec);
                            tempVec.clear();
                        }

                        m_timePassed.push_back(m_deltaTime * m_numStep);
                    }
                }
            }
        }
        // Save also last tempVec
        m_parsed.push_back(tempVec);
    }
};

#endif