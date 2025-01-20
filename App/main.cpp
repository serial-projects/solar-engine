#include "Solar/Solar.hpp"

int main(int argc, char *argv[])
{
    /* NOTE: the instance manager is here: */
    Solar::Instance m_instance;
    Solar::InstanceInit(&m_instance);
    Solar::InstanceLoop(&m_instance);
    Solar::InstanceQuit(&m_instance);
    Solar::InstanceDestroy(&m_instance);
    
    /* Return good if everything reached here: */
    return 0;
}