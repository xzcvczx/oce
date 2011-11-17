package jcas;

public class CasCadeException extends RuntimeException {

 static {
    System.loadLibrary("TKjcas");
 }

  CasCadeException() {
  }

  CasCadeException(String message) {
    super(message);
  }

}
