// Copyright: 	Matra-Datavision 1999
// File:	jcas.cxx
// Created:	Fri Mar 26 14:38:44 1999
// Author:	Arnaud BOUZY
//		<adn>

#include <jcas.hxx>
#include <Standard_PrimitiveTypes.hxx>
#include <Standard_ExtCharacter.hxx>
#include <Standard_PExtCharacter.hxx>

#include <Standard_Macro.hxx>

#include <TCollection_ExtendedString.hxx>
#include <TCollection_AsciiString.hxx>

#define EXTSTRLEN(s,i) {(i) = 0;while((s)[(i)++] != 0);(i)--;}

#ifndef WNT
#define bool Standard_Boolean
#define false Standard_False
#define true  Standard_True
#endif

#define CLASSFILE "ClassFile.cfg"

  // add aVirer in jcas.Object
  // cf Engine_Handle : always True then use delete operator on theHID
  // except for return value by reference False don't delete the returned
  // reference ( CF CCL )
  //

// #define DEBUG

extern "C" {


static jclass jcas_FindClass( JNIEnv *env, char *className) {
                  
  jclass cls1 = env->FindClass(className);
  jclass retcls = 0;
  
  if (!cls1) {
    return retcls;
  }
  
  retcls = (jclass) env->NewGlobalRef(cls1);
  
  return retcls;
}

static bool IsInBase(FILE *f, char *pkName)
{
	char str[1024];
	char *dest;
	int pos;
	bool IsIn = false;

	rewind(f);
	fgets(str, 1024, f);
	dest = strchr(str, ']');
	if ( dest != NULL )
	{
		while ( !feof(f) )
		{
			fgets(str, 1024, f);
			dest = strchr(str, '\n');
			if ( dest != NULL )
			{
				pos = dest - str;
				str[pos] = '\0';
			}
			else
				continue;
	
//			cout << "IsInBase : checking names are   " << pkName << "      " << str << endl;
				
			if ( strcmp(pkName, str) == 0 )
			{
//				cout << "IsInBase : check names EQUAL !" << endl;
				IsIn = true;
			}
			
			dest = strchr(str, ']');
			if ( dest != NULL)
				break;
		}
	}

	return IsIn;
}

static jclass FindCl(JNIEnv *env, char *pkName, char *clName)
{
	FILE *f;
	char newName[1024], curClass[1024], str[1024];
	char *dest;
	int pos=0;
//	jclass retcls = 0;

	sprintf(newName, "%s%s", pkName, clName);

	f = fopen(CLASSFILE, "r");
	if( !f )
	{
//		cout << "  FindCl : Can't open file " << CLASSFILE << " !" << endl;
//		fclose(f);
		// Necessary for tracking:
//		cout << "FindClass for : " << newName << endl;
		return env->FindClass(newName);
	}

	if ( IsInBase(f, pkName) )
	{

//		cout << "  FindCl : IsInBase of " << pkName << " is TRUE !" << endl;

		// Check Base Class

		fgets(str, 1024, f);
		dest = strchr(str, '\n');
		if ( dest != NULL )
		{
			pos = dest - str;
			str[pos] = '\0';
		}

		sprintf(curClass, "%s", str);

		while ( !feof(f) )
		{
			fgets(str, 1024, f);
			dest = strchr(str, '\n');
			if ( dest != NULL )
			{
				pos = dest - str;
				str[pos] = '\0';
			}
				
			if ( str[0] != '/' )
			{
				sprintf(curClass, "%s", str);
				continue;
			}

//			cout << "FindCl : checking names are   " << clName << "         " << str << endl;

			if ( strcmp(clName, str) == 0 )
			{
//				cout << "FindCl : check names EQUAL !" << endl;
				sprintf(newName, "%s%s", curClass, clName);
				break;
			}
		}
	}
//	else
//		cout << "  FindCl : IsInBase of " << pkName << " is FALSE !" << endl;

// Necessary for tracking:
#ifdef DEBUG
	cout << "FindClass for : " << newName << endl;
#endif

	fclose(f);
	return env->FindClass(newName);
}


static jclass jcas_FindClasses(JNIEnv *env, char *className)
{
	char Pstr[1024], Cstr[1024];
	unsigned i;
	char clPart, Np, Nc;

	Np = 0;
	Nc = 0;
	clPart = 0;
	for ( i = 0; i < strlen(className); i++ )
	{
		if ( *(className + i) == '/' )
		{
			if ( (Np > 0) && (Nc > 0) )
			{
				Pstr[Np] = '\0';
				Np++;
				Cstr[Nc] = '\0';
				Nc++;
				strcat(Pstr, Cstr);
				Np += Nc;
				Nc = 0;
			}
			clPart = 1;
		}

		if ( clPart )
		{
			Cstr[Nc] = *(className + i);
			Nc++;
		}
		else
		{
			Pstr[Np] = *(className + i);
			Np++;
		}
	}
	Pstr[Np] = '\0';
	Cstr[Nc] = '\0';


//	cout << "jcas_FindClasses : Pack = " << Pstr << "; Class = " << Cstr << endl;

	return FindCl(env, Pstr, Cstr);
}

static jfieldID jcas_TheHID(JNIEnv *env)
{
  
  static Standard_Boolean initok = Standard_False;
  static jfieldID jcasHIDfid;
  static jclass jcasClass;

  if (!initok) {
    jcasClass = jcas_FindClass( env, "jcas/Object" );
    if (jcasClass) {
      jcasHIDfid = env->GetFieldID(jcasClass, "HID", "J");
      initok = Standard_True;
    }
  }
  
  return jcasHIDfid;
}

static jfieldID jcas_TheaVirer(JNIEnv *env)
{ static Standard_Boolean initok = Standard_False;
  static jfieldID jcasaVirerfid;
  static jclass jcasClass;

  if (!initok) {
    jcasClass = jcas_FindClass( env, "jcas/Object" );
    if (jcasClass) {
      jcasaVirerfid = env->GetFieldID(jcasClass, "aVirer", "J");
      initok = Standard_True;
    }
  }
  
  return jcasaVirerfid;
}

int jcas_GetaVirer(JNIEnv *env, jobject anobj) 
{
  jlong theadd = env->GetLongField(anobj, jcas_TheaVirer(env));
  return  (int) theadd;
}

void jcas_SetaVirer(JNIEnv *env, jobject anobj, int aVirer)
{
   env->SetLongField(anobj, jcas_TheaVirer(env) , (long) aVirer);
}

Standard_EXPORT void* jcas_GetHandle(JNIEnv *env, jobject anobj)
{
  if (anobj == NULL) return NULL;
  jlong theadd = env->GetLongField(anobj, jcas_TheHID(env));
  return  (void*) theadd;
}

Standard_EXPORT void jcas_SetHandle(JNIEnv *env, jobject anobj, const void* ahand)
{
  jlong theadd = (jlong) ahand;
  env->SetLongField(anobj, jcas_TheHID(env), theadd);
}

static jobject jcas_CurThread(JNIEnv *env)
{
  jclass cls = env->FindClass("java/lang/Thread");
  jmethodID mid = env->GetStaticMethodID(cls,"currentThread","()Ljava/lang/Thread;");
  return env->CallStaticObjectMethod(cls,mid);
}
 

static const char* jcas_CurThreadName( JNIEnv *env)
{
  jclass cls = env->FindClass("java/lang/Thread");
  jmethodID mid = env->GetStaticMethodID(cls,"currentThread","()Ljava/lang/Thread;");
  jobject theth = env->CallStaticObjectMethod(cls,mid);
  mid = env->GetMethodID(cls,"getName","()Ljava/lang/String;");
  jstring thename = (jstring) env->CallObjectMethod(theth,mid);
  jboolean iscopy ;
  iscopy = JNI_TRUE;
  return  env->GetStringUTFChars(thename,&iscopy);
  
  
}

Standard_EXPORT void jcas_Lock(JNIEnv *env)
{
  jclass cls = env->FindClass("jcas/Object");
  jfieldID fid = env->GetStaticFieldID(cls,"myCasLock","Ljcas/Locker;");
  jobject thelocker = env->GetStaticObjectField(cls,fid);
  env->MonitorEnter(thelocker);
}

Standard_EXPORT void jcas_Unlock(JNIEnv *env)
{
  jclass cls = env->FindClass("jcas/Object");
  if (cls != 0) {
    jfieldID fid = env->GetStaticFieldID(cls,"myCasLock","Ljcas/Locker;");
    jobject thelocker = env->GetStaticObjectField(cls,fid);
    env->MonitorExit(thelocker);
  }
}


Standard_EXPORT void jcas_ThrowException(JNIEnv *env, char* message)
{
  jclass newExcCls;
  cout << message << endl;
  env->ExceptionClear();

  newExcCls = env->FindClass("jcas/CasCadeException");
  if (newExcCls != 0) {
    jcas_Unlock(env);
    env->ThrowNew(newExcCls, message);
  }
}

Standard_EXPORT jobject jcas_CreateObject(JNIEnv *env, char * aJavaClass,const void* ahand, const int aVirer)
{
  char mess[1000];
  jobject ret; 

//  cout << "jcas_CreateObject : enter with  " << aJavaClass << "     (ahand = " << ahand << ")  " << endl;

//  jclass CLS  = env->FindClass( aJavaClass );
  jclass CLS  = jcas_FindClasses(env, aJavaClass);	
  
  if ( CLS == NULL )
  {
	  cout << "  jcas_CreateObject : Cann't find class " << aJavaClass << " ==> don't create object !" << endl;
	  return NULL;
  }

  jmethodID mid = env->GetMethodID(CLS, "<init>", "()V");

  if (mid == 0) {
    sprintf(mess,"Unable to get empty constructor for java class %s",aJavaClass);
    jcas_ThrowException(env,mess);
  }
  else {
    ret = env->NewObject(CLS, mid);
    if (ret == 0) {
      sprintf(mess,"Unable to create java object %s",aJavaClass);
      jcas_ThrowException(env,mess);
    }
    else {
      env->SetLongField(ret,jcas_TheHID(env) , (long) ahand);
      env->SetLongField(ret,jcas_TheaVirer(env) , (long) aVirer);
    }
  }
  return ret;
}



Standard_EXPORT jstring jcas_ConvertTojstring(JNIEnv *env, const Standard_ExtString astr)
{
  int thelen;
  EXTSTRLEN(astr,thelen);
  return env->NewString((const unsigned short*) astr,thelen);
}

Standard_EXPORT const Standard_ExtString jcas_ConvertToExtString(JNIEnv *env, jstring astr)
{
	/*
  jboolean iscopy;
  iscopy = JNI_TRUE;
  return (const Standard_ExtString) env->GetStringChars(astr,&iscopy);
	*/
	/*
  jboolean iscopy;
  iscopy = JNI_FALSE;
  jsize aLen = env->GetStringLength(astr);
  const jchar *aOldCharPtr = env->GetStringChars(astr,&iscopy);
  jstring aNewString = env->NewString(aOldCharPtr, aLen+1);
  iscopy = JNI_TRUE;
  const jchar *aCharPtr = env->GetStringChars(aNewString,&iscopy);
  env->ReleaseStringChars(astr, aOldCharPtr);
  
  aCharPtr[aLen] = 0; // <-- Causes error, because we cann't modify const object
  return (const Standard_ExtString) aCharPtr;
	*/
	
  jboolean iscopy; 
  iscopy = JNI_FALSE; 
  jsize aLen = env->GetStringLength(astr); 
  const jchar *aCharPtr = env->GetStringCritical(astr,&iscopy);
  const jchar *aCharPtrMoved = aCharPtr;

  // Allocate string buffer 
  TCollection_ExtendedString *aExtendedString = new TCollection_ExtendedString(aLen, '\0'); 
  // Copy string data to buffer 
  Standard_PExtCharacter aNewCharPtr = (Standard_PExtCharacter)aExtendedString->ToExtString(); 
  while(aLen) { *aNewCharPtr++ = *aCharPtrMoved++; aLen-- ;} 

  // Inform Java VM that we finished with string so it may be free 
  env->ReleaseStringCritical(astr, aCharPtr); 
  return aExtendedString->ToExtString(); 
	
}

Standard_EXPORT const Standard_CString jcas_ConvertToCString(JNIEnv *env, jobject astr)
{
  jclass cls = env->GetObjectClass( astr);
  jfieldID fid = env->GetFieldID(cls, "value", "Ljava/lang/String;");
  jstring thejstr = (jstring) env->GetObjectField(astr , fid);
  if (thejstr == 0) {
    return NULL;
  }
	
	
  jboolean iscopy ;
  iscopy = JNI_TRUE;
  return (const Standard_CString) env->GetStringUTFChars(thejstr,&iscopy);
	
/*	
  jboolean iscopy; 
  iscopy = JNI_FALSE; 
  jsize aLen = env->GetStringUTFLength(thejstr); 
  const char *aCharPtr = env->GetStringUTFChars(thejstr,&iscopy); 

  // Allocate string buffer 
  TCollection_AsciiString *anAsciiString = new TCollection_AsciiString(aLen, '\0'); 
  // Copy string data to buffer 
  Standard_CString aNewCharPtr = anAsciiString->ToCString(); 
  while(aLen) { *aNewCharPtr++ = *aCharPtr++; aLen-- ;} 

  // Inform Java VM that we finished with string so it may be free 
  env->ReleaseStringUTFChars(thejstr, aCharPtr); 

  return anAsciiString->ToCString();*/
}

Standard_EXPORT void jcas_SetCStringValue(JNIEnv *env, jobject astr,const Standard_CString fromstr)
{
  jclass cls = env->GetObjectClass( astr);
  jfieldID fid = env->GetFieldID(cls, "value", "Ljava/lang/String;");
  jstring theres = env->NewStringUTF(fromstr);
  env->SetObjectField(astr,fid,theres);
}

Standard_EXPORT const Standard_ExtString jcas_ConvertSBToExtString(JNIEnv *env, jobject astr)
{
  jclass cls = env->GetObjectClass( astr);
  jmethodID mid = env->GetMethodID(cls,"toString","()Ljava/lang/String;");

  if (mid == 0) {
    cout << "Cannot find method toString for StringBuffer" << endl;
    return 0L;
  }
  jstring thestr = (jstring) env->CallObjectMethod(astr,mid);
  return jcas_ConvertToExtString(env,thestr);
}

Standard_EXPORT void jcas_SetExtStringToStringBuffer(JNIEnv *env, jobject astr,const Standard_ExtString fromstr)
{
  jstring thefrom = jcas_ConvertTojstring(env,fromstr);
  jclass cls  = env->FindClass( "java/lang/StringBuffer");
  jmethodID midlen = env->GetMethodID(cls,"length","()I");
  if (midlen == 0) {
    cout << "Cannot find method length for StringBuffer" << endl;
  }
  else {
    jint thelen = env->CallIntMethod(astr,midlen);
    if (thelen > 0) {
      jmethodID midrep = env->GetMethodID(cls,"replace","(IILjava/lang/String;)Ljava/lang/StringBuffer;");
      if (midrep == 0) {
	cout << "Cannot find method replace for StringBuffer" << endl;
      }
      else {
	env->CallObjectMethod(astr,midrep,0,thelen,thefrom);
      }
    }
    else {
      jmethodID midapp = env->GetMethodID(cls,"append","(Ljava/lang/String;)Ljava/lang/StringBuffer;");
      if (midapp == 0) {
	cout << "Cannot find method append for StringBuffer" << endl;
      }
      else {
	env->CallObjectMethod(astr,midapp,thefrom);
      }
    }
      
  }
      
}


Standard_EXPORT Standard_Boolean jcas_GetBoolean(JNIEnv *env, jobject abool)
{
  jclass cls = env->GetObjectClass(abool);
  jfieldID fid = env->GetFieldID(cls, "value", "Z");
  jboolean thejval = (jboolean) env->GetBooleanField(abool , fid);
  return thejval;
}

Standard_EXPORT Standard_Real jcas_GetReal(JNIEnv *env, jobject areal)
{
  jclass cls = env->GetObjectClass(areal);
  jfieldID fid = env->GetFieldID(cls, "value", "D");
  jdouble thejval = (jdouble) env->GetDoubleField(areal , fid);
  return thejval;
}

Standard_EXPORT Standard_Character jcas_GetCharacter(JNIEnv *env, jobject anobj)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "C");
  jchar thejval = (jchar) env->GetCharField(anobj , fid);
  return ::ToCharacter(thejval);
}

Standard_EXPORT Standard_Integer jcas_GetInteger(JNIEnv *env, jobject anobj)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "I");
  jint thejval = (jint) env->GetIntField(anobj , fid);
  return thejval;
}

Standard_EXPORT Standard_ExtCharacter jcas_GetExtCharacter(JNIEnv *env, jobject anobj)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "C");
  jchar thejval = (jchar) env->GetCharField(anobj , fid);
  return thejval;
}

Standard_EXPORT Standard_Byte jcas_GetByte(JNIEnv *env, jobject anobj)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "B");
  jbyte thejval = (jbyte) env->GetByteField(anobj , fid);
  return thejval;
}

Standard_EXPORT Standard_ShortReal jcas_GetShortReal(JNIEnv *env, jobject anobj)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "F");
  jfloat thejval = (jfloat) env->GetFloatField(anobj , fid);
  return thejval;
}

Standard_EXPORT short jcas_GetShort ( JNIEnv* env, jobject anobj ) {

 jclass   cls    =           env -> GetObjectClass ( anobj             );
 jfieldID fid    =           env -> GetFieldID     ( cls, "value", "S" );
 jshort  thejval = ( jshort )env -> GetByteField   ( anobj, fid        );

 return thejval;

}  // end jcas_GetShort

Standard_EXPORT void jcas_SetBoolean(JNIEnv *env, jobject abool,Standard_Boolean aval)
{
  jclass cls = env->GetObjectClass(abool);
  jfieldID fid = env->GetFieldID(cls, "value", "Z");
  env->SetBooleanField(abool , fid, aval);
}

Standard_EXPORT void jcas_SetReal(JNIEnv *env, jobject areal,Standard_Real aval)
{
  jclass cls = env->GetObjectClass(areal);
  jfieldID fid = env->GetFieldID(cls, "value", "D");
  env->SetDoubleField(areal , fid, aval);
}

Standard_EXPORT void jcas_SetCharacter(JNIEnv *env, jobject anobj,Standard_Character aval)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "C");
  jchar theres = ::ToExtCharacter(aval);
  env->SetDoubleField(anobj , fid, theres);
}

Standard_EXPORT void jcas_SetInteger(JNIEnv *env, jobject anobj,Standard_Integer aval)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "I");
  env->SetIntField(anobj , fid, aval);
}

Standard_EXPORT void jcas_SetExtCharacter(JNIEnv *env, jobject anobj,Standard_ExtCharacter aval)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "C");
  env->SetCharField(anobj , fid, aval);
}

Standard_EXPORT void jcas_SetByte(JNIEnv *env, jobject anobj,Standard_Byte aval)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "B");
  env->SetByteField(anobj , fid, aval);
}

Standard_EXPORT void jcas_SetShortReal(JNIEnv *env, jobject anobj,Standard_ShortReal aval)
{
  jclass cls = env->GetObjectClass(anobj);
  jfieldID fid = env->GetFieldID(cls, "value", "F");
  env->SetFloatField(anobj , fid, aval);
}

Standard_EXPORT void jcas_SetShort ( JNIEnv *env, jobject anobj, short aval ) {

 jclass   cls = env -> GetObjectClass ( anobj             );
 jfieldID fid = env -> GetFieldID     ( cls, "value", "S" );

 env -> SetShortField ( anobj, fid, aval );

}  // end jcas_SetShort


Standard_EXPORT jcas_Locking::jcas_Locking(JNIEnv *env)
{
  myenv = env;
  jcas_Lock(env);
}


Standard_EXPORT void jcas_Locking::Release()
{
}

Standard_EXPORT jcas_Locking::~jcas_Locking()
{
  jcas_Unlock(myenv);
}

}
