#define Pin12  12
#define Pin13  13
char character;
String Care;
int month;
int monthToday;
int monthSchedule;
bool schedule;
bool today;
int startDay;
int scheduleDay;
unsigned long timer;

void setup() { 
  Serial.begin(9600);
  pinMode(Pin12, OUTPUT); 
  pinMode(Pin13, OUTPUT);
  schedule = false;
  timer = 0;
  today = false;
}

void loop() { 
  if(Serial.available()) {
     Care = Serial.readString();
     Serial.println(Care);
     if (Care.indexOf("Schedule")>= 0) {
        schedule = true;
        Serial.println(schedule);
     }
     if (Care.indexOf("Today")>= 0) {
        today = true;
        Serial.println(today);
     }
     if (Care.indexOf("December")>= 0){
        month = 12;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("December")+9),(Care.indexOf("December")+11)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("December")+9),(Care.indexOf("December")+11)).toInt(); 
        }
     }
     if (Care.indexOf("November")>= 0){
        month = 11;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("November")+9),(Care.indexOf("November")+11)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("November")+9),(Care.indexOf("November")+11)).toInt(); 
        }
     }
     if (Care.indexOf("October")>= 0){
        month = 10;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("October")+8),(Care.indexOf("October")+10)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("October")+8),(Care.indexOf("October")+10)).toInt(); 
        }
     }
     if (Care.indexOf("September")>= 0){
        month = 9;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("September")+10),(Care.indexOf("September")+12)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("September")+10),(Care.indexOf("September")+12)).toInt(); 
        }
     }
     if (Care.indexOf("August")>= 0){
        month = 8;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("August")+7),(Care.indexOf("August")+9)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("August")+7),(Care.indexOf("August")+9)).toInt(); 
        }
     }
     if (Care.indexOf("July")>= 0){
        month = 7;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("July")+5),(Care.indexOf("July")+7)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("July")+5),(Care.indexOf("July")+7)).toInt(); 
        }
     }
     if (Care.indexOf("June")>= 0){
        month = 6;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("June")+5),(Care.indexOf("June")+7)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("June")+5),(Care.indexOf("June")+7)).toInt(); 
        }
     }
     if (Care.indexOf("May")>= 0){
        month = 5;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("May")+4),(Care.indexOf("May")+6)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("May")+4),(Care.indexOf("May")+6)).toInt(); 
        }
     }
     if (Care.indexOf("April")>= 0){
        month = 4;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("April")+6),(Care.indexOf("April")+8)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("April")+6),(Care.indexOf("April")+8)).toInt(); 
        }
     }
     if (Care.indexOf("March")>= 0){
        month = 3;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("March")+6),(Care.indexOf("March")+8)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("March")+6),(Care.indexOf("March")+8)).toInt(); 
        }
     }
     if (Care.indexOf("February")>= 0){
        month = 2;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("February")+9),(Care.indexOf("February")+11)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("February")+9),(Care.indexOf("February")+11)).toInt(); 
        }
     }
     if (Care.indexOf("January")>= 0){
        month = 1;
        if (today) {
          monthToday = month;
          startDay = Care.substring((Care.indexOf("January")+8),(Care.indexOf("January")+10)).toInt();
        }
        if (schedule){
          monthSchedule = month;
          scheduleDay = Care.substring((Care.indexOf("January")+8),(Care.indexOf("January")+10)).toInt(); 
        }
     }
     if (monthToday == monthSchedule){
        if(startDay == scheduleDay){
          if(Care.substring((Care.indexOf("RN")+3),(Care.indexOf("Time"))).toInt() < Care.substring((Care.indexOf("Time")+5),(Care.indexOf("Timer"))).toInt()){
              timer = Care.substring((Care.indexOf("RN")+3),(Care.indexOf("Time"))).toInt();
              Serial.println(timer);
          }
        }
     }
  }
  Serial.println("test");
  if(timer < Care.substring((Care.indexOf("Timer")+6)).toInt() + Care.substring((Care.indexOf("Time")+5),(Care.indexOf("Timer"))).toInt()){
     timer = timer + 1000;
     Serial.println(timer);
     if(timer > Care.substring((Care.indexOf("Time")+5),(Care.indexOf("Timer"))).toInt()){
        digitalWrite(Pin13,HIGH);
     }
  }
  if(timer > Care.substring((Care.indexOf("Timer")+6)).toInt() + Care.substring((Care.indexOf("Time")+5),(Care.indexOf("Timer"))).toInt()-1){
     Serial.println("one cycle is done");
     digitalWrite(Pin13,LOW);
  }
//  if (schedule){
//    if (today){
//      timer = timer + 1;
//    }
//    else{
//      timer = 0;
//    }
//  }
//  else{
//    timer = 0;
//  }
//  Serial.println(timer);
  delay(1000);
}
