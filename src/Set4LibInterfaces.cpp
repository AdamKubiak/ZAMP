#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces(std::map<std::string, MobileObj *> &_Object_List)
{
  this->scena = new Scena(_Object_List);
  LoadLibrary("libs/libInterp4Move.so");
  LoadLibrary("libs/libInterp4Set.so");
  LoadLibrary("libs/libInterp4Rotate.so");
  LoadLibrary("libs/libInterp4Pause.so");
  //this->scena->AddMobileObj("Alpha");
}

Set4LibInterfaces::~Set4LibInterfaces()
{
  _Lib_List.clear();
  if (nullptr != scena)
    delete scena;
}

void Set4LibInterfaces::LoadLibrary(std::string path)
{
  LibInterface *pLibrary = new LibInterface(path);
  _Lib_List.insert({pLibrary->_Lib_Name, pLibrary});
}

bool Set4LibInterfaces::ExecPreprocessor(const char *NazwaPliku, std::istringstream &IStrm4Cmds)
{
  std::string Cmd4Preproc = "cpp -P ";
  char Line[500];
  std::ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE *pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc)
    return false;

  while (fgets(Line, 500, pProc))
  {
    OTmpStrm << Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}

bool Set4LibInterfaces::ReadCommands(std::istringstream &iStrm, int socket)
{
  std::string _Com_Name, _Obj_Name;
  bool flag;
  std::string message = "Clear\n";

  std::vector<MobileObj *> _objectsList = this->getScena()->getObjects();

  //Send(socket, "Clear\n");
  for (MobileObj *_objectPtr : _objectsList)
  {
    message += "AddObj " + _objectPtr->returnParameters();
  }
  const char *sConfigCmds = message.c_str();
  Send(socket, sConfigCmds);
  //std::cout << message;

  while (iStrm >> _Com_Name) // sprawdza, czy w strumieniu jest jeszcze jakaś komenda
  {
    std::vector<std::thread *> _THREAD_list;

    while (_Com_Name != "End_Parallel_Actions")
    {
      //if(_Com_Name == "End_Parallel_Actions") break;

      if (_Com_Name != "Pause" && _Com_Name != "Begin_Parallel_Actions")
        iStrm >> _Obj_Name;
      flag = true;
      std::map<std::string, LibInterface *>::iterator Iter = this->_Lib_List.find(_Com_Name);
      if (Iter == this->_Lib_List.end())
      {
        std::cerr << "!!! Brak komendy " << _Com_Name << std::endl;

        flag = false;
      }

      // Tworzy komendę na podstawie funkcji wtyczki

      if (flag)
      {
        Interp4Command *pCommand = Iter->second->pCreateCmd();
        if (!pCommand->ReadParams(iStrm))
        {
          std::cerr << "!!! Nieporawne parametry dla komendy '" << _Com_Name << std::endl;
          delete pCommand;
          return false;
        }
        MobileObj *_Obj = this->scena->FindMobileObj(_Obj_Name);
        //std::cout << _Obj_Name<<std::endl;
        if (_Obj == nullptr)
        {
          std::cerr << "!!! Obiekt " << _Obj_Name << " nie istnieje" << std::endl;
          delete pCommand;
          return false;
        }
        else
        { 
          //pCommand->ExecCmd(_Obj, this->scena);
          pCommand->PrintCmd();
          std::thread* new_thread = new std::thread(&Interp4Command::ExecCmd, pCommand, _Obj, this->scena);
          _THREAD_list.push_back(new_thread);
        //if(pCommand->ExecCmd(_Obj, socket)){std::cout<<"Udało się załodować obiekt z sceny"<<std::endl;}
        }
        //delete pCommand;
      }

      iStrm >> _Com_Name;
    }
    for (auto thread_object : _THREAD_list) // czekaj na zakończenie wszystkich zadań
    {
      thread_object->join();
      delete thread_object;
    }
  }
  return true;
}