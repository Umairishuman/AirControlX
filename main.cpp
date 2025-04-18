#include "Controller.h"
#include <unistd.h>
int main(){
    Controller controller;
    // controller.run();
    controller.runSimulation();
    usleep(10000000);
    return 0;
}