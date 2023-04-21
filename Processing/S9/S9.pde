void settings() {
    size(displayWidth / 2, displayHeight / 2);
    pixelDensity(displayDensity());
}

int CENTER_X;
int CENTER_Y;
int FRAMERATE = 30;
int LANE_WIDTH = 100;

int EXERCISE = 3;

int counter = 0;
float duration = 5;

LightColor verticalLight = LightColor.GREEN;
LightColor horizontalLight = LightColor.RED;

Lane up, down, left, right;
void setup() {
    colorMode(HSB, 360, 100, 100);
    CENTER_X = width / 2;
    CENTER_Y = height / 2;
    background(#335533);
    frameRate(FRAMERATE);
    
    
    up = new Lane(Direction.UP, LANE_WIDTH);
    down = new Lane(Direction.DOWN, LANE_WIDTH);
    left = new Lane(Direction.LEFT, LANE_WIDTH);
    right = new Lane(Direction.RIGHT, LANE_WIDTH);
    
    up.lightColor = verticalLight;
    down.lightColor = verticalLight;
    left.lightColor = horizontalLight;
    right.lightColor = horizontalLight;
}


void nextVertical() {
    verticalLight = verticalLight.next();
    up.lightColor = verticalLight;
    down.lightColor = verticalLight;
}

void nextHorizontal() {
    horizontalLight = horizontalLight.next();
    left.lightColor = horizontalLight;
    right.lightColor = horizontalLight;
}


void draw() {
    background(#335533);
    if ((counter / 30) >= duration) {
        counter = 0;
        switch(verticalLight) {
            case GREEN:
                duration /= 2;
                nextVertical();
                break;
            case YELLOW:
                duration *= 2;
                nextVertical();
                nextHorizontal();
                break;
            default:
                counter = 0;
                switch(horizontalLight) {
                    case GREEN:
                        duration /= 2;
                        nextHorizontal();
                        break;
                    case YELLOW:
                        duration *= 2;
                        nextHorizontal();
                        nextVertical();
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    
    counter++;
    
    if (EXERCISE == 1) {
        fill(60);
        rect(0, CENTER_Y - (LANE_WIDTH / 2), width, LANE_WIDTH);
        right.draw();
    } else if (EXERCISE == 2) {
        fill(60);
        rect(0, CENTER_Y - (LANE_WIDTH / 2), width, LANE_WIDTH);
        rect(CENTER_X - (LANE_WIDTH / 2), 0, LANE_WIDTH, height);
        right.draw();
        up.draw();
    } else if (EXERCISE == 3) {
        fill(60);
        rect(0, CENTER_Y - (LANE_WIDTH / 2), width, LANE_WIDTH);
        rect(CENTER_X - (LANE_WIDTH / 2), 0, LANE_WIDTH, height);
        up.draw();
        down.draw();
        left.draw();
        right.draw();
    }
}
