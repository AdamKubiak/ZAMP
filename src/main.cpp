#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include "Set4LibInterfaces.hh"
#include "MobileObj.hh"
#include "Configuration.hh"
#include "xmlinterp.hh"
#include "klient.hh"


int main()
{
  //std::map<std::string, MobileObj*> lista_przyklad;
  //MobileObj *obj1 = new MobileObj;
  //MobileObj *obj2 = new MobileObj;
  //std::cout << &lista_przyklad << std::endl;
 // std::cout << obj2 << std::endl;
  //lista_przyklad.insert({"Alpha",obj1});
  //lista_przyklad.insert({"Beta",obj2});

  //Set4LibInterfaces *LibraryList = new Set4LibInterfaces(lista_przyklad); // Lista (zestaw) bibliotek
  std::istringstream iStrm;           // strumień danych wejściowych komend
  Configuration config;

  cout << "Port: " << PORT << endl;

  int Socket4Sending;

  

  if(false == ReadFile("config/config.xml",config))
  {
    std::cerr<<"error"<<std::endl;
    return 1;
  }

  std::map<std::string, MobileObj*> objectsList = config.getObjectList();
  Set4LibInterfaces *LibraryList = new Set4LibInterfaces(objectsList);

  if(!OpenConnection(Socket4Sending))
  {
     return 1;
  }
  else std::cout<<"Połączenie powiodło się"<<std::endl;
  Sender _Sender(Socket4Sending, LibraryList->getScena());//dorób funkcję do odbierania sceny z setlibinterfaces
  
  thread Thread4Sending(Fun_CommunicationThread, &_Sender);
  LibraryList->ExecPreprocessor("zbior_polecen.cmd", iStrm);
  LibraryList->ReadCommands(iStrm,Socket4Sending);


  close(Socket4Sending, _Sender, move(Thread4Sending));
  
  return 0;
}
