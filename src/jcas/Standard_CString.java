package jcas;

public class Standard_CString {

  private String value;


  public Standard_CString() {
  }

  public Standard_CString(String aval) {
    value = aval;
  }

  public String GetValue() {
    return value;
  }

  public void SetValue(String aval) {
    value = aval;
  }

  public String toString() {
    return value;
  }
}



