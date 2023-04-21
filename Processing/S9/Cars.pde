

public class Cars {
    public boolean stopped = false;
    public boolean vertical;
    Direction direction;
    private float speedX = random(3, 6), speedY = random(3, 6);
    private float posX = CENTER_X, posY = CENTER_Y;
    private color paint = color(random(360), random(100), random(50, 100));
    
    private float offsetX = 0, offsetY = 0;
    
    public float limitX = 0, limitY = 0;
    
    private float carW = 0, carH = 0, carX = 0, carY = 0;
    
    public Cars(Direction direction, int laneWidth) {
        this.direction = direction;
        
        switch(direction) {
            case UP:
                vertical = true;
                offsetX += laneWidth * .1;
                posY = height;
                carW += laneWidth / 3;
                carH += carW * 2;
                break;
            case DOWN:
                vertical = true;
                offsetX -= laneWidth / 2 - laneWidth * .1;
                posY = 0;
                carW += laneWidth / 3;
                carH += carW * 2;
                break;
            case RIGHT:
                vertical = false;
                offsetY += laneWidth * .1;
                posX = 0;
                carH += laneWidth / 3;
                carW += carH * 2;
                break;
            default:
                vertical = false;
                offsetY -= laneWidth / 2 - laneWidth * .1;
                posX = width;
                carH += laneWidth / 3;
                carW += carH * 2;
                break;
        }
        
        
        carX = posX + offsetX;
        carY = posY + offsetY;
    }
    
    private void drawCar() {
        fill(20);
        if (vertical) {
            rect(carX - ((carW * .3) / 2), carY, carW * 1.3, carH * .2);
            rect(carX - ((carW * .3) / 2), carY + (carH * .8), carW * 1.3, carH * .2);
        } else {
            rect(carX, carY - ((carH * .3) / 2), carW * .2, carH * 1.3);
            rect(carX + (carW * .8), carY - ((carH * .3) / 2), carW * .2, carH * 1.3);
        }
        
        fill(paint);
        rect(carX, carY, carW, carH);
        
        fill(#22ddff);
        if (vertical) {
            rect(carX + ((carW * .3) / 2), carY, carW * .7, carH * .2);
            rect(carX + ((carW * .3) / 2), carY + (carH * .8), carW * .7, carH * .2);
        } else {
            rect(carX, carY + ((carH * .3) / 2), carW * .2, carH * .7);
            rect(carX + (carW * .8), carY + ((carH * .3) / 2), carW * .2, carH * .7);
        }
    }
    
    private void reset() {
        speedX = random(3, 6);
        speedY = random(3, 6);
        posX = CENTER_X;
        posY = CENTER_Y;
        paint = color(random(360), random(100), random(50, 100));
        switch(direction) {
            case UP:
                posY = height;
                break;
            case DOWN:
                posY = 0;
                break;
            case RIGHT:
                posX = 0;
                break;
            default:
                posX = width;
                break;
        }
        
        
        carX = posX + offsetX;
        carY = posY + offsetY;
    }
    
    void draw() {
        if (stopped == false) {
            switch(direction) {
                case UP:
                    if (posY == 0) reset();
                    posY -= speedY;
                    posY = constrain(posY, 0, height);
                    carY = posY + offsetY;
                    break;
                case DOWN:
                    if (posY == height) reset();
                    posY += speedY;
                    posY = constrain(posY, 0, height);
                    carY = posY + offsetY - carH;
                    break;
                case RIGHT:
                    if (posX == width) reset();
                    posX += speedX;
                    posX = constrain(posX, 0, width);
                    carX = posX - offsetX - carW;
                    break;
                default:
                    if (posX == 0) reset();
                    posX -= speedX;
                    posX = constrain(posX, 0, width);
                    carX = posX + offsetX;
                    break;
            }
        } else {
            switch(direction) {
                case UP:
                    if (posY == 0) reset();
                    posY -= speedY;
                    posY = constrain(posY, limitY, height);
                    carY = posY + offsetY;
                    break;
                case DOWN:
                    if (posY == height) reset();
                    posY += speedY;
                    posY = constrain(posY, 0, limitY);
                    carY = posY + offsetY - carH;
                    break;
                case RIGHT:
                    if (posX == width) reset();
                    posX += speedX;
                    posX = constrain(posX, 0, limitX);
                    carX = posX - offsetX - carW;
                    break;
                default:
                    if (posX == 0) reset();
                    posX -= speedX;
                    posX = constrain(posX, limitX, width);
                    carX = posX + offsetX;
                    break;
            }
        }
        
        drawCar();
    }
}
