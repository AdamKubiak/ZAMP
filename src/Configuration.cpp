#include "Configuration.hh"

void Configuration::AddMobileObj(const std::string &ObjectName,const Vector3D &Scale,const std::string &RGB,const Vector3D &Shift,const Vector3D &RotXYZ,const Vector3D &Trans)
{
  MobileObj* _Obj = new MobileObj;
  _Obj->SetName(ObjectName.c_str());
  _Obj->SetScale(Scale);
  _Obj->setColor(RGB);
  _Obj->setShift(Shift);
  _Obj->SetPosition_m(Trans);
  _Obj->SetAng_Roll_deg(RotXYZ[0]);
  _Obj->SetAng_Pitch_deg(RotXYZ[1]);
  _Obj->SetAng_Yaw_deg(RotXYZ[2]);
  this->getObjectList().insert({ObjectName,_Obj});
}

void Configuration::AddLibraryName(const std::string &LibraryName)
{
  LibraryList.push_back(LibraryName);
}