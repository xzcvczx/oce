SET(TOOLKIT TKCOLLADA)

SET(TOOLKIT_MODULES
	ColladaMesh
	ColladaAPI
	ColladaTransfer
	RWCollada
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKG2d
	TKMesh
	TKBRep
	TKG3d
	TKTopAlgo
)

INCLUDE(../BuildToolkit.cmake)

