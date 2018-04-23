# University of Washington, Programming Languages, Homework 6, hw6runner.rb

# This is the only file you turn in, so do not modify the other files as
# part of your solution.

class MyPiece < Piece
  # The constant All_My_Pieces should be declared here
  All_My_Pieces = All_Pieces + 
                                [[[[0, 0], [-1, 0], [-2, 0], [1, 0], [2, 0]], # long of 5 cells (only needs two)
                                [[0, 0], [0, -1], [0, -2], [0, 1], [0, 2]]],
                                rotations([[0, 0], [-1, 0], [1, 0], [-1, -1], [0, -1]]),
                                rotations([[0, 0], [1, 0], [0, -1]])]
  Cheat_Piece = [[[0, 0]]]               

  # your enhancements here

  def self.next_piece (board)
    MyPiece.new(All_My_Pieces.sample, board)
  end
  
  def self.cheat_piece(board)      
    MyPiece.new(Cheat_Piece, board)
  end
end

class MyBoard < Board
  # your enhancements here
  def initialize (game)
    super
    @current_block = MyPiece.next_piece(self)
    @cheat_mode = false
  end
  
  def next_piece
    @current_block = cheat_mode ? MyPiece.cheat_piece(self) : MyPiece.next_piece(self)
    @cheat_mode = false
    @current_pos = nil
  end  
  
  def store_current
    locations = @current_block.current_rotation
    displacement = @current_block.position
    (0..locations.size-1).each{|index| 
      current = locations[index];
      @grid[current[1]+displacement[1]][current[0]+displacement[0]] = 
      @current_pos[index]
    }
    remove_filled
    @delay = [@delay - 2, 80].max
  end
  
  def cheat
    if(!cheat_mode and score >= 100)
        @score -= 100
        @cheat_mode = true
    end
  end
  
  def cheat_mode
    @cheat_mode
  end
end

class MyTetris < Tetris
  # your enhancements here
  
  def set_board
    @canvas = TetrisCanvas.new
    @board = MyBoard.new(self)
    @canvas.place(@board.block_size * @board.num_rows + 3,
                  @board.block_size * @board.num_columns + 6, 24, 80)
    @board.draw
  end
  
  def key_bindings
    super
    @root.bind('u', proc {@board.rotate_clockwise
                          @board.rotate_clockwise})
    @root.bind('c', proc {@board.cheat})   
  end
end
