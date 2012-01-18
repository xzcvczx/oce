#include <TopoDS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <ColladaAPI_Writer.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>

#include <gtest/gtest.h>

TEST(COLLADAExportTestSuite, testExportBox)
{
    // create a box, mixing integers and floats
    BRepPrimAPI_MakeBox my_box(10,20.5,30.);
    my_box.Build();
    ColladaAPI_Writer myColladaWriter;
    myColladaWriter.Write(my_box.Shape(), "box.dae");
}

TEST(COLLADAExportTestSuite, testExportSphere)
{
    // create a box, mixing integers and floats
    BRepPrimAPI_MakeSphere my_sphere(50.);
    my_sphere.Build();
    ASSERT_TRUE(my_sphere.IsDone());
    ColladaAPI_Writer myColladaWriter;
    myColladaWriter.Write(my_sphere.Shape(), "sphere.dae");
}

TEST(COLLADAExportTestSuite, testExportTorus)
{
    // create a box, mixing integers and floats
    BRepPrimAPI_MakeTorus my_torus(10,4);
    my_torus.Build();
    ASSERT_TRUE(my_torus.IsDone());
    ColladaAPI_Writer myColladaWriter;
    myColladaWriter.Write(my_torus.Shape(), "torus.dae");
}

TEST(COLLADAExportTestSuite, testExportFromBRep)
{
    Standard_CString aFileName = (Standard_CString) "../../test/data/brep/31_misc2.brep";
    BRep_Builder aBuilder;
    TopoDS_Shape aShape;
    Standard_Boolean result = BRepTools::Read(aShape,aFileName,aBuilder);
    ASSERT_TRUE(result);
    ASSERT_FALSE(aShape.IsNull());
    ColladaAPI_Writer myColladaWriter;
    myColladaWriter.SetDeflection(1);
    myColladaWriter.SetCoefficient(0.1);
    myColladaWriter.Write(aShape, "31_misc2.dae");
}    


int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
