
$:.push(File::dirname($0))

load("test_prologue.rb")


class DBBox_TestClass < TestBase

  # DBox basics
  def test_1_DBox

    a = RBA::DBox::new( -10, 21, 11, 17 )
    assert_equal( a.to_s, "(-10,17;11,21)" )
    assert_equal( RBA::DBox::from_s(a.to_s).to_s, a.to_s )
    assert_equal( (a*0.5).to_s, "(-5,8.5;5.5,10.5)" )

    b = a
    a = a.moved( RBA::DPoint::new( 1, 1 ))

    assert_equal( a.to_s, "(-9,18;12,22)" )
    a = b.moved( 1, -1 )
    assert_equal( a.to_s, "(-9,16;12,20)" )

    a = b.dup
    a.move( 1, -1 )
    assert_equal( a.to_s, "(-9,16;12,20)" )

    a = b.dup
    a.move( RBA::DPoint::new( 1, 1 ))
    assert_equal( a.to_s, "(-9,18;12,22)" )

    assert_equal( b.to_s, "(-10,17;11,21)" )

    assert_equal( a == b, false )
    assert_equal( a != b, true )
    assert_equal( a != a, false )
    assert_equal( a == a, true )
    assert_equal( b != b, false )
    assert_equal( b == b, true )

    a.move( RBA::DPoint::new(1, 1) ).move( RBA::DPoint::new(-2, 2) )
    assert_equal( a.to_s, "(-10,21;11,25)" )

    a.enlarge( RBA::DPoint::new(1, -1) )
    assert_equal( a.to_s, "(-11,22;12,24)" )

    aa = a.dup
    a.enlarge( -1, 1 )
    assert_equal( a.to_s, "(-10,21;11,25)" )
    assert_equal( aa.enlarged( -1, 1 ).to_s, "(-10,21;11,25)" )

    a = a.enlarged( RBA::DPoint::new(1, -1) )
    assert_equal( a.to_s, "(-11,22;12,24)" )

    assert_equal( b.to_s, "(-10,17;11,21)" )

    assert_equal( b.height.to_s, "4.0" )
    assert_equal( b.width.to_s, "21.0" )
    assert_equal( b.perimeter.to_s, "50.0" )
    assert_equal( b.center.to_s, "0.5,19" )
    assert_equal( b.left.to_s, "-10.0" )
    assert_equal( b.right.to_s, "11.0" )
    assert_equal( b.bottom.to_s, "17.0" )
    assert_equal( b.top.to_s, "21.0" )
    assert_equal( b.contains?( RBA::DPoint::new( 0, 0 )), false )
    assert_equal( b.contains?( 0, 0 ), false )
    assert_equal( b.contains?( RBA::DPoint::new( 0, 18 )), true )
    assert_equal( b.contains?( 0, 18 ), true )
    assert_equal( b.inside?( RBA::DBox::new( -20, 15, 21, 22 )), true )
    assert_equal( b.inside?( RBA::DBox::new( -20, 15, 5, 22 )), false )
    assert_equal( b.touches?( RBA::DBox::new( -20, 15, 21, 22 )), true )
    assert_equal( b.touches?( RBA::DBox::new( -20, 15, 5, 22 )), true )
    assert_equal( b.touches?( RBA::DBox::new( -20, 15, -10, 22 )), true )
    assert_equal( b.touches?( RBA::DBox::new( -20, 15, -16, 22 )), false )
    assert_equal( b.overlaps?( RBA::DBox::new( -20, 15, 21, 22 )), true )
    assert_equal( b.overlaps?( RBA::DBox::new( -20, 15, 5, 22 )), true )
    assert_equal( b.overlaps?( RBA::DBox::new( -20, 15, -10, 22 )), false )
    assert_equal( b.overlaps?( RBA::DBox::new( -20, 15, -16, 22 )), false )
    assert_equal( b.area.to_s, "84.0" )
    assert_equal( b.is_point?, false )
    assert_equal( RBA::DBox::new(b.p1, b.p1).to_s, "(-10,17;-10,17)" )
    assert_equal( RBA::DBox::new(b.p1, b.p1).is_point?, true )

    assert_equal( a.empty?, false )

    a = RBA::DBox.new 
    assert_equal( a.empty?, true )

  end

  # DBox basics
  def test_2_DBox

    a = RBA::DBox::new
    b = RBA::DBox::new( RBA::DPoint::new( 1, -1 ), RBA::DPoint::new( 17, 22 ))
    c = RBA::DBox::new( RBA::DPoint::new( 10, -10 ), RBA::DPoint::new( 22, 10 ))
    
    assert_equal( b.to_s, "(1,-1;17,22)" )

    assert_equal( a & b, a )
    assert_equal( (a & b).to_s, "()" )
    assert_equal( (b & c).to_s, "(10,-1;17,10)" )

    assert_equal( a + b, b )
    assert_equal( (b + c).to_s, "(1,-10;22,22)" )

    assert_equal( a + RBA::DPoint::new( 1, -5 ), RBA::DBox::new( 1, -5, 1, -5 ) )
    assert_equal( (b + RBA::DPoint::new( 1, -5 )).to_s, "(1,-5;17,22)" )

    assert_equal( a * b, a )
    assert_equal( (b * c).to_s, "(11,-11;39,32)" )

  end
  
  # DBox basics
  def test_3_DBox

    a = RBA::Box::new( RBA::Point::new( 1, -1 ), RBA::Point::new( 17, 22 ))
    b = RBA::DBox::from_ibox( a )

    assert_equal( a.to_s, "(1,-1;17,22)" )
    assert_equal( b.to_s, "(1,-1;17,22)" )

    t = RBA::DTrans::new( RBA::DTrans::r90, RBA::DPoint::new( 5, 6 ))
    assert_equal( b.transformed(t).to_s, "(-17,7;6,23)" )
    m = RBA::DCplxTrans::new( t, 1.5 )
    assert_equal( b.transformed(m).to_s, "(-28,7.5;6.5,31.5)" )

  end

  # DBox dup, object identity etc.
  def test_4_DBox 

    ref1 = RBA::DBox.new( 10, 5, 20, 17 )
    ref2 = RBA::DBox.new( 10, 5, 20, 17 )
    ref2.move( RBA::DPoint.new(-0.5, 0.0) )

    box1 = RBA::DBox.new( 10, 5, 20, 17 )
    box2 = box1
    box3 = box1.dup

    assert_equal( box1, ref1 )
    assert_equal( box2, ref1 )
    assert_equal( box3, ref1 )

    box1.move( RBA::DPoint.new(-0.5, 0.0) )

    assert_equal( box1, ref2 )
    assert_equal( box2, ref2 )
    assert_equal( box3, ref1 )

  end

  # DBox dup, object identity etc.
  def test_5_DBox

    ref1 = RBA::DBox.new( 10, 5, 20, 17 )
    ref2 = RBA::DBox.new( 10, 5, 20, 17 )
    ref2.move( RBA::DPoint.new(-0.5, 0.0) )

    box1 = RBA::DBox.new( 10, 5, 20, 17 )
    box2 = box1
    box3 = box1.dup

    assert_equal( box1, ref1 )
    assert_equal( box2, ref1 )
    assert_equal( box3, ref1 )

    box1.p1 = box1.p1 + RBA::DPoint.new( -0.5, 0.0 )
    box1.p2 = box1.p2 + RBA::DPoint.new( -0.5, 0.0 )

    assert_equal( box1, ref2 )
    assert_equal( box2, ref2 )
    assert_equal( box3, ref1 )

  end

  # DBox dup, object identity etc.
  def test_6_DBox 

    ref1 = RBA::DBox.new( 10, 5, 20, 17 )
    ref2 = RBA::DBox.new( 10, 5, 20, 17 )
    ref2.move( RBA::DPoint.new(-0.5, 0.0) )

    box1 = RBA::DBox.new( 10, 5, 20, 17 )
    box2 = box1
    box3 = box1.dup

    assert_equal( box1, ref1 )
    assert_equal( box2, ref1 )
    assert_equal( box3, ref1 )

    box1.left = box1.left - 0.5
    box1.right = box1.right - 0.5

    assert_equal( box1, ref2 )
    assert_equal( box2, ref2 )
    assert_equal( box3, ref1 )

  end

  # Box basics
  def test_1_Box

    a = RBA::Box::new( -10, 21, 11, 17 )
    assert_equal( a.to_s, "(-10,17;11,21)" )
    assert_equal( RBA::Box::from_s(a.to_s).to_s, a.to_s )
    assert_equal( (a*2).to_s, "(-20,34;22,42)" )

    b = a
    a = a.moved( RBA::Point::new( 1, 1 ))

    assert_equal( a.to_s, "(-9,18;12,22)" )
    a = b.moved( 1, -1 )
    assert_equal( a.to_s, "(-9,16;12,20)" )

    a = b.dup
    a.move( 1, -1 )
    assert_equal( a.to_s, "(-9,16;12,20)" )

    a = b.dup
    a.move( RBA::Point::new( 1, 1 ))
    assert_equal( a.to_s, "(-9,18;12,22)" )

    assert_equal( b.to_s, "(-10,17;11,21)" )

    assert_equal( a == b, false )
    assert_equal( a != b, true )
    assert_equal( a != a, false )
    assert_equal( a == a, true )
    assert_equal( b != b, false )
    assert_equal( b == b, true )

    a.move( RBA::Point::new(1, 1) ).move( RBA::Point::new(-2, 2) )
    assert_equal( a.to_s, "(-10,21;11,25)" )

    a.enlarge( RBA::Point::new(1, -1) )
    assert_equal( a.to_s, "(-11,22;12,24)" )

    aa = a.dup
    a.enlarge( -1, 1 )
    assert_equal( a.to_s, "(-10,21;11,25)" )
    assert_equal( aa.enlarged( -1, 1 ).to_s, "(-10,21;11,25)" )

    a = a.enlarged( RBA::Point::new(1, -1) )
    assert_equal( a.to_s, "(-11,22;12,24)" )

    assert_equal( b.to_s, "(-10,17;11,21)" )

    assert_equal( b.height.to_s, "4" )
    assert_equal( b.width.to_s, "21" )
    assert_equal( b.perimeter.to_s, "50" )
    assert_equal( b.center.to_s, "0,19" )
    assert_equal( b.left.to_s, "-10" )
    assert_equal( b.right.to_s, "11" )
    assert_equal( b.bottom.to_s, "17" )
    assert_equal( b.top.to_s, "21" )
    assert_equal( b.contains?( RBA::Point::new( 0, 0 )), false )
    assert_equal( b.contains?( 0, 0 ), false )
    assert_equal( b.contains?( RBA::Point::new( 0, 18 )), true )
    assert_equal( b.contains?( 0, 18 ), true )
    assert_equal( b.inside?( RBA::Box::new( -20, 15, 21, 22 )), true )
    assert_equal( b.inside?( RBA::Box::new( -20, 15, 5, 22 )), false )
    assert_equal( b.touches?( RBA::Box::new( -20, 15, 21, 22 )), true )
    assert_equal( b.touches?( RBA::Box::new( -20, 15, 5, 22 )), true )
    assert_equal( b.touches?( RBA::Box::new( -20, 15, -10, 22 )), true )
    assert_equal( b.touches?( RBA::Box::new( -20, 15, -16, 22 )), false )
    assert_equal( b.overlaps?( RBA::Box::new( -20, 15, 21, 22 )), true )
    assert_equal( b.overlaps?( RBA::Box::new( -20, 15, 5, 22 )), true )
    assert_equal( b.overlaps?( RBA::Box::new( -20, 15, -10, 22 )), false )
    assert_equal( b.overlaps?( RBA::Box::new( -20, 15, -16, 22 )), false )
    assert_equal( b.area.to_s, "84.0" )
    assert_equal( b.is_point?, false )
    assert_equal( RBA::Box::new(b.p1, b.p1).to_s, "(-10,17;-10,17)" )
    assert_equal( RBA::Box::new(b.p1, b.p1).is_point?, true )

    assert_equal( a.empty?, false )

    a = RBA::Box.new 
    assert_equal( a.empty?, true )

  end

  # Box basics
  def test_2_Box

    a = RBA::Box::new
    b = RBA::Box::new( RBA::Point::new( 1, -1 ), RBA::Point::new( 17, 22 ) )
    c = RBA::Box::new( RBA::Point::new( 10, -10 ), RBA::Point::new( 22, 10 ) )
    
    assert_equal( b.to_s, "(1,-1;17,22)" )

    assert_equal( a & b, a )
    assert_equal( (a & b).to_s, "()" )
    assert_equal( (b & c).to_s, "(10,-1;17,10)" )

    assert_equal( a + b, b )
    assert_equal( (b + c).to_s, "(1,-10;22,22)" )

    assert_equal( a + RBA::Point::new( 1, -5 ), RBA::Box::new( 1, -5, 1, -5 ) )
    assert_equal( (b + RBA::Point::new( 1, -5 )).to_s, "(1,-5;17,22)" )

    assert_equal( a * b, a )
    assert_equal( (b * c).to_s, "(11,-11;39,32)" )

  end
  
  # Box basics
  def test_3_Box

    a = RBA::DBox::new( RBA::DPoint::new( 1, -1 ), RBA::DPoint::new( 17, 22 ) )
    b = RBA::Box::from_dbox( a )

    assert_equal( a.to_s, "(1,-1;17,22)" )
    assert_equal( b.to_s, "(1,-1;17,22)" )

    t = RBA::Trans::new( RBA::Trans::r90, RBA::Point::new( 5, 6 ))
    assert_equal( b.transformed(t).to_s, "(-17,7;6,23)" )
    m = RBA::CplxTrans::new( t, 1.5 )
    assert_equal( b.transformed(m).to_s, "(-28,7.5;6.5,31.5)" )

  end

  # Box dup, object identity etc.
  def test_4_Box

    ref1 = RBA::Box.new( 10, 5, 20, 17 )
    ref2 = RBA::Box.new( 10, 5, 20, 17 )
    ref2.move( RBA::Point.new(-5, 0) )

    box1 = RBA::Box.new( 10, 5, 20, 17 )
    box2 = box1
    box3 = box1.dup

    assert_equal( box1, ref1 )
    assert_equal( box2, ref1 )
    assert_equal( box3, ref1 )

    box1.move( RBA::Point.new(-5, 0) )

    assert_equal( box1, ref2 )
    assert_equal( box2, ref2 )
    assert_equal( box3, ref1 )

  end

  # Box dup, object identity etc.
  def test_5_Box

    ref1 = RBA::Box.new( 10, 5, 20, 17 )
    ref2 = RBA::Box.new( 10, 5, 20, 17 )
    ref2.move( RBA::Point.new(-5, 0.0) )

    box1 = RBA::Box.new( 10, 5, 20, 17 )
    box2 = box1
    box3 = box1.dup

    assert_equal( box1, ref1 )
    assert_equal( box2, ref1 )
    assert_equal( box3, ref1 )

    box1.p1 = box1.p1 + RBA::Point.new( -5, 0.0 )
    box1.p2 = box1.p2 + RBA::Point.new( -5, 0.0 )

    assert_equal( box1, ref2 )
    assert_equal( box2, ref2 )
    assert_equal( box3, ref1 )

  end

  # Box dup, object identity etc.
  def test_6_Box

    ref1 = RBA::Box.new( 10, 5, 20, 17 )
    ref2 = RBA::Box.new( 10, 5, 20, 17 )
    ref2.move( RBA::Point.new(-5, 0) )

    box1 = RBA::Box.new( 10, 5, 20, 17 )
    box2 = box1
    box3 = box1.dup

    assert_equal( box1, ref1 )
    assert_equal( box2, ref1 )
    assert_equal( box3, ref1 )

    box1.left = box1.left - 5
    box1.right = box1.right - 5

    assert_equal( box1, ref2 )
    assert_equal( box2, ref2 )
    assert_equal( box3, ref1 )

  end

end

load("test_epilogue.rb")
