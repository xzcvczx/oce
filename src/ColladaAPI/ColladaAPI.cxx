#include <ColladaAPI.ixx>
#include <ColladaAPI_Writer.hxx>
#include <ColladaAPI_Reader.hxx>

void ColladaAPI::Write(const TopoDS_Shape& aShape,
		   const Standard_CString aFile,
		   const Standard_Boolean aAsciiMode) 
{
  ColladaAPI_Writer writer;
  writer.ASCIIMode() = aAsciiMode;
  writer.Write (aShape, aFile);
}


void ColladaAPI::Read(TopoDS_Shape& aShape,const Standard_CString aFile)
{
  ColladaAPI_Reader reader;
  reader.Read (aShape, aFile);
}
