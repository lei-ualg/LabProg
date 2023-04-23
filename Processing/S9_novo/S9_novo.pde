final color TRAFFICLIGHT_COLOR = #333333;
final color ROAD_COLOR = #222222;
final color GREEN_LIGHT = #33ff33;
final color YELLOW_LIGHT = #ffff33;
final color RED_LIGHT = #ff3333;
final color LIGHT_OFF = #444444;

final int FRAMERATE = 60;

final int GREENDURATION = 3;


RoadIntersection ri;

void settings() {
  size(displayWidth/2,displayHeight/2);
  pixelDensity(displayDensity());
  //noSmooth();
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

  
  ri = new RoadIntersection(3, GREENDURATION);
  //surface.setTitle("S9");
  //surface.setResizable(true);
  //surface.setLocation(100, 100);
}
void draw() {
  ri.draw();  
}
