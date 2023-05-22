class BubbleGrid {

  BubbleCell[][] cells = new BubbleCell[15][10];
  ArrayList<Bubble> falling = new ArrayList<Bubble>();

  ArrayList<Color> available_colors = new ArrayList();

  BubbleGrid(PVector pos) {
    for (int row = 0; row < cells.length; row++)
      for (int col = 0; col < cells[row].length; col++) {
        if (row%2==0)
          cells[row][col] = new BubbleCell(new PVector(pos.x +(BUBBLE_DIAMETER/2 + (BUBBLE_DIAMETER * col)), pos.y + ((WALL + BUBBLE_DIAMETER/2) + (BUBBLE_DIAMETER * row-1) * cos(radians(30)))), row, col);
        else if (col>0)
          cells[row][col] = new BubbleCell(new PVector(pos.x +(BUBBLE_DIAMETER + (BUBBLE_DIAMETER * (col-1))), pos.y + ((WALL + BUBBLE_DIAMETER/2) + (BUBBLE_DIAMETER * row-1) * cos(radians(30)))), row, col);
      }

    this.reset_colors();
    this.loadLevel();
    this.update_available_colors();
  }

  void reset_colors() {
    available_colors.clear();
    push();
    colorMode(RGB, 255, 255, 255, 100);
    available_colors.add(new Color(color(255, 50, 50)));
    available_colors.add(new Color(color(240, 230, 50)));
    available_colors.add(new Color(color(30, 30, 240)));
    available_colors.add(new Color(color(60, 230, 60)));
    available_colors.add(new Color(color(140, 60, 255)));
    available_colors.add(new Color(color(255, 140, 50)));
    pop();
  }

  Color random_color() {
    int index = (int)random(available_colors.size());
    Color b_color = available_colors.get(index);
    return b_color;
  }

  void update_available_colors() {
    ArrayList<Color> available = new ArrayList<Color>();
    for (int row = 0; row < cells.length; row++) {
      if (cells[row] == null) continue;
      for (int col = 0; col < cells[row].length; col++)
        if (cells[row][col] != null && cells[row][col].bubble != null && !available.contains(cells[row][col].bubble.b_color))
          available.add(cells[row][col].bubble.b_color);
    }
    available_colors = available;
  }


  void loadLevel() {
    reset_colors();
    String[] lines = loadStrings("lvl_" + LEVEL + ".lvl");
    for (int row = 0; row < cells.length; row++) {
      String[] cols = split(lines[row], ' ');
      for (int col = 0; col < cells[row].length; col++) {
        if (cells[row][col] == null) continue;
        if (cols[col].equals("0"))
          cells[row][col].removeBubble();
        else
          cells[row][col].setBubble(available_colors.get(Integer.parseInt(cols[col])-1));
      }
    }
  }

  ArrayList<BubbleCell> neighbors(int row, int col) {
    ArrayList<BubbleCell> nb = new ArrayList<BubbleCell>();
    // Hex grid, odd rows start at 1 and even rows start at 0
    if (row%2==0) { // Even row
      if (row > 0) { // up
        if ((col > 0) && cells[row-1][col] != null) nb.add(cells[row-1][col]);
        if ((col < cells[row-1].length-1) && cells[row-1][col+1] != null) nb.add(cells[row-1][col+1]);
      }

      if ((col > 0) && cells[row][col-1] != null) nb.add(cells[row][col-1]); // left
      if ((col < cells[row].length-1) && cells[row][col+1] != null) nb.add(cells[row][col+1]); // right

      if (row < cells.length-1 && cells[row+1] != null) { // down
        if ((col < cells[row+1].length-1) && cells[row+1][col+1] != null) nb.add(cells[row+1][col+1]);
        if ((col > 0) && cells[row+1][col] != null) nb.add(cells[row+1][col]);
      }
    } else {
      // up (dont need if because odd rows already > 0, and dont need to check if col > 0 because odd rows start at 1, and dont need to check if col < cells[row-1].length-1 because odd rows have 1 less cell)
      if (cells[row-1][col] != null) nb.add(cells[row-1][col]);
      if (cells[row-1][col-1] != null) nb.add(cells[row-1][col-1]);

      if ((col > 0) && cells[row][col-1] != null) nb.add(cells[row][col-1]); // left
      if ((col < cells[row].length-1) && cells[row][col+1] != null) nb.add(cells[row][col+1]); // right

      if (row < cells.length-1 && cells[row+1] != null) { // down
        if (cells[row+1][col-1] != null) nb.add(cells[row+1][col-1]);
        if (cells[row+1][col] != null) nb.add(cells[row+1][col]);
      }
    }
    return nb;
  }

  void ceiling_down(float step_size) {
    for (int row = 0; row < cells.length; row++) {
      if (cells[row] == null) continue;
      for (int col = 0; col < cells[row].length; col++)
        if (cells[row][col] != null) {
          cells[row][col].pos.y += step_size;
          if (cells[row][col].hasBubble()) cells[row][col].bubble.pos.y += step_size;
        }
    }
  }

  ArrayList<BubbleCell> same_color_chain(BubbleCell cell, ArrayList<BubbleCell> chain) {
    if (cell == null) return chain;
    if (chain.contains(cell)) return chain;
    chain.add(cell);
    for (BubbleCell nb : neighbors(cell.row, cell.col))
      if (nb.hasBubble() && nb.bubble.b_color == cell.bubble.b_color)
        chain = same_color_chain(nb, chain);
    return chain;
  }

  ArrayList<BubbleCell> depth_first_search(BubbleCell cell, ArrayList<BubbleCell> visited) {
    if (cell == null) return visited;
    if (visited.contains(cell)) return visited;
    visited.add(cell);
    for (BubbleCell nb : neighbors(cell.row, cell.col))
      if (nb.hasBubble())
        visited = depth_first_search(nb, visited);
    return visited;
  }

  void drop_bubbles(BubbleCell cell) {
    ArrayList<BubbleCell> visited = new ArrayList<BubbleCell>();
    for (int col = 0; col < cells[0].length; col++)
      if (cells[0][col] != null && cells[0][col].bubble != null)
        visited = depth_first_search(cells[0][col], visited);

    for (int row = 0; row < cells.length; row++) {
      if (cells[row] == null) continue;
      for (int col = 0; col < cells[row].length; col++)
        if (cells[row][col] != null && cells[row][col].bubble != null && !visited.contains(cells[row][col])) {
          this.falling.add(new Bubble(cells[row][col].bubble));
          cells[row][col].removeBubble();
        }
    }
    update_available_colors();

    int points = (10 * (int)pow(2, falling.size()-1));
    SCORE += falling.size() * points;

    for (Bubble bubble : falling)
      bubble.setPointsDisplay(points);
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

    falling.removeIf(bubble -> bubble.is_outside());

    for (Bubble bubble : falling)
      bubble.draw();
  }
}
