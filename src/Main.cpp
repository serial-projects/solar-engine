/* 2020 (C) Solar Engine & Solar Project by Pipes Studios. */

#include "Solar/Solar.hpp"

namespace PC
{
    Solar::Instance* instance = nullptr;
    
    void Init()
    {
        PC::instance = Solar::InstanceNew();
        Solar::InstanceInit(PC::instance);
    }

    void Loop()
    {
        Solar::InstanceLoop(PC::instance);
    }

    Solar::U8 Quit()
    {
        Solar::InstanceQuit(PC::instance);
        Solar::InstanceDestroy(PC::instance);
        return 0;
    }
};

int main(int argc, char *argv[])
{
    PC::Init();
    PC::Loop();
    return PC::Quit();
}