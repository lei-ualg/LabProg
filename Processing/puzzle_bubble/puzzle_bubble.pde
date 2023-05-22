final int BUBBLE_DIAMETER = 32;
final int WALL = BUBBLE_DIAMETER/3;
final int TITLE_BANNER = BUBBLE_DIAMETER*5;
final int FRAMERATE = 60;

Field field;
boolean AIM = false;
boolean GAME_OVER = false;
boolean VICTORY = false;
int LEVEL = 1;
int SCORE = 0;
int HIGH_SCORE = 0;

void settings() {
  size((BUBBLE_DIAMETER*10) + (WALL*2), (BUBBLE_DIAMETER*16)+(WALL*8)+TITLE_BANNER);
  pixelDensity(displayDensity());
}

void setup() {
  frameRate(FRAMERATE);
  colorMode(HSB, 360, 100, 100);
  PFont font;
  font = loadFont("font.vlw");
  textFont(font);

  field = new Field();
}


void keyPressed() {
  if (field != null)
    field.keyPressed();
  if ((GAME_OVER && key == 'r') ||(key == 'R')) {
    field = new Field();
    SCORE = 0;
    VICTORY = false;
    GAME_OVER = false;
  }
  if (field != null)
    if (key== 'T') {
      field.ceiling.add_step();
    } else if (key== 'Y') {
      GAME_OVER = true;
    } else if (key== 'U') {
      AIM = !AIM;
    }
}

void keyReleased() {
  if (field != null)
    field.keyReleased();
}

void draw() {
  if (SCORE > HIGH_SCORE) HIGH_SCORE = SCORE;
  background(190, 70, 60);
  noStroke();

  fill(40, 90, 70);
  rectMode(CENTER);
  rect(WALL/2, height/2, WALL, height);
  rect(width-(WALL/2), height/2, WALL, height);
  fill(300);
  rect(width/2, TITLE_BANNER/2, width, TITLE_BANNER);
  push();
  fill(0);
  textAlign(CENTER, CENTER);
  textSize(BUBBLE_DIAMETER);
  text("BUBBLE\nPUZZLE", width/2, TITLE_BANNER*.4);
  textSize(BUBBLE_DIAMETER/2);
  textAlign(LEFT, CENTER);
  text("Level: " + LEVEL, WALL, TITLE_BANNER*.85);
  textAlign(RIGHT, CENTER);
  text("Score: " + SCORE, width-WALL, TITLE_BANNER*.85);
  pop();
  if (!GAME_OVER) {
    field.draw();
  } else {
    field=null;
    push();
    textAlign(CENTER, CENTER);
    fill(300);
    rect(width/2, height/2, width, BUBBLE_DIAMETER*2);
    textSize(BUBBLE_DIAMETER*.5);
    text("Press R to restart", width/2, height/1.75);
    text("SCORE: "+SCORE, width/2, height/2.5);
    text("HIGH SCORE: "+HIGH_SCORE, width/2, height/3.5);
    fill(0);
    textSize(BUBBLE_DIAMETER);
    if (VICTORY) {
      fill(120, 90, 70);
      text("VICTORY", width/2, height/2);
    } else
      text("GAME OVER", width/2, height/2);
    pop();
  }
}
