void settings() {
  size(displayWidth/2, displayHeight/2);
  pixelDensity(displayDensity());
}

float startTime;
float startSec;
void setup() {
  frameRate(30);
  startTime = millis();
  startSec = second();
  int centerX = width/2;
  int centerY = height/2;
  int r = height/4;
  strokeWeight(8);
  stroke(0);
  circle(centerX, centerY, (r)*2);
}
void draw() {
  
  float sec = float(Math.round((((((millis()-startTime)%60_000)/1000)+startSec)%60)*1000))/1000;
    
  colorMode(HSB, 360, 100, 100);
  int r = height/4;
  float rad_s_m = PI/30;
  float rad_h = PI/6;
  int centerX = width/2;
  int centerY = height/2;
  
  strokeWeight(1);
  fill(color(0,0,100));
  stroke(0);
  circle(centerX, centerY, (r)*2);
  
  strokeWeight(2);
  stroke(0);
  for (int s = 0; s <= 60; s++) {
    if (s%5!=0)
      line((centerX)+(sin((s)*rad_s_m))*(r-10), (centerY)-(cos((s)*rad_s_m))*(r-10), (centerX)+(sin((s)*rad_s_m))*(r-5), (centerY)-(cos((s)*rad_s_m))*(r-5));
  }
  
  for (int i = 1; i <=12;i++) {
    fill(0);
    stroke(0);
    textAlign(CENTER, CENTER);
    text(i,(centerX)+(sin((i)*rad_h)*(r-25)), (centerY)-(cos((i)*rad_h)*(r-25)));
    line((centerX)+(sin((i)*rad_h)*(r-15)), (centerY)-(cos((i)*rad_h)*(r-15)),(centerX)+(sin((i)*rad_h)*(r-5)), (centerY)-(cos((i)*rad_h)*(r-5)));
  }
  
  stroke(0);
  strokeWeight(3);
  line(centerX, centerY, (centerX)+(sin(minute()*rad_s_m)*(r/1.7)), (centerY)-(cos(minute()*rad_s_m)*(r/1.75)));
  line(centerX, centerY, (centerX)+(sin((hour()%12)*rad_h)*(r/2)), (centerY)-(cos((hour()%12)*rad_h)*(r/2)));
  
  
  strokeWeight(1);
  stroke(color(0, 100, 100));
  line(centerX, centerY, (centerX)+(sin(sec*rad_s_m)*(r/1.5)), (centerY)-(cos(sec*rad_s_m)*(r/1.5)));
  
  strokeWeight(6);
  point(centerX, centerY);
}
