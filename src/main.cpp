#include "actionneur.h"


//initialisation du moteur gauche

byte a=0,etat=0,com=0,fair;
long time2=0;

AccelStepper motor_G(1, step_G, dir_G);//declaration du moteur gauche
AccelStepper motor_D(1, step_D, dir_D);//declatation du moteur droit

Servo servo_d;
Servo servo_g;



void setup() {

  Wire.begin(my_adr);
  Wire.onReceive(receiveEvent);//donne la fonction a ouvrire l'or de la réception de dune trasmition
  Wire.onRequest(requestEvent);
  // put your setup code here, to run once:
  pinMode(reset_G, OUTPUT);    //le reset se fait à l'état bas
  digitalWrite(reset_G, HIGH);
  pinMode(sleep_G, OUTPUT);    //le sleep se met à l'état bas pour une carte fonctionelle
  digitalWrite(sleep_G, HIGH);

  motor_G.setSpeed(speed);
  motor_G.setAcceleration(acceleration_rg);

  //initialisation du moteur droit
  pinMode(reset_D, OUTPUT);    //le reset se fait à l'état bas
  digitalWrite(reset_D, HIGH);
  pinMode(sleep_D, OUTPUT);    //le sleep se met à l'état bas pour une carte fonctionelle
  digitalWrite(sleep_D, HIGH);

  motor_D.setSpeed(speed);
  motor_D.setAcceleration(acceleration_rd);


  MsTimer2::set(1000,IntrerrupTimer);//tout les  seconde
  MsTimer2::start();

  servo_d.attach(22);
  servo_g.attach(23);
//-----------------------------------------------------------------------------------------------------//
  servo_d.write((int)50*0.7555555);//changer pour la mise a zero
  //servo_g.write(0);
  time2=0;
  while(time2!=2){
    Serial.println(time2);
  }
  servo_g.write((int)(180-90)*0.75555555555);
//-------------------------------------------------------------------------------------------------------//

//  delay(3000);
//  servo_g.write((int)((180-90)*0.755555555));//180°à0° ecrire 136à6
//  delay(95);
//  servo_d.write((int)(90*0.755555555));//0°à180° ecrire 0à136
etat =1;
}

void loop() {
  /*  if(b>10)MsTimer2::stop();
    if((int)(((float)b)/200)%2!=0){
      digitalWrite(Led,HIGH);
    }
    else digitalWrite(Led,LOW);*/
  switch(etat){
    case 1:    //attante de trame
      if(com==1){
        etat=fair;
        time2=0;
      }
    break;
    case 2://ouveture eguille
    //--------------------------------------------------------------------------------------------------//
      //angle d'eguille ouver
        servo_g.write((int)((180-90)*0.755555555));
      if(time2==1){
        servo_d.write((int)((90)*0.75555555));
        etat=1;
        com=0;
      }
    //---------------------------------------------------------------------------------------------------//
    break;


    case 3://fermeture eguille
      servo_d.write(0);
      if(time2==1){
        servo_g.write(90*0.755555555);
        etat=1;
        com=0;
      }
    break;
    case 4:
    break;
    case 5:
    break;
    case 6:
    break;
    case 7:
    break;
    case 8:
    break;
    case 9:
    break;
    case 10:
    break;
    case 11:
    break;
    case 12:
    break;

  }
}
void receiveEvent(int howMany){//fonction d'intérupetion l'or dun envoi du maitre
  byte i;//variable pour le for
  fair=Wire.read();//rampli le tableau si avec les valeur de la transmition
  com=1;// passe la comme a 1 pour l'éxecution de la trame en cour
}
void requestEvent(){//fonciton d'intérupetion l'or d une deamande de trame
  Wire.write(com);//le maitre lira la valeur de com
}
void IntrerrupTimer (){
  time2++;
  //Serial.println("reuasie2");
}
