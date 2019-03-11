#include "actionneur.h"


//initialisation du moteur gauche

byte a=0,etat=0;
int b=0;

AccelStepper motor_G(1, step_G, dir_G);//declaration du moteur gauche
AccelStepper motor_D(1, step_D, dir_D);//declatation du moteur droit

Servo servo_d;
Servo servo_g;

void IntrerrupTimer (){
  b++;
}


void setup() {
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

  pinMode(Led,OUTPUT);

  MsTimer2::set(10,IntrerrupTimer);//tout les centiéme de seconde



  servo_d.attach(22);
//  servo_d.write(0);
//  delay(3000);
  servo_g.attach(23);
//  servo_g.write((int)((180-10)*0.755555555));
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
    break;
    case 2://ouveture eguille
      servo_d.Write(0);
      MsTimer2::start();
    break;
    case 3://fermeture eguille
    break;
    case 4:
    break;
    case 5:
    break;
    case 6:
    break.
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
