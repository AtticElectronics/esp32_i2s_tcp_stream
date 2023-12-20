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
import socket
import threading

def OnClosedSocket():
    print("닫힘 콜백함수")

def start_server(host, port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)
    print(f"Server is listening on port {port}")
    try:
        while True:
            try:
                client_socket, client_address = server_socket.accept()
                print(f"Connected to {client_address}")
                audio_stream_server = ESP32AudioStreamServer(client_socket, client_address, OnClosedSocket)
                client_thread = threading.Thread(target=audio_stream_server.start)
                client_thread.start()
            except Exception as e:
                print(f"Connection error: {e}")
    finally:
        server_socket.close()
        print("Server closed")


start_server('0.0.0.0', 33823)
```
