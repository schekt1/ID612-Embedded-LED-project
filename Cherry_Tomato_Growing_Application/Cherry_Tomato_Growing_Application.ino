//cherry tomato growing application

/*USE CASES
1) Read humidity of your environment
2) Read temperature of your environment
3) Read temperature in both celsius and fahrenheit for your environment
4) Read light sensitivity in relation to sunlight exposure
4) Run's test on given conditions such as temperature being above a certain level for growing cherry tomatoes
5) Test resolves in clear inditication of result e.g. green for pass, red for fail
6) Error checking provides an error message if test fails */


#include "DHT.h" //recyled code from DHT sensor library: DHTtester

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int keyPin = 3;

float humidity;

float celsius;

float fahrenheit;

int photoresistor = 0; //recycled code from Sparkfun Circuit 1C: Photoresistor
int threshold = 800;  

void setup() {

  Serial.begin(9600); 

  pinMode(4, OUTPUT); //Set pin 4 to output green LED

  pinMode(5, OUTPUT); //Set pin 5 to output red LED 

  dht.begin(); //initalises DHT11 sensor 

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  photoresistor = analogRead(A0);
  Serial.println(photoresistor); 
  
  humidity = dht.readHumidity(); //digital read humidity w/ DHT11 sensor

  celsius = dht.readTemperature(); //digital read temperature in celsius w/ DHT11 sensor

  fahrenheit = dht.readTemperature(true); //digital read temperature in fahrenheit w/ DHT11 sensor

  if (isnan(humidity) || isnan(celsius) || isnan(fahrenheit)) { //recyled code from DHT sensor library: DHTtester
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
  }

  Serial.print(F("Humidity: ")); //reycled code from DHT sensor library: DHTtester 
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(celsius);
  Serial.print(F("°C "));
  Serial.print(fahrenheit);
  
  Serial.println("Test Conditions: Tomatoes");
  delay(3000);

  //testing conditions for growing tomatoes (these can be interchangeable depending on what conditions are required for what you are trying to incubate and grow
  if ((photoresistor > threshold) && (celsius >= 10.00) && (celsius <= 95.00) && (humidity <= 85.0) && (humidity >= 60.0)){ 
  Serial.println("Testing...");
  delay(3000);
  digitalWrite(4, HIGH); //if test pases turn on green LED
  Serial.println("Test Passed!"); 
  }else{
  Serial.println("Testing...");
  delay(3000);
  digitalWrite(5, HIGH); //if test fails turn on red LED
  Serial.println("Test Failed!");

  if(photoresistor < threshold){ //error checking displays to the user issues occuring if they occur
  Serial.println("Insufficent sunlight");
  }

  if(celsius < 10.00){
  Serial.println("Temperature too low"); //temperture reading outputs error when it occurs
  }

  if(celsius > 95.00){
  Serial.println("Temerature too high"); //temperature reading outputs error when it occurs
  }

  if(humidity > 85.0){
  Serial.println("Humidity too high"); //humidity outputs error when it occurs
  }

  if(humidity < 60.0){
  Serial.println("Humidity too low"); //humidity outpust error when it occurs
  }
  }
}
