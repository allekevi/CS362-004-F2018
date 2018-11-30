

import junit.framework.TestCase;

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
	   //array of schemes to test different UrlValidator constructor
	   String[] schemes = {"https", "http", "ftp", "file"};
	   
	   //String to act a base url to attach different valid and invalid schemes to
	   String base = "http://www.google.";
	   
	   //array containing valid TLDs
	   String[] validTLD = {"com", "org", "edu", "net"};
	   
	   //array containing invalid TLDS
	   String[] invalidTLD = {"/", "342", "12://", "2test", ":-", "8=D"};
	   
	   UrlValidator urlValAll = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   UrlValidator urlValDefault = new UrlValidator();
	   UrlValidator urlValScheme = new UrlValidator(schemes);
	   
	   //loop through valid schemes to build url
	   for(int i =0; i < validTLD.length; i++) {
		   String testCase = base + validTLD[i];
		   if(!urlValDefault.isValid(testCase)) {
			   System.out.println("default has " + testCase + " as invalid");
		   }
		   if (!urlValScheme.isValid(testCase)) {
			   System.out.println("user schemes has " + testCase + " as invalid");
		   }
		   if (!urlValAll.isValid(testCase)) {
			   System.out.println("ALL schemes has " + testCase + " as invalid");
		   }
	   }
	   //loop through invalid schemes to build url
	   for(int i =0; i < invalidTLD.length; i++) {
		   String testCase = base + invalidTLD[i];
		   if(urlValDefault.isValid(testCase)) {
			   System.out.println("default has " + testCase + " as valid");
		   }
		   if (urlValScheme.isValid(testCase)) {
			   System.out.println("user schemes has " + testCase + " as valid");
		   }
		   if (urlValAll.isValid(testCase)) {
			   System.out.println("ALL schemes has " + testCase + " as valid");
		   }
	   }   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
