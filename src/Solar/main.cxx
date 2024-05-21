#include "Solar/Instance.hxx"
int main(int argc, char *argv[])
{
    Solar::Instance m_instance;
    m_instance.Init();
    m_instance.Loop();
    m_instance.Quit();
    
    // TODO: actually return the error code? but std::exit() does that for us!
    return 0;
}