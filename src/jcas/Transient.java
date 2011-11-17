

package jcas;

public class Transient extends jcas.Object {

 static {
    System.loadLibrary("TKjcas");
 }

  native public final boolean IsNullObj();

  native static void FinalizeID(long anHID);

  public void finalize() {
    synchronized(myCasLock) {
      if ( aVirer != 0 ) FinalizeID(HID);
      HID = 0;
    }
  }

}
