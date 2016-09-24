
$:.push(File::dirname($0))

load("test_prologue.rb")

class DBTrans_TestClass < TestBase

  # Transformation basics
  def test_1_DTrans

    a = RBA::DTrans::new
    b = RBA::DTrans::new( RBA::DTrans::m135, RBA::DPoint::new( 17, 5 ))
    c = RBA::DTrans::new( 3, true, RBA::DPoint::new( 17, 5 ))
    d = RBA::DTrans::new( RBA::DPoint::new( 17, 5 ))
    e = RBA::DTrans::new( RBA::DTrans::m135 )
    f = RBA::DTrans::from_itrans( RBA::Trans::new( RBA::Trans::m135, RBA::Point::new( 17, 5 )) )

    assert_equal( a.to_s, "r0 0,0" )
    assert_equal( RBA::DTrans::from_s(a.to_s).to_s, a.to_s )
    assert_equal( b.to_s, "m135 17,5" )
    assert_equal( c.to_s, "m135 17,5" )
    assert_equal( d.to_s, "r0 17,5" )
    assert_equal( e.to_s, "m135 0,0" )
    assert_equal( f.to_s, "m135 17,5" )
    assert_equal( RBA::DTrans::from_s(f.to_s).to_s, f.to_s )

    assert_equal( b.trans( RBA::DPoint::new( 1, 0 )).to_s, "17,4" )

    assert_equal( a == b, false )
    assert_equal( a == a, true )
    assert_equal( a != b, true )
    assert_equal( a != a, false )
    assert_equal( (d * e) == b, true )
    assert_equal( (e * d) == b, false )

    i = c.inverted

    assert_equal( i.to_s, "m135 5,17" )
    assert_equal( (i * b) == a, true )
    assert_equal( (b * i) == a, true )

    c = RBA::DTrans::new( 3, true, RBA::DPoint::new( 17, 5 ))
    assert_equal( c.to_s, "m135 17,5" )
    c.disp = RBA::DPoint::new(1, 7)
    assert_equal( c.to_s, "m135 1,7" )
    c.angle = 1
    assert_equal( c.to_s, "m45 1,7" )
    c.rot = 3
    assert_equal( c.to_s, "r270 1,7" )
    c.mirror = true
    assert_equal( c.to_s, "m135 1,7" )

  end

  # Magnification basics
  def test_2_DTrans

    a = RBA::DTrans::new
    b = RBA::DTrans::new( RBA::DTrans::m135, RBA::DPoint::new( 17, 5 ))
    ma = RBA::DCplxTrans::new( a, 0.5 )
    mb = RBA::DCplxTrans::new( b, 2.0 )
    u = RBA::DCplxTrans::new( a )

    assert_equal( ma.to_s, "r0 *0.5 0,0" )
    assert_equal( mb.to_s, "m135 *2 17,5" )

    assert_equal( ma == mb, false )
    assert_equal( ma == ma, true )
    assert_equal( ma != mb, true )
    assert_equal( ma != ma, false )

    i = mb.inverted

    assert_equal( i.to_s, "m135 *0.5 2.5,8.5" )
    assert_equal( RBA::DCplxTrans::from_s(i.to_s).to_s, i.to_s )
    assert_equal( i * mb == u, true )
    assert_equal( mb * i == u, true )

    assert_equal( mb.trans( RBA::DPoint::new( 1, 0 )).to_s, "17,3" )
    assert_equal( mb.ctrans(2).to_s, "4.0" )
    assert_equal( i.ctrans(2).to_s, "1.0" )

  end

  # Complex transformation specials
  def test_3_DTrans

    c = RBA::DCplxTrans::new( 5.0, -7.0 )
    assert_equal( c.to_s, "r0 *1 5,-7" )

    c = RBA::DCplxTrans::new( RBA::DCplxTrans::m135 )
    assert_equal( c.to_s, "m135 *1 0,0" )
    assert_equal( c.is_unity?, false )
    assert_equal( c.is_ortho?, true )
    assert_equal( c.is_mag?, false )
    assert_equal( c.is_mirror?, true )
    assert_equal( c.rot, RBA::DCplxTrans::m135 )
    assert_equal( c.s_trans.to_s, "m135 0,0" )
    assert_equal( c.angle, 270 )

    c = RBA::DCplxTrans::new( 1.5 )
    assert_equal( c.to_s, "r0 *1.5 0,0" )
    assert_equal( c.is_unity?, false )
    assert_equal( c.is_ortho?, true )
    assert_equal( c.is_mag?, true )
    assert_equal( c.is_mirror?, false )
    assert_equal( c.rot, RBA::DCplxTrans::r0 )
    assert_equal( c.s_trans.to_s, "r0 0,0" )
    assert_equal( c.angle, 0 )

    c = RBA::DCplxTrans::new( 0.75, 45, true, 2.5, -12.5 )
    assert_equal( c.to_s, "m22.5 *0.75 2.5,-12.5" )
    c = RBA::DCplxTrans::new( 0.75, 45, true, RBA::DPoint::new( 2.5, -12.5 ) )
    assert_equal( c.to_s, "m22.5 *0.75 2.5,-12.5" )
    assert_equal( c.is_unity?, false )
    assert_equal( c.is_ortho?, false )
    assert_equal( c.is_mag?, true )
    assert_equal( c.rot, RBA::DCplxTrans::m0 )
    assert_equal( c.s_trans.to_s, "m0 2.5,-12.5" )
    assert_equal( c.angle, 45 )

    assert_equal( c.ctrans( 5 ).to_s, "3.75" )
    assert_equal( c.trans( RBA::DPoint::new( 12, 16 ) ).to_s, "17.3492424049,-14.6213203436" )

    assert_equal( RBA::DCplxTrans::new.to_s, "r0 *1 0,0" )
    assert_equal( RBA::DCplxTrans::new.is_unity?, true )
    assert_equal( (c * c.inverted()).is_unity?, true )

    c.mirror = false
    assert_equal( c.to_s, "r45 *0.75 2.5,-12.5" )
    c.mag = 1.5
    assert_equal( c.to_s, "r45 *1.5 2.5,-12.5" )
    c.disp = RBA::DPoint::new( -1.0, 5.5 )
    assert_equal( c.to_s, "r45 *1.5 -1,5.5" )
    assert_equal( c.mag, 1.5 )
    c.angle = 60
    assert_equal( c.to_s, "r60 *1.5 -1,5.5" )
    assert_equal( sprintf("%g",c.angle), "60" )

  end

  # Transformation basics
  def test_1_Trans

    a = RBA::Trans::new
    b = RBA::Trans::new( RBA::Trans::m135, RBA::Point::new( 17, 5 ))
    c = RBA::Trans::new( 3, true, RBA::Point::new( 17, 5 ))
    d = RBA::Trans::new( RBA::Point::new( 17, 5 ))
    e = RBA::Trans::new( RBA::Trans::m135 )
    f = RBA::Trans::from_dtrans( RBA::DTrans::new( RBA::DTrans::m135, RBA::DPoint::new( 17, 5 )) )

    assert_equal( a.to_s, "r0 0,0" )
    assert_equal( RBA::Trans::from_s(a.to_s).to_s, a.to_s )
    assert_equal( b.to_s, "m135 17,5" )
    assert_equal( c.to_s, "m135 17,5" )
    assert_equal( d.to_s, "r0 17,5" )
    assert_equal( e.to_s, "m135 0,0" )
    assert_equal( f.to_s, "m135 17,5" )
    assert_equal( RBA::Trans::from_s(f.to_s).to_s, f.to_s )

    assert_equal( b.trans( RBA::Point::new( 1, 0 )).to_s, "17,4" )

    assert_equal( a == b, false )
    assert_equal( a == a, true )
    assert_equal( a != b, true )
    assert_equal( a != a, false )
    assert_equal( (d * e) == b, true )
    assert_equal( (e * d) == b, false )

    i = c.inverted

    assert_equal( i.to_s, "m135 5,17" )
    assert_equal( (i * b) == a, true )
    assert_equal( (b * i) == a, true )

    c = RBA::Trans::new( 3, true, RBA::Point::new( 17, 5 ))
    assert_equal( c.to_s, "m135 17,5" )
    c.disp = RBA::Point::new(1, 7)
    assert_equal( c.to_s, "m135 1,7" )
    c.angle = 1
    assert_equal( c.to_s, "m45 1,7" )
    c.rot = 3
    assert_equal( c.to_s, "r270 1,7" )
    c.mirror = true
    assert_equal( c.to_s, "m135 1,7" )

  end

  # Complex transformation basics
  def test_2_Trans

    a = RBA::Trans::new
    b = RBA::Trans::new( RBA::Trans::m135, RBA::Point::new( 17, 5 ))
    ma = RBA::CplxTrans::new( a, 0.5 )
    mb = RBA::CplxTrans::new( b, 2.0 )
    u = RBA::CplxTrans::new( a )

    assert_equal( ma.to_s, "r0 *0.5 0,0" )
    assert_equal( mb.to_s, "m135 *2 17,5" )

    assert_equal( ma == mb, false )
    assert_equal( ma == ma, true )
    assert_equal( ma != mb, true )
    assert_equal( ma != ma, false )

    i = mb.inverted

    assert_equal( i.to_s, "m135 *0.5 2.5,8.5" )
    assert_equal( i * mb == u, true )
    assert_equal( mb * i == u, true )

    assert_equal( mb.trans( RBA::Point::new( 1, 0 )).to_s, "17,3" )
    assert_equal( mb.ctrans(2).to_s, "4.0" )
    assert_equal( i.ctrans(2).to_s, "1.0" )

  end

  # Complex transformation specials
  def test_3_Trans

    c = RBA::CplxTrans::new( 5, -7 )
    assert_equal( c.to_s, "r0 *1 5,-7" )
    assert_equal( RBA::CplxTrans::from_s(c.to_s).to_s, c.to_s )

    c = RBA::CplxTrans::new( RBA::CplxTrans::m135 )
    assert_equal( c.to_s, "m135 *1 0,0" )
    assert_equal( c.is_unity?, false )
    assert_equal( c.is_ortho?, true )
    assert_equal( c.is_mag?, false )
    assert_equal( c.is_mirror?, true )
    assert_equal( c.rot, RBA::CplxTrans::m135 )
    assert_equal( c.s_trans.to_s, "m135 0,0" )
    assert_equal( c.angle, 270 )

    c = RBA::CplxTrans::new( 1.5 )
    assert_equal( c.to_s, "r0 *1.5 0,0" )
    assert_equal( c.is_unity?, false )
    assert_equal( c.is_ortho?, true )
    assert_equal( c.is_mag?, true )
    assert_equal( c.is_mirror?, false )
    assert_equal( c.rot, RBA::CplxTrans::r0 )
    assert_equal( c.s_trans.to_s, "r0 0,0" )
    assert_equal( c.angle, 0 )

    c = RBA::CplxTrans::new( 0.75, 45, true, 2.5, -12.5 )
    assert_equal( c.to_s, "m22.5 *0.75 2.5,-12.5" )
    assert_equal( RBA::CplxTrans::from_s(c.to_s).to_s, c.to_s )
    c = RBA::CplxTrans::new( 0.75, 45, true, RBA::DPoint::new( 2.5, -12.5 ) )
    assert_equal( c.to_s, "m22.5 *0.75 2.5,-12.5" )
    assert_equal( c.is_unity?, false )
    assert_equal( c.is_ortho?, false )
    assert_equal( c.is_mag?, true )
    assert_equal( c.rot, RBA::CplxTrans::m0 )
    assert_equal( c.s_trans.to_s, "m0 3,-13" )
    assert_equal( c.angle, 45 )

    assert_equal( c.ctrans( 5 ).to_s, "3.75" )
    assert_equal( c.trans( RBA::Point::new( 12, 16 ) ).to_s, "17.3492424049,-14.6213203436" )

    assert_equal( RBA::CplxTrans::new.to_s, "r0 *1 0,0" )
    assert_equal( RBA::CplxTrans::new.is_unity?, true )
    assert_equal( (c * c.inverted()).is_unity?, true )

    c.mirror = false
    assert_equal( c.to_s, "r45 *0.75 2.5,-12.5" )
    c.mag = 1.5
    assert_equal( c.to_s, "r45 *1.5 2.5,-12.5" )
    c.disp = RBA::DPoint::new( -1.0, 5.5 )
    assert_equal( c.to_s, "r45 *1.5 -1,5.5" )
    assert_equal( c.mag, 1.5 )
    c.angle = 60
    assert_equal( c.to_s, "r60 *1.5 -1,5.5" )
    assert_equal( sprintf("%g",c.angle), "60" )

  end

  # Complex transformation types
  def test_4_Trans

    a = RBA::Trans::new
    m = RBA::CplxTrans::new( a, 1.1 )
    da = RBA::DTrans::new
    dm = RBA::DCplxTrans::new( da, 1.1 )

    assert_equal( m.to_s, "r0 *1.1 0,0" )
    assert_equal( RBA::DCplxTrans::from_s(m.to_s).to_s, m.to_s )
    assert_equal( m.trans( RBA::Point::new( 5, -7 )).to_s, "5.5,-7.7" )

    im = RBA::ICplxTrans::new( a, 0.5 )
    im_old = im.dup

    assert_equal( im.to_s, "r0 *0.5 0,0" )
    assert_equal( RBA::ICplxTrans::from_s(im.to_s).to_s, im.to_s )
    assert_equal( im.trans( RBA::Point::new( 5, -7 )).to_s, "3,-4" )

    im = RBA::ICplxTrans::from_trans(m)
    assert_equal( im.to_s, "r0 *1.1 0,0" )
    assert_equal( im.trans( RBA::Point::new( 5, -7 )).to_s, "6,-8" )

    im = RBA::ICplxTrans::from_dtrans(dm)
    assert_equal( im.to_s, "r0 *1.1 0,0" )
    assert_equal( im.trans( RBA::Point::new( 5, -7 )).to_s, "6,-8" )

    im.assign(im_old)
    assert_equal( im.to_s, "r0 *0.5 0,0" )
    assert_equal( im.trans( RBA::Point::new( 5, -7 )).to_s, "3,-4" )

    assert_equal( RBA::ICplxTrans::new(5,-7).to_s, "r0 *1 5,-7" )

  end

end

load("test_epilogue.rb")
