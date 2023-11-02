#include <Servo.h>;

//int targetSensor[3] = []
byte segValue[10][7] = { //세그먼트 숫자
   {1,1,1,1,1,1,0}, //0
   {0,1,1,0,0,0,0}, //1
   {1,1,0,1,1,0,1}, //2
   {1,1,1,1,0,0,1}, //3
   {0,1,1,0,0,1,1}, //4
   {1,0,1,1,0,1,1}, //5
   {1,0,1,1,1,1,1}, //6
   {1,1,1,0,0,0,0}, //7
   {1,1,1,1,1,1,1}, //8
   {1,1,1,1,0,1,1}  //9  
};

byte segPin[8]={2,3,4,5,6,7,8}; //사용핀{a,b,c,d,e,f,g} 순서대로임
byte digitPin[2] = {A1,A2}; //segment 위치 핀

int d1 = 0; //1의 자리
int d2 = 0; //10의 자리

void segOutput(int d, int Number){ 
  segClear(); //세그먼트 초기화
  digitalWrite(digitPin[d], HIGH);  //전류O
  for(int i=0;i<7;i++){
     digitalWrite(segPin[i], segValue[Number][i]); //세그먼트에 표시        
  }
  delayMicroseconds(10000); //기다리기
  digitalWrite(digitPin[d], LOW); //전류X
}

void segClear(){
  for(int i=0;i<8;i++){
    digitalWrite(segPin[i], LOW); //세그먼트 지우기        
  }
}

Servo servo;
int servoPos = 0;
int score = 0; //점수
bool check1,check2 = false; //과녁 상태(쓰러짐=1, 쓰러지지 않음=0)
bool reloading = false;


void setup() {
  Serial.begin(9600);
  servo.attach(9);
  for(servoPos; servoPos > 0;) {
    servoPos-= 2;
    servo.write(servoPos);
    delay(50);
  }
  for(int i=0;i<9;i++){
    pinMode(segPin[i], OUTPUT); //digital 2~8번핀 세그먼트
  }
  pinMode(digitPin[0], OUTPUT); //A0 세그먼트
  pinMode(digitPin[1], OUTPUT); //A1 세그먼트
  digitalWrite(digitPin[0], LOW); //전류X
  digitalWrite(digitPin[1], LOW); //전류O
}
unsigned long lastExecutionTime = 0;  // 마지막 작업 실행 시간을 저장할 변수
unsigned long interval = 50;        // 작업을 수행할 간격 (50ms)

void loop() {
  Serial.println(analogRead(A3));
  Serial.println(check1);
  unsigned long currentTime = millis();
  if (reloading && currentTime - lastExecutionTime >= interval) {
    if(servoPos < 180) {
      servoPos+=5;
      servo.write(servoPos);
    } else {
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      check1 = false;
      check2 = false;
      reloading = false;
    }
    lastExecutionTime = currentTime; 
  }
  if(analogRead(A3) > 1000 && !check1) { //과녁1 쓰러짐
    score+=5; //점수+5
    check1=true; //쓰러짐 체크
    digitalWrite(10,LOW); //LED1 끄기
  }
  if(analogRead(A4) > 1000 && !check2) { //과녁2 쓰러짐
    score+=5; //점수+5
    check2=true; //쓰러짐 체크
    digitalWrite(11,LOW); //LED2 끄기
  }
  d1=score%10;//1의 자리 변수
  d2=(score-score%10)/10;//10의 자리 변수
  segOutput(1,d1); //1의 자리 세그먼트에 표시
  segOutput(0,d2); //10의 자리 세그먼트에 표시
  if(check1&&check2&&!reloading) {
    reloading = true;
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }
}
