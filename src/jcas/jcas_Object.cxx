// Copyright: 	Matra-Datavision 1999
// File:	jcas_Object.cxx
// Created:	Wed Mar 31 13:18:02 1999
// Author:	Arnaud BOUZY
//		<adn>


#include <jcas_Object.h>
#include <jcas.hxx>
#include <Standard_Transient.hxx>
#include <Standard_Boolean.hxx>
#include <stdlib.h>
#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>
#include <Standard_SStream.hxx>
#include <Standard_CString.hxx>
#include <Standard_Type.hxx>

#include <Standard_Macro.hxx>


extern "C" {

JNIEXPORT void JNICALL Java_jcas_Object_FinalizeID
  (JNIEnv * /*env*/ , jclass /*theobj*/, jlong theid)
{

  if (theid) {
    Handle(Standard_Transient)* thehandleobj = (Handle(Standard_Transient)*) theid;
    delete thehandleobj;
  }


}

JNIEXPORT jboolean JNICALL Java_jcas_Object_IsNullObj
  (JNIEnv *env, jobject theobj)
{
jboolean thejret = 0;
jcas_Locking alock(env);
{
try {
  OCC_CATCH_SIGNALS
Handle(Standard_Transient) the_this = *((Handle(Standard_Transient)*) jcas_GetHandle(env,theobj));
thejret = the_this.IsNull();

}
catch (Standard_Failure) {
  Standard_SStream Err;
  Err <<   Standard_Failure::Caught(); 
  Err << (char) 0;
  jcas_ThrowException(env,GetSString(Err));
}
}
alock.Release(); 
return thejret;
}

JNIEXPORT jobject JNICALL Java_jcas_Object_DownCast
  (JNIEnv *env, jobject theobj, jobject aClassName, jobject aPackageName)
{
  jobject thejret=0;
  jcas_Locking alock(env);
      
  {
    try {
      OCC_CATCH_SIGNALS
      Handle(Standard_Transient)* the_this = (Handle(Standard_Transient)*) jcas_GetHandle(env,theobj);
      Standard_CString the_ClassName = jcas_ConvertToCString(env,aClassName);
      Standard_CString the_PackageName = jcas_ConvertToCString(env,aPackageName);
      
      /* Causes "SEGVWntHandler SIGSEGV  signum=11"
	 
	 if ((*the_this)->IsKind(the_ClassName))
	 {
	 char newName[1024];
	 sprintf(newName, "%s/%s", the_PackageName, the_ClassName);
	 thejret = jcas_CreateObject(env, newName, the_this, 0);
	 }
	 else
	 {
	 thejret = theobj;
	 }
      */
      
      
      // Caller is responsible for proper transformation
      
      //if (strcmp((*the_this)->DynamicType()->Name(), the_ClassName) == 0)
      //{
      char newName[1024];
      sprintf(newName, "%s/%s", the_PackageName, the_ClassName);
  
      // Get aVirer parameter
      int aVirer = jcas_GetaVirer(env, theobj);
      
      // Set aVirer parameter for initial object
      jcas_SetaVirer(env, theobj, 0);
      
      // Create a copy
      thejret = jcas_CreateObject(env, newName, the_this, aVirer);
      //}
      //else
      //{
      //	thejret = theobj;
      //}
      
    }
    catch (Standard_Failure) {
      Standard_SStream Err;
      Err <<   Standard_Failure::Caught(); 
      Err << (char) 0;
      jcas_ThrowException(env,GetSString(Err));
    }
  }
  alock.Release(); 
  return thejret;
}


JNIEXPORT jobject JNICALL Java_jcas_Object_DynamicType
  (JNIEnv *env, jobject theobj)
{
jobject thejret=0;

jcas_Locking alock(env);
{
try {
  OCC_CATCH_SIGNALS
Handle(Standard_Transient) the_this = *((Handle(Standard_Transient)*) jcas_GetHandle(env,theobj));
Standard_CString sret = the_this->DynamicType()->Name();
jclass CLSret  = env->FindClass("jcas/Standard_CString");
thejret = env->AllocObject(CLSret);
jcas_SetCStringValue(env,thejret,sret);

}
catch (Standard_Failure) {
  Standard_SStream Err;
  Err <<   Standard_Failure::Caught(); 
  Err << (char) 0;
  jcas_ThrowException(env,GetSString(Err));
}
}
alock.Release();
return thejret;
}

JNIEXPORT jboolean JNICALL Java_jcas_Object_IsKind
   (JNIEnv *env, jobject theobj, jobject aClassName)
{
  jboolean thejret = 0;
  jcas_Locking alock(env);
  {
    try {
      OCC_CATCH_SIGNALS
      Handle(Standard_Transient)* the_this     = (Handle(Standard_Transient)*) jcas_GetHandle(env,theobj);
      Standard_CString            the_ClassName = jcas_ConvertToCString(env,aClassName);
      thejret = (*the_this)->IsKind(the_ClassName);
    } catch (Standard_Failure) {
      Standard_SStream Err;
      Err << Standard_Failure::Caught(); 
      Err << (char) 0;
      jcas_ThrowException(env,GetSString(Err));
    }
  }
  alock.Release(); 
  return thejret;
}

}


