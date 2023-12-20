#include <WiFi.h>
#include <WiFiClient.h>
#include <I2SAudioReceiver.h>
#include <I2SAudioSender.h>
#include <Button.h>

Button testbutton(9);
WiFiClient client;
I2SAudioSender sendVoice;


void setup()
{
    Serial.begin(115200);
    WiFi.begin("YOUR_SSID", "YOUR_PW");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
    }
    sendVoice.setWifiClient(client);
    sendVoice.setServerAddr("192.168.0.200", 33823);
    sendVoice.setI2sBus(1);
    sendVoice.setAudioQulity(16000, 16, 1);
    sendVoice.setI2sPin(8, 19, 20);
    sendVoice.setDmaBuf(1024, 6);
    sendVoice.i2sBegin();

}

void loop()
{
    int state = testbutton.checkState();
    if (state == 1)
    {
        sendVoice.openFile();
    }
    else if (state == 2)
    {
        sendVoice.writeData();
    }
    else if (state == 3)
    {
        sendVoice.closeFile();
    }
}
