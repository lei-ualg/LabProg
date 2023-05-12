final int BUBBLE_DIAMETER = 32;
final int WALL = 10;
final int FRAMERATE = 60;
final color[] COLORS = {color(255, 50, 50), color(240, 230, 50), color(30, 30, 240), color(60, 230, 60), color(140, 60, 255), color(255, 140, 50)};

Field field;

boolean GAME_OVER = false;

void settings() {
  size((BUBBLE_DIAMETER*10) + (WALL*2), (BUBBLE_DIAMETER*16)+(WALL*8));
  pixelDensity(displayDensity());
}

void setup() {
  frameRate(FRAMERATE);
  colorMode(HSB, 360, 100, 100);
  field = new Field();
}

void keyPressed() {
  if (field != null)
    field.keyPressed();
  if (GAME_OVER && key == 'r') {
    field = new Field();
    GAME_OVER = false;
  }
  if (keyCode== DOWN) {
    if (field != null)
      field.ceiling.add_step();
  }
}

void keyReleased() {
  if (field != null)
    field.keyReleased();
}


void draw() {
  background(color(190, 50, 50));
  noStroke();
  //for (int j=0; j<15; j++)
  //  for (int i = 0; i<10; i++)
  //  {
  //    rectMode(CORNER);
  //    color bg = (i%2)==j%2 ?color(180, 90, 40):color(180, 90, 30);
  //    fill(bg);
  //    rect(WALL+(BUBBLE_DIAMETER*i), WALL+(BUBBLE_DIAMETER*j), BUBBLE_DIAMETER, BUBBLE_DIAMETER);
  //  }
  fill(color(40, 90, 70));
  rectMode(CENTER);
  rect(WALL/2, height/2, WALL, height);
  rect(width-(WALL/2), height/2, WALL, height);

  if (!GAME_OVER) {
    field.draw();
    fill(255);
    text(frameRate, WALL, WALL);
  } else {
    field=null;
    push();
    textSize(width/5);
    textAlign(CENTER, CENTER);
    text("GAME OVER", width/2, height/2);
    fill(0, 0, 100);
    textSize(width/10);
    text("R to restart", width/2, height/1.5);
    pop();
  }
}
