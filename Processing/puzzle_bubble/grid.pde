class BubbleGrid {

  BubbleCell[][] cells = new BubbleCell[15][10];
  int step = 0;

  BubbleGrid() {
    for (int row = 0; row < cells.length; row++)
      for (int col = 0; col < cells[row].length; col++) {
        if (row%2==0)
          cells[row][col] = new BubbleCell(new PVector((WALL + BUBBLE_DIAMETER/2) + (BUBBLE_DIAMETER * col), (BUBBLE_DIAMETER*step) + (WALL + BUBBLE_DIAMETER/2) + (BUBBLE_DIAMETER * row-1) * cos(radians(30))));
        else if (col>0)
          cells[row][col] = new BubbleCell(new PVector((WALL + BUBBLE_DIAMETER) + (BUBBLE_DIAMETER * (col-1)), (BUBBLE_DIAMETER*step) + (WALL + BUBBLE_DIAMETER/2) + (BUBBLE_DIAMETER * row-1) * cos(radians(30))));
      }
  }

  void draw() {
    for (int row = 0; row < cells.length; row++) {
      if (cells[row] == null) continue;
      for (int col = 0; col < cells[row].length; col++) {
        if (row%2==1)
          if (col==0) continue;
        cells[row][col].draw();
      }
    }
  }
}
