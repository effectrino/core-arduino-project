#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>

#define _API_USE_BSD_CLOSE true

//#include <Ethernet.h>
#include <WSClient.h>

#include <duino-tools.h>

#define SPI_SCK_PIN  14
#define SPI_MOSI_PIN  11
#define SPI_MISO_PIN  12

// CC3000 interrupt and control pins
#define ADAFRUIT_CC3000_IRQ_PIN   7 // MUST be an interrupt pin!
#define ADAFRUIT_CC3000_VBAT_PIN  8 // These can be
#define ADAFRUIT_CC3000_CS_PIN   15 // any two pins

Adafruit_CC3000 cc3000 = Adafruit_CC3000(
  ADAFRUIT_CC3000_CS_PIN, 
  ADAFRUIT_CC3000_IRQ_PIN, 
  ADAFRUIT_CC3000_VBAT_PIN,
  SPI_CLOCK_DIVIDER
);

Adafruit_CC3000_Client cc3000WSClient;
WSClient websocket;

void setup() {

  delay(500);
  initDebug(true);
  delay(500);

  cc3000.setPrinter(&Debug);
  
  SPI.setSCK(SPI_SCK_PIN);
  SPI.setMOSI(SPI_MOSI_PIN);
  SPI.setMISO(SPI_MISO_PIN);
  
  SPI.begin();
  
  // TODO repeat every 60 seconds
  if ( initWiFi() ) {
    connectToWebSocketServer();
  }
}

boolean connectToWiFi(const char *ssid, const char *pass, uint8_t sec, uint8_t connectionAttempts = 0)
{
  Debug << "Attempting to connect to " << ssid << "... ";

  if ( !cc3000.connectToAP(ssid, pass, sec, connectionAttempts) )
  {
    Debug << "Failed!" << CRLF;
    return false;
  }
   
  Debug << "Connected!" << CRLF;

  Debug << "Requesting DHCP... ";
  
  const int attemptsMaxCount = 20;
  int attemptsCounter = 0;

  while ( attemptsCounter < attemptsMaxCount )
  {
    if ( cc3000.checkDHCP() )
    {
      Debug << "Done!" << CRLF;
      displayConnectionDetails();
      return true;
    }

    Debug << "DHCP failure!" << CRLF;
    attemptsCounter++;

    delay(1000);
  }
  
  return false;
}

boolean connectToWebSocketServer()
{
  const char *serverName = "echo.websocket.org";
  
  uint32_t ip;

  Debug << "Resolving " << serverName << "..." << CRLF;
  
  cc3000.getHostByName(serverName, &ip);
  
//  Debug << "Connecting to WebSocket server "; cc3000.printIPdotsRev(&ip); Debug << "... ";
  Debug << "Connecting to WebSocket server " << serverName << "... ";

  cc3000WSClient = cc3000.connectTCP(ip, 80);

  if ( ! cc3000WSClient.connected() ) {
    Debug << "Failed!" << CRLF;
    return false;
  }

  Debug << "Done!" << CRLF;

  // Define path and host for Handshaking with the server
  websocket.path = "/";
  websocket.host = (char *)serverName;

  Debug << "Handshake... ";

  if ( !websocket.handshake(cc3000WSClient) ) {
    Debug << "Failed!" << CRLF;
    return false;
  }

  Debug << "Done!" << CRLF;

  return true;
}

boolean initWiFi()
{
  /* Initialise the module */
  Debug << "Initializing..." << CRLF;
  if ( !cc3000.begin() )
  {
    Debug << "Couldn't begin()! Check your wiring?";
    while(1);
  }
  
  //listSSIDResults();

  const char *ssid = "GENA-HOME";
  const char *pass = "microlab-2010-user";

  // TODO read all cached Wi-Fi APs and search any of them
  return connectToWiFi(ssid, pass, WLAN_SEC_WPA2, 3);
}


void loop() {

  String data;
  String input;

  if (cc3000WSClient.connected()) {
    data = websocket.getData();
    if (data.length() > 0) {
      Debug << "Received data: " << data;
    }
    
    if ( Serial.available() > 0 ) {
      input = "";
      while (Serial.available() > 0) {
        input += (char) Serial.read();
      }

      // Serial.println(F("")); 
      Debug << input;
      websocket.sendData(input);
    }
  } else {
    Debug << "Waiting for connection..." << CRLF;
  }

  delay(500);
}



/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Debug << "Unable to retrieve the IP Address!\r\n";
    return false;
  }
  else
  {
    Debug << "\nIP Addr: "; cc3000.printIPdotsRev(ipAddress);
    Debug << "\nNetmask: "; cc3000.printIPdotsRev(netmask);
    Debug << "\nGateway: "; cc3000.printIPdotsRev(gateway);
    Debug << "\nDHCPsrv: "; cc3000.printIPdotsRev(dhcpserv);
    Debug << "\nDNSserv: "; cc3000.printIPdotsRev(dnsserv);
    Debug << CRLF;
    return true;
  }
}

/**************************************************************************/
/*!
    @brief  Begins an SSID scan and prints out all the visible networks
*/
/**************************************************************************/

void listSSIDResults(void)
{
  uint32_t index;
//  uint8_t valid, rssi, sec;
  uint8_t rssi, sec;
  char ssidname[33]; 

  if (!cc3000.startSSIDscan(&index)) {
    Serial.println(F("SSID scan failed!"));
    return;
  }

  Serial.print(F("Networks found: ")); Serial.println(index);
  Serial.println(F("================================================"));

  while (index) {
    index--;

    // valid = cc3000.getNextSSID(&rssi, &sec, ssidname);
    cc3000.getNextSSID(&rssi, &sec, ssidname);
    
    Serial.print(F("SSID Name    : ")); Serial.print(ssidname);
    Serial.println();
    Serial.print(F("RSSI         : "));
    Serial.println(rssi);
    Serial.print(F("Security Mode: "));
    Serial.println(sec);
    Serial.println();
  }
  Serial.println(F("================================================"));

  cc3000.stopSSIDscan();
}

