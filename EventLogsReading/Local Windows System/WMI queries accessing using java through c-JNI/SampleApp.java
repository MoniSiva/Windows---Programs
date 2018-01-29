public class SampleApp {
	
	static {
		System.load("D://Windows/sample.dll"); //  (Windows) or libhello.so (Unixes) loaded dll path
    }
		
	public void printComputerName(String compName) {
		System.out.print(compName+" ");
	}
		
	public void printSourceName(String souName) {
		System.out.print(souName+" ");
	}
		
	public void printEventCode(int evecode) {
		System.out.print(evecode+" ");
	}
		
	public void printEventId(int eveid) {
		if(eveid==1)
			System.out.println("Error");
		else if(eveid==2)
			System.out.println("Warning");
		else if(eveid==3)
			System.out.println("Informational");
		else if(eveid==4)
			System.out.println("Audit Success");
		else if(eveid==5)
			System.out.println("Audit Failure");
			
	}
   
   // Native method declaration
   private native void logMessage(String message);
  
 
   // Test Driver
   public static void main(String[] args) {
	   String as="System";
		new SampleApp().logMessage(as);  // Invoke native method
   }
}