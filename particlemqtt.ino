// This #include statement was automatically added by the Particle IDE.
#include "MQTT/MQTT.h"

void callback(char* topic, byte* payload, unsigned int length);

int led0 = D0;

/**
 * if want to use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * want to use domain name,
 * MQTT client("www.sample.com", 1883, callback);
 **/
 
//byte server[] = {176,58,105,156}; 
MQTT client("op-en.se", 1883, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);

    digitalWrite(led0, HIGH);

    if (message.equals("RED"))  {
        RGB.color(255, 0, 0);
    }
    
    if (message.equals("GREEN"))    { 
        RGB.color(0, 255, 0);
    }    
        
    if (message.equals("BLUE"))  {  
        RGB.color(0, 0, 255);
    }
    
    delay(1000);
    digitalWrite(led0, LOW);

}


void setup() {
    
    pinMode(led0, OUTPUT);
    
    RGB.control(true);
    
    // connect to the server
    client.connect("connect");

    // publish/subscribe
    if (client.isConnected()) {
        RGB.color(0, 0, 255);
        client.publish("Datasites/particle","hello nodered!");
        client.subscribe("Datasites/particle");
    } else {
        RGB.color(255, 0, 0);
    }
}

void loop() {
    if (client.isConnected())
        client.loop();
}
