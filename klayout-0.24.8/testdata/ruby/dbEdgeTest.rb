
$:.push(File::dirname($0))

load("test_prologue.rb")

class DBEdge_TestClass < TestBase

  # DEdge basics
  def test_1_DEdge

    a = RBA::DEdge::new
    assert_equal( a.to_s, "(0,0;0,0)" )
    assert_equal( a.is_degenerate?, true )

    b = a
    a = RBA::DEdge::new( -1, 2, 15, -7 )
    assert_equal( a.to_s, "(-1,2;15,-7)" )
    assert_equal( RBA::DEdge::from_s(a.to_s).to_s, a.to_s )
    assert_equal( (a*0.5).to_s, "(-0.5,1;7.5,-3.5)" )
    d = RBA::Edge::from_dedge( a )
    assert_equal( d.to_s, "(-1,2;15,-7)" )
    assert_equal( a.p1.to_s, "-1,2" )
    assert_equal( a.p2.to_s, "15,-7" )
    assert_equal( a.x1, -1.0 )
    assert_equal( a.y1, 2.0 )
    assert_equal( a.x2, 15 )
    assert_equal( a.y2, -7.0 )
    assert_equal( a.dx, 16.0 )
    assert_equal( a.dy, -9.0 )
    assert_equal( a.dx_abs, 16.0 )
    assert_equal( a.dy_abs, 9.0 )
    assert_equal( a.is_degenerate?, false )

    c = a.dup;
    assert_equal( a == c, true )
    assert_equal( a == b, false )
    assert_equal( a != c, false )
    assert_equal( a != b, true )

    aa = a.dup
    a.move( RBA::DPoint::new( 1, 2 ) )
    assert_equal( a.to_s, "(0,4;16,-5)" )
    assert_equal( a.ortho_length, 25.0 )

    aa.move( 1, 2 )
    assert_equal( aa.to_s, "(0,4;16,-5)" )
    assert_equal( aa.ortho_length, 25.0 )
    aa.p1 = RBA::DPoint::new( 1, 5 )
    assert_equal( aa.to_s, "(1,5;16,-5)" )
    aa.p2 = RBA::DPoint::new( 2, 6 )
    assert_equal( aa.to_s, "(1,5;2,6)" )
    aa.x1 = 1.5
    assert_equal( aa.to_s, "(1.5,5;2,6)" )
    aa.x2 = 2.5
    assert_equal( aa.to_s, "(1.5,5;2.5,6)" )
    aa.y1 = 5.5
    assert_equal( aa.to_s, "(1.5,5.5;2.5,6)" )
    aa.y2 = 6.5
    assert_equal( aa.to_s, "(1.5,5.5;2.5,6.5)" )

    assert_equal( a == c.moved( RBA::DPoint::new( 1, 2 ) ), true )
    assert_equal( a == c.moved( 1, 2 ), true )

    a = RBA::DEdge::new( -1, 2, 5, 2 )
    c = a.dup

    a.enlarge( RBA::DPoint::new( 1, 0 ) )
    assert_equal( a.to_s, "(-2,2;6,2)" )
    assert_equal( a.length, 8.0 )
    assert_equal( a.ortho_length, 8.0 )
    assert_equal( a.sq_length, 64.0 )
    assert_equal( a.contains?( RBA::DPoint::new( 4, 2 ) ), true )
    assert_equal( a.contains?( RBA::DPoint::new( 4, 3 ) ), false )
    assert_equal( a.contains?( RBA::DPoint::new( -2, 2 ) ), true )
    assert_equal( a.contains_excl?( RBA::DPoint::new( 4, 2 ) ), true )
    assert_equal( a.contains_excl?( RBA::DPoint::new( 4, 3 ) ), false )
    assert_equal( a.contains_excl?( RBA::DPoint::new( -2, 2 ) ), false )
    assert_equal( a.is_parallel?( a ), true )
    assert_equal( a.coincident?( a ), true )
    assert_equal( a.is_parallel?( RBA::DEdge::new( -1, 3, 5, 3 ) ), true )
    assert_equal( a.coincident?( RBA::DEdge::new( -1, 3, 5, 3 ) ), false )
    assert_equal( a.is_parallel?( RBA::DEdge::new( -1, 3, 5, 3.5 ) ), false )
    assert_equal( a == c.enlarged( RBA::DPoint::new( 1, 0 ) ), true )

    assert_equal( a.intersect?( RBA::DEdge::new( -1, -1, 1, 5 ) ), true )
    assert_equal( a.intersection_point( RBA::DEdge::new( -1, -1, 1, 5 ) ).to_s, "0,2" )
    assert_equal( a.intersect?( RBA::DEdge::new( -1, 11, 1, 15 ) ), false )
    assert_equal( a.distance( RBA::DPoint::new( 3, 3 ) ), 1.0 )
    assert_equal( a.distance( RBA::DPoint::new( 3, 1 ) ), -1.0 )
    assert_equal( a.distance_abs( RBA::DPoint::new( 3, 3 ) ), 1.0 )
    assert_equal( a.distance_abs( RBA::DPoint::new( 3, 1 ) ), 1.0 )
    assert_equal( a.side_of( RBA::DPoint::new( 3, 3 ) ), 1 )
    assert_equal( a.side_of( RBA::DPoint::new( 3, 1 ) ), -1 )
    
    a.swap_points 
    assert_equal( a.to_s, "(6,2;-2,2)" )

    assert_equal( a.transformed(RBA::DCplxTrans::new(2.2)).to_s, "(13.2,4.4;-4.4,4.4)" )

    assert_equal( RBA::DEdge::new( -1, -5, -1, -1 ).crossed_by?( a ), true )
    assert_equal( RBA::DEdge::new( -1, -5, -1, -1 ).crossing_point( a ).to_s, "-1,2" )
    assert_equal( RBA::DEdge::new( -5, -5, -5, -1 ).crossed_by?( a ), false )

    a = RBA::DEdge::new(10, 0, 50, 0)
    assert_equal( a.shifted(2.5).to_s, "(10,2.5;50,2.5)" )
    a.shift( -1.5 )
    assert_equal( a.to_s, "(10,-1.5;50,-1.5)" )
    assert_equal( a.swapped_points.to_s, "(50,-1.5;10,-1.5)" )

    a = RBA::DEdge::new(10, 0, 50, 0)
    assert_equal( a.extended(2.5).to_s, "(7.5,0;52.5,0)")
    a.extend(-2.5)
    assert_equal( a.to_s, "(12.5,0;47.5,0)")

  end

  # Edge basics
  def test_1_Edge

    a = RBA::Edge::new
    assert_equal( a.to_s, "(0,0;0,0)" )
    assert_equal( a.is_degenerate?, true )

    b = a
    a = RBA::Edge::new( RBA::Point::new( -1, 2 ), RBA::Point::new( 15, -7 ) )
    assert_equal( a.to_s, "(-1,2;15,-7)" )
    assert_equal( RBA::Edge::from_s(a.to_s).to_s, a.to_s )
    assert_equal( (a*2).to_s, "(-2,4;30,-14)" )
    d = RBA::DEdge::from_iedge( a )
    assert_equal( d.to_s, "(-1,2;15,-7)" )
    assert_equal( a.p1.to_s, "-1,2" )
    assert_equal( a.p2.to_s, "15,-7" )
    assert_equal( a.x1, -1 )
    assert_equal( a.y1, 2 )
    assert_equal( a.x2, 15 )
    assert_equal( a.y2, -7 )
    assert_equal( a.dx, 16 )
    assert_equal( a.dy, -9 )
    assert_equal( a.dx_abs, 16 )
    assert_equal( a.dy_abs, 9 )
    assert_equal( a.is_degenerate?, false )

    c = a.dup;
    assert_equal( a == c, true )
    assert_equal( a == b, false )
    assert_equal( a != c, false )
    assert_equal( a != b, true )

    aa = a.dup
    a.move( RBA::Point::new( 1, 2 ) )
    assert_equal( a.to_s, "(0,4;16,-5)" )
    assert_equal( a.ortho_length, 25 )

    aa.move( 1, 2 )
    assert_equal( aa.to_s, "(0,4;16,-5)" )
    assert_equal( aa.ortho_length, 25 )
    aa.p1 = RBA::Point::new( 1, 5 )
    assert_equal( aa.to_s, "(1,5;16,-5)" )
    aa.p2 = RBA::Point::new( 2, 6 )
    assert_equal( aa.to_s, "(1,5;2,6)" )
    aa.x1 = -1
    assert_equal( aa.to_s, "(-1,5;2,6)" )
    aa.x2 = -2
    assert_equal( aa.to_s, "(-1,5;-2,6)" )
    aa.y1 = -5
    assert_equal( aa.to_s, "(-1,-5;-2,6)" )
    aa.y2 = -6
    assert_equal( aa.to_s, "(-1,-5;-2,-6)" )

    assert_equal( a == c.moved( RBA::Point::new( 1, 2 ) ), true )
    assert_equal( a == c.moved( 1, 2 ), true )

    a = RBA::Edge::new( RBA::Point::new( -1, 2 ), RBA::Point::new( 5, 2 ) )
    c = a.dup

    a.enlarge( RBA::Point::new( 1, 0 ) )
    assert_equal( a.to_s, "(-2,2;6,2)" )
    assert_equal( a.length, 8 )
    assert_equal( a.ortho_length, 8 )
    assert_equal( a.sq_length, 64 )
    assert_equal( a.contains?( RBA::Point::new( 4, 2 ) ), true )
    assert_equal( a.contains?( RBA::Point::new( 4, 3 ) ), false )
    assert_equal( a.contains?( RBA::Point::new( -2, 2 ) ), true )
    assert_equal( a.contains_excl?( RBA::Point::new( 4, 2 ) ), true )
    assert_equal( a.contains_excl?( RBA::Point::new( 4, 3 ) ), false )
    assert_equal( a.contains_excl?( RBA::Point::new( -2, 2 ) ), false )
    assert_equal( a.is_parallel?( a ), true )
    assert_equal( a.coincident?( a ), true )
    assert_equal( a.is_parallel?( RBA::Edge::new( RBA::Point::new( -1, 3 ), RBA::Point::new( 5, 3 ) ) ), true )
    assert_equal( a.coincident?( RBA::Edge::new( RBA::Point::new( -1, 3 ), RBA::Point::new( 5, 3 ) ) ), false )
    assert_equal( a.is_parallel?( RBA::Edge::new( RBA::Point::new( -1, 3 ), RBA::Point::new( 5, 4 ) ) ), false )
    assert_equal( a == c.enlarged( RBA::Point::new( 1, 0 ) ), true )

    assert_equal( a.intersect?( RBA::Edge::new( RBA::Point::new( -1, -1 ), RBA::Point::new( 1, 5 ) ) ), true )
    assert_equal( a.intersection_point( RBA::Edge::new( RBA::Point::new( -1, -1 ), RBA::Point::new( 1, 5 ) ) ).to_s, "0,2" )
    assert_equal( a.intersect?( RBA::Edge::new( RBA::Point::new( -1, 11 ), RBA::Point::new( 1, 15 ) ) ), false )
    assert_equal( a.distance( RBA::Point::new( 3, 3 ) ), 1.0 )
    assert_equal( a.distance( RBA::Point::new( 3, 1 ) ), -1.0 )
    assert_equal( a.distance_abs( RBA::Point::new( 3, 3 ) ), 1.0 )
    assert_equal( a.distance_abs( RBA::Point::new( 3, 1 ) ), 1.0 )
    assert_equal( a.side_of( RBA::Point::new( 3, 3 ) ), 1 )
    assert_equal( a.side_of( RBA::Point::new( 3, 1 ) ), -1 )
    
    a.swap_points 
    assert_equal( a.to_s, "(6,2;-2,2)" )

    assert_equal( RBA::Edge::new( RBA::Point::new( -1, -5 ), RBA::Point::new( -1, -1 ) ).crossed_by?( a ), true )
    assert_equal( RBA::Edge::new( RBA::Point::new( -1, -5 ), RBA::Point::new( -1, -1 ) ).crossing_point( a ).to_s, "-1,2" )
    assert_equal( RBA::Edge::new( RBA::Point::new( -5, -5 ), RBA::Point::new( -5, -1 ) ).crossed_by?( a ), false )

    assert_equal( a.transformed(RBA::CplxTrans::new(2.2)).to_s, "(13.2,4.4;-4.4,4.4)" )
    assert_equal( a.transformed(RBA::ICplxTrans::new(2.2)).to_s, "(13,4;-4,4)" )

    a = RBA::DEdge::new(10, 0, 50, 0)
    assert_equal( a.shifted(2).to_s, "(10,2;50,2)" )
    a.shift( -5 )
    assert_equal( a.to_s, "(10,-5;50,-5)" )
    assert_equal( a.swapped_points.to_s, "(50,-5;10,-5)" )

    a = RBA::DEdge::new(10, 0, 50, 0)
    assert_equal( a.extended(5).to_s, "(5,0;55,0)")
    a.extend(-2)
    assert_equal( a.to_s, "(12,0;48,0)")

  end

end

load("test_epilogue.rb")
