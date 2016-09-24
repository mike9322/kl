
$:.push(File::dirname($0))

load("test_prologue.rb")

class DBPath_TestClass < TestBase

  # DPath basics
  def test_1_DPath

    a = RBA::DPath::new
    assert_equal( a.to_s, "() w=0 bx=0 ex=0 r=false" )
    assert_equal( a.area.to_s, "0.0" )
    assert_equal( a.length.to_s, "0.0" )
    assert_equal( RBA::DPath::from_s(a.to_s).to_s, a.to_s )

    b = a.dup 
    a = RBA::DPath::new( [ RBA::DPoint::new( 0, 1 ), RBA::DPoint::new( 1, 5 ) ], 2.5 )
    assert_equal( a.to_s, "(0,1;1,5) w=2.5 bx=0 ex=0 r=false" )
    assert_equal( "%.3f" % a.area, "10.308" )
    assert_equal( "%.3f" % a.length, "4.123" )
    assert_equal( RBA::DPath::from_s(a.to_s).to_s, a.to_s )
    c = a.dup 

    assert_equal( a == b, false )
    assert_equal( a == c, true )
    assert_equal( a != b, true )
    assert_equal( a != c, false )

    assert_equal( "%.6f" % a.area, "10.307764" )
    assert_equal( a.width, 2.5 )
    a.width = 3.0
    assert_equal( a.width, 3 )

    a = RBA::DPath::new( [ RBA::DPoint::new( 0, 1 ), RBA::DPoint::new( 1, 5 ) ], 2.5, -0.5, 1.5 )
    assert_equal( a.to_s, "(0,1;1,5) w=2.5 bx=-0.5 ex=1.5 r=false" )
    assert_equal( RBA::DPath::from_s(a.to_s).to_s, a.to_s )
    assert_equal( "%.3f" % a.length, "5.123" )
    assert_equal( RBA::Path::from_dpath(a).to_s, "(0,1;1,5) w=3 bx=-1 ex=2 r=false" )

    a.bgn_ext = 0.5
    assert_equal( a.to_s, "(0,1;1,5) w=2.5 bx=0.5 ex=1.5 r=false" )
    assert_equal( a.bgn_ext, 0.5 )

    a.end_ext = 2.5
    assert_equal( a.to_s, "(0,1;1,5) w=2.5 bx=0.5 ex=2.5 r=false" )
    assert_equal( a.end_ext, 2.5 )

    a = RBA::DPath::new( [ RBA::DPoint::new( 0, 1 ), RBA::DPoint::new( 1, 5 ) ], 2.5, -0.5, 1.5, true )
    assert_equal( a.to_s, "(0,1;1,5) w=2.5 bx=-0.5 ex=1.5 r=true" )

    assert_equal( a.is_round?, true )
    a.round = false
    assert_equal( a.is_round?, false )

    a.points = [ RBA::DPoint::new( 0, 1 ), RBA::DPoint::new( 2, 2 ), RBA::DPoint::new( 1, 5 ) ]
    assert_equal( a.to_s, "(0,1;2,2;1,5) w=2.5 bx=-0.5 ex=1.5 r=false" )
    assert_equal( (a * 2).to_s, "(0,2;4,4;2,10) w=5 bx=-1 ex=3 r=false" )
    assert_equal( a.points, 3 )

    arr = []
    a.each_point { |p| arr.push( p.to_s ) }
    assert_equal( arr, [ "0,1", "2,2", "1,5" ] )

    b = a.dup

    assert_equal( a.moved( RBA::DPoint::new( 0, 1 ) ).to_s, "(0,2;2,3;1,6) w=2.5 bx=-0.5 ex=1.5 r=false" )
    assert_equal( a.moved( 0, 1 ).to_s, "(0,2;2,3;1,6) w=2.5 bx=-0.5 ex=1.5 r=false" )
    aa = a.dup
    aa.move( 1, 0 )
    assert_equal( aa.to_s, "(1,1;3,2;2,5) w=2.5 bx=-0.5 ex=1.5 r=false" )
    a.move( RBA::DPoint::new( 1, 0 ) )
    assert_equal( a.to_s, "(1,1;3,2;2,5) w=2.5 bx=-0.5 ex=1.5 r=false" )

    b = b.transformed( RBA::DTrans::new( RBA::DTrans::r0, RBA::DPoint::new( 1, 0 )) )
    assert_equal( b.to_s, "(1,1;3,2;2,5) w=2.5 bx=-0.5 ex=1.5 r=false" )

    m = RBA::DCplxTrans::new( RBA::DTrans::new, 1.5 )
    assert_equal( a.transformed(m).to_s, "(1.5,1.5;4.5,3;3,7.5) w=3.75 bx=-0.75 ex=2.25 r=false" )

    a.points = [ RBA::DPoint::new( 0, 1 ), RBA::DPoint::new( 1, 1 ), RBA::DPoint::new( 1, 5 ) ]
    a.width = 2.0
    a.bgn_ext = 1.0
    a.end_ext = 1.0
    assert_equal( a.bbox.to_s, "(-1,0;2,6)" )

    assert_equal( a.simple_polygon.to_s, "(-1,0;-1,2;0,2;0,6;2,6;2,0)" )
    assert_equal( a.polygon.to_s, "(-1,0;-1,2;0,2;0,6;2,6;2,0)" )

  end

  # Path basics
  def test_1_Path

    a = RBA::Path::new
    assert_equal( a.to_s, "() w=0 bx=0 ex=0 r=false" )
    assert_equal( a.area.to_s, "0" )
    assert_equal( a.length.to_s, "0" )
    assert_equal( RBA::Path::from_s(a.to_s).to_s, a.to_s )

    b = a.dup 
    a = RBA::Path::new( [ RBA::Point::new( 0, 10 ), RBA::Point::new( 10, 50 ) ], 25 )
    assert_equal( a.to_s, "(0,10;10,50) w=25 bx=0 ex=0 r=false" )
    assert_equal( a.area.to_s, "1025" )
    assert_equal( a.length.to_s, "41" )
    assert_equal( RBA::Path::from_s(a.to_s).to_s, a.to_s )
    c = a.dup 

    assert_equal( a == b, false )
    assert_equal( a == c, true )
    assert_equal( a != b, true )
    assert_equal( a != c, false )

    assert_equal( a.width, 25 )
    a.width = 30
    assert_equal( a.width, 30 )

    a = RBA::Path::new( [ RBA::Point::new( 0, 10 ), RBA::Point::new( 10, 50 ) ], 25, -5, 15 )
    assert_equal( a.to_s, "(0,10;10,50) w=25 bx=-5 ex=15 r=false" )
    assert_equal( a.length.to_s, "51" )
    assert_equal( RBA::Path::from_s(a.to_s).to_s, a.to_s )
    assert_equal( RBA::DPath::from_ipath(a).to_s, "(0,10;10,50) w=25 bx=-5 ex=15 r=false" )

    a.bgn_ext = 5
    assert_equal( a.to_s, "(0,10;10,50) w=25 bx=5 ex=15 r=false" )
    assert_equal( a.bgn_ext, 5 )

    a.end_ext = 25
    assert_equal( a.to_s, "(0,10;10,50) w=25 bx=5 ex=25 r=false" )
    assert_equal( a.end_ext, 25 )

    a = RBA::Path::new( [ RBA::Point::new( 0, 10 ), RBA::Point::new( 10, 50 ) ], 25, -5, 15, true )
    assert_equal( a.to_s, "(0,10;10,50) w=25 bx=-5 ex=15 r=true" )
    assert_equal( (a * 2).to_s, "(0,20;20,100) w=50 bx=-10 ex=30 r=true" )

    assert_equal( a.is_round?, true )
    a.round = false
    assert_equal( a.is_round?, false )

    a.points = [ RBA::Point::new( 0, 10 ), RBA::Point::new( 20, 20 ), RBA::Point::new( 10, 50 ) ]
    assert_equal( a.to_s, "(0,10;20,20;10,50) w=25 bx=-5 ex=15 r=false" )
    assert_equal( a.points, 3 )

    arr = []
    a.each_point { |p| arr.push( p.to_s ) }
    assert_equal( arr, [ "0,10", "20,20", "10,50" ] )

    b = a.dup

    assert_equal( a.moved( RBA::Point::new( 0, 10 ) ).to_s, "(0,20;20,30;10,60) w=25 bx=-5 ex=15 r=false" )
    assert_equal( a.moved( 0, 10 ).to_s, "(0,20;20,30;10,60) w=25 bx=-5 ex=15 r=false" )
    aa = a.dup
    aa.move( 10, 0 )
    assert_equal( aa.to_s, "(10,10;30,20;20,50) w=25 bx=-5 ex=15 r=false" )
    a.move( RBA::Point::new( 10, 0 ) )
    assert_equal( a.to_s, "(10,10;30,20;20,50) w=25 bx=-5 ex=15 r=false" )

    b = b.transformed( RBA::Trans::new( RBA::Trans::r0, RBA::Point::new( 10, 0 )) )
    assert_equal( b.to_s, "(10,10;30,20;20,50) w=25 bx=-5 ex=15 r=false" )

    m = RBA::CplxTrans::new( RBA::Trans::new, 1.5 )
    assert_equal( a.transformed(m).to_s, "(15,15;45,30;30,75) w=37.5 bx=-7.5 ex=22.5 r=false" )
    assert_equal( a.transformed(RBA::ICplxTrans::from_trans(m)).to_s, "(15,15;45,30;30,75) w=38 bx=-8 ex=23 r=false" )

    a.points = [ RBA::Point::new( 0, 10 ), RBA::Point::new( 10, 10 ), RBA::Point::new( 10, 50 ) ]
    a.width = 20
    a.bgn_ext = 10
    a.end_ext = 10
    assert_equal( a.bbox.to_s, "(-10,0;20,60)" )

    assert_equal( a.simple_polygon.to_s, "(-10,0;-10,20;0,20;0,60;20,60;20,0)" )
    assert_equal( a.polygon.to_s, "(-10,0;-10,20;0,20;0,60;20,60;20,0)" )

  end

end

load("test_epilogue.rb")
