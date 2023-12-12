#include <cstdlib>

int main() {
    // Generate the Gnuplot script file (as shown in the previous step)

    // Use a system command to execute Gnuplot with the script
    system("gnuplot -p plot_particles.gp");

    return 0;
}