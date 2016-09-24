
$:.push(File::dirname($0))

load("test_prologue.rb")

class DBEdges_TestClass < TestBase

  # Basics
  def test_1

    r = RBA::Edges::new
    assert_equal(r.to_s, "")
    assert_equal(r.is_empty?, true)
    assert_equal(r.size, 0)
    assert_equal(r.bbox.to_s, "()")
    assert_equal(r.is_merged?, true)
    
    r.assign(RBA::Edges::new([RBA::Edge::new(10, 20, 100, 200)]))
    assert_equal(r.to_s, "(10,20;100,200)")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 1)
    assert_equal(r.bbox.to_s, "(10,20;100,200)")
    assert_equal(r.is_merged?, false)

    r.assign(RBA::Edges::new(RBA::Edge::new(10, 20, 100, 200)))
    assert_equal(r.to_s, "(10,20;100,200)")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 1)
    assert_equal(r.bbox.to_s, "(10,20;100,200)")
    assert_equal(r.is_merged?, false)

    r.assign(RBA::Edges::new(RBA::Box::new(10, 20, 100, 200)))
    assert_equal(r.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    s = "" 
    r.each do |e|
      s.empty? || s += ";"
      s += e.to_s
    end
    assert_equal(s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 4)
    assert_equal(r.bbox.to_s, "(10,20;100,200)")
    assert_equal(r.is_merged?, false)

    assert_equal(r.moved(RBA::Point::new(10, 20)).bbox.to_s, "(20,40;110,220)")
    assert_equal(r.moved(10, 20).bbox.to_s, "(20,40;110,220)")
    rr = r.dup
    rr.move(RBA::Point::new(10, 20))
    assert_equal(rr.bbox.to_s, "(20,40;110,220)")
    rr = r.dup
    rr.move(10, 20)
    assert_equal(rr.bbox.to_s, "(20,40;110,220)")
    rr.swap(r)
    assert_equal(r.bbox.to_s, "(20,40;110,220)")
    assert_equal(rr.bbox.to_s, "(10,20;100,200)")

    assert_equal(r.transformed(RBA::Trans::new(1)).bbox.to_s, "(-220,20;-40,110)")
    rr = r.dup
    rr.transform(RBA::Trans::new(1))
    assert_equal(rr.bbox.to_s, "(-220,20;-40,110)")

    assert_equal(r.transformed(RBA::ICplxTrans::new(2)).bbox.to_s, "(-110,-220;-20,-40)")
    rr = r.dup
    rr.transform(RBA::ICplxTrans::new(2))
    assert_equal(rr.bbox.to_s, "(-110,-220;-20,-40)")

    r.clear
    assert_equal(r.to_s, "")
    assert_equal(r.is_empty?, true)
    assert_equal(r.size, 0)
    assert_equal(r.bbox.to_s, "()")
    assert_equal(r.is_merged?, true)
    
    r = RBA::Edges::new(RBA::Polygon::new(RBA::Box::new(10, 20, 100, 200)))
    assert_equal(r.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 4)
    assert_equal(r.bbox.to_s, "(10,20;100,200)")
    assert_equal(r.is_merged?, false)
    
    r = RBA::Edges::new(RBA::SimplePolygon::new(RBA::Box::new(10, 20, 100, 200)))
    assert_equal(r.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 4)
    assert_equal(r.bbox.to_s, "(10,20;100,200)")
    assert_equal(r.length, 2*90+2*180)
    assert_equal(r.length(RBA::Box::new(0, 0, 50, 50)), 70)
    assert_equal(r.is_merged?, false)

    r.insert(RBA::Box::new(10, 20, 100, 200))
    assert_equal(r.is_merged?, false)
    assert_equal(r.merged_semantics?, true)
    assert_equal(r.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20);(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    assert_equal(r.merged.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    assert_equal(r.length, 2*90+2*180)
    r.merged_semantics = false
    assert_equal(r.merged_semantics?, false)
    assert_equal(r.length, 2*(2*90+2*180))
    
    r = RBA::Edges::new(RBA::Path::new([ RBA::Point::new(0, 0), RBA::Point::new(100, 0) ], 20))
    assert_equal(r.to_s, "(0,-10;0,10);(0,10;100,10);(100,10;100,-10);(100,-10;0,-10)")
    assert_equal(r.extents.to_s, "")
    assert_equal(r.extents(10).to_s, "(-10,-20;-10,20;10,20;10,-20);(-10,0;-10,20;110,20;110,0);(90,-20;90,20;110,20;110,-20);(-10,-20;-10,0;110,0;110,-20)")
    assert_equal(r.extents(5, -5).to_s, "(-5,-5;-5,5;5,5;5,-5);(95,-5;95,5;105,5;105,-5)")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 4)
    assert_equal(r.bbox.to_s, "(0,-10;100,10)")
    assert_equal(r.is_merged?, false)
    
    r = RBA::Edges::new( [
        RBA::Polygon::new(RBA::Box::new(10, 20, 100, 200)),
        RBA::Polygon::new(RBA::Box::new(20, 50, 120, 250))
    ] )
    assert_equal(r.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20);(20,50;20,250);(20,250;120,250);(120,250;120,50);(120,50;20,50)")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 8)
    assert_equal(r.bbox.to_s, "(10,20;120,250)")
    assert_equal(r.is_merged?, false)

    ly = RBA::Layout::new
    l1 = ly.layer("l1")
    l2 = ly.layer("l2")
    c1 = ly.create_cell("C1")
    c2 = ly.create_cell("C2")
    c1.insert(RBA::CellInstArray::new(c2.cell_index, RBA::Trans::new(0, 0)))
    c1.insert(RBA::CellInstArray::new(c2.cell_index, RBA::Trans::new(0, 100)))
    c1.insert(RBA::CellInstArray::new(c2.cell_index, RBA::Trans::new(200, 100)))
    c2.shapes(l1).insert(RBA::Box::new(-10, -20, 10, 20))
    c2.shapes(l2).insert(RBA::Edge::new(-10, -20, 10, 20))
    
    r = RBA::Edges::new(ly.begin_shapes(c1.cell_index, l1), true)
    assert_equal(r.to_s(30), "(-10,-20;-10,20);(-10,20;10,20);(10,20;10,-20);(10,-20;-10,-20);(-10,80;-10,120);(-10,120;10,120);(10,120;10,80);(10,80;-10,80);(190,80;190,120);(190,120;210,120);(210,120;210,80);(210,80;190,80)")
    assert_equal(r.to_s(2), "(-10,-20;-10,20);(-10,20;10,20)...")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 12)
    assert_equal(r[1].to_s, "(-10,20;10,20)")
    assert_equal(r[100].to_s, "")
    assert_equal(r.bbox.to_s, "(-10,-20;210,120)")
    assert_equal(r.is_merged?, false)
    
    r = RBA::Edges::new(ly.begin_shapes(c1.cell_index, l2), false)
    assert_equal(r.to_s(30), "(-10,-20;10,20);(-10,80;10,120);(190,80;210,120)")
    assert_equal(r.to_s(2), "(-10,-20;10,20);(-10,80;10,120)...")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 3)
    assert_equal(r[1].to_s, "(-10,80;10,120)")
    assert_equal(r[100].to_s, "")
    assert_equal(r.bbox.to_s, "(-10,-20;210,120)")
    assert_equal(r.is_merged?, false)
    
    r = RBA::Edges::new(ly.begin_shapes(c1.cell_index, l1), RBA::ICplxTrans::new(10, 20), true)
    assert_equal(r.to_s(30), "(0,0;0,40);(0,40;20,40);(20,40;20,0);(20,0;0,0);(0,100;0,140);(0,140;20,140);(20,140;20,100);(20,100;0,100);(200,100;200,140);(200,140;220,140);(220,140;220,100);(220,100;200,100)")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 12)
    assert_equal(r.bbox.to_s, "(0,0;220,140)")
    assert_equal(r.is_merged?, false)

    a = 0
    r.each { |p| a += p.length }
    assert_equal(r.length, a)

    r = RBA::Edges::new(ly.begin_shapes(c1.cell_index, l2), RBA::ICplxTrans::new(10, 20), false)
    assert_equal(r.to_s(30), "(0,0;20,40);(0,100;20,140);(200,100;220,140)")
    assert_equal(r.is_empty?, false)
    assert_equal(r.size, 3)
    assert_equal(r.bbox.to_s, "(0,0;220,140)")
    assert_equal(r.is_merged?, false)

    a = 0
    r.each { |p| a += p.length }
    assert_equal(r.length, a)

    r = RBA::Edges::new
    r.insert(RBA::Edge::new(10, 20, 100, 200))
    assert_equal(r.to_s, "(10,20;100,200)")
    r.clear
    r.insert(RBA::Box::new(10, 20, 100, 200))
    assert_equal(r.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    r.clear
    r.insert(RBA::Polygon::new(RBA::Box::new(10, 20, 100, 200)))
    assert_equal(r.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    r.clear
    r.insert(RBA::SimplePolygon::new(RBA::Box::new(10, 20, 100, 200)))
    assert_equal(r.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    r.clear
    r.insert(RBA::Path::new([ RBA::Point::new(0, 0), RBA::Point::new(100, 0) ], 20))
    assert_equal(r.to_s, "(0,-10;0,10);(0,10;100,10);(100,10;100,-10);(100,-10;0,-10)")
    r.clear
    r.insert( [
        RBA::Polygon::new(RBA::Box::new(10, 20, 100, 200)),
        RBA::Polygon::new(RBA::Box::new(20, 50, 120, 250))
    ] )
    assert_equal(r.to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20);(20,50;20,250);(20,250;120,250);(120,250;120,50);(120,50;20,50)")
    r.clear
    r.insert( [
        RBA::Edge::new(10, 20, 100, 200),
        RBA::Edge::new(20, 50, 120, 250)
    ] )
    assert_equal(r.to_s, "(10,20;100,200);(20,50;120,250)")
    r.clear
    r.insert(ly.begin_shapes(c1.cell_index, l1))
    assert_equal(r.to_s(30), "(-10,-20;-10,20);(-10,20;10,20);(10,20;10,-20);(10,-20;-10,-20);(-10,80;-10,120);(-10,120;10,120);(10,120;10,80);(10,80;-10,80);(190,80;190,120);(190,120;210,120);(210,120;210,80);(210,80;190,80)")
    r.clear
    r.insert(ly.begin_shapes(c1.cell_index, l1), RBA::ICplxTrans::new(10, 20))
    assert_equal(r.to_s(30), "(0,0;0,40);(0,40;20,40);(20,40;20,0);(20,0;0,0);(0,100;0,140);(0,140;20,140);(20,140;20,100);(20,100;0,100);(200,100;200,140);(200,140;220,140);(220,140;220,100);(220,100;200,100)")

  end

  # Merge, booleans
  def test_2

    r1 = RBA::Edges::new
    r1.insert(RBA::Edge::new(0, 0, 100, 0))
    r2 = RBA::Edges::new
    r2.insert(RBA::Edge::new(50, 0, 200, 0))

    r = r1 + r2
    assert_equal(r.to_s, "(0,0;100,0);(50,0;200,0)")
    assert_equal(r.merged.to_s, "(0,0;200,0)")
    r.merge
    assert_equal(r.is_merged?, true)
    assert_equal(r.to_s, "(0,0;200,0)")
    r = r1.dup
    r += r2
    assert_equal(r.to_s, "(0,0;100,0);(50,0;200,0)")

    r = r1 | r2
    assert_equal(r.to_s, "(0,0;200,0)")
    assert_equal(r.merged.to_s, "(0,0;200,0)")
    r.merge
    assert_equal(r.is_merged?, true)
    assert_equal(r.to_s, "(0,0;200,0)")
    r = r1.dup
    r |= r2
    assert_equal(r.to_s, "(0,0;200,0)")

    r = r1 & r2
    assert_equal(r.to_s, "(50,0;100,0)")
    assert_equal(r.is_merged?, true)
    r = r1.dup
    r &= r2
    assert_equal(r.to_s, "(50,0;100,0)")

    r = r1 - r2
    assert_equal(r.to_s, "(0,0;50,0)")
    assert_equal(r.is_merged?, true)
    r = r1.dup
    r -= r2
    assert_equal(r.to_s, "(0,0;50,0)")

    r = r1 ^ r2
    assert_equal(r.to_s, "(0,0;50,0);(100,0;200,0)")
    assert_equal(r.is_merged?, true)
    r = r1.dup
    r ^= r2
    assert_equal(r.to_s, "(0,0;50,0);(100,0;200,0)")

  end

  # segments
  def test_3

    r = RBA::Edges::new
    r.insert(RBA::Edge::new(0, 0, 100, 0))
    assert_equal(r.centers(10, 0.0).to_s, "(45,0;55,0)")
    assert_equal(r.centers(0, 0.0).to_s, "(50,0;50,0)")
    assert_equal(r.centers(0, 0.2).to_s, "(40,0;60,0)")
    assert_equal(r.start_segments(10, 0.0).to_s, "(0,0;10,0)")
    assert_equal(r.start_segments(0, 0.2).to_s, "(0,0;20,0)")
    assert_equal(r.end_segments(10, 0.0).to_s, "(90,0;100,0)")
    assert_equal(r.end_segments(0, 0.2).to_s, "(80,0;100,0)")

  end

  # extended
  def test_3

    r = RBA::Edges::new
    r.insert(RBA::Edge::new(0, 0, 100, 0))
    r.insert(RBA::Edge::new(100, 0, 100, 100))
    assert_equal(r.extended(1, 2, 3, 4, false).to_s, "(-1,-4;-1,3;102,3;102,-4);(97,-1;97,102;104,102;104,-1)")
    assert_equal(r.extended(1, 2, 3, 4, true).to_s, "(-1,-4;-1,3;97,3;97,102;104,102;104,-4)")
    assert_equal(r.extended_in(1).to_s, "(0,-1;0,0;100,0;100,-1);(100,0;100,100;101,100;101,0)")
    assert_equal(r.extended_out(1).to_s, "(0,0;0,1;100,1;100,0);(99,0;99,100;100,100;100,0)")

  end

  # DRC
  def test_4

    r1 = RBA::Region::new
    r1.insert(RBA::Box::new(0, 0, 100, 200))
    r1.insert(RBA::Box::new(50, 200, 100, 220))
    r1.insert(RBA::Box::new(10, 220, 100, 400))
    r1 = r1.merged.edges
    r2 = RBA::Edges::new(RBA::Box::new(120, 20, 130, 380))
    r3 = RBA::Edges::new(RBA::Box::new(110, 0, 150, 400))
    r3a = RBA::Edges::new(RBA::Box::new(-30, -10, -10, 10))
    r3b = RBA::Edges::new(RBA::Box::new(-10, -10, 10, 10))

    assert_equal(r2.inside_check(r3, 15).to_s, "(120,20;120,380)/(110,9;110,391)")
    assert_equal(r2.inside_check(r3, 15, false, RBA::Edges::Projection, nil, nil, nil).to_s, "(120,20;120,380)/(110,20;110,380)")
    assert_equal(r2.inside_check(r3, 15, true, RBA::Edges::Projection, nil, nil, nil).to_s, "(120,20;120,380)/(110,0;110,400)")
    assert_equal(r2.inside_check(r3, 15, true, RBA::Edges::Projection, 0.0, nil, nil).to_s, "")
    assert_equal(r2.inside_check(r3, 15, false, RBA::Edges::Projection, nil, 0, 500).to_s, "(120,20;120,380)/(110,20;110,380)")
    assert_equal(r2.inside_check(r3, 15, false, RBA::Edges::Projection, nil, 380, 500).to_s, "")
    assert_equal(r2.inside_check(r3, 15, false, RBA::Edges::Projection, nil, 0, 300).to_s, "")
    
    assert_equal(r3.enclosing_check(r2, 15).to_s, "(110,9;110,391)/(120,20;120,380)")
    assert_equal(r3.enclosing_check(r2, 15, false, RBA::Region::Projection, nil, nil, nil).to_s, "(110,20;110,380)/(120,20;120,380)")
    assert_equal(r3.enclosing_check(r2, 15, true, RBA::Region::Projection, nil, nil, nil).to_s, "(110,0;110,400)/(120,20;120,380)")
    assert_equal(r3.enclosing_check(r2, 15, true, RBA::Region::Projection, 0.0, nil, nil).to_s, "")
    assert_equal(r3.enclosing_check(r2, 15, false, RBA::Region::Projection, nil, 0, 500).to_s, "(110,20;110,380)/(120,20;120,380)")
    assert_equal(r3.enclosing_check(r2, 15, false, RBA::Region::Projection, nil, 380, 500).to_s, "")
    assert_equal(r3.enclosing_check(r2, 15, false, RBA::Region::Projection, nil, 0, 300).to_s, "")
    
    assert_equal(r3a.separation_check(r1, 15).to_s, "(-10,10;-10,-10)/(0,0;0,21)")
    assert_equal(r3a.separation_check(r1, 15, false, RBA::Edges::Projection, nil, nil, nil).to_s, "(-10,10;-10,0)/(0,0;0,10)")
    assert_equal(r3a.separation_check(r1, 15, true, RBA::Edges::Projection, nil, nil, nil).to_s, "(-10,10;-10,-10)/(0,0;0,200)")
    assert_equal(r3a.separation_check(r1, 15, true, RBA::Edges::Projection, 0.0, nil, nil).to_s, "")
    assert_equal(r3a.separation_check(r1, 15, false, RBA::Edges::Projection, nil, 0, 500).to_s, "(-10,10;-10,0)/(0,0;0,10)")
    assert_equal(r3a.separation_check(r1, 15, false, RBA::Edges::Projection, nil, 380, 500).to_s, "")
    assert_equal(r3a.separation_check(r1, 15, false, RBA::Edges::Projection, nil, 0, 300).to_s, "(-10,10;-10,0)/(0,0;0,10)")
    
    assert_equal(r3b.overlap_check(r1, 15).to_s, "(-10,10;10,10)/(21,0;0,0);(10,10;10,-10)/(0,0;0,21)")
    assert_equal(r3b.overlap_check(r1, 15, false, RBA::Edges::Projection, nil, nil, nil).to_s, "(0,10;10,10)/(10,0;0,0);(10,10;10,0)/(0,0;0,10)")
    assert_equal(r3b.overlap_check(r1, 15, true, RBA::Edges::Projection, nil, nil, nil).to_s, "(-10,10;10,10)/(100,0;0,0);(10,10;10,-10)/(0,0;0,200)")
    assert_equal(r3b.overlap_check(r1, 15, true, RBA::Edges::Projection, 0.0, nil, nil).to_s, "")
    assert_equal(r3b.overlap_check(r1, 15, false, RBA::Edges::Projection, nil, 0, 500).to_s, "(0,10;10,10)/(10,0;0,0);(10,10;10,0)/(0,0;0,10)")
    assert_equal(r3b.overlap_check(r1, 15, false, RBA::Edges::Projection, nil, 380, 500).to_s, "")
    assert_equal(r3b.overlap_check(r1, 15, false, RBA::Edges::Projection, nil, 0, 300).to_s, "(0,10;10,10)/(10,0;0,0);(10,10;10,0)/(0,0;0,10)")
    
    assert_equal((r2 | r1).space_check(25).to_s, "(120,20;120,380)/(100,395;100,5);(0,200;50,200)/(50,220;10,220)")
    assert_equal((r2 | r1).space_check(25, false, RBA::Edges::Projection, nil, nil, nil).to_s, "(120,20;120,380)/(100,380;100,20);(10,200;50,200)/(50,220;10,220)")
    assert_equal((r2 | r1).space_check(25, true, RBA::Edges::Projection, nil, nil, nil).to_s, "(120,20;120,380)/(100,400;100,0);(0,200;50,200)/(50,220;10,220)")
    assert_equal((r2 | r1).space_check(25, true, RBA::Edges::Projection, 0.0, nil, nil).to_s, "")
    assert_equal((r2 | r1).space_check(25, true, RBA::Edges::Projection, nil, 50, nil).to_s, "(120,20;120,380)/(100,400;100,0)")
    assert_equal((r2 | r1).space_check(25, true, RBA::Edges::Projection, nil, nil, 50).to_s, "(0,200;50,200)/(50,220;10,220)")

    assert_equal((r2 | r1).width_check(60).to_s, "(120,20;120,380)/(130,380;130,20);(50,200;50,220)/(100,253;100,167)")
    assert_equal((r2 | r1).width_check(60, false, RBA::Edges::Projection, nil, nil, nil).to_s, "(120,20;120,380)/(130,380;130,20);(50,200;50,220)/(100,220;100,200)")
    assert_equal((r2 | r1).width_check(60, true, RBA::Edges::Projection, nil, nil, nil).to_s, "(120,20;120,380)/(130,380;130,20);(50,200;50,220)/(100,400;100,0)")
    assert_equal((r2 | r1).width_check(60, true, RBA::Edges::Projection, 0.0, nil, nil).to_s, "")
    assert_equal((r2 | r1).width_check(60, true, RBA::Edges::Projection, nil, 50, nil).to_s, "(120,20;120,380)/(130,380;130,20)")
    assert_equal((r2 | r1).width_check(60, true, RBA::Edges::Projection, nil, nil, 50).to_s, "(50,200;50,220)/(100,400;100,0)")

  end

  # with..
  def test_5

    r = RBA::Edges::new
    r.insert(RBA::Edge::new(0, 0, 100, 0))
    r.insert(RBA::Edge::new(100, 0, 100, 50))
    assert_equal(r.with_angle(0, false).to_s, "(0,0;100,0)")
    assert_equal(r.with_angle(0, true).to_s, "(100,0;100,50)")
    assert_equal(r.with_angle(90, false).to_s, "(100,0;100,50)")
    assert_equal(r.with_angle(90, true).to_s, "(0,0;100,0)")
    assert_equal(r.with_angle(-10, 10, false).to_s, "(0,0;100,0)")
    assert_equal(r.with_angle(-10, 10, true).to_s, "(100,0;100,50)")
    assert_equal(r.with_angle(80, 100, false).to_s, "(100,0;100,50)")
    assert_equal(r.with_length(100, false).to_s, "(0,0;100,0)")
    assert_equal(r.with_length(100, true).to_s, "(100,0;100,50)")
    assert_equal(r.with_length(50, false).to_s, "(100,0;100,50)")
    assert_equal(r.with_length(50, true).to_s, "(0,0;100,0)")
    assert_equal(r.with_length(100, nil, false).to_s, "(0,0;100,0)")
    assert_equal(r.with_length(100, 200, true).to_s, "(100,0;100,50)")
    assert_equal(r.with_length(nil, 100, false).to_s, "(100,0;100,50)")

  end

  # interact
  def test_6

    r = RBA::Edges::new
    r.insert(RBA::Edge::new(0, 0, 100, 0))
    r.insert(RBA::Edge::new(100, 0, 100, 50))
    r2 = RBA::Edges::new
    r2.insert(RBA::Edge::new(0, 10, 200, 10))
    g2 = RBA::Region::new
    g2.insert(RBA::Box::new(0, 10, 200, 20))

    assert_equal(r.interacting(r2).to_s, "(100,0;100,50)")
    assert_equal(r.not_interacting(r2).to_s, "(0,0;100,0)")
    rr = r.dup
    rr.select_interacting(r2)
    assert_equal(rr.to_s, "(100,0;100,50)")
    rr = r.dup
    rr.select_not_interacting(r2)
    assert_equal(rr.to_s, "(0,0;100,0)")

    assert_equal(r.interacting(g2).to_s, "(100,0;100,50)")
    assert_equal(r.not_interacting(g2).to_s, "(0,0;100,0)")
    rr = r.dup
    rr.select_interacting(g2)
    assert_equal(rr.to_s, "(100,0;100,50)")
    rr = r.dup
    rr.select_not_interacting(g2)
    assert_equal(rr.to_s, "(0,0;100,0)")

  end

  # Selections
  def test_7

    r1 = RBA::Edges::new
    r1.insert(RBA::Box::new(10, 20, 100, 200))
    r1.insert(RBA::Box::new(50, 70, 150, 270))
    r2 = RBA::Edges::new
    r2.insert(RBA::Box::new(100, 70, 250, 270))
    r2.insert(RBA::Box::new(10, 20, 100, 200))

    r1.merged_semantics = false
    r2.merged_semantics = false

    assert_equal(r1.in(r2).to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    assert_equal(r2.in(r1).to_s, "(10,20;10,200);(10,200;100,200);(100,200;100,20);(100,20;10,20)")
    assert_equal(r1.not_in(r2).to_s, "(50,70;50,270);(50,270;150,270);(150,270;150,70);(150,70;50,70)")
    assert_equal(r2.not_in(r1).to_s, "(100,70;100,270);(100,270;250,270);(250,270;250,70);(250,70;100,70)")

    r1.merged_semantics = true
    r2.merged_semantics = true

    assert_equal(r1.in(r2).to_s, "(10,20;10,200);(10,200;100,200);(100,20;10,20)")
    assert_equal(r2.in(r1).to_s, "(10,20;10,200);(10,200;100,200);(100,20;10,20)")
    assert_equal(r1.not_in(r2).to_s, "(100,200;100,20);(50,70;50,270);(50,270;150,270);(150,270;150,70);(150,70;50,70)")
    assert_equal(r2.not_in(r1).to_s, "(100,270;250,270);(250,270;250,70);(250,70;100,70);(100,70;100,20);(100,200;100,270)")

  end

  # Edges and regions
  def test_8

    r = RBA::Region::new
    r.insert(RBA::Box::new(0, 0, 100, 200))

    e = RBA::Edges::new
    e.insert(RBA::Edge::new(-100, 100, 200, 100))
    assert_equal((e & r).to_s, "(0,100;100,100)")
    assert_equal(e.inside_part(r).to_s, "(0,100;100,100)")

    ee = e.dup
    ee &= r
    assert_equal(ee.to_s, "(0,100;100,100)")

    ee = e.dup
    ee.select_inside(r)
    assert_equal(ee.to_s, "(0,100;100,100)")

    assert_equal((e - r).to_s, "(-100,100;0,100);(100,100;200,100)")
    assert_equal(e.outside_part(r).to_s, "(-100,100;0,100);(100,100;200,100)")

    ee = e.dup
    ee -= r
    assert_equal(ee.to_s, "(-100,100;0,100);(100,100;200,100)")

    ee = e.dup
    ee.select_outside_part(r)
    assert_equal(ee.to_s, "(-100,100;0,100);(100,100;200,100)")

    e.clear
    e.insert(RBA::Edge::new(-100, 0, 200, 0))
    assert_equal((e & r).to_s, "(0,0;100,0)")
    assert_equal(e.inside_part(r).to_s, "")

    ee = e.dup
    ee &= r
    assert_equal(ee.to_s, "(0,0;100,0)")

    ee = e.dup
    ee.select_inside(r)
    assert_equal(ee.to_s, "")

    assert_equal((e - r).to_s, "(-100,0;0,0);(100,0;200,0)")
    assert_equal(e.outside_part(r).to_s, "(-100,0;0,0);(0,0;100,0);(100,0;200,0)")

    ee = e.dup
    ee -= r
    assert_equal(ee.to_s, "(-100,0;0,0);(100,0;200,0)")

    ee = e.dup
    ee.select_outside_part(r)
    assert_equal(ee.to_s, "(-100,0;0,0);(0,0;100,0);(100,0;200,0)")

  end

end

load("test_epilogue.rb")

