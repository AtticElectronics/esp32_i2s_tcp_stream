# TCP서버와 ESP32간의 i2s오디오 전송, 수신

# 현재 클래스별 용도 설명
    1. I2SAudioSender: eps32의 wav프레임을 서버측에 wav파일로저장
    2. I2SAudioReceiver: 서버의 wav파일을 esp32에서 스트리밍 재생
    3. python_server: 수신 데이터를 wav파일로저장, wav파일의 데이터를 전송 

## 현재 제한사항
    비트심도 : 16bit 
    채널 : 1ch

## 로드맵
    I2SAudioSender클래스 로드맵 : 미정
    I2SAudioReceiver클래스 로드맵 : 미정
    
## 예제 
```cpp
#include <WiFi.h>
#include <WiFiClient.h>
#include <I2SAudioReceiver.h>
#include <Button.h>

Button testbutton(9);

WiFiClient client;
I2SAudioReceiver i2sAudioReceiver;

void setup()
{
  WiFi.begin("공유기 이름", "공유기 비밀번호");
  i2sAudioReceiver.setWifiClient(client);
  i2sAudioReceiver.setServerAddr("192.168.0.200", 33819);
  i2sAudioReceiver.i2sBegin();
}

void loop()
{
  int state = testbutton.checkState();
  if (state == BUTTON_PRESSED)
  {
    String gptmsg = i2sAudioReceiver.startSteam();
    int err = i2sAudioReceiver.playStreamData();
  }
}
```

## 서버코드
```python
if __name__ == "__main__":
    # 첫 번째 서버 인스턴스 생성 및 스레드 시작
    server1 = ESPTCPServer('0.0.0.0', 33819, ESPTCPAudioSend)
    server1_thread = threading.Thread(target=server1.start)
    server1_thread.start()

    # 두 번째 서버 인스턴스 생성 및 스레드 시작
    server2 = ESPTCPServer('0.0.0.0', 33823, ESP32TCPAudioRecv)
    server2_thread = threading.Thread(target=server2.start)
    server2_thread.start()
```

## 코드 목적: HTTP프로토콜은 느려서 TCP로 사족을 쳐내고 만들어보자, 일단 자주 쓰일것같아서 초안 느낌만 코드로작성, 시간날때나 재사용시 관련업데이트 예정
