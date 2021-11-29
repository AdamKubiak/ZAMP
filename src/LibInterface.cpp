#include "LibInterface.hh"

LibInterface::LibInterface(std::string path)
{
    handler = dlopen(path.c_str(), RTLD_LAZY);

    if (!handler)
    {
        std::cerr << "!!! Brak biblioteki: " << path << std::endl;
    }

    void *pFun = dlsym(handler, "CreateCmd");
    if (!pFun)
        std::cerr << "!!! Nie znaleziono funkcji CreateCmd " << path <<std::endl;

    
    pCreateCmd = *reinterpret_cast<Interp4Command *(*)(void)>(pFun);
    Interp4Command *interp_cmd = pCreateCmd();
    _Lib_Name = interp_cmd->GetCmdName();
    delete interp_cmd;
}

LibInterface::~LibInterface()
{
    dlclose(handler);
}