//=======================================================================
// File:	ColladaMesh_MeshTriangle.cxx
// Created:	Mon Sep 25 11:24:02 1995
// Author:	Philippe GIRODENGO
// Copyright:    Matra Datavision	

#include <ColladaMesh_MeshTriangle.ixx>
#include <Precision.hxx>
#include <gp_XYZ.hxx>

//=======================================================================
//function : ColladaMesh_MeshTriangle
//design   : 
//warning  : 
//=======================================================================

ColladaMesh_MeshTriangle::ColladaMesh_MeshTriangle()
     : MyV1 (0), MyV2 (0), MyV3 (0), Myn1x (0.0), Myn1y (0.0), Myn1z (0.0),Myn2x (0.0), Myn2y (0.0), Myn2z (0.0),Myn3x (0.0), Myn3y (0.0), Myn3z (0.0) { }


//=======================================================================
//function : ColladaMesh_MeshTriangle
//design   : 
//warning  : 
//=======================================================================

     ColladaMesh_MeshTriangle::ColladaMesh_MeshTriangle(const Standard_Integer V1, 
						const Standard_Integer V2, 
						const Standard_Integer V3, 
						const Standard_Real n1x, 
						const Standard_Real n1y, 
						const Standard_Real n1z,
						const Standard_Real n2x, 
						const Standard_Real n2y, 
						const Standard_Real n2z,
						const Standard_Real n3x, 
						const Standard_Real n3y, 
						const Standard_Real n3z
						)
: MyV1 (V1), MyV2 (V2), MyV3 (V3), Myn1x (n1x), Myn1y (n1y), Myn1z (n1z),Myn2x (n2x), Myn2y (n2y), Myn2z (n2z),Myn3x (n3x), Myn3y (n3y), Myn3z (n3z) { }


//=======================================================================
//function : GetVertexAndOrientation
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_MeshTriangle::GetVertexAndOrientation(Standard_Integer& V1, 
						   Standard_Integer& V2, 
						   Standard_Integer& V3, 
						   Standard_Real& n1x, 
						   Standard_Real& n1y, 
						   Standard_Real& n1z,
						   Standard_Real& n2x, 
   						   Standard_Real& n2y, 
   						   Standard_Real& n2z,
   						   Standard_Real& n3x, 
   						   Standard_Real& n3y, 
   						   Standard_Real& n3z) const 
{
  V1 = MyV1;
  V2 = MyV2;
  V3 = MyV3;
  n1x = Myn1x;
  n1y = Myn1y;
  n1z = Myn1z;
  n2x = Myn2x;
  n2y = Myn2y;
  n2z = Myn2z;
  n3x = Myn3x;
  n3y = Myn3y;
  n3z = Myn3z;
  
}

//=======================================================================
//function : SetVertexAndOrientation
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_MeshTriangle::SetVertexAndOrientation(const Standard_Integer V1, const Standard_Integer V2, 
						   const Standard_Integer V3,
						   const Standard_Real n1x, const Standard_Real n1y, const Standard_Real n1z,
						   const Standard_Real n2x, const Standard_Real n2y, const Standard_Real n2z,
						   const Standard_Real n3x, const Standard_Real n3y, const Standard_Real n3z)
{
  MyV1 = V1;
  MyV2 = V2;
  MyV3 = V3;
  Myn1x = n1x;
  Myn1y = n1y;
  Myn1z = n1z;
  Myn2x = n2x;
  Myn2y = n2y;
  Myn2z = n2z;
  Myn3x = n3x;
  Myn3y = n3y;
  Myn3z = n3z;
  
}

//=======================================================================
//function : GetVertex
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_MeshTriangle::GetVertex(Standard_Integer& V1, Standard_Integer& V2, Standard_Integer& V3) const 
{
  V1 = MyV1;
  V2 = MyV2;
  V3 = MyV3;
}

//=======================================================================
//function : SetVertex
//design   : 
//warning  : 
//=======================================================================

void ColladaMesh_MeshTriangle::SetVertex(const Standard_Integer V1, const Standard_Integer V2, const Standard_Integer V3)
{
  MyV1 = V1;
  MyV2 = V2;
  MyV3 = V3;
}



