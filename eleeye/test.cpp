#include <logger.h>

#define DEBUG

int main(int argc, char** argv)
{
#ifdef DEBUG
    getLogger()->init("./logger.log");
#endif
 
    getLogger()->logger("In Main, use logger >_< !\n");
 
    getLogger()->close();
 
    return 0;
}
