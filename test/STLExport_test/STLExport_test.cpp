#include <TopoDS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <StlAPI_Writer.hxx>

#include <gtest/gtest.h>

TEST(STLExportTestSuite, testExportBox)
{
    // create a box, mixing integers and floats
    BRepPrimAPI_MakeBox my_box(10,20.5,30.);
    my_box.Build();
    StlAPI_Writer myStlWriter;
    myStlWriter.Write(my_box.Shape(), "tmp.stl");
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
