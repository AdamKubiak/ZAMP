#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include "unistd.h"
using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _Speed_mmS(0), _Lenght_ofRoad(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName()<<" " << _Speed_mmS<<" "  << _Lenght_ofRoad << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccCtrl) const
{
  int direction = this->_Speed_mmS > 0 ? 1 : -1;
  int iterations = std::floor(this->_Lenght_ofRoad/this->_Speed_mmS);

  for (int i = 0; i < iterations; ++i)
  {
    pAccCtrl->LockAccess();
    Vector3D position = pMobObj->GetPositoin_m();
    double angle = pMobObj->GetAng_Roll_deg();

    position[0] += this->_Speed_mmS * direction * cos(M_PI * angle/180);
    position[1] += this->_Speed_mmS * direction * sin(M_PI * angle/180);
    
    pMobObj->SetPosition_m(position);
    pAccCtrl->MarkChange();
    pAccCtrl->UnlockAccess();
    usleep(100000);
    
  }
  std::cout<<"ZROBILEM SIE";
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList>> _Speed_mmS >> _Lenght_ofRoad;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
