#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define LED_COUNT 30   // 네오픽셀 LED 개수
#define RST_PIN   5
#define SS_PIN    10
int Tx =  9;
int Rx =  8;
char input;
  
MFRC522 rc522(SS_PIN, RST_PIN);
SoftwareSerial btSerial(Tx,Rx);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT,7, NEO_GRB + NEO_KHZ800);
int face = 0;

//하트
uint8_t heart[8] = {  0x00,0x0A,0x1F,0x1F,0x0E,0x0E,0x04,0x00};
uint8_t first[8] = {0x1F,0x1F,0x1F,0x00,0x00,0x00,0x1F,0x1F};
uint8_t seconds[8] = {0x10,0x18,0x1C,0x1E,0x1E,0x1C,0x18,0x10};
uint8_t third[8] = {0x1F,0x1F,0x00,0x00,0x00,0x1F,0x1F,0x1F};
uint8_t fourth[8] = {0x10,0x18,0x1C,0x1E,0x1E,0x1C,0x18,0x10}; 

//눈물
uint8_t cry[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
uint8_t half[8] = {0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F};
uint8_t te[8] = {0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00};
uint8_t et[8] = {0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F};
uint8_t ft[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,0x00};

//화남
uint8_t a1[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
uint8_t d1[8] = {0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F};
uint8_t u1[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00};
uint8_t f1[8] = {0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x1F, 0x00};
uint8_t v1[8] = {0x00, 0x1F, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00};
uint8_t c1[8] = {0x00, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00};
uint8_t k1[8] = {0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00};

//평상시
uint8_t two1[8] = {  0x00,  0x00,  0x00,  0x00,  0x07,  0x07,  0x00,  0x00};
uint8_t two2[8] = {  0x03,  0x0F,  0x1C,  0x10,  0x00,  0x00,  0x00,  0x00};
uint8_t two3[8] = {  0x1F,  0x1F,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00};
uint8_t two4[8] = {  0x18,  0x1E,  0x07,  0x01,  0x00,  0x00,  0x00,  0x00};
uint8_t two5[8] = {  0x00,  0x00,  0x00,  0x00,  0x1C,  0x1C,  0x00,  0x00};
uint8_t two6[8] = {  0x1F,  0x1F,  0x1F,  0x1F , 0x1F,  0x1F,  0x1F,  0x1F};
uint8_t two61[8] ={  0x0F,  0x08,  0x08,  0x08,  0x08,  0x08,  0x08,  0x0F};
uint8_t two7[8] = {  0x1F,  0x1F,  0x1F,  0x1F , 0x1F,  0x1F,  0x1F,  0x1F};
uint8_t two71[8] = { 0x1E,  0x02,  0x02,  0x02,  0x02,  0x02,  0x02,  0x1E};

uint8_t rabbit[8] = { 0x00,  0x00,  0x1F,  0x1F,  0x1F,  0x00,  0x00,  0x00};
uint8_t rabbit_l[8] ={ 0x00,   0x00,  0x1F,  0x1F,  0x1F,  0x0C,  0x0C,  0x00};
uint8_t rabbit_r[8] ={  0x00,  0x00,  0x1F,  0x1F,  0x1F,  0x06,  0x06,  0x00};

uint8_t shame[8] = {  0x00,  0x01,  0x02,  0x04,  0x08,  0x10,  0x00,  0x00};

//찡긋
uint8_t a2[8] = {0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   // 위에 두개
uint8_t b2[8] = {0x00, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00}; // 가운데 2개 줄
uint8_t c2[8] = {0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00}; // 위에 3개
uint8_t d2[8] = {0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00}; // 위에 2개 다음 3개 채운거
uint8_t e2[8] = {0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x00}; // 가운데 3개
uint8_t f2[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F}; // 밑에 3개
uint8_t g2[8] = {0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x1F}; // 위에 3개 밑에 3개
uint8_t h2[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F}; // 밑에 2개

// 물음표
uint8_t a3[8]= { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
uint8_t b3[8]= { 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00};
uint8_t c3[8]= { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F};
uint8_t d3[8]= { 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00};
uint8_t e3[8]= { 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x1F};
uint8_t f3[8]= { 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x1C, 0x1F};
uint8_t g3[8]= { 0x1F, 0x1E, 0x1C, 0x18, 0x10, 0x00, 0x00, 0x00};
uint8_t h3[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F};

// 어지러움
uint8_t mg1[8]= { 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00}; // 위에 4개 0
uint8_t mg3[8]= { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}; //다 채워진 2
uint8_t mg4[8]= { 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F}; // 밑에 4개 3
uint8_t mg5[8]= { 0x00, 0x01, 0x03, 0x07, 0x0E, 0x1C, 0x18, 0x10};//입 1  4
uint8_t mg6[8]= { 0x00, 0x10, 0x18, 0x1C, 0x0E, 0x07, 0x03, 0x01}; // 입2  5
uint8_t mg7[8]= { 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x10}; // 볼

//탄산

uint8_t ta[8] = {0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};   // 위에 두개
uint8_t tb[8] = {0x00, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00}; // 가운데 2개 줄
uint8_t tc[8] = {0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00}; // 위에 3개
uint8_t td[8] = {0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00}; // 위에 2개 다음 3개 채운거
uint8_t tz[8] = {0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x00}; // 가운데 3개
uint8_t tf[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F}; // 밑에 3개
uint8_t tg[8] = {0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x1F}; // 위에 3개 밑에 3개
uint8_t th[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F}; // 밑에 2개
uint8_t tm[8]= { 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x10}; // 볼

LiquidCrystal_I2C lcd(0x27,20,4); 

void color_cloud (int x); // 구름색 선언
void color_yellow (int x); // 노란색 선언
void color_blue (int x); // 파랑색 선언
void color_red (int x); // 빨간색 선언
void color_pink (int x); // 핑크색 선언
void color_green (int x); // 초록색 선언

void touch(int x,int y,int z); // 조도센서 함수 선언

void Char_heart(); // 하트 표정 선언
void Char_cry(); // 우는 표정 선언
void Char_angry(); // 화난 표정 선언
void Char_normal(); // 평범 얼굴 선언
void Char_glasses(); // 물음표 얼굴 선언
void Char_frown(); // 찡긋 얼굴 선언
void Char_dizzy(); //어지러운 얼굴 선언
void Char_acid(); // 탄산
void Char_normal_left(); // 눈 왼쪽
void Char_normal_right(); // 눈 오른쪽

void createChar1(); // 하트 createChar
void createChar2(); // 우는 createChar
void createChar3(); // 화난 createChar
void createChar4(); // 평범 createChar
void createChar5(); // 물음표 createChar
void createChar6(); // 찡긋 createChar
void createChar7(); // 어지러움 createChar
void createChar8(); // 탄산 


void colorWipe(uint32_t color, int wait);
void theaterChaseRainbow(int wait); 
int rainbow(int wait); // 레인보우 함수 선언
int N = 0, bt_cnt = 0;

void setup() 
{

lcd.begin(); 
lcd.backlight(); 

strip.setBrightness(100);
strip.begin();
strip.show();
btSerial.begin(9600);
Serial.begin(9600);
SPI.begin();
rc522.PCD_Init();

createChar4();
lcd.clear(); //화면 초기화
  
Char_normal(); // 평상시 얼굴 출력
theaterChaseRainbow(50);
}

void loop() 
{
if(btSerial.available()){
    input = btSerial.read();
    if( input == "1" || input == '1' || input == 1 || input == "2"|| input == '2' || input == 2 )
      { 
  Serial.println(input);
  N++;
  color_cloud(LED_COUNT);
  delay(4000);
  int l0 = analogRead(A0);
  
/* if(N%100==0)
{
 Serial.print("l0 :");
 Serial.println(l0);
 */
 if(l0>450)
 {
  createChar1();
  lcd.clear(); // 화면 초기화
  Char_heart(); // 하트 얼굴
  
  rainbow(50);

  lcd.clear(); // 화면 초기화
  
  createChar5();
  Char_glasses();
  color_cloud(LED_COUNT);
 }
      
  if(input == "2" || input == '2' || input == 2) // 얼굴 인식 했을 때 슬픔이면 눈물 얼굴 및 파란색 빛나기
  {
  Serial.println("a : 2") ;  
  color_green(LED_COUNT); // 구름색
  //uint8_t temp = random(0, );
  lcd.clear(); //화면 초기화
  createChar4();
  Char_normal(); //눈물 얼굴 출력
  delay(1000);
  lcd.scrollDisplayLeft();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);  
  lcd.scrollDisplayLeft();
 
  delay(2000); 
  lcd.clear();
  createChar5();
  Char_glasses();
  color_cloud(LED_COUNT);
  } 

  if(input == "1" || input == '1' || input == 1){ //   인식 했을 때 웃음이면 찡긋 얼굴 및 노란색 빛나기
  Serial.println("a : 1") ;
  color_yellow(LED_COUNT); // 노란색

  createChar6();
  lcd.clear(); //화면 초기화
  
  Char_frown(); // 찡긋 얼굴 출력
  delay(1000);
  lcd.scrollDisplayLeft();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);  
  lcd.scrollDisplayLeft();
 
  delay(2000);
  lcd.clear();
  createChar5();
  Char_glasses();
  color_cloud(LED_COUNT);
  }

  /*if(input == "3" || input == '3' || input == 3) // 얼굴 인식 했을 때 슬픔이면 눈물 얼굴 및 파란색 빛나기
  {
  Serial.println("a : 3") ;  
  color_blue(LED_COUNT); //파란색

  createChar2();
  lcd.clear(); //화면 초기화

  Char_cry(); //눈물 얼굴 출력
  delay(1000);
  lcd.scrollDisplayLeft();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);  
  lcd.scrollDisplayLeft();
 
  delay(4000); 
  lcd.clear(); //화면 초기화
  createChar4();
  Char_normal();
  color_cloud(LED_COUNT);
  } 

  if(input== 3) // 얼굴 인식 했을 때 화남이면 화난 얼굴 및 빨간색 빛나기
  {
  color_red(LED_COUNT); //빨간색

  createChar3();
  lcd.clear(); //화면 초기화
  
  Char_angry(); //화남 얼굴 출력
  delay(1000);
  lcd.scrollDisplayLeft();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);  
  lcd.scrollDisplayLeft();
  delay(2000); 

  lcd.clear(); //화면 초기화
  createChar4();
  Char_normal();
  }

  if(input == 4) //4 입력시 물음표 얼굴 및 초록색
  {
  color_green (LED_COUNT);
  
  createChar5();
  lcd.clear(); //화면 초기화

  Char_glasses(); // 물음표 얼굴 출력
  delay(1000);
  lcd.scrollDisplayLeft();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);
  lcd.scrollDisplayRight();
  delay(1000);  
  lcd.scrollDisplayLeft();
  delay(1000); 

  lcd.clear(); //화면 초기화
  createChar4();
  Char_normal();
  }
*/
}
}
      


if ( ! rc522.PICC_IsNewCardPresent())
  {
     return;
    }
  if( ! rc522.PICC_ReadCardSerial() ) 
    {
      return; 
    }
    
    Serial.print("UID tag :");
    String tag_uid= "";
    for (byte i = 0; i< rc522.uid.size; i++)
    {
        Serial.print(rc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rc522.uid.uidByte[i], HEX);
        tag_uid.concat(String(rc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        tag_uid.concat(String(rc522.uid.uidByte[i], HEX));
     }
     Serial.println();
     tag_uid.toUpperCase();

      if(tag_uid.substring(1) == "D1 57 28 24")
      {
         Serial.println("BEER");
         
         lcd.clear(); //화면 초기화 
         createChar7(); 
         Char_dizzy(); // 어지러움 출력
         theaterChase(strip.Color(102,   51,   0), 50); // 주황색
         
         delay(1000);
         lcd.scrollDisplayLeft();
         delay(1000);
         lcd.scrollDisplayRight();
         delay(1000);
         
         lcd.clear(); //화면 초기화
         
         createChar4();
         Char_normal();
         color_cloud(LED_COUNT);
      }
      else if(tag_uid.substring(1) == "3C 11 C9 38")
      {
         Serial.println("COLA");
         createChar8();
         lcd.clear(); //화면 초기화
  
         Char_acid(); // 탄산 얼굴 출력
         theaterChase(strip.Color(102,   0,   102), 50); // 보라색
         
         delay(1000);
         lcd.scrollDisplayLeft();
         delay(1000);
         lcd.scrollDisplayRight();
         delay(1000);
         
         lcd.clear();
         createChar4();
         Char_normal();
         color_cloud(LED_COUNT);
      }
      else if(tag_uid.substring(1) == "5C D6 DD 37")
      {
         Serial.println("CIDER");
         createChar3(); 
         lcd.clear(); //화면 초기화
  
         Char_angry(); // 탄산 얼굴 출력
         theaterChase(strip.Color(255,   255,   255), 50); // 흰색
         
         delay(1000);
         lcd.scrollDisplayLeft();
         delay(1000);
         lcd.scrollDisplayRight();
         delay(1000);
         
         lcd.clear();
         
         createChar5();
         Char_glasses();
         color_cloud(LED_COUNT);         
      }    

      else if (tag_uid.substring(1) == "AA A3 1A B1")//화남
      {
              Serial.println("angry");
              createChar3(); 
              lcd.clear(); //화면 초기화
   
         Char_angry(); // 탄산 얼굴 출력
         theaterChase(strip.Color(255,   0,   0), 50); // 빨간색

          delay(1000);
         lcd.scrollDisplayLeft();
         delay(1000);
         lcd.scrollDisplayRight();
         delay(1000);
         
         lcd.clear();
         
         createChar5();
         Char_glasses();
         color_cloud(LED_COUNT);     
       }
            else if (tag_uid.substring(1) == "9C 0E C5 38")//슬픔
      {
              Serial.println("sad");
              createChar2(); 
              lcd.clear(); //화면 초기화
   
         Char_cry(); // 탄산 얼굴 출력
         theaterChase(strip.Color(0,   0,   255), 50); // 파란색

          delay(1000);
         lcd.scrollDisplayLeft();
         delay(1000);
         lcd.scrollDisplayRight();
         delay(1000);
         
         lcd.clear();
         
         createChar5();
         Char_glasses();
         color_cloud(LED_COUNT);     
       }
      else 
       {
         Serial.println("This card is not registered");
        } 
        delay(1000);

}
void Char_heart() //하트
{
  // 0층
  lcd.setCursor(3,0);
  lcd.write(0);
  lcd.setCursor(5,0);
  lcd.write(0);

  lcd.setCursor(14,0);
  lcd.write(0);
  lcd.setCursor(16,0);
  lcd.write(0);

  // 1층
  lcd.setCursor(2,1);
  lcd.write(0);
  lcd.setCursor(3,1);
  lcd.write(0);
  lcd.setCursor(4,1);
  lcd.write(0);
  lcd.setCursor(5,1);
  lcd.write(0);
  lcd.setCursor(6,1);
  lcd.write(0);

  lcd.setCursor(13,1);
  lcd.write(0);
  lcd.setCursor(14,1);
  lcd.write(0);
  lcd.setCursor(15,1);
  lcd.write(0);
  lcd.setCursor(16,1);
  lcd.write(0);
  lcd.setCursor(17,1);
  lcd.write(0);

  // 2층
  lcd.setCursor(3,2);
  lcd.write(0);
  lcd.setCursor(4,2);
  lcd.write(0);
  lcd.setCursor(5,2);
  lcd.write(0);

  lcd.setCursor(9,2);
  lcd.write(1);
  lcd.setCursor(10,2);
  lcd.write(2);

  lcd.setCursor(14,2);
  lcd.write(0);
  lcd.setCursor(15,2);
  lcd.write(0);
  lcd.setCursor(16,2);
  lcd.write(0);

  // 3층
  lcd.setCursor(4,3);
  lcd.write(0);

  lcd.setCursor(9,3);
  lcd.write(3);
  lcd.setCursor(10,3);
  lcd.write(4);

  lcd.setCursor(15,3);
  lcd.write(0);
}

void Char_cry() //슬픔
{
  // 0층
  lcd.setCursor(2,0);
  lcd.write(3);
  lcd.setCursor(3,0);
  lcd.write(3); 
  lcd.setCursor(4,0);
  lcd.write(3);
  lcd.setCursor(5,0);
  lcd.write(3);
  lcd.setCursor(6,0);
  lcd.write(3); 

  lcd.setCursor(13,0);
  lcd.write(3); 
  lcd.setCursor(14,0);
  lcd.write(3);
  lcd.setCursor(15,0);
  lcd.write(3);
  lcd.setCursor(16,0);
  lcd.write(3); 
  lcd.setCursor(17,0);
  lcd.write(3);

  // 1층
  lcd.setCursor(3,1);
  lcd.write(0); 
  lcd.setCursor(5,1);
  lcd.write(0);  
   
  lcd.setCursor(14,1);
  lcd.write(0);
  lcd.setCursor(16,1);
  lcd.write(0);
  
  // 2층
  
  lcd.setCursor(3,2);
  lcd.write(2);
  lcd.setCursor(5,2);
  lcd.write(2);
  lcd.setCursor(9,2);
  lcd.write(3);
  lcd.setCursor(10,2);
  lcd.write(3);
  
  lcd.setCursor(14,2);
  lcd.write(2);
  lcd.setCursor(16,2);
  lcd.write(2);

  // 3층
  lcd.setCursor(7,3);
  lcd.write(1);
  lcd.setCursor(8,3);
  lcd.write(4);
  lcd.setCursor(11,3);
  lcd.write(4);
  lcd.setCursor(12,3);
  lcd.write(1);
}

void Char_angry() //화남
{
  // 0층
  lcd.setCursor(4,0);  //출력할 위치
  lcd.write(2); 
  lcd.setCursor(5,0);
  lcd.write(1);
  lcd.setCursor(14,0);
  lcd.write(1);
  lcd.setCursor(15,0);
  lcd.write(2);
  lcd.setCursor(17,0);
  lcd.write(3);
  lcd.setCursor(18,0);
  lcd.write(6);

  // 1층
  lcd.setCursor(6,1);
  lcd.write(2);
  lcd.setCursor(7,1);
  lcd.write(1);

  lcd.setCursor(12,1);
  lcd.write(1);
  lcd.setCursor(13,1);
  lcd.write(2); 
  lcd.setCursor(17,1);
  lcd.write(4);
  lcd.setCursor(18,1);
  lcd.write(5);  

  // 2층
  lcd.setCursor(5,2);
  lcd.write(0);
  lcd.setCursor(9,2);
  lcd.write(1);
  lcd.setCursor(10,2);
  lcd.write(1);
  lcd.setCursor(14,2);
  lcd.write(0);

  // 3층
  lcd.setCursor(7,3);
  lcd.write(1);
  lcd.setCursor(8,3);
  lcd.write(2); 
  lcd.setCursor(9,3);
  lcd.write(1);
  lcd.setCursor(10,3);
  lcd.write(1);
  lcd.setCursor(11,3);
  lcd.write(2); 
  lcd.setCursor(12,3);
  lcd.write(1); 
}

void Char_normal() //평상시
{
  // 0층
  lcd.setCursor(3,0);
  lcd.write(2);
  lcd.setCursor(4,0);
  lcd.write(3);
  lcd.setCursor(5,0);
  lcd.write(4); 

  lcd.setCursor(14,0);
  lcd.write(2);
  lcd.setCursor(15,0);
  lcd.write(3);
  lcd.setCursor(16,0);
  lcd.write(4); 

  // 1층
  lcd.setCursor(4,1);
  lcd.write(5);

  lcd.setCursor(15,1);
  lcd.write(6);

  // 2층

  lcd.setCursor(1,2);
  lcd.write(10);
  lcd.setCursor(2,2);
  lcd.write(10);
  lcd.setCursor(3,2);
  lcd.write(10);
      
  lcd.setCursor(8,2);
  lcd.write(7);
  lcd.setCursor(9,2);
  lcd.write(8);
  lcd.setCursor(10,2);
  lcd.write(9);
  lcd.setCursor(11,2);
  lcd.write(7);

  lcd.setCursor(16,2);
  lcd.write(10);
  lcd.setCursor(17,2);
  lcd.write(10);
  lcd.setCursor(18,2);
  lcd.write(10);

}

void Char_frown() //찡긋
{
  // 0층
  lcd.setCursor(2,0);  
  lcd.write(0); 
  lcd.setCursor(3,0);
  lcd.write(3);
  lcd.setCursor(4,0);
  lcd.write(5);

  lcd.setCursor(15,0);
  lcd.write(5); 
  lcd.setCursor(16,0);
  lcd.write(3); 
  lcd.setCursor(17,0);
  lcd.write(0);

  // 1층
  lcd.setCursor(5,1);
  lcd.write(6);
  lcd.setCursor(6,1);
  lcd.write(1); 
  lcd.setCursor(13,1);
  lcd.write(1);
  lcd.setCursor(14,1);
  lcd.write(6);

  // 2층
  lcd.setCursor(2,2);
  lcd.write(7);
  lcd.setCursor(3,2);
  lcd.write(4);
  lcd.setCursor(4,2);
  lcd.write(2);

  lcd.setCursor(15,2);
  lcd.write(2); 
  lcd.setCursor(16,2);
  lcd.write(4);
  lcd.setCursor(17,2);
  lcd.write(7);

  // 3층
  lcd.setCursor(7,3);
  lcd.write(1);
  lcd.setCursor(8,3);
  lcd.write(1);
  lcd.setCursor(9,3);
  lcd.write(1);
  lcd.setCursor(10,3);
  lcd.write(1);
  lcd.setCursor(11,3);
  lcd.write(1);
  lcd.setCursor(12,3);
  lcd.write(1);
}

void Char_glasses()
{
  // 0층
  lcd.setCursor(3,0);  
  lcd.write(4); 
  lcd.setCursor(4,0);
  lcd.write(2);
  lcd.setCursor(5,0); 
  lcd.write(5); 
  lcd.setCursor(14,0);
  lcd.write(4);
  lcd.setCursor(15,0); 
  lcd.write(2); 
  lcd.setCursor(16,0);
  lcd.write(5);

  // 1층
  lcd.setCursor(3,1);
  lcd.write(1);
  lcd.setCursor(5,1);
  lcd.write(0);
  lcd.setCursor(14,1);
  lcd.write(1); 
  lcd.setCursor(16,1);
  lcd.write(0); 
  
  // 2층
  lcd.setCursor(4,2);
  lcd.write(0); 
  lcd.setCursor(5,2);  
  lcd.write(6); 
  
  lcd.setCursor(15,2);
  lcd.write(0);
  lcd.setCursor(16,2);
  lcd.write(6); 

  lcd.setCursor(4,3);
  lcd.write(3);

  lcd.setCursor(8,3);
  lcd.write(7);
  lcd.setCursor(9,3);
  lcd.write(7);
  lcd.setCursor(10,3);
  lcd.write(7);
  lcd.setCursor(11,3);
  lcd.write(7);
  
  lcd.setCursor(15,3);
  lcd.write(3); 
}

void Char_dizzy() // 어지러움
{
  lcd.createChar(0, mg1);
  lcd.createChar(2, mg3);
  lcd.createChar(3, mg4);
  lcd.createChar(4, mg5);
  lcd.createChar(5, mg6);
  lcd.clear(); //화면 초기화 

  lcd.setCursor(2,0);
  lcd.write(2);
  lcd.setCursor(3,0);
  lcd.write(0);
  lcd.setCursor(4,0);
  lcd.write(0);
  lcd.setCursor(5,0);
  lcd.write(0);
  lcd.setCursor(6,0);
  lcd.write(0);

  //0층
  lcd.setCursor(13,0);
  lcd.write(2);
  lcd.setCursor(14,0);
  lcd.write(0);
  lcd.setCursor(15,0);
  lcd.write(0);
  lcd.setCursor(16,0);
  lcd.write(0);
  lcd.setCursor(17,0);
  lcd.write(0);

  //1층
  lcd.setCursor(2,1);
  lcd.write(2);
  lcd.setCursor(4,1);
  lcd.write(2);
  lcd.setCursor(5,1);
  lcd.write(0);
  lcd.setCursor(6,1);
  lcd.write(2);
  lcd.setCursor(13,1);
  lcd.write(2);
  lcd.setCursor(15,1);
  lcd.write(2);
  lcd.setCursor(16,1);
  lcd.write(0);
  lcd.setCursor(17,1);
  lcd.write(2);
  //2층
  lcd.setCursor(2,2);
  lcd.write(2);
  lcd.setCursor(3,2);
  lcd.write(3);
  lcd.setCursor(4,2);
  lcd.write(3);
  lcd.setCursor(5,2);
  lcd.write(3);
  lcd.setCursor(6,2);
  lcd.write(2);
  lcd.setCursor(13,2);
  lcd.write(2);
  lcd.setCursor(14,2);
  lcd.write(3);
  lcd.setCursor(15,2);
  lcd.write(3);
  lcd.setCursor(16,2);
  lcd.write(3);
  lcd.setCursor(17,2);
  lcd.write(2);
  //3층

  lcd.setCursor(0,3);
  lcd.write(6);
  lcd.setCursor(1,3);
  lcd.write(6);
  lcd.setCursor(2,3);
  lcd.write(6);
  lcd.setCursor(17,3);
  lcd.write(6);
  lcd.setCursor(18,3);
  lcd.write(6);
  lcd.setCursor(19,3);
  lcd.write(6);
  
  lcd.setCursor(8,3);
  lcd.write(4);
  lcd.setCursor(9,3);
  lcd.write(5);
  lcd.setCursor(10,3);
  lcd.write(4);
  lcd.setCursor(11,3);
  lcd.write(5);
  lcd.setCursor(12,3);
  lcd.write(4);
}

void Char_acid() 
{
  // 0층
  lcd.setCursor(2,0);  //출력할 위치
  lcd.write(3); 
  lcd.setCursor(3,0);
  lcd.write(3);
  lcd.setCursor(4,0);
  lcd.write(5);

  lcd.setCursor(15,0);
  lcd.write(5); 
  lcd.setCursor(16,0);
  lcd.write(3); 
  lcd.setCursor(17,0);
  lcd.write(3);

  // 1층
  lcd.setCursor(5,1);
  lcd.write(6);
  lcd.setCursor(6,1);
  lcd.write(1); 
  lcd.setCursor(13,1);
  lcd.write(1);
  lcd.setCursor(14,1);
  lcd.write(6);

  // 2층
  lcd.setCursor(2,2);
  lcd.write(7);
  lcd.setCursor(3,2);
  lcd.write(4);
  lcd.setCursor(4,2);
  lcd.write(2);

  lcd.setCursor(15,2);
  lcd.write(2); 
  lcd.setCursor(16,2);
  lcd.write(4);
  lcd.setCursor(17,2);
  lcd.write(7);

  // 3층
  lcd.setCursor(7,3);
  lcd.write(1);
  lcd.setCursor(8,3);
  lcd.write(1);
  lcd.setCursor(9,3);
  lcd.write(1);
  lcd.setCursor(10,3);
  lcd.write(1);
  lcd.setCursor(11,3);
  lcd.write(1);
  lcd.setCursor(12,3);
  lcd.write(1);


  lcd.setCursor(0,3);
  lcd.write(8);
  lcd.setCursor(1,3);
  lcd.write(8);
  lcd.setCursor(2,3);
  lcd.write(8);
  lcd.setCursor(17,3);
  lcd.write(8);
  lcd.setCursor(18,3);
  lcd.write(8);
  lcd.setCursor(19,3);
  lcd.write(8);
  }

void Char_normal_left() // 눈 왼쪽
{
    // 0층
  lcd.setCursor(3,0);
  lcd.write(2);
  lcd.setCursor(4,0);
  lcd.write(3);
  lcd.setCursor(5,0);
  lcd.write(4); 

  lcd.setCursor(14,0);
  lcd.write(2);
  lcd.setCursor(15,0);
  lcd.write(3);
  lcd.setCursor(16,0);
  lcd.write(4); 

  // 1층
  lcd.setCursor(2,1);
  lcd.write(5);

  lcd.setCursor(13,1);
  lcd.write(6);

  // 2층 만들어야돼 (입)

  lcd.setCursor(1,2);
  lcd.write(10);
  lcd.setCursor(2,2);
  lcd.write(10);
  lcd.setCursor(3,2);
  lcd.write(10);
      
  lcd.setCursor(8,2);
  lcd.write(7);
  lcd.setCursor(9,2);
  lcd.write(8);
  lcd.setCursor(10,2);
  lcd.write(9);
  lcd.setCursor(11,2);
  lcd.write(7);

  lcd.setCursor(16,2);
  lcd.write(10);
  lcd.setCursor(17,2);
  lcd.write(10);
  lcd.setCursor(18,2);
  lcd.write(10);
  }
void Char_normal_right() // 눈 오른쪽
{
    // 0층
  lcd.setCursor(3,0);
  lcd.write(2);
  lcd.setCursor(4,0);
  lcd.write(3);
  lcd.setCursor(5,0);
  lcd.write(4); 

  lcd.setCursor(14,0);
  lcd.write(2);
  lcd.setCursor(15,0);
  lcd.write(3);
  lcd.setCursor(16,0);
  lcd.write(4); 

  // 1층
  lcd.setCursor(6,1);
  lcd.write(5);

  lcd.setCursor(17,1);
  lcd.write(6);

  // 2층 만들어야돼 (입)

  lcd.setCursor(1,2);
  lcd.write(10);
  lcd.setCursor(2,2);
  lcd.write(10);
  lcd.setCursor(3,2);
  lcd.write(10);
      
  lcd.setCursor(8,2);
  lcd.write(7);
  lcd.setCursor(9,2);
  lcd.write(8);
  lcd.setCursor(10,2);
  lcd.write(9);
  lcd.setCursor(11,2);
  lcd.write(7);

  lcd.setCursor(16,2);
  lcd.write(10);
  lcd.setCursor(17,2);
  lcd.write(10);
  lcd.setCursor(18,2);
  lcd.write(10);
  }

void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) { // Repeat 10 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;
  for (int a = 0; a < 30; a++) { 
    for (int b = 0; b < 3; b++) {
      strip.clear();         
      for (int c = b; c < strip.numPixels(); c += 3) {        
        int hue = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color);
      }
      strip.show();                
      delay(wait);                 
      firstPixelHue += 65536 / 90; 
    }
  }
}

 int rainbow(int wait) 
  { 
  int time = 0;
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) 
  {
    
    for (int i = 0; i < strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());      
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      time++;
      if (time == 5000)
      {
         return 0;
      }
      
    }
    strip.show();
    delay(wait);
  }
  }
    
void color_cloud (int x) // 구름색
{
  for (int i = 0; i < x; i++) 
  {
    strip.setPixelColor(i, 0, 255, 255 , 0); //구름이색(하늘색)
    strip.show();    // 저장
   }
}

void color_yellow (int x) // 노란색
{
  for (int i = 0; i < x; i++) 
  {
    strip.setPixelColor(i, 255, 255, 0 , 0); // 노란색
    strip.show();    // 저장
  }
}

void color_blue (int x) // 파랑색
{
  for (int i = 0; i < x; i++) 
  {
    strip.setPixelColor(i, 0, 0, 255 , 0); // 파랑색
    strip.show();    // 저장
  }
}

void color_red (int x) // 빨간색
{
  for (int i = 0; i < x; i++) 
  {
    strip.setPixelColor(i, 255, 0, 0 , 0); // 빨간색
    strip.show();    // 저장
  }
}

void color_pink (int x)
{
  for (int i = 0; i < x; i++) 
  {
    strip.setPixelColor(i, 255, 0, 255 , 0); // 핑크색
    strip.show();    // 저장
  }
}

void color_green (int x)
{
  for (int i = 0; i < x; i++) 
  {
    strip.setPixelColor(i, 0, 255, 0 , 0); // 연두색
    strip.show();    // 저장
  }
}

void createChar1() // 하트 createChar
{
  lcd.createChar(0, heart);
  lcd.createChar(1, first);
  lcd.createChar(2, seconds);
  lcd.createChar(3, third);
  lcd.createChar(4, fourth);
  } 
void createChar2() // 우는 createChar
{
  lcd.createChar(0, cry);
  lcd.createChar(1, half);
  lcd.createChar(2, te);
  lcd.createChar(3, et);
  lcd.createChar(4, ft);  
  } 
void createChar3() // 화난 createChar
{
  lcd.createChar(0, a1);
  lcd.createChar(1, d1);
  lcd.createChar(2, u1);
  lcd.createChar(3, f1);
  lcd.createChar(4, v1);
  lcd.createChar(5, c1);
  lcd.createChar(6, k1);
  } 
void createChar4() // 평범 createChar
{
  lcd.createChar(0, two1);
  lcd.createChar(1, two2);
  lcd.createChar(2, two3);
  lcd.createChar(3, two4);
  lcd.createChar(4, two5);  
  lcd.createChar(5, two6);  
  lcd.createChar(6, two7); 

  lcd.createChar(7, rabbit);  
  lcd.createChar(8, rabbit_l);  
  lcd.createChar(9, rabbit_r); 

  lcd.createChar(10, shame);
  
  } 
void createChar5() // 물음표 createChar
{
  lcd.createChar(0, a3);
  lcd.createChar(1, b3);
  lcd.createChar(2, c3);
  lcd.createChar(3, d3);
  lcd.createChar(4, e3);
  lcd.createChar(5, f3);
  lcd.createChar(6, g3);
  lcd.createChar(7, h3);
  } 
void createChar6() // 찡긋 createChar
{
  lcd.createChar(0, a2);
  lcd.createChar(1, b2);
  lcd.createChar(2, c2);
  lcd.createChar(3, d2);
  lcd.createChar(4, e2);
  lcd.createChar(5, f2);
  lcd.createChar(6, g2);
  lcd.createChar(7, h2);
  } 
void createChar7() // 어지러움 createChar
{
  lcd.createChar(0, mg1);
  lcd.createChar(2, mg3);
  lcd.createChar(3, mg4);
  lcd.createChar(4, mg5);
  lcd.createChar(5, mg6);
  lcd.createChar(6, mg7);
  } 

void createChar8() // 탄산
{
  lcd.createChar(0, ta);
  lcd.createChar(1, tb);
  lcd.createChar(2, tc);
  lcd.createChar(3, td);
  lcd.createChar(4, tz);
  lcd.createChar(5, tf);
  lcd.createChar(6, tg);
  lcd.createChar(7, th);
  lcd.createChar(8, tm);
  }