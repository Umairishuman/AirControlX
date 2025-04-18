#include "Controller.h"
#include <unistd.h>
int main(){
    Controller controller;
    controller.run();
    usleep(300000000);
    return 0;
}