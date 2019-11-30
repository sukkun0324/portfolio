#include<stdio.h>
#include<errno.h>
#include<string.h>

#include<wiringPi.h>
#include<softTone.h>

#define PIN 1

int scale=300;

int main(){
int i;
wiringPiSetup();
softToneCreate(PIN);

while(1){
softToneWrite(PIN, 2400);
}
}
