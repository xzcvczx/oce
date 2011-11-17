

package jcas;

import jcas.Locker;
import jcas.Standard_CString;

public abstract class Object {

 static {
    System.loadLibrary("TKjcas");
 }

  static public Locker myCasLock = new Locker();

  public long HID = 0;
  // BBL
  // cf Engine_Handle : always True then use delete operator on theHID
  // except for return value by reference False don't delete the returned
  // reference ( CF CCL )
  //

  public long aVirer = 1;

  protected java.lang.Object clone()
                throws CloneNotSupportedException
  {
    throw new CloneNotSupportedException();
  }

  public native Object DownCast(Standard_CString aClassName,
                                Standard_CString aPackageName);  

}
