# 목적 : TCP 프로토콜로 IS2데이터를 서버로 전송

## TCP통신관련설정 
```cpp
WiFi.begin("YOUR_SSID", "YOUR_PW");
sendVoice.setWifiClient(client);
sendVoice.setServerAddr("192.168.0.200", 33823);
```
## 오디오 관련설정
```cpp
sendVoice.setI2sBus(1);
sendVoice.setAudioQulity(16000, 16, 1);
sendVoice.setI2sPin(8, 19, 20);
sendVoice.setDmaBuf(1024, 6);
sendVoice.i2sBegin();
```
## 
```cpp
sendVoice.openFile();
sendVoice.writeData();
sendVoice.closeFile();
```


## 서버코드 파일저장위치 전송완료 콜백 가능
```python
if __name__ == "__main__":
    server1 = ESPTCPServer('0.0.0.0', 33819, ESPTCPAudioSend)
    server2 = ESPTCPServer('0.0.0.0', 33820, ESP32TCPAudioRecv)
    server1.start()
    server2.start()
start_server('0.0.0.0', 33823)
```
