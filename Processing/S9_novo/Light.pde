public class Light {
  public float x, y;
  public float d;

  public boolean on = false;

  public int timeTurnedOn;
  public float duration;

  private color lightColor;

  Light(float x, float y, float d, color lightColor) {
    this.x = x;
    this.y = y;
    this.d = d;
    this.lightColor = lightColor;
  }

  public void toggleLight() {
    this.on = !this.on;
    if (this.on) this.timeTurnedOn = millis();
  }

  public void draw() {
    noStroke();
    fill(LIGHT_OFF);
    if (this.on) fill(this.lightColor);
    circle(this.x, this.y, this.d);
  }
}
