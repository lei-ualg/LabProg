enum LightColor {
    GREEN,
    YELLOW,
    RED;
    
    public LightColor next() {
        return values()[(ordinal() + 1) % values().length];
    }
}

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
}
