final color TRAFFICLIGHT_COLOR = #333333;
final color ROAD_COLOR = #222222;
final color GREEN_LIGHT = #33ff33;
final color YELLOW_LIGHT = #ffff33;
final color RED_LIGHT = #ff3333;
final color LIGHT_OFF = #444444;

final int FRAMERATE = 60;

final int GREENDURATION = 3;

int CENTER_X, CENTER_Y, TL_W, TL_H;

RoadIntersection ri;

void settings() {
  size(displayWidth/2, displayHeight);
  pixelDensity(displayDensity());
  noSmooth();
}

void setup() {
  background(#336644);
  strokeWeight(3);
  stroke(#337744);
  for (int i=0;i < (width < height ? height : width);i+=10 ) {
    line(0,i,i,0);
    line(width-i,height,width,height - i);
  }
  noStroke();
  
  frameRate(FRAMERATE);

  CENTER_X = width/2;
  CENTER_Y = height/2;

  TL_W = width/20;
  TL_H = TL_W*2;
  
  ri = new RoadIntersection(5, GREENDURATION);

}
void draw() {
  ri.draw();  
}
