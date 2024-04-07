#include "./src/Simulator/Simulator.h"
#include "./src/const.h"

#include "./src/Plot/Plot.h"

int main() {

    std::string filename = "data.bin";

    rVector A(3690,1340,5017);
    rVector B(3658,-421,5199);
    Simulator sim;
    sim.start(1e5, A, B, 1000, 10, filename);

    Plot::plotData(filename);

    return 0;

}