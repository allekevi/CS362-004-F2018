

import junit.framework.TestCase;

// import library for random numbers 
import java.util.random 

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   //runs test of array of testable urls
   //String[] tests should be an array of urls to be tested
   //String type is the type of UrlValidator being tested i.e default, All_Schemes_Allowed ...
   //boolean true for array of valid urls, false for invalid urls 
   public void runTest(UrlValidator val, String[] tests, String type, boolean good) {
	   for(String test:tests) {
		   try {
			   if(val.isValid(test) && !good) {
				   System.out.println(type + " has " + test + " as valid");
			   }
			   else if (!val.isValid(test) && good) {
				   System.out.println(type + " has " + test + " as invalid");
			   }
		   }
		   catch(Throwable er) {
			   System.out.println(type +" had a "+ er +" when testing " + test);
		   }
	   }
   }
   
   public void testManualTest()
   {
	   //array of schemes to test different UrlValidator constructor
	   String[] schemes = {"https", "http", "ftp", "file"}; 
	   //array of valid URLs
	   String[] valids = {"http://www.google.com", "https://www.wellsfargo.com", "ftp://google.com", "www.yahoo.com"};
	   //array of invalid URLS
	   String[] invalids = {"htp://www.google.com", "http:/www.garbage.dumb", "ftp://255.255.255.300"};
	   
	   UrlValidator urlValDefault = new UrlValidator();
	   UrlValidator urlValAll = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   UrlValidator urlValScheme = new UrlValidator(schemes);

	   runTest(urlValDefault, valids, "default", true);
	   runTest(urlValDefault, invalids, "default", false);
	   
	   runTest(urlValAll, valids, "All schemes", true);
	   runTest(urlValAll, invalids, "All schemes", false);
	   
	   runTest(urlValScheme, valids, "user schemes", true);
	   runTest(urlValScheme, invalids, "user schemes", false);
   
   }
   
   
   public void testYourFirstPartition()
   {
	   System.out.println();
	   System.out.println("1st Partition");
	   //array of schemes to test different UrlValidator constructor
	   String[] schemes = {"https", "http", "ftp", "file"};
	   
	   //String to act a base url to attach different valid and invalid schemes to
	   String base = "www.google.com";
	   
	   //array containing valid schema
	   String[] validScheme = {"http://", "https://", "ftp://", "file://"};
	   
	   //array containing invalid schema
	   String[] invalidScheme = {"htp://", "http:/", "12://", "2test://", ":- why", "8=D://"};
	   
	   //No need for ALLOW_ALL_SCHEMES type, as it will pass everything
	   UrlValidator urlValDefault = new UrlValidator();
	   UrlValidator urlValScheme = new UrlValidator(schemes);
	   //loop through valid schemes to build url
	   for(int i =0; i < validScheme.length; i++) {
		   String testCase = validScheme[i] + base;
		   if(!urlValDefault.isValid(testCase)) {
			   System.out.println("default has " + testCase + " as invalid");
		   }
		   if (!urlValScheme.isValid(testCase)) {
			   System.out.println("user schemes has " + testCase + " as invalid");
		   }
	   }
	   //loop through invalid schemes to build url
	   for(int i =0; i < invalidScheme.length; i++) {
		   String testCase = invalidScheme[i] + base;
		   if(urlValDefault.isValid(testCase)) {
			   System.out.println("default has " + testCase + " as valid");
		   }
		   if (urlValScheme.isValid(testCase)) {
			   System.out.println("user schemes has " + testCase + " as valid");
		   }
	   }
   }
   
   public void testYourSecondPartition(){
	   System.out.println();
	   System.out.println("2nd Partition");
	   //The second partition case will be urls which have their parts in order
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //Test 1: Valid URL
	   if (validator.isValid("https://www.projectalpha.com/browse/#svod?method=show"))
		   System.out.println("TEST PASSED");
	   else
		   System.out.println("TEST FAILED");
	   
	   //Test 2: All components invalid
	   if (!validator.isValid("htp://w.project.abcedfg:123456789//show?!try=this"))
		   System.out.println("TEST PASSED");
	   else
		   System.out.println("TEST FAILED");
	   
	   //Test 3: Mixed validity
	   if (!validator.isValid("https://ww.projectalpha.com/browse/#svod??method=show"))
		   System.out.println("TEST PASSED");
	   else
		   System.out.println("TEST FAILED");
	   
	   //Test 4: Missing components
	   if (!validator.isValid("://www.projectalpha/browse/#svod?method=show"))
		   System.out.println("TEST PASSED");
	   else
		   System.out.println("TEST FAILED");
	   
	   //Test 5: Optional components omitted
	   if (validator.isValid("https://www.projectalpha.com"))
		   System.out.println("TEST PASSED");
	   else
		   System.out.println("TEST FAILED");
	   
	   //Test 6: Optional Components omitted, extant components invalid
	   if (!validator.isValid("ps://.projectalpha.asdf"))
		   System.out.println("TEST PASSED");
	   else
		   System.out.println("TEST FAILED");
	   
	   //Test 7: Testing special case file://
	   if (!validator.isValid("file://test?file=component"))
		   System.out.println("TEST PASSED");
	   else
		   System.out.println("TEST FAILED");
   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   Random random_number = new Random();
	   
	   int maxport = 0, minport = 0, minIP =0, maxIP=0; 

	   int portNumber, ipOctet; 

	   String baseIP = "http://192.160.100."; 
	   String baseURL = "http://www.google.com:";

	   // loop to test random port numbers 
	   for (int i=0; i<100; i++)
	   {
	   		minport = -999; 
	   		maxport = 99999;

	   		//generate random port number in min to max range 

	   		portNumber = minport + random_number.nextInt((maxport - minport) + 1);

	   		// create testURL from base URL and random port number 

	   		String testURL = baseURL + portNumber; 

	   		// test for false negatives and false positives of valid / invalid URLs w random ports 
	   		if(portNumber >= 0 && portNumber <= 65535)
	   		{
	   			if(!validator.isValid(testURL))
	   				System.out.println("TEST FAILED - Port " + portNumber + " is valid!");
	   		}
	   		else {
	   			if (validator.isValid(testURL))
	   				System.out.println("TEST FAILED - Port " + portNumber + " is invalid!"); 
	   		}

	   		//clear testURL to run again 
	   		testURL = ""; 

	   		// generate random number for 4th IP octet 
	   		minIP = 0; 
	   		maxIP = 999; 

	   		ipOctet = minIP + random_number.nextInt((maxIP - minIP) + 1);

	   		// create test IP URL with baseIP URL and random 4th octet 
	   		String testIP = baseIP + ipOctet; 

	   		// test for false negatives and false positives of valid / invalid IP URLs 
	   		if(ipOctet < 256)
	   		{
	   			if(!validator.isValid(testIP))
	   				System.out.println("TEST FAILED - IP octet " + testIP + " is valid!");
	   		}
	   		else {
	   			if(validator.isValid(testIP))
	   			System.out.println("TEST FAILED - IP ip octet " + testIP + " is invalid!");
	   		}

	   		// clear test IP URL to run again 
	   		testIP = ""; 
	   }
   }
   


}
