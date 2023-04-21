public class Lane {
    public LightColor lightColor;
    public float trafficLightPosX = 0;
    public float trafficLightPosY = 0;
    
    public Direction direction;
    
    public int laneWidth;
    
    private Cars traffic;
    
    
    public Lane(Direction direction,int laneWidth) {
        this.direction = direction;
        this.laneWidth = laneWidth;
        traffic = new Cars(direction, laneWidth);
}

void nextLight() {
    lightColor = lightColor.next();
}

void draw() {
    traffic.draw();
    
    noStroke();
    float TL_W = laneWidth *.2;
    float TL_H = TL_W * 3;
    float TL_R = TL_W *.7;
    
    float greenX, greenY;
    float yellowX, yellowY;
    float redX, redY;
    float boxW, boxH;
    float offsetX = 0, offsetY = 0;
    
    
    strokeWeight(3);
    stroke(0);
    
    switch(direction) {
        case UP:
            offsetX += laneWidth / 1.5;
            offsetY += laneWidth;
            boxW = TL_W;
            boxH = TL_H;
            greenX = CENTER_X;
            greenY = CENTER_Y - TL_W;
            yellowX = CENTER_X;
            yellowY = CENTER_Y;
            redX = CENTER_X;
            redY = CENTER_Y + TL_W;
            trafficLightPosY = CENTER_Y + offsetY + (boxH / 2);
            //line(0, trafficLightPosY, width, trafficLightPosY);
            traffic.limitY = trafficLightPosY;
            if (lightColor != LightColor.GREEN && traffic.posY >= trafficLightPosY)
                traffic.stopped = true;
            else
                traffic.stopped = false;
            break;
        case DOWN:
            offsetX -= laneWidth / 1.5;
            offsetY -= laneWidth;
            boxW = TL_W;
            boxH = TL_H;
            greenX = CENTER_X;
            greenY = CENTER_Y + TL_W;
            yellowX = CENTER_X;
            yellowY = CENTER_Y;
            redX = CENTER_X;
            redY = CENTER_Y - TL_W;
            trafficLightPosY = CENTER_Y + offsetY - (boxH / 2);
            //line(0, trafficLightPosY, width, trafficLightPosY);
            traffic.limitY = trafficLightPosY;
            if (lightColor != LightColor.GREEN && traffic.posY <= trafficLightPosY)
                traffic.stopped = true;
            else
                traffic.stopped = false;
            break;
        case RIGHT:
            offsetX -= laneWidth;
            offsetY += laneWidth / 1.5;
            boxW = TL_H;
            boxH = TL_W;
            greenX = CENTER_X + TL_W;
            greenY = CENTER_Y;
            yellowX = CENTER_X;
            yellowY = CENTER_Y;
            redX = CENTER_X - TL_W;
            redY = CENTER_Y;
            trafficLightPosX = CENTER_X + offsetX - (boxW / 2);
            //line(trafficLightPosX,0,trafficLightPosX,height);
            traffic.limitX = trafficLightPosX;
            if (lightColor != LightColor.GREEN && traffic.posX <= trafficLightPosX)
                traffic.stopped = true;
            else
                traffic.stopped = false;
            break;
        default:
            offsetX += laneWidth;
            offsetY -= laneWidth / 1.5;
            boxW = TL_H;
            boxH = TL_W;
            greenX = CENTER_X - TL_W;
            greenY = CENTER_Y;
            yellowX = CENTER_X;
            yellowY = CENTER_Y;
            redX = CENTER_X + TL_W;
            redY = CENTER_Y;
            trafficLightPosX = CENTER_X + offsetX + (boxW / 2);
            //line(trafficLightPosX,0,trafficLightPosX,height);
            traffic.limitX = trafficLightPosX;
            if (lightColor != LightColor.GREEN && traffic.posX >= trafficLightPosX)
                traffic.stopped = true;
            else
                traffic.stopped = false;
            break;
    }
    
    noStroke();
    
    fill(40);
    rect(CENTER_X - (boxW / 2) + offsetX, CENTER_Y - (boxH / 2) + offsetY, boxW, boxH);
    
    fill(80);
    if (lightColor == LightColor.GREEN) fill(color(#33ff33));
    circle(greenX + offsetX, greenY + offsetY, TL_R);
    
    fill(80);
    if (lightColor == LightColor.YELLOW) fill(color(#ffff33));
    circle(yellowX + offsetX, yellowY + offsetY, TL_R);
    
    fill(80);
    if (lightColor == LightColor.RED) fill(color(#ff3333));
    circle(redX + offsetX, redY + offsetY, TL_R);
}
}
