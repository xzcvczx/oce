// This file is generated by WOK (CSFDBSchema).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ShapeSchema_PColgp_FieldOfHArray1OfCirc2d_HeaderFile
#define _ShapeSchema_PColgp_FieldOfHArray1OfCirc2d_HeaderFile

#ifndef _Handle_Storage_Schema_HeaderFile
#include <Handle_Storage_Schema.hxx>
#endif
#ifndef _Storage_BaseDriver_HeaderFile
#include <Storage_BaseDriver.hxx>
#endif

#ifndef _ShapeSchema_gp_Circ2d_HeaderFile
#include <ShapeSchema_gp_Circ2d.hxx>
#endif


class PColgp_FieldOfHArray1OfCirc2d;

class ShapeSchema_PColgp_FieldOfHArray1OfCirc2d {
public:
  Standard_EXPORT static void SAdd(const PColgp_FieldOfHArray1OfCirc2d&,const Handle(Storage_Schema)& aSchema);
  Standard_EXPORT static void SWrite(const PColgp_FieldOfHArray1OfCirc2d&,Storage_BaseDriver& aDriver,const Handle(Storage_Schema)& aSchema);
  Standard_EXPORT static void SRead(PColgp_FieldOfHArray1OfCirc2d&,Storage_BaseDriver& aDriver,const Handle(Storage_Schema)& aSchema);
};
#endif