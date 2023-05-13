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
  if ((GAME_OVER && key == 'r') ||(key == 'R')) {
    field = new Field();
    GAME_OVER = false;
  }
  if (field != null)
    if (key== 'T') {
      field.ceiling.add_step();
    } else if (key== 'Y') {
      GAME_OVER = true;
    }
}

void keyReleased() {
  if (field != null)
    field.keyReleased();
}


void draw() {
  background(190, 70, 60);
  noStroke();
  fill(40, 90, 70);
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
    textSize(width/12);
    text("Press R to restart", width/2, height/1.5);
    pop();
  }
}
