
#include <ESP8266WiFi.h>
#include <WiFiServer.h>

WiFiServer server (80);

const char* ssid = "AndroidAP";
const char* pass = "forouhar2015";
String html;
byte s[4]={D3,D4,D5,D6};
void setup() {
  
   Serial.begin(9600);
  
for(byte i=0;i<=4;i++){
  pinMode(s[i],OUTPUT);
}


   delay(10);
   WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
 Serial.print(WiFi.localIP());
  //////////////////////////////////////HTML AND CSS///////////////////////////
html+=" <!DOCTYPE html>";
html+="<html>";
html+="<head>";
   ////////////////////////////////////CSS CODE/////////////////////////////////
html+="<style>";
html+="body{";
 html+="background-image: url(\"https://static.pexels.com/photos/172292/pexels-photo-172292.jpeg\");";
  html+="height: auto;";
  html+="width: auto;";

html+="}";
html+="#logo{";
  html+="font-family:Cambria, \"Hoefler Text\", \"Liberation Serif\", Times, \"Times New Roman\", \"serif\";";
  html+="text-align: center;";
html+="}";
html+="#main{";
  
  html+="border-radius: 20px;";
  html+="position: relative;";
  html+="background-color: aliceblue ;";
  html+="text-align: center;";
  html+="border: 3px solid black;";
  html+="margin: 0 auto;";
  html+="width: 300px;";
  html+="height: auto;";
  
html+="}";
html+="#footer{";
  html+="text-align: center;";
  html+="color: white;";
html+="}";

html+="#img{";
  html+="margin: 0 auto;";
  html+="text-align: center;";
html+="}";
html+="h3{";
  html+="font-family: Constantia, \"Lucida Bright\", \"DejaVu Serif\", Georgia, \"serif\";";
html+="}";

html+="</style>";
//////////////////////////////////////////CSS END/////////////////////////////////
html+="</head>";
html+="<body>";
// img 
  html+="<div id=\"img\">";
  html+="<img src=\"http://cdn.persiangig.com/preview/X7GDSm9Bno/13129451_1727850594105501_1964723742_a.jpg\" alt=\"logo\" height=\"150px\" width=\"150px\">";
  html+="</div>";
// main 
   html+="<div id=\"main\">";
   html+="<h1 id=\"logo\">Ahvaz robotic home</h1>";

   /////////////////////////////////BUTTON///////////////////////////
    html+="<p>Light 1 : <a href=\"light1on\"><input type=\"button\" name=\"light1on\" value=\"On\"></a><a href=\"light1off\"> <input type=\"button\" name=\"light1off\" value=\"Off\"> </a></p>";
    html+="<p>Light 2 : <a href=\"light2on\"><input type=\"button\" name=\"light2on\" value=\"On\"></a><a href=\"light2off\"> <input type=\"button\" name=\"light2off\" value=\"Off\"> </a></p>";
    html+="<p>Light 3 : <a href=\"light3on\"><input type=\"button\" name=\"light3on\" value=\"On\"></a><a href=\"light3off\"> <input type=\"button\" name=\"light3off\" value=\"Off\"> </a></p>";
    html+="<p>Light 4 : <a href=\"light4on\"><input type=\"button\" name=\"light4on\" value=\"On\"></a><a href=\"light4off\"> <input type=\"button\" name=\"light4off\" value=\"Off\"> </a></p>";
    html+="<p>Mode 1 : <a href=\"mode1\"><input type=\"button\" name=\"mode1\" value=\"Mode1\"></p></a>";
    html+="<p>Mode 2 : <a href=\"mode2\"><input type=\"button\" name=\"mode2\" value=\"Mode2\"></p></a>";
    html+="<p>All on : <a href=\"allon\"><input type=\"button\" name=\"allon\" value=\"ON\"></p></a>";
    html+="<p>All off : <a href=\"alloff\"><input type=\"button\" name=\"alloff\" value=\"OFF\"></p></a>";
 
//////////////////////////////////////////////
html+="</div>";
html+="<div id=\"footer\">";
  html+="<h3>Designer : Forouhar m.panah </h3>";
  html+="<h3>Gmail: forouhar.m.panah2001@gmail.com</h3>";
html+="</div>";

html+="</body>";
html+="</html>";

}
//////////////////////////////HTML END/////////////////////////////
void loop() {
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  client.flush();
 
 Serial.println(request);

  if (request.indexOf("light1on") != -1)digitalWrite(s[0] , HIGH);
  else if (request.indexOf("light1off") != -1)digitalWrite(s[0], LOW);
  else if (request.indexOf("light2on") != -1) digitalWrite(s[1] , HIGH);
  else if (request.indexOf("light2off") != -1) digitalWrite(s[1], LOW);
  else if (request.indexOf("light3on") != -1) digitalWrite(s[2] , HIGH);
  else if (request.indexOf("light3off") != -1) digitalWrite(s[2] ,LOW);
  else if (request.indexOf("light4on") != -1) digitalWrite(s[3],HIGH);
  else if (request.indexOf("light4off") != -1) digitalWrite(s[3] , LOW);
  else if (request.indexOf("mode1") != -1) {
    for (byte i = 0; i <= 3; i++) {
      digitalWrite(s[i], LOW);
    }
    for (byte i = 0; i <= 3; i++) {
      digitalWrite(s[i], HIGH);
      delay(1000);
    }
  }
  else if (request.indexOf("mode2") != -1) {
    for (byte i = 0; i <= 3; i++) {
      digitalWrite(s[i], HIGH);
    }
    for (byte i = 0; i <= 3; i++) {
      digitalWrite(s[i], LOW);
      delay(1000);
    }
  }
  else if (request.indexOf("allon") != -1) {
    for (byte i = 0; i <= 3; i++) {
      digitalWrite(s[i], HIGH);
    }
  }
  else if (request.indexOf("alloff") != -1) {
    for (byte i = 0; i <= 3; i++) {
      digitalWrite(s[i], LOW);
    }
  } 
  



client.println(html);
}
