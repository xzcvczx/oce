#include <ColladaAPI_Writer.ixx>
#include <ColladaTransfer.hxx>
#include <TopoDS_Shape.hxx>
#include <Bnd_Box.hxx>
#include <RWCollada.hxx>
#include <BRepBndLib.hxx>
#include <OSD_Path.hxx>

#define MAX2(X, Y)      (  Abs(X) > Abs(Y)? Abs(X) : Abs(Y) )
#define MAX3(X, Y, Z)   ( MAX2 ( MAX2(X,Y) , Z) )

ColladaAPI_Writer::ColladaAPI_Writer()
{
  theColladaMesh = new ColladaMesh_Mesh;
  theASCIIMode = Standard_True;
  theDeflection = 0.01;
  theRelativeMode = Standard_True;
  theCoefficient = 0.001;
}

void ColladaAPI_Writer::SetDeflection(const Standard_Real aDeflection) 
{
  theDeflection = aDeflection;
}
void ColladaAPI_Writer::SetCoefficient(const Standard_Real aCoefficient) 
{
  theCoefficient = aCoefficient;
}

Standard_Boolean& ColladaAPI_Writer::RelativeMode() 
{
  return theRelativeMode;
}

Standard_Boolean& ColladaAPI_Writer::ASCIIMode() 
{
  return theASCIIMode;
}

void ColladaAPI_Writer::Write(const TopoDS_Shape& aShape,const Standard_CString aFileName) 
{
  OSD_Path aFile(aFileName);
  if (theRelativeMode) {
    Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
    Bnd_Box Total;
    BRepBndLib::Add(aShape, Total);
    Total.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
    theDeflection = MAX3(aXmax-aXmin , aYmax-aYmin , aZmax-aZmin)*theCoefficient;
  }
  ColladaTransfer::BuildIncrementalMesh(aShape, theDeflection, theColladaMesh);
  // Write the built mesh
  if (theASCIIMode) {
    RWCollada::WriteDAE(theColladaMesh, aFile);
    }  
  else {
    RWCollada::WriteZAE(theColladaMesh, aFile);
    }
}

