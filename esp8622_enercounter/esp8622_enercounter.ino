#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <WiFiUdp.h>
#include <FTPClient_Generic.h>
#include <AES.h>
#include <NTPClient.h>
#include <SPI.h>
#include <SD.h>

//https://github.com/Obsttube/CryptoAES_CBC/blob/master/examples/TestAES/TestAES.ino
//CryptoAES_CBC


byte key[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


extern struct rst_info resetInfo;
uint8_t rtc_memory[512];

#if 0
Lua code
https://hackaday.com/2017/06/20/practical-iot-cryptography-on-the-espressif-esp8266/
nodeid = node.chipid()
staticiv = "abcdef2345678901";
ivkey = "2345678901abcdef";
datakey = "0123456789abcdef";
passphrase = "mypassphrase";
 
data = adc.read(0)
half1 = node.random(4294967295)
half2 = node.random(4294967295)
I = string.format("%8x", half1)
V = string.format("%8x", half2)
iv = I .. V
 
encrypted_iv = crypto.encrypt("AES-CBC", ivkey, iv, staticiv)
encrypted_nodeid = crypto.encrypt("AES-CBC", datakey, nodeid,iv)
encrypted_data = crypto.encrypt("AES-CBC", datakey, data,iv)
fullmessage = nodeid .. iv .. data .. sessionID
hmac = crypto.toHex(crypto.hmac("sha1",fullmessage,passphrase))
payload = table.concat({encrypted_iv, encrypted_nodeid, encrypted_data, hmac}, ",")




python:
from Crypto.Cipher import AES
import binascii
from Crypto.Hash import SHA, HMAC
 
# define all keys
ivkey = '2345678901abcdef'
datakey = '0123456789abcdef'
staticiv = 'abcdef2345678901'
passphrase = 'mypassphrase'
 
# Convert the received string to a list
data = payload.split(&quot;,&quot;)
 
# extract list items
encrypted_iv = binascii.unhexlify(data[0])
encrypted_nodeid = binascii.unhexlify(data[1])
encrypted_data = binascii.unhexlify(data[2])
received_hash = binascii.unhexlify(data[3])
 
# decrypt the initialization vector
iv_decryption_suite = AES.new(ivkey,AES.MODE_CBC, staticiv)
iv = iv_decryption_suite.decrypt(encrypted_iv)
 
# decrypt the data using the initialization vector
id_decryption_suite = AES.new(datakey,AES.MODE_CBC, iv)
nodeid = id_decryption_suite.decrypt(encrypted_nodeid)
data_decryption_suite = AES.new(datakey,AES.MODE_CBC, iv)
sensordata = data_decryption_suite.decrypt(encrypted_data)
 
# compute hash function to compare to received_hash
fullmessage = s.join([nodeid,iv,sensordata,sessionID])
hmac = HMAC.new(passphrase,fullmessage,SHA)
computed_hash = hmac.hexdigest()
 
# see docs.python.org/2/library/hmac.html for how to compare hashes s
#endif

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

  char ftp_server[] = "192.168.2.112";

  char ftp_user[]   = "ftp_test";
  char ftp_pass[]   = "ftp_test";

  char dirName[]    = "/home/ftp_test";
  char newDirName[] = "/home/ftp_test/NewDir";

FTPClient_Generic ftp (ftp_server, ftp_user, ftp_pass, 60000);

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer

#if 0
   if(!ESP.rtcUserMemoryRead(0, &rtc_memory, sizeof(rtc_memory))) {
    Serial.println("RTC read failed!");
    while(1)
      yield();
  }


  if(!ESP.rtcUserMemoryWrite(0, &rtc_memory, sizeof(rtc_memory))) {
    Serial.println("RTC write failed!");
    while(1)
      yield();
  }
#endif

  Serial.println('\n');

  wifiMulti.addAP("ssid_from_AP_1", "your_password_for_AP_1");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");
  int i = 0;

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
     String dataString = "";
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }  else {
    Serial.println("error opening datalog.txt");
  }

  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(1000);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

if ( resetInfo.reason == REASON_DEEP_SLEEP_AWAKE ) {
}
  if (rtc_memory[0] == 0) {
    Serial.println("Will wake up with radio!");
    ESP.deepSleep(5000000, WAKE_RFCAL);
  } else {
    Serial.println("Will wake up without radio!");
    ESP.deepSleep(5000000, WAKE_RF_DISABLED);
  }

  ftp.OpenConnection();
  ftp.ChangeWorkDir(dirName);
  ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  
  ftp.NewFile("hello_world.txt");
  ftp.Write("Hi, I'm a new file");
  ftp.CloseFile();

   timeClient.begin();
   timeClient.update();

     time_t epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);

}


void loop() {

 }