#pragma once

#include "Scena.hh"
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "AccessControl.hh"
#include "Port.hh"
#include <unistd.h>
#include <string.h>
#include <vector>
using namespace std;
/*!
 * \brief Wysyła napis do poprzez gniazdo sieciowe.
 *
 * Wysyła napis do poprzez gniazdo sieciowe.
 * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które 
 *                        ma zostać wysłany napis w sensie języka C.
 * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
 *                    gniazdo sieciowe.
 */
int Send(int Sk2Server, const char *sMesg);

/*!
 * \brief Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 *
 * Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 * W tym celu monitoruje zmiany na scenie, a gdy je wykryje przesyła
 * informacje o aktualnej pozycji wszystkich obiektów.
 */
class Sender {
  /*!
   * \brief Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * 
   * Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * W przypadku wartości \p true, pętla wątku będzie wykonywana.
   * Natomiast wartość \p false powoduje przerwanie pętli.
   */
   volatile bool    _ContinueLooping = true;
  /*!
   * \brief Deskryptor gniazda sieciowego, poprzez które wysyłane są polecenia.
   */
   int             _Socket = 0;
  /*!
   * \brief Wskaźnik na scenę, które stan jest przesyłany w postaci
   *        poleceń do serwera graficzneg.
   */
   Scena          *_pScn = nullptr;
   

  
 public:
 std::thread klient_thread;
  /*!
   * \brief Inicjalizuje obiekt deskryptorem gniazda i wskaźnikiem
   *        na scenę, na zmianę stanu które będzie ten obiekt reagował.
   */
   Sender(int Socket, Scena *pScn): _Socket(Socket), _pScn(pScn) {}

  /*!
   * \brief Sprawdza, czy pętla wątku może być wykonywana.
   * 
   * Sprawdza, czy pętla wątku może być wykonywana.
   * \retval true - pętla wątku może być nadal wykonywana.
   * \retval false - w przypadku przeciwnym.
   */
   bool ShouldCountinueLooping() const { return _ContinueLooping; }
  /*!
   * \brief Powoduje przerwanie działania pętli wątku.
   *
   * Powoduje przerwanie działania pętli wątku.
   * \warning Reakcja na tę operację nie będize natychmiastowa.
   */  
   void CancelCountinueLooping() { _ContinueLooping = false; }

  /*!
   * \brief Ta metoda jest de facto treścią wątku komunikacyjnego
   *
   * Przegląda scenę i tworzy odpowiednie polecenia, a następnie
   * wysyła je do serwera.
   * \param[in] Socket - deskryptor gniazda sieciowego, poprzez które
   *                     wysyłane są polecenia.
   */
   void Watching_and_Sending() {
     while (ShouldCountinueLooping()) {
       if (!_pScn->IsChanged())  { usleep(10000); continue; }
       _pScn->LockAccess();
       
       //------- Przeglądanie tej kolekcji to uproszczony przykład
       
       //Send(_Socket,"Clear\n"); // To jest konieczne, aby usunąć wcześniejsze obiekty.
       //cout << "Clear\n";
    std::map<std::string, MobileObj*> MobileObjects = _pScn->getObjList();
    std::vector<MobileObj*> objects_list;
    std::map<std::string, MobileObj*>::iterator Iter;

    for(Iter = MobileObjects.begin(); Iter != MobileObjects.end(); Iter++)
    {
        objects_list.push_back(Iter->second);
    }


    for (MobileObj* object_ptr : objects_list)
    {
      //MobileObj* object = object_ptr;

      std::string message = "UpdateObj ";
      message += object_ptr->returnParameters();
      //std::cout<<"lul"<<message<<"XDDDD"<<std::endl;
                                     // Ta instrukcja to tylko uproszczony przykład
          // cout << objectPointer->movingState;
           Send(_Socket, message.c_str()); // Tu musi zostać wywołanie odpowiedniej
                                           // metody/funkcji gerującej polecenia dla serwera.
       }
       //Send(_Socket,"Display\n"); // To jest konieczne, aby zobaczyć zmiany
       //cout << "Display\n";
       
       _pScn->CancelChange();
       _pScn->UnlockAccess();
     }
   }
  
};

/*!
 * \brief Funkcja jest treścią wątku komunikacyjnego
 * 
 * Funkcja jest treścią wątku komunikacyjnego.
 * \param[in] rSender - odpowiada za śledenie zmian na scenie 
 *                      i przesyłanie do serwera graficznego
 *                      aktualnego stanu sceny, gdy uległ on zmianie.
 */
void Fun_CommunicationThread(Sender  *pSender);



/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 */
bool OpenConnection(int &rSocket);

void close(int socket, Sender &clientSender, thread t);