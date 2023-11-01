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
int check1,check2 = 0; //과녁 상태(쓰러짐=1, 쓰러지지 않음=0)

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  for(int i=0;i<9;i++){
    pinMode(segPin[i], OUTPUT); //digital 2~8번핀 세그먼트
  }
  pinMode(digitPin[0], OUTPUT); //A0 세그먼트
  pinMode(digitPin[1], OUTPUT); //A1 세그먼트
  digitalWrite(digitPin[0], LOW); //전류X
  digitalWrite(digitPin[1], LOW); //전류O
}
void loop() {
  if(analogRead(A3) > 1000) { //과녁1 쓰러짐
    score+=5; //점수+5
    check1=1; //쓰러짐 체크
    digitalWrite(10,HIGH); //LED1 켜기
  }
  if(analogRead(A4) > 1000) { //과녁2 쓰러짐
    score+=5; //점수+5
    check2=1; //쓰러짐 체크
    digitalWrite(11,HIGH); //LED2 켜기
  }
  d1=score%10;//1의 자리 변수
  d2=(score-score%10)/10;//10의 자리 변수
  segOutput(1,d1,1); //1의 자리 세그먼트에 표시
  segOutput(0,d2,1); //10의 자리 세그먼트에 표시
  if(check1==check2==1)
  {
    reloadTarget();//과녁 되돌리기
  }
}
void reloadTarget() {
  servoPos = 180;
  servo.write(180);//서보모터 돌리기
  digitalWrite(10,LOW);//LED1 끄기
  digitalWrite(11,LOW);//LED2 끄기
  }
