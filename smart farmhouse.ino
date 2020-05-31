const int analogPin = A0;
float gerilimDeger = 0;
float sensorDeger = 0;
float sicaklikDeger = 0;
int buzzer=7;

int trigpin=4;
int echopin=3;
int olcum;
int cm;
int led=13;


int oda1 = 6; //1.oda ışığı 3.dijital pin
int bahce=10;

int ldr=A1;

int depremsensor=A5;
const int buzzerdeprem = 5;



void setup() {

   pinMode(buzzerdeprem,OUTPUT);
  
   pinMode(bahce,OUTPUT);

   pinMode(oda1,OUTPUT); // çıkış ayarlandı

   pinMode(trigpin,OUTPUT);
   pinMode(echopin,INPUT);
   pinMode(led,OUTPUT);

   pinMode(buzzer,OUTPUT); 
  Serial.begin(9600);
       
}
 
void loop() {
 digitalWrite(oda1,HIGH);
 //digitalWrite(bahce,HIGH);
 delay(100); // 100ms bekle
 yangin_sistemi(); // Yangın olup olmadığını kontrol et
 delay(500); // 500ms bekle
 mesafe_sistemi();
 delay(500);
 karanlik_sistem();
 delay(500);
 deprem_sistem();
 delay(500);

 
}

void yangin_sistemi() {
  
  sensorDeger = analogRead(analogPin);
 
 Serial.print("Sensör Değeri:  ");
 Serial.println(sensorDeger);
 
 // A0 pininden okunan değeri mV cinsinden gerilim değerine dönüştürüyoruz.
 gerilimDeger = (sensorDeger/1023)*5000;
 
 Serial.print("Gerilim Değeri: ");
 Serial.println(gerilimDeger);
 
 // Gerilim değerini sıcaklık değerine dönüştürüyoruz.
 sicaklikDeger = gerilimDeger / 10.0;
 
 Serial.print("Sıcaklık Değeri: ");
 Serial.println(sicaklikDeger);
 
 Serial.println("**********************************");
 if(sicaklikDeger <50.0 && sicaklikDeger > 0) {
  digitalWrite(buzzer,HIGH);
  delay(2000);
  digitalWrite(buzzer,LOW);
 }
 delay(1000);
 
}

void mesafe_sistemi() {
  
   digitalWrite(trigpin,LOW);
   delayMicroseconds(10);
   digitalWrite(trigpin,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigpin,LOW);
   olcum=pulseIn(echopin,HIGH);
   cm=olcum/58;

    Serial.print("teras Değeri: ");
 Serial.println(cm);


   if( cm <10 && cm > 0) {

    digitalWrite(led,HIGH);
   }
   else {

    digitalWrite(led,LOW);
   }
   Serial.println(cm);
   delay(500);
   
}

void karanlik_sistem(){
  int deger=analogRead(ldr);
  Serial.println(deger);
  if(deger<1020){
    digitalWrite(bahce,HIGH);
  }else{
    digitalWrite(bahce,LOW);
  }
}

void deprem_sistem() {
  int deprem_deger = analogRead(depremsensor);
   Serial.print("Deprem Sensor Value: ");
    Serial.println(deprem_deger);
  if (deprem_deger >550) {
    tone(buzzerdeprem, 500);
    Serial.print("Sensor Value: ");
    Serial.println(deprem_deger);
  }
  else {
    noTone(buzzerdeprem);
     Serial.print("Sensor Value: ");
    Serial.println(deprem_deger);
  }
  
}
