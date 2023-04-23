enum Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST;
  
  public boolean isVertical() {
    return this == NORTH || this == SOUTH;
  }
}
